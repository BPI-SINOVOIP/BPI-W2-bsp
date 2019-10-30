#ifndef _CACHE_H_
#define _CACHE_H_

#define SCTLR_EL3_UCI     (1 << 26)
#define SCTLR_EL3_EE      (1 << 25)
#define SCTLR_EL3_E0E     (1 << 24)
#define SCTLR_EL3_WXN     (1 << 19)
#define SCTLR_EL3_nTWE    (1 << 18)
#define SCTLR_EL3_nTWI    (1 << 16)
#define SCTLR_EL3_UCT     (1 << 15)
#define SCTLR_EL3_DZE     (1 << 14)
#define SCTLR_EL3_I       (1 << 12)//Global instruction cache enable
#define SCTLR_EL3_UMA     (1 << 9)
#define SCTLR_EL3_SED     (1 << 8)
#define SCTLR_EL3_ITD     (1 << 7)
#define SCTLR_EL3_THEE    (1 << 6)
#define SCTLR_EL3_CP15BEN (1 << 5)
#define SCTLR_EL3_SA0     (1 << 4)
#define SCTLR_EL3_SA      (1 << 3)
#define SCTLR_EL3_C       (1 << 2) //Global enable for data and unifies caches
#define SCTLR_EL3_A       (1 << 1) //Enable alignment fault check
#define SCTLR_EL3_M       (1 << 0) //Global Enable EL3 mmu


#define CP15ISB	asm volatile ("ISB SY" : : : "memory")
#define CP15DSB	asm volatile ("DSB SY" : : : "memory")
#define CP15DMB	asm volatile ("DMB SY" : : : "memory")

#define isb() __asm__ __volatile__ ("isb" : : : "memory")
#define nop() __asm__ __volatile__("mov\tr0,r0\t@ nop\n\t");

#define U_FLUSH_CACHE(addr, len) __asm_flush_dcache_range(addr, addr+len)

void disable_dcache(void);

#endif //_CACHE_H_
