#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/module.h>
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
#include <linux/miscdevice.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>

#include "jpu.h"
#include "compat_jpu.h"
#include "../puwrap.h"

//from jpuconfig.h
#define MAX_NUM_INSTANCE 8
#define MAX_INST_HANDLE_SIZE (12*1024)

/* definitions to be changed as customer  configuration */
//#define JPU_SUPPORT_CLOCK_CONTROL /if you want to have clock gating scheme frame by frame
#define JPU_SUPPORT_ISR
/* if the platform driver knows the name of this driver. JPU_PLATFORM_DEVICE_NAME */
#define JPU_SUPPORT_PLATFORM_DRIVER_REGISTER
#ifndef CONFIG_RTK_RESERVE_MEMORY
/* if this driver knows the dedicated video memory address */
//#define JPU_SUPPORT_RESERVED_VIDEO_MEMORY
#endif
//#define JPU_IRQ_CONTROL
#define DEV_NAME "[RTK_JPU]"
#define JPU_PLATFORM_DEVICE_NAME "jdec"
#define JPU_CLK_NAME "jpeg"
#define JPU_DEV_NAME "jpu"

#define JPU_BASE_ADDR 0x9803e000
#define JPU_REG_SIZE 0x1000

#ifdef JPU_SUPPORT_ISR
#define JPU_IRQ_NUM 84+32
#endif

#ifndef VM_RESERVED /* for kernel up to 3.7.0 version */
# define  VM_RESERVED   (VM_DONTEXPAND | VM_DONTDUMP)
#endif

typedef struct jpu_drv_context_t {
	struct fasync_struct *async_queue;
	unsigned long interrupt_reason;
} jpu_drv_context_t;

/* To track the allocated memory buffer */
typedef struct jpudrv_buffer_pool_t {
	struct list_head list;
	struct jpudrv_buffer_t jb;
	struct file *filp;
} jpudrv_buffer_pool_t;

/* To track the instance index and buffer in instance pool */
typedef struct jpudrv_instanace_list_t {
	struct list_head list;
	unsigned long inst_idx;
	struct file *filp;
} jpudrv_instanace_list_t;

typedef struct jpudrv_instance_pool_t {
	unsigned char jpgInstPool[MAX_NUM_INSTANCE][MAX_INST_HANDLE_SIZE];
} jpudrv_instance_pool_t;

#ifdef JPU_SUPPORT_RESERVED_VIDEO_MEMORY
#define JPU_INIT_VIDEO_MEMORY_SIZE_IN_BYTE (16*1024*1024)
#define JPU_DRAM_PHYSICAL_BASE (0x8AA00000)
#include "jmm.h"
static jpu_mm_t s_jmem;
static jpudrv_buffer_t s_image_memory = {0};
#endif

static int jpu_hw_reset(void);
static void jpu_clk_disable(struct clk *clk);
static int jpu_clk_enable(struct clk *clk);
static struct clk *jpu_clk_get(struct device *dev);
static void jpu_clk_put(struct clk *clk);
// end customer definition

static jpudrv_buffer_t s_jpu_instance_pool = {0};
static jpu_drv_context_t s_jpu_drv_context;
static struct miscdevice s_jpu_dev;
static int s_jpu_open_count;
static struct clk *s_jpu_clk;
static struct reset_control *rstc_jpeg = NULL;
#ifdef JPU_SUPPORT_ISR
static int s_jpu_irq = JPU_IRQ_NUM;
static atomic_t s_interrupt_flag;
#endif
static unsigned long s_jpu_reg_phy_base = JPU_BASE_ADDR;
static void __iomem *s_jpu_reg_virt_base;
static jpudrv_buffer_t s_jpu_register = {0};
static jpudrv_buffer_t s_bonding_register = {0};

static unsigned long s_jpu_pll_phy_base = 0;
static void __iomem *s_jpu_pll_virt_base = NULL;
static unsigned long s_jpu_pll_size = 0;

static wait_queue_head_t s_interrupt_wait_q;
static int dbus_en = 1;

#define JPEG_DBUS_REG (0x0000 + 0xF00)

static spinlock_t s_jpu_lock = __SPIN_LOCK_UNLOCKED(s_jpu_lock);
static DEFINE_SEMAPHORE(s_jpu_sem);
static struct list_head s_jbp_head = LIST_HEAD_INIT(s_jbp_head);
static struct list_head s_jpu_inst_list_head = LIST_HEAD_INIT(s_jpu_inst_list_head);

/* implement to power management functions */
#define ReadJpuRegister(addr) *(volatile unsigned int *)(s_jpu_reg_virt_base + addr)
#define WriteJpuRegister(addr, val) *(volatile unsigned int *)(s_jpu_reg_virt_base + addr) = (unsigned int)val;

