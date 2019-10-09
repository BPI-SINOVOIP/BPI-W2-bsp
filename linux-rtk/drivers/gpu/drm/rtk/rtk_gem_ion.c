#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/export.h>
#include <linux/dma-buf.h>
#include <linux/dma-mapping.h>

#include <drm/drmP.h>
#include <drm/drm.h>
#include "rtk_gem_ion.h"
#include <drm/drm_vma_manager.h>

extern struct ion_device *rtk_phoenix_ion_device;

static struct ion_client * rtk_gem_ion_client = NULL;

static struct ion_client * rtk_gem_ion_get_client(void)
{
    if (rtk_gem_ion_client == NULL)
        rtk_gem_ion_client = ion_client_create(rtk_phoenix_ion_device, "rtk_gem_ion");
    return rtk_gem_ion_client;
}

int rtk_gem_ion_device_init(struct drm_device *drm)
{
    if (IS_ERR(rtk_gem_ion_get_client()))
        return (-ENOMEM);
    return 0;
}

void rtk_gem_ion_device_deinit(struct drm_device *drm)
{
    if (rtk_gem_ion_client != NULL) {
        ion_client_destroy(rtk_gem_ion_client);
        rtk_gem_ion_client = NULL;
    }
}

static inline unsigned int rtk_ion_flags(unsigned int dumb_flags)
{
    unsigned int ret = 0;
    if (dumb_flags & RTK_BOT_BUFFER_NONCACHED     ) ret |= ION_FLAG_NONCACHED;
    if (dumb_flags & RTK_BOT_BUFFER_SCPUACC       ) ret |= ION_FLAG_SCPUACC;
    if (dumb_flags & RTK_BOT_BUFFER_ACPUACC       ) ret |= ION_FLAG_ACPUACC;
    if (dumb_flags & RTK_BOT_BUFFER_HWIPACC       ) ret |= ION_FLAG_HWIPACC;
    if (dumb_flags & RTK_BOT_BUFFER_VE_SPEC       ) ret |= ION_FLAG_VE_SPEC;
    if (dumb_flags & RTK_BOT_BUFFER_ALGO_LAST_FIT ) ret |= ION_USAGE_ALGO_LAST_FIT;
    if (dumb_flags & RTK_BOT_BUFFER_PROTECTED     ) ret |= ION_USAGE_PROTECTED;
    if (dumb_flags & RTK_BOT_BUFFER_SECURE_AUDIO  ) ret |= ION_FLAG_SECURE_AUDIO;

    if (ret == 0)
        ret |= ION_FLAG_NONCACHED | ION_FLAG_SCPUACC | ION_FLAG_HWIPACC;
    return ret;
}

static inline unsigned int rtk_ion_heaps(unsigned int dumb_flags)
{
    unsigned int ret = 0;
    if (dumb_flags & RTK_BOT_BUFFER_HEAP_MEDIA    ) ret |= RTK_PHOENIX_ION_HEAP_MEDIA_MASK;
    if (dumb_flags & RTK_BOT_BUFFER_HEAP_AUDIO    ) ret |= RTK_PHOENIX_ION_HEAP_AUDIO_MASK;
    if (dumb_flags & RTK_BOT_BUFFER_HEAP_SYSTEM   ) ret |= ION_HEAP_SYSTEM_MASK;
    if (dumb_flags & RTK_BOT_BUFFER_HEAP_DMA      ) ret |= ION_HEAP_TYPE_DMA_MASK;
    if (dumb_flags & RTK_BOT_BUFFER_HEAP_SECURE   ) ret |= RTK_PHOENIX_ION_HEAP_SECURE_MASK;

    if (ret == 0)
        ret |= RTK_PHOENIX_ION_HEAP_MEDIA_MASK;
    return ret;
}



static struct rtk_gem_ion_object * __rtk_gem_ion_create(struct drm_device *drm, size_t size)
{
    struct rtk_gem_ion_object *ion_obj;
    struct drm_gem_object *gem_obj;
    int ret;

    ion_obj = kzalloc(sizeof(*ion_obj), GFP_KERNEL);
    if (!ion_obj)
        return ERR_PTR(-ENOMEM);

    gem_obj = &ion_obj->base;

    ret = drm_gem_object_init(drm, gem_obj, size);
    if (ret)
        goto error;

    ret = drm_gem_create_mmap_offset(gem_obj);
    if (ret) {
        drm_gem_object_release(gem_obj);
        goto error;
    }

    return ion_obj;

error:
    kfree(ion_obj);
    return ERR_PTR(ret);
}

struct rtk_gem_ion_object *rtk_gem_ion_create(struct drm_device *drm, size_t size, unsigned int flags)
{
    struct rtk_gem_ion_object *ion_obj;

