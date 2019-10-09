#include <generated/autoconf.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/pci.h>
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <linux/pagemap.h>
#include <linux/radix-tree.h>
#include <linux/blkdev.h>
#include <linux/module.h>
#include <linux/blkpg.h>
#include <linux/buffer_head.h>
#include <linux/mpage.h>
#include <linux/ioctl.h> /* needed for the _IOW etc stuff used later */
#include <linux/sched.h>
#include <linux/dcache.h>
#include <linux/kthread.h>
#include <linux/ktime.h>
#include <linux/file.h>
#include <linux/console.h>
#include <linux/platform_device.h>
#include <linux/fence.h>
#include <linux/sync_file.h>
#include <linux/dma-buf.h>
#include <uapi/linux/sync_file.h>


#include "../../../../../drivers/staging/android/ion/ion.h"
#include "../../../../../drivers/dma-buf/sync_debug.h"
#include "../../../../../drivers/soc/realtek/common/rpc/rtk_rpc.h"
#include <soc/realtek/rtk_ipc_shm.h>

#ifdef CONFIG_REALTEK_RPC
#include <linux/RPCDriver.h>
#endif
#ifdef CONFIG_REALTEK_AVCPU
#include "../avcpu.h"
#endif

#define RTKFB_SET_VSYNC_INT _IOW('F', 206, unsigned int)

#include "../rtk_fb.h"
#include "dc2vo.h"

static int debug = 0;
static int warning = 1;
static int info = 1;

#define dprintk(msg...) \
	if (debug) { \
		pr_debug("D/DC: " msg); \
	}
#define eprintk(msg...) \
	if (1) { \
		pr_err("E/DC: " msg); \
	}
#define wprintk(msg...) \
	if (warning) { \
		pr_warn("W/DC: " msg); \
	}
#define iprintk(msg...) \
	if (info) { \
		pr_info("I/DC: " msg); \
	}

#ifndef DC_UNREFERENCED_PARAMETER
#define DC_UNREFERENCED_PARAMETER(param) (param) = (param)
#endif

#ifdef CONFIG_RTK_RPC
extern void dc2vo_send_interrupt(void);
#endif

#ifdef DC2VO_SUPPORT_MEMORY_TRASH
#define AFBC_MODE_MASK 0x0000ffff
#define AFBC_MODE_EXT_MASK 0xffff0000
__maybe_unused static enum _AFBC_MODE_EXT {
	VO_AFBC_DEBUG_MASK = 0x1u<<16, //1:afbc debug enable
} AFBC_MODE_EXT;
static bool gbMemoryTrash = false;
#endif /* End of DC2VO_SUPPORT_MEMORY_TRASH */

//#define CREATE_THREAD_FOR_RELEASE_DEBUG
//#define DC2VO_SUPPORT_DCSYS_DEBUG

#ifdef DC2VO_SUPPORT_DCSYS_DEBUG
#define DC2VO_DCSYS_CONTROL 0x98008300
#define DC2VO_DCSYS_CONTROL_SETUP 0x03000000
#define DC2VO_DCSYS_CONTROL_ERROR ((0x1U << 22) | (0x1U << 23))
static void __iomem * gpDcSysControl = NULL;
static bool gbDcSysError = false;
static struct task_struct *gsDcSysDebugThread = NULL;
static struct kthread_work gsDcSysDebugWork;
static struct kthread_worker	gsDcSysDebugWorker;
static inline void dc_sys_debug_trigger(void);
#endif /* End of DC2VO_SUPPORT_DCSYS_DEBUG */

static int DCINIT = 0;
extern struct ion_device *rtk_phoenix_ion_device;

typedef struct {
	struct fb_info *pfbi;

	REFCLOCK *REF_CLK;
	RINGBUFFER_HEADER *RING_HEADER;
	void *RING_HEADER_BASE;
	struct ion_client *gpsIONClient;
	unsigned int gAlpha; /* [0]:Pixel Alpha	[0x01 ~ 0xFF]:Global Alpha */

	volatile unsigned int *CLK_ADDR_LOW; /* legacy */
	volatile unsigned int *CLK_ADDR_HI; /* legacy */

	int64_t PTS;
	unsigned int CTX;
	unsigned int flags;
	int irq;

	wait_queue_head_t vsync_wait;
	long long vsync_timeout_ms;
	rwlock_t vsync_lock;
	ktime_t  vsync_timestamp;

	volatile void *vo_vsync_flag; /* VSync enable and notify. (VOut => SCPU) */

	unsigned int uiRes32Width;
	unsigned int uiRes32Height;

	struct sync_timeline *timeline;

	int timeline_max;

	struct dc_pending_post *onscreen;

	struct list_head post_list;
	struct mutex post_lock;
	struct task_struct *post_thread;
	struct kthread_work post_work;
	struct kthread_worker post_worker;

	struct list_head complete_list;
	struct mutex complete_lock;
	struct task_struct *complete_thread;
	struct kthread_work complete_work;
	struct kthread_worker complete_worker;

#ifdef CREATE_THREAD_FOR_RELEASE_DEBUG
	struct list_head free_list;
	struct mutex free_lock;
	struct task_struct *free_thread;
	struct kthread_work free_work;
	struct kthread_worker free_worker;
#endif /* End of CREATE_THREAD_FOR_RELEASE_DEBUG */

	DC_SYSTEM_TIME_INFO DC_TIME_INFO;
} DC_INFO;

enum {
	RPC_READY			   = (1U << 0),
	ISR_INIT				= (1U << 2),
	WAIT_VSYNC			  = (1U << 3),
	CHANGE_RES			  = (1U << 4),
	BG_SWAP				 = (1U << 5),
	SUSPEND				 = (1U << 6),
	VSYNC_FORCE_LOCK		= (1U << 7),
};

inline long	 dc_wait_vsync_timeout	   (DC_INFO *pdc_info);
void			dc_update_vsync_timestamp   (DC_INFO *pdc_info);
static int dc_do_simple_post_config(VENUSFB_MACH_INFO * video_info, void *arg);

#ifdef CONFIG_RTK_RPC
DC_INFO *gpdc_info;
DEFINE_SPINLOCK(gASLock);
//EXPORT_SYSMBOL(gASLock);
EXPORT_SYMBOL(gASLock);
#else
static DEFINE_SPINLOCK(gASLock);
#endif

void DC_Reset_OSD_param(struct fb_info *fb, VENUSFB_MACH_INFO * video_info)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	DC_UNREFERENCED_PARAMETER (fb);
	pdc_info->PTS = 0;
	pdc_info->CTX = 0;
	clkResetPresentation(pdc_info->REF_CLK);
}

int DC_Set_RPCAddr(struct fb_info *fb, VENUSFB_MACH_INFO * video_info, DCRT_PARAM_RPC_ADDR* param)
{

	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	DC_UNREFERENCED_PARAMETER (pdc_info);
	DC_UNREFERENCED_PARAMETER (fb);
	DC_UNREFERENCED_PARAMETER (video_info);

	#if 0
	// Set RefClk Table
	pdc_info->REF_CLK = (REFCLOCK*)
		phys_to_virt((phys_addr_t)ulPhyAddrFilter(param->refclockAddr));
		//ioremap((phys_addr_t)ulPhyAddrFilter(param->refclockAddr),sizeof(pdc_info->REF_CLK));

	// Set CMD Queue (Ring Buffer)
	pdc_info->RING_HEADER = (RINGBUFFER_HEADER*)
		phys_to_virt((phys_addr_t)ulPhyAddrFilter(param->ringPhyAddr));
		//ioremap((phys_addr_t)ulPhyAddrFilter(param->ringPhyAddr),sizeof(pdc_info->RING_HEADER));
	#endif

	dprintk("[%s] REFCLK: phy:0x%08x vir:%p\n", __func__, (u32)param->refclockAddr, pdc_info->REF_CLK);
	dprintk("[%s] RING_HEADER: phy:0x%08x vir:%p\n", __func__, (u32)param->ringPhyAddr, pdc_info->RING_HEADER);
	DC_Reset_OSD_param(fb,video_info);

	pdc_info->REF_CLK->mastership.videoMode = AVSYNC_FORCED_MASTER;

	{
		DC_PRESENTATION_INFO pos;
		clkGetPresentation(pdc_info->REF_CLK, &pos);
		iprintk("CLK pts:%lld ctx:%d\n", pos.videoSystemPTS,pos.videoContext);
		iprintk("drvBeAddr:%x s:%u id:%u rw:(%x %x) #rPtr:%u\n",
				(unsigned int)pli_IPCReadULONG((BYTE*)&pdc_info->RING_HEADER->beginAddr),
				pli_IPCReadULONG((BYTE*)&pdc_info->RING_HEADER->size),
				pli_IPCReadULONG((BYTE*)&pdc_info->RING_HEADER->bufferID),
				(unsigned int)pli_IPCReadULONG( (BYTE*)&pdc_info->RING_HEADER->readPtr[0]),
				(unsigned int)pli_IPCReadULONG( (BYTE*)&pdc_info->RING_HEADER->writePtr),
				pli_IPCReadULONG((BYTE*) &pdc_info->RING_HEADER->numOfReadPtr)
			  );
	}

	smp_mb();
	pdc_info->flags |= RPC_READY;
	smp_mb();

	return 0;
}

