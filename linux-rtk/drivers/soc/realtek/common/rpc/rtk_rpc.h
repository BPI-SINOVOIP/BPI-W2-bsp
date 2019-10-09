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

#ifndef _RTK_RPC_H
#define _RTK_RPC_H
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <asm/current.h>
#include <asm/barrier.h>
#include <asm/cacheflush.h>
#ifdef CONFIG_DEVFS_FS
#include <linux/devfs_fs_kernel.h>
#endif
#include "soc/realtek/memory.h"

#define MY_COPY

extern const char *rpc_name;

#define RPC_SB2_INT 0x0
#define RPC_SB2_INT_EN 0x4
#define RPC_INT_WRITE_1 1
#define RPC_INT_AS (1 << 3)
#define RPC_INT_SA (1 << 1)

#if 0
#define __read_32bit_caller_register() \
{ int __res; \
__asm__ __volatile__( \
"mov\t%0, lr\n\t" \
: "=r" (__res)); \
__res; \
}
#endif

#define CONFIG_REALTEK_RPC_PROGRAM_REGISTER
#define RPC_SUPPORT_MULTI_CALLER_SEND_TID_PID

//#define CONFIG_REALTEK_AVCPU

#define R_PROGRAM 98
#define AUDIO_SYSTEM 201
#define AUDIO_AGENT 202
#define VIDEO_AGENT 300

#define KERNELID 98
#define REPLYID 99
#define RPC_AUDIO 0x0
#define RPC_VIDEO 0x1
#define RPC_VIDEO2 0x2
#define RPC_KCPU 0x3
#define RPC_OK 0
#define RPC_FAIL -1

#ifndef RPC_ID
#define RPC_ID 0x5566
#endif

#ifndef RPC_MAJOR
#define RPC_MAJOR 240 /* dynamic major by default */
#endif

#ifndef RPC_NR_DEVS
/*
 * 2 for S-A,
 * 2 for A-S,
 * 2 for S-V1,
 * 2 for V1-S,
 * 2 for S-V2,
 * 2 for V2-S
 */
typedef enum {
	RPC_POLL_DEV_SA_ID0, /* poll audio write */
	RPC_POLL_DEV_AS_ID1, /*poll audio read */
	RPC_POLL_DEV_SV1_ID2, /*poll video write */
	RPC_POLL_DEV_V1S_ID3, /*poll video read */
//	RPC_POLL_DEV_SV2_ID4,
//	RPC_POLL_DEV_V2S_ID5,
	RPC_POLL_DEV_TOTAL
} NUM_POLL_DEV;

typedef enum {
	RPC_INTR_DEV_SA_ID0, /* intr audio write */
	RPC_INTR_DEV_AS_ID1, /*intr audio read */
	RPC_INTR_DEV_SV1_ID2, /* intr video write */
	RPC_INTR_DEV_V1S_ID3, /* intr video read */
//	RPC_INTR_DEV_SV2_ID4,
//	RPC_INTR_DEV_V2S_ID5,
	RPC_INTR_DEV_TOTAL
} NUM_INTR_DEV;

/* total ring buffer number */
#define RPC_NR_DEVS (RPC_POLL_DEV_TOTAL + RPC_INTR_DEV_TOTAL)
#endif /* RPC_NR_DEVS */

#ifndef RPC_NR_PAIR
#define RPC_NR_PAIR 2 /* for interrupt and polling mode */
#endif /* RPC_NR_PAIR */

#ifndef RPC_NR_KERN_DEVS
/*
 * S-A,
 * A-S,
 * S-V1,
 * V1-S,
 * S-V2,
 * V2-S
 */
typedef enum {
	RPC_KERN_DEV_SA_ID0, /* kern audio write */
	RPC_KERN_DEV_AS_ID1, /* kern audio read */
	RPC_KERN_DEV_SV1_ID2, /* kern video write */
	RPC_KERN_DEV_V1S_ID3, /* kern video read */
	//  RPC_KERN_DEV_SV2_ID4,
	//  RPC_KERN_DEV_V2S_ID5,
	RPC_NR_KERN_DEVS	/* total ring buffer number */
} NUM_KERN_DEV;

//#define RPC_NR_KERN_DEVS 6	/* total ring buffer number */
#endif /* RPC_NR_KERN_DEVS */

