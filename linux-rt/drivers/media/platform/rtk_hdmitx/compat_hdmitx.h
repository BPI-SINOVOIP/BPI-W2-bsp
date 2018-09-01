/*
 * compat_hdmitx.h - RTK hdmitx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef _LINUX_COMPAT_HDMITX_H
#define _LINUX_COMPAT_HDMITX_H

#include "hdmitx.h"

#if IS_ENABLED(CONFIG_COMPAT)

long compat_hdmitx_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

#endif /* CONFIG_COMPAT */
#endif /* _LINUX_COMPAT_HDMITX_H */
