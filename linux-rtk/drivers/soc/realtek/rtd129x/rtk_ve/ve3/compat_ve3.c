/*
 * drivers/soc/realtek/rtd129x/rtk_ve/ve3/compat_ve3.h
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

#include "ve3.h"
#include "compat_ve3.h"

/* See drivers/soc/realtek/rtd129x/rtk_ve/ve3/ve3.h for the definition of these structs */
struct compat_core_desc
{
    compat_uint_t id; /* id of the core */
    compat_ulong_t regs; /* pointer to user registers */
    compat_uint_t size; /* size of register space */
};

#define COMPAT_HANTRODEC_IOCGHWOFFSET _IOR(HANTRODEC_IOC_MAGIC, 3, compat_ulong_t)
#define COMPAT_HANTRODEC_IOCGHWIOSIZE _IOR(HANTRODEC_IOC_MAGIC, 4, compat_uint_t)
#define COMPAT_HANTRODEC_IOC_MC_OFFSETS _IOR(HANTRODEC_IOC_MAGIC, 7, compat_ulong_t)
#define COMPAT_HANTRODEC_IOC_MC_CORES _IOR(HANTRODEC_IOC_MAGIC, 8, compat_uint_t)
#define COMPAT_HANTRODEC_IOCS_DEC_PUSH_REG _IOW(HANTRODEC_IOC_MAGIC, 9, struct compat_core_desc)
#define COMPAT_HANTRODEC_IOCX_DEC_WAIT _IOWR(HANTRODEC_IOC_MAGIC, 15, struct compat_core_desc)
#define COMPAT_HANTRODEC_IOCS_DEC_PULL_REG _IOWR(HANTRODEC_IOC_MAGIC, 17, struct compat_core_desc)
#define COMPAT_HANTRODEC_IOCG_CORE_WAIT _IOR(HANTRODEC_IOC_MAGIC, 19, compat_int_t)
#define COMPAT_HANTRODEC_IOX_ASIC_ID _IOWR(HANTRODEC_IOC_MAGIC, 20, compat_uint_t)
#define COMPAT_HANTRODEC_GET_ASIC_REG _IOWR(HANTRODEC_IOC_MAGIC, 24, struct compat_core_desc)
#define COMPAT_HANTRODEC_BONDINGOFFSET      _IOR(HANTRODEC_IOC_MAGIC,  23, compat_ulong_t)
#define COMPAT_HANTRODEC_BONDINGIOSIZE      _IOR(HANTRODEC_IOC_MAGIC,  22, compat_uint_t)

static int compat_get_ve3_core_desc_data(
    struct compat_core_desc __user *data32,
    struct core_desc __user *data)
{
    compat_uint_t i;
    compat_ulong_t r;
    compat_uint_t s;
    int err;

    err = get_user(i, &data32->id);
    err |= put_user(i, &data->id);
    err = get_user(r, &data32->regs);
    err |= put_user(r, &data->regs);
    err |= get_user(s, &data32->size);
    err |= put_user(s, &data->size);

    return err;
}

static int compat_put_ve3_core_desc_data(
    struct compat_core_desc __user *data32,
    struct core_desc __user *data)
{
    compat_uint_t i;
    compat_ulong_t r;
    compat_uint_t s;
    int err;

    err = get_user(i, &data->id);
    err |= put_user(i, &data32->id);
    err = get_user(r, &data->regs);
    err |= put_user(r, &data32->regs);
    err |= get_user(s, &data->size);
    err |= put_user(s, &data32->size);

    return err;
}

