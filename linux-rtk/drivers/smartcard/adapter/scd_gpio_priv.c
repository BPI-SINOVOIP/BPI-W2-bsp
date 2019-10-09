/* ------------------------------------------------------------------------- 
   scd_gpio.c  scd driver for Realtek Neptune/Mars           
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
#include <linux/time.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <asm/io.h>
#include <platform.h>
#include <asm/mach-rtk_dmp/venus_gpio.h>
#include <asm/mach-rtk_dmp/venus_pwm.h>
#include "scd_gpio_priv.h"
#include "scd_gpio_priv_config.h"
#include "scd_mars_reg.h"

MODULE_LICENSE("GPL");

/* Basic operation */

#if 1

#define rtd_inb(offset)             (*(volatile unsigned char  *)(offset))
#define rtd_inw(offset)             (*(volatile unsigned short *)(offset))
#define rtd_inl(offset)             (*(volatile unsigned long  *)(offset))
#define rtd_outb(offset,val)        (*(volatile unsigned char  *)(offset) = val)
#define rtd_outw(offset,val)        (*(volatile unsigned short *)(offset) = val)
#define rtd_outl(offset,val)        (*(volatile unsigned long  *)(offset) = val)

#else

#define rtd_inb(offset)             (*(volatile unsigned char  *)(offset))
#define rtd_inw(offset)             (*(volatile unsigned short *)(offset))
#define rtd_inl(offset)             (*(volatile unsigned long  *)(offset))
#define rtd_outb(offset,val)        do { (*(volatile unsigned char  *)(offset) = val); printk("write reg=%08x, val=%08x\n", offset, (unsigned long) val); }while(0)
#define rtd_outw(offset,val)        do { (*(volatile unsigned short *)(offset) = val); printk("write reg=%08x, val=%08x\n", offset, (unsigned long) val); }while(0)
#define rtd_outl(offset,val)        do { (*(volatile unsigned long  *)(offset) = val); printk("write reg=%08x, val=%08x\n", offset, (unsigned long) val); }while(0)

#endif

#define rtd_mask_outl(offset, mask, val)   rtd_outl(offset, (rtd_inl(offset) & ~(mask))|((val) & (mask)))        


#define DBG_CHAR(x)                 rtd_outl(0xb8007800, x)

#ifdef GPIO_SCD_RX_DBG_EN
#define GPIO_SCD_RX_DBG(x)          DBG_CHAR(x)
#else
#define GPIO_SCD_RX_DBG(x)          
#endif

#define SET_MIS_ISR(val)            rtd_outl(MIS_ISR, val)
#define GET_MIS_ISR()               rtd_inl(MIS_ISR)
#define MISC_IRQ                    3

#define MAX_SC_CLK                   5000000
#define MIN_SC_CLK                   1000000    


typedef enum {
    UART_PARITY_NONE = 0,
    UART_PARITY_ODD,
    UART_PARITY_EVEN,    
}UART_PARITY;

typedef enum {    
    UART_STB_1BIS,
    UART_STB_2BIS,    
}UART_STB;

#define ULCR_DLAB          (1 << 7)

#define ULCR_BRK           (1 << 6)

#define ULCR_EPS(x)        ((x & 0x3) <<4)
  #define ULCR_EPS_ODD      ULCR_EPS(0)
  #define ULCR_EPS_EVEN     ULCR_EPS(1)
  #define ULCR_EPS_MARK     ULCR_EPS(0)
  #define ULCR_EPS_SPACE    ULCR_EPS(1)
  
#define ULCR_PEN(x)         ((x & 0x1) <<3)

#define ULCR_STB(x)        ((x & 0x1) <<2)
  #define ULCR_STB_1BITS     ULCR_STB(0)  
  #define ULCR_STB_2BITS     ULCR_STB(1)  
  
#define ULCR_WLS(x)        ((x & 0x3))
  #define ULCR_WLS_5BITS     ULCR_WLS(0)  
  #define ULCR_WLS_6BITS     ULCR_WLS(1)  
  #define ULCR_WLS_7BITS     ULCR_WLS(2)  
  #define ULCR_WLS_8BITS     ULCR_WLS(3)  


#define SA_SHIRQ IRQF_SHARED

int venus_uart_config(unsigned long baud_rate, UART_PARITY parity, UART_STB stop_bits)
{    
    unsigned long div = 27000000/ baud_rate;
    unsigned long lcr = ULCR_WLS_8BITS;
    
    switch(parity)
    {
    case UART_PARITY_NONE:
        lcr |= ULCR_PEN(0);
        break;
        
    case UART_PARITY_ODD:
        lcr |= ULCR_PEN(1) | ULCR_EPS_ODD;
        break;
        
    case UART_PARITY_EVEN:
        lcr |= ULCR_PEN(1) | ULCR_EPS_EVEN;
        break;                
    }
    
    if (stop_bits==UART_STB_1BIS)
        lcr |= ULCR_STB_1BITS;
    else
        lcr |= ULCR_STB_2BITS;
    
    rtd_outl(0xb801bc0c, rtd_inl(0xb801bc0c) | ULCR_DLAB);
    rtd_outl(0xb801bc00, div & 0xff);
    rtd_outl(0xb801bc04, (div >> 8) & 0xff);        
    rtd_outl(0xb801bc0c, (rtd_inl(0xb801bc0c) & ULCR_BRK) | lcr);            
    
    //SC_INFO("UART1 Baud=%ld, Div=%lx\n", baud_rate, div);

    return 0;    
}


int venus_uart_tx_break(unsigned char on)
{
    if (on)
        rtd_outl(0xb801bc0c, rtd_inl(0xb801bc0c) | ULCR_BRK);
    else
        rtd_outl(0xb801bc0c, rtd_inl(0xb801bc0c) & ~ULCR_BRK);

    return 0;
}


int venus_uart_enable(unsigned char on)
{       
    if (on) {
        rtd_outl(0xb801bc08, 0x6);
        rtd_outl(0xb801bc04, 0x1);    
        rtd_outl(0xb801bc08, 0x1);   // enable rx fifo...
    }
    else {
        //venus_uart_tx_break(1);
        rtd_outl(0xb801bc04, 0);  
        rtd_outl(0xb801bc08, 0x6);  
    }
    return 0;
}


