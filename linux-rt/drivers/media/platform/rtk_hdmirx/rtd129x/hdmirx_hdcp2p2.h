/*
 * hdmirx_hdcp2p2.h - RTK hdmi rx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __HDCP2P2_H_
#define __HDCP2P2_H_

#include "hdcp2p2_dev.h"

unsigned char Is_HdmiRx_hdcp2p2_enabled(void);

void init_hdcp2p2_waitqueue(void);
int get_hdcp2p2_msg(struct rx_hdcp22_msg *msg);
int write_hdcp2p2_msg_to_tx(struct rx_hdcp22_msg *msg);
int get_stream_msg(struct rx_hdcp22_msg *msg);
int set_hdcp2p2_ks(struct rx_hdcp22_ks *ks);
void Clear_Hdmi_hdcp_2_2_Read_Status(void);
int get_hdcp2p2_msg_done(int *done);
void Set_Rx_status_Ready(void);
void DownStream_done(void);
int set_hdcp2p2_switch_state(int *state);

#endif /* __HDCP2P2_H_ */
