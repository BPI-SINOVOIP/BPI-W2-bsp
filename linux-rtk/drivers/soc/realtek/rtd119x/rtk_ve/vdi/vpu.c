
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/wait.h>
#include <linux/list.h>
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/cdev.h> 
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/export.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include "vpuconfig.h"

#include "vpu.h"
#include "../puwrap.h"

#ifdef CONFIG_RTK_RESERVE_MEMORY
extern unsigned int pu_alloc_dma_buffer(unsigned int size, unsigned long long *phys_addr, unsigned long *base);
extern void pu_free_dma_buffer(unsigned long base, unsigned long long phys_addr);
#endif
extern void *pu_get_drv_context(void);

// definitions to be changed as customer  configuration
#define VPU_HACK_CLOCK_CONTROL
//#define VPU_SUPPORT_CLOCK_CONTROL				//if you want to have clock gating scheme frame by frame
//#define VPU_SUPPORT_ISR						//if the driver want to use interrupt service from kernel ISR //Fuchun 20131112 disabled, move to puwrap.c
//#define VPU_SUPPORT_PLATFORM_DRIVER_REGISTER	//if the platform driver knows the name of this driver. VPU_PLATFORM_DEVICE_NAME 
//#define VPU_SUPPORT_RESERVED_VIDEO_MEMORY		//if this driver knows the dedicated video memory address 

#define VPU_PLATFORM_DEVICE_NAME "rtk_vpu"
#define VPU_CLK_NAME "vpu_clk"
#define VPU_DEV_NAME "vpu"

// if the platform driver knows this driver. the definition of VPU_REG_BASE_ADDR and VPU_REG_SIZE are not meaningful
#define VPU_REG_BASE_ADDR 0x18040000
#define VPU_REG_SIZE 0x4000*3//(0x4000*MAX_NUM_VPU_CORE) //Fuchun 20131101, because coda855j's registers between coda980 and wave410

#define VPU_VIRT_ADDR_MAP(addr)	(RBUS_BASE_VIRT + ((u32)addr - RBUS_BASE_PHYS))
#define VPU_WRITE_REG_INT32U(addr,val)	writel(val, IOMEM(VPU_VIRT_ADDR_MAP(addr)))

#define VPU_CLOCK_REG_BASE		0x18000000
#define VPU_CLOCK_ENABLE_REG		0x1800000c
#define VPU_CLOCK_PLL_REG		0x18000114
#define VPU_CLOCK_PLL2_REG		0x18000118
#define VPU_BONDING_REG		0x18007028

//#ifdef VPU_SUPPORT_ISR
#define VPU_IRQ_NUM 83//(23+32)
//#endif


#ifndef VM_RESERVED
#define VM_RESERVED (VM_DONTEXPAND | VM_DONTDUMP)
#endif

typedef struct vpu_drv_context_t {
	struct fasync_struct *async_queue;
	unsigned long interrupt_reason;
} vpu_drv_context_t;

/* To track the allocated memory buffer */
typedef struct vpudrv_buffer_pool_t {
	struct list_head list;
	struct vpudrv_buffer_t vb;
	struct file *filp;
} vpudrv_buffer_pool_t;

/* To track the instance index and buffer in instance pool */
typedef struct vpudrv_instanace_list_t {
	struct list_head list;
	unsigned long inst_idx;
	unsigned long core_idx;
	struct file *filp;
} vpudrv_instanace_list_t;

typedef struct vpudrv_instance_pool_t {
	unsigned char codecInstPool[MAX_NUM_INSTANCE][MAX_INST_HANDLE_SIZE];
	void*         pendingInst;
	int           pendingInstIdxPlus1;
} vpudrv_instance_pool_t;

#ifdef VPU_SUPPORT_RESERVED_VIDEO_MEMORY
#define VPU_INIT_VIDEO_MEMORY_SIZE_IN_BYTE (16*1024*1024)//(62*1024*1024)
#define VPU_DRAM_PHYSICAL_BASE 0x06000000//0x86C00000
#include "vmm.h"
static video_mm_t s_vmem;	
static vpudrv_buffer_t s_video_memory = {0};
#endif //VPU_SUPPORT_RESERVED_VIDEO_MEMORY


static int vpu_hw_reset(u32 coreIdx);
static void vpu_clk_disable(struct clk *clk);
static int vpu_clk_enable(struct clk *clk);
static struct clk *vpu_clk_get(struct device *dev, int coreIdx);
static void vpu_clk_put(struct clk *clk);
#ifdef CONFIG_PM
static int vpu_suspend(struct platform_device *pdev, pm_message_t state);
static int vpu_resume(struct platform_device *pdev);
#endif
// end customer definition
static vpudrv_buffer_t s_instance_pool = {0};
static vpudrv_buffer_t s_common_memory = {0};
static vpu_drv_context_t s_vpu_drv_context;
#if 0
static int s_vpu_major;
static struct class *s_vpu_class = NULL;
static struct device *s_vpu_dev = NULL;
static struct cdev s_vpu_cdev;
#else
static struct miscdevice s_vpu_dev;
#endif
static int s_vpu_open_ref_count;
static int s_vpu_fourk_info_value = 0;
static int s_vpu_fourk_info_instidx_plus1 = 0;
static int s_vpu_fourk_info_coreidx = 0;
static int s_vpu_fourk_info_enable[MAX_NUM_VPU_CORE][MAX_NUM_INSTANCE] = {0};
static struct clk *s_vpu_clk_980;
static struct clk *s_vpu_clk_410;
static struct clk *s_vpu_clk_vpll;
//#ifdef VPU_SUPPORT_ISR
static int s_vpu_irq = VPU_IRQ_NUM;
//#endif
static u32 s_vpu_reg_phy_addr = VPU_REG_BASE_ADDR;
static void __iomem *s_vpu_reg_virt_addr;

static atomic_t s_interrupt_flag;
static wait_queue_head_t s_interrupt_wait_q;

static spinlock_t s_vpu_lock = __SPIN_LOCK_UNLOCKED(s_vpu_lock);
static DEFINE_SEMAPHORE(s_vpu_sem);
static struct list_head s_vbp_head = LIST_HEAD_INIT(s_vbp_head);
static struct list_head s_inst_list_head = LIST_HEAD_INIT(s_inst_list_head);


static vpu_bit_firmware_info_t s_bit_firmware_info[MAX_NUM_VPU_CORE];

#ifdef CONFIG_PM
/* implement to power management functions */
#define BIT_BASE				0x0000
#define BIT_CODE_RUN		(BIT_BASE + 0x000)
#define BIT_CODE_DOWN		(BIT_BASE + 0x004)
#define BIT_INT_CLEAR		(BIT_BASE + 0x00C)
#define BIT_INT_STS			(BIT_BASE + 0x010)
#define BIT_CODE_RESET		(BIT_BASE + 0x014)
#define BIT_INT_REASON		(BIT_BASE + 0x174)
#define BIT_BUSY_FLAG		(BIT_BASE + 0x160)
#define BIT_RUN_COMMAND	(BIT_BASE + 0x164)
#define BIT_RUN_INDEX		(BIT_BASE + 0x168)
#define BIT_RUN_COD_STD	(BIT_BASE + 0x16C)

/* WAVE4 registers */
#define W4_REG_BASE				0x0000
#define W4_VPU_INT_REASON_CLEAR	(W4_REG_BASE + 0x0034)
#define W4_VPU_INT_CLEAR			(W4_REG_BASE + 0x003C)
#define W4_VPU_INT_STS				(W4_REG_BASE + 0x0044)
#define W4_VPU_INT_REASON			(W4_REG_BASE + 0x004c)

#define W4_RET_SUCCESS				(W4_REG_BASE + 0x0110)
#define W4_RET_FAIL_REASON		(W4_REG_BASE + 0x0114)

/* WAVE4 INIT, WAKEUP */
#define W4_PO_CONF					(W4_REG_BASE + 0x0000)
#define W4_VCPU_CUR_PC				(W4_REG_BASE + 0x0004)

#define W4_VPU_INT_ENABLE			(W4_REG_BASE + 0x0048)

#define W4_RESET_REQ				(W4_REG_BASE + 0x0050)
#define W4_RESET_STATUS			(W4_REG_BASE + 0x0054)

#define W4_VPU_REMAP_CTRL			(W4_REG_BASE + 0x0060)
#define W4_VPU_REMAP_VADDR		(W4_REG_BASE + 0x0064)
#define W4_VPU_REMAP_PADDR		(W4_REG_BASE + 0x0068)
#define W4_VPU_REMAP_PROC_START	(W4_REG_BASE + 0x006C)
#define W4_VPU_BUSY_STATUS		(W4_REG_BASE + 0x0070)

#define W4_REMAP_CODE_INDEX             0
enum {
    W4_INT_INIT_VPU          = 0,
    W4_INT_DEC_PIC_HDR       = 1,
    W4_INT_FINI_SEQ          = 2,
    W4_INT_DEC_PIC           = 3,
    W4_INT_SET_FRAMEBUF      = 4,
    W4_INT_FLUSH_DEC         = 5,
    W4_INT_GET_FW_VERSION    = 9,
    W4_INT_QUERY_DEC         = 10,
    W4_INT_SLEEP_VPU         = 11,
    W4_INT_WAKEUP_VPU        = 12,
    W4_INT_CHANGE_INT        = 13,       
    W4_INT_CREATE_INSTANCE   = 14, 
    W4_INT_BSBUF_EMPTY       = 15,   /*!<< Bitstream buffer empty */
};

