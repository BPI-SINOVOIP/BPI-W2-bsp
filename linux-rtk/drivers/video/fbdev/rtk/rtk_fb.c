/*
 *  android_fb.c
 * 
 *  Copyright 2007, The Android Open Source Project
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */


/*
 * ANDROID PORTING GUIDE: FRAME BUFFER DRIVER TEMPLATE
 *
 * This template is designed to provide the minimum frame buffer
 * functionality necessary for Android to display properly on a new
 * device.  The PGUIDE_FB macros are meant as pointers indicating
 * where to implement the hardware specific code necessary for the new
 * device.  The existence of the macros is not meant to trivialize the
 * work required, just as an indication of where the work needs to be
 * done.
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/mm.h>
#include <linux/fb.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/init.h>
#include <linux/dma-mapping.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/io.h>
#include <linux/dma-contiguous.h>
#include <asm/div64.h>

#include "debug.h"
#include "rtk_fb.h"
#include "dc2vo/dc2vo.h"

#ifdef CONFIG_REALTEK_AVCPU
#include "avcpu.h"
#endif


#define USE_UMP 1
#ifdef USE_UMP
#include <linux/ump.h>
#include <linux/ump_fb.h>
#define IOCTL_GET_FB_UMP_SECURE_ID _IOWR('m', 0xF8, __u32)
static ump_dd_handle ump_wrapped_buffer = UMP_DD_INVALID_MEMORY_HANDLE;
#endif

struct fb_dmabuf_export
{
	__u32 fd;
	__u32 flags;
};
#define FBIOGET_DMABUF  _IOR('F', 0x21, struct fb_dmabuf_export)

struct fb_resize
{
	__u32 width;
	__u32 height;
	__u32 count;
	__u32 byte_per_pixel;
	__u32 reserve[16-4];
};
#define FBIOSET_RESIZE  _IOWR('F', 0x22, struct fb_resize)


#include "../../../../drivers/staging/android/ion/ion.h"
#include "../../../../drivers/staging/android/uapi/ion_rtk.h"
extern struct ion_device *rtk_phoenix_ion_device;

#define ANDROID_NUMBER_OF_FPS 60
#define ANDROID_BYTES_PER_PIXEL 4
static int debug = 0;

#define dprintk(msg...) if (debug)   { printk(KERN_ALERT	"D/RTK_FB: " msg); }
//#define dprintk(msg...) if (debug)   { dbg_info(KERN_DEBUG	"D/RTK_FB: " msg); }

#define MEMORY_ALIGN( value, base ) (((value) + ((base) - 1)) & ~((base) - 1))

#ifdef USE_UMP
static struct ump_operations ump_ops;

int ump_ops_register(struct ump_operations *cb)
{
	printk(KERN_ALERT "register ump cb\n");
	ump_ops.create_from_phys_blocks_64 = cb->create_from_phys_blocks_64;
	ump_ops.create_from_phys_blocks = cb->create_from_phys_blocks;
	ump_ops.secure_id_get = cb->secure_id_get;
	return 1;
}

//EXPORT_SYMBOL(ump_ops);
EXPORT_SYMBOL(ump_ops_register);
#endif

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

enum rtk_fb_memory_flags {
	RTK_FB_MEM_ALLOC_ALGO_LAST_FIT = 0x1 << 0,
};

__maybe_unused static int rtk_fb_set_size (struct rtk_fb *fb, int width, int height, int count, int byte_per_pixel, int flags);

__maybe_unused static int rtk_fb_memory_alloc (struct rtk_fb_memory **ppMem, int width, int height, int byte_per_pixel ,int align, int count, int flags);
__maybe_unused static void rtk_fb_memory_destroy (struct rtk_fb_memory **ppMem);
__maybe_unused static unsigned long rtk_fb_memory_phy (struct rtk_fb_memory *pMem);
__maybe_unused static void *rtk_fb_memory_map (struct rtk_fb_memory *pMem);
__maybe_unused static int rtk_fb_memory_share_fd (struct rtk_fb_memory *pMem);
__maybe_unused static inline size_t rtk_fb_memory_size (struct rtk_fb_memory *pMem) { return (pMem != NULL) ? pMem->alloc_size:0;}
__maybe_unused static inline int	rtk_fb_memory_width (struct rtk_fb_memory *pMem) { return (pMem != NULL) ? pMem->width:0;}
__maybe_unused static inline int	rtk_fb_memory_height (struct rtk_fb_memory *pMem) { return (pMem != NULL) ? pMem->height:0;}
__maybe_unused static inline int	rtk_fb_memory_align (struct rtk_fb_memory *pMem) { return (pMem != NULL) ? pMem->align:0;}
__maybe_unused static inline int	rtk_fb_memory_count (struct rtk_fb_memory *pMem) { return (pMem != NULL) ? pMem->count:0;}
__maybe_unused static inline int	rtk_fb_memory_bypePrePixel  (struct rtk_fb_memory *pMem) { return (pMem != NULL) ? pMem->byte_per_pixel:ANDROID_BYTES_PER_PIXEL;}

static int fb_avcpu_event_notify(struct notifier_block *self, unsigned long action, void *data)
{
	struct fb_info *info = (struct fb_info *)registered_fb[0];
	struct rtk_fb *fb = container_of(info, struct rtk_fb, fb);
	return DC_avcpu_event_notify(action, &fb->video_info);
}

__maybe_unused static struct notifier_block fb_avcpu_event_notifier = {
	.notifier_call = fb_avcpu_event_notify,
};

static inline u32 convert_bitfield(int val, struct fb_bitfield *bf)
{
	unsigned int mask = (1 << bf->length) - 1;

	return (val >> (16 - bf->length) & mask) << bf->offset;
}

/* set the software color map.  Probably doesn't need modifying. */
static int rtk_fb_setcolreg(unsigned int regno, unsigned int red, unsigned int green,
	unsigned int blue, unsigned int transp, struct fb_info *info)
{
	struct rtk_fb *fb = container_of(info, struct rtk_fb, fb);

	if (regno < 16) {
		fb->cmap[regno] = convert_bitfield(transp, &fb->fb.var.transp) |
			convert_bitfield(blue, &fb->fb.var.blue) |
			convert_bitfield(green, &fb->fb.var.green) |
			convert_bitfield(red, &fb->fb.var.red);
		return 0;
	} else {
		return 1;
	}
}

