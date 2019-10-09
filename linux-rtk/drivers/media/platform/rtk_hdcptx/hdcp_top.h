/*
 * hdcp_top.h - RTK hdcp tx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef _HDCP_TOP_H_
#define _HDCP_TOP_H_

#include <linux/interrupt.h>
#include "hdcp.h"

#if IS_ENABLED(CONFIG_COMPAT)
long compat_hdcp_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
#else
#define compat_hdcp_ioctl  NULL
#endif

irqreturn_t HDCP_interrupt_handler(int irq, void *dev_id);


#endif /* _HDCP_TOP_H_ */
