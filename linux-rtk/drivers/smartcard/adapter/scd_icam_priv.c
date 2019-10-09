/* ------------------------------------------------------------------------- 
   scd_icam.c  scd driver for Realtek Nike ICAM
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
#include <platform.h>
#include <asm/mach-rtk_dmp/platform.h>
#include <nike.h>
#include "scd_icam_priv.h"

MODULE_LICENSE("GPL");


#define SA_SHIRQ IRQF_SHARED
#define ICAM_IRQ 5

#define _readl(x)                      readl(x) 
//#define _writel(x,y)                   do { printk("wr_reg(%lx)=%lx\n", y, x); writel(x,y);} while(0)
#define _writel(x,y)                   writel(x,y) 
#define GET_NDS_SC_CKSEL(h)            readl((volatile unsigned int*)(NIKE_IO_PORT_BASE + NIKE_NDS_SC_CKSEL))
#define SET_NDS_SC_CKSEL(h,v)          _writel(v, (volatile unsigned int*)(NIKE_IO_PORT_BASE + NIKE_NDS_SC_CKSEL))

#define GET_ICAM_UART_DATA(h)          readl((volatile unsigned int*)(NIKE_IO_PORT_BASE + NIKE_ICAM_UART_DATA))        
#define GET_ICAM_UART_CTRL_STAT(h)     readl((volatile unsigned int*)(NIKE_IO_PORT_BASE + NIKE_ICAM_UART_CTRL_STAT))
#define GET_ICAM_UART_BAUD_RATE_L(h)   readl((volatile unsigned int*)(NIKE_IO_PORT_BASE + NIKE_ICAM_UART_BAUD_RATE_L))   
#define GET_ICAM_UART_BAUD_RATE_H(h)   readl((volatile unsigned int*)(NIKE_IO_PORT_BASE + NIKE_ICAM_UART_BAUD_RATE_H))  
#define GET_ICAM_UART_COM(h)           readl((volatile unsigned int*)(NIKE_IO_PORT_BASE + NIKE_ICAM_UART_COM))           
#define GET_ICAM_UART_INT(h)           readl((volatile unsigned int*)(NIKE_IO_PORT_BASE + NIKE_ICAM_UART_INT))            
#define GET_ICAM_UART_GUARD_TIME(h)    readl((volatile unsigned int*)(NIKE_IO_PORT_BASE + NIKE_ICAM_UART_GUARD_TIME))
#define SET_ICAM_UART_DATA(h,v)        _writel(v, (volatile unsigned int*)(NIKE_IO_PORT_BASE + NIKE_ICAM_UART_DATA))        
#define SET_ICAM_UART_CTRL_STAT(h,v)   _writel(v, (volatile unsigned int*)(NIKE_IO_PORT_BASE + NIKE_ICAM_UART_CTRL_STAT))
#define SET_ICAM_UART_BAUD_RATE_L(h,v) _writel(v, (volatile unsigned int*)(NIKE_IO_PORT_BASE + NIKE_ICAM_UART_BAUD_RATE_L))   
#define SET_ICAM_UART_BAUD_RATE_H(h,v) _writel(v, (volatile unsigned int*)(NIKE_IO_PORT_BASE + NIKE_ICAM_UART_BAUD_RATE_H))  
#define SET_ICAM_UART_COM(h,v)         _writel(v, (volatile unsigned int*)(NIKE_IO_PORT_BASE + NIKE_ICAM_UART_COM))           
#define SET_ICAM_UART_INT(h,v)         _writel(v, (volatile unsigned int*)(NIKE_IO_PORT_BASE + NIKE_ICAM_UART_INT))            
#define SET_ICAM_UART_GUARD_TIME(h,v)  _writel(v, (volatile unsigned int*)(NIKE_IO_PORT_BASE + NIKE_ICAM_UART_GUARD_TIME))



#define NDS_CLOCK_SOURCE        27000000
#define NDS_ICAM_SYSTEM_CLOCK   202500000
#define IFD_MODOLE              "NIKE_ICAM_SMC"
    
#ifdef ISR_POLLING  
#define ISR_POLLING_INTERVAL        (HZ>>2)
static void icam_scd_timer(unsigned long arg);
#endif




/*------------------------------------------------------------------
 * Func : icam_scd_set_state
 *
 * Desc : 
 *
 * Parm : p_this : handle of icam smartcard ifd 
 *         
 * Retn : N/A  
 *------------------------------------------------------------------*/
