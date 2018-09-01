/*
 * Realtek RPC driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/fcntl.h>
#include <linux/ioctl.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/debugfs.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <soc/realtek/rtk_ipc_shm.h>
#include <soc/realtek/avcpu.h>

#include "rtk_rpc.h"
#include "dc2vo/dc2vo.h"

#ifdef CONFIG_RTK_XEN_SUPPORT
#include <xen/xen.h>
#endif

#ifdef CONFIG_REALTEK_IR
extern int venus_irtx_getscancode(u32, u32*, u32*);
#endif /* CONFIG_REALTEK_IR */

//#define SHOW_TASKS_ON_SYSFS
#define SHOW_TASKS_ON_DEBUGFS
#define RPC_NAME "RTK_RPC"

#ifdef CONFIG_FB_RTK
extern spinlock_t gASLock;
extern void dc_irq_handler(void);
#else
static DEFINE_SPINLOCK(gASLock);
#endif /* CONFIG_FB_RTK */

//#if !defined(CONFIG_FB_RTK) || defined(CONFIG_FB_RTK_FPGA)
//void __iomem *rpc_common_base = NULL;
//void __iomem *rpc_rbussync_base = NULL;
//#endif
volatile void __iomem *rpc_ringbuf_base;
volatile void __iomem *rpc_common_base;
volatile void __iomem *rpc_int_base;
volatile void __iomem *rpc_int_flag;
volatile void __iomem *rpc_refclk_base;

static int rpc_irq;
int rpc_major;

#ifdef SHOW_TASKS_ON_SYSFS
static ssize_t show_tasks(struct device *cd, struct device_attribute *attr,
		char *buf)
{
	RPC_DEV_EXTRA *extra = (RPC_DEV_EXTRA *)dev_get_drvdata(cd);
	RPC_DEV *dev = extra->dev;
	RPC_PROCESS *curr = (RPC_PROCESS *)extra->currProc;
	RPC_PROCESS *proc;
	RPC_THREAD *thread;
	RPC_HANDLER *handler;
	struct task_struct *task;
	ssize_t cnt = 0;

	cnt += scnprintf(buf + cnt, (ssize_t)PAGE_SIZE - cnt, "name: %s\n",
			extra->name);
	cnt += scnprintf(buf + cnt, (ssize_t)PAGE_SIZE - cnt, "currProc: %d\n",
			curr ? curr->pid : 0);
	cnt += scnprintf(buf + cnt, (ssize_t)PAGE_SIZE - cnt, "nextRpc: %x\n",
			extra->nextRpc);
	cnt += scnprintf(buf + cnt, (ssize_t)PAGE_SIZE - cnt, "RingBuf: %x\n",
			dev->ringBuf);
	cnt += scnprintf(buf + cnt, (ssize_t)PAGE_SIZE - cnt, "RingStart: %x\n",
			dev->ringStart);
	cnt += scnprintf(buf + cnt, (ssize_t)PAGE_SIZE - cnt, "RingIn: %x\n",
			dev->ringIn);
	cnt += scnprintf(buf + cnt, (ssize_t)PAGE_SIZE - cnt, "RingOut: %x\n",
			dev->ringOut);
	cnt += scnprintf(buf + cnt, (ssize_t)PAGE_SIZE - cnt, "RingEnd: %x\n",
			dev->ringEnd);

	spin_lock_bh(&extra->lock);
	list_for_each_entry(proc, &extra->tasks, list) {

		task = find_task_by_vpid(proc->pid);

		cnt += scnprintf(buf + cnt, (ssize_t)PAGE_SIZE - cnt, "\nProcess:%s\n",
				task ? task->comm : "N/A");

		list_for_each_entry(handler, &proc->handlers, list) {
			cnt += scnprintf(buf + cnt, (ssize_t)PAGE_SIZE - cnt,
					"\tprogramID:%u\n", handler->programID);
		}

		cnt += scnprintf(buf + cnt, (ssize_t)PAGE_SIZE - cnt, "\tp:%d\n",
				proc->pid);

		list_for_each_entry(thread, &proc->threads, list) {
			cnt += scnprintf(buf + cnt, (ssize_t)PAGE_SIZE - cnt, "\tt:%d\n",
					thread->pid);
		}
	}
	spin_unlock_bh(&extra->lock);
	return cnt;
}

