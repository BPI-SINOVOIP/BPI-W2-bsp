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
#define CR_BASE_ADDR            (0x00000000)  //map to 0x98012000

//hank emmc ip register

#define EMMC_SDMASA_R			     (CR_BASE_ADDR)
#define EMMC_BLOCKSIZE_R		     (CR_BASE_ADDR + 0x004)
#define EMMC_BLOCKCOUNT_R    		     (CR_BASE_ADDR + 0x006)
#define EMMC_ARGUMENT_R      		     (CR_BASE_ADDR + 0x008)
#define EMMC_XFER_MODE_R     		     (CR_BASE_ADDR + 0x00c)
#define EMMC_CMD_R           		     (CR_BASE_ADDR + 0x00e)
#define EMMC_RESP01_R        		     (CR_BASE_ADDR + 0x010)
#define EMMC_RESP23_R        		     (CR_BASE_ADDR + 0x014)
#define EMMC_RESP45_R        		     (CR_BASE_ADDR + 0x018)
#define EMMC_RESP67_R        		     (CR_BASE_ADDR + 0x01c)
#define EMMC_BUF_DATA_R			     (CR_BASE_ADDR + 0x020)
#define EMMC_PSTATE_REG      		     (CR_BASE_ADDR + 0x024)
#define EMMC_HOST_CTRL1_R		     (CR_BASE_ADDR + 0x028)
#define EMMC_PWR_CTRL_R    		     (CR_BASE_ADDR + 0x029)
#define EMMC_BGAP_CTRL_R		     (CR_BASE_ADDR + 0x02a)
#define EMMC_CLK_CTRL_R			     (CR_BASE_ADDR + 0x02c)
#define EMMC_TOUT_CTRL_R    		     (CR_BASE_ADDR + 0x02e)
#define EMMC_SW_RST_R     		     (CR_BASE_ADDR + 0x02f)
#define EMMC_NORMAL_INT_STAT_R		     (CR_BASE_ADDR + 0x030)
#define EMMC_ERROR_INT_STAT_R		     (CR_BASE_ADDR + 0x032)
#define EMMC_NORMAL_INT_STAT_EN_R    	     (CR_BASE_ADDR + 0x034)
#define EMMC_ERROR_INT_STAT_EN_R      	     (CR_BASE_ADDR + 0x036)
#define EMMC_NORMAL_INT_SIGNAL_EN_R  	     (CR_BASE_ADDR + 0x038)
#define EMMC_ERROR_INT_SIGNAL_EN_R           (CR_BASE_ADDR + 0x03a)
#define EMMC_AUTO_CMD_STAT_R           	     (CR_BASE_ADDR + 0x03c)
#define EMMC_HOST_CTRL2_R                    (CR_BASE_ADDR + 0x03e)
#define EMMC_ADMA_ERR_STAT_R		     (CR_BASE_ADDR + 0x054)
#define EMMC_ADMA_SA_LOW_R                   (CR_BASE_ADDR + 0x058)
#define EMMC_AT_CTRL_R                       (CR_BASE_ADDR + 0x240)

#define EMMC_MSHC_CTRL_R                     (CR_BASE_ADDR + 0x208)
#define EMMC_CMD_CONFLICT_CHECK              (1<<0)

