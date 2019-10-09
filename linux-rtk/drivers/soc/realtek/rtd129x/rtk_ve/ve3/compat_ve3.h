/*

 * drivers/soc/realtek/rtd129x/rtk_ve/ve3/compat_ve3.h
 *
 * Copyright (C) 2013 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _LINUX_COMPAT_VE3_H
#define _LINUX_COMPAT_VE3_H

#if IS_ENABLED(CONFIG_COMPAT)

long compat_hantrodec_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);

#else

#define compat_hantrodec_ioctl  NULL

#endif /* CONFIG_COMPAT */
#endif /* _LINUX_COMPAT_VE3_H */