static DEVICE_ATTR(tasks, S_IRUGO, show_tasks, NULL);
#endif /* SHOW_TASKS_ON_SYSFS */

#ifdef SHOW_TASKS_ON_DEBUGFS
static int rpc_debug_node_show(struct seq_file *s, void *unused)
{
	RPC_DEV_EXTRA *extra = (RPC_DEV_EXTRA *)s->private;
	RPC_DEV *dev = extra->dev;
	RPC_PROCESS *curr = (RPC_PROCESS *)extra->currProc;
	RPC_PROCESS *proc;
	RPC_THREAD *thread;
	RPC_HANDLER *handler;
	struct task_struct *task;
	int i;

	seq_printf(s, "name: %s\n", extra->name);
	seq_printf(s, "currProc: %d\n", curr ? curr->pid : 0);
	seq_printf(s, "nextRpc: %x\n", extra->nextRpc);
	seq_printf(s, "RingBuf: %x\n", dev->ringBuf);
	seq_printf(s, "RingStart: %x\n", dev->ringStart);
	seq_printf(s, "RingIn: %x\n", dev->ringIn);
	seq_printf(s, "RingOut: %x\n", dev->ringOut);
	seq_printf(s, "RingEnd: %x\n", dev->ringEnd);

	seq_printf(s, "\nRingBuffer:\n");
	for (i = 0; i < RPC_RING_SIZE; i += 16) {
		uint32_t *addr = (uint32_t *)(AVCPU2SCPU(dev->ringStart) + i);
		seq_printf(s, "%x: %08x %08x %08x %08x\n",
				dev->ringStart + i,
				ntohl(*(addr + 0)),
				ntohl(*(addr + 1)),
				ntohl(*(addr + 2)),
				ntohl(*(addr + 3)));
	}

	spin_lock_bh(&extra->lock);
	list_for_each_entry(proc, &extra->tasks, list) {
		task = find_task_by_vpid(proc->pid);

		seq_printf(s, "\nProcess:%s\n", task ? task->comm : "N/A");

		list_for_each_entry(handler, &proc->handlers, list) {
			seq_printf(s, "\tprogramID:%u\n", handler->programID);
		}

		seq_printf(s, "\tp:%d\n", proc->pid);

		list_for_each_entry(thread, &proc->threads, list) {
			seq_printf(s, "\tt:%d\n", thread->pid);
		}
	}
	spin_unlock_bh(&extra->lock);
	return 0;
}

static int rpc_debug_node_open(struct inode *inode, struct file *file)
{
	return single_open(file, rpc_debug_node_show, inode->i_private);
}

static const struct file_operations rpc_debug_node_ops = {
	.open = rpc_debug_node_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};
#endif /* SHOW_TASKS_ON_DEBUGFS */

static int rpc_event_notify(struct notifier_block *self,
		unsigned long action, void *data);

static struct notifier_block __maybe_unused rpc_event_notifier = {
	.notifier_call  = rpc_event_notify,
};

struct file_operations *rpc_fop_array[] = {
	&rpc_poll_fops, /* poll */
	&rpc_intr_fops /* intr */
};

void **rpc_data_ptr_array[] = {
	(void **)&rpc_poll_devices, /* poll */
	(void **)&rpc_intr_devices /* intr */
};

int rpc_data_size_array[] = {
	sizeof(RPC_DEV), /* poll */
	sizeof(RPC_DEV) /* intr */
};

/*
 * Finally, the module stuff
 */
static struct class *rpc_class;

void rpc_set_flag(uint32_t flag)
{
	struct rtk_ipc_shm __iomem *ipc = (void __iomem *)IPC_SHM_VIRT;

	writel(__cpu_to_be32(flag), &(ipc->audio_rpc_flag));/* audio RPC flag */
	//rtk_rpc_wmb(rpc_common_base, RPC_COMM_SIZE);
	//*((int *)phys_to_virt(0x0000b000)) = flag; // audio RPC flag
	//*((int *)phys_to_virt(0x0000b0d0)) = flag; // audio RPC flag
	//*((int *)phys_to_virt(0x0000b0d4)) = flag; // video RPC flag
	//*((int *)phys_to_virt(0x0000b0d8)) = flag;
}

