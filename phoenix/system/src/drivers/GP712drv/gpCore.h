/*
 * $Header: //depot/release/Embedded/BaseComps/v2.4.5.0/sw/comps/halLinux/kernel/GP_Generic_Driver/gpCore.h#1 $
 * $Change: 68365 $
 * $DateTime: 2015/07/31 10:23:51 $
 * Copyright (C) 2014, GreenPeak Technologies
 *
 * support@greenpeak.com
 * www.greenpeak.com
 *
 * This file is part of the GP kernel module.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _GP_H_
#define _GP_H_

#include <linux/ioctl.h>

#if !defined(GP_DIVERSITY_GPHAL_K5) && !defined(GP_DIVERSITY_GPHAL_K4) && !defined(GP_DIVERSITY_GPHAL_K3) && !defined(GP_DIVERSITY_GPHAL_K7C)
#if defined(GP712)
#define GP_DIVERSITY_GPHAL_K7C
#elif defined(GP501) || defined(GP711)
#define GP_DIVERSITY_GPHAL_K5
#elif defined(GP510) || defined(GP710)
#define GP_DIVERSITY_GPHAL_K4
#elif defined(GP500)
#define GP_DIVERSITY_GPHAL_K3
#else
#error error: you need to define a GP chip for which to compile for from this list {GP500, GP501, GP510, GP710, GP711, GP712}.
#endif
#endif

#define GP_IOC_MAGIC 'k'

/**
 *  Reset the GP chip via the RESETn pin. The host processor should create a pulse (transition low - high - low) on the RESETn pin.
 *  The ioctl has no parameters. When called, the interrupt of the GP chip is disabled and a pulse on the RESETn pin is created. After the pulse was created, any pending interrupt is cleared and the interrupt is enabled again.
 *
*/
#define GP_IOCRESET              _IO(GP_IOC_MAGIC, 0)

/**
 *  Wake up the GP chip from one of its sleep modes by creating a short pulse (1ms) on the WKUP pin. The host processor should create a pulse (transition low - high - low) on the WKUP pin.
 *  The ioctl has no parameters.
 *
*/
#define GP_IOCWAKEUP             _IO(GP_IOC_MAGIC, 1)

/**
 *  Read a register of the GP chip using the communication protocol as described in the datasheet. The host processor should transmit the read command ID and the register address it wants to read from.
 *  The GP chip will reply with a readconfirm status (indicating a failure or success) followed by the byte to read in case the readconfirm indicates success.
 *
 *  @ param readRegData     This ioctl has as parameter a structure from type gp50x_ReadRegData_t. It contains the register address to read from. The read value is stored in the byteRead member of the gp50x_ReadRegData_t structure.
 *  @ return                This ioctl returns 0 if the read was successful, an error code otherwise.
 *
*/
#define GP_IOCXREADREG           _IOWR(GP_IOC_MAGIC, 2, int)

/**
 *  Write a single byte to a register of the GP chip using the communication protocol as described in the datasheet. The host processor should transmit the write command ID and the register address it wants to write to followed by the byte to write.
 *  The GP chip will reply with a writeconfirm status (indicating a failure or success).
 *
 *  @ param writeRegData    This ioctl has as parameter a structure from type gp50x_WriteRegData_t. It contains the register address to write to and the byte to be written.
 *  @ return                This ioctl returns 0 if the write was successful, an error code otherwise.
 *
*/
#define GP_IOCSWRITEREG          _IOW (GP_IOC_MAGIC, 3, int)

/**
 *  Read a register of the GP chip using the communication protocol as described in the datasheet and modify it. Write back the modified value.
 *  The GP chip will reply with a confirm status (indicating a failure or success).
 *
 *  @ param readModWriteRegData  This ioctl has as parameter a structure from type gp50x_ReadModWriteRegData_t. It contains the register address to read from, the mask (the bits in the read byte to modify) and the new value.
 *  @ return                     This ioctl returns 0 if the command was successful, an error code otherwise.
 *
*/
#define GP_IOCSREADMODWRITEREG   _IOW (GP_IOC_MAGIC, 4, int)

