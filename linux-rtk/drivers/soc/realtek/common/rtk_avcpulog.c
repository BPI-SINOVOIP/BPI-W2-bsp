/*
 * rtk_avcpulog.c - avcpu share-memory logging driver
 *
 * Copyright (c) 2019 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/sched.h>
#include <linux/workqueue.h>
#include <linux/completion.h>
#include <linux/of.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/platform_device.h>
#include <asm/io.h>
#include <soc/realtek/rtk_ipc_shm.h>
#include <soc/realtek/rtk_sb2_sem.h>

#define MODULE_NAME		"avlog"
#define MODULE_NUM		1
#define HWSEM_COMPAT_NAME	"realtek,sb2-sem-avlog"
#define HWSEM_DEF_TIMEOUT	500 /* msec */
#define WORK_DEF_DELAY_TIME	500 /* msec */

typedef enum {
	L_PENDING,
	L_RUNNING,
	L_WAITING,
	L_EXIT,
	L_ERR,
} LOG_STAT;

typedef struct {
	/* static vars */
	struct class *class;
	struct device *device;
	struct cdev cdev;
	struct sb2_sem *avcpu_sem;
	struct avcpu_syslog_struct *syslog_p;
	struct delayed_work log_check_work;
	void __iomem *log_buf;
	/* dynamic vars */
	spinlock_t lock;
	atomic_t cnt;
	LOG_STAT stat;
	struct task_struct *tsk;
	uint32_t record_start;
	struct completion completion;
	/* dynamic vars doesn't require lock */
	unsigned int hwsem_timeout;
	unsigned int work_delay;
} avlog_ctl_t;

/* return value 0 means success getting semaphore with preempt disabled */
static inline int avlog_hwsem_get(struct sb2_sem *sem, unsigned int timeout)
{
	unsigned long jif_timeout;

	jif_timeout = jiffies + msecs_to_jiffies(timeout);
	while(time_before(jiffies, jif_timeout)) {
		preempt_disable();
		/* 1 means lock acquired */
		if (sb2_sem_try_lock(sem, 0)) {
			mb();
			return 0;
		}
		preempt_enable();
		msleep(10);
	}

	return -1;
}

static inline int avlog_hwsem_put(struct sb2_sem *sem)
{
	/* write barrier to ensure share data updated before release hwsem */
	wmb();
	sb2_sem_unlock(sem);
	preempt_enable();
	return 0;
}

static void log_check_work_fn(struct work_struct *work)
{
	avlog_ctl_t *ctl = container_of(work, avlog_ctl_t, log_check_work.work);
	struct sb2_sem *sem = ctl->avcpu_sem;
	uint32_t log_start, log_end;

	/* wake up reader if fail to get semaphore */
	if (avlog_hwsem_get(sem, ctl->hwsem_timeout)) {
		pr_err("%s : timeout waiting for hwsem\n", __func__);
		spin_lock(&ctl->lock);
		ctl->stat = L_ERR;
		spin_unlock(&ctl->lock);
		complete_all(&ctl->completion);
		return;
	}

	/* check if log had updated, if yes wake up reader. If not,
	   schedule another work and keeps reader sleep */
	log_start = ctl->syslog_p->log_start;
	log_end = ctl->syslog_p->log_end;
	avlog_hwsem_put(sem);

	spin_lock(&ctl->lock);

	/* Don't do anything if current reader is not in waiting stat */\
	if (ctl->stat != L_WAITING) {
		spin_unlock(&ctl->lock);
		return;
	}

	if (log_start != log_end) {
		complete_all(&ctl->completion);
		ctl->stat = L_RUNNING;
	} else {
		if (!schedule_delayed_work(&ctl->log_check_work,
			msecs_to_jiffies(ctl->work_delay))) {
			/* wake up reader directly or reader may sleep forever */
			pr_err("%s: fail to schedule work\n", __func__);
			ctl->stat = L_ERR;
			complete_all(&ctl->completion);
		}
	}

	spin_unlock(&ctl->lock);
}

static int rtk_avcpu_log_open(struct inode *inode, struct file *filp)
{
	avlog_ctl_t *ctl = container_of(inode->i_cdev, avlog_ctl_t, cdev);
	struct sb2_sem *sem = ctl->avcpu_sem;
	uint32_t log_start;

	/* hold sem first since we want to record reader-pointer(log_start) */
	if (avlog_hwsem_get(sem, ctl->hwsem_timeout)) {
		pr_debug("%s: couldn't get hw-sem for more then %d msec\n",
			__func__, HWSEM_DEF_TIMEOUT);
		return -EBUSY;
	}

	log_start = ctl->syslog_p->log_start;
	avlog_hwsem_put(sem);

	spin_lock(&ctl->lock);

	/* we assume L_ERR might have chance to recover?? */
	if (ctl->stat != L_PENDING) {
		spin_unlock(&ctl->lock);
		return -EBUSY;
	}

	ctl->tsk = current;
	ctl->record_start = log_start;
	ctl->stat = L_RUNNING;
	filp->private_data = ctl;
	atomic_inc(&ctl->cnt);
	spin_unlock(&ctl->lock);

	return 0;
}