//extern void __iomem *rpc_rbussync_base;
extern volatile void __iomem *rpc_ringbuf_base;

#if 0
#define rtk_rpc_wmb(start, size) \
do { \
smp_mb(); \
__flush_dcache_area(start, size); \
writel(0x1234, rpc_rbussync_base); \
smp_mb(); \
} while (0)
#endif

#define rtk_rpc_wmb(start, size) wmb()

#ifdef CONFIG_ARCH_RTD129x
#define AVCPU_NOCACHE 0xa0000000
#else
#define AVCPU_NOCACHE 0x0
#endif

#if 0
#define AVCPU_SCPU_OFFSET (AVCPU_NOCACHE + RPC_RINGBUF_PHYS - \
		(unsigned long)RPC_RINGBUF_VIRT)
#endif

#define AVCPU_SCPU_OFFSET (AVCPU_NOCACHE + RPC_RINGBUF_PHYS \
- (unsigned long)rpc_ringbuf_base)
#define AVCPU2SCPU(x) ((char *)(x - AVCPU_SCPU_OFFSET))
#define SCPU2AVCPU(x) ((unsigned long)x + AVCPU_SCPU_OFFSET)
#define RPCREAD32(addr) AVCPU2SCPU(addr)
#define RPCWRITE32(addr, val) \
do { \
AVCPU2SCPU(addr) = val; \
} while (0)

#ifndef RPC_RING_SIZE
#define RPC_RING_SIZE 512	/* size of ring buffer */
#endif	/* RPC_RING_SIZE */

#ifndef RPC_POLL_DEV_ADDR
#define RPC_POLL_DEV_ADDR (AVCPU_NOCACHE + 0x01ffe000)
#endif	/* RPC_POLL_DEV_ADDR */

#ifndef RPC_INTR_DEV_ADDR
#define RPC_INTR_DEV_ADDR (RPC_POLL_DEV_ADDR+RPC_RING_SIZE)
#endif	/* RPC_INTR_DEV_ADDR */

#ifndef RPC_KERN_DEV_ADDR
#define RPC_KERN_DEV_ADDR (AVCPU_NOCACHE + 0x01fff200)
#endif	/* RPC_KERN_DEV_ADDR */

#ifndef RPC_RECORD_SIZE
#define RPC_RECORD_SIZE 64	/* size of ring buffer record */
#endif	/* RPC_RECORD_SIZE */

#ifndef RPC_POLL_RECORD_ADDR
#define RPC_POLL_RECORD_ADDR (AVCPU_NOCACHE + 0x01fff000)
#endif	/* RPC_POLL_RECORD_ADDR */

#ifndef RPC_INTR_RECORD_ADDR
#define RPC_INTR_RECORD_ADDR (RPC_POLL_RECORD_ADDR+RPC_RECORD_SIZE \
*(RPC_NR_DEVS/RPC_NR_PAIR))
#endif	/* RPC_INTR_RECORD_ADDR */

#ifndef RPC_KERN_RECORD_ADDR
#define RPC_KERN_RECORD_ADDR (AVCPU_NOCACHE + 0x01fffa00)
#endif	/* RPC_KERN_RECORD_ADDR */

extern struct file_operations rpc_poll_fops;	/* for poll mode */
extern struct file_operations rpc_intr_fops;	/* for intr mode */
extern struct file_operations rpc_ctrl_fops;	/* for ctrl mode */

extern struct file_operations *rpc_fop_array[];

/*
 *struct RPC_STRUCT
 *@uint32_t programID: program ID defined in IDL file
 *@uint32_t versionID: version ID defined in IDL file
 *@uint32_t procedureID: function ID defined in IDL file
 *@uint32_t taskID: the caller's task ID, assign 0 if NONBLOCK_MODE
 *@uint32_t sysTID: N/A
 *@uint32_t sysPID: the callee's task ID
 *@uint32_t parameterSize: packet's body size
 *@uint32_t mycontext: return address of reply value
 */
typedef struct RPC_STRUCT {
	uint32_t programID;
	uint32_t versionID;
	uint32_t procedureID;
	uint32_t taskID;
#ifdef RPC_SUPPORT_MULTI_CALLER_SEND_TID_PID
	uint32_t sysTID;
#endif	/* RPC_SUPPORT_MULTI_CALLER_SEND_TID_PID */
	uint32_t sysPID;
	uint32_t parameterSize;
	uint32_t mycontext;
} RPC_STRUCT;