int icam_scd_set_state(
    icam_scd*               p_this, 
    IFD_FSM                 fsm
    )
{
    unsigned char id = p_this->id;
    
    if (p_this->fsm == fsm)
        return 0;
        
    switch(fsm)
    {       
    case IFD_FSM_DISABLE:        
        SC_INFO("SC%d - FSM = DISABLE\n", id);
        icam_scd_set_vcc(p_this, 0);    
        icam_scd_set_vcc_level(p_this, SC_VCC_3V);
        icam_scd_set_clock(p_this, LOWEST_CLOCK);       
        icam_scd_set_etu(p_this, 372);
        icam_scd_set_convention(p_this, SC_DIRECT_CONV);
        icam_scd_set_guard_interval(p_this, 2);
        SET_ICAM_UART_INT(p_this, GET_ICAM_UART_INT(p_this) | ICAM_UART_RESET_INT);       // clear interrupts        
        SET_ICAM_UART_INT(p_this, 0);
        p_this->atr.length = 0;         
        break;
        
    case IFD_FSM_DEACTIVATE:        
        SC_INFO("SC%d - FSM = IDEL\n", id);                                      
        icam_scd_set_vcc(p_this, 0);
        p_this->atr.length = 0;
        kfifo_reset(&p_this->rx_fifo);
        SET_ICAM_UART_INT(p_this, GET_ICAM_UART_INT(p_this) | ICAM_UART_RESET_INT);       // clear interrupts        
        SET_ICAM_UART_INT(p_this, ICAM_UART_INT_DETECT);     // start card detect        
        break;
        
    case IFD_FSM_RESET:      
               
        p_this->atr.length = 0;
                                            
        if (!icam_scd_card_detect(p_this))
        {
            SC_WARNING("SC%d - RESET icam scd failed, no ICC exist\n", id);                            
            icam_scd_set_state(p_this, IFD_FSM_DEACTIVATE);
            return SC_ERR_NO_ICC;
        }
                                    
        kfifo_reset(&p_this->rx_fifo);
        
        icam_scd_set_etu(p_this, 372);
        icam_scd_set_vcc(p_this, 1);
                
        SET_ICAM_UART_CTRL_STAT(p_this, p_this->uart_ctrl); 
        
        SET_ICAM_UART_INT(p_this, ICAM_UART_INT_RX | ICAM_UART_RX_OVERFLOW | ICAM_UART_RX_PARITY_ERR | 
                                  ICAM_UART_INT_DETECT);
        udelay(100);        
        SET_ICAM_UART_INT(p_this, GET_ICAM_UART_INT(p_this) | ICAM_UART_RESET_INT);       // clear interrupts                
        SET_ICAM_UART_CTRL_STAT(p_this, p_this->uart_ctrl | ICAM_UART_CTRL_RESET_MASK);
        p_this->atr_timeout = jiffies + HZ;                            
        SC_INFO("SC%d - FSM = RESET & ATR\n", id);        
        break;
        
    case IFD_FSM_ACTIVE:
        
        SC_INFO("SC%d - FSM = ACTIVATE\n", id);        
        SET_ICAM_UART_INT(p_this, ICAM_UART_INT_RX | ICAM_UART_RX_OVERFLOW | ICAM_UART_RX_PARITY_ERR | 
                                  ICAM_UART_INT_DETECT);        
        break;

    default:
    case IFD_FSM_UNKNOWN:
        break;                    
    }    
    
    p_this->fsm = fsm;             
    
    p_this->card_status_change = 1;    
    wake_up(&p_this->wq);             
    
    return 0;
}



/*------------------------------------------------------------------
 * Func : icam_scd_work
 *
 * Desc : icam scd work routine
 *
 * Parm : p_this : handle of icam cec 
 *         
 * Retn : N/A  
 *------------------------------------------------------------------*/
