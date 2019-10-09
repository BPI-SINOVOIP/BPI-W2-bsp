/************************************************************************
 *
 *  sys_reg.h
 *
 *  Defines for Phoenix CRT registers
 *
 ************************************************************************/

#ifndef _REG_SYS_H
#define _REG_SYS_H

/* CRT */                                   
#define SYS_REG_BASE			0x18000000                                   

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
#define	SYS_PLL_DISP_SD1		(SYS_REG_BASE + 0x11c)
#define	SYS_PLL_DISP_SD4		(SYS_REG_BASE + 0x128)
#define	SYS_PLL_REG_CTRL		(SYS_REG_BASE + 0x144)
#define SYS_PLL_BUS 			(SYS_REG_BASE + 0x164)
#define SYS_PLL_BUS2			(SYS_REG_BASE + 0x168)
#define SYS_PLL_BUS3			(SYS_REG_BASE + 0x16c)
#define	SYS_PLL_DISP_2_SD1		(SYS_REG_BASE + 0x174)
#define	SYS_PLL_DCSB1    		(SYS_REG_BASE + 0x1b0)
#define	SYS_PLL_DCSB2    		(SYS_REG_BASE + 0x1b4)
#define	SYS_PLL_DCSB3    		(SYS_REG_BASE + 0x1b8)
#define SYS_PLL_SD1             (SYS_REG_BASE + 0x1e0)
#define SYS_PLL_SD2             (SYS_REG_BASE + 0x1e4)
#define SYS_PLL_SD3             (SYS_REG_BASE + 0x1e8)
#define SYS_PLL_SD4             (SYS_REG_BASE + 0x1ec)
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

#define SYS_muxpad0				(SYS_REG_BASE + 0x360)	//mux for nf
#define SYS_muxpad1				(SYS_REG_BASE + 0x364)	//mux for cr
#define SYS_muxpad2				(SYS_REG_BASE + 0x368)	//mux for arm,lextra ej-tag
#define SYS_muxpad3				(SYS_REG_BASE + 0x36c)	//mux for arm,lextra ej-tag
#define SYS_muxpad4				(SYS_REG_BASE + 0x370)	//mux for ej-tag
#define SYS_muxpad5				(SYS_REG_BASE + 0x374)	//sf_en = 1, force gpio0-3 mux to spi pins
#define SYS_DUMMY               (SYS_REG_BASE + 0x450)  //dummy register

//wraper
#define WRAP_A7_BASE            0x1801d400
#define WRAP_L2_BIST_BISR_RSTN  (WRAP_A7_BASE)
#define WRAP_HOLD_REMAP         (WRAP_A7_BASE+0x4)
#define WRAP_SECOND_RUN_EN      (WRAP_A7_BASE+0x8)
#define WRAP_DRF_BIST_BISR_MODE (WRAP_A7_BASE+0xc)
#define WRAP_BISR_DONE          (WRAP_A7_BASE+0x18)
#define WRAP_BISR_FAIL_GROUP    (WRAP_A7_BASE+0x24)

#endif /* #ifndef _REG_SYS_H */
