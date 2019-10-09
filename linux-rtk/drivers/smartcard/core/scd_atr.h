#ifndef __SCD_ATR_H__
#define __SCD_ATR_H__

typedef struct 
{
    unsigned char status;           // parse status
    unsigned char progress;         // parse progress
    
    unsigned char T1Len;
    unsigned char T2Len;
    unsigned char T3Len;
    unsigned char nHistoryBytes;
    
    //----------  info          
    unsigned char TS;
    unsigned char T0;
    unsigned char T1[4];    
    unsigned char T2[4];
    unsigned char T3[4];    
    unsigned char History[16];
    unsigned char TCK;                        
}scd_atr_info;


#define get_ta1(p_atr_info)        (p_atr_info->T1[0])
#define get_tb1(p_atr_info)        (p_atr_info->T1[1])
#define get_tc1(p_atr_info)        (p_atr_info->T1[2])
#define get_td1(p_atr_info)        (p_atr_info->T1[3]) 

#define get_ta2(p_atr_info)        (p_atr_info->T2[0])
#define get_tb2(p_atr_info)        (p_atr_info->T2[1])
#define get_tc2(p_atr_info)        (p_atr_info->T2[2])
#define get_td2(p_atr_info)        (p_atr_info->T2[3])

#define get_ta3(p_atr_info)        (p_atr_info->T3[0])
#define get_tb3(p_atr_info)        (p_atr_info->T3[1])
#define get_tc3(p_atr_info)        (p_atr_info->T3[2])
#define get_td3(p_atr_info)        (p_atr_info->T3[3])

#define has_ta1(p_atr_info)        (p_atr_info->T0 & 0x10)
#define has_tb1(p_atr_info)        (p_atr_info->T0 & 0x20)
#define has_tc1(p_atr_info)        (p_atr_info->T0 & 0x40)
#define has_td1(p_atr_info)        (p_atr_info->T0 & 0x80)

#define has_ta2(p_atr_info)        (has_td1(p_atr_info) && (get_td1(p_atr_info) & 0x10))
#define has_tb2(p_atr_info)        (has_td1(p_atr_info) && (get_td1(p_atr_info) & 0x20))
#define has_tc2(p_atr_info)        (has_td1(p_atr_info) && (get_td1(p_atr_info) & 0x40))
#define has_td2(p_atr_info)        (has_td1(p_atr_info) && (get_td1(p_atr_info) & 0x80))

#define has_ta3(p_atr_info)        (has_td2(p_atr_info) && (get_td2(p_atr_info) & 0x10))
#define has_tb3(p_atr_info)        (has_td2(p_atr_info) && (get_td2(p_atr_info) & 0x20))
#define has_tc3(p_atr_info)        (has_td2(p_atr_info) && (get_td2(p_atr_info) & 0x40))
#define has_td3(p_atr_info)        (has_td2(p_atr_info) && (get_td2(p_atr_info) & 0x80))

#define ta1_f(p_atr_info)          ((get_ta1(p_info)>>4)& 0xF)
#define ta1_d(p_atr_info)          (get_ta1(p_info) & 0xF)
#define tc1_n(p_atr_info)          (get_tc1(p_atr_info) & 0xFF)
#define td1_protocol(p_atr_info)   (get_td1(p_atr_info) & 0xF)

#define td2_protocol(p_atr_info)   (get_td2(p_atr_info) & 0xF)
#define td2_wi(p_atr_info)         (get_tc2(p_atr_info) & 0xFF)

#define ta3_ifsc(p_atr_info)       (get_ta3(p_atr_info) & 0xFF)
#define tb3_cwi(p_atr_info)        (get_td3(p_atr_info) & 0xF)
#define tb3_bwi(p_atr_info)        ((get_td3(p_atr_info)>>4) & 0xF)

typedef struct 
{
    int           length;
    #define MAX_ATR_SIZE    128    
    unsigned char data[MAX_ATR_SIZE];    
}scd_atr;


#define ATR_COMPLETE        0x80


typedef enum {
    VALID_ATR,
    INVALID_ATR,
    INCOMPLETE_ATR,
}atr_status;


extern int  is_atr_complete(scd_atr* p_atr);
extern int  decompress_atr(scd_atr* p_atr, scd_atr_info* p_info);
extern void init_atr(scd_atr* p_atr);

#define SC_ATR_DBG          printk

#endif  //__SCD_ATR_H__