/* check var to see if supported by this device.  Probably doesn't
 * need modifying.
 */
static int rtk_fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct rtk_fb *fb = container_of(info, struct rtk_fb, fb);

	dprintk("[%s %d]\n", __func__, __LINE__);
#if 0
	if ((var->rotate & 1) != (info->var.rotate & 1)) {
		if ((var->xres != info->var.yres) ||
			(var->yres != info->var.xres) ||
			(var->xres_virtual != info->var.yres) ||
			(var->yres_virtual > info->var.xres * ANDROID_NUMBER_OF_BUFFERS) ||
			(var->yres_virtual < info->var.xres )) {
			return -EINVAL;
		}
	} else {
		if ((var->xres != info->var.xres) ||
			(var->yres != info->var.yres) ||
			(var->xres_virtual != info->var.xres) ||
			(var->yres_virtual > info->var.yres * ANDROID_NUMBER_OF_BUFFERS) ||
			(var->yres_virtual < info->var.yres )) {
			return -EINVAL;
		}
	}
	if ((var->xoffset != info->var.xoffset) ||
		(var->bits_per_pixel != info->var.bits_per_pixel) ||
		(var->grayscale != info->var.grayscale)) {
		return -EINVAL;
	}
#endif

	if (info->var.xres_virtual > rtk_fb_memory_width(fb->pMem))
		info->var.xres_virtual = rtk_fb_memory_width(fb->pMem);
	if (info->var.yres_virtual > (rtk_fb_memory_height(fb->pMem) *rtk_fb_memory_count(fb->pMem)))
		info->var.yres_virtual = rtk_fb_memory_height(fb->pMem) *rtk_fb_memory_count(fb->pMem);

	return 0;
}

