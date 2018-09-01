#include <linux/version.h>
#include <linux/shmem_fs.h>
#include <linux/dma-buf.h>
#include <linux/module.h>

#include <drm/drmP.h>
#include <drm/drm_crtc_helper.h>
#include <drm/drm_atomic_helper.h>

#include "rtk_drm.h"

struct rtk_drm_plane_state * rtk_drm_create_plane_state(struct drm_plane *plane)
{   
    struct rtk_drm_plane_state *state;
    DRM_DEBUG_KMS("[%s:%d]\n", __FUNCTION__, __LINE__);

    state = kzalloc(sizeof(*state), GFP_KERNEL);
    if (!state)
        return NULL;
    state->base.plane       = plane;
    state->base.rotation    = DRM_ROTATE_0;
    state->base.crtc_x      = 0;
    state->base.crtc_y      = 0;
    state->base.crtc_h      = 1080;
    state->base.crtc_w      = 1920;
    state->base.src_x       = 0;
    state->base.src_y       = 0;
    state->base.src_h       = 1080;
    state->base.src_w       = 1920;
    return state;
}

void rtk_drm_plane_destroy_state(struct drm_plane *plane,
        struct drm_plane_state *state)
{
    DRM_DEBUG_KMS("[%s:%d]\n", __FUNCTION__, __LINE__);
    drm_atomic_helper_plane_destroy_state(plane, state);
}

static const uint32_t rtk_primary_formats[] = {
    DRM_FORMAT_XRGB8888,
    DRM_FORMAT_ARGB8888,
};

static int rtk_update_plane(struct drm_plane *plane, struct drm_crtc *crtc,
        struct drm_framebuffer *fb, int crtc_x, int crtc_y,
        unsigned int crtc_w, unsigned int crtc_h,
        uint32_t src_x, uint32_t src_y, uint32_t src_w,
        uint32_t src_h)
{
    DRM_DEBUG_KMS("[%s:%d]\n", __FUNCTION__, __LINE__);
    return 0;
}

void rtk_plane_destroy(struct drm_plane *plane)
{   
    struct rtk_drm_plane *rtk_plane = RTK_PLANE_FROM_PLANE(plane);
    drm_plane_cleanup(plane);
    kfree(rtk_plane);
} 

static int rtk_disable_plane(struct drm_plane *plane)
{
    DRM_DEBUG_KMS("[%s:%d]\n", __FUNCTION__, __LINE__);
    return 0;
}

static const struct drm_plane_funcs rtk_plane_funcs = {
    .update_plane       = rtk_update_plane,
    .disable_plane      = rtk_disable_plane,
    .destroy            = rtk_plane_destroy,
    .atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
    .atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
};

int rtk_prepare_plane_fb(struct drm_plane *plane,
        struct drm_plane_state *new_state)
{
    DRM_DEBUG_KMS("[%s:%d]\n", __FUNCTION__, __LINE__);
    return 0;
}

void rtk_cleanup_plane_fb(struct drm_plane *plane,
        struct drm_plane_state *old_state)
{
    DRM_DEBUG_KMS("[%s:%d]\n", __FUNCTION__, __LINE__);
}

int rtk_plane_atomic_check(struct drm_plane *plane,
        struct drm_plane_state *state)
{
    DRM_DEBUG_KMS("[%s:%d]\n", __FUNCTION__, __LINE__);
    return 0;
}

void rtk_plane_atomic_update(struct drm_plane *plane,
        struct drm_plane_state *old_state)
{
    DRM_DEBUG_KMS("[%s:%d]\n", __FUNCTION__, __LINE__);
}

const struct drm_plane_helper_funcs rtk_plane_helper_funcs = {
    .prepare_fb     = rtk_prepare_plane_fb,
    .cleanup_fb     = rtk_cleanup_plane_fb,
    .atomic_check   = rtk_plane_atomic_check,
    .atomic_update  = rtk_plane_atomic_update,
};


struct rtk_drm_plane * rtk_drm_primary_create(struct drm_device *dev) {
    struct rtk_drm_plane *          plane = NULL;
    struct rtk_drm_plane_state *    state = NULL;

    DRM_DEBUG_KMS("[%s:%d]\n", __FUNCTION__, __LINE__);

    plane =  kzalloc(sizeof(*plane), GFP_KERNEL);
    if (plane == NULL)
        return NULL;

    state = rtk_drm_create_plane_state(&plane->base);
    if (state == NULL)
        goto err;

    plane->base.state = &state->base;

    drm_universal_plane_init(dev, &plane->base, 0,
            &rtk_plane_funcs,
            rtk_primary_formats, 2,
            DRM_PLANE_TYPE_PRIMARY, NULL);

    drm_plane_helper_add(&plane->base, &rtk_plane_helper_funcs);

    return plane;
err:
    if (state)
        rtk_drm_plane_destroy_state(&plane->base, &state->base);
    if (plane)
        kfree(plane);
    return NULL;
}



struct rtk_drm_planes * rtk_plans_create(struct drm_device *dev) {
    struct rtk_drm_planes *     planes = NULL;
    DRM_DEBUG_KMS("[%s:%d]\n", __FUNCTION__, __LINE__);
	planes = kzalloc(sizeof(*planes), GFP_KERNEL);
    if (planes == NULL)
        return NULL;

    planes->primary = rtk_drm_primary_create(dev);

    if (planes->primary == NULL) {
        kfree(planes);
        return NULL;
    }
    return planes;
}
