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

#define TA_HDCPTX14_UUID { 0x87ef28e8, 0xf581, 0x4e3d, \
		{ 0xb2, 0xb2, 0xd7, 0xe3, 0xd4, 0x8b, 0x23, 0x21} }

#define HDCP14_AN_CMD_LEN		8
#define HDCP14_BKSV_CMD_LEN		5
#define HDCP_AKSV_SIZE			5

#define HDCP14_PK_SIZE	280

#define MAX_SHA_DATA_SIZE       645
#define MAX_SHA_VPRIME_SIZE     20

#define TEE_IOCTL_UUID_LEN		16

enum HDCP14_CMD_FOR_TA {
	TA_TEE_HDCP14_GenAn			= 0x1,
	TA_TEE_HDCP14_WriteBKSV		= 0x2,
	TA_TEE_HDCP14_SetRepeaterBitInTx	= 0x3,
	TA_TEE_HDCP14_CheckRepeaterBitInTx	= 0x4,
	TA_TEE_HDCP14_SetEnc		= 0x5,
	TA_TEE_HDCP14_SetWinderWin	= 0x6,
	TA_TEE_HDCP14_EnRi			= 0x7,
	TA_TEE_HDCP14_SetAVMute		= 0x8,
	TA_TEE_HDCP14_SHAAppend		= 0x9,
	TA_TEE_HDCP14_ComputeV		= 0xa,
	TA_TEE_HDCP14_VerifyV		= 0xb,
	TA_TEE_HDCP14_CheckR0		= 0xc,
	TA_TEE_HDCP14_GetAKSV		= 0xd,
	TA_TEE_HDCP14_GetCtrlState	= 0xe,
};

enum hdcp_repeater {
	HDCP_RECEIVER = 0,
	HDCP_REPEATER = 1
};

enum encryption_state {
	HDCP_ENC_OFF = 0x0,
	HDCP_ENC_ON  = 0x1
};

enum ri_state {
	HDCP_RI_OFF = 0x0,
	HDCP_RI_ON  = 0x1
};

enum av_mute {
	AV_MUTE_SET = 0x01,
	AV_MUTE_CLEAR = 0x10
};

struct hdcp_sha_in {
	uint8_t data[MAX_SHA_DATA_SIZE];
	uint32_t byte_counter;
	uint8_t vprime[MAX_SHA_VPRIME_SIZE];
};

struct tee_ioctl_open_session_arg arg;
struct tee_param  param[4];
struct tee_context *ctx;

int ta_hdcp_lib_get_aksv(uint8_t *aksv);

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

