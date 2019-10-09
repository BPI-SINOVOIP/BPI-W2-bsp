/**************************************************************************/
/*                              EREGDEF.H                                 */
/**************************************************************************/
/*  Copyright(c) 1987-99 Embedded Performance, Inc.. All rights reserved  */
/*																		  */
/*  This software is the property of Embedded Performance, Inc (EPI)	  */
/*  which specifically  grants the user the right to modify, and use	  */
/*  this software provided this notice is not removed or altered.  All	  */
/*  other rights are reserved by EPI.									  */
/*                                                                        */
/**************************************************************************/
/*                                                                        */
/*  Embedded Performance, Inc. (EPI) makes no warranty  of any kind,      */
/*  express or implied, with regard to this software.  In no event shall  */
/*  EPI be liable for incidental or consequential damages in connection   */
/*  with or arising from  the furnishing,  performance, or use of this    */
/*  software.                                                             */
/*                                                                        */
/**************************************************************************/
/*																		  */
/*  This file defines various register names and chip addresses.          */
/*																		  */
/**************************************************************************/
/*																		  */
/*  Internal to EPI note:  This file is maintained in both scm and scmr4k */
/*  Please make any changes to both places.                               */
/*																		  */
/**************************************************************************/


#ifdef LANGUAGE_ASSEMBLY		/* set automatically by assembler */

#define zero $0	
#define AT	$at		/* assembler temp */
#define v0	$2		/* function return value0 */
#define v1	$3      /* function return value1 */
#define a0	$4		/* argument registers 0-3 */
#define a1	$5
#define a2	$6
#define a3	$7
#define t0	$8
#define t1	$9
#define t2	$10
#define t3	$11
#define t4	$12
#define t5	$13
#define t6	$14
#define t7	$15
#define s0	$16
#define s1	$17
#define s2	$18
#define s3	$19
#define s4	$20
#define s5	$21
#define s6	$22
#define s7	$23
#define t8	$24	
#define t9	$25
#define k0	$26		/* kernel temporary */
#define k1	$27		/* kernel reserved */
#define gp	$28		/* global data pointer */
#define sp	$29		/* stack pointer */
#define s8	$30		/* one more callee saved */
#define ra	$31		/* return address */

/*----- hardware registers names ---------------------*/
#define r0	$0	
#define r1	$at	
#define r2	$2	
#define r3	$3
#define r4	$4	
#define r5	$5
#define r6	$6
#define r7	$7
#define r8	$8	
#define r9	$9
#define r10	$10
#define r11	$11
#define r12	$12
#define r13	$13
#define r14	$14
#define r15	$15
#define r16	$16		
#define r17	$17
#define r18	$18
#define r19	$19
#define r20	$20
#define r21	$21
#define r22	$22
#define r23	$23
#define r24	$24		
#define r25	$25
#define r26	$26		
#define r27	$27
#define r28	$28		
#define r29	$29		
#define r30	$30		
#define r31	$31		


/*----- coprocessor 0 register names ----------------*/

/* generic names */
#define C0_0		$0
#define C0_1		$1
#define C0_2		$2
#define C0_3		$3
#define C0_4		$4
#define C0_5		$5
#define C0_6		$6
#define C0_7		$7
#define C0_8		$8
#define C0_9		$9
#define C0_10		$10
#define C0_11		$11
#define C0_12		$12
#define C0_13		$13
#define C0_14		$14
#define C0_15		$15
#define C0_16		$16
#define C0_17		$17
#define C0_18		$18
#define C0_19		$19
#define C0_20		$20
#define C0_21		$21
#define C0_22		$22
#define C0_23		$23
#define C0_24		$24
#define C0_25		$25
#define C0_26		$26
#define C0_27		$27
#define C0_28		$28
#define C0_29		$29
#define C0_30		$30
#define C0_31		$31

