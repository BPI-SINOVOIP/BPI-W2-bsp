#ifndef _LINUX_ION_RTK_CARVEOUT_HEAP_H
#define _LINUX_ION_RTK_CARVEOUT_HEAP_H

#include "../ion.h"
#include "../ion_priv.h"
#include "../../uapi/ion_rtk.h"
#include "soc/realtek/memory.h"

enum ion_rtk_carveout_pool_type {
    RTK_CARVEOUT_GEN_POOL_TYPE = 0,
    RTK_CARVEOUT_CMA_POOL_TYPE,
};

struct ion_rtk_priv_pool {
    enum ion_rtk_carveout_pool_type type;
    ion_phys_addr_t base;
    struct cma * cma_pool;
    size_t size;
    unsigned long flags;
    struct list_head list;
};

struct ion_rtk_carveout_meminfo {
    unsigned long usedSize;
    unsigned long freeSize;
};

struct ion_rtk_carveout_ops {
    unsigned int (*getVersion) (struct ion_heap * heap);
    int          (*getMemInfo) (struct ion_heap * heap, unsigned int flags, struct ion_rtk_carveout_meminfo * info);
};

struct ion_heap *   ion_rtk_carveout_heap_create    (struct ion_platform_heap *);
void                ion_rtk_carveout_heap_destroy   (struct ion_heap *);

struct ion_rtk_carveout_ops * get_rtk_carveout_ops  (struct ion_heap * heap);

#endif /* End of _LINUX_ION_RTK_CARVEOUT_HEAP_H */
