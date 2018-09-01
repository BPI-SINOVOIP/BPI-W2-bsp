/**************************************************************
// Spec Version                  : 0.0.2
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/4/22 17:17:31
***************************************************************/


#ifndef _TVE_REG_H_INCLUDED_
#define _TVE_REG_H_INCLUDED_
#ifdef  _TVE_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     write_en6:1;
unsigned int     ph_sync_go:1;
unsigned int     write_en5:1;
unsigned int     hi_sync_go:1;
unsigned int     write_en4:1;
unsigned int     pi_sync_go:1;
unsigned int     write_en3:1;
unsigned int     i_sync_go:1;
unsigned int     write_en2:1;
unsigned int     p_sync_go:1;
unsigned int     write_en1:1;
unsigned int     h_sync_go:1;
}TVE_SYNCGEN_RST;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     v_thr:11;
unsigned int     write_en1:1;
unsigned int     h_thr:13;
}TVE_SYNCGEN_I;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     write_en3:1;
unsigned int     i_p_sel:1;
unsigned int     write_en2:1;
unsigned int     v_thr:11;
unsigned int     write_en1:1;
unsigned int     h_thr:13;
}TVE_SYNCGEN_P;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     write_en4:1;
unsigned int     mode_1080i:1;
unsigned int     write_en3:1;
unsigned int     i_p_sel:1;
unsigned int     write_en2:1;
unsigned int     v_thr:11;
unsigned int     write_en1:1;
unsigned int     h_thr:13;
}TVE_SYNCGEN_HDMI;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     comp_ebl:1;
unsigned int     sdtv_ebl:1;
unsigned int     vs_polar:1;
unsigned int     hs_polar:1;
unsigned int     vga_hvsync:1;
unsigned int     comp_sel:1;
unsigned int     sync_rb_ebl:1;
unsigned int     sync_g_ebl:1;
unsigned int     rgb_mod:1;
unsigned int     vbi_rb_ebl:1;
unsigned int     vbi_g_ebl:1;
unsigned int     hdsync:1;
unsigned int     syncmod_sel:1;
unsigned int     write_data:1;
}TVE_COMP_CTRL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     i_field:1;
unsigned int     i_vcnt:11;
unsigned int     p_field:1;
unsigned int     p_vcnt:11;
}TVE_SYNCGEN_STATUS_I;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     h_field:1;
unsigned int     h_vcnt:11;
}TVE_SYNCGEN_STATUS_H;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     inten_vbi_h:1;
unsigned int     inten_vbi_i:1;
unsigned int     inten_vbi_p:1;
unsigned int     inten_h:1;
unsigned int     inten_i:1;
unsigned int     inten_p:1;
unsigned int     write_data:1;
}TVE_INTEN;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     intst_vbi_h:1;
unsigned int     intst_vbi_i:1;
unsigned int     intst_vbi_p:1;
unsigned int     intst_h:1;
unsigned int     intst_i:1;
unsigned int     intst_p:1;
unsigned int     write_data:1;
}TVE_INTST;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     int_vpos:11;
unsigned int     write_en1:1;
unsigned int     int_hpos:13;
}TVE_INTPOS_I;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     int_vpos:11;
unsigned int     write_en1:1;
unsigned int     int_hpos:13;
}TVE_INTPOS_P1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     int_vpos:11;
unsigned int     write_en1:1;
unsigned int     int_hpos:13;
}TVE_INTPOS_P2;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     int_vpos:11;
unsigned int     write_en1:1;
unsigned int     int_hpos:13;
}TVE_INTPOS_H1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     int_vpos:11;
unsigned int     write_en1:1;
unsigned int     int_hpos:13;
}TVE_INTPOS_H2;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     srstn:1;
}TVE_SRSTN;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     h_colorbar_ebl:1;
unsigned int     h_black_ebl:1;
unsigned int     i_colorbar_ebl:1;
unsigned int     p_colorbar_ebl:1;
unsigned int     i_black_ebl:1;
unsigned int     p_black_ebl:1;
unsigned int     write_data:1;
}TVE_AV_CTRL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     fir422_sel:2;
}TVE_CAV_422;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     write_en4:1;
unsigned int     i_en:1;
unsigned int     write_en3:1;
unsigned int     p_en:1;
unsigned int     write_en2:1;
unsigned int     i_slewrate:2;
unsigned int     write_en1:1;
unsigned int     p_slewrate:2;
}TVE_AV_SLEW;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     write_en2:1;
unsigned int     i_h_st:10;
unsigned int     write_en1:1;
unsigned int     i_h_end:10;
}TVE_SLEW_I_HPOS;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     write_en2:1;
unsigned int     i_h_st:13;
unsigned int     write_en1:1;
unsigned int     i_h_end:13;
}TVE_AV_I_HPOS;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     write_en3:1;
unsigned int     p_av_cord:1;
unsigned int     write_en2:1;
unsigned int     p_h_st:13;
unsigned int     write_en1:1;
unsigned int     p_h_end:13;
}TVE_AV_P_HPOS1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     write_en3:1;
unsigned int     h_av_cord:1;
unsigned int     write_en2:1;
unsigned int     h_h_st:13;
unsigned int     write_en1:1;
unsigned int     h_h_end:13;
}TVE_AV_H_HPOS1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_en2:1;
unsigned int     itop_v_st:11;
unsigned int     write_en1:1;
unsigned int     itop_v_end:11;
}TVE_ITOP_VPOS;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_en2:1;
unsigned int     ibot_v_st:11;
unsigned int     write_en1:1;
unsigned int     ibot_v_end:11;
}TVE_IBOT_VPOS;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_en2:1;
unsigned int     p_v_st:11;
unsigned int     write_en1:1;
unsigned int     p_v_end:11;
}TVE_P_VPOS1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_en2:1;
unsigned int     p_v_st:11;
unsigned int     write_en1:1;
unsigned int     p_v_end:11;
}TVE_P_VPOS2;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_en2:1;
unsigned int     h_v_st:11;
unsigned int     write_en1:1;
unsigned int     h_v_end:11;
}TVE_H_VPOS1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_en2:1;
unsigned int     h_v_st:11;
unsigned int     write_en1:1;
unsigned int     h_v_end:11;
}TVE_H_VPOS2;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     write_en2:1;
unsigned int     i_h_width:10;
unsigned int     write_en1:1;
unsigned int     i_h_st_pos:10;
}TVE_I_COLORBAR_HPOS;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     write_en2:1;
unsigned int     p_h_width:10;
unsigned int     write_en1:1;
unsigned int     p_h_st_pos:10;
}TVE_P_COLORBAR_HPOS;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     write_en2:1;
unsigned int     p_h_width:10;
unsigned int     write_en1:1;
unsigned int     p_h_st_pos:10;
}TVE_H_COLORBAR_HPOS;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     write_en3:1;
unsigned int     negsyncst:9;
unsigned int     write_en2:1;
unsigned int     possyncst:9;
unsigned int     write_en1:1;
unsigned int     syncend:9;
}TVE_COMP_VSYNC_HPOS;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     1080i_ebl:1;
}TVE_COMP_SER_CTRL;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     write_en2:1;
unsigned int     ser_hstart:13;
unsigned int     write_en1:1;
unsigned int     ser_hend:13;
}TVE_COMP_SER_HPOS;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     write_en2:1;
unsigned int     ser_vstart:5;
unsigned int     write_en1:1;
unsigned int     ser_vend:5;
}TVE_COMP_SER_VPOS;

typedef struct 
{
unsigned int     write_en4:1;
unsigned int     dsync_b_vstart:10;
unsigned int     write_en3:1;
unsigned int     dsync_b_vend:10;
unsigned int     write_en2:1;
unsigned int     dsync_t_vstart:4;
unsigned int     write_en1:1;
unsigned int     dsync_t_vend:4;
}TVE_COMP_DSYNC_VPOS;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     write_en2:1;
unsigned int     hs_start:13;
unsigned int     write_en1:1;
unsigned int     hs_end:13;
}TVE_VGA_HSYNC_HPOS;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     vs_st_posv:11;
unsigned int     write_en1:1;
unsigned int     vs_st_posh:13;
}TVE_VGA_VSYNC_ST_POS;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     vs_end_posv:11;
unsigned int     write_en1:1;
unsigned int     vs_end_posh:13;
}TVE_VGA_VSYNC_END_POS;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     write_en2:1;
unsigned int     ip_vsync_pos1:10;
unsigned int     write_en1:1;
unsigned int     ip_vsync_pos2:10;
}TVE_IP_VSYNCPOS;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     hthr:11;
}TVE_IP_HSYNCPOS;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     write_en4:1;
unsigned int     sync_en:1;
unsigned int     write_en3:1;
unsigned int     ch_sel:1;
unsigned int     write_en2:1;
unsigned int     vpos:11;
unsigned int     write_en1:1;
unsigned int     hpos:13;
}TVE_HDMI_ST;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     write_en2:1;
unsigned int     hs_start:13;
unsigned int     write_en1:1;
unsigned int     hs_end:13;
}TVE_HDMI_DISP_HS;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     vs_st_pos1v:11;
unsigned int     write_en1:1;
unsigned int     vs_st_pos1h:13;
}TVE_HDMI_DISP_VSST1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     vs_end_pos1v:11;
unsigned int     write_en1:1;
unsigned int     vs_end_pos1h:13;
}TVE_HDMI_DISP_VSED1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     vs_st_pos2v:11;
unsigned int     write_en1:1;
unsigned int     vs_st_pos2h:13;
}TVE_HDMI_DISP_VSST2;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     vs_end_pos2v:11;
unsigned int     write_en1:1;
unsigned int     vs_end_pos2h:13;
}TVE_HDMI_DISP_VSED2;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     write_en2:1;
unsigned int     hpos_end:13;
unsigned int     write_en1:1;
unsigned int     hpos_st:13;
}TVE_HDMI_PXLACT;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     write_en3:1;
unsigned int     slewrate:2;
unsigned int     write_en2:1;
unsigned int     y_negsynclvl:12;
unsigned int     write_en1:1;
unsigned int     y_possynclvl:12;
}TVE_COMP_SYNCLVL;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     y_sync_h:12;
unsigned int     write_en1:1;
unsigned int     y_sync_m:12;
}TVE_COMP_SYNC_SLEWLVL;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     y_sync_l:12;
unsigned int     write_en1:1;
unsigned int     bp_lvl:12;
}TVE_COMP_BP_LVL;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     pbpr_negsynclvl:12;
unsigned int     write_en1:1;
unsigned int     pbpr_possynclvl:12;
}TVE_COMP_PBPR_SYNCLVL;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     y_blank_lvl:12;
unsigned int     write_en1:1;
unsigned int     pbpr_blank_lvl:12;
}TVE_COMP_PBPR_BLNKLVL;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     g_up:12;
unsigned int     write_en1:1;
unsigned int     g_dn:12;
}TVE_COMP_G_CLMPLVL;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     rb_up:12;
unsigned int     write_en1:1;
unsigned int     rb_dn:12;
}TVE_COMP_RB_CLMPLVL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     y_black_lvl:8;
}TVE_IP_INPUT;

typedef struct 
{
unsigned int     write_en2:1;
unsigned int     gain:15;
unsigned int     write_en1:1;
unsigned int     offset:15;
}TVE_VBI_COEFF;

typedef struct 
{
unsigned int     write_en2:1;
unsigned int     gain:15;
unsigned int     write_en1:1;
unsigned int     offset:15;
}TVE_BLNK_COEFF;

typedef struct 
{
unsigned int     write_en2:1;
unsigned int     c2:15;
unsigned int     write_en1:1;
unsigned int     c1:15;
}TVE_AV_COEFF1;

typedef struct 
{
unsigned int     write_en2:1;
unsigned int     c3:15;
unsigned int     write_en1:1;
unsigned int     c4:15;
}TVE_AV_COEFF2;

typedef struct 
{
unsigned int     write_en2:1;
unsigned int     c5:15;
unsigned int     write_en1:1;
unsigned int     c6:15;
}TVE_AV_COEFF3;

typedef struct 
{
unsigned int     write_en2:1;
unsigned int     k1:15;
unsigned int     write_en1:1;
unsigned int     k2:15;
}TVE_AV_COEFF4;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_en1:1;
unsigned int     vbi_gain_ebl:1;
unsigned int     write_en2:1;
unsigned int     k3:15;
}TVE_AV_COEFF5;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     mv_rb_ebl:1;
unsigned int     mv_g_ebl:1;
unsigned int     mv_ebl:1;
unsigned int     write_data:1;
}TVE_MV_CTRL;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     write_en2:1;
unsigned int     mv_end_line:6;
unsigned int     write_en1:1;
unsigned int     mv_st_line:6;
}TVE_MV_VPOS;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     write_en4:1;
unsigned int     mv_st_ps:8;
unsigned int     write_en3:1;
unsigned int     mv_ps_len:6;
unsigned int     write_en2:1;
unsigned int     mv_agc_len:6;
unsigned int     write_en1:1;
unsigned int     mv_blnk_len:6;
}TVE_MV_LEN;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     mv_rd:20;
}TVE_MV_RD;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     mv_dn:20;
}TVE_MV_DN;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     mv_ru:20;
}TVE_MV_RU;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     mv_up:20;
}TVE_MV_UP;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     write_en3:1;
unsigned int     mv_ru_dlt:8;
unsigned int     write_en2:1;
unsigned int     mv_rd_dlt:8;
unsigned int     write_en1:1;
unsigned int     mv_stn:12;
}TVE_MV_LVL;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     write_en3:1;
unsigned int     cgms_i_ebl:1;
unsigned int     write_en2:1;
unsigned int     cgms_p_ebl:1;
unsigned int     write_en1:1;
unsigned int     cgms_data:20;
}TVE_CGMS_CTRL;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     cgms_data:20;
}TVE_CGMS_CTRL1;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     write_en2:1;
unsigned int     cgms_i_vpos1:9;
unsigned int     write_en1:1;
unsigned int     cgms_i_vpos2:10;
}TVE_CGMS_I_VPOS;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     write_en2:1;
unsigned int     cgms_p_vpos2:11;
unsigned int     write_en1:1;
unsigned int     cgms_p_vpos1:10;
}TVE_CGMS_P_VPOS;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     write_en2:1;
unsigned int     cgms_i_hst:10;
unsigned int     write_en1:1;
unsigned int     cgms_i_len:10;
}TVE_CGMS_I_HPOS;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     write_en3:1;
unsigned int     cgms_p_lvl:8;
unsigned int     write_en2:1;
unsigned int     cgms_p_hst:10;
unsigned int     write_en1:1;
unsigned int     cgms_p_len:10;
}TVE_CGMS_P_HPOS;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     write_en3:1;
unsigned int     cgms_p_b_ebl:1;
unsigned int     write_en2:1;
unsigned int     cgms_p2_vpos2:11;
unsigned int     write_en1:1;
unsigned int     cgms_p2_vpos1:10;
}TVE_CGMS_P2_VPOS;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     write_en3:1;
unsigned int     cgms_p2_lvl:8;
unsigned int     write_en2:1;
unsigned int     cgms_p2_hst:10;
unsigned int     write_en1:1;
unsigned int     cgms_p2_len:10;
}TVE_CGMS_P2_HPOS;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     cgms_hdr:6;
}TVE_CGMS_B_HDR;

typedef struct 
{
unsigned int     cgms_data:32;
}TVE_CGMS_B_DATA;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     write_en4:1;
unsigned int     wss_ebl:1;
unsigned int     write_en3:1;
unsigned int     wss_intp_sel:1;
unsigned int     write_en2:1;
unsigned int     wss_end_hpos:11;
unsigned int     write_en1:1;
unsigned int     wss_data:14;
}TVE_WSS_CTRL;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     write_en2:1;
unsigned int     wss_h_pos:11;
unsigned int     write_en1:1;
unsigned int     wss_v_pos:10;
}TVE_WSS_POS;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     write_en3:1;
unsigned int     wss_ebl:1;
unsigned int     write_en2:1;
unsigned int     wss_intp_sel:1;
unsigned int     write_en1:1;
unsigned int     wss_data:14;
}TVE_625P_WSS_CTRL;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     write_en2:1;
unsigned int     wss_h_pos:11;
unsigned int     write_en1:1;
unsigned int     wss_v_pos:10;
}TVE_625P_WSS_POS;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     write_en4:1;
unsigned int     tt_h_st:11;
unsigned int     write_en3:1;
unsigned int     tt_line_no:8;
unsigned int     write_en2:1;
unsigned int     tt_intp_sel:1;
unsigned int     write_en1:1;
unsigned int     vbi_tt_ebl:1;
}TVE_TT_CTRL;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     write_en2:1;
unsigned int     tt_b_vst:9;
unsigned int     write_en1:1;
unsigned int     tt_t_vst:5;
}TVE_TT_VPOS;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_en2:1;
unsigned int     start_line2:11;
unsigned int     write_en1:1;
unsigned int     start_line1:11;
}TVE_TT_MASK_VPOS;

typedef struct 
{
unsigned int     tt_line_mask:32;
}TVE_TT_MASK_FLG;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     write_en4:1;
unsigned int     vps_h_pos:11;
unsigned int     write_en3:1;
unsigned int     vps_v_pos:10;
unsigned int     write_en2:1;
unsigned int     vps_intp_sel:1;
unsigned int     write_en1:1;
unsigned int     vbi_vps_ebl:1;
}TVE_VPS_CTRL;

typedef struct 
{
unsigned int     vps_data:32;
}TVE_VPS_DATA;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vps_data:8;
}TVE_VPS_DATA1;

typedef struct 
{
unsigned int     write_en4:1;
unsigned int     dwn_ebl:2;
unsigned int     write_en3:1;
unsigned int     dwn_i_p_sel:1;
unsigned int     write_en2:1;
unsigned int     dwn_st_i:12;
unsigned int     write_en1:1;
unsigned int     dwn_end_i:13;
}TVE_VBI_DWN_CTRL;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     write_en2:1;
unsigned int     dwn_st_p:12;
unsigned int     write_en1:1;
unsigned int     dwn_end_p:13;
}TVE_VBI_DWN_HPOS;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_en2:1;
unsigned int     vbi_start_line2:11;
unsigned int     write_en1:1;
unsigned int     vbi_start_line1:11;
}TVE_VBI_DWN_VPOS_I;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_en2:1;
unsigned int     vbi_start_line2:11;
unsigned int     write_en1:1;
unsigned int     vbi_start_line1:11;
}TVE_VBI_DWN_VPOS_P;

typedef struct 
{
unsigned int     vbi_line_flg:32;
}TVE_VBI_LINE_FLAG_I;

typedef struct 
{
unsigned int     vbi_line_flg:32;
}TVE_VBI_LINE_FLAG_P;

typedef struct 
{
unsigned int     vbi_pty:32;
}TVE_VBI_LINE_PTY_I;

typedef struct 
{
unsigned int     vbi_pty:32;
}TVE_VBI_LINE_PTY_P;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     write_en3:1;
unsigned int     di_i_p_sel:2;
unsigned int     write_en2:1;
unsigned int     hact_start:13;
unsigned int     write_en1:1;
unsigned int     hact_end:13;
}TVE_DIF_HACTIVE;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     cd:1;
unsigned int     di_bus_swap:1;
unsigned int     di_clk_phs:1;
unsigned int     di_fpga_clk_sel:1;
unsigned int     di_vbi_bypass:1;
unsigned int     di_ebl:1;
unsigned int     di_source_sel:1;
unsigned int     di_mod:1;
unsigned int     di_hdr_ebl:1;
unsigned int     write_data:1;
}TVE_DIF_CTRL;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     write_en3:1;
unsigned int     hs_polar:1;
unsigned int     write_en2:1;
unsigned int     hs_start:13;
unsigned int     write_en1:1;
unsigned int     hs_end:13;
}TVE_DIF_HSYNC;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     write_en3:1;
unsigned int     vs_polar:1;
unsigned int     write_en2:1;
unsigned int     vs_st_pos1v:11;
unsigned int     write_en1:1;
unsigned int     vs_st_pos1h:13;
}TVE_DIF_VS_ST_POS1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     vs_end_pos1v:11;
unsigned int     write_en1:1;
unsigned int     vs_end_pos1h:13;
}TVE_DIF_VS_END_POS1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     vs_st_pos2v:11;
unsigned int     write_en1:1;
unsigned int     vs_st_pos2h:13;
}TVE_DIF_VS_ST_POS2;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     vs_end_pos2v:11;
unsigned int     write_en1:1;
unsigned int     vs_end_pos2h:13;
}TVE_DIF_VS_END_POS2;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_en2:1;
unsigned int     v_tgl_hi:11;
unsigned int     write_en1:1;
unsigned int     v_tgl_lo:11;
}TVE_DIF_F_BIT_POS;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_en2:1;
unsigned int     v_tgl1_hi:11;
unsigned int     write_en1:1;
unsigned int     v_tgl1_lo:11;
}TVE_DIF_V_BIT_POS1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_en2:1;
unsigned int     v_tgl2_hi:11;
unsigned int     write_en1:1;
unsigned int     v_tgl2_lo:11;
}TVE_DIF_V_BIT_POS2;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     write_en2:1;
unsigned int     fv_start:13;
unsigned int     write_en1:1;
unsigned int     fv_end:13;
}TVE_DIF_FV_BIT_HPOS;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     phi:8;
}TVE_IP_PHS;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sctoh:8;
}TVE_IP_SCTOH;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     u_invert:1;
unsigned int     v_invert:1;
unsigned int     t_offset_phase:1;
unsigned int     t_reset_fsc:1;
}TVE_IP_F_CTRL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     t_sel_sin:1;
unsigned int     t_fsc_rom:1;
}TVE_IP_T_SEL_SIN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     black_lvl:8;
}TVE_IP_BLCK_LVL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     blank_lvl:8;
}TVE_IP_BLNK_LVL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     clamp_lvl:8;
}TVE_IP_CLAMP_LVL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sync_lvl:8;
}TVE_IP_SYNC_LVL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     y_interp:2;
unsigned int     y_colorbar_en:1;
unsigned int     t_ydel_adj:3;
unsigned int     t_sel_ylpf:1;
unsigned int     t_ygain_val:1;
}TVE_IP_Y_CTRL;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     t_byp_yups:1;
unsigned int     t_sel_ylp:1;
unsigned int     t_ygain_off:1;
unsigned int     y_tsin_cos:1;
unsigned int     y_tsel_dac_tst:1;
unsigned int     y_tdig_out:2;
}TVE_IP_TEST_PARAM;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     y_gain:10;
}TVE_IP_Y_GAIN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sync_lvl_h:8;
}TVE_IP_SYNC_LVL2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sync_lvl_m:8;
}TVE_IP_SYNC_LVL3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sync_lvl_l:8;
}TVE_IP_SYNC_LVL4;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     y_tsel_yuv:1;
unsigned int     t_pd_cvdac:1;
unsigned int     t_pd_ydac:1;
unsigned int     t_pd_cdac:1;
}TVE_IP_O_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     nba:8;
}TVE_IP_NBA;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     pba:8;
}TVE_IP_PBA;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     t_pal_clpf:1;
unsigned int     t_sel_c_gain:1;
}TVE_IP_C_CTRL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     t_byp_cups:1;
unsigned int     t_byp_clpf:1;
unsigned int     t_c_gain_off:1;
}TVE_IP_TEST_T_BYP_CUPS;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     clpf_gain:8;
}TVE_IP_SYNCLPF_GAIN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     t_hsync_phs:1;
unsigned int     t_vsync_phs:1;
unsigned int     y_tsyncmode:3;
unsigned int     y_tencd_mode:3;
}TVE_IP_S_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     clk_phs:2;
unsigned int     t_fsync_enbl:1;
unsigned int     t_fsync_phs:1;
unsigned int     reserved_1:2;
unsigned int     vso:2;
}TVE_IP_VSO0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     vso:8;
}TVE_IP_VSO1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     hso:3;
}TVE_IP_HSO0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hso:8;
}TVE_IP_HSO1;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     hlc:2;
}TVE_IP_HLC0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hlc:8;
}TVE_IP_HLC1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ccd_odd:8;
}TVE_IP_CCD_ODD;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ccd_even:8;
}TVE_IP_CCD_EVEN;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     cc_enbl:2;
}TVE_IP_CCD_ENBL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     hlr:2;
}TVE_IP_TEST_HLR0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hlr:8;
}TVE_IP_TEST_HLR1;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     vsmr:5;
}TVE_IP_TEST_VSMR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     sync_strt:4;
}TVE_IP_SYNC_STRT;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     sync_end:7;
}TVE_IP_SYNC_END;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sync_srend:8;
}TVE_IP_SYNC_SREND;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     sync_eqend:6;
}TVE_IP_SYNC_EQEND;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     actv_strt:8;
}TVE_IP_ACTV_STRT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     actv_end:8;
}TVE_IP_ACTV_END;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     wbrst_strt:7;
}TVE_IP_WBRST_STRT;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     nbrst_strt:7;
}TVE_IP_NBRST_STRT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     nbrst_end:8;
}TVE_IP_NBRST_END;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mvfcr:8;
}TVE_IP_MVFCR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mvcsl1:8;
}TVE_IP_MVCSL1;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     mvcls1:6;
}TVE_IP_MVCLS1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mvcsl2:8;
}TVE_IP_MVCSL2;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     mvcls2:6;
}TVE_IP_MVCLS2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mvcssp:3;
unsigned int     mvcsnum:3;
unsigned int     mvcsln:2;
}TVE_IP_MVCSSP;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     mvpsd:6;
}TVE_IP_MVPSD;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     mvpsl:6;
}TVE_IP_MVPSL;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     mvpss:6;
}TVE_IP_MVPSS;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     mvpsls:7;
}TVE_IP_MVPSLS0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mvpsls:8;
}TVE_IP_MVPSLS1;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     mvpsfs:7;
}TVE_IP_MVPSFS0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mvpsfs:8;
}TVE_IP_MVPSFS1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mvpsagca:8;
}TVE_IP_MVPSAGCA;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mvpsagcb:8;
}TVE_IP_MVPSAGCB;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mveofbpc:8;
}TVE_IP_MVEOFBPC;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mvpbz1:4;
unsigned int     mvpbz2:4;
}TVE_IP_MVPBZ1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mvpbz3:4;
unsigned int     mvpadvbsen:1;
unsigned int     mvpzninvrt:3;
}TVE_IP_MVPBZ3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mvpcslimd_lsb:8;
}TVE_IP_MVPCSLIMD0;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     mvpcslimd_msb:2;
}TVE_IP_MVPCSLIMD1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mvtms:8;
}TVE_IP_MV_CTRL;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     vdac_apow:1;
unsigned int     vdac_bpow:1;
unsigned int     vdac_cpow:1;
unsigned int     powldv_l:1;
unsigned int     stanby_l:1;
unsigned int     reserved_1:2;
unsigned int     biasa_regl:4;
unsigned int     reserved_2:2;
unsigned int     biasb_regl:4;
unsigned int     reserved_3:2;
unsigned int     biasc_regl:4;
}TVE_VIDEO_DAC_CTRL;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     abiq_regl:3;
unsigned int     ldvbias_regl:3;
unsigned int     vcmref_regl:2;
unsigned int     reserved_1:2;
unsigned int     vdac_cf_regl:3;
unsigned int     vdac_rf_regl:2;
}TVE_VIDEO_DAC_CTRL2;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     write_en6:1;
unsigned int     dcc2_l:1;
unsigned int     write_en5:1;
unsigned int     dcc_l:1;
unsigned int     write_en4:1;
unsigned int     caldiv:2;
unsigned int     reserved_1:3;
unsigned int     write_en3:1;
unsigned int     div_regl:2;
unsigned int     write_en2:1;
unsigned int     ckmode_regl:2;
unsigned int     write_en1:1;
unsigned int     calen_regl:2;
}TVE_VIDEO_DAC_CTRL3;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     write_en1:1;
unsigned int     dac0_sel:2;
}TVE_DAC_SEL;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     write_en6:1;
unsigned int     up_ctrl_prog:2;
unsigned int     write_en5:1;
unsigned int     up_ctrl_int0:2;
unsigned int     write_en4:1;
unsigned int     up_ctrl_int1:2;
unsigned int     write_en3:1;
unsigned int     dacmode:2;
unsigned int     write_en2:1;
unsigned int     swap23:1;
unsigned int     write_en1:1;
unsigned int     swap56:1;
}TVE_DAC_MUX;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     write_en3:1;
unsigned int     ygdelay:2;
unsigned int     write_en2:1;
unsigned int     bdelay:2;
unsigned int     write_en1:1;
unsigned int     rdelay:2;
}TVE_CMP_DLY;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en4:1;
unsigned int     out_control123:3;
unsigned int     write_en3:1;
unsigned int     neg_out:6;
unsigned int     write_en2:1;
unsigned int     out_control:1;
unsigned int     write_en1:1;
unsigned int     dac_value:10;
unsigned int     reserved_1:2;
}TVE_DAC_MISC;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     dac_value3:10;
unsigned int     dac_value2:10;
unsigned int     dac_value1:10;
}TVE_DAC_MISC1;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     write_en3:1;
unsigned int     sel1:4;
unsigned int     write_en2:1;
unsigned int     sel0:4;
unsigned int     write_en1:1;
unsigned int     enable:1;
}TVE_DBG;

typedef struct 
{
unsigned int     dummy:32;
}TVE_DUMMY;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     aio_dac_en:1;
unsigned int     dac1_en:1;
unsigned int     dac0_en:1;
}TVE_DAC_TEST;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     int_vpos:11;
unsigned int     write_en1:1;
unsigned int     int_hpos:13;
}TVE_INTVBI_I;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     int_vpos:11;
unsigned int     write_en1:1;
unsigned int     int_hpos:13;
}TVE_INTVBI_P1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     int_vpos:11;
unsigned int     write_en1:1;
unsigned int     int_hpos:13;
}TVE_INTVBI_P2;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     int_vpos:11;
unsigned int     write_en1:1;
unsigned int     int_hpos:13;
}TVE_INTVBI_H1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     int_vpos:11;
unsigned int     write_en1:1;
unsigned int     int_hpos:13;
}TVE_INTVBI_H2;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     c1:14;
unsigned int     reserved_1:2;
unsigned int     c0:14;
}TVE_DAC1_FIR_1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     c3:14;
unsigned int     reserved_1:2;
unsigned int     c2:14;
}TVE_DAC1_FIR_2;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     c1:14;
unsigned int     reserved_1:2;
unsigned int     c0:14;
}TVE_DAC2_FIR_1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     c3:14;
unsigned int     reserved_1:2;
unsigned int     c2:14;
}TVE_DAC2_FIR_2;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     c1:14;
unsigned int     reserved_1:2;
unsigned int     c0:14;
}TVE_DAC3_FIR_1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     c3:14;
unsigned int     reserved_1:2;
unsigned int     c2:14;
}TVE_DAC3_FIR_2;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     c1:14;
unsigned int     reserved_1:2;
unsigned int     c0:14;
}TVE_DAC4_FIR_1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     c3:14;
unsigned int     reserved_1:2;
unsigned int     c2:14;
}TVE_DAC4_FIR_2;

typedef struct 
{
unsigned int     reg_vdac_dac_en:1;
unsigned int     reg_vdac_powmbias:1;
unsigned int     reg_vdac_mbias_envr:1;
unsigned int     reg_vdac_mbias_vr15sel:2;
unsigned int     reg_vdac_bg_rbg2:2;
unsigned int     reg_vdac_bg_envbgup:1;
unsigned int     reg_vdac_bg_rbg:3;
unsigned int     reg_vdac_dac_vref_adj:2;
unsigned int     reg_vdac_dac_res75_setup:5;
unsigned int     reg_vdac_dac_clkedge:1;
unsigned int     reg_vdac_dac_cur:4;
unsigned int     reg_vdac_dac_cal75_en:1;
unsigned int     reg_vdac_dac_draw_en:1;
unsigned int     reg_vdac_dac_plugin_en:1;
unsigned int     reg_vdac_dac_res75_en:1;
unsigned int     reg_vdac_dac_res75_sel:1;
unsigned int     reserved_0:4;
}TVE_VDAC_CTR1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     reg_vdac_bg_auto_en:1;
unsigned int     reg_vdac_dac_rescal:5;
unsigned int     reg_vdac_dac_plugin:1;
unsigned int     reg_vdac_dac_drawout:1;
}TVE_VDAC_CTR2;

#endif

#define TVE_SYNCGEN_RST                                                              0x18018000
#define TVE_SYNCGEN_RST_reg_addr                                                     "0xB8018000"
#define TVE_SYNCGEN_RST_reg                                                          0xB8018000
#define set_TVE_SYNCGEN_RST_reg(data)   (*((volatile unsigned int*) TVE_SYNCGEN_RST_reg)=data)
#define get_TVE_SYNCGEN_RST_reg   (*((volatile unsigned int*) TVE_SYNCGEN_RST_reg))
#define TVE_SYNCGEN_RST_inst_adr                                                     "0x0000"
#define TVE_SYNCGEN_RST_inst                                                         0x0000
#define TVE_SYNCGEN_RST_write_en6_shift                                              (11)
#define TVE_SYNCGEN_RST_write_en6_mask                                               (0x00000800)
#define TVE_SYNCGEN_RST_write_en6(data)                                              (0x00000800&((data)<<11))
#define TVE_SYNCGEN_RST_write_en6_src(data)                                          ((0x00000800&(data))>>11)
#define TVE_SYNCGEN_RST_get_write_en6(data)                                          ((0x00000800&(data))>>11)
#define TVE_SYNCGEN_RST_ph_sync_go_shift                                             (10)
#define TVE_SYNCGEN_RST_ph_sync_go_mask                                              (0x00000400)
#define TVE_SYNCGEN_RST_ph_sync_go(data)                                             (0x00000400&((data)<<10))
#define TVE_SYNCGEN_RST_ph_sync_go_src(data)                                         ((0x00000400&(data))>>10)
#define TVE_SYNCGEN_RST_get_ph_sync_go(data)                                         ((0x00000400&(data))>>10)
#define TVE_SYNCGEN_RST_write_en5_shift                                              (9)
#define TVE_SYNCGEN_RST_write_en5_mask                                               (0x00000200)
#define TVE_SYNCGEN_RST_write_en5(data)                                              (0x00000200&((data)<<9))
#define TVE_SYNCGEN_RST_write_en5_src(data)                                          ((0x00000200&(data))>>9)
#define TVE_SYNCGEN_RST_get_write_en5(data)                                          ((0x00000200&(data))>>9)
#define TVE_SYNCGEN_RST_hi_sync_go_shift                                             (8)
#define TVE_SYNCGEN_RST_hi_sync_go_mask                                              (0x00000100)
#define TVE_SYNCGEN_RST_hi_sync_go(data)                                             (0x00000100&((data)<<8))
#define TVE_SYNCGEN_RST_hi_sync_go_src(data)                                         ((0x00000100&(data))>>8)
#define TVE_SYNCGEN_RST_get_hi_sync_go(data)                                         ((0x00000100&(data))>>8)
#define TVE_SYNCGEN_RST_write_en4_shift                                              (7)
#define TVE_SYNCGEN_RST_write_en4_mask                                               (0x00000080)
#define TVE_SYNCGEN_RST_write_en4(data)                                              (0x00000080&((data)<<7))
#define TVE_SYNCGEN_RST_write_en4_src(data)                                          ((0x00000080&(data))>>7)
#define TVE_SYNCGEN_RST_get_write_en4(data)                                          ((0x00000080&(data))>>7)
#define TVE_SYNCGEN_RST_pi_sync_go_shift                                             (6)
#define TVE_SYNCGEN_RST_pi_sync_go_mask                                              (0x00000040)
#define TVE_SYNCGEN_RST_pi_sync_go(data)                                             (0x00000040&((data)<<6))
#define TVE_SYNCGEN_RST_pi_sync_go_src(data)                                         ((0x00000040&(data))>>6)
#define TVE_SYNCGEN_RST_get_pi_sync_go(data)                                         ((0x00000040&(data))>>6)
#define TVE_SYNCGEN_RST_write_en3_shift                                              (5)
#define TVE_SYNCGEN_RST_write_en3_mask                                               (0x00000020)
#define TVE_SYNCGEN_RST_write_en3(data)                                              (0x00000020&((data)<<5))
#define TVE_SYNCGEN_RST_write_en3_src(data)                                          ((0x00000020&(data))>>5)
#define TVE_SYNCGEN_RST_get_write_en3(data)                                          ((0x00000020&(data))>>5)
#define TVE_SYNCGEN_RST_i_sync_go_shift                                              (4)
#define TVE_SYNCGEN_RST_i_sync_go_mask                                               (0x00000010)
#define TVE_SYNCGEN_RST_i_sync_go(data)                                              (0x00000010&((data)<<4))
#define TVE_SYNCGEN_RST_i_sync_go_src(data)                                          ((0x00000010&(data))>>4)
#define TVE_SYNCGEN_RST_get_i_sync_go(data)                                          ((0x00000010&(data))>>4)
#define TVE_SYNCGEN_RST_write_en2_shift                                              (3)
#define TVE_SYNCGEN_RST_write_en2_mask                                               (0x00000008)
#define TVE_SYNCGEN_RST_write_en2(data)                                              (0x00000008&((data)<<3))
#define TVE_SYNCGEN_RST_write_en2_src(data)                                          ((0x00000008&(data))>>3)
#define TVE_SYNCGEN_RST_get_write_en2(data)                                          ((0x00000008&(data))>>3)
#define TVE_SYNCGEN_RST_p_sync_go_shift                                              (2)
#define TVE_SYNCGEN_RST_p_sync_go_mask                                               (0x00000004)
#define TVE_SYNCGEN_RST_p_sync_go(data)                                              (0x00000004&((data)<<2))
#define TVE_SYNCGEN_RST_p_sync_go_src(data)                                          ((0x00000004&(data))>>2)
#define TVE_SYNCGEN_RST_get_p_sync_go(data)                                          ((0x00000004&(data))>>2)
#define TVE_SYNCGEN_RST_write_en1_shift                                              (1)
#define TVE_SYNCGEN_RST_write_en1_mask                                               (0x00000002)
#define TVE_SYNCGEN_RST_write_en1(data)                                              (0x00000002&((data)<<1))
#define TVE_SYNCGEN_RST_write_en1_src(data)                                          ((0x00000002&(data))>>1)
#define TVE_SYNCGEN_RST_get_write_en1(data)                                          ((0x00000002&(data))>>1)
#define TVE_SYNCGEN_RST_h_sync_go_shift                                              (0)
#define TVE_SYNCGEN_RST_h_sync_go_mask                                               (0x00000001)
#define TVE_SYNCGEN_RST_h_sync_go(data)                                              (0x00000001&((data)<<0))
#define TVE_SYNCGEN_RST_h_sync_go_src(data)                                          ((0x00000001&(data))>>0)
#define TVE_SYNCGEN_RST_get_h_sync_go(data)                                          ((0x00000001&(data))>>0)


#define TVE_SYNCGEN_I                                                                0x18018004
#define TVE_SYNCGEN_I_reg_addr                                                       "0xB8018004"
#define TVE_SYNCGEN_I_reg                                                            0xB8018004
#define set_TVE_SYNCGEN_I_reg(data)   (*((volatile unsigned int*) TVE_SYNCGEN_I_reg)=data)
#define get_TVE_SYNCGEN_I_reg   (*((volatile unsigned int*) TVE_SYNCGEN_I_reg))
#define TVE_SYNCGEN_I_inst_adr                                                       "0x0001"
#define TVE_SYNCGEN_I_inst                                                           0x0001
#define TVE_SYNCGEN_I_write_en2_shift                                                (25)
#define TVE_SYNCGEN_I_write_en2_mask                                                 (0x02000000)
#define TVE_SYNCGEN_I_write_en2(data)                                                (0x02000000&((data)<<25))
#define TVE_SYNCGEN_I_write_en2_src(data)                                            ((0x02000000&(data))>>25)
#define TVE_SYNCGEN_I_get_write_en2(data)                                            ((0x02000000&(data))>>25)
#define TVE_SYNCGEN_I_v_thr_shift                                                    (14)
#define TVE_SYNCGEN_I_v_thr_mask                                                     (0x01FFC000)
#define TVE_SYNCGEN_I_v_thr(data)                                                    (0x01FFC000&((data)<<14))
#define TVE_SYNCGEN_I_v_thr_src(data)                                                ((0x01FFC000&(data))>>14)
#define TVE_SYNCGEN_I_get_v_thr(data)                                                ((0x01FFC000&(data))>>14)
#define TVE_SYNCGEN_I_write_en1_shift                                                (13)
#define TVE_SYNCGEN_I_write_en1_mask                                                 (0x00002000)
#define TVE_SYNCGEN_I_write_en1(data)                                                (0x00002000&((data)<<13))
#define TVE_SYNCGEN_I_write_en1_src(data)                                            ((0x00002000&(data))>>13)
#define TVE_SYNCGEN_I_get_write_en1(data)                                            ((0x00002000&(data))>>13)
#define TVE_SYNCGEN_I_h_thr_shift                                                    (0)
#define TVE_SYNCGEN_I_h_thr_mask                                                     (0x00001FFF)
#define TVE_SYNCGEN_I_h_thr(data)                                                    (0x00001FFF&((data)<<0))
#define TVE_SYNCGEN_I_h_thr_src(data)                                                ((0x00001FFF&(data))>>0)
#define TVE_SYNCGEN_I_get_h_thr(data)                                                ((0x00001FFF&(data))>>0)


#define TVE_SYNCGEN_P                                                                0x18018008
#define TVE_SYNCGEN_P_reg_addr                                                       "0xB8018008"
#define TVE_SYNCGEN_P_reg                                                            0xB8018008
#define set_TVE_SYNCGEN_P_reg(data)   (*((volatile unsigned int*) TVE_SYNCGEN_P_reg)=data)
#define get_TVE_SYNCGEN_P_reg   (*((volatile unsigned int*) TVE_SYNCGEN_P_reg))
#define TVE_SYNCGEN_P_inst_adr                                                       "0x0002"
#define TVE_SYNCGEN_P_inst                                                           0x0002
#define TVE_SYNCGEN_P_write_en3_shift                                                (27)
#define TVE_SYNCGEN_P_write_en3_mask                                                 (0x08000000)
#define TVE_SYNCGEN_P_write_en3(data)                                                (0x08000000&((data)<<27))
#define TVE_SYNCGEN_P_write_en3_src(data)                                            ((0x08000000&(data))>>27)
#define TVE_SYNCGEN_P_get_write_en3(data)                                            ((0x08000000&(data))>>27)
#define TVE_SYNCGEN_P_i_p_sel_shift                                                  (26)
#define TVE_SYNCGEN_P_i_p_sel_mask                                                   (0x04000000)
#define TVE_SYNCGEN_P_i_p_sel(data)                                                  (0x04000000&((data)<<26))
#define TVE_SYNCGEN_P_i_p_sel_src(data)                                              ((0x04000000&(data))>>26)
#define TVE_SYNCGEN_P_get_i_p_sel(data)                                              ((0x04000000&(data))>>26)
#define TVE_SYNCGEN_P_write_en2_shift                                                (25)
#define TVE_SYNCGEN_P_write_en2_mask                                                 (0x02000000)
#define TVE_SYNCGEN_P_write_en2(data)                                                (0x02000000&((data)<<25))
#define TVE_SYNCGEN_P_write_en2_src(data)                                            ((0x02000000&(data))>>25)
#define TVE_SYNCGEN_P_get_write_en2(data)                                            ((0x02000000&(data))>>25)
#define TVE_SYNCGEN_P_v_thr_shift                                                    (14)
#define TVE_SYNCGEN_P_v_thr_mask                                                     (0x01FFC000)
#define TVE_SYNCGEN_P_v_thr(data)                                                    (0x01FFC000&((data)<<14))
#define TVE_SYNCGEN_P_v_thr_src(data)                                                ((0x01FFC000&(data))>>14)
#define TVE_SYNCGEN_P_get_v_thr(data)                                                ((0x01FFC000&(data))>>14)
#define TVE_SYNCGEN_P_write_en1_shift                                                (13)
#define TVE_SYNCGEN_P_write_en1_mask                                                 (0x00002000)
#define TVE_SYNCGEN_P_write_en1(data)                                                (0x00002000&((data)<<13))
#define TVE_SYNCGEN_P_write_en1_src(data)                                            ((0x00002000&(data))>>13)
#define TVE_SYNCGEN_P_get_write_en1(data)                                            ((0x00002000&(data))>>13)
#define TVE_SYNCGEN_P_h_thr_shift                                                    (0)
#define TVE_SYNCGEN_P_h_thr_mask                                                     (0x00001FFF)
#define TVE_SYNCGEN_P_h_thr(data)                                                    (0x00001FFF&((data)<<0))
#define TVE_SYNCGEN_P_h_thr_src(data)                                                ((0x00001FFF&(data))>>0)
#define TVE_SYNCGEN_P_get_h_thr(data)                                                ((0x00001FFF&(data))>>0)


#define TVE_SYNCGEN_HDMI                                                             0x1801800c
#define TVE_SYNCGEN_HDMI_reg_addr                                                    "0xB801800C"
#define TVE_SYNCGEN_HDMI_reg                                                         0xB801800C
#define set_TVE_SYNCGEN_HDMI_reg(data)   (*((volatile unsigned int*) TVE_SYNCGEN_HDMI_reg)=data)
#define get_TVE_SYNCGEN_HDMI_reg   (*((volatile unsigned int*) TVE_SYNCGEN_HDMI_reg))
#define TVE_SYNCGEN_HDMI_inst_adr                                                    "0x0003"
#define TVE_SYNCGEN_HDMI_inst                                                        0x0003
#define TVE_SYNCGEN_HDMI_write_en4_shift                                             (29)
#define TVE_SYNCGEN_HDMI_write_en4_mask                                              (0x20000000)
#define TVE_SYNCGEN_HDMI_write_en4(data)                                             (0x20000000&((data)<<29))
#define TVE_SYNCGEN_HDMI_write_en4_src(data)                                         ((0x20000000&(data))>>29)
#define TVE_SYNCGEN_HDMI_get_write_en4(data)                                         ((0x20000000&(data))>>29)
#define TVE_SYNCGEN_HDMI_mode_1080i_shift                                            (28)
#define TVE_SYNCGEN_HDMI_mode_1080i_mask                                             (0x10000000)
#define TVE_SYNCGEN_HDMI_mode_1080i(data)                                            (0x10000000&((data)<<28))
#define TVE_SYNCGEN_HDMI_mode_1080i_src(data)                                        ((0x10000000&(data))>>28)
#define TVE_SYNCGEN_HDMI_get_mode_1080i(data)                                        ((0x10000000&(data))>>28)
#define TVE_SYNCGEN_HDMI_write_en3_shift                                             (27)
#define TVE_SYNCGEN_HDMI_write_en3_mask                                              (0x08000000)
#define TVE_SYNCGEN_HDMI_write_en3(data)                                             (0x08000000&((data)<<27))
#define TVE_SYNCGEN_HDMI_write_en3_src(data)                                         ((0x08000000&(data))>>27)
#define TVE_SYNCGEN_HDMI_get_write_en3(data)                                         ((0x08000000&(data))>>27)
#define TVE_SYNCGEN_HDMI_i_p_sel_shift                                               (26)
#define TVE_SYNCGEN_HDMI_i_p_sel_mask                                                (0x04000000)
#define TVE_SYNCGEN_HDMI_i_p_sel(data)                                               (0x04000000&((data)<<26))
#define TVE_SYNCGEN_HDMI_i_p_sel_src(data)                                           ((0x04000000&(data))>>26)
#define TVE_SYNCGEN_HDMI_get_i_p_sel(data)                                           ((0x04000000&(data))>>26)
#define TVE_SYNCGEN_HDMI_write_en2_shift                                             (25)
#define TVE_SYNCGEN_HDMI_write_en2_mask                                              (0x02000000)
#define TVE_SYNCGEN_HDMI_write_en2(data)                                             (0x02000000&((data)<<25))
#define TVE_SYNCGEN_HDMI_write_en2_src(data)                                         ((0x02000000&(data))>>25)
#define TVE_SYNCGEN_HDMI_get_write_en2(data)                                         ((0x02000000&(data))>>25)
#define TVE_SYNCGEN_HDMI_v_thr_shift                                                 (14)
#define TVE_SYNCGEN_HDMI_v_thr_mask                                                  (0x01FFC000)
#define TVE_SYNCGEN_HDMI_v_thr(data)                                                 (0x01FFC000&((data)<<14))
#define TVE_SYNCGEN_HDMI_v_thr_src(data)                                             ((0x01FFC000&(data))>>14)
#define TVE_SYNCGEN_HDMI_get_v_thr(data)                                             ((0x01FFC000&(data))>>14)
#define TVE_SYNCGEN_HDMI_write_en1_shift                                             (13)
#define TVE_SYNCGEN_HDMI_write_en1_mask                                              (0x00002000)
#define TVE_SYNCGEN_HDMI_write_en1(data)                                             (0x00002000&((data)<<13))
#define TVE_SYNCGEN_HDMI_write_en1_src(data)                                         ((0x00002000&(data))>>13)
#define TVE_SYNCGEN_HDMI_get_write_en1(data)                                         ((0x00002000&(data))>>13)
#define TVE_SYNCGEN_HDMI_h_thr_shift                                                 (0)
#define TVE_SYNCGEN_HDMI_h_thr_mask                                                  (0x00001FFF)
#define TVE_SYNCGEN_HDMI_h_thr(data)                                                 (0x00001FFF&((data)<<0))
#define TVE_SYNCGEN_HDMI_h_thr_src(data)                                             ((0x00001FFF&(data))>>0)
#define TVE_SYNCGEN_HDMI_get_h_thr(data)                                             ((0x00001FFF&(data))>>0)


#define TVE_COMP_CTRL                                                                0x18018010
#define TVE_COMP_CTRL_reg_addr                                                       "0xB8018010"
#define TVE_COMP_CTRL_reg                                                            0xB8018010
#define set_TVE_COMP_CTRL_reg(data)   (*((volatile unsigned int*) TVE_COMP_CTRL_reg)=data)
#define get_TVE_COMP_CTRL_reg   (*((volatile unsigned int*) TVE_COMP_CTRL_reg))
#define TVE_COMP_CTRL_inst_adr                                                       "0x0004"
#define TVE_COMP_CTRL_inst                                                           0x0004
#define TVE_COMP_CTRL_comp_ebl_shift                                                 (13)
#define TVE_COMP_CTRL_comp_ebl_mask                                                  (0x00002000)
#define TVE_COMP_CTRL_comp_ebl(data)                                                 (0x00002000&((data)<<13))
#define TVE_COMP_CTRL_comp_ebl_src(data)                                             ((0x00002000&(data))>>13)
#define TVE_COMP_CTRL_get_comp_ebl(data)                                             ((0x00002000&(data))>>13)
#define TVE_COMP_CTRL_sdtv_ebl_shift                                                 (12)
#define TVE_COMP_CTRL_sdtv_ebl_mask                                                  (0x00001000)
#define TVE_COMP_CTRL_sdtv_ebl(data)                                                 (0x00001000&((data)<<12))
#define TVE_COMP_CTRL_sdtv_ebl_src(data)                                             ((0x00001000&(data))>>12)
#define TVE_COMP_CTRL_get_sdtv_ebl(data)                                             ((0x00001000&(data))>>12)
#define TVE_COMP_CTRL_vs_polar_shift                                                 (11)
#define TVE_COMP_CTRL_vs_polar_mask                                                  (0x00000800)
#define TVE_COMP_CTRL_vs_polar(data)                                                 (0x00000800&((data)<<11))
#define TVE_COMP_CTRL_vs_polar_src(data)                                             ((0x00000800&(data))>>11)
#define TVE_COMP_CTRL_get_vs_polar(data)                                             ((0x00000800&(data))>>11)
#define TVE_COMP_CTRL_hs_polar_shift                                                 (10)
#define TVE_COMP_CTRL_hs_polar_mask                                                  (0x00000400)
#define TVE_COMP_CTRL_hs_polar(data)                                                 (0x00000400&((data)<<10))
#define TVE_COMP_CTRL_hs_polar_src(data)                                             ((0x00000400&(data))>>10)
#define TVE_COMP_CTRL_get_hs_polar(data)                                             ((0x00000400&(data))>>10)
#define TVE_COMP_CTRL_vga_hvsync_shift                                               (9)
#define TVE_COMP_CTRL_vga_hvsync_mask                                                (0x00000200)
#define TVE_COMP_CTRL_vga_hvsync(data)                                               (0x00000200&((data)<<9))
#define TVE_COMP_CTRL_vga_hvsync_src(data)                                           ((0x00000200&(data))>>9)
#define TVE_COMP_CTRL_get_vga_hvsync(data)                                           ((0x00000200&(data))>>9)
#define TVE_COMP_CTRL_comp_sel_shift                                                 (8)
#define TVE_COMP_CTRL_comp_sel_mask                                                  (0x00000100)
#define TVE_COMP_CTRL_comp_sel(data)                                                 (0x00000100&((data)<<8))
#define TVE_COMP_CTRL_comp_sel_src(data)                                             ((0x00000100&(data))>>8)
#define TVE_COMP_CTRL_get_comp_sel(data)                                             ((0x00000100&(data))>>8)
#define TVE_COMP_CTRL_sync_rb_ebl_shift                                              (7)
#define TVE_COMP_CTRL_sync_rb_ebl_mask                                               (0x00000080)
#define TVE_COMP_CTRL_sync_rb_ebl(data)                                              (0x00000080&((data)<<7))
#define TVE_COMP_CTRL_sync_rb_ebl_src(data)                                          ((0x00000080&(data))>>7)
#define TVE_COMP_CTRL_get_sync_rb_ebl(data)                                          ((0x00000080&(data))>>7)
#define TVE_COMP_CTRL_sync_g_ebl_shift                                               (6)
#define TVE_COMP_CTRL_sync_g_ebl_mask                                                (0x00000040)
#define TVE_COMP_CTRL_sync_g_ebl(data)                                               (0x00000040&((data)<<6))
#define TVE_COMP_CTRL_sync_g_ebl_src(data)                                           ((0x00000040&(data))>>6)
#define TVE_COMP_CTRL_get_sync_g_ebl(data)                                           ((0x00000040&(data))>>6)
#define TVE_COMP_CTRL_rgb_mod_shift                                                  (5)
#define TVE_COMP_CTRL_rgb_mod_mask                                                   (0x00000020)
#define TVE_COMP_CTRL_rgb_mod(data)                                                  (0x00000020&((data)<<5))
#define TVE_COMP_CTRL_rgb_mod_src(data)                                              ((0x00000020&(data))>>5)
#define TVE_COMP_CTRL_get_rgb_mod(data)                                              ((0x00000020&(data))>>5)
#define TVE_COMP_CTRL_vbi_rb_ebl_shift                                               (4)
#define TVE_COMP_CTRL_vbi_rb_ebl_mask                                                (0x00000010)
#define TVE_COMP_CTRL_vbi_rb_ebl(data)                                               (0x00000010&((data)<<4))
#define TVE_COMP_CTRL_vbi_rb_ebl_src(data)                                           ((0x00000010&(data))>>4)
#define TVE_COMP_CTRL_get_vbi_rb_ebl(data)                                           ((0x00000010&(data))>>4)
#define TVE_COMP_CTRL_vbi_g_ebl_shift                                                (3)
#define TVE_COMP_CTRL_vbi_g_ebl_mask                                                 (0x00000008)
#define TVE_COMP_CTRL_vbi_g_ebl(data)                                                (0x00000008&((data)<<3))
#define TVE_COMP_CTRL_vbi_g_ebl_src(data)                                            ((0x00000008&(data))>>3)
#define TVE_COMP_CTRL_get_vbi_g_ebl(data)                                            ((0x00000008&(data))>>3)
#define TVE_COMP_CTRL_hdsync_shift                                                   (2)
#define TVE_COMP_CTRL_hdsync_mask                                                    (0x00000004)
#define TVE_COMP_CTRL_hdsync(data)                                                   (0x00000004&((data)<<2))
#define TVE_COMP_CTRL_hdsync_src(data)                                               ((0x00000004&(data))>>2)
#define TVE_COMP_CTRL_get_hdsync(data)                                               ((0x00000004&(data))>>2)
#define TVE_COMP_CTRL_syncmod_sel_shift                                              (1)
#define TVE_COMP_CTRL_syncmod_sel_mask                                               (0x00000002)
#define TVE_COMP_CTRL_syncmod_sel(data)                                              (0x00000002&((data)<<1))
#define TVE_COMP_CTRL_syncmod_sel_src(data)                                          ((0x00000002&(data))>>1)
#define TVE_COMP_CTRL_get_syncmod_sel(data)                                          ((0x00000002&(data))>>1)
#define TVE_COMP_CTRL_write_data_shift                                               (0)
#define TVE_COMP_CTRL_write_data_mask                                                (0x00000001)
#define TVE_COMP_CTRL_write_data(data)                                               (0x00000001&((data)<<0))
#define TVE_COMP_CTRL_write_data_src(data)                                           ((0x00000001&(data))>>0)
#define TVE_COMP_CTRL_get_write_data(data)                                           ((0x00000001&(data))>>0)


#define TVE_SYNCGEN_STATUS_I                                                         0x18018014
#define TVE_SYNCGEN_STATUS_I_reg_addr                                                "0xB8018014"
#define TVE_SYNCGEN_STATUS_I_reg                                                     0xB8018014
#define set_TVE_SYNCGEN_STATUS_I_reg(data)   (*((volatile unsigned int*) TVE_SYNCGEN_STATUS_I_reg)=data)
#define get_TVE_SYNCGEN_STATUS_I_reg   (*((volatile unsigned int*) TVE_SYNCGEN_STATUS_I_reg))
#define TVE_SYNCGEN_STATUS_I_inst_adr                                                "0x0005"
#define TVE_SYNCGEN_STATUS_I_inst                                                    0x0005
#define TVE_SYNCGEN_STATUS_I_i_field_shift                                           (23)
#define TVE_SYNCGEN_STATUS_I_i_field_mask                                            (0x00800000)
#define TVE_SYNCGEN_STATUS_I_i_field(data)                                           (0x00800000&((data)<<23))
#define TVE_SYNCGEN_STATUS_I_i_field_src(data)                                       ((0x00800000&(data))>>23)
#define TVE_SYNCGEN_STATUS_I_get_i_field(data)                                       ((0x00800000&(data))>>23)
#define TVE_SYNCGEN_STATUS_I_i_vcnt_shift                                            (12)
#define TVE_SYNCGEN_STATUS_I_i_vcnt_mask                                             (0x007FF000)
#define TVE_SYNCGEN_STATUS_I_i_vcnt(data)                                            (0x007FF000&((data)<<12))
#define TVE_SYNCGEN_STATUS_I_i_vcnt_src(data)                                        ((0x007FF000&(data))>>12)
#define TVE_SYNCGEN_STATUS_I_get_i_vcnt(data)                                        ((0x007FF000&(data))>>12)
#define TVE_SYNCGEN_STATUS_I_p_field_shift                                           (11)
#define TVE_SYNCGEN_STATUS_I_p_field_mask                                            (0x00000800)
#define TVE_SYNCGEN_STATUS_I_p_field(data)                                           (0x00000800&((data)<<11))
#define TVE_SYNCGEN_STATUS_I_p_field_src(data)                                       ((0x00000800&(data))>>11)
#define TVE_SYNCGEN_STATUS_I_get_p_field(data)                                       ((0x00000800&(data))>>11)
#define TVE_SYNCGEN_STATUS_I_p_vcnt_shift                                            (0)
#define TVE_SYNCGEN_STATUS_I_p_vcnt_mask                                             (0x000007FF)
#define TVE_SYNCGEN_STATUS_I_p_vcnt(data)                                            (0x000007FF&((data)<<0))
#define TVE_SYNCGEN_STATUS_I_p_vcnt_src(data)                                        ((0x000007FF&(data))>>0)
#define TVE_SYNCGEN_STATUS_I_get_p_vcnt(data)                                        ((0x000007FF&(data))>>0)


#define TVE_SYNCGEN_STATUS_H                                                         0x18018018
#define TVE_SYNCGEN_STATUS_H_reg_addr                                                "0xB8018018"
#define TVE_SYNCGEN_STATUS_H_reg                                                     0xB8018018
#define set_TVE_SYNCGEN_STATUS_H_reg(data)   (*((volatile unsigned int*) TVE_SYNCGEN_STATUS_H_reg)=data)
#define get_TVE_SYNCGEN_STATUS_H_reg   (*((volatile unsigned int*) TVE_SYNCGEN_STATUS_H_reg))
#define TVE_SYNCGEN_STATUS_H_inst_adr                                                "0x0006"
#define TVE_SYNCGEN_STATUS_H_inst                                                    0x0006
#define TVE_SYNCGEN_STATUS_H_h_field_shift                                           (11)
#define TVE_SYNCGEN_STATUS_H_h_field_mask                                            (0x00000800)
#define TVE_SYNCGEN_STATUS_H_h_field(data)                                           (0x00000800&((data)<<11))
#define TVE_SYNCGEN_STATUS_H_h_field_src(data)                                       ((0x00000800&(data))>>11)
#define TVE_SYNCGEN_STATUS_H_get_h_field(data)                                       ((0x00000800&(data))>>11)
#define TVE_SYNCGEN_STATUS_H_h_vcnt_shift                                            (0)
#define TVE_SYNCGEN_STATUS_H_h_vcnt_mask                                             (0x000007FF)
#define TVE_SYNCGEN_STATUS_H_h_vcnt(data)                                            (0x000007FF&((data)<<0))
#define TVE_SYNCGEN_STATUS_H_h_vcnt_src(data)                                        ((0x000007FF&(data))>>0)
#define TVE_SYNCGEN_STATUS_H_get_h_vcnt(data)                                        ((0x000007FF&(data))>>0)


#define TVE_INTEN                                                                    0x1801801c
#define TVE_INTEN_reg_addr                                                           "0xB801801C"
#define TVE_INTEN_reg                                                                0xB801801C
#define set_TVE_INTEN_reg(data)   (*((volatile unsigned int*) TVE_INTEN_reg)=data)
#define get_TVE_INTEN_reg   (*((volatile unsigned int*) TVE_INTEN_reg))
#define TVE_INTEN_inst_adr                                                           "0x0007"
#define TVE_INTEN_inst                                                               0x0007
#define TVE_INTEN_inten_vbi_h_shift                                                  (6)
#define TVE_INTEN_inten_vbi_h_mask                                                   (0x00000040)
#define TVE_INTEN_inten_vbi_h(data)                                                  (0x00000040&((data)<<6))
#define TVE_INTEN_inten_vbi_h_src(data)                                              ((0x00000040&(data))>>6)
#define TVE_INTEN_get_inten_vbi_h(data)                                              ((0x00000040&(data))>>6)
#define TVE_INTEN_inten_vbi_i_shift                                                  (5)
#define TVE_INTEN_inten_vbi_i_mask                                                   (0x00000020)
#define TVE_INTEN_inten_vbi_i(data)                                                  (0x00000020&((data)<<5))
#define TVE_INTEN_inten_vbi_i_src(data)                                              ((0x00000020&(data))>>5)
#define TVE_INTEN_get_inten_vbi_i(data)                                              ((0x00000020&(data))>>5)
#define TVE_INTEN_inten_vbi_p_shift                                                  (4)
#define TVE_INTEN_inten_vbi_p_mask                                                   (0x00000010)
#define TVE_INTEN_inten_vbi_p(data)                                                  (0x00000010&((data)<<4))
#define TVE_INTEN_inten_vbi_p_src(data)                                              ((0x00000010&(data))>>4)
#define TVE_INTEN_get_inten_vbi_p(data)                                              ((0x00000010&(data))>>4)
#define TVE_INTEN_inten_h_shift                                                      (3)
#define TVE_INTEN_inten_h_mask                                                       (0x00000008)
#define TVE_INTEN_inten_h(data)                                                      (0x00000008&((data)<<3))
#define TVE_INTEN_inten_h_src(data)                                                  ((0x00000008&(data))>>3)
#define TVE_INTEN_get_inten_h(data)                                                  ((0x00000008&(data))>>3)
#define TVE_INTEN_inten_i_shift                                                      (2)
#define TVE_INTEN_inten_i_mask                                                       (0x00000004)
#define TVE_INTEN_inten_i(data)                                                      (0x00000004&((data)<<2))
#define TVE_INTEN_inten_i_src(data)                                                  ((0x00000004&(data))>>2)
#define TVE_INTEN_get_inten_i(data)                                                  ((0x00000004&(data))>>2)
#define TVE_INTEN_inten_p_shift                                                      (1)
#define TVE_INTEN_inten_p_mask                                                       (0x00000002)
#define TVE_INTEN_inten_p(data)                                                      (0x00000002&((data)<<1))
#define TVE_INTEN_inten_p_src(data)                                                  ((0x00000002&(data))>>1)
#define TVE_INTEN_get_inten_p(data)                                                  ((0x00000002&(data))>>1)
#define TVE_INTEN_write_data_shift                                                   (0)
#define TVE_INTEN_write_data_mask                                                    (0x00000001)
#define TVE_INTEN_write_data(data)                                                   (0x00000001&((data)<<0))
#define TVE_INTEN_write_data_src(data)                                               ((0x00000001&(data))>>0)
#define TVE_INTEN_get_write_data(data)                                               ((0x00000001&(data))>>0)


#define TVE_INTST                                                                    0x18018020
#define TVE_INTST_reg_addr                                                           "0xB8018020"
#define TVE_INTST_reg                                                                0xB8018020
#define set_TVE_INTST_reg(data)   (*((volatile unsigned int*) TVE_INTST_reg)=data)
#define get_TVE_INTST_reg   (*((volatile unsigned int*) TVE_INTST_reg))
#define TVE_INTST_inst_adr                                                           "0x0008"
#define TVE_INTST_inst                                                               0x0008
#define TVE_INTST_intst_vbi_h_shift                                                  (6)
#define TVE_INTST_intst_vbi_h_mask                                                   (0x00000040)
#define TVE_INTST_intst_vbi_h(data)                                                  (0x00000040&((data)<<6))
#define TVE_INTST_intst_vbi_h_src(data)                                              ((0x00000040&(data))>>6)
#define TVE_INTST_get_intst_vbi_h(data)                                              ((0x00000040&(data))>>6)
#define TVE_INTST_intst_vbi_i_shift                                                  (5)
#define TVE_INTST_intst_vbi_i_mask                                                   (0x00000020)
#define TVE_INTST_intst_vbi_i(data)                                                  (0x00000020&((data)<<5))
#define TVE_INTST_intst_vbi_i_src(data)                                              ((0x00000020&(data))>>5)
#define TVE_INTST_get_intst_vbi_i(data)                                              ((0x00000020&(data))>>5)
#define TVE_INTST_intst_vbi_p_shift                                                  (4)
#define TVE_INTST_intst_vbi_p_mask                                                   (0x00000010)
#define TVE_INTST_intst_vbi_p(data)                                                  (0x00000010&((data)<<4))
#define TVE_INTST_intst_vbi_p_src(data)                                              ((0x00000010&(data))>>4)
#define TVE_INTST_get_intst_vbi_p(data)                                              ((0x00000010&(data))>>4)
#define TVE_INTST_intst_h_shift                                                      (3)
#define TVE_INTST_intst_h_mask                                                       (0x00000008)
#define TVE_INTST_intst_h(data)                                                      (0x00000008&((data)<<3))
#define TVE_INTST_intst_h_src(data)                                                  ((0x00000008&(data))>>3)
#define TVE_INTST_get_intst_h(data)                                                  ((0x00000008&(data))>>3)
#define TVE_INTST_intst_i_shift                                                      (2)
#define TVE_INTST_intst_i_mask                                                       (0x00000004)
#define TVE_INTST_intst_i(data)                                                      (0x00000004&((data)<<2))
#define TVE_INTST_intst_i_src(data)                                                  ((0x00000004&(data))>>2)
#define TVE_INTST_get_intst_i(data)                                                  ((0x00000004&(data))>>2)
#define TVE_INTST_intst_p_shift                                                      (1)
#define TVE_INTST_intst_p_mask                                                       (0x00000002)
#define TVE_INTST_intst_p(data)                                                      (0x00000002&((data)<<1))
#define TVE_INTST_intst_p_src(data)                                                  ((0x00000002&(data))>>1)
#define TVE_INTST_get_intst_p(data)                                                  ((0x00000002&(data))>>1)
#define TVE_INTST_write_data_shift                                                   (0)
#define TVE_INTST_write_data_mask                                                    (0x00000001)
#define TVE_INTST_write_data(data)                                                   (0x00000001&((data)<<0))
#define TVE_INTST_write_data_src(data)                                               ((0x00000001&(data))>>0)
#define TVE_INTST_get_write_data(data)                                               ((0x00000001&(data))>>0)


#define TVE_INTPOS_I                                                                 0x18018024
#define TVE_INTPOS_I_reg_addr                                                        "0xB8018024"
#define TVE_INTPOS_I_reg                                                             0xB8018024
#define set_TVE_INTPOS_I_reg(data)   (*((volatile unsigned int*) TVE_INTPOS_I_reg)=data)
#define get_TVE_INTPOS_I_reg   (*((volatile unsigned int*) TVE_INTPOS_I_reg))
#define TVE_INTPOS_I_inst_adr                                                        "0x0009"
#define TVE_INTPOS_I_inst                                                            0x0009
#define TVE_INTPOS_I_write_en2_shift                                                 (25)
#define TVE_INTPOS_I_write_en2_mask                                                  (0x02000000)
#define TVE_INTPOS_I_write_en2(data)                                                 (0x02000000&((data)<<25))
#define TVE_INTPOS_I_write_en2_src(data)                                             ((0x02000000&(data))>>25)
#define TVE_INTPOS_I_get_write_en2(data)                                             ((0x02000000&(data))>>25)
#define TVE_INTPOS_I_int_vpos_shift                                                  (14)
#define TVE_INTPOS_I_int_vpos_mask                                                   (0x01FFC000)
#define TVE_INTPOS_I_int_vpos(data)                                                  (0x01FFC000&((data)<<14))
#define TVE_INTPOS_I_int_vpos_src(data)                                              ((0x01FFC000&(data))>>14)
#define TVE_INTPOS_I_get_int_vpos(data)                                              ((0x01FFC000&(data))>>14)
#define TVE_INTPOS_I_write_en1_shift                                                 (13)
#define TVE_INTPOS_I_write_en1_mask                                                  (0x00002000)
#define TVE_INTPOS_I_write_en1(data)                                                 (0x00002000&((data)<<13))
#define TVE_INTPOS_I_write_en1_src(data)                                             ((0x00002000&(data))>>13)
#define TVE_INTPOS_I_get_write_en1(data)                                             ((0x00002000&(data))>>13)
#define TVE_INTPOS_I_int_hpos_shift                                                  (0)
#define TVE_INTPOS_I_int_hpos_mask                                                   (0x00001FFF)
#define TVE_INTPOS_I_int_hpos(data)                                                  (0x00001FFF&((data)<<0))
#define TVE_INTPOS_I_int_hpos_src(data)                                              ((0x00001FFF&(data))>>0)
#define TVE_INTPOS_I_get_int_hpos(data)                                              ((0x00001FFF&(data))>>0)


#define TVE_INTPOS_P1                                                                0x18018028
#define TVE_INTPOS_P1_reg_addr                                                       "0xB8018028"
#define TVE_INTPOS_P1_reg                                                            0xB8018028
#define set_TVE_INTPOS_P1_reg(data)   (*((volatile unsigned int*) TVE_INTPOS_P1_reg)=data)
#define get_TVE_INTPOS_P1_reg   (*((volatile unsigned int*) TVE_INTPOS_P1_reg))
#define TVE_INTPOS_P1_inst_adr                                                       "0x000A"
#define TVE_INTPOS_P1_inst                                                           0x000A
#define TVE_INTPOS_P1_write_en2_shift                                                (25)
#define TVE_INTPOS_P1_write_en2_mask                                                 (0x02000000)
#define TVE_INTPOS_P1_write_en2(data)                                                (0x02000000&((data)<<25))
#define TVE_INTPOS_P1_write_en2_src(data)                                            ((0x02000000&(data))>>25)
#define TVE_INTPOS_P1_get_write_en2(data)                                            ((0x02000000&(data))>>25)
#define TVE_INTPOS_P1_int_vpos_shift                                                 (14)
#define TVE_INTPOS_P1_int_vpos_mask                                                  (0x01FFC000)
#define TVE_INTPOS_P1_int_vpos(data)                                                 (0x01FFC000&((data)<<14))
#define TVE_INTPOS_P1_int_vpos_src(data)                                             ((0x01FFC000&(data))>>14)
#define TVE_INTPOS_P1_get_int_vpos(data)                                             ((0x01FFC000&(data))>>14)
#define TVE_INTPOS_P1_write_en1_shift                                                (13)
#define TVE_INTPOS_P1_write_en1_mask                                                 (0x00002000)
#define TVE_INTPOS_P1_write_en1(data)                                                (0x00002000&((data)<<13))
#define TVE_INTPOS_P1_write_en1_src(data)                                            ((0x00002000&(data))>>13)
#define TVE_INTPOS_P1_get_write_en1(data)                                            ((0x00002000&(data))>>13)
#define TVE_INTPOS_P1_int_hpos_shift                                                 (0)
#define TVE_INTPOS_P1_int_hpos_mask                                                  (0x00001FFF)
#define TVE_INTPOS_P1_int_hpos(data)                                                 (0x00001FFF&((data)<<0))
#define TVE_INTPOS_P1_int_hpos_src(data)                                             ((0x00001FFF&(data))>>0)
#define TVE_INTPOS_P1_get_int_hpos(data)                                             ((0x00001FFF&(data))>>0)


#define TVE_INTPOS_P2                                                                0x1801802c
#define TVE_INTPOS_P2_reg_addr                                                       "0xB801802C"
#define TVE_INTPOS_P2_reg                                                            0xB801802C
#define set_TVE_INTPOS_P2_reg(data)   (*((volatile unsigned int*) TVE_INTPOS_P2_reg)=data)
#define get_TVE_INTPOS_P2_reg   (*((volatile unsigned int*) TVE_INTPOS_P2_reg))
#define TVE_INTPOS_P2_inst_adr                                                       "0x000B"
#define TVE_INTPOS_P2_inst                                                           0x000B
#define TVE_INTPOS_P2_write_en2_shift                                                (25)
#define TVE_INTPOS_P2_write_en2_mask                                                 (0x02000000)
#define TVE_INTPOS_P2_write_en2(data)                                                (0x02000000&((data)<<25))
#define TVE_INTPOS_P2_write_en2_src(data)                                            ((0x02000000&(data))>>25)
#define TVE_INTPOS_P2_get_write_en2(data)                                            ((0x02000000&(data))>>25)
#define TVE_INTPOS_P2_int_vpos_shift                                                 (14)
#define TVE_INTPOS_P2_int_vpos_mask                                                  (0x01FFC000)
#define TVE_INTPOS_P2_int_vpos(data)                                                 (0x01FFC000&((data)<<14))
#define TVE_INTPOS_P2_int_vpos_src(data)                                             ((0x01FFC000&(data))>>14)
#define TVE_INTPOS_P2_get_int_vpos(data)                                             ((0x01FFC000&(data))>>14)
#define TVE_INTPOS_P2_write_en1_shift                                                (13)
#define TVE_INTPOS_P2_write_en1_mask                                                 (0x00002000)
#define TVE_INTPOS_P2_write_en1(data)                                                (0x00002000&((data)<<13))
#define TVE_INTPOS_P2_write_en1_src(data)                                            ((0x00002000&(data))>>13)
#define TVE_INTPOS_P2_get_write_en1(data)                                            ((0x00002000&(data))>>13)
#define TVE_INTPOS_P2_int_hpos_shift                                                 (0)
#define TVE_INTPOS_P2_int_hpos_mask                                                  (0x00001FFF)
#define TVE_INTPOS_P2_int_hpos(data)                                                 (0x00001FFF&((data)<<0))
#define TVE_INTPOS_P2_int_hpos_src(data)                                             ((0x00001FFF&(data))>>0)
#define TVE_INTPOS_P2_get_int_hpos(data)                                             ((0x00001FFF&(data))>>0)


#define TVE_INTPOS_H1                                                                0x18018030
#define TVE_INTPOS_H1_reg_addr                                                       "0xB8018030"
#define TVE_INTPOS_H1_reg                                                            0xB8018030
#define set_TVE_INTPOS_H1_reg(data)   (*((volatile unsigned int*) TVE_INTPOS_H1_reg)=data)
#define get_TVE_INTPOS_H1_reg   (*((volatile unsigned int*) TVE_INTPOS_H1_reg))
#define TVE_INTPOS_H1_inst_adr                                                       "0x000C"
#define TVE_INTPOS_H1_inst                                                           0x000C
#define TVE_INTPOS_H1_write_en2_shift                                                (25)
#define TVE_INTPOS_H1_write_en2_mask                                                 (0x02000000)
#define TVE_INTPOS_H1_write_en2(data)                                                (0x02000000&((data)<<25))
#define TVE_INTPOS_H1_write_en2_src(data)                                            ((0x02000000&(data))>>25)
#define TVE_INTPOS_H1_get_write_en2(data)                                            ((0x02000000&(data))>>25)
#define TVE_INTPOS_H1_int_vpos_shift                                                 (14)
#define TVE_INTPOS_H1_int_vpos_mask                                                  (0x01FFC000)
#define TVE_INTPOS_H1_int_vpos(data)                                                 (0x01FFC000&((data)<<14))
#define TVE_INTPOS_H1_int_vpos_src(data)                                             ((0x01FFC000&(data))>>14)
#define TVE_INTPOS_H1_get_int_vpos(data)                                             ((0x01FFC000&(data))>>14)
#define TVE_INTPOS_H1_write_en1_shift                                                (13)
#define TVE_INTPOS_H1_write_en1_mask                                                 (0x00002000)
#define TVE_INTPOS_H1_write_en1(data)                                                (0x00002000&((data)<<13))
#define TVE_INTPOS_H1_write_en1_src(data)                                            ((0x00002000&(data))>>13)
#define TVE_INTPOS_H1_get_write_en1(data)                                            ((0x00002000&(data))>>13)
#define TVE_INTPOS_H1_int_hpos_shift                                                 (0)
#define TVE_INTPOS_H1_int_hpos_mask                                                  (0x00001FFF)
#define TVE_INTPOS_H1_int_hpos(data)                                                 (0x00001FFF&((data)<<0))
#define TVE_INTPOS_H1_int_hpos_src(data)                                             ((0x00001FFF&(data))>>0)
#define TVE_INTPOS_H1_get_int_hpos(data)                                             ((0x00001FFF&(data))>>0)


#define TVE_INTPOS_H2                                                                0x18018034
#define TVE_INTPOS_H2_reg_addr                                                       "0xB8018034"
#define TVE_INTPOS_H2_reg                                                            0xB8018034
#define set_TVE_INTPOS_H2_reg(data)   (*((volatile unsigned int*) TVE_INTPOS_H2_reg)=data)
#define get_TVE_INTPOS_H2_reg   (*((volatile unsigned int*) TVE_INTPOS_H2_reg))
#define TVE_INTPOS_H2_inst_adr                                                       "0x000D"
#define TVE_INTPOS_H2_inst                                                           0x000D
#define TVE_INTPOS_H2_write_en2_shift                                                (25)
#define TVE_INTPOS_H2_write_en2_mask                                                 (0x02000000)
#define TVE_INTPOS_H2_write_en2(data)                                                (0x02000000&((data)<<25))
#define TVE_INTPOS_H2_write_en2_src(data)                                            ((0x02000000&(data))>>25)
#define TVE_INTPOS_H2_get_write_en2(data)                                            ((0x02000000&(data))>>25)
#define TVE_INTPOS_H2_int_vpos_shift                                                 (14)
#define TVE_INTPOS_H2_int_vpos_mask                                                  (0x01FFC000)
#define TVE_INTPOS_H2_int_vpos(data)                                                 (0x01FFC000&((data)<<14))
#define TVE_INTPOS_H2_int_vpos_src(data)                                             ((0x01FFC000&(data))>>14)
#define TVE_INTPOS_H2_get_int_vpos(data)                                             ((0x01FFC000&(data))>>14)
#define TVE_INTPOS_H2_write_en1_shift                                                (13)
#define TVE_INTPOS_H2_write_en1_mask                                                 (0x00002000)
#define TVE_INTPOS_H2_write_en1(data)                                                (0x00002000&((data)<<13))
#define TVE_INTPOS_H2_write_en1_src(data)                                            ((0x00002000&(data))>>13)
#define TVE_INTPOS_H2_get_write_en1(data)                                            ((0x00002000&(data))>>13)
#define TVE_INTPOS_H2_int_hpos_shift                                                 (0)
#define TVE_INTPOS_H2_int_hpos_mask                                                  (0x00001FFF)
#define TVE_INTPOS_H2_int_hpos(data)                                                 (0x00001FFF&((data)<<0))
#define TVE_INTPOS_H2_int_hpos_src(data)                                             ((0x00001FFF&(data))>>0)
#define TVE_INTPOS_H2_get_int_hpos(data)                                             ((0x00001FFF&(data))>>0)


#define TVE_SRSTN                                                                    0x18018038
#define TVE_SRSTN_reg_addr                                                           "0xB8018038"
#define TVE_SRSTN_reg                                                                0xB8018038
#define set_TVE_SRSTN_reg(data)   (*((volatile unsigned int*) TVE_SRSTN_reg)=data)
#define get_TVE_SRSTN_reg   (*((volatile unsigned int*) TVE_SRSTN_reg))
#define TVE_SRSTN_inst_adr                                                           "0x000E"
#define TVE_SRSTN_inst                                                               0x000E
#define TVE_SRSTN_srstn_shift                                                        (0)
#define TVE_SRSTN_srstn_mask                                                         (0x00000001)
#define TVE_SRSTN_srstn(data)                                                        (0x00000001&((data)<<0))
#define TVE_SRSTN_srstn_src(data)                                                    ((0x00000001&(data))>>0)
#define TVE_SRSTN_get_srstn(data)                                                    ((0x00000001&(data))>>0)


#define TVE_AV_CTRL                                                                  0x18018040
#define TVE_AV_CTRL_reg_addr                                                         "0xB8018040"
#define TVE_AV_CTRL_reg                                                              0xB8018040
#define set_TVE_AV_CTRL_reg(data)   (*((volatile unsigned int*) TVE_AV_CTRL_reg)=data)
#define get_TVE_AV_CTRL_reg   (*((volatile unsigned int*) TVE_AV_CTRL_reg))
#define TVE_AV_CTRL_inst_adr                                                         "0x0010"
#define TVE_AV_CTRL_inst                                                             0x0010
#define TVE_AV_CTRL_h_colorbar_ebl_shift                                             (6)
#define TVE_AV_CTRL_h_colorbar_ebl_mask                                              (0x00000040)
#define TVE_AV_CTRL_h_colorbar_ebl(data)                                             (0x00000040&((data)<<6))
#define TVE_AV_CTRL_h_colorbar_ebl_src(data)                                         ((0x00000040&(data))>>6)
#define TVE_AV_CTRL_get_h_colorbar_ebl(data)                                         ((0x00000040&(data))>>6)
#define TVE_AV_CTRL_h_black_ebl_shift                                                (5)
#define TVE_AV_CTRL_h_black_ebl_mask                                                 (0x00000020)
#define TVE_AV_CTRL_h_black_ebl(data)                                                (0x00000020&((data)<<5))
#define TVE_AV_CTRL_h_black_ebl_src(data)                                            ((0x00000020&(data))>>5)
#define TVE_AV_CTRL_get_h_black_ebl(data)                                            ((0x00000020&(data))>>5)
#define TVE_AV_CTRL_i_colorbar_ebl_shift                                             (4)
#define TVE_AV_CTRL_i_colorbar_ebl_mask                                              (0x00000010)
#define TVE_AV_CTRL_i_colorbar_ebl(data)                                             (0x00000010&((data)<<4))
#define TVE_AV_CTRL_i_colorbar_ebl_src(data)                                         ((0x00000010&(data))>>4)
#define TVE_AV_CTRL_get_i_colorbar_ebl(data)                                         ((0x00000010&(data))>>4)
#define TVE_AV_CTRL_p_colorbar_ebl_shift                                             (3)
#define TVE_AV_CTRL_p_colorbar_ebl_mask                                              (0x00000008)
#define TVE_AV_CTRL_p_colorbar_ebl(data)                                             (0x00000008&((data)<<3))
#define TVE_AV_CTRL_p_colorbar_ebl_src(data)                                         ((0x00000008&(data))>>3)
#define TVE_AV_CTRL_get_p_colorbar_ebl(data)                                         ((0x00000008&(data))>>3)
#define TVE_AV_CTRL_i_black_ebl_shift                                                (2)
#define TVE_AV_CTRL_i_black_ebl_mask                                                 (0x00000004)
#define TVE_AV_CTRL_i_black_ebl(data)                                                (0x00000004&((data)<<2))
#define TVE_AV_CTRL_i_black_ebl_src(data)                                            ((0x00000004&(data))>>2)
#define TVE_AV_CTRL_get_i_black_ebl(data)                                            ((0x00000004&(data))>>2)
#define TVE_AV_CTRL_p_black_ebl_shift                                                (1)
#define TVE_AV_CTRL_p_black_ebl_mask                                                 (0x00000002)
#define TVE_AV_CTRL_p_black_ebl(data)                                                (0x00000002&((data)<<1))
#define TVE_AV_CTRL_p_black_ebl_src(data)                                            ((0x00000002&(data))>>1)
#define TVE_AV_CTRL_get_p_black_ebl(data)                                            ((0x00000002&(data))>>1)
#define TVE_AV_CTRL_write_data_shift                                                 (0)
#define TVE_AV_CTRL_write_data_mask                                                  (0x00000001)
#define TVE_AV_CTRL_write_data(data)                                                 (0x00000001&((data)<<0))
#define TVE_AV_CTRL_write_data_src(data)                                             ((0x00000001&(data))>>0)
#define TVE_AV_CTRL_get_write_data(data)                                             ((0x00000001&(data))>>0)


#define TVE_CAV_422                                                                  0x18018044
#define TVE_CAV_422_reg_addr                                                         "0xB8018044"
#define TVE_CAV_422_reg                                                              0xB8018044
#define set_TVE_CAV_422_reg(data)   (*((volatile unsigned int*) TVE_CAV_422_reg)=data)
#define get_TVE_CAV_422_reg   (*((volatile unsigned int*) TVE_CAV_422_reg))
#define TVE_CAV_422_inst_adr                                                         "0x0011"
#define TVE_CAV_422_inst                                                             0x0011
#define TVE_CAV_422_fir422_sel_shift                                                 (0)
#define TVE_CAV_422_fir422_sel_mask                                                  (0x00000003)
#define TVE_CAV_422_fir422_sel(data)                                                 (0x00000003&((data)<<0))
#define TVE_CAV_422_fir422_sel_src(data)                                             ((0x00000003&(data))>>0)
#define TVE_CAV_422_get_fir422_sel(data)                                             ((0x00000003&(data))>>0)


#define TVE_AV_SLEW                                                                  0x18018048
#define TVE_AV_SLEW_reg_addr                                                         "0xB8018048"
#define TVE_AV_SLEW_reg                                                              0xB8018048
#define set_TVE_AV_SLEW_reg(data)   (*((volatile unsigned int*) TVE_AV_SLEW_reg)=data)
#define get_TVE_AV_SLEW_reg   (*((volatile unsigned int*) TVE_AV_SLEW_reg))
#define TVE_AV_SLEW_inst_adr                                                         "0x0012"
#define TVE_AV_SLEW_inst                                                             0x0012
#define TVE_AV_SLEW_write_en4_shift                                                  (9)
#define TVE_AV_SLEW_write_en4_mask                                                   (0x00000200)
#define TVE_AV_SLEW_write_en4(data)                                                  (0x00000200&((data)<<9))
#define TVE_AV_SLEW_write_en4_src(data)                                              ((0x00000200&(data))>>9)
#define TVE_AV_SLEW_get_write_en4(data)                                              ((0x00000200&(data))>>9)
#define TVE_AV_SLEW_i_en_shift                                                       (8)
#define TVE_AV_SLEW_i_en_mask                                                        (0x00000100)
#define TVE_AV_SLEW_i_en(data)                                                       (0x00000100&((data)<<8))
#define TVE_AV_SLEW_i_en_src(data)                                                   ((0x00000100&(data))>>8)
#define TVE_AV_SLEW_get_i_en(data)                                                   ((0x00000100&(data))>>8)
#define TVE_AV_SLEW_write_en3_shift                                                  (7)
#define TVE_AV_SLEW_write_en3_mask                                                   (0x00000080)
#define TVE_AV_SLEW_write_en3(data)                                                  (0x00000080&((data)<<7))
#define TVE_AV_SLEW_write_en3_src(data)                                              ((0x00000080&(data))>>7)
#define TVE_AV_SLEW_get_write_en3(data)                                              ((0x00000080&(data))>>7)
#define TVE_AV_SLEW_p_en_shift                                                       (6)
#define TVE_AV_SLEW_p_en_mask                                                        (0x00000040)
#define TVE_AV_SLEW_p_en(data)                                                       (0x00000040&((data)<<6))
#define TVE_AV_SLEW_p_en_src(data)                                                   ((0x00000040&(data))>>6)
#define TVE_AV_SLEW_get_p_en(data)                                                   ((0x00000040&(data))>>6)
#define TVE_AV_SLEW_write_en2_shift                                                  (5)
#define TVE_AV_SLEW_write_en2_mask                                                   (0x00000020)
#define TVE_AV_SLEW_write_en2(data)                                                  (0x00000020&((data)<<5))
#define TVE_AV_SLEW_write_en2_src(data)                                              ((0x00000020&(data))>>5)
#define TVE_AV_SLEW_get_write_en2(data)                                              ((0x00000020&(data))>>5)
#define TVE_AV_SLEW_i_slewrate_shift                                                 (3)
#define TVE_AV_SLEW_i_slewrate_mask                                                  (0x00000018)
#define TVE_AV_SLEW_i_slewrate(data)                                                 (0x00000018&((data)<<3))
#define TVE_AV_SLEW_i_slewrate_src(data)                                             ((0x00000018&(data))>>3)
#define TVE_AV_SLEW_get_i_slewrate(data)                                             ((0x00000018&(data))>>3)
#define TVE_AV_SLEW_write_en1_shift                                                  (2)
#define TVE_AV_SLEW_write_en1_mask                                                   (0x00000004)
#define TVE_AV_SLEW_write_en1(data)                                                  (0x00000004&((data)<<2))
#define TVE_AV_SLEW_write_en1_src(data)                                              ((0x00000004&(data))>>2)
#define TVE_AV_SLEW_get_write_en1(data)                                              ((0x00000004&(data))>>2)
#define TVE_AV_SLEW_p_slewrate_shift                                                 (0)
#define TVE_AV_SLEW_p_slewrate_mask                                                  (0x00000003)
#define TVE_AV_SLEW_p_slewrate(data)                                                 (0x00000003&((data)<<0))
#define TVE_AV_SLEW_p_slewrate_src(data)                                             ((0x00000003&(data))>>0)
#define TVE_AV_SLEW_get_p_slewrate(data)                                             ((0x00000003&(data))>>0)


#define TVE_SLEW_I_HPOS                                                              0x1801804c
#define TVE_SLEW_I_HPOS_reg_addr                                                     "0xB801804C"
#define TVE_SLEW_I_HPOS_reg                                                          0xB801804C
#define set_TVE_SLEW_I_HPOS_reg(data)   (*((volatile unsigned int*) TVE_SLEW_I_HPOS_reg)=data)
#define get_TVE_SLEW_I_HPOS_reg   (*((volatile unsigned int*) TVE_SLEW_I_HPOS_reg))
#define TVE_SLEW_I_HPOS_inst_adr                                                     "0x0013"
#define TVE_SLEW_I_HPOS_inst                                                         0x0013
#define TVE_SLEW_I_HPOS_write_en2_shift                                              (21)
#define TVE_SLEW_I_HPOS_write_en2_mask                                               (0x00200000)
#define TVE_SLEW_I_HPOS_write_en2(data)                                              (0x00200000&((data)<<21))
#define TVE_SLEW_I_HPOS_write_en2_src(data)                                          ((0x00200000&(data))>>21)
#define TVE_SLEW_I_HPOS_get_write_en2(data)                                          ((0x00200000&(data))>>21)
#define TVE_SLEW_I_HPOS_i_h_st_shift                                                 (11)
#define TVE_SLEW_I_HPOS_i_h_st_mask                                                  (0x001FF800)
#define TVE_SLEW_I_HPOS_i_h_st(data)                                                 (0x001FF800&((data)<<11))
#define TVE_SLEW_I_HPOS_i_h_st_src(data)                                             ((0x001FF800&(data))>>11)
#define TVE_SLEW_I_HPOS_get_i_h_st(data)                                             ((0x001FF800&(data))>>11)
#define TVE_SLEW_I_HPOS_write_en1_shift                                              (10)
#define TVE_SLEW_I_HPOS_write_en1_mask                                               (0x00000400)
#define TVE_SLEW_I_HPOS_write_en1(data)                                              (0x00000400&((data)<<10))
#define TVE_SLEW_I_HPOS_write_en1_src(data)                                          ((0x00000400&(data))>>10)
#define TVE_SLEW_I_HPOS_get_write_en1(data)                                          ((0x00000400&(data))>>10)
#define TVE_SLEW_I_HPOS_i_h_end_shift                                                (0)
#define TVE_SLEW_I_HPOS_i_h_end_mask                                                 (0x000003FF)
#define TVE_SLEW_I_HPOS_i_h_end(data)                                                (0x000003FF&((data)<<0))
#define TVE_SLEW_I_HPOS_i_h_end_src(data)                                            ((0x000003FF&(data))>>0)
#define TVE_SLEW_I_HPOS_get_i_h_end(data)                                            ((0x000003FF&(data))>>0)


#define TVE_AV_I_HPOS                                                                0x18018050
#define TVE_AV_I_HPOS_reg_addr                                                       "0xB8018050"
#define TVE_AV_I_HPOS_reg                                                            0xB8018050
#define set_TVE_AV_I_HPOS_reg(data)   (*((volatile unsigned int*) TVE_AV_I_HPOS_reg)=data)
#define get_TVE_AV_I_HPOS_reg   (*((volatile unsigned int*) TVE_AV_I_HPOS_reg))
#define TVE_AV_I_HPOS_inst_adr                                                       "0x0014"
#define TVE_AV_I_HPOS_inst                                                           0x0014
#define TVE_AV_I_HPOS_write_en2_shift                                                (27)
#define TVE_AV_I_HPOS_write_en2_mask                                                 (0x08000000)
#define TVE_AV_I_HPOS_write_en2(data)                                                (0x08000000&((data)<<27))
#define TVE_AV_I_HPOS_write_en2_src(data)                                            ((0x08000000&(data))>>27)
#define TVE_AV_I_HPOS_get_write_en2(data)                                            ((0x08000000&(data))>>27)
#define TVE_AV_I_HPOS_i_h_st_shift                                                   (14)
#define TVE_AV_I_HPOS_i_h_st_mask                                                    (0x07FFC000)
#define TVE_AV_I_HPOS_i_h_st(data)                                                   (0x07FFC000&((data)<<14))
#define TVE_AV_I_HPOS_i_h_st_src(data)                                               ((0x07FFC000&(data))>>14)
#define TVE_AV_I_HPOS_get_i_h_st(data)                                               ((0x07FFC000&(data))>>14)
#define TVE_AV_I_HPOS_write_en1_shift                                                (13)
#define TVE_AV_I_HPOS_write_en1_mask                                                 (0x00002000)
#define TVE_AV_I_HPOS_write_en1(data)                                                (0x00002000&((data)<<13))
#define TVE_AV_I_HPOS_write_en1_src(data)                                            ((0x00002000&(data))>>13)
#define TVE_AV_I_HPOS_get_write_en1(data)                                            ((0x00002000&(data))>>13)
#define TVE_AV_I_HPOS_i_h_end_shift                                                  (0)
#define TVE_AV_I_HPOS_i_h_end_mask                                                   (0x00001FFF)
#define TVE_AV_I_HPOS_i_h_end(data)                                                  (0x00001FFF&((data)<<0))
#define TVE_AV_I_HPOS_i_h_end_src(data)                                              ((0x00001FFF&(data))>>0)
#define TVE_AV_I_HPOS_get_i_h_end(data)                                              ((0x00001FFF&(data))>>0)


#define TVE_AV_P_HPOS1                                                               0x18018054
#define TVE_AV_P_HPOS1_reg_addr                                                      "0xB8018054"
#define TVE_AV_P_HPOS1_reg                                                           0xB8018054
#define set_TVE_AV_P_HPOS1_reg(data)   (*((volatile unsigned int*) TVE_AV_P_HPOS1_reg)=data)
#define get_TVE_AV_P_HPOS1_reg   (*((volatile unsigned int*) TVE_AV_P_HPOS1_reg))
#define TVE_AV_P_HPOS1_inst_adr                                                      "0x0015"
#define TVE_AV_P_HPOS1_inst                                                          0x0015
#define TVE_AV_P_HPOS1_write_en3_shift                                               (29)
#define TVE_AV_P_HPOS1_write_en3_mask                                                (0x20000000)
#define TVE_AV_P_HPOS1_write_en3(data)                                               (0x20000000&((data)<<29))
#define TVE_AV_P_HPOS1_write_en3_src(data)                                           ((0x20000000&(data))>>29)
#define TVE_AV_P_HPOS1_get_write_en3(data)                                           ((0x20000000&(data))>>29)
#define TVE_AV_P_HPOS1_p_av_cord_shift                                               (28)
#define TVE_AV_P_HPOS1_p_av_cord_mask                                                (0x10000000)
#define TVE_AV_P_HPOS1_p_av_cord(data)                                               (0x10000000&((data)<<28))
#define TVE_AV_P_HPOS1_p_av_cord_src(data)                                           ((0x10000000&(data))>>28)
#define TVE_AV_P_HPOS1_get_p_av_cord(data)                                           ((0x10000000&(data))>>28)
#define TVE_AV_P_HPOS1_write_en2_shift                                               (27)
#define TVE_AV_P_HPOS1_write_en2_mask                                                (0x08000000)
#define TVE_AV_P_HPOS1_write_en2(data)                                               (0x08000000&((data)<<27))
#define TVE_AV_P_HPOS1_write_en2_src(data)                                           ((0x08000000&(data))>>27)
#define TVE_AV_P_HPOS1_get_write_en2(data)                                           ((0x08000000&(data))>>27)
#define TVE_AV_P_HPOS1_p_h_st_shift                                                  (14)
#define TVE_AV_P_HPOS1_p_h_st_mask                                                   (0x07FFC000)
#define TVE_AV_P_HPOS1_p_h_st(data)                                                  (0x07FFC000&((data)<<14))
#define TVE_AV_P_HPOS1_p_h_st_src(data)                                              ((0x07FFC000&(data))>>14)
#define TVE_AV_P_HPOS1_get_p_h_st(data)                                              ((0x07FFC000&(data))>>14)
#define TVE_AV_P_HPOS1_write_en1_shift                                               (13)
#define TVE_AV_P_HPOS1_write_en1_mask                                                (0x00002000)
#define TVE_AV_P_HPOS1_write_en1(data)                                               (0x00002000&((data)<<13))
#define TVE_AV_P_HPOS1_write_en1_src(data)                                           ((0x00002000&(data))>>13)
#define TVE_AV_P_HPOS1_get_write_en1(data)                                           ((0x00002000&(data))>>13)
#define TVE_AV_P_HPOS1_p_h_end_shift                                                 (0)
#define TVE_AV_P_HPOS1_p_h_end_mask                                                  (0x00001FFF)
#define TVE_AV_P_HPOS1_p_h_end(data)                                                 (0x00001FFF&((data)<<0))
#define TVE_AV_P_HPOS1_p_h_end_src(data)                                             ((0x00001FFF&(data))>>0)
#define TVE_AV_P_HPOS1_get_p_h_end(data)                                             ((0x00001FFF&(data))>>0)


#define TVE_AV_H_HPOS1                                                               0x18018058
#define TVE_AV_H_HPOS1_reg_addr                                                      "0xB8018058"
#define TVE_AV_H_HPOS1_reg                                                           0xB8018058
#define set_TVE_AV_H_HPOS1_reg(data)   (*((volatile unsigned int*) TVE_AV_H_HPOS1_reg)=data)
#define get_TVE_AV_H_HPOS1_reg   (*((volatile unsigned int*) TVE_AV_H_HPOS1_reg))
#define TVE_AV_H_HPOS1_inst_adr                                                      "0x0016"
#define TVE_AV_H_HPOS1_inst                                                          0x0016
#define TVE_AV_H_HPOS1_write_en3_shift                                               (29)
#define TVE_AV_H_HPOS1_write_en3_mask                                                (0x20000000)
#define TVE_AV_H_HPOS1_write_en3(data)                                               (0x20000000&((data)<<29))
#define TVE_AV_H_HPOS1_write_en3_src(data)                                           ((0x20000000&(data))>>29)
#define TVE_AV_H_HPOS1_get_write_en3(data)                                           ((0x20000000&(data))>>29)
#define TVE_AV_H_HPOS1_h_av_cord_shift                                               (28)
#define TVE_AV_H_HPOS1_h_av_cord_mask                                                (0x10000000)
#define TVE_AV_H_HPOS1_h_av_cord(data)                                               (0x10000000&((data)<<28))
#define TVE_AV_H_HPOS1_h_av_cord_src(data)                                           ((0x10000000&(data))>>28)
#define TVE_AV_H_HPOS1_get_h_av_cord(data)                                           ((0x10000000&(data))>>28)
#define TVE_AV_H_HPOS1_write_en2_shift                                               (27)
#define TVE_AV_H_HPOS1_write_en2_mask                                                (0x08000000)
#define TVE_AV_H_HPOS1_write_en2(data)                                               (0x08000000&((data)<<27))
#define TVE_AV_H_HPOS1_write_en2_src(data)                                           ((0x08000000&(data))>>27)
#define TVE_AV_H_HPOS1_get_write_en2(data)                                           ((0x08000000&(data))>>27)
#define TVE_AV_H_HPOS1_h_h_st_shift                                                  (14)
#define TVE_AV_H_HPOS1_h_h_st_mask                                                   (0x07FFC000)
#define TVE_AV_H_HPOS1_h_h_st(data)                                                  (0x07FFC000&((data)<<14))
#define TVE_AV_H_HPOS1_h_h_st_src(data)                                              ((0x07FFC000&(data))>>14)
#define TVE_AV_H_HPOS1_get_h_h_st(data)                                              ((0x07FFC000&(data))>>14)
#define TVE_AV_H_HPOS1_write_en1_shift                                               (13)
#define TVE_AV_H_HPOS1_write_en1_mask                                                (0x00002000)
#define TVE_AV_H_HPOS1_write_en1(data)                                               (0x00002000&((data)<<13))
#define TVE_AV_H_HPOS1_write_en1_src(data)                                           ((0x00002000&(data))>>13)
#define TVE_AV_H_HPOS1_get_write_en1(data)                                           ((0x00002000&(data))>>13)
#define TVE_AV_H_HPOS1_h_h_end_shift                                                 (0)
#define TVE_AV_H_HPOS1_h_h_end_mask                                                  (0x00001FFF)
#define TVE_AV_H_HPOS1_h_h_end(data)                                                 (0x00001FFF&((data)<<0))
#define TVE_AV_H_HPOS1_h_h_end_src(data)                                             ((0x00001FFF&(data))>>0)
#define TVE_AV_H_HPOS1_get_h_h_end(data)                                             ((0x00001FFF&(data))>>0)


#define TVE_ITOP_VPOS                                                                0x1801805c
#define TVE_ITOP_VPOS_reg_addr                                                       "0xB801805C"
#define TVE_ITOP_VPOS_reg                                                            0xB801805C
#define set_TVE_ITOP_VPOS_reg(data)   (*((volatile unsigned int*) TVE_ITOP_VPOS_reg)=data)
#define get_TVE_ITOP_VPOS_reg   (*((volatile unsigned int*) TVE_ITOP_VPOS_reg))
#define TVE_ITOP_VPOS_inst_adr                                                       "0x0017"
#define TVE_ITOP_VPOS_inst                                                           0x0017
#define TVE_ITOP_VPOS_write_en2_shift                                                (23)
#define TVE_ITOP_VPOS_write_en2_mask                                                 (0x00800000)
#define TVE_ITOP_VPOS_write_en2(data)                                                (0x00800000&((data)<<23))
#define TVE_ITOP_VPOS_write_en2_src(data)                                            ((0x00800000&(data))>>23)
#define TVE_ITOP_VPOS_get_write_en2(data)                                            ((0x00800000&(data))>>23)
#define TVE_ITOP_VPOS_itop_v_st_shift                                                (12)
#define TVE_ITOP_VPOS_itop_v_st_mask                                                 (0x007FF000)
#define TVE_ITOP_VPOS_itop_v_st(data)                                                (0x007FF000&((data)<<12))
#define TVE_ITOP_VPOS_itop_v_st_src(data)                                            ((0x007FF000&(data))>>12)
#define TVE_ITOP_VPOS_get_itop_v_st(data)                                            ((0x007FF000&(data))>>12)
#define TVE_ITOP_VPOS_write_en1_shift                                                (11)
#define TVE_ITOP_VPOS_write_en1_mask                                                 (0x00000800)
#define TVE_ITOP_VPOS_write_en1(data)                                                (0x00000800&((data)<<11))
#define TVE_ITOP_VPOS_write_en1_src(data)                                            ((0x00000800&(data))>>11)
#define TVE_ITOP_VPOS_get_write_en1(data)                                            ((0x00000800&(data))>>11)
#define TVE_ITOP_VPOS_itop_v_end_shift                                               (0)
#define TVE_ITOP_VPOS_itop_v_end_mask                                                (0x000007FF)
#define TVE_ITOP_VPOS_itop_v_end(data)                                               (0x000007FF&((data)<<0))
#define TVE_ITOP_VPOS_itop_v_end_src(data)                                           ((0x000007FF&(data))>>0)
#define TVE_ITOP_VPOS_get_itop_v_end(data)                                           ((0x000007FF&(data))>>0)


#define TVE_IBOT_VPOS                                                                0x18018060
#define TVE_IBOT_VPOS_reg_addr                                                       "0xB8018060"
#define TVE_IBOT_VPOS_reg                                                            0xB8018060
#define set_TVE_IBOT_VPOS_reg(data)   (*((volatile unsigned int*) TVE_IBOT_VPOS_reg)=data)
#define get_TVE_IBOT_VPOS_reg   (*((volatile unsigned int*) TVE_IBOT_VPOS_reg))
#define TVE_IBOT_VPOS_inst_adr                                                       "0x0018"
#define TVE_IBOT_VPOS_inst                                                           0x0018
#define TVE_IBOT_VPOS_write_en2_shift                                                (23)
#define TVE_IBOT_VPOS_write_en2_mask                                                 (0x00800000)
#define TVE_IBOT_VPOS_write_en2(data)                                                (0x00800000&((data)<<23))
#define TVE_IBOT_VPOS_write_en2_src(data)                                            ((0x00800000&(data))>>23)
#define TVE_IBOT_VPOS_get_write_en2(data)                                            ((0x00800000&(data))>>23)
#define TVE_IBOT_VPOS_ibot_v_st_shift                                                (12)
#define TVE_IBOT_VPOS_ibot_v_st_mask                                                 (0x007FF000)
#define TVE_IBOT_VPOS_ibot_v_st(data)                                                (0x007FF000&((data)<<12))
#define TVE_IBOT_VPOS_ibot_v_st_src(data)                                            ((0x007FF000&(data))>>12)
#define TVE_IBOT_VPOS_get_ibot_v_st(data)                                            ((0x007FF000&(data))>>12)
#define TVE_IBOT_VPOS_write_en1_shift                                                (11)
#define TVE_IBOT_VPOS_write_en1_mask                                                 (0x00000800)
#define TVE_IBOT_VPOS_write_en1(data)                                                (0x00000800&((data)<<11))
#define TVE_IBOT_VPOS_write_en1_src(data)                                            ((0x00000800&(data))>>11)
#define TVE_IBOT_VPOS_get_write_en1(data)                                            ((0x00000800&(data))>>11)
#define TVE_IBOT_VPOS_ibot_v_end_shift                                               (0)
#define TVE_IBOT_VPOS_ibot_v_end_mask                                                (0x000007FF)
#define TVE_IBOT_VPOS_ibot_v_end(data)                                               (0x000007FF&((data)<<0))
#define TVE_IBOT_VPOS_ibot_v_end_src(data)                                           ((0x000007FF&(data))>>0)
#define TVE_IBOT_VPOS_get_ibot_v_end(data)                                           ((0x000007FF&(data))>>0)


#define TVE_P_VPOS1                                                                  0x18018064
#define TVE_P_VPOS1_reg_addr                                                         "0xB8018064"
#define TVE_P_VPOS1_reg                                                              0xB8018064
#define set_TVE_P_VPOS1_reg(data)   (*((volatile unsigned int*) TVE_P_VPOS1_reg)=data)
#define get_TVE_P_VPOS1_reg   (*((volatile unsigned int*) TVE_P_VPOS1_reg))
#define TVE_P_VPOS1_inst_adr                                                         "0x0019"
#define TVE_P_VPOS1_inst                                                             0x0019
#define TVE_P_VPOS1_write_en2_shift                                                  (23)
#define TVE_P_VPOS1_write_en2_mask                                                   (0x00800000)
#define TVE_P_VPOS1_write_en2(data)                                                  (0x00800000&((data)<<23))
#define TVE_P_VPOS1_write_en2_src(data)                                              ((0x00800000&(data))>>23)
#define TVE_P_VPOS1_get_write_en2(data)                                              ((0x00800000&(data))>>23)
#define TVE_P_VPOS1_p_v_st_shift                                                     (12)
#define TVE_P_VPOS1_p_v_st_mask                                                      (0x007FF000)
#define TVE_P_VPOS1_p_v_st(data)                                                     (0x007FF000&((data)<<12))
#define TVE_P_VPOS1_p_v_st_src(data)                                                 ((0x007FF000&(data))>>12)
#define TVE_P_VPOS1_get_p_v_st(data)                                                 ((0x007FF000&(data))>>12)
#define TVE_P_VPOS1_write_en1_shift                                                  (11)
#define TVE_P_VPOS1_write_en1_mask                                                   (0x00000800)
#define TVE_P_VPOS1_write_en1(data)                                                  (0x00000800&((data)<<11))
#define TVE_P_VPOS1_write_en1_src(data)                                              ((0x00000800&(data))>>11)
#define TVE_P_VPOS1_get_write_en1(data)                                              ((0x00000800&(data))>>11)
#define TVE_P_VPOS1_p_v_end_shift                                                    (0)
#define TVE_P_VPOS1_p_v_end_mask                                                     (0x000007FF)
#define TVE_P_VPOS1_p_v_end(data)                                                    (0x000007FF&((data)<<0))
#define TVE_P_VPOS1_p_v_end_src(data)                                                ((0x000007FF&(data))>>0)
#define TVE_P_VPOS1_get_p_v_end(data)                                                ((0x000007FF&(data))>>0)


#define TVE_P_VPOS2                                                                  0x18018068
#define TVE_P_VPOS2_reg_addr                                                         "0xB8018068"
#define TVE_P_VPOS2_reg                                                              0xB8018068
#define set_TVE_P_VPOS2_reg(data)   (*((volatile unsigned int*) TVE_P_VPOS2_reg)=data)
#define get_TVE_P_VPOS2_reg   (*((volatile unsigned int*) TVE_P_VPOS2_reg))
#define TVE_P_VPOS2_inst_adr                                                         "0x001A"
#define TVE_P_VPOS2_inst                                                             0x001A
#define TVE_P_VPOS2_write_en2_shift                                                  (23)
#define TVE_P_VPOS2_write_en2_mask                                                   (0x00800000)
#define TVE_P_VPOS2_write_en2(data)                                                  (0x00800000&((data)<<23))
#define TVE_P_VPOS2_write_en2_src(data)                                              ((0x00800000&(data))>>23)
#define TVE_P_VPOS2_get_write_en2(data)                                              ((0x00800000&(data))>>23)
#define TVE_P_VPOS2_p_v_st_shift                                                     (12)
#define TVE_P_VPOS2_p_v_st_mask                                                      (0x007FF000)
#define TVE_P_VPOS2_p_v_st(data)                                                     (0x007FF000&((data)<<12))
#define TVE_P_VPOS2_p_v_st_src(data)                                                 ((0x007FF000&(data))>>12)
#define TVE_P_VPOS2_get_p_v_st(data)                                                 ((0x007FF000&(data))>>12)
#define TVE_P_VPOS2_write_en1_shift                                                  (11)
#define TVE_P_VPOS2_write_en1_mask                                                   (0x00000800)
#define TVE_P_VPOS2_write_en1(data)                                                  (0x00000800&((data)<<11))
#define TVE_P_VPOS2_write_en1_src(data)                                              ((0x00000800&(data))>>11)
#define TVE_P_VPOS2_get_write_en1(data)                                              ((0x00000800&(data))>>11)
#define TVE_P_VPOS2_p_v_end_shift                                                    (0)
#define TVE_P_VPOS2_p_v_end_mask                                                     (0x000007FF)
#define TVE_P_VPOS2_p_v_end(data)                                                    (0x000007FF&((data)<<0))
#define TVE_P_VPOS2_p_v_end_src(data)                                                ((0x000007FF&(data))>>0)
#define TVE_P_VPOS2_get_p_v_end(data)                                                ((0x000007FF&(data))>>0)


#define TVE_H_VPOS1                                                                  0x1801806c
#define TVE_H_VPOS1_reg_addr                                                         "0xB801806C"
#define TVE_H_VPOS1_reg                                                              0xB801806C
#define set_TVE_H_VPOS1_reg(data)   (*((volatile unsigned int*) TVE_H_VPOS1_reg)=data)
#define get_TVE_H_VPOS1_reg   (*((volatile unsigned int*) TVE_H_VPOS1_reg))
#define TVE_H_VPOS1_inst_adr                                                         "0x001B"
#define TVE_H_VPOS1_inst                                                             0x001B
#define TVE_H_VPOS1_write_en2_shift                                                  (23)
#define TVE_H_VPOS1_write_en2_mask                                                   (0x00800000)
#define TVE_H_VPOS1_write_en2(data)                                                  (0x00800000&((data)<<23))
#define TVE_H_VPOS1_write_en2_src(data)                                              ((0x00800000&(data))>>23)
#define TVE_H_VPOS1_get_write_en2(data)                                              ((0x00800000&(data))>>23)
#define TVE_H_VPOS1_h_v_st_shift                                                     (12)
#define TVE_H_VPOS1_h_v_st_mask                                                      (0x007FF000)
#define TVE_H_VPOS1_h_v_st(data)                                                     (0x007FF000&((data)<<12))
#define TVE_H_VPOS1_h_v_st_src(data)                                                 ((0x007FF000&(data))>>12)
#define TVE_H_VPOS1_get_h_v_st(data)                                                 ((0x007FF000&(data))>>12)
#define TVE_H_VPOS1_write_en1_shift                                                  (11)
#define TVE_H_VPOS1_write_en1_mask                                                   (0x00000800)
#define TVE_H_VPOS1_write_en1(data)                                                  (0x00000800&((data)<<11))
#define TVE_H_VPOS1_write_en1_src(data)                                              ((0x00000800&(data))>>11)
#define TVE_H_VPOS1_get_write_en1(data)                                              ((0x00000800&(data))>>11)
#define TVE_H_VPOS1_h_v_end_shift                                                    (0)
#define TVE_H_VPOS1_h_v_end_mask                                                     (0x000007FF)
#define TVE_H_VPOS1_h_v_end(data)                                                    (0x000007FF&((data)<<0))
#define TVE_H_VPOS1_h_v_end_src(data)                                                ((0x000007FF&(data))>>0)
#define TVE_H_VPOS1_get_h_v_end(data)                                                ((0x000007FF&(data))>>0)


#define TVE_H_VPOS2                                                                  0x18018070
#define TVE_H_VPOS2_reg_addr                                                         "0xB8018070"
#define TVE_H_VPOS2_reg                                                              0xB8018070
#define set_TVE_H_VPOS2_reg(data)   (*((volatile unsigned int*) TVE_H_VPOS2_reg)=data)
#define get_TVE_H_VPOS2_reg   (*((volatile unsigned int*) TVE_H_VPOS2_reg))
#define TVE_H_VPOS2_inst_adr                                                         "0x001C"
#define TVE_H_VPOS2_inst                                                             0x001C
#define TVE_H_VPOS2_write_en2_shift                                                  (23)
#define TVE_H_VPOS2_write_en2_mask                                                   (0x00800000)
#define TVE_H_VPOS2_write_en2(data)                                                  (0x00800000&((data)<<23))
#define TVE_H_VPOS2_write_en2_src(data)                                              ((0x00800000&(data))>>23)
#define TVE_H_VPOS2_get_write_en2(data)                                              ((0x00800000&(data))>>23)
#define TVE_H_VPOS2_h_v_st_shift                                                     (12)
#define TVE_H_VPOS2_h_v_st_mask                                                      (0x007FF000)
#define TVE_H_VPOS2_h_v_st(data)                                                     (0x007FF000&((data)<<12))
#define TVE_H_VPOS2_h_v_st_src(data)                                                 ((0x007FF000&(data))>>12)
#define TVE_H_VPOS2_get_h_v_st(data)                                                 ((0x007FF000&(data))>>12)
#define TVE_H_VPOS2_write_en1_shift                                                  (11)
#define TVE_H_VPOS2_write_en1_mask                                                   (0x00000800)
#define TVE_H_VPOS2_write_en1(data)                                                  (0x00000800&((data)<<11))
#define TVE_H_VPOS2_write_en1_src(data)                                              ((0x00000800&(data))>>11)
#define TVE_H_VPOS2_get_write_en1(data)                                              ((0x00000800&(data))>>11)
#define TVE_H_VPOS2_h_v_end_shift                                                    (0)
#define TVE_H_VPOS2_h_v_end_mask                                                     (0x000007FF)
#define TVE_H_VPOS2_h_v_end(data)                                                    (0x000007FF&((data)<<0))
#define TVE_H_VPOS2_h_v_end_src(data)                                                ((0x000007FF&(data))>>0)
#define TVE_H_VPOS2_get_h_v_end(data)                                                ((0x000007FF&(data))>>0)


#define TVE_I_COLORBAR_HPOS                                                          0x18018074
#define TVE_I_COLORBAR_HPOS_reg_addr                                                 "0xB8018074"
#define TVE_I_COLORBAR_HPOS_reg                                                      0xB8018074
#define set_TVE_I_COLORBAR_HPOS_reg(data)   (*((volatile unsigned int*) TVE_I_COLORBAR_HPOS_reg)=data)
#define get_TVE_I_COLORBAR_HPOS_reg   (*((volatile unsigned int*) TVE_I_COLORBAR_HPOS_reg))
#define TVE_I_COLORBAR_HPOS_inst_adr                                                 "0x001D"
#define TVE_I_COLORBAR_HPOS_inst                                                     0x001D
#define TVE_I_COLORBAR_HPOS_write_en2_shift                                          (21)
#define TVE_I_COLORBAR_HPOS_write_en2_mask                                           (0x00200000)
#define TVE_I_COLORBAR_HPOS_write_en2(data)                                          (0x00200000&((data)<<21))
#define TVE_I_COLORBAR_HPOS_write_en2_src(data)                                      ((0x00200000&(data))>>21)
#define TVE_I_COLORBAR_HPOS_get_write_en2(data)                                      ((0x00200000&(data))>>21)
#define TVE_I_COLORBAR_HPOS_i_h_width_shift                                          (11)
#define TVE_I_COLORBAR_HPOS_i_h_width_mask                                           (0x001FF800)
#define TVE_I_COLORBAR_HPOS_i_h_width(data)                                          (0x001FF800&((data)<<11))
#define TVE_I_COLORBAR_HPOS_i_h_width_src(data)                                      ((0x001FF800&(data))>>11)
#define TVE_I_COLORBAR_HPOS_get_i_h_width(data)                                      ((0x001FF800&(data))>>11)
#define TVE_I_COLORBAR_HPOS_write_en1_shift                                          (10)
#define TVE_I_COLORBAR_HPOS_write_en1_mask                                           (0x00000400)
#define TVE_I_COLORBAR_HPOS_write_en1(data)                                          (0x00000400&((data)<<10))
#define TVE_I_COLORBAR_HPOS_write_en1_src(data)                                      ((0x00000400&(data))>>10)
#define TVE_I_COLORBAR_HPOS_get_write_en1(data)                                      ((0x00000400&(data))>>10)
#define TVE_I_COLORBAR_HPOS_i_h_st_pos_shift                                         (0)
#define TVE_I_COLORBAR_HPOS_i_h_st_pos_mask                                          (0x000003FF)
#define TVE_I_COLORBAR_HPOS_i_h_st_pos(data)                                         (0x000003FF&((data)<<0))
#define TVE_I_COLORBAR_HPOS_i_h_st_pos_src(data)                                     ((0x000003FF&(data))>>0)
#define TVE_I_COLORBAR_HPOS_get_i_h_st_pos(data)                                     ((0x000003FF&(data))>>0)


#define TVE_P_COLORBAR_HPOS                                                          0x18018078
#define TVE_P_COLORBAR_HPOS_reg_addr                                                 "0xB8018078"
#define TVE_P_COLORBAR_HPOS_reg                                                      0xB8018078
#define set_TVE_P_COLORBAR_HPOS_reg(data)   (*((volatile unsigned int*) TVE_P_COLORBAR_HPOS_reg)=data)
#define get_TVE_P_COLORBAR_HPOS_reg   (*((volatile unsigned int*) TVE_P_COLORBAR_HPOS_reg))
#define TVE_P_COLORBAR_HPOS_inst_adr                                                 "0x001E"
#define TVE_P_COLORBAR_HPOS_inst                                                     0x001E
#define TVE_P_COLORBAR_HPOS_write_en2_shift                                          (21)
#define TVE_P_COLORBAR_HPOS_write_en2_mask                                           (0x00200000)
#define TVE_P_COLORBAR_HPOS_write_en2(data)                                          (0x00200000&((data)<<21))
#define TVE_P_COLORBAR_HPOS_write_en2_src(data)                                      ((0x00200000&(data))>>21)
#define TVE_P_COLORBAR_HPOS_get_write_en2(data)                                      ((0x00200000&(data))>>21)
#define TVE_P_COLORBAR_HPOS_p_h_width_shift                                          (11)
#define TVE_P_COLORBAR_HPOS_p_h_width_mask                                           (0x001FF800)
#define TVE_P_COLORBAR_HPOS_p_h_width(data)                                          (0x001FF800&((data)<<11))
#define TVE_P_COLORBAR_HPOS_p_h_width_src(data)                                      ((0x001FF800&(data))>>11)
#define TVE_P_COLORBAR_HPOS_get_p_h_width(data)                                      ((0x001FF800&(data))>>11)
#define TVE_P_COLORBAR_HPOS_write_en1_shift                                          (10)
#define TVE_P_COLORBAR_HPOS_write_en1_mask                                           (0x00000400)
#define TVE_P_COLORBAR_HPOS_write_en1(data)                                          (0x00000400&((data)<<10))
#define TVE_P_COLORBAR_HPOS_write_en1_src(data)                                      ((0x00000400&(data))>>10)
#define TVE_P_COLORBAR_HPOS_get_write_en1(data)                                      ((0x00000400&(data))>>10)
#define TVE_P_COLORBAR_HPOS_p_h_st_pos_shift                                         (0)
#define TVE_P_COLORBAR_HPOS_p_h_st_pos_mask                                          (0x000003FF)
#define TVE_P_COLORBAR_HPOS_p_h_st_pos(data)                                         (0x000003FF&((data)<<0))
#define TVE_P_COLORBAR_HPOS_p_h_st_pos_src(data)                                     ((0x000003FF&(data))>>0)
#define TVE_P_COLORBAR_HPOS_get_p_h_st_pos(data)                                     ((0x000003FF&(data))>>0)


#define TVE_H_COLORBAR_HPOS                                                          0x1801807c
#define TVE_H_COLORBAR_HPOS_reg_addr                                                 "0xB801807C"
#define TVE_H_COLORBAR_HPOS_reg                                                      0xB801807C
#define set_TVE_H_COLORBAR_HPOS_reg(data)   (*((volatile unsigned int*) TVE_H_COLORBAR_HPOS_reg)=data)
#define get_TVE_H_COLORBAR_HPOS_reg   (*((volatile unsigned int*) TVE_H_COLORBAR_HPOS_reg))
#define TVE_H_COLORBAR_HPOS_inst_adr                                                 "0x001F"
#define TVE_H_COLORBAR_HPOS_inst                                                     0x001F
#define TVE_H_COLORBAR_HPOS_write_en2_shift                                          (21)
#define TVE_H_COLORBAR_HPOS_write_en2_mask                                           (0x00200000)
#define TVE_H_COLORBAR_HPOS_write_en2(data)                                          (0x00200000&((data)<<21))
#define TVE_H_COLORBAR_HPOS_write_en2_src(data)                                      ((0x00200000&(data))>>21)
#define TVE_H_COLORBAR_HPOS_get_write_en2(data)                                      ((0x00200000&(data))>>21)
#define TVE_H_COLORBAR_HPOS_p_h_width_shift                                          (11)
#define TVE_H_COLORBAR_HPOS_p_h_width_mask                                           (0x001FF800)
#define TVE_H_COLORBAR_HPOS_p_h_width(data)                                          (0x001FF800&((data)<<11))
#define TVE_H_COLORBAR_HPOS_p_h_width_src(data)                                      ((0x001FF800&(data))>>11)
#define TVE_H_COLORBAR_HPOS_get_p_h_width(data)                                      ((0x001FF800&(data))>>11)
#define TVE_H_COLORBAR_HPOS_write_en1_shift                                          (10)
#define TVE_H_COLORBAR_HPOS_write_en1_mask                                           (0x00000400)
#define TVE_H_COLORBAR_HPOS_write_en1(data)                                          (0x00000400&((data)<<10))
#define TVE_H_COLORBAR_HPOS_write_en1_src(data)                                      ((0x00000400&(data))>>10)
#define TVE_H_COLORBAR_HPOS_get_write_en1(data)                                      ((0x00000400&(data))>>10)
#define TVE_H_COLORBAR_HPOS_p_h_st_pos_shift                                         (0)
#define TVE_H_COLORBAR_HPOS_p_h_st_pos_mask                                          (0x000003FF)
#define TVE_H_COLORBAR_HPOS_p_h_st_pos(data)                                         (0x000003FF&((data)<<0))
#define TVE_H_COLORBAR_HPOS_p_h_st_pos_src(data)                                     ((0x000003FF&(data))>>0)
#define TVE_H_COLORBAR_HPOS_get_p_h_st_pos(data)                                     ((0x000003FF&(data))>>0)


#define TVE_COMP_VSYNC_HPOS                                                          0x18018080
#define TVE_COMP_VSYNC_HPOS_reg_addr                                                 "0xB8018080"
#define TVE_COMP_VSYNC_HPOS_reg                                                      0xB8018080
#define set_TVE_COMP_VSYNC_HPOS_reg(data)   (*((volatile unsigned int*) TVE_COMP_VSYNC_HPOS_reg)=data)
#define get_TVE_COMP_VSYNC_HPOS_reg   (*((volatile unsigned int*) TVE_COMP_VSYNC_HPOS_reg))
#define TVE_COMP_VSYNC_HPOS_inst_adr                                                 "0x0020"
#define TVE_COMP_VSYNC_HPOS_inst                                                     0x0020
#define TVE_COMP_VSYNC_HPOS_write_en3_shift                                          (29)
#define TVE_COMP_VSYNC_HPOS_write_en3_mask                                           (0x20000000)
#define TVE_COMP_VSYNC_HPOS_write_en3(data)                                          (0x20000000&((data)<<29))
#define TVE_COMP_VSYNC_HPOS_write_en3_src(data)                                      ((0x20000000&(data))>>29)
#define TVE_COMP_VSYNC_HPOS_get_write_en3(data)                                      ((0x20000000&(data))>>29)
#define TVE_COMP_VSYNC_HPOS_negsyncst_shift                                          (20)
#define TVE_COMP_VSYNC_HPOS_negsyncst_mask                                           (0x1FF00000)
#define TVE_COMP_VSYNC_HPOS_negsyncst(data)                                          (0x1FF00000&((data)<<20))
#define TVE_COMP_VSYNC_HPOS_negsyncst_src(data)                                      ((0x1FF00000&(data))>>20)
#define TVE_COMP_VSYNC_HPOS_get_negsyncst(data)                                      ((0x1FF00000&(data))>>20)
#define TVE_COMP_VSYNC_HPOS_write_en2_shift                                          (19)
#define TVE_COMP_VSYNC_HPOS_write_en2_mask                                           (0x00080000)
#define TVE_COMP_VSYNC_HPOS_write_en2(data)                                          (0x00080000&((data)<<19))
#define TVE_COMP_VSYNC_HPOS_write_en2_src(data)                                      ((0x00080000&(data))>>19)
#define TVE_COMP_VSYNC_HPOS_get_write_en2(data)                                      ((0x00080000&(data))>>19)
#define TVE_COMP_VSYNC_HPOS_possyncst_shift                                          (10)
#define TVE_COMP_VSYNC_HPOS_possyncst_mask                                           (0x0007FC00)
#define TVE_COMP_VSYNC_HPOS_possyncst(data)                                          (0x0007FC00&((data)<<10))
#define TVE_COMP_VSYNC_HPOS_possyncst_src(data)                                      ((0x0007FC00&(data))>>10)
#define TVE_COMP_VSYNC_HPOS_get_possyncst(data)                                      ((0x0007FC00&(data))>>10)
#define TVE_COMP_VSYNC_HPOS_write_en1_shift                                          (9)
#define TVE_COMP_VSYNC_HPOS_write_en1_mask                                           (0x00000200)
#define TVE_COMP_VSYNC_HPOS_write_en1(data)                                          (0x00000200&((data)<<9))
#define TVE_COMP_VSYNC_HPOS_write_en1_src(data)                                      ((0x00000200&(data))>>9)
#define TVE_COMP_VSYNC_HPOS_get_write_en1(data)                                      ((0x00000200&(data))>>9)
#define TVE_COMP_VSYNC_HPOS_syncend_shift                                            (0)
#define TVE_COMP_VSYNC_HPOS_syncend_mask                                             (0x000001FF)
#define TVE_COMP_VSYNC_HPOS_syncend(data)                                            (0x000001FF&((data)<<0))
#define TVE_COMP_VSYNC_HPOS_syncend_src(data)                                        ((0x000001FF&(data))>>0)
#define TVE_COMP_VSYNC_HPOS_get_syncend(data)                                        ((0x000001FF&(data))>>0)


#define TVE_COMP_SER_CTRL                                                            0x18018084
#define TVE_COMP_SER_CTRL_reg_addr                                                   "0xB8018084"
#define TVE_COMP_SER_CTRL_reg                                                        0xB8018084
#define set_TVE_COMP_SER_CTRL_reg(data)   (*((volatile unsigned int*) TVE_COMP_SER_CTRL_reg)=data)
#define get_TVE_COMP_SER_CTRL_reg   (*((volatile unsigned int*) TVE_COMP_SER_CTRL_reg))
#define TVE_COMP_SER_CTRL_inst_adr                                                   "0x0021"
#define TVE_COMP_SER_CTRL_inst                                                       0x0021
#define TVE_COMP_SER_CTRL_1080i_ebl_shift                                            (0)
#define TVE_COMP_SER_CTRL_1080i_ebl_mask                                             (0x00000001)
#define TVE_COMP_SER_CTRL_1080i_ebl(data)                                            (0x00000001&((data)<<0))
#define TVE_COMP_SER_CTRL_1080i_ebl_src(data)                                        ((0x00000001&(data))>>0)
#define TVE_COMP_SER_CTRL_get_1080i_ebl(data)                                        ((0x00000001&(data))>>0)


#define TVE_COMP_SER_HPOS                                                            0x18018088
#define TVE_COMP_SER_HPOS_reg_addr                                                   "0xB8018088"
#define TVE_COMP_SER_HPOS_reg                                                        0xB8018088
#define set_TVE_COMP_SER_HPOS_reg(data)   (*((volatile unsigned int*) TVE_COMP_SER_HPOS_reg)=data)
#define get_TVE_COMP_SER_HPOS_reg   (*((volatile unsigned int*) TVE_COMP_SER_HPOS_reg))
#define TVE_COMP_SER_HPOS_inst_adr                                                   "0x0022"
#define TVE_COMP_SER_HPOS_inst                                                       0x0022
#define TVE_COMP_SER_HPOS_write_en2_shift                                            (27)
#define TVE_COMP_SER_HPOS_write_en2_mask                                             (0x08000000)
#define TVE_COMP_SER_HPOS_write_en2(data)                                            (0x08000000&((data)<<27))
#define TVE_COMP_SER_HPOS_write_en2_src(data)                                        ((0x08000000&(data))>>27)
#define TVE_COMP_SER_HPOS_get_write_en2(data)                                        ((0x08000000&(data))>>27)
#define TVE_COMP_SER_HPOS_ser_hstart_shift                                           (14)
#define TVE_COMP_SER_HPOS_ser_hstart_mask                                            (0x07FFC000)
#define TVE_COMP_SER_HPOS_ser_hstart(data)                                           (0x07FFC000&((data)<<14))
#define TVE_COMP_SER_HPOS_ser_hstart_src(data)                                       ((0x07FFC000&(data))>>14)
#define TVE_COMP_SER_HPOS_get_ser_hstart(data)                                       ((0x07FFC000&(data))>>14)
#define TVE_COMP_SER_HPOS_write_en1_shift                                            (13)
#define TVE_COMP_SER_HPOS_write_en1_mask                                             (0x00002000)
#define TVE_COMP_SER_HPOS_write_en1(data)                                            (0x00002000&((data)<<13))
#define TVE_COMP_SER_HPOS_write_en1_src(data)                                        ((0x00002000&(data))>>13)
#define TVE_COMP_SER_HPOS_get_write_en1(data)                                        ((0x00002000&(data))>>13)
#define TVE_COMP_SER_HPOS_ser_hend_shift                                             (0)
#define TVE_COMP_SER_HPOS_ser_hend_mask                                              (0x00001FFF)
#define TVE_COMP_SER_HPOS_ser_hend(data)                                             (0x00001FFF&((data)<<0))
#define TVE_COMP_SER_HPOS_ser_hend_src(data)                                         ((0x00001FFF&(data))>>0)
#define TVE_COMP_SER_HPOS_get_ser_hend(data)                                         ((0x00001FFF&(data))>>0)


#define TVE_COMP_SER_VPOS                                                            0x1801808c
#define TVE_COMP_SER_VPOS_reg_addr                                                   "0xB801808C"
#define TVE_COMP_SER_VPOS_reg                                                        0xB801808C
#define set_TVE_COMP_SER_VPOS_reg(data)   (*((volatile unsigned int*) TVE_COMP_SER_VPOS_reg)=data)
#define get_TVE_COMP_SER_VPOS_reg   (*((volatile unsigned int*) TVE_COMP_SER_VPOS_reg))
#define TVE_COMP_SER_VPOS_inst_adr                                                   "0x0023"
#define TVE_COMP_SER_VPOS_inst                                                       0x0023
#define TVE_COMP_SER_VPOS_write_en2_shift                                            (11)
#define TVE_COMP_SER_VPOS_write_en2_mask                                             (0x00000800)
#define TVE_COMP_SER_VPOS_write_en2(data)                                            (0x00000800&((data)<<11))
#define TVE_COMP_SER_VPOS_write_en2_src(data)                                        ((0x00000800&(data))>>11)
#define TVE_COMP_SER_VPOS_get_write_en2(data)                                        ((0x00000800&(data))>>11)
#define TVE_COMP_SER_VPOS_ser_vstart_shift                                           (6)
#define TVE_COMP_SER_VPOS_ser_vstart_mask                                            (0x000007C0)
#define TVE_COMP_SER_VPOS_ser_vstart(data)                                           (0x000007C0&((data)<<6))
#define TVE_COMP_SER_VPOS_ser_vstart_src(data)                                       ((0x000007C0&(data))>>6)
#define TVE_COMP_SER_VPOS_get_ser_vstart(data)                                       ((0x000007C0&(data))>>6)
#define TVE_COMP_SER_VPOS_write_en1_shift                                            (5)
#define TVE_COMP_SER_VPOS_write_en1_mask                                             (0x00000020)
#define TVE_COMP_SER_VPOS_write_en1(data)                                            (0x00000020&((data)<<5))
#define TVE_COMP_SER_VPOS_write_en1_src(data)                                        ((0x00000020&(data))>>5)
#define TVE_COMP_SER_VPOS_get_write_en1(data)                                        ((0x00000020&(data))>>5)
#define TVE_COMP_SER_VPOS_ser_vend_shift                                             (0)
#define TVE_COMP_SER_VPOS_ser_vend_mask                                              (0x0000001F)
#define TVE_COMP_SER_VPOS_ser_vend(data)                                             (0x0000001F&((data)<<0))
#define TVE_COMP_SER_VPOS_ser_vend_src(data)                                         ((0x0000001F&(data))>>0)
#define TVE_COMP_SER_VPOS_get_ser_vend(data)                                         ((0x0000001F&(data))>>0)


#define TVE_COMP_DSYNC_VPOS                                                          0x18018090
#define TVE_COMP_DSYNC_VPOS_reg_addr                                                 "0xB8018090"
#define TVE_COMP_DSYNC_VPOS_reg                                                      0xB8018090
#define set_TVE_COMP_DSYNC_VPOS_reg(data)   (*((volatile unsigned int*) TVE_COMP_DSYNC_VPOS_reg)=data)
#define get_TVE_COMP_DSYNC_VPOS_reg   (*((volatile unsigned int*) TVE_COMP_DSYNC_VPOS_reg))
#define TVE_COMP_DSYNC_VPOS_inst_adr                                                 "0x0024"
#define TVE_COMP_DSYNC_VPOS_inst                                                     0x0024
#define TVE_COMP_DSYNC_VPOS_write_en4_shift                                          (31)
#define TVE_COMP_DSYNC_VPOS_write_en4_mask                                           (0x80000000)
#define TVE_COMP_DSYNC_VPOS_write_en4(data)                                          (0x80000000&((data)<<31))
#define TVE_COMP_DSYNC_VPOS_write_en4_src(data)                                      ((0x80000000&(data))>>31)
#define TVE_COMP_DSYNC_VPOS_get_write_en4(data)                                      ((0x80000000&(data))>>31)
#define TVE_COMP_DSYNC_VPOS_dsync_b_vstart_shift                                     (21)
#define TVE_COMP_DSYNC_VPOS_dsync_b_vstart_mask                                      (0x7FE00000)
#define TVE_COMP_DSYNC_VPOS_dsync_b_vstart(data)                                     (0x7FE00000&((data)<<21))
#define TVE_COMP_DSYNC_VPOS_dsync_b_vstart_src(data)                                 ((0x7FE00000&(data))>>21)
#define TVE_COMP_DSYNC_VPOS_get_dsync_b_vstart(data)                                 ((0x7FE00000&(data))>>21)
#define TVE_COMP_DSYNC_VPOS_write_en3_shift                                          (20)
#define TVE_COMP_DSYNC_VPOS_write_en3_mask                                           (0x00100000)
#define TVE_COMP_DSYNC_VPOS_write_en3(data)                                          (0x00100000&((data)<<20))
#define TVE_COMP_DSYNC_VPOS_write_en3_src(data)                                      ((0x00100000&(data))>>20)
#define TVE_COMP_DSYNC_VPOS_get_write_en3(data)                                      ((0x00100000&(data))>>20)
#define TVE_COMP_DSYNC_VPOS_dsync_b_vend_shift                                       (10)
#define TVE_COMP_DSYNC_VPOS_dsync_b_vend_mask                                        (0x000FFC00)
#define TVE_COMP_DSYNC_VPOS_dsync_b_vend(data)                                       (0x000FFC00&((data)<<10))
#define TVE_COMP_DSYNC_VPOS_dsync_b_vend_src(data)                                   ((0x000FFC00&(data))>>10)
#define TVE_COMP_DSYNC_VPOS_get_dsync_b_vend(data)                                   ((0x000FFC00&(data))>>10)
#define TVE_COMP_DSYNC_VPOS_write_en2_shift                                          (9)
#define TVE_COMP_DSYNC_VPOS_write_en2_mask                                           (0x00000200)
#define TVE_COMP_DSYNC_VPOS_write_en2(data)                                          (0x00000200&((data)<<9))
#define TVE_COMP_DSYNC_VPOS_write_en2_src(data)                                      ((0x00000200&(data))>>9)
#define TVE_COMP_DSYNC_VPOS_get_write_en2(data)                                      ((0x00000200&(data))>>9)
#define TVE_COMP_DSYNC_VPOS_dsync_t_vstart_shift                                     (5)
#define TVE_COMP_DSYNC_VPOS_dsync_t_vstart_mask                                      (0x000001E0)
#define TVE_COMP_DSYNC_VPOS_dsync_t_vstart(data)                                     (0x000001E0&((data)<<5))
#define TVE_COMP_DSYNC_VPOS_dsync_t_vstart_src(data)                                 ((0x000001E0&(data))>>5)
#define TVE_COMP_DSYNC_VPOS_get_dsync_t_vstart(data)                                 ((0x000001E0&(data))>>5)
#define TVE_COMP_DSYNC_VPOS_write_en1_shift                                          (4)
#define TVE_COMP_DSYNC_VPOS_write_en1_mask                                           (0x00000010)
#define TVE_COMP_DSYNC_VPOS_write_en1(data)                                          (0x00000010&((data)<<4))
#define TVE_COMP_DSYNC_VPOS_write_en1_src(data)                                      ((0x00000010&(data))>>4)
#define TVE_COMP_DSYNC_VPOS_get_write_en1(data)                                      ((0x00000010&(data))>>4)
#define TVE_COMP_DSYNC_VPOS_dsync_t_vend_shift                                       (0)
#define TVE_COMP_DSYNC_VPOS_dsync_t_vend_mask                                        (0x0000000F)
#define TVE_COMP_DSYNC_VPOS_dsync_t_vend(data)                                       (0x0000000F&((data)<<0))
#define TVE_COMP_DSYNC_VPOS_dsync_t_vend_src(data)                                   ((0x0000000F&(data))>>0)
#define TVE_COMP_DSYNC_VPOS_get_dsync_t_vend(data)                                   ((0x0000000F&(data))>>0)


#define TVE_VGA_HSYNC_HPOS                                                           0x18018094
#define TVE_VGA_HSYNC_HPOS_reg_addr                                                  "0xB8018094"
#define TVE_VGA_HSYNC_HPOS_reg                                                       0xB8018094
#define set_TVE_VGA_HSYNC_HPOS_reg(data)   (*((volatile unsigned int*) TVE_VGA_HSYNC_HPOS_reg)=data)
#define get_TVE_VGA_HSYNC_HPOS_reg   (*((volatile unsigned int*) TVE_VGA_HSYNC_HPOS_reg))
#define TVE_VGA_HSYNC_HPOS_inst_adr                                                  "0x0025"
#define TVE_VGA_HSYNC_HPOS_inst                                                      0x0025
#define TVE_VGA_HSYNC_HPOS_write_en2_shift                                           (27)
#define TVE_VGA_HSYNC_HPOS_write_en2_mask                                            (0x08000000)
#define TVE_VGA_HSYNC_HPOS_write_en2(data)                                           (0x08000000&((data)<<27))
#define TVE_VGA_HSYNC_HPOS_write_en2_src(data)                                       ((0x08000000&(data))>>27)
#define TVE_VGA_HSYNC_HPOS_get_write_en2(data)                                       ((0x08000000&(data))>>27)
#define TVE_VGA_HSYNC_HPOS_hs_start_shift                                            (14)
#define TVE_VGA_HSYNC_HPOS_hs_start_mask                                             (0x07FFC000)
#define TVE_VGA_HSYNC_HPOS_hs_start(data)                                            (0x07FFC000&((data)<<14))
#define TVE_VGA_HSYNC_HPOS_hs_start_src(data)                                        ((0x07FFC000&(data))>>14)
#define TVE_VGA_HSYNC_HPOS_get_hs_start(data)                                        ((0x07FFC000&(data))>>14)
#define TVE_VGA_HSYNC_HPOS_write_en1_shift                                           (13)
#define TVE_VGA_HSYNC_HPOS_write_en1_mask                                            (0x00002000)
#define TVE_VGA_HSYNC_HPOS_write_en1(data)                                           (0x00002000&((data)<<13))
#define TVE_VGA_HSYNC_HPOS_write_en1_src(data)                                       ((0x00002000&(data))>>13)
#define TVE_VGA_HSYNC_HPOS_get_write_en1(data)                                       ((0x00002000&(data))>>13)
#define TVE_VGA_HSYNC_HPOS_hs_end_shift                                              (0)
#define TVE_VGA_HSYNC_HPOS_hs_end_mask                                               (0x00001FFF)
#define TVE_VGA_HSYNC_HPOS_hs_end(data)                                              (0x00001FFF&((data)<<0))
#define TVE_VGA_HSYNC_HPOS_hs_end_src(data)                                          ((0x00001FFF&(data))>>0)
#define TVE_VGA_HSYNC_HPOS_get_hs_end(data)                                          ((0x00001FFF&(data))>>0)


#define TVE_VGA_VSYNC_ST_POS_0                                                       0x18018098
#define TVE_VGA_VSYNC_ST_POS_1                                                       0x1801809C
#define TVE_VGA_VSYNC_ST_POS_0_reg_addr                                              "0xB8018098"
#define TVE_VGA_VSYNC_ST_POS_1_reg_addr                                              "0xB801809C"
#define TVE_VGA_VSYNC_ST_POS_0_reg                                                   0xB8018098
#define TVE_VGA_VSYNC_ST_POS_1_reg                                                   0xB801809C
#define set_TVE_VGA_VSYNC_ST_POS_0_reg(data)   (*((volatile unsigned int*) TVE_VGA_VSYNC_ST_POS_0_reg)=data)
#define set_TVE_VGA_VSYNC_ST_POS_1_reg(data)   (*((volatile unsigned int*) TVE_VGA_VSYNC_ST_POS_1_reg)=data)
#define get_TVE_VGA_VSYNC_ST_POS_0_reg   (*((volatile unsigned int*) TVE_VGA_VSYNC_ST_POS_0_reg))
#define get_TVE_VGA_VSYNC_ST_POS_1_reg   (*((volatile unsigned int*) TVE_VGA_VSYNC_ST_POS_1_reg))
#define TVE_VGA_VSYNC_ST_POS_0_inst_adr                                              "0x0026"
#define TVE_VGA_VSYNC_ST_POS_1_inst_adr                                              "0x0027"
#define TVE_VGA_VSYNC_ST_POS_0_inst                                                  0x0026
#define TVE_VGA_VSYNC_ST_POS_1_inst                                                  0x0027
#define TVE_VGA_VSYNC_ST_POS_write_en2_shift                                         (25)
#define TVE_VGA_VSYNC_ST_POS_write_en2_mask                                          (0x02000000)
#define TVE_VGA_VSYNC_ST_POS_write_en2(data)                                         (0x02000000&((data)<<25))
#define TVE_VGA_VSYNC_ST_POS_write_en2_src(data)                                     ((0x02000000&(data))>>25)
#define TVE_VGA_VSYNC_ST_POS_get_write_en2(data)                                     ((0x02000000&(data))>>25)
#define TVE_VGA_VSYNC_ST_POS_vs_st_posv_shift                                        (14)
#define TVE_VGA_VSYNC_ST_POS_vs_st_posv_mask                                         (0x01FFC000)
#define TVE_VGA_VSYNC_ST_POS_vs_st_posv(data)                                        (0x01FFC000&((data)<<14))
#define TVE_VGA_VSYNC_ST_POS_vs_st_posv_src(data)                                    ((0x01FFC000&(data))>>14)
#define TVE_VGA_VSYNC_ST_POS_get_vs_st_posv(data)                                    ((0x01FFC000&(data))>>14)
#define TVE_VGA_VSYNC_ST_POS_write_en1_shift                                         (13)
#define TVE_VGA_VSYNC_ST_POS_write_en1_mask                                          (0x00002000)
#define TVE_VGA_VSYNC_ST_POS_write_en1(data)                                         (0x00002000&((data)<<13))
#define TVE_VGA_VSYNC_ST_POS_write_en1_src(data)                                     ((0x00002000&(data))>>13)
#define TVE_VGA_VSYNC_ST_POS_get_write_en1(data)                                     ((0x00002000&(data))>>13)
#define TVE_VGA_VSYNC_ST_POS_vs_st_posh_shift                                        (0)
#define TVE_VGA_VSYNC_ST_POS_vs_st_posh_mask                                         (0x00001FFF)
#define TVE_VGA_VSYNC_ST_POS_vs_st_posh(data)                                        (0x00001FFF&((data)<<0))
#define TVE_VGA_VSYNC_ST_POS_vs_st_posh_src(data)                                    ((0x00001FFF&(data))>>0)
#define TVE_VGA_VSYNC_ST_POS_get_vs_st_posh(data)                                    ((0x00001FFF&(data))>>0)


#define TVE_VGA_VSYNC_END_POS_0                                                      0x180180A0
#define TVE_VGA_VSYNC_END_POS_1                                                      0x180180A4
#define TVE_VGA_VSYNC_END_POS_0_reg_addr                                             "0xB80180A0"
#define TVE_VGA_VSYNC_END_POS_1_reg_addr                                             "0xB80180A4"
#define TVE_VGA_VSYNC_END_POS_0_reg                                                  0xB80180A0
#define TVE_VGA_VSYNC_END_POS_1_reg                                                  0xB80180A4
#define set_TVE_VGA_VSYNC_END_POS_0_reg(data)   (*((volatile unsigned int*) TVE_VGA_VSYNC_END_POS_0_reg)=data)
#define set_TVE_VGA_VSYNC_END_POS_1_reg(data)   (*((volatile unsigned int*) TVE_VGA_VSYNC_END_POS_1_reg)=data)
#define get_TVE_VGA_VSYNC_END_POS_0_reg   (*((volatile unsigned int*) TVE_VGA_VSYNC_END_POS_0_reg))
#define get_TVE_VGA_VSYNC_END_POS_1_reg   (*((volatile unsigned int*) TVE_VGA_VSYNC_END_POS_1_reg))
#define TVE_VGA_VSYNC_END_POS_0_inst_adr                                             "0x0028"
#define TVE_VGA_VSYNC_END_POS_1_inst_adr                                             "0x0029"
#define TVE_VGA_VSYNC_END_POS_0_inst                                                 0x0028
#define TVE_VGA_VSYNC_END_POS_1_inst                                                 0x0029
#define TVE_VGA_VSYNC_END_POS_write_en2_shift                                        (25)
#define TVE_VGA_VSYNC_END_POS_write_en2_mask                                         (0x02000000)
#define TVE_VGA_VSYNC_END_POS_write_en2(data)                                        (0x02000000&((data)<<25))
#define TVE_VGA_VSYNC_END_POS_write_en2_src(data)                                    ((0x02000000&(data))>>25)
#define TVE_VGA_VSYNC_END_POS_get_write_en2(data)                                    ((0x02000000&(data))>>25)
#define TVE_VGA_VSYNC_END_POS_vs_end_posv_shift                                      (14)
#define TVE_VGA_VSYNC_END_POS_vs_end_posv_mask                                       (0x01FFC000)
#define TVE_VGA_VSYNC_END_POS_vs_end_posv(data)                                      (0x01FFC000&((data)<<14))
#define TVE_VGA_VSYNC_END_POS_vs_end_posv_src(data)                                  ((0x01FFC000&(data))>>14)
#define TVE_VGA_VSYNC_END_POS_get_vs_end_posv(data)                                  ((0x01FFC000&(data))>>14)
#define TVE_VGA_VSYNC_END_POS_write_en1_shift                                        (13)
#define TVE_VGA_VSYNC_END_POS_write_en1_mask                                         (0x00002000)
#define TVE_VGA_VSYNC_END_POS_write_en1(data)                                        (0x00002000&((data)<<13))
#define TVE_VGA_VSYNC_END_POS_write_en1_src(data)                                    ((0x00002000&(data))>>13)
#define TVE_VGA_VSYNC_END_POS_get_write_en1(data)                                    ((0x00002000&(data))>>13)
#define TVE_VGA_VSYNC_END_POS_vs_end_posh_shift                                      (0)
#define TVE_VGA_VSYNC_END_POS_vs_end_posh_mask                                       (0x00001FFF)
#define TVE_VGA_VSYNC_END_POS_vs_end_posh(data)                                      (0x00001FFF&((data)<<0))
#define TVE_VGA_VSYNC_END_POS_vs_end_posh_src(data)                                  ((0x00001FFF&(data))>>0)
#define TVE_VGA_VSYNC_END_POS_get_vs_end_posh(data)                                  ((0x00001FFF&(data))>>0)


#define TVE_IP_VSYNCPOS                                                              0x180180b0
#define TVE_IP_VSYNCPOS_reg_addr                                                     "0xB80180B0"
#define TVE_IP_VSYNCPOS_reg                                                          0xB80180B0
#define set_TVE_IP_VSYNCPOS_reg(data)   (*((volatile unsigned int*) TVE_IP_VSYNCPOS_reg)=data)
#define get_TVE_IP_VSYNCPOS_reg   (*((volatile unsigned int*) TVE_IP_VSYNCPOS_reg))
#define TVE_IP_VSYNCPOS_inst_adr                                                     "0x002C"
#define TVE_IP_VSYNCPOS_inst                                                         0x002C
#define TVE_IP_VSYNCPOS_write_en2_shift                                              (21)
#define TVE_IP_VSYNCPOS_write_en2_mask                                               (0x00200000)
#define TVE_IP_VSYNCPOS_write_en2(data)                                              (0x00200000&((data)<<21))
#define TVE_IP_VSYNCPOS_write_en2_src(data)                                          ((0x00200000&(data))>>21)
#define TVE_IP_VSYNCPOS_get_write_en2(data)                                          ((0x00200000&(data))>>21)
#define TVE_IP_VSYNCPOS_ip_vsync_pos1_shift                                          (11)
#define TVE_IP_VSYNCPOS_ip_vsync_pos1_mask                                           (0x001FF800)
#define TVE_IP_VSYNCPOS_ip_vsync_pos1(data)                                          (0x001FF800&((data)<<11))
#define TVE_IP_VSYNCPOS_ip_vsync_pos1_src(data)                                      ((0x001FF800&(data))>>11)
#define TVE_IP_VSYNCPOS_get_ip_vsync_pos1(data)                                      ((0x001FF800&(data))>>11)
#define TVE_IP_VSYNCPOS_write_en1_shift                                              (10)
#define TVE_IP_VSYNCPOS_write_en1_mask                                               (0x00000400)
#define TVE_IP_VSYNCPOS_write_en1(data)                                              (0x00000400&((data)<<10))
#define TVE_IP_VSYNCPOS_write_en1_src(data)                                          ((0x00000400&(data))>>10)
#define TVE_IP_VSYNCPOS_get_write_en1(data)                                          ((0x00000400&(data))>>10)
#define TVE_IP_VSYNCPOS_ip_vsync_pos2_shift                                          (0)
#define TVE_IP_VSYNCPOS_ip_vsync_pos2_mask                                           (0x000003FF)
#define TVE_IP_VSYNCPOS_ip_vsync_pos2(data)                                          (0x000003FF&((data)<<0))
#define TVE_IP_VSYNCPOS_ip_vsync_pos2_src(data)                                      ((0x000003FF&(data))>>0)
#define TVE_IP_VSYNCPOS_get_ip_vsync_pos2(data)                                      ((0x000003FF&(data))>>0)


#define TVE_IP_HSYNCPOS                                                              0x180180b4
#define TVE_IP_HSYNCPOS_reg_addr                                                     "0xB80180B4"
#define TVE_IP_HSYNCPOS_reg                                                          0xB80180B4
#define set_TVE_IP_HSYNCPOS_reg(data)   (*((volatile unsigned int*) TVE_IP_HSYNCPOS_reg)=data)
#define get_TVE_IP_HSYNCPOS_reg   (*((volatile unsigned int*) TVE_IP_HSYNCPOS_reg))
#define TVE_IP_HSYNCPOS_inst_adr                                                     "0x002D"
#define TVE_IP_HSYNCPOS_inst                                                         0x002D
#define TVE_IP_HSYNCPOS_hthr_shift                                                   (0)
#define TVE_IP_HSYNCPOS_hthr_mask                                                    (0x000007FF)
#define TVE_IP_HSYNCPOS_hthr(data)                                                   (0x000007FF&((data)<<0))
#define TVE_IP_HSYNCPOS_hthr_src(data)                                               ((0x000007FF&(data))>>0)
#define TVE_IP_HSYNCPOS_get_hthr(data)                                               ((0x000007FF&(data))>>0)


#define TVE_HDMI_ST                                                                  0x180180b8
#define TVE_HDMI_ST_reg_addr                                                         "0xB80180B8"
#define TVE_HDMI_ST_reg                                                              0xB80180B8
#define set_TVE_HDMI_ST_reg(data)   (*((volatile unsigned int*) TVE_HDMI_ST_reg)=data)
#define get_TVE_HDMI_ST_reg   (*((volatile unsigned int*) TVE_HDMI_ST_reg))
#define TVE_HDMI_ST_inst_adr                                                         "0x002E"
#define TVE_HDMI_ST_inst                                                             0x002E
#define TVE_HDMI_ST_write_en4_shift                                                  (29)
#define TVE_HDMI_ST_write_en4_mask                                                   (0x20000000)
#define TVE_HDMI_ST_write_en4(data)                                                  (0x20000000&((data)<<29))
#define TVE_HDMI_ST_write_en4_src(data)                                              ((0x20000000&(data))>>29)
#define TVE_HDMI_ST_get_write_en4(data)                                              ((0x20000000&(data))>>29)
#define TVE_HDMI_ST_sync_en_shift                                                    (28)
#define TVE_HDMI_ST_sync_en_mask                                                     (0x10000000)
#define TVE_HDMI_ST_sync_en(data)                                                    (0x10000000&((data)<<28))
#define TVE_HDMI_ST_sync_en_src(data)                                                ((0x10000000&(data))>>28)
#define TVE_HDMI_ST_get_sync_en(data)                                                ((0x10000000&(data))>>28)
#define TVE_HDMI_ST_write_en3_shift                                                  (27)
#define TVE_HDMI_ST_write_en3_mask                                                   (0x08000000)
#define TVE_HDMI_ST_write_en3(data)                                                  (0x08000000&((data)<<27))
#define TVE_HDMI_ST_write_en3_src(data)                                              ((0x08000000&(data))>>27)
#define TVE_HDMI_ST_get_write_en3(data)                                              ((0x08000000&(data))>>27)
#define TVE_HDMI_ST_ch_sel_shift                                                     (26)
#define TVE_HDMI_ST_ch_sel_mask                                                      (0x04000000)
#define TVE_HDMI_ST_ch_sel(data)                                                     (0x04000000&((data)<<26))
#define TVE_HDMI_ST_ch_sel_src(data)                                                 ((0x04000000&(data))>>26)
#define TVE_HDMI_ST_get_ch_sel(data)                                                 ((0x04000000&(data))>>26)
#define TVE_HDMI_ST_write_en2_shift                                                  (25)
#define TVE_HDMI_ST_write_en2_mask                                                   (0x02000000)
#define TVE_HDMI_ST_write_en2(data)                                                  (0x02000000&((data)<<25))
#define TVE_HDMI_ST_write_en2_src(data)                                              ((0x02000000&(data))>>25)
#define TVE_HDMI_ST_get_write_en2(data)                                              ((0x02000000&(data))>>25)
#define TVE_HDMI_ST_vpos_shift                                                       (14)
#define TVE_HDMI_ST_vpos_mask                                                        (0x01FFC000)
#define TVE_HDMI_ST_vpos(data)                                                       (0x01FFC000&((data)<<14))
#define TVE_HDMI_ST_vpos_src(data)                                                   ((0x01FFC000&(data))>>14)
#define TVE_HDMI_ST_get_vpos(data)                                                   ((0x01FFC000&(data))>>14)
#define TVE_HDMI_ST_write_en1_shift                                                  (13)
#define TVE_HDMI_ST_write_en1_mask                                                   (0x00002000)
#define TVE_HDMI_ST_write_en1(data)                                                  (0x00002000&((data)<<13))
#define TVE_HDMI_ST_write_en1_src(data)                                              ((0x00002000&(data))>>13)
#define TVE_HDMI_ST_get_write_en1(data)                                              ((0x00002000&(data))>>13)
#define TVE_HDMI_ST_hpos_shift                                                       (0)
#define TVE_HDMI_ST_hpos_mask                                                        (0x00001FFF)
#define TVE_HDMI_ST_hpos(data)                                                       (0x00001FFF&((data)<<0))
#define TVE_HDMI_ST_hpos_src(data)                                                   ((0x00001FFF&(data))>>0)
#define TVE_HDMI_ST_get_hpos(data)                                                   ((0x00001FFF&(data))>>0)


#define TVE_HDMI_DISP_HS                                                             0x180180bc
#define TVE_HDMI_DISP_HS_reg_addr                                                    "0xB80180BC"
#define TVE_HDMI_DISP_HS_reg                                                         0xB80180BC
#define set_TVE_HDMI_DISP_HS_reg(data)   (*((volatile unsigned int*) TVE_HDMI_DISP_HS_reg)=data)
#define get_TVE_HDMI_DISP_HS_reg   (*((volatile unsigned int*) TVE_HDMI_DISP_HS_reg))
#define TVE_HDMI_DISP_HS_inst_adr                                                    "0x002F"
#define TVE_HDMI_DISP_HS_inst                                                        0x002F
#define TVE_HDMI_DISP_HS_write_en2_shift                                             (27)
#define TVE_HDMI_DISP_HS_write_en2_mask                                              (0x08000000)
#define TVE_HDMI_DISP_HS_write_en2(data)                                             (0x08000000&((data)<<27))
#define TVE_HDMI_DISP_HS_write_en2_src(data)                                         ((0x08000000&(data))>>27)
#define TVE_HDMI_DISP_HS_get_write_en2(data)                                         ((0x08000000&(data))>>27)
#define TVE_HDMI_DISP_HS_hs_start_shift                                              (14)
#define TVE_HDMI_DISP_HS_hs_start_mask                                               (0x07FFC000)
#define TVE_HDMI_DISP_HS_hs_start(data)                                              (0x07FFC000&((data)<<14))
#define TVE_HDMI_DISP_HS_hs_start_src(data)                                          ((0x07FFC000&(data))>>14)
#define TVE_HDMI_DISP_HS_get_hs_start(data)                                          ((0x07FFC000&(data))>>14)
#define TVE_HDMI_DISP_HS_write_en1_shift                                             (13)
#define TVE_HDMI_DISP_HS_write_en1_mask                                              (0x00002000)
#define TVE_HDMI_DISP_HS_write_en1(data)                                             (0x00002000&((data)<<13))
#define TVE_HDMI_DISP_HS_write_en1_src(data)                                         ((0x00002000&(data))>>13)
#define TVE_HDMI_DISP_HS_get_write_en1(data)                                         ((0x00002000&(data))>>13)
#define TVE_HDMI_DISP_HS_hs_end_shift                                                (0)
#define TVE_HDMI_DISP_HS_hs_end_mask                                                 (0x00001FFF)
#define TVE_HDMI_DISP_HS_hs_end(data)                                                (0x00001FFF&((data)<<0))
#define TVE_HDMI_DISP_HS_hs_end_src(data)                                            ((0x00001FFF&(data))>>0)
#define TVE_HDMI_DISP_HS_get_hs_end(data)                                            ((0x00001FFF&(data))>>0)


#define TVE_HDMI_DISP_VSST1                                                          0x180180c0
#define TVE_HDMI_DISP_VSST1_reg_addr                                                 "0xB80180C0"
#define TVE_HDMI_DISP_VSST1_reg                                                      0xB80180C0
#define set_TVE_HDMI_DISP_VSST1_reg(data)   (*((volatile unsigned int*) TVE_HDMI_DISP_VSST1_reg)=data)
#define get_TVE_HDMI_DISP_VSST1_reg   (*((volatile unsigned int*) TVE_HDMI_DISP_VSST1_reg))
#define TVE_HDMI_DISP_VSST1_inst_adr                                                 "0x0030"
#define TVE_HDMI_DISP_VSST1_inst                                                     0x0030
#define TVE_HDMI_DISP_VSST1_write_en2_shift                                          (25)
#define TVE_HDMI_DISP_VSST1_write_en2_mask                                           (0x02000000)
#define TVE_HDMI_DISP_VSST1_write_en2(data)                                          (0x02000000&((data)<<25))
#define TVE_HDMI_DISP_VSST1_write_en2_src(data)                                      ((0x02000000&(data))>>25)
#define TVE_HDMI_DISP_VSST1_get_write_en2(data)                                      ((0x02000000&(data))>>25)
#define TVE_HDMI_DISP_VSST1_vs_st_pos1v_shift                                        (14)
#define TVE_HDMI_DISP_VSST1_vs_st_pos1v_mask                                         (0x01FFC000)
#define TVE_HDMI_DISP_VSST1_vs_st_pos1v(data)                                        (0x01FFC000&((data)<<14))
#define TVE_HDMI_DISP_VSST1_vs_st_pos1v_src(data)                                    ((0x01FFC000&(data))>>14)
#define TVE_HDMI_DISP_VSST1_get_vs_st_pos1v(data)                                    ((0x01FFC000&(data))>>14)
#define TVE_HDMI_DISP_VSST1_write_en1_shift                                          (13)
#define TVE_HDMI_DISP_VSST1_write_en1_mask                                           (0x00002000)
#define TVE_HDMI_DISP_VSST1_write_en1(data)                                          (0x00002000&((data)<<13))
#define TVE_HDMI_DISP_VSST1_write_en1_src(data)                                      ((0x00002000&(data))>>13)
#define TVE_HDMI_DISP_VSST1_get_write_en1(data)                                      ((0x00002000&(data))>>13)
#define TVE_HDMI_DISP_VSST1_vs_st_pos1h_shift                                        (0)
#define TVE_HDMI_DISP_VSST1_vs_st_pos1h_mask                                         (0x00001FFF)
#define TVE_HDMI_DISP_VSST1_vs_st_pos1h(data)                                        (0x00001FFF&((data)<<0))
#define TVE_HDMI_DISP_VSST1_vs_st_pos1h_src(data)                                    ((0x00001FFF&(data))>>0)
#define TVE_HDMI_DISP_VSST1_get_vs_st_pos1h(data)                                    ((0x00001FFF&(data))>>0)


#define TVE_HDMI_DISP_VSED1                                                          0x180180c4
#define TVE_HDMI_DISP_VSED1_reg_addr                                                 "0xB80180C4"
#define TVE_HDMI_DISP_VSED1_reg                                                      0xB80180C4
#define set_TVE_HDMI_DISP_VSED1_reg(data)   (*((volatile unsigned int*) TVE_HDMI_DISP_VSED1_reg)=data)
#define get_TVE_HDMI_DISP_VSED1_reg   (*((volatile unsigned int*) TVE_HDMI_DISP_VSED1_reg))
#define TVE_HDMI_DISP_VSED1_inst_adr                                                 "0x0031"
#define TVE_HDMI_DISP_VSED1_inst                                                     0x0031
#define TVE_HDMI_DISP_VSED1_write_en2_shift                                          (25)
#define TVE_HDMI_DISP_VSED1_write_en2_mask                                           (0x02000000)
#define TVE_HDMI_DISP_VSED1_write_en2(data)                                          (0x02000000&((data)<<25))
#define TVE_HDMI_DISP_VSED1_write_en2_src(data)                                      ((0x02000000&(data))>>25)
#define TVE_HDMI_DISP_VSED1_get_write_en2(data)                                      ((0x02000000&(data))>>25)
#define TVE_HDMI_DISP_VSED1_vs_end_pos1v_shift                                       (14)
#define TVE_HDMI_DISP_VSED1_vs_end_pos1v_mask                                        (0x01FFC000)
#define TVE_HDMI_DISP_VSED1_vs_end_pos1v(data)                                       (0x01FFC000&((data)<<14))
#define TVE_HDMI_DISP_VSED1_vs_end_pos1v_src(data)                                   ((0x01FFC000&(data))>>14)
#define TVE_HDMI_DISP_VSED1_get_vs_end_pos1v(data)                                   ((0x01FFC000&(data))>>14)
#define TVE_HDMI_DISP_VSED1_write_en1_shift                                          (13)
#define TVE_HDMI_DISP_VSED1_write_en1_mask                                           (0x00002000)
#define TVE_HDMI_DISP_VSED1_write_en1(data)                                          (0x00002000&((data)<<13))
#define TVE_HDMI_DISP_VSED1_write_en1_src(data)                                      ((0x00002000&(data))>>13)
#define TVE_HDMI_DISP_VSED1_get_write_en1(data)                                      ((0x00002000&(data))>>13)
#define TVE_HDMI_DISP_VSED1_vs_end_pos1h_shift                                       (0)
#define TVE_HDMI_DISP_VSED1_vs_end_pos1h_mask                                        (0x00001FFF)
#define TVE_HDMI_DISP_VSED1_vs_end_pos1h(data)                                       (0x00001FFF&((data)<<0))
#define TVE_HDMI_DISP_VSED1_vs_end_pos1h_src(data)                                   ((0x00001FFF&(data))>>0)
#define TVE_HDMI_DISP_VSED1_get_vs_end_pos1h(data)                                   ((0x00001FFF&(data))>>0)


#define TVE_HDMI_DISP_VSST2                                                          0x180180c8
#define TVE_HDMI_DISP_VSST2_reg_addr                                                 "0xB80180C8"
#define TVE_HDMI_DISP_VSST2_reg                                                      0xB80180C8
#define set_TVE_HDMI_DISP_VSST2_reg(data)   (*((volatile unsigned int*) TVE_HDMI_DISP_VSST2_reg)=data)
#define get_TVE_HDMI_DISP_VSST2_reg   (*((volatile unsigned int*) TVE_HDMI_DISP_VSST2_reg))
#define TVE_HDMI_DISP_VSST2_inst_adr                                                 "0x0032"
#define TVE_HDMI_DISP_VSST2_inst                                                     0x0032
#define TVE_HDMI_DISP_VSST2_write_en2_shift                                          (25)
#define TVE_HDMI_DISP_VSST2_write_en2_mask                                           (0x02000000)
#define TVE_HDMI_DISP_VSST2_write_en2(data)                                          (0x02000000&((data)<<25))
#define TVE_HDMI_DISP_VSST2_write_en2_src(data)                                      ((0x02000000&(data))>>25)
#define TVE_HDMI_DISP_VSST2_get_write_en2(data)                                      ((0x02000000&(data))>>25)
#define TVE_HDMI_DISP_VSST2_vs_st_pos2v_shift                                        (14)
#define TVE_HDMI_DISP_VSST2_vs_st_pos2v_mask                                         (0x01FFC000)
#define TVE_HDMI_DISP_VSST2_vs_st_pos2v(data)                                        (0x01FFC000&((data)<<14))
#define TVE_HDMI_DISP_VSST2_vs_st_pos2v_src(data)                                    ((0x01FFC000&(data))>>14)
#define TVE_HDMI_DISP_VSST2_get_vs_st_pos2v(data)                                    ((0x01FFC000&(data))>>14)
#define TVE_HDMI_DISP_VSST2_write_en1_shift                                          (13)
#define TVE_HDMI_DISP_VSST2_write_en1_mask                                           (0x00002000)
#define TVE_HDMI_DISP_VSST2_write_en1(data)                                          (0x00002000&((data)<<13))
#define TVE_HDMI_DISP_VSST2_write_en1_src(data)                                      ((0x00002000&(data))>>13)
#define TVE_HDMI_DISP_VSST2_get_write_en1(data)                                      ((0x00002000&(data))>>13)
#define TVE_HDMI_DISP_VSST2_vs_st_pos2h_shift                                        (0)
#define TVE_HDMI_DISP_VSST2_vs_st_pos2h_mask                                         (0x00001FFF)
#define TVE_HDMI_DISP_VSST2_vs_st_pos2h(data)                                        (0x00001FFF&((data)<<0))
#define TVE_HDMI_DISP_VSST2_vs_st_pos2h_src(data)                                    ((0x00001FFF&(data))>>0)
#define TVE_HDMI_DISP_VSST2_get_vs_st_pos2h(data)                                    ((0x00001FFF&(data))>>0)


#define TVE_HDMI_DISP_VSED2                                                          0x180180cc
#define TVE_HDMI_DISP_VSED2_reg_addr                                                 "0xB80180CC"
#define TVE_HDMI_DISP_VSED2_reg                                                      0xB80180CC
#define set_TVE_HDMI_DISP_VSED2_reg(data)   (*((volatile unsigned int*) TVE_HDMI_DISP_VSED2_reg)=data)
#define get_TVE_HDMI_DISP_VSED2_reg   (*((volatile unsigned int*) TVE_HDMI_DISP_VSED2_reg))
#define TVE_HDMI_DISP_VSED2_inst_adr                                                 "0x0033"
#define TVE_HDMI_DISP_VSED2_inst                                                     0x0033
#define TVE_HDMI_DISP_VSED2_write_en2_shift                                          (25)
#define TVE_HDMI_DISP_VSED2_write_en2_mask                                           (0x02000000)
#define TVE_HDMI_DISP_VSED2_write_en2(data)                                          (0x02000000&((data)<<25))
#define TVE_HDMI_DISP_VSED2_write_en2_src(data)                                      ((0x02000000&(data))>>25)
#define TVE_HDMI_DISP_VSED2_get_write_en2(data)                                      ((0x02000000&(data))>>25)
#define TVE_HDMI_DISP_VSED2_vs_end_pos2v_shift                                       (14)
#define TVE_HDMI_DISP_VSED2_vs_end_pos2v_mask                                        (0x01FFC000)
#define TVE_HDMI_DISP_VSED2_vs_end_pos2v(data)                                       (0x01FFC000&((data)<<14))
#define TVE_HDMI_DISP_VSED2_vs_end_pos2v_src(data)                                   ((0x01FFC000&(data))>>14)
#define TVE_HDMI_DISP_VSED2_get_vs_end_pos2v(data)                                   ((0x01FFC000&(data))>>14)
#define TVE_HDMI_DISP_VSED2_write_en1_shift                                          (13)
#define TVE_HDMI_DISP_VSED2_write_en1_mask                                           (0x00002000)
#define TVE_HDMI_DISP_VSED2_write_en1(data)                                          (0x00002000&((data)<<13))
#define TVE_HDMI_DISP_VSED2_write_en1_src(data)                                      ((0x00002000&(data))>>13)
#define TVE_HDMI_DISP_VSED2_get_write_en1(data)                                      ((0x00002000&(data))>>13)
#define TVE_HDMI_DISP_VSED2_vs_end_pos2h_shift                                       (0)
#define TVE_HDMI_DISP_VSED2_vs_end_pos2h_mask                                        (0x00001FFF)
#define TVE_HDMI_DISP_VSED2_vs_end_pos2h(data)                                       (0x00001FFF&((data)<<0))
#define TVE_HDMI_DISP_VSED2_vs_end_pos2h_src(data)                                   ((0x00001FFF&(data))>>0)
#define TVE_HDMI_DISP_VSED2_get_vs_end_pos2h(data)                                   ((0x00001FFF&(data))>>0)


#define TVE_HDMI_PXLACT                                                              0x180180d0
#define TVE_HDMI_PXLACT_reg_addr                                                     "0xB80180D0"
#define TVE_HDMI_PXLACT_reg                                                          0xB80180D0
#define set_TVE_HDMI_PXLACT_reg(data)   (*((volatile unsigned int*) TVE_HDMI_PXLACT_reg)=data)
#define get_TVE_HDMI_PXLACT_reg   (*((volatile unsigned int*) TVE_HDMI_PXLACT_reg))
#define TVE_HDMI_PXLACT_inst_adr                                                     "0x0034"
#define TVE_HDMI_PXLACT_inst                                                         0x0034
#define TVE_HDMI_PXLACT_write_en2_shift                                              (27)
#define TVE_HDMI_PXLACT_write_en2_mask                                               (0x08000000)
#define TVE_HDMI_PXLACT_write_en2(data)                                              (0x08000000&((data)<<27))
#define TVE_HDMI_PXLACT_write_en2_src(data)                                          ((0x08000000&(data))>>27)
#define TVE_HDMI_PXLACT_get_write_en2(data)                                          ((0x08000000&(data))>>27)
#define TVE_HDMI_PXLACT_hpos_end_shift                                               (14)
#define TVE_HDMI_PXLACT_hpos_end_mask                                                (0x07FFC000)
#define TVE_HDMI_PXLACT_hpos_end(data)                                               (0x07FFC000&((data)<<14))
#define TVE_HDMI_PXLACT_hpos_end_src(data)                                           ((0x07FFC000&(data))>>14)
#define TVE_HDMI_PXLACT_get_hpos_end(data)                                           ((0x07FFC000&(data))>>14)
#define TVE_HDMI_PXLACT_write_en1_shift                                              (13)
#define TVE_HDMI_PXLACT_write_en1_mask                                               (0x00002000)
#define TVE_HDMI_PXLACT_write_en1(data)                                              (0x00002000&((data)<<13))
#define TVE_HDMI_PXLACT_write_en1_src(data)                                          ((0x00002000&(data))>>13)
#define TVE_HDMI_PXLACT_get_write_en1(data)                                          ((0x00002000&(data))>>13)
#define TVE_HDMI_PXLACT_hpos_st_shift                                                (0)
#define TVE_HDMI_PXLACT_hpos_st_mask                                                 (0x00001FFF)
#define TVE_HDMI_PXLACT_hpos_st(data)                                                (0x00001FFF&((data)<<0))
#define TVE_HDMI_PXLACT_hpos_st_src(data)                                            ((0x00001FFF&(data))>>0)
#define TVE_HDMI_PXLACT_get_hpos_st(data)                                            ((0x00001FFF&(data))>>0)


#define TVE_COMP_SYNCLVL                                                             0x180180e0
#define TVE_COMP_SYNCLVL_reg_addr                                                    "0xB80180E0"
#define TVE_COMP_SYNCLVL_reg                                                         0xB80180E0
#define set_TVE_COMP_SYNCLVL_reg(data)   (*((volatile unsigned int*) TVE_COMP_SYNCLVL_reg)=data)
#define get_TVE_COMP_SYNCLVL_reg   (*((volatile unsigned int*) TVE_COMP_SYNCLVL_reg))
#define TVE_COMP_SYNCLVL_inst_adr                                                    "0x0038"
#define TVE_COMP_SYNCLVL_inst                                                        0x0038
#define TVE_COMP_SYNCLVL_write_en3_shift                                             (28)
#define TVE_COMP_SYNCLVL_write_en3_mask                                              (0x10000000)
#define TVE_COMP_SYNCLVL_write_en3(data)                                             (0x10000000&((data)<<28))
#define TVE_COMP_SYNCLVL_write_en3_src(data)                                         ((0x10000000&(data))>>28)
#define TVE_COMP_SYNCLVL_get_write_en3(data)                                         ((0x10000000&(data))>>28)
#define TVE_COMP_SYNCLVL_slewrate_shift                                              (26)
#define TVE_COMP_SYNCLVL_slewrate_mask                                               (0x0C000000)
#define TVE_COMP_SYNCLVL_slewrate(data)                                              (0x0C000000&((data)<<26))
#define TVE_COMP_SYNCLVL_slewrate_src(data)                                          ((0x0C000000&(data))>>26)
#define TVE_COMP_SYNCLVL_get_slewrate(data)                                          ((0x0C000000&(data))>>26)
#define TVE_COMP_SYNCLVL_write_en2_shift                                             (25)
#define TVE_COMP_SYNCLVL_write_en2_mask                                              (0x02000000)
#define TVE_COMP_SYNCLVL_write_en2(data)                                             (0x02000000&((data)<<25))
#define TVE_COMP_SYNCLVL_write_en2_src(data)                                         ((0x02000000&(data))>>25)
#define TVE_COMP_SYNCLVL_get_write_en2(data)                                         ((0x02000000&(data))>>25)
#define TVE_COMP_SYNCLVL_y_negsynclvl_shift                                          (13)
#define TVE_COMP_SYNCLVL_y_negsynclvl_mask                                           (0x01FFE000)
#define TVE_COMP_SYNCLVL_y_negsynclvl(data)                                          (0x01FFE000&((data)<<13))
#define TVE_COMP_SYNCLVL_y_negsynclvl_src(data)                                      ((0x01FFE000&(data))>>13)
#define TVE_COMP_SYNCLVL_get_y_negsynclvl(data)                                      ((0x01FFE000&(data))>>13)
#define TVE_COMP_SYNCLVL_write_en1_shift                                             (12)
#define TVE_COMP_SYNCLVL_write_en1_mask                                              (0x00001000)
#define TVE_COMP_SYNCLVL_write_en1(data)                                             (0x00001000&((data)<<12))
#define TVE_COMP_SYNCLVL_write_en1_src(data)                                         ((0x00001000&(data))>>12)
#define TVE_COMP_SYNCLVL_get_write_en1(data)                                         ((0x00001000&(data))>>12)
#define TVE_COMP_SYNCLVL_y_possynclvl_shift                                          (0)
#define TVE_COMP_SYNCLVL_y_possynclvl_mask                                           (0x00000FFF)
#define TVE_COMP_SYNCLVL_y_possynclvl(data)                                          (0x00000FFF&((data)<<0))
#define TVE_COMP_SYNCLVL_y_possynclvl_src(data)                                      ((0x00000FFF&(data))>>0)
#define TVE_COMP_SYNCLVL_get_y_possynclvl(data)                                      ((0x00000FFF&(data))>>0)


#define TVE_COMP_SYNC_SLEWLVL                                                        0x180180e4
#define TVE_COMP_SYNC_SLEWLVL_reg_addr                                               "0xB80180E4"
#define TVE_COMP_SYNC_SLEWLVL_reg                                                    0xB80180E4
#define set_TVE_COMP_SYNC_SLEWLVL_reg(data)   (*((volatile unsigned int*) TVE_COMP_SYNC_SLEWLVL_reg)=data)
#define get_TVE_COMP_SYNC_SLEWLVL_reg   (*((volatile unsigned int*) TVE_COMP_SYNC_SLEWLVL_reg))
#define TVE_COMP_SYNC_SLEWLVL_inst_adr                                               "0x0039"
#define TVE_COMP_SYNC_SLEWLVL_inst                                                   0x0039
#define TVE_COMP_SYNC_SLEWLVL_write_en2_shift                                        (25)
#define TVE_COMP_SYNC_SLEWLVL_write_en2_mask                                         (0x02000000)
#define TVE_COMP_SYNC_SLEWLVL_write_en2(data)                                        (0x02000000&((data)<<25))
#define TVE_COMP_SYNC_SLEWLVL_write_en2_src(data)                                    ((0x02000000&(data))>>25)
#define TVE_COMP_SYNC_SLEWLVL_get_write_en2(data)                                    ((0x02000000&(data))>>25)
#define TVE_COMP_SYNC_SLEWLVL_y_sync_h_shift                                         (13)
#define TVE_COMP_SYNC_SLEWLVL_y_sync_h_mask                                          (0x01FFE000)
#define TVE_COMP_SYNC_SLEWLVL_y_sync_h(data)                                         (0x01FFE000&((data)<<13))
#define TVE_COMP_SYNC_SLEWLVL_y_sync_h_src(data)                                     ((0x01FFE000&(data))>>13)
#define TVE_COMP_SYNC_SLEWLVL_get_y_sync_h(data)                                     ((0x01FFE000&(data))>>13)
#define TVE_COMP_SYNC_SLEWLVL_write_en1_shift                                        (12)
#define TVE_COMP_SYNC_SLEWLVL_write_en1_mask                                         (0x00001000)
#define TVE_COMP_SYNC_SLEWLVL_write_en1(data)                                        (0x00001000&((data)<<12))
#define TVE_COMP_SYNC_SLEWLVL_write_en1_src(data)                                    ((0x00001000&(data))>>12)
#define TVE_COMP_SYNC_SLEWLVL_get_write_en1(data)                                    ((0x00001000&(data))>>12)
#define TVE_COMP_SYNC_SLEWLVL_y_sync_m_shift                                         (0)
#define TVE_COMP_SYNC_SLEWLVL_y_sync_m_mask                                          (0x00000FFF)
#define TVE_COMP_SYNC_SLEWLVL_y_sync_m(data)                                         (0x00000FFF&((data)<<0))
#define TVE_COMP_SYNC_SLEWLVL_y_sync_m_src(data)                                     ((0x00000FFF&(data))>>0)
#define TVE_COMP_SYNC_SLEWLVL_get_y_sync_m(data)                                     ((0x00000FFF&(data))>>0)


#define TVE_COMP_BP_LVL                                                              0x180180e8
#define TVE_COMP_BP_LVL_reg_addr                                                     "0xB80180E8"
#define TVE_COMP_BP_LVL_reg                                                          0xB80180E8
#define set_TVE_COMP_BP_LVL_reg(data)   (*((volatile unsigned int*) TVE_COMP_BP_LVL_reg)=data)
#define get_TVE_COMP_BP_LVL_reg   (*((volatile unsigned int*) TVE_COMP_BP_LVL_reg))
#define TVE_COMP_BP_LVL_inst_adr                                                     "0x003A"
#define TVE_COMP_BP_LVL_inst                                                         0x003A
#define TVE_COMP_BP_LVL_write_en2_shift                                              (25)
#define TVE_COMP_BP_LVL_write_en2_mask                                               (0x02000000)
#define TVE_COMP_BP_LVL_write_en2(data)                                              (0x02000000&((data)<<25))
#define TVE_COMP_BP_LVL_write_en2_src(data)                                          ((0x02000000&(data))>>25)
#define TVE_COMP_BP_LVL_get_write_en2(data)                                          ((0x02000000&(data))>>25)
#define TVE_COMP_BP_LVL_y_sync_l_shift                                               (13)
#define TVE_COMP_BP_LVL_y_sync_l_mask                                                (0x01FFE000)
#define TVE_COMP_BP_LVL_y_sync_l(data)                                               (0x01FFE000&((data)<<13))
#define TVE_COMP_BP_LVL_y_sync_l_src(data)                                           ((0x01FFE000&(data))>>13)
#define TVE_COMP_BP_LVL_get_y_sync_l(data)                                           ((0x01FFE000&(data))>>13)
#define TVE_COMP_BP_LVL_write_en1_shift                                              (12)
#define TVE_COMP_BP_LVL_write_en1_mask                                               (0x00001000)
#define TVE_COMP_BP_LVL_write_en1(data)                                              (0x00001000&((data)<<12))
#define TVE_COMP_BP_LVL_write_en1_src(data)                                          ((0x00001000&(data))>>12)
#define TVE_COMP_BP_LVL_get_write_en1(data)                                          ((0x00001000&(data))>>12)
#define TVE_COMP_BP_LVL_bp_lvl_shift                                                 (0)
#define TVE_COMP_BP_LVL_bp_lvl_mask                                                  (0x00000FFF)
#define TVE_COMP_BP_LVL_bp_lvl(data)                                                 (0x00000FFF&((data)<<0))
#define TVE_COMP_BP_LVL_bp_lvl_src(data)                                             ((0x00000FFF&(data))>>0)
#define TVE_COMP_BP_LVL_get_bp_lvl(data)                                             ((0x00000FFF&(data))>>0)


#define TVE_COMP_PBPR_SYNCLVL                                                        0x180180ec
#define TVE_COMP_PBPR_SYNCLVL_reg_addr                                               "0xB80180EC"
#define TVE_COMP_PBPR_SYNCLVL_reg                                                    0xB80180EC
#define set_TVE_COMP_PBPR_SYNCLVL_reg(data)   (*((volatile unsigned int*) TVE_COMP_PBPR_SYNCLVL_reg)=data)
#define get_TVE_COMP_PBPR_SYNCLVL_reg   (*((volatile unsigned int*) TVE_COMP_PBPR_SYNCLVL_reg))
#define TVE_COMP_PBPR_SYNCLVL_inst_adr                                               "0x003B"
#define TVE_COMP_PBPR_SYNCLVL_inst                                                   0x003B
#define TVE_COMP_PBPR_SYNCLVL_write_en2_shift                                        (25)
#define TVE_COMP_PBPR_SYNCLVL_write_en2_mask                                         (0x02000000)
#define TVE_COMP_PBPR_SYNCLVL_write_en2(data)                                        (0x02000000&((data)<<25))
#define TVE_COMP_PBPR_SYNCLVL_write_en2_src(data)                                    ((0x02000000&(data))>>25)
#define TVE_COMP_PBPR_SYNCLVL_get_write_en2(data)                                    ((0x02000000&(data))>>25)
#define TVE_COMP_PBPR_SYNCLVL_pbpr_negsynclvl_shift                                  (13)
#define TVE_COMP_PBPR_SYNCLVL_pbpr_negsynclvl_mask                                   (0x01FFE000)
#define TVE_COMP_PBPR_SYNCLVL_pbpr_negsynclvl(data)                                  (0x01FFE000&((data)<<13))
#define TVE_COMP_PBPR_SYNCLVL_pbpr_negsynclvl_src(data)                              ((0x01FFE000&(data))>>13)
#define TVE_COMP_PBPR_SYNCLVL_get_pbpr_negsynclvl(data)                              ((0x01FFE000&(data))>>13)
#define TVE_COMP_PBPR_SYNCLVL_write_en1_shift                                        (12)
#define TVE_COMP_PBPR_SYNCLVL_write_en1_mask                                         (0x00001000)
#define TVE_COMP_PBPR_SYNCLVL_write_en1(data)                                        (0x00001000&((data)<<12))
#define TVE_COMP_PBPR_SYNCLVL_write_en1_src(data)                                    ((0x00001000&(data))>>12)
#define TVE_COMP_PBPR_SYNCLVL_get_write_en1(data)                                    ((0x00001000&(data))>>12)
#define TVE_COMP_PBPR_SYNCLVL_pbpr_possynclvl_shift                                  (0)
#define TVE_COMP_PBPR_SYNCLVL_pbpr_possynclvl_mask                                   (0x00000FFF)
#define TVE_COMP_PBPR_SYNCLVL_pbpr_possynclvl(data)                                  (0x00000FFF&((data)<<0))
#define TVE_COMP_PBPR_SYNCLVL_pbpr_possynclvl_src(data)                              ((0x00000FFF&(data))>>0)
#define TVE_COMP_PBPR_SYNCLVL_get_pbpr_possynclvl(data)                              ((0x00000FFF&(data))>>0)


#define TVE_COMP_PBPR_BLNKLVL                                                        0x180180f0
#define TVE_COMP_PBPR_BLNKLVL_reg_addr                                               "0xB80180F0"
#define TVE_COMP_PBPR_BLNKLVL_reg                                                    0xB80180F0
#define set_TVE_COMP_PBPR_BLNKLVL_reg(data)   (*((volatile unsigned int*) TVE_COMP_PBPR_BLNKLVL_reg)=data)
#define get_TVE_COMP_PBPR_BLNKLVL_reg   (*((volatile unsigned int*) TVE_COMP_PBPR_BLNKLVL_reg))
#define TVE_COMP_PBPR_BLNKLVL_inst_adr                                               "0x003C"
#define TVE_COMP_PBPR_BLNKLVL_inst                                                   0x003C
#define TVE_COMP_PBPR_BLNKLVL_write_en2_shift                                        (25)
#define TVE_COMP_PBPR_BLNKLVL_write_en2_mask                                         (0x02000000)
#define TVE_COMP_PBPR_BLNKLVL_write_en2(data)                                        (0x02000000&((data)<<25))
#define TVE_COMP_PBPR_BLNKLVL_write_en2_src(data)                                    ((0x02000000&(data))>>25)
#define TVE_COMP_PBPR_BLNKLVL_get_write_en2(data)                                    ((0x02000000&(data))>>25)
#define TVE_COMP_PBPR_BLNKLVL_y_blank_lvl_shift                                      (13)
#define TVE_COMP_PBPR_BLNKLVL_y_blank_lvl_mask                                       (0x01FFE000)
#define TVE_COMP_PBPR_BLNKLVL_y_blank_lvl(data)                                      (0x01FFE000&((data)<<13))
#define TVE_COMP_PBPR_BLNKLVL_y_blank_lvl_src(data)                                  ((0x01FFE000&(data))>>13)
#define TVE_COMP_PBPR_BLNKLVL_get_y_blank_lvl(data)                                  ((0x01FFE000&(data))>>13)
#define TVE_COMP_PBPR_BLNKLVL_write_en1_shift                                        (12)
#define TVE_COMP_PBPR_BLNKLVL_write_en1_mask                                         (0x00001000)
#define TVE_COMP_PBPR_BLNKLVL_write_en1(data)                                        (0x00001000&((data)<<12))
#define TVE_COMP_PBPR_BLNKLVL_write_en1_src(data)                                    ((0x00001000&(data))>>12)
#define TVE_COMP_PBPR_BLNKLVL_get_write_en1(data)                                    ((0x00001000&(data))>>12)
#define TVE_COMP_PBPR_BLNKLVL_pbpr_blank_lvl_shift                                   (0)
#define TVE_COMP_PBPR_BLNKLVL_pbpr_blank_lvl_mask                                    (0x00000FFF)
#define TVE_COMP_PBPR_BLNKLVL_pbpr_blank_lvl(data)                                   (0x00000FFF&((data)<<0))
#define TVE_COMP_PBPR_BLNKLVL_pbpr_blank_lvl_src(data)                               ((0x00000FFF&(data))>>0)
#define TVE_COMP_PBPR_BLNKLVL_get_pbpr_blank_lvl(data)                               ((0x00000FFF&(data))>>0)


#define TVE_COMP_G_CLMPLVL                                                           0x180180f4
#define TVE_COMP_G_CLMPLVL_reg_addr                                                  "0xB80180F4"
#define TVE_COMP_G_CLMPLVL_reg                                                       0xB80180F4
#define set_TVE_COMP_G_CLMPLVL_reg(data)   (*((volatile unsigned int*) TVE_COMP_G_CLMPLVL_reg)=data)
#define get_TVE_COMP_G_CLMPLVL_reg   (*((volatile unsigned int*) TVE_COMP_G_CLMPLVL_reg))
#define TVE_COMP_G_CLMPLVL_inst_adr                                                  "0x003D"
#define TVE_COMP_G_CLMPLVL_inst                                                      0x003D
#define TVE_COMP_G_CLMPLVL_write_en2_shift                                           (25)
#define TVE_COMP_G_CLMPLVL_write_en2_mask                                            (0x02000000)
#define TVE_COMP_G_CLMPLVL_write_en2(data)                                           (0x02000000&((data)<<25))
#define TVE_COMP_G_CLMPLVL_write_en2_src(data)                                       ((0x02000000&(data))>>25)
#define TVE_COMP_G_CLMPLVL_get_write_en2(data)                                       ((0x02000000&(data))>>25)
#define TVE_COMP_G_CLMPLVL_g_up_shift                                                (13)
#define TVE_COMP_G_CLMPLVL_g_up_mask                                                 (0x01FFE000)
#define TVE_COMP_G_CLMPLVL_g_up(data)                                                (0x01FFE000&((data)<<13))
#define TVE_COMP_G_CLMPLVL_g_up_src(data)                                            ((0x01FFE000&(data))>>13)
#define TVE_COMP_G_CLMPLVL_get_g_up(data)                                            ((0x01FFE000&(data))>>13)
#define TVE_COMP_G_CLMPLVL_write_en1_shift                                           (12)
#define TVE_COMP_G_CLMPLVL_write_en1_mask                                            (0x00001000)
#define TVE_COMP_G_CLMPLVL_write_en1(data)                                           (0x00001000&((data)<<12))
#define TVE_COMP_G_CLMPLVL_write_en1_src(data)                                       ((0x00001000&(data))>>12)
#define TVE_COMP_G_CLMPLVL_get_write_en1(data)                                       ((0x00001000&(data))>>12)
#define TVE_COMP_G_CLMPLVL_g_dn_shift                                                (0)
#define TVE_COMP_G_CLMPLVL_g_dn_mask                                                 (0x00000FFF)
#define TVE_COMP_G_CLMPLVL_g_dn(data)                                                (0x00000FFF&((data)<<0))
#define TVE_COMP_G_CLMPLVL_g_dn_src(data)                                            ((0x00000FFF&(data))>>0)
#define TVE_COMP_G_CLMPLVL_get_g_dn(data)                                            ((0x00000FFF&(data))>>0)


#define TVE_COMP_RB_CLMPLVL                                                          0x180180f8
#define TVE_COMP_RB_CLMPLVL_reg_addr                                                 "0xB80180F8"
#define TVE_COMP_RB_CLMPLVL_reg                                                      0xB80180F8
#define set_TVE_COMP_RB_CLMPLVL_reg(data)   (*((volatile unsigned int*) TVE_COMP_RB_CLMPLVL_reg)=data)
#define get_TVE_COMP_RB_CLMPLVL_reg   (*((volatile unsigned int*) TVE_COMP_RB_CLMPLVL_reg))
#define TVE_COMP_RB_CLMPLVL_inst_adr                                                 "0x003E"
#define TVE_COMP_RB_CLMPLVL_inst                                                     0x003E
#define TVE_COMP_RB_CLMPLVL_write_en2_shift                                          (25)
#define TVE_COMP_RB_CLMPLVL_write_en2_mask                                           (0x02000000)
#define TVE_COMP_RB_CLMPLVL_write_en2(data)                                          (0x02000000&((data)<<25))
#define TVE_COMP_RB_CLMPLVL_write_en2_src(data)                                      ((0x02000000&(data))>>25)
#define TVE_COMP_RB_CLMPLVL_get_write_en2(data)                                      ((0x02000000&(data))>>25)
#define TVE_COMP_RB_CLMPLVL_rb_up_shift                                              (13)
#define TVE_COMP_RB_CLMPLVL_rb_up_mask                                               (0x01FFE000)
#define TVE_COMP_RB_CLMPLVL_rb_up(data)                                              (0x01FFE000&((data)<<13))
#define TVE_COMP_RB_CLMPLVL_rb_up_src(data)                                          ((0x01FFE000&(data))>>13)
#define TVE_COMP_RB_CLMPLVL_get_rb_up(data)                                          ((0x01FFE000&(data))>>13)
#define TVE_COMP_RB_CLMPLVL_write_en1_shift                                          (12)
#define TVE_COMP_RB_CLMPLVL_write_en1_mask                                           (0x00001000)
#define TVE_COMP_RB_CLMPLVL_write_en1(data)                                          (0x00001000&((data)<<12))
#define TVE_COMP_RB_CLMPLVL_write_en1_src(data)                                      ((0x00001000&(data))>>12)
#define TVE_COMP_RB_CLMPLVL_get_write_en1(data)                                      ((0x00001000&(data))>>12)
#define TVE_COMP_RB_CLMPLVL_rb_dn_shift                                              (0)
#define TVE_COMP_RB_CLMPLVL_rb_dn_mask                                               (0x00000FFF)
#define TVE_COMP_RB_CLMPLVL_rb_dn(data)                                              (0x00000FFF&((data)<<0))
#define TVE_COMP_RB_CLMPLVL_rb_dn_src(data)                                          ((0x00000FFF&(data))>>0)
#define TVE_COMP_RB_CLMPLVL_get_rb_dn(data)                                          ((0x00000FFF&(data))>>0)


#define TVE_IP_INPUT                                                                 0x18018220
#define TVE_IP_INPUT_reg_addr                                                        "0xB8018220"
#define TVE_IP_INPUT_reg                                                             0xB8018220
#define set_TVE_IP_INPUT_reg(data)   (*((volatile unsigned int*) TVE_IP_INPUT_reg)=data)
#define get_TVE_IP_INPUT_reg   (*((volatile unsigned int*) TVE_IP_INPUT_reg))
#define TVE_IP_INPUT_inst_adr                                                        "0x0088"
#define TVE_IP_INPUT_inst                                                            0x0088
#define TVE_IP_INPUT_y_black_lvl_shift                                               (0)
#define TVE_IP_INPUT_y_black_lvl_mask                                                (0x000000FF)
#define TVE_IP_INPUT_y_black_lvl(data)                                               (0x000000FF&((data)<<0))
#define TVE_IP_INPUT_y_black_lvl_src(data)                                           ((0x000000FF&(data))>>0)
#define TVE_IP_INPUT_get_y_black_lvl(data)                                           ((0x000000FF&(data))>>0)


#define TVE_VBI_COEFF                                                                0x18018100
#define TVE_VBI_COEFF_reg_addr                                                       "0xB8018100"
#define TVE_VBI_COEFF_reg                                                            0xB8018100
#define set_TVE_VBI_COEFF_reg(data)   (*((volatile unsigned int*) TVE_VBI_COEFF_reg)=data)
#define get_TVE_VBI_COEFF_reg   (*((volatile unsigned int*) TVE_VBI_COEFF_reg))
#define TVE_VBI_COEFF_inst_adr                                                       "0x0040"
#define TVE_VBI_COEFF_inst                                                           0x0040
#define TVE_VBI_COEFF_write_en2_shift                                                (31)
#define TVE_VBI_COEFF_write_en2_mask                                                 (0x80000000)
#define TVE_VBI_COEFF_write_en2(data)                                                (0x80000000&((data)<<31))
#define TVE_VBI_COEFF_write_en2_src(data)                                            ((0x80000000&(data))>>31)
#define TVE_VBI_COEFF_get_write_en2(data)                                            ((0x80000000&(data))>>31)
#define TVE_VBI_COEFF_gain_shift                                                     (16)
#define TVE_VBI_COEFF_gain_mask                                                      (0x7FFF0000)
#define TVE_VBI_COEFF_gain(data)                                                     (0x7FFF0000&((data)<<16))
#define TVE_VBI_COEFF_gain_src(data)                                                 ((0x7FFF0000&(data))>>16)
#define TVE_VBI_COEFF_get_gain(data)                                                 ((0x7FFF0000&(data))>>16)
#define TVE_VBI_COEFF_write_en1_shift                                                (15)
#define TVE_VBI_COEFF_write_en1_mask                                                 (0x00008000)
#define TVE_VBI_COEFF_write_en1(data)                                                (0x00008000&((data)<<15))
#define TVE_VBI_COEFF_write_en1_src(data)                                            ((0x00008000&(data))>>15)
#define TVE_VBI_COEFF_get_write_en1(data)                                            ((0x00008000&(data))>>15)
#define TVE_VBI_COEFF_offset_shift                                                   (0)
#define TVE_VBI_COEFF_offset_mask                                                    (0x00007FFF)
#define TVE_VBI_COEFF_offset(data)                                                   (0x00007FFF&((data)<<0))
#define TVE_VBI_COEFF_offset_src(data)                                               ((0x00007FFF&(data))>>0)
#define TVE_VBI_COEFF_get_offset(data)                                               ((0x00007FFF&(data))>>0)


#define TVE_BLNK_COEFF                                                               0x18018104
#define TVE_BLNK_COEFF_reg_addr                                                      "0xB8018104"
#define TVE_BLNK_COEFF_reg                                                           0xB8018104
#define set_TVE_BLNK_COEFF_reg(data)   (*((volatile unsigned int*) TVE_BLNK_COEFF_reg)=data)
#define get_TVE_BLNK_COEFF_reg   (*((volatile unsigned int*) TVE_BLNK_COEFF_reg))
#define TVE_BLNK_COEFF_inst_adr                                                      "0x0041"
#define TVE_BLNK_COEFF_inst                                                          0x0041
#define TVE_BLNK_COEFF_write_en2_shift                                               (31)
#define TVE_BLNK_COEFF_write_en2_mask                                                (0x80000000)
#define TVE_BLNK_COEFF_write_en2(data)                                               (0x80000000&((data)<<31))
#define TVE_BLNK_COEFF_write_en2_src(data)                                           ((0x80000000&(data))>>31)
#define TVE_BLNK_COEFF_get_write_en2(data)                                           ((0x80000000&(data))>>31)
#define TVE_BLNK_COEFF_gain_shift                                                    (16)
#define TVE_BLNK_COEFF_gain_mask                                                     (0x7FFF0000)
#define TVE_BLNK_COEFF_gain(data)                                                    (0x7FFF0000&((data)<<16))
#define TVE_BLNK_COEFF_gain_src(data)                                                ((0x7FFF0000&(data))>>16)
#define TVE_BLNK_COEFF_get_gain(data)                                                ((0x7FFF0000&(data))>>16)
#define TVE_BLNK_COEFF_write_en1_shift                                               (15)
#define TVE_BLNK_COEFF_write_en1_mask                                                (0x00008000)
#define TVE_BLNK_COEFF_write_en1(data)                                               (0x00008000&((data)<<15))
#define TVE_BLNK_COEFF_write_en1_src(data)                                           ((0x00008000&(data))>>15)
#define TVE_BLNK_COEFF_get_write_en1(data)                                           ((0x00008000&(data))>>15)
#define TVE_BLNK_COEFF_offset_shift                                                  (0)
#define TVE_BLNK_COEFF_offset_mask                                                   (0x00007FFF)
#define TVE_BLNK_COEFF_offset(data)                                                  (0x00007FFF&((data)<<0))
#define TVE_BLNK_COEFF_offset_src(data)                                              ((0x00007FFF&(data))>>0)
#define TVE_BLNK_COEFF_get_offset(data)                                              ((0x00007FFF&(data))>>0)


#define TVE_AV_COEFF1                                                                0x18018108
#define TVE_AV_COEFF1_reg_addr                                                       "0xB8018108"
#define TVE_AV_COEFF1_reg                                                            0xB8018108
#define set_TVE_AV_COEFF1_reg(data)   (*((volatile unsigned int*) TVE_AV_COEFF1_reg)=data)
#define get_TVE_AV_COEFF1_reg   (*((volatile unsigned int*) TVE_AV_COEFF1_reg))
#define TVE_AV_COEFF1_inst_adr                                                       "0x0042"
#define TVE_AV_COEFF1_inst                                                           0x0042
#define TVE_AV_COEFF1_write_en2_shift                                                (31)
#define TVE_AV_COEFF1_write_en2_mask                                                 (0x80000000)
#define TVE_AV_COEFF1_write_en2(data)                                                (0x80000000&((data)<<31))
#define TVE_AV_COEFF1_write_en2_src(data)                                            ((0x80000000&(data))>>31)
#define TVE_AV_COEFF1_get_write_en2(data)                                            ((0x80000000&(data))>>31)
#define TVE_AV_COEFF1_c2_shift                                                       (16)
#define TVE_AV_COEFF1_c2_mask                                                        (0x7FFF0000)
#define TVE_AV_COEFF1_c2(data)                                                       (0x7FFF0000&((data)<<16))
#define TVE_AV_COEFF1_c2_src(data)                                                   ((0x7FFF0000&(data))>>16)
#define TVE_AV_COEFF1_get_c2(data)                                                   ((0x7FFF0000&(data))>>16)
#define TVE_AV_COEFF1_write_en1_shift                                                (15)
#define TVE_AV_COEFF1_write_en1_mask                                                 (0x00008000)
#define TVE_AV_COEFF1_write_en1(data)                                                (0x00008000&((data)<<15))
#define TVE_AV_COEFF1_write_en1_src(data)                                            ((0x00008000&(data))>>15)
#define TVE_AV_COEFF1_get_write_en1(data)                                            ((0x00008000&(data))>>15)
#define TVE_AV_COEFF1_c1_shift                                                       (0)
#define TVE_AV_COEFF1_c1_mask                                                        (0x00007FFF)
#define TVE_AV_COEFF1_c1(data)                                                       (0x00007FFF&((data)<<0))
#define TVE_AV_COEFF1_c1_src(data)                                                   ((0x00007FFF&(data))>>0)
#define TVE_AV_COEFF1_get_c1(data)                                                   ((0x00007FFF&(data))>>0)


#define TVE_AV_COEFF2                                                                0x1801810c
#define TVE_AV_COEFF2_reg_addr                                                       "0xB801810C"
#define TVE_AV_COEFF2_reg                                                            0xB801810C
#define set_TVE_AV_COEFF2_reg(data)   (*((volatile unsigned int*) TVE_AV_COEFF2_reg)=data)
#define get_TVE_AV_COEFF2_reg   (*((volatile unsigned int*) TVE_AV_COEFF2_reg))
#define TVE_AV_COEFF2_inst_adr                                                       "0x0043"
#define TVE_AV_COEFF2_inst                                                           0x0043
#define TVE_AV_COEFF2_write_en2_shift                                                (31)
#define TVE_AV_COEFF2_write_en2_mask                                                 (0x80000000)
#define TVE_AV_COEFF2_write_en2(data)                                                (0x80000000&((data)<<31))
#define TVE_AV_COEFF2_write_en2_src(data)                                            ((0x80000000&(data))>>31)
#define TVE_AV_COEFF2_get_write_en2(data)                                            ((0x80000000&(data))>>31)
#define TVE_AV_COEFF2_c3_shift                                                       (16)
#define TVE_AV_COEFF2_c3_mask                                                        (0x7FFF0000)
#define TVE_AV_COEFF2_c3(data)                                                       (0x7FFF0000&((data)<<16))
#define TVE_AV_COEFF2_c3_src(data)                                                   ((0x7FFF0000&(data))>>16)
#define TVE_AV_COEFF2_get_c3(data)                                                   ((0x7FFF0000&(data))>>16)
#define TVE_AV_COEFF2_write_en1_shift                                                (15)
#define TVE_AV_COEFF2_write_en1_mask                                                 (0x00008000)
#define TVE_AV_COEFF2_write_en1(data)                                                (0x00008000&((data)<<15))
#define TVE_AV_COEFF2_write_en1_src(data)                                            ((0x00008000&(data))>>15)
#define TVE_AV_COEFF2_get_write_en1(data)                                            ((0x00008000&(data))>>15)
#define TVE_AV_COEFF2_c4_shift                                                       (0)
#define TVE_AV_COEFF2_c4_mask                                                        (0x00007FFF)
#define TVE_AV_COEFF2_c4(data)                                                       (0x00007FFF&((data)<<0))
#define TVE_AV_COEFF2_c4_src(data)                                                   ((0x00007FFF&(data))>>0)
#define TVE_AV_COEFF2_get_c4(data)                                                   ((0x00007FFF&(data))>>0)


#define TVE_AV_COEFF3                                                                0x18018110
#define TVE_AV_COEFF3_reg_addr                                                       "0xB8018110"
#define TVE_AV_COEFF3_reg                                                            0xB8018110
#define set_TVE_AV_COEFF3_reg(data)   (*((volatile unsigned int*) TVE_AV_COEFF3_reg)=data)
#define get_TVE_AV_COEFF3_reg   (*((volatile unsigned int*) TVE_AV_COEFF3_reg))
#define TVE_AV_COEFF3_inst_adr                                                       "0x0044"
#define TVE_AV_COEFF3_inst                                                           0x0044
#define TVE_AV_COEFF3_write_en2_shift                                                (31)
#define TVE_AV_COEFF3_write_en2_mask                                                 (0x80000000)
#define TVE_AV_COEFF3_write_en2(data)                                                (0x80000000&((data)<<31))
#define TVE_AV_COEFF3_write_en2_src(data)                                            ((0x80000000&(data))>>31)
#define TVE_AV_COEFF3_get_write_en2(data)                                            ((0x80000000&(data))>>31)
#define TVE_AV_COEFF3_c5_shift                                                       (16)
#define TVE_AV_COEFF3_c5_mask                                                        (0x7FFF0000)
#define TVE_AV_COEFF3_c5(data)                                                       (0x7FFF0000&((data)<<16))
#define TVE_AV_COEFF3_c5_src(data)                                                   ((0x7FFF0000&(data))>>16)
#define TVE_AV_COEFF3_get_c5(data)                                                   ((0x7FFF0000&(data))>>16)
#define TVE_AV_COEFF3_write_en1_shift                                                (15)
#define TVE_AV_COEFF3_write_en1_mask                                                 (0x00008000)
#define TVE_AV_COEFF3_write_en1(data)                                                (0x00008000&((data)<<15))
#define TVE_AV_COEFF3_write_en1_src(data)                                            ((0x00008000&(data))>>15)
#define TVE_AV_COEFF3_get_write_en1(data)                                            ((0x00008000&(data))>>15)
#define TVE_AV_COEFF3_c6_shift                                                       (0)
#define TVE_AV_COEFF3_c6_mask                                                        (0x00007FFF)
#define TVE_AV_COEFF3_c6(data)                                                       (0x00007FFF&((data)<<0))
#define TVE_AV_COEFF3_c6_src(data)                                                   ((0x00007FFF&(data))>>0)
#define TVE_AV_COEFF3_get_c6(data)                                                   ((0x00007FFF&(data))>>0)


#define TVE_AV_COEFF4                                                                0x18018114
#define TVE_AV_COEFF4_reg_addr                                                       "0xB8018114"
#define TVE_AV_COEFF4_reg                                                            0xB8018114
#define set_TVE_AV_COEFF4_reg(data)   (*((volatile unsigned int*) TVE_AV_COEFF4_reg)=data)
#define get_TVE_AV_COEFF4_reg   (*((volatile unsigned int*) TVE_AV_COEFF4_reg))
#define TVE_AV_COEFF4_inst_adr                                                       "0x0045"
#define TVE_AV_COEFF4_inst                                                           0x0045
#define TVE_AV_COEFF4_write_en2_shift                                                (31)
#define TVE_AV_COEFF4_write_en2_mask                                                 (0x80000000)
#define TVE_AV_COEFF4_write_en2(data)                                                (0x80000000&((data)<<31))
#define TVE_AV_COEFF4_write_en2_src(data)                                            ((0x80000000&(data))>>31)
#define TVE_AV_COEFF4_get_write_en2(data)                                            ((0x80000000&(data))>>31)
#define TVE_AV_COEFF4_k1_shift                                                       (16)
#define TVE_AV_COEFF4_k1_mask                                                        (0x7FFF0000)
#define TVE_AV_COEFF4_k1(data)                                                       (0x7FFF0000&((data)<<16))
#define TVE_AV_COEFF4_k1_src(data)                                                   ((0x7FFF0000&(data))>>16)
#define TVE_AV_COEFF4_get_k1(data)                                                   ((0x7FFF0000&(data))>>16)
#define TVE_AV_COEFF4_write_en1_shift                                                (15)
#define TVE_AV_COEFF4_write_en1_mask                                                 (0x00008000)
#define TVE_AV_COEFF4_write_en1(data)                                                (0x00008000&((data)<<15))
#define TVE_AV_COEFF4_write_en1_src(data)                                            ((0x00008000&(data))>>15)
#define TVE_AV_COEFF4_get_write_en1(data)                                            ((0x00008000&(data))>>15)
#define TVE_AV_COEFF4_k2_shift                                                       (0)
#define TVE_AV_COEFF4_k2_mask                                                        (0x00007FFF)
#define TVE_AV_COEFF4_k2(data)                                                       (0x00007FFF&((data)<<0))
#define TVE_AV_COEFF4_k2_src(data)                                                   ((0x00007FFF&(data))>>0)
#define TVE_AV_COEFF4_get_k2(data)                                                   ((0x00007FFF&(data))>>0)


#define TVE_AV_COEFF5                                                                0x18018118
#define TVE_AV_COEFF5_reg_addr                                                       "0xB8018118"
#define TVE_AV_COEFF5_reg                                                            0xB8018118
#define set_TVE_AV_COEFF5_reg(data)   (*((volatile unsigned int*) TVE_AV_COEFF5_reg)=data)
#define get_TVE_AV_COEFF5_reg   (*((volatile unsigned int*) TVE_AV_COEFF5_reg))
#define TVE_AV_COEFF5_inst_adr                                                       "0x0046"
#define TVE_AV_COEFF5_inst                                                           0x0046
#define TVE_AV_COEFF5_write_en1_shift                                                (17)
#define TVE_AV_COEFF5_write_en1_mask                                                 (0x00020000)
#define TVE_AV_COEFF5_write_en1(data)                                                (0x00020000&((data)<<17))
#define TVE_AV_COEFF5_write_en1_src(data)                                            ((0x00020000&(data))>>17)
#define TVE_AV_COEFF5_get_write_en1(data)                                            ((0x00020000&(data))>>17)
#define TVE_AV_COEFF5_vbi_gain_ebl_shift                                             (16)
#define TVE_AV_COEFF5_vbi_gain_ebl_mask                                              (0x00010000)
#define TVE_AV_COEFF5_vbi_gain_ebl(data)                                             (0x00010000&((data)<<16))
#define TVE_AV_COEFF5_vbi_gain_ebl_src(data)                                         ((0x00010000&(data))>>16)
#define TVE_AV_COEFF5_get_vbi_gain_ebl(data)                                         ((0x00010000&(data))>>16)
#define TVE_AV_COEFF5_write_en2_shift                                                (15)
#define TVE_AV_COEFF5_write_en2_mask                                                 (0x00008000)
#define TVE_AV_COEFF5_write_en2(data)                                                (0x00008000&((data)<<15))
#define TVE_AV_COEFF5_write_en2_src(data)                                            ((0x00008000&(data))>>15)
#define TVE_AV_COEFF5_get_write_en2(data)                                            ((0x00008000&(data))>>15)
#define TVE_AV_COEFF5_k3_shift                                                       (0)
#define TVE_AV_COEFF5_k3_mask                                                        (0x00007FFF)
#define TVE_AV_COEFF5_k3(data)                                                       (0x00007FFF&((data)<<0))
#define TVE_AV_COEFF5_k3_src(data)                                                   ((0x00007FFF&(data))>>0)
#define TVE_AV_COEFF5_get_k3(data)                                                   ((0x00007FFF&(data))>>0)


#define TVE_MV_CTRL                                                                  0x18018130
#define TVE_MV_CTRL_reg_addr                                                         "0xB8018130"
#define TVE_MV_CTRL_reg                                                              0xB8018130
#define set_TVE_MV_CTRL_reg(data)   (*((volatile unsigned int*) TVE_MV_CTRL_reg)=data)
#define get_TVE_MV_CTRL_reg   (*((volatile unsigned int*) TVE_MV_CTRL_reg))
#define TVE_MV_CTRL_inst_adr                                                         "0x004C"
#define TVE_MV_CTRL_inst                                                             0x004C
#define TVE_MV_CTRL_mv_rb_ebl_shift                                                  (3)
#define TVE_MV_CTRL_mv_rb_ebl_mask                                                   (0x00000008)
#define TVE_MV_CTRL_mv_rb_ebl(data)                                                  (0x00000008&((data)<<3))
#define TVE_MV_CTRL_mv_rb_ebl_src(data)                                              ((0x00000008&(data))>>3)
#define TVE_MV_CTRL_get_mv_rb_ebl(data)                                              ((0x00000008&(data))>>3)
#define TVE_MV_CTRL_mv_g_ebl_shift                                                   (2)
#define TVE_MV_CTRL_mv_g_ebl_mask                                                    (0x00000004)
#define TVE_MV_CTRL_mv_g_ebl(data)                                                   (0x00000004&((data)<<2))
#define TVE_MV_CTRL_mv_g_ebl_src(data)                                               ((0x00000004&(data))>>2)
#define TVE_MV_CTRL_get_mv_g_ebl(data)                                               ((0x00000004&(data))>>2)
#define TVE_MV_CTRL_mv_ebl_shift                                                     (1)
#define TVE_MV_CTRL_mv_ebl_mask                                                      (0x00000002)
#define TVE_MV_CTRL_mv_ebl(data)                                                     (0x00000002&((data)<<1))
#define TVE_MV_CTRL_mv_ebl_src(data)                                                 ((0x00000002&(data))>>1)
#define TVE_MV_CTRL_get_mv_ebl(data)                                                 ((0x00000002&(data))>>1)
#define TVE_MV_CTRL_write_data_shift                                                 (0)
#define TVE_MV_CTRL_write_data_mask                                                  (0x00000001)
#define TVE_MV_CTRL_write_data(data)                                                 (0x00000001&((data)<<0))
#define TVE_MV_CTRL_write_data_src(data)                                             ((0x00000001&(data))>>0)
#define TVE_MV_CTRL_get_write_data(data)                                             ((0x00000001&(data))>>0)


#define TVE_MV_VPOS                                                                  0x18018134
#define TVE_MV_VPOS_reg_addr                                                         "0xB8018134"
#define TVE_MV_VPOS_reg                                                              0xB8018134
#define set_TVE_MV_VPOS_reg(data)   (*((volatile unsigned int*) TVE_MV_VPOS_reg)=data)
#define get_TVE_MV_VPOS_reg   (*((volatile unsigned int*) TVE_MV_VPOS_reg))
#define TVE_MV_VPOS_inst_adr                                                         "0x004D"
#define TVE_MV_VPOS_inst                                                             0x004D
#define TVE_MV_VPOS_write_en2_shift                                                  (13)
#define TVE_MV_VPOS_write_en2_mask                                                   (0x00002000)
#define TVE_MV_VPOS_write_en2(data)                                                  (0x00002000&((data)<<13))
#define TVE_MV_VPOS_write_en2_src(data)                                              ((0x00002000&(data))>>13)
#define TVE_MV_VPOS_get_write_en2(data)                                              ((0x00002000&(data))>>13)
#define TVE_MV_VPOS_mv_end_line_shift                                                (7)
#define TVE_MV_VPOS_mv_end_line_mask                                                 (0x00001F80)
#define TVE_MV_VPOS_mv_end_line(data)                                                (0x00001F80&((data)<<7))
#define TVE_MV_VPOS_mv_end_line_src(data)                                            ((0x00001F80&(data))>>7)
#define TVE_MV_VPOS_get_mv_end_line(data)                                            ((0x00001F80&(data))>>7)
#define TVE_MV_VPOS_write_en1_shift                                                  (6)
#define TVE_MV_VPOS_write_en1_mask                                                   (0x00000040)
#define TVE_MV_VPOS_write_en1(data)                                                  (0x00000040&((data)<<6))
#define TVE_MV_VPOS_write_en1_src(data)                                              ((0x00000040&(data))>>6)
#define TVE_MV_VPOS_get_write_en1(data)                                              ((0x00000040&(data))>>6)
#define TVE_MV_VPOS_mv_st_line_shift                                                 (0)
#define TVE_MV_VPOS_mv_st_line_mask                                                  (0x0000003F)
#define TVE_MV_VPOS_mv_st_line(data)                                                 (0x0000003F&((data)<<0))
#define TVE_MV_VPOS_mv_st_line_src(data)                                             ((0x0000003F&(data))>>0)
#define TVE_MV_VPOS_get_mv_st_line(data)                                             ((0x0000003F&(data))>>0)


#define TVE_MV_LEN                                                                   0x18018138
#define TVE_MV_LEN_reg_addr                                                          "0xB8018138"
#define TVE_MV_LEN_reg                                                               0xB8018138
#define set_TVE_MV_LEN_reg(data)   (*((volatile unsigned int*) TVE_MV_LEN_reg)=data)
#define get_TVE_MV_LEN_reg   (*((volatile unsigned int*) TVE_MV_LEN_reg))
#define TVE_MV_LEN_inst_adr                                                          "0x004E"
#define TVE_MV_LEN_inst                                                              0x004E
#define TVE_MV_LEN_write_en4_shift                                                   (29)
#define TVE_MV_LEN_write_en4_mask                                                    (0x20000000)
#define TVE_MV_LEN_write_en4(data)                                                   (0x20000000&((data)<<29))
#define TVE_MV_LEN_write_en4_src(data)                                               ((0x20000000&(data))>>29)
#define TVE_MV_LEN_get_write_en4(data)                                               ((0x20000000&(data))>>29)
#define TVE_MV_LEN_mv_st_ps_shift                                                    (21)
#define TVE_MV_LEN_mv_st_ps_mask                                                     (0x1FE00000)
#define TVE_MV_LEN_mv_st_ps(data)                                                    (0x1FE00000&((data)<<21))
#define TVE_MV_LEN_mv_st_ps_src(data)                                                ((0x1FE00000&(data))>>21)
#define TVE_MV_LEN_get_mv_st_ps(data)                                                ((0x1FE00000&(data))>>21)
#define TVE_MV_LEN_write_en3_shift                                                   (20)
#define TVE_MV_LEN_write_en3_mask                                                    (0x00100000)
#define TVE_MV_LEN_write_en3(data)                                                   (0x00100000&((data)<<20))
#define TVE_MV_LEN_write_en3_src(data)                                               ((0x00100000&(data))>>20)
#define TVE_MV_LEN_get_write_en3(data)                                               ((0x00100000&(data))>>20)
#define TVE_MV_LEN_mv_ps_len_shift                                                   (14)
#define TVE_MV_LEN_mv_ps_len_mask                                                    (0x000FC000)
#define TVE_MV_LEN_mv_ps_len(data)                                                   (0x000FC000&((data)<<14))
#define TVE_MV_LEN_mv_ps_len_src(data)                                               ((0x000FC000&(data))>>14)
#define TVE_MV_LEN_get_mv_ps_len(data)                                               ((0x000FC000&(data))>>14)
#define TVE_MV_LEN_write_en2_shift                                                   (13)
#define TVE_MV_LEN_write_en2_mask                                                    (0x00002000)
#define TVE_MV_LEN_write_en2(data)                                                   (0x00002000&((data)<<13))
#define TVE_MV_LEN_write_en2_src(data)                                               ((0x00002000&(data))>>13)
#define TVE_MV_LEN_get_write_en2(data)                                               ((0x00002000&(data))>>13)
#define TVE_MV_LEN_mv_agc_len_shift                                                  (7)
#define TVE_MV_LEN_mv_agc_len_mask                                                   (0x00001F80)
#define TVE_MV_LEN_mv_agc_len(data)                                                  (0x00001F80&((data)<<7))
#define TVE_MV_LEN_mv_agc_len_src(data)                                              ((0x00001F80&(data))>>7)
#define TVE_MV_LEN_get_mv_agc_len(data)                                              ((0x00001F80&(data))>>7)
#define TVE_MV_LEN_write_en1_shift                                                   (6)
#define TVE_MV_LEN_write_en1_mask                                                    (0x00000040)
#define TVE_MV_LEN_write_en1(data)                                                   (0x00000040&((data)<<6))
#define TVE_MV_LEN_write_en1_src(data)                                               ((0x00000040&(data))>>6)
#define TVE_MV_LEN_get_write_en1(data)                                               ((0x00000040&(data))>>6)
#define TVE_MV_LEN_mv_blnk_len_shift                                                 (0)
#define TVE_MV_LEN_mv_blnk_len_mask                                                  (0x0000003F)
#define TVE_MV_LEN_mv_blnk_len(data)                                                 (0x0000003F&((data)<<0))
#define TVE_MV_LEN_mv_blnk_len_src(data)                                             ((0x0000003F&(data))>>0)
#define TVE_MV_LEN_get_mv_blnk_len(data)                                             ((0x0000003F&(data))>>0)


#define TVE_MV_RD                                                                    0x1801813c
#define TVE_MV_RD_reg_addr                                                           "0xB801813C"
#define TVE_MV_RD_reg                                                                0xB801813C
#define set_TVE_MV_RD_reg(data)   (*((volatile unsigned int*) TVE_MV_RD_reg)=data)
#define get_TVE_MV_RD_reg   (*((volatile unsigned int*) TVE_MV_RD_reg))
#define TVE_MV_RD_inst_adr                                                           "0x004F"
#define TVE_MV_RD_inst                                                               0x004F
#define TVE_MV_RD_mv_rd_shift                                                        (0)
#define TVE_MV_RD_mv_rd_mask                                                         (0x000FFFFF)
#define TVE_MV_RD_mv_rd(data)                                                        (0x000FFFFF&((data)<<0))
#define TVE_MV_RD_mv_rd_src(data)                                                    ((0x000FFFFF&(data))>>0)
#define TVE_MV_RD_get_mv_rd(data)                                                    ((0x000FFFFF&(data))>>0)


#define TVE_MV_DN                                                                    0x18018140
#define TVE_MV_DN_reg_addr                                                           "0xB8018140"
#define TVE_MV_DN_reg                                                                0xB8018140
#define set_TVE_MV_DN_reg(data)   (*((volatile unsigned int*) TVE_MV_DN_reg)=data)
#define get_TVE_MV_DN_reg   (*((volatile unsigned int*) TVE_MV_DN_reg))
#define TVE_MV_DN_inst_adr                                                           "0x0050"
#define TVE_MV_DN_inst                                                               0x0050
#define TVE_MV_DN_mv_dn_shift                                                        (0)
#define TVE_MV_DN_mv_dn_mask                                                         (0x000FFFFF)
#define TVE_MV_DN_mv_dn(data)                                                        (0x000FFFFF&((data)<<0))
#define TVE_MV_DN_mv_dn_src(data)                                                    ((0x000FFFFF&(data))>>0)
#define TVE_MV_DN_get_mv_dn(data)                                                    ((0x000FFFFF&(data))>>0)


#define TVE_MV_RU                                                                    0x18018144
#define TVE_MV_RU_reg_addr                                                           "0xB8018144"
#define TVE_MV_RU_reg                                                                0xB8018144
#define set_TVE_MV_RU_reg(data)   (*((volatile unsigned int*) TVE_MV_RU_reg)=data)
#define get_TVE_MV_RU_reg   (*((volatile unsigned int*) TVE_MV_RU_reg))
#define TVE_MV_RU_inst_adr                                                           "0x0051"
#define TVE_MV_RU_inst                                                               0x0051
#define TVE_MV_RU_mv_ru_shift                                                        (0)
#define TVE_MV_RU_mv_ru_mask                                                         (0x000FFFFF)
#define TVE_MV_RU_mv_ru(data)                                                        (0x000FFFFF&((data)<<0))
#define TVE_MV_RU_mv_ru_src(data)                                                    ((0x000FFFFF&(data))>>0)
#define TVE_MV_RU_get_mv_ru(data)                                                    ((0x000FFFFF&(data))>>0)


#define TVE_MV_UP                                                                    0x18018148
#define TVE_MV_UP_reg_addr                                                           "0xB8018148"
#define TVE_MV_UP_reg                                                                0xB8018148
#define set_TVE_MV_UP_reg(data)   (*((volatile unsigned int*) TVE_MV_UP_reg)=data)
#define get_TVE_MV_UP_reg   (*((volatile unsigned int*) TVE_MV_UP_reg))
#define TVE_MV_UP_inst_adr                                                           "0x0052"
#define TVE_MV_UP_inst                                                               0x0052
#define TVE_MV_UP_mv_up_shift                                                        (0)
#define TVE_MV_UP_mv_up_mask                                                         (0x000FFFFF)
#define TVE_MV_UP_mv_up(data)                                                        (0x000FFFFF&((data)<<0))
#define TVE_MV_UP_mv_up_src(data)                                                    ((0x000FFFFF&(data))>>0)
#define TVE_MV_UP_get_mv_up(data)                                                    ((0x000FFFFF&(data))>>0)


#define TVE_MV_LVL                                                                   0x1801814c
#define TVE_MV_LVL_reg_addr                                                          "0xB801814C"
#define TVE_MV_LVL_reg                                                               0xB801814C
#define set_TVE_MV_LVL_reg(data)   (*((volatile unsigned int*) TVE_MV_LVL_reg)=data)
#define get_TVE_MV_LVL_reg   (*((volatile unsigned int*) TVE_MV_LVL_reg))
#define TVE_MV_LVL_inst_adr                                                          "0x0053"
#define TVE_MV_LVL_inst                                                              0x0053
#define TVE_MV_LVL_write_en3_shift                                                   (30)
#define TVE_MV_LVL_write_en3_mask                                                    (0x40000000)
#define TVE_MV_LVL_write_en3(data)                                                   (0x40000000&((data)<<30))
#define TVE_MV_LVL_write_en3_src(data)                                               ((0x40000000&(data))>>30)
#define TVE_MV_LVL_get_write_en3(data)                                               ((0x40000000&(data))>>30)
#define TVE_MV_LVL_mv_ru_dlt_shift                                                   (22)
#define TVE_MV_LVL_mv_ru_dlt_mask                                                    (0x3FC00000)
#define TVE_MV_LVL_mv_ru_dlt(data)                                                   (0x3FC00000&((data)<<22))
#define TVE_MV_LVL_mv_ru_dlt_src(data)                                               ((0x3FC00000&(data))>>22)
#define TVE_MV_LVL_get_mv_ru_dlt(data)                                               ((0x3FC00000&(data))>>22)
#define TVE_MV_LVL_write_en2_shift                                                   (21)
#define TVE_MV_LVL_write_en2_mask                                                    (0x00200000)
#define TVE_MV_LVL_write_en2(data)                                                   (0x00200000&((data)<<21))
#define TVE_MV_LVL_write_en2_src(data)                                               ((0x00200000&(data))>>21)
#define TVE_MV_LVL_get_write_en2(data)                                               ((0x00200000&(data))>>21)
#define TVE_MV_LVL_mv_rd_dlt_shift                                                   (13)
#define TVE_MV_LVL_mv_rd_dlt_mask                                                    (0x001FE000)
#define TVE_MV_LVL_mv_rd_dlt(data)                                                   (0x001FE000&((data)<<13))
#define TVE_MV_LVL_mv_rd_dlt_src(data)                                               ((0x001FE000&(data))>>13)
#define TVE_MV_LVL_get_mv_rd_dlt(data)                                               ((0x001FE000&(data))>>13)
#define TVE_MV_LVL_write_en1_shift                                                   (12)
#define TVE_MV_LVL_write_en1_mask                                                    (0x00001000)
#define TVE_MV_LVL_write_en1(data)                                                   (0x00001000&((data)<<12))
#define TVE_MV_LVL_write_en1_src(data)                                               ((0x00001000&(data))>>12)
#define TVE_MV_LVL_get_write_en1(data)                                               ((0x00001000&(data))>>12)
#define TVE_MV_LVL_mv_stn_shift                                                      (0)
#define TVE_MV_LVL_mv_stn_mask                                                       (0x00000FFF)
#define TVE_MV_LVL_mv_stn(data)                                                      (0x00000FFF&((data)<<0))
#define TVE_MV_LVL_mv_stn_src(data)                                                  ((0x00000FFF&(data))>>0)
#define TVE_MV_LVL_get_mv_stn(data)                                                  ((0x00000FFF&(data))>>0)


#define TVE_CGMS_CTRL                                                                0x18018160
#define TVE_CGMS_CTRL_reg_addr                                                       "0xB8018160"
#define TVE_CGMS_CTRL_reg                                                            0xB8018160
#define set_TVE_CGMS_CTRL_reg(data)   (*((volatile unsigned int*) TVE_CGMS_CTRL_reg)=data)
#define get_TVE_CGMS_CTRL_reg   (*((volatile unsigned int*) TVE_CGMS_CTRL_reg))
#define TVE_CGMS_CTRL_inst_adr                                                       "0x0058"
#define TVE_CGMS_CTRL_inst                                                           0x0058
#define TVE_CGMS_CTRL_write_en3_shift                                                (24)
#define TVE_CGMS_CTRL_write_en3_mask                                                 (0x01000000)
#define TVE_CGMS_CTRL_write_en3(data)                                                (0x01000000&((data)<<24))
#define TVE_CGMS_CTRL_write_en3_src(data)                                            ((0x01000000&(data))>>24)
#define TVE_CGMS_CTRL_get_write_en3(data)                                            ((0x01000000&(data))>>24)
#define TVE_CGMS_CTRL_cgms_i_ebl_shift                                               (23)
#define TVE_CGMS_CTRL_cgms_i_ebl_mask                                                (0x00800000)
#define TVE_CGMS_CTRL_cgms_i_ebl(data)                                               (0x00800000&((data)<<23))
#define TVE_CGMS_CTRL_cgms_i_ebl_src(data)                                           ((0x00800000&(data))>>23)
#define TVE_CGMS_CTRL_get_cgms_i_ebl(data)                                           ((0x00800000&(data))>>23)
#define TVE_CGMS_CTRL_write_en2_shift                                                (22)
#define TVE_CGMS_CTRL_write_en2_mask                                                 (0x00400000)
#define TVE_CGMS_CTRL_write_en2(data)                                                (0x00400000&((data)<<22))
#define TVE_CGMS_CTRL_write_en2_src(data)                                            ((0x00400000&(data))>>22)
#define TVE_CGMS_CTRL_get_write_en2(data)                                            ((0x00400000&(data))>>22)
#define TVE_CGMS_CTRL_cgms_p_ebl_shift                                               (21)
#define TVE_CGMS_CTRL_cgms_p_ebl_mask                                                (0x00200000)
#define TVE_CGMS_CTRL_cgms_p_ebl(data)                                               (0x00200000&((data)<<21))
#define TVE_CGMS_CTRL_cgms_p_ebl_src(data)                                           ((0x00200000&(data))>>21)
#define TVE_CGMS_CTRL_get_cgms_p_ebl(data)                                           ((0x00200000&(data))>>21)
#define TVE_CGMS_CTRL_write_en1_shift                                                (20)
#define TVE_CGMS_CTRL_write_en1_mask                                                 (0x00100000)
#define TVE_CGMS_CTRL_write_en1(data)                                                (0x00100000&((data)<<20))
#define TVE_CGMS_CTRL_write_en1_src(data)                                            ((0x00100000&(data))>>20)
#define TVE_CGMS_CTRL_get_write_en1(data)                                            ((0x00100000&(data))>>20)
#define TVE_CGMS_CTRL_cgms_data_shift                                                (0)
#define TVE_CGMS_CTRL_cgms_data_mask                                                 (0x000FFFFF)
#define TVE_CGMS_CTRL_cgms_data(data)                                                (0x000FFFFF&((data)<<0))
#define TVE_CGMS_CTRL_cgms_data_src(data)                                            ((0x000FFFFF&(data))>>0)
#define TVE_CGMS_CTRL_get_cgms_data(data)                                            ((0x000FFFFF&(data))>>0)


#define TVE_CGMS_CTRL1                                                               0x18018310
#define TVE_CGMS_CTRL1_reg_addr                                                      "0xB8018310"
#define TVE_CGMS_CTRL1_reg                                                           0xB8018310
#define set_TVE_CGMS_CTRL1_reg(data)   (*((volatile unsigned int*) TVE_CGMS_CTRL1_reg)=data)
#define get_TVE_CGMS_CTRL1_reg   (*((volatile unsigned int*) TVE_CGMS_CTRL1_reg))
#define TVE_CGMS_CTRL1_inst_adr                                                      "0x00C4"
#define TVE_CGMS_CTRL1_inst                                                          0x00C4
#define TVE_CGMS_CTRL1_cgms_data_shift                                               (0)
#define TVE_CGMS_CTRL1_cgms_data_mask                                                (0x000FFFFF)
#define TVE_CGMS_CTRL1_cgms_data(data)                                               (0x000FFFFF&((data)<<0))
#define TVE_CGMS_CTRL1_cgms_data_src(data)                                           ((0x000FFFFF&(data))>>0)
#define TVE_CGMS_CTRL1_get_cgms_data(data)                                           ((0x000FFFFF&(data))>>0)


#define TVE_CGMS_I_VPOS                                                              0x18018164
#define TVE_CGMS_I_VPOS_reg_addr                                                     "0xB8018164"
#define TVE_CGMS_I_VPOS_reg                                                          0xB8018164
#define set_TVE_CGMS_I_VPOS_reg(data)   (*((volatile unsigned int*) TVE_CGMS_I_VPOS_reg)=data)
#define get_TVE_CGMS_I_VPOS_reg   (*((volatile unsigned int*) TVE_CGMS_I_VPOS_reg))
#define TVE_CGMS_I_VPOS_inst_adr                                                     "0x0059"
#define TVE_CGMS_I_VPOS_inst                                                         0x0059
#define TVE_CGMS_I_VPOS_write_en2_shift                                              (20)
#define TVE_CGMS_I_VPOS_write_en2_mask                                               (0x00100000)
#define TVE_CGMS_I_VPOS_write_en2(data)                                              (0x00100000&((data)<<20))
#define TVE_CGMS_I_VPOS_write_en2_src(data)                                          ((0x00100000&(data))>>20)
#define TVE_CGMS_I_VPOS_get_write_en2(data)                                          ((0x00100000&(data))>>20)
#define TVE_CGMS_I_VPOS_cgms_i_vpos1_shift                                           (11)
#define TVE_CGMS_I_VPOS_cgms_i_vpos1_mask                                            (0x000FF800)
#define TVE_CGMS_I_VPOS_cgms_i_vpos1(data)                                           (0x000FF800&((data)<<11))
#define TVE_CGMS_I_VPOS_cgms_i_vpos1_src(data)                                       ((0x000FF800&(data))>>11)
#define TVE_CGMS_I_VPOS_get_cgms_i_vpos1(data)                                       ((0x000FF800&(data))>>11)
#define TVE_CGMS_I_VPOS_write_en1_shift                                              (10)
#define TVE_CGMS_I_VPOS_write_en1_mask                                               (0x00000400)
#define TVE_CGMS_I_VPOS_write_en1(data)                                              (0x00000400&((data)<<10))
#define TVE_CGMS_I_VPOS_write_en1_src(data)                                          ((0x00000400&(data))>>10)
#define TVE_CGMS_I_VPOS_get_write_en1(data)                                          ((0x00000400&(data))>>10)
#define TVE_CGMS_I_VPOS_cgms_i_vpos2_shift                                           (0)
#define TVE_CGMS_I_VPOS_cgms_i_vpos2_mask                                            (0x000003FF)
#define TVE_CGMS_I_VPOS_cgms_i_vpos2(data)                                           (0x000003FF&((data)<<0))
#define TVE_CGMS_I_VPOS_cgms_i_vpos2_src(data)                                       ((0x000003FF&(data))>>0)
#define TVE_CGMS_I_VPOS_get_cgms_i_vpos2(data)                                       ((0x000003FF&(data))>>0)


#define TVE_CGMS_P_VPOS                                                              0x18018168
#define TVE_CGMS_P_VPOS_reg_addr                                                     "0xB8018168"
#define TVE_CGMS_P_VPOS_reg                                                          0xB8018168
#define set_TVE_CGMS_P_VPOS_reg(data)   (*((volatile unsigned int*) TVE_CGMS_P_VPOS_reg)=data)
#define get_TVE_CGMS_P_VPOS_reg   (*((volatile unsigned int*) TVE_CGMS_P_VPOS_reg))
#define TVE_CGMS_P_VPOS_inst_adr                                                     "0x005A"
#define TVE_CGMS_P_VPOS_inst                                                         0x005A
#define TVE_CGMS_P_VPOS_write_en2_shift                                              (22)
#define TVE_CGMS_P_VPOS_write_en2_mask                                               (0x00400000)
#define TVE_CGMS_P_VPOS_write_en2(data)                                              (0x00400000&((data)<<22))
#define TVE_CGMS_P_VPOS_write_en2_src(data)                                          ((0x00400000&(data))>>22)
#define TVE_CGMS_P_VPOS_get_write_en2(data)                                          ((0x00400000&(data))>>22)
#define TVE_CGMS_P_VPOS_cgms_p_vpos2_shift                                           (11)
#define TVE_CGMS_P_VPOS_cgms_p_vpos2_mask                                            (0x003FF800)
#define TVE_CGMS_P_VPOS_cgms_p_vpos2(data)                                           (0x003FF800&((data)<<11))
#define TVE_CGMS_P_VPOS_cgms_p_vpos2_src(data)                                       ((0x003FF800&(data))>>11)
#define TVE_CGMS_P_VPOS_get_cgms_p_vpos2(data)                                       ((0x003FF800&(data))>>11)
#define TVE_CGMS_P_VPOS_write_en1_shift                                              (10)
#define TVE_CGMS_P_VPOS_write_en1_mask                                               (0x00000400)
#define TVE_CGMS_P_VPOS_write_en1(data)                                              (0x00000400&((data)<<10))
#define TVE_CGMS_P_VPOS_write_en1_src(data)                                          ((0x00000400&(data))>>10)
#define TVE_CGMS_P_VPOS_get_write_en1(data)                                          ((0x00000400&(data))>>10)
#define TVE_CGMS_P_VPOS_cgms_p_vpos1_shift                                           (0)
#define TVE_CGMS_P_VPOS_cgms_p_vpos1_mask                                            (0x000003FF)
#define TVE_CGMS_P_VPOS_cgms_p_vpos1(data)                                           (0x000003FF&((data)<<0))
#define TVE_CGMS_P_VPOS_cgms_p_vpos1_src(data)                                       ((0x000003FF&(data))>>0)
#define TVE_CGMS_P_VPOS_get_cgms_p_vpos1(data)                                       ((0x000003FF&(data))>>0)


#define TVE_CGMS_I_HPOS                                                              0x1801816c
#define TVE_CGMS_I_HPOS_reg_addr                                                     "0xB801816C"
#define TVE_CGMS_I_HPOS_reg                                                          0xB801816C
#define set_TVE_CGMS_I_HPOS_reg(data)   (*((volatile unsigned int*) TVE_CGMS_I_HPOS_reg)=data)
#define get_TVE_CGMS_I_HPOS_reg   (*((volatile unsigned int*) TVE_CGMS_I_HPOS_reg))
#define TVE_CGMS_I_HPOS_inst_adr                                                     "0x005B"
#define TVE_CGMS_I_HPOS_inst                                                         0x005B
#define TVE_CGMS_I_HPOS_write_en2_shift                                              (21)
#define TVE_CGMS_I_HPOS_write_en2_mask                                               (0x00200000)
#define TVE_CGMS_I_HPOS_write_en2(data)                                              (0x00200000&((data)<<21))
#define TVE_CGMS_I_HPOS_write_en2_src(data)                                          ((0x00200000&(data))>>21)
#define TVE_CGMS_I_HPOS_get_write_en2(data)                                          ((0x00200000&(data))>>21)
#define TVE_CGMS_I_HPOS_cgms_i_hst_shift                                             (11)
#define TVE_CGMS_I_HPOS_cgms_i_hst_mask                                              (0x001FF800)
#define TVE_CGMS_I_HPOS_cgms_i_hst(data)                                             (0x001FF800&((data)<<11))
#define TVE_CGMS_I_HPOS_cgms_i_hst_src(data)                                         ((0x001FF800&(data))>>11)
#define TVE_CGMS_I_HPOS_get_cgms_i_hst(data)                                         ((0x001FF800&(data))>>11)
#define TVE_CGMS_I_HPOS_write_en1_shift                                              (10)
#define TVE_CGMS_I_HPOS_write_en1_mask                                               (0x00000400)
#define TVE_CGMS_I_HPOS_write_en1(data)                                              (0x00000400&((data)<<10))
#define TVE_CGMS_I_HPOS_write_en1_src(data)                                          ((0x00000400&(data))>>10)
#define TVE_CGMS_I_HPOS_get_write_en1(data)                                          ((0x00000400&(data))>>10)
#define TVE_CGMS_I_HPOS_cgms_i_len_shift                                             (0)
#define TVE_CGMS_I_HPOS_cgms_i_len_mask                                              (0x000003FF)
#define TVE_CGMS_I_HPOS_cgms_i_len(data)                                             (0x000003FF&((data)<<0))
#define TVE_CGMS_I_HPOS_cgms_i_len_src(data)                                         ((0x000003FF&(data))>>0)
#define TVE_CGMS_I_HPOS_get_cgms_i_len(data)                                         ((0x000003FF&(data))>>0)


#define TVE_CGMS_P_HPOS                                                              0x18018170
#define TVE_CGMS_P_HPOS_reg_addr                                                     "0xB8018170"
#define TVE_CGMS_P_HPOS_reg                                                          0xB8018170
#define set_TVE_CGMS_P_HPOS_reg(data)   (*((volatile unsigned int*) TVE_CGMS_P_HPOS_reg)=data)
#define get_TVE_CGMS_P_HPOS_reg   (*((volatile unsigned int*) TVE_CGMS_P_HPOS_reg))
#define TVE_CGMS_P_HPOS_inst_adr                                                     "0x005C"
#define TVE_CGMS_P_HPOS_inst                                                         0x005C
#define TVE_CGMS_P_HPOS_write_en3_shift                                              (30)
#define TVE_CGMS_P_HPOS_write_en3_mask                                               (0x40000000)
#define TVE_CGMS_P_HPOS_write_en3(data)                                              (0x40000000&((data)<<30))
#define TVE_CGMS_P_HPOS_write_en3_src(data)                                          ((0x40000000&(data))>>30)
#define TVE_CGMS_P_HPOS_get_write_en3(data)                                          ((0x40000000&(data))>>30)
#define TVE_CGMS_P_HPOS_cgms_p_lvl_shift                                             (22)
#define TVE_CGMS_P_HPOS_cgms_p_lvl_mask                                              (0x3FC00000)
#define TVE_CGMS_P_HPOS_cgms_p_lvl(data)                                             (0x3FC00000&((data)<<22))
#define TVE_CGMS_P_HPOS_cgms_p_lvl_src(data)                                         ((0x3FC00000&(data))>>22)
#define TVE_CGMS_P_HPOS_get_cgms_p_lvl(data)                                         ((0x3FC00000&(data))>>22)
#define TVE_CGMS_P_HPOS_write_en2_shift                                              (21)
#define TVE_CGMS_P_HPOS_write_en2_mask                                               (0x00200000)
#define TVE_CGMS_P_HPOS_write_en2(data)                                              (0x00200000&((data)<<21))
#define TVE_CGMS_P_HPOS_write_en2_src(data)                                          ((0x00200000&(data))>>21)
#define TVE_CGMS_P_HPOS_get_write_en2(data)                                          ((0x00200000&(data))>>21)
#define TVE_CGMS_P_HPOS_cgms_p_hst_shift                                             (11)
#define TVE_CGMS_P_HPOS_cgms_p_hst_mask                                              (0x001FF800)
#define TVE_CGMS_P_HPOS_cgms_p_hst(data)                                             (0x001FF800&((data)<<11))
#define TVE_CGMS_P_HPOS_cgms_p_hst_src(data)                                         ((0x001FF800&(data))>>11)
#define TVE_CGMS_P_HPOS_get_cgms_p_hst(data)                                         ((0x001FF800&(data))>>11)
#define TVE_CGMS_P_HPOS_write_en1_shift                                              (10)
#define TVE_CGMS_P_HPOS_write_en1_mask                                               (0x00000400)
#define TVE_CGMS_P_HPOS_write_en1(data)                                              (0x00000400&((data)<<10))
#define TVE_CGMS_P_HPOS_write_en1_src(data)                                          ((0x00000400&(data))>>10)
#define TVE_CGMS_P_HPOS_get_write_en1(data)                                          ((0x00000400&(data))>>10)
#define TVE_CGMS_P_HPOS_cgms_p_len_shift                                             (0)
#define TVE_CGMS_P_HPOS_cgms_p_len_mask                                              (0x000003FF)
#define TVE_CGMS_P_HPOS_cgms_p_len(data)                                             (0x000003FF&((data)<<0))
#define TVE_CGMS_P_HPOS_cgms_p_len_src(data)                                         ((0x000003FF&(data))>>0)
#define TVE_CGMS_P_HPOS_get_cgms_p_len(data)                                         ((0x000003FF&(data))>>0)


#define TVE_CGMS_P2_VPOS                                                             0x18018384
#define TVE_CGMS_P2_VPOS_reg_addr                                                    "0xB8018384"
#define TVE_CGMS_P2_VPOS_reg                                                         0xB8018384
#define set_TVE_CGMS_P2_VPOS_reg(data)   (*((volatile unsigned int*) TVE_CGMS_P2_VPOS_reg)=data)
#define get_TVE_CGMS_P2_VPOS_reg   (*((volatile unsigned int*) TVE_CGMS_P2_VPOS_reg))
#define TVE_CGMS_P2_VPOS_inst_adr                                                    "0x00E1"
#define TVE_CGMS_P2_VPOS_inst                                                        0x00E1
#define TVE_CGMS_P2_VPOS_write_en3_shift                                             (24)
#define TVE_CGMS_P2_VPOS_write_en3_mask                                              (0x01000000)
#define TVE_CGMS_P2_VPOS_write_en3(data)                                             (0x01000000&((data)<<24))
#define TVE_CGMS_P2_VPOS_write_en3_src(data)                                         ((0x01000000&(data))>>24)
#define TVE_CGMS_P2_VPOS_get_write_en3(data)                                         ((0x01000000&(data))>>24)
#define TVE_CGMS_P2_VPOS_cgms_p_b_ebl_shift                                          (23)
#define TVE_CGMS_P2_VPOS_cgms_p_b_ebl_mask                                           (0x00800000)
#define TVE_CGMS_P2_VPOS_cgms_p_b_ebl(data)                                          (0x00800000&((data)<<23))
#define TVE_CGMS_P2_VPOS_cgms_p_b_ebl_src(data)                                      ((0x00800000&(data))>>23)
#define TVE_CGMS_P2_VPOS_get_cgms_p_b_ebl(data)                                      ((0x00800000&(data))>>23)
#define TVE_CGMS_P2_VPOS_write_en2_shift                                             (22)
#define TVE_CGMS_P2_VPOS_write_en2_mask                                              (0x00400000)
#define TVE_CGMS_P2_VPOS_write_en2(data)                                             (0x00400000&((data)<<22))
#define TVE_CGMS_P2_VPOS_write_en2_src(data)                                         ((0x00400000&(data))>>22)
#define TVE_CGMS_P2_VPOS_get_write_en2(data)                                         ((0x00400000&(data))>>22)
#define TVE_CGMS_P2_VPOS_cgms_p2_vpos2_shift                                         (11)
#define TVE_CGMS_P2_VPOS_cgms_p2_vpos2_mask                                          (0x003FF800)
#define TVE_CGMS_P2_VPOS_cgms_p2_vpos2(data)                                         (0x003FF800&((data)<<11))
#define TVE_CGMS_P2_VPOS_cgms_p2_vpos2_src(data)                                     ((0x003FF800&(data))>>11)
#define TVE_CGMS_P2_VPOS_get_cgms_p2_vpos2(data)                                     ((0x003FF800&(data))>>11)
#define TVE_CGMS_P2_VPOS_write_en1_shift                                             (10)
#define TVE_CGMS_P2_VPOS_write_en1_mask                                              (0x00000400)
#define TVE_CGMS_P2_VPOS_write_en1(data)                                             (0x00000400&((data)<<10))
#define TVE_CGMS_P2_VPOS_write_en1_src(data)                                         ((0x00000400&(data))>>10)
#define TVE_CGMS_P2_VPOS_get_write_en1(data)                                         ((0x00000400&(data))>>10)
#define TVE_CGMS_P2_VPOS_cgms_p2_vpos1_shift                                         (0)
#define TVE_CGMS_P2_VPOS_cgms_p2_vpos1_mask                                          (0x000003FF)
#define TVE_CGMS_P2_VPOS_cgms_p2_vpos1(data)                                         (0x000003FF&((data)<<0))
#define TVE_CGMS_P2_VPOS_cgms_p2_vpos1_src(data)                                     ((0x000003FF&(data))>>0)
#define TVE_CGMS_P2_VPOS_get_cgms_p2_vpos1(data)                                     ((0x000003FF&(data))>>0)


#define TVE_CGMS_P2_HPOS                                                             0x18018354
#define TVE_CGMS_P2_HPOS_reg_addr                                                    "0xB8018354"
#define TVE_CGMS_P2_HPOS_reg                                                         0xB8018354
#define set_TVE_CGMS_P2_HPOS_reg(data)   (*((volatile unsigned int*) TVE_CGMS_P2_HPOS_reg)=data)
#define get_TVE_CGMS_P2_HPOS_reg   (*((volatile unsigned int*) TVE_CGMS_P2_HPOS_reg))
#define TVE_CGMS_P2_HPOS_inst_adr                                                    "0x00D5"
#define TVE_CGMS_P2_HPOS_inst                                                        0x00D5
#define TVE_CGMS_P2_HPOS_write_en3_shift                                             (30)
#define TVE_CGMS_P2_HPOS_write_en3_mask                                              (0x40000000)
#define TVE_CGMS_P2_HPOS_write_en3(data)                                             (0x40000000&((data)<<30))
#define TVE_CGMS_P2_HPOS_write_en3_src(data)                                         ((0x40000000&(data))>>30)
#define TVE_CGMS_P2_HPOS_get_write_en3(data)                                         ((0x40000000&(data))>>30)
#define TVE_CGMS_P2_HPOS_cgms_p2_lvl_shift                                           (22)
#define TVE_CGMS_P2_HPOS_cgms_p2_lvl_mask                                            (0x3FC00000)
#define TVE_CGMS_P2_HPOS_cgms_p2_lvl(data)                                           (0x3FC00000&((data)<<22))
#define TVE_CGMS_P2_HPOS_cgms_p2_lvl_src(data)                                       ((0x3FC00000&(data))>>22)
#define TVE_CGMS_P2_HPOS_get_cgms_p2_lvl(data)                                       ((0x3FC00000&(data))>>22)
#define TVE_CGMS_P2_HPOS_write_en2_shift                                             (21)
#define TVE_CGMS_P2_HPOS_write_en2_mask                                              (0x00200000)
#define TVE_CGMS_P2_HPOS_write_en2(data)                                             (0x00200000&((data)<<21))
#define TVE_CGMS_P2_HPOS_write_en2_src(data)                                         ((0x00200000&(data))>>21)
#define TVE_CGMS_P2_HPOS_get_write_en2(data)                                         ((0x00200000&(data))>>21)
#define TVE_CGMS_P2_HPOS_cgms_p2_hst_shift                                           (11)
#define TVE_CGMS_P2_HPOS_cgms_p2_hst_mask                                            (0x001FF800)
#define TVE_CGMS_P2_HPOS_cgms_p2_hst(data)                                           (0x001FF800&((data)<<11))
#define TVE_CGMS_P2_HPOS_cgms_p2_hst_src(data)                                       ((0x001FF800&(data))>>11)
#define TVE_CGMS_P2_HPOS_get_cgms_p2_hst(data)                                       ((0x001FF800&(data))>>11)
#define TVE_CGMS_P2_HPOS_write_en1_shift                                             (10)
#define TVE_CGMS_P2_HPOS_write_en1_mask                                              (0x00000400)
#define TVE_CGMS_P2_HPOS_write_en1(data)                                             (0x00000400&((data)<<10))
#define TVE_CGMS_P2_HPOS_write_en1_src(data)                                         ((0x00000400&(data))>>10)
#define TVE_CGMS_P2_HPOS_get_write_en1(data)                                         ((0x00000400&(data))>>10)
#define TVE_CGMS_P2_HPOS_cgms_p2_len_shift                                           (0)
#define TVE_CGMS_P2_HPOS_cgms_p2_len_mask                                            (0x000003FF)
#define TVE_CGMS_P2_HPOS_cgms_p2_len(data)                                           (0x000003FF&((data)<<0))
#define TVE_CGMS_P2_HPOS_cgms_p2_len_src(data)                                       ((0x000003FF&(data))>>0)
#define TVE_CGMS_P2_HPOS_get_cgms_p2_len(data)                                       ((0x000003FF&(data))>>0)


#define TVE_CGMS_B_HDR                                                               0x18018358
#define TVE_CGMS_B_HDR_reg_addr                                                      "0xB8018358"
#define TVE_CGMS_B_HDR_reg                                                           0xB8018358
#define set_TVE_CGMS_B_HDR_reg(data)   (*((volatile unsigned int*) TVE_CGMS_B_HDR_reg)=data)
#define get_TVE_CGMS_B_HDR_reg   (*((volatile unsigned int*) TVE_CGMS_B_HDR_reg))
#define TVE_CGMS_B_HDR_inst_adr                                                      "0x00D6"
#define TVE_CGMS_B_HDR_inst                                                          0x00D6
#define TVE_CGMS_B_HDR_cgms_hdr_shift                                                (0)
#define TVE_CGMS_B_HDR_cgms_hdr_mask                                                 (0x0000003F)
#define TVE_CGMS_B_HDR_cgms_hdr(data)                                                (0x0000003F&((data)<<0))
#define TVE_CGMS_B_HDR_cgms_hdr_src(data)                                            ((0x0000003F&(data))>>0)
#define TVE_CGMS_B_HDR_get_cgms_hdr(data)                                            ((0x0000003F&(data))>>0)


#define TVE_CGMS_B_DATA_0                                                            0x1801835C
#define TVE_CGMS_B_DATA_1                                                            0x18018360
#define TVE_CGMS_B_DATA_2                                                            0x18018364
#define TVE_CGMS_B_DATA_3                                                            0x18018368
#define TVE_CGMS_B_DATA_0_reg_addr                                                   "0xB801835C"
#define TVE_CGMS_B_DATA_1_reg_addr                                                   "0xB8018360"
#define TVE_CGMS_B_DATA_2_reg_addr                                                   "0xB8018364"
#define TVE_CGMS_B_DATA_3_reg_addr                                                   "0xB8018368"
#define TVE_CGMS_B_DATA_0_reg                                                        0xB801835C
#define TVE_CGMS_B_DATA_1_reg                                                        0xB8018360
#define TVE_CGMS_B_DATA_2_reg                                                        0xB8018364
#define TVE_CGMS_B_DATA_3_reg                                                        0xB8018368
#define set_TVE_CGMS_B_DATA_0_reg(data)   (*((volatile unsigned int*) TVE_CGMS_B_DATA_0_reg)=data)
#define set_TVE_CGMS_B_DATA_1_reg(data)   (*((volatile unsigned int*) TVE_CGMS_B_DATA_1_reg)=data)
#define set_TVE_CGMS_B_DATA_2_reg(data)   (*((volatile unsigned int*) TVE_CGMS_B_DATA_2_reg)=data)
#define set_TVE_CGMS_B_DATA_3_reg(data)   (*((volatile unsigned int*) TVE_CGMS_B_DATA_3_reg)=data)
#define get_TVE_CGMS_B_DATA_0_reg   (*((volatile unsigned int*) TVE_CGMS_B_DATA_0_reg))
#define get_TVE_CGMS_B_DATA_1_reg   (*((volatile unsigned int*) TVE_CGMS_B_DATA_1_reg))
#define get_TVE_CGMS_B_DATA_2_reg   (*((volatile unsigned int*) TVE_CGMS_B_DATA_2_reg))
#define get_TVE_CGMS_B_DATA_3_reg   (*((volatile unsigned int*) TVE_CGMS_B_DATA_3_reg))
#define TVE_CGMS_B_DATA_0_inst_adr                                                   "0x00D7"
#define TVE_CGMS_B_DATA_1_inst_adr                                                   "0x00D8"
#define TVE_CGMS_B_DATA_2_inst_adr                                                   "0x00D9"
#define TVE_CGMS_B_DATA_3_inst_adr                                                   "0x00DA"
#define TVE_CGMS_B_DATA_0_inst                                                       0x00D7
#define TVE_CGMS_B_DATA_1_inst                                                       0x00D8
#define TVE_CGMS_B_DATA_2_inst                                                       0x00D9
#define TVE_CGMS_B_DATA_3_inst                                                       0x00DA
#define TVE_CGMS_B_DATA_cgms_data_shift                                              (0)
#define TVE_CGMS_B_DATA_cgms_data_mask                                               (0xFFFFFFFF)
#define TVE_CGMS_B_DATA_cgms_data(data)                                              (0xFFFFFFFF&((data)<<0))
#define TVE_CGMS_B_DATA_cgms_data_src(data)                                          ((0xFFFFFFFF&(data))>>0)
#define TVE_CGMS_B_DATA_get_cgms_data(data)                                          ((0xFFFFFFFF&(data))>>0)


#define TVE_WSS_CTRL                                                                 0x18018174
#define TVE_WSS_CTRL_reg_addr                                                        "0xB8018174"
#define TVE_WSS_CTRL_reg                                                             0xB8018174
#define set_TVE_WSS_CTRL_reg(data)   (*((volatile unsigned int*) TVE_WSS_CTRL_reg)=data)
#define get_TVE_WSS_CTRL_reg   (*((volatile unsigned int*) TVE_WSS_CTRL_reg))
#define TVE_WSS_CTRL_inst_adr                                                        "0x005D"
#define TVE_WSS_CTRL_inst                                                            0x005D
#define TVE_WSS_CTRL_write_en4_shift                                                 (30)
#define TVE_WSS_CTRL_write_en4_mask                                                  (0x40000000)
#define TVE_WSS_CTRL_write_en4(data)                                                 (0x40000000&((data)<<30))
#define TVE_WSS_CTRL_write_en4_src(data)                                             ((0x40000000&(data))>>30)
#define TVE_WSS_CTRL_get_write_en4(data)                                             ((0x40000000&(data))>>30)
#define TVE_WSS_CTRL_wss_ebl_shift                                                   (29)
#define TVE_WSS_CTRL_wss_ebl_mask                                                    (0x20000000)
#define TVE_WSS_CTRL_wss_ebl(data)                                                   (0x20000000&((data)<<29))
#define TVE_WSS_CTRL_wss_ebl_src(data)                                               ((0x20000000&(data))>>29)
#define TVE_WSS_CTRL_get_wss_ebl(data)                                               ((0x20000000&(data))>>29)
#define TVE_WSS_CTRL_write_en3_shift                                                 (28)
#define TVE_WSS_CTRL_write_en3_mask                                                  (0x10000000)
#define TVE_WSS_CTRL_write_en3(data)                                                 (0x10000000&((data)<<28))
#define TVE_WSS_CTRL_write_en3_src(data)                                             ((0x10000000&(data))>>28)
#define TVE_WSS_CTRL_get_write_en3(data)                                             ((0x10000000&(data))>>28)
#define TVE_WSS_CTRL_wss_intp_sel_shift                                              (27)
#define TVE_WSS_CTRL_wss_intp_sel_mask                                               (0x08000000)
#define TVE_WSS_CTRL_wss_intp_sel(data)                                              (0x08000000&((data)<<27))
#define TVE_WSS_CTRL_wss_intp_sel_src(data)                                          ((0x08000000&(data))>>27)
#define TVE_WSS_CTRL_get_wss_intp_sel(data)                                          ((0x08000000&(data))>>27)
#define TVE_WSS_CTRL_write_en2_shift                                                 (26)
#define TVE_WSS_CTRL_write_en2_mask                                                  (0x04000000)
#define TVE_WSS_CTRL_write_en2(data)                                                 (0x04000000&((data)<<26))
#define TVE_WSS_CTRL_write_en2_src(data)                                             ((0x04000000&(data))>>26)
#define TVE_WSS_CTRL_get_write_en2(data)                                             ((0x04000000&(data))>>26)
#define TVE_WSS_CTRL_wss_end_hpos_shift                                              (15)
#define TVE_WSS_CTRL_wss_end_hpos_mask                                               (0x03FF8000)
#define TVE_WSS_CTRL_wss_end_hpos(data)                                              (0x03FF8000&((data)<<15))
#define TVE_WSS_CTRL_wss_end_hpos_src(data)                                          ((0x03FF8000&(data))>>15)
#define TVE_WSS_CTRL_get_wss_end_hpos(data)                                          ((0x03FF8000&(data))>>15)
#define TVE_WSS_CTRL_write_en1_shift                                                 (14)
#define TVE_WSS_CTRL_write_en1_mask                                                  (0x00004000)
#define TVE_WSS_CTRL_write_en1(data)                                                 (0x00004000&((data)<<14))
#define TVE_WSS_CTRL_write_en1_src(data)                                             ((0x00004000&(data))>>14)
#define TVE_WSS_CTRL_get_write_en1(data)                                             ((0x00004000&(data))>>14)
#define TVE_WSS_CTRL_wss_data_shift                                                  (0)
#define TVE_WSS_CTRL_wss_data_mask                                                   (0x00003FFF)
#define TVE_WSS_CTRL_wss_data(data)                                                  (0x00003FFF&((data)<<0))
#define TVE_WSS_CTRL_wss_data_src(data)                                              ((0x00003FFF&(data))>>0)
#define TVE_WSS_CTRL_get_wss_data(data)                                              ((0x00003FFF&(data))>>0)


#define TVE_WSS_POS                                                                  0x18018178
#define TVE_WSS_POS_reg_addr                                                         "0xB8018178"
#define TVE_WSS_POS_reg                                                              0xB8018178
#define set_TVE_WSS_POS_reg(data)   (*((volatile unsigned int*) TVE_WSS_POS_reg)=data)
#define get_TVE_WSS_POS_reg   (*((volatile unsigned int*) TVE_WSS_POS_reg))
#define TVE_WSS_POS_inst_adr                                                         "0x005E"
#define TVE_WSS_POS_inst                                                             0x005E
#define TVE_WSS_POS_write_en2_shift                                                  (22)
#define TVE_WSS_POS_write_en2_mask                                                   (0x00400000)
#define TVE_WSS_POS_write_en2(data)                                                  (0x00400000&((data)<<22))
#define TVE_WSS_POS_write_en2_src(data)                                              ((0x00400000&(data))>>22)
#define TVE_WSS_POS_get_write_en2(data)                                              ((0x00400000&(data))>>22)
#define TVE_WSS_POS_wss_h_pos_shift                                                  (11)
#define TVE_WSS_POS_wss_h_pos_mask                                                   (0x003FF800)
#define TVE_WSS_POS_wss_h_pos(data)                                                  (0x003FF800&((data)<<11))
#define TVE_WSS_POS_wss_h_pos_src(data)                                              ((0x003FF800&(data))>>11)
#define TVE_WSS_POS_get_wss_h_pos(data)                                              ((0x003FF800&(data))>>11)
#define TVE_WSS_POS_write_en1_shift                                                  (10)
#define TVE_WSS_POS_write_en1_mask                                                   (0x00000400)
#define TVE_WSS_POS_write_en1(data)                                                  (0x00000400&((data)<<10))
#define TVE_WSS_POS_write_en1_src(data)                                              ((0x00000400&(data))>>10)
#define TVE_WSS_POS_get_write_en1(data)                                              ((0x00000400&(data))>>10)
#define TVE_WSS_POS_wss_v_pos_shift                                                  (0)
#define TVE_WSS_POS_wss_v_pos_mask                                                   (0x000003FF)
#define TVE_WSS_POS_wss_v_pos(data)                                                  (0x000003FF&((data)<<0))
#define TVE_WSS_POS_wss_v_pos_src(data)                                              ((0x000003FF&(data))>>0)
#define TVE_WSS_POS_get_wss_v_pos(data)                                              ((0x000003FF&(data))>>0)


#define TVE_625P_WSS_CTRL                                                            0x1801817c
#define TVE_625P_WSS_CTRL_reg_addr                                                   "0xB801817C"
#define TVE_625P_WSS_CTRL_reg                                                        0xB801817C
#define set_TVE_625P_WSS_CTRL_reg(data)   (*((volatile unsigned int*) TVE_625P_WSS_CTRL_reg)=data)
#define get_TVE_625P_WSS_CTRL_reg   (*((volatile unsigned int*) TVE_625P_WSS_CTRL_reg))
#define TVE_625P_WSS_CTRL_inst_adr                                                   "0x005F"
#define TVE_625P_WSS_CTRL_inst                                                       0x005F
#define TVE_625P_WSS_CTRL_write_en3_shift                                            (18)
#define TVE_625P_WSS_CTRL_write_en3_mask                                             (0x00040000)
#define TVE_625P_WSS_CTRL_write_en3(data)                                            (0x00040000&((data)<<18))
#define TVE_625P_WSS_CTRL_write_en3_src(data)                                        ((0x00040000&(data))>>18)
#define TVE_625P_WSS_CTRL_get_write_en3(data)                                        ((0x00040000&(data))>>18)
#define TVE_625P_WSS_CTRL_wss_ebl_shift                                              (17)
#define TVE_625P_WSS_CTRL_wss_ebl_mask                                               (0x00020000)
#define TVE_625P_WSS_CTRL_wss_ebl(data)                                              (0x00020000&((data)<<17))
#define TVE_625P_WSS_CTRL_wss_ebl_src(data)                                          ((0x00020000&(data))>>17)
#define TVE_625P_WSS_CTRL_get_wss_ebl(data)                                          ((0x00020000&(data))>>17)
#define TVE_625P_WSS_CTRL_write_en2_shift                                            (16)
#define TVE_625P_WSS_CTRL_write_en2_mask                                             (0x00010000)
#define TVE_625P_WSS_CTRL_write_en2(data)                                            (0x00010000&((data)<<16))
#define TVE_625P_WSS_CTRL_write_en2_src(data)                                        ((0x00010000&(data))>>16)
#define TVE_625P_WSS_CTRL_get_write_en2(data)                                        ((0x00010000&(data))>>16)
#define TVE_625P_WSS_CTRL_wss_intp_sel_shift                                         (15)
#define TVE_625P_WSS_CTRL_wss_intp_sel_mask                                          (0x00008000)
#define TVE_625P_WSS_CTRL_wss_intp_sel(data)                                         (0x00008000&((data)<<15))
#define TVE_625P_WSS_CTRL_wss_intp_sel_src(data)                                     ((0x00008000&(data))>>15)
#define TVE_625P_WSS_CTRL_get_wss_intp_sel(data)                                     ((0x00008000&(data))>>15)
#define TVE_625P_WSS_CTRL_write_en1_shift                                            (14)
#define TVE_625P_WSS_CTRL_write_en1_mask                                             (0x00004000)
#define TVE_625P_WSS_CTRL_write_en1(data)                                            (0x00004000&((data)<<14))
#define TVE_625P_WSS_CTRL_write_en1_src(data)                                        ((0x00004000&(data))>>14)
#define TVE_625P_WSS_CTRL_get_write_en1(data)                                        ((0x00004000&(data))>>14)
#define TVE_625P_WSS_CTRL_wss_data_shift                                             (0)
#define TVE_625P_WSS_CTRL_wss_data_mask                                              (0x00003FFF)
#define TVE_625P_WSS_CTRL_wss_data(data)                                             (0x00003FFF&((data)<<0))
#define TVE_625P_WSS_CTRL_wss_data_src(data)                                         ((0x00003FFF&(data))>>0)
#define TVE_625P_WSS_CTRL_get_wss_data(data)                                         ((0x00003FFF&(data))>>0)


#define TVE_625P_WSS_POS                                                             0x18018180
#define TVE_625P_WSS_POS_reg_addr                                                    "0xB8018180"
#define TVE_625P_WSS_POS_reg                                                         0xB8018180
#define set_TVE_625P_WSS_POS_reg(data)   (*((volatile unsigned int*) TVE_625P_WSS_POS_reg)=data)
#define get_TVE_625P_WSS_POS_reg   (*((volatile unsigned int*) TVE_625P_WSS_POS_reg))
#define TVE_625P_WSS_POS_inst_adr                                                    "0x0060"
#define TVE_625P_WSS_POS_inst                                                        0x0060
#define TVE_625P_WSS_POS_write_en2_shift                                             (22)
#define TVE_625P_WSS_POS_write_en2_mask                                              (0x00400000)
#define TVE_625P_WSS_POS_write_en2(data)                                             (0x00400000&((data)<<22))
#define TVE_625P_WSS_POS_write_en2_src(data)                                         ((0x00400000&(data))>>22)
#define TVE_625P_WSS_POS_get_write_en2(data)                                         ((0x00400000&(data))>>22)
#define TVE_625P_WSS_POS_wss_h_pos_shift                                             (11)
#define TVE_625P_WSS_POS_wss_h_pos_mask                                              (0x003FF800)
#define TVE_625P_WSS_POS_wss_h_pos(data)                                             (0x003FF800&((data)<<11))
#define TVE_625P_WSS_POS_wss_h_pos_src(data)                                         ((0x003FF800&(data))>>11)
#define TVE_625P_WSS_POS_get_wss_h_pos(data)                                         ((0x003FF800&(data))>>11)
#define TVE_625P_WSS_POS_write_en1_shift                                             (10)
#define TVE_625P_WSS_POS_write_en1_mask                                              (0x00000400)
#define TVE_625P_WSS_POS_write_en1(data)                                             (0x00000400&((data)<<10))
#define TVE_625P_WSS_POS_write_en1_src(data)                                         ((0x00000400&(data))>>10)
#define TVE_625P_WSS_POS_get_write_en1(data)                                         ((0x00000400&(data))>>10)
#define TVE_625P_WSS_POS_wss_v_pos_shift                                             (0)
#define TVE_625P_WSS_POS_wss_v_pos_mask                                              (0x000003FF)
#define TVE_625P_WSS_POS_wss_v_pos(data)                                             (0x000003FF&((data)<<0))
#define TVE_625P_WSS_POS_wss_v_pos_src(data)                                         ((0x000003FF&(data))>>0)
#define TVE_625P_WSS_POS_get_wss_v_pos(data)                                         ((0x000003FF&(data))>>0)


#define TVE_TT_CTRL                                                                  0x18018184
#define TVE_TT_CTRL_reg_addr                                                         "0xB8018184"
#define TVE_TT_CTRL_reg                                                              0xB8018184
#define set_TVE_TT_CTRL_reg(data)   (*((volatile unsigned int*) TVE_TT_CTRL_reg)=data)
#define get_TVE_TT_CTRL_reg   (*((volatile unsigned int*) TVE_TT_CTRL_reg))
#define TVE_TT_CTRL_inst_adr                                                         "0x0061"
#define TVE_TT_CTRL_inst                                                             0x0061
#define TVE_TT_CTRL_write_en4_shift                                                  (24)
#define TVE_TT_CTRL_write_en4_mask                                                   (0x01000000)
#define TVE_TT_CTRL_write_en4(data)                                                  (0x01000000&((data)<<24))
#define TVE_TT_CTRL_write_en4_src(data)                                              ((0x01000000&(data))>>24)
#define TVE_TT_CTRL_get_write_en4(data)                                              ((0x01000000&(data))>>24)
#define TVE_TT_CTRL_tt_h_st_shift                                                    (13)
#define TVE_TT_CTRL_tt_h_st_mask                                                     (0x00FFE000)
#define TVE_TT_CTRL_tt_h_st(data)                                                    (0x00FFE000&((data)<<13))
#define TVE_TT_CTRL_tt_h_st_src(data)                                                ((0x00FFE000&(data))>>13)
#define TVE_TT_CTRL_get_tt_h_st(data)                                                ((0x00FFE000&(data))>>13)
#define TVE_TT_CTRL_write_en3_shift                                                  (12)
#define TVE_TT_CTRL_write_en3_mask                                                   (0x00001000)
#define TVE_TT_CTRL_write_en3(data)                                                  (0x00001000&((data)<<12))
#define TVE_TT_CTRL_write_en3_src(data)                                              ((0x00001000&(data))>>12)
#define TVE_TT_CTRL_get_write_en3(data)                                              ((0x00001000&(data))>>12)
#define TVE_TT_CTRL_tt_line_no_shift                                                 (4)
#define TVE_TT_CTRL_tt_line_no_mask                                                  (0x00000FF0)
#define TVE_TT_CTRL_tt_line_no(data)                                                 (0x00000FF0&((data)<<4))
#define TVE_TT_CTRL_tt_line_no_src(data)                                             ((0x00000FF0&(data))>>4)
#define TVE_TT_CTRL_get_tt_line_no(data)                                             ((0x00000FF0&(data))>>4)
#define TVE_TT_CTRL_write_en2_shift                                                  (3)
#define TVE_TT_CTRL_write_en2_mask                                                   (0x00000008)
#define TVE_TT_CTRL_write_en2(data)                                                  (0x00000008&((data)<<3))
#define TVE_TT_CTRL_write_en2_src(data)                                              ((0x00000008&(data))>>3)
#define TVE_TT_CTRL_get_write_en2(data)                                              ((0x00000008&(data))>>3)
#define TVE_TT_CTRL_tt_intp_sel_shift                                                (2)
#define TVE_TT_CTRL_tt_intp_sel_mask                                                 (0x00000004)
#define TVE_TT_CTRL_tt_intp_sel(data)                                                (0x00000004&((data)<<2))
#define TVE_TT_CTRL_tt_intp_sel_src(data)                                            ((0x00000004&(data))>>2)
#define TVE_TT_CTRL_get_tt_intp_sel(data)                                            ((0x00000004&(data))>>2)
#define TVE_TT_CTRL_write_en1_shift                                                  (1)
#define TVE_TT_CTRL_write_en1_mask                                                   (0x00000002)
#define TVE_TT_CTRL_write_en1(data)                                                  (0x00000002&((data)<<1))
#define TVE_TT_CTRL_write_en1_src(data)                                              ((0x00000002&(data))>>1)
#define TVE_TT_CTRL_get_write_en1(data)                                              ((0x00000002&(data))>>1)
#define TVE_TT_CTRL_vbi_tt_ebl_shift                                                 (0)
#define TVE_TT_CTRL_vbi_tt_ebl_mask                                                  (0x00000001)
#define TVE_TT_CTRL_vbi_tt_ebl(data)                                                 (0x00000001&((data)<<0))
#define TVE_TT_CTRL_vbi_tt_ebl_src(data)                                             ((0x00000001&(data))>>0)
#define TVE_TT_CTRL_get_vbi_tt_ebl(data)                                             ((0x00000001&(data))>>0)


#define TVE_TT_VPOS                                                                  0x18018188
#define TVE_TT_VPOS_reg_addr                                                         "0xB8018188"
#define TVE_TT_VPOS_reg                                                              0xB8018188
#define set_TVE_TT_VPOS_reg(data)   (*((volatile unsigned int*) TVE_TT_VPOS_reg)=data)
#define get_TVE_TT_VPOS_reg   (*((volatile unsigned int*) TVE_TT_VPOS_reg))
#define TVE_TT_VPOS_inst_adr                                                         "0x0062"
#define TVE_TT_VPOS_inst                                                             0x0062
#define TVE_TT_VPOS_write_en2_shift                                                  (15)
#define TVE_TT_VPOS_write_en2_mask                                                   (0x00008000)
#define TVE_TT_VPOS_write_en2(data)                                                  (0x00008000&((data)<<15))
#define TVE_TT_VPOS_write_en2_src(data)                                              ((0x00008000&(data))>>15)
#define TVE_TT_VPOS_get_write_en2(data)                                              ((0x00008000&(data))>>15)
#define TVE_TT_VPOS_tt_b_vst_shift                                                   (6)
#define TVE_TT_VPOS_tt_b_vst_mask                                                    (0x00007FC0)
#define TVE_TT_VPOS_tt_b_vst(data)                                                   (0x00007FC0&((data)<<6))
#define TVE_TT_VPOS_tt_b_vst_src(data)                                               ((0x00007FC0&(data))>>6)
#define TVE_TT_VPOS_get_tt_b_vst(data)                                               ((0x00007FC0&(data))>>6)
#define TVE_TT_VPOS_write_en1_shift                                                  (5)
#define TVE_TT_VPOS_write_en1_mask                                                   (0x00000020)
#define TVE_TT_VPOS_write_en1(data)                                                  (0x00000020&((data)<<5))
#define TVE_TT_VPOS_write_en1_src(data)                                              ((0x00000020&(data))>>5)
#define TVE_TT_VPOS_get_write_en1(data)                                              ((0x00000020&(data))>>5)
#define TVE_TT_VPOS_tt_t_vst_shift                                                   (0)
#define TVE_TT_VPOS_tt_t_vst_mask                                                    (0x0000001F)
#define TVE_TT_VPOS_tt_t_vst(data)                                                   (0x0000001F&((data)<<0))
#define TVE_TT_VPOS_tt_t_vst_src(data)                                               ((0x0000001F&(data))>>0)
#define TVE_TT_VPOS_get_tt_t_vst(data)                                               ((0x0000001F&(data))>>0)


#define TVE_TT_MASK_VPOS                                                             0x1801818c
#define TVE_TT_MASK_VPOS_reg_addr                                                    "0xB801818C"
#define TVE_TT_MASK_VPOS_reg                                                         0xB801818C
#define set_TVE_TT_MASK_VPOS_reg(data)   (*((volatile unsigned int*) TVE_TT_MASK_VPOS_reg)=data)
#define get_TVE_TT_MASK_VPOS_reg   (*((volatile unsigned int*) TVE_TT_MASK_VPOS_reg))
#define TVE_TT_MASK_VPOS_inst_adr                                                    "0x0063"
#define TVE_TT_MASK_VPOS_inst                                                        0x0063
#define TVE_TT_MASK_VPOS_write_en2_shift                                             (23)
#define TVE_TT_MASK_VPOS_write_en2_mask                                              (0x00800000)
#define TVE_TT_MASK_VPOS_write_en2(data)                                             (0x00800000&((data)<<23))
#define TVE_TT_MASK_VPOS_write_en2_src(data)                                         ((0x00800000&(data))>>23)
#define TVE_TT_MASK_VPOS_get_write_en2(data)                                         ((0x00800000&(data))>>23)
#define TVE_TT_MASK_VPOS_start_line2_shift                                           (12)
#define TVE_TT_MASK_VPOS_start_line2_mask                                            (0x007FF000)
#define TVE_TT_MASK_VPOS_start_line2(data)                                           (0x007FF000&((data)<<12))
#define TVE_TT_MASK_VPOS_start_line2_src(data)                                       ((0x007FF000&(data))>>12)
#define TVE_TT_MASK_VPOS_get_start_line2(data)                                       ((0x007FF000&(data))>>12)
#define TVE_TT_MASK_VPOS_write_en1_shift                                             (11)
#define TVE_TT_MASK_VPOS_write_en1_mask                                              (0x00000800)
#define TVE_TT_MASK_VPOS_write_en1(data)                                             (0x00000800&((data)<<11))
#define TVE_TT_MASK_VPOS_write_en1_src(data)                                         ((0x00000800&(data))>>11)
#define TVE_TT_MASK_VPOS_get_write_en1(data)                                         ((0x00000800&(data))>>11)
#define TVE_TT_MASK_VPOS_start_line1_shift                                           (0)
#define TVE_TT_MASK_VPOS_start_line1_mask                                            (0x000007FF)
#define TVE_TT_MASK_VPOS_start_line1(data)                                           (0x000007FF&((data)<<0))
#define TVE_TT_MASK_VPOS_start_line1_src(data)                                       ((0x000007FF&(data))>>0)
#define TVE_TT_MASK_VPOS_get_start_line1(data)                                       ((0x000007FF&(data))>>0)


#define TVE_TT_MASK_FLG_0                                                            0x18018190
#define TVE_TT_MASK_FLG_1                                                            0x18018194
#define TVE_TT_MASK_FLG_0_reg_addr                                                   "0xB8018190"
#define TVE_TT_MASK_FLG_1_reg_addr                                                   "0xB8018194"
#define TVE_TT_MASK_FLG_0_reg                                                        0xB8018190
#define TVE_TT_MASK_FLG_1_reg                                                        0xB8018194
#define set_TVE_TT_MASK_FLG_0_reg(data)   (*((volatile unsigned int*) TVE_TT_MASK_FLG_0_reg)=data)
#define set_TVE_TT_MASK_FLG_1_reg(data)   (*((volatile unsigned int*) TVE_TT_MASK_FLG_1_reg)=data)
#define get_TVE_TT_MASK_FLG_0_reg   (*((volatile unsigned int*) TVE_TT_MASK_FLG_0_reg))
#define get_TVE_TT_MASK_FLG_1_reg   (*((volatile unsigned int*) TVE_TT_MASK_FLG_1_reg))
#define TVE_TT_MASK_FLG_0_inst_adr                                                   "0x0064"
#define TVE_TT_MASK_FLG_1_inst_adr                                                   "0x0065"
#define TVE_TT_MASK_FLG_0_inst                                                       0x0064
#define TVE_TT_MASK_FLG_1_inst                                                       0x0065
#define TVE_TT_MASK_FLG_tt_line_mask_shift                                           (0)
#define TVE_TT_MASK_FLG_tt_line_mask_mask                                            (0xFFFFFFFF)
#define TVE_TT_MASK_FLG_tt_line_mask(data)                                           (0xFFFFFFFF&((data)<<0))
#define TVE_TT_MASK_FLG_tt_line_mask_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define TVE_TT_MASK_FLG_get_tt_line_mask(data)                                       ((0xFFFFFFFF&(data))>>0)


#define TVE_VPS_CTRL                                                                 0x18018198
#define TVE_VPS_CTRL_reg_addr                                                        "0xB8018198"
#define TVE_VPS_CTRL_reg                                                             0xB8018198
#define set_TVE_VPS_CTRL_reg(data)   (*((volatile unsigned int*) TVE_VPS_CTRL_reg)=data)
#define get_TVE_VPS_CTRL_reg   (*((volatile unsigned int*) TVE_VPS_CTRL_reg))
#define TVE_VPS_CTRL_inst_adr                                                        "0x0066"
#define TVE_VPS_CTRL_inst                                                            0x0066
#define TVE_VPS_CTRL_write_en4_shift                                                 (26)
#define TVE_VPS_CTRL_write_en4_mask                                                  (0x04000000)
#define TVE_VPS_CTRL_write_en4(data)                                                 (0x04000000&((data)<<26))
#define TVE_VPS_CTRL_write_en4_src(data)                                             ((0x04000000&(data))>>26)
#define TVE_VPS_CTRL_get_write_en4(data)                                             ((0x04000000&(data))>>26)
#define TVE_VPS_CTRL_vps_h_pos_shift                                                 (15)
#define TVE_VPS_CTRL_vps_h_pos_mask                                                  (0x03FF8000)
#define TVE_VPS_CTRL_vps_h_pos(data)                                                 (0x03FF8000&((data)<<15))
#define TVE_VPS_CTRL_vps_h_pos_src(data)                                             ((0x03FF8000&(data))>>15)
#define TVE_VPS_CTRL_get_vps_h_pos(data)                                             ((0x03FF8000&(data))>>15)
#define TVE_VPS_CTRL_write_en3_shift                                                 (14)
#define TVE_VPS_CTRL_write_en3_mask                                                  (0x00004000)
#define TVE_VPS_CTRL_write_en3(data)                                                 (0x00004000&((data)<<14))
#define TVE_VPS_CTRL_write_en3_src(data)                                             ((0x00004000&(data))>>14)
#define TVE_VPS_CTRL_get_write_en3(data)                                             ((0x00004000&(data))>>14)
#define TVE_VPS_CTRL_vps_v_pos_shift                                                 (4)
#define TVE_VPS_CTRL_vps_v_pos_mask                                                  (0x00003FF0)
#define TVE_VPS_CTRL_vps_v_pos(data)                                                 (0x00003FF0&((data)<<4))
#define TVE_VPS_CTRL_vps_v_pos_src(data)                                             ((0x00003FF0&(data))>>4)
#define TVE_VPS_CTRL_get_vps_v_pos(data)                                             ((0x00003FF0&(data))>>4)
#define TVE_VPS_CTRL_write_en2_shift                                                 (3)
#define TVE_VPS_CTRL_write_en2_mask                                                  (0x00000008)
#define TVE_VPS_CTRL_write_en2(data)                                                 (0x00000008&((data)<<3))
#define TVE_VPS_CTRL_write_en2_src(data)                                             ((0x00000008&(data))>>3)
#define TVE_VPS_CTRL_get_write_en2(data)                                             ((0x00000008&(data))>>3)
#define TVE_VPS_CTRL_vps_intp_sel_shift                                              (2)
#define TVE_VPS_CTRL_vps_intp_sel_mask                                               (0x00000004)
#define TVE_VPS_CTRL_vps_intp_sel(data)                                              (0x00000004&((data)<<2))
#define TVE_VPS_CTRL_vps_intp_sel_src(data)                                          ((0x00000004&(data))>>2)
#define TVE_VPS_CTRL_get_vps_intp_sel(data)                                          ((0x00000004&(data))>>2)
#define TVE_VPS_CTRL_write_en1_shift                                                 (1)
#define TVE_VPS_CTRL_write_en1_mask                                                  (0x00000002)
#define TVE_VPS_CTRL_write_en1(data)                                                 (0x00000002&((data)<<1))
#define TVE_VPS_CTRL_write_en1_src(data)                                             ((0x00000002&(data))>>1)
#define TVE_VPS_CTRL_get_write_en1(data)                                             ((0x00000002&(data))>>1)
#define TVE_VPS_CTRL_vbi_vps_ebl_shift                                               (0)
#define TVE_VPS_CTRL_vbi_vps_ebl_mask                                                (0x00000001)
#define TVE_VPS_CTRL_vbi_vps_ebl(data)                                               (0x00000001&((data)<<0))
#define TVE_VPS_CTRL_vbi_vps_ebl_src(data)                                           ((0x00000001&(data))>>0)
#define TVE_VPS_CTRL_get_vbi_vps_ebl(data)                                           ((0x00000001&(data))>>0)


#define TVE_VPS_DATA_0                                                               0x180181A0
#define TVE_VPS_DATA_1                                                               0x180181A4
#define TVE_VPS_DATA_2                                                               0x180181A8
#define TVE_VPS_DATA_0_reg_addr                                                      "0xB80181A0"
#define TVE_VPS_DATA_1_reg_addr                                                      "0xB80181A4"
#define TVE_VPS_DATA_2_reg_addr                                                      "0xB80181A8"
#define TVE_VPS_DATA_0_reg                                                           0xB80181A0
#define TVE_VPS_DATA_1_reg                                                           0xB80181A4
#define TVE_VPS_DATA_2_reg                                                           0xB80181A8
#define set_TVE_VPS_DATA_0_reg(data)   (*((volatile unsigned int*) TVE_VPS_DATA_0_reg)=data)
#define set_TVE_VPS_DATA_1_reg(data)   (*((volatile unsigned int*) TVE_VPS_DATA_1_reg)=data)
#define set_TVE_VPS_DATA_2_reg(data)   (*((volatile unsigned int*) TVE_VPS_DATA_2_reg)=data)
#define get_TVE_VPS_DATA_0_reg   (*((volatile unsigned int*) TVE_VPS_DATA_0_reg))
#define get_TVE_VPS_DATA_1_reg   (*((volatile unsigned int*) TVE_VPS_DATA_1_reg))
#define get_TVE_VPS_DATA_2_reg   (*((volatile unsigned int*) TVE_VPS_DATA_2_reg))
#define TVE_VPS_DATA_0_inst_adr                                                      "0x0068"
#define TVE_VPS_DATA_1_inst_adr                                                      "0x0069"
#define TVE_VPS_DATA_2_inst_adr                                                      "0x006A"
#define TVE_VPS_DATA_0_inst                                                          0x0068
#define TVE_VPS_DATA_1_inst                                                          0x0069
#define TVE_VPS_DATA_2_inst                                                          0x006A
#define TVE_VPS_DATA_vps_data_shift                                                  (0)
#define TVE_VPS_DATA_vps_data_mask                                                   (0xFFFFFFFF)
#define TVE_VPS_DATA_vps_data(data)                                                  (0xFFFFFFFF&((data)<<0))
#define TVE_VPS_DATA_vps_data_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define TVE_VPS_DATA_get_vps_data(data)                                              ((0xFFFFFFFF&(data))>>0)


#define TVE_VPS_DATA1                                                                0x180181ac
#define TVE_VPS_DATA1_reg_addr                                                       "0xB80181AC"
#define TVE_VPS_DATA1_reg                                                            0xB80181AC
#define set_TVE_VPS_DATA1_reg(data)   (*((volatile unsigned int*) TVE_VPS_DATA1_reg)=data)
#define get_TVE_VPS_DATA1_reg   (*((volatile unsigned int*) TVE_VPS_DATA1_reg))
#define TVE_VPS_DATA1_inst_adr                                                       "0x006B"
#define TVE_VPS_DATA1_inst                                                           0x006B
#define TVE_VPS_DATA1_vps_data_shift                                                 (0)
#define TVE_VPS_DATA1_vps_data_mask                                                  (0x000000FF)
#define TVE_VPS_DATA1_vps_data(data)                                                 (0x000000FF&((data)<<0))
#define TVE_VPS_DATA1_vps_data_src(data)                                             ((0x000000FF&(data))>>0)
#define TVE_VPS_DATA1_get_vps_data(data)                                             ((0x000000FF&(data))>>0)


#define TVE_VBI_DWN_CTRL                                                             0x18018314
#define TVE_VBI_DWN_CTRL_reg_addr                                                    "0xB8018314"
#define TVE_VBI_DWN_CTRL_reg                                                         0xB8018314
#define set_TVE_VBI_DWN_CTRL_reg(data)   (*((volatile unsigned int*) TVE_VBI_DWN_CTRL_reg)=data)
#define get_TVE_VBI_DWN_CTRL_reg   (*((volatile unsigned int*) TVE_VBI_DWN_CTRL_reg))
#define TVE_VBI_DWN_CTRL_inst_adr                                                    "0x00C5"
#define TVE_VBI_DWN_CTRL_inst                                                        0x00C5
#define TVE_VBI_DWN_CTRL_write_en4_shift                                             (31)
#define TVE_VBI_DWN_CTRL_write_en4_mask                                              (0x80000000)
#define TVE_VBI_DWN_CTRL_write_en4(data)                                             (0x80000000&((data)<<31))
#define TVE_VBI_DWN_CTRL_write_en4_src(data)                                         ((0x80000000&(data))>>31)
#define TVE_VBI_DWN_CTRL_get_write_en4(data)                                         ((0x80000000&(data))>>31)
#define TVE_VBI_DWN_CTRL_dwn_ebl_shift                                               (29)
#define TVE_VBI_DWN_CTRL_dwn_ebl_mask                                                (0x60000000)
#define TVE_VBI_DWN_CTRL_dwn_ebl(data)                                               (0x60000000&((data)<<29))
#define TVE_VBI_DWN_CTRL_dwn_ebl_src(data)                                           ((0x60000000&(data))>>29)
#define TVE_VBI_DWN_CTRL_get_dwn_ebl(data)                                           ((0x60000000&(data))>>29)
#define TVE_VBI_DWN_CTRL_write_en3_shift                                             (28)
#define TVE_VBI_DWN_CTRL_write_en3_mask                                              (0x10000000)
#define TVE_VBI_DWN_CTRL_write_en3(data)                                             (0x10000000&((data)<<28))
#define TVE_VBI_DWN_CTRL_write_en3_src(data)                                         ((0x10000000&(data))>>28)
#define TVE_VBI_DWN_CTRL_get_write_en3(data)                                         ((0x10000000&(data))>>28)
#define TVE_VBI_DWN_CTRL_dwn_i_p_sel_shift                                           (27)
#define TVE_VBI_DWN_CTRL_dwn_i_p_sel_mask                                            (0x08000000)
#define TVE_VBI_DWN_CTRL_dwn_i_p_sel(data)                                           (0x08000000&((data)<<27))
#define TVE_VBI_DWN_CTRL_dwn_i_p_sel_src(data)                                       ((0x08000000&(data))>>27)
#define TVE_VBI_DWN_CTRL_get_dwn_i_p_sel(data)                                       ((0x08000000&(data))>>27)
#define TVE_VBI_DWN_CTRL_write_en2_shift                                             (26)
#define TVE_VBI_DWN_CTRL_write_en2_mask                                              (0x04000000)
#define TVE_VBI_DWN_CTRL_write_en2(data)                                             (0x04000000&((data)<<26))
#define TVE_VBI_DWN_CTRL_write_en2_src(data)                                         ((0x04000000&(data))>>26)
#define TVE_VBI_DWN_CTRL_get_write_en2(data)                                         ((0x04000000&(data))>>26)
#define TVE_VBI_DWN_CTRL_dwn_st_i_shift                                              (14)
#define TVE_VBI_DWN_CTRL_dwn_st_i_mask                                               (0x03FFC000)
#define TVE_VBI_DWN_CTRL_dwn_st_i(data)                                              (0x03FFC000&((data)<<14))
#define TVE_VBI_DWN_CTRL_dwn_st_i_src(data)                                          ((0x03FFC000&(data))>>14)
#define TVE_VBI_DWN_CTRL_get_dwn_st_i(data)                                          ((0x03FFC000&(data))>>14)
#define TVE_VBI_DWN_CTRL_write_en1_shift                                             (13)
#define TVE_VBI_DWN_CTRL_write_en1_mask                                              (0x00002000)
#define TVE_VBI_DWN_CTRL_write_en1(data)                                             (0x00002000&((data)<<13))
#define TVE_VBI_DWN_CTRL_write_en1_src(data)                                         ((0x00002000&(data))>>13)
#define TVE_VBI_DWN_CTRL_get_write_en1(data)                                         ((0x00002000&(data))>>13)
#define TVE_VBI_DWN_CTRL_dwn_end_i_shift                                             (0)
#define TVE_VBI_DWN_CTRL_dwn_end_i_mask                                              (0x00001FFF)
#define TVE_VBI_DWN_CTRL_dwn_end_i(data)                                             (0x00001FFF&((data)<<0))
#define TVE_VBI_DWN_CTRL_dwn_end_i_src(data)                                         ((0x00001FFF&(data))>>0)
#define TVE_VBI_DWN_CTRL_get_dwn_end_i(data)                                         ((0x00001FFF&(data))>>0)


#define TVE_VBI_DWN_HPOS                                                             0x18018318
#define TVE_VBI_DWN_HPOS_reg_addr                                                    "0xB8018318"
#define TVE_VBI_DWN_HPOS_reg                                                         0xB8018318
#define set_TVE_VBI_DWN_HPOS_reg(data)   (*((volatile unsigned int*) TVE_VBI_DWN_HPOS_reg)=data)
#define get_TVE_VBI_DWN_HPOS_reg   (*((volatile unsigned int*) TVE_VBI_DWN_HPOS_reg))
#define TVE_VBI_DWN_HPOS_inst_adr                                                    "0x00C6"
#define TVE_VBI_DWN_HPOS_inst                                                        0x00C6
#define TVE_VBI_DWN_HPOS_write_en2_shift                                             (26)
#define TVE_VBI_DWN_HPOS_write_en2_mask                                              (0x04000000)
#define TVE_VBI_DWN_HPOS_write_en2(data)                                             (0x04000000&((data)<<26))
#define TVE_VBI_DWN_HPOS_write_en2_src(data)                                         ((0x04000000&(data))>>26)
#define TVE_VBI_DWN_HPOS_get_write_en2(data)                                         ((0x04000000&(data))>>26)
#define TVE_VBI_DWN_HPOS_dwn_st_p_shift                                              (14)
#define TVE_VBI_DWN_HPOS_dwn_st_p_mask                                               (0x03FFC000)
#define TVE_VBI_DWN_HPOS_dwn_st_p(data)                                              (0x03FFC000&((data)<<14))
#define TVE_VBI_DWN_HPOS_dwn_st_p_src(data)                                          ((0x03FFC000&(data))>>14)
#define TVE_VBI_DWN_HPOS_get_dwn_st_p(data)                                          ((0x03FFC000&(data))>>14)
#define TVE_VBI_DWN_HPOS_write_en1_shift                                             (13)
#define TVE_VBI_DWN_HPOS_write_en1_mask                                              (0x00002000)
#define TVE_VBI_DWN_HPOS_write_en1(data)                                             (0x00002000&((data)<<13))
#define TVE_VBI_DWN_HPOS_write_en1_src(data)                                         ((0x00002000&(data))>>13)
#define TVE_VBI_DWN_HPOS_get_write_en1(data)                                         ((0x00002000&(data))>>13)
#define TVE_VBI_DWN_HPOS_dwn_end_p_shift                                             (0)
#define TVE_VBI_DWN_HPOS_dwn_end_p_mask                                              (0x00001FFF)
#define TVE_VBI_DWN_HPOS_dwn_end_p(data)                                             (0x00001FFF&((data)<<0))
#define TVE_VBI_DWN_HPOS_dwn_end_p_src(data)                                         ((0x00001FFF&(data))>>0)
#define TVE_VBI_DWN_HPOS_get_dwn_end_p(data)                                         ((0x00001FFF&(data))>>0)


#define TVE_VBI_DWN_VPOS_I                                                           0x1801831c
#define TVE_VBI_DWN_VPOS_I_reg_addr                                                  "0xB801831C"
#define TVE_VBI_DWN_VPOS_I_reg                                                       0xB801831C
#define set_TVE_VBI_DWN_VPOS_I_reg(data)   (*((volatile unsigned int*) TVE_VBI_DWN_VPOS_I_reg)=data)
#define get_TVE_VBI_DWN_VPOS_I_reg   (*((volatile unsigned int*) TVE_VBI_DWN_VPOS_I_reg))
#define TVE_VBI_DWN_VPOS_I_inst_adr                                                  "0x00C7"
#define TVE_VBI_DWN_VPOS_I_inst                                                      0x00C7
#define TVE_VBI_DWN_VPOS_I_write_en2_shift                                           (23)
#define TVE_VBI_DWN_VPOS_I_write_en2_mask                                            (0x00800000)
#define TVE_VBI_DWN_VPOS_I_write_en2(data)                                           (0x00800000&((data)<<23))
#define TVE_VBI_DWN_VPOS_I_write_en2_src(data)                                       ((0x00800000&(data))>>23)
#define TVE_VBI_DWN_VPOS_I_get_write_en2(data)                                       ((0x00800000&(data))>>23)
#define TVE_VBI_DWN_VPOS_I_vbi_start_line2_shift                                     (12)
#define TVE_VBI_DWN_VPOS_I_vbi_start_line2_mask                                      (0x007FF000)
#define TVE_VBI_DWN_VPOS_I_vbi_start_line2(data)                                     (0x007FF000&((data)<<12))
#define TVE_VBI_DWN_VPOS_I_vbi_start_line2_src(data)                                 ((0x007FF000&(data))>>12)
#define TVE_VBI_DWN_VPOS_I_get_vbi_start_line2(data)                                 ((0x007FF000&(data))>>12)
#define TVE_VBI_DWN_VPOS_I_write_en1_shift                                           (11)
#define TVE_VBI_DWN_VPOS_I_write_en1_mask                                            (0x00000800)
#define TVE_VBI_DWN_VPOS_I_write_en1(data)                                           (0x00000800&((data)<<11))
#define TVE_VBI_DWN_VPOS_I_write_en1_src(data)                                       ((0x00000800&(data))>>11)
#define TVE_VBI_DWN_VPOS_I_get_write_en1(data)                                       ((0x00000800&(data))>>11)
#define TVE_VBI_DWN_VPOS_I_vbi_start_line1_shift                                     (0)
#define TVE_VBI_DWN_VPOS_I_vbi_start_line1_mask                                      (0x000007FF)
#define TVE_VBI_DWN_VPOS_I_vbi_start_line1(data)                                     (0x000007FF&((data)<<0))
#define TVE_VBI_DWN_VPOS_I_vbi_start_line1_src(data)                                 ((0x000007FF&(data))>>0)
#define TVE_VBI_DWN_VPOS_I_get_vbi_start_line1(data)                                 ((0x000007FF&(data))>>0)


#define TVE_VBI_DWN_VPOS_P                                                           0x18018320
#define TVE_VBI_DWN_VPOS_P_reg_addr                                                  "0xB8018320"
#define TVE_VBI_DWN_VPOS_P_reg                                                       0xB8018320
#define set_TVE_VBI_DWN_VPOS_P_reg(data)   (*((volatile unsigned int*) TVE_VBI_DWN_VPOS_P_reg)=data)
#define get_TVE_VBI_DWN_VPOS_P_reg   (*((volatile unsigned int*) TVE_VBI_DWN_VPOS_P_reg))
#define TVE_VBI_DWN_VPOS_P_inst_adr                                                  "0x00C8"
#define TVE_VBI_DWN_VPOS_P_inst                                                      0x00C8
#define TVE_VBI_DWN_VPOS_P_write_en2_shift                                           (23)
#define TVE_VBI_DWN_VPOS_P_write_en2_mask                                            (0x00800000)
#define TVE_VBI_DWN_VPOS_P_write_en2(data)                                           (0x00800000&((data)<<23))
#define TVE_VBI_DWN_VPOS_P_write_en2_src(data)                                       ((0x00800000&(data))>>23)
#define TVE_VBI_DWN_VPOS_P_get_write_en2(data)                                       ((0x00800000&(data))>>23)
#define TVE_VBI_DWN_VPOS_P_vbi_start_line2_shift                                     (12)
#define TVE_VBI_DWN_VPOS_P_vbi_start_line2_mask                                      (0x007FF000)
#define TVE_VBI_DWN_VPOS_P_vbi_start_line2(data)                                     (0x007FF000&((data)<<12))
#define TVE_VBI_DWN_VPOS_P_vbi_start_line2_src(data)                                 ((0x007FF000&(data))>>12)
#define TVE_VBI_DWN_VPOS_P_get_vbi_start_line2(data)                                 ((0x007FF000&(data))>>12)
#define TVE_VBI_DWN_VPOS_P_write_en1_shift                                           (11)
#define TVE_VBI_DWN_VPOS_P_write_en1_mask                                            (0x00000800)
#define TVE_VBI_DWN_VPOS_P_write_en1(data)                                           (0x00000800&((data)<<11))
#define TVE_VBI_DWN_VPOS_P_write_en1_src(data)                                       ((0x00000800&(data))>>11)
#define TVE_VBI_DWN_VPOS_P_get_write_en1(data)                                       ((0x00000800&(data))>>11)
#define TVE_VBI_DWN_VPOS_P_vbi_start_line1_shift                                     (0)
#define TVE_VBI_DWN_VPOS_P_vbi_start_line1_mask                                      (0x000007FF)
#define TVE_VBI_DWN_VPOS_P_vbi_start_line1(data)                                     (0x000007FF&((data)<<0))
#define TVE_VBI_DWN_VPOS_P_vbi_start_line1_src(data)                                 ((0x000007FF&(data))>>0)
#define TVE_VBI_DWN_VPOS_P_get_vbi_start_line1(data)                                 ((0x000007FF&(data))>>0)


#define TVE_VBI_LINE_FLAG_I_0                                                        0x18018324
#define TVE_VBI_LINE_FLAG_I_1                                                        0x18018328
#define TVE_VBI_LINE_FLAG_I_0_reg_addr                                               "0xB8018324"
#define TVE_VBI_LINE_FLAG_I_1_reg_addr                                               "0xB8018328"
#define TVE_VBI_LINE_FLAG_I_0_reg                                                    0xB8018324
#define TVE_VBI_LINE_FLAG_I_1_reg                                                    0xB8018328
#define set_TVE_VBI_LINE_FLAG_I_0_reg(data)   (*((volatile unsigned int*) TVE_VBI_LINE_FLAG_I_0_reg)=data)
#define set_TVE_VBI_LINE_FLAG_I_1_reg(data)   (*((volatile unsigned int*) TVE_VBI_LINE_FLAG_I_1_reg)=data)
#define get_TVE_VBI_LINE_FLAG_I_0_reg   (*((volatile unsigned int*) TVE_VBI_LINE_FLAG_I_0_reg))
#define get_TVE_VBI_LINE_FLAG_I_1_reg   (*((volatile unsigned int*) TVE_VBI_LINE_FLAG_I_1_reg))
#define TVE_VBI_LINE_FLAG_I_0_inst_adr                                               "0x00C9"
#define TVE_VBI_LINE_FLAG_I_1_inst_adr                                               "0x00CA"
#define TVE_VBI_LINE_FLAG_I_0_inst                                                   0x00C9
#define TVE_VBI_LINE_FLAG_I_1_inst                                                   0x00CA
#define TVE_VBI_LINE_FLAG_I_vbi_line_flg_shift                                       (0)
#define TVE_VBI_LINE_FLAG_I_vbi_line_flg_mask                                        (0xFFFFFFFF)
#define TVE_VBI_LINE_FLAG_I_vbi_line_flg(data)                                       (0xFFFFFFFF&((data)<<0))
#define TVE_VBI_LINE_FLAG_I_vbi_line_flg_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define TVE_VBI_LINE_FLAG_I_get_vbi_line_flg(data)                                   ((0xFFFFFFFF&(data))>>0)


#define TVE_VBI_LINE_FLAG_P_0                                                        0x1801832C
#define TVE_VBI_LINE_FLAG_P_1                                                        0x18018330
#define TVE_VBI_LINE_FLAG_P_0_reg_addr                                               "0xB801832C"
#define TVE_VBI_LINE_FLAG_P_1_reg_addr                                               "0xB8018330"
#define TVE_VBI_LINE_FLAG_P_0_reg                                                    0xB801832C
#define TVE_VBI_LINE_FLAG_P_1_reg                                                    0xB8018330
#define set_TVE_VBI_LINE_FLAG_P_0_reg(data)   (*((volatile unsigned int*) TVE_VBI_LINE_FLAG_P_0_reg)=data)
#define set_TVE_VBI_LINE_FLAG_P_1_reg(data)   (*((volatile unsigned int*) TVE_VBI_LINE_FLAG_P_1_reg)=data)
#define get_TVE_VBI_LINE_FLAG_P_0_reg   (*((volatile unsigned int*) TVE_VBI_LINE_FLAG_P_0_reg))
#define get_TVE_VBI_LINE_FLAG_P_1_reg   (*((volatile unsigned int*) TVE_VBI_LINE_FLAG_P_1_reg))
#define TVE_VBI_LINE_FLAG_P_0_inst_adr                                               "0x00CB"
#define TVE_VBI_LINE_FLAG_P_1_inst_adr                                               "0x00CC"
#define TVE_VBI_LINE_FLAG_P_0_inst                                                   0x00CB
#define TVE_VBI_LINE_FLAG_P_1_inst                                                   0x00CC
#define TVE_VBI_LINE_FLAG_P_vbi_line_flg_shift                                       (0)
#define TVE_VBI_LINE_FLAG_P_vbi_line_flg_mask                                        (0xFFFFFFFF)
#define TVE_VBI_LINE_FLAG_P_vbi_line_flg(data)                                       (0xFFFFFFFF&((data)<<0))
#define TVE_VBI_LINE_FLAG_P_vbi_line_flg_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define TVE_VBI_LINE_FLAG_P_get_vbi_line_flg(data)                                   ((0xFFFFFFFF&(data))>>0)


#define TVE_VBI_LINE_PTY_I_0                                                         0x18018334
#define TVE_VBI_LINE_PTY_I_1                                                         0x18018338
#define TVE_VBI_LINE_PTY_I_0_reg_addr                                                "0xB8018334"
#define TVE_VBI_LINE_PTY_I_1_reg_addr                                                "0xB8018338"
#define TVE_VBI_LINE_PTY_I_0_reg                                                     0xB8018334
#define TVE_VBI_LINE_PTY_I_1_reg                                                     0xB8018338
#define set_TVE_VBI_LINE_PTY_I_0_reg(data)   (*((volatile unsigned int*) TVE_VBI_LINE_PTY_I_0_reg)=data)
#define set_TVE_VBI_LINE_PTY_I_1_reg(data)   (*((volatile unsigned int*) TVE_VBI_LINE_PTY_I_1_reg)=data)
#define get_TVE_VBI_LINE_PTY_I_0_reg   (*((volatile unsigned int*) TVE_VBI_LINE_PTY_I_0_reg))
#define get_TVE_VBI_LINE_PTY_I_1_reg   (*((volatile unsigned int*) TVE_VBI_LINE_PTY_I_1_reg))
#define TVE_VBI_LINE_PTY_I_0_inst_adr                                                "0x00CD"
#define TVE_VBI_LINE_PTY_I_1_inst_adr                                                "0x00CE"
#define TVE_VBI_LINE_PTY_I_0_inst                                                    0x00CD
#define TVE_VBI_LINE_PTY_I_1_inst                                                    0x00CE
#define TVE_VBI_LINE_PTY_I_vbi_pty_shift                                             (0)
#define TVE_VBI_LINE_PTY_I_vbi_pty_mask                                              (0xFFFFFFFF)
#define TVE_VBI_LINE_PTY_I_vbi_pty(data)                                             (0xFFFFFFFF&((data)<<0))
#define TVE_VBI_LINE_PTY_I_vbi_pty_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define TVE_VBI_LINE_PTY_I_get_vbi_pty(data)                                         ((0xFFFFFFFF&(data))>>0)


#define TVE_VBI_LINE_PTY_P_0                                                         0x1801833C
#define TVE_VBI_LINE_PTY_P_1                                                         0x18018340
#define TVE_VBI_LINE_PTY_P_0_reg_addr                                                "0xB801833C"
#define TVE_VBI_LINE_PTY_P_1_reg_addr                                                "0xB8018340"
#define TVE_VBI_LINE_PTY_P_0_reg                                                     0xB801833C
#define TVE_VBI_LINE_PTY_P_1_reg                                                     0xB8018340
#define set_TVE_VBI_LINE_PTY_P_0_reg(data)   (*((volatile unsigned int*) TVE_VBI_LINE_PTY_P_0_reg)=data)
#define set_TVE_VBI_LINE_PTY_P_1_reg(data)   (*((volatile unsigned int*) TVE_VBI_LINE_PTY_P_1_reg)=data)
#define get_TVE_VBI_LINE_PTY_P_0_reg   (*((volatile unsigned int*) TVE_VBI_LINE_PTY_P_0_reg))
#define get_TVE_VBI_LINE_PTY_P_1_reg   (*((volatile unsigned int*) TVE_VBI_LINE_PTY_P_1_reg))
#define TVE_VBI_LINE_PTY_P_0_inst_adr                                                "0x00CF"
#define TVE_VBI_LINE_PTY_P_1_inst_adr                                                "0x00D0"
#define TVE_VBI_LINE_PTY_P_0_inst                                                    0x00CF
#define TVE_VBI_LINE_PTY_P_1_inst                                                    0x00D0
#define TVE_VBI_LINE_PTY_P_vbi_pty_shift                                             (0)
#define TVE_VBI_LINE_PTY_P_vbi_pty_mask                                              (0xFFFFFFFF)
#define TVE_VBI_LINE_PTY_P_vbi_pty(data)                                             (0xFFFFFFFF&((data)<<0))
#define TVE_VBI_LINE_PTY_P_vbi_pty_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define TVE_VBI_LINE_PTY_P_get_vbi_pty(data)                                         ((0xFFFFFFFF&(data))>>0)


#define TVE_DIF_HACTIVE                                                              0x180181b0
#define TVE_DIF_HACTIVE_reg_addr                                                     "0xB80181B0"
#define TVE_DIF_HACTIVE_reg                                                          0xB80181B0
#define set_TVE_DIF_HACTIVE_reg(data)   (*((volatile unsigned int*) TVE_DIF_HACTIVE_reg)=data)
#define get_TVE_DIF_HACTIVE_reg   (*((volatile unsigned int*) TVE_DIF_HACTIVE_reg))
#define TVE_DIF_HACTIVE_inst_adr                                                     "0x006C"
#define TVE_DIF_HACTIVE_inst                                                         0x006C
#define TVE_DIF_HACTIVE_write_en3_shift                                              (30)
#define TVE_DIF_HACTIVE_write_en3_mask                                               (0x40000000)
#define TVE_DIF_HACTIVE_write_en3(data)                                              (0x40000000&((data)<<30))
#define TVE_DIF_HACTIVE_write_en3_src(data)                                          ((0x40000000&(data))>>30)
#define TVE_DIF_HACTIVE_get_write_en3(data)                                          ((0x40000000&(data))>>30)
#define TVE_DIF_HACTIVE_di_i_p_sel_shift                                             (28)
#define TVE_DIF_HACTIVE_di_i_p_sel_mask                                              (0x30000000)
#define TVE_DIF_HACTIVE_di_i_p_sel(data)                                             (0x30000000&((data)<<28))
#define TVE_DIF_HACTIVE_di_i_p_sel_src(data)                                         ((0x30000000&(data))>>28)
#define TVE_DIF_HACTIVE_get_di_i_p_sel(data)                                         ((0x30000000&(data))>>28)
#define TVE_DIF_HACTIVE_write_en2_shift                                              (27)
#define TVE_DIF_HACTIVE_write_en2_mask                                               (0x08000000)
#define TVE_DIF_HACTIVE_write_en2(data)                                              (0x08000000&((data)<<27))
#define TVE_DIF_HACTIVE_write_en2_src(data)                                          ((0x08000000&(data))>>27)
#define TVE_DIF_HACTIVE_get_write_en2(data)                                          ((0x08000000&(data))>>27)
#define TVE_DIF_HACTIVE_hact_start_shift                                             (14)
#define TVE_DIF_HACTIVE_hact_start_mask                                              (0x07FFC000)
#define TVE_DIF_HACTIVE_hact_start(data)                                             (0x07FFC000&((data)<<14))
#define TVE_DIF_HACTIVE_hact_start_src(data)                                         ((0x07FFC000&(data))>>14)
#define TVE_DIF_HACTIVE_get_hact_start(data)                                         ((0x07FFC000&(data))>>14)
#define TVE_DIF_HACTIVE_write_en1_shift                                              (13)
#define TVE_DIF_HACTIVE_write_en1_mask                                               (0x00002000)
#define TVE_DIF_HACTIVE_write_en1(data)                                              (0x00002000&((data)<<13))
#define TVE_DIF_HACTIVE_write_en1_src(data)                                          ((0x00002000&(data))>>13)
#define TVE_DIF_HACTIVE_get_write_en1(data)                                          ((0x00002000&(data))>>13)
#define TVE_DIF_HACTIVE_hact_end_shift                                               (0)
#define TVE_DIF_HACTIVE_hact_end_mask                                                (0x00001FFF)
#define TVE_DIF_HACTIVE_hact_end(data)                                               (0x00001FFF&((data)<<0))
#define TVE_DIF_HACTIVE_hact_end_src(data)                                           ((0x00001FFF&(data))>>0)
#define TVE_DIF_HACTIVE_get_hact_end(data)                                           ((0x00001FFF&(data))>>0)


#define TVE_DIF_CTRL                                                                 0x180181b4
#define TVE_DIF_CTRL_reg_addr                                                        "0xB80181B4"
#define TVE_DIF_CTRL_reg                                                             0xB80181B4
#define set_TVE_DIF_CTRL_reg(data)   (*((volatile unsigned int*) TVE_DIF_CTRL_reg)=data)
#define get_TVE_DIF_CTRL_reg   (*((volatile unsigned int*) TVE_DIF_CTRL_reg))
#define TVE_DIF_CTRL_inst_adr                                                        "0x006D"
#define TVE_DIF_CTRL_inst                                                            0x006D
#define TVE_DIF_CTRL_cd_shift                                                        (9)
#define TVE_DIF_CTRL_cd_mask                                                         (0x00000200)
#define TVE_DIF_CTRL_cd(data)                                                        (0x00000200&((data)<<9))
#define TVE_DIF_CTRL_cd_src(data)                                                    ((0x00000200&(data))>>9)
#define TVE_DIF_CTRL_get_cd(data)                                                    ((0x00000200&(data))>>9)
#define TVE_DIF_CTRL_di_bus_swap_shift                                               (8)
#define TVE_DIF_CTRL_di_bus_swap_mask                                                (0x00000100)
#define TVE_DIF_CTRL_di_bus_swap(data)                                               (0x00000100&((data)<<8))
#define TVE_DIF_CTRL_di_bus_swap_src(data)                                           ((0x00000100&(data))>>8)
#define TVE_DIF_CTRL_get_di_bus_swap(data)                                           ((0x00000100&(data))>>8)
#define TVE_DIF_CTRL_di_clk_phs_shift                                                (7)
#define TVE_DIF_CTRL_di_clk_phs_mask                                                 (0x00000080)
#define TVE_DIF_CTRL_di_clk_phs(data)                                                (0x00000080&((data)<<7))
#define TVE_DIF_CTRL_di_clk_phs_src(data)                                            ((0x00000080&(data))>>7)
#define TVE_DIF_CTRL_get_di_clk_phs(data)                                            ((0x00000080&(data))>>7)
#define TVE_DIF_CTRL_di_fpga_clk_sel_shift                                           (6)
#define TVE_DIF_CTRL_di_fpga_clk_sel_mask                                            (0x00000040)
#define TVE_DIF_CTRL_di_fpga_clk_sel(data)                                           (0x00000040&((data)<<6))
#define TVE_DIF_CTRL_di_fpga_clk_sel_src(data)                                       ((0x00000040&(data))>>6)
#define TVE_DIF_CTRL_get_di_fpga_clk_sel(data)                                       ((0x00000040&(data))>>6)
#define TVE_DIF_CTRL_di_vbi_bypass_shift                                             (5)
#define TVE_DIF_CTRL_di_vbi_bypass_mask                                              (0x00000020)
#define TVE_DIF_CTRL_di_vbi_bypass(data)                                             (0x00000020&((data)<<5))
#define TVE_DIF_CTRL_di_vbi_bypass_src(data)                                         ((0x00000020&(data))>>5)
#define TVE_DIF_CTRL_get_di_vbi_bypass(data)                                         ((0x00000020&(data))>>5)
#define TVE_DIF_CTRL_di_ebl_shift                                                    (4)
#define TVE_DIF_CTRL_di_ebl_mask                                                     (0x00000010)
#define TVE_DIF_CTRL_di_ebl(data)                                                    (0x00000010&((data)<<4))
#define TVE_DIF_CTRL_di_ebl_src(data)                                                ((0x00000010&(data))>>4)
#define TVE_DIF_CTRL_get_di_ebl(data)                                                ((0x00000010&(data))>>4)
#define TVE_DIF_CTRL_di_source_sel_shift                                             (3)
#define TVE_DIF_CTRL_di_source_sel_mask                                              (0x00000008)
#define TVE_DIF_CTRL_di_source_sel(data)                                             (0x00000008&((data)<<3))
#define TVE_DIF_CTRL_di_source_sel_src(data)                                         ((0x00000008&(data))>>3)
#define TVE_DIF_CTRL_get_di_source_sel(data)                                         ((0x00000008&(data))>>3)
#define TVE_DIF_CTRL_di_mod_shift                                                    (2)
#define TVE_DIF_CTRL_di_mod_mask                                                     (0x00000004)
#define TVE_DIF_CTRL_di_mod(data)                                                    (0x00000004&((data)<<2))
#define TVE_DIF_CTRL_di_mod_src(data)                                                ((0x00000004&(data))>>2)
#define TVE_DIF_CTRL_get_di_mod(data)                                                ((0x00000004&(data))>>2)
#define TVE_DIF_CTRL_di_hdr_ebl_shift                                                (1)
#define TVE_DIF_CTRL_di_hdr_ebl_mask                                                 (0x00000002)
#define TVE_DIF_CTRL_di_hdr_ebl(data)                                                (0x00000002&((data)<<1))
#define TVE_DIF_CTRL_di_hdr_ebl_src(data)                                            ((0x00000002&(data))>>1)
#define TVE_DIF_CTRL_get_di_hdr_ebl(data)                                            ((0x00000002&(data))>>1)
#define TVE_DIF_CTRL_write_data_shift                                                (0)
#define TVE_DIF_CTRL_write_data_mask                                                 (0x00000001)
#define TVE_DIF_CTRL_write_data(data)                                                (0x00000001&((data)<<0))
#define TVE_DIF_CTRL_write_data_src(data)                                            ((0x00000001&(data))>>0)
#define TVE_DIF_CTRL_get_write_data(data)                                            ((0x00000001&(data))>>0)


#define TVE_DIF_HSYNC                                                                0x180181b8
#define TVE_DIF_HSYNC_reg_addr                                                       "0xB80181B8"
#define TVE_DIF_HSYNC_reg                                                            0xB80181B8
#define set_TVE_DIF_HSYNC_reg(data)   (*((volatile unsigned int*) TVE_DIF_HSYNC_reg)=data)
#define get_TVE_DIF_HSYNC_reg   (*((volatile unsigned int*) TVE_DIF_HSYNC_reg))
#define TVE_DIF_HSYNC_inst_adr                                                       "0x006E"
#define TVE_DIF_HSYNC_inst                                                           0x006E
#define TVE_DIF_HSYNC_write_en3_shift                                                (29)
#define TVE_DIF_HSYNC_write_en3_mask                                                 (0x20000000)
#define TVE_DIF_HSYNC_write_en3(data)                                                (0x20000000&((data)<<29))
#define TVE_DIF_HSYNC_write_en3_src(data)                                            ((0x20000000&(data))>>29)
#define TVE_DIF_HSYNC_get_write_en3(data)                                            ((0x20000000&(data))>>29)
#define TVE_DIF_HSYNC_hs_polar_shift                                                 (28)
#define TVE_DIF_HSYNC_hs_polar_mask                                                  (0x10000000)
#define TVE_DIF_HSYNC_hs_polar(data)                                                 (0x10000000&((data)<<28))
#define TVE_DIF_HSYNC_hs_polar_src(data)                                             ((0x10000000&(data))>>28)
#define TVE_DIF_HSYNC_get_hs_polar(data)                                             ((0x10000000&(data))>>28)
#define TVE_DIF_HSYNC_write_en2_shift                                                (27)
#define TVE_DIF_HSYNC_write_en2_mask                                                 (0x08000000)
#define TVE_DIF_HSYNC_write_en2(data)                                                (0x08000000&((data)<<27))
#define TVE_DIF_HSYNC_write_en2_src(data)                                            ((0x08000000&(data))>>27)
#define TVE_DIF_HSYNC_get_write_en2(data)                                            ((0x08000000&(data))>>27)
#define TVE_DIF_HSYNC_hs_start_shift                                                 (14)
#define TVE_DIF_HSYNC_hs_start_mask                                                  (0x07FFC000)
#define TVE_DIF_HSYNC_hs_start(data)                                                 (0x07FFC000&((data)<<14))
#define TVE_DIF_HSYNC_hs_start_src(data)                                             ((0x07FFC000&(data))>>14)
#define TVE_DIF_HSYNC_get_hs_start(data)                                             ((0x07FFC000&(data))>>14)
#define TVE_DIF_HSYNC_write_en1_shift                                                (13)
#define TVE_DIF_HSYNC_write_en1_mask                                                 (0x00002000)
#define TVE_DIF_HSYNC_write_en1(data)                                                (0x00002000&((data)<<13))
#define TVE_DIF_HSYNC_write_en1_src(data)                                            ((0x00002000&(data))>>13)
#define TVE_DIF_HSYNC_get_write_en1(data)                                            ((0x00002000&(data))>>13)
#define TVE_DIF_HSYNC_hs_end_shift                                                   (0)
#define TVE_DIF_HSYNC_hs_end_mask                                                    (0x00001FFF)
#define TVE_DIF_HSYNC_hs_end(data)                                                   (0x00001FFF&((data)<<0))
#define TVE_DIF_HSYNC_hs_end_src(data)                                               ((0x00001FFF&(data))>>0)
#define TVE_DIF_HSYNC_get_hs_end(data)                                               ((0x00001FFF&(data))>>0)


#define TVE_DIF_VS_ST_POS1                                                           0x180181bc
#define TVE_DIF_VS_ST_POS1_reg_addr                                                  "0xB80181BC"
#define TVE_DIF_VS_ST_POS1_reg                                                       0xB80181BC
#define set_TVE_DIF_VS_ST_POS1_reg(data)   (*((volatile unsigned int*) TVE_DIF_VS_ST_POS1_reg)=data)
#define get_TVE_DIF_VS_ST_POS1_reg   (*((volatile unsigned int*) TVE_DIF_VS_ST_POS1_reg))
#define TVE_DIF_VS_ST_POS1_inst_adr                                                  "0x006F"
#define TVE_DIF_VS_ST_POS1_inst                                                      0x006F
#define TVE_DIF_VS_ST_POS1_write_en3_shift                                           (27)
#define TVE_DIF_VS_ST_POS1_write_en3_mask                                            (0x08000000)
#define TVE_DIF_VS_ST_POS1_write_en3(data)                                           (0x08000000&((data)<<27))
#define TVE_DIF_VS_ST_POS1_write_en3_src(data)                                       ((0x08000000&(data))>>27)
#define TVE_DIF_VS_ST_POS1_get_write_en3(data)                                       ((0x08000000&(data))>>27)
#define TVE_DIF_VS_ST_POS1_vs_polar_shift                                            (26)
#define TVE_DIF_VS_ST_POS1_vs_polar_mask                                             (0x04000000)
#define TVE_DIF_VS_ST_POS1_vs_polar(data)                                            (0x04000000&((data)<<26))
#define TVE_DIF_VS_ST_POS1_vs_polar_src(data)                                        ((0x04000000&(data))>>26)
#define TVE_DIF_VS_ST_POS1_get_vs_polar(data)                                        ((0x04000000&(data))>>26)
#define TVE_DIF_VS_ST_POS1_write_en2_shift                                           (25)
#define TVE_DIF_VS_ST_POS1_write_en2_mask                                            (0x02000000)
#define TVE_DIF_VS_ST_POS1_write_en2(data)                                           (0x02000000&((data)<<25))
#define TVE_DIF_VS_ST_POS1_write_en2_src(data)                                       ((0x02000000&(data))>>25)
#define TVE_DIF_VS_ST_POS1_get_write_en2(data)                                       ((0x02000000&(data))>>25)
#define TVE_DIF_VS_ST_POS1_vs_st_pos1v_shift                                         (14)
#define TVE_DIF_VS_ST_POS1_vs_st_pos1v_mask                                          (0x01FFC000)
#define TVE_DIF_VS_ST_POS1_vs_st_pos1v(data)                                         (0x01FFC000&((data)<<14))
#define TVE_DIF_VS_ST_POS1_vs_st_pos1v_src(data)                                     ((0x01FFC000&(data))>>14)
#define TVE_DIF_VS_ST_POS1_get_vs_st_pos1v(data)                                     ((0x01FFC000&(data))>>14)
#define TVE_DIF_VS_ST_POS1_write_en1_shift                                           (13)
#define TVE_DIF_VS_ST_POS1_write_en1_mask                                            (0x00002000)
#define TVE_DIF_VS_ST_POS1_write_en1(data)                                           (0x00002000&((data)<<13))
#define TVE_DIF_VS_ST_POS1_write_en1_src(data)                                       ((0x00002000&(data))>>13)
#define TVE_DIF_VS_ST_POS1_get_write_en1(data)                                       ((0x00002000&(data))>>13)
#define TVE_DIF_VS_ST_POS1_vs_st_pos1h_shift                                         (0)
#define TVE_DIF_VS_ST_POS1_vs_st_pos1h_mask                                          (0x00001FFF)
#define TVE_DIF_VS_ST_POS1_vs_st_pos1h(data)                                         (0x00001FFF&((data)<<0))
#define TVE_DIF_VS_ST_POS1_vs_st_pos1h_src(data)                                     ((0x00001FFF&(data))>>0)
#define TVE_DIF_VS_ST_POS1_get_vs_st_pos1h(data)                                     ((0x00001FFF&(data))>>0)


#define TVE_DIF_VS_END_POS1                                                          0x180181c0
#define TVE_DIF_VS_END_POS1_reg_addr                                                 "0xB80181C0"
#define TVE_DIF_VS_END_POS1_reg                                                      0xB80181C0
#define set_TVE_DIF_VS_END_POS1_reg(data)   (*((volatile unsigned int*) TVE_DIF_VS_END_POS1_reg)=data)
#define get_TVE_DIF_VS_END_POS1_reg   (*((volatile unsigned int*) TVE_DIF_VS_END_POS1_reg))
#define TVE_DIF_VS_END_POS1_inst_adr                                                 "0x0070"
#define TVE_DIF_VS_END_POS1_inst                                                     0x0070
#define TVE_DIF_VS_END_POS1_write_en2_shift                                          (25)
#define TVE_DIF_VS_END_POS1_write_en2_mask                                           (0x02000000)
#define TVE_DIF_VS_END_POS1_write_en2(data)                                          (0x02000000&((data)<<25))
#define TVE_DIF_VS_END_POS1_write_en2_src(data)                                      ((0x02000000&(data))>>25)
#define TVE_DIF_VS_END_POS1_get_write_en2(data)                                      ((0x02000000&(data))>>25)
#define TVE_DIF_VS_END_POS1_vs_end_pos1v_shift                                       (14)
#define TVE_DIF_VS_END_POS1_vs_end_pos1v_mask                                        (0x01FFC000)
#define TVE_DIF_VS_END_POS1_vs_end_pos1v(data)                                       (0x01FFC000&((data)<<14))
#define TVE_DIF_VS_END_POS1_vs_end_pos1v_src(data)                                   ((0x01FFC000&(data))>>14)
#define TVE_DIF_VS_END_POS1_get_vs_end_pos1v(data)                                   ((0x01FFC000&(data))>>14)
#define TVE_DIF_VS_END_POS1_write_en1_shift                                          (13)
#define TVE_DIF_VS_END_POS1_write_en1_mask                                           (0x00002000)
#define TVE_DIF_VS_END_POS1_write_en1(data)                                          (0x00002000&((data)<<13))
#define TVE_DIF_VS_END_POS1_write_en1_src(data)                                      ((0x00002000&(data))>>13)
#define TVE_DIF_VS_END_POS1_get_write_en1(data)                                      ((0x00002000&(data))>>13)
#define TVE_DIF_VS_END_POS1_vs_end_pos1h_shift                                       (0)
#define TVE_DIF_VS_END_POS1_vs_end_pos1h_mask                                        (0x00001FFF)
#define TVE_DIF_VS_END_POS1_vs_end_pos1h(data)                                       (0x00001FFF&((data)<<0))
#define TVE_DIF_VS_END_POS1_vs_end_pos1h_src(data)                                   ((0x00001FFF&(data))>>0)
#define TVE_DIF_VS_END_POS1_get_vs_end_pos1h(data)                                   ((0x00001FFF&(data))>>0)


#define TVE_DIF_VS_ST_POS2                                                           0x180181c4
#define TVE_DIF_VS_ST_POS2_reg_addr                                                  "0xB80181C4"
#define TVE_DIF_VS_ST_POS2_reg                                                       0xB80181C4
#define set_TVE_DIF_VS_ST_POS2_reg(data)   (*((volatile unsigned int*) TVE_DIF_VS_ST_POS2_reg)=data)
#define get_TVE_DIF_VS_ST_POS2_reg   (*((volatile unsigned int*) TVE_DIF_VS_ST_POS2_reg))
#define TVE_DIF_VS_ST_POS2_inst_adr                                                  "0x0071"
#define TVE_DIF_VS_ST_POS2_inst                                                      0x0071
#define TVE_DIF_VS_ST_POS2_write_en2_shift                                           (25)
#define TVE_DIF_VS_ST_POS2_write_en2_mask                                            (0x02000000)
#define TVE_DIF_VS_ST_POS2_write_en2(data)                                           (0x02000000&((data)<<25))
#define TVE_DIF_VS_ST_POS2_write_en2_src(data)                                       ((0x02000000&(data))>>25)
#define TVE_DIF_VS_ST_POS2_get_write_en2(data)                                       ((0x02000000&(data))>>25)
#define TVE_DIF_VS_ST_POS2_vs_st_pos2v_shift                                         (14)
#define TVE_DIF_VS_ST_POS2_vs_st_pos2v_mask                                          (0x01FFC000)
#define TVE_DIF_VS_ST_POS2_vs_st_pos2v(data)                                         (0x01FFC000&((data)<<14))
#define TVE_DIF_VS_ST_POS2_vs_st_pos2v_src(data)                                     ((0x01FFC000&(data))>>14)
#define TVE_DIF_VS_ST_POS2_get_vs_st_pos2v(data)                                     ((0x01FFC000&(data))>>14)
#define TVE_DIF_VS_ST_POS2_write_en1_shift                                           (13)
#define TVE_DIF_VS_ST_POS2_write_en1_mask                                            (0x00002000)
#define TVE_DIF_VS_ST_POS2_write_en1(data)                                           (0x00002000&((data)<<13))
#define TVE_DIF_VS_ST_POS2_write_en1_src(data)                                       ((0x00002000&(data))>>13)
#define TVE_DIF_VS_ST_POS2_get_write_en1(data)                                       ((0x00002000&(data))>>13)
#define TVE_DIF_VS_ST_POS2_vs_st_pos2h_shift                                         (0)
#define TVE_DIF_VS_ST_POS2_vs_st_pos2h_mask                                          (0x00001FFF)
#define TVE_DIF_VS_ST_POS2_vs_st_pos2h(data)                                         (0x00001FFF&((data)<<0))
#define TVE_DIF_VS_ST_POS2_vs_st_pos2h_src(data)                                     ((0x00001FFF&(data))>>0)
#define TVE_DIF_VS_ST_POS2_get_vs_st_pos2h(data)                                     ((0x00001FFF&(data))>>0)


#define TVE_DIF_VS_END_POS2                                                          0x180181c8
#define TVE_DIF_VS_END_POS2_reg_addr                                                 "0xB80181C8"
#define TVE_DIF_VS_END_POS2_reg                                                      0xB80181C8
#define set_TVE_DIF_VS_END_POS2_reg(data)   (*((volatile unsigned int*) TVE_DIF_VS_END_POS2_reg)=data)
#define get_TVE_DIF_VS_END_POS2_reg   (*((volatile unsigned int*) TVE_DIF_VS_END_POS2_reg))
#define TVE_DIF_VS_END_POS2_inst_adr                                                 "0x0072"
#define TVE_DIF_VS_END_POS2_inst                                                     0x0072
#define TVE_DIF_VS_END_POS2_write_en2_shift                                          (25)
#define TVE_DIF_VS_END_POS2_write_en2_mask                                           (0x02000000)
#define TVE_DIF_VS_END_POS2_write_en2(data)                                          (0x02000000&((data)<<25))
#define TVE_DIF_VS_END_POS2_write_en2_src(data)                                      ((0x02000000&(data))>>25)
#define TVE_DIF_VS_END_POS2_get_write_en2(data)                                      ((0x02000000&(data))>>25)
#define TVE_DIF_VS_END_POS2_vs_end_pos2v_shift                                       (14)
#define TVE_DIF_VS_END_POS2_vs_end_pos2v_mask                                        (0x01FFC000)
#define TVE_DIF_VS_END_POS2_vs_end_pos2v(data)                                       (0x01FFC000&((data)<<14))
#define TVE_DIF_VS_END_POS2_vs_end_pos2v_src(data)                                   ((0x01FFC000&(data))>>14)
#define TVE_DIF_VS_END_POS2_get_vs_end_pos2v(data)                                   ((0x01FFC000&(data))>>14)
#define TVE_DIF_VS_END_POS2_write_en1_shift                                          (13)
#define TVE_DIF_VS_END_POS2_write_en1_mask                                           (0x00002000)
#define TVE_DIF_VS_END_POS2_write_en1(data)                                          (0x00002000&((data)<<13))
#define TVE_DIF_VS_END_POS2_write_en1_src(data)                                      ((0x00002000&(data))>>13)
#define TVE_DIF_VS_END_POS2_get_write_en1(data)                                      ((0x00002000&(data))>>13)
#define TVE_DIF_VS_END_POS2_vs_end_pos2h_shift                                       (0)
#define TVE_DIF_VS_END_POS2_vs_end_pos2h_mask                                        (0x00001FFF)
#define TVE_DIF_VS_END_POS2_vs_end_pos2h(data)                                       (0x00001FFF&((data)<<0))
#define TVE_DIF_VS_END_POS2_vs_end_pos2h_src(data)                                   ((0x00001FFF&(data))>>0)
#define TVE_DIF_VS_END_POS2_get_vs_end_pos2h(data)                                   ((0x00001FFF&(data))>>0)


#define TVE_DIF_F_BIT_POS                                                            0x180181cc
#define TVE_DIF_F_BIT_POS_reg_addr                                                   "0xB80181CC"
#define TVE_DIF_F_BIT_POS_reg                                                        0xB80181CC
#define set_TVE_DIF_F_BIT_POS_reg(data)   (*((volatile unsigned int*) TVE_DIF_F_BIT_POS_reg)=data)
#define get_TVE_DIF_F_BIT_POS_reg   (*((volatile unsigned int*) TVE_DIF_F_BIT_POS_reg))
#define TVE_DIF_F_BIT_POS_inst_adr                                                   "0x0073"
#define TVE_DIF_F_BIT_POS_inst                                                       0x0073
#define TVE_DIF_F_BIT_POS_write_en2_shift                                            (23)
#define TVE_DIF_F_BIT_POS_write_en2_mask                                             (0x00800000)
#define TVE_DIF_F_BIT_POS_write_en2(data)                                            (0x00800000&((data)<<23))
#define TVE_DIF_F_BIT_POS_write_en2_src(data)                                        ((0x00800000&(data))>>23)
#define TVE_DIF_F_BIT_POS_get_write_en2(data)                                        ((0x00800000&(data))>>23)
#define TVE_DIF_F_BIT_POS_v_tgl_hi_shift                                             (12)
#define TVE_DIF_F_BIT_POS_v_tgl_hi_mask                                              (0x007FF000)
#define TVE_DIF_F_BIT_POS_v_tgl_hi(data)                                             (0x007FF000&((data)<<12))
#define TVE_DIF_F_BIT_POS_v_tgl_hi_src(data)                                         ((0x007FF000&(data))>>12)
#define TVE_DIF_F_BIT_POS_get_v_tgl_hi(data)                                         ((0x007FF000&(data))>>12)
#define TVE_DIF_F_BIT_POS_write_en1_shift                                            (11)
#define TVE_DIF_F_BIT_POS_write_en1_mask                                             (0x00000800)
#define TVE_DIF_F_BIT_POS_write_en1(data)                                            (0x00000800&((data)<<11))
#define TVE_DIF_F_BIT_POS_write_en1_src(data)                                        ((0x00000800&(data))>>11)
#define TVE_DIF_F_BIT_POS_get_write_en1(data)                                        ((0x00000800&(data))>>11)
#define TVE_DIF_F_BIT_POS_v_tgl_lo_shift                                             (0)
#define TVE_DIF_F_BIT_POS_v_tgl_lo_mask                                              (0x000007FF)
#define TVE_DIF_F_BIT_POS_v_tgl_lo(data)                                             (0x000007FF&((data)<<0))
#define TVE_DIF_F_BIT_POS_v_tgl_lo_src(data)                                         ((0x000007FF&(data))>>0)
#define TVE_DIF_F_BIT_POS_get_v_tgl_lo(data)                                         ((0x000007FF&(data))>>0)


#define TVE_DIF_V_BIT_POS1                                                           0x180181d0
#define TVE_DIF_V_BIT_POS1_reg_addr                                                  "0xB80181D0"
#define TVE_DIF_V_BIT_POS1_reg                                                       0xB80181D0
#define set_TVE_DIF_V_BIT_POS1_reg(data)   (*((volatile unsigned int*) TVE_DIF_V_BIT_POS1_reg)=data)
#define get_TVE_DIF_V_BIT_POS1_reg   (*((volatile unsigned int*) TVE_DIF_V_BIT_POS1_reg))
#define TVE_DIF_V_BIT_POS1_inst_adr                                                  "0x0074"
#define TVE_DIF_V_BIT_POS1_inst                                                      0x0074
#define TVE_DIF_V_BIT_POS1_write_en2_shift                                           (23)
#define TVE_DIF_V_BIT_POS1_write_en2_mask                                            (0x00800000)
#define TVE_DIF_V_BIT_POS1_write_en2(data)                                           (0x00800000&((data)<<23))
#define TVE_DIF_V_BIT_POS1_write_en2_src(data)                                       ((0x00800000&(data))>>23)
#define TVE_DIF_V_BIT_POS1_get_write_en2(data)                                       ((0x00800000&(data))>>23)
#define TVE_DIF_V_BIT_POS1_v_tgl1_hi_shift                                           (12)
#define TVE_DIF_V_BIT_POS1_v_tgl1_hi_mask                                            (0x007FF000)
#define TVE_DIF_V_BIT_POS1_v_tgl1_hi(data)                                           (0x007FF000&((data)<<12))
#define TVE_DIF_V_BIT_POS1_v_tgl1_hi_src(data)                                       ((0x007FF000&(data))>>12)
#define TVE_DIF_V_BIT_POS1_get_v_tgl1_hi(data)                                       ((0x007FF000&(data))>>12)
#define TVE_DIF_V_BIT_POS1_write_en1_shift                                           (11)
#define TVE_DIF_V_BIT_POS1_write_en1_mask                                            (0x00000800)
#define TVE_DIF_V_BIT_POS1_write_en1(data)                                           (0x00000800&((data)<<11))
#define TVE_DIF_V_BIT_POS1_write_en1_src(data)                                       ((0x00000800&(data))>>11)
#define TVE_DIF_V_BIT_POS1_get_write_en1(data)                                       ((0x00000800&(data))>>11)
#define TVE_DIF_V_BIT_POS1_v_tgl1_lo_shift                                           (0)
#define TVE_DIF_V_BIT_POS1_v_tgl1_lo_mask                                            (0x000007FF)
#define TVE_DIF_V_BIT_POS1_v_tgl1_lo(data)                                           (0x000007FF&((data)<<0))
#define TVE_DIF_V_BIT_POS1_v_tgl1_lo_src(data)                                       ((0x000007FF&(data))>>0)
#define TVE_DIF_V_BIT_POS1_get_v_tgl1_lo(data)                                       ((0x000007FF&(data))>>0)


#define TVE_DIF_V_BIT_POS2                                                           0x180181d4
#define TVE_DIF_V_BIT_POS2_reg_addr                                                  "0xB80181D4"
#define TVE_DIF_V_BIT_POS2_reg                                                       0xB80181D4
#define set_TVE_DIF_V_BIT_POS2_reg(data)   (*((volatile unsigned int*) TVE_DIF_V_BIT_POS2_reg)=data)
#define get_TVE_DIF_V_BIT_POS2_reg   (*((volatile unsigned int*) TVE_DIF_V_BIT_POS2_reg))
#define TVE_DIF_V_BIT_POS2_inst_adr                                                  "0x0075"
#define TVE_DIF_V_BIT_POS2_inst                                                      0x0075
#define TVE_DIF_V_BIT_POS2_write_en2_shift                                           (23)
#define TVE_DIF_V_BIT_POS2_write_en2_mask                                            (0x00800000)
#define TVE_DIF_V_BIT_POS2_write_en2(data)                                           (0x00800000&((data)<<23))
#define TVE_DIF_V_BIT_POS2_write_en2_src(data)                                       ((0x00800000&(data))>>23)
#define TVE_DIF_V_BIT_POS2_get_write_en2(data)                                       ((0x00800000&(data))>>23)
#define TVE_DIF_V_BIT_POS2_v_tgl2_hi_shift                                           (12)
#define TVE_DIF_V_BIT_POS2_v_tgl2_hi_mask                                            (0x007FF000)
#define TVE_DIF_V_BIT_POS2_v_tgl2_hi(data)                                           (0x007FF000&((data)<<12))
#define TVE_DIF_V_BIT_POS2_v_tgl2_hi_src(data)                                       ((0x007FF000&(data))>>12)
#define TVE_DIF_V_BIT_POS2_get_v_tgl2_hi(data)                                       ((0x007FF000&(data))>>12)
#define TVE_DIF_V_BIT_POS2_write_en1_shift                                           (11)
#define TVE_DIF_V_BIT_POS2_write_en1_mask                                            (0x00000800)
#define TVE_DIF_V_BIT_POS2_write_en1(data)                                           (0x00000800&((data)<<11))
#define TVE_DIF_V_BIT_POS2_write_en1_src(data)                                       ((0x00000800&(data))>>11)
#define TVE_DIF_V_BIT_POS2_get_write_en1(data)                                       ((0x00000800&(data))>>11)
#define TVE_DIF_V_BIT_POS2_v_tgl2_lo_shift                                           (0)
#define TVE_DIF_V_BIT_POS2_v_tgl2_lo_mask                                            (0x000007FF)
#define TVE_DIF_V_BIT_POS2_v_tgl2_lo(data)                                           (0x000007FF&((data)<<0))
#define TVE_DIF_V_BIT_POS2_v_tgl2_lo_src(data)                                       ((0x000007FF&(data))>>0)
#define TVE_DIF_V_BIT_POS2_get_v_tgl2_lo(data)                                       ((0x000007FF&(data))>>0)


#define TVE_DIF_FV_BIT_HPOS                                                          0x180181d8
#define TVE_DIF_FV_BIT_HPOS_reg_addr                                                 "0xB80181D8"
#define TVE_DIF_FV_BIT_HPOS_reg                                                      0xB80181D8
#define set_TVE_DIF_FV_BIT_HPOS_reg(data)   (*((volatile unsigned int*) TVE_DIF_FV_BIT_HPOS_reg)=data)
#define get_TVE_DIF_FV_BIT_HPOS_reg   (*((volatile unsigned int*) TVE_DIF_FV_BIT_HPOS_reg))
#define TVE_DIF_FV_BIT_HPOS_inst_adr                                                 "0x0076"
#define TVE_DIF_FV_BIT_HPOS_inst                                                     0x0076
#define TVE_DIF_FV_BIT_HPOS_write_en2_shift                                          (27)
#define TVE_DIF_FV_BIT_HPOS_write_en2_mask                                           (0x08000000)
#define TVE_DIF_FV_BIT_HPOS_write_en2(data)                                          (0x08000000&((data)<<27))
#define TVE_DIF_FV_BIT_HPOS_write_en2_src(data)                                      ((0x08000000&(data))>>27)
#define TVE_DIF_FV_BIT_HPOS_get_write_en2(data)                                      ((0x08000000&(data))>>27)
#define TVE_DIF_FV_BIT_HPOS_fv_start_shift                                           (14)
#define TVE_DIF_FV_BIT_HPOS_fv_start_mask                                            (0x07FFC000)
#define TVE_DIF_FV_BIT_HPOS_fv_start(data)                                           (0x07FFC000&((data)<<14))
#define TVE_DIF_FV_BIT_HPOS_fv_start_src(data)                                       ((0x07FFC000&(data))>>14)
#define TVE_DIF_FV_BIT_HPOS_get_fv_start(data)                                       ((0x07FFC000&(data))>>14)
#define TVE_DIF_FV_BIT_HPOS_write_en1_shift                                          (13)
#define TVE_DIF_FV_BIT_HPOS_write_en1_mask                                           (0x00002000)
#define TVE_DIF_FV_BIT_HPOS_write_en1(data)                                          (0x00002000&((data)<<13))
#define TVE_DIF_FV_BIT_HPOS_write_en1_src(data)                                      ((0x00002000&(data))>>13)
#define TVE_DIF_FV_BIT_HPOS_get_write_en1(data)                                      ((0x00002000&(data))>>13)
#define TVE_DIF_FV_BIT_HPOS_fv_end_shift                                             (0)
#define TVE_DIF_FV_BIT_HPOS_fv_end_mask                                              (0x00001FFF)
#define TVE_DIF_FV_BIT_HPOS_fv_end(data)                                             (0x00001FFF&((data)<<0))
#define TVE_DIF_FV_BIT_HPOS_fv_end_src(data)                                         ((0x00001FFF&(data))>>0)
#define TVE_DIF_FV_BIT_HPOS_get_fv_end(data)                                         ((0x00001FFF&(data))>>0)


#define TVE_IP_PHS_0                                                                 0x18018880
#define TVE_IP_PHS_1                                                                 0x18018884
#define TVE_IP_PHS_2                                                                 0x18018888
#define TVE_IP_PHS_3                                                                 0x1801888C
#define TVE_IP_PHS_0_reg_addr                                                        "0xB8018880"
#define TVE_IP_PHS_1_reg_addr                                                        "0xB8018884"
#define TVE_IP_PHS_2_reg_addr                                                        "0xB8018888"
#define TVE_IP_PHS_3_reg_addr                                                        "0xB801888C"
#define TVE_IP_PHS_0_reg                                                             0xB8018880
#define TVE_IP_PHS_1_reg                                                             0xB8018884
#define TVE_IP_PHS_2_reg                                                             0xB8018888
#define TVE_IP_PHS_3_reg                                                             0xB801888C
#define set_TVE_IP_PHS_0_reg(data)   (*((volatile unsigned int*) TVE_IP_PHS_0_reg)=data)
#define set_TVE_IP_PHS_1_reg(data)   (*((volatile unsigned int*) TVE_IP_PHS_1_reg)=data)
#define set_TVE_IP_PHS_2_reg(data)   (*((volatile unsigned int*) TVE_IP_PHS_2_reg)=data)
#define set_TVE_IP_PHS_3_reg(data)   (*((volatile unsigned int*) TVE_IP_PHS_3_reg)=data)
#define get_TVE_IP_PHS_0_reg   (*((volatile unsigned int*) TVE_IP_PHS_0_reg))
#define get_TVE_IP_PHS_1_reg   (*((volatile unsigned int*) TVE_IP_PHS_1_reg))
#define get_TVE_IP_PHS_2_reg   (*((volatile unsigned int*) TVE_IP_PHS_2_reg))
#define get_TVE_IP_PHS_3_reg   (*((volatile unsigned int*) TVE_IP_PHS_3_reg))
#define TVE_IP_PHS_0_inst_adr                                                        "0x0020"
#define TVE_IP_PHS_1_inst_adr                                                        "0x0021"
#define TVE_IP_PHS_2_inst_adr                                                        "0x0022"
#define TVE_IP_PHS_3_inst_adr                                                        "0x0023"
#define TVE_IP_PHS_0_inst                                                            0x0020
#define TVE_IP_PHS_1_inst                                                            0x0021
#define TVE_IP_PHS_2_inst                                                            0x0022
#define TVE_IP_PHS_3_inst                                                            0x0023
#define TVE_IP_PHS_phi_shift                                                         (0)
#define TVE_IP_PHS_phi_mask                                                          (0x000000FF)
#define TVE_IP_PHS_phi(data)                                                         (0x000000FF&((data)<<0))
#define TVE_IP_PHS_phi_src(data)                                                     ((0x000000FF&(data))>>0)
#define TVE_IP_PHS_get_phi(data)                                                     ((0x000000FF&(data))>>0)


#define TVE_IP_SCTOH_0                                                               0x18018890
#define TVE_IP_SCTOH_1                                                               0x18018894
#define TVE_IP_SCTOH_2                                                               0x18018898
#define TVE_IP_SCTOH_3                                                               0x1801889C
#define TVE_IP_SCTOH_0_reg_addr                                                      "0xB8018890"
#define TVE_IP_SCTOH_1_reg_addr                                                      "0xB8018894"
#define TVE_IP_SCTOH_2_reg_addr                                                      "0xB8018898"
#define TVE_IP_SCTOH_3_reg_addr                                                      "0xB801889C"
#define TVE_IP_SCTOH_0_reg                                                           0xB8018890
#define TVE_IP_SCTOH_1_reg                                                           0xB8018894
#define TVE_IP_SCTOH_2_reg                                                           0xB8018898
#define TVE_IP_SCTOH_3_reg                                                           0xB801889C
#define set_TVE_IP_SCTOH_0_reg(data)   (*((volatile unsigned int*) TVE_IP_SCTOH_0_reg)=data)
#define set_TVE_IP_SCTOH_1_reg(data)   (*((volatile unsigned int*) TVE_IP_SCTOH_1_reg)=data)
#define set_TVE_IP_SCTOH_2_reg(data)   (*((volatile unsigned int*) TVE_IP_SCTOH_2_reg)=data)
#define set_TVE_IP_SCTOH_3_reg(data)   (*((volatile unsigned int*) TVE_IP_SCTOH_3_reg)=data)
#define get_TVE_IP_SCTOH_0_reg   (*((volatile unsigned int*) TVE_IP_SCTOH_0_reg))
#define get_TVE_IP_SCTOH_1_reg   (*((volatile unsigned int*) TVE_IP_SCTOH_1_reg))
#define get_TVE_IP_SCTOH_2_reg   (*((volatile unsigned int*) TVE_IP_SCTOH_2_reg))
#define get_TVE_IP_SCTOH_3_reg   (*((volatile unsigned int*) TVE_IP_SCTOH_3_reg))
#define TVE_IP_SCTOH_0_inst_adr                                                      "0x0024"
#define TVE_IP_SCTOH_1_inst_adr                                                      "0x0025"
#define TVE_IP_SCTOH_2_inst_adr                                                      "0x0026"
#define TVE_IP_SCTOH_3_inst_adr                                                      "0x0027"
#define TVE_IP_SCTOH_0_inst                                                          0x0024
#define TVE_IP_SCTOH_1_inst                                                          0x0025
#define TVE_IP_SCTOH_2_inst                                                          0x0026
#define TVE_IP_SCTOH_3_inst                                                          0x0027
#define TVE_IP_SCTOH_sctoh_shift                                                     (0)
#define TVE_IP_SCTOH_sctoh_mask                                                      (0x000000FF)
#define TVE_IP_SCTOH_sctoh(data)                                                     (0x000000FF&((data)<<0))
#define TVE_IP_SCTOH_sctoh_src(data)                                                 ((0x000000FF&(data))>>0)
#define TVE_IP_SCTOH_get_sctoh(data)                                                 ((0x000000FF&(data))>>0)


#define TVE_IP_F_CTRL                                                                0x180188a0
#define TVE_IP_F_CTRL_reg_addr                                                       "0xB80188A0"
#define TVE_IP_F_CTRL_reg                                                            0xB80188A0
#define set_TVE_IP_F_CTRL_reg(data)   (*((volatile unsigned int*) TVE_IP_F_CTRL_reg)=data)
#define get_TVE_IP_F_CTRL_reg   (*((volatile unsigned int*) TVE_IP_F_CTRL_reg))
#define TVE_IP_F_CTRL_inst_adr                                                       "0x0028"
#define TVE_IP_F_CTRL_inst                                                           0x0028
#define TVE_IP_F_CTRL_u_invert_shift                                                 (3)
#define TVE_IP_F_CTRL_u_invert_mask                                                  (0x00000008)
#define TVE_IP_F_CTRL_u_invert(data)                                                 (0x00000008&((data)<<3))
#define TVE_IP_F_CTRL_u_invert_src(data)                                             ((0x00000008&(data))>>3)
#define TVE_IP_F_CTRL_get_u_invert(data)                                             ((0x00000008&(data))>>3)
#define TVE_IP_F_CTRL_v_invert_shift                                                 (2)
#define TVE_IP_F_CTRL_v_invert_mask                                                  (0x00000004)
#define TVE_IP_F_CTRL_v_invert(data)                                                 (0x00000004&((data)<<2))
#define TVE_IP_F_CTRL_v_invert_src(data)                                             ((0x00000004&(data))>>2)
#define TVE_IP_F_CTRL_get_v_invert(data)                                             ((0x00000004&(data))>>2)
#define TVE_IP_F_CTRL_t_offset_phase_shift                                           (1)
#define TVE_IP_F_CTRL_t_offset_phase_mask                                            (0x00000002)
#define TVE_IP_F_CTRL_t_offset_phase(data)                                           (0x00000002&((data)<<1))
#define TVE_IP_F_CTRL_t_offset_phase_src(data)                                       ((0x00000002&(data))>>1)
#define TVE_IP_F_CTRL_get_t_offset_phase(data)                                       ((0x00000002&(data))>>1)
#define TVE_IP_F_CTRL_t_reset_fsc_shift                                              (0)
#define TVE_IP_F_CTRL_t_reset_fsc_mask                                               (0x00000001)
#define TVE_IP_F_CTRL_t_reset_fsc(data)                                              (0x00000001&((data)<<0))
#define TVE_IP_F_CTRL_t_reset_fsc_src(data)                                          ((0x00000001&(data))>>0)
#define TVE_IP_F_CTRL_get_t_reset_fsc(data)                                          ((0x00000001&(data))>>0)


#define TVE_IP_T_SEL_SIN                                                             0x18018980
#define TVE_IP_T_SEL_SIN_reg_addr                                                    "0xB8018980"
#define TVE_IP_T_SEL_SIN_reg                                                         0xB8018980
#define set_TVE_IP_T_SEL_SIN_reg(data)   (*((volatile unsigned int*) TVE_IP_T_SEL_SIN_reg)=data)
#define get_TVE_IP_T_SEL_SIN_reg   (*((volatile unsigned int*) TVE_IP_T_SEL_SIN_reg))
#define TVE_IP_T_SEL_SIN_inst_adr                                                    "0x0060"
#define TVE_IP_T_SEL_SIN_inst                                                        0x0060
#define TVE_IP_T_SEL_SIN_t_sel_sin_shift                                             (1)
#define TVE_IP_T_SEL_SIN_t_sel_sin_mask                                              (0x00000002)
#define TVE_IP_T_SEL_SIN_t_sel_sin(data)                                             (0x00000002&((data)<<1))
#define TVE_IP_T_SEL_SIN_t_sel_sin_src(data)                                         ((0x00000002&(data))>>1)
#define TVE_IP_T_SEL_SIN_get_t_sel_sin(data)                                         ((0x00000002&(data))>>1)
#define TVE_IP_T_SEL_SIN_t_fsc_rom_shift                                             (0)
#define TVE_IP_T_SEL_SIN_t_fsc_rom_mask                                              (0x00000001)
#define TVE_IP_T_SEL_SIN_t_fsc_rom(data)                                             (0x00000001&((data)<<0))
#define TVE_IP_T_SEL_SIN_t_fsc_rom_src(data)                                         ((0x00000001&(data))>>0)
#define TVE_IP_T_SEL_SIN_get_t_fsc_rom(data)                                         ((0x00000001&(data))>>0)


#define TVE_IP_BLCK_LVL                                                              0x180188a8
#define TVE_IP_BLCK_LVL_reg_addr                                                     "0xB80188A8"
#define TVE_IP_BLCK_LVL_reg                                                          0xB80188A8
#define set_TVE_IP_BLCK_LVL_reg(data)   (*((volatile unsigned int*) TVE_IP_BLCK_LVL_reg)=data)
#define get_TVE_IP_BLCK_LVL_reg   (*((volatile unsigned int*) TVE_IP_BLCK_LVL_reg))
#define TVE_IP_BLCK_LVL_inst_adr                                                     "0x002A"
#define TVE_IP_BLCK_LVL_inst                                                         0x002A
#define TVE_IP_BLCK_LVL_black_lvl_shift                                              (0)
#define TVE_IP_BLCK_LVL_black_lvl_mask                                               (0x000000FF)
#define TVE_IP_BLCK_LVL_black_lvl(data)                                              (0x000000FF&((data)<<0))
#define TVE_IP_BLCK_LVL_black_lvl_src(data)                                          ((0x000000FF&(data))>>0)
#define TVE_IP_BLCK_LVL_get_black_lvl(data)                                          ((0x000000FF&(data))>>0)


#define TVE_IP_BLNK_LVL                                                              0x180188ac
#define TVE_IP_BLNK_LVL_reg_addr                                                     "0xB80188AC"
#define TVE_IP_BLNK_LVL_reg                                                          0xB80188AC
#define set_TVE_IP_BLNK_LVL_reg(data)   (*((volatile unsigned int*) TVE_IP_BLNK_LVL_reg)=data)
#define get_TVE_IP_BLNK_LVL_reg   (*((volatile unsigned int*) TVE_IP_BLNK_LVL_reg))
#define TVE_IP_BLNK_LVL_inst_adr                                                     "0x002B"
#define TVE_IP_BLNK_LVL_inst                                                         0x002B
#define TVE_IP_BLNK_LVL_blank_lvl_shift                                              (0)
#define TVE_IP_BLNK_LVL_blank_lvl_mask                                               (0x000000FF)
#define TVE_IP_BLNK_LVL_blank_lvl(data)                                              (0x000000FF&((data)<<0))
#define TVE_IP_BLNK_LVL_blank_lvl_src(data)                                          ((0x000000FF&(data))>>0)
#define TVE_IP_BLNK_LVL_get_blank_lvl(data)                                          ((0x000000FF&(data))>>0)


#define TVE_IP_CLAMP_LVL                                                             0x180188b0
#define TVE_IP_CLAMP_LVL_reg_addr                                                    "0xB80188B0"
#define TVE_IP_CLAMP_LVL_reg                                                         0xB80188B0
#define set_TVE_IP_CLAMP_LVL_reg(data)   (*((volatile unsigned int*) TVE_IP_CLAMP_LVL_reg)=data)
#define get_TVE_IP_CLAMP_LVL_reg   (*((volatile unsigned int*) TVE_IP_CLAMP_LVL_reg))
#define TVE_IP_CLAMP_LVL_inst_adr                                                    "0x002C"
#define TVE_IP_CLAMP_LVL_inst                                                        0x002C
#define TVE_IP_CLAMP_LVL_clamp_lvl_shift                                             (0)
#define TVE_IP_CLAMP_LVL_clamp_lvl_mask                                              (0x000000FF)
#define TVE_IP_CLAMP_LVL_clamp_lvl(data)                                             (0x000000FF&((data)<<0))
#define TVE_IP_CLAMP_LVL_clamp_lvl_src(data)                                         ((0x000000FF&(data))>>0)
#define TVE_IP_CLAMP_LVL_get_clamp_lvl(data)                                         ((0x000000FF&(data))>>0)


#define TVE_IP_SYNC_LVL                                                              0x180188b4
#define TVE_IP_SYNC_LVL_reg_addr                                                     "0xB80188B4"
#define TVE_IP_SYNC_LVL_reg                                                          0xB80188B4
#define set_TVE_IP_SYNC_LVL_reg(data)   (*((volatile unsigned int*) TVE_IP_SYNC_LVL_reg)=data)
#define get_TVE_IP_SYNC_LVL_reg   (*((volatile unsigned int*) TVE_IP_SYNC_LVL_reg))
#define TVE_IP_SYNC_LVL_inst_adr                                                     "0x002D"
#define TVE_IP_SYNC_LVL_inst                                                         0x002D
#define TVE_IP_SYNC_LVL_sync_lvl_shift                                               (0)
#define TVE_IP_SYNC_LVL_sync_lvl_mask                                                (0x000000FF)
#define TVE_IP_SYNC_LVL_sync_lvl(data)                                               (0x000000FF&((data)<<0))
#define TVE_IP_SYNC_LVL_sync_lvl_src(data)                                           ((0x000000FF&(data))>>0)
#define TVE_IP_SYNC_LVL_get_sync_lvl(data)                                           ((0x000000FF&(data))>>0)


#define TVE_IP_Y_CTRL                                                                0x180188b8
#define TVE_IP_Y_CTRL_reg_addr                                                       "0xB80188B8"
#define TVE_IP_Y_CTRL_reg                                                            0xB80188B8
#define set_TVE_IP_Y_CTRL_reg(data)   (*((volatile unsigned int*) TVE_IP_Y_CTRL_reg)=data)
#define get_TVE_IP_Y_CTRL_reg   (*((volatile unsigned int*) TVE_IP_Y_CTRL_reg))
#define TVE_IP_Y_CTRL_inst_adr                                                       "0x002E"
#define TVE_IP_Y_CTRL_inst                                                           0x002E
#define TVE_IP_Y_CTRL_y_interp_shift                                                 (6)
#define TVE_IP_Y_CTRL_y_interp_mask                                                  (0x000000C0)
#define TVE_IP_Y_CTRL_y_interp(data)                                                 (0x000000C0&((data)<<6))
#define TVE_IP_Y_CTRL_y_interp_src(data)                                             ((0x000000C0&(data))>>6)
#define TVE_IP_Y_CTRL_get_y_interp(data)                                             ((0x000000C0&(data))>>6)
#define TVE_IP_Y_CTRL_y_colorbar_en_shift                                            (5)
#define TVE_IP_Y_CTRL_y_colorbar_en_mask                                             (0x00000020)
#define TVE_IP_Y_CTRL_y_colorbar_en(data)                                            (0x00000020&((data)<<5))
#define TVE_IP_Y_CTRL_y_colorbar_en_src(data)                                        ((0x00000020&(data))>>5)
#define TVE_IP_Y_CTRL_get_y_colorbar_en(data)                                        ((0x00000020&(data))>>5)
#define TVE_IP_Y_CTRL_t_ydel_adj_shift                                               (2)
#define TVE_IP_Y_CTRL_t_ydel_adj_mask                                                (0x0000001C)
#define TVE_IP_Y_CTRL_t_ydel_adj(data)                                               (0x0000001C&((data)<<2))
#define TVE_IP_Y_CTRL_t_ydel_adj_src(data)                                           ((0x0000001C&(data))>>2)
#define TVE_IP_Y_CTRL_get_t_ydel_adj(data)                                           ((0x0000001C&(data))>>2)
#define TVE_IP_Y_CTRL_t_sel_ylpf_shift                                               (1)
#define TVE_IP_Y_CTRL_t_sel_ylpf_mask                                                (0x00000002)
#define TVE_IP_Y_CTRL_t_sel_ylpf(data)                                               (0x00000002&((data)<<1))
#define TVE_IP_Y_CTRL_t_sel_ylpf_src(data)                                           ((0x00000002&(data))>>1)
#define TVE_IP_Y_CTRL_get_t_sel_ylpf(data)                                           ((0x00000002&(data))>>1)
#define TVE_IP_Y_CTRL_t_ygain_val_shift                                              (0)
#define TVE_IP_Y_CTRL_t_ygain_val_mask                                               (0x00000001)
#define TVE_IP_Y_CTRL_t_ygain_val(data)                                              (0x00000001&((data)<<0))
#define TVE_IP_Y_CTRL_t_ygain_val_src(data)                                          ((0x00000001&(data))>>0)
#define TVE_IP_Y_CTRL_get_t_ygain_val(data)                                          ((0x00000001&(data))>>0)


#define TVE_IP_TEST_PARAM                                                            0x18018984
#define TVE_IP_TEST_PARAM_reg_addr                                                   "0xB8018984"
#define TVE_IP_TEST_PARAM_reg                                                        0xB8018984
#define set_TVE_IP_TEST_PARAM_reg(data)   (*((volatile unsigned int*) TVE_IP_TEST_PARAM_reg)=data)
#define get_TVE_IP_TEST_PARAM_reg   (*((volatile unsigned int*) TVE_IP_TEST_PARAM_reg))
#define TVE_IP_TEST_PARAM_inst_adr                                                   "0x0061"
#define TVE_IP_TEST_PARAM_inst                                                       0x0061
#define TVE_IP_TEST_PARAM_t_byp_yups_shift                                           (6)
#define TVE_IP_TEST_PARAM_t_byp_yups_mask                                            (0x00000040)
#define TVE_IP_TEST_PARAM_t_byp_yups(data)                                           (0x00000040&((data)<<6))
#define TVE_IP_TEST_PARAM_t_byp_yups_src(data)                                       ((0x00000040&(data))>>6)
#define TVE_IP_TEST_PARAM_get_t_byp_yups(data)                                       ((0x00000040&(data))>>6)
#define TVE_IP_TEST_PARAM_t_sel_ylp_shift                                            (5)
#define TVE_IP_TEST_PARAM_t_sel_ylp_mask                                             (0x00000020)
#define TVE_IP_TEST_PARAM_t_sel_ylp(data)                                            (0x00000020&((data)<<5))
#define TVE_IP_TEST_PARAM_t_sel_ylp_src(data)                                        ((0x00000020&(data))>>5)
#define TVE_IP_TEST_PARAM_get_t_sel_ylp(data)                                        ((0x00000020&(data))>>5)
#define TVE_IP_TEST_PARAM_t_ygain_off_shift                                          (4)
#define TVE_IP_TEST_PARAM_t_ygain_off_mask                                           (0x00000010)
#define TVE_IP_TEST_PARAM_t_ygain_off(data)                                          (0x00000010&((data)<<4))
#define TVE_IP_TEST_PARAM_t_ygain_off_src(data)                                      ((0x00000010&(data))>>4)
#define TVE_IP_TEST_PARAM_get_t_ygain_off(data)                                      ((0x00000010&(data))>>4)
#define TVE_IP_TEST_PARAM_y_tsin_cos_shift                                           (3)
#define TVE_IP_TEST_PARAM_y_tsin_cos_mask                                            (0x00000008)
#define TVE_IP_TEST_PARAM_y_tsin_cos(data)                                           (0x00000008&((data)<<3))
#define TVE_IP_TEST_PARAM_y_tsin_cos_src(data)                                       ((0x00000008&(data))>>3)
#define TVE_IP_TEST_PARAM_get_y_tsin_cos(data)                                       ((0x00000008&(data))>>3)
#define TVE_IP_TEST_PARAM_y_tsel_dac_tst_shift                                       (2)
#define TVE_IP_TEST_PARAM_y_tsel_dac_tst_mask                                        (0x00000004)
#define TVE_IP_TEST_PARAM_y_tsel_dac_tst(data)                                       (0x00000004&((data)<<2))
#define TVE_IP_TEST_PARAM_y_tsel_dac_tst_src(data)                                   ((0x00000004&(data))>>2)
#define TVE_IP_TEST_PARAM_get_y_tsel_dac_tst(data)                                   ((0x00000004&(data))>>2)
#define TVE_IP_TEST_PARAM_y_tdig_out_shift                                           (0)
#define TVE_IP_TEST_PARAM_y_tdig_out_mask                                            (0x00000003)
#define TVE_IP_TEST_PARAM_y_tdig_out(data)                                           (0x00000003&((data)<<0))
#define TVE_IP_TEST_PARAM_y_tdig_out_src(data)                                       ((0x00000003&(data))>>0)
#define TVE_IP_TEST_PARAM_get_y_tdig_out(data)                                       ((0x00000003&(data))>>0)


#define TVE_IP_Y_GAIN                                                                0x18018a00
#define TVE_IP_Y_GAIN_reg_addr                                                       "0xB8018A00"
#define TVE_IP_Y_GAIN_reg                                                            0xB8018A00
#define set_TVE_IP_Y_GAIN_reg(data)   (*((volatile unsigned int*) TVE_IP_Y_GAIN_reg)=data)
#define get_TVE_IP_Y_GAIN_reg   (*((volatile unsigned int*) TVE_IP_Y_GAIN_reg))
#define TVE_IP_Y_GAIN_inst_adr                                                       "0x0080"
#define TVE_IP_Y_GAIN_inst                                                           0x0080
#define TVE_IP_Y_GAIN_y_gain_shift                                                   (0)
#define TVE_IP_Y_GAIN_y_gain_mask                                                    (0x000003FF)
#define TVE_IP_Y_GAIN_y_gain(data)                                                   (0x000003FF&((data)<<0))
#define TVE_IP_Y_GAIN_y_gain_src(data)                                               ((0x000003FF&(data))>>0)
#define TVE_IP_Y_GAIN_get_y_gain(data)                                               ((0x000003FF&(data))>>0)


#define TVE_IP_SYNC_LVL2                                                             0x180189c0
#define TVE_IP_SYNC_LVL2_reg_addr                                                    "0xB80189C0"
#define TVE_IP_SYNC_LVL2_reg                                                         0xB80189C0
#define set_TVE_IP_SYNC_LVL2_reg(data)   (*((volatile unsigned int*) TVE_IP_SYNC_LVL2_reg)=data)
#define get_TVE_IP_SYNC_LVL2_reg   (*((volatile unsigned int*) TVE_IP_SYNC_LVL2_reg))
#define TVE_IP_SYNC_LVL2_inst_adr                                                    "0x0070"
#define TVE_IP_SYNC_LVL2_inst                                                        0x0070
#define TVE_IP_SYNC_LVL2_sync_lvl_h_shift                                            (0)
#define TVE_IP_SYNC_LVL2_sync_lvl_h_mask                                             (0x000000FF)
#define TVE_IP_SYNC_LVL2_sync_lvl_h(data)                                            (0x000000FF&((data)<<0))
#define TVE_IP_SYNC_LVL2_sync_lvl_h_src(data)                                        ((0x000000FF&(data))>>0)
#define TVE_IP_SYNC_LVL2_get_sync_lvl_h(data)                                        ((0x000000FF&(data))>>0)


#define TVE_IP_SYNC_LVL3                                                             0x180189c4
#define TVE_IP_SYNC_LVL3_reg_addr                                                    "0xB80189C4"
#define TVE_IP_SYNC_LVL3_reg                                                         0xB80189C4
#define set_TVE_IP_SYNC_LVL3_reg(data)   (*((volatile unsigned int*) TVE_IP_SYNC_LVL3_reg)=data)
#define get_TVE_IP_SYNC_LVL3_reg   (*((volatile unsigned int*) TVE_IP_SYNC_LVL3_reg))
#define TVE_IP_SYNC_LVL3_inst_adr                                                    "0x0071"
#define TVE_IP_SYNC_LVL3_inst                                                        0x0071
#define TVE_IP_SYNC_LVL3_sync_lvl_m_shift                                            (0)
#define TVE_IP_SYNC_LVL3_sync_lvl_m_mask                                             (0x000000FF)
#define TVE_IP_SYNC_LVL3_sync_lvl_m(data)                                            (0x000000FF&((data)<<0))
#define TVE_IP_SYNC_LVL3_sync_lvl_m_src(data)                                        ((0x000000FF&(data))>>0)
#define TVE_IP_SYNC_LVL3_get_sync_lvl_m(data)                                        ((0x000000FF&(data))>>0)


#define TVE_IP_SYNC_LVL4                                                             0x180189c8
#define TVE_IP_SYNC_LVL4_reg_addr                                                    "0xB80189C8"
#define TVE_IP_SYNC_LVL4_reg                                                         0xB80189C8
#define set_TVE_IP_SYNC_LVL4_reg(data)   (*((volatile unsigned int*) TVE_IP_SYNC_LVL4_reg)=data)
#define get_TVE_IP_SYNC_LVL4_reg   (*((volatile unsigned int*) TVE_IP_SYNC_LVL4_reg))
#define TVE_IP_SYNC_LVL4_inst_adr                                                    "0x0072"
#define TVE_IP_SYNC_LVL4_inst                                                        0x0072
#define TVE_IP_SYNC_LVL4_sync_lvl_l_shift                                            (0)
#define TVE_IP_SYNC_LVL4_sync_lvl_l_mask                                             (0x000000FF)
#define TVE_IP_SYNC_LVL4_sync_lvl_l(data)                                            (0x000000FF&((data)<<0))
#define TVE_IP_SYNC_LVL4_sync_lvl_l_src(data)                                        ((0x000000FF&(data))>>0)
#define TVE_IP_SYNC_LVL4_get_sync_lvl_l(data)                                        ((0x000000FF&(data))>>0)


#define TVE_IP_O_CTRL                                                                0x180188bc
#define TVE_IP_O_CTRL_reg_addr                                                       "0xB80188BC"
#define TVE_IP_O_CTRL_reg                                                            0xB80188BC
#define set_TVE_IP_O_CTRL_reg(data)   (*((volatile unsigned int*) TVE_IP_O_CTRL_reg)=data)
#define get_TVE_IP_O_CTRL_reg   (*((volatile unsigned int*) TVE_IP_O_CTRL_reg))
#define TVE_IP_O_CTRL_inst_adr                                                       "0x002F"
#define TVE_IP_O_CTRL_inst                                                           0x002F
#define TVE_IP_O_CTRL_y_tsel_yuv_shift                                               (3)
#define TVE_IP_O_CTRL_y_tsel_yuv_mask                                                (0x00000008)
#define TVE_IP_O_CTRL_y_tsel_yuv(data)                                               (0x00000008&((data)<<3))
#define TVE_IP_O_CTRL_y_tsel_yuv_src(data)                                           ((0x00000008&(data))>>3)
#define TVE_IP_O_CTRL_get_y_tsel_yuv(data)                                           ((0x00000008&(data))>>3)
#define TVE_IP_O_CTRL_t_pd_cvdac_shift                                               (2)
#define TVE_IP_O_CTRL_t_pd_cvdac_mask                                                (0x00000004)
#define TVE_IP_O_CTRL_t_pd_cvdac(data)                                               (0x00000004&((data)<<2))
#define TVE_IP_O_CTRL_t_pd_cvdac_src(data)                                           ((0x00000004&(data))>>2)
#define TVE_IP_O_CTRL_get_t_pd_cvdac(data)                                           ((0x00000004&(data))>>2)
#define TVE_IP_O_CTRL_t_pd_ydac_shift                                                (1)
#define TVE_IP_O_CTRL_t_pd_ydac_mask                                                 (0x00000002)
#define TVE_IP_O_CTRL_t_pd_ydac(data)                                                (0x00000002&((data)<<1))
#define TVE_IP_O_CTRL_t_pd_ydac_src(data)                                            ((0x00000002&(data))>>1)
#define TVE_IP_O_CTRL_get_t_pd_ydac(data)                                            ((0x00000002&(data))>>1)
#define TVE_IP_O_CTRL_t_pd_cdac_shift                                                (0)
#define TVE_IP_O_CTRL_t_pd_cdac_mask                                                 (0x00000001)
#define TVE_IP_O_CTRL_t_pd_cdac(data)                                                (0x00000001&((data)<<0))
#define TVE_IP_O_CTRL_t_pd_cdac_src(data)                                            ((0x00000001&(data))>>0)
#define TVE_IP_O_CTRL_get_t_pd_cdac(data)                                            ((0x00000001&(data))>>0)


#define TVE_IP_NBA                                                                   0x180188c8
#define TVE_IP_NBA_reg_addr                                                          "0xB80188C8"
#define TVE_IP_NBA_reg                                                               0xB80188C8
#define set_TVE_IP_NBA_reg(data)   (*((volatile unsigned int*) TVE_IP_NBA_reg)=data)
#define get_TVE_IP_NBA_reg   (*((volatile unsigned int*) TVE_IP_NBA_reg))
#define TVE_IP_NBA_inst_adr                                                          "0x0032"
#define TVE_IP_NBA_inst                                                              0x0032
#define TVE_IP_NBA_nba_shift                                                         (0)
#define TVE_IP_NBA_nba_mask                                                          (0x000000FF)
#define TVE_IP_NBA_nba(data)                                                         (0x000000FF&((data)<<0))
#define TVE_IP_NBA_nba_src(data)                                                     ((0x000000FF&(data))>>0)
#define TVE_IP_NBA_get_nba(data)                                                     ((0x000000FF&(data))>>0)


#define TVE_IP_PBA                                                                   0x180188cc
#define TVE_IP_PBA_reg_addr                                                          "0xB80188CC"
#define TVE_IP_PBA_reg                                                               0xB80188CC
#define set_TVE_IP_PBA_reg(data)   (*((volatile unsigned int*) TVE_IP_PBA_reg)=data)
#define get_TVE_IP_PBA_reg   (*((volatile unsigned int*) TVE_IP_PBA_reg))
#define TVE_IP_PBA_inst_adr                                                          "0x0033"
#define TVE_IP_PBA_inst                                                              0x0033
#define TVE_IP_PBA_pba_shift                                                         (0)
#define TVE_IP_PBA_pba_mask                                                          (0x000000FF)
#define TVE_IP_PBA_pba(data)                                                         (0x000000FF&((data)<<0))
#define TVE_IP_PBA_pba_src(data)                                                     ((0x000000FF&(data))>>0)
#define TVE_IP_PBA_get_pba(data)                                                     ((0x000000FF&(data))>>0)


#define TVE_IP_C_CTRL                                                                0x180188d0
#define TVE_IP_C_CTRL_reg_addr                                                       "0xB80188D0"
#define TVE_IP_C_CTRL_reg                                                            0xB80188D0
#define set_TVE_IP_C_CTRL_reg(data)   (*((volatile unsigned int*) TVE_IP_C_CTRL_reg)=data)
#define get_TVE_IP_C_CTRL_reg   (*((volatile unsigned int*) TVE_IP_C_CTRL_reg))
#define TVE_IP_C_CTRL_inst_adr                                                       "0x0034"
#define TVE_IP_C_CTRL_inst                                                           0x0034
#define TVE_IP_C_CTRL_t_pal_clpf_shift                                               (1)
#define TVE_IP_C_CTRL_t_pal_clpf_mask                                                (0x00000002)
#define TVE_IP_C_CTRL_t_pal_clpf(data)                                               (0x00000002&((data)<<1))
#define TVE_IP_C_CTRL_t_pal_clpf_src(data)                                           ((0x00000002&(data))>>1)
#define TVE_IP_C_CTRL_get_t_pal_clpf(data)                                           ((0x00000002&(data))>>1)
#define TVE_IP_C_CTRL_t_sel_c_gain_shift                                             (0)
#define TVE_IP_C_CTRL_t_sel_c_gain_mask                                              (0x00000001)
#define TVE_IP_C_CTRL_t_sel_c_gain(data)                                             (0x00000001&((data)<<0))
#define TVE_IP_C_CTRL_t_sel_c_gain_src(data)                                         ((0x00000001&(data))>>0)
#define TVE_IP_C_CTRL_get_t_sel_c_gain(data)                                         ((0x00000001&(data))>>0)


#define TVE_IP_TEST_T_BYP_CUPS                                                       0x1801898c
#define TVE_IP_TEST_T_BYP_CUPS_reg_addr                                              "0xB801898C"
#define TVE_IP_TEST_T_BYP_CUPS_reg                                                   0xB801898C
#define set_TVE_IP_TEST_T_BYP_CUPS_reg(data)   (*((volatile unsigned int*) TVE_IP_TEST_T_BYP_CUPS_reg)=data)
#define get_TVE_IP_TEST_T_BYP_CUPS_reg   (*((volatile unsigned int*) TVE_IP_TEST_T_BYP_CUPS_reg))
#define TVE_IP_TEST_T_BYP_CUPS_inst_adr                                              "0x0063"
#define TVE_IP_TEST_T_BYP_CUPS_inst                                                  0x0063
#define TVE_IP_TEST_T_BYP_CUPS_t_byp_cups_shift                                      (2)
#define TVE_IP_TEST_T_BYP_CUPS_t_byp_cups_mask                                       (0x00000004)
#define TVE_IP_TEST_T_BYP_CUPS_t_byp_cups(data)                                      (0x00000004&((data)<<2))
#define TVE_IP_TEST_T_BYP_CUPS_t_byp_cups_src(data)                                  ((0x00000004&(data))>>2)
#define TVE_IP_TEST_T_BYP_CUPS_get_t_byp_cups(data)                                  ((0x00000004&(data))>>2)
#define TVE_IP_TEST_T_BYP_CUPS_t_byp_clpf_shift                                      (1)
#define TVE_IP_TEST_T_BYP_CUPS_t_byp_clpf_mask                                       (0x00000002)
#define TVE_IP_TEST_T_BYP_CUPS_t_byp_clpf(data)                                      (0x00000002&((data)<<1))
#define TVE_IP_TEST_T_BYP_CUPS_t_byp_clpf_src(data)                                  ((0x00000002&(data))>>1)
#define TVE_IP_TEST_T_BYP_CUPS_get_t_byp_clpf(data)                                  ((0x00000002&(data))>>1)
#define TVE_IP_TEST_T_BYP_CUPS_t_c_gain_off_shift                                    (0)
#define TVE_IP_TEST_T_BYP_CUPS_t_c_gain_off_mask                                     (0x00000001)
#define TVE_IP_TEST_T_BYP_CUPS_t_c_gain_off(data)                                    (0x00000001&((data)<<0))
#define TVE_IP_TEST_T_BYP_CUPS_t_c_gain_off_src(data)                                ((0x00000001&(data))>>0)
#define TVE_IP_TEST_T_BYP_CUPS_get_t_c_gain_off(data)                                ((0x00000001&(data))>>0)


#define TVE_IP_SYNCLPF_GAIN                                                          0x180189cc
#define TVE_IP_SYNCLPF_GAIN_reg_addr                                                 "0xB80189CC"
#define TVE_IP_SYNCLPF_GAIN_reg                                                      0xB80189CC
#define set_TVE_IP_SYNCLPF_GAIN_reg(data)   (*((volatile unsigned int*) TVE_IP_SYNCLPF_GAIN_reg)=data)
#define get_TVE_IP_SYNCLPF_GAIN_reg   (*((volatile unsigned int*) TVE_IP_SYNCLPF_GAIN_reg))
#define TVE_IP_SYNCLPF_GAIN_inst_adr                                                 "0x0073"
#define TVE_IP_SYNCLPF_GAIN_inst                                                     0x0073
#define TVE_IP_SYNCLPF_GAIN_clpf_gain_shift                                          (0)
#define TVE_IP_SYNCLPF_GAIN_clpf_gain_mask                                           (0x000000FF)
#define TVE_IP_SYNCLPF_GAIN_clpf_gain(data)                                          (0x000000FF&((data)<<0))
#define TVE_IP_SYNCLPF_GAIN_clpf_gain_src(data)                                      ((0x000000FF&(data))>>0)
#define TVE_IP_SYNCLPF_GAIN_get_clpf_gain(data)                                      ((0x000000FF&(data))>>0)


#define TVE_IP_S_CTRL                                                                0x180188e0
#define TVE_IP_S_CTRL_reg_addr                                                       "0xB80188E0"
#define TVE_IP_S_CTRL_reg                                                            0xB80188E0
#define set_TVE_IP_S_CTRL_reg(data)   (*((volatile unsigned int*) TVE_IP_S_CTRL_reg)=data)
#define get_TVE_IP_S_CTRL_reg   (*((volatile unsigned int*) TVE_IP_S_CTRL_reg))
#define TVE_IP_S_CTRL_inst_adr                                                       "0x0038"
#define TVE_IP_S_CTRL_inst                                                           0x0038
#define TVE_IP_S_CTRL_t_hsync_phs_shift                                              (7)
#define TVE_IP_S_CTRL_t_hsync_phs_mask                                               (0x00000080)
#define TVE_IP_S_CTRL_t_hsync_phs(data)                                              (0x00000080&((data)<<7))
#define TVE_IP_S_CTRL_t_hsync_phs_src(data)                                          ((0x00000080&(data))>>7)
#define TVE_IP_S_CTRL_get_t_hsync_phs(data)                                          ((0x00000080&(data))>>7)
#define TVE_IP_S_CTRL_t_vsync_phs_shift                                              (6)
#define TVE_IP_S_CTRL_t_vsync_phs_mask                                               (0x00000040)
#define TVE_IP_S_CTRL_t_vsync_phs(data)                                              (0x00000040&((data)<<6))
#define TVE_IP_S_CTRL_t_vsync_phs_src(data)                                          ((0x00000040&(data))>>6)
#define TVE_IP_S_CTRL_get_t_vsync_phs(data)                                          ((0x00000040&(data))>>6)
#define TVE_IP_S_CTRL_y_tsyncmode_shift                                              (3)
#define TVE_IP_S_CTRL_y_tsyncmode_mask                                               (0x00000038)
#define TVE_IP_S_CTRL_y_tsyncmode(data)                                              (0x00000038&((data)<<3))
#define TVE_IP_S_CTRL_y_tsyncmode_src(data)                                          ((0x00000038&(data))>>3)
#define TVE_IP_S_CTRL_get_y_tsyncmode(data)                                          ((0x00000038&(data))>>3)
#define TVE_IP_S_CTRL_y_tencd_mode_shift                                             (0)
#define TVE_IP_S_CTRL_y_tencd_mode_mask                                              (0x00000007)
#define TVE_IP_S_CTRL_y_tencd_mode(data)                                             (0x00000007&((data)<<0))
#define TVE_IP_S_CTRL_y_tencd_mode_src(data)                                         ((0x00000007&(data))>>0)
#define TVE_IP_S_CTRL_get_y_tencd_mode(data)                                         ((0x00000007&(data))>>0)


#define TVE_IP_VSO0                                                                  0x180188e4
#define TVE_IP_VSO0_reg_addr                                                         "0xB80188E4"
#define TVE_IP_VSO0_reg                                                              0xB80188E4
#define set_TVE_IP_VSO0_reg(data)   (*((volatile unsigned int*) TVE_IP_VSO0_reg)=data)
#define get_TVE_IP_VSO0_reg   (*((volatile unsigned int*) TVE_IP_VSO0_reg))
#define TVE_IP_VSO0_inst_adr                                                         "0x0039"
#define TVE_IP_VSO0_inst                                                             0x0039
#define TVE_IP_VSO0_clk_phs_shift                                                    (6)
#define TVE_IP_VSO0_clk_phs_mask                                                     (0x000000C0)
#define TVE_IP_VSO0_clk_phs(data)                                                    (0x000000C0&((data)<<6))
#define TVE_IP_VSO0_clk_phs_src(data)                                                ((0x000000C0&(data))>>6)
#define TVE_IP_VSO0_get_clk_phs(data)                                                ((0x000000C0&(data))>>6)
#define TVE_IP_VSO0_t_fsync_enbl_shift                                               (5)
#define TVE_IP_VSO0_t_fsync_enbl_mask                                                (0x00000020)
#define TVE_IP_VSO0_t_fsync_enbl(data)                                               (0x00000020&((data)<<5))
#define TVE_IP_VSO0_t_fsync_enbl_src(data)                                           ((0x00000020&(data))>>5)
#define TVE_IP_VSO0_get_t_fsync_enbl(data)                                           ((0x00000020&(data))>>5)
#define TVE_IP_VSO0_t_fsync_phs_shift                                                (4)
#define TVE_IP_VSO0_t_fsync_phs_mask                                                 (0x00000010)
#define TVE_IP_VSO0_t_fsync_phs(data)                                                (0x00000010&((data)<<4))
#define TVE_IP_VSO0_t_fsync_phs_src(data)                                            ((0x00000010&(data))>>4)
#define TVE_IP_VSO0_get_t_fsync_phs(data)                                            ((0x00000010&(data))>>4)
#define TVE_IP_VSO0_vso_shift                                                        (0)
#define TVE_IP_VSO0_vso_mask                                                         (0x00000003)
#define TVE_IP_VSO0_vso(data)                                                        (0x00000003&((data)<<0))
#define TVE_IP_VSO0_vso_src(data)                                                    ((0x00000003&(data))>>0)
#define TVE_IP_VSO0_get_vso(data)                                                    ((0x00000003&(data))>>0)


#define TVE_IP_VSO1                                                                  0x180188e8
#define TVE_IP_VSO1_reg_addr                                                         "0xB80188E8"
#define TVE_IP_VSO1_reg                                                              0xB80188E8
#define set_TVE_IP_VSO1_reg(data)   (*((volatile unsigned int*) TVE_IP_VSO1_reg)=data)
#define get_TVE_IP_VSO1_reg   (*((volatile unsigned int*) TVE_IP_VSO1_reg))
#define TVE_IP_VSO1_inst_adr                                                         "0x003A"
#define TVE_IP_VSO1_inst                                                             0x003A
#define TVE_IP_VSO1_vso_shift                                                        (0)
#define TVE_IP_VSO1_vso_mask                                                         (0x000000FF)
#define TVE_IP_VSO1_vso(data)                                                        (0x000000FF&((data)<<0))
#define TVE_IP_VSO1_vso_src(data)                                                    ((0x000000FF&(data))>>0)
#define TVE_IP_VSO1_get_vso(data)                                                    ((0x000000FF&(data))>>0)


#define TVE_IP_HSO0                                                                  0x180188ec
#define TVE_IP_HSO0_reg_addr                                                         "0xB80188EC"
#define TVE_IP_HSO0_reg                                                              0xB80188EC
#define set_TVE_IP_HSO0_reg(data)   (*((volatile unsigned int*) TVE_IP_HSO0_reg)=data)
#define get_TVE_IP_HSO0_reg   (*((volatile unsigned int*) TVE_IP_HSO0_reg))
#define TVE_IP_HSO0_inst_adr                                                         "0x003B"
#define TVE_IP_HSO0_inst                                                             0x003B
#define TVE_IP_HSO0_hso_shift                                                        (0)
#define TVE_IP_HSO0_hso_mask                                                         (0x00000007)
#define TVE_IP_HSO0_hso(data)                                                        (0x00000007&((data)<<0))
#define TVE_IP_HSO0_hso_src(data)                                                    ((0x00000007&(data))>>0)
#define TVE_IP_HSO0_get_hso(data)                                                    ((0x00000007&(data))>>0)


#define TVE_IP_HSO1                                                                  0x180188f0
#define TVE_IP_HSO1_reg_addr                                                         "0xB80188F0"
#define TVE_IP_HSO1_reg                                                              0xB80188F0
#define set_TVE_IP_HSO1_reg(data)   (*((volatile unsigned int*) TVE_IP_HSO1_reg)=data)
#define get_TVE_IP_HSO1_reg   (*((volatile unsigned int*) TVE_IP_HSO1_reg))
#define TVE_IP_HSO1_inst_adr                                                         "0x003C"
#define TVE_IP_HSO1_inst                                                             0x003C
#define TVE_IP_HSO1_hso_shift                                                        (0)
#define TVE_IP_HSO1_hso_mask                                                         (0x000000FF)
#define TVE_IP_HSO1_hso(data)                                                        (0x000000FF&((data)<<0))
#define TVE_IP_HSO1_hso_src(data)                                                    ((0x000000FF&(data))>>0)
#define TVE_IP_HSO1_get_hso(data)                                                    ((0x000000FF&(data))>>0)


#define TVE_IP_HLC0                                                                  0x180188f4
#define TVE_IP_HLC0_reg_addr                                                         "0xB80188F4"
#define TVE_IP_HLC0_reg                                                              0xB80188F4
#define set_TVE_IP_HLC0_reg(data)   (*((volatile unsigned int*) TVE_IP_HLC0_reg)=data)
#define get_TVE_IP_HLC0_reg   (*((volatile unsigned int*) TVE_IP_HLC0_reg))
#define TVE_IP_HLC0_inst_adr                                                         "0x003D"
#define TVE_IP_HLC0_inst                                                             0x003D
#define TVE_IP_HLC0_hlc_shift                                                        (0)
#define TVE_IP_HLC0_hlc_mask                                                         (0x00000003)
#define TVE_IP_HLC0_hlc(data)                                                        (0x00000003&((data)<<0))
#define TVE_IP_HLC0_hlc_src(data)                                                    ((0x00000003&(data))>>0)
#define TVE_IP_HLC0_get_hlc(data)                                                    ((0x00000003&(data))>>0)


#define TVE_IP_HLC1                                                                  0x180188f8
#define TVE_IP_HLC1_reg_addr                                                         "0xB80188F8"
#define TVE_IP_HLC1_reg                                                              0xB80188F8
#define set_TVE_IP_HLC1_reg(data)   (*((volatile unsigned int*) TVE_IP_HLC1_reg)=data)
#define get_TVE_IP_HLC1_reg   (*((volatile unsigned int*) TVE_IP_HLC1_reg))
#define TVE_IP_HLC1_inst_adr                                                         "0x003E"
#define TVE_IP_HLC1_inst                                                             0x003E
#define TVE_IP_HLC1_hlc_shift                                                        (0)
#define TVE_IP_HLC1_hlc_mask                                                         (0x000000FF)
#define TVE_IP_HLC1_hlc(data)                                                        (0x000000FF&((data)<<0))
#define TVE_IP_HLC1_hlc_src(data)                                                    ((0x000000FF&(data))>>0)
#define TVE_IP_HLC1_get_hlc(data)                                                    ((0x000000FF&(data))>>0)


#define TVE_IP_CCD_ODD_0                                                             0x18018904
#define TVE_IP_CCD_ODD_1                                                             0x18018908
#define TVE_IP_CCD_ODD_0_reg_addr                                                    "0xB8018904"
#define TVE_IP_CCD_ODD_1_reg_addr                                                    "0xB8018908"
#define TVE_IP_CCD_ODD_0_reg                                                         0xB8018904
#define TVE_IP_CCD_ODD_1_reg                                                         0xB8018908
#define set_TVE_IP_CCD_ODD_0_reg(data)   (*((volatile unsigned int*) TVE_IP_CCD_ODD_0_reg)=data)
#define set_TVE_IP_CCD_ODD_1_reg(data)   (*((volatile unsigned int*) TVE_IP_CCD_ODD_1_reg)=data)
#define get_TVE_IP_CCD_ODD_0_reg   (*((volatile unsigned int*) TVE_IP_CCD_ODD_0_reg))
#define get_TVE_IP_CCD_ODD_1_reg   (*((volatile unsigned int*) TVE_IP_CCD_ODD_1_reg))
#define TVE_IP_CCD_ODD_0_inst_adr                                                    "0x0041"
#define TVE_IP_CCD_ODD_1_inst_adr                                                    "0x0042"
#define TVE_IP_CCD_ODD_0_inst                                                        0x0041
#define TVE_IP_CCD_ODD_1_inst                                                        0x0042
#define TVE_IP_CCD_ODD_ccd_odd_shift                                                 (0)
#define TVE_IP_CCD_ODD_ccd_odd_mask                                                  (0x000000FF)
#define TVE_IP_CCD_ODD_ccd_odd(data)                                                 (0x000000FF&((data)<<0))
#define TVE_IP_CCD_ODD_ccd_odd_src(data)                                             ((0x000000FF&(data))>>0)
#define TVE_IP_CCD_ODD_get_ccd_odd(data)                                             ((0x000000FF&(data))>>0)


#define TVE_IP_CCD_EVEN_0                                                            0x1801890C
#define TVE_IP_CCD_EVEN_1                                                            0x18018910
#define TVE_IP_CCD_EVEN_0_reg_addr                                                   "0xB801890C"
#define TVE_IP_CCD_EVEN_1_reg_addr                                                   "0xB8018910"
#define TVE_IP_CCD_EVEN_0_reg                                                        0xB801890C
#define TVE_IP_CCD_EVEN_1_reg                                                        0xB8018910
#define set_TVE_IP_CCD_EVEN_0_reg(data)   (*((volatile unsigned int*) TVE_IP_CCD_EVEN_0_reg)=data)
#define set_TVE_IP_CCD_EVEN_1_reg(data)   (*((volatile unsigned int*) TVE_IP_CCD_EVEN_1_reg)=data)
#define get_TVE_IP_CCD_EVEN_0_reg   (*((volatile unsigned int*) TVE_IP_CCD_EVEN_0_reg))
#define get_TVE_IP_CCD_EVEN_1_reg   (*((volatile unsigned int*) TVE_IP_CCD_EVEN_1_reg))
#define TVE_IP_CCD_EVEN_0_inst_adr                                                   "0x0043"
#define TVE_IP_CCD_EVEN_1_inst_adr                                                   "0x0044"
#define TVE_IP_CCD_EVEN_0_inst                                                       0x0043
#define TVE_IP_CCD_EVEN_1_inst                                                       0x0044
#define TVE_IP_CCD_EVEN_ccd_even_shift                                               (0)
#define TVE_IP_CCD_EVEN_ccd_even_mask                                                (0x000000FF)
#define TVE_IP_CCD_EVEN_ccd_even(data)                                               (0x000000FF&((data)<<0))
#define TVE_IP_CCD_EVEN_ccd_even_src(data)                                           ((0x000000FF&(data))>>0)
#define TVE_IP_CCD_EVEN_get_ccd_even(data)                                           ((0x000000FF&(data))>>0)


#define TVE_IP_CCD_ENBL                                                              0x18018914
#define TVE_IP_CCD_ENBL_reg_addr                                                     "0xB8018914"
#define TVE_IP_CCD_ENBL_reg                                                          0xB8018914
#define set_TVE_IP_CCD_ENBL_reg(data)   (*((volatile unsigned int*) TVE_IP_CCD_ENBL_reg)=data)
#define get_TVE_IP_CCD_ENBL_reg   (*((volatile unsigned int*) TVE_IP_CCD_ENBL_reg))
#define TVE_IP_CCD_ENBL_inst_adr                                                     "0x0045"
#define TVE_IP_CCD_ENBL_inst                                                         0x0045
#define TVE_IP_CCD_ENBL_cc_enbl_shift                                                (0)
#define TVE_IP_CCD_ENBL_cc_enbl_mask                                                 (0x00000003)
#define TVE_IP_CCD_ENBL_cc_enbl(data)                                                (0x00000003&((data)<<0))
#define TVE_IP_CCD_ENBL_cc_enbl_src(data)                                            ((0x00000003&(data))>>0)
#define TVE_IP_CCD_ENBL_get_cc_enbl(data)                                            ((0x00000003&(data))>>0)


#define TVE_IP_TEST_HLR0                                                             0x180189b4
#define TVE_IP_TEST_HLR0_reg_addr                                                    "0xB80189B4"
#define TVE_IP_TEST_HLR0_reg                                                         0xB80189B4
#define set_TVE_IP_TEST_HLR0_reg(data)   (*((volatile unsigned int*) TVE_IP_TEST_HLR0_reg)=data)
#define get_TVE_IP_TEST_HLR0_reg   (*((volatile unsigned int*) TVE_IP_TEST_HLR0_reg))
#define TVE_IP_TEST_HLR0_inst_adr                                                    "0x006D"
#define TVE_IP_TEST_HLR0_inst                                                        0x006D
#define TVE_IP_TEST_HLR0_hlr_shift                                                   (0)
#define TVE_IP_TEST_HLR0_hlr_mask                                                    (0x00000003)
#define TVE_IP_TEST_HLR0_hlr(data)                                                   (0x00000003&((data)<<0))
#define TVE_IP_TEST_HLR0_hlr_src(data)                                               ((0x00000003&(data))>>0)
#define TVE_IP_TEST_HLR0_get_hlr(data)                                               ((0x00000003&(data))>>0)


#define TVE_IP_TEST_HLR1                                                             0x180189b8
#define TVE_IP_TEST_HLR1_reg_addr                                                    "0xB80189B8"
#define TVE_IP_TEST_HLR1_reg                                                         0xB80189B8
#define set_TVE_IP_TEST_HLR1_reg(data)   (*((volatile unsigned int*) TVE_IP_TEST_HLR1_reg)=data)
#define get_TVE_IP_TEST_HLR1_reg   (*((volatile unsigned int*) TVE_IP_TEST_HLR1_reg))
#define TVE_IP_TEST_HLR1_inst_adr                                                    "0x006E"
#define TVE_IP_TEST_HLR1_inst                                                        0x006E
#define TVE_IP_TEST_HLR1_hlr_shift                                                   (0)
#define TVE_IP_TEST_HLR1_hlr_mask                                                    (0x000000FF)
#define TVE_IP_TEST_HLR1_hlr(data)                                                   (0x000000FF&((data)<<0))
#define TVE_IP_TEST_HLR1_hlr_src(data)                                               ((0x000000FF&(data))>>0)
#define TVE_IP_TEST_HLR1_get_hlr(data)                                               ((0x000000FF&(data))>>0)


#define TVE_IP_TEST_VSMR                                                             0x180189bc
#define TVE_IP_TEST_VSMR_reg_addr                                                    "0xB80189BC"
#define TVE_IP_TEST_VSMR_reg                                                         0xB80189BC
#define set_TVE_IP_TEST_VSMR_reg(data)   (*((volatile unsigned int*) TVE_IP_TEST_VSMR_reg)=data)
#define get_TVE_IP_TEST_VSMR_reg   (*((volatile unsigned int*) TVE_IP_TEST_VSMR_reg))
#define TVE_IP_TEST_VSMR_inst_adr                                                    "0x006F"
#define TVE_IP_TEST_VSMR_inst                                                        0x006F
#define TVE_IP_TEST_VSMR_vsmr_shift                                                  (0)
#define TVE_IP_TEST_VSMR_vsmr_mask                                                   (0x0000001F)
#define TVE_IP_TEST_VSMR_vsmr(data)                                                  (0x0000001F&((data)<<0))
#define TVE_IP_TEST_VSMR_vsmr_src(data)                                              ((0x0000001F&(data))>>0)
#define TVE_IP_TEST_VSMR_get_vsmr(data)                                              ((0x0000001F&(data))>>0)


#define TVE_IP_SYNC_STRT                                                             0x180189d0
#define TVE_IP_SYNC_STRT_reg_addr                                                    "0xB80189D0"
#define TVE_IP_SYNC_STRT_reg                                                         0xB80189D0
#define set_TVE_IP_SYNC_STRT_reg(data)   (*((volatile unsigned int*) TVE_IP_SYNC_STRT_reg)=data)
#define get_TVE_IP_SYNC_STRT_reg   (*((volatile unsigned int*) TVE_IP_SYNC_STRT_reg))
#define TVE_IP_SYNC_STRT_inst_adr                                                    "0x0074"
#define TVE_IP_SYNC_STRT_inst                                                        0x0074
#define TVE_IP_SYNC_STRT_sync_strt_shift                                             (0)
#define TVE_IP_SYNC_STRT_sync_strt_mask                                              (0x0000000F)
#define TVE_IP_SYNC_STRT_sync_strt(data)                                             (0x0000000F&((data)<<0))
#define TVE_IP_SYNC_STRT_sync_strt_src(data)                                         ((0x0000000F&(data))>>0)
#define TVE_IP_SYNC_STRT_get_sync_strt(data)                                         ((0x0000000F&(data))>>0)


#define TVE_IP_SYNC_END                                                              0x180189d4
#define TVE_IP_SYNC_END_reg_addr                                                     "0xB80189D4"
#define TVE_IP_SYNC_END_reg                                                          0xB80189D4
#define set_TVE_IP_SYNC_END_reg(data)   (*((volatile unsigned int*) TVE_IP_SYNC_END_reg)=data)
#define get_TVE_IP_SYNC_END_reg   (*((volatile unsigned int*) TVE_IP_SYNC_END_reg))
#define TVE_IP_SYNC_END_inst_adr                                                     "0x0075"
#define TVE_IP_SYNC_END_inst                                                         0x0075
#define TVE_IP_SYNC_END_sync_end_shift                                               (0)
#define TVE_IP_SYNC_END_sync_end_mask                                                (0x0000007F)
#define TVE_IP_SYNC_END_sync_end(data)                                               (0x0000007F&((data)<<0))
#define TVE_IP_SYNC_END_sync_end_src(data)                                           ((0x0000007F&(data))>>0)
#define TVE_IP_SYNC_END_get_sync_end(data)                                           ((0x0000007F&(data))>>0)


#define TVE_IP_SYNC_SREND                                                            0x180189d8
#define TVE_IP_SYNC_SREND_reg_addr                                                   "0xB80189D8"
#define TVE_IP_SYNC_SREND_reg                                                        0xB80189D8
#define set_TVE_IP_SYNC_SREND_reg(data)   (*((volatile unsigned int*) TVE_IP_SYNC_SREND_reg)=data)
#define get_TVE_IP_SYNC_SREND_reg   (*((volatile unsigned int*) TVE_IP_SYNC_SREND_reg))
#define TVE_IP_SYNC_SREND_inst_adr                                                   "0x0076"
#define TVE_IP_SYNC_SREND_inst                                                       0x0076
#define TVE_IP_SYNC_SREND_sync_srend_shift                                           (0)
#define TVE_IP_SYNC_SREND_sync_srend_mask                                            (0x000000FF)
#define TVE_IP_SYNC_SREND_sync_srend(data)                                           (0x000000FF&((data)<<0))
#define TVE_IP_SYNC_SREND_sync_srend_src(data)                                       ((0x000000FF&(data))>>0)
#define TVE_IP_SYNC_SREND_get_sync_srend(data)                                       ((0x000000FF&(data))>>0)


#define TVE_IP_SYNC_EQEND                                                            0x180189dc
#define TVE_IP_SYNC_EQEND_reg_addr                                                   "0xB80189DC"
#define TVE_IP_SYNC_EQEND_reg                                                        0xB80189DC
#define set_TVE_IP_SYNC_EQEND_reg(data)   (*((volatile unsigned int*) TVE_IP_SYNC_EQEND_reg)=data)
#define get_TVE_IP_SYNC_EQEND_reg   (*((volatile unsigned int*) TVE_IP_SYNC_EQEND_reg))
#define TVE_IP_SYNC_EQEND_inst_adr                                                   "0x0077"
#define TVE_IP_SYNC_EQEND_inst                                                       0x0077
#define TVE_IP_SYNC_EQEND_sync_eqend_shift                                           (0)
#define TVE_IP_SYNC_EQEND_sync_eqend_mask                                            (0x0000003F)
#define TVE_IP_SYNC_EQEND_sync_eqend(data)                                           (0x0000003F&((data)<<0))
#define TVE_IP_SYNC_EQEND_sync_eqend_src(data)                                       ((0x0000003F&(data))>>0)
#define TVE_IP_SYNC_EQEND_get_sync_eqend(data)                                       ((0x0000003F&(data))>>0)


#define TVE_IP_ACTV_STRT                                                             0x180189e0
#define TVE_IP_ACTV_STRT_reg_addr                                                    "0xB80189E0"
#define TVE_IP_ACTV_STRT_reg                                                         0xB80189E0
#define set_TVE_IP_ACTV_STRT_reg(data)   (*((volatile unsigned int*) TVE_IP_ACTV_STRT_reg)=data)
#define get_TVE_IP_ACTV_STRT_reg   (*((volatile unsigned int*) TVE_IP_ACTV_STRT_reg))
#define TVE_IP_ACTV_STRT_inst_adr                                                    "0x0078"
#define TVE_IP_ACTV_STRT_inst                                                        0x0078
#define TVE_IP_ACTV_STRT_actv_strt_shift                                             (0)
#define TVE_IP_ACTV_STRT_actv_strt_mask                                              (0x000000FF)
#define TVE_IP_ACTV_STRT_actv_strt(data)                                             (0x000000FF&((data)<<0))
#define TVE_IP_ACTV_STRT_actv_strt_src(data)                                         ((0x000000FF&(data))>>0)
#define TVE_IP_ACTV_STRT_get_actv_strt(data)                                         ((0x000000FF&(data))>>0)


#define TVE_IP_ACTV_END                                                              0x180189e4
#define TVE_IP_ACTV_END_reg_addr                                                     "0xB80189E4"
#define TVE_IP_ACTV_END_reg                                                          0xB80189E4
#define set_TVE_IP_ACTV_END_reg(data)   (*((volatile unsigned int*) TVE_IP_ACTV_END_reg)=data)
#define get_TVE_IP_ACTV_END_reg   (*((volatile unsigned int*) TVE_IP_ACTV_END_reg))
#define TVE_IP_ACTV_END_inst_adr                                                     "0x0079"
#define TVE_IP_ACTV_END_inst                                                         0x0079
#define TVE_IP_ACTV_END_actv_end_shift                                               (0)
#define TVE_IP_ACTV_END_actv_end_mask                                                (0x000000FF)
#define TVE_IP_ACTV_END_actv_end(data)                                               (0x000000FF&((data)<<0))
#define TVE_IP_ACTV_END_actv_end_src(data)                                           ((0x000000FF&(data))>>0)
#define TVE_IP_ACTV_END_get_actv_end(data)                                           ((0x000000FF&(data))>>0)


#define TVE_IP_WBRST_STRT                                                            0x180189e8
#define TVE_IP_WBRST_STRT_reg_addr                                                   "0xB80189E8"
#define TVE_IP_WBRST_STRT_reg                                                        0xB80189E8
#define set_TVE_IP_WBRST_STRT_reg(data)   (*((volatile unsigned int*) TVE_IP_WBRST_STRT_reg)=data)
#define get_TVE_IP_WBRST_STRT_reg   (*((volatile unsigned int*) TVE_IP_WBRST_STRT_reg))
#define TVE_IP_WBRST_STRT_inst_adr                                                   "0x007A"
#define TVE_IP_WBRST_STRT_inst                                                       0x007A
#define TVE_IP_WBRST_STRT_wbrst_strt_shift                                           (0)
#define TVE_IP_WBRST_STRT_wbrst_strt_mask                                            (0x0000007F)
#define TVE_IP_WBRST_STRT_wbrst_strt(data)                                           (0x0000007F&((data)<<0))
#define TVE_IP_WBRST_STRT_wbrst_strt_src(data)                                       ((0x0000007F&(data))>>0)
#define TVE_IP_WBRST_STRT_get_wbrst_strt(data)                                       ((0x0000007F&(data))>>0)


#define TVE_IP_NBRST_STRT                                                            0x180189ec
#define TVE_IP_NBRST_STRT_reg_addr                                                   "0xB80189EC"
#define TVE_IP_NBRST_STRT_reg                                                        0xB80189EC
#define set_TVE_IP_NBRST_STRT_reg(data)   (*((volatile unsigned int*) TVE_IP_NBRST_STRT_reg)=data)
#define get_TVE_IP_NBRST_STRT_reg   (*((volatile unsigned int*) TVE_IP_NBRST_STRT_reg))
#define TVE_IP_NBRST_STRT_inst_adr                                                   "0x007B"
#define TVE_IP_NBRST_STRT_inst                                                       0x007B
#define TVE_IP_NBRST_STRT_nbrst_strt_shift                                           (0)
#define TVE_IP_NBRST_STRT_nbrst_strt_mask                                            (0x0000007F)
#define TVE_IP_NBRST_STRT_nbrst_strt(data)                                           (0x0000007F&((data)<<0))
#define TVE_IP_NBRST_STRT_nbrst_strt_src(data)                                       ((0x0000007F&(data))>>0)
#define TVE_IP_NBRST_STRT_get_nbrst_strt(data)                                       ((0x0000007F&(data))>>0)


#define TVE_IP_NBRST_END                                                             0x180189f0
#define TVE_IP_NBRST_END_reg_addr                                                    "0xB80189F0"
#define TVE_IP_NBRST_END_reg                                                         0xB80189F0
#define set_TVE_IP_NBRST_END_reg(data)   (*((volatile unsigned int*) TVE_IP_NBRST_END_reg)=data)
#define get_TVE_IP_NBRST_END_reg   (*((volatile unsigned int*) TVE_IP_NBRST_END_reg))
#define TVE_IP_NBRST_END_inst_adr                                                    "0x007C"
#define TVE_IP_NBRST_END_inst                                                        0x007C
#define TVE_IP_NBRST_END_nbrst_end_shift                                             (0)
#define TVE_IP_NBRST_END_nbrst_end_mask                                              (0x000000FF)
#define TVE_IP_NBRST_END_nbrst_end(data)                                             (0x000000FF&((data)<<0))
#define TVE_IP_NBRST_END_nbrst_end_src(data)                                         ((0x000000FF&(data))>>0)
#define TVE_IP_NBRST_END_get_nbrst_end(data)                                         ((0x000000FF&(data))>>0)


#define TVE_IP_MVFCR                                                                 0x18018920
#define TVE_IP_MVFCR_reg_addr                                                        "0xB8018920"
#define TVE_IP_MVFCR_reg                                                             0xB8018920
#define set_TVE_IP_MVFCR_reg(data)   (*((volatile unsigned int*) TVE_IP_MVFCR_reg)=data)
#define get_TVE_IP_MVFCR_reg   (*((volatile unsigned int*) TVE_IP_MVFCR_reg))
#define TVE_IP_MVFCR_inst_adr                                                        "0x0048"
#define TVE_IP_MVFCR_inst                                                            0x0048
#define TVE_IP_MVFCR_mvfcr_shift                                                     (0)
#define TVE_IP_MVFCR_mvfcr_mask                                                      (0x000000FF)
#define TVE_IP_MVFCR_mvfcr(data)                                                     (0x000000FF&((data)<<0))
#define TVE_IP_MVFCR_mvfcr_src(data)                                                 ((0x000000FF&(data))>>0)
#define TVE_IP_MVFCR_get_mvfcr(data)                                                 ((0x000000FF&(data))>>0)


#define TVE_IP_MVCSL1                                                                0x18018924
#define TVE_IP_MVCSL1_reg_addr                                                       "0xB8018924"
#define TVE_IP_MVCSL1_reg                                                            0xB8018924
#define set_TVE_IP_MVCSL1_reg(data)   (*((volatile unsigned int*) TVE_IP_MVCSL1_reg)=data)
#define get_TVE_IP_MVCSL1_reg   (*((volatile unsigned int*) TVE_IP_MVCSL1_reg))
#define TVE_IP_MVCSL1_inst_adr                                                       "0x0049"
#define TVE_IP_MVCSL1_inst                                                           0x0049
#define TVE_IP_MVCSL1_mvcsl1_shift                                                   (0)
#define TVE_IP_MVCSL1_mvcsl1_mask                                                    (0x000000FF)
#define TVE_IP_MVCSL1_mvcsl1(data)                                                   (0x000000FF&((data)<<0))
#define TVE_IP_MVCSL1_mvcsl1_src(data)                                               ((0x000000FF&(data))>>0)
#define TVE_IP_MVCSL1_get_mvcsl1(data)                                               ((0x000000FF&(data))>>0)


#define TVE_IP_MVCLS1                                                                0x18018928
#define TVE_IP_MVCLS1_reg_addr                                                       "0xB8018928"
#define TVE_IP_MVCLS1_reg                                                            0xB8018928
#define set_TVE_IP_MVCLS1_reg(data)   (*((volatile unsigned int*) TVE_IP_MVCLS1_reg)=data)
#define get_TVE_IP_MVCLS1_reg   (*((volatile unsigned int*) TVE_IP_MVCLS1_reg))
#define TVE_IP_MVCLS1_inst_adr                                                       "0x004A"
#define TVE_IP_MVCLS1_inst                                                           0x004A
#define TVE_IP_MVCLS1_mvcls1_shift                                                   (0)
#define TVE_IP_MVCLS1_mvcls1_mask                                                    (0x0000003F)
#define TVE_IP_MVCLS1_mvcls1(data)                                                   (0x0000003F&((data)<<0))
#define TVE_IP_MVCLS1_mvcls1_src(data)                                               ((0x0000003F&(data))>>0)
#define TVE_IP_MVCLS1_get_mvcls1(data)                                               ((0x0000003F&(data))>>0)


#define TVE_IP_MVCSL2                                                                0x1801892c
#define TVE_IP_MVCSL2_reg_addr                                                       "0xB801892C"
#define TVE_IP_MVCSL2_reg                                                            0xB801892C
#define set_TVE_IP_MVCSL2_reg(data)   (*((volatile unsigned int*) TVE_IP_MVCSL2_reg)=data)
#define get_TVE_IP_MVCSL2_reg   (*((volatile unsigned int*) TVE_IP_MVCSL2_reg))
#define TVE_IP_MVCSL2_inst_adr                                                       "0x004B"
#define TVE_IP_MVCSL2_inst                                                           0x004B
#define TVE_IP_MVCSL2_mvcsl2_shift                                                   (0)
#define TVE_IP_MVCSL2_mvcsl2_mask                                                    (0x000000FF)
#define TVE_IP_MVCSL2_mvcsl2(data)                                                   (0x000000FF&((data)<<0))
#define TVE_IP_MVCSL2_mvcsl2_src(data)                                               ((0x000000FF&(data))>>0)
#define TVE_IP_MVCSL2_get_mvcsl2(data)                                               ((0x000000FF&(data))>>0)


#define TVE_IP_MVCLS2                                                                0x18018930
#define TVE_IP_MVCLS2_reg_addr                                                       "0xB8018930"
#define TVE_IP_MVCLS2_reg                                                            0xB8018930
#define set_TVE_IP_MVCLS2_reg(data)   (*((volatile unsigned int*) TVE_IP_MVCLS2_reg)=data)
#define get_TVE_IP_MVCLS2_reg   (*((volatile unsigned int*) TVE_IP_MVCLS2_reg))
#define TVE_IP_MVCLS2_inst_adr                                                       "0x004C"
#define TVE_IP_MVCLS2_inst                                                           0x004C
#define TVE_IP_MVCLS2_mvcls2_shift                                                   (0)
#define TVE_IP_MVCLS2_mvcls2_mask                                                    (0x0000003F)
#define TVE_IP_MVCLS2_mvcls2(data)                                                   (0x0000003F&((data)<<0))
#define TVE_IP_MVCLS2_mvcls2_src(data)                                               ((0x0000003F&(data))>>0)
#define TVE_IP_MVCLS2_get_mvcls2(data)                                               ((0x0000003F&(data))>>0)


#define TVE_IP_MVCSSP                                                                0x18018934
#define TVE_IP_MVCSSP_reg_addr                                                       "0xB8018934"
#define TVE_IP_MVCSSP_reg                                                            0xB8018934
#define set_TVE_IP_MVCSSP_reg(data)   (*((volatile unsigned int*) TVE_IP_MVCSSP_reg)=data)
#define get_TVE_IP_MVCSSP_reg   (*((volatile unsigned int*) TVE_IP_MVCSSP_reg))
#define TVE_IP_MVCSSP_inst_adr                                                       "0x004D"
#define TVE_IP_MVCSSP_inst                                                           0x004D
#define TVE_IP_MVCSSP_mvcssp_shift                                                   (5)
#define TVE_IP_MVCSSP_mvcssp_mask                                                    (0x000000E0)
#define TVE_IP_MVCSSP_mvcssp(data)                                                   (0x000000E0&((data)<<5))
#define TVE_IP_MVCSSP_mvcssp_src(data)                                               ((0x000000E0&(data))>>5)
#define TVE_IP_MVCSSP_get_mvcssp(data)                                               ((0x000000E0&(data))>>5)
#define TVE_IP_MVCSSP_mvcsnum_shift                                                  (2)
#define TVE_IP_MVCSSP_mvcsnum_mask                                                   (0x0000001C)
#define TVE_IP_MVCSSP_mvcsnum(data)                                                  (0x0000001C&((data)<<2))
#define TVE_IP_MVCSSP_mvcsnum_src(data)                                              ((0x0000001C&(data))>>2)
#define TVE_IP_MVCSSP_get_mvcsnum(data)                                              ((0x0000001C&(data))>>2)
#define TVE_IP_MVCSSP_mvcsln_shift                                                   (0)
#define TVE_IP_MVCSSP_mvcsln_mask                                                    (0x00000003)
#define TVE_IP_MVCSSP_mvcsln(data)                                                   (0x00000003&((data)<<0))
#define TVE_IP_MVCSSP_mvcsln_src(data)                                               ((0x00000003&(data))>>0)
#define TVE_IP_MVCSSP_get_mvcsln(data)                                               ((0x00000003&(data))>>0)


#define TVE_IP_MVPSD                                                                 0x18018938
#define TVE_IP_MVPSD_reg_addr                                                        "0xB8018938"
#define TVE_IP_MVPSD_reg                                                             0xB8018938
#define set_TVE_IP_MVPSD_reg(data)   (*((volatile unsigned int*) TVE_IP_MVPSD_reg)=data)
#define get_TVE_IP_MVPSD_reg   (*((volatile unsigned int*) TVE_IP_MVPSD_reg))
#define TVE_IP_MVPSD_inst_adr                                                        "0x004E"
#define TVE_IP_MVPSD_inst                                                            0x004E
#define TVE_IP_MVPSD_mvpsd_shift                                                     (0)
#define TVE_IP_MVPSD_mvpsd_mask                                                      (0x0000003F)
#define TVE_IP_MVPSD_mvpsd(data)                                                     (0x0000003F&((data)<<0))
#define TVE_IP_MVPSD_mvpsd_src(data)                                                 ((0x0000003F&(data))>>0)
#define TVE_IP_MVPSD_get_mvpsd(data)                                                 ((0x0000003F&(data))>>0)


#define TVE_IP_MVPSL                                                                 0x1801893c
#define TVE_IP_MVPSL_reg_addr                                                        "0xB801893C"
#define TVE_IP_MVPSL_reg                                                             0xB801893C
#define set_TVE_IP_MVPSL_reg(data)   (*((volatile unsigned int*) TVE_IP_MVPSL_reg)=data)
#define get_TVE_IP_MVPSL_reg   (*((volatile unsigned int*) TVE_IP_MVPSL_reg))
#define TVE_IP_MVPSL_inst_adr                                                        "0x004F"
#define TVE_IP_MVPSL_inst                                                            0x004F
#define TVE_IP_MVPSL_mvpsl_shift                                                     (0)
#define TVE_IP_MVPSL_mvpsl_mask                                                      (0x0000003F)
#define TVE_IP_MVPSL_mvpsl(data)                                                     (0x0000003F&((data)<<0))
#define TVE_IP_MVPSL_mvpsl_src(data)                                                 ((0x0000003F&(data))>>0)
#define TVE_IP_MVPSL_get_mvpsl(data)                                                 ((0x0000003F&(data))>>0)


#define TVE_IP_MVPSS                                                                 0x18018940
#define TVE_IP_MVPSS_reg_addr                                                        "0xB8018940"
#define TVE_IP_MVPSS_reg                                                             0xB8018940
#define set_TVE_IP_MVPSS_reg(data)   (*((volatile unsigned int*) TVE_IP_MVPSS_reg)=data)
#define get_TVE_IP_MVPSS_reg   (*((volatile unsigned int*) TVE_IP_MVPSS_reg))
#define TVE_IP_MVPSS_inst_adr                                                        "0x0050"
#define TVE_IP_MVPSS_inst                                                            0x0050
#define TVE_IP_MVPSS_mvpss_shift                                                     (0)
#define TVE_IP_MVPSS_mvpss_mask                                                      (0x0000003F)
#define TVE_IP_MVPSS_mvpss(data)                                                     (0x0000003F&((data)<<0))
#define TVE_IP_MVPSS_mvpss_src(data)                                                 ((0x0000003F&(data))>>0)
#define TVE_IP_MVPSS_get_mvpss(data)                                                 ((0x0000003F&(data))>>0)


#define TVE_IP_MVPSLS0                                                               0x18018944
#define TVE_IP_MVPSLS0_reg_addr                                                      "0xB8018944"
#define TVE_IP_MVPSLS0_reg                                                           0xB8018944
#define set_TVE_IP_MVPSLS0_reg(data)   (*((volatile unsigned int*) TVE_IP_MVPSLS0_reg)=data)
#define get_TVE_IP_MVPSLS0_reg   (*((volatile unsigned int*) TVE_IP_MVPSLS0_reg))
#define TVE_IP_MVPSLS0_inst_adr                                                      "0x0051"
#define TVE_IP_MVPSLS0_inst                                                          0x0051
#define TVE_IP_MVPSLS0_mvpsls_shift                                                  (0)
#define TVE_IP_MVPSLS0_mvpsls_mask                                                   (0x0000007F)
#define TVE_IP_MVPSLS0_mvpsls(data)                                                  (0x0000007F&((data)<<0))
#define TVE_IP_MVPSLS0_mvpsls_src(data)                                              ((0x0000007F&(data))>>0)
#define TVE_IP_MVPSLS0_get_mvpsls(data)                                              ((0x0000007F&(data))>>0)


#define TVE_IP_MVPSLS1                                                               0x18018948
#define TVE_IP_MVPSLS1_reg_addr                                                      "0xB8018948"
#define TVE_IP_MVPSLS1_reg                                                           0xB8018948
#define set_TVE_IP_MVPSLS1_reg(data)   (*((volatile unsigned int*) TVE_IP_MVPSLS1_reg)=data)
#define get_TVE_IP_MVPSLS1_reg   (*((volatile unsigned int*) TVE_IP_MVPSLS1_reg))
#define TVE_IP_MVPSLS1_inst_adr                                                      "0x0052"
#define TVE_IP_MVPSLS1_inst                                                          0x0052
#define TVE_IP_MVPSLS1_mvpsls_shift                                                  (0)
#define TVE_IP_MVPSLS1_mvpsls_mask                                                   (0x000000FF)
#define TVE_IP_MVPSLS1_mvpsls(data)                                                  (0x000000FF&((data)<<0))
#define TVE_IP_MVPSLS1_mvpsls_src(data)                                              ((0x000000FF&(data))>>0)
#define TVE_IP_MVPSLS1_get_mvpsls(data)                                              ((0x000000FF&(data))>>0)


#define TVE_IP_MVPSFS0                                                               0x1801894c
#define TVE_IP_MVPSFS0_reg_addr                                                      "0xB801894C"
#define TVE_IP_MVPSFS0_reg                                                           0xB801894C
#define set_TVE_IP_MVPSFS0_reg(data)   (*((volatile unsigned int*) TVE_IP_MVPSFS0_reg)=data)
#define get_TVE_IP_MVPSFS0_reg   (*((volatile unsigned int*) TVE_IP_MVPSFS0_reg))
#define TVE_IP_MVPSFS0_inst_adr                                                      "0x0053"
#define TVE_IP_MVPSFS0_inst                                                          0x0053
#define TVE_IP_MVPSFS0_mvpsfs_shift                                                  (0)
#define TVE_IP_MVPSFS0_mvpsfs_mask                                                   (0x0000007F)
#define TVE_IP_MVPSFS0_mvpsfs(data)                                                  (0x0000007F&((data)<<0))
#define TVE_IP_MVPSFS0_mvpsfs_src(data)                                              ((0x0000007F&(data))>>0)
#define TVE_IP_MVPSFS0_get_mvpsfs(data)                                              ((0x0000007F&(data))>>0)


#define TVE_IP_MVPSFS1                                                               0x18018950
#define TVE_IP_MVPSFS1_reg_addr                                                      "0xB8018950"
#define TVE_IP_MVPSFS1_reg                                                           0xB8018950
#define set_TVE_IP_MVPSFS1_reg(data)   (*((volatile unsigned int*) TVE_IP_MVPSFS1_reg)=data)
#define get_TVE_IP_MVPSFS1_reg   (*((volatile unsigned int*) TVE_IP_MVPSFS1_reg))
#define TVE_IP_MVPSFS1_inst_adr                                                      "0x0054"
#define TVE_IP_MVPSFS1_inst                                                          0x0054
#define TVE_IP_MVPSFS1_mvpsfs_shift                                                  (0)
#define TVE_IP_MVPSFS1_mvpsfs_mask                                                   (0x000000FF)
#define TVE_IP_MVPSFS1_mvpsfs(data)                                                  (0x000000FF&((data)<<0))
#define TVE_IP_MVPSFS1_mvpsfs_src(data)                                              ((0x000000FF&(data))>>0)
#define TVE_IP_MVPSFS1_get_mvpsfs(data)                                              ((0x000000FF&(data))>>0)


#define TVE_IP_MVPSAGCA                                                              0x18018954
#define TVE_IP_MVPSAGCA_reg_addr                                                     "0xB8018954"
#define TVE_IP_MVPSAGCA_reg                                                          0xB8018954
#define set_TVE_IP_MVPSAGCA_reg(data)   (*((volatile unsigned int*) TVE_IP_MVPSAGCA_reg)=data)
#define get_TVE_IP_MVPSAGCA_reg   (*((volatile unsigned int*) TVE_IP_MVPSAGCA_reg))
#define TVE_IP_MVPSAGCA_inst_adr                                                     "0x0055"
#define TVE_IP_MVPSAGCA_inst                                                         0x0055
#define TVE_IP_MVPSAGCA_mvpsagca_shift                                               (0)
#define TVE_IP_MVPSAGCA_mvpsagca_mask                                                (0x000000FF)
#define TVE_IP_MVPSAGCA_mvpsagca(data)                                               (0x000000FF&((data)<<0))
#define TVE_IP_MVPSAGCA_mvpsagca_src(data)                                           ((0x000000FF&(data))>>0)
#define TVE_IP_MVPSAGCA_get_mvpsagca(data)                                           ((0x000000FF&(data))>>0)


#define TVE_IP_MVPSAGCB                                                              0x18018958
#define TVE_IP_MVPSAGCB_reg_addr                                                     "0xB8018958"
#define TVE_IP_MVPSAGCB_reg                                                          0xB8018958
#define set_TVE_IP_MVPSAGCB_reg(data)   (*((volatile unsigned int*) TVE_IP_MVPSAGCB_reg)=data)
#define get_TVE_IP_MVPSAGCB_reg   (*((volatile unsigned int*) TVE_IP_MVPSAGCB_reg))
#define TVE_IP_MVPSAGCB_inst_adr                                                     "0x0056"
#define TVE_IP_MVPSAGCB_inst                                                         0x0056
#define TVE_IP_MVPSAGCB_mvpsagcb_shift                                               (0)
#define TVE_IP_MVPSAGCB_mvpsagcb_mask                                                (0x000000FF)
#define TVE_IP_MVPSAGCB_mvpsagcb(data)                                               (0x000000FF&((data)<<0))
#define TVE_IP_MVPSAGCB_mvpsagcb_src(data)                                           ((0x000000FF&(data))>>0)
#define TVE_IP_MVPSAGCB_get_mvpsagcb(data)                                           ((0x000000FF&(data))>>0)


#define TVE_IP_MVEOFBPC                                                              0x1801895c
#define TVE_IP_MVEOFBPC_reg_addr                                                     "0xB801895C"
#define TVE_IP_MVEOFBPC_reg                                                          0xB801895C
#define set_TVE_IP_MVEOFBPC_reg(data)   (*((volatile unsigned int*) TVE_IP_MVEOFBPC_reg)=data)
#define get_TVE_IP_MVEOFBPC_reg   (*((volatile unsigned int*) TVE_IP_MVEOFBPC_reg))
#define TVE_IP_MVEOFBPC_inst_adr                                                     "0x0057"
#define TVE_IP_MVEOFBPC_inst                                                         0x0057
#define TVE_IP_MVEOFBPC_mveofbpc_shift                                               (0)
#define TVE_IP_MVEOFBPC_mveofbpc_mask                                                (0x000000FF)
#define TVE_IP_MVEOFBPC_mveofbpc(data)                                               (0x000000FF&((data)<<0))
#define TVE_IP_MVEOFBPC_mveofbpc_src(data)                                           ((0x000000FF&(data))>>0)
#define TVE_IP_MVEOFBPC_get_mveofbpc(data)                                           ((0x000000FF&(data))>>0)


#define TVE_IP_MVPBZ1                                                                0x18018960
#define TVE_IP_MVPBZ1_reg_addr                                                       "0xB8018960"
#define TVE_IP_MVPBZ1_reg                                                            0xB8018960
#define set_TVE_IP_MVPBZ1_reg(data)   (*((volatile unsigned int*) TVE_IP_MVPBZ1_reg)=data)
#define get_TVE_IP_MVPBZ1_reg   (*((volatile unsigned int*) TVE_IP_MVPBZ1_reg))
#define TVE_IP_MVPBZ1_inst_adr                                                       "0x0058"
#define TVE_IP_MVPBZ1_inst                                                           0x0058
#define TVE_IP_MVPBZ1_mvpbz1_shift                                                   (4)
#define TVE_IP_MVPBZ1_mvpbz1_mask                                                    (0x000000F0)
#define TVE_IP_MVPBZ1_mvpbz1(data)                                                   (0x000000F0&((data)<<4))
#define TVE_IP_MVPBZ1_mvpbz1_src(data)                                               ((0x000000F0&(data))>>4)
#define TVE_IP_MVPBZ1_get_mvpbz1(data)                                               ((0x000000F0&(data))>>4)
#define TVE_IP_MVPBZ1_mvpbz2_shift                                                   (0)
#define TVE_IP_MVPBZ1_mvpbz2_mask                                                    (0x0000000F)
#define TVE_IP_MVPBZ1_mvpbz2(data)                                                   (0x0000000F&((data)<<0))
#define TVE_IP_MVPBZ1_mvpbz2_src(data)                                               ((0x0000000F&(data))>>0)
#define TVE_IP_MVPBZ1_get_mvpbz2(data)                                               ((0x0000000F&(data))>>0)


#define TVE_IP_MVPBZ3                                                                0x18018964
#define TVE_IP_MVPBZ3_reg_addr                                                       "0xB8018964"
#define TVE_IP_MVPBZ3_reg                                                            0xB8018964
#define set_TVE_IP_MVPBZ3_reg(data)   (*((volatile unsigned int*) TVE_IP_MVPBZ3_reg)=data)
#define get_TVE_IP_MVPBZ3_reg   (*((volatile unsigned int*) TVE_IP_MVPBZ3_reg))
#define TVE_IP_MVPBZ3_inst_adr                                                       "0x0059"
#define TVE_IP_MVPBZ3_inst                                                           0x0059
#define TVE_IP_MVPBZ3_mvpbz3_shift                                                   (4)
#define TVE_IP_MVPBZ3_mvpbz3_mask                                                    (0x000000F0)
#define TVE_IP_MVPBZ3_mvpbz3(data)                                                   (0x000000F0&((data)<<4))
#define TVE_IP_MVPBZ3_mvpbz3_src(data)                                               ((0x000000F0&(data))>>4)
#define TVE_IP_MVPBZ3_get_mvpbz3(data)                                               ((0x000000F0&(data))>>4)
#define TVE_IP_MVPBZ3_mvpadvbsen_shift                                               (3)
#define TVE_IP_MVPBZ3_mvpadvbsen_mask                                                (0x00000008)
#define TVE_IP_MVPBZ3_mvpadvbsen(data)                                               (0x00000008&((data)<<3))
#define TVE_IP_MVPBZ3_mvpadvbsen_src(data)                                           ((0x00000008&(data))>>3)
#define TVE_IP_MVPBZ3_get_mvpadvbsen(data)                                           ((0x00000008&(data))>>3)
#define TVE_IP_MVPBZ3_mvpzninvrt_shift                                               (0)
#define TVE_IP_MVPBZ3_mvpzninvrt_mask                                                (0x00000007)
#define TVE_IP_MVPBZ3_mvpzninvrt(data)                                               (0x00000007&((data)<<0))
#define TVE_IP_MVPBZ3_mvpzninvrt_src(data)                                           ((0x00000007&(data))>>0)
#define TVE_IP_MVPBZ3_get_mvpzninvrt(data)                                           ((0x00000007&(data))>>0)


#define TVE_IP_MVPCSLIMD0                                                            0x18018968
#define TVE_IP_MVPCSLIMD0_reg_addr                                                   "0xB8018968"
#define TVE_IP_MVPCSLIMD0_reg                                                        0xB8018968
#define set_TVE_IP_MVPCSLIMD0_reg(data)   (*((volatile unsigned int*) TVE_IP_MVPCSLIMD0_reg)=data)
#define get_TVE_IP_MVPCSLIMD0_reg   (*((volatile unsigned int*) TVE_IP_MVPCSLIMD0_reg))
#define TVE_IP_MVPCSLIMD0_inst_adr                                                   "0x005A"
#define TVE_IP_MVPCSLIMD0_inst                                                       0x005A
#define TVE_IP_MVPCSLIMD0_mvpcslimd_lsb_shift                                        (0)
#define TVE_IP_MVPCSLIMD0_mvpcslimd_lsb_mask                                         (0x000000FF)
#define TVE_IP_MVPCSLIMD0_mvpcslimd_lsb(data)                                        (0x000000FF&((data)<<0))
#define TVE_IP_MVPCSLIMD0_mvpcslimd_lsb_src(data)                                    ((0x000000FF&(data))>>0)
#define TVE_IP_MVPCSLIMD0_get_mvpcslimd_lsb(data)                                    ((0x000000FF&(data))>>0)


#define TVE_IP_MVPCSLIMD1                                                            0x1801896c
#define TVE_IP_MVPCSLIMD1_reg_addr                                                   "0xB801896C"
#define TVE_IP_MVPCSLIMD1_reg                                                        0xB801896C
#define set_TVE_IP_MVPCSLIMD1_reg(data)   (*((volatile unsigned int*) TVE_IP_MVPCSLIMD1_reg)=data)
#define get_TVE_IP_MVPCSLIMD1_reg   (*((volatile unsigned int*) TVE_IP_MVPCSLIMD1_reg))
#define TVE_IP_MVPCSLIMD1_inst_adr                                                   "0x005B"
#define TVE_IP_MVPCSLIMD1_inst                                                       0x005B
#define TVE_IP_MVPCSLIMD1_mvpcslimd_msb_shift                                        (0)
#define TVE_IP_MVPCSLIMD1_mvpcslimd_msb_mask                                         (0x00000003)
#define TVE_IP_MVPCSLIMD1_mvpcslimd_msb(data)                                        (0x00000003&((data)<<0))
#define TVE_IP_MVPCSLIMD1_mvpcslimd_msb_src(data)                                    ((0x00000003&(data))>>0)
#define TVE_IP_MVPCSLIMD1_get_mvpcslimd_msb(data)                                    ((0x00000003&(data))>>0)


#define TVE_IP_MV_CTRL                                                               0x18018990
#define TVE_IP_MV_CTRL_reg_addr                                                      "0xB8018990"
#define TVE_IP_MV_CTRL_reg                                                           0xB8018990
#define set_TVE_IP_MV_CTRL_reg(data)   (*((volatile unsigned int*) TVE_IP_MV_CTRL_reg)=data)
#define get_TVE_IP_MV_CTRL_reg   (*((volatile unsigned int*) TVE_IP_MV_CTRL_reg))
#define TVE_IP_MV_CTRL_inst_adr                                                      "0x0064"
#define TVE_IP_MV_CTRL_inst                                                          0x0064
#define TVE_IP_MV_CTRL_mvtms_shift                                                   (0)
#define TVE_IP_MV_CTRL_mvtms_mask                                                    (0x000000FF)
#define TVE_IP_MV_CTRL_mvtms(data)                                                   (0x000000FF&((data)<<0))
#define TVE_IP_MV_CTRL_mvtms_src(data)                                               ((0x000000FF&(data))>>0)
#define TVE_IP_MV_CTRL_get_mvtms(data)                                               ((0x000000FF&(data))>>0)


#define TVE_VIDEO_DAC_CTRL_0                                                         0x18018200
#define TVE_VIDEO_DAC_CTRL_1                                                         0x18018204
#define TVE_VIDEO_DAC_CTRL_0_reg_addr                                                "0xB8018200"
#define TVE_VIDEO_DAC_CTRL_1_reg_addr                                                "0xB8018204"
#define TVE_VIDEO_DAC_CTRL_0_reg                                                     0xB8018200
#define TVE_VIDEO_DAC_CTRL_1_reg                                                     0xB8018204
#define set_TVE_VIDEO_DAC_CTRL_0_reg(data)   (*((volatile unsigned int*) TVE_VIDEO_DAC_CTRL_0_reg)=data)
#define set_TVE_VIDEO_DAC_CTRL_1_reg(data)   (*((volatile unsigned int*) TVE_VIDEO_DAC_CTRL_1_reg)=data)
#define get_TVE_VIDEO_DAC_CTRL_0_reg   (*((volatile unsigned int*) TVE_VIDEO_DAC_CTRL_0_reg))
#define get_TVE_VIDEO_DAC_CTRL_1_reg   (*((volatile unsigned int*) TVE_VIDEO_DAC_CTRL_1_reg))
#define TVE_VIDEO_DAC_CTRL_0_inst_adr                                                "0x0080"
#define TVE_VIDEO_DAC_CTRL_1_inst_adr                                                "0x0081"
#define TVE_VIDEO_DAC_CTRL_0_inst                                                    0x0080
#define TVE_VIDEO_DAC_CTRL_1_inst                                                    0x0081
#define TVE_VIDEO_DAC_CTRL_vdac_apow_shift                                           (22)
#define TVE_VIDEO_DAC_CTRL_vdac_apow_mask                                            (0x00400000)
#define TVE_VIDEO_DAC_CTRL_vdac_apow(data)                                           (0x00400000&((data)<<22))
#define TVE_VIDEO_DAC_CTRL_vdac_apow_src(data)                                       ((0x00400000&(data))>>22)
#define TVE_VIDEO_DAC_CTRL_get_vdac_apow(data)                                       ((0x00400000&(data))>>22)
#define TVE_VIDEO_DAC_CTRL_vdac_bpow_shift                                           (21)
#define TVE_VIDEO_DAC_CTRL_vdac_bpow_mask                                            (0x00200000)
#define TVE_VIDEO_DAC_CTRL_vdac_bpow(data)                                           (0x00200000&((data)<<21))
#define TVE_VIDEO_DAC_CTRL_vdac_bpow_src(data)                                       ((0x00200000&(data))>>21)
#define TVE_VIDEO_DAC_CTRL_get_vdac_bpow(data)                                       ((0x00200000&(data))>>21)
#define TVE_VIDEO_DAC_CTRL_vdac_cpow_shift                                           (20)
#define TVE_VIDEO_DAC_CTRL_vdac_cpow_mask                                            (0x00100000)
#define TVE_VIDEO_DAC_CTRL_vdac_cpow(data)                                           (0x00100000&((data)<<20))
#define TVE_VIDEO_DAC_CTRL_vdac_cpow_src(data)                                       ((0x00100000&(data))>>20)
#define TVE_VIDEO_DAC_CTRL_get_vdac_cpow(data)                                       ((0x00100000&(data))>>20)
#define TVE_VIDEO_DAC_CTRL_powldv_l_shift                                            (19)
#define TVE_VIDEO_DAC_CTRL_powldv_l_mask                                             (0x00080000)
#define TVE_VIDEO_DAC_CTRL_powldv_l(data)                                            (0x00080000&((data)<<19))
#define TVE_VIDEO_DAC_CTRL_powldv_l_src(data)                                        ((0x00080000&(data))>>19)
#define TVE_VIDEO_DAC_CTRL_get_powldv_l(data)                                        ((0x00080000&(data))>>19)
#define TVE_VIDEO_DAC_CTRL_stanby_l_shift                                            (18)
#define TVE_VIDEO_DAC_CTRL_stanby_l_mask                                             (0x00040000)
#define TVE_VIDEO_DAC_CTRL_stanby_l(data)                                            (0x00040000&((data)<<18))
#define TVE_VIDEO_DAC_CTRL_stanby_l_src(data)                                        ((0x00040000&(data))>>18)
#define TVE_VIDEO_DAC_CTRL_get_stanby_l(data)                                        ((0x00040000&(data))>>18)
#define TVE_VIDEO_DAC_CTRL_biasa_regl_shift                                          (12)
#define TVE_VIDEO_DAC_CTRL_biasa_regl_mask                                           (0x0000F000)
#define TVE_VIDEO_DAC_CTRL_biasa_regl(data)                                          (0x0000F000&((data)<<12))
#define TVE_VIDEO_DAC_CTRL_biasa_regl_src(data)                                      ((0x0000F000&(data))>>12)
#define TVE_VIDEO_DAC_CTRL_get_biasa_regl(data)                                      ((0x0000F000&(data))>>12)
#define TVE_VIDEO_DAC_CTRL_biasb_regl_shift                                          (6)
#define TVE_VIDEO_DAC_CTRL_biasb_regl_mask                                           (0x000003C0)
#define TVE_VIDEO_DAC_CTRL_biasb_regl(data)                                          (0x000003C0&((data)<<6))
#define TVE_VIDEO_DAC_CTRL_biasb_regl_src(data)                                      ((0x000003C0&(data))>>6)
#define TVE_VIDEO_DAC_CTRL_get_biasb_regl(data)                                      ((0x000003C0&(data))>>6)
#define TVE_VIDEO_DAC_CTRL_biasc_regl_shift                                          (0)
#define TVE_VIDEO_DAC_CTRL_biasc_regl_mask                                           (0x0000000F)
#define TVE_VIDEO_DAC_CTRL_biasc_regl(data)                                          (0x0000000F&((data)<<0))
#define TVE_VIDEO_DAC_CTRL_biasc_regl_src(data)                                      ((0x0000000F&(data))>>0)
#define TVE_VIDEO_DAC_CTRL_get_biasc_regl(data)                                      ((0x0000000F&(data))>>0)


#define TVE_VIDEO_DAC_CTRL2_0                                                        0x18018218
#define TVE_VIDEO_DAC_CTRL2_1                                                        0x1801821C
#define TVE_VIDEO_DAC_CTRL2_0_reg_addr                                               "0xB8018218"
#define TVE_VIDEO_DAC_CTRL2_1_reg_addr                                               "0xB801821C"
#define TVE_VIDEO_DAC_CTRL2_0_reg                                                    0xB8018218
#define TVE_VIDEO_DAC_CTRL2_1_reg                                                    0xB801821C
#define set_TVE_VIDEO_DAC_CTRL2_0_reg(data)   (*((volatile unsigned int*) TVE_VIDEO_DAC_CTRL2_0_reg)=data)
#define set_TVE_VIDEO_DAC_CTRL2_1_reg(data)   (*((volatile unsigned int*) TVE_VIDEO_DAC_CTRL2_1_reg)=data)
#define get_TVE_VIDEO_DAC_CTRL2_0_reg   (*((volatile unsigned int*) TVE_VIDEO_DAC_CTRL2_0_reg))
#define get_TVE_VIDEO_DAC_CTRL2_1_reg   (*((volatile unsigned int*) TVE_VIDEO_DAC_CTRL2_1_reg))
#define TVE_VIDEO_DAC_CTRL2_0_inst_adr                                               "0x0086"
#define TVE_VIDEO_DAC_CTRL2_1_inst_adr                                               "0x0087"
#define TVE_VIDEO_DAC_CTRL2_0_inst                                                   0x0086
#define TVE_VIDEO_DAC_CTRL2_1_inst                                                   0x0087
#define TVE_VIDEO_DAC_CTRL2_abiq_regl_shift                                          (12)
#define TVE_VIDEO_DAC_CTRL2_abiq_regl_mask                                           (0x00007000)
#define TVE_VIDEO_DAC_CTRL2_abiq_regl(data)                                          (0x00007000&((data)<<12))
#define TVE_VIDEO_DAC_CTRL2_abiq_regl_src(data)                                      ((0x00007000&(data))>>12)
#define TVE_VIDEO_DAC_CTRL2_get_abiq_regl(data)                                      ((0x00007000&(data))>>12)
#define TVE_VIDEO_DAC_CTRL2_ldvbias_regl_shift                                       (9)
#define TVE_VIDEO_DAC_CTRL2_ldvbias_regl_mask                                        (0x00000E00)
#define TVE_VIDEO_DAC_CTRL2_ldvbias_regl(data)                                       (0x00000E00&((data)<<9))
#define TVE_VIDEO_DAC_CTRL2_ldvbias_regl_src(data)                                   ((0x00000E00&(data))>>9)
#define TVE_VIDEO_DAC_CTRL2_get_ldvbias_regl(data)                                   ((0x00000E00&(data))>>9)
#define TVE_VIDEO_DAC_CTRL2_vcmref_regl_shift                                        (7)
#define TVE_VIDEO_DAC_CTRL2_vcmref_regl_mask                                         (0x00000180)
#define TVE_VIDEO_DAC_CTRL2_vcmref_regl(data)                                        (0x00000180&((data)<<7))
#define TVE_VIDEO_DAC_CTRL2_vcmref_regl_src(data)                                    ((0x00000180&(data))>>7)
#define TVE_VIDEO_DAC_CTRL2_get_vcmref_regl(data)                                    ((0x00000180&(data))>>7)
#define TVE_VIDEO_DAC_CTRL2_vdac_cf_regl_shift                                       (2)
#define TVE_VIDEO_DAC_CTRL2_vdac_cf_regl_mask                                        (0x0000001C)
#define TVE_VIDEO_DAC_CTRL2_vdac_cf_regl(data)                                       (0x0000001C&((data)<<2))
#define TVE_VIDEO_DAC_CTRL2_vdac_cf_regl_src(data)                                   ((0x0000001C&(data))>>2)
#define TVE_VIDEO_DAC_CTRL2_get_vdac_cf_regl(data)                                   ((0x0000001C&(data))>>2)
#define TVE_VIDEO_DAC_CTRL2_vdac_rf_regl_shift                                       (0)
#define TVE_VIDEO_DAC_CTRL2_vdac_rf_regl_mask                                        (0x00000003)
#define TVE_VIDEO_DAC_CTRL2_vdac_rf_regl(data)                                       (0x00000003&((data)<<0))
#define TVE_VIDEO_DAC_CTRL2_vdac_rf_regl_src(data)                                   ((0x00000003&(data))>>0)
#define TVE_VIDEO_DAC_CTRL2_get_vdac_rf_regl(data)                                   ((0x00000003&(data))>>0)


#define TVE_VIDEO_DAC_CTRL3                                                          0x18018350
#define TVE_VIDEO_DAC_CTRL3_reg_addr                                                 "0xB8018350"
#define TVE_VIDEO_DAC_CTRL3_reg                                                      0xB8018350
#define set_TVE_VIDEO_DAC_CTRL3_reg(data)   (*((volatile unsigned int*) TVE_VIDEO_DAC_CTRL3_reg)=data)
#define get_TVE_VIDEO_DAC_CTRL3_reg   (*((volatile unsigned int*) TVE_VIDEO_DAC_CTRL3_reg))
#define TVE_VIDEO_DAC_CTRL3_inst_adr                                                 "0x00D4"
#define TVE_VIDEO_DAC_CTRL3_inst                                                     0x00D4
#define TVE_VIDEO_DAC_CTRL3_write_en6_shift                                          (18)
#define TVE_VIDEO_DAC_CTRL3_write_en6_mask                                           (0x00040000)
#define TVE_VIDEO_DAC_CTRL3_write_en6(data)                                          (0x00040000&((data)<<18))
#define TVE_VIDEO_DAC_CTRL3_write_en6_src(data)                                      ((0x00040000&(data))>>18)
#define TVE_VIDEO_DAC_CTRL3_get_write_en6(data)                                      ((0x00040000&(data))>>18)
#define TVE_VIDEO_DAC_CTRL3_dcc2_l_shift                                             (17)
#define TVE_VIDEO_DAC_CTRL3_dcc2_l_mask                                              (0x00020000)
#define TVE_VIDEO_DAC_CTRL3_dcc2_l(data)                                             (0x00020000&((data)<<17))
#define TVE_VIDEO_DAC_CTRL3_dcc2_l_src(data)                                         ((0x00020000&(data))>>17)
#define TVE_VIDEO_DAC_CTRL3_get_dcc2_l(data)                                         ((0x00020000&(data))>>17)
#define TVE_VIDEO_DAC_CTRL3_write_en5_shift                                          (16)
#define TVE_VIDEO_DAC_CTRL3_write_en5_mask                                           (0x00010000)
#define TVE_VIDEO_DAC_CTRL3_write_en5(data)                                          (0x00010000&((data)<<16))
#define TVE_VIDEO_DAC_CTRL3_write_en5_src(data)                                      ((0x00010000&(data))>>16)
#define TVE_VIDEO_DAC_CTRL3_get_write_en5(data)                                      ((0x00010000&(data))>>16)
#define TVE_VIDEO_DAC_CTRL3_dcc_l_shift                                              (15)
#define TVE_VIDEO_DAC_CTRL3_dcc_l_mask                                               (0x00008000)
#define TVE_VIDEO_DAC_CTRL3_dcc_l(data)                                              (0x00008000&((data)<<15))
#define TVE_VIDEO_DAC_CTRL3_dcc_l_src(data)                                          ((0x00008000&(data))>>15)
#define TVE_VIDEO_DAC_CTRL3_get_dcc_l(data)                                          ((0x00008000&(data))>>15)
#define TVE_VIDEO_DAC_CTRL3_write_en4_shift                                          (14)
#define TVE_VIDEO_DAC_CTRL3_write_en4_mask                                           (0x00004000)
#define TVE_VIDEO_DAC_CTRL3_write_en4(data)                                          (0x00004000&((data)<<14))
#define TVE_VIDEO_DAC_CTRL3_write_en4_src(data)                                      ((0x00004000&(data))>>14)
#define TVE_VIDEO_DAC_CTRL3_get_write_en4(data)                                      ((0x00004000&(data))>>14)
#define TVE_VIDEO_DAC_CTRL3_caldiv_shift                                             (12)
#define TVE_VIDEO_DAC_CTRL3_caldiv_mask                                              (0x00003000)
#define TVE_VIDEO_DAC_CTRL3_caldiv(data)                                             (0x00003000&((data)<<12))
#define TVE_VIDEO_DAC_CTRL3_caldiv_src(data)                                         ((0x00003000&(data))>>12)
#define TVE_VIDEO_DAC_CTRL3_get_caldiv(data)                                         ((0x00003000&(data))>>12)
#define TVE_VIDEO_DAC_CTRL3_write_en3_shift                                          (8)
#define TVE_VIDEO_DAC_CTRL3_write_en3_mask                                           (0x00000100)
#define TVE_VIDEO_DAC_CTRL3_write_en3(data)                                          (0x00000100&((data)<<8))
#define TVE_VIDEO_DAC_CTRL3_write_en3_src(data)                                      ((0x00000100&(data))>>8)
#define TVE_VIDEO_DAC_CTRL3_get_write_en3(data)                                      ((0x00000100&(data))>>8)
#define TVE_VIDEO_DAC_CTRL3_div_regl_shift                                           (6)
#define TVE_VIDEO_DAC_CTRL3_div_regl_mask                                            (0x000000C0)
#define TVE_VIDEO_DAC_CTRL3_div_regl(data)                                           (0x000000C0&((data)<<6))
#define TVE_VIDEO_DAC_CTRL3_div_regl_src(data)                                       ((0x000000C0&(data))>>6)
#define TVE_VIDEO_DAC_CTRL3_get_div_regl(data)                                       ((0x000000C0&(data))>>6)
#define TVE_VIDEO_DAC_CTRL3_write_en2_shift                                          (5)
#define TVE_VIDEO_DAC_CTRL3_write_en2_mask                                           (0x00000020)
#define TVE_VIDEO_DAC_CTRL3_write_en2(data)                                          (0x00000020&((data)<<5))
#define TVE_VIDEO_DAC_CTRL3_write_en2_src(data)                                      ((0x00000020&(data))>>5)
#define TVE_VIDEO_DAC_CTRL3_get_write_en2(data)                                      ((0x00000020&(data))>>5)
#define TVE_VIDEO_DAC_CTRL3_ckmode_regl_shift                                        (3)
#define TVE_VIDEO_DAC_CTRL3_ckmode_regl_mask                                         (0x00000018)
#define TVE_VIDEO_DAC_CTRL3_ckmode_regl(data)                                        (0x00000018&((data)<<3))
#define TVE_VIDEO_DAC_CTRL3_ckmode_regl_src(data)                                    ((0x00000018&(data))>>3)
#define TVE_VIDEO_DAC_CTRL3_get_ckmode_regl(data)                                    ((0x00000018&(data))>>3)
#define TVE_VIDEO_DAC_CTRL3_write_en1_shift                                          (2)
#define TVE_VIDEO_DAC_CTRL3_write_en1_mask                                           (0x00000004)
#define TVE_VIDEO_DAC_CTRL3_write_en1(data)                                          (0x00000004&((data)<<2))
#define TVE_VIDEO_DAC_CTRL3_write_en1_src(data)                                      ((0x00000004&(data))>>2)
#define TVE_VIDEO_DAC_CTRL3_get_write_en1(data)                                      ((0x00000004&(data))>>2)
#define TVE_VIDEO_DAC_CTRL3_calen_regl_shift                                         (0)
#define TVE_VIDEO_DAC_CTRL3_calen_regl_mask                                          (0x00000003)
#define TVE_VIDEO_DAC_CTRL3_calen_regl(data)                                         (0x00000003&((data)<<0))
#define TVE_VIDEO_DAC_CTRL3_calen_regl_src(data)                                     ((0x00000003&(data))>>0)
#define TVE_VIDEO_DAC_CTRL3_get_calen_regl(data)                                     ((0x00000003&(data))>>0)


#define TVE_DAC_SEL                                                                  0x1801836c
#define TVE_DAC_SEL_reg_addr                                                         "0xB801836C"
#define TVE_DAC_SEL_reg                                                              0xB801836C
#define set_TVE_DAC_SEL_reg(data)   (*((volatile unsigned int*) TVE_DAC_SEL_reg)=data)
#define get_TVE_DAC_SEL_reg   (*((volatile unsigned int*) TVE_DAC_SEL_reg))
#define TVE_DAC_SEL_inst_adr                                                         "0x00DB"
#define TVE_DAC_SEL_inst                                                             0x00DB
#define TVE_DAC_SEL_write_en1_shift                                                  (2)
#define TVE_DAC_SEL_write_en1_mask                                                   (0x00000004)
#define TVE_DAC_SEL_write_en1(data)                                                  (0x00000004&((data)<<2))
#define TVE_DAC_SEL_write_en1_src(data)                                              ((0x00000004&(data))>>2)
#define TVE_DAC_SEL_get_write_en1(data)                                              ((0x00000004&(data))>>2)
#define TVE_DAC_SEL_dac0_sel_shift                                                   (0)
#define TVE_DAC_SEL_dac0_sel_mask                                                    (0x00000003)
#define TVE_DAC_SEL_dac0_sel(data)                                                   (0x00000003&((data)<<0))
#define TVE_DAC_SEL_dac0_sel_src(data)                                               ((0x00000003&(data))>>0)
#define TVE_DAC_SEL_get_dac0_sel(data)                                               ((0x00000003&(data))>>0)


#define TVE_DAC_MUX                                                                  0x18018208
#define TVE_DAC_MUX_reg_addr                                                         "0xB8018208"
#define TVE_DAC_MUX_reg                                                              0xB8018208
#define set_TVE_DAC_MUX_reg(data)   (*((volatile unsigned int*) TVE_DAC_MUX_reg)=data)
#define get_TVE_DAC_MUX_reg   (*((volatile unsigned int*) TVE_DAC_MUX_reg))
#define TVE_DAC_MUX_inst_adr                                                         "0x0082"
#define TVE_DAC_MUX_inst                                                             0x0082
#define TVE_DAC_MUX_write_en6_shift                                                  (15)
#define TVE_DAC_MUX_write_en6_mask                                                   (0x00008000)
#define TVE_DAC_MUX_write_en6(data)                                                  (0x00008000&((data)<<15))
#define TVE_DAC_MUX_write_en6_src(data)                                              ((0x00008000&(data))>>15)
#define TVE_DAC_MUX_get_write_en6(data)                                              ((0x00008000&(data))>>15)
#define TVE_DAC_MUX_up_ctrl_prog_shift                                               (13)
#define TVE_DAC_MUX_up_ctrl_prog_mask                                                (0x00006000)
#define TVE_DAC_MUX_up_ctrl_prog(data)                                               (0x00006000&((data)<<13))
#define TVE_DAC_MUX_up_ctrl_prog_src(data)                                           ((0x00006000&(data))>>13)
#define TVE_DAC_MUX_get_up_ctrl_prog(data)                                           ((0x00006000&(data))>>13)
#define TVE_DAC_MUX_write_en5_shift                                                  (12)
#define TVE_DAC_MUX_write_en5_mask                                                   (0x00001000)
#define TVE_DAC_MUX_write_en5(data)                                                  (0x00001000&((data)<<12))
#define TVE_DAC_MUX_write_en5_src(data)                                              ((0x00001000&(data))>>12)
#define TVE_DAC_MUX_get_write_en5(data)                                              ((0x00001000&(data))>>12)
#define TVE_DAC_MUX_up_ctrl_int0_shift                                               (10)
#define TVE_DAC_MUX_up_ctrl_int0_mask                                                (0x00000C00)
#define TVE_DAC_MUX_up_ctrl_int0(data)                                               (0x00000C00&((data)<<10))
#define TVE_DAC_MUX_up_ctrl_int0_src(data)                                           ((0x00000C00&(data))>>10)
#define TVE_DAC_MUX_get_up_ctrl_int0(data)                                           ((0x00000C00&(data))>>10)
#define TVE_DAC_MUX_write_en4_shift                                                  (9)
#define TVE_DAC_MUX_write_en4_mask                                                   (0x00000200)
#define TVE_DAC_MUX_write_en4(data)                                                  (0x00000200&((data)<<9))
#define TVE_DAC_MUX_write_en4_src(data)                                              ((0x00000200&(data))>>9)
#define TVE_DAC_MUX_get_write_en4(data)                                              ((0x00000200&(data))>>9)
#define TVE_DAC_MUX_up_ctrl_int1_shift                                               (7)
#define TVE_DAC_MUX_up_ctrl_int1_mask                                                (0x00000180)
#define TVE_DAC_MUX_up_ctrl_int1(data)                                               (0x00000180&((data)<<7))
#define TVE_DAC_MUX_up_ctrl_int1_src(data)                                           ((0x00000180&(data))>>7)
#define TVE_DAC_MUX_get_up_ctrl_int1(data)                                           ((0x00000180&(data))>>7)
#define TVE_DAC_MUX_write_en3_shift                                                  (6)
#define TVE_DAC_MUX_write_en3_mask                                                   (0x00000040)
#define TVE_DAC_MUX_write_en3(data)                                                  (0x00000040&((data)<<6))
#define TVE_DAC_MUX_write_en3_src(data)                                              ((0x00000040&(data))>>6)
#define TVE_DAC_MUX_get_write_en3(data)                                              ((0x00000040&(data))>>6)
#define TVE_DAC_MUX_dacmode_shift                                                    (4)
#define TVE_DAC_MUX_dacmode_mask                                                     (0x00000030)
#define TVE_DAC_MUX_dacmode(data)                                                    (0x00000030&((data)<<4))
#define TVE_DAC_MUX_dacmode_src(data)                                                ((0x00000030&(data))>>4)
#define TVE_DAC_MUX_get_dacmode(data)                                                ((0x00000030&(data))>>4)
#define TVE_DAC_MUX_write_en2_shift                                                  (3)
#define TVE_DAC_MUX_write_en2_mask                                                   (0x00000008)
#define TVE_DAC_MUX_write_en2(data)                                                  (0x00000008&((data)<<3))
#define TVE_DAC_MUX_write_en2_src(data)                                              ((0x00000008&(data))>>3)
#define TVE_DAC_MUX_get_write_en2(data)                                              ((0x00000008&(data))>>3)
#define TVE_DAC_MUX_swap23_shift                                                     (2)
#define TVE_DAC_MUX_swap23_mask                                                      (0x00000004)
#define TVE_DAC_MUX_swap23(data)                                                     (0x00000004&((data)<<2))
#define TVE_DAC_MUX_swap23_src(data)                                                 ((0x00000004&(data))>>2)
#define TVE_DAC_MUX_get_swap23(data)                                                 ((0x00000004&(data))>>2)
#define TVE_DAC_MUX_write_en1_shift                                                  (1)
#define TVE_DAC_MUX_write_en1_mask                                                   (0x00000002)
#define TVE_DAC_MUX_write_en1(data)                                                  (0x00000002&((data)<<1))
#define TVE_DAC_MUX_write_en1_src(data)                                              ((0x00000002&(data))>>1)
#define TVE_DAC_MUX_get_write_en1(data)                                              ((0x00000002&(data))>>1)
#define TVE_DAC_MUX_swap56_shift                                                     (0)
#define TVE_DAC_MUX_swap56_mask                                                      (0x00000001)
#define TVE_DAC_MUX_swap56(data)                                                     (0x00000001&((data)<<0))
#define TVE_DAC_MUX_swap56_src(data)                                                 ((0x00000001&(data))>>0)
#define TVE_DAC_MUX_get_swap56(data)                                                 ((0x00000001&(data))>>0)


#define TVE_CMP_DLY                                                                  0x1801820c
#define TVE_CMP_DLY_reg_addr                                                         "0xB801820C"
#define TVE_CMP_DLY_reg                                                              0xB801820C
#define set_TVE_CMP_DLY_reg(data)   (*((volatile unsigned int*) TVE_CMP_DLY_reg)=data)
#define get_TVE_CMP_DLY_reg   (*((volatile unsigned int*) TVE_CMP_DLY_reg))
#define TVE_CMP_DLY_inst_adr                                                         "0x0083"
#define TVE_CMP_DLY_inst                                                             0x0083
#define TVE_CMP_DLY_write_en3_shift                                                  (8)
#define TVE_CMP_DLY_write_en3_mask                                                   (0x00000100)
#define TVE_CMP_DLY_write_en3(data)                                                  (0x00000100&((data)<<8))
#define TVE_CMP_DLY_write_en3_src(data)                                              ((0x00000100&(data))>>8)
#define TVE_CMP_DLY_get_write_en3(data)                                              ((0x00000100&(data))>>8)
#define TVE_CMP_DLY_ygdelay_shift                                                    (6)
#define TVE_CMP_DLY_ygdelay_mask                                                     (0x000000C0)
#define TVE_CMP_DLY_ygdelay(data)                                                    (0x000000C0&((data)<<6))
#define TVE_CMP_DLY_ygdelay_src(data)                                                ((0x000000C0&(data))>>6)
#define TVE_CMP_DLY_get_ygdelay(data)                                                ((0x000000C0&(data))>>6)
#define TVE_CMP_DLY_write_en2_shift                                                  (5)
#define TVE_CMP_DLY_write_en2_mask                                                   (0x00000020)
#define TVE_CMP_DLY_write_en2(data)                                                  (0x00000020&((data)<<5))
#define TVE_CMP_DLY_write_en2_src(data)                                              ((0x00000020&(data))>>5)
#define TVE_CMP_DLY_get_write_en2(data)                                              ((0x00000020&(data))>>5)
#define TVE_CMP_DLY_bdelay_shift                                                     (3)
#define TVE_CMP_DLY_bdelay_mask                                                      (0x00000018)
#define TVE_CMP_DLY_bdelay(data)                                                     (0x00000018&((data)<<3))
#define TVE_CMP_DLY_bdelay_src(data)                                                 ((0x00000018&(data))>>3)
#define TVE_CMP_DLY_get_bdelay(data)                                                 ((0x00000018&(data))>>3)
#define TVE_CMP_DLY_write_en1_shift                                                  (2)
#define TVE_CMP_DLY_write_en1_mask                                                   (0x00000004)
#define TVE_CMP_DLY_write_en1(data)                                                  (0x00000004&((data)<<2))
#define TVE_CMP_DLY_write_en1_src(data)                                              ((0x00000004&(data))>>2)
#define TVE_CMP_DLY_get_write_en1(data)                                              ((0x00000004&(data))>>2)
#define TVE_CMP_DLY_rdelay_shift                                                     (0)
#define TVE_CMP_DLY_rdelay_mask                                                      (0x00000003)
#define TVE_CMP_DLY_rdelay(data)                                                     (0x00000003&((data)<<0))
#define TVE_CMP_DLY_rdelay_src(data)                                                 ((0x00000003&(data))>>0)
#define TVE_CMP_DLY_get_rdelay(data)                                                 ((0x00000003&(data))>>0)


#define TVE_DAC_MISC                                                                 0x18018210
#define TVE_DAC_MISC_reg_addr                                                        "0xB8018210"
#define TVE_DAC_MISC_reg                                                             0xB8018210
#define set_TVE_DAC_MISC_reg(data)   (*((volatile unsigned int*) TVE_DAC_MISC_reg)=data)
#define get_TVE_DAC_MISC_reg   (*((volatile unsigned int*) TVE_DAC_MISC_reg))
#define TVE_DAC_MISC_inst_adr                                                        "0x0084"
#define TVE_DAC_MISC_inst                                                            0x0084
#define TVE_DAC_MISC_write_en4_shift                                                 (25)
#define TVE_DAC_MISC_write_en4_mask                                                  (0x02000000)
#define TVE_DAC_MISC_write_en4(data)                                                 (0x02000000&((data)<<25))
#define TVE_DAC_MISC_write_en4_src(data)                                             ((0x02000000&(data))>>25)
#define TVE_DAC_MISC_get_write_en4(data)                                             ((0x02000000&(data))>>25)
#define TVE_DAC_MISC_out_control123_shift                                            (22)
#define TVE_DAC_MISC_out_control123_mask                                             (0x01C00000)
#define TVE_DAC_MISC_out_control123(data)                                            (0x01C00000&((data)<<22))
#define TVE_DAC_MISC_out_control123_src(data)                                        ((0x01C00000&(data))>>22)
#define TVE_DAC_MISC_get_out_control123(data)                                        ((0x01C00000&(data))>>22)
#define TVE_DAC_MISC_write_en3_shift                                                 (21)
#define TVE_DAC_MISC_write_en3_mask                                                  (0x00200000)
#define TVE_DAC_MISC_write_en3(data)                                                 (0x00200000&((data)<<21))
#define TVE_DAC_MISC_write_en3_src(data)                                             ((0x00200000&(data))>>21)
#define TVE_DAC_MISC_get_write_en3(data)                                             ((0x00200000&(data))>>21)
#define TVE_DAC_MISC_neg_out_shift                                                   (15)
#define TVE_DAC_MISC_neg_out_mask                                                    (0x001F8000)
#define TVE_DAC_MISC_neg_out(data)                                                   (0x001F8000&((data)<<15))
#define TVE_DAC_MISC_neg_out_src(data)                                               ((0x001F8000&(data))>>15)
#define TVE_DAC_MISC_get_neg_out(data)                                               ((0x001F8000&(data))>>15)
#define TVE_DAC_MISC_write_en2_shift                                                 (14)
#define TVE_DAC_MISC_write_en2_mask                                                  (0x00004000)
#define TVE_DAC_MISC_write_en2(data)                                                 (0x00004000&((data)<<14))
#define TVE_DAC_MISC_write_en2_src(data)                                             ((0x00004000&(data))>>14)
#define TVE_DAC_MISC_get_write_en2(data)                                             ((0x00004000&(data))>>14)
#define TVE_DAC_MISC_out_control_shift                                               (13)
#define TVE_DAC_MISC_out_control_mask                                                (0x00002000)
#define TVE_DAC_MISC_out_control(data)                                               (0x00002000&((data)<<13))
#define TVE_DAC_MISC_out_control_src(data)                                           ((0x00002000&(data))>>13)
#define TVE_DAC_MISC_get_out_control(data)                                           ((0x00002000&(data))>>13)
#define TVE_DAC_MISC_write_en1_shift                                                 (12)
#define TVE_DAC_MISC_write_en1_mask                                                  (0x00001000)
#define TVE_DAC_MISC_write_en1(data)                                                 (0x00001000&((data)<<12))
#define TVE_DAC_MISC_write_en1_src(data)                                             ((0x00001000&(data))>>12)
#define TVE_DAC_MISC_get_write_en1(data)                                             ((0x00001000&(data))>>12)
#define TVE_DAC_MISC_dac_value_shift                                                 (2)
#define TVE_DAC_MISC_dac_value_mask                                                  (0x00000FFC)
#define TVE_DAC_MISC_dac_value(data)                                                 (0x00000FFC&((data)<<2))
#define TVE_DAC_MISC_dac_value_src(data)                                             ((0x00000FFC&(data))>>2)
#define TVE_DAC_MISC_get_dac_value(data)                                             ((0x00000FFC&(data))>>2)


#define TVE_DAC_MISC1                                                                0x18018224
#define TVE_DAC_MISC1_reg_addr                                                       "0xB8018224"
#define TVE_DAC_MISC1_reg                                                            0xB8018224
#define set_TVE_DAC_MISC1_reg(data)   (*((volatile unsigned int*) TVE_DAC_MISC1_reg)=data)
#define get_TVE_DAC_MISC1_reg   (*((volatile unsigned int*) TVE_DAC_MISC1_reg))
#define TVE_DAC_MISC1_inst_adr                                                       "0x0089"
#define TVE_DAC_MISC1_inst                                                           0x0089
#define TVE_DAC_MISC1_dac_value3_shift                                               (20)
#define TVE_DAC_MISC1_dac_value3_mask                                                (0x3FF00000)
#define TVE_DAC_MISC1_dac_value3(data)                                               (0x3FF00000&((data)<<20))
#define TVE_DAC_MISC1_dac_value3_src(data)                                           ((0x3FF00000&(data))>>20)
#define TVE_DAC_MISC1_get_dac_value3(data)                                           ((0x3FF00000&(data))>>20)
#define TVE_DAC_MISC1_dac_value2_shift                                               (10)
#define TVE_DAC_MISC1_dac_value2_mask                                                (0x000FFC00)
#define TVE_DAC_MISC1_dac_value2(data)                                               (0x000FFC00&((data)<<10))
#define TVE_DAC_MISC1_dac_value2_src(data)                                           ((0x000FFC00&(data))>>10)
#define TVE_DAC_MISC1_get_dac_value2(data)                                           ((0x000FFC00&(data))>>10)
#define TVE_DAC_MISC1_dac_value1_shift                                               (0)
#define TVE_DAC_MISC1_dac_value1_mask                                                (0x000003FF)
#define TVE_DAC_MISC1_dac_value1(data)                                               (0x000003FF&((data)<<0))
#define TVE_DAC_MISC1_dac_value1_src(data)                                           ((0x000003FF&(data))>>0)
#define TVE_DAC_MISC1_get_dac_value1(data)                                           ((0x000003FF&(data))>>0)


#define TVE_DBG                                                                      0x18018214
#define TVE_DBG_reg_addr                                                             "0xB8018214"
#define TVE_DBG_reg                                                                  0xB8018214
#define set_TVE_DBG_reg(data)   (*((volatile unsigned int*) TVE_DBG_reg)=data)
#define get_TVE_DBG_reg   (*((volatile unsigned int*) TVE_DBG_reg))
#define TVE_DBG_inst_adr                                                             "0x0085"
#define TVE_DBG_inst                                                                 0x0085
#define TVE_DBG_write_en3_shift                                                      (11)
#define TVE_DBG_write_en3_mask                                                       (0x00000800)
#define TVE_DBG_write_en3(data)                                                      (0x00000800&((data)<<11))
#define TVE_DBG_write_en3_src(data)                                                  ((0x00000800&(data))>>11)
#define TVE_DBG_get_write_en3(data)                                                  ((0x00000800&(data))>>11)
#define TVE_DBG_sel1_shift                                                           (7)
#define TVE_DBG_sel1_mask                                                            (0x00000780)
#define TVE_DBG_sel1(data)                                                           (0x00000780&((data)<<7))
#define TVE_DBG_sel1_src(data)                                                       ((0x00000780&(data))>>7)
#define TVE_DBG_get_sel1(data)                                                       ((0x00000780&(data))>>7)
#define TVE_DBG_write_en2_shift                                                      (6)
#define TVE_DBG_write_en2_mask                                                       (0x00000040)
#define TVE_DBG_write_en2(data)                                                      (0x00000040&((data)<<6))
#define TVE_DBG_write_en2_src(data)                                                  ((0x00000040&(data))>>6)
#define TVE_DBG_get_write_en2(data)                                                  ((0x00000040&(data))>>6)
#define TVE_DBG_sel0_shift                                                           (2)
#define TVE_DBG_sel0_mask                                                            (0x0000003C)
#define TVE_DBG_sel0(data)                                                           (0x0000003C&((data)<<2))
#define TVE_DBG_sel0_src(data)                                                       ((0x0000003C&(data))>>2)
#define TVE_DBG_get_sel0(data)                                                       ((0x0000003C&(data))>>2)
#define TVE_DBG_write_en1_shift                                                      (1)
#define TVE_DBG_write_en1_mask                                                       (0x00000002)
#define TVE_DBG_write_en1(data)                                                      (0x00000002&((data)<<1))
#define TVE_DBG_write_en1_src(data)                                                  ((0x00000002&(data))>>1)
#define TVE_DBG_get_write_en1(data)                                                  ((0x00000002&(data))>>1)
#define TVE_DBG_enable_shift                                                         (0)
#define TVE_DBG_enable_mask                                                          (0x00000001)
#define TVE_DBG_enable(data)                                                         (0x00000001&((data)<<0))
#define TVE_DBG_enable_src(data)                                                     ((0x00000001&(data))>>0)
#define TVE_DBG_get_enable(data)                                                     ((0x00000001&(data))>>0)


#define TVE_DUMMY_0                                                                  0x18018300
#define TVE_DUMMY_1                                                                  0x18018304
#define TVE_DUMMY_0_reg_addr                                                         "0xB8018300"
#define TVE_DUMMY_1_reg_addr                                                         "0xB8018304"
#define TVE_DUMMY_0_reg                                                              0xB8018300
#define TVE_DUMMY_1_reg                                                              0xB8018304
#define set_TVE_DUMMY_0_reg(data)   (*((volatile unsigned int*) TVE_DUMMY_0_reg)=data)
#define set_TVE_DUMMY_1_reg(data)   (*((volatile unsigned int*) TVE_DUMMY_1_reg)=data)
#define get_TVE_DUMMY_0_reg   (*((volatile unsigned int*) TVE_DUMMY_0_reg))
#define get_TVE_DUMMY_1_reg   (*((volatile unsigned int*) TVE_DUMMY_1_reg))
#define TVE_DUMMY_0_inst_adr                                                         "0x00C0"
#define TVE_DUMMY_1_inst_adr                                                         "0x00C1"
#define TVE_DUMMY_0_inst                                                             0x00C0
#define TVE_DUMMY_1_inst                                                             0x00C1
#define TVE_DUMMY_dummy_shift                                                        (0)
#define TVE_DUMMY_dummy_mask                                                         (0xFFFFFFFF)
#define TVE_DUMMY_dummy(data)                                                        (0xFFFFFFFF&((data)<<0))
#define TVE_DUMMY_dummy_src(data)                                                    ((0xFFFFFFFF&(data))>>0)
#define TVE_DUMMY_get_dummy(data)                                                    ((0xFFFFFFFF&(data))>>0)


#define TVE_DAC_TEST                                                                 0x18018344
#define TVE_DAC_TEST_reg_addr                                                        "0xB8018344"
#define TVE_DAC_TEST_reg                                                             0xB8018344
#define set_TVE_DAC_TEST_reg(data)   (*((volatile unsigned int*) TVE_DAC_TEST_reg)=data)
#define get_TVE_DAC_TEST_reg   (*((volatile unsigned int*) TVE_DAC_TEST_reg))
#define TVE_DAC_TEST_inst_adr                                                        "0x00D1"
#define TVE_DAC_TEST_inst                                                            0x00D1
#define TVE_DAC_TEST_aio_dac_en_shift                                                (2)
#define TVE_DAC_TEST_aio_dac_en_mask                                                 (0x00000004)
#define TVE_DAC_TEST_aio_dac_en(data)                                                (0x00000004&((data)<<2))
#define TVE_DAC_TEST_aio_dac_en_src(data)                                            ((0x00000004&(data))>>2)
#define TVE_DAC_TEST_get_aio_dac_en(data)                                            ((0x00000004&(data))>>2)
#define TVE_DAC_TEST_dac1_en_shift                                                   (1)
#define TVE_DAC_TEST_dac1_en_mask                                                    (0x00000002)
#define TVE_DAC_TEST_dac1_en(data)                                                   (0x00000002&((data)<<1))
#define TVE_DAC_TEST_dac1_en_src(data)                                               ((0x00000002&(data))>>1)
#define TVE_DAC_TEST_get_dac1_en(data)                                               ((0x00000002&(data))>>1)
#define TVE_DAC_TEST_dac0_en_shift                                                   (0)
#define TVE_DAC_TEST_dac0_en_mask                                                    (0x00000001)
#define TVE_DAC_TEST_dac0_en(data)                                                   (0x00000001&((data)<<0))
#define TVE_DAC_TEST_dac0_en_src(data)                                               ((0x00000001&(data))>>0)
#define TVE_DAC_TEST_get_dac0_en(data)                                               ((0x00000001&(data))>>0)


#define TVE_INTVBI_I                                                                 0x18018348
#define TVE_INTVBI_I_reg_addr                                                        "0xB8018348"
#define TVE_INTVBI_I_reg                                                             0xB8018348
#define set_TVE_INTVBI_I_reg(data)   (*((volatile unsigned int*) TVE_INTVBI_I_reg)=data)
#define get_TVE_INTVBI_I_reg   (*((volatile unsigned int*) TVE_INTVBI_I_reg))
#define TVE_INTVBI_I_inst_adr                                                        "0x00D2"
#define TVE_INTVBI_I_inst                                                            0x00D2
#define TVE_INTVBI_I_write_en2_shift                                                 (25)
#define TVE_INTVBI_I_write_en2_mask                                                  (0x02000000)
#define TVE_INTVBI_I_write_en2(data)                                                 (0x02000000&((data)<<25))
#define TVE_INTVBI_I_write_en2_src(data)                                             ((0x02000000&(data))>>25)
#define TVE_INTVBI_I_get_write_en2(data)                                             ((0x02000000&(data))>>25)
#define TVE_INTVBI_I_int_vpos_shift                                                  (14)
#define TVE_INTVBI_I_int_vpos_mask                                                   (0x01FFC000)
#define TVE_INTVBI_I_int_vpos(data)                                                  (0x01FFC000&((data)<<14))
#define TVE_INTVBI_I_int_vpos_src(data)                                              ((0x01FFC000&(data))>>14)
#define TVE_INTVBI_I_get_int_vpos(data)                                              ((0x01FFC000&(data))>>14)
#define TVE_INTVBI_I_write_en1_shift                                                 (13)
#define TVE_INTVBI_I_write_en1_mask                                                  (0x00002000)
#define TVE_INTVBI_I_write_en1(data)                                                 (0x00002000&((data)<<13))
#define TVE_INTVBI_I_write_en1_src(data)                                             ((0x00002000&(data))>>13)
#define TVE_INTVBI_I_get_write_en1(data)                                             ((0x00002000&(data))>>13)
#define TVE_INTVBI_I_int_hpos_shift                                                  (0)
#define TVE_INTVBI_I_int_hpos_mask                                                   (0x00001FFF)
#define TVE_INTVBI_I_int_hpos(data)                                                  (0x00001FFF&((data)<<0))
#define TVE_INTVBI_I_int_hpos_src(data)                                              ((0x00001FFF&(data))>>0)
#define TVE_INTVBI_I_get_int_hpos(data)                                              ((0x00001FFF&(data))>>0)


#define TVE_INTVBI_P1                                                                0x1801834c
#define TVE_INTVBI_P1_reg_addr                                                       "0xB801834C"
#define TVE_INTVBI_P1_reg                                                            0xB801834C
#define set_TVE_INTVBI_P1_reg(data)   (*((volatile unsigned int*) TVE_INTVBI_P1_reg)=data)
#define get_TVE_INTVBI_P1_reg   (*((volatile unsigned int*) TVE_INTVBI_P1_reg))
#define TVE_INTVBI_P1_inst_adr                                                       "0x00D3"
#define TVE_INTVBI_P1_inst                                                           0x00D3
#define TVE_INTVBI_P1_write_en2_shift                                                (25)
#define TVE_INTVBI_P1_write_en2_mask                                                 (0x02000000)
#define TVE_INTVBI_P1_write_en2(data)                                                (0x02000000&((data)<<25))
#define TVE_INTVBI_P1_write_en2_src(data)                                            ((0x02000000&(data))>>25)
#define TVE_INTVBI_P1_get_write_en2(data)                                            ((0x02000000&(data))>>25)
#define TVE_INTVBI_P1_int_vpos_shift                                                 (14)
#define TVE_INTVBI_P1_int_vpos_mask                                                  (0x01FFC000)
#define TVE_INTVBI_P1_int_vpos(data)                                                 (0x01FFC000&((data)<<14))
#define TVE_INTVBI_P1_int_vpos_src(data)                                             ((0x01FFC000&(data))>>14)
#define TVE_INTVBI_P1_get_int_vpos(data)                                             ((0x01FFC000&(data))>>14)
#define TVE_INTVBI_P1_write_en1_shift                                                (13)
#define TVE_INTVBI_P1_write_en1_mask                                                 (0x00002000)
#define TVE_INTVBI_P1_write_en1(data)                                                (0x00002000&((data)<<13))
#define TVE_INTVBI_P1_write_en1_src(data)                                            ((0x00002000&(data))>>13)
#define TVE_INTVBI_P1_get_write_en1(data)                                            ((0x00002000&(data))>>13)
#define TVE_INTVBI_P1_int_hpos_shift                                                 (0)
#define TVE_INTVBI_P1_int_hpos_mask                                                  (0x00001FFF)
#define TVE_INTVBI_P1_int_hpos(data)                                                 (0x00001FFF&((data)<<0))
#define TVE_INTVBI_P1_int_hpos_src(data)                                             ((0x00001FFF&(data))>>0)
#define TVE_INTVBI_P1_get_int_hpos(data)                                             ((0x00001FFF&(data))>>0)


#define TVE_INTVBI_P2                                                                0x18018370
#define TVE_INTVBI_P2_reg_addr                                                       "0xB8018370"
#define TVE_INTVBI_P2_reg                                                            0xB8018370
#define set_TVE_INTVBI_P2_reg(data)   (*((volatile unsigned int*) TVE_INTVBI_P2_reg)=data)
#define get_TVE_INTVBI_P2_reg   (*((volatile unsigned int*) TVE_INTVBI_P2_reg))
#define TVE_INTVBI_P2_inst_adr                                                       "0x00DC"
#define TVE_INTVBI_P2_inst                                                           0x00DC
#define TVE_INTVBI_P2_write_en2_shift                                                (25)
#define TVE_INTVBI_P2_write_en2_mask                                                 (0x02000000)
#define TVE_INTVBI_P2_write_en2(data)                                                (0x02000000&((data)<<25))
#define TVE_INTVBI_P2_write_en2_src(data)                                            ((0x02000000&(data))>>25)
#define TVE_INTVBI_P2_get_write_en2(data)                                            ((0x02000000&(data))>>25)
#define TVE_INTVBI_P2_int_vpos_shift                                                 (14)
#define TVE_INTVBI_P2_int_vpos_mask                                                  (0x01FFC000)
#define TVE_INTVBI_P2_int_vpos(data)                                                 (0x01FFC000&((data)<<14))
#define TVE_INTVBI_P2_int_vpos_src(data)                                             ((0x01FFC000&(data))>>14)
#define TVE_INTVBI_P2_get_int_vpos(data)                                             ((0x01FFC000&(data))>>14)
#define TVE_INTVBI_P2_write_en1_shift                                                (13)
#define TVE_INTVBI_P2_write_en1_mask                                                 (0x00002000)
#define TVE_INTVBI_P2_write_en1(data)                                                (0x00002000&((data)<<13))
#define TVE_INTVBI_P2_write_en1_src(data)                                            ((0x00002000&(data))>>13)
#define TVE_INTVBI_P2_get_write_en1(data)                                            ((0x00002000&(data))>>13)
#define TVE_INTVBI_P2_int_hpos_shift                                                 (0)
#define TVE_INTVBI_P2_int_hpos_mask                                                  (0x00001FFF)
#define TVE_INTVBI_P2_int_hpos(data)                                                 (0x00001FFF&((data)<<0))
#define TVE_INTVBI_P2_int_hpos_src(data)                                             ((0x00001FFF&(data))>>0)
#define TVE_INTVBI_P2_get_int_hpos(data)                                             ((0x00001FFF&(data))>>0)


#define TVE_INTVBI_H1                                                                0x18018374
#define TVE_INTVBI_H1_reg_addr                                                       "0xB8018374"
#define TVE_INTVBI_H1_reg                                                            0xB8018374
#define set_TVE_INTVBI_H1_reg(data)   (*((volatile unsigned int*) TVE_INTVBI_H1_reg)=data)
#define get_TVE_INTVBI_H1_reg   (*((volatile unsigned int*) TVE_INTVBI_H1_reg))
#define TVE_INTVBI_H1_inst_adr                                                       "0x00DD"
#define TVE_INTVBI_H1_inst                                                           0x00DD
#define TVE_INTVBI_H1_write_en2_shift                                                (25)
#define TVE_INTVBI_H1_write_en2_mask                                                 (0x02000000)
#define TVE_INTVBI_H1_write_en2(data)                                                (0x02000000&((data)<<25))
#define TVE_INTVBI_H1_write_en2_src(data)                                            ((0x02000000&(data))>>25)
#define TVE_INTVBI_H1_get_write_en2(data)                                            ((0x02000000&(data))>>25)
#define TVE_INTVBI_H1_int_vpos_shift                                                 (14)
#define TVE_INTVBI_H1_int_vpos_mask                                                  (0x01FFC000)
#define TVE_INTVBI_H1_int_vpos(data)                                                 (0x01FFC000&((data)<<14))
#define TVE_INTVBI_H1_int_vpos_src(data)                                             ((0x01FFC000&(data))>>14)
#define TVE_INTVBI_H1_get_int_vpos(data)                                             ((0x01FFC000&(data))>>14)
#define TVE_INTVBI_H1_write_en1_shift                                                (13)
#define TVE_INTVBI_H1_write_en1_mask                                                 (0x00002000)
#define TVE_INTVBI_H1_write_en1(data)                                                (0x00002000&((data)<<13))
#define TVE_INTVBI_H1_write_en1_src(data)                                            ((0x00002000&(data))>>13)
#define TVE_INTVBI_H1_get_write_en1(data)                                            ((0x00002000&(data))>>13)
#define TVE_INTVBI_H1_int_hpos_shift                                                 (0)
#define TVE_INTVBI_H1_int_hpos_mask                                                  (0x00001FFF)
#define TVE_INTVBI_H1_int_hpos(data)                                                 (0x00001FFF&((data)<<0))
#define TVE_INTVBI_H1_int_hpos_src(data)                                             ((0x00001FFF&(data))>>0)
#define TVE_INTVBI_H1_get_int_hpos(data)                                             ((0x00001FFF&(data))>>0)


#define TVE_INTVBI_H2                                                                0x18018378
#define TVE_INTVBI_H2_reg_addr                                                       "0xB8018378"
#define TVE_INTVBI_H2_reg                                                            0xB8018378
#define set_TVE_INTVBI_H2_reg(data)   (*((volatile unsigned int*) TVE_INTVBI_H2_reg)=data)
#define get_TVE_INTVBI_H2_reg   (*((volatile unsigned int*) TVE_INTVBI_H2_reg))
#define TVE_INTVBI_H2_inst_adr                                                       "0x00DE"
#define TVE_INTVBI_H2_inst                                                           0x00DE
#define TVE_INTVBI_H2_write_en2_shift                                                (25)
#define TVE_INTVBI_H2_write_en2_mask                                                 (0x02000000)
#define TVE_INTVBI_H2_write_en2(data)                                                (0x02000000&((data)<<25))
#define TVE_INTVBI_H2_write_en2_src(data)                                            ((0x02000000&(data))>>25)
#define TVE_INTVBI_H2_get_write_en2(data)                                            ((0x02000000&(data))>>25)
#define TVE_INTVBI_H2_int_vpos_shift                                                 (14)
#define TVE_INTVBI_H2_int_vpos_mask                                                  (0x01FFC000)
#define TVE_INTVBI_H2_int_vpos(data)                                                 (0x01FFC000&((data)<<14))
#define TVE_INTVBI_H2_int_vpos_src(data)                                             ((0x01FFC000&(data))>>14)
#define TVE_INTVBI_H2_get_int_vpos(data)                                             ((0x01FFC000&(data))>>14)
#define TVE_INTVBI_H2_write_en1_shift                                                (13)
#define TVE_INTVBI_H2_write_en1_mask                                                 (0x00002000)
#define TVE_INTVBI_H2_write_en1(data)                                                (0x00002000&((data)<<13))
#define TVE_INTVBI_H2_write_en1_src(data)                                            ((0x00002000&(data))>>13)
#define TVE_INTVBI_H2_get_write_en1(data)                                            ((0x00002000&(data))>>13)
#define TVE_INTVBI_H2_int_hpos_shift                                                 (0)
#define TVE_INTVBI_H2_int_hpos_mask                                                  (0x00001FFF)
#define TVE_INTVBI_H2_int_hpos(data)                                                 (0x00001FFF&((data)<<0))
#define TVE_INTVBI_H2_int_hpos_src(data)                                             ((0x00001FFF&(data))>>0)
#define TVE_INTVBI_H2_get_int_hpos(data)                                             ((0x00001FFF&(data))>>0)


#define TVE_DAC1_FIR_1                                                               0x1801837c
#define TVE_DAC1_FIR_1_reg_addr                                                      "0xB801837C"
#define TVE_DAC1_FIR_1_reg                                                           0xB801837C
#define set_TVE_DAC1_FIR_1_reg(data)   (*((volatile unsigned int*) TVE_DAC1_FIR_1_reg)=data)
#define get_TVE_DAC1_FIR_1_reg   (*((volatile unsigned int*) TVE_DAC1_FIR_1_reg))
#define TVE_DAC1_FIR_1_inst_adr                                                      "0x00DF"
#define TVE_DAC1_FIR_1_inst                                                          0x00DF
#define TVE_DAC1_FIR_1_c1_shift                                                      (16)
#define TVE_DAC1_FIR_1_c1_mask                                                       (0x3FFF0000)
#define TVE_DAC1_FIR_1_c1(data)                                                      (0x3FFF0000&((data)<<16))
#define TVE_DAC1_FIR_1_c1_src(data)                                                  ((0x3FFF0000&(data))>>16)
#define TVE_DAC1_FIR_1_get_c1(data)                                                  ((0x3FFF0000&(data))>>16)
#define TVE_DAC1_FIR_1_c0_shift                                                      (0)
#define TVE_DAC1_FIR_1_c0_mask                                                       (0x00003FFF)
#define TVE_DAC1_FIR_1_c0(data)                                                      (0x00003FFF&((data)<<0))
#define TVE_DAC1_FIR_1_c0_src(data)                                                  ((0x00003FFF&(data))>>0)
#define TVE_DAC1_FIR_1_get_c0(data)                                                  ((0x00003FFF&(data))>>0)


#define TVE_DAC1_FIR_2                                                               0x18018380
#define TVE_DAC1_FIR_2_reg_addr                                                      "0xB8018380"
#define TVE_DAC1_FIR_2_reg                                                           0xB8018380
#define set_TVE_DAC1_FIR_2_reg(data)   (*((volatile unsigned int*) TVE_DAC1_FIR_2_reg)=data)
#define get_TVE_DAC1_FIR_2_reg   (*((volatile unsigned int*) TVE_DAC1_FIR_2_reg))
#define TVE_DAC1_FIR_2_inst_adr                                                      "0x00E0"
#define TVE_DAC1_FIR_2_inst                                                          0x00E0
#define TVE_DAC1_FIR_2_c3_shift                                                      (16)
#define TVE_DAC1_FIR_2_c3_mask                                                       (0x3FFF0000)
#define TVE_DAC1_FIR_2_c3(data)                                                      (0x3FFF0000&((data)<<16))
#define TVE_DAC1_FIR_2_c3_src(data)                                                  ((0x3FFF0000&(data))>>16)
#define TVE_DAC1_FIR_2_get_c3(data)                                                  ((0x3FFF0000&(data))>>16)
#define TVE_DAC1_FIR_2_c2_shift                                                      (0)
#define TVE_DAC1_FIR_2_c2_mask                                                       (0x00003FFF)
#define TVE_DAC1_FIR_2_c2(data)                                                      (0x00003FFF&((data)<<0))
#define TVE_DAC1_FIR_2_c2_src(data)                                                  ((0x00003FFF&(data))>>0)
#define TVE_DAC1_FIR_2_get_c2(data)                                                  ((0x00003FFF&(data))>>0)


#define TVE_DAC2_FIR_1                                                               0x18018388
#define TVE_DAC2_FIR_1_reg_addr                                                      "0xB8018388"
#define TVE_DAC2_FIR_1_reg                                                           0xB8018388
#define set_TVE_DAC2_FIR_1_reg(data)   (*((volatile unsigned int*) TVE_DAC2_FIR_1_reg)=data)
#define get_TVE_DAC2_FIR_1_reg   (*((volatile unsigned int*) TVE_DAC2_FIR_1_reg))
#define TVE_DAC2_FIR_1_inst_adr                                                      "0x00E2"
#define TVE_DAC2_FIR_1_inst                                                          0x00E2
#define TVE_DAC2_FIR_1_c1_shift                                                      (16)
#define TVE_DAC2_FIR_1_c1_mask                                                       (0x3FFF0000)
#define TVE_DAC2_FIR_1_c1(data)                                                      (0x3FFF0000&((data)<<16))
#define TVE_DAC2_FIR_1_c1_src(data)                                                  ((0x3FFF0000&(data))>>16)
#define TVE_DAC2_FIR_1_get_c1(data)                                                  ((0x3FFF0000&(data))>>16)
#define TVE_DAC2_FIR_1_c0_shift                                                      (0)
#define TVE_DAC2_FIR_1_c0_mask                                                       (0x00003FFF)
#define TVE_DAC2_FIR_1_c0(data)                                                      (0x00003FFF&((data)<<0))
#define TVE_DAC2_FIR_1_c0_src(data)                                                  ((0x00003FFF&(data))>>0)
#define TVE_DAC2_FIR_1_get_c0(data)                                                  ((0x00003FFF&(data))>>0)


#define TVE_DAC2_FIR_2                                                               0x1801838c
#define TVE_DAC2_FIR_2_reg_addr                                                      "0xB801838C"
#define TVE_DAC2_FIR_2_reg                                                           0xB801838C
#define set_TVE_DAC2_FIR_2_reg(data)   (*((volatile unsigned int*) TVE_DAC2_FIR_2_reg)=data)
#define get_TVE_DAC2_FIR_2_reg   (*((volatile unsigned int*) TVE_DAC2_FIR_2_reg))
#define TVE_DAC2_FIR_2_inst_adr                                                      "0x00E3"
#define TVE_DAC2_FIR_2_inst                                                          0x00E3
#define TVE_DAC2_FIR_2_c3_shift                                                      (16)
#define TVE_DAC2_FIR_2_c3_mask                                                       (0x3FFF0000)
#define TVE_DAC2_FIR_2_c3(data)                                                      (0x3FFF0000&((data)<<16))
#define TVE_DAC2_FIR_2_c3_src(data)                                                  ((0x3FFF0000&(data))>>16)
#define TVE_DAC2_FIR_2_get_c3(data)                                                  ((0x3FFF0000&(data))>>16)
#define TVE_DAC2_FIR_2_c2_shift                                                      (0)
#define TVE_DAC2_FIR_2_c2_mask                                                       (0x00003FFF)
#define TVE_DAC2_FIR_2_c2(data)                                                      (0x00003FFF&((data)<<0))
#define TVE_DAC2_FIR_2_c2_src(data)                                                  ((0x00003FFF&(data))>>0)
#define TVE_DAC2_FIR_2_get_c2(data)                                                  ((0x00003FFF&(data))>>0)


#define TVE_DAC3_FIR_1                                                               0x18018390
#define TVE_DAC3_FIR_1_reg_addr                                                      "0xB8018390"
#define TVE_DAC3_FIR_1_reg                                                           0xB8018390
#define set_TVE_DAC3_FIR_1_reg(data)   (*((volatile unsigned int*) TVE_DAC3_FIR_1_reg)=data)
#define get_TVE_DAC3_FIR_1_reg   (*((volatile unsigned int*) TVE_DAC3_FIR_1_reg))
#define TVE_DAC3_FIR_1_inst_adr                                                      "0x00E4"
#define TVE_DAC3_FIR_1_inst                                                          0x00E4
#define TVE_DAC3_FIR_1_c1_shift                                                      (16)
#define TVE_DAC3_FIR_1_c1_mask                                                       (0x3FFF0000)
#define TVE_DAC3_FIR_1_c1(data)                                                      (0x3FFF0000&((data)<<16))
#define TVE_DAC3_FIR_1_c1_src(data)                                                  ((0x3FFF0000&(data))>>16)
#define TVE_DAC3_FIR_1_get_c1(data)                                                  ((0x3FFF0000&(data))>>16)
#define TVE_DAC3_FIR_1_c0_shift                                                      (0)
#define TVE_DAC3_FIR_1_c0_mask                                                       (0x00003FFF)
#define TVE_DAC3_FIR_1_c0(data)                                                      (0x00003FFF&((data)<<0))
#define TVE_DAC3_FIR_1_c0_src(data)                                                  ((0x00003FFF&(data))>>0)
#define TVE_DAC3_FIR_1_get_c0(data)                                                  ((0x00003FFF&(data))>>0)


#define TVE_DAC3_FIR_2                                                               0x18018394
#define TVE_DAC3_FIR_2_reg_addr                                                      "0xB8018394"
#define TVE_DAC3_FIR_2_reg                                                           0xB8018394
#define set_TVE_DAC3_FIR_2_reg(data)   (*((volatile unsigned int*) TVE_DAC3_FIR_2_reg)=data)
#define get_TVE_DAC3_FIR_2_reg   (*((volatile unsigned int*) TVE_DAC3_FIR_2_reg))
#define TVE_DAC3_FIR_2_inst_adr                                                      "0x00E5"
#define TVE_DAC3_FIR_2_inst                                                          0x00E5
#define TVE_DAC3_FIR_2_c3_shift                                                      (16)
#define TVE_DAC3_FIR_2_c3_mask                                                       (0x3FFF0000)
#define TVE_DAC3_FIR_2_c3(data)                                                      (0x3FFF0000&((data)<<16))
#define TVE_DAC3_FIR_2_c3_src(data)                                                  ((0x3FFF0000&(data))>>16)
#define TVE_DAC3_FIR_2_get_c3(data)                                                  ((0x3FFF0000&(data))>>16)
#define TVE_DAC3_FIR_2_c2_shift                                                      (0)
#define TVE_DAC3_FIR_2_c2_mask                                                       (0x00003FFF)
#define TVE_DAC3_FIR_2_c2(data)                                                      (0x00003FFF&((data)<<0))
#define TVE_DAC3_FIR_2_c2_src(data)                                                  ((0x00003FFF&(data))>>0)
#define TVE_DAC3_FIR_2_get_c2(data)                                                  ((0x00003FFF&(data))>>0)


#define TVE_DAC4_FIR_1                                                               0x18018398
#define TVE_DAC4_FIR_1_reg_addr                                                      "0xB8018398"
#define TVE_DAC4_FIR_1_reg                                                           0xB8018398
#define set_TVE_DAC4_FIR_1_reg(data)   (*((volatile unsigned int*) TVE_DAC4_FIR_1_reg)=data)
#define get_TVE_DAC4_FIR_1_reg   (*((volatile unsigned int*) TVE_DAC4_FIR_1_reg))
#define TVE_DAC4_FIR_1_inst_adr                                                      "0x00E6"
#define TVE_DAC4_FIR_1_inst                                                          0x00E6
#define TVE_DAC4_FIR_1_c1_shift                                                      (16)
#define TVE_DAC4_FIR_1_c1_mask                                                       (0x3FFF0000)
#define TVE_DAC4_FIR_1_c1(data)                                                      (0x3FFF0000&((data)<<16))
#define TVE_DAC4_FIR_1_c1_src(data)                                                  ((0x3FFF0000&(data))>>16)
#define TVE_DAC4_FIR_1_get_c1(data)                                                  ((0x3FFF0000&(data))>>16)
#define TVE_DAC4_FIR_1_c0_shift                                                      (0)
#define TVE_DAC4_FIR_1_c0_mask                                                       (0x00003FFF)
#define TVE_DAC4_FIR_1_c0(data)                                                      (0x00003FFF&((data)<<0))
#define TVE_DAC4_FIR_1_c0_src(data)                                                  ((0x00003FFF&(data))>>0)
#define TVE_DAC4_FIR_1_get_c0(data)                                                  ((0x00003FFF&(data))>>0)


#define TVE_DAC4_FIR_2                                                               0x1801839c
#define TVE_DAC4_FIR_2_reg_addr                                                      "0xB801839C"
#define TVE_DAC4_FIR_2_reg                                                           0xB801839C
#define set_TVE_DAC4_FIR_2_reg(data)   (*((volatile unsigned int*) TVE_DAC4_FIR_2_reg)=data)
#define get_TVE_DAC4_FIR_2_reg   (*((volatile unsigned int*) TVE_DAC4_FIR_2_reg))
#define TVE_DAC4_FIR_2_inst_adr                                                      "0x00E7"
#define TVE_DAC4_FIR_2_inst                                                          0x00E7
#define TVE_DAC4_FIR_2_c3_shift                                                      (16)
#define TVE_DAC4_FIR_2_c3_mask                                                       (0x3FFF0000)
#define TVE_DAC4_FIR_2_c3(data)                                                      (0x3FFF0000&((data)<<16))
#define TVE_DAC4_FIR_2_c3_src(data)                                                  ((0x3FFF0000&(data))>>16)
#define TVE_DAC4_FIR_2_get_c3(data)                                                  ((0x3FFF0000&(data))>>16)
#define TVE_DAC4_FIR_2_c2_shift                                                      (0)
#define TVE_DAC4_FIR_2_c2_mask                                                       (0x00003FFF)
#define TVE_DAC4_FIR_2_c2(data)                                                      (0x00003FFF&((data)<<0))
#define TVE_DAC4_FIR_2_c2_src(data)                                                  ((0x00003FFF&(data))>>0)
#define TVE_DAC4_FIR_2_get_c2(data)                                                  ((0x00003FFF&(data))>>0)


#define TVE_VDAC_CTR1                                                                0x180183A0
#define TVE_VDAC_CTR1_reg_addr                                                       "0xB80183A0"
#define TVE_VDAC_CTR1_reg                                                            0xB80183A0
#define set_TVE_VDAC_CTR1_reg(data)   (*((volatile unsigned int*) TVE_VDAC_CTR1_reg)=data)
#define get_TVE_VDAC_CTR1_reg   (*((volatile unsigned int*) TVE_VDAC_CTR1_reg))
#define TVE_VDAC_CTR1_inst_adr                                                       "0x00E8"
#define TVE_VDAC_CTR1_inst                                                           0x00E8
#define TVE_VDAC_CTR1_reg_vdac_dac_en_shift                                          (31)
#define TVE_VDAC_CTR1_reg_vdac_dac_en_mask                                           (0x80000000)
#define TVE_VDAC_CTR1_reg_vdac_dac_en(data)                                          (0x80000000&((data)<<31))
#define TVE_VDAC_CTR1_reg_vdac_dac_en_src(data)                                      ((0x80000000&(data))>>31)
#define TVE_VDAC_CTR1_get_reg_vdac_dac_en(data)                                      ((0x80000000&(data))>>31)
#define TVE_VDAC_CTR1_reg_vdac_powmbias_shift                                        (30)
#define TVE_VDAC_CTR1_reg_vdac_powmbias_mask                                         (0x40000000)
#define TVE_VDAC_CTR1_reg_vdac_powmbias(data)                                        (0x40000000&((data)<<30))
#define TVE_VDAC_CTR1_reg_vdac_powmbias_src(data)                                    ((0x40000000&(data))>>30)
#define TVE_VDAC_CTR1_get_reg_vdac_powmbias(data)                                    ((0x40000000&(data))>>30)
#define TVE_VDAC_CTR1_reg_vdac_mbias_envr_shift                                      (29)
#define TVE_VDAC_CTR1_reg_vdac_mbias_envr_mask                                       (0x20000000)
#define TVE_VDAC_CTR1_reg_vdac_mbias_envr(data)                                      (0x20000000&((data)<<29))
#define TVE_VDAC_CTR1_reg_vdac_mbias_envr_src(data)                                  ((0x20000000&(data))>>29)
#define TVE_VDAC_CTR1_get_reg_vdac_mbias_envr(data)                                  ((0x20000000&(data))>>29)
#define TVE_VDAC_CTR1_reg_vdac_mbias_vr15sel_shift                                   (27)
#define TVE_VDAC_CTR1_reg_vdac_mbias_vr15sel_mask                                    (0x18000000)
#define TVE_VDAC_CTR1_reg_vdac_mbias_vr15sel(data)                                   (0x18000000&((data)<<27))
#define TVE_VDAC_CTR1_reg_vdac_mbias_vr15sel_src(data)                               ((0x18000000&(data))>>27)
#define TVE_VDAC_CTR1_get_reg_vdac_mbias_vr15sel(data)                               ((0x18000000&(data))>>27)
#define TVE_VDAC_CTR1_reg_vdac_bg_rbg2_shift                                         (25)
#define TVE_VDAC_CTR1_reg_vdac_bg_rbg2_mask                                          (0x06000000)
#define TVE_VDAC_CTR1_reg_vdac_bg_rbg2(data)                                         (0x06000000&((data)<<25))
#define TVE_VDAC_CTR1_reg_vdac_bg_rbg2_src(data)                                     ((0x06000000&(data))>>25)
#define TVE_VDAC_CTR1_get_reg_vdac_bg_rbg2(data)                                     ((0x06000000&(data))>>25)
#define TVE_VDAC_CTR1_reg_vdac_bg_envbgup_shift                                      (24)
#define TVE_VDAC_CTR1_reg_vdac_bg_envbgup_mask                                       (0x01000000)
#define TVE_VDAC_CTR1_reg_vdac_bg_envbgup(data)                                      (0x01000000&((data)<<24))
#define TVE_VDAC_CTR1_reg_vdac_bg_envbgup_src(data)                                  ((0x01000000&(data))>>24)
#define TVE_VDAC_CTR1_get_reg_vdac_bg_envbgup(data)                                  ((0x01000000&(data))>>24)
#define TVE_VDAC_CTR1_reg_vdac_bg_rbg_shift                                          (21)
#define TVE_VDAC_CTR1_reg_vdac_bg_rbg_mask                                           (0x00E00000)
#define TVE_VDAC_CTR1_reg_vdac_bg_rbg(data)                                          (0x00E00000&((data)<<21))
#define TVE_VDAC_CTR1_reg_vdac_bg_rbg_src(data)                                      ((0x00E00000&(data))>>21)
#define TVE_VDAC_CTR1_get_reg_vdac_bg_rbg(data)                                      ((0x00E00000&(data))>>21)
#define TVE_VDAC_CTR1_reg_vdac_dac_vref_adj_shift                                    (19)
#define TVE_VDAC_CTR1_reg_vdac_dac_vref_adj_mask                                     (0x00180000)
#define TVE_VDAC_CTR1_reg_vdac_dac_vref_adj(data)                                    (0x00180000&((data)<<19))
#define TVE_VDAC_CTR1_reg_vdac_dac_vref_adj_src(data)                                ((0x00180000&(data))>>19)
#define TVE_VDAC_CTR1_get_reg_vdac_dac_vref_adj(data)                                ((0x00180000&(data))>>19)
#define TVE_VDAC_CTR1_reg_vdac_dac_res75_setup_shift                                 (14)
#define TVE_VDAC_CTR1_reg_vdac_dac_res75_setup_mask                                  (0x0007C000)
#define TVE_VDAC_CTR1_reg_vdac_dac_res75_setup(data)                                 (0x0007C000&((data)<<14))
#define TVE_VDAC_CTR1_reg_vdac_dac_res75_setup_src(data)                             ((0x0007C000&(data))>>14)
#define TVE_VDAC_CTR1_get_reg_vdac_dac_res75_setup(data)                             ((0x0007C000&(data))>>14)
#define TVE_VDAC_CTR1_reg_vdac_dac_clkedge_shift                                     (13)
#define TVE_VDAC_CTR1_reg_vdac_dac_clkedge_mask                                      (0x00002000)
#define TVE_VDAC_CTR1_reg_vdac_dac_clkedge(data)                                     (0x00002000&((data)<<13))
#define TVE_VDAC_CTR1_reg_vdac_dac_clkedge_src(data)                                 ((0x00002000&(data))>>13)
#define TVE_VDAC_CTR1_get_reg_vdac_dac_clkedge(data)                                 ((0x00002000&(data))>>13)
#define TVE_VDAC_CTR1_reg_vdac_dac_cur_shift                                         (9)
#define TVE_VDAC_CTR1_reg_vdac_dac_cur_mask                                          (0x00001E00)
#define TVE_VDAC_CTR1_reg_vdac_dac_cur(data)                                         (0x00001E00&((data)<<9))
#define TVE_VDAC_CTR1_reg_vdac_dac_cur_src(data)                                     ((0x00001E00&(data))>>9)
#define TVE_VDAC_CTR1_get_reg_vdac_dac_cur(data)                                     ((0x00001E00&(data))>>9)
#define TVE_VDAC_CTR1_reg_vdac_dac_cal75_en_shift                                    (8)
#define TVE_VDAC_CTR1_reg_vdac_dac_cal75_en_mask                                     (0x00000100)
#define TVE_VDAC_CTR1_reg_vdac_dac_cal75_en(data)                                    (0x00000100&((data)<<8))
#define TVE_VDAC_CTR1_reg_vdac_dac_cal75_en_src(data)                                ((0x00000100&(data))>>8)
#define TVE_VDAC_CTR1_get_reg_vdac_dac_cal75_en(data)                                ((0x00000100&(data))>>8)
#define TVE_VDAC_CTR1_reg_vdac_dac_draw_en_shift                                     (7)
#define TVE_VDAC_CTR1_reg_vdac_dac_draw_en_mask                                      (0x00000080)
#define TVE_VDAC_CTR1_reg_vdac_dac_draw_en(data)                                     (0x00000080&((data)<<7))
#define TVE_VDAC_CTR1_reg_vdac_dac_draw_en_src(data)                                 ((0x00000080&(data))>>7)
#define TVE_VDAC_CTR1_get_reg_vdac_dac_draw_en(data)                                 ((0x00000080&(data))>>7)
#define TVE_VDAC_CTR1_reg_vdac_dac_plugin_en_shift                                   (6)
#define TVE_VDAC_CTR1_reg_vdac_dac_plugin_en_mask                                    (0x00000040)
#define TVE_VDAC_CTR1_reg_vdac_dac_plugin_en(data)                                   (0x00000040&((data)<<6))
#define TVE_VDAC_CTR1_reg_vdac_dac_plugin_en_src(data)                               ((0x00000040&(data))>>6)
#define TVE_VDAC_CTR1_get_reg_vdac_dac_plugin_en(data)                               ((0x00000040&(data))>>6)
#define TVE_VDAC_CTR1_reg_vdac_dac_res75_en_shift                                    (5)
#define TVE_VDAC_CTR1_reg_vdac_dac_res75_en_mask                                     (0x00000020)
#define TVE_VDAC_CTR1_reg_vdac_dac_res75_en(data)                                    (0x00000020&((data)<<5))
#define TVE_VDAC_CTR1_reg_vdac_dac_res75_en_src(data)                                ((0x00000020&(data))>>5)
#define TVE_VDAC_CTR1_get_reg_vdac_dac_res75_en(data)                                ((0x00000020&(data))>>5)
#define TVE_VDAC_CTR1_reg_vdac_dac_res75_sel_shift                                   (4)
#define TVE_VDAC_CTR1_reg_vdac_dac_res75_sel_mask                                    (0x00000010)
#define TVE_VDAC_CTR1_reg_vdac_dac_res75_sel(data)                                   (0x00000010&((data)<<4))
#define TVE_VDAC_CTR1_reg_vdac_dac_res75_sel_src(data)                               ((0x00000010&(data))>>4)
#define TVE_VDAC_CTR1_get_reg_vdac_dac_res75_sel(data)                               ((0x00000010&(data))>>4)


#define TVE_VDAC_CTR2                                                                0x180183A4
#define TVE_VDAC_CTR2_reg_addr                                                       "0xB80183A4"
#define TVE_VDAC_CTR2_reg                                                            0xB80183A4
#define set_TVE_VDAC_CTR2_reg(data)   (*((volatile unsigned int*) TVE_VDAC_CTR2_reg)=data)
#define get_TVE_VDAC_CTR2_reg   (*((volatile unsigned int*) TVE_VDAC_CTR2_reg))
#define TVE_VDAC_CTR2_inst_adr                                                       "0x00E9"
#define TVE_VDAC_CTR2_inst                                                           0x00E9
#define TVE_VDAC_CTR2_reg_vdac_bg_auto_en_shift                                      (7)
#define TVE_VDAC_CTR2_reg_vdac_bg_auto_en_mask                                       (0x00000080)
#define TVE_VDAC_CTR2_reg_vdac_bg_auto_en(data)                                      (0x00000080&((data)<<7))
#define TVE_VDAC_CTR2_reg_vdac_bg_auto_en_src(data)                                  ((0x00000080&(data))>>7)
#define TVE_VDAC_CTR2_get_reg_vdac_bg_auto_en(data)                                  ((0x00000080&(data))>>7)
#define TVE_VDAC_CTR2_reg_vdac_dac_rescal_shift                                      (2)
#define TVE_VDAC_CTR2_reg_vdac_dac_rescal_mask                                       (0x0000007C)
#define TVE_VDAC_CTR2_reg_vdac_dac_rescal(data)                                      (0x0000007C&((data)<<2))
#define TVE_VDAC_CTR2_reg_vdac_dac_rescal_src(data)                                  ((0x0000007C&(data))>>2)
#define TVE_VDAC_CTR2_get_reg_vdac_dac_rescal(data)                                  ((0x0000007C&(data))>>2)
#define TVE_VDAC_CTR2_reg_vdac_dac_plugin_shift                                      (1)
#define TVE_VDAC_CTR2_reg_vdac_dac_plugin_mask                                       (0x00000002)
#define TVE_VDAC_CTR2_reg_vdac_dac_plugin(data)                                      (0x00000002&((data)<<1))
#define TVE_VDAC_CTR2_reg_vdac_dac_plugin_src(data)                                  ((0x00000002&(data))>>1)
#define TVE_VDAC_CTR2_get_reg_vdac_dac_plugin(data)                                  ((0x00000002&(data))>>1)
#define TVE_VDAC_CTR2_reg_vdac_dac_drawout_shift                                     (0)
#define TVE_VDAC_CTR2_reg_vdac_dac_drawout_mask                                      (0x00000001)
#define TVE_VDAC_CTR2_reg_vdac_dac_drawout(data)                                     (0x00000001&((data)<<0))
#define TVE_VDAC_CTR2_reg_vdac_dac_drawout_src(data)                                 ((0x00000001&(data))>>0)
#define TVE_VDAC_CTR2_get_reg_vdac_dac_drawout(data)                                 ((0x00000001&(data))>>0)


#endif
