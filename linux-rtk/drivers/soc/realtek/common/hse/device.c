#include <linux/module.h>
#include <linux/fs.h>
#include <linux/pm_runtime.h>
#include "hse.h"

#include <linux/uaccess.h>

struct hse_cmd {
	u32 size;
	u32 cmds[32];
};

#define HSE_IOCTL_VERSION   _IOR('H', 0x00, unsigned int)
#define HSE_IOCTL_ADD_CMD   _IOW('H', 0x01, struct hse_cmd)
#define HSE_IOCTL_START     _IO('H', 0x02)

static int hse_open(struct inode *inode, struct file *filp)
{
	struct hse_device *hdev = container_of(filp->private_data,
		struct hse_device, mdev);
	struct hse_command_queue *cq;

	cq = hse_cq_alloc(hdev);
	if (!cq)
		return -ENOMEM;

	filp->private_data = cq;
	pm_runtime_get_sync(hdev->dev);

	return 0;
}

static int hse_release(struct inode *inode, struct file *filp)
{
	struct hse_command_queue *cq = filp->private_data;

	pm_runtime_put_sync(cq->hdev->dev);
	hse_cq_free(cq);

	return 0;
}

static long hse_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct hse_command_queue *cq = filp->private_data;
	int ret;

	switch (cmd) {
	case HSE_IOCTL_ADD_CMD: {
		struct hse_cmd cmd;

		ret = copy_from_user(&cmd, (unsigned int __user *)arg,
			sizeof(struct hse_cmd));
		if (ret)
			return ret;

		hse_cq_add_data(cq, cmd.cmds, cmd.size);

		break;
	}
	case HSE_IOCTL_START: {
		struct hse_engine *eng;

		hse_cq_pad(cq);
		eng = hse_engine_get_any(cq->hdev);
		if (!eng)
			return -EBUSY;
		hse_engine_execute_cq(eng, cq);
		hse_engine_put(eng);
		hse_cq_reset(cq);
		break;
	}
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
};