/**
 *  Read a block of bytes from the GP chip using the communication protocol as described in the datasheet. The host processor should transmit the read bytestream command ID and the register address it wants to read from followed by the amount of bytes to read.
 *  The GP chip will reply with a readconfirm status (indicating a failure or success).
 *  The GP chip allows for reading maximum 'GP_MAXIMAL_BLOCKDATA' bytes in a single command. If the user space application issues this ioctl with a length exceeding GP_MAXIMAL_BLOCKDATA, the driver must ensure the total read is split up  into multiple readstream commands of maximum GP_MAXIMAL_BLOCKDATA length.
 *
 *  @ param readStreamData  This ioctl has as parameter a structure from type gp50x_ReadStreamData_t. It contains the register address to read from, the amount of bytes to read and a buffer to store the read bytes.
 *  @ return                This ioctl returns 0 if the read was successful, an error code otherwise.
 *
*/
#define GP_IOCXREADSTREAM        _IOWR(GP_IOC_MAGIC, 5, int)

/**
 *  Write a block of bytes to the GP chip using the communication protocol as described in the datasheet. The host processor should transmit the write bytestream command ID and the register address it wants to write to followed by the length and the bytes to write.
 *  The GP chip will reply with a writeconfirm status (indicating a failure or success).
 *  The GP chip allows for writing maximum 'GP_MAXIMAL_BLOCKDATA' bytes in a single command. If the user space application issues this ioctl with a length exceeding GP_MAXIMAL_BLOCKDATA, the driver must ensure the total write is split up  into multiple writes of maximum GP_MAXIMAL_BLOCKDATA length.
 *
 *  @ param writeStreamData This ioctl has as parameter a structure from type gp50x_WriteStreamData_t. It contains the register address to write to, the amount of bytes to write and the bytes to be written.
 *  @ return                This ioctl returns 0 if the write was successful, an error code otherwise.
 *
*/
#define GP_IOCSWRITESTREAM       _IOW (GP_IOC_MAGIC, 6, int)

/**
 *  Enable/Disable the interrupts from the GP chip.
 *
 *  @ param enable      This ioctl has as parameter an integer. 0 is used to disable the interrupts from the GP chip. 1 enables them.
 *  @ return            This ioctl returns 0 if the command was successful, an error code otherwise.
 *
*/
#define GP_IOCSENABLEINT         _IOW (GP_IOC_MAGIC, 7, int)

#define GP_IOC_MAXNR             _IOC_NR(GP_IOCSENABLEINT)

#if defined(GP_DIVERSITY_GPHAL_K7C)
typedef unsigned long address_t;
#else
typedef unsigned short address_t;
#endif

typedef struct {
	address_t  address;
	unsigned char   byteRead;
} gp_ReadRegData_t;

typedef struct {
	address_t  address;
	unsigned char   byteWrite;
} gp_WriteRegData_t;

typedef struct {
	address_t  address;
	unsigned char   mask;
	unsigned char   byteWrite;
} gp_ReadModWriteRegData_t;

typedef struct {
	address_t  address;
	unsigned int    length;
	unsigned char  *bufferRead;
} gp_ReadStreamData_t;

typedef struct {
	address_t  address;
	unsigned int    length;
	unsigned char  *bufferWrite;
} gp_WriteStreamData_t;

#ifdef CONFIG_COMPAT
#include <linux/compat.h>

#if defined(GP_DIVERSITY_GPHAL_K7C)
typedef compat_ulong_t compat_address_t;
#else
typedef compat_ushort_t compat_address_t;
#endif

typedef struct {
	compat_address_t  address;
	unsigned char     byteRead;
} compat_gp_ReadRegData_t;

typedef struct {
	compat_address_t  address;
	unsigned char     byteWrite;
} compat_gp_WriteRegData_t;

typedef struct {
	compat_address_t  address;
	unsigned char     mask;
	unsigned char     byteWrite;
} compat_gp_ReadModWriteRegData_t;

typedef struct {
	compat_address_t  address;
	compat_uint_t     length;
	compat_uptr_t     bufferRead;
} compat_gp_ReadStreamData_t;

typedef struct {
	compat_address_t  address;
	compat_uint_t     length;
	compat_uptr_t     bufferWrite;
} compat_gp_WriteStreamData_t;
#endif //CONFIG_COMPAT

#endif /* _GP_H_ */