/*
 *struct RPC_SYNC_Struct
 *@wait_queue_head_t waitQueue: for blocking read
 */
typedef struct RPC_SYNC_Struct {
	wait_queue_head_t waitQueue;
	struct rw_semaphore readSem;
	struct rw_semaphore writeSem;
} RPC_SYNC_Struct;

/*
 *struct RPC_DEV
 *@uint32_t ringBuf: buffer for interrupt mode
 *@uint32_t ringStart: pointer to start of ring buffer
 *@uint32_t ringEnd: pointer to end of ring buffer
 *@volatile uint32_t ringIn: pointer to where next data will be inserted in
 *the ring buffer
 *@volatile uint32_t ringOut: pointer to where next data will
 *be extracted from the ring buffer
 */
typedef struct RPC_DEV { /*size should be 64 bytes*/
	uint32_t ringBuf;
	uint32_t ringStart;
	uint32_t ringEnd;
	volatile uint32_t ringIn;
	volatile uint32_t ringOut;
	/* scpu internal use */
	uint32_t reserved1;
	RPC_SYNC_Struct *ptrSync;
	uint32_t reserved2[8];

#if defined(CONFIG_ARCH_MULTI_V7)
	uint32_t reserved3;
#endif

} RPC_DEV;

/*
 *struct RPC_DEV_EXTRA
 *@volatile void *currProc: current process which handles rpc command
 *@char *name: the rpc device name
 *@struct list_head tasks: tasks that open this rpc device
 *@struct tasklet_struct tasklet: schedule a tasklet for bottom half
 *@volatile uint32_t nextRpc: points to next Rpc
 *@spinlock_t lock: lock to protect data synchronization
 *@struct device *sdev: struct device
 */
typedef struct RPC_DEV_EXTRA {
	RPC_DEV	 *dev;
	volatile void *currProc;
	char *name;
	struct list_head tasks;
	struct tasklet_struct tasklet;
	volatile uint32_t nextRpc;
	spinlock_t lock;
	struct device *sdev;
} RPC_DEV_EXTRA;

/*
 * struct RPC_THREAD
 * maintain a list of threads in the same process
 */
typedef struct RPC_THREAD {
	pid_t pid;
	struct list_head list;
} RPC_THREAD;

/*
 * struct RPC_PROCESS
 * @struct list_head threads: pids that share the same file descriptor
 *
 * maintain a list of processes that use the same RPC device
 */
typedef struct RPC_PROCESS {
	pid_t pid;
	wait_queue_head_t waitQueue;
	RPC_DEV	 *dev;
	RPC_DEV_EXTRA *extra;
#ifdef CONFIG_REALTEK_RPC_PROGRAM_REGISTER
	struct list_head handlers;
#endif	/* CONFIG_REALTEK_RPC_PROGRAM_REGISTER */
	struct list_head threads;
	struct list_head list;
} RPC_PROCESS;

#ifdef CONFIG_REALTEK_RPC_PROGRAM_REGISTER
/*
 * struct RPC_HANDLER
 * maintain a list of handlers
 */
typedef struct RPC_HANDLER {
	uint32_t programID;
	struct list_head list;
} RPC_HANDLER;
#endif	/* CONFIG_REALTEK_RPC_PROGRAM_REGISTER */

/*
 * struct RPC_DBG_FLAG
 * @uint32_t op: 0:get, 1:set
 */
typedef struct RPC_DBG_FLAG {
	uint32_t op;
	uint32_t flagValue;
	uint32_t flagAddr;
} RPC_DBG_FLAG;

extern int pid_max;
extern RPC_DEV_EXTRA rpc_intr_extra[RPC_NR_DEVS/RPC_NR_PAIR];
extern RPC_DEV_EXTRA rpc_poll_extra[RPC_NR_DEVS/RPC_NR_PAIR];
void rpc_dispatch(unsigned long data);

#ifdef MY_COPY
//FIXME: accepts SCPU addr
static inline int my_memcpy(int *des, int *src, int size)
{

#if defined(CONFIG_ARCH_MULTI_V7)
	_memcpy_fromio(des, src, size);
	return 0;
#else
	__memcpy_fromio(des, src, size);
	return 0;
#endif

}
#endif