#define W4_HW_OPTION				(W4_REG_BASE + 0x0124)
#define W4_CODE_SIZE				(W4_REG_BASE + 0x011C)
/* Note: W4_INIT_CODE_BASE_ADDR should be aligned to 4KB */
#define W4_ADDR_CODE_BASE			(W4_REG_BASE + 0x0118)
#define W4_CODE_PARAM				(W4_REG_BASE + 0x0120)
/* Note: W4_INIT_STACK_BASE_ADDR should be aligned to 4KB */
#define W4_ADDR_STACK_BASE		(W4_REG_BASE + 0x012C)
#define W4_STACK_SIZE				(W4_REG_BASE + 0x0130)
#define W4_INIT_VPU_TIME_OUT_CNT	(W4_REG_BASE + 0x0134)

/* WAVE4 Wave4BitIssueCommand */
#define W4_CORE_INDEX				(W4_REG_BASE + 0x0104)
#define W4_INST_INDEX				(W4_REG_BASE + 0x0108)
#define W4_COMMAND				(W4_REG_BASE + 0x0100)
#define W4_VPU_HOST_INT_REQ		(W4_REG_BASE + 0x0038)

/* Product register */
#define VPU_PRODUCT_CODE_REGISTER	(BIT_BASE + 0x1044)


static u32	s_vpu_reg_store[MAX_NUM_VPU_CORE][64];
#if defined(CODA7L) || defined(CODA851)
static u32 s_run_index;
static u32 s_run_codstd;
#endif
#endif

//------------------------------------------------------------------------------
// common struct and definition
//------------------------------------------------------------------------------
typedef enum {
    STD_AVC,
    STD_VC1,
    STD_MPEG2,
    STD_MPEG4,
    STD_H263,
    STD_DIV3,
    STD_RV,
    STD_AVS,
    STD_THO = 9,
    STD_VP3,
    STD_VP8,
    STD_HEVC,
    STD_MAX
} CodStd;

#define ENABLE_RM		(1 << 7)
#define ENABLE_DIVX	(1 << 6)
#define DISABLE_265	(1 << 5)

static u32 support_codec_types = (1<<STD_AVC) | (1<<STD_VC1) | (1<<STD_MPEG2) | (1<<STD_MPEG4) | (1<<STD_H263) | (1<<STD_AVS) | (1<<STD_THO) | (1<<STD_VP8);


#define ReadVpuRegister(addr, core)		*(volatile unsigned int *)(s_vpu_reg_virt_addr + s_bit_firmware_info[core].reg_base_offset + addr)
#define WriteVpuRegister(addr, val, core)	*(volatile unsigned int *)(s_vpu_reg_virt_addr + s_bit_firmware_info[core].reg_base_offset + addr) = (unsigned int)val;
#define WriteVpu(addr, val)				*(volatile unsigned int *)(addr) = (unsigned int)val;


static int vpu_alloc_dma_buffer(vpudrv_buffer_t *vb)
{
	unsigned int ret;
	if (!vb)
		return -1;
	
#ifdef VPU_SUPPORT_RESERVED_VIDEO_MEMORY
	vb->phys_addr = (unsigned long long)vmem_alloc(&s_vmem, vb->size, 0);
	if ((unsigned long)vb->phys_addr  == (unsigned long)-1)
	{
		printk(KERN_ERR "[VPUDRV] Physical memory allocation error size=%d\n", vb->size);
		return -1;
	}

	vb->base = (unsigned long)(s_video_memory.base + (vb->phys_addr - s_video_memory.phys_addr));
#elif CONFIG_RTK_RESERVE_MEMORY
	ret = pu_alloc_dma_buffer(vb->size, &vb->phys_addr, &vb->base);
	if(ret == -1)
	{
		printk(KERN_ERR "[VPUDRV] Physical memory allocation error size=%d\n", vb->size);
		return -1;
	}
#else
	vb->base = (unsigned long)dma_alloc_coherent(NULL, PAGE_ALIGN(vb->size), (dma_addr_t *) (&vb->phys_addr), GFP_DMA | GFP_KERNEL);
	if ((void *)(vb->base) == NULL) 
	{
		printk(KERN_ERR "[VPUDRV] Physical memory allocation error size=%d\n", vb->size);
		return -1;
	}
#endif
	printk("[VPUDRV] base:0x%x, phy_addr:0x%x, size:%d\n", vb->base, (unsigned long)vb->phys_addr, vb->size);
	return 0;
}

static void vpu_free_dma_buffer(vpudrv_buffer_t *vb)
{
	if (!vb)
		return;

#ifdef VPU_SUPPORT_RESERVED_VIDEO_MEMORY
	if (vb->base) 
		vmem_free(&s_vmem, vb->phys_addr, 0);
#elif CONFIG_RTK_RESERVE_MEMORY
	pu_free_dma_buffer(vb->base, vb->phys_addr);
#else
	if (vb->base) 
		dma_free_coherent(0, PAGE_ALIGN(vb->size), (void *)vb->base, vb->phys_addr);
#endif
}

static int vpu_free_instances(struct file *filp) 
{
	vpudrv_instanace_list_t *vil, *n;
	vpudrv_instance_pool_t *vip;
	int instance_pool_size_per_core;

	printk("[VPUDRV] vpu_free_instances\n");

	instance_pool_size_per_core = (s_instance_pool.size/MAX_NUM_VPU_CORE); // s_instance_pool.size  assigned to the size of all core once call VDI_IOCTL_GET_INSTANCE_POOL by user.

	list_for_each_entry_safe(vil, n, &s_inst_list_head, list) 
	{
		if (vil->filp == filp)
		{
			vip = (vpudrv_instance_pool_t *)(s_instance_pool.base + (instance_pool_size_per_core*vil->core_idx));
			if (vip)
			{
				if (vil->inst_idx == (vip->pendingInstIdxPlus1-1) && vip->pendingInst != 0)
				{
					printk(KERN_WARNING "[VPUDRV] vil->inst_idx:%d, vil->core_idx:%d is pending, clear in here\n", vil->inst_idx, vil->core_idx);
					vip->pendingInst = 0;
					vip->pendingInstIdxPlus1 = 0;
				}
				memset(&vip->codecInstPool[vil->inst_idx], 0x00, 4);	// only first 4 byte is key point to free the corresponding instance.

				if (vil->inst_idx == (s_vpu_fourk_info_instidx_plus1-1) && s_vpu_fourk_info_value == 1)
				{
					s_vpu_fourk_info_value = 0;
					s_vpu_fourk_info_instidx_plus1 = 0;
					s_vpu_fourk_info_coreidx = 0;
				}
			}
			s_vpu_open_ref_count--;
			s_vpu_fourk_info_enable[vil->core_idx][vil->inst_idx] = 0;
			list_del(&vil->list);
			kfree(vil);		
		}
	}

	return 1;
}

static int vpu_free_buffers(struct file *filp)
{
	vpudrv_buffer_pool_t *pool, *n;
	vpudrv_buffer_t vb;

	printk(KERN_INFO "[VPUDRV] vpu_free_buffers\n");

	list_for_each_entry_safe(pool, n, &s_vbp_head, list) 
	{
		if (pool->filp == filp)
		{
			vb = pool->vb;
			if (vb.base) 
			{
				vpu_free_dma_buffer(&vb);
				list_del(&pool->list);
				kfree(pool);
			}
		}
		
	}

	return 0;
}

void vpu_irq_handler2(int core_num, void *dev_id)
{
	//printk(KERN_INFO "[VPUDRV] vpu_irq_handler2, core_num:%d\n", core_num);
	pu_drv_context_t *dev = (pu_drv_context_t *)dev_id;

	if (s_bit_firmware_info[core_num].size == 0) // it means that we didn't get an information the current core from API layer. No core activated.
		return;

	//printk("BIT_INT_STS:0x%08x, WAVE4_VPU_INT_STS:0x%08x\n", ReadVpuRegister(BIT_INT_STS, 0), ReadVpuRegister(WAVE4_VPU_INT_STS, 1));

	if(core_num == 0 && ReadVpuRegister(BIT_INT_STS, core_num))
	{
		dev->vpu_interrupt_reason = ReadVpuRegister(BIT_INT_REASON, core_num);
		//printk("@@ In[%s][%d]  reason:%d @@\n", __func__, __LINE__, dev->vpu_interrupt_reason);
		WriteVpuRegister(BIT_INT_REASON, 0, core_num);
		WriteVpuRegister(BIT_INT_CLEAR, 0x1, core_num); 
	}
	else if(core_num == 1 && ReadVpuRegister(W4_VPU_INT_STS, core_num))
	{
		dev->vpu_interrupt_reason = ReadVpuRegister(W4_VPU_INT_REASON, core_num);
		//printk("@@ In[%s][%d]  reason:%d @@\n", __func__, __LINE__, dev->vpu_interrupt_reason);
		WriteVpuRegister(W4_VPU_INT_REASON_CLEAR, dev->vpu_interrupt_reason, core_num);
		WriteVpuRegister(W4_VPU_INT_CLEAR, 0x1, core_num);
	}

	atomic_set(&s_interrupt_flag, 1);
	wake_up_interruptible(&s_interrupt_wait_q);
}

