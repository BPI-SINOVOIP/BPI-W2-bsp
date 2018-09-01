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

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/fcntl.h>
#include <linux/ioctl.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/freezer.h>
#include <linux/ratelimit.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/kthread.h>


#include "rtk_rpc.h"

#include "uapi/ion.h"
#include "ion/ion.h"
#include "uapi/ion_rtk.h"

/*
 * dump ring buffer rate limiting:
 * not more than 1 ring buffer dumping every 3s
 */
DEFINE_RATELIMIT_STATE(ring_dump_state, 3 * HZ, 1);
static DEFINE_SPINLOCK(rpc_alloc_lock);


volatile RPC_DEV *rpc_intr_devices;
int rpc_intr_is_paused;
int rpc_intr_is_suspend;

int timeout = HZ / 40; /* jiffies */

RPC_DEV_EXTRA rpc_intr_extra[RPC_NR_DEVS / RPC_NR_PAIR];

extern void rpc_send_interrupt(void);




struct ion_client *fw_rpc_ion_client;
extern struct ion_device *rtk_phoenix_ion_device;

typedef struct r_program_entry
{
	struct ion_handle *handle;
	unsigned long phys_addr;
	struct r_program_entry *next;
}r_program_entry_t;

static r_program_entry_t *r_program_head = NULL;
static int r_program_count = 0;

struct task_struct *r_program_kthread;
wait_queue_head_t r_program_waitQueue;
int r_program_flag = 0;

static void r_program_add(r_program_entry_t * entry)
{
	spin_lock_bh(&rpc_alloc_lock);
	entry->next = r_program_head;
	r_program_head = entry;
	r_program_count++;
	spin_unlock_bh(&rpc_alloc_lock);
}

static r_program_entry_t *r_program_remove(unsigned long phys_addr)
{
	r_program_entry_t *prev = NULL;
	r_program_entry_t *curr = NULL;

	spin_lock_bh(&rpc_alloc_lock);
	curr = r_program_head;
	while (curr != NULL) {
		if (curr->phys_addr != phys_addr) {
			prev = curr;
			curr = curr->next;
			continue;
		}

		if (prev == NULL) {
			r_program_head = curr->next;
		} else {
			prev->next = curr->next;
		}
		r_program_count--;
		spin_unlock_bh(&rpc_alloc_lock);

		return curr;
	}
	spin_unlock_bh(&rpc_alloc_lock);
	return NULL;
}

ssize_t r_program_read(RPC_DEV_EXTRA *extra, RPC_DEV *dev, char *buf, size_t count)
{
	int temp, size;
	size_t r;
	ssize_t ret = 0;
	uint32_t ptmp;
	int rpc_ring_size = dev->ringEnd - dev->ringStart;

	down_write(&dev->ptrSync->readSem);

	if (dev->ringIn > dev->ringOut)
		size = dev->ringIn - dev->ringOut;
	else
		size = rpc_ring_size + dev->ringIn - dev->ringOut;

	pr_debug("%s:%d ==going read== count:%zu avail:%d "
			"ringOut:%x ringIn:%x nextRPC:%x",
			extra->name, __LINE__, count, size, dev->ringOut, dev->ringIn,
			extra->nextRpc);
	peek_rpc_struct(__func__, dev);
	if (count > size)
		count = size;
	temp = dev->ringEnd - dev->ringOut;
	rtk_rpc_wmb(AVCPU2SCPU(dev->ringStart), PAGE_ALIGN(rpc_ring_size));

	if (temp >= count) {
#ifdef MY_COPY
		r = my_copy_user((int *)buf,
				(int *)AVCPU2SCPU(dev->ringOut), count);
#else
		r = copy_to_user((int *)buf, (int *)AVCPU2SCPU(dev->ringOut), count);
#endif /* MY_COPY */
		if (r) {
			pr_err("%s:%d buf:%p count:%lu EFAULT\n",
				extra->name, __LINE__, buf, count);
			ret = -EFAULT;
			goto out;
		}

		ret = count;
		ptmp = dev->ringOut + ((count+3) & 0xfffffffc);
		if (ptmp == dev->ringEnd)
			dev->ringOut = dev->ringStart;
		else
			dev->ringOut = ptmp;

		//pr_debug("RPC Read is in 1st kind...\n");
	} else {
#ifdef MY_COPY
		r = my_copy_user((int *)buf,
				(int *)AVCPU2SCPU(dev->ringOut), temp);
#else
		r = copy_to_user((int *)buf,
				(int *)AVCPU2SCPU(dev->ringOut), temp);
#endif /* MY_COPY */

		if (r) {
			pr_err("%s:%d buf:%p count:%lu EFAULT\n",
					extra->name, __LINE__, buf, count);
			ret = -EFAULT;
			goto out;
		}

		count -= temp;

#ifdef MY_COPY
		r = my_copy_user((int *)(buf+temp),
				(int *)AVCPU2SCPU(dev->ringStart), count);
#else
		r = copy_to_user((int *)(buf+temp),
				(int *)AVCPU2SCPU(dev->ringStart), count);
#endif /* MY_COPY */

		if (r) {
			pr_err("%s:%d buf:%p count:%lu EFAULT\n",
					extra->name, __LINE__, buf, count);
			ret = -EFAULT;
			goto out;
		}
		ret = (temp + count);
		dev->ringOut = dev->ringStart+((count+3) & 0xfffffffc);

		//pr_debug("RPC Read is in 2nd kind...\n");
	}
	spin_lock_bh(&extra->lock);

	if (rpc_done(extra)) {
		pr_debug("%s: Previous RPC is done, unregister myself\n", extra->name);
		update_currProc(extra, NULL);
	}

	spin_unlock_bh(&extra->lock);

	if (need_dispatch(extra))
		tasklet_schedule(&(extra->tasklet));
	up_write(&dev->ptrSync->readSem);
	return ret;
out:
	pr_err("[%s] read error occur\n", __func__);
	up_write(&dev->ptrSync->readSem);
	return ret;

}