int venus_uart_read(unsigned char* buff, unsigned int len)
{
    int rx_len = 0;
        
    while(rtd_inl(0xb801bc14) & 0x1 && rx_len < len) {
        //DBG_CHAR('*');
        buff[rx_len++] = (rtd_inl(0xb801bc00) & 0xff);    
    }
    return rx_len;
}


int venus_uart_write(unsigned char* buff, unsigned int len)
{    
    int i;
    
    while(len)
    {
        for (i=0; i<32 && len; i++) {
            rtd_outl(0xb801bc00, *(buff++));
            len--;
        }
                    
        while(((rtd_inl(0xb801bc14)>>5) & 0x3)!=0x3);            
    }
        
    udelay(1000);    
    return 0;
}



/*------------------------------------------------------------------
 * Func : gpio_scd_timer
 *
 * Desc : timer of mars scd
 *
 * Parm : arg : input param 
 *         
 * Retn : IRQ_NONE, IRQ_HANDLED
 *------------------------------------------------------------------*/
static void gpio_scd_timer(unsigned long arg)        
{   
    gpio_scd* p_this = (gpio_scd*) arg;
        
    if (gpio_scd_card_detect(p_this)) {
        //SC_WARNING("SC%d - gpio_scd_timer, pull high rst...\n", p_this->id);
        _gpio_scd_reset(p_this, 0);
    }    
}


/*------------------------------------------------------------------
 * Func : gpio_scd_set_state
 *
 * Desc : 
 *
 * Parm : p_this : handle of gpio cec 
 *         
 * Retn : N/A  
 *------------------------------------------------------------------*/
int gpio_scd_set_state(
    gpio_scd*               p_this, 
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
        
        // Deactivate flow : should be complete within 100ms
        // 1. Pull RST down
        // 2. Disable Clock Output
        // 3. Disable VCC         
        _gpio_scd_reset(p_this, 1);
        _gpio_scd_card_detect_enable(p_this, 0);
        _gpio_scd_io_mode(p_this, SCD_IO_OFF);
        _gpio_scd_clock_enable(p_this, 0);        
        _gpio_scd_vcc_enable(p_this, 0);
        gpio_scd_set_vcc_lvl(p_this, SC_VCC_3V);
        gpio_scd_set_etu(p_this, 372);
        gpio_scd_set_clock(p_this, 1000000);
        gpio_scd_set_convention(p_this, SC_AUTO_CONV);
        gpio_scd_set_parity(p_this, SC_PARITY_EVEN);
        p_this->atr.length = -1;
        break;        
        
    case IFD_FSM_DEACTIVATE:
    
        SC_INFO("SC%d - FSM = DEACTIVATE\n", id);                
        _gpio_scd_reset(p_this, 1);
        gpio_scd_set_etu(p_this, 372);
        _gpio_scd_io_mode(p_this, SCD_IO_OFF);
        _gpio_scd_clock_enable(p_this, 0);
        _gpio_scd_card_detect_enable(p_this, 1);        
        _gpio_scd_vcc_enable(p_this, 0);        
        p_this->atr.length = -1;
        kfifo_reset(&p_this->rx_fifo);   
        break;
        
    case IFD_FSM_RESET:

        p_this->atr.length = -1;        
        if (!gpio_scd_card_detect(p_this))
        {
            SC_WARNING("SC%d - RESET gpio scd failed, no ICC exist\n", id);                            
            gpio_scd_set_state(p_this, IFD_FSM_DEACTIVATE);
            return -1;
        }
                                                                
        kfifo_reset(&p_this->rx_fifo);   
        _gpio_scd_vcc_enable(p_this, 1);
        _gpio_scd_pwrsel(p_this, p_this->vcc_5v_en);
        _gpio_scd_clock_enable(p_this, 1);        // output clock
        gpio_scd_set_etu(p_this, 372);
        _gpio_scd_io_mode(p_this, SCD_IO_RECV); 
        _gpio_scd_card_detect_enable(p_this, 1);
        _gpio_scd_reset(p_this, 1);                
        if (p_this->auto_conv_en)
            p_this->conv = SC_AUTO_CONV;                 
        
        init_timer(&p_this->timer);
        p_this->timer.data     = (unsigned long)p_this;
        p_this->timer.function = gpio_scd_timer;
        p_this->timer.expires  = jiffies + ((40000 * 100) / p_this->clock_freq) + 2;        
        add_timer(&p_this->timer);              
        
        printk("interval = %ld jiffies\n", ((40000 * 100) / p_this->clock_freq));  
        
        p_this->atr_timeout = jiffies + HZ;                    
        
        SC_INFO("SC%d - FSM = RESET & ATR\n", id);
        break;
          
    case IFD_FSM_ACTIVATE:    
        SC_INFO("SC%d - FSM = ACTIVATE\n", id);
        break;

    default:
    case IFD_FSM_UNKNOWN:
        break;                    
    }    
    
    p_this->fsm = fsm;     
    p_this->card_status_change = 1;
    wake_up_interruptible(&p_this->wq);             
    
    return 0;
}



/*------------------------------------------------------------------
 * Func : gpio_scd_fsm_reset
 *
 * Desc : 
 *
 * Parm : p_this : handle of mars cec 
 *         
 * Retn : N/A  
 *------------------------------------------------------------------*/
