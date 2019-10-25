/*
 *  irda_sw_decoder.h - RTK irda software decoder header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#ifndef __IRDA_SW_DECODER__H__
#define __IRDA_SW_DECODER__H__

struct swdec_ops {
	void (*init)(void);
	int (*decoder)(unsigned int *, int);
};

extern const struct swdec_ops rc6_swdec_ops;
extern const struct swdec_ops xmp_swdec_ops;
#endif
