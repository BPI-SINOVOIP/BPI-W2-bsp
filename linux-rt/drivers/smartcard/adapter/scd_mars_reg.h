/*
 * scd_mars_reg.h - smartcard driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 */

#ifndef __MARS_SCD_REG_H__
#define __MARS_SCD_REG_H__
                                 
#define MIS_ISR                (0xb801b00c)
#define MIS_SC0_INT            (0x00000001<<24)
                                                                 


#define MAX_IFD_CNT             1
#define IFD_MODOLE              "Kylin"
#define SC_BASE0                0x9801BE00
#define MIS_SC0_INT            (0x00000001<<24)
#define SYSTEM_CLK              27000000


#define SCFP                    0x0000      /* Smartcard Carrier Frequency Programmer*/
#define SCCR                    0x0004      /* Smartcard Control Register */
#define SCPCR                   0x0008      /* Smartcard Protocol Control Register */
#define SCTXFIFO                0x000C      /* Smartcard Transmit FIFO Register */
#define SCTXLENR                0x0010      /* Smartcard Txmit Length Register */
#define SCRXFIFO                0x0014      /* Smartcard Receive FIFO Register */
#define SCRXLENR                0x0018      /* Smartcard Receive Length Register */
#define SCFCR                   0x001C      /* Smartcard Flow Control Register */
#define SCIRSR                  0x0020      /* Smartcard Interrupt Status Register */
#define SCIRER                  0x0024      /* Smartcard Interrupt Enable Register */

// SC_FP - SC Frequency Programmer
#define SC_CLK_EN(x)            ((x & 0x00000001)<<24)
#define SC_CLKDIV(x)            ((x & 0x0000003F)<<18)
#define SC_BAUDDIV2(x)          ((x & 0x00000003)<<16)
#define SC_BAUDDIV1(x)          ((x & 0x000000FF)<<8)
#define SC_PRE_CLKDIV(x)        ((x & 0x000000FF))
#define SC_CLKDIV_MASK          SC_CLKDIV(0x3F)
#define SC_BAUDDIV2_MASK        SC_BAUDDIV2(0x3)
#define SC_BAUDDIV1_MASK        SC_BAUDDIV1(0xFF)
#define SC_BAUDDIV_MASK         (SC_BAUDDIV1_MASK | SC_BAUDDIV2_MASK)
#define SC_PRE_CLKDIV_MASK      SC_PRE_CLKDIV(0xFF)

#define SC_CLK_EN_VAL(x)        ((x << 24) & 0x00000001)
#define SC_CLKDIV_VAL(x)        ((x << 18) & 0x0000003F)
#define SC_BAUDDIV2_VAL(x)      ((x << 16) & 0x00000003)
#define SC_BAUDDIV1_VAL(x)      ((x <<  8) & 0x000000FF)
#define SC_PRE_CLKDIV_VAL(x)    ((x & 0x000000FF))

// SC_CR - SC Control Register
#define SC_FIFO_RST(x)          ((x & 0x00000001)<<31)
#define SC_RST(x)               ((x & 0x00000001)<<30)
#define SC_SCEN(x)              ((x & 0x00000001)<<29)
#define SC_TX_GO(x)             ((x & 0x00000001)<<28)
#define SC_AUTO_ATR(x)          ((x & 0x00000001)<<27)
#define SC_CONV(x)              ((x & 0x00000001)<<26)
#define SC_CLK_STOP(x)          ((x & 0x00000001)<<25)
#define SC_PS(x)                ((x & 0x00000001)<<24)

#define SC_PS_VAL(x)            ((x >> 24) & 0x00000001)


// SCPCR - SC Protocol control Register 
#define SC_TXGRDT(x)          ((x & 0x000000FF)<<24)
#define SC_CWI(x)             ((x & 0x0000000F)<<20)
#define SC_BWI(x)             ((x & 0x0000000F)<<16)
#define SC_WWI(x)             ((x & 0x0000000F)<<12)
#define SC_BGT(x)             ((x & 0x0000001F)<<7)
#define SC_EDC_EN(x)          ((x & 0x00000001)<<6)
#define SC_CRC(x)             ((x & 0x00000001)<<5)
#define SC_PROTOCOL_T(x)      ((x & 0x00000001)<<4)
#define SC_T0RTY(x)           ((x & 0x00000001)<<3)
#define SC_T0RTY_CNT(x)       ((x & 0x00000007))

#define MASK_SC_TXGRDT        SC_TXGRDT(0xFF)
#define MASK_SC_CWI           SC_CWI(0xF)
#define MASK_SC_BWI           SC_BWI(0xF)
#define MASK_SC_WWI           SC_WWI(0xF)
#define MASK_SC_BGT           SC_BGT(0x1F)
#define MASK_SC_EDC_EN        SC_EDC_EN(1)
#define MASK_SC_EDC_TYPE      SC_EDC_TYPE(1)
#define MASK_SC_PROTOCOL      SC_PROTOCOL(1)
#define MASK_SC_T0RTY         SC_T0RTY(1)
#define MASK_SC_T0RTY_CNT     SC_T0RTY_CNT(1)

// SC_FCR - Flow Control Register
#define SC_RXFLOW(x)          ((x & 0x00000001)<<1)
#define SC_FLOW_EN(x)         ((x & 0x00000001))


// SCIRSR & SCIRER - SC Interrupt Status/Enable Register
#define SC_DRDY_INT           0x00000001
#define SC_RCV_INT            0x00000002
#define SC_BWT_INT            0x00000004
#define SC_WWT_INT            0x00000008
#define SC_RLEN_INT           0x00000010
#define SC_CWT_INT            0x00000020
#define SC_BGT_INT            0x00000040
#define SC_ATRS_INT           0x00000080
#define SC_RXP_INT            0x00000100
#define SC_RX_FOVER_INT       0x00000200
#define SC_EDCERR_INT         0x00000400
#define SC_TXEMPTY_INT        0x00000800
#define SC_TXDONE_INT         0x00001000
#define SC_TXP_INT            0x00002000
#define SC_TXFLOW_INT         0x00004000
#define SC_CPRES_INT          0x00008000
#define SC_PRES               0x00010000


#endif  //__MARS_SCD_REG_H__

