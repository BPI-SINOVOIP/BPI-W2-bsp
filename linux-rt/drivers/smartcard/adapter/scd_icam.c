/* ------------------------------------------------------------------------- 
   scd_icam.c  scd driver for Realtek Neptune/Mars           
   ------------------------------------------------------------------------- 
    Copyright (C) 2008 Kevin Wang <kevin_wang@realtek.com.tw>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.    
----------------------------------------------------------------------------
Update List :
----------------------------------------------------------------------------
    1.0     |   20090312    |   Kevin Wang  | 1) create phase
----------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/ioport.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <asm/io.h>
#include "scd_icam_priv.h"

MODULE_LICENSE("GPL");


/*------------------------------------------------------------------
 * Func : ops_probe
 *
 * Desc : probe a scd device
 *
 * Parm : dev
 *         
 * Retn : SC_SUCCESS / SC_FAIL
 *------------------------------------------------------------------*/
static 
int ops_probe(scd_device* dev)
{    
    icam_scd* p_scd;
    
    if ((dev->id & 0xFFFFFFFF)!=ICAM_SCD_ID)
        return -ENODEV;                            
                
    p_scd = icam_scd_open();
    
    if (p_scd==NULL)
        return -ENOMEM;
   
    scd_set_drvdata(dev, p_scd);    // attach it to the scd_device
    return 0;     
}



/*------------------------------------------------------------------
 * Func : ops_remove
 *
 * Desc : this function will be invoked when a smart card device which 
 *        associated with this driver has been removed
 *
 * Parm : dev : smart card device to be removed
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
static 
void ops_remove(scd_device* dev)
{       
    icam_scd_close((icam_scd*) scd_get_drvdata(dev));
}



/*------------------------------------------------------------------
 * Func : ops_enable
 *
 * Desc : enable IFD
 *
 * Parm : dev    : ifd device
 *        on_off : 0      : disable IFD 
 *                 others : enable IFD
 *         
 * Retn : SC_SUCCESS / SC_FAIL
 *------------------------------------------------------------------*/
static 
int ops_enable(scd_device* dev, unsigned char on_off)
{    
    icam_scd* p_this = (icam_scd*) scd_get_drvdata(dev);
    return icam_scd_enable(p_this, on_off);        
}



/*------------------------------------------------------------------
 * Func : ops_set_param
 *
 * Desc : set param of IFD
 *
 * Parm : dev
 *         
 * Retn : SC_SUCCESS / SC_FAIL
 *------------------------------------------------------------------*/
static 
int ops_set_param(
    scd_device*             dev, 
    unsigned long           id,
    unsigned long           val
    )
{    
    icam_scd* p_this = (icam_scd*) scd_get_drvdata(dev);
    int ret= SC_SUCCESS; 
        
    switch(id) 
    {        
    case SC_PARAM_VCC_LVL:
        ret = icam_scd_set_vcc_level(p_this, (SC_VCC_LVL) val);   
        break;
        
    case SC_PARAM_CLOCK:
        ret = icam_scd_set_clock(p_this, (unsigned long) val);        
        break;
        
    case SC_PARAM_ETU:
        ret = icam_scd_set_etu(p_this, (unsigned long) val); 
        break;
        
    case SC_PARAM_CONV:
        ret = icam_scd_set_convention(p_this, (SC_CONV) val);   
        break;
        
    case SC_PARAM_PARITY:
        // do nothing...        
        break;
        
    case SC_PARAM_GUARD_INTERVAL:
        ret = icam_scd_set_guard_interval(p_this, val);   
        break;
        
    case SC_PARAM_FLOW_CONTROL:
        ret = icam_scd_set_flow_control(p_this, val);   
        break;        
        
    case SC_PARAM_EXTENDED_IO_CONTROL:
        ret = icam_scd_set_uart_command(p_this, val);   
        break;         
        
    default:
        ret = SC_FAIL;        
    }
            
    return ret;
}



/*------------------------------------------------------------------
 * Func : ops_get_param
 *
 * Desc : get param of IFD
 *
 * Parm : dev
 *         
 * Retn : SC_SUCCESS / SC_FAIL
 *------------------------------------------------------------------*/
static 
int ops_get_param(
    scd_device*             dev, 
    unsigned long           id,                                
    unsigned long*          p_val
    )
{    
    icam_scd* p_this = (icam_scd*) scd_get_drvdata(dev);
    int ret = SC_SUCCESS;    
        
    switch(id) 
    {        
    case SC_PARAM_VCC_LVL:
        ret = icam_scd_get_vcc_level(p_this, (SC_VCC_LVL*) p_val);   
        break;
        
    case SC_PARAM_CLOCK:        
        ret = icam_scd_get_clock(p_this,  p_val);        
        break;
        
    case SC_PARAM_ETU:
        ret = icam_scd_get_etu(p_this, p_val); 
        break;
        
    case SC_PARAM_CONV:
        ret = icam_scd_get_convention(p_this, (SC_CONV*) p_val);   
        break;
        
    case SC_PARAM_PARITY:
        *p_val = SC_PARITY_EVEN;        
        break;
        
    case SC_PARAM_GUARD_INTERVAL:        
        ret = icam_scd_get_guard_interval(p_this, p_val);   
        break;        
        
    case SC_PARAM_EXTENDED_IO_CONTROL:
        ret = icam_scd_get_uart_command(p_this, p_val);   
        break;                
        
    default:
        ret = SC_FAIL;        
    }
    
    return ret;
}