#ifdef VPU_SUPPORT_ISR
static irqreturn_t vpu_irq_handler(int irq, void *dev_id)
{
	vpu_drv_context_t *dev = (vpu_drv_context_t *)dev_id;

	// this can be removed. it also work in VPU_WaitInterrupt of API function
	int core;
	int product_code;

	printk(KERN_INFO "[VPUDRV] vpu_irq_handler\n");	

	for (core=0; core<MAX_NUM_VPU_CORE; core++)
	{
		if (s_bit_firmware_info[core].size == 0) // it means that we didn't get an information the current core from API layer. No core activated.
			continue;
		product_code = ReadVpuRegister(VPU_PRODUCT_CODE_REGISTER, core);
		if (product_code == WAVE410_CODE) {
			if (ReadVpuRegister(W4_VPU_INT_STS, 1)) {
				WriteVpuRegister(W4_VPU_INT_CLEAR, 0x1, 1);
			}
		}
		else {
			if (ReadVpuRegister(BIT_INT_STS, 0)) {
				WriteVpuRegister(BIT_INT_CLEAR, 0x1, 0); 
			}
		}
	}
	
	if (dev->async_queue)
		kill_fasync(&dev->async_queue, SIGIO, POLL_IN);	// notify the interrupt to user space
	
	atomic_set(&s_interrupt_flag, 1);
	wake_up_interruptible(&s_interrupt_wait_q);
	return IRQ_HANDLED;
}
#endif

static int vpu_open(struct inode *inode, struct file *filp)
{
	spin_lock(&s_vpu_lock);
#ifdef VPU_SUPPORT_ISR
	filp->private_data = (void *)(&s_vpu_drv_context);
#else
	void *drv_context = pu_get_drv_context();
	filp->private_data = (void *)(drv_context);
#endif
	spin_unlock(&s_vpu_lock);
	return 0;
}

