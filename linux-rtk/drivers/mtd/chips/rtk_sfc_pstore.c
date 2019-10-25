#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/pstore.h>
#include <linux/mtd/mtd.h>

#include "rtk_sfc.h"

#define RTKSFCOOPS_KERNMSG_MAGIC 0x52544b5346435053	/* 'RTKSFCPS' */
#define RTKSFCOOPS_HEADER_SIZE 8

static char mtddev[80] = "oops";

static struct mtd_info *mtd = NULL;

static unsigned long record_size = 32768;
module_param(record_size, ulong, 0400);
MODULE_PARM_DESC(record_size, "size of each dump record (default 32768)");

static unsigned long mtd_size;
module_param(mtd_size, ulong, 0400);
MODULE_PARM_DESC(mtd_size, "size of MTD partition");

static unsigned long erasesize;
module_param(erasesize, ulong, 0400);
MODULE_PARM_DESC(erasesize, "erasesize of MTD partition");

static unsigned int records;
module_param(records, uint, 0400);
MODULE_PARM_DESC(records, "number of dump records");

struct rtksfcoops_context {
	int nextrcd;
	unsigned int oops_records;
	unsigned int oops_read_cnt;
	void *oops_buf;

	struct pstore_info pstore;
};

struct oops_log_info {
	u64 magic;
	enum pstore_type_id type;
	size_t log_size;
	__u64 timestamp;
	bool compressed;
};

static int rtk_sfc_pstore_open(struct pstore_info *psi)
{
	struct rtksfcoops_context *cxt = psi->data;

	cxt->oops_read_cnt = 0;

	return 0;
}

static int rtk_sfc_pstore_close(struct pstore_info *psi)
{
	return 0;
}

static int rtk_sfc_read_hdr(uint * c, uint max, u64 * id,
			    enum pstore_type_id *type, struct timespec *time,
			    bool * compressed, size_t * log_size)
{
	struct oops_log_info oops_hdr;
	unsigned int offset;
	size_t retlen;
	int i = (*c)++;

	if (i >= max)
		return -1;

	offset = i * record_size;
	mtd_read(mtd, offset, sizeof(oops_hdr), &retlen, (void *)&oops_hdr);
	if (retlen != sizeof(oops_hdr))
		return -1;

	if (oops_hdr.magic != RTKSFCOOPS_KERNMSG_MAGIC)
		return -1;

	*type = oops_hdr.type;
	*id = i;
	*log_size = oops_hdr.log_size;
	time->tv_sec = oops_hdr.timestamp;
	time->tv_nsec = 0;
	*compressed = oops_hdr.compressed;

	return i;
}

static ssize_t rtk_sfc_pstore_read(u64 * id, enum pstore_type_id *type,
				   int *count, struct timespec *time,
				   char **buf, bool * compressed,  ssize_t *ecc_notice_size,
				   struct pstore_info *psi)
{
	ssize_t size;
	struct rtksfcoops_context *cxt = psi->data;
	unsigned int offset;
	size_t hlen = sizeof(struct oops_log_info);
	size_t log_size;
	size_t retlen;
	int rcd = -1;

	time->tv_sec = 0;
	time->tv_nsec = 0;
	*compressed = false;

	/* Get oops header */
	while ((cxt->oops_read_cnt < cxt->oops_records) && (rcd == -1)) {
		rcd =
		    rtk_sfc_read_hdr(&cxt->oops_read_cnt, cxt->oops_records, id,
				     type, time, compressed, &log_size);

		if (rcd == -1)
			continue;
	}

	if (rcd == -1)
		return 0;

	/* Read oops data */
	*buf = kmalloc(log_size, GFP_KERNEL);
	if (*buf == NULL)
		return -ENOMEM;

	offset = rcd * record_size;
	mtd_read(mtd, offset + hlen, log_size, &retlen, *buf);
	size = retlen;

	return size;
}

/*
 * This structure is copied from drivers/mtd/mtdpart.c.
 */
struct mtd_part {
	struct mtd_info mtd;
	struct mtd_info *master;
	uint64_t offset;
	struct list_head list;
};

/*
 * This function is copied from drivers/mtd/mtdpart.c.
 */
static inline struct mtd_part *mtd_to_part(const struct mtd_info *mtd)
{
	return container_of(mtd, struct mtd_part, mtd);
}

/*
 * This function is modified from drivers/mtd/mtdpart.c.
 */
static int part_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	struct mtd_part *part = mtd_to_part(mtd);
	int ret;

	/* Pass master MTD object and the offset from the start of flash device */
	instr->addr += part->offset;
	ret = rtk_sfc_panic_erase(part->master, instr);
	if (ret) {
		if (instr->fail_addr != MTD_FAIL_ADDR_UNKNOWN)
			instr->fail_addr -= part->offset;
		instr->addr -= part->offset;
	}
	return ret;
}

static int rtk_sfc_oops_erase(struct rtksfcoops_context *cxt, int offset,
			      int size)
{
	struct erase_info erase;
	int ret = 0;

	erase.mtd = mtd;
	erase.addr = offset;
	erase.len = size;

	/* earse blocks at address within a partition */
	ret = part_erase(mtd, &erase);

	return 0;
}

