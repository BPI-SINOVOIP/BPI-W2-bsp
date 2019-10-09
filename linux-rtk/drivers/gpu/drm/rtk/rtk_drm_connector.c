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
 * rtk_drm_connector.c
 * Implementation of the connector functions for RTK DRM
 */
#include <linux/version.h>
#include <linux/shmem_fs.h>
#include <linux/dma-buf.h>
#include <linux/module.h>

#include <drm/drmP.h>
#include <drm/drm_atomic.h>
#include <drm/drm_crtc_helper.h>
#include <drm/drm_atomic_helper.h>
#include <drm/drm_edid.h>
#include "../drm_internal.h"
#include "rtk_drm.h"
#include "../../../media/platform/rtk_hdmitx/hdmitx_dev.h"

void rtk_connector_destroy(struct drm_connector *connector)
{
    struct rtk_drm_connector *rtk_connector =
        RTK_CONNECTOR_FROM_CONNECTOR(connector);

    DRM_DEBUG_KMS("DRM %s on connector=%p\n", __func__, connector);

    drm_connector_unreference(connector);
    drm_connector_unregister(connector);
    drm_connector_cleanup(connector);
    kfree(rtk_connector);
}

enum drm_connector_status rtk_connector_detect(struct drm_connector
        *connector, bool force)
{
    enum drm_connector_status status;

    DRM_DEBUG_KMS("DRM %s on connector=%p\n", __func__, connector);

#if 1
    status = connector_status_connected;
    drm_connector_reference(connector);
#else
    if (hdmitx_switch_get_state())
        status = connector_status_connected;
    else
        status = connector_status_disconnected;
#endif

    return status;
}

void rtk_connector_dpms(struct drm_connector *connector, int mode)
{
    DRM_DEBUG_KMS("DRM %s on connector=%p\n", __func__, connector);
}

struct drm_encoder *
rtk_connector_helper_best_encoder(struct drm_connector *connector)
{
    DRM_DEBUG_KMS("DRM %s on connector=%p\n", __func__, connector);

    if (connector->encoder != NULL) {
        return connector->encoder; /* Return attached encoder */
    } else {
        /*
         * If there is no attached encoder we choose the best candidate
         * from the list.
         * For RTK there is only one encoder so we return the first
         * one we find.
         * Other h/w would require a suitable criterion below.
         */
        struct drm_encoder *encoder = NULL;
        struct drm_device *dev = connector->dev;

        list_for_each_entry(encoder, &dev->mode_config.encoder_list,
                head) {
            if (1) { /* criterion ? */
                break;
            }
        }
        return encoder; /* return best candidate encoder */
    }
}

static struct {
       int w, h, type;
} rtk_drm_modes[] = {
       {1920, 1080,  DRM_MODE_TYPE_PREFERRED},
       {  -1,  -1, -1}
};


