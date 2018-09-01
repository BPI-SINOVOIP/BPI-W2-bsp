/*
 *  Copyright (C) 2013 Realtek Semiconductors, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __REG_MMC_H
#define __REG_MMC_H

/* eMMC control register definition */
#define CR_BASE_ADDR            0x00000000  //map to 0x98012000

//1295 emmc ip register
#define EMMC_CTRL                            ( CR_BASE_ADDR)
#define EMMC_PWREN                           ( CR_BASE_ADDR + 0x004)
#define EMMC_CLKDIV                          ( CR_BASE_ADDR + 0x008)
#define EMMC_CLKSRC                          ( CR_BASE_ADDR + 0x00C)
#define EMMC_CLKENA                          ( CR_BASE_ADDR + 0x010)
#define EMMC_TMOUT                           ( CR_BASE_ADDR + 0x014)
#define EMMC_CTYPE                           ( CR_BASE_ADDR + 0x018)
#define EMMC_BLKSIZE                         ( CR_BASE_ADDR + 0x01C)
#define EMMC_BYTCNT                          ( CR_BASE_ADDR + 0x020)
#define EMMC_INTMASK                         ( CR_BASE_ADDR + 0x024)
#define EMMC_CMDARG                          ( CR_BASE_ADDR + 0x028)
#define EMMC_CMD                             ( CR_BASE_ADDR + 0x02C)
#define EMMC_RESP0                           ( CR_BASE_ADDR + 0x030)
#define EMMC_RESP1                           ( CR_BASE_ADDR + 0x034)
#define EMMC_RESP2                           ( CR_BASE_ADDR + 0x038)
#define EMMC_RESP3                           ( CR_BASE_ADDR + 0x03C)
#define EMMC_MINTSTS                         ( CR_BASE_ADDR + 0x040)
#define EMMC_RINTSTS                         ( CR_BASE_ADDR + 0x044)
#define EMMC_STATUS                          ( CR_BASE_ADDR + 0x048)
#define EMMC_FIFOTH                          ( CR_BASE_ADDR + 0x04C)
#define EMMC_TBBCNT                          ( CR_BASE_ADDR + 0x060)
#define EMMC_UHSREG                          ( CR_BASE_ADDR + 0x074)
#define EMMC_BMOD                            ( CR_BASE_ADDR + 0x080)
#define EMMC_DBADDR                          ( CR_BASE_ADDR + 0x088)
#define EMMC_IDINTEN                         ( CR_BASE_ADDR + 0x090)
#define EMMC_IDSTS			     			 ( CR_BASE_ADDR + 0x08C)
#define EMMC_CARD_THR_CTL			         ( CR_BASE_ADDR + 0x100)
#define EMMC_DDR_REG			     		 ( CR_BASE_ADDR + 0x10c)


//1295 emmc wrapper register
#define EMMC_DESC_CTL0         ( 0x400 )
#define EMMC_DESC_CTL1         ( 0x404 )
#define EMMC_DESC_CTL2         ( 0x408 )
#define EMMC_DESC_CTL3         ( 0x40C )
#define EMMC_DESC_STS          ( 0x410 )
#define EMMC_DESC_THD          ( 0x414 )
#define EMMC_SYS_LOW_PWR       ( 0x418 )
#define EMMC_CP                ( 0x41c )
#define EMMC_OTHER1            ( 0x420 )
#define EMMC_ISR               ( 0x424 )
#define EMMC_DBG				(0x444)
#define EMMC_PAD_CTL           ( 0x474 )
#define EMMC_IP_DESC0			( 0x4a0)
#define EMMC_IP_DESC1			( 0x4a4)
#define EMMC_IP_DESC2			( 0x4a8)
#define EMMC_IP_DESC3			( 0x4ac)
#define EMMC_MAIN2_DBG			( 0x4b0)

#if defined(CONFIG_ARCH_RTD129x)
#define EMMC_muxpad0				(0x600)	//mux for nand and emmc
#define EMMC_muxpad1				(0x604)	//mux for sdio and sd card
#define EMMC_PFUNC_NF1				(0x60c)	
#define EMMC_PFUNC_CR				(0x610)	
#define EMMC_muxpad2				(0x61c)
#define EMMC_PDRIVE_NF0        ( 0x620 )
#define EMMC_PDRIVE_NF1        ( 0x624 )
#define EMMC_PDRIVE_NF2        ( 0x628 )
#define EMMC_PDRIVE_NF3        ( 0x62c )
#define EMMC_PDRIVE_NF4        ( 0x630 )