#if 0 /* Fuchun disable 20160204, set clock gating by jdi.c */
static void jpu_pll_setting(unsigned long offset, unsigned int value, unsigned int bOverwrite, unsigned int bEnable)
{
	if (s_jpu_pll_phy_base == 0 || s_jpu_pll_virt_base == 0 || s_jpu_pll_size == 0) {
		pr_warn("%s In[%s][%d] didn't get pll register\n", DEV_NAME, __FUNCTION__, __LINE__);
		return;
	} else if (offset > s_jpu_pll_size) {
		pr_warn("%s In[%s][%d] offset over than register size\n", DEV_NAME, __FUNCTION__, __LINE__);
		return;
	}

	if (bOverwrite == 1) {
		__raw_writel(value, (volatile u8 *)(s_jpu_pll_virt_base+offset));
	} else {
		if (bEnable)
			__raw_writel(__raw_readl((volatile u8 *)(s_jpu_pll_virt_base+offset)) | value, (volatile u8 *)(s_jpu_pll_virt_base+offset));
		else
			__raw_writel(__raw_readl((volatile u8 *)(s_jpu_pll_virt_base+offset)) & value, (volatile u8 *)(s_jpu_pll_virt_base+offset));
	}
}
#endif

static int jpu_alloc_dma_buffer(jpudrv_buffer_t *jb)
{
#ifdef JPU_SUPPORT_RESERVED_VIDEO_MEMORY
	jb->phys_addr = (unsigned long)jmem_alloc(&s_jmem, jb->size, 0);

	if ((unsigned long)jb->phys_addr  == (unsigned long)-1) {
		pr_err("%s Physical memory allocation error size=%d\n", DEV_NAME, jb->size);
		return -1;
	}

	jb->base = (unsigned long)(s_image_memory.base + (jb->phys_addr - s_image_memory.phys_addr));
#elif defined(CONFIG_RTK_RESERVE_MEMORY)
	unsigned int ret;
	ret = pu_alloc_dma_buffer(jb->size, &jb->phys_addr, &jb->base, 0);
	if (ret == -1) {
		pr_err("%s Physical memory allocation error size=%d\n", DEV_NAME, jb->size);
		return -1;
	}
#else
	jb->base = (unsigned long)dma_alloc_coherent(s_jpu_dev.this_device, PAGE_ALIGN(jb->size), (dma_addr_t *) (&jb->phys_addr), GFP_DMA | GFP_KERNEL);
	if ((void *)(jb->base) == NULL) {
		pr_err("%s Physical memory allocation error size=%d\n", DEV_NAME, jb->size);
		return -1;
	}
#endif
//	pr_info("%s base:0x%08x, phy_addr:0x%08x, size:%d\n", DEV_NAME, (unsigned int)jb->base, (unsigned int)jb->phys_addr, jb->size);
	return 0;
}

static void jpu_free_dma_buffer(jpudrv_buffer_t *jb)
{
#ifdef JPU_SUPPORT_RESERVED_VIDEO_MEMORY
	if (jb->base)
		jmem_free(&s_jmem, jb->phys_addr, 0);
#elif defined(CONFIG_RTK_RESERVE_MEMORY)
	pu_free_dma_buffer(jb->base, jb->phys_addr);
#else
	if (jb->base)
		dma_free_coherent(s_jpu_dev.this_device, PAGE_ALIGN(jb->size), (void *)jb->base, jb->phys_addr);
#endif
}

static int jpu_free_instances(struct file *filp)
{
	u32 inst_idx;
	jpudrv_instanace_list_t *jil, *n;
	jpudrv_instance_pool_t *jip;
	void *jip_base;
	void* jdi_mutex_base;
	const unsigned int PTHREAD_MUTEX_T_DESTROY_VALUE = 0xdead10cc;

	list_for_each_entry_safe(jil, n, &s_jpu_inst_list_head, list) {
		if (jil->filp == filp) {
			int i;
			for (i = 0; i < MAX_NUM_INSTANCE; i++) /* reset dovi flag */
			{
				pu_set_dovi_flag(2, i, 0);
			}

			inst_idx = jil->inst_idx;
			jip_base = (void *)(s_jpu_instance_pool.base);
			jip = (jpudrv_instance_pool_t *)jip_base;
			if (jip) {
				memset(&jip->jpgInstPool[inst_idx], 0x00, 4);	// only first 4 byte is key point to free the corresponding instance.
#define PTHREAD_MUTEX_T_HANDLE_SIZE 40
				jdi_mutex_base = (jip_base + (s_jpu_instance_pool.size - PTHREAD_MUTEX_T_HANDLE_SIZE));
				if (jdi_mutex_base) {
					memcpy(jdi_mutex_base, &PTHREAD_MUTEX_T_DESTROY_VALUE, PTHREAD_MUTEX_T_HANDLE_SIZE);
				}
			}
			s_jpu_open_count--;
			list_del(&jil->list);
			kfree(jil);
		}
	}

	return s_jpu_open_count;
}

static int jpu_free_buffers(struct file *filp)
{
	jpudrv_buffer_pool_t *pool, *n;
	jpudrv_buffer_t jb;

	list_for_each_entry_safe(pool, n, &s_jbp_head, list) {
		if (pool->filp == filp) {
			jb = pool->jb;
			if (jb.base) {
				jpu_free_dma_buffer(&jb);
				list_del(&pool->list);
				kfree(pool);
			}
		}
	}

	return 0;
}

