/* ------------------------------------------------------------------------- 
   scd_mars.c  scd driver for Realtek Neptune/Mars           
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
#include "scd_mars_priv.h"
#include "scd_mars_reg.h"

#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>

#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/reset-helper.h> /* rstc_get */
#include <linux/reset.h>
#include <linux/clkdev.h>
#include <linux/clk-provider.h> 


MODULE_LICENSE("GPL");

extern MARS_DTS_INFO_T dts_info;

#define SA_SHIRQ IRQF_SHARED

/* Basic operation */

#if 1

#define rtd_inb(offset)             (*(volatile unsigned char  *)(offset))
#define rtd_inw(offset)             (*(volatile unsigned short *)(offset))
#define rtd_inl(offset)             readl(offset)
#define rtd_outb(offset,val)        (*(volatile unsigned char  *)(offset) = val)
#define rtd_outw(offset,val)        (*(volatile unsigned short *)(offset) = val)
#define rtd_outl(offset,val)        writel(val, offset)

#else

#define rtd_inb(offset)             (*(volatile unsigned char  *)(offset))
#define rtd_inw(offset)             (*(volatile unsigned short *)(offset))
#define rtd_inl(offset)             (*(volatile unsigned long  *)(offset))
#define rtd_outb(offset,val)        do { (*(volatile unsigned char  *)(offset) = val); printk("  @write reg=%08x, val=%08x\n", offset, (unsigned long) val); }while(0)
#define rtd_outw(offset,val)        do { (*(volatile unsigned short *)(offset) = val); printk("  @write reg=%08x, val=%08x\n", offset, (unsigned long) val); }while(0)
#define rtd_outl(offset,val)        do { (*(volatile unsigned long  *)(offset) = val); printk("  @write reg=%08x, val=%08x\n", offset, (unsigned long) val); }while(0)

#endif

#define DBG_CHAR(x)                 rtd_outl(0xb8007800, x)


static const unsigned long          SC_BASE[]={SC_BASE0};
static const unsigned long          MIS_SC_ISR[]={MIS_SC0_INT};

#define SET_MIS_ISR(misc, val)      rtd_outl(misc, val)
#define SET_SCFP(base, val)         rtd_outl(base + SCFP,    val)
#define SET_SCCR(base, val)         rtd_outl(base + SCCR,    val)
#define SET_SCPCR(base, val)        rtd_outl(base + SCPCR,   val)
#define SET_SC_TXFIFO(base, val)    rtd_outl(base + SCTXFIFO,val)
#define SET_SCFCR(base, val)        rtd_outl(base + SCFCR,   val)
#define SET_SCIRSR(base, val)       rtd_outl(base + SCIRSR,  val)
#define SET_SCIRER(base, val)       rtd_outl(base + SCIRER,  val)          


#define GET_MIS_ISR(misc)           rtd_inl(misc)
#define GET_SCFP(base)              rtd_inl(base + SCFP)
#define GET_SCCR(base)              rtd_inl(base + SCCR)
#define GET_SCPCR(base)             rtd_inl(base + SCPCR)
#define GET_SC_TXLENR(base)         rtd_inl(base + SCTXLENR)
#define GET_SC_RXFIFO(base)         rtd_inl(base + SCRXFIFO)
#define GET_SC_RXLENR(base)         rtd_inl(base + SCRXLENR)
#define GET_SCFCR(base)             rtd_inl(base + SCFCR)
#define GET_SCIRSR(base)            rtd_inl(base + SCIRSR)
#define GET_SCIRER(base)            rtd_inl(base + SCIRER)          

#define MAX_SC_CLK                   8000000
#define MIN_SC_CLK                   1000000   

#define TX_RX_DEPTH			40
    
#ifdef ISR_POLLING
#define ISR_POLLING_INTERVAL        (HZ)
static void mars_scd_timer(unsigned long arg);
#endif

extern char *parse_token(const char *parsed_string, const char *token);



/*------------------------------------------------------------------
 * Func : mars_scd_power_enable
 *
 * Desc : enable power for SMC
 *
 * Parm : p_this : handle of mars smartcard ifd 
 *        on     : enable / disable power
 *         
 * Retn : N/A  
 *------------------------------------------------------------------*/
void mars_scd_power_enable(
    mars_scd*               p_this, 
    unsigned char           on
    )
{
    unsigned char val = (on) ? ((p_this->cmd_vcc_polarity) ? 1 :0) : ((p_this->cmd_vcc_polarity) ? 0 :1);
    
    if (p_this->cmd_vcc_en)
    {   
        //SC_INFO("SC%d - power enable=%d, %s_GPIO[%d]=%d\n", 
        //p_this->id, on, gpio_type(p_this->pin_cmd_vcc), gpio_idx(p_this->pin_cmd_vcc), val);                
     	gpio_direction_output(p_this->pin_cmd_vcc, val);        
    }     
}    



/*------------------------------------------------------------------
 * Func : mars_scd_power_select
 *
 * Desc : enable power select for SMC
 *
 * Parm : p_this : handle of mars smartcard ifd 
 *        on     : enable / disable power select pin
 *         
 * Retn : N/A  
 *------------------------------------------------------------------*/
void mars_scd_power_select(
    mars_scd*               p_this, 
    unsigned char           on
    )
{
    unsigned char val = (on) ? ((p_this->pwr_sel_polarity) ? 1 :0) : ((p_this->pwr_sel_polarity) ? 0 :1);
    
    if (p_this->pwr_sel_en)
    {   
        //SC_INFO("SC%d - power select=%d, %s_GPIO[%d]=%d\n", 
        //p_this->id, on, gpio_type(p_this->pin_pwr_sel), gpio_idx(p_this->pin_pwr_sel), val);
        gpio_direction_output(p_this->pin_pwr_sel, val);
    }     
}    


/*------------------------------------------------------------------
 * Func : mars_scd_set_state
 *
 * Desc : 
 *
 * Parm : p_this : handle of mars smartcard ifd 
 *         
 * Retn : N/A  
 *------------------------------------------------------------------*/
