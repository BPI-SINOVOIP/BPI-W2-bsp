
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
#include "jpuconfig.h"

#include "jpu.h"
#include "../puwrap.h"

#ifdef CONFIG_RTK_RESERVE_MEMORY
extern unsigned int pu_alloc_dma_buffer(unsigned int size, unsigned long long *phys_addr, unsigned long *base);
extern void pu_free_dma_buffer(unsigned long base, unsigned long long phys_addr);
#endif
extern void *pu_get_drv_context(void);


// definitions to be changed as customer  configuration
//#define JPU_SUPPORT_CLOCK_CONTROL				/if you want to have clock gating scheme frame by frame
//#define JPU_SUPPORT_ISR
//#define JPU_SUPPORT_PLATFORM_DRIVER_REGISTER	//if the platform driver knows the name of this driver. JPU_PLATFORM_DEVICE_NAME 
//#define JPU_SUPPORT_RESERVED_VIDEO_MEMORY		//if this driver knows the dedicated video memory address

#define JPU_PLATFORM_DEVICE_NAME "rtk_jpu"
#define JPU_CLK_NAME "jpeg"
#define JPU_DEV_NAME "jpu"

#define JPU_BASE_ADDR 0x18044000
#define JPU_REG_SIZE 0x4000

#define JPU_VIRT_ADDR_MAP(addr)	(RBUS_BASE_VIRT + ((u32)addr - RBUS_BASE_PHYS))
#define JPU_WRITE_REG_INT32U(addr,val)	writel(val, IOMEM(JPU_VIRT_ADDR_MAP(addr)))

#define JPU_CLOCK_REG_BASE		0x18000000
#define JPU_CLOCK_ENABLE_REG		0x1800000c


//#ifdef JPU_SUPPORT_ISR
#define JPU_IRQ_NUM 83			
//#endif

#ifndef VM_RESERVED	// for kernel up to 3.7.0 version
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
#if 0
static int s_jpu_major;
static struct class *s_jpu_class = NULL;
static struct device *s_jpu_dev = NULL;
static struct cdev s_jpu_cdev;
#else
static struct miscdevice s_jpu_dev;
#endif
static int s_jpu_open_count;
static struct clk *s_jpu_clk;
//#ifdef JPU_SUPPORT_ISR
static int s_jpu_irq = JPU_IRQ_NUM;
static atomic_t s_interrupt_flag;
//#endif
static u32 s_jpu_reg_phy_base = JPU_BASE_ADDR;
static void __iomem *s_jpu_reg_virt_base;


static wait_queue_head_t s_interrupt_wait_q;


static spinlock_t s_jpu_lock = __SPIN_LOCK_UNLOCKED(s_jpu_lock);
static DEFINE_SEMAPHORE(s_jpu_sem);
static struct list_head s_jbp_head = LIST_HEAD_INIT(s_jbp_head);
static struct list_head s_jpu_inst_list_head = LIST_HEAD_INIT(s_jpu_inst_list_head);

/* implement to power management functions */
#define	ReadJpuRegister(addr)			*(volatile unsigned int *)(s_jpu_reg_virt_base + addr)
#define	WriteJpuRegister(addr, val)		*(volatile unsigned int *)(s_jpu_reg_virt_base + addr) = (unsigned int)val;	

