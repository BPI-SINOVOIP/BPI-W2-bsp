/*
 * scd_gpio_priv_config.h - smartcard driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 */


#ifndef __SCD_GPIO_PRIV_CONFIG_H__
#define __SCD_GPIO_PRIV_CONFIG_H__

//#define SPI_UART
//#define SPI_UART_TX
#define FORCE_SET_PINMUX

// clock
#define GPIO_SCD_CLK_GPIO           venus_gpio_id(MIS_GPIO, 4)
#define GPIO_SCD_CLK_PINMUX_REG     0xb8000378
#define GPIO_SCD_CLK_PINMUX_MASK    (0x7<<8)
#define GPIO_SCD_CLK_PINMUX_VAL_IO  (0x4<<8)
#define GPIO_SCD_CLK_PINMUX_VAL_PWM (0x6<<8)

// Card Detect
//#define GPIO_SCD_CD_GPIO           venus_gpio_id(MIS_GPIO, 5)
//#define GPIO_SCD_CD_PINMUX_REG     0xb8000378
//#define GPIO_SCD_CD_PINMUX_MASK    (0x7<<8)
//#define GPIO_SCD_CD_PINMUX_VAL     (0x4<<8)

#define GPIO_SCD_CD_GPIO           venus_gpio_id(MIS_GPIO, 122)
#define GPIO_SCD_CD_PINMUX_REG     0xb800037c
#define GPIO_SCD_CD_PINMUX_MASK    (0x3<<21)
#define GPIO_SCD_CD_PINMUX_VAL     (0)

// Reset
//#define GPIO_SCD_RST_GPIO           venus_gpio_id(MIS_GPIO, 121)
//#define GPIO_SCD_RST_PINMUX_REG     0xb800037C
//#define GPIO_SCD_RST_PINMUX_MASK    (0x3<<15)
//#define GPIO_SCD_RST_PINMUX_VAL     (0)   
    
#define GPIO_SCD_RST_GPIO           venus_gpio_id(MIS_GPIO, 60)
#define GPIO_SCD_RST_PINMUX_REG     0xb800037C
#define GPIO_SCD_RST_PINMUX_MASK    (0x3<<19)
#define GPIO_SCD_RST_PINMUX_VAL     (0)   

//#define GPIO_SCD_RST_GPIO             venus_gpio_id(MIS_GPIO, 120)   
//#define GPIO_SCD_RST_PINMUX_REG       0xb800037C
//#define GPIO_SCD_RST_PINMUX_MASK      (0x3<<17)
//#define GPIO_SCD_RST_PINMUX_VAL       (0)

    
// IO    
#ifdef SPI_UART     

    #define GPIO_SCD_DATAOUT_GPIO               venus_gpio_id(MIS_GPIO, 1)
    #define GPIO_SCD_DATAOUT_PINMUX_REG         0xb8000378
    #define GPIO_SCD_DATAOUT_PINMUX_MASK        (0x3<<2)
    #define GPIO_SCD_DATAOUT_PINMUX_VAL_GPIO    (0x1<<2)
    #define GPIO_SCD_DATAOUT_PINMUX_VAL_UART    (0x2<<2)
    
    #define GPIO_SCD_DATAIN_GPIO                venus_gpio_id(MIS_GPIO, 2)
    #define GPIO_SCD_DATAIN_PINMUX_REG          0xb8000378
    #define GPIO_SCD_DATAIN_PINMUX_MASK         (0x3<<4)
    #define GPIO_SCD_DATAIN_PINMUX_VAL_GPIO     (0x1<<4)    
    #define GPIO_SCD_DATAIN_PINMUX_VAL_UART     (0x2<<4)    
         
#else        

  #ifdef SPI_UART_TX
    #define GPIO_SCD_DATAOUT_GPIO               venus_gpio_id(MIS_GPIO, 1)
    #define GPIO_SCD_DATAOUT_PINMUX_REG         0xb8000378
    #define GPIO_SCD_DATAOUT_PINMUX_MASK        (0x3<<2)
    #define GPIO_SCD_DATAOUT_PINMUX_VAL_GPIO    (0x1<<2)  
    #define GPIO_SCD_DATAOUT_PINMUX_VAL_UART    (0x2<<2)      
  #else        
    #define GPIO_SCD_DATAOUT_GPIO               venus_gpio_id(MIS_GPIO, 58)
    #define GPIO_SCD_DATAOUT_PINMUX_REG         0xb8000378
    #define GPIO_SCD_DATAOUT_PINMUX_MASK        (0x7<<16)
    #define GPIO_SCD_DATAOUT_PINMUX_VAL_GPIO    (0x7<<16)  
    #define GPIO_SCD_DATAOUT_PINMUX_VAL_UART    (0x4<<16)  
  #endif                
    #define GPIO_SCD_DATAIN_GPIO                venus_gpio_id(MIS_GPIO, 57)
    #define GPIO_SCD_DATAIN_PINMUX_REG          0xb8000378
    #define GPIO_SCD_DATAIN_PINMUX_MASK         (0x7<<16)
    #define GPIO_SCD_DATAIN_PINMUX_VAL_GPIO     (0x7<<16)                 
    #define GPIO_SCD_DATAIN_PINMUX_VAL_UART     (0x4<<16)                 
#endif                


// CMD_VCC
#ifdef USE_TDA8024
//#define GPIO_SCD_CMD_VCC_GPIO           venus_gpio_id(MIS_GPIO, 120)   
//#define GPIO_SCD_CMD_VCC_PINMUX_REG     0xb800037C
//#define GPIO_SCD_CMD_VCC_PINMUX_MASK    (0x3<<17)
//#define GPIO_SCD_CMD_VCC_PINMUX_VAL     (0)

#define GPIO_SCD_CMD_VCC_GPIO           venus_gpio_id(MIS_GPIO, 121)
#define GPIO_SCD_CMD_VCC_PINMUX_REG     0xb800037C
#define GPIO_SCD_CMD_VCC_PINMUX_MASK    (0x3<<15)
#define GPIO_SCD_CMD_VCC_PINMUX_VAL     (0)   

#define GPIO_SCD_PWR_SEL_GPIO           venus_gpio_id(MIS_GPIO, 5)
#define GPIO_SCD_PWR_SEL_PINMUX_REG     0xb8000378
#define GPIO_SCD_PWR_SEL_PINMUX_MASK    (0x7<<11)
#define GPIO_SCD_PWR_SEL_PINMUX_VAL     (0x4<<11)   
#endif

#endif // __SCD_GPIO_PRIV_CONFIG_H__
