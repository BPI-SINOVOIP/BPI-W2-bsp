/**
 * snd-realtek_RPC.c - Realtek alsa driver
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
//#include <linux/pageremap.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include <linux/dma-mapping.h>
#include <sound/asound.h>
#include <asm/cacheflush.h>
#include "snd-realtek.h"
#include <rtk_rpc.h>
#include <soc/realtek/kernel-rpc.h>

#ifdef USE_ION_AUDIO_HEAP

#ifdef CONFIG_64BIT
#define PRIVATE_INFO_MASK 0xFFFFFFFFFFFFFFFC
#else
#define PRIVATE_INFO_MASK 0xFFFFFFFC
#endif

extern struct ion_client *alsa_client;

int RPC_TOAGENT_CHECK_AUDIO_READY() 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    RPC_DEFAULT_INPUT_T *rpc = NULL;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_RPC();
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);

#ifdef AO_ON_SCPU
    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_CHECK_READY
        , (unsigned char *)rpc, sizeof(rpc->info)
        , (unsigned char *)rpc + sizeof(rpc->info), sizeof(RPCRES_LONG )
        , (unsigned char *)&rpc->ret, sizeof(unsigned int));
#else
    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_CHECK_READY,
        CONVERT_FOR_AVCPU(dat), //rpc->info address
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->info))), //rpc->retval address
        &rpc->ret)) {
        ALSA_WARNING("[ALSA %s RPC fail]\n", __FUNCTION__);
        goto exit;
    }

    if (rpc->ret != S_OK ) {
        ALSA_WARNING("[ALSA %s RPC fail]\n", __FUNCTION__);
        goto exit;
    }

    if (rpc->info == 0) {
        ALSA_WARNING("[ALSA Audio is not ready]\n");
        goto exit;
    }
#endif
    //TRACE_CODE("[%s %s %d ] success\n", __FILE__, __FUNCTION__, __LINE__);
    // successful
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_SEND_AUDIO_VERSION(OMX_AUDIO_VERSION version)
{
    AUDIO_RPC_PRIVATEINFO_PARAMETERS *cmd;
    AUDIO_RPC_PRIVATEINFO_RETURNVAL *res;
    HRESULT RPC_ret;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;
    unsigned long offset;

    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
       goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }

    cmd = ion_map_kernel(alsa_client, handle);
    offset = get_rpc_alignment_offset(sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned long)cmd + offset);

    memset(cmd, 0, sizeof(*cmd));
    cmd->type = htonl(ENUM_PRIVATEINFO_OMX_AUDIO_VERSION);
    cmd->privateInfo[0] = htonl(version);

#ifndef AO_ON_SCPU
    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_PRIVATEINFO,
        CONVERT_FOR_AVCPU(dat), //cmd address
        CONVERT_FOR_AVCPU(dat + offset), //res address
        &RPC_ret)) {
            ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
            goto exit;
        }

    if (RPC_ret != S_OK) {
            ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
            goto exit;
        }
#endif
    ret = 0;

exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_CREATE_PP_AGENT(int* ppId, int* pinId)
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    RPC_CREATE_AO_AGENT_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);
    rpc->info.instanceID = htonl(0);
    rpc->info.type = htonl(AUDIO_PP_OUT);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_CREATE_AGENT,
        CONVERT_FOR_AVCPU(dat), //rpc->info address
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->info))),//rpc->retval address
        &rpc->ret)) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }

    if (ntohl(rpc->retval.result) != S_OK || rpc->ret != S_OK) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }

    *ppId = ntohl(rpc->retval.data);
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = RPC_TOAGENT_GET_GLOBAL_PP_PIN(pinId);

exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_CREATE_AO_AGENT(int* aoId, int pinId)
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    RPC_CREATE_AO_AGENT_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_RPC();
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);
    rpc->info.instanceID = htonl(0);
    rpc->info.type = htonl(pinId);

#ifdef AO_ON_SCPU    
    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_CREATE_AGENT
        , (unsigned char *)rpc, sizeof(rpc->info)
        , (unsigned char *)rpc + sizeof(rpc->info), sizeof(rpc->retval)
        , (unsigned char *)&rpc->ret, sizeof(unsigned int));

    if(ntohl(rpc->retval.result) != S_OK || rpc->ret != S_OK) {
        ALSA_WARNING("[ALSA %x %x %s %d RPC fail]\n", rpc->retval.result, rpc->ret, __FUNCTION__, __LINE__);
        goto exit;
    }
#else    
    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_CREATE_AGENT,
        CONVERT_FOR_AVCPU(dat), //rpc->info address
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->info))),//rpc->retval address
        &rpc->ret)) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }

    if (ntohl(rpc->retval.result) != S_OK || rpc->ret != S_OK) {
        ALSA_WARNING("[ALSA %x %x %s %d RPC fail]\n", rpc->retval.result, rpc->ret, __FUNCTION__, __LINE__);
        goto exit;
    }
#endif

    *aoId = ntohl(rpc->retval.data);
    //TRACE_CODE("[%s %s %d] aoid %d success\n", __FILE__, __FUNCTION__, __LINE__, *aoId);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_PUT_SHARE_MEMORY_LATENCY(void *p, void *p2, int decID, int type)
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    AUDIO_RPC_PRIVATEINFO_PARAMETERS *cmd;
    AUDIO_RPC_PRIVATEINFO_RETURNVAL *res;
    int ret = 0;
    int magic_num = 2379;
    HRESULT RPC_ret;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;
    unsigned long offset;

    TRACE_RPC();
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }

    cmd = ion_map_kernel(alsa_client, handle);
    //res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)(((unsigned long)cmd + sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS) + 8) & PRIVATE_INFO_MASK);
    offset = get_rpc_alignment_offset(sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned long)cmd + offset);
    //offset = (unsigned long)res - (unsigned long)cmd;
    printk("[%s %d ion_alloc p1 %x p2 %x decID %d type %d\n", __FUNCTION__, __LINE__, (uint32_t)((long)p), (uint32_t)((long)p2), decID, type);
    memset(cmd, 0, sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    cmd->type = htonl(type);
    cmd->privateInfo[0] = (uint32_t)htonl((uint32_t)((long)p));
    cmd->privateInfo[1] = htonl(magic_num);
    cmd->privateInfo[2] = (uint32_t)htonl((uint32_t)((long)p2));
    cmd->privateInfo[3] = (uint32_t)htonl((uint32_t)(decID));
#ifdef AO_ON_SCPU
    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_PRIVATEINFO
        , (unsigned char *)cmd, sizeof(*cmd)
        , (unsigned char *)cmd + offset, sizeof(AUDIO_RPC_PRIVATEINFO_RETURNVAL)
        , (unsigned char *)&RPC_ret, sizeof(unsigned int));
#else
    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_PRIVATEINFO,
        CONVERT_FOR_AVCPU(dat),
        CONVERT_FOR_AVCPU(dat + offset),
        &RPC_ret)) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (RPC_ret != S_OK ) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
#endif
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_PUT_SHARE_MEMORY(void *p, int type)
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    AUDIO_RPC_PRIVATEINFO_PARAMETERS *cmd;  
    AUDIO_RPC_PRIVATEINFO_RETURNVAL *res;
    int ret = 0;
    HRESULT RPC_ret;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;
    unsigned long offset;

    TRACE_RPC();
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }

    cmd = ion_map_kernel(alsa_client, handle);
    //res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)(((unsigned long)cmd + sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS) + 8) & PRIVATE_INFO_MASK);
    offset = get_rpc_alignment_offset(sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned long)cmd + offset);
    //offset = (unsigned long)res - (unsigned long)cmd;

    memset(cmd, 0, sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    cmd->type = htonl(type);
    cmd->privateInfo[0] = (uint32_t)htonl((uint32_t)((long)p));
#ifdef AO_ON_SCPU
    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_PRIVATEINFO
        , (unsigned char *)cmd, sizeof(*cmd)
        , (unsigned char *)cmd + offset, sizeof(AUDIO_RPC_PRIVATEINFO_RETURNVAL)
        , (unsigned char *)&RPC_ret, sizeof(unsigned int));
#else
    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_PRIVATEINFO,
        CONVERT_FOR_AVCPU(dat),
        CONVERT_FOR_AVCPU(dat + offset),
        &RPC_ret)) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (RPC_ret != S_OK ) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
#endif
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_GET_AO_FLASH_PIN(snd_card_RTK_pcm_t *dpcm) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    
    AUDIO_RPC_PRIVATEINFO_PARAMETERS *cmd;  
    AUDIO_RPC_PRIVATEINFO_RETURNVAL *res;
    HRESULT RPC_ret;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;
    unsigned long offset;

    TRACE_RPC();
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }

    cmd = ion_map_kernel(alsa_client, handle);
    //res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)(((unsigned long)cmd + sizeof(*cmd) + 8) & PRIVATE_INFO_MASK);
    offset = get_rpc_alignment_offset(sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned long)cmd + offset);
    //offset = (unsigned long)res - (unsigned long)cmd;
    memset(cmd, 0, sizeof(*cmd));
    memset(res, 0, sizeof(*res));
    cmd->instanceID = htonl(dpcm->AOAgentID);   
    cmd->type = htonl(ENUM_PRIVATEINFO_AUDIO_GET_FLASH_PIN);
    cmd->privateInfo[0] = 0xFF; 
    cmd->privateInfo[1] = 0xFF;
    cmd->privateInfo[2] = 0xFF; 
    cmd->privateInfo[3] = 0xFF;     
    cmd->privateInfo[4] = 0xFF;     
    cmd->privateInfo[5] = 0xFF; 
#ifdef AO_ON_SCPU
    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_PRIVATEINFO
        , (unsigned char *)cmd, sizeof(*cmd)
        , (unsigned char *)res, sizeof(AUDIO_RPC_PRIVATEINFO_RETURNVAL)
        , (unsigned char *)&RPC_ret, sizeof(unsigned int));
#else
    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_PRIVATEINFO,
        CONVERT_FOR_AVCPU(dat), //cmd address
        CONVERT_FOR_AVCPU(dat + offset),//res address
        &RPC_ret)) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (RPC_ret != S_OK ) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit; 
    }
#endif
    
    ret = ntohl(res->privateInfo[0]);
    
    if (ret < FLASH_AUDIO_PIN_1 || ret > FLASH_AUDIO_PIN_3) {
        ALSA_WARNING("[ALSA %s %d RPC %d fail]\n", __FUNCTION__, __LINE__, ret);
        ret = -1;
    }
    //ALSA_WARNING("GET_AO_FLASH_PIN ret %d\n", ret);
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_GET_GLOBAL_PP_PIN(int* pinId)
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    AUDIO_RPC_PRIVATEINFO_PARAMETERS *cmd;
    AUDIO_RPC_PRIVATEINFO_RETURNVAL *res;
    HRESULT RPC_ret;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;
    unsigned long offset;

    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }

    cmd = ion_map_kernel(alsa_client, handle);
    //res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned long)(cmd + sizeof(*cmd)+8) & PRIVATE_INFO_MASK);
    offset = get_rpc_alignment_offset(sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned long)cmd + offset);
    //offset = (unsigned long)res - (unsigned long)cmd;

    memset(cmd, 0, sizeof(*cmd));
    cmd->type = htonl(ENUM_PRIVATEINFO_AUDIO_GET_PP_FREE_PINID);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_PRIVATEINFO,
        CONVERT_FOR_AVCPU(dat), //cmd address
        CONVERT_FOR_AVCPU(dat + offset), //res address
        &RPC_ret)) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (RPC_ret != S_OK ) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (res != NULL && res->privateInfo[0] == 0x44495050) {
        //int first = res->privateInfo[1];
        //TRACE_CODE("##### get PP Pin = %ld first %d\n", ntohl(res->privateInfo[2]), ntohl(first));
        *pinId = ntohl(res->privateInfo[2]);
        ret = 0;
    } else {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        ret = -1;
    }
    //ALSA_WARNING("GET_GLOBAL_PIN ret %d\n", ret);
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_SET_AO_FLASH_VOLUME(snd_pcm_substream_t * substream) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    snd_pcm_runtime_t *runtime = substream->runtime;
    snd_card_RTK_pcm_t *dpcm = runtime->private_data;
    HRESULT rpc_ret;
    AUDIO_RPC_PRIVATEINFO_PARAMETERS *cmd;
    AUDIO_RPC_PRIVATEINFO_RETURNVAL *res;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;
    unsigned long offset;

    TRACE_RPC();
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }

    //cmd = (AUDIO_RPC_PRIVATEINFO_PARAMETERS *) ((unsigned int)page_address(page));
    //res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *) ((((unsigned int) page_address(page) + sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS)+8) & 0xFFFFFFFC));
    cmd = ion_map_kernel(alsa_client, handle);
    //res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)(((unsigned long)cmd + sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS) + 8) & PRIVATE_INFO_MASK);
    offset = get_rpc_alignment_offset(sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned long)cmd + offset);
    //offset = (unsigned long)res - (unsigned long)cmd;

    memset(cmd, 0, sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    cmd->instanceID = htonl(dpcm->AOAgentID);
    cmd->type = htonl(ENUM_PRIVATEINFO_AUDIO_CONTROL_FLASH_VOLUME);
    cmd->privateInfo[0] = htonl(dpcm->AOpinID);
    cmd->privateInfo[1] = htonl((31-dpcm->volume));

#ifdef AO_ON_SCPU
    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_PRIVATEINFO
        , (unsigned char *)cmd, sizeof(*cmd)
        , (unsigned char *)res, sizeof(AUDIO_RPC_PRIVATEINFO_RETURNVAL)
        , &rpc_ret, sizeof(rpc_ret));
#else
    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_PRIVATEINFO,
        CONVERT_FOR_AVCPU(dat),
        CONVERT_FOR_AVCPU(dat + offset),
        &rpc_ret)) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (rpc_ret != S_OK) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
#endif
    ALSA_VitalPrint("[ALSA set AO_pin %d volume %d]\n", dpcm->AOpinID, dpcm->volume);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_CREATE_DECODER_AGENT(int* decID, int* pinID)
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    RPC_CREATE_PCM_DECODER_CTRL_T* rpc = NULL;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_RPC();
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);
    rpc->instance.type = htonl(AUDIO_DECODER);
    rpc->instance.instanceID = htonl(-1);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_CREATE_AGENT,
        CONVERT_FOR_AVCPU(dat), //rpc->instance address
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->instance))), //rpc->res address
        &rpc->ret)) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (rpc->ret != S_OK) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    *decID = ntohl(rpc->res.data);
    *pinID = BASE_BS_IN;

    //printk("[ALSA Create Decoder instance %d]\n", *decID/*dpcm->DECAgentID*/);
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