/* common register names of C0 */
#define C0_INDEX	$0
#define C0_INX		$0		/* TLB Index */
#define C0_IBASE	$0		/* Instruction Addr. Space Base	*/
#define	C0_IBOUND	$1		/* Instruction Addr. Space Bound	*/
#define C0_RANDOM	$1
#define C0_RAND		$1		/* TLB Random */
#define C0_ENTRYLO	$2
#define C0_TLBLO	$2		/* TLB EntryLo */
#define C0_DBASE	$2		/* Data Address Space Base		*/
#define	C0_ENTRYLO0	$2
#define C0_DBOUND	$3		/* Data Address Space Bound		*/
#define C0_ENTRYLO1	$3
#define C0_CONTEXT	$4
#define C0_CTEXT	$4		/* Context */
#define	C0_PAGEMASK	$5
#define	C0_WIRED	$6
#define C0_BADVADDR	$8
#define C0_COUNT	$9		/* R4K Timer	*/
#define C0_ENTRYHI	$10
#define C0_TLBHI	$10		/* TLB EntryHi */
#define C0_COMPARE	$11		/* R4K: acts as s timer	*/
#define C0_SR		$12
#define C0_STATUS	$12
#define C0_CAUSE	$13
#define C0_EPC		$14
#define C0_PRID		$15
#if	defined(R4K)||defined(r4k)
#define C0_CONFIG	$16		/* Device Configuration Information. Read ONLY	*/
#else
#define C0_CONFIG   $3		/* IDT 3081/71/41 specific registers */
#endif	/* R4K	*/
#define C0_CALG		$17		/* Cache Attributes	*/
#define C0_LLADDR	$17
#define C0_IWATCH	$18		/* R4K		*/
#define C0_DWATCH	$19
#define	C0_XCONTEXT	$20
#define C0_ECC		$26		/* Error Checking and Correcting	*/
#define C0_CACHEERR	$27		/* Cache parity error: read only	*/
#define C0_TAGLO	$28		/* Cache Addressing	*/
#define C0_TAGHI	$29
#define C0_ERROREPC	$30



/* IDT 3041 specific registers */
#define C0_BUSCTRL  $2
#define C0_COUNT	$9
#define C0_PORTSIZE $10
#define C0_COMPARE  $11



/*----- coprocessor 1 control register names ---------*/
#define C1_FCR0		$0		/* Implementation/Revision register */
#define FPA_IRR		$0
#define C1_FGR0		$0
#define C1_FGR1		$1
#define C1_FGR2		$2
#define C1_FGR3		$3
#define C1_FGR4		$4
#define C1_FGR5		$5
#define C1_FGR6		$6
#define C1_FGR7		$7
#define C1_FGR8		$8
#define C1_FGR9		$9
#define C1_FGR10	$10
#define C1_FGR11	$11
#define C1_FGR12	$12
#define C1_FGR13	$13
#define C1_FGR14	$14
#define C1_FGR15	$15
#define C1_FGR16	$16
#define C1_FGR17	$17
#define C1_FGR18	$18
#define C1_FGR19	$19
#define C1_FGR20	$20
#define C1_FGR21	$21
#define C1_FGR22	$22
#define C1_FGR23	$23
#define C1_FGR24	$24
#define C1_FGR25	$25
#define C1_FGR26	$26
#define C1_FGR27	$27
#define C1_FGR28	$28
#define C1_FGR29	$29
#define C1_FGR30	$30
#define C1_FGR31	$31
#define FPA_CSR		$31		/* Control/Status register */
#define C1_FCR31	$31


/*----- misc. assembly language defines -----------------------------*/
#define global globl


/*
** LEAF: start of a leaf routine define
*/
#define	LEAF(proc)	\
	.globl	proc;	\
	.ent	proc;	\
proc:;				\
	.frame	sp,0,ra

/*
** END: end of the procedure define
*/
#define	END(proc) .end	proc



#endif  /* LANGUAGE_ASSEMBLY */


/* Exception vector locations */

#if defined( R4K )||defined( r4k )
#define TLB_MISS_VECT 	0x80000000
#define XTLB_MISS_VECT 	0x80000080
#define CACHE_ERROR_VECT 0xA0000100
#define GENERAL_VECT	0x80000180
#define INTERRUPT_VECT	0x80000200
#else
#define UTLB_MISS_VECT 	0x80000000
#define GENERAL_VECT	0x80000080
#endif




