#include <linux/version.h>
#include <linux/err.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/dma-contiguous.h>

#if LINUX_VERSION_CODE > KERNEL_VERSION(3, 10, 9)
#include "../../drivers/staging/android/ion/ion.h"
#include "../../drivers/staging/android/uapi/ion.h"
#include "../../drivers/staging/android/ion/ion_priv.h"
#include "../../drivers/staging/android/ion/realtek/ion_rtk_carveout_heap.h"
#include "../../drivers/staging/android/uapi/ion_rtk.h"
#else
#include <linux/ion.h>
#include "../../drivers/gpu/ion/ion_priv.h"
#endif

#include "include/debug.h"
#include "soc/realtek/memory.h"
#include "../../../../mm/cma.h"

struct ion_device *rtk_phoenix_ion_device;
EXPORT_SYMBOL(rtk_phoenix_ion_device);

static int num_heaps;
static struct ion_heap **heaps;

struct ion_heap_desc {
	unsigned int id;
	enum ion_heap_type type;
	const char *name;
	unsigned int permission_type;
};

enum ion_heap_ids {
	INVALID_HEAP_ID = -1,
	ION_HEAP_TYPE_SYSTEM_ID = 0,
	ION_HEAP_TYPE_SYSTEM_CONTIG_ID = 1,
	ION_HEAP_TYPE_CARVEOUT_ID = 2,
	ION_HEAP_TYPE_CHUNK_ID = 3,
	ION_HEAP_TYPE_DMA_ID = 4,
	ION_HEAP_TYPE_CUSTOM_ID = 5,
	RTK_PHOENIX_ION_HEAP_TYPE_TILER_ID = 6,
	RTK_PHOENIX_ION_HEAP_TYPE_MEDIA_ID = 7,
	RTK_PHOENIX_ION_HEAP_TYPE_AUDIO_ID = 8,
	RTK_PHOENIX_ION_HEAP_TYPE_SECURE_ID = 9,
	ION_CP_MM_HEAP_ID = 4,
	ION_RPC_HEAP_ID	 = 15,
	ION_AUDIO_HEAP_ID = 16,
	ION_MM_HEAP_ID	 = 29,
	ION_SYSTEM_HEAP_ID = 30,
	/* bit reserved for secure flag */
	ION_HEAP_ID_RESERVED = 31
};

#define ION_VMALLOC_HEAP_NAME "vmalloc"
#define ION_RPC_HEAP_NAME "rpc"
#define ION_AUDIO_HEAP_NAME "audio"
#define ION_MM_HEAP_NAME "multimedia"

static struct ion_heap_desc ion_heap_meta[] = {
	{
		.type = ION_HEAP_TYPE_SYSTEM,
		.name = "System",
		.id = ION_HEAP_TYPE_SYSTEM_ID,
	},
	{
		.type = ION_HEAP_TYPE_SYSTEM_CONTIG,
		.name = "SystemContig",
		.id = ION_HEAP_TYPE_SYSTEM_CONTIG_ID,
	},
	{
		.type = RTK_PHOENIX_ION_HEAP_TYPE_TILER,
		.id = RTK_PHOENIX_ION_HEAP_TYPE_TILER_ID,
		.name = "NativeWindow",
	},
	{
		.type = RTK_PHOENIX_ION_HEAP_TYPE_MEDIA,
		.id = RTK_PHOENIX_ION_HEAP_TYPE_MEDIA_ID,
		.name = "Media",
	},
	{
		.type = RTK_PHOENIX_ION_HEAP_TYPE_AUDIO,
		.id = RTK_PHOENIX_ION_HEAP_TYPE_AUDIO_ID,
		.name = "Audio",
	},
	{
		.type = RTK_PHOENIX_ION_HEAP_TYPE_SECURE,
		.id = RTK_PHOENIX_ION_HEAP_TYPE_SECURE_ID,
		.name = "Secure",
	},
	{
		.type = ION_HEAP_TYPE_DMA,
		.id = ION_HEAP_TYPE_DMA_ID,
		.name = "DMA",
	},
	/*
		{
			.id = ION_SYSTEM_HEAP_ID,
			.type	= ION_HEAP_TYPE_SYSTEM,
			.name = ION_VMALLOC_HEAP_NAME,
		},
	*/
	{
		.id = ION_RPC_HEAP_ID,
		.type	= ION_HEAP_TYPE_DMA,
		.name = ION_RPC_HEAP_NAME,
	},
	{
		.id = ION_AUDIO_HEAP_ID,
		.type	= ION_HEAP_TYPE_DMA,
		.name = ION_AUDIO_HEAP_NAME,
	},
	{
		.id = ION_MM_HEAP_ID,
		.type	= ION_HEAP_TYPE_DMA,
		.name = ION_MM_HEAP_NAME,
	},
};

static int rtk_ion_populate_heap(struct ion_platform_heap *heap)
{
	unsigned int i;
	int ret = -EINVAL;
	unsigned int len = ARRAY_SIZE(ion_heap_meta);

	for (i = 0 ; i < len ; i++) {
		if (ion_heap_meta[i].id == heap->id) {
			heap->name = ion_heap_meta[i].name;
			heap->type = ion_heap_meta[i].type;
			ret = 0;
			break;
		}
	}
	if (ret)
		dbg_err("%s: unable to populate heap, error: %d", __func__, ret);

	return ret;
}

