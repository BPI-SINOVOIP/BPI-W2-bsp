/*
 * hdcp2p2_dev.h - RTK hdmi rx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __HDCP2P2_DEV_H_
#define __HDCP2P2_DEV_H_

struct rx_hdcp22_msg {
	unsigned int bLen;
	unsigned char msg[864];
	unsigned char g_RX_state;
} __attribute__ ((packed));


struct rx_hdcp22_ks {
	unsigned char bks[16];
} __attribute__ ((packed));


#define HDCP22IOC_INIT				_IOWR('V', 0, int)
#define HDCP22IOC_GET_HDCP22_MSG	_IOWR('V', 1, struct rx_hdcp22_msg)
#define HDCP22IOC_WRITE_DATA_TO_TX	_IOWR('V', 2, struct rx_hdcp22_msg)
#define HDCP22IOC_GET_STREAM_MSG	_IOWR('V', 3, struct rx_hdcp22_msg)
#define HDCP22IOC_SET_KS			_IOWR('V', 4, struct rx_hdcp22_ks)
#define HDCP22IOC_CLR_MSG_DONE		_IOWR('V', 5, int)
#define HDCP22IOC_GET_MSG_DONE		_IOWR('V', 6, int)
#define HDCP22IOC_SET_STATUS_READY	_IOWR('V', 7, int)
#define HDCP22IOC_SET_DOWNSTREAM_DONE	_IOWR('V', 8, int)
#define HDCP22IOC_SET_SWITCH_STATE	_IOWR('V', 9, int)


void register_hdcp2p2_device(void);

#endif /* __HDCP2P2_DEV_H_ */
