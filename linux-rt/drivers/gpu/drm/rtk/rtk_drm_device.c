/*
 *
 * (C) COPYRIGHT 2012-2015 ARM Limited. All rights reserved.
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
 * rtk_drm_device.c
 * Implementation of the Linux device driver entrypoints for RTK DRM
 */
#include <linux/version.h>
#include <linux/shmem_fs.h>
#include <linux/dma-buf.h>
#include <linux/module.h>
#include <linux/slab.h>

#include <drm/drmP.h>
#include <drm/drm_crtc_helper.h>
#include <drm/drm_atomic_helper.h>
#include "rtk_gem_ion.h"
#include "rtk_drm.h"

#include "../../../video/fbdev/rtk/dc2vo/dc2vo.h"

void rtk_drm_preclose(struct drm_device *dev, struct drm_file *file_priv)
{
    struct rtk_drm_private *priv = dev->dev_private;
    DRM_DEBUG_KMS("DRM %s on dev=%p\n", __func__, dev);
    if (priv != NULL && priv->rtk_crtc != NULL)
        rtk_crtc_pending_vblank(&priv->rtk_crtc->base, file_priv);
}

/*
 * rtk does not have a proper HW counter for vblank IRQs so enable_vblank
 * and disable_vblank are just no op callbacks.
 */
static int rtk_enable_vblank(struct drm_device *dev, unsigned int pipe)
{
    DRM_DEBUG_KMS("%s: dev=%p, crtc=%d", __func__, dev, pipe);
    return 0;
}

static void rtk_disable_vblank(struct drm_device *dev, unsigned int pipe)
{
    DRM_DEBUG_KMS("%s: dev=%p, crtc=%d", __func__, dev, pipe);
}

static int vblank_thread(void *data)
{
    struct drm_device *dev = (struct drm_device *)data;
    unsigned long long nsecs = 0;
#ifdef PAGE_FLIP_ALING_WITH_VBLANK
    struct rtk_drm_private *priv = dev->dev_private;
#endif
    do {
        drm_handle_vblank(dev, 0);
#ifdef PAGE_FLIP_ALING_WITH_VBLANK
        rtk_crtc_finish_page_flip(priv->rtk_crtc);
#endif
        DC_VsyncWait(&nsecs);
    } while(!kthread_should_stop());

    return 0;
}

static void rtk_drm_driver_lastclose(struct drm_device *dev)
{
#ifdef RTK_USE_FBHELPER
    struct rtk_drm_private *priv = dev->dev_private;
    if (priv->fbhelper)
        drm_fbdev_ion_restore_mode(priv->fbhelper);
#endif
}

static void rtk_drm_output_poll_changed(struct drm_device *dev)
{
#ifdef RTK_USE_FBHELPER
    struct rtk_drm_private *priv = dev->dev_private;
    if (priv->fbhelper)
        drm_fbdev_ion_hotplug_event(priv->fbhelper);
#endif
}

struct drm_mode_config_funcs mode_config_funcs = {
    .fb_create           = drm_fb_ion_create,
    .output_poll_changed = rtk_drm_output_poll_changed,
    .atomic_check        = drm_atomic_helper_check,
    .atomic_commit       = drm_atomic_helper_commit,
};

void rtk_drm_mode_config_init(struct drm_device *dev)
{
    drm_mode_config_init(dev);
    dev->mode_config.min_width       = 0;
    dev->mode_config.min_height      = 0;
    dev->mode_config.max_width       = 1920; //3840
    dev->mode_config.max_height      = 1080; //2160
    //dev->mode_config.async_page_flip = true;
    dev->mode_config.funcs           = &mode_config_funcs;
}

