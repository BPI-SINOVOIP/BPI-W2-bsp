/*
 * drivers/soc/realtek/rtd129x/rtk_ve/ve3/compat_memalloc.h
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

#include "memalloc.h"
#include "compat_memalloc.h"

#define COMPAT_MEMALLOC_IOCSFREEBUFFER _IOW(MEMALLOC_IOC_MAGIC, 2, compat_ulong_t)

long compat_memalloc_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    long ret = 0;

    if (!filp->f_op->unlocked_ioctl)
        return -ENOTTY;

    switch (cmd)
    {
    case MEMALLOC_IOCHARDRESET:
    case MEMALLOC_IOCXGETBUFFER:
    {
        return filp->f_op->unlocked_ioctl(filp, cmd,
                                          (unsigned long)compat_ptr(arg));
    }

    case COMPAT_MEMALLOC_IOCSFREEBUFFER:
    {
        compat_ulong_t __user *data32;
        unsigned long __user *data;
        compat_ulong_t n;
        int err;

        data32 = compat_ptr(arg);
        data = compat_alloc_user_space(sizeof(*data));
        if (data == NULL)
            return -EFAULT;

        err = get_user(n, data32);
        err |= put_user(n, data);
        if (err)
            return err;

        ret = filp->f_op->unlocked_ioctl(filp, MEMALLOC_IOCSFREEBUFFER, (unsigned long)data);
        err = get_user(n, data);
        err |= put_user(n, data32);
        return ret ? ret : err;
    }
    default:
    {
        printk(KERN_ERR "[COMPAT_MEMALLOC] No such IOCTL, cmd is %d\n", cmd);
        return -ENOIOCTLCMD;
    }
    }
}