    size = round_up(size, PAGE_SIZE);

    DRM_DEBUG_KMS("[%s:%d] size = %zu, flags = 0x%x\n", __func__, __LINE__,
            size, flags);

    ion_obj = __rtk_gem_ion_create(drm, size);
    if (IS_ERR(ion_obj))
        return ion_obj;


    ion_obj->handle = ion_alloc(rtk_gem_ion_get_client(), size, 0, rtk_ion_heaps(flags), rtk_ion_flags(flags));

    if (IS_ERR(ion_obj->handle))
        goto error;

    ion_obj->vaddr = ion_map_kernel(rtk_gem_ion_get_client(), ion_obj->handle);
    {
        ion_phys_addr_t addr;
        size_t len;
        if (ion_phys(rtk_gem_ion_get_client(), ion_obj->handle, &addr, &len) == 0)
            ion_obj->paddr = addr;
    }

    return ion_obj;

error:
    rtk_gem_ion_free_object(&ion_obj->base);
    return ERR_PTR(-ENOMEM);
}

static struct rtk_gem_ion_object * rtk_gem_ion_create_with_handle(struct drm_file *file_priv,
        struct drm_device *drm, size_t size, unsigned int flags,
        uint32_t *handle)
{
    struct rtk_gem_ion_object *ion_obj;
    struct drm_gem_object *gem_obj;
    int ret;

    ion_obj = rtk_gem_ion_create(drm, size, flags);
    if (IS_ERR(ion_obj))
        return ion_obj;

    gem_obj = &ion_obj->base;

    ret = drm_gem_handle_create(file_priv, gem_obj, handle);
    if (ret)
        goto err_handle_create;

    /* drop reference from allocate - handle holds it now. */
    drm_gem_object_unreference_unlocked(gem_obj);

    return ion_obj;

err_handle_create:
    rtk_gem_ion_free_object(gem_obj);

    return ERR_PTR(ret);
}

void rtk_gem_ion_free_object(struct drm_gem_object *gem_obj)
{
    struct rtk_gem_ion_object *ion_obj;

    ion_obj = to_rtk_gem_ion_obj(gem_obj);

    if (ion_obj->handle) {
        ion_free(rtk_gem_ion_get_client(), ion_obj->handle);
    } else if (gem_obj->import_attach) {
        drm_prime_gem_destroy(gem_obj, ion_obj->sgt);
    }

    drm_gem_object_release(gem_obj);

    kfree(ion_obj);
}

int rtk_gem_ion_dumb_create_internal(struct drm_file *file_priv,
        struct drm_device *drm,
        struct drm_mode_create_dumb *args)
{
    unsigned int min_pitch = DIV_ROUND_UP(args->width * args->bpp, 8);
    struct rtk_gem_ion_object *ion_obj;

    //if (args->pitch < min_pitch)
    args->pitch = min_pitch;

    if (args->size < args->pitch * args->height)
        args->size = args->pitch * args->height;

    ion_obj = rtk_gem_ion_create_with_handle(file_priv, drm, args->size, args->flags,
            &args->handle);
    return PTR_ERR_OR_ZERO(ion_obj);
}

int rtk_gem_ion_dumb_create(struct drm_file *file_priv,
        struct drm_device *drm,
        struct drm_mode_create_dumb *args)
{
    struct rtk_gem_ion_object *ion_obj;

    args->pitch = DIV_ROUND_UP(args->width * args->bpp, 8);
    args->size = args->pitch * args->height;

    DRM_DEBUG_KMS("DRM %s on [ %d x %d, bpp=%d, flags=0x%x]\n", __func__,
            args->width, args->height, args->bpp, args->flags);

    ion_obj = rtk_gem_ion_create_with_handle(file_priv, drm, args->size, args->flags,
            &args->handle);
    return PTR_ERR_OR_ZERO(ion_obj);
}

int rtk_gem_ion_dumb_map_offset(struct drm_file *file_priv,
        struct drm_device *drm, u32 handle,
        u64 *offset)
{
    struct drm_gem_object *gem_obj;

    mutex_lock(&drm->struct_mutex);

    gem_obj = drm_gem_object_lookup(file_priv, handle);
    if (!gem_obj) {
        dev_err(drm->dev, "failed to lookup GEM object\n");
        mutex_unlock(&drm->struct_mutex);
        return -EINVAL;
    }

    *offset = drm_vma_node_offset_addr(&gem_obj->vma_node);

    drm_gem_object_unreference(gem_obj);

    mutex_unlock(&drm->struct_mutex);

    return 0;
}

const struct vm_operations_struct rtk_gem_ion_vm_ops = {
    .open = drm_gem_vm_open,
    .close = drm_gem_vm_close,
};