ssize_t r_program_write(RPC_DEV_EXTRA *extra, RPC_DEV *dev, char *buf, size_t count)
{

	int temp, size;
	size_t r;
	ssize_t ret = 0;
	uint32_t ptmp;
	int rpc_ring_size = dev->ringEnd - dev->ringStart;
	RPC_STRUCT *rpc;

	rpc = (RPC_STRUCT *)(buf);
	pr_debug("%s: program:%u version:%u procedure:%u taskID:%u sysTID:%u sysPID:%u size:%u context:%x 90k:%u %s\n",
			__func__, ntohl(rpc->programID), ntohl(rpc->versionID), ntohl(rpc->procedureID), ntohl(rpc->taskID), ntohl(rpc->sysTID), ntohl(rpc->sysPID),
			ntohl(rpc->parameterSize),ntohl(rpc->mycontext), readl(rpc_refclk_base), in_atomic() ? "atomic" : "");
	down_write(&dev->ptrSync->writeSem);

	if (dev->ringIn == dev->ringOut)
		size = 0;   // the ring is empty
	else if (dev->ringIn > dev->ringOut)
		size = dev->ringIn - dev->ringOut;
	else
		size = RPC_RING_SIZE + dev->ringIn - dev->ringOut;

	if (count > (RPC_RING_SIZE - size - 1))
		goto out;

	temp = dev->ringEnd - dev->ringIn;
	if (temp >= count) {
#ifdef MY_COPY
		r = my_copy_user((int *)AVCPU2SCPU(dev->ringIn), (int *)buf, count);
#else
		r = ((int *)AVCPU2SCPU(dev->ringIn) !=
				memcpy((int *)AVCPU2SCPU(dev->ringIn), (int *)buf, count));
#endif /* MY_COPY */
		if (r) {
			ret = -EFAULT;
			goto out;
		}
		ret += count;
		ptmp = dev->ringIn + ((count+3) & 0xfffffffc);

		//asm("DSB");
		mb();

		if (ptmp == dev->ringEnd)
			dev->ringIn = dev->ringStart;
		else
			dev->ringIn = ptmp;

		pr_debug("RPC Write is in 1st kind...\n");
	} else {
#ifdef MY_COPY
		r = my_copy_user((int *)AVCPU2SCPU(dev->ringIn), (int *)buf, temp);
#else
		r = ((int *)AVCPU2SCPU(dev->ringIn) !=
				memcpy((int *)AVCPU2SCPU(dev->ringIn), (int *)buf, temp));
#endif
		if (r) {
			ret = -EFAULT;
			goto out;
		}
		count -= temp;

#ifdef MY_COPY
		r = my_copy_user((int *)AVCPU2SCPU(dev->ringStart),
				(int *)(buf+temp), count);
#else
		r = ((int *)AVCPU2SCPU(dev->ringStart) != memcpy((int *)AVCPU2SCPU(dev->ringStart), (int *)(buf+temp), count));
#endif
		if (r) {
			ret = -EFAULT;
			goto out;
		}
		ret += (temp + count);

		//asm("DSB");
		mb();

		dev->ringIn = dev->ringStart+((count+3) & 0xfffffffc);

		pr_debug("RPC Write is in 2nd kind...\n");
	}

	rtk_rpc_wmb(AVCPU2SCPU(dev->ringStart),
			PAGE_ALIGN(rpc_ring_size));

#if 1
	rpc_send_interrupt();
#else
		/* audio */
		writel((RPC_INT_SA | RPC_INT_WRITE_1), rpc_int_base+RPC_SB2_INT);
#endif
	up_write(&dev->ptrSync->writeSem);
	return ret;
out:
	pr_err("[%s]RingBuf full! RPC FW intr write ringIn pointer is : %p\n", __func__, AVCPU2SCPU(dev->ringIn));
	up_write(&dev->ptrSync->writeSem);
	return ret;
}



