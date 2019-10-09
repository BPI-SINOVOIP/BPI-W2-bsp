#ifndef __SCD_DEBUG_H__
#define __SCD_DEBUG_H__


//-- scd debug messages
//#define CONFIG_SMARTCARD_DBG
//#define CONFIG_SCD_INT_DBG
//#define CONFIG_SCD_TX_DBG
//#define CONFIG_SCD_RX_DBG
//#define CONFIG_SCD_INFO
//#define CONFIG_SCD_WARNING

#ifdef  CONFIG_SMARTCARD_DBG
#define SC_TRACE                   printk(KERN_WARNING "[SCD] TRACE, " fmt, ## args)  
#else
#define SC_TRACE(args...)    
#endif


#ifdef  CONFIG_SCD_INT_DBG
#define SC_INT_DBG(fmt, args...)        printk(KERN_WARNING "[SCD] INT, " fmt, ## args)  
#else
#define SC_INT_DBG(args...)    
#endif

#ifdef CONFIG_SCD_INFO
#define SC_INFO(fmt, args...)           printk(KERN_WARNING "[SCD] Info, " fmt, ## args)  
#else
#define SC_INFO(fmt, args...) 
#endif

#ifdef CONFIG_SCD_WARNING
#define SC_WARNING(fmt, args...)        printk(KERN_EMERG "[SCD] Warning, " fmt, ## args)  
#else
#define SC_WARNING(fmt, args...)  
#endif


#endif  //__SCD_DEBUG_H__



