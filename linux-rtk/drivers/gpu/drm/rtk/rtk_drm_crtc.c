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
 * rtk_drm_crtc.c
 * Implementation of the CRTC functions for RTK DRM
 */
#include <linux/version.h>
#include <linux/shmem_fs.h>
#include <linux/dma-buf.h>
#include <linux/module.h>

#include <drm/drmP.h>
#include <drm/drm_crtc_helper.h>
#include <drm/drm_atomic_helper.h>

#include "rtk_drm.h"

#include "../../../drivers/dma-buf/sync_debug.h"
#include "../../../video/fbdev/rtk/dc2vo/dc2vo.h"

#include "rtk_gem_ion.h"
#include "rtk_drm_fb_ion.h"

#define RTK_CRTC_SWAP_SHORT_FENCE_TIMEOUT_MS    (60)
#define RTK_CRTC_SWAP_LONG_FENCE_TIMEOUT_MS     (-1)

struct rtk_crtc_swap_post {
    struct list_head        head;
    struct sync_file *     fence;
    struct drm_framebuffer *fb;
    struct rtk_drm_crtc *   rtk_crtc;
    struct drm_pending_vblank_event *event;
};

static void rtk_crtc_swap_post_cleanup(struct rtk_crtc_swap_post * cfg)
{
    if (cfg == NULL)
        return;
    if (cfg->fence)
        fput(cfg->fence->file);
    kfree(cfg);
}

static void rtk_crtc_swap_post_release(struct rtk_crtc_swap_post * cfg)
{
    if (cfg == NULL)
        return;

    if (cfg->fence) {
        int err = fence_wait_timeout(cfg->fence->fence, 1, RTK_CRTC_SWAP_SHORT_FENCE_TIMEOUT_MS);
        if (err == -ETIME) {
            DRM_ERROR("DRM %s:%d fence %p\n", __FUNCTION__, __LINE__, cfg->fence);
            err = fence_wait_timeout(cfg->fence->fence, 1, RTK_CRTC_SWAP_SHORT_FENCE_TIMEOUT_MS);
        }
        if (err < 0)
            DRM_ERROR("DRM %s:%d fence %p\n", __FUNCTION__, __LINE__, cfg->fence);
    }

    if (cfg->fb) {
        struct rtk_gem_ion_object * ion_obj = drm_fb_ion_get_gem_obj(cfg->fb,0);
        drm_framebuffer_unreference(cfg->fb);
        if (ion_obj)
            drm_gem_object_unreference_unlocked(&ion_obj->base);
    }
#if 0
    {
        struct rtk_drm_crtc * rtk_crtc = cfg->rtk_crtc;
        if (rtk_crtc->vblank_en) {
            rtk_crtc->event = cfg->event;
        }
    }
#endif
    return rtk_crtc_swap_post_cleanup(cfg);
}

struct rtk_crtc_swap_post * rtk_crtc_swap_post_create(
        struct drm_framebuffer *fb, struct sync_file * fence, struct rtk_drm_crtc *rtk_crtc,
        struct drm_pending_vblank_event *event)
{
    struct rtk_crtc_swap_post * cfg = kzalloc(sizeof(*cfg), GFP_KERNEL);
    INIT_LIST_HEAD(&cfg->head);
    cfg->fence  = fence;
    cfg->fb     = fb;
    cfg->rtk_crtc = rtk_crtc;
    cfg->event = event;
    return cfg;
}

static int rtk_crtc_swap_post_to_worker(struct drm_crtc *crtc, struct drm_framebuffer *fb,
        struct drm_pending_vblank_event *event)
{
    struct rtk_drm_crtc *rtk_crtc = RTK_CRTC_FROM_CRTC(crtc);
    struct rtk_crtc_swap_post * cfg = NULL;
    struct sync_file * fence = NULL;

    {
        struct rtk_gem_ion_object * ion_obj = drm_fb_ion_get_gem_obj(fb,0);
        struct dc_buffer buf;
        memset(&buf, 0, sizeof(buf));
        buf.id                          = eUserBuffer;
        buf.overlay_engine              = eEngine_VO;
        buf.phyAddr                     = ion_obj->paddr;
        //buf.format                      = xxxxxxxxxx;
        buf.width                       = fb->width;
        buf.height                      = fb->height;
        buf.stride                      = ((fb->width * fb->bits_per_pixel) + 7)/8;
        buf.acquire.fence               = (struct sync_file *) 0;
        if (fb->pixel_format == DRM_FORMAT_XRGB8888) {
            buf.flags |= eBuffer_USE_GLOBAL_ALPHA;
            buf.alpha = 0xff;
        }

        fence = DC_QueueBuffer(&buf);
    }

    //DRM_DEBUG_KMS("[%s:%d] [%d x %d] bits_per_pixel = %d\n", __func__, __LINE__, fb->width, fb->height, fb->bits_per_pixel);

    if (fence == NULL)
        return -1;
    cfg = rtk_crtc_swap_post_create(fb, fence, rtk_crtc, event);

    if (cfg == NULL) {
        fput(fence->file);
        return -1;
    }