void rpc_ion_handler(RPC_DEV_EXTRA *extra)
{
	struct ion_handle *handle = NULL;
	ion_phys_addr_t phys_addr;
	unsigned long reply_value = 0;
	size_t len;
	size_t align;
	size_t alloc_val;
	char tmpbuf[sizeof(RPC_STRUCT) + sizeof(uint32_t)];
	uint32_t *tmp;
	char replybuf[sizeof(RPC_STRUCT) + 2*sizeof(uint32_t)];
	RPC_STRUCT *rpc;
	RPC_STRUCT *rrpc;
	unsigned long map_addr;
	RPC_DEV_EXTRA *extra_w = &rpc_intr_extra[0];
	r_program_entry_t *rpc_entry;


	if (r_program_read(extra, extra->dev, (char *) &tmpbuf, sizeof(RPC_STRUCT) + sizeof(uint32_t)) != (sizeof(RPC_STRUCT) + sizeof(uint32_t))) {
		pr_err("[%s] remote allocate read error...\n", __func__);
		return;
	}
	spin_lock_bh(&extra->lock);
	r_program_flag = 0;
	spin_unlock_bh(&extra->lock);
	rpc = (RPC_STRUCT *)(tmpbuf);

	//convert_rpc_struct(extra->name, rpc);
	pr_debug("%s: program:%u version:%u procedure:%u taskID:%u sysTID:%u sysPID:%u size:%u context:%x 90k:%u %s\n",
			__func__, ntohl(rpc->programID), ntohl(rpc->versionID), ntohl(rpc->procedureID), ntohl(rpc->taskID), ntohl(rpc->sysTID), ntohl(rpc->sysPID),
			ntohl(rpc->parameterSize), ntohl(rpc->mycontext), readl(rpc_refclk_base), in_atomic() ? "atomic" : "");

	if (ntohl(rpc->procedureID) == 1) { /*allocate*/
		align = PAGE_SIZE;
		tmp = (uint32_t *)(tmpbuf + sizeof(RPC_STRUCT));
		alloc_val = PAGE_ALIGN(ntohl(*tmp));
		if ((ntohl(rpc->mycontext) & 0x1) == 0) {
			align = (1 << 14);
		}
		rpc->mycontext = htonl(ntohl(rpc->mycontext) & 0xfffffffc);

		handle = ion_alloc(fw_rpc_ion_client, alloc_val, align,
			RTK_PHOENIX_ION_HEAP_MEDIA_MASK,
			ION_FLAG_NONCACHED | ION_FLAG_SCPUACC | ION_FLAG_HWIPACC | ION_FLAG_ACPUACC);

		if (IS_ERR(handle)) {
			pr_err("[%s] ERROR: ion_alloc fail %d\n", __func__, (int *) handle);
		}
		if (ion_phys(fw_rpc_ion_client, handle, &phys_addr, &alloc_val) != 0) {
			pr_err("[%s] ERROR: ion_phys fail\n", __func__);
		}
		rpc_entry = kmalloc(sizeof(struct r_program_entry), GFP_KERNEL);
		rpc_entry->handle = handle;
		rpc_entry->phys_addr = phys_addr;
		r_program_add(rpc_entry);
#ifdef CONFIG_ARCH_RTD129x
		reply_value = phys_addr + 0x80000000;
#else
		reply_value = phys_addr;
#endif
	} else if(ntohl(rpc->procedureID) == 2) { /*free*/
		tmp = (uint32_t *)(tmpbuf + sizeof(RPC_STRUCT));
#ifdef CONFIG_ARCH_RTD129x
		phys_addr = ntohl(*tmp) - 0x80000000;
#else
		phys_addr = ntohl(*tmp);
#endif
		rpc_entry = r_program_remove(phys_addr);
		if (rpc_entry == NULL){
			pr_err("[%s]cannot find rpc_entry to free:phys_addr:%x\n", __func__, phys_addr);
			return;
		}
		ion_free(fw_rpc_ion_client, rpc_entry->handle);
		kfree(rpc_entry);
		rpc->mycontext = htonl(ntohl(rpc->mycontext) & 0xfffffffc);
		reply_value = 0;
	} else if (ntohl(rpc->procedureID) == 3) { /*Secure allocate*/
		align = PAGE_SIZE;
		tmp = (uint32_t *)(tmpbuf + sizeof(RPC_STRUCT));
		alloc_val = PAGE_ALIGN(ntohl(*tmp));
		if ((ntohl(rpc->mycontext) & 0x1) == 0) {
			align = (1 << 14);
		}
		rpc->mycontext = htonl(ntohl(rpc->mycontext) & 0xfffffffc);

		handle = ion_alloc(fw_rpc_ion_client, alloc_val, align,
			RTK_PHOENIX_ION_HEAP_SECURE_MASK,
			ION_FLAG_NONCACHED  | ION_FLAG_HWIPACC);

		if (IS_ERR(handle)) {
			pr_err("[%s] ERROR: secure ion_alloc fail %d\n", __func__, (int *) handle);
		}
		if (ion_phys(fw_rpc_ion_client, handle, &phys_addr, &alloc_val) != 0) {
			pr_err("[%s] ERROR: secure ion_phys fail\n", __func__);
		}
		rpc_entry = kmalloc(sizeof(struct r_program_entry), GFP_KERNEL);
		rpc_entry->handle = handle;
		rpc_entry->phys_addr = phys_addr;
		r_program_add(rpc_entry);
#ifdef CONFIG_ARCH_RTD129x
		reply_value = phys_addr + 0x80000000;
#else
		reply_value = phys_addr;
#endif
	}

	/*Reply RPC*/
	rrpc = (RPC_STRUCT *)replybuf;
	rrpc->programID = htonl(REPLYID);
	rrpc->versionID = htonl(REPLYID);
	rrpc->procedureID = 0;
	rrpc->taskID = 0;
#ifdef RPC_SUPPORT_MULTI_CALLER_SEND_TID_PID
	rrpc->sysTID = 0;
#endif /* RPC_SUPPORT_MULTI_CALLER_SEND_TID_PID */
	rrpc->sysPID = 0;
	rrpc->parameterSize = htonl(2*sizeof(uint32_t));
	rrpc->mycontext = rpc->mycontext;

	/* fill the parameters... */
	tmp = (uint32_t *)(replybuf + sizeof(RPC_STRUCT));
	*(tmp+0) = rpc->taskID; /* FIXME: should be 64bit */
	*(tmp+1) = htonl(reply_value);

	if (r_program_write(extra_w, extra_w->dev, (char *) &replybuf, sizeof(RPC_STRUCT) + 2*sizeof(uint32_t)) != (sizeof(RPC_STRUCT) + 2*sizeof(uint32_t))) {
		pr_err("[%s] remote allocate reply error...\n", __func__);
		return;
	}

}


static int remote_alloc_thread(void * p)
{
	RPC_DEV_EXTRA *extra = &rpc_intr_extra[1];

	while (1) {
		if (wait_event_interruptible(r_program_waitQueue, r_program_flag || kthread_should_stop())) {
			pr_notice("%s got signal or should stop...\n", current->comm);
			continue;
		}

		if (kthread_should_stop()) {
			pr_notice("%s exit...\n", current->comm);
			break;
		}
		rpc_ion_handler(extra);
	}
	return 0;
}

/*
 * This function may be called by tasklet and rpc_intr_read(),
 * rpc_poll_read()
 */
