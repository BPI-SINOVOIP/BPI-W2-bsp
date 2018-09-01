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

#ifndef _MACH_SATURN_H
#define _MACH_SATURN_H

//#include <asm/addrspace.h>
//#include <jupiter.h>

#define SATURN_IO_PORT_BASE                     JUPITER_IO_PORT_BASE     

/*-------------------------------------------------------------
 * Saturn DC SYS register
 *-------------------------------------------------------------*/  
#define SATURN_DC_EC_CTRL               0x8300
#define SATURN_DC_EC_ADDCMD_HI          0x8304
#define SATURN_DC_EC_ADDCMD_LO          0x8308

#define SATURN_DC_MT_ENTRY_COUNT           8
#define SATURN_DC_MT_SADDR                 0x08200
#define SATURN_DC_MT_EADDR                 0x08220
#define SATURN_DC_MT_MODE                  0x08240
#define SATURN_DC_MT_TABLE                 0x08260
#define SATURN_DC_MT_ADDCMD_HI             0x08280
#define SATURN_DC_MT_ADDCMD_LO             0x082A0


/*-------------------------------------------------------------
 * Saturn MISC I2C register
 *-------------------------------------------------------------*/  
#define SATURN_MIS_I2C1_SDA_DEL                 0x1b088
#define SATURN_MIS_I2C2_SDA_DEL                 0x1b08C
#define SATURN_MIS_I2C3_SDA_DEL                 0x1b090
#define SATURN_MIS_I2C4_SDA_DEL                 0x1b094
#define SATURN_MIS_I2C5_SDA_DEL                 0x1b098

  #define I2C_SDA_DEL_MASK                        (0x1FF)
  #define I2C_SDA_DEL_EN(x)                       (0x00000001<<8)
  #define I2C_SDA_DEL_SEL(x)                      ((x & 0x1F))          // Delay time: (unit 518ns)
        
#define SATURN_MIS_PWM_OCD                      0x1b400
#define SATURN_MIS_PWM_CD                       0x1b404
#define SATURN_MIS_PWM_CSD                      0x1b408

  #define PWM_OUTPUT_DIV(i, val)      ((val & 0xFF) << (i<<3))
  #define PWM_OUTPUT_DIV_MASK(i)      ((0xFF) << (i<<3))
  #define PWM_CLK_DUTY(i, val)        ((val & 0xFF) << (i<<3))
  #define PWM_CLK_DUTY_MASK(i)        ((0xFF) << (i<<3))
  #define PWM_SCLK_DIV(i, val)        ((val & 0xF) << (i<<2))
  #define PWM_SCLK_DIV_MASK(i)        ((0xF) << (i<<2))


/*-------------------------------------------------------------
 * Saturn ISO system register
 *-------------------------------------------------------------*/
#define Saturn_ISO_ISR             0x7000
#define SATURN_ISO_ISR             Saturn_ISO_ISR
#define SATURN_ISO_ISR_CEC_TX     (0x00000001<<22)
#define SATURN_ISO_ISR_CEC_RX     (0x00000001<<23)


#define SATURN_ISO_I2C0_SDA_DEL                 0x7084
#define SATURN_ISO_I2C6_SDA_DEL                 0x70c0


#define SATURN_ISO_UMSK_ISR                     0x7004
#define SATURN_ISO_UMSK_ISR_GP                  0x7008
#define SATURN_ISO_UMSK_ISR_KPADAH              0x700C
#define SATURN_ISO_UMSK_ISR_KPADAL              0x7010
#define SATURN_ISO_UMSK_ISR_KPADDAH             0x7014
#define SATURN_ISO_UMSK_ISR_KPADDAL             0x7018
#define SATURN_ISO_UMSK_ISR_SW                  0x701C
#define SATURN_ISO_DBG                          0x7020
#define SATURN_ISO_DUMMY1                       0x7024
#define SATURN_ISO_CHIP_INFO1                   0x7028
#define SATURN_ISO_CHIP_INFO2                   0x702C
#define SATURN_ISO_CHIP_CTRL                    0x7030
#define SATURN_ISO_RTC                          0x7034
#define SATURN_ISO_CELL                         0x7038
#define SATURN_ISO_POWER                        0x703C
#define SATURN_ISO_SCPU_INT_EN                  0x7040
#define SATURN_ISO_KCPU_INT_EN                  0x7044
#define SATURN_ISO_CPU_ST1                      0x7048
#define SATURN_ISO_CPU_ST1V                     0x704C
#define SATURN_ISO_DUMMY2                       0x7050