//static int vpu_ioctl(struct inode *inode, struct file *filp, u_int cmd, u_long arg) // for kernel 2.6.9 of C&M
static long vpu_ioctl(struct file *filp, u_int cmd, u_long arg)
{
	int ret = 0; 
	struct pu_drv_context_t *dev = (struct pu_drv_context_t *)filp->private_data;

	switch (cmd) 
	{
	case VDI_IOCTL_ALLOCATE_PHYSICAL_MEMORY:
		{
			vpudrv_buffer_pool_t *vbp;

			down(&s_vpu_sem);

			vbp = kzalloc(sizeof(*vbp), GFP_KERNEL);
			if (!vbp)
			{
				up(&s_vpu_sem);
				return -ENOMEM;
			}

			ret = copy_from_user(&(vbp->vb), (vpudrv_buffer_t *)arg, sizeof(vpudrv_buffer_t));
			if (ret) 
			{
				kfree(vbp);
				up(&s_vpu_sem);
				return -EFAULT;
			}

			ret = vpu_alloc_dma_buffer(&(vbp->vb));
			if (ret == -1) 
			{
				ret = -ENOMEM;
				kfree(vbp);
				up(&s_vpu_sem);
				break;
			}			
			ret = copy_to_user((void __user *)arg, &(vbp->vb), sizeof(vpudrv_buffer_t));
			if (ret) 
			{
				kfree(vbp);
				ret = -EFAULT;
				up(&s_vpu_sem);
				break;
			}

			vbp->filp = filp;
			spin_lock(&s_vpu_lock);
			list_add(&vbp->list, &s_vbp_head);
			spin_unlock(&s_vpu_lock);		

			up(&s_vpu_sem);
		}
		break;
	case VDI_IOCTL_FREE_PHYSICALMEMORY:
		{

			vpudrv_buffer_pool_t *vbp, *n;
			vpudrv_buffer_t vb;

			down(&s_vpu_sem);

			ret = copy_from_user(&vb, (vpudrv_buffer_t *)arg, sizeof(vpudrv_buffer_t));
			if (ret)
			{
				up(&s_vpu_sem);
				return -EACCES;
			}

			if (vb.base) 
				vpu_free_dma_buffer(&vb);

			spin_lock(&s_vpu_lock);
			list_for_each_entry_safe(vbp, n, &s_vbp_head, list) 
			{
				if (vbp->vb.base == vb.base) 
				{
					list_del(&vbp->list);
					kfree(vbp);
					break;
				}
			}
			spin_unlock(&s_vpu_lock);

			up(&s_vpu_sem);

		}
		break;
	case VDI_IOCTL_GET_RESERVED_VIDEO_MEMORY_INFO:
		{
#ifdef VPU_SUPPORT_RESERVED_VIDEO_MEMORY
			if (s_video_memory.base != 0) 
			{
				ret = copy_to_user((void __user *)arg, &s_video_memory, sizeof(vpudrv_buffer_t));
				if (ret != 0) 
					ret = -EFAULT;
			} 
			else
			{
				ret = -EFAULT;
			}
#endif
		}
		break;
	case VDI_IOCTL_WAIT_INTERRUPT:
		{
			vpudrv_intr_info_t info;

			//printk("[VPUDRV] ioctl VDI_IOCTL_WAIT_INTERRUPT\n");
			ret = copy_from_user(&info, (vpudrv_intr_info_t*)arg, sizeof(vpudrv_intr_info_t));
			if (ret != 0)
				return -EFAULT;

			smp_rmb();
			ret = wait_event_interruptible_timeout(s_interrupt_wait_q, atomic_read(&s_interrupt_flag) != 0, msecs_to_jiffies(info.timeout));
			if (!ret)
			{
				ret = -ETIME;
				//printk("[VPUDRV] ioctl VDI_IOCTL_WAIT_INTERRUPT fail\n");
				break;
			}
			//printk("[VPUDRV] ioctl VDI_IOCTL_WAIT_INTERRUPT success\n");

			if (signal_pending(current))
			{
				ret = -ERESTARTSYS;
				break;
			}

			atomic_set(&s_interrupt_flag, 0);
			info.intr_reason = dev->vpu_interrupt_reason;
			ret = copy_to_user((void __user *)arg, &info, sizeof(vpudrv_intr_info_t));
			if (ret != 0)
				return -EFAULT;
		}
		break;
	case VDI_IOCTL_ENABLE_INTERRUPT:
		{
			enable_irq(s_vpu_irq);
		}
		break;
	case VDI_IOCTL_SET_CLOCK_GATE:
		{
			u32 clkgate;

			if (get_user(clkgate, (u32 __user *) arg))
				return -EFAULT;
#ifdef VPU_SUPPORT_CLOCK_CONTROL
			if (clkgate)
				vpu_clk_enable(s_vpu_clk);
			else
				vpu_clk_disable(s_vpu_clk);
#endif
		}
		break;
	case VDI_IOCTL_GET_INSTANCE_POOL:
		{
			down(&s_vpu_sem);

			if (s_instance_pool.base != 0) 
			{
				ret = copy_to_user((void __user *)arg, &s_instance_pool, sizeof(vpudrv_buffer_t));
				if (ret != 0) 
					ret = -EFAULT;
			} 
			else
			{
				ret = copy_from_user(&s_instance_pool, (vpudrv_buffer_t *)arg, sizeof(vpudrv_buffer_t));
				if (ret == 0)
				{
					if (vpu_alloc_dma_buffer(&s_instance_pool) != -1)
					{
						memset((void *)s_instance_pool.base, 0x0, s_instance_pool.size); // clearing memory.
						ret = copy_to_user((void __user *)arg, &s_instance_pool, sizeof(vpudrv_buffer_t));
						if (ret == 0)
						{
							// success to get memory for instance pool
							up(&s_vpu_sem);
							break;
						}
					}
				
				}
				ret = -EFAULT;
			}
			
			up(&s_vpu_sem);
		
		}
		break;
	case VDI_IOCTL_GET_COMMON_MEMORY:
		{
			if (s_common_memory.base != 0) 
			{
				ret = copy_to_user((void __user *)arg, &s_common_memory, sizeof(vpudrv_buffer_t));
				if (ret != 0) 
					ret = -EFAULT;
			} 
			else
			{
				ret = copy_from_user(&s_common_memory, (vpudrv_buffer_t *)arg, sizeof(vpudrv_buffer_t));
				if (ret == 0)
				{
					if (vpu_alloc_dma_buffer(&s_common_memory) != -1)
					{
						ret = copy_to_user((void __user *)arg, &s_common_memory, sizeof(vpudrv_buffer_t));
						if (ret == 0)
						{
							// success to get memory for common memory
							break;
						}
					}	
				}

				ret = -EFAULT;
			}

		}
		break;
	case VDI_IOCTL_OPEN_INSTANCE:
		{
			vpudrv_inst_info_t inst_info;
			vpudrv_instanace_list_t *vil, *n;

			vil = kzalloc(sizeof(*vil), GFP_KERNEL);
			if (!vil)
				return -ENOMEM;

			if (copy_from_user(&inst_info, (vpudrv_inst_info_t *)arg, sizeof(vpudrv_inst_info_t)))
			{
				kfree(vil);
				return -EFAULT;
			}

			vil->inst_idx = inst_info.inst_idx;
			vil->core_idx = inst_info.core_idx;
			vil->filp = filp;
			spin_lock(&s_vpu_lock);
			list_add(&vil->list, &s_inst_list_head);

			inst_info.inst_open_count = 0; // counting the current open instance number
			list_for_each_entry_safe(vil, n, &s_inst_list_head, list) 
			{
				if (vil->core_idx == inst_info.core_idx)
					inst_info.inst_open_count++;
			}
			spin_unlock(&s_vpu_lock);			

			s_vpu_open_ref_count++; //flag just for that vpu is in opened or closed

			if (copy_to_user((void __user *)arg, &inst_info, sizeof(vpudrv_inst_info_t)))
				return -EFAULT;

			printk("[VPUDRV] VDI_IOCTL_OPEN_INSTANCE core_idx=%d, inst_idx=%d, s_vpu_open_ref_count=%d, inst_open_count=%d\n", (int)inst_info.core_idx, (int)inst_info.inst_idx, s_vpu_open_ref_count, inst_info.inst_open_count);
		}
		break;
	case VDI_IOCTL_CLOSE_INSTANCE:
		{
			vpudrv_inst_info_t inst_info;
			vpudrv_instanace_list_t *vil, *n;

			if (copy_from_user(&inst_info, (vpudrv_inst_info_t *)arg, sizeof(vpudrv_inst_info_t)))
				return -EFAULT;

			spin_lock(&s_vpu_lock);

			list_for_each_entry_safe(vil, n, &s_inst_list_head, list) 
			{
				if (vil->inst_idx == inst_info.inst_idx && vil->core_idx == inst_info.core_idx)
				{
					list_del(&vil->list);
					kfree(vil);
					break;
				}
			}

			inst_info.inst_open_count = 0; // counting the current open instance number
			list_for_each_entry_safe(vil, n, &s_inst_list_head, list) 
			{
				if (vil->core_idx == inst_info.core_idx)
					inst_info.inst_open_count++;
			}
			spin_unlock(&s_vpu_lock);
			
			s_vpu_open_ref_count--; // flag just for that vpu is in opened or closed

			if (copy_to_user((void __user *)arg, &inst_info, sizeof(vpudrv_inst_info_t)))
				return -EFAULT;

			printk("[VPUDRV] VDI_IOCTL_CLOSE_INSTANCE core_idx=%d, inst_idx=%d, s_vpu_open_ref_count=%d, inst_open_count=%d\n", (int)inst_info.core_idx, (int)inst_info.inst_idx, s_vpu_open_ref_count, inst_info.inst_open_count);
		}
		break;
	case VDI_IOCTL_GET_INSTANCE_NUM:
		{
			vpudrv_inst_info_t inst_info;
			vpudrv_instanace_list_t *vil, *n;
			
			ret = copy_from_user(&inst_info, (vpudrv_inst_info_t *)arg, sizeof(vpudrv_inst_info_t));
			if (ret != 0) 
				break;

			inst_info.inst_open_count = 0;

			spin_lock(&s_vpu_lock);
			list_for_each_entry_safe(vil, n, &s_inst_list_head, list) 
			{
				if (vil->core_idx == inst_info.core_idx)
					inst_info.inst_open_count++;					
			}
			spin_unlock(&s_vpu_lock);		
			
			ret = copy_to_user((void __user *)arg, &inst_info, sizeof(vpudrv_inst_info_t));

			printk("[VPUDRV] VDI_IOCTL_GET_INSTANCE_NUM core_idx=%d, inst_idx=%d, open_count=%d\n", (int)inst_info.core_idx, (int)inst_info.inst_idx, inst_info.inst_open_count);

		}
		break;
	case VDI_IOCTL_RESET:
		{
			u32 coreIdx;
			if (get_user(coreIdx, (u32 __user *) arg))
				return -EFAULT;
			vpu_hw_reset(coreIdx);
		}
		break;
	/*
		VPU Clock setting value
		0x0860E600      //432MHz
		0x0869C600      //418.5MHz
		0x0860D600      //405MHz
		0x0860A600      //324MHz
		0x08695600      //310.5MHz
		0x08609600      //297MHz
		0x08693600      //283.5MHz
		0x08607600      //243MHz
		0x08606600      //216MHz
	*/
	case VDI_IOCTL_SET_CLOCK:
		{
			vpu_clock_info_t clockInfo;
			ret = copy_from_user(&clockInfo, (vpu_clock_info_t *)arg, sizeof(vpu_clock_info_t));
			if (ret == 0)
			{
				u32 clk_en_val, ve_en_val;
				printk(KERN_INFO "[VPUDRV] VDI_IOCTL_SET_CLOCK value:0x%08x\n", clockInfo.value);
				clk_en_val = readl(IOMEM(VPU_VIRT_ADDR_MAP(VPU_CLOCK_ENABLE_REG)));
				ve_en_val = clk_en_val & (1 << 29 | 1 << 12);
				VPU_WRITE_REG_INT32U(VPU_CLOCK_ENABLE_REG, (clk_en_val & ~ve_en_val)); //Disable clock gating
				VPU_WRITE_REG_INT32U(VPU_CLOCK_PLL_REG, clockInfo.value);
#if 0
				VPU_WRITE_REG_INT32U(VPU_CLOCK_PLL2_REG, 0x5); //Power On
				VPU_WRITE_REG_INT32U(VPU_CLOCK_PLL2_REG, 0x7); //Release Reset
				__delay(100);
				VPU_WRITE_REG_INT32U(VPU_CLOCK_PLL2_REG, 0x3); //Release Reset
#else
				__delay(100);
#endif
				clk_en_val = readl(IOMEM(VPU_VIRT_ADDR_MAP(VPU_CLOCK_ENABLE_REG)));
				VPU_WRITE_REG_INT32U(VPU_CLOCK_ENABLE_REG, (clk_en_val | ve_en_val)); //Enable clock gating
				break;
			}

			ret = -EFAULT;
		}
		break;
	case VDI_IOCTL_GET_CLOCK:
		{
			vpu_clock_info_t clockInfo;
			clockInfo.value = readl(IOMEM(VPU_VIRT_ADDR_MAP(VPU_CLOCK_PLL_REG)));
			printk(KERN_INFO "[VPUDRV] VDI_IOCTL_GET_CLOCK value:0x%08x\n", clockInfo.value);
			ret = copy_to_user((vpu_clock_info_t *)arg, &clockInfo, sizeof(vpu_clock_info_t));
			if (ret != 0)
				ret = -EFAULT;
		}
		break;
	/*
		Clock Enable
		1 << 29    clk_en_ve_h265
		1 << 13    clk_en_ve_jpeg
		1 << 12    clk_en_ve_h264
	*/
	case VDI_IOCTL_SET_CLOCK_ENABLE:
		{
			vpu_clock_info_t clockInfo;
			ret = copy_from_user(&clockInfo, (vpu_clock_info_t *)arg, sizeof(vpu_clock_info_t));
			if (ret == 0)
			{
				unsigned int clk_en_val;
				//printk(KERN_INFO "[VPUDRV]  VDI_IOCTL_SET_CLOCK_ENABLE value:0x%08x\n", clockInfo.value);
				clk_en_val = readl(IOMEM(VPU_VIRT_ADDR_MAP(VPU_CLOCK_ENABLE_REG)));
				clk_en_val |= clockInfo.value;
				VPU_WRITE_REG_INT32U(VPU_CLOCK_ENABLE_REG, clk_en_val);
				__delay(100);
				break;
			}

			ret = -EFAULT;
		}
		break;
	case VDI_IOCTL_SET_CLOCK_DISABLE:
		{
			vpu_clock_info_t clockInfo;
			ret = copy_from_user(&clockInfo, (vpu_clock_info_t *)arg, sizeof(vpu_clock_info_t));
			if (ret == 0)
			{
				u32 clk_en_val;
				//printk(KERN_INFO "[VPUDRV]  VDI_IOCTL_SET_CLOCK_DISABLE value:0x%08x\n", clockInfo.value);
				clk_en_val = readl(IOMEM(VPU_VIRT_ADDR_MAP(VPU_CLOCK_ENABLE_REG)));
				clk_en_val &= ~(clockInfo.value);
				VPU_WRITE_REG_INT32U(VPU_CLOCK_ENABLE_REG, clk_en_val);
				__delay(100);
				break;
			}

			ret = -EFAULT;
		}
		break;
	case VDI_IOCTL_GET_SUPPORT_TYPE:
		{
			ret = put_user(support_codec_types, (u32 __user *)arg);
			if (ret != 0)
				ret = -EFAULT;
		}
		break;
	case VDI_IOCTL_FOURK_INFO:
		{
			vpudrv_fourk_info_t fourkInfo;
			ret = copy_from_user(&fourkInfo, (vpudrv_fourk_info_t *)arg, sizeof(vpudrv_fourk_info_t));
			if (ret == 0)
			{
				spin_lock(&s_vpu_lock);
				switch(fourkInfo.setvalue)
				{
					case FOURK_SET_PENDING:
					{
						s_vpu_fourk_info_value = fourkInfo.value;
						if (s_vpu_fourk_info_value == 1)
						{
							s_vpu_fourk_info_instidx_plus1 = (fourkInfo.inst_idx+1);
							s_vpu_fourk_info_coreidx = fourkInfo.core_idx;
						}
						else
						{
							s_vpu_fourk_info_instidx_plus1 = 0;
							s_vpu_fourk_info_coreidx = 0;
						}
						printk(KERN_INFO "[FOURK_SET_PENDING] s_vpu_fourk_info_value:%d, inst_idx:%d\n", s_vpu_fourk_info_value, fourkInfo.inst_idx);
						break;
					}
					case FOURK_GET_PENDING:
					{
						if (fourkInfo.core_idx == s_vpu_fourk_info_coreidx && fourkInfo.inst_idx == (s_vpu_fourk_info_instidx_plus1-1))
							fourkInfo.value = 0;
						else
							fourkInfo.value = s_vpu_fourk_info_value;
						printk(KERN_INFO "[FOURK_GET_PENDING] inst_idx:%d, value:%d\n", fourkInfo.inst_idx, fourkInfo.value);
						ret = copy_to_user((vpudrv_fourk_info_t *)arg, &fourkInfo, sizeof(vpudrv_fourk_info_t));
						if (ret != 0)
							ret = -EFAULT;
						break;
					}
					case FOURK_SET_INSTANCE_TYPE:
					{
						s_vpu_fourk_info_enable[fourkInfo.core_idx][fourkInfo.inst_idx] = fourkInfo.value;
						printk(KERN_INFO "[FOURK_SET_INSTANCE_TYPE] inst_idx:%d, value:%d\n", fourkInfo.inst_idx, fourkInfo.value);
						break;
					}
					case FOURK_GET_INSTANCE_NUM:
					{
						unsigned int i, j;
						unsigned int totalNum = 0;
						for (i = 0; i < MAX_NUM_VPU_CORE; i++)
						{
							for (j = 0; j < MAX_NUM_INSTANCE; j++)
							{
								totalNum += s_vpu_fourk_info_enable[i][j];
							}
						}
						fourkInfo.value = totalNum;
						printk(KERN_INFO "[FOURK_GET_INSTANCE_NUM] inst_idx:%d, value:%d\n", fourkInfo.inst_idx, fourkInfo.value);
						ret = copy_to_user((vpudrv_fourk_info_t *)arg, &fourkInfo, sizeof(vpudrv_fourk_info_t));
						if (ret != 0)
							ret = -EFAULT;
						break;
					}
					case FOURK_GET_INSTIDX:
					{
						printk(KERN_INFO "[FOURK_GET_INSTIDX] inst_idx:%d, (s_vpu_fourk_info_instidx_plus1-1):%d\n", fourkInfo.inst_idx, (s_vpu_fourk_info_instidx_plus1-1));
						fourkInfo.inst_idx = (s_vpu_fourk_info_instidx_plus1-1);
						ret = copy_to_user((vpudrv_fourk_info_t *)arg, &fourkInfo, sizeof(vpudrv_fourk_info_t));
						if (ret != 0)
							ret = -EFAULT;
						break;
					}
					default:
					{
						printk(KERN_ERR "[VPUDRV] No such setvalue, fourkInfo.setvalue is %d\n", fourkInfo.setvalue);
						break;
					}
				}
				spin_unlock(&s_vpu_lock);
				break;
			}

			ret = -EFAULT;
		}
#ifdef CONFIG_PM
	case VDI_IOCTL_SLEEP:
		{
			pm_message_t msg;
			vpu_suspend(NULL, msg);
			break;
		}
	case VDI_IOCTL_WAKEUP:
		vpu_resume(NULL);
		break;
#endif
	default:
		{
			printk(KERN_ERR "[VPUDRV] No such IOCTL, cmd is %d\n", cmd);
		}
		break;
	}
	return ret;
}