#define EMMC_PDRIVE_CR0        ( 0x634 )
#define EMMC_PDRIVE_CR1        ( 0x638 )
#define EMMC_PDRIVE_SDIO           ( 0x63c )
#define EMMC_PDRIVE_SDIO1          ( 0x640 )

#elif defined(CONFIG_ARCH_RTD139x)	//139x
#define ISO_MUXPAD	( 0x00000000 )
#define ISO_muxpad4	( ISO_MUXPAD + 0x10 )
#define pfunc_emmc0	( ISO_MUXPAD + 0x50 )
#define pfunc_emmc1     ( ISO_MUXPAD + 0x54 )
#define pfunc_emmc2     ( ISO_MUXPAD + 0x58 )
#define pfunc_emmc3     ( ISO_MUXPAD + 0x5c )
#define pfunc_emmc4     ( ISO_MUXPAD + 0x60 )
#define pfunc_emmc5     ( ISO_MUXPAD + 0x64 )

#elif defined(CONFIG_ARCH_RTD16xx)	//16xx
#define M2TMX      ( 0x00000000 )
#define m2tmx_muxpad0     ( M2TMX )
#define m2tmx_pfunc4     ( M2TMX + 0x1c )
#define m2tmx_pfunc5     ( M2TMX + 0x20 )
#define m2tmx_pfunc6     ( M2TMX + 0x24 )
#define m2tmx_pfunc7     ( M2TMX + 0x28 )
#define m2tmx_pfunc8     ( M2TMX + 0x2c )
#endif

//MISC
#define MISC_GP2DIR 				(0x108)
#define MISC_GP3DIR 				(0x10c)

#define MISC_GP2DATO 				(0x118)
#define MISC_GP3DATO 				(0x11c)

#define MISC_DUMMY1 				(0x0e4)
#define MISC_DUMMY2 				(0x0e8)



#define ISR_WRITE_DATA	     1 //set bit
#define ISR_DMA_DONE_INT	(1<<1)
#define ISR_DMA_INT_MASK	(1<<2)
#define ISR_DESC_INT_MASK	(1<<3)
#define ISR_IP_INT_MASK	(1<<4)
#define EMMC_ISREN             ( 0x428 )
#define EMMC_DUMMY_SYS         ( 0x42c )
#define EMMC_AHB               ( 0x430 )
#define EMMC_IP_CTL            ( 0x470 )
#define EMMC_CKGEN_CTL         ( 0x478 )
#define EMMC_CARD_DRV1         ( 0x490 )
#define EMMC_CARD_DRV2         ( 0x494 )
#define EMMC_DQS_CTRL1         ( 0x498 )
#define EMMC_SWC_SEL           ( 0x4d4 )

#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
#define EMMC_SWC_SEL1          ( 0x4d8 )
#define EMMC_SWC_SEL2          ( 0x4dc )
#define EMMC_SWC_SEL3          ( 0x4e0 )
#endif

#define RESP_LEN64                (0x1)
#define RESP_LEN17                (0x2)
#define DMA_XFER                (0x00000001)
#define DDR_WR                  (0x00000001<<1)
#define RSP17_SEL               (0x00000001<<4)
#define RSP64_SEL               (0x00000001<<5)
#define DAT64_SEL               (0x00000001<<5)

/*CARD_EXIST 0x1801051f */
#if 0
#define SD_WRITE_PROTECT		(0x00000001<<5)
#define XD_EXISTENCE			(0x00000001<<4)
#define MS_EXISTENCE			(0x00000001<<3)
#define SD_EXISTENCE			(0x00000001<<2)
#define SM_EXISTENCE			(0x00000001<<1)
#endif

/* SD_CONFIGURE1 0x18012180 */
#define SDCLK_DIV                   (0x00000001<<7)
#define SDCLK_NO_DIV                (0x00000000)
#define SDCLK_DIV_128               (0x00000000)
#define SDCLK_DIV_256               (0x00000001<<6)
#define NO_RST_RDWR_FIFO            (0x00000000)
#define RST_RDWR_FIFO               (0x00000001<<4)

