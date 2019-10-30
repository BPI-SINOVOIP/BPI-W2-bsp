/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2012 by Chuck Chen <ycchen@realtek.com>
 *
 * prototype of system related functions for RTD1395
 */

#ifndef _LSADC_H_
#define _LSADC_H_

int rtk_lsadc_init(void);
int rtk_lsadc0_pad0_mv_get(void);
int rtk_lsadc0_pad0_int_chk(void);

#endif