    if (fb) {
        struct rtk_gem_ion_object * ion_obj = drm_fb_ion_get_gem_obj(fb,0);
        if (ion_obj)
            drm_gem_object_reference(&ion_obj->base);
        drm_framebuffer_reference(fb);
    }

    {
        if (rtk_crtc->vblank_en) {
#ifdef PAGE_FLIP_ALING_WITH_VBLANK
            rtk_crtc->event = event;//crtc->state->event;
#else
            struct drm_device *dev = rtk_crtc->base.dev;
            drm_vblank_get(dev, rtk_crtc->crtc_index);
            if (event) {
                unsigned long flags;
                spin_lock_irqsave(&dev->event_lock, flags);
                drm_send_vblank_event(dev, rtk_crtc->crtc_index, event);
                spin_unlock_irqrestore(&dev->event_lock, flags);
            }
            drm_vblank_put(dev, rtk_crtc->crtc_index);
#endif
        }
    }

    mutex_lock(&rtk_crtc->swap_lock);
    list_add_tail(&cfg->head, &rtk_crtc->swap_list);
    kthread_queue_work(&rtk_crtc->swap_worker, &rtk_crtc->swap_work);
    mutex_unlock(&rtk_crtc->swap_lock);

    return 0;
}

static int show_framebuffer_on_crtc(struct drm_crtc *crtc,
        struct drm_framebuffer *fb,
        struct drm_pending_vblank_event *event)
{
    crtc->primary->fb = fb;
    if (rtk_crtc_swap_post_to_worker(crtc, fb, event) != 0) {
        pr_err("DRM %s:%d rtk_crtc_swap_post_to_worker return error!", __FUNCTION__, __LINE__);
        drm_framebuffer_reference(fb);
        return -1;
    }
    DRM_DEBUG_KMS("DRM %s %d", __FUNCTION__, __LINE__);
    return 0;
}

static int rtk_crtc_page_flip(struct drm_crtc *crtc, struct drm_framebuffer *fb,
        struct drm_pending_vblank_event *event,
        uint32_t flags)
{
    DRM_DEBUG_KMS("DRM %s: crtc=%p, fb=%p, event=%p\n", __func__, crtc, fb, event);
    //return drm_atomic_helper_page_flip(crtc, fb, event, flags);
    return show_framebuffer_on_crtc(crtc, fb, event);
}

void rtk_crtc_finish_page_flip(struct rtk_drm_crtc *rtk_crtc)
{
    struct drm_device *dev = rtk_crtc->base.dev;
    unsigned long flags;

    spin_lock_irqsave(&dev->event_lock, flags);

    if (rtk_crtc->event) {
        //drm_vblank_get(dev, rtk_crtc->crtc_index);
        //drm_send_vblank_event(dev, rtk_crtc->crtc_index, rtk_crtc->event);
        //drm_vblank_put(dev, rtk_crtc->crtc_index);

        drm_crtc_vblank_get(&rtk_crtc->base);
        drm_crtc_send_vblank_event(&rtk_crtc->base, rtk_crtc->event);
        drm_crtc_vblank_put(&rtk_crtc->base);
        rtk_crtc->event = NULL;
    }
    spin_unlock_irqrestore(&dev->event_lock, flags);
}

#if 1
static void rtk_crtc_atomic_begin(struct drm_crtc *crtc, struct drm_crtc_state *old_crtc_state)
{
    struct rtk_drm_crtc *rtk_crtc = RTK_CRTC_FROM_CRTC(crtc);

    if (crtc->state->event) {
         crtc->state->event->pipe = drm_crtc_index(crtc);
         WARN_ON(drm_crtc_vblank_get(crtc) != 0);
         rtk_crtc->event = crtc->state->event;
         crtc->state->event = NULL;
    }
}

static void rtk_crtc_atomic_flush(struct drm_crtc *crtc, struct drm_crtc_state *old_crtc_state)
{
/* TODO: write common plane control register if available */
}
#endif

__maybe_unused static int rtk_crtc_helper_mode_set(struct drm_crtc *crtc,
        struct drm_display_mode *mode,
        struct drm_display_mode *adjusted_mode,
        int x, int y, struct drm_framebuffer *old_fb)
{
    pr_info("DRM %s %d", __FUNCTION__, __LINE__);
    return 0;
}

static void rtk_crtc_helper_prepare(struct drm_crtc *crtc)
{
    DRM_DEBUG_KMS("DRM %s on crtc=%p\n", __func__, crtc);
}

static void rtk_crtc_helper_commit(struct drm_crtc *crtc)
{
    struct rtk_drm_crtc *rtk_crtc = RTK_CRTC_FROM_CRTC(crtc);
    DRM_DEBUG_KMS("DRM %s on crtc=%p\n", __func__, crtc);
    rtk_crtc->vblank_en = true;
    drm_crtc_vblank_on(crtc);
}

void rtk_crtc_pending_vblank(struct drm_crtc *crtc, struct drm_file *file_priv)
{
    struct rtk_drm_crtc *rtk_crtc = RTK_CRTC_FROM_CRTC(crtc);
    if (rtk_crtc->swap_thread) {
        kthread_flush_worker(&rtk_crtc->swap_worker);
    }
}