#define MASK_CLOCK_MODE         (0x00000003<<2)
#define MASK_CLOCK_DIV          (0x00000003<<6)
#define CLOCK_DIV_NON           (0x00000002)
#define CLOCK_DIV_256           (0x00000001<<6)
#define CLOCK_DIV_128           (0x00000000)
#define EMMC_CLOCK_DIV_NON      (0x00000000)
#define EMMC_CLOCK_DIV_2        (0x00000001)
#define EMMC_CLOCK_DIV_8        (0x00000004)
#define EMMC_CLOCK_DIV_128      (0x00000001<<6)
#define EMMC_CLOCK_DIV_256      (0x00000001<<7)


#define SPEED_MOD_HIGH          (0x00000001<<4)
#define SPEED_MOD_NORM          (0x00000000)
#define DELAY_PHA_MASK          (0x00000003<<2)
#define DELAY_PHA_NORM          (0x00000001<<3)
#define DELAY_PHA_HIGH          (0x00000001<<2)
#define SD30_ASYNC_FIFO_RST		(0x00000001<<4)
#define ACCESS_MODE_SDR       	(0x00000000)
#define ACCESS_MODE_DDR        	(0x00000001)
#define ACCESS_MODE_HS200       (0x00000002)
#define ACCESS_MODE_HS400       (0x00000003)
#define MODE_SEL_MASK          	(0x00000003<<2)
#define MODE_SEL_SD20          	(ACCESS_MODE_SD20<<2)
#define MODE_SEL_DDR          	(ACCESS_MODE_DDR<<2)
#define MODE_SEL_SD30          	(ACCESS_MODE_SD30<<2)

#define MASK_MODE_SELECT        (0x0c)
#define MODE_SDR                (0x00) //sdr20/50
#define MODE_DDR                (0x01<<2) //ddr50
#define MODE_HS200              (0x02<<2) //hs-200
#define MODE_HS400              (0x03<<2) //hs-400

#define MASK_BUS_WIDTH          (0x00010001)
#define BUS_WIDTH_1             (0x00000000)
#define BUS_WIDTH_4             (0x00000001)
#define BUS_WIDTH_8             (0x00010000)

/* CPU_ACC_CTL 0x18012080 */
#define CPU_MODE_EN             (0x00000001)
#define BUF_FULL		(0x00000001<<2)

/* SD_CONFIGURE2 0x18012181 */
#define CRC7_CAL_DIS            (0x00000001<<7)
#define CRC16_CAL_DIS           (0x00000001<<6)
#define IGN_WR_CRC_ERR_EN	(0x00000001<<4)
#define WAIT_BUSY_EN            (0x00000001<<3)
#define CRC7_CHK_DIS            (0x00000001<<2)

#define MASK_RESP_TYPE          (0x00000003)
#define RESP_TYPE_NON           (0x00000000)
#define RESP_TYPE_6B            (0x00000001)
#define RESP_TYPE_17B           (0x00000002)

/* SD_CONFIGURE3 0x18012182 */
#define DATA_TRANS_OVER_EN      (0x00000001<<3)
#define RESP_CHK_EN             (0x00000001<<2)
#define ADDR_BYTE_MODE          (0x00000001<<1)
#define SD_CMD_RSP_TO           (0x00000001<<0)

/* SD_TRANSFER 0x18012193 */
//98012044 : Raw Interrupt Status Register
#define INT_STS_EBE		(1<<15)
#define INT_STS_ACD		(1<<14)
#define INT_STS_SBE_BCI		(1<<13)
#define INT_STS_HLE		(1<<12)
#define INT_STS_FRUN		(1<<11)
#define INT_STS_HTO		(1<<10)
#define INT_STS_DRTO_BDS	(1<<9)
#define INT_STS_RTO_BAR		(1<<8)
#define INT_STS_DCRC		(1<<7)
#define INT_STS_RCRC		(1<<6)
#define INT_STS_RXDR		(1<<5)
#define INT_STS_TXDR		(1<<4)
#define INT_STS_DTO		(1<<3)
#define INT_STS_CD	  	(1<<2)
#define INT_STS_RE		(1<<1)
#define INT_STS_CRD		(1<<0)
#define INT_STS_ERRORS		(INT_STS_RE|INT_STS_RCRC|INT_STS_DCRC|INT_STS_RTO_BAR|INT_STS_DRTO_BDS|INT_STS_HTO|INT_STS_FRUN|INT_STS_HLE|INT_STS_SBE_BCI|INT_STS_EBE)
#define INT_STS_ERRORS2		(INT_STS_RE|INT_STS_RCRC|INT_STS_DCRC|INT_STS_DRTO_BDS|INT_STS_HTO|INT_STS_FRUN|INT_STS_HLE|INT_STS_SBE_BCI|INT_STS_EBE)