//FIXME: must use the same type of addr (AVCPU addr or SCPU addr)
static inline int __get_ring_data_size(uint32_t start, uint32_t end,
		uint32_t in, uint32_t out)
{
	int32_t ringsize = end - start;
	int32_t datasize = (ringsize + in - out) % ringsize;

	pr_debug("%s ringsize:%d datasize:%d start:%x end:%x in:%x out:%x\n",
			__func__, ringsize, datasize, start, end, in, out);
	return datasize;
}

static inline int get_ring_data_size(RPC_DEV *dev)
{
	return __get_ring_data_size(dev->ringStart, dev->ringEnd,
			dev->ringIn, dev->ringOut);
}

/*
 * get ring data in buf and return next data pointer
 */
//FIXME: out is AVCPU addr
static inline uint32_t get_ring_data(const char *func, RPC_DEV *dev,
		uint32_t out, char *buf, int datasize)
{
	int size = __get_ring_data_size(dev->ringStart, dev->ringEnd,
			dev->ringIn, out);
	int tail = dev->ringEnd - out;

	if (size < datasize) {
		pr_debug("%s: Size not enough %d < %d\n", func, size, datasize);
		return 0;
	}

	if (tail >= datasize) {
#ifdef MY_COPY
		my_memcpy((int *)buf, (int *)AVCPU2SCPU(out), datasize);
#else
		memcpy(buf, AVCPU2SCPU(out), datasize);
#endif
		out += datasize;
	} else {
#ifdef MY_COPY
		my_memcpy((int *)buf, (int *)AVCPU2SCPU(out), tail);
		my_memcpy((int *)(buf + tail), (int *)AVCPU2SCPU(dev->ringStart),
				datasize - tail);
#else
		memcpy(buf, AVCPU2SCPU(out), tail);
		memcpy(buf + tail, AVCPU2SCPU(dev->ringStart), datasize - tail);
#endif
		out = dev->ringStart + datasize - tail;
	}

	return out;
}

static inline void dump_ring_buffer(const char *func, RPC_DEV_EXTRA *extra)
{
	int i;
	RPC_DEV *dev = extra->dev;

	char *bufaddr = AVCPU2SCPU(dev->ringStart);
	pr_err("==*== %s Start:%p Out:%p next:%p In:%p End:%p size:%d %s ==*==\n",
			func, AVCPU2SCPU(dev->ringStart),
			AVCPU2SCPU(dev->ringOut),
			AVCPU2SCPU(extra->nextRpc),
			AVCPU2SCPU(dev->ringIn),
			AVCPU2SCPU(dev->ringEnd),
			get_ring_data_size(dev),
			in_atomic() ? "atomic" : "");
	for (i = 0; i < RPC_RING_SIZE ; i += 16) {
		uint32_t *addr = (uint32_t *)(bufaddr + i);
		pr_err("%p: %08x %08x %08x %08x\n",
				addr, ntohl(*(addr + 0)),
				ntohl(*(addr + 1)),
				ntohl(*(addr + 2)),
				ntohl(*(addr + 3)));
	}
}

static inline void convert_rpc_struct(const char *func, RPC_STRUCT *rpc)
{
	rpc->programID = ntohl(rpc->programID);
	rpc->versionID = ntohl(rpc->versionID);
	rpc->procedureID = ntohl(rpc->procedureID);
	rpc->taskID = ntohl(rpc->taskID);
#ifdef RPC_SUPPORT_MULTI_CALLER_SEND_TID_PID
	rpc->sysTID = ntohl(rpc->sysTID);
#endif	/* RPC_SUPPORT_MULTI_CALLER_SEND_TID_PID */
	rpc->sysPID = ntohl(rpc->sysPID);
	rpc->parameterSize = ntohl(rpc->parameterSize);
	rpc->mycontext = ntohl(rpc->mycontext);
}

