
/************************************************************************
 *
 *  crc32.c
 *
 *  Monitor command to compute CRC32 for a given memory area.
 *  Same algorithm and polynomial as UNIX' cksum is used.
 *
 *
 ************************************************************************/


/************************************************************************
 *  Include files
 ************************************************************************/
/*
#include <string.h>
#include <stdio.h>
#include <ctype.h>
*/

/************************************************************************
 *  Definitions
 ************************************************************************/

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/

static unsigned int crc_table[256];

/* Table of CRCs of all 8-bit messages. */
static int crc_table_computed = 0;

/************************************************************************
 *  Static function prototypes
 ************************************************************************/
static void make_crc_table(void);
static unsigned int Reflect(unsigned int ref, char ch);

/************************************************************************
 *                          crc32
 ************************************************************************/
unsigned int	
crc32(
    unsigned char  *p,
    int	   len,
    unsigned int *crc )
{
	int cnt = len;
	unsigned int value;

	if (!crc_table_computed)
		make_crc_table();

	value = 0xFFFFFFFF;
	while (cnt--) {
		value = (value >> 8) ^ crc_table[(value & 0xFF) ^ *p++];
	}
	
	*crc = value ^ 0xFFFFFFFF;

	return 0;
}

/* Make the table for a fast CRC. */

static void make_crc_table(void)
{

	//unsigned int c;
	unsigned int polynomial = 0x04C11DB7;
	int i, j;

	for (i = 0; i <= 0xFF; i++)
	{
		crc_table[i] = Reflect(i, 8) << 24;
		for (j = 0; j < 8; j++)
			crc_table[i] = (crc_table[i] << 1) ^ (crc_table[i] & (1 << 31) ? polynomial : 0);
		crc_table[i] = Reflect(crc_table[i],  32);
	}
	
	crc_table_computed = 1;
}

static unsigned int Reflect(unsigned int ref, char ch)
{
	unsigned int value = 0;
	int i;
	// Swap bit 0 for bit 7
	// bit 1 for bit 6, etc.
	for (i = 1; i < (ch + 1); i++)
	{
		if (ref & 1)
			value |= 1 << (ch - i);
		ref >>= 1;
	} 
	return value;
}

