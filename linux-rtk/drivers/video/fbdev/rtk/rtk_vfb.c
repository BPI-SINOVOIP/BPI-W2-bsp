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
#include <linux/kthread.h>
#include <linux/sched.h>
#include <asm/div64.h>

#include "debug.h"
#include "rtk_fb.h"
#include "dc2vo/dc2vo.h"

static DEFINE_MUTEX(free_logo_mutex);

#define INVERT_BITVAL_1 ~1

#ifdef CONFIG_REALTEK_AVCPU
#include "avcpu.h"
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
#define FBIOSET_GETBUFFER  _IO('F', 0x23)


#include "../../../../drivers/staging/android/ion/ion.h"
#include "../../../../drivers/staging/android/uapi/ion_rtk.h"
extern struct ion_device *rtk_phoenix_ion_device;

#define ANDROID_NUMBER_OF_FPS 60
#define VIDEO_BYTES_PER_PIXEL 2
static int debug = 0;
static uint32_t my_fb_node=0;
#define dprintk(msg...) if (debug)   { printk(KERN_ALERT	"D/RTK_VFB: " msg); }
//#define dprintk(msg...) if (debug)   { dbg_info(KERN_DEBUG	"D/RTK_FB: " msg); }

#define MEMORY_ALIGN( value, base ) (((value) + ((base) - 1)) & ~((base) - 1))
#define ICQ_RING_BUFFER_SIZE 512*1024


struct rtk_vfb_memory {
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
    uint32_t                    VideoAddr;    
    uint32_t                    VideoSize;     
};

struct rtk_vfb {
	struct fb_info fb;
	int rotation;
	u32 cmap[16];
	VENUSFB_MACH_INFO video_info;
	struct rtk_vfb_memory *pMem;
	int fps;
	int irq;
};

enum rtk_vfb_memory_flags {
	RTK_FB_MEM_ALLOC_ALGO_LAST_FIT = 0x1 << 0,
	RTK_FB_MEM_FREE_FB = 0x1 << 1,
};

static struct task_struct *free_logo_task;
uint32_t vfb_phyaddr;
EXPORT_SYMBOL(vfb_phyaddr);
struct ion_handle * vfb_handle;
EXPORT_SYMBOL(vfb_handle);

__maybe_unused static int rtk_vfb_set_size (struct rtk_vfb *fb, int width, int height, int count, int byte_per_pixel, int flags);
__maybe_unused static int rtk_vfb_get_bufinfo(struct fb_info *info,struct FBDev_PARAM_BUF_ADDR *pbufinfo);

__maybe_unused static int rtk_vfb_memory_alloc (struct rtk_vfb_memory **ppMem, int width, int height, int byte_per_pixel ,int align, int count, int flags);
__maybe_unused static void rtk_vfb_memory_destroy (struct rtk_vfb_memory **ppMem);
__maybe_unused static unsigned long rtk_vfb_memory_phy (struct rtk_vfb_memory *pMem);
__maybe_unused static void *rtk_vfb_memory_map (struct rtk_vfb_memory *pMem);
__maybe_unused static int rtk_vfb_memory_share_fd (struct rtk_vfb_memory *pMem);
__maybe_unused static inline size_t rtk_vfb_memory_size (struct rtk_vfb_memory *pMem) { return (pMem != NULL) ? pMem->alloc_size:0;}
__maybe_unused static inline int	rtk_vfb_memory_width (struct rtk_vfb_memory *pMem) { return (pMem != NULL) ? pMem->width:0;}
__maybe_unused static inline int	rtk_vfb_memory_height (struct rtk_vfb_memory *pMem) { return (pMem != NULL) ? pMem->height:0;}
__maybe_unused static inline int	rtk_vfb_memory_align (struct rtk_vfb_memory *pMem) { return (pMem != NULL) ? pMem->align:0;}
__maybe_unused static inline int	rtk_vfb_memory_count (struct rtk_vfb_memory *pMem) { return (pMem != NULL) ? pMem->count:0;}
__maybe_unused static inline int	rtk_vfb_memory_bypePrePixel  (struct rtk_vfb_memory *pMem) { return (pMem != NULL) ? pMem->byte_per_pixel:VIDEO_BYTES_PER_PIXEL;}

