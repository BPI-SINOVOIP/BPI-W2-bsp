/*
 * (C) Copyright 2000-2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * Misc boot support
 */
#include <common.h>
#ifndef CONFIG_BOOT_FOR_WD
#include <command.h>
#include <net.h>
#include <watchdog.h>
#include <nand.h>
#include <rtkspi.h>
#include <fdt_support.h>
#include "linux/lzo.h"
#include "../lib/fastboot/bootimg.h"
#include <asm/sizes.h>
#include <asm/arch/system.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/mcp.h>
#include <asm/arch/bootparam.h>
#include <asm/arch/rbus/crt_reg.h>
#include <asm/arch/rbus/nand_reg.h>
#include <asm/arch/rbus/iso_reg.h>
#include <asm/arch/rbus/crt_sys_reg.h>
#include <asm/arch/rtk_ipc_shm.h>
#include <asm/arch/cpu.h>
#include <asm/arch/factorylib.h>
#include <asm/arch/rtkemmc.h>
#ifdef CONFIG_CMD_SATA
#include <sata.h>
#endif
#ifdef CONFIG_CUSTOMIZE_BOOTFLOW_1
#include <customized.h>
#endif
#if CONFIG_NAS_ENABLE
#include <fdt_support.h>
#include <version.h>
#endif

#ifdef CONFIG_LZMA
#include <lzma/LzmaTypes.h>
#include <lzma/LzmaDec.h>
#include <lzma/LzmaTools.h>
#endif /* CONFIG_LZMA */

#define CONFIG_ANDROID_RECOVERY 0
#if CONFIG_ANDROID_RECOVERY
#include <asm/arch/factorylib.h>
#define RECOVERY_FILE_IN_FACTORY    FACTORY_HEADER_FILE_NAME"recovery"

typedef struct _bootloader_message {
    char command[32];
    char status[32];
    char recovery[1024];
} bootloader_message;
#endif

#define CONFIG_FW_TABLE_SIZE    0x8000

//#define BYPASS_CHECKSUM
//#define EMMC_BLOCK_LOG

DECLARE_GLOBAL_DATA_PTR;

typedef enum{
	BOOT_FROM_USB_DISABLE,
	BOOT_FROM_USB_UNCOMPRESSED,
	BOOT_FROM_USB_COMPRESSED
}BOOT_FROM_USB_T;

typedef enum{
	BOOT_FROM_FLASH_NORMAL_MODE,
	BOOT_FROM_FLASH_MANUAL_MODE
}BOOT_FROM_FLASH_T;

#ifdef CONFIG_CMD_SATA
extern int sata_boot_debug;
extern int sata_curr_device;
extern block_dev_desc_t sata_dev_desc[CONFIG_SYS_SATA_MAX_DEVICE];
#endif /* CONFIG_CMD_SATA */

//[fw] share memory.
extern struct RTK119X_ipc_shm ipc_shm;
extern struct RTK119X_ipc_shm_ir ipc_ir;
int ipc_ir_set = 0;

//[fw] image display.
uchar boot_logo_enable=0;
uint custom_logo_src_width=0;
uint custom_logo_src_height=0;
uint custom_logo_dst_width=0;
uint custom_logo_dst_height=0;
uchar sys_logo_is_HDMI = 0;

#ifndef CONFIG_FACTORY_START
uint eMMC_bootcode_area_size = 0x220000;		// eMMC bootcode area size
#else
uint eMMC_bootcode_area_size = CONFIG_FACTORY_START;
#endif
uint eMMC_fw_desc_table_start = 0;                // start address of valid fw desc table in emmc
uint nand_fw_desc_table_start = 0;                // start address of valid fw desc table in nand
uint sata_fw_desc_table_start = 34;               // start address of valid fw desc table in sata
uint spi_fw_desc_table_start = 0x100000;          // start address of valid fw desc table in spi

BOOT_FROM_FLASH_T boot_from_flash = BOOT_FROM_FLASH_NORMAL_MODE;
BOOT_FROM_USB_T boot_from_usb = BOOT_FROM_USB_DISABLE;
extern BOOT_MODE boot_mode;

#ifdef NAS_ENABLE
uint initrd_size=0;

#if defined(NAS_ENABLE) && defined(CONFIG_RTD161x)
char *ion_media_heap0_size_str;
char *ion_media_heap1_size_str;
long ion_media_heap0_size_MB;
long ion_media_heap1_size_MB;
uint skip_avfw_entry = 0;
#endif /*defined(NAS_ENABLE) && defined(CONFIG_RTD161x)*/
#endif /* NAS_ENABLE */
#ifdef CONFIG_CMD_KEY_BURNING
extern int OTP_Get_Byte(int offset, unsigned char *ptr, unsigned int cnt);
extern unsigned int OTP_JUDGE_BIT(unsigned int offset);
#endif /* CONFIG_CMD_KEY_BURNING */

/* The global variable for realtek feature */
static int accelerate_state = 0;  /*The flag for controlling faster blue logo*/
static int audio_fw_state = 0;
unsigned int Auto_AFW_MEM_START = 0; /* Save the address of AFW from fw_desc */
int UBOOT_NORMAL_BOOT = 1; /* Set UBoot normal or secure boot */

extern const unsigned int Kh_key_default[4];

#ifdef CONFIG_CMD_GO
#if defined(CONFIG_UBOOT_DEFAULT) || defined(CONFIG_FT_RESCUE)

#define BIST_ROOTFS_ADDR    0x30000000

extern void delete_env(void);
extern void enable_clock(uint reg_reset, uint mask_reset, uint reg_clock, uint mask_clock);
extern int rtk_plat_boot_go(bootm_headers_t *images);

extern unsigned int mcp_dscpt_addr;
extern const unsigned int Kh_key_default[4];

int rtk_plat_prepare_fw_image_from_NAND(void);
int rtk_plat_prepare_fw_image_from_eMMC(void);
int rtk_plat_prepare_fw_image_from_SATA(void);
int rtk_plat_prepare_fw_image_from_SPI(void);
int rtk_plat_prepare_fw_image_from_SD(void);
char *rtk_plat_prepare_fw_image_from_USB(int fw_type);
int rtk_plat_do_boot_linux(void);
int rtk_plat_boot_handler(void);
#if defined(CONFIG_RTK_ARM32) || defined(CONFIG_CPU_V7)
static int rtk_call_bootm(void);
#else
static int rtk_call_booti(void);
#endif
int decrypt_image(char *src, char *dst, uint length, uint *key);
int rtk_get_secure_boot_type(void);
void rtk_hexdump( const char * str, unsigned char * pcBuf, unsigned int length );
void GetKeyFromSRAM(unsigned int sram_addr, unsigned char* key, unsigned int length);

static void reset_shared_memory(void);
#if defined(CONFIG_SYS_RTK_SD_FLASH) || defined(CONFIG_SYS_RTK_EMMC_FLASH) || defined(CONFIG_BOOT_FROM_SPI) || defined(CONFIG_SYS_RTK_NAND_FLASH)
static unsigned int get_rescue_rootfs_addr(unsigned int fw_tbl_addr) __maybe_unused;
#endif

#define OTP_REG_BASE  0x98017000
UINT32 OTP_GET_BYTE(UINT32 offset, UINT8 *ptr, UINT32 cnt)
{
	UINT32 ret = -1;
	UINT32 i = 0;
	volatile UINT32 div_n=0;
	volatile UINT32 align_n=0, align_rem_n=0;
	volatile UINT32 real_ofset=0;

	real_ofset = offset&~0x7;
	for(i=0;i<cnt;i++)
	{
		div_n = (real_ofset+i*8)/8;
		align_n = div_n & ~0x3;
		align_rem_n = div_n & 0x3;
		*(ptr+i) = (UINT8)((REG32((uintptr_t)OTP_REG_BASE + align_n)>>(align_rem_n*8))&0xff);
	}

	ret = 0;

	return ret;
}

static unsigned long do_go_kernel_image(void)
{
    int ret = RTK_PLAT_ERR_OK;

#ifdef CONFIG_SYS_RTK_NAND_FLASH
	ret = rtk_plat_prepare_fw_image_from_NAND();
#elif defined(CONFIG_SYS_RTK_EMMC_FLASH)
	ret = rtk_plat_prepare_fw_image_from_eMMC();
#elif defined(CONFIG_SYS_RTK_SATA_STORAGE)
	ret = rtk_plat_prepare_fw_image_from_SATA();
#elif defined(CONFIG_BOOT_FROM_SPI)
	ret = rtk_plat_prepare_fw_image_from_SPI();
#endif
	if (ret!= RTK_PLAT_ERR_OK)
		return ret;

	return rtk_plat_do_boot_linux();
}

#if defined(CONFIG_RTD161x)
void cmd_bl31_afw_magic(unsigned int startup_addr, unsigned int magic_num)
{
	//write magic1
	asm volatile("mov x2, %0" : :"r"(magic_num): "cc");
	asm volatile("mov x1, %0" : :"r"(startup_addr): "cc");
	asm volatile("mov x0, %0" : :"r"(0x8400ffff): "cc"); //function id
	asm volatile("isb" : : : "cc");
	asm volatile("smc #0" : : : "cc");
	asm volatile("isb" : : : "cc");
}
#endif

static unsigned long do_go_audio_fw(void)
{
	int magic = SWAPEND32(0x16803001);
	int offset = SWAPEND32(MIPS_SHARED_MEMORY_ENTRY_ADDR);
	unsigned long fw_addr = getenv_ulong("audio_loadaddr", 16, 0);

	printf("[BPI]%s start audio_fw_state = %d\n", __func__, audio_fw_state);

	if(audio_fw_state) return 0;

	// if IR wakeup info is set...
	if (ipc_ir_set) {
		// cat ir info to the end of IPC_SHM with 16 byte align
		void *ir_tbl_addr = (void*)ALIGN((MIPS_SHARED_MEMORY_ENTRY_ADDR + 0xC4 + sizeof(ipc_shm)), 16);
		memcpy(ir_tbl_addr, &ipc_ir, sizeof(ipc_ir));
		ipc_shm.ir_extended_tbl_pt = SWAPEND32((unsigned int)(uintptr_t)ir_tbl_addr);
	}

	printf("Start Audio Firmware ...\n");

	reset_shared_memory();

	if (!fw_addr)
		fw_addr = CONFIG_FW_LOADADDR;
	if (!ipc_shm.audio_fw_entry_pt)
		ipc_shm.audio_fw_entry_pt = SWAPEND32(fw_addr | MIPS_KSEG0BASE);

	memcpy((unsigned char *)(MIPS_SHARED_MEMORY_ENTRY_ADDR+0xC4), &ipc_shm, sizeof(ipc_shm));
	memcpy((unsigned char *)(MIPS_SHARED_MEMORY_ENTRY_ADDR), &magic, sizeof(magic));
	memcpy((unsigned char *)(MIPS_SHARED_MEMORY_ENTRY_ADDR +4), &offset, sizeof(offset));

	flush_dcache_all();

#if defined(CONFIG_RTD1395)
	rtd_outl(ACPU_STARTUP_FLAG, ACPU_MAGIC1); //write magic1
#elif defined(CONFIG_RTD161x)
	/* ACPU PLL setting */
	rtd_outl(SYS_PLL_ACPU2, 0x00000005); /* OEB=1, RSTB=0, POW=1 */
	rtd_outl(SYS_PLL_ACPU2, 0x00000007); /* OEB=1, RSTB=1, POW=1 */
	rtd_outl(SYS_PLL_SSC_DIG_ACPU0, 0x0000000c); /* turn off OC_EN_ACPU */
	rtd_outl(SYS_PLL_SSC_DIG_ACPU1, 0x00012ded); /* 550MHz(Default) */
	rtd_outl(SYS_PLL_SSC_DIG_ACPU0, 0x0000000d); /* turn on OC_EN_ACPU */
	udelay(150);
	rtd_outl(SYS_PLL_ACPU2, 0x00000003); /* enable ACPU PLL OEB */

	cmd_bl31_afw_magic(ACPU_STARTUP_FLAG, ACPU_MAGIC1);
#else
	rtd_outl(ISO_RESERVED_USE_3, MIPS_A_ENTRY_CODE_ADDR | MIPS_KSEG1BASE);
#endif
	sync();
	/* Enable ACPU */
#ifdef CONFIG_RTD161x
	rtd_setbits(CLOCK_ENABLE3_reg,_BIT7|_BIT6);
#else
	rtd_setbits(CLOCK_ENABLE2_reg,_BIT4);
#endif

	audio_fw_state = 1;

	printf("[BPI]%s end audio_fw_state = %d\n", __func__, audio_fw_state);

	return 0;
}

static unsigned int do_go_video_fw(void)
{
#if defined(CONFIG_RTD131x)
	int err;
	unsigned int fdt_addr;

	printf("Booting VCPU...\n");

	/* Reserve the memory for vcpu */
	fdt_addr = getenv_ulong("fdt_loadaddr", 16, 0x02100000);
	err = fdt_add_mem_rsv((void *)(uintptr_t)fdt_addr, VFW_MEM_START_ADDR, VFW_MEM_SIZE);
	if (err < 0)
		printf("## WARNING %s Add VFW_MEMRSV: %s\n", __func__, fdt_strerror(err));

	/* Continuously send smc command will hang, using mdelay to avoid it. */
	mdelay(1);
	cmd_bl31_afw_magic(VCPU_STARTUP_FLAG, VCPU_MAGIC1);
	sync();

	rtd_setbits(SYS_SOFT_RESET1, _BIT14|_BIT15); /* reset ve2 bist */
	mdelay(1);
	cmd_bl31_afw_magic(RESET_VE2_REGISTER, 0x1); /* reset ve2 bit */
	sync();
	rtd_outl(SYS_CLOCK_ENABLE1, 0x00C00000); /* clock enable for ve2 H256 */
	rtd_outl(SYS_VE_CKSEL, 0x0000061B); /* VE_CKSEL */
	rtd_outl(SYS_PLL_VE2_2, 0x00000003); /* pllvcpu2 reset control active and power control on */
#endif
	return 0;
}

static unsigned long do_go_all_fw(void)
{

	int ret = RTK_PLAT_ERR_OK;

	if (run_command("go a", 0) != 0) {
		printf("go a failed!\n");
		return RTK_PLAT_ERR_BOOT;
	}

	if (run_command("go v", 0) != 0) {
		printf("go v failed!\n");
		return RTK_PLAT_ERR_BOOT;
	}

	if (run_command("go k", 0) != 0) {
		printf("go k failed!\n");
		return RTK_PLAT_ERR_BOOT;
	}

	return ret;
}

#ifdef CONFIG_RESCUE_FROM_USB
int rtk_decrypt_rescue_from_usb(char* filename, unsigned int target)
{
	char tmpbuf[128];
	unsigned char ks[16],kh[16],kimg[16];
    unsigned char aes_key[16],rsa_key[256];
    unsigned int real_body_size = 0;
#ifdef CONFIG_CMD_KEY_BURNING
	unsigned int * Kh_key_ptr = NULL;
#else
	unsigned int * Kh_key_ptr = (unsigned int *)(uintptr_t)Kh_key_default;
#endif
	unsigned int img_truncated_size = RSA_SIGNATURE_LENGTH*2+NP_INV32_LENGTH; // install_a will append 256-byte signature data to it
	int ret;
	unsigned int image_size=0;

	extern unsigned int mcp_dscpt_addr;
	mcp_dscpt_addr = 0;


	sprintf(tmpbuf, "fatload usb 0:1 %x %s",ENCRYPTED_FW_ADDR,filename);
	if (run_command(tmpbuf, 0) != 0) {
			return RTK_PLAT_ERR_READ_FW_IMG;
	}

	image_size = getenv_ulong("filesize", 16, 0);

	memset(ks,0x00,16);
	memset(kh,0x00,16);
	memset(kimg,0x00,16);

    memset(aes_key,0x00,16);
	memset(rsa_key,0x00,256);

    GetKeyFromSRAM(KH_P_SRAM_ADDR, aes_key, AES_KEY_SIZE);
    GetKeyFromSRAM(RSA_KEY_FW_SRAM_ADDR, rsa_key, RSA_KEY_SIZE);
    flush_cache((unsigned int) (uintptr_t)aes_key, AES_KEY_SIZE);
    flush_cache((unsigned int) (uintptr_t)rsa_key, RSA_KEY_SIZE);

#ifdef CONFIG_CMD_KEY_BURNING
	OTP_Get_Byte(OTP_K_S, ks, 16);
	OTP_Get_Byte(OTP_K_H, kh, 16);
	sync();
	flush_cache((unsigned int) (uintptr_t)ks, 16);
	flush_cache((unsigned int) (uintptr_t)kh, 16);
#endif
	AES_ECB_encrypt(ks, 16, kimg, (unsigned int *)kh);
	flush_cache((unsigned int) (uintptr_t)kimg, 16);
	sync();

	//Kh_key_ptr = kimg;
	//Kh_key_ptr[0] = swap_endian(Kh_key_ptr[0]);
	//Kh_key_ptr[1] = swap_endian(Kh_key_ptr[1]);
	//Kh_key_ptr[2] = swap_endian(Kh_key_ptr[2]);
	//Kh_key_ptr[3] = swap_endian(Kh_key_ptr[3]);
    Kh_key_ptr = (unsigned int *) (uintptr_t)aes_key;
	flush_cache((unsigned int) (uintptr_t)aes_key, 16);

    // decrypt image
	printf("to decrypt...\n");

	flush_cache((unsigned int) ENCRYPTED_FW_ADDR, image_size);

    if (decrypt_image((char *)ENCRYPTED_FW_ADDR,
		(char *)(uintptr_t)target,
		image_size - img_truncated_size,
		Kh_key_ptr))
	{
		printf("decrypt image:%s error!\n", filename);
		return RTK_PLAT_ERR_READ_FW_IMG;
	}

	sync();
	memset(ks,0x00,16);
	memset(kh,0x00,16);
	memset(kimg,0x00,16);

    copy_memory((void *)(uintptr_t)target + image_size - img_truncated_size,(void *) ENCRYPTED_FW_ADDR + image_size - img_truncated_size, img_truncated_size);
	flush_cache((unsigned int) target, image_size);

    real_body_size = (UINT32)(REG32((volatile UINT32 *)(uintptr_t)target + (image_size - img_truncated_size) - 4));
    real_body_size = swap_endian(real_body_size);
	real_body_size /= 8;

	ret = Verify_SHA256_hash( (unsigned char *)(uintptr_t)target,
							real_body_size,
							(unsigned char *)(uintptr_t)(target + image_size - img_truncated_size),
							1, rsa_key);
	if( ret < 0 ) {
		printf("[ERR] %s: verify hash fail(%d)\n", __FUNCTION__, ret );
		return RTK_PLAT_ERR_READ_FW_IMG;
	}

	return RTK_PLAT_ERR_OK;
}

int boot_rescue_from_usb(void)
{
	char tmpbuf[128];
	int ret = RTK_PLAT_ERR_OK;
	char *filename;
	unsigned int rescue_rootfs_loadaddr=CONFIG_RESCUE_ROOTFS_LOADADDR;
	unsigned int secure_mode=0;

	secure_mode = rtk_get_secure_boot_type();

	printf("==== %s (secure mode:%d)=====\n", __func__, secure_mode);

	run_command("usb start", 0);	/* "usb start" always return 0 */
	if (run_command("usb dev", 0) != 0) {
		printf("No USB device found!\n");
		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}

	/* DTB */
	if ((filename = getenv("rescue_dtb")) == NULL) {
		filename =(char*) CONFIG_RESCUE_FROM_USB_DTB;
	}
	sprintf(tmpbuf, "fatload usb 0:1 %s %s", getenv("fdt_loadaddr"), filename);
	if (run_command(tmpbuf, 0) != 0) {
		goto loading_failed;
	}

	printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("fdt_loadaddr"));

	/* Linux kernel */
	if ((filename = getenv("rescue_vmlinux")) == NULL) {
		filename =(char*) CONFIG_RESCUE_FROM_USB_VMLINUX;
	}
	if(secure_mode == RTK_SECURE_BOOT)
	{
		if (rtk_decrypt_rescue_from_usb(filename,getenv_ulong("kernel_loadaddr", 16, 0)))
		goto loading_failed;
	}
	else
	{
		sprintf(tmpbuf, "fatload usb 0:1 %s %s", getenv("kernel_loadaddr"), filename);
		if (run_command(tmpbuf, 0) != 0) {
			goto loading_failed;
		}
	}

	printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("kernel_loadaddr"));

	/* rootfs */
	if ((filename = getenv("rescue_rootfs")) == NULL) {
		filename =(char*) CONFIG_RESCUE_FROM_USB_ROOTFS;
	}
	rescue_rootfs_loadaddr = get_rescue_rootfs_addr(rescue_rootfs_loadaddr);
	if(secure_mode == RTK_SECURE_BOOT)
	{
		if (rtk_decrypt_rescue_from_usb(filename, rescue_rootfs_loadaddr))
		goto loading_failed;
	}
	else
	{
		sprintf(tmpbuf, "fatload usb 0:1 0x%08x %s", rescue_rootfs_loadaddr, filename);
		if (run_command(tmpbuf, 0) != 0) {
			goto loading_failed;
		}
	}

	printf("Loading \"%s\" to 0x%08x is OK.\n\n", filename, rescue_rootfs_loadaddr);

	/* audio firmware */
	if ((filename = getenv("rescue_audio")) == NULL) {
		filename =(char*) CONFIG_RESCUE_FROM_USB_AUDIO_CORE;
	}
	if(secure_mode == RTK_SECURE_BOOT)
	{
		if (!rtk_decrypt_rescue_from_usb(filename, MIPS_AUDIO_FW_ENTRY_ADDR))
		{
			printf("Loading \"%s\" to 0x%08x is OK.\n", filename, MIPS_AUDIO_FW_ENTRY_ADDR);
			run_command("go a", 0);
		}
		else
			printf("Loading \"%s\" from USB failed.\n", filename);
			/* Go on without Audio firmware. */
	}
	else
	{
		sprintf(tmpbuf, "fatload usb 0:1 0x%08x %s", MIPS_AUDIO_FW_ENTRY_ADDR, filename);
		if (run_command(tmpbuf, 0) == 0) {
			printf("Loading \"%s\" to 0x%08x is OK.\n", filename, MIPS_AUDIO_FW_ENTRY_ADDR);
			run_command("go a", 0);
		}
		else {
			printf("Loading \"%s\" from USB failed.\n", filename);
			/* Go on without Audio firmware. */
		}
    }
	boot_mode = BOOT_RESCUE_MODE;

	/* Clear the HYP ADDR since we don't want rescue jump to HYP mode */
	if (getenv("hyp_loadaddr"))
		setenv("hyp_loadaddr", "");

#if defined(CONFIG_RTK_ARM32) || defined(CONFIG_CPU_V7)
	ret = rtk_call_bootm();
#else
	ret = rtk_call_booti();
#endif
	/* Should not reach here */

	return ret;

loading_failed:
	printf("Loading \"%s\" from USB failed.\n", filename);
	return RTK_PLAT_ERR_READ_RESCUE_IMG;
}
#endif /* CONFIG_RESCUE_FROM_USB */
#endif /* defined(CONFIG_UBOOT_DEFAULT) || defined(CONFIG_FT_RESCUE) */

#ifdef CONFIG_BOOT_FROM_SD
int boot_from_sd(void)
{
	char tmpbuf[128];
	int ret = RTK_PLAT_ERR_OK;
	char *filename;
	unsigned int secure_mode=0;

	secure_mode = rtk_get_secure_boot_type();

	printf("[BPI] %s (boot from SD mode; secure_mode %d)=====\n",
	__func__, secure_mode);

#if 0 /* had beed executed in board.c>>sd_card_init */
	ret = run_command("sd init", 0);
	if( ret != 0 ) {
		DDDDRED("sd initialize failed\n");
		goto loading_failed;
	}
#endif

	/* DTB 0x02100000 */
	/* ROOTFS 0x02100000 */
	/* Kernel 0x03000000 */
	/* AudioFW 0x0f900000 or 0x01b00000 */
	/* Image file boot logo 0x1e800000 */

	/* DTB ------------------------------------------------------------------ */
	if ((filename = getenv("sd_boot_dtb")) == NULL) {
		filename =(char*) CONFIG_BOOT_FROM_SD_DTB;
	}
	sprintf(tmpbuf, "fatload %s 0:1 %s %s", getenv("device"), getenv("fdt_loadaddr"), filename);
	if (run_command(tmpbuf, 0) != 0) {
		DDDDRED("load %s to %s failed\n", filename, getenv("fdt_loadaddr"));
		goto loading_failed;
	}
	printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("fdt_loadaddr"));

	/* ROOTFS(uInitrd) --------------------------------------------------------------- */
	if ((filename = getenv("sd_boot_rootfs")) == NULL) {
		filename =(char*) CONFIG_BOOT_FROM_SD_ROOTFS;
	}
	
	if(secure_mode == RTK_SECURE_BOOT)
	{
#if 0
		if (rtk_decrypt_rescue_from_sd(filename,getenv_ulong("rootfs_loadaddr", 16, 0))) {
			DDDDRED("Loading \"%s\" to %s failed.\n\n", filename, getenv("rootfs_loadaddr"));
			goto loading_failed;
		}
#else
		DDDDRED("Not implement for secure mode\n");
		DDDDRED("Loading \"%s\" to %s failed.\n\n", filename, getenv("rootfs_loadaddr"));
		goto loading_failed;
#endif
	}
	else {
		sprintf(tmpbuf, "fatload %s 0:1 %s %s", getenv("device"), getenv("rootfs_loadaddr"), filename);
		if (run_command(tmpbuf, 0) != 0) {
			DDDDRED("load %s to %s failed\n", filename, getenv("rootfs_loadaddr"));
#if 0 /* it is not essential for ubuntu kernel */
			goto loading_failed;
#endif
		}
		else
			printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("rootfs_loadaddr"));
	}

	/* Kernel --------------------------------------------------------------- */
	if ((filename = getenv("sd_vmlinux")) == NULL) {
		filename =(char*) CONFIG_BOOT_FROM_SD_VMLINUX;
	}
	if(secure_mode == RTK_SECURE_BOOT)
	{
#if 0
		if (rtk_decrypt_rescue_from_sd(filename,getenv_ulong("kernel_loadaddr", 16, 0))) {
			DDDDRED("Loading \"%s\" to %s failed.\n\n", filename, getenv("kernel_loadaddr"));
			goto loading_failed;
		}
#else
		DDDDRED("Not implement for secure mode\n");
		DDDDRED("Loading \"%s\" to %s failed.\n\n", filename, getenv("kernel_loadaddr"));
		goto loading_failed;
#endif
	}
	else
	{
		sprintf(tmpbuf, "fatload %s 0:1 %s %s", getenv("device"), getenv("kernel_loadaddr"), filename);
		if (run_command(tmpbuf, 0) != 0) {
			DDDDRED("load %s to %s failed\n", filename, getenv("kernel_loadaddr"));
			goto loading_failed;
		}
		printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("kernel_loadaddr"));
	}

	/* audio firmware ------------------------------------------------------- */
	if ((filename = getenv("sd_audio")) == NULL) {
		filename =(char*) CONFIG_BOOT_FROM_SD_AUDIO_CORE;
	}
	if(secure_mode == RTK_SECURE_BOOT)
	{
#if 0
		if (rtk_decrypt_rescue_from_sd(filename,getenv_ulong("audio_loadaddr", 16, 0))) {
			DDDDRED("Loading \"%s\" to %s failed.\n\n", filename, getenv("audio_loadaddr"));
			goto loading_failed;
		}
#else
		DDDDRED("Not implement for secure mode\n");
		DDDDRED("Loading \"%s\" to %s failed.\n\n", filename, getenv("audio_loadaddr"));
		goto loading_failed;
#endif
	}
	else
	{
		sprintf(tmpbuf, "fatload %s 0:1 %s %s", getenv("device"), getenv("audio_loadaddr"), filename);
		if (run_command(tmpbuf, 0) != 0) {
			DDDDRED("load %s to %s failed\n", filename, getenv("audio_loadaddr"));
			goto loading_failed;
		}
		printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("audio_loadaddr"));
	}

	/* bpi, audio firmware prepare */
	printf("[BPI]%s run go a to prepare audio firmware\n", __func__);
	run_command("go a", 0);

	boot_mode = BOOT_RESCUE_MODE;

