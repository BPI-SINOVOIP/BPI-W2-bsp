#ifndef _MCP_DEFINES_H_INCLUDED_
#define _MCP_DEFINES_H_INCLUDED_
enum {E_MODE_DES=0,
      E_MODE_TDES=1,
      E_MODE_RC4=2,
      E_MODE_MD5=3,
      E_MODE_SHA1=4,
      E_MODE_AES128=5,
      E_MODE_AES192=29,
      E_MODE_AES256=21,
      E_MODE_AES_G=6,
      E_MODE_AES_H=7,
      E_MODE_CMAC=8,
      E_MODE_CSA=9,
      E_MODE_MULTI2=10,
      E_MODE_SHA256=11,
      E_MODE_BYPASS=31,
      //E_MODE_CRC=12,
      //E_MODE_CRC_SHA256=13,
      E_MODE_LOAD_MICRO_CODE=14,
      E_MODE_MICRO_CODE=15,
      E_MODE_DECSS=17,
      E_MODE_BDR=28,
      E_MODE_BDP=27,
      E_MODE_HDR_SOB=26,
      E_MODE_HDR_VOB=25,
      E_MODE_HDP=24,
      E_MODE_CPRM=19,
      E_MODE_CPPM=18};
enum {E_BCM_ECB=0,E_BCM_CBC=1,E_BCM_CTR=2,E_BCM_RCBC_CS=3,E_BCM_CBC_CS3=7,E_BCM_CBC_CS2=11,E_BCM_CBC_CS1=15};
enum {E_ENDE_DE = 0,E_ENDE_EN=1};
enum {E_OTP_SEL_KN=0,E_OTP_SEL_KH=1,E_OTP_SEL_KS=2};
enum {E_KEY_SEL_DT=0,E_KEY_SEL_OTP=1,E_KEY_SEL_CW=2,E_KEY_SEL_DDR=3};

enum {E_RCP_MODE_AES128=0,
      E_RCP_MODE_TDES=1,
      E_RCP_MODE_DES=2,
      E_RCP_MODE_AES192=3,
      E_RCP_MODE_AES256=4,
      E_RCP_MODE_TDES_DROP_LSB=5,
      E_RCP_MODE_DES_DROP_LSB=6,
      E_RCP_MODE_TDES_DROP_MSB=13,
      E_RCP_MODE_DES_DROP_MSB=14};
enum {E_RCP_CBC=1,E_RCP_ECB=0};      
enum {E_RCP_KEY_MODE_REG=0,E_RCP_KEY_MODE_CW=1,E_RCP_KEY_MODE_OTP_KN=2,E_RCP_KEY_MODE_OTP_KH=3,E_RCP_KEY_MODE_OTP_KS=4};
enum {E_RCP_IV_MODE_REG=0,E_RCP_IV_MODE_CW=1};
enum {E_RCP_INPUT_MODE_REG=0,E_RCP_INPUT_MODE_CW=1};
enum {E_RCP_OUTPUT_MODE_REG=0,E_RCP_OUTPUT_MODE_CW=1};
enum {E_CPU_SCPU=0,E_CPU_KCPU=1};
#ifdef SCPU_ARM
    #define SET_CP_ISR_NWC(addr) SET_INT(INTERRUPT_SCPU_CP_NWC,(void*)addr)
    #define SET_CP_ISR_SWC(addr) SET_INT(INTERRUPT_SCPU_CP_SWC,(void*)addr)
    #define CP_DATA_BASE 0x00160000
#else
    #define SET_CP_ISR_NWC(addr) *((volatile*) HW_INTVEC_ADDR5) = (void*) addr
    #define SET_CP_ISR_SWC(addr) *((volatile*) HW_INTVEC_ADDR5_KCPU) = (void*) addr
    #define CP_DATA_BASE 0
#endif
#define CP_BYTE_SWAP(data)\
       ((((data) & 0xFF000000)>>24)  |\
        (((data) & 0x00FF0000)>> 8)  |\
        (((data) & 0x0000FF00)<< 8)  |\
        (((data) & 0x000000FF)<<24))

#define DT_SIZE  56
#define MCP_DATA_OFFSET(data)    (0xFF000000&((data)<<24))
#define MCP_OTP_SEL(data)        (0x00300000&((data)<<20))
#define MCP_MICRO_CODE_SEL(data) (0x000C0000&((data)<<18))
#define MCP_INIKEY_REG3(data)    (0x00020000&((data)<<17))
#define MCP_SHORT_BLOCK(data)    (0x00018000&((data)<<15))
#define MCP_INIKEY_REG2(data)    (0x00004000&((data)<<14))
#define MCP_KEY_SEL(data)        (0x00003000&((data)<<12))
#define MCP_INIKEY_REG(data)     (0x00000800&((data)<<11))
#define MCP_STATE_DUMP(data)     (0x00000400&((data)<<10))
#define MCP_BCM(data)            (0x000003C0&((data)<< 6))
#define MCP_ENDE(data)           (0x00000020&((data)<< 5))
#define MCP_MODE(data)           (0x0000001F&((data)<< 0))

#define CW_IV_ADDR(data)      (0x0000007f&((data)<<0))
#define CW_KEY_ADDR(data)     (0x00007f00&((data)<<8))
#define CW_SYSKEY_ADDR(data)  (0x007f0000&((data)<<16))

#define SET_DDR(addr,data)                (*(unsigned int *) (0xa0000000|(addr)) = (data))
#define SET_DT_WD0(base_addr,data)        SET_DDR(base_addr+ 0, data)
#define SET_DT_KEY0(base_addr,data)       SET_DDR(base_addr+ 4, data)
#define SET_DT_KEY1(base_addr,data)       SET_DDR(base_addr+ 8, data)
#define SET_DT_KEY2(base_addr,data)       SET_DDR(base_addr+12, data)
#define SET_DT_KEY3(base_addr,data)       SET_DDR(base_addr+16, data)
#define SET_DT_KEY4(base_addr,data)       SET_DDR(base_addr+20, data)
#define SET_DT_KEY5(base_addr,data)       SET_DDR(base_addr+24, data)
#define SET_DT_INI_KEY0(base_addr,data)   SET_DDR(base_addr+28, data)
#define SET_DT_INI_KEY1(base_addr,data)   SET_DDR(base_addr+32, data)
#define SET_DT_INI_KEY2(base_addr,data)   SET_DDR(base_addr+36, data)
#define SET_DT_INI_KEY3(base_addr,data)   SET_DDR(base_addr+40, data)
#define SET_DT_SADR(base_addr,data)       SET_DDR(base_addr+44, data)
#define SET_DT_DADR(base_addr,data)       SET_DDR(base_addr+48, data)
#define SET_DT_BC(base_addr,data)         SET_DDR(base_addr+52, data)
#endif
