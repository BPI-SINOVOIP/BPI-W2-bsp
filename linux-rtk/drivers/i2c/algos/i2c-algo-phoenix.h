/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License version 2 as published by the Free Software Foundation.
 *
 * Copyright (C) 2005 Chih-pin Wu <wucp@realtek.com.tw>
 */

#ifndef I2C_ALGO_VENUS_H
#define I2C_ALGO_VENUS_H

#include <linux/i2c.h>


#define MAX_NAME_LENGTH     32

typedef struct  
{	
    unsigned char   addr;
    char            name[MAX_NAME_LENGTH];
}venus_i2c_name_param;

typedef struct {
    unsigned int        tx_count;
    unsigned int        tx_err;
    unsigned int        rx_count;    
    unsigned int        rx_err;
	char                name[MAX_NAME_LENGTH];	
}target_info;

typedef struct 
{    
	void* dev_id;
	int (*masterXfer)(void* dev_id, struct i2c_msg *msgs, int num);
	int (*set_speed) (void* dev_id, int KHz);
	
}i2c_venus_algo;



int i2c_venus_add_bus(struct i2c_adapter *);
int i2c_venus_del_bus(struct i2c_adapter *);
int venus_set_target_name(
    struct i2c_adapter*     adapter,     
    unsigned char           addr,
    const char*             name, 
    unsigned char           length 
    );

#endif /* I2C_ALGO_VENUS_H */