int Get_RefClock(struct fb_info *fb, VENUSFB_MACH_INFO * video_info, REFCLOCK* pclk)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	REFCLOCK* clk = pdc_info->REF_CLK;
	DC_UNREFERENCED_PARAMETER (pdc_info);
	DC_UNREFERENCED_PARAMETER (fb);
	DC_UNREFERENCED_PARAMETER (video_info);
	if(clk == NULL) return -EAGAIN;
	else {
		unsigned long PliReadMastership = (unsigned long)   pli_IPCReadULONG		((BYTE*)&clk->mastership	  );
		pclk->mastership.systemMode	 = (unsigned char)   ((PliReadMastership & 0xff000000) >> 24);
		pclk->mastership.videoMode	  = (unsigned char)   ((PliReadMastership & 0x00ff0000) >> 16);
		pclk->mastership.audioMode	  = (unsigned char)   ((PliReadMastership & 0x0000ff00) >> 8);
		pclk->mastership.masterState	= (unsigned char)   ((PliReadMastership & 0x000000ff) >> 0);
		pclk->AO_Underflow			  = (unsigned long)   pli_IPCReadULONG		((BYTE*)&clk->AO_Underflow	);
		pclk->GPTSTimeout			   = (long long)	   pli_IPCReadULONGLONG	((BYTE*)&clk->GPTSTimeout	 );
		pclk->RCD					   = (long long)	   pli_IPCReadULONGLONG	((BYTE*)&clk->RCD			 );
		pclk->RCD_ext				   = (unsigned long)   pli_IPCReadULONG		((BYTE*)&clk->RCD_ext		 );
		pclk->VO_Underflow			  = (unsigned long)   pli_IPCReadULONG		((BYTE*)&clk->VO_Underflow	);
		pclk->audioContext			  = (unsigned long)   pli_IPCReadULONG		((BYTE*)&clk->audioContext	);
		pclk->videoContext			  = (unsigned long)   pli_IPCReadULONG		((BYTE*)&clk->videoContext	);
		pclk->masterGPTS				= (long long)	   pli_IPCReadULONGLONG	((BYTE*)&clk->masterGPTS	  );
		pclk->audioSystemPTS			= (long long)	   pli_IPCReadULONGLONG	((BYTE*)&clk->audioSystemPTS  );
		pclk->videoSystemPTS			= (long long)	   pli_IPCReadULONGLONG	((BYTE*)&clk->videoSystemPTS  );
		pclk->audioRPTS				 = (long long)	   pli_IPCReadULONGLONG	((BYTE*)&clk->audioRPTS	   );
		pclk->videoRPTS				 = (long long)	   pli_IPCReadULONGLONG	((BYTE*)&clk->videoRPTS	   );
	}
	return 0;
}

int DC_Get_BufferAddr(struct fb_info *fb, VENUSFB_MACH_INFO * video_info,DCRT_PARAM_BUF_ADDR* param)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	DC_UNREFERENCED_PARAMETER (pdc_info);
	DC_UNREFERENCED_PARAMETER (video_info);
	//TODO: Info from fb framebuffer info
#if 1
	memset(param, 0, sizeof(*param));
	param->width  = fb->var.xres;
	param->height = fb->var.yres;
	return 0;
#else
	DC_NOHW_DEVINFO *psDevInfo;
	psDevInfo = GetAnchorPtr();
	if( param->buf_id <= DC_NOHW_MAX_BACKBUFFERS)
	{
		param->buf_Paddr = psDevInfo->asBackBuffers[param->buf_id].sSysAddr.uiAddr | 0xa0000000;
		param->buf_Vaddr = (unsigned int)psDevInfo->asBackBuffers[param->buf_id].sCPUVAddr;
		param->buf_size = psDevInfo->sSysDims.ui32Height * psDevInfo->sSysDims.ui32ByteStride;
		param->width = psDevInfo->sSysDims.ui32Width;
		param->height = psDevInfo->sSysDims.ui32Height;
		param->format =  psDevInfo->sSysFormat.pixelformat; //PVRSRV_PIXEL_FORMAT
		DCRT_DEBUG("get BUF_ADDR 0x%x 0x%x id:%d %u %d wh(%u %u)\n", param->buf_Paddr,
				param->buf_Vaddr,
				param->buf_id, param->buf_size, param->format, param->width, param->height);
	}
	else
	{
		memset(param, 0, sizeof(param));
	}
	return 0;
#endif
}

int DC_VsyncWait(unsigned long long *nsecs)
{
	if (gpdc_info)
		dc_wait_vsync_timeout(gpdc_info);
	else
		msleep(16);

	if (nsecs)
		*nsecs = ktime_to_ns(ktime_get());

	return 0;
}
EXPORT_SYMBOL(DC_VsyncWait);

int DC_Wait_Vsync(struct fb_info *fb, VENUSFB_MACH_INFO * video_info, unsigned long long *nsecs)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	DC_UNREFERENCED_PARAMETER (pdc_info);
	DC_UNREFERENCED_PARAMETER (fb);
	DC_UNREFERENCED_PARAMETER (video_info);

	// WIAT VSYNC EVENT
#if 0
	msleep(16);
#else
	dc_wait_vsync_timeout(pdc_info);
#endif

	// WRITE NSECS TO USER
	*nsecs = ktime_to_ns(ktime_get());
	return 0;
}

int DC_Set_RateInfo(struct fb_info *fb, VENUSFB_MACH_INFO * video_info,DCRT_PARAM_RATE_INFO* param)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	DC_UNREFERENCED_PARAMETER (pdc_info);
	DC_UNREFERENCED_PARAMETER (fb);
	DC_UNREFERENCED_PARAMETER (video_info);
#if 0
	pdc_info->CLK_ADDR_LOW = (unsigned int*)ioremap((phys_addr_t)ulPhyAddrFilter(param->clockAddrLow) ,0x4);
	pdc_info->CLK_ADDR_HI =  (unsigned int*)ioremap((phys_addr_t)ulPhyAddrFilter(param->clockAddrHi)   ,0x4);
#else
	pdc_info->CLK_ADDR_LOW = (unsigned int*)phys_to_virt((phys_addr_t)ulPhyAddrFilter(param->clockAddrLow));
	pdc_info->CLK_ADDR_HI =  (unsigned int*)phys_to_virt((phys_addr_t)ulPhyAddrFilter(param->clockAddrHi));
#endif
	iprintk("DC rInfo: pdc_info->CLK_ADDR_LOW=%p pdc_info->CLK_ADDR_HI=%p\n", pdc_info->CLK_ADDR_LOW, pdc_info->CLK_ADDR_HI);
	return 0;
}

int DC_Get_Clock_Map_Info(struct fb_info *fb, VENUSFB_MACH_INFO * video_info,DC_CLOCK_MAP_INFO * param)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	DC_UNREFERENCED_PARAMETER (pdc_info);
	DC_UNREFERENCED_PARAMETER (fb);
	DC_UNREFERENCED_PARAMETER (video_info);
#if 1
	wprintk("[%s] WE ARE NOT SUPPORT!\n",__func__);
	memset(param,0,sizeof(DC_CLOCK_MAP_INFO));
#else
	if(pdc_info->CLK_ADDR_LOW == NULL || pdc_info->CLK_ADDR_HI == NULL) return -EAGAIN;
	else {
		DC_CLOCK_MAP_INFO info;
		info.HiOffset   = ((unsigned int)pdc_info->CLK_ADDR_HI) &  (PAGE_SIZE-1);
		info.LowOffset  = ((unsigned int)pdc_info->CLK_ADDR_LOW) & (PAGE_SIZE-1);
		memcpy(param,&info,sizeof(DC_CLOCK_MAP_INFO));
	}
#endif
	return 0;
}

int DC_Get_Clock_Info(struct fb_info *fb, VENUSFB_MACH_INFO * video_info,REFCLOCK * RefClock)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	DC_UNREFERENCED_PARAMETER (pdc_info);
	DC_UNREFERENCED_PARAMETER (fb);
	DC_UNREFERENCED_PARAMETER (video_info);
	return Get_RefClock(fb,video_info,RefClock);
}

int DC_Reset_RefClock_Table(struct fb_info *fb, VENUSFB_MACH_INFO * video_info,unsigned int option)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	REFCLOCK* clk = pdc_info->REF_CLK;
	DC_UNREFERENCED_PARAMETER (pdc_info);
	DC_UNREFERENCED_PARAMETER (fb);
	DC_UNREFERENCED_PARAMETER (video_info);
	if( clk != NULL)
	{
		if(option & ResetOption_videoSystemPTS)
			pli_IPCWriteULONGLONG(  (BYTE*)&clk->videoSystemPTS	 , -1ULL);
		if(option & ResetOption_audioSystemPTS)
			pli_IPCWriteULONGLONG(  (BYTE*)&clk->audioSystemPTS	 , -1ULL);
		if(option & ResetOption_videoRPTS)
			pli_IPCWriteULONGLONG(  (BYTE*)&clk->videoRPTS		  , -1ULL);
		if(option & ResetOption_audioRPTS)
			pli_IPCWriteULONGLONG(  (BYTE*)&clk->audioRPTS		  , -1ULL);
		if(option & ResetOption_videoContext)
			pli_IPCWriteULONG(	  (BYTE*)&clk->videoContext	   , -1U);
		if(option & ResetOption_audioContext)
			pli_IPCWriteULONG(	  (BYTE*)&clk->audioContext	   , -1U);
		if(option & ResetOption_videoEndOfSegment)
			pli_IPCWriteULONG(	  (BYTE*)&clk->videoEndOfSegment  , -1U);
		//if(option & ResetOption_RCD)
		//	pli_IPCWriteULONGLONG(  (BYTE*)&clk->RCD				,-1);
		return 0;
	}
	else return -1;
}