#define EMMC_CTRL_R			     (CR_BASE_ADDR + 0x22c)
//hank emmc wrapper register
#define EMMC_CP                       	(CR_BASE_ADDR + 0x41c)
#define EMMC_OTHER1                     (CR_BASE_ADDR + 0x420)
#define EMMC_ISR                        (CR_BASE_ADDR + 0x424)  //unused in hank
#define EMMC_ISREN                      (CR_BASE_ADDR + 0x428)	//unused in hank
#define EMMC_DUMMY_SYS                  (CR_BASE_ADDR + 0x42c)
#define EMMC_AHB                  	(CR_BASE_ADDR + 0x430)
#define EMMC_DBG                        (CR_BASE_ADDR + 0x444)
#define EMMC_PP_BIST_CTL                (CR_BASE_ADDR + 0x460)
#define EMMC_IP_BIST_CTL                (CR_BASE_ADDR + 0x464)
#define EMMC_PP_BIST_STS                (CR_BASE_ADDR + 0x468)
#define EMMC_IP_BIST_STS                (CR_BASE_ADDR + 0x46c)
#define EMMC_CKGEN_CTL                	(CR_BASE_ADDR + 0x478)
#define EMMC_CARD_SIG                   (CR_BASE_ADDR + 0x484)
#define EMMC_DQS_CTRL1                  (CR_BASE_ADDR + 0x498)
#define EMMC_DQS_CTRL2                  (CR_BASE_ADDR + 0x49c)
#define EMMC_IP_DESC0                   (CR_BASE_ADDR + 0x4a0)
#define EMMC_IP_DESC1                   (CR_BASE_ADDR + 0x4a4)
#define EMMC_IP_DESC2                   (CR_BASE_ADDR + 0x4a8)
#define EMMC_IP_DESC3                   (CR_BASE_ADDR + 0x4ac)
#define EMMC_PROTECT0                   (CR_BASE_ADDR + 0x4c0)
#define EMMC_PROTECT1                   (CR_BASE_ADDR + 0x4c4)
#define EMMC_PROTECT2                   (CR_BASE_ADDR + 0x4c8)
#define EMMC_PROTECT3                   (CR_BASE_ADDR + 0x4cc)
#define EMMC_SWC_SEL_CHK                (CR_BASE_ADDR + 0x4e4)
#define EMMC_DUMMY_SYS1                 (CR_BASE_ADDR + 0x500)
#define EMMC_CLK_DET_PLLEMMC            (CR_BASE_ADDR + 0x504)
#define EMMC_DQ_CTRL_SET                (CR_BASE_ADDR + 0x50c)
#define EMMC_WDQ_CTRL0                  (CR_BASE_ADDR + 0x510)
#define EMMC_WDQ_CTRL1                  (CR_BASE_ADDR + 0x514)
#define EMMC_WDQ_CTRL2                  (CR_BASE_ADDR + 0x518)
#define EMMC_WDQ_CTRL3                  (CR_BASE_ADDR + 0x51c)
#define EMMC_WDQ_CTRL4                  (CR_BASE_ADDR + 0x520)
#define EMMC_WDQ_CTRL5                  (CR_BASE_ADDR + 0x524)
#define EMMC_WDQ_CTRL6                  (CR_BASE_ADDR + 0x528)
#define EMMC_WDQ_CTRL7                  (CR_BASE_ADDR + 0x52c)
#define EMMC_RDQ_CTRL0                  (CR_BASE_ADDR + 0x530)
#define EMMC_RDQ_CTRL1                  (CR_BASE_ADDR + 0x534)
#define EMMC_RDQ_CTRL2                  (CR_BASE_ADDR + 0x538)
#define EMMC_RDQ_CTRL3                  (CR_BASE_ADDR + 0x53c)
#define EMMC_RDQ_CTRL4                  (CR_BASE_ADDR + 0x540)
#define EMMC_RDQ_CTRL5                  (CR_BASE_ADDR + 0x544)
#define EMMC_RDQ_CTRL6                  (CR_BASE_ADDR + 0x548)
#define EMMC_RDQ_CTRL7                  (CR_BASE_ADDR + 0x54c)
#define EMMC_CMD_CTRL_SET		(CR_BASE_ADDR + 0x550)
#define EMMC_WCMD_CTRL                  (CR_BASE_ADDR + 0x554)
#define EMMC_RCMD_CTRL                  (CR_BASE_ADDR + 0x558)
#define EMMC_PLL_STATUS                 (CR_BASE_ADDR + 0x55c)

#define EMMC_PON_DES0                   (CR_BASE_ADDR + 0x800)
#define EMMC_PON_DES1                   (CR_BASE_ADDR + 0x804)
#define EMMC_PON_DES2                   (CR_BASE_ADDR + 0x808)
#define EMMC_PON_CTRL                   (CR_BASE_ADDR + 0x80c)
#define EMMC_PON_ID                     (CR_BASE_ADDR + 0x810)
#define EMMC_PON_ADDR                   (CR_BASE_ADDR + 0x814)
#define EMMC_PON_ST                     (CR_BASE_ADDR + 0x818)
#define EMMC_PON_SAVE                   (CR_BASE_ADDR + 0x81c)
#define EMMC_PON_DBUS_SLV               (CR_BASE_ADDR + 0x820)
#define EMMC_PON_DBG_CTRL               (CR_BASE_ADDR + 0x824)
#define EMMC_PON_DBUS_SLV_DBG           (CR_BASE_ADDR + 0x828)
#define EMMC_PON_MEM                    (CR_BASE_ADDR + 0x82c)
#define EMMC_PON_DBG0                   (CR_BASE_ADDR + 0x830)
#define EMMC_PON_DBG1                   (CR_BASE_ADDR + 0x834)
#define EMMC_PON_DBG2                   (CR_BASE_ADDR + 0x838)
#define EMMC_PON_DBG3                   (CR_BASE_ADDR + 0x83c)
#define EMMC_PON_DBG_CTRL1              (CR_BASE_ADDR + 0x840)

