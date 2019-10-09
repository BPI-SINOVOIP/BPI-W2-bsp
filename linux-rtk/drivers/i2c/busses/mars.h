/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Defines of the Mars cpu's specific address-MAP, registers, etc. Mars cpu
 * inherits most of the defines of Venus cpu.
 *
 * Copyright (C) 2010 by Chien-An Lin <colin@realtek.com.tw>
 */

#ifndef _MACH_MARS_H
#define _MACH_MARS_H

//#include <asm/addrspace.h>
#include "venus.h"

#define ISO_IO_PORT_BASE		VENUS_ISO_IO_PORT_BASE  
#define MISC_IO_PORT_BASE		VENUS_MISC_IO_PORT_BASE  

/*-------------------------------------------------------------
 * Mars CP
 *-------------------------------------------------------------*/

#define MARS_MCP_CTRL             0xb8015100
    #define MCP_GO                (0x01<<1)
    #define MCP_IDEL              (0x01<<2)
    #define MCP_SWAP              (0x01<<3)
    #define MCP_CLEAR             (0x01<<4)
    #define MCP_CHK_SYS_HDR       (0x01<<5)     /* this bit has been removed from jupiter cpu */        
    #define MCP_ARB_MODE(x)       ((x & 0x01)<<6)     /* for Jupiter only */        
    #define MCP_OFB_1(x)          ((x & 0x01)<<7)     /* for Jupiter only */
    #define MCP_OFB_2(x)          ((x & 0x01)<<8)     /* for Jupiter only */

#define MARS_MCP_STATUS           0xb8015104          

    #define MCP_WRITE_DATA        (0x01)
    #define MCP_RING_EMPTY        (0x01 <<1)
    #define MCP_ERROR             (0x01 <<2)
    #define MCP_COMPARE           (0x01 <<3)
    #define MCP_HDR_OTHER_PCAK    (0x01 <<4)    /* this bit has been removed from jupiter cpu */        
    #define MCP_HDP_OTHER_PCAK    (0x01 <<5)    /* this bit has been removed from jupiter cpu */        
    #define MCP_ACP_ERR           (0x01 <<6)    
    #define MCP_SYS_HDR_ERR       (0x01 <<7)    /* this bit has been removed from jupiter cpu */                    
    
#define MARS_MCP_EN               0xb8015108
#define MARS_MCP_BASE             0xb801510C
#define MARS_MCP_LIMIT            0xb8015110
#define MARS_MCP_RDPTR            0xb8015114
#define MARS_MCP_WRPTR            0xb8015118
#define MARS_MCP_AES_INI_KEY0     0xb8015124
#define MARS_MCP_AES_INI_KEY1     0xb8015128
#define MARS_MCP_AES_INI_KEY2     0xb801512C
#define MARS_MCP_AES_INI_KEY3     0xb8015130
#define MARS_MCP_DES_COUNT        0xb8015148
#define MARS_MCP_DES_COMPARE      0xb8015138
#define JUPITER_MCP_CTRL1         0xb8015198    /* for Jupiter only */
    #define MCP_AES_PAD_OFF(x)    ((x & 0x1)<<10)
    #define MCP_CSA_ENTROPY(x)    ((x & 0x3)<<8)
        #define ORIGIONAL_MODE    0x0
        #define CSA_MODE_1        0x1
        #define CSA_MODE_2        0x2
    #define MCP_ROUND_NO(x)       ((x & 0xFF))

// Descriptor Definition
#define MARS_MCP_MODE(x)     (x & 0x1F)   

#define MCP_ALGO_DES         0x00
#define MCP_ALGO_3DES        0x01
#define MCP_ALGO_RC4         0x02
#define MCP_ALGO_MD5         0x03
#define MCP_ALGO_SHA_1       0x04
#define MCP_ALGO_AES         0x05
#define MCP_ALGO_AES_G       0x06
#define MCP_ALGO_AES_H       0x07
#define MCP_ALGO_CMAC        0x08

#define MARS_MCP_BCM(x)     ((x & 0x3) << 6)  
#define MCP_BCM_ECB          0x0
#define MCP_BCM_CBC          0x1
#define MCP_BCM_CTR          0x2

#define MARS_MCP_ENC(x)     ((x & 0x1) << 5)  

#define MARS_MCP_KEY_SEL(x) ((x & 0x1) << 12)  
#define MCP_KEY_SEL_OTP      0x1
#define MCP_KEY_SEL_DESC     0x0

#define MARS_MCP_IV_SEL(x)  ((x & 0x1) << 11)  
#define MCP_IV_SEL_REG      0x1
#define MCP_IV_SEL_DESC     0x0

/*-------------------------------------------------------------
 * Mars CRT
 *-------------------------------------------------------------*/
#define MARS_CRT_BASE			0xB8000000
#define MARS_CRT_PCICK_SEL		0x0338


/*-------------------------------------------------------------
 * Mars MISC 
 *-------------------------------------------------------------*/

#define MARS_MIS_BASE			0xB8010000

