/************************************************************************
 *
 *  platform_iso.h
 *
 *  Public header file for MacArthur ISO module 
 *
 ************************************************************************/

#ifndef PLATFORM_ISO_H
#define PLATFORM_ISO_H

/************************************************************************
 *  Definition
 ************************************************************************/
#define  ISO_REG_BASE              0xb8007000 
                                   
/* ISO system */                                   
#define  ISO_ISR                   (ISO_REG_BASE + 0x00)   //ISO mask interrupt status
#define  ISO_UMSK_ISR              (ISO_REG_BASE + 0x04)   //ISO unmask interrupt status
#define  ISO_UMSK_ISR_GP           (ISO_REG_BASE + 0x08)   //ISO unmasked GPIO Assert/De-assert interrupt status
#define  ISO_UMSK_ISR_KPADAH       (ISO_REG_BASE + 0x0c)   //ISO unmasked Keypad Assert High interrupt status
#define  ISO_UMSK_ISR_KPADAL       (ISO_REG_BASE + 0x10)   //ISO unmasked Keypad Assert Low interrupt status
#define  ISO_UMSK_ISR_KPADDAH      (ISO_REG_BASE + 0x14)   //ISO unmasked Keypad Dis-Assert High interrupt status
#define  ISO_UMSK_ISR_KPADDAL      (ISO_REG_BASE + 0x18)   //ISO unmasked Keypad Dis-Assert Low interrupt status
#define  ISO_UMSK_ISR_SW           (ISO_REG_BASE + 0x1c)   //ISO unmasked Switch interrupt status
#define  ISO_DBG                   (ISO_REG_BASE + 0x20)   //ISO Debug

#define  ISO_CHIP_INFO1            (ISO_REG_BASE + 0x28)   //ISO CHIP information 1
#define  ISO_CHIP_INFO2            (ISO_REG_BASE + 0x2c)   //ISO CHIP information 2
#define  ISO_CHIP_CTRL             (ISO_REG_BASE + 0x30)   //ISO control
#define  ISO_RTC                   (ISO_REG_BASE + 0x34)   //RTC control


/* GPIO */
#define  ISO_GPDIR                 (ISO_REG_BASE + 0x100)  //GPIO direction
#define  ISO_GPDATO                (ISO_REG_BASE + 0x104)  //GPIO data output
#define  ISO_GPDATI                (ISO_REG_BASE + 0x108)  //GPIO data input
#define  ISO_GPIE                  (ISO_REG_BASE + 0x10c)  //GPIO interrupt enable
#define  ISO_GPDP                  (ISO_REG_BASE + 0x110)  //GPIO detection polarity
#define  ISO_GPDEB                 (ISO_REG_BASE + 0x114)  //GPIO de-bounce length


/* VFD */
/*
#define  ISO_VFD_CTL               (ISO_REG_BASE + 0x200)  //VFD Control
#define  ISO_VFD_WRCTL             (ISO_REG_BASE + 0x204)  //VFD Write Control
#define  ISO_VFDO                  (ISO_REG_BASE + 0x208)  //VFD Date Out
#define  ISO_VFD_ARDCTL            (ISO_REG_BASE + 0x20c)  //VFD Auto Read Control
#define  ISO_VFD_KPADLIE           (ISO_REG_BASE + 0x210)  //VFD Keypad Low Interrupt Enable
#define  ISO_VFD_KPADHIE           (ISO_REG_BASE + 0x214)  //VFD Keypad High Interrupt Enable
#define  ISO_VFD_SWIE              (ISO_REG_BASE + 0x218)  //VFD Switch Interrupt Enable
#define  ISO_VFD_ARDKPADL          (ISO_REG_BASE + 0x21c)  //VFD Auto Read KPAD Low Status
#define  ISO_VFD_ARDKPADH          (ISO_REG_BASE + 0x220)  //VFD Auto Read KPAD High Status
#define  ISO_VFD_ARDSW             (ISO_REG_BASE + 0x224)  //VFD Auto Read Switch Status
#define  ISO_VFD_CTL1              (ISO_REG_BASE + 0x228)  //VFD Control_1
*/

/* PADMUX */
#define  ISO_PFUNC1                (ISO_REG_BASE + 0x300)  //pad function 1
#define  ISO_PFUNC2                (ISO_REG_BASE + 0x304)  //pad function 1
#define  ISO_PADMUX                (ISO_REG_BASE + 0x308)  //pad mux

/* Timer3 */
#define  ISO_TC3TVR                (ISO_REG_BASE + 0x620)
#define  ISO_TC3CVR                (ISO_REG_BASE + 0x624)
#define  ISO_TC3CR                 (ISO_REG_BASE + 0x628)
#define  ISO_TC3ICR                (ISO_REG_BASE + 0x62c)

