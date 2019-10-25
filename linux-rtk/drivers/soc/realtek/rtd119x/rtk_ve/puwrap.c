
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
#include <linux/dma-buf.h>
#include <linux/module.h>
#include "puwrap.h"

#ifdef CONFIG_VIDEO_CODEC
extern void vpu_irq_handler2(int core_num, void *dev_id);
#endif
#ifdef CONFIG_IMAGE_CODEC
extern void jpu_irq_handler2(void *dev_id);
#endif


#ifdef CONFIG_RTK_RESERVE_MEMORY
#define USE_ION_ALLOCATOR
#ifdef USE_ION_ALLOCATOR
#define NUM_ION_STRUCT 256
#include "../../../../staging/android/ion/ion.h"
#include "../../../../staging/android/uapi/ion_rtk.h"
struct rtkdrv_ion_buffer_t{
	unsigned int size;
	unsigned int inUse;
	unsigned long long phys_addr;
	unsigned long long dmabuf;
	unsigned long pIonHandle;
};
static DEFINE_MUTEX(s_pu_mutex);
extern struct ion_device *rtk_phoenix_ion_device;
struct ion_client *pu_client = NULL;
struct rtkdrv_ion_buffer_t pu_ion_buffer[NUM_ION_STRUCT];
#else /* else USE_ION_ALLOCATOR */
typedef struct rtkdrv_buffer_t {
	unsigned int size;
	unsigned long long phys_addr;
	unsigned long base;							/* kernel logical address in use kernel */
	unsigned long virt_addr;				/* virtual user space address */
} rtkdrv_buffer_t;

#define RTK_INIT_VIDEO_MEMORY_SIZE_IN_BYTE (16*1024*1024)
#define RTK_DRAM_PHYSICAL_BASE 0x06000000
#include "rtk_mm.h"
static rtk_mm_t s_mem;	
static rtkdrv_buffer_t s_memory = {0};
#endif /* endif USE_ION_ALLOCATOR */
#endif /* endif CONFIG_RTK_RESERVE_MEMORY */


#define PU_PLATFORM_DEVICE_NAME "rtk_puwrap"
#define PU_REG_BASE_ADDR 0x18047000
#define PU_REG_SIZE 0xC00
#define PU_IRQ_NUM 83//(23+32)

#define PU_REG_INT_STS 0x20

#define INT_980	(1<<0)
#define INT_855	(1<<1)
#define INT_410	(1<<2)


static pu_drv_context_t s_pu_drv_context;
static u32 s_pu_reg_phy_addr = PU_REG_BASE_ADDR;
static void __iomem *s_pu_reg_virt_addr;
static int s_pu_irq = PU_IRQ_NUM;
static int bLowMem = 0;
#define ReadRegister(addr)		__raw_readl(s_pu_reg_virt_addr + addr)
#define WriteRegister(addr, val)	__raw_writel(val, (s_pu_reg_virt_addr + addr))


