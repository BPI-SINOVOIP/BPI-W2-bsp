#ifndef __SCD_DEV_H__
#define __SCD_DEV_H__

#include <linux/cdev.h>
#include "scd.h"

#define SCD_IFD_ENABLE          0x7300
#define SCD_RESET               0x7301
#define SCD_SETPARAM            0x7302  
#define SCD_GETPARAM            0x7303
#define SCD_DEACTIVE            0x7306
#define SCD_ACTIVE              0x7307
#define SCD_GET_ATR             0x7309
#define SCD_READ                0x730a
#define SCD_WRITE               0x730b
#define SCD_GET_CARD_STATUS     0x730d
#define SCD_POLL_CARD_STATUS_CHANGE 0x730e

#define SCD_SETPARAM_EX         0x7310  
#define SCD_GETPARAM_EX         0x7311

typedef struct {    
    unsigned long clk;
    unsigned long etu;                            
}scd_ifd_param;

typedef struct{                
    unsigned char*  p_data;
    unsigned int    length;
}sc_msg_buff;


typedef struct{        
    struct cdev     cdev;
    struct device*  device;
}scd_dev;

extern int  create_scd_dev_node(scd_device* dev);
extern void remove_scd_dev_node(scd_device* dev);

extern int scd_dev_module_init(void);
extern void scd_dev_module_exit(void);

#endif  //__SCD_DEV_H__

