#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/wait.h>
#include <linux/list.h>
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/export.h>
#include <linux/miscdevice.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/kthread.h>
#include "vo_reg.h"
#include "hdmi_reg.h"
#include "dc2fpga.h"

#define VPU_SUPPORT_ISR


#ifdef VPU_SUPPORT_ISR
#define HDMI_IRQ_NUM (63)
#endif

#ifdef VPU_SUPPORT_ISR
static int s_hdmi_irq = HDMI_IRQ_NUM;
#endif

#define ENABLE_DEBUG_MSG
#ifdef ENABLE_DEBUG_MSG
#define DPRINTK(args...)		printk(KERN_INFO args);
#else
#define DPRINTK(args...)
#endif



unsigned long rbus_virt_address = 0;
unsigned long hdmi_virt_address = 0;
unsigned long vo_virt_address = 0;
int fd_mem = -1;

static inline void WRITE_REG_INT32U(unsigned long Addr, unsigned int Value) {
    volatile unsigned int* ptr = NULL;
    if (Addr > 0x98000000 && Addr < (0x98000000 + 0x1000))
        ptr = (volatile unsigned int*) (((unsigned long)rbus_virt_address) + (Addr - 0x98000000));
    else if (Addr>=HDMI_INTEN)
        ptr = (volatile unsigned int*) (((unsigned long)hdmi_virt_address) + (Addr - HDMI_INTEN));
    else
        ptr = (volatile unsigned int*) (((unsigned long)vo_virt_address) + (Addr - VO_MODE));

    writel(Value, ptr);
}

static inline unsigned int READ_REG_INT32U(unsigned long Addr) {
    volatile unsigned int* ptr = NULL;
    if (Addr > 0x98000000 && Addr < (0x98000000 + 0x1000))
        ptr = (volatile unsigned int*) (((unsigned long)rbus_virt_address) + (Addr - 0x98000000));
    else if (Addr>=HDMI_INTEN)
        ptr = (volatile unsigned int*) (((unsigned long)hdmi_virt_address) + (Addr - HDMI_INTEN));
    else
        ptr = (volatile unsigned int*) (((unsigned long)vo_virt_address) + (Addr - VO_MODE));
    return readl(ptr);
}

#define WIN_PHYS_ADDRESS             (0x10000000 - 0x100000) //1MB



typedef struct vodrv_buffer_t {
    unsigned int size;
    unsigned long phys_addr;
    unsigned long base;							/* kernel logical address in use kernel */
    unsigned long virt_addr;				/* virtual user space address */
} vodrv_buffer_t;

static struct miscdevice s_vo_dev;
static vodrv_buffer_t s_vo_register = {0};
static vodrv_buffer_t s_hdmi_register = {0};
static vodrv_buffer_t s_rbus_register = {0};

#ifndef VM_RESERVED	/*for kernel up to 3.7.0 version*/
# define  VM_RESERVED   (VM_DONTEXPAND | VM_DONTDUMP)
#endif


static struct task_struct *brook_task;
static int brook_data;
static int kbrook(void *arg);

void HDMI_ISR(void) {
    if(HDMI_INTSTV_get_vsyncupdated(READ_REG_INT32U(HDMI_INTSTV)))
    {

#if CW_DEBUG
        unsigned int voinst =         READ_REG_INT32U(VO_INTST);
        printf("222 VO_INTST:%x \n",voinst);
#endif
        //printk(KERN_ALERT "[%s %d] HDMI_INTSTV_get_vsyncupdated", __FUNCTION__, __LINE__);

        //0xb800d278
        WRITE_REG_INT32U(HDMI_INTSTV,
                HDMI_INTSTV_vendupdated(0)|
                HDMI_INTSTV_vsyncupdated(0));
        //0x98005e84
        WRITE_REG_INT32U(VO_INTST,
                VO_INTST_afbc_parser_fail(0)|
                VO_INTST_afbc_decode_fail(0)|
                VO_INTST_h_under(0)|
                VO_INTST_i_under(0)|
                VO_INTST_p_under(0)|
                VO_INTST_sub2(0)|
                VO_INTST_sub1(0)|
                VO_INTST_wb2fin(0)|
                VO_INTST_wb1fin(0)|
                VO_INTST_m3fin(0)|
                VO_INTST_m2fin(0)|
                VO_INTST_m1fin(1)|
                VO_INTST_write_data(0));
        /*
        //0x98005e84  cwww
        WRITE_REG_INT32U(VO_INTEN,

        VO_INTEN_h_under(1)|
        VO_INTEN_i_under(1)|
        VO_INTEN_sub2(1)|
        VO_INTEN_sub1(1)|
        VO_INTEN_wb2fin(1)|
        VO_INTEN_wb1fin(1)|
        VO_INTEN_m3fin(1)|
        VO_INTEN_m1fin(1)|
        VO_INTEN_write_data(1));

*/
        WRITE_REG_INT32U(VO_INTEN,VO_INTEN_m1fin(1) | VO_INTEN_write_data(1));

        //0x98005020
        WRITE_REG_INT32U(VO_FC,
                VO_FC_wb2go(0)|
                VO_FC_wb1go(0)|
                VO_FC_mddgo(0)|
                VO_FC_m2go(0)|
                VO_FC_m1go(1)|
                VO_FC_write_data(1));




        if(VO_INTST_get_h_under(READ_REG_INT32U(VO_INTST)))
        {
#if CW_DEBUG
            printf("#@@ VO_INTST:get h_under \n");
#endif
            //0x98005e84
            WRITE_REG_INT32U(VO_INTST,
                    VO_INTST_afbc_parser_fail(0)|
                    VO_INTST_afbc_decode_fail(0)|
                    VO_INTST_h_under(1)|
                    VO_INTST_i_under(0)|
                    VO_INTST_p_under(0)|
                    VO_INTST_sub2(0)|
                    VO_INTST_sub1(0)|
                    VO_INTST_wb2fin(0)|
                    VO_INTST_wb1fin(0)|
                    VO_INTST_m3fin(0)|
                    VO_INTST_m2fin(0)|
                    VO_INTST_m1fin(0)|
                    VO_INTST_write_data(0));
        }
    }
}
static int kbrook(void *arg)
{
    unsigned int timeout;
    int *d = (int *) arg;

    for(;;) {
        if (kthread_should_stop()) break;
        //printk("%s(): %d\n", __FUNCTION__, (*d)++);
        static int temp = 5000;
        do {
            set_current_state(TASK_INTERRUPTIBLE);
            timeout = schedule_timeout(HZ/60);
            while(temp > 0)
            {
                temp--;
                //msleep(1000/120);
                msleep(1);
                //usleep((1000000/120)); //usleep (1/120)s

#if 1
                HDMI_ISR();
#else
                if(HDMI_INTSTV_get_vsyncupdated(READ_REG_INT32U(HDMI_INTSTV)))
                {

#if CW_DEBUG
                    unsigned int voinst =         READ_REG_INT32U(VO_INTST);
                    printf("222 VO_INTST:%x \n",voinst);
#endif
                    //printk(KERN_ALERT "[%s %d] HDMI_INTSTV_get_vsyncupdated", __FUNCTION__, __LINE__);
                    msleep(1);

                    //0xb800d278
                    WRITE_REG_INT32U(HDMI_INTSTV,
                            HDMI_INTSTV_vendupdated(0)|
                            HDMI_INTSTV_vsyncupdated(0));
                    //0x98005e84
                    WRITE_REG_INT32U(VO_INTST,
                            VO_INTST_afbc_parser_fail(0)|
                            VO_INTST_afbc_decode_fail(0)|
                            VO_INTST_h_under(0)|
                            VO_INTST_i_under(0)|
                            VO_INTST_p_under(0)|
                            VO_INTST_sub2(0)|
                            VO_INTST_sub1(0)|
                            VO_INTST_wb2fin(0)|
                            VO_INTST_wb1fin(0)|
                            VO_INTST_m3fin(0)|
                            VO_INTST_m2fin(0)|
                            VO_INTST_m1fin(1)|
                            VO_INTST_write_data(0));
                    /*
                    //0x98005e84  cwww
                    WRITE_REG_INT32U(VO_INTEN,

                    VO_INTEN_h_under(1)|
                    VO_INTEN_i_under(1)|
                    VO_INTEN_sub2(1)|
                    VO_INTEN_sub1(1)|
                    VO_INTEN_wb2fin(1)|
                    VO_INTEN_wb1fin(1)|
                    VO_INTEN_m3fin(1)|
                    VO_INTEN_m1fin(1)|
                    VO_INTEN_write_data(1));

*/
                    WRITE_REG_INT32U(VO_INTEN,VO_INTEN_m1fin(1) | VO_INTEN_write_data(1));

                    //0x98005020
                    WRITE_REG_INT32U(VO_FC,
                            VO_FC_wb2go(0)|
                            VO_FC_wb1go(0)|
                            VO_FC_mddgo(0)|
                            VO_FC_m2go(0)|
                            VO_FC_m1go(1)|
                            VO_FC_write_data(1));




                    if(VO_INTST_get_h_under(READ_REG_INT32U(VO_INTST)))
                    {
#if CW_DEBUG
                        printf("#@@ VO_INTST:get h_under \n");
#endif
                        //0x98005e84
                        WRITE_REG_INT32U(VO_INTST,
                                VO_INTST_afbc_parser_fail(0)|
                                VO_INTST_afbc_decode_fail(0)|
                                VO_INTST_h_under(1)|
                                VO_INTST_i_under(0)|
                                VO_INTST_p_under(0)|
                                VO_INTST_sub2(0)|
                                VO_INTST_sub1(0)|
                                VO_INTST_wb2fin(0)|
                                VO_INTST_wb1fin(0)|
                                VO_INTST_m3fin(0)|
                                VO_INTST_m2fin(0)|
                                VO_INTST_m1fin(0)|
                                VO_INTST_write_data(0));
                    }
                }
#endif
            }
        } while(timeout);
    }
    printk("break\n");

    return 0;
}


#if 1

enum VO_OSD_COLOR_FORMAT {
	VO_OSD_COLOR_FORMAT_2BIT = 0,
	VO_OSD_COLOR_FORMAT_4BIT = 1,
	VO_OSD_COLOR_FORMAT_8BIT = 2,
	VO_OSD_COLOR_FORMAT_RGB332 = 3,
	VO_OSD_COLOR_FORMAT_RGB565 = 4,
	VO_OSD_COLOR_FORMAT_ARGB1555 = 5,
	VO_OSD_COLOR_FORMAT_ARGB4444 = 6,
	VO_OSD_COLOR_FORMAT_ARGB8888 = 7,
	VO_OSD_COLOR_FORMAT_Reserved0 = 8,
	VO_OSD_COLOR_FORMAT_Reserved1 = 9,
	VO_OSD_COLOR_FORMAT_Reserved2 = 10,
	VO_OSD_COLOR_FORMAT_YCBCRA4444 = 11,
	VO_OSD_COLOR_FORMAT_YCBCRA8888 = 12,
	VO_OSD_COLOR_FORMAT_RGBA5551 = 13,
	VO_OSD_COLOR_FORMAT_RGBA4444 = 14,
	VO_OSD_COLOR_FORMAT_RGBA8888 = 15,
	VO_OSD_COLOR_FORMAT_420 = 16,
	VO_OSD_COLOR_FORMAT_422 = 17,
	VO_OSD_COLOR_FORMAT_RGB323 = 18,
	VO_OSD_COLOR_FORMAT_RGB233 = 19,
	VO_OSD_COLOR_FORMAT_RGB556 = 20,
	VO_OSD_COLOR_FORMAT_RGB655 = 21,
	VO_OSD_COLOR_FORMAT_RGB888 = 22,
	VO_OSD_COLOR_FORMAT_RGB565_LITTLE = 36,
	VO_OSD_COLOR_FORMAT_ARGB1555_LITTLE = 37,
	VO_OSD_COLOR_FORMAT_ARGB4444_LITTLE = 38,
	VO_OSD_COLOR_FORMAT_ARGB8888_LITTLE = 39,
	VO_OSD_COLOR_FORMAT_YCBCRA4444_LITTLE = 43,
	VO_OSD_COLOR_FORMAT_YCBCRA8888_LITTLE = 44,
	VO_OSD_COLOR_FORMAT_RGBA5551_LITTLE = 45,
	VO_OSD_COLOR_FORMAT_RGBA4444_LITTLE = 46,
	VO_OSD_COLOR_FORMAT_RGBA8888_LITTLE = 47,
	VO_OSD_COLOR_FORMAT_RGB556_LITTLE = 52,
	VO_OSD_COLOR_FORMAT_RGB655_LITTLE = 53,
	VO_OSD_COLOR_FORMAT_RGB888_LITTLE = 54,
};
typedef enum VO_OSD_COLOR_FORMAT VO_OSD_COLOR_FORMAT;

