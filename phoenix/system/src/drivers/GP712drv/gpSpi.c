/*
 * $Header: //depot/release/Embedded/BaseComps/v2.4.5.0/sw/comps/halLinux/kernel/GP_Generic_Driver/gpSpi.c#1 $
 * $Change: 68365 $
 * $DateTime: 2015/07/31 10:23:51 $
 * Copyright (C) 2014, GreenPeak Technologies
 *
 * support@greenpeak.com
 * www.greenpeak.com
 *
 * This file is part of the GP kernel module. This file contains the implementation of the
 * SPI protocol between master processor and GP chip (K5 family).
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * Alternatively, see http://www.gnu.org/licenses/gpl-2.0.txt
 */

#include "gpCore.h"
#include "gpSpi.h"
#include "gpIo.h"
#include "gpPinout.h"

#include <linux/uaccess.h>
#include <linux/module.h>

#ifdef GP_DIVERSITY_GPHAL_K7C
#define GPHAL_MSI_IDLE_BYTE  0xa5
#define BYTE_STREAM_TX_HEADER  GP_MSI_COMMAND_OVERHEAD + 3
#else
#define GPHAL_MSI_IDLE_BYTE  0x00
#define BYTE_STREAM_TX_HEADER  GP_MSI_COMMAND_OVERHEAD + 2
#endif

static  const   u8      max_retry   = GP_SPI_MAX_NUMBER_OF_RETRIES; 
extern          u8      gpio_ssn_pin;
/*
 * Remark regarding the cs_change flag in struct spi_transfer.
 *
 * All SPI transfers start with the relevant chipselect active.  Normally
 * it stays selected until after the last transfer in a message.  Drivers
 * can affect the chipselect signal using cs_change.
 *
 * The normal behaviour is:
 *   * After all transfers except the last: chipselect stays active
 *   * After the last transfer: chipselect goes inactive
 *
 * The cs_change flag is used to change the default behaviour.
 * If the transfer isn't the last one in the message, this flag is
 * set to make the chipselect briefly go inactive in the middle of the
 * message.
 * For the last transfer in the message, the cs_change flag is set to
 * indicate that the chipselect should stay active after the transfer
 * (though the driver may not actually be able to do so, e.g. if
 * the message is followed by a message to a different device.)
 */

