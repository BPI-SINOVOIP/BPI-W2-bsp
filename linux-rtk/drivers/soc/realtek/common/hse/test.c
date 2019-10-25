#define pr_fmt(fmt)  "hse-test: " fmt
#include <linux/dma-mapping.h>
#include <linux/pm_runtime.h>
#include <linux/debugfs.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include <soc/realtek/rtk_chip.h>
#include "hse.h"
#include "hsectl.h"
#include "hse-sw.h"

#define CHECK_ARGS(cond, msg) \
do { \
	if (cond) { \
		pr_err("%s: %s\n", __func__, msg); \
		return -EINVAL; \
	} \
} while (0)


#define HSE_TEST_MEM_SIZE               (4 * PAGE_SIZE)
#define HSE_TEST_MAX_MEM_NUM            (6)
#define HSE_TEST_FILENAME_LENGTH        (100)
#define HSE_TEST_INVAL                  (0xcc)

/*
 * Create debug blob files
 */
static LIST_HEAD(hse_test_blob_list);
static struct dentry *hse_test_root;

struct hse_test_blob {
	struct debugfs_blob_wrapper blob;
	struct list_head list;
};

static void hse_test_init_debugfs(void)
{
	if (!hse_test_root)
		hse_test_root = debugfs_create_dir("hse_test", NULL);
}

static
void hse_test_create_blob_file(const char *filename, void *data,
			       unsigned long size)
{
	struct hse_test_blob *b;

	pr_err("creating file %s\n", filename);

	b = kzalloc(sizeof(*b), GFP_KERNEL);
	if (!b) {
		pr_err("failed to create hse test blob\n");
		return;
	}

	b->blob.size = size;
	b->blob.data = kmemdup(data, size, GFP_KERNEL);
	if (!b->blob.data) {
		pr_err("failed to copy data\n");
		kfree(b);
		return;
	}

	list_add(&b->list, &hse_test_blob_list);
	debugfs_create_blob(filename, 0444, hse_test_root, &b->blob);
}

/*
 * test buf
 */
struct hse_test_buf {
	dma_addr_t phys;
	void *virt;
	int size;
};

static inline
void hse_test_buf_memset(struct hse_test_buf *buf, int val, size_t size,
			 bool flush)
{
	memset(buf->virt, val, size);
	if (flush)
		hse_flush_dcache_area(buf->virt, size);
}

static
void hse_test_buf_free(struct device *dev, struct hse_test_buf *bufs,
		       int mem_num)
{
	int i;

	for (i = 0; i < mem_num; i++) {
		if (!bufs[i].virt)
			continue;
		dma_free_coherent(dev, bufs[i].size, bufs[i].virt,
				bufs[i].phys);
	}
	kfree(bufs);
}

static __must_check
struct hse_test_buf *hse_test_buf_alloc(struct device *dev, size_t mem_num,
					int size)
{
	struct hse_test_buf *bufs;
	int i;

	bufs = kcalloc(mem_num, sizeof(*bufs), GFP_KERNEL);
	if (!bufs)
		return NULL;

	for (i = 0; i < mem_num; i++) {
		bufs[i].size = size;
		bufs[i].virt = dma_alloc_coherent(dev, size, &bufs[i].phys,
			GFP_KERNEL | GFP_DMA);
		dev_err(dev, "mem%d: phys:%pad, virt=%p\n", i,
			&bufs[i].phys, bufs[i].virt);
		if (!bufs[i].virt)
			goto error;
	}

	return bufs;
error:
	hse_test_buf_free(dev, bufs, mem_num);
	return NULL;
}

struct hse_test_obj {
	int pass;
	int fail;
	int total;
	struct hse_test_buf *bufs;
	struct hse_engine *eng;

	char test_info[1024];
	int test_info_size;
	ktime_t start;
};

