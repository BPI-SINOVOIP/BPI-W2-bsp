/*
 * r8169.c: RealTek 8169/8168/8101 ethernet driver.
 *
 * Copyright (c) 2002 ShuChen <shuchen@realtek.com.tw>
 * Copyright (c) 2003 - 2007 Francois Romieu <romieu@fr.zoreil.com>
 * Copyright (c) a lot of people too. Please respect their work.
 *
 * See MAINTAINERS file for support contact information.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/proc_fs.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/delay.h>
#include <linux/ethtool.h>
#include <linux/mii.h>
#include <linux/if_vlan.h>
#include <linux/crc32.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <linux/pm_runtime.h>
#include <linux/firmware.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_net.h>
#include <linux/of_address.h>
//#include <mach/cpu.h>

#include <asm/io.h>
#include <asm/irq.h>

/* Yukuen: Use kthread to watch link status change. 20150206 */
#include <linux/kthread.h>
#include <linux/suspend.h>
#include <linux/clk.h>
#include <linux/clk-provider.h>
#include <linux/reset.h>

#include <soc/realtek/rtk_cpu.h>
#include <soc/realtek/rtk_chip.h>

#if defined(CONFIG_ARCH_RTD139x)
#include <linux/pinctrl/consumer.h>
#define R_K_DEFAULT		0x8
#define IDAC_FINE_DEFAULT	0x33
#elif defined(CONFIG_ARCH_RTD16xx)
#define RC_K_DEFAULT		0x8888
#define R_K_DEFAULT		0x8888
#define AMP_K_DEFAULT		0x7777
#define ADC_BIAS_K_DEFAULT	0x8888
#endif /* CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */

#define RTL8169_VERSION "2.5LK-NAPI"
#define MODULENAME "r8169"
#define PFX MODULENAME ": "

#if defined(CONFIG_ARCH_RTD16xx)
#define RTL_TX_NO_CLOSE
#endif /* CONFIG_ARCH_RTD16xx */

#define FIRMWARE_8168D_1	"rtl_nic/rtl8168d-1.fw"
#define FIRMWARE_8168D_2	"rtl_nic/rtl8168d-2.fw"
#define FIRMWARE_8168E_1	"rtl_nic/rtl8168e-1.fw"
#define FIRMWARE_8168E_2	"rtl_nic/rtl8168e-2.fw"
#define FIRMWARE_8168E_3	"rtl_nic/rtl8168e-3.fw"
#define FIRMWARE_8168F_1	"rtl_nic/rtl8168f-1.fw"
#define FIRMWARE_8168F_2	"rtl_nic/rtl8168f-2.fw"
#define FIRMWARE_8105E_1	"rtl_nic/rtl8105e-1.fw"
#define FIRMWARE_8402_1		"rtl_nic/rtl8402-1.fw"
#define FIRMWARE_8411_1		"rtl_nic/rtl8411-1.fw"
#define FIRMWARE_8106E_1	"rtl_nic/rtl8106e-1.fw"
#define FIRMWARE_8106E_2	"rtl_nic/rtl8106e-2.fw"
#define FIRMWARE_8168G_2	"rtl_nic/rtl8168g-2.fw"
#define FIRMWARE_8168G_3	"rtl_nic/rtl8168g-3.fw"

// Fix me : work aroud for 1295
#define IOMEM(x)        ((void __force __iomem *)(x))
#define RTK1195_REV_A		0
#define soc_is_rtk1195()	0
#define realtek_rev()		RTK1195_REV_A
// Fix me : work aroud for 1295 end

#define CYAN	"\033[0;36m"
#define NONE	"\033[m"
#ifdef RTL8169_DEBUG
#define assert(expr) \
	if (!(expr)) {					\
		printk( "Assertion failed! %s,%s,%s,line=%d\n",	\
		#expr,__FILE__,__func__,__LINE__);		\
	}
#define dprintk(fmt, args...) \
	do { printk(KERN_DEBUG "\033[0;36m" PFX "\033[m" fmt, ## args); } while (0)
#else
#define assert(expr) do {} while (0)
#define dprintk(fmt, args...)	do {} while (0)
#endif /* RTL8169_DEBUG */

#define R8169_MSG_DEFAULT \
	(NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_IFUP | NETIF_MSG_IFDOWN)

#define TX_SLOTS_AVAIL(tp) \
	(tp->dirty_tx + NUM_TX_DESC - tp->cur_tx)

/* A skbuff with nr_frags needs nr_frags+1 entries in the tx queue */
#define TX_FRAGS_READY_FOR(tp,nr_frags) \
	(TX_SLOTS_AVAIL(tp) >= (nr_frags + 1))

/* Maximum number of multicast addresses to filter (vs. Rx-all-multicast).
   The RTL chips use a 64 element hash table based on the Ethernet CRC. */
static const int multicast_filter_limit = 32;

#define MAX_READ_REQUEST_SHIFT	12
#define TX_DMA_BURST	4	/* Maximum PCI burst, '7' is unlimited */
#define InterFrameGap	0x03	/* 3 means InterFrameGap = the shortest one */

#define R8169_REGS_SIZE		256
#define R8169_NAPI_WEIGHT	64
#define NUM_TX_DESC	64	/* Number of Tx descriptor registers */
#define NUM_RX_DESC	256U	/* Number of Rx descriptor registers */
#define R8169_TX_RING_BYTES	(NUM_TX_DESC * sizeof(struct TxDesc))
#define R8169_RX_RING_BYTES	(NUM_RX_DESC * sizeof(struct RxDesc))

#define RTL8169_TX_TIMEOUT	(6*HZ)
#define RTL8169_PHY_TIMEOUT	(2*HZ)

#define RTL_PROC 1

/* write/read MMIO register */
#define RTL_W8(reg, val8)	writeb ((val8), ioaddr + (reg))
#define RTL_W16(reg, val16)	writew ((val16), ioaddr + (reg))
#define RTL_W32(reg, val32)	writel ((val32), ioaddr + (reg))
#define RTL_R8(reg)		readb (ioaddr + (reg))
#define RTL_R16(reg)		readw (ioaddr + (reg))
#define RTL_R32(reg)		readl (ioaddr + (reg))

enum mac_version {
	RTL_GIGA_MAC_VER_01 = 0,
	RTL_GIGA_MAC_VER_02,
	RTL_GIGA_MAC_VER_03,
	RTL_GIGA_MAC_VER_04,
	RTL_GIGA_MAC_VER_05,
	RTL_GIGA_MAC_VER_06,
	RTL_GIGA_MAC_VER_07,
	RTL_GIGA_MAC_VER_08,
	RTL_GIGA_MAC_VER_09,
	RTL_GIGA_MAC_VER_10,
	RTL_GIGA_MAC_VER_11,
	RTL_GIGA_MAC_VER_12,
	RTL_GIGA_MAC_VER_13,
	RTL_GIGA_MAC_VER_14,
	RTL_GIGA_MAC_VER_15,
	RTL_GIGA_MAC_VER_16,
	RTL_GIGA_MAC_VER_17,
	RTL_GIGA_MAC_VER_18,
	RTL_GIGA_MAC_VER_19,
	RTL_GIGA_MAC_VER_20,
	RTL_GIGA_MAC_VER_21,
	RTL_GIGA_MAC_VER_22,
	RTL_GIGA_MAC_VER_23,
	RTL_GIGA_MAC_VER_24,
	RTL_GIGA_MAC_VER_25,
	RTL_GIGA_MAC_VER_26,
	RTL_GIGA_MAC_VER_27,
	RTL_GIGA_MAC_VER_28,
	RTL_GIGA_MAC_VER_29,
	RTL_GIGA_MAC_VER_30,
	RTL_GIGA_MAC_VER_31,
	RTL_GIGA_MAC_VER_32,
	RTL_GIGA_MAC_VER_33,
	RTL_GIGA_MAC_VER_34,
	RTL_GIGA_MAC_VER_35,
	RTL_GIGA_MAC_VER_36,
	RTL_GIGA_MAC_VER_37,
	RTL_GIGA_MAC_VER_38,
	RTL_GIGA_MAC_VER_39,
	RTL_GIGA_MAC_VER_40,
	RTL_GIGA_MAC_VER_41,
	RTL_GIGA_MAC_VER_42,
	RTL_GIGA_MAC_VER_43,
	RTL_GIGA_MAC_NONE   = 0xff,
};

enum rtl_tx_desc_version {
	RTL_TD_0	= 0,
	RTL_TD_1	= 1,
};

#define JUMBO_1K	ETH_DATA_LEN
#define JUMBO_4K	(4*1024 - ETH_HLEN - 2)
#define JUMBO_6K	(6*1024 - ETH_HLEN - 2)
#define JUMBO_7K	(7*1024 - ETH_HLEN - 2)
#define JUMBO_9K	(9*1024 - ETH_HLEN - 2)

#define _R(NAME,TD,FW,SZ,B) {	\
	.name = NAME,		\
	.txd_version = TD,	\
	.fw_name = FW,		\
	.jumbo_max = SZ,	\
	.jumbo_tx_csum = B	\
}

static const struct {
	const char *name;
	enum rtl_tx_desc_version txd_version;
	const char *fw_name;
	u16 jumbo_max;
	bool jumbo_tx_csum;
} rtl_chip_infos[] = {
	/* PCI devices. */
	[RTL_GIGA_MAC_VER_01] =
		_R("RTL8169",		RTL_TD_0, NULL, JUMBO_7K, true),
	[RTL_GIGA_MAC_VER_02] =
		_R("RTL8169s",		RTL_TD_0, NULL, JUMBO_7K, true),
	[RTL_GIGA_MAC_VER_03] =
		_R("RTL8110s",		RTL_TD_0, NULL, JUMBO_7K, true),
	[RTL_GIGA_MAC_VER_04] =
		_R("RTL8169sb/8110sb",	RTL_TD_0, NULL, JUMBO_7K, true),
	[RTL_GIGA_MAC_VER_05] =
		_R("RTL8169sc/8110sc",	RTL_TD_0, NULL, JUMBO_7K, true),
	[RTL_GIGA_MAC_VER_06] =
		_R("RTL8169sc/8110sc",	RTL_TD_0, NULL, JUMBO_7K, true),
	/* PCI-E devices. */
	[RTL_GIGA_MAC_VER_07] =
		_R("RTL8102e",		RTL_TD_1, NULL, JUMBO_1K, true),
	[RTL_GIGA_MAC_VER_08] =
		_R("RTL8102e",		RTL_TD_1, NULL, JUMBO_1K, true),
	[RTL_GIGA_MAC_VER_09] =
		_R("RTL8102e",		RTL_TD_1, NULL, JUMBO_1K, true),
	[RTL_GIGA_MAC_VER_10] =
		_R("RTL8101e",		RTL_TD_0, NULL, JUMBO_1K, true),
	[RTL_GIGA_MAC_VER_11] =
		_R("RTL8168b/8111b",	RTL_TD_0, NULL, JUMBO_4K, false),
	[RTL_GIGA_MAC_VER_12] =
		_R("RTL8168b/8111b",	RTL_TD_0, NULL, JUMBO_4K, false),
	[RTL_GIGA_MAC_VER_13] =
		_R("RTL8101e",		RTL_TD_0, NULL, JUMBO_1K, true),
	[RTL_GIGA_MAC_VER_14] =
		_R("RTL8100e",		RTL_TD_0, NULL, JUMBO_1K, true),
	[RTL_GIGA_MAC_VER_15] =
		_R("RTL8100e",		RTL_TD_0, NULL, JUMBO_1K, true),
	[RTL_GIGA_MAC_VER_16] =
		_R("RTL8101e",		RTL_TD_0, NULL, JUMBO_1K, true),
	[RTL_GIGA_MAC_VER_17] =
		_R("RTL8168b/8111b",	RTL_TD_1, NULL, JUMBO_4K, false),
	[RTL_GIGA_MAC_VER_18] =
		_R("RTL8168cp/8111cp",	RTL_TD_1, NULL, JUMBO_6K, false),
	[RTL_GIGA_MAC_VER_19] =
		_R("RTL8168c/8111c",	RTL_TD_1, NULL, JUMBO_6K, false),
	[RTL_GIGA_MAC_VER_20] =
		_R("RTL8168c/8111c",	RTL_TD_1, NULL, JUMBO_6K, false),
	[RTL_GIGA_MAC_VER_21] =
		_R("RTL8168c/8111c",	RTL_TD_1, NULL, JUMBO_6K, false),
	[RTL_GIGA_MAC_VER_22] =
		_R("RTL8168c/8111c",	RTL_TD_1, NULL, JUMBO_6K, false),
	[RTL_GIGA_MAC_VER_23] =
		_R("RTL8168cp/8111cp",	RTL_TD_1, NULL, JUMBO_6K, false),
	[RTL_GIGA_MAC_VER_24] =
		_R("RTL8168cp/8111cp",	RTL_TD_1, NULL, JUMBO_6K, false),
	[RTL_GIGA_MAC_VER_25] =
		_R("RTL8168d/8111d",	RTL_TD_1, FIRMWARE_8168D_1,
							JUMBO_9K, false),
	[RTL_GIGA_MAC_VER_26] =
		_R("RTL8168d/8111d",	RTL_TD_1, FIRMWARE_8168D_2,
							JUMBO_9K, false),
	[RTL_GIGA_MAC_VER_27] =
		_R("RTL8168dp/8111dp",	RTL_TD_1, NULL, JUMBO_9K, false),
	[RTL_GIGA_MAC_VER_28] =
		_R("RTL8168dp/8111dp",	RTL_TD_1, NULL, JUMBO_9K, false),
	[RTL_GIGA_MAC_VER_29] =
		_R("RTL8105e",		RTL_TD_1, FIRMWARE_8105E_1,
							JUMBO_1K, true),
	[RTL_GIGA_MAC_VER_30] =
		_R("RTL8105e",		RTL_TD_1, FIRMWARE_8105E_1,
							JUMBO_1K, true),
	[RTL_GIGA_MAC_VER_31] =
		_R("RTL8168dp/8111dp",	RTL_TD_1, NULL, JUMBO_9K, false),
	[RTL_GIGA_MAC_VER_32] =
		_R("RTL8168e/8111e",	RTL_TD_1, FIRMWARE_8168E_1,
							JUMBO_9K, false),
	[RTL_GIGA_MAC_VER_33] =
		_R("RTL8168e/8111e",	RTL_TD_1, FIRMWARE_8168E_2,
							JUMBO_9K, false),
	[RTL_GIGA_MAC_VER_34] =
		_R("RTL8168evl/8111evl",RTL_TD_1, FIRMWARE_8168E_3,
							JUMBO_9K, false),
	[RTL_GIGA_MAC_VER_35] =
		_R("RTL8168f/8111f",	RTL_TD_1, FIRMWARE_8168F_1,
							JUMBO_9K, false),
	[RTL_GIGA_MAC_VER_36] =
		_R("RTL8168f/8111f",	RTL_TD_1, FIRMWARE_8168F_2,
							JUMBO_9K, false),
	[RTL_GIGA_MAC_VER_37] =
		_R("RTL8402",		RTL_TD_1, FIRMWARE_8402_1,
							JUMBO_1K, true),
	[RTL_GIGA_MAC_VER_38] =
		_R("RTL8411",		RTL_TD_1, FIRMWARE_8411_1,
							JUMBO_9K, false),
	[RTL_GIGA_MAC_VER_39] =
		_R("RTL8106e",		RTL_TD_1, FIRMWARE_8106E_1,
							JUMBO_1K, true),
	[RTL_GIGA_MAC_VER_40] =
		_R("RTL8168g/8111g",	RTL_TD_1, FIRMWARE_8168G_2,
							JUMBO_9K, false),
	[RTL_GIGA_MAC_VER_41] =
		_R("RTL8168g/8111g",	RTL_TD_1, NULL, JUMBO_9K, false),
	[RTL_GIGA_MAC_VER_42] =
	//	_R("RTL8168g/8111g",	RTL_TD_1, FIRMWARE_8168G_3,
		_R("RTL8168g/8111g",	RTL_TD_1, NULL,
							JUMBO_9K, false),
	[RTL_GIGA_MAC_VER_43] =
		_R("RTL8106e",		RTL_TD_1, FIRMWARE_8106E_2,
							JUMBO_1K, true),
};
#undef _R

enum cfg_version {
	RTL_CFG_0 = 0x00,
	RTL_CFG_1,
	RTL_CFG_2
};

static const struct of_device_id rtl8169_dt_ids[] = {
	{ .compatible = "Realtek,r8168", },
	{},
};

MODULE_DEVICE_TABLE(of, rtl8169_dt_ids);

static int rx_buf_sz = 16383;
static int use_dac;
static struct {
	u32 msg_enable;
} debug = { -1 };

enum rtl_registers {
	MAC0		= 0,	/* Ethernet hardware address. */
	MAC4		= 4,
	MAR0		= 8,	/* Multicast filter. */
	CounterAddrLow		= 0x10,
	CounterAddrHigh		= 0x14,
	LEDSEL				= 0x18,
	TxDescStartAddrLow	= 0x20,
	TxDescStartAddrHigh	= 0x24,
	TxHDescStartAddrLow	= 0x28,
	TxHDescStartAddrHigh	= 0x2c,
	FLASH		= 0x30,
	ERSR		= 0x36,
	ChipCmd		= 0x37,
	TxPoll		= 0x38,
	IntrMask	= 0x3c,
	IntrStatus	= 0x3e,

	TxConfig	= 0x40,
#define	TXCFG_AUTO_FIFO			(1 << 7)	/* 8111e-vl */
#define	TXCFG_EMPTY			(1 << 11)	/* 8111e-vl */

	RxConfig	= 0x44,
#define	RX128_INT_EN			(1 << 15)	/* 8111c and later */
#define	RX_MULTI_EN			(1 << 14)	/* 8111c only */
#define	RXCFG_FIFO_SHIFT		13
					/* No threshold before first PCI xfer */
#define	RX_FIFO_THRESH			(7 << RXCFG_FIFO_SHIFT)
#define	RX_EARLY_OFF			(1 << 11)
#define	RXCFG_DMA_SHIFT			8
					/* Unlimited maximum PCI burst. */
#define	RX_DMA_BURST			(3 << RXCFG_DMA_SHIFT)	/* 128 bytes */

	RxMissed	= 0x4c,
	Cfg9346		= 0x50,
	Config0		= 0x51,
	Config1		= 0x52,
	Config2		= 0x53,
#define PME_SIGNAL			(1 << 5)	/* 8168c and later */

	Config3		= 0x54,
	Config4		= 0x55,
	Config5		= 0x56,
	MultiIntr	= 0x5c,
	PHYAR		= 0x60,
	PHYstatus	= 0x6c,
	RxMaxSize	= 0xda,
	CPlusCmd	= 0xe0,
	IntrMitigate	= 0xe2,
	RxDescAddrLow	= 0xe4,
	RxDescAddrHigh	= 0xe8,
	EarlyTxThres	= 0xec,	/* 8169. Unit of 32 bytes. */

#define NoEarlyTx	0x3f	/* Max value : no early transmit. */

	MaxTxPacketSize	= 0xec,	/* 8101/8168. Unit of 128 bytes. */

#define TxPacketMax	(8064 >> 7)
#define EarlySize	0x27

	FuncEvent	= 0xf0,
	FuncEventMask	= 0xf4,
	FuncPresetState	= 0xf8,
	FuncForceEvent	= 0xfc,
};

enum rtl8110_registers {
	TBICSR			= 0x64,
	TBI_ANAR		= 0x68,
	TBI_LPAR		= 0x6a,
};

enum rtl8168_8101_registers {
	CSIDR			= 0x64,
	CSIAR			= 0x68,
#define	CSIAR_FLAG			0x80000000
#define	CSIAR_WRITE_CMD			0x80000000
#define	CSIAR_BYTE_ENABLE		0x0f
#define	CSIAR_BYTE_ENABLE_SHIFT		12
#define	CSIAR_ADDR_MASK			0x0fff
#define CSIAR_FUNC_CARD			0x00000000
#define CSIAR_FUNC_SDIO			0x00010000
#define CSIAR_FUNC_NIC			0x00020000
	PMCH			= 0x6f,
	EPHYAR			= 0x80,
#define	EPHYAR_FLAG			0x80000000
#define	EPHYAR_WRITE_CMD		0x80000000
#define	EPHYAR_REG_MASK			0x1f
#define	EPHYAR_REG_SHIFT		16
#define	EPHYAR_DATA_MASK		0xffff
	DLLPR			= 0xd0,
#define	PFM_EN				(1 << 6)
	DBG_REG			= 0xd1,
#define	FIX_NAK_1			(1 << 4)
#define	FIX_NAK_2			(1 << 3)
	TWSI			= 0xd2,
	MCU			= 0xd3,
#define	NOW_IS_OOB			(1 << 7)
#define	TX_EMPTY			(1 << 5)
#define	RX_EMPTY			(1 << 4)
#define	RXTX_EMPTY			(TX_EMPTY | RX_EMPTY)
#define	EN_NDP				(1 << 3)
#define	EN_OOB_RESET			(1 << 2)
#define	LINK_LIST_RDY			(1 << 1)
#define	DIS_MCU_CLROOB			(1 << 0)
	EFUSEAR			= 0xdc,
#define	EFUSEAR_FLAG			0x80000000
#define	EFUSEAR_WRITE_CMD		0x80000000
#define	EFUSEAR_READ_CMD		0x00000000
#define	EFUSEAR_REG_MASK		0x03ff
#define	EFUSEAR_REG_SHIFT		8
#define	EFUSEAR_DATA_MASK		0xff
};

enum rtl8168_registers {
	LED_FREQ		= 0x1a,
	EEE_LED			= 0x1b,
	ERIDR			= 0x70,
	ERIAR			= 0x74,
#define ERIAR_FLAG			0x80000000
#define ERIAR_WRITE_CMD			0x80000000
#define ERIAR_READ_CMD			0x00000000
#define ERIAR_ADDR_BYTE_ALIGN		4
#define ERIAR_TYPE_SHIFT		16
#define ERIAR_EXGMAC			(0x00 << ERIAR_TYPE_SHIFT)
#define ERIAR_MSIX			(0x01 << ERIAR_TYPE_SHIFT)
#define ERIAR_ASF			(0x02 << ERIAR_TYPE_SHIFT)
#define ERIAR_MASK_SHIFT		12
#define ERIAR_MASK_0001			(0x1 << ERIAR_MASK_SHIFT)
#define ERIAR_MASK_0011			(0x3 << ERIAR_MASK_SHIFT)
#define ERIAR_MASK_0101			(0x5 << ERIAR_MASK_SHIFT)
#define ERIAR_MASK_1111			(0xf << ERIAR_MASK_SHIFT)
	EPHY_RXER_NUM		= 0x7c,
	OCPDR			= 0xb0,	/* OCP GPHY access */
#define OCPDR_WRITE_CMD			0x80000000
#define OCPDR_READ_CMD			0x00000000
#define OCPDR_REG_MASK			0x7f
#define OCPDR_GPHY_REG_SHIFT		16
#define OCPDR_DATA_MASK			0xffff
	OCPAR			= 0xb4,
#define OCPAR_FLAG			0x80000000
#define OCPAR_GPHY_WRITE_CMD		0x8000f060
#define OCPAR_GPHY_READ_CMD		0x0000f060
	GPHY_OCP		= 0xb8,
	RDSAR1			= 0xd0,	/* 8168c only. Undocumented on 8168dp */
	MISC			= 0xf0,	/* 8168e only. */
#define TXPLA_RST			(1 << 29)
#define DISABLE_LAN_EN			(1 << 23) /* Enable GPIO pin */
#define PWM_EN				(1 << 22)
#define RXDV_GATED_EN			(1 << 19)
#define EARLY_TALLY_EN			(1 << 16)
};

#if defined(RTL_TX_NO_CLOSE)
enum rtl8169soc_registers {
	TX_DESC_TAIL_IDX	= 0x20,	/* the last descriptor index */
	TX_DESC_CLOSE_IDX	= 0x22,	/* the closed descriptor index */
#define TX_DESC_CNT_MASK		0x3FFF
#define TX_DESC_CNT_SIZE		0x4000
};
#endif /* RTL_TX_NO_CLOSE */

enum rtl_register_content {
	/* InterruptStatusBits */
	SYSErr		= 0x8000,
	PCSTimeout	= 0x4000,
	SWInt		= 0x0100,
	TxDescUnavail	= 0x0080,
	RxFIFOOver	= 0x0040,
	LinkChg		= 0x0020,
	RxOverflow	= 0x0010,
	TxErr		= 0x0008,
	TxOK		= 0x0004,
	RxErr		= 0x0002,
	RxOK		= 0x0001,

	/* RxStatusDesc */
	RxBOVF	= (1 << 24),
	RxFOVF	= (1 << 23),
	RxRWT	= (1 << 22),
	RxRES	= (1 << 21),
	RxRUNT	= (1 << 20),
	RxCRC	= (1 << 19),

	/* ChipCmdBits */
	StopReq		= 0x80,
	CmdReset	= 0x10,
	CmdRxEnb	= 0x08,
	CmdTxEnb	= 0x04,
	RxBufEmpty	= 0x01,

	/* TXPoll register p.5 */
	HPQ		= 0x80,		/* Poll cmd on the high prio queue */
	NPQ		= 0x40,		/* Poll cmd on the low prio queue */
	FSWInt		= 0x01,		/* Forced software interrupt */

	/* Cfg9346Bits */
	Cfg9346_Lock	= 0x00,
	Cfg9346_Unlock	= 0xc0,

	/* rx_mode_bits */
	AcceptErr	= 0x20,
	AcceptRunt	= 0x10,
	AcceptBroadcast	= 0x08,
	AcceptMulticast	= 0x04,
	AcceptMyPhys	= 0x02,
	AcceptAllPhys	= 0x01,
#define RX_CONFIG_ACCEPT_MASK		0x3f

	/* TxConfigBits */
	TxInterFrameGapShift = 24,
	TxDMAShift = 8,	/* DMA burst value (0-7) is shift this many bits */

	/* Config1 register p.24 */
	LEDS1		= (1 << 7),
	LEDS0		= (1 << 6),
	Speed_down	= (1 << 4),
	MEMMAP		= (1 << 3),
	IOMAP		= (1 << 2),
	VPD		= (1 << 1),
	PMEnable	= (1 << 0),	/* Power Management Enable */

	/* Config2 register p. 25 */
	ClkReqEn	= (1 << 7),	/* Clock Request Enable */
	MSIEnable	= (1 << 5),	/* 8169 only. Reserved in the 8168. */
	PCI_Clock_66MHz = 0x01,
	PCI_Clock_33MHz = 0x00,

	/* Config3 register p.25 */
	MagicPacket	= (1 << 5),	/* Wake up when receives a Magic Packet */
	LinkUp		= (1 << 4),	/* Wake up when the cable connection is re-established */
	Jumbo_En0	= (1 << 2),	/* 8168 only. Reserved in the 8168b */
	Beacon_en	= (1 << 0),	/* 8168 only. Reserved in the 8168b */

	/* Config4 register */
	Jumbo_En1	= (1 << 1),	/* 8168 only. Reserved in the 8168b */

	/* Config5 register p.27 */
	BWF		= (1 << 6),	/* Accept Broadcast wakeup frame */
	MWF		= (1 << 5),	/* Accept Multicast wakeup frame */
	UWF		= (1 << 4),	/* Accept Unicast wakeup frame */
	Spi_en		= (1 << 3),
	LanWake		= (1 << 1),	/* LanWake enable/disable */
	PMEStatus	= (1 << 0),	/* PME status can be reset by PCI RST# */
	ASPM_en		= (1 << 0),	/* ASPM enable */

	/* TBICSR p.28 */
	TBIReset	= 0x80000000,
	TBILoopback	= 0x40000000,
	TBINwEnable	= 0x20000000,
	TBINwRestart	= 0x10000000,
	TBILinkOk	= 0x02000000,
	TBINwComplete	= 0x01000000,

	/* CPlusCmd p.31 */
	EnableBist	= (1 << 15),	// 8168 8101
	Mac_dbgo_oe	= (1 << 14),	// 8168 8101
	Normal_mode	= (1 << 13),	// unused
	Force_half_dup	= (1 << 12),	// 8168 8101
	Force_rxflow_en	= (1 << 11),	// 8168 8101
	Force_txflow_en	= (1 << 10),	// 8168 8101
	Cxpl_dbg_sel	= (1 << 9),	// 8168 8101
	ASF		= (1 << 8),	// 8168 8101
	PktCntrDisable	= (1 << 7),	// 8168 8101
	Mac_dbgo_sel	= 0x001c,	// 8168
	RxVlan		= (1 << 6),
	RxChkSum	= (1 << 5),
	PCIDAC		= (1 << 4),
	PCIMulRW	= (1 << 3),
	INTT_0		= 0x0000,	// 8168
	INTT_1		= 0x0001,	// 8168
	INTT_2		= 0x0002,	// 8168
	INTT_3		= 0x0003,	// 8168

	/* rtl8169_PHYstatus */
	TBI_Enable	= 0x80,
	TxFlowCtrl	= 0x40,
	RxFlowCtrl	= 0x20,
	_1000bpsF	= 0x10,
	_100bps		= 0x08,
	_10bps		= 0x04,
	LinkStatus	= 0x02,
	FullDup		= 0x01,

	/* _TBICSRBit */
	TBILinkOK	= 0x02000000,

	/* DumpCounterCommand */
	CounterDump	= 0x8,
};

enum rtl_desc_bit {
	/* First doubleword. */
	DescOwn		= (1 << 31), /* Descriptor is owned by NIC */
	RingEnd		= (1 << 30), /* End of descriptor ring */
	FirstFrag	= (1 << 29), /* First segment of a packet */
	LastFrag	= (1 << 28), /* Final segment of a packet */
};

/* Generic case. */
enum rtl_tx_desc_bit {
	/* First doubleword. */
	TD_LSO		= (1 << 27),		/* Large Send Offload */
#define TD_MSS_MAX			0x07ffu	/* MSS value */

	/* Second doubleword. */
	TxVlanTag	= (1 << 17),		/* Add VLAN tag */
};

/* 8169, 8168b and 810x except 8102e. */
enum rtl_tx_desc_bit_0 {
	/* First doubleword. */
#define TD0_MSS_SHIFT			16	/* MSS position (11 bits) */
	TD0_TCP_CS	= (1 << 16),		/* Calculate TCP/IP checksum */
	TD0_UDP_CS	= (1 << 17),		/* Calculate UDP/IP checksum */
	TD0_IP_CS	= (1 << 18),		/* Calculate IP checksum */
};

/* 8102e, 8168c and beyond. */
enum rtl_tx_desc_bit_1 {
	/* Second doubleword. */
#define TD1_MSS_SHIFT			18	/* MSS position (11 bits) */
	TD1_IP_CS	= (1 << 29),		/* Calculate IP checksum */
	TD1_TCP_CS	= (1 << 30),		/* Calculate TCP/IP checksum */
	TD1_UDP_CS	= (1 << 31),		/* Calculate UDP/IP checksum */
};

static const struct rtl_tx_desc_info {
	struct {
		u32 udp;
		u32 tcp;
	} checksum;
	u16 mss_shift;
	u16 opts_offset;
} tx_desc_info [] = {
	[RTL_TD_0] = {
		.checksum = {
			.udp	= TD0_IP_CS | TD0_UDP_CS,
			.tcp	= TD0_IP_CS | TD0_TCP_CS
		},
		.mss_shift	= TD0_MSS_SHIFT,
		.opts_offset	= 0
	},
	[RTL_TD_1] = {
		.checksum = {
			.udp	= TD1_IP_CS | TD1_UDP_CS,
			.tcp	= TD1_IP_CS | TD1_TCP_CS
		},
		.mss_shift	= TD1_MSS_SHIFT,
		.opts_offset	= 1
	}
};

enum rtl_rx_desc_bit {
	/* Rx private */
	PID1		= (1 << 18), /* Protocol ID bit 1/2 */
	PID0		= (1 << 17), /* Protocol ID bit 2/2 */

#define RxProtoUDP	(PID1)
#define RxProtoTCP	(PID0)
#define RxProtoIP	(PID1 | PID0)
#define RxProtoMask	RxProtoIP

	IPFail		= (1 << 16), /* IP checksum failed */
	UDPFail		= (1 << 15), /* UDP/IP checksum failed */
	TCPFail		= (1 << 14), /* TCP/IP checksum failed */
	RxVlanTag	= (1 << 16), /* VLAN tag available */
};

#define RsvdMask	0x3fffc000

struct TxDesc {
	__le32 opts1;
	__le32 opts2;
	__le64 addr;
};

struct RxDesc {
	__le32 opts1;
	__le32 opts2;
	__le64 addr;
};

struct ring_info {
	struct sk_buff	*skb;
	u32		len;
	u8		__pad[sizeof(void *) - sizeof(u32)];
};

enum features {
	RTL_FEATURE_WOL		= (1 << 0),
	RTL_FEATURE_MSI		= (1 << 1),
	RTL_FEATURE_GMII	= (1 << 2),
};

struct rtl8169_counters {
	__le64	tx_packets;
	__le64	rx_packets;
	__le64	tx_errors;
	__le32	rx_errors;
	__le16	rx_missed;
	__le16	align_errors;
	__le32	tx_one_collision;
	__le32	tx_multi_collision;
	__le64	rx_unicast;
	__le64	rx_broadcast;
	__le32	rx_multicast;
	__le16	tx_aborted;
	__le16	tx_underun;
};

enum rtl_flag {
	RTL_FLAG_TASK_ENABLED,
	RTL_FLAG_TASK_SLOW_PENDING,
	RTL_FLAG_TASK_RESET_PENDING,
	RTL_FLAG_TASK_PHY_PENDING,
	RTL_FLAG_MAX
};

struct rtl8169_stats {
	u64			packets;
	u64			bytes;
	struct u64_stats_sync	syncp;
};

#define RGMII0_PAD_CTRL_ADDR	0x9801a960
#define ISO_RGMII_MDIO_TO_GMAC	0x98007064

enum rtl_output_mode {
	OUTPUT_EMBEDDED_PHY,
	#if defined(CONFIG_ARCH_RTD129x)
	OUTPUT_RGMII_TO_MAC,
	OUTPUT_RGMII_TO_PHY,
	#elif defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
	OUTPUT_SGMII_TO_MAC,
	OUTPUT_SGMII_TO_PHY,
	#endif /* CONFIG_ARCH_RTD129x | CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */
	OUTPUT_MAX
};

/* ISO base addr 0x98007000 */
enum iso_registers {
	ISO_UMSK_ISR	= 0x0004,
	ISO_POWERCUT_ETN = 0x005c,
	ISO_ETN_TESTIO	= 0x0060,
	ISO_SOFT_RESET = 0x0088,
	ISO_CLOCK_ENABLE = 0x008c,
};

#if defined(CONFIG_ARCH_RTD129x)
enum rtl_rgmii_voltage {
	VOLTAGE_1_DOT_8V = 1,
	VOLTAGE_2_DOT_5V,
	VOLTAGE_3_DOT_3V,
	VOLTAGE_MAX
};

enum rtl_rgmii_delay {
	RGMII_DELAY_0NS,
	RGMII_DELAY_2NS,
	RGMII_DELAY_MAX
};
#elif defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
enum phy_addr_e {
	INT_PHY_ADDR = 1,	/* embedded PHY PHY ID */
	SERDES_DPHY_0 = 0,	/* embedded SerDes DPHY PHY ID 0, RL6481_T28_SGMII.doc ANA00~ANA0F */
	SERDES_DPHY_1 = 1,	/* embedded SerDes DPHY PHY ID 1, RL6481_T28_SGMII.doc ANA20~ANA2F */
	EXT_PHY_ADDR = 3,	/* external RTL8211FS SGMII PHY ID */
};

/* SDS base addr 0x981c8000 */
#if defined(CONFIG_ARCH_RTD139x)
enum sds_registers {
	SDS_REG02 	= 0x0008,
	SDS_REG28 	= 0x0070,
	SDS_REG29 	= 0x0074,
	SDS_MISC	= 0x1804,
	SDS_LINK	= 0x1810,
};
#elif defined(CONFIG_ARCH_RTD16xx)
enum sds_registers {
	SDS_REG02 	= 0x0008,
	SDS_MISC	= 0x1804,
	SDS_LINK	= 0x180c,
	SDS_DEBUG	= 0x1810,
};
#endif

/* ISO testmux base addr 0x9804e000 */
enum testmux_registers {
	ISO_TESTMUX_MUXPAD0 	= 0x0000,
	ISO_TESTMUX_MUXPAD1 	= 0x0004,
	ISO_TESTMUX_MUXPAD2 	= 0x0008,
};

#if defined(CONFIG_ARCH_RTD16xx)
enum sgmii_swing_e {
	TX_Swing_550mV,
	TX_Swing_380mV,
	TX_Swing_250mV,
	TX_Swing_190mV
};
#else
#define SGMII_SWING		(0X3 << 8)
#define TX_SWING_1040MV		(0X0 << 8)	/* DEFAULT */
#define TX_SWING_693MV		(0X1 << 8)
#define TX_SWING_474MV		(0X2 << 8)
#define TX_SWING_352MV		(0X3 << 8)
#define TX_SWING_312MV		(0X4 << 8)
#endif /* CONFIG_ARCH_RTD16xx */

/* SBX and SC_WRAP base addr 0x9801c000 */
enum sbx_sc_wrap_registers {
	SBX_SB3_CHANNEL_REQ_MASK	= 0x020c,
	SBX_SB3_CHANNEL_REQ_BUSY	= 0x0210,
	SBX_ACP_CHANNEL_REQ_MASK	= 0x080c,
	SBX_ACP_CHANNEL_REQ_BUSY	= 0x0810,
	SBX_ACP_MISC_CTRL		= 0x0814,
	SC_WRAP_ACP_CRT_CTRL		= 0x1030,
	SC_WRAP_CRT_CTRL		= 0x1100,
	SC_WRAP_INTERFACE_EN		= 0x1124,
	SC_WRAP_ACP_CTRL		= 0x1800,
};
#endif /* CONFIG_ARCH_RTD129x | CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */

#ifdef RTL_PROC
static struct proc_dir_entry *rtw_proc;
static u8 wol_enable=0;
#endif

struct rtl8169_private {
	void __iomem *mmio_addr;	/* memory map physical address */
	void __iomem *mmio_clkaddr;
	struct platform_device *pdev;
//	struct device *device;
	struct net_device *dev;
	struct napi_struct napi;
	u32 msg_enable;
	u16 txd_version;
	u16 mac_version;
	u32 cur_rx; /* Index into the Rx descriptor buffer of next Rx pkt. */
	u32 cur_tx; /* Index into the Tx descriptor buffer of next Rx pkt. */
	u32 dirty_tx;
	struct rtl8169_stats rx_stats;
	struct rtl8169_stats tx_stats;
	struct TxDesc *TxDescArray;	/* 256-aligned Tx descriptor ring */
	struct RxDesc *RxDescArray;	/* 256-aligned Rx descriptor ring */
	dma_addr_t TxPhyAddr;
	dma_addr_t RxPhyAddr;
	void *Rx_databuff[NUM_RX_DESC];	/* Rx data buffers */
	struct ring_info tx_skb[NUM_TX_DESC];	/* Tx data buffers */
	struct timer_list timer;
	u16 cp_cmd;

	u16 event_slow;

#ifdef RTL_PROC
	struct proc_dir_entry *dir_dev;
#endif

	struct mdio_ops {
		void (*write)(struct rtl8169_private *, int, int);
		int (*read)(struct rtl8169_private *, int);
	} mdio_ops;

	struct pll_power_ops {
		void (*down)(struct rtl8169_private *);
		void (*up)(struct rtl8169_private *);
	} pll_power_ops;

	struct jumbo_ops {
		void (*enable)(struct rtl8169_private *);
		void (*disable)(struct rtl8169_private *);
	} jumbo_ops;

	struct csi_ops {
		void (*write)(struct rtl8169_private *, int, int);
		u32 (*read)(struct rtl8169_private *, int);
	} csi_ops;

	int (*set_speed)(struct net_device *, u8 aneg, u16 sp, u8 dpx, u32 adv);
	int (*get_settings)(struct net_device *, struct ethtool_cmd *);
	void (*phy_reset_enable)(struct rtl8169_private *tp);
	void (*hw_start)(struct net_device *);
	unsigned int (*phy_reset_pending)(struct rtl8169_private *tp);
	unsigned int (*link_ok)(void __iomem *);
	int (*do_ioctl)(struct rtl8169_private *tp, struct mii_ioctl_data *data, int cmd);

	struct {
		DECLARE_BITMAP(flags, RTL_FLAG_MAX);
		struct mutex mutex;
		struct work_struct work;
	} wk;

	unsigned features;

	struct mii_if_info mii;
	struct rtl8169_counters counters;
	u32 saved_wolopts;
	u32 opts1_mask;

	struct rtl_fw {
		const struct firmware *fw;

#define RTL_VER_SIZE		32

		char version[RTL_VER_SIZE];

		struct rtl_fw_phy_action {
			__le32 *code;
			size_t size;
		} phy_action;
	} *rtl_fw;
#define RTL_FIRMWARE_UNKNOWN	ERR_PTR(-EAGAIN)

	u32 ocp_base;

	/* For link status change. */
	struct task_struct *kthr;
	wait_queue_head_t thr_wait;
	int link_chg;

	#if defined(CONFIG_ARCH_RTD129x)
	/* RGMII */
	u8 output_mode; /* 0:embedded PHY, 1:RGMII to MAC, 2:RGMII to PHY */
	u8 rgmii_voltage; /* 1:1.8V, 2: 2.5V, 3:3.3V */
	u8 rgmii_tx_delay; /* 0: 0ns, 1: 2ns */
	u8 rgmii_rx_delay; /* 0: 0ns, 1: 2ns */
	#elif defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
	void __iomem *mmio_sbxaddr;
	void __iomem *mmio_otpaddr;
	void __iomem *mmio_sdsaddr;
	void __iomem *mmio_pinmuxaddr;

	/* SGMII */
	u8 output_mode; /* 0:embedded PHY, 1:SGMII to MAC, 2:SGMII to PHY */
	#if defined(CONFIG_ARCH_RTD16xx)
	u8 sgmii_swing; /* 0:640mV, 1:380mV, 2:250mV, 3:190mV */
	#endif /* CONFIG_ARCH_RTD16xx */

	bool bypass_enable; /* 0: disable, 1: enable */
	#endif /* CONFIG_ARCH_RTD129x | CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */
	u8 ext_phy_id; /* 0 ~ 31 */
	bool eee_enable; /* 0: disable, 1: enable */
	bool acp_enable; /* 0: disable, 1: enable */
	bool ext_phy;
};

MODULE_AUTHOR("Realtek and the Linux r8169 crew <netdev@vger.kernel.org>");
MODULE_DESCRIPTION("RealTek RTL-8169 Gigabit Ethernet driver");
module_param(use_dac, int, 0);
MODULE_PARM_DESC(use_dac, "Enable PCI DAC. Unsafe on 32 bit PCI slot.");
module_param_named(debug, debug.msg_enable, int, 0);
MODULE_PARM_DESC(debug, "Debug verbosity level (0=none, ..., 16=all)");
MODULE_LICENSE("GPL");
MODULE_VERSION(RTL8169_VERSION);
MODULE_FIRMWARE(FIRMWARE_8168D_1);
MODULE_FIRMWARE(FIRMWARE_8168D_2);
MODULE_FIRMWARE(FIRMWARE_8168E_1);
MODULE_FIRMWARE(FIRMWARE_8168E_2);
MODULE_FIRMWARE(FIRMWARE_8168E_3);
MODULE_FIRMWARE(FIRMWARE_8105E_1);
MODULE_FIRMWARE(FIRMWARE_8168F_1);
MODULE_FIRMWARE(FIRMWARE_8168F_2);
MODULE_FIRMWARE(FIRMWARE_8402_1);
MODULE_FIRMWARE(FIRMWARE_8411_1);
MODULE_FIRMWARE(FIRMWARE_8106E_1);
MODULE_FIRMWARE(FIRMWARE_8106E_2);
MODULE_FIRMWARE(FIRMWARE_8168G_2);
MODULE_FIRMWARE(FIRMWARE_8168G_3);

static void rtl_lock_work(struct rtl8169_private *tp)
{
	mutex_lock(&tp->wk.mutex);
}

static void rtl_unlock_work(struct rtl8169_private *tp)
{
	mutex_unlock(&tp->wk.mutex);
}

static void rtl_tx_performance_tweak(struct platform_device *pdev, u16 force)
{
//	pcie_capability_clear_and_set_word(pdev, PCI_EXP_DEVCTL,
//					   PCI_EXP_DEVCTL_READRQ, force);
}

struct rtl_cond {
	bool (*check)(struct rtl8169_private *);
	const char *msg;
};

static void rtl_udelay(unsigned int d)
{
	udelay(d);
}

static bool rtl_loop_wait(struct rtl8169_private *tp, const struct rtl_cond *c,
			  void (*delay)(unsigned int), unsigned int d, int n,
			  bool high)
{
	int i;

	for (i = 0; i < n; i++) {
		delay(d);
		if (c->check(tp) == high)
			return true;
	}
	netif_err(tp, drv, tp->dev, "%s == %d (loop: %d, delay: %d).\n",
		  c->msg, !high, n, d);
	return false;
}

static bool rtl_udelay_loop_wait_high(struct rtl8169_private *tp,
					  const struct rtl_cond *c,
					  unsigned int d, int n)
{
	return rtl_loop_wait(tp, c, rtl_udelay, d, n, true);
}

static bool rtl_udelay_loop_wait_low(struct rtl8169_private *tp,
					 const struct rtl_cond *c,
					 unsigned int d, int n)
{
	return rtl_loop_wait(tp, c, rtl_udelay, d, n, false);
}

static bool rtl_msleep_loop_wait_high(struct rtl8169_private *tp,
					  const struct rtl_cond *c,
					  unsigned int d, int n)
{
	return rtl_loop_wait(tp, c, msleep, d, n, true);
}

static bool rtl_msleep_loop_wait_low(struct rtl8169_private *tp,
					 const struct rtl_cond *c,
					 unsigned int d, int n)
{
	return rtl_loop_wait(tp, c, msleep, d, n, false);
}

#define DECLARE_RTL_COND(name)				\
static bool name ## _check(struct rtl8169_private *);	\
							\
static const struct rtl_cond name = {			\
	.check	= name ## _check,			\
	.msg	= #name					\
};							\
							\
static bool name ## _check(struct rtl8169_private *tp)

DECLARE_RTL_COND(rtl_ocpar_cond)
{
	void __iomem *ioaddr = tp->mmio_addr;

	return RTL_R32(OCPAR) & OCPAR_FLAG;
}

static u32 ocp_read(struct rtl8169_private *tp, u8 mask, u16 reg)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W32(OCPAR, ((u32)mask & 0x0f) << 12 | (reg & 0x0fff));

	return rtl_udelay_loop_wait_high(tp, &rtl_ocpar_cond, 100, 20) ?
		RTL_R32(OCPDR) : ~0;
}

static void ocp_write(struct rtl8169_private *tp, u8 mask, u16 reg, u32 data)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W32(OCPDR, data);
	RTL_W32(OCPAR, OCPAR_FLAG | ((u32)mask & 0x0f) << 12 | (reg & 0x0fff));

	rtl_udelay_loop_wait_low(tp, &rtl_ocpar_cond, 100, 20);
}

DECLARE_RTL_COND(rtl_eriar_cond)
{
	void __iomem *ioaddr = tp->mmio_addr;

	return RTL_R32(ERIAR) & ERIAR_FLAG;
}

static void rtl8168_oob_notify(struct rtl8169_private *tp, u8 cmd)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W8(ERIDR, cmd);
	RTL_W32(ERIAR, 0x800010e8);
	msleep(2);

	if (!rtl_udelay_loop_wait_low(tp, &rtl_eriar_cond, 100, 5))
		return;

	ocp_write(tp, 0x1, 0x30, 0x00000001);
}

#define OOB_CMD_RESET		0x00
#define OOB_CMD_DRIVER_START	0x05
#define OOB_CMD_DRIVER_STOP	0x06

static u16 rtl8168_get_ocp_reg(struct rtl8169_private *tp)
{
	return (tp->mac_version == RTL_GIGA_MAC_VER_31) ? 0xb8 : 0x10;
}

DECLARE_RTL_COND(rtl_ocp_read_cond)
{
	u16 reg;

	reg = rtl8168_get_ocp_reg(tp);

	return ocp_read(tp, 0x0f, reg) & 0x00000800;
}

static void rtl8168_driver_start(struct rtl8169_private *tp)
{
	rtl8168_oob_notify(tp, OOB_CMD_DRIVER_START);

	rtl_msleep_loop_wait_high(tp, &rtl_ocp_read_cond, 10, 10);
}

static void rtl8168_driver_stop(struct rtl8169_private *tp)
{
	rtl8168_oob_notify(tp, OOB_CMD_DRIVER_STOP);

	rtl_msleep_loop_wait_low(tp, &rtl_ocp_read_cond, 10, 10);
}

static int r8168dp_check_dash(struct rtl8169_private *tp)
{
	u16 reg = rtl8168_get_ocp_reg(tp);

	return (ocp_read(tp, 0x0f, reg) & 0x00008000) ? 1 : 0;
}

static bool rtl_ocp_reg_failure(struct rtl8169_private *tp, u32 reg)
{
	if (reg & 0xffff0001) {
		netif_err(tp, drv, tp->dev, "Invalid ocp reg %x!\n", reg);
		return true;
	}
	return false;
}

DECLARE_RTL_COND(rtl_ocp_gphy_cond)
{
	void __iomem *ioaddr = tp->mmio_addr;

	return RTL_R32(GPHY_OCP) & OCPAR_FLAG;
}

static void r8168_phy_ocp_write(struct rtl8169_private *tp, u32 reg, u32 data)
{
	void __iomem *ioaddr = tp->mmio_addr;

	if (rtl_ocp_reg_failure(tp, reg))
		return;

	RTL_W32(GPHY_OCP, OCPAR_FLAG | (reg << 15) | data);

	rtl_udelay_loop_wait_low(tp, &rtl_ocp_gphy_cond, 25, 10);
}

static u16 r8168_phy_ocp_read(struct rtl8169_private *tp, u32 reg)
{
	void __iomem *ioaddr = tp->mmio_addr;

	if (rtl_ocp_reg_failure(tp, reg))
		return 0;

	RTL_W32(GPHY_OCP, reg << 15);

	return rtl_udelay_loop_wait_high(tp, &rtl_ocp_gphy_cond, 25, 10) ?
		(RTL_R32(GPHY_OCP) & 0xffff) : ~0;
}

static void r8168_mac_ocp_write(struct rtl8169_private *tp, u32 reg, u32 data)
{
	void __iomem *ioaddr = tp->mmio_addr;

	if (rtl_ocp_reg_failure(tp, reg))
		return;

	RTL_W32(OCPDR, OCPAR_FLAG | (reg << 15) | data);
}

static u16 r8168_mac_ocp_read(struct rtl8169_private *tp, u32 reg)
{
	void __iomem *ioaddr = tp->mmio_addr;

	if (rtl_ocp_reg_failure(tp, reg))
		return 0;

	RTL_W32(OCPDR, reg << 15);

	return RTL_R32(OCPDR);
}

void r8169soc_ocp_reg_write(struct rtl8169_private *tp,
				unsigned int reg_addr,
				unsigned int value)
{
	void __iomem *ioaddr = tp->mmio_addr;
	unsigned int wdata;

	// write value to reg
	wdata = (0x1 << 31) | (((reg_addr & 0xffff) >> 1) << 16) |
		(value & 0xffff);
	RTL_W32(OCPDR, wdata);
}

unsigned int r8169soc_ocp_reg_read(struct rtl8169_private *tp,
				unsigned int reg_addr)
{
	void __iomem *ioaddr = tp->mmio_addr;
	unsigned int wdata;
	unsigned int rdata;

	// write value to reg
	wdata = (0x0 << 31) | (((reg_addr & 0xffff) >> 1) << 16);
	RTL_W32(OCPDR, wdata);
	rdata = RTL_R32(OCPDR);
	return(rdata & 0xffff);
}

#define OCP_STD_PHY_BASE	0xa400

static __maybe_unused void r8168g_mdio_write(struct rtl8169_private *tp, int reg, int value)
{
	if (reg == 0x1f) {
		tp->ocp_base = value ? value << 4 : OCP_STD_PHY_BASE;
		return;
	}

	if (tp->ocp_base != OCP_STD_PHY_BASE)
		reg -= 0x10;

	r8168_phy_ocp_write(tp, tp->ocp_base + reg * 2, value);
}

static __maybe_unused int r8168g_mdio_read(struct rtl8169_private *tp, int reg)
{
	if (tp->ocp_base != OCP_STD_PHY_BASE)
		reg -= 0x10;

	return r8168_phy_ocp_read(tp, tp->ocp_base + reg * 2);
}

static __maybe_unused void mac_mcu_write(struct rtl8169_private *tp, int reg, int value)
{
	if (reg == 0x1f) {
		tp->ocp_base = value << 4;
		return;
	}

	r8168_mac_ocp_write(tp, tp->ocp_base + reg, value);
}

static __maybe_unused int mac_mcu_read(struct rtl8169_private *tp, int reg)
{
	return r8168_mac_ocp_read(tp, tp->ocp_base + reg);
}

DECLARE_RTL_COND(rtl_phyar_cond)
{
	void __iomem *ioaddr = tp->mmio_addr;

	return RTL_R32(PHYAR) & 0x80000000;
}

static void rtl_ephy_write(struct rtl8169_private *tp, int reg_addr, int value);
static u16 rtl_ephy_read(struct rtl8169_private *tp, int reg_addr);

static void r8169_mdio_write(struct rtl8169_private *tp, int reg, int value)
{
	void __iomem *ioaddr = tp->mmio_addr;

	if (tp->ext_phy) {
		rtl_ephy_write(tp, reg, value);
		return;
	}
	RTL_W32(PHYAR, 0x80000000 | (reg & 0x1f) << 16 | (value & 0xffff));

	rtl_udelay_loop_wait_low(tp, &rtl_phyar_cond, 25, 20);
	/*
	 * According to hardware specs a 20us delay is required after write
	 * complete indication, but before sending next command.
	 */
	udelay(20);
}

static int r8169_mdio_read(struct rtl8169_private *tp, int reg)
{
	void __iomem *ioaddr = tp->mmio_addr;
	int value;

	if (tp->ext_phy) {
		return rtl_ephy_read(tp, reg);
	}

	RTL_W32(PHYAR, 0x0 | (reg & 0x1f) << 16);

	value = rtl_udelay_loop_wait_high(tp, &rtl_phyar_cond, 25, 20) ?
		RTL_R32(PHYAR) & 0xffff : ~0;

	/*
	 * According to hardware specs a 20us delay is required after read
	 * complete indication, but before sending next command.
	 */
	udelay(20);

	return value;
}

#if defined(CONFIG_ARCH_RTD129x)
#define MDIO_LOCK							\
do {									\
	/* disable interrupt from PHY to MCU */				\
	r8169soc_ocp_reg_write(tp, 0xfc1e,				\
		r8169soc_ocp_reg_read(tp, 0xfc1e) &			\
					~(BIT(1) | BIT(11) | BIT(12)));	\
} while (0)
#define MDIO_UNLOCK							\
do {									\
	u32 tmp;							\
	/* enable interrupt from PHY to MCU */				\
	tmp = r8169soc_ocp_reg_read(tp, 0xfc1e);			\
	if (tp->output_mode == OUTPUT_RGMII_TO_MAC)			\
		tmp |= (BIT(11) | BIT(12)); /* ignore BIT(1):mac_intr*/	\
	else								\
		tmp |= (BIT(1) | BIT(11) | BIT(12));			\
	r8169soc_ocp_reg_write(tp, 0xfc1e, tmp);			\
} while (0)
#elif defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
#define MDIO_WAIT_TIMEOUT	100
#define MDIO_LOCK							\
do {									\
	u32 wait_cnt = 0;						\
									\
	/* disable timer 2 */						\
	r8169soc_ocp_reg_write(tp, 0xE404,				\
		(r8169soc_ocp_reg_read(tp, 0xE404) & 			\
		~(BIT(12) | BIT(11) | BIT(8))) | (BIT(12)));		\
	/* wait MDIO channel is free */					\
	while (0 != (BIT(0) & r8169soc_ocp_reg_read(tp, 0xDE4E))) {	\
		wait_cnt++;						\
		udelay(1);						\
		if (wait_cnt > MDIO_WAIT_TIMEOUT)			\
			break;						\
	}								\
	while (wait_cnt <= MDIO_WAIT_TIMEOUT) {				\
		/* enter driver mode */					\
		r8169soc_ocp_reg_write(tp, 0xDE42,			\
			r8169soc_ocp_reg_read(tp, 0xDE42) | BIT(0));	\
		/* check if MDIO channel is still free */		\
		if (0 == (BIT(0) & r8169soc_ocp_reg_read(tp, 0xDE4E))) {\
			/* lock successfully */				\
			break;						\
		} else {						\
			/* exit driver mode */				\
			r8169soc_ocp_reg_write(tp, 0xDE42,		\
				r8169soc_ocp_reg_read(tp, 0xDE42) & 	\
							~BIT(0));	\
			wait_cnt++;					\
			udelay(1);					\
		}							\
	}								\
	if (wait_cnt > MDIO_WAIT_TIMEOUT) {				\
		/* enable timer 2 */					\
		r8169soc_ocp_reg_write(tp, 0xE404,			\
			(r8169soc_ocp_reg_read(tp, 0xE404) | 		\
			BIT(12) | BIT(11) | BIT(8)));			\
		pr_err("%s:%d: MDIO lock failed\n", __func__,__LINE__);	\
	}								\
} while (0)

#define MDIO_UNLOCK							\
do {									\
	/* exit driver mode */						\
	r8169soc_ocp_reg_write(tp, 0xDE42,				\
			r8169soc_ocp_reg_read(tp, 0xDE42) & ~BIT(0));	\
	/* enable timer 2 */						\
	r8169soc_ocp_reg_write(tp, 0xE404,				\
		(r8169soc_ocp_reg_read(tp, 0xE404) | 			\
		BIT(12) | BIT(11) | BIT(8)));				\
} while (0)
#endif /* CONFIG_ARCH_RTD129x | CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */

static void r8168dp_1_mdio_access(struct rtl8169_private *tp, int reg, u32 data)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W32(OCPDR, data | ((reg & OCPDR_REG_MASK) << OCPDR_GPHY_REG_SHIFT));
	RTL_W32(OCPAR, OCPAR_GPHY_WRITE_CMD);
	RTL_W32(EPHY_RXER_NUM, 0);

	rtl_udelay_loop_wait_low(tp, &rtl_ocpar_cond, 1000, 100);
}

static void r8168dp_1_mdio_write(struct rtl8169_private *tp, int reg, int value)
{
	r8168dp_1_mdio_access(tp, reg,
				  OCPDR_WRITE_CMD | (value & OCPDR_DATA_MASK));
}

static int r8168dp_1_mdio_read(struct rtl8169_private *tp, int reg)
{
	void __iomem *ioaddr = tp->mmio_addr;

	r8168dp_1_mdio_access(tp, reg, OCPDR_READ_CMD);

	mdelay(1);
	RTL_W32(OCPAR, OCPAR_GPHY_READ_CMD);
	RTL_W32(EPHY_RXER_NUM, 0);

	return rtl_udelay_loop_wait_high(tp, &rtl_ocpar_cond, 1000, 100) ?
		RTL_R32(OCPDR) & OCPDR_DATA_MASK : ~0;
}

#define R8168DP_1_MDIO_ACCESS_BIT	0x00020000

static void r8168dp_2_mdio_start(void __iomem *ioaddr)
{
	RTL_W32(0xd0, RTL_R32(0xd0) & ~R8168DP_1_MDIO_ACCESS_BIT);
}

static void r8168dp_2_mdio_stop(void __iomem *ioaddr)
{
	RTL_W32(0xd0, RTL_R32(0xd0) | R8168DP_1_MDIO_ACCESS_BIT);
}

static void r8168dp_2_mdio_write(struct rtl8169_private *tp, int reg, int value)
{
	void __iomem *ioaddr = tp->mmio_addr;

	r8168dp_2_mdio_start(ioaddr);

	r8169_mdio_write(tp, reg, value);

	r8168dp_2_mdio_stop(ioaddr);
}

static int r8168dp_2_mdio_read(struct rtl8169_private *tp, int reg)
{
	void __iomem *ioaddr = tp->mmio_addr;
	int value;

	r8168dp_2_mdio_start(ioaddr);

	value = r8169_mdio_read(tp, reg);

	r8168dp_2_mdio_stop(ioaddr);

	return value;
}

static void rtl_writephy(struct rtl8169_private *tp, int location, u32 val)
{
	tp->mdio_ops.write(tp, location, val);
}

static int rtl_readphy(struct rtl8169_private *tp, int location)
{
	return tp->mdio_ops.read(tp, location);
}

static void rtl_patchphy(struct rtl8169_private *tp, int reg_addr, int value)
{
	rtl_writephy(tp, reg_addr, rtl_readphy(tp, reg_addr) | value);
}

static void rtl_w1w0_phy(struct rtl8169_private *tp, int reg_addr, int p, int m)
{
	int val;

	val = rtl_readphy(tp, reg_addr);
	rtl_writephy(tp, reg_addr, (val | p) & ~m);
}

static void rtl_mdio_write(struct net_device *dev, int phy_id, int location,
			   int val)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	rtl_writephy(tp, location, val);
}

static int rtl_mdio_read(struct net_device *dev, int phy_id, int location)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	return rtl_readphy(tp, location);
}

DECLARE_RTL_COND(rtl_ephyar_cond)
{
	void __iomem *ioaddr = tp->mmio_addr;

	return RTL_R32(EPHYAR) & EPHYAR_FLAG;
}

static void rtl_ephy_write(struct rtl8169_private *tp, int reg_addr, int value)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W32(EPHYAR, EPHYAR_WRITE_CMD | (value & EPHYAR_DATA_MASK) |
		(reg_addr & EPHYAR_REG_MASK) << EPHYAR_REG_SHIFT);

	rtl_udelay_loop_wait_low(tp, &rtl_ephyar_cond, 10, 100);

	udelay(10);
}

static u16 rtl_ephy_read(struct rtl8169_private *tp, int reg_addr)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W32(EPHYAR, (reg_addr & EPHYAR_REG_MASK) << EPHYAR_REG_SHIFT);

	return rtl_udelay_loop_wait_high(tp, &rtl_ephyar_cond, 10, 100) ?
		RTL_R32(EPHYAR) & EPHYAR_DATA_MASK : ~0;
}

static void rtl_eri_write(struct rtl8169_private *tp, int addr, u32 mask,
			  u32 val, int type)
{
	void __iomem *ioaddr = tp->mmio_addr;

	BUG_ON((addr & 3) || (mask == 0));
	RTL_W32(ERIDR, val);
	RTL_W32(ERIAR, ERIAR_WRITE_CMD | type | mask | addr);

	rtl_udelay_loop_wait_low(tp, &rtl_eriar_cond, 100, 100);
}

static u32 rtl_eri_read(struct rtl8169_private *tp, int addr, int type)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W32(ERIAR, ERIAR_READ_CMD | type | ERIAR_MASK_1111 | addr);

	return rtl_udelay_loop_wait_high(tp, &rtl_eriar_cond, 100, 100) ?
		RTL_R32(ERIDR) : ~0;
}

static void rtl_w1w0_eri(struct rtl8169_private *tp, int addr, u32 mask, u32 p,
			 u32 m, int type)
{
	u32 val;

	val = rtl_eri_read(tp, addr, type);
	rtl_eri_write(tp, addr, mask, (val & ~m) | p, type);
}

struct exgmac_reg {
	u16 addr;
	u16 mask;
	u32 val;
};

static void rtl_write_exgmac_batch(struct rtl8169_private *tp,
				   const struct exgmac_reg *r, int len)
{
	while (len-- > 0) {
		rtl_eri_write(tp, r->addr, r->mask, r->val, ERIAR_EXGMAC);
		r++;
	}
}

DECLARE_RTL_COND(rtl_efusear_cond)
{
	void __iomem *ioaddr = tp->mmio_addr;

	return RTL_R32(EFUSEAR) & EFUSEAR_FLAG;
}

static u8 rtl8168d_efuse_read(struct rtl8169_private *tp, int reg_addr)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W32(EFUSEAR, (reg_addr & EFUSEAR_REG_MASK) << EFUSEAR_REG_SHIFT);

	return rtl_udelay_loop_wait_high(tp, &rtl_efusear_cond, 100, 300) ?
		RTL_R32(EFUSEAR) & EFUSEAR_DATA_MASK : ~0;
}

static u16 rtl_get_events(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	return RTL_R16(IntrStatus);
}

static void rtl_ack_events(struct rtl8169_private *tp, u16 bits)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W16(IntrStatus, bits);
	mmiowb();
}

static void rtl_irq_disable(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W16(IntrMask, 0);
	mmiowb();
}

static void rtl_irq_enable(struct rtl8169_private *tp, u16 bits)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W16(IntrMask, bits);
}

#define RTL_EVENT_NAPI_RX	(RxOK | RxErr)
#define RTL_EVENT_NAPI_TX	(TxOK | TxErr)
#define RTL_EVENT_NAPI		(RTL_EVENT_NAPI_RX | RTL_EVENT_NAPI_TX)

static void rtl_irq_enable_all(struct rtl8169_private *tp)
{
	rtl_irq_enable(tp, RTL_EVENT_NAPI | tp->event_slow);
}

static void rtl8169_irq_mask_and_ack(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	rtl_irq_disable(tp);
	rtl_ack_events(tp, RTL_EVENT_NAPI | tp->event_slow);
	RTL_R8(ChipCmd);
}

static unsigned int rtl8169_tbi_reset_pending(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	return RTL_R32(TBICSR) & TBIReset;
}

static unsigned int rtl8169_xmii_reset_pending(struct rtl8169_private *tp)
{
	return rtl_readphy(tp, MII_BMCR) & BMCR_RESET;
}

static unsigned int rtl8169_tbi_link_ok(void __iomem *ioaddr)
{
	return RTL_R32(TBICSR) & TBILinkOk;
}

static unsigned int rtl8169_xmii_link_ok(void __iomem *ioaddr)
{
	return RTL_R8(PHYstatus) & LinkStatus;
}

static unsigned int rtl8169_xmii_always_link_ok(void __iomem *ioaddr)
{
	return true;
}

static void rtl8169_tbi_reset_enable(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W32(TBICSR, RTL_R32(TBICSR) | TBIReset);
}

static void rtl8169_xmii_reset_enable(struct rtl8169_private *tp)
{
	unsigned int val;

	MDIO_LOCK;
	val = rtl_readphy(tp, MII_BMCR) | BMCR_RESET;
	rtl_writephy(tp, MII_BMCR, val & 0xffff);
	MDIO_UNLOCK;
}

static void rtl_link_chg_patch(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	struct net_device *dev = tp->dev;

	if (!netif_running(dev))
		return;

	if (tp->mac_version == RTL_GIGA_MAC_VER_34 ||
		tp->mac_version == RTL_GIGA_MAC_VER_38) {
		if (RTL_R8(PHYstatus) & _1000bpsF) {
			rtl_eri_write(tp, 0x1bc, ERIAR_MASK_1111, 0x00000011,
					  ERIAR_EXGMAC);
			rtl_eri_write(tp, 0x1dc, ERIAR_MASK_1111, 0x00000005,
					  ERIAR_EXGMAC);
		} else if (RTL_R8(PHYstatus) & _100bps) {
			rtl_eri_write(tp, 0x1bc, ERIAR_MASK_1111, 0x0000001f,
					  ERIAR_EXGMAC);
			rtl_eri_write(tp, 0x1dc, ERIAR_MASK_1111, 0x00000005,
					  ERIAR_EXGMAC);
		} else {
			rtl_eri_write(tp, 0x1bc, ERIAR_MASK_1111, 0x0000001f,
					  ERIAR_EXGMAC);
			rtl_eri_write(tp, 0x1dc, ERIAR_MASK_1111, 0x0000003f,
					  ERIAR_EXGMAC);
		}
		/* Reset packet filter */
		rtl_w1w0_eri(tp, 0xdc, ERIAR_MASK_0001, 0x00, 0x01,
				 ERIAR_EXGMAC);
		rtl_w1w0_eri(tp, 0xdc, ERIAR_MASK_0001, 0x01, 0x00,
				 ERIAR_EXGMAC);
	} else if (tp->mac_version == RTL_GIGA_MAC_VER_35 ||
		   tp->mac_version == RTL_GIGA_MAC_VER_36) {
		if (RTL_R8(PHYstatus) & _1000bpsF) {
			rtl_eri_write(tp, 0x1bc, ERIAR_MASK_1111, 0x00000011,
					  ERIAR_EXGMAC);
			rtl_eri_write(tp, 0x1dc, ERIAR_MASK_1111, 0x00000005,
					  ERIAR_EXGMAC);
		} else {
			rtl_eri_write(tp, 0x1bc, ERIAR_MASK_1111, 0x0000001f,
					  ERIAR_EXGMAC);
			rtl_eri_write(tp, 0x1dc, ERIAR_MASK_1111, 0x0000003f,
					  ERIAR_EXGMAC);
		}
	} else if (tp->mac_version == RTL_GIGA_MAC_VER_37) {
		if (RTL_R8(PHYstatus) & _10bps) {
			rtl_eri_write(tp, 0x1d0, ERIAR_MASK_0011, 0x4d02,
					  ERIAR_EXGMAC);
			rtl_eri_write(tp, 0x1dc, ERIAR_MASK_0011, 0x0060,
					  ERIAR_EXGMAC);
		} else {
			rtl_eri_write(tp, 0x1d0, ERIAR_MASK_0011, 0x0000,
					  ERIAR_EXGMAC);
		}
	}
}

void r8169_mmd_write(struct rtl8169_private *tp, unsigned int dev_addr, unsigned int reg_addr, unsigned int value)
{
	// page 0
	r8169_mdio_write(tp, 0x1f, 0);
	// address mode
	r8169_mdio_write(tp, 13, (0x3fff & dev_addr));
	// write the desired address
	r8169_mdio_write(tp, 14, reg_addr);
	// data mode, no post increment
	r8169_mdio_write(tp, 13, ((0x3fff & dev_addr) | (0x1 << 14)));
	// write the content of the selected register
	r8169_mdio_write(tp, 14, value);
}

unsigned int r8169_mmd_read(struct rtl8169_private *tp, unsigned int dev_addr, unsigned int reg_addr)
{
	// page 0
	r8169_mdio_write(tp, 0x1f, 0);
	// address mode
	r8169_mdio_write(tp, 13, (0x3fff & dev_addr));
	// write the desired address
	r8169_mdio_write(tp, 14, reg_addr);
	// data mode, no post increment
	r8169_mdio_write(tp, 13, ((0x3fff & dev_addr) | (0x1 << 14)));
	// read the content of the selected register
	return r8169_mdio_read(tp, 14);
}

void r8169_display_eee_info(struct net_device *dev, struct rtl8169_private *tp)
{
	// display DUT and link partner EEE capability
	unsigned int	temp, tmp1, tmp2;
	int		speed = 0;
	bool		eee1000, eee100, eee10;

	MDIO_LOCK;
	// page 0xa43
	r8169_mdio_write(tp, 0x1f, 0xa43);
	temp = r8169_mdio_read(tp, 26);
	if (0 == ((0x1 << 2) & temp)) {
		MDIO_UNLOCK;
		pr_err("%s: link is down\n", dev->name);
		return;
	}

	if ((0x0 << 4) == ((0x3 << 4) & temp)) {
		speed = 10;

		r8169_mdio_write(tp, 0x1f, 0xbcd);
		tmp1 = r8169_mdio_read(tp, 19);

		r8169_mdio_write(tp, 0x1f, 0xa60);
		tmp2 = r8169_mdio_read(tp, 16);

		if (0 == ((0x1 << 4) & tmp1))
			eee10 = false;
		else
			eee10 = true;

		MDIO_UNLOCK;
		pr_err("%s: link speed = %dM, EEE = %s, PCS_Status = 0x%02x\n", dev->name, speed, eee10?"Y":"N", tmp2 & 0xff);
		return;
	}
	if ((0x1 << 4) == ((0x3 << 4) & temp)) speed = 100;
	if ((0x2 << 4) == ((0x3 << 4) & temp)) speed = 1000;
	if ((0x1 << 8) == ((0x1 << 8) & temp)) {
		pr_err("%s: link speed = %dM, EEE = Y\n", dev->name, speed);

		r8169_mdio_write(tp, 0x1f, 0xa60);
		tmp1 = r8169_mdio_read(tp, 16);

		r8169_mdio_write(tp, 0x1f, 0xa5c);
		tmp2 = r8169_mdio_read(tp, 19);
		pr_err("PCS_Status = 0x%02x, EEE_wake_error = 0x%04x\n", tmp1 & 0xff, tmp2);
	} else {
		pr_err("%s: link speed = %dM, EEE = N\n", dev->name, speed);

		temp = r8169_mmd_read(tp, 0x7, 0x3d);
		if (0 == (temp & (0x1 << 2)))
			eee1000 = false;
		else
			eee1000 = true;

		if (0 == (temp & (0x1 << 1)))
			eee100 = false;
		else
			eee100 = true;

		pr_err("%s: Link Partner EEE1000=%s, EEE100=%s\n", dev->name, eee1000?"Y":"N", eee100?"Y":"N");
	}
	MDIO_UNLOCK;
}

static void __rtl8169_check_link_status(struct net_device *dev,
					struct rtl8169_private *tp,
					void __iomem *ioaddr, bool pm)
{
	if (tp->link_ok(ioaddr)) {
		rtl_link_chg_patch(tp);
		/* This is to cancel a scheduled suspend if there's one. */
		if (pm)
			pm_request_resume(&tp->pdev->dev);
		netif_carrier_on(dev);
		if (net_ratelimit())
			netif_info(tp, ifup, dev, "link up\n");
	} else {
		netif_carrier_off(dev);
		netif_info(tp, ifdown, dev, "link down\n");
		if (pm)
			pm_schedule_suspend(&tp->pdev->dev, 5000);
	}
}

static void rtl8169_check_link_status(struct net_device *dev,
					  struct rtl8169_private *tp,
					  void __iomem *ioaddr)
{
	__rtl8169_check_link_status(dev, tp, ioaddr, false);
}

#define WAKE_ANY (WAKE_PHY | WAKE_MAGIC | WAKE_UCAST | WAKE_BCAST | WAKE_MCAST)

static u32 __rtl8169_get_wol(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	u8 options;
	u32 wolopts = 0;

	options = RTL_R8(Config1);
	if (!(options & PMEnable))
		return 0;

	options = RTL_R8(Config3);
	if (options & LinkUp)
		wolopts |= WAKE_PHY;
	if (options & MagicPacket)
		wolopts |= WAKE_MAGIC;

	options = RTL_R8(Config5);
	if (options & UWF)
		wolopts |= WAKE_UCAST;
	if (options & BWF)
		wolopts |= WAKE_BCAST;
	if (options & MWF)
		wolopts |= WAKE_MCAST;

	return wolopts;
}

static void rtl8169_get_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	rtl_lock_work(tp);

	wol->supported = WAKE_ANY;
	wol->wolopts = __rtl8169_get_wol(tp);

	rtl_unlock_work(tp);
}

static void __rtl8169_set_wol(struct rtl8169_private *tp, u32 wolopts)
{
	void __iomem *ioaddr = tp->mmio_addr;
	unsigned int i;
	static const struct {
		u32 opt;
		u16 reg;
		u8  mask;
	} cfg[] = {
		{ WAKE_PHY,   Config3, LinkUp },
		{ WAKE_MAGIC, Config3, MagicPacket },
		{ WAKE_UCAST, Config5, UWF },
		{ WAKE_BCAST, Config5, BWF },
		{ WAKE_MCAST, Config5, MWF },
		{ WAKE_ANY,   Config5, LanWake }
	};
	u8 options;

	RTL_W8(Cfg9346, Cfg9346_Unlock);

	for (i = 0; i < ARRAY_SIZE(cfg); i++) {
		options = RTL_R8(cfg[i].reg) & ~cfg[i].mask;
		if (wolopts & cfg[i].opt)
			options |= cfg[i].mask;
		RTL_W8(cfg[i].reg, options);
	}

	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_01 ... RTL_GIGA_MAC_VER_17:
		options = RTL_R8(Config1) & ~PMEnable;
		if (wolopts)
			options |= PMEnable;
		RTL_W8(Config1, options);
		break;
	default:
		options = RTL_R8(Config2) & ~PME_SIGNAL;
		if (wolopts)
			options |= PME_SIGNAL;
		RTL_W8(Config2, options);
		break;
	}

	RTL_W8(Cfg9346, Cfg9346_Lock);
}

static int rtl8169_set_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	rtl_lock_work(tp);

	if (wol->wolopts)
		tp->features |= RTL_FEATURE_WOL;
	else
		tp->features &= ~RTL_FEATURE_WOL;
	__rtl8169_set_wol(tp, wol->wolopts);

	rtl_unlock_work(tp);

	device_set_wakeup_enable(&tp->pdev->dev, wol->wolopts);

	return 0;
}

static const char *rtl_lookup_firmware_name(struct rtl8169_private *tp)
{
	return rtl_chip_infos[tp->mac_version].fw_name;
}

static void rtl8169_get_drvinfo(struct net_device *dev,
				struct ethtool_drvinfo *info)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	struct rtl_fw *rtl_fw = tp->rtl_fw;

	strlcpy(info->driver, MODULENAME, sizeof(info->driver));
	strlcpy(info->version, RTL8169_VERSION, sizeof(info->version));
	strlcpy(info->bus_info, "RTK119X-ETN", sizeof(info->bus_info));
	BUILD_BUG_ON(sizeof(info->fw_version) < sizeof(rtl_fw->version));
	if (!IS_ERR_OR_NULL(rtl_fw))
		strlcpy(info->fw_version, rtl_fw->version,
			sizeof(info->fw_version));
}

static int rtl8169_get_regs_len(struct net_device *dev)
{
	return R8169_REGS_SIZE;
}

static int rtl8169_set_speed_tbi(struct net_device *dev,
				 u8 autoneg, u16 speed, u8 duplex, u32 ignored)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	void __iomem *ioaddr = tp->mmio_addr;
	int ret = 0;
	u32 reg;

	reg = RTL_R32(TBICSR);
	if ((autoneg == AUTONEG_DISABLE) && (speed == SPEED_1000) &&
		(duplex == DUPLEX_FULL)) {
		RTL_W32(TBICSR, reg & ~(TBINwEnable | TBINwRestart));
	} else if (autoneg == AUTONEG_ENABLE)
		RTL_W32(TBICSR, reg | TBINwEnable | TBINwRestart);
	else {
		netif_warn(tp, link, dev,
			   "incorrect speed setting refused in TBI mode\n");
		ret = -EOPNOTSUPP;
	}

	return ret;
}

static int rtl8169_set_speed_xmii(struct net_device *dev,
				  u8 autoneg, u16 speed, u8 duplex, u32 adv)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	int giga_ctrl, bmcr;
	int rc = -EINVAL;

	MDIO_LOCK;
	rtl_writephy(tp, 0x1f, 0x0000);

	if (autoneg == AUTONEG_ENABLE) {
		int auto_nego;

		auto_nego = rtl_readphy(tp, MII_ADVERTISE);
		auto_nego &= ~(ADVERTISE_10HALF | ADVERTISE_10FULL |
				ADVERTISE_100HALF | ADVERTISE_100FULL);

		if (adv & ADVERTISED_10baseT_Half)
			auto_nego |= ADVERTISE_10HALF;
		if (adv & ADVERTISED_10baseT_Full)
			auto_nego |= ADVERTISE_10FULL;
		if (adv & ADVERTISED_100baseT_Half)
			auto_nego |= ADVERTISE_100HALF;
		if (adv & ADVERTISED_100baseT_Full)
			auto_nego |= ADVERTISE_100FULL;

		auto_nego |= ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;

		giga_ctrl = rtl_readphy(tp, MII_CTRL1000);
		giga_ctrl &= ~(ADVERTISE_1000FULL | ADVERTISE_1000HALF);

		/* The 8100e/8101e/8102e do Fast Ethernet only. */
		if (tp->mii.supports_gmii) {
			if (adv & ADVERTISED_1000baseT_Half)
				giga_ctrl |= ADVERTISE_1000HALF;
			if (adv & ADVERTISED_1000baseT_Full)
				giga_ctrl |= ADVERTISE_1000FULL;
		} else if (adv & (ADVERTISED_1000baseT_Half |
				  ADVERTISED_1000baseT_Full)) {
			netif_info(tp, link, dev,
				   "PHY does not support 1000Mbps\n");
			goto out;
		}

		bmcr = BMCR_ANENABLE | BMCR_ANRESTART;

		rtl_writephy(tp, MII_ADVERTISE, auto_nego);
		rtl_writephy(tp, MII_CTRL1000, giga_ctrl);
	} else {
		giga_ctrl = 0;

		if (speed == SPEED_10)
			bmcr = 0;
		else if (speed == SPEED_100)
			bmcr = BMCR_SPEED100;
		else
			goto out;

		if (duplex == DUPLEX_FULL)
			bmcr |= BMCR_FULLDPLX;
	}

	rtl_writephy(tp, MII_BMCR, bmcr);

	if (tp->mac_version == RTL_GIGA_MAC_VER_02 ||
		tp->mac_version == RTL_GIGA_MAC_VER_03) {
		if ((speed == SPEED_100) && (autoneg != AUTONEG_ENABLE)) {
			rtl_writephy(tp, 0x17, 0x2138);
			rtl_writephy(tp, 0x0e, 0x0260);
		} else {
			rtl_writephy(tp, 0x17, 0x2108);
			rtl_writephy(tp, 0x0e, 0x0000);
		}
	}

	rc = 0;
out:
	MDIO_UNLOCK;
	return rc;
}

static int rtl8169_set_speed(struct net_device *dev,
				 u8 autoneg, u16 speed, u8 duplex, u32 advertising)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	int ret;

	ret = tp->set_speed(dev, autoneg, speed, duplex, advertising);
	if (ret < 0)
		goto out;

	if (netif_running(dev)) {
		mod_timer(&tp->timer, jiffies + RTL8169_PHY_TIMEOUT);
	}
out:
	return ret;
}

static int rtl8169_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	int ret;

	del_timer_sync(&tp->timer);

	rtl_lock_work(tp);
	ret = rtl8169_set_speed(dev, cmd->autoneg, ethtool_cmd_speed(cmd),
				cmd->duplex, cmd->advertising);
	rtl_unlock_work(tp);

	return ret;
}

static netdev_features_t rtl8169_fix_features(struct net_device *dev,
	netdev_features_t features)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	if (dev->mtu > TD_MSS_MAX)
		features &= ~NETIF_F_ALL_TSO;

	if (dev->mtu > JUMBO_1K &&
		!rtl_chip_infos[tp->mac_version].jumbo_tx_csum)
		features &= ~NETIF_F_IP_CSUM;

	return features;
}

static void __rtl8169_set_features(struct net_device *dev,
				   netdev_features_t features)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	netdev_features_t changed = features ^ dev->features;
	void __iomem *ioaddr = tp->mmio_addr;

	if (!(changed & (NETIF_F_RXALL | NETIF_F_RXCSUM |
			 NETIF_F_HW_VLAN_CTAG_RX)))
		return;

	if (changed & (NETIF_F_RXCSUM | NETIF_F_HW_VLAN_CTAG_RX)) {
		if (features & NETIF_F_RXCSUM)
			tp->cp_cmd |= RxChkSum;
		else
			tp->cp_cmd &= ~RxChkSum;

		if (dev->features & NETIF_F_HW_VLAN_CTAG_RX)
			tp->cp_cmd |= RxVlan;
		else
			tp->cp_cmd &= ~RxVlan;

		RTL_W16(CPlusCmd, tp->cp_cmd);
		RTL_R16(CPlusCmd);
	}
	if (changed & NETIF_F_RXALL) {
		int tmp = (RTL_R32(RxConfig) & ~(AcceptErr | AcceptRunt));
		if (features & NETIF_F_RXALL)
			tmp |= (AcceptErr | AcceptRunt);
		RTL_W32(RxConfig, tmp);
	}
}

static int rtl8169_set_features(struct net_device *dev,
				netdev_features_t features)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	rtl_lock_work(tp);
	__rtl8169_set_features(dev, features);
	rtl_unlock_work(tp);

	return 0;
}


static inline u32 rtl8169_tx_vlan_tag(struct sk_buff *skb)
{
	return (skb_vlan_tag_present(skb)) ?
		TxVlanTag | swab16(skb_vlan_tag_get(skb)) : 0x00;
}

static void rtl8169_rx_vlan_tag(struct RxDesc *desc, struct sk_buff *skb)
{
	u32 opts2 = le32_to_cpu(desc->opts2);

	if (opts2 & RxVlanTag)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), swab16(opts2 & 0xffff));
}

static int rtl8169_gset_tbi(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	void __iomem *ioaddr = tp->mmio_addr;
	u32 status;

	cmd->supported =
		SUPPORTED_1000baseT_Full | SUPPORTED_Autoneg | SUPPORTED_FIBRE;
	cmd->port = PORT_FIBRE;
	cmd->transceiver = XCVR_INTERNAL;

	status = RTL_R32(TBICSR);
	cmd->advertising = (status & TBINwEnable) ?  ADVERTISED_Autoneg : 0;
	cmd->autoneg = !!(status & TBINwEnable);

	ethtool_cmd_speed_set(cmd, SPEED_1000);
	cmd->duplex = DUPLEX_FULL; /* Always set */

	return 0;
}

static int rtl8169_gset_xmii(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	return mii_ethtool_gset(&tp->mii, cmd);
}

static int rtl8169_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	int rc;

	rtl_lock_work(tp);
	rc = tp->get_settings(dev, cmd);
	rtl_unlock_work(tp);

	return rc;
}

static void rtl8169_get_regs(struct net_device *dev, struct ethtool_regs *regs,
				 void *p)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	if (regs->len > R8169_REGS_SIZE)
		regs->len = R8169_REGS_SIZE;

	rtl_lock_work(tp);
	memcpy_fromio(p, tp->mmio_addr, regs->len);
	rtl_unlock_work(tp);
}

static u32 rtl8169_get_msglevel(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	return tp->msg_enable;
}

static void rtl8169_set_msglevel(struct net_device *dev, u32 value)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	tp->msg_enable = value;
}

static const char rtl8169_gstrings[][ETH_GSTRING_LEN] = {
	"tx_packets",
	"rx_packets",
	"tx_errors",
	"rx_errors",
	"rx_missed",
	"align_errors",
	"tx_single_collisions",
	"tx_multi_collisions",
	"unicast",
	"broadcast",
	"multicast",
	"tx_aborted",
	"tx_underrun",
};

static int rtl8169_get_sset_count(struct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		return ARRAY_SIZE(rtl8169_gstrings);
	default:
		return -EOPNOTSUPP;
	}
}

DECLARE_RTL_COND(rtl_counters_cond)
{
	void __iomem *ioaddr = tp->mmio_addr;

	return RTL_R32(CounterAddrLow) & CounterDump;
}

static void rtl8169_update_counters(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	void __iomem *ioaddr = tp->mmio_addr;
	struct device *d = &tp->pdev->dev;
	struct rtl8169_counters *counters;
	dma_addr_t paddr;
	u32 cmd;
	int node = dev->dev.parent ? dev_to_node(dev->dev.parent) : -1;

	/*
	 * Some chips are unable to dump tally counters when the receiver
	 * is disabled.
	 */
	if ((RTL_R8(ChipCmd) & CmdRxEnb) == 0)
		return;

	if (tp->acp_enable) {
		counters = kzalloc_node(sizeof(*counters), GFP_KERNEL, node);
		paddr = virt_to_phys(counters);
	} else {
		counters = dma_alloc_coherent(d, sizeof(*counters), &paddr, GFP_KERNEL);
	}
	if (!counters)
		return;

	RTL_W32(CounterAddrHigh, (u64)paddr >> 32);
	cmd = (u64)paddr & DMA_BIT_MASK(32);
	RTL_W32(CounterAddrLow, cmd);
	RTL_W32(CounterAddrLow, cmd | CounterDump);

	if (rtl_udelay_loop_wait_low(tp, &rtl_counters_cond, 10, 1000))
		memcpy(&tp->counters, counters, sizeof(*counters));

	RTL_W32(CounterAddrLow, 0);
	RTL_W32(CounterAddrHigh, 0);

	if (tp->acp_enable) {
		kfree(counters);
	} else {
		dma_free_coherent(d, sizeof(*counters), counters, paddr);
	}
}

static void rtl8169_get_ethtool_stats(struct net_device *dev,
					  struct ethtool_stats *stats, u64 *data)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	ASSERT_RTNL();

	rtl8169_update_counters(dev);

	data[0] = le64_to_cpu(tp->counters.tx_packets);
	data[1] = le64_to_cpu(tp->counters.rx_packets);
	data[2] = le64_to_cpu(tp->counters.tx_errors);
	data[3] = le32_to_cpu(tp->counters.rx_errors);
	data[4] = le16_to_cpu(tp->counters.rx_missed);
	data[5] = le16_to_cpu(tp->counters.align_errors);
	data[6] = le32_to_cpu(tp->counters.tx_one_collision);
	data[7] = le32_to_cpu(tp->counters.tx_multi_collision);
	data[8] = le64_to_cpu(tp->counters.rx_unicast);
	data[9] = le64_to_cpu(tp->counters.rx_broadcast);
	data[10] = le32_to_cpu(tp->counters.rx_multicast);
	data[11] = le16_to_cpu(tp->counters.tx_aborted);
	data[12] = le16_to_cpu(tp->counters.tx_underun);
}

static void rtl8169_get_strings(struct net_device *dev, u32 stringset, u8 *data)
{
	switch(stringset) {
	case ETH_SS_STATS:
		memcpy(data, *rtl8169_gstrings, sizeof(rtl8169_gstrings));
		break;
	}
}

static const struct ethtool_ops rtl8169_ethtool_ops = {
	.get_drvinfo		= rtl8169_get_drvinfo,
	.get_regs_len		= rtl8169_get_regs_len,
	.get_link		= ethtool_op_get_link,
	.get_settings		= rtl8169_get_settings,
	.set_settings		= rtl8169_set_settings,
	.get_msglevel		= rtl8169_get_msglevel,
	.set_msglevel		= rtl8169_set_msglevel,
	.get_regs		= rtl8169_get_regs,
	.get_wol		= rtl8169_get_wol,
	.set_wol		= rtl8169_set_wol,
	.get_strings		= rtl8169_get_strings,
	.get_sset_count		= rtl8169_get_sset_count,
	.get_ethtool_stats	= rtl8169_get_ethtool_stats,
	.get_ts_info		= ethtool_op_get_ts_info,
};

static void rtl8169_get_mac_version(struct rtl8169_private *tp,
					struct net_device *dev, u8 default_version)
{
//	void __iomem *ioaddr = tp->mmio_addr;
	/*
	 * The driver currently handles the 8168Bf and the 8168Be identically
	 * but they can be identified more specifically through the test below
	 * if needed:
	 *
	 * (RTL_R32(TxConfig) & 0x700000) == 0x500000 ? 8168Bf : 8168Be
	 *
	 * Same thing for the 8101Eb and the 8101Ec:
	 *
	 * (RTL_R32(TxConfig) & 0x700000) == 0x200000 ? 8101Eb : 8101Ec
	 */
#if 0
	static const struct rtl_mac_info {
		u32 mask;
		u32 val;
		int mac_version;
	} mac_info[] = {
		/* 8168G family. */
		{ 0x7cf00000, 0x50900000,	RTL_GIGA_MAC_VER_42 },
		{ 0x7cf00000, 0x4c100000,	RTL_GIGA_MAC_VER_41 },
		{ 0x7cf00000, 0x4c000000,	RTL_GIGA_MAC_VER_40 },

		/* 8168F family. */
		{ 0x7c800000, 0x48800000,	RTL_GIGA_MAC_VER_38 },
		{ 0x7cf00000, 0x48100000,	RTL_GIGA_MAC_VER_36 },
		{ 0x7cf00000, 0x48000000,	RTL_GIGA_MAC_VER_35 },

		/* 8168E family. */
		{ 0x7c800000, 0x2c800000,	RTL_GIGA_MAC_VER_34 },
		{ 0x7cf00000, 0x2c200000,	RTL_GIGA_MAC_VER_33 },
		{ 0x7cf00000, 0x2c100000,	RTL_GIGA_MAC_VER_32 },
		{ 0x7c800000, 0x2c000000,	RTL_GIGA_MAC_VER_33 },

		/* 8168D family. */
		{ 0x7cf00000, 0x28300000,	RTL_GIGA_MAC_VER_26 },
		{ 0x7cf00000, 0x28100000,	RTL_GIGA_MAC_VER_25 },
		{ 0x7c800000, 0x28000000,	RTL_GIGA_MAC_VER_26 },

		/* 8168DP family. */
		{ 0x7cf00000, 0x28800000,	RTL_GIGA_MAC_VER_27 },
		{ 0x7cf00000, 0x28a00000,	RTL_GIGA_MAC_VER_28 },
		{ 0x7cf00000, 0x28b00000,	RTL_GIGA_MAC_VER_31 },

		/* 8168C family. */
		{ 0x7cf00000, 0x3cb00000,	RTL_GIGA_MAC_VER_24 },
		{ 0x7cf00000, 0x3c900000,	RTL_GIGA_MAC_VER_23 },
		{ 0x7cf00000, 0x3c800000,	RTL_GIGA_MAC_VER_18 },
		{ 0x7c800000, 0x3c800000,	RTL_GIGA_MAC_VER_24 },
		{ 0x7cf00000, 0x3c000000,	RTL_GIGA_MAC_VER_19 },
		{ 0x7cf00000, 0x3c200000,	RTL_GIGA_MAC_VER_20 },
		{ 0x7cf00000, 0x3c300000,	RTL_GIGA_MAC_VER_21 },
		{ 0x7cf00000, 0x3c400000,	RTL_GIGA_MAC_VER_22 },
		{ 0x7c800000, 0x3c000000,	RTL_GIGA_MAC_VER_22 },

		/* 8168B family. */
		{ 0x7cf00000, 0x38000000,	RTL_GIGA_MAC_VER_12 },
		{ 0x7cf00000, 0x38500000,	RTL_GIGA_MAC_VER_17 },
		{ 0x7c800000, 0x38000000,	RTL_GIGA_MAC_VER_17 },
		{ 0x7c800000, 0x30000000,	RTL_GIGA_MAC_VER_11 },

		/* 8101 family. */
		{ 0x7cf00000, 0x44900000,	RTL_GIGA_MAC_VER_39 },
		{ 0x7c800000, 0x44800000,	RTL_GIGA_MAC_VER_39 },
		{ 0x7c800000, 0x44000000,	RTL_GIGA_MAC_VER_37 },
		{ 0x7cf00000, 0x40b00000,	RTL_GIGA_MAC_VER_30 },
		{ 0x7cf00000, 0x40a00000,	RTL_GIGA_MAC_VER_30 },
		{ 0x7cf00000, 0x40900000,	RTL_GIGA_MAC_VER_29 },
		{ 0x7c800000, 0x40800000,	RTL_GIGA_MAC_VER_30 },
		{ 0x7cf00000, 0x34a00000,	RTL_GIGA_MAC_VER_09 },
		{ 0x7cf00000, 0x24a00000,	RTL_GIGA_MAC_VER_09 },
		{ 0x7cf00000, 0x34900000,	RTL_GIGA_MAC_VER_08 },
		{ 0x7cf00000, 0x24900000,	RTL_GIGA_MAC_VER_08 },
		{ 0x7cf00000, 0x34800000,	RTL_GIGA_MAC_VER_07 },
		{ 0x7cf00000, 0x24800000,	RTL_GIGA_MAC_VER_07 },
		{ 0x7cf00000, 0x34000000,	RTL_GIGA_MAC_VER_13 },
		{ 0x7cf00000, 0x34300000,	RTL_GIGA_MAC_VER_10 },
		{ 0x7cf00000, 0x34200000,	RTL_GIGA_MAC_VER_16 },
		{ 0x7c800000, 0x34800000,	RTL_GIGA_MAC_VER_09 },
		{ 0x7c800000, 0x24800000,	RTL_GIGA_MAC_VER_09 },
		{ 0x7c800000, 0x34000000,	RTL_GIGA_MAC_VER_16 },
		/* FIXME: where did these entries come from ? -- FR */
		{ 0xfc800000, 0x38800000,	RTL_GIGA_MAC_VER_15 },
		{ 0xfc800000, 0x30800000,	RTL_GIGA_MAC_VER_14 },

		/* 8110 family. */
		{ 0xfc800000, 0x98000000,	RTL_GIGA_MAC_VER_06 },
		{ 0xfc800000, 0x18000000,	RTL_GIGA_MAC_VER_05 },
		{ 0xfc800000, 0x10000000,	RTL_GIGA_MAC_VER_04 },
		{ 0xfc800000, 0x04000000,	RTL_GIGA_MAC_VER_03 },
		{ 0xfc800000, 0x00800000,	RTL_GIGA_MAC_VER_02 },
		{ 0xfc800000, 0x00000000,	RTL_GIGA_MAC_VER_01 },

		/* Catch-all */
		{ 0x00000000, 0x00000000,	RTL_GIGA_MAC_NONE   }
	};
	const struct rtl_mac_info *p = mac_info;
	u32 reg;

	reg = RTL_R32(TxConfig);
	while ((reg & p->mask) != p->val)
		p++;
	tp->mac_version = p->mac_version;
#endif

	if (tp->mac_version == RTL_GIGA_MAC_NONE) {
		netif_notice(tp, probe, dev,
				 "unknown MAC, using family default\n");
		tp->mac_version = default_version;
	}
/* barry mask off
	else if (tp->mac_version == RTL_GIGA_MAC_VER_42) {
		tp->mac_version = tp->mii.supports_gmii ?
				  RTL_GIGA_MAC_VER_42 :
				  RTL_GIGA_MAC_VER_43;
	}
*/
}

static void rtl8169_print_mac_version(struct rtl8169_private *tp)
{
	dprintk("mac_version = 0x%02x\n", tp->mac_version);
}

struct phy_reg {
	u16 reg;
	u16 val;
};

static void rtl_writephy_batch(struct rtl8169_private *tp,
				   const struct phy_reg *regs, int len)
{
	while (len-- > 0) {
		rtl_writephy(tp, regs->reg, regs->val);
		regs++;
	}
}

#define PHY_READ		0x00000000
#define PHY_DATA_OR		0x10000000
#define PHY_DATA_AND		0x20000000
#define PHY_BJMPN		0x30000000
#define PHY_MDIO_CHG		0x40000000
#define PHY_CLEAR_READCOUNT	0x70000000
#define PHY_WRITE		0x80000000
#define PHY_READCOUNT_EQ_SKIP	0x90000000
#define PHY_COMP_EQ_SKIPN	0xa0000000
#define PHY_COMP_NEQ_SKIPN	0xb0000000
#define PHY_WRITE_PREVIOUS	0xc0000000
#define PHY_SKIPN		0xd0000000
#define PHY_DELAY_MS		0xe0000000

struct fw_info {
	u32	magic;
	char	version[RTL_VER_SIZE];
	__le32	fw_start;
	__le32	fw_len;
	u8	chksum;
} __packed;

#define FW_OPCODE_SIZE	sizeof(typeof(*((struct rtl_fw_phy_action *)0)->code))

static bool rtl_fw_format_ok(struct rtl8169_private *tp, struct rtl_fw *rtl_fw)
{
	const struct firmware *fw = rtl_fw->fw;
	struct fw_info *fw_info = (struct fw_info *)fw->data;
	struct rtl_fw_phy_action *pa = &rtl_fw->phy_action;
	char *version = rtl_fw->version;
	bool rc = false;

	if (fw->size < FW_OPCODE_SIZE)
		goto out;

	if (!fw_info->magic) {
		size_t i, size, start;
		u8 checksum = 0;

		if (fw->size < sizeof(*fw_info))
			goto out;

		for (i = 0; i < fw->size; i++)
			checksum += fw->data[i];
		if (checksum != 0)
			goto out;

		start = le32_to_cpu(fw_info->fw_start);
		if (start > fw->size)
			goto out;

		size = le32_to_cpu(fw_info->fw_len);
		if (size > (fw->size - start) / FW_OPCODE_SIZE)
			goto out;

		memcpy(version, fw_info->version, RTL_VER_SIZE);

		pa->code = (__le32 *)(fw->data + start);
		pa->size = size;
	} else {
		if (fw->size % FW_OPCODE_SIZE)
			goto out;

		strlcpy(version, rtl_lookup_firmware_name(tp), RTL_VER_SIZE);

		pa->code = (__le32 *)fw->data;
		pa->size = fw->size / FW_OPCODE_SIZE;
	}
	version[RTL_VER_SIZE - 1] = 0;

	rc = true;
out:
	return rc;
}

static bool rtl_fw_data_ok(struct rtl8169_private *tp, struct net_device *dev,
			   struct rtl_fw_phy_action *pa)
{
	bool rc = false;
	size_t index;

	for (index = 0; index < pa->size; index++) {
		u32 action = le32_to_cpu(pa->code[index]);
		u32 regno = (action & 0x0fff0000) >> 16;

		switch(action & 0xf0000000) {
		case PHY_READ:
		case PHY_DATA_OR:
		case PHY_DATA_AND:
		case PHY_MDIO_CHG:
		case PHY_CLEAR_READCOUNT:
		case PHY_WRITE:
		case PHY_WRITE_PREVIOUS:
		case PHY_DELAY_MS:
			break;

		case PHY_BJMPN:
			if (regno > index) {
				netif_err(tp, ifup, tp->dev,
					  "Out of range of firmware\n");
				goto out;
			}
			break;
		case PHY_READCOUNT_EQ_SKIP:
			if (index + 2 >= pa->size) {
				netif_err(tp, ifup, tp->dev,
					  "Out of range of firmware\n");
				goto out;
			}
			break;
		case PHY_COMP_EQ_SKIPN:
		case PHY_COMP_NEQ_SKIPN:
		case PHY_SKIPN:
			if (index + 1 + regno >= pa->size) {
				netif_err(tp, ifup, tp->dev,
					  "Out of range of firmware\n");
				goto out;
			}
			break;

		default:
			netif_err(tp, ifup, tp->dev,
				  "Invalid action 0x%08x\n", action);
			goto out;
		}
	}
	rc = true;
out:
	return rc;
}

static int rtl_check_firmware(struct rtl8169_private *tp, struct rtl_fw *rtl_fw)
{
	struct net_device *dev = tp->dev;
	int rc = -EINVAL;

	if (!rtl_fw_format_ok(tp, rtl_fw)) {
		netif_err(tp, ifup, dev, "invalid firwmare\n");
		goto out;
	}

	if (rtl_fw_data_ok(tp, dev, &rtl_fw->phy_action))
		rc = 0;
out:
	return rc;
}

static void rtl_phy_write_fw(struct rtl8169_private *tp, struct rtl_fw *rtl_fw)
{
#if 0
	struct rtl_fw_phy_action *pa = &rtl_fw->phy_action;
	struct mdio_ops org, *ops = &tp->mdio_ops;
	u32 predata, count;
	size_t index;

	predata = count = 0;
	org.write = ops->write;
	org.read = ops->read;

	for (index = 0; index < pa->size; ) {
		u32 action = le32_to_cpu(pa->code[index]);
		u32 data = action & 0x0000ffff;
		u32 regno = (action & 0x0fff0000) >> 16;

		if (!action)
			break;

		switch(action & 0xf0000000) {
		case PHY_READ:
			predata = rtl_readphy(tp, regno);
			count++;
			index++;
			break;
		case PHY_DATA_OR:
			predata |= data;
			index++;
			break;
		case PHY_DATA_AND:
			predata &= data;
			index++;
			break;
		case PHY_BJMPN:
			index -= regno;
			break;
		case PHY_MDIO_CHG:
			if (data == 0) {
				ops->write = org.write;
				ops->read = org.read;
			} else if (data == 1) {
				ops->write = mac_mcu_write;
				ops->read = mac_mcu_read;
			}

			index++;
			break;
		case PHY_CLEAR_READCOUNT:
			count = 0;
			index++;
			break;
		case PHY_WRITE:
			rtl_writephy(tp, regno, data);
			index++;
			break;
		case PHY_READCOUNT_EQ_SKIP:
			index += (count == data) ? 2 : 1;
			break;
		case PHY_COMP_EQ_SKIPN:
			if (predata == data)
				index += regno;
			index++;
			break;
		case PHY_COMP_NEQ_SKIPN:
			if (predata != data)
				index += regno;
			index++;
			break;
		case PHY_WRITE_PREVIOUS:
			rtl_writephy(tp, regno, predata);
			index++;
			break;
		case PHY_SKIPN:
			index += regno + 1;
			break;
		case PHY_DELAY_MS:
			mdelay(data);
			index++;
			break;

		default:
			BUG();
		}
	}

	ops->write = org.write;
	ops->read = org.read;
#endif
}

static void rtl_release_firmware(struct rtl8169_private *tp)
{
	if (!IS_ERR_OR_NULL(tp->rtl_fw)) {
		release_firmware(tp->rtl_fw->fw);
		kfree(tp->rtl_fw);
	}
	tp->rtl_fw = RTL_FIRMWARE_UNKNOWN;
}

static void rtl_apply_firmware(struct rtl8169_private *tp)
{
	struct rtl_fw *rtl_fw = tp->rtl_fw;

	/* TODO: release firmware once rtl_phy_write_fw signals failures. */
	if (!IS_ERR_OR_NULL(rtl_fw))
		rtl_phy_write_fw(tp, rtl_fw);
}

static void rtl_apply_firmware_cond(struct rtl8169_private *tp, u8 reg, u16 val)
{
	if (rtl_readphy(tp, reg) != val)
		netif_warn(tp, hw, tp->dev, "chipset not ready for firmware\n");
	else
		rtl_apply_firmware(tp);
}

static void rtl8169s_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		{ 0x1f, 0x0001 },
		{ 0x06, 0x006e },
		{ 0x08, 0x0708 },
		{ 0x15, 0x4000 },
		{ 0x18, 0x65c7 },

		{ 0x1f, 0x0001 },
		{ 0x03, 0x00a1 },
		{ 0x02, 0x0008 },
		{ 0x01, 0x0120 },
		{ 0x00, 0x1000 },
		{ 0x04, 0x0800 },
		{ 0x04, 0x0000 },

		{ 0x03, 0xff41 },
		{ 0x02, 0xdf60 },
		{ 0x01, 0x0140 },
		{ 0x00, 0x0077 },
		{ 0x04, 0x7800 },
		{ 0x04, 0x7000 },

		{ 0x03, 0x802f },
		{ 0x02, 0x4f02 },
		{ 0x01, 0x0409 },
		{ 0x00, 0xf0f9 },
		{ 0x04, 0x9800 },
		{ 0x04, 0x9000 },

		{ 0x03, 0xdf01 },
		{ 0x02, 0xdf20 },
		{ 0x01, 0xff95 },
		{ 0x00, 0xba00 },
		{ 0x04, 0xa800 },
		{ 0x04, 0xa000 },

		{ 0x03, 0xff41 },
		{ 0x02, 0xdf20 },
		{ 0x01, 0x0140 },
		{ 0x00, 0x00bb },
		{ 0x04, 0xb800 },
		{ 0x04, 0xb000 },

		{ 0x03, 0xdf41 },
		{ 0x02, 0xdc60 },
		{ 0x01, 0x6340 },
		{ 0x00, 0x007d },
		{ 0x04, 0xd800 },
		{ 0x04, 0xd000 },

		{ 0x03, 0xdf01 },
		{ 0x02, 0xdf20 },
		{ 0x01, 0x100a },
		{ 0x00, 0xa0ff },
		{ 0x04, 0xf800 },
		{ 0x04, 0xf000 },

		{ 0x1f, 0x0000 },
		{ 0x0b, 0x0000 },
		{ 0x00, 0x9200 }
	};

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));
}

static void rtl8169sb_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		{ 0x1f, 0x0002 },
		{ 0x01, 0x90d0 },
		{ 0x1f, 0x0000 }
	};

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));
}

static void rtl8169scd_hw_phy_config_quirk(struct rtl8169_private *tp)
{
#if 0
	struct platform_device *pdev = tp->pdev;

	if ((pdev->subsystem_vendor != PCI_VENDOR_ID_GIGABYTE) ||
		(pdev->subsystem_device != 0xe000))
		return;

	rtl_writephy(tp, 0x1f, 0x0001);
	rtl_writephy(tp, 0x10, 0xf01b);
	rtl_writephy(tp, 0x1f, 0x0000);
#endif
}

static void rtl8169scd_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		{ 0x1f, 0x0001 },
		{ 0x04, 0x0000 },
		{ 0x03, 0x00a1 },
		{ 0x02, 0x0008 },
		{ 0x01, 0x0120 },
		{ 0x00, 0x1000 },
		{ 0x04, 0x0800 },
		{ 0x04, 0x9000 },
		{ 0x03, 0x802f },
		{ 0x02, 0x4f02 },
		{ 0x01, 0x0409 },
		{ 0x00, 0xf099 },
		{ 0x04, 0x9800 },
		{ 0x04, 0xa000 },
		{ 0x03, 0xdf01 },
		{ 0x02, 0xdf20 },
		{ 0x01, 0xff95 },
		{ 0x00, 0xba00 },
		{ 0x04, 0xa800 },
		{ 0x04, 0xf000 },
		{ 0x03, 0xdf01 },
		{ 0x02, 0xdf20 },
		{ 0x01, 0x101a },
		{ 0x00, 0xa0ff },
		{ 0x04, 0xf800 },
		{ 0x04, 0x0000 },
		{ 0x1f, 0x0000 },

		{ 0x1f, 0x0001 },
		{ 0x10, 0xf41b },
		{ 0x14, 0xfb54 },
		{ 0x18, 0xf5c7 },
		{ 0x1f, 0x0000 },

		{ 0x1f, 0x0001 },
		{ 0x17, 0x0cc0 },
		{ 0x1f, 0x0000 }
	};

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));

	rtl8169scd_hw_phy_config_quirk(tp);
}

static void rtl8169sce_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		{ 0x1f, 0x0001 },
		{ 0x04, 0x0000 },
		{ 0x03, 0x00a1 },
		{ 0x02, 0x0008 },
		{ 0x01, 0x0120 },
		{ 0x00, 0x1000 },
		{ 0x04, 0x0800 },
		{ 0x04, 0x9000 },
		{ 0x03, 0x802f },
		{ 0x02, 0x4f02 },
		{ 0x01, 0x0409 },
		{ 0x00, 0xf099 },
		{ 0x04, 0x9800 },
		{ 0x04, 0xa000 },
		{ 0x03, 0xdf01 },
		{ 0x02, 0xdf20 },
		{ 0x01, 0xff95 },
		{ 0x00, 0xba00 },
		{ 0x04, 0xa800 },
		{ 0x04, 0xf000 },
		{ 0x03, 0xdf01 },
		{ 0x02, 0xdf20 },
		{ 0x01, 0x101a },
		{ 0x00, 0xa0ff },
		{ 0x04, 0xf800 },
		{ 0x04, 0x0000 },
		{ 0x1f, 0x0000 },

		{ 0x1f, 0x0001 },
		{ 0x0b, 0x8480 },
		{ 0x1f, 0x0000 },

		{ 0x1f, 0x0001 },
		{ 0x18, 0x67c7 },
		{ 0x04, 0x2000 },
		{ 0x03, 0x002f },
		{ 0x02, 0x4360 },
		{ 0x01, 0x0109 },
		{ 0x00, 0x3022 },
		{ 0x04, 0x2800 },
		{ 0x1f, 0x0000 },

		{ 0x1f, 0x0001 },
		{ 0x17, 0x0cc0 },
		{ 0x1f, 0x0000 }
	};

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));
}

static void rtl8168bb_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		{ 0x10, 0xf41b },
		{ 0x1f, 0x0000 }
	};

	rtl_writephy(tp, 0x1f, 0x0001);
	rtl_patchphy(tp, 0x16, 1 << 0);

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));
}

static void rtl8168bef_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		{ 0x1f, 0x0001 },
		{ 0x10, 0xf41b },
		{ 0x1f, 0x0000 }
	};

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));
}

static void rtl8168cp_1_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		{ 0x1f, 0x0000 },
		{ 0x1d, 0x0f00 },
		{ 0x1f, 0x0002 },
		{ 0x0c, 0x1ec8 },
		{ 0x1f, 0x0000 }
	};

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));
}

static void rtl8168cp_2_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		{ 0x1f, 0x0001 },
		{ 0x1d, 0x3d98 },
		{ 0x1f, 0x0000 }
	};

	rtl_writephy(tp, 0x1f, 0x0000);
	rtl_patchphy(tp, 0x14, 1 << 5);
	rtl_patchphy(tp, 0x0d, 1 << 5);

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));
}

static void rtl8168c_1_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		{ 0x1f, 0x0001 },
		{ 0x12, 0x2300 },
		{ 0x1f, 0x0002 },
		{ 0x00, 0x88d4 },
		{ 0x01, 0x82b1 },
		{ 0x03, 0x7002 },
		{ 0x08, 0x9e30 },
		{ 0x09, 0x01f0 },
		{ 0x0a, 0x5500 },
		{ 0x0c, 0x00c8 },
		{ 0x1f, 0x0003 },
		{ 0x12, 0xc096 },
		{ 0x16, 0x000a },
		{ 0x1f, 0x0000 },
		{ 0x1f, 0x0000 },
		{ 0x09, 0x2000 },
		{ 0x09, 0x0000 }
	};

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));

	rtl_patchphy(tp, 0x14, 1 << 5);
	rtl_patchphy(tp, 0x0d, 1 << 5);
	rtl_writephy(tp, 0x1f, 0x0000);
}

static void rtl8168c_2_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		{ 0x1f, 0x0001 },
		{ 0x12, 0x2300 },
		{ 0x03, 0x802f },
		{ 0x02, 0x4f02 },
		{ 0x01, 0x0409 },
		{ 0x00, 0xf099 },
		{ 0x04, 0x9800 },
		{ 0x04, 0x9000 },
		{ 0x1d, 0x3d98 },
		{ 0x1f, 0x0002 },
		{ 0x0c, 0x7eb8 },
		{ 0x06, 0x0761 },
		{ 0x1f, 0x0003 },
		{ 0x16, 0x0f0a },
		{ 0x1f, 0x0000 }
	};

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));

	rtl_patchphy(tp, 0x16, 1 << 0);
	rtl_patchphy(tp, 0x14, 1 << 5);
	rtl_patchphy(tp, 0x0d, 1 << 5);
	rtl_writephy(tp, 0x1f, 0x0000);
}

static void rtl8168c_3_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		{ 0x1f, 0x0001 },
		{ 0x12, 0x2300 },
		{ 0x1d, 0x3d98 },
		{ 0x1f, 0x0002 },
		{ 0x0c, 0x7eb8 },
		{ 0x06, 0x5461 },
		{ 0x1f, 0x0003 },
		{ 0x16, 0x0f0a },
		{ 0x1f, 0x0000 }
	};

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));

	rtl_patchphy(tp, 0x16, 1 << 0);
	rtl_patchphy(tp, 0x14, 1 << 5);
	rtl_patchphy(tp, 0x0d, 1 << 5);
	rtl_writephy(tp, 0x1f, 0x0000);
}

static void rtl8168c_4_hw_phy_config(struct rtl8169_private *tp)
{
	rtl8168c_3_hw_phy_config(tp);
}

static void rtl8168d_1_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init_0[] = {
		/* Channel Estimation */
		{ 0x1f, 0x0001 },
		{ 0x06, 0x4064 },
		{ 0x07, 0x2863 },
		{ 0x08, 0x059c },
		{ 0x09, 0x26b4 },
		{ 0x0a, 0x6a19 },
		{ 0x0b, 0xdcc8 },
		{ 0x10, 0xf06d },
		{ 0x14, 0x7f68 },
		{ 0x18, 0x7fd9 },
		{ 0x1c, 0xf0ff },
		{ 0x1d, 0x3d9c },
		{ 0x1f, 0x0003 },
		{ 0x12, 0xf49f },
		{ 0x13, 0x070b },
		{ 0x1a, 0x05ad },
		{ 0x14, 0x94c0 },

		/*
		 * Tx Error Issue
		 * Enhance line driver power
		 */
		{ 0x1f, 0x0002 },
		{ 0x06, 0x5561 },
		{ 0x1f, 0x0005 },
		{ 0x05, 0x8332 },
		{ 0x06, 0x5561 },

		/*
		 * Can not link to 1Gbps with bad cable
		 * Decrease SNR threshold form 21.07dB to 19.04dB
		 */
		{ 0x1f, 0x0001 },
		{ 0x17, 0x0cc0 },

		{ 0x1f, 0x0000 },
		{ 0x0d, 0xf880 }
	};

	rtl_writephy_batch(tp, phy_reg_init_0, ARRAY_SIZE(phy_reg_init_0));

	/*
	 * Rx Error Issue
	 * Fine Tune Switching regulator parameter
	 */
	rtl_writephy(tp, 0x1f, 0x0002);
	rtl_w1w0_phy(tp, 0x0b, 0x0010, 0x00ef);
	rtl_w1w0_phy(tp, 0x0c, 0xa200, 0x5d00);

	if (rtl8168d_efuse_read(tp, 0x01) == 0xb1) {
		static const struct phy_reg phy_reg_init[] = {
			{ 0x1f, 0x0002 },
			{ 0x05, 0x669a },
			{ 0x1f, 0x0005 },
			{ 0x05, 0x8330 },
			{ 0x06, 0x669a },
			{ 0x1f, 0x0002 }
		};
		int val;

		rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));

		val = rtl_readphy(tp, 0x0d);

		if ((val & 0x00ff) != 0x006c) {
			static const u32 set[] = {
				0x0065, 0x0066, 0x0067, 0x0068,
				0x0069, 0x006a, 0x006b, 0x006c
			};
			int i;

			rtl_writephy(tp, 0x1f, 0x0002);

			val &= 0xff00;
			for (i = 0; i < ARRAY_SIZE(set); i++)
				rtl_writephy(tp, 0x0d, val | set[i]);
		}
	} else {
		static const struct phy_reg phy_reg_init[] = {
			{ 0x1f, 0x0002 },
			{ 0x05, 0x6662 },
			{ 0x1f, 0x0005 },
			{ 0x05, 0x8330 },
			{ 0x06, 0x6662 }
		};

		rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));
	}

	/* RSET couple improve */
	rtl_writephy(tp, 0x1f, 0x0002);
	rtl_patchphy(tp, 0x0d, 0x0300);
	rtl_patchphy(tp, 0x0f, 0x0010);

	/* Fine tune PLL performance */
	rtl_writephy(tp, 0x1f, 0x0002);
	rtl_w1w0_phy(tp, 0x02, 0x0100, 0x0600);
	rtl_w1w0_phy(tp, 0x03, 0x0000, 0xe000);

	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x001b);

	rtl_apply_firmware_cond(tp, MII_EXPANSION, 0xbf00);

	rtl_writephy(tp, 0x1f, 0x0000);
}

static void rtl8168d_2_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init_0[] = {
		/* Channel Estimation */
		{ 0x1f, 0x0001 },
		{ 0x06, 0x4064 },
		{ 0x07, 0x2863 },
		{ 0x08, 0x059c },
		{ 0x09, 0x26b4 },
		{ 0x0a, 0x6a19 },
		{ 0x0b, 0xdcc8 },
		{ 0x10, 0xf06d },
		{ 0x14, 0x7f68 },
		{ 0x18, 0x7fd9 },
		{ 0x1c, 0xf0ff },
		{ 0x1d, 0x3d9c },
		{ 0x1f, 0x0003 },
		{ 0x12, 0xf49f },
		{ 0x13, 0x070b },
		{ 0x1a, 0x05ad },
		{ 0x14, 0x94c0 },

		/*
		 * Tx Error Issue
		 * Enhance line driver power
		 */
		{ 0x1f, 0x0002 },
		{ 0x06, 0x5561 },
		{ 0x1f, 0x0005 },
		{ 0x05, 0x8332 },
		{ 0x06, 0x5561 },

		/*
		 * Can not link to 1Gbps with bad cable
		 * Decrease SNR threshold form 21.07dB to 19.04dB
		 */
		{ 0x1f, 0x0001 },
		{ 0x17, 0x0cc0 },

		{ 0x1f, 0x0000 },
		{ 0x0d, 0xf880 }
	};

	rtl_writephy_batch(tp, phy_reg_init_0, ARRAY_SIZE(phy_reg_init_0));

	if (rtl8168d_efuse_read(tp, 0x01) == 0xb1) {
		static const struct phy_reg phy_reg_init[] = {
			{ 0x1f, 0x0002 },
			{ 0x05, 0x669a },
			{ 0x1f, 0x0005 },
			{ 0x05, 0x8330 },
			{ 0x06, 0x669a },

			{ 0x1f, 0x0002 }
		};
		int val;

		rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));

		val = rtl_readphy(tp, 0x0d);
		if ((val & 0x00ff) != 0x006c) {
			static const u32 set[] = {
				0x0065, 0x0066, 0x0067, 0x0068,
				0x0069, 0x006a, 0x006b, 0x006c
			};
			int i;

			rtl_writephy(tp, 0x1f, 0x0002);

			val &= 0xff00;
			for (i = 0; i < ARRAY_SIZE(set); i++)
				rtl_writephy(tp, 0x0d, val | set[i]);
		}
	} else {
		static const struct phy_reg phy_reg_init[] = {
			{ 0x1f, 0x0002 },
			{ 0x05, 0x2642 },
			{ 0x1f, 0x0005 },
			{ 0x05, 0x8330 },
			{ 0x06, 0x2642 }
		};

		rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));
	}

	/* Fine tune PLL performance */
	rtl_writephy(tp, 0x1f, 0x0002);
	rtl_w1w0_phy(tp, 0x02, 0x0100, 0x0600);
	rtl_w1w0_phy(tp, 0x03, 0x0000, 0xe000);

	/* Switching regulator Slew rate */
	rtl_writephy(tp, 0x1f, 0x0002);
	rtl_patchphy(tp, 0x0f, 0x0017);

	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x001b);

	rtl_apply_firmware_cond(tp, MII_EXPANSION, 0xb300);

	rtl_writephy(tp, 0x1f, 0x0000);
}

static void rtl8168d_3_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		{ 0x1f, 0x0002 },
		{ 0x10, 0x0008 },
		{ 0x0d, 0x006c },

		{ 0x1f, 0x0000 },
		{ 0x0d, 0xf880 },

		{ 0x1f, 0x0001 },
		{ 0x17, 0x0cc0 },

		{ 0x1f, 0x0001 },
		{ 0x0b, 0xa4d8 },
		{ 0x09, 0x281c },
		{ 0x07, 0x2883 },
		{ 0x0a, 0x6b35 },
		{ 0x1d, 0x3da4 },
		{ 0x1c, 0xeffd },
		{ 0x14, 0x7f52 },
		{ 0x18, 0x7fc6 },
		{ 0x08, 0x0601 },
		{ 0x06, 0x4063 },
		{ 0x10, 0xf074 },
		{ 0x1f, 0x0003 },
		{ 0x13, 0x0789 },
		{ 0x12, 0xf4bd },
		{ 0x1a, 0x04fd },
		{ 0x14, 0x84b0 },
		{ 0x1f, 0x0000 },
		{ 0x00, 0x9200 },

		{ 0x1f, 0x0005 },
		{ 0x01, 0x0340 },
		{ 0x1f, 0x0001 },
		{ 0x04, 0x4000 },
		{ 0x03, 0x1d21 },
		{ 0x02, 0x0c32 },
		{ 0x01, 0x0200 },
		{ 0x00, 0x5554 },
		{ 0x04, 0x4800 },
		{ 0x04, 0x4000 },
		{ 0x04, 0xf000 },
		{ 0x03, 0xdf01 },
		{ 0x02, 0xdf20 },
		{ 0x01, 0x101a },
		{ 0x00, 0xa0ff },
		{ 0x04, 0xf800 },
		{ 0x04, 0xf000 },
		{ 0x1f, 0x0000 },

		{ 0x1f, 0x0007 },
		{ 0x1e, 0x0023 },
		{ 0x16, 0x0000 },
		{ 0x1f, 0x0000 }
	};

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));
}

static void rtl8168d_4_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		{ 0x1f, 0x0001 },
		{ 0x17, 0x0cc0 },

		{ 0x1f, 0x0007 },
		{ 0x1e, 0x002d },
		{ 0x18, 0x0040 },
		{ 0x1f, 0x0000 }
	};

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));
	rtl_patchphy(tp, 0x0d, 1 << 5);
}

static void rtl8168e_1_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		/* Enable Delay cap */
		{ 0x1f, 0x0005 },
		{ 0x05, 0x8b80 },
		{ 0x06, 0xc896 },
		{ 0x1f, 0x0000 },

		/* Channel estimation fine tune */
		{ 0x1f, 0x0001 },
		{ 0x0b, 0x6c20 },
		{ 0x07, 0x2872 },
		{ 0x1c, 0xefff },
		{ 0x1f, 0x0003 },
		{ 0x14, 0x6420 },
		{ 0x1f, 0x0000 },

		/* Update PFM & 10M TX idle timer */
		{ 0x1f, 0x0007 },
		{ 0x1e, 0x002f },
		{ 0x15, 0x1919 },
		{ 0x1f, 0x0000 },

		{ 0x1f, 0x0007 },
		{ 0x1e, 0x00ac },
		{ 0x18, 0x0006 },
		{ 0x1f, 0x0000 }
	};

	rtl_apply_firmware(tp);

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));

	/* DCO enable for 10M IDLE Power */
	rtl_writephy(tp, 0x1f, 0x0007);
	rtl_writephy(tp, 0x1e, 0x0023);
	rtl_w1w0_phy(tp, 0x17, 0x0006, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* For impedance matching */
	rtl_writephy(tp, 0x1f, 0x0002);
	rtl_w1w0_phy(tp, 0x08, 0x8000, 0x7f00);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* PHY auto speed down */
	rtl_writephy(tp, 0x1f, 0x0007);
	rtl_writephy(tp, 0x1e, 0x002d);
	rtl_w1w0_phy(tp, 0x18, 0x0050, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);
	rtl_w1w0_phy(tp, 0x14, 0x8000, 0x0000);

	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b86);
	rtl_w1w0_phy(tp, 0x06, 0x0001, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b85);
	rtl_w1w0_phy(tp, 0x06, 0x0000, 0x2000);
	rtl_writephy(tp, 0x1f, 0x0007);
	rtl_writephy(tp, 0x1e, 0x0020);
	rtl_w1w0_phy(tp, 0x15, 0x0000, 0x1100);
	rtl_writephy(tp, 0x1f, 0x0006);
	rtl_writephy(tp, 0x00, 0x5a00);
	rtl_writephy(tp, 0x1f, 0x0000);
	rtl_writephy(tp, 0x0d, 0x0007);
	rtl_writephy(tp, 0x0e, 0x003c);
	rtl_writephy(tp, 0x0d, 0x4007);
	rtl_writephy(tp, 0x0e, 0x0000);
	rtl_writephy(tp, 0x0d, 0x0000);
}

static void rtl_rar_exgmac_set(struct rtl8169_private *tp, u8 *addr)
{
	const u16 w[] = {
		addr[0] | (addr[1] << 8),
		addr[2] | (addr[3] << 8),
		addr[4] | (addr[5] << 8)
	};
	const struct exgmac_reg e[] = {
		{ .addr = 0xe0, ERIAR_MASK_1111, .val = w[0] | (w[1] << 16) },
		{ .addr = 0xe4, ERIAR_MASK_1111, .val = w[2] },
		{ .addr = 0xf0, ERIAR_MASK_1111, .val = w[0] << 16 },
		{ .addr = 0xf4, ERIAR_MASK_1111, .val = w[1] | (w[2] << 16) }
	};

	rtl_write_exgmac_batch(tp, e, ARRAY_SIZE(e));
}

static void rtl8168e_2_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		/* Enable Delay cap */
		{ 0x1f, 0x0004 },
		{ 0x1f, 0x0007 },
		{ 0x1e, 0x00ac },
		{ 0x18, 0x0006 },
		{ 0x1f, 0x0002 },
		{ 0x1f, 0x0000 },
		{ 0x1f, 0x0000 },

		/* Channel estimation fine tune */
		{ 0x1f, 0x0003 },
		{ 0x09, 0xa20f },
		{ 0x1f, 0x0000 },
		{ 0x1f, 0x0000 },

		/* Green Setting */
		{ 0x1f, 0x0005 },
		{ 0x05, 0x8b5b },
		{ 0x06, 0x9222 },
		{ 0x05, 0x8b6d },
		{ 0x06, 0x8000 },
		{ 0x05, 0x8b76 },
		{ 0x06, 0x8000 },
		{ 0x1f, 0x0000 }
	};

	rtl_apply_firmware(tp);

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));

	/* For 4-corner performance improve */
	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b80);
	rtl_w1w0_phy(tp, 0x17, 0x0006, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* PHY auto speed down */
	rtl_writephy(tp, 0x1f, 0x0004);
	rtl_writephy(tp, 0x1f, 0x0007);
	rtl_writephy(tp, 0x1e, 0x002d);
	rtl_w1w0_phy(tp, 0x18, 0x0010, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0002);
	rtl_writephy(tp, 0x1f, 0x0000);
	rtl_w1w0_phy(tp, 0x14, 0x8000, 0x0000);

	/* improve 10M EEE waveform */
	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b86);
	rtl_w1w0_phy(tp, 0x06, 0x0001, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* Improve 2-pair detection performance */
	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b85);
	rtl_w1w0_phy(tp, 0x06, 0x4000, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* EEE setting */
	rtl_w1w0_eri(tp, 0x1b0, ERIAR_MASK_1111, 0x0000, 0x0003, ERIAR_EXGMAC);
	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b85);
	rtl_w1w0_phy(tp, 0x06, 0x0000, 0x2000);
	rtl_writephy(tp, 0x1f, 0x0004);
	rtl_writephy(tp, 0x1f, 0x0007);
	rtl_writephy(tp, 0x1e, 0x0020);
	rtl_w1w0_phy(tp, 0x15, 0x0000, 0x0100);
	rtl_writephy(tp, 0x1f, 0x0002);
	rtl_writephy(tp, 0x1f, 0x0000);
	rtl_writephy(tp, 0x0d, 0x0007);
	rtl_writephy(tp, 0x0e, 0x003c);
	rtl_writephy(tp, 0x0d, 0x4007);
	rtl_writephy(tp, 0x0e, 0x0000);
	rtl_writephy(tp, 0x0d, 0x0000);

	/* Green feature */
	rtl_writephy(tp, 0x1f, 0x0003);
	rtl_w1w0_phy(tp, 0x19, 0x0000, 0x0001);
	rtl_w1w0_phy(tp, 0x10, 0x0000, 0x0400);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* Broken BIOS workaround: feed GigaMAC registers with MAC address. */
	rtl_rar_exgmac_set(tp, tp->dev->dev_addr);
}

static void rtl8168f_hw_phy_config(struct rtl8169_private *tp)
{
	/* For 4-corner performance improve */
	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b80);
	rtl_w1w0_phy(tp, 0x06, 0x0006, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* PHY auto speed down */
	rtl_writephy(tp, 0x1f, 0x0007);
	rtl_writephy(tp, 0x1e, 0x002d);
	rtl_w1w0_phy(tp, 0x18, 0x0010, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);
	rtl_w1w0_phy(tp, 0x14, 0x8000, 0x0000);

	/* Improve 10M EEE waveform */
	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b86);
	rtl_w1w0_phy(tp, 0x06, 0x0001, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);
}

static void rtl8168f_1_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		/* Channel estimation fine tune */
		{ 0x1f, 0x0003 },
		{ 0x09, 0xa20f },
		{ 0x1f, 0x0000 },

		/* Modify green table for giga & fnet */
		{ 0x1f, 0x0005 },
		{ 0x05, 0x8b55 },
		{ 0x06, 0x0000 },
		{ 0x05, 0x8b5e },
		{ 0x06, 0x0000 },
		{ 0x05, 0x8b67 },
		{ 0x06, 0x0000 },
		{ 0x05, 0x8b70 },
		{ 0x06, 0x0000 },
		{ 0x1f, 0x0000 },
		{ 0x1f, 0x0007 },
		{ 0x1e, 0x0078 },
		{ 0x17, 0x0000 },
		{ 0x19, 0x00fb },
		{ 0x1f, 0x0000 },

		/* Modify green table for 10M */
		{ 0x1f, 0x0005 },
		{ 0x05, 0x8b79 },
		{ 0x06, 0xaa00 },
		{ 0x1f, 0x0000 },

		/* Disable hiimpedance detection (RTCT) */
		{ 0x1f, 0x0003 },
		{ 0x01, 0x328a },
		{ 0x1f, 0x0000 }
	};

	rtl_apply_firmware(tp);

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));

	rtl8168f_hw_phy_config(tp);

	/* Improve 2-pair detection performance */
	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b85);
	rtl_w1w0_phy(tp, 0x06, 0x4000, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);
}

static void rtl8168f_2_hw_phy_config(struct rtl8169_private *tp)
{
	rtl_apply_firmware(tp);

	rtl8168f_hw_phy_config(tp);
}

static void rtl8411_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		/* Channel estimation fine tune */
		{ 0x1f, 0x0003 },
		{ 0x09, 0xa20f },
		{ 0x1f, 0x0000 },

		/* Modify green table for giga & fnet */
		{ 0x1f, 0x0005 },
		{ 0x05, 0x8b55 },
		{ 0x06, 0x0000 },
		{ 0x05, 0x8b5e },
		{ 0x06, 0x0000 },
		{ 0x05, 0x8b67 },
		{ 0x06, 0x0000 },
		{ 0x05, 0x8b70 },
		{ 0x06, 0x0000 },
		{ 0x1f, 0x0000 },
		{ 0x1f, 0x0007 },
		{ 0x1e, 0x0078 },
		{ 0x17, 0x0000 },
		{ 0x19, 0x00aa },
		{ 0x1f, 0x0000 },

		/* Modify green table for 10M */
		{ 0x1f, 0x0005 },
		{ 0x05, 0x8b79 },
		{ 0x06, 0xaa00 },
		{ 0x1f, 0x0000 },

		/* Disable hiimpedance detection (RTCT) */
		{ 0x1f, 0x0003 },
		{ 0x01, 0x328a },
		{ 0x1f, 0x0000 }
	};


	rtl_apply_firmware(tp);

	rtl8168f_hw_phy_config(tp);

	/* Improve 2-pair detection performance */
	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b85);
	rtl_w1w0_phy(tp, 0x06, 0x4000, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));

	/* Modify green table for giga */
	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b54);
	rtl_w1w0_phy(tp, 0x06, 0x0000, 0x0800);
	rtl_writephy(tp, 0x05, 0x8b5d);
	rtl_w1w0_phy(tp, 0x06, 0x0000, 0x0800);
	rtl_writephy(tp, 0x05, 0x8a7c);
	rtl_w1w0_phy(tp, 0x06, 0x0000, 0x0100);
	rtl_writephy(tp, 0x05, 0x8a7f);
	rtl_w1w0_phy(tp, 0x06, 0x0100, 0x0000);
	rtl_writephy(tp, 0x05, 0x8a82);
	rtl_w1w0_phy(tp, 0x06, 0x0000, 0x0100);
	rtl_writephy(tp, 0x05, 0x8a85);
	rtl_w1w0_phy(tp, 0x06, 0x0000, 0x0100);
	rtl_writephy(tp, 0x05, 0x8a88);
	rtl_w1w0_phy(tp, 0x06, 0x0000, 0x0100);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* uc same-seed solution */
	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b85);
	rtl_w1w0_phy(tp, 0x06, 0x8000, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* eee setting */
	rtl_w1w0_eri(tp, 0x1b0, ERIAR_MASK_0001, 0x00, 0x03, ERIAR_EXGMAC);
	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b85);
	rtl_w1w0_phy(tp, 0x06, 0x0000, 0x2000);
	rtl_writephy(tp, 0x1f, 0x0004);
	rtl_writephy(tp, 0x1f, 0x0007);
	rtl_writephy(tp, 0x1e, 0x0020);
	rtl_w1w0_phy(tp, 0x15, 0x0000, 0x0100);
	rtl_writephy(tp, 0x1f, 0x0000);
	rtl_writephy(tp, 0x0d, 0x0007);
	rtl_writephy(tp, 0x0e, 0x003c);
	rtl_writephy(tp, 0x0d, 0x4007);
	rtl_writephy(tp, 0x0e, 0x0000);
	rtl_writephy(tp, 0x0d, 0x0000);

	/* Green feature */
	rtl_writephy(tp, 0x1f, 0x0003);
	rtl_w1w0_phy(tp, 0x19, 0x0000, 0x0001);
	rtl_w1w0_phy(tp, 0x10, 0x0000, 0x0400);
	rtl_writephy(tp, 0x1f, 0x0000);
}

static void rtl8168g_1_hw_phy_config(struct rtl8169_private *tp)
{
	rtl_apply_firmware(tp);

	rtl_writephy(tp, 0x1f, 0x0a46);
	if (rtl_readphy(tp, 0x10) & 0x0100) {
		rtl_writephy(tp, 0x1f, 0x0bcc);
		rtl_w1w0_phy(tp, 0x12, 0x0000, 0x8000);
	} else {
		rtl_writephy(tp, 0x1f, 0x0bcc);
		rtl_w1w0_phy(tp, 0x12, 0x8000, 0x0000);
	}

	rtl_writephy(tp, 0x1f, 0x0a46);
	if (rtl_readphy(tp, 0x13) & 0x0100) {
		rtl_writephy(tp, 0x1f, 0x0c41);
		rtl_w1w0_phy(tp, 0x15, 0x0002, 0x0000);
	} else {
		rtl_writephy(tp, 0x1f, 0x0c41);
		rtl_w1w0_phy(tp, 0x15, 0x0000, 0x0002);
	}

	/* Enable PHY auto speed down */
	rtl_writephy(tp, 0x1f, 0x0a44);
	rtl_w1w0_phy(tp, 0x11, 0x000c, 0x0000);

	rtl_writephy(tp, 0x1f, 0x0bcc);
	rtl_w1w0_phy(tp, 0x14, 0x0100, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0a44);
	rtl_w1w0_phy(tp, 0x11, 0x00c0, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0a43);
	rtl_writephy(tp, 0x13, 0x8084);
	rtl_w1w0_phy(tp, 0x14, 0x0000, 0x6000);
	rtl_w1w0_phy(tp, 0x10, 0x1003, 0x0000);

	/* EEE auto-fallback function */
	rtl_writephy(tp, 0x1f, 0x0a4b);
	rtl_w1w0_phy(tp, 0x11, 0x0004, 0x0000);

	/* Enable UC LPF tune function */
	rtl_writephy(tp, 0x1f, 0x0a43);
	rtl_writephy(tp, 0x13, 0x8012);
	rtl_w1w0_phy(tp, 0x14, 0x8000, 0x0000);

	rtl_writephy(tp, 0x1f, 0x0c42);
	rtl_w1w0_phy(tp, 0x11, 0x4000, 0x2000);

	/* Improve SWR Efficiency */
	rtl_writephy(tp, 0x1f, 0x0bcd);
	rtl_writephy(tp, 0x14, 0x5065);
	rtl_writephy(tp, 0x14, 0xd065);
	rtl_writephy(tp, 0x1f, 0x0bc8);
	rtl_writephy(tp, 0x11, 0x5655);
	rtl_writephy(tp, 0x1f, 0x0bcd);
	rtl_writephy(tp, 0x14, 0x1065);
	rtl_writephy(tp, 0x14, 0x9065);
	rtl_writephy(tp, 0x14, 0x1065);

	/* Check ALDPS bit, disable it if enabled */
	rtl_writephy(tp, 0x1f, 0x0a43);
	if (rtl_readphy(tp, 0x10) & 0x0004)
		rtl_w1w0_phy(tp, 0x10, 0x0000, 0x0004);

	rtl_writephy(tp, 0x1f, 0x0000);
}

static void rtl8168g_2_hw_mac_mcu_patch(struct rtl8169_private *tp)
{
	#if defined(CONFIG_ARCH_RTD129x)
	unsigned int tmp;
	unsigned int cpu_revision;
	void __iomem *rgmii0_addr, *tmp_addr;
	#endif /* CONFIG_ARCH_RTD129x */

	MDIO_LOCK;
	/* power down PHY */
	rtl_writephy(tp, 0x1f, 0x0000);
	rtl_patchphy(tp, MII_BMCR, BMCR_PDOWN);
	MDIO_UNLOCK;

	#if defined(CONFIG_ARCH_RTD129x)
	// mac mcu patch from Tenno to support EEE/EEE+
	cpu_revision = get_rtd129x_cpu_revision();
	if ((cpu_revision == RTD129x_CHIP_REVISION_A00) ||
		(cpu_revision == RTD129x_CHIP_REVISION_A01) ||
		(cpu_revision >= RTD129x_CHIP_REVISION_B00)) {
		// disable break point
		r8169soc_ocp_reg_write(tp, 0xfc28, 0);
		r8169soc_ocp_reg_write(tp, 0xfc2a, 0);
		r8169soc_ocp_reg_write(tp, 0xfc2c, 0);
		r8169soc_ocp_reg_write(tp, 0xfc2e, 0);
		r8169soc_ocp_reg_write(tp, 0xfc30, 0);
		r8169soc_ocp_reg_write(tp, 0xfc32, 0);
		r8169soc_ocp_reg_write(tp, 0xfc34, 0);
		r8169soc_ocp_reg_write(tp, 0xfc36, 0);
		mdelay(3);

		// disable base address
		r8169soc_ocp_reg_write(tp, 0xfc26, 0);

		// patch code
		r8169soc_ocp_reg_write(tp, 0xf800, 0xE008);
		r8169soc_ocp_reg_write(tp, 0xf802, 0xE012);
		r8169soc_ocp_reg_write(tp, 0xf804, 0xE044);
		r8169soc_ocp_reg_write(tp, 0xf806, 0xE046);
		r8169soc_ocp_reg_write(tp, 0xf808, 0xE048);
		r8169soc_ocp_reg_write(tp, 0xf80a, 0xE04A);
		r8169soc_ocp_reg_write(tp, 0xf80c, 0xE04C);
		r8169soc_ocp_reg_write(tp, 0xf80e, 0xE04E);
		r8169soc_ocp_reg_write(tp, 0xf810, 0x44E3);
		r8169soc_ocp_reg_write(tp, 0xf812, 0xC708);
		r8169soc_ocp_reg_write(tp, 0xf814, 0x75E0);
		r8169soc_ocp_reg_write(tp, 0xf816, 0x485D);
		r8169soc_ocp_reg_write(tp, 0xf818, 0x9DE0);
		r8169soc_ocp_reg_write(tp, 0xf81a, 0xC705);
		r8169soc_ocp_reg_write(tp, 0xf81c, 0xC502);
		r8169soc_ocp_reg_write(tp, 0xf81e, 0xBD00);
		r8169soc_ocp_reg_write(tp, 0xf820, 0x01EE);
		r8169soc_ocp_reg_write(tp, 0xf822, 0xE85A);
		r8169soc_ocp_reg_write(tp, 0xf824, 0xE000);
		r8169soc_ocp_reg_write(tp, 0xf826, 0xC72D);
		r8169soc_ocp_reg_write(tp, 0xf828, 0x76E0);
		r8169soc_ocp_reg_write(tp, 0xf82a, 0x49ED);
		r8169soc_ocp_reg_write(tp, 0xf82c, 0xF026);
		r8169soc_ocp_reg_write(tp, 0xf82e, 0xC02A);
		r8169soc_ocp_reg_write(tp, 0xf830, 0x7400);
		r8169soc_ocp_reg_write(tp, 0xf832, 0xC526);
		r8169soc_ocp_reg_write(tp, 0xf834, 0xC228);
		r8169soc_ocp_reg_write(tp, 0xf836, 0x9AA0);
		r8169soc_ocp_reg_write(tp, 0xf838, 0x73A2);
		r8169soc_ocp_reg_write(tp, 0xf83a, 0x49BE);
		r8169soc_ocp_reg_write(tp, 0xf83c, 0xF11E);
		r8169soc_ocp_reg_write(tp, 0xf83e, 0xC324);
		r8169soc_ocp_reg_write(tp, 0xf840, 0x9BA2);
		r8169soc_ocp_reg_write(tp, 0xf842, 0x73A2);
		r8169soc_ocp_reg_write(tp, 0xf844, 0x49BE);
		r8169soc_ocp_reg_write(tp, 0xf846, 0xF0FE);
		r8169soc_ocp_reg_write(tp, 0xf848, 0x73A2);
		r8169soc_ocp_reg_write(tp, 0xf84a, 0x49BE);
		r8169soc_ocp_reg_write(tp, 0xf84c, 0xF1FE);
		r8169soc_ocp_reg_write(tp, 0xf84e, 0x1A02);
		r8169soc_ocp_reg_write(tp, 0xf850, 0x49C9);
		r8169soc_ocp_reg_write(tp, 0xf852, 0xF003);
		r8169soc_ocp_reg_write(tp, 0xf854, 0x4821);
		r8169soc_ocp_reg_write(tp, 0xf856, 0xE002);
		r8169soc_ocp_reg_write(tp, 0xf858, 0x48A1);
		r8169soc_ocp_reg_write(tp, 0xf85a, 0x73A2);
		r8169soc_ocp_reg_write(tp, 0xf85c, 0x49BE);
		r8169soc_ocp_reg_write(tp, 0xf85e, 0xF10D);
		r8169soc_ocp_reg_write(tp, 0xf860, 0xC313);
		r8169soc_ocp_reg_write(tp, 0xf862, 0x9AA0);
		r8169soc_ocp_reg_write(tp, 0xf864, 0xC312);
		r8169soc_ocp_reg_write(tp, 0xf866, 0x9BA2);
		r8169soc_ocp_reg_write(tp, 0xf868, 0x73A2);
		r8169soc_ocp_reg_write(tp, 0xf86a, 0x49BE);
		r8169soc_ocp_reg_write(tp, 0xf86c, 0xF0FE);
		r8169soc_ocp_reg_write(tp, 0xf86e, 0x73A2);
		r8169soc_ocp_reg_write(tp, 0xf870, 0x49BE);
		r8169soc_ocp_reg_write(tp, 0xf872, 0xF1FE);
		r8169soc_ocp_reg_write(tp, 0xf874, 0x48ED);
		r8169soc_ocp_reg_write(tp, 0xf876, 0x9EE0);
		r8169soc_ocp_reg_write(tp, 0xf878, 0xC602);
		r8169soc_ocp_reg_write(tp, 0xf87a, 0xBE00);
		r8169soc_ocp_reg_write(tp, 0xf87c, 0x0532);
		r8169soc_ocp_reg_write(tp, 0xf87e, 0xDE00);
		r8169soc_ocp_reg_write(tp, 0xf880, 0xE85A);
		r8169soc_ocp_reg_write(tp, 0xf882, 0xE086);
		r8169soc_ocp_reg_write(tp, 0xf884, 0x0A44);
		r8169soc_ocp_reg_write(tp, 0xf886, 0x801F);
		r8169soc_ocp_reg_write(tp, 0xf888, 0x8015);
		r8169soc_ocp_reg_write(tp, 0xf88a, 0x0015);
		r8169soc_ocp_reg_write(tp, 0xf88c, 0xC602);
		r8169soc_ocp_reg_write(tp, 0xf88e, 0xBE00);
		r8169soc_ocp_reg_write(tp, 0xf890, 0x0000);
		r8169soc_ocp_reg_write(tp, 0xf892, 0xC602);
		r8169soc_ocp_reg_write(tp, 0xf894, 0xBE00);
		r8169soc_ocp_reg_write(tp, 0xf896, 0x0000);
		r8169soc_ocp_reg_write(tp, 0xf898, 0xC602);
		r8169soc_ocp_reg_write(tp, 0xf89a, 0xBE00);
		r8169soc_ocp_reg_write(tp, 0xf89c, 0x0000);
		r8169soc_ocp_reg_write(tp, 0xf89e, 0xC602);
		r8169soc_ocp_reg_write(tp, 0xf8a0, 0xBE00);
		r8169soc_ocp_reg_write(tp, 0xf8a2, 0x0000);
		r8169soc_ocp_reg_write(tp, 0xf8a4, 0xC602);
		r8169soc_ocp_reg_write(tp, 0xf8a6, 0xBE00);
		r8169soc_ocp_reg_write(tp, 0xf8a8, 0x0000);
		r8169soc_ocp_reg_write(tp, 0xf8aa, 0xC602);
		r8169soc_ocp_reg_write(tp, 0xf8ac, 0xBE00);
		r8169soc_ocp_reg_write(tp, 0xf8ae, 0x0000);

		// enable base address
		r8169soc_ocp_reg_write(tp, 0xfc26, 0x8000);

		// enable breakpoint
		r8169soc_ocp_reg_write(tp, 0xfc28, 0x01ED);
		r8169soc_ocp_reg_write(tp, 0xfc2a, 0x0531);

		if (tp->eee_enable) {
			/* EEE MAC mode */
			r8169soc_ocp_reg_write(tp, 0xe040, (r8169soc_ocp_reg_read(tp, 0xe040) | (BIT(1) | BIT(0))));
			/* EEE+ MAC mode */
			r8169soc_ocp_reg_write(tp, 0xe080, (r8169soc_ocp_reg_read(tp, 0xe080) | BIT(1)));
		}
	}

	if ((cpu_revision >= RTD129x_CHIP_REVISION_B00)) {
		if (tp->output_mode == OUTPUT_EMBEDDED_PHY) {
			tmp = r8169soc_ocp_reg_read(tp, 0xea34) & ~(BIT(0) | BIT(1));
			tmp |= BIT(1); // MII
			r8169soc_ocp_reg_write(tp, 0xea34, tmp);
		} else { /* RGMII */
			if (tp->output_mode == OUTPUT_RGMII_TO_PHY) {
				//# ETN spec, MDC freq=2.5MHz
				r8169soc_ocp_reg_write(tp, 0xde30, (r8169soc_ocp_reg_read(tp, 0xde30) & ~(BIT(6) | BIT(7))));
				//# ETN spec, set external PHY addr
				r8169soc_ocp_reg_write(tp, 0xde24,
					(r8169soc_ocp_reg_read(tp, 0xde24) & ~(0x1F)) | (tp->ext_phy_id & 0x1F));
			}

			tmp = r8169soc_ocp_reg_read(tp, 0xea34) & ~(BIT(0) | BIT(1));
			tmp |= BIT(0); // RGMII

			if (tp->output_mode == OUTPUT_RGMII_TO_MAC) {
				tmp &= ~(BIT(3) | BIT(4));
				tmp |= BIT(4); // speed: 1G
				tmp |= BIT(2); // full duplex
			}
			if (tp->rgmii_rx_delay == RGMII_DELAY_0NS)
				tmp &= ~BIT(6);
			else
				tmp |= BIT(6);

			if (tp->rgmii_tx_delay == RGMII_DELAY_0NS)
				tmp &= ~BIT(7);
			else
				tmp |= BIT(7);

			r8169soc_ocp_reg_write(tp, 0xea34, tmp);

			/* adjust RGMII voltage */
			rgmii0_addr = ioremap(RGMII0_PAD_CTRL_ADDR, 12);
			switch(tp->rgmii_voltage) {
			case VOLTAGE_1_DOT_8V:
				writel(0, rgmii0_addr);
				writel(0x44444444, rgmii0_addr + 4);
				writel(0x24444444, rgmii0_addr + 8);
				break;
			case VOLTAGE_2_DOT_5V:
				writel(0, rgmii0_addr);
				writel(0x44444444, rgmii0_addr + 4);
				writel(0x64444444, rgmii0_addr + 8);
				break;
			case VOLTAGE_3_DOT_3V:
				writel(0x3F, rgmii0_addr);
				writel(0, rgmii0_addr + 4);
				writel(0xA4000000, rgmii0_addr + 8);
			}
			__iounmap(rgmii0_addr);

			/* switch RGMII/MDIO to GMAC */
			tmp_addr = ioremap(ISO_RGMII_MDIO_TO_GMAC, 4);
			writel((readl(tmp_addr) | BIT(1)), tmp_addr);
			__iounmap(tmp_addr);

			if (tp->output_mode == OUTPUT_RGMII_TO_MAC) {
				/* force GMAC link up */
				r8169soc_ocp_reg_write(tp, 0xde40, 0x30EC);
				/* ignore mac_intr from PHY */
				r8169soc_ocp_reg_write(tp, 0xfc1e, (r8169soc_ocp_reg_read(tp, 0xfc1e) & ~BIT(1)));
			}
		}
	}
	#endif /* CONFIG_ARCH_RTD129x */

}

static void rtl8168g_2_hw_phy_config(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	/* set dis_mcu_clroob to avoid WOL fail when ALDPS mode is enabled */
	RTL_W8(MCU, RTL_R8(MCU) | DIS_MCU_CLROOB);
	#if defined(CONFIG_ARCH_RTD129x)
	/* enable ALDPS mode */
	rtl_writephy(tp, 0x1f, 0x0a43);
	rtl_w1w0_phy(tp, 0x18, BIT(2), BIT(12) | BIT(1) | BIT(0));

	/* enable EEE of 10Mbps */
	rtl_writephy(tp, 0x1f, 0x0a43);
	rtl_patchphy(tp, 0x19, (1 << 4));
	#elif defined(CONFIG_ARCH_RTD139x)
	#endif /* CONFIG_ARCH_RTD129x | CONFIG_ARCH_RTD139x */

	//	rtl_apply_firmware(tp);
	// gphy patch from Riri   	add by yukuen
/*	if (soc_is_rtk1195()) {
		if ((realtek_rev() == RTK1195_REV_A)) {
			// disable green
			rtl_writephy(tp, 0x1f, 0x0A43);
			rtl_writephy(tp, 0x1b, 0x8011);
			rtl_writephy(tp, 0x1c, 0x1737);   //disable green

			rtl_writephy(tp, 0x1f, 0x0BCC);
			rtl_writephy(tp, 0x11, 0x4444);	  //write abiq /ldvbias

			// R/ RC auto k
			rtl_writephy(tp, 0x1f, 0x0A43);
			rtl_writephy(tp, 0x1b, 0x8013);
			rtl_writephy(tp, 0x1c, 0x0F08);   //default ff08  disable auto k RC/R

			rtl_writephy(tp, 0x1f, 0x0BCE);   //force tapbin = 4
			rtl_writephy(tp, 0x10, 0x4444);

			rtl_writephy(tp, 0x1f, 0x0BCD);
			rtl_writephy(tp, 0x17, 0x8888);		//tx rc
			rtl_writephy(tp, 0x16, 0x9999);		//rx rc

			// increase sd thd
			rtl_writephy(tp, 0x1f, 0x0A43);
			rtl_writephy(tp, 0x1b, 0x8101);
			rtl_writephy(tp, 0x1c, 0x3E00);   //master sd  : 0x1e00

			rtl_writephy(tp, 0x1f, 0x0A43);
			rtl_writephy(tp, 0x1b, 0x80E2);
			rtl_writephy(tp, 0x1c, 0x3E00);   //default sd  : 0x0e00

			rtl_writephy(tp, 0x1f, 0x0A43);
			rtl_writephy(tp, 0x1b, 0x8120);
			rtl_writephy(tp, 0x1c, 0x3E00);   //slave sd  : 0x0e00
		}
		else {	// REV_B
			//#GDAC updown
			rtl_writephy(tp, 0x1f, 0x0BCC);
			rtl_writephy(tp, 0x12, 0x00BE);

			//R_RC
			rtl_writephy(tp, 0x1f, 0x0A43);
			rtl_writephy(tp, 0x1b, 0x81DE);
			rtl_writephy(tp, 0x1c, 0xFDFE);     //#  fbfe [15:8] tapbin tx -3 #  [7:0] tapbin rx -2

			rtl_writephy(tp, 0x1b, 0x81E0);
			rtl_writephy(tp, 0x1c, 0xFDFF);     //#  [15:8] rlen  -3

			rtl_writephy(tp, 0x1b, 0x81E2);
			rtl_writephy(tp, 0x1c, 0x0400);     //#  [15:8] rlen_100 +4, -3+4=1
			rtl_writephy(tp, 0x1b, 0x80d3);
			rtl_writephy(tp, 0x1c, 0x04a4);     //# fnet cable length constant 0aa4

			rtl_writephy(tp, 0x1b, 0x8111);
			rtl_writephy(tp, 0x1c, 0x0a7f);     //# slave cable length constant fa7f

			rtl_writephy(tp, 0x1b, 0x810d);
			rtl_writephy(tp, 0x1c, 0x5604);     //# slave const dagc 0606

			rtl_writephy(tp, 0x1b, 0x80f4);
			rtl_writephy(tp, 0x1c, 0x5df7);     //# master cable length delta 3df7

			rtl_writephy(tp, 0x1b, 0x80f2);
			rtl_writephy(tp, 0x1c, 0x0a8f);     //# master cable length constant fa8f

			rtl_writephy(tp, 0x1b, 0x80f6);
			rtl_writephy(tp, 0x1c, 0x54ca);     //# master delta dagc 63ca

			rtl_writephy(tp, 0x1b, 0x80ec);
			rtl_writephy(tp, 0x1c, 0x007c);     //# master aagc 146c

			//disble ALDPS interrupt
			rtl_writephy(tp, 0x1f, 0x0a42);
			rtl_writephy(tp, 0x12, rtl_readphy(tp, 0x12) & ~BIT(9));

			//enable ALDPS
			rtl_writephy(tp, 0x1f, 0x0a43);
			rtl_writephy(tp, 0x10, rtl_readphy(tp, 0x10) | BIT(2));
		}
	}*/
}

static void rtl8102e_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		{ 0x1f, 0x0003 },
		{ 0x08, 0x441d },
		{ 0x01, 0x9100 },
		{ 0x1f, 0x0000 }
	};

	rtl_writephy(tp, 0x1f, 0x0000);
	rtl_patchphy(tp, 0x11, 1 << 12);
	rtl_patchphy(tp, 0x19, 1 << 13);
	rtl_patchphy(tp, 0x10, 1 << 15);

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));
}

static void rtl8105e_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		{ 0x1f, 0x0005 },
		{ 0x1a, 0x0000 },
		{ 0x1f, 0x0000 },

		{ 0x1f, 0x0004 },
		{ 0x1c, 0x0000 },
		{ 0x1f, 0x0000 },

		{ 0x1f, 0x0001 },
		{ 0x15, 0x7701 },
		{ 0x1f, 0x0000 }
	};

	/* Disable ALDPS before ram code */
	rtl_writephy(tp, 0x1f, 0x0000);
	rtl_writephy(tp, 0x18, 0x0310);
	msleep(100);

	rtl_apply_firmware(tp);

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));
}

static void rtl8402_hw_phy_config(struct rtl8169_private *tp)
{
	/* Disable ALDPS before setting firmware */
	rtl_writephy(tp, 0x1f, 0x0000);
	rtl_writephy(tp, 0x18, 0x0310);
	msleep(20);

	rtl_apply_firmware(tp);

	/* EEE setting */
	rtl_eri_write(tp, 0x1b0, ERIAR_MASK_0011, 0x0000, ERIAR_EXGMAC);
	rtl_writephy(tp, 0x1f, 0x0004);
	rtl_writephy(tp, 0x10, 0x401f);
	rtl_writephy(tp, 0x19, 0x7030);
	rtl_writephy(tp, 0x1f, 0x0000);
}

static void rtl8106e_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		{ 0x1f, 0x0004 },
		{ 0x10, 0xc07f },
		{ 0x19, 0x7030 },
		{ 0x1f, 0x0000 }
	};

	/* Disable ALDPS before ram code */
	rtl_writephy(tp, 0x1f, 0x0000);
	rtl_writephy(tp, 0x18, 0x0310);
	msleep(100);

	rtl_apply_firmware(tp);

	rtl_eri_write(tp, 0x1b0, ERIAR_MASK_0011, 0x0000, ERIAR_EXGMAC);
	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));

	rtl_eri_write(tp, 0x1d0, ERIAR_MASK_0011, 0x0000, ERIAR_EXGMAC);
}

static void rtl_hw_phy_config(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	rtl8169_print_mac_version(tp);

	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_01:
		break;
	case RTL_GIGA_MAC_VER_02:
	case RTL_GIGA_MAC_VER_03:
		rtl8169s_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_04:
		rtl8169sb_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_05:
		rtl8169scd_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_06:
		rtl8169sce_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_07:
	case RTL_GIGA_MAC_VER_08:
	case RTL_GIGA_MAC_VER_09:
		rtl8102e_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_11:
		rtl8168bb_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_12:
		rtl8168bef_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_17:
		rtl8168bef_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_18:
		rtl8168cp_1_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_19:
		rtl8168c_1_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_20:
		rtl8168c_2_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_21:
		rtl8168c_3_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_22:
		rtl8168c_4_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_23:
	case RTL_GIGA_MAC_VER_24:
		rtl8168cp_2_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_25:
		rtl8168d_1_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_26:
		rtl8168d_2_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_27:
		rtl8168d_3_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_28:
		rtl8168d_4_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_29:
	case RTL_GIGA_MAC_VER_30:
		rtl8105e_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_31:
		/* None. */
		break;
	case RTL_GIGA_MAC_VER_32:
	case RTL_GIGA_MAC_VER_33:
		rtl8168e_1_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_34:
		rtl8168e_2_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_35:
		rtl8168f_1_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_36:
		rtl8168f_2_hw_phy_config(tp);
		break;

	case RTL_GIGA_MAC_VER_37:
		rtl8402_hw_phy_config(tp);
		break;

	case RTL_GIGA_MAC_VER_38:
		rtl8411_hw_phy_config(tp);
		break;

	case RTL_GIGA_MAC_VER_39:
		rtl8106e_hw_phy_config(tp);
		break;

	case RTL_GIGA_MAC_VER_40:
		rtl8168g_1_hw_phy_config(tp);
		break;
	case RTL_GIGA_MAC_VER_42:
	case RTL_GIGA_MAC_VER_43:
		rtl8168g_2_hw_mac_mcu_patch(tp);
		rtl8168g_2_hw_phy_config(tp);
		break;

	case RTL_GIGA_MAC_VER_41:
	default:
		break;
	}
}

static void rtl_schedule_task(struct rtl8169_private *tp, enum rtl_flag flag)
{
	if (!test_and_set_bit(flag, tp->wk.flags))
		schedule_work(&tp->wk.work);
}

static void rtl_rar_set(struct rtl8169_private *tp, u8 *addr)
{
	void __iomem *ioaddr = tp->mmio_addr;

	rtl_lock_work(tp);

	RTL_W8(Cfg9346, Cfg9346_Unlock);

	RTL_W32(MAC4, addr[4] | addr[5] << 8);
	RTL_R32(MAC4);

	RTL_W32(MAC0, addr[0] | addr[1] << 8 | addr[2] << 16 | addr[3] << 24);
	RTL_R32(MAC0);

	if (tp->mac_version == RTL_GIGA_MAC_VER_34)
		rtl_rar_exgmac_set(tp, addr);

	RTL_W8(Cfg9346, Cfg9346_Lock);

	rtl_unlock_work(tp);
}

static void rtl_phy_work(struct rtl8169_private *tp)
{
	// 1295 remove the patch first
	return;
/*	struct timer_list *timer = &tp->timer;
	void __iomem *ioaddr = tp->mmio_addr;
	unsigned long timeout = RTL8169_PHY_TIMEOUT;
	u32 i,j;
	int gphy_code;
	int gphy_status;
	u32  macaddr1;
	u16  macaddr2;

	macaddr1 = RTL_R32(MAC0);
	macaddr2 = RTL_R16(MAC4);

	if (tp->link_ok(ioaddr))
		return;

	rtl_writephy(tp, 0x1f, 0x0A46);
	gphy_status = rtl_readphy(tp, 0x15);

	rtl_writephy(tp, 0x1b, 0x0002);
	gphy_code=rtl_readphy(tp, 0x1c);

	gphy_status = gphy_status & 0x0F00;
	gphy_status = gphy_status >>8;


	if((gphy_status>=3)&&(gphy_code==0x6329))
	{
		goto out_mod_timer;
	}

	napi_disable(&tp->napi);
	rtl_irq_disable(tp);

	netif_err(tp, drv, tp->dev, "gphy check failed, reset start\n");

	i=readl(IOMEM(0xFE000000));
	i = i & 0xffffbfff;
	writel(i,IOMEM(0xFE000000));

	j=readl(IOMEM(0xFE007088));
	j = j & 0xfffff9ff;
	writel(j,IOMEM(0xFE007088));


	i=readl(IOMEM(0xFE000000));
	i = i | 0x00004000;
	writel(i,IOMEM(0xFE000000));

	j=readl(IOMEM(0xFE007088));
	j = j | 0x00000600;
	writel(j,IOMEM(0xFE007088));

	msleep(300);

	napi_enable(&tp->napi);

	rtl_writephy(tp, 0x1f, 0x0A46);
	gphy_status = rtl_readphy(tp, 0x15);
	gphy_status = gphy_status & 0x0700;
	gphy_status = gphy_status >>8;

	netif_err(tp, drv, tp->dev, "gphy check failed, reset check phystatus=%x\n",gphy_status);

	if(gphy_status>=3)
	{
		// refill addres

		RTL_W8(Cfg9346, Cfg9346_Unlock);
		RTL_W32(MAC0,macaddr1);
		RTL_W16(MAC4,macaddr2);
		RTL_W8(Cfg9346, Cfg9346_Lock);
		netif_err(tp, drv, tp->dev, "gphy check failed, reset complete\n");
		rtl_schedule_task(tp, RTL_FLAG_TASK_RESET_PENDING);
	}

out_mod_timer:
	mod_timer(timer, jiffies + timeout);
*/
}


static void rtl8169_phy_timer(unsigned long __opaque)
{
	struct net_device *dev = (struct net_device *)__opaque;
	struct rtl8169_private *tp = netdev_priv(dev);

	rtl_schedule_task(tp, RTL_FLAG_TASK_PHY_PENDING);
}

static void rtl8169_release_board(struct platform_device *pdev, struct net_device *dev,
				  void __iomem *ioaddr)
{
//	iounmap(ioaddr);
//	pci_release_regions(pdev);
//	pci_clear_mwi(pdev);
//	pci_disable_device(pdev);
	free_netdev(dev);
}

DECLARE_RTL_COND(rtl_phy_reset_cond)
{
	return tp->phy_reset_pending(tp);
}

static void rtl8169_phy_reset(struct net_device *dev,
				  struct rtl8169_private *tp)
{
	tp->phy_reset_enable(tp);
	rtl_msleep_loop_wait_low(tp, &rtl_phy_reset_cond, 1, 100);
}

static bool rtl_tbi_enabled(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	return (tp->mac_version == RTL_GIGA_MAC_VER_01) &&
		(RTL_R8(PHYstatus) & TBI_Enable);
}

static void rtl8169_init_phy(struct net_device *dev, struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	rtl_hw_phy_config(dev);

	if (tp->mac_version <= RTL_GIGA_MAC_VER_06) {
		dprintk("Set MAC Reg C+CR Offset 0x82h = 0x01h\n");
		RTL_W8(0x82, 0x01);
	}

	// disable now is oob
	RTL_W8(MCU, RTL_R8(MCU) & ~NOW_IS_OOB);

//	pci_write_config_byte(tp->pci_dev, PCI_LATENCY_TIMER, 0x40);

//	if (tp->mac_version <= RTL_GIGA_MAC_VER_06)
//		pci_write_config_byte(tp->pci_dev, PCI_CACHE_LINE_SIZE, 0x08);

	if (tp->mac_version == RTL_GIGA_MAC_VER_02) {
		dprintk("Set MAC Reg C+CR Offset 0x82h = 0x01h\n");
		RTL_W8(0x82, 0x01);
		dprintk("Set PHY Reg 0x0bh = 0x00h\n");
		rtl_writephy(tp, 0x0b, 0x0000); //w 0x0b 15 0 0
	}

	rtl8169_phy_reset(dev, tp);

	rtl8169_set_speed(dev, AUTONEG_ENABLE, SPEED_1000, DUPLEX_FULL,
			  ADVERTISED_10baseT_Half | ADVERTISED_10baseT_Full |
			  ADVERTISED_100baseT_Half | ADVERTISED_100baseT_Full |
			  (tp->mii.supports_gmii ?
			   ADVERTISED_1000baseT_Half |
			   ADVERTISED_1000baseT_Full : 0));

	if (rtl_tbi_enabled(tp))
		netif_info(tp, link, dev, "TBI auto-negotiating\n");
}


static int rtl_set_mac_address(struct net_device *dev, void *p)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);

	rtl_rar_set(tp, dev->dev_addr);

	return 0;
}

static int rtl8169_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	struct mii_ioctl_data *data = if_mii(ifr);

	return netif_running(dev) ? tp->do_ioctl(tp, data, cmd) : -ENODEV;
}

static int rtl_xmii_ioctl(struct rtl8169_private *tp,
			  struct mii_ioctl_data *data, int cmd)
{
	switch (cmd) {
	case SIOCGMIIPHY:
		data->phy_id = 32; /* Internal PHY */
		return 0;

	case SIOCGMIIREG:
		data->val_out = rtl_readphy(tp, data->reg_num & 0x1f);
		return 0;

	case SIOCSMIIREG:
		rtl_writephy(tp, data->reg_num & 0x1f, data->val_in);
		return 0;
	}
	return -EOPNOTSUPP;
}

static int rtl_tbi_ioctl(struct rtl8169_private *tp, struct mii_ioctl_data *data, int cmd)
{
	return -EOPNOTSUPP;
}

static __maybe_unused void rtl_disable_msi(struct platform_device *pdev, struct rtl8169_private *tp)
{
//	if (tp->features & RTL_FEATURE_MSI) {
//		pci_disable_msi(pdev);
//		tp->features &= ~RTL_FEATURE_MSI;
//	}
}

static void rtl_init_mdio_ops(struct rtl8169_private *tp)
{
	struct mdio_ops *ops = &tp->mdio_ops;

	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_27:
		ops->write	= r8168dp_1_mdio_write;
		ops->read	= r8168dp_1_mdio_read;
		break;
	case RTL_GIGA_MAC_VER_28:
	case RTL_GIGA_MAC_VER_31:
		ops->write	= r8168dp_2_mdio_write;
		ops->read	= r8168dp_2_mdio_read;
		break;
	case RTL_GIGA_MAC_VER_40:
	case RTL_GIGA_MAC_VER_41:
	case RTL_GIGA_MAC_VER_42:
	case RTL_GIGA_MAC_VER_43:
	//	ops->write	= r8168g_mdio_write;
	//	ops->read	= r8168g_mdio_read;
		ops->write	= r8169_mdio_write;
		ops->read	= r8169_mdio_read;
		break;
	default:
		ops->write	= r8169_mdio_write;
		ops->read	= r8169_mdio_read;
		break;
	}
}

static void rtl_speed_down(struct rtl8169_private *tp)
{
	u32 adv;
	int lpa;

	rtl_writephy(tp, 0x1f, 0x0000);
	lpa = rtl_readphy(tp, MII_LPA);

	if (lpa & (LPA_10HALF | LPA_10FULL))
		adv = ADVERTISED_10baseT_Half | ADVERTISED_10baseT_Full;
	else if (lpa & (LPA_100HALF | LPA_100FULL))
		adv = ADVERTISED_10baseT_Half | ADVERTISED_10baseT_Full |
			  ADVERTISED_100baseT_Half | ADVERTISED_100baseT_Full;
	else
		adv = ADVERTISED_10baseT_Half | ADVERTISED_10baseT_Full |
			  ADVERTISED_100baseT_Half | ADVERTISED_100baseT_Full |
			  (tp->mii.supports_gmii ?
			   ADVERTISED_1000baseT_Half |
			   ADVERTISED_1000baseT_Full : 0);

	rtl8169_set_speed(tp->dev, AUTONEG_ENABLE, SPEED_1000, DUPLEX_FULL,
			  adv);
}

static void rtl_wol_suspend_quirk(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_25:
	case RTL_GIGA_MAC_VER_26:
	case RTL_GIGA_MAC_VER_29:
	case RTL_GIGA_MAC_VER_30:
	case RTL_GIGA_MAC_VER_32:
	case RTL_GIGA_MAC_VER_33:
	case RTL_GIGA_MAC_VER_34:
	case RTL_GIGA_MAC_VER_37:
	case RTL_GIGA_MAC_VER_38:
	case RTL_GIGA_MAC_VER_39:
	case RTL_GIGA_MAC_VER_40:
	case RTL_GIGA_MAC_VER_41:
	case RTL_GIGA_MAC_VER_42:
	case RTL_GIGA_MAC_VER_43:
		RTL_W32(RxConfig, RTL_R32(RxConfig) |
			AcceptBroadcast | AcceptMulticast | AcceptMyPhys);
		break;
	default:
		break;
	}
}

static bool rtl_wol_pll_power_down(struct rtl8169_private *tp)
{
	if (!(__rtl8169_get_wol(tp) & WAKE_ANY))
		return false;

	rtl_speed_down(tp);
	rtl_wol_suspend_quirk(tp);

	return true;
}

static void r810x_phy_power_down(struct rtl8169_private *tp)
{
	rtl_writephy(tp, 0x1f, 0x0000);
	rtl_writephy(tp, MII_BMCR, BMCR_PDOWN);
}

static void r810x_phy_power_up(struct rtl8169_private *tp)
{
	rtl_writephy(tp, 0x1f, 0x0000);
	rtl_writephy(tp, MII_BMCR, BMCR_ANENABLE);
}

static void r810x_pll_power_down(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	if (rtl_wol_pll_power_down(tp))
		return;

	r810x_phy_power_down(tp);

	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_07:
	case RTL_GIGA_MAC_VER_08:
	case RTL_GIGA_MAC_VER_09:
	case RTL_GIGA_MAC_VER_10:
	case RTL_GIGA_MAC_VER_13:
	case RTL_GIGA_MAC_VER_16:
		break;
	default:
		RTL_W8(PMCH, RTL_R8(PMCH) & ~0x80);
		break;
	}
}

static void r810x_pll_power_up(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	r810x_phy_power_up(tp);

	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_07:
	case RTL_GIGA_MAC_VER_08:
	case RTL_GIGA_MAC_VER_09:
	case RTL_GIGA_MAC_VER_10:
	case RTL_GIGA_MAC_VER_13:
	case RTL_GIGA_MAC_VER_16:
		break;
	default:
		RTL_W8(PMCH, RTL_R8(PMCH) | 0x80);
		break;
	}
}

static void r8168_phy_power_up(struct rtl8169_private *tp)
{
	rtl_writephy(tp, 0x1f, 0x0000);
	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_11:
	case RTL_GIGA_MAC_VER_12:
	case RTL_GIGA_MAC_VER_17:
	case RTL_GIGA_MAC_VER_18:
	case RTL_GIGA_MAC_VER_19:
	case RTL_GIGA_MAC_VER_20:
	case RTL_GIGA_MAC_VER_21:
	case RTL_GIGA_MAC_VER_22:
	case RTL_GIGA_MAC_VER_23:
	case RTL_GIGA_MAC_VER_24:
	case RTL_GIGA_MAC_VER_25:
	case RTL_GIGA_MAC_VER_26:
	case RTL_GIGA_MAC_VER_27:
	case RTL_GIGA_MAC_VER_28:
	case RTL_GIGA_MAC_VER_31:
		rtl_writephy(tp, 0x0e, 0x0000);
		break;
	default:
		break;
	}
	rtl_writephy(tp, MII_BMCR, BMCR_ANENABLE);
}

static void r8168_phy_power_down(struct rtl8169_private *tp)
{
	rtl_writephy(tp, 0x1f, 0x0000);
	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_32:
	case RTL_GIGA_MAC_VER_33:
	case RTL_GIGA_MAC_VER_40:
	case RTL_GIGA_MAC_VER_41:
		rtl_writephy(tp, MII_BMCR, BMCR_ANENABLE | BMCR_PDOWN);
		break;

	case RTL_GIGA_MAC_VER_11:
	case RTL_GIGA_MAC_VER_12:
	case RTL_GIGA_MAC_VER_17:
	case RTL_GIGA_MAC_VER_18:
	case RTL_GIGA_MAC_VER_19:
	case RTL_GIGA_MAC_VER_20:
	case RTL_GIGA_MAC_VER_21:
	case RTL_GIGA_MAC_VER_22:
	case RTL_GIGA_MAC_VER_23:
	case RTL_GIGA_MAC_VER_24:
	case RTL_GIGA_MAC_VER_25:
	case RTL_GIGA_MAC_VER_26:
	case RTL_GIGA_MAC_VER_27:
	case RTL_GIGA_MAC_VER_28:
	case RTL_GIGA_MAC_VER_31:
		rtl_writephy(tp, 0x0e, 0x0200);
	default:
		rtl_writephy(tp, MII_BMCR, BMCR_PDOWN);
		break;
	}
}

static void r8168_pll_power_down(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	if ((tp->mac_version == RTL_GIGA_MAC_VER_27 ||
		 tp->mac_version == RTL_GIGA_MAC_VER_28 ||
		 tp->mac_version == RTL_GIGA_MAC_VER_31) &&
		r8168dp_check_dash(tp)) {
		return;
	}

	if ((tp->mac_version == RTL_GIGA_MAC_VER_23 ||
		 tp->mac_version == RTL_GIGA_MAC_VER_24) &&
		(RTL_R16(CPlusCmd) & ASF)) {
		return;
	}

	if (tp->mac_version == RTL_GIGA_MAC_VER_32 ||
		tp->mac_version == RTL_GIGA_MAC_VER_33)
		rtl_ephy_write(tp, 0x19, 0xff64);

	RTL_W8(Cfg9346, Cfg9346_Unlock);
	if(wol_enable)
	{
		//enable now_is_oob
		RTL_W8(MCU, RTL_R8(MCU) | NOW_IS_OOB);
		RTL_W8(Config5, RTL_R8(Config5) | LanWake);;
		RTL_W8(Config3, RTL_R8(Config3) | MagicPacket);
	}
	else
	{
		RTL_W8(Config5, RTL_R8(Config5) & ~LanWake);
		RTL_W8(Config3, RTL_R8(Config3) & ~MagicPacket);
	}
	RTL_W8(Cfg9346, Cfg9346_Lock);

	if (rtl_wol_pll_power_down(tp))
		return;

	r8168_phy_power_down(tp);

	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_25:
	case RTL_GIGA_MAC_VER_26:
	case RTL_GIGA_MAC_VER_27:
	case RTL_GIGA_MAC_VER_28:
	case RTL_GIGA_MAC_VER_31:
	case RTL_GIGA_MAC_VER_32:
	case RTL_GIGA_MAC_VER_33:
		RTL_W8(PMCH, RTL_R8(PMCH) & ~0x80);
		break;
	case RTL_GIGA_MAC_VER_40:
	case RTL_GIGA_MAC_VER_41:
		rtl_w1w0_eri(tp, 0x1a8, ERIAR_MASK_1111, 0x00000000,
				 0xfc000000, ERIAR_EXGMAC);
		break;
	}
}

static void r8168_pll_power_up(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_25:
	case RTL_GIGA_MAC_VER_26:
	case RTL_GIGA_MAC_VER_27:
	case RTL_GIGA_MAC_VER_28:
	case RTL_GIGA_MAC_VER_31:
	case RTL_GIGA_MAC_VER_32:
	case RTL_GIGA_MAC_VER_33:
		RTL_W8(PMCH, RTL_R8(PMCH) | 0x80);
		break;
	case RTL_GIGA_MAC_VER_40:
	case RTL_GIGA_MAC_VER_41:
		rtl_w1w0_eri(tp, 0x1a8, ERIAR_MASK_1111, 0xfc000000,
				 0x00000000, ERIAR_EXGMAC);
		break;
	}

	r8168_phy_power_up(tp);
}

static void rtl_generic_op(struct rtl8169_private *tp,
			   void (*op)(struct rtl8169_private *))
{
	if (op)
		op(tp);
}

static void rtl_pll_power_down(struct rtl8169_private *tp)
{
	rtl_generic_op(tp, tp->pll_power_ops.down);
}

static void rtl_pll_power_up(struct rtl8169_private *tp)
{
	rtl_generic_op(tp, tp->pll_power_ops.up);
}

static void rtl_init_pll_power_ops(struct rtl8169_private *tp)
{
	struct pll_power_ops *ops = &tp->pll_power_ops;

	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_07:
	case RTL_GIGA_MAC_VER_08:
	case RTL_GIGA_MAC_VER_09:
	case RTL_GIGA_MAC_VER_10:
	case RTL_GIGA_MAC_VER_16:
	case RTL_GIGA_MAC_VER_29:
	case RTL_GIGA_MAC_VER_30:
	case RTL_GIGA_MAC_VER_37:
	case RTL_GIGA_MAC_VER_39:
	case RTL_GIGA_MAC_VER_43:
		ops->down	= r810x_pll_power_down;
		ops->up		= r810x_pll_power_up;
		break;

	case RTL_GIGA_MAC_VER_11:
	case RTL_GIGA_MAC_VER_12:
	case RTL_GIGA_MAC_VER_17:
	case RTL_GIGA_MAC_VER_18:
	case RTL_GIGA_MAC_VER_19:
	case RTL_GIGA_MAC_VER_20:
	case RTL_GIGA_MAC_VER_21:
	case RTL_GIGA_MAC_VER_22:
	case RTL_GIGA_MAC_VER_23:
	case RTL_GIGA_MAC_VER_24:
	case RTL_GIGA_MAC_VER_25:
	case RTL_GIGA_MAC_VER_26:
	case RTL_GIGA_MAC_VER_27:
	case RTL_GIGA_MAC_VER_28:
	case RTL_GIGA_MAC_VER_31:
	case RTL_GIGA_MAC_VER_32:
	case RTL_GIGA_MAC_VER_33:
	case RTL_GIGA_MAC_VER_34:
	case RTL_GIGA_MAC_VER_35:
	case RTL_GIGA_MAC_VER_36:
	case RTL_GIGA_MAC_VER_38:
	case RTL_GIGA_MAC_VER_40:
	case RTL_GIGA_MAC_VER_41:
	case RTL_GIGA_MAC_VER_42:
		ops->down	= r8168_pll_power_down;
		ops->up		= r8168_pll_power_up;
		break;

	default:
		ops->down	= NULL;
		ops->up		= NULL;
		break;
	}
}

static void rtl_init_rxcfg(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_01:
	case RTL_GIGA_MAC_VER_02:
	case RTL_GIGA_MAC_VER_03:
	case RTL_GIGA_MAC_VER_04:
	case RTL_GIGA_MAC_VER_05:
	case RTL_GIGA_MAC_VER_06:
	case RTL_GIGA_MAC_VER_10:
	case RTL_GIGA_MAC_VER_11:
	case RTL_GIGA_MAC_VER_12:
	case RTL_GIGA_MAC_VER_13:
	case RTL_GIGA_MAC_VER_14:
	case RTL_GIGA_MAC_VER_15:
	case RTL_GIGA_MAC_VER_16:
	case RTL_GIGA_MAC_VER_17:
		RTL_W32(RxConfig, RX_FIFO_THRESH | RX_DMA_BURST);
		break;
	case RTL_GIGA_MAC_VER_18:
	case RTL_GIGA_MAC_VER_19:
	case RTL_GIGA_MAC_VER_20:
	case RTL_GIGA_MAC_VER_21:
	case RTL_GIGA_MAC_VER_22:
	case RTL_GIGA_MAC_VER_23:
	case RTL_GIGA_MAC_VER_24:
	case RTL_GIGA_MAC_VER_34:
	case RTL_GIGA_MAC_VER_35:
		RTL_W32(RxConfig, RX128_INT_EN | RX_MULTI_EN | RX_DMA_BURST);
		break;
	case RTL_GIGA_MAC_VER_40:
	case RTL_GIGA_MAC_VER_41:
	case RTL_GIGA_MAC_VER_42:
	case RTL_GIGA_MAC_VER_43:
		RTL_W32(RxConfig, RX128_INT_EN | RX_DMA_BURST | RX_EARLY_OFF);
		break;
	default:
		RTL_W32(RxConfig, RX128_INT_EN | RX_DMA_BURST);
		break;
	}
}

static void rtl8169_init_ring_indexes(struct rtl8169_private *tp)
{
	tp->dirty_tx = tp->cur_tx = tp->cur_rx = 0;
}

static void rtl_hw_jumbo_enable(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W8(Cfg9346, Cfg9346_Unlock);
	rtl_generic_op(tp, tp->jumbo_ops.enable);
	RTL_W8(Cfg9346, Cfg9346_Lock);
}

static void rtl_hw_jumbo_disable(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W8(Cfg9346, Cfg9346_Unlock);
	rtl_generic_op(tp, tp->jumbo_ops.disable);
	RTL_W8(Cfg9346, Cfg9346_Lock);
}

static void r8168c_hw_jumbo_enable(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W8(Config3, RTL_R8(Config3) | Jumbo_En0);
	RTL_W8(Config4, RTL_R8(Config4) | Jumbo_En1);
	rtl_tx_performance_tweak(tp->pdev, 0x2 << MAX_READ_REQUEST_SHIFT);
}

static void r8168c_hw_jumbo_disable(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W8(Config3, RTL_R8(Config3) & ~Jumbo_En0);
	RTL_W8(Config4, RTL_R8(Config4) & ~Jumbo_En1);
	rtl_tx_performance_tweak(tp->pdev, 0x5 << MAX_READ_REQUEST_SHIFT);
}

static void r8168dp_hw_jumbo_enable(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W8(Config3, RTL_R8(Config3) | Jumbo_En0);
}

static void r8168dp_hw_jumbo_disable(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W8(Config3, RTL_R8(Config3) & ~Jumbo_En0);
}

static void r8168e_hw_jumbo_enable(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W8(MaxTxPacketSize, 0x3f);
	RTL_W8(Config3, RTL_R8(Config3) | Jumbo_En0);
	RTL_W8(Config4, RTL_R8(Config4) | 0x01);
	rtl_tx_performance_tweak(tp->pdev, 0x2 << MAX_READ_REQUEST_SHIFT);
}

static void r8168e_hw_jumbo_disable(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W8(MaxTxPacketSize, 0x0c);
	RTL_W8(Config3, RTL_R8(Config3) & ~Jumbo_En0);
	RTL_W8(Config4, RTL_R8(Config4) & ~0x01);
	rtl_tx_performance_tweak(tp->pdev, 0x5 << MAX_READ_REQUEST_SHIFT);
}

static void r8168b_0_hw_jumbo_enable(struct rtl8169_private *tp)
{
//	rtl_tx_performance_tweak(tp->pdev,
//		(0x2 << MAX_READ_REQUEST_SHIFT) | PCI_EXP_DEVCTL_NOSNOOP_EN);
}

static void r8168b_0_hw_jumbo_disable(struct rtl8169_private *tp)
{
//	rtl_tx_performance_tweak(tp->pdev,
//		(0x5 << MAX_READ_REQUEST_SHIFT) | PCI_EXP_DEVCTL_NOSNOOP_EN);
}

static void r8168b_1_hw_jumbo_enable(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	r8168b_0_hw_jumbo_enable(tp);

	RTL_W8(Config4, RTL_R8(Config4) | (1 << 0));
}

static void r8168b_1_hw_jumbo_disable(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	r8168b_0_hw_jumbo_disable(tp);

	RTL_W8(Config4, RTL_R8(Config4) & ~(1 << 0));
}

static void rtl_init_jumbo_ops(struct rtl8169_private *tp)
{
	struct jumbo_ops *ops = &tp->jumbo_ops;

	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_11:
		ops->disable	= r8168b_0_hw_jumbo_disable;
		ops->enable	= r8168b_0_hw_jumbo_enable;
		break;
	case RTL_GIGA_MAC_VER_12:
	case RTL_GIGA_MAC_VER_17:
		ops->disable	= r8168b_1_hw_jumbo_disable;
		ops->enable	= r8168b_1_hw_jumbo_enable;
		break;
	case RTL_GIGA_MAC_VER_18: /* Wild guess. Needs info from Realtek. */
	case RTL_GIGA_MAC_VER_19:
	case RTL_GIGA_MAC_VER_20:
	case RTL_GIGA_MAC_VER_21: /* Wild guess. Needs info from Realtek. */
	case RTL_GIGA_MAC_VER_22:
	case RTL_GIGA_MAC_VER_23:
	case RTL_GIGA_MAC_VER_24:
	case RTL_GIGA_MAC_VER_25:
	case RTL_GIGA_MAC_VER_26:
		ops->disable	= r8168c_hw_jumbo_disable;
		ops->enable	= r8168c_hw_jumbo_enable;
		break;
	case RTL_GIGA_MAC_VER_27:
	case RTL_GIGA_MAC_VER_28:
		ops->disable	= r8168dp_hw_jumbo_disable;
		ops->enable	= r8168dp_hw_jumbo_enable;
		break;
	case RTL_GIGA_MAC_VER_31: /* Wild guess. Needs info from Realtek. */
	case RTL_GIGA_MAC_VER_32:
	case RTL_GIGA_MAC_VER_33:
	case RTL_GIGA_MAC_VER_34:
		ops->disable	= r8168e_hw_jumbo_disable;
		ops->enable	= r8168e_hw_jumbo_enable;
		break;

	/*
	 * No action needed for jumbo frames with 8169.
	 * No jumbo for 810x at all.
	 */
	case RTL_GIGA_MAC_VER_40:
	case RTL_GIGA_MAC_VER_41:
	case RTL_GIGA_MAC_VER_42:
	case RTL_GIGA_MAC_VER_43:
	default:
		ops->disable	= NULL;
		ops->enable	= NULL;
		break;
	}
}

DECLARE_RTL_COND(rtl_chipcmd_cond)
{
	void __iomem *ioaddr = tp->mmio_addr;

	return RTL_R8(ChipCmd) & CmdReset;
}

static void rtl_hw_reset(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W8(ChipCmd, CmdReset);

	rtl_udelay_loop_wait_low(tp, &rtl_chipcmd_cond, 100, 100);
}

static void rtl_request_uncached_firmware(struct rtl8169_private *tp)
{
	struct rtl_fw *rtl_fw;
	const char *name;
	int rc = -ENOMEM;

	name = rtl_lookup_firmware_name(tp);
	if (!name)
		goto out_no_firmware;

	rtl_fw = kzalloc(sizeof(*rtl_fw), GFP_KERNEL);
	if (!rtl_fw)
		goto err_warn;

	rc = request_firmware(&rtl_fw->fw, name, &tp->pdev->dev);
	if (rc < 0)
		goto err_free;

	rc = rtl_check_firmware(tp, rtl_fw);
	if (rc < 0)
		goto err_release_firmware;

	tp->rtl_fw = rtl_fw;
out:
	return;

err_release_firmware:
	release_firmware(rtl_fw->fw);
err_free:
	kfree(rtl_fw);
err_warn:
	netif_warn(tp, ifup, tp->dev, "unable to load firmware patch %s (%d)\n",
		   name, rc);
out_no_firmware:
	tp->rtl_fw = NULL;
	goto out;
}

static __maybe_unused void rtl_request_firmware(struct rtl8169_private *tp)
{
	if (IS_ERR(tp->rtl_fw))
		rtl_request_uncached_firmware(tp);
}

static void rtl_rx_close(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W32(RxConfig, RTL_R32(RxConfig) & ~RX_CONFIG_ACCEPT_MASK);
}

DECLARE_RTL_COND(rtl_npq_cond)
{
	void __iomem *ioaddr = tp->mmio_addr;

	return RTL_R8(TxPoll) & NPQ;
}

DECLARE_RTL_COND(rtl_txcfg_empty_cond)
{
	void __iomem *ioaddr = tp->mmio_addr;

	return RTL_R32(TxConfig) & TXCFG_EMPTY;
}

static void rtl8169_hw_reset(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	/* Disable interrupts */
	rtl8169_irq_mask_and_ack(tp);

	rtl_rx_close(tp);

	if (tp->mac_version == RTL_GIGA_MAC_VER_27 ||
		tp->mac_version == RTL_GIGA_MAC_VER_28 ||
		tp->mac_version == RTL_GIGA_MAC_VER_31) {
		rtl_udelay_loop_wait_low(tp, &rtl_npq_cond, 20, 42*42);
	} else if (tp->mac_version == RTL_GIGA_MAC_VER_34 ||
			   tp->mac_version == RTL_GIGA_MAC_VER_35 ||
			   tp->mac_version == RTL_GIGA_MAC_VER_36 ||
			   tp->mac_version == RTL_GIGA_MAC_VER_37 ||
			   tp->mac_version == RTL_GIGA_MAC_VER_40 ||
			   tp->mac_version == RTL_GIGA_MAC_VER_41 ||
			   tp->mac_version == RTL_GIGA_MAC_VER_42 ||
			   tp->mac_version == RTL_GIGA_MAC_VER_43 ||
			   tp->mac_version == RTL_GIGA_MAC_VER_38) {
		RTL_W8(ChipCmd, RTL_R8(ChipCmd) | StopReq);
		rtl_udelay_loop_wait_high(tp, &rtl_txcfg_empty_cond, 100, 666);
	} else {
		RTL_W8(ChipCmd, RTL_R8(ChipCmd) | StopReq);
		udelay(100);
	}

	rtl_hw_reset(tp);
}

static void rtl_set_rx_tx_config_registers(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	/* Set DMA burst size and Interframe Gap Time */
	RTL_W32(TxConfig, (TX_DMA_BURST << TxDMAShift) |
		(InterFrameGap << TxInterFrameGapShift));
}

static void rtl_hw_start(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	tp->hw_start(dev);

	rtl_irq_enable_all(tp);
}

static void rtl_set_rx_tx_desc_registers(struct rtl8169_private *tp,
					 void __iomem *ioaddr)
{
	/*
	 * Magic spell: some iop3xx ARM board needs the TxDescAddrHigh
	 * register to be written before TxDescAddrLow to work.
	 * Switching from MMIO to I/O access fixes the issue as well.
	 */
	RTL_W32(TxDescStartAddrHigh, ((u64) tp->TxPhyAddr) >> 32);
	RTL_W32(TxDescStartAddrLow, ((u64) tp->TxPhyAddr) & DMA_BIT_MASK(32));
	RTL_W32(RxDescAddrHigh, ((u64) tp->RxPhyAddr) >> 32);
	RTL_W32(RxDescAddrLow, ((u64) tp->RxPhyAddr) & DMA_BIT_MASK(32));
}

static u16 rtl_rw_cpluscmd(void __iomem *ioaddr)
{
	u16 cmd;

	cmd = RTL_R16(CPlusCmd);
	RTL_W16(CPlusCmd, cmd);
	return cmd;
}

static void rtl_set_rx_max_size(void __iomem *ioaddr, unsigned int rx_buf_sz)
{
	/* Low hurts. Let's disable the filtering. */
	RTL_W16(RxMaxSize, rx_buf_sz + 1);
}

static void rtl8169_set_magic_reg(void __iomem *ioaddr, unsigned mac_version)
{
	static const struct rtl_cfg2_info {
		u32 mac_version;
		u32 clk;
		u32 val;
	} cfg2_info [] = {
		{ RTL_GIGA_MAC_VER_05, PCI_Clock_33MHz, 0x000fff00 }, // 8110SCd
		{ RTL_GIGA_MAC_VER_05, PCI_Clock_66MHz, 0x000fffff },
		{ RTL_GIGA_MAC_VER_06, PCI_Clock_33MHz, 0x00ffff00 }, // 8110SCe
		{ RTL_GIGA_MAC_VER_06, PCI_Clock_66MHz, 0x00ffffff }
	};
	const struct rtl_cfg2_info *p = cfg2_info;
	unsigned int i;
	u32 clk;

	clk = RTL_R8(Config2) & PCI_Clock_66MHz;
	for (i = 0; i < ARRAY_SIZE(cfg2_info); i++, p++) {
		if ((p->mac_version == mac_version) && (p->clk == clk)) {
			RTL_W32(0x7c, p->val);
			break;
		}
	}
}

static void rtl_set_rx_mode(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	void __iomem *ioaddr = tp->mmio_addr;
	u32 mc_filter[2];	/* Multicast hash filter */
	int rx_mode;
	u32 tmp = 0;

	if (dev->flags & IFF_PROMISC) {
		/* Unconditionally log net taps. */
		netif_notice(tp, link, dev, "Promiscuous mode enabled\n");
		rx_mode =
			AcceptBroadcast | AcceptMulticast | AcceptMyPhys |
			AcceptAllPhys;
		mc_filter[1] = mc_filter[0] = 0xffffffff;
	} else if ((netdev_mc_count(dev) > multicast_filter_limit) ||
		   (dev->flags & IFF_ALLMULTI)) {
		/* Too many to filter perfectly -- accept all multicasts. */
		rx_mode = AcceptBroadcast | AcceptMulticast | AcceptMyPhys;
		mc_filter[1] = mc_filter[0] = 0xffffffff;
	} else {
		struct netdev_hw_addr *ha;

		rx_mode = AcceptBroadcast | AcceptMyPhys;
		mc_filter[1] = mc_filter[0] = 0;
		netdev_for_each_mc_addr(ha, dev) {
			int bit_nr = ether_crc(ETH_ALEN, ha->addr) >> 26;
			mc_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
			rx_mode |= AcceptMulticast;
		}
	}

	if (dev->features & NETIF_F_RXALL)
		rx_mode |= (AcceptErr | AcceptRunt);

	tmp = (RTL_R32(RxConfig) & ~RX_CONFIG_ACCEPT_MASK) | rx_mode;

	if (tp->mac_version > RTL_GIGA_MAC_VER_06) {
		u32 data = mc_filter[0];

		mc_filter[0] = swab32(mc_filter[1]);
		mc_filter[1] = swab32(data);
	}

	if (tp->mac_version == RTL_GIGA_MAC_VER_35)
		mc_filter[1] = mc_filter[0] = 0xffffffff;

	RTL_W32(MAR0 + 4, mc_filter[1]);
	RTL_W32(MAR0 + 0, mc_filter[0]);

	RTL_W32(RxConfig, tmp);
}

static void rtl_hw_start_8169(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	void __iomem *ioaddr = tp->mmio_addr;
//	struct platform_device *pdev = tp->pdev;

	if (tp->mac_version == RTL_GIGA_MAC_VER_05) {
		RTL_W16(CPlusCmd, RTL_R16(CPlusCmd) | PCIMulRW);
	//	pci_write_config_byte(pdev, PCI_CACHE_LINE_SIZE, 0x08);
	}

	RTL_W8(Cfg9346, Cfg9346_Unlock);
	if (tp->mac_version == RTL_GIGA_MAC_VER_01 ||
		tp->mac_version == RTL_GIGA_MAC_VER_02 ||
		tp->mac_version == RTL_GIGA_MAC_VER_03 ||
		tp->mac_version == RTL_GIGA_MAC_VER_04)
		RTL_W8(ChipCmd, CmdTxEnb | CmdRxEnb);

	rtl_init_rxcfg(tp);

	RTL_W8(EarlyTxThres, NoEarlyTx);

	rtl_set_rx_max_size(ioaddr, rx_buf_sz);

	if (tp->mac_version == RTL_GIGA_MAC_VER_01 ||
		tp->mac_version == RTL_GIGA_MAC_VER_02 ||
		tp->mac_version == RTL_GIGA_MAC_VER_03 ||
		tp->mac_version == RTL_GIGA_MAC_VER_04)
		rtl_set_rx_tx_config_registers(tp);

	tp->cp_cmd |= rtl_rw_cpluscmd(ioaddr) | PCIMulRW;

	if (tp->mac_version == RTL_GIGA_MAC_VER_02 ||
		tp->mac_version == RTL_GIGA_MAC_VER_03) {
		dprintk("Set MAC Reg C+CR Offset 0xE0. "
			"Bit-3 and bit-14 MUST be 1\n");
		tp->cp_cmd |= (1 << 14);
	}

	RTL_W16(CPlusCmd, tp->cp_cmd);

	rtl8169_set_magic_reg(ioaddr, tp->mac_version);

	/*
	 * Undocumented corner. Supposedly:
	 * (TxTimer << 12) | (TxPackets << 8) | (RxTimer << 4) | RxPackets
	 */
	RTL_W16(IntrMitigate, 0x0000);

	rtl_set_rx_tx_desc_registers(tp, ioaddr);

	if (tp->mac_version != RTL_GIGA_MAC_VER_01 &&
		tp->mac_version != RTL_GIGA_MAC_VER_02 &&
		tp->mac_version != RTL_GIGA_MAC_VER_03 &&
		tp->mac_version != RTL_GIGA_MAC_VER_04) {
		RTL_W8(ChipCmd, CmdTxEnb | CmdRxEnb);
		rtl_set_rx_tx_config_registers(tp);
	}

	RTL_W8(Cfg9346, Cfg9346_Lock);

	/* Initially a 10 us delay. Turned it into a PCI commit. - FR */
	RTL_R8(IntrMask);

	RTL_W32(RxMissed, 0);

	rtl_set_rx_mode(dev);

	/* no early-rx interrupts */
	RTL_W16(MultiIntr, RTL_R16(MultiIntr) & 0xF000);
}

static void rtl_csi_write(struct rtl8169_private *tp, int addr, int value)
{
	if (tp->csi_ops.write)
		tp->csi_ops.write(tp, addr, value);
}

static u32 rtl_csi_read(struct rtl8169_private *tp, int addr)
{
	return tp->csi_ops.read ? tp->csi_ops.read(tp, addr) : ~0;
}

static void rtl_csi_access_enable(struct rtl8169_private *tp, u32 bits)
{
	u32 csi;

	csi = rtl_csi_read(tp, 0x070c) & 0x00ffffff;
	rtl_csi_write(tp, 0x070c, csi | bits);
}

static void rtl_csi_access_enable_1(struct rtl8169_private *tp)
{
	rtl_csi_access_enable(tp, 0x17000000);
}

static void rtl_csi_access_enable_2(struct rtl8169_private *tp)
{
	rtl_csi_access_enable(tp, 0x27000000);
}

DECLARE_RTL_COND(rtl_csiar_cond)
{
	void __iomem *ioaddr = tp->mmio_addr;

	return RTL_R32(CSIAR) & CSIAR_FLAG;
}

static void r8169_csi_write(struct rtl8169_private *tp, int addr, int value)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W32(CSIDR, value);
	RTL_W32(CSIAR, CSIAR_WRITE_CMD | (addr & CSIAR_ADDR_MASK) |
		CSIAR_BYTE_ENABLE << CSIAR_BYTE_ENABLE_SHIFT);

	rtl_udelay_loop_wait_low(tp, &rtl_csiar_cond, 10, 100);
}

static u32 r8169_csi_read(struct rtl8169_private *tp, int addr)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W32(CSIAR, (addr & CSIAR_ADDR_MASK) |
		CSIAR_BYTE_ENABLE << CSIAR_BYTE_ENABLE_SHIFT);

	return rtl_udelay_loop_wait_high(tp, &rtl_csiar_cond, 10, 100) ?
		RTL_R32(CSIDR) : ~0;
}

static void r8402_csi_write(struct rtl8169_private *tp, int addr, int value)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W32(CSIDR, value);
	RTL_W32(CSIAR, CSIAR_WRITE_CMD | (addr & CSIAR_ADDR_MASK) |
		CSIAR_BYTE_ENABLE << CSIAR_BYTE_ENABLE_SHIFT |
		CSIAR_FUNC_NIC);

	rtl_udelay_loop_wait_low(tp, &rtl_csiar_cond, 10, 100);
}

static u32 r8402_csi_read(struct rtl8169_private *tp, int addr)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W32(CSIAR, (addr & CSIAR_ADDR_MASK) | CSIAR_FUNC_NIC |
		CSIAR_BYTE_ENABLE << CSIAR_BYTE_ENABLE_SHIFT);

	return rtl_udelay_loop_wait_high(tp, &rtl_csiar_cond, 10, 100) ?
		RTL_R32(CSIDR) : ~0;
}

static void rtl_init_csi_ops(struct rtl8169_private *tp)
{
	struct csi_ops *ops = &tp->csi_ops;

	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_01:
	case RTL_GIGA_MAC_VER_02:
	case RTL_GIGA_MAC_VER_03:
	case RTL_GIGA_MAC_VER_04:
	case RTL_GIGA_MAC_VER_05:
	case RTL_GIGA_MAC_VER_06:
	case RTL_GIGA_MAC_VER_10:
	case RTL_GIGA_MAC_VER_11:
	case RTL_GIGA_MAC_VER_12:
	case RTL_GIGA_MAC_VER_13:
	case RTL_GIGA_MAC_VER_14:
	case RTL_GIGA_MAC_VER_15:
	case RTL_GIGA_MAC_VER_16:
	case RTL_GIGA_MAC_VER_17:
		ops->write	= NULL;
		ops->read	= NULL;
		break;

	case RTL_GIGA_MAC_VER_37:
	case RTL_GIGA_MAC_VER_38:
		ops->write	= r8402_csi_write;
		ops->read	= r8402_csi_read;
		break;

	default:
		ops->write	= r8169_csi_write;
		ops->read	= r8169_csi_read;
		break;
	}
}

struct ephy_info {
	unsigned int offset;
	u16 mask;
	u16 bits;
};

static void rtl_ephy_init(struct rtl8169_private *tp, const struct ephy_info *e,
			  int len)
{
#if 0
	u16 w;

	while (len-- > 0) {
		w = (rtl_ephy_read(tp, e->offset) & ~e->mask) | e->bits;
		rtl_ephy_write(tp, e->offset, w);
		e++;
	}
#endif
}

static void rtl_disable_clock_request(struct platform_device *pdev)
{
//	pcie_capability_clear_word(pdev, PCI_EXP_LNKCTL,
//				   PCI_EXP_LNKCTL_CLKREQ_EN);
}

static void rtl_enable_clock_request(struct platform_device *pdev)
{
//	pcie_capability_set_word(pdev, PCI_EXP_LNKCTL,
//				 PCI_EXP_LNKCTL_CLKREQ_EN);
}

#define R8168_CPCMD_QUIRK_MASK (\
	EnableBist | \
	Mac_dbgo_oe | \
	Force_half_dup | \
	Force_rxflow_en | \
	Force_txflow_en | \
	Cxpl_dbg_sel | \
	ASF | \
	PktCntrDisable | \
	Mac_dbgo_sel)

static void rtl_hw_start_8168bb(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	struct platform_device *pdev = tp->pdev;

	RTL_W8(Config3, RTL_R8(Config3) & ~Beacon_en);

	RTL_W16(CPlusCmd, RTL_R16(CPlusCmd) & ~R8168_CPCMD_QUIRK_MASK);

	if (tp->dev->mtu <= ETH_DATA_LEN) {
		rtl_tx_performance_tweak(pdev, (0x5 << MAX_READ_REQUEST_SHIFT) |
					 0x0800);
		//			 PCI_EXP_DEVCTL_NOSNOOP_EN);
	}
}

static void rtl_hw_start_8168bef(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	rtl_hw_start_8168bb(tp);

	RTL_W8(MaxTxPacketSize, TxPacketMax);

	RTL_W8(Config4, RTL_R8(Config4) & ~(1 << 0));
}

static void __rtl_hw_start_8168cp(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	struct platform_device *pdev = tp->pdev;

	RTL_W8(Config1, RTL_R8(Config1) | Speed_down);

	RTL_W8(Config3, RTL_R8(Config3) & ~Beacon_en);

	if (tp->dev->mtu <= ETH_DATA_LEN)
		rtl_tx_performance_tweak(pdev, 0x5 << MAX_READ_REQUEST_SHIFT);

	rtl_disable_clock_request(pdev);

	RTL_W16(CPlusCmd, RTL_R16(CPlusCmd) & ~R8168_CPCMD_QUIRK_MASK);
}

static void rtl_hw_start_8168cp_1(struct rtl8169_private *tp)
{
	static const struct ephy_info e_info_8168cp[] = {
		{ 0x01, 0,	0x0001 },
		{ 0x02, 0x0800,	0x1000 },
		{ 0x03, 0,	0x0042 },
		{ 0x06, 0x0080,	0x0000 },
		{ 0x07, 0,	0x2000 }
	};

	rtl_csi_access_enable_2(tp);

	rtl_ephy_init(tp, e_info_8168cp, ARRAY_SIZE(e_info_8168cp));

	__rtl_hw_start_8168cp(tp);
}

static void rtl_hw_start_8168cp_2(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	struct platform_device *pdev = tp->pdev;

	rtl_csi_access_enable_2(tp);

	RTL_W8(Config3, RTL_R8(Config3) & ~Beacon_en);

	if (tp->dev->mtu <= ETH_DATA_LEN)
		rtl_tx_performance_tweak(pdev, 0x5 << MAX_READ_REQUEST_SHIFT);

	RTL_W16(CPlusCmd, RTL_R16(CPlusCmd) & ~R8168_CPCMD_QUIRK_MASK);
}

static void rtl_hw_start_8168cp_3(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	struct platform_device *pdev = tp->pdev;

	rtl_csi_access_enable_2(tp);

	RTL_W8(Config3, RTL_R8(Config3) & ~Beacon_en);

	/* Magic. */
	RTL_W8(DBG_REG, 0x20);

	RTL_W8(MaxTxPacketSize, TxPacketMax);

	if (tp->dev->mtu <= ETH_DATA_LEN)
		rtl_tx_performance_tweak(pdev, 0x5 << MAX_READ_REQUEST_SHIFT);

	RTL_W16(CPlusCmd, RTL_R16(CPlusCmd) & ~R8168_CPCMD_QUIRK_MASK);
}

static void rtl_hw_start_8168c_1(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	static const struct ephy_info e_info_8168c_1[] = {
		{ 0x02, 0x0800,	0x1000 },
		{ 0x03, 0,	0x0002 },
		{ 0x06, 0x0080,	0x0000 }
	};

	rtl_csi_access_enable_2(tp);

	RTL_W8(DBG_REG, 0x06 | FIX_NAK_1 | FIX_NAK_2);

	rtl_ephy_init(tp, e_info_8168c_1, ARRAY_SIZE(e_info_8168c_1));

	__rtl_hw_start_8168cp(tp);
}

static void rtl_hw_start_8168c_2(struct rtl8169_private *tp)
{
	static const struct ephy_info e_info_8168c_2[] = {
		{ 0x01, 0,	0x0001 },
		{ 0x03, 0x0400,	0x0220 }
	};

	rtl_csi_access_enable_2(tp);

	rtl_ephy_init(tp, e_info_8168c_2, ARRAY_SIZE(e_info_8168c_2));

	__rtl_hw_start_8168cp(tp);
}

static void rtl_hw_start_8168c_3(struct rtl8169_private *tp)
{
	rtl_hw_start_8168c_2(tp);
}

static void rtl_hw_start_8168c_4(struct rtl8169_private *tp)
{
	rtl_csi_access_enable_2(tp);

	__rtl_hw_start_8168cp(tp);
}

static void rtl_hw_start_8168d(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	struct platform_device *pdev = tp->pdev;

	rtl_csi_access_enable_2(tp);

	rtl_disable_clock_request(pdev);

	RTL_W8(MaxTxPacketSize, TxPacketMax);

	if (tp->dev->mtu <= ETH_DATA_LEN)
		rtl_tx_performance_tweak(pdev, 0x5 << MAX_READ_REQUEST_SHIFT);

	RTL_W16(CPlusCmd, RTL_R16(CPlusCmd) & ~R8168_CPCMD_QUIRK_MASK);
}

static void rtl_hw_start_8168dp(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	struct platform_device *pdev = tp->pdev;

	rtl_csi_access_enable_1(tp);

	if (tp->dev->mtu <= ETH_DATA_LEN)
		rtl_tx_performance_tweak(pdev, 0x5 << MAX_READ_REQUEST_SHIFT);

	RTL_W8(MaxTxPacketSize, TxPacketMax);

	rtl_disable_clock_request(pdev);
}

static void rtl_hw_start_8168d_4(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	struct platform_device *pdev = tp->pdev;
	static const struct ephy_info e_info_8168d_4[] = {
		{ 0x0b, ~0,	0x48 },
		{ 0x19, 0x20,	0x50 },
		{ 0x0c, ~0,	0x20 }
	};
	int i;

	rtl_csi_access_enable_1(tp);

	rtl_tx_performance_tweak(pdev, 0x5 << MAX_READ_REQUEST_SHIFT);

	RTL_W8(MaxTxPacketSize, TxPacketMax);

	for (i = 0; i < ARRAY_SIZE(e_info_8168d_4); i++) {
		const struct ephy_info *e = e_info_8168d_4 + i;
		u16 w;

		w = rtl_ephy_read(tp, e->offset);
		rtl_ephy_write(tp, 0x03, (w & e->mask) | e->bits);
	}

	rtl_enable_clock_request(pdev);
}

static void rtl_hw_start_8168e_1(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	struct platform_device *pdev = tp->pdev;
	static const struct ephy_info e_info_8168e_1[] = {
		{ 0x00, 0x0200,	0x0100 },
		{ 0x00, 0x0000,	0x0004 },
		{ 0x06, 0x0002,	0x0001 },
		{ 0x06, 0x0000,	0x0030 },
		{ 0x07, 0x0000,	0x2000 },
		{ 0x00, 0x0000,	0x0020 },
		{ 0x03, 0x5800,	0x2000 },
		{ 0x03, 0x0000,	0x0001 },
		{ 0x01, 0x0800,	0x1000 },
		{ 0x07, 0x0000,	0x4000 },
		{ 0x1e, 0x0000,	0x2000 },
		{ 0x19, 0xffff,	0xfe6c },
		{ 0x0a, 0x0000,	0x0040 }
	};

	rtl_csi_access_enable_2(tp);

	rtl_ephy_init(tp, e_info_8168e_1, ARRAY_SIZE(e_info_8168e_1));

	if (tp->dev->mtu <= ETH_DATA_LEN)
		rtl_tx_performance_tweak(pdev, 0x5 << MAX_READ_REQUEST_SHIFT);

	RTL_W8(MaxTxPacketSize, TxPacketMax);

	rtl_disable_clock_request(pdev);

	/* Reset tx FIFO pointer */
	RTL_W32(MISC, RTL_R32(MISC) | TXPLA_RST);
	RTL_W32(MISC, RTL_R32(MISC) & ~TXPLA_RST);

	RTL_W8(Config5, RTL_R8(Config5) & ~Spi_en);
}

static void rtl_hw_start_8168e_2(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	struct platform_device *pdev = tp->pdev;
	static const struct ephy_info e_info_8168e_2[] = {
		{ 0x09, 0x0000,	0x0080 },
		{ 0x19, 0x0000,	0x0224 }
	};

	rtl_csi_access_enable_1(tp);

	rtl_ephy_init(tp, e_info_8168e_2, ARRAY_SIZE(e_info_8168e_2));

	if (tp->dev->mtu <= ETH_DATA_LEN)
		rtl_tx_performance_tweak(pdev, 0x5 << MAX_READ_REQUEST_SHIFT);

	rtl_eri_write(tp, 0xc0, ERIAR_MASK_0011, 0x0000, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xb8, ERIAR_MASK_0011, 0x0000, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xc8, ERIAR_MASK_1111, 0x00100002, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xe8, ERIAR_MASK_1111, 0x00100006, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xcc, ERIAR_MASK_1111, 0x00000050, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xd0, ERIAR_MASK_1111, 0x07ff0060, ERIAR_EXGMAC);
	rtl_w1w0_eri(tp, 0x1b0, ERIAR_MASK_0001, 0x10, 0x00, ERIAR_EXGMAC);
	rtl_w1w0_eri(tp, 0x0d4, ERIAR_MASK_0011, 0x0c00, 0xff00, ERIAR_EXGMAC);

	RTL_W8(MaxTxPacketSize, EarlySize);

	rtl_disable_clock_request(pdev);

	RTL_W32(TxConfig, RTL_R32(TxConfig) | TXCFG_AUTO_FIFO);
	RTL_W8(MCU, RTL_R8(MCU) & ~NOW_IS_OOB);

	/* Adjust EEE LED frequency */
	RTL_W8(EEE_LED, RTL_R8(EEE_LED) & ~0x07);

	RTL_W8(DLLPR, RTL_R8(DLLPR) | PFM_EN);
	RTL_W32(MISC, RTL_R32(MISC) | PWM_EN);
	RTL_W8(Config5, RTL_R8(Config5) & ~Spi_en);
}

static void rtl_hw_start_8168f(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	struct platform_device *pdev = tp->pdev;

	rtl_csi_access_enable_2(tp);

	rtl_tx_performance_tweak(pdev, 0x5 << MAX_READ_REQUEST_SHIFT);

	rtl_eri_write(tp, 0xc0, ERIAR_MASK_0011, 0x0000, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xb8, ERIAR_MASK_0011, 0x0000, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xc8, ERIAR_MASK_1111, 0x00100002, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xe8, ERIAR_MASK_1111, 0x00100006, ERIAR_EXGMAC);
	rtl_w1w0_eri(tp, 0xdc, ERIAR_MASK_0001, 0x00, 0x01, ERIAR_EXGMAC);
	rtl_w1w0_eri(tp, 0xdc, ERIAR_MASK_0001, 0x01, 0x00, ERIAR_EXGMAC);
	rtl_w1w0_eri(tp, 0x1b0, ERIAR_MASK_0001, 0x10, 0x00, ERIAR_EXGMAC);
	rtl_w1w0_eri(tp, 0x1d0, ERIAR_MASK_0001, 0x10, 0x00, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xcc, ERIAR_MASK_1111, 0x00000050, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xd0, ERIAR_MASK_1111, 0x00000060, ERIAR_EXGMAC);

	RTL_W8(MaxTxPacketSize, EarlySize);

	rtl_disable_clock_request(pdev);

	RTL_W32(TxConfig, RTL_R32(TxConfig) | TXCFG_AUTO_FIFO);
	RTL_W8(MCU, RTL_R8(MCU) & ~NOW_IS_OOB);
	RTL_W8(DLLPR, RTL_R8(DLLPR) | PFM_EN);
	RTL_W32(MISC, RTL_R32(MISC) | PWM_EN);
	RTL_W8(Config5, RTL_R8(Config5) & ~Spi_en);
}

static void rtl_hw_start_8168f_1(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	static const struct ephy_info e_info_8168f_1[] = {
		{ 0x06, 0x00c0,	0x0020 },
		{ 0x08, 0x0001,	0x0002 },
		{ 0x09, 0x0000,	0x0080 },
		{ 0x19, 0x0000,	0x0224 }
	};

	rtl_hw_start_8168f(tp);

	rtl_ephy_init(tp, e_info_8168f_1, ARRAY_SIZE(e_info_8168f_1));

	rtl_w1w0_eri(tp, 0x0d4, ERIAR_MASK_0011, 0x0c00, 0xff00, ERIAR_EXGMAC);

	/* Adjust EEE LED frequency */
	RTL_W8(EEE_LED, RTL_R8(EEE_LED) & ~0x07);
}

static void rtl_hw_start_8411(struct rtl8169_private *tp)
{
	static const struct ephy_info e_info_8168f_1[] = {
		{ 0x06, 0x00c0,	0x0020 },
		{ 0x0f, 0xffff,	0x5200 },
		{ 0x1e, 0x0000,	0x4000 },
		{ 0x19, 0x0000,	0x0224 }
	};

	rtl_hw_start_8168f(tp);

	rtl_ephy_init(tp, e_info_8168f_1, ARRAY_SIZE(e_info_8168f_1));

	rtl_w1w0_eri(tp, 0x0d4, ERIAR_MASK_0011, 0x0c00, 0x0000, ERIAR_EXGMAC);
}

static void rtl_hw_start_8168g_1(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	struct platform_device *pdev = tp->pdev;

	RTL_W32(TxConfig, RTL_R32(TxConfig) | TXCFG_AUTO_FIFO);

	rtl_eri_write(tp, 0xc8, ERIAR_MASK_0101, 0x080002, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xcc, ERIAR_MASK_0001, 0x38, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xd0, ERIAR_MASK_0001, 0x48, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xe8, ERIAR_MASK_1111, 0x00100006, ERIAR_EXGMAC);

	rtl_csi_access_enable_1(tp);

	rtl_tx_performance_tweak(pdev, 0x5 << MAX_READ_REQUEST_SHIFT);

	rtl_w1w0_eri(tp, 0xdc, ERIAR_MASK_0001, 0x00, 0x01, ERIAR_EXGMAC);
	rtl_w1w0_eri(tp, 0xdc, ERIAR_MASK_0001, 0x01, 0x00, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0x2f8, ERIAR_MASK_0011, 0x1d8f, ERIAR_EXGMAC);

	RTL_W8(ChipCmd, CmdTxEnb | CmdRxEnb);
	RTL_W32(MISC, RTL_R32(MISC) & ~RXDV_GATED_EN);
	RTL_W8(MaxTxPacketSize, EarlySize);

	rtl_eri_write(tp, 0xc0, ERIAR_MASK_0011, 0x0000, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xb8, ERIAR_MASK_0011, 0x0000, ERIAR_EXGMAC);

	/* Adjust EEE LED frequency */
	RTL_W8(EEE_LED, RTL_R8(EEE_LED) & ~0x07);

	rtl_w1w0_eri(tp, 0x2fc, ERIAR_MASK_0001, 0x01, 0x06, ERIAR_EXGMAC);
	rtl_w1w0_eri(tp, 0x1b0, ERIAR_MASK_0011, 0x0000, 0x1000, ERIAR_EXGMAC);
}

static void rtl_hw_start_8168g_2(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	static const struct ephy_info e_info_8168g_2[] = {
		{ 0x00, 0x0000,	0x0008 },
		{ 0x0c, 0x3df0,	0x0200 },
		{ 0x19, 0xffff,	0xfc00 },
		{ 0x1e, 0xffff,	0x20eb }
	};

	rtl_hw_start_8168g_1(tp);

	// LED setting  add by yukuen
	#if defined(CONFIG_ARCH_RTD129x)
	RTL_W32(LEDSEL, 0x000670ca);
	#elif defined(CONFIG_ARCH_RTD139x)
	RTL_W32(LEDSEL, 0x000679a9);
	#elif defined(CONFIG_ARCH_RTD16xx)
	RTL_W32(LEDSEL, 0x17067ca9);
	#endif /* CONFIG_ARCH_RTD129x | CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */

	/* disable aspm and clock request before access ephy */
	RTL_W8(Config2, RTL_R8(Config2) & ~ClkReqEn);
	RTL_W8(Config5, RTL_R8(Config5) & ~ASPM_en);
	rtl_ephy_init(tp, e_info_8168g_2, ARRAY_SIZE(e_info_8168g_2));
}

static void rtl_hw_start_8168(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W8(Cfg9346, Cfg9346_Unlock);

	RTL_W8(MaxTxPacketSize, TxPacketMax);

	rtl_set_rx_max_size(ioaddr, rx_buf_sz);

	tp->cp_cmd |= RTL_R16(CPlusCmd) | PktCntrDisable | INTT_1;

	RTL_W16(CPlusCmd, tp->cp_cmd);

	RTL_W16(IntrMitigate, 0x5151);

	/* Work around for RxFIFO overflow. */
	if (tp->mac_version == RTL_GIGA_MAC_VER_11) {
		tp->event_slow |= RxFIFOOver | PCSTimeout;
		tp->event_slow &= ~RxOverflow;
	}

	rtl_set_rx_tx_desc_registers(tp, ioaddr);

	rtl_set_rx_tx_config_registers(tp);

	#if defined(RTL_TX_NO_CLOSE)
	/* enable tx no close mode */
	r8169soc_ocp_reg_write(tp, 0xE610,
		(r8169soc_ocp_reg_read(tp, 0xE610) | (BIT(4) | BIT(6))));
	#endif /* RTL_TX_NO_CLOSE */

	RTL_R8(IntrMask);

	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_11:
		rtl_hw_start_8168bb(tp);
		break;

	case RTL_GIGA_MAC_VER_12:
	case RTL_GIGA_MAC_VER_17:
		rtl_hw_start_8168bef(tp);
		break;

	case RTL_GIGA_MAC_VER_18:
		rtl_hw_start_8168cp_1(tp);
		break;

	case RTL_GIGA_MAC_VER_19:
		rtl_hw_start_8168c_1(tp);
		break;

	case RTL_GIGA_MAC_VER_20:
		rtl_hw_start_8168c_2(tp);
		break;

	case RTL_GIGA_MAC_VER_21:
		rtl_hw_start_8168c_3(tp);
		break;

	case RTL_GIGA_MAC_VER_22:
		rtl_hw_start_8168c_4(tp);
		break;

	case RTL_GIGA_MAC_VER_23:
		rtl_hw_start_8168cp_2(tp);
		break;

	case RTL_GIGA_MAC_VER_24:
		rtl_hw_start_8168cp_3(tp);
		break;

	case RTL_GIGA_MAC_VER_25:
	case RTL_GIGA_MAC_VER_26:
	case RTL_GIGA_MAC_VER_27:
		rtl_hw_start_8168d(tp);
		break;

	case RTL_GIGA_MAC_VER_28:
		rtl_hw_start_8168d_4(tp);
		break;

	case RTL_GIGA_MAC_VER_31:
		rtl_hw_start_8168dp(tp);
		break;

	case RTL_GIGA_MAC_VER_32:
	case RTL_GIGA_MAC_VER_33:
		rtl_hw_start_8168e_1(tp);
		break;
	case RTL_GIGA_MAC_VER_34:
		rtl_hw_start_8168e_2(tp);
		break;

	case RTL_GIGA_MAC_VER_35:
	case RTL_GIGA_MAC_VER_36:
		rtl_hw_start_8168f_1(tp);
		break;

	case RTL_GIGA_MAC_VER_38:
		rtl_hw_start_8411(tp);
		break;

	case RTL_GIGA_MAC_VER_40:
	case RTL_GIGA_MAC_VER_41:
		rtl_hw_start_8168g_1(tp);
		break;
	case RTL_GIGA_MAC_VER_42:
		rtl_hw_start_8168g_2(tp);
		break;

	default:
		printk(KERN_ERR PFX "%s: unknown chipset (mac_version = %d).\n",
			dev->name, tp->mac_version);
		break;
	}

	RTL_W8(Cfg9346, Cfg9346_Lock);

	RTL_W8(ChipCmd, CmdTxEnb | CmdRxEnb);

	rtl_set_rx_mode(dev);

	RTL_W16(MultiIntr, RTL_R16(MultiIntr) & 0xF000);
}

#define R810X_CPCMD_QUIRK_MASK (\
	EnableBist | \
	Mac_dbgo_oe | \
	Force_half_dup | \
	Force_rxflow_en | \
	Force_txflow_en | \
	Cxpl_dbg_sel | \
	ASF | \
	PktCntrDisable | \
	Mac_dbgo_sel)

static void rtl_hw_start_8102e_1(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	struct platform_device *pdev = tp->pdev;
	static const struct ephy_info e_info_8102e_1[] = {
		{ 0x01,	0, 0x6e65 },
		{ 0x02,	0, 0x091f },
		{ 0x03,	0, 0xc2f9 },
		{ 0x06,	0, 0xafb5 },
		{ 0x07,	0, 0x0e00 },
		{ 0x19,	0, 0xec80 },
		{ 0x01,	0, 0x2e65 },
		{ 0x01,	0, 0x6e65 }
	};
	u8 cfg1;

	rtl_csi_access_enable_2(tp);

	RTL_W8(DBG_REG, FIX_NAK_1);

	rtl_tx_performance_tweak(pdev, 0x5 << MAX_READ_REQUEST_SHIFT);

	RTL_W8(Config1,
		   LEDS1 | LEDS0 | Speed_down | MEMMAP | IOMAP | VPD | PMEnable);
	RTL_W8(Config3, RTL_R8(Config3) & ~Beacon_en);

	cfg1 = RTL_R8(Config1);
	if ((cfg1 & LEDS0) && (cfg1 & LEDS1))
		RTL_W8(Config1, cfg1 & ~LEDS0);

	rtl_ephy_init(tp, e_info_8102e_1, ARRAY_SIZE(e_info_8102e_1));
}

static void rtl_hw_start_8102e_2(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	struct platform_device *pdev = tp->pdev;

	rtl_csi_access_enable_2(tp);

	rtl_tx_performance_tweak(pdev, 0x5 << MAX_READ_REQUEST_SHIFT);

	RTL_W8(Config1, MEMMAP | IOMAP | VPD | PMEnable);
	RTL_W8(Config3, RTL_R8(Config3) & ~Beacon_en);
}

static void rtl_hw_start_8102e_3(struct rtl8169_private *tp)
{
	rtl_hw_start_8102e_2(tp);

	rtl_ephy_write(tp, 0x03, 0xc2f9);
}

static void rtl_hw_start_8105e_1(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	static const struct ephy_info e_info_8105e_1[] = {
		{ 0x07,	0, 0x4000 },
		{ 0x19,	0, 0x0200 },
		{ 0x19,	0, 0x0020 },
		{ 0x1e,	0, 0x2000 },
		{ 0x03,	0, 0x0001 },
		{ 0x19,	0, 0x0100 },
		{ 0x19,	0, 0x0004 },
		{ 0x0a,	0, 0x0020 }
	};

	/* Force LAN exit from ASPM if Rx/Tx are not idle */
	RTL_W32(FuncEvent, RTL_R32(FuncEvent) | 0x002800);

	/* Disable Early Tally Counter */
	RTL_W32(FuncEvent, RTL_R32(FuncEvent) & ~0x010000);

	RTL_W8(MCU, RTL_R8(MCU) | EN_NDP | EN_OOB_RESET);
	RTL_W8(DLLPR, RTL_R8(DLLPR) | PFM_EN);

	rtl_ephy_init(tp, e_info_8105e_1, ARRAY_SIZE(e_info_8105e_1));
}

static void rtl_hw_start_8105e_2(struct rtl8169_private *tp)
{
	rtl_hw_start_8105e_1(tp);
	rtl_ephy_write(tp, 0x1e, rtl_ephy_read(tp, 0x1e) | 0x8000);
}

static void rtl_hw_start_8402(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	static const struct ephy_info e_info_8402[] = {
		{ 0x19,	0xffff, 0xff64 },
		{ 0x1e,	0, 0x4000 }
	};

	rtl_csi_access_enable_2(tp);

	/* Force LAN exit from ASPM if Rx/Tx are not idle */
	RTL_W32(FuncEvent, RTL_R32(FuncEvent) | 0x002800);

	RTL_W32(TxConfig, RTL_R32(TxConfig) | TXCFG_AUTO_FIFO);
	RTL_W8(MCU, RTL_R8(MCU) & ~NOW_IS_OOB);

	rtl_ephy_init(tp, e_info_8402, ARRAY_SIZE(e_info_8402));

	rtl_tx_performance_tweak(tp->pdev, 0x5 << MAX_READ_REQUEST_SHIFT);

	rtl_eri_write(tp, 0xc8, ERIAR_MASK_1111, 0x00000002, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xe8, ERIAR_MASK_1111, 0x00000006, ERIAR_EXGMAC);
	rtl_w1w0_eri(tp, 0xdc, ERIAR_MASK_0001, 0x00, 0x01, ERIAR_EXGMAC);
	rtl_w1w0_eri(tp, 0xdc, ERIAR_MASK_0001, 0x01, 0x00, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xc0, ERIAR_MASK_0011, 0x0000, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xb8, ERIAR_MASK_0011, 0x0000, ERIAR_EXGMAC);
	rtl_w1w0_eri(tp, 0x0d4, ERIAR_MASK_0011, 0x0e00, 0xff00, ERIAR_EXGMAC);
}

static void rtl_hw_start_8106(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	/* Force LAN exit from ASPM if Rx/Tx are not idle */
	RTL_W32(FuncEvent, RTL_R32(FuncEvent) | 0x002800);

	RTL_W32(MISC, (RTL_R32(MISC) | DISABLE_LAN_EN) & ~EARLY_TALLY_EN);
	RTL_W8(MCU, RTL_R8(MCU) | EN_NDP | EN_OOB_RESET);
	RTL_W8(DLLPR, RTL_R8(DLLPR) & ~PFM_EN);
}

static void rtl_hw_start_8101(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	void __iomem *ioaddr = tp->mmio_addr;
//	struct platform_device *pdev = tp->pdev;

	if (tp->mac_version >= RTL_GIGA_MAC_VER_30)
		tp->event_slow &= ~RxFIFOOver;

//	if (tp->mac_version == RTL_GIGA_MAC_VER_13 ||
//	    tp->mac_version == RTL_GIGA_MAC_VER_16)
//		pcie_capability_set_word(pdev, PCI_EXP_DEVCTL,
//					 PCI_EXP_DEVCTL_NOSNOOP_EN);

	RTL_W8(Cfg9346, Cfg9346_Unlock);

	RTL_W8(MaxTxPacketSize, TxPacketMax);

	rtl_set_rx_max_size(ioaddr, rx_buf_sz);

	tp->cp_cmd &= ~R810X_CPCMD_QUIRK_MASK;
	RTL_W16(CPlusCmd, tp->cp_cmd);

	rtl_set_rx_tx_desc_registers(tp, ioaddr);

	rtl_set_rx_tx_config_registers(tp);

	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_07:
		rtl_hw_start_8102e_1(tp);
		break;

	case RTL_GIGA_MAC_VER_08:
		rtl_hw_start_8102e_3(tp);
		break;

	case RTL_GIGA_MAC_VER_09:
		rtl_hw_start_8102e_2(tp);
		break;

	case RTL_GIGA_MAC_VER_29:
		rtl_hw_start_8105e_1(tp);
		break;
	case RTL_GIGA_MAC_VER_30:
		rtl_hw_start_8105e_2(tp);
		break;

	case RTL_GIGA_MAC_VER_37:
		rtl_hw_start_8402(tp);
		break;

	case RTL_GIGA_MAC_VER_39:
		rtl_hw_start_8106(tp);
		break;
	case RTL_GIGA_MAC_VER_43:
		rtl_hw_start_8168g_2(tp);
		break;
	}

	RTL_W8(Cfg9346, Cfg9346_Lock);

	RTL_W16(IntrMitigate, 0x0000);

	RTL_W8(ChipCmd, CmdTxEnb | CmdRxEnb);

	rtl_set_rx_mode(dev);

	RTL_R8(IntrMask);

	RTL_W16(MultiIntr, RTL_R16(MultiIntr) & 0xf000);
}

static int link_status(void *data)
{
	struct net_device *dev = data;
	struct rtl8169_private *tp = netdev_priv(dev);
	void __iomem *ioaddr = tp->mmio_addr;
	set_user_nice(current, 5);
	printk("[Ethernet] Watch link status change.\n");

	while(!kthread_should_stop()){
		wait_event_interruptible(tp->thr_wait, kthread_should_stop() || tp->link_chg);
		if(kthread_should_stop()){
			break;
		}
		else if(!tp->link_chg)
			continue;
		else
			tp->link_chg = 0;

		// Send uevent about link status
		if(tp->link_ok(ioaddr)){
			kobject_uevent(&tp->dev->dev.kobj, KOBJ_LINKUP);
		}
		else{
			kobject_uevent(&tp->dev->dev.kobj, KOBJ_LINKDOWN);
		}
	}

	do_exit(0);
}

static int rtl8169_change_mtu(struct net_device *dev, int new_mtu)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	if (new_mtu < ETH_ZLEN ||
		new_mtu > rtl_chip_infos[tp->mac_version].jumbo_max)
		return -EINVAL;

	if (new_mtu > ETH_DATA_LEN)
		rtl_hw_jumbo_enable(tp);
	else
		rtl_hw_jumbo_disable(tp);

	dev->mtu = new_mtu;
	netdev_update_features(dev);

	return 0;
}

static inline void rtl8169_make_unusable_by_asic(struct RxDesc *desc)
{
	desc->addr = cpu_to_le64(0x0badbadbadbadbadull);
	desc->opts1 &= ~cpu_to_le32(DescOwn | RsvdMask);
}

static void rtl8169_free_rx_databuff(struct rtl8169_private *tp,
					 void **data_buff, struct RxDesc *desc)
{
	if (!tp->acp_enable)
		dma_unmap_single(&tp->pdev->dev, le64_to_cpu(desc->addr),
				 rx_buf_sz, DMA_FROM_DEVICE);

	kfree(*data_buff);
	*data_buff = NULL;
	rtl8169_make_unusable_by_asic(desc);
}

static inline void rtl8169_mark_to_asic(struct RxDesc *desc, u32 rx_buf_sz)
{
	u32 eor = le32_to_cpu(desc->opts1) & RingEnd;

	desc->opts1 = cpu_to_le32(DescOwn | eor | rx_buf_sz);
}

static inline void rtl8169_map_to_asic(struct RxDesc *desc, dma_addr_t mapping,
					   u32 rx_buf_sz)
{
	desc->addr = cpu_to_le64(mapping);
	wmb();
	rtl8169_mark_to_asic(desc, rx_buf_sz);
}

static inline void *rtl8169_align(void *data)
{
	return (void *)ALIGN((long)data, 16);
}

static struct sk_buff *rtl8169_alloc_rx_data(struct rtl8169_private *tp,
						 struct RxDesc *desc)
{
	void *data;
	dma_addr_t mapping;
	struct device *d = &tp->pdev->dev;
	struct net_device *dev = tp->dev;
	int node = dev->dev.parent ? dev_to_node(dev->dev.parent) : -1;

	data = kmalloc_node(rx_buf_sz, GFP_KERNEL, node);
	if (!data)
		return NULL;

	if (rtl8169_align(data) != data) {
		kfree(data);
		data = kmalloc_node(rx_buf_sz + 15, GFP_KERNEL, node);
		if (!data)
			return NULL;
	}

	if (tp->acp_enable) {
		mapping = virt_to_phys(rtl8169_align(data));
	} else {
		mapping = dma_map_single(d, rtl8169_align(data), rx_buf_sz,
					 DMA_FROM_DEVICE);
		if (unlikely(dma_mapping_error(d, mapping))) {
			if (net_ratelimit())
				netif_err(tp, drv, tp->dev, "Failed to map RX DMA!\n");
			goto err_out;
		}
	}

	rtl8169_map_to_asic(desc, mapping, rx_buf_sz);
	return data;

err_out:
	kfree(data);
	return NULL;
}

static void rtl8169_rx_clear(struct rtl8169_private *tp)
{
	unsigned int i;

	for (i = 0; i < NUM_RX_DESC; i++) {
		if (tp->Rx_databuff[i]) {
			rtl8169_free_rx_databuff(tp, tp->Rx_databuff + i,
						tp->RxDescArray + i);
		}
	}
}

static inline void rtl8169_mark_as_last_descriptor(struct RxDesc *desc)
{
	desc->opts1 |= cpu_to_le32(RingEnd);
}

static int rtl8169_rx_fill(struct rtl8169_private *tp)
{
	unsigned int i;

	for (i = 0; i < NUM_RX_DESC; i++) {
		void *data;

		if (tp->Rx_databuff[i])
			continue;

		data = rtl8169_alloc_rx_data(tp, tp->RxDescArray + i);
		if (!data) {
			rtl8169_make_unusable_by_asic(tp->RxDescArray + i);
			goto err_out;
		}
		tp->Rx_databuff[i] = data;
	}

	rtl8169_mark_as_last_descriptor(tp->RxDescArray + NUM_RX_DESC - 1);
	return 0;

err_out:
	rtl8169_rx_clear(tp);
	return -ENOMEM;
}

static int rtl8169_init_ring(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	rtl8169_init_ring_indexes(tp);

	memset(tp->tx_skb, 0x0, NUM_TX_DESC * sizeof(struct ring_info));
	memset(tp->Rx_databuff, 0x0, NUM_RX_DESC * sizeof(void *));

	return rtl8169_rx_fill(tp);
}

static void rtl8169_unmap_tx_skb(struct rtl8169_private *tp, struct device *d,
				 struct ring_info *tx_skb, struct TxDesc *desc)
{
	unsigned int len = tx_skb->len;

	if (!tp->acp_enable)
		dma_unmap_single(d, le64_to_cpu(desc->addr), len,
				 DMA_TO_DEVICE);

	desc->opts1 = 0x00;
	desc->opts2 = 0x00;
	desc->addr = 0x00;
	tx_skb->len = 0;
}

static void rtl8169_tx_clear_range(struct rtl8169_private *tp, u32 start,
				   unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++) {
		unsigned int entry = (start + i) % NUM_TX_DESC;
		struct ring_info *tx_skb = tp->tx_skb + entry;
		unsigned int len = tx_skb->len;

		if (len) {
			struct sk_buff *skb = tx_skb->skb;

			rtl8169_unmap_tx_skb(tp, &tp->pdev->dev, tx_skb,
						 tp->TxDescArray + entry);
			if (skb) {
				tp->dev->stats.tx_dropped++;
				dev_kfree_skb(skb);
				tx_skb->skb = NULL;
			}
		}
	}
}

static void rtl8169_tx_clear(struct rtl8169_private *tp)
{
	rtl8169_tx_clear_range(tp, tp->dirty_tx, NUM_TX_DESC);
	tp->cur_tx = tp->dirty_tx = 0;
}

static void rtl_reset_work(struct rtl8169_private *tp)
{
	struct net_device *dev = tp->dev;
	int i;

	napi_disable(&tp->napi);
	netif_stop_queue(dev);
	synchronize_sched();

	rtl8169_hw_reset(tp);

	for (i = 0; i < NUM_RX_DESC; i++)
		rtl8169_mark_to_asic(tp->RxDescArray + i, rx_buf_sz);

	rtl8169_tx_clear(tp);
	rtl8169_init_ring_indexes(tp);

	napi_enable(&tp->napi);
	rtl_hw_start(dev);
	netif_wake_queue(dev);
	rtl8169_check_link_status(dev, tp, tp->mmio_addr);
}

static void rtl8169_tx_timeout(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	rtl_schedule_task(tp, RTL_FLAG_TASK_RESET_PENDING);
}

static int rtl8169_xmit_frags(struct rtl8169_private *tp, struct sk_buff *skb,
				  u32 *opts)
{
	struct skb_shared_info *info = skb_shinfo(skb);
	unsigned int cur_frag, entry;
	struct TxDesc * uninitialized_var(txd);
	struct device *d = &tp->pdev->dev;

	entry = tp->cur_tx;
	for (cur_frag = 0; cur_frag < info->nr_frags; cur_frag++) {
		const skb_frag_t *frag = info->frags + cur_frag;
		dma_addr_t mapping;
		u32 status, len;
		void *addr;

		entry = (entry + 1) % NUM_TX_DESC;

		txd = tp->TxDescArray + entry;
		len = skb_frag_size(frag);
		addr = skb_frag_address(frag);
		if (tp->acp_enable) {
			mapping = virt_to_phys(addr);
		} else {
			mapping = dma_map_single(d, addr, len, DMA_TO_DEVICE);
			if (unlikely(dma_mapping_error(d, mapping))) {
				if (net_ratelimit())
					netif_err(tp, drv, tp->dev,
						  "Failed to map TX fragments DMA!\n");
				goto err_out;
			}
		}

		/* Anti gcc 2.95.3 bugware (sic) */
		status = opts[0] | len |
			(RingEnd * !((entry + 1) % NUM_TX_DESC));

		txd->opts1 = cpu_to_le32(status);
		txd->opts2 = cpu_to_le32(opts[1]);
		txd->addr = cpu_to_le64(mapping);

		tp->tx_skb[entry].len = len;
	}

	if (cur_frag) {
		tp->tx_skb[entry].skb = skb;
		txd->opts1 |= cpu_to_le32(LastFrag);
	}

	return cur_frag;

err_out:
	rtl8169_tx_clear_range(tp, tp->cur_tx + 1, cur_frag);
	return -EIO;
}

static bool rtl_skb_pad(struct sk_buff *skb)
{
	if (skb_padto(skb, ETH_ZLEN))
		return false;
	skb_put(skb, ETH_ZLEN - skb->len);
	return true;
}

static bool rtl_test_hw_pad_bug(struct rtl8169_private *tp, struct sk_buff *skb)
{
	return skb->len < ETH_ZLEN && tp->mac_version == RTL_GIGA_MAC_VER_34;
}

static inline bool rtl8169_tso_csum(struct rtl8169_private *tp,
					struct sk_buff *skb, u32 *opts)
{
	const struct rtl_tx_desc_info *info = tx_desc_info + tp->txd_version;
	u32 mss = skb_shinfo(skb)->gso_size;
	int offset = info->opts_offset;

	if (mss) {
		opts[0] |= TD_LSO;
		opts[offset] |= min(mss, TD_MSS_MAX) << info->mss_shift;
	} else if (skb->ip_summed == CHECKSUM_PARTIAL) {
		const struct iphdr *ip = ip_hdr(skb);

		if (unlikely(rtl_test_hw_pad_bug(tp, skb)))
			return skb_checksum_help(skb) == 0 && rtl_skb_pad(skb);

		if (ip->protocol == IPPROTO_TCP)
			opts[offset] |= info->checksum.tcp;
		else if (ip->protocol == IPPROTO_UDP)
			opts[offset] |= info->checksum.udp;
		else
			WARN_ON_ONCE(1);
	} else {
		if (unlikely(rtl_test_hw_pad_bug(tp, skb)))
			return rtl_skb_pad(skb);
	}
	return true;
}

static netdev_tx_t rtl8169_start_xmit(struct sk_buff *skb,
					  struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	unsigned int entry = tp->cur_tx % NUM_TX_DESC;
	struct TxDesc *txd = tp->TxDescArray + entry;
	void __iomem *ioaddr = tp->mmio_addr;
	struct device *d = &tp->pdev->dev;
	dma_addr_t mapping;
	u32 status, len;
	u32 opts[2];
	int frags;
	#if defined(RTL_TX_NO_CLOSE)
	u16 close_idx;
	u16 tail_idx;
	#endif /* RTL_TX_NO_CLOSE */

	if (unlikely(!TX_FRAGS_READY_FOR(tp, skb_shinfo(skb)->nr_frags))) {
		netif_err(tp, drv, dev, "BUG! Tx Ring full when queue awake!\n");
		goto err_stop_0;
	}

	#if defined(RTL_TX_NO_CLOSE)
	close_idx = RTL_R16(TX_DESC_CLOSE_IDX) & TX_DESC_CNT_MASK;
	tail_idx = tp->cur_tx & TX_DESC_CNT_MASK;
	if (((tail_idx > close_idx) && (tail_idx - close_idx == NUM_TX_DESC)) ||
		((tail_idx < close_idx) &&
		 (TX_DESC_CNT_SIZE - close_idx + tail_idx == NUM_TX_DESC)))
		goto err_stop_0;
	#else
	if (unlikely(le32_to_cpu(txd->opts1) & DescOwn))
		goto err_stop_0;
	#endif /* RTL_TX_NO_CLOSE */

	opts[1] = cpu_to_le32(rtl8169_tx_vlan_tag(skb));
	opts[0] = DescOwn;

	if (!rtl8169_tso_csum(tp, skb, opts))
		goto err_update_stats;

	len = skb_headlen(skb);
	if (tp->acp_enable) {
		mapping = virt_to_phys(skb->data);
	} else {
		mapping = dma_map_single(d, skb->data, len, DMA_TO_DEVICE);
		if (unlikely(dma_mapping_error(d, mapping))) {
			if (net_ratelimit())
				netif_err(tp, drv, dev, "Failed to map TX DMA!\n");
			goto err_dma_0;
		}
	}

	tp->tx_skb[entry].len = len;
	txd->addr = cpu_to_le64(mapping);

	frags = rtl8169_xmit_frags(tp, skb, opts);
	if (frags < 0)
		goto err_dma_1;
	else if (frags)
		opts[0] |= FirstFrag;
	else {
		opts[0] |= FirstFrag | LastFrag;
		tp->tx_skb[entry].skb = skb;
	}

	txd->opts2 = cpu_to_le32(opts[1]);

	skb_tx_timestamp(skb);

	wmb();

	/* Anti gcc 2.95.3 bugware (sic) */
	status = opts[0] | len | (RingEnd * !((entry + 1) % NUM_TX_DESC));
	txd->opts1 = cpu_to_le32(status);

	tp->cur_tx += frags + 1;

	#if defined(RTL_TX_NO_CLOSE)
	RTL_W16(TX_DESC_TAIL_IDX, tp->cur_tx & TX_DESC_CNT_MASK);
	#endif /* RTL_TX_NO_CLOSE */

	wmb();

	RTL_W8(TxPoll, NPQ);

	mmiowb();

	if (!TX_FRAGS_READY_FOR(tp, MAX_SKB_FRAGS)) {
		/* Avoid wrongly optimistic queue wake-up: rtl_tx thread must
		 * not miss a ring update when it notices a stopped queue.
		 */
		smp_wmb();
		netif_stop_queue(dev);
		/* Sync with rtl_tx:
		 * - publish queue status and cur_tx ring index (write barrier)
		 * - refresh dirty_tx ring index (read barrier).
		 * May the current thread have a pessimistic view of the ring
		 * status and forget to wake up queue, a racing rtl_tx thread
		 * can't.
		 */
		smp_mb();
		if (TX_FRAGS_READY_FOR(tp, MAX_SKB_FRAGS))
			netif_wake_queue(dev);
	}

	return NETDEV_TX_OK;

err_dma_1:
	rtl8169_unmap_tx_skb(tp, d, tp->tx_skb + entry, txd);
err_dma_0:
	dev_kfree_skb(skb);
err_update_stats:
	dev->stats.tx_dropped++;
	return NETDEV_TX_OK;

err_stop_0:
	netif_stop_queue(dev);
	dev->stats.tx_dropped++;
	return NETDEV_TX_BUSY;
}

static void rtl8169_pcierr_interrupt(struct net_device *dev)
{
#if 0	//barry
	struct rtl8169_private *tp = netdev_priv(dev);
	struct platform_device *pdev = tp->pdev;
	u16 pci_status, pci_cmd;

	pci_read_config_word(pdev, PCI_COMMAND, &pci_cmd);
	pci_read_config_word(pdev, PCI_STATUS, &pci_status);

	netif_err(tp, intr, dev, "PCI error (cmd = 0x%04x, status = 0x%04x)\n",
		  pci_cmd, pci_status);

	/*
	 * The recovery sequence below admits a very elaborated explanation:
	 * - it seems to work;
	 * - I did not see what else could be done;
	 * - it makes iop3xx happy.
	 *
	 * Feel free to adjust to your needs.
	 */
	if (pdev->broken_parity_status)
		pci_cmd &= ~PCI_COMMAND_PARITY;
	else
		pci_cmd |= PCI_COMMAND_SERR | PCI_COMMAND_PARITY;

	pci_write_config_word(pdev, PCI_COMMAND, pci_cmd);

	pci_write_config_word(pdev, PCI_STATUS,
		pci_status & (PCI_STATUS_DETECTED_PARITY |
		PCI_STATUS_SIG_SYSTEM_ERROR | PCI_STATUS_REC_MASTER_ABORT |
		PCI_STATUS_REC_TARGET_ABORT | PCI_STATUS_SIG_TARGET_ABORT));

	/* The infamous DAC f*ckup only happens at boot time */
	if ((tp->cp_cmd & PCIDAC) && !tp->cur_rx) {
		void __iomem *ioaddr = tp->mmio_addr;

		netif_info(tp, intr, dev, "disabling PCI DAC\n");
		tp->cp_cmd &= ~PCIDAC;
		RTL_W16(CPlusCmd, tp->cp_cmd);
		dev->features &= ~NETIF_F_HIGHDMA;
	}

	rtl8169_hw_reset(tp);

	rtl_schedule_task(tp, RTL_FLAG_TASK_RESET_PENDING);
#endif
}

static void rtl_tx(struct net_device *dev, struct rtl8169_private *tp)
{
	unsigned int dirty_tx, tx_left;
	#if defined(RTL_TX_NO_CLOSE)
	u16 close_idx;
	u16 dirty_tx_idx;
	void __iomem *ioaddr = tp->mmio_addr;
	#endif /* RTL_TX_NO_CLOSE */

	dirty_tx = tp->dirty_tx;
	#if defined(RTL_TX_NO_CLOSE)
	close_idx = RTL_R16(TX_DESC_CLOSE_IDX) & TX_DESC_CNT_MASK;
	dirty_tx_idx = dirty_tx & TX_DESC_CNT_MASK;
	smp_rmb();
	if (dirty_tx_idx <= close_idx)
		tx_left = close_idx - dirty_tx_idx;
	else
		tx_left = close_idx + TX_DESC_CNT_SIZE - dirty_tx_idx;
	#else
	smp_rmb();
	tx_left = tp->cur_tx - dirty_tx;
	#endif /* RTL_TX_NO_CLOSE */

	while (tx_left > 0) {
		unsigned int entry = dirty_tx % NUM_TX_DESC;
		struct ring_info *tx_skb = tp->tx_skb + entry;
		u32 status;

		rmb();
		status = le32_to_cpu(tp->TxDescArray[entry].opts1);
		#if !defined(RTL_TX_NO_CLOSE)
		if (status & DescOwn)
			break;
		#endif /* !RTL_TX_NO_CLOSE */

		rtl8169_unmap_tx_skb(tp, &tp->pdev->dev, tx_skb,
					 tp->TxDescArray + entry);
		if (status & LastFrag) {
			u64_stats_update_begin(&tp->tx_stats.syncp);
			tp->tx_stats.packets++;
			tp->tx_stats.bytes += tx_skb->skb->len;
			u64_stats_update_end(&tp->tx_stats.syncp);
			dev_kfree_skb(tx_skb->skb);
			tx_skb->skb = NULL;
		}
		dirty_tx++;
		tx_left--;
	}

	if (tp->dirty_tx != dirty_tx) {
		tp->dirty_tx = dirty_tx;
		/* Sync with rtl8169_start_xmit:
		 * - publish dirty_tx ring index (write barrier)
		 * - refresh cur_tx ring index and queue status (read barrier)
		 * May the current thread miss the stopped queue condition,
		 * a racing xmit thread can only have a right view of the
		 * ring status.
		 */
		smp_mb();
		if (netif_queue_stopped(dev) &&
			TX_FRAGS_READY_FOR(tp, MAX_SKB_FRAGS)) {
			netif_wake_queue(dev);
		}
		/*
		 * 8168 hack: TxPoll requests are lost when the Tx packets are
		 * too close. Let's kick an extra TxPoll request when a burst
		 * of start_xmit activity is detected (if it is not detected,
		 * it is slow enough). -- FR
		 */
		if (tp->cur_tx != dirty_tx) {
			void __iomem *ioaddr = tp->mmio_addr;

			RTL_W8(TxPoll, NPQ);
		}
	}
}

static inline int rtl8169_fragmented_frame(u32 status)
{
	return (status & (FirstFrag | LastFrag)) != (FirstFrag | LastFrag);
}

static inline void rtl8169_rx_csum(struct sk_buff *skb, u32 opts1)
{
	u32 status = opts1 & RxProtoMask;

	if (((status == RxProtoTCP) && !(opts1 & TCPFail)) ||
		((status == RxProtoUDP) && !(opts1 & UDPFail)))
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	else
		skb_checksum_none_assert(skb);
}

static struct sk_buff *rtl8169_try_rx_copy(void *data,
					   struct rtl8169_private *tp,
					   int pkt_size,
					   dma_addr_t addr)
{
	struct sk_buff *skb;
	struct device *d = &tp->pdev->dev;

	data = rtl8169_align(data);
	if (!tp->acp_enable)
		dma_sync_single_for_cpu(d, addr, pkt_size, DMA_FROM_DEVICE);
	prefetch(data);
	skb = netdev_alloc_skb_ip_align(tp->dev, pkt_size);
	if (skb)
		memcpy(skb->data, data, pkt_size);
	if (!tp->acp_enable)
		dma_sync_single_for_device(d, addr, pkt_size, DMA_FROM_DEVICE);

	return skb;
}

static int rtl_rx(struct net_device *dev, struct rtl8169_private *tp, u32 budget)
{
	unsigned int cur_rx, rx_left;
	unsigned int count;

	cur_rx = tp->cur_rx;

	for (rx_left = min(budget, NUM_RX_DESC); rx_left > 0; rx_left--, cur_rx++) {
		unsigned int entry = cur_rx % NUM_RX_DESC;
		struct RxDesc *desc = tp->RxDescArray + entry;
		u32 status;

		rmb();
		status = le32_to_cpu(desc->opts1) & tp->opts1_mask;

		if (status & DescOwn)
			break;
		if (unlikely(status & RxRES)) {
			netif_info(tp, rx_err, dev, "Rx ERROR. status = %08x\n",
				   status);
			dev->stats.rx_errors++;
			if (status & (RxRWT | RxRUNT))
				dev->stats.rx_length_errors++;
			if (status & RxCRC)
				dev->stats.rx_crc_errors++;
			if (status & RxFOVF) {
				rtl_schedule_task(tp, RTL_FLAG_TASK_RESET_PENDING);
				dev->stats.rx_fifo_errors++;
			}
			if ((status & (RxRUNT | RxCRC)) &&
				!(status & (RxRWT | RxFOVF)) &&
				(dev->features & NETIF_F_RXALL))
				goto process_pkt;
		} else {
			struct sk_buff *skb;
			dma_addr_t addr;
			int pkt_size;

process_pkt:
			addr = le64_to_cpu(desc->addr);
			if (likely(!(dev->features & NETIF_F_RXFCS)))
				pkt_size = (status & 0x00003fff) - 4;
			else
				pkt_size = status & 0x00003fff;

			/*
			 * The driver does not support incoming fragmented
			 * frames. They are seen as a symptom of over-mtu
			 * sized frames.
			 */
			if (unlikely(rtl8169_fragmented_frame(status))) {
				dev->stats.rx_dropped++;
				dev->stats.rx_length_errors++;
				goto release_descriptor;
			}

			skb = rtl8169_try_rx_copy(tp->Rx_databuff[entry],
						  tp, pkt_size, addr);
			if (!skb) {
				dev->stats.rx_dropped++;
				goto release_descriptor;
			}

			rtl8169_rx_csum(skb, status);
			skb_put(skb, pkt_size);
			skb->protocol = eth_type_trans(skb, dev);

			rtl8169_rx_vlan_tag(desc, skb);

			napi_gro_receive(&tp->napi, skb);

			u64_stats_update_begin(&tp->rx_stats.syncp);
			tp->rx_stats.packets++;
			tp->rx_stats.bytes += pkt_size;
			u64_stats_update_end(&tp->rx_stats.syncp);
		}
release_descriptor:
		desc->opts2 = 0;
		wmb();
		rtl8169_mark_to_asic(desc, rx_buf_sz);
	}

	count = cur_rx - tp->cur_rx;
	tp->cur_rx = cur_rx;

	return count;
}

static irqreturn_t rtl8169_interrupt(int irq, void *dev_instance)
{
	struct net_device *dev = dev_instance;
	struct rtl8169_private *tp = netdev_priv(dev);
	int handled = 0;
	u16 status;

	status = rtl_get_events(tp);
	if (status && status != 0xffff) {
		status &= RTL_EVENT_NAPI | tp->event_slow;
		if (status) {
			handled = 1;

			rtl_irq_disable(tp);
			napi_schedule(&tp->napi);
		}
	}
	return IRQ_RETVAL(handled);
}

/*
 * Workqueue context.
 */
static void rtl_slow_event_work(struct rtl8169_private *tp)
{
	struct net_device *dev = tp->dev;
	void __iomem *ioaddr = tp->mmio_addr;
	u16 status;

	status = rtl_get_events(tp) & tp->event_slow;
	rtl_ack_events(tp, status);

	if (unlikely(status & RxFIFOOver)) {
		switch (tp->mac_version) {
		/* Work around for rx fifo overflow */
		case RTL_GIGA_MAC_VER_11:
			netif_stop_queue(dev);
			/* XXX - Hack alert. See rtl_task(). */
			set_bit(RTL_FLAG_TASK_RESET_PENDING, tp->wk.flags);
		default:
			break;
		}
	}

	if (unlikely(status & SYSErr))
		rtl8169_pcierr_interrupt(dev);

	if (status & LinkChg)
	{
		__rtl8169_check_link_status(dev, tp, tp->mmio_addr, true);

		/* Add for link status change */
		tp->link_chg = 1;
		wake_up(&tp->thr_wait);

				// prevet ALDPS enter MAC Powercut Tx/Rx disable
				// use MAC reset to set counter to offset 0
		if (tp->link_ok(ioaddr))
		{
		   rtl_schedule_task(tp, RTL_FLAG_TASK_RESET_PENDING);
		}
		else
		{
		   mod_timer(&tp->timer, jiffies + RTL8169_PHY_TIMEOUT);
		}
	}

	rtl_irq_enable_all(tp);
}

static void rtl_task(struct work_struct *work)
{
	static const struct {
		int bitnr;
		void (*action)(struct rtl8169_private *);
	} rtl_work[] = {
		/* XXX - keep rtl_slow_event_work() as first element. */
		{ RTL_FLAG_TASK_SLOW_PENDING,	rtl_slow_event_work },
		{ RTL_FLAG_TASK_RESET_PENDING,	rtl_reset_work },
		{ RTL_FLAG_TASK_PHY_PENDING,	rtl_phy_work }
	};
	struct rtl8169_private *tp =
		container_of(work, struct rtl8169_private, wk.work);
	struct net_device *dev = tp->dev;
	int i;

	rtl_lock_work(tp);

	if (!netif_running(dev) ||
		!test_bit(RTL_FLAG_TASK_ENABLED, tp->wk.flags))
		goto out_unlock;

	for (i = 0; i < ARRAY_SIZE(rtl_work); i++) {
		bool pending;

		pending = test_and_clear_bit(rtl_work[i].bitnr, tp->wk.flags);
		if (pending)
			rtl_work[i].action(tp);
	}

out_unlock:
	rtl_unlock_work(tp);
}

static int rtl8169_poll(struct napi_struct *napi, int budget)
{
	struct rtl8169_private *tp = container_of(napi, struct rtl8169_private, napi);
	struct net_device *dev = tp->dev;
	u16 enable_mask = RTL_EVENT_NAPI | tp->event_slow;
	int work_done= 0;
	u16 status;

	status = rtl_get_events(tp);
	rtl_ack_events(tp, status & ~tp->event_slow);

	if (status & RTL_EVENT_NAPI_RX)
		work_done = rtl_rx(dev, tp, (u32) budget);

	if (status & RTL_EVENT_NAPI_TX)
		rtl_tx(dev, tp);

	if (status & tp->event_slow) {
		enable_mask &= ~tp->event_slow;

		rtl_schedule_task(tp, RTL_FLAG_TASK_SLOW_PENDING);
	}

	if (work_done < budget) {
		napi_complete(napi);

		rtl_irq_enable(tp, enable_mask);
		mmiowb();
	}

	return work_done;
}

static void rtl8169_rx_missed(struct net_device *dev, void __iomem *ioaddr)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	if (tp->mac_version > RTL_GIGA_MAC_VER_06)
		return;

	dev->stats.rx_missed_errors += (RTL_R32(RxMissed) & 0xffffff);
	RTL_W32(RxMissed, 0);
}

static void rtl8169_down(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	void __iomem *ioaddr = tp->mmio_addr;

	del_timer_sync(&tp->timer);

	napi_disable(&tp->napi);
	netif_stop_queue(dev);

	rtl8169_hw_reset(tp);
	/*
	 * At this point device interrupts can not be enabled in any function,
	 * as netif_running is not true (rtl8169_interrupt, rtl8169_reset_task)
	 * and napi is disabled (rtl8169_poll).
	 */
	rtl8169_rx_missed(dev, ioaddr);

	/* Give a racing hard_start_xmit a few cycles to complete. */
	synchronize_sched();

	rtl8169_tx_clear(tp);

	rtl8169_rx_clear(tp);

	rtl_pll_power_down(tp);
}

static int rtl8169_close(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	struct platform_device *pdev = tp->pdev;

//	pm_runtime_get_sync(&pdev->dev);

	/* Update counters before going down */
	rtl8169_update_counters(dev);

	rtl_lock_work(tp);
	clear_bit(RTL_FLAG_TASK_ENABLED, tp->wk.flags);

	rtl8169_down(dev);
	rtl_unlock_work(tp);

	free_irq(dev->irq, dev);

	if (tp->acp_enable) {
		kfree(tp->RxDescArray);
		kfree(tp->TxDescArray);
	} else {
		dma_free_coherent(&pdev->dev, R8169_RX_RING_BYTES,
				  tp->RxDescArray, tp->RxPhyAddr);
		dma_free_coherent(&pdev->dev, R8169_TX_RING_BYTES,
				  tp->TxDescArray, tp->TxPhyAddr);
	}
	tp->TxDescArray = NULL;
	tp->RxDescArray = NULL;

//	pm_runtime_put_sync(&pdev->dev);

	return 0;
}

#ifdef CONFIG_NET_POLL_CONTROLLER
static void rtl8169_netpoll(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	rtl8169_interrupt(tp->pdev->irq, dev);
}
#endif

static int rtl_open(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	void __iomem *ioaddr = tp->mmio_addr;
	struct platform_device *pdev = tp->pdev;
	int retval = -ENOMEM;
	int node = dev->dev.parent ? dev_to_node(dev->dev.parent) : -1;

//	pm_runtime_get_sync(&pdev->dev);

	/*
	 * Rx and Tx descriptors needs 256 bytes alignment.
	 * dma_alloc_coherent provides more.
	 */
	if (tp->acp_enable) {
		tp->TxDescArray = kzalloc_node(R8169_TX_RING_BYTES, GFP_KERNEL,
						node);
		tp->TxPhyAddr = virt_to_phys(tp->TxDescArray);
	} else {
		tp->TxDescArray = dma_alloc_coherent(&pdev->dev,
			R8169_TX_RING_BYTES, &tp->TxPhyAddr, GFP_KERNEL);
	}
	if (!tp->TxDescArray)
		goto err_pm_runtime_put;

	if (tp->acp_enable) {
		tp->RxDescArray = kzalloc_node(R8169_RX_RING_BYTES, GFP_KERNEL,
						node);
		tp->RxPhyAddr = virt_to_phys(tp->RxDescArray);
	} else {
		tp->RxDescArray = dma_alloc_coherent(&pdev->dev,
			R8169_RX_RING_BYTES, &tp->RxPhyAddr, GFP_KERNEL);
	}
	if (!tp->RxDescArray)
		goto err_free_tx_0;

	retval = rtl8169_init_ring(dev);
	if (retval < 0)
		goto err_free_rx_1;

	INIT_WORK(&tp->wk.work, rtl_task);

	smp_mb();

	//rtl_request_firmware(tp);

	retval = request_irq(dev->irq, rtl8169_interrupt,
				 (tp->features & RTL_FEATURE_MSI) ? 0 : IRQF_SHARED,
				 dev->name, dev);
	if (retval < 0)
		goto err_release_fw_2;

	rtl_lock_work(tp);

	set_bit(RTL_FLAG_TASK_ENABLED, tp->wk.flags);

	napi_enable(&tp->napi);

	rtl8169_init_phy(dev, tp);

	__rtl8169_set_features(dev, dev->features);

	rtl_pll_power_up(tp);

	rtl_hw_start(dev);

	netif_start_queue(dev);

	rtl_unlock_work(tp);

	tp->saved_wolopts = 0;
//	pm_runtime_put_noidle(&pdev->dev);

	rtl8169_check_link_status(dev, tp, ioaddr);
out:
	return retval;

err_release_fw_2:
	rtl_release_firmware(tp);
	rtl8169_rx_clear(tp);
err_free_rx_1:
	if (tp->acp_enable)
		kfree(tp->RxDescArray);
	else
		dma_free_coherent(&pdev->dev, R8169_RX_RING_BYTES,
				  tp->RxDescArray, tp->RxPhyAddr);
	tp->RxDescArray = NULL;
err_free_tx_0:
	if (tp->acp_enable)
		kfree(tp->TxDescArray);
	else
		dma_free_coherent(&pdev->dev, R8169_TX_RING_BYTES,
				  tp->TxDescArray, tp->TxPhyAddr);
	tp->TxDescArray = NULL;
err_pm_runtime_put:
//	pm_runtime_put_noidle(&pdev->dev);
	goto out;
}

static struct rtnl_link_stats64 *
rtl8169_get_stats64(struct net_device *dev, struct rtnl_link_stats64 *stats)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	void __iomem *ioaddr = tp->mmio_addr;
	unsigned int start;

	if (netif_running(dev))
		rtl8169_rx_missed(dev, ioaddr);

	do {
		start = u64_stats_fetch_begin_irq(&tp->rx_stats.syncp);
		stats->rx_packets = tp->rx_stats.packets;
		stats->rx_bytes	= tp->rx_stats.bytes;
	} while (u64_stats_fetch_retry_irq(&tp->rx_stats.syncp, start));


	do {
		start = u64_stats_fetch_begin_irq(&tp->tx_stats.syncp);
		stats->tx_packets = tp->tx_stats.packets;
		stats->tx_bytes	= tp->tx_stats.bytes;
	} while (u64_stats_fetch_retry_irq(&tp->tx_stats.syncp, start));

	stats->rx_dropped	= dev->stats.rx_dropped;
	stats->tx_dropped	= dev->stats.tx_dropped;
	stats->rx_length_errors = dev->stats.rx_length_errors;
	stats->rx_errors	= dev->stats.rx_errors;
	stats->rx_crc_errors	= dev->stats.rx_crc_errors;
	stats->rx_fifo_errors	= dev->stats.rx_fifo_errors;
	stats->rx_missed_errors = dev->stats.rx_missed_errors;

	return stats;
}

#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
static void r8169soc_eee_init(struct rtl8169_private *tp, bool enable);
#endif /* CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */

static void rtl8169_net_suspend(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	if (!netif_running(dev))
		return;

	netif_device_detach(dev);
	netif_stop_queue(dev);

	rtl_lock_work(tp);
	napi_disable(&tp->napi);
	clear_bit(RTL_FLAG_TASK_ENABLED, tp->wk.flags);
	rtl_unlock_work(tp);

	/* disable EEE if it is enabled */
	if (tp->eee_enable) {
		/* power down PHY */
		MDIO_LOCK;
		rtl_writephy(tp, 0x1f, 0x0000);
		rtl_patchphy(tp, MII_BMCR, BMCR_PDOWN);
		MDIO_UNLOCK;

		#if defined(CONFIG_ARCH_RTD129x)
		MDIO_LOCK;
		r8169_mmd_write(tp, 0x7, 0x3c, 0);
		MDIO_UNLOCK;

		r8169soc_ocp_reg_write(tp, 0xe040, (r8169soc_ocp_reg_read(tp, 0xe040) & ~0x3));   // turn off EEE
		r8169soc_ocp_reg_write(tp, 0xe080, (r8169soc_ocp_reg_read(tp, 0xe080) & ~0x2));   // turn off EEE+
		#elif defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
		r8169soc_eee_init(tp, false);
		#endif /* CONFIG_ARCH_RTD129x | CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */

		mdelay(100); // wait PHY ready
		rtl8169_phy_reset(dev, tp);
	}

	rtl8169_hw_reset(tp);

	rtl_pll_power_down(tp);
}

#ifdef CONFIG_PM

static int rtl8169_suspend(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct rtl8169_private *tp = netdev_priv(ndev);
	void __iomem *ioaddr = tp->mmio_addr;

	printk(KERN_ERR "[RTK_ETN] Enter %s\n", __func__);

	rtl8169_net_suspend(ndev);

	/* turn off LED, and current solution is switch pad to GPIO input */
	#if defined(CONFIG_ARCH_RTD129x)
	writel(readl(tp->mmio_clkaddr + 0x310) & ~0x3C000000,
		(tp->mmio_clkaddr + 0x310));
	#elif defined(CONFIG_ARCH_RTD139x)
	writel(readl(tp->mmio_pinmuxaddr + ISO_TESTMUX_MUXPAD1) & ~0x000000F0,
		(tp->mmio_pinmuxaddr + ISO_TESTMUX_MUXPAD1));
	#elif defined(CONFIG_ARCH_RTD16xx)
	writel(readl(tp->mmio_pinmuxaddr + ISO_TESTMUX_MUXPAD0) & ~0x3C000000,
		(tp->mmio_pinmuxaddr + ISO_TESTMUX_MUXPAD0));
	writel(readl(tp->mmio_pinmuxaddr + ISO_TESTMUX_MUXPAD2) & ~0x38000000,
		(tp->mmio_pinmuxaddr + ISO_TESTMUX_MUXPAD2));
	#endif /* CONFIG_ARCH_RTD129x | CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */

	if(RTK_PM_STATE == PM_SUSPEND_STANDBY){
		//For idle mode
		printk(KERN_ERR "[RTK_ETN] %s Idle mode\n", __func__);

		/* stop PLL for power saving */
		RTL_W16(CPlusCmd, RTL_R16(CPlusCmd) | BIT(2));
	}else{
		//For suspend mode
		printk(KERN_ERR "[RTK_ETN] %s Suspend mode\n", __func__);
	}


	printk(KERN_ERR "[RTK_ETN] Exit %s\n", __func__);

	return 0;
}

static void __rtl8169_resume(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	u32 val;
	//u32 i,j;

	netif_device_attach(dev);
/*
	printk(KERN_INFO "resume r8169 eth0 gphy work \n");

	i=readl(IOMEM(0xFE000000));
	i = i & 0xffffbfff;
	writel(i,IOMEM(0xFE000000));

	j=readl(IOMEM(0xFE007088));
	j = j & 0xfffff9ff;
	writel(j,IOMEM(0xFE007088));


	i=readl(IOMEM(0xFE000000));
	i = i | 0x00004000;
	writel(i,IOMEM(0xFE000000));

	j=readl(IOMEM(0xFE007088));
	j = j | 0x00000600;
	writel(j,IOMEM(0xFE007088));

	msleep(300);
*/
	/* turn on LED */
	#if defined(CONFIG_ARCH_RTD129x)
	val = readl(tp->mmio_clkaddr + 0x310) & ~0x3C000000;
	writel(val | 0x14000000, (tp->mmio_clkaddr + 0x310));
	#elif defined(CONFIG_ARCH_RTD139x)
	val = readl(tp->mmio_pinmuxaddr + ISO_TESTMUX_MUXPAD1) & ~0x000000F0;
	writel(val | 0x50, (tp->mmio_pinmuxaddr + ISO_TESTMUX_MUXPAD1));
	#elif defined(CONFIG_ARCH_RTD16xx)
	val = readl(tp->mmio_pinmuxaddr + ISO_TESTMUX_MUXPAD0) & ~0x3C000000;
	writel(val | 0x14000000, (tp->mmio_pinmuxaddr + ISO_TESTMUX_MUXPAD0));
	val = readl(tp->mmio_pinmuxaddr + ISO_TESTMUX_MUXPAD2) & ~0x38000000;
	writel(val | 0x18000000, (tp->mmio_pinmuxaddr + ISO_TESTMUX_MUXPAD2));
	#endif /* CONFIG_ARCH_RTD129x | CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */

	rtl_pll_power_up(tp);
	rtl_rar_set(tp, tp->dev->dev_addr);

	rtl_lock_work(tp);
	napi_enable(&tp->napi);
	set_bit(RTL_FLAG_TASK_ENABLED, tp->wk.flags);
	rtl_unlock_work(tp);

	rtl_schedule_task(tp, RTL_FLAG_TASK_RESET_PENDING);
}

static int rtl8169_resume(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct rtl8169_private *tp = netdev_priv(ndev);
	void __iomem *ioaddr = tp->mmio_addr;

	printk(KERN_ERR "[RTK_ETN] Enter %s\n", __func__);

	if(RTK_PM_STATE == PM_SUSPEND_STANDBY){
		//For idle mode
		printk(KERN_ERR "[RTK_ETN] %s Idle mode\n", __func__);

		/* enable PLL from power saving */
		RTL_W16(CPlusCmd, RTL_R16(CPlusCmd) & ~BIT(2));
	}else{
		//For suspend mode
		printk(KERN_ERR "[RTK_ETN] %s Suspend mode\n", __func__);
	}

	if (netif_running(ndev))
		__rtl8169_resume(ndev);

	/* enable EEE according to tp->eee_enable */
	if (tp->eee_enable) {
		/* power down PHY */
		MDIO_LOCK;
		rtl_writephy(tp, 0x1f, 0x0000);
		rtl_patchphy(tp, MII_BMCR, BMCR_PDOWN);
		MDIO_UNLOCK;

		#if defined(CONFIG_ARCH_RTD129x)
		MDIO_LOCK;
		r8169_mmd_write(tp, 0x7, 0x3c, 0x6);
		MDIO_UNLOCK;

		r8169soc_ocp_reg_write(tp, 0xe040, (r8169soc_ocp_reg_read(tp, 0xe040) | 0x3));   // turn on EEE
		r8169soc_ocp_reg_write(tp, 0xe080, (r8169soc_ocp_reg_read(tp, 0xe080) | 0x2));   // turn on EEE+
		#elif defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
		r8169soc_eee_init(tp, true);
		#endif /* CONFIG_ARCH_RTD129x | CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */

		mdelay(100); // wait PHY ready
	}

	rtl8169_init_phy(ndev, tp);

	printk(KERN_ERR "[RTK_ETN] Exit %s\n", __func__);

	return 0;
}

static __maybe_unused int rtl8169_runtime_suspend(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct rtl8169_private *tp = netdev_priv(ndev);

	if (!tp->TxDescArray)
		return 0;

	rtl_lock_work(tp);
	tp->saved_wolopts = __rtl8169_get_wol(tp);
	__rtl8169_set_wol(tp, WAKE_ANY);
	rtl_unlock_work(tp);

	rtl8169_net_suspend(ndev);

	return 0;
}

static __maybe_unused int rtl8169_runtime_resume(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct rtl8169_private *tp = netdev_priv(ndev);

	if (!tp->TxDescArray)
		return 0;

	rtl_lock_work(tp);
	__rtl8169_set_wol(tp, tp->saved_wolopts);
	tp->saved_wolopts = 0;
	rtl_unlock_work(tp);

	rtl8169_init_phy(ndev, tp);

	__rtl8169_resume(ndev);

	return 0;
}

static __maybe_unused int rtl8169_runtime_idle(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct rtl8169_private *tp = netdev_priv(ndev);

	return tp->TxDescArray ? -EBUSY : 0;
}

static const struct dev_pm_ops rtl8169_pm_ops = {
	.suspend		= rtl8169_suspend,
	.resume			= rtl8169_resume,
	.freeze			= rtl8169_suspend,
	.thaw			= rtl8169_resume,
	.poweroff		= rtl8169_suspend,
	.restore		= rtl8169_resume,
	.runtime_suspend	= rtl8169_runtime_suspend,
	.runtime_resume		= rtl8169_runtime_resume,
	.runtime_idle		= rtl8169_runtime_idle,
};

#define RTL8169_PM_OPS	(&rtl8169_pm_ops)

#else /* !CONFIG_PM */

#define RTL8169_PM_OPS	NULL

#endif /* !CONFIG_PM */

static void rtl_wol_shutdown_quirk(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;

	/* WoL fails with 8168b when the receiver is disabled. */
	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_11:
	case RTL_GIGA_MAC_VER_12:
	case RTL_GIGA_MAC_VER_17:
		//pci_clear_master(tp->pdev);

		RTL_W8(ChipCmd, CmdRxEnb);
		/* PCI commit */
		RTL_R8(ChipCmd);
		break;
	default:
		break;
	}
}

static void rtl_shutdown(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);
	struct rtl8169_private *tp = netdev_priv(dev);
//	struct device *d = &pdev->dev;

//	pm_runtime_get_sync(d);

	rtl8169_net_suspend(dev);

	/* Restore original MAC address */
	rtl_rar_set(tp, dev->perm_addr);

	rtl8169_hw_reset(tp);

	if (system_state == SYSTEM_POWER_OFF) {
		if (__rtl8169_get_wol(tp) & WAKE_ANY) {
			rtl_wol_suspend_quirk(tp);
			rtl_wol_shutdown_quirk(tp);
		}

		//pci_wake_from_d3(pdev, true);
		//pci_set_power_state(pdev, PCI_D3hot);
	}

//	pm_runtime_put_noidle(d);
}

static int rtl_remove_one(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);
	struct rtl8169_private *tp = netdev_priv(dev);

	if (tp->mac_version == RTL_GIGA_MAC_VER_27 ||
		tp->mac_version == RTL_GIGA_MAC_VER_28 ||
		tp->mac_version == RTL_GIGA_MAC_VER_31) {
		rtl8168_driver_stop(tp);
	}


#ifdef RTL_PROC
	do{
		if(tp->dir_dev==NULL)
			break;

		remove_proc_entry("wol_enable", tp->dir_dev);
		remove_proc_entry("eee", tp->dir_dev);
		remove_proc_entry("test", tp->dir_dev);

		if(rtw_proc==NULL)
			break;

		remove_proc_entry(MODULENAME, rtw_proc);
		remove_proc_entry("eth0", init_net.proc_net);

			rtw_proc=NULL;

	}while(0);
#endif

	cancel_work_sync(&tp->wk.work);

	netif_napi_del(&tp->napi);

	unregister_netdev(dev);

	rtl_release_firmware(tp);

//	if (pci_dev_run_wake(pdev))
//		pm_runtime_get_noresume(&pdev->dev);

	/* restore original MAC address */
	rtl_rar_set(tp, dev->perm_addr);

//	rtl_disable_msi(pdev, tp);
	rtl8169_release_board(pdev, dev, tp->mmio_addr);
	platform_set_drvdata(pdev, NULL);

	/* Yukuen: Add for link status uevent. 20150206 */
	if(tp->kthr){
		kthread_stop(tp->kthr);
		tp->kthr = NULL;
	}
	return 0;
}

static const struct net_device_ops rtl_netdev_ops = {
	.ndo_open		= rtl_open,
	.ndo_stop		= rtl8169_close,
	.ndo_get_stats64	= rtl8169_get_stats64,
	.ndo_start_xmit		= rtl8169_start_xmit,
	.ndo_tx_timeout		= rtl8169_tx_timeout,
	.ndo_validate_addr	= eth_validate_addr,
	.ndo_change_mtu		= rtl8169_change_mtu,
	.ndo_fix_features	= rtl8169_fix_features,
	.ndo_set_features	= rtl8169_set_features,
	.ndo_set_mac_address	= rtl_set_mac_address,
	.ndo_do_ioctl		= rtl8169_ioctl,
	.ndo_set_rx_mode	= rtl_set_rx_mode,
#ifdef CONFIG_NET_POLL_CONTROLLER
	.ndo_poll_controller	= rtl8169_netpoll,
#endif

};

static struct rtl_cfg_info {
	void (*hw_start)(struct net_device *);
	unsigned int region;
	unsigned int align;
	u16 event_slow;
	unsigned features;
	u8 default_ver;
} rtl_cfg_infos [] = {
	[RTL_CFG_0] = {
		.hw_start	= rtl_hw_start_8169,
		.region		= 1,
		.align		= 0,
		.event_slow	= SYSErr | LinkChg | RxOverflow | RxFIFOOver,
		.features	= RTL_FEATURE_GMII,
		.default_ver	= RTL_GIGA_MAC_VER_01,
	},
	[RTL_CFG_1] = {
		.hw_start	= rtl_hw_start_8168,
		.region		= 2,
		.align		= 8,
		.event_slow	= SYSErr | LinkChg | RxOverflow,
		.features	= RTL_FEATURE_GMII | RTL_FEATURE_MSI,
		.default_ver	= RTL_GIGA_MAC_VER_11,
	},
	[RTL_CFG_2] = {
		.hw_start	= rtl_hw_start_8101,
		.region		= 2,
		.align		= 8,
		.event_slow	= SYSErr | LinkChg | RxOverflow | RxFIFOOver |
				  PCSTimeout,
		.features	= RTL_FEATURE_MSI,
		.default_ver	= RTL_GIGA_MAC_VER_13,
	}
};

/* Cfg9346_Unlock assumed. */
static unsigned rtl_try_msi(struct rtl8169_private *tp,
				const struct rtl_cfg_info *cfg)
{
	void __iomem *ioaddr = tp->mmio_addr;
	unsigned msi = 0;
	u8 cfg2;

	cfg2 = RTL_R8(Config2) & ~MSIEnable;
	if (cfg->features & RTL_FEATURE_MSI) {
#if 0

		if (pci_enable_msi(tp->pci_dev)) {
			netif_info(tp, hw, tp->dev, "no MSI. Back to INTx.\n");
		} else {
			cfg2 |= MSIEnable;
			msi = RTL_FEATURE_MSI;
		}
#endif
	}
	if (tp->mac_version <= RTL_GIGA_MAC_VER_06)
		RTL_W8(Config2, cfg2);
	return msi;
}

DECLARE_RTL_COND(rtl_link_list_ready_cond)
{
	void __iomem *ioaddr = tp->mmio_addr;

	return RTL_R8(MCU) & LINK_LIST_RDY;
}

DECLARE_RTL_COND(rtl_rxtx_empty_cond)
{
	void __iomem *ioaddr = tp->mmio_addr;

	return (RTL_R8(MCU) & RXTX_EMPTY) == RXTX_EMPTY;
}

static void rtl_hw_init_8168g(struct rtl8169_private *tp)
{
	void __iomem *ioaddr = tp->mmio_addr;
	u32 data;

	tp->ocp_base = OCP_STD_PHY_BASE;

	RTL_W32(MISC, RTL_R32(MISC) | RXDV_GATED_EN);

	if (!rtl_udelay_loop_wait_high(tp, &rtl_txcfg_empty_cond, 100, 42))
		return;

	if (!rtl_udelay_loop_wait_high(tp, &rtl_rxtx_empty_cond, 100, 42))
		return;

	RTL_W8(ChipCmd, RTL_R8(ChipCmd) & ~(CmdTxEnb | CmdRxEnb));
	msleep(1);		// yukuen mask for SMP issue
	RTL_W8(MCU, RTL_R8(MCU) & ~NOW_IS_OOB);

	data = r8168_mac_ocp_read(tp, 0xe8de);
	data &= ~(1 << 14);
	r8168_mac_ocp_write(tp, 0xe8de, data);

	if (!rtl_udelay_loop_wait_high(tp, &rtl_link_list_ready_cond, 100, 42))
		return;

	data = r8168_mac_ocp_read(tp, 0xe8de);
	data |= (1 << 15);
	r8168_mac_ocp_write(tp, 0xe8de, data);

	if (!rtl_udelay_loop_wait_high(tp, &rtl_link_list_ready_cond, 100, 42))
		return;
}

static void rtl_hw_initialize(struct rtl8169_private *tp)
{
	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_40:
	case RTL_GIGA_MAC_VER_41:
	case RTL_GIGA_MAC_VER_42:
	case RTL_GIGA_MAC_VER_43:
		rtl_hw_init_8168g(tp);
		break;

	default:
		break;
	}
}
#ifdef RTL_PROC
static ssize_t read_proc(struct file *filp,char *buf,size_t count,loff_t *offp )
{

	ssize_t len = 0;
	static int finished = 0;

	if ( finished ) {
		printk(KERN_INFO "procfs_read: END\n");
		finished = 0;
		return 0;
	}

	finished = 1;

	printk(KERN_INFO "read procfs ethernet wol_enable = %x \n",wol_enable);

	len = sprintf(buf,"%d\n", wol_enable);
	return len;
}

static ssize_t write_proc(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
	char tmp[32];
	u32 val,num;

	if (buffer && !copy_from_user(tmp, buffer, sizeof(tmp)))
	{
		num = sscanf(tmp, "%x", &val);
		wol_enable=val;
		printk(KERN_INFO "write procfs ethernet wol_enable = %x \n",wol_enable);
	}
	return count;
}

static const struct file_operations proc_fops = {
.read= read_proc,
.write= write_proc,
};

static int eee_read_proc(struct seq_file *m, void *v)
{

	struct net_device *dev = m->private;
	struct rtl8169_private *tp = netdev_priv(dev);
	unsigned short e040, e080;

	e040 = r8169soc_ocp_reg_read(tp, 0xe040);   // EEE
	e080 = r8169soc_ocp_reg_read(tp, 0xe080);   // EEE+
	pr_err("%s: eee = %d, OCP 0xe040 = 0x%x, OCP 0xe080 = 0x%x\n", dev->name, tp->eee_enable, e040, e080);
	r8169_display_eee_info(dev, tp);

	seq_putc(m, '\n');
	return 0;

}

static ssize_t eee_write_proc(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
	char tmp[32];
	u32 val = 0,num;
	struct net_device *dev = (struct net_device *) ((struct seq_file *)file->private_data)->private;
	struct rtl8169_private *tp = netdev_priv(dev);

	if (buffer && !copy_from_user(tmp, buffer, sizeof(tmp)))
	{
		num = sscanf(tmp, "%x", &val);
		pr_err("write %s eee = %x\n", dev->name, val);
	}

	if (val > 0 && tp->eee_enable == false) {
		tp->eee_enable = true;

		/* power down PHY */
		MDIO_LOCK;
		rtl_writephy(tp, 0x1f, 0x0000);
		rtl_patchphy(tp, MII_BMCR, BMCR_PDOWN);
		MDIO_UNLOCK;

		#if defined(CONFIG_ARCH_RTD129x)
		MDIO_LOCK;
		r8169_mmd_write(tp, 0x7, 0x3c, 0x6);
		MDIO_UNLOCK;

		r8169soc_ocp_reg_write(tp, 0xe040, (r8169soc_ocp_reg_read(tp, 0xe040) | 0x3));   // turn on EEE
		r8169soc_ocp_reg_write(tp, 0xe080, (r8169soc_ocp_reg_read(tp, 0xe080) | 0x2));   // turn on EEE+
		#elif defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
		r8169soc_eee_init(tp, tp->eee_enable);
		#endif /* CONFIG_ARCH_RTD129x | CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */

		mdelay(100); // wait PHY ready
		rtl8169_phy_reset(dev, tp);
	} else if (val == 0 && tp->eee_enable == true) {
		tp->eee_enable = false;

		/* power down PHY */
		MDIO_LOCK;
		rtl_writephy(tp, 0x1f, 0x0000);
		rtl_patchphy(tp, MII_BMCR, BMCR_PDOWN);
		MDIO_UNLOCK;

		#if defined(CONFIG_ARCH_RTD129x)
		MDIO_LOCK;
		r8169_mmd_write(tp, 0x7, 0x3c, 0);
		MDIO_UNLOCK;

		r8169soc_ocp_reg_write(tp, 0xe040, (r8169soc_ocp_reg_read(tp, 0xe040) & ~0x3));   // turn off EEE
		r8169soc_ocp_reg_write(tp, 0xe080, (r8169soc_ocp_reg_read(tp, 0xe080) & ~0x2));   // turn off EEE+
		#elif defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
		r8169soc_eee_init(tp, tp->eee_enable);
		#endif /* CONFIG_ARCH_RTD129x | CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */

		mdelay(100); // wait PHY ready
		rtl8169_phy_reset(dev, tp);
	}
	return count;
}

/*
 * seq_file wrappers for procfile show routines.
 */
static int eee_proc_open(struct inode *inode, struct file *file)
{
	struct net_device *dev = proc_get_parent_data(inode);

	return single_open(file, eee_read_proc, dev);
}

static const struct file_operations eee_proc_fops = {
	.open           = eee_proc_open,
	.read           = seq_read,
	.write          = eee_write_proc,
	.llseek         = seq_lseek,
	.release        = single_release,
};

static void r8169soc_dump_regs(struct rtl8169_private *tp) {
	u32 addr;
	u32 val;
	u32 i;

	pr_err("eee = %d\n", tp->eee_enable);
	#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
	pr_err("output_mode = %d, bypass = %d, acp = %d\n\n",
		tp->output_mode, tp->bypass_enable, tp->acp_enable);

	#endif /* CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */

	pr_err("ISO_UMSK_ISR\t[0x98007004] = %08x\n",
		readl(tp->mmio_clkaddr + ISO_UMSK_ISR));
	pr_err("ISO_POWERCUT_ETN\t[0x9800705c] = %08x\n",
		readl(tp->mmio_clkaddr + ISO_POWERCUT_ETN));
	pr_err("ISO_ETN_TESTIO\t[0x98007060] = %08x\n",
		readl(tp->mmio_clkaddr + ISO_ETN_TESTIO));
	pr_err("ETN_RESET_CTRL\t[0x98007088] = %08x\n",
		readl(tp->mmio_clkaddr + ISO_SOFT_RESET));
	pr_err("ETN_CLK_CTRL\t[0x9800708c] = %08x\n",
		readl(tp->mmio_clkaddr + ISO_CLOCK_ENABLE));

	if (tp->output_mode != OUTPUT_EMBEDDED_PHY) {
		#if defined(CONFIG_ARCH_RTD139x)
		pr_err("SDS_REG02\t[0x981c8008] = %08x\n",
			readl(tp->mmio_sdsaddr + SDS_REG02));
		pr_err("SDS_REG28\t[0x981c8070] = %08x\n",
			readl(tp->mmio_sdsaddr + SDS_REG28));
		pr_err("SDS_REG29\t[0x981c8074] = %08x\n",
			readl(tp->mmio_sdsaddr + SDS_REG29));
		pr_err("SDS_MISC\t\t[0x981c9804] = %08x\n",
			readl(tp->mmio_sdsaddr + SDS_MISC));
		pr_err("SDS_LINK\t\t[0x981c9810] = %08x\n",
			readl(tp->mmio_sdsaddr + SDS_LINK));
		#elif defined(CONFIG_ARCH_RTD16xx)
		pr_err("SDS_REG02\t[0x981c8008] = %08x\n",
			readl(tp->mmio_sdsaddr + SDS_REG02));
		pr_err("SDS_MISC\t\t[0x981c9804] = %08x\n",
			readl(tp->mmio_sdsaddr + SDS_MISC));
		pr_err("SDS_LINK\t\t[0x981c9808] = %08x\n",
			readl(tp->mmio_sdsaddr + SDS_LINK));
		pr_err("SDS_DEBUG\t\t[0x981c9810] = %08x\n",
			readl(tp->mmio_sdsaddr + SDS_DEBUG));
		#endif /* CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */
	}

	pr_err("ETN MAC regs:\n");
	for (i = 0; i < 256; i += 4) {
		addr = 0x98106000 + i;
		val = readl(tp->mmio_addr + i);
		pr_err("[%08x] = %08x\n", addr, val);
	}
}

static int test_read_proc(struct seq_file *m, void *v)
{

	struct net_device *dev = m->private;
	struct rtl8169_private *tp = netdev_priv(dev);

	r8169soc_dump_regs(tp);

	seq_putc(m, '\n');
	return 0;

}

static ssize_t test_write_proc(struct file *file, const char __user *buffer,
				size_t count, loff_t *pos)
{
	char tmp[32];
	u32 val,num;
	struct net_device *dev = (struct net_device *)
			((struct seq_file *)file->private_data)->private;
	struct rtl8169_private *tp = netdev_priv(dev);

	if (buffer && !copy_from_user(tmp, buffer, sizeof(tmp)))
	{
		num = sscanf(tmp, "%x", &val);
		pr_err("%s test case 0x%x\n", dev->name, val);
	}

	if (val & BIT(1)) {
		pr_err("BIT 1 = 1: MDIO lock\n");
		MDIO_LOCK;
	} else {
		pr_err("BIT 1 = 0: MDIO unlock\n");
		MDIO_UNLOCK;
	}

	return count;
}

/*
 * seq_file wrappers for procfile show routines.
 */
static int test_proc_open(struct inode *inode, struct file *file)
{
	struct net_device *dev = proc_get_parent_data(inode);

	return single_open(file, test_read_proc, dev);
}

static const struct file_operations test_proc_fops = {
	.open           = test_proc_open,
	.read           = seq_read,
	.write          = test_write_proc,
	.llseek         = seq_lseek,
	.release        = single_release,
};

#endif

#if defined(CONFIG_ARCH_RTD139x)
static void r8169soc_reset_phy_gmac(struct rtl8169_private *tp)
{
	u32 tmp;
	struct clk *clk_etn_sys  = clk_get(&tp->pdev->dev, "etn_sys");
	struct clk *clk_etn_250m = clk_get(&tp->pdev->dev, "etn_250m");
	struct reset_control *rstc_gphy =
		reset_control_get(&tp->pdev->dev, "gphy");
	struct reset_control *rstc_gmac =
		reset_control_get(&tp->pdev->dev, "gmac");
	struct clk *clk_en_sds;
	struct reset_control *rstc_sds_reg;
	struct reset_control *rstc_sds;
	struct reset_control *rstc_pcie0_power;
	struct reset_control *rstc_pcie0_phy;
	struct reset_control *rstc_pcie0_sgmii_mdio;
	struct reset_control *rstc_pcie0_phy_mdio;

	clk_prepare_enable(clk_etn_sys);
	clk_prepare_enable(clk_etn_250m);

	/* reg_0x9800708c[12:11] = 00 */
	/* ISO spec, clock enable bit for etn clock & etn 250MHz */
	clk_disable_unprepare(clk_etn_sys);
	clk_disable_unprepare(clk_etn_250m);

	/* reg_0x98007088[10:9] = 00 */
	/* ISO spec, rstn_gphy & rstn_gmac */
	reset_control_assert(rstc_gphy);
	reset_control_assert(rstc_gmac);

	/* reg_0x98007060[1] = 1 */
	/* ISO spec, bypass mode enable */
	tmp = readl(tp->mmio_clkaddr + ISO_ETN_TESTIO);
	tmp |= BIT(1);
	writel(tmp, tp->mmio_clkaddr + ISO_ETN_TESTIO);

	/* reg_0x9800705c = 0x00616703 */
	/* ISO spec, default value */
	writel(0x00616703, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

	/* RESET for SGMII if needed */
	if (tp->output_mode != OUTPUT_EMBEDDED_PHY) {
		clk_en_sds = clk_get(&tp->pdev->dev, "sds");
		rstc_sds_reg = reset_control_get(&tp->pdev->dev, "sds_reg");
		rstc_sds = reset_control_get(&tp->pdev->dev, "sds");
		rstc_pcie0_power =
			reset_control_get(&tp->pdev->dev, "pcie0_power");
		rstc_pcie0_phy =
			reset_control_get(&tp->pdev->dev, "pcie0_phy");
		rstc_pcie0_sgmii_mdio =
			reset_control_get(&tp->pdev->dev, "pcie0_sgmii_mdio");
		rstc_pcie0_phy_mdio =
			reset_control_get(&tp->pdev->dev, "pcie0_phy_mdio");

		clk_prepare_enable(clk_en_sds);

		/* reg_0x9800000c[7] = 0 */
		/* CRT spec, clk_en_sds */
		clk_disable_unprepare(clk_en_sds);

		/* reg_0x98000000[4:3] = 00 */
		/* CRT spec, rstn_sds_reg & rstn_sds */
		reset_control_assert(rstc_sds);
		reset_control_assert(rstc_sds_reg);

		/* reg_0x98000004[7] = 0 */
		/* reg_0x98000004[14] = 0 */
		/* CRT spec, rstn_pcie0_power & rstn_pcie0_phy */
		reset_control_assert(rstc_pcie0_power);
		reset_control_assert(rstc_pcie0_phy);

		/* reg_0x98000050[13] = 0 */
		/* reg_0x98000050[16] = 0 */
		/* CRT spec, rstn_pcie0_sgmii_mdio & rstn_pcie0_phy_mdio */
		reset_control_assert(rstc_pcie0_sgmii_mdio);
		reset_control_assert(rstc_pcie0_phy_mdio);

		reset_control_put(rstc_sds_reg);
		reset_control_put(rstc_sds);
		reset_control_put(rstc_pcie0_power);
		reset_control_put(rstc_pcie0_phy);
		reset_control_put(rstc_pcie0_sgmii_mdio);
		reset_control_put(rstc_pcie0_phy_mdio);
	}

	mdelay(100);

	/* release resource */
	reset_control_put(rstc_gphy);
	reset_control_put(rstc_gmac);
}

static void r8169soc_acp_init(struct rtl8169_private *tp)
{
	u32 tmp;

	/* SBX spec, Select ETN access DDR path. */
	if (tp->acp_enable) {
		/* reg_0x9801c20c[6] = 1 */
		/* SBX spec, Mask ETN_ALL to SB3 DBUS REQ */
		tmp = readl(tp->mmio_sbxaddr + SBX_SB3_CHANNEL_REQ_MASK);
		tmp |= BIT(6);
		writel(tmp, tp->mmio_sbxaddr + SBX_SB3_CHANNEL_REQ_MASK);

		pr_info("wait all SB3 access finished...");
		tmp = 0;
		while (0 != (BIT(6) & readl(tp->mmio_sbxaddr + SBX_SB3_CHANNEL_REQ_BUSY))) {
			mdelay(10);
			tmp += 10;
			if (tmp >= 100) {
				pr_err("\n wait SB3 access failed (wait %d ms)\n", tmp);
				break;
			}
		}
		if (tmp < 100)
			pr_info("done.\n");

		/* reg_0x9801d100[29] = 0 */
		/* SCPU wrapper spec, CLKACP division, 0 = div 2, 1 = div 3 */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_CRT_CTRL);
		tmp &= ~(BIT(29));
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_CRT_CTRL);

		/* reg_0x9801d124[1:0] = 00 */
		/* SCPU wrapper spec, ACP master active, 0 = active */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_INTERFACE_EN);
		tmp &= ~(BIT(1) | BIT(0));
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_INTERFACE_EN);

		/* reg_0x9801d100[30] = 1 */
		/* SCPU wrapper spec, dy_icg_en_acp */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_CRT_CTRL);
		tmp |= BIT(30);
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_CRT_CTRL);

		/* reg_0x9801d100[21] = 1 */
		/* SCPU wrapper spec, ACP CLK enable */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_CRT_CTRL);
		tmp |= BIT(21);
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_CRT_CTRL);

		/* reg_0x9801d100[14] = 1 */
		/* SCPU wrapper spec, Do not apply reset to ACP port axi3 master */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_CRT_CTRL);
		tmp |= BIT(14);
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_CRT_CTRL);

		/* reg_0x9801d800[3:0] = 0111 */
		/* reg_0x9801d800[7:4] = 0111 */
		/* reg_0x9801d800[9:8] = 00 */
		/* reg_0x9801d800[20:16] = 01100 */
		/* reg_0x9801d800[28:24] = 01110 */
		/* Configure control of ACP port */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_ACP_CTRL);
		tmp &= ~((0x1f << 24) | (0x1f << 16) | (0x1 << 9) |
			(0xf << 4) | (0xf << 0));
		tmp |= (0x0e << 24) | (0x0c << 16) | (0x1 << 9) | (0x7 << 4) |
			(0x7 << 0);
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_ACP_CTRL);

		/* reg_0x9801d030[28] = 1 */
		/* SCPU wrapper spec, dy_icg_en_acp */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_ACP_CRT_CTRL);
		tmp |= BIT(28);
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_ACP_CRT_CTRL);

		/* reg_0x9801d030[16] = 1 */
		/* SCPU wrapper spec, ACP CLK Enable for acp of scpu_chip_top */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_ACP_CRT_CTRL);
		tmp |= BIT(16);
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_ACP_CRT_CTRL);

		/* reg_0x9801d030[0] = 1 */
		/* SCPU wrapper spec, Do not apply reset to ACP port axi3 master */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_ACP_CRT_CTRL);
		tmp |= BIT(0);
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_ACP_CRT_CTRL);

		/* reg_0x9801c814[17] = 1 */
		/* through ACP to SCPU_ACP */
		tmp = readl(tp->mmio_sbxaddr + SBX_ACP_MISC_CTRL);
		tmp |= BIT(17);
		writel(tmp, tp->mmio_sbxaddr + SBX_ACP_MISC_CTRL);

		pr_info("ARM ACP on\n.");
	} else {
		#if 0
		/* reg_0x9801c814[17] = 0 */
		/* through SB3 to DC_SYS (default) */
		tmp = readl(tp->mmio_sbxaddr + SBX_ACP_MISC_CTRL);
		tmp &= ~(BIT(17));
		writel(tmp, tp->mmio_sbxaddr + SBX_ACP_MISC_CTRL);
		#endif
	}
}

static void r8169soc_pll_clock_init(struct rtl8169_private *tp)
{
	u32 tmp;
	struct clk *clk_etn_sys  = clk_get(&tp->pdev->dev, "etn_sys");
	struct clk *clk_etn_250m = clk_get(&tp->pdev->dev, "etn_250m");
	struct reset_control *rstc_gphy =
		reset_control_get(&tp->pdev->dev, "gphy");
	struct reset_control *rstc_gmac =
		reset_control_get(&tp->pdev->dev, "gmac");

	/* reg_0x98007004[27] = 0 */
	/* ISO spec, ETN_PHY_INTR, clear ETN interrupt for ByPassMode */
	writel(BIT(27), tp->mmio_clkaddr + ISO_UMSK_ISR);

	/* reg_0x98007088[10] = 1 */
	/* ISO spec, reset bit of gphy */
	reset_control_deassert(rstc_gphy);

	mdelay(10);	/* wait 10ms for PHY PLL stable */

	/* In Hercules, EPHY need choose the bypass mode or Non-bypass mode */
	/* Bypass mode : ETN MAC bypass efuse update flow. SW need to take this sequence. */
	/* Non-Bypass mode : ETN MAC set efuse update and efuse_rdy setting */
	/* Default : Bypass mode (0x9800_7060[1] = 1'b1) */
	if (!tp->bypass_enable) {
		/* reg_0x98007060[1] = 0 */
		/* ISO spec, bypass mode disable */
		tmp = readl(tp->mmio_clkaddr + ISO_ETN_TESTIO);
		tmp &= ~(BIT(1));
		writel(tmp, tp->mmio_clkaddr + ISO_ETN_TESTIO);
	} else {
		/* reg_0x98007060[1] = 1 */
		/* ISO spec, bypass mode enable */
		/* bypass mode, SW need to handle the EPHY Status check ,
		   EFUSE data update and EPHY fuse_rdy setting. */
		tmp = readl(tp->mmio_clkaddr + ISO_ETN_TESTIO);
		tmp |= BIT(1);
		writel(tmp, tp->mmio_clkaddr + ISO_ETN_TESTIO);
	}

	/* reg_0x98007088[9] = 1 */
	/* ISO spec, reset bit of gmac */
	reset_control_deassert(rstc_gmac);

	/* reg_0x9800708c[12:11] = 11 */
	/* ISO spec, clock enable bit for etn clock & etn 250MHz */
	clk_prepare_enable(clk_etn_sys);
	clk_prepare_enable(clk_etn_250m);

	mdelay(10);	/* wait 10ms for GMAC uC to be stable */

	/* release resource */
	reset_control_put(rstc_gphy);
	reset_control_put(rstc_gmac);
}

/* Hercules only uses 13 bits in OTP 0x9801_72C8[12:8] and 0x9801_72D8[7:0]
   if 0x9801_72C8[12] is 1, then 0x9801_72C8[11:8] (R-calibration) is used to set PHY
   0x9801_72D8[7:0] is used to set idac_fine for PHY
 */
static void r8169soc_load_otp_content(struct rtl8169_private *tp)
{

	u32 otp;
	u16 tmp;

	otp = (readl(tp->mmio_otpaddr) & (0x1f << 8)) >> 8;
	if (0 != ((0x1 << 4) & otp)) {    /* OTP[4] = valid flag, OTP[3:0] = content */
		tmp = otp ^ R_K_DEFAULT;      /* frc_r_value_default = 0x8 */
		r8169_mdio_write(tp, 31, 0xbc0);
		r8169_mdio_write(tp, 20,
			(tmp | (r8169_mdio_read(tp, 20) & ~(0x1f << 0))));
	}

	otp = (readl(tp->mmio_otpaddr + 0x10) & (0xff << 0));
	tmp = otp ^ IDAC_FINE_DEFAULT;      /* IDAC_FINE_DEFAULT = 0x33 */
	r8169_mdio_write(tp, 31, 0xbc0);
	r8169_mdio_write(tp, 23,
			(tmp | (r8169_mdio_read(tp, 23) & ~(0xff << 0))));
}

static u32 r8169soc_serdes_init(struct rtl8169_private *tp)
{
	u32 stable_ticks;
	u32 tmp;
	struct clk *clk_en_sds = clk_get(&tp->pdev->dev, "sds");
	struct reset_control *rstc_sds_reg =
		reset_control_get(&tp->pdev->dev, "sds_reg");
	struct reset_control *rstc_sds =
		reset_control_get(&tp->pdev->dev, "sds");
	struct reset_control *rstc_pcie0_power =
		reset_control_get(&tp->pdev->dev, "pcie0_power");
	struct reset_control *rstc_pcie0_phy =
		reset_control_get(&tp->pdev->dev, "pcie0_phy");
	struct reset_control *rstc_pcie0_sgmii_mdio =
		reset_control_get(&tp->pdev->dev, "pcie0_sgmii_mdio");
	struct reset_control *rstc_pcie0_phy_mdio =
		reset_control_get(&tp->pdev->dev, "pcie0_phy_mdio");

	/* reg_0x98000000[4:3] = 11 */
	/* CRT spec, rstn_sds_reg & rstn_sds */
	reset_control_deassert(rstc_sds);
	reset_control_deassert(rstc_sds_reg);

	/* reg_0x98000004[7] = 1 */
	/* reg_0x98000004[14] = 1 */
	/* CRT spec, rstn_pcie0_power & rstn_pcie0_phy */
	reset_control_deassert(rstc_pcie0_power);
	reset_control_deassert(rstc_pcie0_phy);

	/* reg_0x98000050[13] = 1 */
	/* reg_0x98000050[16] = 1 */
	/* CRT spec, rstn_pcie0_sgmii_mdio & rstn_pcie0_phy_mdio */
	reset_control_deassert(rstc_pcie0_sgmii_mdio);
	reset_control_deassert(rstc_pcie0_phy_mdio);

	/* reg_0x9800000c[7] = 1 */
	/* CRT spec, clk_en_sds */
	clk_prepare_enable(clk_en_sds);

	/* reg_0x9800705c[6] = 1 */
	/* ISO spec, set PCIE channel to SGMII */
	tmp = readl(tp->mmio_clkaddr + ISO_POWERCUT_ETN);
	tmp |= BIT(6);
	writel(tmp, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

	/* reg_0x9800705c[7] = 1 */
	/* ISO spec, set internal MDIO to PCIE */
	tmp = readl(tp->mmio_clkaddr + ISO_POWERCUT_ETN);
	tmp |= BIT(7);
	writel(tmp, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

	/* ### Beginning of SGMII DPHY register tuning ### */
	MDIO_LOCK;

	/* reg_0x9800705c[20:16] = 00000 */
	/* ISO spec, set internal PHY addr to SERDES_DPHY_0 */
	tmp = readl(tp->mmio_clkaddr + ISO_POWERCUT_ETN);
	tmp &= ~(BIT(20) | BIT(19) | BIT(18) | BIT(17) | BIT(16));
	tmp |= (SERDES_DPHY_0 << 16);
	writel(tmp, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

	/* # DPHY spec, DPHY reg13[8:7]=00, choose 1.25GHz */
	r8169_mdio_write(tp, 0x0d,
		(tmp | (r8169_mdio_read(tp, 0x0d) & ~(BIT(8) | BIT(7)))));

	/* # DPHY spec, 5GHz tuning */
	r8169_mdio_write(tp, 0x4, 0x52f5);
	r8169_mdio_write(tp, 0x5, 0xead7);
	r8169_mdio_write(tp, 0x6, 0x0010);
	r8169_mdio_write(tp, 0xa, 0xc653);
	r8169_mdio_write(tp, 0x1, 0xa830);

	/* reg_0x9800705c[20:16] = 00001 */
	/* ISO spec, set internal PHY addr to SERDES_DPHY_1 */
	tmp = readl(tp->mmio_clkaddr + ISO_POWERCUT_ETN);
	tmp &= ~(BIT(20) | BIT(19) | BIT(18) | BIT(17) | BIT(16));
	tmp |= (SERDES_DPHY_1 << 16);
	writel(tmp, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

	/* TX_Swing_1040mV */
	r8169_mdio_write(tp, 0x0, 0xd4aa);
	r8169_mdio_write(tp, 0x1, 0x88aa);

	/* reg_0x9800705c[20:16] = 00001 */
	/* ISO spec, set internal PHY addr to INT_PHY_ADDR */
	tmp = readl(tp->mmio_clkaddr + ISO_POWERCUT_ETN);
	tmp &= ~(BIT(20) | BIT(19) | BIT(18) | BIT(17) | BIT(16));
	tmp |= (INT_PHY_ADDR << 16);
	writel(tmp, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

	tp->ext_phy = true;
	MDIO_UNLOCK;
	mdelay(10);     /* wait for clock stable */
	/* ext_phy == true now */

	#if 0
	mdelay(10);
	#else
	/* reg_0x981c8070[9:0] = 0000000110 */
	/* SDS spec, set SP_CFG_SDS_DBG_SEL to get PHY_Ready */
	tmp = readl(tp->mmio_sdsaddr + SDS_REG28);
	tmp &= ~(0x3ff << 0);
	tmp |= (0x006 << 0);
	writel(tmp, tp->mmio_sdsaddr + SDS_REG28);

	tmp = 0;
	stable_ticks = 0;
	while (10 > stable_ticks) {
		/* # SDS spec, wait for phy ready */
		while (0 == (readl(tp->mmio_sdsaddr + SDS_REG29) & BIT(14))) {
			stable_ticks = 0;
			if (tmp >= 100) {
				stable_ticks = 10;
				pr_err("SGMII PHY not ready in 100ms\n");
				break;
			}
		}
		stable_ticks++;
		tmp++;
		mdelay(1);
	}
	pr_info("SGMII PHY is ready in %d ms", tmp);
	#endif

	/* reg_0x9800705c[4] = 1 */
	/* ISO spec, set data path to SGMII */
	tmp = readl(tp->mmio_clkaddr + ISO_POWERCUT_ETN);
	tmp |= BIT(4);
	writel(tmp, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

	/* reg_0x981c8008[9:8] = 00 */
	/* # SDS spec, SP_SDS_FRC_AN, SERDES auto mode */
	tmp = readl(tp->mmio_sdsaddr + SDS_REG02);
	tmp &= ~(BIT(9) | BIT(8));
	writel(tmp, tp->mmio_sdsaddr + SDS_REG02);

	/* # SDS spec, wait for SERDES link up */
	tmp = 0;
	stable_ticks = 0;
	while (10 > stable_ticks) {
		while ( (BIT(13) | BIT(12)) !=
			(readl(tp->mmio_sdsaddr + SDS_MISC) &
			(BIT(13) | BIT(12)))) {
			stable_ticks = 0;
			if (tmp >= 100) {
				stable_ticks = 10;
				pr_err("SGMII link down in 100ms\n");
				break;
			}
		}
		stable_ticks++;
		tmp++;
		mdelay(1);
	}
	pr_info("SGMII link up in %d ms", tmp);

	reset_control_put(rstc_sds_reg);
	reset_control_put(rstc_sds);
	reset_control_put(rstc_pcie0_power);
	reset_control_put(rstc_pcie0_phy);
	reset_control_put(rstc_pcie0_sgmii_mdio);
	reset_control_put(rstc_pcie0_phy_mdio);
	return 0;
}

static void r8169soc_phy_iol_tuning(struct rtl8169_private *tp)
{
	switch (get_rtd_chip_revision()) {
	case RTD_CHIP_A00: /* TSMC, cut A */
	case RTD_CHIP_A01: /* TSMC, cut B */
		/* idacfine */
		r8169_mdio_write(tp, 31, 0xbc0);
		r8169_mdio_write(tp, 23, 0x0088);

		/* abiq */
		/* r8169_mdio_write(tp, 31, 0xbc0); */
		r8169_mdio_write(tp, 21, 0x0004);

		/* ldvbias */
		/* r8169_mdio_write(tp, 31, 0xbc0); */
		r8169_mdio_write(tp, 22, 0x0777);

		/* iatt */
		r8169_mdio_write(tp, 31, 0xbd0);
		r8169_mdio_write(tp, 16, 0x0300);

		/* vcm_ref, cf_l */
		/* r8169_mdio_write(tp, 31, 0xbd0); */
		r8169_mdio_write(tp, 17, 0xf8ca);
		break;
	case RTD_CHIP_B00: /* UMC, cut C */
		/* 100M Swing */
		/* idac_fine_mdix, idac_fine_mdi */
		r8169_mdio_write(tp, 31, 0xbc0);
		r8169_mdio_write(tp, 23, 0x0044);

		/* 100M Tr/Tf */
		/* abiq_10m=0x0, abiq_100m_short=0x4, abiq_normal=0x6 */
		/* mdio_write(tp, 31, 0xbc0); */
		r8169_mdio_write(tp, 21, 0x0046);

		/* 10M */
		/* ldvbias_10m=0x2, ldvbias_10m_short=0x4, ldvbias_normal=0x4 */
		/* mdio_write(tp, 31, 0xbc0); */
		r8169_mdio_write(tp, 22, 0x0244);

		/* vcmref=0x0, cf_l=0x3 */
		r8169_mdio_write(tp, 31, 0xbd0);
		r8169_mdio_write(tp, 17, 0x18ca);

		/* iatt=0x1 */
		/* mdio_write(tp, 31, 0xbd0); */
		r8169_mdio_write(tp, 16, 0x0100);
		break;

	/* default: */
	}
}

static void r8169soc_mdio_init(struct rtl8169_private *tp)
{
	u32 tmp;
	struct pinctrl *p_sgmii_mdio;
	struct pinctrl_state * ps_sgmii_mdio;
	void __iomem *ioaddr = tp->mmio_addr;

	/* ISO spec, ETN_PHY_INTR, wait interrupt from PHY and it means MDIO is ready */
	tmp = 0;
	while ((readl(tp->mmio_clkaddr + ISO_UMSK_ISR) & BIT(27)) == 0) {
		tmp += 10;
		mdelay(10);
		if (tmp >= 100) {
			pr_err("PHY PHY_Status timeout.\n");
			break;
		}
	}
	pr_info("wait %d ms for PHY interrupt. UMSK_ISR = 0x%x\n",
		tmp, readl(tp->mmio_clkaddr + ISO_UMSK_ISR));

	MDIO_LOCK;
	/* In Hercules ByPass mode,
	   SW need to handle the EPHY Status check ,
	   OTP data update and EPHY fuse_rdy setting. */
	if (tp->bypass_enable) {
		/* PHY will stay in state 1 mode */
		r8169_mdio_write(tp, 31, 0x0a42);
		tmp = 0;
		while (0x1 != (r8169_mdio_read(tp, 16) & 0x07)) {
			tmp += 10;
			mdelay(10);
			if (tmp >= 2000) {
				pr_err("PHY status is not 0x1 in bypass mode, current = 0x%02x\n",
					(r8169_mdio_read(tp, 16) & 0x07));
				break;
			}
		}

		/* adjust FE PHY electrical characteristics */
		r8169soc_phy_iol_tuning(tp);

		/* 1. read OTP 0x9801_72C8[12:8]
		   2. xor 0x08
		   3. set value to PHY registers to correct R-calibration
		   4. read OTP 0x9801_72D8[7:0]
		   5. xor 0x33
		   6. set value to PHY registers to correct AMP
		 */
		r8169soc_load_otp_content(tp);

		/* fill fuse_rdy & rg_ext_ini_done */
		r8169_mdio_write(tp, 31, 0x0a46);
		r8169_mdio_write(tp, 20,
			(r8169_mdio_read(tp, 20) | (BIT(1) | BIT(0))));
	} else {
		/* adjust FE PHY electrical characteristics */
		r8169soc_phy_iol_tuning(tp);
	}

	/* init_autoload_done = 1 */
	tmp = r8169soc_ocp_reg_read(tp, 0xe004);
	tmp |= BIT(7);
	r8169soc_ocp_reg_write(tp, 0xe004, tmp);
	/* ee_mode = 3 */
	RTL_W8(Cfg9346, Cfg9346_Unlock);

	/* wait LAN-ON */
	r8169_mdio_write(tp, 31, 0x0a42);
	tmp = 0;
	do {
		tmp += 10;
		mdelay(10);
		if (tmp >= 2000) {
			pr_err("PHY status is not 0x3, current = 0x%02x\n",
				(r8169_mdio_read(tp, 16) & 0x07));
			break;
		}
	} while (0x3 != (r8169_mdio_read(tp, 16) & 0x07));
	MDIO_UNLOCK;
	pr_info("wait %d ms for PHY ready, current = 0x%x\n",
		tmp, r8169_mdio_read(tp, 16));

	if (tp->output_mode == OUTPUT_EMBEDDED_PHY) {
		/* Init PHY path */
		/* reg_0x9800705c[5] = 0 */
		/* reg_0x9800705c[7] = 0 */
		/* ISO spec, set internal MDIO to access PHY */
		tmp = readl(tp->mmio_clkaddr + ISO_POWERCUT_ETN);
		tmp &= ~(BIT(7) | BIT(5));
		writel(tmp, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

		/* reg_0x9800705c[4] = 0 */
		/* ISO spec, set data path to access PHY */
		tmp = readl(tp->mmio_clkaddr + ISO_POWERCUT_ETN);
		tmp &= ~(BIT(4));
		writel(tmp, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

		/* # ETN spec, GMAC data path select MII-like(embedded GPHY), not SGMII(external PHY) */
		tmp = r8169soc_ocp_reg_read(tp, 0xea34) & ~(BIT(0) | BIT(1));
		tmp |= BIT(1); /* MII */
		r8169soc_ocp_reg_write(tp, 0xea34, tmp);
	} else {
		/* SGMII */
		/* # ETN spec, adjust MDC freq=2.5MHz */
		r8169soc_ocp_reg_write(tp, 0xDE30,
			r8169soc_ocp_reg_read(tp, 0xDE30) & ~(BIT(7) | BIT(6)));
		/* # ETN spec, set external PHY addr */
		r8169soc_ocp_reg_write(tp, 0xDE24,
			((r8169soc_ocp_reg_read(tp, 0xDE24) & ~(0x1f << 0)) |
						(tp->ext_phy_id & 0x1f)));
		/* ISO mux spec, GPIO29 is set to MDC pin */
		/* ISO mux spec, GPIO46 is set to MDIO pin */
		p_sgmii_mdio = devm_pinctrl_get(&tp->pdev->dev);
		ps_sgmii_mdio = pinctrl_lookup_state(p_sgmii_mdio, "sgmii");
		pinctrl_select_state(p_sgmii_mdio, ps_sgmii_mdio);

		/* check if external PHY is available */
		pr_info("Searching external PHY...");
		MDIO_LOCK;
		tp->ext_phy = true;
		r8169_mdio_write(tp, 31, 0x0a43);
		tmp = 0;
		while (0xa43 != r8169_mdio_read(tp, 31)) {
			pr_info(".");
			tmp += 100;
			mdelay(100);
			if (tmp >= 2000) {
				pr_err("\n External SGMII PHY not found, current = 0x%02x\n",
					r8169_mdio_read(tp, 31));
				break;
			}
		}
		if (tmp < 2000)
			pr_info("found.\n");

		/* lower SGMII TX swing of RTL8211FS to reduce EMI */
		r8169_mdio_write(tp, 31, 0x0dcd);
		r8169_mdio_write(tp, 16, 0x104e);	/* TX swing = 470mV, default value */

		tp->ext_phy = false;
		MDIO_UNLOCK;

		/* # ETN spec, GMAC data path select SGMII(external PHY), not MII-like(embedded GPHY) */
		tmp = r8169soc_ocp_reg_read(tp, 0xea34) & ~(BIT(0) | BIT(1));
		tmp |= BIT(1) | BIT(0); /* SGMII */
		r8169soc_ocp_reg_write(tp, 0xea34, tmp);

		if (0 != r8169soc_serdes_init(tp))
			pr_err("SERDES init failed\n");
		/* ext_phy == true now */

		/* SDS spec, auto update SGMII link capability */
		tmp = readl(tp->mmio_sdsaddr + SDS_LINK);
		tmp |= BIT(2);
		writel(tmp, tp->mmio_sdsaddr + SDS_LINK);
	}
}

static void r8169soc_eee_init(struct rtl8169_private *tp, bool enable)
{
	if (enable) {
		MDIO_LOCK;
		if (tp->output_mode == OUTPUT_EMBEDDED_PHY) {
			/* 100M EEE capability */
			r8169_mmd_write(tp, 0x7, 60, BIT(1));
			/* 10M EEE */
			r8169_mdio_write(tp, 31, 0xa43);
			r8169_mdio_write(tp, 25, r8169_mdio_read(tp, 25) | (BIT(4) | BIT(2)));
			/* disable dynamic RX power in PHY */
			r8169_mdio_write(tp, 31, 0xbd0);
			r8169_mdio_write(tp, 21, (r8169_mdio_read(tp, 21) & ~BIT(8)) | BIT(9));
		} else { /* SGMII */
			/* 1000M & 100M EEE capability */
			r8169_mmd_write(tp, 0x7, 60, (BIT(2) | BIT(1)));
			/* 10M EEE */
			r8169_mdio_write(tp, 31, 0xa43);
			r8169_mdio_write(tp, 25, r8169_mdio_read(tp, 25) | (BIT(4) | BIT(2)));
		}
		MDIO_UNLOCK;
		/* EEE MAC mode */
		r8169soc_ocp_reg_write(tp, 0xe040, (r8169soc_ocp_reg_read(tp, 0xe040) | (BIT(1) | BIT(0))));
		/* EEE+ MAC mode */
		r8169soc_ocp_reg_write(tp, 0xe080, (r8169soc_ocp_reg_read(tp, 0xe080) | BIT(1)));
	} else {
		if (tp->output_mode == OUTPUT_EMBEDDED_PHY) {
			/* no EEE capability */
			r8169_mmd_write(tp, 0x7, 60, 0);
			/* 10M EEE */
			r8169_mdio_write(tp, 31, 0xa43);
			r8169_mdio_write(tp, 25, r8169_mdio_read(tp, 25) & ~(BIT(4) | BIT(2)));
		} else { /* SGMII */
			/* no EEE capability */
			r8169_mmd_write(tp, 0x7, 60, 0);
			/* 10M EEE */
			r8169_mdio_write(tp, 31, 0xa43);
			r8169_mdio_write(tp, 25, r8169_mdio_read(tp, 25) & ~(BIT(4) | BIT(2)));
		}
		MDIO_UNLOCK;
		/* reset to default value */
		r8169soc_ocp_reg_write(tp, 0xe040, (r8169soc_ocp_reg_read(tp, 0xe040) | BIT(13)));
		/* EEE MAC mode */
		r8169soc_ocp_reg_write(tp, 0xe040, (r8169soc_ocp_reg_read(tp, 0xe040) & ~(BIT(1) | BIT(0))));
		/* EEE+ MAC mode */
		r8169soc_ocp_reg_write(tp, 0xe080, (r8169soc_ocp_reg_read(tp, 0xe080) & ~BIT(1)));
	}
}
#endif /* CONFIG_ARCH_RTD139x */

#if defined(CONFIG_ARCH_RTD16xx)
static void r8169soc_reset_phy_gmac(struct rtl8169_private *tp)
{
	u32 tmp;
	struct clk *clk_etn_sys  = clk_get(&tp->pdev->dev, "etn_sys");
	struct clk *clk_etn_250m = clk_get(&tp->pdev->dev, "etn_250m");
	struct reset_control *rstc_gphy =
		reset_control_get(&tp->pdev->dev, "gphy");
	struct reset_control *rstc_gmac =
		reset_control_get(&tp->pdev->dev, "gmac");
	struct clk *clk_en_sds;
	struct reset_control *rstc_sds_reg;
	struct reset_control *rstc_sds;
	struct reset_control *rstc_pcie0_power;
	struct reset_control *rstc_pcie0_phy;
	struct reset_control *rstc_pcie0_sgmii_mdio;
	struct reset_control *rstc_pcie0_phy_mdio;

	clk_prepare_enable(clk_etn_sys);
	clk_prepare_enable(clk_etn_250m);
	clk_en_sds = clk_get(&tp->pdev->dev, "sds");
	rstc_sds_reg = reset_control_get(&tp->pdev->dev, "sds_reg");
	rstc_sds = reset_control_get(&tp->pdev->dev, "sds");
	rstc_pcie0_power = reset_control_get(&tp->pdev->dev, "pcie0_power");
	rstc_pcie0_phy = reset_control_get(&tp->pdev->dev, "pcie0_phy");
	rstc_pcie0_sgmii_mdio = reset_control_get(&tp->pdev->dev, "pcie0_sgmii_mdio");
	rstc_pcie0_phy_mdio = reset_control_get(&tp->pdev->dev, "pcie0_phy_mdio");


	/* reg_0x9800708c[12:11] = 00 */
	/* ISO spec, clock enable bit for etn clock & etn 250MHz */
	clk_disable_unprepare(clk_etn_sys);
	clk_disable_unprepare(clk_etn_250m);

	/* reg_0x98007088[10:9] = 00 */
	/* ISO spec, rstn_gphy & rstn_gmac */
	reset_control_assert(rstc_gphy);
	reset_control_assert(rstc_gmac);

	/* reg_0x98007060[1] = 1 */
	/* ISO spec, bypass mode enable */
	tmp = readl(tp->mmio_clkaddr + ISO_ETN_TESTIO);
	tmp |= BIT(1);
	writel(tmp, tp->mmio_clkaddr + ISO_ETN_TESTIO);

	/* reg_0x9800705c = 0x00616703 */
	/* ISO spec, default value */
	writel(0x00616703, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

	/* RESET for SGMII if needed */
	clk_prepare_enable(clk_en_sds);

	/* reg_0x98000050[13:12] = 10 */
	/* CRT spec, clk_en_sds */
	clk_disable_unprepare(clk_en_sds);

	/* reg_0x98000000[7:6] = 10 */
	/* reg_0x98000000[9:8] = 10 */
	/* CRT spec, rstn_sds_reg & rstn_sds */
	reset_control_assert(rstc_sds);
	reset_control_assert(rstc_sds_reg);

	/* reg_0x98000004[25:24] = 10 	CRT spec, rstn_pcie0_sgmii_mdio */
	/* reg_0x98000004[23:22] = 10 	CRT spec, rstn_pcie0_phy_mdio */
	/* reg_0x98000004[19:18] = 10 	CRT spec, rstn_pcie0_power */
	/* reg_0x98000004[13:12] = 10 	CRT spec, rstn_pcie0_phy */
	reset_control_assert(rstc_pcie0_sgmii_mdio);
	reset_control_assert(rstc_pcie0_phy_mdio);
	reset_control_assert(rstc_pcie0_power);
	reset_control_assert(rstc_pcie0_phy);


	mdelay(100);

	/* release resource */
	reset_control_put(rstc_sds_reg);
	reset_control_put(rstc_sds);
	reset_control_put(rstc_pcie0_power);
	reset_control_put(rstc_pcie0_phy);
	reset_control_put(rstc_pcie0_sgmii_mdio);
	reset_control_put(rstc_pcie0_phy_mdio);
	reset_control_put(rstc_gphy);
	reset_control_put(rstc_gmac);
}

static void r8169soc_acp_init(struct rtl8169_private *tp)
{
	u32 tmp;

	/* SBX spec, Select ETN access DDR path. */
	if (tp->acp_enable) {
		/* reg_0x9801c20c[6] = 1 */
		/* SBX spec, Mask ETN_ALL to SB3 DBUS REQ */
		tmp = readl(tp->mmio_sbxaddr + SBX_SB3_CHANNEL_REQ_MASK);
		tmp |= BIT(6);
		writel(tmp, tp->mmio_sbxaddr + SBX_SB3_CHANNEL_REQ_MASK);

		pr_info("wait all SB3 access finished...");
		tmp = 0;
		while (0 != (BIT(6) & readl(tp->mmio_sbxaddr + SBX_SB3_CHANNEL_REQ_BUSY))) {
			mdelay(10);
			tmp += 10;
			if (tmp >= 100) {
				pr_err("\n wait SB3 access failed (wait %d ms)\n", tmp);
				break;
			}
		}
		if (tmp < 100)
			pr_info("done.\n");

		/* reg_0x9801d100[29] = 0 */
		/* SCPU wrapper spec, CLKACP division, 0 = div 2, 1 = div 3 */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_CRT_CTRL);
		tmp &= ~(BIT(29));
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_CRT_CTRL);

		/* reg_0x9801d124[1:0] = 00 */
		/* SCPU wrapper spec, ACP master active, 0 = active */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_INTERFACE_EN);
		tmp &= ~(BIT(1) | BIT(0));
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_INTERFACE_EN);

		/* reg_0x9801d100[30] = 1 */
		/* SCPU wrapper spec, dy_icg_en_acp */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_CRT_CTRL);
		tmp |= BIT(30);
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_CRT_CTRL);

		/* reg_0x9801d100[21] = 1 */
		/* SCPU wrapper spec, ACP CLK enable */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_CRT_CTRL);
		tmp |= BIT(21);
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_CRT_CTRL);

		/* reg_0x9801d100[14] = 1 */
		/* SCPU wrapper spec, Do not apply reset to ACP port axi3 master */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_CRT_CTRL);
		tmp |= BIT(14);
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_CRT_CTRL);

		/* reg_0x9801d800[3:0] = 0111 */
		/* reg_0x9801d800[7:4] = 0111 */
		/* reg_0x9801d800[9:8] = 00 */
		/* reg_0x9801d800[20:16] = 01100 */
		/* reg_0x9801d800[28:24] = 01110 */
		/* Configure control of ACP port */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_ACP_CTRL);
		tmp &= ~((0x1f << 24) | (0x1f << 16) | (0x1 << 9) |
			(0xf << 4) | (0xf << 0));
		tmp |= (0x0e << 24) | (0x0c << 16) | (0x1 << 9) | (0x7 << 4) |
			(0x7 << 0);
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_ACP_CTRL);

		/* reg_0x9801d030[28] = 1 */
		/* SCPU wrapper spec, dy_icg_en_acp */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_ACP_CRT_CTRL);
		tmp |= BIT(28);
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_ACP_CRT_CTRL);

		/* reg_0x9801d030[16] = 1 */
		/* SCPU wrapper spec, ACP CLK Enable for acp of scpu_chip_top */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_ACP_CRT_CTRL);
		tmp |= BIT(16);
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_ACP_CRT_CTRL);

		/* reg_0x9801d030[0] = 1 */
		/* SCPU wrapper spec, Do not apply reset to ACP port axi3 master */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_ACP_CRT_CTRL);
		tmp |= BIT(0);
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_ACP_CRT_CTRL);

		/* reg_0x9801c814[17] = 1 */
		/* through ACP to SCPU_ACP */
		tmp = readl(tp->mmio_sbxaddr + SBX_ACP_MISC_CTRL);
		tmp |= BIT(17);
		writel(tmp, tp->mmio_sbxaddr + SBX_ACP_MISC_CTRL);

		/* SBX spec, Remove mask ETN_ALL to ACP DBUS REQ */
		tmp = readl(tp->mmio_sbxaddr + SBX_ACP_CHANNEL_REQ_MASK);
		tmp &= ~BIT(1);
		writel(tmp, tp->mmio_sbxaddr + SBX_ACP_CHANNEL_REQ_MASK);


		pr_info("ARM ACP on\n.");
	} else {
		/* SBX spec, Mask ETN_ALL to ACP DBUS REQ */
		tmp = readl(tp->mmio_sbxaddr + SBX_ACP_CHANNEL_REQ_MASK);
		tmp |= BIT(1);
		writel(tmp, tp->mmio_sbxaddr + SBX_ACP_CHANNEL_REQ_MASK);

		pr_info("wait all ACP access finished...");
		tmp = 0;
		while (0 != (BIT(1) & readl(tp->mmio_sbxaddr + SBX_ACP_CHANNEL_REQ_BUSY))) {
			mdelay(10);
			tmp += 10;
			if (tmp >= 100) {
				pr_err("\n ACP channel is still busy (wait %d ms)\n", tmp);
				break;
			}
		}
		if (tmp < 100)
			pr_info("done.\n");

		/* SCPU wrapper spec, Inactive MP4 AINACTS signal */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_INTERFACE_EN);
		tmp |= (BIT(1) | BIT(0));
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_INTERFACE_EN);

		/* SCPU wrapper spec, nACPRESET_DVFS & CLKENACP_DVFS */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_CRT_CTRL);
		tmp &= ~(BIT(21) | BIT(14));
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_CRT_CTRL);

		/* SCPU wrapper spec, nACPRESET & CLKENACP */
		tmp = readl(tp->mmio_sbxaddr + SC_WRAP_ACP_CRT_CTRL);
		tmp &= ~(BIT(16) | BIT(0));
		writel(tmp, tp->mmio_sbxaddr + SC_WRAP_ACP_CRT_CTRL);

		/* reg_0x9801c814[17] = 0 */
		/* SBX spec, Switch ETN_ALL to DC_SYS path */
		tmp = readl(tp->mmio_sbxaddr + SBX_ACP_MISC_CTRL);
		tmp &= ~BIT(17);
		writel(tmp, tp->mmio_sbxaddr + SBX_ACP_MISC_CTRL);

		/* SBX spec, Remove mask ETN_ALL to SB3 DBUS REQ */
		tmp = readl(tp->mmio_sbxaddr + SBX_SB3_CHANNEL_REQ_MASK);
		tmp &= ~BIT(6);
		writel(tmp, tp->mmio_sbxaddr + SBX_SB3_CHANNEL_REQ_MASK);

		pr_info("ARM ACP off\n.");
	}
}

static void r8169soc_pll_clock_init(struct rtl8169_private *tp)
{
	u32 tmp;
	struct clk *clk_etn_sys  = clk_get(&tp->pdev->dev, "etn_sys");
	struct clk *clk_etn_250m = clk_get(&tp->pdev->dev, "etn_250m");
	struct reset_control *rstc_gphy =
		reset_control_get(&tp->pdev->dev, "gphy");
	struct reset_control *rstc_gmac =
		reset_control_get(&tp->pdev->dev, "gmac");

	/* reg_0x98007004[27] = 0 */
	/* ISO spec, ETN_PHY_INTR, clear ETN interrupt for ByPassMode */
	writel(BIT(27), tp->mmio_clkaddr + ISO_UMSK_ISR);

	/* reg_0x98007088[10] = 1 */
	/* ISO spec, reset bit of gphy */
	reset_control_deassert(rstc_gphy);

	mdelay(10);	/* wait 10ms for PHY PLL stable */

	/* Thor only supports the bypass mode */
	/* Bypass mode : ETN MAC bypass efuse update flow. SW need to take this sequence. */
	/* reg_0x98007060[1] = 1 */
	/* ISO spec, bypass mode enable */
	/* bypass mode, SW need to handle the EPHY Status check ,
	   EFUSE data update and EPHY fuse_rdy setting. */
	tmp = readl(tp->mmio_clkaddr + ISO_ETN_TESTIO);
	tmp |= BIT(1);
	writel(tmp, tp->mmio_clkaddr + ISO_ETN_TESTIO);

	/* reg_0x98007088[9] = 1 */
	/* ISO spec, reset bit of gmac */
	reset_control_deassert(rstc_gmac);

	/* reg_0x9800708c[12:11] = 11 */
	/* ISO spec, clock enable bit for etn clock & etn 250MHz */
	clk_prepare_enable(clk_etn_sys);
	clk_prepare_enable(clk_etn_250m);

	mdelay(10);	/* wait 10ms for GMAC uC to be stable */

	/* release resource */
	reset_control_put(rstc_gphy);
	reset_control_put(rstc_gmac);
}

static void r8169soc_load_otp_content(struct rtl8169_private *tp)
{
	u32 otp;
	u16 tmp;

	/* RC-K 0x980174F8[27:24] */
	otp = (readl(tp->mmio_otpaddr) & (0xf << 24)) >> 24;
	tmp = (otp << 12) | (otp << 8) | (otp << 4) | otp;
	tmp ^= RC_K_DEFAULT;
	r8169_mdio_write(tp, 31, 0xbcd);
	r8169_mdio_write(tp, 22, tmp);
	r8169_mdio_write(tp, 23, tmp);

	/* R-K 0x98017500[18:15] */
	otp = (readl(tp->mmio_otpaddr + 0x8) & (0xf << 15)) >> 15;
	tmp = (otp << 12) | (otp << 8) | (otp << 4) | otp;
	tmp ^= R_K_DEFAULT;
	r8169_mdio_write(tp, 31, 0xbce);
	r8169_mdio_write(tp, 16, tmp);
	r8169_mdio_write(tp, 17, tmp);

	/* Amp-K 0x980174FC[15:0] */
	otp = (readl(tp->mmio_otpaddr + 0x4) & (0xffff << 0)) >> 0;
	tmp = otp ^ AMP_K_DEFAULT;
	r8169_mdio_write(tp, 31, 0xbca);
	r8169_mdio_write(tp, 22, tmp);

	/* Bias-K 0x980174FC[31:16] */
	otp = (readl(tp->mmio_otpaddr + 0x4) & (0xffff << 16)) >> 16;
	tmp = otp ^ ADC_BIAS_K_DEFAULT;
	r8169_mdio_write(tp, 31, 0xbcf);
	r8169_mdio_write(tp, 22, tmp);
}

static u32 r8169soc_serdes_init(struct rtl8169_private *tp)
{
	u32 stable_ticks;
	u32 tmp;
	struct clk *clk_en_sds = clk_get(&tp->pdev->dev, "sds");
	struct reset_control *rstc_sds_reg =
		reset_control_get(&tp->pdev->dev, "sds_reg");
	struct reset_control *rstc_sds =
		reset_control_get(&tp->pdev->dev, "sds");
	struct reset_control *rstc_pcie0_power =
		reset_control_get(&tp->pdev->dev, "pcie0_power");
	struct reset_control *rstc_pcie0_phy =
		reset_control_get(&tp->pdev->dev, "pcie0_phy");
	struct reset_control *rstc_pcie0_sgmii_mdio =
		reset_control_get(&tp->pdev->dev, "pcie0_sgmii_mdio");
	struct reset_control *rstc_pcie0_phy_mdio =
		reset_control_get(&tp->pdev->dev, "pcie0_phy_mdio");

	/* reg_0x98000050[13:12] = 11 */
	/* CRT spec, clk_en_sds */
	clk_prepare_enable(clk_en_sds);

	/* reg_0x98000000[9:8] = 11 */
	/* reg_0x98000000[7:6] = 11 */
	/* CRT spec, rstn_sds_reg & rstn_sds */
	reset_control_deassert(rstc_sds);
	reset_control_deassert(rstc_sds_reg);

	/* reg_0x98000004[25:24] = 11 	CRT spec, rstn_pcie0_sgmii_mdio */
	/* reg_0x98000004[23:22] = 11 	CRT spec, rstn_pcie0_phy_mdio */
	/* reg_0x98000004[19:18] = 11 	CRT spec, rstn_pcie0_power */
	/* reg_0x98000004[13:12] = 11 	CRT spec, rstn_pcie0_phy */
	reset_control_deassert(rstc_pcie0_power);
	reset_control_deassert(rstc_pcie0_phy);
	reset_control_deassert(rstc_pcie0_sgmii_mdio);
	reset_control_deassert(rstc_pcie0_phy_mdio);

	/* reg_0x9800705c[6] = 1 */
	/* ISO spec, set PCIe channel to SGMII */
	tmp = readl(tp->mmio_clkaddr + ISO_POWERCUT_ETN);
	tmp |= BIT(6);
	writel(tmp, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

	/* ### Beginning of SGMII DPHY register tuning ### */
	MDIO_LOCK;

	/* reg_0x9800705c[7] = 1 */
	/* ISO spec, set internal MDIO to PCIe */
	tmp = readl(tp->mmio_clkaddr + ISO_POWERCUT_ETN);
	tmp |= BIT(7);
	writel(tmp, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

	/* reg_0x9800705c[20:16] = 00000 */
	/* ISO spec, set internal PHY addr to SERDES_DPHY_0 */
	tmp = readl(tp->mmio_clkaddr + ISO_POWERCUT_ETN);
	tmp &= ~(BIT(20) | BIT(19) | BIT(18) | BIT(17) | BIT(16));
	tmp |= (SERDES_DPHY_0 << 16);
	writel(tmp, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

	/* # DPHY spec, 5GHz tuning */
	r8169_mdio_write(tp, 0x4, 0x52f5);
	r8169_mdio_write(tp, 0x5, 0xead7);
	r8169_mdio_write(tp, 0x6, 0x0010);
	r8169_mdio_write(tp, 0xa, 0xc653);
	r8169_mdio_write(tp, 0x1, 0xe030);
	r8169_mdio_write(tp, 0xd, 0xee1c);

	/* reg_0x9800705c[20:16] = 00001 */
	/* ISO spec, set internal PHY addr to SERDES_DPHY_1 */
	tmp = readl(tp->mmio_clkaddr + ISO_POWERCUT_ETN);
	tmp &= ~(BIT(20) | BIT(19) | BIT(18) | BIT(17) | BIT(16));
	tmp |= (SERDES_DPHY_1 << 16);
	writel(tmp, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

	/* TX_Swing_550mV by default */
	switch (tp->sgmii_swing) {
	case TX_Swing_190mV:
		r8169_mdio_write(tp, 0x0, 0xd411);
		r8169_mdio_write(tp, 0x1, 0x2277);
		break;
	case TX_Swing_250mV:
		r8169_mdio_write(tp, 0x0, 0xd433);
		r8169_mdio_write(tp, 0x1, 0x2244);
		break;
	case TX_Swing_380mV:
		r8169_mdio_write(tp, 0x0, 0xd433);
		r8169_mdio_write(tp, 0x1, 0x22aa);
		break;
	case TX_Swing_550mV: /* recommended by RDC */
	default :
		r8169_mdio_write(tp, 0x0, 0xd455);
		r8169_mdio_write(tp, 0x1, 0x2828);
	}

	/* reg_0x9800705c[20:16] = 00001 */
	/* ISO spec, set internal PHY addr to INT_PHY_ADDR */
	tmp = readl(tp->mmio_clkaddr + ISO_POWERCUT_ETN);
	tmp &= ~(BIT(20) | BIT(19) | BIT(18) | BIT(17) | BIT(16));
	tmp |= (INT_PHY_ADDR << 16);
	writel(tmp, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

	mdelay(10);     /* wait for clock stable */

	/* reg_0x9800705c[5] = 0 */
	/* reg_0x9800705c[7] = 0 */
	/* ISO spec, set internal MDIO to GPHY */
	tmp = readl(tp->mmio_clkaddr + ISO_POWERCUT_ETN);
	tmp &= ~(BIT(7) | BIT(5));
	writel(tmp, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

	MDIO_UNLOCK;
	tp->ext_phy = true;
	/* ext_phy == true now */

	tmp = 0;
	stable_ticks = 0;
	while (10 > stable_ticks) {
		/* # SDS spec, wait for phy ready */
		while (0 == (readl(tp->mmio_sdsaddr + SDS_LINK) & BIT(24))) {
			stable_ticks = 0;
			if (tmp >= 100) {
				stable_ticks = 10;
				pr_err("SGMII PHY not ready in 100ms\n");
				break;
			}
		}
		stable_ticks++;
		tmp++;
		mdelay(1);
	}
	pr_info("SGMII PHY is ready in %d ms", tmp);

	/* reg_0x9800705c[4] = 1 */
	/* ISO spec, set data path to SGMII */
	tmp = readl(tp->mmio_clkaddr + ISO_POWERCUT_ETN);
	tmp |= BIT(4);
	writel(tmp, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

	/* reg_0x981c8008[9:8] = 00 */
	/* # SDS spec, SP_SDS_FRC_AN, SERDES auto mode */
	tmp = readl(tp->mmio_sdsaddr + SDS_REG02);
	tmp &= ~(BIT(9) | BIT(8));
	writel(tmp, tp->mmio_sdsaddr + SDS_REG02);

	/* # SDS spec, wait for SERDES link up */
	tmp = 0;
	stable_ticks = 0;
	while (10 > stable_ticks) {
		while ( 0 == (readl(tp->mmio_sdsaddr + SDS_MISC) & BIT(12))) {
			stable_ticks = 0;
			if (tmp >= 100) {
				stable_ticks = 10;
				pr_err("SGMII link down in 100ms\n");
				break;
			}
		}
		stable_ticks++;
		tmp++;
		mdelay(1);
	}
	pr_info("SGMII link up in %d ms", tmp);

	reset_control_put(rstc_sds_reg);
	reset_control_put(rstc_sds);
	reset_control_put(rstc_pcie0_power);
	reset_control_put(rstc_pcie0_phy);
	reset_control_put(rstc_pcie0_sgmii_mdio);
	reset_control_put(rstc_pcie0_phy_mdio);
	return 0;
}

static void r8169soc_phy_iol_tuning(struct rtl8169_private *tp)
{
	/* for common mode voltage */
	r8169_mdio_write(tp, 31, 0xbc0);
	r8169_mdio_write(tp, 17,
		((r8169_mdio_read(tp, 17) & ~(0xff << 4)) | (0xb4 << 4)));

	/* for 1000 Base-T, Transmitter Distortion */
	r8169_mdio_write(tp, 31, 0xa43);
	r8169_mdio_write(tp, 27, 0x8082);
	r8169_mdio_write(tp, 28, 0xae00);
}

static void r8169soc_phy_sram_table(struct rtl8169_private *tp)
{
	/* enable echo power*2 */
	r8169_mdio_write(tp, 31, 0xa42);
	r8169_mdio_write(tp, 22, 0x0f10);

	/* Channel estimation, 100Mbps adjustment */
	r8169_mdio_write(tp, 31, 0xa43);
	r8169_mdio_write(tp, 27, 0x8087);	/* gain_i slope */
	r8169_mdio_write(tp, 28, 0x42f0);	/* 0x43 => 0x42 */
	r8169_mdio_write(tp, 27, 0x808e);	/* clen_i_c initial value */
	r8169_mdio_write(tp, 28, 0x14a4);	/* 0x13 => 0x14 */
	/* adc peak adjustment */
	r8169_mdio_write(tp, 27, 0x8088);	/* aagc_lvl_c initial value 0x3f0 => ok */
	r8169_mdio_write(tp, 28, 0xf0eb);	/* delta_a slope 0x1e => 0x1d */
	/* cb0 adjustment */
	r8169_mdio_write(tp, 27, 0x808c);	/* cb0_i_c initial value */
	r8169_mdio_write(tp, 28, 0xef09);	/* 0x9ef => ok */
	r8169_mdio_write(tp, 27, 0x808f);	/* delta_b slope */
	r8169_mdio_write(tp, 28, 0xa4c6);	/* 0xa4 => ok */
	/* DAGC adjustment */
	r8169_mdio_write(tp, 27, 0x808a);	/* cg_i_c initial value */
	r8169_mdio_write(tp, 28, 0x400a);	/* 0xb40 => 0xa40 */
	r8169_mdio_write(tp, 27, 0x8092);	/* delta_g slope */
	r8169_mdio_write(tp, 28, 0xc21e);	/* 0x0c0 => 0x0c2 */

	/* 1000Mbps master adjustment */
	/* line adjustment */
	r8169_mdio_write(tp, 27, 0x8099);	/* gain_i slope */
	r8169_mdio_write(tp, 28, 0x2ae0);	/* 0x2e => 0x2a */
	r8169_mdio_write(tp, 27, 0x80a0);	/* clen_i_c initial value */
	r8169_mdio_write(tp, 28, 0xf28f);	/* 0xfe => 0xf2 */
	/* adc peak adjustment */
	r8169_mdio_write(tp, 27, 0x809a);	/* aagc_lvl_c initial value 0x3e0 => 0x470 */
	r8169_mdio_write(tp, 28, 0x7084);	/* delta_a slope 0x0d => 0x10 */
	/* cb0 adjustment */
	r8169_mdio_write(tp, 27, 0x809e);	/* cb0_i_c initial value */
	r8169_mdio_write(tp, 28, 0xa008);	/* 0x7a1 => 0x8a0 */
	r8169_mdio_write(tp, 27, 0x80a1);	/* delta_b slope */
	r8169_mdio_write(tp, 28, 0x783d);	/* 0x8f => 0x78 */
	/* DAGC adjustment */
	r8169_mdio_write(tp, 27, 0x809c);	/* cg_i_c initial value */
	r8169_mdio_write(tp, 28, 0x8008);	/* 0xb00 => 0x880 */
	r8169_mdio_write(tp, 27, 0x80a4);	/* delta_g slope */
	r8169_mdio_write(tp, 28, 0x580c);	/* 0x063 => 0x058 */

	/* 1000Mbps slave adjustment */
	/* line adjustment */
	r8169_mdio_write(tp, 27, 0x80ab);	/* gain_i slope */
	r8169_mdio_write(tp, 28, 0x2b4a);	/* 0x2e => 0x2b */
	r8169_mdio_write(tp, 27, 0x80b2);	/* clen_i_c initial value */
	r8169_mdio_write(tp, 28, 0xf47f);	/* 0xfa => 0xf4 */
	/* adc peak adjustment */
	r8169_mdio_write(tp, 27, 0x80ac);	/* aagc_lvl_c initial value 0x44a => 0x488 */
	r8169_mdio_write(tp, 28, 0x8884);	/* delta_a slope 0x0e => 0x10 */
	/* cb0 adjustment */
	r8169_mdio_write(tp, 27, 0x80b0);	/* cb0_i_c initial value */
	r8169_mdio_write(tp, 28, 0xa107);	/* 0x6a1 => 0x7a1 */
	r8169_mdio_write(tp, 27, 0x80b3);	/* delta_b slope */
	r8169_mdio_write(tp, 28, 0x683d);	/* 0x7f => 0x68 */
	/* DAGC adjustment */
	r8169_mdio_write(tp, 27, 0x80ae);	/* cg_i_c initial value */
	r8169_mdio_write(tp, 28, 0x2006);	/* 0x760 => 0x620 */
	r8169_mdio_write(tp, 27, 0x80b6);	/* delta_g slope */
	r8169_mdio_write(tp, 28, 0x850c);	/* 0x090 => 0x085 */
}

static void r8169soc_mdio_init(struct rtl8169_private *tp)
{
	u32 tmp;
	struct pinctrl *p_sgmii_mdio;
	struct pinctrl_state * ps_sgmii_mdio;
	void __iomem *ioaddr = tp->mmio_addr;

	/* ISO spec, ETN_PHY_INTR, wait interrupt from PHY and it means MDIO is ready */
	tmp = 0;
	while ((readl(tp->mmio_clkaddr + ISO_UMSK_ISR) & BIT(27)) == 0) {
		tmp += 10;
		mdelay(10);
		if (tmp >= 100) {
			pr_err("PHY PHY_Status timeout.\n");
			break;
		}
	}
	pr_info("wait %d ms for PHY interrupt. UMSK_ISR = 0x%x\n",
		tmp, readl(tp->mmio_clkaddr + ISO_UMSK_ISR));

	MDIO_LOCK;
	/* In ByPass mode,
	   SW need to handle the EPHY Status check ,
	   OTP data update and EPHY fuse_rdy setting. */
	/* PHY will stay in state 1 mode */
	r8169_mdio_write(tp, 31, 0x0a42);
	tmp = 0;
	while (0x1 != (r8169_mdio_read(tp, 16) & 0x07)) {
		tmp += 10;
		mdelay(10);
		if (tmp >= 2000) {
			pr_err("PHY status is not 0x1 in bypass mode, current = 0x%02x\n",
				(r8169_mdio_read(tp, 16) & 0x07));
			break;
		}
	}

	/* fill fuse_rdy & rg_ext_ini_done */
	r8169_mdio_write(tp, 31, 0x0a46);
	r8169_mdio_write(tp, 20,
		(r8169_mdio_read(tp, 20) | (BIT(1) | BIT(0))));

	/* init_autoload_done = 1 */
	tmp = r8169soc_ocp_reg_read(tp, 0xe004);
	tmp |= BIT(7);
	r8169soc_ocp_reg_write(tp, 0xe004, tmp);

	/* ee_mode = 3 */
	RTL_W8(Cfg9346, Cfg9346_Unlock);

	/* wait LAN-ON */
	r8169_mdio_write(tp, 31, 0x0a42);
	tmp = 0;
	do {
		tmp += 10;
		mdelay(10);
		if (tmp >= 2000) {
			pr_err("PHY status is not 0x3, current = 0x%02x\n",
				(r8169_mdio_read(tp, 16) & 0x07));
			break;
		}
	} while (0x3 != (r8169_mdio_read(tp, 16) & 0x07));
	pr_info("wait %d ms for PHY ready, current = 0x%x\n",
		tmp, r8169_mdio_read(tp, 16));

	/* adjust PHY SRAM table */
	r8169soc_phy_sram_table(tp);

	/* adjust PHY electrical characteristics */
	r8169soc_phy_iol_tuning(tp);

	/* load OTP contents (RC-K, R-K, Amp-K, and Bias-K)
	   RC-K:	0x980174F8[27:24]
	   R-K:		0x98017500[18:15]
	   Amp-K:	0x980174FC[15:0]
	   Bias-K:	0x980174FC[31:16]
	 */
	r8169soc_load_otp_content(tp);

	MDIO_UNLOCK;

	if (tp->output_mode == OUTPUT_EMBEDDED_PHY) {
		/* Init PHY path */
		/* reg_0x9800705c[5] = 0 */
		/* reg_0x9800705c[7] = 0 */
		/* ISO spec, set internal MDIO to access PHY */
		tmp = readl(tp->mmio_clkaddr + ISO_POWERCUT_ETN);
		tmp &= ~(BIT(7) | BIT(5));
		writel(tmp, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

		/* reg_0x9800705c[4] = 0 */
		/* ISO spec, set data path to access PHY */
		tmp = readl(tp->mmio_clkaddr + ISO_POWERCUT_ETN);
		tmp &= ~(BIT(4));
		writel(tmp, tp->mmio_clkaddr + ISO_POWERCUT_ETN);

		/* # ETN spec, GMAC data path select MII-like(embedded GPHY), not SGMII(external PHY) */
		tmp = r8169soc_ocp_reg_read(tp, 0xea34) & ~(BIT(0) | BIT(1));
		tmp |= BIT(1); /* MII */
		r8169soc_ocp_reg_write(tp, 0xea34, tmp);
	} else {
		/* SGMII */
		/* # ETN spec, adjust MDC freq=2.5MHz */
		r8169soc_ocp_reg_write(tp, 0xDE30,
			r8169soc_ocp_reg_read(tp, 0xDE30) & ~(BIT(7) | BIT(6)));
		/* # ETN spec, set external PHY addr */
		r8169soc_ocp_reg_write(tp, 0xDE24,
			((r8169soc_ocp_reg_read(tp, 0xDE24) & ~(0x1f << 0)) |
						(tp->ext_phy_id & 0x1f)));
		/* ISO mux spec, GPIO29 is set to MDC pin */
		/* ISO mux spec, GPIO46 is set to MDIO pin */
		p_sgmii_mdio = devm_pinctrl_get(&tp->pdev->dev);
		ps_sgmii_mdio = pinctrl_lookup_state(p_sgmii_mdio, "sgmii");
		pinctrl_select_state(p_sgmii_mdio, ps_sgmii_mdio);

		/* check if external PHY is available */
		pr_info("Searching external PHY...");
		MDIO_LOCK;
		tp->ext_phy = true;
		r8169_mdio_write(tp, 31, 0x0a43);
		tmp = 0;
		while (0xa43 != r8169_mdio_read(tp, 31)) {
			pr_info(".");
			tmp += 100;
			mdelay(100);
			if (tmp >= 2000) {
				pr_err("\n External SGMII PHY not found, current = 0x%02x\n",
					r8169_mdio_read(tp, 31));
				return;
			}
		}
		if (tmp < 2000)
			pr_info("found.\n");

		/* lower SGMII TX swing of RTL8211FS to reduce EMI */
		r8169_mdio_write(tp, 31, 0x0dcd);
		r8169_mdio_write(tp, 16, 0x104e);	/* TX swing = 470mV, default value */

		tp->ext_phy = false;
		MDIO_UNLOCK;

		/* # ETN spec, GMAC data path select SGMII(external PHY), not MII-like(embedded GPHY) */
		tmp = r8169soc_ocp_reg_read(tp, 0xea34) & ~(BIT(0) | BIT(1));
		tmp |= BIT(1) | BIT(0); /* SGMII */
		r8169soc_ocp_reg_write(tp, 0xea34, tmp);

		if (0 != r8169soc_serdes_init(tp))
			pr_err("SERDES init failed\n");
		/* ext_phy == true now */

		/* SDS spec, auto update SGMII link capability */
		tmp = readl(tp->mmio_sdsaddr + SDS_DEBUG);
		tmp |= BIT(2);
		writel(tmp, tp->mmio_sdsaddr + SDS_DEBUG);

		/* enable 8b/10b symbol error even it is only valid in 1000Mbps */
		r8169_mdio_write(tp, 31, 0x0dcf);
		r8169_mdio_write(tp, 16,
			(r8169_mdio_read(tp, 16) & ~(BIT(2) | BIT(1) | BIT(0))));
		r8169_mdio_read(tp, 17); /* dummy read */
	}
}

static void r8169soc_eee_init(struct rtl8169_private *tp, bool enable)
{
	if (enable) {
		MDIO_LOCK;
		if (tp->output_mode == OUTPUT_EMBEDDED_PHY) {
			/* 100M EEE capability */
			r8169_mmd_write(tp, 0x7, 60, BIT(1));
			/* 10M EEE */
			r8169_mdio_write(tp, 31, 0xa43);
			r8169_mdio_write(tp, 25, r8169_mdio_read(tp, 25) | (BIT(4) | BIT(2)));
			/* disable dynamic RX power in PHY */
			r8169_mdio_write(tp, 31, 0xbd0);
			r8169_mdio_write(tp, 21, (r8169_mdio_read(tp, 21) & ~BIT(8)) | BIT(9));
		} else { /* SGMII */
			/* 1000M & 100M EEE capability */
			r8169_mmd_write(tp, 0x7, 60, (BIT(2) | BIT(1)));
			/* 10M EEE */
			r8169_mdio_write(tp, 31, 0xa43);
			r8169_mdio_write(tp, 25, r8169_mdio_read(tp, 25) | (BIT(4) | BIT(2)));
		}
		MDIO_UNLOCK;
		/* EEE MAC mode */
		r8169soc_ocp_reg_write(tp, 0xe040, (r8169soc_ocp_reg_read(tp, 0xe040) | (BIT(1) | BIT(0))));
		/* EEE+ MAC mode */
		r8169soc_ocp_reg_write(tp, 0xe080, (r8169soc_ocp_reg_read(tp, 0xe080) | BIT(1)));
	} else {
		if (tp->output_mode == OUTPUT_EMBEDDED_PHY) {
			/* no EEE capability */
			r8169_mmd_write(tp, 0x7, 60, 0);
			/* 10M EEE */
			r8169_mdio_write(tp, 31, 0xa43);
			r8169_mdio_write(tp, 25, r8169_mdio_read(tp, 25) & ~(BIT(4) | BIT(2)));
		} else { /* SGMII */
			/* no EEE capability */
			r8169_mmd_write(tp, 0x7, 60, 0);
			/* 10M EEE */
			r8169_mdio_write(tp, 31, 0xa43);
			r8169_mdio_write(tp, 25, r8169_mdio_read(tp, 25) & ~(BIT(4) | BIT(2)));
		}
		MDIO_UNLOCK;
		/* reset to default value */
		r8169soc_ocp_reg_write(tp, 0xe040, (r8169soc_ocp_reg_read(tp, 0xe040) | BIT(13)));
		/* EEE MAC mode */
		r8169soc_ocp_reg_write(tp, 0xe040, (r8169soc_ocp_reg_read(tp, 0xe040) & ~(BIT(1) | BIT(0))));
		/* EEE+ MAC mode */
		r8169soc_ocp_reg_write(tp, 0xe080, (r8169soc_ocp_reg_read(tp, 0xe080) & ~BIT(1)));
	}
}
#endif /* CONFIG_ARCH_RTD16xx */

static int
rtl_init_one(struct platform_device *pdev)
{
	struct rtl_cfg_info *cfg;
	struct rtl8169_private *tp;
	struct mii_if_info *mii;
	struct net_device *ndev;
	void __iomem *ioaddr;
	void __iomem *clkaddr;
	int chipset, i;
	int rc;
	int rtl_config;
	int mac_version;
	u32 tmp;
	int irq;
	int retry;
	const char *mac_addr;
#ifdef RTL_PROC
	struct proc_dir_entry *dir_dev = NULL;
	struct proc_dir_entry *entry=NULL;
#endif
	#if defined(CONFIG_ARCH_RTD129x)
	struct clk *clk_etn_sys  = clk_get(&pdev->dev, "etn_sys");
	struct clk *clk_etn_250m = clk_get(&pdev->dev, "etn_250m");
	struct reset_control *rstc_gphy = reset_control_get(&pdev->dev, "gphy");
	struct reset_control *rstc_gmac = reset_control_get(&pdev->dev, "gmac");
	u32 rgmii_voltage = 1;
	u32 rgmii_tx_delay = 0;
	u32 rgmii_rx_delay = 0;
	#elif defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
	void __iomem *sbxaddr;
	void __iomem *otpaddr;
	void __iomem *sdsaddr;
	void __iomem *pinmuxaddr;
	u32 bypass_enable = 0;
	u32 acp_enable = 0;
	#if defined(CONFIG_ARCH_RTD16xx)
	u32 sgmii_swing = 0;
	#endif /* CONFIG_ARCH_RTD16xx */
	#endif /* CONFIG_ARCH_RTD129x | CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */
	u32 output_mode = 0;
	u32 ext_phy_id = 1;
	u32 eee_enable = 0;

	if (netif_msg_drv(&debug)) {
		printk(KERN_INFO "%s Gigabit Ethernet driver %s loaded\n",
			   MODULENAME, RTL8169_VERSION);
	}

#if 1	//barry
	if (of_property_read_u32(pdev->dev.of_node, "rtl-config", &rtl_config)) {
		dprintk("%s canot specified config", __func__);
	}
	cfg = rtl_cfg_infos + rtl_config;
	if (of_property_read_u32(pdev->dev.of_node, "mac-version", &mac_version)) {
		dprintk("%s canot specified config", __func__);
	}
	if (of_property_read_u32(pdev->dev.of_node, "output-mode", &output_mode)) {
		dprintk("%s can't get output mode", __func__);
	}
	if (of_property_read_u32(pdev->dev.of_node, "ext-phy-id", &ext_phy_id)) {
		dprintk("%s can't get RGMII external PHY ID", __func__);
	}
	if (of_property_read_u32(pdev->dev.of_node, "eee", &eee_enable)) {
		dprintk("%s can't get eee_enable", __func__);
	}

	#if defined(CONFIG_ARCH_RTD129x)
	if (of_property_read_u32(pdev->dev.of_node, "rgmii-voltage", &rgmii_voltage)) {
		dprintk("%s can't get RGMII voltage", __func__);
	}
	if (of_property_read_u32(pdev->dev.of_node, "rgmii-tx-delay", &rgmii_tx_delay)) {
		dprintk("%s can't get RGMII TX delay", __func__);
	}
	if (of_property_read_u32(pdev->dev.of_node, "rgmii-rx-delay", &rgmii_rx_delay)) {
		dprintk("%s can't get RGMII RX delay", __func__);
	}
	#elif defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
	if (of_property_read_u32(pdev->dev.of_node, "bypass", &bypass_enable)) {
		dprintk("%s can't get bypass", __func__);
	}
	if (of_property_read_u32(pdev->dev.of_node, "acp", &acp_enable)) {
		dprintk("%s can't get acp", __func__);
	}
	#if defined(CONFIG_ARCH_RTD16xx)
	if (of_property_read_u32(pdev->dev.of_node, "sgmii-swing", &sgmii_swing)) {
		dprintk("%s can't get sgmii-swing", __func__);
	}
	#endif /* CONFIG_ARCH_RTD16xx */
	sbxaddr = of_iomap(pdev->dev.of_node, 2);
	otpaddr = of_iomap(pdev->dev.of_node, 3);
	sdsaddr = of_iomap(pdev->dev.of_node, 4);
	pinmuxaddr = of_iomap(pdev->dev.of_node, 5);
	#endif /* CONFIG_ARCH_RTD129x | CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */

	if (soc_is_rtk1195() && (realtek_rev() == RTK1195_REV_A)) {
		if (of_property_read_u32(pdev->dev.of_node, "rtl-features", &(cfg->features))) {
			cfg->features &= ~RTL_FEATURE_GMII;
		}
	}
	if (of_get_property(pdev->dev.of_node, "force-Gb-off", NULL)) {
		pr_info("~~~ disable Gb features~~~\n");
		cfg->features &= ~RTL_FEATURE_GMII;
	}
	irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	if (!pdev->dev.dma_mask)
		pdev->dev.dma_mask = &pdev->dev.coherent_dma_mask;
	if (!pdev->dev.coherent_dma_mask)
		pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);

	ioaddr = of_iomap(pdev->dev.of_node, 0);


	clkaddr = of_iomap(pdev->dev.of_node, 1);

	ndev = alloc_etherdev(sizeof (*tp));
	if (!ndev) {
		rc = -ENOMEM;
		goto out;
	}

	SET_NETDEV_DEV(ndev, &pdev->dev);
	ndev->netdev_ops = &rtl_netdev_ops;
	ndev->irq = irq;
	tp = netdev_priv(ndev);
	tp->dev = ndev;
	tp->pdev = pdev;
	tp->msg_enable = netif_msg_init(debug.msg_enable, R8169_MSG_DEFAULT);
	tp->mac_version = mac_version - 1;
	tp->mmio_addr = ioaddr;
	tp->mmio_clkaddr = clkaddr;
	tp->output_mode = output_mode;
	tp->ext_phy_id = ext_phy_id;
	tp->eee_enable = !!(eee_enable > 0);
	#if defined(CONFIG_ARCH_RTD129x)
	tp->rgmii_voltage = rgmii_voltage;
	tp->rgmii_tx_delay = rgmii_tx_delay;
	tp->rgmii_rx_delay = rgmii_rx_delay;
	tp->acp_enable = false;
	#elif defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
	tp->mmio_sbxaddr = sbxaddr;
	tp->mmio_otpaddr = otpaddr;
	tp->mmio_sdsaddr = sdsaddr;
	tp->mmio_pinmuxaddr = pinmuxaddr;
	tp->bypass_enable = !!(bypass_enable > 0);
	tp->acp_enable = !!(acp_enable > 0);
	tp->ext_phy = false;
	#if defined(CONFIG_ARCH_RTD16xx)
	tp->sgmii_swing = sgmii_swing;
	#endif /* CONFIG_ARCH_RTD16xx */
	#endif /* CONFIG_ARCH_RTD129x | CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */

	mii = &tp->mii;
	mii->dev = ndev;
	mii->mdio_read = rtl_mdio_read;
	mii->mdio_write = rtl_mdio_write;
	mii->phy_id_mask = 0x1f;
	mii->reg_num_mask = 0x1f;
	mii->supports_gmii = !!(cfg->features & RTL_FEATURE_GMII);

//#define ETN_GPHY_BYPASS 0x98007060
//#define ETN_RESET_CTRL  0x98007088
//#define ETN_CLK_CTRL    0x9800708c
//#define ETN_DBUS_CLK    0x98007fc0

	#if defined(CONFIG_ARCH_RTD129x)
	if (unlikely(!__clk_is_enabled(clk_etn_sys) || !__clk_is_enabled(clk_etn_250m))) {
		//1. reg_0x98007088[10] = 1                    // ISO spec, reset bit of gphy
		reset_control_deassert(rstc_gphy);

		//2. CPU software waiting 200uS
		udelay(200);

		//3. reg_0x98007060[1] = 0                      // ISO spec, Ethernet Boot up bypass gphy ready mode
		tmp = readl(clkaddr+0x60);
		tmp &= ~BIT(1);
		writel(tmp,clkaddr+0x60);

		//4. reg_0x98007fc0[0] = 0                      // ISO spec, Ethernet Boot up disable dbus clock gating
		tmp = readl(clkaddr+0xfc0);
		tmp &= ~BIT(0);
		writel(tmp,clkaddr+0xfc0);

		//5. CPU software waiting 200uS
		udelay(200);

		//6. reg_0x9800708c[12:11] = 11              // ISO spec, clock enable bit for etn clock & etn 250MHz
		clk_prepare_enable(clk_etn_sys);
		clk_prepare_enable(clk_etn_250m);

		//7. reg_0x9800708c[12:11] = 00              // ISO spec, clock enable bit for etn clock & etn 250MHz
		clk_disable_unprepare(clk_etn_sys);
		clk_disable_unprepare(clk_etn_250m);

		//8. reg_0x98007088[9] = 1                      // ISO spec, reset bit of gmac
		reset_control_deassert(rstc_gmac);

		//9. reg_0x9800708c[12:11] = 11              // ISO spec, clock enable bit for etn clock & etn 250MHz
		clk_prepare_enable(clk_etn_sys);
		clk_prepare_enable(clk_etn_250m);

		msleep(100);
	}
	#elif defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
	r8169soc_reset_phy_gmac(tp);
	r8169soc_acp_init(tp);
	r8169soc_pll_clock_init(tp);
	r8169soc_mdio_init(tp);
	/* after r8169soc_mdio_init(),
	   SGMII : tp->ext_phy == true  ==> external MDIO,
	   FE PHY: tp->ext_phy == false ==> internal MDIO */

	r8169soc_eee_init(tp, tp->eee_enable);

	/* Enable ALDPS */
	MDIO_LOCK;
	r8169_mdio_write(tp, 31, 0xa43);
	r8169_mdio_write(tp, 24, (r8169_mdio_read(tp, 24) | BIT(2)));
	MDIO_UNLOCK;
	#endif /* CONFIG_ARCH_RTD129x | CONFIG_ARCH_RTD139x | CONFIG_ARCH_RTD16xx */
#endif

#if 0	//barry
	/* disable ASPM completely as that cause random device stop working
	 * problems as well as full system hangs for some PCIe devices users */
	pci_disable_link_state(pdev, PCIE_LINK_STATE_L0S | PCIE_LINK_STATE_L1 |
					 PCIE_LINK_STATE_CLKPM);

	/* enable device (incl. PCI PM wakeup and hotplug setup) */
	rc = pci_enable_device(pdev);
	if (rc < 0) {
		netif_err(tp, probe, dev, "enable failure\n");
		goto err_out_free_dev_1;
	}

	if (pci_set_mwi(pdev) < 0)
		netif_info(tp, probe, dev, "Mem-Wr-Inval unavailable\n");

	/* make sure PCI base addr 1 is MMIO */
	if (!(pci_resource_flags(pdev, region) & IORESOURCE_MEM)) {
		netif_err(tp, probe, dev,
			  "region #%d not an MMIO resource, aborting\n",
			  region);
		rc = -ENODEV;
		goto err_out_mwi_2;
	}

	/* check for weird/broken PCI region reporting */
	if (pci_resource_len(pdev, region) < R8169_REGS_SIZE) {
		netif_err(tp, probe, dev,
			  "Invalid PCI region size(s), aborting\n");
		rc = -ENODEV;
		goto err_out_mwi_2;
	}

	rc = pci_request_regions(pdev, MODULENAME);
	if (rc < 0) {
		netif_err(tp, probe, dev, "could not request regions\n");
		goto err_out_mwi_2;
	}

	tp->cp_cmd = RxChkSum;

	if ((sizeof(dma_addr_t) > 4) &&
		!pci_set_dma_mask(pdev, DMA_BIT_MASK(64)) && use_dac) {
		tp->cp_cmd |= PCIDAC;
		dev->features |= NETIF_F_HIGHDMA;
	} else {
		rc = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		if (rc < 0) {
			netif_err(tp, probe, dev, "DMA configuration failed\n");
			goto err_out_free_res_3;
		}
	}

	/* ioremap MMIO region */
	ioaddr = ioremap(pci_resource_start(pdev, region), R8169_REGS_SIZE);
	if (!ioaddr) {
		netif_err(tp, probe, dev, "cannot remap MMIO, aborting\n");
		rc = -EIO;
		goto err_out_free_res_3;
	}
#endif
#ifdef RTL_PROC
	do{
		// create /proc/net/$rtw_proc_name
		rtw_proc=proc_mkdir_data("eth0",  S_IRUGO|S_IXUGO,init_net.proc_net, NULL);

		if (rtw_proc == NULL) {
			//DBG_871X(KERN_ERR "Unable to create rtw_proc directory\n");
			printk(KERN_INFO "procfs:create /proc/net/eth0 failed\n");
			break;
		}

		// create /proc/net/$rtw_proc_name/$dev->name
		if(tp->dir_dev == NULL)
		{
			tp->dir_dev = proc_mkdir_data(MODULENAME, S_IFDIR | S_IRUGO | S_IXUGO,rtw_proc, ndev);
			dir_dev = tp->dir_dev;

			if(dir_dev==NULL)
			{
				printk(KERN_INFO "procfs:create /proc/net/eth0/r8169 failed\n");

				if(rtw_proc){
					remove_proc_entry("eth0", init_net.proc_net);
					rtw_proc = NULL;
				}
				break;
			}
		}
		else
		{
			break;
		}


		entry = proc_create_data("wol_enable", S_IFREG | S_IRUGO,
				   dir_dev, &proc_fops, NULL);
		if (!entry) {
			printk(KERN_INFO "procfs:create /proc/net/eth0/r8169/wol_enable failed\n");
			break;
		}

		entry = proc_create_data("eee", S_IFREG | S_IRUGO,
				   dir_dev, &eee_proc_fops, NULL);
		if (!entry) {
			printk(KERN_INFO "procfs:create /proc/net/eth0/r8169/eee failed\n");
			break;
		}

		entry = proc_create_data("test", S_IFREG | S_IRUGO,
				   dir_dev, &test_proc_fops, NULL);
		if (!entry) {
			printk(KERN_INFO "procfs:create /proc/net/eth0/r8169/test failed\n");
			break;
		}
	}while(0);
#endif

//	if (!pci_is_pcie(pdev))
//		netif_info(tp, probe, dev, "not PCI Express\n");

	/* Identify chip attached to board */
	rtl8169_get_mac_version(tp, ndev, cfg->default_ver);

	rtl_init_rxcfg(tp);

	rtl_irq_disable(tp);

	rtl_hw_initialize(tp);

	rtl_hw_reset(tp);

	rtl_ack_events(tp, 0xffff);

//	pci_set_master(pdev);

	/*
	 * Pretend we are using VLANs; This bypasses a nasty bug where
	 * Interrupts stop flowing on high load on 8110SCd controllers.
	 */
	if (tp->mac_version == RTL_GIGA_MAC_VER_05)
		tp->cp_cmd |= RxVlan;

	rtl_init_mdio_ops(tp);
	rtl_init_pll_power_ops(tp);
	rtl_init_jumbo_ops(tp);
	rtl_init_csi_ops(tp);

	rtl8169_print_mac_version(tp);

	chipset = tp->mac_version;
	tp->txd_version = rtl_chip_infos[chipset].txd_version;

	RTL_W8(Cfg9346, Cfg9346_Unlock);
	RTL_W8(Config1, RTL_R8(Config1) | PMEnable);
	RTL_W8(Config5, RTL_R8(Config5) & PMEStatus);

	//disable magic packet WOL
	RTL_W8(Config3, RTL_R8(Config3) & ~MagicPacket);

	if ((RTL_R8(Config3) & (LinkUp | MagicPacket)) != 0)
		tp->features |= RTL_FEATURE_WOL;
	if ((RTL_R8(Config5) & (UWF | BWF | MWF)) != 0)
		tp->features |= RTL_FEATURE_WOL;
	tp->features |= rtl_try_msi(tp, cfg);
	RTL_W8(Cfg9346, Cfg9346_Lock);

	if (rtl_tbi_enabled(tp)) {
		tp->set_speed = rtl8169_set_speed_tbi;
		tp->get_settings = rtl8169_gset_tbi;
		tp->phy_reset_enable = rtl8169_tbi_reset_enable;
		tp->phy_reset_pending = rtl8169_tbi_reset_pending;
		tp->link_ok = rtl8169_tbi_link_ok;
		tp->do_ioctl = rtl_tbi_ioctl;
	} else {
		tp->set_speed = rtl8169_set_speed_xmii;
		tp->get_settings = rtl8169_gset_xmii;
		tp->phy_reset_enable = rtl8169_xmii_reset_enable;
		tp->phy_reset_pending = rtl8169_xmii_reset_pending;
		tp->link_ok = rtl8169_xmii_link_ok;
		tp->do_ioctl = rtl_xmii_ioctl;
	}

	#if defined(CONFIG_ARCH_RTD129x)
	if ((get_rtd129x_cpu_revision() >= RTD129x_CHIP_REVISION_B00) &&
		(tp->output_mode == OUTPUT_RGMII_TO_MAC))
		tp->link_ok = rtl8169_xmii_always_link_ok;
	#elif defined(CONFIG_ARCH_RTD139x)
	if (tp->output_mode == OUTPUT_SGMII_TO_MAC)
		tp->link_ok = rtl8169_xmii_always_link_ok;
	#endif /* CONFIG_ARCH_RTD129x | CONFIG_ARCH_RTD139x */

	mutex_init(&tp->wk.mutex);

	/* Get MAC address */
	mac_addr = of_get_mac_address(pdev->dev.of_node);
	if (mac_addr)
		rtl_rar_set(tp, (u8*)mac_addr);

	/* workaround: avoid getting deadbeef */
	#define RETRY_MAX	10
	for (retry = 0; retry < RETRY_MAX; retry++) {
		for (i = 0; i < ETH_ALEN; i++)
			ndev->dev_addr[i] = RTL_R8(MAC0 + i);

		if (*(u32 *) ndev->dev_addr != 0xdeadbeef) {
			break;
		} else {
			printk(KERN_ERR "%s get invalid MAC address %pM, retry %d\n",
				rtl_chip_infos[chipset].name, ndev->dev_addr, retry);
			tmp = RTL_R32(PHYAR); // read something else
			msleep(10);
		}
	}
	if (retry == RETRY_MAX)
		printk(KERN_ERR "%s get invalid MAC address %pM, give up!\n",
			rtl_chip_infos[chipset].name, ndev->dev_addr);


	ndev->ethtool_ops = &rtl8169_ethtool_ops;
	ndev->watchdog_timeo = RTL8169_TX_TIMEOUT;

	netif_napi_add(ndev, &tp->napi, rtl8169_poll, R8169_NAPI_WEIGHT);

	/* don't enable SG, IP_CSUM and TSO by default - it might not work
	 * properly for all devices */
	ndev->features |= NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_TSO |NETIF_F_RXCSUM | NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX;

	ndev->hw_features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_TSO |
		NETIF_F_RXCSUM | NETIF_F_HW_VLAN_CTAG_TX |
		NETIF_F_HW_VLAN_CTAG_RX;
	ndev->vlan_features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_TSO |
		NETIF_F_HIGHDMA;

	if (tp->mac_version == RTL_GIGA_MAC_VER_05)
		/* 8110SCd requires hardware Rx VLAN - disallow toggling */
		ndev->hw_features &= ~NETIF_F_HW_VLAN_CTAG_RX;

	ndev->hw_features |= NETIF_F_RXALL;
	ndev->hw_features |= NETIF_F_RXFCS;

	tp->hw_start = cfg->hw_start;
	tp->event_slow = cfg->event_slow;

	tp->opts1_mask = (tp->mac_version != RTL_GIGA_MAC_VER_01) ?
		~(RxBOVF | RxFOVF) : ~0;

	init_timer(&tp->timer);
	tp->timer.data = (unsigned long) ndev;
	tp->timer.function = rtl8169_phy_timer;

	tp->rtl_fw = RTL_FIRMWARE_UNKNOWN;

	rc = register_netdev(ndev);
	if (rc < 0)
		goto err_out_msi_4;

//	pci_set_drvdata(pdev, dev);
	platform_set_drvdata(pdev, ndev);

	netif_info(tp, probe, ndev, "%s at 0x%p, XID %08x IRQ %d\n",
		   rtl_chip_infos[chipset].name, ioaddr,
		   (u32)(RTL_R32(TxConfig) & 0x9cf0f8ff), ndev->irq);
	if (rtl_chip_infos[chipset].jumbo_max != JUMBO_1K) {
		netif_info(tp, probe, ndev, "jumbo features [frames: %d bytes, "
			   "tx checksumming: %s]\n",
			   rtl_chip_infos[chipset].jumbo_max,
			   rtl_chip_infos[chipset].jumbo_tx_csum ? "ok" : "ko");
	}

	if (tp->mac_version == RTL_GIGA_MAC_VER_27 ||
		tp->mac_version == RTL_GIGA_MAC_VER_28 ||
		tp->mac_version == RTL_GIGA_MAC_VER_31) {
		rtl8168_driver_start(tp);
	}

	device_set_wakeup_enable(&pdev->dev, tp->features & RTL_FEATURE_WOL);

//	if (pci_dev_run_wake(pdev))
//		pm_runtime_put_noidle(&pdev->dev);

	netif_carrier_off(ndev);

	/* Yukuen: Add for link status uevent. 20150206 */
	init_waitqueue_head(&tp->thr_wait);
	tp->link_chg = 0;
	tp->kthr = NULL;
	tp->kthr = kthread_create(link_status, (void*)ndev, "%s-linkstatus", ndev->name);
	if(IS_ERR(tp->kthr)){
		tp->kthr = NULL;
		printk (KERN_WARNING "%s: unable to start kthread for link status.\n",
				ndev->name);
	}
	else{
		wake_up_process(tp->kthr);  // run thread function
	}

out:
	return rc;

err_out_msi_4:
	netif_napi_del(&tp->napi);
//	rtl_disable_msi(pdev, tp);
//	iounmap(ioaddr);
//err_out_free_res_3:
//	pci_release_regions(pdev);
//err_out_mwi_2:
//	pci_clear_mwi(pdev);
//	pci_disable_device(pdev);
//err_out_free_dev_1:
	free_netdev(ndev);
	goto out;
}

static struct platform_driver rtl8169_soc_driver = {
	.probe		= rtl_init_one,
	.remove		= rtl_remove_one,
	.shutdown	= rtl_shutdown,
	.driver = {
		.name		= MODULENAME,
		.owner		= THIS_MODULE,
		.pm			= RTL8169_PM_OPS,
		.of_match_table = of_match_ptr(rtl8169_dt_ids),
	},
};

module_platform_driver(rtl8169_soc_driver);
