/*
 * Copyright (c) 2013-2015, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#define pr_fmt(fmt) "rtktrace: " fmt

#include <linux/atomic.h>
#include <linux/export.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/dma-mapping.h>
#include <linux/mod_devicetable.h>
#include <linux/platform_device.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/atomic.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/io.h>
#include <asm-generic/sizes.h>
#include <linux/rtk_trace.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define MODULE_NAME	"rtktrace"


#define SENTINEL_BYTE_1 0xFF
#define SENTINEL_BYTE_2 0xAA
#define SENTINEL_BYTE_3 0xFF

#define VMAP_MAGIC	0x11223344

extern void external_vmap_area_lock(void);
extern void external_vmap_area_unlock(void);

/* Write
 * 1) 3 bytes sentinel
 * 2) 1 bytes of log type
 * 3) 8 bytes of where the caller came from
 * 4) 4 bytes index
 * 4) 8 bytes extra data from the caller
 * 5) 8 bytes of timestamp
 *
 * Total = 32 bytes.
 */
struct rtk_trace_layout {
	unsigned char sentinel[3];
	unsigned char log_type;
	uint32_t idx;
	uint64_t caller;
	uint64_t data;
	uint64_t timestamp;
} __attribute__ ((__packed__));


struct rtk_trace_state {
	struct rtk_trace_layout *t_buf;
	phys_addr_t phys;
	int nentries;
	int size;
	int enabled;
	int initialized;
	uint32_t filter;
	int step_size;
};

struct rtk_trace_dump_device {
	char name[32];
	struct miscdevice device;
	int size;
	char *last_buf;
};

/* structure & variables used for vmap info */
struct rtk_trace_vmap_info {
	uint64_t va;
	uint64_t size;
	uint64_t pa;
	uint32_t magic;
	uint32_t dummy;
} __attribute__ ((__packed__));

struct vmap_info_stat_t {
	spinlock_t lock;
	void *vmap_p;
	int vmap_size;
	int count;
};

DEFINE_PER_CPU(atomic_t, rtk_trace_idx_cpu);

static struct vmap_info_stat_t vmap_info_stat;
static atomic_t vmap_initialized __read_mostly = ATOMIC_INIT(0);

static struct rtk_trace_state rtk_trace = {
	/* remove rtk_trace.filter from cmdline to control the filter here */
	.filter = (1 << LOGK_READL)|(1 << LOGK_WRITEL)|(1 << LOGK_LOGBUF)|(1 << LOGK_HOTPLUG)|(1 << LOGK_CTXID)|(1 << LOGK_IRQ)|(1 << LOGK_DIE)|(1 << LOGK_INITCALL)|(1 << LOGK_SOFTIRQ)|(1 << LOGK_HVC),
	.enabled = 1,
};

module_param_named(filter, rtk_trace.filter, uint, 0644);
module_param_named(enable, rtk_trace.enabled, int, 0644);

void rtk_trace_disable(void)
{
	rtk_trace.enabled = 0;
	return;
}
EXPORT_SYMBOL(rtk_trace_disable);

static int rtk_trace_panic_notifier(struct notifier_block *this,
					unsigned long event, void *ptr)
{
	rtk_trace.enabled = 0;
	pr_info("stop due to panic\n");
	return NOTIFY_DONE;
}

static struct notifier_block rtk_trace_panic_blk = {
	.notifier_call  = rtk_trace_panic_notifier,
};

int notrace rtk_trace_event_should_log(enum logk_event_type log_type)
{
	return rtk_trace.initialized && rtk_trace.enabled &&
		((1 << (log_type & ~LOGTYPE_NOPC)) & rtk_trace.filter);
}
EXPORT_SYMBOL(rtk_trace_event_should_log);

static void rtk_trace_emit_sentinel(struct rtk_trace_layout *start)
{
	start->sentinel[0] = SENTINEL_BYTE_1;
	start->sentinel[1] = SENTINEL_BYTE_2;
	start->sentinel[2] = SENTINEL_BYTE_3;
}

static void rtk_trace_write_type(enum logk_event_type log_type,
			struct rtk_trace_layout *start)
{
	start->log_type = (char)log_type;
}

static void rtk_trace_write_caller(uint64_t caller, struct rtk_trace_layout *start)
{
	start->caller = caller;
}

static void rtk_trace_write_idx(uint32_t idx,
				struct rtk_trace_layout *start)
{
	start->idx = idx;
}

static void rtk_trace_write_data(uint64_t data, struct rtk_trace_layout *start)
{
	start->data = data;
}

static void rtk_trace_write_timestamp(struct rtk_trace_layout *start)
{
	start->timestamp = sched_clock();
}

