/*
 * Realtek Audio & Video cpu driver
 *
 * Copyright (c) 2011 EJ Hsu <ejhsu@realtek.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License.
 *
 * History:
 *
 * 2011-12-02:  EJ Hsu: first version
 * 2013-05-02:  EJ Hsu: port to arm platform
 */

#ifndef _LINUX_AVCPU_H
#define _LINUX_AVCPU_H

#include <generated/autoconf.h>
#include <linux/module.h>
#include <linux/kernel.h>

#define AUDIO_CPU               1
#define VIDEO_CPU_1             2
#define VIDEO_CPU_2             3

#define AUDIO_ENTRY_ADDR        (PAGE_OFFSET+0xe0)
#define VIDEO_ENTRY_ADDR_1      (PAGE_OFFSET+0xe4)
#define VIDEO_ENTRY_ADDR_2      (PAGE_OFFSET+0xdc)

#define AVCPU_MAJOR             241

#define AVCPU_SUSPEND           100
#define AVCPU_RESUME            101
#define AVCPU_RESET_PREPARE     102
#define AVCPU_RESET_DONE        103

#define AVSTAT_NORMAL   0
#define AVSTAT_SUSPEND  1
#define AVSTAT_RESUME   2
#define AVSTAT_RESETAV  3


#ifdef CONFIG_RTK_ACPU_RELOAD

#define FW_DESC_TABLE_V1_T_VERSION_1            0x1
#define FW_DESC_TABLE_V1_T_VERSION_11           0x11
#define FW_DESC_TABLE_V1_T_VERSION_21           0x21

#define FW_DESC_TABLE_V2_T_VERSION_2            0x2
#define FW_DESC_TABLE_V2_T_VERSION_12           0x12
#define FW_DESC_TABLE_V2_T_VERSION_22           0x22

#define FW_DESC_BASE_VERSION(v)                 ((v) & 0xf)
#define FW_DESC_EXT_VERSION(v)                  ((v) >> 4)

int register_avcpu_notifier(struct notifier_block *nb);
int unregister_avcpu_notifier(struct notifier_block *nb);

int resetav_lock(int is_suspend);
int resetav_unlock(int is_suspend);

int load_av_image(char *, unsigned int, char *, unsigned int, char *, unsigned int);

typedef enum {
    FW_TYPE_RESERVED = 0,
    FW_TYPE_BOOTCODE,
    FW_TYPE_KERNEL,
    FW_TYPE_RESCUE_DT,
    FW_TYPE_KERNEL_DT,
    FW_TYPE_RESCUE_ROOTFS,
    FW_TYPE_KERNEL_ROOTFS,
    FW_TYPE_AUDIO,
    FW_TYPE_AUDIO_FILE,
    FW_TYPE_VIDEO_FILE,
    FW_TYPE_EXT4,
    FW_TYPE_UBIFS,
    FW_TYPE_SQUASH,
    FW_TYPE_EXT3,
    FW_TYPE_ODD,
    FW_TYPE_YAFFS2,
    FW_TYPE_ISO,
    FW_TYPE_SWAP,
    FW_TYPE_NTFS,
    FW_TYPE_JFFS2,
    FW_TYPE_IMAGE_FILE,
    FW_TYPE_VIDEO,
    FW_TYPE_VIDEO2,
    FW_TYPE_ECPU,
    FW_TYPE_UNKNOWN
} fw_type_code_t;

typedef enum {
    RTK_PLAT_ERR_OK = 0,
    RTK_PLAT_ERR_PARSE_FW_DESC,
    RTK_PLAT_ERR_READ_FW_IMG,
    RTK_PLAT_ERR_READ_KERNEL_IMG,
    RTK_PLAT_ERR_READ_RESCUE_IMG,
    RTK_PLAT_ERR_BOOT,
} rtk_plat_err_t;

typedef enum {
    FS_TYPE_JFFS2 = 0,
    FS_TYPE_YAFFS2,
    FS_TYPE_SQUASH,
    FS_TYPE_RAWFILE,
    FS_TYPE_EXT4,
    FS_TYPE_UBIFS,
    FS_TYPE_NONE,
    FS_TYPE_UNKOWN
} rtk_part_fw_type_t;

typedef struct {
    char            *audio_image;
    unsigned int        audio_start;
    char            *video_image_1;
    unsigned int        video_start_1;
    char            *video_image_2;
    unsigned int        video_start_2;
} resetav_struct;

typedef struct {
    unsigned int    timeout; //in ms
    int             status;
} status_struct;

typedef struct {
    wait_queue_head_t   status_wq;
    int                 status;
} avcpu_info;

typedef struct {
    u8          signature[8];
    u32         checksum;
    u8          version;    //0x00
    u8          reserved[15];
    u32         length;
} __attribute__((packed)) fw_desc_table_t;