extern volatile void __iomem *rpc_refclk_base;
static inline void show_rpc_struct(const char *func, RPC_STRUCT *rpc)
{
#ifdef RPC_SUPPORT_MULTI_CALLER_SEND_TID_PID
	pr_debug("%s: program:%u version:%u procedure:%u taskID:%u sysTID:%u sysPID:%u size:%u context:%x 90k:%u %s\n",
		func, rpc->programID, rpc->versionID, rpc->procedureID, rpc->taskID, rpc->sysTID, rpc->sysPID,
		rpc->parameterSize, rpc->mycontext, readl(rpc_refclk_base), in_atomic() ? "atomic" : "");
#else
	pr_debug("%s: program:%u version:%u procedure:%u taskID:%u sysPID:%u size:%u context:%x 90k:u %s\n",
			func, rpc->programID, rpc->versionID, rpc->procedureID, rpc->taskID, rpc->sysPID, rpc->parameterSize,
			rpc->mycontext, readl(rpc_refclk_base), in_atomic() ? "atomic" : "");
#endif	/* RPC_SUPPORT_MULTI_CALLER_SEND_TID_PID */
}

static inline void peek_rpc_struct(const char *func, RPC_DEV *dev)
{
	RPC_STRUCT rpc;
	uint32_t pid;
	uint32_t arg;
	uint32_t out = dev->ringOut;

	out = get_ring_data(func, dev, out, (char *)&rpc, sizeof(RPC_STRUCT));
	if (out == 0)
		return;
	convert_rpc_struct(func, &rpc);
	show_rpc_struct(func, &rpc);

	if (rpc.programID == AUDIO_AGENT && rpc.versionID == 0) {
		//Parse more information here
	} else if (rpc.programID == VIDEO_AGENT && rpc.versionID == 0) {
		//Parse more information here
	} else if (rpc.programID == R_PROGRAM && rpc.versionID == 0) {
		out = get_ring_data(func, dev, out, (char *)&arg, sizeof(uint32_t));
		if (out == 0)
			return;
		arg = ntohl(arg);
		if (rpc.procedureID == 1)
			pr_debug("%s: alloc %u bytes\n", func, arg);
		else
			pr_debug("%s: free addr %x\n", func, arg);
	} else if (rpc.programID == REPLYID && rpc.versionID == REPLYID) {
		out = get_ring_data(func, dev, out, (char *)&pid, sizeof(uint32_t));
		if (out == 0)
			return;
		pid = ntohl(pid);
		pr_debug("%s: reply to taskid:%u\n", func, pid);
	}
}

#if 0
static inline void update_currProc(RPC_DEV_EXTRA *extra, RPC_PROCESS *proc)
{
	extra->currProc = proc;
}

//FIXME: accept AVCPU addr
static inline void update_nextRpc(RPC_DEV_EXTRA *extra, char *nextRpc)
{
	extra->nextRpc = nextRpc;
}

static inline int rpc_done(RPC_DEV_EXTRA *extra)
{
	RPC_DEV *dev = extra->dev;

	return dev->ringOut == extra->nextRpc;
}

static inline int ring_empty(RPC_DEV *dev)
{
	return dev->ringOut == dev->ringIn;
}

static inline int need_dispatch(RPC_DEV_EXTRA *extra)
{
	//size is not zero and previous rpc is done
	return extra->currProc == NULL && !ring_empty(extra->dev) && rpc_done(extra);
}
#else
#define update_currProc(extra, proc) \
do { \
extra->currProc = proc; \
} while (0)

#define update_nextRpc(extra, next) \
do { \
extra->nextRpc = next; \
} while (0)

#define rpc_done(extra) (extra->dev->ringOut == extra->nextRpc)

#define ring_empty(dev) (dev->ringOut == dev->ringIn)

#define need_dispatch(extra) (extra->currProc == NULL && !ring_empty(extra->dev) && rpc_done(extra))
#endif

static inline RPC_PROCESS *pick_one_proc(RPC_DEV_EXTRA *extra)
{
	RPC_PROCESS *proc = NULL;

	spin_lock_bh(&extra->lock);
	if (!list_empty(&extra->tasks)) {
		proc = list_first_entry(&extra->tasks, RPC_PROCESS, list);
		pr_debug("%s:%d Pick process:%d\n", extra->name, __LINE__, proc->pid);
	} else {
		pr_debug("%s:%d No available process\n", extra->name, __LINE__);
	}
	spin_unlock_bh(&extra->lock);
	return proc;
}

