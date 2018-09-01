#ifndef __SOC_REALTEK_DEBUG_H
#define __SOC_REALTEK_DEBUG_H

struct rdbg_info;

#ifdef CONFIG_RTK_REGISTER_TRACKER

struct rdbg_info *rdbg_create_info(unsigned long paddr);
struct rdbg_info *rdbg_phy2info(unsigned long paddr);
void rdbg_update_ref(struct rdbg_info *info, unsigned int update_val,
	const char *caller);

#else /* !CONFIG_RTK_REGISTER_TRACKER */

static inline struct rdbg_info *rdbg_create_info(unsigned long paddr)
{
	return NULL;
}

static inline struct rdbg_info *rdbg_phy2info(unsigned long paddr)
{
	return NULL;
}

static inline void rdbg_update_ref(struct rdbg_info *info, unsigned int update_val,
	        const char *caller)
{

}
#endif /* CONFIG_RTK_REGISTER_TRACKER */

#include <linux/of_address.h>
#include <linux/ioport.h>

static inline struct rdbg_info *of_rdbg_get_info(struct device_node *np,
	int index, unsigned int offset)
{
	struct resource res;
	struct rdbg_info *info;

	of_address_to_resource(np, index, &res);

	info = rdbg_phy2info((unsigned long)res.start + offset);
	if (!info)
		info = rdbg_create_info((unsigned long)res.start + offset);

	return info;
}

#ifdef CONFIG_RTK_PM_RUNTIME_DEBUG

int rpm_debug_sysfs_add(struct device *dev);
void rpm_debug_sysfs_remove(struct device *dev);

#else /* !CONFIG_RTK_PM_RUNTIME_DEBUG */

static inline int rpm_debug_sysfs_add(struct device *dev)
{
	return 0;
}

static inline void rpm_debug_sysfs_remove(struct device *dev)
{}

#endif /* CONFIG_RTK_PM_RUNTIME_DEBUG */


#endif /* __SOC_REALTEK_DEBUG_H */