#define MARS_MIS_ISR			VENUS_MIS_ISR
#define MARS_PCMCIA_INT			(0x00000001 <<21)
#define MARS_MIS_ISR_CEC_TX    	(0x00000001 <<22)
#define MARS_MIS_ISR_CEC_RX   	(0x00000001 <<23)
#define MARS_MIS_ISR_I2C1     	(0x00000001 <<4)
#define MARS_MIS_ISR_I2C2     	(0x00000001 <<26)
#define MARS_MIS_ISR_I2C3     	(0x00000001 <<23)
#define MARS_MIS_ISR_I2C4     	(0x00000001 <<15)
#define MARS_MIS_ISR_I2C5     	(0x00000001 <<14)



#define MARS_ISO_ISR			VENUS_ISO_ISR
#define MARS_ISO_ISR_I2C0     	(0x00000001 <<8)
#define MARS_ISO_ISR_I2C6     	(0x00000001 <<10)















#define MARS_0_SYS_MUXPAD0		0xB8000350

  #define I2C0_LOC_MASK              (0x00000003 << 18)
  #define I2C0_LOC_QFPA_BGA          (0x00000000)
  #define I2C0_LOC_QFPB              (0x00000001 << 18)    
  #define I2C1_LOC_MASK              (0x00000003 << 20)
  #define I2C1_LOC_MUX_PCI           (0x00000000)
  #define I2C1_LOC_MUX_UR0           (0x00000001 << 18)  
  
#define MARS_0_SYS_MUXPAD1		0xB8000354
#define MARS_0_SYS_MUXPAD2		0xB8000358
#define MARS_0_SYS_MUXPAD3		0xB800035C
  
  #define I2C0_MASK                  (0x00000003 << 4)
  #define I2C0_SDA_SCL               (0x00000000)
  #define I2C0_GP4_GP5               (0x00000001 << 4)    
  #define I2C1_MASK                  (0x00000003)
  #define I2C1_SDA_SCL               (0x00000002)
  #define I2C1_GP0_GP1               (0x00000001)  
  #define I2C1_UART1                 (0x00000000)  
  
#define MARS_0_SYS_MUXPAD4		0xB8000360
#define MARS_0_SYS_MUXPAD5		0xB8000364

  #define PCI_MUX1_MASK              (0x00000003<<2)
  #define PCI_MUX1_PCI               (0x00000000<<2)
  #define PCI_MUX1_GPIO              (0x00000001<<2)
  #define PCI_MUX1_I2C1              (0x00000002<<2)
  
#define MARS_0_SYS_MUXPAD6		0xB8000368
#define MARS_0_SYS_MUXPAD7		0xB800036C

  

/*
 * Mars GPIO registers.
 */
#define MARS_MIS_GP0DIR			0x1B100
#define MARS_MIS_GP1DIR			0x1B104
#define MARS_MIS_GP2DIR			0x1B108
#define MARS_MIS_GP3DIR			0x1B10C
#define MARS_MIS_GP0DATO		0x1B110
#define MARS_MIS_GP1DATO		0x1B114
#define MARS_MIS_GP2DATO		0x1B118
#define MARS_MIS_GP3DATO		0x1B11C
#define MARS_MIS_GP0DATI		0x1B120
#define MARS_MIS_GP1DATI		0x1B124
#define MARS_MIS_GP2DATI		0x1B128
#define MARS_MIS_GP3DATI		0x1B12C
#define MARS_MIS_GP0IE			0x1B130
#define MARS_MIS_GP1IE			0x1B134
#define MARS_MIS_GP2IE			0x1B138
#define MARS_MIS_GP3IE			0x1B13C
#define MARS_MIS_GP0DP			0x1B140
#define MARS_MIS_GP1DP			0x1B144
#define MARS_MIS_GP2DP			0x1B148
#define MARS_MIS_GP3DP			0x1B14C
#define MARS_MIS_GPDEB			0x1B150

/*-------------------------------------------------------------
 * Mars MISC UART register
 *-------------------------------------------------------------*/
#define MARS_MIS_U0RBR_THR_DLL		0x1B200

/*-------------------------------------------------------------
 * Mars MISC CEC register
 *-------------------------------------------------------------*/                                                              
#define MARS_MIS_CEC_CR0        0x1B900                       
#define MARS_MIS_CEC_CR1        0x1B904                       
#define MARS_MIS_CEC_CR2        0x1B908                       
#define MARS_MIS_CEC_CR3        0x1B90C                       
#define MARS_MIS_CEC_RT0        0x1B910                       
#define MARS_MIS_CEC_RT1        0x1B914                       
#define MARS_MIS_CEC_RX0        0x1B918                       
#define MARS_MIS_CEC_RX1        0x1B91C                       
#define MARS_MIS_CEC_TX0        0x1B920                       
#define MARS_MIS_CEC_TX1        0x1B924                       
#define MARS_MIS_CEC_TX_FIFO    0x1B928                       
#define MARS_MIS_CEC_RX_FIFO    0x1B92C                       
#define MARS_MIS_CEC_RX_START0  0x1B930                       
#define MARS_MIS_CEC_RX_START1  0x1B934                       
#define MARS_MIS_CEC_RX_DATA0   0x1B938                       
#define MARS_MIS_CEC_RX_DATA1   0x1B93C                       
#define MARS_MIS_CEC_TX_START0  0x1B940                       
#define MARS_MIS_CEC_TX_START1  0x1B944                       
#define MARS_MIS_CEC_TX_DATA0   0x1B948                       
#define MARS_MIS_CEC_TX_DATA1   0x1B94C                       
#define MARS_MIS_CEC_TX_DATA2   0x1B950                       
 
 
/*-------------------------------------------------------------
 * Mars MISC I2C register
 *-------------------------------------------------------------*/  
 
