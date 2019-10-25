/*
 * TEE2p1_HDCP1p4_ENTRY.c - RTK hdmi rx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/idr.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/tee_drv.h>
#include <linux/uaccess.h>

#include "tee_private.h"
#include "tee_client_api.h"

#define TA_HDCP1p4RX_UUID {0x0df2fadb, 0xb2e0, 0x4345, \
		{0xa4, 0x91, 0xef, 0x0a, 0xcf, 0xae, 0xd1, 0x84} }
#define TA_HELLO_WORLD_CMD_INC_VALUE 0xff
#define TA_HDCP1p4_KEY 0x0e

struct tee_context *ctx_hdcprx;
struct tee_ioctl_open_session_arg arg_hdcprx;
struct tee_param  param_HDCP1p4[4];

extern int TEE2p1_Flag;

static void uuid_to_octets(uint8_t d[TEE_IOCTL_UUID_LEN], const TEEC_UUID *s)
{
	d[0] = s->timeLow >> 24;
	d[1] = s->timeLow >> 16;
	d[2] = s->timeLow >> 8;
	d[3] = s->timeLow;
	d[4] = s->timeMid >> 8;
	d[5] = s->timeMid;
	d[6] = s->timeHiAndVersion >> 8;
	d[7] = s->timeHiAndVersion;
	memcpy(d + 8, s->clockSeqAndNode, sizeof(s->clockSeqAndNode));
}

static int hdcp_optee_match(struct tee_ioctl_version_data *data,
	const void *vers)
{
	return 1;
}

void HDCP1p4_ta_init(void)
{
	struct tee_ioctl_version_data vers = {
		.impl_id = TEE_OPTEE_CAP_TZ,
		.impl_caps = TEE_IMPL_ID_OPTEE,
		.gen_caps = TEE_GEN_CAP_GP,
	};

	TEEC_UUID ta_id = TA_HDCP1p4RX_UUID;

	ctx_hdcprx = tee_client_open_context(NULL, hdcp_optee_match, NULL, &vers);

	if (IS_ERR(ctx_hdcprx))
		pr_err("[HDCP RX] get tee context fail\n");

	uuid_to_octets((uint8_t *)&arg_hdcprx.uuid, &ta_id);

	arg_hdcprx.clnt_login = TEEC_LOGIN_PUBLIC;
	arg_hdcprx.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	param_HDCP1p4[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	param_HDCP1p4[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	param_HDCP1p4[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	param_HDCP1p4[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;

	tee_client_open_session(ctx_hdcprx, &arg_hdcprx, param_HDCP1p4);

}


int HDCP1p4_ta_deinit(void)
{
	int result;

	if (ctx_hdcprx == NULL)
		return 0;

	result = tee_client_close_session(ctx_hdcprx, arg_hdcprx.session);
	tee_client_close_context(ctx_hdcprx);
	ctx_hdcprx = NULL;

	return result;
}


unsigned char  T_KEY[5];
int  CA_hdcp1p4_RX_SET_KEY(void)
{
	struct tee_param *invoke_param = NULL;
	struct tee_ioctl_invoke_arg arg_I;
	struct tee_shm *shm;

	arg_I.func = TA_HDCP1p4_KEY;
	arg_I.session = arg_hdcprx.session;
	arg_I.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	invoke_param = kcalloc(TEEC_CONFIG_PAYLOAD_REF_COUNT,
		sizeof(struct tee_param), GFP_KERNEL);

	if (!invoke_param)
		return -ENOMEM;

	shm = tee_shm_alloc(ctx_hdcprx, 1, TEE_SHM_MAPPED | TEE_SHM_DMA_BUF);
	if (IS_ERR(shm))
		return PTR_ERR(shm);

	invoke_param[1].u.memref.size = 1;
	invoke_param[1].u.memref.shm = shm;

	memcpy(invoke_param[1].u.memref.shm->kaddr, T_KEY, 1);

	invoke_param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT;
	invoke_param[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;

	tee_client_invoke_func(ctx_hdcprx, &arg_I, invoke_param);

	return 0;
}

void CA_hdcp1p4_load(void)
{
	if (TEE2p1_Flag == 0)
		return;

	HDCP1p4_ta_init();
	CA_hdcp1p4_RX_SET_KEY();
	HDCP1p4_ta_deinit();

}

