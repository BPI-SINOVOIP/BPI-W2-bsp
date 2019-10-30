/*
 * Realtek switch ethernet speed tool
 */

#include <common.h>
#include <command.h>
#include <asm/arch/io.h>
#include <linux/mii.h>
#include <linux/ethtool.h>

/*
#define DEBUG
*/

#define MMIO_ADDR 0x98016000

#define AUTONEG_ENABLE	0x01
#define DUPLEX_HALF		0x00
#define DUPLEX_FULL		0x01
#define SPEED_10		10
#define SPEED_100		100
#define SPEED_1000		1000

/* write/read MMIO register. Notice: {read,write}[wl] do the necessary swapping */
#define RTL_W8(reg, val8)	writeb ((val8), ioaddr + (reg))
#define RTL_W16(reg, val16)	writew ((val16), ioaddr + (reg))
#define RTL_W32(reg, val32)	writel ((val32), ioaddr + (reg))
#define RTL_R8(reg)			readb (ioaddr + (reg))
#define RTL_R16(reg)		readw (ioaddr + (reg))
#define RTL_R32(reg)		((unsigned long) readl (ioaddr + (reg)))

enum RTL8168_registers {
	MAC0            = 0x00,     /* Ethernet hardware address. */
	MAC4            = 0x04,
	MAR0            = 0x08,     /* Multicast filter. */
	CounterAddrLow  = 0x10,
	CounterAddrHigh = 0x14,
	CustomLED       = 0x18,
	TxDescStartAddrLow      = 0x20,
	TxDescStartAddrHigh     = 0x24,
	TxHDescStartAddrLow     = 0x28,
	TxHDescStartAddrHigh    = 0x2c,
	FLASH           = 0x30,
	ERSR            = 0x36,
	ChipCmd         = 0x37,
	TxPoll          = 0x38,
	IntrMask        = 0x3C,
	IntrStatus      = 0x3E,
	TxConfig        = 0x40,
	RxConfig        = 0x44,
	TCTR            = 0x48,
	Cfg9346         = 0x50,
	Config0         = 0x51,
	Config1         = 0x52,
	Config2         = 0x53,
	Config3         = 0x54,
	Config4         = 0x55,
	Config5         = 0x56,
	TDFNR           = 0x57,
	TimeIntr        = 0x58,
	PHYAR           = 0x60,
	CSIDR           = 0x64,
	CSIAR           = 0x68,
	PHYstatus       = 0x6C,
	MACDBG          = 0x6D,
	GPIO            = 0x6E,
	PMCH            = 0x6F,
	ERIDR           = 0x70,
	ERIAR           = 0x74,
	EPHY_RXER_NUM   = 0x7C,
	EPHYAR          = 0x80,
	OCPDR           = 0xB0,
	MACOCP          = 0xB0,
	OCPAR           = 0xB4,
	PHYOCP          = 0xB8,
	DBG_reg         = 0xD1,
	MCUCmd_reg      = 0xD3,
	RxMaxSize       = 0xDA,
	EFUSEAR         = 0xDC,
	CPlusCmd        = 0xE0,
	IntrMitigate    = 0xE2,
	RxDescAddrLow   = 0xE4,
	RxDescAddrHigh  = 0xE8,
	MTPS            = 0xEC,
	FuncEvent       = 0xF0,
	FuncEventMask   = 0xF4,
	FuncPresetState = 0xF8,
	FuncForceEvent  = 0xFC,
};

enum RTL8168_register_content {
	/* InterruptStatusBits */
	SYSErr      = 0x8000,
	PCSTimeout  = 0x4000,
	SWInt       = 0x0100,
	TxDescUnavail   = 0x0080,
	RxFIFOOver  = 0x0040,
	LinkChg     = 0x0020,
	RxDescUnavail   = 0x0010,
	TxErr       = 0x0008,
	TxOK        = 0x0004,
	RxErr       = 0x0002,
	RxOK        = 0x0001,

	/* RxStatusDesc */
	RxRWT = (1 << 22),
	RxRES = (1 << 21),
	RxRUNT = (1 << 20),
	RxCRC = (1 << 19),