void rpc_dispatch(unsigned long data)
{
	RPC_DEV_EXTRA *extra = (RPC_DEV_EXTRA *) data;
	RPC_DEV *dev = extra->dev;
	RPC_PROCESS *proc = NULL;
	uint32_t out;
	RPC_STRUCT rpc;
	int found = 0;
	uint32_t ringOut = dev->ringOut;
	uint32_t ringIn = dev->ringIn;
	uint32_t nextRpc = extra->nextRpc;
	RPC_PROCESS *curr = (RPC_PROCESS *)extra->currProc;

	pr_debug("==*==*==%s Out:%x next:%x In:%x size:%d %s==*==*==\n",
			extra->name, ringOut, nextRpc, ringIn, get_ring_data_size(dev), in_atomic() ? "atomic" : "");
	if (curr != NULL || ringOut == ringIn || ringOut != nextRpc) {
		pr_debug("%s: unable to disp. currProc:%d Out:%x next:%x "
				"In:%x size:%d %s\n",
				extra->name, curr ? curr->pid : 0, ringOut, nextRpc, ringIn,
				get_ring_data_size(dev), in_atomic() ? "atomic" : "");
		return;
	}

	//peek_rpc_struct(extra->name, dev);
	out = get_ring_data(extra->name, dev, ringOut, (char *) &rpc,
			sizeof(RPC_STRUCT));
	if (out == 0)
		return;

	convert_rpc_struct(extra->name, &rpc);
	show_rpc_struct(__func__, &rpc);

	switch (rpc.programID) {
	case R_PROGRAM:
		pr_debug("%s: program:%u version:%u procedure:%u taskID:%u sysTID:%u sysPID:%u size:%u context:%x 90k:%u %s\n",
			__func__, rpc.programID, rpc.versionID, rpc.procedureID, rpc.taskID, rpc.sysTID, rpc.sysPID,
			rpc.parameterSize, rpc.mycontext, readl(rpc_refclk_base), in_atomic() ? "atomic" : "");
#if 1   /*audio fw ion remote alloc handled by kernel*/
		out += rpc.parameterSize;
		if (out >= dev->ringEnd)
			out = dev->ringStart + (out - dev->ringEnd);

		spin_lock_bh(&extra->lock);
		update_nextRpc(extra, out);
		r_program_flag = 1;
		wake_up_interruptible(&r_program_waitQueue);
		spin_unlock_bh(&extra->lock);

		return;
#else
#ifdef CONFIG_REALTEK_RPC_PROGRAM_REGISTER
		proc = pick_supported_proc(extra, rpc.programID);
#else
		proc = pick_one_proc(extra);
#endif /* CONFIG_REALTEK_RPC_PROGRAM_REGISTER */
#endif
		break;
	case AUDIO_AGENT:
	case VIDEO_AGENT:
		proc = NULL;
		//show_rpc_struct(extra->name, &rpc);
		/* use sysPID directly */
		if (rpc.sysPID > 0 && rpc.sysPID < pid_max) {
			pr_info("lookup by sysPID:%d\n", rpc.sysPID);
			proc = lookup_by_taskID(extra, rpc.sysPID);
			if (proc == NULL)
				show_rpc_struct(extra->name, &rpc);
#ifdef RPC_SUPPORT_MULTI_CALLER_SEND_TID_PID
		/* lookup pid by sysTID */
		} else if (rpc.sysTID > 0 && rpc.sysTID < pid_max) {
			pr_info("lookup by sysTID:%d\n", rpc.sysTID);
			proc = lookup_by_taskID(extra, rpc.sysTID);
			if (proc == NULL)
				show_rpc_struct(extra->name, &rpc);
		}
#endif /* RPC_SUPPORT_MULTI_CALLER_SEND_TID_PID */
		if (unlikely(proc == NULL)) {
#ifdef CONFIG_REALTEK_RPC_PROGRAM_REGISTER
			proc = pick_supported_proc(extra, rpc.programID);
#else
			proc = pick_one_proc(extra);
#endif
		}
		break;
	case REPLYID:
		if (rpc.versionID == REPLYID &&
				rpc.parameterSize >= sizeof(uint32_t)) {
			uint32_t taskID;
			if (get_ring_data(extra->name, dev, out, (char *) &taskID,
					sizeof(uint32_t)) == 0)
				return;

			taskID = ntohl(taskID);
			pr_debug("%s:%d taskID:%u\n", extra->name, __LINE__, taskID);
			proc = lookup_by_taskID(extra, taskID);
		}
		break;
	default:
		if (in_atomic() && __ratelimit(&ring_dump_state)) {
			pr_err("%s:%d invalid programID:%u!!! Out:%x next:%x In:%x\n",
					__func__, __LINE__, rpc.programID, ringOut, nextRpc,
					ringIn);
			show_rpc_struct(extra->name, &rpc);
			dump_ring_buffer(extra->name, extra);
		}
		return;
		//BUG();
		//__WARN();
	}

	if (proc) {
		found = 1;
	} else if (__ratelimit(&ring_dump_state)) {
		pr_err("%s:%d can't find process for handling %s programID:%u\n",
				extra->name, __LINE__, extra->name, rpc.programID);
		show_rpc_struct(extra->name, &rpc);
	}

	out += rpc.parameterSize;
	if (out >= dev->ringEnd)
		out = dev->ringStart + (out - dev->ringEnd);

	spin_lock_bh(&extra->lock);
	if (found) {
		update_nextRpc(extra, out);
		update_currProc(extra, proc);
		wake_up_interruptible(&proc->waitQueue);
		pr_debug("%s:%d ###Wakeup### proc:%p(%d) process:%p(%d) and \
				update nextRpc:%x for programID:%u\n",
				extra->name, __LINE__, proc, proc ? proc->pid : 0,
				extra->currProc,
				extra->currProc ? ((RPC_PROCESS *)extra->currProc)->pid : 0,
				extra->nextRpc, rpc.programID);
	} else {
#if 0
		pr_info("%s: clear %s(%p) current process\n",
				__func__, extra->name, dev);
		update_currProc(extra, NULL);
#endif
	}
	spin_unlock_bh(&extra->lock);
}

