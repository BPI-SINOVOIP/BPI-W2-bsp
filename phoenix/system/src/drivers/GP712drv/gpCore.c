/*
 * $Header: //depot/release/Embedded/BaseComps/v2.4.5.0/sw/comps/halLinux/kernel/GP_Generic_Driver/gpCore.c#1 $
 * $Change: 68365 $
 * $DateTime: 2015/07/31 10:23:51 $
 * Copyright (C) 2014, GreenPeak Technologies
 *
 * support@greenpeak.com
 * www.greenpeak.com
 *
 * This file is part of the GP kernel module. This file contains the initialization
 * and deinitializtion of the module. It also contains the ioctl interface for the
 * userspace application.
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
#include "gpPinout.h"
#include "gpSpi.h"
#include "gpIo.h"

#include <linux/delay.h>
#include <linux/version.h>
#include <linux/poll.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/netdevice.h>
#include <linux/suspend.h>

#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>

struct gp_dev
{
	struct semaphore   lock;
	dev_t              devt;
	struct cdev        cdev;
	struct spi_device *spi_device;
	wait_queue_head_t  intq;
	u8                 isDeviceOpen;
};

#if defined(GP_DIVERSITY_LINUXKERNEL)
char    driver_name[]       = "GP";
#elif defined(GP501)
char    driver_name[]       = "GP501";
#elif defined(GP711)
char    driver_name[]       = "GP711";
#elif defined(GP712)
char    driver_name[]       = "GP712";
#elif defined(GP510)
char    driver_name[]       = "GP510";
#elif defined(GP710)
char    driver_name[]       = "GP710";
#elif defined(GP500)
char    driver_name[]       = "GP500";
#endif

static  struct  gp_dev  gp_dev;


static u16   spi_bus_num        = GP_SPI_BUS_NUM;
static u16   spi_chip_select    = GP_SPI_CHIP_SELECT;
static u8    gpio_interrupt_pin = GP_GPIO_INTERRUPT_PIN;
static u8    gpio_wakeup_pin    = GP_GPIO_WAKEUP_PIN;
static u8    gpio_reset_pin     = GP_GPIO_RESET_PIN;
u8           gpio_ssn_pin        = GP_GPIO_SSN_PIN;
bool           debug              = 0;

static u32   gp_ext_gpio_en = 0;
static u32   gp_ext_wkup_pin = 0;
static struct net_device *ndev;
#ifdef RTK8822BE_GPIO_API
u8 rtw_get_gpio(struct net_device *netdev, u8 gpio_num);
int  rtw_set_gpio_output_value(struct net_device *netdev, u8 gpio_num, bool isHigh);
int rtw_config_gpio(struct net_device *netdev, u8 gpio_num, bool isOutput);
#endif /* RTK8822BE_GPIO_API */

//#define GPCORE_DEBUG	1
#ifdef GPCORE_DEBUG
#define DBG(fmt, ...) printk(KERN_ERR "%s:%d: " fmt "\n", \
						__func__, __LINE__, ## __VA_ARGS__)
#else
#define DBG(fmt, ...)
#endif

#ifndef GP_DIVERSITY_LINUXKERNEL
module_param(debug,              bool,   S_IRUGO);
MODULE_PARM_DESC(debug,              "Enable debug information,"
									 "1 = enabled, 0 = disabled (default)");
#endif

void gp_Config_Wakeup_Line_ext(int gpio)
{
	#ifdef RTK8822BE_GPIO_API
	rtw_config_gpio(ndev, gpio, 1);
	rtw_set_gpio_output_value(ndev, gpio, 0);
	#endif /* RTK8822BE_GPIO_API */
}

void gp_Trigger_Wakeup_Line_ext(int gpio)
{
	#ifdef RTK8822BE_GPIO_API
	rtw_set_gpio_output_value(ndev, gpio, 1);
	mdelay(2);
	rtw_set_gpio_output_value(ndev, gpio, 0);
	#endif /* RTK8822BE_GPIO_API */
}