static struct ion_platform_data *rtk_ion_parse_dt(const struct device_node *dt_node)
{
	struct ion_platform_data *pdata = 0;
	struct ion_platform_heap *heap_data = 0;
	struct device_node *node;
	uint32_t val = 0;
	int ret = 0;
	uint32_t num_heaps = 0;

	for_each_child_of_node(dt_node, node)
	num_heaps++;
	if (!num_heaps)
		return ERR_PTR(-EINVAL);

	pdata = kzalloc(sizeof(struct ion_platform_data), GFP_KERNEL);
	if (!pdata)
		return ERR_PTR(-ENOMEM);

	pdata->nr = num_heaps;

	pdata->heaps = kcalloc(num_heaps, sizeof(struct ion_platform_heap), GFP_KERNEL);
	if (!pdata->heaps) {
		ret = -ENOMEM;
		goto free_pdata;
	}

	heap_data = pdata->heaps;
	for_each_child_of_node(dt_node, node) {
		ret = of_property_read_u32(node, "reg", &val);
		if (ret) {
			dbg_err("%s: unable to find reg key", __func__);
			goto free_heaps;
		}
		heap_data->id = val;
		ret = rtk_ion_populate_heap(heap_data);
		if (ret)
			goto free_heaps;

#if 0
		ret = of_property_read_u32(node, "rtk,memory-reserve-base", &val);
		heap_data->base = (!ret) ? val : 0;

		ret = of_property_read_u32(node, "rtk,memory-reservation-size", &val);
		heap_data->size = (!ret) ? val : 0;
#else
		heap_data->base = 0;
		heap_data->size = 0;
		heap_data->priv = NULL;

		{
#define COLUMN 3
			const u32 *prop;
			int err,size,i;
			struct list_head * pools = kzalloc(sizeof(struct list_head), GFP_KERNEL);

			INIT_LIST_HEAD(pools);
			prop = of_get_property(node, "rtk,memory-reserve", &size);
			err = size % (sizeof(u32) * COLUMN);
			if ((prop) && (!err)) {
				int counter = size / (sizeof(u32) * COLUMN);
				for (i=0; i<counter; i+=1) {
					struct ion_rtk_priv_pool * pool = kzalloc(sizeof(struct ion_rtk_priv_pool), GFP_KERNEL);
					pool->type  = RTK_CARVEOUT_GEN_POOL_TYPE;
					pool->base  = (ion_phys_addr_t)((u32)of_read_number(prop, 1 + (i*COLUMN)));
					pool->size  = (size_t)((u32)of_read_number(prop, 2 + (i*COLUMN)));
					pool->flags = (unsigned long)((u32)of_read_number(prop, 3 + (i*COLUMN)));
					list_add(&pool->list,pools);
				}
				heap_data->priv = (void *) pools;
			}
			if (heap_data->id == RTK_PHOENIX_ION_HEAP_TYPE_MEDIA_ID) {
				if( cma_area_count == 1 ) {
					struct ion_rtk_priv_pool * pool = kzalloc(sizeof(struct ion_rtk_priv_pool), GFP_KERNEL);
					pool->type  = RTK_CARVEOUT_CMA_POOL_TYPE;
					pool->cma_pool = dma_contiguous_default_area;
					pool->base  = cma_get_base(pool->cma_pool);
					pool->size  = cma_get_size(pool->cma_pool);
					pool->flags = RTK_FLAG_SCPUACC | RTK_FLAG_NONCACHED | RTK_FLAG_HWIPACC;
					list_add(&pool->list,pools);
				}
				else {
					for (i=0; i<(cma_area_count-1); i+=1) { // last cma is used as dma_contiguous_default_area
						struct ion_rtk_priv_pool * pool = kzalloc(sizeof(struct ion_rtk_priv_pool), GFP_KERNEL);
						pool->type  = RTK_CARVEOUT_CMA_POOL_TYPE;
						pool->cma_pool = &cma_areas[i];
						pool->base  = cma_get_base(pool->cma_pool);
						pool->size  = cma_get_size(pool->cma_pool);
						//pool->flags = RTK_FLAG_SCPUACC | RTK_FLAG_NONCACHED | RTK_FLAG_HWIPACC;
						pool->flags = RTK_FLAG_DEAULT; //(/*RTK_FLAG_NONCACHED | */RTK_FLAG_SCPUACC | RTK_FLAG_ACPUACC | RTK_FLAG_HWIPACC)
						list_add(&pool->list,pools);
					}
				}
			}
			if( heap_data->priv == NULL ) {
				heap_data->priv = (void *) pools;
			}
		}
#endif
		heap_data++;
	}
	return pdata;

free_heaps:
	kfree(pdata->heaps);
free_pdata:
	kfree(pdata);
	return ERR_PTR(ret);
}