int DC_Get_System_Time_Info(struct fb_info *fb, VENUSFB_MACH_INFO * video_info, DC_SYSTEM_TIME_INFO * param)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	DC_UNREFERENCED_PARAMETER (pdc_info);
	DC_UNREFERENCED_PARAMETER (fb);
	DC_UNREFERENCED_PARAMETER (video_info);
	pdc_info->DC_TIME_INFO.PTS			  =					   pdc_info->PTS;
	pdc_info->DC_TIME_INFO.CTX			  =					   pdc_info->CTX;
	pdc_info->DC_TIME_INFO.RefClockAddr	 = (unsigned long long)  pdc_info->REF_CLK;
	pdc_info->DC_TIME_INFO.ClockAddr_HI	 = (unsigned long long)  pdc_info->CLK_ADDR_HI;
	pdc_info->DC_TIME_INFO.ClockAddr_LOW	= (unsigned long long)  pdc_info->CLK_ADDR_LOW;
	pdc_info->DC_TIME_INFO.WAIT_ISR		 =				   0;//atomic_read(&pdc_info->ISR_FLIP);
	pdc_info->DC_TIME_INFO.RTK90KClock	  = 0;
	pdc_info->DC_TIME_INFO.RTK90KClock	  = ((unsigned long long) readl(pdc_info->CLK_ADDR_HI))<<32;
	pdc_info->DC_TIME_INFO.RTK90KClock	 |= readl(pdc_info->CLK_ADDR_LOW);

	if(Get_RefClock(fb,video_info,&pdc_info->DC_TIME_INFO.RefClock) != 0) return -EAGAIN;
	memcpy(param,&pdc_info->DC_TIME_INFO,sizeof(DC_SYSTEM_TIME_INFO));
	return 0;
}

int DC_Get_Surface(struct fb_info *fb, VENUSFB_MACH_INFO * video_info, DCRT_PARAM_SURFACE* param)
{
#if 1
	DC_UNREFERENCED_PARAMETER (fb);
	DC_UNREFERENCED_PARAMETER (video_info);
	DC_UNREFERENCED_PARAMETER (param);
	wprintk("[%s] WE ARE NOT SUPPORT!\n",__func__);
	return 0;
#else
	int err=0;
	int idx = 0;
	DC_NOHW_DEVINFO *psDevInfo = (DC_NOHW_DEVINFO *)gpvAnchor;
	DCRT_VSYNC_FLIP_ITEM *psFlipItem= NULL;
	unsigned long ulLockFlags;

	if( psDevInfo == NULL || psDevInfo->psSwapChain == NULL) {
		err = -ENOENT;
		goto DC_Get_Surface_End;
	}
	else if( psDevInfo->ui32BufferSize < param->buf_size) {
		err = -EINVAL;
		goto DC_Get_Surface_End;
	}
	spin_lock_irqsave(&psDevInfo->psSwapChainLock, ulLockFlags);
	if( psDevInfo->ulInsertIndex != psDevInfo->ulRemoveIndex)
	{
		idx = psDevInfo->ulInsertIndex;
	}
	else { //==, use last one
		idx = psDevInfo->ulInsertIndex;
	}
	psFlipItem = &psDevInfo->psVSyncFlips[idx];
	{
		unsigned int srcAddr  = (unsigned int )phys_to_virt(psFlipItem->phyAddr);
		unsigned int dstAddr = (unsigned int )phys_to_virt(param->buf_Paddr);
		if( md_memcpy( (void*)dstAddr, (void*)srcAddr,  param->buf_size, true) != 0 )
		{  //md copy err
			err = -EAGAIN;
		}
	}
	spin_unlock_irqrestore(&psDevInfo->psSwapChainLock, ulLockFlags);
DC_Get_Surface_End:
	if( err) {
		//****   ****//
	}
	return err;
#endif
}

int DC_Set_ION_Share_Memory(struct fb_info *fb, VENUSFB_MACH_INFO *video_info,
	DC_ION_SHARE_MEMORY *param)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	DC_UNREFERENCED_PARAMETER (fb);
	DC_UNREFERENCED_PARAMETER (video_info);

	if (pdc_info->gpsIONClient == NULL)
		pdc_info->gpsIONClient = ion_client_create(rtk_phoenix_ion_device, "dc2vo");

	if (param->sfd_refclk != 0) {
		struct ion_handle *refclk_handle;

		refclk_handle = ion_import_dma_buf(pdc_info->gpsIONClient, dma_buf_get(param->sfd_refclk));
		pdc_info->REF_CLK = ion_map_kernel(pdc_info->gpsIONClient, refclk_handle);
		dprintk("[%s] refclk sfd:%d handle:%p vAddr:%p\n", __func__,
				param->sfd_refclk, refclk_handle, pdc_info->REF_CLK);
	}
	if (param->sfd_rbHeader!= 0) {
		struct ion_handle *rbHeader_handle;

		rbHeader_handle = ion_import_dma_buf(pdc_info->gpsIONClient, dma_buf_get(param->sfd_rbHeader));
		pdc_info->RING_HEADER =  ion_map_kernel(pdc_info->gpsIONClient, rbHeader_handle);
		dprintk("[%s] rbHeader sfd:%d handle:%p vAddr:%p\n", __func__,
				param->sfd_rbHeader, rbHeader_handle, pdc_info->RING_HEADER);
	}
	if (param->sfd_rbBase != 0) {
		struct ion_handle *rbBase_handle;

		rbBase_handle = ion_import_dma_buf(pdc_info->gpsIONClient, dma_buf_get(param->sfd_rbBase));
		pdc_info->RING_HEADER_BASE = ion_map_kernel(pdc_info->gpsIONClient, rbBase_handle);
		dprintk("[%s] rbHeaderBase sfd:%d handle:%p vAddr:%p\n", __func__,
				param->sfd_rbBase, rbBase_handle, pdc_info->RING_HEADER_BASE);
	}
	return 0;
}

int DC_Set_Buffer_Info(struct fb_info *fb, VENUSFB_MACH_INFO *video_info, DC_BUFFER_INFO *param)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	DC_UNREFERENCED_PARAMETER (fb);
	DC_UNREFERENCED_PARAMETER (video_info);
	if (pdc_info == NULL || param == NULL)
		goto err;

	if (param->enable)
		pdc_info->flags |= CHANGE_RES;
	else
		pdc_info->flags &= ~CHANGE_RES;

	pdc_info->uiRes32Width = param->width;
	pdc_info->uiRes32Height = param->height;

	dprintk("[%s] enable:%d width:%d height:%d\n",__func__,param->enable,param->width,param->height);
	return 0;
err:
	eprintk("[%s] ERROR!",__func__);
	return -1;
}

#define goERROR(tag) { \
eprintk("ERROR! CMD = %u LINE = %d tag = %d",cmd,__LINE__,tag); \
goto ERROR; \
}