// I2C
#define MARS_ISO_IC0_CON                 0x7d00
#define MARS_ISO_IC0_TAR                 0x7d04
#define MARS_ISO_IC0_SAR                 0x7d08
#define MARS_ISO_IC0_HS_MADDR            0x7d0c
#define MARS_ISO_IC0_DATA_CMD            0x7d10
#define MARS_ISO_IC0_SS_SCL_HCNT         0x7d14
#define MARS_ISO_IC0_SS_SCL_LCNT         0x7d18
#define MARS_ISO_IC0_FS_SCL_HCNT         0x7d1c
#define MARS_ISO_IC0_FS_SCL_LCNT         0x7d20
#define MARS_ISO_IC0_INTR_STAT           0x7d2c
#define MARS_ISO_IC0_INTR_MASK           0x7d30
#define MARS_ISO_IC0_RAW_INTR_STAT       0x7d34
#define MARS_ISO_IC0_RX_TL               0x7d38
#define MARS_ISO_IC0_TX_TL               0x7d3c
#define MARS_ISO_IC0_CLR_INTR            0x7d40
#define MARS_ISO_IC0_CLR_RX_UNDER        0x7d44
#define MARS_ISO_IC0_CLR_RX_OVER         0x7d48
#define MARS_ISO_IC0_CLR_TX_OVER         0x7d4c
#define MARS_ISO_IC0_CLR_RD_REQ          0x7d50
#define MARS_ISO_IC0_CLR_TX_ABRT         0x7d54
#define MARS_ISO_IC0_CLR_RX_DONE         0x7d58
#define MARS_ISO_IC0_CLR_ACTIVITY        0x7d5c
#define MARS_ISO_IC0_CLR_STOP_DET        0x7d60
#define MARS_ISO_IC0_CLR_START_DET       0x7d64
#define MARS_ISO_IC0_CLR_GEN_CALL        0x7d68
#define MARS_ISO_IC0_ENABLE              0x7d6c
#define MARS_ISO_IC0_STATUS              0x7d70
#define MARS_ISO_IC0_TXFLR               0x7d74
#define MARS_ISO_IC0_RXFLR               0x7d78
#define MARS_ISO_IC0_SDA_HOLD               0x7d7c
#define MARS_ISO_IC0_TX_ABRT_SOURCE      0x7d80
#define MARS_ISO_IC0_SLV_DATA_NACK_ONLY     0x7d84
#define MARS_ISO_IC0_DMA_CR              0x7d88
#define MARS_ISO_IC0_DMA_TDLR            0x7d8c
#define MARS_ISO_IC0_DMA_RDLR            0x7d90
#define MARS_ISO_IC0_SDA_SETUP            0x7d94
#define MARS_ISO_IC0_ACK_GENERAL_CALL            0x7d98
#define MARS_ISO_IC0_ENABLE_STATUS            0x7d9c
#define MARS_ISO_IC0_COMP_PARAM_1        0x7df4
#define MARS_ISO_IC0_COMP_VERSION        0x7df8
#define MARS_ISO_IC0_COMP_TYPE           0x7dfc


