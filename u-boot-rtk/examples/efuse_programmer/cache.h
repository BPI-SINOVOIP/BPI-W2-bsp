#ifndef _CACHE_H_
#define _CACHE_H_

/*
 * CR1 bits (CP#15 CR1)
 */
#define CR_M	(1 << 0)	/* MMU enable				*/
#define CR_A	(1 << 1)	/* Alignment abort enable		*/
#define CR_C	(1 << 2)	/* Dcache enable			*/
#define CR_W	(1 << 3)	/* Write buffer enable			*/
#define CR_P	(1 << 4)	/* 32-bit exception handler		*/
#define CR_D	(1 << 5)	/* 32-bit data address range		*/
#define CR_L	(1 << 6)	/* Implementation defined		*/
#define CR_B	(1 << 7)	/* Big endian				*/
#define CR_S	(1 << 8)	/* System MMU protection		*/
#define CR_R	(1 << 9)	/* ROM MMU protection			*/
#define CR_F	(1 << 10)	/* Implementation defined		*/
#define CR_Z	(1 << 11)	/* Implementation defined		*/
#define CR_I	(1 << 12)	/* Icache enable			*/
#define CR_V	(1 << 13)	/* Vectors relocated to 0xffff0000	*/
#define CR_RR	(1 << 14)	/* Round Robin cache replacement	*/
#define CR_L4	(1 << 15)	/* LDR pc can set T bit			*/
#define CR_DT	(1 << 16)
#define CR_IT	(1 << 18)
#define CR_ST	(1 << 19)
#define CR_FI	(1 << 21)	/* Fast interrupt (lower latency mode)	*/
#define CR_U	(1 << 22)	/* Unaligned access operation		*/
#define CR_XP	(1 << 23)	/* Extended page tables			*/
#define CR_VE	(1 << 24)	/* Vectored interrupts			*/
#define CR_EE	(1 << 25)	/* Exception (Big) Endian		*/
#define CR_TRE	(1 << 28)	/* TEX remap enable			*/
#define CR_AFE	(1 << 29)	/* Access flag enable			*/
#define CR_TE	(1 << 30)	/* Thumb exception enable		*/

//cache setting
#define ARMV7_DCACHE_INVAL_ALL			1
#define ARMV7_DCACHE_CLEAN_INVAL_ALL	2
#define ARMV7_DCACHE_INVAL_RANGE		3
#define ARMV7_DCACHE_CLEAN_INVAL_RANGE	4

/* CCSIDR */
#define CCSIDR_LINE_SIZE_OFFSET		0
#define CCSIDR_LINE_SIZE_MASK		0x7
#define CCSIDR_ASSOCIATIVITY_OFFSET	3
#define CCSIDR_ASSOCIATIVITY_MASK	(0x3FF << 3)
#define CCSIDR_NUM_SETS_OFFSET		13
#define CCSIDR_NUM_SETS_MASK		(0x7FFF << 13)

/*
 * Values for InD field in CSSELR
 * Selects the type of cache
 */
#define ARMV7_CSSELR_IND_DATA_UNIFIED	0
#define ARMV7_CSSELR_IND_INSTRUCTION	1

/* Values for Ctype fields in CLIDR */
#define ARMV7_CLIDR_CTYPE_NO_CACHE			0
#define ARMV7_CLIDR_CTYPE_INSTRUCTION_ONLY	1
#define ARMV7_CLIDR_CTYPE_DATA_ONLY			2
#define ARMV7_CLIDR_CTYPE_INSTRUCTION_DATA	3
#define ARMV7_CLIDR_CTYPE_UNIFIED			4

/*
 * CP15 Barrier instructions
 * Please note that we have separate barrier instructions in ARMv7
 * However, we use the CP15 based instructtions because we use
 * -march=armv5 in U-Boot
 */
//1295 + armv7 implies armv8 aarch32 mode

#ifdef __ARM_ARCH_8A__
#define CP15ISB	asm volatile ("ISB SY" : : : "memory")
#define CP15DSB	asm volatile ("DSB SY" : : : "memory")
#define CP15DMB	asm volatile ("DMB SY" : : : "memory")
#else
#define CP15ISB	asm volatile ("mcr     p15, 0, %0, c7, c5, 4" : : "r" (0))
#define CP15DSB	asm volatile ("mcr     p15, 0, %0, c7, c10, 4" : : "r" (0))
#define CP15DMB	asm volatile ("mcr     p15, 0, %0, c7, c10, 5" : : "r" (0))
#endif
#define isb() __asm__ __volatile__ ("" : : : "memory")
#define nop() __asm__ __volatile__("mov\tr0,r0\t@ nop\n\t");

static inline unsigned int get_cr(void)
{
        unsigned int val;
#if 0
        asm("mrc p15, 0, %0, c1, c0, 0  @ get CR" : "=r" (val) : : "cc");
#else
        asm ("MRS %0, SCTLR_EL1" : "=r" (val) : : "cc");
#endif 
        return val;
}

static inline void set_cr(unsigned int val)
{
#if 0
        asm volatile("mcr p15, 0, %0, c1, c0, 0 @ set CR"
          : : "r" (val) : "cc");
#else
          asm ("MSR SCTLR_EL1, %0" : : "r" (val)  : "cc");

#endif
        isb();
}

#endif //_CACHE_H_