void ta_hdcp14_init(void)
{
	int ret;
	struct tee_ioctl_version_data vers = {
		.impl_id = TEE_OPTEE_CAP_TZ,
		.impl_caps = TEE_IMPL_ID_OPTEE,
		.gen_caps = TEE_GEN_CAP_GP,
	};

	pr_err("[TEE_HDCPTX] %s\n", __func__);

	const TEEC_UUID test_id = TA_HDCPTX14_UUID;

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

void ta_hdcp14_deinit(void)
{
	pr_err("[TEE_HDCPTX] %s\n", __func__);

	if (ctx == NULL)
		return;

	tee_client_close_session(ctx, arg.session);
	tee_client_close_context(ctx);
	ctx = NULL;
}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_generate_an (Generate An using HDCP HW)
 *-----------------------------------------------------------------------------
 */
int ta_hdcp_lib_generate_an(uint8_t *an)
{
	struct tee_param *invoke_param = NULL;
	struct tee_ioctl_invoke_arg arg_I;

	struct tee_shm *shm;

	arg_I.func = TA_TEE_HDCP14_GenAn;
	arg_I.session = arg.session;
	arg_I.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	invoke_param = kcalloc(TEEC_CONFIG_PAYLOAD_REF_COUNT,
		sizeof(struct tee_param), GFP_KERNEL);

	if (!invoke_param)
		return -ENOMEM;

	shm = tee_shm_alloc(ctx, HDCP14_AN_CMD_LEN, TEE_SHM_MAPPED | TEE_SHM_DMA_BUF);
	if (IS_ERR(shm))
		return PTR_ERR(shm);

#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   ta_hdcp_lib_generate_an.\n");
#endif
	invoke_param[0].u.memref.size = HDCP14_AN_CMD_LEN;
	invoke_param[0].u.memref.shm = shm;

	memcpy(invoke_param[0].u.memref.shm->kaddr, an, HDCP14_AN_CMD_LEN);

	invoke_param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT;
	invoke_param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;

	tee_client_invoke_func(ctx, &arg_I, invoke_param);

	memcpy(an, invoke_param[0].u.memref.shm->kaddr, HDCP14_AN_CMD_LEN);

	tee_shm_free(shm);
	kfree(invoke_param);

	return 0;/* HDCP_OK */
}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_get_aksv from RPMB
 *-----------------------------------------------------------------------------
 */
int ta_hdcp_lib_get_aksv(uint8_t *aksv)
{
	struct tee_param *invoke_param = NULL;
	struct tee_ioctl_invoke_arg arg_I;
	unsigned int check_val = 0;
	struct tee_shm *shm;

	arg_I.func = TA_TEE_HDCP14_GetAKSV;
	arg_I.session = arg.session;
	arg_I.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	invoke_param = kcalloc(TEEC_CONFIG_PAYLOAD_REF_COUNT,
		sizeof(struct tee_param), GFP_KERNEL);

	if (!invoke_param)
		return -ENOMEM;

	shm = tee_shm_alloc(ctx, HDCP_AKSV_SIZE, TEE_SHM_MAPPED | TEE_SHM_DMA_BUF);
	if (IS_ERR(shm))
		return PTR_ERR(shm);
#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   ta_hdcp_lib_get_aksv.\n");
#endif
	invoke_param[0].u.memref.size = HDCP_AKSV_SIZE;
	invoke_param[0].u.memref.shm = shm;

	memcpy(invoke_param[0].u.memref.shm->kaddr, aksv, HDCP_AKSV_SIZE);

	invoke_param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT;
	invoke_param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT;
	invoke_param[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;

	tee_client_invoke_func(ctx, &arg_I, invoke_param);

	check_val = invoke_param[1].u.value.a;
	memcpy(aksv, invoke_param[0].u.memref.shm->kaddr, HDCP_AKSV_SIZE);

	tee_shm_free(shm);
	kfree(invoke_param);
	/* pr_err("[TEE_KERNEL_DBG]   ta_hdcp_lib_get_aksv: %d\n", check_val); */
	return check_val;
}

int ta_hdcp_lib_write_bksv(uint8_t *ksv_data)
{
	struct tee_param *invoke_param = NULL;
	struct tee_ioctl_invoke_arg arg_I;

	struct tee_shm *shm;
	struct tee_shm *shm1;

	arg_I.func = TA_TEE_HDCP14_WriteBKSV;
	arg_I.session = arg.session;
	arg_I.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	invoke_param = kcalloc(TEEC_CONFIG_PAYLOAD_REF_COUNT,
		sizeof(struct tee_param), GFP_KERNEL);

	if (!invoke_param)
		return -ENOMEM;

	shm = tee_shm_alloc(ctx, HDCP14_BKSV_CMD_LEN, TEE_SHM_MAPPED | TEE_SHM_DMA_BUF);
	if (IS_ERR(shm))
		return PTR_ERR(shm);

#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   ta_hdcp_lib_write_bksv.\n");
#endif
	invoke_param[0].u.memref.size = HDCP14_BKSV_CMD_LEN;
	invoke_param[0].u.memref.shm = shm;

	memcpy(invoke_param[0].u.memref.shm->kaddr, ksv_data, HDCP14_BKSV_CMD_LEN);

	shm1 = tee_shm_alloc(ctx, HDCP14_PK_SIZE, TEE_SHM_MAPPED | TEE_SHM_DMA_BUF);
	if (IS_ERR(shm1))
		return PTR_ERR(shm1);
#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   ta_hdcp_lib_write_bksv pk.\n");
#endif
	invoke_param[1].u.memref.size = HDCP14_PK_SIZE;
	invoke_param[1].u.memref.shm = shm1;

	invoke_param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT;
	invoke_param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;

	tee_client_invoke_func(ctx, &arg_I, invoke_param);

	memcpy(ksv_data, invoke_param[0].u.memref.shm->kaddr, HDCP14_BKSV_CMD_LEN);

	tee_shm_free(shm);
	tee_shm_free(shm1);
	kfree(invoke_param);

	return 0;/* HDCP_OK */
}

void ta_hdcp_lib_set_repeater_bit_in_tx(enum hdcp_repeater rx_mode)
{
	struct tee_param *invoke_param = NULL;
	struct tee_ioctl_invoke_arg arg_I;

	arg_I.func = TA_TEE_HDCP14_SetRepeaterBitInTx;
	arg_I.session = arg.session;
	arg_I.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	invoke_param = kcalloc(TEEC_CONFIG_PAYLOAD_REF_COUNT,
		sizeof(struct tee_param), GFP_KERNEL);

	if (!invoke_param)
		return;

#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   ta_hdcp_lib_set_repeater_bit_in_tx.\n");
#endif
	invoke_param[0].u.value.a = rx_mode;

	invoke_param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT;
	invoke_param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;

	tee_client_invoke_func(ctx, &arg_I, invoke_param);

	kfree(invoke_param);
}

int ta_hdcp_lib_check_repeater_bit_in_tx(void)
{
	struct tee_param *invoke_param = NULL;
	struct tee_ioctl_invoke_arg arg_I;
	unsigned int check_val = 0;

	arg_I.func = TA_TEE_HDCP14_CheckRepeaterBitInTx;
	arg_I.session = arg.session;
	arg_I.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	invoke_param = kcalloc(TEEC_CONFIG_PAYLOAD_REF_COUNT,
		sizeof(struct tee_param), GFP_KERNEL);

	if (!invoke_param)
		return -ENOMEM;

#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   ta_hdcp_lib_check_repeater_bit_in_tx.\n");
#endif
	invoke_param[0].u.value.a = 0;

	invoke_param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT;
	invoke_param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;

	tee_client_invoke_func(ctx, &arg_I, invoke_param);
	check_val = invoke_param[0].u.value.a;

	kfree(invoke_param);

#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   ta_hdcp_lib_check_repeater_bit_in_tx: %d\n",
		check_val);
#endif

	return check_val;
}

void ta_hdcp_lib_set_encryption(enum encryption_state enc_state)
{
	struct tee_param *invoke_param = NULL;
	struct tee_ioctl_invoke_arg arg_I;

	arg_I.func = TA_TEE_HDCP14_SetEnc;
	arg_I.session = arg.session;
	arg_I.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	invoke_param = kcalloc(TEEC_CONFIG_PAYLOAD_REF_COUNT,
		sizeof(struct tee_param), GFP_KERNEL);

	if (!invoke_param)
		return;

#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   ta_hdcp_lib_set_encryption.\n");
#endif
	invoke_param[0].u.value.a = enc_state;

	invoke_param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT;
	invoke_param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;

	tee_client_invoke_func(ctx, &arg_I, invoke_param);

	kfree(invoke_param);
}

void ta_hdcp_lib_set_wider_window(void)
{
	struct tee_param *invoke_param = NULL;
	struct tee_ioctl_invoke_arg arg_I;

	arg_I.func = TA_TEE_HDCP14_SetWinderWin;
	arg_I.session = arg.session;
	arg_I.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	invoke_param = kcalloc(TEEC_CONFIG_PAYLOAD_REF_COUNT,
		sizeof(struct tee_param), GFP_KERNEL);

	if (!invoke_param)
		return;
#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   ta_hdcp_lib_set_wider_window.\n");
#endif
	invoke_param[0].u.value.a = 1;

	invoke_param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT;
	invoke_param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;

	tee_client_invoke_func(ctx, &arg_I, invoke_param);

	kfree(invoke_param);
}

void ta_hdcp_lib_set_ri(enum ri_state ri_state)
{
	struct tee_param *invoke_param = NULL;
	struct tee_ioctl_invoke_arg arg_I;

	arg_I.func = TA_TEE_HDCP14_EnRi;
	arg_I.session = arg.session;
	arg_I.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	invoke_param = kcalloc(TEEC_CONFIG_PAYLOAD_REF_COUNT,
		sizeof(struct tee_param), GFP_KERNEL);

	if (!invoke_param)
		return;

#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   ta_hdcp_lib_set_ri.\n");
#endif
	invoke_param[0].u.value.a = ri_state;

	invoke_param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT;
	invoke_param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;

	tee_client_invoke_func(ctx, &arg_I, invoke_param);

	kfree(invoke_param);
}

void ta_hdcp_lib_set_av_mute(enum av_mute av_mute_state)
{
	struct tee_param *invoke_param = NULL;
	struct tee_ioctl_invoke_arg arg_I;

	arg_I.func = TA_TEE_HDCP14_SetAVMute;
	arg_I.session = arg.session;
	arg_I.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	invoke_param = kcalloc(TEEC_CONFIG_PAYLOAD_REF_COUNT,
		sizeof(struct tee_param), GFP_KERNEL);

	if (!invoke_param)
		return;

#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   ta_hdcp_lib_set_av_mute.\n");
#endif
	invoke_param[0].u.value.a = av_mute_state;

	invoke_param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT;
	invoke_param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;

	tee_client_invoke_func(ctx, &arg_I, invoke_param);

	kfree(invoke_param);
}

int ta_hdcp_lib_SHA_append_bstatus_M0(struct hdcp_sha_in *sha, uint8_t *bstatus)
{
	struct tee_param *invoke_param = NULL;
	struct tee_ioctl_invoke_arg arg_I;

	struct tee_shm *shm;
	struct tee_shm *shm1;

	arg_I.func = TA_TEE_HDCP14_SHAAppend;
	arg_I.session = arg.session;
	arg_I.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	invoke_param = kcalloc(TEEC_CONFIG_PAYLOAD_REF_COUNT,
		sizeof(struct tee_param), GFP_KERNEL);

	if (!invoke_param)
		return -ENOMEM;

	shm = tee_shm_alloc(ctx, MAX_SHA_DATA_SIZE, TEE_SHM_MAPPED | TEE_SHM_DMA_BUF);
	if (IS_ERR(shm))
		return PTR_ERR(shm);

#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   ta_hdcp_lib_SHA_append.\n");
#endif
	invoke_param[0].u.memref.size = MAX_SHA_DATA_SIZE;
	invoke_param[0].u.memref.shm = shm;

	memcpy(invoke_param[0].u.memref.shm->kaddr, sha->data, MAX_SHA_DATA_SIZE);

	shm1 = tee_shm_alloc(ctx, 2, TEE_SHM_MAPPED | TEE_SHM_DMA_BUF);
	if (IS_ERR(shm1))
		return PTR_ERR(shm1);
#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   ta_hdcp_lib_SHA_append bstaus.\n");
#endif

	invoke_param[1].u.memref.size = 2;
	invoke_param[1].u.memref.shm = shm1;

	memcpy(invoke_param[1].u.memref.shm->kaddr, bstatus, 2);

	invoke_param[2].u.value.a = sha->byte_counter;

	invoke_param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT;
	invoke_param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT;
	invoke_param[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT;
	invoke_param[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   sha->byte_counter bef: %d\n",
		invoke_param[2].u.value.a);
#endif

	tee_client_invoke_func(ctx, &arg_I, invoke_param);

	sha->byte_counter = invoke_param[2].u.value.a;
	memcpy(sha->data, invoke_param[0].u.memref.shm->kaddr, MAX_SHA_DATA_SIZE);

#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   sha->byte_counter aft: %d\n",
		invoke_param[2].u.value.a);
#endif

	tee_shm_free(shm);
	tee_shm_free(shm1);
	kfree(invoke_param);

	return 0;/* HDCP_OK */
}

int ta_hdcp_lib_compute_V(struct hdcp_sha_in *sha)
{
	struct tee_param *invoke_param = NULL;
	struct tee_ioctl_invoke_arg arg_I;

	struct tee_shm *shm;

	int ret = 0;

	arg_I.func = TA_TEE_HDCP14_ComputeV;
	arg_I.session = arg.session;
	arg_I.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	invoke_param = kcalloc(TEEC_CONFIG_PAYLOAD_REF_COUNT,
		sizeof(struct tee_param), GFP_KERNEL);

	if (!invoke_param)
		return -ENOMEM;

	shm = tee_shm_alloc(ctx, MAX_SHA_DATA_SIZE, TEE_SHM_MAPPED | TEE_SHM_DMA_BUF);
	if (IS_ERR(shm))
		return PTR_ERR(shm);

#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   ta_hdcp_lib_compute_V.\n");
#endif
	invoke_param[0].u.memref.size = MAX_SHA_DATA_SIZE;
	invoke_param[0].u.memref.shm = shm;

	memcpy(invoke_param[0].u.memref.shm->kaddr, sha->data, MAX_SHA_DATA_SIZE);

	invoke_param[1].u.value.a = sha->byte_counter;
	invoke_param[1].u.value.b = 0;

	invoke_param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT;
	invoke_param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT;
	invoke_param[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;

#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   return invoke_param[1].u.value.b: %d\n",
		invoke_param[1].u.value.b);
#endif

	tee_client_invoke_func(ctx, &arg_I, invoke_param);

	sha->byte_counter = invoke_param[1].u.value.a;
	memcpy(sha->data, invoke_param[0].u.memref.shm->kaddr, MAX_SHA_DATA_SIZE);

	ret = invoke_param[1].u.value.b;

	tee_shm_free(shm);
	kfree(invoke_param);

	return ret;
}

int ta_hdcp_lib_verify_V(struct hdcp_sha_in *sha)
{
	struct tee_param *invoke_param = NULL;
	struct tee_ioctl_invoke_arg arg_I;

	struct tee_shm *shm;
	int ret = 0;

	arg_I.func = TA_TEE_HDCP14_VerifyV;
	arg_I.session = arg.session;
	arg_I.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	invoke_param = kcalloc(TEEC_CONFIG_PAYLOAD_REF_COUNT,
		sizeof(struct tee_param), GFP_KERNEL);

	if (!invoke_param)
		return -ENOMEM;

	shm = tee_shm_alloc(ctx, MAX_SHA_VPRIME_SIZE, TEE_SHM_MAPPED | TEE_SHM_DMA_BUF);
	if (IS_ERR(shm))
		return PTR_ERR(shm);

#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   ta_hdcp_lib_verify_V.\n");
#endif
	invoke_param[0].u.memref.size = MAX_SHA_DATA_SIZE;
	invoke_param[0].u.memref.shm = shm;

	memcpy(invoke_param[0].u.memref.shm->kaddr, sha->vprime, MAX_SHA_VPRIME_SIZE);

	invoke_param[1].u.value.a = 0;

	invoke_param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT;
	invoke_param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT;
	invoke_param[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;

	tee_client_invoke_func(ctx, &arg_I, invoke_param);

	memcpy(sha->vprime, invoke_param[0].u.memref.shm->kaddr, MAX_SHA_VPRIME_SIZE);

#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   return invoke_param[1].u.value.a: %d\n",
		invoke_param[1].u.value.a);
#endif
	ret = invoke_param[1].u.value.a;

	tee_shm_free(shm);
	kfree(invoke_param);

	return ret;
}

int ta_hdcp_get_ctrl_state(unsigned char select)
{
	struct tee_param *invoke_param = NULL;
	struct tee_ioctl_invoke_arg arg_I;
	int ret_val;

	arg_I.func = TA_TEE_HDCP14_GetCtrlState;
	arg_I.session = arg.session;
	arg_I.num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;

	invoke_param = kcalloc(TEEC_CONFIG_PAYLOAD_REF_COUNT,
		sizeof(struct tee_param), GFP_KERNEL);

	if (!invoke_param)
		return -ENOMEM;

#ifdef KERNEL_TA_DBG
	pr_err("[TEE_KERNEL_DBG]   ta_hdcp_get_ctrl_state.\n");
#endif

	invoke_param[0].attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT;
	invoke_param[1].attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT;
	invoke_param[2].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
	invoke_param[3].attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;

	tee_client_invoke_func(ctx, &arg_I, invoke_param);

	if (select == 0)
		ret_val = invoke_param[0].u.value.a;
	else
		ret_val = invoke_param[1].u.value.a;

	kfree(invoke_param);

	pr_err("[TEE_KERNEL_DBG]   ta_hdcp_get_ctrl_state: hdcp_en=%u hdcp22=%u\n",
			(unsigned int)invoke_param[0].u.value.a, (unsigned int)invoke_param[1].u.value.a);

	return ret_val;
}
