#ifndef __DEBUG_RTK_H__
#define __DEBUG_RTK_H__

#include "color.h"

#define dbg_fmt(fmt) fmt

#define dbg_err(fmt, ...) \
	printk(KERN_ERR RED dbg_fmt(fmt) NONE"\n", ##__VA_ARGS__)

#define dbg_emerg(fmt, ...) \
	printk(KERN_EMERG RED dbg_fmt(fmt) NONE"\n", ##__VA_ARGS__)

#define dbg_alert(fmt, ...) \
	printk(KERN_ALERT RED dbg_fmt(fmt) NONE"\n", ##__VA_ARGS__)

#define dbg_crit(fmt, ...) \
	printk(KERN_CRIT RED dbg_fmt(fmt) NONE"\n", ##__VA_ARGS__)

#define dbg_warning(fmt, ...) \
	printk(KERN_WARNING RED dbg_fmt(fmt) NONE"\n", ##__VA_ARGS__)

#define dbg_warn dbg_warning

#define dbg_info(fmt, ...) \
	printk(KERN_INFO CYAN dbg_fmt(fmt) NONE"\n", ##__VA_ARGS__)

#define dbg_notice(fmt, ...) \
	printk(KERN_NOTICE CYAN dbg_fmt(fmt) NONE"\n", ##__VA_ARGS__)

#define dbg_cont(fmt, ...) \
	printk(KERN_CONT CYAN fmt NONE"\n", ##__VA_ARGS__)

#endif /* __DEBUG_RTK_H__ */