int readRegExternal(struct spi_device *spi_device, gp_ReadRegData_t *readRegData, u8 gpio_ssn_pin, bool debug)
{
    struct spi_message   msg;
    struct spi_transfer  xfer[2];
    unsigned char        tx_buf[BYTE_STREAM_TX_HEADER];
    unsigned char        rx_buf[3];
    u8                   retry = 0;
    int                  error = 0;

    spi_message_init(&msg);
    memset(xfer, 0, sizeof(xfer));
    memset(tx_buf, 0, sizeof(tx_buf));
    memset(rx_buf, 0, sizeof(rx_buf));
    rx_buf[1] = GPHAL_MSI_IDLE_BYTE;

    /* Write command and 16-bit address */
    tx_buf[0]                           = (GP_MSI_READCMD);
#ifdef GP_DIVERSITY_GPHAL_K7C
    tx_buf[GP_MSI_COMMAND_OVERHEAD]     |= ((readRegData->address >> 16) & 0xff);
    tx_buf[GP_MSI_COMMAND_OVERHEAD + 1]  = ((readRegData->address >> 8) & 0xff);
    tx_buf[GP_MSI_COMMAND_OVERHEAD + 2]  = readRegData->address & 0xff;
#else
    tx_buf[GP_MSI_COMMAND_OVERHEAD]    |= ((readRegData->address >> 8) & 0xff);
    tx_buf[GP_MSI_COMMAND_OVERHEAD + 1] =  readRegData->address       & 0xff;
 #endif

    xfer[0].tx_buf    = tx_buf;
    xfer[0].rx_buf    = NULL;
    xfer[0].len       = BYTE_STREAM_TX_HEADER;
    xfer[0].cs_change = 0; /* Keep default behaviour, cfr. remark */
    spi_message_add_tail(&xfer[0], &msg);

    /* Read zero byte and event code */
    xfer[1].tx_buf    = NULL;
    xfer[1].rx_buf    = rx_buf;
    xfer[1].len       = 2;
    xfer[1].cs_change = 1; /* Change default behaviour, cfr. remark */
    spi_message_add_tail(&xfer[1], &msg);
    
    gp_Set_SSN_Line(gpio_ssn_pin, 0);

    error = spi_sync(spi_device, &msg);
    if (error)
    {
        goto disable_cs;
    }
    
    if (rx_buf[0] != GPHAL_MSI_IDLE_BYTE)
    {
        /* We expect at least 1 zero byte. If we get here, this means that reading this zero byte failed */
        if (debug)
        {
            printk(KERN_ERR "GP: %s, First received byte is %#04x, expected %#04x\n", __func__, rx_buf[0], GPHAL_MSI_IDLE_BYTE);
        }
        error = -EIO;
        goto disable_cs;
    }

    while (rx_buf[1] == GPHAL_MSI_IDLE_BYTE && retry < max_retry)
    {
        /* Try reading out the event/synchronization code*/
        retry++;

        spi_message_init(&msg);
        memset(&xfer[0], 0, sizeof(xfer[0]));

        xfer[0].tx_buf    = NULL;
        xfer[0].rx_buf    = rx_buf + 1;
        xfer[0].len       = 1;
        xfer[0].cs_change = 1; /* Change default behaviour, cfr. remark */
        spi_message_add_tail(&xfer[0], &msg);

        error = spi_sync(spi_device, &msg);
        if (error)
        {
            goto disable_cs;
        }
    }

    if (debug)
    {
        if (retry)
        {
            printk(KERN_INFO "GP: %s, Retried %u time(s) to receive event code\n",__func__, retry);
        }    
    }
    /* Received event code */
    if (rx_buf[1] != GP_MSI_READCONFIRM)
    {
        if (debug)
        {
            printk(KERN_ERR "GP: %s, Received event code is %#04x, expected %#04x\n",__func__, rx_buf[1], GP_MSI_READCONFIRM);
        }
        error = -EIO;
        goto disable_cs;
    }

    /* Read register value */
    spi_message_init(&msg);
    memset(&xfer[0], 0, sizeof(xfer[0]));

    xfer[0].tx_buf    = NULL;
    xfer[0].rx_buf    = rx_buf + 2;
    xfer[0].len       = 1;
    xfer[0].cs_change = 0; /* Keep default behaviour, cfr. remark */
    spi_message_add_tail(&xfer[0], &msg);

    error = spi_sync(spi_device, &msg);
    if (error)
    {
        goto exit;
    }
    
    if (debug) 
    {
    
        if(GP_MSI_COMMAND_OVERHEAD == 0)
        {
            printk(KERN_INFO "GP: %s, TX: |%#04x:%#04x|\n",__func__,tx_buf[0], tx_buf[1]);
        }
        else
        {
            printk(KERN_INFO "GP: %s, TX: |%#04x:%#04x:%#04x|\n",__func__,tx_buf[0], tx_buf[1], tx_buf[2]);
        }
        printk(KERN_INFO "GP: %s, RX: |%#04x:%#04x:%#04x|\n",__func__,rx_buf[0], rx_buf[1], rx_buf[2]);
    }

    readRegData->byteRead = rx_buf[2];
    goto exit;

disable_cs:
    spi_message_init(&msg);
    memset(&xfer[0], 0, sizeof(xfer[0]));
    spi_message_add_tail(&xfer[0], &msg);
    spi_sync(spi_device, &msg);

exit:
    if (error) 
    {
        printk(KERN_ERR "%s() from address %#06x failed\n",__func__,(unsigned int)readRegData->address);
        printk(KERN_ERR "Response is '%#04x %#04x %#04x'\n",rx_buf[0],rx_buf[1],rx_buf[2]);
    }
    gp_Set_SSN_Line(gpio_ssn_pin, 1);

    return error;
}