#define MARS_MIS_IC1_CON                 0x1b300
#define MARS_MIS_IC1_TAR                 0x1b304
#define MARS_MIS_IC1_SAR                 0x1b308
#define MARS_MIS_IC1_HS_MADDR            0x1b30c
#define MARS_MIS_IC1_DATA_CMD            0x1b310
#define MARS_MIS_IC1_SS_SCL_HCNT         0x1b314
#define MARS_MIS_IC1_SS_SCL_LCNT         0x1b318
#define MARS_MIS_IC1_FS_SCL_HCNT         0x1b31c
#define MARS_MIS_IC1_FS_SCL_LCNT         0x1b320
#define MARS_MIS_IC1_INTR_STAT           0x1b32c
#define MARS_MIS_IC1_INTR_MASK           0x1b330
#define MARS_MIS_IC1_RAW_INTR_STAT       0x1b334
#define MARS_MIS_IC1_RX_TL               0x1b338
#define MARS_MIS_IC1_TX_TL               0x1b33c
#define MARS_MIS_IC1_CLR_INTR            0x1b340
#define MARS_MIS_IC1_CLR_RX_UNDER        0x1b344
#define MARS_MIS_IC1_CLR_RX_OVER         0x1b348
#define MARS_MIS_IC1_CLR_TX_OVER         0x1b34c
#define MARS_MIS_IC1_CLR_RD_REQ          0x1b350
#define MARS_MIS_IC1_CLR_TX_ABRT         0x1b354
#define MARS_MIS_IC1_CLR_RX_DONE         0x1b358
#define MARS_MIS_IC1_CLR_ACTIVITY        0x1b35c
#define MARS_MIS_IC1_CLR_STOP_DET        0x1b360
#define MARS_MIS_IC1_CLR_START_DET       0x1b364
#define MARS_MIS_IC1_CLR_GEN_CALL        0x1b368
#define MARS_MIS_IC1_ENABLE              0x1b36c
#define MARS_MIS_IC1_STATUS              0x1b370
#define MARS_MIS_IC1_TXFLR               0x1b374
#define MARS_MIS_IC1_RXFLR               0x1b378
#define MARS_MIS_IC1_SDA_HOLD               0x1b37c
#define MARS_MIS_IC1_TX_ABRT_SOURCE      0x1b380
#define MARS_MIS_IC1_SLV_DATA_NACK_ONLY     0x1b384
#define MARS_MIS_IC1_DMA_CR              0x1b388
#define MARS_MIS_IC1_DMA_TDLR            0x1b38c
#define MARS_MIS_IC1_DMA_RDLR            0x1b390
#define MARS_MIS_IC1_SDA_SETUP            0x1b394
#define MARS_MIS_IC1_ACK_GENERAL_CALL            0x1b398
#define MARS_MIS_IC1_ENABLE_STATUS            0x1b39c
#define MARS_MIS_IC1_COMP_PARAM_1        0x1b3f4
#define MARS_MIS_IC1_COMP_VERSION        0x1b3f8
#define MARS_MIS_IC1_COMP_TYPE           0x1b3fc

#define MARS_MIS_IC2_CON                 0x1b700
#define MARS_MIS_IC2_TAR                 0x1b704
#define MARS_MIS_IC2_SAR                 0x1b708
#define MARS_MIS_IC2_HS_MADDR            0x1b70c
#define MARS_MIS_IC2_DATA_CMD            0x1b710
#define MARS_MIS_IC2_SS_SCL_HCNT         0x1b714
#define MARS_MIS_IC2_SS_SCL_LCNT         0x1b718
#define MARS_MIS_IC2_FS_SCL_HCNT         0x1b71c
#define MARS_MIS_IC2_FS_SCL_LCNT         0x1b720
#define MARS_MIS_IC2_INTR_STAT           0x1b72c
#define MARS_MIS_IC2_INTR_MASK           0x1b730
#define MARS_MIS_IC2_RAW_INTR_STAT       0x1b734
#define MARS_MIS_IC2_RX_TL               0x1b738
#define MARS_MIS_IC2_TX_TL               0x1b73c
#define MARS_MIS_IC2_CLR_INTR            0x1b740
#define MARS_MIS_IC2_CLR_RX_UNDER        0x1b744
#define MARS_MIS_IC2_CLR_RX_OVER         0x1b748
#define MARS_MIS_IC2_CLR_TX_OVER         0x1b74c
#define MARS_MIS_IC2_CLR_RD_REQ          0x1b750
#define MARS_MIS_IC2_CLR_TX_ABRT         0x1b754
#define MARS_MIS_IC2_CLR_RX_DONE         0x1b758
#define MARS_MIS_IC2_CLR_ACTIVITY        0x1b75c
#define MARS_MIS_IC2_CLR_STOP_DET        0x1b760
#define MARS_MIS_IC2_CLR_START_DET       0x1b764
#define MARS_MIS_IC2_CLR_GEN_CALL        0x1b768
#define MARS_MIS_IC2_ENABLE              0x1b76c
#define MARS_MIS_IC2_STATUS              0x1b770
#define MARS_MIS_IC2_TXFLR               0x1b774
#define MARS_MIS_IC2_RXFLR               0x1b778
#define MARS_MIS_IC2_SDA_HOLD               0x1b77c
#define MARS_MIS_IC2_TX_ABRT_SOURCE      0x1b780
#define MARS_MIS_IC2_SLV_DATA_NACK_ONLY     0x1b784
#define MARS_MIS_IC2_DMA_CR              0x1b788
#define MARS_MIS_IC2_DMA_TDLR            0x1b78c
#define MARS_MIS_IC2_DMA_RDLR            0x1b790
#define MARS_MIS_IC2_SDA_SETUP            0x1b794
#define MARS_MIS_IC2_ACK_GENERAL_CALL            0x1b798
#define MARS_MIS_IC2_ENABLE_STATUS            0x1b79c
#define MARS_MIS_IC2_COMP_PARAM_1        0x1b7f4
#define MARS_MIS_IC2_COMP_VERSION        0x1b7f8
#define MARS_MIS_IC2_COMP_TYPE           0x1b7fc

