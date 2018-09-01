
#pragma once

#include <asm/arch/fw_info.h>

struct partition_entry
{
	unsigned char active;
	unsigned char head_start;
	unsigned char sector_start;
	unsigned char cylinder_start;
	unsigned char id;
	unsigned char head_end;
	unsigned char sector_end;
	unsigned char cylinder_end;
	unsigned int rel_sector_start;
	unsigned int sector_num;
};

struct mbr_table
{
	unsigned char codes[446];
	struct partition_entry part[4];
	unsigned short signature;
} __attribute__ ((__packed__));

/* EBR: Extended Boot Records */
struct ebr_table
{
	unsigned char codes[446];
	struct partition_entry entry;
	struct partition_entry next_ebr_entry;
	struct partition_entry unused_part[2];
	unsigned short signature;
} __attribute__ ((__packed__));

#define MBR_SIZE 0x200
#define MBR_SIGN 0xaa55
#define EBR_PARTITION_OFFEST 0x2000

struct gpt_table
{
	/* TODO */
};

/* Layout information */

#define MAX_FW_INFO 14
struct fw_info {
	int index;
	fw_type_code_t id;
	const char *name;
	char *path;

	u8 ro;
	u32 version;
	uint64_t load_addr;
	uint64_t start_addr;
	uint64_t start_block;
	size_t bytes_size; // mapping to padding
	size_t block_size;
	size_t length;

	bool in_fwt; // in fw table
	bool is_use;

	uchar   sha_hash[32];

	void *fw_desc_entry;
};

#define MAX_PART_INFO 13
typedef enum { /* Need match to partition order */
	PART_FW = 0,
	PART_SYSTEM = 1,
	PART_DATA,
	PART_CACHE,
	PART_EXTEND, // extend partition
	PART_VENDOR,
	PART_UBOOT,
	PART_LOGO,
	PART_BACKUP,
	PART_VERIFY,
	PART_ROOTFS,
	PART_ETC,
	PART_XEN,
} enum_part_id_t;

struct part_info {
	int index;
	enum_part_id_t id;
	part_type_code_t type;
	const char *name;
	char *path;
	char mount[32];
	char *fs_type;
	int fw_type;
	int fw_count;
	size_t length;
	int ro;

	uint64_t start_addr;
	uint64_t start_block;
	size_t bytes_size;
	size_t block_size;

	uint64_t mbr_addr;
	struct mbr_table *mbr;
	int mbr_index;
	bool is_extend;

	bool in_fwt; // in fw table
	bool is_use;

	void *part_desc_entry;
};

struct part_info *get_part_info(const char *name);
struct part_info *get_part_info_by_mount(char *mount);
struct fw_info *get_fw_info(const char *name);
struct fw_info *get_fw_info_next(struct fw_info *fw);

int storage_write(uint64_t start_addr, uint64_t data_size, void *data);
int storage_read(uint64_t start_addr, uint64_t data_size, void *data);

/* For fw table */
int build_fw_table(struct fw_info *f_infos, struct part_info* p_infos);
int read_fw_info(struct fw_info *fw_infos, struct part_info *part_infos);
int write_fw_img(struct fw_info *fw, uint64_t file_size, uint64_t offset,
		void *buffer, size_t size);

/* For part */
int build_part_table(struct part_info* p_infos);
int read_part_info(struct part_info *p_infos);
int write_partition_img(struct part_info *part, uint64_t file_size,
		uint64_t offset, void *data, size_t sz);

/* For MBR */
int build_part_table_to_mbr(struct part_info *p_infos);
int read_part_info_from_mbr(struct part_info *p_infos);