int writeRegExternal(struct spi_device *spi_device, gp_WriteRegData_t *writeRegData, u8 gpio_ssn_pin, bool debug)
{
    struct spi_message   msg;
    struct spi_transfer  xfer[2];
    unsigned char        tx_buf[BYTE_STREAM_TX_HEADER + 1];
    unsigned char        rx_buf[2];
    u8                   retry = 0;
    int                  error = 0;

    spi_message_init(&msg);
    memset(tx_buf, 0, sizeof(tx_buf));
    memset(rx_buf, 0, sizeof(rx_buf));
    memset(xfer, 0, sizeof(xfer));
    rx_buf[1] = GPHAL_MSI_IDLE_BYTE;

    /* Write command, 16-bit address and value */
    tx_buf[0]                           = (GP_MSI_WRITECMD) ;
#ifdef GP_DIVERSITY_GPHAL_K7C
    tx_buf[GP_MSI_COMMAND_OVERHEAD]     |= ((writeRegData->address >> 16) & 0xff);
    tx_buf[GP_MSI_COMMAND_OVERHEAD + 1]  = ((writeRegData->address >> 8) & 0xff);
    tx_buf[GP_MSI_COMMAND_OVERHEAD + 2]  = writeRegData->address & 0xff;
    tx_buf[GP_MSI_COMMAND_OVERHEAD + 3]  = writeRegData->byteWrite;
#else
    tx_buf[GP_MSI_COMMAND_OVERHEAD]    |= ((writeRegData->address >> 8) & 0xff);
    tx_buf[GP_MSI_COMMAND_OVERHEAD + 1] =  writeRegData->address       & 0xff;
    tx_buf[GP_MSI_COMMAND_OVERHEAD + 2] =  writeRegData->byteWrite;
#endif
    xfer[0].tx_buf    = tx_buf;
    xfer[0].rx_buf    = NULL;
    xfer[0].len       = BYTE_STREAM_TX_HEADER + 1;
    xfer[0].cs_change = 0; /* Keep default behaviour, cfr. remark */
    spi_message_add_tail(&xfer[0], &msg);

    /* Read zero byte and event code */
    xfer[1].tx_buf    = NULL;
    xfer[1].rx_buf    = rx_buf;
    xfer[1].len       = 2;
    xfer[1].cs_change = 1; /* Change default behaviour, cfr. remark */
    spi_message_add_tail(&xfer[1], &msg);

    gp_Set_SSN_Line(gpio_ssn_pin, 0);

    error = spi_sync(spi_device, &msg);
    if (error)
    {
        goto disable_cs;
    } 
    
    if (rx_buf[0] != GPHAL_MSI_IDLE_BYTE)
    {
        /* We expect at least 1 zero byte. If we get here, this means that reading this zero byte failed */
        if (debug)
        {
            printk(KERN_ERR "GP: %s, First received byte is %#04x, expected %#04x\n", __func__, rx_buf[0], GPHAL_MSI_IDLE_BYTE);
        }
        error = -EIO;
        goto disable_cs;
    }

    while (rx_buf[1] == GPHAL_MSI_IDLE_BYTE && retry < max_retry)
    {
        /* Try reading out the event/synchronization code*/
        retry++;

        spi_message_init(&msg);
        memset(&xfer[0], 0, sizeof(xfer[0]));

        xfer[0].tx_buf    = NULL;
        xfer[0].rx_buf    = rx_buf + 1;
        xfer[0].len       = 1;
        xfer[0].cs_change = 1; /* Change default behaviour, cfr. remark */
        spi_message_add_tail(&xfer[0], &msg);

        error = spi_sync(spi_device, &msg);
        if (error)
        {
            goto disable_cs;
        }
    }
    if (debug)
    {
        if (retry)
        {
            printk(KERN_INFO "GP: %s, Retried %u time(s) to receive event code\n",__func__, retry);
        }    
    }
    /* Received event code */
    if (rx_buf[1] != GP_MSI_WRITECONFIRM)
    {
        if (debug)
        {
            printk(KERN_ERR "GP: %s, Received event code is %#04x, expected %#04x\n",__func__, rx_buf[1], GP_MSI_WRITECONFIRM);
        }
        error = -EIO;
        goto disable_cs;
    }
        
    if (debug) 
    {
        if(GP_MSI_COMMAND_OVERHEAD == 0)
        {
            printk(KERN_INFO "GP: %s, TX: |%#04x:%#04x:%#04x|\n",__func__,tx_buf[0], tx_buf[1], tx_buf[2]);
        }
        else
        {
            printk(KERN_INFO "GP: %s, TX: |%#04x:%#04x:%#04x:%#04x|\n",__func__,tx_buf[0], tx_buf[1], tx_buf[2], tx_buf[3]);
        }
        printk(KERN_INFO "GP: %s, RX: |%#04x:%#04x|\n",__func__,rx_buf[0], rx_buf[1]);
    }
    
disable_cs:
    spi_message_init(&msg);
    memset(&xfer[0], 0, sizeof(xfer[0]));
    spi_message_add_tail(&xfer[0], &msg);
    spi_sync(spi_device, &msg);
 
    if (error) 
    {
        printk(KERN_ERR "%s() to address %#06x with value %#04x failed\n",__func__,(unsigned int)writeRegData->address, (unsigned int)writeRegData->byteWrite);
        printk(KERN_ERR "Response is '%#04x %#04x '\n",rx_buf[0],rx_buf[1]);
    }
    gp_Set_SSN_Line(gpio_ssn_pin, 1);
    
    return error;
}