#ifdef JPU_SUPPORT_ISR
static irqreturn_t jpu_irq_handler(int irq, void *dev_id)
{
	jpu_drv_context_t *dev = (jpu_drv_context_t *)dev_id;
#ifdef JPU_IRQ_CONTROL
	disable_irq_nosync(s_jpu_irq);
#endif

	dev->interrupt_reason = ReadJpuRegister(0x004); /* MJPEG_PIC_STATUS_REG */
	WriteJpuRegister(0x004, dev->interrupt_reason);
	if (dev->async_queue)
		kill_fasync(&dev->async_queue, SIGIO, POLL_IN); /* notify the interrupt to userspace */

	atomic_set(&s_interrupt_flag, 1);
	smp_wmb();

	//pr_info("%s jpu_irq_handler\n", DEV_NAME);
	wake_up_interruptible(&s_interrupt_wait_q);

	return IRQ_HANDLED;
}
#endif

static int jpu_open(struct inode *inode, struct file *filp)
{
	spin_lock(&s_jpu_lock);

	filp->private_data = (void *)(&s_jpu_drv_context);
	spin_unlock(&s_jpu_lock);
	return 0;
}

static long jpu_ioctl(struct file *filp, u_int cmd, u_long arg)
{
	int ret = 0;
	struct jpu_drv_context_t *dev = (struct jpu_drv_context_t *)filp->private_data;
	jpudrv_buffer_pool_t *jbp;
	jpudrv_buffer_pool_t *n;
	jpudrv_buffer_t jb;
	jpudrv_intr_info_t info;
	jpudrv_instanace_list_t *jil;
	jpudrv_instanace_list_t *tmp;
	jpudrv_dovi_info_t doviInfo;
	u32 inst_idx;
	u32 clkgate;
	u32 val;

	switch (cmd) {
	case JDI_IOCTL_ALLOCATE_PHYSICAL_MEMORY:
		down(&s_jpu_sem);

		jbp = kzalloc(sizeof(*jbp), GFP_KERNEL);
		if (!jbp) {
			up(&s_jpu_sem);
			return -ENOMEM;
		}

		ret = copy_from_user(&(jbp->jb), (jpudrv_buffer_t *)arg, sizeof(jpudrv_buffer_t));
		if (ret) {
			kfree(jbp);
			up(&s_jpu_sem);
			return -EFAULT;
		}

		ret = jpu_alloc_dma_buffer(&(jbp->jb));
		if (ret == -1) {
			ret = -ENOMEM;
			kfree(jbp);
			up(&s_jpu_sem);
			break;
		}

		ret = copy_to_user((void __user *)arg, &(jbp->jb), sizeof(jpudrv_buffer_t));
		if (ret) {
			kfree(jbp);
			ret = -EFAULT;
			up(&s_jpu_sem);
			break;
		}

		jbp->filp = filp;
		spin_lock(&s_jpu_lock);
		list_add(&jbp->list, &s_jbp_head);
		spin_unlock(&s_jpu_lock);

		up(&s_jpu_sem);
		break;
	case JDI_IOCTL_FREE_PHYSICALMEMORY:
		down(&s_jpu_sem);

		ret = copy_from_user(&jb, (jpudrv_buffer_t *)arg, sizeof(jpudrv_buffer_t));
		if (ret) {
			up(&s_jpu_sem);
			return -EACCES;
		}

		if (jb.base)
			jpu_free_dma_buffer(&jb);

		spin_lock(&s_jpu_lock);
		list_for_each_entry_safe(jbp, n, &s_jbp_head, list) {
			if (jbp->jb.phys_addr == jb.phys_addr) {
				list_del(&jbp->list);
				kfree(jbp);
				break;
			}
		}
		spin_unlock(&s_jpu_lock);

		up(&s_jpu_sem);
		break;
	case JDI_IOCTL_GET_RESERVED_VIDEO_MEMORY_INFO:
#ifdef JPU_SUPPORT_RESERVED_VIDEO_MEMORY
		if (s_image_memory.base != 0) {
			ret = copy_to_user((void __user *)arg, &s_image_memory, sizeof(jpudrv_buffer_t));
			if (ret != 0)
				ret = -EFAULT;
		} else {
			ret = -EFAULT;
		}
#endif
		break;
#ifdef JPU_SUPPORT_ISR
	case JDI_IOCTL_WAIT_INTERRUPT:
		ret = copy_from_user(&info, (jpudrv_intr_info_t*)arg, sizeof(jpudrv_intr_info_t));
		if (ret != 0)
			return -EFAULT;

		smp_rmb();
		ret = wait_event_interruptible_timeout(s_interrupt_wait_q, atomic_read(&s_interrupt_flag) != 0, msecs_to_jiffies(info.timeout));
		if (!ret) {
			ret = -ETIME;
			//pr_info("%s JDI_IOCTL_WAIT_INTERRUPT fail\n", DEV_NAME);
			break;
		}

		if (signal_pending(current)) {
			ret = -ERESTARTSYS;
			break;
		}

		atomic_set(&s_interrupt_flag, 0);
		smp_wmb();
		info.intr_reason = dev->interrupt_reason;
		ret = copy_to_user((void __user *)arg, &info, sizeof(jpudrv_intr_info_t));
		if (ret != 0)
			return -EFAULT;

		//pr_info("%s JDI_IOCTL_WAIT_INTERRUPT done, info.intr_reason:0x%x\n", DEV_NAME, info.intr_reason);
		break;
#endif /* JPU_SUPPORT_ISR */
	case JDI_IOCTL_ENABLE_INTERRUPT:
#ifdef JPU_IRQ_CONTROL
		enable_irq(s_jpu_irq);
#endif
		break;
	case JDI_IOCTL_SET_CLOCK_GATE:
		if (get_user(clkgate, (u32 __user *) arg))
			return -EFAULT;

#ifdef JPU_SUPPORT_CLOCK_CONTROL
		if (clkgate)
			jpu_clk_enable(s_jpu_clk);
		else
			jpu_clk_disable(s_jpu_clk);
#endif

		break;
	case JDI_IOCTL_GET_INSTANCE_POOL:
		down(&s_jpu_sem);

		if (s_jpu_instance_pool.base != 0) {
			ret = copy_to_user((void __user *)arg, &s_jpu_instance_pool, sizeof(jpudrv_buffer_t));
			if (ret != 0)
				ret = -EFAULT;
		} else {
			ret = copy_from_user(&s_jpu_instance_pool, (jpudrv_buffer_t *)arg, sizeof(jpudrv_buffer_t));
			if (ret == 0) {
#ifdef J_USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY
				s_jpu_instance_pool.size = PAGE_ALIGN(s_jpu_instance_pool.size);
				s_jpu_instance_pool.base = (unsigned long)vmalloc(s_jpu_instance_pool.size);
				s_jpu_instance_pool.phys_addr = s_jpu_instance_pool.base;

				if (s_jpu_instance_pool.base != 0)
#else
				if (jpu_alloc_dma_buffer(&s_jpu_instance_pool) != -1)
#endif
				{
					memset((void *)s_jpu_instance_pool.base, 0x0, s_jpu_instance_pool.size);
					ret = copy_to_user((void __user *)arg, &s_jpu_instance_pool, sizeof(jpudrv_buffer_t));
					if (ret == 0) {
						// success to get memory for instance pool
						up(&s_jpu_sem);
						break;
					}
				}
			}
			ret = -EFAULT;
		}
		up(&s_jpu_sem);

		break;
	case JDI_IOCTL_OPEN_INSTANCE:
		jil = kzalloc(sizeof(*jil), GFP_KERNEL);
		if (!jil)
			return -ENOMEM;

		if (get_user(inst_idx, (u32 __user *) arg))
			return -EFAULT;

		jil->inst_idx = inst_idx;
		jil->filp = filp;
		spin_lock(&s_jpu_lock);
		list_add(&jil->list, &s_jpu_inst_list_head);
		s_jpu_open_count++;
		spin_unlock(&s_jpu_lock);
		break;
	case JDI_IOCTL_CLOSE_INSTANCE:
		if (get_user(inst_idx, (u32 __user *) arg))
			return -EFAULT;

		spin_lock(&s_jpu_lock);

		list_for_each_entry_safe(jil, tmp, &s_jpu_inst_list_head, list) {
			if (jil->inst_idx == inst_idx) {
				s_jpu_open_count--;
				list_del(&jil->list);
				kfree(jil);
//				printk(KERN_INFO "[JPUDRV] JDI_IOCTL_CLOSE_INSTANCE inst_idx=%d, open_count=%d\n", (int)inst_idx, s_jpu_open_count);
				break;
			}
		}
		spin_unlock(&s_jpu_lock);
		break;
	case JDI_IOCTL_GET_INSTANCE_NUM:
		down(&s_jpu_sem);

		ret = copy_to_user((void __user *)arg, &s_jpu_open_count, sizeof(int));
		if (ret != 0)
			ret = -EFAULT;

		//printk(KERN_INFO "[JPUDRV] VDI_IOCTL_GET_INSTANCE_NUM open_count=%d\n", s_jpu_open_count);

		up(&s_jpu_sem);
		break;
	case JDI_IOCTL_RESET:
		jpu_hw_reset();
		break;
	case JDI_IOCTL_GET_REGISTER_INFO:
		ret = copy_to_user((void __user *)arg, &s_jpu_register, sizeof(jpudrv_buffer_t));
		if (ret != 0)
			ret = -EFAULT;
		break;
	case JDI_IOCTL_GET_BONDING_INFO:
		ret = copy_to_user((void __user *)arg, &s_bonding_register, sizeof(jpudrv_buffer_t));
		if (ret != 0)
			ret = -EFAULT;
		break;
	case JDI_IOCTL_SET_CLOCK_ENABLE:

		if (get_user(clkgate, (u32 __user *) arg))
			return -EFAULT;

		if (clkgate) {
			reset_control_deassert(rstc_jpeg);
			jpu_clk_enable(s_jpu_clk);
			val = ReadJpuRegister(JPEG_DBUS_REG);
			val |= (dbus_en << 0);
			val &= ~(1 << 1); //Disable idle gating, fix it later.
			WriteJpuRegister(JPEG_DBUS_REG, val);
		} else {
			jpu_clk_disable(s_jpu_clk);
			reset_control_assert(rstc_jpeg);
		}
		break;
	case JDI_IOCTL_SET_RTK_DOVI_FLAG:
		//pr_info("%s [+]JDI_IOCTL_SET_RTK_DOVI_FLAG\n", DEV_NAME);
		ret = copy_from_user(&doviInfo, (jpudrv_dovi_info_t *)arg, sizeof(jpudrv_dovi_info_t));
		if (ret != 0)
			break;

		doviInfo.enable = pu_set_dovi_flag(2, doviInfo.inst_idx, doviInfo.enable);

		ret = copy_to_user((jpudrv_dovi_info_t *)arg, &doviInfo, sizeof(jpudrv_dovi_info_t));
		if (ret != 0)
			break;
		//pr_info("%s [-]JDI_IOCTL_SET_RTK_DOVI_FLAG doviInfo.inst_idx:%d, doviInfo.value:%d\n", DEV_NAME, doviInfo.inst_idx, doviInfo.enable);
		break;
	default:
		printk(KERN_ERR "No such IOCTL, cmd is %d\n", cmd);
		break;
	}

	return ret;
}