void gpio_scd_fsm_reset(gpio_scd* p_this)
{    
    unsigned long event  = p_this->event;    
    int rx_len;
       
    //printk("SC_RISR=%08lx\n", event);
                                            
    if ((event & SC_RXP_INT) || !gpio_scd_card_detect(p_this) || time_after(jiffies, p_this->atr_timeout))
        goto err_atr_failed;        
    
    if (p_this->atr.length== -1 && (event & SC_RCV_INT)) 
        p_this->atr.length = 0;         // got ATR
            
    if (kfifo_len(&p_this->rx_fifo))  
    {                                   
        if (p_this->atr.length<0)
        {
            kfifo_reset(&p_this->rx_fifo);            
            goto end_proc;           
        }

        // receive atr :                
        rx_len = kfifo_out_locked(&p_this->rx_fifo, 
                                  &p_this->atr.data[p_this->atr.length], 
                                  sizeof(p_this->atr.data) - p_this->atr.length, 
                                  &p_this->rx_fifo_lock);

        SC_INT_DBG("fifo_len=%d, atr_remain=%d, p_this->atr.lengt=%d\n", 
                kfifo_len(&p_this->rx_fifo), 
                sizeof(p_this->atr.data - p_this->atr.length),
                p_this->atr.length);    
                
        if (rx_len > 0)
        {                            
            p_this->atr.length += rx_len;

            // check atr 
            if (is_atr_complete(&p_this->atr))
            {            
                SC_INFO("SC%d - Got ATR Completed\n", p_this->id);
                
                if (decompress_atr(&p_this->atr, &p_this->atr_info)<0)
                    goto err_atr_failed;
                      
                gpio_scd_set_state(p_this, IFD_FSM_ACTIVATE);       // jump to active state
            }
        }
    }       
    
end_proc:    
    p_this->event = 0;
    return; 
    
err_atr_failed:

    if (!gpio_scd_card_detect(p_this))
    {
        SC_WARNING("SC%d - RESET ICC failed, no ICC detected\n", p_this->id);
    }    
    
    if (event & SC_RXP_INT)
    {
        SC_WARNING("SC%d - RESET ICC failed, RX Parity Error\n", p_this->id);
    }
    
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
    
    gpio_scd_set_state(p_this, IFD_FSM_DEACTIVATE);
    
    goto end_proc;
}



/*------------------------------------------------------------------
 * Func : gpio_scd_work
 *
 * Desc : gpio scd work routine
 *
 * Parm : p_this : handle of gpio scd
 *         
 * Retn : N/A  
 *------------------------------------------------------------------*/
void gpio_scd_work(gpio_scd* p_this)
{    
    if (p_this->event & SC_CPRES_INT)            
    {           
        if (gpio_scd_card_detect(p_this))         
        {
            SC_INFO("SC%d - ICC detected!!\n", p_this->id);                         
        }
        else  
        {
            SC_INFO("SC%d - ICC removed!!\n", p_this->id);              
            gpio_scd_set_state(p_this, IFD_FSM_DEACTIVATE);            
        }
            
        p_this->card_status_change = 1;
        wake_up_interruptible(&p_this->wq); 
    }            
        
    switch (p_this->fsm)
    {                   
    case IFD_FSM_RESET:    gpio_scd_fsm_reset(p_this);  break;
    default:
        break;
    }            

    p_this->event = 0;  
}



unsigned char _inverse_bit_order(unsigned char in)
{
    unsigned char out = 0;
    int i=0;
    
    for (i=0; i<8; i++) 
    {
        if (in & 0x1)
            out |= 1<<(7-i);
            
        in >>=1;
    }        
    return out;        
}



/*------------------------------------------------------------------
 * Func : gpio_scd_isr
 *
 * Desc : isr of gpio scd
 *
 * Parm : gid    : gpio id
 *        assert : assert or deassert
 *        dev_id : device id
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
void gpio_scd_isr(
    VENUS_GPIO_ID           gid, 
    unsigned char           assert, 
    void*                   dev_id
    )
{    
    gpio_scd* p_this = (gpio_scd*) dev_id;
    unsigned long flag;    
             
    spin_lock_irqsave(&p_this->lock, flag);      

    if (gid==p_this->pin_card_detect)
    {
        p_this->event |= SC_CPRES_INT;     // setup event                

        gpio_scd_work(p_this);        
    }
    
    spin_unlock_irqrestore(&p_this->lock, flag);       
}



/*------------------------------------------------------------------
 * Func : gpio_scd_isr
 *
 * Desc : isr of gpio scd
 *
 * Parm : p_this : handle of gpio scd 
 *        dev_id : handle of the gpio_scd
 *        regs   :
 *         
 * Retn : IRQ_NONE, IRQ_HANDLED
 *------------------------------------------------------------------*/
static irqreturn_t
gpio_scd_io_isr(
    int                     this_irq, 
    void*                   dev_id
    )
{   
    gpio_scd* p_this = (gpio_scd*) dev_id;
    unsigned char sdata;             
    unsigned char tx_data;          
    unsigned long event = GET_MIS_ISR() & 0x8;            
    unsigned long flag;    
                                 
    if (!event)
        return IRQ_NONE;                
        
    spin_lock_irqsave(&p_this->lock, flag);   
            
    //printk("MIS ISR=%08x, status=%08x, ier=%08x\n", event, rtd_inl(0xb801bc14), rtd_inl(0xb801bc04));                         
                    
    if (rtd_inl(0xb801bc14) & 0x1)
    {
        // read data....
        while(venus_uart_read(&sdata, 1))                
        {            
            if (p_this->conv==SC_AUTO_CONV)                         
            {        
                if (sdata==0x3B)                
                    p_this->conv = SC_DIRECT_CONV;
                else if ((~_inverse_bit_order(sdata) & 0xFF)==0x3F)
                    p_this->conv = SC_INVERSE_CONV;
                else
                {
                    SC_WARNING("invalid TS %02x, drop it...\n", sdata);  
                    continue; // drop it
                }
            }

            //printk("> %02x\n", sdata);  
            
            if (p_this->conv==SC_INVERSE_CONV)
                sdata = ~_inverse_bit_order(sdata) & 0xFF;           

            //printk("%02x\n", sdata);
            
            if (kfifo_out_locked(&p_this->tx_fifo, &tx_data, 1, &p_this->tx_fifo_lock)==1 && tx_data==sdata)
                continue;       // tx data... ignore it...                                                        
                            
            if (kfifo_in_locked(&p_this->rx_fifo, &sdata, 1, &p_this->rx_fifo_lock)<1)                            
                p_this->event |= SC_RX_FOVER_INT;

            p_this->event |= SC_RCV_INT;
        }            
                
        gpio_scd_work(p_this);        
    }
    
    SET_MIS_ISR(event);         
               
    spin_unlock_irqrestore(&p_this->lock, flag); 
    
    return IRQ_HANDLED;    
}