enum VO_GRAPHIC_PLANE {
	VO_GRAPHIC_OSD = 0,
	VO_GRAPHIC_SUB1 = 1,
	VO_GRAPHIC_SUB2 = 2,
	VO_GRAPHIC_OSD1 = 0,
	VO_GRAPHIC_OSD2 = 2,
};
typedef enum VO_GRAPHIC_PLANE VO_GRAPHIC_PLANE;

struct VO_RECTANGLE {
	short x;
	short y;
	unsigned short width;
	unsigned short height;
};
typedef struct VO_RECTANGLE VO_RECTANGLE;

enum VO_OSD_RGB_ORDER {
	VO_OSD_COLOR_RGB = 0,
	VO_OSD_COLOR_BGR = 1,
	VO_OSD_COLOR_GRB = 2,
	VO_OSD_COLOR_GBR = 3,
	VO_OSD_COLOR_RBG = 4,
	VO_OSD_COLOR_BRG = 5,
};
typedef enum VO_OSD_RGB_ORDER VO_OSD_RGB_ORDER;


struct VIDEO_RPC_VOUT_CREATE_GRAPHIC_WIN {
	enum VO_GRAPHIC_PLANE plane;
	struct VO_RECTANGLE winPos;
	enum VO_OSD_COLOR_FORMAT colorFmt;
	enum VO_OSD_RGB_ORDER rgbOrder;
	int colorKey;
	unsigned char alpha;
	unsigned char reserved;
};
typedef struct VIDEO_RPC_VOUT_CREATE_GRAPHIC_WIN VIDEO_RPC_VOUT_CREATE_GRAPHIC_WIN;


struct VIDEO_RPC_VOUT_CONFIG_GRAPHIC_CANVAS {
	enum VO_GRAPHIC_PLANE plane;
	struct VO_RECTANGLE srcWin;
	struct VO_RECTANGLE dispWin;
	unsigned char go;
};
int already_init = 0;
/*
typedef struct
{
  unsigned int last:1 ;
  unsigned int reserved:31 ;

} VO_OSD_WIN_NEXT_ADDR ;

typedef struct
{
  unsigned int y:16 ;
  unsigned int x:16 ;

} VO_OSD_WIN_XY ;


typedef struct
{
  unsigned int height:16 ;
  unsigned int width:16 ;

} VO_OSD_WIN_WH ;

typedef struct
{
  unsigned int extendMode:1 ;
  unsigned int rgbOrder:3 ;
  unsigned int alphaType:1 ;
  unsigned int alphaEn:1 ;
  unsigned int storageMode:1 ;
  unsigned int objType:1 ;
  unsigned int alpha:8 ;
  unsigned int reserved1:6 ;
  unsigned int littleEndian:1 ;
  unsigned int keepPreCLUT:1 ;
  unsigned int reserved2:3 ;
  unsigned int type:5 ;

} VO_OSD_WIN_ATTR ;

typedef struct
{
  unsigned int reserved:7 ;
  unsigned int keyEn:1 ;
  unsigned int key:24 ;

}VO_OSD_WIN_KEY ;

typedef struct
{
  unsigned int objYoffset:16 ;
  unsigned int objXoffset:16 ;

} VO_OSD_WIN_INIT ;

typedef struct
{
  unsigned int reserved:6 ;
  unsigned int id:8 ;
  unsigned int previd:8 ;
  unsigned int nextid:8 ;
  unsigned int drawn:1 ;
  unsigned int occupied:1 ;

} VO_OSD_WIN_CTRL ;
*/
typedef struct
{
  unsigned int reserved:31 ;

  unsigned int last:1 ;

} VO_OSD_WIN_NEXT_ADDR ;

typedef struct
{
  unsigned int x:16 ;

  unsigned int y:16 ;

} VO_OSD_WIN_XY ;


typedef struct
{
  unsigned int width:16 ;

  unsigned int height:16 ;

} VO_OSD_WIN_WH ;

typedef struct
{

  unsigned int type:5 ;
  //unsigned int reserved2:3 ;
  unsigned int afbc_mode :1;
  unsigned int afbc_yuv_trans:1;
  unsigned int afbc_block_split:1;
  unsigned int keepPreCLUT:1 ;
  unsigned int littleEndian:1 ;
 unsigned int reserved1:6 ;
  
 unsigned int alpha:8 ;

  unsigned int objType:1 ;
  unsigned int storageMode:1 ;
  unsigned int alphaEn:1 ;
   unsigned int alphaType:1 ;
  unsigned int rgbOrder:3 ;
  
  unsigned int extendMode:1 ;




 




} VO_OSD_WIN_ATTR ;

typedef struct
{

unsigned int key:24 ;
  unsigned int keyEn:1 ;

  unsigned int reserved:7 ;
  

  
}VO_OSD_WIN_KEY ;

typedef struct
{  unsigned int objXoffset:16 ;
  unsigned int objYoffset:16 ;


} VO_OSD_WIN_INIT ;

typedef struct
{
  unsigned int occupied:1 ;
  unsigned int drawn:1 ;
  unsigned int nextid:8 ;
  unsigned int previd:8 ;
  unsigned int id:8 ;

  unsigned int reserved:6 ;





} VO_OSD_WIN_CTRL ;




typedef struct
{
  VO_OSD_WIN_NEXT_ADDR reserve ;
  // Window Region 
  VO_OSD_WIN_XY   winXY ;
  VO_OSD_WIN_WH   winWH ;
  // Window Attribute 
  VO_OSD_WIN_ATTR attr ;
  unsigned int    CLUT_addr ;
  VO_OSD_WIN_KEY  colorKey ;
  unsigned int    top_addr ;    // top or progressive OSD start address (sequential) or index (block mode) 
  unsigned int    bot_addr ;    // bottom OSD start address (sequential) or index (block mode) 
  unsigned int    pitch ;
  VO_OSD_WIN_INIT objOffset ;
  unsigned int    nxtAddr ;
  unsigned int afbc_head_addr;

} VO_OSD_WIN ;
#if 0
typedef struct
{
  VO_OSD_WIN_NEXT_ADDR nxtAddr ;
  /* Window Region */
  VO_OSD_WIN_XY   winXY ;
  VO_OSD_WIN_WH   winWH ;
  /* Window Attribute */
  VO_OSD_WIN_ATTR attr ;
  unsigned int    CLUT_addr ;
  VO_OSD_WIN_KEY  colorKey ;
  unsigned int    top_addr ;    /* top or progressive OSD start address (sequential) or index (block mode) */
  unsigned int    bot_addr ;    /* bottom OSD start address (sequential) or index (block mode) */
  unsigned int    pitch ;
  VO_OSD_WIN_INIT objOffset ;

  // below size should be multiple of 16 s.t every element of VO_OSD_WIN array can be located at 16 byte-aligned address //
  VO_OSD_WIN_CTRL ctrl __attribute__((aligned(16))) ;
  unsigned int    srcImg[2] ;
  unsigned short  srcPitch[2] ;
  VO_OSD_WIN_XY   winXY_2D ;
  VO_OSD_WIN_WH   winWH_2D ;
  int dummy[4] __attribute__((aligned(16)));

} VO_OSD_WIN ;
#endif
typedef struct
{
  short x ;        /* upper-left corner x coordinate */
  short y ;        /* upper-left corner y coordinate */
  short width ;    /* window width */
  short height ;   /* window height */

} VP_WINDOW ;


enum VO_GRAPHIC_STORAGE_MODE {
	VO_GRAPHIC_BLOCK = 0,
	VO_GRAPHIC_SEQUENTIAL = 1,
};
typedef enum VO_GRAPHIC_STORAGE_MODE VO_GRAPHIC_STORAGE_MODE;

struct VIDEO_RPC_VOUT_DRAW_GRAPHIC_WIN {
	enum VO_GRAPHIC_PLANE plane;
	u_short winID;
	enum VO_GRAPHIC_STORAGE_MODE storageMode;
	u_char paletteIndex;
	u_char compressed;
	u_char interlace_Frame;
	u_char bottomField;
	u_short startX[4];
	u_short startY[4];
	u_short imgPitch[4];
	long pImage[4];
	u_char reserved;
	u_char go;
};
typedef struct VIDEO_RPC_VOUT_DRAW_GRAPHIC_WIN VIDEO_RPC_VOUT_DRAW_GRAPHIC_WIN;