static int fb_avcpu_event_notify(struct notifier_block *self, unsigned long action, void *data)
{
	struct fb_info *info = (struct fb_info *)registered_fb[my_fb_node];
	struct rtk_vfb *fb = container_of(info, struct rtk_vfb, fb);
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
static int rtk_vfb_setcolreg(unsigned int regno, unsigned int red, unsigned int green,
	unsigned int blue, unsigned int transp, struct fb_info *info)
{
	struct rtk_vfb *fb = container_of(info, struct rtk_vfb, fb);

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
static int rtk_vfb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
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
	return 0;
}

static int rtk_vfb_set_par(struct fb_info *info)
{
	struct rtk_vfb *fb = container_of(info, struct rtk_vfb, fb);
	if (fb->rotation != fb->fb.var.rotate) {
		dbg_info("[%s %d] TODO: FB_ROTATE\n",__func__,__LINE__);

		info->fix.line_length   = info->var.xres * rtk_vfb_memory_bypePrePixel(fb->pMem);
		fb->rotation = fb->fb.var.rotate;
	}
	return 0;
}

__maybe_unused static int rtk_vfb_blank(int blank_mode, struct fb_info *info)
{
	return 0;
}

static int rtk_vfb_pan_display(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct rtk_vfb *fb __attribute__ ((unused)) = container_of(info, struct rtk_vfb, fb);

	/* Set the frame buffer base to something like:
	 * fb->fb.fix.smem_start + fb->fb.var.xres *
	 * VIDEO_BYTES_PER_PIXEL * var->yoffset
	*/
	fb->fb.var.xoffset = var->xoffset;
	fb->fb.var.yoffset = var->yoffset;
	fb->fb.var.xres_virtual = var->xres_virtual;
	fb->fb.var.yres_virtual = var->yres_virtual;

	return DC_Swap_Buffer(info, &fb->video_info);
}

static int rtk_vfb_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	struct rtk_vfb *fb __attribute__ ((unused)) = container_of(info, struct rtk_vfb, fb);
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
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	return vm_iomap_memory(vma, start, len);
}


static int rtk_vfb_ioctl(struct fb_info *info, unsigned int cmd, unsigned long arg)
{
	struct rtk_vfb *fb __attribute__ ((unused)) = container_of(info, struct rtk_vfb, fb);
	int gat_cmd = 0;
	int ret = 0;

	switch (cmd) {
        case FBIOSET_GETBUFFER           :
            {
                struct FBDev_PARAM_BUF_ADDR bufinfo;
                struct FBDev_PARAM_BUF_ADDR __user * up_bufinfo = (struct FBDev_PARAM_BUF_ADDR __user *) arg;
                rtk_vfb_get_bufinfo(info, &bufinfo);
                ret=copy_to_user(up_bufinfo, &bufinfo, sizeof(FBDev_PARAM_BUF_ADDR));
                gat_cmd = 1;
                break;
            }
	case FBIOSET_RESIZE:
		{
			struct fb_resize sNewSize;

			if (copy_from_user(&sNewSize, (void *)arg, sizeof(sNewSize)) == 0) {
				rtk_vfb_set_size(fb, sNewSize.width, sNewSize.height, sNewSize.count, sNewSize.byte_per_pixel, RTK_FB_MEM_FREE_FB);
			}
			gat_cmd = 1;
			break;
		}
	case FBIOGET_DMABUF:
		{
			struct fb_dmabuf_export __user *up_dmabuf_export = (struct fb_dmabuf_export __user *) arg;
			struct fb_dmabuf_export dmabuf_export;

			dmabuf_export.flags = 0;
			dmabuf_export.fd = (__u32) rtk_vfb_memory_share_fd(fb->pMem);
#if defined(CONFIG_CPU_V7)
			ret = copy_to_user(arg, &dmabuf_export, sizeof(dmabuf_export));
#else
			ret = put_user(dmabuf_export, up_dmabuf_export);
#endif /* CONFIG_CPU_V7 */
			dprintk("[%s] FBIOGET_DMABUF return[ret:%d fd:%d]\n", __func__, ret, dmabuf_export.fd);
			gat_cmd = 1;
			break;
		}
	default:
		break;
	}

	if (gat_cmd)
		return ret;

    {
        bool skip_lock = false;
        if (mutex_is_locked(&info->lock))
            skip_lock = true;

        if (skip_lock)
            unlock_fb_info(info);

        ret = DC_Ioctl(info, (void *)&fb->video_info, cmd, arg);
        if (skip_lock)
            lock_fb_info(info);
    }
    return ret;
}