static ssize_t jpu_read(struct file *filp, char __user *buf, size_t len, loff_t *ppos)
{
	return -1;
}

static ssize_t jpu_write(struct file *filp, const char __user *buf, size_t len, loff_t *ppos)
{

	return -1;
}

static int jpu_release(struct inode *inode, struct file *filp)
{
//	pr_info("%s jpu_release s_jpu_open_count=%d\n", DEV_NAME, s_jpu_open_count);

	spin_lock(&s_jpu_lock);


	if (s_jpu_open_count > 0) {
		/* found and free the not handled buffer by user applications */
		jpu_free_buffers(filp);

		/* found and free the not closed instance by user applications */
		jpu_free_instances(filp);
	}

#if 1 //Fuchun 20150909, we must not free instance pool and common memory
	if (s_jpu_open_count == 0) {
		if (s_jpu_instance_pool.base) {
#ifdef J_USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY
			vfree((const void *)s_jpu_instance_pool.base);
#else
			jpu_free_dma_buffer(&s_jpu_instance_pool);
#endif
			s_jpu_instance_pool.base = 0;
//			pr_info("%s jpu_release - free s_jpu_instance_pool\n", DEV_NAME);
		}
	}
#endif

	spin_unlock(&s_jpu_lock);

	return 0;
}