	/* ChipCmdBits */
	StopReq  = 0x80,
	CmdReset = 0x10,
	CmdRxEnb = 0x08,
	CmdTxEnb = 0x04,
	RxBufEmpty = 0x01,

	/* Cfg9346Bits */
	Cfg9346_Lock = 0x00,
	Cfg9346_Unlock = 0xC0,
	Cfg9346_EEDO = (1 << 0),
	Cfg9346_EEDI = (1 << 1),
	Cfg9346_EESK = (1 << 2),
	Cfg9346_EECS = (1 << 3),
	Cfg9346_EEM0 = (1 << 6),
	Cfg9346_EEM1 = (1 << 7),

	/* rx_mode_bits */
	AcceptErr = 0x20,
	AcceptRunt = 0x10,
	AcceptBroadcast = 0x08,
	AcceptMulticast = 0x04,
	AcceptMyPhys = 0x02,
	AcceptAllPhys = 0x01,

	/* Transmit Priority Polling*/
	HPQ = 0x80,
	NPQ = 0x40,
	FSWInt = 0x01,

	/* RxConfigBits */
	Reserved2_shift = 13,
	RxCfgDMAShift = 8,
	RxCfg_128_int_en = (1 << 15),
	RxCfg_fet_multi_en = (1 << 14),
	RxCfg_half_refetch = (1 << 13),
	RxCfg_9356SEL = (1 << 6),

	/* TxConfigBits */
	TxInterFrameGapShift = 24,
	TxDMAShift = 8, /* DMA burst value (0-7) is shift this many bits */
	TxMACLoopBack = (1 << 17),  /* MAC loopback */

	/* Config1 register */
	LEDS1       = (1 << 7),
	LEDS0       = (1 << 6),
	Speed_down  = (1 << 4),
	MEMMAP      = (1 << 3),
	IOMAP       = (1 << 2),
	VPD         = (1 << 1),
	PMEnable    = (1 << 0), /* Power Management Enable */

	/* Config2 register */
	PMSTS_En    = (1 << 5),

	/* Config3 register */
	Isolate_en  = (1 << 12), /* Isolate enable */
	MagicPacket = (1 << 5), /* Wake up when receives a Magic Packet */
	LinkUp      = (1 << 4), /* This bit is reserved in RTL8168B.*/
	/* Wake up when the cable connection is re-established */
	ECRCEN      = (1 << 3), /* This bit is reserved in RTL8168B*/
	Jumbo_En0   = (1 << 2), /* This bit is reserved in RTL8168B*/
	RDY_TO_L23  = (1 << 1), /* This bit is reserved in RTL8168B*/
	Beacon_en   = (1 << 0), /* This bit is reserved in RTL8168B*/

	/* Config4 register */
	Jumbo_En1   = (1 << 1), /* This bit is reserved in RTL8168B*/

	/* Config5 register */
	BWF     = (1 << 6), /* Accept Broadcast wakeup frame */
	MWF     = (1 << 5), /* Accept Multicast wakeup frame */
	UWF     = (1 << 4), /* Accept Unicast wakeup frame */
	LanWake     = (1 << 1), /* LanWake enable/disable */
	PMEStatus   = (1 << 0), /* PME status can be reset by PCI RST# */

	/* CPlusCmd */
	EnableBist  = (1 << 15),
	Macdbgo_oe  = (1 << 14),
	Normal_mode = (1 << 13),
	Force_halfdup   = (1 << 12),
	Force_rxflow_en = (1 << 11),
	Force_txflow_en = (1 << 10),
	Cxpl_dbg_sel    = (1 << 9),//This bit is reserved in RTL8168B
	ASF     = (1 << 8),//This bit is reserved in RTL8168C
	PktCntrDisable  = (1 << 7),
	RxVlan      = (1 << 6),
	RxChkSum    = (1 << 5),
	Macdbgo_sel = 0x001C,
	INTT_0      = 0x0000,
	INTT_1      = 0x0001,
	INTT_2      = 0x0002,
	INTT_3      = 0x0003,