int DC_Ioctl (struct fb_info *fb, VENUSFB_MACH_INFO *video_info,
	unsigned int cmd, unsigned long arg)
{
	int retval = 0;

	switch (cmd) {
	case DC2VO_GET_BUFFER_ADDR:
		{
			DCRT_PARAM_BUF_ADDR param;
			if (copy_from_user(&param, (void *)arg, sizeof(param)) != 0)
				goERROR(0);
			retval = DC_Get_BufferAddr(fb,video_info,&param);
			if (copy_to_user((void *)arg, &param, sizeof(param)) != 0)
				goERROR(0);
			break;
		}
	case DC2VO_SET_RING_INFO:
		{
			DCRT_PARAM_RPC_ADDR param;
			if (copy_from_user(&param, (void *)arg, sizeof(param)) != 0)
				goERROR(0);
			retval = DC_Set_RPCAddr(fb, video_info, &param);
			break;
		}
	case DC2VO_SET_OUT_RATE_INFO:
		{
			DCRT_PARAM_RATE_INFO param;
			if (copy_from_user(&param, (void *)arg, sizeof(param)) != 0)
				goERROR(0);
			if( param.param_size != sizeof(DCRT_PARAM_RATE_INFO) )
				goERROR(0);
			retval = DC_Set_RateInfo(fb, video_info, &param);
			break;
		}
	case DC2VO_GET_CLOCK_MAP_INFO:
		{
			DC_CLOCK_MAP_INFO param;

			if(DC_Get_Clock_Map_Info(fb, video_info, &param) != 0)
				goERROR(0);
			if(copy_to_user((void *)arg, &param, sizeof(DC_CLOCK_MAP_INFO)) != 0)
				goERROR(0);
			break;
		}
	case DC2VO_GET_CLOCK_INFO:
		{
			REFCLOCK RefClock;

			if(DC_Get_Clock_Info(fb, video_info, &RefClock) != 0)
				goERROR(0);
			if(copy_to_user((void *)arg, &RefClock, sizeof(REFCLOCK)) != 0)
				goERROR(0);
			break;
		}
	case DC2VO_RESET_CLOCK_TABLE	 :
		{
			unsigned int option = 0;

			if(copy_from_user(&option,(void *)arg, sizeof(option)) != 0)
				goERROR(0);
			if(DC_Reset_RefClock_Table(fb, video_info, option) != 0)
				goERROR(0);
			break;
		}
	case FBIO_WAITFORVSYNC:
		{
			unsigned long long nsecs;

			if (DC_Wait_Vsync(fb, video_info, &nsecs) != 0)
				goERROR(0);
			//if(copy_to_user((void *)arg,&nsecs,sizeof(u32)) != 0)
			// goERROR(0);
			break;
		}
	case DC2VO_WAIT_FOR_VSYNC:
		{
			unsigned long long nsecs;

			if (DC_Wait_Vsync(fb, video_info, &nsecs) != 0)
				goERROR(0);
			if(copy_to_user((void *)arg, &nsecs, sizeof(nsecs)) != 0)
				goERROR(0);
			break;
		}
	case DC2VO_GET_SURFACE:
		{
			DCRT_PARAM_SURFACE param;

			if (copy_from_user(&param, (void *)arg, sizeof(param)) != 0)
				goERROR(0);
			if( param.param_size != sizeof(DCRT_PARAM_SURFACE) )
				goERROR(0);
			retval = DC_Get_Surface(fb, video_info, &param);
			break;
		}
	case DC2VO_GET_SYSTEM_TIME_INFO:
		{
			DC_SYSTEM_TIME_INFO param;

			DC_Get_System_Time_Info(fb, video_info, &param);
			if(copy_to_user((void *)arg, &param, sizeof(DC_SYSTEM_TIME_INFO)) != 0)
				goERROR(0);
			break;
		}
	case DC2VO_GET_MAX_FRAME_BUFFER:
		{
			unsigned int MAX_FRAME_BUFFER = DC_NOHW_MAX_BACKBUFFERS;
			if (copy_to_user((void *)arg, &MAX_FRAME_BUFFER, sizeof(MAX_FRAME_BUFFER)) != 0)
				goERROR(0);
			break;
		}
	case RTKFB_SET_VSYNC_INT	:
		{
			/*
			 * 1: enable vsync
			 * 0: disable vsync
			 */
			break;
		}
	case DC2VO_SET_ION_SHARE_MEMORY:
		{
			DC_ION_SHARE_MEMORY param;

			if (copy_from_user(&param, (void *)arg, sizeof(param)) != 0)
				goERROR(0);
			if (DC_Set_ION_Share_Memory(fb, video_info, &param) != 0)
				goERROR(0);
			break;
		}
	case DC2VO_SET_BUFFER_INFO:
		{
			DC_BUFFER_INFO param;

			if (copy_from_user(&param, (void *)arg, sizeof(param)) != 0)
				goERROR(0);
			if (DC_Set_Buffer_Info(fb, video_info, &param) != 0)
				goERROR(0);
			break;
		}
	case DC2VO_SET_BG_SWAP:
		{
			DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
			unsigned int swap;

			if (pdc_info == NULL)
				goERROR(0);
			if (copy_from_user(&swap, (void *)arg, sizeof(swap)) != 0)
				goERROR(0);

			if (swap)
				pdc_info->flags |= BG_SWAP;
			else
				pdc_info->flags &= ~BG_SWAP;

			break;
		}
	case DC2VO_SET_VSYNC_FORCE_LOCK:
		{
			DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
			unsigned int lock;

			if (pdc_info == NULL)
				goERROR(0);
			if (copy_from_user(&lock, (void *)arg, sizeof(lock)) != 0)
				goERROR(0);

			if (lock)
				pdc_info->flags |= VSYNC_FORCE_LOCK;
			else
				pdc_info->flags &= ~VSYNC_FORCE_LOCK;

			break;
		}
	case DC2VO_SET_GLOBAL_ALPHA:
		{
			DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
			unsigned int alpha;

			if (pdc_info == NULL)
				goERROR(0);
			if (copy_from_user(&alpha, (void *)arg, sizeof(alpha)) != 0)
				goERROR(0);

			if (alpha <= 0xFF)
				pdc_info->gAlpha = alpha;
			else
				pdc_info->gAlpha = 0; /* 0 : Pixel Alpha */

			break;
		}
	case DC2VO_SIMPLE_POST_CONFIG:
		{
			if (dc_do_simple_post_config(video_info, (void *)arg))
				goERROR(0);
			break;
		}
	case DC2VO_SET_SYSTEM_TIME_INFO:
	case DC2VO_SET_BUFFER_ADDR:
	case DC2VO_SET_DISABLE:
	case DC2VO_SET_MODIFY:
		{
			dprintk("[%s %d] CMD = %u \n",__func__,__LINE__,cmd);
			break;
		}
	default:
		retval = -EAGAIN;
	}

	return retval;

ERROR:

#undef goERROR

	return -EFAULT;
}

#ifdef CONFIG_RTK_RPC
void dc_irq_handler(void)
{
	DC_INFO * pdc_info = gpdc_info;
	if (DCINIT == 0)
		return;

	if(!DC_HAS_BIT(pdc_info->vo_vsync_flag, DC_VO_FEEDBACK_NOTIFY))
		return;

	DC_RESET_BIT(pdc_info->vo_vsync_flag,  DC_VO_FEEDBACK_NOTIFY) ;
	dc_update_vsync_timestamp(pdc_info);

	return;
}
EXPORT_SYMBOL(dc_irq_handler);
#else
irqreturn_t dc_irq_handler(int irq, void *dev_id)
{
	VENUSFB_MACH_INFO * video_info = (VENUSFB_MACH_INFO *)dev_id;
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	DC_UNREFERENCED_PARAMETER (pdc_info);

	if(!DC_HAS_BIT(pdc_info->vo_vsync_flag, DC_VO_FEEDBACK_NOTIFY))
		return IRQ_NONE;

	DC_RESET_BIT(pdc_info->vo_vsync_flag,  DC_VO_FEEDBACK_NOTIFY) ;
	dc_update_vsync_timestamp(pdc_info);

	return IRQ_HANDLED;
}
#endif

int Activate_vSync(VENUSFB_MACH_INFO * video_info)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	int result=0;
	DC_UNREFERENCED_PARAMETER (pdc_info);
	dprintk("%s:%d DEBUG!!!! \n", __func__, __LINE__);
#ifndef CONFIG_RTK_RPC
	if( !(pdc_info->flags & ISR_INIT))
	{
		if (pdc_info->irq > 0)
			result = request_irq(pdc_info->irq, dc_irq_handler, IRQF_SHARED, "dc2vo", (void *) video_info);
		else
			result = request_irq(DCRT_IRQ, dc_irq_handler, IRQF_SHARED, "dc2vo", (void *) video_info);
		if(result)
		{
			eprintk("DC: irq ins fail %i\n", DCRT_IRQ);
			return result;
		}
		else {
			dprintk("DC irq Ins\n");
			smp_mb();
			pdc_info->flags |= ISR_INIT;
			smp_mb();
		}
	}
#endif
	spin_lock_irq(&gASLock);
	DC_SET_BIT(pdc_info->vo_vsync_flag, DC_VO_SET_NOTIFY);
	spin_unlock_irq(&gASLock);
	return result;
}

int DeInit_vSync(VENUSFB_MACH_INFO * video_info)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	unsigned long ulLockFlags;
	static spinlock_t  vSyncLock;
	DC_UNREFERENCED_PARAMETER (pdc_info);
	spin_lock_irqsave(&vSyncLock, ulLockFlags);
	if( pdc_info->flags & ISR_INIT ) {
#ifndef CONFIG_RTK_RPC
		free_irq(DCRT_IRQ, (void *) video_info);
#endif
		smp_mb();
		pdc_info->flags &= ~ISR_INIT;
		smp_mb();
		dprintk("DC irqUn\n");
	}
	spin_unlock_irqrestore(&vSyncLock, ulLockFlags);
	return 0;
}

long dc_wait_vsync_timeout(DC_INFO *pdc_info)
{
    long ret = 0;
	unsigned long   flags;
	ktime_t		 timestamp;
	long			timeout;

	read_lock_irqsave(&pdc_info->vsync_lock, flags);
	timestamp = pdc_info->vsync_timestamp;
	read_unlock_irqrestore(&pdc_info->vsync_lock, flags);

	timeout = wait_event_interruptible_hrtimeout(pdc_info->vsync_wait,
			!ktime_equal(timestamp, pdc_info->vsync_timestamp),
            ktime_set( 0, (pdc_info->vsync_timeout_ms * NSEC_PER_MSEC)));

	if (timeout ==  -ETIME) {
		unsigned int flag = pli_IPCReadULONG((BYTE*)pdc_info->vo_vsync_flag);
		eprintk("[%s %d] wait vsync timeout! vo_vsync_flag:0x%08x\n",
				__func__, __LINE__, flag);
        ret = -1L;
	}

	return ret;
}

void dc_update_vsync_timestamp(DC_INFO *pdc_info)
{
	unsigned long flags;

	write_lock_irqsave(&pdc_info->vsync_lock, flags);
	pdc_info->vsync_timestamp = ktime_get();
	write_unlock_irqrestore(&pdc_info->vsync_lock, flags);

	wake_up_interruptible_all(&pdc_info->vsync_wait);
}

static void dc_fence_wait(DC_INFO * pdc_info, struct sync_file *fence)
{
	/* fence_wait() dumps debug information on timeout.  Experience
	 * has shown that if the pipeline gets stuck, a short timeout followed
	 * by a longer one provides useful information for debugging.
	 */

	int err = fence_wait_timeout(fence->fence, 1, DC_SHORT_FENCE_TIMEOUT);

	if (err >= 0)
		return;

	if (err == -ETIME)
		err = fence_wait_timeout(fence->fence, 1, DC_LONG_FENCE_TIMEOUT);

	if (err < 0)
		pr_warn("error waiting on fence: %d\n", err);
}

static void dc_fence_put(struct sync_file *fence)
{
	struct fence *my_fence = fence->fence;

	if (my_fence)
		kref_put(&my_fence->refcount, fence_release);
}

void dc_buffer_dump(struct dc_buffer *buf)
{
	if (!buf) {
		eprintk("buffer is null!\n");
		return;
	}
	wprintk("buffer:%p id:%d ov_engine:%d fmt:%d offset:0x%x ctx:%d [%d %d %d %d] [%d %d %d %d]\n",
			buf, buf->id, buf->overlay_engine, buf->format, buf->offset, buf->context,
			buf->sourceCrop.left,
			buf->sourceCrop.top,
			buf->sourceCrop.right,
			buf->sourceCrop.bottom,
			buf->displayFrame.left,
			buf->displayFrame.top,
			buf->displayFrame.right,
			buf->displayFrame.bottom);
}