static int jpu_fasync(int fd, struct file *filp, int mode)
{
	struct jpu_drv_context_t *dev = (struct jpu_drv_context_t *)filp->private_data;
	return fasync_helper(fd, filp, mode, &dev->async_queue);
}

static int jpu_map_to_register(struct file *fp, struct vm_area_struct *vm)
{
	unsigned long pfn;

	vm->vm_flags |= VM_IO | VM_RESERVED;
	vm->vm_page_prot = pgprot_noncached(vm->vm_page_prot);
	pfn = vm->vm_pgoff;

	return remap_pfn_range(vm, vm->vm_start, pfn, vm->vm_end-vm->vm_start, vm->vm_page_prot) ? -EAGAIN : 0;
}

static int jpu_map_to_physical_memory(struct file *fp, struct vm_area_struct *vm)
{
#ifdef CONFIG_RTK_RESERVE_MEMORY
	return pu_mmap_dma_buffer(vm);
#else
	vm->vm_flags |= VM_IO | VM_RESERVED;
	vm->vm_page_prot = pgprot_writecombine(vm->vm_page_prot);

	return remap_pfn_range(vm, vm->vm_start, vm->vm_pgoff, vm->vm_end-vm->vm_start, vm->vm_page_prot) ? -EAGAIN : 0;
#endif
}

static int jpu_map_to_instance_pool_memory(struct file *fp, struct vm_area_struct *vm)
{
#ifdef J_USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY
	int ret;
	long length = vm->vm_end - vm->vm_start;
	unsigned long start = vm->vm_start;
	char *vmalloc_area_ptr = (char *)s_jpu_instance_pool.base;
	unsigned long pfn;

	vm->vm_flags |= VM_RESERVED;

	/* loop over all pages, map it page individually */
	while (length > 0) {
		pfn = vmalloc_to_pfn(vmalloc_area_ptr);
		if ((ret = remap_pfn_range(vm, start, pfn, PAGE_SIZE, PAGE_SHARED)) < 0) {
			return ret;
		}
		start += PAGE_SIZE;
		vmalloc_area_ptr += PAGE_SIZE;
		length -= PAGE_SIZE;
	}

	return 0;
#else
	vm->vm_flags |= VM_IO | VM_RESERVED;
	vm->vm_page_prot = pgprot_noncached(vm->vm_page_prot);
	return remap_pfn_range(vm, vm->vm_start, vm->vm_pgoff, vm->vm_end-vm->vm_start, vm->vm_page_prot) ? -EAGAIN : 0;
#endif
}