static int rtk_fb_set_par(struct fb_info *info)
{
	struct rtk_fb *fb = container_of(info, struct rtk_fb, fb);
	if (fb->rotation != fb->fb.var.rotate) {
		dbg_info("[%s %d] TODO: FB_ROTATE\n",__func__,__LINE__);

		info->fix.line_length   = info->var.xres * rtk_fb_memory_bypePrePixel(fb->pMem);
		fb->rotation = fb->fb.var.rotate;
	}

	if (info->var.xres_virtual > rtk_fb_memory_width(fb->pMem))
		info->var.xres_virtual = rtk_fb_memory_width(fb->pMem);
	if (info->var.yres_virtual > (rtk_fb_memory_height(fb->pMem) * rtk_fb_memory_count(fb->pMem)))
		info->var.yres_virtual = rtk_fb_memory_height(fb->pMem) * rtk_fb_memory_count(fb->pMem);

	return 0;
}

__maybe_unused static int rtk_fb_blank(int blank_mode, struct fb_info *info)
{
	return 0;
}

static int rtk_fb_pan_display(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct rtk_fb *fb __attribute__ ((unused)) = container_of(info, struct rtk_fb, fb);

	/* Set the frame buffer base to something like:
	 * fb->fb.fix.smem_start + fb->fb.var.xres *
	 * ANDROID_BYTES_PER_PIXEL * var->yoffset
	*/
	fb->fb.var.xoffset = var->xoffset;
	fb->fb.var.yoffset = var->yoffset;
	fb->fb.var.xres_virtual = var->xres_virtual;
	fb->fb.var.yres_virtual = var->yres_virtual;

	return DC_Swap_Buffer(info, &fb->video_info);
}

static int rtk_fb_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	struct rtk_fb *fb __attribute__ ((unused)) = container_of(info, struct rtk_fb, fb);
	unsigned long start;
	unsigned long mmio_pgoff;
	u32 len;

	start = info->fix.smem_start;
	len = info->fix.smem_len;
	mmio_pgoff  = PAGE_ALIGN((start & ~PAGE_MASK) + len) >> PAGE_SHIFT;

	if (vma->vm_pgoff >= mmio_pgoff) {
		if (info->var.accel_flags) {
			return -EINVAL;
		}

		vma->vm_pgoff -= mmio_pgoff;
		start   = info->fix.mmio_start;
		len	 = info->fix.mmio_len;
	}
	//vma->vm_page_prot = vm_get_page_prot(vma->vm_flags);
	//vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
	return vm_iomap_memory(vma, start, len);
}

#ifdef USE_UMP
static int ump_wrapper(struct fb_info *info)
{
	ump_dd_physical_block blocks;
	unsigned long block_num = 1;

	if (ump_wrapped_buffer != UMP_DD_INVALID_MEMORY_HANDLE)
		return 1;

	blocks.addr = info->fix.smem_start;
	blocks.size = info->fix.smem_len;
	ump_wrapped_buffer = ump_ops.create_from_phys_blocks(&blocks, block_num);

	if (ump_wrapped_buffer == UMP_DD_INVALID_MEMORY_HANDLE)
		return 0;
	else
		return 1;
}
#endif