void icam_scd_work(icam_scd* p_this)
{
    unsigned long status = GET_ICAM_UART_INT(p_this);      
    unsigned char val; 

    
    
    SET_ICAM_UART_INT(p_this, status | ICAM_UART_RESET_INT);       // clear interrupts        
                
    if (status & ICAM_UART_STATUS_RX_READY)      
    {
        val = GET_ICAM_UART_DATA(p_this);
        //SC_INFO("SC%d - Read %02x!!\n", p_this->id, val); 
        
        //printk(KERN_DEBUG "%02x\n", val);
        
        if (p_this->uart_ctrl & ICAM_UART_CTRL_MANUAL_FLOW_CTRL_ON)
        {
            SET_ICAM_UART_CTRL_STAT(p_this, p_this->uart_ctrl &~ICAM_UART_CTRL_MANUAL_FLOW_CTRL_ON);             
            SET_ICAM_UART_CTRL_STAT(p_this, p_this->uart_ctrl | ICAM_UART_CTRL_MANUAL_FLOW_CTRL_ON); 
        }
        
        switch (p_this->fsm)
        {       
        case IFD_FSM_RESET:
            
            if (p_this->atr.length >= MAX_ATR_SIZE)
                goto err_atr_failed;
                                      
            p_this->atr.data[p_this->atr.length] = val;
                    
            if (p_this->atr.length==0)
            {                
                switch(p_this->atr.data[0])
                {
                case 0x3B:
                    //SC_INFO("SC%d - Direct Convention (%02x)\n", p_this->id, p_this->atr.data[0]);
                    p_this->atr.length++;
                    break;
                    
                case 0x3F:
                    p_this->atr.data[0] = 0x3F;
                    //SC_INFO("SC%d - Inverse Convention (%02x)\n", p_this->id, p_this->atr.data[0]);
                    p_this->atr.length++;
                    break;
                                
                default:
                    //SC_WARNING("SC%d - unknown TS (%02x)\n", p_this->id, p_this->atr.data[0]);
                    break;                     
                }                   
            }
            else                
                p_this->atr.length++;
                    
            SC_INT_DBG("p_this->atr.length=%d\n", p_this->atr.length);
            
            // check atr 
            if (is_atr_complete(&p_this->atr))
            {            
                SC_INFO("SC%d - Got ATR Completed\n", p_this->id);
                
                if (decompress_atr(&p_this->atr, &p_this->atr_info)<0)
                    goto err_atr_failed;                                                           
    
                icam_scd_set_state(p_this, IFD_FSM_ACTIVE);       // jump to active state
            }

            break;            
            
        case IFD_FSM_ACTIVE:
            
            if (kfifo_in_locked(&p_this->rx_fifo, &val, 1, &p_this->rx_fifo_lock)<1)
            {
                SC_WARNING("icam_scd_fsm_active : fifo over flow... flush data...\n");   
                kfifo_reset(&p_this->rx_fifo);
            }
            break;
            
        default:
            break;
        }
    }
    
    if (status & ICAM_UART_INT_DETECT)            
    {           
        if (icam_scd_card_detect(p_this)) 
        {
            SC_INFO("SC%d - ICC detected!!\n", p_this->id);             
        }
        else 
        {
            icam_scd_set_state(p_this, IFD_FSM_DEACTIVATE);
            SC_INFO("SC%d - ICC removed!!\n", p_this->id);              
        }
            
        p_this->card_status_change = 1;            
        wake_up(&p_this->wq);           
    }
    
    if (status & ICAM_UART_RX_OVERFLOW)
    {
        SC_INFO("SC%d - Rx Overflow!!\n", p_this->id); 
    }
    
    if (status & ICAM_UART_TX_PARITY_ERR)
    {
        SC_INFO("SC%d - Tx Parity Error!!\n", p_this->id); 
    }
    
    if (status & ICAM_UART_RX_PARITY_ERR)
    {
        SC_INFO("SC%d - Rx Parity Error!!\n", p_this->id); 
    }
        
    return;
    
//---------------------------    
err_atr_failed:
    
    if (time_after(jiffies, p_this->atr_timeout))
    {        
        SC_WARNING("SC%d - RESET ICC failed, timeout\n", p_this->id);                   
    }    
    
    if (p_this->atr.length <0)
    {
        SC_WARNING("SC%d - RESET ICC failed, wait ATR failed\n", p_this->id); 
    }
    else if (p_this->atr.length >= MAX_ATR_SIZE)
    {
        SC_WARNING("SC%d - RESET ICC failed, atr length %d more then %d\n", p_this->id, p_this->atr.length, MAX_ATR_SIZE); 
    }
    else if (!is_atr_complete(&p_this->atr))
    {
        SC_WARNING("SC%d - RESET ICC failed, incomplete atr\n", p_this->id); 
    }
    else if (decompress_atr(&p_this->atr, &p_this->atr_info)<0)
    {
        SC_WARNING("SC%d - RESET ICC failed, decompress atr failed\n", p_this->id); 
    }
    else
    {
        SC_WARNING("SC%d - RESET ICC failed, parse protocol faield\n", p_this->id); 
    }
                                                                
    icam_scd_set_state(p_this, IFD_FSM_DEACTIVATE);    
}



#ifdef ISR_POLLING     
/*------------------------------------------------------------------
 * Func : icam_scd_timer
 *
 * Desc : timer of icam scd
 *
 * Parm : arg : input param 
 *         
 * Retn : IRQ_NONE, IRQ_HANDLED
 *------------------------------------------------------------------*/
static void icam_scd_timer(unsigned long arg)        
{   
    icam_scd* p_this = (icam_scd*) arg;                   

    if (GET_ICAM_UART_INT(p_this))           
        icam_scd_work(p_this);
        
    mod_timer(&p_this->timer, jiffies + ISR_POLLING_INTERVAL);
}

#else


/*------------------------------------------------------------------
 * Func : icam_scd_isr
 *
 * Desc : isr of icam scd
 *
 * Parm : p_this : handle of icam scd 
 *        dev_id : handle of the icam_scd
 *        regs   :
 *         
 * Retn : IRQ_NONE, IRQ_HANDLED
 *------------------------------------------------------------------*/
static irqreturn_t
icam_scd_isr(
    int                     this_irq, 
    void*                   dev_id
    )
{   
    icam_scd* p_this = (icam_scd*) dev_id;
    unsigned long flag;                     
         
    spin_lock_irqsave(&p_this->lock, flag);         

    icam_scd_work(p_this);        
                                          
    spin_unlock_irqrestore(&p_this->lock, flag);                               
                      
    return IRQ_HANDLED;    
}