#define EMMC_HD_SEM                     (CR_BASE_ADDR + 0x900)

//0x98012030 status bitmap
#define EMMC_ERR_INTERRUPT		1<<15
#define EMMC_CQE_EVENT			1<<14
#define EMMC_FX_EVENT			1<<13
#define EMMC_RE_TUNE_EVENT		1<<12
#define EMMC_INT_C			1<<11
#define EMMC_INT_B                      1<<10
#define EMMC_INT_A                      1<<9
#define EMMC_CARD_INTERRUPT		1<<8
#define EMMC_CARD_REMOVAL		1<<7
#define EMMC_CARD_INSERTION             1<<6
#define EMMC_BUF_RD_READY		1<<5
#define EMMC_BUF_WR_READY               1<<4
#define EMMC_DMA_INTERRPT		1<<3
#define EMMC_BGAP_EVENT			1<<2
#define EMMC_XFER_COMPLETE		1<<1
#define EMMC_CMD_COMPLETE		1

//0x98012032 error bitmap
#define EMMC_VENDOR_ERR3		1<<15
#define EMMC_VENDOR_ERR2                1<<14
#define EMMC_VENDOR_ERR1                1<<13
#define EMMC_BOOT_ACK_ERR               1<<12
#define EMMC_RESP_ERR			1<<11
#define EMMC_TUNING_ERR			1<<10
#define EMMC_ADMA_ERR			1<<9
#define EMMC_AUTO_CMD_ERR		1<<8
#define EMMC_CUR_LMT_ERR		1<<7
#define EMMC_DATA_END_BIT_ERR		1<<6
#define EMMC_DATA_CRC_ERR		1<<5
#define EMMC_DATA_TOUT_ERR		1<<4
#define EMMC_CMD_IDX_ERR		1<<3
#define EMMC_CMD_END_BIT_ERR		1<<2
#define EMMC_CMD_CRC_ERR		1<<1
#define EMMC_CMD_TOUT_ERR		1

//0x98012034 status enable bitmap
#define EMMC_CQE_EVENT_STAT_EN                  1<<14
#define EMMC_FX_EVENT_STAT_EN                   1<<13
#define EMMC_RE_TUNE_EVENT_STAT_EN              1<<12
#define EMMC_INT_C_STAT_EN                      1<<11
#define EMMC_INT_B_STAT_EN                      1<<10
#define EMMC_INT_A_STAT_EN                      1<<9
#define EMMC_CARD_INTERRUPT_STAT_EN             1<<8
#define EMMC_CARD_REMOVAL_STAT_EN               1<<7
#define EMMC_CARD_INSERTION_STAT_EN             1<<6
#define EMMC_BUF_RD_READY_STAT_EN               1<<5
#define EMMC_BUF_WR_READY_STAT_EN               1<<4
#define EMMC_DMA_INTERRPT_STAT_EN               1<<3
#define EMMC_BGAP_EVENT_STAT_EN                 1<<2
#define EMMC_XFER_COMPLETE_STAT_EN              1<<1
#define EMMC_CMD_COMPLETE_STAT_EN               1

//0x98012036 error status enable bitmap
#define EMMC_VENDOR_ERR_STAT_EN3                1<<15
#define EMMC_VENDOR_ERR_STAT_EN2                1<<14
#define EMMC_VENDOR_ERR_STAT_EN1                1<<13
#define EMMC_BOOT_ACK_ERR_STAT_EN               1<<12
#define EMMC_RESP_ERR_STAT_EN                   1<<11
#define EMMC_TUNING_ERR_STAT_EN                 1<<10
#define EMMC_ADMA_ERR_STAT_EN                   1<<9
#define EMMC_AUTO_CMD_ERR_STAT_EN               1<<8
#define EMMC_CUR_LMT_ERR_STAT_EN                1<<7
#define EMMC_DATA_END_BIT_ERR_STAT_EN           1<<6
#define EMMC_DATA_CRC_ERR_STAT_EN               1<<5
#define EMMC_DATA_TOUT_ERR_STAT_EN              1<<4
#define EMMC_CMD_IDX_ERR_STAT_EN                1<<3
#define EMMC_CMD_END_BIT_ERR_STAT_EN            1<<2
#define EMMC_CMD_CRC_ERR_STAT_EN                1<<1
#define EMMC_CMD_TOUT_ERR_STAT_EN               1