void rpc_set_ir_wakeup_key(uint32_t uScancode, uint32_t uScancode_msk)
{
	struct rtk_ipc_shm __iomem *ipc = (void __iomem *)IPC_SHM_VIRT;

	pr_info("[%s] uScancode = 0x%x , uScancode_msk = 0x%x ", RPC_NAME, uScancode, uScancode_msk);
	/* audio RPC flag for scancode mask */
	writel(__cpu_to_be32(uScancode_msk), &(ipc->ir_scancode_mask));
	/* audio RPC flag for scancode key */
	writel(__cpu_to_be32(uScancode), &(ipc->ir_wakeup_scancode));
}

uint32_t rpc_get_flag(void)
{
	struct rtk_ipc_shm __iomem *ipc = (void __iomem *)IPC_SHM_VIRT;

	return __be32_to_cpu(readl(&(ipc->audio_rpc_flag)));
}

void rpc_send_interrupt(void)
{
	if (rpc_int_flag != NULL && RPC_HAS_BIT(rpc_int_flag, AUDIO_RPC_SET_NOTIFY)) {
		RPC_SET_BIT(rpc_int_flag, AUDIO_RPC_FEEDBACK_NOTIFY);
#if 0
		/* audio */
		writel((RPC_INT_SA | RPC_INT_WRITE_1), rpc_int_base+RPC_SB2_INT);
	}
#else
	}
	/* audio */
	writel((RPC_INT_SA | RPC_INT_WRITE_1), rpc_int_base+RPC_SB2_INT);
#endif
}
EXPORT_SYMBOL(rpc_send_interrupt);

void dc2vo_send_interrupt(void)
{
	if (rpc_int_flag != NULL && RPC_HAS_BIT(rpc_int_flag, VO_DC_SET_NOTIFY)) {
		RPC_SET_BIT(rpc_int_flag, VO_DC_FEEDBACK_NOTIFY);
		/* audio */
		writel((RPC_INT_SA | RPC_INT_WRITE_1), rpc_int_base+RPC_SB2_INT);
	}
}
EXPORT_SYMBOL(dc2vo_send_interrupt);

static int rpc_event_notify(struct notifier_block *self, unsigned long action,
		void *data)
{
#ifdef CONFIG_REALTEK_AVCPU
	switch (action) {
	case AVCPU_SUSPEND:
		pr_debug("[%s]: AVCPU_SUSPEND...\n", RPC_NAME);
		//rpc_poll_pause();
		rpc_poll_suspend();
		//rpc_intr_pause();
		rpc_intr_suspend();
		//rpc_kern_pause();
		rpc_kern_suspend();
		mdelay(10);
		break;
	case AVCPU_RESUME:
		pr_debug("[%s]: AVCPU_RESUME...\n", RPC_NAME);
		rpc_poll_resume();
		rpc_intr_resume();
		rpc_kern_resume();
		break;
	case AVCPU_RESET_PREPARE:
		pr_debug("[%s]: AVCPU_RESET_PREPARE...\n", RPC_NAME);
		rpc_poll_pause();
		rpc_intr_pause();
		rpc_kern_pause();
		mdelay(10);
		rpc_set_flag(0x00000000);
		break;
	case AVCPU_RESET_DONE:
		pr_debug("[%s]: AVCPU_RESET_DONE...\n", RPC_NAME);
		rpc_poll_init();
		rpc_intr_init();
		rpc_kern_init();
		/* clear the inter-processor interrupts */
		//*((int *)REG_SB2_CPU_INT) = 0x0000007e;
		RPC_SET_BIT(rpc_int_flag, RPC_AUDIO_SET_NOTIFY);
		//rtk_rpc_wmb(rpc_common_base, RPC_COMM_SIZE);
		writel(RPC_INT_AS, rpc_int_base+RPC_SB2_INT);
		writel(RPC_INT_SA, rpc_int_base+RPC_SB2_INT);
		/* Enable the interrupt from system to audio & video */
#if 0
		writel((RPC_INT_SA | RPC_INT_WRITE_1), rpc_int_base+RPC_SB2_INT_EN);
#else
		rpc_send_interrupt();
#endif
		rpc_set_flag(0xffffffff);
		break;
	default:
		break;
	}
#endif /* CONFIG_REALTEK_AVCPU */

	return 0;
}