static int rtk_fb_ioctl(struct fb_info *info, unsigned int cmd, unsigned long arg)
{
	struct rtk_fb *fb __attribute__ ((unused)) = container_of(info, struct rtk_fb, fb);
	int gat_cmd = 0;
	int ret = 0;

	switch (cmd) {
	case FBIOSET_RESIZE:
		{
			struct fb_resize sNewSize;

			if (copy_from_user(&sNewSize, (void *)arg, sizeof(sNewSize)) == 0) {
				rtk_fb_set_size(fb, sNewSize.width, sNewSize.height, sNewSize.count, sNewSize.byte_per_pixel, 0);
			}
			gat_cmd = 1;
			break;
		}
	case FBIOGET_DMABUF:
		{
			struct fb_dmabuf_export __user *up_dmabuf_export = (struct fb_dmabuf_export __user *) arg;
			struct fb_dmabuf_export dmabuf_export;

			dmabuf_export.flags = 0;
			dmabuf_export.fd = (__u32) rtk_fb_memory_share_fd(fb->pMem);
#if defined(CONFIG_ARCH_MULTI_V7)
			ret = copy_from_user(&dmabuf_export, arg, sizeof(dmabuf_export));
			ret = copy_to_user(arg, &dmabuf_export, sizeof(dmabuf_export));
#else
			ret = put_user(dmabuf_export, up_dmabuf_export);
#endif /* CONFIG_ARCH_MULTI_V7 */
			dprintk("[%s] FBIOGET_DMABUF return[ret:%d fd:%d]\n", __func__, ret, dmabuf_export.fd);
			gat_cmd = 1;
			break;
		}
#ifdef USE_UMP
	case IOCTL_GET_FB_UMP_SECURE_ID:
		{
			//dprintk(KERN_ALERT "%s %d IOCTL GET FB UMP\n", __FUNCTION__, __LINE__);
			u32 __user *psecureid;
			ump_secure_id secure_id;

			if (ump_wrapper(info) == 0) {
				printk(KERN_ALERT "Unable to wrap ump memory\n");
				break;
			}
			psecureid = (u32 __user *)arg;
			//secure_id = 0;//ump_dd_secure_id_get(ump_wrapped_buffer);
			secure_id = ump_ops.secure_id_get(ump_wrapped_buffer);
			dprintk(KERN_ALERT "UMP secure ID %d\n", secure_id);
			ret = put_user((u32)secure_id, psecureid);
			gat_cmd = 1;
			break;
		}
#endif
	default:
		break;
	}

	if (gat_cmd)
		return ret;

	return DC_Ioctl(info, (void *)&fb->video_info, cmd, arg);
}

static int rtk_fb_memory_alloc(struct rtk_fb_memory ** ppMem, int width,
	int height, int byte_per_pixel ,int align, int count, int flags)
{
	uint32_t allocate_size =
		MEMORY_ALIGN((width * height * byte_per_pixel * count), align);
	uint32_t ion_heap_mask =
		RTK_PHOENIX_ION_HEAP_MEDIA_MASK;
	uint32_t ion_heap_flag = ION_FLAG_SCPUACC | ION_FLAG_HWIPACC;
	struct rtk_fb_memory *pMem = NULL;

	if (*ppMem != NULL)
		goto err;

	if (flags & RTK_FB_MEM_ALLOC_ALGO_LAST_FIT)
		ion_heap_flag |= ION_USAGE_ALGO_LAST_FIT;

	*ppMem = (struct rtk_fb_memory *)kzalloc(sizeof(struct rtk_fb_memory),
		GFP_KERNEL);
	pMem = *ppMem;

	pMem->fb_client = ion_client_create(rtk_phoenix_ion_device, "android_fb");

	pMem->fb_handle = ion_alloc(pMem->fb_client, allocate_size,
		align, ion_heap_mask, ion_heap_flag);
	pMem->alloc_size = allocate_size;
	pMem->width = width;
	pMem->height = height;
	pMem->align = align;
	pMem->count = count;
	pMem->byte_per_pixel = byte_per_pixel;
	pMem->flags = flags;

	return 0;
err:
	if (pMem != NULL)
		kfree(pMem);

	*ppMem = NULL;

	return -1;
}

static void rtk_fb_memory_destroy(struct rtk_fb_memory ** ppMem)
{
	struct rtk_fb_memory *pMem;

	if (ppMem == NULL || *ppMem == NULL)
		return;

	pMem = *ppMem;
	ion_free(pMem->fb_client, pMem->fb_handle);
	ion_client_destroy(pMem->fb_client);
	kfree(pMem);
	*ppMem = NULL;
}

static unsigned long rtk_fb_memory_phy(struct rtk_fb_memory *pMem)
{
	unsigned long ret = -1UL;
	size_t len;

	if (pMem == NULL)
		goto err;

	if (ion_phys(pMem->fb_client, pMem->fb_handle, &ret, &len) != 0) {
		dbg_err("[%s %s] ion_phys error size=%ld\n", __FILE__, __func__, pMem->alloc_size);
		ret = -1UL;
	}

err:
	return ret;
}