/*------------------------------------------------------------------
 * Func : gpio_scd_enable
 *
 * Desc : enable gpio smart card interface
 *
 * Parm : p_this   : handle of gpio scd  
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int gpio_scd_enable(gpio_scd* p_this, unsigned char on_off)
{
    if (on_off)        
    {
        if (p_this->fsm==IFD_FSM_DISABLE)
            return gpio_scd_set_state(p_this, IFD_FSM_DEACTIVATE);
    }
    else    
        return gpio_scd_set_state(p_this, IFD_FSM_DISABLE);    
    
    return 0;
}



/*------------------------------------------------------------------
 * Func : gpio_scd_set_clock
 *
 * Desc : set clock frequency of gpio smart card interface
 *
 * Parm : p_this   : handle of gpio scd  
 *        clk      : clock (in HZ)
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int gpio_scd_set_clock(gpio_scd* p_this, unsigned long clk)
{           
    if (clk > MAX_SC_CLK) {
        SC_WARNING("clock %lu out of range, using minimum value to instead %lu\n", 
                    (unsigned long)clk, (unsigned long)MAX_SC_CLK);        
        clk = MAX_SC_CLK;
    }
        
    if (clk < MIN_SC_CLK) {
        SC_WARNING("clock %lu out of range, using minimum value to instead %lu\n", 
                    (unsigned long)clk, (unsigned long)MIN_SC_CLK);
        clk = MIN_SC_CLK;
    }
    
    p_this->clock_freq = clk;    
    _gpio_scd_clock_config(p_this);      
    _gpio_scd_io_config(p_this);
    return 0;
}



/*------------------------------------------------------------------
 * Func : gpio_scd_set_etu
 *
 * Desc : set etu of gpio smart card interface
 *
 * Parm : p_this   : handle of gpio scd  
 *        etu      : cycles
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int gpio_scd_set_etu(gpio_scd* p_this, unsigned long etu)
{                 
    p_this->etu = etu;
    _gpio_scd_io_config(p_this);   
    return 0;
}



/*------------------------------------------------------------------
 * Func : gpio_scd_set_parity
 *
 * Desc : set parity of gpio smart card interface
 *
 * Parm : p_this   : handle of gpio scd  
 *        parity   : 
 *           SC_PARITY_NONE
 *           SC_PARITY_ODD 
 *           SC_PARITY_EVEN 
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int gpio_scd_set_parity(gpio_scd* p_this, SC_PARITY parity)
{        
    p_this->parity = parity;                                
    _gpio_scd_io_config(p_this);                              
    return 0;
}



/*------------------------------------------------------------------
 * Func : gpio_scd_set_convention
 *
 * Desc : set convention setting of gpio smart card interface
 *
 * Parm : p_this   : handle of gpio scd  
 *        conv     : convention
 *          SC_AUTO_CONV : Auto Convention
 *          SC_DIRECT_CONV : Direct Convention
 *          SC_CONV_INVERSE : Inverse Convention
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int gpio_scd_set_convention(gpio_scd* p_this, SC_CONV conv)
{    
    if (conv==SC_AUTO_CONV)
        p_this->auto_conv_en = 1;    
    else
    {
        p_this->auto_conv_en = 0;       
        p_this->conv = conv;        
    }
    
    return 0;    
}




/*------------------------------------------------------------------
 * Func : gpio_scd_activate
 *
 * Desc : activate an ICC
 *
 * Parm : p_this   : handle of gpio scd  
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/        
int gpio_scd_activate(gpio_scd* p_this)
{
    switch(p_this->fsm)
    {
    case IFD_FSM_DISABLE:
        SC_WARNING("activate ICC failed, please enable IFD first\n");
        return -1;
        
    case IFD_FSM_DEACTIVATE:
    
        if (gpio_scd_reset(p_this)==0)
        {
            SC_INFO("activate ICC success\n");
            return 0;
        }
        else
        {
            SC_WARNING("activate ICC failed\n");
            return -1;
        }
        break;            
        
    case IFD_FSM_RESET:
        SC_INFO("ICC has is reseting\n");
        return 0;
        
    case IFD_FSM_ACTIVATE:
        SC_INFO("ICC has been activated already\n");
        return 0;
        
    default:        
        SC_WARNING("activate ICC failed, unknown state\n");
        return -1;
    } 
}



/*------------------------------------------------------------------
 * Func : gpio_scd_deactivate
 *
 * Desc : deactivate an ICC
 *
 * Parm : p_this   : handle of gpio scd  
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/        
int gpio_scd_deactivate(gpio_scd* p_this)
{    
    if (p_this->fsm != IFD_FSM_DISABLE)
    {
        gpio_scd_set_state(p_this, IFD_FSM_DISABLE);
        gpio_scd_set_state(p_this, IFD_FSM_DEACTIVATE);
    }
    return 0;
}




/*------------------------------------------------------------------
 * Func : gpio_scd_reset
 *
 * Desc : reset gpio smart card interface
 *
 * Parm : p_this   : handle of gpio scd  
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/        
int gpio_scd_reset(gpio_scd* p_this)
{        
    unsigned long t;
    
    if (gpio_scd_set_state(p_this, IFD_FSM_RESET))
        return -1;
    
    t = jiffies + (HZ<<1);
    
    while(!time_after(jiffies,t) && p_this->fsm == IFD_FSM_RESET)    {        
        msleep(100);    
    }
    
    if (p_this->fsm!=IFD_FSM_ACTIVATE)
    {
        SC_WARNING("SC%d - Reset ICC failed\n", p_this->id);
        gpio_scd_set_state(p_this, IFD_FSM_DEACTIVATE);
        return -1;     
    }
        
    SC_INFO("SC%d - Reset ICC Complete\n", p_this->id);
    return 0;
}



/*------------------------------------------------------------------
 * Func : gpio_scd_get_atr
 *
 * Desc : s mars smart card interface
 *
 * Parm : p_this   : handle of mars scd  
 *        p_atr    : atr output buffer
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/        
int gpio_scd_get_atr(gpio_scd* p_this, scd_atr* p_atr)
{        
    if (p_this->fsm != IFD_FSM_ACTIVATE)
    {    
        p_atr->length = -1;  
        return -1;
    }
    
    p_atr->length = p_this->atr.length;
    memcpy(p_atr->data, p_this->atr.data, p_this->atr.length);    
    return 0;    
}



/*------------------------------------------------------------------
 * Func : gpio_scd_card_detect
 *
 * Desc : get card status
 *
 * Parm : p_this   : handle of gpio scd  
 *         
 * Retn : 0 : no icc exists, others : icc exists
 *------------------------------------------------------------------*/   
