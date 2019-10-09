#include <generated/autoconf.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/ioctl.h> /* needed for the _IOW etc stuff used later */
#include <asm/io.h>
#include <asm/uaccess.h>
#include "../include/os/type.h"
#include "../include/vo_reg.h"
#include "../include/tve_reg.h"
#include "../hdmi/hdmi.h"
#include "../include/hdmi_reg.h"
#include "../example/example.h"
#include "osd.h"
#include "../../../debug.h"
#include "../../dc_rpc.h"

static int debug    = 0;
static int error    = 1;
#define dprintk(msg...) if (debug)   { dbg_info(KERN_DEBUG    "D/OSD: " msg); }
#define eprintk(msg...) if (error)   { dbg_info(KERN_DEBUG    "E/OSD: " msg); }

#define OSD_WRITE_REG_INT32U(addr,val) {                                            \
    WRITE_REG_INT32U(addr,val);                                                     \
    dprintk(" [0x%08x] w:0x%08x => r:0x%08x",(addr),(val),READ_REG_INT32U(addr));   \
}


typedef struct {
    unsigned int init;
    unsigned int output_w;
    unsigned int output_h;
    unsigned int mix1w;
    unsigned int mix1h;
} _OSDSTATE;

#define OFFSET_BASE             0x18070000
#define OFFSET_OSD_STRUCT       ( OFFSET_BASE + 0      ) // OSD Struct           (SCPU Write)
#define OFFSET_VO_OSD_WIN       ( OFFSET_BASE + 0x100  ) // VO_OSD_WIN           (SCPU Write)
#define OFFSET_RET_TOP_ADDR     ( OFFSET_BASE + 0x1000 ) // return top_addr      (ACPU Write)
#define OFFSET_VO_RESOLUTION    ( OFFSET_BASE + 0x1100 ) // VO_RESOLUTION_INFO   (ACPU Write)
#define OFFSET_YUV_STRUCT       ( OFFSET_BASE + 0x2000 ) // YUV Struct           (SCPU Write)
#define OFFSET_RET_Y_ADDR       ( OFFSET_BASE + 0x3000 ) // return Y_addr        (ACPU Write)

static  VO_RETURN * vo_return = NULL; // 0x18071000
static  OSD_STATE * osd_state = NULL; // 0x18070000
static  OSD_STATE * _osd_state = NULL;// page alloc
static  YUV_STATE * yuv_state = NULL; // 0x18072000
static  YUV_STATE * _yuv_state = NULL; // page alloc
static  VO_RESOLUTION_INFO * vo_res_info = NULL;

static int yuv_flag = NULL;
enum {
    v1_ready = 0x1,
    hwc_ready = 0x2,
};

static WINDOW_INFO osd_window = {
    .dst_x = 0,
    .dst_y = 0,
    .dst_width = 1920,
    .dst_height = 1080,
};

static WINDOW_INFO vo_window = {
    .dst_x = 0,
    .dst_y = 0,
    .dst_width = 1920,
    .dst_height = 1080,
};

#define DEAFULT_OSD_STATE 1 // 0:ON 1:OFF
#define DEAFULT_OSD_ORDER 2 // 0 ~ 2 top:2

static _OSDSTATE OSDSTATE = {
    .init = 0,
    .output_w = 720,
    .output_h = 480,
    .mix1w = 0,
    .mix1h = 0,
};


int OSDInit(void)
{

    /*
     * set mix1 plane
     */
    OSD_WRITE_REG_INT32U(VO_MIX1,
                     VO_MIX1_i_vbi(1)|
                     VO_MIX1_vbi(1)|
                     VO_MIX1_osd1(0)|
                     VO_MIX1_sub1(1)|
                     VO_MIX1_v1(1)|
                     VO_MIX1_bg(1)|
                     VO_MIX1_write_data(0));

    OSD_WRITE_REG_INT32U(VO_MIX1,
                     VO_MIX1_i_vbi(0)|
                     VO_MIX1_vbi(0)|
                     VO_MIX1_osd1(1)|
                     VO_MIX1_sub1(0)|
                     VO_MIX1_v1(0)|
                     VO_MIX1_bg(0)|
                     VO_MIX1_write_data(1));

    OSDSTATE.init = 1;
    return 0;
}