static ssize_t vpu_read(struct file *filp, char __user *buf, size_t len, loff_t *ppos)
{
	return -1;
}

static ssize_t vpu_write(struct file *filp, const char __user *buf, size_t len, loff_t *ppos)
{
	printk(KERN_INFO "[VPUDRV] vpu_write len=%d\n", (int)len);
	if ( !buf )
	{
		printk(KERN_ERR "[VPUDRV] vpu_write buf = NULL error \n");
		return -EFAULT;
	}

	if (len == sizeof(vpu_bit_firmware_info_t))
	{
		vpu_bit_firmware_info_t *bit_firmware_info;

		bit_firmware_info = kzalloc(sizeof(vpu_bit_firmware_info_t), GFP_KERNEL);
		if (!bit_firmware_info)
		{
			printk(KERN_ERR "[VPUDRV] vpu_write  bit_firmware_info allocation error \n");
			return -EFAULT;
		}

		if (copy_from_user(bit_firmware_info, buf, len)) {
			printk(KERN_ERR "[VPUDRV] vpu_write copy_from_user error for bit_firmware_info\n");
			kfree(bit_firmware_info);
			return -EFAULT;		
		}

		if (bit_firmware_info->size == sizeof(vpu_bit_firmware_info_t))
		{
			printk("[VPUDRV] vpu_write set bit_firmware_info coreIdx=0x%x, reg_base_offset=0x%x size=0x%x, bit_code[0]=0x%x\n",
			bit_firmware_info->core_idx, (int)bit_firmware_info->reg_base_offset, bit_firmware_info->size, bit_firmware_info->bit_code[0]); 

			if (bit_firmware_info->core_idx > MAX_NUM_VPU_CORE)
			{
				printk(KERN_ERR "[VPUDRV] vpu_write coreIdx[%d] is exceeded than MAX_NUM_VPU_CORE[%d]\n", bit_firmware_info->core_idx, MAX_NUM_VPU_CORE);
				kfree(bit_firmware_info);
				return -ENODEV;
			}
    
			memcpy((void *)&s_bit_firmware_info[bit_firmware_info->core_idx], bit_firmware_info, sizeof(vpu_bit_firmware_info_t));
			kfree(bit_firmware_info);
			return len;
		}

		kfree(bit_firmware_info);
	}

	return -1;
}

static int vpu_release(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "[VPUDRV] vpu_release open_count=%d\n", s_vpu_open_ref_count);

	spin_lock(&s_vpu_lock);

		/* found and free the not handled buffer by user applications */
		vpu_free_buffers(filp);		

		/* found and free the not closed instance by user applications */
		vpu_free_instances(filp);

	spin_unlock(&s_vpu_lock);

	return 0;
}


static int vpu_fasync(int fd, struct file *filp, int mode)
{
	struct vpu_drv_context_t *dev = (struct vpu_drv_context_t *)filp->private_data;
	return fasync_helper(fd, filp, mode, &dev->async_queue);
}


static int vpu_map_to_register(struct file *fp, struct vm_area_struct *vm)
{
	unsigned long pfn;

	vm->vm_flags |= VM_IO | VM_RESERVED;
	vm->vm_page_prot = pgprot_noncached(vm->vm_page_prot);
	pfn = s_vpu_reg_phy_addr >> PAGE_SHIFT;

	return remap_pfn_range(vm, vm->vm_start, pfn, vm->vm_end-vm->vm_start, vm->vm_page_prot) ? -EAGAIN : 0;
}


static int vpu_map_to_physical_memory(struct file *fp, struct vm_area_struct *vm)
{
	vm->vm_flags |= VM_IO | VM_RESERVED;
	vm->vm_page_prot = pgprot_writecombine(vm->vm_page_prot); 

	return remap_pfn_range(vm, vm->vm_start, vm->vm_pgoff, vm->vm_end-vm->vm_start, vm->vm_page_prot) ? -EAGAIN : 0;
}
static int vpu_map_to_instance_pool_memory(struct file *fp, struct vm_area_struct *vm)
{
	vm->vm_flags |= VM_IO | VM_RESERVED;
	vm->vm_page_prot = pgprot_noncached(vm->vm_page_prot);
	return remap_pfn_range(vm, vm->vm_start, vm->vm_pgoff, vm->vm_end-vm->vm_start, vm->vm_page_prot) ? -EAGAIN : 0;
}
/*!
 * @brief memory map interface for vpu file operation
 * @return  0 on success or negative error code on error
 */
static int vpu_mmap(struct file *fp, struct vm_area_struct *vm)
{
	if (vm->vm_pgoff) 
	{
		if(vm->vm_pgoff == (s_instance_pool.phys_addr>>PAGE_SHIFT))
			return  vpu_map_to_instance_pool_memory(fp, vm);
	
		return vpu_map_to_physical_memory(fp, vm);
	}
	else
		return vpu_map_to_register(fp, vm);
}

struct file_operations vpu_fops = {
	.owner = THIS_MODULE,
	.open = vpu_open,
	.read = vpu_read,
	.write = vpu_write,
	//.ioctl = vpu_ioctl, // for kernel 2.6.9 of C&M
	.unlocked_ioctl = vpu_ioctl,
	.release = vpu_release,
	.fasync = vpu_fasync,
	.mmap = vpu_mmap,
};




static int vpu_probe(struct platform_device *pdev)
{
	int err = 0;
	struct resource *res=NULL;
	printk(KERN_INFO "[VPUDRV] vpu_probe\n");

	if(pdev)
		res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res) 	// if platform driver is implemented
	{
		s_vpu_reg_phy_addr = res->start;
		s_vpu_reg_virt_addr = ioremap(res->start, res->end - res->start);
		printk(KERN_INFO "[VPUDRV] : 1 vpu base address get from platform driver physical base addr=0x%x, virtual base=0x%x\n", (int)s_vpu_reg_phy_addr , (int)s_vpu_reg_virt_addr);		
	}
	else
	{
		s_vpu_reg_virt_addr = ioremap(s_vpu_reg_phy_addr, VPU_REG_SIZE);
		printk(KERN_INFO "[VPUDRV] : 2 vpu base address get from defined value physical base addr=0x%x, virtual base=0x%x\n", (int)s_vpu_reg_phy_addr, (int)s_vpu_reg_virt_addr);
		
	}

#if 1
	u32 bonding_value;
	bonding_value = readl(IOMEM(VPU_VIRT_ADDR_MAP(VPU_BONDING_REG)));

	if (bonding_value & ENABLE_RM)
		support_codec_types |= (1<<STD_RV);
	if (bonding_value & ENABLE_DIVX)
		support_codec_types |= (1 << STD_DIV3);
	if ((bonding_value & DISABLE_265) == 0)
		support_codec_types |= (1 << STD_HEVC);

	//printk(KERN_INFO "[VPUDRV] BONDING_VALUE : 0x%08x, support_codec_types : 0x%08x\n", bonding_value, support_codec_types);
#endif