#endif




/*------------------------------------------------------------------
 * Func : icam_scd_enable
 *
 * Desc : enable icam smart card interface
 *
 * Parm : p_this   : handle of icam scd  
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int icam_scd_enable(icam_scd* p_this, unsigned char on_off)
{
    int ret = 0;
    if (on_off)        
    {
        if (p_this->fsm==IFD_FSM_DISABLE)
        {
            ret =  icam_scd_set_state(p_this, IFD_FSM_DEACTIVATE);
            msleep(200);   // fix bug of get card status fail on darwin platform....
        }
    }
    else    
        ret =  icam_scd_set_state(p_this, IFD_FSM_DISABLE);    
    
    return ret;
}



/*------------------------------------------------------------------
 * Func : icam_scd_set_vcc
 *
 * Desc : enable/disable vcc output
 *
 * Parm : p_this   : handle of icam scd  
 *        clk      : clock (in HZ)
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int icam_scd_set_vcc(icam_scd* p_this, unsigned char on)
{
    if (on)
    {
        p_this->uart_ctrl &= ~(ICAM_UART_CTRL_VCC_MASK | ICAM_UART_CTRL_3V5V_MASK);
        p_this->uart_ctrl |=  (ICAM_UART_CTRL_VCC_ON | p_this->vcc_sel);
    }
    else
    {            
        p_this->uart_ctrl &= ~(ICAM_UART_CTRL_VCC_MASK|ICAM_UART_CTRL_3V5V_MASK);        
        p_this->uart_ctrl |=  (ICAM_UART_CTRL_VCC_OFF | p_this->vcc_sel);                    
    }
    
    SC_INFO("icam_scd_set_vcc=%d, uart_ctrl=%lx\n", on, p_this->uart_ctrl);
    SET_ICAM_UART_CTRL_STAT(p_this, p_this->uart_ctrl);     
   
    return 0;
}



/*------------------------------------------------------------------
 * Func : icam_scd_set_vcc_level
 *
 * Desc : set vcc output level
 *
 * Parm : p_this   : handle of icam scd  
 *        vcc_5v   : clock (in HZ)
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int icam_scd_set_vcc_level(icam_scd* p_this, SC_VCC_LVL lvl)
{     
    p_this->vcc_sel = (lvl==SC_VCC_5V) ? ICAM_UART_CTRL_3V5V_OFF : ICAM_UART_CTRL_3V5V_ON;    
    return 0;
}


/*------------------------------------------------------------------
 * Func : icam_scd_get_vcc_level
 *
 * Desc : get vcc output level
 *
 * Parm : p_this   : handle of icam scd  
 *        vcc_5v   : clock (in HZ)
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int icam_scd_get_vcc_level(icam_scd* p_this, SC_VCC_LVL* p_lvl)
{     
    *p_lvl = (p_this->vcc_sel==ICAM_UART_CTRL_3V5V_OFF) ? SC_VCC_5V : SC_VCC_3V;     
    return 0;
}



/*------------------------------------------------------------------
 * Func : icam_scd_set_convention
 *
 * Desc : set convention
 *
 * Parm : p_this   : handle of icam scd  
 *        conv     : conv
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int icam_scd_set_convention(icam_scd* p_this, SC_CONV convention)
{
    switch (convention)
    {
    case SC_INVERSE_CONV:
        SC_INFO("Set Convention = Inverse\n");        
        p_this->uart_ctrl &= ~ICAM_UART_CTRL_CONV_MASK;
        p_this->uart_ctrl |=  ICAM_UART_CTRL_INVERSE_CONV;  
        break;   
            
    case SC_AUTO_CONV:                
    case SC_DIRECT_CONV:    
        SC_INFO("Set Convention = Direct\n");
        p_this->uart_ctrl &= ~ICAM_UART_CTRL_CONV_MASK;
        p_this->uart_ctrl |=  ICAM_UART_CTRL_DIRECT_CONV;                   
        break;
        
    default:
        SC_WARNING("unkonwn convention %d\n", convention);
        return -1;                            
    }   
        
    SC_INFO("icam_scd_set_convention=%d, uart_ctrl=%lx\n", convention, p_this->uart_ctrl);
        
    SET_ICAM_UART_CTRL_STAT(p_this, p_this->uart_ctrl);    
    return 0;
}



/*------------------------------------------------------------------
 * Func : icam_scd_get_convention
 *
 * Desc : get convention
 *
 * Parm : p_this   : handle of icam scd  
 *        p_conv   : convention output
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int icam_scd_get_convention(icam_scd* p_this, SC_CONV* p_conv)
{    
    *p_conv = ((p_this->uart_ctrl & ICAM_UART_CTRL_CONV_MASK)==ICAM_UART_CTRL_DIRECT_CONV) ? SC_DIRECT_CONV : SC_INVERSE_CONV;      
    printk("*p_conv=%d\n", *p_conv);
    return 0;
}



/*------------------------------------------------------------------
 * Func : icam_scd_set_clock
 *
 * Desc : set clock frequency of icam smart card interface
 *
 * Parm : p_this   : handle of icam scd  
 *        clk      : clock (in HZ)
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int icam_scd_set_clock(icam_scd* p_this, unsigned long clk)
{
    switch(clk)
    {
    case HIGHEST_CLOCK:
        SET_NDS_SC_CKSEL(p_this, NDS_SC_CKSEL_DIV_2);     // divided by 2
        break;
    case MEDIUM_CLOCK:
        SET_NDS_SC_CKSEL(p_this, NDS_SC_CKSEL_DIV_4);     // divided by 4
        break;        
    case LOWEST_CLOCK:
        SET_NDS_SC_CKSEL(p_this, NDS_SC_CKSEL_DIV_6);     // divided by 6
        break;
    default:
        SC_WARNING("unsupportted clock frequency - %lu\n", clk);
        return -1;
    }    
    
    icam_scd_set_etu(p_this, p_this->etu);  // update etu
    return 0;    
}



/*------------------------------------------------------------------
 * Func : icam_scd_get_clock
 *
 * Desc : get clock frequency of icam smart card interface
 *
 * Parm : p_this   : handle of icam scd  
 *        p_clock  : clock (in HZ)
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int icam_scd_get_clock(icam_scd* p_this, unsigned long* p_clock)
{    
    *p_clock = 0;
    switch(GET_NDS_SC_CKSEL(p_this))
    {
    case NDS_SC_CKSEL_DIV_2: *p_clock = NDS_CLOCK_SOURCE / 2; break;
    case NDS_SC_CKSEL_DIV_4: *p_clock = NDS_CLOCK_SOURCE / 4; break;                
    case NDS_SC_CKSEL_DIV_6: *p_clock = NDS_CLOCK_SOURCE / 6; break; 
    case NDS_SC_CKSEL_DIV_8: *p_clock = NDS_CLOCK_SOURCE / 8; break;          
    default:
        SC_WARNING("Get clock freq failed, unknown clock divisor - %d\n", GET_NDS_SC_CKSEL(p_this));
        return -1;
    }   
        
    return 0;
}



/*------------------------------------------------------------------
 * Func : icam_scd_set_etu
 *
 * Desc : set etu of icam smart card interface
 *
 * Parm : p_this   : handle of icam scd  
 *        etu      : cycles
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int icam_scd_set_etu(icam_scd* p_this, unsigned long etu)
{    
    unsigned long div;       
    unsigned long sclk;       
    
    icam_scd_get_clock(p_this, &sclk);
    div = (NDS_ICAM_SYSTEM_CLOCK/1000) * etu;
    div = div / (sclk/1000);
    
    if (div <2 || div > 0xFFFF)
    {
        SC_WARNING("Set etu failed, invalid divider - %lu\n", div);
        return -1;
    }                     
    
    p_this->etu = etu;                
    div -= 2;                
    SET_ICAM_UART_BAUD_RATE_H(p_this, (div >>8) & 0xFF);    
    SET_ICAM_UART_BAUD_RATE_L(p_this, (div) & 0xFF);        
    return 0;
}



/*------------------------------------------------------------------
 * Func : icam_scd_get_etu
 *
 * Desc : set etu of icam smart card interface
 *
 * Parm : p_this   : handle of icam scd  
 *        etu      : cycles
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int icam_scd_get_etu(icam_scd* p_this, unsigned long* p_etu)
{    
    *p_etu = p_this->etu;
    return 0;
}



/*------------------------------------------------------------------
 * Func : icam_scd_set_guard_interval
 *
 * Desc : set guard interval of icam smart card interface
 *
 * Parm : p_this   : handle of icam scd  
 *        guard_interval : guard interval in etu
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int icam_scd_set_guard_interval(icam_scd* p_this, unsigned long guard_interval)
{    
    if (guard_interval > 0xFF)
    {
        SC_WARNING("Set etu failed, invald guard interval - %lu\n", guard_interval);
        return -1;
    }         
    
    p_this->guard_time = (unsigned char) guard_interval;
        
    SET_ICAM_UART_GUARD_TIME(p_this, guard_interval);        
    return 0;
}



/*------------------------------------------------------------------
 * Func : icam_scd_get_guard_interval
 *
 * Desc : set guard interval
 *
 * Parm : p_this : handle of icam scd  
 *        p_guard_interval : guard interval output
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int icam_scd_get_guard_interval(icam_scd* p_this, unsigned long* p_guard_interval)
{    
    *p_guard_interval = p_this->guard_time;                        
    return 0;
}



/*------------------------------------------------------------------
 * Func : icam_scd_set_flow_control
 *
 * Desc : enable/disable flow control function
 *
 * Parm : p_this : handle of icam scd  
 *        on  : enable /disable flow control
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int icam_scd_set_flow_control(icam_scd* p_this, unsigned char on)
{    
    if (on)
        p_this->uart_ctrl |= ICAM_UART_CTRL_MANUAL_FLOW_CTRL_ON;
    else            
        p_this->uart_ctrl &=~ICAM_UART_CTRL_MANUAL_FLOW_CTRL_ON;
 
    SC_INFO("icam_scd_set_flow_control=%d, uart_ctrl=%lx\n", on, p_this->uart_ctrl);
 
    SET_ICAM_UART_CTRL_STAT(p_this, p_this->uart_ctrl);             
    return 0;
}



/*------------------------------------------------------------------
 * Func : icam_scd_set_uart_command
 *
 * Desc : set uart command function
 *
 * Parm : p_this : handle of icam scd  
 *        io_mask  : io mask
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int icam_scd_set_uart_command(icam_scd* p_this, unsigned long io_mask)
{    
    unsigned long io_mode = io_mask & SC_IO_CTRL_IO_MASK;
    unsigned long uart_cmd = 0;
        
    switch(io_mode)
    {
    case SC_IO_CTRL_IO_C7:
        
        uart_cmd = ICAM_UART_COM_MODE_IO_C7;        
        
        if (io_mask & SC_IO_CTRL_C7_ON) 
        {
            SC_WARNING("Set UART command failed, C7 can not be programed both as IO and GPIO\n");            
            return -1;
        }     
        
        if (io_mask & SC_IO_CTRL_C4_ON)
            uart_cmd |= ICAM_UART_COM_MODE_C4_ON;
            
        if (io_mask & SC_IO_CTRL_C8_ON)        
            uart_cmd |= ICAM_UART_COM_MODE_C8_ON;
        break;
        
    case SC_IO_CTRL_IO_C4:
        
        uart_cmd = ICAM_UART_COM_MODE_IO_C4;   
        
        if (io_mask & SC_IO_CTRL_C4_ON) 
        {
            SC_WARNING("Set UART command failed, C4 can not be programed both as IO and GPIO\n");            
            return -1;
        }   
                  
        break;
        
    case SC_IO_CTRL_IO_C8:   
             
        uart_cmd = ICAM_UART_COM_MODE_IO_C8; 
        
        if (io_mask & SC_IO_CTRL_C8_ON) 
        {
            SC_WARNING("Set UART command failed, C8 can not be programed both as IO and GPIO\n");            
            return -1;
        }                     
        break;            
        
    default:
        SC_WARNING("Set UART command failed, unknown io mode - %08lx\n", io_mode);
        return -1;
    }
    
    SET_ICAM_UART_COM(p_this, uart_cmd);                
    return 0;
}




/*------------------------------------------------------------------
 * Func : icam_scd_get_uart_command
 *
 * Desc : get uart command function
 *
 * Parm : p_this : handle of icam scd  
 *        p_io_mask : io mask output
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int icam_scd_get_uart_command(icam_scd* p_this, unsigned long* p_io_mask)
{    
    unsigned long uart_com = GET_ICAM_UART_COM(p_this);
    
    *p_io_mask = 0;    
    
    if (uart_com & ICAM_UART_COM_MODE_C4_ON)
        *p_io_mask |= SC_IO_CTRL_C4_ON;    
        
    if (uart_com & ICAM_UART_COM_MODE_C8_ON)
        *p_io_mask |= SC_IO_CTRL_C8_ON;  
                        
    switch (uart_com & ICAM_UART_COM_MODE_MASK)
    {
    case ICAM_UART_COM_MODE_IO_C7:
        *p_io_mask |= SC_IO_CTRL_IO_C7;  
        break;
        
    case ICAM_UART_COM_MODE_IO_C4:
        *p_io_mask |= SC_IO_CTRL_IO_C4;  
        break;
                
    case ICAM_UART_COM_MODE_IO_C8:
        *p_io_mask |= SC_IO_CTRL_IO_C8;  
        break;        
        
    default:        
        SC_WARNING("Get UART command failed, unknown io mode - %08lx\n", uart_com & ICAM_UART_COM_MODE_MASK);
        return -1;               
    }               
    
    return 0;
}



/*------------------------------------------------------------------
 * Func : icam_scd_activate
 *
 * Desc : activate an ICC
 *
 * Parm : p_this   : handle of icam scd  
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/        
int icam_scd_activate(icam_scd* p_this)
{    
    switch(p_this->fsm)
    {
    case IFD_FSM_DISABLE:
        SC_WARNING("activate ICC failed, please enable IFD first\n");
        return SC_ERR_IFD_DISABLED;
        
    case IFD_FSM_DEACTIVATE:        
    
        if (icam_scd_reset(p_this)==0)
        {
            SC_INFO("activate ICC success\n");
            return SC_SUCCESS;
        }
        else
        {
            SC_WARNING("activate ICC failed\n");
            return SC_ERR_NO_ICC;
        }
        break;            
        
    case IFD_FSM_RESET:
        SC_INFO("ICC has is reseting\n");
        return SC_SUCCESS;
        
    case IFD_FSM_ACTIVE:
        SC_INFO("ICC has been activated already\n");
        return SC_SUCCESS;
        
    default:        
        SC_WARNING("activate ICC failed, unknown state\n");
        return SC_FAIL;
    } 
}



/*------------------------------------------------------------------
 * Func : icam_scd_deactivate
 *
 * Desc : deactivate an ICC
 *
 * Parm : p_this   : handle of icam scd  
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/        
int icam_scd_deactivate(icam_scd* p_this)
{    
    if (p_this->fsm != IFD_FSM_DISABLE)
    {
        //icam_scd_set_state(p_this, IFD_FSM_DISABLE);
        icam_scd_set_state(p_this, IFD_FSM_DEACTIVATE);
    }
    return 0;
}




/*------------------------------------------------------------------
 * Func : icam_scd_reset
 *
 * Desc : reset icam smart card interface
 *
 * Parm : p_this   : handle of icam scd  
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/        
int icam_scd_reset(icam_scd* p_this)
{
    unsigned long t;
    
    if (icam_scd_set_state(p_this, IFD_FSM_RESET))
        return SC_FAIL;
    
    t = jiffies + (HZ);
    
    while(!time_after(jiffies,t) && p_this->fsm == IFD_FSM_RESET)    
        msleep(100);    
    
    if (p_this->fsm!=IFD_FSM_ACTIVE)
    {
        SC_WARNING("SC%d - Reset ICC failed\n", p_this->id);
        icam_scd_set_state(p_this, IFD_FSM_DEACTIVATE);
        return SC_ERR_ATR_TIMEOUT;     
    }
        
    SC_INFO("SC%d - Reset ICC Complete, atr_len=%d\n", p_this->id, p_this->atr.length);
    return SC_SUCCESS;
}



/*------------------------------------------------------------------
 * Func : icam_scd_get_atr
 *
 * Desc : s icam smart card interface
 *
 * Parm : p_this   : handle of icam scd  
 *        p_atr    : atr output buffer
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/        
int icam_scd_get_atr(icam_scd* p_this, scd_atr* p_atr)
{        
    if (p_this->fsm != IFD_FSM_ACTIVE)
    {    
        p_atr->length = -1;  
        return -1;
    }
                
    p_atr->length = p_this->atr.length;
    memcpy(p_atr->data, p_this->atr.data, p_this->atr.length);    
    return 0;    
}



/*------------------------------------------------------------------
 * Func : icam_scd_card_detect
 *
 * Desc : get card status
 *
 * Parm : p_this   : handle of icam scd  
 *         
 * Retn : 0 : no icc exists, others : icc exists
 *------------------------------------------------------------------*/   