int OSDSetMix1(unsigned int w, unsigned int h)
{
   /*
     * set mix1 size
     */
#if 0
    unsigned int mix1w = (w * OSDSTATE.output_w)/OSDSTATE.output_w;
    unsigned int mix1h = (h * OSDSTATE.output_h)/OSDSTATE.output_h;
#else
#if 0
    unsigned int mix1w = (OSDSTATE.output_w * w) / w;
    unsigned int mix1h = (OSDSTATE.output_h * h) / h;
#else
    unsigned int mix1w = w;
    unsigned int mix1h = h;
#endif
#endif
    OSD_WRITE_REG_INT32U(VO_MODE,
            VO_MODE_shut_down_enable(0)|
            VO_MODE_gating_enable(1)|
            VO_MODE_write_data(1));


    OSD_WRITE_REG_INT32U(VO_M1_SIZE,
            VO_M1_SIZE_w(mix1w)|
            VO_M1_SIZE_h(mix1h));

    OSD_WRITE_REG_INT32U(VO_INTEN,
            VO_INTEN_h_under(1)|
            VO_INTEN_i_under(1)|
            VO_INTEN_sub1(1)|
            VO_INTEN_wbfin(1)|
            VO_INTEN_m1fin(1)|
            VO_INTEN_m2fin(1)|
            VO_INTEN_write_data(1));

    OSDSTATE.mix1w = w;
    OSDSTATE.mix1h = h;
    return 0;
}