static void *rtk_fb_memory_map(struct rtk_fb_memory *pMem)
{
	void *ret = NULL;

	if (pMem == NULL)
		goto err;

	if (pMem->virAddr == NULL)
		pMem->virAddr = ion_map_kernel(pMem->fb_client, pMem->fb_handle);

	ret = pMem->virAddr;
err:
	return ret;
}

static int rtk_fb_memory_share_fd(struct rtk_fb_memory *pMem)
{
	int ret = -1;

	if (pMem == NULL)
		goto err;

	ret = ion_share_dma_buf_fd(pMem->fb_client, pMem->fb_handle);

err:
	return ret;
}

static struct fb_ops rtk_fb_ops = {
	.owner = THIS_MODULE,
	.fb_blank = rtk_fb_blank,
	.fb_check_var = rtk_fb_check_var,
	.fb_set_par = rtk_fb_set_par,
	.fb_setcolreg = rtk_fb_setcolreg,
	.fb_pan_display = rtk_fb_pan_display,
	.fb_ioctl = rtk_fb_ioctl,
	.fb_mmap = rtk_fb_mmap,
#ifdef CONFIG_COMPAT
	.fb_compat_ioctl = rtk_fb_ioctl,
#endif
	/* These are generic software based fb functions */
#ifdef CONFIG_FB_CFB_FILLRECT
	.fb_fillrect = cfb_fillrect,
#endif
#ifdef CONFIG_FB_CFB_COPYAREA
	.fb_copyarea = cfb_copyarea,
#endif
#ifdef CONFIG_FB_CFB_IMAGEBLIT
	.fb_imageblit = cfb_imageblit,
#endif
};

static int rtk_fb_update_by_memory(struct rtk_fb *fb, struct rtk_fb_memory *pMem)
{
	int ret = -1;
	int fb_width;
	int fb_height;
	dma_addr_t fb_phys;
	size_t	  fb_size;
	int fb_cnt;
	void *fb_virAddr;
	int fb_byte_per_pixel;
	long long temp;
	long long temp2;

	if (fb == NULL || pMem == NULL)
		goto err_fb_set_var_failed;

	fb_phys = rtk_fb_memory_phy(pMem);
	fb_size = rtk_fb_memory_size(pMem);
	fb_width = rtk_fb_memory_width(pMem);
	fb_height = rtk_fb_memory_height(pMem);
	fb_virAddr = rtk_fb_memory_map(pMem);
	fb_byte_per_pixel = rtk_fb_memory_bypePrePixel(pMem);

	dbg_info("[%s %s] [%d x %d] addr:0x%lx size:0x%lx irq:%d\n",
		__FILE__, __func__, fb_width, fb_height, (unsigned long)fb_phys, fb_size, fb->irq);

	fb->fb.flags	 = FBINFO_FLAG_DEFAULT;
	fb->fb.pseudo_palette = fb->cmap;
	fb->fb.fix.type = FB_TYPE_PACKED_PIXELS;
	fb->fb.fix.visual = FB_VISUAL_TRUECOLOR;
	fb->fb.fix.line_length = fb_width *fb_byte_per_pixel;
	fb->fb.fix.accel = FB_ACCEL_NONE;
	fb->fb.fix.ypanstep = 1;

	fb_cnt = (fb_size)/(fb->fb.fix.line_length * fb_height);

	if (fb_cnt > rtk_fb_memory_count(pMem))
		fb_cnt = rtk_fb_memory_count(pMem);

	dbg_info("[%s %s] numberofbuffers %d\n",
		__FILE__, __func__, fb_cnt);

	fb->fb.var.xres = fb_width;
	fb->fb.var.yres = fb_height;
	fb->fb.var.xres_virtual = fb_width;
	fb->fb.var.yres_virtual = fb_height * fb_cnt;
	fb->fb.var.activate = FB_ACTIVATE_NOW;
	fb->fb.var.height = fb_height;
	fb->fb.var.width = fb_width;

	if (fb_byte_per_pixel == 4) {
		/* ARGB 8888 */
		fb->fb.var.bits_per_pixel = 32;
		fb->fb.var.transp.offset = 24;
		fb->fb.var.transp.length = 8;
		fb->fb.var.red.offset = 16;
		fb->fb.var.red.length = 8;
		fb->fb.var.green.offset = 8;
		fb->fb.var.green.length = 8;
		fb->fb.var.blue.offset = 0;
		fb->fb.var.blue.length = 8;
	} else {
		/* RGB 565 */
		fb->fb.var.bits_per_pixel = 16;
		fb->fb.var.red.offset = 11;
		fb->fb.var.red.length = 5;
		fb->fb.var.green.offset = 5;
		fb->fb.var.green.length = 6;
		fb->fb.var.blue.offset = 0;
		fb->fb.var.blue.length = 5;
	}

	fb->fb.var.width = 0;
	fb->fb.var.height = 0;

	switch (fb_width) {
	case 1920:
	case 720:
		fb->fb.var.vsync_len = 1;
		fb->fb.var.hsync_len = 2;
		break;
	case 1280:
		fb->fb.var.vsync_len = 11;
		fb->fb.var.hsync_len = 3;
	default:
		break;
	}

	temp = (fb->fb.var.xres+fb->fb.var.vsync_len) * (fb->fb.var.yres+fb->fb.var.hsync_len);
	temp2 = 1000000000000;
	do_div(temp2, temp);
	fb->fb.var.pixclock = temp2;
	fb->fb.var.pixclock /= fb->fps;
	fb->fb.fix.smem_len = fb_size;
	fb->fb.fix.smem_start = fb_phys;
	fb->fb.screen_base = fb_virAddr;
	if (!fb->fb.screen_base) {
		dbg_err("Could not allocate frame buffer memory");
		goto err_fb_set_var_failed;
	}
	if (fb_set_var(&fb->fb, &fb->fb.var) != 0) {
		goto err_fb_set_var_failed;
	}

	ret = 0;
err_fb_set_var_failed:
	return ret ;
}

