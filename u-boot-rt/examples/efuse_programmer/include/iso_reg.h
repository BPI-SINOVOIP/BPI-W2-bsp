/************************************************************************
 *
 *  iso_reg.h
 *
 *  Defines for Phoenix ISO registers
 *
 ************************************************************************/

#ifndef ISO_REG_H
#define ISO_REG_H

/************************************************************************
 *  Definition
 ************************************************************************/
#define BOOTCODE_OPTION_ADDR        ISO_RESERVED_USER_1

#define ISO_REG_BASE			0x98007000	//see iso document

#define ISO_ISR				(ISO_REG_BASE + 0x0)
#define ISO_UMSK_ISR			(ISO_REG_BASE + 0x4)
#define ISO_UMSK_ISR_GP_ASSERT		(ISO_REG_BASE + 0x8)
#define ISO_UMSK_ISR_GP_DEASSERT	(ISO_REG_BASE + 0xc)
#define ISO_DBG				(ISO_REG_BASE + 0x24)
#define ISO_CHIP_INFO1			(ISO_REG_BASE + 0x28)
#define ISO_CTRL			(ISO_REG_BASE + 0x30)
#define ISO_SCPU_INT_EN			(ISO_REG_BASE + 0x40)
#define ISO_SOFT_RESET              (ISO_REG_BASE + 0x88)
#define ISO_CLOCK_ENABLE            (ISO_REG_BASE + 0x8c)

//iso pin mux
#define ISO_muxpad0			(ISO_REG_BASE + 0x310)
#define ISO_DUMMY1			(ISO_REG_BASE + 0x54)
#define ISO_DUMMY2			(ISO_REG_BASE + 0x58)
#define ISO_powercut_ETN                (ISO_REG_BASE + 0x5c)

#define ISO_RESERVED_USER_0		(ISO_REG_BASE + 0x64)
#define ISO_RESERVED_USER_1		(ISO_REG_BASE + 0x78)
#define ISO_RESERVED_USER_2		(ISO_REG_BASE + 0x7c)
#define ISO_RESERVED_USER_3		(ISO_REG_BASE + 0x1c)

/* GPIO */
#define ISO_GPDIR		(ISO_REG_BASE + 0x100)
#define ISO_GPDIR1		(ISO_REG_BASE + 0x104)
#define ISO_GPDATO		(ISO_REG_BASE + 0x108)
#define ISO_GPDATO1		(ISO_REG_BASE + 0x10C)
#define ISO_GPDATI		(ISO_REG_BASE + 0x110)
#define ISO_GPDATI1		(ISO_REG_BASE + 0x114)
#define ISO_GPIE		(ISO_REG_BASE + 0x118)
#define ISO_GPIE1		(ISO_REG_BASE + 0x11C)
#define ISO_GPDP		(ISO_REG_BASE + 0x120)
#define ISO_GPDP1		(ISO_REG_BASE + 0x124)
#define ISO_GPDEB		(ISO_REG_BASE + 0x128)

//cold rst
#define ISO_COLD_RST1   (ISO_REG_BASE + 0x610)
#define ISO_COLD_RST2   (ISO_REG_BASE + 0x614)
#define ISO_COLD_RST3   (ISO_REG_BASE + 0x660)
#define ISO_COLD_RST4   (ISO_REG_BASE + 0x664)
#define ISO_COLD_RST5   (ISO_REG_BASE + 0x668)
#define ISO_COLD_RST6   (ISO_REG_BASE + 0x66c)
#define ISO_COLD_RST7   (ISO_REG_BASE + 0x670)
#define ISO_COLD_RST8   (ISO_REG_BASE + 0x674)
#define ISO_COLD_RST9   (ISO_REG_BASE + 0x678)
#define ISO_COLD_RST10  (ISO_REG_BASE + 0x67c)

//iso
#define ISO_SB2_0		(ISO_REG_BASE + 0xf00)
#define ISO_DDR_IO_ctrl 	(ISO_REG_BASE + 0xf08)

#endif /* #ifndef ISO_REG_H */
