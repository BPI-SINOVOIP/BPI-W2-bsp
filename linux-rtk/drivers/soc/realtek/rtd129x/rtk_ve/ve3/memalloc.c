/* Copyright 2012 Google Inc. All Rights Reserved. */

#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/dma-mapping.h>
#include <linux/mm.h>

#include "memalloc.h"
#include "compat_memalloc.h"
#include "../puwrap.h"

#ifndef CONFIG_RTK_RESERVE_MEMORY
//#define SUPPORT_RESERVED_VIDEO_MEMORY
#endif

#ifndef HLINA_START_ADDRESS
#define HLINA_START_ADDRESS 0x02000000
#endif

#ifndef HLINA_SIZE
#define HLINA_SIZE 96
#endif

#ifndef HLINA_TRANSL_OFFSET
#define HLINA_TRANSL_OFFSET 0x0
#endif

/* the size of chunk in MEMALLOC_DYNAMIC */
#define CHUNK_SIZE (PAGE_SIZE * 4)

/* memory size in MBs for MEMALLOC_DYNAMIC */
unsigned long alloc_size = HLINA_SIZE;
unsigned long alloc_base = HLINA_START_ADDRESS;

/* user space SW will substract HLINA_TRANSL_OFFSET from the bus address
 * and decoder HW will use the result as the address translated base
 * address. The SW needs the original host memory bus address for memory
 * mapping to virtual address. */
unsigned long addr_transl = HLINA_TRANSL_OFFSET;

static struct miscdevice s_memalloc_dev;

#ifndef VM_RESERVED	/*for kernel up to 3.7.0 version*/
# define  VM_RESERVED   (VM_DONTEXPAND | VM_DONTDUMP)
#endif

/* module_param(name, type, perm) */
module_param(alloc_size, ulong, 0);
module_param(alloc_base, ulong, 0);
module_param(addr_transl, ulong, 0);

static spinlock_t s_mem_lock = __SPIN_LOCK_UNLOCKED(s_mem_lock);

typedef struct hlinc {
    u64 bus_address;
    u32 chunks_reserved;
    const struct file *filp; /* Client that allocated this chunk */
} hlina_chunk;

typedef struct rtk_hlinc {
    unsigned long phys_addr;
    unsigned long base;
    u32 size;
    const struct file *filp; /* Client that allocated this chunk */
} rtk_hlina_chunk;

#define RTK_CHUNKS 1024

#ifdef SUPPORT_RESERVED_VIDEO_MEMORY
static hlina_chunk *hlina_chunks = NULL;
#endif
static rtk_hlina_chunk *rtk_hlina_chunks = NULL;
static size_t chunks = 0;

static int AllocMemory(unsigned *busaddr, unsigned long size, unsigned int mem_type,
                       const struct file *filp);
static int FreeMemory(unsigned long busaddr, const struct file *filp);
static void ResetMems(void);

static long memalloc_ioctl(struct file *filp, unsigned int cmd,
                           unsigned long arg) {
    int ret = 0;
    MemallocParams memparams;
    unsigned long busaddr;

    PDEBUG("ioctl cmd 0x%08x\n", cmd);

    /*
     * extract the type and number bitfields, and don't decode
     * wrong cmds: return ENOTTY (inappropriate ioctl) before access_ok()
     */
    if (_IOC_TYPE(cmd) != MEMALLOC_IOC_MAGIC) return -ENOTTY;
    if (_IOC_NR(cmd) > MEMALLOC_IOC_MAXNR) return -ENOTTY;

    if (_IOC_DIR(cmd) & _IOC_READ)
        ret = !access_ok(VERIFY_WRITE, arg, _IOC_SIZE(cmd));
    else if (_IOC_DIR(cmd) & _IOC_WRITE)
        ret = !access_ok(VERIFY_READ, arg, _IOC_SIZE(cmd));
    if (ret) return -EFAULT;

    switch (cmd) {
    case MEMALLOC_IOCHARDRESET:
        PDEBUG("HARDRESET\n");
        ResetMems();
        break;
    case MEMALLOC_IOCXGETBUFFER:
        PDEBUG("GETBUFFER");

        ret = copy_from_user(&memparams, (MemallocParams *)arg,
                             sizeof(MemallocParams));
        if (ret) break;

        ret = AllocMemory(&memparams.bus_address, memparams.size, memparams.mem_type, filp);

        memparams.translation_offset = addr_transl;

        ret |= copy_to_user((MemallocParams *)arg, &memparams,
                            sizeof(MemallocParams));

        break;
    case MEMALLOC_IOCSFREEBUFFER:
        PDEBUG("FREEBUFFER\n");

        __get_user(busaddr, (unsigned long *)arg);
        ret = FreeMemory(busaddr, filp);
        break;
    }


    return ret ? -EFAULT : 0;
}

