/**
 * rtk_fb_RPC.c - Realtek frame buffer driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <linux/wait.h>
#include <linux/moduleparam.h>
#include <linux/delay.h>
#include <sound/core.h>
#include <sound/control.h>
#include <sound/pcm.h>
#include <sound/rawmidi.h>
#include <sound/initval.h>
#include <linux/mutex.h>
#include <linux/ioctl.h> /* needed for the _IOW etc stuff used later */
#include <linux/syscalls.h> /* needed for the _IOW etc stuff used later */
#include <linux/mpage.h>
#include <linux/dcache.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include <linux/dma-mapping.h>
#include <sound/asound.h>
#include <asm/cacheflush.h>
#include <soc/realtek/kernel-rpc.h>
#include "debug.h"

#include "rtk_fb.h"
#include "rtk_fb_RPC.h"
#include "dc2vo/dc2vo.h"

#include "dc2vo/dc_rpc.h"

//////////////////
// Main Control //
//////////////////
#define USE_ION_FB_HEAP
//#define CAPTURE_USE_PTS_RING
//#define USE_COPY_OPS

///////////////////
// Debug Control //
///////////////////
//#define _TRACE_FB_RPC

#ifdef _TRACE_FB_RPC
#define TRACE_RPC() printk(KERN_ALERT "�� fb %s\n", __FUNCTION__);
#else
#define TRACE_RPC()
#endif

#ifdef USE_ION_FB_HEAP
#include "../../../../drivers/staging/android/ion/ion.h"
#include "../../../../drivers/staging/android/uapi/ion_rtk.h"
extern struct ion_device *rtk_phoenix_ion_device;

#endif

static struct ion_client *rtkfb_client;
static struct ion_handle *rtkfb_handle;
#define HDMI_OUT_EN         1
#define HDMI_VER            2
#define HDMI_EDID_SIZE      5

//extern struct ion_client *rtkfb_client;

#define S_OK        0x10000000

#if defined(CONFIG_ARCH_RTD129x) || defined(CONFIG_ARCH_RTD119X)
#define CONVERT_FOR_AVCPU(x)        ((unsigned int)(x) | 0xA0000000)
#else
#define CONVERT_FOR_AVCPU(x)        (x)
#endif
#define AUDIO_ION_FLAG              (ION_FLAG_NONCACHED |ION_FLAG_SCPUACC | ION_FLAG_ACPUACC)

typedef enum
{
    ENUM_KERNEL_RPC_CREATE_AGENT,   // 0
    ENUM_KERNEL_RPC_INIT_RINGBUF,
    ENUM_KERNEL_RPC_PRIVATEINFO,
    ENUM_KERNEL_RPC_RUN,
    ENUM_KERNEL_RPC_PAUSE,
    ENUM_KERNEL_RPC_SWITCH_FOCUS,   // 5
    ENUM_KERNEL_RPC_MALLOC_ADDR,
    ENUM_KERNEL_RPC_VOLUME_CONTROL,      // AUDIO_CONFIG_COMMAND
    ENUM_KERNEL_RPC_FLUSH,               // AUDIO_RPC_SENDIO
    ENUM_KERNEL_RPC_CONNECT,             // AUDIO_RPC_CONNECTION
    ENUM_KERNEL_RPC_SETREFCLOCK,    // 10     // AUDIO_RPC_REFCLOCK
    ENUM_KERNEL_RPC_DAC_I2S_CONFIG,      // AUDIO_CONFIG_DAC_I2S
    ENUM_KERNEL_RPC_DAC_SPDIF_CONFIG,    // AUDIO_CONFIG_DAC_SPDIF
    ENUM_KERNEL_RPC_HDMI_OUT_EDID,       // AUDIO_HDMI_OUT_EDID_DATA
    ENUM_KERNEL_RPC_HDMI_OUT_EDID2,      // AUDIO_HDMI_OUT_EDID_DATA2
    ENUM_KERNEL_RPC_HDMI_SET,       // 15     // AUDIO_HDMI_SET
    ENUM_KERNEL_RPC_HDMI_MUTE,           //AUDIO_HDMI_MUTE_INFO
    ENUM_KERNEL_RPC_ASK_DBG_MEM_ADDR,
    ENUM_KERNEL_RPC_DESTROY,
    ENUM_KERNEL_RPC_STOP,
    ENUM_KERNEL_RPC_CHECK_READY,     // 20    // check if Audio get memory pool from AP
    ENUM_KERNEL_RPC_GET_MUTE_N_VOLUME,   // get mute and volume level
    ENUM_KERNEL_RPC_EOS,
    ENUM_KERNEL_RPC_ADC0_CONFIG,
    ENUM_KERNEL_RPC_ADC1_CONFIG,
    ENUM_KERNEL_RPC_ADC2_CONFIG,    // 25
#if defined(AUDIO_TV_PLATFORM)
    ENUM_KERNEL_RPC_BBADC_CONFIG,
    ENUM_KERNEL_RPC_I2SI_CONFIG,
    ENUM_KERNEL_RPC_SPDIFI_CONFIG,
#endif // AUDIO_TV_PLATFORM
    ENUM_KERNEL_RPC_HDMI_OUT_VSDB,
    ENUM_VIDEO_KERNEL_RPC_CONFIG_TV_SYSTEM,
    ENUM_VIDEO_KERNEL_RPC_CONFIG_HDMI_INFO_FRAME,
    ENUM_VIDEO_KERNEL_RPC_QUERY_DISPLAY_WIN,
    ENUM_VIDEO_KERNEL_RPC_PP_INIT_PIN,
    ENUM_KERNEL_RPC_INIT_RINGBUF_AO, //need check this enum
    ENUM_VIDEO_KERNEL_RPC_VOUT_EDID_DATA,
    ENUM_KERNEL_RPC_AUDIO_POWER_SET,
    ENUM_VIDEO_KERNEL_RPC_VOUT_VDAC_SET,
    ENUM_VIDEO_KERNEL_RPC_QUERY_CONFIG_TV_SYSTEM,
    ENUM_KERNEL_RPC_AUDIO_CONFIG,
    ENUM_KERNEL_RPC_AIO_PRIVATEINFO,
    ENUM_KERNEL_RPC_QUERY_FW_DEBUG_INFO,
    ENUM_KERNEL_RPC_HDMI_RX_LATENCY_MEM,
    ENUM_KERNEL_RPC_EQ_CONFIG,
    ENUM_VIDEO_KERNEL_RPC_CREATE,
    ENUM_VIDEO_KERNEL_RPC_DISPLAY,
    ENUM_VIDEO_KERNEL_RPC_CONFIGUREDISPLAYWINDOW,
    ENUM_VIDEO_KERNEL_RPC_SETREFCLOCK,
    ENUM_VIDEO_KERNEL_RPC_RUN,
    ENUM_VIDEO_KERNEL_RPC_INITRINGBUFFER,
    ENUM_VIDEO_KERNEL_RPC_SETRESCALEMODE
} ENUM_FB_KERNEL_RPC_CMD;