static int rtk_fb_set_size (struct rtk_fb *fb, int width, int height,
	int count, int _byte_per_pixel, int flags)
{
	int ret = -1;
	struct rtk_fb_memory *pMem = NULL;
	int byte_per_pixel = ANDROID_BYTES_PER_PIXEL;

	/* Only support 4 byte or 2 byte */
	switch (_byte_per_pixel) {
	case 4:
	case 2:
		byte_per_pixel = _byte_per_pixel;
		break;
	default:
		break;
	}

	if (fb->pMem != NULL &&
		width	== rtk_fb_memory_width(fb->pMem) &&
		height == rtk_fb_memory_height(fb->pMem) &&
		count == rtk_fb_memory_count(fb->pMem) &&
		byte_per_pixel == rtk_fb_memory_bypePrePixel(fb->pMem))
		goto done;

	ret = rtk_fb_memory_alloc(&pMem, width, height, byte_per_pixel, PAGE_SIZE, count, flags);
	if (ret != 0) {
		dbg_err("[%s %s] rtk_fb_memory_alloc return error! ([%dx%d] bypePrePixel=%d align=%ld count=%d) \n",
			__FILE__, __func__, width, height, byte_per_pixel, PAGE_SIZE, count);
		goto err;
	}


	ret = rtk_fb_update_by_memory(fb, pMem);
	if (ret != 0) {
		dbg_err("[%s %s] rtk_fb_update_by_memory return error! ([%dx%d] bypePrePixel=%d align=%ld count=%d) \n",
			__FILE__, __func__, width, height, byte_per_pixel, PAGE_SIZE, count);
		goto err;
	}

	if (fb->pMem != NULL){
		rtk_fb_memory_destroy(&fb->pMem);
	}

	fb->pMem = pMem;

done:
	ret = 0;
err:
	return ret;
}

