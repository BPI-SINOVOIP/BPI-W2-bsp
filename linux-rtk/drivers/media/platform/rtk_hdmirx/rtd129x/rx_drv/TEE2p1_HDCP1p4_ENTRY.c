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

struct tee_context *ctx_HDCP1p4;
struct tee_ioctl_open_session_arg arg_HDCP1p4;
struct tee_param  param_HDCP1p4[4];

extern int TEE2p1_Flag;

void HDCP1p4_ta_init(void)
{
	TEEC_UUID test_id =	TA_HDCP1p4RX_UUID;

	ctx_HDCP1p4 = tee_client_open_context(NULL, NULL, NULL, NULL);

	memcpy(&arg_HDCP1p4.uuid, &test_id, sizeof(test_id));

	arg_HDCP1p4.clnt_login = TEEC_LOGIN_PUBLIC;
	arg_HDCP1p4.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	param_HDCP1p4[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	param_HDCP1p4[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	param_HDCP1p4[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	param_HDCP1p4[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;

	tee_client_open_session(ctx_HDCP1p4, &arg_HDCP1p4, &param_HDCP1p4);

}


int HDCP1p4_ta_deinit(void)
{
	int result;

	result = tee_client_close_session(ctx_HDCP1p4, arg_HDCP1p4.session);

	return result;
}


unsigned char  T_KEY[5];
int  CA_hdcp1p4_RX_SET_KEY(void)
{
	struct tee_param *invoke_param = NULL;
	struct tee_ioctl_invoke_arg arg_I;
	struct tee_shm *shm;

	arg_I.func = TA_HDCP1p4_KEY;
	arg_I.session = arg_HDCP1p4.session;
	arg_I.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	invoke_param = kcalloc(TEEC_CONFIG_PAYLOAD_REF_COUNT,
		sizeof(struct tee_param), GFP_KERNEL);

	if (!invoke_param)
		return -ENOMEM;

	shm = tee_shm_alloc(ctx_HDCP1p4, 1, TEE_SHM_MAPPED | TEE_SHM_DMA_BUF);
	if (IS_ERR(shm))
		return PTR_ERR(shm);

	invoke_param[1].u.memref.size = 1;
	invoke_param[1].u.memref.shm = shm;

	memcpy(invoke_param[1].u.memref.shm->kaddr, T_KEY, 1);

	invoke_param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT;
	invoke_param[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;

	tee_client_invoke_func(ctx_HDCP1p4, &arg_I, invoke_param);

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

