#ifndef __SCD_H__
#define __SCD_H__

#include <linux/device.h>
#include "scd_debug.h"
#include "scd_atr.h"
#include "scd_buff.h"

extern struct bus_type scd_bus_type;

#define MAX_SCD_DEVICE     4

//-------------------------------------------------------
// data structure
//-------------------------------------------------------
typedef enum {
    SC_VCC_3V = 0,
    SC_VCC_5V,    
}SC_VCC_LVL;

typedef enum {
    SC_AUTO_CONV = 0,
    SC_DIRECT_CONV,
    SC_INVERSE_CONV,    
}SC_CONV;

typedef enum {
    SC_PARITY_NONE = 0,
    SC_PARITY_ODD,
    SC_PARITY_EVEN,    
}SC_PARITY;

typedef enum {
    SC_CARD_REMOVED = 0,        // ICC does not exist
    SC_CARD_DEACTIVATE,         // ICC exists, but has not been activated
    SC_CARD_RESET,              // ICC is reseting and waiting for ATR
    SC_CARD_RESET_TIMEOUT,      // ICC Reset failed, due to no ATR responsed
    SC_CARD_ACTIVATE,           // ICC has been activated successfully
    SC_CARD_UNKNOWN,            // ICC has some error...
}SC_CARD_STATUS;

typedef enum {
    SC_SUCCESS = 0,
    SC_FAIL = -1,
    SC_ERR_NO_ICC = -2 ,  
    SC_ERR_ICC_DEACTIVATE = -3,    
    SC_ERR_IFD_DISABLED = -4,       
    SC_ERR_ATR_TIMEOUT = -5,   
}SC_RET;

typedef enum {
    SC_PARAM_VCC_LVL = 0,
    SC_PARAM_CLOCK,
    SC_PARAM_ETU,
    SC_PARAM_CONV,
    SC_PARAM_PARITY,
    SC_PARAM_GUARD_INTERVAL,
    SC_PARAM_FLOW_CONTROL,             // used for SMC with Flow Control (ICAM SMC)
    SC_PARAM_EXTENDED_IO_CONTROL,      // used for SMC with Extend IO Control (ICAM SMC)    
    SC_PARAM_RESETTIMEOUT,
    SC_PARAM_ENABLE_BYPASSATR,
    SC_PARAM_BWI,
    SC_PARAM_CWI
}SC_PARAMETER_ID;

#define SC_IO_CTRL_IO_C7    0x80       // Use C7 as IO Pin, C4, C8 = Bidirectional GPIO
#define SC_IO_CTRL_IO_C4    0x40       // Use C4 as IO Pin, C7, C8 = Bidirectional GPIO
#define SC_IO_CTRL_IO_C8    0x20       // Use C8 as IO Pin, C7, C4 = Bidirectional GPIO  
#define SC_IO_CTRL_IO_MASK  (SC_IO_CTRL_IO_C7|SC_IO_CTRL_IO_C4|SC_IO_CTRL_IO_C8)  
#define SC_IO_CTRL_C7_ON    0x08       // C7 output High (only valid if C7 is in GPIO mode)
#define SC_IO_CTRL_C4_ON    0x04       // C4 output High (only valid if C4 is in GPIO mode)   
#define SC_IO_CTRL_C8_ON    0x02       // C8 output High (only valid if C8 is in GPIO mode)   

typedef struct {
    unsigned long long  id;         // parameter id
    unsigned long  long val;        // parameter val
}scd_param;

//-------------------------------------------------------
// device
//-------------------------------------------------------
typedef struct 
{
    unsigned long   id;
    char*           name;
    struct device   dev;
}scd_device;



#define to_scd_device(x)  container_of(x, scd_device, dev) 

static inline void *scd_get_drvdata (scd_device *device)
{
    return dev_get_drvdata(&device->dev);
}
 
static inline void
scd_set_drvdata (scd_device *device, void *data)
{
    struct device *dev = &device->dev;
    dev_set_drvdata(dev, data);
}

extern int  register_scd_device(scd_device* device);
extern void unregister_scd_device(scd_device* device);



//-------------------------------------------------------
// driver
//-------------------------------------------------------

typedef struct 
{
    char*                       name;
    
    struct device_driver        drv;    
    
    //--------- ops
    
    int     (*probe)            (scd_device*        dev);
    
    void    (*remove)           (scd_device*        dev);    
        
    int     (*enable)           (scd_device*        dev, 
                                 unsigned char      on_off);
                                         
    int     (*set_param)        (scd_device*        dev, 
                                 unsigned long      param_id,                                
                                 unsigned long      val);
                                 
    int     (*get_param)        (scd_device*        dev, 
                                 unsigned long      param_id,                                
                                 unsigned long*     p_val);                                 

    //---------         
    int     (*activate)         (scd_device*        dev);

    int     (*deactivate)       (scd_device*        dev);

    int     (*reset)            (scd_device*        dev);
    
    int     (*get_atr)          (scd_device*        dev, 
                                 scd_atr*           p_atr);
    
    int     (*get_card_status)  (scd_device*        dev);
    
    int     (*poll_card_status) (scd_device*        dev);
    
    int     (*xmit)             (scd_device*        dev, 
                                 unsigned char*     p_data,
                                 unsigned int       len);    
    
    int     (*read)             (scd_device*        dev,
                                 unsigned char*     p_data, 
                                 unsigned int       len);   

    //--------- power management ------------
    int     (*suspend)          (scd_device* dev);
    
    int     (*resume)           (scd_device* dev);
    
    
}scd_driver;


#define to_scd_driver(x)  container_of(x, scd_driver, drv) 

extern int  register_scd_driver(scd_driver* driver);
extern void unregister_scd_driver(scd_driver* driver);


#endif  //__SCD_CORE_H__

