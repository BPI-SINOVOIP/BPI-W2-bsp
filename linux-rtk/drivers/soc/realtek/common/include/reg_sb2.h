/*
 * reg_sb2.h - bus debug driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#ifndef _REG_SB2_H_INCLUDED_
#define _REG_SB2_H_INCLUDED_

#define SB2_OFFSET						0x0001A000

#define	CHIP_ID							0x00000200
#define CHIP_REV						0x00000204

#define RBUS_SB2_BASE_PHYS		(RBUS_BASE_PHYS + SB2_OFFSET)
#define RBUS_SB2_PHYS(pa)		(RBUS_BASE_PHYS + SB2_OFFSET + pa)

#define SB2_IO_ADDR(pa)		(IOMEM(RBUS_BASE_VIRT) + SB2_OFFSET + pa)

#define get_cpu_id()		readl(SB2_IO_ADDR(CHIP_ID))
#define get_cpu_revision()	readl(SB2_IO_ADDR(CHIP_REV))

#define is_revinfo_0			(get_cpu_revision()==0x00000000)
#define is_revinfo_1			(get_cpu_revision()==0x00010000)
#define is_revinfo_2			(get_cpu_revision()==0x00020000)

#define SB2_INV_INTEN		(iobase + 0x004)
#define SB2_INV_INTSTAT		(iobase + 0x008)
#define SB2_INV_ADDR		(iobase + 0x00c)
#define SB2_DEBUG_REG		(iobase + 0x010)

#define SWCIVAIRQ_EN		(1<<6)
#define ACIVAIRQ_EN 		(1<<3)
#define SCIVAIRQ_EN             (1<<1)

#define SWCIVA_INT		(1<<4)
#define ACIVA_INT		(1<<3)
#define SCIVA_INT		(1<<1)

#define WRITE_DATA_1 		(1<<0)
#define WRITE_DATA_0 		(0<<0)




#define SB2_DBG_START_REG0	(iobase + 0x458)
#define SB2_DBG_START_REG1	(iobase + 0x45c)
#define SB2_DBG_START_REG2	(iobase + 0x460)
#define SB2_DBG_START_REG3	(iobase + 0x464)
#define SB2_DBG_START_REG4	(iobase + 0x468)
#define SB2_DBG_START_REG5	(iobase + 0x46c)
#define SB2_DBG_START_REG6	(iobase + 0x470)
#define SB2_DBG_START_REG7	(iobase + 0x474)

#define SB2_DBG_END_REG0	(iobase + 0x478)
#define SB2_DBG_END_REG1	(iobase + 0x47c)
#define SB2_DBG_END_REG2	(iobase + 0x480)
#define SB2_DBG_END_REG3	(iobase + 0x484)
#define SB2_DBG_END_REG4	(iobase + 0x488)
#define SB2_DBG_END_REG5	(iobase + 0x48c)
#define SB2_DBG_END_REG6	(iobase + 0x490)
#define SB2_DBG_END_REG7	(iobase + 0x494)

#define SB2_DBG_CTRL_REG0	(iobase + 0x498)
#define SB2_DBG_CTRL_REG1	(iobase + 0x49c)
#define SB2_DBG_CTRL_REG2	(iobase + 0x4a0)
#define SB2_DBG_CTRL_REG3	(iobase + 0x4a4)
#define SB2_DBG_CTRL_REG4	(iobase + 0x4a8)
#define SB2_DBG_CTRL_REG5	(iobase + 0x4ac)
#define SB2_DBG_CTRL_REG6	(iobase + 0x4b0)
#define SB2_DBG_CTRL_REG7	(iobase + 0x4b4)
#define SB2_DBG_ADDR_AUDIO	(iobase + 0x4b8)
#define SB2_DBG_ADDR_SYSTEM (iobase + 0x4c0)
#define SB2_DBG_ADDR1		(iobase + 0x4c8)
#define SB2_DBG_INT			(iobase + 0x4E0)

#define SB2_DBG_MONITOR_DATA	((1<<4)|(1<<2))
#define SB2_DBG_MONITOR_INST	((1<<4)|(1<<3))
#define SB2_DBG_MONITOR_READ	((1<<7)|(1<<5))
#define SB2_DBG_MONITOR_WRITE	((1<<7)|(1<<6))

//SB2_DBG_INT
#define SB2_ACPU_INT_EN			(1<<9)
#define SB2_SCPU_INT_EN			(1<<7)
#define SB2_ACPU_NEG_INT_EN		(1<<3)
#define SB2_SCPU_NEG_INT_EN		(1<<1)

#endif
