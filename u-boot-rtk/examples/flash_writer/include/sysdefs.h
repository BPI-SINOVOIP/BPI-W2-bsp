
/************************************************************************
 *
 *  sysdefs.h
 *
 *  System definitions
 *
 * ######################################################################
 *
 * mips_start_of_legal_notice
 *
 * Copyright (c) 2003 MIPS Technologies, Inc. All rights reserved.
 *
 *
 * Unpublished rights (if any) reserved under the copyright laws of the
 * United States of America and other countries.
 *
 * This code is proprietary to MIPS Technologies, Inc. ("MIPS
 * Technologies"). Any copying, reproducing, modifying or use of this code
 * (in whole or in part) that is not expressly permitted in writing by MIPS
 * Technologies or an authorized third party is strictly prohibited. At a
 * minimum, this code is protected under unfair competition and copyright
 * laws. Violations thereof may result in criminal penalties and fines.
 *
 * MIPS Technologies reserves the right to change this code to improve
 * function, design or otherwise. MIPS Technologies does not assume any
 * liability arising out of the application or use of this code, or of any
 * error or omission in such code. Any warranties, whether express,
 * statutory, implied or otherwise, including but not limited to the implied
 * warranties of merchantability or fitness for a particular purpose, are
 * excluded. Except as expressly provided in any written license agreement
 * from MIPS Technologies or an authorized third party, the furnishing of
 * this code does not give recipient any license to any intellectual
 * property rights, including any patent rights, that cover this code.
 *
 * This code shall not be exported or transferred for the purpose of
 * reexporting in violation of any U.S. or non-U.S. regulation, treaty,
 * Executive Order, law, statute, amendment or supplement thereto.
 *
 * This code constitutes one or more of the following: commercial computer
 * software, commercial computer software documentation or other commercial
 * items. If the user of this code, or any related documentation of any
 * kind, including related technical data or manuals, is an agency,
 * department, or other entity of the United States government
 * ("Government"), the use, duplication, reproduction, release,
 * modification, disclosure, or transfer of this code, or any related
 * documentation of any kind, is restricted in accordance with Federal
 * Acquisition Regulation 12.212 for civilian agencies and Defense Federal
 * Acquisition Regulation Supplement 227.7202 for military agencies. The use
 * of this code by the Government is further restricted in accordance with
 * the terms of the license agreement(s) and/or applicable contract terms
 * and conditions covering this code from MIPS Technologies or an authorized
 * third party.
 *
 *
 * mips_end_of_legal_notice
 *
 *
 ************************************************************************/


#ifndef SYSDEFS_H
#define SYSDEFS_H


/************************************************************************
 *  Include files
 ************************************************************************/
#include <project_config_f.h>
#include <dvrboot_inc/io.h>

/************************************************************************
 *  Definitions
*************************************************************************/
#ifdef __ghs__
#define _GHS_
#endif

#ifdef _ASSEMBLER_

/******** ASSEMBLER SPECIFIC DEFINITIONS ********/

#ifdef  __ghs__
#define ALIGN(x) .##align (1 << (x))
#else
#define ALIGN(x) .##align (x)
#endif

#ifdef __ghs__
#define SET_MIPS3()
#define SET_MIPS0()
#define SET_PUSH()
#define SET_POP()
#else
#define SET_MIPS3() .##set mips3
#define SET_MIPS0() .##set mips0
#define SET_PUSH()  .##set push
#define SET_POP()   .##set pop
#endif

/*  Different assemblers have different requirements for how to
 *  indicate that the next section is bss :
 *
 *  Some use :   .bss
 *  Others use : .section bss
 *
 *  We select which to use based on _BSS_OLD_, which may be defined
 *  in makefile.
 */
#ifdef _BSS_OLD_
#define BSS	.##section bss
#else
#define BSS	.##bss
#endif

#define SWAPEND32( src, tmp0, tmp1 )\
		and	tmp0, src, 0xff;\
		srl	src,  8;\
		sll	tmp0, 8;\
		and	tmp1, src, 0xff;\
		or	tmp0, tmp1;\
		srl	src,  8;\
		sll	tmp0, 8;\
		and	tmp1, src, 0xff;\
		or	tmp0, tmp1;\
		srl	src,  8;\
		sll	tmp0, 8;\
		or	src,  tmp0


#define LEAF(name)\
  		.##text;\
  		.##globl	name;\
  		.##ent	name;\
name:


#define SLEAF(name)\
  		.##text;\
  		.##ent	name;\