/* Status Register */
#if defined( R4K ) || defined( r4k )
#define SR_CUMASK		0xf0000000	/* Coprocessor usable bits */
#define	SR_CU3			0x80000000	/* Coprocessor 3 usable */
#define SR_CU2			0x40000000	/* coprocessor 2 usable */
#define SR_CU1			0x20000000	/* Coprocessor 1 usable */
#define SR_CU0			0x10000000	/* Coprocessor 0 usable */
#define SR_FR			0x04000000	/* Enable Additional Floating-point Reg.*/
#define SR_RE			0x02000000	/* Reverse Endian Bit	*/
#define SR_DL			0x01000000	/* Data Cache Lock: refill into A disable*/
#define SR_IL			0x00800000	/* Instr. Cahe Lock: Refill to A disabled*/
#define SR_BEV			0x00400000	/* Bootstrap Exception Vector */
#define SR_SR			0x00100000	/* Soft Reset or NMI occurring bit	*/
#define SR_CH			0x00040000	/* Cache Hit(: 1)/Miss(: 0) */
#define SR_CE			0x00020000	/* ECC register set(: 1) */
#define SR_DE			0x00010000	/* Cache parity exception:dis/enabled(1/0)*/

#define SR_IMASK		0x0000ff00	/* Interrupt Mask */
#define SR_IMASK8		0x00000000	/* Interrupt Mask level=8 */
#define SR_IMASK7		0x00008000	/* Interrupt Mask level=7 */
#define SR_IMASK6		0x0000c000	/* Interrupt Mask level=6 */
#define SR_IMASK5		0x0000e000	/* Interrupt Mask level=5 */
#define SR_IMASK4		0x0000f000	/* Interrupt Mask level=4 */
#define SR_IMASK3		0x0000f800	/* Interrupt Mask level=3 */
#define SR_IMASK2		0x0000fc00	/* Interrupt Mask level=2 */
#define SR_IMASK1		0x0000fe00	/* Interrupt Mask level=1 */
#define SR_IMASK0		0x0000ff00	/* Interrupt Mask level=0 */

#define SR_IBIT8		0x00008000	/*  (Intr5) */
#define SR_IBIT7		0x00004000	/*  (Intr4) */
#define SR_IBIT6		0x00002000	/*  (Intr3) */
#define SR_IBIT5		0x00001000	/*  (Intr2) */
#define SR_IBIT4		0x00000800	/*  (Intr1) */
#define SR_IBIT3		0x00000400	/*  (Intr0) */
#define SR_IBIT2		0x00000200	/*  (Software Interrupt 1) */
#define SR_IBIT1		0x00000100	/*  (Software Interrupt 0) */

#define	SR_KX			0x00000080
#define SR_SX			0x00000040
#define SR_UX			0x00000020	/* 1=64 bit enabled; 0=32 bit enabled	*/
#define SR_UM			0x00000010	/* 0=Kernal Mode / 1=User Mode	*/
#define SR_KSU			0x00000018	/* Supervisor Mode.  4600/4700	*/
#define SR_ERL			0x00000004	/* Error Level: 0-normal/1-error	*/
#define SR_EXL			0x00000002	/* Exception Level: 0-normal/1-exception */
#define SR_IE			0x00000001	/* Interrupt Enable, current */
#else	/* end of R4K, start of R3K:	*/
#define SR_CUMASK		0xf0000000	/* Coprocessor usable bits */
#define	SR_CU3			0x80000000	/* Coprocessor 3 usable */
#define SR_CU2			0x40000000	/* coprocessor 2 usable */
#define SR_CU1			0x20000000	/* Coprocessor 1 usable */
#define SR_CU0			0x10000000	/* Coprocessor 0 usable */
#define SR_BEV			0x00400000	/* Bootstrap Exception Vector */
#define SR_TS			0x00200000	/* TLB shutdown */
#define SR_PE			0x00100000	/* Parity Error */
#define SR_CM			0x00080000	/* Cache Miss */
#define SR_PZ			0x00040000	/* Parity Zero */
#define SR_SWC			0x00020000	/* Swap Caches */
#define SR_ISC			0x00010000	/* Isolate Cache */

#define SR_IMASK		0x0000ff00	/* Interrupt Mask */
#define SR_IMASK8		0x00000000	/* Interrupt Mask level=8 */
#define SR_IMASK7		0x00008000	/* Interrupt Mask level=7 */
#define SR_IMASK6		0x0000c000	/* Interrupt Mask level=6 */
#define SR_IMASK5		0x0000e000	/* Interrupt Mask level=5 */
#define SR_IMASK4		0x0000f000	/* Interrupt Mask level=4 */
#define SR_IMASK3		0x0000f800	/* Interrupt Mask level=3 */
#define SR_IMASK2		0x0000fc00	/* Interrupt Mask level=2 */
#define SR_IMASK1		0x0000fe00	/* Interrupt Mask level=1 */
#define SR_IMASK0		0x0000ff00	/* Interrupt Mask level=0 */