#if 0
	/* get the major number of the character device */
	if ((alloc_chrdev_region(&s_vpu_major, 0, 1, VPU_DEV_NAME)) < 0)
	{
		err = -EBUSY;
		printk(KERN_ERR "could not allocate major number\n");
		goto ERROR_PROVE_DEVICE;
	}

	s_vpu_class = class_create(THIS_MODULE, VPU_DEV_NAME);
	if (IS_ERR(s_vpu_class))
	{
		err = -EBUSY;
		printk(KERN_ERR "could not create class\n");

		goto ERROR_PROVE_DEVICE;
	}

	s_vpu_dev = device_create(s_vpu_class, NULL, MKDEV(s_vpu_major, 0), NULL, VPU_DEV_NAME);
	if (IS_ERR(s_vpu_dev))
	{
		err = -EBUSY;
		printk(KERN_ERR "could not create device\n");

		goto ERROR_PROVE_DEVICE;
	}

	/* initialize the device structure and register the device with the kernel */
	cdev_init(&s_vpu_cdev, &vpu_fops);
	if ((cdev_add(&s_vpu_cdev, s_vpu_major, 1)) < 0)
	{
		err = -EBUSY;
		printk(KERN_ERR "could not allocate chrdev\n");

		goto ERROR_PROVE_DEVICE;
	}
#else
	s_vpu_dev.minor = MISC_DYNAMIC_MINOR;
	s_vpu_dev.name = VPU_DEV_NAME;
	s_vpu_dev.fops = &vpu_fops;
	s_vpu_dev.parent = NULL;
	if (misc_register(&s_vpu_dev)) {
		printk("vpu: failed to register misc device.");
		goto ERROR_PROVE_DEVICE;
	}
#endif

	if (pdev)
		s_vpu_clk_980 = vpu_clk_get(&pdev->dev, 0);
	else
		s_vpu_clk_980 = vpu_clk_get(NULL, 0);

	if (!s_vpu_clk_980)
		printk(KERN_ERR "[VPUDRV] : fail to get clock controller, but, do not treat as error, coreIdx=0\n");
	else
		printk(KERN_INFO "[VPUDRV] : get clock controller s_vpu_clk_980=0x%x\n", (int)s_vpu_clk_980);

	if (pdev)
		s_vpu_clk_410 = vpu_clk_get(&pdev->dev, 1);
	else
		s_vpu_clk_410 = vpu_clk_get(NULL, 1);

	if (!s_vpu_clk_410)
		printk(KERN_ERR "[VPUDRV] : fail to get clock controller, but, do not treat as error, coreIdx=1\n");
	else
		printk(KERN_INFO "[VPUDRV] : get clock controller s_vpu_clk_410=0x%x\n", (int)s_vpu_clk_410);

	s_vpu_clk_vpll = clk_get(NULL, "vpll");
	if (!s_vpu_clk_vpll)
		printk(KERN_ERR "[VPUDRV] : fail to get clock controller, but, do not treat as error, coreIdx=vpll\n");
	else
		printk(KERN_INFO "[VPUDRV] : get clock controller s_vpu_clk_vpll=0x%x\n", (int)s_vpu_clk_vpll);

#ifdef VPU_SUPPORT_CLOCK_CONTROL
	vpu_clk_enable(s_vpu_clk_980);
	vpu_clk_enable(s_vpu_clk_410);
#endif


#ifdef VPU_SUPPORT_ISR
	if(pdev)
		res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (res) 	// if platform driver is implemented
	{
		s_vpu_irq = res->start;
		printk(KERN_INFO "[VPUDRV] : 1 vpu irq number get from platform driver irq=0x%x\n", s_vpu_irq );		
	}
	else
	{
		printk(KERN_INFO "[VPUDRV] : 2 vpu irq number get from defined value irq=0x%x\n", s_vpu_irq );
	}


	err = request_irq(s_vpu_irq, vpu_irq_handler, 0, "VPU_CODEC_IRQ", (void *)(&s_vpu_drv_context));
	if (err)
	{
		printk(KERN_ERR "[VPUDRV] :  fail to register interrupt handler\n");
		goto ERROR_PROVE_DEVICE;
	}
#endif
	
	
#ifdef VPU_SUPPORT_RESERVED_VIDEO_MEMORY
	s_video_memory.size = VPU_INIT_VIDEO_MEMORY_SIZE_IN_BYTE;
	s_video_memory.phys_addr = VPU_DRAM_PHYSICAL_BASE;
	s_video_memory.base = (unsigned long)ioremap(s_video_memory.phys_addr, PAGE_ALIGN(s_video_memory.size));
	if (!s_video_memory.base)
	{	
		printk(KERN_ERR "[VPUDRV] :  fail to remap video memory physical phys_addr=0x%x, base=0x%x, size=%d\n", (int)s_video_memory.phys_addr, (int)s_video_memory.base, (int)s_video_memory.size);
		goto ERROR_PROVE_DEVICE;
	}
	
	if (vmem_init(&s_vmem, s_video_memory.phys_addr, s_video_memory.size) < 0)
	{
		printk(KERN_ERR "[VPUDRV] :  fail to init vmem system\n");
		goto ERROR_PROVE_DEVICE;
	}
	printk(KERN_INFO "[VPUDRV] success to probe vpu device with reserved video memory phys_addr=0x%x, base = 0x%x\n",(int) s_video_memory.phys_addr, (int)s_video_memory.base);
#else
	printk(KERN_INFO "[VPUDRV] success to probe vpu device with non reserved video memory\n");
#endif	
	
	
	return 0;


ERROR_PROVE_DEVICE:

#if 0
	if (s_vpu_dev)
	{
		device_destroy(s_vpu_class, MKDEV(s_vpu_major, 0));
		s_vpu_dev = NULL;
	}

	if (s_vpu_class)
	{
		class_destroy(s_vpu_class);
		s_vpu_class = NULL;
	}

	if (s_vpu_major)
		unregister_chrdev_region(s_vpu_major, 1);
#else
	misc_deregister(&s_vpu_dev);
#endif

	if (s_vpu_reg_virt_addr)
		iounmap(s_vpu_reg_virt_addr);

	return err;
}

static int vpu_remove(struct platform_device *pdev)
{
#ifdef VPU_SUPPORT_PLATFORM_DRIVER_REGISTER	

	printk(KERN_INFO "[VPUDRV] vpu_remove\n");
	if (s_instance_pool.base) 
	{
		vpu_free_dma_buffer(&s_instance_pool);
		s_instance_pool.base = 0;
	}


	if (s_common_memory.base)
	{
		vpu_free_dma_buffer(&s_common_memory);
		s_common_memory.base = 0;
	}

#ifdef VPU_SUPPORT_RESERVED_VIDEO_MEMORY
	if (s_video_memory.base) 
	{
		iounmap((void *)s_video_memory.base);
		s_video_memory.base = 0;

		vmem_exit(&s_vmem);		
	}
#endif

#if 0
	if (s_vpu_dev)
	{
		device_destroy(s_vpu_class, MKDEV(s_vpu_major, 0));
		s_vpu_dev = NULL;
	}

	if (s_vpu_class)
	{
		class_destroy(s_vpu_class);
		s_vpu_class = NULL;
	}

	if (s_vpu_major > 0)
	{
		cdev_del(&s_vpu_cdev);
		unregister_chrdev_region(s_vpu_major, 1);
		s_vpu_major = 0;
	}
#else
	misc_deregister(&s_vpu_dev);
#endif

#ifdef VPU_SUPPORT_ISR	
	if (s_vpu_irq)
		free_irq(s_vpu_irq, &s_vpu_drv_context);
#endif

	if (s_vpu_reg_virt_addr)
		iounmap(s_vpu_reg_virt_addr);

	vpu_clk_put(s_vpu_clk_980);
	vpu_clk_put(s_vpu_clk_410);
#endif //VPU_SUPPORT_PLATFORM_DRIVER_REGISTER
	return 0;
}

#define WAVE4_STACK_SIZE		(8*1024)       /* DO NOT CHANGE */
#define W4_MAX_CODE_BUF_SIZE	(512*1024)
#define W4_CMD_INIT_VPU		(0x0001)
#define W4_CMD_SLEEP_VPU		(0x0400)
#define W4_CMD_WAKEUP_VPU	(0x0800)

static void Wave4BitIssueCommand(Uint32 cmd)
{
	WriteVpuRegister(W4_VPU_BUSY_STATUS, 1, 1);
	WriteVpuRegister(W4_CORE_INDEX,  0, 1);
	//coreIdx = ReadVpuRegister(W4_VPU_BUSY_STATUS, 1);
	//coreIdx = 0;
	WriteVpuRegister(W4_INST_INDEX,  0, 1);
	WriteVpuRegister(W4_COMMAND, cmd, 1);
	WriteVpuRegister(W4_VPU_HOST_INT_REQ, 1, 1);

	return;
}