static int rtk_gem_ion_mmap_obj(struct rtk_gem_ion_object *ion_obj,
        struct vm_area_struct *vma)
{
    /*
     * Clear the VM_PFNMAP flag that was set by drm_gem_mmap(), and set the
     * vm_pgoff (used as a fake buffer offset by DRM) to 0 as we want to map
     * the whole buffer.
     */
    vma->vm_flags &= ~VM_PFNMAP;
    vma->vm_pgoff = 0;
    return ion_mmap_by_handle(ion_obj->handle, vma);
}

int rtk_gem_ion_mmap(struct file *filp, struct vm_area_struct *vma)
{
    struct rtk_gem_ion_object *ion_obj;
    struct drm_gem_object *gem_obj;
    int ret;

    ret = drm_gem_mmap(filp, vma);
    if (ret)
        return ret;

    gem_obj = vma->vm_private_data;
    ion_obj = to_rtk_gem_ion_obj(gem_obj);

    return rtk_gem_ion_mmap_obj(ion_obj, vma);
}

struct sg_table *rtk_gem_ion_prime_get_sg_table(struct drm_gem_object *obj)
{
    struct rtk_gem_ion_object *ion_obj = to_rtk_gem_ion_obj(obj);
    struct sg_table *ion_sgt = NULL;
    struct sg_table *sgt = NULL;

    DRM_DEBUG_PRIME("[%s:%d]\n", __func__, __LINE__);

    ion_sgt = ion_sg_table(rtk_gem_ion_get_client(), ion_obj->handle);
    if (!ion_sgt) {
        DRM_ERROR("[%s:%d] ion_sg_table %p \n", __func__, __LINE__, ion_sgt);
        return NULL;
    }

    sgt = kzalloc(sizeof(*sgt), GFP_KERNEL);
    if (!sgt)
        return NULL;

    if (sg_alloc_table(sgt, ion_sgt->nents, GFP_KERNEL) != 0) {
        DRM_ERROR("[%s:%d] sg_alloc_table %p \n", __func__, __LINE__, sgt);
        kfree(sgt);
        goto out;
    }

    {
        struct scatterlist *rd, *wr;
        unsigned int i;
        rd = ion_sgt->sgl;
        wr = sgt->sgl;
        for (i = 0; i<ion_sgt->nents; i++) {
            sg_set_page(wr, sg_page(rd), rd->length, rd->offset);
            sg_dma_address(wr) = sg_phys(rd);
            sg_dma_len(wr) = rd->length;
            rd = sg_next(rd);
            wr = sg_next(wr);
        }
    }

    return sgt;

out:
    kfree(sgt);
    return NULL;
}

struct drm_gem_object * rtk_gem_ion_prime_import_sg_table(struct drm_device *dev,
        struct dma_buf_attachment *attach,
        struct sg_table *sgt)
{
    struct rtk_gem_ion_object *ion_obj;

    if (sgt->nents != 1)
        return ERR_PTR(-EINVAL);

    /* Create a CMA GEM buffer. */
    ion_obj = __rtk_gem_ion_create(dev, attach->dmabuf->size);
    if (IS_ERR(ion_obj))
        return ERR_CAST(ion_obj);

    ion_obj->paddr = sg_dma_address(sgt->sgl);
    ion_obj->sgt = sgt;

    DRM_DEBUG_PRIME("dma_addr = %pad, size = %zu\n", &ion_obj->paddr, attach->dmabuf->size);

    return &ion_obj->base;
}

int rtk_gem_ion_prime_mmap(struct drm_gem_object *obj,
        struct vm_area_struct *vma)
{
    struct rtk_gem_ion_object *ion_obj;
    struct drm_device *dev = obj->dev;
    int ret;

    mutex_lock(&dev->struct_mutex);
    ret = drm_gem_mmap_obj(obj, obj->size, vma);
    mutex_unlock(&dev->struct_mutex);
    if (ret < 0)
        return ret;

    ion_obj = to_rtk_gem_ion_obj(obj);
    return rtk_gem_ion_mmap_obj(ion_obj, vma);
}

void *rtk_gem_ion_prime_vmap(struct drm_gem_object *obj)
{
    struct rtk_gem_ion_object *ion_obj = to_rtk_gem_ion_obj(obj);

    return ion_obj->vaddr;
}

void rtk_gem_ion_prime_vunmap(struct drm_gem_object *obj, void *vaddr)
{
    /* Nothing to do */
}

int rtk_gem_create_ioctl(struct drm_device *drm, void *data, struct drm_file *file_priv) {
    DRM_DEBUG_PRIME("[%s]\n", __func__);
    return rtk_gem_ion_dumb_create_internal(file_priv, drm, (struct drm_mode_create_dumb *)data);
}