int rtk_connector_helper_get_modes(struct drm_connector *connector)
{
    int count = 0;
    struct drm_connector_state *state = connector->state;

#if 0
    struct i2c_adapter *p_adap = NULL;
    unsigned char bus_id= 1;
    struct edid *edid;

    if ((p_adap = i2c_get_adapter(bus_id)) != NULL) {
        edid = drm_get_edid(connector, p_adap);
        if (edid) {
            count = drm_add_edid_modes(connector, edid);
            drm_mode_connector_update_edid_property(connector, edid);
            kfree(edid);
        }
    }
#else
    unsigned char* hdmitx_edid;

    hdmitx_edid = kmalloc(2 * EDID_LENGTH, GFP_KERNEL);
    if (hdmitx_edid != NULL) {
        if (!hdmitx_get_raw_edid(hdmitx_edid)) {
            DRM_DEBUG_KMS("hdmitx_get_raw_edid success\n");
            count = drm_add_edid_modes(connector, (struct edid *)hdmitx_edid);
            drm_mode_connector_update_edid_property(connector, (struct edid *)hdmitx_edid);
        } else {
            pr_err("hdmitx_get_raw_edid failed\n");
        }
        kfree(hdmitx_edid);
    } else {
        pr_err("alloc hdmitx_edid block failed\n");
    }
#endif

    if (state != NULL) {
        if (connector->encoder != NULL) {
            //DRM_DEBUG_KMS("[DRM] %s %d set drm_connector_state encoder %p\n", __FUNCTION__, __LINE__, connector->encoder);
            state->best_encoder = connector->encoder;
            if (connector->encoder->crtc != NULL) {
                //DRM_DEBUG_KMS("[DRM] %s %d drm_connector_state crtc %p\n", __FUNCTION__, __LINE__, connector->encoder->crtc);
                state->crtc = connector->encoder->crtc;
            }
        }
    }

    if (count == 0) {
        /* default */
        int i = 0;
        while (rtk_drm_modes[i].w != -1) {
            struct drm_display_mode *mode =
                drm_mode_find_dmt(connector->dev,
                        rtk_drm_modes[i].w,
                        rtk_drm_modes[i].h,
                        60 , false);

            if (mode != NULL) {
                mode->type |= rtk_drm_modes[i].type;
                drm_mode_probed_add(connector, mode);
                count++;
            }

            i++;
        }
       DRM_DEBUG_KMS("found %d modes\n", count);

    }
    return count;
}

int rtk_connector_helper_mode_valid(struct drm_connector *connector,
        struct drm_display_mode *mode)
{
    DRM_DEBUG_KMS("DRM %s on connector=%p\n", __func__, connector);
    return MODE_OK;
}

const struct drm_connector_funcs connector_funcs = {
    //.dpms                   = rtk_connector_dpms,
    .dpms                   = drm_atomic_helper_connector_dpms,
    .detect                 = rtk_connector_detect,
    .fill_modes             = drm_helper_probe_single_connector_modes,
    .destroy                = rtk_connector_destroy,
    .reset                  = drm_atomic_helper_connector_reset,
    .atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
    .atomic_destroy_state   = drm_atomic_helper_connector_destroy_state,
};

const struct drm_connector_helper_funcs connector_helper_funcs = {
    .get_modes              = rtk_connector_helper_get_modes,
    .mode_valid             = rtk_connector_helper_mode_valid,
    .best_encoder           = rtk_connector_helper_best_encoder,
};

struct rtk_drm_connector *rtk_connector_create(struct drm_device *dev)
{
    struct rtk_drm_connector *rtk_connector;
    struct drm_connector *connector;
    int ret = 0;
    rtk_connector = kzalloc(sizeof(struct rtk_drm_connector), GFP_KERNEL);

    if (rtk_connector == NULL) {
        pr_err("Failed to allocated rtk_drm_connector\n");
        return NULL;
    }

    pr_info("DRM %s %d\n", __func__, __LINE__);
    connector = &rtk_connector->base;

    connector->display_info.width_mm    = 1920;
    connector->display_info.height_mm   = 1080;
    connector->interlace_allowed        = true;
    connector->doublescan_allowed       = false;
    connector->stereo_allowed           = false; //3D mode flags
    connector->polled                   = DRM_CONNECTOR_POLL_HPD;

    ret = drm_connector_init(dev, connector, &connector_funcs, DRM_MODE_CONNECTOR_HDMIA);
    if (ret < 0) {
        DRM_DEBUG_KMS("DRM connector_init failed\n");
        kfree(rtk_connector);
        return NULL;
    }

    drm_connector_helper_add(connector, &connector_helper_funcs);
    ret = drm_connector_register(connector);
    if (ret < 0) {
        DRM_DEBUG_KMS("DRM connector_init failed\n");
        kfree(rtk_connector);
        return NULL;
    }

    connector->dpms = DRM_MODE_DPMS_OFF;

    return rtk_connector;
}
