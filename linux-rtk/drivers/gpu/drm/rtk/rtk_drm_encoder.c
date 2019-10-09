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
 * rtk_drm_encoder.c
 * Implementation of the encoder functions for RTK DRM
 */
#include <linux/version.h>
#include <linux/shmem_fs.h>
#include <linux/dma-buf.h>
#include <linux/module.h>

#include <drm/drmP.h>
#include <drm/drm_crtc_helper.h>

#include "rtk_drm.h"

bool rtk_encoder_helper_mode_fixup(struct drm_encoder *encoder,
					const struct drm_display_mode *mode,
					struct drm_display_mode *adjusted_mode)
{
	DRM_DEBUG_KMS("DRM %s on encoder=%p\n", __func__, encoder);
	return true;
}

void rtk_encoder_helper_prepare(struct drm_encoder *encoder)
{
	DRM_DEBUG_KMS("DRM %s on encoder=%p\n", __func__, encoder);
}

void rtk_encoder_helper_commit(struct drm_encoder *encoder)
{
	DRM_DEBUG_KMS("DRM %s on encoder=%p\n", __func__, encoder);
}

void rtk_encoder_helper_mode_set(struct drm_encoder *encoder,
				struct drm_display_mode *mode,
				struct drm_display_mode *adjusted_mode)
{
	DRM_DEBUG_KMS("DRM %s on encoder=%p\n", __func__, encoder);
}

void rtk_encoder_helper_disable(struct drm_encoder *encoder)
{
	DRM_DEBUG_KMS("DRM %s on encoder=%p\n", __func__, encoder);
}

void rtk_encoder_destroy(struct drm_encoder *encoder)
{
	struct rtk_drm_encoder *rtk_encoder =
					RTK_ENCODER_FROM_ENCODER(encoder);

	DRM_DEBUG_KMS("DRM %s on encoder=%p\n", __func__, encoder);

	drm_encoder_cleanup(encoder);
	kfree(rtk_encoder);
}

const struct drm_encoder_funcs encoder_funcs = {
	.destroy        = rtk_encoder_destroy,
};

const struct drm_encoder_helper_funcs encoder_helper_funcs = {
    //todo
	.mode_fixup     = rtk_encoder_helper_mode_fixup,
	.prepare        = rtk_encoder_helper_prepare,
	.commit         = rtk_encoder_helper_commit,
	.mode_set       = rtk_encoder_helper_mode_set,
	.disable        = rtk_encoder_helper_disable,
};

struct rtk_drm_encoder *rtk_encoder_create(struct drm_device *dev,
						int possible_crtcs)
{
	struct rtk_drm_encoder *rtk_encoder;

	rtk_encoder = kzalloc(sizeof(struct rtk_drm_encoder), GFP_KERNEL);
	if (rtk_encoder == NULL) {
		pr_err("Failed to allocated rtk_drm_encoder\n");
		return NULL;
	}

	//drm_encoder_init(dev, &rtk_encoder->encoder, &encoder_funcs, DRM_MODE_ENCODER_DAC);
	drm_encoder_init(dev, &rtk_encoder->base, &encoder_funcs, DRM_MODE_ENCODER_TMDS, NULL);

	drm_encoder_helper_add(&rtk_encoder->base, &encoder_helper_funcs);

	rtk_encoder->base.possible_crtcs = possible_crtcs;

	return rtk_encoder;
}

