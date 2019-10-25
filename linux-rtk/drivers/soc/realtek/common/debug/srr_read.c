/*
 * srr_read.c -  Simple RBUS Register Reader
 *
 * Copyright (C) 2019, Realtek Semiconductor Corporation
 *                     Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <linux/module.h>
#include <linux/debugfs.h>
#include <linux/arm-smccc.h>

MODULE_LICENSE("GPL");

static u32 srr_read_addr;
#define MAGIC_NUM             0x8400fffe
#define RBUS_BASE             0x98000000
#define RBUS_SIZE             0x200000

static int srr_read_debugfs_u64_set(void *data, u64 val)
{
	srr_read_addr = 0;
	if (val > RBUS_SIZE)
		return -EINVAL;
	if (val & 0x3)
		return -EINVAL;
	srr_read_addr = (u32)(val + RBUS_BASE);
	return 0;
}

static int srr_read_debugfs_u64_get(void *data, u64 *val)
{
	struct arm_smccc_res res;
	u32 addr = srr_read_addr;

	if (!addr)
		return -EINVAL;
	arm_smccc_smc(MAGIC_NUM, addr, 0, 0, 0, 0, 0, 0, &res);
	*val = res.a0;
	return 0;
}

DEFINE_SIMPLE_ATTRIBUTE(srr_read_file_ops,
			srr_read_debugfs_u64_get,
			srr_read_debugfs_u64_set,
			"%08llx\n");

static __init int srr_read_init(void)
{
	debugfs_create_file("srr_read", 0644, NULL, NULL, &srr_read_file_ops);
	return 0;
}
module_init(srr_read_init);