int OSDShowPic(unsigned int srcW,unsigned int srcH,unsigned int pImage)
{
#if 0
    unsigned int srcW    = 1280 ;
    unsigned int srcH    = 720 ;
    unsigned int pImage = 0x83900000 ;
#endif
    unsigned int byteCnt = 4 ;//ARGB8888
    unsigned int pitch = srcW*byteCnt ;

#if 1
    unsigned int dstW = srcW;
    unsigned int dstH = srcH;
#else
    unsigned int dstW = OSDSTATE.output_w;
    unsigned int dstH = OSDSTATE.output_h;
#endif

    static VO_OSD_WIN *win = NULL;

    if (OSDSTATE.init == 0)
        OSDInit();

    if (srcW != OSDSTATE.mix1w || srcH != OSDSTATE.mix1h)
        OSDSetMix1(srcW,srcH);

#if 0
    if (win == NULL)
        win = (VO_OSD_WIN*) kmalloc(sizeof(VO_OSD_WIN)+20,GFP_KERNEL|__GFP_ZERO);
#else
    if (win == NULL) {
        win = (void *) __get_free_pages(__GFP_ZERO|GFP_KERNEL, get_order((sizeof(VO_OSD_WIN)+20)));
        memset(win, 0, (sizeof(VO_OSD_WIN)+20));
    }
#endif


    dprintk(" Image phyaddr = 0x%08x\n",pImage);
    win->nxtAddr.addr         = 0;
    win->nxtAddr.last         = 1;
    win->winXY.x              = 0;
    win->winXY.y              = 0;
    win->winWH.width          = srcW;
    win->winWH.height         = srcH;
    win->attr.extendMode      = 0 ;
    //win->attr.extendMode      = 1 ;
    win->attr.littleEndian    = 1 ;
    win->attr.rgbOrder        = 0 ; //RGB
    win->attr.alphaType       = 0 ;
    win->attr.alphaEn         = 1 ;
    win->attr.storageMode     = 1 ; //sequential
    win->attr.alpha           = 255 ;
    win->attr.type            = 7 ;//ARGB8888
    win->colorKey.keyEn       = 0 ;
    /* top or progressive OSD start address (sequential) or index (block mode) */
    win->top_addr             = pImage ;
    win->pitch                = pitch ;
    win->objOffset.objYoffset =0 ;
    win->objOffset.objXoffset =0 ;


    /*
     * vo->OSD1_size.w = srcW ;
     * vo->OSD1_size.h = srcH ;
     */
    OSD_WRITE_REG_INT32U(VO_OSD1_SIZE,
            VO_OSD1_SIZE_w(srcW)|
            VO_OSD1_SIZE_h(srcH));

    /*
     * vo->OSD1_ctrl.fetch_1080i = 0 ;
     */
    OSD_WRITE_REG_INT32U(VO_OSD1,
            VO_OSD1_fetch_1080i(1)|
            VO_OSD1_write_data(0));

#if 1   /* dstW== srcW && dstH==srcH */


    /*
     * vo->OSD1_ctrl.vs =       //v scale enable
     * vo->OSD1_ctrl.hs = 0 ;   //h scale enable
     */
    OSD_WRITE_REG_INT32U(VO_OSD1,
            VO_OSD1_d3_dbh(1)|
            VO_OSD1_d3_vdup(1)|
            VO_OSD1_write_data(0));


#else  /* dstW!= srcW or dstH!=srcH, need to calculate phase, offset, delta */
    /*
     * vo->OSD1_ctrl.vs =
     * vo->OSD1_ctrl.hs = 1 ;
     * vo->OSD1_VS_i.phase  =
     * vo->OSD1_HS_i.phase  =
     * vo->OSD1_VS_i.offset =
     * vo->OSD1_HS_i.offset = 0 ;
     * vo->OSD1_VS_d.delta = 0x10000 ;
     * vo->OSD1_HS_d.delta = 0x10000 ;
     */
    OSD_WRITE_REG_INT32U(VO_OSD1,
            VO_OSD1_d3_dbh(1)|
            VO_OSD1_d3_vdup(1)|
            VO_OSD1_write_data(1));
    OSD_WRITE_REG_INT32U(VO_OSD1_VSI,
            VO_OSD1_VSI_offset(0)|
            VO_OSD1_VSI_phase(0));
    OSD_WRITE_REG_INT32U(VO_OSD1_HSI,
            VO_OSD1_HSI_offset(0)|
            VO_OSD1_HSI_phase(0));
    OSD_WRITE_REG_INT32U(VO_OSD1_VSD,
            VO_OSD1_VSD_delta(dstW));
    OSD_WRITE_REG_INT32U(VO_OSD1_HSD,
            VO_OSD1_HSD_delta(dstH));
#endif

    /*
     * vo->OSD1_xy.y = 0 ;
     * vo->OSD1_xy.x = 0 ;
     */
    OSD_WRITE_REG_INT32U(VO_OSD1_XY,
            VO_OSD1_XY_x(0)|
            VO_OSD1_XY_y(0));


    /*
     * vo->OSD1_VS_d.out = dstW ;
     */
    OSD_WRITE_REG_INT32U(VO_OSD1_VSD,
            VO_OSD1_VSD_delta(dstW));

    /*
     * vo->OSD1_HS_d.out = dstH ;
     */
    OSD_WRITE_REG_INT32U(VO_OSD1_HSD,
            VO_OSD1_HSD_delta(dstH));

    /*
     * vo->OSD1_ctrl.dvb = 0 ;
     */
    OSD_WRITE_REG_INT32U(VO_OSD1,
            VO_OSD1_dvb(1)|
            VO_OSD1_write_data(0));

    /*
     * vo->OSD1_ctrl.osd = 1 ;
     */
    OSD_WRITE_REG_INT32U(VO_OSD1,
            VO_OSD1_osd(1)|
            VO_OSD1_write_data(1));

    /*
     * TODO: window infomation addr
     * vo->OSD1_wi.a = ((unsigned int) &win ) & ~0xe0000000 ; //window infomation addr
     */
    dprintk("set window infomation addr = 0x%08x\n",(unsigned int)(virt_to_phys(win)));

    OSD_WRITE_REG_INT32U(VO_OSD1_WI,
            VO_OSD1_WI_endian(0)|
            VO_OSD1_WI_a((virt_to_phys(win))));

    OSD_WRITE_REG_INT32U(VO_FC,
            VO_FC_m1go(1)|
            VO_FC_m2go(0)|
            VO_FC_write_data(1));

    return 0;
}

