/************************************************************************
 *
 *  sys_reg.h
 *
 *  Defines for Phoenix CRT registers
 *
 ************************************************************************/

#ifndef SYS_REG_H
#define SYS_REG_H

#define EMMC_REG_BASE                   0x98010000
/* CRT */                                   
#define SYS_REG_BASE			0x98000000                                   

#define SYS_GROUP1_CK_EN		(SYS_REG_BASE + 0x014)
#define SYS_GROUP1_CK_SEL		(SYS_REG_BASE + 0x018)
#define SYS_SOFT_RESET1			(SYS_REG_BASE + 0x000)
#define SYS_SOFT_RESET2			(SYS_REG_BASE + 0x004)
#define SYS_SOFT_RESET3			(SYS_REG_BASE + 0x008)
#define SYS_CLOCK_ENABLE1		(SYS_REG_BASE + 0x00c)
#define SYS_CLOCK_ENABLE2		(SYS_REG_BASE + 0x010)
#define SYS_NF_CKSEL            (SYS_REG_BASE + 0x038)
#define	SYS_PLL_SCPU1 			(SYS_REG_BASE + 0x100)
#define	SYS_PLL_SCPU2			(SYS_REG_BASE + 0x104)
#define	SYS_PLL_SCPU3			(SYS_REG_BASE + 0x108)
#define	SYS_PLL_ACPU1 			(SYS_REG_BASE + 0x10c)
#define	SYS_PLL_ACPU2			(SYS_REG_BASE + 0x110)
#define	SYS_PLL_VCPU1 			(SYS_REG_BASE + 0x114)
#define	SYS_PLL_VCPU2			(SYS_REG_BASE + 0x118)
#define	SYS_PLL_REG_CTRL		(SYS_REG_BASE + 0x144)
#define SYS_PLL_BUS3			(SYS_REG_BASE + 0x16c)
#define SYS_PLL_EMMC1           (SYS_REG_BASE + 0x1f0)
#define SYS_PLL_EMMC2           (SYS_REG_BASE + 0x1f4)
#define SYS_PLL_EMMC3           (SYS_REG_BASE + 0x1f8)
#define SYS_PLL_EMMC4           (SYS_REG_BASE + 0x1fc)
#define SYS_BG_CTL				(SYS_REG_BASE + 0x204)

#define SYS_CHIP_INFO2			(SYS_REG_BASE + 0x308)
														//eg: when kcpu_boot_info is setting, then set kcpu_boot_info_valid to let ISO module to latch it
#define SYS_PWDN_CTRL			(SYS_REG_BASE + 0x320)	//scpu_boot_info : scpu sent notify to acpu
#define SYS_PWDN_CTRL2			(SYS_REG_BASE + 0x324)	//acpu_boot_info : acpu sent notify to kcpu
#define SYS_PWDN_CTRL3			(SYS_REG_BASE + 0x328)	//scpu_boot_info_valid : b2
#define SYS_PWDN_CTRL4			(SYS_REG_BASE + 0x32c)	//acpu_boot_info_valid : b2 

#define SYS_muxpad0				(0x98012600)	//mux for nand and emmc
#define SYS_muxpad1				(0x98012604)	//mux for sdio and sd card
#define SYS_muxpad2				(0x9801a908)	//mux for arm,lextra ej-tag
#define SYS_muxpad3				(0x9801a90C)	//mux for arm,lextra ej-tag
#define SYS_muxpad4				(0x9801a910)	//mux for ej-tag
#define SYS_muxpad5				(0x9801a914)	//sf_en = 1, force gpio0-3 mux to spi pins

#define EMMC_CKGEN_CTL          ( EMMC_REG_BASE + 0x2478 )
//sb2
#define SB2_CHIP_INFO			(0x9801a204)

//cr
#define CR_EMMC_PFUC_NF1		(0x9810260c)

#endif /* #ifndef SYS_REG_H */
