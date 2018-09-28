/*
 * $Header: //depot/release/Embedded/BaseComps/v2.4.5.0/sw/comps/halLinux/kernel/GP_Generic_Driver/gpIo.c#1 $
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
 
#include "gpCore.h"
#include "gpIo.h"
#include "gpPinout.h"

#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/module.h>

#ifdef SPIN_LOCK_UNLOCKED
static spinlock_t            lock               = SPIN_LOCK_UNLOCKED;
#else
DEFINE_SPINLOCK(lock);
#endif    
static u8                    interrupt_enable   = 0;
static interrupt_callback_t  interrupt_callback = NULL;
static void                 *interrupt_dev      = NULL;

static irqreturn_t gp_irq_handler(int irq, void *dev_id);

void gp_Config_Reset_Line(int gpio)
{
    gpio_direction_output(gpio, GP_RESET_PIN_INACTIVE_LEVEL);
}

void gp_Trigger_Reset_Line(int gpio)
{
    gpio_set_value(gpio, GP_RESET_PIN_INACTIVE_LEVEL);
    mdelay(20);
    gpio_set_value(gpio, GP_RESET_PIN_ACTIVE_LEVEL);
}

void gp_Config_Wakeup_Line(int gpio)
{
    gpio_direction_output(gpio, 0);
}

void gp_Trigger_Wakeup_Line(int gpio)
{
    gpio_set_value(gpio, 1);
    udelay(1);
    gpio_set_value(gpio, 0);
}

void gp_Config_Interrupt_Line(int gpio, interrupt_callback_t callback, void *status, char* driver_name)
{

    unsigned int      irq;
    unsigned long     flags;
    int               error;

    gpio_direction_input(gpio);

    irq = gpio_to_irq(gpio);

	flags = IRQF_SHARED | IRQF_TRIGGER_FALLING;

    interrupt_callback = callback;
    interrupt_dev      = status;

	irq_set_irq_type(irq, IRQ_TYPE_EDGE_FALLING);
    error = request_irq(irq, gp_irq_handler, flags, driver_name, interrupt_dev);
    if (error)
    {
        printk(KERN_ERR "request_irq() for IRQ %u on pin %d returned %d\n", irq, gpio, error);
    }
}

void gp_UnConfig_Interrupt_Line(int gpio)
{
    unsigned int  irq;

    irq = gpio_to_irq(gpio);

    free_irq(irq, interrupt_dev);
    
    interrupt_callback = NULL;
    interrupt_dev      = NULL;
}

void gp_Clear_Interrupt(int gpio)
{
}

int  gp_Interrupt_Line_Status(int gpio)
{
    int  value;
    value = gpio_get_value(gpio);
    return value ? 0 : 1;
}

void gp_Enable_Interrupt(int gpio, int value)
{
    unsigned long  flags;

    spin_lock_irqsave(&lock, flags);

    interrupt_enable = value;

    spin_unlock_irqrestore(&lock, flags);
}

void gp_Config_SSN_Line(int gpio)
{
#if defined (GP_DIVERSITY_USE_SSN_GPIO_CONTROL)
    gpio_direction_output(gpio,0);
    gpio_set_value(gpio,1);
#endif
}

void gp_Set_SSN_Line(int gpio, int value)
{
#if defined (GP_DIVERSITY_USE_SSN_GPIO_CONTROL)
    gpio_set_value(gpio, value);
#endif
}

/*
interrupt handler for the interrupt from GP chip to host processor.
*/
static irqreturn_t gp_irq_handler(int irq, void *dev_id)
{
    unsigned long  flags;

    spin_lock_irqsave(&lock, flags);

    if (interrupt_enable)
    {
        if (interrupt_callback)
        {
            interrupt_callback(dev_id);
        }
    }

    spin_unlock_irqrestore(&lock, flags);

    return IRQ_HANDLED;
}

MODULE_AUTHOR("GreenPeak Technologies");
MODULE_LICENSE("GPL");
