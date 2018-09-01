/*
 * kernel-rpc.h
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#ifndef _KERNEL_RPC_H_
#define _KERNEL_RPC_H_

#define RPC_AUDIO   0x0
#define RPC_VIDEO   0x1
#define RPC_VIDEO2  0x2 //add by Angus
#define RPC_KCPU    0x3

// The param1, param2 must be multiple of 4(bytes)
int send_rpc_command(int opt, uint32_t command, uint32_t param1, uint32_t param2, uint32_t *retvalue);

static inline uint32_t get_rpc_alignment_offset(uint32_t offset)
{
	if((offset%4) == 0)
		return offset;
	else
		return (offset+(4-(offset%4)));
}

#endif //_KERNEL_RPC_H_