enum VIDEO_VF_TYPE {
    VF_TYPE_VIDEO_MPEG2_DECODER = 0,
    VF_TYPE_VIDEO_MPEG4_DECODER = 1,
    VF_TYPE_VIDEO_DIVX_DECODER = 2,
    VF_TYPE_VIDEO_H263_DECODER = 3,
    VF_TYPE_VIDEO_H264_DECODER = 4,
    VF_TYPE_VIDEO_VC1_DECODER = 5,
    VF_TYPE_VIDEO_REAL_DECODER = 6,
    VF_TYPE_VIDEO_JPEG_DECODER = 7,
    VF_TYPE_VIDEO_MJPEG_DECODER = 8,
    VF_TYPE_SPU_DECODER = 9,
    VF_TYPE_VIDEO_OUT = 10,
    VF_TYPE_TRANSITION = 11,
    VF_TYPE_THUMBNAIL = 12,
    VF_TYPE_VIDEO_VP6_DECODER = 13,
    VF_TYPE_VIDEO_IMAGE_DECODER = 14,
    VF_TYPE_FLASH = 15,
    VF_TYPE_VIDEO_AVS_DECODER = 16,
    VF_TYPE_MIXER = 17,
    VF_TYPE_VIDEO_VP8_DECODER = 18,
    VF_TYPE_VIDEO_WMV7_DECODER = 19,
    VF_TYPE_VIDEO_WMV8_DECODER = 20,
    VF_TYPE_VIDEO_RAW_DECODER = 21,
    VF_TYPE_VIDEO_THEORA_DECODER = 22,
    VF_TYPE_VIDEO_FJPEG_DECODER = 23,
    VF_TYPE_VIDEO_H265_DECODER = 24,
    VF_TYPE_VIDEO_VP9_DECODER = 25,
};
typedef enum VIDEO_VF_TYPE VIDEO_VF_TYPE;

enum VO_VIDEO_PLANE {
    VO_VIDEO_PLANE_V1 = 0,
    VO_VIDEO_PLANE_V2 = 1,
    VO_VIDEO_PLANE_SUB1 = 2,
    VO_VIDEO_PLANE_OSD1 = 3,
    VO_VIDEO_PLANE_OSD2 = 4,
    VO_VIDEO_PLANE_WIN1 = 5,
    VO_VIDEO_PLANE_WIN2 = 6,
    VO_VIDEO_PLANE_WIN3 = 7,
    VO_VIDEO_PLANE_WIN4 = 8,
    VO_VIDEO_PLANE_WIN5 = 9,
    VO_VIDEO_PLANE_WIN6 = 10,
    VO_VIDEO_PLANE_WIN7 = 11,
    VO_VIDEO_PLANE_WIN8 = 12,
    VO_VIDEO_PLANE_SUB2 = 13,
    VO_VIDEO_PLANE_CSR = 14,
    VO_VIDEO_PLANE_NONE = 255,
};
typedef enum VO_VIDEO_PLANE VO_VIDEO_PLANE;