#ifdef CONFIG_RTK_RESERVE_MEMORY
int pu_alloc_dma_buffer(unsigned int size, unsigned long *phys_addr, unsigned long *base, unsigned int mem_type)
{
    if (!size)
        return -1;

#ifdef USE_ION_ALLOCATOR
    unsigned int i;
    struct ion_handle *handle;
    struct dma_buf *dmabuf;
    ion_phys_addr_t dat;
    size_t len;
    int heap = RTK_PHOENIX_ION_HEAP_MEDIA_MASK;
    int flags = (ION_FLAG_SCPUACC | ION_FLAG_HWIPACC | ION_FLAG_NONCACHED);

    mutex_lock(&s_pu_mutex);
    for (i = 0; i < NUM_ION_STRUCT; i++)
    {
        if (pu_ion_buffer[i].inUse == 0)
            break;
    }
    if (i == NUM_ION_STRUCT)
    {
        printk(KERN_ERR "[PUWRAP] NUM_ION_STRUCT is too small!!!");
        mutex_unlock(&s_pu_mutex);
        return -1;
    }
    heap = RTK_PHOENIX_ION_HEAP_MEDIA_MASK;
    flags = (ION_FLAG_SCPUACC | ION_FLAG_HWIPACC | ION_FLAG_NONCACHED);

    handle = ion_alloc(pu_client, size, 1024, heap, flags);
    if (IS_ERR(handle))
    {
        printk(KERN_ERR "[PUWRAP] ion_alloc allocation error size=%d\n", size);
        mutex_unlock(&s_pu_mutex);
        return -1;
    }

    if(ion_phys(pu_client, handle, &dat, &len) != 0)
    {
        printk(KERN_ERR "[PUWRAP] ion_alloc allocation error size=%d\n", size);
        mutex_unlock(&s_pu_mutex);
        return -1;
    }

    *base = (unsigned long)ion_map_kernel(pu_client, handle);
    *phys_addr = (unsigned long)dat;
    dmabuf = ion_share_dma_buf(pu_client, handle);

    pu_ion_buffer[i].size = size;
    pu_ion_buffer[i].inUse = 1;
    pu_ion_buffer[i].phys_addr = (unsigned long)*phys_addr;
    pu_ion_buffer[i].dmabuf = (unsigned long)dmabuf;
    pu_ion_buffer[i].pIonHandle = (unsigned long)handle;

    mutex_unlock(&s_pu_mutex);

#else /* else USE_ION_ALLOCATOR */
    *phys_addr = (unsigned long)vmem_alloc(&s_mem, size, 0);
    if (*phys_addr  == (unsigned long)-1)
    {
        printk(KERN_ERR "[PUWRAP] Physical memory allocation error size=%d\n", size);
        return -1;
    }

    *base = (unsigned long)(s_memory.base + (*phys_addr - s_memory.phys_addr));
#endif /* endif USE_ION_ALLOCATOR */
    //printk("[PUWARP] base:0x%lx, phy_addr:0x%lx, size:%d\n", *base, (unsigned long)*phys_addr, size);

    return 0;
}

void pu_free_dma_buffer(unsigned long base, unsigned long phys_addr)
{
    if (!base)
        return;

#ifdef USE_ION_ALLOCATOR
    unsigned int i;
    struct ion_handle *handle;
    struct dma_buf *dmabuf;
    mutex_lock(&s_pu_mutex);

    for (i = 0; i < NUM_ION_STRUCT; i++)
    {
        if (pu_ion_buffer[i].phys_addr == phys_addr)
            break;
    }
    if (i == NUM_ION_STRUCT)
    {
        printk(KERN_ERR "[PUWRAP] can't find phys_addr:0x%lx !!!\n", (unsigned long)phys_addr);
        mutex_unlock(&s_pu_mutex);
        return;
    }

    dmabuf = (struct dma_buf *)pu_ion_buffer[i].dmabuf;
    if (dmabuf != NULL)
    {
        dma_buf_put(dmabuf);
        pu_ion_buffer[i].dmabuf = NULL;
    }

    handle = (struct ion_handle *)pu_ion_buffer[i].pIonHandle;
    if(handle != NULL)
    {
        ion_unmap_kernel(pu_client, handle);
        ion_free(pu_client, handle);
    }
    memset(&pu_ion_buffer[i], 0, sizeof(struct rtkdrv_ion_buffer_t));
    mutex_unlock(&s_pu_mutex);
#else
    vmem_free(&s_mem, (unsigned long)phys_addr, 0);
#endif
}

int pu_mmap_dma_buffer(struct vm_area_struct *vm)
{
#ifdef USE_ION_ALLOCATOR
    u32 i;
    int ret = 0;
    struct dma_buf *dmabuf;
    unsigned long phys_addr = (unsigned long)(vm->vm_pgoff << PAGE_SHIFT);
    mutex_lock(&s_pu_mutex);

    for (i = 0; i < NUM_ION_STRUCT; i++)
    {
        if (pu_ion_buffer[i].phys_addr == phys_addr)
            break;
    }
    if (i == NUM_ION_STRUCT)
    {
        printk(KERN_ERR "[PUWRAP] can't find phys_addr:0x%lx !!!\n", (unsigned long)phys_addr);
        mutex_unlock(&s_pu_mutex);
        return -EINVAL;
    }

    dmabuf = (struct dma_buf *)pu_ion_buffer[i].dmabuf;
    ret = dma_buf_mmap(dmabuf, vm, 0);

    mutex_unlock(&s_pu_mutex);

    return ret;
#else
    return -EINVAL;
#endif
}

#endif //#ifdef CONFIG_RTK_RESERVE_MEMORY

void *pu_get_drv_context(void)
{
        return (void *)&s_pu_drv_context;
}