#define SR_IBIT8		0x00008000	/*  (Intr5) */
#define SR_IBIT7		0x00004000	/*  (Intr4) */
#define SR_IBIT6		0x00002000	/*  (Intr3) */
#define SR_IBIT5		0x00001000	/*  (Intr2) */
#define SR_IBIT4		0x00000800	/*  (Intr1) */
#define SR_IBIT3		0x00000400	/*  (Intr0) */
#define SR_IBIT2		0x00000200	/*  (Software Interrupt 1) */
#define SR_IBIT1		0x00000100	/*  (Software Interrupt 0) */

#define SR_KUO			0x00000020	/* Kernel/User mode, old */
#define SR_IEO			0x00000010	/* Interrupt Enable, old */
#define SR_KUP			0x00000008	/* Kernel/User mode, previous */
#define SR_IEP			0x00000004	/* Interrupt Enable, previous */
#define SR_KUC			0x00000002	/* Kernel/User mode, current */
#define SR_IEC			0x00000001	/* Interrupt Enable, current */
#endif	/*	R3K	*/


/* C0_CALG	*/
/* MX: cache mode; CX: number of bits for MX to be left shifted	in C0_CALG	*/
#define C0_CALG_C0		0x0		/* 0x00000000 to 0x1FFFFFFF					*/
#define C0_CALG_C1		0x4		/* 0x20000000 to 0x3FFFFFFF					*/
#define C0_CALG_C2		0x8		/* 0x40000000 to 0x5FFFFFFF					*/
#define C0_CALG_C3		0xc		/* 0x60000000 to 0x7FFFFFFF					*/
#define C0_CALG_C4		0x10	/* 0x80000000 to 0x9FFFFFFF					*/
#define C0_CALG_C5		0x14	/* 0xA0000000 to 0xBFFFFFFF					*/
#define C0_CALG_C6		0x18	/* 0xC0000000 to 0xDFFFFFFF					*/
#define C0_CALG_C7		0x1c	/* 0xE0000000 to 0xFFFFFFFF					*/
#define C0_CALG_M0		0x0		/* Cached, write-through, no write-allocate */
#define C0_CALG_M1		0x1		/* Cached, write-through, write-allocate	*/
#define	C0_CALG_M2		0x2		/* Uncahced									*/
#define C0_CALG_M3		0x3		/* Cached, write-back, write-allocate		*/

/* BSO compatible */
#define ST_KUO			0x00000020	/* Kernel/User mode, old */
#define ST_IEO			0x00000010	/* Interrupt Enable, old */
#define ST_KUP			0x00000008	/* Kernel/User mode, previous */
#define ST_IEP			0x00000004	/* Interrupt Enable, previous */
#define ST_KUC			0x00000002	/* Kernel/User mode, current */
#define ST_IEC			0x00000001	/* Interrupt Enable, current */

/* Cause Register */
#define CAUSE_BD		0x80000000	/* Branch Delay */
#define CAUSE_CEMASK	0x30000000	/* Coprocessor Error */
#define CAUSE_CESHIFT	28			/* Right justify CE  */
#define CAUSE_DW		0x02000000	/* DWatch Reg. matced on a Watch except. */
#define CAUSE_IW		0x01000000	/* IWatch Reg. matced on a Watch except. */
#define CAUSE_IV		0x00800000	/* Exception Vec. (200) for interrupt.	*/
#define CAUSE_IPMASK	0x0000ff00	/* Interrupt Pending */
#define CAUSE_IPSHIFT	8			/* Right justify IP  */
#define CAUSE_IP8		0x00008000	/*  (Intr5) */
#define CAUSE_IP7		0x00004000	/*  (Intr4) */
#define CAUSE_IP6		0x00002000	/*  (Intr3) */
#define CAUSE_IP5		0x00001000	/*  (Intr2) */
#define CAUSE_IP4		0x00000800	/*  (Intr1) */
#define CAUSE_IP3		0x00000400	/*  (Intr0) */
#define CAUSE_SW2		0x00000200	/*  (Software Interrupt 1) */
#define CAUSE_SW1		0x00000100	/*  (Software Interrupt 0) */
#define CAUSE_EXCMASK	0x0000007c	/* Exception Code */
#define CAUSE_EXCSHIFT	2			/* Right justify EXC */

