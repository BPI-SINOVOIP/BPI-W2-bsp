/*
 * (C) Copyright 2000, 2001
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/*
 * Support for read and write access to EEPROM like memory devices. This
 * includes regular EEPROM as well as  FRAM (ferroelectic nonvolaile RAM).
 * FRAM devices read and write data at bus speed. In particular, there is no
 * write delay. Also, there is no limit imposed on the number of bytes that can
 * be transferred with a single read or write.
 *
 * Use the following configuration options to ensure no unneeded performance
 * degradation (typical for EEPROM) is incured for FRAM memory:
 *
 * #define CONFIG_SYS_I2C_FRAM
 * #undef CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS
 *
 */

#include <common.h>
#include <config.h>
#include <command.h>
#include <i2c.h>

extern void eeprom_init  (void);
extern int  eeprom_read  (unsigned dev_addr, unsigned offset,
			  uchar *buffer, unsigned cnt);
extern int  eeprom_write (unsigned dev_addr, unsigned offset,
			  uchar *buffer, unsigned cnt);
#if defined(CONFIG_SYS_EEPROM_WREN)
extern int eeprom_write_enable (unsigned dev_addr, int state);
#endif


#if defined(CONFIG_SYS_EEPROM_X40430)
	/* Maximum number of times to poll for acknowledge after write */
#define MAX_ACKNOWLEDGE_POLLS	10
#endif

/************************************************************************************************
*   EEPROM_SIZE:								 		*
*   24c00: 16, 24c01: 128, 24c02: 256, 24c04: 512, 24c08: 1024, 24c16: 2048	 		*
*   24c32: 4096, 24c64: 8192, 24c128: 16384, 24c256: 32768, 24c512: 65536, 	 		*
*												*
*   I2C_EEPROM_ADDR_LEN:									*
*   24c00, 24c01,24c02, 24c04, 24c08, 24c16 the address mode is 1 bytes,                        *
*   24c32, 24c64, 24c128, 24c256, 24c512, the address mode is 2 bytes                           *
*                                                                                               *
*   PAGE_WRITE_SIZE:										*
*   EEPROM supports page write mechanism, however, each eeprom type has different		*
*   page write size. User needs to read the eeprom spec and look for the page write 		*
*   size, or user will get trouble when write operation attempts to croos a page 		*
*   boundary. The following comment is from eeprom data sheet:					*
*  "Page write operations are limited to writing bytes within a single physical page,		*
*   regardless of the number of bytes actually being written. Physical page boundaries		*
*   start at addresses that are integer multiples of the page buffer size (or ‘page size’)	*
*   and end at addresses that are integer multiples of [page size - 1].				*
*   If a Page Write command attempts to write across a physical page boundary,			*
*   the result is that the data wraps around to the beginning of the current page		*
*   (overwriting data previously stored there), instead of being written to the next page,	*
*   as might be expected. It is, therefore, necessary for the application software to prevent	*
*   page write operations that would attempt to cross a page boundary."				*
*************************************************************************************************/
#define AT24C01		0
#define AT24C01A    1
#define AT24C02		2
#define AT24C04		3
#define AT24C08A	4
#define AT24C16A	5
#define AT24C32		6
#define AT24C64		7
#define AT24C128	8
#define AT24C256	9
#define AT24C512	10
/*new type eeprom type add here*/

#define EEPROM_SUPPORT_LIST 12 //when new eeprom type is added into eeprom_support, users need to modify this value

struct eeprom_data{
    unsigned int   EEPROM_SIZE;		//eeprom capacity
    unsigned short PAGE_WRITE_SIZE;	//write page mechanism, 0 if there is not such limitation
};