/*------------------------------------------------------------------
 * Func : ops_activate
 *
 * Desc : activate ICC via reset procedure
 *
 * Parm : dev
 *         
 * Retn : SC_SUCCESS / SC_FAIL
 *------------------------------------------------------------------*/        
static 
int ops_activate(scd_device* dev)
{            
    icam_scd* p_this = (icam_scd*) scd_get_drvdata(dev);    
    return icam_scd_activate(p_this);    
}



/*------------------------------------------------------------------
 * Func : ops_deactivate
 *
 * Desc : deactivate icc
 *
 * Parm : dev
 *         
 * Retn : SC_SUCCESS / SC_FAIL
 *------------------------------------------------------------------*/        
static 
int ops_deactivate(scd_device* dev)
{            
    icam_scd* p_this = (icam_scd*) scd_get_drvdata(dev);    
    return icam_scd_deactivate(p_this);    
}



/*------------------------------------------------------------------
 * Func : ops_reset
 *
 * Desc : reset a scd device 
 *
 * Parm : dev
 *         
 * Retn : SC_SUCCESS / SC_FAIL
 *------------------------------------------------------------------*/        
static 
int ops_reset(scd_device* dev)
{            
    icam_scd* p_this = (icam_scd*) scd_get_drvdata(dev);    
    return icam_scd_reset(p_this);    
}



/*------------------------------------------------------------------
 * Func : ops_get_atr
 *
 * Desc : get atr from a scd device 
 *
 * Parm : dev 
 *         
 * Retn : SC_SUCCESS / SC_FAIL
 *------------------------------------------------------------------*/        
static 
int ops_get_atr(scd_device* dev, scd_atr* p_atr)
{
    icam_scd* p_this = (icam_scd*) scd_get_drvdata(dev);              
    return icam_scd_get_atr(p_this, p_atr);            
}


/*------------------------------------------------------------------
 * Func : ops_get_card_status
 *
 * Desc : get card status of IFD 
 *
 * Parm : dev 
 *         
 * Retn : SC_SUCCESS / SC_FAIL
 *------------------------------------------------------------------*/        
static 
int ops_get_card_status(scd_device* dev)
{    
    icam_scd* p_this = (icam_scd*) scd_get_drvdata(dev);    
    return icam_scd_get_card_status(p_this);
}


  
/*------------------------------------------------------------------
 * Func : ops_poll_card_status
 *
 * Desc : poll card status
 *
 * Parm : dev  :   
 *         
 * Retn : SC_SUCCESS / SC_FAIL
 *------------------------------------------------------------------*/        
static 
int ops_poll_card_status(scd_device* dev)
{
    icam_scd* p_this = (icam_scd*) scd_get_drvdata(dev);    
    return icam_scd_poll_card_status(p_this);    
}

  
/*------------------------------------------------------------------
 * Func : ops_xmit
 *
 * Desc : xmit data via smart card bus
 *
 * Parm : dev  :   
 *         
 * Retn : SC_SUCCESS / SC_FAIL
 *------------------------------------------------------------------*/        
static 
int ops_xmit(scd_device* dev, unsigned char* p_data, unsigned int len)
{   
    icam_scd* p_this = (icam_scd*) scd_get_drvdata(dev);    
    return icam_scd_xmit(p_this, p_data, len);     
}                                 
              
              
  
/*------------------------------------------------------------------
 * Func : ops_read
 *
 * Desc : read data via smart card bus
 *
 * Parm : dev  :   
 *         
 * Retn : SC_SUCCESS / SC_FAIL
 *------------------------------------------------------------------*/        
static 
int ops_read(scd_device* dev, unsigned char* p_data, unsigned int len)
{   
    icam_scd* p_this = (icam_scd*) scd_get_drvdata(dev);
    return icam_scd_read(p_this, p_data, len);
}
                                                                  

static scd_device icam_scd_controller[1] = 
{
    {
        .id   = ICAM_SCD_ID,
        .name = "icam_scd_0"
    },
};


static scd_driver icam_scd_driver = 
{    
    .name               = "icam_scd",
    .probe              = ops_probe,
    .remove             = ops_remove,        
    .suspend            = NULL,
    .resume             = NULL,
    .enable             = ops_enable,
    .set_param          = ops_set_param,
    .get_param          = ops_get_param,    
    .activate           = ops_activate,
    .deactivate         = ops_deactivate,
    .reset              = ops_reset,
    .get_atr            = ops_get_atr,
    .get_card_status    = ops_get_card_status,
    .poll_card_status   = ops_poll_card_status,
    .xmit               = ops_xmit,
    .read               = ops_read,
};




/*------------------------------------------------------------------
 * Func : icam_scd_module_init
 *
 * Desc : init icam smart card interface driver
 *
 * Parm : N/A
 *         
 * Retn : 0 : success, others fail  
 *------------------------------------------------------------------*/
static int __init icam_scd_module_init(void)
{                        
    SC_INFO("icam scd module init\n");        
                                
    if (register_scd_driver(&icam_scd_driver)!=0)
        return -EFAULT;                                        

    register_scd_device(&icam_scd_controller[0]);          // register scd device                            
    return 0;
}



/*------------------------------------------------------------------
 * Func : icam_scd_module_exit
 *
 * Desc : uninit icam smart card interface driver
 *
 * Parm : N/A
 *         
 * Retn : 0 : success, others fail  
 *------------------------------------------------------------------*/
static void __exit icam_scd_module_exit(void)
{            
    unregister_scd_device(&icam_scd_controller[0]);
    unregister_scd_driver(&icam_scd_driver);
}


module_init(icam_scd_module_init);
module_exit(icam_scd_module_exit);