static bool rtk_crtc_helper_mode_fixup(struct drm_crtc *crtc,
        const struct drm_display_mode *mode,
        struct drm_display_mode *adjusted_mode)
{
    struct rtk_drm_crtc *rtk_crtc = RTK_CRTC_FROM_CRTC(crtc);
    DRM_DEBUG_KMS("DRM %s on crtc=%p\n", __func__, crtc);
    if (rtk_crtc->swap_thread) {
        kthread_flush_worker(&rtk_crtc->swap_worker);
    }
    rtk_crtc->vblank_en = false;
    //drm_crtc_vblank_off(crtc);
    return true;
}

static void rtk_crtc_helper_disable(struct drm_crtc *crtc)
{
    DRM_DEBUG_KMS("DRM %s on crtc=%p\n", __func__, crtc);
    //clcd_disable(crtc);
}

static void rtk_crtc_destroy(struct drm_crtc *crtc)
{
    struct rtk_drm_crtc *rtk_crtc = RTK_CRTC_FROM_CRTC(crtc);

    DRM_DEBUG_KMS("DRM %s on crtc=%p\n", __func__, crtc);


    if (rtk_crtc->swap_thread) {
        kthread_flush_worker(&rtk_crtc->swap_worker);
        kthread_stop(rtk_crtc->swap_thread);
    }
    drm_crtc_cleanup(crtc);
    kfree(rtk_crtc);
}

static void rtk_crtc_mode_set_nofb(struct drm_crtc *crtc)
{
    DRM_DEBUG_KMS("DRM %s on crtc=%p\n", __func__, crtc);
}

const struct drm_crtc_funcs rtk_crtc_funcs = {
    .cursor_set             = NULL,
    .cursor_move            = NULL,
    .set_config             = drm_atomic_helper_set_config,
    .page_flip              = rtk_crtc_page_flip,
    .destroy                = rtk_crtc_destroy,
    .reset                  = drm_atomic_helper_crtc_reset,
    .atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
    .atomic_destroy_state   = drm_atomic_helper_crtc_destroy_state,
};

const struct drm_crtc_helper_funcs crtc_helper_funcs = {
    .mode_set           = drm_helper_crtc_mode_set, //rtk_crtc_helper_mode_set
    .prepare            = rtk_crtc_helper_prepare,
    .commit             = rtk_crtc_helper_commit,
    .mode_fixup         = rtk_crtc_helper_mode_fixup,
    .disable            = rtk_crtc_helper_disable,
    .mode_set_nofb      = rtk_crtc_mode_set_nofb,
    .mode_set_base      = drm_helper_crtc_mode_set_base,
    .atomic_begin       = rtk_crtc_atomic_begin,
    .atomic_flush       = rtk_crtc_atomic_flush,
};

static void rtk_crtc_swap_work_func(struct kthread_work *work)
{
    struct rtk_drm_crtc *rtk_crtc = container_of(work, struct rtk_drm_crtc, swap_work);
    struct rtk_crtc_swap_post *post, *next;
    struct list_head saved_list;

    mutex_lock(&rtk_crtc->swap_lock);
    memcpy(&saved_list, &rtk_crtc->swap_list, sizeof(saved_list));
    list_replace_init(&rtk_crtc->swap_list, &saved_list);
    mutex_unlock(&rtk_crtc->swap_lock);
    list_for_each_entry_safe(post, next, &saved_list, head) {
        list_del(&post->head);
        rtk_crtc_swap_post_release(post);
    }
}

struct rtk_drm_crtc *rtk_crtc_create(struct drm_device *dev)
{
    struct rtk_drm_private *priv = dev->dev_private;
    struct rtk_drm_crtc *rtk_crtc;
    pr_info("DRM %s %d", __FUNCTION__, __LINE__);

    rtk_crtc = kzalloc(sizeof(struct rtk_drm_crtc), GFP_KERNEL);

    if (rtk_crtc == NULL) {
        pr_err("Failed to allocated rtk_drm_crtc\n");
        return NULL;
    }

    rtk_crtc->vblank_en = false;

    drm_crtc_init_with_planes(dev, &rtk_crtc->base, &priv->planes->primary->base, NULL, &rtk_crtc_funcs, NULL);
    drm_crtc_helper_add(&rtk_crtc->base, &crtc_helper_funcs);
    rtk_crtc->base.enabled = 0;
    rtk_crtc->crtc_index = drm_crtc_index(&rtk_crtc->base);

    drm_mode_crtc_set_gamma_size(&rtk_crtc->base, 256);

    INIT_LIST_HEAD(&rtk_crtc->swap_list);
    mutex_init(&rtk_crtc->swap_lock);
    kthread_init_worker(&rtk_crtc->swap_worker);
    kthread_init_work(&rtk_crtc->swap_work, rtk_crtc_swap_work_func);
    rtk_crtc->swap_thread = kthread_run(kthread_worker_fn, &rtk_crtc->swap_worker, "rtk_crtc swap_worker");
    return rtk_crtc;
}