//0x98012038 signal interrupt enable
#define EMMC_CQE_EVENT_SIGNAL_EN                  1<<14
#define EMMC_FX_EVENT_SIGNAL_EN                   1<<13
#define EMMC_RE_TUNE_EVENT_SIGNAL_EN              1<<12
#define EMMC_INT_C_SIGNAL_EN                      1<<11
#define EMMC_INT_B_SIGNAL_EN                      1<<10
#define EMMC_INT_A_SIGNAL_EN                      1<<9
#define EMMC_CARD_INTERRUPT_SIGNAL_EN             1<<8
#define EMMC_CARD_REMOVAL_SIGNAL_EN               1<<7
#define EMMC_CARD_INSERTION_SIGNAL_EN             1<<6
#define EMMC_BUF_RD_READY_SIGNAL_EN               1<<5
#define EMMC_BUF_WR_READY_SIGNAL_EN               1<<4
#define EMMC_DMA_INTERRPT_SIGNAL_EN               1<<3
#define EMMC_BGAP_EVENT_SIGNAL_EN                 1<<2
#define EMMC_XFER_COMPLETE_SIGNAL_EN              1<<1
#define EMMC_CMD_COMPLETE_SIGNAL_EN               1

//0x9801203a error ssignal enable bitmap
#define EMMC_VENDOR_ERR_SIGNAL_EN3                1<<15
#define EMMC_VENDOR_ERR_SIGNAL_EN2                1<<14
#define EMMC_VENDOR_ERR_SIGNAL_EN1                1<<13
#define EMMC_BOOT_ACK_ERR_SIGNAL_EN               1<<12
#define EMMC_RESP_ERR_SIGNAL_EN                   1<<11
#define EMMC_TUNING_ERR_SIGNAL_EN                 1<<10
#define EMMC_ADMA_ERR_SIGNAL_EN                   1<<9
#define EMMC_AUTO_CMD_ERR_SIGNAL_EN               1<<8
#define EMMC_CUR_LMT_ERR_SIGNAL_EN                1<<7
#define EMMC_DATA_END_BIT_ERR_SIGNAL_EN           1<<6
#define EMMC_DATA_CRC_ERR_SIGNAL_EN               1<<5
#define EMMC_DATA_TOUT_ERR_SIGNAL_EN              1<<4
#define EMMC_CMD_IDX_ERR_SIGNAL_EN                1<<3
#define EMMC_CMD_END_BIT_ERR_SIGNAL_EN            1<<2
#define EMMC_CMD_CRC_ERR_SIGNAL_EN                1<<1
#define EMMC_CMD_TOUT_ERR_STAT_EN                 1

#define EMMC_ALL_NORMAL_STAT_EN			  (0xfeff)
#define EMMC_ALL_ERR_STAT_EN			  (0xffff)	//enablle all error interrupt in 0x98012036
#define EMMC_ALL_SIGNAL_STAT_EN                   (0xfeff)
#define EMMC_ALL_ERR_SIGNAL_EN			  (0xffff)	//enable all singal error interrupt in 0x9801203a


#define CMD_IDX_MASK(x)         ((x >> 8)&0x3f)

//0x9801200e
#define EMMC_RESP_TYPE_SELECT	0
#define EMMC_CMD_TYPE		6
#define EMMC_NO_RESP		0x0
#define EMMC_RESP_LEN_136	0x1
#define EMMC_RESP_LEN_48	0x2
#define EMMC_RESP_LEN_48B	0x3
#define EMMC_CMD_CHK_RESP_CRC        	(1<<3)
#define EMMC_CMD_IDX_CHK_ENABLE		(1<<4)
#define EMMC_DATA			(1<<5)
#define EMMC_ABORT_CMD		0x3
#define EMMC_RESUME_CMD		0x2
#define EMMC_SUSPEND_CMD	0x1
#define EMMC_NORMAL_CMD		0x0

//0x98012028
#define EMMC_DMA_SEL		3
#define EMMC_SDMA		0x0
#define EMMC_ADMA2_32		0x2
#define EMMC_ADMA2_64		0x3
#define EMMC_EXT_DAT_XFER		(1<<5)
#define EMMC_HIGH_SPEED_EN		(1<<2)
#define EMMC_DAT_XFER_WIDTH		(1<<1)
#define EMMC_BUS_WIDTH_8		EMMC_EXT_DAT_XFER
#define EMMC_BUS_WIDTH_4		EMMC_DAT_XFER_WIDTH
#define EMMC_BUS_WIDTH_1		0<<1

//0x9801200c
#define EMMC_MULTI_BLK_SEL		5
#define EMMC_DATA_XFER_DIR		4
#define EMMC_BLOCK_COUNT_ENABLE		(1<<1)
#define EMMC_DMA_ENABLE			(1<<0)
#define EMMC_AUTO_CMD_ENABLE		2
#define EMMC_AUTO_CMD_DISABLED		0x0
#define EMMC_AUTO_CMD12_ENABLED		0x1
#define EMMC_AUTO_CMD23_ENABLED		0x2
#define EMMC_AUTO_CMD_SEL		0x3