static int jpu_alloc_dma_buffer(jpudrv_buffer_t *jb)
{
#ifdef JPU_SUPPORT_RESERVED_VIDEO_MEMORY
	jb->phys_addr = (unsigned long long)jmem_alloc(&s_jmem, jb->size, 0);
	if ((unsigned long)jb->phys_addr  == (unsigned long)-1)
	{
		printk(KERN_ERR "[JPUDRV] Physical memory allocation error size=%d\n", jb->size);
		return -1;
	}

	jb->base = (unsigned long)(s_image_memory.base + (jb->phys_addr - s_image_memory.phys_addr));
#elif CONFIG_RTK_RESERVE_MEMORY
	unsigned int ret;
	ret = pu_alloc_dma_buffer(jb->size, &jb->phys_addr, &jb->base);
	if(ret == -1)
	{
		printk(KERN_ERR "[JPUDRV] Physical memory allocation error size=%d\n", jb->size);
		return -1;
	}
#else
	jb->base = (unsigned long)dma_alloc_coherent(NULL, PAGE_ALIGN(jb->size), (dma_addr_t *) (&jb->phys_addr), GFP_DMA | GFP_KERNEL);
	if ((void *)(jb->base) == NULL) 
	{
		printk(KERN_ERR "[JPUDRV] Physical memory allocation error size=%d\n", jb->size);
		return -1;
	}
#endif
	printk("[JPUDRV] base:0x%08x, phy_addr:0x%08x, size:%d\n", jb->base, (unsigned long)jb->phys_addr, jb->size);
	return 0;
}

static void jpu_free_dma_buffer(jpudrv_buffer_t *jb)
{
#ifdef JPU_SUPPORT_RESERVED_VIDEO_MEMORY
	if (jb->base) 
		jmem_free(&s_jmem, jb->phys_addr, 0);
#elif CONFIG_RTK_RESERVE_MEMORY
	pu_free_dma_buffer(jb->base, jb->phys_addr);
#else
	if (jb->base) 
	{
		dma_free_coherent(0, PAGE_ALIGN(jb->size), (void *)jb->base, jb->phys_addr);
	}
#endif
}

static int jpu_free_instances(struct file *filp) 
{
	u32 inst_idx;
	jpudrv_instanace_list_t *jil, *n;
	jpudrv_instance_pool_t *jip;

	list_for_each_entry_safe(jil, n, &s_jpu_inst_list_head, list) 
	{
		if (jil->filp == filp)
		{
			inst_idx = jil->inst_idx;
			jip = (jpudrv_instance_pool_t *)s_jpu_instance_pool.base;
			if (jip)
				memset(&jip->jpgInstPool[inst_idx], 0x00, 4);	// only first 4 byte is key point to free the corresponding instance.				
			s_jpu_open_count--;
			list_del(&jil->list);
			kfree(jil);		
		}
	}

	return 1;
}

static int jpu_free_buffers(struct file *filp)
{
	jpudrv_buffer_pool_t *pool, *n;
	jpudrv_buffer_t jb;

	list_for_each_entry_safe(pool, n, &s_jbp_head, list) 
	{
		if (pool->filp == filp)
		{
			jb = pool->jb;
			if (jb.base) 
			{
				jpu_free_dma_buffer(&jb);
				list_del(&pool->list);
				kfree(pool);
			}
		}
		
	}

	return 0;
}

void jpu_irq_handler2(void *dev_id)
{
	pu_drv_context_t *dev = (pu_drv_context_t *)dev_id;
	disable_irq_nosync(s_jpu_irq); //Fuchun 20140407 wait IP vendor reply that how to fix this

	dev->jpu_interrupt_reason = ReadJpuRegister(0x004); //MJPEG_PIC_STATUS_REG
	//WriteJpuRegister(0x004, dev->jpu_interrupt_reason);
	atomic_set(&s_interrupt_flag, 1);
	//printk(KERN_INFO "jpu_irq_handler2, status:0x%08x, dev:%p\n", dev->jpu_interrupt_reason, dev);
	wake_up_interruptible(&s_interrupt_wait_q);
}

#ifdef JPU_SUPPORT_ISR
static irqreturn_t jpu_irq_handler(int irq, void *dev_id)
{
	jpu_drv_context_t *dev = (jpu_drv_context_t *)dev_id;

	disable_irq_nosync(s_jpu_irq);
	
	if (dev->async_queue)
		kill_fasync(&dev->async_queue, SIGIO, POLL_IN);	// notify the interrupt to userspace
	
	
	atomic_set(&s_interrupt_flag, 1);
	//printk(KERN_INFO "jpu_irq_handler\n");	
	wake_up_interruptible(&s_interrupt_wait_q);
	
	return IRQ_HANDLED;
}
#endif

