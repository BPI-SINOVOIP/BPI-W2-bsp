#ifndef __RTK_FB_DRIVER_H__
#define __RTK_FB_DRIVER_H__

#include <linux/fb.h>

typedef struct venusfb_mach_info {
	void *dc_info;
} VENUSFB_MACH_INFO;

struct rtk_fb_memory {
	struct ion_client *fb_client;
	struct ion_handle *fb_handle;
	size_t alloc_size;
	int width;
	int height;
	int align;
	int count;
	void *virAddr;
	int byte_per_pixel;
	int flags;
};

struct rtk_fb {
	struct fb_info fb;
	int rotation;
	u32 cmap[16];
	VENUSFB_MACH_INFO video_info;
	struct rtk_fb_memory *pMem;
	int fps;
	int irq;
};

#if 1//def __LINUX_MEDIA_NAS__
typedef struct FBDev_PARAM_BUF_ADDR
{
    unsigned int video_buf_Paddr;
    unsigned int video_buf_count;
    unsigned int video_buf_size;
    unsigned int width;
    unsigned int height;
    unsigned int misc_buf_Paddr;
    unsigned int misc_buf_size;
} FBDev_PARAM_BUF_ADDR;
#endif

#endif