int gpio_scd_card_detect(gpio_scd* p_this)
{               
    return _gpio_scd_card_detect_status(p_this);
}


/*------------------------------------------------------------------
 * Func : gpio_scd_get_card_status
 *
 * Desc : get card status
 *
 * Parm : p_this   : handle of gpio scd  
 *         
 * Retn : 0 : no icc exists, others : icc exists
 *------------------------------------------------------------------*/   
int gpio_scd_get_card_status(gpio_scd* p_this)
{               
    switch(p_this->fsm) {       
    case IFD_FSM_DISABLE:   return SC_CARD_REMOVED;                
    case IFD_FSM_DEACTIVATE:      return gpio_scd_card_detect(p_this) ? SC_CARD_DEACTIVATE : SC_CARD_REMOVED;                        
    case IFD_FSM_RESET:     return SC_CARD_RESET;                                                            
    case IFD_FSM_ACTIVATE:  return SC_CARD_ACTIVATE;                
    default:                return SC_CARD_UNKNOWN;
    }
}



/*------------------------------------------------------------------
 * Func : gpio_scd_poll_card_status
 *
 * Desc : poll card status change
 *
 * Parm : p_this   : handle of gpio scd  
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/   
int gpio_scd_poll_card_status(gpio_scd* p_this)
{       
    p_this->card_status_change = 0;
    wait_event_interruptible(p_this->wq, p_this->card_status_change); 
    return gpio_scd_get_card_status(p_this);     
}



/*------------------------------------------------------------------
 * Func : gpio_scd_xmit
 *
 * Desc : xmit data via smart card bus
 *
 * Parm : p_this   : handle of gpio scd  
 *        scb      : data to be xmit
 *         
 * Retn : SC_SUCCESS / SC_FAIL
 *------------------------------------------------------------------*/        
int gpio_scd_xmit(gpio_scd* p_this, unsigned char* p_data, unsigned int len)
{    
    int i;
    
    if (p_this->fsm==IFD_FSM_ACTIVATE)
    {
        venus_uart_enable(1);
        _gpio_scd_io_mode(p_this, SCD_IO_XMIT); // TX mode
        kfifo_in_locked(&p_this->tx_fifo, p_data, len, &p_this->tx_fifo_lock);             

        for (i=0; i<len; i++) 
        {
            if (p_this->conv==SC_INVERSE_CONV)
                p_data[i] = ~_inverse_bit_order(p_data[i]) & 0xFF;       
        }
                                    
        venus_uart_write(p_data, len);    
        _gpio_scd_io_mode(p_this, SCD_IO_RECV); // TX mode    
        return SC_SUCCESS;
    }
    
    return SC_ERR_ICC_DEACTIVATE;
}                        




/*------------------------------------------------------------------
 * Func : gpio_scd_read
 *
 * Desc : read data via smart card bus
 *
 * Parm : p_this   : handle of gpio scd   
 *         
 * Retn : sc_buff
 *------------------------------------------------------------------*/        
int gpio_scd_read(gpio_scd* p_this, unsigned char* data, unsigned int len)
{    
    if (p_this->fsm==IFD_FSM_ACTIVATE)    
        return kfifo_out_locked(&p_this->rx_fifo, data, len, &p_this->rx_fifo_lock);
    
    return SC_ERR_ICC_DEACTIVATE;
}



/*------------------------------------------------------------------
 * Func : gpio_scd_open
 *
 * Desc : open a gpio scd device
 *
 * Parm : id  : channel id
 *         
 * Retn : handle of gpio scd
 *------------------------------------------------------------------*/
gpio_scd* gpio_scd_open(unsigned char id)
{           
    gpio_scd* p_this;
    
    if (id >= 1) {
        SC_WARNING("scd : open gpio scd failed, invalid id - %d\n", id);
        return NULL;
    }                       
        
    p_this = (gpio_scd*) kmalloc(sizeof(gpio_scd), GFP_KERNEL);    
    
    if (p_this)
    {
        memset(p_this, 0, sizeof(gpio_scd));        
  
        p_this->id               = id;
        p_this->fsm              = IFD_FSM_UNKNOWN;
        p_this->atr.length       = -1;        
        if (kfifo_alloc(&p_this->rx_fifo, 512, GFP_KERNEL)<0)
        {
            SC_WARNING("scd : open gpio scd(%d) failed, create rx fifo failed\n", id);
            kfree(p_this);
            return NULL;
        }
        
        if (kfifo_alloc(&p_this->tx_fifo, 512, GFP_KERNEL)<0)
        {
            SC_WARNING("scd : open gpio scd(%d) failed, create rx fifo failed\n", id);
            kfree(p_this);
            return NULL;
        }
                
        spin_lock_init(&p_this->rx_fifo_lock);
        spin_lock_init(&p_this->tx_fifo_lock);        
        init_waitqueue_head(&p_this->wq);                        
        
        // pin assignment ---
        p_this->pin_clk          = GPIO_SCD_CLK_GPIO;      
        p_this->pin_card_detect  = GPIO_SCD_CD_GPIO;      
        p_this->pin_reset        = GPIO_SCD_RST_GPIO;            
        p_this->pin_uart_tx      = GPIO_SCD_DATAOUT_GPIO;
        p_this->pin_uart_rx      = GPIO_SCD_DATAIN_GPIO;                
#ifdef USE_TDA8024            
        p_this->pin_cmd_vcc      = GPIO_SCD_CMD_VCC_GPIO;
        p_this->pin_power_sel    = GPIO_SCD_PWR_SEL_GPIO;
#endif        
        p_this->pwm_id           = 0;
        
        // configurations ---
        p_this->clock_freq       = 1000000;             
        p_this->clock_en         = 0;
        p_this->etu              = 372;        // default etu = 372     
        p_this->parity           = SC_PARITY_EVEN;    
        p_this->auto_conv_en     = 1;
        p_this->vcc_5v_en        = 0;
        p_this->conv             = SC_AUTO_CONV;

        if (_gpio_scd_clock_init(p_this)<0 ||
            _gpio_scd_reset_init(p_this)<0 ||
            _gpio_scd_card_detect_init(p_this) <0 ||
            _gpio_scd_vcc_init(p_this) < 0 ||
            _gpio_scd_pwrsel_init(p_this) < 0 ||
            _gpio_scd_io_init(p_this)<0)
        {
            SC_WARNING("scd : open gpio scd failed, init io pin failed\n"); 
            kfree(p_this);          
            return NULL;
        }        
                    
        gpio_scd_set_state(p_this, IFD_FSM_DISABLE);
    }        
    else
        SC_WARNING("scd : open gpio scd failed, out of memory\n");   
        
    return p_this;
}    


