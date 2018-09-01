#ifndef __LOGO_H__
#define __LOGO_H__

#include "vo_reg.h"


typedef enum {
	LOGO_NTSC	= 0,
	LOGO_PAL	= 1,
	LOGO_1080	= 2,
} logo_type_t;


/*
mode : NTSC = 0, PAL = 1
offset : the size of top field (bytes)
color : 
0: background pixel
1: Pattern pixel
2: Emphasis pixel-1
3: Emphasis pixel-2
*/
typedef struct {
	logo_type_t mode;
	unsigned long offset;
	unsigned long spclut_reg[4];
	unsigned int spclut[4];
} param_info_t;

/* An object of type, logo_info_t, is used to describe a bitmap file. */
typedef struct {
	logo_type_t logo_type;
	//int width;
	//int height;
	param_info_t param_info;
	//flash_info_t *flash_info;
	//char *dev_mount_dir;
	//char *logo_dir;
	char *logo_bmp_file;
	char *logo_bin_file;
	char *logo_param_file;
} logo_info_t;

//extern int logo_changer_installer(void);
#endif /* __LOGO_H__ */
