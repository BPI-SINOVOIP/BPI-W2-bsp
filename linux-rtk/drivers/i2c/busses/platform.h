/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * This file contains platform-related defines for Realtek boards.
 *
 * Copyright (C) 2010 by Chien-An Lin <colin@realtek.com.tw>
 */


#ifndef _MACH_PLATFORM_H
#define _MACH_PLATFORM_H

#define AES_CCMP_LEN		571
#define SYSTEM_PARAMETERS_LEN	960 // 1~6
#define MODEL_CONFIG_LEN	64	// Originally this value is 20 for libra 10bytes config and now we support 32byes for customer extra use
#define SIGNATURE_LEN		129
#define AES_IMG_KEY_LEN		16
#define RSA_KEY_MODULUS_LEN	128
#define _PRIV_LEN		1024
#define _CUSTOM_PARAM_LEN	4096
#if defined(CONFIG_REALTEK_PCBMGR)
#define panel_parameter_LEN     129
#define pcb_enum_parameter_LEN  4096
#endif

typedef struct {
	int mode;		// 0: NTSC, 1: PAL
	int size;
	int color[4];
} logo_info_struct;

/* The format of "bootrev" is like "00.00.26c". The second byte of it stands for board id, and the upper half byte of board id stands for CPU id */
/* The new format of "bootrev" is extended to be "xxxx.xxxx.xx". We support both "xx.xx.xx" and "xxxx.xxxx.xx".  */
typedef enum {
	realtek_qa_board		=0x0,
	realtek_mk_board		=0x1,
	realtek_1261_demo_board		=0x2,		/* first demo board */
	realtek_1281_demo_board		=0x4,		/* little blue */
	realtek_mk2_board		=0x5,		/* little white */
	realtek_photoviewer_board	=0x7,
	realtek_avhdd_demo_board	=0x8,		/* little yellow */
	realtek_pvr_demo_board		=0x9,
	realtek_pvrbox_demo_board	=0xA,
	realtek_avhdd2_demo_board	=0xB,		/* little yellow 2 */
	realtek_pvrbox_pc_demo_board	=0xC,		/* little yellow 2 with PC install */
	realtek_1071_avhdd_mk_demo_board	=0xD,	/* 1071 AVHDD MK Demo Board */
	realtek_1261_avhdd_hdd25_demo_board	=0xE,	/* 1261 2.5" AVHDD Demo Board */
	realtek_neptune_qa_board	=0x0101,
	realtek_neptuneB_qa_board	=0x1101,
	realtek_neptune_demo_board	=0x0102,
	realtek_neptuneB_demo_board	=0x1102,
	realtek_1282_neptuneB_qa_board	=0x1103, /* 1282 Neptune B, QA Board. */
	realtek_1282_neptuneB_demo_board	=0x1104, /* 1282 Neptune B, DEMO board. */
	realtek_1262_neptuneB_pc_install_demo_board	=0x1105, /* 1262 Neptune B, DEMO board with PC install. */
	realtek_1262_neptuneB_mk_board	=0x1106, /* 1262 Neptune B, MK board. */
	realtek_1262_neptuneB_avhdd_ewha10_mk_board	=0x1107, /* 1262 Neptune B, AVHDD Ewha 1.0 MK board. */
	realtek_1283_mars_qa_board	=0x0200, /* 1283 Mars, QA board. */
	C01_avhdd_board			=0x10001,
	C01_1262_avhdd_board		=0x11101, /* 1262 Neptune AVHDD Board. */
	C01_photoviewer_board		=0x10007,
	C02_avhdd_board			=0x20008,
	C02_1262_Neptune_avhdd_board	=0x21101,
	C03_pvr_8m_board		=0x30001,
	C03_pvr_board			=0x30009,
	C03_pvr2_board			=0x3000B,
	C04_pvr_board			=0x40009,
	C04_pvr2_board			=0x4000B,
	C05_pvrbox_board		=0x5000A,
	C05_pvrbox2_board		=0x50001,
	C06_pvr_board			=0x60009,
	C07_avhdd_board			=0x70001, //AVHDD with J-Micron SATA.
	C07_pvrbox_board		=0x7000a, //PVR-BOX with PC Install.
	C07_pvrbox2_board		=0x7000b, //PVR-BOX without PC Install.
	C08_pvr_board			=0x80009,
	C09_pvrbox_board		=0x90001,
	C09_pvrbox2_board		=0x90002,
	C0A_pvr_board			=0xa0001, //2MB NOR and 128MB+ NAND.Behavior is the same with C0003.B000b
	C0B_dvr_board			=0xb1101, //Neptune 1282 DVR Demo Board.
	C0C_avhdd_board			=0xc0001,
	C0D_pvr_board			=0xd0001,	//8 MB PVR Module.
	C0E_dvr_board			=0xe0001,	//1281 2MB DVR (little blue).
	C0F_1061_avhdd_hdd35_board	=0xf0001,	//1061 AVHDD with 3.5" HDD.
	C0F_1061_avhdd_board		=0xf0002,	//1061 AVHDD without HDD.
	C0F_1262_avhdd_hdd35_board	=0xf1101,	//1262 AVHDD with 3.5" HDD.
	C0F_1262_avhdd_hdd25_board	=0xf1102,	//1262 AVHDD with 2.5" HDD.
	C10_1071_avhdd_board		=0x100001,	//1071 AVHDD
} board_id_t;