static int rtk_vfb_memory_alloc(struct rtk_vfb_memory ** ppMem, int width,
	int height, int byte_per_pixel ,int align, int count, int flags)
{
	uint32_t video_size =
		MEMORY_ALIGN((width * height * byte_per_pixel * count), align);
	uint32_t ion_heap_mask =
		RTK_PHOENIX_ION_HEAP_MEDIA_MASK;
	uint32_t ion_heap_flag = ION_FLAG_NONCACHED | ION_FLAG_SCPUACC | ION_FLAG_HWIPACC;
	struct rtk_vfb_memory *pMem = NULL;

	if (*ppMem != NULL)
		goto err;

	if (flags & RTK_FB_MEM_ALLOC_ALGO_LAST_FIT)
		ion_heap_flag |= ION_USAGE_ALGO_LAST_FIT;

	*ppMem = (struct rtk_vfb_memory *)kzalloc(sizeof(struct rtk_vfb_memory),
		GFP_KERNEL);
	pMem = *ppMem;

    pMem->alloc_size        = MEMORY_ALIGN(video_size+PAGE_SIZE/*for misc buffer*/,align);
	pMem->fb_client = ion_client_create(rtk_phoenix_ion_device, "video_fb");

	pMem->fb_handle = ion_alloc(pMem->fb_client, pMem->alloc_size,
		align, ion_heap_mask, ion_heap_flag);
	pMem->width = width;
	pMem->height = height;
	pMem->align = align;
	pMem->count = count;
	pMem->byte_per_pixel = byte_per_pixel;
	pMem->flags = flags;
    pMem->VideoAddr         = (uint32_t)rtk_vfb_memory_phy(pMem);
    pMem->VideoSize         = video_size;    

    vfb_phyaddr = pMem->VideoAddr;
    vfb_handle = pMem->fb_handle;
    dprintk("[%s] PAGE_SIZE:%d,PAGE_SHIFT:%d,video_size:%d,width:%d,height:%d,byte_per_pixel:%d,count:%d\n", __func__, PAGE_SIZE,PAGE_SHIFT,video_size,width,height,byte_per_pixel,count);

	return 0;
err:
	if (pMem != NULL)
		kfree(pMem);

	*ppMem = NULL;

	return -1;
}

static void rtk_vfb_memory_destroy(struct rtk_vfb_memory ** ppMem)
{
	struct rtk_vfb_memory *pMem;

	if (ppMem == NULL || *ppMem == NULL)
		return;

	pMem = *ppMem;
	ion_free(pMem->fb_client, pMem->fb_handle);
	ion_client_destroy(pMem->fb_client);
	kfree(pMem);
	*ppMem = NULL;
}

static unsigned long rtk_vfb_memory_phy(struct rtk_vfb_memory *pMem)
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

static void *rtk_vfb_memory_map(struct rtk_vfb_memory *pMem)
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

static int rtk_vfb_memory_share_fd(struct rtk_vfb_memory *pMem)
{
	int ret = -1;

	if (pMem == NULL)
		goto err;

	ret = ion_share_dma_buf_fd(pMem->fb_client, pMem->fb_handle);

err:
	return ret;
}

static struct fb_ops rtk_vfb_ops = {
	.owner = THIS_MODULE,
	.fb_blank = rtk_vfb_blank,
	.fb_check_var = rtk_vfb_check_var,
	.fb_set_par = rtk_vfb_set_par,
	.fb_setcolreg = rtk_vfb_setcolreg,
	.fb_pan_display = rtk_vfb_pan_display,
	.fb_ioctl = rtk_vfb_ioctl,
	.fb_mmap = rtk_vfb_mmap,
#ifdef CONFIG_COMPAT
	.fb_compat_ioctl = rtk_vfb_ioctl,
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

static int rtk_vfb_update_by_memory(struct rtk_vfb *fb, struct rtk_vfb_memory *pMem)
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

