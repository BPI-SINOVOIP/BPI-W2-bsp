/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2015 by Tom Ting <tom_ting@realtek.com>
 *
 * prototype of system related functions for RTD1619
 */

#ifndef _SYS_PROTO_H_
#define _SYS_PROTO_H_

#include <asm/io.h>

struct rtd161x_sysinfo {
	char *board_string;
};
extern const struct rtd161x_sysinfo sysinfo;

#endif
