#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "SpuGen.h"


int SpuEncode(FILE *ofd, unsigned char *pixelImg, int width, int height) {
	unsigned char *sub, *subhead;
	unsigned int subo, result, BottomOffset=0;
	int remainbit, i;

	sub = (unsigned char *)malloc( SUB_BUFFER_MAX + SUB_BUFFER_HEADROOM);
	if(!sub) {
		fprintf(stderr, "ERR: Could not allocate space for sub, aborting.\n");
		return -EINVAL;
	}

	memset(sub, 0, SUB_BUFFER_MAX);
	subhead = sub;
	remainbit = 8;
	subo = 0;

	for(i = 0; i < height; i += 2)
		dvd_encode_row(i, width, pixelImg, sub, &subo, &remainbit);

	BottomOffset = subo;
	for(i = 1; i < height; i += 2)
		dvd_encode_row(i, width, pixelImg, sub, &subo, &remainbit);

	if((result = fwrite(subhead, 1, subo, ofd)) != subo) {
		printf("file rr write error, total: %d, result: %d\n", subo, result);
		free(sub);
		return -EINVAL;
	}

	free(sub);
	return BottomOffset;
}


void dvd_encode_row(int y,int xd, unsigned char *icptr, unsigned char *sub,
						unsigned int *subo, int *remainbit) {
	unsigned char *localptr;
	int new_pos, x;
	int count;
    
	new_pos = 0;

	localptr = (unsigned char*)malloc(xd);

	icptr += (y*xd / 4);
	//expand the spu image, two bit put in one char    
	for(x = 0; x < xd/4; x++) {
		localptr[x*4] = (icptr[x] >> 6 ) & 3;
		localptr[x*4+1] = (icptr[x] >> 4 ) & 3;
		localptr[x*4+2] = (icptr[x] >> 2 ) & 3;
		localptr[x*4+3] = icptr[x] & 3;
	}

	for(x = 0; x < (xd - 1); x++) {
		/* get color from x,y */

		if(localptr[x+1] != localptr[x]) {
			count= x + 1 - new_pos;
			while (count > 255) {
				do_rle(255, localptr[x], sub, subo, remainbit);
				count -= 255;
			}

			if(count)
				do_rle(count, localptr[x], sub, subo, remainbit);

			new_pos = x + 1;
		}
	} /* end for x */

	/*
		One special case,
		encoding a count of zero using the 16-bit format,
		indicates the same pixel value until the end of the line.
	*/

	if(xd != new_pos) {
		count = xd-new_pos;

		if(count < 64)
			do_rle(count, localptr[new_pos], sub, subo, remainbit);
		else {
			/* send same colors to end of line */
			store_nibble(0, sub, subo, remainbit);
			store_nibble(0, sub, subo, remainbit);
			store_nibble(0, sub, subo, remainbit);            
			store_nibble(localptr[new_pos], sub, subo, remainbit);
		}
	}

	/* If, at the end of a line, the bit count is not a multiple of 8,
		four fill bits of 0 are added. */

	store_align(sub, subo, remainbit);

	free(localptr);
}

void do_rle(int count, int color, unsigned char *sub, unsigned int *subo, int *remainbit) {
	int a;

    /* argument check */
    assert(count>=1 && count<=255);
    assert(color>=0 && color<=3);

    /* make rle code in b */
    a = (count << 2) | color;

    /* a now ranges from 0x4 up, because count is at least 1 */

    if(count >= 64)             // 64 - 255
    {
        /* 64-255, 16 bits, 0 0 0 0  0 0 n n  n n n n  n n c c */
        store_nibble(0, sub, subo, remainbit);
        store_nibble(((a & 0xf00) >> 8), sub, subo, remainbit);
        store_nibble(((a & 0xf0) >> 4), sub, subo, remainbit);
        store_nibble((a & 0xf), sub, subo, remainbit);
    }
    else if(count >= 16)        // 16 - 63
    {
        /* 16 - 63, 12 bits, 0 0 0 0  n n n n  n n c c */
        store_nibble(0, sub, subo, remainbit);
        store_nibble(((a & 0xf0) >> 4), sub, subo, remainbit);
        store_nibble((a & 0xf), sub, subo, remainbit);
    }
    else if(count >= 4)         // 4 - 15
    {
        /* 4-15, 8 bits, 0 0 n n  n n c c */
        store_nibble(((a & 0xf0) >> 4), sub, subo, remainbit);
        store_nibble((a & 0xf), sub, subo, remainbit);
    }
    else                        // 1 - 3
    {
        /* 1-3, 4 bits, n n c c */
        store_nibble((a & 0xf), sub, subo, remainbit);
    }
} /* end function do_rle */


void
store_nibble(int val, unsigned char *sub, unsigned int *sudo, int *remainbit)
{
    assert(val>=0 && val<=15);
    store_bits(val, 4, sub, sudo, remainbit);
}

void
store_bits(unsigned int val, int bits, unsigned char *sub, unsigned int *subo, int *remainbit)
{
    int bitmask[9]={0,1,3,7,15,31,63,127,255};

    if( (*subo) >SUB_BUFFER_MAX )
        return;
    while(bits) {
        if( bits > (*remainbit) ) {
            sub[(*subo)++] |= (val >> (bits-*remainbit)) & bitmask[(*remainbit)];
            bits = bits - (*remainbit);
            (*remainbit) = 8;
        } else if( bits == *remainbit ) {
            sub[(*subo)++] |= val & bitmask[(*remainbit)];
            (*remainbit) = 8;
            return;
        } else {
            sub[(*subo)] |= (val & bitmask[bits]) << ((*remainbit) - bits);
            (*remainbit) = (*remainbit) - bits;
            return;
        }
    }
}

void
store_align(unsigned char *sub, unsigned int *subo, int *remainbit)
{
    if( (*remainbit) != 8 )
        store_bits(0, (*remainbit), sub, subo, remainbit);
}


void
set_header(int field, unsigned char *sub, unsigned int *subo)
{
    int a;
    a = *subo;
    
    if (field == 1) {   // Size of Sub-picture Unit
        sub[0] = a >> 8;
        sub[1] = a;	  
    }
    if (field == 2) {   // Start address of Display Control Sequence Table
        sub[2] = a >> 8;
        sub[3] = a;
    }    

}

void
store_1(int val, unsigned char *sub, unsigned int *subo, int *remainbit)
{
    store_bits(val, 8, sub, subo, remainbit);
}



void
store_2(int val, unsigned char *sub, unsigned int *subo, int *remainbit)
{
    store_bits(val, 16, sub, subo, remainbit);
}


void
store_trinibble(int val, unsigned char *sub, unsigned int *subo, int *remainbit)
{
    store_nibble(((val>>8)&15), sub, subo, remainbit);
    store_nibble(((val>>4)&15), sub, subo, remainbit);
    store_nibble((val&15), sub, subo, remainbit);
}


