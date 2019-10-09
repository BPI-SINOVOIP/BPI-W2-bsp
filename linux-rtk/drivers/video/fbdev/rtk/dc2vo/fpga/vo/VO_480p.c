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
#include "../include/aio_reg.h"
#include "../include/vo_reg.h"
//#######################################################################################################
//
//  File Name:      VO_480p.C
//  Description:    Vedio Output 720x480p setting
//
//#######################################################################################################
void VO_480p(INT8U Test_Pattern, INT8U Timing_Gen, INT8U Enable_3D, INT8U Format_3D, unsigned int YPhyAddr, unsigned int CPhyAddr)
{
    int leftflag = 0;
    //0xb8005008
    WRITE_REG_INT32U(VO_MIX1,
                     VO_MIX1_i_vbi(1)|
                     VO_MIX1_vbi(1)|
                     VO_MIX1_osd1(1)|
                     VO_MIX1_sub1(1)|
                     VO_MIX1_v1(1)|
                     VO_MIX1_bg(1)|
                     VO_MIX1_write_data(0));
    //0xb8005008
    WRITE_REG_INT32U(VO_MIX1,
                     VO_MIX1_i_vbi(0)|
                     VO_MIX1_vbi(0)|
                     VO_MIX1_osd1(0)|
                     VO_MIX1_sub1(0)|
                     VO_MIX1_v1(1)|
                     VO_MIX1_bg(0)|
                     VO_MIX1_write_data(1));
    //0xb8005014
    WRITE_REG_INT32U(VO_3D,
                     VO_3D_top_and_bottom(1)|
                     VO_3D_side_by_side(1)|
                     VO_3D_right(1)|
                     VO_3D_write_data(0));
    //0xb8005020
    WRITE_REG_INT32U(VO_V1,
                     VO_V1_d3_dbh(1)|
                     VO_V1_d3_dbw(1)|
                     VO_V1_d3_dup(1)|
                     VO_V1_st(1)|
                     VO_V1_seq(1)|
                     VO_V1_di(1)|
                     VO_V1_f422(1)|
                     VO_V1_vs(1)|
                     VO_V1_vs_near(1)|
                     VO_V1_vs_yodd(1)|
                     VO_V1_vs_codd(1)|
                     VO_V1_hs(1)|
                     VO_V1_hs_yodd(1)|
                     VO_V1_hs_codd(1)|
                     VO_V1_topfield(1)|
                     VO_V1_dmaweave(1)|
                     VO_V1_write_data(0));
#if 0
    if(Enable_3D==1) //3D
    {
        //0xb8005000
        WRITE_REG_INT32U(VO_MODE,
                         VO_MODE_ch2i(0)|
                         VO_MODE_ch2(0)|
                         VO_MODE_ch1i(0)|
                         VO_MODE_ch1(1)|
                         VO_MODE_write_data(1));
        //0xb8005000
        WRITE_REG_INT32U(VO_MODE,
                         VO_MODE_ch2i(1)|
                         VO_MODE_ch2(1)|
                         VO_MODE_ch1i(1)|
                         VO_MODE_ch1(0)|
                         VO_MODE_write_data(0));
        //0xb8005004
        WRITE_REG_INT32U(VO_OUT,
                         VO_OUT_write_en3(1)|VO_OUT_h(1)|
                         VO_OUT_write_en2(1)|VO_OUT_i(0)|
                         VO_OUT_write_en1(1)|VO_OUT_p(0));
        if(Format_3D==0)
        {
            //0xb8005020
            WRITE_REG_INT32U(VO_V1,
                             VO_V1_d3_dbh(0)|
                             VO_V1_d3_dbw(0)|
                             VO_V1_d3_dup(0)|
                             VO_V1_st(0)|
                             VO_V1_seq(1)|
                             VO_V1_di(0)|
                             VO_V1_f422(1)|
                             VO_V1_vs(0)|
                             VO_V1_vs_near(0)|
                             VO_V1_vs_yodd(0)|
                             VO_V1_vs_codd(0)|
                             VO_V1_hs(0)|
                             VO_V1_hs_yodd(0)|
                             VO_V1_hs_codd(0)|
                             VO_V1_topfield(0)|
                             VO_V1_dmaweave(0)|
                             VO_V1_write_data(1));
            //0xb8005038
            WRITE_REG_INT32U(VO_V1_SEQ_SA_C_Y, VO_V1_SEQ_SA_C_Y_a(0xe000000));
            //0xb800503c
            WRITE_REG_INT32U(VO_V1_SEQ_SA_C_C, VO_V1_SEQ_SA_C_C_a(0xe060000));
            //0xb8005058
            WRITE_REG_INT32U(VO_V1_SEQ_SA_C_Y_3D, VO_V1_SEQ_SA_C_Y_3D_a(0xe7b8000));
            //0xb800505c
            WRITE_REG_INT32U(VO_V1_SEQ_SA_C_C_3D, VO_V1_SEQ_SA_C_C_3D_a(0xe818000));
            //0xb8005048
            WRITE_REG_INT32U(VO_V1_SEQ_PITCH_C_Y, VO_V1_SEQ_PITCH_C_Y_p(720));
            //0xb800504c
            WRITE_REG_INT32U(VO_V1_SEQ_PITCH_C_C, VO_V1_SEQ_PITCH_C_C_p(720));
            //0xb8005068
            WRITE_REG_INT32U(VO_V1_SIZE,
                             VO_V1_SIZE_w(720)|
                             VO_V1_SIZE_h(480));
            //0xb8005604
            WRITE_REG_INT32U(VO_M1_SIZE,
                             VO_M1_SIZE_w(720)|
                             VO_M1_SIZE_h(480));
        }
        if(Format_3D==6)
        {
            //0xb8005020
            WRITE_REG_INT32U(VO_V1,
                             VO_V1_d3_dbh(1)|
                             VO_V1_d3_dbw(0)|
                             VO_V1_d3_dup(0)|
                             VO_V1_st(0)|
                             VO_V1_seq(1)|
                             VO_V1_di(0)|
                             VO_V1_f422(1)|
                             VO_V1_vs(0)|
                             VO_V1_vs_near(0)|
                             VO_V1_vs_yodd(0)|
                             VO_V1_vs_codd(0)|
                             VO_V1_hs(0)|
                             VO_V1_hs_yodd(0)|
                             VO_V1_hs_codd(0)|
                             VO_V1_topfield(0)|
                             VO_V1_dmaweave(0)|
                             VO_V1_write_data(1));
            //0xb8005038
            WRITE_REG_INT32U(VO_V1_SEQ_SA_C_Y, VO_V1_SEQ_SA_C_Y_a(0xd000000));
            //0xb800503c
            WRITE_REG_INT32U(VO_V1_SEQ_SA_C_C, VO_V1_SEQ_SA_C_C_a(0xd060000));
            //0xb8005048
            WRITE_REG_INT32U(VO_V1_SEQ_PITCH_C_Y, VO_V1_SEQ_PITCH_C_Y_p(720));
            //0xb800504c
            WRITE_REG_INT32U(VO_V1_SEQ_PITCH_C_C, VO_V1_SEQ_PITCH_C_C_p(720));
            //0xb8005068
            WRITE_REG_INT32U(VO_V1_SIZE,
                             VO_V1_SIZE_w(720)|
                             VO_V1_SIZE_h(240));
            //0xb8005604
            WRITE_REG_INT32U(VO_M1_SIZE,
                             VO_M1_SIZE_w(720)|
                             VO_M1_SIZE_h(240));
        }
        if(Format_3D==8)
        {
            //0xb8005020
            WRITE_REG_INT32U(VO_V1,
                             VO_V1_d3_dbh(0)|
                             VO_V1_d3_dbw(1)|
                             VO_V1_d3_dup(0)|
                             VO_V1_st(0)|
                             VO_V1_seq(1)|
                             VO_V1_di(0)|
                             VO_V1_f422(1)|
                             VO_V1_vs(0)|
                             VO_V1_vs_near(0)|
                             VO_V1_vs_yodd(0)|
                             VO_V1_vs_codd(0)|
                             VO_V1_hs(0)|
                             VO_V1_hs_yodd(0)|
                             VO_V1_hs_codd(0)|
                             VO_V1_topfield(0)|
                             VO_V1_dmaweave(0)|
                             VO_V1_write_data(1));
            //0xb8005038
            WRITE_REG_INT32U(VO_V1_SEQ_SA_C_Y, VO_V1_SEQ_SA_C_Y_a(0xd7b8000));
            //0xb800503c
            WRITE_REG_INT32U(VO_V1_SEQ_SA_C_C, VO_V1_SEQ_SA_C_C_a(0xd818000));
            //0xb8005048
            WRITE_REG_INT32U(VO_V1_SEQ_PITCH_C_Y, VO_V1_SEQ_PITCH_C_Y_p(720));
            //0xb800504c
            WRITE_REG_INT32U(VO_V1_SEQ_PITCH_C_C, VO_V1_SEQ_PITCH_C_C_p(720));
            //0xb8005068
            WRITE_REG_INT32U(VO_V1_SIZE,
                             VO_V1_SIZE_w(360)|
                             VO_V1_SIZE_h(480));
            //0xb8005604
            WRITE_REG_INT32U(VO_M1_SIZE,
                             VO_M1_SIZE_w(360)|
                             VO_M1_SIZE_h(480));
        }
        //0xb8005610
        WRITE_REG_INT32U(VO_V1_XY,
                         VO_V1_XY_x(0)|
                         VO_V1_XY_y(0));
        //0xb8005644
        WRITE_REG_INT32U(VO_CH1,
                         VO_CH1_itop(1)|
                         VO_CH1_ireint(1)|
                         VO_CH1_top(1)|
                         VO_CH1_reint(1)|
                         VO_CH1_write_data(0));
    }
    else //2D
#endif
    {
        //0xb8005000
        WRITE_REG_INT32U(VO_MODE,
                         VO_MODE_ch2i(0)|
                         VO_MODE_ch2(0)|
                         VO_MODE_ch1i(0)|
                         VO_MODE_ch1(1)|
                         VO_MODE_write_data(1));
        //0xb8005000
        WRITE_REG_INT32U(VO_MODE,
                         VO_MODE_ch2i(1)|
                         VO_MODE_ch2(1)|
                         VO_MODE_ch1i(1)|
                         VO_MODE_ch1(0)|
                         VO_MODE_write_data(0));
        if(Timing_Gen)
        {
            //0xb8005004
            WRITE_REG_INT32U(VO_OUT,
                             VO_OUT_write_en3(1)|VO_OUT_h(1)|
                             VO_OUT_write_en2(1)|VO_OUT_i(0)|
                             VO_OUT_write_en1(1)|VO_OUT_p(0));
        }
        else
        {
            //0xb8005004
            WRITE_REG_INT32U(VO_OUT,
                             VO_OUT_write_en3(1)|VO_OUT_h(0)|
                             VO_OUT_write_en2(1)|VO_OUT_i(0)|
                             VO_OUT_write_en1(1)|VO_OUT_p(1));
        }
        //0xb8005020
        WRITE_REG_INT32U(VO_V1,
                         VO_V1_d3_dbh(0)|
                         VO_V1_d3_dbw(0)|
                         VO_V1_d3_dup(0)|
                         VO_V1_st(0)|
                         VO_V1_seq(1)|
                         VO_V1_di(0)|
                         VO_V1_f422(1)|
                         VO_V1_vs(0)|
                         VO_V1_vs_near(0)|
                         VO_V1_vs_yodd(0)|
                         VO_V1_vs_codd(0)|
                         VO_V1_hs(0)|
                         VO_V1_hs_yodd(0)|
                         VO_V1_hs_codd(0)|
                         VO_V1_topfield(0)|
                         VO_V1_dmaweave(0)|
                         VO_V1_write_data(1));
        if(Test_Pattern)
        {
            //0xb8005038
            WRITE_REG_INT32U(VO_V1_SEQ_SA_C_Y, VO_V1_SEQ_SA_C_Y_a(YPhyAddr));
            //0xb800503c
            WRITE_REG_INT32U(VO_V1_SEQ_SA_C_C, VO_V1_SEQ_SA_C_C_a(CPhyAddr));
        }
        else
        {
            //0xb8005038
            WRITE_REG_INT32U(VO_V1_SEQ_SA_C_Y, VO_V1_SEQ_SA_C_Y_a(YPhyAddr));
            //0xb800503c
            WRITE_REG_INT32U(VO_V1_SEQ_SA_C_C, VO_V1_SEQ_SA_C_C_a(CPhyAddr));
        }
        //0xb8005048
        WRITE_REG_INT32U(VO_V1_SEQ_PITCH_C_Y, VO_V1_SEQ_PITCH_C_Y_p(720));
        //0xb800504c
        WRITE_REG_INT32U(VO_V1_SEQ_PITCH_C_C, VO_V1_SEQ_PITCH_C_C_p(720));
        //0xb8005068
        WRITE_REG_INT32U(VO_V1_SIZE,
                         VO_V1_SIZE_w(720)|
                         VO_V1_SIZE_h(480));
        //0xb8005604
        WRITE_REG_INT32U(VO_M1_SIZE,
                         VO_M1_SIZE_w(720)|
                         VO_M1_SIZE_h(480));
        //0xb8005610
        WRITE_REG_INT32U(VO_V1_XY,
                         VO_V1_XY_x(0)|
                         VO_V1_XY_y(0));
        //0xb8005644
        WRITE_REG_INT32U(VO_CH1,
                         VO_CH1_itop(1)|
                         VO_CH1_ireint(1)|
                         VO_CH1_top(1)|
                         VO_CH1_reint(1)|
                         VO_CH1_write_data(0));
    }

    //--------------------------------------------------------------
    //Set TVE general control
    //--------------------------------------------------------------
    //0xb8018040
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

#if 0

    while(*UART_flag==1)
    {
        UART_READ();
        if(Enable_3D==1) //3D
        {
            if(Format_3D==0)
            {
                if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV))
                {
                    leftflag = 1;
                    //0xb800d278
                    WRITE_REG_INT32U(HDMI_INTSTV,
                                     HDMI_INTSTV_vendupdated(0)|
                                     HDMI_INTSTV_vsyncupdated(0));
                    //0xb8005014
                    WRITE_REG_INT32U(VO_3D,
                                     VO_3D_top_and_bottom(0)|
                                     VO_3D_side_by_side(0)|
                                     VO_3D_right(1)|
                                     VO_3D_write_data(0));
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
                }
                if(HDMI_INTSTV_get_vendupdated(*(volatile unsigned int *)HDMI_INTSTV) && leftflag)
                {
                    leftflag = 0;                                
                    //0xb800d278
                    WRITE_REG_INT32U(HDMI_INTSTV,
                                     HDMI_INTSTV_vendupdated(0)|
                                     HDMI_INTSTV_vsyncupdated(0));
                    //0xb8005014
                    WRITE_REG_INT32U(VO_3D,
                                     VO_3D_top_and_bottom(0)|
                                     VO_3D_side_by_side(0)|
                                     VO_3D_right(1)|
                                     VO_3D_write_data(1));
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
                }
            }
            if(Format_3D==6)
            {
                if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV))
                {
                    //0xb800d278
                    WRITE_REG_INT32U(HDMI_INTSTV,
                                     HDMI_INTSTV_vendupdated(0)|
                                     HDMI_INTSTV_vsyncupdated(0));
                    //0xb8005014
                    WRITE_REG_INT32U(VO_3D,
                                     VO_3D_top_and_bottom(1)|
                                     VO_3D_side_by_side(0)|
                                     VO_3D_right(0)|
                                     VO_3D_write_data(1));
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
                }
            } 
            if(Format_3D==8)
            {
                if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV))
                {
                    //0xb800d278
                    WRITE_REG_INT32U(HDMI_INTSTV,
                                     HDMI_INTSTV_vendupdated(0)|
                                     HDMI_INTSTV_vsyncupdated(0));
                    //0xb8005014
                    WRITE_REG_INT32U(VO_3D,
                                     VO_3D_top_and_bottom(0)|
                                     VO_3D_side_by_side(1)|
                                     VO_3D_right(0)|
                                     VO_3D_write_data(1));
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
                }
            }
            if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST))
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
        else //2D
        {
            if(HDMI_INTSTV_get_vsyncupdated(*(volatile unsigned int *)HDMI_INTSTV))
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
                    if(VO_INTST_get_h_under(*(volatile unsigned int *)VO_INTST))
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
                    if(VO_INTST_get_p_under(*(volatile unsigned int *)VO_INTST))
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
    }
#endif
}