	/* rtl8168_PHYstatus */
	PowerSaveStatus = 0x80,
	TxFlowCtrl = 0x40,
	RxFlowCtrl = 0x20,
	_1000bpsF = 0x10,
	_100bps = 0x08,
	_10bps = 0x04,
	LinkStatus = 0x02,
	FullDup = 0x01,

	/* DBG_reg */
	Fix_Nak_1 = (1 << 4),
	Fix_Nak_2 = (1 << 3),
	DBGPIN_E2 = (1 << 0),

	/* DumpCounterCommand */
	CounterDump = 0x8,

	/* PHY access */
	PHYAR_Flag = 0x80000000,
	PHYAR_Write = 0x80000000,
	PHYAR_Read = 0x00000000,
	PHYAR_Reg_Mask = 0x1f,
	PHYAR_Reg_shift = 16,
	PHYAR_Data_Mask = 0xffff,

	/* EPHY access */
	EPHYAR_Flag = 0x80000000,
	EPHYAR_Write = 0x80000000,
	EPHYAR_Read = 0x00000000,
	EPHYAR_Reg_Mask = 0x1f,
	EPHYAR_Reg_shift = 16,
	EPHYAR_Data_Mask = 0xffff,

	/* CSI access */
	CSIAR_Flag = 0x80000000,
	CSIAR_Write = 0x80000000,
	CSIAR_Read = 0x00000000,
	CSIAR_ByteEn = 0x0f,
	CSIAR_ByteEn_shift = 12,
	CSIAR_Addr_Mask = 0x0fff,

	/* ERI access */
	ERIAR_Flag = 0x80000000,
	ERIAR_Write = 0x80000000,
	ERIAR_Read = 0x00000000,
	ERIAR_Addr_Align = 4, /* ERI access register address must be 4 byte alignment */
	ERIAR_ExGMAC = 0,
	ERIAR_MSIX = 1,
	ERIAR_ASF = 2,
	ERIAR_OOB = 2,
	ERIAR_Type_shift = 16,
	ERIAR_ByteEn = 0x0f,
	ERIAR_ByteEn_shift = 12,

	/* OCP GPHY access */
	OCPDR_Write = 0x80000000,
	OCPDR_Read = 0x00000000,
	OCPDR_Reg_Mask = 0xFF,
	OCPDR_Data_Mask = 0xFFFF,
	OCPDR_GPHY_Reg_shift = 16,
	OCPAR_Flag = 0x80000000,
	OCPAR_GPHY_Write = 0x8000F060,
	OCPAR_GPHY_Read = 0x0000F060,
	OCPR_Write = 0x80000000,
	OCPR_Read = 0x00000000,
	OCPR_Addr_Reg_shift = 16,
	OCPR_Flag = 0x80000000,
	OCP_STD_PHY_BASE_PAGE = 0x0A40,

	/* MCU Command */
	Now_is_oob = (1 << 7),
	Txfifo_empty = (1 << 5),
	Rxfifo_empty = (1 << 4),

	/* E-FUSE access */
	EFUSE_WRITE = 0x80000000,
	EFUSE_WRITE_OK  = 0x00000000,
	EFUSE_READ  = 0x00000000,
	EFUSE_READ_OK   = 0x80000000,
	EFUSE_Reg_Mask  = 0x03FF,
	EFUSE_Reg_Shift = 8,
	EFUSE_Check_Cnt = 300,
	EFUSE_READ_FAIL = 0xFF,
	EFUSE_Data_Mask = 0x000000FF,

	/* GPIO */
	GPIO_en = (1 << 0),

};

enum bits {
	BIT_0 = (1 << 0),
	BIT_1 = (1 << 1),
	BIT_2 = (1 << 2),
	BIT_3 = (1 << 3),
	BIT_4 = (1 << 4),
	BIT_5 = (1 << 5),
	BIT_6 = (1 << 6),
	BIT_7 = (1 << 7),
	BIT_8 = (1 << 8),
	BIT_9 = (1 << 9),
	BIT_10 = (1 << 10),
	BIT_11 = (1 << 11),
	BIT_12 = (1 << 12),
	BIT_13 = (1 << 13),
	BIT_14 = (1 << 14),
	BIT_15 = (1 << 15),
	BIT_16 = (1 << 16),
	BIT_17 = (1 << 17),
	BIT_18 = (1 << 18),
	BIT_19 = (1 << 19),
	BIT_20 = (1 << 20),
	BIT_21 = (1 << 21),
	BIT_22 = (1 << 22),
	BIT_23 = (1 << 23),
	BIT_24 = (1 << 24),
	BIT_25 = (1 << 25),
	BIT_26 = (1 << 26),
	BIT_27 = (1 << 27),
	BIT_28 = (1 << 28),
	BIT_29 = (1 << 29),
	BIT_30 = (1 << 30),
	BIT_31 = (1 << 31)
};