/*------------------------------------------------------------------
 * Func : gpio_scd_close
 *
 * Desc : close a gpio scd device
 *
 * Parm : p_this  : gpio scd to be close
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
void gpio_scd_close(gpio_scd* p_this)
{   
    gpio_scd_set_state(p_this, IFD_FSM_DISABLE);    
    _gpio_scd_io_uninit(p_this);
    _gpio_scd_reset_uninit(p_this);
    _gpio_scd_card_detect_uninit(p_this);      
    kfifo_free(&p_this->rx_fifo);
    wake_up(&p_this->wq);   
    kfree(p_this);        
}    


//////////////////////////////////////////////////////////////////
// Low Level API
//////////////////////////////////////////////////////////////////



/*------------------------------------------------------------------
 * Func : _gpio_scd_io_mode
 *
 * Desc : set io mode
 *
 * Parm : p_this  : handle of GPIO SCD
 *        mode    : 
 *          SCD_IO_OFF  : Disable IO Pin (output low)
 *          SCD_IO_RECV : Rx mode
 *          SCD_IO_XMIT : Tx mode
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
void _gpio_scd_io_mode(gpio_scd* p_this, SCD_IO_MODE mode)
{
#ifdef SPI_UART       
    switch(mode)
    {
    case SCD_IO_OFF:        
        //rtd_outl(0xb8000378, (rtd_inl(0xb8000378) & ~(0xF<<2)) | (0x6<<2));   // GPIO[2] = GPIO, GPIO[1] = UART1_TX
        rtd_outl(0xb8000378, (rtd_inl(0xb8000378) & ~(0xF<<2)) | (0xA<<2));     // GPIO[2] = UART1_RX, GPIO[1] = UART1_TX       
        venus_uart_enable(1);
        break;
        
    case SCD_IO_RECV:       
        //rtd_outl(0xb8000378, (rtd_inl(0xb8000378) & ~(0xF<<2)) | (0x9<<2));   // GPIO[2] = UART1_RX, GPIO[1] = Input GPIO
        rtd_outl(0xb8000378, (rtd_inl(0xb8000378) & ~(0xF<<2)) | (0xA<<2));     // GPIO[2] = UART1_RX, GPIO[1] = UART1_TX           
        venus_uart_enable(1);                
        kfifo_reset(&p_this->rx_fifo);            
        break;
        
    case SCD_IO_XMIT:
        //rtd_outl(0xb8000378, (rtd_inl(0xb8000378) & ~(0xF<<2)) | (0x9<<2));   // GPIO[2] = GPIO, GPIO[1] = UART1_TX
        rtd_outl(0xb8000378, (rtd_inl(0xb8000378) & ~(0xF<<2)) | (0xA<<2));     // GPIO[2] = UART1_RX, GPIO[1] = UART1_TX    
        venus_uart_enable(1);          
        kfifo_reset(&p_this->rx_fifo);                  
        break;

    default:
        break;                
    }
    
#else

    switch(mode)
    {
    case SCD_IO_OFF:
        venus_uart_tx_break(0);
  #ifdef SPI_UART_TX
        rtd_outl(0xb8000378, (rtd_inl(0xb8000378) & ~(0x7003C)) | (0x70018));     // GPIO[1] = UART1_TX, GPIO[57:58] = GPIO        
  #else        
        rtd_outl(0xb8000378, (rtd_inl(0xb8000378) & ~(0x7003C)) | (0x40014));     // GPIO[57] = UART1_RX GPIO[58] = UART1_TX 
  #endif        
        venus_uart_enable(0);      
        kfifo_reset(&p_this->rx_fifo);     
        kfifo_reset(&p_this->tx_fifo);   
        break;
        
    case SCD_IO_RECV:
        //venus_uart_tx_break(0);
        //venus_uart_enable(0);             
        rtd_outl(0xb8000378, (rtd_inl(0xb8000378) & ~(0x7003C)) | (0x40014));     // GPIO[57] = UART1_RX GPIO[58] = UART1_TX 
        venus_uart_enable(1);       
        //kfifo_reset(&p_this->rx_fifo);                  
        break;
        
    case SCD_IO_XMIT:
        //venus_uart_tx_break(0);
        //venus_uart_enable(0);
        kfifo_reset(&p_this->tx_fifo);     // clear tx fifo
            
  #ifdef SPI_UART_TX
        rtd_outl(0xb8000378, (rtd_inl(0xb8000378) & ~(0x7003C)) | (0x70018));     // GPIO[1] = UART1_TX, GPIO[57:58]
  #else        
        rtd_outl(0xb8000378, (rtd_inl(0xb8000378) & ~(0x7003C)) | (0x40014));     // GPIO[57] = UART1_RX GPIO[58] = UART1_TX 
  #endif        
        venus_uart_enable(1);              
        kfifo_reset(&p_this->rx_fifo);   
        break;

    default:
        break;                
    }
    
#endif
    
//    printk("mode = %d, 0xb8000378=%08lx\n", mode, rtd_inl(0xb8000378));
}



/*------------------------------------------------------------------
 * Func : _gpio_scd_io_config
 *
 * Desc : config io pin prarmeter
 *
 * Parm : p_this  : handle of GPIO SCD
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
void _gpio_scd_io_config(gpio_scd* p_this)
{    
    //SC_INFO("SC%d - baud rate=%ld (etu=%ld, freq=%ld Hz)\n", 
    //    p_this->id, p_this->clock_freq / p_this->etu,
    //    p_this->etu, p_this->clock_freq);                        
        
    venus_uart_config(p_this->clock_freq/p_this->etu, 
                     (p_this->parity==SC_PARITY_EVEN) ? UART_PARITY_EVEN : 
                     (p_this->parity==SC_PARITY_ODD) ? UART_PARITY_ODD : UART_PARITY_NONE, 
                     UART_STB_2BIS);
}



/*------------------------------------------------------------------
 * Func : _gpio_scd_io_init
 *
 * Desc : init io pin
 *
 * Parm : p_this  : handle of GPIO SCD
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int _gpio_scd_io_init(gpio_scd* p_this)
{   
    int ret = 0;     
        
    rtd_outl(0xb8000380, 0);    
    venus_gpio_set_dir(p_this->pin_uart_rx, 0);
    venus_gpio_set_dir(p_this->pin_uart_tx, 0);
    _gpio_scd_io_mode(p_this, SCD_IO_OFF);    

    if (request_irq(MISC_IRQ, gpio_scd_io_isr, SA_SHIRQ, "SCD_IO", (void *) p_this) < 0) 
    {
        SC_WARNING("scd : init scd io pin failed, unable to request irq#%d\n", MISC_IRQ); 
        ret = -1;
    }        

    _gpio_scd_io_config(p_this);

    return ret;
}



/*------------------------------------------------------------------
 * Func : _gpio_scd_io_uninit
 *
 * Desc : uninit io pin
 *
 * Parm : p_this  : handle of GPIO SCD
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
void _gpio_scd_io_uninit(gpio_scd* p_this)
{    
    _gpio_scd_io_mode(p_this, SCD_IO_OFF);               
    free_irq(MISC_IRQ, (void *) p_this);
}


/*------------------------------------------------------------------
 * Func : _gpio_scd_card_detect_init
 *
 * Desc : init card detect pin
 *
 * Parm : p_this  : handle of GPIO SCD
 *         
 * Retn : 0 : success, others: failed
 *------------------------------------------------------------------*/