#define MARS_MIS_IC3_CON                 0x1b900
#define MARS_MIS_IC3_TAR                 0x1b904
#define MARS_MIS_IC3_SAR                 0x1b908
#define MARS_MIS_IC3_HS_MADDR            0x1b90c
#define MARS_MIS_IC3_DATA_CMD            0x1b910
#define MARS_MIS_IC3_SS_SCL_HCNT         0x1b914
#define MARS_MIS_IC3_SS_SCL_LCNT         0x1b918
#define MARS_MIS_IC3_FS_SCL_HCNT         0x1b91c
#define MARS_MIS_IC3_FS_SCL_LCNT         0x1b920
#define MARS_MIS_IC3_INTR_STAT           0x1b92c
#define MARS_MIS_IC3_INTR_MASK           0x1b930
#define MARS_MIS_IC3_RAW_INTR_STAT       0x1b934
#define MARS_MIS_IC3_RX_TL               0x1b938
#define MARS_MIS_IC3_TX_TL               0x1b93c
#define MARS_MIS_IC3_CLR_INTR            0x1b940
#define MARS_MIS_IC3_CLR_RX_UNDER        0x1b944
#define MARS_MIS_IC3_CLR_RX_OVER         0x1b948
#define MARS_MIS_IC3_CLR_TX_OVER         0x1b94c
#define MARS_MIS_IC3_CLR_RD_REQ          0x1b950
#define MARS_MIS_IC3_CLR_TX_ABRT         0x1b954
#define MARS_MIS_IC3_CLR_RX_DONE         0x1b958
#define MARS_MIS_IC3_CLR_ACTIVITY        0x1b95c
#define MARS_MIS_IC3_CLR_STOP_DET        0x1b960
#define MARS_MIS_IC3_CLR_START_DET       0x1b964
#define MARS_MIS_IC3_CLR_GEN_CALL        0x1b968
#define MARS_MIS_IC3_ENABLE              0x1b96c
#define MARS_MIS_IC3_STATUS              0x1b970
#define MARS_MIS_IC3_TXFLR               0x1b974
#define MARS_MIS_IC3_RXFLR               0x1b978
#define MARS_MIS_IC3_SDA_HOLD               0x1b97c
#define MARS_MIS_IC3_TX_ABRT_SOURCE      0x1b980
#define MARS_MIS_IC3_SLV_DATA_NACK_ONLY     0x1b984
#define MARS_MIS_IC3_DMA_CR              0x1b988
#define MARS_MIS_IC3_DMA_TDLR            0x1b98c
#define MARS_MIS_IC3_DMA_RDLR            0x1b990
#define MARS_MIS_IC3_SDA_SETUP            0x1b994
#define MARS_MIS_IC3_ACK_GENERAL_CALL            0x1b998
#define MARS_MIS_IC3_ENABLE_STATUS            0x1b99c
#define MARS_MIS_IC3_COMP_PARAM_1        0x1b9f4
#define MARS_MIS_IC3_COMP_VERSION        0x1b9f8
#define MARS_MIS_IC3_COMP_TYPE           0x1b9fc

#define MARS_MIS_IC4_CON                 0x1ba00
#define MARS_MIS_IC4_TAR                 0x1ba04
#define MARS_MIS_IC4_SAR                 0x1ba08
#define MARS_MIS_IC4_HS_MADDR            0x1ba0c
#define MARS_MIS_IC4_DATA_CMD            0x1ba10
#define MARS_MIS_IC4_SS_SCL_HCNT         0x1ba14
#define MARS_MIS_IC4_SS_SCL_LCNT         0x1ba18
#define MARS_MIS_IC4_FS_SCL_HCNT         0x1ba1c
#define MARS_MIS_IC4_FS_SCL_LCNT         0x1ba20
#define MARS_MIS_IC4_INTR_STAT           0x1ba2c
#define MARS_MIS_IC4_INTR_MASK           0x1ba30
#define MARS_MIS_IC4_RAW_INTR_STAT       0x1ba34
#define MARS_MIS_IC4_RX_TL               0x1ba38
#define MARS_MIS_IC4_TX_TL               0x1ba3c
#define MARS_MIS_IC4_CLR_INTR            0x1ba40
#define MARS_MIS_IC4_CLR_RX_UNDER        0x1ba44
#define MARS_MIS_IC4_CLR_RX_OVER         0x1ba48
#define MARS_MIS_IC4_CLR_TX_OVER         0x1ba4c
#define MARS_MIS_IC4_CLR_RD_REQ          0x1ba50
#define MARS_MIS_IC4_CLR_TX_ABRT         0x1ba54
#define MARS_MIS_IC4_CLR_RX_DONE         0x1ba58
#define MARS_MIS_IC4_CLR_ACTIVITY        0x1ba5c
#define MARS_MIS_IC4_CLR_STOP_DET        0x1ba60
#define MARS_MIS_IC4_CLR_START_DET       0x1ba64
#define MARS_MIS_IC4_CLR_GEN_CALL        0x1ba68
#define MARS_MIS_IC4_ENABLE              0x1ba6c
#define MARS_MIS_IC4_STATUS              0x1ba70
#define MARS_MIS_IC4_TXFLR               0x1ba74
#define MARS_MIS_IC4_RXFLR               0x1ba78
#define MARS_MIS_IC4_SDA_HOLD               0x1ba7c
#define MARS_MIS_IC4_TX_ABRT_SOURCE      0x1ba80
#define MARS_MIS_IC4_SLV_DATA_NACK_ONLY     0x1ba84
#define MARS_MIS_IC4_DMA_CR              0x1ba88
#define MARS_MIS_IC4_DMA_TDLR            0x1ba8c
#define MARS_MIS_IC4_DMA_RDLR            0x1ba90
#define MARS_MIS_IC4_SDA_SETUP            0x1ba94
#define MARS_MIS_IC4_ACK_GENERAL_CALL            0x1ba98
#define MARS_MIS_IC4_ENABLE_STATUS            0x1ba9c
#define MARS_MIS_IC4_COMP_PARAM_1        0x1baf4
#define MARS_MIS_IC4_COMP_VERSION        0x1baf8
#define MARS_MIS_IC4_COMP_TYPE           0x1bafc