/* Exception Code */
#define EXC_INT			(0 << 2)	/* External interrupt */
#define EXC_MOD			(1 << 2)	/* TLB modification */
#define EXC_TLBL		(2 << 2)    /* TLB miss (Load or Ifetch) */
#define EXC_IBOUND		(2 << 2)	/* Replacing TLB in 4650	*/
#define EXC_TLBS		(3 << 2)	/* TLB miss (Save) */
#define EXC_DBOUND		(3 << 2)	/* Replacing TLB in 4650	*/
#define EXC_ADEL		(4 << 2)    /* Address error (Load or Ifetch) */
#define EXC_ADES		(5 << 2)	/* Address error (Store) */
#define EXC_IBE			(6 << 2)	/* Bus error (Ifetch) */
#define EXC_DBE			(7 << 2)	/* Bus error (data load or store) */
#define EXC_SYS			(8 << 2)	/* System call */
#define EXC_BP			(9 << 2)	/* Break point */
#define EXC_RI			(10 << 2)	/* Reserved instruction */
#define EXC_CPU			(11 << 2)	/* Coprocessor unusable */
#define EXC_OVF			(12 << 2)	/* Arithmetic overflow */
#define EXC_TR			(13 << 2)	/* Trap Exception		*/
#define	EXC_FPE			(15 << 2)	/* Floating-Point Exception	*/
#define EXC_WATCH		(23 << 23)	/* Watch Exception			*/

/* 3041 */
#define BUSCTRL_LOCK	0x80000000
#define BUSCTRL_MEM		0x0C000000
#define BUSCTRL_ED		0x03000000
#define BUSCTRL_IO		0x00C00000
#define BUSCTRL_BE16	0x00200000
#define BUSCTRL_BE		0x00080000
#define BUSCTRL_BTA		0x0000C000
#define BUSCTRL_DMA		0x00002000
#define BUSCTRL_TC		0x00001000
#define BUSCTRL_BR		0x00000800




/* Normalized Exception Codes */
#if defined( R3K )||defined( r3k )

#define EX_UNKNOWN_INTERRUPT		0
#define	EX_TLB_MODIFIED				1
#define	EX_TLB_MISS_LF				2
#define	EX_TLB_MISS_S				3
#define	EX_ADDRESS_ERROR_LF			4
#define	EX_ADDRESS_ERROR_S			5
#define	EX_BUS_ERROR_F				6
#define	EX_BUS_ERROR_LS				7
#define	EX_UNKNOWN_SYSCALL			8
#define	EX_UNKNOWN_BREAK			9
#define	EX_RESERVED_INSTRUCTION		10
#define	EX_COPROCESSOR_UNUSABLE		11
#define	EX_OVERFLOW					12
#define	EX_RESERVED13				13
#define	EX_RESERVED14				14
#define	EX_RESERVED15				15

#endif

#if defined( R4K )||defined( r4k )

#define EX_UNKNOWN_INTERRUPT		0
#define	EX_TLB_MODIFIED				1
#define	EX_TLB_MISS_LF				2
#define	EX_TLB_MISS_S				3
#define	EX_ADDRESS_ERROR_LF			4
#define	EX_ADDRESS_ERROR_S			5
#define	EX_BUS_ERROR_F				6
#define	EX_BUS_ERROR_LS				7
#define	EX_UNKNOWN_SYSCALL			8
#define	EX_UNKNOWN_BREAK			9
#define	EX_RESERVED_INSTRUCTION		10
#define	EX_COPROCESSOR_UNUSABLE		11
#define	EX_OVERFLOW					12
#define	EX_TRP						13
#define	EX_RESERVED14				14
#define	EX_FPE						15

#endif

/* CACHE opcode	*/
#if defined( R4K )||defined( r4k )

/* primary cache	*/
#define	I_INDEX_INVALIDATE			0x0
#define D_INDEX_WRITEBACK_INVALIDATE		0x1
#define	I_INDEX_LOAD_TAG			0x4
#define	D_INDEX_LOAD_TAG			0x5
#define	I_INDEX_STORE_TAG			0x8
#define	D_INDEX_STORE_TAG			0x9
#define D_CREATE_DIRTY_EXCLUSIVE	0xd
#define I_HIT_INVALIDATE			0x10
#define D_HIT_INVALIDATE			0x11
#define	I_FILL						0x14
#define	D_HIT_WRITEBACK_INVALIDATE	0x15
#define	I_HIT_WRITEBACK				0x18
#define	D_HIT_WRITEBACK				0x19