static int rtk_fb_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct rtk_fb *fb;
	int width;
	int height;
	int count;
	const u32 *prop;
	int size;

	dbg_warn("[%s %s] \n", __FILE__, __func__);

	fb = kzalloc(sizeof(*fb), GFP_KERNEL);
	if (fb == NULL) {
		ret = -ENOMEM;
		goto err_fb_alloc_failed;
	}

	fb->fps = ANDROID_NUMBER_OF_FPS;

	prop = of_get_property(pdev->dev.of_node, "resolution", &size);
	if ((prop) && (size >= sizeof(u32)*2)) {
		width = of_read_number(prop, 1);
		height = of_read_number(prop, 2);
	} else {
		width = 1280;
		height = 720;
		dbg_warn("[%s %s] Use default w:%d h:%d\n", __FILE__, __func__, width, height);
	}

	prop = of_get_property(pdev->dev.of_node, "buffer-cnt", &size);
	if ((prop) && (size >= sizeof(u32) * 1)) {
		count = of_read_number(prop, 1);
	} else {
		count = 3;
		dbg_warn("[%s %s] Use default count:%d\n", __FILE__, __func__, count);
	}

	fb->irq = irq_of_parse_and_map(pdev->dev.of_node, 0);

	prop = of_get_property(pdev->dev.of_node, "fps", &size);
	if ((prop) && (size >= sizeof(u32) * 1))
		fb->fps = of_read_number(prop, 1);
	else
		dbg_warn("[%s %s] Use default fps:%d\n", __FILE__, __func__, fb->fps);

	ret = rtk_fb_set_size(fb, width, height, count, ANDROID_BYTES_PER_PIXEL, RTK_FB_MEM_ALLOC_ALGO_LAST_FIT);
	if (ret != 0) {
		dbg_err("[%s %s] rtk_fb_set_size return error! ([%dx%d] bypePrePixel=%d align=%ld count=%d) \n",
			__FILE__, __func__, width, height, ANDROID_BYTES_PER_PIXEL, PAGE_SIZE, count);
		goto err_fb_set_var_failed;
	}

	dev_set_drvdata(&pdev->dev, fb);

	DC_Init(&fb->video_info, &fb->fb, fb->irq);

	fb->fb.fbops = &rtk_fb_ops;

	/* Avoid black screen */
	//memset(fb->fb.screen_base,0, fb_size);

	ret = register_framebuffer(&fb->fb);
	if(ret)
		goto err_register_framebuffer_failed;

#ifdef CONFIG_REALTEK_AVCPU
	register_avcpu_notifier(&fb_avcpu_event_notifier);
#endif

	return 0;

err_register_framebuffer_failed:

err_fb_set_var_failed:
	DC_Deinit(&fb->video_info);
	kfree(fb);

err_fb_alloc_failed:

	return ret;
}

static int rtk_fb_suspend(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtk_fb *fb = platform_get_drvdata(pdev);

	return DC_Suspend(&fb->video_info);
}

static int rtk_fb_resume(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtk_fb *fb = platform_get_drvdata(pdev);

	return DC_Resume(&fb->video_info);
}

static int rtk_fb_remove(struct platform_device *pdev)
{
	struct rtk_fb *fb = platform_get_drvdata(pdev);

#ifdef CONFIG_REALTEK_AVCPU
	unregister_avcpu_notifier(&fb_avcpu_event_notifier);
#endif
	DC_Deinit(&fb->video_info);
	unregister_framebuffer(&fb->fb);
	rtk_fb_memory_destroy(&fb->pMem);
	if (fb != NULL)
		kfree(fb);
	dev_set_drvdata(&pdev->dev, NULL);

	return 0;
}

static struct of_device_id rtk_fb_ids[] = {
	{ .compatible = "Realtek,rtk-fb" },
	{ /* Sentinel */ },
};

MODULE_DEVICE_TABLE(of, rtk_fb_ids);

static const struct dev_pm_ops rtk_fb_pm_ops = {
	.suspend = rtk_fb_suspend,
	.resume  = rtk_fb_resume,
};

static struct platform_driver rtkfb_of_driver = {
	.remove	= rtk_fb_remove,
	.driver = {
		.name = "rtk-fb",
		.owner = THIS_MODULE,
		.of_match_table = rtk_fb_ids,
#ifdef CONFIG_PM
		.pm = &rtk_fb_pm_ops,
#endif
	},
};

module_platform_driver_probe(rtkfb_of_driver, rtk_fb_probe);

MODULE_LICENSE("GPL");
