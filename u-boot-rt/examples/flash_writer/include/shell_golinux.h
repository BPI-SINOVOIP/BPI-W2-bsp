#ifndef SHELL_GOLINUX_H
#define SHELL_GOLINUX_H
//#include <common.h>
//#include <exports.h>
//#include <linux/types.h>


#define UNZIP_ADDRESS       0xa0100000 - UBOOT_DDR_OFFSET
#define COPY_MERGE_ADDRESS  0xa1000000 - UBOOT_DDR_OFFSET

typedef struct {
	unsigned char	signature[8];
	unsigned int	checksum;
	unsigned char	version;
	unsigned char	reserved[15];
	unsigned int	length;
} __attribute__((packed)) fw_desc_table_t;


extern int Lzma_main(char *inAddr, char *outAddr, long length, char *rs, unsigned int *extract_len);


//char *shell_golinux();



#endif
