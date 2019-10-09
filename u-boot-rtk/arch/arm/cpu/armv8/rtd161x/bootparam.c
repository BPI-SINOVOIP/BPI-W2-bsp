#include <linux/ctype.h>
#include <linux/string.h>
#include <linux/stddef.h>
#include <asm/arch/io.h>
#include <asm/arch/system.h>

#include <common.h>
#include <parse_h.h>
#include <asm/arch/bootparam.h>
#include <asm/arch/factorylib.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/rtkemmc.h>
#include <hdmitx.h>
#include <part.h>

#define DEBUG(msg,arg...)   do { printf("[%s %3d]:", __FILE__, __LINE__); printf(msg,##arg); } while(0)
//#define DEBUG(msg,arg...)

#define BOOT_PARAM_FILE_NAME	FACTORY_HEADER_FILE_NAME"000BootParam.h"
#define BOOT_PART_FILE_NAME		FACTORY_HEADER_FILE_NAME"layout.txt"
#define BOOT_TVSYSTEM_FILE_NAME		FACTORY_HEADER_FILE_NAME"video_rpc.bin"
#define BOOT_CHECKSUM_FILE_NAME		FACTORY_HEADER_FILE_NAME"edid_checksum.bin"
#define BOOT_TXFORMAT_FILE_NAME		FACTORY_HEADER_FILE_NAME"hdmitx_format.bin"

extern uchar boot_logo_enable;
extern uint custom_logo_src_width;
extern uint custom_logo_src_height;
extern uint custom_logo_dst_width;
extern uint custom_logo_dst_height;

