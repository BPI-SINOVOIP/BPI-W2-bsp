#include <drm/drmP.h>
#include <drm/drm_crtc.h>
#include <drm/drm_fb_helper.h>
#include <drm/drm_crtc_helper.h>
#include <linux/module.h>

#include "rtk_gem_ion.h"
#include "rtk_drm_fb_ion.h"

struct drm_fb_ion {
    struct drm_framebuffer		fb;
    struct rtk_gem_ion_object	*obj[4];
};

struct drm_fbdev_ion {
    struct drm_fb_helper	fb_helper;
    struct drm_fb_ion	*   fb;
};

static inline struct drm_fbdev_ion *to_fbdev_ion(struct drm_fb_helper *helper)
{
    return container_of(helper, struct drm_fbdev_ion, fb_helper);
}

static inline struct drm_fb_ion *to_fb_ion(struct drm_framebuffer *fb)
{
    return container_of(fb, struct drm_fb_ion, fb);
}

static void drm_fb_ion_destroy(struct drm_framebuffer *fb)
{
    struct drm_fb_ion *fb_ion = to_fb_ion(fb);
    int i;

    drm_framebuffer_cleanup(fb);

    for (i = 0; i < 4; i++) {
        if (fb_ion->obj[i])
            drm_gem_object_unreference_unlocked(&fb_ion->obj[i]->base);
    }

    kfree(fb_ion);
}

static int drm_fb_ion_create_handle(struct drm_framebuffer *fb,
        struct drm_file *file_priv, unsigned int *handle)
{
    struct drm_fb_ion *fb_ion = to_fb_ion(fb);

    return drm_gem_handle_create(file_priv,
            &fb_ion->obj[0]->base, handle);
}

static int drm_fb_ion_framebuffer_dirty(struct drm_framebuffer *fb,
        struct drm_file *file_priv, unsigned flags, unsigned color,
        struct drm_clip_rect *clips, unsigned num_clips)
{
    //TODO
    DRM_DEBUG_KMS("[%s:%d] fb = %p, flags = 0x%x, color = 0x%x, num_clips = %d\n",
            __func__, __LINE__, fb, flags, color, num_clips);
    return 0;
}

static struct drm_framebuffer_funcs drm_fb_ion_funcs = {
    .destroy	    = drm_fb_ion_destroy,
    .create_handle	= drm_fb_ion_create_handle,
    .dirty          = drm_fb_ion_framebuffer_dirty,
};

static struct drm_fb_ion *drm_fb_ion_alloc(struct drm_device *dev,
        const struct drm_mode_fb_cmd2 *mode_cmd, struct rtk_gem_ion_object **obj,
        unsigned int num_planes)
{
    struct drm_fb_ion *fb_ion;
    int ret;
    int i;

    fb_ion = kzalloc(sizeof(*fb_ion), GFP_KERNEL);
    if (!fb_ion)
        return ERR_PTR(-ENOMEM);

    drm_helper_mode_fill_fb_struct(&fb_ion->fb, mode_cmd);

    for (i = 0; i < num_planes; i++)
        fb_ion->obj[i] = obj[i];

    ret = drm_framebuffer_init(dev, &fb_ion->fb, &drm_fb_ion_funcs);
    if (ret) {
        dev_err(dev->dev, "Failed to initialize framebuffer: %d\n", ret);
        kfree(fb_ion);
        return ERR_PTR(ret);
    }

    return fb_ion;
}

struct drm_framebuffer *drm_fb_ion_create(struct drm_device *dev,
        struct drm_file *file_priv, const struct drm_mode_fb_cmd2 *mode_cmd)
{
    struct drm_fb_ion *fb_ion;
    struct rtk_gem_ion_object *objs[4];
    struct drm_gem_object *obj;
    unsigned int hsub;
    unsigned int vsub;
    int ret;
    int i;

    hsub = drm_format_horz_chroma_subsampling(mode_cmd->pixel_format);
    vsub = drm_format_vert_chroma_subsampling(mode_cmd->pixel_format);

