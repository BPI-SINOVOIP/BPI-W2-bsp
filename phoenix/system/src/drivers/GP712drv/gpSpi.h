/*
 * $Header: //depot/release/Embedded/BaseComps/v2.4.5.0/sw/comps/halLinux/kernel/GP_Generic_Driver/gpSpi.h#1 $
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

#include <linux/spi/spi.h>


#if defined(GP_DIVERSITY_GPHAL_K5) || defined(GP_DIVERSITY_GPHAL_K7C)
#define GP_MAXIMAL_BLOCKDATA                127
#elif defined(GP_DIVERSITY_GPHAL_K3) || defined(GP_DIVERSITY_GPHAL_K4)
#define GP_MAXIMAL_BLOCKDATA                32
#endif

#if defined(GP_DIVERSITY_GPHAL_K7C)
#define GP_MSI_READCMD                      0x00
#define GP_MSI_WRITECMD                     0x40
#define GP_MSI_BLOCKCMD                     0x80
#define GP_MSI_MASKEDWRITECMD               0xC0
#define GP_MSI_BLOCKREADCMD                 GP_MSI_BLOCKCMD
#define GP_MSI_BLOCKWRITECMD                GP_MSI_BLOCKCMD
#define GP_MSI_BLOCKREADEXTCMD              0x00  // GP_MSI_BLOCKREADCMD
#define GP_MSI_BLOCKWRITEEXTCMD             0x80  // GP_MSI_BLOCKWRITECMD

#elif defined(GP_DIVERSITY_GPHAL_K5)
#define GP_MSI_READCMD                      0x00
#define GP_MSI_WRITECMD                     0x40
#define GP_MSI_MASKEDWRITECMD               0xC0
#define GP_MSI_BLOCKREADCMD                 0x80
#define GP_MSI_BLOCKWRITECMD                0x80
#define GP_MSI_BLOCKREADEXTCMD              0x00
#define GP_MSI_BLOCKWRITEEXTCMD             0x80

#elif defined(GP_DIVERSITY_GPHAL_K4)
#define GP_MSI_READCMD                      0x00
#define GP_MSI_WRITECMD                     0x40
#define GP_MSI_BLOCKREADCMD                 0x80
#define GP_MSI_BLOCKWRITECMD                0xC0
#define GP_MSI_BLOCKREADEXTCMD              0x00
#define GP_MSI_BLOCKWRITEEXTCMD             0x00

#elif defined(GP_DIVERSITY_GPHAL_K3)
#define GP_MSI_READCMD                      0x56
#define GP_MSI_WRITECMD                     0x57
#define GP_MSI_BLOCKREADCMD                 0x58
#define GP_MSI_BLOCKWRITECMD                0x59
#define GP_MSI_BLOCKREADEXTCMD              0x00
#define GP_MSI_BLOCKWRITEEXTCMD             0x00
#endif

#define GP_MSI_WRITECONFIRM                 0x01
#define GP_MSI_READCONFIRM                  0x03
#define GP_MSI_WRITEBLOCKCONFIRM            0x05
#define GP_MSI_READBLOCKCONFIRM             0x07
#define GP_MSI_MASKEDWRITECONFIRM           0x01

#ifdef GP_DIVERSITY_GPHAL_K3
#define     GP_MSI_COMMAND_OVERHEAD           1
#elif defined(GP_DIVERSITY_GPHAL_K4) || defined(GP_DIVERSITY_GPHAL_K5) || defined(GP_DIVERSITY_GPHAL_K7C)
#define     GP_MSI_COMMAND_OVERHEAD           0
#endif

/** @brief Read register function.
 *
 *  This is the function for reading registers.
 *
 *  Depending on the GreenPeak chip used, access to the registers is using SPI, I2C or UART.
 *  The protocol for the transaction is described in detail in the GreenPeak chip datasheet.
 *
 *  @param spi_device        Pointer to the spi_device used for the transaction.
 *
 *  @param readRegData       Pointer to a structure of type gp_ReadRegData_t which contains the address of the register to read
 *                          and a pointer to store the read data.
*/
int readRegExternal(struct spi_device *spi_device, gp_ReadRegData_t *readRegData, u8 gpio_ssn_pin, bool debug);

/** @brief Write register function.
 *
 *  This is the function for writing a value to the registers of the GreenPeak chip.
 *
 *  Depending on the GreenPeak chip used, access to the registers is using SPI, I2C or UART.
 *  The protocol for the transaction is described in detail in the GreenPeak chip datasheet.
 *
 *  @param spi_device       Pointer to the spi_device used for the transaction.
 *
 *  @param writeRegData     Pointer to a structure of type gp_WriteRegData_t which contains the address of the register to write
 *                          and a pointer to the data to be written.
*/
int writeRegExternal(struct spi_device *spi_device, gp_WriteRegData_t *writeRegData, u8 gpio_ssn_pin, bool debug);

/** @brief Read block of registers function.
 *
 *  This is the function for reading an array of data from a block of registers of the GreenPeak chip.
 *
 *  Depending on the GreenPeak chip used, access to the registers is using SPI, I2C or UART.
 *  The protocol for the transaction is described in detail in the GreenPeak chip datasheet.
 *
 *  @param spi_device       Pointer to the spi_device used for the transaction.
 *
 *  @param readStreamData   Pointer to a structure of type gp_ReadStreamData_t which contains the start address of the block of registers to read
 *                          the length of the block, and a pointer to an array where the read data can be stored..
*/
int readByteStreamExternal(struct spi_device *spi_device, gp_ReadStreamData_t *readStreamData, u8 gpio_ssn_pin, bool debug);

/** @brief Write block of registers function.
 *
 *  This is the function for writing an array of data to a block of registers of the GreenPeak chip.
 *
 *  Depending on the GreenPeak chip used, access to the registers is using SPI, I2C or UART.
 *  The protocol for the transaction is described in detail in the GreenPeak chip datasheet.
 *
 *  @param spi_device       Pointer to the spi_device used for the transaction.
 *
 *  @param writeStreamData  Pointer to a structure of type gp_WriteStreamData_t which contains the start address of the block of registers to write
 *                          the length of the block, and a pointer to the data to be written.
*/
int writeByteStreamExternal(struct spi_device *spi_device, gp_WriteStreamData_t *writeStreamData, u8 gpio_ssn_pin, bool debug);

#if defined(GP_DIVERSITY_GPHAL_K5)
/** @brief Write a property.
 *
 *  This is the function for writing a property (masked register) of the GreenPeak chip.
 *
 *  Depending on the GreenPeak chip used, access to the registers is using SPI, I2C or UART.
 *  The protocol for the transaction is described in detail in the GreenPeak chip datasheet.
 *
 *  @param spi_device       Pointer to the spi_device used for the transaction.
 *
 *  @param readModWriteRegData  Pointer to a structure of type gp_ReadModWriteRegData_t which contains the address of the register,
 *                              the mask and a pointer to the data to be written in the masked value.
*/
int writeMaskedByteStreamExternal(struct spi_device *spi_device, gp_ReadModWriteRegData_t *readModWriteRegData, u8 gpio_ssn_pin, bool debug);
#endif