// data of AUDIO_RPC_RINGBUFFER_HEADER is "hose side"
int RPC_TOAGENT_INITRINGBUFFER_HEADER_SVC(AUDIO_RPC_RINGBUFFER_HEADER *header, int buffer_count) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    RPC_INITRINGBUFFER_HEADER_T *rpc;
    int ch;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_RPC();
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if(ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);
    rpc->header.instanceID = htonl(header->instanceID);
    rpc->header.pinID = htonl(header->pinID);
    rpc->header.readIdx = htonl(header->readIdx); 
    rpc->header.listSize = htonl(header->listSize);

    //printk(" header instance ID %d\n", header->instanceID);
    //printk(" header pinID       %d\n", header->pinID);
    //printk(" header readIdx     %d\n", header->readIdx);
    //printk(" header listSize    %d\n", header->listSize);

    for ( ch = 0; ch < buffer_count; ch++) {
        //rpc_initringbuffer->header.pRingBufferHeaderList[i] = htonl(0xa0000000|(((unsigned int) header->pRingBufferHeaderList[i])&0x1FFFFFFF));
        //printk("[test]header.pRingBufferHeaderList[%d] = %lx\n", ch, header->pRingBufferHeaderList[ch]); 
        rpc->header.pRingBufferHeaderList[ch] = htonl((unsigned int) header->pRingBufferHeaderList[ch]);
        //rpc->header.pRingBufferHeaderList[ch] = htonl(0xa0000000|(((unsigned int) header->pRingBufferHeaderList[ch])&0x1FFFFFFF));
    }

    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_INIT_RINGBUF,
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->ret) + sizeof(rpc->res))), //rpc->header address
        CONVERT_FOR_AVCPU(dat), //rpc->ret address
        &rpc->res)) {
        ALSA_WARNING("[%s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (rpc->res != S_OK || ntohl(rpc->ret.result) != S_OK) {
        ALSA_WARNING("[%s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit; 
    }
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

#ifdef AO_ON_SCPU
int KRPC_TOAGENT_INITRINGBUFFER_HEADER_SVC(AUDIO_RPC_RINGBUFFER_HEADER *header, int buffer_count) 
{
    TRACE_RPC();
    RPCRES_LONG ret;
    HRESULT res;
    int i;

    header->instanceID = htonl(header->instanceID);
    header->listSize = htonl(header->listSize);
    header->pinID = htonl(header->pinID);
    header->readIdx = htonl(header->readIdx);
    for(i=0 ; i<8 ; ++i)
        header->pRingBufferHeaderList[i] = htonl(header->pRingBufferHeaderList[i]);

    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_INIT_RINGBUF_AO
        , (unsigned char *)header, sizeof(*header)
        , (unsigned char *)&ret, sizeof(ret)
        , (unsigned char *)&res, sizeof(res));

    return 0;
}

void RPC_TOAGENT_AO_INIT_FLASH(snd_pcm_substream_t *substream)
{
    TRACE_RPC();
    snd_pcm_runtime_t *runtime = substream->runtime;
    snd_card_RTK_pcm_t *dpcm = runtime->private_data;
    AUDIO_RPC_PRIVATEINFO_PARAMETERS *cmd;  
    AUDIO_RPC_PRIVATEINFO_RETURNVAL *res;
    struct ion_handle *handle = NULL;
    unsigned int offset;
    HRESULT rpc_ret = 0;
    ion_phys_addr_t dat;
    size_t len;

    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);
    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
    if(ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }
    cmd = ion_map_kernel(alsa_client, handle);
    res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned int)((unsigned int)cmd + sizeof(*cmd)+8) & PRIVATE_INFO_MASK);
    offset = (unsigned int)res - (unsigned int)cmd;
    
    memset(cmd, 0, sizeof(*cmd));
    cmd->instanceID = htonl(dpcm->AOAgentID) ;
    cmd->type = htonl(ENUM_PRIVATEINFO_AUDIO_CONFIG_CMD_BS_INFO);
    cmd->privateInfo[0] = htonl(runtime->channels);
    cmd->privateInfo[1] = htonl(ENUM_AO_FLASH_32BIT_BE);
#if 1
    cmd->privateInfo[2] = htonl(48000);
    ALSA_WARNING("ALSA hack sr 48k\n");
#else
    cmd->privateInfo[2] = htonl(runtime->rate);
#endif
    cmd->privateInfo[4] = htonl(dpcm->AOpinID);
    cmd->privateInfo[5] = htonl(ENUM_AUDIO_LEFT_FRONT_INDEX);
    cmd->privateInfo[6] = htonl(ENUM_AUDIO_RIGHT_FRONT_INDEX);

    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_PRIVATEINFO
        , (unsigned char *)cmd, sizeof(*cmd)
        , (unsigned char *)res, sizeof(*res)
        , (unsigned char *)&rpc_ret, sizeof(rpc_ret));

exit:
    if(handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
}

#endif

int RPC_TOAGENT_CONNECT_SVC(AUDIO_RPC_CONNECTION *pconnection) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    RPC_CONNECTION_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_RPC();
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[%s malloc fail]\n", __FUNCTION__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);
    rpc->out.srcInstanceID = htonl(pconnection->srcInstanceID);
    rpc->out.srcPinID = htonl(pconnection->srcPinID);
    rpc->out.desInstanceID = htonl(pconnection->desInstanceID);
    rpc->out.desPinID= htonl(pconnection->desPinID);

#ifdef AO_ON_SCPU
    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_CONNECT
        , (unsigned char *)rpc, sizeof(rpc->out)
        , (unsigned char *)rpc + sizeof(rpc->out), sizeof(rpc->ret)
        , (unsigned char *)&rpc->res, sizeof(rpc->res));