static int rtk_modeset_init(struct drm_device *dev)
{
    struct rtk_drm_private *priv = dev->dev_private;
    int ret = 0;

    if (priv == NULL)
        return -EINVAL;

    rtk_drm_mode_config_init(dev);

    priv->planes = rtk_plans_create(dev);
    if (priv->planes == NULL) {
        pr_err("Failed to create rtk_drm_planes\n");
        ret = -ENOMEM;
        goto out_config;
    }

    priv->rtk_crtc = rtk_crtc_create(dev);
    if (priv->rtk_crtc == NULL) {
        pr_err("Failed to create rtk_drm_crtc\n");
        ret = -ENOMEM;
        goto out_config;
    }

    priv->connector = rtk_connector_create(dev);
    if (priv->connector == NULL) {
        pr_err("Failed to create rtk_drm_connector\n");
        ret = -ENOMEM;
        goto out_config;
    }

    priv->encoder = rtk_encoder_create(dev, 1);
    if (priv->encoder == NULL) {
        pr_err("Failed to create rtk_drm_encoder\n");
        ret = -ENOMEM;
        goto out_config;
    }

    ret = drm_mode_connector_attach_encoder(&priv->connector->base, &priv->encoder->base);
    if (ret != 0) {
        DRM_ERROR("Failed to attach encoder\n");
        goto out_config;
    }

    priv->connector->base.encoder = &priv->encoder->base;

    priv->encoder->base.crtc = &priv->rtk_crtc->base;

#ifdef RTK_USE_FBHELPER
    priv->fbhelper = drm_fbdev_ion_init(dev, 32,
            dev->mode_config.num_crtc,
            dev->mode_config.num_connector);
#endif

    goto finish;

out_config:
    drm_mode_config_cleanup(dev);
finish:
    DRM_DEBUG("%s returned %d\n", __func__, ret);
    return ret;
}

static void rtk_modeset_fini(struct drm_device *dev)
{
    drm_mode_config_cleanup(dev);
}

static int rtk_drm_load(struct drm_device *dev, unsigned long flags)
{
    int ret = 0;
    struct rtk_drm_private *priv;
    pr_info("DRM %s %d\n", __func__, __LINE__);

    //drm_atomic = 1;
    //drm_debug=1;

    priv = kzalloc(sizeof(struct rtk_drm_private), GFP_KERNEL);
    if (!priv)
        return -ENOMEM;

    dev->dev_private = priv;

    ret = rtk_gem_ion_device_init(dev);
    if (ret != 0) {
        DRM_ERROR("[%s:%d] Failed to init rtk_gem_ion\n", __func__, __LINE__);
        kfree(priv);
        return -ENOMEM;
    }

    ret = rtk_modeset_init(dev);
    if (ret != 0) {
        pr_err("Failed to init modeset\n");
        goto out_slab;
    }

    ret = rtk_device_init(dev);
    if (ret != 0) {
        DRM_ERROR("Failed to init MMIO and IRQ\n");
        goto out_modeset;
    }

    drm_mode_config_reset(dev);

    /* syncpoints are used for full 32-bit hardware VBLANK counters */
    dev->max_vblank_count = 0xffffffff;

    ret = drm_vblank_init(dev, 1);
    if (ret != 0) {
        DRM_ERROR("Failed to init vblank\n");
        goto out_vblank;
    }

    /*
     * enable drm irq mode.
     * - with irq_enabled = true, we can use the vblank feature.
     *
     * P.S. note that we wouldn't use drm irq handler but
     *      just specific driver own one instead because
     *      drm framework supports only one irq handler and
     *      drivers can well take care of their interrupts
     */
    dev->irq_enabled = true;

    platform_set_drvdata(dev->platformdev, dev);

    //drm_kms_helper_poll_init(dev);

    priv->vblank_task = kthread_create(vblank_thread, dev, "vblank thread");
    if (IS_ERR(priv->vblank_task)) {
        DRM_ERROR("create vblank thread failed\n");
    } else {
        pr_info("create vblank thread success\n");
        wake_up_process(priv->vblank_task);
    }

    pr_info("DRM %s %d\n", __func__, __LINE__);
    goto finish;

out_vblank:
    rtk_device_fini(dev);
out_modeset:
    rtk_modeset_fini(dev);
out_slab:
finish:
    DRM_DEBUG_KMS("rtk_drm_load returned %d\n", ret);
    return ret;
}

