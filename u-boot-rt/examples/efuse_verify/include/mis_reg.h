/************************************************************************
 *
 *  mis_reg.h
 *
 *  Defines for Phoenix MISC registers
 *
 ************************************************************************/

#ifndef MIS_REG_H
#define MIS_REG_H

/************************************************************************
 *  Definition
 ************************************************************************/
 //interrupt
#define MIS_REG_BASE		(0x98010000)
#define MIS_UMSK_ISR		(MIS_REG_BASE + 0xb008)
#define MIS_ISR				(MIS_REG_BASE + 0xb00c)
#define MIS_UMSK_ISR_SWC	(MIS_REG_BASE + 0xb010)
#define MIS_ISR_SWC			(MIS_REG_BASE + 0xb014)
#define MIS_UR_CTRL			(MIS_REG_BASE + 0xb06c)
 //gpio
#define MIS_GP0DIR			(MIS_REG_BASE + 0xb100)
#define MIS_GP1DIR			(MIS_REG_BASE + 0xb104)
#define MIS_GP0DATO			(MIS_REG_BASE + 0xb110)
#define MIS_GP1DATO			(MIS_REG_BASE + 0xb114)
#define MIS_GP0DATI			(MIS_REG_BASE + 0xb120)
#define MIS_GP1DATI			(MIS_REG_BASE + 0xb124)
#define MIS_GP0IE			(MIS_REG_BASE + 0xb130)
#define MIS_GP1IE			(MIS_REG_BASE + 0xb134)
#define MIS_GP0DP			(MIS_REG_BASE + 0xb140)
#define MIS_GP1DP			(MIS_REG_BASE + 0xb144)
#define MIS_GPDEB			(MIS_REG_BASE + 0xb150)
 //uart
#define MIS_U1RBR_THR_DLL	(MIS_REG_BASE + 0xb200)
#define MIS_U1IER_DLH		(MIS_REG_BASE + 0xb204)
#define MIS_U1IIR_FCR		(MIS_REG_BASE + 0xb208)
#define MIS_U1LCR			(MIS_REG_BASE + 0xb20c)
#define MIS_U1MCR			(MIS_REG_BASE + 0xb210)
#define MIS_U1LSR			(MIS_REG_BASE + 0xb214)
#define MIS_U1MSR			(MIS_REG_BASE + 0xb218)
#define MIS_U1SCR			(MIS_REG_BASE + 0xb21c)
#define MIS_U1SRBR			(MIS_REG_BASE + 0xb230)
#define MIS_U1FAR			(MIS_REG_BASE + 0xb270)
#define MIS_U1TFR			(MIS_REG_BASE + 0xb274)
#define MIS_U1RFW			(MIS_REG_BASE + 0xb278)
#define MIS_U1USR			(MIS_REG_BASE + 0xb27c)
#define MIS_U1TFL			(MIS_REG_BASE + 0xb280)
#define MIS_U1RFL			(MIS_REG_BASE + 0xb284)
#define MIS_U1SRR			(MIS_REG_BASE + 0xb288)
#define MIS_U1SBCR			(MIS_REG_BASE + 0xb290)
#define MIS_U1SDMAM			(MIS_REG_BASE + 0xb294)
#define MIS_U1SFE			(MIS_REG_BASE + 0xb298)
#define MIS_U1SRT			(MIS_REG_BASE + 0xb29c)
#define MIS_U1STET			(MIS_REG_BASE + 0xb2a0)
#define MIS_U1HTX			(MIS_REG_BASE + 0xb2a4)
#define MIS_U1DMASA			(MIS_REG_BASE + 0xb2a8)
#define MIS_U1CPR			(MIS_REG_BASE + 0xb2f4)
#define MIS_U1UCV			(MIS_REG_BASE + 0xb2f8)
#define MIS_U1CTR			(MIS_REG_BASE + 0xb2fc)
 //timer
#define MIS_TC0TVR			(MIS_REG_BASE + 0xb500)
#define MIS_TC1TVR			(MIS_REG_BASE + 0xb504)
#define MIS_TC2TVR			(MIS_REG_BASE + 0xb508)
#define MIS_TC0CVR			(MIS_REG_BASE + 0xb50c)
#define MIS_TC1CVR			(MIS_REG_BASE + 0xb510)
#define MIS_TC2CVR			(MIS_REG_BASE + 0xb514)
#define MIS_TC0CR			(MIS_REG_BASE + 0xb518)
#define MIS_TC1CR			(MIS_REG_BASE + 0xb51c)
#define MIS_TC2CR			(MIS_REG_BASE + 0xb520)
#define MIS_TC0ICR			(MIS_REG_BASE + 0xb524)
#define MIS_TC1ICR			(MIS_REG_BASE + 0xb528)
#define MIS_TC2ICR			(MIS_REG_BASE + 0xb52c)
#define MIS_CLK90K_CTRL		(MIS_REG_BASE + 0xb538)
#define MIS_SCPU_CLK27M_90K		(MIS_REG_BASE + 0xb53c)
#define MIS_SCPU_CLK90K_LO		(MIS_REG_BASE + 0xb540)
#define MIS_SCPU_CLK90K_HI		(MIS_REG_BASE + 0xb544)
#define MIS_ACPU_CLK27M_90K		(MIS_REG_BASE + 0xb548)
#define MIS_ACPU_CLK90K_LO		(MIS_REG_BASE + 0xb54c)
#define MIS_ACPU_CLK90K_HI		(MIS_REG_BASE + 0xb550)
#define MIS_TCWCR			(MIS_REG_BASE + 0xb5b0)
#define MIS_TCWTR			(MIS_REG_BASE + 0xb5b4)
#define MIS_TCWNMI			(MIS_REG_BASE + 0xb5b8)
#define MIS_TCWOV			(MIS_REG_BASE + 0xb5bc)
#define MIS_TCWCR_SWC		(MIS_REG_BASE + 0xb5c0)
#define MIS_TCWTR_SWC		(MIS_REG_BASE + 0xb5c4)
#define MIS_TCWNMI_SWC		(MIS_REG_BASE + 0xb5c8)
#define MIS_TCWOV_SWC		(MIS_REG_BASE + 0xb5cc)
#endif /* #ifndef MIS_REG_H */