int _gpio_scd_card_detect_init(gpio_scd* p_this)
{
    if ((rtd_inl(GPIO_SCD_CD_PINMUX_REG) & GPIO_SCD_CD_PINMUX_MASK) != GPIO_SCD_CD_PINMUX_VAL)
    {
        printk("_gpio_scd_card_detect_init failed, pin has been programed for another application\n");
        
#ifdef FORCE_SET_PINMUX
        rtd_mask_outl(GPIO_SCD_CD_PINMUX_REG, GPIO_SCD_CD_PINMUX_MASK, GPIO_SCD_CD_PINMUX_VAL);
#else   
        return -1;     
#endif                       
    }
    venus_gpio_set_irq_enable(p_this->pin_card_detect, 0);
    venus_gpio_set_dir(p_this->pin_card_detect, 0); 
    venus_gpio_set_debounce(p_this->pin_card_detect, VENUS_GPIO_DEBOUNCE_1ms); 
    venus_gpio_set_irq_polarity(p_this->pin_card_detect, 1);
    return venus_gpio_request_irq(p_this->pin_card_detect, gpio_scd_isr, "SCD", p_this); 
}



/*------------------------------------------------------------------
 * Func : _gpio_scd_card_detect_uninit
 *
 * Desc : uninit card detect pin
 *
 * Parm : p_this  : handle of GPIO SCD
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
void _gpio_scd_card_detect_uninit(gpio_scd* p_this)
{
    venus_gpio_set_dir(p_this->pin_card_detect, 0); 
    venus_gpio_set_irq_enable(p_this->pin_card_detect, 0);      
    venus_gpio_free_irq(p_this->pin_card_detect, p_this);  
}



/*------------------------------------------------------------------
 * Func : _gpio_scd_card_detect_enable
 *
 * Desc : enable card detect feature
 *
 * Parm : p_this  : handle of GPIO SCD
 *        On : 0 : disable, others : enable
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
void _gpio_scd_card_detect_enable(gpio_scd* p_this, unsigned char on)
{
    venus_gpio_set_irq_enable(p_this->pin_card_detect, (on) ? 1 : 0);
}



/*------------------------------------------------------------------
 * Func : _gpio_scd_card_detect_status
 *
 * Desc : get card detect status
 *
 * Parm : p_this  : handle of GPIO SCD
 *         
 * Retn : 0 : no card, 1 : card exists
 *------------------------------------------------------------------*/
int _gpio_scd_card_detect_status(gpio_scd* p_this)
{
   return venus_gpio_input(p_this->pin_card_detect) ? 1 : 0;
}



/*------------------------------------------------------------------
 * Func : _gpio_scd_reset_init
 *
 * Desc : init reset pin
 *
 * Parm : p_this  : handle of GPIO SCD
 *         
 * Retn : 0 : success, others : failed
 *------------------------------------------------------------------*/
int _gpio_scd_reset_init(gpio_scd* p_this)
{
    if ((rtd_inl(GPIO_SCD_RST_PINMUX_REG) & GPIO_SCD_RST_PINMUX_MASK) != GPIO_SCD_RST_PINMUX_VAL)
    {
        printk("_gpio_scd_reset_init failed, pin has been programed for another application\n");        
#ifdef FORCE_SET_PINMUX
        rtd_mask_outl(GPIO_SCD_RST_PINMUX_REG, GPIO_SCD_RST_PINMUX_MASK, GPIO_SCD_RST_PINMUX_VAL);
#else   
        return -1;     
#endif           
    }
    venus_gpio_output(p_this->pin_reset, 0);
    venus_gpio_set_dir(p_this->pin_reset, 1);
    return 0;
}