    for (i = 0; i < drm_format_num_planes(mode_cmd->pixel_format); i++) {
        unsigned int width = mode_cmd->width / (i ? hsub : 1);
        unsigned int height = mode_cmd->height / (i ? vsub : 1);
        unsigned int min_size;

        obj = drm_gem_object_lookup(file_priv, mode_cmd->handles[i]);
        if (!obj) {
            dev_err(dev->dev, "Failed to lookup GEM object\n");
            ret = -ENXIO;
            goto err_gem_object_unreference;
        }

        min_size = (height - 1) * mode_cmd->pitches[i]
            + width * drm_format_plane_cpp(mode_cmd->pixel_format, i)
            + mode_cmd->offsets[i];

        if (obj->size < min_size) {
            drm_gem_object_unreference_unlocked(obj);
            ret = -EINVAL;
            DRM_ERROR("[%s:%d] obj->size = %zu, min_size = %d\n", __func__, __LINE__,
                    obj->size, min_size);
            goto err_gem_object_unreference;
        }
        objs[i] = to_rtk_gem_ion_obj(obj);
    }

    fb_ion = drm_fb_ion_alloc(dev, mode_cmd, objs, i);
    if (IS_ERR(fb_ion)) {
        ret = PTR_ERR(fb_ion);
        goto err_gem_object_unreference;
    }

    DRM_DEBUG_KMS("[%s:%d] fb = %p\n", __func__, __LINE__,
            &fb_ion->fb);
    return &fb_ion->fb;

err_gem_object_unreference:
    for (i--; i >= 0; i--)
        drm_gem_object_unreference_unlocked(&objs[i]->base);
    DRM_ERROR("[%s:%d]\n", __func__, __LINE__);
    return ERR_PTR(ret);
}

struct rtk_gem_ion_object *drm_fb_ion_get_gem_obj(struct drm_framebuffer *fb,
        unsigned int plane)
{
    struct drm_fb_ion *fb_ion = to_fb_ion(fb);

    if (plane >= 4)
        return NULL;

    return fb_ion->obj[plane];
}

static struct fb_ops drm_fbdev_ion_ops = {
    .owner		= THIS_MODULE,
    .fb_fillrect	= sys_fillrect,
    .fb_copyarea	= sys_copyarea,
    .fb_imageblit	= sys_imageblit,
    .fb_check_var	= drm_fb_helper_check_var,
    .fb_set_par	= drm_fb_helper_set_par,
    .fb_blank	= drm_fb_helper_blank,
    .fb_pan_display	= drm_fb_helper_pan_display,
    .fb_setcmap	= drm_fb_helper_setcmap,
};

static int drm_fbdev_ion_create(struct drm_fb_helper *helper,
        struct drm_fb_helper_surface_size *sizes)
{
    struct drm_fbdev_ion *fbdev_ion = to_fbdev_ion(helper);
    struct drm_mode_fb_cmd2 mode_cmd = { 0 };
    struct drm_device *dev = helper->dev;
    struct rtk_gem_ion_object *obj;
    struct drm_framebuffer *fb;
    unsigned int bytes_per_pixel;
    unsigned long offset;
    struct fb_info *fbi;
    size_t size;
    int flags = 0;
    int ret;

    DRM_DEBUG_KMS("surface width(%d), height(%d) and bpp(%d)\n",
            sizes->surface_width, sizes->surface_height,
            sizes->surface_bpp);

    bytes_per_pixel = DIV_ROUND_UP(sizes->surface_bpp, 8);

    mode_cmd.width = sizes->surface_width;
    mode_cmd.height = sizes->surface_height;
    mode_cmd.pitches[0] = sizes->surface_width * bytes_per_pixel;
    mode_cmd.pixel_format = drm_mode_legacy_fb_format(sizes->surface_bpp,
            sizes->surface_depth);
    mode_cmd.flags = DRM_MODE_FB_MODIFIERS;

    size = mode_cmd.pitches[0] * mode_cmd.height;

    flags |= RTK_BOT_BUFFER_SCPUACC;
    flags |= RTK_BOT_BUFFER_HWIPACC;
    flags |= RTK_BOT_BUFFER_HEAP_MEDIA;

    obj = rtk_gem_ion_create(dev, size, flags);
    if (IS_ERR(obj))
        return -ENOMEM;

    fbi = framebuffer_alloc(0, dev->dev);
    if (!fbi) {
        dev_err(dev->dev, "Failed to allocate framebuffer info.\n");
        ret = -ENOMEM;
        goto err_rtk_gem_ion_free_object;
    }

    fbdev_ion->fb = drm_fb_ion_alloc(dev, &mode_cmd, &obj, 1);
    if (IS_ERR(fbdev_ion->fb)) {
        dev_err(dev->dev, "Failed to allocate DRM framebuffer.\n");
        ret = PTR_ERR(fbdev_ion->fb);
        goto err_framebuffer_release;
    }

    fb = &fbdev_ion->fb->fb;
    helper->fb = fb;
    helper->fbdev = fbi;