static int rtk_sfc_pstore_write(enum pstore_type_id type,
				enum kmsg_dump_reason reason, u64 * id,
				unsigned int part, int count, bool compressed,
				size_t size, struct pstore_info *psi)
{
	struct rtksfcoops_context *cxt = psi->data;
	struct oops_log_info *oops_hdr = (struct oops_log_info *)cxt->oops_buf;
	size_t retlen;

	if (cxt->nextrcd >= cxt->oops_records) {
		pr_err("rtk_sfc_pstore: no storage space left\n");
		return -ENOSPC;
	}

	pr_info
	    ("rtk_sfc_pstore: write log to record %d in MTD partition \"%s\"\n",
	     cxt->nextrcd, mtddev);

	/* Erase record */
	rtk_sfc_oops_erase(cxt, cxt->nextrcd * record_size, record_size);

	/* Set oops header */
	oops_hdr->magic = RTKSFCOOPS_KERNMSG_MAGIC;
	oops_hdr->type = type;
	oops_hdr->log_size = size;
	oops_hdr->timestamp = get_seconds();
	oops_hdr->compressed = compressed;

	/* Write oops header and data */
	mtd_panic_write(mtd, cxt->nextrcd * record_size,
			sizeof(*oops_hdr) + size, &retlen, cxt->oops_buf);

	cxt->nextrcd++;

	return 0;
}

static void rtk_sfc_erase_callback(struct erase_info *done)
{
	wait_queue_head_t *wait_q = (wait_queue_head_t *) done->priv;
	wake_up(wait_q);
}

static int rtk_sfc_erase_record(struct rtksfcoops_context *cxt, int offset,
				int size)
{
	struct erase_info erase;
	DECLARE_WAITQUEUE(wait, current);
	wait_queue_head_t wait_q;
	int ret;

	init_waitqueue_head(&wait_q);
	erase.mtd = mtd;
	erase.callback = rtk_sfc_erase_callback;
	erase.addr = offset;
	erase.len = size;
	erase.priv = (u_long) & wait_q;

	set_current_state(TASK_INTERRUPTIBLE);
	add_wait_queue(&wait_q, &wait);

	ret = mtd_erase(mtd, &erase);
	if (ret) {
		set_current_state(TASK_RUNNING);
		remove_wait_queue(&wait_q, &wait);
		printk(KERN_WARNING
		       "rtk_sfc_pstore: erase of region [0x%llx, 0x%llx] on \"%s\" failed\n",
		       (unsigned long long)erase.addr,
		       (unsigned long long)(erase.addr + erase.len), mtddev);
		return ret;
	}

	schedule();		/* Wait for erase to finish. */
	remove_wait_queue(&wait_q, &wait);

	return 0;
}

static int rtk_sfc_pstore_erase(enum pstore_type_id type, u64 id, int count,
				struct timespec time, struct pstore_info *psi)
{
	struct rtksfcoops_context *cxt = psi->data;

	rtk_sfc_erase_record(cxt, id * record_size, record_size);

	return 0;
}

static struct rtksfcoops_context oops_cxt = {
	.pstore = {
		   .owner = THIS_MODULE,
		   .name = "rtksfc",
		   .open = rtk_sfc_pstore_open,
		   .close = rtk_sfc_pstore_close,
		   .read = rtk_sfc_pstore_read,
		   .write = rtk_sfc_pstore_write,
		   .erase = rtk_sfc_pstore_erase,
		   },
};

static int __init rtk_sfc_pstore_init(void)
{
	struct rtksfcoops_context *cxt = &oops_cxt;
	int rc = 0;

	/* Obtain a handle for an MTD device by device name */
	mtd = get_mtd_device_nm(mtddev);
	if (IS_ERR(mtd)) {
		pr_err("rtk_sfc_pstore: no MTD partition \"%s\" found\n",
		       mtddev);
		return -ENODEV;
	}

	pr_info
	    ("rtk_sfc_pstore: attach to MTD partition \"%s\" with size %llu and erasesize %u\n",
	     mtddev, mtd->size, mtd->erasesize);
	mtd_size = mtd->size;
	erasesize = mtd->erasesize;

	if ((record_size & (erasesize - 1)) != 0) {
		pr_err
		    ("rtk_sfc_pstore: record_size must be a multiple of erasesize %u\n",
		     mtd->erasesize);
		rc = -EINVAL;
		goto fail_device;
	}

	cxt->nextrcd = 0;
	cxt->oops_records = mtd->size / record_size;
	records = cxt->oops_records;
	pr_info("rtk_sfc_pstore: %d records of record_size %lu\n",
		cxt->oops_records, record_size);

	cxt->pstore.data = cxt;
	cxt->oops_buf = kmalloc(record_size, GFP_KERNEL);
	if (!cxt->oops_buf) {
		pr_err("cannot allocate pstore buffer\n");
		rc = -ENOMEM;
		goto fail_device;
	}

	memset(cxt->oops_buf, 0xff, record_size);
	cxt->pstore.buf = cxt->oops_buf + sizeof(struct oops_log_info);
	cxt->pstore.bufsize = record_size - sizeof(struct oops_log_info);

	spin_lock_init(&cxt->pstore.buf_lock);

	rc = pstore_register(&cxt->pstore);
	if (rc) {
		if (rc != -EPERM)
			pr_err("rtk_sfc_pstore: cannot register with pstore\n");
		goto fail_buf;
	}

	return 0;

 fail_buf:
	kfree(cxt->oops_buf);
	cxt->oops_buf = NULL;
	cxt->pstore.buf = NULL;
	cxt->pstore.bufsize = 0;
 fail_device:
	put_mtd_device(mtd);

	return rc;
}

static void __exit rtk_sfc_pstore_exit(void)
{
	struct rtksfcoops_context *cxt = &oops_cxt;

	pstore_unregister(&cxt->pstore);

	kfree(cxt->oops_buf);
	if (mtd)
		put_mtd_device(mtd);
}

module_init(rtk_sfc_pstore_init);
module_exit(rtk_sfc_pstore_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chien-Ming Cheng <cmcheng@realtek.com.tw>");
MODULE_DESCRIPTION("Realtek SPI flash backend for pstore");
