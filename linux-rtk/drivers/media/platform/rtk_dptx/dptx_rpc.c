/*
 *  dptx_rpc.c - RTK display port driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/dma-mapping.h>

#include "dptx_rpc.h"

#define CONVERT_FOR_AVCPU(x)		((unsigned int)(x) | 0xA0000000)

extern struct ion_device *rtk_phoenix_ion_device;

int RPC_TOAGENT_DPTX_QUERY_TV_System(struct ion_client *client,
			struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM *arg)
{
	struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM *i_rpc = NULL;
	struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM *o_rpc = NULL;
	int ret = -1;
	struct ion_handle *handle = NULL;
	unsigned int RPC_ret;
	size_t len;
	ion_phys_addr_t dat;
	unsigned int offset;

	handle = ion_alloc(client, 4096, 1024,
			RTK_PHOENIX_ION_HEAP_AUDIO_MASK, ION_FLAG_NONCACHED |
			ION_FLAG_SCPUACC |
			ION_FLAG_ACPUACC);
	if (IS_ERR(handle)) {
		pr_err("%s ion_alloc fail\n", __FUNCTION__);
		goto exit;
	}
	if(ion_phys(client, handle, &dat, &len) != 0) {
		pr_err("%s ion_phys fail\n", __FUNCTION__);
		goto exit;
	}
	i_rpc = ion_map_kernel(client, handle);
	offset = get_rpc_alignment_offset(
			sizeof(struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM));
	o_rpc = (struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM *)
				((unsigned long)i_rpc + offset);

	if (send_rpc_command(RPC_AUDIO,
			ENUM_VIDEO_KERNEL_RPC_QUERY_CONFIG_TV_SYSTEM,
			CONVERT_FOR_AVCPU(dat),
			CONVERT_FOR_AVCPU(dat + offset),
			&RPC_ret))
	{
		pr_err("%s RPC fail\n", __FUNCTION__);
		goto exit;
	}
	ret = 0;

	memcpy(arg, o_rpc, sizeof(struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM));

	arg->interfaceType = htonl(arg->interfaceType);
	arg->videoInfo.standard = htonl(arg->videoInfo.standard);
	arg->videoInfo.pedType  = htonl(arg->videoInfo.pedType);
	arg->videoInfo.dataInt0 = htonl(arg->videoInfo.dataInt0);
	arg->videoInfo.dataInt1 = htonl(arg->videoInfo.dataInt1);

	arg->dptxInfo.dptxMode  = htonl(arg->dptxInfo.dptxMode);
	arg->dptxInfo.audioSampleFreq = htonl(arg->dptxInfo.audioSampleFreq);
	arg->dptxInfo.dataInt0  = htonl(arg->dptxInfo.dataInt0);
	arg->dptxInfo.hdmi2p0_feature = htonl(arg->dptxInfo.hdmi2p0_feature);
	arg->dptxInfo.hdmi_off_mode = htonl(arg->dptxInfo.hdmi_off_mode);
	arg->dptxInfo.reserved3 = htonl(arg->dptxInfo.reserved3);
	arg->dptxInfo.reserved4 = htonl(arg->dptxInfo.reserved4);
exit:
	if(handle != NULL) {
		ion_unmap_kernel(client, handle);
		ion_free(client, handle);
	}
	return ret;
}

int RPC_TOAGENT_DPTX_Config_TV_System(struct ion_client *client,
			struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM *arg)
{
	struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM *rpc = NULL;
	unsigned int RPC_ret;
	ion_phys_addr_t dat;
	struct ion_handle *handle = NULL;
	size_t len;
	int ret = -1;

	handle = ion_alloc(client, 4096, 1024,
			RTK_PHOENIX_ION_HEAP_AUDIO_MASK,
			ION_FLAG_NONCACHED | ION_FLAG_SCPUACC |	ION_FLAG_ACPUACC);
	if (IS_ERR(handle)) {
		pr_err("%s ion_alloc fail\n", __FUNCTION__);
		goto exit;
	}
	if(ion_phys(client, handle, &dat, &len) != 0) {
		pr_err("%s ion_phys fail\n", __FUNCTION__);
		goto exit;
	}
	rpc = ion_map_kernel(client, handle);
	 
	memcpy(rpc, arg, sizeof(struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM));

	rpc->interfaceType = htonl(arg->interfaceType);
	rpc->videoInfo.standard = htonl(arg->videoInfo.standard);
	rpc->videoInfo.pedType  = htonl(arg->videoInfo.pedType);
	rpc->videoInfo.dataInt0 = htonl(arg->videoInfo.dataInt0);
	rpc->videoInfo.dataInt1 = htonl(arg->videoInfo.dataInt1);

	rpc->dptxInfo.dptxMode  = htonl(arg->dptxInfo.dptxMode);
	rpc->dptxInfo.audioSampleFreq = htonl(arg->dptxInfo.audioSampleFreq);
	rpc->dptxInfo.dataInt0  = htonl(arg->dptxInfo.dataInt0);
	rpc->dptxInfo.hdmi2p0_feature = htonl(arg->dptxInfo.hdmi2p0_feature);
	rpc->dptxInfo.hdmi_off_mode = htonl(arg->dptxInfo.hdmi_off_mode);
	rpc->dptxInfo.reserved3 = htonl(arg->dptxInfo.reserved3);
	rpc->dptxInfo.reserved4 = htonl(arg->dptxInfo.reserved4);

	if (send_rpc_command(RPC_AUDIO,
			ENUM_VIDEO_KERNEL_RPC_CONFIG_TV_SYSTEM,
			CONVERT_FOR_AVCPU(dat),
			CONVERT_FOR_AVCPU(dat + get_rpc_alignment_offset(sizeof(struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM))),
			&RPC_ret))
	{
		pr_err("%s RPC fail\n", __FUNCTION__);
		goto exit;
	}
	ret = 0;
exit:
	if(handle != NULL) {
		ion_unmap_kernel(client, handle);
		ion_free(client, handle);
	}
	return ret;
}