static int rtk_drm_unload(struct drm_device *dev)
{
    struct rtk_drm_private *priv = dev->dev_private;
    pr_info("DRM %s\n", __func__);

    //drm_kms_helper_poll_fini(dev);

    if (!IS_ERR(priv->vblank_task)){
        int ret = kthread_stop(priv->vblank_task);
        pr_info("thread function has run %d\n", ret);
    }

#ifdef RTK_USE_FBHELPER
    if (priv->fbhelper)
        drm_fbdev_ion_fini(priv->fbhelper);
#endif
    rtk_modeset_fini(dev);
    drm_vblank_cleanup(dev);
    rtk_device_fini(dev);
    rtk_gem_ion_device_deinit(dev);

    if (priv != NULL) {
        kfree(dev->dev_private);
        dev->dev_private = NULL;
    }
    return 0;
}

static const struct file_operations drm_fops = {
    .owner          = THIS_MODULE,
    .open           = drm_open,
    .release        = drm_release,
    .unlocked_ioctl = drm_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl   = drm_compat_ioctl,
#endif
    .mmap           = rtk_gem_ion_mmap,
    .poll           = drm_poll,
    .read           = drm_read,
};

static struct drm_ioctl_desc rtk_ioctls[] = {
    //DRM_IOCTL_DEF_DRV(RTK_GEM_CREATE, rtk_drm_gem_create_ioctl, DRM_UNLOCKED),
    //DRM_IOCTL_DEF_DRV(RTK_GEM_MAP, rtk_gem_mmap, DRM_UNLOCKED),
};

static struct drm_driver driver = {
    .driver_features = DRIVER_MODESET | DRIVER_GEM | DRIVER_PRIME | DRIVER_ATOMIC /*| DRIVER_HAVE_IRQ*/ | DRIVER_RENDER,
    .load                       = rtk_drm_load,
    .unload                     = rtk_drm_unload,
    //.set_busid                  = drm_platform_set_busid,
    .preclose                   = rtk_drm_preclose,
    .get_vblank_counter         = drm_vblank_count,
    .enable_vblank              = rtk_enable_vblank,
    .disable_vblank             = rtk_disable_vblank,
    //.suspend                    = rtk_drm_suspend,
    //.resume                     = rtk_drm_resume,
    .gem_free_object            = rtk_gem_ion_free_object,
    .gem_vm_ops                 = &rtk_gem_ion_vm_ops,
    .gem_prime_get_sg_table     = rtk_gem_ion_prime_get_sg_table,
    .gem_prime_import_sg_table  = rtk_gem_ion_prime_import_sg_table,
    .gem_prime_vmap             = rtk_gem_ion_prime_vmap,
    .gem_prime_vunmap           = rtk_gem_ion_prime_vunmap,
    .gem_prime_mmap             = rtk_gem_ion_prime_mmap,
    .dumb_create                = rtk_gem_ion_dumb_create,
    .dumb_map_offset            = rtk_gem_ion_dumb_map_offset,
    .dumb_destroy               = drm_gem_dumb_destroy,
    .gem_prime_export           = drm_gem_prime_export,
    .gem_prime_import           = drm_gem_prime_import,
    .prime_handle_to_fd         = drm_gem_prime_handle_to_fd,
    .prime_fd_to_handle         = drm_gem_prime_fd_to_handle,
    .ioctls                     = rtk_ioctls,
    .num_ioctls                 = ARRAY_SIZE(rtk_ioctls),
    .fops                       = &drm_fops,
    .name                       = DRIVER_NAME,
    .desc                       = DRIVER_DESC,
    .date                       = DRIVER_DATE,
    .major                      = DRIVER_MAJOR,
    .minor                      = DRIVER_MINOR,
    .patchlevel                 = DRIVER_PATCHLEVEL,
    .lastclose                  = rtk_drm_driver_lastclose,
};

int rtk_drm_init(struct platform_device *dev)
{
    int ret;
    pr_info("DRM %s\n", __func__);
    pr_info("RTK DRM initialize, driver name: %s, version %d.%d\n",
            DRIVER_NAME, DRIVER_MAJOR, DRIVER_MINOR);
    ret = 0;
    return drm_platform_init(&driver, dev);
}

void rtk_drm_exit(struct platform_device *dev)
{
    pr_info("DRM %s\n", __func__);
    drm_put_dev(platform_get_drvdata(dev));
}
