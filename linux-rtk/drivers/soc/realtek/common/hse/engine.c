#include <linux/slab.h>
#include "hse.h"
#include "asm/cacheflush.h"

static inline int hse_engine_read(struct hse_engine *eng, int offset)
{
	return hse_read(eng->hdev, eng->base_offset + offset);
}

static inline void hse_engine_write(struct hse_engine *eng, int offset,
	unsigned int val)
{
	hse_write(eng->hdev, eng->base_offset + offset, val);
}

int hse_engine_suspend(struct hse_engine *eng)
{
	if (!eng)
		return -EINVAL;

	// TODO

	return 0;
}

int hse_engine_resume(struct hse_engine *eng)
{
	if (!eng)
		return -EINVAL;

	// TODO

	return 0;
}

static void hse_engine_cmd_done(struct hse_engine *eng)
{
	eng->cmd_done = true;
	wake_up_interruptible(&eng->cmd_done_wait);
}

void hse_engine_check_ints(struct hse_engine *eng)
{
	u32 ints;

	ints = hse_engine_read(eng, HSE_REG_ENGINE_OFFSET_INTS);
	if (ints == 0)
		return;
	if (ints & 0x4)
		eng->status |= HSE_STATUS_IRQ_CMD_ERR;
	if (ints & 0x2)
		eng->status |= HSE_STATUS_IRQ_OK;

	/* stop the engine */
	hse_engine_write(eng, HSE_REG_ENGINE_OFFSET_INTC, 0);
	hse_engine_write(eng, HSE_REG_ENGINE_OFFSET_Q,    0);
	hse_engine_write(eng, HSE_REG_ENGINE_OFFSET_INTS, 0x6);

	hse_engine_cmd_done(eng);
}

void hse_engine_wait(struct hse_engine *eng)
{
	int ret;

	ret = wait_event_interruptible_timeout(eng->cmd_done_wait,
		(eng->cmd_done), msecs_to_jiffies(500));
	if (ret == 0)
		eng->status |= HSE_STATUS_TIMEOUT;
	eng->cmd_done = false;
}

void hse_engine_execute_cq(struct hse_engine *eng, struct hse_command_queue *cq)
{
	struct device *dev = eng->hdev->dev;
	/* fill the cq */
	eng->cq = cq;
	hse_engine_write(eng, HSE_REG_ENGINE_OFFSET_QB, cq->phys);
	hse_engine_write(eng, HSE_REG_ENGINE_OFFSET_QL, cq->phys + cq->size);
	hse_engine_write(eng, HSE_REG_ENGINE_OFFSET_QR, cq->phys);
	hse_engine_write(eng, HSE_REG_ENGINE_OFFSET_QW, cq->phys + cq->pos);

	dev_dbg(dev, "qb = %08x\n", hse_engine_read(eng, HSE_REG_ENGINE_OFFSET_QB));
	dev_dbg(dev, "ql = %08x\n", hse_engine_read(eng, HSE_REG_ENGINE_OFFSET_QL));
	dev_dbg(dev, "qr = %08x\n", hse_engine_read(eng, HSE_REG_ENGINE_OFFSET_QR));
	dev_dbg(dev, "qw = %08x\n", hse_engine_read(eng, HSE_REG_ENGINE_OFFSET_QW));

	/* start the engine */
	eng->status = 0;
	hse_engine_write(eng, HSE_REG_ENGINE_OFFSET_INTC, 0x6);
	hse_engine_write(eng, HSE_REG_ENGINE_OFFSET_Q, 0x1);

	/* wait */
	hse_engine_wait(eng);
	// check result
	if (eng->status & ~HSE_STATUS_IRQ_OK)
		dev_err(dev, "engine->status =%04x\n", eng->status);
	dev_dbg(dev, "qb = %08x\n", hse_engine_read(eng, HSE_REG_ENGINE_OFFSET_QB));
	dev_dbg(dev, "ql = %08x\n", hse_engine_read(eng, HSE_REG_ENGINE_OFFSET_QL));
	dev_dbg(dev, "qr = %08x\n", hse_engine_read(eng, HSE_REG_ENGINE_OFFSET_QR));
	dev_dbg(dev, "qw = %08x\n", hse_engine_read(eng, HSE_REG_ENGINE_OFFSET_QW));

	eng->cq = NULL;
}

struct hse_engine *hse_engine_get_any(struct hse_device *hdev)
{
	int i;
	struct hse_engine *eng, *ret = NULL;

	for (i  = 0; i < HSE_MAX_ENGINES; i++) {
		eng = hdev->engs[i];
		if (!eng)
			continue;

		mutex_lock(&eng->req_lock);
		if (eng->req == 0) {
			ret = eng;
			eng->req = 1;
		}
		mutex_unlock(&eng->req_lock);
		if (ret)
			break;
	}
	return ret;
}

void hse_engine_put(struct hse_engine *eng)
{
	if (!eng)
		return;

	mutex_lock(&eng->req_lock);
	eng->req = 0;
	mutex_unlock(&eng->req_lock);
}

int hse_engine_init(struct hse_device *hdev, int index)
{
	struct hse_engine *eng;
	struct device *dev = hdev->dev;

	eng = devm_kzalloc(dev, sizeof(*eng), GFP_KERNEL);
	if (!eng)
		return -ENOMEM;

	if (hdev->irqs[index >> 1] == 0) {
		dev_warn(dev, "irq%d is required by engine%d\n",
			index >> 1, index);
		return -EINVAL;
	}

	eng->hdev = hdev;
	eng->base_offset = HSE_REG_ENGINE_BASE(index);

	mutex_init(&eng->req_lock);
	eng->req = 0;
	init_waitqueue_head(&eng->cmd_done_wait);
	eng->cmd_done = false;

	hse_engine_write(eng, HSE_REG_ENGINE_OFFSET_Q,   0);
	hse_engine_write(eng, HSE_REG_ENGINE_OFFSET_QCL, 0);
	hse_engine_write(eng, HSE_REG_ENGINE_OFFSET_QCH, 0);

	hdev->engs[index] = eng;

	return 0;
}

void hse_engine_fini(struct hse_device *hdev, int index)
{
	// TODO ...
}