#define MARS_MIS_IC5_CON                0x1bb00
#define MARS_MIS_IC5_TAR                0x1bb04
#define MARS_MIS_IC5_SAR                0x1bb08
#define MARS_MIS_IC5_HS_MADDR           0x1bb0c
#define MARS_MIS_IC5_DATA_CMD           0x1bb10
#define MARS_MIS_IC5_SS_SCL_HCNT        0x1bb14
#define MARS_MIS_IC5_SS_SCL_LCNT        0x1bb18
#define MARS_MIS_IC5_FS_SCL_HCNT        0x1bb1c
#define MARS_MIS_IC5_FS_SCL_LCNT        0x1bb20
#define MARS_MIS_IC5_INTR_STAT          0x1bb2c
#define MARS_MIS_IC5_INTR_MASK          0x1bb30
#define MARS_MIS_IC5_RAW_INTR_STAT      0x1bb34
#define MARS_MIS_IC5_RX_TL              0x1bb38
#define MARS_MIS_IC5_TX_TL              0x1bb3c
#define MARS_MIS_IC5_CLR_INTR           0x1bb40
#define MARS_MIS_IC5_CLR_RX_UNDER       0x1bb44
#define MARS_MIS_IC5_CLR_RX_OVER        0x1bb48
#define MARS_MIS_IC5_CLR_TX_OVER        0x1bb4c
#define MARS_MIS_IC5_CLR_RD_REQ         0x1bb50
#define MARS_MIS_IC5_CLR_TX_ABRT        0x1bb54
#define MARS_MIS_IC5_CLR_RX_DONE        0x1bb58
#define MARS_MIS_IC5_CLR_ACTIVITY       0x1bb5c
#define MARS_MIS_IC5_CLR_STOP_DET       0x1bb60
#define MARS_MIS_IC5_CLR_START_DET      0x1bb64
#define MARS_MIS_IC5_CLR_GEN_CALL       0x1bb68
#define MARS_MIS_IC5_ENABLE             0x1bb6c
#define MARS_MIS_IC5_STATUS             0x1bb70
#define MARS_MIS_IC5_TXFLR              0x1bb74
#define MARS_MIS_IC5_RXFLR              0x1bb78
#define MARS_MIS_IC5_SDA_HOLD               0x1bb7c
#define MARS_MIS_IC5_TX_ABRT_SOURCE     0x1bb80
#define MARS_MIS_IC5_SLV_DATA_NACK_ONLY     0x1bb84
#define MARS_MIS_IC5_DMA_CR             0x1bb88
#define MARS_MIS_IC5_DMA_TDLR           0x1bb8c
#define MARS_MIS_IC5_DMA_RDLR           0x1bb90
#define MARS_MIS_IC5_SDA_SETUP            0x1bb94
#define MARS_MIS_IC5_ACK_GENERAL_CALL            0x1bb98
#define MARS_MIS_IC5_ENABLE_STATUS            0x1bb9c
#define MARS_MIS_IC5_COMP_PARAM_1       0x1bbf4
#define MARS_MIS_IC5_COMP_VERSION       0x1bbf8
#define MARS_MIS_IC5_COMP_TYPE          0x1bbfc
 