void dc_buffer_cleanup(struct dc_buffer *buf)
{
	if (buf->acquire.fence)
		dc_fence_put(buf->acquire.fence);

	kfree(buf);
}

void dc_post_cleanup(DC_INFO *pdc_info, struct dc_pending_post *post)
{
	size_t i;
	for (i = 0; i < post->config.n_bufs; i++)
		dc_buffer_cleanup(&post->config.bufs[i]);

#if 0
	if (post->release.fence)
		dc_fence_put(post->release.fence);
#endif

	kfree(post);
}

#if 0
static struct sync_file *dc_sw_complete_fence(DC_INFO *pdc_info)
{
	struct sync_pt *pt;
	struct sync_file *complete_fence;

	if (!pdc_info->timeline) {
		pdc_info->timeline = sw_sync_timeline_create("rtk_fb");
		if (!pdc_info->timeline)
			return ERR_PTR(-ENOMEM);
		pdc_info->timeline_max = 1;
	}

	dprintk("[%s %d] sw_sync_pt_create (%d)\n", __func__, __LINE__, pdc_info->timeline_max);
	pt = sw_sync_pt_create(pdc_info->timeline, pdc_info->timeline_max);
	pdc_info->timeline_max++;
	if (!pt)
		goto err_pt_create;

	complete_fence = sync_fence_create("rtk_fb", pt);
	if (!complete_fence)
		goto err_fence_create;


	return complete_fence;

err_fence_create:
	eprintk("[%s %d]\n", __func__, __LINE__);
	sync_pt_free(pt);
err_pt_create:
	eprintk("[%s %d]\n", __func__, __LINE__);
	pdc_info->timeline_max--;
	return ERR_PTR(-ENOSYS);
}
#endif

static struct sync_file *dc_sw_complete_fence(DC_INFO *pdc_info)
{
	struct sync_pt *pt;
	struct sync_file *complete_fence;

	if (!pdc_info->timeline) {
		pdc_info->timeline = sync_timeline_create("rtk_fb");
		if (!pdc_info->timeline)
			return ERR_PTR(-ENOMEM);
		pdc_info->timeline_max = 1;
	}

	pr_debug("[%s %d] sync_pt_create (%d)\n", __func__, __LINE__, pdc_info->timeline_max);

	pt = sync_pt_create(pdc_info->timeline, pdc_info->timeline_max);
	pdc_info->timeline_max++;
	if (!pt)
		goto err_pt_create;

	complete_fence = sync_file_create(&pt->base);

	if (!complete_fence)
		goto err_fence_create;

    fence_put(&pt->base);

	return complete_fence;

err_fence_create:
	pr_err("[%s %d]\n", __func__, __LINE__);
	fence_put(&pt->base);

err_pt_create:
	pr_err("[%s %d]\n", __func__, __LINE__);
	pdc_info->timeline_max--;

	return ERR_PTR(-ENOSYS);
}

static int dc_buffer_import(DC_INFO *pdc_info,
		struct dc_buffer __user *buf_from_user, struct dc_buffer *buf)
{
	struct dc_buffer user_buf;
	int ret = 0;

	if (copy_from_user(&user_buf, buf_from_user, sizeof(user_buf)))
		return -EFAULT;

	memcpy(buf, &user_buf, sizeof(struct dc_buffer));

	if (user_buf.acquire.fence_fd >= 0) {
		buf->acquire.fence = sync_file_fdget(user_buf.acquire.fence_fd);
		if (!buf->acquire.fence) {
			eprintk("getting fence fd %lld failed\n", user_buf.acquire.fence_fd);
			ret = -EINVAL;
			goto done;
		}
	} else
		buf->acquire.fence = (struct sync_file *) NULL;

	if (buf->overlay_engine > eEngine_MAX) {
		eprintk("invalid overlay engine id mask %u\n", buf->overlay_engine);
		//ret = -EINVAL;
		//goto done;
	}

	dprintk("[%s %d] buf->acquire_fenc : %p\n", __func__, __LINE__, buf->acquire.fence);
done:
	/*
	 * if (ret < 0)
	 * dc_buffer_cleanup(buf);
	 */
	return ret;
}

static void dc_sw_advance_timeline(DC_INFO *pdc_info)
{
#ifdef CONFIG_SW_SYNC
	sync_timeline_signal(pdc_info->timeline, 1);
#else
	BUG();
#endif
}

struct sync_file *dc_device_post_to_work(DC_INFO * pdc_info,
		struct dc_buffer *bufs, size_t n_bufs)
{
	struct dc_pending_post *cfg;
	struct sync_file *ret;

	cfg = kzalloc(sizeof(*cfg), GFP_KERNEL);
	if (!cfg) {
		ret = ERR_PTR(-ENOMEM);
		goto err_alloc;
	}

	INIT_LIST_HEAD(&cfg->head);
	cfg->config.n_bufs = n_bufs;
	cfg->config.bufs = bufs;

	mutex_lock(&pdc_info->post_lock);
	ret = dc_sw_complete_fence(pdc_info);
	if (IS_ERR(ret))
		goto err_fence;

	cfg->release.fence = ret;

	list_add_tail(&cfg->head, &pdc_info->post_list);
	kthread_queue_work(&pdc_info->post_worker, &pdc_info->post_work);
	mutex_unlock(&pdc_info->post_lock);

	return ret;

err_fence:
	mutex_unlock(&pdc_info->post_lock);

err_alloc:
	if (cfg) {
		if (cfg->config.bufs)
			kfree(cfg->config.bufs);
		kfree(cfg);
	}
	return ret;
}

struct sync_file *dc_device_post(DC_INFO *pdc_info,
	struct dc_buffer *bufs, size_t n_bufs)
{
	struct dc_buffer *bufs_copy = NULL;

	bufs_copy = kzalloc(sizeof(bufs_copy[0]) * n_bufs, GFP_KERNEL);
	if (!bufs_copy)
		return ERR_PTR(-ENOMEM);

	memcpy(bufs_copy, bufs, sizeof(bufs_copy[0]) * n_bufs);

	return dc_device_post_to_work(pdc_info, bufs_copy, n_bufs);
}

struct sync_file *dc_simple_post(DC_INFO *pdc_info,
		struct dc_buffer *buf)
{
	return dc_device_post(pdc_info, buf, 1);
}

struct sync_file * DC_QueueBuffer(struct dc_buffer *buf)
{
	return dc_simple_post(gpdc_info, buf);
}
EXPORT_SYMBOL(DC_QueueBuffer);

static int dc_do_simple_post_config(VENUSFB_MACH_INFO * video_info, void *arg)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	struct dc_simple_post_config __user *cfg = (struct dc_simple_post_config __user *) arg;
	struct sync_file *complete_fence = NULL;
	int complete_fence_fd;
	struct dc_buffer buf;
	int ret = 0;

	//complete_fence_fd = get_unused_fd();
	complete_fence_fd = get_unused_fd_flags(O_CLOEXEC);
	if (complete_fence_fd < 0) {
		eprintk("[%s %d] complete_fence_fd = %d\n", __func__, __LINE__, complete_fence_fd);
		return complete_fence_fd;
	}

	ret = dc_buffer_import(pdc_info, &cfg->buf, &buf);
	if (ret < 0) {
		eprintk("[%s %d] ret = %d\n", __func__, __LINE__, ret);
		goto err_import;
	}

	complete_fence = dc_simple_post(pdc_info, &buf);
	if (IS_ERR(complete_fence)) {
		ret = PTR_ERR(complete_fence);
		eprintk("[%s %d] complete_fence : %p\n", __func__, __LINE__, complete_fence);
		goto err_put_user;
	}

	 fd_install(complete_fence_fd, complete_fence->file);

	if (put_user(complete_fence_fd, &cfg->complete_fence_fd)) {
		eprintk("[%s %d] put_user complete_fence_fd:%d failed!\n", __func__, __LINE__, complete_fence_fd);
		ret = -EFAULT;
		goto err_put_user;
	}

	return 0;

err_put_user:
	//dc_buffer_cleanup(&buf);
err_import:
	put_unused_fd(complete_fence_fd);
	return ret;
}

int DC_Swap_Buffer(struct fb_info *fb, VENUSFB_MACH_INFO * video_info)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	struct sync_file *complete_fence = NULL;
	struct dc_buffer buf;

	if (pdc_info->flags & SUSPEND) {
		dc_wait_vsync_timeout(pdc_info);
		return 0;
	}

	if (debug)
		console_unlock();

	memset(&buf, 0, sizeof(buf));

	buf.id						  = eFrameBuffer;
	buf.overlay_engine			  = eEngine_VO;
	buf.offset					  = fb->var.yoffset;
	buf.acquire.fence			   = (struct sync_file *) 0;

	complete_fence = dc_simple_post(pdc_info, &buf);

	if (IS_ERR(complete_fence))
		goto err;

	dc_fence_wait(pdc_info, complete_fence);

    fput(complete_fence->file);

	if (debug)
		console_lock();
	return 0;

err:
	eprintk("[%s %d]!!!!!!! \n", __func__, __LINE__);
	if (debug)
		console_lock();
	return -EFAULT;
}