/* UART0 */
#define  ISO_U0RBR_THR_DLL         (ISO_REG_BASE + 0x800)
#define  ISO_U0IER_DLH             (ISO_REG_BASE + 0x804)  //UART0 interrupt enable/ divisor latch MSB register
#define  ISO_U0FCR                 (ISO_REG_BASE + 0x808)
#define  ISO_U0LCR                 (ISO_REG_BASE + 0x80c)  //UART0 line control register
#define  ISO_U0MCR                 (ISO_REG_BASE + 0x810)
#define  ISO_U0LSR                 (ISO_REG_BASE + 0x814)
#define  ISO_U0MSR                 (ISO_REG_BASE + 0x818)
#define  ISO_U0SCR                 (ISO_REG_BASE + 0x81c)

/* I2C */
/*
#define ISO_IC0_CON                (ISO_REG_BASE + 0x600)
#define ISO_IC0_TAR                (ISO_REG_BASE + 0x604)
#define ISO_IC0_SAR                (ISO_REG_BASE + 0x608)
#define ISO_IC0_HS_MADDR           (ISO_REG_BASE + 0x60c)
#define ISO_IC0_DATA_CMD           (ISO_REG_BASE + 0x610)
#define ISO_IC0_SS_SCL_HCNT        (ISO_REG_BASE + 0x614)
#define ISO_IC0_SS_SCL_LCNT        (ISO_REG_BASE + 0x618)
#define ISO_IC0_FS_SCL_HCNT        (ISO_REG_BASE + 0x61c)
#define ISO_IC0_FS_SCL_LCNT        (ISO_REG_BASE + 0x620)
#define ISO_IC0_INTR_STAT          (ISO_REG_BASE + 0x62c)
#define ISO_IC0_INTR_MASK          (ISO_REG_BASE + 0x630)
#define ISO_IC0_RAW_INTR_STAT      (ISO_REG_BASE + 0x634)
#define ISO_IC0_RX_TL              (ISO_REG_BASE + 0x638)
#define ISO_IC0_TX_TL              (ISO_REG_BASE + 0x63c)
#define ISO_IC0_CLR_INTR           (ISO_REG_BASE + 0x640)
#define ISO_IC0_CLR_RX_UNDER       (ISO_REG_BASE + 0x644)
#define ISO_IC0_CLR_RX_OVER        (ISO_REG_BASE + 0x648)
#define ISO_IC0_CLR_TX_OVER        (ISO_REG_BASE + 0x64c)
#define ISO_IC0_CLR_RD_REQ         (ISO_REG_BASE + 0x650)
#define ISO_IC0_CLR_TX_ABRT        (ISO_REG_BASE + 0x654)
#define ISO_IC0_CLR_RX_DONE        (ISO_REG_BASE + 0x658)
#define ISO_IC0_CLR_ACTIVITY       (ISO_REG_BASE + 0x65c)
#define ISO_IC0_CLR_STOP_DET       (ISO_REG_BASE + 0x660)
#define ISO_IC0_CLR_START_DET      (ISO_REG_BASE + 0x664)
#define ISO_IC0_CLR_GEN_CALL       (ISO_REG_BASE + 0x668)
#define ISO_IC0_ENABLE             (ISO_REG_BASE + 0x66c)
#define ISO_IC0_STATUS             (ISO_REG_BASE + 0x670)
#define ISO_IC0_TXFLR              (ISO_REG_BASE + 0x674)
#define ISO_IC0_RXFLR              (ISO_REG_BASE + 0x678)
#define ISO_IC0_TX_ABRT_SOURCE     (ISO_REG_BASE + 0x680)
#define ISO_IC0_DMA_CR             (ISO_REG_BASE + 0x688)
#define ISO_IC0_DMA_TDLR           (ISO_REG_BASE + 0x68c)
#define ISO_IC0_DMA_RDLR           (ISO_REG_BASE + 0x690)
#define ISO_IC0_COMP_PARAM_1       (ISO_REG_BASE + 0x6f4)
#define ISO_IC0_COMP_VERSION       (ISO_REG_BASE + 0x6f8)
#define ISO_IC0_COMP_TYPE          (ISO_REG_BASE + 0x6fc)
*/

#define  S_BONDING                 8
#define  M_BONDING                 (0x3 << S_BONDING)
#define  BONDING_QFP_128           (0x0 << S_BONDING)
#define  BONDING_QFP_256           (0x1 << S_BONDING)
#define  BONDING_BGA               (0x2 << S_BONDING)

/************************************************************************
 *  Public functions
 ************************************************************************/

#endif /* #ifndef PLATFORM_ISO_H */