/*------------------------------------------------------------------
 * Func : _gpio_scd_reset_uninit
 *
 * Desc : uninit reset pin
 *
 * Parm : p_this  : handle of GPIO SCD
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
void _gpio_scd_reset_uninit(gpio_scd* p_this)
{
    venus_gpio_output(p_this->pin_reset, 0);
    venus_gpio_set_dir(p_this->pin_reset, 0);
}



/*------------------------------------------------------------------
 * Func : _gpio_scd_reset
 *
 * Desc : do reset
 *
 * Parm : p_this  : handle of GPIO SCD
 *        on      : 0 : clear reset flag, others : set reset flag
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
void _gpio_scd_reset(gpio_scd* p_this, unsigned char on)
{
    venus_gpio_output(p_this->pin_reset, (on) ? 0 : 1);
}



/*------------------------------------------------------------------
 * Func : _gpio_scd_clock_init
 *
 * Desc : enable clock output
 *
 * Parm : p_this  : handle of gpio scd  
 *        on      : enable (in HZ)
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int _gpio_scd_clock_init(gpio_scd* p_this)
{           
    switch(rtd_inl(GPIO_SCD_CLK_PINMUX_REG) & GPIO_SCD_CLK_PINMUX_MASK)
    {
    case GPIO_SCD_CLK_PINMUX_VAL_IO:
    case GPIO_SCD_CLK_PINMUX_VAL_PWM:
        break;
        
    default:                 
        printk("_gpio_scd_clock_init failed, clk pin has been programed for another application\n");
        
#ifdef FORCE_SET_PINMUX
        rtd_mask_outl(GPIO_SCD_CLK_PINMUX_REG, GPIO_SCD_CLK_PINMUX_MASK, GPIO_SCD_CLK_PINMUX_VAL_PWM);
        break;
#else
        return -1;        
#endif        
    }

    _gpio_scd_clock_enable(p_this, 0);
    _gpio_scd_clock_config(p_this);        
    return 0;
}



/*------------------------------------------------------------------
 * Func : _gpio_scd_clock_config
 *
 * Desc : enable clock output
 *
 * Parm : p_this  : handle of gpio scd  
 *        on      : enable (in HZ)
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int _gpio_scd_clock_config(gpio_scd* p_this)
{           
    return venus_pwm_ctrl(p_this->pwm_id, p_this->clock_freq, 50);;
}


/*------------------------------------------------------------------
 * Func : _gpio_scd_clock_enable
 *
 * Desc : enable clock output
 *
 * Parm : p_this  : handle of gpio scd  
 *        on      : enable clock
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int _gpio_scd_clock_enable(gpio_scd* p_this, unsigned char on)
{           
    unsigned long val;
    venus_gpio_output(p_this->pin_clk, 0);
    venus_gpio_set_dir(p_this->pin_clk, 1);
    
    val = rtd_inl(GPIO_SCD_CLK_PINMUX_REG) & ~GPIO_SCD_CLK_PINMUX_MASK;
    
    if (on)    
        val |= GPIO_SCD_CLK_PINMUX_VAL_PWM;       // PWM mode   
    else
        val |= GPIO_SCD_CLK_PINMUX_VAL_IO;        // GPIO mode        
        
    rtd_outl(GPIO_SCD_CLK_PINMUX_REG, val);                     

    return 0;
}



/*------------------------------------------------------------------
 * Func : _gpio_scd_vcc_init
 *
 * Desc : init vcc output pad
 *
 * Parm : p_this  : handle of gpio scd  
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/
int _gpio_scd_vcc_init(gpio_scd* p_this)
{
#ifdef USE_TDA8024       

    if ((rtd_inl(GPIO_SCD_CMD_VCC_PINMUX_REG) & GPIO_SCD_CMD_VCC_PINMUX_MASK) != GPIO_SCD_CMD_VCC_PINMUX_VAL)
    {
        printk("_gpio_scd_vcc_init failed, pin has been programed for another application\n");
        
#ifdef FORCE_SET_PINMUX
        rtd_mask_outl(GPIO_SCD_CMD_VCC_PINMUX_REG, GPIO_SCD_CMD_VCC_PINMUX_MASK, GPIO_SCD_CMD_VCC_PINMUX_VAL);
#else
        return -1;        
#endif           
    }
    
    venus_gpio_output(p_this->pin_cmd_vcc, 0);
    venus_gpio_set_dir(p_this->pin_cmd_vcc, 1);    // 1: disable VCC
#endif        
    return 0;
}



/*------------------------------------------------------------------
 * Func : _gpio_scd_vcc_enable
 *
 * Desc : enable vcc output
 *
 * Parm : p_this  : handle of gpio scd  
 *        on      : enable vcc
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int _gpio_scd_vcc_enable(gpio_scd* p_this, unsigned char on)
{
#ifdef USE_TDA8024    
    venus_gpio_output(p_this->pin_cmd_vcc, (on) ? 0 : 1);   // 0: Enable VCC 1: Disable VCC
#endif        
    return 0;
}



/*------------------------------------------------------------------
 * Func : _gpio_scd_pwrsel_init
 *
 * Desc : init power select output pad
 *
 * Parm : p_this  : handle of gpio scd  
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/
int _gpio_scd_pwrsel_init(gpio_scd* p_this)
{
#ifdef USE_TDA8024       

    if ((rtd_inl(GPIO_SCD_PWR_SEL_PINMUX_REG) & GPIO_SCD_PWR_SEL_PINMUX_MASK) != GPIO_SCD_PWR_SEL_PINMUX_VAL)
    {
        printk("_gpio_scd_vcc_init failed, pin has been programed for another application\n");
        
#ifdef FORCE_SET_PINMUX
        rtd_mask_outl(GPIO_SCD_PWR_SEL_PINMUX_REG, GPIO_SCD_PWR_SEL_PINMUX_MASK, GPIO_SCD_PWR_SEL_PINMUX_VAL);
#else
        return -1;        
#endif           
    }
    
    venus_gpio_output(p_this->pin_power_sel, 0);
    venus_gpio_set_dir(p_this->pin_power_sel, 1);
#endif        
    return 0;
}



/*------------------------------------------------------------------
 * Func : _gpio_scd_pwrsel
 *
 * Desc : select power
 *
 * Parm : p_this  : handle of gpio scd  
 *        power   : select power
 *          1 : 5V
 *          0 : 3.3V
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int _gpio_scd_pwrsel(gpio_scd* p_this, unsigned char power)
{
#ifdef USE_TDA8024    
    venus_gpio_output(p_this->pin_power_sel, (power) ? 1 : 0); 
#endif        
    return 0;
}

