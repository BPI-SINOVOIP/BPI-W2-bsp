/*
 * scd_mars_priv.h - smartcard driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 */

#ifndef __SCD_MARS_PRIV_H__
#define __SCD_MARS_PRIV_H__

#include <linux/wait.h>
#include <linux/timer.h>
#include <linux/spinlock.h>
#include <linux/kfifo.h>
#include <soc/realtek/venus_gpio.h>
#include "../core/scd.h"
#include "../core/scd_atr.h"

#define ID_MARS_SCD(x)          (0x12830000 | (x & 0x3))
#define MARS_SCD_CHANNEL(id)    (id & 0x03)

#define MISC_IRQ        3
#define RX_RING_LENGTH  32
#define TX_RING_LENGTH  32


typedef enum {    
    IFD_FSM_UNKNOWN,
    IFD_FSM_DISABLE,        // function disabled
    IFD_FSM_DEACTIVATE,     // function enabled but not reset the card yet
    IFD_FSM_RESET,          // reset the card and waiting for ATR
    IFD_FSM_ACTIVE,         // card activated
}IFD_FSM; 

//#define ISR_POLLING

struct clk;
struct reset_control;

typedef struct mars_dts_info
{
    //void __iomem        *crt;
    //void __iomem        *padmux;
    void __iomem        *misc;
    void __iomem        *base;
#if 0
    void __iomem        *crt;
    void __iomem        *pinmux;
    void __iomem        *gpio;
#endif
    unsigned int        irq;
    unsigned int        id;
    unsigned char       cmd_vcc_en;
    unsigned char       cmd_vcc_polarity;
    unsigned char       pwr_sel_en;
    unsigned char       pwr_sel_polarity;
    VENUS_GPIO_ID       pin_cmd_vcc;         // command vcc
    VENUS_GPIO_ID       pin_pwr_sel;         // power sel

    struct clk *clk;
    struct reset_control *rstc;
}MARS_DTS_INFO_T;

typedef struct mars_scd_tag   mars_scd;

struct mars_scd_tag
{    
    unsigned int        id;         // channel id      
    void __iomem 	    *base;
    unsigned int	    irq;  
    IFD_FSM             fsm;        // finate state machine of ifd
	unsigned char       card_status_change;
	unsigned char       tx_status;
	#define SC_TX_DONE          0x1	
	#define SC_TX_PARITY_ERROR  0x2
    
    // config
    unsigned char       clock_div;          // clock divider
    unsigned char       pre_clock_div;      // pre_clock divider
    unsigned long       baud_div1; 
    unsigned long       baud_div2;    
    unsigned char       parity;
    
    unsigned char       vcc_5v : 1;
    unsigned char       cmd_vcc_en : 1;
    unsigned char       cmd_vcc_polarity : 1;
    unsigned char       pwr_sel_en : 1;    
    unsigned char       pwr_sel_polarity : 1;
    VENUS_GPIO_ID       pin_cmd_vcc;         // command vcc
    VENUS_GPIO_ID       pin_pwr_sel;         // power sel    

	// atr              
	scd_atr             atr;               // current atr
	scd_atr_info        atr_info;          // current atr
	unsigned long       atr_timeout;
	    
    wait_queue_head_t   wq;
    struct kfifo        rx_fifo;
    struct kfifo        tx_fifo;
    spinlock_t          rx_fifo_lock;
    
#ifdef ISR_POLLING    
    struct timer_list   timer;
#endif

    spinlock_t          lock;
    struct list_head    list;	
};

typedef enum {
    CTL_DISABLE = 0,
    CTL_ENABLE  = 1
} SCD_CLK_CTL;

extern mars_scd* mars_scd_open(unsigned char id);
extern void mars_scd_close(mars_scd* p_this);

extern int mars_scd_enable           (mars_scd* p_this, unsigned char on_off);       
extern int mars_scd_set_clock        (mars_scd* p_this, unsigned long clock);
extern int mars_scd_set_etu          (mars_scd* p_this, unsigned long etu);
extern int mars_scd_set_parity       (mars_scd* p_this, SC_PARITY parity);

extern int mars_scd_get_clock        (mars_scd* p_this, unsigned long* p_clock);
extern int mars_scd_get_etu          (mars_scd* p_this, unsigned long* p_etu);
extern int mars_scd_get_parity       (mars_scd* p_this, SC_PARITY* p_parity);

extern int mars_scd_set_bwi(mars_scd* p_this, unsigned long bwi);
extern int mars_scd_get_bwi(mars_scd* p_this, unsigned long* p_bwi);
extern int mars_scd_set_cwi(mars_scd* p_this, unsigned long cwi);
extern int mars_scd_get_cwi(mars_scd* p_this, unsigned long* p_cwi);
extern int mars_scd_set_guard_interval(mars_scd* p_this, unsigned long guard_interval);
extern int mars_scd_get_guard_interval(mars_scd* p_this, unsigned long* p_guard_interval);

static int inline mars_scd_set_vcc_lvl(mars_scd* p_this, SC_VCC_LVL lvl)
{        
    p_this->vcc_5v = (lvl==SC_VCC_5V) ? 1 : 0;
    return SC_SUCCESS;
}

static int inline mars_scd_get_vcc_lvl(mars_scd* p_this, SC_VCC_LVL* p_lvl)
{
    *p_lvl = (p_this->vcc_5v) ? SC_VCC_5V : SC_VCC_3V;
    return SC_SUCCESS;
}

static int inline mars_scd_set_convention(mars_scd* p_this, SC_CONV conv)
{    
    return SC_SUCCESS;
}

static int inline mars_scd_get_convention(mars_scd* p_this, SC_CONV* p_conv)
{
    *p_conv = SC_AUTO_CONV;
    return SC_SUCCESS;
}

extern int mars_scd_activate         (mars_scd* p_this);         
extern int mars_scd_deactivate       (mars_scd* p_this);         
extern int mars_scd_reset            (mars_scd* p_this);         
extern int mars_scd_get_atr          (mars_scd* p_this, scd_atr* p_atr);    
extern int mars_scd_card_detect      (mars_scd* p_this);
extern int mars_scd_get_card_status  (mars_scd* p_this);
extern int mars_scd_poll_card_status (mars_scd* p_this);
extern int mars_scd_xmit             (mars_scd* p_this, unsigned char* p_data, unsigned int len);    		    
extern int mars_scd_read             (mars_scd* p_this, unsigned char* p_data, unsigned int len);
    
#endif //__SCD_MARS_PRIV_H__