void UpdateVORes(void)
{
    if (vo_res_info == NULL)
        vo_res_info= (VO_RESOLUTION_INFO *) ioremap(OFFSET_VO_RESOLUTION,sizeof(VO_RESOLUTION_INFO));

    VO_RESOLUTION_INFO vo_resolution_info;
    pli_ipcCopyMemory((unsigned char*)&vo_resolution_info, (unsigned char*)vo_res_info, sizeof(VO_RESOLUTION_INFO));
    vo_window.dst_width = vo_resolution_info.width;
    vo_window.dst_height= vo_resolution_info.height;
}

int OSDShowPic2(unsigned int srcW,unsigned int srcH,unsigned int pImage)
{

    enum {
        RGB = 0,   // 000:0
        BGR,       // 001:1
        GRB,       // 010:2
        GBR,       // 011:3
        RBG,       // 100:4
        BRG,       // 101:5
    };
#if 0
    {
        static VO_OSD_WIN *win = NULL;
        static VO_OSD_WIN *_win = NULL;
        if (win == NULL)
            win = (VO_OSD_WIN *) ioremap(0x18070100,sizeof(VO_OSD_WIN)+20);
        if (_win == NULL) {
            _win = (void *) __get_free_pages(__GFP_ZERO|GFP_KERNEL, get_order((sizeof(VO_OSD_WIN)+20)));
            memset(_win, 0, (sizeof(VO_OSD_WIN)+20));
        }


        _win->nxtAddr.last         = 1;
        _win->nxtAddr.addr         = 0;
        _win->winXY.x              = 0;
        _win->winXY.y              = 0;
        _win->winWH.width          = srcW;
        _win->winWH.height         = srcH;
        _win->attr.extendMode      = 0 ;
        _win->attr.rgbOrder        = RGB;
        _win->attr.alphaType       = 0 ;
        _win->attr.alphaEn         = 1 ;
        _win->attr.storageMode     = 1 ; //sequential   
        _win->attr.alpha           = 255 ;
        _win->attr.littleEndian    = 1;
        _win->attr.type            = 7 ;//ARGB8888
        _win->colorKey.keyEn       = 0 ;
        _win->top_addr             = pImage;   
        _win->pitch                = srcW*4 ;
        _win->objOffset.objYoffset =0 ;
        _win->objOffset.objXoffset =0 ;

        pli_ipcCopyMemory((unsigned char*)win, (unsigned char*)_win,sizeof(VO_OSD_WIN));
        //memcpy((void*)win,(void *)_win,sizeof(VO_OSD_WIN));
    }
#endif

#if 1
    {
        if (vo_return == NULL)
            vo_return = (VO_RETURN *) ioremap(OFFSET_RET_TOP_ADDR,sizeof(VO_RETURN));

        if (osd_state == NULL)
            osd_state = (OSD_STATE *) ioremap(OFFSET_OSD_STRUCT,sizeof(OSD_STATE));

        #if 0
        if (vo_res_info == NULL) {
            VO_RESOLUTION_INFO temp_vo_res_iofo;
            vo_res_info= (VO_RESOLUTION_INFO *) ioremap(OFFSET_VO_RESOLUTION,sizeof(VO_RESOLUTION_INFO));
            pli_ipcCopyMemory((unsigned char*)&temp_vo_res_iofo, (unsigned char*)vo_res_info, sizeof(VO_RESOLUTION_INFO));
            vo_window.dst_width = temp_vo_res_iofo.width;
            vo_window.dst_height = temp_vo_res_iofo.height;
        }
        #else
        UpdateVORes();
        #endif

        if (_osd_state == NULL) {
            _osd_state = (void *) __get_free_pages(__GFP_ZERO|GFP_KERNEL, get_order((sizeof(OSD_STATE))));
            memset(_osd_state, 0, (sizeof(OSD_STATE)));
            _osd_state->state = DEAFULT_OSD_STATE;
            _osd_state->order = DEAFULT_OSD_ORDER;
        }

        if (_yuv_state == NULL) {
            _yuv_state = (void *) __get_free_pages(__GFP_ZERO|GFP_KERNEL, get_order((sizeof(YUV_STATE))));
            memset(_yuv_state, 0, (sizeof(YUV_STATE)));
            _yuv_state->state = 0;
            _yuv_state->dst_width    = 1920;
            _yuv_state->dst_height   = 1080;
            _yuv_state->dst_x        = 0;
            _yuv_state->dst_y        = 0;
        }

        if (yuv_state == NULL)
            yuv_state = (YUV_STATE *) ioremap(OFFSET_YUV_STRUCT,sizeof(YUV_STATE));

        osd_window.dst_width = srcW;
        osd_window.dst_height = srcH;

        _osd_state->magic = 0x11223344;
        _osd_state->phyAddr = pImage;
        _osd_state->Height  = srcH;
        _osd_state->Width   = srcW;
        _osd_state->attr_rgbOrder   = BGR;//RGB
        _osd_state->attr_type       = 7;//ARGB8888

        pli_ipcCopyMemory((unsigned char*)osd_state, (unsigned char*)_osd_state,sizeof(OSD_STATE));

#if 0
        { /* Wait OSD Complete */
            const int MaxWaitCount = 30;
            int waitCount = 0;
            do {
                msleep(1);
                VO_RETURN _vo_return;
                pli_ipcCopyMemory((unsigned char*)&_vo_return,(unsigned char*)vo_return,sizeof(VO_RETURN));
                if (_vo_return.phyAddr == pImage) {
                    dprintk("[%s] OSD Complete. (%d, 0x%08x)",__func__,waitCount,pImage);
                    break;
                }
                waitCount++;
            } while (waitCount <= MaxWaitCount);

            if (waitCount >= MaxWaitCount) {
                //eprintk("[%s] Wait OSD Complete. Time Out!",__func__);
            }
        }
#endif
    }
#endif

    return 0;
}

