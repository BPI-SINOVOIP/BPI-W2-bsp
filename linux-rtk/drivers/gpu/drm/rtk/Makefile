ccflags-y := -Iinclude/drm -Werror

rtk_drm-y := rtk_drm_connector.o \
    rtk_drm_crtc.o \
	rtk_drm_device.o \
	rtk_drm_encoder.o \
	rtk_drm_drv.o \
	rtk_drm_platform.o \
	rtk_drm_suspend.o \
	rtk_gem_ion.o \
	rtk_drm_fb_ion.o \
	rtk_drm_plane.o

obj-$(CONFIG_DRM_RTK) += rtk_drm.o