/*!
 * @brief memory map interface for jpu file operation
 * @return  0 on success or negative error code on error
 */
static int jpu_mmap(struct file *fp, struct vm_area_struct *vm)
{
#ifdef J_USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY
	if (vm->vm_pgoff == 0)
		return jpu_map_to_instance_pool_memory(fp, vm);

	if ((vm->vm_pgoff == (s_jpu_register.phys_addr>>PAGE_SHIFT)) || (vm->vm_pgoff == (s_bonding_register.phys_addr>>PAGE_SHIFT)))
		return jpu_map_to_register(fp, vm);

	return jpu_map_to_physical_memory(fp, vm);
#else
	if (vm->vm_pgoff) {
		if (vm->vm_pgoff == (s_jpu_instance_pool.phys_addr>>PAGE_SHIFT))
			return  jpu_map_to_instance_pool_memory(fp, vm);

		return jpu_map_to_physical_memory(fp, vm);
	} else
		return jpu_map_to_register(fp, vm);
#endif
}

struct file_operations jpu_fops = {
	.owner = THIS_MODULE,
	.open = jpu_open,
	.read = jpu_read,
	.write = jpu_write,
	.unlocked_ioctl = jpu_ioctl,
	.compat_ioctl   = compat_jpu_ioctl,
	.release = jpu_release,
	.fasync = jpu_fasync,
	.mmap = jpu_mmap,
};

static int jpu_probe(struct platform_device *pdev)
{
	int err = 0;
	struct resource res;
	void __iomem *iobase;
	int irq;
	struct device_node *node = pdev->dev.of_node;

	pr_info("%s jpu_probe\n", DEV_NAME);

	of_address_to_resource(node, 0, &res);
	iobase = of_iomap(node, 0);

	s_jpu_reg_phy_base = res.start;
	s_jpu_reg_virt_base = iobase;
	s_jpu_register.phys_addr = res.start;
	s_jpu_register.virt_addr = (unsigned long)iobase;
	s_jpu_register.size = res.end - res.start + 1;

	pr_info("%s jpu base address get from DTB physical base addr=0x%lx, virtual base=0x%lx, size=0x%x\n", DEV_NAME, (unsigned long)s_jpu_reg_phy_base, (unsigned long)s_jpu_reg_virt_base, (unsigned int)(res.end - res.start + 1));

	of_address_to_resource(node, 1, &res);
	iobase = of_iomap(node, 1);

	s_jpu_pll_phy_base = res.start;
	s_jpu_pll_virt_base = iobase;
	s_jpu_pll_size = res.end - res.start + 1;

	of_address_to_resource(node, 2, &res);
	iobase = of_iomap(node, 2);

	s_bonding_register.phys_addr = res.start;
	s_bonding_register.virt_addr = (unsigned long)iobase;
	s_bonding_register.size = res.end - res.start + 1;

	s_jpu_dev.minor = MISC_JPU_MINOR;
	s_jpu_dev.name = JPU_DEV_NAME;
	s_jpu_dev.fops = &jpu_fops;
	s_jpu_dev.parent = NULL;
	if (misc_register(&s_jpu_dev)) {
		pr_info("%s failed to register misc device.", DEV_NAME);
		goto ERROR_PROVE_DEVICE;
	}

	if (pdev)
		s_jpu_clk = jpu_clk_get(&pdev->dev);
	else
		s_jpu_clk = jpu_clk_get(NULL);

	if (!s_jpu_clk)
		pr_err("%s fail to get clock controller, but, do not treat as error, \n", DEV_NAME);
	else
		pr_info("%s get clock controller s_jpu_clk=0x%p\n", DEV_NAME, s_jpu_clk);

#ifdef JPU_SUPPORT_CLOCK_CONTROL
	jpu_clk_enable(s_jpu_clk);
#endif

	rstc_jpeg = reset_control_get(&pdev->dev, NULL);

	/* RTK clock setting */
	reset_control_deassert(rstc_jpeg); // RESET disable
#if 0 //Fuchun disable 20160204, set clock gating by jdi.c
	jpu_pll_setting(0x10, (1 << jpg_clk_enable_bit), 0, 1); // CLK enable

	val = ReadJpuRegister(JPEG_DBUS_REG);
	val |= (dbus_en << 0);
	WriteJpuRegister(JPEG_DBUS_REG, val);
#endif

#ifdef JPU_SUPPORT_ISR
	irq = irq_of_parse_and_map(node, 0);
	if (irq <= 0)
		panic("Can't parse IRQ");

	s_jpu_irq = irq;
	pr_info("%s s_jpu_irq:%d want to register jpu_irq_handler\n", DEV_NAME, s_jpu_irq);
	err = request_irq(s_jpu_irq, jpu_irq_handler, 0, "JPEG_CODEC_IRQ", (void *)(&s_jpu_drv_context));
	err = 0;
	if (err != 0) {
		if (err == -EINVAL)
			pr_err("%s Bad s_jpu_irq number or handler\n", DEV_NAME);
		else if (err == -EBUSY)
			pr_err("%s s_jpu_irq <%d> busy, change your config\n", DEV_NAME, s_jpu_irq);

		goto ERROR_PROVE_DEVICE;
	}
#endif

#ifdef JPU_SUPPORT_RESERVED_VIDEO_MEMORY
	s_image_memory.size = JPU_INIT_VIDEO_MEMORY_SIZE_IN_BYTE;
	s_image_memory.phys_addr = JPU_DRAM_PHYSICAL_BASE;
	s_image_memory.base = (unsigned long)ioremap(s_image_memory.phys_addr, PAGE_ALIGN(s_image_memory.size));

	if (!s_image_memory.base) {
		pr_err("%s fail to remap video memory physical phys_addr=0x%x, base=0x%x, size=%d\n", DEV_NAME, (int)s_image_memory.phys_addr, (int)s_image_memory.base, (int)s_image_memory.size);
		goto ERROR_PROVE_DEVICE;
	}

	if (jmem_init(&s_jmem, s_image_memory.phys_addr, s_image_memory.size) < 0) {
		pr_err("%s fail to init vmem system\n", DEV_NAME);
		goto ERROR_PROVE_DEVICE;
	}

	pr_info("%s success to probe jpu device with reserved video memory phys_addr=0x%x, base = 0x%x\n", DEV_NAME, (int) s_image_memory.phys_addr, (int)s_image_memory.base);
#else
	pr_info("%s success to probe jpu device with non reserved video memory\n", DEV_NAME);
#endif

	reset_control_assert(rstc_jpeg);

	return 0;


ERROR_PROVE_DEVICE:

	misc_deregister(&s_jpu_dev);

	if (s_jpu_reg_virt_base)
		iounmap(s_jpu_reg_virt_base);

	return err;
}