//0x9801203e
#define MODE_LEGACY	0x0
#define MODE_SDR	0x1
#define MODE_HS200	0x3
#define MODE_DDR	0x4
#define MODE_HS400	0x7

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

#define EMMC_SWC_SEL                    (0x0)
#define EMMC_SWC_SEL1                   (0x4)
#define EMMC_SWC_SEL2                   (0x8)
#define EMMC_SWC_SEL3                   (0xc)

#define EMMC_NAND_DMA_SEL		(0x54)

#define EMMC_CLK_O_ICG_EN		(1<<3)
#define EMMC_CARD_STOP_ENABLE		(1<<23)

#define EMMC_SW_RST_DAT			(1<<2)

#define EMMC_ISO_pfunc1		(0x20)
#define EMMC_ISO_pfunc2         (0x24)
#define EMMC_ISO_pfunc3         (0x28)
#define EMMC_ISO_pfunc4         (0x2c)
#define EMMC_ISO_pfunc5         (0x30)

#ifdef CONFIG_MMC_RTK_EMMC_CMDQ
//command queue related registers
#define DCMD_SLOT 31
#define NUM_SLOTS 32	//reserve slot 0 for pon
/* 1 sec */
#define HALT_TIMEOUT_MS 1000

#define EMMC_CQCFG		(0x188)
#define EMMC_CQCTL		(0x18c)
#define EMMC_CQIS		(0x190)
#define EMMC_CQIS_STAT_EN	(0x194)
#define EMMC_CQIS_SIGNAL_EN	(0x198)
#define EMMC_CQIC		(0x19c)
#define EMMC_CQTDLBA		(0x1a0)
#define EMMC_CQTDBR		(0x1a8)
#define EMMC_CQTCN		(0x1ac)
#define EMMC_CQDQS		(0x1b0)
#define EMMC_CQDPT		(0x1b4)
#define EMMC_CQTCLR		(0x1b8)
#define EMMC_CQSSC1		(0x1c0)
#define EMMC_CQSSC2		(0x1c4)
#define EMMC_CQCRDCT		(0x1c8)
#define EMMC_CQRMEM		(0x1d0)
#define EMMC_CQTERRI		(0x1d4)
#define EMMC_CQCRI		(0x1d8)
#define EMMC_CQCRA		(0x1dc)

#define EMMC_CQ_EN		(1<<0)
#define EMMC_CQ_HALT		(1<<0)
#define EMMC_TASK_DESC_SIZE	(1<<8)
#define EMMC_DCMD_EN		(1<<12)

#define VALID(x)        ((x & 1) << 0)
#define END(x)          ((x & 1) << 1)
#define INT(x)          ((x & 1) << 2)
#define ACT(x)          ((x & 0x7) << 3)

#define EMMC_CQIS_HAC        (1<<0)
#define EMMC_CQIS_TCC        (1<<1)
#define EMMC_CQIS_RED        (1<<2)
#define EMMC_CQIS_TCL        (1<<3)

/* data command task descriptor fields */
#define FORCED_PROG(x)  ((x & 1) << 6)
#define CONTEXT(x)      ((x & 0xF) << 7)
#define DATA_TAG(x)     ((x & 1) << 11)
#define DATA_DIR(x)     ((x & 1) << 12)
#define PRIORITY(x)     ((x & 1) << 13)
#define QBAR(x)         ((x & 1) << 14)
#define REL_WRITE(x)    ((x & 1) << 15)
#define BLK_COUNT(x)    ((x & 0xFFFF) << 16)
#define BLK_ADDR(x)     ((x & 0xFFFFFFFF) << 32)

/* direct command task descriptor fields */
#define CMD_INDEX(x)    ((x & 0x3F) << 16)
#define CMD_TIMING(x)   ((x & 1) << 22)
#define RESP_TYPE(x)    ((x & 0x3) << 23)

/* transfer descriptor fields */
#define DAT_LENGTH(x)   ((x & 0xFFFF) << 16)
#define DAT_ADDR_LO(x)  ((x & 0xFFFFFFFF) << 32)
#define DAT_ADDR_HI(x)  ((x & 0xFFFFFFFF) << 0)

#define EMMC_CQ_ALL_STAT_EN                   (0x3f)
#define EMMC_CQ_ALL_SIGNAL_EN                 (0x3f)
#endif

#endif