#ifdef MY_COPY
int my_copy_to_user(int *des, int *src, int size)
{
	char buf[256];
	int count = size;
	void *pSrc = (void *)src;
	int ret = 0;
	int i = 0;

	if (size > 256) {
		BUG();
	}

	while (size >= 4) {
		*(int *)&buf[i] = __raw_readl(pSrc);
		i += 4;
		pSrc += 4;
		size -= 4;
	}

	while (size > 0) {
		buf[i] = __raw_readb(pSrc);
		i++;
		pSrc++;
		size--;
	}

	ret = copy_to_user((int *)des, (int *)buf, count);

	return ret;
}

int my_copy_from_user(volatile void __iomem *des, const void *src, int size)
{

	char buf[256];
	int count = size;
	void *pSrc = (void *)src;
	int ret = 0;
	int i = 0;
	char *csrc, *cdes;

	if (size > 256) {
		BUG();
	}
	pr_debug("[%s] %s(des:%p, src:%p, size:%d) pid:%d tid:%d comm:%s\n",
			RPC_NAME, __func__, des, src, size, current->tgid,
			current->pid, current->comm);
	ret = copy_from_user((unsigned int *)buf, (unsigned int __user *)src, size);

	if(ret!=0){
		printk("[%s][%s]copy_from_user error: %d bytes\n", RPC_NAME, __func__, ret);
	}

	cdes = (char *)des;
	for (i = 0 ; i < size ; i++) {
		cdes[i] = buf[i];
	}

	return 0;
}


int my_copy_user(int *des, int *src, int size)
{
	char *csrc, *cdes;
	int i;

	pr_debug("[%s] %s(des:%p, src:%p, size:%d) pid:%d tid:%d comm:%s\n",
			RPC_NAME, __func__, des, src, size, current->tgid,
			current->pid, current->comm);

	might_fault();

	if ((unsigned long)des < 0xc0000000 &&
			access_ok(VERIFY_WRITE, des, size) == 0)
		BUG();

	if ((unsigned long)src < 0xc0000000 &&
			access_ok(VERIFY_READ, src, size) == 0)
		BUG();

	if (((unsigned long)src & 0x3) || ((unsigned long)des & 0x3))
		pr_warn("[%s] my_copy_user: unaligned happen...\n", RPC_NAME);

	while (size >= 4) {
		*des++ = *src++;
		size -= 4;
	}

	csrc = (char *)src;
	cdes = (char *)des;

	for (i = 0 ; i < size ; i++)
		cdes[i] = csrc[i];

	return 0;
}
#endif /* MY_COPY */

irqreturn_t rpc_isr(int irq, void *dev_id)
{
	int itr;

	//pr_debug("irq number %d...\n", irq);
	itr = readl(rpc_int_base+RPC_SB2_INT);

#ifdef CONFIG_FB_RTK
	dc_irq_handler();
#endif /* CONFIG_FB_RTK */
#if 1
	if (!RPC_HAS_BIT(rpc_int_flag, RPC_AUDIO_FEEDBACK_NOTIFY)) {
		/* to clear interrupt, set bit[0] to 0 then we can clear A2S int */
		if (itr & (RPC_INT_AS))
			writel(RPC_INT_AS, rpc_int_base+RPC_SB2_INT);
#if 1
		return IRQ_HANDLED;
#else
		return IRQ_NONE;
#endif
	} else {
		//unsigned long flags;
		//spin_lock_irqsave(&gASLock,flags);
		RPC_RESET_BIT(rpc_int_flag, RPC_AUDIO_FEEDBACK_NOTIFY);
		//rtk_rpc_wmb(rpc_common_base, RPC_COMM_SIZE);
		//spin_unlock_irqrestore(&gASLock,flags);
	}
#endif

	if (itr & (RPC_INT_AS)) {
		while (itr & (RPC_INT_AS)) {
			/* ack the interrupt */
			if (itr & RPC_INT_AS) {
				/* to clear interrupt, set bit[0] to 0 then we can clear A2S int */
				writel(RPC_INT_AS, rpc_int_base+RPC_SB2_INT);

				if (rpc_intr_devices[RPC_INTR_DEV_AS_ID1].ringIn != rpc_intr_devices[RPC_INTR_DEV_AS_ID1].ringOut) {
					pr_debug("[%s] %s intr\n", RPC_NAME, __func__);
					tasklet_schedule(&(rpc_intr_extra[RPC_INTR_DEV_AS_ID1].tasklet));
				}

				if (rpc_kern_devices[RPC_KERN_DEV_AS_ID1].ringIn != rpc_kern_devices[RPC_KERN_DEV_AS_ID1].ringOut) {
					pr_debug("[%s] %s intr\n", RPC_NAME, __func__);
					wake_up_interruptible(&(rpc_kern_devices[RPC_KERN_DEV_AS_ID1].ptrSync->waitQueue));
				}
			}
			itr = readl(rpc_int_base + RPC_SB2_INT);
		}
	} else {
		//pr_warn("Not RPC interrupt...\n");
#if 1
		return IRQ_HANDLED;
#else
		return IRQ_NONE;
#endif
	}
	return IRQ_HANDLED;
}