#define MARS_ISO_IC6_CON                			0x7e00
#define MARS_ISO_IC6_TAR                			0x7e04
#define MARS_ISO_IC6_SAR               			0x7e08
#define MARS_ISO_IC6_HS_MADDR           		0x7e0c
#define MARS_ISO_IC6_DATA_CMD           		0x7e10
#define MARS_ISO_IC6_SS_SCL_HCNT        		0x7e14
#define MARS_ISO_IC6_SS_SCL_LCNT        		0x7e18
#define MARS_ISO_IC6_FS_SCL_HCNT        		0x7e1c
#define MARS_ISO_IC6_FS_SCL_LCNT        		0x7e20
#define MARS_ISO_IC6_INTR_STAT          		0x7e2c
#define MARS_ISO_IC6_INTR_MASK          		0x7e30
#define MARS_ISO_IC6_RAW_INTR_STAT   		0x7e34
#define MARS_ISO_IC6_RX_TL              			0x7e38
#define MARS_ISO_IC6_TX_TL              			0x7e3c
#define MARS_ISO_IC6_CLR_INTR           		0x7e40
#define MARS_ISO_IC6_CLR_RX_UNDER       		0x7e44
#define MARS_ISO_IC6_CLR_RX_OVER        		0x7e48
#define MARS_ISO_IC6_CLR_TX_OVER        		0x7e4c
#define MARS_ISO_IC6_CLR_RD_REQ         		0x7e50
#define MARS_ISO_IC6_CLR_TX_ABRT        		0x7e54
#define MARS_ISO_IC6_CLR_RX_DONE        		0x7e58
#define MARS_ISO_IC6_CLR_ACTIVITY       		0x7e5c
#define MARS_ISO_IC6_CLR_STOP_DET       		0x7e60
#define MARS_ISO_IC6_CLR_START_DET   		0x7e64
#define MARS_ISO_IC6_CLR_GEN_CALL       		0x7e68
#define MARS_ISO_IC6_ENABLE             		0x7e6c
#define MARS_ISO_IC6_STATUS             		0x7e70
#define MARS_ISO_IC6_TXFLR              			0x7e74
#define MARS_ISO_IC6_RXFLR             	 		0x7e78
#define MARS_ISO_IC6_SDA_HOLD           		0x7e7c
#define MARS_ISO_IC6_TX_ABRT_SOURCE  		0x7e80
#define MARS_ISO_IC6_SLV_DATA_NACK_ONLY	0x7e84
#define MARS_ISO_IC6_DMA_CR             		0x7e88
#define MARS_ISO_IC6_DMA_TDLR           		0x7e8c
#define MARS_ISO_IC6_DMA_RDLR           		0x7e90
#define MARS_ISO_IC6_SDA_SETUP            		0x7e94
#define MARS_ISO_IC6_ACK_GENERAL_CALL    	0x7e98
#define MARS_ISO_IC6_ENABLE_STATUS   		0x7e9c
#define MARS_ISO_IC6_COMP_PARAM_1      	0x7ef4
#define MARS_ISO_IC6_COMP_VERSION       	0x7ef8
#define MARS_ISO_IC6_COMP_TYPE          		0x7efc
 
 
 
//IC_CON
#define IC_SLAVE_DISABLE    0x0040
#define IC_RESTART_EN       0x0020                  
#define IC_10BITADDR_MASTER 0x0010                  
#define IC_10BITADDR_SLAVE  0x0008                  
#define IC_MASTER_MODE      0x0001                  
                  
#define IC_SPEED            0x0006
#define SPEED_SS            0x0002
#define SPEED_FS            0x0004
#define SPEED_HS            0x0006

//ID_DATA
#define READ_CMD            0x0100

// INT
#define GEN_CALL_BIT        0x800
#define START_DET_BIT       0x400
#define STOP_DET_BIT        0x200
#define ACTIVITY_BIT        0x100
#define RX_DONE_BIT         0x080
#define TX_ABRT_BIT         0x040
#define RD_REQ_BIT          0x020
#define TX_EMPTY_BIT        0x010
#define TX_OVER_BIT         0x008
#define RX_FULL_BIT         0x004
#define RX_OVER_BIT         0x002
#define RX_UNDER_BIT        0x001

// STATUS
#define ST_RFF_BIT          0x10
#define ST_RFNE_BIT         0x08
#define ST_TFE_BIT          0x04
#define ST_TFNF_BIT         0x02
#define ST_ACTIVITY_BIT     0x01     


// IC_TX_ABRT_SOURCE
#define ABRT_SLVRD_INTX             0x8000
#define ABRT_SLV_ARB_LOST           0x4000
#define ABRT_SLV_FLUSH_TX_FIFO      0x2000
#define ABRT_ARB_LOST               0x1000
#define ABR_MASTER_DIS              0x0800   
#define ABRT_10B_RD_NORSTRT         0x0400
#define ABRT_SBYTE_NORSTRT          0x0200
#define ABRT_HS_NORSTRT             0x0100
#define ABRT_SBYTE_ACKDET           0x0080
#define ABRT_HS_ACKDET              0x0040
#define ABRT_GCALL_READ             0x0020
#define ABRT_GCALL_NOACK            0x0010
#define ABRT_TXDATA_NOACK           0x0008
#define ABRT_10ADDR2_NOACK          0x0004
#define ABRT_10ADDR1_NOACK          0x0002
#define ABRT_7ADDR_NOACK            0x0001
 
/*-------------------------------------------------------------
 * Mars MISC PCMCIA register
 *-------------------------------------------------------------*/
