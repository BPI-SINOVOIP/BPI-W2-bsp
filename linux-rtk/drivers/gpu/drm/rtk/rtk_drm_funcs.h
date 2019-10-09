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
 * rtk_drm_funcs.h
 * Function prototypes for RTK DRM
 */

#ifndef RTK_DRM_FUNCS_H_
#define RTK_DRM_FUNCS_H_

/* Platform Initialisation */
int rtk_drm_init(struct platform_device *dev);
void rtk_drm_exit(struct platform_device *dev);

/* Plane Functions */
struct rtk_drm_planes * rtk_plans_create(struct drm_device *dev);


/* CRTC Functions */
struct rtk_drm_crtc * rtk_crtc_create(struct drm_device *dev);
void rtk_crtc_finish_page_flip(struct rtk_drm_crtc *rtk_crtc);

/* Connector Functions */
struct rtk_drm_connector * rtk_connector_create(struct drm_device *dev);

/* Encoder Functions */
struct rtk_drm_encoder * rtk_encoder_create(struct drm_device *dev, int possible_crtcs);

/* Frame Buffer Functions */
void rtk_drm_mode_config_init(struct drm_device *dev);

/* Suspend Functions */
int rtk_drm_resume(struct drm_device *dev);
int rtk_drm_suspend(struct drm_device *dev, pm_message_t state);

void rtk_crtc_pending_vblank(struct drm_crtc *crtc, struct drm_file *file_priv);

int rtk_device_init(struct drm_device *dev);
void rtk_device_fini(struct drm_device *dev);
#endif /* RTK_DRM_FUNCS_H_ */
