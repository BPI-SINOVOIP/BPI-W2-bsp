/*
 * drivers/soc/realtek/rtd129x/rtk_ve/jdi/compat_jpu.h
 *
 * Copyright (C) 2013 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/compat.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#include "jpu.h"
#include "compat_jpu.h"

/* See drivers/soc/realtek/rtd129x/rtk_ve/jdi/jpu.h for the definition of these structs */
typedef struct compat_jpudrv_buffer_t {
    compat_uint_t size;
    compat_ulong_t phys_addr;
    compat_ulong_t base;							/* kernel logical address in use kernel */
    compat_ulong_t virt_addr;				/* virtual user space address */
} compat_jpudrv_buffer_t;

typedef struct compat_jpudrv_intr_info_t {
    compat_uint_t timeout;
    compat_int_t intr_reason;
} compat_jpudrv_intr_info_t;

typedef struct compat_jpudrv_dovi_info_t{
	compat_uint_t inst_idx;
	compat_uint_t enable;
} compat_jpudrv_dovi_info_t;

#define COMPAT_JDI_IOCTL_ALLOCATE_PHYSICAL_MEMORY _IO(JDI_IOCTL_MAGIC, 0)
#define COMPAT_JDI_IOCTL_FREE_PHYSICALMEMORY _IO(JDI_IOCTL_MAGIC, 1)
#define COMPAT_JDI_IOCTL_WAIT_INTERRUPT _IO(JDI_IOCTL_MAGIC, 2)
#define COMPAT_JDI_IOCTL_GET_INSTANCE_POOL _IO(JDI_IOCTL_MAGIC, 5)
#define COMPAT_JDI_IOCTL_GET_RESERVED_VIDEO_MEMORY_INFO _IO(JDI_IOCTL_MAGIC, 6)
#define COMPAT_JDI_IOCTL_GET_REGISTER_INFO _IO(JDI_IOCTL_MAGIC, 11)
#define COMPAT_JDI_IOCTL_GET_BONDING_INFO _IO(JDI_IOCTL_MAGIC, 13)
#define COMPAT_JDI_IOCTL_SET_RTK_DOVI_FLAG _IO(JDI_IOCTL_MAGIC, 14)

static int compat_get_jpu_buffer_data(
    compat_jpudrv_buffer_t __user *data32,
    jpudrv_buffer_t __user *data)
{
    compat_uint_t s;
    compat_ulong_t p;
    compat_ulong_t b;
    compat_ulong_t v;
    int err;

    err = get_user(s, &data32->size);
    err |= put_user(s, &data->size);
    err |= get_user(p, &data32->phys_addr);
    err |= put_user(p, &data->phys_addr);
    err |= get_user(b, &data32->base);
    err |= put_user(b, &data->base);
    err |= get_user(v, &data32->virt_addr);
    err |= put_user(v, &data->virt_addr);

    return err;
}

static int compat_get_jpu_intr_info_data(
    compat_jpudrv_intr_info_t __user *data32,
    jpudrv_intr_info_t __user *data)
{
    compat_uint_t t;
    compat_int_t i;
    int err;

    err = get_user(t, &data32->timeout);
    err |= put_user(t, &data->timeout);
    err |= get_user(i, &data32->intr_reason);
    err |= put_user(i, &data->intr_reason);

    return err;
}

static int compat_get_jpu_dovi_info(
	compat_jpudrv_dovi_info_t __user *data32,
	jpudrv_dovi_info_t __user *data)
{
	compat_uint_t e;
	compat_uint_t i;
	int err;

	err |= get_user(i, &data32->inst_idx);
	err |= put_user(i, &data->inst_idx);
	err |= get_user(e, &data32->enable);
	err |= put_user(e, &data->enable);

	return err;
}

static int compat_put_jpu_buffer_data(
    compat_jpudrv_buffer_t __user *data32,
    jpudrv_buffer_t __user *data)
{
    compat_uint_t s;
    compat_ulong_t p;
    compat_ulong_t b;
    compat_ulong_t v;
    int err;

    err = get_user(s, &data->size);
    err |= put_user(s, &data32->size);
    err |= get_user(p, &data->phys_addr);
    err |= put_user(p, &data32->phys_addr);
    err |= get_user(b, &data->base);
    err |= put_user(b, &data32->base);
    err |= get_user(v, &data->virt_addr);
    err |= put_user(v, &data32->virt_addr);

    return err;
}

static int compat_put_jpu_intr_info_data(
    compat_jpudrv_intr_info_t __user *data32,
    jpudrv_intr_info_t __user *data)
{
    compat_uint_t t;
    compat_int_t i;
    int err;

    err = get_user(t, &data->timeout);
    err |= put_user(t, &data32->timeout);
    err |= get_user(i, &data->intr_reason);
    err |= put_user(i, &data32->intr_reason);

    return err;
}

static int compat_put_jpu_dovi_info(
	compat_jpudrv_dovi_info_t __user *data32,
	jpudrv_dovi_info_t __user *data)
{
	compat_uint_t i;
	compat_uint_t e;
	int err;

	err |= get_user(i, &data->inst_idx);
	err |= put_user(i, &data32->inst_idx);
	err |= get_user(e, &data->enable);
	err |= put_user(e, &data32->enable);

	return err;
}

