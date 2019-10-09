#ifndef __SPUGEN_H_
#define __SPUGEN_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
//#include "spu_types.h"

#define SUB_MAX_TEXT            16
#define SUB_BUFFER_MAX          53220
#define SUB_BUFFER_HEADROOM     1024


int SpuEncode(FILE *ofd, unsigned char *pixelImg, int width, int height); 
void do_rle(int count, int color,
            unsigned char *sub, unsigned int *subo, int *remainbit);
            
void store_nibble(int val,
                  unsigned char *sub, unsigned int *sudo, int *remainbit);

void store_bits(unsigned int val, int bits,
                unsigned char *sub, unsigned int *subo, int *remainbit);
                
void store_align(unsigned char *sub, unsigned int *subo, int *remainbit);

void set_header(int field, unsigned char *sub, unsigned int *subo);
void store_1(int val, unsigned char *sub, unsigned int *subo, int *remainbit);
void store_2(int val, unsigned char *sub, unsigned int *subo, int *remainbit);
void store_trinibble(int val, unsigned char *sub, unsigned int *subo, int *remainbit);

//=============================================================================//
// The coordinates is counted from (1,1) 
void dvd_encode_row(int y,int xd, unsigned char *icptr,
                     unsigned char *sub, unsigned int *subo, int *remainbit);


#endif // __SPUGEN_H_