#define INT_EN			(INT_STS_ACD|INT_STS_DTO|INT_STS_CD)

//98012048 : Status Register
#define STS_RSP_IDX_MASK       (0x3f<<11)
#define STS_RSP_IDX            (11)

#define STS_DATA_BUSY		(1<<9)
#define STS_DATA_3_STATUS	(1<<8)

//9801202c : command register
#define CMD_IDX_MASK(x)		(x & 0x3f)
#define CMD_IDX			(0x3f)
#define CMD_RSP_EXP		(1<<6)
#define CMD_RSP_LEN		(1<<7)
#define CMD_CHK_RESP_CRC	(1<<8)
#define CMD_DATA_EXP		(1<<9)
#define CMD_RD_WR		(1<<10)
#define CMD_TRANS_MODE		(1<<11)
#define CMD_SEND_AUTO_STOP	(1<<12)
#define CMD_WAIT_PRV_DATA_COMPLETE	(1<<13)
#define CMD_USE_HOLD_REG	(1<<29)
#define CMD_START_CMD		(1<<31)


#define MASK_CMD_CODE           (0x0F)
#define SD_NORMALWRITE          (0x00)
#define SD_AUTOWRITE3           (0x01)
#define SD_AUTOWRITE4           (0x02)
#define SD_AUTOREAD3            (0x05)
#define SD_AUTOREAD4            (0x06)
#define SD_SENDCMDGETRSP        (0x08)
#define SD_AUTOWRITE1           (0x09)
#define SD_AUTOWRITE2           (0x0A)
#define SD_NORMALREAD           (0x0C)
#define SD_AUTOREAD1            (0x0D)
#define SD_AUTOREAD2            (0x0E)
#define SD_CMD_UNKNOW           (0x0F)

#define EMMC_MASK_CMD_CODE        (0xFF)
#define EMMC_NORMALWRITE          (0x00)
#define EMMC_AUTOWRITE3           (0x01)
#define EMMC_AUTOWRITE4           (0x02)
#define EMMC_AUTOREAD3            (0x05)
#define EMMC_AUTOREAD4            (0x06)
#define EMMC_SENDCMDGETRSP        (0x08)
#define EMMC_AUTOWRITE1           (0x09)
#define EMMC_AUTOWRITE2           (0x0A)
#define EMMC_NORMALREAD           (0x0C)
#define EMMC_AUTOREAD1            (0x0D)
#define EMMC_AUTOREAD2            (0x0E)
#define EMMC_TUNING               (0x0F)
#define EMMC_CMD_UNKNOW           (0x10)

/* SD_CONFIGURE2 0x18012181 */
#define CRC7_STATUS             (0x00000001<<7)
#define CRC16_STATUS            (0x00000001<<6)
#define WRT_ERR_BIT             (0x00000001<<5)
#define CRC_TIMEOUT_ERR         (0x00000001<<1)
#define PATTERN_CMP_ERR         (0x00000001<<0)
#define WRITE_CRC_ERR_STAT(x)   ((x & (0x7<<2))>>2)
/* SD_STATUS2 0x18012184 */
#define SD_CMD_RESP_INVALID     (0x00000001<<1)
#define SD_CMD_RESP_TIMEOUT     (0x00000001)
/* SD_BUS_STATUS 0x18012185 */
#define SD_CLK_TOG_EN     		(0x00000001<<7)
#define SD_CLK_TOG_STOP     	(0x00000001<<6)
#define SD_DAT3_0_LEVEL     	(0x0000000F<<1)
#define SD_CMD_LEVEL     		(0x00000001<<0)


#define WRITE_DATA              (0x1)
#define CLR_WRITE_DATA          (0x0)
#define SD_EMMC_INT_EN          (0x00000001<<2)
#endif