#ifdef CONFIG_WAIT_AFW_1_SECOND
	mdelay(1000); /* wait audio fw log print out */
#endif

	/* Clear the HYP ADDR since we don't want rescue jump to HYP mode */
	if (getenv("hyp_loadaddr"))
		setenv("hyp_loadaddr", "");

#if defined(CONFIG_RTK_ARM32) || defined(CONFIG_CPU_V7)
	ret = rtk_call_bootm();
#else
	ret = rtk_call_booti();
#endif
	/* Should not reach here */

	return ret;

loading_failed:
	//printf("Loading \"%s\" from SD failed.\n", filename);
	return RTK_PLAT_ERR_READ_SD_IMG;
}
#endif /* CONFIG_BOOT_FROM_SD */


#ifdef CONFIG_LOADBOOTCODE_FROM_SD
int load_bootcode_from_sd(void)
{
	int ret;
	unsigned char *pBuf;
	char commandBuf[128];

	printf("==== start load bootcode from SD =====\n");

	do {
		ret = run_command("sd init", 0);
		if( ret != 0 ) {
			DDDDRED("sd initialize failed\n");
			break;
		}

		/* add sanity check here */
		sprintf(commandBuf, "sd read 0x%08x 0x50 0x430", CONFIG_SD_BOOTCODE_BASE);
		run_command(commandBuf, 0);
		pBuf = (unsigned char *)CONFIG_SD_BOOTCODE_BASE;
		/* add sanity check here */
		if( ! ( pBuf[0] == 0x0A &&
				pBuf[1] == 0x00 &&
				pBuf[2] == 0x00 &&
				pBuf[3] == 0x14 ) ) {
			DDDDRED("[WARNING] bootcode seem is not valid, first 4 bytes:\n"
					"          %02x %02x %02x %02x\n",
					pBuf[0], pBuf[1], pBuf[2], pBuf[3]);
			break;
		}
		run_command("icache off", 0);
		run_command("dcache off", 0);
		printf("finish to load bootcode from SD to 0x%08x\n", CONFIG_SD_BOOTCODE_BASE);

		sprintf(commandBuf, "go 0x%08x", CONFIG_SD_BOOTCODE_BASE);
		run_command(commandBuf, 0);

		DDDDRED("==== sholud not reach =====\n");
	}
	while(0);

	return RTK_PLAT_ERR_BOOT;
}
#endif /* CONFIG_LOADBOOTCODE_FROM_SD */


/* Allow ports to override the default behavior */
__attribute__((weak))
unsigned long do_go_exec (ulong (*entry)(int, char * const []), int argc, char * const argv[])
{
	return entry (argc, argv);
}


int do_go (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	ulong	addr, rc;
	int     rcode = 0;
	int     do_cleanup = 0;

	if (argc < 2)
		return CMD_RET_USAGE;

	if (argv[1][0] == 'a')
	{
		if (argv[1][1] == '\0')	// audio fw
		{
			return do_go_audio_fw();
		}
		else if (argv[1][1] == 'l' && argv[1][2] == 'l')	// all fw
		{
			return do_go_all_fw();
		}
		else
		{
			printf("Unknown command '%s'\n", argv[1]);
			return CMD_RET_USAGE;
		}
	}
	else if(argv[1][0] == 'v')
	{
		if (argv[1][1] == '\0')	// video fw
		{
			return do_go_video_fw();
		}
	}
	else if( strncmp( argv[1], "sdb", 3 ) == 0 )
	{
#ifdef CONFIG_LOADBOOTCODE_FROM_SD
		return load_bootcode_from_sd();
#else
		printf("Unknown command '%s'\n", argv[1]);
		return CMD_RET_USAGE;
#endif /* CONFIG_LOADBOOTCODE_FROM_SD */
	}
	else if( strncmp( argv[1], "sd", 2 ) == 0 )
	{
#ifdef CONFIG_BOOT_FROM_SD
		return boot_from_sd();
#else
		printf("Unknown command '%s'\n", argv[1]);
		return CMD_RET_USAGE;
#endif /* CONFIG_LOADBOOTCODE_FROM_SD */
	}
#ifdef CONFIG_BOOT_FROM_SATA
	else if (argv[1][0] == 's')
	{
		sata_boot_debug = 0;
		if( argc > 2 ) {
			if( strncmp( argv[2], "debug", 5 ) == 0 ) {
				sata_boot_debug = 1;
			}
		}
		if( strncmp( argv[1], "snboot", 6 ) == 0 ) {
			boot_mode = BOOT_NORMAL_MODE;
			return rtk_plat_boot_handler();
		}
		else if( strncmp( argv[1], "saboot", 6 ) == 0 ) {
			boot_mode = BOOT_ANDROID_MODE;
			return rtk_plat_boot_handler();
		}
		else if( strncmp( argv[1], "srboot", 6 ) == 0 ) {
			boot_mode = BOOT_RESCUE_MODE;
			return rtk_plat_boot_handler();
		}
		else if( strncmp( argv[1], "sgboot", 6 ) == 0 ) {
			boot_mode = BOOT_GOLD_MODE;
			return rtk_plat_boot_handler();
		}
	}
	else if (argv[1][0] == 'i')
	{
		if( strncmp( argv[1], "info", 4 ) == 0 ) {
			printf("## boot_mode is %d\n", boot_mode);
			printf("## boot_flash_type is %d\n", boot_flash_type);
			printf("## sata_curr_device is %d\n", sata_curr_device);
			printf("## fw_desc_table_v1 struct size    = 0x%lx\n", sizeof(fw_desc_table_v1_t));
			printf("## part_entry struct size          = 0x%lx\n", sizeof(part_desc_entry_v1_t));
			printf("## fw_entry struct size            = 0x%lx\n", sizeof(fw_desc_entry_v1_t));
			return 0;
		}
	}
#endif /* CONFIG_BOOT_FROM_SATA */
	else if (argv[1][0] == 'k')
	{
		if (argv[1][1] == '\0')	// getkernel image from ddr;
		{
			return rtk_plat_do_boot_linux();
		}
		else if (argv[1][1] == 'f')	// get kernel image from flash;
		{
			boot_mode = BOOT_KERNEL_ONLY_MODE;
			return do_go_kernel_image();
		}
		else
		{
			printf("Unknown command '%s'\n", argv[1]);
			return CMD_RET_USAGE;
		}

	}
	else if (argv[1][0] == 'r')
	{
		if (argv[1][1] == '\0') // rescue from flash
		{
			boot_mode = BOOT_RESCUE_MODE;
#ifdef NAS_ENABLE
			if (RTK_PLAT_ERR_OK == rtk_plat_boot_handler())
				return RTK_PLAT_ERR_OK;
			else
				boot_mode=BOOT_GOLD_MODE;
#endif
			return rtk_plat_boot_handler();
		}
		else if (argv[1][1] == 'a') // rescue for android
		{
			boot_mode = BOOT_ANDROID_MODE;
			return rtk_plat_boot_handler();
		}
#ifdef CONFIG_RESCUE_FROM_USB
		else if (argv[1][1] == 'u') // rescue from usb
		{
			return boot_rescue_from_usb();
		}
#endif
		else
		{
			return 0;
		}
	}

	addr = simple_strtoul(argv[1], NULL, 16);

#ifdef CONFIG_CLEAR_ENV_AFTER_UPDATE_BOOTCODE
	if (addr == DVRBOOT_EXE_BIN_ENTRY_ADDR)
	{
		printf ("Clear env when updating bootcode ...\n");
		delete_env();
	}
#endif

	printf ("Starting application at 0x%08lX ...\n", addr);

	if( strncmp( argv[2], "nocache", 7 ) == 0 ) {
		do_cleanup = 1;
		printf ("Run application w/o any cache\n");
		//cleanup_before_dvrbootexe();
	}

	/*
	 * pass address parameter as argv[0] (aka command name),
	 * and all remaining args
	 */
	rc = do_go_exec ((void *)addr, argc - 1 - do_cleanup, argv + 1 + do_cleanup);
	if (rc != 0) rcode = 1;

	printf ("Application terminated, rc = 0x%lX\n", rc);
	return rcode;
}


int do_goru (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	//boot_mode = BOOT_CONSOLE_MODE;
#ifdef CONFIG_RESCUE_FROM_USB
	WATCHDOG_DISABLE();
	setenv("bootcmd", "bootr");
	return boot_rescue_from_usb();
#else
	return 0;
#endif
}


int do_gosd (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	printf("[BPI]%s\n", __func__);
	
	//boot_mode = BOOT_CONSOLE_MODE;
#ifdef CONFIG_BOOT_FROM_SD
	WATCHDOG_DISABLE();
	setenv("bootcmd", "bootr");
	return boot_from_sd();
#else
	DDDDRED("command \"gosd\" not IMPLEMENT\n");
	return 0;
#endif
}

/* sdb means SD Bootcode */
int do_gosdb (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	//boot_mode = BOOT_CONSOLE_MODE;
#ifdef CONFIG_LOADBOOTCODE_FROM_SD
	WATCHDOG_DISABLE();
	return load_bootcode_from_sd();
#else
	DDDDRED("command \"gosdb\" not IMPLEMENT\n");
	return 0;
#endif
}

/* -------------------------------------------------------------------- */

U_BOOT_CMD(
	go, CONFIG_SYS_MAXARGS, 1,	do_go,
	"start application at address 'addr' or start running fw",
	"[addr/a/v/v1/v2/k] [arg ...]\n"
	"\taddr  - start application at address 'addr'\n"
	"\ta     - start audio firmware\n"
	"\tv     - start video firmware\n"
	"\tk     - start kernel\n"
	"\tr     - start rescue linux\n"
#ifdef CONFIG_RESCUE_FROM_USB
	"\tru    - start rescue linux from usb\n"
#endif
#ifdef CONFIG_LOADBOOTCODE_FROM_SD
	"\tsdb   - start load bootcode from SD\n"
#endif
#ifdef CONFIG_BOOT_FROM_SD
	"\tsd    - start load image from SD\n"
#endif
#ifdef CONFIG_BOOT_FROM_SATA
    "\tsnboot - go sata boot flow(BOOT_NORMAL_MODE)\n"
    "\tsaboot - go sata boot flow(BOOT_ANDROID_MODE)\n"
    "\tsrboot - go sata rescue boot flow(BOOT_RESCUE_MODE)\n"
	"\tsgboot - go golden rescue boot flow(BOOT_GOLD_MODE)\n"
	"\tinfo   - show curren mode info\n"
#endif
	"\tall   - start all firmware\n"
	"\t[arg] - passing 'arg' as arguments\n"
);


/* -------------------------------------------------------------------- */

U_BOOT_CMD(
	goru, CONFIG_SYS_MAXARGS, 1,    do_goru,
	"start rescue linux from usb",
	""
);

U_BOOT_CMD(
	gosd, CONFIG_SYS_MAXARGS, 1,    do_gosd,
	"start boot from sd",
	""
);

U_BOOT_CMD(
	gosdb, CONFIG_SYS_MAXARGS, 1,    do_gosdb,
	"load bootcode from sd",
	""
);

#endif


U_BOOT_CMD(
	reset, 1, 0,	do_reset,
	"Perform RESET of the CPU",
	""
);

uint get_checksum(uchar *p, uint len) {
	uint checksum = 0;
	uint i;

	for(i = 0; i < len; i++) {
		checksum += *(p+i);

		if (i % 0x200000 == 0)
		{
			EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here
		}
	}
	return checksum;
}


uint get_mem_layout_when_read_image(MEM_LAYOUT_WHEN_READ_IMAGE_T *mem_layout)
{
	if (mem_layout->image_target_addr == 0)
	{
		printf("[ERROR] mem_layout->image_target_addr = 0x%08x\n", mem_layout->image_target_addr);

		return 1;
	}

	if (mem_layout->bIsEncrypted)
	{
#ifdef CONFIG_SYS_RTK_NAND_FLASH
		mem_layout->flash_to_ram_addr = mem_layout->image_target_addr;
#else
		mem_layout->flash_to_ram_addr = mem_layout->encrpyted_addr = ENCRYPTED_FW_ADDR;
#endif
		if (mem_layout->bIsCompressed)
		{
			mem_layout->decrypted_addr = mem_layout->compressed_addr = COMPRESSED_FW_IMAGE_ADDR;
			mem_layout->decompressed_addr = mem_layout->image_target_addr;
		}
		else
		{
			mem_layout->decrypted_addr = mem_layout->image_target_addr;
		}
	}
	else
	{
		if (mem_layout->bIsCompressed)
		{
			mem_layout->flash_to_ram_addr = mem_layout->compressed_addr = COMPRESSED_FW_IMAGE_ADDR;
			mem_layout->decompressed_addr = mem_layout->image_target_addr;
		}
		else
		{
			mem_layout->flash_to_ram_addr = mem_layout->image_target_addr;
		}
	}

	return 0;
}

int decrypt_image(char *src, char *dst, uint length, uint *key)
{
	printf("decrypt from 0x%08lu to 0x%08lu, len:0x%08x\n", (ulong)src, (ulong)dst, length);

    if (length & 0xf) {
        printf("%s %d, fail\n", __FUNCTION__, __LINE__);
        return -1;
    }

    if (AES_ECB_decrypt((uchar *)src, length, (uchar *)dst, key)) {
		printf("%s %d, fail\n", __FUNCTION__, __LINE__);
		return -1;
	}

	return 0;
}

//#define DUBUG_FW_DESC_TABLE
#ifdef DUBUG_FW_DESC_TABLE
void dump_fw_desc_table_v1(fw_desc_table_v1_t *fw_desc_table_v1)
{
	if (fw_desc_table_v1 != NULL) {
		printf("## Fw Desc Table ##############################\n");
		printf("## fw_desc_table_v1                = %p\n", fw_desc_table_v1);
		printf("## fw_desc_table_v1->signature     = %s\n", fw_desc_table_v1->signature);
		printf("## fw_desc_table_v1->checksum      = 0x%08x\n", fw_desc_table_v1->checksum);
		printf("## fw_desc_table_v1->version       = 0x%08x\n", fw_desc_table_v1->version);
		printf("## fw_desc_table_v1->paddings      = 0x%08x\n", fw_desc_table_v1->paddings);
		printf("## fw_desc_table_v1->part_list_len = 0x%08x\n", fw_desc_table_v1->part_list_len);
		printf("## fw_desc_table_v1->fw_list_len   = 0x%08x\n", fw_desc_table_v1->fw_list_len);
#ifdef NAS_DUAL
		printf("## fw_desc_table_v1->seqnum        = 0x%08x\n", fw_desc_table_v1->seqnum);
#endif
		printf("###############################################\n\n");
	}
	else {
		printf("[ERR] %s:%d fw_desc_table_v1 is NULL.\n", __FUNCTION__, __LINE__);
	}
}

void dump_part_desc_entry_v1(part_desc_entry_v1_t *part_entry)
{
	if (part_entry != NULL) {
		printf("## Part Desc Entry ############################\n");
		printf("## part_entry                      = %p\n",	part_entry);
		printf("## part_entry->type                = 0x%08x\n", part_entry->type);
		printf("## part_entry->ro                  = 0x%08x\n", part_entry->ro);
		printf("## part_entry->length              = 0x%08llx\n", part_entry->length);
		printf("## part_entry->fw_count            = 0x%08x\n", part_entry->fw_count);
		printf("## part_entry->fw_type             = 0x%08x\n", part_entry->fw_type);
		printf("## part_entry->mount_point         = %s\n", part_entry->mount_point);
		printf("###############################################\n\n");
	}
	else {
		printf("[ERR] %s:%d part_entry is NULL.\n", __FUNCTION__, __LINE__);
	}
}

void dump_fw_desc_entry_v1(fw_desc_entry_v1_t *fw_entry)
{
	if (fw_entry != NULL) {
		printf("## Fw Desc Entry ##############################\n");
		printf("## fw_entry                        = %p\n", fw_entry);
		printf("## fw_entry->type                  = 0x%08x\n", fw_entry->type);
		printf("## fw_entry->lzma                  = 0x%08x\n", fw_entry->lzma);
		printf("## fw_entry->ro                    = 0x%08x\n", fw_entry->ro);
		printf("## fw_entry->version               = 0x%08x\n", fw_entry->version);
		printf("## fw_entry->target_addr           = 0x%08x\n", fw_entry->target_addr);
		printf("## fw_entry->offset                = 0x%08x\n", fw_entry->offset);
		printf("## fw_entry->length                = 0x%08x\n", fw_entry->length);
		printf("## fw_entry->paddings              = 0x%08x\n", fw_entry->paddings);
		printf("## fw_entry->checksum              = 0x%08x\n", fw_entry->checksum);
		printf("###############################################\n\n");
	}
	else {
		printf("[ERR] %s:%d fw_entry is NULL.\n", __FUNCTION__, __LINE__);
	}
}

void dump_fw_desc_entry_v2(fw_desc_entry_v2_t *fw_entry)
{
	int i;

	if (fw_entry != NULL) {
		printf("## Fw Desc Entry ##############################\n");
		printf("## fw_entry                        = %p\n", fw_entry);
		printf("## fw_entry->type                  = 0x%08x\n", fw_entry->type);
		printf("## fw_entry->lzma                  = 0x%08x\n", fw_entry->lzma);
		printf("## fw_entry->ro                    = 0x%08x\n", fw_entry->ro);
		printf("## fw_entry->version               = 0x%08x\n", fw_entry->version);
		printf("## fw_entry->target_addr           = 0x%08x\n", fw_entry->target_addr);
		printf("## fw_entry->offset                = 0x%08Lx\n", fw_entry->offset);
		printf("## fw_entry->length                = 0x%08x\n", fw_entry->length);
		printf("## fw_entry->paddings              = 0x%08x\n", fw_entry->paddings);
		printf("## fw_entry->sha_hash              = ");
		for (i = 0 ; i < 32 ; i++)
			printf("%02x", fw_entry->sha_hash[i]);
		printf("\n");
		printf("###############################################\n\n");
	}
	else {
		printf("[ERR] %s:%d fw_entry is NULL.\n", __FUNCTION__, __LINE__);
	}
}
#endif

//#define DUBUG_BOOT_AV_INFO
#ifdef DUBUG_BOOT_AV_INFO
void dump_boot_av_info(boot_av_info_t *boot_av)
{
	if (boot_av != NULL) {
		printf("\n");
		printf("## Boot AV Info (0x%08x) ##################\n", boot_av);
		printf("## boot_av->dwMagicNumber          = 0x%08x\n", boot_av->dwMagicNumber);
		printf("## boot_av->dwVideoStreamAddress   = 0x%08x\n", boot_av->dwVideoStreamAddress);
		printf("## boot_av->dwVideoStreamLength    = 0x%08x\n", boot_av->dwVideoStreamLength);
		printf("## boot_av->dwAudioStreamAddress   = 0x%08x\n", boot_av->dwAudioStreamAddress);
		printf("## boot_av->dwAudioStreamLength    = 0x%08x\n", boot_av->dwAudioStreamLength);
		printf("## boot_av->bVideoDone             = 0x%08x\n", boot_av->bVideoDone);
		printf("## boot_av->bAudioDone             = 0x%08x\n", boot_av->bAudioDone);
		printf("## boot_av->bHDMImode              = 0x%08x\n", boot_av->bHDMImode);
		printf("## boot_av->dwAudioStreamVolume    = 0x%08x\n", boot_av->dwAudioStreamVolume);
		printf("## boot_av->dwAudioStreamRepeat    = 0x%08x\n", boot_av->dwAudioStreamRepeat);
		printf("## boot_av->bPowerOnImage          = 0x%08x\n", boot_av->bPowerOnImage);
		printf("## boot_av->bRotate                = 0x%08x\n", boot_av->bRotate);
		printf("## boot_av->dwVideoStreamType      = 0x%08x\n", boot_av->dwVideoStreamType);
		printf("## boot_av->audio_buffer_addr      = 0x%08x\n", boot_av->audio_buffer_addr);
		printf("## boot_av->audio_buffer_size      = 0x%08x\n", boot_av->audio_buffer_size);
		printf("## boot_av->video_buffer_addr      = 0x%08x\n", boot_av->video_buffer_addr);
		printf("## boot_av->video_buffer_size      = 0x%08x\n", boot_av->video_buffer_size);
		printf("## boot_av->last_image_addr        = 0x%08x\n", boot_av->last_image_addr);
		printf("## boot_av->last_image_size        = 0x%08x\n", boot_av->last_image_size);
		printf("###############################################\n\n");
	}
}
#endif

static void reset_shared_memory(void)
{
	boot_av_info_t *boot_av;

	boot_av = (boot_av_info_t *) MIPS_BOOT_AV_INFO_ADDR;
	if(boot_av-> dwMagicNumber != SWAPEND32(BOOT_AV_INFO_MAGICNO))
	{
		/* clear boot_av_info memory */
		memset(boot_av, 0, sizeof(boot_av_info_t));
	}
}

/*
 * read Efuse.
 */
int rtk_get_secure_boot_type(void)
{
#ifdef CONFIG_CMD_KEY_BURNING
	if(OTP_JUDGE_BIT(OTP_BIT_SECUREBOOT))
		return RTK_SECURE_BOOT;
#endif
	//return RTK_SECURE_BOOT;
	return NONE_SECURE_BOOT;
}


/*
 * Support boot from NAND or eMMC on squashfs/ext4 partition.
 */
#ifdef NAS_ENABLE
#define NAS_ROOT "/"
#define NAS_ETC "etc"
#define NAS_SPI_PARTS "mtdparts=RtkSFC:1024k(Boot)ro,-(FW) "
int rtk_plat_set_boot_flag_from_part_desc(
        part_desc_entry_v1_t* part_entry, int part_count)
{
#ifndef NAS_DUAL
    if(boot_mode == BOOT_RESCUE_MODE || boot_mode == BOOT_GOLD_MODE)
    {
#if defined(CONFIG_BOOT_FROM_SPI)
        setenv("nas_part", NAS_SPI_PARTS);
#endif
        return RTK_PLAT_ERR_OK;
    }
#endif

    const char *nas_root = NAS_ROOT;
    char *device_path = NULL;
    if (BOOT_EMMC == boot_flash_type)
        device_path = "/dev/mmcblk0p";
    else if (BOOT_NAND == boot_flash_type)
        device_path = "/dev/mtdblock";
	else if (BOOT_SATA == boot_flash_type)
        device_path = "/dev/satablk0p";
	else if (BOOT_NOR_SERIAL == boot_flash_type) {
#ifdef CONFIG_BOOT_FROM_SATA
        device_path = "/dev/satablk0p";
#elif defined(CONFIG_BOOT_FROM_SPI)
        device_path = "/dev/sda";
#endif
    }

    if (!device_path)
        return RTK_PLAT_ERR_BOOT;

#ifdef NAS_DUAL
    if(boot_mode == BOOT_GOLD_MODE)
        nas_root = "/root";
#endif

    char *tmp_cmdline = NULL;

    tmp_cmdline = (char*)malloc(256);

    if (!tmp_cmdline) {
        printf("%s: Malloc failed\n", __func__);
        return RTK_PLAT_ERR_BOOT;
    }
    memset(tmp_cmdline, 0, 256);

    unsigned char empty_mount[sizeof(part_entry->mount_point)];
    memset(empty_mount, 0, sizeof(empty_mount));

#if defined(CONFIG_BOOT_FROM_SPI)
    // Set mtd Boot partition for read-only access
    if (BOOT_NOR_SERIAL == boot_flash_type) {
        strcpy(tmp_cmdline, NAS_SPI_PARTS);
        strcpy(tmp_cmdline+strlen(tmp_cmdline), "init=/etc/init ");
        strcpy(tmp_cmdline+strlen(tmp_cmdline), "root=/dev/sda1 rootfstype=ext4 rootwait");
    }
#endif

    int i;
    for(i = 0; i < part_count; i++) {
        if (memcmp(empty_mount, part_entry[i].mount_point, sizeof(empty_mount)) != 0) {
            if (0 == strcmp((char *)part_entry[i].mount_point, nas_root)){
                int minor_num = i;
#ifdef CONFIG_SYS_RTK_EMMC_FLASH
                if (BOOT_EMMC == boot_flash_type)
                    minor_num = part_entry[i].emmc_partIdx;
#endif

                strcpy(tmp_cmdline+strlen(tmp_cmdline), " init=/etc/init ");

                int cmd_len = strlen(tmp_cmdline);
                char *rootfstype = "";
                char *opts = "";
                switch (part_entry[i].fw_type)
                {
                    case FS_TYPE_SQUASH:
                        rootfstype = "squashfs";
                        if (BOOT_NAND == boot_flash_type) {
                            opts = " ubi.mtd=/ ubi.block=0,rootfs";
                            device_path = "/dev/ubiblock0_";
                            minor_num = 0;
                        }
                        break;
                    case FS_TYPE_EXT4:
                        rootfstype = "ext4";
                        opts = " ro";
                        break;
                    case FS_TYPE_UBIFS:
                        rootfstype = "ubifs";
                        opts = " rw ubi.mtd=/";
                        break;
                    default:
                        free(tmp_cmdline);
                        return RTK_PLAT_ERR_PARSE_FW_DESC;
                }

                if(FS_TYPE_UBIFS == part_entry[i].fw_type){
                snprintf(tmp_cmdline+cmd_len, 255-cmd_len,
                        "root=ubi0:rootfs%s rootfstype=%s ",
                        opts,rootfstype);
                }
                else{
                    snprintf(tmp_cmdline+cmd_len, 255-cmd_len,
                            "root=%s%d%s rootfstype=%s rootwait ",
                            device_path,minor_num,opts,rootfstype);
                }
                debug("NASROOT found. cmd:%s\n", tmp_cmdline);
            }
            else if (0 == strcmp((char *)part_entry[i].mount_point, NAS_ETC)
                    && FS_TYPE_UBIFS == part_entry[i].fw_type){
                int cmd_len = strlen(tmp_cmdline);
                snprintf(tmp_cmdline+cmd_len, 255-cmd_len,
                        "ubi.mtd=etc ");
                debug("NASETC found. cmd:%s\n", tmp_cmdline);
            }
        }
    }
    setenv("nas_part", tmp_cmdline);
    free(tmp_cmdline);

    return RTK_PLAT_ERR_OK;
}
#endif

/*
 * Use firmware description table to read images from usb.
 */