/*these data are from ATMEL EEPROM spec, it would need to be modified if any bugs*/
struct eeprom_data EEPROM[EEPROM_SUPPORT_LIST] ={
    {128,	4},			//AT24C01
    {128,   8},     	//AT24C01A
    {256,	8},			//AT24C02
    {512,	16},		//AT24C04
    {1024,	16},		//AT24C08A
    {2048,	16},		//AT24C16A, AT24C164
    {4096,	32},		//AT24C32
    {8192,	32},		//AT24C64
    {16384,	64},		//AT24C128
    {32768,	64},		//AT24C256
    {65536,	128},		//AT24C512
    {0,0/*New support EEPROM will pe defined from here*/}
};

//***************************************   User Define Area   ************************************************
#define EEPROM_TYPE	AT24C16A	//chosing your eeprom manually
#define I2C_CHANNEL	5		//In Realtek design, eeprom using i2c 5, eeprom device address is 0x50
#define EEPROM_ADDR	0x50
//*************************************************************************************************************

/*---------------If new support eeproms are added, the following if condition should be modified ----------------*/
#if EEPROM_TYPE >= AT24C32             //new 2 bytes address mode eeprom should be put behind AT24C32
	#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN 2
#else
	#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN 1
#endif

#if EEPROM_TYPE == AT24C01
	#define BUFFER_SIZE 4
#elif EEPROM_TYPE > AT24C01 && EEPROM_TYPE < AT24C04
	#define BUFFER_SIZE 8
#else
	#define BUFFER_SIZE 16
#endif
/*-----------------------------------------------------------------------------------------------------------------*/


/* ------------------------------------------------------------------------- */