#ifdef CONFIG_PM
static int vpu_suspend(struct platform_device *pdev, pm_message_t state)
{
	int i;
	int core;
	unsigned long timeout = jiffies + HZ;	// vpu wait timeout to 1sec

	printk(KERN_INFO "[VPUDRV] vpu_suspend\n");
#ifdef VPU_HACK_CLOCK_CONTROL
	unsigned int clk_en_val;
	clk_en_val = readl(IOMEM(VPU_VIRT_ADDR_MAP(VPU_CLOCK_ENABLE_REG)));
	clk_en_val |= (1 << 12 | 1 << 29);
	VPU_WRITE_REG_INT32U(VPU_CLOCK_ENABLE_REG, clk_en_val);
	__delay(100);
#else
	vpu_clk_enable(s_vpu_clk_980);
	vpu_clk_enable(s_vpu_clk_410);
#endif

	for (core=0; core<MAX_NUM_VPU_CORE; core++)
	{
		if (s_bit_firmware_info[core].size == 0)
			continue;

		if (core == 0)
		{
			while (ReadVpuRegister(BIT_BUSY_FLAG, core))
			{
				if (time_after(jiffies, timeout))
				{
					printk("In[%s][%d] BUSY timeout\n", __func__, __LINE__);
					goto DONE_SUSPEND;
				}
			}

#if defined(CODA7L) || defined(CODA851)
			s_run_index = ReadVpuRegister(BIT_RUN_INDEX, core);
			s_run_codstd = ReadVpuRegister(BIT_RUN_COD_STD, core);
			WriteVpuRegister(BIT_BUSY_FLAG, 1, core);
			WriteVpuRegister(BIT_RUN_COMMAND, VPU_SLEEP, core);

			while (ReadVpuRegister(BIT_BUSY_FLAG, core))
			{
				if (time_after(jiffies, timeout))
					goto DONE_SUSPEND;
			}
#endif

			for ( i = 0 ; i < 64 ; i++)
			{
				s_vpu_reg_store[core][i] = ReadVpuRegister(BIT_BASE+(0x100+(i * 4)), core);
			}
		}
		else
		{
			while (ReadVpuRegister(W4_VPU_BUSY_STATUS, core))
			{
				if (time_after(jiffies, timeout))
				{
					printk("In[%s][%d] BUSY timeout\n", __func__, __LINE__);
					goto DONE_SUSPEND;
				}
			}

			Wave4BitIssueCommand(W4_CMD_SLEEP_VPU);

			while (ReadVpuRegister(W4_VPU_BUSY_STATUS, core) || ReadVpuRegister(W4_VPU_INT_STS, core))
			{
				if (time_after(jiffies, timeout))
				{
					printk("In[%s][%d] SLEEP_VPU BUSY timeout\n", __func__, __LINE__);
					goto DONE_SUSPEND;
				}
			}

			if (ReadVpuRegister(W4_RET_SUCCESS, core) == 0)
			{
				printk("SLEEP_VPU failed [0x%x]\n", ReadVpuRegister(W4_RET_FAIL_REASON, core));
				goto DONE_SUSPEND;
			}
		}
	}

#ifdef VPU_HACK_CLOCK_CONTROL
	clk_en_val = readl(IOMEM(VPU_VIRT_ADDR_MAP(VPU_CLOCK_ENABLE_REG)));
	clk_en_val &= ~(1 << 12 | 1 << 29);
	VPU_WRITE_REG_INT32U(VPU_CLOCK_ENABLE_REG, clk_en_val);
	__delay(100);
#else
	vpu_clk_disable(s_vpu_clk_410);
	vpu_clk_disable(s_vpu_clk_980);
#endif
	printk(KERN_INFO "[VPUDRV] vpu_suspend end\n");
	
	return 0;

DONE_SUSPEND:
#ifdef VPU_HACK_CLOCK_CONTROL
	clk_en_val = readl(IOMEM(VPU_VIRT_ADDR_MAP(VPU_CLOCK_ENABLE_REG)));
	clk_en_val &= ~(1 << 12 | 1 << 29);
	VPU_WRITE_REG_INT32U(VPU_CLOCK_ENABLE_REG, clk_en_val);
	__delay(100);
#else
	vpu_clk_disable(s_vpu_clk_410);
	vpu_clk_disable(s_vpu_clk_980);
#endif
	return -EAGAIN;

}

static int vpu_resume(struct platform_device *pdev)
{
	int i;
	int core;
	u32 val;
	unsigned long timeout = jiffies + HZ;	// vpu wait timeout to 1sec
	unsigned long   code_base;
	unsigned long   code_phys;
	Uint32          code_size;
	unsigned long   stack_base;
	Uint32          stack_size;
	Uint32          remap_size;
	int             regVal;
	Uint32          hwOption  = 0;
	Uint32          *bitcode;

	printk(KERN_INFO "[VPUDRV] vpu_resume\n");
#ifdef VPU_HACK_CLOCK_CONTROL
	unsigned int clk_en_val;
	clk_en_val = readl(IOMEM(VPU_VIRT_ADDR_MAP(VPU_CLOCK_ENABLE_REG)));
	clk_en_val |= (1 << 12 | 1 << 29);
	VPU_WRITE_REG_INT32U(VPU_CLOCK_ENABLE_REG, clk_en_val);
	__delay(100);
#else
	vpu_clk_enable(s_vpu_clk_980);
	vpu_clk_enable(s_vpu_clk_410);
#endif
	WriteVpuRegister(0x7000, 0x13, core); //RTK wrapper for VE
	
	for (core=0; core<MAX_NUM_VPU_CORE; core++)
	{
		if (s_bit_firmware_info[core].size == 0)
			continue;

		if (core == 0)
		{
			WriteVpuRegister(BIT_CODE_RUN, 0, core);

			//---- LOAD BOOT CODE
			for( i = 0; i <512; i++ ) 
			{
				val = s_bit_firmware_info[core].bit_code[i];
				WriteVpuRegister(BIT_CODE_DOWN, ((i << 16) | val), core);			
			}

			for (i = 0 ; i < 64 ; i++) 
				WriteVpuRegister(BIT_BASE+(0x100+(i * 4)), s_vpu_reg_store[core][i], core);

			WriteVpuRegister(BIT_BUSY_FLAG, 1, core);
			WriteVpuRegister(BIT_CODE_RESET, 1, core);
			WriteVpuRegister(BIT_CODE_RUN, 1, core);

			while (ReadVpuRegister(BIT_BUSY_FLAG, core))
			{
				if (time_after(jiffies, timeout))
				{
					printk("In[%s][%d] BIT_CODE_RUN BUSY timeout\n", __func__, __LINE__);
					goto DONE_WAKEUP;
				}
			}

#if defined(CODA7L) || defined(CODA851)
			WriteVpuRegister(BIT_BUSY_FLAG, 1, core);
			WriteVpuRegister(BIT_RUN_INDEX,   s_run_index, core);
			WriteVpuRegister(BIT_RUN_COD_STD, s_run_codstd, core);
			WriteVpuRegister(BIT_RUN_COMMAND, VPU_WAKE, core);	

			while (ReadVpuRegister(BIT_BUSY_FLAG, core))
			{
				if (time_after(jiffies, timeout))
					goto DONE_WAKEUP;
			}
#endif
		}
		else
		{
			code_base = s_common_memory.base+(core*SIZE_COMMON);
			code_phys = (unsigned long)(s_common_memory.phys_addr+(core*SIZE_COMMON));
			/* ALIGN TO 4KB */
			code_size = (W4_MAX_CODE_BUF_SIZE&~0xfff);
			bitcode = (unsigned int *)s_bit_firmware_info[core].bit_code;
			if (code_size < s_bit_firmware_info[core].size*2) {
				goto DONE_WAKEUP;
			}
			stack_base = code_phys + code_size;
			stack_size = WAVE4_STACK_SIZE;

#if 0
			//---- LOAD BOOT CODE
			for( i = 0; i < 256 ; i++ )
			{
				val = bitcode[i];
				WriteVpu(code_base+(i*4), val);
			}
#endif
#if 1
			regVal = 0;
			WriteVpuRegister(W4_PO_CONF, regVal, core);

			/* Reset All blocks */
			regVal = 0x7ffffff;
			WriteVpuRegister(W4_RESET_REQ, regVal, core);    // Reset All blocks

			/* Waiting reset done */
			while (ReadVpuRegister(W4_RESET_STATUS, core))
			{
				if (time_after(jiffies, timeout))
				{
					printk("In[%s][%d] W4_RESET_REQ BUSY timeoutn", __func__, __LINE__);
					goto DONE_WAKEUP;
				}
			}

			WriteVpuRegister(W4_RESET_REQ, 0, core);

			/* remap page size */
			remap_size = (code_size >> 12) &0x1ff;
			regVal = 0x80000000 | (W4_REMAP_CODE_INDEX<<12) | (0xf<<16) | (1<<11) | remap_size;
			WriteVpuRegister(W4_VPU_REMAP_CTRL,     regVal, core);
			WriteVpuRegister(W4_VPU_REMAP_VADDR,    0x00000000, core);    /* DO NOT CHANGE! */
			WriteVpuRegister(W4_VPU_REMAP_PADDR,    code_phys, core);
			WriteVpuRegister(W4_ADDR_CODE_BASE,     code_phys, core);
			WriteVpuRegister(W4_CODE_SIZE,          code_size, core);
			WriteVpuRegister(W4_CODE_PARAM,         0xf, core);
			WriteVpuRegister(W4_INIT_VPU_TIME_OUT_CNT,   0xffff, core);

			/* Stack */
			WriteVpuRegister(W4_ADDR_STACK_BASE, stack_base, core);
			WriteVpuRegister(W4_STACK_SIZE,      stack_size, core);
			WriteVpuRegister(W4_HW_OPTION, hwOption, core);

			/* Interrupt */
			regVal  = (1<<W4_INT_DEC_PIC_HDR);
			regVal |= (1<<W4_INT_DEC_PIC);
			regVal |= (1<<W4_INT_QUERY_DEC);
			regVal |= (1<<W4_INT_SLEEP_VPU);
			regVal |= (1<<W4_INT_BSBUF_EMPTY);

			WriteVpuRegister(W4_VPU_INT_ENABLE,  regVal, core);

			Wave4BitIssueCommand(W4_CMD_INIT_VPU);
			WriteVpuRegister(W4_VPU_REMAP_PROC_START, 1, core);
#else
			//for ( i = 0 ; i < 64 ; i++)
			//	WriteVpuRegister(W4_REG_BASE + 0x100 + (i * 4), s_vpu_reg_store[core][i], core);

			//WriteVpuRegister(W4_SET_CUR_SP, s_vpu_sp_store[core], core);


			WriteVpuRegister(W4_ADDR_CODE_BASE,     code_base, core);
			WriteVpuRegister(W4_CODE_SIZE,          code_size, core);
			WriteVpuRegister(W4_CODE_PARAM,         0, core);
			/* Stack */
			WriteVpuRegister(W4_ADDR_STACK_BASE, stack_base, core);
			WriteVpuRegister(W4_VPU_STACK_SIZE,  stack_size, core);

			Wave4BitIssueCommand(W4_CMD_WAKEUP_VPU );
#endif
			while (ReadVpuRegister(W4_VPU_BUSY_STATUS, core) || ReadVpuRegister(W4_VPU_INT_STS, core))
			{
				if (time_after(jiffies, timeout))
				{
					printk("In[%s][%d] W4_CMD_INIT_VPU BUSY timeout\n", __func__, __LINE__);
					goto DONE_WAKEUP;
				}
			}

			if (ReadVpuRegister(W4_RET_SUCCESS, core) == 0)
			{
				printk("WAKEUP_VPU failed [0x%x]\n", ReadVpuRegister(W4_RET_FAIL_REASON, core));
				goto DONE_WAKEUP;
			}
		}
	}

	if (s_vpu_open_ref_count == 0)
	{
#ifdef VPU_HACK_CLOCK_CONTROL
		clk_en_val = readl(IOMEM(VPU_VIRT_ADDR_MAP(VPU_CLOCK_ENABLE_REG)));
		clk_en_val &= ~(1 << 12 | 1 << 29);
		VPU_WRITE_REG_INT32U(VPU_CLOCK_ENABLE_REG, clk_en_val);
		__delay(100);
#else
		vpu_clk_disable(s_vpu_clk_410);
		vpu_clk_disable(s_vpu_clk_980);
#endif
	}

DONE_WAKEUP:

	if (s_vpu_open_ref_count > 0)
	{
#ifdef VPU_HACK_CLOCK_CONTROL
		clk_en_val = readl(IOMEM(VPU_VIRT_ADDR_MAP(VPU_CLOCK_ENABLE_REG)));
		clk_en_val |= (1 << 12 | 1 << 29);
		VPU_WRITE_REG_INT32U(VPU_CLOCK_ENABLE_REG, clk_en_val);
		__delay(100);
#else
		vpu_clk_enable(s_vpu_clk_980);
		vpu_clk_enable(s_vpu_clk_410);
#endif
	}

	printk(KERN_INFO "[VPUDRV] vpu_resume end\n");

	return 0;
}
#else
#define	vpu_suspend	NULL
#define	vpu_resume	NULL
#endif				/* !CONFIG_PM */