/* The format of "bootrev" is like "00.00.26c". The first byte of it stands for company id */
typedef enum {
	company_realtek		=0x0,
	company_alpha		=0x1,
	company_C02		=0x2,
	company_C03		=0x3,
	company_C04		=0x4,
	company_C05		=0x5,
	company_C06		=0x6,
	company_C07		=0x7,
	company_C08		=0x8,
	company_C09		=0x9,
	company_C0A		=0xa,
	company_C0B		=0xb,
	company_C0C		=0xc,
	company_C0D		=0xd,
	company_C0E		=0xe,
	company_C0F		=0xf,
	company_C10		=0x10,
} company_id_t;

/* Defines of CPU ID */
typedef enum {
	realtek_venus_cpu	=0x00,
	realtek_venus2_cpu	=0x10,
	realtek_venus3_cpu	=0x20,
	realtek_neptune_cpu	=0x01,
	realtek_neptuneB_cpu	=0x11,
	realtek_mars_cpu	=0x02,
	realtek_marsB_cpu	=0x12,
	realtek_marsC_cpu	=0x22,
	realtek_marsD_cpu	=0x32,
	realtek_jupiter_cpu	=0x03,
	realtek_jupiterB_cpu    =0x13,
	realtek_jupiterC_cpu    =0x23,
	realtek_jupiterD_cpu    =0x33,
	realtek_saturn_cpu	=0x04,
	realtek_saturnB_cpu	=0x14,
	realtek_darwin_cpu	=0x05,
	realtek_macarthur_cpu	=0x06,
	realtek_nike_cpu	=0x07,
} cpu_id_t;

typedef enum {
	PAL,
	NTSC,
} tv_encoding_system_t;

typedef struct {
	board_id_t		board_id;
	company_id_t		company_id;
	cpu_id_t		cpu_id;
	char			kernel_source_code_info[64];
	char			bootloader_version[32];
	char			ethaddr[20];			/* Ethernet Mac address */
	int			ethtype;			/* Ethernet type. 0 for 100M; 1 for 1G */
	char			usb_param[20];			/* USB parameter */
	char			usb1_param[20];			/* USB parameter */
	char			usb2_param[20];			/* USB parameter */
	unsigned char		AES_CCMP[AES_CCMP_LEN];		/* maximum size 113. The last one may be '\0' */
	int			AES_CCMP_len;			/* The stored length of the binary data in AES_CCMP[] */
#if defined(CONFIG_REALTEK_PCBMGR)
	unsigned char		panel_parameter[panel_parameter_LEN];		/* maximum size 113. The last one may be '\0' */
	int			panel_parameter_len;			/* The stored length of the binary data in AES_CCMP[] */
	char           pcb_enum_parameter[pcb_enum_parameter_LEN];
	int 		   pcb_enum_parameter_len;
#endif
	int			update_mode;
	char			system_parameters[SYSTEM_PARAMETERS_LEN];
	tv_encoding_system_t	tv_encoding_system;
	char			signature[SIGNATURE_LEN];
	unsigned char 		modelconfig[MODEL_CONFIG_LEN];
	int			modelconfig_len;
	int			secure_boot;
	char			AES_IMG_KEY[AES_IMG_KEY_LEN];
	char			RSA_KEY_MODULUS[RSA_KEY_MODULUS_LEN];
	char			_priv_[_PRIV_LEN];
	char			_custom_param_[_CUSTOM_PARAM_LEN];
	unsigned		short rtc_base_date_year;	/* The base year of RTC passed from bootloader. The default is 2005 */
} platform_info_t;

