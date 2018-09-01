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

#ifndef _RTK_DRM_H_
#define _RTK_DRM_H_

#include <drm/drm_gem.h>
#include <drm/drm_plane_helper.h>
#include <drm/drm_fb_helper.h>
#include <linux/kthread.h>

#include "rtk_drm_fb_ion.h"
#include "../../../video/fbdev/rtk/rtk_fb.h"

#include "../../../staging/android/ion/ion.h"
#include "../../../staging/android/uapi/ion_rtk.h"
extern struct ion_device *rtk_phoenix_ion_device;

#define DRIVER_AUTHOR    "Realtek"
#define DRIVER_NAME      "rtk_drm"
#define DRIVER_DESC      "DRM module for RTK"
#define DRIVER_LICENCE   "GPL"
#define DRIVER_ALIAS     "platform:rtk_drm"
#define DRIVER_DATE      "20170207"
#define DRIVER_VERSION   "1.0"
#define DRIVER_MAJOR      1
#define DRIVER_MINOR      5
#define DRIVER_PATCHLEVEL 0

/*
 * Number of flips allowed in flight at any one time. Any more flips requested
 * beyond this value will cause the caller to block until earlier flips have
 * completed.
 *
 * For performance reasons, this must be greater than the number of buffers
 * used in the rendering pipeline. Note that the rendering pipeline can contain
 * different types of buffer, e.g.:
 * - 2 final framebuffers
 * - >2 geometry buffers for GPU use-cases
 * - >2 vertex buffers for GPU use-cases
 *
 * For example, a system using 5 geometry buffers could have 5 flips in flight,
 * and so NR_FLIPS_IN_FLIGHT_THRESHOLD must be 5 or greater.
 *
 * Whilst there may be more intermediate buffers (such as vertex/geometry) than
 * final framebuffers, KDS is used to ensure that GPU rendering waits for the
 * next off-screen buffer, so it doesn't overwrite an on-screen buffer and
 * produce tearing.
 */

/*
 * Here, we choose a conservative value. A lower value is most likely
 * suitable for GPU use-cases.
 */
//#define NR_FLIPS_IN_FLIGHT_THRESHOLD 16

#define CLCD_IRQ_NEXTBASE_UPDATE (1u<<2)

// Parameters for different buffer objects and type:

//#define RTK_USE_FBHELPER

#define PAGE_FLIP_ALING_WITH_VBLANK

struct rtk_drm_plane {
    struct drm_plane base;
};

struct rtk_drm_plane_state {
    struct drm_plane_state base;
};

struct rtk_drm_planes {
    struct rtk_drm_plane *primary;
};

struct rtk_drm_crtc {
    struct drm_crtc base;
    int crtc_index;
    struct drm_display_mode *new_mode;
    struct drm_display_mode *current_mode;
    bool vblank_en;
    struct drm_pending_vblank_event *event;

    struct list_head      swap_list;
    struct mutex          swap_lock;
    struct task_struct *  swap_thread;
    struct kthread_work   swap_work;
    struct kthread_worker swap_worker;
};

struct rtk_drm_connector {
    struct drm_connector base;
};

struct rtk_drm_encoder {
    struct drm_encoder base;
};

struct rtk_drm_private {
    struct rtk_drm_crtc *      rtk_crtc;
    struct drm_gem_object *    fbdev_bo;
    struct rtk_drm_planes *    planes;
    struct rtk_drm_connector * connector;
    struct rtk_drm_encoder *   encoder;
#ifdef RTK_USE_FBHELPER
    struct drm_fbdev_ion *     fbhelper;
#endif
    struct task_struct *       vblank_task;
};

#define RTK_CRTC_FROM_CRTC(x)               (container_of(x, struct rtk_drm_crtc, base))
#define RTK_ENCODER_FROM_ENCODER(x)         (container_of(x, struct rtk_drm_encoder, base))
#define RTK_CONNECTOR_FROM_CONNECTOR(x)     (container_of(x, struct rtk_drm_connector, base))
#define RTK_PLANE_FROM_PLANE(x)             (container_of(x, struct rtk_drm_plane, base))

#include "rtk_drm_funcs.h"

#endif /* _RTK_DRM_H_ */