static int rtk_avcpu_log_release(struct inode *inode, struct file *filp)
{
	avlog_ctl_t *ctl = container_of(inode->i_cdev, avlog_ctl_t, cdev);

	spin_lock(&ctl->lock);

	ctl->tsk = NULL;
	if (ctl->stat != L_ERR)
		ctl->stat = L_PENDING;
	spin_unlock(&ctl->lock);
	atomic_dec(&ctl->cnt);

	if (delayed_work_pending(&ctl->log_check_work))
		cancel_delayed_work_sync(&ctl->log_check_work);

	return 0;
}

static ssize_t rtk_avcpu_log_read(struct file *filp, char __user *buf,
		size_t count, loff_t *f_pos)
{
	avlog_ctl_t *ctl = (avlog_ctl_t *)filp->private_data;
	struct sb2_sem *sem = ctl->avcpu_sem;
	struct avcpu_syslog_struct *p_syslog = ctl->syslog_p;
	const char drop_msg[] = "*** LOG DROP ***\n";
	char *iter = NULL, *tmp_buf = NULL;
	int err = 0, rcount = 0, log_count = 0, cp_count = 0;
	unsigned int idx_start, idx_end;

again:
	/* if reader wake up by any signal under sleep stat,
	   switch back to running stat since it's not cause by error*/
	if (signal_pending(current)) {
		spin_lock(&ctl->lock);
		if (ctl->stat == L_WAITING)
			ctl->stat = L_RUNNING;
		spin_unlock(&ctl->lock);
		if (delayed_work_pending(&ctl->log_check_work))
			cancel_delayed_work(&ctl->log_check_work);
		return -EINTR;
	}

	if (avlog_hwsem_get(sem, ctl->hwsem_timeout)) {
		spin_lock(&ctl->lock);
		ctl->stat = L_ERR;
		spin_unlock(&ctl->lock);
		pr_err("%s: fail to get hwsem\n", __func__);
		return -EBUSY;
	}

	spin_lock(&ctl->lock);

	if (ctl->stat != L_RUNNING) {
		spin_unlock(&ctl->lock);
		avlog_hwsem_put(sem);
		return -EFAULT;
	}

	/* log_start & log_end is incremental, need to change policy if overflow happened */
	if (p_syslog->log_start < ctl->record_start ||
	    p_syslog->log_end < p_syslog->log_start) {
		pr_err("%s: log_start:0x%x, log_end:0x%x, record_start:0x%x\n",
			__func__, p_syslog->log_start, p_syslog->log_end, ctl->record_start);
		ctl->stat = L_ERR;
		spin_unlock(&ctl->lock);
		avlog_hwsem_put(sem);
		return -ENOSPC;
	}

	/* Log had been rolled over, return the drop msg directly */
	if (p_syslog->log_start != ctl->record_start) {
		if (count <= strlen(drop_msg)) {
			pr_info("%s: read buf size %d too small\n",
				__func__, (int)count);
			cp_count = count -1;
		} else {
			cp_count = strlen(drop_msg);
		}

		pr_debug("%s: drop, record_start:0x%x, log_start:0x%x\n",
			__func__, ctl->record_start, p_syslog->log_start);
		ctl->record_start = p_syslog->log_start;
		spin_unlock(&ctl->lock);
		avlog_hwsem_put(sem);

		if (copy_to_user(buf, drop_msg, cp_count)) {
			pr_err("%s: copy fail\n", __func__);
			return -EFAULT;
		}

		put_user('\0', buf + cp_count);
		rcount = cp_count + 1;
		return rcount;
	}

	/* Log buf empty, go to sleep until new log came in */
	if (p_syslog->log_start == p_syslog->log_end) {
		ctl->stat = L_WAITING;
		reinit_completion(&ctl->completion);
		if (!schedule_delayed_work(&ctl->log_check_work,
			msecs_to_jiffies(ctl->work_delay))) {
			pr_err("%s: fail to schedule work\n", __func__);
			ctl->stat = L_ERR;
			spin_unlock(&ctl->lock);
			avlog_hwsem_put(sem);
			return -EFAULT;
		}
		spin_unlock(&ctl->lock);
		avlog_hwsem_put(sem);
		/* work should switch stat back to L_RUNNING */
		wait_for_completion_interruptible(&ctl->completion);
		goto again;
	}


	/* Only emit log if no error or DROP happened */
	/* Ok, now there is valid log inside log buffer. Try to read
	   as much as we could */
	log_count = p_syslog->log_end - p_syslog->log_start;
	/* make sure if user buffer is enough, if not, fill the buffer */
	if (log_count > count)
		cp_count = count;
	else
		cp_count = log_count;

	if (!(tmp_buf = kzalloc(count, GFP_ATOMIC))) {
		pr_err("%s : allocate %d buf fail\n", __func__, (int)count);
		err = -ENOMEM;
	}

	/* since log_start/end is incremental, need to figure out the
	   correct position in the buffer */
	idx_start = p_syslog->log_start % p_syslog->log_buf_len;
	idx_end = p_syslog->log_end % p_syslog->log_buf_len;

	while(!err && cp_count) {
		int tmp_cnt;
		bool wrap;

		wrap = (cp_count + idx_start >= p_syslog->log_buf_len) ? true : false;
		tmp_cnt = wrap ? (p_syslog->log_buf_len - idx_start) :
				cp_count;

		iter = ctl->log_buf + idx_start;
		pr_debug("%s: tmp_buf:0x%p, rcount:%d, log_buf:0x%p, log_start:0x%x, tmp_cnt:%d\n",
			__func__, tmp_buf, rcount, ctl->log_buf, idx_start, tmp_cnt);
		memcpy(tmp_buf + rcount, iter, tmp_cnt);
		rcount += tmp_cnt;
		cp_count -= tmp_cnt;
		idx_start = (idx_start + tmp_cnt) % p_syslog->log_buf_len;
	}

	p_syslog->log_start += rcount;
	ctl->record_start = p_syslog->log_start;

	spin_unlock(&ctl->lock);
	avlog_hwsem_put(sem);

	if (!err) {
		if (copy_to_user(buf, tmp_buf, rcount)) {
			pr_err("%s: copy fail\n", __func__);
			err = -EFAULT;
		}
	}

	kfree(tmp_buf);
	return err ? err : rcount;
}