static void mac_ocp_write(u16 reg_addr, u16 value)
{
	phys_addr_t ioaddr = MMIO_ADDR;
	u32 data32;

	data32 = reg_addr/2;
	data32 <<= OCPR_Addr_Reg_shift;
	data32 += value;
	data32 |= OCPR_Write;

	RTL_W32(MACOCP, data32);
}

static u16 mac_ocp_read(u16 reg_addr)
{
	phys_addr_t ioaddr = MMIO_ADDR;
	u32 data32;
	u16 data16 = 0;

	data32 = reg_addr/2;
	data32 <<= OCPR_Addr_Reg_shift;

	RTL_W32(MACOCP, data32);
	data16 = (u16)RTL_R32(MACOCP);

	return data16;
}

#define MDIO_WAIT_TIMEOUT   100
#define MDIO_LOCK														\
do {																	\
	u32 wait_cnt = 0;													\
																		\
	/* disable timer 2 */												\
	mac_ocp_write(0xE404,												\
		(mac_ocp_read(0xE404) & ~(BIT_12 | BIT_11 | BIT_8)) | BIT_12);	\
	/* wait MDIO channel is free */										\
	while (0 != (BIT_0 & mac_ocp_read(0xDE4E))) {						\
		wait_cnt++;														\
		udelay(1);														\
		if (wait_cnt > MDIO_WAIT_TIMEOUT)								\
			break;														\
	}																	\
	while (wait_cnt <= MDIO_WAIT_TIMEOUT) {								\
		/* enter driver mode */											\
		mac_ocp_write(0xDE42, mac_ocp_read(0xDE42) | BIT_0); 			\
		/* check if MDIO channel is still free */						\
		if (0 == (BIT_0 & mac_ocp_read(0xDE4E))) {						\
			/* lock successfully */										\
			break;														\
		} else {														\
			/* exit driver mode */										\
			mac_ocp_write(0xDE42, mac_ocp_read(0xDE42) & ~BIT_0);		\
			wait_cnt++;													\
			udelay(1);													\
		}																\
	}																	\
	if (wait_cnt > MDIO_WAIT_TIMEOUT) {									\
		/* enable timer 2 */											\
		mac_ocp_write(0xE404,											\
			(mac_ocp_read(0xE404) | BIT_12 | BIT_11 | BIT_8));			\
		printf("%s:%d: MDIO lock failed\n", __func__, __LINE__);		\
	}																	\
} while (0)

#define MDIO_UNLOCK														\
do {																	\
	/* exit driver mode */												\
	mac_ocp_write(0xDE42, mac_ocp_read(0xDE42) & ~BIT_0);				\
	/* enable timer 2 */												\
	mac_ocp_write(0xE404,												\
		(mac_ocp_read(0xE404) | BIT_12 | BIT_11 | BIT_8));				\
} while (0)

static void r8168_mdio_write(u32 RegAddr,
							 u32 value)
{
	/* mcfg == CFG_METHOD_25 == 24 */
	phys_addr_t ioaddr = MMIO_ADDR;
	int i;

	RTL_W32 (PHYAR, PHYAR_Write |
			(RegAddr & PHYAR_Reg_Mask) << PHYAR_Reg_shift |
			(value & PHYAR_Data_Mask));
	//printf("WPHY addr %x value %x \n",RegAddr,value);
	for (i = 0; i < 10; i++) {
		udelay(100);

		/* Check if the RTL8168 has completed writing to the specified MII register */
		if (!(RTL_R32(PHYAR) & PHYAR_Flag)) {
			udelay(20);
			break;
		}
	}

}

