/*
 * $Header: //depot/release/Embedded/BaseComps/v2.4.5.0/sw/comps/halLinux/kernel/GP_Generic_Driver/gpIo.h#1 $
 * $Change: 68365 $
 * $DateTime: 2015/07/31 10:23:51 $
 * Copyright (C) 2014, GreenPeak Technologies
 *
 * support@greenpeak.com
 * www.greenpeak.com
 *
 * This file is part of the GP kernel module. This file contains the API to access
 * the GPIO's that are part of the interface between the GP chip and host processor.
 * These GPIO's include the reset, wkup, and interrupt pin.
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
 
#ifndef _GP_IO_H_
#define _GP_IO_H_

#ifdef GP_DIVERSITY_GPHAL_K3
#define     GP_RESET_PIN_ACTIVE_LEVEL         0
#define     GP_RESET_PIN_INACTIVE_LEVEL       1
#else
#define     GP_RESET_PIN_ACTIVE_LEVEL         1
#define     GP_RESET_PIN_INACTIVE_LEVEL       0
#endif

typedef void (*interrupt_callback_t)(void *status);

/** 
 *  Configure the pin of the host processor connected to the reset pin of the GP chip as an output.
 *  The pin should be put in a state (high or low) so that the GP chip is put in reset (see the GP chip datasheet for the exact polarity of the reset pin).
 *
 *  @ param gpio            The GPIO number of the pin on the host processor which is connected to the Reset pin of the GP chip.
 *
*/
void gp_Config_Reset_Line(int gpio);

/** 
 *  Trigger a reset of the GP chip via Reset pin of the GP chip.
 *  The GP chip will be reset by a high-low or low-high transition (see the GP chip datasheet for the exact polarity of the reset pin) on the reset pin.
 *
 *  @ param gpio            The GPIO number of the pin on the host processor which is connected to the Reset pin of the GP chip.
 *
*/
void gp_Trigger_Reset_Line(int gpio);

/** 
 *  Configure the pin of the host processor connected to the WKUP pin of the GP chip as an output.
 *  The pin should be put in a low state.
 *
 *  @ param gpio            The GPIO number of the pin on the host processor which is connected to the WKUP pin of the GP chip.
 *
*/
void gp_Config_Wakeup_Line(int gpio);

/** 
 *  Wake up the GP chip from its sleep mode by triggering a high-low transition on the WKUP pin of the GP chip.
 *  When woken up, the GP chip will inform the host processor by creating an interrupt.
 *
 *  @ param gpio            The GPIO number of the pin on the host processor which is connected to the WKUP pin of the GP chip.
 *
*/
void gp_Trigger_Wakeup_Line(int gpio);

/** 
 *  Configure the pin of the host processor connected to the INTOUTn pin of the GP chip as an input.
 *  The pin should be pulled up internally in the host processor or external via a pull-up resistor.
 *  When the GP chip has an interrupt pending, this pin will be pulled down.
 *  The driver should be configured so that the function 'callback' is called when a falling edge is 
 *  seen on the INTOUTn pin of the GP chip.
 *
 *  @ param gpio            The GPIO number of the pin on the host processor which is connected to the INTOUTn pin of the GP chip.
 *  @ param callback        The function to be called when an interrupt is triggered (falling edge on INTOUTn pin of the GP chip).
 *  @ param status          Pointer to gp_dev structure with driver information.
 *
*/
void gp_Config_Interrupt_Line(int gpio, interrupt_callback_t callback, void *status, char* driver_name);

/** 
 *  Disable the interrupt detection on the INTOUTn pin of the GP chip. When called, the driver should no longer trigger and interrupt
 *  when a falling edge on the INTOUTn pin is seen. All registered callbacks should be unregistered.
 *
 *  @ param gpio            The GPIO number of the pin on the host processor which is connected to the INTOUTn pin of the GP chip.
 *
*/
void gp_UnConfig_Interrupt_Line(int gpio);

/** 
 *  Clear a pending interrupt when it is handled/noticed in the driver. Actual clearing of the interrupt in the GP chip will not be done 
 *  via this function, but will happen through a register access from userspace.
 *
 *  @ param gpio            The GPIO number of the pin on the host processor which is connected to the INTOUTn pin of the GP chip.
 *
*/
void gp_Clear_Interrupt(int gpio);

/** 
 *  Return whether an interrupt is pending on the GP chip or not.
 *  When the INTOUTn pin of the GP chip is low, this function should return 1.
 *  When the INTOUTn pin of the GP chip is high, this function should return 0.
 *
 *  @ param gpio            The GPIO number of the pin on the host processor which is connected to the INTOUTn pin of the GP chip.
 *  @ return                0 when the INTOUTn pin of the GP chip is high, 1 otherwise.
 *
*/
int  gp_Interrupt_Line_Status(int gpio);

/** 
 *  Enable/disable interrupt detection. When enabled, a falling edge on the INTOUTn pin of the GP chip should create an interrupt
 *  in the kernel driver and call the corresponding callback (registered through gp_Config_Interrupt_Line).
 *
 *  @ param gpio            The GPIO number of the pin on the host processor which is connected to the INTOUTn pin of the GP chip.
 *  @ param value           0 when the interrupt needs to be disabled, 1 otherwise.
 *
*/
void gp_Enable_Interrupt(int gpio, int value);

/** 
 *  Configure the pin of the host processor connected to the SSn pin of the GP chip as an output.
 *  The pin should be put in a high state.
 *
 *  @ param gpio            The GPIO number of the pin on the host processor which is connected to the SSn pin of the GP chip.
 *
*/
void gp_Config_SSN_Line(int gpio);

/** 
 *  Make the pin of the host processor connected to the SSn pin of the GP chip high or low.
 *
 *  @ param gpio            The GPIO number of the pin on the host processor which is connected to the SSn pin of the GP chip.
 *  @ param value           0 when the pin needs to be made low, 1 when it needs to be made high.
 *
*/
void gp_Set_SSN_Line(int gpio, int value);

#endif /* _GP_IO_H_ */
