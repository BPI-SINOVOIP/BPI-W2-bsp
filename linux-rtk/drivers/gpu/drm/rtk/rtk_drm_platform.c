/*
 *
 * (C) COPYRIGHT 2012-2013 ARM Limited. All rights reserved.
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
 * rtk_drm_platform.c
 * Implementation of the Linux platform device entrypoints for RTK DRM
 */
#include <linux/version.h>
#include <linux/shmem_fs.h>
#include <linux/dma-buf.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <drm/drmP.h>
#include <drm/drm_crtc_helper.h>
#include "rtk_drm.h"

static int rtk_platform_drm_suspend(struct platform_device *dev,
					pm_message_t state)
{
	pr_info("DRM %s\n", __func__);
	return 0;
}

static int rtk_platform_drm_resume(struct platform_device *dev)
{
	pr_info("DRM %s\n", __func__);
	return 0;
}

int rtk_platform_drm_probe(struct platform_device *dev)
{
	pr_info("DRM %s\n", __func__);
	return rtk_drm_init(dev);
}

static int rtk_platform_drm_remove(struct platform_device *dev)
{
	pr_info("DRM %s\n", __func__);
	rtk_drm_exit(dev);
	return 0;
}

static struct platform_driver platform_drm_driver = {
	.probe = rtk_platform_drm_probe,
	.remove = rtk_platform_drm_remove,
	.suspend = rtk_platform_drm_suspend,
	.resume = rtk_platform_drm_resume,
	.driver = {
			.owner = THIS_MODULE,
			.name = DRIVER_NAME,
		},
};

static const struct platform_device_info rtk_drm_pdevinfo = {
	.name = DRIVER_NAME,
	.id = -1,
	.dma_mask = ~0UL
};

static struct platform_device *rtk_drm_device;

static int __init rtk_platform_drm_init(void)
{
	int ret;

	printk(KERN_ALERT "DRM %s\n", __func__);

	rtk_drm_device = platform_device_register_full(&rtk_drm_pdevinfo);
	if (rtk_drm_device == NULL) {
		pr_err("DRM platform_device_register_full() failed\n");
		return -ENOMEM;
	}

    ret = platform_driver_register(&platform_drm_driver);
	if (ret != 0) {
		pr_err("DRM platform_driver_register() failed %d\n", ret);
		goto err_pdrv_reg;
	}

	return 0;

err_pdrv_reg:
	platform_device_unregister(rtk_drm_device);

	return ret;
}

static void __exit rtk_platform_drm_exit(void)
{
	pr_info("DRM %s\n", __func__);

	platform_device_unregister(rtk_drm_device);
	platform_driver_unregister(&platform_drm_driver);
}

#ifdef MODULE
module_init(rtk_platform_drm_init);
#else
late_initcall(rtk_platform_drm_init);
#endif
module_exit(rtk_platform_drm_exit);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERSION);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_LICENSE(DRIVER_LICENCE);
MODULE_ALIAS(DRIVER_ALIAS);
