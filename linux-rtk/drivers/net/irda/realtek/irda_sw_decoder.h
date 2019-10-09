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


struct swdec_priv {
	unsigned int fifostate;
	unsigned int length_hb;
	unsigned int length_lb;
	unsigned int symbol_cnt;
	unsigned char encode_mode;
	unsigned char encode_num;
	int symbol;
	int codenum;
	int valid_code[5];
	int (*decoder)(struct swdec_priv *, unsigned int *, int);
};

int raw_comcast_decoder(struct swdec_priv *pdec, unsigned int *fifoval, int fifolv);

#endif