static int rtk_ion_probe(struct platform_device *pdev)
{
	struct ion_platform_data *pdata;
	struct ion_platform_heap *heap_data;
	unsigned int pdata_needs_freed;
	int err = -1;
	int i;

	dbg_info("%s %s",__FILE__, __func__);
	if (pdev->dev.of_node) {
		pdata = rtk_ion_parse_dt(pdev->dev.of_node);
		if (IS_ERR(pdata)) {
			err = PTR_ERR(pdata);
			goto out;
		}
		pdata_needs_freed = 1;
	}
	else {
		pdata = pdev->dev.platform_data;
		pdata_needs_freed = 0;
	}

	num_heaps = pdata->nr;

	dbg_info("%s %s nr_heaps:%d",__FILE__, __func__, num_heaps);

	//heaps = kcalloc(pdata->nr, sizeof(struct ion_heap*), GFP_KERNEL);
	heaps = devm_kzalloc(&pdev->dev,
						 sizeof(struct ion_heap *) * pdata->nr,
						 GFP_KERNEL);
	if (!heaps) {
		err = -ENOMEM;
		goto out;
	}

	rtk_phoenix_ion_device = ion_device_create(rtk_phoenix_ion_ioctl);
	if (IS_ERR_OR_NULL(rtk_phoenix_ion_device)) {
		err = PTR_ERR(rtk_phoenix_ion_device);
		goto freeheaps;
	}
	/* create the heaps as specified in the board file */
	heap_data = pdata->heaps;
	for (i = 0; i < num_heaps; i++) {
#if 1
		if(heap_data->type == ION_HEAP_TYPE_DMA) {
			if (heap_data->priv) {
				struct list_head * pools = (struct list_head *) heap_data->priv;
				struct ion_rtk_priv_pool * pool, * tmp_pool;
				list_for_each_entry_safe(pool, tmp_pool,  pools, list) {
					list_del(&pool->list);
					kfree(pool);
				}
				kfree(pools);
			}
			heap_data->priv = NULL;
		} else if (heap_data->type == ION_HEAP_TYPE_CARVEOUT)
#else
		if ((heap_data->type == ION_HEAP_TYPE_CARVEOUT) ||
				(heap_data->type == ION_HEAP_TYPE_DMA) )
#endif
		{
			if (heap_data->priv) {
				struct list_head * pools = (struct list_head *) heap_data->priv;
				struct ion_rtk_priv_pool * pool;
				list_for_each_entry(pool, pools, list) {
					if (pool->base == 0 && pool->type == RTK_CARVEOUT_GEN_POOL_TYPE) {
						struct page *page = dma_alloc_from_contiguous(&(pdev->dev), pool->size >> PAGE_SHIFT, get_order(pool->size));
						pool->base = page_to_phys(page);
					}
				}

			}
		}

		heaps[i] = ion_heap_create(heap_data);

		if (IS_ERR_OR_NULL(heaps[i])) {
			heaps[i] = 0;
			continue;
		}

		ion_device_add_heap(rtk_phoenix_ion_device, heaps[i]);

		if (heap_data->priv) {
			struct list_head * pools = (struct list_head *) heap_data->priv;
			struct ion_rtk_priv_pool * pool, * tmp_pool;
			list_for_each_entry_safe(pool, tmp_pool,  pools, list) {

				dbg_info("%s: adding heap %s of type %d with %lx@%lx (type:%s)", __func__, heap_data->name,
						 heap_data->type, pool->base, pool->size,
						 (pool->type == RTK_CARVEOUT_GEN_POOL_TYPE)?"GEN_POOL":
						 (pool->type == RTK_CARVEOUT_CMA_POOL_TYPE)?"CMA_POOL":"Unknown");

				list_del(&pool->list);
				kfree(pool);
			}
			kfree(pools);
		}
		heap_data++;
	}

	if (pdata_needs_freed) {
		kfree(pdata->heaps);
		kfree(pdata);
	}

	platform_set_drvdata(pdev, rtk_phoenix_ion_device);
	return 0;

freeheaps:
	kfree(heaps);
out:
	return err;
}

static int rtk_ion_remove(struct platform_device *pdev)
{
	struct ion_device *rtk_phoenix_ion_device = platform_get_drvdata(pdev);
	int i;

	for (i = 0; i < num_heaps; i++)
		ion_heap_destroy(heaps[i]);

	ion_device_destroy(rtk_phoenix_ion_device);
	kfree(heaps);
	return 0;
}

static struct of_device_id rtk_ion_ids[] = {
	{ .compatible = "Realtek,rtk-ion" },
	{ /* Sentinel */ },
};

static struct platform_driver rtk_ion_driver = {
	.probe = rtk_ion_probe,
	.remove = rtk_ion_remove,
	.driver = {
		.name = "ion-rtk",
		.of_match_table = rtk_ion_ids,
	},
};

#if 1
static int __init rtk_ion_init(void)
{
	return platform_driver_register(&rtk_ion_driver);
}

static void __exit rtk_ion_exit(void)
{
	platform_driver_unregister(&rtk_ion_driver);
}

fs_initcall(rtk_ion_init);
module_exit(rtk_ion_exit);
#else
module_platform_driver(rtk_ion_driver);
#endif