	fb_phys = rtk_vfb_memory_phy(pMem);
	fb_size = rtk_vfb_memory_size(pMem);
	fb_width = rtk_vfb_memory_width(pMem);
	fb_height = rtk_vfb_memory_height(pMem);
	fb_virAddr = rtk_vfb_memory_map(pMem);
	fb_byte_per_pixel = rtk_vfb_memory_bypePrePixel(pMem);

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

	if (fb_cnt > rtk_vfb_memory_count(pMem))
		fb_cnt = rtk_vfb_memory_count(pMem);

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

static void free_logo_rsv_mem(void *data) {
	mutex_lock(&free_logo_mutex);
	free_reserved_area(phys_to_virt(0x30000000),
					   phys_to_virt(0x30900000),
					   0,
					   "logo area"
					   );
	mutex_unlock(&free_logo_mutex);
}

static int free_logo_threadfn(void *data) {
	struct sched_param param = {
		.sched_priority = MAX_RT_PRIO - 2,
	};
	int timeout = 5;

	sched_setscheduler(current, SCHED_FIFO, &param);
	while (1) {
		if (kthread_should_stop() || timeout == 0)
			break;
		msleep(1000);
		timeout--;
	}
	free_logo_rsv_mem(data);
	return 0;
}

static void rtk_vfb_free_logo_rsv_mem_init (void)
{
	/* create a thread to sleep N sec, then free logo reserved mem. area */
	/* disabled by default */
	#if 0
	free_logo_task = kthread_create(free_logo_threadfn, NULL, "free_logo_area" );
	if (IS_ERR(free_logo_task)) {
		printk(KERN_ERR "\033[1;33m" "Failed to create free logo kthread task" "\033[m\n");
		return 0;
	}
	kthread_bind(free_logo_task, 0);
	wake_up_process(free_logo_task);
	#endif
	free_logo_rsv_mem(NULL);
}
EXPORT_SYMBOL(rtk_vfb_free_logo_rsv_mem_init);

static ssize_t freelogo_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count) {
	unsigned long state;
	int ret;
	ret = kstrtol(buf, 0, &state);
	/* valid input value: 0 or 1 */
	if (ret != 0 || state & INVERT_BITVAL_1)
		return -EINVAL;

	if (state == 1)
		free_logo_rsv_mem(NULL);
	
	return count;
}

static DEVICE_ATTR(freelogo, S_IWUSR, NULL, freelogo_store);
  
static int rtk_vfb_get_bufinfo (struct fb_info *info,struct FBDev_PARAM_BUF_ADDR *pbufinfo)
{
    struct rtk_vfb *fb = container_of(info, struct rtk_vfb, fb);

    pbufinfo->video_buf_Paddr=fb->pMem->VideoAddr;
    pbufinfo->video_buf_count=fb->pMem->count;
    pbufinfo->video_buf_size=fb->pMem->VideoSize;
    pbufinfo->width=fb->pMem->width;
    pbufinfo->height=fb->pMem->height;
    pbufinfo->misc_buf_Paddr=pbufinfo->video_buf_Paddr + pbufinfo->video_buf_size;
    pbufinfo->misc_buf_size=PAGE_SIZE;
    return 0;
}


static int rtk_vfb_set_size (struct rtk_vfb *fb, int width, int height,
	int count, int _byte_per_pixel, int flags)
{
	int ret = -1;
	struct rtk_vfb_memory *pMem = NULL;
	int byte_per_pixel = VIDEO_BYTES_PER_PIXEL;

    if (flags == RTK_FB_MEM_FREE_FB) {
        if (fb->pMem != NULL) {
            rtk_vfb_memory_destroy(&fb->pMem);
        }
        fb->pMem = NULL;
        goto done;
    }

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
		width	== rtk_vfb_memory_width(fb->pMem) &&
		height == rtk_vfb_memory_height(fb->pMem) &&
		count == rtk_vfb_memory_count(fb->pMem) &&
		byte_per_pixel == rtk_vfb_memory_bypePrePixel(fb->pMem))
		goto done;

	ret = rtk_vfb_memory_alloc(&pMem, MEMORY_ALIGN(width,16), MEMORY_ALIGN(height,16), byte_per_pixel, PAGE_SIZE, count, flags);
	if (ret != 0) {
		dbg_err("[%s %s] rtk_vfb_memory_alloc return error! ([%dx%d] bypePrePixel=%d align=%ld count=%d) \n",
			__FILE__, __func__, width, height, byte_per_pixel, PAGE_SIZE, count);
		goto err;
	}


	ret = rtk_vfb_update_by_memory(fb, pMem);
	if (ret != 0) {
		dbg_err("[%s %s] rtk_vfb_update_by_memory return error! ([%dx%d] bypePrePixel=%d align=%ld count=%d) \n",
			__FILE__, __func__, width, height, byte_per_pixel, PAGE_SIZE, count);
		goto err;
	}

	if (fb->pMem != NULL){
		rtk_vfb_memory_destroy(&fb->pMem);
	}

	fb->pMem = pMem;

