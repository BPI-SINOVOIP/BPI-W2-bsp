/*
 * i2c-algo-venus.c: i2c driver algorithms for Realtek Venus DVR
 * 
 * This file is subject to the terms and conditions of the GNU General Public
 * License version 2 as published by the Free Software Foundation.
 *
 * Copyright (C) 2005 Chih-pin Wu <wucp@realtek.com.tw>
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/delay.h>

#include <linux/i2c-dev.h>
#include <linux/proc_fs.h>
#include "i2c-algo-phoenix.h"


/*------------------------------------------------------------------
 * Func : venus_xfer
 *
 * Desc : 
 *
 * Parm : adapter : i2c adapter
 *
 * Retn : 
 *------------------------------------------------------------------*/ 
static 
int venus_xfer(
    struct i2c_adapter*     i2c_adap,
    struct i2c_msg*         msgs,
    int                     num
    )
{
    i2c_venus_algo* p_alog = (i2c_venus_algo*) i2c_adap->algo_data;
    
    return p_alog->masterXfer(p_alog->dev_id, msgs, num);	
}


/*------------------------------------------------------------------
 * Func : venus_func
 *
 * Desc : 
 *
 * Parm : adapter : i2c adapter
 *
 * Retn : 
 *------------------------------------------------------------------*/ 
static 
u32 venus_func(
    struct i2c_adapter*     adap
    )
{
	return I2C_FUNC_SMBUS_EMUL;
}	


static 
struct i2c_algorithm venus_algo = {		
	.master_xfer	= venus_xfer,	
	.functionality	= venus_func,
};

 
 
/*------------------------------------------------------------------
 * Func : i2c_venus_add_bus
 *
 * Desc : add an venus i2c adapter onto i2c bus
 *
 * Parm : adapter : i2c adapter 
 *
 * Retn : 
 *------------------------------------------------------------------*/  
int i2c_venus_add_bus(struct i2c_adapter *adap)
{        	
	adap->algo = &venus_algo;   	
	return i2c_add_adapter(adap);
}



/*------------------------------------------------------------------
 * Func : i2c_venus_add_bus
 *
 * Desc : delete an venus i2c adapter from i2c bus
 *
 * Parm : adapter : i2c adapter 
 *
 * Retn : 
 *------------------------------------------------------------------*/
int i2c_venus_del_bus(struct i2c_adapter *adap)
{    
	i2c_del_adapter(adap);
	return ;
}


EXPORT_SYMBOL(i2c_venus_add_bus);
EXPORT_SYMBOL(i2c_venus_del_bus);

MODULE_AUTHOR("Kevin Wang <kevin_wang@realtek.com>");
MODULE_DESCRIPTION("I2C-Bus Venus algorithm");
MODULE_LICENSE("GPL");