long compat_hantrodec_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    long ret = 0;

    if (!filp->f_op->unlocked_ioctl)
        return -ENOTTY;

    switch (cmd)
    {
    case HANTRODEC_IOC_CLI:
    case HANTRODEC_IOC_STI:
    case HANTRODEC_IOCH_DEC_RESERVE:
    case HANTRODEC_IOCT_DEC_RELEASE:
    case HANTRODEC_DEBUG_STATUS:
    case HANTRODEC_SET_CLOCK_ENABLE:
    case HANTRODEC_RESET_CLK_GATING:
    case HANTRODEC_NOTIFY_RELEASE:
    case HANTRODEC_GET_ASIC_REVISION:
    {
        return filp->f_op->unlocked_ioctl(filp, cmd,
                                          (unsigned long)compat_ptr(arg));
    }

    case COMPAT_HANTRODEC_IOCGHWOFFSET:
    case COMPAT_HANTRODEC_BONDINGOFFSET:
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

        if (cmd == COMPAT_HANTRODEC_IOCGHWOFFSET)
            ret = filp->f_op->unlocked_ioctl(filp, HANTRODEC_IOCGHWOFFSET, (unsigned long)data);
        else
            ret = filp->f_op->unlocked_ioctl(filp, HANTRODEC_BONDINGOFFSET, (unsigned long)data);
        err = get_user(n, data);
        err |= put_user(n, data32);
        return ret ? ret : err;
    }

    case COMPAT_HANTRODEC_IOCGHWIOSIZE:
    case COMPAT_HANTRODEC_BONDINGIOSIZE:
    {
        compat_uint_t __user *data32;
        unsigned int __user *data;
        compat_uint_t n;
        int err;

        data32 = compat_ptr(arg);
        data = compat_alloc_user_space(sizeof(*data));
        if (data == NULL)
            return -EFAULT;

        err = get_user(n, data32);
        err |= put_user(n, data);
        if (err)
            return err;

        if (cmd == COMPAT_HANTRODEC_IOCGHWIOSIZE)
            ret = filp->f_op->unlocked_ioctl(filp, HANTRODEC_IOCGHWIOSIZE, (unsigned long)data);
        else
            ret = filp->f_op->unlocked_ioctl(filp, HANTRODEC_BONDINGIOSIZE, (unsigned long)data);
        err = get_user(n, data);
        err |= put_user(n, data32);
        return ret ? ret : err;
    }

    case COMPAT_HANTRODEC_IOC_MC_OFFSETS:
    {
        compat_ulong_t __user *data32;
        u64 __user data[HXDEC_MAX_CORES];
        compat_ulong_t n[HXDEC_MAX_CORES];
        int err;

        data32 = compat_ptr(arg);

        err = copy_from_user(n, data32, sizeof(n));
        err |= copy_to_user(data, n, sizeof(data));
        if (err)
            return err;

        ret = filp->f_op->unlocked_ioctl(filp, HANTRODEC_IOC_MC_OFFSETS, (unsigned long)data);
        err = copy_from_user(n, data, sizeof(data));
        err |= copy_to_user(n, data32, sizeof(n));
        return ret ? ret : err;
    }

    case COMPAT_HANTRODEC_IOC_MC_CORES:
    {
        compat_uint_t __user *data32;
        unsigned int __user *data;
        compat_uint_t n;
        int err;

        data32 = compat_ptr(arg);
        data = compat_alloc_user_space(sizeof(*data));
        if (data == NULL)
            return -EFAULT;

        err = get_user(n, data32);
        err |= put_user(n, data);
        if (err)
            return err;

        ret = filp->f_op->unlocked_ioctl(filp, HANTRODEC_IOC_MC_CORES, (unsigned long)data);
        err = get_user(n, data);
        err |= put_user(n, data32);
        return ret ? ret : err;
    }

    case COMPAT_HANTRODEC_IOCS_DEC_PUSH_REG:
    {
        struct compat_core_desc __user *data32;
        struct core_desc __user *data;
        int err;

        data32 = compat_ptr(arg);
        data = compat_alloc_user_space(sizeof(*data));
        if (data == NULL)
            return -EFAULT;

        err = compat_get_ve3_core_desc_data(data32, data);
        if (err)
            return err;
        ret = filp->f_op->unlocked_ioctl(filp, HANTRODEC_IOCS_DEC_PUSH_REG, (unsigned long)data);
        err = compat_put_ve3_core_desc_data(data32, data);
        return ret ? ret : err;
    }

    case COMPAT_HANTRODEC_IOCS_DEC_PULL_REG:
    {
        struct compat_core_desc __user *data32;
        struct core_desc __user *data;
        int err;

        data32 = compat_ptr(arg);
        data = compat_alloc_user_space(sizeof(*data));
        if (data == NULL)
            return -EFAULT;

        err = compat_get_ve3_core_desc_data(data32, data);
        if (err)
            return err;
        ret = filp->f_op->unlocked_ioctl(filp, HANTRODEC_IOCS_DEC_PULL_REG, (unsigned long)data);
        err = compat_put_ve3_core_desc_data(data32, data);
        return ret ? ret : err;
    }


    case COMPAT_HANTRODEC_IOCX_DEC_WAIT:
    {
        struct compat_core_desc __user *data32;
        struct core_desc __user *data;
        int err;

        data32 = compat_ptr(arg);
        data = compat_alloc_user_space(sizeof(*data));
        if (data == NULL)
            return -EFAULT;

        err = compat_get_ve3_core_desc_data(data32, data);
        if (err)
            return err;
        ret = filp->f_op->unlocked_ioctl(filp, HANTRODEC_IOCX_DEC_WAIT, (unsigned long)data);
        err = compat_put_ve3_core_desc_data(data32, data);
        return ret ? ret : err;
    }

    case COMPAT_HANTRODEC_IOCG_CORE_WAIT:
    {
        compat_uint_t __user *data32;
        unsigned int __user *data;
        compat_uint_t n;
        int err;

        data32 = compat_ptr(arg);
        data = compat_alloc_user_space(sizeof(*data));
        if (data == NULL)
            return -EFAULT;

        err = get_user(n, data32);
        err |= put_user(n, data);
        if (err)
            return err;

        ret = filp->f_op->unlocked_ioctl(filp, HANTRODEC_IOCG_CORE_WAIT, (unsigned long)data);
        err = get_user(n, data);
        err |= put_user(n, data32);
        return ret ? ret : err;
    }
    case COMPAT_HANTRODEC_IOX_ASIC_ID:
    {
        compat_uint_t __user *data32;
        unsigned int __user *data;
        compat_uint_t n;
        int err;

        data32 = compat_ptr(arg);
        data = compat_alloc_user_space(sizeof(*data));
        if (data == NULL)
            return -EFAULT;

        err = get_user(n, data32);
        err |= put_user(n, data);
        if (err)
            return err;

        ret = filp->f_op->unlocked_ioctl(filp, HANTRODEC_IOX_ASIC_ID, (unsigned long)data);
        err = get_user(n, data);
        err |= put_user(n, data32);
        return ret ? ret : err;
    }
    case COMPAT_HANTRODEC_GET_ASIC_REG:
    {
        struct compat_core_desc __user *data32;
        struct core_desc __user *data;
        int err;

        data32 = compat_ptr(arg);
        data = compat_alloc_user_space(sizeof(*data));
        if (data == NULL)
            return -EFAULT;

        err = compat_get_ve3_core_desc_data(data32, data);
        if (err)
            return err;
        ret = filp->f_op->unlocked_ioctl(filp, HANTRODEC_GET_ASIC_REG, (unsigned long)data);
        err = compat_put_ve3_core_desc_data(data32, data);
        return ret ? ret : err;
    }

    default:
    {
        printk(KERN_ERR "[COMPAT_VE3] No such IOCTL, cmd is 0x%x[0x%x, 0x%x]\n", cmd, COMPAT_HANTRODEC_BONDINGOFFSET, COMPAT_HANTRODEC_BONDINGIOSIZE);
        return -ENOIOCTLCMD;
    }
    }
}