static int memalloc_open(struct inode *inode, struct file *filp) {

    PDEBUG("dev opened\n");
    return 0;
}

static int memalloc_release(struct inode *inode, struct file *filp) {
    int i = 0;

#ifdef SUPPORT_RESERVED_VIDEO_MEMORY
    for (i = 0; i < chunks; i++) {
        spin_lock(&s_mem_lock);
        if (hlina_chunks[i].filp == filp) {
            printk(KERN_WARNING "memalloc: Found unfreed memory at release time!\n");

            hlina_chunks[i].filp = NULL;
            hlina_chunks[i].chunks_reserved = 0;
        }
        spin_unlock(&s_mem_lock);
    }
#else /* else of SUPPORT_RESERVED_VIDEO_MEMORY */
    unsigned long phys_addr = 0;
    unsigned long base = 0;
    u32 size = 0;
    for (i = 0; i < chunks; i++)
    {
        spin_lock(&s_mem_lock);
        phys_addr = 0;
        base = 0;
        size = 0;
        if (rtk_hlina_chunks[i].filp == filp)
        {
            printk(KERN_WARNING "memalloc: Found unfreed memory at release time!\n");
            phys_addr = rtk_hlina_chunks[i].phys_addr;
            base = rtk_hlina_chunks[i].base;
            size = rtk_hlina_chunks[i].size;
            rtk_hlina_chunks[i].filp = NULL;
        }
        spin_unlock(&s_mem_lock);

        if (phys_addr != 0 && base!= 0 && size != 0)
        {
#ifdef CONFIG_RTK_RESERVE_MEMORY
            pu_free_dma_buffer(base, phys_addr);
#else
            if (base)
                dma_free_coherent(s_memalloc_dev.this_device, PAGE_ALIGN(size), (void *)base, phys_addr);
#endif
        }
    }
#endif /* end of SUPPORT_RESERVED_VIDEO_MEMORY */

    PDEBUG("dev closed\n");
    return 0;
}

void __exit memalloc_cleanup(void) {
#ifdef SUPPORT_RESERVED_VIDEO_MEMORY
    if (hlina_chunks != NULL) vfree(hlina_chunks);
#else
    if (rtk_hlina_chunks != NULL) vfree(rtk_hlina_chunks);
#endif

#if 0
    unregister_chrdev(memalloc_major, "memalloc");
#else
    misc_deregister(&s_memalloc_dev);
#endif

    PDEBUG("module removed\n");
    return;
}

static int memalloc_mmap(struct file *fp, struct vm_area_struct *vm)
{
#ifdef CONFIG_RTK_RESERVE_MEMORY
    return pu_mmap_dma_buffer(vm);
#else
    vm->vm_flags |= VM_IO | VM_RESERVED;
    vm->vm_page_prot = pgprot_writecombine(vm->vm_page_prot);

    return remap_pfn_range(vm, vm->vm_start, vm->vm_pgoff, vm->vm_end-vm->vm_start, vm->vm_page_prot) ? -EAGAIN : 0;
#endif
}

/* VFS methods */
static struct file_operations memalloc_fops = {
    .owner = THIS_MODULE,
    .open = memalloc_open,
    .release = memalloc_release,
    .unlocked_ioctl = memalloc_ioctl,
    .compat_ioctl = compat_memalloc_ioctl,
    .mmap = memalloc_mmap
};