static int jpu_remove(struct platform_device *pdev)
{
#ifdef JPU_SUPPORT_PLATFORM_DRIVER_REGISTER

	pr_info("%s jpu_remove\n", DEV_NAME);

	if (s_jpu_instance_pool.base) {
#ifdef J_USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY
		vfree((const void *)s_jpu_instance_pool.base);
#else
		jpu_free_dma_buffer(&s_jpu_instance_pool);
#endif
		s_jpu_instance_pool.base = 0;
	}
#ifdef JPU_SUPPORT_RESERVED_VIDEO_MEMORY
	if (s_image_memory.base) {
		iounmap((void *)s_image_memory.base);
		s_image_memory.base = 0;
		jmem_exit(&s_jmem);
	}
#endif

	misc_deregister(&s_jpu_dev);

#ifdef JPU_SUPPORT_ISR
	if (s_jpu_irq)
		free_irq(s_jpu_irq, &s_jpu_drv_context);
#endif

	if (s_jpu_reg_virt_base)
		iounmap(s_jpu_reg_virt_base);

	if (rstc_jpeg != NULL)
		reset_control_put(rstc_jpeg);

	jpu_clk_put(s_jpu_clk);

#endif //JPU_SUPPORT_PLATFORM_DRIVER_REGISTER

	return 0;
}

#ifdef CONFIG_PM
static int jpu_suspend(struct device *pdev)
{
	pr_info("%s Enter %s\n", DEV_NAME, __func__);

	reset_control_deassert(rstc_jpeg);
	jpu_clk_enable(s_jpu_clk);
#if 0
	if (s_jpu_open_count > 0) {
		u32 inst_idx;
		jpudrv_instanace_list_t *jil, *n;
		jpudrv_instance_pool_t *jip;
		void *jip_base;
		jpudrv_buffer_pool_t *pool, *n;
		jpudrv_buffer_t jb;

		s_jpu_open_count = 0;
		atomic_set(&s_interrupt_flag, 0);
		wake_up_interruptible_all(&s_interrupt_wait_q);

		if (s_jpu_instance_pool.base) {
#ifdef J_USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY
			vfree((const void *)s_jpu_instance_pool.base);
#else
			jpu_free_dma_buffer(&s_jpu_instance_pool);
#endif
			s_jpu_instance_pool.base = 0;
			pr_info("%s jpu_release - free s_jpu_instance_pool\n", DEV_NAME);
		}

		list_for_each_entry_safe(jil, n, &s_jpu_inst_list_head, list) {
			inst_idx = jil->inst_idx;
			jip_base = (void *)(s_jpu_instance_pool.base);
			jip = (jpudrv_instance_pool_t *)jip_base;
			if (jip) {
				memset(&jip->jpgInstPool[inst_idx], 0x00, 4);	// only first 4 byte is key point to free the corresponding instance.
			}
			list_del(&jil->list);
			kfree(jil);
		}

		list_for_each_entry_safe(pool, n, &s_jbp_head, list) {
			jb = pool->jb;
			if (jb.base) {
				jpu_free_dma_buffer(&jb);
				list_del(&pool->list);
				kfree(pool);
			}
		}
	}
#endif
	jpu_clk_disable(s_jpu_clk);
	reset_control_assert(rstc_jpeg);

	pr_info("%s Exit %s\n", DEV_NAME, __func__);

	return 0;

}