int rpc_intr_init(void)
{
	static int is_init;
	int result = 0, i;
	is_init = 0;
	int j = 0;

	fw_rpc_ion_client = ion_client_create(rtk_phoenix_ion_device,
						"FW_REMOTE_ALLOC");
	/* Create corresponding structures for each device. */
	rpc_intr_devices = (RPC_DEV *) AVCPU2SCPU(RPC_INTR_RECORD_ADDR);

	for (i = 0; i < RPC_INTR_DEV_TOTAL; i++) {
		pr_debug("rpc_intr_device %d addr: %p\n", i, &rpc_intr_devices[i]);
		rpc_intr_devices[i].ringBuf = RPC_INTR_DEV_ADDR +
				i * RPC_RING_SIZE * 2;

		/* Initialize pointers... */
		rpc_intr_devices[i].ringStart = rpc_intr_devices[i].ringBuf;
		rpc_intr_devices[i].ringEnd = rpc_intr_devices[i].ringBuf
				+ RPC_RING_SIZE;
		rpc_intr_devices[i].ringIn = rpc_intr_devices[i].ringBuf;
		rpc_intr_devices[i].ringOut = rpc_intr_devices[i].ringBuf;

		pr_debug("The %dth intr dev:\n", i);
		pr_debug("RPC ringStart: %p\n",
				AVCPU2SCPU(rpc_intr_devices[i].ringStart));
		pr_debug("RPC ringEnd:   %p\n",
				AVCPU2SCPU(rpc_intr_devices[i].ringEnd));
		pr_debug("RPC ringIn:    %p\n",
				AVCPU2SCPU(rpc_intr_devices[i].ringIn));
		pr_debug("RPC ringOut:   %p\n",
				AVCPU2SCPU(rpc_intr_devices[i].ringOut));

		rpc_intr_extra[i].nextRpc = rpc_intr_devices[i].ringOut;
		rpc_intr_extra[i].currProc = NULL;

		if (!is_init) {
			rpc_intr_devices[i].ptrSync = kmalloc(sizeof(RPC_SYNC_Struct),
					GFP_KERNEL);
			kmemleak_not_leak(rpc_intr_devices[i].ptrSync);

			/* Initialize wait queue... */
			init_waitqueue_head(&(rpc_intr_devices[i].ptrSync->waitQueue));

			/* Initialize sempahores... */
			init_rwsem(&rpc_intr_devices[i].ptrSync->readSem);
			init_rwsem(&rpc_intr_devices[i].ptrSync->writeSem);

			rpc_intr_extra[i].dev = (void *) &rpc_intr_devices[i];
			INIT_LIST_HEAD(&rpc_intr_extra[i].tasks);
			tasklet_init(&rpc_intr_extra[i].tasklet, rpc_dispatch,
					(unsigned long) &rpc_intr_extra[i]);
			spin_lock_init(&rpc_intr_extra[i].lock);
			switch (i) {
			case 0:
				rpc_intr_extra[i].name = "AudioIntrWrite";
				break;
			case 1:
				rpc_intr_extra[i].name = "AudioIntrRead";
				break;
			case 2:
				rpc_intr_extra[i].name = "Video1IntrWrite";
				break;
			case 3:
				rpc_intr_extra[i].name = "Video1IntrRead";
				break;
			case 4:
				rpc_intr_extra[i].name = "Video2IntrWrite";
				break;
			case 5:
				rpc_intr_extra[i].name = "Video2IntrRead";
				break;
			}
		}
	}
	init_waitqueue_head(&r_program_waitQueue);
	r_program_kthread = kthread_run(remote_alloc_thread, (void *)&j, "r_program");
	is_init = 1;
	rpc_intr_is_paused = 0;
	rpc_intr_is_suspend = 0;
	pr_info("\033[31m[RTK_RPC]rpc is not paused & suspended\033[m\n");

//fail:
	return result;
}

int rpc_intr_pause(void)
{
	rpc_intr_is_paused = 1;
	pr_info("\033[31mrpc is paused\033[m\n");
	return 0;
}

int rpc_intr_suspend(void)
{
	rpc_intr_is_suspend = 1;
	pr_info("\033[31mrpc is suspended\033[m\n");
	return 0;
}

int rpc_intr_resume(void)
{
	rpc_intr_is_suspend = 0;
	pr_info("\033[31mrpc is not suspended\033[m\n");
	return 0;
}

void rpc_intr_cleanup(void)
{
	int i;

	/* Clean corresponding structures for each device. */
	if (rpc_intr_devices) {
		/* Clean ring buffers. */
		for (i = 0; i < RPC_INTR_DEV_TOTAL; i++) {
			//if (rpc_intr_devices[i].ringBuf)
				//kfree(rpc_intr_devices[i].ringBuf);
			kfree(rpc_intr_devices[i].ptrSync);
		}
		//kfree(rpc_intr_devices);
	}

	return;
}

int rpc_intr_open(struct inode *inode, struct file *filp)
{
	int minor = MINOR(inode->i_rdev);

	pr_debug("RPC intr open with minor number: %d\n", minor);

	if (!filp->private_data) {
		RPC_PROCESS *proc = kmalloc(sizeof(RPC_PROCESS), GFP_KERNEL);
		if (proc == NULL) {
			pr_err("%s: failed to allocate RPC_PROCESS", __func__);
			return -ENOMEM;
		}

		proc->dev = (RPC_DEV *)&rpc_intr_devices[minor / RPC_NR_PAIR];
		proc->extra = &rpc_intr_extra[minor / RPC_NR_PAIR];
		/* current->tgid = process id, current->pid = thread id */
		proc->pid = current->tgid;
		init_waitqueue_head(&proc->waitQueue);
		INIT_LIST_HEAD(&proc->threads);
#ifdef CONFIG_REALTEK_RPC_PROGRAM_REGISTER
		INIT_LIST_HEAD(&proc->handlers);
#endif
		spin_lock_bh(&proc->extra->lock);
		list_add(&proc->list, &proc->extra->tasks);
		spin_unlock_bh(&proc->extra->lock);
		pr_debug("%s: Current process pid:%d tgid:%d => %d(%p) for %s(%p)\n",
				__func__, current->pid, current->tgid, proc->pid,
				&proc->waitQueue, proc->extra->name, proc->dev);

		filp->private_data = proc;
		filp->f_pos = (loff_t) minor;
	}

	/* Before we maybe sleep */
	//MOD_INC_USE_COUNT;

	return 0; /* success */
}

