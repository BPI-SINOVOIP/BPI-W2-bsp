#include <linux/module.h>
#include <linux/fs.h>
#include <linux/pm_runtime.h>
#include <linux/slab.h>
#include <linux/dma-mapping.h>
#include "hse.h"
#include "include/hsectl.h"

#include <linux/uaccess.h>
#include <linux/mm.h>

struct hse_file_data {
	struct hse_device *hdev;
	struct hse_command_queue *cq;
	atomic_t busy;
};

static int hse_open(struct inode *inode, struct file *filp)
{
	struct hse_device *hdev = container_of(filp->private_data,
		struct hse_device, mdev);
	struct hse_file_data *data;
	int ret;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->hdev = hdev;
	atomic_set(&data->busy, 0);
	data->cq = hse_cq_alloc(hdev);
	if (!data->cq) {
		ret = -ENOMEM;
		goto free_data;
	}

	filp->private_data = data;
	pm_runtime_get_sync(hdev->dev);
	return 0;
free_data:
	kfree(data);
	return ret;
}

static int hse_release(struct inode *inode, struct file *filp)
{
	struct hse_file_data *data = filp->private_data;
	struct hse_command_queue *cq = data->cq;

	pm_runtime_put_sync(cq->hdev->dev);
	hse_cq_free(cq);
	kfree(data);
	return 0;
}

static const struct vm_operations_struct hse_vm_ops = {
#ifdef CONFIG_HAVE_IOREMAP_PROT
        .access = generic_access_phys,
#endif
};

#ifdef CONFIG_RTK_HSE_TESTBUF_EXPORT
static int hse_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct hse_file_data *data = filp->private_data;
	struct hse_device *hdev = data->hdev;
	phys_addr_t addr = hdev->test_phys;
	resource_size_t size = HSE_TEST_BUF_SIZE;

	if (!hdev->test_virt)
		return -ENOMEM;

	if (vma->vm_end < vma->vm_start)
		return -EINVAL;

	if ((HSE_TEST_BUF_SIZE >> PAGE_SHIFT) <= vma->vm_pgoff)
		return -EINVAL;

	if ((vma->vm_end - vma->vm_start) > size)
		return -EINVAL;

	vma->vm_ops = &hse_vm_ops;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	return remap_pfn_range(vma,
			       vma->vm_start,
			       (addr >> PAGE_SHIFT) + vma->vm_pgoff,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot);
}
#endif


static long hse_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct hse_file_data *data = filp->private_data;
	struct hse_command_queue *cq = data->cq;
	int ret;
	struct hse_cmd c;
	struct hse_testbuf_info m __maybe_unused;
	struct hse_engine *eng;
	int busy;

	switch (cmd) {
	case HSE_IOCTL_ADD_CMD:
		busy = atomic_xchg(&data->busy, 1);
		if (busy)
			return -EBUSY;

		ret = copy_from_user(&c, (unsigned int __user *)arg, sizeof(c));
		if (ret)
			return ret;

		hse_cq_add_data(cq, c.cmds, c.size);
		atomic_set(&data->busy, 0);
		break;

	case HSE_IOCTL_START:
		busy = atomic_xchg(&data->busy, 1);
		if (busy)
			return -EBUSY;

		hse_cq_pad(cq);
		eng = hse_engine_get_any(cq->hdev);
		if (!eng)
			return -EBUSY;
		hse_engine_execute_cq(eng, cq);
		hse_engine_put(eng);
		hse_cq_reset(cq);
		atomic_set(&data->busy, 0);
		break;

#ifdef CONFIG_RTK_HSE_TESTBUF_EXPORT
	case HSE_IOCTL_SELFTEST_MEM:
		if (!data->hdev->test_virt)
			return -ENOMEM;

		m.phys = data->hdev->test_phys;
		m.size = HSE_TEST_BUF_SIZE;
		ret = copy_to_user((void *)arg,  &m, sizeof (m));
		if (ret)
			return ret;
		break;
#endif
	}

	return 0;
}

static long hse_compact_ioctl(struct file *filp, unsigned int cmd,
			      unsigned long arg)
{
	return hse_ioctl(filp, cmd, arg);
}

const struct file_operations hse_fops = {
	.owner          = THIS_MODULE,
	.open           = hse_open,
	.unlocked_ioctl = hse_ioctl,
	.compat_ioctl   = hse_compact_ioctl,
	.release        = hse_release,
#ifdef CONFIG_RTK_HSE_TESTBUF_EXPORT
	.mmap           = hse_mmap,
#endif
};

#ifdef CONFIG_RTK_HSE_TESTBUF_EXPORT
int hse_create_testbuf(struct hse_device *hdev)
{
	hdev->test_virt = dma_alloc_coherent(hdev->dev, HSE_TEST_BUF_SIZE,
				             &hdev->test_phys, GFP_KERNEL);
	if (!hdev->test_virt) {
		dev_err(hdev->dev, "failed to alloc test_buf\n");
		return -ENOMEM;
	}
	return 0;
}
#endif
