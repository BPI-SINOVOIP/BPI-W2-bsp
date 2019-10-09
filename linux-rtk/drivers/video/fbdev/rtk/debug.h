#ifndef __DEBUG_RTK_H__
#define __DEBUG_RTK_H__

#define NONE            "\033[m"
#define RED             "\033[0;32;31m"
#define LIGHT_RED       "\033[1;31m"
#define GREEN           "\033[0;32;32m"
#define LIGHT_GREEN     "\033[1;32m"
#define BLUE            "\033[0;32;34m"
#define LIGHT_BLUE      "\033[1;34m"
#define DARY_GRAY       "\033[1;30m"
#define CYAN            "\033[0;36m"
#define LIGHT_CYAN      "\033[1;36m"
#define PURPLE          "\033[0;35m"
#define LIGHT_PURPLE    "\033[1;35m"
#define BROWN           "\033[0;33m"
#define YELLOW          "\033[1;33m"
#define LIGHT_GRAY      "\033[0;37m"
#define WHITE           "\033[1;37m"

#define ATTR_OFF        "\033[0m"
#define BOLD            "\033[1m"
#define UNDERSCORE      "\033[4m"
#define BLINK           "\033[5m"
#define REVERSE         "\033[7m"
#define CONCEALED       "\033[8m"

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