int __init memalloc_init(void) {
    int result;

    PDEBUG("module init\n");
    printk("memalloc: Linear Memory Allocator\n");

#ifdef SUPPORT_RESERVED_VIDEO_MEMORY
    printk("memalloc: Linear memory base = 0x%08x\n", alloc_base);

    chunks = (alloc_size * 1024 * 1024) / CHUNK_SIZE;

    printk(KERN_INFO
           "memalloc: Total size %d MB; %d chunks"
           " of size %lu\n",
           alloc_size, chunks, CHUNK_SIZE);

    hlina_chunks = (hlina_chunk *)vmalloc(chunks * sizeof(hlina_chunk));
    if (hlina_chunks == NULL) {
        printk(KERN_ERR "memalloc: cannot allocate hlina_chunks\n");
        result = -ENOMEM;
        goto err;
    }
#else /* else of SUPPORT_RESERVED_VIDEO_MEMORY */
    chunks = RTK_CHUNKS;
    rtk_hlina_chunks = (rtk_hlina_chunk *)vmalloc(chunks * sizeof(rtk_hlina_chunk));
    if (rtk_hlina_chunks == NULL) {
        printk(KERN_ERR "memalloc: cannot allocate rtk_hlina_chunks\n");
        result = -ENOMEM;
        goto err;
    }
#endif /* end of SUPPORT_RESERVED_VIDEO_MEMORY */

#if 0
    result = register_chrdev(memalloc_major, "memalloc", &memalloc_fops);
    if (result < 0) {
        PDEBUG("memalloc: unable to get major %d\n", memalloc_major);
        goto err;
    } else if (result != 0) {/* this is for dynamic major */
        memalloc_major = result;
    }
#else
    s_memalloc_dev.minor = MISC_MEM_MINOR;
    s_memalloc_dev.name = "memalloc";
    s_memalloc_dev.fops = &memalloc_fops;
    s_memalloc_dev.parent = NULL;
    if (misc_register(&s_memalloc_dev)) {
        printk("memalloc: failed to register misc device.");
        goto err;
    }
#endif

    ResetMems();

    return 0;

err:
#ifdef SUPPORT_RESERVED_VIDEO_MEMORY
    if (hlina_chunks != NULL) vfree(hlina_chunks);
#else
    if (rtk_hlina_chunks != NULL) vfree(rtk_hlina_chunks);
#endif

    return result;
}

/* Cycle through the buffers we have, give the first free one */
static int AllocMemory(unsigned *busaddr, unsigned long size, unsigned int mem_type,
                       const struct file *filp) {

    int i = 0;

    *busaddr = 0;

    /* run through the chunk table */
#ifdef SUPPORT_RESERVED_VIDEO_MEMORY
    /* calculate how many chunks we need; round up to chunk boundary */
    unsigned int alloc_chunks = (size + CHUNK_SIZE - 1) / CHUNK_SIZE;

    spin_lock(&s_mem_lock);
    for (i = 0; i < chunks;) {
        int j = 0;
        unsigned int skip_chunks = 0;
        skip_chunks = 0;
        /* if this chunk is available */
        if (!hlina_chunks[i].chunks_reserved) {
            /* check that there is enough memory left */
            if (i + alloc_chunks > chunks) break;

            /* check that there is enough consecutive chunks available */
            for (j = i; j < i + alloc_chunks; j++) {
                if (hlina_chunks[j].chunks_reserved) {
                    skip_chunks = 1;
                    /* skip the used chunks */
                    i = j + hlina_chunks[j].chunks_reserved;
                    break;
                }
            }

            /* if enough free memory found */
            if (!skip_chunks) {
                *busaddr = hlina_chunks[i].bus_address;
                hlina_chunks[i].filp = filp;
                hlina_chunks[i].chunks_reserved = alloc_chunks;
                break;
            }
        } else {
            /* skip the used chunks */
            i += hlina_chunks[i].chunks_reserved;
        }
    }
    spin_unlock(&s_mem_lock);
#else /* else of SUPPORT_RESERVED_VIDEO_MEMORY */
    unsigned long phys_addr;
    unsigned long base;
    unsigned long nSize = size;
#ifdef CONFIG_RTK_RESERVE_MEMORY
    unsigned int ret = pu_alloc_dma_buffer(nSize, &phys_addr, &base, mem_type);
    if(ret == -1)
    {
        printk(KERN_ERR "memalloc: Physical memory allocation error size=%d\n", nSize);
        return -EFAULT;
    }
#else /* else of CONFIG_RTK_RESERVE_MEMORY */
    base = (unsigned long)dma_alloc_coherent(s_memalloc_dev.this_device, PAGE_ALIGN(nSize), (dma_addr_t *) (&phys_addr), GFP_DMA | GFP_KERNEL);
    if ((void *)(base) == NULL)	{
        printk(KERN_ERR "memalloc: Physical memory allocation error size=%d\n", (int)nSize);
        return -EFAULT;
    }
#endif /* end of CONFIG_RTK_RESERVE_MEMORY */
    spin_lock(&s_mem_lock);
    for (i = 0; i < chunks; i++)
    {
        if (!rtk_hlina_chunks[i].filp)
        {
            rtk_hlina_chunks[i].size = size;
            rtk_hlina_chunks[i].base = base;
            rtk_hlina_chunks[i].phys_addr = phys_addr;
            rtk_hlina_chunks[i].filp = filp;
            *busaddr = rtk_hlina_chunks[i].phys_addr;
            PDEBUG("memalloc: base:0x%lx, phy_addr:0x%lx, size:%d\n", rtk_hlina_chunks[i].base, rtk_hlina_chunks[i].phys_addr, rtk_hlina_chunks[i].size);
            break;
        }
    }
    spin_unlock(&s_mem_lock);
#endif /* end of SUPPORT_RESERVED_VIDEO_MEMORY */

    if (*busaddr == 0) {
        printk("memalloc: Allocation FAILED: size = %d\n", (int)size);
        return -EFAULT;
    } else {
        PDEBUG("MEMALLOC OK: size: %d, reserved: %ld\n", (int)size,
               alloc_chunks * CHUNK_SIZE);
    }

    return 0;
}

