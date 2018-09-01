#include <linux/dma-mapping.h>
#include <linux/pm_runtime.h>
#include <linux/io.h>
#include <linux/slab.h>
#include "asm/cacheflush.h"
#include "hse.h"

#define MEM_SIZE (2*PAGE_SIZE)
#define MEM_NUM   4
static void *dcsys_base;

struct hse_test_buf {
	int type;
	dma_addr_t phys;
	void *virt;
	int size;
};

static void hse_test_buf_free(struct device *dev, struct hse_test_buf *bufs, int mem_num)
{
	int i;

	for (i = 0; i < mem_num; i++) {
		if (!bufs[i].virt)
			continue;
		if (bufs[i].type) {
			iounmap(bufs[i].virt);
		} else {
			dma_free_coherent(dev, bufs[i].size, bufs[i].virt,
				bufs[i].phys);
		}
	}
	kfree(bufs);
}

static __must_check struct hse_test_buf *hse_test_buf_alloc(struct device *dev,
	size_t mem_num, int size, bool secure_en)
{
	struct hse_test_buf *bufs;
	int i;
	dma_addr_t phys_base = 0;

	if (secure_en) {
		u32 val;

		if (!dcsys_base) {
			dev_err(dev, "dcsys is not available\n");
			return NULL;
		}

		val = readl(dcsys_base + 0x408);
		phys_base = val << 2;
	}

	bufs = kcalloc(mem_num, sizeof(*bufs), GFP_KERNEL);
	if (!bufs)
		return NULL;


	for (i = 0; i < mem_num; i++) {
		if (secure_en) {
			bufs[i].type = 1;
			bufs[i].size = size;
			bufs[i].virt = ioremap(phys_base, size);
			bufs[i].phys = phys_base;

			phys_base += size;
		} else {
			bufs[i].type = 0;
			bufs[i].size = size;
			bufs[i].virt = dma_alloc_coherent(dev, size, &bufs[i].phys,
				GFP_KERNEL | GFP_DMA);
		}
		dev_err(dev, "mem%d: type:%d, phys:%pad, virt=%p\n", i,
			bufs[i].type, &bufs[i].phys, bufs[i].virt);
		if (!bufs[i].virt)
			goto error;
	}

	return bufs;
error:
	hse_test_buf_free(dev, bufs, mem_num);
	return NULL;
}

static int hse_test_engine(struct hse_device *hdev, struct hse_engine *eng)
{
	struct device *dev = hdev->dev;
	struct hse_command_queue *cq;
	struct hse_test_buf *bufs;
	int i;
	int ret;
	u32 cmds[32];
	int test;

	dev_info(dev, "engine@%03x: test start", eng->base_offset);

	cq = hse_cq_alloc(hdev);
	if (!cq) {
		dev_err(dev, "failed to alloc cq\n");
		return -ENOMEM;
	}
	bufs = hse_test_buf_alloc(dev, MEM_NUM, MEM_SIZE,
		eng->base_offset < 0x200 ? 1 : 0);
	if (!bufs) {
		dev_err(dev, "failed to alloc buf\n");
		return -ENOMEM;
	}

	/* test 0 */
	test = 0;
	memset(bufs[1].virt, 0x1, MEM_SIZE);
#if defined(CONFIG_ARCH_MULTI_V7)
	v7_flush_kern_dcache_area(bufs[1].virt, MEM_SIZE);
#else
	__flush_dcache_area(bufs[1].virt, MEM_SIZE);
#endif /* CONFIG_ARCH_MULTI_V7 */
	memset(bufs[0].virt, 0x34, MEM_SIZE);
#if defined(CONFIG_ARCH_MULTI_V7)
	v7_flush_kern_dcache_area(bufs[0].virt, MEM_SIZE);
#else
	__flush_dcache_area(bufs[0].virt, MEM_SIZE);
#endif /* CONFIG_ARCH_MULTI_V7 */
	cmds[0] = 0x1;
	cmds[1] = MEM_SIZE;
	cmds[2] = bufs[1].phys;
	cmds[3] = bufs[0].phys;
	hse_cq_add_data(cq, cmds, 4);
	hse_cq_pad(cq);
	hse_engine_execute_cq(eng, cq);
	ret = memcmp(bufs[0].virt, bufs[1].virt, MEM_SIZE);
	if (ret != 0) {
		dev_err(dev, "engine@%03x: test%d failed\n", eng->base_offset,
			test);
		for (i = 0; i < 2; i++) {
			dev_err(dev, "mem%d: %pad\n", i, &bufs[i].phys);
			print_hex_dump(KERN_ERR, "", DUMP_PREFIX_OFFSET, 16, 1,
				bufs[i].virt, 0x40, false);
		}
	} else
		dev_err(dev, "engine@%03x: test%d pass\n", eng->base_offset,
			test);
	hse_cq_reset(cq);

	/* test 1 */
	test = 1;
	i = 0;
	memset(bufs[0].virt, 0x25, MEM_SIZE);
#if defined(CONFIG_ARCH_MULTI_V7)
	v7_flush_kern_dcache_area(bufs[0].virt, MEM_SIZE);
#else
	__flush_dcache_area(bufs[0].virt, MEM_SIZE);
#endif /* CONFIG_ARCH_MULTI_V7 */
	memset(bufs[1].virt, 0x12, MEM_SIZE);
#if defined(CONFIG_ARCH_MULTI_V7)
	v7_flush_kern_dcache_area(bufs[1].virt, MEM_SIZE);
#else
	__flush_dcache_area(bufs[1].virt, MEM_SIZE);
#endif /* CONFIG_ARCH_MULTI_V7 */
	cmds[i++] = 0x10001;
	cmds[i++] = MEM_SIZE;
	cmds[i++] = bufs[2].phys;
	cmds[i++] = bufs[0].phys;
	cmds[i++] = bufs[1].phys;
	cmds[i++] = 0x10001;
	cmds[i++] = MEM_SIZE;
	cmds[i++] = bufs[3].phys;
	cmds[i++] = bufs[1].phys;
	cmds[i++] = bufs[2].phys;
	hse_cq_add_data(cq, cmds, i);
	hse_cq_pad(cq);
	hse_engine_execute_cq(eng, cq);
	ret = memcmp(bufs[0].virt, bufs[3].virt, MEM_SIZE);
	if (ret != 0) {
		dev_err(dev, "engine@%03x: test%d failed\n", eng->base_offset,
			test);
		for (i = 0; i < 4; i++) {
			dev_err(dev, "mem%d: %pad\n", i, &bufs[i].phys);
			print_hex_dump(KERN_ERR, "", DUMP_PREFIX_OFFSET, 16, 1,
				bufs[i].virt, 0x40, false);
		}
	} else
		dev_err(dev, "engine@%03x: test%d pass\n", eng->base_offset,
			test);
	hse_cq_reset(cq);
	ret = 0;

	hse_test_buf_free(dev, bufs, MEM_NUM);
	hse_cq_free(cq);
	dev_info(dev, "engine@%03x: test done with %d", eng->base_offset, ret);
	return ret;
}