    fbi->par = helper;
    fbi->flags = FBINFO_FLAG_DEFAULT;
    fbi->fbops = &drm_fbdev_ion_ops;

    ret = fb_alloc_cmap(&fbi->cmap, 256, 0);
    if (ret) {
        dev_err(dev->dev, "Failed to allocate color map.\n");
        goto err_drm_fb_ion_destroy;
    }

    drm_fb_helper_fill_fix(fbi, fb->pitches[0], fb->depth);
    drm_fb_helper_fill_var(fbi, helper, sizes->fb_width, sizes->fb_height);

    offset = fbi->var.xoffset * bytes_per_pixel;
    offset += fbi->var.yoffset * fb->pitches[0];

    dev->mode_config.fb_base = (resource_size_t)obj->paddr;
    fbi->screen_base = obj->vaddr + offset;
    fbi->fix.smem_start = (unsigned long)(obj->paddr + offset);
    fbi->screen_size = size;
    fbi->fix.smem_len = size;

    return 0;

err_drm_fb_ion_destroy:
    drm_framebuffer_unregister_private(fb);
    drm_fb_ion_destroy(fb);
err_framebuffer_release:
    framebuffer_release(fbi);
err_rtk_gem_ion_free_object:
    rtk_gem_ion_free_object(&obj->base);
    return ret;
}

static const struct drm_fb_helper_funcs drm_fb_ion_helper_funcs = {
    .fb_probe = drm_fbdev_ion_create,
};

struct drm_fbdev_ion *drm_fbdev_ion_init(struct drm_device *dev,
        unsigned int preferred_bpp, unsigned int num_crtc,
        unsigned int max_conn_count)
{
    struct drm_fbdev_ion *fbdev_ion;
    struct drm_fb_helper *helper;
    int ret;

    fbdev_ion = kzalloc(sizeof(*fbdev_ion), GFP_KERNEL);
    if (!fbdev_ion) {
        dev_err(dev->dev, "Failed to allocate drm fbdev.\n");
        return ERR_PTR(-ENOMEM);
    }

    helper = &fbdev_ion->fb_helper;

    drm_fb_helper_prepare(dev, helper, &drm_fb_ion_helper_funcs);

    ret = drm_fb_helper_init(dev, helper, num_crtc, max_conn_count);
    if (ret < 0) {
        dev_err(dev->dev, "Failed to initialize drm fb helper.\n");
        goto err_free;
    }

    ret = drm_fb_helper_single_add_all_connectors(helper);
    if (ret < 0) {
        dev_err(dev->dev, "Failed to add connectors.\n");
        goto err_drm_fb_helper_fini;

    }

    /* disable all the possible outputs/crtcs before entering KMS mode */
    drm_helper_disable_unused_functions(dev);

    ret = drm_fb_helper_initial_config(helper, preferred_bpp);
    if (ret < 0) {
        dev_err(dev->dev, "Failed to set initial hw configuration.\n");
        goto err_drm_fb_helper_fini;
    }

    return fbdev_ion;

err_drm_fb_helper_fini:
    drm_fb_helper_fini(helper);
err_free:
    kfree(fbdev_ion);

    return ERR_PTR(ret);
}

void drm_fbdev_ion_fini(struct drm_fbdev_ion *fbdev_ion)
{
    if (fbdev_ion->fb_helper.fbdev) {
        struct fb_info *info;
        int ret;

        info = fbdev_ion->fb_helper.fbdev;
        ret = unregister_framebuffer(info);
        if (ret < 0)
            DRM_DEBUG_KMS("failed unregister_framebuffer()\n");

        if (info->cmap.len)
            fb_dealloc_cmap(&info->cmap);

        framebuffer_release(info);
    }

    if (fbdev_ion->fb) {
        drm_framebuffer_unregister_private(&fbdev_ion->fb->fb);
        drm_fb_ion_destroy(&fbdev_ion->fb->fb);
    }

    drm_fb_helper_fini(&fbdev_ion->fb_helper);
    kfree(fbdev_ion);
}

void drm_fbdev_ion_restore_mode(struct drm_fbdev_ion *fbdev_ion)
{
    if (fbdev_ion)
        drm_fb_helper_restore_fbdev_mode_unlocked(&fbdev_ion->fb_helper);
}

void drm_fbdev_ion_hotplug_event(struct drm_fbdev_ion *fbdev_ion)
{
    if (fbdev_ion)
        drm_fb_helper_hotplug_event(&fbdev_ion->fb_helper);
}