int readByteStreamExternal(struct spi_device *spi_device, gp_ReadStreamData_t *readStreamData, u8 gpio_ssn_pin, bool debug)
{

    struct spi_message   msg;
    struct spi_transfer  xfer[2];
    unsigned char        tx_buf[BYTE_STREAM_TX_HEADER + 1];
    unsigned char        rx_buf[2 + GP_MAXIMAL_BLOCKDATA];
    address_t            address;
    unsigned int         length;
    unsigned char       *bufferRead;
    unsigned int         n;
    u8                   retry = 0;
    int                  error = 0;

    address    = readStreamData->address;
    length     = readStreamData->length;
    bufferRead = readStreamData->bufferRead;

    while (length > 0)
    {

        spi_message_init(&msg);
        memset(xfer, 0, sizeof(xfer));
        memset(tx_buf, 0, sizeof(tx_buf));
        memset(rx_buf, 0, sizeof(rx_buf));
        rx_buf[1] = GPHAL_MSI_IDLE_BYTE;

        n = length < GP_MAXIMAL_BLOCKDATA ? length : GP_MAXIMAL_BLOCKDATA;

        /* Write command, length and 16-bit address */
        
        tx_buf[0]                            = (GP_MSI_BLOCKREADCMD);
#ifdef GP_DIVERSITY_GPHAL_K3
        tx_buf[GP_MSI_COMMAND_OVERHEAD ]     = n; 
        tx_buf[GP_MSI_COMMAND_OVERHEAD + 1]  = ((address >> 8) & 0xff);
        tx_buf[GP_MSI_COMMAND_OVERHEAD + 2]  = address & 0xff;
#elif defined(GP_DIVERSITY_GPHAL_K7C)
        tx_buf[GP_MSI_COMMAND_OVERHEAD]     |= ((address >> 16) & 0xff);
        tx_buf[GP_MSI_COMMAND_OVERHEAD + 1]  = ((address >> 8) & 0xff);
        tx_buf[GP_MSI_COMMAND_OVERHEAD + 2]  = address & 0xff;
        tx_buf[GP_MSI_COMMAND_OVERHEAD + 3]  = (GP_MSI_BLOCKREADEXTCMD) | (n  & 0x7F);
#else
        tx_buf[GP_MSI_COMMAND_OVERHEAD]     |= ((address >> 8) & 0xff);
        tx_buf[GP_MSI_COMMAND_OVERHEAD + 1]  = address & 0xff;
        tx_buf[GP_MSI_COMMAND_OVERHEAD + 2]  = (GP_MSI_BLOCKREADEXTCMD) | (n  & 0x7F);
#endif
        xfer[0].tx_buf    = tx_buf;
        xfer[0].rx_buf    = NULL;
        xfer[0].len       = BYTE_STREAM_TX_HEADER + 1;
        xfer[0].cs_change = 0; /* Keep default behaviour, cfr. remark */
        spi_message_add_tail(&xfer[0], &msg);

        /* Read zero byte, event code */
        xfer[1].tx_buf    = NULL;
        xfer[1].rx_buf    = rx_buf;
        xfer[1].len       = 2;
        xfer[1].cs_change = 1; /* Change default behaviour, cfr. remark */
        spi_message_add_tail(&xfer[1], &msg);

        gp_Set_SSN_Line(gpio_ssn_pin, 0);

        error = spi_sync(spi_device, &msg);
        if (error)
        {
            goto disable_cs;
        }
        
        if (rx_buf[0] != GPHAL_MSI_IDLE_BYTE)
        {
            /* We expect at least 1 zero byte. If we get here, this means that reading this zero byte failed */
            if (debug)
            {
                printk(KERN_ERR "GP: %s, First received byte is %#04x, expected %#04x\n", __func__, rx_buf[0], GPHAL_MSI_IDLE_BYTE);
            }
            error = -EIO;
            goto disable_cs;
        }
        retry = 0;
        while (rx_buf[1] == GPHAL_MSI_IDLE_BYTE && retry < max_retry)
        {
            /* Try reading out the event/synchronization code*/
            retry++;

            spi_message_init(&msg);
            memset(&xfer[0], 0, sizeof(xfer[0]));

            xfer[0].tx_buf    = NULL;
            xfer[0].rx_buf    = rx_buf + 1;
            xfer[0].len       = 1;
            xfer[0].cs_change = 1; /* Change default behaviour, cfr. remark */
            spi_message_add_tail(&xfer[0], &msg);

            error = spi_sync(spi_device, &msg);
            if (error)
            {
                goto disable_cs;
            }
        }

        if (debug)
        {
            if (retry)
            {
                printk(KERN_INFO "GP: %s, Retried %u time(s) to receive event code\n",__func__, retry);
            }    
        }
        /* Received event code */
        if (rx_buf[1] != GP_MSI_READBLOCKCONFIRM)
        {
            if (debug)
            {
                printk(KERN_ERR "GP: %s, Received event code is %#04x, expected %#04x\n",__func__, rx_buf[1], GP_MSI_READBLOCKCONFIRM);
            }
            error = -EIO;
            goto disable_cs;
        }
            
        /* Read block data */
        spi_message_init(&msg);
        memset(&xfer[0], 0, sizeof(xfer[0]));

        xfer[0].tx_buf    = NULL;
        xfer[0].rx_buf    = rx_buf + 2;
        xfer[0].len       = n;
        xfer[0].cs_change = 0; /* Keep default behaviour, cfr. remark */
        spi_message_add_tail(&xfer[0], &msg);

        error = spi_sync(spi_device, &msg);
        if (error)
        {
            goto exit;
        }       
        if (debug) 
        {
            unsigned int i;          
            if(GP_MSI_COMMAND_OVERHEAD == 0)
            {
                printk(KERN_INFO "GP: %s, TX: |%#04x:%#04x:%#04x|\n",__func__,tx_buf[0], tx_buf[1], tx_buf[2]);
            }
            else
            {
                printk(KERN_INFO "GP: %s, TX: |%#04x:%#04x:%#04x:%#04x|\n",__func__,tx_buf[0], tx_buf[1], tx_buf[2], tx_buf[3]);
            }
            printk(KERN_INFO "GP: %s, RX: |%#04x:%#04x:%#04x|\n",__func__,rx_buf[0], rx_buf[1], rx_buf[2]);
             
            for (i = 1; i < n; i++)
            {
                printk(KERN_CONT " %#04x", rx_buf[2 + i]);
            }
            printk(KERN_CONT "|\n");
        }

        error = copy_to_user(bufferRead, &rx_buf[2], n);
        if (error)
        {
            goto exit;
        }
        gp_Set_SSN_Line(gpio_ssn_pin, 1);

        address    += n;
        length     -= n;
        bufferRead += n;
    }

    goto exit;

disable_cs:
    spi_message_init(&msg);
    memset(&xfer[0], 0, sizeof(xfer[0]));
    spi_message_add_tail(&xfer[0], &msg);
    spi_sync(spi_device, &msg);

exit:
    if (error) 
    {
        printk(KERN_ERR "%s() from address %#06x with length %#04x failed\n",__func__,(unsigned int)readStreamData->address, (unsigned int)readStreamData->length);
        printk(KERN_ERR "Response is '%#04x %#04x '\n",rx_buf[0],rx_buf[1]);
    }

    gp_Set_SSN_Line(gpio_ssn_pin, 1);
    return error;
}