int rpc_intr_release(struct inode *inode, struct file *filp)
{
#ifdef CONFIG_REALTEK_RPC_PROGRAM_REGISTER
	RPC_HANDLER *handler, *hdltmp;
#endif /* CONFIG_REALTEK_RPC_PROGRAM_REGISTER */
	RPC_THREAD *th, *thtmp;
	int minor = MINOR(inode->i_rdev);

	RPC_PROCESS *proc = filp->private_data;
	RPC_DEV *dev = proc->dev; /* the first listitem */
	RPC_DEV_EXTRA *extra = proc->extra;

	if (extra->currProc == proc) {
		pr_debug("%s: clear %s(%p) current process\n", __func__,
				proc->extra->name, dev);
		update_currProc(extra, NULL);
		 /* intr read device (ugly code)*/
		if (minor == 3 || minor == 7 || minor == 11) {
			if (!rpc_done(extra)) {
				pr_debug("%s: previous rpc hasn't finished, force clear!! ringOut %p => %p\n",
						__func__, AVCPU2SCPU(dev->ringOut),
						AVCPU2SCPU(extra->nextRpc));
				down_write(&dev->ptrSync->readSem);
				dev->ringOut = extra->nextRpc;
				up_write(&dev->ptrSync->readSem);
			}
		}
	}

#ifdef CONFIG_SND_REALTEK
	if (rpc_intr_is_paused)
		pr_err("rpc is paused, no self destroy: %s\n", current->comm);
	else
		RPC_DESTROY_AUDIO_FLOW(current->tgid);
#endif /* CONFIG_SND_REALTEK */

	spin_lock_bh(&extra->lock);

#ifdef CONFIG_REALTEK_RPC_PROGRAM_REGISTER
	/* unregister myself from handler list */
	list_for_each_entry_safe(handler, hdltmp, &proc->handlers, list) {
		list_del(&handler->list);
		kfree(handler);
	}
#endif /* CONFIG_REALTEK_RPC_PROGRAM_REGISTER */

	list_for_each_entry_safe(th, thtmp, &proc->threads, list) {
		list_del(&th->list);
		kfree(th);
	}

	/* remove myself from task list*/
	list_del(&proc->list);
	kfree(proc);

	spin_unlock_bh(&extra->lock);

	pr_debug("RPC intr close with minor number: %d\n", minor);

	//MOD_DEC_USE_COUNT;

	return 0;
}

/*
 * We don't need parameter f_pos here...
 * note:rpc_intr_read support both blocking & nonblocking modes
 */
ssize_t rpc_intr_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	RPC_PROCESS *proc = filp->private_data;
	RPC_DEV *dev = proc->dev; /* the first listitem */
	RPC_DEV_EXTRA *extra = proc->extra;
	int temp, size;
	size_t r;
	ssize_t ret = 0;
	uint32_t ptmp;
	int rpc_ring_size = dev->ringEnd - dev->ringStart;
	long k;

	//pr_debug("%s:%d thread:%s pid:%d tgid:%d device:%s\n",
	//__func__, __LINE__, current->comm, current->pid, current->tgid,
	//extra->name);
	if (rpc_intr_is_paused) {
		pr_err("RPCintr: someone access rpc intr during the pause...\n");
		pr_err("%s:%d buf:%p count:%lu EAGAIN\n", extra->name, __LINE__, buf,
				count);
		msleep(1000);
		return -EAGAIN;
	}

	if (need_dispatch(extra))
		tasklet_schedule(&(extra->tasklet));
	//pr_debug("%s: dev:%p currProc:%p\n",
		//extra->name, dev, extra->currProc);
	if ((extra->currProc != proc) || (ring_empty(dev))) {
		if (filp->f_flags & O_NONBLOCK)
			goto done;

wait_again:

		k = wait_event_interruptible_timeout(proc->waitQueue,
			(extra->currProc == proc) && (!ring_empty(dev)),
			timeout);
		if (k == 0)
			goto done; /* timeout */

		//if (current->flags & PF_FREEZE) {
		//refrigerator(PF_FREEZE);
		//if (!signal_pending(current))
			//goto wait_again;
		//}

		if (try_to_freeze()) {
			if (!signal_pending(current))
				goto wait_again;
		}

		if (signal_pending(current)) {
			pr_debug("RPC deblock because of receiving a signal...\n");
			goto done;
		}
	}

	down_write(&dev->ptrSync->readSem);

	if (dev->ringIn > dev->ringOut)
		size = dev->ringIn - dev->ringOut;
	else
		size = rpc_ring_size + dev->ringIn - dev->ringOut;

	pr_debug("%s:%d ==going read== count:%zu avail:%d "
			"ringOut:%x ringIn:%x nextRPC:%x",
			extra->name, __LINE__, count, size, dev->ringOut, dev->ringIn,
			extra->nextRpc);
	peek_rpc_struct(__func__, dev);

	if (count > size)
		count = size;


	temp = dev->ringEnd - dev->ringOut;
	rtk_rpc_wmb(AVCPU2SCPU(dev->ringStart), PAGE_ALIGN(rpc_ring_size));

	if (temp >= count) {
#ifdef MY_COPY
		r = my_copy_to_user((int *)buf,
				(int *)AVCPU2SCPU(dev->ringOut), count);
#else
		r = copy_to_user((int *)buf, (int *)AVCPU2SCPU(dev->ringOut), count);
#endif /* MY_COPY */
		if (r) {
			pr_err("%s:%d buf:%p count:%lu EFAULT\n",
				extra->name, __LINE__, buf, count);
			ret = -EFAULT;
			goto out;
		}

		ret = count;
		ptmp = dev->ringOut + ((count+3) & 0xfffffffc);
		if (ptmp == dev->ringEnd)
			dev->ringOut = dev->ringStart;
		else
			dev->ringOut = ptmp;

		//pr_debug("RPC Read is in 1st kind...\n");
	} else {
#ifdef MY_COPY
		r = my_copy_to_user((int *)buf,
				(int *)AVCPU2SCPU(dev->ringOut), temp);
#else
		r = copy_to_user((int *)buf,
				(int *)AVCPU2SCPU(dev->ringOut), temp);
#endif /* MY_COPY */

		if (r) {
			pr_err("%s:%d buf:%p count:%lu EFAULT\n",
					extra->name, __LINE__, buf, count);
			ret = -EFAULT;
			goto out;
		}

		count -= temp;

#ifdef MY_COPY
		r = my_copy_to_user((int *)(buf+temp),
				(int *)AVCPU2SCPU(dev->ringStart), count);
#else
		r = copy_to_user((int *)(buf+temp),
				(int *)AVCPU2SCPU(dev->ringStart), count);
#endif /* MY_COPY */

		if (r) {
			pr_err("%s:%d buf:%p count:%lu EFAULT\n",
					extra->name, __LINE__, buf, count);
			ret = -EFAULT;
			goto out;
		}
		ret = (temp + count);
		dev->ringOut = dev->ringStart+((count+3) & 0xfffffffc);

		//pr_debug("RPC Read is in 2nd kind...\n");
	}

	/*
	 * NOTE: we do not need spin lock here because we are protected by
	 * semaphore already
	 */
	spin_lock_bh(&extra->lock);
	if (rpc_done(extra) && extra->currProc == proc) {
		pr_debug("%s: Previous RPC is done, unregister myself\n", extra->name);
		update_currProc(extra, NULL);
	}
	spin_unlock_bh(&extra->lock);

	/* process next rpc command if any */
	if (need_dispatch(extra))
		tasklet_schedule(&(extra->tasklet));

