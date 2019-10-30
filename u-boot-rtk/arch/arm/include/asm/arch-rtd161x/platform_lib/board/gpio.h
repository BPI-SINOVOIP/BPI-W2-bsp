#ifndef GPIO_USERSPACE_ACCESS_LIBRARY
#define GPIO_USERSPACE_ACCESS_LIBRARY

#include <asm/arch/rbus/iso_reg.h>

#define ISO_GPIO_MAX   86

//refer to kylin mis
//1395
/*gpio*/
/*#define MIS_REG_BASE     		        (0x98010000)
#define MIS_GP0DIR                      (MIS_REG_BASE + 0xb100)
#define MIS_GP1DIR                      (MIS_REG_BASE + 0xb104)
#define MIS_GP0DATO                     (MIS_REG_BASE + 0xb110)
#define MIS_GP1DATO                     (MIS_REG_BASE + 0xb114)
#define MIS_GP0DATI                     (MIS_REG_BASE + 0xb120)
#define MIS_GP1DATI                     (MIS_REG_BASE + 0xb124)
#define MIS_GP0IE                       (MIS_REG_BASE + 0xb130)
#define MIS_GP1IE                       (MIS_REG_BASE + 0xb134)
#define MIS_GP0DP                       (MIS_REG_BASE + 0xb140)
#define MIS_GP1DP                       (MIS_REG_BASE + 0xb144)
#define MIS_GPDEB                       (MIS_REG_BASE + 0xb150)
*/
//refer to phoenix iso
/*iso*/
#define ISO_REG_BASE                     0x98007000      //see iso document

//#define ISO_ISR                        (ISO_REG_BASE + 0x0)
//#define ISO_UMSK_ISR                   (ISO_REG_BASE + 0x4)
//#define ISO_UMSK_ISR_GP_ASSERT         (ISO_REG_BASE + 0x8)
//#define ISO_UMSK_ISR_GP_DEASSERT       (ISO_REG_BASE + 0xc)
//#define ISO_DBG                        (ISO_REG_BASE + 0x24)
//#define ISO_CTRL                       (ISO_REG_BASE + 0x30)
//#define ISO_SCPU_INT_EN                (ISO_REG_BASE + 0x40)

//iso pin mux
//#define ISO_muxpad0                    (ISO_REG_BASE + 0x30c)
//#define ISO_DUMMY1                     (ISO_REG_BASE + 0x54)
//#define ISO_DUMMY2                     (ISO_REG_BASE + 0x58)
//#define ISO_RESERVED_USER_0            (ISO_REG_BASE + 0x64)
//#define ISO_RESERVED_USER_1            (ISO_REG_BASE + 0x78)
//#define ISO_RESERVED_USER_2            (ISO_REG_BASE + 0x7c)
//#define ISO_RESERVED_USER_3            (ISO_REG_BASE + 0x80)

/* iso gpio */
//#define ISO_GPDIR               		 (ISO_REG_BASE + 0x100)
//#define ISO_GP1DIR              		 (ISO_REG_BASE + 0x104)
//#define ISO_GPDATO              		 (ISO_REG_BASE + 0x108)
//#define ISO_GP1DATO             		 (ISO_REG_BASE + 0x10C)
//#define ISO_GPDATI              		 (ISO_REG_BASE + 0x110)
//#define ISO_GP1DATI             		 (ISO_REG_BASE + 0x114)
//#define ISO_GPIE                		 (ISO_REG_BASE + 0x118)
//#define ISO_GP1IE               		 (ISO_REG_BASE + 0x11C)
//#define ISO_GPDP                		 (ISO_REG_BASE + 0x120)
//#define ISO_GP1DP               		 (ISO_REG_BASE + 0x124)
//#define ISO_GPDEB             		 (ISO_REG_BASE + 0x128)

#define SYS_muxpad0				(0x98012600)			//mux for nand and emmc
#define SYS_muxpad1				(0x98012604)			//mux for sdio and sd card
#define SYS_muxpad2				(0x9801a908)		//mux for arm,lextra ej-tag
#define SYS_muxpad3				(0x9801a90C)	//mux for arm,lextra ej-tag
#define SYS_muxpad4				(0x9801a910)	//mux for ej-tag
#define SYS_muxpad5				(0x9801a914)	//sf_en = 1, force gpio0-3 mux to spi pins

#define PULL_DISABLE	0
#define PULL_DOWN		1
#define PULL_UP			2

int getGPIO(int GPIO_NUM);
int setGPIO(int GPIO_NUM, int value);
int getISOGPIO(int ISOGPIO_NUM);
int setISOGPIO(int ISOGPIO_NUM, int value);
int setGPIO_pullsel(unsigned int GPIO_NUM, unsigned char pull_sel);
int setISOGPIO_pullsel(int ISOGPIO_NUM, unsigned char pull_sel);

#endif