int icam_scd_card_detect(icam_scd* p_this)
{                              
    return (GET_ICAM_UART_CTRL_STAT(p_this) & ICAM_UART_STATUS_DETECT) ? 1 : 0;                        
}



/*------------------------------------------------------------------
 * Func : icam_scd_get_card_status
 *
 * Desc : get card status
 *
 * Parm : p_this   : handle of icam scd  
 *         
 * Retn : 0 : no icc exists, others : icc exists
 *------------------------------------------------------------------*/   
int icam_scd_get_card_status(icam_scd* p_this)
{
    switch(p_this->fsm) {       
    case IFD_FSM_DISABLE:   return SC_CARD_REMOVED;                
    case IFD_FSM_DEACTIVATE:      return icam_scd_card_detect(p_this) ? SC_CARD_DEACTIVATE : SC_CARD_REMOVED;                        
    case IFD_FSM_RESET:     return SC_CARD_RESET;                                                            
    case IFD_FSM_ACTIVE:    return SC_CARD_ACTIVATE;                
    default:                return SC_CARD_UNKNOWN;
    }    
}



/*------------------------------------------------------------------
 * Func : icam_scd_poll_card_status
 *
 * Desc : poll card status change
 *
 * Parm : p_this   : handle of icam scd  
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/   
int icam_scd_poll_card_status(icam_scd* p_this)
{               
    p_this->card_status_change = 0;
    wait_event_interruptible(p_this->wq, p_this->card_status_change); 
    return icam_scd_get_card_status(p_this);     
}



/*------------------------------------------------------------------
 * Func : icam_scd_xmit
 *
 * Desc : xmit data via smart card bus
 *
 * Parm : p_this   : handle of icam scd  
 *        scb      : data to be xmit
 *         
 * Retn : SC_SUCCESS / SC_FAIL
 *------------------------------------------------------------------*/        