static const struct file_operations rtk_avcpu_log_fops = {
        .owner = THIS_MODULE,
        .open = rtk_avcpu_log_open,
        .read = rtk_avcpu_log_read,
	.release = rtk_avcpu_log_release,
};

static int __init parse_dtb(avlog_ctl_t *alog_ctl, const struct device_node *node)
{
	int ret = 0;
	unsigned int val = 0;
	struct device_node *np = NULL;
	struct sb2_sem *tmp_sem = NULL;

	if (!alog_ctl || !node) {
		pr_err("%s: error input\n", __func__);
		return -EFAULT;
	}

	/* First, we have to get correct HW Semaphoe */
	np = of_parse_phandle(node, "sync_lock", 0);
	if (!np || !of_device_is_compatible(np, HWSEM_COMPAT_NAME)) {
		pr_err("%s: parsing lock fail\n", __func__);
		return -ENODEV;
	}

	tmp_sem = sb2_sem_node_to_lock(np);
        if (IS_ERR(tmp_sem)) {
                ret = PTR_ERR(tmp_sem);
		pr_err("%s: get sb2_sem fail\n", __func__);
		return ret;
	}

	alog_ctl->avcpu_sem = tmp_sem;

	if (of_property_read_u32(node, "sync_lock_timeout", &val)) {
		pr_info("%s : use default %u for hwsem_timeout\n",
			__func__, HWSEM_DEF_TIMEOUT);
		val = HWSEM_DEF_TIMEOUT;
	}
	alog_ctl->hwsem_timeout = val;

	if (of_property_read_u32(node, "log_check_period", &val)) {
		pr_info("%s : use default %u for work_delay\n",
			__func__, WORK_DEF_DELAY_TIME);
		val = WORK_DEF_DELAY_TIME;
	}
	alog_ctl->work_delay = val;

	return 0;
}