static void uncached_logk_pc_idx(enum logk_event_type log_type, uint64_t caller,
				 uint64_t data, int idx)
{
	struct rtk_trace_layout *start;

	start = &rtk_trace.t_buf[idx & (rtk_trace.nentries - 1)];

	rtk_trace_emit_sentinel(start);
	rtk_trace_write_type(log_type, start);
	rtk_trace_write_caller(caller, start);
	rtk_trace_write_idx(idx, start);
	rtk_trace_write_data(data, start);
	rtk_trace_write_timestamp(start);
	mb();

	return;
}

static void uncached_logk_timestamp(int idx)
{
	unsigned long long timestamp;

	timestamp = sched_clock();
	uncached_logk_pc_idx(LOGK_TIMESTAMP|LOGTYPE_NOPC,
			(uint64_t)lower_32_bits(timestamp),
			(uint64_t)upper_32_bits(timestamp), idx);
}

/*
 * Since it is not necessarily true that nentries % step_size == 0,
 * must make appropriate adjustments to the index when a "wraparound"
 * occurs to ensure that rtk_trace.t_buf[x] always belongs to the same cpu.
 * It is desired to give all cpus the same number of entries; this leaves
 * (nentries % step_size) dead space at the end of the buffer.
 */
static int rtk_trace_get_idx(void)
{
	int cpu, i, offset;
	atomic_t *index;
	unsigned long flags;
	u32 unused_buffer_size = rtk_trace.nentries % rtk_trace.step_size;
	int adjusted_size;

	/*
	 * ideally we would use get_cpu but this is a close enough
	 * approximation for our purposes.
	 */
	cpu = raw_smp_processor_id();

	index = &per_cpu(rtk_trace_idx_cpu, cpu);

	local_irq_save(flags);
	i = atomic_add_return(rtk_trace.step_size, index);
	i -= rtk_trace.step_size;

	/*
	 * Check if index has wrapped around or is in the unused region at the
	 * end of the buffer
	 */
	adjusted_size = atomic_read(index) + unused_buffer_size;
	offset = (adjusted_size & (rtk_trace.nentries - 1)) -
		 ((adjusted_size - rtk_trace.step_size) & (rtk_trace.nentries - 1));
	if (offset < 0) {
		uncached_logk_timestamp(i);
		i = atomic_add_return(rtk_trace.step_size + unused_buffer_size,
									index);
		i -= rtk_trace.step_size;
	}
	local_irq_restore(flags);

	return i;
}

int notrace uncached_logk_pc(enum logk_event_type log_type, void *caller,
				void *data)
{
	int i;

	if (!rtk_trace_event_should_log(log_type))
		return 0;

	i = rtk_trace_get_idx();
	uncached_logk_pc_idx(log_type, (uint64_t)((unsigned long) caller),
				(uint64_t)((unsigned long) data), i);

	return 1;
}
EXPORT_SYMBOL(uncached_logk_pc);

noinline int notrace uncached_logk(enum logk_event_type log_type, void *data)
{
	return uncached_logk_pc(log_type, __builtin_return_address(0), data);
}
EXPORT_SYMBOL(uncached_logk);

static int rtk_trace_open(struct inode *inode, struct file *filep)
{
	struct rtk_trace_dump_device *td_dev = container_of(filep->private_data, struct rtk_trace_dump_device, device);
	pr_info("%s opened by %s(%d)\n", td_dev->name, current->comm, current->pid);
        return 0;
}

static int rtk_trace_release(struct inode *inode, struct file *filep)
{
	struct rtk_trace_dump_device *td_dev = container_of(filep->private_data, struct rtk_trace_dump_device, device);
	pr_info("%s closed by %s(%d)\n", td_dev->name, current->comm, current->pid);
        return 0;
}

static ssize_t rtk_trace_read(struct file *filep, char __user *buf, size_t count, loff_t *pos)
{
	struct rtk_trace_dump_device *td_dev = container_of(filep->private_data, struct rtk_trace_dump_device, device);
	size_t copy_size = 0;
	int ret = 0;

	if (*pos < td_dev->size) {
		copy_size = td_dev->size - *pos;
		copy_size = min(copy_size, count);

		if (copy_to_user(buf, td_dev->last_buf + *pos, copy_size)) {
			ret = -EFAULT;
			goto dump_done;
		}

		*pos += copy_size;
		count -= copy_size;
		buf += copy_size;
		if (count == 0)
			return copy_size;
	}

dump_done:
	*pos = 0;
	return ret;
}

static const struct file_operations rtk_trace_file_ops = {
	.open = rtk_trace_open,
	.release = rtk_trace_release,
	.read = rtk_trace_read,
};