static int jpu_open(struct inode *inode, struct file *filp)
{
	spin_lock(&s_jpu_lock);

#ifdef JPU_SUPPORT_ISR
	filp->private_data = (void *)(&s_jpu_drv_context);
#else
	void *drv_context = pu_get_drv_context();
	filp->private_data = (void *)(drv_context);
#endif
	spin_unlock(&s_jpu_lock);
	return 0;
}

static long jpu_ioctl(struct file *filp, u_int cmd, u_long arg)
{
	int ret = 0;
	struct pu_drv_context_t *dev = (struct pu_drv_context_t *)filp->private_data;

	switch (cmd) 
	{
	case JDI_IOCTL_ALLOCATE_PHYSICAL_MEMORY:
		{
			jpudrv_buffer_pool_t *jbp;

			down(&s_jpu_sem);

			jbp = kzalloc(sizeof(*jbp), GFP_KERNEL);
			if (!jbp)
			{
				up(&s_jpu_sem);
				return -ENOMEM;
			}

			ret = copy_from_user(&(jbp->jb), (jpudrv_buffer_t *)arg, sizeof(jpudrv_buffer_t));
			if (ret) 
			{
				kfree(jbp);
				up(&s_jpu_sem);
				return -EFAULT;
			}

			ret = jpu_alloc_dma_buffer(&(jbp->jb));
			if (ret == -1) 
			{
				ret = -ENOMEM;
				kfree(jbp);
				up(&s_jpu_sem);
				break;
			}

			ret = copy_to_user((void __user *)arg, &(jbp->jb), sizeof(jpudrv_buffer_t));
			if (ret) 
			{
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

		}
		break;
	case JDI_IOCTL_FREE_PHYSICALMEMORY:
		{

			jpudrv_buffer_pool_t *jbp, *n;
			jpudrv_buffer_t jb;

			down(&s_jpu_sem);

			ret = copy_from_user(&jb, (jpudrv_buffer_t *)arg, sizeof(jpudrv_buffer_t));
			if (ret)
			{
				up(&s_jpu_sem);
				return -EACCES;
			}

			if (jb.base) 
				jpu_free_dma_buffer(&jb);

			spin_lock(&s_jpu_lock);
			list_for_each_entry_safe(jbp, n, &s_jbp_head, list) 
			{
				if (jbp->jb.base == jb.base) 
				{
					list_del(&jbp->list);
					kfree(jbp);
					break;
				}
			}
			spin_unlock(&s_jpu_lock);

			up(&s_jpu_sem);

		}
		break;

	case JDI_IOCTL_GET_RESERVED_VIDEO_MEMORY_INFO:
		{
#ifdef JPU_SUPPORT_RESERVED_VIDEO_MEMORY
			if (s_image_memory.base != 0) 
			{
				ret = copy_to_user((void __user *)arg, &s_image_memory, sizeof(jpudrv_buffer_t));
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

//#ifdef JPU_SUPPORT_ISR
	case JDI_IOCTL_WAIT_INTERRUPT:
		{
			jpudrv_intr_info_t info;

			ret = copy_from_user(&info, (jpudrv_intr_info_t*)arg, sizeof(jpudrv_intr_info_t));
			if (ret != 0)
				return -EFAULT;
			//printk("[JPUDRV] JDI_IOCTL_WAIT_INTERRUPT\n");
			smp_rmb();
			ret = wait_event_interruptible_timeout(s_interrupt_wait_q, atomic_read(&s_interrupt_flag) != 0, msecs_to_jiffies(info.timeout));
			if (!ret)
			{
				ret = -ETIME;
				//printk("[JPUDRV] JDI_IOCTL_WAIT_INTERRUPT fail\n");
				break;
			} 
			
			if (signal_pending(current)) 
			{
				ret = -ERESTARTSYS;
				break;
			} 
			
			atomic_set(&s_interrupt_flag, 0);
			info.intr_reason = dev->jpu_interrupt_reason;
			ret = copy_to_user((void __user *)arg, &info, sizeof(jpudrv_intr_info_t));
			if (ret != 0)
				return -EFAULT;

			//printk("[JPUDRV] JDI_IOCTL_WAIT_INTERRUPT done, info.intr_reason:0x%x\n", info.intr_reason);
		}
		break;
//#endif	//JPU_SUPPORT_ISR

	case JDI_IOCTL_ENABLE_INTERRUPT:
		{
			enable_irq(s_jpu_irq);
		}
		break;

	case JDI_IOCTL_SET_CLOCK_GATE:
		{
			u32 clkgate;
			
			if (get_user(clkgate, (u32 __user *) arg))
				return -EFAULT;
			
#ifdef JPU_SUPPORT_CLOCK_CONTROL	
			if (clkgate)
				jpu_clk_enable(s_jpu_clk);
			else
				jpu_clk_disable(s_jpu_clk);
#endif
			
		}
		break;
        case JDI_IOCTL_SET_CLOCK_ENABLE:
		{
			u32 clkgate;
			u32 clk_en_val;
			
			if (get_user(clkgate, (u32 __user *) arg))
				return -EFAULT;

			clk_en_val = readl(IOMEM(JPU_VIRT_ADDR_MAP(JPU_CLOCK_ENABLE_REG)));
			if (clkgate)
				clk_en_val |= (1 << 13);
			else
				clk_en_val &= ~(1 << 13);
			JPU_WRITE_REG_INT32U(JPU_CLOCK_ENABLE_REG, clk_en_val);
			__delay(100);
		}
		break;
	case JDI_IOCTL_GET_INSTANCE_POOL:
		{
			down(&s_jpu_sem);
			
			if (s_jpu_instance_pool.base != 0) 
			{
				ret = copy_to_user((void __user *)arg, &s_jpu_instance_pool, sizeof(jpudrv_buffer_t));
				if (ret != 0) 
					ret = -EFAULT;
			} 
			else
			{
				ret = copy_from_user(&s_jpu_instance_pool, (jpudrv_buffer_t *)arg, sizeof(jpudrv_buffer_t));
				if (ret == 0)
				{
					if (jpu_alloc_dma_buffer(&s_jpu_instance_pool) != -1)
					{
						memset((void *)s_jpu_instance_pool.base, 0x0, s_jpu_instance_pool.size); 
						ret = copy_to_user((void __user *)arg, &s_jpu_instance_pool, sizeof(jpudrv_buffer_t));
						if (ret == 0)
						{
							// success to get memory for instance pool
							up(&s_jpu_sem);
							break;
						}
					}
				}
				
				ret = -EFAULT;
			}
			up(&s_jpu_sem);
		}
		break;
	case JDI_IOCTL_OPEN_INSTANCE:
		{
			u32 inst_idx;
			jpudrv_instanace_list_t *jil;

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

		}
		break;
	case JDI_IOCTL_CLOSE_INSTANCE:
		{
			u32 inst_idx;
			jpudrv_instanace_list_t *jil, *n;

			if (get_user(inst_idx, (u32 __user *) arg))
				return -EFAULT;

			spin_lock(&s_jpu_lock);

			list_for_each_entry_safe(jil, n, &s_jpu_inst_list_head, list) 
			{
				if (jil->inst_idx == inst_idx)
				{
					s_jpu_open_count--;
					list_del(&jil->list);
					kfree(jil);
					printk(KERN_INFO "[JPUDRV] JDI_IOCTL_CLOSE_INSTANCE inst_idx=%d, open_count=%d\n", (int)inst_idx, s_jpu_open_count);
					break;
				}
			}
			spin_unlock(&s_jpu_lock);
		}
		break;
	case JDI_IOCTL_GET_INSTANCE_NUM:
		{
			down(&s_jpu_sem);

			ret = copy_to_user((void __user *)arg, &s_jpu_open_count, sizeof(int));
			if (ret != 0) 
				ret = -EFAULT;

			//printk(KERN_INFO "[JPUDRV] VDI_IOCTL_GET_INSTANCE_NUM open_count=%d\n", s_vpu_open_count);

			up(&s_jpu_sem);
		}
		break;
	case JDI_IOCTL_RESET:
		{
			jpu_hw_reset();
		}
		break;
	default:
		{
			printk(KERN_ERR "No such IOCTL, cmd is %d\n", cmd);
		}
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
	printk(KERN_INFO "jpu_release s_jpu_open_count=%d\n", s_jpu_open_count);	

	spin_lock(&s_jpu_lock);


	if (s_jpu_open_count > 0) 
	{
		/* found and free the not handled buffer by user applications */
		jpu_free_buffers(filp);		

		/* found and free the not closed instance by user applications */
		jpu_free_instances(filp);
	}

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
	pfn = s_jpu_reg_phy_base >> PAGE_SHIFT;
	
	return remap_pfn_range(vm, vm->vm_start, pfn, vm->vm_end-vm->vm_start, vm->vm_page_prot) ? -EAGAIN : 0;
}

static int jpu_map_to_physical_memory(struct file *fp, struct vm_area_struct *vm)
{
	vm->vm_flags |= VM_IO | VM_RESERVED;
	vm->vm_page_prot = pgprot_writecombine(vm->vm_page_prot);

	return remap_pfn_range(vm, vm->vm_start, vm->vm_pgoff, vm->vm_end-vm->vm_start, vm->vm_page_prot) ? -EAGAIN : 0;
}

static int jpu_map_to_instance_pool_memory(struct file *fp, struct vm_area_struct *vm)
{
	vm->vm_flags |= VM_IO | VM_RESERVED;
	vm->vm_page_prot = pgprot_noncached(vm->vm_page_prot);
	return remap_pfn_range(vm, vm->vm_start, vm->vm_pgoff, vm->vm_end-vm->vm_start, vm->vm_page_prot) ? -EAGAIN : 0;
}

/*!
 * @brief memory map interface for jpu file operation
 * @return  0 on success or negative error code on error
 */
static int jpu_mmap(struct file *fp, struct vm_area_struct *vm)
{
	if (vm->vm_pgoff) 
	{
		if(vm->vm_pgoff == (s_jpu_instance_pool.phys_addr>>PAGE_SHIFT))
			return  jpu_map_to_instance_pool_memory(fp, vm);

		return jpu_map_to_physical_memory(fp, vm);
	}
	else
		return jpu_map_to_register(fp, vm);
	
}

struct file_operations jpu_fops = {
	.owner = THIS_MODULE,
	.open = jpu_open,
	.read = jpu_read,
	.write = jpu_write,
	.unlocked_ioctl = jpu_ioctl,
	.release = jpu_release,
	.fasync = jpu_fasync,
	.mmap = jpu_mmap,
};

static int jpu_probe(struct platform_device *pdev)
{
	int err = 0;

	struct resource *res = NULL;
	printk(KERN_INFO "jpu_probe\n");	

	if (pdev)
		res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	if (res) 	// if platform driver is implemented
	{
		s_jpu_reg_phy_base = res->start;
		s_jpu_reg_virt_base = ioremap(res->start, res->end - res->start);
		printk(KERN_INFO "[JPUDRV] : 1 jpu base address get from platform driver base addr=0x%u, virtualbase=0x%p\n", s_jpu_reg_phy_base , s_jpu_reg_virt_base);		
	}
	else
	{
		s_jpu_reg_virt_base = ioremap(s_jpu_reg_phy_base, JPU_REG_SIZE);
		printk(KERN_INFO "[JPUDRV] : 2 jpu base address get from defined value base addr=0x%u, virtualbase=0x%p\n", s_jpu_reg_phy_base, s_jpu_reg_virt_base);		
	}
	
#if 0
	/* get the major number of the character device */
	if ((alloc_chrdev_region(&s_jpu_major, 0, 1, JPU_DEV_NAME)) < 0)
	{
		err = -EBUSY;
		printk(KERN_ERR "could not allocate major number\n");
		goto ERROR_PROVE_DEVICE;
	}

	s_jpu_class = class_create(THIS_MODULE, JPU_DEV_NAME);
	if (IS_ERR(s_jpu_class))
	{
		err = -EBUSY;
		printk(KERN_ERR "could not create class\n");
		goto ERROR_PROVE_DEVICE;
	}

	s_jpu_dev = device_create(s_jpu_class, NULL, MKDEV(s_jpu_major, 0), NULL, JPU_DEV_NAME);
	if (IS_ERR(s_jpu_dev))
	{
		err = -EBUSY;
		printk(KERN_ERR "could not create device\n");
		goto ERROR_PROVE_DEVICE;
	}

	/* initialize the device structure and register the device with the kernel */
	cdev_init(&s_jpu_cdev, &jpu_fops);
	if ((cdev_add(&s_jpu_cdev, s_jpu_major, 1)) < 0)
	{
		err = -EBUSY;
		printk(KERN_ERR "could not allocate chrdev\n");
		goto ERROR_PROVE_DEVICE;
	}
#else
	s_jpu_dev.minor = MISC_DYNAMIC_MINOR;
	s_jpu_dev.name = JPU_DEV_NAME;
	s_jpu_dev.fops = &jpu_fops;
	s_jpu_dev.parent = NULL;
	if (misc_register(&s_jpu_dev)) {
	       printk("jpu: failed to register misc device.");
	       goto ERROR_PROVE_DEVICE;
	}
#endif

	if (pdev)
		s_jpu_clk = jpu_clk_get(&pdev->dev);
	else
		s_jpu_clk = jpu_clk_get(NULL);
	
	if (!s_jpu_clk) {
		printk(KERN_ERR "[JPUDRV] : fail to get clock controller, but, do not treat as error, \n");			
	}
	else {
		printk(KERN_INFO "[JPUDRV] : get clock controller s_jpu_clk=0x%p\n", s_jpu_clk);					
	}
	
#ifdef JPU_SUPPORT_CLOCK_CONTROL	
	jpu_clk_enable(s_jpu_clk);
#endif

	
#ifdef JPU_SUPPORT_ISR	
	if(pdev)
		res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (res) 	// if platform driver is implemented
	{
		s_jpu_irq = res->start;
		printk(KERN_INFO "[JPUDRV] : 1 jpu irq number get from platform driver irq=0x%x\n", s_jpu_irq );		
	}
	else
	{
		printk(KERN_INFO "[JPUDRV] : 2 jpu irq number get from defined value irq=0x%x\n", s_jpu_irq );
	}


	err = request_irq(s_jpu_irq, jpu_irq_handler, 0, "JPU_CODEC", (void *)(&s_jpu_drv_context));
	if (err)
	{
		printk(KERN_ERR "[JPUDRV] :  fail to register interrupt handler\n");
		goto ERROR_PROVE_DEVICE;
	}
#endif

#ifdef JPU_SUPPORT_RESERVED_VIDEO_MEMORY
	s_image_memory.size = JPU_INIT_VIDEO_MEMORY_SIZE_IN_BYTE;
	s_image_memory.phys_addr = JPU_DRAM_PHYSICAL_BASE;
	s_image_memory.base = (unsigned long)ioremap(s_image_memory.phys_addr, PAGE_ALIGN(s_image_memory.size));
	if (!s_image_memory.base)
	{	
		printk(KERN_ERR "[JPUDRV] :  fail to remap video memory physical phys_addr=0x%x, base=0x%x, size=%d\n", (int)s_image_memory.phys_addr, (int)s_image_memory.base, (int)s_image_memory.size);
		goto ERROR_PROVE_DEVICE;
	}
	if (jmem_init(&s_jmem, s_image_memory.phys_addr, s_image_memory.size) < 0)
	{
		printk(KERN_ERR "[JPUDRV] :  fail to init vmem system\n");
		goto ERROR_PROVE_DEVICE;
	}
	printk(KERN_INFO "[JPUDRV] success to probe jpu device with reserved video memory phys_addr=0x%x, base = 0x%x\n",(int) s_image_memory.phys_addr, (int)s_image_memory.base);
#else
	printk(KERN_INFO "[JPUDRV] success to probe jpu device with non reserved video memory\n");
#endif	
				


	return 0;


ERROR_PROVE_DEVICE:

#if 0
	if (s_jpu_dev)
	{
		device_destroy(s_jpu_class, MKDEV(s_jpu_major, 0));
		s_jpu_dev = NULL;
	}

	if (s_jpu_class)
	{
		class_destroy(s_jpu_class);
		s_jpu_class = NULL;
	}

	if (s_jpu_major)
		unregister_chrdev_region(s_jpu_major, 1);
#else
	misc_deregister(&s_jpu_dev);
#endif

	if (s_jpu_reg_virt_base)
		iounmap(s_jpu_reg_virt_base);

	return err;
}

static int jpu_remove(struct platform_device *pdev)
{
#ifdef JPU_SUPPORT_PLATFORM_DRIVER_REGISTER	

	printk(KERN_INFO "jpu_remove\n");

	if (s_jpu_instance_pool.base)
	{
		jpu_free_dma_buffer(&s_jpu_instance_pool);
		s_jpu_instance_pool.base = 0;
	}
#ifdef JPU_SUPPORT_RESERVED_VIDEO_MEMORY
	if (s_image_memory.base) 
	{
		iounmap((void *)s_image_memory.base);
		s_image_memory.base = 0;
		jmem_exit(&s_jmem);		
	}	
#endif	

#if 0
	if (s_jpu_dev)
	{
		device_destroy(s_jpu_class, MKDEV(s_jpu_major, 0));
		s_jpu_dev = NULL;
	}

	if (s_jpu_class)
	{
		class_destroy(s_jpu_class);
		s_jpu_class = NULL;
	}

	cdev_del(&s_jpu_cdev);
	if (s_jpu_major > 0)
	{
		unregister_chrdev_region(s_jpu_major, 1);
		s_jpu_major = 0;
	}
#else
	misc_deregister(&s_jpu_dev);
#endif

#ifdef JPU_SUPPORT_ISR
	if (s_jpu_irq)
		free_irq(s_jpu_irq, &s_jpu_drv_context);		
#endif

	if (s_jpu_reg_virt_base)
		iounmap(s_jpu_reg_virt_base);

	jpu_clk_put(s_jpu_clk);	
		
#endif //JPU_SUPPORT_PLATFORM_DRIVER_REGISTER

	return 0;
}

#ifdef CONFIG_PM
static int jpu_suspend(struct platform_device *pdev, pm_message_t state)
{
	jpu_clk_disable(s_jpu_clk);
	return 0;

}

static int jpu_resume(struct platform_device *pdev)
{
	jpu_clk_enable(s_jpu_clk);

	return 0;
}
#else
#define	jpu_suspend	NULL
#define	jpu_resume	NULL
#endif				/* !CONFIG_PM */

static struct platform_driver jpu_driver = {
	.driver = {
		   .name = JPU_PLATFORM_DEVICE_NAME,
		   },
	.probe = jpu_probe,
	.remove = jpu_remove,
	.suspend    = NULL,//TODO: jpu_suspend,
	.resume     = NULL,//TODO: jpu_resume,
};

static int __init jpu_init(void)
{
	int res;
	res = 0;
	printk(KERN_INFO "jpu_init\n");	
	init_waitqueue_head(&s_interrupt_wait_q);
	s_jpu_instance_pool.base = 0;	

#ifdef JPU_SUPPORT_PLATFORM_DRIVER_REGISTER
	res = platform_driver_register(&jpu_driver);
#else
	res = platform_driver_register(&jpu_driver);
	res = jpu_probe(NULL);
#endif

	printk(KERN_INFO "end jpu_init result=0x%x\n", res);	
	return res;
}

static void __exit jpu_exit(void)
{
#ifdef JPU_SUPPORT_PLATFORM_DRIVER_REGISTER	
	printk(KERN_INFO "jpu_exit\n");
#else	
	if (s_jpu_instance_pool.base)
	{
		jpu_free_dma_buffer(&s_jpu_instance_pool);
		s_jpu_instance_pool.base = 0;
	}
#ifdef JPU_SUPPORT_RESERVED_VIDEO_MEMORY
	if (s_image_memory.base) 
	{
		iounmap((void *)s_image_memory.base);
		s_image_memory.base = 0;
	}
#endif		

#if 0
	if (s_jpu_dev)
	{
		device_destroy(s_jpu_class, MKDEV(s_jpu_major, 0));
		s_jpu_dev = NULL;
	}

	if (s_jpu_class)
	{
		class_destroy(s_jpu_class);
		s_jpu_class = NULL;
	}

	cdev_del(&s_jpu_cdev);
	if (s_jpu_major > 0)
	{
		unregister_chrdev_region(s_jpu_major, 1);
		s_jpu_major = 0;
	}
#else
	misc_deregister(&s_jpu_dev);
#endif

#ifdef JPU_SUPPORT_ISR
	if (s_jpu_irq)
		free_irq(s_jpu_irq, &s_jpu_drv_context);		
#endif	
	
	jpu_clk_put(s_jpu_clk);

	
	if (s_jpu_reg_virt_base) {
		iounmap(s_jpu_reg_virt_base);
		s_jpu_reg_virt_base = (void *)0x00;
	}

#endif //JPU_SUPPORT_PLATFORM_DRIVER_REGISTER

	platform_driver_unregister(&jpu_driver);
	
	return;
}

MODULE_AUTHOR("A customer using C&M JPU, Inc.");
MODULE_DESCRIPTION("JPU linux driver");
MODULE_LICENSE("GPL");

module_init(jpu_init);
module_exit(jpu_exit);

int jpu_hw_reset(void)
{
	u32 reset_value = 0;
	u32 reset_bit = 0;
	u32 clk_en_val = 0;
	u32 clk_en_bit = 0;

	reset_bit = 1 << 18;
	clk_en_bit = 1 << 13;

	// disable clock gatting
	clk_en_val = readl(IOMEM(JPU_VIRT_ADDR_MAP(JPU_CLOCK_ENABLE_REG)));
	clk_en_val &= ~clk_en_bit;
	JPU_WRITE_REG_INT32U(JPU_CLOCK_ENABLE_REG, clk_en_val);
	__delay(100);

	// reset jpu bit to 0
	reset_value = readl(IOMEM(JPU_VIRT_ADDR_MAP(JPU_CLOCK_REG_BASE)));
	reset_value &= ~reset_bit;
	JPU_WRITE_REG_INT32U(JPU_CLOCK_REG_BASE, reset_value);
	__delay(100);

	// reset jpu bit to 1
	reset_value = readl(IOMEM(JPU_VIRT_ADDR_MAP(JPU_CLOCK_REG_BASE)));
	reset_value |= reset_bit;
	JPU_WRITE_REG_INT32U(JPU_CLOCK_REG_BASE, reset_value);
	__delay(100);

	// enable clock gatting
	clk_en_val = readl(IOMEM(JPU_VIRT_ADDR_MAP(JPU_CLOCK_ENABLE_REG)));
	clk_en_val |= clk_en_bit;
	JPU_WRITE_REG_INT32U(JPU_CLOCK_ENABLE_REG, clk_en_val);
	__delay(100);

	printk(KERN_INFO "request jpu reset from application. \n");
	return 0;
}


struct clk *jpu_clk_get(struct device *dev)
{
	return clk_get(dev, JPU_CLK_NAME);
}
void jpu_clk_put(struct clk *clk)
{
	if (clk)
		clk_put(clk);
}
int jpu_clk_enable(struct clk *clk)
{
	if (clk) {
		printk(KERN_INFO "jpu_clk_enable\n");	
		return clk_enable(clk);
	}
	return 0;
}

void jpu_clk_disable(struct clk *clk)
{
	if (clk) {
		printk(KERN_INFO "jpu_clk_disable\n");	
		clk_disable(clk);
	}
}