typedef struct {
    u8          signature[8];
    u32         checksum;
    u8          version;    //0x01
    u8          reserved[7];
    u32         paddings;
    u32         part_list_len;
    u32         fw_list_len;
} __attribute__((packed)) fw_desc_table_v1_t;

typedef struct {
    u8          type;
    u8          reserved:7,
                ro:1;
    u64         length;
    u8          fw_count;
    u8          fw_type;
    //#ifdef CONFIG_SYS_RTK_EMMC_FLASH
#if 1
    u8   emmc_partIdx;
    u8   reserved_1[3];
#else
    u8   reserved_1[4];
#endif
    u8          mount_point[32];
} __attribute__((packed)) part_desc_entry_v1_t;

typedef struct {
    u8          type;
    u8          reserved:6,
                lzma:1,
                ro:1;
    u32         version;
    u32         target_addr;
    u32         offset;
    u32         length;
    u32         paddings;
    u32         checksum;
    u8          reserved_1[6];
} __attribute__((packed)) fw_desc_entry_v1_t;

typedef struct {
    fw_desc_entry_v1_t  v1;
    u32         act_size;
    u8          hash[32];
    u8          part_num;
    u8          reserved[27];
} __attribute__((packed)) fw_desc_entry_v11_t;

typedef struct {
    fw_desc_entry_v1_t v1;
    u32         act_size;
    u8          part_num;
    u8          RSA_sign[256];
    u8          reserved[27];
} __attribute__((packed)) fw_desc_entry_v21_t;

// Version 2, offset->u64 / checksum->sha256
typedef struct {
	u8   type;
#ifdef LITTLE_ENDIAN
	u8   reserved:6,
		lzma:1,
		ro:1;
#else
	u8   ro:1,
		lzma:1,
		reserved:6;
#endif
	u32    version;
	u32    target_addr;
	u64     offset;
	u32    length;
	u32    paddings;
	u8   sha_hash[32];;
	u8   reserved_1[6];
} __attribute__((packed)) fw_desc_entry_v2_t;

// for fw_desc_table_v1_t.version = FW_DESC_TABLE_V1_T_VERSION_11
typedef struct {
	fw_desc_entry_v2_t v2;
	u32    act_size;
	u8   hash[32];
	u8   part_num;
	u8   reserved[27];
} __attribute__((packed)) fw_desc_entry_v12_t;

// for fw_desc_table_v1_t.version = FW_DESC_TABLE_V1_T_VERSION_21
typedef struct {
	fw_desc_entry_v2_t v2;
	u32    act_size;
	u8   part_num;
	u8   RSA_sign[256];
	u8   reserved[27];
} __attribute__((packed)) fw_desc_entry_v22_t;

#define FW_ENTRY_MEMBER_SET(val, fw_entry, member, version) \
{ \
	fw_desc_entry_v1_t* entry_v1 = (fw_desc_entry_v1_t*)fw_entry; \
	fw_desc_entry_v2_t* entry_v2 = (fw_desc_entry_v2_t*)fw_entry; \
	if (FW_DESC_BASE_VERSION(version) == FW_DESC_TABLE_V1_T_VERSION_1) \
		entry_v1->member = val; \
	else if (FW_DESC_BASE_VERSION(version) == FW_DESC_TABLE_V2_T_VERSION_2) \
		entry_v2->member = val; \
} \

#define FW_ENTRY_MEMBER_GET(data, fw_entry, member, version) \
{ \
        fw_desc_entry_v1_t* entry_v1 = (fw_desc_entry_v1_t*)fw_entry; \
        fw_desc_entry_v2_t* entry_v2 = (fw_desc_entry_v2_t*)fw_entry; \
        if (FW_DESC_BASE_VERSION(version) == FW_DESC_TABLE_V1_T_VERSION_1) \
		data = entry_v1->member; \
        else if (FW_DESC_BASE_VERSION(version) == FW_DESC_TABLE_V2_T_VERSION_2) \
		data = entry_v2->member; \
} \

/*
 * Ioctl definitions
 */

/* Use 'c' as magic number */
#define AVCPU_IOC_MAGIC  'c'

/*
 * S means "Set"                : through a ptr,
 * T means "Tell"               : directly with the argument value
 * G means "Get"                : reply by setting through a pointer
 * Q means "Query"              : response is on the return value
 * X means "eXchange"           : G and S atomically
 * H means "sHift"              : T and Q atomically
 */
#define AVCPU_IOCTRESET     _IOW(AVCPU_IOC_MAGIC, 1, resetav_struct)
#define AVCPU_IOCTSTOP      _IO(AVCPU_IOC_MAGIC, 2)
#define AVCPU_IOCTSTART     _IO(AVCPU_IOC_MAGIC, 3)
#define AVCPU_IOCGSTATUS    _IOR(AVCPU_IOC_MAGIC, 4, status_struct)
#define AVCPU_IOCGALIVE     _IO(AVCPU_IOC_MAGIC, 5)

#endif /* CONFIG_RTK_ACPU_RELOAD */

#endif