extern platform_info_t platform_info;

static inline int is_venus_cpu(void) {
/*
	int cpu_id = platform_info.cpu_id;

	#ifdef CONFIG_REALTEK_FORCE_CPUID_AS_CHIP
		#ifdef CONFIG_REALTEK_VENUS
		       return 1;
		#else
			return 0;
		#endif
	#endif

	if((cpu_id&0xf) == realtek_venus_cpu)
		return 1;
	else
*/		return 0;

}

static inline int is_neptune_cpu(void) {
/*	int cpu_id = platform_info.cpu_id;


	#ifdef CONFIG_REALTEK_FORCE_CPUID_AS_CHIP
		#ifdef CONFIG_REALTEK_NEPTUNE
		       return 1;
		#else
			return 0;
		#endif
	#endif

	if((cpu_id&0xf) == realtek_neptune_cpu)
		return 1;
	else
*/		return 0;
}

static inline int is_mars_cpu(void) {
/*	int cpu_id = platform_info.cpu_id;

	#ifdef CONFIG_REALTEK_FORCE_CPUID_AS_CHIP
		#ifdef CONFIG_REALTEK_MARS
		       return 1;
		#else
			return 0;
		#endif
	#endif

	if((cpu_id&0xf) == realtek_mars_cpu)
		return 1;
	else
*/		return 0;
}

static inline int is_jupiter_cpu(void) {
/*	int cpu_id = platform_info.cpu_id;

	#ifdef CONFIG_REALTEK_FORCE_CPUID_AS_CHIP
		#ifdef CONFIG_REALTEK_JUPITER
		       return 1;
		#else
			return 0;
		#endif
	#endif

	if((cpu_id&0xf) == realtek_jupiter_cpu)
		return 1;
	else
*/		return 0;
}

static inline int is_saturn_cpu(void) {
/*        int cpu_id = platform_info.cpu_id;

	#ifdef CONFIG_REALTEK_FORCE_CPUID_AS_CHIP
		#ifdef CONFIG_REALTEK_SATURN
		       return 1;
		#else
			return 0;
		#endif
	#endif

        if((cpu_id&0xf) == realtek_saturn_cpu)
                return 1;
        else
*/                return 0;
}
static inline int is_nike_cpu(void) {
/*        int cpu_id = platform_info.cpu_id;

	#ifdef CONFIG_REALTEK_FORCE_CPUID_AS_CHIP
		#ifdef CONFIG_REALTEK_NIKE
		       return 1;
		#else
			return 0;
		#endif
	#endif

        if((cpu_id&0xf) == realtek_nike_cpu)
                return 1;
        else
*/                return 0;
}
static inline int is_darwin_cpu(void) {
/*        int cpu_id = platform_info.cpu_id;
	#ifdef CONFIG_REALTEK_FORCE_CPUID_AS_CHIP
		#ifdef CONFIG_REALTEK_DARWIN
		       return 1;
		#else
			return 0;
		#endif
	#endif

        if((cpu_id&0xf) == realtek_darwin_cpu)
                return 1;
        else
*/                return 0;
}

static inline int is_macarthur_cpu(void) {
/*
        int cpu_id = platform_info.cpu_id;

	#ifdef CONFIG_REALTEK_FORCE_CPUID_AS_CHIP
		#ifdef CONFIG_REALTEK_MACARTHUR
		       return 1;
		#else
			return 0;
		#endif
	#endif
        if((cpu_id&0xf) == realtek_macarthur_cpu)
                return 1;
        else
*/                return 0;

}
// Return the revision number of Venus/Neptune/Mars/Jupiter... CPUs
static inline int cpu_rev_num(void) {
/*	return (platform_info.cpu_id&0xf0)>>4;
*/                return 0;
}

#endif /* !(_MACH_PLATFORM_H) */