static int __init rtk_avcpu_shm_log_probe(struct platform_device *pdev)
{
	dev_t dev;
	struct avcpu_syslog_struct *tmp_syslog_p =
		(struct avcpu_syslog_struct*)((struct rtk_ipc_shm*)IPC_SHM_VIRT)->printk_buffer;
	avlog_ctl_t *alog_ctl = NULL;
	struct class *class = NULL;
	struct device *device = NULL;
	struct device_node *np = NULL;
	int ret = 0;

	pr_debug("%s: alog addr-0x%x, size-0x%x\n",
		__func__, tmp_syslog_p->log_buf_addr, tmp_syslog_p->log_buf_len);

	/* Check the IPC_SHM part. Related info should be set by bootcode */
	if (tmp_syslog_p->log_buf_addr == 0 || tmp_syslog_p->log_buf_len == 0)
		return -EINVAL;

	/* since avlog is a subnode of rtk_avcpu, check if it exist before parsing */
	np = of_get_child_by_name(pdev->dev.of_node, "avlog");
	if (!np)
		return -ENODEV;

	alog_ctl = kzalloc(sizeof(avlog_ctl_t), GFP_KERNEL);
	if (!alog_ctl) {
		pr_err("%s: couldn't allocate memory for alog\n", __func__);
		return -ENOMEM;
	}

	ret = parse_dtb(alog_ctl, np);
	if (ret) {
		pr_err("%s: parse fail\n", __func__);
		goto fail;
	}

	/* initialize char device part */
	if (alloc_chrdev_region(&dev, 0, MODULE_NUM, MODULE_NAME) < 0) {
		pr_err("%s: fail to reister char-device\n", __func__);
		ret = -ENODEV;
		goto fail;
	}

	cdev_init(&alog_ctl->cdev, &rtk_avcpu_log_fops);
	alog_ctl->cdev.owner = THIS_MODULE;
	ret = cdev_add(&alog_ctl->cdev, dev, MODULE_NUM);
	if (ret) {
		pr_err("%s: cdev_add with ret %d\n", __func__, ret);
		goto fail_unregister_chrdev;
	}

	/* Then, create class and device to spawn node under dev */
	class = class_create(THIS_MODULE, MODULE_NAME);
	if (IS_ERR(class)) {
		ret = PTR_ERR(class);
		pr_err("%s: class_create with ret %d\n", __func__, ret);
		goto fail_unregister_chrdev;
	}

	device = device_create(class, NULL, dev, alog_ctl, MODULE_NAME);
	if (IS_ERR(device)) {
		ret = PTR_ERR(device);
		pr_err("%s: device_create with ret %d\n", __func__, ret);
		goto fail_class_destroy;
	}

	/* Now, finish all the rest of init */
	spin_lock_init(&alog_ctl->lock);
	alog_ctl->syslog_p = tmp_syslog_p;
	alog_ctl->log_buf = ioremap_wc(tmp_syslog_p->log_buf_addr, tmp_syslog_p->log_buf_len);
	if (!alog_ctl->log_buf) {
		pr_err("%s: fail to ioremap\n", __func__);
		ret = -ENOMEM;
		goto fail_class_destroy;
	}
	alog_ctl->cdev.owner = THIS_MODULE;
	alog_ctl->class = class;
	alog_ctl->device = device;
	atomic_set(&alog_ctl->cnt, 0);
	INIT_DELAYED_WORK(&alog_ctl->log_check_work, log_check_work_fn);
	init_completion(&alog_ctl->completion);
	alog_ctl->stat = L_PENDING;

	dev_set_drvdata(&pdev->dev, alog_ctl);

	return 0;

fail_class_destroy:
	class_destroy(class);
fail_unregister_chrdev:
	unregister_chrdev_region(dev, MODULE_NUM);
fail:
	kfree(alog_ctl);

	return ret;
}

static int __exit rtk_avcpu_shm_log_remove(struct platform_device *pdev)
{
	avlog_ctl_t *ctl = (avlog_ctl_t*)dev_get_drvdata(&pdev->dev);
	bool all_finish = false;
	unsigned long timeout;

	if (!ctl)
		return -ENODEV;

	spin_lock(&ctl->lock);
	ctl->stat = L_EXIT;
	if (ctl->tsk)
		do_send_sig_info(SIGKILL, SEND_SIG_FORCED, ctl->tsk, false);
	spin_unlock(&ctl->lock);

	/* wait for 1 sec before reader killed */
	timeout = jiffies + msecs_to_jiffies(1000);
	while(time_before(jiffies, timeout)) {
		if (!atomic_read(&ctl->cnt)) {
			all_finish = true;
			break;
		}
		msleep(20);
	}

	if (!all_finish) {
		pr_err("%s:couldn't finish all reader, release fail\n", __func__);
		return -EBUSY;
	}

	device_destroy(ctl->class, ctl->device->devt);
	class_destroy(ctl->class);
	cdev_del(&ctl->cdev);
	kfree(ctl);

	return 0;
}

static struct of_device_id rtk_avcpu_shm_log_ids[] = {
	{ .compatible = "Realtek,rtk-avcpu" },
	{ /* Sentinel */ },
};

static struct platform_driver rtk_avcpu_shm_log_driver = {
        .probe = rtk_avcpu_shm_log_probe,
        .remove = rtk_avcpu_shm_log_remove,
        .driver = {
                .name = MODULE_NAME,
                .bus = &platform_bus_type,
                .owner = THIS_MODULE,
                .of_match_table = of_match_ptr(rtk_avcpu_shm_log_ids),
        },
};

module_platform_driver(rtk_avcpu_shm_log_driver);

MODULE_DESCRIPTION("Realtek AVCPU log driver");
MODULE_LICENSE("GPL");