static u32 r8168_mdio_read(u32 RegAddr)
{
	/* mcfg == CFG_METHOD_25 == 24 */
	phys_addr_t ioaddr = MMIO_ADDR;
	int i, value = 0;

	RTL_W32(PHYAR,
			PHYAR_Read | (RegAddr & PHYAR_Reg_Mask) << PHYAR_Reg_shift);

	for (i = 0; i < 10; i++) {
		udelay(100);

		/* Check if the RTL8168 has completed retrieving data from the specified MII register */
		if (RTL_R32(PHYAR) & PHYAR_Flag) {
			value = RTL_R32(PHYAR) & PHYAR_Data_Mask;
			udelay(20);
			break;
		}
	}

	return value;
}

static int rtl8168_set_speed_xmii(u8 autoneg, u16 speed, u8 duplex, u32 adv)
{
	u16 giga_ctrl, anar;
	u16 bmcr = 0;
	int rc = -1;

	MDIO_LOCK;
	r8168_mdio_write(0x1f, 0x0000);

	if (autoneg == AUTONEG_ENABLE) {
		anar = r8168_mdio_read(MII_ADVERTISE);
		anar &= ~(ADVERTISE_10HALF | ADVERTISE_10FULL |
				  ADVERTISE_100HALF | ADVERTISE_100FULL);
		
		if (adv & ADVERTISED_10baseT_Half) {
			anar = anar | ADVERTISE_10HALF;
		}
		if (adv & ADVERTISED_10baseT_Full) {
			anar = anar | ADVERTISE_10FULL;
		}
		if (adv & ADVERTISED_100baseT_Half) {
			anar = anar | ADVERTISE_100HALF;
		}
		if (adv & ADVERTISED_100baseT_Full) {
			anar = anar | ADVERTISE_100FULL;
		}

		anar = anar | ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;

		giga_ctrl = r8168_mdio_read(MII_CTRL1000);
		giga_ctrl &= ~(ADVERTISE_1000FULL | ADVERTISE_1000HALF);

		bmcr = BMCR_ANENABLE | BMCR_ANRESTART;
	}
	else {
		giga_ctrl = 0;

		if (speed == SPEED_10) {
			bmcr = 0;
		}
		else if (speed == SPEED_100) {
			bmcr = BMCR_SPEED100;
		}
		else {
			goto out;
		}

		if (duplex == DUPLEX_FULL)
			bmcr = bmcr | BMCR_FULLDPLX;
	}

	r8168_mdio_write(MII_ADVERTISE, anar);
	r8168_mdio_write(MII_CTRL1000, giga_ctrl);
	r8168_mdio_write(MII_BMCR, bmcr);
	
	rc = 0;
	
out:
	MDIO_UNLOCK;
	return rc;
}

static void rtl_speed_down(void)
{
	u32 adv;
	int lpa;

	r8168_mdio_write(0x1f, 0x0000);
	lpa = r8168_mdio_read(MII_LPA);

	if (lpa & (LPA_10HALF | LPA_10FULL)) {
		adv = ADVERTISED_10baseT_Half | ADVERTISED_10baseT_Full;
#ifdef DEBUG
		printf("[DEBUG] ADVERTISED_10baseT_Half | ADVERTISED_10baseT_Full\n");
#endif
	}

	rtl8168_set_speed_xmii(AUTONEG_ENABLE, SPEED_1000, DUPLEX_FULL, adv);
}

static int do_ethspeed(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	uint speed;
	if (argc < 2)
		return CMD_RET_USAGE;
	else {
		speed = (uint) simple_strtoul(argv[1], NULL, 10);
		if( speed == 10 ) {
			printf(
				"Speed: 10Mb/s\n"
				"Duplex: Full\n"
			);
			rtl_speed_down();
		}
		else {
			return CMD_RET_USAGE;
		}
	}
	
	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	ethspeed,	2,	1,	do_ethspeed,
	"switch ethernet speed (R8168)",
	"<ethSpeed>\n"
	"Parameters:\n"
	"ethSpeed : <10>\n"
	/* "ethSpeed : <10|100|1000>\n" */
);