#else
    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_CONNECT,
        CONVERT_FOR_AVCPU(dat), //rpc->out address
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->out))), //rpc->ret
        &rpc->res)) {
        ALSA_WARNING("[%s RPC fail %d]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (rpc->res != S_OK || ntohl(rpc->ret.result) != S_OK) {
        ALSA_WARNING("[%s RPC fail %d]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
#endif
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_SWITCH_FOCUS(AUDIO_RPC_FOCUS *focus)
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    AUDIO_RPC_FOCUS_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[%s malloc fail]\n", __FUNCTION__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);
    rpc->instanceID = htonl(focus->instanceID);
    rpc->focusID = htonl(focus->focusID);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_SWITCH_FOCUS,
        CONVERT_FOR_AVCPU(dat), //rpc->out address
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->instanceID) + sizeof(rpc->focusID))), //rpc->ret
        &rpc->res)) {
        ALSA_WARNING("[%s RPC fail %d]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (rpc->res != S_OK || ntohl(rpc->ret.result) != S_OK) {
        ALSA_WARNING("[%s RPC fail %d]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_DAC_I2S_CONFIG(AUDIO_CONFIG_DAC_I2S *config)
{
    AUDIO_CONFIG_DAC_I2S_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;
    HRESULT *result;
    unsigned long offset;

    TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);
    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[%s malloc fail]\n", __FUNCTION__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);
    offset = get_rpc_alignment_offset(sizeof(AUDIO_CONFIG_DAC_I2S_T));
    result = (HRESULT *)((unsigned long)rpc + offset);
    rpc->instanceID = htonl(config->instanceID);
    rpc->dacConfig.audioGeneralConfig.interface_en = htonl(config->dacConfig.audioGeneralConfig.interface_en);
    rpc->dacConfig.audioGeneralConfig.channel_out = htonl(config->dacConfig.audioGeneralConfig.channel_out);
    rpc->dacConfig.audioGeneralConfig.count_down_play_en = htonl(config->dacConfig.audioGeneralConfig.count_down_play_en);
    rpc->dacConfig.audioGeneralConfig.count_down_play_cyc = htonl(config->dacConfig.audioGeneralConfig.count_down_play_cyc);
    rpc->dacConfig.sampleInfo.sampling_rate = htonl(config->dacConfig.sampleInfo.sampling_rate);
    rpc->dacConfig.sampleInfo.PCM_bitnum = htonl(config->dacConfig.sampleInfo.PCM_bitnum);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_DAC_I2S_CONFIG,
        CONVERT_FOR_AVCPU(dat), //rpc->out address
        CONVERT_FOR_AVCPU(dat + offset), //rpc->ret
        &rpc->res)) {
        ALSA_WARNING("[%s RPC fail %d]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ntohl(*result) != S_OK) {
        ALSA_WARNING("[%s RPC fail %d]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_DAC_SPDIF_CONFIG(AUDIO_CONFIG_DAC_SPDIF *config)
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    AUDIO_CONFIG_DAC_SPDIF_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;
    HRESULT *result;
    unsigned long offset;

    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[%s malloc fail]\n", __FUNCTION__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);
    offset = get_rpc_alignment_offset(sizeof(AUDIO_CONFIG_DAC_SPDIF_T));
    result = (HRESULT *)((unsigned long)rpc + offset);
    rpc->instanceID = htonl(config->instanceID);
    rpc->spdifConfig.audioGeneralConfig.interface_en = htonl(config->spdifConfig.audioGeneralConfig.interface_en);
    rpc->spdifConfig.audioGeneralConfig.channel_out = htonl(config->spdifConfig.audioGeneralConfig.channel_out);
    rpc->spdifConfig.audioGeneralConfig.count_down_play_en = htonl(config->spdifConfig.audioGeneralConfig.count_down_play_en);
    rpc->spdifConfig.audioGeneralConfig.count_down_play_cyc = htonl(config->spdifConfig.audioGeneralConfig.count_down_play_cyc);
    rpc->spdifConfig.sampleInfo.sampling_rate = htonl(config->spdifConfig.sampleInfo.sampling_rate);
    rpc->spdifConfig.sampleInfo.PCM_bitnum = htonl(config->spdifConfig.sampleInfo.PCM_bitnum);
    rpc->spdifConfig.out_cs_info.non_pcm_valid = htonl(config->spdifConfig.out_cs_info.non_pcm_valid);
    rpc->spdifConfig.out_cs_info.non_pcm_format = htonl(config->spdifConfig.out_cs_info.non_pcm_format);
    rpc->spdifConfig.out_cs_info.audio_format = htonl(config->spdifConfig.out_cs_info.audio_format);
    rpc->spdifConfig.out_cs_info.spdif_consumer_use = htonl(config->spdifConfig.out_cs_info.spdif_consumer_use);
    rpc->spdifConfig.out_cs_info.copy_right = htonl(config->spdifConfig.out_cs_info.copy_right);
    rpc->spdifConfig.out_cs_info.pre_emphasis = htonl(config->spdifConfig.out_cs_info.pre_emphasis);
    rpc->spdifConfig.out_cs_info.stereo_channel = htonl(config->spdifConfig.out_cs_info.stereo_channel);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_DAC_SPDIF_CONFIG,
        CONVERT_FOR_AVCPU(dat), //rpc->out address
        CONVERT_FOR_AVCPU(dat + offset), //rpc->ret
        &rpc->res)) {
        ALSA_WARNING("[%s RPC fail %d]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ntohl(*result) != S_OK) {
        ALSA_WARNING("[%s RPC fail %d]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_SETREFCLOCK(AUDIO_RPC_REFCLOCK *pClock)
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    AUDIO_RPC_REFCLOCK_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if(ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[%s malloc fail]\n", __FUNCTION__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);
    rpc->instanceID = htonl(pClock->instanceID);
    rpc->pRefClockID = htonl(pClock->pRefClockID);
    rpc->pRefClock = htonl(pClock->pRefClock);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_SETREFCLOCK,
        CONVERT_FOR_AVCPU(dat), //rpc->out address
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->instanceID) + sizeof(rpc->pRefClockID) + sizeof(rpc->pRefClock))), //rpc->ret
        &rpc->res)) {
        ALSA_WARNING("[%s RPC fail %d]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (rpc->res != S_OK || ntohl(rpc->ret.result) != S_OK) {
        ALSA_WARNING("[%s RPC fail %d]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_PAUSE_SVC(int instance_id) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    RPC_TOAGENT_PAUSE_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_RPC();
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);
    rpc->inst_id = htonl(instance_id);

#ifdef AO_ON_SCPU
    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_PAUSE
        , (unsigned char *)rpc, sizeof(rpc->inst_id)
        , (unsigned char *)rpc + sizeof(rpc->inst_id), sizeof(rpc->retval)
        , (unsigned char *)&rpc->res, sizeof(rpc->res));
#else
    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_PAUSE,
        CONVERT_FOR_AVCPU(dat), //rpc->inst_id address
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->inst_id))),//rpc->retval address
        &rpc->res)) {
        ALSA_WARNING("[%s %d RPC fail\n]", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (rpc->res != S_OK) {
        ALSA_WARNING("[%s %d RPC fail\n]", __FUNCTION__, __LINE__);
        goto exit;
    }
#endif
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_DESTROY_AI_FLOW_SVC(int instance_id) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    AUDIO_RPC_AIO_PRIVATEINFO_PARAMETERS *rpc = NULL;
    int ret = -1;
    struct ion_handle *handle = NULL;
    HRESULT res;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_RPC();
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);
    rpc->type = htonl(ENUM_PRIVATEINFO_AIO_ALSA_DESTROY_AI_FLOW);
    rpc->instanceID = htonl(instance_id);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_AIO_PRIVATEINFO,
        CONVERT_FOR_AVCPU(dat), //rpc->inst_id address
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(*rpc))),//rpc->retval address
        &res)) {
        ALSA_WARNING("[%s %d RPC fail\n]", __FUNCTION__, __LINE__);
        goto exit;
    }
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_RUN_SVC(int instance_id) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    RPC_TOAGENT_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_RPC();
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[%s malloc fail]\n", __FUNCTION__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);
    rpc->inst_id = htonl(instance_id);

#ifdef AO_ON_SCPU
    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_RUN
        , (unsigned char *)rpc, sizeof(rpc->inst_id)
        , (unsigned char *)rpc + sizeof(rpc->inst_id), sizeof(rpc->retval)
        , (unsigned char *)&rpc->res, sizeof(rpc->res));
#else
    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_RUN,
        CONVERT_FOR_AVCPU(dat), //rpc->inst_id address
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->inst_id))), //rpc->retval address
        &rpc->res)) {
        ALSA_WARNING("[%s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (rpc->res != S_OK || ntohl(rpc->retval.result) != S_OK) {
        ALSA_WARNING("[%s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
#endif
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}  

int RPC_TOAGENT_FLUSH_SVC(AUDIO_RPC_SENDIO  *sendio) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    RPC_TOAGENT_FLASH_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_RPC();
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA %s malloc fail]\n", __FUNCTION__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);
    rpc->sendio.instanceID = htonl(sendio->instanceID);
    rpc->sendio.pinID = htonl(sendio->pinID);

#ifdef AO_ON_SCPU
    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_FLUSH
        , (unsigned char *)rpc + sizeof(rpc->retval) + sizeof(rpc->res), sizeof(rpc->sendio)
        , (unsigned char *)rpc, sizeof(rpc->retval)
        , (unsigned char *)&rpc->res, sizeof(rpc->res));
#else
    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_FLUSH,
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->retval) + sizeof(rpc->res))), //rpc->sendio address
        CONVERT_FOR_AVCPU(dat), //rpc->retval address
        &rpc->res)) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (rpc->res != S_OK || ntohl(rpc->retval.result) != S_OK) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