static void dcsys_init(void)
{
	u32 __maybe_unused val;

	dcsys_base = ioremap(0x98008000, 0x1000);
	if (!dcsys_base) {
		pr_err("failed to map dc_sys register\n");
		return;
	}
#ifdef DCSYS_DUMP_INT
	writel(0x0, dcsys_base+0x750);
#endif

#ifdef DCSYS_DUMP_PC
	writel((0x60 << 0) | (0x60 << 8) | (1 << 15), dcsys_base + 0x050);
	writel((0x65 << 0) | (0x65 << 8) | (1 << 15), dcsys_base + 0x500);
	writel((0x20 << 0) | (0x20 << 8) | (1 << 15), dcsys_base + 0x504);
	writel(0x1, dcsys_base + 0x030);
#endif
}

static void dcsys_dump(void)
{
	if (!dcsys_base)
		return;
#ifdef DCSYS_DUMP_INT
	pr_err("dc_mem_int=%08x\n", readl(dcsys_base+0x750));
	writel(0x0, dcsys_base+0x750);
#endif

#ifdef DCSYS_DUMP_PC
	pr_err("ree-0 %08x %08x %08x %08x\n", readl(dcsys_base+0x060),
		 readl(dcsys_base+0x064), readl(dcsys_base+0x068),
		 readl(dcsys_base+0x06c));
	pr_err("ree-1 %08x %08x %08x %08x\n", readl(dcsys_base+0x070),
		 readl(dcsys_base+0x074), readl(dcsys_base+0x078),
		 readl(dcsys_base+0x07c));
	pr_err("tee-0 %08x %08x %08x %08x\n", readl(dcsys_base+0x510),
		 readl(dcsys_base+0x514), readl(dcsys_base+0x518),
		 readl(dcsys_base+0x51c));
	pr_err("tee-1 %08x %08x %08x %08x\n", readl(dcsys_base+0x520),
		 readl(dcsys_base+0x524), readl(dcsys_base+0x528),
		 readl(dcsys_base+0x52c));
	pr_err("cpu-0 %08x %08x %08x %08x\n", readl(dcsys_base+0x540),
		 readl(dcsys_base+0x544), readl(dcsys_base+0x548),
		 readl(dcsys_base+0x54c));
	pr_err("cpu-1 %08x %08x %08x %08x\n", readl(dcsys_base+0x550),
		 readl(dcsys_base+0x554), readl(dcsys_base+0x558),
		 readl(dcsys_base+0x55c));
#endif
}

static void dcsys_fini(void)
{
	if (!dcsys_base)
		return;
	iounmap(dcsys_base);
}

int hse_self_test(struct hse_device *hdev)
{
	struct hse_engine *engs[HSE_MAX_ENGINES] = {0};
	int i;

	pm_runtime_get_sync(hdev->dev);
	dcsys_init();
	for (i = 0; i < HSE_MAX_ENGINES; i++) {
		engs[i] = hse_engine_get_any(hdev);
		if (!engs[i])
			break;
	}

	for (i = 0; i < HSE_MAX_ENGINES; i++)
		if (engs[i]) {
			hse_test_engine(hdev, engs[i]);
			dev_err(hdev->dev, "engine@03%x: dcsys_pc result\n",
				i * 100);
			dcsys_dump();
		}

	for (i = 0; i < HSE_MAX_ENGINES; i++)
		if (engs[i])
			hse_engine_put(engs[i]);
	dcsys_fini();
        pm_runtime_put_sync(hdev->dev);
	return 0;
}