int rtk_plat_read_fw_image_from_USB(int skip)
{
#ifdef CONFIG_BOOT_FROM_USB
	char tmpbuf[128];
	int ret = RTK_PLAT_ERR_OK;
	char *filename;
	unsigned int secure_mode=0;

	secure_mode = rtk_get_secure_boot_type();

	run_command("usb start", 0);	/* "usb start" always return 0 */
	if (run_command("usb dev", 0) != 0) {
		printf("No USB device found!\n");
		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}

	if(!skip) /* dtb */
	{
		if(boot_mode == BOOT_RESCUE_MODE || boot_mode == BOOT_ANDROID_MODE)
			filename = rtk_plat_prepare_fw_image_from_USB(FW_TYPE_RESCUE_DT);
		else
			filename = rtk_plat_prepare_fw_image_from_USB(FW_TYPE_KERNEL_DT);
		if(secure_mode == RTK_SECURE_BOOT)
		{
			if (rtk_decrypt_rescue_from_usb(filename, getenv_ulong("fdt_loadaddr", 16, 0)))
			goto loading_failed;
		}
		else
		{
			sprintf(tmpbuf, "fatload usb 0:1 %s %s", getenv("fdt_loadaddr"), filename);
			if (run_command(tmpbuf, 0) != 0) {
				goto loading_failed;
			}
		}

		printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("fdt_loadaddr"));
	}

	/* Linux kernel */
	filename = rtk_plat_prepare_fw_image_from_USB(FW_TYPE_KERNEL);
	if(secure_mode == RTK_SECURE_BOOT)
	{
		if (rtk_decrypt_rescue_from_usb(filename,getenv_ulong("kernel_loadaddr", 16, 0)))
		goto loading_failed;
	}
	else
	{
		sprintf(tmpbuf, "fatload usb 0:1 %s %s", getenv("kernel_loadaddr"), filename);
		if (run_command(tmpbuf, 0) != 0) {
			goto loading_failed;
		}
	}

	printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("kernel_loadaddr"));

	/* rootfs */
	if(boot_mode == BOOT_RESCUE_MODE || boot_mode == BOOT_ANDROID_MODE)
		filename = rtk_plat_prepare_fw_image_from_USB(FW_TYPE_RESCUE_ROOTFS);
	else
		/* No initrd on NAS normal boot */
		filename = rtk_plat_prepare_fw_image_from_USB(FW_TYPE_KERNEL_ROOTFS);
	if(secure_mode == RTK_SECURE_BOOT)
	{
		if (rtk_decrypt_rescue_from_usb(filename, getenv_ulong("rootfs_loadaddr", 16, 0)))
		goto loading_failed;
	}
	else
	{
		sprintf(tmpbuf, "fatload usb 0:1 %s %s", getenv("rootfs_loadaddr"), filename);
		if (run_command(tmpbuf, 0) != 0) {
			goto loading_failed;
		}
	}

	printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("rootfs_loadaddr"));

	/* audio firmware */
	filename = rtk_plat_prepare_fw_image_from_USB(FW_TYPE_AUDIO);
	if(secure_mode == RTK_SECURE_BOOT)
	{
		if (!rtk_decrypt_rescue_from_usb(filename, MIPS_AUDIO_FW_ENTRY_ADDR))
		{
			printf("Loading \"%s\" to 0x%08x is OK.\n", filename, MIPS_AUDIO_FW_ENTRY_ADDR);
			run_command("go a", 0);
		}
		else
			printf("Loading \"%s\" from USB failed.\n", filename);
			/* Go on without Audio firmware. */
	}
	else
	{
		sprintf(tmpbuf, "fatload usb 0:1 0x%08x %s", MIPS_AUDIO_FW_ENTRY_ADDR, filename);
		if (run_command(tmpbuf, 0) == 0) {
			printf("Loading \"%s\" to 0x%08x is OK.\n", filename, MIPS_AUDIO_FW_ENTRY_ADDR);
			run_command("go a", 0);
		}
		else {
			printf("Loading \"%s\" from USB failed.\n", filename);
			/* Go on without Audio firmware. */
		}
    }

#if defined(CONFIG_RTK_ARM32) || defined(CONFIG_CPU_V7)
	ret = rtk_call_bootm();
#else
	ret = rtk_call_booti();
#endif
	/* Should not reach here */

	return ret;

loading_failed:
	printf("Loading \"%s\" from USB failed.\n", filename);
	return RTK_PLAT_ERR_READ_RESCUE_IMG;

#endif /* CONFIG_BOOT_FROM_USB */

	return RTK_PLAT_ERR_OK;
}


int rtk_plat_get_dtb_target_address(int dtb_address)
{
	if( (CONFIG_FDT_LOADADDR<= dtb_address) && (dtb_address < CONFIG_LOGO_LOADADDR))
		return dtb_address;
	else
		{
			printf("original DT address=%x\n",dtb_address);
			return CONFIG_FDT_LOADADDR;
		}
}

#ifdef CONFIG_PRELOAD_BOOT_IMAGES
int rtk_preload_bootimages(void)
{
#ifdef CONFIG_RTK_MMC
	uint block_no=0, img_addr=0, img_size=0;
#endif

#if  defined(CONFIG_PRELOAD_UBOOT_EMMC_ADDR) && defined(CONFIG_RTK_MMC)
	block_no = CONFIG_PRELOAD_UBOOT_EMMC_ADDR / EMMC_BLOCK_SIZE;
	img_addr = getenv_ulong("bootcode2ndtmp_loadaddr", 16, 0);
	img_size = SZ_1M;
	printf("%s : load U-Boot 64 from 0x%08x to 0x%08x with size 0x%08x\n", __func__, block_no, img_addr, img_size);
	if(!rtk_eMMC_read(block_no, img_size, img_addr)) {
		printf("Error!!!\n");
		return RTK_PLAT_ERR_READ_FW_IMG;
	}
#endif
#if defined(CONFIG_PRELOAD_KERNEL_EMMC_ADDR) && defined(CONFIG_RTK_MMC)
	block_no = CONFIG_PRELOAD_KERNEL_EMMC_ADDR / EMMC_BLOCK_SIZE;
	img_addr = getenv_ulong("kernel_loadaddr", 16, 0);
	img_size = 7 * SZ_1M;
	printf("%s : load Kernel from 0x%08x to 0x%08x with size 0x%08x\n", __func__, block_no, img_addr, img_size);
	if(!rtk_eMMC_read(block_no, img_size, img_addr)) {
		printf("Error!!!\n");
		return RTK_PLAT_ERR_READ_FW_IMG;
	}
#endif
#if defined(CONFIG_PRELOAD_DTB_EMMC_ADDR) && defined(CONFIG_RTK_MMC)
	block_no = CONFIG_PRELOAD_DTB_EMMC_ADDR / EMMC_BLOCK_SIZE;
	img_addr = getenv_ulong("fdt_loadaddr", 16, 0);
	img_size = SZ_32K;
	printf("%s : load Kernel from 0x%08x to 0x%08x with size 0x%08x\n", __func__, block_no, img_addr, img_size);
	if(!rtk_eMMC_read(block_no, img_size, img_addr)) {
		printf("Error!!!\n");
		return RTK_PLAT_ERR_READ_FW_IMG;
	}
#endif

	return 0;
}
#endif

void GetKeyFromSRAM(unsigned int sram_addr, unsigned char* key, unsigned int length)
{
        //#define REG8( addr )		(*(volatile unsigned int*) (addr))

        int i = 0;

        for(i = 0; i < length; i++) {
            *(key + i) = REG8((uintptr_t)sram_addr + i);
        }
}

#if defined(CONFIG_SYS_RTK_SD_FLASH) || defined(CONFIG_SYS_RTK_EMMC_FLASH) || defined(CONFIG_BOOT_FROM_SPI) || defined(CONFIG_SYS_RTK_NAND_FLASH)
//#ifndef NAS_DUAL
/* Rescue-ROOTFS has different load addr for B00 compatible. */
/* B00 rescue-rootfs is preload on DDR before entering LK.   */
/* LK will then copy img from fw-tbl-addr to final addr.     */
/* Uboot for A00/01 could just load it on default address.   */
static unsigned int get_rescue_rootfs_addr(unsigned int fw_tbl_addr)
{
	unsigned int final_addr = getenv_ulong("rescue_rootfs_loadaddr", 16, 0);

	if (final_addr == 0)
		final_addr = CONFIG_RESCUE_ROOTFS_LOADADDR;

	if (fw_tbl_addr != final_addr)
		printf("change recue-rootfs addr from 0x%08x to 0x%08x\n", fw_tbl_addr, final_addr);

	return final_addr;
}
//#endif
#ifdef CONFIG_BFS_SUPPORT_KERNEL_ROOTFS
static unsigned int get_kernel_rootfs_addr(unsigned int fw_tbl_addr)
{
	unsigned int final_addr = getenv_ulong("rootfs_loadaddr", 16, 0);

	if (final_addr == 0)
		final_addr = CONFIG_ROOTFS_LOADADDR;

	if (fw_tbl_addr != final_addr)
		printf("change kernel-rootfs addr from 0x%08x to 0x%08x\n", fw_tbl_addr, final_addr);

	return final_addr;
}
#endif
#endif

int bootimg_parsing(unsigned char entry_type, unsigned int entry_target_addr)
{
	/* Parsing android P flash layout */
	char buff[32] = "";
	unsigned int image_addr, image_entry = 0;
	int ret, page_size = 2048;
	boot_img_hdr * BOOT_IMAGE_HDR;
	block_dev_desc_t *dev_desc;
	disk_partition_t info;

	/* check the magic number for this format */
	BOOT_IMAGE_HDR = (boot_img_hdr *)(uintptr_t)entry_target_addr;
	if (memcmp(BOOT_IMAGE_HDR->magic, BOOT_MAGIC, BOOT_MAGIC_SIZE)) {
		printf("Bad Android BOOT MAGIC!!\n");
		return 1;
	}

	/* Doing vbmeta verify for android P */
	if (entry_type == FW_TYPE_BOOT_IMAGE) {
		run_command_list("avb init 0", -1, 0);
		run_command_list("avb verify", -1, 0);

		/* The dtbo.img in rescue mode is different from normal mode
		 * Normal mode use dtbo.img burn in partition.
		 */
		dev_desc = get_dev("mmc", 0);
		ret = get_partition_info_efi_by_name(dev_desc, "dtbo", &info);
		if (ret == 0) {
			printf("------------dtbo partition found\n");
			rtk_eMMC_read(info.start, EMMC_BLOCK_SIZE * 10, (unsigned int *)getenv_ulong("dtbo_loadaddr", 16, 0x26400000));
		}
	}

	/* set up the image entry */
	image_entry = entry_target_addr;

	/* get kernel loading addr and size */
	image_addr = BOOT_IMAGE_HDR->kernel_addr & 0x0fffffff; /* mask the default value */
	image_entry = image_entry + page_size; /* skip image header size */
#if defined(CONFIG_RTK_ARM32) || defined(CONFIG_CPU_V7)
	image_addr = getenv_ulong("kernel_loadaddr", 16, image_addr);
#endif
	memcpy((void*)(uintptr_t)image_addr, (void*)(uintptr_t)image_entry, BOOT_IMAGE_HDR->kernel_size);
	snprintf(buff, 32, "0x%08llx", (unsigned long long)image_addr);
	setenv("kernel_loadaddr", (char *) buff);
	printf("Kernel:\n");
	printf("\t FW Image to 0x%08x, size=0x%08x (0x%08x)\n",
		image_addr, BOOT_IMAGE_HDR->kernel_size,
		image_addr + BOOT_IMAGE_HDR->kernel_size);
	printf("\t FW Image fr 0x%08x \n", image_entry);

	/* move the number of kerenl page size to next file */
	image_entry = image_entry + ((BOOT_IMAGE_HDR->kernel_size + page_size -1) / page_size) * page_size;

	/* Normal mode doesn't have rootfs */
	if (entry_type == FW_TYPE_RESCUE_IMAGE || entry_type == FW_TYPE_GOLD_IMAGE) {
		/* get rootfs loading addr and size */
		image_addr = BOOT_IMAGE_HDR->ramdisk_addr & 0x0fffffff;
		memcpy((void*)(uintptr_t)image_addr, (void*)(uintptr_t)image_entry, BOOT_IMAGE_HDR->ramdisk_size);
		snprintf(buff, 32, "0x%08llx", (unsigned long long)image_addr);
		setenv("rootfs_loadaddr", (char *) buff);
		printf("ROOTFS:\n");
		printf("\t FW Image to 0x%08x, size=0x%08x (0x%08x)\n",
			image_addr, BOOT_IMAGE_HDR->ramdisk_size,
			image_addr + BOOT_IMAGE_HDR->ramdisk_size);
		printf("\t FW Image fr 0x%08x \n", image_entry);

		/* move the number of rootfs page size to next file */
		image_entry = image_entry + ((BOOT_IMAGE_HDR->ramdisk_size + page_size -1) / page_size) * page_size;
	}

	/* get dtb loading addr and size */
	image_addr = BOOT_IMAGE_HDR->second_addr & 0x0fffffff;
	memcpy((void*)(uintptr_t)image_addr, (void*)(uintptr_t)image_entry, BOOT_IMAGE_HDR->second_size);
	snprintf(buff, 32, "0x%08llx", (unsigned long long)image_addr);
	setenv("fdt_loadaddr", (char *) buff);
	printf("DTB:\n");
	printf("\t FW Image to 0x%08x, size=0x%08x (0x%08x)\n",
		image_addr, BOOT_IMAGE_HDR->second_size,
		image_addr + BOOT_IMAGE_HDR->second_size);
	printf("\t FW Image fr 0x%08x \n", image_entry);

	/* Set the address of device tree */
	snprintf(buff, sizeof(buff) -1, "fdt addr 0x%x", image_addr);
	run_command_list(buff, -1, 0);

	/* get dtbo offset and size */
	if (entry_type == FW_TYPE_RESCUE_IMAGE || entry_type == FW_TYPE_GOLD_IMAGE) {
		/* move the number of dtb page size to next file */
		image_entry = image_entry + ((BOOT_IMAGE_HDR->second_size + page_size -1) / page_size) * page_size;

		/* get dtb loading addr and size */
		image_addr = getenv_ulong("dtbo_loadaddr", 16, 0x26400000);
		memcpy((void*)(uintptr_t)image_addr, (void*)(uintptr_t)image_entry, BOOT_IMAGE_HDR->recovery_dtbo_size);
		snprintf(buff, 32, "0x%08llx", (unsigned long long)image_addr);
		setenv("dtbo_loadaddr", (char *) buff);
		printf("DTBO:\n");
		printf("\t FW Image to 0x%08x, size=0x%08x (0x%08x)\n",
			image_addr, BOOT_IMAGE_HDR->recovery_dtbo_size,
			image_addr + BOOT_IMAGE_HDR->recovery_dtbo_size);
		printf("\t FW Image fr 0x%08x \n", image_entry);
	}

	/* Get each dtbo address and doing apply */
	/* Parse the dtbo start address of desire index */
	snprintf(buff, sizeof(buff) -1, "dtimg start 0x%x %d dtbo_addr", (unsigned int)getenv_ulong("dtbo_loadaddr", 16, 0x26400000), DTBO_INDEX);
	run_command_list(buff, -1, 0);
	image_addr = getenv_ulong("dtbo_addr", 16, 0);
	if (image_addr != 0) {
		snprintf(buff, 32, "fdt apply 0x%x", image_addr);
		run_command_list(buff, -1, 0);
		printf("Apply the index %d of dtbo\n", DTBO_INDEX);
	}

	return 0;
}

/*
 * Use firmware description table to read images from eMMC flash.
 */
