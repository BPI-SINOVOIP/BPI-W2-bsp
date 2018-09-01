#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/smp.h>

#include <asm/cacheflush.h>
#include <asm/cp15.h>
#include <asm/smp_plat.h>

static inline void cpu_enter_lowpower(void)
{
    unsigned int v;

    asm volatile(
        "	mrc p15, 0, %0, c1, c0, 0\n"
        "	bic	%0, %0, %1\n"
        "	mcr	p15, 0, %0, c1, c0, 0\n"
        : "=&r" (v)
        : "Ir" (CR_C)
        : "cc");

    flush_cache_louis();

    asm volatile(
        /*
        * Turn off coherency
        */
        "	mrc	p15, 0, %0, c1, c0, 1\n"
        "	bic	%0, %0, %1\n"
        "	mcr	p15, 0, %0, c1, c0, 1\n"
        : "=&r" (v)
        : "Ir" (0x40)
        : "cc");

    isb();
    dsb();
}

static inline void cpu_leave_lowpower(void)
{
    unsigned int v;

    asm volatile(
        "mrc	p15, 0, %0, c1, c0, 0\n"
        "	orr	%0, %0, %1\n"
        "	mcr	p15, 0, %0, c1, c0, 0\n"
        "	mrc	p15, 0, %0, c1, c0, 1\n"
        "	orr	%0, %0, %2\n"
        "	mcr	p15, 0, %0, c1, c0, 1\n"
        : "=&r" (v)
        : "Ir" (CR_C), "Ir" (0x40)
        : "cc");
}

static inline void platform_do_lowpower(unsigned int cpu)
{
    for (;;) {
        /*
         * here's the WFI
         */
        asm("wfi"
            :
            :
            : "memory", "cc");
        if (pen_release == cpu_logical_map(cpu)) {
            break;
        }
        pr_debug("CPU%u: spurious wakeup call\n", cpu);
    }
}

void __ref rtk119x_cpu_die(unsigned int cpu)
{
    cpu_enter_lowpower();
    platform_do_lowpower(cpu);

    cpu_leave_lowpower();
}
