#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include "scd.h"

MODULE_LICENSE("GPL");

#ifdef CONFIG_SMARTCARD_DEV_FILE
#include "scd_dev.h"
#endif  



/*------------------------------------------------------------------
 * Func : scd_bus_match
 *
 * Desc : scd dev exit function
 *
 * Parm : dev    : device
 *        driver : driver
 *         
 * Retn : 1 : device & driver matched, 0 : device & driver not matched
 *------------------------------------------------------------------*/
int scd_bus_match(
    struct device*          dev, 
    struct device_driver*   drv
    )
{        
    // scd bus have no idea to match device & driver, return 1 to pass all     
    return 1;
}


/*------------------------------------------------------------------
 * Func : scd_bus_suspend
 *
 * Desc : suspend scd dev
 *
 * Parm : dev    : device to be suspend 
 *        state  : event : power state
 *               PM_EVENT_ON      0
 *               PM_EVENT_FREEZE  1
 *               PM_EVENT_SUSPEND 2
 *         
 * Retn : 0
 *------------------------------------------------------------------*/
int scd_bus_suspend(struct device * dev, pm_message_t state)
{    
    scd_device* p_dev = to_scd_device(dev);
    scd_driver* p_drv = to_scd_driver(dev->driver);    
    return (p_drv->suspend) ? p_drv->suspend(p_dev) : 0;
}


/*------------------------------------------------------------------
 * Func : scd_bus_resume
 *
 * Desc : resume scd bus
 *
 * Parm : dev    : device to be resumed 
 *         
 * Retn : 0
 *------------------------------------------------------------------*/
int scd_bus_resume(struct device * dev)
{
    scd_device* p_dev = to_scd_device(dev);
    scd_driver* p_drv = to_scd_driver(dev->driver);    
    return (p_drv->resume) ? p_drv->resume(p_dev) : 0;
}



struct bus_type scd_bus_type = {
    .name    = "smartcard",
    .match   = scd_bus_match,    
    .suspend = scd_bus_suspend,    
    .resume  = scd_bus_resume,    
};



/*------------------------------------------------------------------
 * Func : register_scd_device
 *
 * Desc : register scd device
 *
 * Parm : device    : scd device to be registered
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
void scd_device_release(struct device* dev)
{    
    scd_device* p_dev = to_scd_device(dev);
    
    SC_INFO("scd dev %s released\n", p_dev->name);    
}


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                            scd_device                                    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

static scd_device* scd_device_list[MAX_SCD_DEVICE] = {0};

/*------------------------------------------------------------------
 * Func : register_scd_device
 *
 * Desc : register scd device
 *
 * Parm : device    : scd device to be registered
 *         
 * Retn : 0
 *------------------------------------------------------------------*/
int register_scd_device(scd_device* device)
{
    struct device* dev = &device->dev;
    int i;
    
    for (i=0; i<MAX_SCD_DEVICE; i++)
    {
        if (scd_device_list[i]==NULL)
        {                   
            SC_INFO("register scd device '%s' (%p) to scd%d\n", device->name, dev, i);                
            
            dev_set_name(dev, "scd%d", i);     
    
            dev->bus = &scd_bus_type;
    
            dev->release  = scd_device_release;             
            
            if (device_register(dev)<0) 
            {
                SC_INFO("register scd device '%s' (%p) to scd%d failed\n", device->name, dev, i);
                return -1;
            }
            
            scd_device_list[i] = device;

            return 0;
        }
    }
    
    SC_INFO("register scd device '%s' (%p) failed, no more free entry\n", device->name, dev);
                       
    return -1;
}



/*------------------------------------------------------------------
 * Func : unregister_scd_device
 *
 * Desc : unregister scd device
 *
 * Parm : device : scd device to be unregistered
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
void unregister_scd_device(scd_device* device)
{    
    int i;
        
    for (i=0; i<MAX_SCD_DEVICE; i++)
    {
        if (scd_device_list[i]==device)   
        { 
            device_unregister(&device->dev);
            scd_device_list[i] = NULL;
        }
    }
}



//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                            scd_driver                                    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*------------------------------------------------------------------
 * Func : scd_drv_probe
 *
 * Desc : probe scd device
 *
 * Parm : dev : scd device to be probed
 *         
 * Retn : 0 : if supportted, others : failed
 *------------------------------------------------------------------*/
int scd_drv_probe(struct device * dev)
{
    scd_device* p_dev = to_scd_device(dev);    
    scd_driver* p_drv = to_scd_driver(dev->driver);    
    SC_INFO("probe : scd_dev '%s' (%p), scd_drv '%s' (%p)\n", p_dev->name, dev,p_drv->name, dev->driver);    
    
    if (!p_drv->probe)
        return -ENODEV;
        
    if (p_drv->probe(p_dev)==0)        
    {
#ifdef CONFIG_SMARTCARD_DEV_FILE
        create_scd_dev_node(p_dev);
#endif        
        return 0;    
    }

    return -ENODEV;
}