enum VO_RESCALE_MODE {
    VO_RESCALE_MODE_KEEP_AR_AUTO = 0,
    VO_RESCALE_MODE_KEEP_AR_LB_CNTR = 1,
    VO_RESCALE_MODE_KEEP_AR_LB_TOP = 2,
    VO_RESCALE_MODE_KEEP_AR_PS_CNTR = 3,
    VO_RESCALE_MODE_KEEP_AR_PS_AUTO = 4,
    VO_RESCALE_MODE_FULL_SCALE = 5,
    VO_RESCALE_MODE_USER_DEFINE = 6,
};
typedef enum VO_RESCALE_MODE VO_RESCALE_MODE;

////////////////////////////////

typedef uint32_t HRESULT;

typedef struct RPCRES_LONG {
    HRESULT result;
    int data;
}RPCRES_LONG;

typedef struct {
    uint32_t inst_id;
    RPCRES_LONG retval;
    HRESULT res;
} VIDEO_RPC_RUN_T;

struct VIDEO_RPC_INSTANCE {
    enum VIDEO_VF_TYPE type;
};
typedef struct VIDEO_RPC_INSTANCE VIDEO_RPC_INSTANCE;

typedef struct {
    VIDEO_RPC_INSTANCE info;
    RPCRES_LONG retval;
    HRESULT ret;
} RPC_CREATE_VIDEO_AGENT_T;

struct VIDEO_RPC_VO_FILTER_DISPLAY {
    u_int instanceID;
    enum VO_VIDEO_PLANE videoPlane;
    u_char zeroBuffer;
    u_char realTimeSrc;
};
typedef struct VIDEO_RPC_VO_FILTER_DISPLAY VIDEO_RPC_VO_FILTER_DISPLAY;

typedef struct {
    u_int instanceID;
    enum VO_VIDEO_PLANE videoPlane;
    u_char zeroBuffer;
    u_char realTimeSrc;
    RPCRES_LONG retval;
    HRESULT ret;
} VIDEO_RPC_VO_FILTER_DISPLAY_T;

struct VO_COLOR {
    u_char c1;
    u_char c2;
    u_char c3;
    u_char isRGB;
};
typedef struct VO_COLOR VO_COLOR;

struct VIDEO_RPC_VOUT_CONFIG_DISP_WIN {
    enum VO_VIDEO_PLANE videoPlane;
    struct VO_RECTANGLE videoWin;
    struct VO_RECTANGLE borderWin;
    struct VO_COLOR borderColor;
    u_char enBorder;
};
typedef struct VIDEO_RPC_VOUT_CONFIG_DISP_WIN VIDEO_RPC_VOUT_CONFIG_DISP_WIN;

typedef struct {
    enum VO_VIDEO_PLANE videoPlane;
    struct VO_RECTANGLE videoWin;
    struct VO_RECTANGLE borderWin;
    struct VO_COLOR borderColor;
    u_char enBorder;
    RPCRES_LONG retval;
    HRESULT ret;
} VIDEO_RPC_VOUT_CONFIG_DISP_WIN_T;

typedef struct {
    int instanceID;
    int pRefClock;
} VIDEO_RPC_REFCLOCK;

typedef struct {
    int instanceID;
    int pRefClock;
    RPCRES_LONG ret;
    HRESULT res;
} VIDEO_RPC_REFCLOCK_T;

typedef enum _tagAutoMasterState{
  AUTOMASTER_NOT_MASTER,
  AUTOMASTER_IS_MASTER
} AUTOMASTER_STATE;

typedef struct {
    u_int instanceID;
    u_int pinID;
    u_int readPtrIndex;
    u_int pRINGBUFF_HEADER;
}VIDEO_RPC_RINGBUFFER;

typedef struct {
    RPCRES_LONG ret;
    HRESULT         res;
    u_int instanceID;
    u_int pinID;
    u_int readPtrIndex;
    u_int pRINGBUFF_HEADER;
} VIDEO_RPC_RINGBUFFER_T;

struct VIDEO_RPC_VOUT_SET_RESCALE_MODE {
    enum VO_VIDEO_PLANE videoPlane;
    enum VO_RESCALE_MODE rescaleMode;
    struct VO_RECTANGLE rescaleWindow;
    u_char delayExec;
};
typedef struct VIDEO_RPC_VOUT_SET_RESCALE_MODE VIDEO_RPC_VOUT_SET_RESCALE_MODE;

