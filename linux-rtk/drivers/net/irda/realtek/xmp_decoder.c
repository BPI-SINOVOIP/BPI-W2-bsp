/*
 *  xmp_decoder.c - xmp decoder for RTK irda driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/io.h>
#include "irda_sw_decoder.h"

enum {
	dec_header = 0,
	dec_data,
	dec_ready,
};

struct swdec_priv {
	unsigned int state;
	unsigned int len_h;
	unsigned int len_l;
	unsigned int bitcnt;
	int code;
};

static struct swdec_priv dec;

static int get_bitcnt(unsigned int *fifo, unsigned int len,
		      unsigned int *fifoptr, unsigned int *bitptr, int polar)
{
	unsigned int cnt = 0;

	while (1) {
		if (*bitptr == 0) {
			(*fifoptr)++;
			(*bitptr) = 32;
		}
		if (*fifoptr >= len) {
			(*bitptr) = 0;
			break;
		}
		if (test_bit((*bitptr) - 1,
			     (unsigned long *)(fifo + *fifoptr)) == polar)
			cnt++;
		else
			break;
		(*bitptr)--;
	}
	return cnt;
}

static bool xmp_checksum(int code)
{
	int i;
	int temp = 0;
	int bits;

	for (i = 0; i < 8; i++) {
		if (i == 6)
			continue;
		bits = (code & (0xF << (4 * i))) >> (4 * i);
		temp = temp + bits;
	}
	temp = (~temp + 1) & 0xF;
	if (temp == (code & 0xF << 24) >> 24)
		return true;
	else
		return false;
}

static int length_table[] = {
	20, 23, 27, 30, 34, 37, 40, 44, 47, 51, 54, 58, 61, 64, 68, 71};

static int xmp_dec_data(unsigned int high, unsigned int low)
{
	int i;

	if (high > 8 || high < 3 || low < 16 || low > 72)
		return -1;

	for (i = 0; i < 0x10; i++) {
		if (low < length_table[i])
			return i;
	}
	return -1;
}

bool xmp_dec_header(unsigned int high, unsigned int low)
{
	if (low >= 315 && low <= 350)
		return true;
	return false;
}

int raw_xmp_decoder(unsigned int *fifo, int len)
{
	unsigned int lowcnt[2], highcnt[2];
	unsigned int fifoptr = 0;
	unsigned int bitptr = 32;
	int code;
	int valid_code = -1;
	int dataptr;
	int i;

get_length:
	for (i = 0; i < 2; i++) {
		lowcnt[i] = 0;
		highcnt[i] = 0;
	}
	dataptr = 0;
	lowcnt[dataptr] = 0;
	highcnt[dataptr] = 0;
	highcnt[dataptr] = get_bitcnt(fifo, len, &fifoptr, &bitptr, 0);
	lowcnt[dataptr] = get_bitcnt(fifo, len, &fifoptr, &bitptr, 1);

	if (bitptr == 0 && fifoptr >= len) {
		dec.len_h = highcnt[dataptr];
		dec.len_l = lowcnt[dataptr];
		goto end_decode;
	}
	if (dec.len_h != 0 || dec.len_l != 0) {
		if (dec.len_h != 0 && dec.len_l != 0 &&
		    highcnt[dataptr] != 0 && lowcnt[dataptr] != 0)
			dataptr++;

		highcnt[dataptr] += dec.len_h;
		lowcnt[dataptr] += dec.len_l;
		dec.len_h = 0;
		dec.len_l = 0;
	}

start_decode:
	switch (dec.state) {
	case dec_header:
		if (xmp_dec_header(highcnt[dataptr], lowcnt[dataptr]))
			dec.state = dec_data;
		break;
	case dec_data:
		code = xmp_dec_data(highcnt[dataptr], lowcnt[dataptr]);
		if (code < 0) {
			dec.state = 0;
			dec.bitcnt = 0;
			dec.code = 0;
		} else {
			dec.code |= code << (7 - dec.bitcnt++) * 4;
		}
		if (dec.bitcnt == 8)
			dec.state = dec_ready;
		else
			break;
	case dec_ready:
		if (xmp_checksum(dec.code)) {
			if ((dec.code & 0xFF00) != 0x4400)
				valid_code = (dec.code & 0xFF00) >> 8;
		}
		dec.state = 0;
		dec.bitcnt = 0;
		dec.code = 0;
		break;
	}
	dataptr--;
	if (dataptr >= 0)
		goto start_decode;
	else
		goto get_length;

end_decode:
	return valid_code;
}

void raw_xmp_init(void)
{
	memset(&dec, 0, sizeof(struct swdec_priv));
}

const struct swdec_ops xmp_swdec_ops = {
	.init = raw_xmp_init,
	.decoder = raw_xmp_decoder,
};