name:


#ifdef __ghs__
#define END(name)\
  		.##end	name
#else
#define END(name)\
  		.##size name,.-name;\
  		.##end	name
#endif


#define EXTERN(name)

# else /* not assembler */


/******** C specific definitions ********/

#define SWAPEND32(d)    ((BYTE(d,0) << 24) |\
		         (BYTE(d,1) << 16) |\
		         (BYTE(d,2) << 8)  |\
		         (BYTE(d,3) << 0))




#define SWAPEND64(d)    ((BYTE(d,0) << 56) |\
		         (BYTE(d,1) << 48) |\
		         (BYTE(d,2) << 40)  |\
		         (BYTE(d,3) << 32)  |\
			 (BYTE(d,4) << 24) |\
		         (BYTE(d,5) << 16) |\
		         (BYTE(d,6) << 8)  |\
		         (BYTE(d,7) << 0))

typedef unsigned char		UINT8;
typedef signed char		INT8;
typedef unsigned short		UINT16;
typedef signed short		INT16;
typedef unsigned int		UINT32;
typedef signed int		INT32;
typedef unsigned long long	UINT64;
typedef signed long long	INT64;
typedef UINT8			bool;


#if 1

/* bsd */
typedef unsigned char		u_char;
typedef unsigned short		u_short;
typedef unsigned int		u_int;
typedef unsigned long		u_long;

/* sysv */
typedef unsigned char		unchar;
typedef unsigned short		ushort;
typedef unsigned int		uint;
typedef unsigned long		ulong;

typedef INT8		__s8;
typedef UINT8		__u8;

typedef INT16		__s16;
typedef UINT16		__u16;

typedef INT32		__s32;
typedef UINT32		__u32;

typedef UINT64		__u64;

typedef	__u8		u_int8_t;
typedef	__s8		int8_t;
typedef	__u16		u_int16_t;
typedef	__s16		int16_t;
typedef	__u32		u_int32_t;
typedef	__s32		int32_t;

#define u8		__u8
#define u16		__u16
#define u32		__u32
#define u64		__u64

#ifndef _SIZE_T_
#define _SIZE_T_
#ifdef __ghs__
   typedef unsigned int size_t;
#else
   typedef unsigned long size_t;
#endif
#endif

#endif

#endif /* #ifdef _ASSEMBLER_ */


/******** DEFINITIONS FOR BOTH ASSEMBLER AND C ********/
#if 1
#define ARRAY_COUNT(x)		(sizeof(x) / sizeof((x)[0]))

#define FALSE		          0
#define TRUE			  (!FALSE)

#define NULL		          ((void *)0)
#define MIN(x,y)		  ((x) < (y) ? (x) : (y))
#define MAX(x,y)      		  ((x) > (y) ? (x) : (y))

#define INCWRAP( ptr, size )      (ptr) = ((ptr)+1) % (size)
#define DECWRAP( ptr, size )      (ptr) = (((ptr) == 0) ? ((size) - 1) : ((ptr) - 1))

#define MAXUINT(w)	(\
		((w) == sizeof(UINT8))  ? 0xFFU :\
		((w) == sizeof(UINT16)) ? 0xFFFFU :\
		((w) == sizeof(UINT32)) ? 0xFFFFFFFFU : 0\
		        )

#define MAXINT(w)	(\
		((w) == sizeof(INT8))  ? 0x7F :\
		((w) == sizeof(INT16)) ? 0x7FFF :\
		((w) == sizeof(INT32)) ? 0x7FFFFFFF : 0\
		        )

#define MSK(n)			  ((1 << (n)) - 1)


/* Most/Least significant 32 bit from 64 bit double word */
#define HI32(data64)		  ((UINT32)(data64 >> 32))
#define LO32(data64)		  ((UINT32)(data64 & 0xFFFFFFFF))
#endif
#define REG8( addr )		  (*(volatile UINT8 *) (addr))
#define REG16( addr )		  (*(volatile UINT16 *)(addr))
#define REG32( addr )		  (*(volatile UINT32 *)(addr))
#define REG64( addr )		  (*(volatile UINT64 *)(addr))


/* Register field mapping */
#define REGFIELD(reg, rfld)	  (((reg) & rfld##_MSK) >> rfld##_SHF)

/* absolute register address, access 					*/
#define	REGA(addr)		  REG32(addr)

/* physical register address, access: base address + offsett		*/
#define	REGP(base,phys)	REG32( (UINT32)(base) + (phys) )

