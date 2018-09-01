#ifndef __RTK_GEM_ION_HELPER_H__
#define __RTK_GEM_ION_HELPER_H__

#include <drm/drmP.h>
#include <drm/drm_gem.h>

#include "rtk_drm.h"
#include "../../../staging/android/ion/ion.h"
#include "../../../staging/android/uapi/ion_rtk.h"

enum {
    eRTK_BOT_BUFFER_NONCACHED,
    eRTK_BOT_BUFFER_SCPUACC,
    eRTK_BOT_BUFFER_ACPUACC,
    eRTK_BOT_BUFFER_HWIPACC,
    eRTK_BOT_BUFFER_VE_SPEC,
    eRTK_BOT_BUFFER_ALGO_LAST_FIT,
    eRTK_BOT_BUFFER_PROTECTED,
    eRTK_BOT_BUFFER_SECURE_AUDIO,
    eRTK_BOT_BUFFER_HEAP_MEDIA,
    eRTK_BOT_BUFFER_HEAP_AUDIO,
    eRTK_BOT_BUFFER_HEAP_SYSTEM,
    eRTK_BOT_BUFFER_HEAP_DMA,
    eRTK_BOT_BUFFER_HEAP_SECURE,
    eRTK_BOT_MAX_DEFINED,
};

#define RTK_BOT_BUFFER_NONCACHED            (0x1 << eRTK_BOT_BUFFER_NONCACHED           )
#define RTK_BOT_BUFFER_SCPUACC              (0x1 << eRTK_BOT_BUFFER_SCPUACC             )
#define RTK_BOT_BUFFER_ACPUACC              (0x1 << eRTK_BOT_BUFFER_ACPUACC             )
#define RTK_BOT_BUFFER_HWIPACC              (0x1 << eRTK_BOT_BUFFER_HWIPACC             )
#define RTK_BOT_BUFFER_VE_SPEC              (0x1 << eRTK_BOT_BUFFER_VE_SPEC             )
#define RTK_BOT_BUFFER_ALGO_LAST_FIT        (0x1 << eRTK_BOT_BUFFER_ALGO_LAST_FIT       )
#define RTK_BOT_BUFFER_PROTECTED            (0x1 << eRTK_BOT_BUFFER_PROTECTED           )
#define RTK_BOT_BUFFER_SECURE_AUDIO         (0x1 << eRTK_BOT_BUFFER_SECURE_AUDIO        )
#define RTK_BOT_BUFFER_HEAP_MEDIA           (0x1 << eRTK_BOT_BUFFER_HEAP_MEDIA          )
#define RTK_BOT_BUFFER_HEAP_AUDIO           (0x1 << eRTK_BOT_BUFFER_HEAP_AUDIO          )
#define RTK_BOT_BUFFER_HEAP_SYSTEM          (0x1 << eRTK_BOT_BUFFER_HEAP_SYSTEM         )
#define RTK_BOT_BUFFER_HEAP_DMA             (0x1 << eRTK_BOT_BUFFER_HEAP_DMA            )
#define RTK_BOT_BUFFER_HEAP_SECURE          (0x1 << eRTK_BOT_BUFFER_HEAP_SECURE         )
#define RTK_BOT_MASK                        ((0x1 << eRTK_BOT_MAX_DEFINED) -1           )

struct rtk_gem_ion_object {
    struct drm_gem_object   base;
    struct ion_handle *     handle;
    dma_addr_t              paddr;
    struct sg_table *       sgt;
    void *                  vaddr;
};

static inline struct rtk_gem_ion_object * to_rtk_gem_ion_obj(struct drm_gem_object *gem_obj)
{
    return container_of(gem_obj, struct rtk_gem_ion_object, base);
}

void rtk_gem_ion_free_object(struct drm_gem_object *gem_obj);

int rtk_gem_ion_dumb_create_internal(struct drm_file *file_priv,
        struct drm_device *drm,
        struct drm_mode_create_dumb *args);

int rtk_gem_ion_dumb_create(struct drm_file *file_priv,
        struct drm_device *drm,
        struct drm_mode_create_dumb *args);

int rtk_gem_ion_dumb_map_offset(struct drm_file *file_priv,
        struct drm_device *drm, u32 handle,
        u64 *offset);

int rtk_gem_ion_mmap(struct file *filp, struct vm_area_struct *vma);

struct rtk_gem_ion_object *rtk_gem_ion_create(struct drm_device *drm, size_t size, unsigned int flags);

extern const struct vm_operations_struct rtk_gem_ion_vm_ops;

struct sg_table *rtk_gem_ion_prime_get_sg_table(struct drm_gem_object *obj);

struct drm_gem_object * rtk_gem_ion_prime_import_sg_table(struct drm_device *dev,
        struct dma_buf_attachment *attach,
        struct sg_table *sgt);

int rtk_gem_ion_prime_mmap(struct drm_gem_object *obj,
        struct vm_area_struct *vma);

void *rtk_gem_ion_prime_vmap(struct drm_gem_object *obj);

void rtk_gem_ion_prime_vunmap(struct drm_gem_object *obj, void *vaddr);

int rtk_gem_ion_device_init(struct drm_device *drm);

void rtk_gem_ion_device_deinit(struct drm_device *drm);

int rtk_gem_create_ioctl(struct drm_device *dev, void *data, struct drm_file *file_priv);
#endif /* __RTK_GEM_ION_HELPER_H__ */
