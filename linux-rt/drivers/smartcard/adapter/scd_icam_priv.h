/*
 * scd_icam_priv.h - smartcard driver
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
#include "../core/scd.h"
#include "../core/scd_atr.h"
#include <asm/mach-rtk_dmp/venus_gpio.h>

#define ICAM_SCD_ID          (0x4943414D)

#define MISC_IRQ        3
#define RX_RING_LENGTH  32
#define TX_RING_LENGTH  32


#define LOWEST_CLOCK      4500000
#define MEDIUM_CLOCK      6750000
#define HIGHEST_CLOCK    13500000

typedef enum {    
    IFD_FSM_UNKNOWN,
    IFD_FSM_DISABLE,        // function disabled
    IFD_FSM_DEACTIVATE,     // function enabled but not reset the card yet
    IFD_FSM_RESET,          // reset the card and waiting for ATR
    IFD_FSM_ACTIVE,         // card activated
}IFD_FSM; 


//#define ISR_POLLING

typedef struct icam_scd_tag   icam_scd;

struct icam_scd_tag
{    
    unsigned char       id;         // channel id       
    IFD_FSM             fsm;        // finate state machine of ifd
	unsigned char       card_status_change;
    
    // config           
    unsigned char       cmd_vcc_polarity : 1;    
    unsigned char       pwr_sel_polarity : 1;        
    unsigned long       uart_ctrl;  
    unsigned long       vcc_sel;
    unsigned long       etu;
    unsigned char       guard_time;
    
	// atr              
	scd_atr             atr;               // current atr
	scd_atr_info        atr_info;          // current atr
	unsigned long       atr_timeout;
	    
    wait_queue_head_t   wq;
    struct kfifo        rx_fifo;
    spinlock_t          rx_fifo_lock;    
    spinlock_t          lock;	
};

extern icam_scd* icam_scd_open(void);
extern void icam_scd_close(icam_scd* p_this);

extern int icam_scd_enable           (icam_scd* p_this, unsigned char on_off);       
extern int icam_scd_set_clock        (icam_scd* p_this, unsigned long clock);
extern int icam_scd_get_clock        (icam_scd* p_this, unsigned long* p_clock);

extern int icam_scd_set_etu          (icam_scd* p_this, unsigned long etu);
extern int icam_scd_get_etu          (icam_scd* p_this, unsigned long* p_etu);

extern int icam_scd_set_vcc          (icam_scd* p_this, unsigned char on);
extern int icam_scd_set_vcc_level    (icam_scd* p_this, SC_VCC_LVL lvl);
extern int icam_scd_get_vcc_level    (icam_scd* p_this, SC_VCC_LVL* p_lvl);

extern int icam_scd_set_convention   (icam_scd* p_this, SC_CONV conv);
extern int icam_scd_get_convention   (icam_scd* p_this, SC_CONV* p_conv);

extern int icam_scd_set_guard_interval(icam_scd* p_this, unsigned long guard_interval);
extern int icam_scd_get_guard_interval(icam_scd* p_this, unsigned long* p_guard_interval);

extern int icam_scd_set_flow_control(icam_scd* p_this, unsigned char on);

extern int icam_scd_set_uart_command(icam_scd* p_this, unsigned long io_mask);
extern int icam_scd_get_uart_command(icam_scd* p_this, unsigned long* p_io_mask);

extern int icam_scd_activate         (icam_scd* p_this);         
extern int icam_scd_deactivate       (icam_scd* p_this);         
extern int icam_scd_reset            (icam_scd* p_this);         
extern int icam_scd_get_atr          (icam_scd* p_this, scd_atr* p_atr);    
extern int icam_scd_card_detect      (icam_scd* p_this);
extern int icam_scd_get_card_status  (icam_scd* p_this);
extern int icam_scd_poll_card_status (icam_scd* p_this);
extern int icam_scd_xmit             (icam_scd* p_this, unsigned char* p_data, unsigned int len);    		    
extern int icam_scd_read             (icam_scd* p_this, unsigned char* p_data, unsigned int len);
    
#endif //__SCD_MARS_PRIV_H__