static int gp_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct gp_dev            *gp_dev;
	gp_ReadRegData_t          readRegData;
	gp_WriteRegData_t         writeRegData;
	gp_ReadModWriteRegData_t  readModWriteRegData;
	gp_ReadStreamData_t       readStreamData;
	gp_WriteStreamData_t      writeStreamData;
	int                          error;


	if (_IOC_TYPE(cmd) != GP_IOC_MAGIC)
	{
		if (debug)
		{
			printk(KERN_INFO "%s() called with unsupported type %#04x\n",__func__,_IOC_TYPE(cmd));
		}
		return -ENOTTY;
	}

	if (_IOC_NR(cmd) > GP_IOC_MAXNR)
	{
		if (debug)
		{
			printk(KERN_INFO "%s() called with unsupported number %#04x\n",__func__,_IOC_NR(cmd));
		}
		return -ENOTTY;
	}

	gp_dev = filp->private_data;
	error     = 0;

	if (down_interruptible(&gp_dev->lock))
	{
		return -ERESTARTSYS;
	}

	switch (cmd)
	{
		case GP_IOCRESET:
		{
			DBG("GP_IOCRESET");
			gp_Enable_Interrupt(gpio_interrupt_pin, 0);
			gp_Trigger_Reset_Line(gpio_reset_pin);
			gp_Clear_Interrupt(gpio_interrupt_pin);
			gp_Enable_Interrupt(gpio_interrupt_pin, 1);
			break;
		}
		case GP_IOCWAKEUP:
		{
			DBG("GP_IOCWAKEUP");
			if (gp_ext_gpio_en)
				gp_Trigger_Wakeup_Line_ext(gpio_wakeup_pin);
			else
				gp_Trigger_Wakeup_Line(gpio_wakeup_pin);
			break;
		}
		case GP_IOCXREADREG:
		{
			DBG("GP_IOCXREADREG");
			error = copy_from_user(&readRegData, (const void *)arg, sizeof(gp_ReadRegData_t));
			if (error)
			{
				printk(KERN_ERR "GP_IOCXREADREG copy_from_user() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			error = readRegExternal(gp_dev->spi_device, &readRegData, gpio_ssn_pin, debug);
			if (error)
			{
				printk(KERN_ERR "GP_IOCXREADREG readRegExternal() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			error = copy_to_user((void *)arg, &readRegData, sizeof(gp_ReadRegData_t));
			if (error)
			{
				printk(KERN_ERR "GP_IOCXREADREG copy_to_user() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			break;
		}
		case GP_IOCSWRITEREG:
		{
			DBG("GP_IOCSWRITEREG");
			error = copy_from_user(&writeRegData, (const void *)arg, sizeof(gp_WriteRegData_t));
			if (error)
			{
				printk(KERN_ERR "GP_IOCSWRITEREG copy_from_user() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			error = writeRegExternal(gp_dev->spi_device, &writeRegData, gpio_ssn_pin, debug);
			if (error)
			{
				printk(KERN_ERR "GP_IOCSWRITEREG writeRegExternal() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			break;
		}
		case GP_IOCSREADMODWRITEREG:
		{
			DBG("GP_IOCSREADMODWRITEREG");
			error = copy_from_user(&readModWriteRegData, (const void *)arg, sizeof(gp_ReadModWriteRegData_t));
			if (error)
			{
				printk(KERN_ERR "GP_IOCSREADMODWRITEREG copy_from_user() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}
#ifdef GP_DIVERSITY_GPHAL_K5
			error = writeMaskedByteStreamExternal(gp_dev->spi_device, &readModWriteRegData, gpio_ssn_pin, debug);
			if (error)
			{
				printk(KERN_ERR "GP_IOCSREADMODWRITEREG writeMaskedByteStreamExternal() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}
#else
			readRegData.address = readModWriteRegData.address;
			error = readRegExternal(gp_dev->spi_device, &readRegData, gpio_ssn_pin, debug);
			if (error)
			{
				printk(KERN_ERR "GP_IOCSREADMODWRITEREG readRegExternal() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			writeRegData.address   = readModWriteRegData.address;
			writeRegData.byteWrite = (readRegData.byteRead & ~readModWriteRegData.mask) | (readModWriteRegData.byteWrite & readModWriteRegData.mask);
			error = writeRegExternal(gp_dev->spi_device, &writeRegData, gpio_ssn_pin, debug);
			if (error)
			{
				printk(KERN_ERR "GP_IOCSREADMODWRITEREG writeRegExternal() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}
#endif
			break;
		}
		case GP_IOCXREADSTREAM:
		{
			DBG("GP_IOCXREADSTREAM");
			error = copy_from_user(&readStreamData, (const void *)arg, sizeof(gp_ReadStreamData_t));
			if (error)
			{
				printk(KERN_ERR "GP_IOCXREADSTREAM copy_from_user() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			error = readByteStreamExternal(gp_dev->spi_device, &readStreamData, gpio_ssn_pin, debug);
			if (error)
			{
				printk(KERN_ERR "GP_IOCXREADSTREAM readByteStreamExternal() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			break;
		}
		case GP_IOCSWRITESTREAM:
		{
			DBG("GP_IOCSWRITESTREAM");
			error = copy_from_user(&writeStreamData, (const void *)arg, sizeof(gp_WriteStreamData_t));
			if (error)
			{
				printk(KERN_ERR "GP_IOCSWRITESTREAM copy_from_user() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			error = writeByteStreamExternal(gp_dev->spi_device, &writeStreamData, gpio_ssn_pin, debug);
			if (error)
			{
				printk(KERN_ERR "GP_IOCSWRITESTREAM writeByteStreamExternal() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			break;
		}
		case GP_IOCSENABLEINT:
		{
			DBG("GP_IOCSENABLEINT");
			gp_Enable_Interrupt(gpio_interrupt_pin, *(int *)arg);

			break;
		}
		default:
		{
			printk(KERN_ERR "%s() called with unsupported cmd\n", __func__);
			error = -ENOTTY;

			break;
		}
	}

	up(&gp_dev->lock);

	return error;
}

#ifdef HAVE_UNLOCKED_IOCTL
static long gp_unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	DBG("CMD = %d", cmd);
	return (long) gp_ioctl(filp->f_path.dentry->d_inode, filp, cmd, arg);
}
#endif //HAVE_UNLOCKED_IOCTL

#ifdef CONFIG_COMPAT
static int get_compat_readRegData(gp_ReadRegData_t *p64, compat_gp_ReadRegData_t __user *p32)
{
	if (!access_ok(VERIFY_READ, p32, sizeof(*p32)) ||
			__get_user(p64->address, &p32->address) ||
			__get_user(p64->byteRead, &p32->byteRead))
		return -EFAULT;
	return 0;
}

static int put_compat_readRegData(gp_ReadRegData_t *p64, compat_gp_ReadRegData_t __user *p32)
{
	if (!access_ok(VERIFY_WRITE, p32, sizeof(*p32)) ||
			__put_user(p64->address, &p32->address) ||
			__put_user(p64->byteRead, &p32->byteRead))
		return -EFAULT;
	return 0;
}

static int get_compat_writeRegData(gp_WriteRegData_t *p64, compat_gp_WriteRegData_t __user *p32)
{
	if (!access_ok(VERIFY_READ, p32, sizeof(*p32)) ||
			__get_user(p64->address, &p32->address) ||
			__get_user(p64->byteWrite, &p32->byteWrite))
		return -EFAULT;
	return 0;
}

static int get_compat_readModWriteRegData(gp_ReadModWriteRegData_t *p64, compat_gp_ReadModWriteRegData_t __user *p32)
{
	if (!access_ok(VERIFY_READ, p32, sizeof(*p32)) ||
			__get_user(p64->address, &p32->address) ||
			__get_user(p64->mask, &p32->mask) ||
			__get_user(p64->byteWrite, &p32->byteWrite))
		return -EFAULT;
	return 0;
}

static int get_compat_readStreamData(gp_ReadStreamData_t *p64, compat_gp_ReadStreamData_t __user *p32)
{
	compat_uptr_t tmp;

	if (!access_ok(VERIFY_READ, p32, sizeof(*p32)) ||
			__get_user(p64->address, &p32->address) ||
			__get_user(p64->length, &p32->length) ||
			__get_user(tmp, &p32->bufferRead))
		return -EFAULT;
	p64->bufferRead = compat_ptr(tmp);
	return 0;
}

static int get_compat_writeStreamData(gp_WriteStreamData_t *p64, compat_gp_WriteStreamData_t __user *p32)
{
	compat_uptr_t tmp;

	if (!access_ok(VERIFY_READ, p32, sizeof(*p32)) ||
			__get_user(p64->address, &p32->address) ||
			__get_user(p64->length, &p32->length) ||
			__get_user(tmp, &p32->bufferWrite))
		return -EFAULT;
	p64->bufferWrite = compat_ptr(tmp);
	return 0;
}


static long gp_compat_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct gp_dev            *gp_dev;
	gp_ReadRegData_t          readRegData;
	gp_WriteRegData_t         writeRegData;
	gp_ReadModWriteRegData_t  readModWriteRegData;
	gp_ReadStreamData_t       readStreamData;
	gp_WriteStreamData_t      writeStreamData;
	int                          error;


	if (_IOC_TYPE(cmd) != GP_IOC_MAGIC)
	{
		if (debug)
		{
			printk(KERN_INFO "%s() called with unsupported type %#04x\n",__func__,_IOC_TYPE(cmd));
		}
		return -ENOTTY;
	}

	if (_IOC_NR(cmd) > GP_IOC_MAXNR)
	{
		if (debug)
		{
			printk(KERN_INFO "%s() called with unsupported number %#04x\n",__func__,_IOC_NR(cmd));
		}
		return -ENOTTY;
	}

	gp_dev = filp->private_data;
	error     = 0;

	if (down_interruptible(&gp_dev->lock))
	{
		return -ERESTARTSYS;
	}

	switch (cmd)
	{
		case GP_IOCRESET:
		{
			DBG("GP_IOCRESET");
			gp_Enable_Interrupt(gpio_interrupt_pin, 0);
			gp_Trigger_Reset_Line(gpio_reset_pin);
			gp_Clear_Interrupt(gpio_interrupt_pin);
			gp_Enable_Interrupt(gpio_interrupt_pin, 1);
			break;
		}
		case GP_IOCWAKEUP:
		{
			DBG("GP_IOCWAKEUP");
			if (gp_ext_gpio_en)
				gp_Trigger_Wakeup_Line_ext(gpio_wakeup_pin);
			else
				gp_Trigger_Wakeup_Line(gpio_wakeup_pin);
			break;
		}
		case GP_IOCXREADREG:
		{
			DBG("GP_IOCXREADREG");
			error = get_compat_readRegData(&readRegData, compat_ptr(arg));
			if (error)
			{
				printk(KERN_ERR "GP_IOCXREADREG copy_from_user() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			error = readRegExternal(gp_dev->spi_device, &readRegData, gpio_ssn_pin, debug);
			if (error)
			{
				printk(KERN_ERR "GP_IOCXREADREG readRegExternal() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			error = put_compat_readRegData(&readRegData, compat_ptr(arg));
			if (error)
			{
				printk(KERN_ERR "GP_IOCXREADREG copy_to_user() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			break;
		}
		case GP_IOCSWRITEREG:
		{
			DBG("GP_IOCSWRITEREG");
			error = get_compat_writeRegData(&writeRegData, compat_ptr(arg));
			if (error)
			{
				printk(KERN_ERR "GP_IOCSWRITEREG copy_from_user() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			error = writeRegExternal(gp_dev->spi_device, &writeRegData, gpio_ssn_pin, debug);
			if (error)
			{
				printk(KERN_ERR "GP_IOCSWRITEREG writeRegExternal() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			break;
		}
		case GP_IOCSREADMODWRITEREG:
		{
			DBG("GP_IOCSREADMODWRITEREG");
			error = get_compat_readModWriteRegData(&readModWriteRegData, compat_ptr(arg));
			if (error)
			{
				printk(KERN_ERR "GP_IOCSREADMODWRITEREG copy_from_user() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}
#ifdef GP_DIVERSITY_GPHAL_K5
			error = writeMaskedByteStreamExternal(gp_dev->spi_device, &readModWriteRegData, gpio_ssn_pin, debug);
			if (error)
			{
				printk(KERN_ERR "GP_IOCSREADMODWRITEREG writeMaskedByteStreamExternal() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}
#else
			readRegData.address = readModWriteRegData.address;
			error = readRegExternal(gp_dev->spi_device, &readRegData, gpio_ssn_pin, debug);
			if (error)
			{
				printk(KERN_ERR "GP_IOCSREADMODWRITEREG readRegExternal() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			writeRegData.address   = readModWriteRegData.address;
			writeRegData.byteWrite = (readRegData.byteRead & ~readModWriteRegData.mask) | (readModWriteRegData.byteWrite & readModWriteRegData.mask);
			error = writeRegExternal(gp_dev->spi_device, &writeRegData, gpio_ssn_pin, debug);
			if (error)
			{
				printk(KERN_ERR "GP_IOCSREADMODWRITEREG writeRegExternal() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}
#endif
			break;
		}
		case GP_IOCXREADSTREAM:
		{
			DBG("GP_IOCXREADSTREAM");
			error = get_compat_readStreamData(&readStreamData, compat_ptr(arg));
			if (error)
			{
				printk(KERN_ERR "GP_IOCXREADSTREAM copy_from_user() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			error = readByteStreamExternal(gp_dev->spi_device, &readStreamData, gpio_ssn_pin, debug);
			if (error)
			{
				printk(KERN_ERR "GP_IOCXREADSTREAM readByteStreamExternal() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			break;
		}
		case GP_IOCSWRITESTREAM:
		{
			DBG("GP_IOCSWRITESTREAM");
			error = get_compat_writeStreamData(&writeStreamData, compat_ptr(arg));
			if (error)
			{
				printk(KERN_ERR "GP_IOCSWRITESTREAM copy_from_user() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			error = writeByteStreamExternal(gp_dev->spi_device, &writeStreamData, gpio_ssn_pin, debug);
			if (error)
			{
				printk(KERN_ERR "GP_IOCSWRITESTREAM writeByteStreamExternal() failed (%d)\n", error);
				error = -EFAULT;
				break;
			}

			break;
		}
		case GP_IOCSENABLEINT:
		{
			DBG("GP_IOCSENABLEINT");
			gp_Enable_Interrupt(gpio_interrupt_pin, *(int *)arg);

			break;
		}
		default:
		{
			printk(KERN_ERR "%s() called with unsupported cmd\n", __func__);
			error = -ENOTTY;

			break;
		}
	}

	up(&gp_dev->lock);

	return error;
}
#endif //CONFIG_COMPAT

static unsigned int gp_poll(struct file *filp, poll_table *wait)
{
	struct gp_dev *gp_dev;
	gp_dev = filp->private_data;

	//Userspace application can go to sleep. We will wake up when a falling edge is detected on the interrupt pin.

	if (gp_dev)
	{
		if (gp_Interrupt_Line_Status(gpio_interrupt_pin))
		{
			// If the interrupt pin is already low, then we should immediately inform the userspace application,
			//as this means there is still an interrupt pending in the GP chip.
			return (POLLIN | POLLRDNORM);
		}

		poll_wait(filp, &gp_dev->intq, wait);

		if (gp_Interrupt_Line_Status(gpio_interrupt_pin))
		{
			//Check if the interrupt pin is actually low (could be a spike on the interrupt pin that woke us up).
			//If the pin is actually low, wake up the userspace process.
			return (POLLIN | POLLRDNORM);
		}
	}

	return 0;
}

static void interrupt_callback(void *status)
{
	struct gp_dev *gp_dev;

	gp_dev = status;
	if (gp_dev)
	{
		//Wake up the wait queue
		wake_up_interruptible(&gp_dev->intq);
	}
}

static int gp_open(struct inode *inode, struct file *filp)
{
	struct gp_dev *gp_dev;

	gp_dev = container_of(inode->i_cdev, struct gp_dev, cdev);

	if (down_interruptible(&gp_dev->lock))
	{
		return -ERESTARTSYS;
	}
	if (gp_dev->isDeviceOpen)
	{
		up(&gp_dev->lock);
		return -EBUSY;
	}

	gp_dev->isDeviceOpen = 1;
	filp->private_data      = gp_dev;
	gp_Config_Interrupt_Line(gpio_interrupt_pin, interrupt_callback, gp_dev, driver_name);
	if (gp_ext_gpio_en)
		gp_Config_Wakeup_Line_ext(gpio_wakeup_pin);
	else
		gp_Config_Wakeup_Line(gpio_wakeup_pin);
	gp_Config_Reset_Line(gpio_reset_pin);
	gp_Config_SSN_Line(gpio_ssn_pin);

	up(&gp_dev->lock);

	return 0;
}

static int gp_release(struct inode *inode, struct file *filp)
{
	struct gp_dev *gp_dev;

	gp_dev = filp->private_data;

	if (down_interruptible(&gp_dev->lock))
	{
		return -ERESTARTSYS;
	}

	gp_dev->isDeviceOpen = 0;
	gp_UnConfig_Interrupt_Line(gpio_interrupt_pin);

	up(&gp_dev->lock);

	return 0;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,8,0)
static int __devinit gp_probe(struct spi_device *spi)
#else
static int gp_probe(struct spi_device *spi)
#endif
{
	if (down_interruptible(&gp_dev.lock))
	{
		return -ERESTARTSYS;
	}
	gp_dev.spi_device = spi;
	up(&gp_dev.lock);

	return 0;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,8,0)
static int __devexit gp_remove(struct spi_device *spi)
#else
static int gp_remove(struct spi_device *spi)
#endif
{
	if (down_interruptible(&gp_dev.lock))
	{
		return -ERESTARTSYS;
	}

	gp_dev.spi_device = NULL;
	up(&gp_dev.lock);

	return 0;
}

static struct spi_driver gp_driver = {
	.driver        = {
		.name    = driver_name,
		.owner    = THIS_MODULE,
	},
	.probe        = gp_probe,
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,8,0)
	.remove       = __devexit_p(gp_remove),
#else
	.remove       = gp_remove,
#endif
};

static int  __init gp_init_spi(void)
{
	struct spi_master *spi_master;
	struct spi_device *spi_device;
	int                error;

	error = spi_register_driver(&gp_driver);
	if (error < 0)
	{
		printk(KERN_ERR "spi_register_driver() returned %d\n", error);
		goto spi_error_1;
	}

	spi_master = spi_busnum_to_master(spi_bus_num);
	if (!spi_master)
	{
		printk(KERN_ERR "spi_busnum_to_master(%d) returned NULL\n", spi_bus_num);
		error = -ENODEV;
		goto spi_error_2;
	}
	spi_master->rt = true;
	spi_device = spi_alloc_device(spi_master);
	if (!spi_device)
	{
		printk(KERN_ERR "spi_alloc_device() returned NULL\n");
		error = -ENOMEM;
		goto spi_error_3;
	}

	spi_device->max_speed_hz     = GP_SPI_MAX_SPEED_HZ;
	spi_device->chip_select      = spi_chip_select;
	spi_device->mode             = GP_SPI_MODE;
	spi_device->bits_per_word    = GP_SPI_BITS_PER_WORD;
	spi_device->irq              = GP_SPI_IRQ;
	spi_device->controller_state = NULL;
	spi_device->controller_data  = NULL;
	strlcpy(spi_device->modalias, driver_name, SPI_NAME_SIZE);

	error = spi_add_device(spi_device);
	if (error < 0)
	{
		printk(KERN_ERR "spi_add_device() returned %d\n", error);
		goto spi_error_4;
	}

	spi_master_put(spi_master);

	return 0;

spi_error_4:
	spi_dev_put(spi_device);

spi_error_3:
	spi_master_put(spi_master);

spi_error_2:
	spi_unregister_driver(&gp_driver);

spi_error_1:
	return error;
}

static void gp_exit_spi(void)
{
	spi_unregister_device(gp_dev.spi_device);
	spi_unregister_driver(&gp_driver);
}

static int  __init gp_init_gpio(void)
{
	int  error;

	error = gpio_request(gpio_interrupt_pin, driver_name);
	if (error < 0)
	{
		printk(KERN_ERR "gpio_request() for interrupt pin returned %d\n", error);
		goto gpio_error_1;
	}
	gpio_set_debounce(gpio_interrupt_pin, 5 * 1000);

	if (!gp_ext_gpio_en)
		error = gpio_request(gpio_wakeup_pin, driver_name);
	else
		error = 0;
	if (error < 0)
	{
		printk(KERN_ERR "gpio_request() for wakeup pin returned %d\n", error);
		goto gpio_error_2;
	}

	error = gpio_request(gpio_reset_pin, driver_name);
	if (error < 0)
	{
		printk(KERN_ERR "gpio_request() for reset pin returned %d\n", error);
		goto gpio_error_3;
	}

#if defined (GP_DIVERSITY_USE_SSN_GPIO_CONTROL)
	error = gpio_request(gpio_ssn_pin, driver_name);
	if (error < 0)
	{
		printk(KERN_ERR "gpio_request() for ssn pin returned %d\n", error);
		goto gpio_error_4;
	}
#endif

	return 0;

gpio_error_4:
	gpio_free(gpio_reset_pin);

gpio_error_3:
	if (!gp_ext_gpio_en)
		gpio_free(gpio_wakeup_pin);

gpio_error_2:
	//gpio_set_debounce(gpio_interrupt_pin, 30 * 1000);
	gpio_free(gpio_interrupt_pin);

gpio_error_1:
	return error;
}

static void gp_exit_gpio(void)
{
	//gpio_set_debounce(gpio_interrupt_pin, 30 * 1000);
	gpio_free(gpio_interrupt_pin);
	if (!gp_ext_gpio_en)
		gpio_free(gpio_wakeup_pin);
	gpio_free(gpio_reset_pin);
#if defined (GP_DIVERSITY_USE_SSN_GPIO_CONTROL)
	gpio_free(gpio_ssn_pin);
#endif
}

static struct file_operations gp_fops = {
	.owner          = THIS_MODULE,
	.open           = gp_open,
	.release        = gp_release,
	.poll           = gp_poll,
#ifdef HAVE_UNLOCKED_IOCTL
	.unlocked_ioctl = gp_unlocked_ioctl,
#else
	.ioctl          = gp_ioctl,
#endif //HAVE_UNLOCKED_IOCTL
#ifdef CONFIG_COMPAT
	.compat_ioctl = gp_compat_ioctl,
#endif //CONFIG_COMPAT
};

static int  __init gp_init_cdev(void)
{
	int  error;

	error = alloc_chrdev_region(&gp_dev.devt, 0, 1, driver_name);
	if (error < 0)
	{
		printk(KERN_ERR "alloc_chrdev_region() returned %d\n", error);
		goto cdev_error_1;
	}

	cdev_init(&gp_dev.cdev, &gp_fops);
	gp_dev.cdev.owner = THIS_MODULE;

	error = cdev_add(&gp_dev.cdev, gp_dev.devt, 1);
	if (error < 0)
	{
		printk(KERN_ERR "cdev_add() returned %d\n", error);
		goto cdev_error_2;
	}

	printk(KERN_ALERT "GP Driver built for %s. Major:Minor %d:%d\n", driver_name, MAJOR(gp_dev.devt), MINOR(gp_dev.devt));

	return 0;

cdev_error_2:
	unregister_chrdev_region(gp_dev.devt, 1);

cdev_error_1:
	return error;
}

static void gp_exit_cdev(void)
{
	cdev_del(&gp_dev.cdev);
	unregister_chrdev_region(gp_dev.devt, 1);
}

int  __init gp_init(void)
{
	int  error;

#ifdef init_MUTEX
	init_MUTEX(&gp_dev.lock);
#else
	sema_init(&gp_dev.lock, 1);
#endif
	init_waitqueue_head(&gp_dev.intq);

	gp_dev.isDeviceOpen = 0;

	error = gp_init_cdev();
	if (error < 0)
		goto error_1;

	error = gp_init_gpio();
	if (error < 0)
		goto error_2;

	error = gp_init_spi();
	if (error < 0)
		goto error_3;

	return 0;

error_3:
	gp_exit_gpio();

error_2:
	gp_exit_cdev();

error_1:
	return error;
}

void __exit gp_exit(void)
{
	gp_exit_spi();
	gp_exit_gpio();
	gp_exit_cdev();
}

static int rtk_rf4ce_pm_suspend(struct device *dev)
{
	printk(KERN_ERR "[RF4CE] Enter %s\n", __func__);

	if(RTK_PM_STATE == PM_SUSPEND_STANDBY){
		//For idle mode
		printk(KERN_ERR "[RF4CE] %s Idle mode\n", __func__);
	}else{
		//For suspend mode
		printk(KERN_ERR "[RF4CE] %s Suspend mode\n", __func__);
	}

	printk(KERN_ERR "[RF4CE] Exit %s\n", __func__);

	return 0;
}

static int rtk_rf4ce_pm_resume(struct device *dev)
{
	printk(KERN_ERR "[RF4CE] Enter %s\n", __func__);

	if(RTK_PM_STATE == PM_SUSPEND_STANDBY){
		//For idle mode
		printk(KERN_ERR "[RF4CE] %s Idle mode\n", __func__);
	}else{
		//For suspend mode
		printk(KERN_ERR "[RF4CE] %s Suspend mode\n", __func__);
	}

	/* configure GPIO pins */
	gpio_direction_input(gpio_interrupt_pin);

	if (gp_ext_gpio_en)
		gp_Config_Wakeup_Line_ext(gpio_wakeup_pin);
	else
		gp_Config_Wakeup_Line(gpio_wakeup_pin);
	gp_Config_Reset_Line(gpio_reset_pin);
	gp_Config_SSN_Line(gpio_ssn_pin);

	printk(KERN_ERR "[RF4CE] Exit %s\n", __func__);
	return 0;
}

static const struct dev_pm_ops rtk_rf4ce_pmops = {
	.suspend    = rtk_rf4ce_pm_suspend,
	.resume     = rtk_rf4ce_pm_resume,
};

static int rtk_rf4ce_probe(struct platform_device *pdev)
{
	struct net_device *dev;

	/* get chip select gpio */
	gpio_ssn_pin = of_get_gpio(pdev->dev.of_node, 0);

	/* get reset gpio */
	gpio_reset_pin = of_get_gpio(pdev->dev.of_node, 1);

	/* get interrupt gpio */
	gpio_interrupt_pin = of_get_gpio(pdev->dev.of_node, 2);

	/* get wakeup gpio */
	gpio_wakeup_pin = of_get_gpio(pdev->dev.of_node, 3);
	of_property_read_u32(pdev->dev.of_node, "ext_gpio_en", &gp_ext_gpio_en);
	of_property_read_u32(pdev->dev.of_node, "ext_wkup_pin", &gp_ext_wkup_pin);

	printk(KERN_INFO "RF4CE gpio_ssn_pin = %d\n\t gpio_reset_pin = %d\n\t "
		"gpio_interrupt_pin = %d\n\t gpio_wakeup_pin = %d\n\t "
		"gp_ext_gpio_en = %d\n\t ext_wkup_pin = %d\n\t\n",
		gpio_ssn_pin, gpio_reset_pin, gpio_interrupt_pin, gpio_wakeup_pin,
		gp_ext_gpio_en, gp_ext_wkup_pin);

	/* use external WAKEUP pin instead internal GPIO pin */
	if (gp_ext_gpio_en) {
		gpio_wakeup_pin = gp_ext_wkup_pin;

		for_each_netdev(&init_net, dev) {
			printk(KERN_INFO "dev = [%s], index = %d\n", dev->name, dev->ifindex);
			if (!strncmp("wlan0", dev->name, 5)) {
				ndev = dev;
				printk(KERN_INFO "found 8822be at %p, ifindex %d\n", dev, dev->ifindex);
				break;
			}
		}
	}
	return gp_init();
}

static int rtk_rf4ce_remove(struct platform_device *pdev)
{
	printk(KERN_ALERT "unload SPI protocol driver\n");
	gp_exit();
	return 0;
}

static const struct of_device_id rtk_rf4ce_dt_ids[] = {
	{ .compatible = "Realtek,rtk-rf4ce", },
	{},
};
MODULE_DEVICE_TABLE(of, rtk_rf4ce_dt_ids);


static struct platform_driver rtk_rf4ce_driver = {
	.probe = rtk_rf4ce_probe,
	.remove = rtk_rf4ce_remove,
	.driver = {
		.name = "rtk_rf4ce",
		.owner = THIS_MODULE,
		.pm = &rtk_rf4ce_pmops,
		.of_match_table = of_match_ptr(rtk_rf4ce_dt_ids),
	},
};

module_platform_driver(rtk_rf4ce_driver);

#ifndef GP_DIVERSITY_LINUXKERNEL

MODULE_AUTHOR("GreenPeak Technologies");
MODULE_DESCRIPTION("GreenPeak Generic Kernel Driver");
MODULE_LICENSE("GPL");
#endif