static int dc_prepare_framebuffer(DC_INFO *pdc_info, struct dc_buffer *buffer)
{
	struct fb_info *fb  = pdc_info->pfbi;


	fb->var.yoffset	 = buffer->offset;

	buffer->phyAddr	 = fb->fix.smem_start
							+ fb->fix.line_length * fb->var.yoffset
							+ fb->var.xoffset *  (fb->var.bits_per_pixel / 8);

	buffer->stride	  = fb->fix.line_length;
	buffer->format	  = (pdc_info->flags & BG_SWAP)? INBAND_CMD_GRAPHIC_FORMAT_RGBA8888 : INBAND_CMD_GRAPHIC_FORMAT_ARGB8888_LITTLE;

	if (pdc_info->flags & CHANGE_RES && pdc_info->uiRes32Width > 0 && pdc_info->uiRes32Height > 0) {
		buffer->width   = pdc_info->uiRes32Width;
		buffer->height  = pdc_info->uiRes32Height;
	} else {
		buffer->width   = fb->var.xres;
		buffer->height  = fb->var.yres;
	}

	if (!(buffer->flags & eBuffer_USE_GLOBAL_ALPHA))
		buffer->alpha	   = pdc_info->gAlpha;

	if (pdc_info->CTX == -1)
		pdc_info->CTX = 0;
	else
		pdc_info->CTX++;

	buffer->context = pdc_info->CTX;
	return 0;
}

static int dc_prepare_framebuffer_target(DC_INFO *pdc_info, struct dc_buffer *buffer)
{
	struct fb_info *fb  = pdc_info->pfbi;
	bool bIsAFBC = (buffer->flags & eBuffer_AFBC_Enable)?true:false;

	//dprintk("[%s] phyAddr:0x%08x", __FUNCTION__, buffer->phyAddr);
	buffer->stride	  = fb->fix.line_length;
	buffer->format	  = (pdc_info->flags & BG_SWAP)? INBAND_CMD_GRAPHIC_FORMAT_RGBA8888 : INBAND_CMD_GRAPHIC_FORMAT_ARGB8888_LITTLE;

	if (!bIsAFBC && pdc_info->flags & CHANGE_RES && pdc_info->uiRes32Width > 0 && pdc_info->uiRes32Height > 0) {
		buffer->width   = pdc_info->uiRes32Width;
		buffer->height  = pdc_info->uiRes32Height;
	} else {
		buffer->width   = fb->var.xres;
		buffer->height  = fb->var.yres;
	}

	if (!(buffer->flags & eBuffer_USE_GLOBAL_ALPHA))
		buffer->alpha	   = pdc_info->gAlpha;

	if (pdc_info->CTX == -1)
		pdc_info->CTX = 0;
	else
		pdc_info->CTX++;

	buffer->context = pdc_info->CTX;
	return 0;
}

static int dc_prepare_user_buffer(DC_INFO *pdc_info, struct dc_buffer *buffer)
{
	struct fb_info *fb  = pdc_info->pfbi;
	{
		if (buffer->width == 0)
			buffer->width   = fb->var.xres;

		if (buffer->height == 0)
			buffer->height  = fb->var.yres;

		if (buffer->stride == 0)
			buffer->stride = buffer->width * 4;

		if (buffer->format == 0)
			buffer->format	  = (pdc_info->flags & BG_SWAP)?
				INBAND_CMD_GRAPHIC_FORMAT_RGBA8888 : INBAND_CMD_GRAPHIC_FORMAT_ARGB8888_LITTLE;

		if (!(buffer->flags & eBuffer_USE_GLOBAL_ALPHA))
			buffer->alpha	   = pdc_info->gAlpha;
	}

	if (pdc_info->CTX == -1)
		pdc_info->CTX = 0;
	else
		pdc_info->CTX++;

	buffer->context = pdc_info->CTX;

	return 0;
}

static int dc_queue_vo_buffer(DC_INFO *pdc_info, struct dc_buffer *buffer)
{
	VIDEO_GRAPHIC_PICTURE_OBJECT obj;

	if (!(pdc_info->flags & RPC_READY)) {
		eprintk("[%s %d] pdc_info->RING_HEADER = %p\n",
			__func__, __LINE__, pdc_info->RING_HEADER);
		buffer->id = eFrameBufferSkip;
		return 0;
	}

	if (pdc_info->flags & SUSPEND) {
		buffer->id = eFrameBufferSkip;
		return 0;
	}

	obj.header.type = VIDEO_GRAPHIC_INBAND_CMD_TYPE_PICTURE_OBJECT;
	obj.header.size = sizeof(VIDEO_GRAPHIC_PICTURE_OBJECT);
	obj.context = (unsigned int) buffer->context;
	obj.PTSH = 0;
	obj.PTSL = 0;
	obj.colorkey = -1;
	obj.alpha = buffer->alpha;
	obj.x = 0;
	obj.y = 0;
	obj.format = buffer->format;
	obj.width = buffer->width;
	obj.height = buffer->height;
	obj.pitch = buffer->stride;
	obj.address = buffer->phyAddr;
	obj.address_right = 0;
	obj.pitch_right = 0;
	obj.picLayout = INBAND_CMD_GRAPHIC_2D_MODE;
	obj.afbc = (buffer->flags & eBuffer_AFBC_Enable)?1:0;
	obj.afbc_block_split = (buffer->flags & eBuffer_AFBC_Split)?1:0;
	obj.afbc_yuv_transform = (buffer->flags & eBuffer_AFBC_YUV_Transform)?1:0;

#ifdef DC2VO_SUPPORT_MEMORY_TRASH
	if (gbMemoryTrash && obj.afbc)
		obj.afbc |= VO_AFBC_DEBUG_MASK;
#endif /* End of DC2VO_SUPPORT_MEMORY_TRASH */

	if (ICQ_WriteCmd(&obj, pdc_info->RING_HEADER, pdc_info->RING_HEADER_BASE)) {
		eprintk("[%s %d]ERROR!! Write CMD Error!\n",__FUNCTION__, __LINE__);
		return -EAGAIN;
	}

#ifdef CONFIG_RTK_RPC
	dc2vo_send_interrupt();
#endif

	return 0;
}

static int dc_queue_framebuffer(DC_INFO *pdc_info, struct dc_buffer *buffer)
{

	dprintk("[%s %d]\n", __func__, __LINE__);

	if(dc_prepare_framebuffer(pdc_info, buffer))
		goto err;

	if(dc_queue_vo_buffer(pdc_info, buffer))
		goto err;

	return 0;

err:
	return -EAGAIN;
}

static int dc_queue_framebuffer_target(DC_INFO *pdc_info, struct dc_buffer *buffer)
{

	dprintk("[%s %d]\n", __func__, __LINE__);

	if(dc_prepare_framebuffer_target(pdc_info, buffer))
		goto err;

	if(dc_queue_vo_buffer(pdc_info, buffer))
		goto err;

	return 0;

err:
	return -EAGAIN;
}

static int dc_queue_user_buffer(DC_INFO *pdc_info, struct dc_buffer *buffer)
{

	dprintk("[%s %d]\n", __func__, __LINE__);

	if(dc_prepare_user_buffer(pdc_info, buffer))
		goto err;

	if(dc_queue_vo_buffer(pdc_info, buffer))
		goto err;

	return 0;

err:
	return -EAGAIN;
}

static int dc_wait_context_ready(DC_INFO *pdc_info, unsigned int context, unsigned int maxWaitVsync)
{
	u32 refContext = 0;
	bool recheck;
	bool overflow;

	do {
		refContext = pli_IPCReadULONG((BYTE*)&pdc_info->REF_CLK->videoContext);

		if ((refContext > (context + 1)) && (refContext != -1U))
			wprintk("refContext:%d context:%d \n", refContext, context);

		if (context > refContext && (context - refContext) > (-1U/2))
			overflow = true;
		else
			overflow = false;

		if (!overflow) {
			if (refContext >= context)
				break;
		} else {
			iprintk("refContext:%d context:%d overflow:%d\n", refContext, context, overflow);
			break;
		}

		if (pdc_info->flags & SUSPEND)
			break;

		if (dc_wait_vsync_timeout(pdc_info))
			goto err;

		if (maxWaitVsync == -1U || maxWaitVsync > 0)
			recheck = true;
		else
			recheck = false;

		if (maxWaitVsync != -1U)
			maxWaitVsync--;

	} while (recheck);

	if (!maxWaitVsync)
		goto err;

	return 0;
err:
	eprintk("[%s %d] context:%d refContext:%d waitVsyncTimes %d\n",
			__func__, __LINE__, context, refContext, 10 - maxWaitVsync);
	return -EAGAIN;
}

static int dc_vo_post(DC_INFO *pdc_info, struct dc_buffer *buf)
{
	int ret = 0;

	if (buf->id == eFrameBuffer) {
		ret = dc_queue_framebuffer(pdc_info, buf);
	} else if (buf->id == eUserBuffer) {
		ret = dc_queue_user_buffer(pdc_info, buf);
	} else if (buf->id == eFrameBufferTarget) {
		ret = dc_queue_framebuffer_target(pdc_info, buf);
	} else if (buf->id == eFrameBufferSkip) {
		dprintk("eFrameBufferSkip!");
	} else
		eprintk("buffer id (%u) is not ready!",buf->id)

	if (ret)
		goto err;

	return 0;
err:
	dc_buffer_dump(buf);
	return ret;
}

