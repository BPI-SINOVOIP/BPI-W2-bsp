/*
 * scd_gpio_priv.h - smartcard driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 */

#ifndef __SCD_GPIO_PRIV_H__
#define __SCD_GPIO_PRIV_H__

#include <linux/wait.h>
#include <linux/timer.h>
#include <linux/interrupt.h>
#include <linux/kfifo.h>
#include <asm/mach-rtk_dmp/venus_gpio.h>
#include "../core/scd.h"
#include "../core/scd_atr.h"

#define ID_MARS_SCD(x)          (0x12830000 | (x & 0x3))
#define RX_RING_LENGTH  32
#define TX_RING_LENGTH  32

#define USE_TDA8024

typedef enum {    
    IFD_FSM_UNKNOWN,
    IFD_FSM_DISABLE,        // function disabled
    IFD_FSM_DEACTIVATE,     // function enabled but not reset the card yet
    IFD_FSM_RESET,          // reset the card and waiting for ATR
    IFD_FSM_ACTIVATE,       // reset the card and waiting for ATR   
}IFD_FSM; 



typedef struct gpio_scd_tag   gpio_scd;

struct gpio_scd_tag
{    
    unsigned char       id;         // channel id       
    IFD_FSM             fsm;        // finate state machine of ifd
    unsigned long       event;
    unsigned char       card_status_change;    
    
    //pin assignment    
    VENUS_GPIO_ID       pin_card_detect;     // card detect pin
    VENUS_GPIO_ID       pin_reset;           // reset pin
    VENUS_GPIO_ID       pin_uart_tx;         
    VENUS_GPIO_ID       pin_uart_rx;         
    VENUS_GPIO_ID       pin_clk;             // clock
#ifdef USE_TDA8024    
    VENUS_GPIO_ID       pin_cmd_vcc;         // command vcc
    VENUS_GPIO_ID       pin_power_sel;       // power sel
#endif
    int                 pwm_id;              // pwm pin
    
    unsigned char       clock_en : 1;   
    unsigned char       auto_conv_en : 1;  
    unsigned char       vcc_5v_en : 1;  
    unsigned long       clock_freq;     
    
    // config               
    unsigned long       etu;    
    SC_PARITY           parity;
    SC_CONV             conv;   
            
    // atr              
    scd_atr             atr;               // current atr
    scd_atr_info        atr_info;          // current atr
    unsigned long       atr_timeout;    
    // tx queue
    wait_queue_head_t       wq;
    struct kfifo            rx_fifo;
    spinlock_t              rx_fifo_lock;	    
    struct tasklet_struct   rx_task;         
    struct kfifo            tx_fifo;
    spinlock_t              tx_fifo_lock;	          
        
    struct timer_list   timer;	                
    spinlock_t          lock;	    
};

extern gpio_scd* gpio_scd_open(unsigned char id);
extern void gpio_scd_close(gpio_scd* p_this);

extern int gpio_scd_enable            (gpio_scd* p_this, unsigned char on_off);       
extern int gpio_scd_set_clock         (gpio_scd* p_this, unsigned long clock);
extern int gpio_scd_set_etu           (gpio_scd* p_this, unsigned long etu);
static int gpio_scd_set_vcc_lvl       (gpio_scd* p_this, SC_VCC_LVL lvl);
extern int gpio_scd_set_parity        (gpio_scd* p_this, SC_PARITY parity);
extern int gpio_scd_set_convention    (gpio_scd* p_this, SC_CONV conv);

static int inline gpio_scd_get_clock(gpio_scd* p_this, unsigned long* p_clock)
{
    *p_clock = p_this->clock_freq;
    return SC_SUCCESS;
}

static int inline gpio_scd_get_etu(gpio_scd* p_this, unsigned long* p_etu)
{    
    *p_etu = p_this->etu; 
    return SC_SUCCESS;   
}

static int inline gpio_scd_get_parity(gpio_scd* p_this, SC_PARITY* p_parity)
{
    *p_parity = p_this->parity;
    return SC_SUCCESS;
}

static int inline gpio_scd_get_convention(gpio_scd* p_this, SC_CONV* p_conv)
{
    *p_conv = (p_this->auto_conv_en) ? SC_AUTO_CONV : p_this->conv;
    return SC_SUCCESS;
}

static int inline gpio_scd_set_vcc_lvl(gpio_scd* p_this, SC_VCC_LVL lvl)
{
    p_this->vcc_5v_en = (lvl==SC_VCC_5V) ? 1 : 0;
    return SC_SUCCESS;
}

static int inline gpio_scd_get_vcc_lvl(gpio_scd* p_this, SC_VCC_LVL* p_lvl)
{
    *p_lvl = (p_this->vcc_5v_en) ? SC_VCC_5V : SC_VCC_3V;
    return SC_SUCCESS;             
}

extern int gpio_scd_activate          (gpio_scd* p_this);         
extern int gpio_scd_deactivate        (gpio_scd* p_this);         
extern int gpio_scd_reset             (gpio_scd* p_this);        
extern int gpio_scd_get_atr           (gpio_scd* p_this, scd_atr* p_atr); 
extern int gpio_scd_card_detect       (gpio_scd* p_this);
extern int gpio_scd_get_card_status   (gpio_scd* p_this);
extern int gpio_scd_poll_card_status  (gpio_scd* p_this);
extern int gpio_scd_xmit              (gpio_scd* p_this, unsigned char* p_data, unsigned int len);    		    
extern int gpio_scd_read              (gpio_scd* p_this, unsigned char* p_data, unsigned int len);

////////////////////////////////////////////////
// Internal APIs
////////////////////////////////////////////////

typedef enum {
    SCD_IO_OFF,
    SCD_IO_RECV,
    SCD_IO_XMIT,
}SCD_IO_MODE;

int  _gpio_scd_io_init(gpio_scd* p_this);
void _gpio_scd_io_uninit(gpio_scd* p_this);
void _gpio_scd_io_mode(gpio_scd* p_this, SCD_IO_MODE mode);
void _gpio_scd_io_config(gpio_scd* p_this);

int  _gpio_scd_card_detect_init(gpio_scd* p_this);
void _gpio_scd_card_detect_uninit(gpio_scd* p_this);
void _gpio_scd_card_detect_enable(gpio_scd* p_this, unsigned char on);
int  _gpio_scd_card_detect_status(gpio_scd* p_this);

int  _gpio_scd_reset_init(gpio_scd* p_this);
void _gpio_scd_reset_uninit(gpio_scd* p_this);
void _gpio_scd_reset(gpio_scd* p_this, unsigned char on);

int  _gpio_scd_clock_init(gpio_scd* p_this);
int  _gpio_scd_clock_config(gpio_scd* p_this);
int  _gpio_scd_clock_enable(gpio_scd* p_this, unsigned char on);

int  _gpio_scd_vcc_init(gpio_scd* p_this);
int  _gpio_scd_vcc_enable(gpio_scd* p_this, unsigned char on);

int  _gpio_scd_pwrsel_init(gpio_scd* p_this);
int  _gpio_scd_pwrsel(gpio_scd* p_this, unsigned char power);


#endif //__SCD_MARS_PRIV_H__
