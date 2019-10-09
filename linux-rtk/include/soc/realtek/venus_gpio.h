/*
 * venus_gpio.h
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#ifndef __VENUS_GPIO_H__
#define __VENUS_GPIO_H__

#define VENUS_GPIO_ID               unsigned int

#define venus_gpio_id(group, idx)   (((group & 0x3) << 8) | (idx & 0xFF))
#define gpio_group(id)              ((id >> 8) & 0x3)
#define gpio_idx(id)                (id & 0xFF)
#define gpio_type(group)           ((group==ISO_GPIO) ? "ISO" : "MISC")

typedef struct 
{
    char   name[32];    
    void*  dev_id;
    void (*handler) (VENUS_GPIO_ID id, unsigned char assert, void* data);   // assert call back
}VENUS_GPIO_IRQ;


typedef enum {
    MIS_GPIO = 0,
    ISO_GPIO,
}VENUS_GPIO_GROUP;

typedef enum {
    VENUS_GPIO_DEBOUNCE_37ns = 0,
    VENUS_GPIO_DEBOUNCE_1us,
    VENUS_GPIO_DEBOUNCE_10us,
    VENUS_GPIO_DEBOUNCE_100us,
    VENUS_GPIO_DEBOUNCE_1ms,
    VENUS_GPIO_DEBOUNCE_10ms,
    VENUS_GPIO_DEBOUNCE_20ms,
    VENUS_GPIO_DEBOUNCE_30ms,
}VENUS_GPIO_DEBOUNCE;

////////////////// APIs ////////////////////

static __maybe_unused int venus_gpio_set_dir          (VENUS_GPIO_ID          gid,  unsigned char     out){return 0;}
static __maybe_unused int venus_gpio_set_debounce     (VENUS_GPIO_ID          gid, unsigned char     val){return 0;}                                
static __maybe_unused  int venus_gpio_input            (VENUS_GPIO_ID          gid){return 0;}                                 
static __maybe_unused  int venus_gpio_output           (VENUS_GPIO_ID          gid, unsigned char    val){return 0;}                                
static __maybe_unused  int venus_gpio_set_irq_polarity (VENUS_GPIO_ID          gid, unsigned char     positive){return 0;}
static __maybe_unused  int venus_gpio_set_irq_enable   (VENUS_GPIO_ID          gid,  unsigned char     on){return 0;}
static __maybe_unused  int venus_gpio_request_irq      (VENUS_GPIO_ID          gid, 
                                 void (*handler) (VENUS_GPIO_ID gid, unsigned char assert, void* dev_id), 
                                 char*                  name,
                                 void*                  dev_id){return 0;}


static __maybe_unused  void venus_gpio_free_irq        (VENUS_GPIO_ID          gid,  void*     dev_id){return ;}                                    
static  __maybe_unused int venus_gpio_clear_isr        (VENUS_GPIO_ID          gid){return 0;}
static __maybe_unused  int venus_gpio_chk_irq_enable   (VENUS_GPIO_ID          gid){return 0;}                                                         








/*

int venus_gpio_set_dir          (VENUS_GPIO_ID          gid, 
                                 unsigned char          out);

int venus_gpio_set_debounce     (VENUS_GPIO_ID          gid, 
                                 unsigned char          val);
                                 
int venus_gpio_input            (VENUS_GPIO_ID          gid);
                                 
int venus_gpio_output           (VENUS_GPIO_ID          gid,
                                 unsigned char          val);
                                 
int venus_gpio_set_irq_polarity (VENUS_GPIO_ID          gid, 
                                 unsigned char          positive);

int venus_gpio_set_irq_enable   (VENUS_GPIO_ID          gid, 
                                 unsigned char          on);

int venus_gpio_request_irq      (VENUS_GPIO_ID          gid, 
                                 void (*handler) (VENUS_GPIO_ID gid, unsigned char assert, void* dev_id), 
                                 char*                  name,
                                 void*                  dev_id);

void venus_gpio_free_irq        (VENUS_GPIO_ID          gid,
                                 void*                  dev_id);     
                                 
int venus_gpio_clear_isr        (VENUS_GPIO_ID          gid);

int venus_gpio_chk_irq_enable   (VENUS_GPIO_ID          gid);         
*/
////////////////// Debug messages ////////////////////


#ifdef CONFIG_VENUS_GPIO_DBG_EN
#define VENUS_GPIO_DBG(fmt, args...)          printk("[GPIO] Dbg, " fmt, ## args)
#define VENUS_GPIO_INFO(fmt, args...)         printk("[GPIO] Info, " fmt, ## args)
#else
#define VENUS_GPIO_DBG(fmt, args...) 
#define VENUS_GPIO_INFO(fmt, args...)         
#endif

#define VENUS_GPIO_WARNING(fmt, args...)      printk("[GPIO] Warning, " fmt, ## args)
    
    
#endif //__VENUS_GPIO_H__