#if 0
	if (count == sizeof(RPC_STRUCT) && access_ok(VERIFY_WRITE, buf, sizeof(RPC_STRUCT))) {
		RPC_STRUCT *rpc = (RPC_STRUCT *)buf;
		uint32_t programID = ntohl(rpc->programID);

		if (programID == R_PROGRAM) {
			rpc->versionID = htonl(0);
		} else if (programID == REPLYID) {
			rpc->versionID = htonl(REPLYID);
		} else if (programID == AUDIO_AGENT) {
			rpc->versionID = htonl(0);
		} else {
			pr_warn("%s: invalid programID:%u\n", __func__, programID);
		}
	}
#endif

	pr_debug("%s:%d pid:%d tgid:%d count:%lu actual:%ld ringOut:%x "
			"ringIn:%x nextRpc:%x currProc:%p(%d)\n",
			extra->name, __LINE__, current->pid, current->tgid, count, ret,
			dev->ringOut, dev->ringIn, extra->nextRpc, extra->currProc,
			extra->currProc ? ((RPC_PROCESS *)extra->currProc)->pid : 0);
out:
		up_write(&dev->ptrSync->readSem);
done:
		//pr_debug("RPC intr ringOut pointer is : 0x%8x\n",
		//		(int)AVCPU2SCPU(dev->ringOut));
		//pr_debug("%s:%d pid:%d reads %d bytes\n",
		//		extra->name, __LINE__, current->pid, ret);
		return ret;
}

/*
 * We don't need parameter f_pos here...
 * note: rpc_intr_write only support nonblocking mode
 */