/* Free a buffer based on bus address */
static int FreeMemory(unsigned long busaddr, const struct file *filp) {
    int i = 0;

#ifdef SUPPORT_RESERVED_VIDEO_MEMORY
    spin_lock(&s_mem_lock);
    for (i = 0; i < chunks; i++) {
        /* user space SW has stored the translated bus address, add addr_transl to
         * translate back to our address space */
        if (hlina_chunks[i].bus_address == busaddr + addr_transl) {
            if (hlina_chunks[i].filp == filp) {
                hlina_chunks[i].filp = NULL;
                hlina_chunks[i].chunks_reserved = 0;
            } else {
                printk(KERN_WARNING "memalloc: Owner mismatch while freeing memory!\n");
            }
            break;
        }
    }
    spin_unlock(&s_mem_lock);
#else /* else of SUPPORT_RESERVED_VIDEO_MEMORY */
    unsigned long phys_addr = 0;
    unsigned long base = 0;
    unsigned long size = 0;
    spin_lock(&s_mem_lock);
    for (i = 0; i < chunks; i++)
    {
        if (rtk_hlina_chunks[i].phys_addr == busaddr)
        {
            if (rtk_hlina_chunks[i].filp == filp)
            {
                phys_addr = rtk_hlina_chunks[i].phys_addr;
                base = rtk_hlina_chunks[i].base;
                size = rtk_hlina_chunks[i].size;
                rtk_hlina_chunks[i].filp = NULL;
            }
            else
            {
                printk(KERN_WARNING "memalloc: Owner mismatch while freeing memory (0x%x)!\n", (int)busaddr);
            }
            break;
        }
    }
    spin_unlock(&s_mem_lock);
    if (phys_addr != 0 && base!= 0 && size != 0)
    {
#ifdef CONFIG_RTK_RESERVE_MEMORY
        pu_free_dma_buffer(base, phys_addr);
#else
        if (base)
            dma_free_coherent(s_memalloc_dev.this_device, PAGE_ALIGN(size), (void *)base, phys_addr);
#endif
    }
#endif /* end of SUPPORT_RESERVED_VIDEO_MEMORY */
    return 0;
}

/* Reset "used" status */
static void ResetMems(void) {
    spin_lock(&s_mem_lock);
#ifdef SUPPORT_RESERVED_VIDEO_MEMORY
    int i = 0;
    unsigned long ba = alloc_base;

    for (i = 0; i < chunks; i++) {
        hlina_chunks[i].bus_address = ba;
        hlina_chunks[i].filp = NULL;
        hlina_chunks[i].chunks_reserved = 0;

        ba += CHUNK_SIZE;
    }
#else /* else of SUPPORT_RESERVED_VIDEO_MEMORY */
    memset(rtk_hlina_chunks, 0, (chunks * sizeof(rtk_hlina_chunk)));
#endif /* end of SUPPORT_RESERVED_VIDEO_MEMORY */
    spin_unlock(&s_mem_lock);
}

module_init(memalloc_init);
module_exit(memalloc_cleanup);

/* module description */
MODULE_LICENSE("Proprietary");
MODULE_AUTHOR("Google Finland Oy");
MODULE_DESCRIPTION("Linear RAM allocation");