static struct platform_driver vpu_driver = {
	.driver = {
		   .name = VPU_PLATFORM_DEVICE_NAME,
		   },
	.probe = vpu_probe,
	.remove = vpu_remove,
	.suspend    = vpu_suspend,
	.resume     = vpu_resume,
};


static int __init vpu_init(void)
{
	int res;

	printk(KERN_INFO "[VPUDRV] begin vpu_init\n");	
	init_waitqueue_head(&s_interrupt_wait_q);
	s_common_memory.base = 0;
	s_instance_pool.base = 0;
#ifdef VPU_SUPPORT_PLATFORM_DRIVER_REGISTER
	res = platform_driver_register(&vpu_driver);
#else
	res = platform_driver_register(&vpu_driver);
	res = vpu_probe(NULL);
#endif
	printk(KERN_INFO "[VPUDRV] end vpu_init result=0x%x\n", res);	
	return res;
}

static void __exit vpu_exit(void)
{
#ifdef VPU_SUPPORT_PLATFORM_DRIVER_REGISTER	
	printk(KERN_INFO "[VPUDRV] vpu_exit\n");
	platform_driver_unregister(&vpu_driver);
#else	
	
	vpu_clk_put(s_vpu_clk_980);
	vpu_clk_put(s_vpu_clk_410);

	if (s_instance_pool.base) 
	{
		vpu_free_dma_buffer(&s_instance_pool);
		s_instance_pool.base = 0;
	}


	if (s_common_memory.base)
	{
		vpu_free_dma_buffer(&s_common_memory);
		s_common_memory.base = 0;
	}

#ifdef VPU_SUPPORT_RESERVED_VIDEO_MEMORY
	if (s_video_memory.base) 
	{
		iounmap((void *)s_video_memory.base);
		s_video_memory.base = 0;

		vmem_exit(&s_vmem);
	}
#endif

#if 0
	if (s_vpu_dev)
	{
		device_destroy(s_vpu_class, MKDEV(s_vpu_major, 0));
		s_vpu_dev = NULL;
	}

	if (s_vpu_class)
	{
		class_destroy(s_vpu_class);
		s_vpu_class = NULL;
	}


	if (s_vpu_major > 0)
	{
		cdev_del(&s_vpu_cdev);
		unregister_chrdev_region(s_vpu_major, 1);
		s_vpu_major = 0;
	}
#else
	misc_deregister(&s_vpu_dev);
#endif

#ifdef VPU_SUPPORT_ISR	
	if (s_vpu_irq)
		free_irq(s_vpu_irq, &s_vpu_drv_context);
#endif

	if (s_vpu_reg_virt_addr) {
		iounmap(s_vpu_reg_virt_addr);
		s_vpu_reg_virt_addr = (void *)0x00;
	}

#endif

	platform_driver_unregister(&vpu_driver);
	return;
}

MODULE_AUTHOR("A customer using C&M VPU, Inc.");
MODULE_DESCRIPTION("VPU linux driver");
MODULE_LICENSE("GPL");

module_init(vpu_init);
module_exit(vpu_exit);

/*
	reset bit
	1 << 18    reset bit of VE_JPEG
	1 << 17    reset bit of VE_H264
	1 << 5     reset bit of VE_H265
*/
int vpu_hw_reset(u32 coreIdx)
{
	u32 reset_value = 0;
	u32 reset_bit = 0;
	u32 clk_en_val = 0;
	u32 clk_en_bit = 0;

	if (coreIdx == 0)
	{
		reset_bit = 1 << 17;
		clk_en_bit = 1 << 12;
	}
	else
	{
		reset_bit = 1 << 5;
		clk_en_bit = 1 << 29;
	}

	// disable clock gatting
	clk_en_val = readl(IOMEM(VPU_VIRT_ADDR_MAP(VPU_CLOCK_ENABLE_REG)));
	clk_en_val &= ~clk_en_bit;
	VPU_WRITE_REG_INT32U(VPU_CLOCK_ENABLE_REG, clk_en_val);
	__delay(100);

	// reset vpu bit to 0
	reset_value = readl(IOMEM(VPU_VIRT_ADDR_MAP(VPU_CLOCK_REG_BASE)));
	reset_value &= ~reset_bit;
	VPU_WRITE_REG_INT32U(VPU_CLOCK_REG_BASE, reset_value);
	__delay(100);

	// reset vpu bit to 1
	reset_value = readl(IOMEM(VPU_VIRT_ADDR_MAP(VPU_CLOCK_REG_BASE)));
	reset_value |= reset_bit;
	VPU_WRITE_REG_INT32U(VPU_CLOCK_REG_BASE, reset_value);
	__delay(100);

	// enable clock gatting
	clk_en_val = readl(IOMEM(VPU_VIRT_ADDR_MAP(VPU_CLOCK_ENABLE_REG)));
	clk_en_val |= clk_en_bit;
	VPU_WRITE_REG_INT32U(VPU_CLOCK_ENABLE_REG, clk_en_val);
	__delay(100);

	printk(KERN_INFO "[VPUDRV] request vpu reset from application. \n");
	return 0;
}


struct clk *vpu_clk_get(struct device *dev, int coreIdx)
{
	if (coreIdx == 0)
		return clk_get(dev, "h264");
	else
		return clk_get(dev, "h265");
	//return clk_get(dev, VPU_CLK_NAME);
}
void vpu_clk_put(struct clk *clk)
{
	if (!(clk == NULL || IS_ERR(clk)))
		clk_put(clk);
}
int vpu_clk_enable(struct clk *clk)
{
	if (!(clk == NULL || IS_ERR(clk))){
		// the bellow is for C&M EVB.
	  /*
		{
			struct clk *s_vpuext_clk = NULL;
			s_vpuext_clk = clk_get(NULL, "vcore");
			if (s_vpuext_clk)
			{
				printk(KERN_INFO "[VPUDRV] vcore clk=%p\n", s_vpuext_clk);	
				clk_enable(s_vpuext_clk);
			}

			printk(KERN_INFO "[VPUDRV] vbus clk=%p\n", s_vpuext_clk);	
			if (s_vpuext_clk)
			{
				s_vpuext_clk = clk_get(NULL, "vbus");
				clk_enable(s_vpuext_clk);
			}
		}
		*/
		// for C&M EVB.

		printk(KERN_INFO "[VPUDRV] vpu_clk_enable\n");	
		return clk_enable(clk);
	}

	return 0;
}

void vpu_clk_disable(struct clk *clk)
{
	if (!(clk == NULL || IS_ERR(clk))){
		printk(KERN_INFO "[VPUDRV] vpu_clk_disable\n");	
		clk_disable(clk);
	}
}
