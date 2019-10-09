/*
 *  FIPS-180-2 compliant SHA-256 implementation
 *
 *  Copyright (C) 2001-2003  Christophe Devine
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include<stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "module_cp.h"
#include "sha256.h"

//extern module_cp   *__p_mod_cp;

#define GET_UINT32(n,b,i)                       \
{                                               \
    (n) = ( (uint32) (b)[(i)    ] << 24 )       \
        | ( (uint32) (b)[(i) + 1] << 16 )       \
        | ( (uint32) (b)[(i) + 2] <<  8 )       \
        | ( (uint32) (b)[(i) + 3]       );      \
}

#define PUT_UINT32(n,b,i)                       \
{                                               \
    (b)[(i)    ] = (uint8) ( (n) >> 24 );       \
    (b)[(i) + 1] = (uint8) ( (n) >> 16 );       \
    (b)[(i) + 2] = (uint8) ( (n) >>  8 );       \
    (b)[(i) + 3] = (uint8) ( (n)       );       \
}

#define  SHR(x,n) ((x & 0xFFFFFFFF) >> n)
#define ROTR(x,n) (SHR(x,n) | (x << (32 - n)))

#define S0(x) (ROTR(x, 7) ^ ROTR(x,18) ^  SHR(x, 3))
#define S1(x) (ROTR(x,17) ^ ROTR(x,19) ^  SHR(x,10))

#define S2(x) (ROTR(x, 2) ^ ROTR(x,13) ^ ROTR(x,22))
#define S3(x) (ROTR(x, 6) ^ ROTR(x,11) ^ ROTR(x,25))

#define F0(x,y,z) ((x & y) | (z & (x | y)))
#define F1(x,y,z) (z ^ (x & (y ^ z)))

#define R(t)                                    \
(                                               \
    W[t] = S1(W[t -  2]) + W[t -  7] +          \
           S0(W[t - 15]) + W[t - 16]            \
)
#define PR(t)                  \
{                                               \
;\
}

/*
#define PR(t)                  \
{                                               \
printf("S1=%x, W[t-7]=%x, S0=%x, W[t-16]=%x W[t]=%x\n", S1(W[t-2]), W[t-7], S0(W[t-15]), W[t-16], S1(W[t-2])+W[t-7]+S0(W[t-15])+W[t-16] );\
}

#define P(a,b,c,d,e,f,g,h,x,K)                  \
{                                               \
printf("A=%x, B=%x, C=%x, D=%x, E=%x, F=%x, G=%x, H=%x, W=%x, K=%x\n", a,b,c,d,e,f,g,h, x, K);\
    temp1 = h + S3(e) + F1(e,f,g) + K + x;      \
    temp2 = S2(a) + F0(a,b,c);                  \
printf("sum=%x, Maj=%x, T2=%x\n", S2(a), F0(a, b, c), temp2);\
    d += temp1; h = temp1 + temp2;              \
}
*/

#define P(a,b,c,d,e,f,g,h,x,K)                  \
{                                               \
    temp1 = h + S3(e) + F1(e,f,g) + K + x;      \
    temp2 = S2(a) + F0(a,b,c);                  \
    d += temp1; h = temp1 + temp2;              \
}


void sha256_starts( sha256_context *ctx )
{
    ctx->total[0] = 0;
    ctx->total[1] = 0;
#if 1
    ctx->state[0] = 0x6A09E667;
    ctx->state[1] = 0xBB67AE85;
    ctx->state[2] = 0x3C6EF372;
    ctx->state[3] = 0xA54FF53A;
    ctx->state[4] = 0x510E527F;
    ctx->state[5] = 0x9B05688C;
    ctx->state[6] = 0x1F83D9AB;
    ctx->state[7] = 0x5BE0CD19;
#else
		//invert endian by angus for test
    ctx->state[0] = 0x67E6096A;
    ctx->state[1] = 0x85AE67BB;
    ctx->state[2] = 0x72F36E3C;
    ctx->state[3] = 0x3AF54FA5;
    ctx->state[4] = 0x7F520E51;
    ctx->state[5] = 0x8C68059B;
    ctx->state[6] = 0xABD9831F;
    ctx->state[7] = 0x19CDE05B;
#endif
}