static int dc_vo_complete(DC_INFO *pdc_info, struct dc_buffer *buf)
{
	int ret = 0;

	switch (buf->id) {
		case eUserBuffer:
		case eFrameBuffer:
			{
				unsigned int maxWaitVsync = 10;
				unsigned int waitContext;
				if ((buf->context > 0) && !(pdc_info->flags & VSYNC_FORCE_LOCK))
					waitContext = buf->context - 1;
				else
					waitContext = buf->context;
				ret = dc_wait_context_ready(pdc_info, waitContext, maxWaitVsync);
				break;
			}
		case eFrameBufferTarget:
			{
				unsigned int maxWaitVsync = -1U;
				unsigned int waitContext;
				if ((buf->context > 0) && !(pdc_info->flags & VSYNC_FORCE_LOCK))
					waitContext = buf->context;
				else
					waitContext = buf->context + 1;
				ret = dc_wait_context_ready(pdc_info, waitContext, maxWaitVsync);
				break;
			}
		case eFrameBufferSkip:
			{
				dprintk("eFrameBufferSkip!");
				break;
			}
		default:
			{
				eprintk("buffer id (%u) is not ready!",buf->id);
				ret = -1;
				break;
			}
	}

	if (ret)
		goto err;

#ifdef DC2VO_SUPPORT_MEMORY_TRASH
	if (gbMemoryTrash) {
		static u32 tempContext = -1U;
		u32 errContext = pli_IPCReadULONG((BYTE*)&pdc_info->REF_CLK->memorytrashContext);
		if (errContext != -1) {
			u32 errPhyAddr = pli_IPCReadULONG((BYTE*)&pdc_info->REF_CLK->memorytrashAddr);
			wprintk("[%s] (MemoryTrash) err: %d(0x%08x) free: %d(%08x) CTX:%d\n",
					__FUNCTION__, errContext, errPhyAddr, buf->context, buf->phyAddr, pdc_info->CTX);
			pli_IPCWriteULONG((BYTE *) &pdc_info->REF_CLK->memorytrashContext, -1);
		}

		if (tempContext != -1U && buf->context != (tempContext+1))
			wprintk("[%s] tempContext:%d free: %d(%08x) CTX:%d\n",
					__FUNCTION__, tempContext, buf->context, buf->phyAddr, pdc_info->CTX);

		tempContext = buf->context;
	}
#endif /* End of DC2VO_SUPPORT_MEMORY_TRASH */

#ifdef DC2VO_SUPPORT_DCSYS_DEBUG
	dc_sys_debug_trigger();
#endif /* End of DC2VO_SUPPORT_DCSYS_DEBUG */
	return 0;
err:
	dc_buffer_dump(buf);
	return ret;
}

static void dc_post_work_func(struct kthread_work *work)
{
	DC_INFO *pdc_info =
		container_of(work, DC_INFO, post_work);
	struct dc_pending_post *post, *next;
	struct list_head saved_list;

	mutex_lock(&pdc_info->post_lock);
	memcpy(&saved_list, &pdc_info->post_list, sizeof(saved_list));
	list_replace_init(&pdc_info->post_list, &saved_list);
	mutex_unlock(&pdc_info->post_lock);

	dprintk("[%s %d]\n", __func__, __LINE__);

	list_for_each_entry_safe(post, next, &saved_list, head) {
		int i;

		for (i = 0; i < post->config.n_bufs; i++) {
			struct sync_file *fence =
				post->config.bufs[i].acquire.fence;
			if (fence)
				dc_fence_wait(pdc_info, fence);
		}

		for (i = 0; i < post->config.n_bufs; i++) {
			struct dc_buffer *buffer = &post->config.bufs[i];
			if (buffer->overlay_engine == eEngine_VO) {
				dc_vo_post(pdc_info, buffer);
			} else
				eprintk("overlay_engine (%u) is not ready!",buffer->overlay_engine)
		}

		mutex_lock(&pdc_info->complete_lock);
		INIT_LIST_HEAD(&post->head);
		list_add_tail(&post->head, &pdc_info->complete_list);
		kthread_queue_work(&pdc_info->complete_worker, &pdc_info->complete_work);
		mutex_unlock(&pdc_info->complete_lock);
	}
}

static void dc_complete_work_func(struct kthread_work *work)
{
	DC_INFO *pdc_info =
		container_of(work, DC_INFO, complete_work);
	struct dc_pending_post *post, *next;
	struct list_head saved_list;

	mutex_lock(&pdc_info->complete_lock);
	memcpy(&saved_list, &pdc_info->complete_list, sizeof(saved_list));
	list_replace_init(&pdc_info->complete_list, &saved_list);
	mutex_unlock(&pdc_info->complete_lock);

	list_for_each_entry_safe(post, next, &saved_list, head) {
		int i;
		for (i = 0; i < post->config.n_bufs; i++) {
			struct dc_buffer *buffer = &post->config.bufs[i];
			if (buffer->overlay_engine == eEngine_VO) {
				dc_vo_complete(pdc_info, buffer);
			} else
				eprintk("overlay_engine (%u) is not ready!",buffer->overlay_engine)
		}
#ifdef CREATE_THREAD_FOR_RELEASE_DEBUG
		mutex_lock(&pdc_info->free_lock);
		INIT_LIST_HEAD(&post->head);
		list_add_tail(&post->head, &pdc_info->free_list);
		kthread_queue_work(&pdc_info->free_worker, &pdc_info->free_work);
		mutex_unlock(&pdc_info->free_lock);
#else /* else of CREATE_THREAD_FOR_RELEASE_DEBUG */
		dc_sw_advance_timeline(pdc_info);
		list_del(&post->head);
		if (pdc_info->onscreen)
			dc_post_cleanup(pdc_info, pdc_info->onscreen);
		pdc_info->onscreen = post;
		//dc_post_cleanup(pdc_info, post);
#endif /* End of CREATE_THREAD_FOR_RELEASE_DEBUG */
	}
}

#ifdef CREATE_THREAD_FOR_RELEASE_DEBUG
static void dc_free_work_func(struct kthread_work *work)
{
	DC_INFO *pdc_info =
		container_of(work, DC_INFO, free_work);
	struct dc_pending_post *post, *next;
	struct list_head saved_list;

	mutex_lock(&pdc_info->free_lock);
	memcpy(&saved_list, &pdc_info->free_list, sizeof(saved_list));
	list_replace_init(&pdc_info->free_list, &saved_list);
	mutex_unlock(&pdc_info->free_lock);

	list_for_each_entry_safe(post, next, &saved_list, head) {
		//dc_wait_vsync_timeout(pdc_info);
		dc_sw_advance_timeline(pdc_info);
		list_del(&post->head);
		if (pdc_info->onscreen)
			dc_post_cleanup(pdc_info, pdc_info->onscreen);
		pdc_info->onscreen = post;
		//dc_post_cleanup(pdc_info, post);
	}
}
#endif /* End of CREATE_THREAD_FOR_RELEASE_DEBUG */

int Init_post_Worker(VENUSFB_MACH_INFO * video_info)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;

	INIT_LIST_HEAD(&pdc_info->post_list);
	INIT_LIST_HEAD(&pdc_info->complete_list);
	mutex_init(&pdc_info->post_lock);
	mutex_init(&pdc_info->complete_lock);
	kthread_init_worker(&pdc_info->post_worker);
	kthread_init_worker(&pdc_info->complete_worker);
#ifdef CREATE_THREAD_FOR_RELEASE_DEBUG
	INIT_LIST_HEAD(&pdc_info->free_list);
	mutex_init(&pdc_info->free_lock);
	kthread_init_worker(&pdc_info->free_worker);
#endif /* End of CREATE_THREAD_FOR_RELEASE_DEBUG */

	pdc_info->timeline = NULL;
	pdc_info->timeline_max = 0;

	pdc_info->post_thread = kthread_run(kthread_worker_fn,
			&pdc_info->post_worker, "rtk_post_worker");

	pdc_info->complete_thread = kthread_run(kthread_worker_fn,
			&pdc_info->complete_worker, "rtk_complete_worker");

#ifdef CREATE_THREAD_FOR_RELEASE_DEBUG
	pdc_info->free_thread = kthread_run(kthread_worker_fn,
			&pdc_info->free_worker, "rtk_complete_worker");
#endif /* End of CREATE_THREAD_FOR_RELEASE_DEBUG */

	if (IS_ERR(pdc_info->post_thread)) {
		int ret = PTR_ERR(pdc_info->post_thread);
		pdc_info->post_thread = NULL;
		pr_err("%s: failed to run config posting thread: %d\n",
				__func__, ret);
		goto err;
	}

	if (IS_ERR(pdc_info->complete_thread)) {
		int ret = PTR_ERR(pdc_info->complete_thread);
		pdc_info->complete_thread = NULL;
		pr_err("%s: failed to run config complete thread: %d\n",
				__func__, ret);
		goto err;
	}

#ifdef CREATE_THREAD_FOR_RELEASE_DEBUG
	if (IS_ERR(pdc_info->free_thread)) {
		int ret = PTR_ERR(pdc_info->free_thread);
		pdc_info->free_thread = NULL;
		pr_err("%s: failed to run config complete thread: %d\n",
				__func__, ret);
		goto err;
	}
#endif /* End of CREATE_THREAD_FOR_RELEASE_DEBUG */

	kthread_init_work(&pdc_info->post_work, dc_post_work_func);
	kthread_init_work(&pdc_info->complete_work, dc_complete_work_func);
#ifdef CREATE_THREAD_FOR_RELEASE_DEBUG
	kthread_init_work(&pdc_info->free_work, dc_free_work_func);
#endif /* End of CREATE_THREAD_FOR_RELEASE_DEBUG */

	return 0;

err:
	if (pdc_info->post_thread) {
		kthread_flush_worker(&pdc_info->post_worker);
		kthread_stop(pdc_info->post_thread);
	}

	if (pdc_info->complete_thread) {
		kthread_flush_worker(&pdc_info->complete_worker);
		kthread_stop(pdc_info->complete_thread);
	}

#ifdef CREATE_THREAD_FOR_RELEASE_DEBUG
	if (pdc_info->free_thread) {
		kthread_flush_worker(&pdc_info->free_worker);
		kthread_stop(pdc_info->free_thread);
	}
#endif /* End of CREATE_THREAD_FOR_RELEASE_DEBUG */
	return -1;
}