int icam_scd_xmit(icam_scd* p_this, unsigned char* p_data, unsigned int len)
{            
    unsigned long status;
   
    if (icam_scd_card_detect(p_this)==0)
        return SC_ERR_NO_ICC;
        
    if (p_this->fsm != IFD_FSM_ACTIVE)        
        return SC_ERR_ICC_DEACTIVATE;   
        
    while(len)
    {
        status = GET_ICAM_UART_CTRL_STAT(p_this);        
        
        if ((status & ICAM_UART_STATUS_DETECT)==0)                    
            return SC_ERR_NO_ICC;        

        if (GET_ICAM_UART_INT(p_this) & ICAM_UART_TX_PARITY_ERR)
        {
            SC_WARNING("SC%d - Tx Parity Error!!\n", p_this->id); 
        } 
             
        if (status & ICAM_UART_STATUS_TX_READY)
        {
            SET_ICAM_UART_DATA(p_this, *p_data++);
            len--;
        }
        
        udelay(10);        
    }
            
    return 0;            
}                        




/*------------------------------------------------------------------
 * Func : icam_scd_read
 *
 * Desc : read data via smart card bus
 *
 * Parm : p_this   : handle of icam scd   
 *         
 * Retn : sc_buff
 *------------------------------------------------------------------*/        