ssize_t rpc_intr_write(struct file *filp, const char *buf, size_t count,
		loff_t *f_pos)
{
	RPC_PROCESS *proc = filp->private_data;
	RPC_DEV *dev = proc->dev; /* the first listitem */
	RPC_DEV_EXTRA *extra = proc->extra;
	RPC_DEV_EXTRA *rextra = extra + 1;
	int temp, size;
	size_t r;
	ssize_t ret = 0;
	uint32_t ptmp;
	int rpc_ring_size = dev->ringEnd - dev->ringStart;

	//pr_debug("%s:%d buf:%p count:%u\n", __func__, __LINE__, buf, count);

	if (rpc_intr_is_paused) {
		pr_err("RPCintr: someone access rpc intr during the pause...\n");
		pr_err("%s:%d buf:%p count:%lu EAGAIN\n", __func__, __LINE__, buf,
				count);
		msleep(1000);
		return -EAGAIN;
	}

	down_write(&dev->ptrSync->writeSem);

#if 1
	/*
	 * Threads that share the same file descriptor should have the same tgid
	 * However, with uClibc pthread library, pthread_create() creates threads
	 * with pid == tgid So the tgid is not real tgid, we have to maintain the
	 * thread list that we can lookup later
	 */
	if (current->pid != proc->pid)
		update_thread_list(rextra, proc->pid);
#endif

	if (ring_empty(dev))
		size = 0; /* the ring is empty */
	else if (dev->ringIn > dev->ringOut)
		size = dev->ringIn - dev->ringOut;
	else
		size = rpc_ring_size + dev->ringIn - dev->ringOut;

	//pr_debug("%s: count:%d space:%d\n",
	//		extra->name, count, rpc_ring_size - size - 1);
	//pr_debug("%s: pid:%d tgid:%d\n",
	//		extra->name, current->pid, current->tgid);

	if (count > (rpc_ring_size - size - 1))
		goto out;

#if 0
	if (access_ok(VERIFY_READ, buf, sizeof(RPC_STRUCT))) {
		RPC_STRUCT *rpc = (RPC_STRUCT *)buf;
		uint32_t programID = ntohl(rpc->programID);

		if (programID == AUDIO_SYSTEM || programID == REPLYID || programID == 97) {
			rpc->versionID = htonl(readl(rpc_refclk_base));
		} else {
			pr_warn("%s: invalid programID:%u\n", __func__, programID);
		}
	}
#endif

	temp = dev->ringEnd - dev->ringIn;

	if (temp >= count) {
#ifdef MY_COPY
		r = my_copy_from_user((int *)AVCPU2SCPU(dev->ringIn), (int *)buf, count);
#else
		r = copy_from_user((int *)AVCPU2SCPU(dev->ringIn), (int *)buf, count);
#endif /* MY_COPY */

		if (r) {
			pr_err("%s:%d buf:%p count:%lu EFAULT\n",
					__func__, __LINE__, buf, count);
			ret = -EFAULT;
			goto out;
		}

		ret += count;
		ptmp = dev->ringIn + ((count+3) & 0xfffffffc);

		//asm("DSB");
		mb();

		if (ptmp == dev->ringEnd)
			dev->ringIn = dev->ringStart;
		else
			dev->ringIn = ptmp;

		//pr_debug("RPC Write is in 1st kind...\n");
	} else {
#ifdef MY_COPY
			r = my_copy_from_user((int *)AVCPU2SCPU(dev->ringIn), (int *)buf, temp);
#else
			r = copy_from_user((int *)AVCPU2SCPU(dev->ringIn), (int *)buf, temp);
#endif /* MY_COPY */
			if (r) {
				pr_err("%s:%d buf:%p count:%lu EFAULT\n",
				__func__, __LINE__, buf, count);
				ret = -EFAULT;
				goto out;
			}
			count -= temp;

#ifdef MY_COPY
			r = my_copy_from_user((int *)AVCPU2SCPU(dev->ringStart), (int *)(buf+temp), count);
#else
			r = copy_from_user((int *)AVCPU2SCPU(dev->ringStart), (int *)(buf+temp), count);
#endif /* MY_COPY */
			if (r) {
				pr_err("%s:%d buf:%p count:%lu EFAULT\n",
						__func__, __LINE__, buf, count);
				ret = -EFAULT;
				goto out;
			}
			ret += (temp + count);

			//asm("DSB");
			mb();

			dev->ringIn = dev->ringStart+((count+3) & 0xfffffffc);
			//pr_debug("RPC Write is in 2nd kind...\n");
	}

	peek_rpc_struct(__func__, dev);
	rtk_rpc_wmb(AVCPU2SCPU(dev->ringStart),
			PAGE_ALIGN(rpc_ring_size));

	/* notify all the processes in the wait queue */
	//wake_up_interruptible(&dev->waitQueue);

	/* use the "f_pos" of file object to store the device number */
	temp = (int) *f_pos;
		//if (temp == 1)
	if (temp == 1 || temp == 5) {
#if 1
		rpc_send_interrupt();
#else
		/* audio */
		writel((RPC_INT_SA | RPC_INT_WRITE_1), rpc_int_base+RPC_SB2_INT);
#endif
	//rtd_outl(REG_SB2_CPU_INT, (RPC_INT_SA | RPC_INT_WRITE_1));
	} else {
		pr_err("error device number...");
	}

	pr_debug("%s:%d thread:%s pid:%d tgid:%d device:%s\n",
			__func__, __LINE__, current->comm, current->pid,
			current->tgid, extra->name);
	pr_debug("%s:%d buf:%p count:%lu actual:%ld\n",
			__func__, __LINE__, buf, count, ret);
out:
		//pr_debug("RPC intr ringIn pointer is : 0x%8x\n",
		//		(int)AVCPU2SCPU(dev->ringIn));
	up_write(&dev->ptrSync->writeSem);
	return ret;
}

long rpc_intr_ioctl(struct file *filp, unsigned int cmd,
			unsigned long arg)
{
		int ret = 0;

		while (rpc_intr_is_suspend) {
			pr_warn("RPCintr: someone access rpc poll during the suspend!!!...\n");
			msleep(1000);
		}

		switch (cmd) {
		case RPC_IOCTTIMEOUT:
			timeout = arg;
			break;
		case RPC_IOCQTIMEOUT:
			return timeout;
#ifdef CONFIG_REALTEK_RPC_PROGRAM_REGISTER
		case RPC_IOCTHANDLER: {
			int found;
			RPC_PROCESS *proc = filp->private_data;
			RPC_DEV_EXTRA *extra = proc->extra;
			RPC_HANDLER *handler;

			pr_debug("%s:%d : Register handler for programID:%lu\n",
					__func__, __LINE__, arg);
			found = 0;
			list_for_each_entry(handler, &proc->handlers, list) {
				if (handler->programID == arg) {
					found = 1;
					break;
				}
			}

			if (found)
				break;

			/* not found, add to handler list */
			handler = kmalloc(sizeof(RPC_HANDLER), GFP_KERNEL);
			if (handler == NULL) {
				pr_err("%s: failed to allocate RPC_HANDLER", __func__);
				return -ENOMEM;
			}
			handler->programID = arg;
			spin_lock_bh(&extra->lock);
			list_add(&handler->list, &proc->handlers);
			spin_unlock_bh(&extra->lock);
			pr_debug("%s:%d %s: Add handler pid:%d for programID:%lu\n",
					__func__, __LINE__, proc->extra->name, proc->pid, arg);
			break;
		}
#endif /* CONFIG_REALTEK_RPC_PROGRAM_REGISTER */
		default: /* redundant, as cmd was checked against MAXNR */
			pr_err("%s:%d unsupported ioctl cmd:%x arg:%lx", __func__,
					__LINE__, cmd, arg);
			return -ENOTTY;
		}

		return ret;
}

struct file_operations rpc_intr_fops = {
	//.llseek = scull_llseek,
	.unlocked_ioctl = rpc_intr_ioctl,
	.compat_ioctl = rpc_intr_ioctl,
	.read = rpc_intr_read,
	.write = rpc_intr_write,
	.open = rpc_intr_open,
	.release = rpc_intr_release,
};
