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

//#define TA_I2C_UUID { 0x7e67f57e, 0xab68, 0x4caf, \
//		{ 0xb1, 0x5e, 0xd1, 0xc9, 0xa4, 0xb3, 0x10, 0xc1} }

//#define TA_I2C_ENABLE_VALUE 0xff

#define TA_I2C_UUID \
{ 0x650b79a1, 0xa79a, 0x43ea, \
{ 0x91, 0x85, 0xf6, 0x67, 0x55, 0x65, 0x64, 0xa7 } }

#define TA_I2C_ENABLE_VALUE 0

static struct tee_ioctl_open_session_arg arg;
static struct tee_param  param[4];
static struct tee_context *ctx;

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

void ta_i2c_init(void)
{
	int ret;
	struct tee_ioctl_version_data vers = {
		.impl_id = TEE_OPTEE_CAP_TZ,
		.impl_caps = TEE_IMPL_ID_OPTEE,
		.gen_caps = TEE_GEN_CAP_GP,
	};

	pr_err("[TEE_KERNEL_DBG]   ta_i2c_init. teeos v2.5\n");

	const TEEC_UUID test_id = TA_I2C_UUID;

	ctx = tee_client_open_context(NULL, hdcp_optee_match, NULL, &vers);

	if (IS_ERR(ctx))
		pr_err("%s fail\n", __func__);

	uuid_to_octets((uint8_t *)&arg.uuid, &test_id);

	arg.clnt_login = TEEC_LOGIN_PUBLIC;
	arg.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	param[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	param[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;

#ifdef KERNEL_TA_DBG
	pr_err("UUID = %x ,%x ,%x\n", arg.uuid[0], arg.uuid[1], arg.uuid[2]);
	pr_err("Before session = %x\n", arg.session);
#endif
	ret = tee_client_open_session(ctx, &arg, param);
	if (ret)
		pr_err("%s open session fail\n", __func__);
	/* pr_err("After  session  = %x\n", arg.session); */
}

void ta_hdcp_lib_set_i2c_enable(unsigned int  i2c_enable_value)
{
	struct tee_param *invoke_param = NULL;
	struct tee_ioctl_invoke_arg arg_I;

	arg_I.func = TA_I2C_ENABLE_VALUE;
	arg_I.session = arg.session;
	arg_I.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	invoke_param = kcalloc(TEEC_CONFIG_PAYLOAD_REF_COUNT,
		sizeof(struct tee_param), GFP_KERNEL);

	if (!invoke_param)
		return;

#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   ta_hdcp_lib_set_i2c_enable.\n");
#endif
	invoke_param[0].u.value.a = i2c_enable_value;

	invoke_param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT;
	invoke_param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;

	tee_client_invoke_func(ctx, &arg_I, invoke_param);

	kfree(invoke_param);
}