static char *rpc_devnode(struct device *dev, umode_t *mode)
{
	*mode = 0666;
	return NULL;
}

static int __maybe_unused rtk_rpc_probe(struct platform_device *pdev)
{
	int result;
	int i;
	char buf[16];
	struct device *dev;
	struct device_node *np = pdev->dev.of_node;
	struct rtk_ipc_shm __iomem *ipc = (void __iomem *)IPC_SHM_VIRT;
	RPC_DEV_EXTRA *extra;

#ifdef SHOW_TASKS_ON_DEBUGFS
	struct dentry *rpcroot;
#endif /* SHOW_TASKS_ON_DEBUGFS */

#ifdef SHOW_TASKS_ON_DEBUGFS
	struct dentry *rpcnode;
#endif /* SHOW_TASKS_ON_DEBUGFS */

	pr_info("[%s] rpc driver initial begin\n", RPC_NAME);

	rpc_refclk_base = ioremap(0x9801B540, 0x8);

	if (WARN_ON(!np))
		pr_err("[%s] Could not found device node\n", RPC_NAME);

	/* register rpc_poll_fops as default file operation */
	rpc_major = RPC_MAJOR;
	result = register_chrdev(rpc_major, RPC_NAME, &rpc_poll_fops);
	if (result < 0) {
		pr_debug("[%s] Can't get major %d\n", RPC_NAME, RPC_MAJOR);
		return result;
	}

	if (rpc_major == 0)
		rpc_major = result; /* dynamic */

	pr_debug("[%s] RPC major number: %d\n", RPC_NAME, rpc_major);

	/* update again ipc = IPC_SHM_VIRT */
	ipc = (void __iomem *)IPC_SHM_VIRT;

	rpc_int_base = of_iomap(np, 0);
	if (WARN_ON(!rpc_int_base))
		pr_warn("[%s] Could not map registers for %s\n", RPC_NAME, np->name);

#if 0
	rpc_int_flag = ioremap(DC_VO_SYNC_ADDR, sizeof(unsigned int));
#else
	rpc_int_flag = &ipc->vo_int_sync;
#endif

	result = rpc_poll_init();
	result = rpc_intr_init();
	result = rpc_kern_init();

	rpc_class = class_create(THIS_MODULE, "rpc");

	if (IS_ERR(rpc_class))
		return PTR_ERR(rpc_class);

	rpc_class->devnode = rpc_devnode;

#ifdef SHOW_TASKS_ON_DEBUGFS
	rpcroot = debugfs_create_dir("rpc", NULL);
#endif /* SHOW_TASKS_ON_DEBUGFS */

	for (i = 0; i < RPC_NR_DEVS; i++) {
		extra = ((i % RPC_NR_PAIR) == 0) ? &rpc_poll_extra[i/RPC_NR_PAIR] : &rpc_intr_extra[i/RPC_NR_PAIR];
		dev = device_create(rpc_class, NULL, MKDEV(rpc_major, i), NULL, "rpc%d", i);

#ifdef SHOW_TASKS_ON_SYSFS
		device_create_file(dev, &dev_attr_tasks);
#endif /* SHOW_TASKS_ON_SYSFS */

#ifdef SHOW_TASKS_ON_DEBUGFS
		sprintf(buf, "rpc%d", i);
		rpcnode = debugfs_create_file(buf, 0444, rpcroot, extra, &rpc_debug_node_ops);
#endif /* SHOW_TASKS_ON_DEBUGFS */

		extra->sdev = dev;
		dev_set_drvdata(dev, extra);
	}

	device_create(rpc_class, NULL, MKDEV(rpc_major, 100), NULL, "rpc100");
	rpc_int_flag = &ipc->vo_int_sync;
	rpc_irq = irq_of_parse_and_map(np, 0);

	if (WARN_ON(!rpc_irq))
		pr_warn("[%s] Could not parse IRQ\n", RPC_NAME);

	pr_info("[%s] rpc_int_base:%p irq:%d\n", RPC_NAME, rpc_int_base, rpc_irq);

	spin_lock_irq(&gASLock);
	RPC_SET_BIT(rpc_int_flag, RPC_AUDIO_SET_NOTIFY);
	//rtk_rpc_wmb(rpc_common_base, RPC_COMM_SIZE);
	//writel(readl(rpc_int_flag)|RPC_AUDIO_SET_NOTIFY, rpc_int_flag);
	spin_unlock_irq(&gASLock);

	result = request_irq(rpc_irq, rpc_isr, IRQF_SHARED|IRQF_NO_SUSPEND, "rpc", (void *)RPC_ID);
	if (result != 0)
		pr_err("[%s] Can't get assigned irq...\n", RPC_NAME);

	/* Enable the interrupt from system to audio & video */
#if 0
	writel((RPC_INT_SA | RPC_INT_WRITE_1), rpc_int_base+RPC_SB2_INT_EN);
#else
	rpc_send_interrupt();
#endif

	rpc_set_flag(0xffffffff);

#ifdef CONFIG_REALTEK_AVCPU
	register_avcpu_notifier(&rpc_event_notifier);
#endif

	pr_info("[%s] rpc driver initial done\n", RPC_NAME);

	return 0;
}