#ifdef CONFIG_REALTEK_RPC_PROGRAM_REGISTER
static inline RPC_PROCESS *pick_supported_proc(RPC_DEV_EXTRA *extra,
		uint32_t programID)
{
	RPC_PROCESS *proc;
	RPC_HANDLER *handler;

	spin_lock_bh(&extra->lock);
	list_for_each_entry(proc, &extra->tasks, list) {
		list_for_each_entry(handler, &proc->handlers, list) {
			if (handler->programID == programID) {
				spin_unlock_bh(&extra->lock);
				pr_debug("%s:%d pid:%d supports programID:%u\n", __func__,
						__LINE__, proc->pid, programID);
				return proc;
			}
		}
	}
	spin_unlock_bh(&extra->lock);
	pr_debug("%s:%d can't find any process supports programID:%u\n", __func__,
			__LINE__, programID);
	return NULL;
}
#endif	/* CONFIG_REALTEK_RPC_PROGRAM_REGISTER */

static inline RPC_PROCESS *lookup_by_taskID(RPC_DEV_EXTRA *extra,
		uint32_t taskID)
{
	pid_t pid;
	RPC_PROCESS *proc = NULL;
	struct task_struct *task;

	/* sanity check */
	if (unlikely(taskID >= pid_max)) {
		pr_err("%s:%d invalid taskID:%u >= pid_max:%d\n", extra->name,
				__LINE__, taskID, pid_max);
		return NULL;
	}

	task = find_task_by_pid_ns(taskID, &init_pid_ns);
	if (task == NULL) {
		__WARN_printf("%s:%d can't find_task_by_pid_ns! taskID:%u, thread may be dead\n",
				extra->name, __LINE__, taskID);

		//BUG();

		/*
		 * taskID may be dead, use it directly, risky!!
		 * the same taskID may exist in more than one thread list
		 */
		pid = taskID;
	} else {
		pid = task->tgid;
		pr_debug("%s:%d find_task_by_pid_ns taskID:%u => pid:%d tgid:%d comm:%s\n",
				extra->name, __LINE__, taskID, task->pid, task->tgid, task->comm);
	}

	spin_lock_bh(&extra->lock);
	list_for_each_entry(proc, &extra->tasks, list) {
		pr_debug("%s:%d proc->pid:%d target-pid:%d\n",
				extra->name, __LINE__, proc->pid, pid);

		if (proc->pid == pid) {
			spin_unlock_bh(&extra->lock);
			pr_debug("%s:%d found process:%d\n", extra->name, __LINE__, pid);
			return proc;
		} else {
			RPC_THREAD *thread;

			list_for_each_entry(thread, &proc->threads, list) {
				if (thread->pid == pid) {
					spin_unlock_bh(&extra->lock);
					pr_debug("%s:%d found thread:%d in process:%d\n",
							extra->name, __LINE__, pid, proc->pid);
					return proc;
				}
			}
		}
	}
	spin_unlock_bh(&extra->lock);
	pr_err("%s:%d taskID:%u never shows in thread list\n",
			extra->name, __LINE__, taskID);
	return NULL;
}

/* lock before call this function */
static inline int update_thread_list(RPC_DEV_EXTRA *extra, pid_t pid)
{
	RPC_PROCESS *proc = NULL;
	RPC_PROCESS *proctmp;
	RPC_THREAD *thread;

	spin_lock_bh(&extra->lock);
	list_for_each_entry(proctmp, &extra->tasks, list) {
		/* find the entry in read device task list with the same pid */
		if (proctmp->pid == pid) {
			proc = proctmp;
			break;
		}
	}
	spin_unlock_bh(&extra->lock);

	/* no found, should not happen */
	if (proc == NULL)
		return 0;

	/* current thread is main thread or the thread that open this device */
	if (current->pid == proc->pid)
		return 0;

	spin_lock_bh(&extra->lock);
	list_for_each_entry(thread, &proc->threads, list) {
		/* current is already in thread list */
		if (thread->pid == current->pid) {
			spin_unlock_bh(&extra->lock);
			return 0;
		}
	}
	spin_unlock_bh(&extra->lock);

	/* not found, so add new thread to list */
	thread = kmalloc(sizeof(RPC_THREAD), GFP_KERNEL);
	if (thread == NULL) {
		pr_err("%s: failed to allocate RPC_THREAD\n", __func__);
		return -ENOMEM;
	}
	pr_debug("%s:%d add thread:%s,%d,%d to thread list of process:%d\n",
			__func__, __LINE__, current->comm, current->pid, current->tgid,
			proc->pid);
	thread->pid = current->pid;
	spin_lock_bh(&extra->lock);
	list_add(&thread->list, &proc->threads);
	spin_unlock_bh(&extra->lock);

	return 1;
}