/* secondary cache	*/
#define S_INDEX_LOAD_TAG			0x7
#define S_INDEX_STORE_TAG			0xb
#define S_VALID_CLEAR				0x3
#define S_PAGE_INVALIDATE			0x17
#define S_CACHE_PAGE_SIZE			0x1000
#define S_CACHE_UNIT_SIZE			0x80000
#endif

#define HI_HALF(x)	((x) >> 16)
#define LO_HALF(x)	((x) & 0xffff)



/* Floating-Point Control register bits */
#define CSR_C			0x00800000
#define CSR_EXC			0x0003f000
#define CSR_EE			0x00020000
#define CSR_EV			0x00010000
#define CSR_EZ			0x00008000
#define CSR_EO			0x00004000
#define CSR_EU			0x00002000
#define CSR_EI			0x00001000
#define CSR_TV			0x00000800
#define CSR_TZ			0x00000400
#define CSR_TO			0x00000200
#define CSR_TU			0x00000100
#define CSR_TI			0x00000080
#define CSR_SV			0x00000040
#define CSR_SZ			0x00000020
#define CSR_SO			0x00000010
#define CSR_SU			0x00000008
#define CSR_SI			0x00000004
#define CSR_RM			0x00000003


/*
** PRID Values for various processors:
*/
#define PRID_3000		0x00000230 /* + 3051/52/81/71 */
#define PRID_3041		0x00000700
#define PRID_3041A		0x00000701
#define PRID_3041FX		0x00000710
#define PRID_36100		0x00000710

#define PRID_33000		0			/* 33050/33020 */
#define PRID_33300		0x00000A0A
#define PRID_33310		0x00000B0A

#define PRID_30100		0x00002100	/* Philips PR30100 (MR300 core) */

#define PRID_4640		0x00002200
#define PRID_4650		0x00002200
#define PRID_4000		0x00000400
#define PRID_4200		0x00000a00
#define PRID_4300		0x00000b00
#define PRID_4400		0x00000400	/* should 4400 = 4000 in that sense ? */
#define PRID_4600		0x00002000
#define PRID_4700		0x00002100

#define PRID_5000		0x00002300
#define PRID_52XX		0x00002800
#define PRID_5230		0x00002800
#define PRID_5260		0x00002800
#define PRID_7000		0x00002700

#define PRID_64475		0x00003000
#define PRID_64474		0x00003000
#define PRID_6447X		0x00003000

#define PRID_32364      0x00002600

#define PRID_MASK		0x0000ff00


/*-------------------------------------------------------------------
**
** Memory Mapped Registers - IDT 36100 Family
**
**-------------------------------------------------------------------
*/
#define TM41_PRESCALE_COUNT 0xffffe900
#define TM41_TIMER0_COUNT	0xffffe910
#define TM41_TIMER0_COMPARE	0xffffe914
#define TM41_TIMER0_PWM		0xffffe918
#define TM41_TIMER0_CONTROL	0xffffe91c
#define TM41_TIMER1_COUNT	0xffffe920
#define TM41_TIMER1_COMPARE	0xffffe924
#define TM41_TIMER1_CONTROL	0xffffe92c
#define TM41_TIMER2_COUNT	0xffffe930
#define TM41_TIMER2_COMPARE	0xffffe934
#define TM41_TIMER2_CONTROL	0xffffe93c

#define PIO41_GLOBAL_LOCK	0xffffea00
#define PIO41_DATA0			0xffffea10
#define PIO41_DC0			0xffffea10
#define PIO41_ESC0			0xffffea10
#define PIO41_DATA1			0xffffea10
#define PIO41_DC1			0xffffea10
#define PIO41_ESC1			0xffffea10

#define INT41_EICR			0xffffeb00
#define INT41_EIPR0			0xffffeb10
#define INT41_EIMR0			0xffffeb14
#define INT41_EIPR1			0xffffeb20
#define INT41_EIMR1			0xffffeb24
#define INT41_EIPR2			0xffffeb30
#define INT41_EIMR2			0xffffeb34

