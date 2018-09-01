#include <generated/autoconf.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <asm/io.h>
#include "../include/os/type.h"
#include "../include/vo_reg.h"
#include "../include/tve_reg.h"
#include "../include/hdmi_reg.h"
#include "../example/example.h"
#include "../osd/osd.h"
#include "../vo/vo.h"
#include "../hdmi/hdmi.h"
#include "../../../debug.h"

static int debug    = 1;
#if 0
#define dprintk(msg...) if (debug)   { printk(KERN_DEBUG    "D/DC: " msg); }
#else
#define dprintk(msg...) if (debug)   { dbg_info(KERN_DEBUG    "D/RTK_FB: " msg); }
#endif

#include <linux/kthread.h>
static struct task_struct *brook_tsk;
static int data;
static int kbrook(void *arg);
int FPGAGo(void);

int Timing_Gen = 1;

static int kbrook(void *arg)
{
    unsigned int timeout;
    int *d = (int *) arg;

    for(;;) {
        if (kthread_should_stop()) break;
        //dprintk("%s(): %d\n", __FUNCTION__, (*d)++);
        do {
            set_current_state(TASK_INTERRUPTIBLE);
            timeout = schedule_timeout(HZ/60);
        } while(timeout);
        FPGAGo();
    }
    printk("break\n");

    return 0;
}

int FPGAGo(void)
{
#if 1
    int Enable_3D = 0;
    if(Enable_3D==1) //3D
    {
    }
    else //2D
    {
        if(HDMI_INTSTV_get_vsyncupdated(READ_REG_INT32U(HDMI_INTSTV)))
        {
            //0xb800d278
            WRITE_REG_INT32U(HDMI_INTSTV,
                    HDMI_INTSTV_vendupdated(0)|
                    HDMI_INTSTV_vsyncupdated(0));
            //0xb80056d0
            WRITE_REG_INT32U(VO_INTST,
                    VO_INTST_h_under(0)|
                    VO_INTST_i_under(0)|
                    VO_INTST_p_under(0)|
                    VO_INTST_sub1(0)|
                    VO_INTST_wbfin(0)|
                    VO_INTST_m2fin(0)|
                    VO_INTST_m1fin(1)|
                    VO_INTST_write_data(0));
            //0xb8005018
            WRITE_REG_INT32U(VO_FC,
                    VO_FC_wbgo(0)|
                    VO_FC_m2go(0)|
                    VO_FC_m1go(1)|
                    VO_FC_write_data(1));
            if(Timing_Gen)
            {
                if(VO_INTST_get_h_under(READ_REG_INT32U(VO_INTST)))
                {
                    //0xb80056d0
                    WRITE_REG_INT32U(VO_INTST,
                            VO_INTST_h_under(1)|
                            VO_INTST_i_under(0)|
                            VO_INTST_p_under(0)|
                            VO_INTST_sub1(0)|
                            VO_INTST_wbfin(0)|
                            VO_INTST_m2fin(0)|
                            VO_INTST_m1fin(0)|
                            VO_INTST_write_data(0));
                }
            }
            else
            {
                if(VO_INTST_get_p_under(READ_REG_INT32U(VO_INTST)))
                {
                    //0xb80056d0
                    WRITE_REG_INT32U(VO_INTST,
                            VO_INTST_h_under(0)|
                            VO_INTST_i_under(0)|
                            VO_INTST_p_under(1)|
                            VO_INTST_sub1(0)|
                            VO_INTST_wbfin(0)|
                            VO_INTST_m2fin(0)|
                            VO_INTST_m1fin(0)|
                            VO_INTST_write_data(0));
                }                            	
            }
        }
    }
#else
    WRITE_REG_INT32U(TVE_AV_CTRL,
            TVE_AV_CTRL_h_colorbar_ebl(1)|
            TVE_AV_CTRL_h_black_ebl(1)|
            TVE_AV_CTRL_i_colorbar_ebl(1)|
            TVE_AV_CTRL_p_colorbar_ebl(1)|
            TVE_AV_CTRL_i_black_ebl(1)|
            TVE_AV_CTRL_p_black_ebl(1)|
            TVE_AV_CTRL_write_data(0));

    //0xb8018028
    WRITE_REG_INT32U(TVE_INTPOS_P1,
            TVE_INTPOS_P1_write_en2(1)|TVE_INTPOS_P1_int_vpos(2)|
            TVE_INTPOS_P1_write_en1(1)|TVE_INTPOS_P1_int_hpos(0));

    //0xb8018020
    WRITE_REG_INT32U(TVE_INTST,
            TVE_INTST_intst_h(1)|
            TVE_INTST_intst_i(1)|
            TVE_INTST_intst_p(1)|
            TVE_INTST_write_data(0));

    //0xb800d278
    WRITE_REG_INT32U(HDMI_INTSTV,
            HDMI_INTSTV_vendupdated(0)|
            HDMI_INTSTV_vsyncupdated(0));

    //0xb80056d0
    WRITE_REG_INT32U(VO_INTST,
            VO_INTST_h_under(0)|
            VO_INTST_i_under(0)|
            VO_INTST_p_under(0)|
            VO_INTST_sub1(0)|
            VO_INTST_wbfin(0)|
            VO_INTST_m2fin(0)|
            VO_INTST_m1fin(1)|
            VO_INTST_write_data(0));

    //0xb8005018
    WRITE_REG_INT32U(VO_FC,
            VO_FC_wbgo(0)|
            VO_FC_m2go(0)|
            VO_FC_m1go(1)|
            VO_FC_write_data(1));

    //0xb80056d0
    WRITE_REG_INT32U(VO_INTST,
            VO_INTST_h_under(1)|
            VO_INTST_i_under(0)|
            VO_INTST_p_under(0)|
            VO_INTST_sub1(0)|
            VO_INTST_wbfin(0)|
            VO_INTST_m2fin(0)|
            VO_INTST_m1fin(0)|
            VO_INTST_write_data(0));

#endif

}