#endif
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_RELEASE_AO_FLASH_PIN(snd_card_RTK_pcm_t *dpcm) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    HRESULT rpc_ret = 0;
    int ret = -1;
    AUDIO_RPC_PRIVATEINFO_PARAMETERS *cmd;
    AUDIO_RPC_PRIVATEINFO_RETURNVAL *res;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;
    unsigned long offset;

    TRACE_RPC();
    if (dpcm->AOpinID < FLASH_AUDIO_PIN_1 || dpcm->AOpinID > FLASH_AUDIO_PIN_3) {
       ALSA_WARNING("[%d @ %s %d]\n", dpcm->AOpinID, __FUNCTION__, __LINE__);
       goto exit;
    }

    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }

    cmd = ion_map_kernel(alsa_client, handle);
    //res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)(((unsigned long)cmd + sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS) + 8) & PRIVATE_INFO_MASK);
    offset = get_rpc_alignment_offset(sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned long)cmd + offset);
    //offset = (unsigned long)res - (unsigned long)cmd;

    memset(cmd, 0, sizeof(*cmd));
    cmd->instanceID = htonl(dpcm->AOAgentID);
    cmd->type = htonl(ENUM_PRIVATEINFO_AUDIO_RELEASE_FLASH_PIN);
    cmd->privateInfo[0] = htonl(dpcm->AOpinID);
    cmd->privateInfo[1] = 0xFF;
    cmd->privateInfo[2] = 0xFF;
    cmd->privateInfo[3] = 0xFF;
    cmd->privateInfo[4] = 0xFF;
    cmd->privateInfo[5] = 0xFF;

#ifdef AO_ON_SCPU
    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_PRIVATEINFO
        , (unsigned char *)cmd, sizeof(*cmd)
        , (unsigned char *)res, sizeof(AUDIO_RPC_PRIVATEINFO_RETURNVAL)
        , (unsigned char *)&rpc_ret, sizeof(rpc_ret));
#else
    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_PRIVATEINFO,
        CONVERT_FOR_AVCPU(dat), //cmd address
        CONVERT_FOR_AVCPU(dat + offset), //res address
        &rpc_ret)) {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit; 
    }

    if (rpc_ret != S_OK) {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit; 
    }
#endif
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_STOP_SVC(int instanceID) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    RPC_TOAGENT_STOP_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_RPC();
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA %s malloc fail]\n", __FUNCTION__);
        goto exit;
    }
 
    rpc = ion_map_kernel(alsa_client, handle);
    rpc->instanceID = htonl(instanceID);

#ifdef AO_ON_SCPU
    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_STOP
        , (unsigned char *)rpc + sizeof(rpc->retval) + sizeof(rpc->res), sizeof(rpc->instanceID)
        , (unsigned char *)rpc, sizeof(rpc->retval)
        , (unsigned char *)&rpc->res, sizeof(rpc->res));
#else
    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_STOP,
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->retval) + sizeof(rpc->res))), //rpc->instanceID address
        CONVERT_FOR_AVCPU(dat),//rpc->retval address
        &rpc->res)) {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (rpc->res != S_OK || ntohl(rpc->retval.result) != S_OK) {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
#endif
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_PP_INIT_PIN_SVC(int instanceID)
{
    RPC_TOAGENT_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[%s malloc fail]\n", __FUNCTION__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);
    rpc->inst_id = htonl(instanceID);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_VIDEO_KERNEL_RPC_PP_INIT_PIN,
        CONVERT_FOR_AVCPU(dat), //rpc->inst_id address
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->inst_id))), //rpc->retval address
        &rpc->res)) {
        ALSA_WARNING("[%s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (rpc->res != S_OK || ntohl(rpc->retval.result) != S_OK) {
        ALSA_WARNING("[%s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_DESTROY_SVC(int instanceID) 
{
    RPC_TOAGENT_DESTROY_T *rpc;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_RPC();
    TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
   handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA %s malloc fail]\n", __FUNCTION__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);
    rpc->instanceID = htonl(instanceID);

#ifdef AO_ON_SCPU
    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_DESTROY
        , (unsigned char *)&rpc->instanceID, sizeof(rpc->instanceID)
        , (unsigned char *)rpc, sizeof(rpc->retval)
        , (unsigned char *)&rpc->res, sizeof(rpc->res));
#else
    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_DESTROY,
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->retval) + sizeof(rpc->res))), //rpc->instanceID address
        CONVERT_FOR_AVCPU(dat), //rpc->retval address
        &rpc->res)) {
        ALSA_WARNING("%s %d RPC fail\n", __FILE__, __LINE__);
        goto exit;
    }

    if (rpc->res != S_OK || ntohl(rpc->retval.result) != S_OK) {
        ALSA_WARNING("%s %d RPC fail\n", __FILE__, __LINE__);
        goto exit;
    }
#endif
//    printk(KERN_ALERT "[ALSA] @ %s\n", __FUNCTION__);
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_INBAND_EOS_SVC(snd_card_RTK_pcm_t * dpcm) 
{
    AUDIO_DEC_EOS cmd ;

    TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    cmd.header.type = htonl(AUDIO_DEC_INBAND_CMD_TYPE_EOS);
    cmd.header.size = htonl(sizeof(AUDIO_DEC_EOS));
    cmd.EOSID = 0;
    cmd.wPtr = htonl(dpcm->decInRing_LE[0].writePtr);
#ifdef CONFIG_64BIT
    writeInbandCmd(dpcm, &cmd, sizeof(AUDIO_DEC_EOS));
#else
    //snd_realtek_hw_ring_write(((unsigned int)dpcm->decInbandRing - (unsigned int)dpcm + dpcm->phy_addr), &cmd, sizeof(AUDIO_DEC_EOS));
    snd_realtek_hw_ring_write(&dpcm->decInbandRing, &cmd, sizeof(AUDIO_DEC_EOS), (unsigned int)dpcm - (unsigned int)dpcm->phy_addr);
#endif
    return 0;
}

// set TRUEHD_ERR_SELF_RESET_ENABLED
int RPC_TOAGENT_SET_TRUEHD_ERR_SELF_RESET(bool isON)
{
    AUDIO_CONFIG_COMMAND *config;
    unsigned int *res;
    HRESULT ret;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;
    unsigned long offset;
    TRACE_RPC();
    TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }

    //config = (AUDIO_CONFIG_COMMAND  *) (unsigned int)page_address(page);
    config = ion_map_kernel(alsa_client, handle);
    config->msgID = htonl(AUDIO_CONFIG_TRUEHD_ERR_SELF_RESET_ENABLED);
    config->value[0] = htonl(isON);

    //res = (unsigned int*) (((unsigned long)config + sizeof(AUDIO_CONFIG_COMMAND) + 8) & PRIVATE_INFO_MASK);
    offset = get_rpc_alignment_offset(sizeof(AUDIO_CONFIG_COMMAND));
    res = (unsigned int*)((unsigned long)config + offset);
    //offset = (unsigned long)res - (unsigned long)config;

    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_AUDIO_CONFIG,
        CONVERT_FOR_AVCPU(dat),
        CONVERT_FOR_AVCPU(dat + offset),
        &ret)) {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        ret = -1;
        goto exit;
    }

    if (ret != S_OK) {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        ret = -1;
        goto exit;
    }
    TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

// set AO volume
int RPC_TOAGENT_SET_VOLUME(int volume) 
{
    AUDIO_CONFIG_COMMAND *config;
    unsigned int *res;
    HRESULT ret;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;
    unsigned long offset;

    TRACE_RPC();
    TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }

    //config = (AUDIO_CONFIG_COMMAND  *) (unsigned int)page_address(page);
    config = ion_map_kernel(alsa_client, handle);
    config->msgID = htonl(AUDIO_CONFIG_CMD_VOLUME);
    config->value[0] = htonl(31 - volume);

    //res = (unsigned int*) (((unsigned long)config + sizeof(AUDIO_CONFIG_COMMAND) + 8) & PRIVATE_INFO_MASK);
    offset = get_rpc_alignment_offset(sizeof(AUDIO_CONFIG_COMMAND));
    res = (unsigned int*)((unsigned long)config + offset);
    //offset = (unsigned long)res - (unsigned long)config;

#ifdef AO_ON_SCPU
    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_VOLUME_CONTROL
        , (unsigned char *)config, sizeof(*config)
        , (unsigned char *)res, sizeof(unsigned int *)
        , (unsigned char *)&ret, sizeof(ret));
#else
    // set gpAudio->ao_volume_level(from Audio FW)
    //if (send_rpc_command(RPC_AUDIO, ENUM_KERNEL_RPC_VOLUME_CONTROL, (unsigned int) config,(unsigned int) res, &ret)) {
    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_VOLUME_CONTROL,
        CONVERT_FOR_AVCPU(dat),
        CONVERT_FOR_AVCPU(dat + offset),
        &ret)) {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        ret = -1;
        goto exit;
    }

    if (ret != S_OK) {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        ret = -1;
        goto exit;
    }
#endif
    TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

// get AO volume
int RPC_TOAGENT_GET_VOLUME(snd_card_RTK_pcm_t *mars) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    int volume = 0;
    AUDIO_RPC_PRIVATEINFO_PARAMETERS *pArg;
    AUDIO_RPC_PRIVATEINFO_RETURNVAL *pRet;
    int offset;
    HRESULT rc;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_RPC();
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }

    offset = get_rpc_alignment_offset(sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    pArg = ion_map_kernel(alsa_client, handle);
    pRet = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned long)pArg + offset);
    pArg->type = htonl(ENUM_PRIVATEINFO_AUDIO_GET_MUTE_N_VOLUME);
//    flush_dcache_page(page);

#ifdef AO_ON_SCPU
    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_GET_MUTE_N_VOLUME
        , (unsigned char *)&config->param, sizeof(config->param)
        , (unsigned char *)config, sizeof(config->res)
        , (unsigned char *)&config->ret, sizeof(config->ret));
#else
    //if (send_rpc_command(RPC_AUDIO, ENUM_KERNEL_RPC_GET_MUTE_N_VOLUME , (unsigned int) &(config->param),(unsigned int) &(config->res), &(config->ret))) {
    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_GET_MUTE_N_VOLUME,
        CONVERT_FOR_AVCPU(dat),
        CONVERT_FOR_AVCPU(dat + offset),
        &rc)) {
        ALSA_WARNING("[fail %s %d]\n", __FUNCTION__, __LINE__);
        volume = -1;
        goto exit;
    }
#endif
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    // get gpAudio->ao_volume_level (from audio FW)
    volume = ntohl(pRet->privateInfo[1]);

exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return volume;
}