#define TEST_BEGIN(_hobj, _fmt, ...) \
do { \
	(_hobj)->test_info_size = sprintf((_hobj)->test_info, _fmt, ##__VA_ARGS__); \
	pr_err("\n"); \
	pr_err("### test: %d => " _fmt, ++(_hobj)->total, ##__VA_ARGS__); \
	(_hobj)->start = ktime_get(); \
} while (0);

#define TEST_END(_hobj, _ret) \
do { \
	s64 delta = ktime_to_us(ktime_sub(ktime_get(), (_hobj)->start)); \
\
	pr_err("\n"); \
	pr_err("  result: %s (takes %lld us)\n", (_ret) ? "failed" : "passed", delta); \
	if (_ret) \
		(_hobj)->fail++; \
	else  \
		(_hobj)->pass++; \
} while (0);

static
void hse_test_obj_create_blob_file(struct hse_test_obj *hobj, const char *name,
				   void *data, unsigned long size)
{
	char n[HSE_TEST_FILENAME_LENGTH];

	sprintf(n, "e%03x-t%03d.%s", hobj->eng->base_offset, hobj->total, name);
	hse_test_create_blob_file(n, data, size);
}

static __must_check
struct hse_test_obj *hse_test_obj_alloc(struct hse_engine *eng)
{
	struct hse_test_obj *hobj;
	struct hse_device *hdev = eng->hdev;
	struct hse_test_buf *bufs;

	hobj = kzalloc(sizeof(*hobj), GFP_KERNEL);
	if (!hobj) {
		pr_err("fail to alloc test_obj\n");
		return NULL;
	}

	bufs = hse_test_buf_alloc(hdev->dev, HSE_TEST_MAX_MEM_NUM, HSE_TEST_MEM_SIZE);
	if (!bufs) {
		pr_err("failed to alloc buf\n");
		kfree(hobj);
		return NULL;
	}

	hobj->bufs = bufs;
	hobj->eng = eng;
	return hobj;
}

static void hse_test_obj_free(struct hse_test_obj *hobj)
{
	hse_test_buf_free(hobj->eng->hdev->dev, hobj->bufs, HSE_TEST_MAX_MEM_NUM);
	kfree(hobj);
}

/*
 * run commands
 */
static
int hse_test_run_cmd(struct hse_engine *eng, uint32_t *cmds, uint32_t size)
{
	struct hse_command_queue *cq;

	cq = hse_cq_alloc(eng->hdev);
	if (!cq)
		return -ENOMEM;

	hse_cq_add_data(cq, cmds, size);
	hse_cq_pad(cq);
	hse_engine_execute_cq(eng, cq);
	hse_cq_free(cq);
	return 0;
}

/*********************************************************************
 *
 * copy
 *
 *********************************************************************/
static
int hse_copy(struct hse_engine *eng, struct hse_test_buf *dst,
	     struct hse_test_buf *src, uint32_t size)
{
	uint32_t cmds[32];

	cmds[0] = 0x1;
	cmds[1] = size;
	cmds[2] = dst->phys;
	cmds[3] = src->phys;
	return hse_test_run_cmd(eng, cmds, 4);
}

static
int hse_copy_verify_result(struct hse_test_obj *hobj, struct hse_test_buf *dst,
			   struct hse_test_buf *src, uint32_t size)
{
	int ret;

	ret = memcmp(dst->virt, src->virt, size);
	if (!ret)
		return ret;

	ret = -EINVAL;
	hse_test_obj_create_blob_file(hobj, "info", hobj->test_info, hobj->test_info_size);
	hse_test_obj_create_blob_file(hobj, "src", src->virt, size);
	hse_test_obj_create_blob_file(hobj, "dst", dst->virt, size);
	return ret;
}

/*********************************************************************
 *
 * xor
 *
 *********************************************************************/
static int hse_xor_verify_args(uint32_t num_srcs, uint32_t size)
{
	CHECK_ARGS(num_srcs < 1 || num_srcs > 5, "invalid num_srcs");
	return 0;
}

static
int hse_xor(struct hse_engine *eng, struct hse_test_buf *dst,
	    struct hse_test_buf *srcs, uint32_t num_srcs, uint32_t size)
{
	uint32_t cmds[32];
	uint32_t i;

	if (hse_xor_verify_args(num_srcs, size))
		return -EINVAL;

	i = 0;
	cmds[i++] = 0x01 | ((num_srcs-1) << 16);
	cmds[i++] = size;
	cmds[i++] = dst->phys;
	cmds[i++] = srcs[0].phys;
	if (num_srcs > 1)
		cmds[i++] = srcs[1].phys;
	if (num_srcs > 2)
		cmds[i++] = srcs[2].phys;
	if (num_srcs > 3)
		cmds[i++] = srcs[3].phys;
	if (num_srcs > 4)
		cmds[i++] = srcs[4].phys;
	return hse_test_run_cmd(eng, cmds, i);
}

static
int hse_xor_verify_result(struct hse_test_obj *hobj, struct hse_test_buf *dst,
			  struct hse_test_buf *srcs, uint32_t num_srcs,
			  uint32_t size)
{
	char name[HSE_TEST_FILENAME_LENGTH];
	u8 *p;
	int i, j;
	int ret;

	p = kzalloc(size, GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	for (i = 0; i < size; i++) {
		p[i] = ((u8 *)srcs[0].virt)[i];
		for (j = 1; j < num_srcs; j++)
			p[i] ^= ((u8 *)srcs[j].virt)[i];
	}
	ret = memcmp(dst->virt, p, size);
	if (!ret)
		goto done;

	ret = -EINVAL;
	hse_test_obj_create_blob_file(hobj, "info", hobj->test_info, hobj->test_info_size);
	for (i = 0; i < num_srcs; i++) {
		sprintf(name, "src%d", i);
		hse_test_obj_create_blob_file(hobj, name, srcs[i].virt, size);
	}
	hse_test_obj_create_blob_file(hobj, "dst", dst->virt, size);
	hse_test_obj_create_blob_file(hobj, "sw", p, size);
done:
	kfree(p);
	return ret;
}


/*********************************************************************
 *
 * yuyv2nv12
 *
 *********************************************************************/
static
int hse_yuyv2nv12_check_args(uint32_t width, uint32_t height,
			     uint32_t src_pitch, uint32_t dst_pitch)
{
	CHECK_ARGS(width & 0xf, "invalid width");
	CHECK_ARGS(height & 0xf, "invalid height");
	CHECK_ARGS((src_pitch & 0xf) || src_pitch < width, "invalid src_pitch");
	CHECK_ARGS((dst_pitch & 0xf) || dst_pitch < width/2,
		   "invalid dst_pitch");
	return 0;
}

static
int hse_yuyv2nv12(struct hse_engine *eng, struct hse_test_buf *dst0,
		  struct hse_test_buf *dst1, struct hse_test_buf *src,
		  uint32_t width, uint32_t height, uint32_t src_pitch,
		  uint32_t dst_pitch)
{
	uint32_t cmds[32];

	if (hse_yuyv2nv12_check_args(width, height, src_pitch, dst_pitch))
		return -EINVAL;

	cmds[0] = 0x2;
	cmds[1] = height | (width << 16);
	cmds[2] = dst_pitch | (src_pitch << 16);
	cmds[3] = dst0->phys;
	cmds[4] = dst1->phys;
	cmds[5] = src->phys;
	return hse_test_run_cmd(eng, cmds, 6);
}

static
int __memcmp_pitch(void *m0, void *m1, uint32_t width, uint32_t height,
		   uint32_t pitch)
{
	int h;
	int ret;

	for (h = 0; h < height; h++) {
		ret = memcmp(m0, m1, width);
		if (ret)
			return ret;
		m0 += pitch;
		m1 += pitch;
	}
	return 0;
}

static
int hse_yuyv2nv12_verify_result(struct hse_test_obj *hobj,
				struct hse_test_buf *dst0,
				struct hse_test_buf *dst1,
				struct hse_test_buf *src,
				uint32_t width, uint32_t height,
				uint32_t src_pitch, uint32_t dst_pitch)
{
	u8 *p0, *p1;
	int ret = 0;
	uint32_t size = height * dst_pitch;

	p0 = kzalloc(size, GFP_KERNEL);
	p1 = kzalloc(size, GFP_KERNEL);
	if (!p0 || !p1) {
		ret = -ENOMEM;
		goto done;
	}
	memset(p0, HSE_TEST_INVAL, size);
	memset(p1, HSE_TEST_INVAL, size);

	__hse_sw_yuyv2nv12(p0, p1, src->virt, width, height, src_pitch, dst_pitch);

	ret = __memcmp_pitch(dst0->virt, p0, width / 2, height, dst_pitch);
	ret |= __memcmp_pitch(dst1->virt, p1, width / 2, height, dst_pitch);
	if (!ret)
		goto done;

	ret = -EINVAL;
	hse_test_obj_create_blob_file(hobj, "info", hobj->test_info, hobj->test_info_size);
	hse_test_obj_create_blob_file(hobj, "src", src->virt, size);
	hse_test_obj_create_blob_file(hobj, "dst0", dst0->virt, size);
	hse_test_obj_create_blob_file(hobj, "dst1", dst1->virt, size);
	hse_test_obj_create_blob_file(hobj, "sw0", p0, size);
	hse_test_obj_create_blob_file(hobj, "sw1", p1, size);
done:
	kfree(p0);
	kfree(p1);
	return ret;
}

/*********************************************************************
 *
 * rotate
 *
 *********************************************************************/
static
int hse_rotate_check_args(uint32_t mode, uint32_t width, uint32_t height,
			  uint32_t src_pitch, uint32_t dst_pitch)
{
	CHECK_ARGS(mode != HSE_ROTATE_MODE_90 && mode != HSE_ROTATE_MODE_180 &&
		   mode != HSE_ROTATE_MODE_270, "invalid mode");
	CHECK_ARGS(width & 0xf, "invalid width");
	CHECK_ARGS(height & 0xf, "invalid height");
	CHECK_ARGS(src_pitch & 0xf, "invalid src_pitch");
	CHECK_ARGS(dst_pitch & 0xf, "invalid dst_pitch");
	CHECK_ARGS(src_pitch < width, "invalid src_pitch");
	CHECK_ARGS(mode != HSE_ROTATE_MODE_180 && dst_pitch < height,
		   "invalid mode and dst_pitch");
	CHECK_ARGS(mode == HSE_ROTATE_MODE_180 && dst_pitch < width,
		   "invalid mode and dst_pitch");
	return 0;
}

static
int hse_rotate(struct hse_engine *eng, struct hse_test_buf *dst,
	       struct hse_test_buf *src, uint32_t mode, uint32_t width,
	       uint32_t height, uint32_t src_pitch, uint32_t dst_pitch)
{
	uint32_t cmds[32];

	if (hse_rotate_check_args(mode, width, height, src_pitch, dst_pitch))
		return -EINVAL;

	cmds[0] = 0x05 | (mode << 29);
	cmds[1] = height | (width << 16);
	cmds[2] = dst_pitch | (src_pitch << 16);
	cmds[3] = dst->phys;
	cmds[4] = src->phys;
	return hse_test_run_cmd(eng, cmds, 5);
}

static
int hse_rotate_verify_result(struct hse_test_obj *hobj,
			     struct hse_test_buf *dst, struct hse_test_buf *src,
			     uint32_t mode, uint32_t width, uint32_t height,
			     uint32_t src_pitch, uint32_t dst_pitch)
{
	int ret;
	int size = dst_pitch * (mode == HSE_ROTATE_MODE_180 ? height : width);
	u8 *p;

	/* emulation */
	p = kzalloc(size, GFP_KERNEL);
	if (!p)
		return -ENOMEM;
	memset(p, HSE_TEST_INVAL, size);

	__hse_sw_rotate(src->virt, p, mode, width, height, src_pitch, dst_pitch);

	/* compare */
	ret = memcmp(dst->virt, p, size);
	if (!ret)
		goto done;

	ret = -EINVAL;
	hse_test_obj_create_blob_file(hobj, "info", hobj->test_info, hobj->test_info_size);
	hse_test_obj_create_blob_file(hobj, "src", src->virt, size);
	hse_test_obj_create_blob_file(hobj, "dst", dst->virt, size);
done:
	kfree(p);
	return ret;
}

/*********************************************************************
 *
 * test
 *
 *********************************************************************/
static void hse_test_engine_xor(struct hse_test_obj *hobj)
{
	struct hse_engine *eng = hobj->eng;
	struct hse_test_buf *bufs = hobj->bufs;
	int ret;
	int i;

	/* prepare data for copy and xor */
	hse_test_buf_memset(&bufs[1], 0x01, HSE_TEST_MEM_SIZE, 1);
	hse_test_buf_memset(&bufs[2], 0x02, HSE_TEST_MEM_SIZE, 1);
	hse_test_buf_memset(&bufs[3], 0x06, HSE_TEST_MEM_SIZE, 1);
	hse_test_buf_memset(&bufs[4], 0x18, HSE_TEST_MEM_SIZE, 1);
	hse_test_buf_memset(&bufs[5], 0x30, HSE_TEST_MEM_SIZE, 1);

	/* copy */
	hse_test_buf_memset(&bufs[0], HSE_TEST_INVAL, HSE_TEST_MEM_SIZE, 1);

	TEST_BEGIN(hobj, "op=copy, size=%u\n", (uint32_t)HSE_TEST_MEM_SIZE);
	ret = hse_copy(eng, &bufs[0], &bufs[1], HSE_TEST_MEM_SIZE);
	if (!ret)
		ret = hse_copy_verify_result(hobj, &bufs[0], &bufs[1], HSE_TEST_MEM_SIZE);
	TEST_END(hobj, ret);

	/* xor */
	for (i = 2; i <= 5; i++) {
		uint32_t xor_num;

		hse_test_buf_memset(&bufs[0], HSE_TEST_INVAL, HSE_TEST_MEM_SIZE, 1);

		xor_num = i;
		TEST_BEGIN(hobj, "op=xor, size=%u, num=%u\n", (uint32_t)HSE_TEST_MEM_SIZE, xor_num);
		ret = hse_xor(eng, &bufs[0], &bufs[1], xor_num, HSE_TEST_MEM_SIZE);
		if (!ret)
			ret = hse_xor_verify_result(hobj, &bufs[0], &bufs[1], xor_num, HSE_TEST_MEM_SIZE);
		TEST_END(hobj, ret);
	}
}

struct hse_yuyv2nv12_args {
	uint32_t w;
	uint32_t h;
	uint32_t sp;
	uint32_t dp;
};

__maybe_unused
static void hse_test_engine_yuy2(struct hse_test_obj *hobj)
{
	struct hse_engine *eng = hobj->eng;
	struct hse_test_buf *bufs = hobj->bufs;
	struct hse_yuyv2nv12_args cases[] = {
		{ 32, 32, 32, 16, },
		{ 32, 32, 32, 32, },
		{ 32, 32, 64, 16, },
		{ 32, 32, 64, 32, },
	};
	int ret;
	int i;

	/* prepare data for yuyv2nv12 */
	for (i = 0; i < HSE_TEST_MEM_SIZE; i++)
		((u8 *)bufs[0].virt)[i] = i;
	hse_flush_dcache_area(bufs[0].virt, HSE_TEST_MEM_SIZE);

	/* yuy2 to nv */
	for (i = 0; i < ARRAY_SIZE(cases); i++) {
		uint32_t w = cases[i].w;
		uint32_t h = cases[i].h;
		uint32_t sp = cases[i].sp;
		uint32_t dp = cases[i].dp;

		hse_test_buf_memset(&bufs[1], HSE_TEST_INVAL, HSE_TEST_MEM_SIZE, 1);
		hse_test_buf_memset(&bufs[2], HSE_TEST_INVAL, HSE_TEST_MEM_SIZE, 1);

		TEST_BEGIN(hobj, "op=yuyv2nv12, w=%u h=%u sp=%u dp=%u\n", w, h, sp, dp);
		ret = hse_yuyv2nv12(eng, &bufs[1], &bufs[2], &bufs[0], w, h, sp, dp);
		if (!ret)
			ret = hse_yuyv2nv12_verify_result(hobj, &bufs[1], &bufs[2], &bufs[0], w, h, sp, dp);
		TEST_END(hobj, ret);

	}
}

struct hse_rotate_args {
	uint32_t m;
	uint32_t w;
	uint32_t h;
	uint32_t sp;
	uint32_t dp;
	uint32_t inv;
};

__maybe_unused
static void hse_test_engine_rotate(struct hse_test_obj *hobj)
{

	struct hse_engine *eng = hobj->eng;
	struct hse_test_buf *bufs = hobj->bufs;
	struct hse_rotate_args cases[] = {
		{ HSE_ROTATE_MODE_90,  16,  16,  16,  16, 0, },
		{ HSE_ROTATE_MODE_90,  64,  32,  64,  32, 0, },
		{ HSE_ROTATE_MODE_90, 128,  32, 128,  64, 0, },
		{ HSE_ROTATE_MODE_90,  64,  64,  64,  64, 0, },
		{ HSE_ROTATE_MODE_90,  64,  64,  64, 128, 0, },
		{ HSE_ROTATE_MODE_90,  64,  64, 128,  64, 0, },
		{ HSE_ROTATE_MODE_90,  64,  64, 128,  64, 0, },
		{ HSE_ROTATE_MODE_90,  64,  64, 128, 128, 0, },
		{ HSE_ROTATE_MODE_180, 64,  64,  64,  64, 0, },
		{ HSE_ROTATE_MODE_180, 64,  64,  64, 128, 0, },
		{ HSE_ROTATE_MODE_180, 64,  64, 128,  64, 0, },
		{ HSE_ROTATE_MODE_180, 64,  64, 128, 128, 0, },
		{ HSE_ROTATE_MODE_270, 64,  64,  64,  64, 0, },
		{ HSE_ROTATE_MODE_270, 64,  64,  64, 128, 0, },
		{ HSE_ROTATE_MODE_270, 64,  64, 128,  64, 0, },
		{ HSE_ROTATE_MODE_270, 64,  64, 128, 128, 0, },
		{ HSE_ROTATE_MODE_90,  32, 128,  32,  64, 1, },
		{ HSE_ROTATE_MODE_90,  33, 128,  32,  64, 1, },
		{ 4,  33, 128,  32,  64, 1, },
	};
	int ret;
	int i;

	/* prepare data for rotate */
	for (i = 0; i < HSE_TEST_MEM_SIZE; i++)
		((u8 *)bufs[0].virt)[i] = i;
	hse_flush_dcache_area(bufs[0].virt, HSE_TEST_MEM_SIZE);

	/* rotate */
	for (i = 0 ; i < ARRAY_SIZE(cases); i++) {
		uint32_t m = cases[i].m;
		uint32_t w = cases[i].w;
		uint32_t h = cases[i].h;
		uint32_t sp = cases[i].sp;
		uint32_t dp = cases[i].dp;

		hse_test_buf_memset(&bufs[1], HSE_TEST_INVAL, HSE_TEST_MEM_SIZE, 1);

		TEST_BEGIN(hobj, "op=rotate, m=%u, w=%u h=%u sp=%u dp=%u\n", m, w, h, sp, dp);
		ret = hse_rotate(eng, &bufs[1], &bufs[0], m, w, h, sp, dp);
		if (!ret)
			ret = hse_rotate_verify_result(hobj, &bufs[1], &bufs[0], m, w, h, sp, dp);
		if (cases[i].inv) {
			if (ret)
				ret = 0;
			else
				ret = -EINVAL;
		}
		TEST_END(hobj, ret);
	}
}

static void hse_test_trigger_hw_reset(struct hse_engine *eng)
{
	pr_err("\n");
	pr_err("%s\n", __func__);
	reset_control_reset(eng->hdev->rstc);
}

#define HSE_TEST_FLAGS_RESET_BEFORE_ROTATE   BIT(0)
#define HSE_TEST_FLAGS_RESET_AFTER_ROTATE    BIT(1)

static int hse_test_engine(struct hse_engine *eng)
{
	int ret = 0;
	struct hse_test_obj *hobj;
	uint32_t test_flags = 0;

#ifdef CONFIG_ARCH_RTD16xx
	if (get_rtd_chip_revision() == RTD_CHIP_A00)
		test_flags |= HSE_TEST_FLAGS_RESET_BEFORE_ROTATE |
			      HSE_TEST_FLAGS_RESET_AFTER_ROTATE;
#elif defined(CONFIG_ARCH_RTD13xx)
	test_flags |= HSE_TEST_FLAGS_RESET_AFTER_ROTATE;
#endif

	pr_err("test engine@%03x\n", eng->base_offset);

	hobj = hse_test_obj_alloc(eng);
	if (!hobj)
		return -ENOMEM;

	hse_test_engine_xor(hobj);

#ifdef CONFIG_RTK_HSE_HAS_YUY2
	hse_test_engine_yuy2(hobj);
#endif

#ifdef CONFIG_RTK_HSE_HAS_ROTATE

	if (test_flags & HSE_TEST_FLAGS_RESET_BEFORE_ROTATE)
		hse_test_trigger_hw_reset(eng);

	hse_test_engine_rotate(hobj);

	if (test_flags & HSE_TEST_FLAGS_RESET_AFTER_ROTATE)
		hse_test_trigger_hw_reset(eng);

	hse_test_engine_xor(hobj);
#endif

	pr_err("\n");
	pr_err("### result ###\n");
	pr_err("### passed: %d, failed: %d, total: %d ###\n",
		hobj->pass, hobj->fail, hobj->total);
	pr_err("\n");

	hse_test_obj_free(hobj);
	return ret;
}

int hse_self_test(struct hse_device *hdev)
{
	struct hse_engine *engs[HSE_MAX_ENGINES] = {0};
	int i;

	hse_test_init_debugfs();

	pm_runtime_get_sync(hdev->dev);
	for (i = 0; i < HSE_MAX_ENGINES; i++) {
		engs[i] = hse_engine_get_any(hdev);
		if (!engs[i])
			break;
	}

	for (i = 0; i < HSE_MAX_ENGINES; i++)
		if (engs[i]) {
			hse_test_engine(engs[i]);
		}

	for (i = 0; i < HSE_MAX_ENGINES; i++)
		if (engs[i])
			hse_engine_put(engs[i]);
        pm_runtime_put_sync(hdev->dev);
	return 0;
}
