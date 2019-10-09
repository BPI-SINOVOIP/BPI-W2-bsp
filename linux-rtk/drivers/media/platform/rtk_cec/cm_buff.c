/*
 *  Copyright (C) 2016 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/slab.h>
#include "cm_buff.h"

#define CHECK_BOUNDRARY(cmb)	\
	do {\
		if (cmb->tail > cmb->end)\
			pr_err("cmb over panic:  cmb=%p cmb->tail (%p) > cmb->end (%p)\n", cmb, cmb->tail, cmb->end);\
		if (cmb->data < cmb->head)\
			pr_err("cmb under panic: cmb=%p cmb->data (%p) < cmb->head (%p)\n", cmb, cmb->data, cmb->head);\
	} while (0)

void cmb_queue_head_init(cm_buff_head *head)
{
	spin_lock_init(&head->lock);
	INIT_LIST_HEAD(&head->list);
	head->qlen = 0;
}
EXPORT_SYMBOL(cmb_queue_head_init);

void cmb_queue_head(cm_buff_head *head, cm_buff *cmb)
{
	unsigned long flags;

	spin_lock_irqsave(&head->lock, flags);

	list_add(&cmb->list, &head->list);
	head->qlen++;

	spin_unlock_irqrestore(&head->lock, flags);
}
EXPORT_SYMBOL(cmb_queue_head);

void cmb_queue_tail(cm_buff_head *head, cm_buff *cmb)
{
	unsigned long flags;

	spin_lock_irqsave(&head->lock, flags);

	list_add_tail(&cmb->list, &head->list);
	head->qlen++;

	spin_unlock_irqrestore(&head->lock, flags);
}
EXPORT_SYMBOL(cmb_queue_tail);

cm_buff *cmb_dequeue(cm_buff_head *head)
{
	cm_buff *cmb = NULL;
	unsigned long flags;

	spin_lock_irqsave(&head->lock, flags);

	if (!list_empty(&head->list)) {
		cmb = list_entry(head->list.next, cm_buff, list);
		list_del_init(&cmb->list);
		head->qlen--;
	}

	spin_unlock_irqrestore(&head->lock, flags);

	return cmb;
}
EXPORT_SYMBOL(cmb_dequeue);

cm_buff *cmb_dequeue_tail(cm_buff_head *head)
{
	cm_buff *cmb = NULL;
	unsigned long flags;

	spin_lock_irqsave(&head->lock, flags);

	if (!list_empty(&head->list)) {
		cmb = list_entry(head->list.prev, cm_buff, list);
		list_del_init(&cmb->list);
		head->qlen--;
	}

	spin_unlock_irqrestore(&head->lock, flags);

	return cmb;
}
EXPORT_SYMBOL(cmb_dequeue_tail);

unsigned int cmb_queue_len(const cm_buff_head *head)
{
	return head->qlen;
}
EXPORT_SYMBOL(cmb_queue_len);

void cmb_queue_purge(cm_buff_head *head)
{
	cm_buff *cmb;
	unsigned long flags;

	spin_lock_irqsave(&head->lock, flags);

	while ((cmb = cmb_dequeue(head)) != NULL)
		kfree_cmb(cmb);

	spin_unlock_irqrestore(&head->lock, flags);
}
EXPORT_SYMBOL(cmb_queue_purge);

cm_buff *alloc_cmb(size_t size)
{
	cm_buff *cmb = kmalloc(sizeof(cm_buff) + size, GFP_KERNEL);

	if (cmb) {
		INIT_LIST_HEAD(&cmb->list);
		init_waitqueue_head(&cmb->wq);
		cmb->status = 0;
		cmb->flags  = 0;
		cmb->head   = ((unsigned char *) cmb) + sizeof(cm_buff);
		cmb->data   = cmb->head;
		cmb->tail   = cmb->head;
		cmb->end    = cmb->head + size;
		cmb->len    = 0;
	}
	return cmb;
}
EXPORT_SYMBOL(alloc_cmb);

void kfree_cmb(cm_buff *cmb)
{
	if (cmb)
		kfree(cmb);
}
EXPORT_SYMBOL(kfree_cmb);

int cmb_tailroom(const cm_buff *cmb)
{
	return cmb->end - cmb->tail;
}
EXPORT_SYMBOL(cmb_tailroom);

void cmb_reserve(cm_buff *cmb, unsigned int len)
{
	cmb->data += len;
	cmb->tail += len;
	CHECK_BOUNDRARY(cmb);
}
EXPORT_SYMBOL(cmb_reserve);

unsigned char *cmb_put(cm_buff *cmb, unsigned int len)
{
	unsigned char *ptr = cmb->tail;

	cmb->tail += len;
	cmb->len  += len;
	CHECK_BOUNDRARY(cmb);
	return ptr;
}
EXPORT_SYMBOL(cmb_put);

unsigned char *cmb_push(cm_buff *cmb, unsigned int len)
{
	cmb->data -= len;
	cmb->len  += len;
	CHECK_BOUNDRARY(cmb);
	return cmb->data;
}
EXPORT_SYMBOL(cmb_push);

unsigned char *cmb_pull(cm_buff *cmb, unsigned int len)
{
	if (len <= cmb->len) {
		cmb->data += len;
		cmb->len  -= len;
		return cmb->data;
	}
	return NULL;
}
EXPORT_SYMBOL(cmb_pull);

void cmb_purge(cm_buff *cmb)
{
	cmb->data = cmb->head;
	cmb->tail = cmb->head;
	cmb->len  = 0;
}
EXPORT_SYMBOL(cmb_purge);