int rtk_plat_read_fw_image_from_eMMC(
		uint fw_desc_table_base, part_desc_entry_v1_t* part_entry, int part_count,
		void* fw_entry, int fw_count,
		uchar version)
{
#ifdef CONFIG_SYS_RTK_EMMC_FLASH
	void *this_entry;
	fw_desc_entry_v11_t *v11_entry;
	fw_desc_entry_v12_t *v12_entry;
	int i;
#ifndef BYPASS_CHECKSUM	
	int j;
#endif
	uint unit_len;
	char buf[64];
#ifndef BYPASS_CHECKSUM	
	uint fw_checksum = 0;
#endif	
	unsigned char ks[16],kh[16],kimg[16];
	unsigned char aes_key[16];
	unsigned char rsa_key[256];
#ifndef BYPASS_CHECKSUM	
	unsigned char sha_hash[32];
#endif	
	unsigned char aes_key_addr[16];
	unsigned int secure_mode;
#ifdef CONFIG_CMD_KEY_BURNING
	unsigned int * Kh_key_ptr = NULL;
#else
	unsigned int * Kh_key_ptr = (unsigned int *)(uintptr_t) Kh_key_default;
#endif
	unsigned int img_truncated_size; // install_a will append 256-byte signature data to it
	unsigned int vo_secure_addr;
	unsigned int fw_length = 0;
	int ret;
	boot_av_info_t *boot_av;
	//uint target_addr;
	uint block_no;
	MEM_LAYOUT_WHEN_READ_IMAGE_T mem_layout;
	uint imageSize = 0;
	uint decompressedSize = 0;

	// extern variable
	extern unsigned int mcp_dscpt_addr;
	mcp_dscpt_addr = 0;

	secure_mode = rtk_get_secure_boot_type();
	img_truncated_size = RSA_SIGNATURE_LENGTH*2+NP_INV32_LENGTH;

	unsigned char str[16];// old array size is 5, change to 16. To avoid the risk in memory overlap.

	uchar entry_type = 0;
	uchar entry_lzma = 0;
	uint entry_target_addr = 0;
	u64 entry_offset = 0;
	uint entry_length = 0;
	char tmpbuf[128] __maybe_unused;

	/* find fw_entry structure according to version */
	switch (version)
	{
		case FW_DESC_TABLE_V1_T_VERSION_1:
			unit_len = sizeof(fw_desc_entry_v1_t);
			break;

		case FW_DESC_TABLE_V1_T_VERSION_11:
			unit_len = sizeof(fw_desc_entry_v11_t);
			break;

		case FW_DESC_TABLE_V1_T_VERSION_21:
			unit_len = sizeof(fw_desc_entry_v21_t);
			break;

		case FW_DESC_TABLE_V2_T_VERSION_2:
			unit_len = sizeof(fw_desc_entry_v2_t);
			break;

		case FW_DESC_TABLE_V2_T_VERSION_12:
			unit_len = sizeof(fw_desc_entry_v12_t);
			break;

		case FW_DESC_TABLE_V2_T_VERSION_22:
			UBOOT_NORMAL_BOOT = 0;
			unit_len = sizeof(fw_desc_entry_v22_t);
			break;

		default:
			return RTK_PLAT_ERR_READ_FW_IMG;
	}

	/* clear boot_av_info memory */
	/* When accelerating logo, not to clear boot info again */
	if(accelerate_state == 0 || accelerate_state == 1){
		boot_av = (boot_av_info_t *) MIPS_BOOT_AV_INFO_ADDR;
		memset(boot_av, 0, sizeof(boot_av_info_t));
	}

	/* parse each fw_entry */
	for (i = 0; i < fw_count; i++)
	{
		EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here

		this_entry = (fw_entry + unit_len * i);
		FW_ENTRY_MEMBER_GET(entry_target_addr, this_entry, target_addr, version);
		FW_ENTRY_MEMBER_GET(entry_type, this_entry, type, version);
		FW_ENTRY_MEMBER_GET(entry_length, this_entry, length, version);
		FW_ENTRY_MEMBER_GET(entry_offset, this_entry, offset, version);
		FW_ENTRY_MEMBER_GET(entry_lzma, this_entry, lzma, version);

		if (1 == accelerate_state && entry_type != FW_TYPE_AUDIO && entry_type != FW_TYPE_IMAGE_FILE)
			continue;
		else if (2 == accelerate_state && (entry_type == FW_TYPE_AUDIO || entry_type == FW_TYPE_IMAGE_FILE))
			continue;
		if (audio_fw_state && (entry_type == FW_TYPE_AUDIO || entry_type == FW_TYPE_GOLD_AUDIO))
			continue;
		/*The condition for decision the order of loading FW*/

#if defined(NAS_ENABLE) && defined(CONFIG_RTD161x)
		if (skip_avfw_entry) {
			if ( entry_type == FW_TYPE_AUDIO || entry_type == FW_TYPE_IMAGE_FILE ) {
				continue;
			}
		}
#endif
		if ( entry_type == FW_TYPE_AUDIO || entry_type == FW_TYPE_GOLD_AUDIO)
			Auto_AFW_MEM_START = entry_target_addr;
		/* Save the address of AFW from fw_desc */

		if (entry_target_addr)
		{
			if (boot_mode == BOOT_RESCUE_MODE || boot_mode == BOOT_ANDROID_MODE)
			{
				switch(entry_type)
				{
					case FW_TYPE_KERNEL:
						memset(str, 0, sizeof(str));
#if defined(CONFIG_RTK_ARM32) || defined(CONFIG_CPU_V7)
						entry_target_addr = getenv_ulong("kernel_loadaddr", 16, entry_target_addr);
#endif
						sprintf((char *)str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("kernel_loadaddr", (char *) str);
						printf("Kernel:\n");
						break;

					case FW_TYPE_RESCUE_DT:
						entry_target_addr = rtk_plat_get_dtb_target_address(entry_target_addr);
						FW_ENTRY_MEMBER_SET(entry_target_addr, this_entry, target_addr, version);
						memset(str, 0, sizeof(str));
						sprintf((char *) str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("fdt_loadaddr",(char *) str);
						printf("Rescue DT:\n");
						break;

					case FW_TYPE_RESCUE_ROOTFS:
						printf("Rescue ROOTFS:\n");
						if(boot_mode == BOOT_BIST_MODE)
                            entry_target_addr = BIST_ROOTFS_ADDR;
                        else
						    entry_target_addr = get_rescue_rootfs_addr(entry_target_addr);
#ifdef NAS_ENABLE
						initrd_size = entry_length;
						if(secure_mode != NONE_SECURE_BOOT)
						{
							initrd_size -= img_truncated_size;
							/* Pad 1 ~ 64 bytes by do_sha256 */
							initrd_size -= 64;
						}
#endif
						sprintf(tmpbuf, "mw.b 0x%08x 0 0x%x", entry_target_addr, CONFIG_ROOTFS_RESCUE_SIZE);
						printf("\t Clear memory at 0x%08x, size=0x%08x (0x%08x)\n",
							entry_target_addr, CONFIG_ROOTFS_RESCUE_SIZE, entry_target_addr + CONFIG_ROOTFS_RESCUE_SIZE);
						run_command(tmpbuf, 0);
						break;

					case FW_TYPE_AUDIO:
						if(boot_mode == BOOT_KERNEL_ONLY_MODE)
							continue;
						else
						{
							ipc_shm.audio_fw_entry_pt = CPU_TO_BE32(entry_target_addr | MIPS_KSEG0BASE);
							printf("Audio FW:\n");
						}
						break;
                    case FW_TYPE_IMAGE_FILE:
						printf("IMAGE FILE:\n");
						entry_target_addr = getenv_ulong("blue_logo_loadaddr", 16, BOOT_LOGO_ADDR);
						vo_secure_addr = entry_target_addr + BOOT_LOGO_SIZE - 0x100000;
						memset((void *)(uintptr_t)vo_secure_addr, 0x0, sizeof(char)*VO_SECURE_SIZE);
						printf("Address for boot logo from %x to %x will be reserved.\n", (unsigned int)entry_target_addr,
							(unsigned int)(entry_target_addr + BOOT_LOGO_SIZE));
						/* assign boot_av structure */
						boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
						if(boot_logo_enable)
						{
							boot_av-> logo_enable = boot_logo_enable;
							boot_av-> logo_addr = CPU_TO_BE32(entry_target_addr);
							boot_av-> src_width = CPU_TO_BE32(custom_logo_src_width);
							boot_av-> src_height = CPU_TO_BE32(custom_logo_src_height);
							boot_av-> dst_width = CPU_TO_BE32(custom_logo_dst_width);
							boot_av-> dst_height = CPU_TO_BE32(custom_logo_dst_height);
							boot_av-> vo_secure_addr = CPU_TO_BE32((unsigned int)(uintptr_t)vo_secure_addr);
						}
						break;
					case FW_TYPE_RESCUE_IMAGE:
						printf("RESCUE_IMAGE:\n");
						break;
					case FW_TYPE_VIDEO:
						printf("Video:\n");
						break;
					default:
						//printf("Unknown FW (%d):\n", entry_type);
						continue;
				}
			}
#ifndef NAS_DUAL
			else if(boot_mode == BOOT_GOLD_MODE)
			{
				switch(entry_type)
				{
					case FW_TYPE_GOLD_KERNEL:
						memset(str, 0, sizeof(str));
#if defined(CONFIG_RTK_ARM32) || defined(CONFIG_CPU_V7)
						entry_target_addr = getenv_ulong("kernel_loadaddr", 16, entry_target_addr);
#endif
						sprintf((char *) str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("kernel_loadaddr",(char *) str);
						printf("GOLD Kernel:\n");
						break;
					case FW_TYPE_GOLD_RESCUE_DT:
						entry_target_addr = rtk_plat_get_dtb_target_address(entry_target_addr);
						FW_ENTRY_MEMBER_SET(entry_target_addr, this_entry, target_addr, version);
						memset(str, 0, sizeof(str));
						sprintf((char *) str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("fdt_loadaddr",(char *) str);
						printf("GOLD Rescue DT:\n");
						break;
					case FW_TYPE_GOLD_RESCUE_ROOTFS:
						printf("GOLD Rescue ROOTFS:\n");
						entry_target_addr = get_rescue_rootfs_addr(entry_target_addr);
						break;
					case FW_TYPE_GOLD_AUDIO:
						if(boot_mode == BOOT_KERNEL_ONLY_MODE)
							continue;
						else
						{
							ipc_shm.audio_fw_entry_pt = CPU_TO_BE32(entry_target_addr | MIPS_KSEG0BASE);
							printf("GOLD Audio FW:\n");
						}
						break;
					case FW_TYPE_GOLD_IMAGE:
						printf("GOLD_IMAGE:\n");
						break;
					case FW_TYPE_VIDEO:
						printf("Video:\n");
						break;
					default:
						//printf("Unknown FW (%d):\n", entry_type);
						continue;
				}
			}
#endif // NAS_DUAL
			else
			{
				switch(entry_type)
				{
					case FW_TYPE_BOOTCODE:
						printf("Boot Code:\n");
						break;

					case FW_TYPE_KERNEL:
						memset(str, 0, sizeof(str));
#if defined(CONFIG_RTK_ARM32) || defined(CONFIG_CPU_V7)
						entry_target_addr = getenv_ulong("kernel_loadaddr", 16, entry_target_addr);
#endif
						sprintf((char *) str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("kernel_loadaddr",(char *) str);
						printf("Kernel:\n");
						break;

					case FW_TYPE_KERNEL_DT:
						entry_target_addr = rtk_plat_get_dtb_target_address(entry_target_addr);
						FW_ENTRY_MEMBER_SET(entry_target_addr, this_entry, target_addr, version);
						memset(str, 0, sizeof(str));
						sprintf((char *) str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("fdt_loadaddr",(char *) str);
						printf("DT:\n");
						break;

					case FW_TYPE_KERNEL_ROOTFS:
						printf("ROOTFS:\n");
						break;

					case FW_TYPE_AUDIO:
						if(boot_mode == BOOT_KERNEL_ONLY_MODE)
							continue;
						else
						{
							ipc_shm.audio_fw_entry_pt = CPU_TO_BE32(entry_target_addr | MIPS_KSEG0BASE);
							printf("Audio FW:\n");
						}
						break;

					case FW_TYPE_JFFS2:
						printf("JFFS2 Image:\n");
						break;

					case FW_TYPE_SQUASH:
						printf("Squash Image:\n");
						break;

					case FW_TYPE_EXT3:
						printf("EXT3 Image:\n");
						break;

					case FW_TYPE_ODD:
						printf("ODD Image:\n");
						break;

					case FW_TYPE_YAFFS2:
						printf("YAFFS2 Image:\n");
						break;

					case FW_TYPE_AUDIO_FILE:
						//entry_target_addr = (POWER_ON_MUSIC_STREAM_ADDR | MIPS_KSEG0BASE);

						/* if enable boot music, need to assign boot_av structure */
						//boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
						//boot_av->dwAudioStreamAddress = SWAPEND32(entry_target_addr);
						//boot_av->dwAudioStreamLength = SWAPEND32(entry_length);
						//boot_av->dwAudioStreamVolume = (-17);
						break;

					case FW_TYPE_VIDEO_FILE:

						/* if enable boot video/jpeg, need to assign boot_av structure */
						//boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
						//boot_av->dwVideoStreamAddress = SWAPEND32(entry_target_addr);
						//boot_av->bPowerOnImage = 0;
						//boot_av->dwVideoStreamLength = SWAPEND32(entry_length);
						break;

					case FW_TYPE_IMAGE_FILE:
#ifdef NAS_ENABLE
						entry_target_addr = getenv_ulong("logo_loadaddr", 16, BOOT_LOGO_ADDR);
#else
						entry_target_addr = getenv_ulong("blue_logo_loadaddr", 16, BOOT_LOGO_ADDR);
#endif
						printf("IMAGE FILE:\n");
						vo_secure_addr = entry_target_addr + BOOT_LOGO_SIZE - 0x100000;
						memset((void *)(uintptr_t)vo_secure_addr, 0x0, sizeof(char)*VO_SECURE_SIZE);
						printf("Address for boot logo from %x to %x will be reserved.\n", (unsigned int)entry_target_addr,
							(unsigned int)(entry_target_addr + BOOT_LOGO_SIZE));
						/* assign boot_av structure */
						boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
						if(boot_logo_enable)
						{
							boot_av-> logo_enable = boot_logo_enable;
							boot_av-> logo_addr = CPU_TO_BE32(entry_target_addr);
							boot_av-> src_width = CPU_TO_BE32(custom_logo_src_width);
							boot_av-> src_height = CPU_TO_BE32(custom_logo_src_height);
							boot_av-> dst_width = CPU_TO_BE32(custom_logo_dst_width);
							boot_av-> dst_height = CPU_TO_BE32(custom_logo_dst_height);
							boot_av-> vo_secure_addr = CPU_TO_BE32((unsigned int)(uintptr_t)vo_secure_addr);
						}
						break;
					case FW_TYPE_UBOOT: // 2nd stage bootcode
#if defined CONFIG_SECOND_BOOTCODE_SUPPORT && defined CONFIG_GOLDENBOOT_SUPPORT
						// due to 2nd bootcode run at the same ADDR as 1st, load to other place first
						printf("Support BootCode64\n");
						continue;
						memset(str, 0, sizeof(str));
						sprintf(str, "%x", CONFIG_BOOTCODE_2ND_TMP_ADDR);
						setenv("bootcode2ndtmp_loadaddr", str);

						memset(str, 0, sizeof(str));
						sprintf(str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("bootcode2nd_loadaddr", str);
						printf("2nd BootCode:\n");

						FW_ENTRY_MEMBER_SET(CONFIG_BOOTCODE_2ND_TMP_ADDR, this_entry, target_addr, version);
#else
						printf("%s, 2nd bootloader not support!\n", __func__);
#endif
						break;
					case FW_TYPE_HYP:
						memset(str, 0, sizeof(str));
						sprintf((char *) str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("hyp_loadaddr",(char *) str);
						printf("Hypervisor:\n");
						break;
					case FW_TYPE_BOOT_IMAGE:
						printf("BOOT_IMAGE:\n");
						break;
					case FW_TYPE_VIDEO:
						printf("Video:\n");
						break;
					default:
						//printf("Unknown FW (%d):\n", entry_type);
						continue;
				}
			}
#ifndef CONFIG_RTD1295
#ifndef CONFIG_BOOTCODE_LOAD_AVFW
			// after 1395, audio fw belong to trusted fw and need to be loaded by FSBL
			if (entry_type == FW_TYPE_AUDIO || entry_type == FW_TYPE_GOLD_AUDIO || entry_type == FW_TYPE_VIDEO) {
				printf("\t FW Image preload on 0x%08x, size=0x%08x (0x%08x)\n",
					entry_target_addr, entry_length, entry_target_addr + entry_length);
				continue;
			}
#endif
#endif
#ifdef EMMC_BLOCK_LOG
			printf("\t FW Image to 0x%08x ~ 0x%08x, size=0x%08x, 0x%x blocks\n",
					entry_target_addr,
					entry_target_addr + entry_length,
					entry_length,
					(entry_length%EMMC_BLOCK_SIZE)?(entry_length/EMMC_BLOCK_SIZE)+1:(entry_length/EMMC_BLOCK_SIZE));
			printf("\t FW Image fr 0x%08Lx, blk 0x%x\n",
					entry_offset,
					(eMMC_fw_desc_table_start + entry_offset)/EMMC_BLOCK_SIZE);
#else
			// FW loading is performed else where(ex:fsbl) under Secure BOOT flow
			// LOGO image is not encryption file, so fsbl will not preload.
			if (!UBOOT_NORMAL_BOOT && entry_type != FW_TYPE_IMAGE_FILE ) {
				printf("\t Encrypted FW Image to 0x%08x, size=0x%08x (0x%08x)\n",
					entry_target_addr, entry_length,
					entry_target_addr + entry_length);
				printf("\t Encrypted FW Image fr 0x%08llx \n", entry_offset);
			}
			else {
				printf("\t FW Image to 0x%08x, size=0x%08x (0x%08x)\n",
						entry_target_addr, entry_length, entry_target_addr + entry_length);
				printf("\t FW Image fr 0x%08Lx \n", entry_offset);
			}
#endif

			WATCHDOG_KICK();

				/* secure mode and lzma will only apply to fw image */
				if (entry_type == FW_TYPE_KERNEL ||
					entry_type == FW_TYPE_KERNEL_ROOTFS ||
					entry_type == FW_TYPE_RESCUE_ROOTFS ||
					entry_type == FW_TYPE_AUDIO ||
					entry_type == FW_TYPE_GOLD_KERNEL ||
					entry_type == FW_TYPE_GOLD_RESCUE_ROOTFS ||
					entry_type == FW_TYPE_GOLD_AUDIO)
				{
					/* get memory layout before copy fw image */
					mem_layout.bIsEncrypted = (secure_mode != NONE_SECURE_BOOT);
					mem_layout.bIsCompressed = entry_lzma;
					mem_layout.image_target_addr = entry_target_addr & (~MIPS_KSEG_MSK);
				}
				else if (entry_type == FW_TYPE_IMAGE_FILE) {
					mem_layout.bIsEncrypted = (secure_mode != NONE_SECURE_BOOT);
					mem_layout.bIsCompressed = entry_lzma;
					mem_layout.image_target_addr = entry_target_addr;
				}
				else
				{
					/* get memory layout before copy other image */
					mem_layout.bIsEncrypted = 0;
					mem_layout.bIsCompressed = 0;

					mem_layout.image_target_addr = entry_target_addr;
				}

				get_mem_layout_when_read_image(&mem_layout);

				imageSize = entry_length;

				// 512B aligned
				if (imageSize&(EMMC_BLOCK_SIZE-1)) {
					imageSize &= ~(EMMC_BLOCK_SIZE-1);
					imageSize += EMMC_BLOCK_SIZE;
				}

				block_no = entry_offset / EMMC_BLOCK_SIZE;

				if (!rtk_eMMC_read(block_no, imageSize, (uint *)(uintptr_t)mem_layout.flash_to_ram_addr))
				{
					printf("[ERR] Read fw error (type:%d)!\n", entry_type);

					return RTK_PLAT_ERR_READ_FW_IMG;
				}

#ifndef BYPASS_CHECKSUM
				/* Check checksum */
				if (FW_DESC_BASE_VERSION(version) == FW_DESC_TABLE_V1_T_VERSION_1) {
					fw_checksum = get_checksum((uchar *)(uintptr_t)mem_layout.flash_to_ram_addr, entry_length);
					if (((fw_desc_entry_v1_t*)this_entry)->checksum != fw_checksum &&
						secure_mode!= RTK_SECURE_BOOT) {
						printf("\t FW Image checksum FAILED\n");
						printf("\t FW Image entry  checksum=0x%08x\n",
							((fw_desc_entry_v1_t*)this_entry)->checksum);
						printf("\t FW Image result checksum=0x%08x\n", fw_checksum);
						return RTK_PLAT_ERR_READ_FW_IMG;
					}
				} else if (FW_DESC_BASE_VERSION(version) == FW_DESC_TABLE_V2_T_VERSION_2) {
					SHA256_hash((uchar *)(uintptr_t)mem_layout.flash_to_ram_addr, entry_length, sha_hash, NULL);
					if ((memcmp(((fw_desc_entry_v2_t*)this_entry)->sha_hash, sha_hash, SHA256_SIZE) != 0) &&
						secure_mode!= RTK_SECURE_BOOT) {
						printf("\t FW Image sha FAILED\n");
						printf("\t FW Image entry sha256==>\n");
						for (j = 0 ; j < 32 ; j++)
							printf("%02x ", ((fw_desc_entry_v2_t*)this_entry)->sha_hash[j]);
						printf("\n\t FW Image result sha256==>\n");
						for (j = 0 ; j < 32 ; j++)
							printf("%02x ", sha_hash[j]);
						printf("\n");
						return RTK_PLAT_ERR_READ_FW_IMG;
					}
				}
#endif

				/* UBoot doing decryption */
				OTP_GET_BYTE(AES_KEY_OFFSET, aes_key_addr, 16);
				if (!UBOOT_NORMAL_BOOT && entry_type != FW_TYPE_IMAGE_FILE) {
					if(!decrypt_image(UINT32_PTR(entry_target_addr), UINT32_PTR(entry_target_addr), entry_length - AES_TRUNCATED_SIZE, UINT32_PTR(aes_key_addr))){
						fw_length = SWAPEND32(REG32((uintptr_t)(entry_target_addr + entry_length - AES_TRUNCATED_SIZE - FW_SIZE_OFFSET))) >> 3; /*bit length / 8 = byte length*/
						if (Verify_SHA256_hash(UINT32_PTR(entry_target_addr), fw_length, UINT32_PTR(entry_target_addr + entry_length - AES_TRUNCATED_SIZE), 1, UINT32_PTR(RSA_KEY_ADDR))){
							return RTK_PLAT_ERR_READ_FW_IMG;
						}
					} else {
						return RTK_PLAT_ERR_READ_FW_IMG;
					}
				}

				/* Parsing android P flash layout */
				if (entry_type == FW_TYPE_BOOT_IMAGE || entry_type == FW_TYPE_RESCUE_IMAGE ||
					entry_type == FW_TYPE_GOLD_IMAGE) {
					if(bootimg_parsing(entry_type, entry_target_addr))
						return RTK_PLAT_ERR_READ_FW_IMG;
				}

				/* if secure mode, do AES CBC decrypt */
				if (mem_layout.bIsEncrypted)
				{
					if (secure_mode == RTK_SECURE_BOOT)
					{
					    unsigned int real_body_size = 0;
						//rtk_hexdump("the first 32-byte encrypted data", (unsigned char *)mem_layout.encrpyted_addr, 32);
						//rtk_hexdump("the last 512-byte encrypted data", (unsigned char *)(ENCRYPTED_LINUX_KERNEL_ADDR+entry_length-512), 512);

                        memset(ks,0x00,16);
                        memset(kh,0x00,16);
                        memset(kimg,0x00,16);

                        memset(aes_key, 0x00, 16);
                        memset(rsa_key, 0x00, 256);

                        switch(entry_type)
                        {
                            case FW_TYPE_KERNEL:
                            case FW_TYPE_RESCUE_ROOTFS:
                            case FW_TYPE_KERNEL_ROOTFS:
                            case FW_TYPE_AUDIO:
                            case FW_TYPE_GOLD_KERNEL:
                            case FW_TYPE_GOLD_RESCUE_ROOTFS:
                            case FW_TYPE_GOLD_AUDIO:
                                GetKeyFromSRAM(KH_P_SRAM_ADDR, aes_key, AES_KEY_SIZE);
                                GetKeyFromSRAM(RSA_KEY_FW_SRAM_ADDR, rsa_key, RSA_KEY_SIZE);
                                flush_cache((unsigned long) aes_key, AES_KEY_SIZE);
                                flush_cache((unsigned long) aes_key, RSA_KEY_SIZE);
                                sync();
                                //rtk_hexdump("kh_p : ", aes_key, AES_KEY_SIZE);
                                //rtk_hexdump("rsa_key_fw : ", rsa_key, RSA_KEY_SIZE);
                                break;
                            case FW_TYPE_TEE:
                                GetKeyFromSRAM(KX_P_SRAM_ADDR, aes_key, AES_KEY_SIZE);
                                GetKeyFromSRAM(RSA_KEY_TEE_SRAM_ADDR, rsa_key, RSA_KEY_SIZE);
                                flush_cache((unsigned long) aes_key, AES_KEY_SIZE);
                                flush_cache((unsigned long) aes_key, RSA_KEY_SIZE);
                                sync();
                                //rtk_hexdump("kx_p : ", aes_key, 16);
                                //rtk_hexdump("rsa_key_tee : ", rsa_key, RSA_KEY_SIZE);
                                break;
                            default:
                                break;
                        }

#ifdef CONFIG_CMD_KEY_BURNING
                        OTP_Get_Byte(OTP_K_S, ks, 16);
                        OTP_Get_Byte(OTP_K_H, kh, 16);
                        sync();
						flush_cache((unsigned int) (uintptr_t)ks, 16);
						flush_cache((unsigned int) (uintptr_t)kh, 16);
#endif
                        AES_ECB_encrypt(ks, 16, kimg,(unsigned int *) kh);
						flush_cache((unsigned long) kimg, 16);
                        sync();

                        Kh_key_ptr = (unsigned int *) kimg;
                        Kh_key_ptr = (unsigned int *) aes_key;
                        //Kh_key_ptr[0] = swap_endian(Kh_key_ptr[0]);
                        //Kh_key_ptr[1] = swap_endian(Kh_key_ptr[1]);
                        //Kh_key_ptr[2] = swap_endian(Kh_key_ptr[2]);
                        //Kh_key_ptr[3] = swap_endian(Kh_key_ptr[3]);
						flush_cache((unsigned long) aes_key, 16);

						// decrypt image
						printf("to decrypt...\n");

						flush_cache((unsigned int) mem_layout.encrpyted_addr, entry_length);

						if (decrypt_image((char *)(uintptr_t)mem_layout.encrpyted_addr,
							(char *)(uintptr_t)mem_layout.decrypted_addr,
							entry_length  - img_truncated_size,
							Kh_key_ptr))
						{
							printf("decrypt image(%d) error!\n", entry_type);
							return RTK_PLAT_ERR_READ_FW_IMG;
						}

						sync();
                        memset(ks,0x00,16);
                        memset(kh,0x00,16);
                        memset(kimg,0x00,16);

						//rtk_hexdump("the first 32-byte decrypted data", (unsigned char *)mem_layout.decrypted_addr, 32);

						//reverse_signature( (unsigned char *)(mem_layout.decrypted_addr + imageSize - img_truncated_size) );

                        copy_memory( (void *)(uintptr_t)(mem_layout.decrypted_addr + entry_length - img_truncated_size), (void *)(uintptr_t)(mem_layout.encrpyted_addr + entry_length - img_truncated_size), img_truncated_size);
                        flush_cache((unsigned int) mem_layout.decrypted_addr, entry_length);

                        real_body_size = (UINT32)(REG32( (uintptr_t)(mem_layout.decrypted_addr + (entry_length - img_truncated_size) - 4) ));
                        real_body_size = swap_endian(real_body_size);
                    	real_body_size /= 8;

						flush_cache((unsigned int) mem_layout.decrypted_addr, entry_length);
						ret = Verify_SHA256_hash( (unsigned char *)(uintptr_t)mem_layout.decrypted_addr,
												  real_body_size,
												  (unsigned char *)(uintptr_t)(mem_layout.decrypted_addr + entry_length - img_truncated_size),
												  1, rsa_key);
						if( ret < 0 ) {
							printf("[ERR] %s: verify hash fail(%d)\n", __FUNCTION__, ret );
							return RTK_PLAT_ERR_READ_FW_IMG;
						}

						//imageSize = imageSize - img_truncated_size - SHA256_SIZE;
					}
				}

				/* if lzma type, decompress image */
				if (mem_layout.bIsCompressed)
				{
					#ifndef CONFIG_FT_RESCUE
					if (lzmaBuffToBuffDecompress((uchar*)(uintptr_t)mem_layout.decompressed_addr, (SizeT *)&decompressedSize, (uchar*)(uintptr_t)mem_layout.compressed_addr, imageSize) != 0)
					{
						printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);

						return RTK_PLAT_ERR_READ_FW_IMG;
					}
					#endif //CONFIG_FT_RESCUE
				}
		}
	}



	if (accelerate_state)
		accelerate_state++;
	/*The accelerate_flag for faster blue logo*/

	if (version == FW_DESC_TABLE_V1_T_VERSION_11)
	{
		v11_entry = (fw_desc_entry_v11_t*) (fw_entry + unit_len * i);

		if (v11_entry->act_size != 0)
		{
			// string format: "part_num:act_size:hash,"
			memset(buf, 0, sizeof(buf));
			sprintf(buf, "%d:%d:", v11_entry->part_num, v11_entry->act_size);
			memset(buf, 0, sizeof(buf));
			memcpy(buf, v11_entry->hash, sizeof(v11_entry->hash));
			buf[sizeof(v11_entry->hash)] = ',';
		}
	}
	else if (version == FW_DESC_TABLE_V2_T_VERSION_12)
	{
		v12_entry = (fw_desc_entry_v12_t*) (fw_entry + unit_len * i);

		if (v12_entry->act_size != 0)
		{
			// string format: "part_num:act_size:hash,"
			memset(buf, 0, sizeof(buf));
			sprintf(buf, "%d:%d:", v12_entry->part_num, v12_entry->act_size);
			memset(buf, 0, sizeof(buf));
			memcpy(buf, v12_entry->hash, sizeof(v12_entry->hash));
			buf[sizeof(v12_entry->hash)] = ',';
		}
	}

	/* set boot_av_info_ptr */
	if (boot_av->dwMagicNumber == SWAPEND32(BOOT_AV_INFO_MAGICNO))
	{
		boot_av->bHDMImode = sys_logo_is_HDMI;// ignored.

		// enable audio sound
		if (boot_av->dwAudioStreamLength != 0)
		{
			;
		}

		ipc_shm.pov_boot_av_info = SWAPEND32((uint)(uintptr_t) boot_av);

		#ifdef DUBUG_BOOT_AV_INFO
		dump_boot_av_info(boot_av);
		#endif
	}

	/* Flush caches */
	flush_dcache_all();

#endif /* CONFIG_SYS_RTK_EMMC_FLASH */

	return RTK_PLAT_ERR_OK;
}

/*
 * Use firmware description table to read images from NAND flash.
 */
int rtk_plat_read_fw_image_from_NAND(
		uint fw_desc_table_base, part_desc_entry_v1_t* part_entry, int part_count,
		void* fw_entry, int fw_count,
		uchar version)
{
	int ret = RTK_PLAT_ERR_OK;
#ifdef CONFIG_SYS_RTK_NAND_FLASH
	void *this_entry;
	int i, j;
	uint unit_len;
	uint fw_checksum = 0;
	unsigned int secure_mode;
	unsigned int vo_secure_addr;
	unsigned int fw_length = 0;
	unsigned char sha_hash[32];
	unsigned char aes_key_addr[16];
	boot_av_info_t *boot_av;
	MEM_LAYOUT_WHEN_READ_IMAGE_T mem_layout;
	uint imageSize = 0;
	uint decompressedSize = 0;
	struct mtd_info *mtd = &nand_info[nand_curr_device];
	size_t rwsize;
	char buf[64];
	char tmp[16];
	char *tmp_cmdline = NULL;
	u64 size;
	char str[16];// old array size is 5, change to 16. To avoid the risk in memory overlap.
#ifndef CONFIG_TARGET_RTD1295
	unsigned long used_size = 0;
	unsigned long nand_size = 0;
#else
	unsigned char empty_mount[sizeof(part_entry->mount_point)] = {0};
#endif
	uchar entry_type = 0;
	uchar entry_lzma = 0;
	uint entry_target_addr = 0;
	u64 entry_offset = 0;
	uint entry_length = 0;
	char tmpbuf[128];

	secure_mode = rtk_get_secure_boot_type();

	/* find fw_entry structure according to version */
	switch (version)
	{
		case FW_DESC_TABLE_V1_T_VERSION_1:
			unit_len = sizeof(fw_desc_entry_v1_t);
			break;

		case FW_DESC_TABLE_V1_T_VERSION_11:
			unit_len = sizeof(fw_desc_entry_v11_t);
			break;

		case FW_DESC_TABLE_V1_T_VERSION_21:
			unit_len = sizeof(fw_desc_entry_v21_t);
			break;

		case FW_DESC_TABLE_V2_T_VERSION_2:
			unit_len = sizeof(fw_desc_entry_v2_t);
			break;

		case FW_DESC_TABLE_V2_T_VERSION_12:
			unit_len = sizeof(fw_desc_entry_v12_t);
			break;

		case FW_DESC_TABLE_V2_T_VERSION_22:
			UBOOT_NORMAL_BOOT = 0;
			unit_len = sizeof(fw_desc_entry_v22_t);
			break;

		default:
			return RTK_PLAT_ERR_READ_FW_IMG;
	}

	/* clear boot_av_info memory */
	boot_av = (boot_av_info_t *) MIPS_BOOT_AV_INFO_ADDR;
	memset(boot_av, 0, sizeof(boot_av_info_t));

	/* Add mtd_part env var */
	if(boot_mode != BOOT_RESCUE_MODE && boot_mode != BOOT_GOLD_MODE)
	{
#ifndef CONFIG_TARGET_RTD1295
		setenv("mtd_part", "mtdparts=rtk_nand:");

		for(i = 0; i < part_count; i++) {
			nand_size = nand_size + part_entry[i].length;
		}

		for(i = 0; i < part_count - 1; i++) {
                        //size = (part_entry[i].length >> 10);
                        size = part_entry[i].length;
                        memset(buf, 0, sizeof(buf));
                        memset(tmp, 0, sizeof(tmp));
                        snprintf(tmp, 16, "%llu", size);

			if (i == 0) {
				used_size = size;
				sprintf(buf, "%luk@0x0(rtk_nand)", nand_size >> 10);
			}
			else {
				sprintf(buf, ",%lluk@0x%lx(part%d)", size >> 10, used_size, i);
				used_size = used_size + size;
			}

			tmp_cmdline = (char *)malloc(strlen(getenv("mtd_part")) + 60);
                        if (!tmp_cmdline) {
                                printf("%s: Malloc failed\n", __func__);
                        } else {
				sprintf(tmp_cmdline, "%s%s", getenv("mtd_part"), buf);
                                setenv("mtd_part", tmp_cmdline);
                                free(tmp_cmdline);
                        }
                }

		printf("mtd_part:[%s]\n", getenv("mtd_part"));
#else
		for(i = 0; i < part_count; i++) {
			part_entry[i].length =BE64_TO_CPU(part_entry[i].length);
			size=(part_entry[i].length >> 10);

			memset(buf, 0, sizeof(buf));
			memset(tmp, 0, sizeof(tmp));
			snprintf(tmp, 16, "%llu", size);

			if (memcmp(empty_mount, part_entry[i].mount_point, sizeof(empty_mount)) != 0) {
				sprintf(buf, "%sk(%s%s",tmp, part_entry[i].mount_point,i == part_count-1? ")" :"),");
			}
			else {
				sprintf(buf, "%s%s",tmp,i == part_count-1? "k" :"k,");
			}
			//printf("buf=%s\n",buf);
			tmp_cmdline = (char *)malloc(strlen(getenv("mtd_part")) + 60);
			if (!tmp_cmdline) {
				printf("%s: Malloc failed\n", __func__);
			}
			else {
				sprintf(tmp_cmdline, "%s%s", getenv("mtd_part"),buf);
				setenv("mtd_part", tmp_cmdline);
				free(tmp_cmdline);
			}
			debug(">%s\n",getenv("mtd_part"));
		}
#endif
	}

	/* parse each fw_entry */
	for (i = 0; i < fw_count; i++)
	{
		EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here

		this_entry = (fw_entry + unit_len * i);
		FW_ENTRY_MEMBER_GET(entry_target_addr, this_entry, target_addr, version);
		FW_ENTRY_MEMBER_GET(entry_type, this_entry, type, version);
		FW_ENTRY_MEMBER_GET(entry_length, this_entry, length, version);
		FW_ENTRY_MEMBER_GET(entry_offset, this_entry, offset, version);
		FW_ENTRY_MEMBER_GET(entry_lzma, this_entry, lzma, version);

		if (entry_target_addr)
		{
			if(boot_mode == BOOT_GOLD_MODE)
			{
				switch(entry_type)
				{
					case FW_TYPE_GOLD_KERNEL:
						//entry_offset=entry_offset-1; //let load gold_fw fail, and it can test enter to USB mode
						memset(str, 0, sizeof(str));
#if defined(CONFIG_RTK_ARM32) || defined(CONFIG_CPU_V7)
						entry_target_addr = getenv_ulong("kernel_loadaddr", 16, entry_target_addr);
#endif
						sprintf((char *) str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("kernel_loadaddr",(char *) str);
						printf("GOLD Kernel:\n");
						break;
					case FW_TYPE_GOLD_RESCUE_DT:
						entry_target_addr = rtk_plat_get_dtb_target_address(entry_target_addr);
						FW_ENTRY_MEMBER_SET(entry_target_addr, this_entry, target_addr, version);
						//printf("entry_target_addr =%x\n",entry_target_addr);
						memset(str, 0, sizeof(str));
						sprintf((char *) str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("fdt_loadaddr",(char *) str);
						printf("GOLD Rescue DT:\n");
						break;
					case FW_TYPE_GOLD_RESCUE_ROOTFS:
						printf("GOLD Rescue ROOTFS:\n");
						entry_target_addr = get_rescue_rootfs_addr(entry_target_addr);
#ifdef NAS_ENABLE
						initrd_size = entry_length;
#endif
						break;
					case FW_TYPE_GOLD_AUDIO:
						if(boot_mode == BOOT_KERNEL_ONLY_MODE)
							continue;
						else
						{
							ipc_shm.audio_fw_entry_pt = CPU_TO_BE32(entry_target_addr | MIPS_KSEG0BASE);
							printf("GOLD Audio FW:\n");
						}
						break;
					default:
						//printf("Unknown FW (%d):\n", entry_type);
						continue;
				}
			}
			else
			{
				switch(entry_type)
				{
					case FW_TYPE_KERNEL:
						memset(str, 0, sizeof(str));
#if defined(CONFIG_RTK_ARM32) || defined(CONFIG_CPU_V7)
						entry_target_addr = getenv_ulong("kernel_loadaddr", 16, entry_target_addr);
#endif
						sprintf(str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("kernel_loadaddr", str);
						printf("Kernel:\n");
						break;

					case FW_TYPE_KERNEL_DT:
						if( boot_mode != BOOT_RESCUE_MODE ) {
							entry_target_addr = rtk_plat_get_dtb_target_address(entry_target_addr);
							FW_ENTRY_MEMBER_SET(entry_target_addr, this_entry, target_addr, version);
							memset(str, 0, sizeof(str));
							sprintf((char *)str, "%x", entry_target_addr); /* write entry-point into string */
							setenv("fdt_loadaddr", (char *)str);
							printf("DT:\n");
							break;
						}
						else {
							continue;
						}

					case FW_TYPE_RESCUE_DT:
						if( boot_mode == BOOT_RESCUE_MODE ) {
							entry_target_addr = rtk_plat_get_dtb_target_address(entry_target_addr);
							FW_ENTRY_MEMBER_SET(entry_target_addr, this_entry, target_addr, version);
							memset(str, 0, sizeof(str));
							sprintf((char *)str, "%x", entry_target_addr); /* write entry-point into string */
							setenv("fdt_loadaddr", (char *)str);
							printf("Rescue DT:\n");
							break;
						}
						else {
							continue;
						}

					case FW_TYPE_KERNEL_ROOTFS:
						printf("ROOTFS:\n");
						break;

					case FW_TYPE_RESCUE_ROOTFS:
						if( boot_mode == BOOT_RESCUE_MODE ) {
							printf("Rescue ROOTFS:\n");
							entry_target_addr = get_rescue_rootfs_addr(entry_target_addr);
#ifdef NAS_ENABLE
							initrd_size = entry_length;
#endif
							sprintf(tmpbuf, "mw.b 0x%08x 0 0x%x", entry_target_addr, CONFIG_ROOTFS_RESCUE_SIZE);
							printf("\t Clear memory at 0x%08x, size=0x%08x (0x%08x)\n",
								entry_target_addr, CONFIG_ROOTFS_RESCUE_SIZE, entry_target_addr + CONFIG_ROOTFS_RESCUE_SIZE);
							run_command(tmpbuf, 0);
							break;
						}
						else {
							continue;
						}

					case FW_TYPE_AUDIO:
						if(boot_mode == BOOT_KERNEL_ONLY_MODE)
							continue;
						else
						{
							ipc_shm.audio_fw_entry_pt = CPU_TO_BE32(entry_target_addr | MIPS_KSEG0BASE);
							printf("Audio FW:\n");
						}
						break;

					case FW_TYPE_IMAGE_FILE:
						if(boot_mode == BOOT_KERNEL_ONLY_MODE)
							continue;
#ifdef NAS_ENABLE
						if(boot_mode == BOOT_RESCUE_MODE )
							entry_target_addr = getenv_ulong("logo_loadaddr", 16, get_rescue_rootfs_addr(CONFIG_RESCUE_ROOTFS_LOADADDR)+initrd_size);
						else
							entry_target_addr = getenv_ulong("logo_loadaddr", 16, 0x2400000);
#else
						entry_target_addr = getenv_ulong("blue_logo_loadaddr", 16, BOOT_LOGO_ADDR);
#endif
						printf("IMAGE FILE:\n");
						vo_secure_addr = entry_target_addr + BOOT_LOGO_SIZE - 0x100000;
						memset((void *)(uintptr_t)vo_secure_addr, 0x0, sizeof(char)*VO_SECURE_SIZE);
						printf("Address for boot logo from %x to %x will be reserved.\n", (unsigned int)entry_target_addr,
							(unsigned int)(entry_target_addr + BOOT_LOGO_SIZE));
						/* assign boot_av structure */
						boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
						if(boot_logo_enable)
						{
							boot_av-> logo_enable = boot_logo_enable;
							boot_av-> logo_addr = CPU_TO_BE32(entry_target_addr);
							boot_av-> src_width = CPU_TO_BE32(custom_logo_src_width);
							boot_av-> src_height = CPU_TO_BE32(custom_logo_src_height);
							boot_av-> dst_width = CPU_TO_BE32(custom_logo_dst_width);
							boot_av-> dst_height = CPU_TO_BE32(custom_logo_dst_height);
							boot_av-> vo_secure_addr = CPU_TO_BE32((unsigned int)(uintptr_t)vo_secure_addr);
						}
						break;

					default:
						//printf("Unknown FW (%d):\n", entry_type);
						continue;
				}
			}

#ifndef CONFIG_RTD1295
#ifndef CONFIG_BOOTCODE_LOAD_AVFW
			// after 1395, audio fw belong to trusted fw and need to be loaded by FSBL
			if (entry_type == FW_TYPE_AUDIO || entry_type == FW_TYPE_GOLD_AUDIO) {
				printf("\t FW Image preload on 0x%08x, size=0x%08x (0x%08x)\n",
					entry_target_addr, entry_length, entry_target_addr + entry_length);
				continue;
			}
#endif
#endif

			// FW loading is performed else where(ex:fsbl) under Secure BOOT flow
			// LOGO image is not encryption file, so fsbl will not preload.
			if (!UBOOT_NORMAL_BOOT && entry_type != FW_TYPE_IMAGE_FILE ) {
				printf("\t Encrypted FW Image to 0x%08x, size=0x%08x (0x%08x)\n",
					entry_target_addr, entry_length,
					entry_target_addr + entry_length);
				printf("\t Encrypted FW Image fr 0x%08llx \n", entry_offset);
			}
			else {
				printf("\t FW Image to 0x%08x, size=0x%08x (0x%08x)\n",
						entry_target_addr, entry_length, entry_target_addr + entry_length);
				printf("\t FW Image fr 0x%08Lx %s\n", entry_offset, entry_lzma ? "(lzma)" : "(non-lzma)");
			}

			WATCHDOG_KICK();

			/* secure mode only apply to fw image */
			if (entry_type == FW_TYPE_KERNEL ||
				entry_type == FW_TYPE_KERNEL_ROOTFS ||
				entry_type == FW_TYPE_RESCUE_ROOTFS ||
				entry_type == FW_TYPE_IMAGE_FILE ||
				entry_type == FW_TYPE_AUDIO ||
				entry_type == FW_TYPE_GOLD_KERNEL ||
				entry_type == FW_TYPE_GOLD_RESCUE_ROOTFS ||
				entry_type == FW_TYPE_GOLD_AUDIO)
			{
				/* get memory layout before copy fw image */
				mem_layout.bIsEncrypted = (secure_mode != NONE_SECURE_BOOT);
			}
			mem_layout.bIsCompressed = entry_lzma;
			mem_layout.image_target_addr = entry_target_addr & (~MIPS_KSEG_MSK);

			get_mem_layout_when_read_image(&mem_layout);

			/* read image from flash */
			imageSize = entry_length;

			rwsize = entry_length;
			if (rwsize&(mtd->writesize-1))  // page aligned
			{
				rwsize &= ~(mtd->writesize-1);
				rwsize += mtd->writesize;
			}

			if(mem_layout.bIsEncrypted)
				ret = nand_read_skip_bad_on_the_fly(mtd, entry_offset, &rwsize, (u_char*)(uintptr_t)mem_layout.flash_to_ram_addr,CP_NF_AES_CBC_128);
			else
				ret = nand_read_skip_bad(mtd, entry_offset, &rwsize, NULL, mtd->size, (u_char*)(uintptr_t)mem_layout.flash_to_ram_addr);

			if(ret){
				printf("[ERR] Read fw error (type:%d)!\n", entry_type);
				return RTK_PLAT_ERR_READ_FW_IMG;
			}

			/* Check checksum */
			if (FW_DESC_BASE_VERSION(version) == FW_DESC_TABLE_V1_T_VERSION_1) {
				fw_checksum = get_checksum((uchar *)(uintptr_t)mem_layout.flash_to_ram_addr, entry_length);
				if (((fw_desc_entry_v1_t*)this_entry)->checksum != fw_checksum &&
					secure_mode!= RTK_SECURE_BOOT) {
					printf("\t FW Image checksum FAILED\n");
					printf("\t FW Image entry  checksum=0x%08x\n",
						((fw_desc_entry_v1_t*)this_entry)->checksum);
					printf("\t FW Image result checksum=0x%08x\n", fw_checksum);
					return RTK_PLAT_ERR_READ_FW_IMG;
				}
			} else if (FW_DESC_BASE_VERSION(version) == FW_DESC_TABLE_V2_T_VERSION_2) {
				SHA256_hash((uchar *)(uintptr_t)mem_layout.flash_to_ram_addr, entry_length, sha_hash, NULL);
				if ((memcmp(((fw_desc_entry_v2_t*)this_entry)->sha_hash, sha_hash, SHA256_SIZE) != 0) &&
					secure_mode!= RTK_SECURE_BOOT) {
					printf("\t FW Image sha FAILED\n");
					printf("\t FW Image entry sha256==>\n");
					for (j = 0 ; j < 32 ; j++)
						printf("%02x ", ((fw_desc_entry_v2_t*)this_entry)->sha_hash[j]);
					printf("\n\t FW Image result sha256==>\n");
					for (j = 0 ; j < 32 ; j++)
						printf("%02x ", sha_hash[j]);
					printf("\n");
					return RTK_PLAT_ERR_READ_FW_IMG;
				}
			}

			/* UBoot doing decryption */
			OTP_GET_BYTE(AES_KEY_OFFSET, aes_key_addr, 16);
			if (!UBOOT_NORMAL_BOOT && entry_type != FW_TYPE_IMAGE_FILE) {
				if(!decrypt_image(UINT32_PTR(entry_target_addr), UINT32_PTR(entry_target_addr), entry_length - AES_TRUNCATED_SIZE, UINT32_PTR(aes_key_addr))){
					fw_length = SWAPEND32(REG32((uintptr_t)(entry_target_addr + entry_length - AES_TRUNCATED_SIZE - FW_SIZE_OFFSET))) >> 3; /*bit length / 8 = byte length*/
					if (Verify_SHA256_hash(UINT32_PTR(entry_target_addr), fw_length, UINT32_PTR(entry_target_addr + entry_length - AES_TRUNCATED_SIZE), 1, UINT32_PTR(RSA_KEY_ADDR))){
						return RTK_PLAT_ERR_READ_FW_IMG;
					}
				} else {
					return RTK_PLAT_ERR_READ_FW_IMG;
				}
			}

			/* if lzma type, decompress image */
			if (mem_layout.bIsCompressed)
			{
				decompressedSize = 0;
				if (lzmaBuffToBuffDecompress((uchar*)(uintptr_t)mem_layout.decompressed_addr, (SizeT *)&decompressedSize, (uchar*)(uintptr_t)mem_layout.compressed_addr, imageSize) != 0)
				{
					printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);

					return RTK_PLAT_ERR_READ_FW_IMG;
				}
			}
#ifdef NAS_ENABLE
			if (FW_TYPE_RESCUE_ROOTFS == entry_type)
			{
				initrd_size = (entry_lzma)?decompressedSize:entry_length;
			}
#endif
		}
	}

#ifdef CONFIG_CUSTOMIZE_NEMO
	/* assign boot_av structure for nemo */
	boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
	printf("  boot_logo_enable(%d), magic# 0x%08x\n", boot_logo_enable, boot_av->dwMagicNumber);
	if(boot_logo_enable == 2)
	{
		boot_av-> logo_enable = boot_logo_enable;
		boot_av-> bAudioDone = 0; //audio repeat
		boot_av-> dwAudioStreamAddress = CPU_TO_BE32(ADDR_SPLASH_H264_MP2);
		boot_av-> dwAudioStreamLength = CPU_TO_BE32(SIZE_SPLASH_H264_MP2);
		boot_av-> audio_buffer_addr = CPU_TO_BE32(ANIMATION_AUDIO_ADDR);
		boot_av-> audio_buffer_size = CPU_TO_BE32(ANIMATION_AUDIO_SIZE);
	}
#endif

	/* set boot_av_info_ptr */
	if (boot_av->dwMagicNumber == SWAPEND32(BOOT_AV_INFO_MAGICNO))
	{
		boot_av->bHDMImode = sys_logo_is_HDMI; // ignored.

		// enable audio sound
		if (boot_av->dwAudioStreamLength != 0)
		{
			;
		}

		ipc_shm.pov_boot_av_info = SWAPEND32((uint)(uintptr_t)boot_av);

		#ifdef DUBUG_BOOT_AV_INFO
		dump_boot_av_info(boot_av);
		#endif
	}

	/* Flush caches */
	flush_dcache_all();

#endif /* CONFIG_SYS_RTK_NAND_FLASH */
	/* Start audio fw for S5 power check */
	if (boot_from_flash == BOOT_FROM_FLASH_NORMAL_MODE) {
		do_go_audio_fw();
	}

	return ret;
}

/*
 * Use firmware description table to read images from SPI flash.
 */
#if defined(CONFIG_RTKSPI) && defined(CONFIG_CMD_RTKSPI)
extern unsigned int spi_flash_min_erase_size;
#endif
int rtk_plat_read_fw_image_from_SPI(
		uint fw_desc_table_base, part_desc_entry_v1_t* part_entry, int part_count,
		void* fw_entry, int fw_count,
		uchar version)
{
	int ret = RTK_PLAT_ERR_OK;
#ifdef CONFIG_BOOT_FROM_SPI
	void *this_entry;
	int i;
#ifndef BYPASS_CHECKSUM	
	int j;
#endif	
	uint unit_len;
#ifndef BYPASS_CHECKSUM	
	uint fw_checksum = 0;
#endif	
	unsigned int secure_mode;
#ifndef BYPASS_CHECKSUM	
	unsigned char sha_hash[32];
#endif	
	boot_av_info_t *boot_av;
	MEM_LAYOUT_WHEN_READ_IMAGE_T mem_layout;
	uint imageSize = 0;
	uint erasesize = 0x1000; // Set erasesize default to 4KB
	uint decompressedSize = 0;
	unsigned char str[16];// old array size is 5, change to 16. To avoid the risk in memory overlap.

	uchar entry_type = 0;
	uchar entry_lzma = 0;
	uint entry_target_addr = 0;
	u64 entry_offset = 0;
	uint entry_length = 0;
	uint entry_paddings = 0;
	char tmpbuf[128];
	unsigned int vo_secure_addr;

	secure_mode = rtk_get_secure_boot_type();

	/* find fw_entry structure according to version */
	switch (version)
	{
		case FW_DESC_TABLE_V1_T_VERSION_1:
			unit_len = sizeof(fw_desc_entry_v1_t);
			break;

		case FW_DESC_TABLE_V2_T_VERSION_2:
			unit_len = sizeof(fw_desc_entry_v2_t);
			break;

		default:
			return RTK_PLAT_ERR_READ_FW_IMG;
	}

	/* clear boot_av_info memory */
	boot_av = (boot_av_info_t *) MIPS_BOOT_AV_INFO_ADDR;
	memset(boot_av, 0, sizeof(boot_av_info_t));

	/* parse each fw_entry */
	for (i = 0; i < fw_count; i++)
	{
		EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here

		this_entry = (fw_entry + unit_len * i);
		FW_ENTRY_MEMBER_GET(entry_target_addr, this_entry, target_addr, version);
		FW_ENTRY_MEMBER_GET(entry_type, this_entry, type, version);
		FW_ENTRY_MEMBER_GET(entry_length, this_entry, length, version);
		FW_ENTRY_MEMBER_GET(entry_paddings, this_entry, paddings, version);
		FW_ENTRY_MEMBER_GET(entry_offset, this_entry, offset, version);
		FW_ENTRY_MEMBER_GET(entry_lzma, this_entry, lzma, version);
		
#if defined(NAS_ENABLE) && defined(CONFIG_RTD161x)
		if (skip_avfw_entry) {
			if ( entry_type == FW_TYPE_AUDIO || entry_type == FW_TYPE_IMAGE_FILE ) {
				continue;
			}
		}
#endif

		if (entry_target_addr)
		{
			switch(entry_type)
			{
				case FW_TYPE_KERNEL:
					memset(str, 0, sizeof(str));
					sprintf((char *)str, "%x", entry_target_addr); /* write entry-point into string */
					setenv("kernel_loadaddr", (char *)str);
					printf("Kernel:\n");
					break;

				case FW_TYPE_KERNEL_DT:
					if( boot_mode != BOOT_RESCUE_MODE ) {
						entry_target_addr = rtk_plat_get_dtb_target_address(entry_target_addr);
						FW_ENTRY_MEMBER_SET(entry_target_addr, this_entry, target_addr, version);
						//printf("entry_target_addr =%x\n",entry_target_addr);
						memset(str, 0, sizeof(str));
						sprintf((char *)str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("fdt_loadaddr", (char *)str);
						printf("DT:\n");
						break;
					}
					else {
						continue;
					}

				case FW_TYPE_RESCUE_DT:
					if( boot_mode == BOOT_RESCUE_MODE ) {
						entry_target_addr = rtk_plat_get_dtb_target_address(entry_target_addr);
						FW_ENTRY_MEMBER_SET(entry_target_addr, this_entry, target_addr, version);
						//printf("entry_target_addr =%x\n",entry_target_addr);
						memset(str, 0, sizeof(str));
						sprintf((char *)str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("fdt_loadaddr", (char *)str);
						printf("Rescue DT:\n");
						break;
					}
					else {
						continue;
					}

#ifdef CONFIG_BFS_SUPPORT_KERNEL_ROOTFS
				case FW_TYPE_KERNEL_ROOTFS:
					if( boot_mode != BOOT_RESCUE_MODE ) {
						printf("Kernel ROOTFS:\n");
						entry_target_addr = get_kernel_rootfs_addr(entry_target_addr);
#ifdef NAS_ENABLE
						initrd_size = entry_length;
						sprintf(tmpbuf, "mw.b 0x%08x 0 0x%x", entry_target_addr, entry_paddings);
						printf("\t Clear memory at 0x%08x, size=0x%08x (0x%08x)\n",
							entry_target_addr, entry_paddings, entry_target_addr + entry_paddings);
						run_command(tmpbuf, 0);
#endif
						break;
					}
					else {
						continue;
					}
#endif

				case FW_TYPE_RESCUE_ROOTFS:
					if( boot_mode == BOOT_RESCUE_MODE ) {
						printf("Rescue ROOTFS:\n");
						entry_target_addr = get_rescue_rootfs_addr(entry_target_addr);
#ifdef NAS_ENABLE
						initrd_size = entry_length;
#endif
						sprintf(tmpbuf, "mw.b 0x%08x 0 0x%x", entry_target_addr, CONFIG_ROOTFS_RESCUE_SIZE);
						printf("\t Clear memory at 0x%08x, size=0x%08x (0x%08x)\n",
							entry_target_addr, CONFIG_ROOTFS_RESCUE_SIZE, entry_target_addr + CONFIG_ROOTFS_RESCUE_SIZE);
						run_command(tmpbuf, 0);
						break;
					}
					else {
						continue;
					}

				case FW_TYPE_AUDIO:
					if(boot_mode == BOOT_KERNEL_ONLY_MODE)
						continue;
					else
					{
						ipc_shm.audio_fw_entry_pt = CPU_TO_BE32(entry_target_addr | MIPS_KSEG0BASE);
						printf("Audio FW:\n");
					}
					break;

#ifdef CONFIG_BFS_SUPPORT_LOGO_IMG
				case FW_TYPE_IMAGE_FILE:
					if(boot_mode == BOOT_KERNEL_ONLY_MODE)
						continue;

					printf("IMAGE FILE:\n");
					vo_secure_addr = entry_target_addr + BOOT_LOGO_SIZE - 0x100000;
					memset((void *)(uintptr_t)vo_secure_addr, 0x0, sizeof(char)*VO_SECURE_SIZE);
					printf("Address for boot logo from %x to %x will be reserved.\n", (unsigned int)entry_target_addr,
						(unsigned int)(entry_target_addr + BOOT_LOGO_SIZE));
					/* assign boot_av structure */
					boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
					if(boot_logo_enable)
					{
						boot_av-> logo_enable = boot_logo_enable;
						boot_av-> logo_addr = CPU_TO_BE32(entry_target_addr);
						boot_av-> src_width = CPU_TO_BE32(custom_logo_src_width);
						boot_av-> src_height = CPU_TO_BE32(custom_logo_src_height);
						boot_av-> dst_width = CPU_TO_BE32(custom_logo_dst_width);
						boot_av-> dst_height = CPU_TO_BE32(custom_logo_dst_height);
						boot_av-> vo_secure_addr = CPU_TO_BE32((unsigned int)(uintptr_t)vo_secure_addr);
					}

					break;
#endif

				default:
					//printf("Unknown FW (%d):\n", entry_type);
					continue;
			}
			printf("\t FW Image to 0x%08x, size=0x%08x (0x%08x)\n",
					entry_target_addr, entry_length, entry_target_addr + entry_length);
			printf("\t FW Image fr 0x%08Lx \n", entry_offset);

			WATCHDOG_KICK();

			/* secure mode and lzma will only apply to fw image */
			if (entry_type == FW_TYPE_KERNEL ||
				entry_type == FW_TYPE_KERNEL_ROOTFS ||
				entry_type == FW_TYPE_RESCUE_ROOTFS ||
				entry_type == FW_TYPE_AUDIO)
			{
				/* get memory layout before copy fw image */
				mem_layout.bIsEncrypted = (secure_mode != NONE_SECURE_BOOT);
				mem_layout.bIsCompressed = entry_lzma;
				mem_layout.image_target_addr = entry_target_addr & (~MIPS_KSEG_MSK);
			}
#ifdef CONFIG_BFS_SUPPORT_LOGO_IMG
			else if ( entry_type == FW_TYPE_IMAGE_FILE )
			{
				mem_layout.bIsEncrypted = (secure_mode != NONE_SECURE_BOOT);
				mem_layout.bIsCompressed = entry_lzma;
				mem_layout.image_target_addr = entry_target_addr;
			}
#endif
			else
			{
				/* get memory layout before copy other image */
				mem_layout.bIsEncrypted = 0;
				mem_layout.bIsCompressed = 0;
				mem_layout.image_target_addr = entry_target_addr & (~MIPS_KSEG_MSK);
			}

			get_mem_layout_when_read_image(&mem_layout);

			imageSize = entry_length;

#if defined(CONFIG_RTKSPI) && defined(CONFIG_CMD_RTKSPI)
                        if(spi_flash_min_erase_size) erasesize = spi_flash_min_erase_size;
#endif
			// aligned to erasesize
			if (imageSize&(erasesize-1)) {
				imageSize &= ~(erasesize-1);
				imageSize += erasesize;
			}

		        rtkspi_read32_md(mem_layout.flash_to_ram_addr, SPI_RBUS_BASE_ADDR+entry_offset, imageSize);
#ifdef NAS_ENABLE
			if ((entry_type == FW_TYPE_KERNEL_ROOTFS || entry_type == FW_TYPE_RESCUE_ROOTFS) &&
				entry_length < imageSize)
			{
				printf("\t Clear memory at 0x%08x, size=0x%08x (0x%08x)\n",
					entry_target_addr + entry_length,
					imageSize - entry_length,
					entry_target_addr + imageSize);

				sprintf(tmpbuf, "mw.b 0x%08x 0 0x%x",
					entry_target_addr + entry_length,
					imageSize - entry_length);
				run_command(tmpbuf, 0);
			}
#endif

#ifndef BYPASS_CHECKSUM
			/* Check checksum */
			if (FW_DESC_BASE_VERSION(version) == FW_DESC_TABLE_V1_T_VERSION_1) {
				fw_checksum = get_checksum((uchar *)(uintptr_t)mem_layout.flash_to_ram_addr, entry_length);
				if (((fw_desc_entry_v1_t*)this_entry)->checksum != fw_checksum &&
					secure_mode!= RTK_SECURE_BOOT) {
					printf("\t FW Image checksum FAILED\n");
					printf("\t FW Image entry  checksum=0x%08x\n",
						((fw_desc_entry_v1_t*)this_entry)->checksum);
					printf("\t FW Image result checksum=0x%08x\n", fw_checksum);
					return RTK_PLAT_ERR_READ_FW_IMG;
				}
			} else if (FW_DESC_BASE_VERSION(version) == FW_DESC_TABLE_V2_T_VERSION_2) {
				SHA256_hash((uchar *)(uintptr_t)mem_layout.flash_to_ram_addr, entry_length, sha_hash, NULL);
				if ((memcmp(((fw_desc_entry_v2_t*)this_entry)->sha_hash, sha_hash, SHA256_SIZE) != 0) &&
					secure_mode!= RTK_SECURE_BOOT) {
					printf("\t FW Image sha FAILED\n");
					printf("\t FW Image entry sha256==>\n");
					for (j = 0 ; j < 32 ; j++)
						printf("%02x ", ((fw_desc_entry_v2_t*)this_entry)->sha_hash[j]);
					printf("\n\t FW Image result sha256==>\n");
					for (j = 0 ; j < 32 ; j++)
						printf("%02x ", sha_hash[j]);
					printf("\n");
					return RTK_PLAT_ERR_READ_FW_IMG;
				}
			}
#endif

			/* if lzma type, decompress image */
			if (mem_layout.bIsCompressed)
			{
				decompressedSize = 0;
				if (lzmaBuffToBuffDecompress((uchar*)(uintptr_t)mem_layout.decompressed_addr, (SizeT *)&decompressedSize, (uchar*)(uintptr_t)mem_layout.compressed_addr, imageSize) != 0)
				{
					printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);

					return RTK_PLAT_ERR_READ_FW_IMG;
				}
			}
#ifdef NAS_ENABLE
			if (FW_TYPE_RESCUE_ROOTFS == entry_type)
			{
				initrd_size = (entry_lzma)?decompressedSize:entry_length;
			}
#endif
		}
	}

	/* set boot_av_info_ptr */
	if (boot_av->dwMagicNumber == SWAPEND32(BOOT_AV_INFO_MAGICNO))
	{
		boot_av->bHDMImode = sys_logo_is_HDMI;// ignored.

		// enable audio sound
		if (boot_av->dwAudioStreamLength != 0)
		{
			;
		}

		ipc_shm.pov_boot_av_info = SWAPEND32((uint)(uintptr_t) boot_av);

		#ifdef DUBUG_BOOT_AV_INFO
		dump_boot_av_info(boot_av);
		#endif
	}
	/* Flush caches */
	flush_dcache_all();


#endif // CONFIG_BOOT_FROM_SPI
	/* Start audio fw for S5 power check */
	if (boot_from_flash == BOOT_FROM_FLASH_NORMAL_MODE) {
		do_go_audio_fw();
	}

	return ret;
}

/*
 * Use firmware description table to read images from SD flash.
 */
int rtk_plat_read_fw_image_from_SD(void)
{
#if defined(CONFIG_SYS_RTK_SD_FLASH)
	char tmpbuf[128];
	int ret = RTK_PLAT_ERR_OK;
	char *filename;
	unsigned int secure_mode=0;

	boot_av_info_t *boot_av;
	uint entry_target_addr = 0;
	unsigned int vo_secure_addr;

	secure_mode = rtk_get_secure_boot_type();

	printf("[BPI] %s (boot from SD mode; secure_mode %d)=====\n",
	__func__, secure_mode);

	/* DTB 0x02100000 */
	/* ROOTFS 0x02100000 */
	/* Kernel 0x03000000 */
	/* AudioFW 0x0f900000 or 0x01b00000 */
	/* Image file boot logo 0x1e800000 */

	/* DTB ------------------------------------------------------------------ */
	if ((filename = getenv("sd_boot_dtb")) == NULL) {
		filename =(char*) CONFIG_BOOT_FROM_SD_DTB;
	}
	
	sprintf(tmpbuf, "fatload %s 0:1 %s %s", getenv("device"), getenv("fdt_loadaddr"), filename);
	
	if (run_command(tmpbuf, 0) != 0) {
		DDDDRED("load %s to %s failed\n", filename, getenv("fdt_loadaddr"));
		goto loading_failed;
	}
	else {
		printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("fdt_loadaddr"));
	}

	/* ROOTFS(uInitrd) --------------------------------------------------------------- */
	if ((filename = getenv("sd_boot_rootfs")) == NULL) {
		filename =(char*) CONFIG_BOOT_FROM_SD_ROOTFS;
	}
	
	sprintf(tmpbuf, "fatload %s 0:1 %s %s", getenv("device"), getenv("rootfs_loadaddr"), filename);
	if (run_command(tmpbuf, 0) != 0) {
		DDDDRED("load %s to %s failed\n", filename, getenv("rootfs_loadaddr"));
	}
	else {
		printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("rootfs_loadaddr"));
	}

	/* Kernel --------------------------------------------------------------- */
	if ((filename = getenv("sd_vmlinux")) == NULL) {
		filename =(char*) CONFIG_BOOT_FROM_SD_VMLINUX;
	}

	sprintf(tmpbuf, "fatload %s 0:1 %s %s", getenv("device"), getenv("kernel_loadaddr"), filename);
	
	if (run_command(tmpbuf, 0) != 0) {
		DDDDRED("load %s to %s failed\n", filename, getenv("kernel_loadaddr"));
		goto loading_failed;
	}
	else {
		printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("kernel_loadaddr"));
	}

	/* audio firmware ------------------------------------------------------- */
	if ((filename = getenv("sd_audio")) == NULL) {
		filename =(char*) CONFIG_BOOT_FROM_SD_AUDIO_CORE;
	}

	sprintf(tmpbuf, "fatload %s 0:1 %s %s", getenv("device"), getenv("audio_loadaddr"), filename);
	if (run_command(tmpbuf, 0) != 0) {
		DDDDRED("load %s to %s failed\n", filename, getenv("audio_loadaddr"));
		goto loading_failed;
	}
	else {
		printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("audio_loadaddr"));
	}

	/* blue logo ------------------------------------------------------- */
	/* clear boot_av_info memory */
	boot_av = (boot_av_info_t *) MIPS_BOOT_AV_INFO_ADDR;
	memset(boot_av, 0, sizeof(boot_av_info_t));

	if ((filename = getenv("sd_blue_logo")) == NULL) {
		filename =(char*) CONFIG_BOOT_FROM_SD_AUDIO_CORE;
	}

	sprintf(tmpbuf, "fatload %s 0:1 %s %s", getenv("device"), getenv("blue_logo_loadaddr"), filename);
	if (run_command(tmpbuf, 0) != 0) {
		DDDDRED("load %s to %s failed\n", filename, getenv("blue_logo_loadaddr"));
		goto loading_failed;
	}
	else {
		printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("blue_logo_loadaddr"));
	}

	/* reserve mem for logo */
	entry_target_addr = getenv_ulong("blue_logo_loadaddr", 16, BOOT_LOGO_ADDR);
	vo_secure_addr = entry_target_addr + BOOT_LOGO_SIZE - 0x100000;
	memset((void *)(uintptr_t)vo_secure_addr, 0x0, sizeof(char)*VO_SECURE_SIZE);
	printf("Address for boot logo from %x to %x will be reserved.\n", (unsigned int)entry_target_addr,
		
	(unsigned int)(entry_target_addr + BOOT_LOGO_SIZE));
	/* assign boot_av structure */
	boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
	if(boot_logo_enable)
	{
		boot_av-> logo_enable = boot_logo_enable;
		boot_av-> logo_addr = CPU_TO_BE32(entry_target_addr);
		boot_av-> src_width = CPU_TO_BE32(custom_logo_src_width);
		boot_av-> src_height = CPU_TO_BE32(custom_logo_src_height);
		boot_av-> dst_width = CPU_TO_BE32(custom_logo_dst_width);
		boot_av-> dst_height = CPU_TO_BE32(custom_logo_dst_height);
		boot_av-> vo_secure_addr = CPU_TO_BE32((unsigned int)(uintptr_t)vo_secure_addr);
	}

	/* set boot_av_info_ptr */
	if (boot_av->dwMagicNumber == SWAPEND32(BOOT_AV_INFO_MAGICNO))
	{
		boot_av->bHDMImode = sys_logo_is_HDMI;// ignored.

		// enable audio sound
		if (boot_av->dwAudioStreamLength != 0)
		{
			;
		}

		ipc_shm.pov_boot_av_info = SWAPEND32((uint)(uintptr_t) boot_av);

		#ifdef DUBUG_BOOT_AV_INFO
		dump_boot_av_info(boot_av);
		#endif
	}

	/* Flush caches */
	flush_dcache_all();
#endif
	return ret;

loading_failed:
	return RTK_PLAT_ERR_READ_SD_IMG;
}

/*
 * Use firmware description table to read images from SATAflash.
 */
int rtk_plat_read_fw_image_from_SATA(
		uint fw_desc_table_base, part_desc_entry_v1_t* part_entry, int part_count,
		void* fw_entry, int fw_count,
		uchar version)
{
#ifdef CONFIG_SYS_RTK_SATA_STORAGE
	fw_desc_entry_v1_t *this_entry;
	int i;
	uint unit_len;
	uint fw_checksum = 0;
	unsigned int secure_mode;
	unsigned char ks[16],kh[16],kimg[16];
    unsigned char aes_key[16];
    unsigned char rsa_key[256];
#ifdef CONFIG_CMD_KEY_BURNING
	unsigned int * Kh_key_ptr = NULL;
#else
	unsigned int * Kh_key_ptr = (unsigned int *)Kh_key_default;
#endif
	unsigned int img_truncated_size; // install_a will append 256-byte signature data to it
	int ret;
	boot_av_info_t *boot_av;
	uint block_no;
	MEM_LAYOUT_WHEN_READ_IMAGE_T mem_layout;
	uint imageSize = 0;
	uint imageBlkSize = 0;
	uint decompressedSize = 0;

	// extern variable
	extern unsigned int mcp_dscpt_addr;
	mcp_dscpt_addr = 0;

	secure_mode = rtk_get_secure_boot_type();
	img_truncated_size = RSA_SIGNATURE_LENGTH*2+NP_INV32_LENGTH;

	char str[16];// old array size is 5, change to 16. To avoid the risk in memory overlap.

	/* find fw_entry structure according to version */
	switch (version)
	{
		case FW_DESC_TABLE_V1_T_VERSION_1:
			unit_len = sizeof(fw_desc_entry_v1_t);
			break;

		case FW_DESC_TABLE_V1_T_VERSION_11:
			unit_len = sizeof(fw_desc_entry_v11_t);
			break;

		case FW_DESC_TABLE_V1_T_VERSION_21:
			unit_len = sizeof(fw_desc_entry_v21_t);
			break;

		default:
			return RTK_PLAT_ERR_READ_FW_IMG;
	}

	/* clear boot_av_info memory */
	boot_av = (boot_av_info_t *) MIPS_BOOT_AV_INFO_ADDR;
	memset(boot_av, 0, sizeof(boot_av_info_t));

	//printf("****** %s %d, boot_mode %d\n", __FUNCTION__, __LINE__, boot_mode);

	/* parse each fw_entry */
	for (i = 0; i < fw_count; i++)
	{
		EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here

		this_entry = (fw_desc_entry_v1_t *)(fw_entry + unit_len * i);

		if (this_entry->target_addr)
		{
			if (boot_mode == BOOT_RESCUE_MODE || boot_mode == BOOT_ANDROID_MODE)
			{
				switch(this_entry->type)
				{
					case FW_TYPE_RESCUE_KERNEL:
						memset(str, 0, sizeof(str));
						sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
						setenv("kernel_loadaddr", str);
						printf("Rescue Kernel:\n");
						break;

					case FW_TYPE_RESCUE_DT:
						this_entry->target_addr = rtk_plat_get_dtb_target_address(this_entry->target_addr);
						memset(str, 0, sizeof(str));
						sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
						setenv("fdt_loadaddr", str);
						printf("Rescue DT:\n");
						break;

					case FW_TYPE_RESCUE_ROOTFS:
						printf("Rescue ROOTFS:\n");
						break;

					case FW_TYPE_RESCUE_AUDIO:
						if(boot_mode == BOOT_KERNEL_ONLY_MODE)
							continue;
						else
						{
							ipc_shm.audio_fw_entry_pt = CPU_TO_BE32(this_entry->target_addr | MIPS_KSEG0BASE);
							printf("Rescue Audio FW:\n");
						}
						break;

					default:
						//printf("Unknown FW (%d):\n", this_entry->type);
						continue;
				}
			}
			else if(boot_mode == BOOT_GOLD_MODE)
            {
                switch(this_entry->type)
                {
                    case FW_TYPE_GOLD_KERNEL:
                        memset(str, 0, sizeof(str));
                        sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
                        setenv("kernel_loadaddr", str);
                        printf("GOLD Kernel:\n");
                        break;
                    case FW_TYPE_GOLD_RESCUE_DT:
                        this_entry->target_addr = rtk_plat_get_dtb_target_address(this_entry->target_addr);
                        memset(str, 0, sizeof(str));
                        sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
                        setenv("fdt_loadaddr", str);
                        printf("GOLD Rescue DT:\n");
                        break;
                    case FW_TYPE_GOLD_RESCUE_ROOTFS:
                        printf("GOLD Rescue ROOTFS:\n");
                        break;
                    case FW_TYPE_GOLD_AUDIO:
                        if(boot_mode == BOOT_KERNEL_ONLY_MODE)
                            continue;
                        else
                        {
                            ipc_shm.audio_fw_entry_pt = CPU_TO_BE32(this_entry->target_addr | MIPS_KSEG0BASE);
                            printf("GOLD Audio FW:\n");
                        }
                        break;

                    default:
                        //printf("Unknown FW (%d):\n", this_entry->type);
                        continue;
                }

            }
			else
			{
				switch(this_entry->type)
				{
					case FW_TYPE_KERNEL:
						memset(str, 0, sizeof(str));
						sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
						setenv("kernel_loadaddr", str);
						printf("Kernel:\n");
						break;

					case FW_TYPE_KERNEL_DT:
						this_entry->target_addr = rtk_plat_get_dtb_target_address(this_entry->target_addr);
						memset(str, 0, sizeof(str));
						sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
						setenv("fdt_loadaddr", str);
						printf("DT:\n");
						break;

					case FW_TYPE_KERNEL_ROOTFS:
						printf("ROOTFS:\n");
						break;

					case FW_TYPE_AUDIO:
						if(boot_mode == BOOT_KERNEL_ONLY_MODE)
							continue;
						else
						{
							ipc_shm.audio_fw_entry_pt = CPU_TO_BE32(this_entry->target_addr | MIPS_KSEG0BASE);
							printf("Audio FW:\n");
						}
						break;

					case FW_TYPE_IMAGE_FILE:
						printf("IMAGE FILE:\n");
						/* assign boot_av structure */
						boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
						if(boot_logo_enable)
						{
							boot_av-> logo_enable = boot_logo_enable;
							boot_av-> logo_addr = CPU_TO_BE32(this_entry->target_addr);
							boot_av-> src_width = CPU_TO_BE32(custom_logo_src_width);
							boot_av-> src_height = CPU_TO_BE32(custom_logo_src_height);
							boot_av-> dst_width = CPU_TO_BE32(custom_logo_dst_width);
							boot_av-> dst_height = CPU_TO_BE32(custom_logo_dst_height);
						}

						break;

					case FW_TYPE_UBOOT: /* 37 */ // 2nd stage bootcode
#if defined(CONFIG_SECOND_BOOTCODE_SUPPORT) && defined(CONFIG_GOLDENBOOT_SUPPORT)
						// due to 2nd bootcode run at the same ADDR as 1st, load to other place first
						printf("Support BootCode64\n");
						continue;
#endif
						break;

					case FW_TYPE_HYP: /* 39 */
						memset(str, 0, sizeof(str));
						sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
						setenv("hyp_loadaddr", str);
						printf("Hypervisor:\n");
						break;

					default:
						//printf("Unknown FW (%d):\n", this_entry->type);
						continue;
				}
			}
			printf("\t FW Image to 0x%08x, size=0x%08x (0x%08x)\n", this_entry->target_addr, this_entry->length, this_entry->target_addr + this_entry->length);
			printf("\t FW Image fr 0x%08x \n", this_entry->offset);

			WATCHDOG_KICK();

				/* secure mode and lzma will only apply to fw image */
				if (this_entry->type == FW_TYPE_KERNEL ||
					this_entry->type == FW_TYPE_KERNEL_ROOTFS ||
					this_entry->type == FW_TYPE_RESCUE_ROOTFS ||
					this_entry->type == FW_TYPE_AUDIO )
				{
					/* get memory layout before copy fw image */
					mem_layout.bIsEncrypted = (secure_mode != NONE_SECURE_BOOT);
					mem_layout.bIsCompressed = this_entry->lzma;
					mem_layout.image_target_addr = this_entry->target_addr & (~MIPS_KSEG_MSK);
				}
				else
				{
					/* get memory layout before copy other image */
					mem_layout.bIsEncrypted = 0;
					mem_layout.bIsCompressed = 0;
					mem_layout.image_target_addr = this_entry->target_addr & (~MIPS_KSEG_MSK);
				}

				get_mem_layout_when_read_image(&mem_layout);

				// 512B aligned
				imageSize = this_entry->length + 511;
				imageSize &= (~511UL);
				imageBlkSize = imageSize / 512;

				block_no = (this_entry->offset) / 512;

				if (!rtk_sata_read(block_no, imageBlkSize, (uint *)(uintptr_t)mem_layout.flash_to_ram_addr))
				{
					printf("[ERR] Read fw error (type:%d)!\n", this_entry->type);

					return RTK_PLAT_ERR_READ_FW_IMG;
				}
#ifndef BYPASS_CHECKSUM
				/* Check checksum */
				fw_checksum = get_checksum((uchar *)(uintptr_t)mem_layout.flash_to_ram_addr, this_entry->length);

				if (this_entry->checksum != fw_checksum && secure_mode!= RTK_SECURE_BOOT)
				{
					printf("\t FW Image checksum FAILED\n");
					printf("\t FW Image entry  checksum=0x%08x\n", this_entry->checksum);
					printf("\t FW Image result checksum=0x%08x\n", fw_checksum);
					return RTK_PLAT_ERR_READ_FW_IMG;
				}
#endif
				/* if secure mode, do AES CBC decrypt */
				if (mem_layout.bIsEncrypted)
				{
					if (secure_mode == RTK_SECURE_BOOT)
					{
						unsigned int real_body_size = 0;
						//rtk_hexdump("the first 32-byte encrypted data", (unsigned char *)mem_layout.encrpyted_addr, 32);
						//rtk_hexdump("the last 512-byte encrypted data", (unsigned char *)(ENCRYPTED_LINUX_KERNEL_ADDR+this_entry->length-512), 512);

                        memset(ks,0x00,16);
                        memset(kh,0x00,16);
                        memset(kimg,0x00,16);

                        memset(aes_key, 0x00, 16);
                        memset(rsa_key, 0x00, 256);

                        switch(this_entry->type)
                        {
                            case FW_TYPE_KERNEL:
                            case FW_TYPE_RESCUE_ROOTFS:
                            case FW_TYPE_KERNEL_ROOTFS:
                            case FW_TYPE_AUDIO:
                                GetKeyFromSRAM(KH_P_SRAM_ADDR, aes_key, AES_KEY_SIZE);
                                GetKeyFromSRAM(RSA_KEY_FW_SRAM_ADDR, rsa_key, RSA_KEY_SIZE);
                                flush_cache((unsigned long) aes_key, AES_KEY_SIZE);
                                flush_cache((unsigned long) aes_key, RSA_KEY_SIZE);
                                sync();
                                //rtk_hexdump("kh_p : ", aes_key, AES_KEY_SIZE);
                                //rtk_hexdump("rsa_key_fw : ", rsa_key, RSA_KEY_SIZE);
                                break;
                            case FW_TYPE_TEE:
                                GetKeyFromSRAM(KX_P_SRAM_ADDR, aes_key, AES_KEY_SIZE);
                                GetKeyFromSRAM(RSA_KEY_TEE_SRAM_ADDR, rsa_key, RSA_KEY_SIZE);
                                flush_cache((unsigned long) aes_key, AES_KEY_SIZE);
                                flush_cache((unsigned long) aes_key, RSA_KEY_SIZE);
                                sync();
                                //rtk_hexdump("kx_p : ", aes_key, 16);
                                //rtk_hexdump("rsa_key_tee : ", rsa_key, RSA_KEY_SIZE);
                                break;
                            default:
                                break;
                        }

#ifdef CONFIG_CMD_KEY_BURNING
                        OTP_Get_Byte(OTP_K_S, ks, 16);
                        OTP_Get_Byte(OTP_K_H, kh, 16);
                        sync();
						flush_cache((unsigned int) (uintptr_t)ks, 16);
						flush_cache((unsigned int) (uintptr_t)kh, 16);
#endif
                        AES_ECB_encrypt(ks, 16, kimg,(unsigned int *) kh);
						flush_cache((unsigned long) kimg, 16);
                        sync();

                        Kh_key_ptr = (unsigned int *) kimg;
                        Kh_key_ptr = (unsigned int *) aes_key;
                        //Kh_key_ptr[0] = swap_endian(Kh_key_ptr[0]);
                        //Kh_key_ptr[1] = swap_endian(Kh_key_ptr[1]);
                        //Kh_key_ptr[2] = swap_endian(Kh_key_ptr[2]);
                        //Kh_key_ptr[3] = swap_endian(Kh_key_ptr[3]);
						flush_cache((unsigned long) aes_key, 16);

						// decrypt image
						printf("to decrypt...\n");

						flush_cache((unsigned int) mem_layout.encrpyted_addr, this_entry->length);

						if (decrypt_image((char *)(uintptr_t)mem_layout.encrpyted_addr,
							(char *)(uintptr_t)mem_layout.decrypted_addr,
							this_entry->length  - img_truncated_size,
							Kh_key_ptr))
						{
							printf("decrypt image(%d) error!\n", this_entry->type);
							return RTK_PLAT_ERR_READ_FW_IMG;
						}

						sync();
                        memset(ks,0x00,16);
                        memset(kh,0x00,16);
                        memset(kimg,0x00,16);

						//rtk_hexdump("the first 32-byte decrypted data", (unsigned char *)mem_layout.decrypted_addr, 32);

						//reverse_signature( (unsigned char *)(mem_layout.decrypted_addr + imageSize - img_truncated_size) );

                        copy_memory((void *)(uintptr_t)(mem_layout.decrypted_addr + this_entry->length - img_truncated_size), (void *)(uintptr_t)(mem_layout.encrpyted_addr + this_entry->length - img_truncated_size), img_truncated_size);
						flush_cache((unsigned int) mem_layout.decrypted_addr, this_entry->length);

                        real_body_size = (UINT32)(REG32( (uintptr_t)(mem_layout.decrypted_addr + (this_entry->length - img_truncated_size) - 4)));
                        real_body_size = swap_endian(real_body_size);
						real_body_size /= 8;

						flush_cache((unsigned int) mem_layout.decrypted_addr, this_entry->length);
						ret = Verify_SHA256_hash( (unsigned char *)(uintptr_t)mem_layout.decrypted_addr,
												  real_body_size,
												  (unsigned char *)(uintptr_t)(mem_layout.decrypted_addr + this_entry->length - img_truncated_size),
												  1, rsa_key);
						if( ret < 0 ) {
							printf("[ERR] %s: verify hash fail(%d)\n", __FUNCTION__, ret );
							return RTK_PLAT_ERR_READ_FW_IMG;
						}

						//imageSize = imageSize - img_truncated_size - SHA256_SIZE;
					}
				}

				/* if lzma type, decompress image */
				if (mem_layout.bIsCompressed)
				{
					if (lzmaBuffToBuffDecompress((uchar*)(uintptr_t)mem_layout.decompressed_addr, (SizeT *)&decompressedSize, (uchar*)(uintptr_t)mem_layout.compressed_addr, imageSize) != 0)
					{
						printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);

						return RTK_PLAT_ERR_READ_FW_IMG;
					}
				}
		}
	} // end for-loop

		if (version == FW_DESC_TABLE_V1_T_VERSION_11)
		{
			// remove unusing code
			printf("****** %s %d, not implement\n", __FUNCTION__, __LINE__);
		}
		else if (version == FW_DESC_TABLE_V1_T_VERSION_21)
		{
			// remove unusing code
			printf("****** %s %d, not implement\n", __FUNCTION__, __LINE__);
		}

	/* set boot_av_info_ptr */
	if (boot_av->dwMagicNumber == SWAPEND32(BOOT_AV_INFO_MAGICNO))
	{
		boot_av->bHDMImode = sys_logo_is_HDMI;// ignored.

		// enable audio sound
		if (boot_av->dwAudioStreamLength != 0)
		{
			;
		}

		ipc_shm.pov_boot_av_info = SWAPEND32((uint)(uintptr_t) boot_av);

		#ifdef DUBUG_BOOT_AV_INFO
		dump_boot_av_info(boot_av);
		#endif
	}

	/* Flush caches */
	flush_dcache_all();

#endif /* CONFIG_SYS_RTK_EMMC_FLASH */
	return RTK_PLAT_ERR_OK;
}


#ifdef CONFIG_POWER_DOWN_S5
int start_audio_fw(void)
{
#if defined(CONFIG_RTKSPI) && defined(CONFIG_CMD_RTKSPI)
	SizeT decompressedSize = 0x00300000;
	SizeT imageSize = CONFIG_AFW_SIZE;
        unsigned int afw_addr = CONFIG_AFW_ADDR;
        unsigned int afw_size = CONFIG_AFW_SIZE;

	rtkspi_read32_md(COMPRESSED_FW_IMAGE_ADDR, SPI_RBUS_BASE_ADDR+afw_addr, afw_size);
	if (lzmaBuffToBuffDecompress((uchar*)MIPS_AUDIO_FW_ENTRY_ADDR, &decompressedSize, (uchar*)COMPRESSED_FW_IMAGE_ADDR, imageSize) != 0)
	{
		printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);

		return RTK_PLAT_ERR_READ_FW_IMG;
	}
#else
	run_command_list("bootr f", -1, 0);
#endif

	do_go_audio_fw();
	return RTK_PLAT_ERR_OK;
}
#endif


char *rtk_plat_prepare_fw_image_from_USB(int fw_type)
{
#ifdef CONFIG_BOOT_FROM_USB
	char *filename=NULL;

	switch(fw_type)
	{
		case FW_TYPE_KERNEL: /* Linux kernel */
			filename = getenv("rescue_vmlinux");
			return (filename==NULL)?(char*) CONFIG_RESCUE_FROM_USB_VMLINUX:filename;

		case FW_TYPE_RESCUE_ROOTFS:
			filename = getenv("rescue_rootfs");
			return (filename==NULL)?(char*) CONFIG_RESCUE_FROM_USB_ROOTFS:filename;

		case FW_TYPE_KERNEL_ROOTFS:
			filename = getenv("rootfs");
			return (filename==NULL)?(char*) CONFIG_NORMAL_FROM_USB_ROOTFS:filename;

		case FW_TYPE_RESCUE_DT:
			filename = getenv("rescue_dtb");
			return (filename==NULL)?(char*) CONFIG_RESCUE_FROM_USB_DTB:filename;

		case FW_TYPE_KERNEL_DT:
			filename = getenv("dtb");
			return (filename==NULL)?(char*) CONFIG_NORMAL_FROM_USB_DTB:filename;

		case FW_TYPE_AUDIO:
			filename = getenv("rescue_audio");
			return (filename==NULL)?(char*) CONFIG_RESCUE_FROM_USB_AUDIO_CORE:filename;

		default:
			printf("Unknown FW (%d):\n", fw_type);
			return NULL;
	}
#endif
	return NULL;
}

#if defined(CONFIG_SYS_RTK_EMMC_FLASH) || defined(CONFIG_BOOT_FROM_SPI) || defined(CONFIG_SYS_RTK_NAND_FLASH)
static int rtk_plat_parse_fwdesc(fwdesc_args_t *fwdesc_args,
        uint fw_desc_table_addr, int (*read_func)(uint, uint, uint*))
{
	fw_desc_table_v1_t fw_desc_table_v1;
	part_desc_entry_v1_t *part_entry;
	fw_desc_entry_v1_t *fw_entry, *fw_entry_v1;
	fw_desc_entry_v2_t *fw_entry_v2;
	fw_desc_entry_v11_t *fw_entry_v11;
	fw_desc_entry_v21_t *fw_entry_v21;
	fw_desc_entry_v12_t *fw_entry_v12;
	fw_desc_entry_v22_t *fw_entry_v22;
	uint part_count = 0;
	uint fw_entry_num = 0;
	uint fw_entry_size = 0;
	uchar fw_desc_version;
	uint fw_desc_table_base;
	uint checksum;
	int i;


	fw_desc_table_base = FIRMWARE_DESCRIPTION_TABLE_ADDR;

	/* copy Firmware Description Table Header from flash */
	if (!(*read_func)(fw_desc_table_addr, sizeof(fw_desc_table_v1_t), (uint *)(uintptr_t)fw_desc_table_base))
	{
		printf("[ERR] %s:Read fw_desc_table_v1_t error! (0x%x, 0x%x, 0x%x)\n",
			__FUNCTION__, fw_desc_table_addr, (u32)sizeof(fw_desc_table_v1_t), fw_desc_table_base);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
	else
	{
		memcpy(&fw_desc_table_v1, (void*)(uintptr_t)fw_desc_table_base, sizeof(fw_desc_table_v1_t));
	}

	/* Check signature first! */
	if (strncmp((const char *)fw_desc_table_v1.signature,
			FIRMWARE_DESCRIPTION_TABLE_SIGNATURE,
			sizeof(fw_desc_table_v1.signature)) != 0)
	{
		printf("[ERR] %s:Signature(%s) error!\n", __FUNCTION__, fw_desc_table_v1.signature);
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	fw_desc_table_v1.checksum = BE32_TO_CPU(fw_desc_table_v1.checksum);
	fw_desc_table_v1.paddings = BE32_TO_CPU(fw_desc_table_v1.paddings);
	fw_desc_table_v1.part_list_len = BE32_TO_CPU(fw_desc_table_v1.part_list_len);
	fw_desc_table_v1.fw_list_len = BE32_TO_CPU(fw_desc_table_v1.fw_list_len);
	// In boot32 doesn't do the Big Endian

#ifdef DUBUG_FW_DESC_TABLE
	dump_fw_desc_table_v1(&fw_desc_table_v1);
#endif

	/* copy Firmware Description/Partition/Fw_entry Tables from flash */
	if (!(*read_func)(fw_desc_table_addr, fw_desc_table_v1.paddings, (uint *)(uintptr_t)fw_desc_table_base))
	{
		printf("[ERR] %s:Read all fw tables error! (0x%x, 0x%x, 0x%x)\n",
			__FUNCTION__, fw_desc_table_addr, fw_desc_table_v1.paddings, fw_desc_table_base);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	/* Check checksum */
	checksum = get_checksum((uchar*)(uintptr_t)fw_desc_table_base +
			offsetof(fw_desc_table_v1_t, version),
			sizeof(fw_desc_table_v1_t) -
			offsetof(fw_desc_table_v1_t, version) +
			fw_desc_table_v1.part_list_len +
			fw_desc_table_v1.fw_list_len);

	if (fw_desc_table_v1.checksum != checksum)
	{
		printf("[ERR] %s:Checksum not match(0x%x != 0x%x)\n", __FUNCTION__,
			fw_desc_table_v1.checksum, checksum);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	/* Check partition existence */
	if (fw_desc_table_v1.part_list_len == 0)
	{
		printf("[ERR] %s:No partition found!\n", __FUNCTION__);
		//return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
	else
	{
		part_count = fw_desc_table_v1.part_list_len / sizeof(part_desc_entry_v1_t);
	}

	//fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v1_t);
	//printf("[Info] fw desc table base: 0x%08x, count: %d\n", fw_desc_table_addr, fw_entry_num);

	part_entry = (part_desc_entry_v1_t *)(fw_desc_table_base + sizeof(fw_desc_table_v1_t));
	fw_entry = (fw_desc_entry_v1_t *)(fw_desc_table_base +
			sizeof(fw_desc_table_v1_t) +
			fw_desc_table_v1.part_list_len);

	for (i = 0; i < part_count; i++)
	{
		part_entry[i].length = BE32_TO_CPU(part_entry[i].length);

#ifdef DUBUG_FW_DESC_TABLE
		dump_part_desc_entry_v1(&(part_entry[i]));
#endif
	}

	/* Check partition type */
    /*  It so weired that we use part_entry for checking fw count? So we mark it
	if (part_entry[0].type != PART_TYPE_FW)
	{
		printf("[ERR] %s:No firmware partition found!\n", __FUNCTION__);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
	*/


	fw_desc_version = fw_desc_table_v1.version;

	switch (fw_desc_version) {
		case FW_DESC_TABLE_V1_T_VERSION_1:
			fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v1_t);
			fw_entry_size = sizeof(fw_desc_entry_v1_t);
			break;
		case FW_DESC_TABLE_V1_T_VERSION_11:
			fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v11_t);
			fw_entry_size = sizeof(fw_desc_entry_v11_t);
			break;
		case FW_DESC_TABLE_V1_T_VERSION_21:
			fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v21_t);
			fw_entry_size = sizeof(fw_desc_entry_v21_t);
			break;
		case FW_DESC_TABLE_V2_T_VERSION_2:
			fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v2_t);
			fw_entry_size = sizeof(fw_desc_entry_v2_t);
			break;
		case FW_DESC_TABLE_V2_T_VERSION_12:
			fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v12_t);
			fw_entry_size = sizeof(fw_desc_entry_v12_t);
			break;
		case FW_DESC_TABLE_V2_T_VERSION_22:
			fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v22_t);
			fw_entry_size = sizeof(fw_desc_entry_v22_t);
			break;
		default:
			printf("**** Error fw_desc_version 0x%x\n", fw_desc_version);
			return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

#ifdef CONFIG_SYS_RTK_EMMC_FLASH
	printf("[Info] fw desc table base: 0x%08x, count: %d\n", fw_desc_table_addr*EMMC_BLOCK_SIZE, fw_entry_num);
#elif defined(CONFIG_SYS_RTK_NAND_FLASH)
	printf("[Info] fw desc table base: 0x%08x, count: %d\n", fw_desc_table_addr, fw_entry_num);
#elif defined(CONFIG_BOOT_FROM_SPI)
	printf("[Info] fw desc table base: 0x%08lx, count: %d\n", fw_desc_table_addr-SPI_RBUS_BASE_ADDR, fw_entry_num);
#endif

	for (i = 0 ; i < fw_entry_num ; i++) {
		uint f_version;
		uint f_target_addr;
		u64 f_offset;
		uint f_length;
		uint f_paddings;
		void *fw_desc_ptr;

		fw_desc_ptr = (void*)fw_entry + (i * fw_entry_size);

		/* version */
		FW_ENTRY_MEMBER_GET(f_version, fw_desc_ptr, version, fw_desc_version);
		FW_ENTRY_MEMBER_SET(BE32_TO_CPU(f_version), fw_desc_ptr, version, fw_desc_version);
		/* target_addr */
		FW_ENTRY_MEMBER_GET(f_target_addr, fw_desc_ptr, target_addr, fw_desc_version);
		FW_ENTRY_MEMBER_SET(BE32_TO_CPU(f_target_addr), fw_desc_ptr, target_addr, fw_desc_version);
		/* target_offset */
		FW_ENTRY_MEMBER_GET(f_offset, fw_desc_ptr, offset, fw_desc_version);
		if (FW_DESC_BASE_VERSION(fw_desc_version) == 1) {
			FW_ENTRY_MEMBER_SET(BE32_TO_CPU((uint)f_offset),
				fw_desc_ptr, offset, fw_desc_version);
		} else {// Version 2
			FW_ENTRY_MEMBER_SET(BE64_TO_CPU(f_offset),
				fw_desc_ptr, offset, fw_desc_version);
		}
		/* length */
		FW_ENTRY_MEMBER_GET(f_length, fw_desc_ptr, length, fw_desc_version);
		FW_ENTRY_MEMBER_SET(BE32_TO_CPU(f_length), fw_desc_ptr, length, fw_desc_version);
		/* paddings */
		FW_ENTRY_MEMBER_GET(f_paddings, fw_desc_ptr, paddings, fw_desc_version);
		FW_ENTRY_MEMBER_SET(BE32_TO_CPU(f_paddings), fw_desc_ptr, paddings, fw_desc_version);
		/* checksum */
		if (FW_DESC_BASE_VERSION(fw_desc_version) == 1) {
			fw_entry_v1 = (fw_desc_entry_v1_t*)fw_desc_ptr;
			fw_entry_v1->checksum = BE32_TO_CPU(fw_entry_v1->checksum);

			if (fw_desc_version == FW_DESC_TABLE_V1_T_VERSION_11) {
				fw_entry_v11 = (fw_desc_entry_v11_t*)fw_desc_ptr;
				printf("[OK] fw_entry[%d] offset = 0x%x length = 0x%x (paddings = 0x%x) act_size = %d part_num = %d\n",
					i, fw_entry_v1->offset, fw_entry_v1->length, fw_entry_v1->paddings,
					fw_entry_v11[i].act_size, fw_entry_v11[i].part_num);
			} else if (fw_desc_version == FW_DESC_TABLE_V1_T_VERSION_21) {
				fw_entry_v21 = (fw_desc_entry_v21_t*)fw_desc_ptr;
				printf("[OK] fw_entry[%d] offset = 0x%x length = 0x%x (paddings = 0x%x) act_size = %d part_num = %d\n",
					i, fw_entry_v1->offset, fw_entry_v1->length, fw_entry_v1->paddings,
					fw_entry_v21[i].act_size, fw_entry_v21[i].part_num);
			}
		} else if (FW_DESC_BASE_VERSION(fw_desc_version) == 2) {
			fw_entry_v2 = (fw_desc_entry_v2_t*)fw_desc_ptr;
			if (fw_desc_version == FW_DESC_TABLE_V2_T_VERSION_12) {
				fw_entry_v12 = (fw_desc_entry_v12_t*)fw_desc_ptr;
				printf("[OK] fw_entry[%d] offset = 0x%Lx length = 0x%x (paddings = 0x%x) act_size = %d part_num = %d\n",
					i, fw_entry_v2->offset, fw_entry_v2->length, fw_entry_v2->paddings,
					fw_entry_v12[i].act_size, fw_entry_v12[i].part_num);
			} else if (fw_desc_version == FW_DESC_TABLE_V2_T_VERSION_22) {
				fw_entry_v22 = (fw_desc_entry_v22_t*)fw_desc_ptr;
				printf("[OK] fw_entry[%d] offset = 0x%Lx length = 0x%x (paddings = 0x%x) act_size = %d part_num = %d\n",
					i, fw_entry_v2->offset, fw_entry_v2->length, fw_entry_v2->paddings,
					fw_entry_v22[i].act_size, fw_entry_v22[i].part_num);
			}

		}

#ifdef DUBUG_FW_DESC_TABLE
		if (FW_DESC_BASE_VERSION(fw_desc_version) == 1)
			dump_fw_desc_entry_v1((fw_desc_entry_v1_t*)fw_desc_ptr);
		else if (FW_DESC_BASE_VERSION(fw_desc_version) == 2)
			dump_fw_desc_entry_v2((fw_desc_entry_v2_t*)fw_desc_ptr);
#endif
	}

	fwdesc_args->fw_desc_table_base = fw_desc_table_base;
	fwdesc_args->part_entry = part_entry;
	fwdesc_args->part_count = part_count;
	fwdesc_args->fw_entry = fw_entry;
	fwdesc_args->fw_entry_num = fw_entry_num;
	fwdesc_args->version = fw_desc_table_v1.version;
#ifdef NAS_DUAL
	fwdesc_args->seqnum = fw_desc_table_v1.seqnum;
#endif

	return RTK_PLAT_ERR_OK;
}
#endif

/*
 * Parse firmware description table and read all data from eMMC flash to ram except kernel image.
 */
int rtk_plat_prepare_fw_image_from_eMMC(void)
{
	int ret = RTK_PLAT_ERR_OK;
#ifdef CONFIG_SYS_RTK_EMMC_FLASH
	fwdesc_args_t fwdesc_args = {0};
	uint fw_desc_table_blk;	// block no of firmware description table
#ifdef NAS_DUAL
	uint fwdesc_len;
	fwdesc_args_t fwdesc_args2 = {0};
	void *fwdesc;
	static int boot_fwdesc_seq = 0;
#endif

#ifdef NAS_DUAL
	if(boot_mode==BOOT_GOLD_MODE && !boot_fwdesc_seq)
#else
	if(boot_mode==BOOT_GOLD_MODE)
#endif
	{
		printf("---------------LOAD  GOLD  FW  TABLE ---------------\n");
		eMMC_fw_desc_table_start = eMMC_bootcode_area_size + CONFIG_FACTORY_SIZE + CONFIG_FW_TABLE_SIZE;
	}
	else
	{
		printf("---------------LOAD  NORMAL FW  TABLE ---------------\n");
		eMMC_fw_desc_table_start = eMMC_bootcode_area_size + CONFIG_FACTORY_SIZE;
#ifdef NAS_DUAL
		if(boot_mode==BOOT_GOLD_MODE)
			boot_mode = BOOT_NORMAL_MODE;
#endif
	}

	/* Firmware Description Table is right behind bootcode blocks */
	fw_desc_table_blk = eMMC_fw_desc_table_start / EMMC_BLOCK_SIZE;

	ret = rtk_plat_parse_fwdesc(&fwdesc_args, fw_desc_table_blk, rtk_eMMC_read);
	if (RTK_PLAT_ERR_OK != ret)
		return ret;
#ifdef NAS_DUAL
	if(BOOT_GOLD_MODE == boot_mode)
		printf("[nas-dual]Golden fwdesc tbl seqnum: %d\n",fwdesc_args.seqnum);
	else
		printf("[nas-dual]Normal fwdesc tbl seqnum: %d\n",fwdesc_args.seqnum);
	if(boot_mode != BOOT_GOLD_MODE && !boot_fwdesc_seq) {
		fwdesc_len = ((fw_desc_table_v1_t*)(uintptr_t)fwdesc_args.fw_desc_table_base)->paddings;
		fwdesc = (void*)malloc(fwdesc_len);
		memcpy(fwdesc, (void*)(uintptr_t)fwdesc_args.fw_desc_table_base, fwdesc_len);

		eMMC_fw_desc_table_start = eMMC_bootcode_area_size + CONFIG_FACTORY_SIZE + CONFIG_FW_TABLE_SIZE;
		fw_desc_table_blk = eMMC_fw_desc_table_start / EMMC_BLOCK_SIZE;
		ret = rtk_plat_parse_fwdesc(&fwdesc_args2, fw_desc_table_blk, rtk_eMMC_read);
		if (RTK_PLAT_ERR_OK == ret && \
                  ((fwdesc_args2.seqnum > fwdesc_args.seqnum) || \
                   (0 == fwdesc_args2.seqnum && 255 == fwdesc_args.seqnum)) ) {
			printf("[nas-dual]Golden fwdesc tbl seqnum: %d\n",fwdesc_args2.seqnum);
			printf("---------------Use second FW  TABLE ---------------\n");
			memcpy(&fwdesc_args, &fwdesc_args2, sizeof(fwdesc_args_t));
			boot_fwdesc_seq = 1;
		}
		/* Restore eMMC_fw_desc_table_start */
		else {
			if (RTK_PLAT_ERR_OK != ret)
				printf("Fail to load second FW TABLE\n");
			else
				printf("[nas-dual]Golden fwdesc tbl seqnum: %d\n",fwdesc_args2.seqnum);

			eMMC_fw_desc_table_start = eMMC_bootcode_area_size + CONFIG_FACTORY_SIZE;
			memcpy((void*)(uintptr_t)fwdesc_args.fw_desc_table_base, fwdesc, fwdesc_len);
		}
		free(fwdesc);
	}
#endif

	printf("Normal boot fw follow...\n");
	ret = rtk_plat_read_fw_image_from_eMMC(
		fwdesc_args.fw_desc_table_base, fwdesc_args.part_entry,
		fwdesc_args.part_count, fwdesc_args.fw_entry,
		fwdesc_args.fw_entry_num, fwdesc_args.version);
#endif
	return ret;
}

int rtk_plat_get_fw_desc_table_start(void)
{
#ifdef CONFIG_SYS_RTK_NAND_FLASH
#ifndef CONFIG_TARGET_RTD1295

	struct mtd_info *mtd = &nand_info[nand_curr_device];
	int uboot_768KB = 0xc0000;
	int factory_4MB = 0x400000;
	int reservedSize;

	reservedSize = 6* mtd->erasesize;  //NF profile + BBT
	reservedSize += 1*4* mtd->erasesize; //Hw_setting*4
	reservedSize += ALIGN(uboot_768KB ,mtd->erasesize)*4;
	reservedSize += 1*4* mtd->erasesize; //FSBL*4
	reservedSize += ALIGN(uboot_768KB ,mtd->erasesize)*4; //TEE*4
	reservedSize += 1*4* mtd->erasesize; //BL31*4
	reservedSize += 1*4* mtd->erasesize; //RSA_FW*4
	reservedSize += 1*4* mtd->erasesize; //RSA_TEE*4
	reservedSize += ALIGN(factory_4MB ,mtd->erasesize);

#else //Not define CONFIG_TARGET_RTD1295
#ifdef NAS_ENABLE
	struct mtd_info *mtd = &nand_info[0];
#else
	struct mtd_info *mtd = &nand_info[nand_curr_device];
#endif
	int uboot_768KB = 0xc0000;
#ifdef NAS_ENABLE
	int factory_8MB = CONFIG_FACTORY_SIZE;
#else
	int factory_8MB = 0x800000;
#endif
	int reservedSize;

	reservedSize = 6* mtd->erasesize;  //NF profile + BBT
	reservedSize += 1*4* mtd->erasesize; //Hw_setting*4
	reservedSize += 1*4* mtd->erasesize; //FSBL*4
#ifndef CONFIG_SYS_NO_BL31
	reservedSize += ALIGN(uboot_768KB ,mtd->erasesize)*4; //TEE*4
	reservedSize += 1*4* mtd->erasesize; //BL31*4
	reservedSize += 1*4* mtd->erasesize; //RSA_FW*4
	reservedSize += 1*4* mtd->erasesize; //RSA_TEE*4
#endif
	reservedSize += ALIGN(uboot_768KB ,mtd->erasesize)*4;
	reservedSize += ALIGN(factory_8MB ,mtd->erasesize);

#endif //Not define CONFIG_TARGET_RTD1295
	return reservedSize;
#endif
	return 0;
}

/*
 * Parse firmware description table and read all data from NAND flash to ram except kernel image.
 */
int rtk_plat_prepare_fw_image_from_NAND(void)
{
	int ret = RTK_PLAT_ERR_OK;
#ifdef CONFIG_SYS_RTK_NAND_FLASH
	struct mtd_info *mtd = &nand_info[nand_curr_device];
	fwdesc_args_t fwdesc_args = {0};

	nand_fw_desc_table_start = rtk_plat_get_fw_desc_table_start();
	if(boot_mode==BOOT_GOLD_MODE)
	{
		printf("---------------LOAD  GOLD  FW  TABLE ---------------\n");
		nand_fw_desc_table_start += mtd->erasesize;
	}
	else
	{
		printf("---------------LOAD  NORMAL FW  TABLE ---------------\n");
	}

	ret = rtk_plat_parse_fwdesc(&fwdesc_args, nand_fw_desc_table_start, rtknand_read);

	if (RTK_PLAT_ERR_OK != ret)
		return ret;

	printf("Normal boot fw follow...\n");
	ret = rtk_plat_read_fw_image_from_NAND(
		fwdesc_args.fw_desc_table_base, fwdesc_args.part_entry,
		fwdesc_args.part_count, fwdesc_args.fw_entry,
		fwdesc_args.fw_entry_num, fwdesc_args.version);
#endif

	return ret;
}

/*
 * Parse firmware description table and read all data from SPI flash to ram except kernel image.
 */
//#define SPI_MTD_DEBUG
int rtk_plat_prepare_fw_image_from_SPI(void)
{
	int ret = RTK_PLAT_ERR_OK;
#ifdef CONFIG_SPI_MTD_STATIC
	int i;
	SizeT decompressedSize;
	SizeT imageSize;
	unsigned long target_addr;
	boot_av_info_t *boot_av;
	const fw_type_code_t spi_mtd_fws[] = {
		FW_TYPE_IMAGE_FILE
		,FW_TYPE_AUDIO
                ,FW_TYPE_KERNEL_DT
                ,FW_TYPE_KERNEL
                ,FW_TYPE_KERNEL_ROOTFS
	};
	const int fw_num = sizeof(spi_mtd_fws)/sizeof(fw_type_code_t);
	const unsigned int src_offset[] = {
		CONFIG_LOGO_ADDR
		,CONFIG_AFW_ADDR
		,CONFIG_DTS_BASE
		,CONFIG_KERNEL_ADDR
		,CONFIG_ROOTFS_ADDR
	};
	const unsigned int img_size[] = {
		CONFIG_LOGO_SIZE
		,CONFIG_AFW_SIZE
		,CONFIG_DTS_SIZE
		,CONFIG_KERNEL_SIZE
		,CONFIG_ROOTFS_SIZE
	};
	const char *target_addr_env[] = {
		"logo_loadaddr"
		,"audio_loadaddr"
		,"fdt_loadaddr"
		,"kernel_loadaddr"
		,"rootfs_loadaddr"
	};
	const unsigned long target_addr_default[] = {
		0x2600000
		,CONFIG_FW_LOADADDR
		,CONFIG_FDT_LOADADDR
		,CONFIG_KERNEL_LOADADDR
		,CONFIG_ROOTFS_LOADADDR
	};
	char buffer[CONFIG_SYS_CBSIZE] = "BOOTDEV=";
	const char *bootdevice = getenv("bootdevice");
#endif

#ifdef CONFIG_BOOT_FROM_SPI
	fwdesc_args_t fwdesc_args = {0};
	unsigned int _iSPI_base_addr;
#ifdef NAS_DUAL
	static int reserved_boot_mode;
	fwdesc_args_t fwdesc_args2 = {0};
	int ret2 = RTK_PLAT_ERR_OK;
	int latest_fwtbl = 1;

	if (BOOT_GOLD_MODE != boot_mode)
		reserved_boot_mode = boot_mode;
#endif

        printf("---------------LOAD  NORMAL FW  TABLE ---------------\n");
	_iSPI_base_addr = SPI_RBUS_BASE_ADDR + spi_fw_desc_table_start;

	ret = rtk_plat_parse_fwdesc(&fwdesc_args, _iSPI_base_addr, rtkspi_read);

#ifdef NAS_DUAL
	ret2 = rtk_plat_parse_fwdesc(&fwdesc_args2, _iSPI_base_addr + CONFIG_FW_TABLE_SIZE, rtkspi_read);
	if (RTK_PLAT_ERR_OK != ret && RTK_PLAT_ERR_OK != ret2) {
		printf(VT100_RED"Both FW TABLE are corrupted\n"VT100_NONE);
		printf("FW1 ret: %d FW2 ret: %d\n", ret, ret2);
		return ret;
	}
	else if (RTK_PLAT_ERR_OK == ret && RTK_PLAT_ERR_OK == ret2) {
		printf("[nas-dual]1st fwdesc tbl seqnum: %d\n", fwdesc_args.seqnum);
		printf("[nas-dual]2nd fwdesc tbl seqnum: %d\n", fwdesc_args2.seqnum);

		if ((fwdesc_args2.seqnum > fwdesc_args.seqnum) || \
			(0 == fwdesc_args2.seqnum && 255 == fwdesc_args.seqnum)) {
			latest_fwtbl = 2;
		}

		if ((BOOT_GOLD_MODE != boot_mode && latest_fwtbl == 1) || \
			(BOOT_GOLD_MODE == boot_mode && latest_fwtbl == 2)) {
			printf("---------------Use FIRST FW TABLE ---------------\n");
			rtk_plat_parse_fwdesc(&fwdesc_args, _iSPI_base_addr, rtkspi_read);
		}
		else {
			printf("---------------Use SECOND FW TABLE ---------------\n");
			memcpy(&fwdesc_args, &fwdesc_args2, sizeof(fwdesc_args_t));
		}
	}
	else if (RTK_PLAT_ERR_OK == ret2) {
		/* Only 2nd FW TABLE is ok */
		printf(VT100_RED"FW1 TABLE is corrupted\n"VT100_NONE);
		printf("---------------Use SECOND FW TABLE ---------------\n");
		memcpy(&fwdesc_args, &fwdesc_args2, sizeof(fwdesc_args_t));
	}
	else {
		printf("---------------Use FIRST FW TABLE ---------------\n");
		rtk_plat_parse_fwdesc(&fwdesc_args, _iSPI_base_addr, rtkspi_read);
	}

	if (BOOT_GOLD_MODE == boot_mode)
		boot_mode = reserved_boot_mode;
#endif
	if (RTK_PLAT_ERR_OK != ret)
		return ret;

	printf("Normal boot fw follow...\n");
	ret = rtk_plat_read_fw_image_from_SPI(
		fwdesc_args.fw_desc_table_base, fwdesc_args.part_entry,
		fwdesc_args.part_count, fwdesc_args.fw_entry,
		fwdesc_args.fw_entry_num, fwdesc_args.version);
#if defined(CONFIG_BFS_SUPPORT_BACKUP_SPI_IMG)
	if (RTK_PLAT_ERR_OK != ret) {
		printf(VT100_LIGHT_GREEN"---------------LOAD  BACKUP FW  TABLE ---------------\n"VT100_NONE);
		_iSPI_base_addr = SPI_RBUS_BASE_ADDR + spi_fw_desc_table_start + 0x8000;

		ret = rtk_plat_parse_fwdesc(&fwdesc_args, _iSPI_base_addr, rtkspi_read);

		if (RTK_PLAT_ERR_OK != ret)
			return ret;

		printf(VT100_LIGHT_GREEN"Backup boot fw follow...\n"VT100_NONE);
		ret = rtk_plat_read_fw_image_from_SPI(
			fwdesc_args.fw_desc_table_base, fwdesc_args.part_entry,
			fwdesc_args.part_count, fwdesc_args.fw_entry,
			fwdesc_args.fw_entry_num, fwdesc_args.version);
	}
#endif

#elif defined(CONFIG_SPI_MTD_STATIC)
	/* clear boot_av_info memory */
	boot_av = (boot_av_info_t *) MIPS_BOOT_AV_INFO_ADDR;
	memset(boot_av, 0, sizeof(boot_av_info_t));

	for (i=0; i<fw_num; i++) {
		/* Target address precedence: env addr > default addr */
		target_addr = (target_addr_env[i])?
                  getenv_ulong(target_addr_env[i],16,target_addr_default[i]):
                    target_addr_default[i];

		if (1 == accelerate_state && spi_mtd_fws[i] != FW_TYPE_AUDIO && spi_mtd_fws[i] != FW_TYPE_IMAGE_FILE)
			continue;
		else if (2 == accelerate_state && (spi_mtd_fws[i] == FW_TYPE_AUDIO || spi_mtd_fws[i] == FW_TYPE_IMAGE_FILE))
			continue;
		if (audio_fw_state && (spi_mtd_fws[i] == FW_TYPE_AUDIO || spi_mtd_fws[i] == FW_TYPE_GOLD_AUDIO))
			continue;

		/* No compression on kernel DTB and initrd */
		switch (spi_mtd_fws[i])
		{
			case FW_TYPE_KERNEL_ROOTFS:
				memset((void*)target_addr, 0, CONFIG_INITRD_SIZE);
			case FW_TYPE_KERNEL_DT:
				rtkspi_read32_md(target_addr, SPI_RBUS_BASE_ADDR+src_offset[i], img_size[i]);
				if(Verify_SHA256_hash((unsigned char *)target_addr, img_size[i]-32, (unsigned char *)(target_addr + img_size[i] - 32), 0, NULL)) {
					return RTK_PLAT_ERR_READ_FW_IMG;
				}
				memset((void*)(target_addr+img_size[i]-32), 0, 32);
				continue;
				break;
			default:
				break;
		}
		rtkspi_read32_md(COMPRESSED_FW_IMAGE_ADDR, SPI_RBUS_BASE_ADDR+src_offset[i], img_size[i]);
		if(Verify_SHA256_hash((unsigned char *)(uintptr_t)COMPRESSED_FW_IMAGE_ADDR, img_size[i]-32, (unsigned char *)(uintptr_t)(COMPRESSED_FW_IMAGE_ADDR + img_size[i] - 32), 0, NULL)) {
#ifndef SPI_MTD_DEBUG
			if (FW_TYPE_IMAGE_FILE == spi_mtd_fws[i] || FW_TYPE_AUDIO == spi_mtd_fws[i]) continue;
#endif
			return RTK_PLAT_ERR_READ_FW_IMG;
		}
		memset((void*)(uintptr_t)(COMPRESSED_FW_IMAGE_ADDR+img_size[i]-32), 0, 32);

		decompressedSize = 0;
		imageSize = img_size[i];
		if (lzmaBuffToBuffDecompress((uchar*)target_addr, &decompressedSize, (uchar*)COMPRESSED_FW_IMAGE_ADDR, imageSize) != 0)
		{
			printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);
#ifndef SPI_MTD_DEBUG
			if (FW_TYPE_IMAGE_FILE == spi_mtd_fws[i] || FW_TYPE_AUDIO == spi_mtd_fws[i]) continue;
#endif
			return RTK_PLAT_ERR_READ_FW_IMG;
		}
		if(FW_TYPE_AUDIO == spi_mtd_fws[i]) {
			ipc_shm.audio_fw_entry_pt = CPU_TO_BE32(target_addr | MIPS_KSEG0BASE);
		}
		else if(boot_logo_enable && FW_TYPE_IMAGE_FILE == spi_mtd_fws[i]) {
			boot_av-> logo_addr = CPU_TO_BE32(target_addr);
		}
	}

	if (accelerate_state)
		accelerate_state++;

	if(bootdevice) {
		strncat(buffer, bootdevice, strlen(bootdevice));
		setenv("nas_part", buffer);
	}

	/* assign boot_av structure */
	boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
	if(boot_logo_enable)
	{
		boot_av-> logo_enable = boot_logo_enable;
		boot_av-> src_width = CPU_TO_BE32(custom_logo_src_width);
		boot_av-> src_height = CPU_TO_BE32(custom_logo_src_height);
		boot_av-> dst_width = CPU_TO_BE32(custom_logo_dst_width);
		boot_av-> dst_height = CPU_TO_BE32(custom_logo_dst_height);
	}
	boot_av->bHDMImode = sys_logo_is_HDMI;// ignored.
	ipc_shm.pov_boot_av_info = SWAPEND32((uint)(uintptr_t) boot_av);
	/* Flush caches */
	flush_dcache_all();

	if (boot_from_flash == BOOT_FROM_FLASH_NORMAL_MODE) {
		do_go_audio_fw();
	}
#endif

	return ret;
}

/*
 * Parse firmware description table and read all data from SD flash to ram except kernel image.
 */
int rtk_plat_prepare_fw_image_from_SD(void)
{
	int ret = RTK_PLAT_ERR_OK;

	printf("---------------LOAD  NORMAL FW  TABLE ---------------\n");

#if 0 // for SD
	// add your code here
#endif

	ret = rtk_plat_read_fw_image_from_SD();

	return ret;
}

/*
 * Parse firmware description table and read all data from SATA to ram except kernel image.
 */
int rtk_plat_prepare_fw_image_from_SATA(void)
{
	int ret = RTK_PLAT_ERR_OK;
#ifdef CONFIG_SYS_RTK_SATA_STORAGE
	fw_desc_table_v1_t fw_desc_table_v1;
	part_desc_entry_v1_t *part_entry;
	fw_desc_entry_v1_t *fw_entry;
	uint part_count = 0;
	uint fw_total_len;
	uint fw_total_paddings;
	uint fw_entry_num = 0;
	uint fw_desc_table_base;
	uint fw_desc_table_blk;	// block no of firmware description table
	uint checksum;
	int i;

	if (sata_curr_device == -1) {
		if (sata_initialize()) {
			printf("---------------SATA init fail, try again ---------------\n");
			if (sata_initialize()) {
				printf("---------------No SATA device ---------------\n");
				return RTK_PLAT_ERR_BOOT;
			}
		}
	}

    if(boot_mode==BOOT_GOLD_MODE)
    {
        printf("---------------LOAD  GOLD  FW  TABLE (%d) ---------------\n", boot_mode);
    }
    else if(boot_mode==BOOT_RESCUE_MODE)
    {
        printf("---------------LOAD  RESCUE FW  TABLE (%d) ---------------\n", boot_mode);
    }
    else if(boot_mode==BOOT_ANDROID_MODE)
    {
        printf("---------------LOAD  NORMAL FW  TABLE(%d) ---------------\n", boot_mode);
    }
    else
    {
        printf("---------------LOAD  NORMAL FW  TABLE(%d) ---------------\n", boot_mode);
    }

    sata_fw_desc_table_start = 0x4400;
	fw_desc_table_base = FIRMWARE_DESCRIPTION_TABLE_ADDR; /* 0x06400000 */

	/* Firmware Description Table is right behind bootcode blocks */
	fw_desc_table_blk = sata_fw_desc_table_start / 512;

	/* copy Firmware Description Table Header from flash */
	if (!rtk_sata_read(fw_desc_table_blk, sizeof(fw_desc_table_v1_t), (uint *)(uintptr_t)fw_desc_table_base))
	{
		printf("[ERR] %s:Read fw_desc_table_v1_t error! (0x%x, 0x%x, 0x%x)\n",
			__FUNCTION__, (unsigned int)fw_desc_table_blk, (unsigned int)sizeof(fw_desc_table_v1_t), (unsigned int)fw_desc_table_base);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
	else
	{
		memcpy(&fw_desc_table_v1, (void*)(uintptr_t)fw_desc_table_base, sizeof(fw_desc_table_v1_t));
	}

	/* Check signature first! */
	if (strncmp((const char *)fw_desc_table_v1.signature,
			FIRMWARE_DESCRIPTION_TABLE_SIGNATURE,
			sizeof(fw_desc_table_v1.signature)) != 0)
	{
		printf("[ERR] %s:Signature(%s) error!\n", __FUNCTION__, fw_desc_table_v1.signature);
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	fw_desc_table_v1.checksum = BE32_TO_CPU(fw_desc_table_v1.checksum);
	fw_desc_table_v1.paddings = BE32_TO_CPU(fw_desc_table_v1.paddings);
	fw_desc_table_v1.part_list_len = BE32_TO_CPU(fw_desc_table_v1.part_list_len);
	fw_desc_table_v1.fw_list_len = BE32_TO_CPU(fw_desc_table_v1.fw_list_len);

#ifdef DUBUG_FW_DESC_TABLE
	dump_fw_desc_table_v1(&fw_desc_table_v1);
#endif

	/* copy Firmware Description/Partition/Fw_entry Tables from flash */
	if (!rtk_sata_read(fw_desc_table_blk, fw_desc_table_v1.paddings, (uint *)(uintptr_t)fw_desc_table_base))
	{
		printf("[ERR] %s:Read all fw tables error! (0x%x, 0x%x, 0x%x)\n",
			__FUNCTION__, fw_desc_table_blk, fw_desc_table_v1.paddings, fw_desc_table_base);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	/* Check checksum */
	checksum = get_checksum((uchar*)(uintptr_t)fw_desc_table_base +
			offsetof(fw_desc_table_v1_t, version),
			sizeof(fw_desc_table_v1_t) -
			offsetof(fw_desc_table_v1_t, version) +
			fw_desc_table_v1.part_list_len +
			fw_desc_table_v1.fw_list_len);

	if (fw_desc_table_v1.checksum != checksum)
	{
		printf("[ERR] %s:Checksum not match(0x%x != 0x%x)\n", __FUNCTION__,
			fw_desc_table_v1.checksum, checksum);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	/* Check partition existence */
	if (fw_desc_table_v1.part_list_len == 0)
	{
		printf("[ERR] %s:No partition found!\n", __FUNCTION__);
		//return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
	else
	{
		part_count = fw_desc_table_v1.part_list_len / sizeof(part_desc_entry_v1_t);
	}

	fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v1_t);
	printf("[Info] fw desc table base: 0x%08x, count: %d\n", sata_fw_desc_table_start, fw_entry_num);

	part_entry = (part_desc_entry_v1_t *)(fw_desc_table_base + sizeof(fw_desc_table_v1_t));
	fw_entry = (fw_desc_entry_v1_t *)(fw_desc_table_base +
			sizeof(fw_desc_table_v1_t) +
			fw_desc_table_v1.part_list_len);

	for (i = 0; i < part_count; i++)
	{
		part_entry[i].length = BE32_TO_CPU(part_entry[i].length);

#ifdef DUBUG_FW_DESC_TABLE
		dump_part_desc_entry_v1(&(part_entry[i]));
#endif
	}

	/* Check partition type */
    /*  It so weired that we use part_entry for checking fw count? So we mark it
	if (part_entry[0].type != PART_TYPE_FW)
	{
		printf("[ERR] %s:No firmware partition found!\n", __FUNCTION__);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
    */

	fw_total_len = 0;
	fw_total_paddings = 0;

	/* Parse firmware entries and compute fw_total_len */
	switch (fw_desc_table_v1.version)
	{
		case FW_DESC_TABLE_V1_T_VERSION_1:
			fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v1_t);

			for (i = 0; i < fw_entry_num; i++)
			{
				fw_entry[i].version     = BE32_TO_CPU(fw_entry[i].version);
				fw_entry[i].target_addr = BE32_TO_CPU(fw_entry[i].target_addr);
				fw_entry[i].offset      = BE32_TO_CPU(fw_entry[i].offset);
				fw_entry[i].length      = BE32_TO_CPU(fw_entry[i].length);
				fw_entry[i].paddings    = BE32_TO_CPU(fw_entry[i].paddings);
				fw_entry[i].checksum    = BE32_TO_CPU(fw_entry[i].checksum);

#ifdef DUBUG_FW_DESC_TABLE
				dump_fw_desc_entry_v1(&(fw_entry[i]));
#endif

				fw_total_len += fw_entry[i].length;
				fw_total_paddings += fw_entry[i].paddings;
			}


			break;

		case FW_DESC_TABLE_V1_T_VERSION_11:
			// remove unusing code
			printf("****** %s %d, not implement\n", __FUNCTION__, __LINE__);
			break;

		case FW_DESC_TABLE_V1_T_VERSION_21:
			// remove unusing code
			printf("****** %s %d, not implement\n", __FUNCTION__, __LINE__);
			break;

		default:
			printf("[ERR] %s:unknown version:%d\n", __FUNCTION__, fw_desc_table_v1.version);
			return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	if(sata_boot_debug) {
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	printf("Start loading fw (mode %d)...\n", boot_mode);

	ret = rtk_plat_read_fw_image_from_SATA(
		fw_desc_table_base, part_entry, part_count,
		fw_entry, fw_entry_num,
		fw_desc_table_v1.version);

#endif // CONFIG_SYS_RTK_SATA_STORAGE

	return ret;
}

//#define DEBUG_SKIP_BOOT_ALL
//#define DEBUG_SKIP_BOOT_LINUX
//#define DEBUG_SKIP_BOOT_AV
#ifdef CONFIG_SYS_RTK_NAND_FLASH
extern int rtk_plat_boot_prep_partition(void);
#endif
#if defined(NAS_ENABLE)
extern int rtk_plat_boot_prep_kernelargs(void);
#endif

#if defined(CONFIG_RTK_ARM32) || defined(CONFIG_CPU_V7)
static int rtk_call_bootm(void)
{
	char *bootm_argv[] = { "bootm", NULL, NULL, NULL, NULL };
	int ret = 0;
	int j;
	int argc=4;

	if (getenv("hyp_loadaddr")) {
		bootm_argv[1] = getenv("hyp_loadaddr");
	} else if ((bootm_argv[1] = getenv("kernel_loadaddr")) == NULL) {
		bootm_argv[1] =(char*) CONFIG_KERNEL_LOADADDR;
	}

	if ((bootm_argv[2] = getenv("rootfs_loadaddr")) == NULL) {
		bootm_argv[2] =(char*) CONFIG_ROOTFS_LOADADDR;
	}

	if ((bootm_argv[3] = getenv("fdt_loadaddr")) == NULL) {
		bootm_argv[3] =(char*) CONFIG_FDT_LOADADDR;
	}
#ifdef CONFIG_NAS_ENABLE
	void *fdt_addr = (void*)simple_strtoul(bootm_argv[3], NULL, 16);

	int nodeoffset;
	struct fdt_property *prop;
	int err, oldlen, newlen;
	char *str = NULL;

	if(!fdt_check_header(fdt_addr)) {
		nodeoffset = fdt_find_or_add_subnode(fdt_addr, 0, "chosen");
		if(nodeoffset >= 0){
			prop = fdt_get_property_w(fdt_addr, nodeoffset, "bootargs", &oldlen);
			if (prop) {
				newlen = oldlen+8+strlen(PLAIN_VERSION)+2+strlen(U_BOOT_DATE)+3+strlen(U_BOOT_TIME)+1+1;
				str = (char *)malloc(newlen);
				if (str) {
					memset(str, 0, newlen);
					memcpy(str, prop->data, oldlen);
					sprintf(str+oldlen-1, " U-boot=%s (%s - %s)",
						PLAIN_VERSION, U_BOOT_DATE, U_BOOT_TIME);
				}
				err = fdt_setprop_string(fdt_addr, nodeoffset, "bootargs", str);
				if (err < 0) {
					printf("WARNING: could not set version in bootargs %s.\n",
					       fdt_strerror(err));
				}
				if (str)
					free(str);
			}

		}
	}
#endif

	/*
	 * - do the work -
	 * exec subcommands of do_booti to init the images
	 * data structure
	 */
	debug("bootm_argv ={ ");
	for (j = 0; j < argc; j++)
			printf("%s,",bootm_argv[j]);
	printf("}\n");

#ifdef CONFIG_SYS_RTK_NAND_FLASH
	rtk_plat_boot_prep_partition();
#endif
#if defined(NAS_ENABLE)
	rtk_plat_boot_prep_kernelargs();
#endif

#ifdef CONFIG_CMD_RTKFDT
	extern void rtkfdt_add_factory(void);
	DDDDYELLOW("[Info] convert some env variable to fdt:factory node\n");
	rtkfdt_add_factory();
#endif

	ret = do_bootm(find_cmd("do_bootm"), 0, argc, bootm_argv);

	if (ret) {
		printf("ERROR do_bootm failed!\n");
		return -1;
	}

	return 1;
}
#else
static int rtk_call_booti(void)
{
	char *booti_argv[] = { "booti", NULL, NULL, NULL, NULL };
	int ret = 0;
	int j;
	int argc=4;

	if (getenv("hyp_loadaddr")) {
		booti_argv[1] = getenv("hyp_loadaddr");
	} else if ((booti_argv[1] = getenv("kernel_loadaddr")) == NULL) {
		booti_argv[1] =(char*) CONFIG_KERNEL_LOADADDR;
	}
	
	if ((booti_argv[2] = getenv("rootfs_loadaddr")) == NULL) {
		booti_argv[2] =(char*) CONFIG_ROOTFS_LOADADDR;
	}

	if ((booti_argv[3] = getenv("fdt_loadaddr")) == NULL) {
		booti_argv[3] =(char*) CONFIG_FDT_LOADADDR;
	}
#ifdef CONFIG_NAS_ENABLE
	void *fdt_addr = (void*)simple_strtoul(booti_argv[3], NULL, 16);

#ifdef CONFIG_RTD161x
	ion_media_heap0_size_str = getenv("ion_media_heap0_size");
	ion_media_heap1_size_str = getenv("ion_media_heap1_size");
	ion_media_heap0_size_MB = -1;
	ion_media_heap1_size_MB = -1;
	if (fdt_addr) {
		if (ion_media_heap0_size_str)
			ion_media_heap0_size_MB = simple_strtoul(ion_media_heap0_size_str, NULL, 10);	
		if (ion_media_heap1_size_str) 
			ion_media_heap1_size_MB = simple_strtoul(ion_media_heap1_size_str, NULL, 10);

		if ( (ion_media_heap0_size_MB == 0) && (ion_media_heap1_size_MB == 0)) {
			fdt_disable_rtk_ion(fdt_addr);
		}
		else {
			if ( ion_media_heap0_size_MB > 0 ) {
				if ( ion_media_heap0_size_MB > ION_MEDIA_HEAP0_SIZE_MAX ) {
					printf(	"ion_media_heap0_size exceed MAX\n"
						"ion_media_heap0_size is not changed");
				}
				else {
					/* ion_media_heap0_size_MB = 1~ION_MEDIA_HEAP0_SIZE_MAX */
					printf(	"ion_media_heap0_addr: 0x%08X\n"
						"ion_media_heap0_size: %d MB\n"
						, ION_MEDIA_HEAP_0_PHYS
						, (uint32_t)ion_media_heap0_size_MB);
					fdt_ion_heap(fdt_addr, ION_MEDIA_HEAP_0_PHYS, (uint32_t)ion_media_heap0_size_MB);
				}
			}
			if ( ion_media_heap1_size_MB > 0 ) {
				if ( ion_media_heap1_size_MB > ION_MEDIA_HEAP1_SIZE_MAX ) {
					printf(	"ion_media_heap1_size exceed MAX\n"
						"ion_media_heap1_size is not changed");
				}
				else {
					/* ion_media_heap1_size_MB = 1~ION_MEDIA_HEAP1_SIZE_MAX */
					printf(	"ion_media_heap1_addr: 0x%08X\n"
						"ion_media_heap1_size: %d MB\n"
						, ION_MEDIA_HEAP_1_PHYS
						, (uint32_t)ion_media_heap1_size_MB);
					fdt_ion_heap(fdt_addr, ION_MEDIA_HEAP_1_PHYS, (uint32_t)ion_media_heap1_size_MB);
				}
			}

		}
	}

#endif /*CONFIG_RTD161x */

	int nodeoffset;
	struct fdt_property *prop;
	int err, oldlen, newlen;
	char *str = NULL;

	if(!fdt_check_header(fdt_addr)) {
		nodeoffset = fdt_find_or_add_subnode(fdt_addr, 0, "chosen");
		if(nodeoffset >= 0){
			prop = fdt_get_property_w(fdt_addr, nodeoffset, "bootargs", &oldlen);
			if (prop) {
				newlen = oldlen+8+strlen(PLAIN_VERSION)+2+strlen(U_BOOT_DATE)+3+strlen(U_BOOT_TIME)+1+1;
				str = (char *)malloc(newlen);
				if (str) {
					memset(str, 0, newlen);
					memcpy(str, prop->data, oldlen);
					sprintf(str+oldlen-1, " U-boot=%s (%s - %s)",
						PLAIN_VERSION, U_BOOT_DATE, U_BOOT_TIME);
				}
				err = fdt_setprop_string(fdt_addr, nodeoffset, "bootargs", str);
				if (err < 0) {
					printf("WARNING: could not set version in bootargs %s.\n",
					       fdt_strerror(err));
				}
				if (str)
					free(str);
			}

		}
	}
#endif

	/*
	 * - do the work -
	 * exec subcommands of do_booti to init the images
	 * data structure
	 */
	debug("booti_argv ={ ");
	for (j = 0; j < argc; j++)
			debug("%s,",booti_argv[j]);
	debug("}\n");

#ifdef CONFIG_SYS_RTK_NAND_FLASH
	rtk_plat_boot_prep_partition();
#endif
#if defined(NAS_ENABLE)
	rtk_plat_boot_prep_kernelargs();
#endif

#ifdef CONFIG_CMD_RTKFDT
	extern void rtkfdt_add_factory(void);
	DDDDYELLOW("[Info] convert some env variable to fdt:factory node\n");
	rtkfdt_add_factory();
#endif

	ret = do_booti(find_cmd("do_booti"), 0, argc, booti_argv);

	if (ret) {
		printf("ERROR do_booti failed!\n");
		return -1;
	}

	return 1;
}
#endif

int rtk_plat_set_fw(void)
{
	int ret = RTK_PLAT_ERR_OK;

	printf("[BPI] %s\n", __func__);

	printf("Start Boot Setup ... ");

	/* reset some shared memory */
	reset_shared_memory();

#ifdef DEBUG_SKIP_BOOT_ALL // Skip by CK
	printf("(CK skip)\n");
	return RTK_PLAT_ERR_PARSE_FW_DESC;
#else
	printf("\n");
#endif

#if defined(NAS_ENABLE) && defined(CONFIG_RTD161x)
	/* if excute "go kf" & "go ru" in uboot cmdline, this part will not be excuted */
	ion_media_heap0_size_str = getenv("ion_media_heap0_size");
	ion_media_heap1_size_str = getenv("ion_media_heap1_size");
	ion_media_heap0_size_MB = -1;
	ion_media_heap1_size_MB = -1;

	if (ion_media_heap0_size_str)
		ion_media_heap0_size_MB = simple_strtoul(ion_media_heap0_size_str, NULL, 10);
	if (ion_media_heap1_size_str)
		ion_media_heap1_size_MB = simple_strtoul(ion_media_heap1_size_str, NULL, 10);

	if ( (ion_media_heap0_size_MB == 0) && (ion_media_heap1_size_MB == 0)) {
		skip_avfw_entry = 1;
	}
#endif /* defined(NAS_ENABLE) && defined(CONFIG_RTD161x) */

	if (boot_from_usb != BOOT_FROM_USB_DISABLE) // workaround path that read fw img from usb
	{
		ret = rtk_plat_read_fw_image_from_USB(0);
	}
	else
	{
		/* parse fw_desc_table, and read all data from flash to ram except kernel image */
		if (boot_flash_type == BOOT_EMMC)
		{
			/* For eMMC */
			ret = rtk_plat_prepare_fw_image_from_eMMC();
		}
		else if (boot_flash_type == BOOT_SATA)
		{
			/* For SATA */
			ret = rtk_plat_prepare_fw_image_from_SATA();
		}
		else if (boot_flash_type == BOOT_NAND)
		{
			/* For NAND */
			ret = rtk_plat_prepare_fw_image_from_NAND();
		}
		else if (boot_flash_type == BOOT_SD)
		{
			/* For SD */
			printf("[BPI] %s, boot flash is SD\n", __func__);
			ret = rtk_plat_prepare_fw_image_from_SD();
		}
		else
		{
#ifdef CONFIG_BOOT_FROM_SATA
			ret = rtk_plat_prepare_fw_image_from_SATA();
#else
			/* For SPI */
			ret = rtk_plat_prepare_fw_image_from_SPI();
#ifdef CONFIG_BOOT_FROM_USB
			if(ret == RTK_PLAT_ERR_OK)
				ret = rtk_plat_read_fw_image_from_USB(0);
#endif /* CONFIG_BOOT_FROM_USB */
#endif /* CONFIG_BOOT_FROM_SATA */
		}
	}

#if CONFIG_ANDROID_RECOVERY
    /* factory save ---------work space----------------*/
    //gen recovery signature(update.zip from backup partition).
    if((ret == RTK_PLAT_ERR_OK) && (boot_mode == BOOT_GOLD_MODE))
    {
        printf("------------recovery write start--------------\n");

        /* write in emmc */
        bootloader_message *boot=(bootloader_message *)BACKUP_DESCRIPTION_RECOVERY_ADDR;
        memset(boot, 0, sizeof(bootloader_message));
        memset(boot->command, '\0', sizeof(boot->command));
        memset(boot->recovery, '\0', sizeof(boot->recovery));
        sprintf(boot->command, "boot-recovery");
        sprintf(boot->recovery, "recovery\n--update_package=BACKUP:update.zip\n--locale=en_GB");

#ifdef CONFIG_SYS_FACTORY
    	ret = factory_write(RECOVERY_FILE_IN_FACTORY, (char *)boot, CONFIG_RECOVERY_SIZE);
		if (ret != 0)
        {
            // failed case
    		printf("[ENV] write_recovery failed\n");
    	}
    	else
		    factory_save();
#else
	    printf("[ENV][WARN] CONFIG_SYS_FACTORY is not defined.\n");
#endif
        printf("------------recovery write end--------------\n");
        ret = RTK_PLAT_ERR_OK;
    }
#endif

#ifndef DEBUG_SKIP_BOOT_AV // mark for boot linux kernel only
	if (boot_from_flash == BOOT_FROM_FLASH_NORMAL_MODE)
	{
		if (ret == RTK_PLAT_ERR_OK)
		{
			if(!accelerate_state && !audio_fw_state)
			{
				/* Enable ACPU */
				ret = do_go_audio_fw();
				/* Enable VCPU */
				ret = do_go_video_fw();
			}
		}
	}
	else
	{
		printf("[Skip A] boot manual mode\n");
	}
#endif

	return ret;
}

static void gmt_g2227_set_mode(void)
{
#ifdef CONFIG_GMT_G2227

#ifdef CONFIG_BOOT_DCDC1_FORCE_PWM
      run_command("pmic set dcdc1_mode force_pwm", 0);
#endif

#ifdef CONFIG_BOOT_DCDC2_FORCE_PWM
	run_command("pmic set dcdc2_mode force_pwm", 0);
#endif

#ifdef CONFIG_BOOT_DCDC3_FORCE_PWM
	run_command("pmic set dcdc3_mode force_pwm", 0);
#endif

#ifdef CONFIG_BOOT_DCDC4_FORCE_PWM
	run_command("pmic set dcdc4_mode force_pwm", 0);
#endif

#ifdef CONFIG_BOOT_DCDC5_FORCE_PWM
	run_command("pmic set dcdc5_mode force_pwm", 0);
#endif

#ifdef CONFIG_BOOT_DCDC6_FORCE_PWM
	run_command("pmic set dcdc6_mode force_pwm", 0);
#endif

#endif /* CONFIG_GMT_G2227 */
}

//all standard boot_cmd entry.
int rtk_plat_do_boot_linux(void)
{
	gmt_g2227_set_mode();

#if defined(CONFIG_RTK_ARM32) || defined(CONFIG_CPU_V7)
	rtk_call_bootm();
#else
	rtk_call_booti();
#endif

	/* Reached here means jump to kernel entry flow failed */

	return RTK_PLAT_ERR_BOOT;

}
/*
 ************************************************************************
 *
 * This is the final part before booting Linux in realtek platform:
 * we need to move audio/video firmware and stream files
 * from flash to ram. We will also decompress or decrypt image files,
 * if necessary, which depends on the information from flash writer.
 *
 ************************************************************************
 */
#ifdef CONFIG_CUSTOMIZE_BOOTFLOW_1
extern int normal_boot;
#endif
int  rtk_plat_boot_handler(void)
{
	int ret = RTK_PLAT_ERR_OK;

	printf("[BPI] %s\n", __func__);

	/* copy audio/video firmware and stream files from flash to ram */
	ret = rtk_plat_set_fw();

	if (ret == RTK_PLAT_ERR_OK)
	{
#ifndef DEBUG_SKIP_BOOT_LINUX
		if (boot_from_flash == BOOT_FROM_FLASH_NORMAL_MODE)
		{
			/* go Linux */
#ifdef CONFIG_REALTEK_WATCHDOG
			WATCHDOG_KICK();
#else
			WATCHDOG_DISABLE();
#endif

			EXECUTE_CUSTOMIZE_FUNC(1); // insert execute customer callback at here

#ifdef CONFIG_CUSTOMIZE_BOOTFLOW_1
			if (normal_boot)
				ret = rtk_plat_do_boot_linux ();
			else
				printf("Skip Normal BOOT flow\n");
#else
			ret = rtk_plat_do_boot_linux ();
#endif
		}
		else
		{
			printf("[Skip K] boot manual mode (execute \"go all\")\n");
		}
#endif
	}

	return ret;
}

int rtk_plat_do_bootr(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int ret = RTK_PLAT_ERR_OK;

	printf("[BPI] %s\n", __func__);

	/* reset boot flags */
	boot_from_flash = BOOT_FROM_FLASH_NORMAL_MODE;
	boot_from_usb = BOOT_FROM_USB_DISABLE;

	/* parse option */
	if (argc == 1)
	{
		boot_from_usb = BOOT_FROM_USB_DISABLE;
	}
	else if (argc == 2 && argv[1][0] == 'u')
	{
		if (argv[1][1] == 'z')
		{
			boot_from_usb = BOOT_FROM_USB_COMPRESSED;
		}
		else if (argv[1][1] == '\0')
		{
			boot_from_usb = BOOT_FROM_USB_UNCOMPRESSED;
		}
		else
		{
			return CMD_RET_USAGE;
		}
	}
	else if (argc == 2 && argv[1][0] == 'm')
	{
		boot_from_flash = BOOT_FROM_FLASH_MANUAL_MODE;
	}
#ifndef NAS_DUAL
	else if (argc == 2 && argv[1][0] == 'f')
	{
		boot_from_flash = BOOT_FROM_FLASH_MANUAL_MODE;
		accelerate_state = 1;
		/*The bootr f command is for faster blue logo*/
	}
#endif
	else
	{
		return CMD_RET_USAGE;
	}

	WATCHDOG_KICK();
	ret = rtk_plat_boot_handler();

    if (ret != RTK_PLAT_ERR_OK) {
#if defined(NAS_ENABLE) && defined(CONFIG_SPI_MTD_STATIC)
#if defined(CONFIG_CMD_NET)
	ret = run_command("run upgrade_img_tftp", 0);
#endif // tftp
#if defined(CONFIG_CMD_USB) && defined(CONFIG_USB_STORAGE)
	if(ret) ret=run_command("run upgrade_img_usb", 0);
#endif // USB
	if(!ret) run_command("reset", 0);
#else
        /*   LOAD GOLD FW   */
        ret = RTK_PLAT_ERR_OK;
        boot_mode=BOOT_GOLD_MODE;
        accelerate_state = 0;
        ret = rtk_plat_boot_handler();
#endif
    }

#ifdef CONFIG_RESCUE_FROM_USB
	if (ret != RTK_PLAT_ERR_OK) {
		ret = boot_rescue_from_usb();
	}
#endif /* CONFIG_RESCUE_FROM_USB */

	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	bootr, 2, 0,	rtk_plat_do_bootr,
	"boot realtek platform",
	"[u/uz]\n"
	"\tf   - boot faster of blue logo\n"
	"\tu   - boot from usb\n"
	"\tuz  - boot from usb (use lzma image)\n"
	"\tm   - read fw from flash but boot manually (go all)\n"
);

#endif /* CONFIG_BOOT_FOR_WD */

