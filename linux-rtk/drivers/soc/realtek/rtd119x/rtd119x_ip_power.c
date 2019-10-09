#include <linux/pm.h>
#include <linux/suspend.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/cpu.h>
#include <linux/delay.h>

#include <asm/io.h>
#include <asm/system_misc.h>
//#include "include/reg.h"

#define RTK_VIRT_ADDR_MAP(addr) (RBUS_BASE_VIRT + ((unsigned int)addr - RBUS_BASE_PHYS))
//#define WRITE_REG_INT32U(addr,val)  *(volatile unsigned int *) RTK_VIRT_ADDR_MAP(addr) = (unsigned int)(val)
#define WRITE_REG_INT32U(addr,val)  writel(val, IOMEM(RTK_VIRT_ADDR_MAP(addr)))
//#define READ_REG_INT32U(addr)       *(volatile unsigned int *) RTK_VIRT_ADDR_MAP(addr)
#define READ_REG_INT32U(addr)       readl(IOMEM(RTK_VIRT_ADDR_MAP(addr)))
#define rtd_outl(addr,val)          WRITE_REG_INT32U(addr,val)
#define _sync(x)

__maybe_unused static int debug    = 1;
__maybe_unused static int warning  = 1;
__maybe_unused static int info     = 1;
#define dprintk(msg...) if (debug)   { printk(KERN_DEBUG    "D/IP_POWER: " msg); }
#define eprintk(msg...) if (1)       { printk(KERN_ERR      "E/IP_POWER: " msg); }
#define wprintk(msg...) if (warning) { printk(KERN_WARNING  "W/IP_POWER: " msg); }
#define iprintk(msg...) if (info)    { printk(KERN_INFO     "I/IP_POWER: " msg); }

typedef enum {
    ip_on = 0,
    ip_off,
} ip_state_t;

void rtd_clearbits(unsigned int addr,unsigned int mask)
{
    unsigned int temp = READ_REG_INT32U(addr);
    WRITE_REG_INT32U(addr,(temp & ~mask));
}

void rtd_setbits(unsigned int addr,unsigned int mask)
{
    unsigned int temp = READ_REG_INT32U(addr);
    WRITE_REG_INT32U(addr,(temp | mask));
}

int VideoDAC_A_power(ip_state_t state)
{
    int err = 1;
    if (state == ip_off) {
        dprintk("VideoDAC_A off\n");
        //rtd_clearbits(0x18018200,0x780000);       //A~C
        rtd_clearbits(0x180183a0,0xc0000000);   //current DAC disable
        //rtd_outl(0x180188bc,0x7);             //power down
        err = 0;
    } else if (state == ip_on) {
        dprintk("VideoDAC_A on\n");
        rtd_setbits(0x180183a0,0xc0000000);   //current DAC disable
        err = 0;
    } else {
        eprintk("[%s] %d\n",__func__,__LINE__);
    }
    return err;
}

int AudioDAC_power(ip_state_t state)
{
    int err = 1;
    if (state == ip_off) {
        dprintk("AudioDAC off\n");
        //Turn off Audio DAC
        rtd_outl(0x18006604,0xaaa00);           //AO DAC power down
        _sync();
        rtd_clearbits(0x18000010,0xe0000);      //Audio DAC (da,mod,codec) clock disable
        err = 0;
    } else if (state == ip_on) {
        dprintk("AudioDAC on\n");
        rtd_setbits(0x18000010,0xe0000);        //clock enable
        err = 0;
    } else {
        eprintk("[%s] %d\n",__func__,__LINE__);
    }
    return err;
}

int AVCPU_power(ip_state_t state)
{
#if 1
    return 0;
#else
    int err = 1;
    if (state == ip_off) {
        rtd_setbits(0x18007030,(BIT(2)|BIT(3)));
        err = 0;
    } else if (state == ip_on) {
        unsigned int temp = READ_REG_INT32U(0x18007030);
        temp &= ~BIT(2);
        temp |= BIT(3);
        WRITE_REG_INT32U(0x18007030,temp);
        err = 0;
    } else {
        eprintk("[%s] %d\n",__func__,__LINE__);
    }
    return err;
#endif
}

/**********************************************************************/
void SDIO_power_off(void)
{
	dprintk("SDIO off\n");
	//Turn off SDIO (clock from USB)
	rtd_clearbits(0x18000004,0x1000);				//SDIO reset
	rtd_clearbits(0x1800000c,0x44000000);	//SDIO/SDIO_IP clock disable
}

void GSPI_power_off(void)
{
	dprintk("GSPI off\n");
	//Turn off GSPI
	rtd_clearbits(0x18000000,0x8);				//GSPI reset
	rtd_clearbits(0x1800000c,0x8);				//GSPI clock disable
}