int remove_vmap_info(void *va, int check_init)
{
	struct vmap_info_stat_t *info_stat = &vmap_info_stat;
	struct rtk_trace_vmap_info *iter_info;
	int i;

	if (check_init && !atomic_read(&vmap_initialized))
		return 0;

	spin_lock(&info_stat->lock);
	/* we start from the back since it's easier to found the match item*/
	for (i = info_stat->count - 1 ; i >= 0 ; i--) {
		iter_info = (struct rtk_trace_vmap_info *)info_stat->vmap_p + i;

		if ((u64)va >= iter_info->va && (u64)va < (iter_info->va + iter_info->size))
			break;
	}

	if (i < 0) {
		WARN("Couldn't find record for va:%p\n", va);
		spin_unlock(&info_stat->lock);
		return -EINVAL;
	} else if (i == info_stat->count - 1) {
		/* record is at tail, simply clear the record */
		memset_io(iter_info, 0, sizeof(struct rtk_trace_vmap_info));
	} else {
		memcpy_toio(iter_info, iter_info + 1, (info_stat->count - i - 1) * sizeof(struct rtk_trace_vmap_info));
		iter_info = (struct rtk_trace_vmap_info *)info_stat->vmap_p + info_stat->count - 1;
		memset_io(iter_info, 0, sizeof(struct rtk_trace_vmap_info));
	}

	info_stat->count--;
	spin_unlock(&info_stat->lock);

	return 0;
}

int inject_vmap_info(void *va, unsigned long size , phys_addr_t pa, int check_init)
{
	struct vmap_info_stat_t *info_stat = &vmap_info_stat;
	struct rtk_trace_vmap_info *iter_info = info_stat->vmap_p;

	if (check_init && !atomic_read(&vmap_initialized))
		return 0;

	if ((void*)(iter_info + info_stat->count) >= (info_stat->vmap_p + info_stat->vmap_size)) {
		pr_err("%p exceed reserve buffer %p\n",
			iter_info + info_stat->count, info_stat->vmap_p + info_stat->vmap_size);
		BUG();
	}

	spin_lock(&info_stat->lock);
	iter_info = iter_info + info_stat->count;
	iter_info->va = (uint64_t)va;
	iter_info->size = size;
	iter_info->pa = pa;
	iter_info->magic = VMAP_MAGIC;
	info_stat->count++;
	spin_unlock(&info_stat->lock);

	return 0;
}

#define VM_VM_AREA      0x04 /* flag sync with mm/vmalloc.c */
static int vmap_info_initial(void)
{
	struct vmap_area *va;
	struct vm_struct *vm;

	/* Copy current vmap info first */
	external_vmap_area_lock();
	list_for_each_entry(va, &vmap_area_list, list) {
		/* vmap_area not-ready/invalid, vmalloc didn't use zalloc for vmap_area */
		if (!(va->flags & VM_VM_AREA))
			continue;

		vm = va->vm;

		/* There should be vm_strcut for each vmap_area right? */
		if(!vm)
			continue;

		/* We're not intrested non-ioremapped region */
		if (!(vm->flags & VM_IOREMAP))
			continue;

		/* vmap_area already been invalid?? */
		if ((unsigned long)vm->addr < VMALLOC_START || (unsigned long)vm->addr > VMALLOC_END)
			continue;

		pr_debug("va:%p, size:%lu, pa:%p\n", vm->addr, vm->size, (void*)vm->phys_addr);
		inject_vmap_info(vm->addr, vm->size, vm->phys_addr, 0);
	}

	/* OK, now all the vmap info should be recorded, turn flag on so
	   all the vmap info would be recorded through ioremap */
	atomic_set(&vmap_initialized, 1);
	external_vmap_area_unlock();

	return 0;
}