int OSD_Ioctl (unsigned int cmd, unsigned int arg)
{
    int retval = 0;
    switch (cmd) {
        case GET_OSD_STATE:
            {
                if (_osd_state == NULL) goto err;
                if (copy_to_user((void *)arg, _osd_state, sizeof(OSD_STATE)) != 0) goto err;
                retval = 0;
                break;
            }
        case SET_OSD_STATE:
            {
                OSD_STATE osd_state_;
                if (_osd_state == NULL) goto err;
                if (copy_from_user(&osd_state_, (void *)arg,sizeof(OSD_STATE)) != 0) goto err;
                dprintk("[%s] SET state=%d order=%d",__func__,osd_state_.state,osd_state_.order);
                _osd_state->state = osd_state_.state;
                _osd_state->order = osd_state_.order;
                pli_ipcCopyMemory((unsigned char*)osd_state, (unsigned char*)_osd_state,sizeof(OSD_STATE));
                retval = 0;
                break;
            }
        case OSD_STATE_RESET:
            {
                if (_osd_state == NULL) goto err;
                _osd_state->state = DEAFULT_OSD_STATE;
                _osd_state->order = DEAFULT_OSD_ORDER;
                dprintk("[%s] RESET state=%d order=%d",__func__,_osd_state->state,_osd_state->order);
                pli_ipcCopyMemory((unsigned char*)osd_state, (unsigned char*)_osd_state,sizeof(OSD_STATE));
                retval = 0;
                break;
            }
        #if 0
        case OSD_STATE_CLOSE:
            {
                if (_osd_state == NULL) goto err;
                //_osd_state->state = 0;
                _osd_state->order = 2;
                dprintk("[%s] CLOSE state=%d order=%d",__func__,_osd_state->state,_osd_state->order);
                pli_ipcCopyMemory((unsigned char*)osd_state, (unsigned char*)_osd_state,sizeof(OSD_STATE));
                retval = 0;
                break;
            }
        case OSD_STATE_OPEN:
            {
                if (_osd_state == NULL) goto err;
                //_osd_state->state = 1;
                _osd_state->order = DEAFULT_OSD_ORDER;
                dprintk("[%s] OPEN state=%d order=%d",__func__,_osd_state->state,_osd_state->order);
                pli_ipcCopyMemory((unsigned char*)osd_state, (unsigned char*)_osd_state,sizeof(OSD_STATE));
                retval = 0;
                break;
            }
        #else
        case OSD_STATE_CLOSE:
        case OSD_STATE_OPEN:
            {
                retval = 0;
                break;
            }
        #endif
        case WRITE_YUV_STATE:
            {
                YUV_STATE temp_yuv_state;
                if (copy_from_user(&temp_yuv_state, (void *)arg,sizeof(YUV_STATE_V0)) != 0) goto err;
                _yuv_state->magic       = temp_yuv_state.magic;
                if (temp_yuv_state.state)
                    yuv_flag |= v1_ready;
                if ((yuv_flag & hwc_ready) && (yuv_flag & v1_ready)) {
                    _yuv_state->state       = temp_yuv_state.state;
                }

                _yuv_state->state       = temp_yuv_state.state;

                _yuv_state->Y_addr      = temp_yuv_state.Y_addr;
                _yuv_state->U_addr      = temp_yuv_state.U_addr;
                _yuv_state->YUVFormat   = temp_yuv_state.YUVFormat;
                _yuv_state->width       = temp_yuv_state.width;
                _yuv_state->height      = temp_yuv_state.height;
                _yuv_state->Y_pitch     = temp_yuv_state.Y_pitch;
                _yuv_state->C_pitch     = temp_yuv_state.C_pitch;
                _yuv_state->first       = temp_yuv_state.first;
                _yuv_state->pts_inc     = temp_yuv_state.pts_inc;
                _yuv_state->PTSH        = temp_yuv_state.PTSH;
                _yuv_state->PTSL        = temp_yuv_state.PTSL;
                pli_ipcCopyMemory((unsigned char*)yuv_state, (unsigned char*)_yuv_state,sizeof(YUV_STATE));
                retval = 0;
                break;
            }
        case READ_YUV_STATE:
            {
                if (copy_to_user((void *)arg, _yuv_state, sizeof(YUV_STATE)) != 0) goto err;
                retval = 0;
                break;
            }
        case READ_YUV_RETURN:
            {
                static unsigned int * yuv_return = NULL;
                unsigned int yuv_return_;
                if (yuv_return == NULL)
                    yuv_return = (unsigned int *) ioremap(OFFSET_RET_Y_ADDR,sizeof(unsigned int));
                pli_ipcCopyMemory((unsigned char*)&yuv_return_, (unsigned char*)yuv_return,sizeof(unsigned int));
                if (copy_to_user((void *)arg, &yuv_return_, sizeof(unsigned int)) != 0) goto err;
                retval = 0;
                break;
            }
        case YUV_WINDOW_GET:
            {
                WINDOW_INFO yuv_window;
                yuv_window.dst_width    = _yuv_state->dst_width;
                yuv_window.dst_height   = _yuv_state->dst_height;
                yuv_window.dst_x        = _yuv_state->dst_x;
                yuv_window.dst_y        = _yuv_state->dst_y;
                if (copy_to_user((void *)arg, &yuv_window, sizeof(WINDOW_INFO)) != 0) goto err;
                retval = 0;
                break;
            }
        case YUV_WINDOW_SET:
            {
                #define SCALE_PRECISION 1000
                WINDOW_INFO temp_window;
                unsigned int  w_scale = SCALE_PRECISION;
                unsigned int h_scale = SCALE_PRECISION;
                if (copy_from_user(&temp_window, (void *)arg,sizeof(WINDOW_INFO)) != 0) goto err;
                UpdateVORes();
                w_scale *= vo_window.dst_width;
                h_scale *= vo_window.dst_height;
                w_scale /= osd_window.dst_width;
                h_scale /= osd_window.dst_height;
                temp_window.dst_width   *= w_scale;
                temp_window.dst_height  *= h_scale;
                temp_window.dst_x       *= w_scale;
                temp_window.dst_y       *= h_scale;
                temp_window.dst_width   /= SCALE_PRECISION;
                temp_window.dst_height  /= SCALE_PRECISION;
                temp_window.dst_x       /= SCALE_PRECISION;
                temp_window.dst_y       /= SCALE_PRECISION;
                #undef SCALE_PRECISION

                _yuv_state->dst_width    = temp_window.dst_width;
                _yuv_state->dst_height   = temp_window.dst_height;
                _yuv_state->dst_x        = temp_window.dst_x;
                _yuv_state->dst_y        = temp_window.dst_y;

                pli_ipcCopyMemory((unsigned char*)yuv_state, (unsigned char*)_yuv_state,sizeof(YUV_STATE));
                retval = 0;
                break;
            }
        case YUV_WINDOW_OPEN:
            {
                yuv_flag |= hwc_ready;
                if ((yuv_flag & hwc_ready) && (yuv_flag & v1_ready)) {
                    _yuv_state->state = 1;
                    pli_ipcCopyMemory((unsigned char*)yuv_state, (unsigned char*)_yuv_state,sizeof(YUV_STATE));
                }
                #if 0
                OSD_Ioctl(OSD_STATE_CLOSE,NULL);
                #else
                {
                    _osd_state->order = 2;
                    pli_ipcCopyMemory((unsigned char*)osd_state, (unsigned char*)_osd_state,sizeof(OSD_STATE));
                }
                #endif
                retval = 0;
                break;
            }
        case YUV_WINDOW_CLOSE:
            {
                yuv_flag = 0;
                _yuv_state->state = 0;
                _yuv_state->dst_x = _yuv_state->dst_y = 0;
                _yuv_state->dst_width    = vo_window.dst_width;
                _yuv_state->dst_height   = vo_window.dst_height;
                pli_ipcCopyMemory((unsigned char*)yuv_state, (unsigned char*)_yuv_state,sizeof(YUV_STATE));
                #if 0
                #if 0
                OSD_Ioctl(OSD_STATE_OPEN,NULL);
                #else
                {
                    _osd_state->order = DEAFULT_OSD_ORDER;
                    pli_ipcCopyMemory((unsigned char*)osd_state, (unsigned char*)_osd_state,sizeof(OSD_STATE));
                }
                #endif
                #endif
                retval = 0;
                break;
            }
        #if 1
        case VO_RESOLUTION_GET:
            {
                VO_RESOLUTION_INFO temp_vo_res_iofo;
                pli_ipcCopyMemory((unsigned char*)&temp_vo_res_iofo, (unsigned char*)vo_res_info, sizeof(VO_RESOLUTION_INFO));
                vo_window.dst_width = temp_vo_res_iofo.width;
                vo_window.dst_height = temp_vo_res_iofo.height;
                if (copy_to_user((void *)arg, &temp_vo_res_iofo, sizeof(VO_RESOLUTION_INFO)) != 0) goto err;
                retval = 0;
                break;
            }
        case VO_RESOLUTION_SET:
            {
                VO_RESOLUTION_INFO temp_vo_res_iofo;
                if (copy_from_user(&temp_vo_res_iofo, (void *)arg,sizeof(VO_RESOLUTION_INFO)) != 0) goto err;
                temp_vo_res_iofo.magic = 0x11223344;
                pli_ipcCopyMemory((unsigned char*)vo_res_info, (unsigned char*)&temp_vo_res_iofo, sizeof(VO_RESOLUTION_INFO));
                vo_window.dst_width = temp_vo_res_iofo.width;
                vo_window.dst_height = temp_vo_res_iofo.height;
                retval = 0;
                break;
            }
        #else
        case VO_RESOLUTION_GET:
        case VO_RESOLUTION_SET:
            {
                retval = 0;
                break;
            }
        #endif
        default:
            retval = -2;
    }
    return retval;
err:
    return -1;
}