void eMMC_power_off(void)
{
	dprintk("eMMC off\n");
	//Turn off eMMC
	rtd_clearbits(0x18000004,0x800);			//eMMC reset
	rtd_clearbits(0x1800000c,0x11000000);	//eMMC/eMMC_IP clock disable
	rtd_clearbits(0x180001f4,0x1);				//eMMC clock disable
}

void CardReader_power_off(void)
{
	dprintk("CardReader off\n");
	//Turn off Card Reader
	rtd_clearbits(0x18000004,0x400);			//Card Reader reset
	rtd_clearbits(0x1800000c,0x82000000);	//Card Reader/SD_IP clock disable
	rtd_clearbits(0x180001e4,0x1);				//Card Reader clock disable
}

void CP_RNG_power_off(void)
{
	dprintk("CP_RNG off\n");
	//Turn off CP, RNG
	rtd_clearbits(0x18000000,0x2000000);	//CP reset
	rtd_clearbits(0x1800000c,0x80000);	//CP clock disable
	rtd_clearbits(0x18000000,0x2);				//RNG reset
}

void MD_power_off(void)
{
	dprintk("MD off\n");
	//Turn off MD
	rtd_clearbits(0x18000000,0x4000000);	//MD reset
	rtd_clearbits(0x1800000c,0x100000);		//MD clock disable
}

void AE_power_off(void)
{
	dprintk("AE off\n");
	//Turn off AE
	rtd_clearbits(0x18000000,0x10000000);	//AE reset
}

void VCPU_VE1_VE2_GPU_power_off(void)
{
	dprintk("VCPU_VE1_VE2_GPU off\n");
	//Turn off VCPU VE1,VE2,GPU
	rtd_clearbits(0x18000000,0x60000);		//VE1 264.JPEG reset
	rtd_clearbits(0x1800000c,0x3000);			//VE1 264.JPEG clock disable
	rtd_clearbits(0x18000000,0x20);				//VE2 265 reset
	rtd_clearbits(0x1800000c,0x20000000);	//VE2 265 clock disable
	rtd_outl(0x18000118,0x00000004);		//VCPU PLL off
	rtd_clearbits(0x18000000,0x00010000);	//GPU reset
	rtd_clearbits(0x1800000c,0x00000800);	//GPU clock disable
	rtd_setbits(0x180001c4,0x4);					//GPU PLL off
}

void VO_TVE_power_off(void)
{
	dprintk("VO_TVE off\n");
	//Turn off display VO, TVE
	rtd_clearbits(0x18000000,0x100000);		//VO reset
	rtd_clearbits(0x1800000c,0x8000);			//VO clock disable
	rtd_clearbits(0x18000000,0x80000);		//TVE reset
	rtd_clearbits(0x1800000c,0x4000);			//TVE clock disable
	rtd_outl(0x18000180,0x4);				//Display SD2 (DDSB)PLL off 432
	//rtd_clearbits(0x18000128)=0x00000004		//Display SD1(DDSA) PLL can't turn off 432 (NAND Cardreader)
}

void VideoDAC_A_power_off(void)
{
	dprintk("VideoDAC_A off\n");
	//Turn off Video DAC A
	//rtd_clearbits(0x18018200,0x780000);		//A~C
	rtd_clearbits(0x180183a0,0xc0000000);	//current DAC disable
	//rtd_outl(0x180188bc,0x7);				//power down
}

void TP_power_off(void)
{
	dprintk("TP off\n");
	//Turn off TP
	rtd_clearbits(0x18000000,0x8000000);	//TP reset
	rtd_clearbits(0x1800000c,0x200000);		//TP clock disable
}

void SE_power_off(void)
{
	dprintk("SE off\n");
	//Turn off SE
	rtd_clearbits(0x18000000,0x400000);		//SE reset
	rtd_clearbits(0x1800000c,0x20000);		//SE clock disable
}

void HDMITx_power_off(void)
{
	dprintk("HDMITx/MHLTx off\n");
	//Turn off HDMI Tx
	rtd_clearbits(0x18000000,0x1000);			//HDMI Tx reset
	rtd_clearbits(0x1800000c,0x100);			//HDMI Tx clock disable
	rtd_clearbits(0x18000010,0x100000);		//AO for HDMI clock disable
	rtd_outl(0x18000190,0x0);				//HDMI Tx MAC,PHY power down
	rtd_clearbits(0x18007088,0xc);		//AO for HDMI clock disable
}

void Audio_I2S_power_off(void)
{
	dprintk("Audio_I2S off\n");
	//Turn off Audio I2S in/out
	rtd_clearbits(0x18000010,0xc00000);		//I2S clock disable
}