static int __maybe_unused rtk_rpc_remove(struct platform_device *pdev)
{
	return 0;
}

#ifdef CONFIG_PM
/*
 * Disable the interrupt from system to audio & video
 */
static int rtk_rpc_pm_suspend(struct device *dev)
{
#if 1
	int MaxCount = 500;

#ifdef CONFIG_RTK_XEN_SUPPORT
	if (xen_domain() && !xen_initial_domain()) {
		printk(KERN_INFO "[RTK_RPC] skip %s in DomU\n", __func__);
		return 0;
	}
#endif

	pr_info("[%s] Suspend enter\n", RPC_NAME);

	rpc_set_flag(0xdaedffff); /* STOP AUDIO HAS_CHECK */

	while ((rpc_get_flag() != 0x0) && (MaxCount > 0)) {
		mdelay(1);
		MaxCount--;
	}

	rpc_event_notify(NULL, AVCPU_SUSPEND, NULL); /* STOP SYSTEM RPC */

	RPC_RESET_BIT(rpc_int_flag, RPC_AUDIO_SET_NOTIFY); /* Disable Interrupt */
	rtk_rpc_wmb(rpc_common_base, RPC_COMM_SIZE);

	rpc_set_flag(0xdeadffff); /* WAIT AUDIO RPC SUSPEND READY */

	while ((rpc_get_flag() != 0x0) && (MaxCount > 0)) {
		mdelay(1);
		MaxCount--;
	}

	pr_info("[%s] Wait %d ms\n", RPC_NAME, (500 - MaxCount));

#else
	writel(RPC_INT_SA, rpc_int_base+RPC_SB2_INT_EN);
	//writel(RPC_INT_SV, (void *)REG_SB2_CPU_INT_EN);
	//writel(RPC_INT_SV2, (void *)REG_SB2_CPU_INT_EN);
	//rtd_outl(REG_SB2_CPU_INT_EN, RPC_INT_SA);
	//rtd_outl(REG_SB2_CPU_INT_EN, RPC_INT_SV);
	//rtd_outl(REG_SB2_CPU_INT_EN, RPC_INT_SV2);
#endif

	pr_info("[%s] Suspend exit\n", RPC_NAME);

	return 0;
}