#if 0
void SUB1_draw(void)
{
    int pImage, x, y, w, h  ;

    w =720 ;
    h = 576;
    x = y = 0 ;
	pImage = 0x10000000 ;

	unsigned long tmp = (unsigned long)mmap(0, 0x100000, PROT_READ | PROT_WRITE, MAP_SHARED, fd_mem, WIN_PHYS_ADDRESS);;

	VO_OSD_WIN *win = (VO_OSD_WIN *)tmp;
	win->winXY.x        = x;
    win->winXY.y        = y ;
    win->winWH.width    = w ;
    win->winWH.height   = h ;

    win->attr.rgbOrder  = 0 ;//000   
    win->attr.alphaType= 0;
	win->attr.alphaEn   = 1 ;
    win->attr.storageMode = 1;
    win->attr.alpha= 20;
	win->attr.littleEndian = 1 ;
	win->attr.keepPreCLUT = 0;
	win->attr.afbc_block_split =0;
	win->attr.afbc_yuv_trans=0;
	win->attr.afbc_mode = 0;
	win->attr.type      =  7; //00111
    win->CLUT_addr = 0;
    win->colorKey.keyEn = 0 ;
    win->colorKey.key   = 0xff ;

    win->top_addr     = pImage ;
    win->bot_addr     = pImage ;

    win->pitch = w ;
    win->objOffset.objXoffset = x;
    win->objOffset.objYoffset = y ;
          
    win->nxtAddr = 0;
    win->afbc_head_addr = 0;



    //0xb8005000
    WRITE_REG_INT32U(VO_MODE,
                     VO_MODE_ch2(0)|
                     VO_MODE_ch1(1)|
                     VO_MODE_write_data(1));
                     
                    
  
     //0x98005018
    WRITE_REG_INT32U(VO_M1_3D,
                     VO_M1_3D_top_and_bottom(1)|
                     VO_M1_3D_side_by_side(1)|
                     VO_M1_3D_right(1)|
                     VO_M1_3D_write_data(0));

    WRITE_REG_INT32U(VO_MIX12,
                     VO_MIX12_sub1(1));

        //0xb8005604
    WRITE_REG_INT32U(VO_M1_SIZE,
                     VO_M1_SIZE_w(720)|
                     VO_M1_SIZE_h(576));




            //0xb8005004
     WRITE_REG_INT32U(VO_OUT,
                             VO_OUT_write_en3(1)|VO_OUT_h(1)
                  );
	// WRITE_REG_INT32U(VO_OSD1_WI,VO_OSD1_WI_endian( 1)|VO_OSD1_WI_swap_8byte(1));
     unsigned long winAddr =(unsigned long) &win;
     WRITE_REG_INT32U(VO_SUB1_WI_1,WIN_PHYS_ADDRESS);

     WRITE_REG_INT32U(VO_SUB1,VO_SUB1_osd(1)|VO_SUB1_write_data(1));

     WRITE_REG_INT32U(VO_SUB1_SIZE,VO_SUB1_SIZE_w(w)|VO_SUB1_SIZE_h(h));



}
#endif
//void OSD_draw(void)
int OSD_draw(unsigned int w, unsigned int h, unsigned long pImage)
{
    //printk(KERN_ALERT "[%s %d] w %d h %d pImage 0x%x", __FUNCTION__, __LINE__, w, h, pImage);
    //int pImage, x, y, w, h  ;

    //w =720 ;
    //h = 576;
    int x, y;
    x = y = 0;
	//pImage = 0x10000000 ;

//	unsigned long tmp = (unsigned long)mmap(0, 0x100000, PROT_READ | PROT_WRITE, MAP_SHARED, fd_mem, WIN_PHYS_ADDRESS);
    //printk(KERN_ALERT "this device %p\n", s_vo_dev.this_device);
	unsigned long win_phy, win_vir;
	win_vir = (unsigned long)dma_alloc_coherent(s_vo_dev.this_device, PAGE_ALIGN(sizeof(VO_OSD_WIN)), (dma_addr_t *) (&win_phy), GFP_DMA | GFP_KERNEL);
    if ((void *)(win_vir) == NULL)	{
        printk(KERN_ERR "[VPUDRV] Physical memory allocation error size=%d\n", sizeof(VO_OSD_WIN));
        return -1;
    }
    //printk(KERN_ALERT "[%s %d] win_phy:%lx", __FUNCTION__, __LINE__, win_phy);


	VO_OSD_WIN *win = (VO_OSD_WIN *)win_vir;
	win->reserve.last = 1;
	win->reserve.reserved= 0;
	
	win->winXY.x        = x;
    win->winXY.y        = y ;
    win->winWH.width    = w ;
    win->winWH.height   = h ;

    win->attr.rgbOrder  = 0 ;//000   
    win->attr.alphaType= 0;
	win->attr.alphaEn   = 1 ;
    win->attr.storageMode = 1;
    win->attr.alpha= 20;
	win->attr.littleEndian = 1 ;
	win->attr.keepPreCLUT = 0;
	win->attr.afbc_block_split =0;
	win->attr.afbc_yuv_trans=0;
	win->attr.afbc_mode = 0;
	win->attr.type      =  7; //00111
    win->CLUT_addr = 0;
    win->colorKey.keyEn = 0 ;
    win->colorKey.key   = 0xff ;

    win->top_addr     = pImage ;
    win->bot_addr     = pImage ;

    win->pitch = w * 4;
    win->objOffset.objXoffset = x;
    win->objOffset.objYoffset = y ;
          
    win->nxtAddr = 0;
    win->afbc_head_addr = 0;



    //0xb8005000
    WRITE_REG_INT32U(VO_MODE,
                     VO_MODE_ch2(0)|
                     VO_MODE_ch1(1)|
                     VO_MODE_write_data(1));
                     
                    
  
     //0x98005018
    WRITE_REG_INT32U(VO_M1_3D,
                     VO_M1_3D_top_and_bottom(1)|
                     VO_M1_3D_side_by_side(1)|
                     VO_M1_3D_right(1)|
                     VO_M1_3D_write_data(0));


   WRITE_REG_INT32U(VO_MIX12,
                     VO_MIX12_vbi2(0)|
                     VO_MIX12_vbi1(0)|
                     VO_MIX12_csr(0)|
                     VO_MIX12_osd1(1)|
                    VO_MIX12_sub2(0)|
                     VO_MIX12_sub1(0)|
                     VO_MIX12_v2(0)|
                     VO_MIX12_v1(0)|
                     VO_MIX12_bg2(0)|
                     VO_MIX12_bg1(0));

        //0xb8005604
    WRITE_REG_INT32U(VO_M1_SIZE,
                     VO_M1_SIZE_w(1280)|
                     VO_M1_SIZE_h(720));




            //0xb8005004
     WRITE_REG_INT32U(VO_OUT,
                             VO_OUT_write_en3(1)|VO_OUT_h(1)
                  );
	// WRITE_REG_INT32U(VO_OSD1_WI,VO_OSD1_WI_endian( 1)|VO_OSD1_WI_swap_8byte(1));
  //   unsigned long winAddr =(unsigned long) &win;
  //   WRITE_REG_INT32U(VO_OSD1_WI_1,WIN_PHYS_ADDRESS);
  //   WRITE_REG_INT32U(VO_OSD1_WI_3D,WIN_PHYS_ADDRESS);
     WRITE_REG_INT32U(VO_OSD1_WI_1,win_phy);
     WRITE_REG_INT32U(VO_OSD1_WI_3D,win_phy);



     WRITE_REG_INT32U(VO_OSD1,VO_OSD1_osd(1)|VO_OSD1_write_data(1)/*|VO_OSD1_hs(1)|VO_OSD1_vs(1)*/);

     WRITE_REG_INT32U(VO_OSD1_SIZE,VO_OSD1_SIZE_w(1280/*w*/)|VO_OSD1_SIZE_h(720/*h*/));

     HDMI_ISR();

#if 0 
     static int temp = 1000;
while(temp > 0)
{
    temp--;
    msleep(1000/120);
//usleep((1000000/120)); //usleep (1/120)s
	
     if(HDMI_INTSTV_get_vsyncupdated(READ_REG_INT32U(HDMI_INTSTV)))
     {

#if CW_DEBUG
        unsigned int voinst =         READ_REG_INT32U(VO_INTST);
		printf("222 VO_INTST:%x \n",voinst);
#endif
    //printk(KERN_ALERT "[%s %d] HDMI_INTSTV_get_vsyncupdated", __FUNCTION__, __LINE__);


	//0xb800d278
                WRITE_REG_INT32U(HDMI_INTSTV,
                                 HDMI_INTSTV_vendupdated(0)|
                                 HDMI_INTSTV_vsyncupdated(0));
     //0x98005e84
                WRITE_REG_INT32U(VO_INTST,
                                 VO_INTST_afbc_parser_fail(0)|
                                 VO_INTST_afbc_decode_fail(0)|
                                 VO_INTST_h_under(0)|
                                 VO_INTST_i_under(0)|
                                 VO_INTST_p_under(0)|
                                 VO_INTST_sub2(0)|
                                 VO_INTST_sub1(0)|
                                 VO_INTST_wb2fin(0)|
                                 VO_INTST_wb1fin(0)|
                                 VO_INTST_m3fin(0)|
                                 VO_INTST_m2fin(0)|
                                 VO_INTST_m1fin(1)|
                                 VO_INTST_write_data(0));
/*
	           //0x98005e84  cwww
                WRITE_REG_INT32U(VO_INTEN,
            
                                 VO_INTEN_h_under(1)|
                                 VO_INTEN_i_under(1)|
                                 VO_INTEN_sub2(1)|
                                 VO_INTEN_sub1(1)|
                                 VO_INTEN_wb2fin(1)|
                                 VO_INTEN_wb1fin(1)|
                                 VO_INTEN_m3fin(1)|
                                 VO_INTEN_m1fin(1)|
                                 VO_INTEN_write_data(1));

*/
                WRITE_REG_INT32U(VO_INTEN,VO_INTEN_m1fin(1) | VO_INTEN_write_data(1));
				
                //0x98005020
                WRITE_REG_INT32U(VO_FC,
                                 VO_FC_wb2go(0)|
                                 VO_FC_wb1go(0)|
                                 VO_FC_mddgo(0)|
                                 VO_FC_m2go(0)|
                                 VO_FC_m1go(1)|
                                 VO_FC_write_data(1));



				
	  			if(VO_INTST_get_h_under(READ_REG_INT32U(VO_INTST)))
        		{
#if CW_DEBUG
					printf("#@@ VO_INTST:get h_under \n");
#endif
					//0x98005e84
                        WRITE_REG_INT32U(VO_INTST,
                                         VO_INTST_afbc_parser_fail(0)|
                                         VO_INTST_afbc_decode_fail(0)|
                                         VO_INTST_h_under(1)|
                                         VO_INTST_i_under(0)|
                                         VO_INTST_p_under(0)|
                                         VO_INTST_sub2(0)|
                                         VO_INTST_sub1(0)|
                                         VO_INTST_wb2fin(0)|
                                         VO_INTST_wb1fin(0)|
                                         VO_INTST_m3fin(0)|
                                         VO_INTST_m2fin(0)|
                                         VO_INTST_m1fin(0)|
                                         VO_INTST_write_data(0));
	  		}
     }
}
#endif
    return 0;
}

#endif

#define TEST_Y_ADDR 0x10000000
#define TEST_C_ADDR 0x15000000

#define TEST_MC_OFFSET_ADDR 0x10000000
#define TEST_MC_ADDR 0x15000000

void V1_draw(int VE_Source)
{

	unsigned int MC_C_chroma_offset = 0x2400;
	unsigned int MC_18_chroma_offset = 0x36A00;

    //0xb8005000
    WRITE_REG_INT32U(VO_MODE,
                     VO_MODE_ch2(1)|
                     VO_MODE_ch1(0)|
                     VO_MODE_write_data(0));

    //0xb8005000
    WRITE_REG_INT32U(VO_MODE,
                     VO_MODE_ch2(0)|
                     VO_MODE_ch1(1)|
                     VO_MODE_write_data(1));
                     
    //0xb8005004
    WRITE_REG_INT32U(VO_OUT,
                     VO_OUT_write_en3(1)|VO_OUT_h(1));
    //0xb8005008
    WRITE_REG_INT32U(VO_MIX12,
                     VO_MIX12_v1(1));


	if(VE_Source)
    { //0xb8005020
        WRITE_REG_INT32U(VO_V1,
                         VO_V1_ve_fmt(0)|
                         VO_V1_source(1)|
                          VO_V1_seq(1)|
                         VO_V1_f422(0)|  //cwww
                         VO_V1_write_data(1));
#if CW_DEBUG
        unsigned int vo_v1_mc0 =         READ_REG_INT32U(VO_V1_MC_0);
		printf("@@@ VO_V1_MC_0:%x \n",vo_v1_mc0);
#endif

		WRITE_REG_INT32U(VO_V1_MC_0, VO_V1_MC_0_int_mask(0)| VO_V1_MC_0_run(0));
		WRITE_REG_INT32U(VO_V1_MC_4, VO_V1_MC_4_done(0));
	
		WRITE_REG_INT32U(VO_V1_MC_8, VO_V1_MC_8_luma_offset_sa(TEST_MC_OFFSET_ADDR));
		WRITE_REG_INT32U(VO_V1_MC_C, VO_V1_MC_C_chroma_offset_sa(TEST_MC_OFFSET_ADDR+ MC_C_chroma_offset));
		WRITE_REG_INT32U(VO_V1_MC_10, VO_V1_MC_10_luma_height(288)|VO_V1_MC_10_chroma_height(144));
		WRITE_REG_INT32U(VO_V1_MC_14, VO_V1_MC_14_luma_sa(TEST_MC_ADDR));
		WRITE_REG_INT32U(VO_V1_MC_18, VO_V1_MC_18_chroma_sa(TEST_MC_ADDR+MC_18_chroma_offset));

		WRITE_REG_INT32U(VO_V1_MC_1C, VO_V1_MC_1C_luma_pitch(2880)|VO_V1_MC_1C_chroma_pitch(1440));
		WRITE_REG_INT32U(VO_V1_MC_20, VO_V1_MC_20_x_pos(0)|VO_V1_MC_20_y_pos(0));
		WRITE_REG_INT32U(VO_V1_MC_24, VO_V1_MC_24_x_size(720)|VO_V1_MC_24_y_size(288));
		WRITE_REG_INT32U(VO_V1_MC_28, VO_V1_MC_28_luma_out_mode(0)|VO_V1_MC_28_chroma_out_mode(0)|VO_V1_MC_28_hsync_period(10));
		WRITE_REG_INT32U(VO_V1_MC_30, VO_V1_MC_30_offset_endian(0)|VO_V1_MC_30_data_endian(0));
		WRITE_REG_INT32U(VO_V1_TILE, VO_V1_TILE_mc_f422(0)|VO_V1_TILE_data_endian(1)|VO_V1_TILE_size(0));

		WRITE_REG_INT32U(VO_V1_SIZE,
                         VO_V1_SIZE_w(720)|
                         VO_V1_SIZE_h(288));
		         //0xb8005610
        WRITE_REG_INT32U(VO_V1_XY,
                         VO_V1_XY_x(0)|
                         VO_V1_XY_y(0));
                //0xb8005604
       WRITE_REG_INT32U(VO_M1_SIZE,
                     VO_M1_SIZE_w(720)|
                     VO_M1_SIZE_h(288));                 
	 }else{
        WRITE_REG_INT32U(VO_V1,
                         VO_V1_ve_fmt(0)|
                         VO_V1_source(0)|
                          VO_V1_seq(1)|
                         VO_V1_f422(0)|  //cwww
                         VO_V1_write_data(1));
   		WRITE_REG_INT32U(VO_V1_SEQ_SA_C_Y, VO_V1_SEQ_SA_C_Y_a(TEST_Y_ADDR));

            //0xb800503c
        WRITE_REG_INT32U(VO_V1_SEQ_SA_C_C, VO_V1_SEQ_SA_C_C_a(TEST_C_ADDR));

			        //0xb8005048
        WRITE_REG_INT32U(VO_V1_SEQ_PITCH_C_Y, VO_V1_SEQ_PITCH_C_Y_p(720));
        //0xb800504c
        WRITE_REG_INT32U(VO_V1_SEQ_PITCH_C_C, VO_V1_SEQ_PITCH_C_C_p(720));
        //0xb8005068
        WRITE_REG_INT32U(VO_V1_SIZE,
                         VO_V1_SIZE_w(720)|
                         VO_V1_SIZE_h(576));
                        
        //0xb8005604
        WRITE_REG_INT32U(VO_M1_SIZE,
                         VO_M1_SIZE_w(720)|
                         VO_M1_SIZE_h(576));
                                 //0xb8005610
        WRITE_REG_INT32U(VO_V1_XY,
                         VO_V1_XY_x(0)|
                         VO_V1_XY_y(0));
	 }


#if 0

while(1)
{	
     if(HDMI_INTSTV_get_vsyncupdated(READ_REG_INT32U(HDMI_INTSTV)))
     {

#if CW_DEBUG
        unsigned int voinst =         READ_REG_INT32U(VO_INTST);

		printf("222 VO_INTST:%x \n",voinst);
#endif

		if(VE_Source)
		{

			WRITE_REG_INT32U(VO_V1_MC_0, VO_V1_MC_0_int_mask(0)| VO_V1_MC_0_run(0));
			WRITE_REG_INT32U(VO_V1_MC_4, VO_V1_MC_4_done(1));

		}	

	//0xb800d278
                WRITE_REG_INT32U(HDMI_INTSTV,
                                 HDMI_INTSTV_vendupdated(0)|
                                 HDMI_INTSTV_vsyncupdated(0));
     //0x98005e84
                WRITE_REG_INT32U(VO_INTST,
                                 VO_INTST_afbc_parser_fail(0)|
                                 VO_INTST_afbc_decode_fail(0)|
                                 VO_INTST_h_under(0)|
                                 VO_INTST_i_under(0)|
                                 VO_INTST_p_under(0)|
                                 VO_INTST_sub2(0)|
                                 VO_INTST_sub1(0)|
                                 VO_INTST_wb2fin(0)|
                                 VO_INTST_wb1fin(0)|
                                 VO_INTST_m3fin(0)|
                                 VO_INTST_m2fin(0)|
                                 VO_INTST_m1fin(1)|
                                 VO_INTST_write_data(0));
/*
	           //0x98005e84  cwww
                WRITE_REG_INT32U(VO_INTEN,
            
                                 VO_INTEN_h_under(1)|
                                 VO_INTEN_i_under(1)|
                                 VO_INTEN_sub2(1)|
                                 VO_INTEN_sub1(1)|
                                 VO_INTEN_wb2fin(1)|
                                 VO_INTEN_wb1fin(1)|
                                 VO_INTEN_m3fin(1)|
                                 VO_INTEN_m1fin(1)|
                                 VO_INTEN_write_data(1));
*/
   //0x98005e84  cwww
                WRITE_REG_INT32U(VO_INTEN,
                                 VO_INTEN_m1fin(1)|
                                 VO_INTEN_write_data(1));


				
                //0x98005020
                WRITE_REG_INT32U(VO_FC,
                                 VO_FC_wb2go(0)|
                                 VO_FC_wb1go(0)|
                                 VO_FC_mddgo(0)|
                                 VO_FC_m2go(0)|
                                 VO_FC_m1go(1)|
                                 VO_FC_write_data(1));


					if(VO_INTST_get_h_under(READ_REG_INT32U(VO_INTST)))
        		{

#if CW_DEBUG
					 printf("#@@ VO_INTST:get h_under \n");
#endif
					//0x98005e84
                        WRITE_REG_INT32U(VO_INTST,
                                         VO_INTST_afbc_parser_fail(0)|
                                         VO_INTST_afbc_decode_fail(0)|
                                         VO_INTST_h_under(1)|
                                         VO_INTST_i_under(0)|
                                         VO_INTST_p_under(0)|
                                         VO_INTST_sub2(0)|
                                         VO_INTST_sub1(0)|
                                         VO_INTST_wb2fin(0)|
                                         VO_INTST_wb1fin(0)|
                                         VO_INTST_m3fin(0)|
                                         VO_INTST_m2fin(0)|
                                         VO_INTST_m1fin(0)|
                                         VO_INTST_write_data(0));
	  		}
     }

}
#endif 
}


