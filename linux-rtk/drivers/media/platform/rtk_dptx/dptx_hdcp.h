/*
 *  dptx_hdcp.h - RTK display port driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __DPTX_HDCP_H__
#define __DPTX_HDCP_H__

#include "dptx_hwapi.h"

void dptx_hdcp_check_capability(struct rtk_dptx_hwinfo *hwinfo);
void dptx_hdcp_initial(struct rtk_dptx_hwinfo *hwinfo);
void dptx_hdcp_handler(struct rtk_dptx_hwinfo *hwinfo);
void dptx_hdcp_change_state(struct rtk_dptx_hwinfo *hwinfo, int state);

#endif  //__DPTX_HDCP_H__