/*-------------------------------------------------------------
 * SATURN ISO GPIO register
 *-------------------------------------------------------------*/
#define SATURN_ISO_GPDIR                        0x7100
#define SATURN_ISO_GPDATO                       0x7104
#define SATURN_ISO_GPDATI                       0x7108
#define SATURN_ISO_GPIE                         0x710C
#define SATURN_ISO_GPDP                         0x7110
#define SATURN_ISO_GPDEB                        0x7114

/*-------------------------------------------------------------
 * SATURN ISO IrDA register
 *-------------------------------------------------------------*/
#define SATURN_ISO_IR_PSR                       0x7400
#define SATURN_ISO_IR_PRE                       0x7404
#define SATURN_ISO_IR_SF                        0x7408
#define SATURN_ISO_IR_DPIR                      0x740C
#define SATURN_ISO_IR_CR                        0x7410
#define SATURN_ISO_IR_RP                        0x7414
#define SATURN_ISO_IR_SR                        0x7418
#define SATURN_ISO_IR_RAW_CTRL                  0x741C
#define SATURN_ISO_IR_RAW_FF                    0x7420
#define SATURN_ISO_IR_RAW_SAMPLE_TIME           0x7424
#define SATURN_ISO_IR_WL                        0x7428
#define SATURN_ISO_IR_RAW_DEB                   0x742C
#define SATURN_ISO_IR_PSR_UP                    0x7430
#define SATURN_ISO_IR_PER_UP                    0x7434
#define SATURN_ISO_IR_CTRL_RC6                  0x7438

/*-------------------------------------------------------------
 * SATURN ISO CEC register
 *-------------------------------------------------------------*/                                                                                                                             
#define SATURN_ISO_CEC_CR0         0x7500
#define SATURN_ISO_CEC_CR1         0x7504
#define SATURN_ISO_CEC_CR2         0x7508
#define SATURN_ISO_CEC_CR3         0x750C        
#define SATURN_ISO_CEC_RT0         0x7510                       
#define SATURN_ISO_CEC_RT1         0x7514                       
#define SATURN_ISO_CEC_RX0         0x7518                       
#define SATURN_ISO_CEC_RX1         0x751C                       
#define SATURN_ISO_CEC_TX0         0x7520                       
#define SATURN_ISO_CEC_TX1         0x7524                       
#define SATURN_ISO_CEC_TX_FIFO     0x7528                       
#define SATURN_ISO_CEC_RX_FIFO     0x752C                       
#define SATURN_ISO_CEC_RX_START0   0x7530                       
#define SATURN_ISO_CEC_RX_START1   0x7534                       
#define SATURN_ISO_CEC_RX_DATA0    0x7538                       
#define SATURN_ISO_CEC_RX_DATA1    0x753C                       
#define SATURN_ISO_CEC_TX_START0   0x7540                       
#define SATURN_ISO_CEC_TX_START1   0x7544                       
#define SATURN_ISO_CEC_TX_DATA0    0x7548                       
#define SATURN_ISO_CEC_TX_DATA1    0x754C                       
#define SATURN_ISO_CEC_TX_DATA2    0x7550   

#define SATURN_MIS_SCPU_INT_EN		0x1B080
#define SATURN_MIS_KCPU_INT_EN		0x1B084

#endif /* !(_MACH_SATURN_H) */