/*------------------------------------------------------------------
 * Func : scd_drv_remove
 *
 * Desc : this function was used to inform the scd driver that a scd 
 *        device has been removed
 *
 * Parm : dev : scd device to be removed
 *         
 * Retn : 0 for success, others failed
 *------------------------------------------------------------------*/
int scd_drv_remove(struct device * dev)
{
    scd_device* p_dev = to_scd_device(dev);    
    scd_driver* p_drv = to_scd_driver(dev->driver);
    
    SC_INFO("remove smart card device '%s'\n", p_dev->name);
    
    if (p_drv->remove) 
        p_drv->remove(p_dev);
        
#ifdef CONFIG_SMARTCARD_DEV_FILE   
    create_scd_dev_node(p_dev);
#endif  
        
    return 0;
}



/*------------------------------------------------------------------
 * Func : scd_drv_shutdown
 *
 * Desc : this function was used to short down a scd device 
 *
 * Parm : dev : scd device to be shut down
 *         
 * Retn : 0 for success, others failed
 *------------------------------------------------------------------*/
void scd_drv_shutdown(struct device * dev)
{
    scd_device* p_dev = to_scd_device(dev);    
    scd_driver* p_drv = to_scd_driver(dev->driver);    
    
    SC_INFO("shotdown smart card device '%s'\n", p_dev->name);            
    
    if (p_drv->enable)
        p_drv->enable(p_dev, 0);    
}



/*------------------------------------------------------------------
 * Func : scd_drv_suspend
 *
 * Desc : this function was used to suspend a scd device 
 *
 * Parm : dev : scd device to be suspend
 *         
 * Retn : 0 for success, others failed
 *------------------------------------------------------------------*/
int scd_drv_suspend(struct device * dev, pm_message_t state)
{
    scd_device* p_dev = to_scd_device(dev);    
    scd_driver*  p_drv = to_scd_driver(dev->driver);    
    
    SC_INFO("suspend scd_dev '%s'\n", p_dev->name);
    return (p_drv->suspend) ? p_drv->suspend(p_dev) : 0;
}



/*------------------------------------------------------------------
 * Func : scd_drv_resume
 *
 * Desc : this function was used to resume a scd device 
 *
 * Parm : dev : scd device to be suspend
 *         
 * Retn : 0 for success, others failed
 *------------------------------------------------------------------*/
int scd_drv_resume(struct device * dev)
{
    scd_device* p_dev = to_scd_device(dev);    
    scd_driver*  p_drv = to_scd_driver(dev->driver);    
    
    SC_INFO("resume scd_dev '%s'\n", p_dev->name);
        
    return (p_drv->resume) ? p_drv->resume(p_dev) : 0;    
}



/*------------------------------------------------------------------
 * Func : register_scd_driver
 *
 * Desc : register scd device driver
 *
 * Parm : driver    : scd device driver to be registered
 *         
 * Retn : 0
 *------------------------------------------------------------------*/
int register_scd_driver(scd_driver* driver)
{
    struct device_driver* drv = &driver->drv;
    
    drv->name     = driver->name;
    drv->bus      = &scd_bus_type;
    drv->probe    = scd_drv_probe;
    drv->remove   = scd_drv_remove;
    drv->shutdown = scd_drv_shutdown;
    drv->suspend  = scd_drv_suspend;
    drv->resume   = scd_drv_resume;
    
    SC_INFO("register scd driver '%s' (%p)\n", drv->name, drv);
        
    return driver_register(drv);
}



/*------------------------------------------------------------------
 * Func : unregister_scd_driver
 *
 * Desc : unregister scd driver
 *
 * Parm : driver : scd driver to be unregistered
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
void unregister_scd_driver(scd_driver* driver)
{   
    struct device_driver* drv = &driver->drv;    
    SC_INFO("unregister scd driver '%s' (%p)\n", drv->name, &driver->drv); 
    driver_unregister(&driver->drv);
}



/*------------------------------------------------------------------
 * Func : scd_dev_module_init
 *
 * Desc : scd dev init function
 *
 * Parm : N/A
 *         
 * Retn : 0 : success, others fail  
 *------------------------------------------------------------------*/
static int __init scd_core_init(void)
{                 
    SC_INFO("%s, register scd_bus %p\n",__FUNCTION__, &scd_bus_type);
        
#ifdef CONFIG_SMARTCARD_DEV_FILE
    scd_dev_module_init();
#endif        
        
    return bus_register(&scd_bus_type);     // register scd bus type            
}



/*------------------------------------------------------------------
 * Func : scd_dev_module_exit
 *
 * Desc : scd dev module exit function
 *
 * Parm : N/A
 *         
 * Retn : 0 : success, others fail  
 *------------------------------------------------------------------*/
static void __exit scd_core_exit(void)
{       

#ifdef CONFIG_SMARTCARD_DEV_FILE
    scd_dev_module_exit();
#endif            
    
    bus_unregister(&scd_bus_type);        // unregister scd bus    
}



module_init(scd_core_init);
module_exit(scd_core_exit);


EXPORT_SYMBOL(register_scd_device);
EXPORT_SYMBOL(unregister_scd_device);

EXPORT_SYMBOL(register_scd_driver);
EXPORT_SYMBOL(unregister_scd_driver);
