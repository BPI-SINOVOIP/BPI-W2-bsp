/*
 * hdmitx_api.h - RTK hdmitx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __HDMITX_API_H__
#define __HDMITX_API_H__

#include "hdmitx_dev.h"
#include "hdmitx.h"
#include "hdmitx_rpc.h"

extern unsigned int hdmi_clk_always_on;

int check_hdmi_mhl_mode(void);

int hdmitx_send_AVmute(void __iomem *base, int flag);
int hdmitx_check_tmds_src(void __iomem *base);
int hdmitx_turn_off_tmds(int vo_mode);

void register_ion_client(const char *name);
void deregister_ion_client(const char *name);
int RPC_TOAGENT_HDMI_Config_TV_System(struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM *arg);
int RPC_TOAGENT_HDMI_Config_AVI_Info(struct VIDEO_RPC_VOUT_CONFIG_HDMI_INFO_FRAME *arg);
int RPC_TOAGENT_HDMI_Set(struct AUDIO_HDMI_SET *arg);
int RPC_TOAGENT_HDMI_Mute(struct AUDIO_HDMI_MUTE_INFO *arg);
int RPC_TOAGENT_HDMI_OUT_VSDB(struct AUDIO_HDMI_OUT_VSDB_DATA *arg);
int RPC_ToAgent_HDMI_OUT_EDID_0(struct AUDIO_HDMI_OUT_EDID_DATA2 *arg);
int RPC_ToAgent_Vout_EDIDdata(struct VIDEO_RPC_VOUT_EDID_DATA *arg);
int RPC_ToAgent_QueryConfigTvSystem(struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM *arg);

int hdmitx_check_same_edid(asoc_hdmi_t *p_this);
int hdmitx_reset_sink_capability(asoc_hdmi_t *p_this);
int hdmitx_get_sink_capability(asoc_hdmi_t *p_this);
void hdmitx_print_sink_capability(asoc_hdmi_t *p_this);
void hdmitx_print_sink_info(asoc_hdmi_t *p_this);
int hdmitx_check_rx_sense(void __iomem *reg_base);
void hdmitx_set_error_code(int hdmi_error);
void hdmitx_dump_error_code(void);

int ops_get_sink_cap(void __user *arg, asoc_hdmi_t *data);
int ops_get_raw_edid(void __user *arg, asoc_hdmi_t *data);
int ops_get_extension_blk_count(void __user *arg, asoc_hdmi_t *data);
int ops_get_extended_edid(void __user *arg, asoc_hdmi_t *data);
int ops_get_link_status(void __user *arg);
int ops_get_video_config(void __user *arg, asoc_hdmi_t *data);
int ops_config_tv_system(void __user *arg);
int ops_config_avi_info(void __user *arg);
int ops_set_frequency(void __user *arg);
int ops_set_audio_mute(void __user *arg);
int ops_send_audio_vsdb_data(void __user *arg);
int ops_send_audio_edid2(void __user *arg);
int ops_query_display_standard(void __user *arg);

int ops_send_AVmute(void __user *arg, void __iomem *base);
int ops_check_tmds_src(void __user *arg, void __iomem *base);
int ops_check_rx_sense(void __user *arg, void __iomem *base);
int ops_send_vout_edid_data(void __user *arg);
int ops_get_edid_support_list(void __user *arg, asoc_hdmi_t *data);
int ops_set_output_format(void __user *arg);
int ops_get_output_format(void __user *arg);
int ops_set_interface_type(void __user *arg);

#endif  //__HDMITX_API_H__
