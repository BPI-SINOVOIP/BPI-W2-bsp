/*
 *
 * (C) COPYRIGHT 2012-2014 ARM Limited. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms
 * of such GNU licence.
 *
 * A copy of the licence is included with the program, and can also be obtained
 * from Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 *
 */



/**
 * rtk_drm_drv.c
 * RTK specific functions for RTK DRM
 */
#include <linux/version.h>
#include <linux/shmem_fs.h>
#include <linux/dma-buf.h>
#include <linux/module.h>
#include <drm/drmP.h>
#include <drm/drm_crtc_helper.h>

#include "rtk_drm.h"

int rtk_device_init(struct drm_device *dev)
{
	struct rtk_drm_private *priv = dev->dev_private;
	int ret;

	if (priv == NULL) {
		pr_err("%s no private data\n", __func__);
		return -EINVAL;
	}

    ret = 0;

	goto finish;

finish:
	DRM_DEBUG_KMS("rtk_device_init returned %d\n", ret);
	return ret;
}

void rtk_device_fini(struct drm_device *dev)
{

}
