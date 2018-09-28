/*
 * $Header: //depot/release/Embedded/BaseComps/v2.4.5.0/sw/comps/halLinux/kernel/GP_Generic_Driver/RPi_3_2_27/gpPinout.h#1 $
 * $Change: 68365 $
 * $DateTime: 2015/07/31 10:23:51 $
 * Copyright (C) 2014, GreenPeak Technologies
 *
 * support@greenpeak.com
 * www.greenpeak.com
 *
 * This file is part of the GP kernel module. This file defines how the
 * host processor and GP chip are connected (i.e. what GPIO's of the 
 * host processor are used to control the GP chip.
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

#ifndef _GP_BSP_H_
#define _GP_BSP_H_

#include <linux/gpio.h>
#include <linux/spi/spi.h>

/*Define this if the slave select pin of the SPI master is controlled as a generic GPIO.
  When this is defined, the GP kernel driver will pull down this pin at the start of an
  SPI transfer. When not defined, the GP kernel driver will assume the Linux SPI driver
  pulls down this pin at the start of the SPI transfer.*/
#define GP_DIVERSITY_USE_SSN_GPIO_CONTROL

/*Number of the SPI bus (connected to the GP chip) in the linux kernel.*/
#define GP_SPI_BUS_NUM        0

/*Number of the SPI chip select pin (connected to the GP chip) in the SPI kernel driver.*/
#define GP_SPI_CHIP_SELECT    1

/*GPIO number of the pin of the host processor connected to the INTOUTn pin of the GP chip.*/
#define GP_GPIO_INTERRUPT_PIN        131

/*GPIO number of the pin of the host processor connected to the SSn pin of the GP chip.*/
#define GP_GPIO_SSN_PIN             6

/*GPIO number of the pin of the host processor connected to the WKUP pin of the GP chip.*/
#define GP_GPIO_WAKEUP_PIN            1

/*GPIO number of the pin of the host processor connected to the Reset pin of the GP chip.*/
#define GP_GPIO_RESET_PIN            130

/*SPI protocol configuration. This should not be changed.*/
#define GP_SPI_IRQ                (-1)
#define GP_SPI_MAX_SPEED_HZ        16000000
#define GP_SPI_MODE                SPI_MODE_0
#define GP_SPI_BITS_PER_WORD    8
#define GP_SPI_MAX_NUMBER_OF_RETRIES    15

#endif /* _GP_BSP_H_ */