/* Prototypes for shared functions */
#ifdef MY_COPY
int my_copy_to_user(int *des, int *src, int size);
int my_copy_from_user(volatile void __iomem *des, const void *src, int size);

int my_copy_user(int *des, int *src, int size);
#endif

int rpc_poll_init(void);
int rpc_poll_pause(void);
int rpc_poll_suspend(void);
int rpc_poll_resume(void);
void rpc_poll_cleanup(void);
int rpc_intr_init(void);
int rpc_intr_pause(void);
int rpc_intr_suspend(void);
int rpc_intr_resume(void);
void rpc_intr_cleanup(void);

int rpc_kern_init(void);
int rpc_kern_pause(void);
int rpc_kern_suspend(void);
int rpc_kern_resume(void);
ssize_t rpc_kern_read(int opt, char *buf, size_t count);
ssize_t rpc_kern_write(int opt, const char *buf, size_t count);

#define RPC_DVR_MALLOC 0x1
#define RPC_DVR_FREE 0x2
#define RPC_SIO_INIT 0x3

typedef unsigned long (*FUNC_PTR)(unsigned long, unsigned long);
//int register_kernel_rpc(unsigned long command, FUNC_PTR ptr);

extern volatile RPC_DEV *rpc_poll_devices;
extern volatile RPC_DEV *rpc_intr_devices;
extern volatile RPC_DEV *rpc_kern_devices;
extern volatile void __iomem *rpc_int_base;
extern void rpc_set_flag(uint32_t);
#ifdef CONFIG_SND_REALTEK
int RPC_DESTROY_AUDIO_FLOW(int pid);
#endif

/* Use 'k' as magic number */
#define RPC_IOC_MAGIC 'k'

/*
 * S means "Set": through a ptr,
 * T means "Tell": directly with the argument value
 * G means "Get": reply by setting through a pointer
 * Q means "Query": response is on the return value
 * X means "eXchange": G and S atomically
 * H means "sHift": T and Q atomically
 */
#define RPC_IOCTTIMEOUT _IO(RPC_IOC_MAGIC,  0)
#define RPC_IOCQTIMEOUT _IO(RPC_IOC_MAGIC,  1)
#define RPC_IOCTRESET _IO(RPC_IOC_MAGIC,  2)
#ifdef CONFIG_REALTEK_RPC_PROGRAM_REGISTER
#define RPC_IOCTHANDLER _IO(RPC_IOC_MAGIC, 3)
#endif

#define RPC_DBGREG_GET 0
#define RPC_DBGREG_SET 1
#define RPC_IOCTRGETDBGREG_A _IOWR(RPC_IOC_MAGIC, 0x10, RPC_DBG_FLAG)

#define RPC_HAS_BIT(addr, bit) (readl(addr) & bit)
#define RPC_SET_BIT(addr,bit) (writel((readl(addr)|bit), addr))
#define RPC_RESET_BIT(addr,bit) (writel((readl(addr)&~bit), addr))

#define VO_DC_SET_NOTIFY (__cpu_to_be32(1U << 16)) /* ACPU write */
#define VO_DC_FEEDBACK_NOTIFY (__cpu_to_be32(1U << 17))
#define AUDIO_RPC_SET_NOTIFY (__cpu_to_be32(1U << 24)) /* ACPU write */
#define AUDIO_RPC_FEEDBACK_NOTIFY (__cpu_to_be32(1U << 25))

#define DC_VO_SET_NOTIFY (__cpu_to_be32(1U << 0)) /* SCPU write */
#define DC_VO_FEEDBACK_NOTIFY (__cpu_to_be32(1U << 1))
#define RPC_AUDIO_SET_NOTIFY (__cpu_to_be32(1U << 8)) /* SCPU write */
#define RPC_AUDIO_FEEDBACK_NOTIFY (__cpu_to_be32(1U << 9))

#endif /* _RTK_RPC_H */