void SET_HDMI_Video_576p(int Pixel_Colocr_Format, int DVI_or_HDMI, int Deep_Color, int Deep_Depth, int xv_YCC, int Timing_Gen, int Enable_3D, int Format_3D)
{
	
    //0xb800d034
    WRITE_REG_INT32U(HDMI_CR,
                     HDMI_CR_write_en3(1)|HDMI_CR_tmds_encen(0)|                  
                     HDMI_CR_write_en1(1)|HDMI_CR_enablehdmi(0));
    //0xb800d0bc
    WRITE_REG_INT32U(HDMI_ICR,
                     HDMI_ICR_write_en3(1)|HDMI_ICR_enaudio(0)|
                     HDMI_ICR_write_en2(1)|HDMI_ICR_envitd(0)|
                     HDMI_ICR_write_en1(0)|HDMI_ICR_vitd(0));

    if(!DVI_or_HDMI) //DVI mode=================================================
    {
        //CRT & PHY config
        //TMDS_27MHz(0, 0, 0, 0);
        WRITE_REG_INT32U(0x9800d144,0x070c7d82);
        WRITE_REG_INT32U(0x9800d148,0x00040504);
        WRITE_REG_INT32U(0x9800d148,0x00000504);

        //Timming setting
        if(Timing_Gen)
        {
        	
            //0xb800d234
            WRITE_REG_INT32U(HDMI_H_PARA1,
                             HDMI_H_PARA1_hblank(143)|
                             HDMI_H_PARA1_hactive(719));
            //0xb800d238
            WRITE_REG_INT32U(HDMI_H_PARA2,
                             HDMI_H_PARA2_hsync(63)|
                             HDMI_H_PARA2_hfront(11));
            //0xb800d23c
            WRITE_REG_INT32U(HDMI_H_PARA3,
                             HDMI_H_PARA3_hback(67));
            //0xb800d240
            WRITE_REG_INT32U(HDMI_V_PARA1,
                             HDMI_V_PARA1_Vact_video(575)|
                             HDMI_V_PARA1_vactive(575));
            //0xb800d244
            WRITE_REG_INT32U(HDMI_V_PARA2,
                             HDMI_V_PARA2_Vact_space1(0)|
                             HDMI_V_PARA2_Vact_space(0));
            //0xb800d248
            WRITE_REG_INT32U(HDMI_V_PARA3,
                             HDMI_V_PARA3_Vblank3(0)|
                             HDMI_V_PARA3_Vact_space2(0));
            //0xb800d24c
            WRITE_REG_INT32U(HDMI_V_PARA4,
                             HDMI_V_PARA4_vsync((5<<1))|
                             HDMI_V_PARA4_vblank(48));
            //0xb800d250
            WRITE_REG_INT32U(HDMI_V_PARA5,
                             HDMI_V_PARA5_vback(38)|
                             HDMI_V_PARA5_vfront((5<<1)));
            //0xb800d254
            WRITE_REG_INT32U(HDMI_V_PARA6,
                             HDMI_V_PARA6_Vsync1((0<<1))|
                             HDMI_V_PARA6_Vblank1(0));
            //0xb800d258
            WRITE_REG_INT32U(HDMI_V_PARA7,
                             HDMI_V_PARA7_Vback1(0)|
                             HDMI_V_PARA7_Vfront1((0<<1)));
            //0xb800d25c
            WRITE_REG_INT32U(HDMI_V_PARA8,
                             HDMI_V_PARA8_Vsync2((0<<1))|
                             HDMI_V_PARA8_Vblank2(0));
            //0xb800d260
            WRITE_REG_INT32U(HDMI_V_PARA9,
                             HDMI_V_PARA9_Vback2(0)|
                             HDMI_V_PARA9_Vfront2((0<<1)));
            //0xb800d26c
            WRITE_REG_INT32U(HDMI_V_PARA10,
                             HDMI_V_PARA10_G(0x00beef));
            //0xb800d270
            WRITE_REG_INT32U(HDMI_V_PARA11,
                             HDMI_V_PARA11_B(0x00beef)|
                             HDMI_V_PARA11_R(0x00beef));
            //0xb800d264
            WRITE_REG_INT32U(HDMI_V_PARA12,
                             HDMI_V_PARA12_vsynci((0<<1))|
                             HDMI_V_PARA12_vblanki(0));
            //0xb800d268
            WRITE_REG_INT32U(HDMI_V_PARA13,
                             HDMI_V_PARA13_vbacki(0)|
                             HDMI_V_PARA13_vfronti((0<<1)));
            //0xb800d030
            WRITE_REG_INT32U(HDMI_SYNC_DLY,
                             HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                             HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                             HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                             HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
            //0xb800d154
            WRITE_REG_INT32U(HDMI_DPC,
                             HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(1)|
                             HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(0)|
                             HDMI_DPC_write_en7(1)|HDMI_DPC_fp(0)|
                             HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                             HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(1)|
                             HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(0)|
                             HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(0));
        }
        else
        {
        }
    }
    else //HDMI mode============================================================
    {
        //CRT & PHY config
        //TMDS_27MHz(Deep_Color, Deep_Depth, Enable_3D, Format_3D);

        //Timming setting
        if(Timing_Gen)
        {
            //0xb800d234
            WRITE_REG_INT32U(HDMI_H_PARA1,
                             HDMI_H_PARA1_hblank(143)|
                             HDMI_H_PARA1_hactive(719));
            //0xb800d238
            WRITE_REG_INT32U(HDMI_H_PARA2,
                             HDMI_H_PARA2_hsync(63)|
                             HDMI_H_PARA2_hfront(11));
            //0xb800d23c
            WRITE_REG_INT32U(HDMI_H_PARA3,
                             HDMI_H_PARA3_hback(67));
            if(Enable_3D)
            {
                switch(Format_3D)
                {
                    case 0:
                        //0xb800d240
                        WRITE_REG_INT32U(HDMI_V_PARA1,
                                         HDMI_V_PARA1_Vact_video(575)|
                                         HDMI_V_PARA1_vactive(1200));
                        //0xb800d244
                        WRITE_REG_INT32U(HDMI_V_PARA2,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(48));
                        break;
                    case 6:
                    case 8:
                        //0xb800d240
                        WRITE_REG_INT32U(HDMI_V_PARA1,
                                         HDMI_V_PARA1_Vact_video(575)|
                                         HDMI_V_PARA1_vactive(575));
                        //0xb800d244
                        WRITE_REG_INT32U(HDMI_V_PARA2,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        break;
                    default:
                        break;
                }
            }
            else
            {
                //0xb800d240
                WRITE_REG_INT32U(HDMI_V_PARA1,
                                 HDMI_V_PARA1_Vact_video(575)|
                                 HDMI_V_PARA1_vactive(575));
                //0xb800d244
                WRITE_REG_INT32U(HDMI_V_PARA2,
                                 HDMI_V_PARA2_Vact_space1(0)|
                                 HDMI_V_PARA2_Vact_space(0));
            }
            //0xb800d248
            WRITE_REG_INT32U(HDMI_V_PARA3,
                             HDMI_V_PARA3_Vblank3(0)|
                             HDMI_V_PARA3_Vact_space2(0));
            //0xb800d24c
            WRITE_REG_INT32U(HDMI_V_PARA4,
                             HDMI_V_PARA4_vsync((5<<1))|
                             HDMI_V_PARA4_vblank(48));
            //0xb800d250
            WRITE_REG_INT32U(HDMI_V_PARA5,
                             HDMI_V_PARA5_vback(38)|
                             HDMI_V_PARA5_vfront((5<<1)));
            //0xb800d254
            WRITE_REG_INT32U(HDMI_V_PARA6,
                             HDMI_V_PARA6_Vsync1((0<<1))|
                             HDMI_V_PARA6_Vblank1(0));
            //0xb800d258
            WRITE_REG_INT32U(HDMI_V_PARA7,
                             HDMI_V_PARA7_Vback1(0)|
                             HDMI_V_PARA7_Vfront1((0<<1)));
            //0xb800d25c
            WRITE_REG_INT32U(HDMI_V_PARA8,
                             HDMI_V_PARA8_Vsync2((0<<1))|
                             HDMI_V_PARA8_Vblank2(0));
            //0xb800d260
            WRITE_REG_INT32U(HDMI_V_PARA9,
                             HDMI_V_PARA9_Vback2(0)|
                             HDMI_V_PARA9_Vfront2((0<<1)));
            //0xb800d26c
            WRITE_REG_INT32U(HDMI_V_PARA10,
                             HDMI_V_PARA10_G(0x00beef));
            //0xb800d270
            WRITE_REG_INT32U(HDMI_V_PARA11,
                             HDMI_V_PARA11_B(0x00beef)|
                             HDMI_V_PARA11_R(0x00beef));
            //0xb800d264
            WRITE_REG_INT32U(HDMI_V_PARA12,
                             HDMI_V_PARA12_vsynci((0<<1))|
                             HDMI_V_PARA12_vblanki(0));
            //0xb800d268
            WRITE_REG_INT32U(HDMI_V_PARA13,
                             HDMI_V_PARA13_vbacki(0)|
                             HDMI_V_PARA13_vfronti((0<<1)));

            //Deep Color 24bit========================================================================================
            if(Deep_Color==0 || (Deep_Color==1 && Deep_Depth==4))
            {
                //0xb800d030
                WRITE_REG_INT32U(HDMI_SYNC_DLY,
                                 HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                                 HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                                 HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                                 HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
                //0xb800d154
                WRITE_REG_INT32U(HDMI_DPC,
                                 HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(1)|
                                 HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(0)|
                                 HDMI_DPC_write_en7(1)|HDMI_DPC_fp(0)|
                                 HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                                 HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(1)|
                                 HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(Deep_Depth)|
                                 HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(Deep_Color));
            }
            //Deep Color 30bit========================================================================================
            if(Deep_Color==1 && Deep_Depth==5)
            {
                //0xb800d030
                WRITE_REG_INT32U(HDMI_SYNC_DLY,
                                 HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                                 HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                                 HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                                 HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
                //0xb800d154
                WRITE_REG_INT32U(HDMI_DPC,
                                 HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(1)|
                                 HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(0)|
                                 HDMI_DPC_write_en7(1)|HDMI_DPC_fp(0)|
                                 HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                                 HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(1)|
                                 HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(Deep_Depth)|
                                 HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(Deep_Color));
            }
            //Deep Color 36bit========================================================================================
            if(Deep_Color==1 && Deep_Depth==6)
            {
                //0xb800d030
                WRITE_REG_INT32U(HDMI_SYNC_DLY,
                                 HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                                 HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                                 HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                                 HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
                //0xb800d154
                WRITE_REG_INT32U(HDMI_DPC,
                                 HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(1)|
                                 HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(0)|
                                 HDMI_DPC_write_en7(1)|HDMI_DPC_fp(0)|
                                 HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                                 HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(1)|
                                 HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(Deep_Depth)|
                                 HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(Deep_Color));
            }
        }
        else
        {
        }
    }

    //=====================================================================================================
    // HDMI Control
    //=====================================================================================================
    if(Timing_Gen)
    {
        //0xb800d020
        WRITE_REG_INT32U(HDMI_CHNL_SEL,
                         HDMI_CHNL_SEL_video_sd(1)|
                         HDMI_CHNL_SEL_Interlaced_vfmt(0)|
                         HDMI_CHNL_SEL_3D_video_format(Format_3D)|
                         HDMI_CHNL_SEL_En_3D(Enable_3D)|
                         HDMI_CHNL_SEL_timing_gen_en(1)|
                         HDMI_CHNL_SEL_chl_sel(0));
    }
    else
    {
    }

    if(DVI_or_HDMI==0) //DVI mode
        Pixel_Colocr_Format = 0;
    
    if(Pixel_Colocr_Format==0) //RGB mode
    {
        //-- Color Transform (YCbCr 4:4:4 -> RGB 4:4:4)
        //0xb800d024
        WRITE_REG_INT32U(HDMI_CS_TRANS0, HDMI_CS_TRANS0_c1(0x04a80));
        //0xb800d028
        WRITE_REG_INT32U(HDMI_CS_TRANS1, HDMI_CS_TRANS1_c2(0x1e700));
        //0xb800d02c
        WRITE_REG_INT32U(HDMI_CS_TRANS2, HDMI_CS_TRANS2_c3(0x1cc40));
        //0xb800d200
        WRITE_REG_INT32U(HDMI_CS_TRANS3, HDMI_CS_TRANS3_c4(0x04a80));
        //0xb800d204
        WRITE_REG_INT32U(HDMI_CS_TRANS4, HDMI_CS_TRANS4_c5(0x08140));
        //0xb800d208
        WRITE_REG_INT32U(HDMI_CS_TRANS5, HDMI_CS_TRANS5_c6(0x00000));
        //0xb800d20c
        WRITE_REG_INT32U(HDMI_CS_TRANS6, HDMI_CS_TRANS6_c7(0x04a80));
        //0xb800d210
        WRITE_REG_INT32U(HDMI_CS_TRANS7, HDMI_CS_TRANS7_c8(0x00000));
        //0xb800d214
        WRITE_REG_INT32U(HDMI_CS_TRANS8, HDMI_CS_TRANS8_c9(0x06680));
        //0xb800d218
        WRITE_REG_INT32U(HDMI_CS_TRANS9, HDMI_CS_TRANS9_k1(0x21b0));
        //0xb800d21c
        WRITE_REG_INT32U(HDMI_CS_TRANS10, HDMI_CS_TRANS10_k2(0xba70));
        //0xb800d220
        WRITE_REG_INT32U(HDMI_CS_TRANS11, HDMI_CS_TRANS11_k3(0xc840));
    }
    else //YCbCr mode
    {
        //-- Color Transform (YCbCr 4:4:4 -> RGB 4:4:4)
        //0xb800d024
        WRITE_REG_INT32U(HDMI_CS_TRANS0, HDMI_CS_TRANS0_c1(0x04000));
        //0xb800d028
        WRITE_REG_INT32U(HDMI_CS_TRANS1, HDMI_CS_TRANS1_c2(0x00000));
        //0xb800d02c
        WRITE_REG_INT32U(HDMI_CS_TRANS2, HDMI_CS_TRANS2_c3(0x00000));
        //0xb800d200
        WRITE_REG_INT32U(HDMI_CS_TRANS3, HDMI_CS_TRANS3_c4(0x00000));
        //0xb800d204
        WRITE_REG_INT32U(HDMI_CS_TRANS4, HDMI_CS_TRANS4_c5(0x04000));
        //0xb800d208
        WRITE_REG_INT32U(HDMI_CS_TRANS5, HDMI_CS_TRANS5_c6(0x00000));
        //0xb800d20c
        WRITE_REG_INT32U(HDMI_CS_TRANS6, HDMI_CS_TRANS6_c7(0x00000));
        //0xb800d210
        WRITE_REG_INT32U(HDMI_CS_TRANS7, HDMI_CS_TRANS7_c8(0x00000));
        //0xb800d214
        WRITE_REG_INT32U(HDMI_CS_TRANS8, HDMI_CS_TRANS8_c9(0x04000));
        //0xb800d218
        WRITE_REG_INT32U(HDMI_CS_TRANS9, HDMI_CS_TRANS9_k1(0x0000));
        //0xb800d21c
        WRITE_REG_INT32U(HDMI_CS_TRANS10, HDMI_CS_TRANS10_k2(0x0000));
        //0xb800d220
        WRITE_REG_INT32U(HDMI_CS_TRANS11, HDMI_CS_TRANS11_k3(0x0000));
    }

    //0xb800d0b8
    WRITE_REG_INT32U(HDMI_SCHCR,
                     HDMI_SCHCR_write_en10(1)|
                     HDMI_SCHCR_422_pixel_repeat(0));
    //0xb800d078
    WRITE_REG_INT32U(HDMI_GCPCR,
                     HDMI_GCPCR_enablegcp(1)|
                     HDMI_GCPCR_gcp_clearavmute(0)|
                     HDMI_GCPCR_gcp_setavmute(0)|
                     HDMI_GCPCR_write_data(0));
    //0xb800d078
    WRITE_REG_INT32U(HDMI_GCPCR,
                     HDMI_GCPCR_enablegcp(1)|
                     HDMI_GCPCR_gcp_clearavmute(0)|
                     HDMI_GCPCR_gcp_setavmute(0)|
                     HDMI_GCPCR_write_data(1));
    //0xb800d0a0
    WRITE_REG_INT32U(HDMI_RPCR,
                     HDMI_RPCR_write_en6(1)|HDMI_RPCR_prp5period(0)| //unuse
                     HDMI_RPCR_write_en5(1)|HDMI_RPCR_prp4period(0)| //unuse
                     HDMI_RPCR_write_en4(1)|HDMI_RPCR_prp3period(0)| //Vendor Specific InfoFrame package use
                     HDMI_RPCR_write_en3(1)|HDMI_RPCR_prp2period(0)| //Metadata package use
                     HDMI_RPCR_write_en2(0)|HDMI_RPCR_prp1period(0)| //Audio InfoFrame package use by HDMI_audio_set
                     HDMI_RPCR_write_en1(1)|HDMI_RPCR_prp0period(0)); //AVI InfoFrame package use
    //0xb800d0a4
    WRITE_REG_INT32U(HDMI_RPEN,
                     HDMI_RPEN_enprpkt5(1)| //unuse
                     HDMI_RPEN_enprpkt4(1)| //unuse
                     HDMI_RPEN_enprpkt3(1)| //Vendor Specific InfoFrame package clear
                     HDMI_RPEN_enprpkt2(1)| //Metadata package clear
                     HDMI_RPEN_enprpkt1(0)| //Audio InfoFrame package clear by HDMI_audio_set
                     HDMI_RPEN_enprpkt0(1)| //AVI InfoFrame package clear
                     HDMI_RPEN_write_data(0));
    //0xb800d0b4
    WRITE_REG_INT32U(HDMI_DIPCCR,
                     HDMI_DIPCCR_write_en2(1)|HDMI_DIPCCR_vbidipcnt(17)|//ver. max 18 packets
                     HDMI_DIPCCR_write_en1(1)|HDMI_DIPCCR_hbidipcnt(1));//hor. max 2 packets

    //=====================================================================================================
    // Scheduler
    //=====================================================================================================
    if(DVI_or_HDMI==0) //DVI mode
    {
        //0xb800d0b8
        WRITE_REG_INT32U(HDMI_SCHCR,
                         HDMI_SCHCR_write_en12(1)|HDMI_SCHCR_color_transform_en(1)|
                         HDMI_SCHCR_write_en11(0)|HDMI_SCHCR_ycbcr422_algo(0)|
                         HDMI_SCHCR_write_en10(0)|HDMI_SCHCR_422_pixel_repeat(0)|
                         HDMI_SCHCR_write_en9(0)|HDMI_SCHCR_vsyncpolin(0)|
                         HDMI_SCHCR_write_en8(0)|HDMI_SCHCR_hsyncpolin(0)|
                         HDMI_SCHCR_write_en7(1)|HDMI_SCHCR_vsyncpolinv(1)|
                         HDMI_SCHCR_write_en6(1)|HDMI_SCHCR_hsyncpolinv(1)|
                         HDMI_SCHCR_write_en5(1)|HDMI_SCHCR_pixelencycbcr422(0)|
                         HDMI_SCHCR_write_en4(1)|HDMI_SCHCR_hdmi_videoxs(0)|
                         HDMI_SCHCR_write_en3(1)|HDMI_SCHCR_pixelencfmt(0)| //RGB444
                         HDMI_SCHCR_write_en2(1)|HDMI_SCHCR_pixelrepeat(0)|
                         HDMI_SCHCR_write_en1(1)|HDMI_SCHCR_hdmi_modesel(0));
    }
    else //HDMI mode
    {
        //0xb800d0b8
        WRITE_REG_INT32U(HDMI_SCHCR,
                         HDMI_SCHCR_write_en12(1)|HDMI_SCHCR_color_transform_en(1)|
                         HDMI_SCHCR_write_en11(0)|HDMI_SCHCR_ycbcr422_algo(0)|
                         HDMI_SCHCR_write_en10(0)|HDMI_SCHCR_422_pixel_repeat(0)|
                         HDMI_SCHCR_write_en9(0)|HDMI_SCHCR_vsyncpolin(0)|
                         HDMI_SCHCR_write_en8(0)|HDMI_SCHCR_hsyncpolin(0)|
                         HDMI_SCHCR_write_en7(1)|HDMI_SCHCR_vsyncpolinv(1)|
                         HDMI_SCHCR_write_en6(1)|HDMI_SCHCR_hsyncpolinv(1)|
                         HDMI_SCHCR_write_en5(1)|HDMI_SCHCR_pixelencycbcr422(0)|
                         HDMI_SCHCR_write_en4(1)|HDMI_SCHCR_hdmi_videoxs(0)|
                         HDMI_SCHCR_write_en3(1)|HDMI_SCHCR_pixelencfmt(Pixel_Colocr_Format)|
                         HDMI_SCHCR_write_en2(1)|HDMI_SCHCR_pixelrepeat(0)|
                         HDMI_SCHCR_write_en1(1)|HDMI_SCHCR_hdmi_modesel(1));
    }

    //0xb800d0f0
    WRITE_REG_INT32U(HDMI_HDCP_KOWR, HDMI_HDCP_KOWR_hdcprekeykeepoutwin(0x2a));

    //0xb800d000
    WRITE_REG_INT32U(HDMI_INTEN,
                     HDMI_INTEN_enriupdint(1)|
                     HDMI_INTEN_enpjupdint(1)|
                     HDMI_INTEN_write_data(0));


/*cww
    if(DVI_or_HDMI) HDMI_gen_avi_infoframe(17, Pixel_Colocr_Format, xv_YCC);

    if(DVI_or_HDMI && xv_YCC) HDMI_gen_metadata();

    if(DVI_or_HDMI && Enable_3D) HDMI_gen_vendor_Specific_infoframe(1, Format_3D, 0, 0);
*/
    //0xb800d034
    WRITE_REG_INT32U(HDMI_CR,
                     HDMI_CR_write_en3(1)|HDMI_CR_tmds_encen(1)|
                     HDMI_CR_write_en1(1)|HDMI_CR_enablehdmi(1));
    return;
}

void TMDS_74MHz(int Deep_Color, int Deep_Depth, int En_3D, int Format_3D)
{
    //CRT & PHY config
    //Deep Color 24bit==========================================================
    if(Deep_Color==0 || (Deep_Color==1 && Deep_Depth==4))
    {
        if(En_3D==1 && Format_3D==0) //PIXEL=148.5MHz, TMDS=148.5MHz
        {
        }
        else  //PIXEL=74.25MHz, TMDS=74.25MHz
        {
            WRITE_REG_INT32U(0x98000204,0x93680013);
            WRITE_REG_INT32U(0x98000208,0x90200ffe);
            WRITE_REG_INT32U(0x9800021c,0x00000000);
            WRITE_REG_INT32U(0x98000220,0x00800000);
            WRITE_REG_INT32U(0x98000208,0x90200fff);
            WRITE_REG_INT32U(0x98000230,0x0000000F);
            WRITE_REG_INT32U(0x98000234,0x000000F0);
            WRITE_REG_INT32U(0x98000238,0x00249000);
            WRITE_REG_INT32U(0x9800023C,0x0004c092);
            WRITE_REG_INT32U(0x98000240,0x00000002);
            WRITE_REG_INT32U(0x98000194,0x00060232);
            msleep(1000);
        }
    }
    //Deep Color 30bit==========================================================
    if(Deep_Color==1 && Deep_Depth==5)
    {
        if(En_3D==1 && Format_3D==0) //PIXEL=148.5MHz, TMDS=185.625MHz
        {
        }
        else //PIXEL=74.25MHz, TMDS=92.8125MHz
        {
        }
    }
    //Deep Color 36bit==========================================================
    if(Deep_Color==1 && Deep_Depth==6)
    {
        if(En_3D==1 && Format_3D==0) //PIXEL=148.5MHz, TMDS=222.75MHz
        {
        }
        else //PIXEL=74.25MHz, TMDS=111.375MHz
        {
        }
    }
}

void SET_HDMI_Video_720p60(int Pixel_Colocr_Format, int DVI_or_HDMI, int Deep_Color, int Deep_Depth, int xv_YCC, int Timing_Gen, int Enable_3D, int Format_3D)
{
    //0xb800d034
    WRITE_REG_INT32U(HDMI_CR,
                     HDMI_CR_write_en3(1)|HDMI_CR_tmds_encen(0)|
                     HDMI_CR_write_en1(1)|HDMI_CR_enablehdmi(0));
    //0xb800d0bc
    WRITE_REG_INT32U(HDMI_ICR,
                     HDMI_ICR_write_en3(1)|HDMI_ICR_enaudio(0)|
                     HDMI_ICR_write_en2(1)|HDMI_ICR_envitd(0)|
                     HDMI_ICR_write_en1(0)|HDMI_ICR_vitd(0));

    if(!DVI_or_HDMI) //DVI mode=================================================
    {
        //CRT & PHY config
        TMDS_74MHz(0, 0, 0, 0);

        //Timming setting
        if(Timing_Gen)
        {
            //0xb800d234
            WRITE_REG_INT32U(HDMI_H_PARA1,
                             HDMI_H_PARA1_hblank(369)|
                             HDMI_H_PARA1_hactive(1279));
            //0xb800d238
            WRITE_REG_INT32U(HDMI_H_PARA2,
                             HDMI_H_PARA2_hsync(39)|
                             HDMI_H_PARA2_hfront(109));
            //0xb800d23c
            WRITE_REG_INT32U(HDMI_H_PARA3,
                             HDMI_H_PARA3_hback(219));
            //0xb800d240
            WRITE_REG_INT32U(HDMI_V_PARA1,
                             HDMI_V_PARA1_Vact_video(719)|
                             HDMI_V_PARA1_vactive(719));
            //0xb800d244
            WRITE_REG_INT32U(HDMI_V_PARA2,
                             HDMI_V_PARA2_Vact_space1(0)|
                             HDMI_V_PARA2_Vact_space(0));
            //0xb800d248
            WRITE_REG_INT32U(HDMI_V_PARA3,
                             HDMI_V_PARA3_Vblank3(0)|
                             HDMI_V_PARA3_Vact_space2(0));
            //0xb800d24c
            WRITE_REG_INT32U(HDMI_V_PARA4,
                             HDMI_V_PARA4_vsync((5<<1))|
                             HDMI_V_PARA4_vblank(29));
            //0xb800d250
            WRITE_REG_INT32U(HDMI_V_PARA5,
                             HDMI_V_PARA5_vback(19)|
                             HDMI_V_PARA5_vfront((5<<1)));
            //0xb800d254
            WRITE_REG_INT32U(HDMI_V_PARA6,
                             HDMI_V_PARA6_Vsync1((0<<1))|
                             HDMI_V_PARA6_Vblank1(0));
            //0xb800d258
            WRITE_REG_INT32U(HDMI_V_PARA7,
                             HDMI_V_PARA7_Vback1(0)|
                             HDMI_V_PARA7_Vfront1((0<<1)));
            //0xb800d25c
            WRITE_REG_INT32U(HDMI_V_PARA8,
                             HDMI_V_PARA8_Vsync2((0<<1))|
                             HDMI_V_PARA8_Vblank2(0));
            //0xb800d260
            WRITE_REG_INT32U(HDMI_V_PARA9,
                             HDMI_V_PARA9_Vback2(0)|
                             HDMI_V_PARA9_Vfront2((0<<1)));
            //0xb800d26c
            WRITE_REG_INT32U(HDMI_V_PARA10,
                             HDMI_V_PARA10_G(0x00beef));
            //0xb800d270
            WRITE_REG_INT32U(HDMI_V_PARA11,
                             HDMI_V_PARA11_B(0x00beef)|
                             HDMI_V_PARA11_R(0x00beef));
            //0xb800d264
            WRITE_REG_INT32U(HDMI_V_PARA12,
                             HDMI_V_PARA12_vsynci((0<<1))|
                             HDMI_V_PARA12_vblanki(0));
            //0xb800d268
            WRITE_REG_INT32U(HDMI_V_PARA13,
                             HDMI_V_PARA13_vbacki(0)|
                             HDMI_V_PARA13_vfronti((0<<1)));
            //0xb800d030
            WRITE_REG_INT32U(HDMI_SYNC_DLY,
                             HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                             HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                             HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                             HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
            //0xb800d154
            WRITE_REG_INT32U(HDMI_DPC,
                             HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(1)|
                             HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(0)|
                             HDMI_DPC_write_en7(1)|HDMI_DPC_fp(0)|
                             HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                             HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(1)|
                             HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(0)|
                             HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(0));
        }
        else
        {
        }
    }
    else //HDMI mode============================================================
    {
        //CRT & PHY config
        //TMDS_74MHz(Deep_Color, Deep_Depth, Enable_3D, Format_3D);

        //Timming setting
        if(Timing_Gen)
        {
            //0xb800d234
            WRITE_REG_INT32U(HDMI_H_PARA1,
                             HDMI_H_PARA1_hblank(369)|
                             HDMI_H_PARA1_hactive(1279));
            //0xb800d238
            WRITE_REG_INT32U(HDMI_H_PARA2,
                             HDMI_H_PARA2_hsync(39)|
                             HDMI_H_PARA2_hfront(109));
            //0xb800d23c
            WRITE_REG_INT32U(HDMI_H_PARA3,
                             HDMI_H_PARA3_hback(219));
            if(Enable_3D)
            {
                switch(Format_3D)
                {
                    case 0:
                        //0xb800d240
                        WRITE_REG_INT32U(HDMI_V_PARA1,
                                         HDMI_V_PARA1_Vact_video(719)|
                                         HDMI_V_PARA1_vactive(1469));
                        //0xb800d244
                        WRITE_REG_INT32U(HDMI_V_PARA2,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(29));
                        break;
                    case 6:
                    case 8:
                        //0xb800d240
                        WRITE_REG_INT32U(HDMI_V_PARA1,
                                         HDMI_V_PARA1_Vact_video(719)|
                                         HDMI_V_PARA1_vactive(719));
                        //0xb800d244
                        WRITE_REG_INT32U(HDMI_V_PARA2,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        break;
                    default:
                        break;
                }
            }
            else
            {
                //0xb800d240
                WRITE_REG_INT32U(HDMI_V_PARA1,
                                 HDMI_V_PARA1_Vact_video(719)|
                                 HDMI_V_PARA1_vactive(719));
                //0xb800d244
                WRITE_REG_INT32U(HDMI_V_PARA2,
                                 HDMI_V_PARA2_Vact_space1(0)|
                                 HDMI_V_PARA2_Vact_space(0));
            }
            //0xb800d248
            WRITE_REG_INT32U(HDMI_V_PARA3,
                             HDMI_V_PARA3_Vblank3(0)|
                             HDMI_V_PARA3_Vact_space2(0));
            //0xb800d24c
            WRITE_REG_INT32U(HDMI_V_PARA4,
                             HDMI_V_PARA4_vsync((5<<1))|
                             HDMI_V_PARA4_vblank(29));
            //0xb800d250
            WRITE_REG_INT32U(HDMI_V_PARA5,
                             HDMI_V_PARA5_vback(19)|
                             HDMI_V_PARA5_vfront((5<<1)));
            //0xb800d254
            WRITE_REG_INT32U(HDMI_V_PARA6,
                             HDMI_V_PARA6_Vsync1((0<<1))|
                             HDMI_V_PARA6_Vblank1(0));
            //0xb800d258
            WRITE_REG_INT32U(HDMI_V_PARA7,
                             HDMI_V_PARA7_Vback1(0)|
                             HDMI_V_PARA7_Vfront1((0<<1)));
            //0xb800d25c
            WRITE_REG_INT32U(HDMI_V_PARA8,
                             HDMI_V_PARA8_Vsync2((0<<1))|
                             HDMI_V_PARA8_Vblank2(0));
            //0xb800d260
            WRITE_REG_INT32U(HDMI_V_PARA9,
                             HDMI_V_PARA9_Vback2(0)|
                             HDMI_V_PARA9_Vfront2((0<<1)));
            //0xb800d26c
            WRITE_REG_INT32U(HDMI_V_PARA10,
                             HDMI_V_PARA10_G(0x00beef));
            //0xb800d270
            WRITE_REG_INT32U(HDMI_V_PARA11,
                             HDMI_V_PARA11_B(0x00beef)|
                             HDMI_V_PARA11_R(0x00beef));
            //0xb800d264
            WRITE_REG_INT32U(HDMI_V_PARA12,
                             HDMI_V_PARA12_vsynci((0<<1))|
                             HDMI_V_PARA12_vblanki(0));
            //0xb800d268
            WRITE_REG_INT32U(HDMI_V_PARA13,
                             HDMI_V_PARA13_vbacki(0)|
                             HDMI_V_PARA13_vfronti((0<<1)));

            //Deep Color 24bit========================================================================================
            if(Deep_Color==0 || (Deep_Color==1 && Deep_Depth==4))
            {
                //0xb800d030
                WRITE_REG_INT32U(HDMI_SYNC_DLY,
                                 HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                                 HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                                 HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                                 HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
                //0xb800d154
                WRITE_REG_INT32U(HDMI_DPC,
                                 HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(1)|
                                 HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(0)|
                                 HDMI_DPC_write_en7(1)|HDMI_DPC_fp(0)|
                                 HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                                 HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(1)|
                                 HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(Deep_Depth)|
                                 HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(Deep_Color));
            }
            //Deep Color 30bit========================================================================================
            if(Deep_Color==1 && Deep_Depth==5)
            {
                //0xb800d030
                WRITE_REG_INT32U(HDMI_SYNC_DLY,
                                 HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                                 HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                                 HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                                 HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
                //0xb800d154
                WRITE_REG_INT32U(HDMI_DPC,
                                 HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(3)|
                                 HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(1)|
                                 HDMI_DPC_write_en7(1)|HDMI_DPC_fp(2)|
                                 HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                                 HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(0)|
                                 HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(Deep_Depth)|
                                 HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(Deep_Color));
            }
            //Deep Color 36bit========================================================================================
            if(Deep_Color==1 && Deep_Depth==6)
            {
                //0xb800d030
                WRITE_REG_INT32U(HDMI_SYNC_DLY,
                                 HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                                 HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                                 HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                                 HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
                //0xb800d154
                WRITE_REG_INT32U(HDMI_DPC,
                                 HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(1)|
                                 HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(0)|
                                 HDMI_DPC_write_en7(1)|HDMI_DPC_fp(0)|
                                 HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                                 HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(1)|
                                 HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(Deep_Depth)|
                                 HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(Deep_Color));
            }
        }
        else
        {
        }
    }

    //=====================================================================================================
    // HDMI Control
    //=====================================================================================================
    if(Timing_Gen)
    {
        //0xb800d020
        WRITE_REG_INT32U(HDMI_CHNL_SEL,
                         HDMI_CHNL_SEL_video_sd(0)|
                         HDMI_CHNL_SEL_Interlaced_vfmt(0)|
                         HDMI_CHNL_SEL_3D_video_format(Format_3D)|
                         HDMI_CHNL_SEL_En_3D(Enable_3D)|
                         HDMI_CHNL_SEL_timing_gen_en(1)|
                         HDMI_CHNL_SEL_chl_sel(0));
    }
    else
    {
    }

    if(DVI_or_HDMI==0) //DVI mode
        Pixel_Colocr_Format = 0;
    
    if(Pixel_Colocr_Format==0) //RGB mode
    {
        //-- Color Transform (YCbCr 4:4:4 -> RGB 4:4:4)
        //0xb800d024
        WRITE_REG_INT32U(HDMI_CS_TRANS0, HDMI_CS_TRANS0_c1(0x04a80));
        //0xb800d028
        WRITE_REG_INT32U(HDMI_CS_TRANS1, HDMI_CS_TRANS1_c2(0x1e700));
        //0xb800d02c
        WRITE_REG_INT32U(HDMI_CS_TRANS2, HDMI_CS_TRANS2_c3(0x1cc40));
        //0xb800d200
        WRITE_REG_INT32U(HDMI_CS_TRANS3, HDMI_CS_TRANS3_c4(0x04a80));
        //0xb800d204
        WRITE_REG_INT32U(HDMI_CS_TRANS4, HDMI_CS_TRANS4_c5(0x08140));
        //0xb800d208
        WRITE_REG_INT32U(HDMI_CS_TRANS5, HDMI_CS_TRANS5_c6(0x00000));
        //0xb800d20c
        WRITE_REG_INT32U(HDMI_CS_TRANS6, HDMI_CS_TRANS6_c7(0x04a80));
        //0xb800d210
        WRITE_REG_INT32U(HDMI_CS_TRANS7, HDMI_CS_TRANS7_c8(0x00000));
        //0xb800d214
        WRITE_REG_INT32U(HDMI_CS_TRANS8, HDMI_CS_TRANS8_c9(0x06680));
        //0xb800d218
        WRITE_REG_INT32U(HDMI_CS_TRANS9, HDMI_CS_TRANS9_k1(0x21b0));
        //0xb800d21c
        WRITE_REG_INT32U(HDMI_CS_TRANS10, HDMI_CS_TRANS10_k2(0xba70));
        //0xb800d220
        WRITE_REG_INT32U(HDMI_CS_TRANS11, HDMI_CS_TRANS11_k3(0xc840));
    }
    else //YCbCr mode
    {
        //-- Color Transform (YCbCr 4:4:4 -> RGB 4:4:4)
        //0xb800d024
        WRITE_REG_INT32U(HDMI_CS_TRANS0, HDMI_CS_TRANS0_c1(0x04000));
        //0xb800d028
        WRITE_REG_INT32U(HDMI_CS_TRANS1, HDMI_CS_TRANS1_c2(0x00000));
        //0xb800d02c
        WRITE_REG_INT32U(HDMI_CS_TRANS2, HDMI_CS_TRANS2_c3(0x00000));
        //0xb800d200
        WRITE_REG_INT32U(HDMI_CS_TRANS3, HDMI_CS_TRANS3_c4(0x00000));
        //0xb800d204
        WRITE_REG_INT32U(HDMI_CS_TRANS4, HDMI_CS_TRANS4_c5(0x04000));
        //0xb800d208
        WRITE_REG_INT32U(HDMI_CS_TRANS5, HDMI_CS_TRANS5_c6(0x00000));
        //0xb800d20c
        WRITE_REG_INT32U(HDMI_CS_TRANS6, HDMI_CS_TRANS6_c7(0x00000));
        //0xb800d210
        WRITE_REG_INT32U(HDMI_CS_TRANS7, HDMI_CS_TRANS7_c8(0x00000));
        //0xb800d214
        WRITE_REG_INT32U(HDMI_CS_TRANS8, HDMI_CS_TRANS8_c9(0x04000));
        //0xb800d218
        WRITE_REG_INT32U(HDMI_CS_TRANS9, HDMI_CS_TRANS9_k1(0x0000));
        //0xb800d21c
        WRITE_REG_INT32U(HDMI_CS_TRANS10, HDMI_CS_TRANS10_k2(0x0000));
        //0xb800d220
        WRITE_REG_INT32U(HDMI_CS_TRANS11, HDMI_CS_TRANS11_k3(0x0000));
    }

    //0xb800d0b8
    WRITE_REG_INT32U(HDMI_SCHCR,
                     HDMI_SCHCR_write_en10(1)|
                     HDMI_SCHCR_422_pixel_repeat(0));
    //0xb800d078
    WRITE_REG_INT32U(HDMI_GCPCR,
                     HDMI_GCPCR_enablegcp(1)|
                     HDMI_GCPCR_gcp_clearavmute(0)|
                     HDMI_GCPCR_gcp_setavmute(0)|
                     HDMI_GCPCR_write_data(0));
    //0xb800d078
    WRITE_REG_INT32U(HDMI_GCPCR,
                     HDMI_GCPCR_enablegcp(1)|
                     HDMI_GCPCR_gcp_clearavmute(0)|
                     HDMI_GCPCR_gcp_setavmute(0)|
                     HDMI_GCPCR_write_data(1));
    //0xb800d0a0
    WRITE_REG_INT32U(HDMI_RPCR,
                     HDMI_RPCR_write_en6(1)|HDMI_RPCR_prp5period(0)| //unuse
                     HDMI_RPCR_write_en5(1)|HDMI_RPCR_prp4period(0)| //unuse
                     HDMI_RPCR_write_en4(1)|HDMI_RPCR_prp3period(0)| //Vendor Specific InfoFrame package use
                     HDMI_RPCR_write_en3(1)|HDMI_RPCR_prp2period(0)| //Metadata package use
                     HDMI_RPCR_write_en2(0)|HDMI_RPCR_prp1period(0)| //Audio InfoFrame package use by HDMI_audio_set
                     HDMI_RPCR_write_en1(1)|HDMI_RPCR_prp0period(0)); //AVI InfoFrame package use
    //0xb800d0a4
    WRITE_REG_INT32U(HDMI_RPEN,
                     HDMI_RPEN_enprpkt5(1)| //unuse
                     HDMI_RPEN_enprpkt4(1)| //unuse
                     HDMI_RPEN_enprpkt3(1)| //Vendor Specific InfoFrame package clear
                     HDMI_RPEN_enprpkt2(1)| //Metadata package clear
                     HDMI_RPEN_enprpkt1(0)| //Audio InfoFrame package clear by HDMI_audio_set
                     HDMI_RPEN_enprpkt0(1)| //AVI InfoFrame package clear
                     HDMI_RPEN_write_data(0));
    //0xb800d0b4
    WRITE_REG_INT32U(HDMI_DIPCCR,
                     HDMI_DIPCCR_write_en2(1)|HDMI_DIPCCR_vbidipcnt(17)|//ver. max 18 packets
                     HDMI_DIPCCR_write_en1(1)|HDMI_DIPCCR_hbidipcnt(8));//hor. max 9 packets

    //=====================================================================================================
    // Scheduler
    //=====================================================================================================
    if(DVI_or_HDMI==0) //DVI mode
    {
        //0xb800d0b8
        WRITE_REG_INT32U(HDMI_SCHCR,
                         HDMI_SCHCR_write_en12(1)|HDMI_SCHCR_color_transform_en(1)|
                         HDMI_SCHCR_write_en11(0)|HDMI_SCHCR_ycbcr422_algo(0)|
                         HDMI_SCHCR_write_en10(0)|HDMI_SCHCR_422_pixel_repeat(0)|
                         HDMI_SCHCR_write_en9(0)|HDMI_SCHCR_vsyncpolin(0)|
                         HDMI_SCHCR_write_en8(0)|HDMI_SCHCR_hsyncpolin(0)|
                         HDMI_SCHCR_write_en7(1)|HDMI_SCHCR_vsyncpolinv(0)|
                         HDMI_SCHCR_write_en6(1)|HDMI_SCHCR_hsyncpolinv(0)|
                         HDMI_SCHCR_write_en5(1)|HDMI_SCHCR_pixelencycbcr422(0)|
                         HDMI_SCHCR_write_en4(1)|HDMI_SCHCR_hdmi_videoxs(0)|
                         HDMI_SCHCR_write_en3(1)|HDMI_SCHCR_pixelencfmt(0)| //RGB444
                         HDMI_SCHCR_write_en2(1)|HDMI_SCHCR_pixelrepeat(0)|
                         HDMI_SCHCR_write_en1(1)|HDMI_SCHCR_hdmi_modesel(0));
    }
    else //HDMI mode
    {
        //0xb800d0b8
        WRITE_REG_INT32U(HDMI_SCHCR,
                         HDMI_SCHCR_write_en12(1)|HDMI_SCHCR_color_transform_en(1)|
                         HDMI_SCHCR_write_en11(0)|HDMI_SCHCR_ycbcr422_algo(0)|
                         HDMI_SCHCR_write_en10(0)|HDMI_SCHCR_422_pixel_repeat(0)|
                         HDMI_SCHCR_write_en9(0)|HDMI_SCHCR_vsyncpolin(0)|
                         HDMI_SCHCR_write_en8(0)|HDMI_SCHCR_hsyncpolin(0)|
                         HDMI_SCHCR_write_en7(1)|HDMI_SCHCR_vsyncpolinv(0)|
                         HDMI_SCHCR_write_en6(1)|HDMI_SCHCR_hsyncpolinv(0)|
                         HDMI_SCHCR_write_en5(1)|HDMI_SCHCR_pixelencycbcr422(0)|
                         HDMI_SCHCR_write_en4(1)|HDMI_SCHCR_hdmi_videoxs(0)|
                         HDMI_SCHCR_write_en3(1)|HDMI_SCHCR_pixelencfmt(Pixel_Colocr_Format)|
                         HDMI_SCHCR_write_en2(1)|HDMI_SCHCR_pixelrepeat(0)|
                         HDMI_SCHCR_write_en1(1)|HDMI_SCHCR_hdmi_modesel(1));
    }

    //0xb800d0f0
    WRITE_REG_INT32U(HDMI_HDCP_KOWR, HDMI_HDCP_KOWR_hdcprekeykeepoutwin(0x2a));

    //0xb800d000
    WRITE_REG_INT32U(HDMI_INTEN,
                     HDMI_INTEN_enriupdint(1)|
                     HDMI_INTEN_enpjupdint(1)|
                     HDMI_INTEN_write_data(0));

    /*
    if(DVI_or_HDMI) HDMI_gen_avi_infoframe(4, Pixel_Colocr_Format, xv_YCC);

    if(DVI_or_HDMI && xv_YCC) HDMI_gen_metadata();

    if(DVI_or_HDMI && Enable_3D) HDMI_gen_vendor_Specific_infoframe(1, Format_3D, 0, 0);
    */

    //0xb800d034
    WRITE_REG_INT32U(HDMI_CR,
                     HDMI_CR_write_en3(1)|HDMI_CR_tmds_encen(1)|
                     HDMI_CR_write_en1(1)|HDMI_CR_enablehdmi(1));
    return;
}




static irqreturn_t vo_irq_handler(int irq, void *dev_id)
{
   // vpu_drv_context_t *dev = (vpu_drv_context_t *)dev_id;

 
    HDMI_ISR();
    return IRQ_HANDLED;
//	if(VE_Source)
     if((READ_REG_INT32U(VO_V1)&0x2000000) != 0);
	{

			WRITE_REG_INT32U(VO_V1_MC_0, VO_V1_MC_0_int_mask(0)| VO_V1_MC_0_run(0));
			WRITE_REG_INT32U(VO_V1_MC_4, VO_V1_MC_4_done(1));

	}	

	//0xb800d278
                WRITE_REG_INT32U(HDMI_INTSTV,
                                 HDMI_INTSTV_vendupdated(0)|
                                 HDMI_INTSTV_vsyncupdated(0));
     //0x98005e84
                WRITE_REG_INT32U(VO_INTST,
                                 VO_INTST_afbc_parser_fail(0)|
                                 VO_INTST_afbc_decode_fail(0)|
                                 VO_INTST_h_under(0)|
                                 VO_INTST_i_under(0)|
                                 VO_INTST_p_under(0)|
                                 VO_INTST_sub2(0)|
                                 VO_INTST_sub1(0)|
                                 VO_INTST_wb2fin(0)|
                                 VO_INTST_wb1fin(0)|
                                 VO_INTST_m3fin(0)|
                                 VO_INTST_m2fin(0)|
                                 VO_INTST_m1fin(1)|
                                 VO_INTST_write_data(0));
/*
	           //0x98005e84  cwww
                WRITE_REG_INT32U(VO_INTEN,
            
                                 VO_INTEN_h_under(1)|
                                 VO_INTEN_i_under(1)|
                                 VO_INTEN_sub2(1)|
                                 VO_INTEN_sub1(1)|
                                 VO_INTEN_wb2fin(1)|
                                 VO_INTEN_wb1fin(1)|
                                 VO_INTEN_m3fin(1)|
                                 VO_INTEN_m1fin(1)|
                                 VO_INTEN_write_data(1));
*/
   //0x98005e84  cwww
                WRITE_REG_INT32U(VO_INTEN,
                                 VO_INTEN_m1fin(1)|
                                 VO_INTEN_write_data(1));


				
                //0x98005020
                WRITE_REG_INT32U(VO_FC,
                                 VO_FC_wb2go(0)|
                                 VO_FC_wb1go(0)|
                                 VO_FC_mddgo(0)|
                                 VO_FC_m2go(0)|
                                 VO_FC_m1go(1)|
                                 VO_FC_write_data(1));


					if(VO_INTST_get_h_under(READ_REG_INT32U(VO_INTST)))
        		{

#if CW_DEBUG
					 printf("#@@ VO_INTST:get h_under \n");
#endif
					//0x98005e84
                        WRITE_REG_INT32U(VO_INTST,
                                         VO_INTST_afbc_parser_fail(0)|
                                         VO_INTST_afbc_decode_fail(0)|
                                         VO_INTST_h_under(1)|
                                         VO_INTST_i_under(0)|
                                         VO_INTST_p_under(0)|
                                         VO_INTST_sub2(0)|
                                         VO_INTST_sub1(0)|
                                         VO_INTST_wb2fin(0)|
                                         VO_INTST_wb1fin(0)|
                                         VO_INTST_m3fin(0)|
                                         VO_INTST_m2fin(0)|
                                         VO_INTST_m1fin(0)|
                                         VO_INTST_write_data(0));
	  		}
    return IRQ_HANDLED;
}










static int vo_open(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "[TEST_VO][+] %s\n", __func__);
    printk(KERN_INFO "[TEST_VO][-] %s\n", __func__);

    return 0;
}

static int vo_release(struct inode *inode, struct file *filp)
{
    int ret = 0;

    printk(KERN_INFO "[TEST_VO] vo_release\n");

    return 0;
}

static int vo_map_to_register(struct file *fp, struct vm_area_struct *vm)
{
    printk(KERN_INFO "In[%s][%d]", __FUNCTION__, __LINE__);
    unsigned long pfn;

    vm->vm_flags |= VM_IO | VM_RESERVED;
    vm->vm_page_prot = pgprot_noncached(vm->vm_page_prot);
    pfn = s_vo_register.phys_addr >> PAGE_SHIFT;

    return remap_pfn_range(vm, vm->vm_start, pfn, vm->vm_end-vm->vm_start, vm->vm_page_prot) ? -EAGAIN : 0;
}

static int hdmi_map_to_register(struct file *fp, struct vm_area_struct *vm)
{
    printk(KERN_INFO "In[%s][%d]", __FUNCTION__, __LINE__);
    unsigned long pfn;

    vm->vm_flags |= VM_IO | VM_RESERVED;
    vm->vm_page_prot = pgprot_noncached(vm->vm_page_prot);
    pfn = s_hdmi_register.phys_addr >> PAGE_SHIFT;

    return remap_pfn_range(vm, vm->vm_start, pfn, vm->vm_end-vm->vm_start, vm->vm_page_prot) ? -EAGAIN : 0;
}

static int vo_mmap(struct file *fp, struct vm_area_struct *vm)
{
    printk(KERN_INFO "vm->vm_pgoff:0x%08x, (s_vo_register.phys_addr>>PAGE_SHIFT):0x%08x, (s_hdmi_register.phys_addr>>PAGE_SHIFT):0x%08x\n", vm->vm_pgoff, (s_vo_register.phys_addr>>PAGE_SHIFT), (s_hdmi_register.phys_addr>>PAGE_SHIFT));
    if ((unsigned int)vm->vm_pgoff == (unsigned int)(s_vo_register.phys_addr>>PAGE_SHIFT))
        return vo_map_to_register(fp, vm);
    else
        return hdmi_map_to_register(fp, vm);
}

struct file_operations vo_fops = {
    .owner = THIS_MODULE,
    .open = vo_open,
    .release = vo_release,
    .mmap = vo_mmap,
};

static int vo_probe(struct platform_device *pdev)
{
    int err = 0;
    struct resource res;
    printk(KERN_INFO "[TEST_VO] vo_probe\n");
	int irq;
    void __iomem *iobase;
    struct device_node *node = pdev->dev.of_node;

	void *hdmi_irq_dev_id = (void *)&s_hdmi_irq;   //cw:not sure


    of_address_to_resource(node, 0, &res);
    iobase = of_iomap(node, 0);

    s_vo_register.phys_addr = res.start;
    s_vo_register.virt_addr = (unsigned long)iobase;
    s_vo_register.size = res.end - res.start + 1;

	vo_virt_address = s_vo_register.virt_addr;
	
    printk(KERN_INFO "[TEST_VO] : vo base address get from DTB physical base addr=0x%x, virtual base=0x%x, size=0x%x\n", s_vo_register.phys_addr , s_vo_register.virt_addr, s_vo_register.size);

    of_address_to_resource(node, 1, &res);
    iobase = of_iomap(node, 1);

    s_hdmi_register.phys_addr = res.start;
    s_hdmi_register.virt_addr = (unsigned long)iobase;
    s_hdmi_register.size = res.end - res.start + 1;

	hdmi_virt_address = s_hdmi_register.virt_addr;
	
    printk(KERN_INFO "[TEST_VO] : hdmi base address get from DTB physical base addr=0x%x, virtual base=0x%x, size=0x%x\n", s_hdmi_register.phys_addr , s_hdmi_register.virt_addr, s_hdmi_register.size);

    of_address_to_resource(node, 2, &res);
    iobase = of_iomap(node, 2);

    s_rbus_register.phys_addr = res.start;
    s_rbus_register.virt_addr = (unsigned long)iobase;
    s_rbus_register.size = res.end - res.start + 1;

	rbus_virt_address = s_rbus_register.virt_addr;
	
    printk(KERN_INFO "[TEST_VO] : rbus base address get from DTB physical base addr=0x%x, virtual base=0x%x, size=0x%x\n", s_rbus_register.phys_addr , s_rbus_register.virt_addr, s_rbus_register.size);


    irq = irq_of_parse_and_map(node, 0);
    if (irq <= 0)
        panic("Can't parse IRQ");

    s_hdmi_irq = irq;
    DPRINTK("s_hdmi_irq:%d want to register VO_ISR\n", s_hdmi_irq);

   
/*
    irq = platform_get_irq(pdev, 0);
    s_hdmi_irq = irq;
*/
	
	
    DPRINTK("platform_get_irq -> irq:%d\n", irq);
    err = request_irq(s_hdmi_irq, vo_irq_handler, 0, "VO_HDMI_IRQ", (void *)(&hdmi_irq_dev_id));
    if (err != 0)
    {
        if(err == -EINVAL)
        {
            printk(KERN_ERR "[VPUDRV] : Bad s_hdmi_irq number or handler\n");
        }
        else if(err == -EBUSY)
        {
            printk(KERN_ERR "[VPUDRV] : s_hdmi_irq <%d> busy, change your config\n", s_hdmi_irq);
        }
    }
    
    s_vo_dev.minor = MISC_DYNAMIC_MINOR;
    s_vo_dev.name = "test_vo";
    s_vo_dev.fops = &vo_fops;
    s_vo_dev.parent = NULL;
    if (misc_register(&s_vo_dev)) {
        printk("TEST_VO: failed to register misc device.");
        goto ERROR_PROVE_DEVICE;
    }

    static int temp = 0;
    if (temp == 0) {
        //SET_HDMI_Video_576p(0, 0, 0, 0, 0, 1, 0, 0);
        SET_HDMI_Video_720p60(0, 0, 0, 0, 0, 1, 0, 0);
        msleep(1);
        temp=1;
    }

#if 0
    brook_task = kthread_create(kbrook, &brook_data, "brook");
    if (IS_ERR(brook_task)) {
        brook_task = NULL;
        printk("[%s %d] ERROR!\n",__func__,__LINE__);
    } 

    wake_up_process(brook_task);
#endif
    
    //////
	OSD_draw(1280, 720, 0x22000000);
    //V1_draw(0);

    // set hdmi
	DPRINTK("SET_HDMI_Video_720p\n");

    return 0;


ERROR_PROVE_DEVICE:

    misc_deregister(&s_vo_dev);

    return err;
}

static int vo_remove(struct platform_device *pdev)
{
    printk(KERN_INFO "[TEST_VO] vo_remove\n");

    misc_deregister(&s_vo_dev);

    return 0;
}

static int __init vo_init(void)
{
    int res = 0;

    printk(KERN_INFO "[TEST_VO] begin vo_init\n");

    printk(KERN_INFO "[TEST_VO] end vo_init result=0x%x\n", res);
    return res;
}

static void __exit vo_exit(void)
{
    printk(KERN_INFO "[TEST_VO] vo_exit\n");

    return;
}

MODULE_AUTHOR("A customer using TEST_VO, Inc.");
MODULE_DESCRIPTION("TEST_VO linux driver");
MODULE_LICENSE("GPL");

module_init(vo_init);
module_exit(vo_exit);

static const struct of_device_id rtk_vo_dt_match[] = {
    { .compatible = "Realtek,rtk1295-test_vo" },
    {}
};
MODULE_DEVICE_TABLE(of, rtk_vo_dt_match);

static struct platform_driver rtk_vo_driver = {
    .driver		= {
        .name	= "rtk-test_vo",
        .owner	= THIS_MODULE,
        .of_match_table = rtk_vo_dt_match,
    },
    .probe		= vo_probe,
    .remove		= vo_remove,
};

module_platform_driver(rtk_vo_driver);