int mars_scd_set_state(mars_scd *p_this, IFD_FSM fsm)
{
    void __iomem *base = p_this->base;
    unsigned char id = p_this->id;
    
    if (p_this->fsm == fsm)
        return 0;
        
    switch(fsm)
    {       
    case IFD_FSM_DISABLE:    

        SC_INFO("SC%d - FSM = DISABLE\n", id);

        SET_SCFP(base, SC_CLK_EN(0)    |
                        SC_CLKDIV((p_this->clock_div-1))|
                        SC_BAUDDIV2(0)  |                    // fixed to 31
                        SC_BAUDDIV1((p_this->baud_div1-1))|
                        SC_PRE_CLKDIV((p_this->pre_clock_div-1)));

        SET_SCPCR(base, SC_TXGRDT(2)    |
                        SC_CWI(0)       |
                        SC_BWI(0)       |
                        SC_WWI(0)       |
                        SC_BGT(0x16)    |
                        SC_EDC_EN(0)    |
                        SC_CRC(0)       |
                        SC_PROTOCOL_T(0)|
                        SC_T0RTY(0)     |
                        SC_T0RTY_CNT(0));
    
        SET_SCCR  (base, SC_FIFO_RST(1) | SC_SCEN(0) | SC_AUTO_ATR(1) | SC_CONV(0) | SC_PS(p_this->parity));
        SET_SCIRER(base, 0);                  // Disable ISR
        SET_SCIRSR(base, 0xFFFFFFFF);            
        mars_scd_power_enable(p_this, 0); 
        p_this->atr.length = -1;               
        break;
        
    case IFD_FSM_DEACTIVATE:    
        SC_INFO("SC%d - FSM = IDEL\n", id);
        // - begin - add to fix Nagxx ICC Test 11 - Paired 5040.2 deactivate with extra clk issue
        //mars_scd_power_enable(p_this, 0);
        udelay(100);
        // - end - add to fix Nagxx ICC Test 11 - Paired 5040.2 deactivate with extra clk issue
        mars_scd_set_etu(p_this, 372);
        mars_scd_set_parity(p_this, 1);

        SET_SCFP(base, SC_CLK_EN(1) |
                       SC_CLKDIV((p_this->clock_div-1))|
                       SC_BAUDDIV2(0) |                    // fixed to 31
                       SC_BAUDDIV1((p_this->baud_div1-1))|
                       SC_PRE_CLKDIV((p_this->pre_clock_div-1)));

        SET_SCCR(base, SC_FIFO_RST(0) | SC_SCEN(0) | SC_AUTO_ATR(1) | SC_CONV(0) |SC_PS(p_this->parity));
        udelay(1000);
        SET_SCCR(base, SC_FIFO_RST(0) | SC_SCEN(1) | SC_AUTO_ATR(1) | SC_CONV(0) |SC_PS(p_this->parity) | (1<<19));
        SET_SCIRER(base, SC_CPRES_INT);
        SET_SCIRSR(base, 0xFFFFFFFF);
        mars_scd_power_enable(p_this, 0);
        p_this->atr.length = -1;
        kfifo_reset(&p_this->rx_fifo);
#if 0    
        SC_INFO("SC%d - FSM = IDEL\n", id);          
        mars_scd_set_etu(p_this, 372);  
        mars_scd_set_parity(p_this, 1);                  
                
        SET_SCCR  (base, SC_FIFO_RST(0) | SC_SCEN(1) | SC_AUTO_ATR(1) | SC_CONV(0) |SC_PS(p_this->parity));
        SET_SCIRER(base, SC_CPRES_INT);
        SET_SCIRSR(base, 0xFFFFFFFF);
        mars_scd_power_enable(p_this, 0);
        p_this->atr.length = -1;
        kfifo_reset(&p_this->rx_fifo);
#endif
        break;
        
    case IFD_FSM_RESET:      
               
        p_this->atr.length = -1;
                                            
        if (!mars_scd_card_detect(p_this))
        {
            SC_WARNING("SC%d - RESET mars scd failed, no ICC exist\n", id);                            
            mars_scd_set_state(p_this, IFD_FSM_DEACTIVATE);
            return SC_ERR_NO_ICC;
        }
            
        mars_scd_power_select(p_this, p_this->vcc_5v);
        mars_scd_power_enable(p_this, 1);   // Power On   
        udelay(1000);
        mars_scd_set_etu(p_this, 372);  
        mars_scd_set_parity(p_this, 1);  
        kfifo_reset(&p_this->rx_fifo);

        SET_SCIRER(base, SC_CPRES_INT    |                        
                        SC_ATRS_INT     | 
                        SC_RXP_INT      | 
                        SC_RCV_INT      |
                        SC_RX_FOVER_INT);
                       
        SET_SCCR  (base, 0);
                       
        SET_SCCR  (base, SC_FIFO_RST(1)  |        // pull reset pin
                        SC_RST(1)       | 
                        SC_SCEN(1)      | 
                        SC_AUTO_ATR(1)  | 
                        SC_CONV(0)      |
                        SC_PS(p_this->parity));
                       
        p_this->atr_timeout = jiffies + HZ;                    
        
        SC_INFO("SC%d - FSM = RESET & ATR\n", id);
        
        break;
        
    case IFD_FSM_ACTIVE:
        SC_INFO("SC%d - FSM = ACTIVATE\n", id);
        
        SET_SCIRER(base, SC_CPRES_INT    | 
                        SC_ATRS_INT     | 
                        SC_RXP_INT      | 
                        SC_RCV_INT      |
                        SC_RX_FOVER_INT);        
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
 * Func : mars_scd_fsm_reset
 *
 * Desc : 
 *
 * Parm : p_this : handle of mars cec 
 *         
 * Retn : N/A  
 *------------------------------------------------------------------*/
void mars_scd_fsm_reset(mars_scd* p_this)
{
    unsigned long event  = GET_SCIRSR(p_this->base);    
    unsigned long rx_len = 0;
    unsigned long i      = 0;    
       
    SC_INT_DBG("mars_scd_fsm_reset : SC_RISR=%08lx\n", event);
                                            
    if ((event & SC_RXP_INT) || !(event & SC_PRES)|| time_after(jiffies, p_this->atr_timeout))
        goto err_atr_failed;        
    
    if (event & SC_ATRS_INT)
    {
        SC_INT_DBG("mars_scd_fsm_reset : Got ATR INT, reset ATR buffer\n");
        
        if (p_this->atr.length== -1)
            p_this->atr.length = 0;         // got ATR          
    }
            
    if (event & SC_RCV_INT)  
    {                                   
        SC_INT_DBG("mars_scd_fsm_reset : Got RCV INT, p_this->atr.length==%d, rx_len=%d\n", p_this->atr.length, GET_SC_RXLENR(p_this->base));
                
        if (p_this->atr.length<0)
        {                                   
            // unwanted data, drop it
            rx_len = GET_SC_RXLENR(p_this->base);
            
            for (i=0; i<rx_len; i++)
                GET_SC_RXFIFO(p_this->base);

            goto end_proc;                
        }
            
        // receive atr :                
        while(GET_SC_RXLENR(p_this->base))
        {
            if (p_this->atr.length >= MAX_ATR_SIZE)
                goto err_atr_failed;
                                      
            p_this->atr.data[p_this->atr.length] = GET_SC_RXFIFO(p_this->base);
                
            if (p_this->atr.length==0)
            {                
                switch(p_this->atr.data[0])
                {
                case 0x3B:
                    SC_INFO("SC%d - Direct Convention (%02x)\n", p_this->id, p_this->atr.data[0]);
                    break;
                    
                case 0x03:
                     p_this->atr.data[0] = 0x3F;
                     SC_INFO("SC%d - Inverse Convention (%02x)\n", p_this->id, p_this->atr.data[0]);
                     break;
                                
                default:
                    SC_WARNING("SC%d - unknown TS (%02x)\n", p_this->id, p_this->atr.data[0]);
                    break;                     
                }                   
            }
            
            p_this->atr.length++;

	     //wake_up(&p_this->wq);  //ATR do not use wq
        }        
                
        SC_INT_DBG("mars_scd_fsm_reset : p_this->atr.length=%d\n", p_this->atr.length);
        
        // check atr 
        if (is_atr_complete(&p_this->atr))
        {            
            SC_INFO("SC%d - Got ATR Completed\n", p_this->id);
            
            if (decompress_atr(&p_this->atr, &p_this->atr_info)<0)
                goto err_atr_failed;                                                           

            mars_scd_set_state(p_this, IFD_FSM_ACTIVE);       // jump to active state
        }
    }       
    
end_proc:
    SET_SCIRSR(p_this->base, event);
    return; 
    
err_atr_failed:

    if (!(event & SC_PRES))
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
                                                                
    mars_scd_set_state(p_this, IFD_FSM_DEACTIVATE);
    goto end_proc;
}



/*------------------------------------------------------------------
 * Func : mars_scd_fsm_active
 *
 * Desc : 
 *
 * Parm : p_this : handle of mars cec 
 *         
 * Retn : N/A  
 *------------------------------------------------------------------*/
void mars_scd_fsm_active(mars_scd* p_this)
{
    unsigned long event = GET_SCIRSR(p_this->base) & GET_SCIRER(p_this->base);
    unsigned char i;
    unsigned char len;
    unsigned char buff[TX_RX_DEPTH];
    
    if (mars_scd_card_detect(p_this)==0)
    {                                                   
        mars_scd_set_state(p_this, IFD_FSM_DEACTIVATE);       
        goto end_proc;
    }

    if (event & SC_RCV_INT && p_this->tx_status == SC_TX_DONE)  //RX received at least one character
   {
	    if ((len = GET_SC_RXLENR(p_this->base)))  
	    {
	        for (i=0; i<len; i++)
	        {
	            buff[i] = GET_SC_RXFIFO(p_this->base);
	        }
		SC_INFO("RX Receive~~  event=%d  len=%d  buf=0x%x \n",event,len,buff[0]);
	        if (kfifo_in_locked(&p_this->rx_fifo, buff, len, &p_this->rx_fifo_lock)<len)
	        {
	            SC_WARNING("mars_scd_fsm_active : fifo over flow... flush data...\n");   
	            kfifo_reset(&p_this->rx_fifo);
	        }

		  wake_up(&p_this->wq); 
	    }
	    
	    if (event & SC_RX_FOVER_INT)
	    {           
	        SC_WARNING("Rx over flow!\n");
	        SET_SCCR(p_this->base, GET_SCCR(p_this->base) | SC_FIFO_RST(1));
	    }
    }

#if 1
	if (event & SC_RCV_INT && p_this->tx_status != SC_TX_DONE)
	{
		SC_WARNING("RX Receive~~  event=%d  \n",event);
		SET_SCCR(p_this->base, GET_SCCR(p_this->base) | SC_FIFO_RST(1));
	}
#endif

    if (event & SC_TXEMPTY_INT)
    {
        int tx_data_len = kfifo_len(&p_this->tx_fifo);      // get number of data to xmit
        if (tx_data_len)
        {
            unsigned char tx_buff[TX_RX_DEPTH];
            
            tx_data_len = kfifo_out(&p_this->tx_fifo, tx_buff, sizeof(tx_buff));            
            
            SC_INFO("Send %d Bytes!\n", tx_data_len);
            for(i=0; i<tx_data_len; i++)
                SET_SC_TXFIFO(p_this->base, tx_buff[i]);
                
		    SET_SCCR(p_this->base, GET_SCCR(p_this->base) | SC_TX_GO(1));          // Start Xmit                
        }
        else
        {     
		SC_INFO("TX Done~~  \n");
            SET_SCIRER(p_this->base, GET_SCIRER(p_this->base) & ~SC_TXEMPTY_INT);
            p_this->tx_status = SC_TX_DONE;
            wake_up(&p_this->wq);                               // wakeup queue            
        }  
    }    

end_proc:
    SET_SCIRSR(p_this->base, event);
}

/*------------------------------------------------------------------
 * Func : mars_scd_work
 *
 * Desc : mars scd work routine
 *
 * Parm : p_this : handle of mars cec 
 *         
 * Retn : N/A  
 *------------------------------------------------------------------*/
void mars_scd_work(mars_scd* p_this)
{
    void __iomem *base = p_this->base;
    unsigned long status = GET_SCIRSR(base) & GET_SCIRER(base);

    SC_INFO("SC%d - work!!  FSM--%d  \n", p_this->id,p_this->fsm);               
    
    if (status & SC_CPRES_INT)            
    {           
        if (mars_scd_card_detect(p_this)) 
        {
            SC_INFO("SC%d - ICC detected!!\n", p_this->id);      
        }
        else 
        {
            mars_scd_set_state(p_this, IFD_FSM_DEACTIVATE);
            SC_INFO("SC%d - ICC removed!!\n", p_this->id);              
        }
            
        p_this->card_status_change = 1;            
        wake_up(&p_this->wq);           
    }
        
    switch (p_this->fsm)
    {       
    case IFD_FSM_RESET:    mars_scd_fsm_reset(p_this);  break;
    case IFD_FSM_ACTIVE:   mars_scd_fsm_active(p_this); break;
    default:
        break;
    }   

    SET_SCIRSR(base, status);
}



#ifdef ISR_POLLING     
/*------------------------------------------------------------------
 * Func : mars_scd_timer
 *
 * Desc : timer of mars scd
 *
 * Parm : arg : input param 
 *         
 * Retn : IRQ_NONE, IRQ_HANDLED
 *------------------------------------------------------------------*/
static void mars_scd_timer(unsigned long arg)        
{
    mars_scd* p_this = (mars_scd*) arg;
                   
    unsigned long event = GET_MIS_ISR(dts_info.misc+0xC) & MIS_SC_ISR[p_this->id];                        

    if (event)
        mars_scd_work(p_this);
                
    SET_MIS_ISR(dts_info.misc+0xC, event);
        
    mod_timer(&p_this->timer, jiffies + ISR_POLLING_INTERVAL);
}

#else


/*------------------------------------------------------------------
 * Func : mars_scd_isr
 *
 * Desc : isr of mars scd
 *
 * Parm : p_this : handle of mars scd 
 *        dev_id : handle of the mars_scd
 *        regs   :
 *         
 * Retn : IRQ_NONE, IRQ_HANDLED
 *------------------------------------------------------------------*/
static irqreturn_t mars_scd_isr(int this_irq, void *dev_id)
{
   // printk(KERN_ERR "[%s]:[%s] this_irq:[%d] -- [0x%x]\n", __FILE__, __func__, this_irq, readl(dts_info.misc + 0x80));

    mars_scd* p_this = (mars_scd*) dev_id;
    unsigned long flag;                   
    unsigned long event = GET_MIS_ISR(dts_info.misc+0xC) & MIS_SC_ISR[p_this->id];
   
    spin_lock_irqsave(&p_this->lock, flag);
    
    if (event)
        mars_scd_work(p_this);
                
    SC_INT_DBG("MIS ISR=%08x\n", GET_MIS_ISR(dts_info.misc+0xC));    
    
    SET_MIS_ISR(dts_info.misc+0xC, event);
                                          
    spin_unlock_irqrestore(&p_this->lock, flag);                               
                      
    return IRQ_HANDLED;    
}


#endif




/*------------------------------------------------------------------
 * Func : mars_scd_enable
 *
 * Desc : enable mars smart card interface
 *
 * Parm : p_this   : handle of mars scd  
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int mars_scd_enable(mars_scd* p_this, unsigned char on_off)
{
    int ret = 0;
    if (on_off)        
    {
        if (p_this->fsm==IFD_FSM_DISABLE)
        {
            ret =  mars_scd_set_state(p_this, IFD_FSM_DEACTIVATE);
            msleep(200);   // fix bug of get card status fail on darwin platform....
        }
    }
    else    
    {
        ret =  mars_scd_set_state(p_this, IFD_FSM_DISABLE);    
    }
    return ret;
}



/*------------------------------------------------------------------
 * Func : mars_scd_set_clock
 *
 * Desc : set clock frequency of mars smart card interface
 *
 * Parm : p_this   : handle of mars scd  
 *        clk      : clock (in HZ)
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int mars_scd_set_clock(mars_scd* p_this, unsigned long clk)
{
    unsigned long val; 
    unsigned long div = SYSTEM_CLK / clk / p_this->clock_div;    
        
    if (clk > MAX_SC_CLK)
    {
        SC_WARNING("clock %lu out of range, using minimum value to instead %lu\n", (unsigned long)clk, (unsigned long)MAX_SC_CLK);        
        clk = MAX_SC_CLK;
    }
        
    if (clk < MIN_SC_CLK)
    {
        SC_WARNING("clock %lu out of range, using minimum value to instead %lu\n", (unsigned long)clk, (unsigned long)MIN_SC_CLK);
        clk = MIN_SC_CLK;
    }
    
    p_this->pre_clock_div = div;    
    
    val  = GET_SCFP(p_this->base) & ~SC_PRE_CLKDIV_MASK;
    
    val |= SC_PRE_CLKDIV(p_this->pre_clock_div);
    
    SET_SCFP(p_this->base, val);
    
    return 0;
}



/*------------------------------------------------------------------
 * Func : mars_scd_get_clock
 *
 * Desc : get clock frequency of mars smart card interface
 *
 * Parm : p_this   : handle of mars scd  
 *        p_clock  : clock (in HZ)
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int mars_scd_get_clock(mars_scd* p_this, unsigned long* p_clock)
{   
    *p_clock = SYSTEM_CLK / (p_this->pre_clock_div) / (p_this->clock_div);
    return 0;
}



/*------------------------------------------------------------------
 * Func : mars_scd_set_etu
 *
 * Desc : set etu of mars smart card interface
 *
 * Parm : p_this   : handle of mars scd  
 *        etu      : cycles
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int mars_scd_set_etu(mars_scd* p_this, unsigned long etu)
{
    unsigned long val = (etu % 31);     
    unsigned char div2 = 0;     
    p_this->baud_div2 = 31;        
    
    if ((etu % 39) < val)
    {
        div2 = 2;
        p_this->baud_div2 = 39;
        val = (etu % 39);
    }
    
    if ((etu % 32) < val)
    {
        div2 = 1;
        p_this->baud_div2 = 32;
        val = (etu % 32);
    }
   
    p_this->baud_div1 = etu * p_this->clock_div / p_this->baud_div2;
    val = GET_SCFP(p_this->base) & ~SC_BAUDDIV_MASK;
    val |= SC_BAUDDIV1((p_this->baud_div1-1)) | SC_BAUDDIV2(div2);
    
    SC_INFO("ETU = %lu. Baud Div2=%lu, Div1 = %lu\n", etu, p_this->baud_div2 ,p_this->baud_div1);
    SET_SCFP(p_this->base, val);
    return 0;
}



/*------------------------------------------------------------------
 * Func : mars_scd_get_etu
 *
 * Desc : set etu of mars smart card interface
 *
 * Parm : p_this   : handle of mars scd  
 *        etu      : cycles
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int mars_scd_get_etu(mars_scd* p_this, unsigned long* p_etu)
{    
    *p_etu = (p_this->baud_div2 * p_this->baud_div1) / p_this->clock_div; 
    return 0;
}



/*------------------------------------------------------------------
 * Func : mars_scd_set_parity
 *
 * Desc : set parity of mars smart card interface
 *
 * Parm : p_this   : handle of mars scd  
 *        parity   : 0 : off,  others on
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int mars_scd_set_parity(mars_scd* p_this, SC_PARITY parity)
{
    switch(parity)
    {
    case SC_PARITY_NONE:
        p_this->parity = 0;
        break;
        
    case SC_PARITY_ODD:
    case SC_PARITY_EVEN:
        p_this->parity = 1;
        break;
    default:
        return SC_FAIL;    
    }               
     
    if (p_this->parity)        
        SET_SCCR(p_this->base, GET_SCCR(p_this->base) | SC_PS(p_this->parity));        
    else
        SET_SCCR(p_this->base, GET_SCCR(p_this->base) & ~SC_PS(p_this->parity));
        
    return 0;
}



/*------------------------------------------------------------------
 * Func : mars_scd_get_parity
 *
 * Desc : get parity setting of mars smart card interface
 *
 * Parm : p_this   : handle of mars scd  
 *        p_parity   : 0 : off,  others on
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int mars_scd_get_parity(mars_scd* p_this, SC_PARITY* p_parity)
{    
    *p_parity = (p_this->parity) ? SC_PARITY_EVEN : SC_PARITY_NONE;
    return 0;
}


/*------------------------------------------------------------------
 * Func : mars_scd_set_bwi
 *
 * Desc : set Block Waiting Integer
 *
 * Parm : p_this   : handle of mars scd
 *        bwi : Block Waiting Integer
 *
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/
int mars_scd_set_bwi(mars_scd* p_this, unsigned long bwi)
{
	if(bwi>0xF)
		bwi = 0xF;
    SET_SCPCR(p_this->base, (GET_SCPCR(p_this->base) & ~SC_BWI(0xF)) | SC_BWI(bwi));
    return 0;
}

/*------------------------------------------------------------------
 * Func : mars_scd_get_bwi
 *
 * Desc : set Block Waiting Integer
 *
 * Parm : p_this : handle of mars scd
 *        p_bwi : Block Waiting Integer
 *
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/
int mars_scd_get_bwi(mars_scd* p_this, unsigned long* p_bwi)
{
    *p_bwi = (GET_SCPCR(p_this->base) >> 16) & 0x0F;
    return 0;
}

/*------------------------------------------------------------------
 * Func : mars_scd_set_cwi
 *
 * Desc : set Character Waiting Integer
 *
 * Parm : p_this   : handle of mars scd
 *        cwi : Character Waiting Integer
 *
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/
int mars_scd_set_cwi(mars_scd* p_this, unsigned long cwi)
{
	if(cwi>0xF)
		cwi = 0xF;
    SET_SCPCR(p_this->base, (GET_SCPCR(p_this->base) & ~SC_CWI(0xF)) | SC_CWI(cwi));
    return 0;
}

/*------------------------------------------------------------------
 * Func : mars_scd_get_cwi
 *
 * Desc : set Character Waiting Integer
 *
 * Parm : p_this : handle of mars scd
 *        p_cwi : Character Waiting Integer
 *
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/
int mars_scd_get_cwi(mars_scd* p_this, unsigned long* p_cwi)
{
    *p_cwi = (GET_SCPCR(p_this->base) >> 20) & 0x0F;
    return 0;
}

/*------------------------------------------------------------------
 * Func : mars_scd_set_guard_interval
 *
 * Desc : set guard interval of icam smart card interface
 *
 * Parm : p_this   : handle of mars scd  
 *        guard_interval : guard interval in etu
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int mars_scd_set_guard_interval(mars_scd* p_this, unsigned long guard_interval)
{    

    if (guard_interval >= 0xFF)
        guard_interval = 0xFE;    
/* marked for Nagra ICC
    if (guard_interval<2)    
        guard_interval = 2;                    
*/
    SET_SCPCR(p_this->base, (GET_SCPCR(p_this->base) & ~SC_TXGRDT(0xFF)) | SC_TXGRDT(guard_interval));     
    return 0;
}


/*------------------------------------------------------------------
 * Func : mars_scd_get_guard_interval
 *
 * Desc : set guard interval
 *
 * Parm : p_this : handle of mars scd  
 *        p_guard_interval : guard interval output
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/ 
int mars_scd_get_guard_interval(mars_scd* p_this, unsigned long* p_guard_interval)
{       
    unsigned long guard_time = (GET_SCPCR(p_this->base) >> 24) & 0xFF;  
    //marked for Nagra ICC  
	//*p_guard_interval = (guard_time<0xFF) ? guard_time : 2;
    *p_guard_interval = guard_time;
	return 0;
}



/*------------------------------------------------------------------
 * Func : mars_scd_activate
 *
 * Desc : activate an ICC
 *
 * Parm : p_this   : handle of mars scd  
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/        
int mars_scd_activate(mars_scd* p_this)
{    
    switch(p_this->fsm)
    {
    case IFD_FSM_DISABLE:
        SC_WARNING("activate ICC failed, please enable IFD first\n");
        return SC_ERR_IFD_DISABLED;
        
    case IFD_FSM_DEACTIVATE:        
    
        if (mars_scd_reset(p_this)==0)
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
 * Func : mars_scd_deactivate
 *
 * Desc : deactivate an ICC
 *
 * Parm : p_this   : handle of mars scd  
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/        
int mars_scd_deactivate(mars_scd* p_this)
{    
    if (p_this->fsm != IFD_FSM_DISABLE)
    {
        mars_scd_set_state(p_this, IFD_FSM_DISABLE);
        mars_scd_set_state(p_this, IFD_FSM_DEACTIVATE);
    }
    return 0;
}




/*------------------------------------------------------------------
 * Func : mars_scd_reset
 *
 * Desc : reset mars smart card interface
 *
 * Parm : p_this   : handle of mars scd  
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/        
int mars_scd_reset(mars_scd* p_this)
{
    unsigned long t;

    wait_event_interruptible_timeout(p_this->wq,  p_this->fsm == IFD_FSM_DEACTIVATE, HZ>>1);    // wait for DEACTIVATE state , otherwise reset will be failed
    
    if (mars_scd_set_state(p_this, IFD_FSM_RESET))
        return SC_FAIL;
    
    t = jiffies + (HZ<<1);
    
    while(!time_after(jiffies,t) && p_this->fsm == IFD_FSM_RESET){ 
        //printk(KERN_ERR "...");
        msleep(100);    
    }
    //printk(KERN_ERR "\n");
    
    if (p_this->fsm != IFD_FSM_ACTIVE)
    {
        SC_WARNING("SC%d - Reset ICC failed\n", p_this->id);
        mars_scd_set_state(p_this, IFD_FSM_DEACTIVATE);
        return SC_ERR_ATR_TIMEOUT;     
    }
        
    SC_INFO("SC%d - Reset ICC Complete, atr_len=%d\n", p_this->id, p_this->atr.length);
    return SC_SUCCESS;
}



/*------------------------------------------------------------------
 * Func : mars_scd_get_atr
 *
 * Desc : s mars smart card interface
 *
 * Parm : p_this   : handle of mars scd  
 *        p_atr    : atr output buffer
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/        
int mars_scd_get_atr(mars_scd* p_this, scd_atr* p_atr)
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
 * Func : mars_scd_card_detect
 *
 * Desc : get card status
 *
 * Parm : p_this   : handle of mars scd  
 *         
 * Retn : 0 : no icc exists, others : icc exists
 *------------------------------------------------------------------*/   
int mars_scd_card_detect(mars_scd* p_this)
{               
    return (GET_SCIRSR(p_this->base) & SC_PRES) ? 1 : 0;                        
}



/*------------------------------------------------------------------
 * Func : mars_scd_get_card_status
 *
 * Desc : get card status
 *
 * Parm : p_this   : handle of mars scd  
 *         
 * Retn : 0 : no icc exists, others : icc exists
 *------------------------------------------------------------------*/   
int mars_scd_get_card_status(mars_scd* p_this)
{
    switch(p_this->fsm) {       
    case IFD_FSM_DISABLE:   return SC_CARD_REMOVED;                
    case IFD_FSM_DEACTIVATE:      return mars_scd_card_detect(p_this) ? SC_CARD_DEACTIVATE : SC_CARD_REMOVED;                        
    case IFD_FSM_RESET:     return SC_CARD_RESET;                                                            
    case IFD_FSM_ACTIVE:    return SC_CARD_ACTIVATE;                
    default:                return SC_CARD_UNKNOWN;
    }    
}



/*------------------------------------------------------------------
 * Func : mars_scd_poll_card_status
 *
 * Desc : poll card status change
 *
 * Parm : p_this   : handle of mars scd  
 *         
 * Retn : 0 : for success, others : fail
 *------------------------------------------------------------------*/   
int mars_scd_poll_card_status(mars_scd* p_this)
{               
    p_this->card_status_change = 0;
    wait_event_interruptible(p_this->wq, p_this->card_status_change); 
    return mars_scd_get_card_status(p_this);     
}



/*------------------------------------------------------------------
 * Func : mars_scd_xmit
 *
 * Desc : xmit data via smart card bus
 *
 * Parm : p_this   : handle of mars scd  
 *        scb      : data to be xmit
 *         
 * Retn : SC_SUCCESS / SC_FAIL
 *------------------------------------------------------------------*/        
int mars_scd_xmit(mars_scd* p_this, unsigned char* p_data, unsigned int len)
{   
	
    unsigned char id = p_this->id;
    void __iomem *base = p_this->base;
    unsigned char tx_buff[TX_RX_DEPTH];
    unsigned char tx_data_len;
    int i;
    SC_WARNING("0x%08x:0x%08x:0x%08x:  \n",GET_SCFP(base),GET_SCCR(base),GET_SCPCR(base));
    if (mars_scd_card_detect(p_this)==0)
        return SC_ERR_NO_ICC;
        
    if (p_this->fsm != IFD_FSM_ACTIVE)        
        return SC_ERR_ICC_DEACTIVATE;   
            
    kfifo_reset(&p_this->rx_fifo);
                
    kfifo_reset(&p_this->tx_fifo);
    
    if (kfifo_in(&p_this->tx_fifo, p_data, len)<len)
    {
        SC_WARNING("[SC%d] xmit data failed, tx fifo overflow\n", id);        
        return SC_FAIL;
    }
        
    // load tx data                
    tx_data_len = kfifo_out(&p_this->tx_fifo, tx_buff, sizeof(tx_buff));            
            
    for(i=0; i<tx_data_len; i++)     
        SET_SC_TXFIFO(base, tx_buff[i]);    
    
    //SC_WARNING("Send %d Bytes!\n", tx_data_len);
    
    // kick-off        
    p_this->tx_status = 0;
    
    SET_SCIRER(base, GET_SCIRER(base) | SC_TXEMPTY_INT);   // enable Tx empty interrupt    
    
    SET_SCCR(base, GET_SCCR(base) | SC_TX_GO(1));          // Start Xmit

//for the most INF of 254byte(add NAD,PCB,LEN,EDC is 258byte<32byte*16),the timeout must be 16 times of timer
    wait_event_interruptible_timeout(p_this->wq, (p_this->tx_status & SC_TX_DONE), HZ);
    
    SET_SCIRER(base, GET_SCIRER(base) & ~SC_TXEMPTY_INT);   // disable Tx empty interrupt
                
    if ((p_this->tx_status & SC_TX_DONE)==0)                
    {
        SC_WARNING("[SC%d] xmit data failed, tx timeout\n", id);    
        SET_SCCR(base, GET_SCCR(base) & ~SC_TX_GO(1));      // stop Xmit    
        return SC_FAIL;
    }   
    return SC_SUCCESS;
}                        




/*------------------------------------------------------------------
 * Func : mars_scd_read
 *
 * Desc : read data via smart card bus
 *
 * Parm : p_this   : handle of mars scd   
 *         
 * Retn : sc_buff
 *------------------------------------------------------------------*/        
int mars_scd_read(mars_scd* p_this, unsigned char* data, unsigned int len)
{    
    if (mars_scd_card_detect(p_this)==0)
        return SC_ERR_NO_ICC;

    wait_event_interruptible_timeout(p_this->wq, kfifo_len(&p_this->rx_fifo) >=len || (p_this->fsm != IFD_FSM_ACTIVE), HZ>>2);

    if (p_this->fsm != IFD_FSM_ACTIVE)
        return SC_ERR_ICC_DEACTIVATE;    

   return  kfifo_out_locked(&p_this->rx_fifo, data, len, &p_this->rx_fifo_lock);
}



/*------------------------------------------------------------------
 * Func : mars_scd_load_gpio_config
 *
 * Desc : Load Gpio Config
 *
 * Parm : p_this   : handle of mars scd   
 *         
 * Retn : sc_buff
 *------------------------------------------------------------------*/ 
static void mars_scd_load_gpio_config(mars_scd* p_this)
{   
    /**************************************
     * SCx Command format
     **************************************
        : cmd_vcc_en        (0: no cmd_vcc_gpio, 1: with cmd_vcc_gpio)
        : cmd_vcc_polarity  (0: negative, 1: positive)
        : cmd_vcc_gpio_type (0: MISC, 1: ISO)
        : --                    
        : pwr_sel_en        (0: no cmd_vcc_gpio, 1: with cmd_vcc_gpio)
        : pwr_sel_polarity  (0: negative, 1: positive)
        : pwr_sel_gpio_type (0: MISC, 1: ISO)
        : --           
        : cmd_vcc_gpio
        : pwr_sel_gpio
     **************************************/

    p_this->cmd_vcc_en       = dts_info.cmd_vcc_en;
    p_this->cmd_vcc_polarity = dts_info.cmd_vcc_polarity;
    p_this->pin_cmd_vcc      = 22;

    p_this->cmd_vcc_en       = dts_info.cmd_vcc_en;
    p_this->cmd_vcc_polarity = dts_info.cmd_vcc_polarity;
    p_this->pin_pwr_sel      = 53;
        
    SC_INFO("SC%d - cmd_vcc(en=%d, polarity=%d, pin=%s_GPIO[%d]), pwr_sel(en=%d,polarity=%d,pin=%s_GPIO[%d])\n", 
            p_this->id, 
            p_this->cmd_vcc_en, 
            p_this->cmd_vcc_polarity, 
            gpio_type(gpio_group(p_this->pin_cmd_vcc)), 
            gpio_idx(p_this->pin_cmd_vcc),
            p_this->pwr_sel_en, 
            p_this->pwr_sel_polarity, 
            gpio_type(gpio_group(p_this->pin_pwr_sel)), 
            gpio_idx(p_this->pin_pwr_sel));                    
}


/*------------------------------------------------------------------
 * Func : mars_clk_reset_ctrl
 *
 * Desc :
 *
 * Parm :
 *         
 * Retn :
 *------------------------------------------------------------------*/
static int mars_clk_reset_ctrl(SCD_CLK_CTL enable)
{
#if 0
    struct reset_control *reset = rstc_get("rstn_misc_sc");
    struct clk *clk = clk_get(NULL, "clk_en_misc_sc");

    if(enable == CTL_ENABLE){
        reset_control_deassert(reset);
        clk_prepare_enable(clk);
    }else{
        clk_disable(clk);
    }
#endif
    if(enable == CTL_ENABLE){
        reset_control_deassert(dts_info.rstc);
        clk_prepare_enable(dts_info.clk);
    }else{
        clk_disable_unprepare(dts_info.clk);
        reset_control_assert(dts_info.rstc);
    }

}


/*------------------------------------------------------------------
 * Func : mars_scd_open
 *
 * Desc : open a mars scd device
 *
 * Parm : id  : channel id
 *         
 * Retn : handle of mars scd
 *------------------------------------------------------------------*/
mars_scd* mars_scd_open(unsigned char id)
{           
    mars_scd* p_this;
    //void __iomem *gpio = ioremap(0x9801B000, 0x120);
    
    if (id >= MAX_IFD_CNT) {
        SC_WARNING("scd : open %s scd failed, invalid id - %d\n", IFD_MODOLE, id);
        return NULL;
    }

    p_this = (mars_scd*) kmalloc(sizeof(mars_scd), GFP_KERNEL);

    if (p_this)
    {
        memset(p_this, 0, sizeof(mars_scd));

        p_this->base    = dts_info.base; 
        p_this->id      = dts_info.id;
        p_this->fsm     = IFD_FSM_UNKNOWN;
        p_this->atr.length = -1;

        if (kfifo_alloc(&p_this->rx_fifo, 1024, GFP_KERNEL)<0)
        {
            SC_WARNING("scd : open %s scd(%d) failed, create rx fifo failed\n", IFD_MODOLE, id);
            kfree(p_this);
            return NULL;
        }

        if (kfifo_alloc(&p_this->tx_fifo, 1024, GFP_KERNEL)<0)
        {
            SC_WARNING("scd : open %s scd(%d) failed, create tx fifo failed\n", IFD_MODOLE, id);
            kfifo_free(&p_this->rx_fifo);
            kfree(p_this);
            return NULL;
        }

        mars_clk_reset_ctrl(CTL_ENABLE);
#if 0
        /* reset smartcart crt */
        writel(readl(dts_info.crt + 0x4) | (0x1 << 29), dts_info.crt + 0x4);

        /* enable clock */
        writel(readl(dts_info.crt + 0x10) | (0x1 << 6), dts_info.crt + 0x10);

        /* set padmux */
        writel(readl(dts_info.padmux + 0x314) | 0xFF0000, dts_info.padmux + 0x314);
#endif
        /* set misc interrupt */
        writel(readl(dts_info.misc + 0x80) | (0x1 << 24), dts_info.misc + 0x80);
        //writel(readl(dts_info.misc + 0x80) & 0xFEFFFFFF , dts_info.misc + 0x80);
        //writel(readl(dts_info.misc + 0x80) | (0x1 << 24), dts_info.misc + 0x80);

        spin_lock_init(&p_this->lock);
        spin_lock_init(&p_this->rx_fifo_lock);
        init_waitqueue_head(&p_this->wq);

        p_this->clock_div        = 1;
        p_this->pre_clock_div    = (unsigned char)(SYSTEM_CLK/3000000);
        p_this->baud_div1        = 12;        // default etu = 372 = 31 * 12
        p_this->baud_div2        = 31;
        p_this->parity           = 1;
        p_this->vcc_5v           = 0;

        mars_scd_load_gpio_config(p_this);
#if 1
        if (p_this->cmd_vcc_en)
        {
            //venus_gpio_output(p_this->pin_cmd_vcc, (p_this->cmd_vcc_polarity) ? 0 : 1);     // power off
            //venus_gpio_set_dir(p_this->pin_cmd_vcc, 1);   // set power ping to output mode
            gpio_direction_output(p_this->pin_cmd_vcc, (p_this->cmd_vcc_polarity) ? 0 : 1);
        }

        if (p_this->pwr_sel_en)
        {
            //venus_gpio_output(p_this->pin_pwr_sel, (p_this->pwr_sel_polarity) ? 0 : 1);     // 3.3v
            //venus_gpio_set_dir(p_this->pin_pwr_sel, 1);   // set power ping to output mode
            gpio_direction_output(p_this->pin_pwr_sel, (p_this->pwr_sel_polarity) ? 0 : 1);
        }
#endif
#if 0
        /* set gpio */
        printk(KERN_ERR "gpio+110:[0x%x]\n", readl(gpio + 0x110));
        printk(KERN_ERR "gpio+100:[0x%x]\n", readl(gpio + 0x100));
        writel(readl(gpio + 0x110) | 0x1000, gpio + 0x110);
        writel(readl(gpio + 0x100) | 0x1800, gpio + 0x100);
        writel(readl(gpio + 0x110) | 0x1800, gpio + 0x110);
        writel(readl(gpio + 0x110) & 0xFFFFF7FF, gpio + 0x110);
        printk(KERN_ERR "gpio+110:[0x%x]\n", readl(gpio + 0x110));
        printk(KERN_ERR "gpio+100:[0x%x]\n", readl(gpio + 0x100));
#endif
        // Set All Register to the initial value
        SET_SCFP(p_this->base, SC_CLK_EN(1)    |
                            SC_CLKDIV((p_this->clock_div-1))|
                            SC_BAUDDIV2(0)  |                    // fixed to 31
                            SC_BAUDDIV1((p_this->baud_div1-1))|
                            SC_PRE_CLKDIV((p_this->pre_clock_div-1)));

        SET_SCCR(p_this->base, SC_FIFO_RST(1)  |
                            SC_SCEN(1)      |
                            SC_AUTO_ATR(1)  |
                            SC_CONV(0)      |
                            SC_PS(0));

        SET_SCPCR(p_this->base,SC_TXGRDT(2)    |
                            SC_CWI(0)       |
                            SC_BWI(0)       |
                            SC_WWI(0)       |
                            SC_BGT(0x16)    |
                            SC_EDC_EN(0)    |
                            SC_CRC(0)       |
                            SC_PROTOCOL_T(0)|
                            SC_T0RTY(0)     |
                            SC_T0RTY_CNT(0) );

        SET_SCIRER(p_this->base, 0);

        SET_SCIRSR(p_this->base, 0xFFFFFFFF);

#ifdef ISR_POLLING
        init_timer(&p_this->timer);
        p_this->timer.data     = (unsigned long)p_this;
        p_this->timer.function = mars_scd_timer;
        p_this->timer.expires  = jiffies + ISR_POLLING_INTERVAL;
        add_timer(&p_this->timer);      // register timer
#else
        p_this->irq = dts_info.irq;
        //if (request_irq(p_this->irq, mars_scd_isr, SA_SHIRQ, "MARS SCD", (void *) p_this) < 0)
        if (request_irq(p_this->irq, mars_scd_isr, IRQF_SHARED, "MARS SCD", (void *) p_this) < 0)
        {
            SC_WARNING("scd : open %s scd failed, unable to request irq#%d\n", IFD_MODOLE, p_this->irq); 
            kfifo_free(&p_this->tx_fifo);
            kfifo_free(&p_this->rx_fifo);
            kfree(p_this);          
            return NULL;
        }       
        
        printk(KERN_ERR "scd : open %s scd and request irq#%d successfully.\n", IFD_MODOLE, p_this->irq);
#endif
        mars_scd_set_state(p_this, IFD_FSM_DISABLE);
    }	
    else{
        SC_WARNING("scd : open mars scd failed\n");
        return NULL;
    }
    return p_this;
}    


/*------------------------------------------------------------------
 * Func : mars_scd_close
 *
 * Desc : close a mars scd device
 *
 * Parm : p_this  : mars scd to be close
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
void mars_scd_close(mars_scd* p_this)
{
#ifdef ISR_POLLING             
    del_timer(&p_this->timer);      // register timer
#else
    free_irq(MISC_IRQ ,p_this);    
#endif    

    kfifo_free(&p_this->rx_fifo);
    kfifo_free(&p_this->tx_fifo);   
    mars_scd_set_state(p_this, IFD_FSM_DISABLE);    
    wake_up(&p_this->wq);   
    kfree(p_this);        
}    


