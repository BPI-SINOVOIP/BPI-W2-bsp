/*
 *  comcast_decoder.c - RTK irda software decoder for comcast remote
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

static int get_bit_count(unsigned int *fifo, unsigned int number, unsigned int *ptr, unsigned int *bptr, int polar)
{
	unsigned int bit_cnt = 0;

	if(polar != 0 && polar != 1)
		return -1;

	while(1) {
		if(*bptr == 0) {
			(*ptr)++;
			if( *ptr>=number )
				return bit_cnt;
			(*bptr) = 32;
		} else {
			if( test_bit((*bptr)-1, (unsigned long *)(fifo+*ptr)) ) {
				if(polar == 1) {
					(*bptr)--;
					bit_cnt++;
				} else
					break;
			} else {
				if(polar == 0) {
					(*bptr)--;
					bit_cnt++;
				} else
					break;
			}
		}
	}
	return bit_cnt;
}

static int length_table[]=
{ 20, 23, 27, 30, 34, 37, 40, 44, 47, 51, 54, 58, 61, 64, 68, 71};

static int comcast_length_decode(unsigned int len_h, unsigned int len_l)
{
	int i;
	if( len_h>8 || len_h<3 || len_l<16 || len_l>72 )
		return -1;
	for(i=0; i<0x10; i++) {
		if(len_l < length_table[i])
			return i;
	}
	return i;
}

static int comcast_checksum(int code)
{
	int i;
	int temp=0;
	int bits;

	for(i=0; i<8; i++) {
		if(i!=6) {
			bits = (code & (0xF<<(4*i)))>>(4*i);
			temp = temp + bits;
		}
	}
	temp = (~temp+1) & 0xF;
	if(temp == (code & 0xF<<24)>>24 )
		return 1;
	else
		return 0;
}

int raw_comcast_decoder(struct swdec_priv *pdec, unsigned int *fifoval, int fifolv)
{
	unsigned int length_low=0, length_high=0;
	int code;
	unsigned int fifoptr=0, bitptr=32;

	pdec->codenum=0;

	while(1) {
		length_high = length_low = 0;
		length_high = get_bit_count(fifoval, fifolv, &fifoptr, &bitptr, 0);
		length_low = get_bit_count(fifoval, fifolv, &fifoptr, &bitptr, 1);
		if( bitptr==0 && fifoptr>=fifolv ) {
			if(pdec->fifostate==3 || pdec->fifostate==1) {
				pdec->fifostate = pdec->symbol_cnt = pdec->symbol = 0;
				pdec->length_hb = pdec->length_lb = 0;
			}
			break;
		}
decode_start:
		if(pdec->fifostate<2) {
			if(pdec->fifostate == 1) {
				if(length_high==0 || length_low==0 || pdec->length_lb==0 || pdec->length_hb==0) {
					length_low += pdec->length_lb;
					length_high += pdec->length_hb;
				} else {
					if(pdec->length_lb>=336 && pdec->length_lb<=348) {
						pdec->symbol_cnt = pdec->symbol = 0;
						pdec->fifostate = 2;
					} else
						pdec->fifostate = 0;
				}
				pdec->length_hb = pdec->length_lb = 0;
				if(pdec->fifostate==2)
					goto decode_start;
			}
			if(length_low>=336 && length_low<=348) {
				pdec->symbol_cnt = pdec->symbol = 0;
				pdec->fifostate = 2;
			} else
				pdec->fifostate = 0;
		}
		else if(pdec->fifostate>=2 && pdec->symbol_cnt<=8) {
			if(pdec->fifostate==3) {
				pdec->fifostate = 2;
				if(length_high==0 || length_low==0 || pdec->length_hb==0 || pdec->length_lb==0) {
					length_low += pdec->length_lb;
					length_high += pdec->length_hb;
				} else {
					code = comcast_length_decode(pdec->length_hb, pdec->length_lb);
					if(code < 0)
						pdec->fifostate = pdec->symbol_cnt = pdec->symbol = 0;
					else
						pdec->symbol = pdec->symbol | code << (7-pdec->symbol_cnt++)*4;
				}
				pdec->length_hb = pdec->length_lb = 0;
			}
			if(pdec->symbol_cnt < 8) {
				code = comcast_length_decode(length_high, length_low);
				if(code < 0)
					pdec->fifostate = pdec->symbol_cnt = pdec->symbol = 0;
				else
					pdec->symbol = pdec->symbol | code << (7-pdec->symbol_cnt++)*4;
			}
			if(pdec->symbol_cnt==8) {
				if(comcast_checksum(pdec->symbol)) {
					if( (pdec->symbol & 0xFF00)!=0x4400 )
						pdec->valid_code[pdec->codenum++] = (pdec->symbol&0xFF00)>>8;
				}
				pdec->fifostate = pdec->symbol = pdec->symbol_cnt = 0;
			}
		}
	}
	if(pdec->fifostate==2 || length_low<350 ) {
		pdec->length_hb = length_high;
		pdec->length_lb = length_low;
		pdec->fifostate += 1;
	}
	if(pdec->codenum>0)
		return pdec->valid_code[pdec->codenum-1];
	else
		return -1;
}