int icam_scd_read(icam_scd* p_this, unsigned char* data, unsigned int len)
{    
    if (icam_scd_card_detect(p_this)==0)
        return SC_ERR_NO_ICC;
            
    if (p_this->fsm != IFD_FSM_ACTIVE)
        return SC_ERR_ICC_DEACTIVATE;    
            
    return kfifo_out_locked(&p_this->rx_fifo, data, len, &p_this->rx_fifo_lock);
}



/*------------------------------------------------------------------
 * Func : icam_scd_open
 *
 * Desc : open a icam scd device
 *
 * Parm : id  : channel id
 *         
 * Retn : handle of icam scd
 *------------------------------------------------------------------*/
icam_scd* icam_scd_open()
{           
    icam_scd* p_this;    
       
    p_this = (icam_scd*) kmalloc(sizeof(icam_scd), GFP_KERNEL);    
             
    if (p_this)
    {
        memset(p_this, 0, sizeof(icam_scd));        
  
        p_this->id               = 0;
        p_this->fsm              = IFD_FSM_UNKNOWN;        
        p_this->atr.length       = -1;        
        
        if (kfifo_alloc(&p_this->rx_fifo, 1024, GFP_KERNEL)<0)
        {
            SC_WARNING("scd : open %s scd(%d) failed, create rx fifo failed\n", IFD_MODOLE, p_this->id);
            kfree(p_this);
            return NULL;
        }
        
        spin_lock_init(&p_this->lock);
        spin_lock_init(&p_this->rx_fifo_lock);
        init_waitqueue_head(&p_this->wq);                        
        
        // configurations ---                
        p_this->uart_ctrl = ICAM_UART_CTRL_3V5V_OFF | ICAM_UART_CTRL_DIRECT_CONV | 
                            ICAM_UART_CTRL_VCC_OFF  | ICAM_UART_CTRL_AUTO_FLOW_CTRL_OFF;
        p_this->vcc_sel   = ICAM_UART_CTRL_3V5V_ON;   
        p_this->etu       = 372;     
                        
        SET_ICAM_UART_CTRL_STAT(p_this, p_this->uart_ctrl);
                
        icam_scd_set_clock(p_this, LOWEST_CLOCK);
        
        icam_scd_set_etu(p_this, 372);
        
        icam_scd_set_guard_interval(p_this, 2);
        
        // Set All Register to the initial value            
        // Set Interrupt or IRQ        
        SC_INFO("Request IRQ #%d\n", ICAM_IRQ);             
    
        if (request_irq(ICAM_IRQ, icam_scd_isr, SA_SHIRQ, "ICAM SCD", (void *) p_this) < 0) 
        {
            SC_WARNING("scd : open %s scd failed, unable to request irq#%d\n", IFD_MODOLE, ICAM_IRQ); 
            kfree(p_this);          
            return NULL;
        }                      
                
        icam_scd_set_state(p_this, IFD_FSM_DISABLE);
    }        
    else
        SC_WARNING("scd : open icam scd failed, out of memory\n");   
        
    return p_this;
}    


/*------------------------------------------------------------------
 * Func : icam_scd_close
 *
 * Desc : close a icam scd device
 *
 * Parm : p_this  : icam scd to be close
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
void icam_scd_close(icam_scd* p_this)
{
#ifdef ISR_POLLING             
    del_timer(&p_this->timer);      // register timer
#else
    free_irq(ICAM_IRQ ,p_this);    
#endif    

    kfifo_free(&p_this->rx_fifo);
    icam_scd_set_state(p_this, IFD_FSM_DISABLE);    
    wake_up(&p_this->wq);   
    kfree(p_this);        
}    