static irqreturn_t pu_irq_handler(int irq, void *dev_id)
{
	pu_drv_context_t *dev = (pu_drv_context_t *)dev_id;
	volatile unsigned int reg_val;

	//printk(KERN_INFO "[PUWRAP] pu_irq_handler\n");	

	reg_val = ReadRegister(PU_REG_INT_STS);
	//printk("reg_val:0x%08x\n", reg_val);
#ifdef CONFIG_VIDEO_CODEC
	if(reg_val & INT_980)
	{
		vpu_irq_handler2(0, dev_id); //enable core 0. (coda980)
	}
	if(reg_val & INT_410)
	{
		vpu_irq_handler2(1, dev_id); //enable core 1. (wave410)
	}
#endif
#ifdef CONFIG_IMAGE_CODEC
	if(reg_val & INT_855)
	{
		jpu_irq_handler2(dev_id); //enable coda855j.
	}
#endif

	if (dev->async_queue)
		kill_fasync(&dev->async_queue, SIGIO, POLL_IN);	// notify the interrupt to user space
	

	return IRQ_HANDLED;
}


static int pu_fasync(int fd, struct file *filp, int mode)
{
	struct pu_drv_context_t *dev = (struct pu_drv_context_t *)filp->private_data;
	return fasync_helper(fd, filp, mode, &dev->async_queue);
}


struct file_operations pu_fops = {
	.owner = THIS_MODULE,
	.fasync = pu_fasync,
};


static const struct of_device_id rtk_pu_dt_match[] = {
    { .compatible = "Realtek,rtk1195-pu_pll" },
    {}
};
MODULE_DEVICE_TABLE(of, rtk_pu_dt_match);

static int pu_probe(struct platform_device *pdev)
{
	int err = 0;
	struct resource *res=NULL;
	printk(KERN_INFO "[PUWRAP] pu_probe\n");

	if ((int)(get_num_physpages() << PAGE_SHIFT) <= 0x20000000) //512MB
	{
		printk(KERN_INFO "[PUWRAP] board %luM\n", (int)(get_num_physpages() >> (20 - PAGE_SHIFT)));
		bLowMem = 1;
	}

	if(pdev)
		res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res) 	// if platform driver is implemented
	{
		s_pu_reg_phy_addr = res->start;
		s_pu_reg_virt_addr = ioremap(res->start, res->end - res->start);
		printk(KERN_INFO "[PUWRAP] : 1 pu base address get from platform driver physical base addr=0x%x, virtual base=0x%x\n", (int)s_pu_reg_phy_addr , (int)s_pu_reg_virt_addr);		
	}
	else
	{
		s_pu_reg_virt_addr = ioremap(s_pu_reg_phy_addr, PU_REG_SIZE);
		printk(KERN_INFO "[PUWRAP] : 2 pu base address get from defined value physical base addr=0x%x, virtual base=0x%x\n", (int)s_pu_reg_phy_addr, (int)s_pu_reg_virt_addr);
		
	}

	if(pdev)
		res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (res) 	// if platform driver is implemented
	{
		s_pu_irq = res->start;
		printk(KERN_INFO "[PUWRAP] : 1 pu irq number get from platform driver irq=0x%x\n", s_pu_irq );		
	}
	else
	{
		printk(KERN_INFO "[PUWRAP] : 2 pu irq number get from defined value irq=0x%x\n", s_pu_irq );
	}

	err = request_irq(s_pu_irq, pu_irq_handler, IRQF_SHARED, "pu_wrapper", (void *)(&s_pu_drv_context));
	if (err)
	{
		printk(KERN_ERR "[PUWRAP] :  fail to register interrupt handler\n");
		goto ERROR_PROVE_DEVICE;
	}


#ifdef CONFIG_RTK_RESERVE_MEMORY
#ifdef USE_ION_ALLOCATOR
	pu_client = ion_client_create(rtk_phoenix_ion_device, "PUDriver");
	memset(pu_ion_buffer, 0, sizeof(struct rtkdrv_ion_buffer_t)*NUM_ION_STRUCT);
	printk(KERN_INFO "[PUWRAP] success to probe pu wrapper device with USE_ION_ALLOCATOR\n");