int DeInit_post_Worker(VENUSFB_MACH_INFO * video_info)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	if (pdc_info->post_thread) {
		kthread_flush_worker(&pdc_info->post_worker);
		kthread_stop(pdc_info->post_thread);
	}
	if (pdc_info->complete_thread) {
		kthread_flush_worker(&pdc_info->complete_worker);
		kthread_stop(pdc_info->complete_thread);
	}
#ifdef CREATE_THREAD_FOR_RELEASE_DEBUG
	if (pdc_info->free_thread) {
		kthread_flush_worker(&pdc_info->free_worker);
		kthread_stop(pdc_info->free_thread);
	}
#endif /* End of CREATE_THREAD_FOR_RELEASE_DEBUG */

	if (pdc_info->timeline)
		sync_timeline_put( (struct sync_timeline *) pdc_info->timeline);

	return 0;
}

int DC_Init(VENUSFB_MACH_INFO * video_info, struct fb_info *fbi, int irq)
{
	int retval = 0;

	pr_info("[%s] start\n", __func__);

	if (DCINIT)
		goto DONE;

	if (video_info->dc_info == NULL) {

		DC_INFO *pdc_info = NULL;
		struct rtk_ipc_shm __iomem *ipc = (void __iomem *)IPC_SHM_VIRT;
		ipc = (void __iomem *)IPC_SHM_VIRT;

		pr_info("[%s] allocate DC info buffer\n", __func__);

		video_info->dc_info = (DC_INFO *) kzalloc(sizeof(DC_INFO), GFP_KERNEL);
		pdc_info = (DC_INFO *) video_info->dc_info;

		/* DC_INFO SET DEFAULT */
		memset(video_info->dc_info, 0, sizeof(DC_INFO));

		pr_info("[%s] rpc_common_base = %p, ipc = %p\n", __func__, rpc_common_base, ipc);

		init_waitqueue_head(&pdc_info->vsync_wait);

		pdc_info->gAlpha = 0;
		pdc_info->vsync_timeout_ms = 1000;
		pdc_info->flags &= ~BG_SWAP;
		pdc_info->flags |= VSYNC_FORCE_LOCK;
		pdc_info->pfbi = fbi;
		pdc_info->vo_vsync_flag = &ipc->vo_int_sync;
		pdc_info->irq = irq;

#ifdef CONFIG_RTK_RPC
		gpdc_info = (DC_INFO*)video_info->dc_info;
#endif
	} else {
		pr_warn("[%s] allocate DC info buffer are alrealy done? (%p)\n",  __func__, video_info->dc_info);
	}

	retval = Init_post_Worker(video_info);
	if (retval)
		goto DONE;

	if (Activate_vSync(video_info)) {
		pr_err("[%s %d] error video_info = %p\n", __func__, __LINE__, video_info);
		retval = -1;
		goto DONE;
	}

	DCINIT = 1;

DONE:
	pr_info("[%s] done\n", __func__);

	return retval;
}

void DC_Deinit(VENUSFB_MACH_INFO * video_info)
{
	iprintk("[%s %d]\n",__func__,__LINE__);
	DeInit_post_Worker(video_info);
	DeInit_vSync(video_info);
	if (video_info->dc_info != NULL) {
#if 1
		iprintk("[%s %d] NOT TO FREE DC INFO BUFFER!",__func__,__LINE__);
#else
		kfree(video_info->dc_info);
		video_info->dc_info = NULL;
#endif
	} else {
		wprintk("[%s %d] video_info->dc_info == NULL \n",__func__,__LINE__);
	}
	DCINIT = 0;
}

int DC_Suspend (VENUSFB_MACH_INFO * video_info)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	pdc_info->flags |= SUSPEND;
	kthread_flush_worker(&pdc_info->post_worker);
	//kthread_flush_worker(&pdc_info->complete_worker);

	/* Disable the interrup */
	DC_RESET_BIT(pdc_info->vo_vsync_flag, DC_VO_SET_NOTIFY);

	msleep(5);
	return 0;
}

int DC_Resume (VENUSFB_MACH_INFO * video_info)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	DC_SET_BIT(pdc_info->vo_vsync_flag, DC_VO_SET_NOTIFY);
	smp_mb();
	pdc_info->flags		 &= ~SUSPEND;
	smp_mb();
	return 0;
}

#ifdef CONFIG_REALTEK_AVCPU
int DC_avcpu_event_notify(unsigned long action, VENUSFB_MACH_INFO * video_info)
{
	DC_INFO * pdc_info = (DC_INFO*)video_info->dc_info;
	switch (action) {
		case AVCPU_RESET_PREPARE:
			smp_mb();
			pdc_info->flags &= ~RPC_READY;
			smp_mb();
			DC_RESET_BIT(pdc_info->vo_vsync_flag, DC_VO_SET_NOTIFY);
			break;
		case AVCPU_RESET_DONE:
			DC_SET_BIT(pdc_info->vo_vsync_flag, DC_VO_SET_NOTIFY);
			break;
		case AVCPU_SUSPEND:
		case AVCPU_RESUME:
			break;
		default:
			break;
	}
	return 0;
}
#endif

#ifdef DC2VO_SUPPORT_DCSYS_DEBUG
static inline void dc_sys_debug_trigger(void) {
	if (gsDcSysDebugThread != NULL)
		kthread_queue_work(&gsDcSysDebugWorker, &gsDcSysDebugWork);
}

static void dc_sys_debug_work_func(struct kthread_work *work)
{
	if (gpDcSysControl == NULL)
		return;

	if (readl(gpDcSysControl) & DC2VO_DCSYS_CONTROL_ERROR)
		gbDcSysError = true;

	if (gbDcSysError)
		eprintk("[%s] dc_sys_debug(0x%08x) = 0x%08x\n", __FUNCTION__,
				DC2VO_DCSYS_CONTROL, readl(gpDcSysControl));
}

static int __init dc2vo_dcsys_debug_init(void)
{
	if (gpDcSysControl == NULL)
		gpDcSysControl = ioremap(DC2VO_DCSYS_CONTROL, 0x4);

	if (gpDcSysControl == NULL)
		return -ENOMEM;

	gbDcSysError = false;

	writel((readl(gpDcSysControl) | DC2VO_DCSYS_CONTROL_SETUP) & ~DC2VO_DCSYS_CONTROL_ERROR, gpDcSysControl);

	kthread_init_worker(&gsDcSysDebugWorker);

	gsDcSysDebugThread = kthread_run(kthread_worker_fn,
			&gsDcSysDebugWorker, "dc_sys_debug_worker");

	kthread_init_work(&gsDcSysDebugWork, dc_sys_debug_work_func);
	return 0;
}

module_init(dc2vo_dcsys_debug_init)
#endif /* End of DC2VO_SUPPORT_DCSYS_DEBUG */

#ifdef CONFIG_SYSFS

#define DC2VO_ATTR(_name)				   \
{										   \
	.attr = {.name = #_name, .mode = 0644}, \
	.show =  dc2vo_##_name##_show,	\
	.store = dc2vo_##_name##_store,   \
}

#ifdef DC2VO_SUPPORT_MEMORY_TRASH
static ssize_t dc2vo_memory_trash_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	int n = 0;
	n += sprintf(buf+n,			 "MemoryTrashEn  : %d\n", gbMemoryTrash);
	return n;
}

static ssize_t dc2vo_memory_trash_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	long val;
	int ret = kstrtol(buf, 10, &val);
	if (ret < 0)
		return -ENOMEM;
	gbMemoryTrash = (val == 0)?false:true;
	return count;
}

static struct kobj_attribute dc2vo_memory_trash_attr = DC2VO_ATTR(memory_trash);
#endif /* End of DC2VO_SUPPORT_MEMORY_TRASH */

#ifdef DC2VO_SUPPORT_DCSYS_DEBUG
static ssize_t dc2vo_dcsys_debug_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	int n = 0;
	n += sprintf(buf+n,			 "DcSysError	 : %d\n", gbDcSysError);
	if (gpDcSysControl != NULL)
		n += sprintf(buf+n,		 "DcSysControl   : 0x%08x\n", readl(gpDcSysControl));
	return n;
}

static ssize_t dc2vo_dcsys_debug_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	long val;
	int ret = kstrtol(buf, 10, &val);
	if (ret < 0)
		return -ENOMEM;
	if (ret == 0) {
		if (gpDcSysControl != NULL && gbDcSysError)
			writel(readl(gpDcSysControl) & ~DC2VO_DCSYS_CONTROL_ERROR, gpDcSysControl);
		gbDcSysError = false;
	}
	return count;
}

static struct kobj_attribute dc2vo_dcsys_debug_attr = DC2VO_ATTR(dcsys_debug);
#endif /* End of DC2VO_SUPPORT_DCSYS_DEBUG */

static struct attribute *dc2vo_attrs[] = {
#ifdef DC2VO_SUPPORT_MEMORY_TRASH
	&dc2vo_memory_trash_attr.attr,
#endif /* End of DC2VO_SUPPORT_MEMORY_TRASH */
#ifdef DC2VO_SUPPORT_DCSYS_DEBUG
	&dc2vo_dcsys_debug_attr.attr,
#endif /* End of DC2VO_SUPPORT_DCSYS_DEBUG */
	NULL,
};

static struct attribute_group dc2vo_attr_group = {
	.attrs = dc2vo_attrs,
};

static struct kobject *dc2vo_kobj;

static int __init dc2vo_sysfs_init(void)
{
	int ret;

	dc2vo_kobj = kobject_create_and_add("display", kernel_kobj);
	if (!dc2vo_kobj)
		return -ENOMEM;
	ret = sysfs_create_group(dc2vo_kobj, &dc2vo_attr_group);
	if (ret)
		kobject_put(dc2vo_kobj);
	return ret;
}

module_init(dc2vo_sysfs_init)
#endif /* End of CONFIG_SYSFS */
