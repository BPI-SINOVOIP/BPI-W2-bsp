/*
 *
 * Copyright (C) 2011 Google, Inc.
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

#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/dma-buf.h>

#include "../ion.h"
#include "../ion_priv.h"
#include "../../uapi/ion_rtk.h"
#include "ion_rtk_carveout_heap.h"

#define ALIGNTO   32U
#define ION_ALIGN(len) ( ((len)+ALIGNTO-1) & ~(ALIGNTO-1) )

static int rtk_ion_sync_for_device(struct ion_client *client, int fd, int cmd)
{
	struct dma_buf *dmabuf;
	struct ion_buffer *buffer;
	enum dma_data_direction dir = (cmd == RTK_ION_IOC_INVALIDATE) ? DMA_FROM_DEVICE : DMA_TO_DEVICE;

	switch (cmd) {
	case RTK_ION_IOC_INVALIDATE:
	case RTK_ION_IOC_FLUSH:
		break;
	default:
		return -EINVAL;
	}

	dmabuf = dma_buf_get(fd);
	if (IS_ERR(dmabuf))
		return PTR_ERR(dmabuf);

	buffer = dmabuf->priv;

	dma_sync_sg_for_device(NULL, buffer->sg_table->sgl,
				   buffer->sg_table->nents, dir);
	dma_buf_put(dmabuf);
	return 0;
}

static int rtk_ion_sync_range_for_device(struct ion_client *client, int cmd, struct RTK_ION_IOC_SYNC_RANE *range_data)
{
	struct dma_buf *dmabuf;
	struct ion_buffer *buffer;
	enum dma_data_direction dir = (cmd == RTK_ION_IOC_INVALIDATE_RANGE) ? DMA_FROM_DEVICE : DMA_TO_DEVICE;
	int fd;

	switch (cmd) {
	case RTK_ION_IOC_INVALIDATE_RANGE:
	case RTK_ION_IOC_FLUSH_RANGE:
		break;
	default:
		return -EINVAL;
	}

	fd = (int) range_data->handle & -1U;

	dmabuf = dma_buf_get(fd);
	if (IS_ERR(dmabuf))
		return PTR_ERR(dmabuf);

	buffer = dmabuf->priv;

	dma_sync_single_for_device(NULL, range_data->phyAddr, range_data->len, dir);

	dma_buf_put(dmabuf);
	return 0;
}

static int rtk_ion_get_memory_info(struct ion_client *client, unsigned int heapMask, unsigned int flags, struct ion_rtk_carveout_meminfo * info)
{
	int i;

	if (client == NULL || info == NULL)
		goto err;

	info->usedSize = 0;
	info->freeSize = 0;

	for (i = 0; i < 32; i++) {
		struct ion_heap *			   heap;
		struct ion_rtk_carveout_ops *   ops;
		struct ion_rtk_carveout_meminfo tmp_info;
		unsigned int					target_heap_id_mask = 0x1U << i;

		if ((target_heap_id_mask & heapMask) == 0)
			continue;

		heap = ion_get_client_heap_by_mask(client, target_heap_id_mask);
		if (heap == NULL)
			continue;

		ops = get_rtk_carveout_ops(heap);
		if (ops == NULL)
			continue;

		if (ops->getMemInfo(heap, flags, &tmp_info) == 0) {
			info->usedSize += tmp_info.usedSize;
			info->freeSize += tmp_info.freeSize;
		}
	}

	return 0;
err:
	return -1;
}

static int rtk_ion_get_phy_info(struct ion_client *client, struct RTK_ION_IOC_PHY_INFO * phyInfo)
{
    int ret = -1;
    do {
        struct ion_handle * handle;
        ion_phys_addr_t addr;
        size_t len;

        handle = ion_handle_get_by_id(client, phyInfo->handle);
        if (IS_ERR(handle)) {
            ret = (int) PTR_ERR(handle);
            break;
        }
        ret = ion_phys(client, handle, &addr, &len);
        ion_handle_put(handle);

        if (ret != 0)
            break;

        phyInfo->addr = addr;
        phyInfo->len = len;
        break;
    } while (0);
    return ret;
}

long rtk_phoenix_ion_ioctl(struct ion_client *client, unsigned int cmd,
						   unsigned long arg)
{
	switch (cmd) {

	case RTK_PHOENIX_ION_GET_LAST_ALLOC_ADDR:
	{
		pr_err("%s: Outdated ioctl : RTK_PHOENIX_ION_GET_LAST_ALLOC_ADDR\n", __func__);
		return -EFAULT;
	}
	case RTK_ION_IOC_INVALIDATE:
	case RTK_ION_IOC_FLUSH:
	{
		int fd = (int) arg& -1U;
		if (rtk_ion_sync_for_device(client, fd, cmd) != 0) {
			pr_err("%s: rtk_ion_sync_for_device failed! (cmd:%d fd:%d)\n", __func__, cmd, fd);
			return -EFAULT;
		}
		break;
	}
	case RTK_ION_IOC_FLUSH_RANGE:
	case RTK_ION_IOC_INVALIDATE_RANGE:
	{
		struct RTK_ION_IOC_SYNC_RANE range_data;
		int ret = copy_from_user(&range_data, (void __user *)arg, sizeof (range_data));
		if (ret) {
			pr_err("%s:%d copy_from_user failed! (ret = %d)\n", __func__, __LINE__, ret);
			return -EFAULT;
		}
		if (rtk_ion_sync_range_for_device(client, cmd, &range_data) != 0) {
			pr_err("%s: rtk_ion_sync_range_for_device failed! (cmd:%d handle:%d)\n", __func__, cmd, (int) range_data.handle);
			return -EFAULT;
		}
		break;
	}

    case RTK_ION_IOC_GET_PHYINFO:
    {
        struct RTK_ION_IOC_PHY_INFO phyInfo;
        int ret = copy_from_user(&phyInfo, (void __user *) arg, sizeof (phyInfo));
        if (ret != 0) {
			pr_err("%s:%d copy_from_user failed! (ret = %d)\n", __func__, __LINE__, ret);
			return -EFAULT;
        }

        ret = rtk_ion_get_phy_info(client, &phyInfo);
        if (ret != 0) {
			pr_err("%s:%d rtk_ion_get_phy_info failed! (ret = %d)\n", __func__, __LINE__, ret);
			return -EFAULT;
        }

        ret = copy_to_user((void __user *) arg, &phyInfo, sizeof (phyInfo));
        if (ret != 0) {
			pr_err("%s:%d copy_to_user failed! (ret = %d)\n", __func__, __LINE__, ret);
			return -EFAULT;
        }
        break;
    }

	case RTK_ION_IOC_GET_MEMORY_INFO:
	{
		struct RTK_ION_IOC_GET_MEMORY_INFO_S user_info;
		struct ion_rtk_carveout_meminfo ion_info;
		int ret;
		ret = copy_from_user(&user_info, (void __user *)arg, sizeof (user_info));
		if (ret) {
			pr_err("%s:%d copy_from_user failed! (ret = %d)\n", __func__, __LINE__, ret);
			return -EFAULT;
		}
		ret = rtk_ion_get_memory_info(client, user_info.heapMask, user_info.flags, &ion_info);
		if (ret) {
			pr_err("%s:%d rtk_ion_get_memory_info failed! (ret = %d)\n", __func__, __LINE__, ret);
			return -EFAULT;
		}
		user_info.usedSize = (unsigned int) ion_info.usedSize & -1U;
		user_info.freeSize = (unsigned int) ion_info.freeSize & -1U;
		ret = copy_to_user((void __user *)arg, &user_info, sizeof (user_info));
		if (ret) {
			pr_err("%s:%d copy_to_user failed! (ret = %d)\n", __func__, __LINE__, ret);
			return -EFAULT;
		}
		break;
	}

	default:
		pr_err("%s: Unknown custom ioctl\n", __func__);
		return -ENOTTY;
	}
	return 0;
}

