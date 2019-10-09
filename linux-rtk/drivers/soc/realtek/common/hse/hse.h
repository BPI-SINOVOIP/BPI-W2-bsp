#ifndef __SOC_REALTEK_HSE_H__
#define __SOC_REALTEK_HSE_H__

#include <linux/io.h>
#include <linux/types.h>
#include <linux/clk.h>
#include <linux/reset.h>
#include <linux/wait.h>
#include <linux/miscdevice.h>

#define HSE_MAX_ENGINES          4
#define HSE_MAX_IRQS             2

#define HSE_REG_ENGINE_BASE(i)   (0x100 * (i))
#define HSE_REG_ENGINE_OFFSET_QB         0x00
#define HSE_REG_ENGINE_OFFSET_QL         0x04
#define HSE_REG_ENGINE_OFFSET_QR         0x08
#define HSE_REG_ENGINE_OFFSET_QW         0x0C
#define HSE_REG_ENGINE_OFFSET_Q          0x10
#define HSE_REG_ENGINE_OFFSET_INTS       0x14
#define HSE_REG_ENGINE_OFFSET_SWAP       0x18
#define HSE_REG_ENGINE_OFFSET_QCL        0x1C
#define HSE_REG_ENGINE_OFFSET_QCH        0x20
#define HSE_REG_ENGINE_OFFSET_INTC       0x24

#define HSE_REG_BYPASS  0x41c

enum {
	HSE_STATUS_IRQ_OK = 0x1,
	HSE_STATUS_IRQ_CMD_ERR = 0x2,
	HSE_STATUS_TIMEOUT = 0x4,
};

struct hse_device;
struct hse_command_queue;

struct hse_engine {
	struct hse_device *hdev;
	int base_offset;
	unsigned int status;
	struct mutex req_lock;
	int req;
	wait_queue_head_t cmd_done_wait;
	bool cmd_done;
	struct hse_command_queue *cq;
};


int hse_engine_init(struct hse_device *hdev, int index);
void hse_engine_fini(struct hse_device *hdev, int index);
int hse_engine_suspend(struct hse_engine *eng);
int hse_engine_resume(struct hse_engine *eng);

struct hse_engine *hse_engine_get_any(struct hse_device *hdev);
void hse_engine_put(struct hse_engine *eng);

void hse_engine_check_ints(struct hse_engine *eng);
void hse_engine_execute_cq(struct hse_engine *eng, struct hse_command_queue *cq);


struct hse_command_queue {
	struct hse_device *hdev;
	dma_addr_t phys;
	void *virt;
	size_t size;
	int pos;
};

struct hse_command_queue *hse_cq_alloc(struct hse_device *hdev);
void hse_cq_free(struct hse_command_queue *cq);
void hse_cq_add_data(struct hse_command_queue *cq, u32 *data, size_t size);
void hse_cq_pad(struct hse_command_queue *cq);
void hse_cq_reset(struct hse_command_queue *cq);

struct hse_engine_group {
	int engine_mask;
	const char *irq_name;
};

struct hse_desc {
	int num_groups;
	const struct hse_engine_group *groups;
};

struct hse_device {
	struct device *dev;
	struct miscdevice mdev;
	struct clk *clk;
	struct reset_control *rstc;
	void *base;
	struct hse_engine *engs[HSE_MAX_ENGINES];
	unsigned int engine_mask;
	int irqs[HSE_MAX_IRQS];
	struct hse_desc *desc;
};

static inline void hse_write(struct hse_device *hdev, unsigned int offset,
	u32 val)
{
	dev_dbg(hdev->dev, "w: offset=%03x, val=%08x\n", offset, val);
	writel(val, hdev->base + offset);
}

static inline int hse_read(struct hse_device *hdev, unsigned int offset)
{
	u32 v;

	v = readl(hdev->base + offset);
	dev_dbg(hdev->dev, "r: offset=%03x, val=%08x\n", offset, v);
	return v;
}

extern const struct file_operations hse_fops;

#ifdef CONFIG_RTK_HSE_SELFTEST
int hse_self_test(struct hse_device *hdev);
#else
static inline int hse_self_test(struct hse_device *hdev)
{
	return 0;
}
#endif

#endif /* __SOC_REALTEK_HSE_H__ */
