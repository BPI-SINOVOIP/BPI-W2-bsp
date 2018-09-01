#ifndef _UMP_FB_INTERFACE_H_
#define _UMP_FB_INTERFACE_H_

#include "linux/ump.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct ump_operations {                                                
    ump_dd_handle (*create_from_phys_blocks_64) (const ump_dd_physical_block_64 * blocks, uint64_t num_blocks, ump_alloc_flags flags, ump_dd_security_filter filter_func, ump_dd_final_release_callback final_release_func, void* callback_data);
    ump_dd_handle (*create_from_phys_blocks) (ump_dd_physical_block * blocks, unsigned long num_blocks);

    ump_secure_id (*secure_id_get) (const ump_dd_handle mem);
};

//int ump_ops_register(struct ump_operations * cb);

//EXPORT_SYMBOL(ump_ops);                                                
//EXPORT_SYMBOL(ump_ops_register);

#ifdef __cplusplus
}
#endif
#endif /* _UMP_FB_INTERFACE_H_ */