#else /* else USE_ION_ALLOCATOR */
	if(pdev)
		res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if(res)
	{
		s_memory.size = res->end - res->start;
		s_memory.phys_addr = res->start;
	}
	else
	{
		s_memory.size = RTK_INIT_VIDEO_MEMORY_SIZE_IN_BYTE;
		s_memory.phys_addr = RTK_DRAM_PHYSICAL_BASE;
	}

	s_memory.base = (unsigned long)ioremap(s_memory.phys_addr, PAGE_ALIGN(s_memory.size));
	if (!s_memory.base)
	{	
		printk(KERN_ERR "[PUWRAP] :  fail to remap video memory physical phys_addr=0x%x, base=0x%x, size=%d\n", (int)s_memory.phys_addr, (int)s_memory.base, (int)s_memory.size);
		goto ERROR_PROVE_DEVICE;
	}
	if (rtk_mem_init(&s_mem, s_memory.phys_addr, s_memory.size) < 0)
	{
		printk(KERN_ERR "[PUWRAP] :  fail to init vmem system\n");
		goto ERROR_PROVE_DEVICE;
	}
	printk(KERN_INFO "[PUWRAP] success to probe pu wrapper device with reserved video memory phys_addr=0x%x, base = 0x%x\n", (int) s_memory.phys_addr, (int)s_memory.base);
#endif /* endif USE_ION_ALLOCATOR */
#else /* else CONFIG_RTK_RESERVE_MEMORY */
	printk(KERN_INFO "[PUWRAP] success to probe pu wrapper device\n");
#endif /* endif CONFIG_RTK_RESERVE_MEMORY */
	
	
	return 0;


ERROR_PROVE_DEVICE:

	if (s_pu_reg_virt_addr)
		iounmap(s_pu_reg_virt_addr);

	return err;
}

static int pu_remove(struct platform_device *pdev)
{
	printk(KERN_INFO "[PUWRAP] pu_remove\n");

#ifdef CONFIG_RTK_RESERVE_MEMORY
#ifdef USE_ION_ALLOCATOR
	if(pu_client != NULL)
	{
		ion_client_destroy(pu_client);
		pu_client = NULL;
	}
#else /* else USE_ION_ALLOCATOR */
	if (s_memory.base) 
	{
		iounmap((void *)s_memory.base);
		s_memory.base = 0;
		rtk_mem_exit(&s_mem);		
	}
#endif /* endif USE_ION_ALLOCATOR */
#endif /* endif CONFIG_RTK_RESERVE_MEMORY */

	if (s_pu_irq)
		free_irq(s_pu_irq, &s_pu_drv_context);

	if (s_pu_reg_virt_addr)
		iounmap(s_pu_reg_virt_addr);

	return 0;
}


static struct platform_driver pu_driver = {
	.driver = {
		   .name = PU_PLATFORM_DEVICE_NAME,
		   .owner  = THIS_MODULE,
		   .of_match_table = rtk_pu_dt_match,
		   },
	.probe = pu_probe,
	.remove = pu_remove,
};

static ssize_t pu_memsize_show(struct kobject *kobj, struct kobject_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", (int)(get_num_physpages() << PAGE_SHIFT));
}

static struct kobj_attribute pu_memsize_attr =
	__ATTR(pu_memsize, 0644, pu_memsize_show, NULL);

static struct attribute *pu_attrs[] = {
	&pu_memsize_attr.attr,
	NULL,
};

static struct attribute_group rtk_pu_attr_group = {
	.attrs = pu_attrs,
};

static struct kobject *pu_kobj;

static int __init pu_init(void)
{
	int res;

	pu_kobj = kobject_create_and_add("rtk_pu", kernel_kobj);
	if (pu_kobj)
	{
		res = sysfs_create_group(pu_kobj, &rtk_pu_attr_group);
		if (res)
			printk(KERN_WARNING "[PUWRAP] %d: unable to create sysfs entry\n", __LINE__);
	}
	else
		printk(KERN_WARNING "[PUWRAP] %d: unable to create sysfs entry\n", __LINE__);

	printk(KERN_INFO "[PUWRAP] begin pu_init\n");
	res = platform_driver_register(&pu_driver);
	printk(KERN_INFO "[PUWRAP] end pu_init result=0x%x\n", res);
	return res;
}

static void __exit pu_exit(void)
{
	printk(KERN_INFO "[PUWRAP] pu_exit\n");
	platform_driver_unregister(&pu_driver);
	return;
}
MODULE_AUTHOR("RTK Wrapper for JPU & VPU, Inc.");
MODULE_DESCRIPTION("PU WRAPPER linux driver");
MODULE_LICENSE("GPL");

module_init(pu_init);
module_exit(pu_exit);
