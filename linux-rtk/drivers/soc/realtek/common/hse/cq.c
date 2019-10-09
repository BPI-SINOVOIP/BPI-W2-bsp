#include <linux/dma-mapping.h>
#include <linux/slab.h>
#include "asm/cacheflush.h"
#include "hse.h"

struct hse_command_queue *hse_cq_alloc(struct hse_device *hdev)
{
	struct device *dev = hdev->dev;
	struct hse_command_queue *cq = NULL;

	cq = kzalloc(sizeof(*cq), GFP_KERNEL);
	if (!cq)
		return NULL;

	cq->hdev = hdev;
	cq->size = PAGE_SIZE;
	cq->virt = dma_alloc_coherent(dev, cq->size, &cq->phys,
		GFP_KERNEL | GFP_DMA);
	if (!cq->virt)
		goto free_cq;

	dev_info(hdev->dev, "%s: phys:%pad, virt=%p\n", __func__,
		&cq->phys, cq->virt);
	return cq;

free_cq:
	kfree(cq);
	return NULL;
}

void hse_cq_free(struct hse_command_queue *cq)
{
	struct device *dev = cq->hdev->dev;

	dma_free_coherent(dev, cq->size, cq->virt, cq->phys);
	kfree(cq);
}

static inline void __hse_cq_add_data_one(struct hse_command_queue *cq, u32 data)
{
	u32 *ptr = (cq->virt + cq->pos);

	if (cq->pos >= cq->size) {
		WARN(1, "cq full\n");
		return;
	}

	pr_debug("%s: add data=%08x to %p\n", __func__, data, ptr);
	*ptr++ = data;
	cq->pos += 4;

	if ((cq->pos % 16) == 0) {
		u32 tmp;

		ptr -= 4;

		tmp    = ptr[0];
		ptr[0] = ptr[3];
		ptr[3] = tmp;

		tmp    = ptr[1];
		ptr[1] = ptr[2];
		ptr[2] = tmp;
	}
}


void hse_cq_add_data(struct hse_command_queue *cq, u32 *data, size_t size)
{
	int i;

	for (i = 0; i < size; i++)
		__hse_cq_add_data_one(cq, data[i]);
#if defined(CONFIG_ARCH_MULTI_V7)
	v7_flush_kern_dcache_area(cq->virt, cq->pos);
#else
	__flush_dcache_area(cq->virt, cq->pos);
#endif /* CONFIG_ARCH_MULTI_V7 */
}

void hse_cq_pad(struct hse_command_queue *cq)
{
	__hse_cq_add_data_one(cq, 0);
	while (cq->pos % 16)
		__hse_cq_add_data_one(cq, 0);
#if defined(CONFIG_ARCH_MULTI_V7)
	v7_flush_kern_dcache_area(cq->virt, cq->pos);
#else
	__flush_dcache_area(cq->virt, cq->pos);
#endif
}

void hse_cq_reset(struct hse_command_queue *cq)
{
	cq->pos = 0;
}