/*
void sha256_starts( sha256_context *ctx , unsigned long key[8])
{
    ctx->total[0] = 0;
    ctx->total[1] = 0;

    ctx->state[0] = key[0];
    ctx->state[1] = key[1];
    ctx->state[2] = key[2];
    ctx->state[3] = key[3];
    ctx->state[4] = key[4];
    ctx->state[5] = key[5];
    ctx->state[6] = key[6];
    ctx->state[7] = key[7];
	printf("sha256 init state: %08x %08x %08x %08x %08x %08x %08x %08x\n",ctx->state[0],ctx->state[1],ctx->state[2],ctx->state[3],ctx->state[4], ctx->state[5], ctx->state[6], ctx->state[7]);
}
*/

void sha256_process( sha256_context *ctx, uint8 data[64] )
{
//{{{	
    uint32 temp1, temp2, W[64];
    uint32 A, B, C, D, E, F, G, H;

    GET_UINT32( W[0],  data,  0 );
    GET_UINT32( W[1],  data,  4 );
    GET_UINT32( W[2],  data,  8 );
    GET_UINT32( W[3],  data, 12 );
    GET_UINT32( W[4],  data, 16 );
    GET_UINT32( W[5],  data, 20 );
    GET_UINT32( W[6],  data, 24 );
    GET_UINT32( W[7],  data, 28 );
    GET_UINT32( W[8],  data, 32 );
    GET_UINT32( W[9],  data, 36 );
    GET_UINT32( W[10], data, 40 );
    GET_UINT32( W[11], data, 44 );
    GET_UINT32( W[12], data, 48 );
    GET_UINT32( W[13], data, 52 );
    GET_UINT32( W[14], data, 56 );
    GET_UINT32( W[15], data, 60 );

    A = ctx->state[0];
    B = ctx->state[1];
    C = ctx->state[2];
    D = ctx->state[3];
    E = ctx->state[4];
    F = ctx->state[5];
    G = ctx->state[6];
    H = ctx->state[7];
//printf("[SHA-256] 0 : ");
    P( A, B, C, D, E, F, G, H, W[ 0], 0x428A2F98 );
//printf("[SHA-256] 1 : ");	
    P( H, A, B, C, D, E, F, G, W[ 1], 0x71374491 );
//printf("[SHA-256] 2 : ");
    P( G, H, A, B, C, D, E, F, W[ 2], 0xB5C0FBCF );
//printf("[SHA-256] 3 : ");	
    P( F, G, H, A, B, C, D, E, W[ 3], 0xE9B5DBA5 );
//printf("[SHA-256] 4 : ");	
    P( E, F, G, H, A, B, C, D, W[ 4], 0x3956C25B );
//printf("[SHA-256] 5 : ");
    P( D, E, F, G, H, A, B, C, W[ 5], 0x59F111F1 );
//printf("[SHA-256] 6 : ");
    P( C, D, E, F, G, H, A, B, W[ 6], 0x923F82A4 );
//printf("[SHA-256] 7 : ");
    P( B, C, D, E, F, G, H, A, W[ 7], 0xAB1C5ED5 );
//printf("[SHA-256] 8 : ");
    P( A, B, C, D, E, F, G, H, W[ 8], 0xD807AA98 );
//printf("[SHA-256] 9 : ");	
    P( H, A, B, C, D, E, F, G, W[ 9], 0x12835B01 );
//printf("[SHA-256] 10 : ");
    P( G, H, A, B, C, D, E, F, W[10], 0x243185BE );
//printf("[SHA-256] 11 : ");
    P( F, G, H, A, B, C, D, E, W[11], 0x550C7DC3 );
//printf("[SHA-256] 12 : ");
    P( E, F, G, H, A, B, C, D, W[12], 0x72BE5D74 );
//printf("[SHA-256] 13 : ");
    P( D, E, F, G, H, A, B, C, W[13], 0x80DEB1FE );
//printf("[SHA-256] 14 : ");
    P( C, D, E, F, G, H, A, B, W[14], 0x9BDC06A7 );
//printf("[SHA-256] 15 : ");
    P( B, C, D, E, F, G, H, A, W[15], 0xC19BF174 );
//printf("[SHA-256] 16 : ");
    P( A, B, C, D, E, F, G, H, R(16), 0xE49B69C1 );
PR(16);
//printf("[SHA-256] 17 : ");
    P( H, A, B, C, D, E, F, G, R(17), 0xEFBE4786 );
PR(17);	
//printf("[SHA-256] 18 : ");
    P( G, H, A, B, C, D, E, F, R(18), 0x0FC19DC6 );
PR(18);	
//printf("[SHA-256] 19 : ");
    P( F, G, H, A, B, C, D, E, R(19), 0x240CA1CC );
PR(19);	
//printf("[SHA-256] 20 : ");
    P( E, F, G, H, A, B, C, D, R(20), 0x2DE92C6F );
PR(20);
//printf("[SHA-256] 21 : ");
    P( D, E, F, G, H, A, B, C, R(21), 0x4A7484AA );
PR(21);	
//printf("[SHA-256] 22 : ");
    P( C, D, E, F, G, H, A, B, R(22), 0x5CB0A9DC );
PR(22);
//printf("[SHA-256] 23 : ");
    P( B, C, D, E, F, G, H, A, R(23), 0x76F988DA );
PR(23);
//printf("[SHA-256] 24 : ");
    P( A, B, C, D, E, F, G, H, R(24), 0x983E5152 );
PR(24);
//printf("[SHA-256] 25 : ");
    P( H, A, B, C, D, E, F, G, R(25), 0xA831C66D );
PR(25);
//printf("[SHA-256] 26 : ");
    P( G, H, A, B, C, D, E, F, R(26), 0xB00327C8 );
PR(26);
//printf("[SHA-256] 27 : ");
    P( F, G, H, A, B, C, D, E, R(27), 0xBF597FC7 );
PR(27);
//printf("[SHA-256] 28 : ");
    P( E, F, G, H, A, B, C, D, R(28), 0xC6E00BF3 );
PR(28);
//printf("[SHA-256] 29 : ");
    P( D, E, F, G, H, A, B, C, R(29), 0xD5A79147 );
PR(29);
//printf("[SHA-256] 30 : ");
    P( C, D, E, F, G, H, A, B, R(30), 0x06CA6351 );
PR(30);
//printf("[SHA-256] 31 : ");
    P( B, C, D, E, F, G, H, A, R(31), 0x14292967 );
PR(31);
//printf("[SHA-256] 32 : ");
    P( A, B, C, D, E, F, G, H, R(32), 0x27B70A85 );
PR(32);
//printf("[SHA-256] 33 : ");
    P( H, A, B, C, D, E, F, G, R(33), 0x2E1B2138 );
PR(33);
//printf("[SHA-256] 34 : ");	
    P( G, H, A, B, C, D, E, F, R(34), 0x4D2C6DFC );
PR(34);
//printf("[SHA-256] 35 : ");		
    P( F, G, H, A, B, C, D, E, R(35), 0x53380D13 );
PR(35);
//printf("[SHA-256] 36 : ");	
    P( E, F, G, H, A, B, C, D, R(36), 0x650A7354 );
PR(36);
//printf("[SHA-256] 37 : ");	
    P( D, E, F, G, H, A, B, C, R(37), 0x766A0ABB );
PR(37);
//printf("[SHA-256] 38 : ");	
    P( C, D, E, F, G, H, A, B, R(38), 0x81C2C92E );
PR(38);
//printf("[SHA-256] 39 : ");	
    P( B, C, D, E, F, G, H, A, R(39), 0x92722C85 );
PR(39);
//printf("[SHA-256] 40 : ");	
    P( A, B, C, D, E, F, G, H, R(40), 0xA2BFE8A1 );
PR(40);
//printf("[SHA-256] 41 : ");	
    P( H, A, B, C, D, E, F, G, R(41), 0xA81A664B );
PR(41);
//printf("[SHA-256] 42 : ");	
    P( G, H, A, B, C, D, E, F, R(42), 0xC24B8B70 );
PR(42);
//printf("[SHA-256] 43 : ");	
    P( F, G, H, A, B, C, D, E, R(43), 0xC76C51A3 );
PR(43);
//printf("[SHA-256] 44 : ");	
    P( E, F, G, H, A, B, C, D, R(44), 0xD192E819 );
PR(44);
//printf("[SHA-256] 45 : ");	
    P( D, E, F, G, H, A, B, C, R(45), 0xD6990624 );
PR(45);
//printf("[SHA-256] 46 : ");		
    P( C, D, E, F, G, H, A, B, R(46), 0xF40E3585 );
PR(46);
//printf("[SHA-256] 47 : ");	
    P( B, C, D, E, F, G, H, A, R(47), 0x106AA070 );
PR(47);
//printf("[SHA-256] 48 : ");	
    P( A, B, C, D, E, F, G, H, R(48), 0x19A4C116 );
PR(48);
//printf("[SHA-256] 49 : ");	
    P( H, A, B, C, D, E, F, G, R(49), 0x1E376C08 );
PR(49);
//printf("[SHA-256] 50 : ");	
    P( G, H, A, B, C, D, E, F, R(50), 0x2748774C );
PR(50);
//printf("[SHA-256] 51 : ");	
    P( F, G, H, A, B, C, D, E, R(51), 0x34B0BCB5 );
PR(51);
//printf("[SHA-256] 52 : ");	
    P( E, F, G, H, A, B, C, D, R(52), 0x391C0CB3 );
PR(52);
//printf("[SHA-256] 53 : ");	
    P( D, E, F, G, H, A, B, C, R(53), 0x4ED8AA4A );
PR(53);
//printf("[SHA-256] 54 : ");	
    P( C, D, E, F, G, H, A, B, R(54), 0x5B9CCA4F );
PR(54);
//printf("[SHA-256] 55 : ");	
    P( B, C, D, E, F, G, H, A, R(55), 0x682E6FF3 );
PR(55);
//printf("[SHA-256] 56 : ");	
    P( A, B, C, D, E, F, G, H, R(56), 0x748F82EE );
PR(56);
//printf("[SHA-256] 57 : ");	
    P( H, A, B, C, D, E, F, G, R(57), 0x78A5636F );
PR(57);
//printf("[SHA-256] 58 : ");	
    P( G, H, A, B, C, D, E, F, R(58), 0x84C87814 );
PR(58);
//printf("[SHA-256] 59 : ");	
    P( F, G, H, A, B, C, D, E, R(59), 0x8CC70208 );
PR(59);
//printf("[SHA-256] 60 : ");	
    P( E, F, G, H, A, B, C, D, R(60), 0x90BEFFFA );
PR(60);
//printf("[SHA-256] 61 : ");	
    P( D, E, F, G, H, A, B, C, R(61), 0xA4506CEB );
PR(61);
//printf("[SHA-256] 62 : ");	
    P( C, D, E, F, G, H, A, B, R(62), 0xBEF9A3F7 );
PR(62);
//printf("[SHA-256] 63 : ");	
    P( B, C, D, E, F, G, H, A, R(63), 0xC67178F2 );
PR(63);

//printf("[SHA-256] after process: A=%x, B=%x, C=%x, D=%x, E=%x, F=%x, G=%x, H=%x\n", A,B,C,D,E,F,G,H);
    ctx->state[0] += A;
    ctx->state[1] += B;
    ctx->state[2] += C;
    ctx->state[3] += D;
    ctx->state[4] += E;
    ctx->state[5] += F;
    ctx->state[6] += G;
    ctx->state[7] += H;
//}}}
}

