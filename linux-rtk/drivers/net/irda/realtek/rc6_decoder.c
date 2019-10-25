/*
 *  rc6_decoder.c - rc6 decoder for RTK irda driver
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
	dec_leader = 0,
	dec_mode,
	dec_trailer,
	dec_data,
	dec_ready,
};

struct swdec_priv {
	unsigned int state;
	unsigned int len_h;
	unsigned int len_l;
	unsigned int allcnt;
	bool remain;
	int code;
	unsigned int bitcnt;
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

static int rc6_dec_data(bool *remain, unsigned int bit,
			unsigned int high, unsigned int low)
{
	int data = 0;

	if (high >= 30 && high <= 36) {
		high = high - 22;
		*remain = 0;
	}

	if ((bit == 30 || bit == 31) && low >= 28)
		low = 11;

	if (high >= 18 && high <= 28) {
		if (*remain == 0)
			goto fail;
		if (low >= 18 && low <= 28)
			*remain = 1;
		else if (low >= 8 && low <= 15)
			*remain = 0;
		else
			goto fail;

		data |= (2 << 4) | 0x1;
	} else if (high >= 8 && high <= 15) {
		if (low >= 8 && low <= 15) {
			data |= (1 << 4) | !(*remain);
		} else if (low >= 18 && low <= 28) {
			if (*remain == 1)
				goto fail;
			data |= (1 << 4) | 1;
			*remain = 1;
		} else {
			goto fail;
		}
	} else {
		goto fail;
	}
	return data;
fail:
	*remain = 0;
	return -1;
}

bool rc6_dec_leader(bool *remain, unsigned int high, unsigned int low)
{
	if (high >= 60 && high <= 70) {
		if (low >= 20 && low <= 25)
			*remain = 0;
		else if (low >= 30 && low <= 35)
			*remain = 1;
		else
			goto fail;
	} else {
		goto fail;
	}

	return true;
fail:
	remain = 0;
	return false;
}

int raw_rc6_decoder(unsigned int *fifo, int len)
{
	unsigned int lowcnt[2], highcnt[2];
	unsigned int fifoptr = 0;
	unsigned int bitptr = 32;
	int valid_code = -1;
	int ptr;
	int data;
	int i;

get_length:
	for (i = 0; i < 2; i++) {
		lowcnt[i] = 0;
		highcnt[i] = 0;
	}
	ptr = 0;
	highcnt[ptr] = get_bitcnt(fifo, len, &fifoptr, &bitptr, 0);
	lowcnt[ptr] = get_bitcnt(fifo, len, &fifoptr, &bitptr, 1);

	if (bitptr == 0 && fifoptr >= len) {
		if ((highcnt[ptr] + lowcnt[ptr]) == 512 && dec.len_l != 512) {
			highcnt[ptr] += dec.len_h;
			lowcnt[ptr] += dec.len_l;
			dec.len_h = 0;
			dec.len_l = 512;
			goto start_decode;
		}
		dec.len_h = highcnt[ptr];
		dec.len_l = lowcnt[ptr];
		goto end_decode;
	}
	if (dec.len_h != 0 || dec.len_l != 0) {
		if (dec.len_h != 0 && dec.len_l != 0 &&
		    highcnt[ptr] != 0 && lowcnt[ptr] != 0)
			ptr++;

		highcnt[ptr] += dec.len_h;
		lowcnt[ptr] += dec.len_l;
		dec.len_h = 0;
		dec.len_l = 0;
	}

start_decode:
	switch (dec.state) {
	case dec_leader:
		dec.remain = false;
		if (rc6_dec_leader(&dec.remain, highcnt[ptr], lowcnt[ptr])) {
			if (dec.remain)
				dec.allcnt = 11;
			else
				dec.allcnt = 0;
			dec.bitcnt = 0;
			dec.code = 0;
			dec.state = dec_mode;
		}
		break;
	case dec_mode:
		dec.allcnt += (highcnt[ptr] + lowcnt[ptr]);
		if (dec.allcnt >= 108 && dec.allcnt <= 115) {
			dec.remain = true;
			dec.state = dec_data;
		} else if (dec.allcnt >= 130 && dec.allcnt <= 136) {
			dec.remain = false;
			dec.state = dec_data;
		} else if (dec.allcnt >= 140 && dec.allcnt <= 148) {
			dec.remain = true;
			dec.state = dec_data;
		}
		if (dec.allcnt >= 150 || dec.allcnt < 0) {
			dec.allcnt = 0;
			dec.state = 0;
		}
		break;
	case dec_data:
		data = rc6_dec_data(&dec.remain, dec.bitcnt,
				    highcnt[ptr], lowcnt[ptr]);
		if (data < 0) {
			pr_err("dec error %d %d\n", highcnt[ptr], lowcnt[ptr]);
			dec.state = dec_leader;
		} else {
			if (((data & 0x30) >> 4) == 0x1) {
				dec.code |= (data & 0x1) << (31 - dec.bitcnt);
				dec.bitcnt += 1;
			} else if (((data & 0x30) >> 4) == 0x2) {
				dec.code |= (data & 0x3) << (30 - dec.bitcnt);
				dec.bitcnt += 2;
			}
		}
		if (dec.bitcnt >= 32)
			dec.state = dec_ready;
		else
			break;
	case dec_ready:
		valid_code = dec.code & 0x1fffff;
		dec.state = dec_leader;
		break;
	}
	ptr--;
	if (ptr >= 0)
		goto start_decode;
	else
		goto get_length;

end_decode:
	return valid_code;
}

void raw_rc6_init(void)
{
	memset(&dec, 0, sizeof(struct swdec_priv));
}

const struct swdec_ops rc6_swdec_ops = {
	.init = raw_rc6_init,
	.decoder = raw_rc6_decoder,
};