int FPGAInit(void)
{
    brook_tsk = kthread_create(kbrook, &data, "brook");
    if (IS_ERR(brook_tsk)) {
        brook_tsk = NULL;
        dprintk("[%s %d] ERROR!\n",__func__,__LINE__);
    } else {
        wake_up_process(brook_tsk);
    }
    WRITE_REG_INT32U(0x18000190,0x0000001f);
    WRITE_REG_INT32U(0x1800001c,0x00000603);
    WRITE_REG_INT32U(0x18000024,0x00018100);
    WRITE_REG_INT32U(0x1800d044,0x5afc9014);
    WRITE_REG_INT32U(0x18000194,0x0001c044);
    WRITE_REG_INT32U(0x1800d040,0x0df61891);
    WRITE_REG_INT32U(0x1800d230,0x00002217);
    WRITE_REG_INT32U(0x1800d2a4,0x0000aa22);

    SET_HDMI_Video_480p(
            2, //INT8U Pixel_Colocr_Format,
            0, //INT8U DVI_or_HDMI,
            1, //INT8U Deep_Color,
            4, //INT8U Deep_Depth,
            0, //INT8U xv_YCC,
            Timing_Gen, //INT8U Timing_Gen,
            0, //INT8U En_3D,
            0); //INT8U Format_3D);

    WRITE_REG_INT32U(VO_MODE,
            VO_MODE_ch2i(0)|
            VO_MODE_ch2(0)|
            VO_MODE_ch1i(0)|
            VO_MODE_ch1(1)|
            VO_MODE_write_data(1));

    WRITE_REG_INT32U(VO_MODE,
            VO_MODE_ch2i(1)|
            VO_MODE_ch2(1)|
            VO_MODE_ch1i(1)|
            VO_MODE_ch1(0)|
            VO_MODE_write_data(0));

    WRITE_REG_INT32U(VO_OUT,
            VO_OUT_write_en3(1)|VO_OUT_h(1)|
            VO_OUT_write_en2(1)|VO_OUT_i(0)|
            VO_OUT_write_en1(1)|VO_OUT_p(0));
}

int FPGAShowPic(unsigned int srcW,unsigned int srcH,unsigned int pImage)
{
    static int init = 0;
    if (init == 0) {
        FPGAInit();
        init = 1;
    }

    GO_function(
            0,  //INT32U display_mode,
            0,  //INT8U DVI_or_HDMI,
            Timing_Gen);  //INT8U Timing_Gen);

#if 1
    OSDShowPic(srcW,srcH,pImage);
#else
    VO_480p(
            0,//INT8U Test_Pattern,
            Timing_Gen,//INT8U Timing_Gen,
            0,//INT8U Enable_3D,
            0,//INT8U Format_3D,
            pImage,//unsigned int YPhyAddr,
            0); //pImage);//unsigned int CPhyAddr);`
#endif


    //FPGAGo();
    return 0;
}