/* relative register address, access: base address + offsett		*/
#define REG(base,offs)  REG32( (UINT32)(base) + offs##_##OFS )

/**************************************
 * Macroes not used by YAMON any more
 * (kept for backwards compatibility)
 */
/* register read field							*/
#define	REGARD(addr,fld)	((REGA(addr) & addr##_##fld##_##MSK) 	\
			 >> addr##_##fld##_##SHF)

/* register write numeric field value					*/
#define	REGAWRI(addr,fld,intval) ((REGA(addr) & ~(addr##_##fld##_##MSK))\
				 | ((intval) << addr##_##fld##_##SHF))

/* register write enumerated field value				*/
#define	REGAWRE(addr,fld,enumval) ((REGA(addr) & ~(addr##_##fld##_##MSK))\
			| ((addr##_##fld##_##enumval) << addr##_##fld##_##SHF))


/* Examples:
 *
 *	exccode = REGARD(CPU_CAUSE,EXC);
 *
 *	REGA(SDR_CONTROL) = REGAWRI(OSG_CONTROL,TMO,17)
 *			 | REGAWRE(OSG_CONTROL,DTYPE,PC1);
 */


/* register read field							*/
#define	REGRD(base,offs,fld) ((REG(base,offs) & offs##_##fld##_##MSK) 	\
			 >> offs##_##fld##_##SHF)

/* register write numeric field value					*/
#define	REGWRI(base,offs,fld,intval)((REG(base,offs)& ~(offs##_##fld##_##MSK))\
                                 | (((intval) << offs##_##fld##_##SHF) & offs##_##fld##_##MSK))

/* register write enumerated field value				*/
#define	REGWRE(base,offs,fld,enumval)((REG(base,offs) & ~(offs##_##fld##_##MSK))\
				| ((offs##_##fld##_##enumval) << offs##_##fld##_##SHF))


/* physical register read field							*/
#define	REGPRD(base,phys,fld) ((REGP(base,phys) & phys##_##fld##_##MSK) 	\
			 >> phys##_##fld##_##SHF)

/* physical register write numeric field value					*/
#define	REGPWRI(base,phys,fld,intval)((REGP(base,phys)& ~(phys##_##fld##_##MSK))\
				 | ((intval) << phys##_##fld##_##SHF))

/* physical register write enumerated field value				*/
#define	REGPWRE(base,phys,fld,enumval)((REGP(base,phys) & ~(phys##_##fld##_##MSK))\
				| ((phys##_##fld##_##enumval) << phys##_##fld##_##SHF))
/*
 * End of macroes not used by YAMON any more
 *********************************************/

/* Endian related macros */

#define SWAP_BYTEADDR32( addr )   ( (addr) ^ 0x3 )
#define SWAP_UINT16ADDR32( addr ) ( (addr) ^ 0x2 )

#define BYTE(d,n)		  (((d) >> ((n) << 3)) & 0xFF)

/* Set byte address to little endian format */
#ifdef EL
#define SWAP_BYTEADDR_EL(addr) 	  addr
#else
#define SWAP_BYTEADDR_EL(addr)    SWAP_BYTEADDR32( addr )
#endif

/* Set byte address to big endian format */
#ifdef EB
#define SWAP_BYTEADDR_EB(addr) 	  addr
#else
#define SWAP_BYTEADDR_EB(addr)    SWAP_BYTEADDR32( addr )
#endif

/* Set UINT16 address to little endian format */
#ifdef EL
#define SWAP_UINT16ADDR_EL(addr)  addr
#else
#define SWAP_UINT16ADDR_EL(addr)  SWAP_UINT16ADDR32( addr )
#endif

/* Set UINT16 address to big endian format */
#ifdef EB
#define SWAP_UINT16ADDR_EB(addr)  addr
#else
#define SWAP_UINT16ADDR_EB(addr)  SWAP_UINT16ADDR32( addr )
#endif

#ifdef EL
#define REGW32LE(addr, data)      REG32(addr) = (data)
#define REGR32LE(addr, data)      (data)      = REG32(addr)
#else
#define REGW32LE(addr, data)      REG32(addr) = SWAPEND32(data)
#define REGR32LE(addr, data)      (data)      = REG32(addr), (data) = SWAPEND32(data)
#endif
#if 0
/* Set of 'LE'-macros, convert by BE: */
#ifdef EL
#define CPU_TO_LE32( value ) (value)
#define LE32_TO_CPU( value ) (value)
#define CPU_TO_LE16( value ) (value)
#define LE16_TO_CPU( value ) (value)
#else
#define CPU_TO_LE32( value ) ( (                ((UINT32)value)  << 24) |   \
                               ((0x0000FF00UL & ((UINT32)value)) <<  8) |   \
                               ((0x00FF0000UL & ((UINT32)value)) >>  8) |   \
                               (                ((UINT32)value)  >> 24)   )
#define LE32_TO_CPU( value ) CPU_TO_LE32( value )
#define CPU_TO_LE16( value ) ( ((UINT16)(((UINT16)value)  << 8)) |   \
                               ((UINT16)(((UINT16)value)  >> 8))   )
#define LE16_TO_CPU( value ) CPU_TO_LE16( value )
#endif

#define cpu_to_le32	CPU_TO_LE32
#define le32_to_cpu	LE32_TO_CPU
#define cpu_to_le16	CPU_TO_LE16
#define le16_to_cpu	LE16_TO_CPU
#define __constant_cpu_to_le32	CPU_TO_LE32
#define le32_to_cpup(x)	LE32_TO_CPU(*(x))
#define le16_to_cpup(x)	LE16_TO_CPU(*(x))

/* Set of 'BE'-macros, convert by LE: */
#ifdef EB
#define CPU_TO_BE32( value ) (value)
#define BE32_TO_CPU( value ) (value)

#define CPU_TO_BE16( value ) (value)
#define BE16_TO_CPU( value ) (value)
#else
#define CPU_TO_BE32( value ) ( (                ((UINT32)value)  << 24) |   \
                               ((0x0000FF00UL & ((UINT32)value)) <<  8) |   \
                               ((0x00FF0000UL & ((UINT32)value)) >>  8) |   \
                               (                ((UINT32)value)  >> 24)   )
#define BE32_TO_CPU( value ) CPU_TO_BE32( value )

#define CPU_TO_BE16( value ) ( ((UINT16)(((UINT16)value)  << 8)) |   \
                               ((UINT16)(((UINT16)value)  >> 8))   )
#define BE16_TO_CPU( value ) CPU_TO_BE16( value )
#endif
#endif

/* Standard ports */
#define PORT_TTY0	 0
#define PORT_TTY1	 1
#define PORT_NET	 2
#define PORT_NET2        3
#define PORT_CDROM       4
#define PORT_FLASH       5
#define PORT_HDD         6
#ifdef ENABLE_CONSOLE_SWITCH
  # define DEFAULT_PORT	 default_port
#else /* ENABLE_CONSOLE_SWITCH */
  # define DEFAULT_PORT	 PORT_TTY0
#endif /* ENABLE_CONSOLE_SWITCH */
#define DEBUG_PORT	 PORT_TTY0
#define DEFAULT_GDB_PORT PORT_TTY1

/* Env. variable for default serial port used for load */
#if defined(Board_Product_pvrbox)
  #define DEFAULT_BOOTPORT_ENV   "hd"
#else
  #define DEFAULT_BOOTPORT_ENV   "flash"
#endif

/* Control characters */
#define CTRL_A          ('A'-0x40)
#define CTRL_B          ('B'-0x40)
#define CTRL_C          ('C'-0x40)
#define CTRL_D          ('D'-0x40)
#define CTRL_E          ('E'-0x40)
#define CTRL_F          ('F'-0x40)
#define CTRL_H          ('H'-0x40)
#define CTRL_K          ('K'-0x40)
#define CTRL_N          ('N'-0x40)
#define CTRL_P          ('P'-0x40)
#define CTRL_U          ('U'-0x40)
#define DEL             0x7F
#define TAB             0x09
#define CR              0x0D
#define LF              0x0A
#define ESC             0x1B
#define SP              0x20
#define CSI             0x9B
#define KEY_Q           0x71
#define EOF_SREC        -2
#define UART_ERROR      -1


/* DEF2STR(x) converts #define symbol to string */
#define DEF2STR1(x) #x
#define DEF2STR(x)  DEF2STR1(x)
#define HW_SEMAPHORE_ADDRESS    0x1801a000



#define MARS_REV_A	0x00a0      //added by cylee
#define MARS_REV_B	0x00b0      //added by cylee

//#define rtd_inl(addr)		REG32(addr)
//#define rtd_outl(addr, val)	(REG32(addr) = (u32)val)

//#define udelay(s)		sys_wait_us(s)

#endif /* #ifndef SYSDEFS_H */

