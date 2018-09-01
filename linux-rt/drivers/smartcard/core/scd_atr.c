#include <linux/kernel.h>
#include <linux/module.h>
#include "scd_atr.h"
#include "scd_debug.h"

MODULE_LICENSE("GPL");


//#define COMPRESS_ATR_DEBUG_EN

/*------------------------------------------------------------------
 * Func : is_atr_crc_ok
 *
 * Desc : check is the atr_complete or not
 *
 * Parm : scd_atr : atr to check 
 *         
 * Retn : 1 : complete, 0 : not complete  
 *------------------------------------------------------------------*/
int is_atr_crc_ok(scd_atr* p_atr)
{    
    int i;
    unsigned char crc = 0;
        
    for (i=1; i<p_atr->length; i++) // from T0 to TCK
    {
        crc ^= p_atr->data[i];     
    }        
    
    return (crc==0) ? 1 : 0;        
}


/*------------------------------------------------------------------
 * Func : is_atr_complete
 *
 * Desc : check is the atr_complete or not
 *
 * Parm : scd_atr : atr to check 
 *         
 * Retn : 1 : complete, 0 : not complete  
 *------------------------------------------------------------------*/
int is_atr_complete(scd_atr* p_atr)
{    
    unsigned char  TS    = 0;
    unsigned char  T0    = 0;
    unsigned char  TD1   = 0;
    unsigned char  TD2   = 0;    
    unsigned char  nHistoryByte = 0;
    unsigned char  T1Len = 0;
    unsigned char  T2Len = 0;
    unsigned char  T3Len = 0;
    unsigned char  T     = 0;       
                    
    if (p_atr->length < 3)
        return 0;
    
    //-------- header complete ---------
    TS = p_atr->data[0];
    
    if ((TS!=0x3B) && (TS!=0x3F))      
        return 1;    
            
    T0 = p_atr->data[1];
    
    nHistoryByte = T0 & 0xF;
         
    T1Len = ((T0 >> 4) & 0x01) +
            ((T0 >> 5) & 0x01) +
            ((T0 >> 6) & 0x01) +
            ((T0 >> 7) & 0x01) ;                                                            
                            
    if (p_atr->length <  2 + T1Len)
        return 0;
        
    //-------- TX1 complete ------------
        
    if (T0 & 0x80)         
    {           
        // TD1 exists - find length of TD2
        TD1 = p_atr->data[1 + T1Len];
        T2Len = ((TD1 >> 4) & 0x01) +
                ((TD1 >> 5) & 0x01) +
                ((TD1 >> 6) & 0x01) +
                ((TD1 >> 7) & 0x01) ; 
                
        T   = TD1 & 0xF;                                      
    }
    
    if (p_atr->length <  2 + T1Len + T2Len)
        return 0;
    
    //-------- TX2 complete ------------
    
    if (TD1 & 0x80)     
    {             
        // TD2 exists - find length of TD3
        TD2   = p_atr->data[1 + T1Len + T2Len];
        T3Len = ((TD2 >> 4) & 0x01)+
                ((TD2 >> 5) & 0x01)+
                ((TD2 >> 6) & 0x01)+
                ((TD2 >> 7) & 0x01);                                                                                                        
    }                        
    
    //-------- TX3 & header complete ------------    
    switch(T)
    {
    case 0:
    case 15:    
        // for T=0 or T=15, TCK should be absent
        if (p_atr->length <  2 + T1Len + T2Len + T3Len + nHistoryByte)
            return 0;
            
        return 1;                    
        
    default:
        if (p_atr->length <  3 + T1Len + T2Len + T3Len + nHistoryByte)
            return 0;
                
        return (!is_atr_crc_ok(p_atr)) ? -1 : 1;                                  
    }
}




/*------------------------------------------------------------------
 * Func : decompress_atr
 *
 * Desc : decompress_atr
 *
 * Parm : scd_atr : atr to check 
 *         
 * Retn : 1 : success, others : failed  
 *------------------------------------------------------------------*/
int decompress_atr(scd_atr* p_atr, scd_atr_info* p_info)
{
    unsigned char id = 0;
    unsigned char i  = 0;
    int ret = is_atr_complete(p_atr);
    
    switch (ret)
    {    
    case 0:
        SC_WARNING("Incomplete ATR\n");
        return -1;
    case -1:
        SC_WARNING("ATR CRC Error\n");
        //return -1;                    
    }            
                
#ifdef COMPRESS_ATR_DEBUG_EN
    SC_ATR_DBG("ATR Len = %d\n", p_atr->length);
    SC_ATR_DBG("ATR = ");
    for (i=0; i<p_atr->length; i++)    
        SC_ATR_DBG(" %02x\n", p_atr->data[i]);
#endif
        
    memset(p_info, 0, sizeof(*p_info));
            
    p_info->TS = p_atr->data[id++];
        
    p_info->T0 = p_atr->data[id++];        
    
    for (i=0; i<4; i++)    
        if (p_info->T0 & (0x10 << i))
            p_info->T1[i] = p_atr->data[id++];        
    
    for (i=0; i<4; i++)    
        if (p_info->T1[3] & (0x10 << i))
            p_info->T2[i] = p_atr->data[id++];        
    
    for (i=0; i<4; i++)    
        if (p_info->T2[3] & (0x10 << i))
            p_info->T3[i] = p_atr->data[id++];        
           
    switch (p_info->T1[3] & 0xF)
    {           
    case 0:
    case 15:
        if ((p_atr->length - id) != (p_info->T0 & 0xF))
        {
            SC_WARNING("too much history bytes %d/%d \n", p_atr->length - id, p_info->T0 & 0xF);
            return -1;
        }
        break;
    default:
        if ((p_atr->length - id -1) != (p_info->T0 & 0xF))
        {
            SC_WARNING("too much history bytes %d/%d \n", p_atr->length - id -1, p_info->T0 & 0xF);
            return -1;
        }        
    }
    memcpy(p_info->History, &p_atr->data[id], (p_info->T0 & 0xF));
    
    p_info->TCK = p_atr->data[p_atr->length-1];
                                        
    return 0;                                
}





/*------------------------------------------------------------------
 * Func : is_atr_complete
 *
 * Desc : check is the atr_complete or not
 *
 * Parm : scd_atr : atr to check 
 *         
 * Retn : 1 : complete, 0 : not complete  
 *------------------------------------------------------------------*/
void init_atr(scd_atr* p_atr)
{    
    memset(p_atr, 0, sizeof(scd_atr));
    p_atr->length        = 0;            
}



EXPORT_SYMBOL(init_atr);
EXPORT_SYMBOL(decompress_atr);
EXPORT_SYMBOL(is_atr_complete);