#if defined(CONFIG_CMD_EEPROM)
static int do_eeprom(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	const char *const fmt =
		"\nEEPROM @0x%lX %s: addr %08lx  off %04lx  count %ld ... ";

#if defined(CONFIG_SYS_I2C_MULTI_EEPROMS)
	if (argc == 6) {
		ulong dev_addr = simple_strtoul (argv[2], NULL, 16);
		ulong addr = simple_strtoul (argv[3], NULL, 16);
		ulong off  = simple_strtoul (argv[4], NULL, 16);
		ulong cnt  = simple_strtoul (argv[5], NULL, 16);
#else
	if (argc == 5) {
		ulong dev_addr = CONFIG_SYS_DEF_EEPROM_ADDR;
		ulong addr = simple_strtoul (argv[2], NULL, 16);
		ulong off  = simple_strtoul (argv[3], NULL, 16);
		ulong cnt  = simple_strtoul (argv[4], NULL, 16);
#endif /* CONFIG_SYS_I2C_MULTI_EEPROMS */

# if !defined(CONFIG_SPI) || defined(CONFIG_ENV_EEPROM_IS_ON_I2C)
		eeprom_init ();
# endif /* !CONFIG_SPI */

		if (strcmp (argv[1], "read") == 0) {
			int rcode;

			printf (fmt, dev_addr, argv[1], addr, off, cnt);

			rcode = eeprom_read (dev_addr, off, (uchar *) addr, cnt);

			puts ("done\n");
			return rcode;
		} else if (strcmp (argv[1], "write") == 0) {
			int rcode;

			printf (fmt, dev_addr, argv[1], addr, off, cnt);

			rcode = eeprom_write (dev_addr, off, (uchar *) addr, cnt);

			puts ("done\n");
			return rcode;
		}
	}

	return CMD_RET_USAGE;
}
#endif

/*-----------------------------------------------------------------------
 *
 * for CONFIG_SYS_I2C_EEPROM_ADDR_LEN == 2 (16-bit EEPROM address) offset is
 *   0x000nxxxx for EEPROM address selectors at n, offset xxxx in EEPROM.
 *
 * for CONFIG_SYS_I2C_EEPROM_ADDR_LEN == 1 (8-bit EEPROM page address) offset is
 *   0x00000nxx for EEPROM address selectors and page number at n.
 */

#if !defined(CONFIG_SPI) || defined(CONFIG_ENV_EEPROM_IS_ON_I2C)
#if !defined(CONFIG_SYS_I2C_EEPROM_ADDR_LEN) || CONFIG_SYS_I2C_EEPROM_ADDR_LEN < 1 || CONFIG_SYS_I2C_EEPROM_ADDR_LEN > 2
#error CONFIG_SYS_I2C_EEPROM_ADDR_LEN must be 1 or 2
#endif
#endif

int eeprom_read (unsigned dev_addr, unsigned offset, uchar *buffer, unsigned cnt)
{
	unsigned end = offset + cnt;
	unsigned blk_off;
	int rcode = 0;

	/* Read data until done or would cross a page boundary.
	 * We must write the address again when changing pages
	 * because the next page may be in a different device.
	 */
	while (offset < end) {
		unsigned alen, len;
#if !defined(CONFIG_SYS_I2C_FRAM)
		unsigned maxlen;
#endif

#if CONFIG_SYS_I2C_EEPROM_ADDR_LEN == 1 && !defined(CONFIG_SPI_X)
		uchar addr[2];

		blk_off = offset & 0xFF;	/* block offset */

		addr[0] = offset >> 8;		/* block number */
		addr[1] = blk_off;		/* block offset */
		alen	= 2;
#else
		uchar addr[3];

		blk_off = offset & 0xFF;	/* block offset */

		addr[0] = offset >> 16;		/* block number */
		addr[1] = offset >>  8;		/* upper address octet */
		addr[2] = blk_off;		/* lower address octet */
		alen	= 3;
#endif	/* CONFIG_SYS_I2C_EEPROM_ADDR_LEN, CONFIG_SPI_X */

		addr[0] |= dev_addr;		/* insert device address */

		len = end - offset;

		/*
		 * For a FRAM device there is no limit on the number of the
		 * bytes that can be ccessed with the single read or write
		 * operation.
		 */
#if !defined(CONFIG_SYS_I2C_FRAM)
		maxlen = 0x100 - blk_off;
		if (maxlen > I2C_RXTX_LEN)
			maxlen = I2C_RXTX_LEN;
		if (len > maxlen)
			len = maxlen;
#endif

#if defined(CONFIG_SPI) && !defined(CONFIG_ENV_EEPROM_IS_ON_I2C)
		spi_read (addr, alen, buffer, len);
#else
#if defined(CONFIG_SYS_I2C_EEPROM_BUS)
		i2c_set_bus_num(CONFIG_SYS_I2C_EEPROM_BUS);
#endif
		if (i2c_read(addr[0], offset, alen - 1, buffer, len))
			rcode = 1;
#endif
		buffer += len;
		offset += len;
	}

	return rcode;
}

/*-----------------------------------------------------------------------
 *
 * for CONFIG_SYS_I2C_EEPROM_ADDR_LEN == 2 (16-bit EEPROM address) offset is
 *   0x000nxxxx for EEPROM address selectors at n, offset xxxx in EEPROM.
 *
 * for CONFIG_SYS_I2C_EEPROM_ADDR_LEN == 1 (8-bit EEPROM page address) offset is
 *   0x00000nxx for EEPROM address selectors and page number at n.
 */

int eeprom_write (unsigned dev_addr, unsigned offset, uchar *buffer, unsigned cnt)
{
	unsigned end = offset + cnt;
	unsigned blk_off;
	int rcode = 0;

#if defined(CONFIG_SYS_EEPROM_X40430)
	uchar	contr_r_addr[2];
	uchar	addr_void[2];
	uchar	contr_reg[2];
	uchar	ctrl_reg_v;
	int	i;
#endif

#if defined(CONFIG_SYS_EEPROM_WREN)
	eeprom_write_enable (dev_addr,1);
#endif
	/* Write data until done or would cross a write page boundary.
	 * We must write the address again when changing pages
	 * because the address counter only increments within a page.
	 */

	while (offset < end) {
		unsigned alen, len;
#if !defined(CONFIG_SYS_I2C_FRAM)
		unsigned maxlen;
#endif

#if CONFIG_SYS_I2C_EEPROM_ADDR_LEN == 1 && !defined(CONFIG_SPI_X)
		uchar addr[2];

		blk_off = offset & 0xFF;	/* block offset */

		addr[0] = offset >> 8;		/* block number */
		addr[1] = blk_off;		/* block offset */
		alen	= 2;
#else
		uchar addr[3];

		blk_off = offset & 0xFF;	/* block offset */

		addr[0] = offset >> 16;		/* block number */
		addr[1] = offset >>  8;		/* upper address octet */
		addr[2] = blk_off;		/* lower address octet */
		alen	= 3;
#endif	/* CONFIG_SYS_I2C_EEPROM_ADDR_LEN, CONFIG_SPI_X */

		addr[0] |= dev_addr;		/* insert device address */

		len = end - offset;

		/*
		 * For a FRAM device there is no limit on the number of the
		 * bytes that can be accessed with the single read or write
		 * operation.
		 */
#if !defined(CONFIG_SYS_I2C_FRAM)

#if defined(CONFIG_SYS_EEPROM_PAGE_WRITE_BITS)

#define	EEPROM_PAGE_SIZE	(1 << CONFIG_SYS_EEPROM_PAGE_WRITE_BITS)
#define	EEPROM_PAGE_OFFSET(x)	((x) & (EEPROM_PAGE_SIZE - 1))

		maxlen = EEPROM_PAGE_SIZE - EEPROM_PAGE_OFFSET(blk_off);
#else
		maxlen = 0x100 - blk_off;
#endif
		if (maxlen > I2C_RXTX_LEN)
			maxlen = I2C_RXTX_LEN;

		if (len > maxlen)
			len = maxlen;
#endif

#if defined(CONFIG_SPI) && !defined(CONFIG_ENV_EEPROM_IS_ON_I2C)
		spi_write (addr, alen, buffer, len);
#else
#if defined(CONFIG_SYS_EEPROM_X40430)
		/* Get the value of the control register.
		 * Set current address (internal pointer in the x40430)
		 * to 0x1ff.
		 */
		contr_r_addr[0] = 9;
		contr_r_addr[1] = 0xff;
		addr_void[0]    = 0;
		addr_void[1]    = addr[1];
#ifdef CONFIG_SYS_I2C_EEPROM_ADDR
		contr_r_addr[0] |= CONFIG_SYS_I2C_EEPROM_ADDR;
		addr_void[0]    |= CONFIG_SYS_I2C_EEPROM_ADDR;
#endif
		contr_reg[0] = 0xff;
		if (i2c_read (contr_r_addr[0], contr_r_addr[1], 1, contr_reg, 1) != 0) {
			rcode = 1;
		}
		ctrl_reg_v = contr_reg[0];

		/* Are any of the eeprom blocks write protected?
		 */
		if (ctrl_reg_v & 0x18) {
			ctrl_reg_v &= ~0x18;   /* reset block protect bits  */
			ctrl_reg_v |=  0x02;   /* set write enable latch    */
			ctrl_reg_v &= ~0x04;   /* clear RWEL                */

			/* Set write enable latch.
			 */
			contr_reg[0] = 0x02;
			if (i2c_write (contr_r_addr[0], 0xff, 1, contr_reg, 1) != 0) {
				rcode = 1;
			}

			/* Set register write enable latch.
			 */
			contr_reg[0] = 0x06;
			if (i2c_write (contr_r_addr[0], 0xFF, 1, contr_reg, 1) != 0) {
				rcode = 1;
			}

			/* Modify ctrl register.
			 */
			contr_reg[0] = ctrl_reg_v;
			if (i2c_write (contr_r_addr[0], 0xFF, 1, contr_reg, 1) != 0) {
				rcode = 1;
			}

			/* The write (above) is an operation on NV memory.
			 * These can take some time (~5ms), and the device
			 * will not respond to further I2C messages till
			 * it's completed the write.
			 * So poll device for an I2C acknowledge.
			 * When we get one we know we can continue with other
			 * operations.
			 */
			contr_reg[0] = 0;
			for (i = 0; i < MAX_ACKNOWLEDGE_POLLS; i++) {
				if (i2c_read (addr_void[0], addr_void[1], 1, contr_reg, 1) == 0)
					break;	/* got ack */
#if defined(CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS)
				udelay(CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS * 1000);
#endif
			}
			if (i == MAX_ACKNOWLEDGE_POLLS) {
				puts ("EEPROM poll acknowledge failed\n");
				rcode = 1;
			}
		}

		/* Is the write enable latch on?.
		 */
		else if (!(ctrl_reg_v & 0x02)) {
			/* Set write enable latch.
			 */
			contr_reg[0] = 0x02;
			if (i2c_write (contr_r_addr[0], 0xFF, 1, contr_reg, 1) != 0) {
			       rcode = 1;
			}
		}
		/* Write is enabled ... now write eeprom value.
		 */
#endif
#if defined(CONFIG_SYS_I2C_EEPROM_BUS)
		i2c_set_bus_num(CONFIG_SYS_I2C_EEPROM_BUS);
#endif
		if (i2c_write(addr[0], offset, alen - 1, buffer, len))
			rcode = 1;

#endif
		buffer += len;
		offset += len;

#if defined(CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS)
		udelay(CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS * 1000);
#endif
	}
#if defined(CONFIG_SYS_EEPROM_WREN)
	eeprom_write_enable (dev_addr,0);
#endif
	return rcode;
}

#if !defined(CONFIG_SPI) || defined(CONFIG_ENV_EEPROM_IS_ON_I2C)
int
eeprom_probe (unsigned dev_addr, unsigned offset)
{
	unsigned char chip;

	/* Probe the chip address
	 */
#if CONFIG_SYS_I2C_EEPROM_ADDR_LEN == 1 && !defined(CONFIG_SPI_X)
	chip = offset >> 8;		/* block number */
#else
	chip = offset >> 16;		/* block number */
#endif	/* CONFIG_SYS_I2C_EEPROM_ADDR_LEN, CONFIG_SPI_X */

	chip |= dev_addr;		/* insert device address */

	return (i2c_probe (chip));
}
#endif

/*-----------------------------------------------------------------------
 * Set default values
 */
#ifndef	CONFIG_SYS_I2C_SPEED
#define	CONFIG_SYS_I2C_SPEED	50000
#endif

void eeprom_init  (void)
{

#if defined(CONFIG_SPI) && !defined(CONFIG_ENV_EEPROM_IS_ON_I2C)
	spi_init_f ();
#endif
#if defined(CONFIG_HARD_I2C) || defined(CONFIG_SYS_I2C_SOFT)
	i2c_init (CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE);
#endif
}

/*-----------------------------------------------------------------------
 */

/***************************************************/

#if defined(CONFIG_CMD_EEPROM)

#ifdef CONFIG_SYS_I2C_MULTI_EEPROMS
U_BOOT_CMD(
	eeprom,	6,	1,	do_eeprom,
	"EEPROM sub-system",
	"read  devaddr addr off cnt\n"
	"eeprom write devaddr addr off cnt\n"
	"       - read/write `cnt' bytes from `devaddr` EEPROM at offset `off'"
)
#else /* One EEPROM */
U_BOOT_CMD(
	eeprom,	5,	1,	do_eeprom,
	"EEPROM sub-system",
	"read  addr off cnt\n"
	"eeprom write addr off cnt\n"
	"       - read/write `cnt' bytes at EEPROM offset `off'"
)
#endif /* CONFIG_SYS_I2C_MULTI_EEPROMS */

#endif