void sha256_update( sha256_context *ctx, uint8 *input, uint32 length )
{
//{{{	
    uint32 left, fill;

    if( ! length ) return;

    left = ctx->total[0] & 0x3F;
    fill = 64 - left;

    ctx->total[0] += length;
    ctx->total[0] &= 0xFFFFFFFF;

    if( ctx->total[0] < length )					// overflow
        ctx->total[1]++;

    if( left && length >= fill )
    {
        memcpy( (void *) (ctx->buffer + left),		// last remains in ctx->buffer ~ ctx->buffer+left
                (void *) input, fill );				// padding new data
        sha256_process( ctx, ctx->buffer );
        length -= fill;
        input  += fill;
        left = 0;
    }

    while( length >= 64 )
    {
        sha256_process( ctx, input );
        length -= 64;
        input  += 64;
    }

    if( length )
    {
        memcpy( (void *) (ctx->buffer + left),		// keep remain data in ctx->buffer ~ ctx->buffer+left
                (void *) input, length );
    }
//}}}	
}


static uint8 sha256_padding[64] =
{
 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


void sha256_finish( sha256_context *ctx, uint8 digest[32] )
{
//{{{	
    uint32 last, padn;
    uint32 high, low;
    uint8 msglen[8];

    high = ( ctx->total[0] >> 29 )
         | ( ctx->total[1] <<  3 );
    low  = ( ctx->total[0] <<  3 );

    PUT_UINT32( high, msglen, 0 );
    PUT_UINT32( low,  msglen, 4 );

    last = ctx->total[0] & 0x3F;
    padn = ( last < 56 ) ? ( 56 - last ) : ( 120 - last );

    sha256_update( ctx, sha256_padding, padn );
    sha256_update( ctx, msglen, 8 );

    PUT_UINT32( ctx->state[0], digest,  0 );
    PUT_UINT32( ctx->state[1], digest,  4 );
    PUT_UINT32( ctx->state[2], digest,  8 );
    PUT_UINT32( ctx->state[3], digest, 12 );
    PUT_UINT32( ctx->state[4], digest, 16 );
    PUT_UINT32( ctx->state[5], digest, 20 );
    PUT_UINT32( ctx->state[6], digest, 24 );
    PUT_UINT32( ctx->state[7], digest, 28 );
//}}}	
}