static int rtk_trace_probe(struct platform_device *pdev)
{
	struct resource *res = NULL, *res_vmap = NULL;
	unsigned int cpu;
	struct rtk_trace_dump_device *dump_device = NULL, *dump_device_vmap = NULL;
	int release_vmap_res = 0;
	int ret = 0;

	if (WARN_ON(!(pdev->dev.of_node))) {
		pr_err("%s, couldn't find node!\n", __func__);
		return -ENODEV;
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "rtk_trace_res");

	if (!res) {
		pr_err("%s, resource not defined\n", __func__);
		return -EINVAL;
	}

	rtk_trace.phys = res->start;
	rtk_trace.size = resource_size(res);
	rtk_trace.t_buf = ioremap(rtk_trace.phys, rtk_trace.size);

	if (!rtk_trace.t_buf)
		return -ENOMEM;

	pr_info("phys:0x%llx, size:0x%x, t_buf:%p\n", rtk_trace.phys, rtk_trace.size, rtk_trace.t_buf);

	rtk_trace.nentries = rtk_trace.size / sizeof(struct rtk_trace_layout);

	/* Round this down to a power of 2 */
	rtk_trace.nentries = __rounddown_pow_of_two(rtk_trace.nentries);

	/* Back up old trace buffer */
	dump_device = kzalloc(sizeof(struct rtk_trace_dump_device), GFP_KERNEL);

	if (dump_device) {
		strncpy(dump_device->name, MODULE_NAME, 32);
		dump_device->last_buf = vmalloc(rtk_trace.size);
		dump_device->size = rtk_trace.size;

		if (dump_device->last_buf) {

			dump_device->device.minor = MISC_DYNAMIC_MINOR;
			dump_device->device.name = dump_device->name;
			dump_device->device.fops = &rtk_trace_file_ops;
			if (!(ret = misc_register(&dump_device->device))) {
				memcpy_fromio(dump_device->last_buf, rtk_trace.t_buf, rtk_trace.size);
			} else {
				pr_err("misc device register fail!\n");
				vfree(dump_device->last_buf);
				kfree(dump_device);
			}
		} else {
			pr_err("couldn't allocate last_buf\n");
			kfree(dump_device);
		}
	} else {
		pr_err("couldn't allocate dump_device\n");
	}

	/* Now, start vmap info region */
	res_vmap = platform_get_resource_byname(pdev, IORESOURCE_MEM, "rtk_trace_vmap");

	vmap_info_stat.vmap_p = NULL;
	vmap_info_stat.vmap_size = 0;
	vmap_info_stat.count = 0;
	spin_lock_init(&vmap_info_stat.lock);

	if (res_vmap) {

		vmap_info_stat.vmap_p = ioremap(res_vmap->start, resource_size(res_vmap));
		vmap_info_stat.vmap_size = resource_size(res_vmap);

		if (!vmap_info_stat.vmap_p) {
			pr_err("can't map region %p/%d\n", (void*)res_vmap->start, (int)resource_size(res_vmap));
			release_vmap_res = 1;
			goto skip_vmap;
		}

		dump_device_vmap = kzalloc(sizeof(struct rtk_trace_dump_device), GFP_KERNEL);

		if (!dump_device_vmap) {
			pr_err("can't allocate memory for dump_device_vmap\n");
			release_vmap_res = 1;
			goto skip_vmap;
		}

		dump_device_vmap->last_buf = vmalloc(vmap_info_stat.vmap_size);
		dump_device_vmap->size = vmap_info_stat.vmap_size;

		if (!dump_device_vmap->last_buf) {
			pr_err("can't allocate memory for dump_device_vmap\n");
			release_vmap_res = 1;
			goto skip_vmap;
		}

		strncpy(dump_device_vmap->name, MODULE_NAME"_vmap", 32);
		dump_device_vmap->device.minor = MISC_DYNAMIC_MINOR;
		dump_device_vmap->device.name = dump_device_vmap->name;
		dump_device_vmap->device.fops = &rtk_trace_file_ops;

		if (!(ret = misc_register(&dump_device_vmap->device))) {
			memcpy_fromio(dump_device_vmap->last_buf, vmap_info_stat.vmap_p, vmap_info_stat.vmap_size);
		} else {
			pr_err("misc-vmap register fail\n");
			release_vmap_res = 1;
			goto skip_vmap;
		}
		/* now the backup is done, start record current vmap info */
		memset_io(vmap_info_stat.vmap_p, 0, vmap_info_stat.vmap_size);
		vmap_info_initial();
	}
skip_vmap:
	/* Now clean up trace buff content */
	memset_io(rtk_trace.t_buf, 0, rtk_trace.size);

	for_each_possible_cpu(cpu) {
		atomic_t *a = &per_cpu(rtk_trace_idx_cpu, cpu);
		atomic_set(a, cpu);
	}
	rtk_trace.step_size = num_possible_cpus();

	atomic_notifier_chain_register(&panic_notifier_list,
						&rtk_trace_panic_blk);
	rtk_trace.initialized = 1;

	if (release_vmap_res) {

		if (vmap_info_stat.vmap_p)
			iounmap(vmap_info_stat.vmap_p);

		if (dump_device_vmap) {
			if (dump_device_vmap->last_buf)
				vfree(dump_device_vmap->last_buf);
			kfree(dump_device_vmap);
		}
	}

	return 0;
}

static struct of_device_id rtktrace_match_table[] = {
	{.compatible = "Realtek,trace"},
	{},
};

static struct platform_driver rtk_trace_driver = {
	.driver         = {
		.name = MODULE_NAME,
		.owner = THIS_MODULE,
		.of_match_table = rtktrace_match_table
	},
};

static int __init rtk_trace_init(void)
{
	return platform_driver_probe(&rtk_trace_driver, rtk_trace_probe);
}

static void __exit rtk_trace_exit(void)
{
	platform_driver_unregister(&rtk_trace_driver);
}
module_init(rtk_trace_init)
module_exit(rtk_trace_exit)
