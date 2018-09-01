/*
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

#ifndef _LINUX_COMPAT_VE1_H
#define _LINUX_COMPAT_VE1_H

#if IS_ENABLED(CONFIG_COMPAT)

typedef struct compat_vpu_bit_firmware_info_t {
	compat_uint_t size; /* size of this structure*/
	compat_uint_t core_idx;
	compat_ulong_t reg_base_offset;
	compat_ushort_t bit_code[512];
} compat_vpu_bit_firmware_info_t;

long compat_vpu_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);

#else

typedef struct compat_vpu_bit_firmware_info_t {
	unsigned int size; /* size of this structure*/
	unsigned int core_idx;
	unsigned long reg_base_offset;
	unsigned short bit_code[512];
} compat_vpu_bit_firmware_info_t;

#define compat_vpu_ioctl  NULL

#endif /* CONFIG_COMPAT */
#endif /* _LINUX_COMPAT_VE1_H */
