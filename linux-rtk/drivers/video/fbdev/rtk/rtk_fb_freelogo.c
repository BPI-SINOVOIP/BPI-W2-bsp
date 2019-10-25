/**
 * rtk_fb_freelogo.c - Provide function to free bootlogo reserved mem
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#include <linux/delay.h>
#include <linux/mm.h>
#include <linux/kthread.h>
#include <linux/sched.h>

static DEFINE_MUTEX(free_logo_mutex);

#define INVERT_BITVAL_1 ~1

static struct task_struct *free_logo_task;

static void free_logo_rsv_mem(void *data) {
	mutex_lock(&free_logo_mutex);
	free_reserved_area(phys_to_virt(0x30000000),
					   phys_to_virt(0x30900000),
					   0,
					   "logo area"
					   );
	mutex_unlock(&free_logo_mutex);
}

static int free_logo_threadfn(void *data) {
	struct sched_param param = {
		.sched_priority = MAX_RT_PRIO - 2,
	};
	int timeout = 5;

	sched_setscheduler(current, SCHED_FIFO, &param);
	while (1) {
		if (kthread_should_stop() || timeout == 0)
			break;
		msleep(1000);
		timeout--;
	}
	free_logo_rsv_mem(data);
	return 0;
}

static void rtk_fb_free_logo_rsv_mem_init (void)
{
	/* create a thread to sleep N sec, then free logo reserved mem. area */
	/* disabled by default */
	#if 0
	free_logo_task = kthread_create(free_logo_threadfn, NULL, "free_logo_area" );
	if (IS_ERR(free_logo_task)) {
		printk(KERN_ERR "\033[1;33m" "Failed to create free logo kthread task" "\033[m\n");
		return 0;
	}
	kthread_bind(free_logo_task, 0);
	wake_up_process(free_logo_task);
	#endif
	free_logo_rsv_mem(NULL);
}
EXPORT_SYMBOL(rtk_fb_free_logo_rsv_mem_init);

ssize_t freelogo_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count) {
	unsigned long state;
	int ret;
	ret = kstrtol(buf, 0, &state);
	/* valid input value: 0 or 1 */
	if (ret != 0 || state & INVERT_BITVAL_1)
		return -EINVAL;

	if (state == 1)
		free_logo_rsv_mem(NULL);

	return count;
}