void AudioDAC_power_off(void)
{
	dprintk("AudioDAC off\n");
	//Turn off Audio DAC
	rtd_outl(0x18006604,0xaaa00);		//AO DAC power down
	_sync();
	rtd_clearbits(0x18000010,0xe0000);		//Audio DAC (da,mod,codec) clock disable
}

void SPDIF_power_off(void)
{
	dprintk("SPDIF off\n");
	//Turn off SPDIF
	rtd_clearbits(0x18000010,0x200000);		//SPDIF
}

void HDMIRx_power_off(void)
{
	dprintk("HDMIRx/MHLRx off\n");
	//Turn off HDMI Rx (flow PLL?)
	rtd_clearbits(0x18000000,0x800);			//HDMI Rx reset
	rtd_clearbits(0x1800000c,0x2);				//HDMI Rx clock disable
}

void LVDS_power_off(void)
{
	dprintk("LVDS off\n");
	//Turn off LVDS (flow, PLL?)
	rtd_clearbits(0x18000000,0x200000);	//LVDS reset
	rtd_clearbits(0x1800000c,0x10000);		//LVDS clock disable
	rtd_setbits(0x18000024,0x420000);	//LVDS clock selection PLLLVDS
}

void MIPI_power_off(void)
{
	dprintk("MIPI off\n");
	//Turn off MIPI
	rtd_clearbits(0x18000000,0x40000000);//MIPI reset
	rtd_clearbits(0x1800000c,0x8000000);	//MIPI clock disable
}

void LSADC_power_off(void)
{
	dprintk("LSADC off\n");
	//Turn off LSADC
	rtd_outl(0x1801bc28,0x0);					//LSADC power down
}

void ALL_AV_power_off(void)
{
	dprintk("all AV off\n");
	//Turn off all AV
	rtd_clearbits(0x18000000,0x8000);			//AIO reset
	rtd_clearbits(0x1800000c,0x400);			//AIO clock disable
}
//ISO	block

void ETN_power_off(void)
{
	dprintk("ETN off\n");
	//Turn off ETN & PHY
	rtd_clearbits(0x18007088,0x600);			//ISO ETN ISO reset
	rtd_clearbits(0x1800708c,0x1800);			//ISO ETN clock disable
	rtd_clearbits(0x18000000,0x4000);			//CRT ETN reset
	rtd_clearbits(0x1800000c,0x200);			//CRT ETN clock disable
	rtd_outl(0x1800705c,0x0);				//ISO APHY/DPHY isolation
	rtd_outl(0x18007074,0x09d81153);	//Turn off PLL_ETN
}

void VFD_power_off(void)
{
	dprintk("VFD off\n");
	//Turn off VFD
	rtd_clearbits(0x18007088,0x1);				//ISO VFD ISO reset
	rtd_clearbits(0x1800708c,0x2);				//ISO VFD clock disable
}

void CBUS_power_off(void)
{
	dprintk("CBUS off\n");
	//Turn off CBUS
	rtd_clearbits(0x18007088,0x2060);			//ISO CBUS reset
	rtd_clearbits(0x1800708c,0x78);				//ISO CBUS clock disable
}

void CEC_power_off(void)
{
	dprintk("CEC off\n");
	//Turn off CEC
	rtd_clearbits(0x18007088,0xc);			//ISO CEC reset
	rtd_clearbits(0x1800708c,0x4);				//ISO CEC clock disable
}

void IR_power_off(void)
{
	rtd_clearbits(0x18007088,0x2);				//ISO IR reset
}

/**********************************************************************/

int rtk_ip_power_off(void)
{
    int err = 0;
    err = VideoDAC_A_power(ip_off);
    if (err) goto ERROR;
    err = AudioDAC_power(ip_off);
    /* Test to power down*/
    // HDMITx_power_off();
    // HDMIRx_power_off();
    // SDIO_power_off();
    // GSPI_power_off();
    // eMMC_power_off();
    // CardReader_power_off();
    // CP_RNG_power_off();
    // MD_power_off();
    // AE_power_off();
    // VCPU_VE1_VE2_GPU_power_off();
    // VO_TVE_power_off();
    // TP_power_off();
    // SE_power_off();
    // Audio_I2S_power_off();
    // SPDIF_power_off();
    // LVDS_power_off();
    // MIPI_power_off();
    // LSADC_power_off();
    // ALL_AV_power_off();
    // ETN_power_off();
    // VFD_power_off();
    // CBUS_power_off();
    // CEC_power_off();
    // IR_power_off();
ERROR:
    return err;
}

int rtk_ip_power_on(void)
{
    int err = 0;
    err = VideoDAC_A_power(ip_on);
    if (err) goto ERROR;
    err = AudioDAC_power(ip_on);
ERROR:
    return err;
}
