/*
 * rtk_sha1.h - sha1 API
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

/********************************************************************************
 SHA-1 Hashing
 ********************************************************************************/
#ifndef __RTK_SHA1_H__
#define __RTK_SHA1_H__

#define uint8_t unsigned char
#define uint32_t unsigned int

typedef struct {
    unsigned int   state[5];
    unsigned int   count[2];
    unsigned char  buffer[64];
} SHA1_CTX;

#define SHA1_FILE_HASHING_BUFFER_SIZE        FILE_HASHING_BUFFER_SIZE
#define SHA1_DIGEST_SIZE                     20
#define SHA1_BLOCK_SIZE                      64
#define SHA1_ALIGNMENT_CHECK                 0x3F

int MCP_SHA1_Get_Hash( unsigned char * source, unsigned int source_len, unsigned char * hash );
void MCP_SHA1_dump_hex( unsigned char * pbuf, unsigned int len );

void SHA1_Transform(unsigned int state[5], const unsigned char buffer[64]);
void SHA1_Init(SHA1_CTX * context);
void SHA1_Update(SHA1_CTX * context, const unsigned char * data, const size_t len);
void SHA1_Final(SHA1_CTX * context, unsigned char digest[SHA1_DIGEST_SIZE]);

#endif // __RTK_SHA1_H__