#define DBG41_TRACE_ADDR	0xffffe500
#define DBG41_TRACE_CONTROL	0xffffe504
#define DBG41_DEBUG_CONTROL	0xffffe508




/*-------------------------------------------------------------------
**
** Defines for Lexra's LX-4080 core
**
**-------------------------------------------------------------------
*/
//#if defined( LX4080 ) || defined( LX4080_CORE )
#define C0_CCTL		$20		/* Cache Control */
#define CCTL_DIvl	0x00000001	/* Invalidate Dcache */
#define CCTL_IIvl	0x00000002	/* Invalidate Icache/IRAM */
#define CCTL_ILk	0x00000004
#define CCTL_ILkM	0x00000008

/* Coprocessor 3 Control Registers */
#define C3_CON		$0

/* Coprocessor 3 General Registers */
#define C3_IWBASE	$0	/* IW Base Address [31:10] */
#define C3_IWTOP	$1	/* IW Top Address [15:4] */
#define C3_DWBASE	$4	/* DW Base Address [31:10] */
#define C3_DWTOP	$5	/* DW Top Address [15:4] */
#define C3_CNT0LO	$8	/* Counter 0 [31:0] */
#define C3_CNT0HI	$9	/* Counter 0 [47:32] */
#define C3_CNT1LO	$10	/* Counter 1 [31:0] */
#define C3_CNT1HI	$11	/* Counter 1 [47:32] */
#define C3_CNT2LO	$12	/* Counter 2 [31:0] */
#define C3_CNT2HI	$13	/* Counter 2 [47:32] */
#define C3_CNT3LO	$14	/* Counter 3 [31:0] */
#define C3_CNT3HI	$15	/* Counter 3 [47:32] */

//#endif





/*-------------------------------------------------------------------
**
** Defines for Philips MR300 CORE / PR30100 OCP processor
**
**-------------------------------------------------------------------
*/

/* MR300 core registers and bit definitions */
#define MR_CCR			$16
#define MR_CONFIG		$17

#define CCR_ICD			0x1
#define CCR_ICI			0x2
#define CCR_EII			0x4
#define CCR_ICL			0x8
#define CCR_DCD			0x10
#define CCR_DCI			0x20
#define CCR_EDI			0x40
#define CCR_DBD			0x80
#define CCR_DCL			0x100

#define CONFIG_IS		0x1
#define CONFIG_SP		0x2
#define CONFIG_ILS		0xC
#define CONFIG_DLS		0x30
#define CONFIG_RVE		0x100
#define CONFIG_VS		0x3000
#define CONFIG_SMIO		0xFF0000

/* R4650,R4700,R5000	*/
#define	CONFIG_IC_MASK	0xE00	/* indicates i-cache size	*/
#define CONFIG_DC_MASK	0x1C0	/* indicates d-cache size	*/
#define CONFIG_IB_MASK	0x20	/* indicates i-cache line size	*/
#define CONFIG_DB_MASK	0x10	/* indicates d-cache line szie	*/
#define	CONFIG_BE		0x8000	/* endianness				*/
#define	CONFIG_SS_MASK	0x00300000	/* secondary cache size	*/
#define	CONFIG_SE		0x1000	/* secondary cache enable	*/

/* OCP (PR30100) internal memory mapped registers internals */
#define	OCP_REG_BASE	0xb0c00000

/* register offsets from the base address */
#define OCP_MCR0		0
#define OCP_MCR1		4
#define OCP_MCR2		8
#define OCP_MCR3		0xc
#define OCP_IO_DIR		0xa0
#define OCP_IO_DATA_OUT 0xac

#define	TB_CONF_REG		0xbe000080



/*-------------------------------------------------------------------
**  CPU sub groups (e.g. chip makers) (Used by osboot and rss)
**  BIT Field
**------------------------------------------------------------------- 
*/
#define R3000_CORE		1		/* R3000/R3010 */
#define IDT_R3000_CORE	2		/* IDT 3051/52/81/71/41/41fx */
								/* Philips MR300 core */
#define LR33000_CORE	3		/* LR33000/33050/33020 */
#define R4000_CORE		4		/* R4000 */
#define LX4080_CORE		5		/* Lexra 4080  */
#define IDT32_CORE		6		/* IDT MIPS32 core  */


