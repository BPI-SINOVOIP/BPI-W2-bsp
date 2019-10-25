#ifndef __TSIO_DBG_H__
#define __TSIO_DBG_H__

#define CONFIG_TSIO_DBG

#ifdef  CONFIG_TSIO_DBG
#define TSIO_TRACE(fmt, args...)          printk(KERN_INFO "[TSIO] TRACE, " fmt, ## args)
#define TSIO_WARNING(fmt, args...)        printk(KERN_EMERG "[TSIO] Warning, " fmt, ## args)
#else
#define TSIO_TRACE(fmt, args...)
#define TSIO_WARNING(fmt, args...)
#endif

#endif  //__TSIO_DBG_H__