static int jpu_resume(struct device *pdev)
{
	pr_info("%s Enter %s\n", DEV_NAME, __func__);

	reset_control_deassert(rstc_jpeg);
	jpu_clk_enable(s_jpu_clk);
	jpu_clk_disable(s_jpu_clk);
	reset_control_assert(rstc_jpeg);

	pr_info("%s Exit %s\n", DEV_NAME, __func__);

	return 0;
}
#else
#define jpu_suspend NULL
#define jpu_resume NULL
#endif /* !CONFIG_PM */

static int __init jpu_init(void)
{
	int res;
	res = 0;

	pr_info("%s jpu_init\n", DEV_NAME);
	init_waitqueue_head(&s_interrupt_wait_q);
	s_jpu_instance_pool.base = 0;

	pr_info("%s end jpu_init result=0x%x\n", DEV_NAME, res);
	return res;
}

static void __exit jpu_exit(void)
{
#ifdef JPU_SUPPORT_PLATFORM_DRIVER_REGISTER
	pr_info("%s jpu_exit\n", DEV_NAME);
#else
	if (s_jpu_instance_pool.base) {
#ifdef J_USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY
		vfree((const void *)s_jpu_instance_pool.base);
#else
		jpu_free_dma_buffer(&s_jpu_instance_pool);
#endif
		s_jpu_instance_pool.base = 0;
	}
#ifdef JPU_SUPPORT_RESERVED_VIDEO_MEMORY
	if (s_image_memory.base) {
		iounmap((void *)s_image_memory.base);
		s_image_memory.base = 0;
	}
#endif

	misc_deregister(&s_jpu_dev);

#ifdef JPU_SUPPORT_ISR
	if (s_jpu_irq)
		free_irq(s_jpu_irq, &s_jpu_drv_context);
#endif

	if (rstc_jpeg != NULL)
		reset_control_put(rstc_jpeg);

	jpu_clk_put(s_jpu_clk);


	if (s_jpu_reg_virt_base) {
		iounmap(s_jpu_reg_virt_base);
		s_jpu_reg_virt_base = (void *)0x00;
	}

#endif //JPU_SUPPORT_PLATFORM_DRIVER_REGISTER

	return;
}

MODULE_AUTHOR("A customer using RTK JPU, Inc.");
MODULE_DESCRIPTION("JPU linux driver");
MODULE_LICENSE("GPL");

module_init(jpu_init);
module_exit(jpu_exit);

int jpu_hw_reset(void)
{
	u32 val;

	pr_info("%s request jpu reset from application\n", DEV_NAME);
	jpu_clk_disable(s_jpu_clk);
	reset_control_reset(rstc_jpeg);
	jpu_clk_enable(s_jpu_clk);
	val = ReadJpuRegister(JPEG_DBUS_REG);
	val |= (dbus_en << 0);
	val &= ~(1 << 1); //Disable idle gating, fix it later.
	WriteJpuRegister(JPEG_DBUS_REG, val);
	return 0;
}

struct clk *jpu_clk_get(struct device *dev)
{
	return clk_get(dev, JPU_CLK_NAME);
}

void jpu_clk_put(struct clk *clk)
{
	if (!(clk == NULL || IS_ERR(clk)))
		clk_put(clk);
}

int jpu_clk_enable(struct clk *clk)
{
	if (!(clk == NULL || IS_ERR(clk))) {
//		pr_info("%s jpu_clk_enable\n", DEV_NAME);
		return clk_prepare_enable(clk);
	}
	return 0;
}

void jpu_clk_disable(struct clk *clk)
{
	if (!(clk == NULL || IS_ERR(clk))) {
//		pr_info("%s jpu_clk_disable\n", DEV_NAME);
		clk_disable_unprepare(clk);
	}
}

static const struct of_device_id rtk_jpeg_dt_match[] = {
	{ .compatible = "Realtek,rtk1295-jpeg" },
	{}
};
MODULE_DEVICE_TABLE(of, rtk_jpeg_dt_match);

const struct dev_pm_ops rtk_jpeg_pmops = {
	.suspend = jpu_suspend,
	.resume = jpu_resume,
};

static struct platform_driver rtk_jpeg_driver = {
	.driver = {
		.name = "rtk-jpeg",
		.owner = THIS_MODULE,
		.of_match_table = rtk_jpeg_dt_match,
		.pm = &rtk_jpeg_pmops,
	},
	.probe = jpu_probe,
	.remove = jpu_remove,
};

module_platform_driver(rtk_jpeg_driver);
