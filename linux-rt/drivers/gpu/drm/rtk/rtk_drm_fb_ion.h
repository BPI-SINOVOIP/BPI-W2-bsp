#ifndef __RTK_DRM_FB_ION_H__
#define __RTK_DRM_FB_ION_H__

struct drm_fbdev_ion;
struct rtk_gem_ion_object;

struct drm_framebuffer;
struct drm_device;
struct drm_file;
struct drm_mode_fb_cmd2;

struct drm_fbdev_ion *drm_fbdev_ion_init(struct drm_device *dev,
	unsigned int preferred_bpp, unsigned int num_crtc,
	unsigned int max_conn_count);

void drm_fbdev_ion_fini(struct drm_fbdev_ion *fbdev_ion);

void drm_fbdev_ion_restore_mode(struct drm_fbdev_ion *fbdev_ion);

void drm_fbdev_ion_hotplug_event(struct drm_fbdev_ion *fbdev_ion);

struct drm_framebuffer *drm_fb_ion_create(struct drm_device *dev,
	struct drm_file *file_priv, const struct drm_mode_fb_cmd2 *mode_cmd);

struct rtk_gem_ion_object *drm_fb_ion_get_gem_obj(struct drm_framebuffer *fb,
	unsigned int plane);

#endif