#ifdef CONFIG_SYS_AUTO_DETECT
extern uchar checksum_128;
extern uchar checksum_256;
#endif
/************************************************************************
**
** get boot info in factory area of flash
**
*************************************************************************/
void get_bootparam(void)
{
	char *dst_addr;
	char *retAddr;
	int dst_length;
	uint retVal;

	//display_evaluate_time("get_bootparam-0");

	if (factory_read(BOOT_PARAM_FILE_NAME, &dst_addr, &dst_length)) {
		printf("------------can't find %s\n", BOOT_PARAM_FILE_NAME);	
	}
	else {
		printf("------------%s found\n", BOOT_PARAM_FILE_NAME);
		
		/****** for logo display ******/	
		//source
		if (parse_h("BOOT_LOGO_ENABLE", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			boot_logo_enable = retVal;
			debug("BOOT_LOGO_ENABLE=%d\n", retVal);
		}
		else {
			DEBUG("can't find boot_logo_enable\n");
		}
				
		if (parse_h("CUSTOM_LOGO_SRC_WIDTH", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			custom_logo_src_width = retVal;
			debug("CUSTOM_LOGO_SRC_WIDTH=%d\n", retVal);
		}
		else {
			DEBUG("can't find custom_logo_src_width\n");
		}
		
		if (parse_h("CUSTOM_LOGO_SRC_HEIGHT", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			custom_logo_src_height = retVal;
			debug("CUSTOM_LOGO_SRC_HEIGHT=%d\n", retVal);
		}
		else {
			DEBUG("can't find custom_logo_src_height\n");
		}
		
		//destination
		if (parse_h("CUSTOM_LOGO_DST_WIDTH", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			custom_logo_dst_width = retVal;
			debug("CUSTOM_LOGO_DST_WIDTH=%d\n", retVal);
		}
		else {
			DEBUG("can't find custom_logo_dst_width\n");
		}
		
		if (parse_h("CUSTOM_LOGO_DST_HEIGHT", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			custom_logo_dst_height = retVal;
			debug("CUSTOM_LOGO_DST_HEIGHT=%d\n", retVal);
		}
		else {
			DEBUG("can't find custom_logo_dst_height\n");
		}
		/****** for logo display ******/
	}
	if(boot_logo_enable)
		printf("[logo]src w/h=%d/%d dst w/h=%d/%d\n",custom_logo_src_width ,custom_logo_src_height
													,custom_logo_dst_width ,custom_logo_dst_height);
	//display_evaluate_time("get_bootparam-1");
}

int read_param_one_step(struct ONE_STEP_INFO *param)
{
	int ret;
	unsigned char buffer[EMMC_BLOCK_SIZE];
	block_dev_desc_t *dev_desc;
	disk_partition_t info;

	dev_desc = get_dev("mmc", 0);
	ret = get_partition_info_efi_by_name(dev_desc, "param", &info);
	if (ret == 0) {
		printf("------------param partition found\n");
#ifdef CONFIG_RTK_MMC
		rtk_eMMC_read(info.start, EMMC_BLOCK_SIZE, (unsigned int *)buffer);

		memcpy(param, buffer, sizeof(struct ONE_STEP_INFO));

		if (param->mHeaderFormat[0] != 'F' || param->mHeaderFormat[1] != 'M' ||
			param->mHeaderFormat[2] != 'T')
			ret = -1;/* Invalid ONE_STEP_INFO */
#else
		printf("%s: No emmc driver support\n", __func__);
		ret = -1;
#endif
	}

	return ret;
}

/************************************************************************
**
** get video_rpc.bin in factory area of flash
**
*************************************************************************/
#ifdef CONFIG_SYS_AUTO_DETECT
#define ONE_STEP_NONE	0
#define ONE_STEP_RPC	1
#define ONE_SETP_FORMAT	2
#define ONE_SETP_FORMAT_GPT	3

extern struct hdmi_format_setting hdmi_format;

int get_one_step_info(void)
{
	int ret_val;
	int one_setp_version;
	int dst_length;
	int dst_length_chk;
	char *dst_addr;
	char *dst_addr_chk;
	struct ONE_STEP_INFO param;

	one_setp_version = ONE_STEP_NONE;

	/* printf("%s:\n", __FUNCTION__); */

#ifdef CONFIG_RTK_EMMC_TRADITIONAL_MODE
/*
 * ONE_SETP_FORMAT_GPT - Read one step info from GPT 'param' partition
 * Need turn on CONFIG_PARTITION_UUIDS/CONFIG_CMD_GPT/
 * CONFIG_RTK_EMMC_TRADITIONAL_MODE
 */
	ret_val = read_param_one_step(&param);
	if (ret_val == 0) {
		printf("------------GPT param ONE_STEP_INFO found\n");
		one_setp_version = ONE_SETP_FORMAT_GPT;
		goto read_checksum;
	}
#endif

	ret_val = factory_read(BOOT_TXFORMAT_FILE_NAME, &dst_addr, &dst_length);
	if (ret_val == 0) {
		printf("------------%s found\n", BOOT_TXFORMAT_FILE_NAME);
		one_setp_version = ONE_SETP_FORMAT;
		goto read_checksum;
	} else {
		printf("------------can't find %s\n", BOOT_TXFORMAT_FILE_NAME);
	}

	ret_val = factory_read(BOOT_TVSYSTEM_FILE_NAME, &dst_addr, &dst_length);
	if (ret_val == 0) {
		printf("------------%s found\n", BOOT_TVSYSTEM_FILE_NAME);
		one_setp_version = ONE_STEP_RPC;
		goto read_checksum;
	} else {
		printf("------------can't find %s\n", BOOT_TVSYSTEM_FILE_NAME);
		goto exit;
	}

read_checksum:
	/* set magic pattern in first word */
	rtd_outl(VO_RESOLUTION, 0xee0bdec0);

	switch (one_setp_version) {
	case ONE_SETP_FORMAT:
		memcpy(&hdmi_format, dst_addr ,dst_length);
		break;
	case ONE_STEP_RPC:
		memcpy((void *)(uintptr_t)VO_RESOLUTION+4, dst_addr ,dst_length);
		flush_cache(VO_RESOLUTION, 4+ dst_length);
		break;
	case ONE_SETP_FORMAT_GPT:
		memcpy(&hdmi_format, &param.mSetting, sizeof(hdmi_format));
		if (param.mHeaderEDIDCheckSum[0] == 'E' && param.mHeaderEDIDCheckSum[1] == 'D' &&
			param.mHeaderEDIDCheckSum[2] == 'I' && param.mHeaderEDIDCheckSum[3] == 'D') {
			checksum_128 = param.mChecksum[0];
			checksum_256 = param.mChecksum[1];
		} else {
			printf("------------invalid mHeaderEDIDCheckSum\n");
			one_setp_version = ONE_STEP_NONE;
		}
		/* Skip read factory checksum */
		goto check_checksum;
		break;
	default:
		printf("------------Unknow one_setp_version\n");
		one_setp_version = ONE_STEP_NONE;
		goto exit;
	}

	/* Read checksum file from factory */
	ret_val = factory_read(BOOT_CHECKSUM_FILE_NAME, &dst_addr_chk, &dst_length_chk);
	if (ret_val != 0) {
		printf("------------can't find %s\n", BOOT_CHECKSUM_FILE_NAME);
		one_setp_version = ONE_STEP_NONE;
		goto exit;
	}

	memcpy(&checksum_128, dst_addr_chk, sizeof(unsigned char));
	memcpy(&checksum_256, dst_addr_chk+sizeof(unsigned char), sizeof(unsigned char));

check_checksum:
	if ((checksum_128 == 0) && (checksum_256 == 0)) {
		printf("------------invalid checksum\n");
		one_setp_version = ONE_STEP_NONE;
	}

exit:
	return one_setp_version;
}
#endif