typedef struct {
    enum VO_VIDEO_PLANE videoPlane;
    enum VO_RESCALE_MODE rescaleMode;
    struct VO_RECTANGLE rescaleWindow;
    u_char delayExec;
    RPCRES_LONG retval;
    HRESULT ret;
} VIDEO_RPC_VOUT_SET_RESCALE_MODE_T;

struct AUDIO_HDMI_OUT_EDID_DATA2 {
    u_int Version;
    u_int HDMI_output_enable;
    u_int EDID_DATA_addr;
};
typedef struct AUDIO_HDMI_OUT_EDID_DATA2 AUDIO_HDMI_OUT_EDID_DATA2;

typedef struct {
    u_int Version;
    u_int HDMI_output_enable;
    u_int EDID_DATA_addr;
    RPCRES_LONG retval;
    HRESULT ret;
} AUDIO_HDMI_OUT_EDID_DATA2_T;

///////////////////////////////


uint64_t htonll(long long val) {
    return (((long long) htonl(val)) << 32) + htonl(val >> 32);
}

int RPC_TOAGENT_CREATE_VIDEO_AGENT(uint32_t* videoId, VIDEO_VF_TYPE pinId)
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    RPC_CREATE_VIDEO_AGENT_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_RPC();
    handle = ion_alloc(rtkfb_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        dbg_warn("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(rtkfb_client, handle, &dat, &len) != 0) {
        dbg_warn("[RTKFB %s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = ion_map_kernel(rtkfb_client, handle);
    rpc->info.type = htonl(pinId);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_VIDEO_KERNEL_RPC_CREATE,
        CONVERT_FOR_AVCPU(dat), //rpc->info address
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->info))),//rpc->retval address
        &rpc->ret)) {
        dbg_warn("[RTKFB %s %d RPC fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }

    if (ntohl(rpc->retval.result) != S_OK || rpc->ret != S_OK) {
        dbg_warn("[RTKFB %x %x %s %d RPC fail]\n", rpc->retval.result, rpc->ret, __FUNCTION__, __LINE__);
        goto exit;
    }

    *videoId = ntohl(rpc->retval.data);

    //TRACE_CODE("[%s %s %d] videoId %u success\n", __FILE__, __FUNCTION__, __LINE__, *videoId);
    ret = 0;

exit:
    if (handle != NULL) {
        ion_unmap_kernel(rtkfb_client, handle);
        ion_free(rtkfb_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_VIDEO_DISPLAY(VIDEO_RPC_VO_FILTER_DISPLAY* argp)
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    VIDEO_RPC_VO_FILTER_DISPLAY_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_RPC();
    handle = ion_alloc(rtkfb_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        dbg_warn("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(rtkfb_client, handle, &dat, &len) != 0) {
        dbg_warn("[RTKFB %s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = ion_map_kernel(rtkfb_client, handle);
    rpc->instanceID = htonl(argp->instanceID);
    rpc->videoPlane = htonl(argp->videoPlane);
    rpc->zeroBuffer = htonl(argp->zeroBuffer);
    rpc->realTimeSrc = htonl(argp->realTimeSrc);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_VIDEO_KERNEL_RPC_DISPLAY,
        CONVERT_FOR_AVCPU(dat), //rpc->info address
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(VIDEO_RPC_VO_FILTER_DISPLAY))),//rpc->retval address
        &rpc->ret)) {
        dbg_warn("[RTKFB %s %d RPC fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }

    if (ntohl(rpc->retval.result) != S_OK || rpc->ret != S_OK) {
        dbg_warn("[RTKFB %x %x %s %d RPC fail]\n", rpc->retval.result, rpc->ret, __FUNCTION__, __LINE__);
        goto exit;
    }

    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(rtkfb_client, handle);
        ion_free(rtkfb_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_VIDEO_CONFIGUREDISPLAYWINDOW(VIDEO_RPC_VOUT_CONFIG_DISP_WIN* argp)
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    VIDEO_RPC_VOUT_CONFIG_DISP_WIN_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_RPC();
    handle = ion_alloc(rtkfb_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        dbg_warn("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(rtkfb_client, handle, &dat, &len) != 0) {
        dbg_warn("[RTKFB %s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = ion_map_kernel(rtkfb_client, handle);

    rpc->videoPlane = htonl(argp->videoPlane);
    rpc->videoWin.x = htons(argp->videoWin.x);
    rpc->videoWin.y = htons(argp->videoWin.y);
    rpc->videoWin.width = htons(argp->videoWin.width);
    rpc->videoWin.height = htons(argp->videoWin.height);
    rpc->borderWin.x = htons(argp->borderWin.x);
    rpc->borderWin.y = htons(argp->borderWin.y);
    rpc->borderWin.width = htons(argp->borderWin.width);
    rpc->borderWin.height = htons(argp->borderWin.height);
    rpc->borderColor.c1 = htonl(argp->borderColor.c1);
    rpc->borderColor.c2 = htonl(argp->borderColor.c2);
    rpc->borderColor.c3 = htonl(argp->borderColor.c3);
    rpc->borderColor.isRGB = htonl(argp->borderColor.isRGB);
    rpc->enBorder = htonl(argp->enBorder);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_VIDEO_KERNEL_RPC_CONFIGUREDISPLAYWINDOW,
        CONVERT_FOR_AVCPU(dat), //rpc->info address
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(VIDEO_RPC_VOUT_CONFIG_DISP_WIN))),//rpc->retval address
        &rpc->ret)) {
        dbg_warn("[RTKFB %s %d RPC fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }

    if (ntohl(rpc->retval.result) != S_OK || rpc->ret != S_OK) {
        dbg_warn("[RTKFB %x %x %s %d RPC fail]\n", rpc->retval.result, rpc->ret, __FUNCTION__, __LINE__);
        goto exit;
    }

    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(rtkfb_client, handle);
        ion_free(rtkfb_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_VIDEO_SETREFCLOCK(VIDEO_RPC_REFCLOCK *pClock)
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    VIDEO_RPC_REFCLOCK_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    handle = ion_alloc(rtkfb_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        dbg_warn("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if(ion_phys(rtkfb_client, handle, &dat, &len) != 0) {
        dbg_warn("[%s malloc fail]\n", __FUNCTION__);
        goto exit;
    }

    rpc = ion_map_kernel(rtkfb_client, handle);
    rpc->instanceID = htonl(pClock->instanceID);
    rpc->pRefClock = htonl(pClock->pRefClock);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_VIDEO_KERNEL_RPC_SETREFCLOCK,
        CONVERT_FOR_AVCPU(dat), //rpc->out address
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->instanceID) + sizeof(rpc->pRefClock))), //rpc->ret
        &rpc->res)) {
        dbg_warn("[%s RPC fail %d]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (rpc->res != S_OK || ntohl(rpc->ret.result) != S_OK) {
        dbg_warn("[%s RPC fail %d]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(rtkfb_client, handle);
        ion_free(rtkfb_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_VIDEO_RUN(uint32_t instance_id)
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    VIDEO_RPC_RUN_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_RPC();
    handle = ion_alloc(rtkfb_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        dbg_warn("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(rtkfb_client, handle, &dat, &len) != 0) {
        dbg_warn("[%s malloc fail]\n", __FUNCTION__);
        goto exit;
    }

    rpc = ion_map_kernel(rtkfb_client, handle);
    rpc->inst_id = htonl(instance_id);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_VIDEO_KERNEL_RPC_RUN,
        CONVERT_FOR_AVCPU(dat), //rpc->inst_id address
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->inst_id))), //rpc->retval address
        &rpc->res)) {
        dbg_warn("[%s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (rpc->res != S_OK || ntohl(rpc->retval.result) != S_OK) {
        dbg_warn("[%s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(rtkfb_client, handle);
        ion_free(rtkfb_client, handle);
    }
    return ret;
}

// data of AUDIO_RPC_RINGBUFFER_HEADER is "hose side"
int RPC_TOAGENT_VIDEO_INITRINGBUFFER(VIDEO_RPC_RINGBUFFER* argp)
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    VIDEO_RPC_RINGBUFFER_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_RPC();
    handle = ion_alloc(rtkfb_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        dbg_warn("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if(ion_phys(rtkfb_client, handle, &dat, &len) != 0) {
        dbg_warn("[%s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = ion_map_kernel(rtkfb_client, handle);
    rpc->instanceID = htonl(argp->instanceID);
    rpc->readPtrIndex = htonl(argp->readPtrIndex);
    rpc->pinID = htonl(argp->pinID);
    rpc->pRINGBUFF_HEADER = htonl(argp->pRINGBUFF_HEADER);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_VIDEO_KERNEL_RPC_INITRINGBUFFER,
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->ret) + sizeof(rpc->res))), //rpc->header address
        CONVERT_FOR_AVCPU(dat), //rpc->ret address
        &rpc->res)) {
        dbg_warn("[%s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (rpc->res != S_OK || ntohl(rpc->ret.result) != S_OK) {
        dbg_warn("[%s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(rtkfb_client, handle);
        ion_free(rtkfb_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_VIDEO_SETRESCALEMODE(VIDEO_RPC_VOUT_SET_RESCALE_MODE* argp)
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    VIDEO_RPC_VOUT_SET_RESCALE_MODE_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_RPC();
    handle = ion_alloc(rtkfb_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        dbg_warn("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(rtkfb_client, handle, &dat, &len) != 0) {
        dbg_warn("[RTKFB %s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = ion_map_kernel(rtkfb_client, handle);
    rpc->videoPlane = htonl(argp->videoPlane);
    rpc->rescaleMode = htonl(argp->rescaleMode);
    rpc->rescaleWindow.x = htonl(argp->rescaleWindow.x);
    rpc->rescaleWindow.y = htonl(argp->rescaleWindow.y);
    rpc->rescaleWindow.width = htonl(argp->rescaleWindow.width);
    rpc->rescaleWindow.height = htonl(argp->rescaleWindow.height);
    rpc->delayExec = htonl(argp->delayExec);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_VIDEO_KERNEL_RPC_SETRESCALEMODE,
        CONVERT_FOR_AVCPU(dat), //rpc->info address
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(VIDEO_RPC_VOUT_SET_RESCALE_MODE))),//rpc->retval address
        &rpc->ret)) {
        dbg_warn("[RTKFB %s %d RPC fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }

    if (ntohl(rpc->retval.result) != S_OK || rpc->ret != S_OK) {
        dbg_warn("[RTKFB %x %x %s %d RPC fail]\n", rpc->retval.result, rpc->ret, __FUNCTION__, __LINE__);
        goto exit;
    }

    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(rtkfb_client, handle);
        ion_free(rtkfb_client, handle);
    }
    return ret;
}

int RPC_ToAgent_AUDIO_HDMI_OUT_EDID_0(struct AUDIO_HDMI_OUT_EDID_DATA2 *argp)
{
    AUDIO_HDMI_OUT_EDID_DATA2_T *rpc = NULL;
    int ret = -1;
    u32 RPC_ret;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    handle = ion_alloc(rtkfb_client, 4096, 1024,
                RTK_PHOENIX_ION_HEAP_AUDIO_MASK,
                ION_FLAG_NONCACHED | ION_FLAG_SCPUACC | ION_FLAG_ACPUACC);

    if (IS_ERR(handle)) {
        dbg_warn("[%s %d ion_alloc fail]", __func__, __LINE__);
        goto exit;
    }

    if (ion_phys(rtkfb_client, handle, &dat, &len) != 0) {
        dbg_warn("[%s %d fail]", __func__, __LINE__);
        goto exit;
    }

    rpc = ion_map_kernel(rtkfb_client, handle);

    rpc->Version = htonl(argp->Version);
    rpc->HDMI_output_enable = htonl(argp->HDMI_output_enable);
    rpc->EDID_DATA_addr = htonl(argp->EDID_DATA_addr);

    /*
    pli_ipcCopyMemory((unsigned char *)rpc, (unsigned char *)arg,
        sizeof(struct AUDIO_HDMI_OUT_EDID_DATA2));
        */

    if (send_rpc_command(RPC_AUDIO, ENUM_KERNEL_RPC_HDMI_OUT_EDID2,
        CONVERT_FOR_AVCPU(dat),
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(AUDIO_HDMI_OUT_EDID_DATA2))),
        &RPC_ret)) {

        dbg_warn("[%s %d RPC fail]", __func__, __LINE__);
        goto exit;
    }

    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(rtkfb_client, handle);
        ion_free(rtkfb_client, handle);
    }
    return ret;
}

void SetAudioHdmiOutEdid2(unsigned char *ion_virt, unsigned long ion_phy)
{
    struct AUDIO_HDMI_OUT_EDID_DATA2 audio_edid_data2;
    //unsigned char edid[HDMI_EDID_SIZE] = { 0x04, 0x09, 0x04, 0x07, 0x00 };

    audio_edid_data2.HDMI_output_enable = HDMI_OUT_EN;
    audio_edid_data2.Version = HDMI_VER;
    //memcpy((void*)ion_virt, edid, HDMI_EDID_SIZE);
    ion_virt[0]=0x04;
    ion_virt[1]=0x09;
    ion_virt[2]=0x04;
    ion_virt[3]=0x07;
    ion_virt[4]=0x00;
    audio_edid_data2.EDID_DATA_addr = (long)(0xffffffff&ion_phy);

    if (RPC_ToAgent_AUDIO_HDMI_OUT_EDID_0(&audio_edid_data2) < 0) {
        dbg_warn("[%s %d fail]\n", __FUNCTION__, __LINE__);
        //return -1;
    };
}

int RTK_FB_RPC_OSD_init(struct rtk_fb *fb)
{
    unsigned char *ion_virt;
    ion_phys_addr_t ion_phy;
    size_t len = 0;
    int dma_fd;
    unsigned int osd_width = 1920, osd_height = 1080;
    VO_RECTANGLE rect;
    REFCLOCK* m_core;
    RINGBUFFER_HEADER *ringheader;
    uint32_t VIDEOAgentID = 0;
    VIDEO_VF_TYPE type;
    DCRT_PARAM_RATE_INFO rateParam;
    unsigned int hz=60;
    VIDEO_RPC_VO_FILTER_DISPLAY info;
    VO_COLOR blueBorder = {0,0,255,1};
    VIDEO_RPC_VOUT_CONFIG_DISP_WIN structConfigDispWin;
    VIDEO_RPC_REFCLOCK rpc_refclock;
    VIDEO_RPC_RINGBUFFER ringbuffer;
    DC_ION_SHARE_MEMORY ion_share_memory;
    DCRT_PARAM_RPC_ADDR inbandParam;

    /* osd init */
    dbg_warn("osd init,[%s %s][%d] \n", __FILE__, __func__, __LINE__);

    /* allocate ion memory for RPC: SetRefClock, InitRingBuffer, SetAudioHdmiOutEdid2 */
    rtkfb_client = ion_client_create(rtk_phoenix_ion_device, "RTKFBDriver");

    rtkfb_handle = ion_alloc(rtkfb_client, 67*1024, 1<<12, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, (ION_FLAG_NONCACHED | ION_FLAG_ACPUACC | ION_FLAG_SCPUACC));
    if (IS_ERR(rtkfb_handle)) {
        dbg_warn("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        return -1;
    }


    if (ion_phys(rtkfb_client, rtkfb_handle, &ion_phy, &len) != 0) {
        dbg_warn("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
        return -1;
    }

    ion_virt = ion_map_kernel(rtkfb_client, rtkfb_handle);

    dma_fd = ion_share_dma_buf_fd(rtkfb_client, rtkfb_handle);

    if (0)
    {
        memset(ion_virt, 0, 67*1024);
    }
    else
    {
        uint64_t *ptr=(uint64_t *)ion_virt;
        uint32_t i;
        for (i=0;i<((67*1024)/sizeof(uint64_t));i++)
        {
            ptr[i]=0;
        }
    }

    /* gldc_osd_main */
    m_core=(REFCLOCK*)((unsigned long)(ion_virt)+(65*1024));
    ringheader=(RINGBUFFER_HEADER*)((unsigned long)(ion_virt)+(64*1024));

    osd_width = fb->fb.var.xres;
    osd_height = fb->fb.var.yres;

    rect.x = 0;
    rect.y = 0;
    rect.width = osd_width;
    rect.height = osd_height;

    /* VIDEO_RPC_ToAgent_Create_0 */
    type = VF_TYPE_VIDEO_OUT;
    if (RPC_TOAGENT_CREATE_VIDEO_AGENT(&VIDEOAgentID, type))
    {
        dbg_warn("[No Video agent %s %d]\n", __FUNCTION__, __LINE__);
        return -1;
    }

    /* DCRT_CMD_SET_OUT_RATE_INFO */
    memset(&rateParam, 0, sizeof(rateParam));
    rateParam.param_size = sizeof(rateParam);
    rateParam.pts_gap =  (unsigned int)90000/hz;
    rateParam.hz = hz*1000;
    rateParam.clockAddrLow = 0x1801B540;
    rateParam.clockAddrHi =  0x1801B544;

    if (DC_Set_RateInfo(&fb->fb, &fb->video_info, &rateParam) != 0){
        dbg_warn("[%s %d]\n", __FUNCTION__, __LINE__);
        return -1;
    }


    /* VIDEO_RPC_VO_FILTER_ToAgent_Display_0 */
    memset(&info, 0, sizeof(info));
    info.instanceID = VIDEOAgentID;
    info.videoPlane = VO_VIDEO_PLANE_OSD1;
    info.zeroBuffer  = 0;
    info.realTimeSrc = 0;
    if (RPC_TOAGENT_VIDEO_DISPLAY(&info))
    {
        dbg_warn("[%s %d]\n", __FUNCTION__, __LINE__);
        return -1;
    }

    /* VIDEO_RPC_VOUT_ToAgent_ConfigureDisplayWindow_0 */
    memset(&structConfigDispWin, 0, sizeof(structConfigDispWin));
    structConfigDispWin.videoPlane = VO_VIDEO_PLANE_OSD1;
    structConfigDispWin.videoWin = rect;
    structConfigDispWin.borderWin = rect;
    structConfigDispWin.borderColor = blueBorder;
    structConfigDispWin.enBorder = 0;
    if (RPC_TOAGENT_VIDEO_CONFIGUREDISPLAYWINDOW(&structConfigDispWin))
    {
        dbg_warn("[%s %d]\n", __FUNCTION__, __LINE__);
        return -1;
    }

    /* VIDEO_RPC_ToAgent_SetRefClock_0 */
    m_core->RCD = htonll(-1LL);
    m_core->RCD_ext = htonl(-1L);
    m_core->masterGPTS = htonll(-1LL);
    m_core->GPTSTimeout = htonll(0LL);
    m_core->videoSystemPTS = htonll(-1LL);
    m_core->audioSystemPTS = htonll(-1LL);
    m_core->videoRPTS = htonll(-1LL);
    m_core->audioRPTS = htonll(-1LL);
    m_core->videoContext = htonl(-1);
    m_core->audioContext = htonl(-1);
    m_core->videoEndOfSegment = htonl(-1);
    m_core->videoFreeRunThreshold = htonl(0x7FFFFFFF);
    m_core->audioFreeRunThreshold = htonl(0x7FFFFFFF);
    m_core->VO_Underflow = htonl(0);
    m_core->AO_Underflow = htonl(0);
    m_core->mastership.systemMode  = (unsigned char)AVSYNC_FORCED_SLAVE;
    m_core->mastership.videoMode   = (unsigned char)AVSYNC_FORCED_MASTER;
    m_core->mastership.audioMode   = (unsigned char)AVSYNC_FORCED_MASTER;
    m_core->mastership.masterState = (unsigned char)AUTOMASTER_NOT_MASTER;
    memset(&rpc_refclock, 0, sizeof(rpc_refclock));
    rpc_refclock.instanceID = VIDEOAgentID;
    rpc_refclock.pRefClock = (long)(0xffffffff&ion_phy)+65*1024;
    if (RPC_TOAGENT_VIDEO_SETREFCLOCK(&rpc_refclock)) {
        dbg_warn("[%s %d]\n", __FUNCTION__, __LINE__);
        return -1;
    }

    /* VIDEO_RPC_ToAgent_Run_0 */
    if (RPC_TOAGENT_VIDEO_RUN(VIDEOAgentID)){
            dbg_warn("[%s %d]\n", __FUNCTION__, __LINE__);
         return -1;
    }

    /*  VIDEO_RPC_ToAgent_InitRingBuffer_0 */
    ringheader->beginAddr=htonl((long)(0xffffffff&ion_phy));
    ringheader->size=htonl(64*1024);
    ringheader->writePtr=ringheader->beginAddr;
    ringheader->readPtr[0]=ringheader->beginAddr;
    ringheader->bufferID=htonl(1);
    memset(&ringbuffer, 0, sizeof(ringbuffer));
    ringbuffer.instanceID = VIDEOAgentID;
    ringbuffer.readPtrIndex = 0;
    ringbuffer.pinID = 0;
    ringbuffer.pRINGBUFF_HEADER=(long)(0xffffffff&ion_phy)+64*1024;
    if (RPC_TOAGENT_VIDEO_INITRINGBUFFER(&ringbuffer) < 0) {
        dbg_warn("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -1;
    };

    /* DC2VO_SET_ION_SHARE_MEMORY */
    memset(&ion_share_memory, 0, sizeof(ion_share_memory));
    ion_share_memory.sfd_refclk=dma_fd;
    ion_share_memory.sfd_rbHeader=0;
    ion_share_memory.sfd_rbBase=0;

    if (DC_Set_ION_Share_Memory(&fb->fb, &fb->video_info, &ion_share_memory)!= 0){
        dbg_warn("!!ERROR!! [ %s %d ] \n", __FUNCTION__, __LINE__);
        return -1;
    }

    /* DCRT_CMD_SET_RING_INFO DC2VO_SET_RING_INFO */
    memset(&inbandParam, 0, sizeof(inbandParam));
    inbandParam.ringPhyAddr=ringbuffer.pRINGBUFF_HEADER;
    inbandParam.refclockAddr=rpc_refclock.pRefClock;

    if (DC_Set_RPCAddr(&fb->fb, &fb->video_info, &inbandParam)!= 0){
        dbg_warn("SET_RING_INFO fail \n");
        return -1;
    }

    /* VIDEO_RPC_VO_FILTER_ToAgent_Display_0 */
    memset(&info, 0, sizeof(info));
    info.instanceID = VIDEOAgentID;
    info.videoPlane = VO_VIDEO_PLANE_OSD1;
    info.zeroBuffer  = 1;
    info.realTimeSrc = 0;
    if (RPC_TOAGENT_VIDEO_DISPLAY(&info))
    {
        dbg_warn("[%s %d]\n", __FUNCTION__, __LINE__);
        return -1;
    }

    SetAudioHdmiOutEdid2((unsigned char*)((unsigned long)ion_virt+66*1024), ion_phy+66*1024);

    if (rtkfb_handle != NULL) {
        ion_unmap_kernel(rtkfb_client, rtkfb_handle);
        ion_free(rtkfb_client, rtkfb_handle);
        ion_client_destroy(rtkfb_client);
    }

    return 0;
}