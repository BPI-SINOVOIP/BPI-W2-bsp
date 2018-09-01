#ifndef __REALTEK_PLAT_CPU_H__
#define __REALTEK_PLAT_CPU_H__

extern unsigned long realtek_cpu_id;

#define RTK1195_CPU_ID		0x00006329
#define RTK1195_CPU_MASK	0x0000FFFF
#define RTK1195_REV_A		(0x0)
#define RTK1195_REV_B		(0x1)
#define RTK1195_REV_C		(0x2)
#define RTK1195_REV_D           (0x3)

#define IS_REALTEK_CPU(name, id, mask)		\
static inline int is_realtek_##name(void)	\
{											\
	return ((realtek_cpu_id & mask) == (id & mask));	\
}

IS_REALTEK_CPU(rtk1195, RTK1195_CPU_ID, RTK1195_CPU_MASK)

#if defined(CONFIG_ARCH_RTD119X)
#define soc_is_rtk1195()	is_realtek_rtk1195()
#else
#define soc_is_rtk1195()	0
#endif

extern unsigned int realtek_rev(void);

#endif /* __REALTEK_PLAT_CPU_H__ */