static void rtk_rpc_pm_shutdown(struct platform_device *pdev)
{
#if 1
	int MaxCount = 500;
	struct device *dev = &pdev->dev;

	dev_info(dev, "Enter %s\n", __func__);

	rpc_set_flag(0xdaedffff); /* STOP AUDIO HAS_CHECK */

	while ((rpc_get_flag() != 0x0) && (MaxCount > 0)) {
		mdelay(1);
		MaxCount--;
	}

	rpc_event_notify(NULL, AVCPU_SUSPEND, NULL); /* STOP SYSTEM RPC */

	RPC_RESET_BIT(rpc_int_flag, RPC_AUDIO_SET_NOTIFY); /* Disable Interrupt */
	rtk_rpc_wmb(rpc_common_base, RPC_COMM_SIZE);

	rpc_set_flag(0xdeadffff); /* WAIT AUDIO RPC SUSPEND READY */

	while ((rpc_get_flag() != 0x0) && (MaxCount > 0)) {
		mdelay(1);
		MaxCount--;
	}

	pr_info("[%s] Wait %d ms\n", RPC_NAME, (500 - MaxCount));

#else
	writel(RPC_INT_SA, rpc_int_base+RPC_SB2_INT_EN);
#endif

	dev_info(dev, "Exit %s\n", __func__);
}

/*
 * Enable the interrupt from system to audio & video
 */
static int rtk_rpc_pm_resume(struct device *dev)
{
#ifdef CONFIG_RTK_XEN_SUPPORT
	if (xen_domain() && !xen_initial_domain()) {
		printk(KERN_INFO "[RTK_RPC] skip %s in DomU\n", __func__);
		return 0;
	}
#endif

	pr_info("[%s] Resume enter\n", RPC_NAME);

#if 1
	RPC_SET_BIT(rpc_int_flag, RPC_AUDIO_SET_NOTIFY);
	//rtk_rpc_wmb(rpc_common_base, RPC_COMM_SIZE);
	rpc_set_flag(0xffffffff);
#else
	writel((RPC_INT_SA | RPC_INT_WRITE_1), rpc_int_base+RPC_SB2_INT_EN);
	//writel((RPC_INT_SV | RPC_INT_WRITE_1), (void *)REG_SB2_CPU_INT_EN);
	//writel((RPC_INT_SV2 | RPC_INT_WRITE_1), (void *)REG_SB2_CPU_INT_EN);
	//rtd_outl(REG_SB2_CPU_INT_EN, (RPC_INT_SA | RPC_INT_WRITE_1));
	//rtd_outl(REG_SB2_CPU_INT_EN, (RPC_INT_SV | RPC_INT_WRITE_1));
	//rtd_outl(REG_SB2_CPU_INT_EN, (RPC_INT_SV2 | RPC_INT_WRITE_1));
#endif

	rpc_event_notify(NULL, AVCPU_RESUME, NULL);

	pr_info("[%s] Resume exit\n", RPC_NAME);

	return 0;
}

static const struct dev_pm_ops rtk_rpc_pm_ops = {
	.suspend_late = rtk_rpc_pm_suspend,
	.resume_early = rtk_rpc_pm_resume,
	.poweroff = rtk_rpc_pm_suspend,
#ifdef CONFIG_HIBERNATION
	.freeze = rtk_rpc_pm_suspend,
	.thaw = rtk_rpc_pm_resume,
	.restore = rtk_rpc_pm_resume,
#endif
};
#endif /* CONFIG_PM */

static struct __maybe_unused of_device_id rtk_rpc_ids[] = {
	{.compatible = "Realtek,rtk-rpc" },
	{/* Sentinel */ },
};

static struct platform_driver rtk_rpc_driver = {
	.probe = rtk_rpc_probe,
	.remove = rtk_rpc_remove,
#ifdef CONFIG_PM
	.shutdown = rtk_rpc_pm_shutdown,
#endif /* CONFIG_PM */
	.driver = {
		.name = "Realtek,rtk-rpc",
		.bus = &platform_bus_type,
		.of_match_table = rtk_rpc_ids,
#ifdef CONFIG_PM
		.pm = &rtk_rpc_pm_ops,
#endif /* CONFIG_PM */
	},
};

module_platform_driver(rtk_rpc_driver);
MODULE_LICENSE("Dual BSD/GPL");