long compat_jpu_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    long ret = 0;

    if (!filp->f_op->unlocked_ioctl)
        return -ENOTTY;

    switch (cmd)
    {
    case COMPAT_JDI_IOCTL_ALLOCATE_PHYSICAL_MEMORY:
    {
        compat_jpudrv_buffer_t __user *data32;
        jpudrv_buffer_t __user *data;
        int err;

        data32 = compat_ptr(arg);
        data = compat_alloc_user_space(sizeof(*data));
        if (data == NULL)
            return -EFAULT;

        err = compat_get_jpu_buffer_data(data32, data);
        if (err)
            return err;
        ret = filp->f_op->unlocked_ioctl(filp, JDI_IOCTL_ALLOCATE_PHYSICAL_MEMORY, (unsigned long)data);
        err = compat_put_jpu_buffer_data(data32, data);
        return ret ? ret : err;
    }

    case COMPAT_JDI_IOCTL_FREE_PHYSICALMEMORY:
    {
        compat_jpudrv_buffer_t __user *data32;
        jpudrv_buffer_t __user *data;
        int err;

        data32 = compat_ptr(arg);
        data = compat_alloc_user_space(sizeof(*data));
        if (data == NULL)
            return -EFAULT;

        err = compat_get_jpu_buffer_data(data32, data);
        if (err)
            return err;

        return filp->f_op->unlocked_ioctl(filp, JDI_IOCTL_FREE_PHYSICALMEMORY, (unsigned long)data);
    }

    case COMPAT_JDI_IOCTL_GET_RESERVED_VIDEO_MEMORY_INFO:
    {
        compat_jpudrv_buffer_t __user *data32;
        jpudrv_buffer_t __user *data;
        int err;

        data32 = compat_ptr(arg);
        data = compat_alloc_user_space(sizeof(*data));
        if (data == NULL)
            return -EFAULT;

        err = compat_get_jpu_buffer_data(data32, data);
        if (err)
            return err;
        ret = filp->f_op->unlocked_ioctl(filp, JDI_IOCTL_GET_RESERVED_VIDEO_MEMORY_INFO, (unsigned long)data);
        err = compat_put_jpu_buffer_data(data32, data);
        return ret ? ret : err;
    }

    case COMPAT_JDI_IOCTL_WAIT_INTERRUPT:
    {
        compat_jpudrv_intr_info_t __user *data32;
        jpudrv_intr_info_t __user *data;
        int err;

        data32 = compat_ptr(arg);
        data = compat_alloc_user_space(sizeof(*data));
        if (data == NULL)
            return -EFAULT;

        err = compat_get_jpu_intr_info_data(data32, data);
        if (err)
            return err;

        ret = filp->f_op->unlocked_ioctl(filp, JDI_IOCTL_WAIT_INTERRUPT, (unsigned long)data);
        err = compat_put_jpu_intr_info_data(data32, data);
        return ret ? ret : err;
    }

    case JDI_IOCTL_ENABLE_INTERRUPT:
    case JDI_IOCTL_SET_CLOCK_GATE:
    case JDI_IOCTL_OPEN_INSTANCE:
    case JDI_IOCTL_CLOSE_INSTANCE:
    case JDI_IOCTL_GET_INSTANCE_NUM:
    case JDI_IOCTL_RESET:
    case JDI_IOCTL_SET_CLOCK_ENABLE:
    {
        return filp->f_op->unlocked_ioctl(filp, cmd,
                                          (unsigned long)compat_ptr(arg));
    }

    case COMPAT_JDI_IOCTL_GET_INSTANCE_POOL:
    {
        compat_jpudrv_buffer_t __user *data32;
        jpudrv_buffer_t __user *data;
        int err;

        data32 = compat_ptr(arg);
        data = compat_alloc_user_space(sizeof(*data));
        if (data == NULL)
            return -EFAULT;

        err = compat_get_jpu_buffer_data(data32, data);
        if (err)
            return err;
        ret = filp->f_op->unlocked_ioctl(filp, JDI_IOCTL_GET_INSTANCE_POOL, (unsigned long)data);
        err = compat_put_jpu_buffer_data(data32, data);
        return ret ? ret : err;
    }

    case COMPAT_JDI_IOCTL_GET_REGISTER_INFO:
    case COMPAT_JDI_IOCTL_GET_BONDING_INFO:
    {
        compat_jpudrv_buffer_t __user *data32;
        jpudrv_buffer_t __user *data;
        int err;

        data32 = compat_ptr(arg);
        data = compat_alloc_user_space(sizeof(*data));
        if (data == NULL)
            return -EFAULT;

        err = compat_get_jpu_buffer_data(data32, data);
        if (err)
            return err;
        if (cmd == COMPAT_JDI_IOCTL_GET_REGISTER_INFO)
            ret = filp->f_op->unlocked_ioctl(filp, JDI_IOCTL_GET_REGISTER_INFO, (unsigned long)data);
        else
            ret = filp->f_op->unlocked_ioctl(filp, JDI_IOCTL_GET_BONDING_INFO, (unsigned long)data);
        err = compat_put_jpu_buffer_data(data32, data);
        return ret ? ret : err;
    }

	case COMPAT_JDI_IOCTL_SET_RTK_DOVI_FLAG:
	{
		compat_jpudrv_dovi_info_t __user *data32;
		jpudrv_dovi_info_t __user *data;
		int err;

		data32 = compat_ptr(arg);
		data = compat_alloc_user_space(sizeof(*data));
		if (data == NULL)
			return -EFAULT;

		err = compat_get_jpu_dovi_info(data32, data);
		if (err)
			return err;
		ret = filp->f_op->unlocked_ioctl(filp, JDI_IOCTL_SET_RTK_DOVI_FLAG, (unsigned long)data);
		err = compat_put_jpu_dovi_info(data32, data);
		return ret ? ret : err;
	}

    default:
    {
        printk(KERN_ERR "[COMPAT JPU]No such IOCTL, cmd is %d\n", cmd);
        return -ENOIOCTLCMD;
    }
    }
}