int writeByteStreamExternal(struct spi_device *spi_device, gp_WriteStreamData_t *writeStreamData, u8 gpio_ssn_pin, bool debug)
{
    struct spi_message   msg;
    struct spi_transfer  xfer[2];
    unsigned char        tx_buf[BYTE_STREAM_TX_HEADER + 1 + GP_MAXIMAL_BLOCKDATA];
    unsigned char        rx_buf[2];
    address_t            address;
    unsigned int         length;
    unsigned char       *bufferWrite;
    unsigned int         n;
    u8                   retry = 0;
    int                  error;

    address     = writeStreamData->address;
    length      = writeStreamData->length;
    bufferWrite = writeStreamData->bufferWrite;

    while (length > 0) 
    {
        spi_message_init(&msg);
        memset(xfer, 0, sizeof(xfer));
        memset(tx_buf, 0, sizeof(tx_buf));
        memset(rx_buf, 0, sizeof(rx_buf));
        rx_buf[1] = GPHAL_MSI_IDLE_BYTE;

        n = length < GP_MAXIMAL_BLOCKDATA ? length : GP_MAXIMAL_BLOCKDATA;

        /* Write command, length, 16-bit address and block data */
        tx_buf[0]                            = (GP_MSI_BLOCKWRITECMD);
#ifdef GP_DIVERSITY_GPHAL_K3
        tx_buf[GP_MSI_COMMAND_OVERHEAD ]     = n; 
        tx_buf[GP_MSI_COMMAND_OVERHEAD + 1]  = ((address >> 8) & 0xff);
        tx_buf[GP_MSI_COMMAND_OVERHEAD + 2]  = address & 0xff;
#elif defined(GP_DIVERSITY_GPHAL_K7C)
        tx_buf[GP_MSI_COMMAND_OVERHEAD]     |= ((address >> 16) & 0xff);
        tx_buf[GP_MSI_COMMAND_OVERHEAD + 1]  = ((address >> 8) & 0xff);
        tx_buf[GP_MSI_COMMAND_OVERHEAD + 2]  = address & 0xff;
        tx_buf[GP_MSI_COMMAND_OVERHEAD + 3]  = (GP_MSI_BLOCKWRITEEXTCMD) | (n  & 0x7F);
#else
        tx_buf[GP_MSI_COMMAND_OVERHEAD]     |= ((address >> 8) & 0xff);
        tx_buf[GP_MSI_COMMAND_OVERHEAD + 1]  = address & 0xff;
        tx_buf[GP_MSI_COMMAND_OVERHEAD + 2]  = (GP_MSI_BLOCKWRITEEXTCMD) | (n  & 0x7F);
#endif
        error = copy_from_user(&tx_buf[BYTE_STREAM_TX_HEADER + 1], bufferWrite, n);
        
        if (error)
        {
            goto exit;
        }
        xfer[0].tx_buf    = tx_buf;
        xfer[0].rx_buf    = NULL;
        xfer[0].len       = BYTE_STREAM_TX_HEADER + 1 + n;
        xfer[0].cs_change = 0; /* Keep default behaviour, cfr. remark */
        spi_message_add_tail(&xfer[0], &msg);

        /* Read zero byte and event code */
        xfer[1].tx_buf    = NULL;
        xfer[1].rx_buf    = rx_buf;
        xfer[1].len       = 2;
        xfer[1].cs_change = 1; /* Change default behaviour, cfr. remark */
        spi_message_add_tail(&xfer[1], &msg);

        gp_Set_SSN_Line(gpio_ssn_pin, 0);

        error = spi_sync(spi_device, &msg);
        if (error)
        {
            goto disable_cs;
        }
        
        if (rx_buf[0] != GPHAL_MSI_IDLE_BYTE)
        {
            /* We expect at least 1 zero byte. If we get here, this means that reading this zero byte failed */
            if (debug)
            {
                printk(KERN_ERR "GP: %s, First received byte is %#04x, expected %#04x\n", __func__, rx_buf[0], GPHAL_MSI_IDLE_BYTE);
            }
            error = -EIO;
            goto disable_cs;
        }
        retry = 0;
        while (rx_buf[1] == GPHAL_MSI_IDLE_BYTE && retry < max_retry)
        {
            /* Try reading out the event/synchronization code*/
            retry++;

            spi_message_init(&msg);
            memset(&xfer[0], 0, sizeof(xfer[0]));

            xfer[0].tx_buf    = NULL;
            xfer[0].rx_buf    = rx_buf + 1;
            xfer[0].len       = 1;
            xfer[0].cs_change = 1; /* Change default behaviour, cfr. remark */
            spi_message_add_tail(&xfer[0], &msg);

            error = spi_sync(spi_device, &msg);
            if (error)
            {
                goto disable_cs;
            }
        }

        if (debug)
        {
            if (retry)
            {
                printk(KERN_INFO "GP: %s, Retried %u time(s) to receive event code\n",__func__, retry);
            }    
        }
        /* Received event code */        
        if (rx_buf[1] != GP_MSI_WRITEBLOCKCONFIRM)
        {
            if (debug)
            {
                printk(KERN_ERR "GP: %s, Received event code is %#04x, expected %#04x\n",__func__, rx_buf[1], GP_MSI_WRITEBLOCKCONFIRM);
            }
            error = -EIO;
            goto disable_cs;
        }
       
        if (debug) 
        {
            unsigned int i;          
            if(GP_MSI_COMMAND_OVERHEAD == 0)
            {
                printk(KERN_INFO "GP: %s, TX: |%#04x:%#04x:%#04x|\n",__func__,tx_buf[0], tx_buf[1], tx_buf[2]);
            }
            else
            {
                printk(KERN_INFO "GP: %s, TX: |%#04x:%#04x:%#04x:%#04x|\n",__func__,tx_buf[0], tx_buf[1], tx_buf[2], tx_buf[3]);
            }
            for (i = 0; i < n; i++)
            {
                printk(KERN_CONT " %#04x", tx_buf[4 + i]);
            }
            printk(KERN_CONT "|\n");
            
            printk(KERN_INFO "GP: %s, RX: |%#04x:%#04x|\n",__func__,rx_buf[0], rx_buf[1]);
        }

        /* Disable the chip select for next block transfer */
        spi_message_init(&msg);
        memset(&xfer[0], 0, sizeof(xfer[0]));
        spi_message_add_tail(&xfer[0], &msg);
        spi_sync(spi_device, &msg);

        gp_Set_SSN_Line(gpio_ssn_pin, 1);

        address     += n;
        length      -= n;
        bufferWrite += n;
    }

    goto exit;

disable_cs:
    spi_message_init(&msg);
    memset(&xfer[0], 0, sizeof(xfer[0]));

    spi_message_add_tail(&xfer[0], &msg);

    spi_sync(spi_device, &msg);

    gp_Set_SSN_Line(gpio_ssn_pin, 1);

exit:
    if (error) 
    {
        printk(KERN_ERR "%s() to address %#06x with length %#04x failed\n",__func__,(unsigned int)writeStreamData->address, (unsigned int)writeStreamData->length);
        printk(KERN_ERR "Response is '%#04x %#04x '\n",rx_buf[0],rx_buf[1]);
    }

    gp_Set_SSN_Line(gpio_ssn_pin, 1);

    return error;
}
#if defined(GP_DIVERSITY_GPHAL_K5)
int writeMaskedByteStreamExternal(struct spi_device *spi_device, gp_ReadModWriteRegData_t *readModWriteRegData, u8 gpio_ssn_pin, bool debug)
{

    struct spi_message   msg;
    struct spi_transfer  xfer[2];
    unsigned char        tx_buf[GP_MSI_COMMAND_OVERHEAD + 4];
    unsigned char        rx_buf[2];
    address_t            address;
    unsigned char          mask;
    unsigned char         byteWrite;
    u8                   retry = 0;
    int                  error;

    address     = readModWriteRegData->address;
    mask         = readModWriteRegData->mask;
    byteWrite   = readModWriteRegData->byteWrite;

    spi_message_init(&msg);
    memset(xfer, 0, sizeof(xfer));
    memset(tx_buf, 0, sizeof(tx_buf));
    memset(rx_buf, 0, sizeof(rx_buf));

    /* Write command, length, 16-bit address and block data */
    tx_buf[0]                           = (GP_MSI_MASKEDWRITECMD);
    tx_buf[GP_MSI_COMMAND_OVERHEAD]    |= ((address >> 8) & 0xff);
    tx_buf[GP_MSI_COMMAND_OVERHEAD + 1] = address & 0xff;
    tx_buf[GP_MSI_COMMAND_OVERHEAD + 2] = mask & 0xff;
    tx_buf[GP_MSI_COMMAND_OVERHEAD + 3] = byteWrite;
    
    xfer[0].tx_buf    = tx_buf;
    xfer[0].rx_buf    = NULL;
    xfer[0].len       = GP_MSI_COMMAND_OVERHEAD + 4;
    xfer[0].cs_change = 0; /* Keep default behaviour, cfr. remark */
    spi_message_add_tail(&xfer[0], &msg);

    /* Read zero byte and event code */
    xfer[1].tx_buf    = NULL;
    xfer[1].rx_buf    = rx_buf;
    xfer[1].len       = 2;
    xfer[1].cs_change = 1; /* Change default behaviour, cfr. remark */
    spi_message_add_tail(&xfer[1], &msg);

    gp_Set_SSN_Line(gpio_ssn_pin, 0);

    error = spi_sync(spi_device, &msg);
    if (error)
    {
        goto disable_cs;
    } 
    
    if (rx_buf[0] != 0x00) 
    {
        /* We expect at least 1 zero byte. If we get here, this means that reading this zero byte failed */
        if (debug)
        {
            printk(KERN_ERR "GP: %s, First received byte is %#04x, expected %#04x\n", __func__, rx_buf[0], 0);
        }
        error = -EIO;
        goto disable_cs;
    }

    while (rx_buf[1] == GPHAL_MSI_IDLE_BYTE && retry < max_retry)
    {
        /* Try reading out the event/synchronization code*/
        retry++;

        spi_message_init(&msg);
        memset(&xfer[0], 0, sizeof(xfer[0]));

        xfer[0].tx_buf    = NULL;
        xfer[0].rx_buf    = rx_buf + 1;
        xfer[0].len       = 1;
        xfer[0].cs_change = 1; /* Change default behaviour, cfr. remark */
        spi_message_add_tail(&xfer[0], &msg);

        error = spi_sync(spi_device, &msg);
        if (error)
        {
            goto disable_cs;
        }
    }
    if (debug)
    {
        if (retry)
        {
            printk(KERN_INFO "GP: %s, Retried %u time(s) to receive event code\n",__func__, retry);
        }    
    }
    /* Received event code */
    if (rx_buf[1] != GP_MSI_MASKEDWRITECONFIRM)
    {
        if (debug)
        {
            printk(KERN_ERR "GP: %s, Received event code is %#04x, expected %#04x\n",__func__, rx_buf[1], GP_MSI_MASKEDWRITECONFIRM);
        }
        error = -EIO;
        goto disable_cs;
    }
        
    if (debug) 
    {
        if(GP_MSI_COMMAND_OVERHEAD == 0)
        {
            printk(KERN_INFO "GP: %s, TX: |%#04x:%#04x:%#04x:%#04x|\n",__func__,tx_buf[0], tx_buf[1], tx_buf[2], tx_buf[3]);
        }
        else
        {
            printk(KERN_INFO "GP: %s, TX: |%#04x:%#04x:%#04x:%#04x:%#04x|\n",__func__,tx_buf[0], tx_buf[1], tx_buf[2], tx_buf[3], tx_buf[4]);
        }
        printk(KERN_INFO "GP: %s, RX: |%#04x:%#04x|\n",__func__,rx_buf[0], rx_buf[1]);
    }

disable_cs:
    spi_message_init(&msg);
    memset(&xfer[0], 0, sizeof(xfer[0]));
    spi_message_add_tail(&xfer[0], &msg);
    spi_sync(spi_device, &msg);
    gp_Set_SSN_Line(gpio_ssn_pin, 1);
    if (error) 
    {
        printk(KERN_ERR "%s() to address %#06x with mask %#04x failed\n",__func__,readModWriteRegData->address, readModWriteRegData->mask);
        printk(KERN_ERR "Response is '%#04x %#04x '\n",rx_buf[0],rx_buf[1]);
    }
    return error;
}
#endif

MODULE_AUTHOR("GreenPeak Technologies");
MODULE_LICENSE("GPL");