done:
	ret = 0;
err:
	return ret;
}

static int rtk_vfb_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct rtk_vfb *fb;
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

	ret = rtk_vfb_set_size(fb, width, height, count,  VIDEO_BYTES_PER_PIXEL, RTK_FB_MEM_ALLOC_ALGO_LAST_FIT);
	if (ret != 0) {
		dbg_err("[%s %s] rtk_vfb_set_size return error! ([%dx%d] bypePrePixel=%d align=%ld count=%d) \n",
			__FILE__, __func__, width, height,  VIDEO_BYTES_PER_PIXEL, PAGE_SIZE, count);
		goto err_fb_set_var_failed;
	}

	dev_set_drvdata(&pdev->dev, fb);

	DC_Init(&fb->video_info, &fb->fb, fb->irq);

	fb->fb.fbops = &rtk_vfb_ops;

	/* Avoid black screen */
	//memset(fb->fb.screen_base,0, fb_size);

	ret = register_framebuffer(&fb->fb);
	if(ret)
		goto err_register_framebuffer_failed;

	my_fb_node=fb->fb.node;

#ifdef CONFIG_REALTEK_AVCPU
	register_avcpu_notifier(&fb_avcpu_event_notifier);
#endif

	ret = device_create_file(&pdev->dev, &dev_attr_freelogo);
	if (ret < 0)
		goto err_create_devfile_failed;

	return 0;

err_create_devfile_failed:
	unregister_framebuffer(&fb->fb);
err_register_framebuffer_failed:
err_fb_set_var_failed:
	DC_Deinit(&fb->video_info);
	kfree(fb);

err_fb_alloc_failed:

	return ret;
}

static int rtk_vfb_suspend(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtk_vfb *fb = platform_get_drvdata(pdev);

	return DC_Suspend(&fb->video_info);
}

static int rtk_vfb_resume(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtk_vfb *fb = platform_get_drvdata(pdev);

	return DC_Resume(&fb->video_info);
}

static int rtk_vfb_remove(struct platform_device *pdev)
{
	struct rtk_vfb *fb = platform_get_drvdata(pdev);

	device_remove_file(&pdev->dev, &dev_attr_freelogo);
#ifdef CONFIG_REALTEK_AVCPU
	unregister_avcpu_notifier(&fb_avcpu_event_notifier);
#endif
	DC_Deinit(&fb->video_info);
	unregister_framebuffer(&fb->fb);
    if (fb->pMem != NULL)
        rtk_vfb_memory_destroy(&fb->pMem);
	if (fb != NULL)
		kfree(fb);
	dev_set_drvdata(&pdev->dev, NULL);

	return 0;
}

static struct of_device_id rtk_vfb_ids[] = {
	{ .compatible = "Realtek,rtk-vfb" },
	{ /* Sentinel */ },
};

MODULE_DEVICE_TABLE(of, rtk_vfb_ids);

static const struct dev_pm_ops rtk_vfb_pm_ops = {
	.suspend = rtk_vfb_suspend,
	.resume  = rtk_vfb_resume,
};

static struct platform_driver rtkvfb_of_driver = {
	.probe  = rtk_vfb_probe,
	.remove	= rtk_vfb_remove,
	.driver = {
		.name = "rtk-vfb",
		.owner = THIS_MODULE,
		.of_match_table = rtk_vfb_ids,
#ifdef CONFIG_PM
		.pm = &rtk_vfb_pm_ops,
#endif
	},
};

//module_platform_driver_probe(rtkvfb_of_driver, rtk_vfb_probe);

static int rtk_vfb_init(void)
{
	return platform_driver_register(&rtkvfb_of_driver);
}
late_initcall(rtk_vfb_init);

MODULE_LICENSE("GPL");