int RPC_TOAGENT_AI_CONFIG_I2S_IN(snd_card_RTK_capture_pcm_t *dpcm)
{
    AUDIO_RPC_PRIVATEINFO_PARAMETERS *rpc = NULL;
    HRESULT RPC_ret;
    unsigned int offset;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if(ion_phys(alsa_client, handle, &dat, &len) != 0)
    {
        ALSA_WARNING("[ALSA %s %d fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);
    offset = get_rpc_alignment_offset(sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    rpc->instanceID = htonl(dpcm->AIAgentID);
    rpc->type = htonl(ENUM_PRIVATEINFO_AUDIO_AI_PAD_IN);
	rpc->privateInfo[0] = htonl(48000);

    if(send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_PRIVATEINFO,
        CONVERT_FOR_AVCPU(dat),
        CONVERT_FOR_AVCPU(dat + offset),
        &RPC_ret))
    {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }

    if(RPC_ret != S_OK )
    {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if(handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_SET_AI_FLASH_VOLUME(snd_card_RTK_capture_pcm_t *dpcm, unsigned int volume)
{
	//TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    
	AUDIO_RPC_AIO_PRIVATEINFO_PARAMETERS *rpc = NULL;
	AUDIO_RPC_PRIVATEINFO_RETURNVAL *res;
	struct ion_handle *handle = NULL;
	HRESULT rpc_ret;
	unsigned int offset;
    int ret = -1;
	ion_phys_addr_t dat;
	size_t len;
	
	TRACE_RPC();
	handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);
	
	if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
	
	if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
	
	rpc = ion_map_kernel(alsa_client, handle);
	offset = get_rpc_alignment_offset(sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
	res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned long)rpc + offset);
	rpc->instanceID = htonl(dpcm->AIAgentID);    
	rpc->type = htonl(ENUM_PRIVATEINFO_AIO_AI_PRIVATEINFO);
	rpc->argateInfo[0] = htonl(ENUM_AI_PRIVATE_ADC_SET_VOLUME);
	rpc->argateInfo[1] = htonl(volume); // ADC left channel digital volume in 0.5 dB step, -33.5dB~30dB
	rpc->argateInfo[2] = htonl(volume); // ADC right channel digital volume in 0.5 dB step, -33.5dB~30dB
	
	if(send_rpc_command(RPC_AUDIO,
		ENUM_KERNEL_RPC_AIO_PRIVATEINFO,
		CONVERT_FOR_AVCPU(dat),
		CONVERT_FOR_AVCPU(dat + offset),
		&rpc_ret)) {
		ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
	}
	
	if(rpc_ret != S_OK) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
	
	TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
	
exit:
	if(handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_SET_SOFTWARE_AI_FLASH_VOLUME(snd_card_RTK_capture_pcm_t *dpcm, unsigned int volume)
{
	//TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    
	AUDIO_RPC_AIO_PRIVATEINFO_PARAMETERS *rpc = NULL;
	AUDIO_RPC_PRIVATEINFO_RETURNVAL *res;
	struct ion_handle *handle = NULL;
	HRESULT rpc_ret;
	unsigned int offset;
    int ret = -1, rpc_volume;
	ion_phys_addr_t dat;
	size_t len;
	
	/* The range of software control volume index is from 0 to 32. */
	if (volume >= 0 && volume < 17)
		rpc_volume = ENUM_AUDIO_VOLUME_CTRL_0_DB + volume;
	else if (volume >= 17 && volume < 33)
		rpc_volume = ENUM_AUDIO_VOLUME_CTRL_P1_DB + volume%17;
	else
		goto exit;
	
	TRACE_RPC();
	handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);
	
	if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
	
	if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
	
	rpc = ion_map_kernel(alsa_client, handle);
	offset = get_rpc_alignment_offset(sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
	res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned long)rpc + offset);
	rpc->instanceID = htonl(dpcm->AIAgentID);    
	rpc->type = htonl(ENUM_PRIVATEINFO_AIO_AI_PRIVATEINFO);
	rpc->argateInfo[0] = htonl(ENUM_AI_PRIVATE_VOLUME_CTRL);
	rpc->argateInfo[1] = htonl(rpc_volume); // one of AUDIO_VOLUME_CTRL
	
	if(send_rpc_command(RPC_AUDIO,
		ENUM_KERNEL_RPC_AIO_PRIVATEINFO,
		CONVERT_FOR_AVCPU(dat),
		CONVERT_FOR_AVCPU(dat + offset),
		&rpc_ret)) {
		ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
	}
	
	if(rpc_ret != S_OK) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
	
	TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
	
exit:
	if(handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_AI_CONFIG_NONPCM_IN(snd_card_RTK_capture_pcm_t *dpcm)
{
    AUDIO_RPC_PRIVATEINFO_PARAMETERS *rpc = NULL;
    HRESULT RPC_ret;
    unsigned int offset;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if(ion_phys(alsa_client, handle, &dat, &len) != 0)
    {
        ALSA_WARNING("[ALSA %s %d fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);
    offset = get_rpc_alignment_offset(sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    rpc->instanceID = htonl(dpcm->AIAgentID);
    rpc->type = htonl(ENUM_PRIVATEINFO_AUDIO_AI_NON_PCM_IN);

    if(send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_PRIVATEINFO,
        CONVERT_FOR_AVCPU(dat),
        CONVERT_FOR_AVCPU(dat + offset),
        &RPC_ret))
    {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }

    if(RPC_ret != S_OK )
    {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if(handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}


int RPC_TOAGENT_CREATE_AI_AGENT(snd_card_RTK_capture_pcm_t *dpcm)
{
    RPC_CREATE_AO_AGENT_T *rpc = NULL;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;

    TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if(ion_phys(alsa_client, handle, &dat, &len) != 0)
    {
        ALSA_WARNING("[ALSA %s %d fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = ion_map_kernel(alsa_client, handle);
    rpc->info.instanceID = htonl(-1);
    rpc->info.type = htonl(AUDIO_IN);

    if(send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_CREATE_AGENT,
        CONVERT_FOR_AVCPU(dat),
        CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(rpc->info))),
        &rpc->ret))
    {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }

    if(ntohl(rpc->retval.result) != S_OK || rpc->ret != S_OK)
    {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }

    dpcm->AIAgentID = ntohl(rpc->retval.data);
//    printk(KERN_ALERT "[ALSA Create AI instance %d]\n", dpcm->AIAgentID);
    TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    // success
    ret = 0;
exit:
    if(handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_CONFIGURE_AI_HW(snd_pcm_runtime_t *runtime) 
{
    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
    AUDIO_CONFIG_ADC *rpc = NULL;
    AUDIO_ADC_CONFIG *pConfig = NULL;
    HRESULT *rpc_arg;
    int ret = -1;
    HRESULT RPC_ret;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;
    unsigned int offset;

    TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if(ion_phys(alsa_client, handle, &dat, &len) != 0)
    {
        ALSA_WARNING("[ALSA %s %d fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }
    rpc = ion_map_kernel(alsa_client, handle);
    //rpc_arg = (HRESULT *)((unsigned int)(rpc + sizeof(AUDIO_CONFIG_ADC) + 8) & 0xFFFFFFFC);
    offset = get_rpc_alignment_offset(sizeof(AUDIO_CONFIG_ADC));
    rpc_arg = (HRESULT *)((unsigned long)rpc + offset);

    //offset = (unsigned int)rpc_arg - (unsigned int)rpc;

    pConfig = &rpc->adcConfig;
    rpc->instanceID = htonl(dpcm->AIAgentID);
    pConfig->audioGeneralConfig.interface_en = 1;
    pConfig->audioGeneralConfig.channel_in = 0x3;
    pConfig->sampleInfo.sampling_rate = htonl(runtime->rate);
    pConfig->sampleInfo.PCM_bitnum = htonl(24);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_ADC0_CONFIG,
        CONVERT_FOR_AVCPU(dat),//rpc address
        CONVERT_FOR_AVCPU(dat + offset), //rpc_arg address
        &RPC_ret))
    {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }
    TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if(handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_AI_CONNECT_ALSA(snd_card_RTK_capture_pcm_t *dpcm)
{
    AUDIO_RPC_PRIVATEINFO_PARAMETERS *cmd;
    AUDIO_RPC_PRIVATEINFO_RETURNVAL*res;
    HRESULT RPC_ret;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;
    unsigned int offset;

    TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if(ion_phys(alsa_client, handle, &dat, &len) != 0)
    {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }

    cmd = ion_map_kernel(alsa_client, handle);
    //res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned int)(cmd + sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS)+8) & 0xFFFFFFFC);
    offset = get_rpc_alignment_offset(sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned long)cmd + offset);
    //offset = (unsigned int)res - (unsigned int)cmd;

    memset(cmd, 0, sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    cmd->instanceID = htonl(dpcm->AIAgentID);
    cmd->type = htonl(ENUM_PRIVATEINFO_AUDIO_AI_CONNECT_ALSA);
    cmd->privateInfo[0] = htonl(dpcm->nAIFormat);

    if(send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_PRIVATEINFO,
        CONVERT_FOR_AVCPU(dat),
        CONVERT_FOR_AVCPU(dat + offset),
        &RPC_ret))
    {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if(RPC_ret != S_OK )
    {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    ret = 0;
exit:
    if(handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_DESTROY_AUDIO_FLOW(int pid)
{
    AUDIO_RPC_PRIVATEINFO_PARAMETERS *cmd = NULL;
    AUDIO_RPC_PRIVATEINFO_RETURNVAL *res;
    HRESULT RPC_ret;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;
    unsigned int offset;
    //ALSA_WARNING("[%s] PID = %d\n",__func__,pid);

    TRACE_RPC();
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }

    //cmd = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);
    cmd = ion_map_kernel(alsa_client, handle);
    //res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned int)((unsigned int)cmd + sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS)+8) & PRIVATE_INFO_MASK);
    offset = get_rpc_alignment_offset(sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned long)cmd + offset);
    //offset = (unsigned long)res - (unsigned long)cmd;
    memset(cmd, 0, sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    cmd->instanceID = htonl(-1);
    cmd->type = htonl(ENUM_PRIVATEINFO_AUDIO_DO_SELF_DESTROY_FLOW);
    cmd->privateInfo[0] = htonl(pid);

#ifdef AO_ON_SCPU
    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_PRIVATEINFO
        , (unsigned char *)cmd, sizeof(*cmd)
        , (unsigned char *)res, sizeof(*res)
        , (unsigned char *)&RPC_ret, sizeof(RPC_ret));
#else
    if (send_rpc_command(RPC_AUDIO,
                ENUM_KERNEL_RPC_PRIVATEINFO,
                CONVERT_FOR_AVCPU(dat),
                CONVERT_FOR_AVCPU(dat + offset),
                &RPC_ret)) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
    }

    if (RPC_ret != S_OK ) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
#endif

exit:
    if(handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

int RPC_TOAGENT_SET_LOW_WATER_LEVEL(bool isLowWater)
{
    AUDIO_RPC_PRIVATEINFO_PARAMETERS *cmd;
    AUDIO_RPC_PRIVATEINFO_RETURNVAL *res;
    HRESULT RPC_ret;
    int ret = -1;
    struct ion_handle *handle = NULL;
    ion_phys_addr_t dat;
    size_t len;
    unsigned long offset;

    TRACE_RPC();
    handle = ion_alloc(alsa_client, 4096, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (ion_phys(alsa_client, handle, &dat, &len) != 0) {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }

    cmd = ion_map_kernel(alsa_client, handle);
    offset = get_rpc_alignment_offset(sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned long)cmd + offset);
    memset(cmd, 0, sizeof(*cmd));
    memset(res, 0, sizeof(*res));
    cmd->type = htonl(ENUM_PRIVATEINFO_AUDIO_SET_LOW_WATERLEVEL);
    if (isLowWater) {
        cmd->privateInfo[0] = htonl(0x1);
        printk("Enable pp ao low waterlevel mode\n");
    } else {
        cmd->privateInfo[0] = 0;
        printk("Disable pp ao low waterlevel mode\n");
    }
    cmd->privateInfo[1] = 0;
    cmd->privateInfo[2] = 0;
    cmd->privateInfo[3] = 0;

#ifdef AO_ON_SCPU
    rtk_ao_kernel_rpc(ENUM_KERNEL_RPC_PRIVATEINFO
        , (unsigned char *)cmd, sizeof(*cmd)
        , (unsigned char *)res, sizeof(AUDIO_RPC_PRIVATEINFO_RETURNVAL)
        , (unsigned char *)&RPC_ret, sizeof(unsigned int));
#else
    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_PRIVATEINFO,
        CONVERT_FOR_AVCPU(dat), //cmd address
        CONVERT_FOR_AVCPU(dat + offset),//res address
        &RPC_ret)) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (RPC_ret != S_OK ) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
#endif

    // successful
    ret = 0;
exit:
    if (handle != NULL) {
        ion_unmap_kernel(alsa_client, handle);
        ion_free(alsa_client, handle);
    }
    return ret;
}

#else // use dma

int RPC_TOAGENT_CHECK_AUDIO_READY() 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    RPC_DEFAULT_INPUT_T *rpc = NULL;
    int ret = -1;
    dma_addr_t dat;
    void *addr = 0;

    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);
    if(!addr) {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = addr;

    if(send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_CHECK_READY,
        CONVERT_FOR_AVCPU(dat), //rpc->info address
        CONVERT_FOR_AVCPU(dat + sizeof(rpc->info)), //rpc->retval address
        &rpc->ret)) {
        ALSA_WARNING("[ALSA %s RPC fail]\n", __FUNCTION__);
        goto exit;
    }
    
    if(rpc->ret != S_OK ) {
        ALSA_WARNING("[ALSA %s RPC fail]\n", __FUNCTION__);
        goto exit;
    }

    if(rpc->info == 0) {
        ALSA_WARNING("[ALSA Audio is not ready]\n");
        goto exit;
    }

    //TRACE_CODE("[%s %s %d ] success\n", __FILE__, __FUNCTION__, __LINE__);

    // successful
    ret = 0;
exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);
    return ret;
}

int RPC_TOAGENT_CREATE_AO_AGENT(snd_card_RTK_pcm_t *dpcm) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    
    RPC_CREATE_AO_AGENT_T *rpc;
    int ret = -1;
    dma_addr_t dat;
    void *addr = 0;

    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);
    if(!addr) {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = addr;
    rpc->info.instanceID = htonl(0);
    rpc->info.type = htonl(AUDIO_OUT);//AUDIO_ALSA_OUT

    if(send_rpc_command(RPC_AUDIO, 
        ENUM_KERNEL_RPC_CREATE_AGENT,
        CONVERT_FOR_AVCPU(dat), //rpc->info address
        CONVERT_FOR_AVCPU(dat + sizeof(rpc->info)),//rpc->retval address
        &rpc->ret)) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }
    
    if(ntohl(rpc->retval.result) != S_OK || rpc->ret != S_OK) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }

    dpcm->AOAgentID = ntohl(rpc->retval.data);
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
    // success
    ret = 0;
exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);
    return ret;
}
 


int RPC_TOAGENT_PUT_SHARE_MEMORY(void *p)
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    AUDIO_RPC_PRIVATEINFO_PARAMETERS *cmd;  
    AUDIO_RPC_PRIVATEINFO_RETURNVAL*res;
    int ret = 0;
    HRESULT RPC_ret;
    dma_addr_t dat;
    void *addr = 0;
    unsigned int offset;

    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);

    if(!addr)
    {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }

    cmd = addr;
    res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned int)(cmd + sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS)+8) & 0xFFFFFFFC);

    offset = (unsigned int)res - (unsigned int)cmd;

    memset(cmd, 0, sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    cmd->type = htonl(ENUM_PRIVATEINFO_AUDIO_GET_SHARE_MEMORY_FROM_ALSA);           
    cmd->privateInfo[0] = htonl((int)p);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_PRIVATEINFO,
        CONVERT_FOR_AVCPU(dat),
        CONVERT_FOR_AVCPU(dat+offset),
        &RPC_ret))
    {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (RPC_ret != S_OK )  
    {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit; 
    }

exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);
    
    return ret;
}

