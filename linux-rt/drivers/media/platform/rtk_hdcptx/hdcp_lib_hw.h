/*
 * hdcp_lib_hw.h - RTK hdcp tx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifdef CONFIG_RTK_HDCP_1x_TEE

extern void ta_hdcp14_init(void);
extern void ta_hdcp14_deinit(void);
extern int ta_hdcp_lib_check_repeater_bit_in_tx(void);
extern int ta_hdcp_lib_generate_an(uint8_t *an);
extern void ta_hdcp_lib_set_repeater_bit_in_tx(enum hdcp_repeater rx_mode);
extern void ta_hdcp_lib_set_wider_window(void);
extern void ta_hdcp_lib_set_ri(enum ri_state ri_state);
extern void ta_hdcp_lib_set_encryption(enum encryption_state enc_state);
extern int ta_hdcp_lib_SHA_append_bstatus_M0(struct hdcp_sha_in *sha, uint8_t *bstatus);
extern int ta_hdcp_lib_compute_V(struct hdcp_sha_in *sha);
extern int ta_hdcp_lib_verify_V(struct hdcp_sha_in *sha);
extern void ta_hdcp_lib_set_av_mute(enum av_mute av_mute_state);
extern int ta_hdcp_lib_write_bksv(uint8_t *ksv_data);

#define hdcp_lib_check_repeater_bit_in_tx(arg) ta_hdcp_lib_check_repeater_bit_in_tx(arg)
#define hdcp_lib_generate_an(arg) ta_hdcp_lib_generate_an(arg)
#define hdcp_lib_set_repeater_bit_in_tx(arg) ta_hdcp_lib_set_repeater_bit_in_tx(arg)
#define hdcp_lib_set_wider_window(arg) ta_hdcp_lib_set_wider_window(arg)
#define hdcp_lib_set_ri_interrupt(arg) ta_hdcp_lib_set_ri(arg)
#define hdcp_lib_set_encryption(arg) ta_hdcp_lib_set_encryption(arg)
#define hdcp_lib_SHA_append_bstatus_M0(arg1, arg2) ta_hdcp_lib_SHA_append_bstatus_M0(arg1, arg2)
#define hdcp_lib_compute_V(arg) ta_hdcp_lib_compute_V(arg)
#define hdcp_lib_verify_V(arg) ta_hdcp_lib_verify_V(arg)
#define hdcp_lib_write_bksv(arg) ta_hdcp_lib_write_bksv(arg)
#define hdcp_lib_set_av_mute(arg) ta_hdcp_lib_set_av_mute(arg)

#else

int hdcp_lib_check_repeater_bit_in_tx(void);
int hdcp_lib_generate_an(uint8_t *an);
void hdcp_lib_set_repeater_bit_in_tx(enum hdcp_repeater rx_mode);
void hdcp_lib_set_wider_window(void);
void hdcp_lib_set_ri_interrupt(enum ri_state state);
void hdcp_lib_set_encryption(enum encryption_state enc_state);
void hdcp_lib_SHA_append_bstatus_M0(struct hdcp_sha_in *sha, uint8_t *data);
int hdcp_lib_compute_V(struct hdcp_sha_in *sha);
int hdcp_lib_verify_V(struct hdcp_sha_in *sha);
int hdcp_lib_write_bksv(uint8_t *ksv_data);
void hdcp_lib_set_av_mute(enum av_mute av_mute_state);

#endif