#define MARS_PCMCIA_CMDFF		0x1B800
#define MARS_PCMCIA_CTRL		0x1B804
#define MARS_PCMCIA_STS			0x1B808
#define MARS_PCMCIA_AMTC		0x1B80C
#define MARS_PCMCIA_IOMTC		0x1B810
#define MARS_PCMCIA_MATC		0x1B814
#define MARS_PCMCIA_ACTRL		0x1B818


//-- MARS_PCMCIA_CMDFF
#define PC_CT(x)			(((x) & 0x01)<< 24)
#define PC_CT_READ			PC_CT(0)
#define PC_CT_WRITE			PC_CT(1)
#define PC_AT(x)			(((x) & 0x01)<< 23)
#define PC_AT_IO			PC_AT(0)
#define PC_AT_ATTRMEM			PC_AT(1)
#define PC_PA(x)			(((x) & 0x7FFF) << 8)
#define PC_DF(x)			(((x) & 0xFF))

//-- MARS_PCMCIA_CTRL
#define PC_PSR				(0x00000001 << 31)
#define PC_CE1_CARD1			(0x00000001 << 30)
#define PC_CE1_CARD2			(0x00000001 << 29)
#define PC_CE2_CARD1			(0x00000001 << 28)
#define PC_CE2_CARD2			(0x00000001 << 27)
#define PC_PCR1				(0x00000001 << 26)
#define PC_PCR2				(0x00000001 << 25)
#define PC_PCR1_OE			(0x00000001 << 24)
#define PC_PCR2_OE			(0x00000001 << 23)
#define PC_PIIE1			(0x00000001 << 7)
#define PC_PCIIE1			(0x00000001 << 6)
#define PC_PCRIE1			(0x00000001 << 5)
#define PC_PIIE2			(0x00000001 << 4)
#define PC_PCIIE2			(0x00000001 << 3)
#define PC_PCRIE2			(0x00000001 << 2)
#define PC_AFIE				(0x00000001 << 1)
#define PC_APFIE			(0x00000001)

//-- MARS_PCMCIA_STS
#define PC_PRES1			(0x00000001 << 9)
#define PC_PRES2			(0x00000001 << 8)
#define PC_PII1				(0x00000001 << 7)
#define PC_PCII1			(0x00000001 << 6)
#define PC_PCRI1			(0x00000001 << 5)
#define PC_PII2				(0x00000001 << 4)
#define PC_PCII2			(0x00000001 << 3)
#define PC_PCRI2			(0x00000001 << 2)
#define PC_AFI				(0x00000001 << 1)
#define PC_APFI				(0x00000001)

//-- MARS_PCMCIA_AMTC
#define PC_TWE(x)			(((x) & 0x3F) << 26)
#define PC_THD(x)			(((x) & 0x0F) << 22)
#define PC_TAOE(x)			(((x) & 0x1F) << 17)
#define PC_THCE(x)			(((x) & 0x1F) << 8)
#define PC_TSU(x)			(((x) & 0x1F))

//-- MARS_PCMCIA_IOMTC
#define PC_TDIORD(x)			(((x) & 0x1F) << 16)
#define PC_TSUIO(x)			(((x) & 0x0F) << 8)
#define PC_TDINPACK(x)			(((x) & 0x0F) << 4)
#define PC_TDWT(x)			(((x) & 0x0F))

//-- MARS_PCMCIA_MATC
#define PC_TC(x)			(((x) & 0xFF) << 24)
#define PC_THDIO(x)			(((x) & 0x0F) << 20)
#define PC_TCIO(x)			(((x) & 0xFF) << 8)
#define PC_TWIOWR(x)			(((x) & 0x3F))

//-- MARS_PCMCIA_MATC
#define PC_OE(x)			(((x) & 0x7FFF))


// USB Host Registers
//#define VENUS_USB_HOST_BASE			(VENUS_USB_BASE+0x800)
#define MARS_USB_HOST_VERSION			(VENUS_USB_HOST_BASE+0x14)
#define MARS_USB_HOST_WRAPP_2PORT		(VENUS_USB_HOST_BASE+0x20)
#define MARS_USB_HOST_VSTATUS_2PORT		(VENUS_USB_HOST_BASE+0x24)
#define MARS_USB_HOST_USBIPINPUT_2PORT		(VENUS_USB_HOST_BASE+0x28)
#define MARS_USB_HOST_RESET_UTMI_2PORT		(VENUS_USB_HOST_BASE+0x2C)
#define MARS_USB_HOST_SELF_LOOP_BACK_2PORT	(VENUS_USB_HOST_BASE+0x30)
#define MARS_USB_HOST_IPNEWINPUT_2PORT		(VENUS_USB_HOST_BASE+0x34)
#define MARS_USB_HOST_USBPHY_SLB0		(VENUS_USB_HOST_BASE+0x38)
#define MARS_USB_HOST_USBPHY_SLB1		(VENUS_USB_HOST_BASE+0x3C)
#define MARS_USB_HOST_OTG			(VENUS_USB_HOST_BASE+0x40)
#define MARS_USB_HOST_OTGMUX			(VENUS_USB_HOST_BASE+0x44)

#endif /* !(_MACH_MARS_H) */