int RPC_TOAGENT_GET_AO_FLASH_PIN(snd_card_RTK_pcm_t *dpcm) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    
    AUDIO_RPC_PRIVATEINFO_PARAMETERS *cmd;  
    AUDIO_RPC_PRIVATEINFO_RETURNVAL *res;
    HRESULT RPC_ret;
    int ret = -1;
    dma_addr_t dat;
    void *addr = 0;
    unsigned int offset;

    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);

    if(!addr) {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }

    cmd = addr;
    res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned int)(cmd + sizeof(cmd)+8) & 0xFFFFFFFC);
    offset = (unsigned int)res - (unsigned int)cmd;

    memset(cmd, 0, sizeof(cmd));
    cmd->instanceID = htonl(dpcm->AOAgentID);   
    cmd->type = htonl(ENUM_PRIVATEINFO_AUDIO_GET_FLASH_PIN);
    cmd->privateInfo[0] = 0xFF; 
    cmd->privateInfo[1] = 0xFF;
    cmd->privateInfo[2] = 0xFF; 
    cmd->privateInfo[3] = 0xFF;     
    cmd->privateInfo[4] = 0xFF;     
    cmd->privateInfo[5] = 0xFF; 

    if(send_rpc_command(RPC_AUDIO, 
        ENUM_KERNEL_RPC_PRIVATEINFO, 
        CONVERT_FOR_AVCPU(dat), //cmd address
        CONVERT_FOR_AVCPU(dat + offset),//res address
        &RPC_ret)) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if(RPC_ret != S_OK ) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit; 
    }
    
    ret = ntohl(res->privateInfo[0]);
    
    if(ret < FLASH_AUDIO_PIN_1 || ret > FLASH_AUDIO_PIN_3) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        ret = -1;
    }

    //ALSA_WARNING("GET_AO_FLASH_PIN ret %d\n", ret);
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);

    return ret;
}



int RPC_TOAGENT_SET_AO_FLASH_VOLUME(snd_pcm_substream_t * substream) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
        
    snd_pcm_runtime_t *runtime = substream->runtime;
    snd_card_RTK_pcm_t *dpcm = runtime->private_data;   
    HRESULT RPC_ret;
    AUDIO_RPC_PRIVATEINFO_PARAMETERS *cmd;  
    AUDIO_RPC_PRIVATEINFO_RETURNVAL *res;
    int ret = -1;
    dma_addr_t dat;
    void *addr = 0;
    unsigned int offset;
    
    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);
    
    if(!addr) {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }
  
    //cmd = (AUDIO_RPC_PRIVATEINFO_PARAMETERS *) ((unsigned int)page_address(page));
    //res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *) ((((unsigned int) page_address(page) + sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS)+8) & 0xFFFFFFFC));   
    cmd = addr;
    res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned int)(cmd + sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS)+8) & 0xFFFFFFFC);
    offset = (unsigned int)res - (unsigned int)cmd;
    
    memset(cmd, 0, sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    cmd->instanceID = htonl(dpcm->AOAgentID);   
    cmd->type = htonl(ENUM_PRIVATEINFO_AUDIO_CONTROL_FLASH_VOLUME);         
    cmd->privateInfo[0] = htonl(dpcm->AOpinID); 
    cmd->privateInfo[1] = htonl((31-dpcm->volume));

    if(send_rpc_command(RPC_AUDIO, 
        ENUM_KERNEL_RPC_PRIVATEINFO, 
        CONVERT_FOR_AVCPU(dat),
        CONVERT_FOR_AVCPU(dat + offset),
        &rpc_ret)) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if(rpc_ret != S_OK) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    // success
    ret = 0;
    //ALSA_VitalPrint("[ALSA set AO_pin %d volume %d]\n", dpcm->AOpinID, dpcm->volume);
exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);
    return ret;
}

int RPC_TOAGENT_CREATE_DECODER_AGENT(snd_card_RTK_pcm_t * dpcm) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    
    RPC_CREATE_PCM_DECODER_CTRL_T* rpc = NULL;
    int ret = -1;
    dma_addr_t dat;
    void *addr = 0;

    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);
    if(!addr) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = addr;
    rpc->instance.type = htonl(AUDIO_DECODER);
    rpc->instance.instanceID = htonl(-1);   

    if(send_rpc_command(RPC_AUDIO, 
        ENUM_KERNEL_RPC_CREATE_AGENT, 
        CONVERT_FOR_AVCPU(dat), //rpc->instance address
        CONVERT_FOR_AVCPU(dat + sizeof(rpc->instance)), //rpc->res address
        &rpc->ret)) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if(rpc->ret != S_OK) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    dpcm->DECAgentID = ntohl(rpc->res.data);
    dpcm->DECpinID = BASE_BS_IN ;

    ret = 0;
    printk("[ALSA Create Decoder instance %d]\n", dpcm->DECAgentID);
    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);

exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);

    return ret;
}

// data of AUDIO_RPC_RINGBUFFER_HEADER is "hose side"
int RPC_TOAGENT_INITRINGBUFFER_HEADER_SVC(AUDIO_RPC_RINGBUFFER_HEADER *header, int buffer_count) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    RPC_INITRINGBUFFER_HEADER_T *rpc;
    int ch;
    int ret = -1;
    dma_addr_t dat;
    void *addr = 0;

    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);
    if(!addr) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = addr;
    rpc->header.instanceID = htonl(header->instanceID);
    rpc->header.pinID = htonl(header->pinID);
    rpc->header.readIdx = htonl(header->readIdx); 
    rpc->header.listSize = htonl(header->listSize);

    //printk(" header instance ID %d\n", header->instanceID);
    //printk(" header pinID       %d\n", header->pinID);
    //printk(" header readIdx     %d\n", header->readIdx);
    //printk(" header listSize    %d\n", header->listSize);

    for( ch = 0; ch < buffer_count; ch++) {
        //rpc_initringbuffer->header.pRingBufferHeaderList[i] = htonl(0xa0000000|(((unsigned int) header->pRingBufferHeaderList[i])&0x1FFFFFFF));
        //printk("[test]header.pRingBufferHeaderList[%d] = %lx\n", ch, header->pRingBufferHeaderList[ch]); 
        rpc->header.pRingBufferHeaderList[ch] = htonl((unsigned int) header->pRingBufferHeaderList[ch]);
        //rpc->header.pRingBufferHeaderList[ch] = htonl(0xa0000000|(((unsigned int) header->pRingBufferHeaderList[ch])&0x1FFFFFFF));
        
    }
    
    if(send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_INIT_RINGBUF,
        CONVERT_FOR_AVCPU(dat + sizeof(rpc->ret) + sizeof(rpc->res)), //rpc->header address
        CONVERT_FOR_AVCPU(dat), //rpc->ret address
        &rpc->res)) {
        ALSA_WARNING("[%s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if(rpc->res != S_OK || ntohl(rpc->ret.result) != S_OK) {
        ALSA_WARNING("[%s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit; 
    }

    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);

    // success
    ret = 0;

exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);
    return ret;
}

int RPC_TOAGENT_CONNECT_SVC(AUDIO_RPC_CONNECTION *pconnection) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    RPC_CONNECTION_T *rpc;
    int ret = -1;
    dma_addr_t dat;
    void *addr = 0;

    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);
    if(!addr) {
        ALSA_WARNING("[%s malloc fail]\n", __FUNCTION__);
        goto exit;
    }
    
    rpc = addr; 
    rpc->out.srcInstanceID = htonl(pconnection->srcInstanceID); 
    rpc->out.srcPinID = htonl(pconnection->srcPinID);   
    rpc->out.desInstanceID = htonl(pconnection->desInstanceID); 
    rpc->out.desPinID= htonl(pconnection->desPinID);        
    
    if(send_rpc_command(RPC_AUDIO, 
        ENUM_KERNEL_RPC_CONNECT, 
        CONVERT_FOR_AVCPU(dat), //rpc->out address
        CONVERT_FOR_AVCPU(dat + sizeof(rpc->out)), //rpc->ret
        &rpc->res)) {
        ALSA_WARNING("[%s RPC fail %d]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if(rpc->res != S_OK || ntohl(rpc->ret.result) != S_OK) {
        ALSA_WARNING("[%s RPC fail %d]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);

    // success
    ret = 0;
exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);
    return ret;
}

int RPC_TOAGENT_PAUSE_SVC(int instance_id) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    RPC_TOAGENT_PAUSE_T *rpc;
    int ret = -1;
    dma_addr_t dat;
    void *addr = 0;

    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);
    if(!addr) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
    
    rpc = addr;
    rpc->inst_id = htonl(instance_id);
    
    if(send_rpc_command(RPC_AUDIO, 
        ENUM_KERNEL_RPC_PAUSE, 
        CONVERT_FOR_AVCPU(dat), //rpc->inst_id address
        CONVERT_FOR_AVCPU(dat + sizeof(rpc->inst_id)),//rpc->retval address
        &rpc->res)) {
        ALSA_WARNING("[%s %d RPC fail\n]", __FUNCTION__, __LINE__);
        goto exit;
    }

    if(rpc->res != S_OK) {
        ALSA_WARNING("[%s %d RPC fail\n]", __FUNCTION__, __LINE__);
        goto exit;
    }

    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);

    // success
    ret = 0;
exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);
    return ret;
}

int RPC_TOAGENT_RUN_SVC(int instance_id) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    RPC_TOAGENT_T *rpc;
    int ret = -1;
    dma_addr_t dat;
    void *addr = 0;

    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);
    if(!addr) {
        ALSA_WARNING("[%s malloc fail]\n", __FUNCTION__);
        goto exit;
    }
   
    rpc = addr;    
    rpc->inst_id = htonl(instance_id);
    
    if(send_rpc_command(RPC_AUDIO, 
        ENUM_KERNEL_RPC_RUN, 
        CONVERT_FOR_AVCPU(dat), //rpc->inst_id address
        CONVERT_FOR_AVCPU(dat + sizeof(rpc->inst_id)), //rpc->retval address
        &rpc->res)) {
        ALSA_WARNING("[%s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if(rpc->res != S_OK || ntohl(rpc->retval.result) != S_OK) {
        ALSA_WARNING("[%s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);

    // success
    ret = 0;
exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);
    return ret;
}  

int RPC_TOAGENT_FLUSH_SVC(AUDIO_RPC_SENDIO  *sendio) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    RPC_TOAGENT_FLASH_T *rpc;
    int ret = -1;
    dma_addr_t dat;
    void *addr = 0;
    
    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);
    if(!addr) {
        ALSA_WARNING("[ALSA %s malloc fail]\n", __FUNCTION__);
        goto exit;
    }
    
    rpc = addr;
    rpc->sendio.instanceID = htonl(sendio->instanceID);
    rpc->sendio.pinID = htonl(sendio->pinID);

    if(send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_FLUSH,
        CONVERT_FOR_AVCPU(dat + sizeof(rpc->retval) + sizeof(rpc->res)), //rpc->sendio address
        CONVERT_FOR_AVCPU(dat), //rpc->retval address
        &rpc->res)) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if(rpc->res != S_OK || ntohl(rpc->retval.result) != S_OK) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);

    // success
    ret = 0;
exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);  
    return ret;
}

int RPC_TOAGENT_RELEASE_AO_FLASH_PIN(snd_card_RTK_pcm_t *dpcm) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    HRESULT rpc_ret = 0;
    int ret = -1;
    AUDIO_RPC_PRIVATEINFO_PARAMETERS *cmd;  
    AUDIO_RPC_PRIVATEINFO_RETURNVAL *res;
    dma_addr_t dat;
    void *addr = 0;
    unsigned int offset;

    if(dpcm->AOpinID < FLASH_AUDIO_PIN_1 || dpcm->AOpinID > FLASH_AUDIO_PIN_3) {
       ALSA_WARNING("[%d @ %s %d]\n", dpcm->AOpinID, __FUNCTION__, __LINE__);
       goto exit;
    }
    
    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);
    
    if(!addr) {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }

    cmd = addr;
    res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned int)(cmd + sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS)+8) & 0xFFFFFFFC);
    offset = (unsigned int)res - (unsigned int)cmd;
    
    memset(cmd, 0, sizeof(cmd));
    cmd->instanceID = htonl(dpcm->AOAgentID);   
    cmd->type = htonl(ENUM_PRIVATEINFO_AUDIO_RELEASE_FLASH_PIN);            
    cmd->privateInfo[0] = htonl(dpcm->AOpinID); 
    cmd->privateInfo[1] = 0xFF;
    cmd->privateInfo[2] = 0xFF; 
    cmd->privateInfo[3] = 0xFF;     
    cmd->privateInfo[4] = 0xFF;     
    cmd->privateInfo[5] = 0xFF; 
    
    if(send_rpc_command(RPC_AUDIO, 
        ENUM_KERNEL_RPC_PRIVATEINFO, 
        CONVERT_FOR_AVCPU(dat), //cmd address
        CONVERT_FOR_AVCPU(dat + offset), //res address
        &rpc_ret)) {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit; 
    }

    if(rpc_ret != S_OK) {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit; 
    }

    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);

    ret = 0;

exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);

    return ret;
}

int RPC_TOAGENT_STOP_SVC(int instanceID) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    RPC_TOAGENT_STOP_T *rpc;
    int ret = -1;
    dma_addr_t dat;
    void *addr = 0;
    
    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);

    if(!addr) {
        ALSA_WARNING("[ALSA %s malloc fail]\n", __FUNCTION__);
        goto exit;
    }
    
    rpc = addr;
    rpc->instanceID = htonl(instanceID);
    
    if(send_rpc_command(RPC_AUDIO, 
        ENUM_KERNEL_RPC_STOP,
        CONVERT_FOR_AVCPU(dat + sizeof(rpc->retval) + sizeof(rpc->res)), //rpc->instanceID address
        CONVERT_FOR_AVCPU(dat),//rpc->retval address
        &rpc->res))
    {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit; 
    }

    if(rpc->res != S_OK || ntohl(rpc->retval.result) != S_OK)
    {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        goto exit; 
    }

    ret = 0;
exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);
    return ret;
}

int RPC_TOAGENT_DESTROY_SVC(int instanceID) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    RPC_TOAGENT_DESTROY_T *rpc;
    int ret = -1;
    dma_addr_t dat;
    void *addr = 0;

    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);
    if(!addr) 
    {
        ALSA_WARNING("[ALSA %s malloc fail]\n", __FUNCTION__);
        goto exit;
    }

    rpc = addr;
    rpc->instanceID = htonl(instanceID);

    if(send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_DESTROY,
        CONVERT_FOR_AVCPU(dat + sizeof(rpc->retval) + sizeof(rpc->res)), //rpc->instanceID address
        CONVERT_FOR_AVCPU(dat), //rpc->retval address
        &rpc->res)) {
        ALSA_WARNING("%s %d RPC fail\n", __FILE__, __LINE__);
        goto exit;
    }

    if(rpc->res != S_OK || ntohl(rpc->retval.result) != S_OK) {
        ALSA_WARNING("%s %d RPC fail\n", __FILE__, __LINE__);
        goto exit;
    }

    ret = 0;
exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);
    return ret;
}

int RPC_TOAGENT_INBAND_EOS_SVC(snd_card_RTK_pcm_t * dpcm) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    AUDIO_DEC_EOS cmd ;
    
    cmd.header.type = htonl(AUDIO_DEC_INBAND_CMD_TYPE_EOS);
    cmd.header.size = htonl(sizeof(AUDIO_DEC_EOS));
    cmd.EOSID = 0;

    cmd.wPtr = htonl(dpcm->decInRing_LE[0].writePtr);
    //TRACE_CODE("[test]write cmd type %d\n", AUDIO_DEC_INBAND_CMD_TYPE_EOS);
    //snd_realtek_hw_ring_write(((unsigned int)dpcm->decInbandRing - (unsigned int)dpcm + dpcm->phy_addr), &cmd, sizeof(AUDIO_DEC_EOS));
    snd_realtek_hw_ring_write((unsigned int)&dpcm->decInbandRing, &cmd, sizeof(AUDIO_DEC_EOS), (unsigned int)dpcm - (unsigned int)dpcm->phy_addr);
    return 0;
}

// set AO volume
int RPC_TOAGENT_SET_VOLUME(int volume) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
    
    AUDIO_CONFIG_COMMAND *config;
    unsigned int *res;
    HRESULT ret;
    dma_addr_t dat;
    void *addr = 0;
    unsigned int offset;

    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);

    if(!addr) {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }

    //config = (AUDIO_CONFIG_COMMAND  *) (unsigned int)page_address(page);
    config = addr;
    config->msgID = htonl(AUDIO_CONFIG_CMD_VOLUME);
    config->value[0] = htonl(31- volume);

    res = (unsigned int *) ((unsigned int) (config + sizeof(AUDIO_CONFIG_COMMAND)+8) & 0xFFFFFFFC); 
    offset = (unsigned int)res - (unsigned int)config;

    // set gpAudio->ao_volume_level(from Audio FW)
    //if (send_rpc_command(RPC_AUDIO, ENUM_KERNEL_RPC_VOLUME_CONTROL, (unsigned int) config,(unsigned int) res, &ret)) {
    if(send_rpc_command(RPC_AUDIO, 
        ENUM_KERNEL_RPC_VOLUME_CONTROL, 
        CONVERT_FOR_AVCPU(dat),
        CONVERT_FOR_AVCPU(dat + offset), 
        &ret)) {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        ret = -1;
        goto exit;
    }
    
    if (ret != S_OK) {
        ALSA_WARNING("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        ret = -1;
        goto exit;
    }

    ret = 0;

    //TRACE_CODE("[%s %s %d] success\n", __FILE__, __FUNCTION__, __LINE__);
exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);
    
    return ret;
}

// get AO volume
int RPC_TOAGENT_GET_VOLUME(snd_card_RTK_pcm_t *mars) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    int volume;
    RPC_GET_VOLUME_T *config;
    dma_addr_t dat;
    void *addr = 0;
    
    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);
    if(!addr) {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }
    
    //config = (RPC_GET_VOLUME_T  *) (unsigned int)page_address(page);
    config = addr;
    config->param.instanceID = htonl(mars->AOAgentID);
    config->param.type = htonl(ENUM_PRIVATEINFO_AUDIO_GET_MUTE_N_VOLUME);

//    flush_dcache_page(page);

    //if (send_rpc_command(RPC_AUDIO, ENUM_KERNEL_RPC_GET_MUTE_N_VOLUME , (unsigned int) &(config->param),(unsigned int) &(config->res), &(config->ret))) {
    if(send_rpc_command(RPC_AUDIO, 
        ENUM_KERNEL_RPC_GET_MUTE_N_VOLUME ,
        CONVERT_FOR_AVCPU(dat + sizeof(config->res) + sizeof(config->ret)),
        CONVERT_FOR_AVCPU(dat),
        &(config->ret))) {
        ALSA_WARNING("[fail %s %d]\n", __FUNCTION__, __LINE__);
        volume = -1;
        goto exit;
    }

    if(config->ret != S_OK) {
        ALSA_WARNING("[fail %s %d]\n", __FUNCTION__, __LINE__);
        volume = -1;
        goto exit;
    }

    // get gpAudio->ao_volume_level (from audio FW)
    volume = config->param.privateInfo[1];
exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);
    
    return volume;
}

int RPC_TOAGENT_CREATE_AI_AGENT(snd_card_RTK_capture_pcm_t *dpcm) 
{
    TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    RPC_CREATE_AO_AGENT_T *rpc = NULL;
    int ret = -1;
    dma_addr_t dat;
    void *addr = 0;

    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);
    if (!addr) 
    {
        ALSA_WARNING("[ALSA %s %d fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }

    rpc = addr;
    rpc->info.instanceID = htonl(-1);
    rpc->info.type = htonl(AUDIO_IN);

    if (send_rpc_command(RPC_AUDIO, 
        ENUM_KERNEL_RPC_CREATE_AGENT, 
        CONVERT_FOR_AVCPU(dat),
        CONVERT_FOR_AVCPU(dat + sizeof(rpc->info)),
        &rpc->ret))
    {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }
    
    if (ntohl(rpc->retval.result) != S_OK || rpc->ret != S_OK)  
    {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }

    dpcm->AIAgentID = ntohl(rpc->retval.data);
    // success
    ret = 0;
exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);
    return ret;
}

int RPC_TOAGENT_CONFIGURE_AI_HW(snd_pcm_runtime_t *runtime)
{
    TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
    AUDIO_CONFIG_ADC *rpc = NULL;
    AUDIO_ADC_CONFIG *pConfig = NULL;
    HRESULT *rpc_arg;
    int ret = -1;
    HRESULT RPC_ret;
    dma_addr_t dat;
    void *addr = 0;
    unsigned int offset;
    
    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);

    if(!addr)
    {
        ALSA_WARNING("[ALSA %s %d fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }
    rpc = addr;
    rpc_arg = (HRESULT *)((unsigned int)(rpc + sizeof(AUDIO_CONFIG_ADC) + 8) & 0xFFFFFFFC);

    offset = (unsigned int)rpc_arg - (unsigned int)rpc;

    pConfig = &rpc->adcConfig;
    rpc->instanceID = htonl(dpcm->AIAgentID);
    pConfig->audioGeneralConfig.interface_en = 1;
    pConfig->audioGeneralConfig.channel_in = 0x3;
    pConfig->sampleInfo.sampling_rate = htonl(runtime->rate);
    pConfig->sampleInfo.PCM_bitnum = htonl(24);

    if (send_rpc_command(RPC_AUDIO, 
        ENUM_KERNEL_RPC_ADC0_CONFIG,
        CONVERT_FOR_AVCPU(dat),//rpc address
        CONVERT_FOR_AVCPU(dat + offset), //rpc_arg address
        &RPC_ret)) 
    {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n",__FUNCTION__, __LINE__);
        goto exit;
    }
    
    ret = 0;
exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);
    return ret;
}

int RPC_TOAGENT_AI_CONNECT_ALSA(snd_card_RTK_capture_pcm_t *dpcm)
{
    TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    AUDIO_RPC_PRIVATEINFO_PARAMETERS *cmd;
    AUDIO_RPC_PRIVATEINFO_RETURNVAL*res;
    HRESULT RPC_ret;
    int ret = -1;
    dma_addr_t dat;
    void *addr = 0;
    unsigned int offset;

    addr = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);

    if(!addr)
    {
        ALSA_WARNING("[ALSA malloc fail %s]\n", __FUNCTION__);
        goto exit;
    }

    cmd = addr;
    res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned int)(cmd + sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS)+8) & 0xFFFFFFFC);
    offset = (unsigned int)res - (unsigned int)cmd;

    memset(cmd, 0, sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    cmd->instanceID = htonl(dpcm->AIAgentID);
    cmd->type = htonl(ENUM_PRIVATEINFO_AUDIO_AI_CONNECT_ALSA);
    cmd->privateInfo[0] = htonl(dpcm->nAIFormat);

    if (send_rpc_command(RPC_AUDIO,
        ENUM_KERNEL_RPC_PRIVATEINFO,
        CONVERT_FOR_AVCPU(dat),
        CONVERT_FOR_AVCPU(dat + offset),
        &RPC_ret))
    {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }

    if (RPC_ret != S_OK)
    {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit; 
    }

    ret = 0;
exit:
    if(addr)
        dma_free_coherent(NULL, 4096, addr, dat);
    return ret;
}

int RPC_DESTROY_AUDIO_FLOW(int pid)
{
    AUDIO_RPC_PRIVATEINFO_PARAMETERS *cmd = NULL;
    AUDIO_RPC_PRIVATEINFO_RETURNVAL *res;
    HRESULT RPC_ret;
    int ret = -1;
    dma_addr_t dat;
    unsigned int offset;
    //ALSA_WARNING("[%s] PID = %d\n",__func__,pid);
    cmd = dma_alloc_coherent(NULL, 4096, &dat, GFP_KERNEL);
    res = (AUDIO_RPC_PRIVATEINFO_RETURNVAL *)((unsigned int)(cmd + sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS)+8) & 0xFFFFFFFC);
    offset = (unsigned int)res - (unsigned int)cmd;
    memset(cmd, 0, sizeof(AUDIO_RPC_PRIVATEINFO_PARAMETERS));
    cmd->instanceID = htonl(-1);
    cmd->type = htonl(ENUM_PRIVATEINFO_AUDIO_DO_SELF_DESTROY_FLOW);
    cmd->privateInfo[0] = htonl(pid);
    if(send_rpc_command(RPC_AUDIO,
                ENUM_KERNEL_RPC_PRIVATEINFO,
                CONVERT_FOR_AVCPU(dat),
                CONVERT_FOR_AVCPU(dat + offset),
                &RPC_ret)) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
    }

    if(RPC_ret != S_OK ) {
        ALSA_WARNING("[ALSA %s %d RPC fail]\n", __FUNCTION__, __LINE__);
        goto exit;
    }
exit:
    if (NULL != cmd)
        dma_free_coherent(NULL, 4096, cmd, dat);
    return ret;
}

#endif //USE_ION_AUDIO_HEAP
