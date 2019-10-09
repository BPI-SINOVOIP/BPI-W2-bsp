#include <generated/autoconf.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <asm/io.h>
#include "../include/os/type.h"
#include "../include/hdmi_reg.h"
#include "../include/tve_reg.h"
#include "hdmi.h"
//#######################################################################################################
//
//  File Name:      HDMI_480p.C
//  Description:    HDMI Video 720x480p @59.94/60Hz initial setting
//
//#######################################################################################################
#ifdef FPGA_USE_IOMAP
#define HDMI_IO_BASE HDMI_INTEN
#define HDMI_IO_SIZE 0x1000
#define HDMI_WRITE_REG_INT32U(addr,val) WRITE_REG_INT32U(((unsigned int)hdmi_iomap+(addr-HDMI_IO_BASE)),val)
static void* hdmi_iomap = NULL;
#else
#define HDMI_WRITE_REG_INT32U(addr,val) WRITE_REG_INT32U(addr,val)
#endif

#ifdef FPGA_USE_IOMAP
#define TVE_IO_BASE TVE_SYNCGEN_RST
#define TVE_IO_SIZE 0x1000
#define TVE_WRITE_REG_INT32U(addr,val) WRITE_REG_INT32U(((unsigned int)tve_iomap+(addr-TVE_IO_BASE)),val)
static void* tve_iomap = NULL;
#else
#define TVE_WRITE_REG_INT32U(addr,val) WRITE_REG_INT32U(addr,val)
#endif
void SET_HDMI_Video_480p(INT8U Pixel_Colocr_Format, INT8U DVI_or_HDMI, INT8U Deep_Color, INT8U Deep_Depth, INT8U xv_YCC, INT8U Timing_Gen, INT8U En_3D, INT8U Format_3D)
{
#ifdef FPGA_USE_IOMAP
    if (hdmi_iomap == NULL)
        hdmi_iomap = ioremap(HDMI_IO_BASE,HDMI_IO_SIZE);
        //hdmi_iomap = phys_to_virt(HDMI_IO_BASE);
    if (tve_iomap == NULL)
        tve_iomap = ioremap(TVE_IO_BASE,TVE_IO_SIZE);
        //tve_iomap = phys_to_virt(TVE_IO_BASE);
#endif
    //0xb800d034
    HDMI_WRITE_REG_INT32U(HDMI_CR,
                     HDMI_CR_write_en3(1)|HDMI_CR_tmds_encen(0)| //TMDS Encoder disable
                     HDMI_CR_write_en2(0)|HDMI_CR_enablehdcp(0)|
                     HDMI_CR_write_en1(1)|HDMI_CR_enablehdmi(0)); //HDMI disable
    //0xb800d0bc
    HDMI_WRITE_REG_INT32U(HDMI_ICR,
                     HDMI_ICR_write_en3(1)|HDMI_ICR_enaudio(0)| //0:disable HDMI audio data path
                     HDMI_ICR_write_en2(1)|HDMI_ICR_envitd(0)|
                     HDMI_ICR_write_en1(0)|HDMI_ICR_vitd(0));

    if(!DVI_or_HDMI) //DVI mode=================================================
    {
        //CRT & PHY config
        //Timming setting
        if(Timing_Gen)//using HDMI timing generator control
        {
            //0xb800d234
            HDMI_WRITE_REG_INT32U(HDMI_H_PARA1,
                             HDMI_H_PARA1_hblank(137)|
                             HDMI_H_PARA1_hactive(719));
            //0xb800d238
            HDMI_WRITE_REG_INT32U(HDMI_H_PARA2,
                             HDMI_H_PARA2_hsync(61)|
                             HDMI_H_PARA2_hfront(15));
            //0xb800d23c
            HDMI_WRITE_REG_INT32U(HDMI_H_PARA3,
                             HDMI_H_PARA3_hback(59));
            //0xb800d240
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA1,
                             HDMI_V_PARA1_Vact_video(479)|
                             HDMI_V_PARA1_vactive(479));
            //0xb800d244
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA2,
                             HDMI_V_PARA2_Vact_space1(0)|
                             HDMI_V_PARA2_Vact_space(0));
            //0xb800d248
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA3,
                             HDMI_V_PARA3_Vblank3(0)|
                             HDMI_V_PARA3_Vact_space2(0));
            //0xb800d24c
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA4,
                             HDMI_V_PARA4_vsync((6<<1))|
                             HDMI_V_PARA4_vblank(44));
            //0xb800d250
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA5,
                             HDMI_V_PARA5_vback(29)|
                             HDMI_V_PARA5_vfront((9<<1)));
            //0xb800d254
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA6,
                             HDMI_V_PARA6_Vsync1((0<<1))|
                             HDMI_V_PARA6_Vblank1(0));
            //0xb800d258
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA7,
                             HDMI_V_PARA7_Vback1(0)|
                             HDMI_V_PARA7_Vfront1((0<<1)));
            //0xb800d25c
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA8,
                             HDMI_V_PARA8_Vsync2((0<<1))|
                             HDMI_V_PARA8_Vblank2(0));
            //0xb800d260
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA9,
                             HDMI_V_PARA9_Vback2(0)|
                             HDMI_V_PARA9_Vfront2((0<<1)));
            //0xb800d26c
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA10,
                             HDMI_V_PARA10_G(0x00beef));
            //0xb800d270
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA11,
                             HDMI_V_PARA11_B(0x00beef)|
                             HDMI_V_PARA11_R(0x00beef));
            //0xb800d264
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA12,
                             HDMI_V_PARA12_vsynci((0<<1))|
                             HDMI_V_PARA12_vblanki(0));
            //0xb800d268
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA13,
                             HDMI_V_PARA13_vbacki(0)|
                             HDMI_V_PARA13_vfronti((0<<1)));
            //0xb800d030
            HDMI_WRITE_REG_INT32U(HDMI_SYNC_DLY,
                             HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                             HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                             HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                             HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
            //0xb800d154
            HDMI_WRITE_REG_INT32U(HDMI_DPC,
                             HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(1)|
                             HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(0)|
                             HDMI_DPC_write_en7(1)|HDMI_DPC_fp(0)|
                             HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                             HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(1)|
                             HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(0)|
                             HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(0));
        }
        else //using TVE timing generator control
        {
            //0xb80180b8
            TVE_WRITE_REG_INT32U(TVE_HDMI_ST,
                             TVE_HDMI_ST_write_en4(1)|TVE_HDMI_ST_sync_en(1)|
                             TVE_HDMI_ST_write_en3(1)|TVE_HDMI_ST_ch_sel(0)| //0:progressive, 1:interlace
                             TVE_HDMI_ST_write_en2(1)|TVE_HDMI_ST_vpos(0)|
                             TVE_HDMI_ST_write_en1(1)|TVE_HDMI_ST_hpos(0));
            //0xb80180bc
            TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_HS,
                             TVE_HDMI_DISP_HS_write_en2(1)|TVE_HDMI_DISP_HS_hs_start(15)|
                             TVE_HDMI_DISP_HS_write_en1(1)|TVE_HDMI_DISP_HS_hs_end(77));
            //0xb80180c0
            TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_VSST1,
                             TVE_HDMI_DISP_VSST1_write_en2(1)|TVE_HDMI_DISP_VSST1_vs_st_pos1v(6)|
                             TVE_HDMI_DISP_VSST1_write_en1(1)|TVE_HDMI_DISP_VSST1_vs_st_pos1h(15));
            //0xb80180c4
            TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_VSED1,
                             TVE_HDMI_DISP_VSED1_write_en2(1)|TVE_HDMI_DISP_VSED1_vs_end_pos1v(12)|
                             TVE_HDMI_DISP_VSED1_write_en1(1)|TVE_HDMI_DISP_VSED1_vs_end_pos1h(15));
            //0xb80180c8
            TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_VSST2,
                             TVE_HDMI_DISP_VSST2_write_en2(1)|TVE_HDMI_DISP_VSST2_vs_st_pos2v(0)|
                             TVE_HDMI_DISP_VSST2_write_en1(1)|TVE_HDMI_DISP_VSST2_vs_st_pos2h(0));
            //0xb80180cc
            TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_VSED2,
                             TVE_HDMI_DISP_VSED2_write_en2(1)|TVE_HDMI_DISP_VSED2_vs_end_pos2v(0)|
                             TVE_HDMI_DISP_VSED2_write_en1(1)|TVE_HDMI_DISP_VSED2_vs_end_pos2h(0));
            //0xb80180d0
            TVE_WRITE_REG_INT32U(TVE_HDMI_PXLACT,
                             TVE_HDMI_PXLACT_write_en2(1)|TVE_HDMI_PXLACT_hpos_end(850)|
                             TVE_HDMI_PXLACT_write_en1(1)|TVE_HDMI_PXLACT_hpos_st(116));
            //0xb800d030
            HDMI_WRITE_REG_INT32U(HDMI_SYNC_DLY,
                             HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                             HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                             HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(2)|
                             HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(2));
            //0xb800d154
            HDMI_WRITE_REG_INT32U(HDMI_DPC,
                             HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(1)|
                             HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(0)|
                             HDMI_DPC_write_en7(1)|HDMI_DPC_fp(0)|
                             HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                             HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(1)|
                             HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(0)|
                             HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(0));
        }
    }
    else //HDMI mode============================================================
    {
        //CRT & PHY config
        //Timming setting
        if(Timing_Gen)//using HDMI timing generator control
        {
            //0xb800d234
            HDMI_WRITE_REG_INT32U(HDMI_H_PARA1,
                             HDMI_H_PARA1_hblank(137)|
                             HDMI_H_PARA1_hactive(719));
            //0xb800d238
            HDMI_WRITE_REG_INT32U(HDMI_H_PARA2,
                             HDMI_H_PARA2_hsync(61)|
                             HDMI_H_PARA2_hfront(15));
            //0xb800d23c
            HDMI_WRITE_REG_INT32U(HDMI_H_PARA3,
                             HDMI_H_PARA3_hback(59));
            if(En_3D)
            {
                switch(Format_3D)
                {
                    case 0:
                    case 4:
                        //0xb800d240
                        HDMI_WRITE_REG_INT32U(HDMI_V_PARA1,
                                         HDMI_V_PARA1_Vact_video(479)|
                                         HDMI_V_PARA1_vactive(1004));
                        //0xb800d244
                        HDMI_WRITE_REG_INT32U(HDMI_V_PARA2,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(44));
                        break;
                    case 1:
                        //Field alternative no support!!
                        break;
                    case 2:
                    case 3:
                        //0xb800d240
                        HDMI_WRITE_REG_INT32U(HDMI_V_PARA1,
                                         HDMI_V_PARA1_Vact_video(479)|
                                         HDMI_V_PARA1_vactive(479));
                        //0xb800d244
                        HDMI_WRITE_REG_INT32U(HDMI_V_PARA2,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        break;
                    case 5:
                        //0xb800d240
                        HDMI_WRITE_REG_INT32U(HDMI_V_PARA1,
                                         HDMI_V_PARA1_Vact_video(479)|
                                         HDMI_V_PARA1_vactive(2054));
                        //0xb800d244
                        HDMI_WRITE_REG_INT32U(HDMI_V_PARA2,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(44));
                        break;
                    case 6:
                    case 8:
                        //0xb800d240
                        HDMI_WRITE_REG_INT32U(HDMI_V_PARA1,
                                         HDMI_V_PARA1_Vact_video(479)|
                                         HDMI_V_PARA1_vactive(479));
                        //0xb800d244
                        HDMI_WRITE_REG_INT32U(HDMI_V_PARA2,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        break;
                    case 7:
                        break;
                    default:
                        break;
                }
            }
            else
            {
                //0xb800d240
                HDMI_WRITE_REG_INT32U(HDMI_V_PARA1,
                                 HDMI_V_PARA1_Vact_video(479)|
                                 HDMI_V_PARA1_vactive(479));
                //0xb800d244
                HDMI_WRITE_REG_INT32U(HDMI_V_PARA2,
                                 HDMI_V_PARA2_Vact_space1(0)|
                                 HDMI_V_PARA2_Vact_space(0));
            }
            //0xb800d248
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA3,
                             HDMI_V_PARA3_Vblank3(0)|
                             HDMI_V_PARA3_Vact_space2(0));
            //0xb800d24c
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA4,
                             HDMI_V_PARA4_vsync((6<<1))|
                             HDMI_V_PARA4_vblank(44));
            //0xb800d250
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA5,
                             HDMI_V_PARA5_vback(29)|
                             HDMI_V_PARA5_vfront((9<<1)));
            //0xb800d254
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA6,
                             HDMI_V_PARA6_Vsync1((0<<1))|
                             HDMI_V_PARA6_Vblank1(0));
            //0xb800d258
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA7,
                             HDMI_V_PARA7_Vback1(0)|
                             HDMI_V_PARA7_Vfront1((0<<1)));
            //0xb800d25c
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA8,
                             HDMI_V_PARA8_Vsync2((0<<1))|
                             HDMI_V_PARA8_Vblank2(0));
            //0xb800d260
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA9,
                             HDMI_V_PARA9_Vback2(0)|
                             HDMI_V_PARA9_Vfront2((0<<1)));
            //0xb800d26c
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA10,
                             HDMI_V_PARA10_G(0x00beef));
            //0xb800d270
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA11,
                             HDMI_V_PARA11_B(0x00beef)|
                             HDMI_V_PARA11_R(0x00beef));
            //0xb800d264
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA12,
                             HDMI_V_PARA12_vsynci((0<<1))|
                             HDMI_V_PARA12_vblanki(0));
            //0xb800d268
            HDMI_WRITE_REG_INT32U(HDMI_V_PARA13,
                             HDMI_V_PARA13_vbacki(0)|
                             HDMI_V_PARA13_vfronti((0<<1)));

            //Deep Color 24bit========================================================================================
            if(Deep_Color==0 || (Deep_Color==1 && Deep_Depth==4))
            {
                //0xb800d030
                HDMI_WRITE_REG_INT32U(HDMI_SYNC_DLY,
                                 HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                                 HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                                 HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                                 HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
                //0xb800d154
                HDMI_WRITE_REG_INT32U(HDMI_DPC,
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
                HDMI_WRITE_REG_INT32U(HDMI_SYNC_DLY,
                                 HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                                 HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                                 HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                                 HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
                //0xb800d154
                HDMI_WRITE_REG_INT32U(HDMI_DPC,
                                 HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(3)|
                                 HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(1)|
                                 HDMI_DPC_write_en7(1)|HDMI_DPC_fp(1)|
                                 HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                                 HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(0)|
                                 HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(Deep_Depth)|
                                 HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(Deep_Color));
            }
            //Deep Color 36bit========================================================================================
            if(Deep_Color==1 && Deep_Depth==6)
            {
                //0xb800d030
                HDMI_WRITE_REG_INT32U(HDMI_SYNC_DLY,
                                 HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                                 HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                                 HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                                 HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
                //0xb800d154
                HDMI_WRITE_REG_INT32U(HDMI_DPC,
                                 HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(1)|
                                 HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(0)|
                                 HDMI_DPC_write_en7(1)|HDMI_DPC_fp(0)|
                                 HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                                 HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(1)|
                                 HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(Deep_Depth)|
                                 HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(Deep_Color));
            }
        }
        else //using TVE timing control
        {
            //Deep Color 24bit========================================================================================
            if(Deep_Color==0 || (Deep_Color==1 && Deep_Depth==4))
            {
                //0xb80180b8
                TVE_WRITE_REG_INT32U(TVE_HDMI_ST,
                                 TVE_HDMI_ST_write_en4(1)|TVE_HDMI_ST_sync_en(1)|
                                 TVE_HDMI_ST_write_en3(1)|TVE_HDMI_ST_ch_sel(0)| //0:progressive, 1:interlace
                                 TVE_HDMI_ST_write_en2(1)|TVE_HDMI_ST_vpos(0)|
                                 TVE_HDMI_ST_write_en1(1)|TVE_HDMI_ST_hpos(0));
                //0xb80180bc
                TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_HS,
                                 TVE_HDMI_DISP_HS_write_en2(1)|TVE_HDMI_DISP_HS_hs_start(15)|
                                 TVE_HDMI_DISP_HS_write_en1(1)|TVE_HDMI_DISP_HS_hs_end(77));
                //0xb80180c0
                TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_VSST1,
                                 TVE_HDMI_DISP_VSST1_write_en2(1)|TVE_HDMI_DISP_VSST1_vs_st_pos1v(6)|
                                 TVE_HDMI_DISP_VSST1_write_en1(1)|TVE_HDMI_DISP_VSST1_vs_st_pos1h(15));
                //0xb80180c4
                TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_VSED1,
                                 TVE_HDMI_DISP_VSED1_write_en2(1)|TVE_HDMI_DISP_VSED1_vs_end_pos1v(12)|
                                 TVE_HDMI_DISP_VSED1_write_en1(1)|TVE_HDMI_DISP_VSED1_vs_end_pos1h(15));
                //0xb80180c8
                TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_VSST2,
                                 TVE_HDMI_DISP_VSST2_write_en2(1)|TVE_HDMI_DISP_VSST2_vs_st_pos2v(0)|
                                 TVE_HDMI_DISP_VSST2_write_en1(1)|TVE_HDMI_DISP_VSST2_vs_st_pos2h(0));
                //0xb80180cc
                TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_VSED2,
                                 TVE_HDMI_DISP_VSED2_write_en2(1)|TVE_HDMI_DISP_VSED2_vs_end_pos2v(0)|
                                 TVE_HDMI_DISP_VSED2_write_en1(1)|TVE_HDMI_DISP_VSED2_vs_end_pos2h(0));
                //0xb80180d0
                TVE_WRITE_REG_INT32U(TVE_HDMI_PXLACT,
                                 TVE_HDMI_PXLACT_write_en2(1)|TVE_HDMI_PXLACT_hpos_end(850)|
                                 TVE_HDMI_PXLACT_write_en1(1)|TVE_HDMI_PXLACT_hpos_st(116));
                //0xb800d030
                HDMI_WRITE_REG_INT32U(HDMI_SYNC_DLY,
                                 HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                                 HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                                 HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(2)|
                                 HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(2));
                //0xb800d154
                HDMI_WRITE_REG_INT32U(HDMI_DPC,
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
                //0xb80180b8
                TVE_WRITE_REG_INT32U(TVE_HDMI_ST,
                                 TVE_HDMI_ST_write_en4(1)|TVE_HDMI_ST_sync_en(1)|
                                 TVE_HDMI_ST_write_en3(1)|TVE_HDMI_ST_ch_sel(0)| //0:progressive, 1:interlace
                                 TVE_HDMI_ST_write_en2(1)|TVE_HDMI_ST_vpos(0)|
                                 TVE_HDMI_ST_write_en1(1)|TVE_HDMI_ST_hpos(0));
                //0xb80180bc
                TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_HS,
                                 TVE_HDMI_DISP_HS_write_en2(1)|TVE_HDMI_DISP_HS_hs_start(15)|
                                 TVE_HDMI_DISP_HS_write_en1(1)|TVE_HDMI_DISP_HS_hs_end(77));
                //0xb80180c0
                TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_VSST1,
                                 TVE_HDMI_DISP_VSST1_write_en2(1)|TVE_HDMI_DISP_VSST1_vs_st_pos1v(6)|
                                 TVE_HDMI_DISP_VSST1_write_en1(1)|TVE_HDMI_DISP_VSST1_vs_st_pos1h(15));
                //0xb80180c4
                TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_VSED1,
                                 TVE_HDMI_DISP_VSED1_write_en2(1)|TVE_HDMI_DISP_VSED1_vs_end_pos1v(12)|
                                 TVE_HDMI_DISP_VSED1_write_en1(1)|TVE_HDMI_DISP_VSED1_vs_end_pos1h(15));
                //0xb80180c8
                TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_VSST2,
                                 TVE_HDMI_DISP_VSST2_write_en2(1)|TVE_HDMI_DISP_VSST2_vs_st_pos2v(0)|
                                 TVE_HDMI_DISP_VSST2_write_en1(1)|TVE_HDMI_DISP_VSST2_vs_st_pos2h(0));
                //0xb80180cc
                TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_VSED2,
                                 TVE_HDMI_DISP_VSED2_write_en2(1)|TVE_HDMI_DISP_VSED2_vs_end_pos2v(0)|
                                 TVE_HDMI_DISP_VSED2_write_en1(1)|TVE_HDMI_DISP_VSED2_vs_end_pos2h(0));
                //0xb80180d0
                TVE_WRITE_REG_INT32U(TVE_HDMI_PXLACT,
                                 TVE_HDMI_PXLACT_write_en2(1)|TVE_HDMI_PXLACT_hpos_end(850)|
                                 TVE_HDMI_PXLACT_write_en1(1)|TVE_HDMI_PXLACT_hpos_st(116));
                //0xb800d030
                HDMI_WRITE_REG_INT32U(HDMI_SYNC_DLY,
                                 HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                                 HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                                 HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(2)|
                                 HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(2));
                //0xb800d154
                HDMI_WRITE_REG_INT32U(HDMI_DPC,
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
                //0xb80180b8
                TVE_WRITE_REG_INT32U(TVE_HDMI_ST,
                                 TVE_HDMI_ST_write_en4(1)|TVE_HDMI_ST_sync_en(1)|
                                 TVE_HDMI_ST_write_en3(1)|TVE_HDMI_ST_ch_sel(0)| //0:progressive, 1:interlace
                                 TVE_HDMI_ST_write_en2(1)|TVE_HDMI_ST_vpos(0)|
                                 TVE_HDMI_ST_write_en1(1)|TVE_HDMI_ST_hpos(0));
                //0xb80180bc
                TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_HS,
                                 TVE_HDMI_DISP_HS_write_en2(1)|TVE_HDMI_DISP_HS_hs_start(15)|
                                 TVE_HDMI_DISP_HS_write_en1(1)|TVE_HDMI_DISP_HS_hs_end(77));
                //0xb80180c0
                TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_VSST1,
                                 TVE_HDMI_DISP_VSST1_write_en2(1)|TVE_HDMI_DISP_VSST1_vs_st_pos1v(6)|
                                 TVE_HDMI_DISP_VSST1_write_en1(1)|TVE_HDMI_DISP_VSST1_vs_st_pos1h(15));
                //0xb80180c4
                TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_VSED1,
                                 TVE_HDMI_DISP_VSED1_write_en2(1)|TVE_HDMI_DISP_VSED1_vs_end_pos1v(12)|
                                 TVE_HDMI_DISP_VSED1_write_en1(1)|TVE_HDMI_DISP_VSED1_vs_end_pos1h(15));
                //0xb80180c8
                TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_VSST2,
                                 TVE_HDMI_DISP_VSST2_write_en2(1)|TVE_HDMI_DISP_VSST2_vs_st_pos2v(0)|
                                 TVE_HDMI_DISP_VSST2_write_en1(1)|TVE_HDMI_DISP_VSST2_vs_st_pos2h(0));
                //0xb80180cc
                TVE_WRITE_REG_INT32U(TVE_HDMI_DISP_VSED2,
                                 TVE_HDMI_DISP_VSED2_write_en2(1)|TVE_HDMI_DISP_VSED2_vs_end_pos2v(0)|
                                 TVE_HDMI_DISP_VSED2_write_en1(1)|TVE_HDMI_DISP_VSED2_vs_end_pos2h(0));
                //0xb80180d0
                TVE_WRITE_REG_INT32U(TVE_HDMI_PXLACT,
                                 TVE_HDMI_PXLACT_write_en2(1)|TVE_HDMI_PXLACT_hpos_end(850)|
                                 TVE_HDMI_PXLACT_write_en1(1)|TVE_HDMI_PXLACT_hpos_st(116));
                //0xb800d030
                HDMI_WRITE_REG_INT32U(HDMI_SYNC_DLY,
                                 HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                                 HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                                 HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(2)|
                                 HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(2));
                //0xb800d154
                HDMI_WRITE_REG_INT32U(HDMI_DPC,
                                 HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(1)|
                                 HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(0)|
                                 HDMI_DPC_write_en7(1)|HDMI_DPC_fp(0)|
                                 HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                                 HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(1)|
                                 HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(Deep_Depth)|
                                 HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(Deep_Color));
            }
        }
    }

    //=====================================================================================================
    // HDMI Control
    //=====================================================================================================
    if(Timing_Gen)
    {
        //0xb800d020
        HDMI_WRITE_REG_INT32U(HDMI_CHNL_SEL,
                         HDMI_CHNL_SEL_video_sd(1)|
                         HDMI_CHNL_SEL_Interlaced_vfmt(0)|
                         HDMI_CHNL_SEL_3D_video_format(Format_3D)|
                         HDMI_CHNL_SEL_En_3D(En_3D)|
                         HDMI_CHNL_SEL_timing_gen_en(1)|
                         HDMI_CHNL_SEL_chl_sel(0)); //0:P channel 1:I channel
    }
    else
    {
        //0xb800d020
        HDMI_WRITE_REG_INT32U(HDMI_CHNL_SEL,
                         HDMI_CHNL_SEL_video_sd(1)|
                         HDMI_CHNL_SEL_Interlaced_vfmt(0)|
                         HDMI_CHNL_SEL_3D_video_format(0xf)|
                         HDMI_CHNL_SEL_En_3D(0)|
                         HDMI_CHNL_SEL_timing_gen_en(0)|
                         HDMI_CHNL_SEL_chl_sel(0)); //0:P channel 1:I channel
    }

    if(DVI_or_HDMI==0) //DVI mode
        Pixel_Colocr_Format = 0;
    
    if(Pixel_Colocr_Format==0) //RGB mode
    {
        //-- Color Transform (YCbCr 4:4:4 -> RGB 4:4:4)
        //0xb800d024
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS0, HDMI_CS_TRANS0_c1(0x04a80));
        //0xb800d028
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS1, HDMI_CS_TRANS1_c2(0x1e700));
        //0xb800d02c
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS2, HDMI_CS_TRANS2_c3(0x1cc40));
        //0xb800d200
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS3, HDMI_CS_TRANS3_c4(0x04a80));
        //0xb800d204
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS4, HDMI_CS_TRANS4_c5(0x08140));
        //0xb800d208
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS5, HDMI_CS_TRANS5_c6(0x00000));
        //0xb800d20c
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS6, HDMI_CS_TRANS6_c7(0x04a80));
        //0xb800d210
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS7, HDMI_CS_TRANS7_c8(0x00000));
        //0xb800d214
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS8, HDMI_CS_TRANS8_c9(0x06680));
        //0xb800d218
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS9, HDMI_CS_TRANS9_k1(0x21b0));
        //0xb800d21c
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS10, HDMI_CS_TRANS10_k2(0xba70));
        //0xb800d220
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS11, HDMI_CS_TRANS11_k3(0xc840));
    }
    else //YCbCr mode
    {
        //-- Color Transform (YCbCr 4:4:4 -> RGB 4:4:4)
        //0xb800d024
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS0, HDMI_CS_TRANS0_c1(0x04000));
        //0xb800d028
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS1, HDMI_CS_TRANS1_c2(0x00000));
        //0xb800d02c
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS2, HDMI_CS_TRANS2_c3(0x00000));
        //0xb800d200
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS3, HDMI_CS_TRANS3_c4(0x00000));
        //0xb800d204
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS4, HDMI_CS_TRANS4_c5(0x04000));
        //0xb800d208
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS5, HDMI_CS_TRANS5_c6(0x00000));
        //0xb800d20c
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS6, HDMI_CS_TRANS6_c7(0x00000));
        //0xb800d210
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS7, HDMI_CS_TRANS7_c8(0x00000));
        //0xb800d214
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS8, HDMI_CS_TRANS8_c9(0x04000));
        //0xb800d218
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS9, HDMI_CS_TRANS9_k1(0x0000));
        //0xb800d21c
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS10, HDMI_CS_TRANS10_k2(0x0000));
        //0xb800d220
        HDMI_WRITE_REG_INT32U(HDMI_CS_TRANS11, HDMI_CS_TRANS11_k3(0x0000));
    }

    //0xb800d0b8
    HDMI_WRITE_REG_INT32U(HDMI_SCHCR,
                     HDMI_SCHCR_write_en10(1)|
                     HDMI_SCHCR_422_pixel_repeat(0));
    //0xb800d078
    HDMI_WRITE_REG_INT32U(HDMI_GCPCR,
                     HDMI_GCPCR_enablegcp(1)|
                     HDMI_GCPCR_gcp_clearavmute(0)|
                     HDMI_GCPCR_gcp_setavmute(0)|
                     HDMI_GCPCR_write_data(0));
    //0xb800d078
    HDMI_WRITE_REG_INT32U(HDMI_GCPCR,
                     HDMI_GCPCR_enablegcp(1)|
                     HDMI_GCPCR_gcp_clearavmute(0)|
                     HDMI_GCPCR_gcp_setavmute(0)|
                     HDMI_GCPCR_write_data(1));
    //0xb800d0a0
    HDMI_WRITE_REG_INT32U(HDMI_RPCR,
                     HDMI_RPCR_write_en6(1)|HDMI_RPCR_prp5period(0)|
                     HDMI_RPCR_write_en5(1)|HDMI_RPCR_prp4period(0)|
                     HDMI_RPCR_write_en4(1)|HDMI_RPCR_prp3period(0)|
                     HDMI_RPCR_write_en3(1)|HDMI_RPCR_prp2period(0)|
                     HDMI_RPCR_write_en2(0)|HDMI_RPCR_prp1period(0)|
                     HDMI_RPCR_write_en1(1)|HDMI_RPCR_prp0period(0));
    //0xb800d0a4
    HDMI_WRITE_REG_INT32U(HDMI_RPEN,
                     HDMI_RPEN_enprpkt5(1)|
                     HDMI_RPEN_enprpkt4(1)|
                     HDMI_RPEN_enprpkt3(1)|
                     HDMI_RPEN_enprpkt2(1)| //Metadata package clear
                     HDMI_RPEN_enprpkt1(0)| //Audio InfoFrame package clear by HDMI_audio_set
                     HDMI_RPEN_enprpkt0(1)| //AVI InfoFrame package clear
                     HDMI_RPEN_write_data(0));
    //0xb800d0b4
    HDMI_WRITE_REG_INT32U(HDMI_DIPCCR,
                     HDMI_DIPCCR_write_en2(1)|HDMI_DIPCCR_vbidipcnt(17)|//18)|//ver. max 18 packets
                     HDMI_DIPCCR_write_en1(1)|HDMI_DIPCCR_hbidipcnt(1));//hor. max 2 packets

    //=====================================================================================================
    // Scheduler
    //=====================================================================================================
    if(DVI_or_HDMI==0) //DVI mode
    {
        //0xb800d0b8
        HDMI_WRITE_REG_INT32U(HDMI_SCHCR,
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
                         HDMI_SCHCR_write_en1(1)|HDMI_SCHCR_hdmi_modesel(0)); //0:DVI mode 1:HDMI mode
    }
    else //HDMI mode
    {
        //0xb800d0b8
        HDMI_WRITE_REG_INT32U(HDMI_SCHCR,
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
                         HDMI_SCHCR_write_en1(1)|HDMI_SCHCR_hdmi_modesel(1)); //0:DVI mode 1:HDMI mode
    }

    //0xb800d0f0
    HDMI_WRITE_REG_INT32U(HDMI_HDCP_KOWR, HDMI_HDCP_KOWR_hdcprekeykeepoutwin(0x29));

    //0xb800d000
    HDMI_WRITE_REG_INT32U(HDMI_INTEN,
                     HDMI_INTEN_enriupdint(1)|
                     HDMI_INTEN_enpjupdint(1)|
                     HDMI_INTEN_write_data(0));

#if 0
    if(DVI_or_HDMI) HDMI_gen_avi_infoframe(2, Pixel_Colocr_Format, xv_YCC);

    if(En_3D) HDMI_gen_vendor_Specific_infoframe(Format_3D);

    if(DVI_or_HDMI && xv_YCC) HDMI_gen_metadata();
#endif

    //0xb800d034
    HDMI_WRITE_REG_INT32U(HDMI_CR,
                     HDMI_CR_write_en3(1)|HDMI_CR_tmds_encen(1)| //TMDS Encoder enable
                     HDMI_CR_write_en2(1)|HDMI_CR_enablehdcp(1)| //Fixed a critical case of 480p with HDCP
                     HDMI_CR_write_en1(1)|HDMI_CR_enablehdmi(1)); //HDMI enable
    return;
}
