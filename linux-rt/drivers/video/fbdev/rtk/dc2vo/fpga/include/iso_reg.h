/**************************************************************
// Spec Version                  : 0.41
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/8/1 21:17:43
***************************************************************/


#ifndef _ISO_REG_H_INCLUDED_
#define _ISO_REG_H_INCLUDED_
#ifdef  _ISO_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     cec_int:1;
unsigned int     reserved_1:1;
unsigned int     gpioda_int:1;
unsigned int     gpioa_int:1;
unsigned int     vfd_ardswda_int:1;
unsigned int     vfd_ardswa_int:1;
unsigned int     vfd_ardkpadda_int:1;
unsigned int     vfd_ardkpada_int:1;
unsigned int     vfd_wdone_int:1;
unsigned int     rtc_alarm_int:1;
unsigned int     rtc_hsec_int:1;
unsigned int     reserved_2:1;
unsigned int     i2c6_int:1;
unsigned int     tc4_int:1;
unsigned int     i2c0_int:1;
unsigned int     wdog_nmi_int:1;
unsigned int     reserved_3:1;
unsigned int     irda_int:1;
unsigned int     reserved_4:2;
unsigned int     ur0_int:1;
unsigned int     tc3_int:1;
unsigned int     write_data:1;
}ISO_ISR;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     gpioda_int:1;
unsigned int     gpioa_int:1;
unsigned int     vfd_ardswda_int:1;
unsigned int     vfd_ardswa_int:1;
unsigned int     vfd_ardkpadda_int:1;
unsigned int     vfd_ardkpada_int:1;
unsigned int     vfd_wdone_int:1;
unsigned int     rtc_alarm_int:1;
unsigned int     rtc_hsec_int:1;
unsigned int     reserved_1:2;
unsigned int     tc4_int:1;
unsigned int     reserved_2:1;
unsigned int     wdog_nmi_int:1;
unsigned int     reserved_3:1;
unsigned int     irda_int:1;
unsigned int     reserved_4:3;
unsigned int     tc3_int:1;
unsigned int     write_data:1;
}ISO_UMSK_ISR;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     int20_a:1;
unsigned int     int19_a:1;
unsigned int     int18_a:1;
unsigned int     int17_a:1;
unsigned int     int16_a:1;
unsigned int     int15_a:1;
unsigned int     int14_a:1;
unsigned int     int13_a:1;
unsigned int     int12_a:1;
unsigned int     int11_a:1;
unsigned int     int10_a:1;
unsigned int     int9_a:1;
unsigned int     int8_a:1;
unsigned int     int7_a:1;
unsigned int     int6_a:1;
unsigned int     int5_a:1;
unsigned int     int4_a:1;
unsigned int     int3_a:1;
unsigned int     int2_a:1;
unsigned int     int1_a:1;
unsigned int     int0_a:1;
unsigned int     write_data:1;
}ISO_UMSK_ISR_GPA;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     int20_da:1;
unsigned int     int19_da:1;
unsigned int     int18_da:1;
unsigned int     int17_da:1;
unsigned int     int16_da:1;
unsigned int     int15_da:1;
unsigned int     int14_da:1;
unsigned int     int13_da:1;
unsigned int     int12_da:1;
unsigned int     int11_da:1;
unsigned int     int10_da:1;
unsigned int     int9_da:1;
unsigned int     int8_da:1;
unsigned int     int7_da:1;
unsigned int     int6_da:1;
unsigned int     int5_da:1;
unsigned int     int4_da:1;
unsigned int     int3_da:1;
unsigned int     int2_da:1;
unsigned int     int1_da:1;
unsigned int     int0_da:1;
unsigned int     write_data:1;
}ISO_UMSK_ISR_GPDA;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     int47:1;
unsigned int     int46:1;
unsigned int     int45:1;
unsigned int     int44:1;
unsigned int     int43:1;
unsigned int     int42:1;
unsigned int     int41:1;
unsigned int     int40:1;
unsigned int     int39:1;
unsigned int     int38:1;
unsigned int     int37:1;
unsigned int     int36:1;
unsigned int     int35:1;
unsigned int     int34:1;
unsigned int     int33:1;
unsigned int     int32:1;
unsigned int     int31:1;
unsigned int     int30:1;
unsigned int     int29:1;
unsigned int     int28:1;
unsigned int     reserved_1:3;
unsigned int     write_data:1;
}ISO_UMSK_ISR_KPADAH;

typedef struct 
{
unsigned int     int27:1;
unsigned int     int26:1;
unsigned int     int25:1;
unsigned int     int24:1;
unsigned int     int23:1;
unsigned int     int22:1;
unsigned int     int21:1;
unsigned int     int20:1;
unsigned int     int19:1;
unsigned int     int18:1;
unsigned int     int17:1;
unsigned int     int16:1;
unsigned int     int15:1;
unsigned int     int14:1;
unsigned int     int13:1;
unsigned int     int12:1;
unsigned int     int11:1;
unsigned int     int10:1;
unsigned int     int9:1;
unsigned int     int8:1;
unsigned int     int7:1;
unsigned int     int6:1;
unsigned int     int5:1;
unsigned int     int4:1;
unsigned int     int3:1;
unsigned int     int2:1;
unsigned int     int1:1;
unsigned int     int0:1;
unsigned int     reserved_0:3;
unsigned int     write_data:1;
}ISO_UMSK_ISR_KPADAL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     int47:1;
unsigned int     int46:1;
unsigned int     int45:1;
unsigned int     int44:1;
unsigned int     int43:1;
unsigned int     int42:1;
unsigned int     int41:1;
unsigned int     int40:1;
unsigned int     int39:1;
unsigned int     int38:1;
unsigned int     int37:1;
unsigned int     int36:1;
unsigned int     int35:1;
unsigned int     int34:1;
unsigned int     int33:1;
unsigned int     int32:1;
unsigned int     int31:1;
unsigned int     int30:1;
unsigned int     int29:1;
unsigned int     int28:1;
unsigned int     reserved_1:3;
unsigned int     write_data:1;
}ISO_UMSK_ISR_KPADDAH;

typedef struct 
{
unsigned int     int27:1;
unsigned int     int26:1;
unsigned int     int25:1;
unsigned int     int24:1;
unsigned int     int23:1;
unsigned int     int22:1;
unsigned int     int21:1;
unsigned int     int20:1;
unsigned int     int19:1;
unsigned int     int18:1;
unsigned int     int17:1;
unsigned int     int16:1;
unsigned int     int15:1;
unsigned int     int14:1;
unsigned int     int13:1;
unsigned int     int12:1;
unsigned int     int11:1;
unsigned int     int10:1;
unsigned int     int9:1;
unsigned int     int8:1;
unsigned int     int7:1;
unsigned int     int6:1;
unsigned int     int5:1;
unsigned int     int4:1;
unsigned int     int3:1;
unsigned int     int2:1;
unsigned int     int1:1;
unsigned int     int0:1;
unsigned int     reserved_0:3;
unsigned int     write_data:1;
}ISO_UMSK_ISR_KPADDAL;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     da_int3:1;
unsigned int     da_int2:1;
unsigned int     da_int1:1;
unsigned int     da_int0:1;
unsigned int     a_int3:1;
unsigned int     a_int2:1;
unsigned int     a_int1:1;
unsigned int     a_int0:1;
unsigned int     reserved_1:3;
unsigned int     write_data:1;
}ISO_UMSK_ISR_SW;

typedef struct 
{
unsigned int     write_en5:1;
unsigned int     standby_dbg_sel:7;
unsigned int     write_en4:1;
unsigned int     reserved_0:2;
unsigned int     standby_dbg_en:1;
unsigned int     write_en3:1;
unsigned int     reserved_1:3;
unsigned int     sel1:4;
unsigned int     write_en2:1;
unsigned int     reserved_2:3;
unsigned int     sel0:4;
unsigned int     write_en1:1;
unsigned int     reserved_3:2;
unsigned int     enable:1;
}ISO_DBG;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     testmode:1;
unsigned int     boot_sel:1;
unsigned int     bound_opt:13;
}ISO_CHIP_INFO1;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     pow_latch:19;
}ISO_CHIP_INFO2;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_en9:1;
unsigned int     iso_rst_wd_mask:1;
unsigned int     write_en8:1;
unsigned int     dc_phy_cke_pd:1;
unsigned int     write_en7:1;
unsigned int     iso_mis_clk_en:1;
unsigned int     write_en6:1;
unsigned int     iso_rbus_sel:1;
unsigned int     write_en5:1;
unsigned int     iso_rst_mask:1;
unsigned int     write_en4:1;
unsigned int     clk_osc_on_en:1;
unsigned int     write_en3:1;
unsigned int     crt_sw_rstn:1;
unsigned int     write_en2:1;
unsigned int     iso_clk_sel:1;
unsigned int     write_en1:1;
unsigned int     ejtag_en:1;
}ISO_CTRL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     hsec_int_en:1;
unsigned int     alarm_int_en:1;
}ISO_RTC;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     bi_bypass:1;
unsigned int     iso_ctrl_en1:1;
unsigned int     iso_ctrl_en0:1;
}ISO_CELL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     top_vdd_on:1;
unsigned int     scpu_vdd_on:1;
}ISO_POWER;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     cec:1;
unsigned int     reserved_1:1;
unsigned int     gpioda:1;
unsigned int     gpioa:1;
unsigned int     vfd_ardswda:1;
unsigned int     vfd_ardswa:1;
unsigned int     vfd_ardkpadda:1;
unsigned int     vfd_ardkpada:1;
unsigned int     vfd_wdone:1;
unsigned int     rtc_alarm:1;
unsigned int     rtc_hsec:1;
unsigned int     reserved_2:1;
unsigned int     i2c6:1;
unsigned int     reserved_3:1;
unsigned int     i2c0:1;
unsigned int     reserved_4:2;
unsigned int     irda:1;
unsigned int     reserved_5:2;
unsigned int     ur0:1;
unsigned int     reserved_6:2;
}ISO_SCPU_INT_EN;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     dcp_ctrl1:1;
unsigned int     dcp_ctrl0:1;
}ISO_USB;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     cec:1;
unsigned int     reserved_1:1;
unsigned int     gpioda:1;
unsigned int     gpioa:1;
unsigned int     vfd_ardswda:1;
unsigned int     vfd_ardswa:1;
unsigned int     vfd_ardkpadda:1;
unsigned int     vfd_ardkpada:1;
unsigned int     vfd_wdone:1;
unsigned int     rtc_alarm:1;
unsigned int     rtc_hsec:1;
unsigned int     reserved_2:1;
unsigned int     i2c6:1;
unsigned int     reserved_3:1;
unsigned int     i2c0:1;
unsigned int     reserved_4:2;
unsigned int     irda:1;
unsigned int     reserved_5:2;
unsigned int     ur0:1;
unsigned int     reserved_6:2;
}ISO_ACPU_INT_EN;

typedef struct 
{
unsigned int     acpu_boot_info:32;
}ISO_CPU_ST1;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     acpu_boot_info_valid:1;
}ISO_CPU_ST1V;

typedef struct 
{
unsigned int     rvd31:1;
unsigned int     rvd30:1;
unsigned int     rvd29:1;
unsigned int     rvd28:1;
unsigned int     rvd27:1;
unsigned int     rvd26:1;
unsigned int     rvd25:1;
unsigned int     rvd24:1;
unsigned int     rvd23:1;
unsigned int     rvd22:1;
unsigned int     rvd21:1;
unsigned int     rvd20:1;
unsigned int     rvd19:1;
unsigned int     rvd18:1;
unsigned int     rvd17:1;
unsigned int     rvd16:1;
unsigned int     rvd15:1;
unsigned int     rvd14:1;
unsigned int     rvd13:1;
unsigned int     rvd12:1;
unsigned int     rvd11:1;
unsigned int     rvd10:1;
unsigned int     rvd9:1;
unsigned int     rvd8:1;
unsigned int     rvd7:1;
unsigned int     rvd6:1;
unsigned int     rvd5:1;
unsigned int     rvd4:1;
unsigned int     rvd3:1;
unsigned int     rvd2:1;
unsigned int     rvd1:1;
unsigned int     rvd0:1;
}ISO_DUMMY1;

typedef struct 
{
unsigned int     rvd31:1;
unsigned int     rvd30:1;
unsigned int     rvd29:1;
unsigned int     rvd28:1;
unsigned int     rvd27:1;
unsigned int     rvd26:1;
unsigned int     rvd25:1;
unsigned int     rvd24:1;
unsigned int     rvd23:1;
unsigned int     rvd22:1;
unsigned int     rvd21:1;
unsigned int     rvd20:1;
unsigned int     rvd19:1;
unsigned int     rvd18:1;
unsigned int     rvd17:1;
unsigned int     rvd16:1;
unsigned int     rvd15:1;
unsigned int     rvd14:1;
unsigned int     rvd13:1;
unsigned int     rvd12:1;
unsigned int     rvd11:1;
unsigned int     rvd10:1;
unsigned int     rvd9:1;
unsigned int     rvd8:1;
unsigned int     rvd7:1;
unsigned int     rvd6:1;
unsigned int     rvd5:1;
unsigned int     rvd4:1;
unsigned int     rvd3:1;
unsigned int     rvd2:1;
unsigned int     rvd1:1;
unsigned int     rvd0:1;
}ISO_DUMMY2;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     powercut_ana_d2a_isolate_b:1;
unsigned int     powercut_ana_a2d_isolate_b:1;
}ISO_POWERCUT_ETN;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     etn_bpsgphy_mode:1;
unsigned int     etn_ocd_mode:1;
}ISO_ETN_TESTIO;

typedef struct 
{
unsigned int     dmy:32;
}ISO_RESERVED_USE_0;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     ir_tx:1;
unsigned int     ir_raw:1;
}ISO_LPI;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     cnt_wait_pwr:16;
}ISO_WD;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     plletn_wdout:1;
}ISO_PLL_WDOUT;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     plletn_oeb:1;
unsigned int     plletn_rstb:1;
unsigned int     plletn_o:4;
unsigned int     plletn_m:7;
unsigned int     plletn_ldo_pow:1;
unsigned int     plletn_pow:1;
unsigned int     plletn_ldo_sel:2;
unsigned int     plletn_wdmode:2;
unsigned int     plletn_n:2;
unsigned int     plletn_lf_rs:2;
unsigned int     plletn_lf_cp:2;
unsigned int     plletn_ip:3;
}ISO_PLL_ETN;

typedef struct 
{
unsigned int     dmy:32;
}ISO_RESERVED_USE_1;

typedef struct 
{
unsigned int     dmy:32;
}ISO_RESERVED_USE_2;

typedef struct 
{
unsigned int     dmy:32;
}ISO_RESERVED_USE_3;

typedef struct 
{
unsigned int     dmy1:20;
unsigned int     reserved_0:3;
unsigned int     en:1;
unsigned int     reserved_1:3;
unsigned int     sel:5;
}ISO_I2C0_SDA_DEL;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     rstn_cbus:1;
unsigned int     rstn_i2c_6:1;
unsigned int     rstn_i2c_0:1;
unsigned int     rstn_gphy:1;
unsigned int     rstn_gmac:1;
unsigned int     rstn_ur0:1;
unsigned int     rstn_efuse:1;
unsigned int     rstn_cbusrx:1;
unsigned int     rstn_cbustx:1;
unsigned int     rstn_dp:1;
unsigned int     rstn_cec1:1;
unsigned int     rstn_cec0:1;
unsigned int     rstn_ir:1;
unsigned int     rstn_vfd:1;
}ISO_SOFT_RESET;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     clk_en_etn_sys:1;
unsigned int     clk_en_etn_250m:1;
unsigned int     clk_en_i2c6:1;
unsigned int     clk_en_i2c0:1;
unsigned int     clk_en_misc_ur0:1;
unsigned int     clk_en_misc_ir:1;
unsigned int     clk_en_cbus_osc:1;
unsigned int     clk_en_cbus_sys:1;
unsigned int     clk_en_cbustx_sys:1;
unsigned int     clk_en_cbusrx_sys:1;
unsigned int     clk_en_misc_cec0:1;
unsigned int     clk_en_misc_vfd:1;
unsigned int     clk_en_misc_mix:1;
}ISO_CLOCK_ENABLE;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     rd_only_0_en:1;
unsigned int     reserved_1:2;
unsigned int     blk_protect_0_wpro_en:1;
unsigned int     reserved_2:2;
unsigned int     blk_protect_0_en:1;
unsigned int     reserved_3:8;
unsigned int     protect_0_wpro_en:1;
unsigned int     reserved_4:8;
unsigned int     protect_0_en:1;
}ISO_DC_0;

typedef struct 
{
unsigned int     mem_saddr0:20;
unsigned int     reserved_0:12;
}ISO_DC_1;

typedef struct 
{
unsigned int     mem_eaddr0:20;
unsigned int     reserved_0:12;
}ISO_DC_2;

typedef struct 
{
unsigned int     blk_saddr0:20;
unsigned int     reserved_0:12;
}ISO_DC_3;

typedef struct 
{
unsigned int     blk_eaddr0:20;
unsigned int     reserved_0:12;
}ISO_DC_4;

typedef struct 
{
unsigned int     ro_saddr0:20;
unsigned int     reserved_0:12;
}ISO_DC_5;

typedef struct 
{
unsigned int     ro_eaddr0:20;
unsigned int     reserved_0:12;
}ISO_DC_6;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     md_tee_protect_en:1;
unsigned int     reserved_1:7;
unsigned int     cp_tee_protect_en:1;
unsigned int     reserved_2:7;
unsigned int     vo_protect_en:1;
unsigned int     reserved_3:7;
unsigned int     nf_tee_protect_en:1;
}ISO_DC_7;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     scpu_tee_protect_en:1;
unsigned int     reserved_1:7;
unsigned int     acpu_protect_en:1;
unsigned int     reserved_2:7;
unsigned int     video_protect_en:1;
unsigned int     reserved_3:7;
unsigned int     audio_protect_en:1;
}ISO_DC_8;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     scpu_tee_blk_protect_en:1;
unsigned int     reserved_1:1;
unsigned int     acpu_blk_protect_en:1;
unsigned int     reserved_2:1;
unsigned int     video_blk_protect_en:1;
unsigned int     reserved_3:1;
unsigned int     audio_blk_protect_en:1;
unsigned int     reserved_4:1;
unsigned int     md_tee_blk_protect_en:1;
unsigned int     reserved_5:1;
unsigned int     cp_tee_blk_protect_en:1;
unsigned int     reserved_6:1;
unsigned int     vo_blk_protect_en:1;
unsigned int     reserved_7:1;
unsigned int     nf_tee_blk_protect_en:1;
}ISO_DC_9;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     scpu_tee_ro_protect_en:1;
unsigned int     reserved_1:3;
unsigned int     acpu_ro_protect_en:1;
unsigned int     reserved_2:3;
unsigned int     video_ro_protect_en:1;
unsigned int     reserved_3:3;
unsigned int     audio_ro_protect_en:1;
unsigned int     reserved_4:3;
unsigned int     md_tee_ro_protect_en:1;
unsigned int     reserved_5:3;
unsigned int     cp_tee_ro_protect_en:1;
unsigned int     reserved_6:3;
unsigned int     vo_ro_protect_en:1;
unsigned int     reserved_7:3;
unsigned int     nf_tee_ro_protect_en:1;
}ISO_DC_A;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     xtal_pad_drv:2;
}ISO_PLL_XTAL_CTRL;

typedef struct 
{
unsigned int     dmy1:20;
unsigned int     reserved_0:3;
unsigned int     en:1;
unsigned int     reserved_1:3;
unsigned int     sel:5;
}ISO_I2C6_SDA_DEL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     int_option:1;
}ISO_HDMI_RX;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     i2c6_mis_mux:1;
}ISO_I2C6_MUX;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     usb2sram_ctrl:1;
unsigned int     ve_encode_block_nwc:1;
unsigned int     ve_block_nwc:1;
unsigned int     vo_block_nwc:1;
unsigned int     dc_mem_port_lock:1;
unsigned int     secure_rbus:1;
}ISO_SB2_0;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     gpdir:21;
}ISO_GPDIR;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     gpdato:21;
}ISO_GPDATO;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     gpdati:21;
}ISO_GPDATI;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     gp:21;
}ISO_GPIE;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     gpha:21;
}ISO_GPDP;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     write_en1:1;
unsigned int     clk1:3;
}ISO_GPDEB;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     kpaden:1;
unsigned int     swen:1;
unsigned int     clksel:1;
unsigned int     envfd:1;
}ISO_VFD_CTL;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     nact_csn:1;
unsigned int     b3c:1;
unsigned int     b2c:1;
unsigned int     b1c:1;
unsigned int     b0c:1;
unsigned int     enb3:1;
unsigned int     enb2:1;
unsigned int     enb1:1;
unsigned int     enb0:1;
unsigned int     reserved_1:2;
unsigned int     wd:1;
unsigned int     wdie:1;
}ISO_VFD_WRCTL;

typedef struct 
{
unsigned int     byte3:8;
unsigned int     byte2:8;
unsigned int     byte1:8;
unsigned int     byte0:8;
}ISO_VFDO;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     kpadbn:3;
unsigned int     reserved_1:2;
unsigned int     swha:1;
unsigned int     kpadha:1;
unsigned int     reserved_2:2;
unsigned int     ardp:2;
}ISO_VFD_ARDCTL;

typedef struct 
{
unsigned int     kpadie:32;
}ISO_VFD_KPADLIE;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     kpadie:16;
}ISO_VFD_KPADHIE;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     swie:4;
}ISO_VFD_SWIE;

typedef struct 
{
unsigned int     st_31_24:8;
unsigned int     st_23_16:8;
unsigned int     st_15_8:8;
unsigned int     st_7_0:8;
}ISO_VFD_ARDKPADL;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     st_15_8:8;
unsigned int     st_7_0:8;
}ISO_VFD_ARDKPADH;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     rvda:12;
unsigned int     st:4;
}ISO_VFD_ARDSW;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     clksel_1:1;
unsigned int     tclk_csn:8;
unsigned int     twait1:8;
}ISO_VFD_CTL1;

typedef struct 
{
unsigned int     i2c_scl_0_smt:1;
unsigned int     i2c_scl_0_e2:1;
unsigned int     i2c_scl_0_pud_en:1;
unsigned int     i2c_scl_0_pud_sel:1;
unsigned int     i2c_sda_0_smt:1;
unsigned int     i2c_sda_0_e2:1;
unsigned int     i2c_sda_0_pud_en:1;
unsigned int     i2c_sda_0_pud_sel:1;
unsigned int     vfd_d_smt:1;
unsigned int     vfd_d_e2:1;
unsigned int     vfd_d_pud_en:1;
unsigned int     vfd_d_pud_sel:1;
unsigned int     vfd_clk_smt:1;
unsigned int     vfd_clk_e2:1;
unsigned int     vfd_clk_pud_en:1;
unsigned int     vfd_clk_pud_sel:1;
unsigned int     vfd_cs_n_smt:1;
unsigned int     vfd_cs_n_e2:1;
unsigned int     vfd_cs_n_pud_en:1;
unsigned int     vfd_cs_n_pud_sel:1;
unsigned int     ir_rx_smt:1;
unsigned int     ir_rx_e2:1;
unsigned int     ir_rx_pud_en:1;
unsigned int     ir_rx_pud_sel:1;
unsigned int     usb_ovrcur_flag_n_1_smt:1;
unsigned int     usb_ovrcur_flag_n_1_e2:1;
unsigned int     usb_ovrcur_flag_n_1_pud_en:1;
unsigned int     usb_ovrcur_flag_n_1_pud_sel:1;
unsigned int     usb_ovrcur_flag_n_0_smt:1;
unsigned int     usb_ovrcur_flag_n_0_e2:1;
unsigned int     usb_ovrcur_flag_n_0_pud_en:1;
unsigned int     usb_ovrcur_flag_n_0_pud_sel:1;
}ISO_PFUNC0;

typedef struct 
{
unsigned int     etn_led_rxtx_smt:1;
unsigned int     etn_led_rxtx_e2:1;
unsigned int     etn_led_rxtx_pud_en:1;
unsigned int     etn_led_rxtx_pud_sel:1;
unsigned int     etn_led_link_smt:1;
unsigned int     etn_led_link_e2:1;
unsigned int     etn_led_link_pud_en:1;
unsigned int     etn_led_link_pud_sel:1;
unsigned int     ur0_tx_smt:1;
unsigned int     ur0_tx_e2:1;
unsigned int     ur0_tx_pud_en:1;
unsigned int     ur0_tx_pud_sel:1;
unsigned int     ur0_rx_smt:1;
unsigned int     ur0_rx_e2:1;
unsigned int     ur0_rx_pud_en:1;
unsigned int     ur0_rx_pud_sel:1;
unsigned int     ur1_cts_n_smt:1;
unsigned int     ur1_cts_n_e2:1;
unsigned int     ur1_cts_n_pud_en:1;
unsigned int     ur1_cts_n_pud_sel:1;
unsigned int     ur1_rts_n_smt:1;
unsigned int     ur1_rts_n_e2:1;
unsigned int     ur1_rts_n_pud_en:1;
unsigned int     ur1_rts_n_pud_sel:1;
unsigned int     ur1_tx_smt:1;
unsigned int     ur1_tx_e2:1;
unsigned int     ur1_tx_pud_en:1;
unsigned int     ur1_tx_pud_sel:1;
unsigned int     ur1_rx_smt:1;
unsigned int     ur1_rx_e2:1;
unsigned int     ur1_rx_pud_en:1;
unsigned int     ur1_rx_pud_sel:1;
}ISO_PFUNC1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     ir_tx_smt:1;
unsigned int     ir_tx_e2:1;
unsigned int     ir_tx_pud_en:1;
unsigned int     ir_tx_pud_sel:1;
unsigned int     i2c_scl_6_smt:1;
unsigned int     i2c_scl_6_e2:1;
unsigned int     i2c_scl_6_pud_en:1;
unsigned int     i2c_scl_6_pud_sel:1;
unsigned int     i2c_sda_6_smt:1;
unsigned int     i2c_sda_6_e2:1;
unsigned int     i2c_sda_6_pud_en:1;
unsigned int     i2c_sda_6_pud_sel:1;
unsigned int     boot_sel_pud_en:1;
unsigned int     boot_sel_pud_sel:1;
unsigned int     testmode_pud_en:1;
unsigned int     testmode_pud_sel:1;
unsigned int     standby1_smt:1;
unsigned int     standby1_e2:1;
unsigned int     standby1_pud_en:1;
unsigned int     standby1_pud_sel:1;
unsigned int     standby_smt:1;
unsigned int     standby_e2:1;
unsigned int     standby_pud_en:1;
unsigned int     standby_pud_sel:1;
}ISO_PFUNC2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     boption12_en:1;
unsigned int     boption12_sel:1;
unsigned int     boption11_en:1;
unsigned int     boption11_sel:1;
unsigned int     boption10_en:1;
unsigned int     boption10_sel:1;
unsigned int     boption2_en:1;
unsigned int     boption2_sel:1;
}ISO_PFUNC3;

typedef struct 
{
unsigned int     etn_led_rxtx:2;
unsigned int     etn_led_link:2;
unsigned int     i2c_sda_0:2;
unsigned int     i2c_scl_0:2;
unsigned int     ur0_tx:2;
unsigned int     ur0_rx:2;
unsigned int     ur1_cts_n:2;
unsigned int     ur1_rts_n:2;
unsigned int     ur1_tx:2;
unsigned int     ur1_rx:2;
unsigned int     usb1:2;
unsigned int     usb0:2;
unsigned int     ir_rx:2;
unsigned int     vfd_cs_n:2;
unsigned int     vfd_clk:2;
unsigned int     vfd_d:2;
}ISO_MUXPAD0;

typedef struct 
{
unsigned int     ai_loc:2;
unsigned int     ejtag_avcpu_loc:2;
unsigned int     ur1_loc:2;
unsigned int     pwm_01_open_drain_switch:1;
unsigned int     pwm_23_open_drain_switch:1;
unsigned int     reserved_0:18;
unsigned int     ir_tx:2;
unsigned int     i2c_sda_6:2;
unsigned int     i2c_scl_6:2;
}ISO_MUXPAD1;

typedef struct 
{
unsigned int     irrbl:8;
unsigned int     irrml:8;
unsigned int     irrdzl:8;
unsigned int     irrdol:8;
}ISO_IR_PSR;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     irrdl:6;
unsigned int     irrrl:8;
unsigned int     irrsl:8;
}ISO_IR_PER;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     irfd:16;
}ISO_IR_SF;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     iriotcdp:16;
}ISO_IR_DPIR;

typedef struct 
{
unsigned int     irsr:1;
unsigned int     reserved_0:5;
unsigned int     rcmm_en:1;
unsigned int     toshiba_en:1;
unsigned int     irednm:1;
unsigned int     reserved_1:1;
unsigned int     iredn:6;
unsigned int     reserved_2:1;
unsigned int     raw_fifo_ov:1;
unsigned int     raw_fifo_val:1;
unsigned int     raw_en:1;
unsigned int     mlae:1;
unsigned int     irie:1;
unsigned int     irres:1;
unsigned int     irue:1;
unsigned int     ircm:1;
unsigned int     irbme:1;
unsigned int     irdpm:1;
unsigned int     irdn:5;
}ISO_IR_CR;

typedef struct 
{
unsigned int     irrp:32;
}ISO_IR_RP;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     slen_big:1;
unsigned int     blen_big:1;
unsigned int     raw_fifo_ov:1;
unsigned int     raw_fifo_val:1;
unsigned int     irrf:1;
unsigned int     irdvf:1;
}ISO_IR_SR;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     stop_sample:1;
unsigned int     stop_time:16;
unsigned int     reserved_1:1;
unsigned int     write_en1:1;
unsigned int     fifo_thr:6;
}ISO_IR_RAW_CTRL;

typedef struct 
{
unsigned int     dat:32;
}ISO_IR_RAW_FF;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     cnt:16;
}ISO_IR_RAW_SAMPLE_TIME;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     val:6;
}ISO_IR_RAW_WL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     len:8;
unsigned int     clk:16;
}ISO_IR_RAW_DEB;

typedef struct 
{
unsigned int     irrbl:8;
unsigned int     irrml:8;
unsigned int     irrdzl:8;
unsigned int     irrdol:8;
}ISO_IR_PSR_UP;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     irrrl:8;
unsigned int     irrsl:8;
}ISO_IR_PER_UP;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     rc6_en:1;
unsigned int     irtr:8;
}ISO_IR_CTRL_RC6;

typedef struct 
{
unsigned int     irrp:32;
}ISO_IR_RP2;

typedef struct 
{
unsigned int     irtx_en:1;
unsigned int     reserved_0:20;
unsigned int     iact_lvl:1;
unsigned int     modulation:1;
unsigned int     endian:1;
unsigned int     dummy:2;
unsigned int     fifoout_inv:1;
unsigned int     irtxout_inv:1;
unsigned int     reserved_1:3;
unsigned int     start:1;
}ISO_IRTX_CFG;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     irtx_fd:16;
}ISO_IRTX_TIM;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     pwm_clksrc_div:4;
unsigned int     pwm_clk_duty:8;
unsigned int     pwm_clk_div:8;
}ISO_IRTX_PWM_SETTING;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     data_thr:6;
unsigned int     reserved_1:5;
unsigned int     fin_en:1;
unsigned int     emp_en:1;
unsigned int     req_en:1;
}ISO_IRTX_INT_EN;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     fin_flag:1;
unsigned int     emp_flag:1;
unsigned int     req_flag:1;
}ISO_IRTX_INT_ST;

typedef struct 
{
unsigned int     fifo_rst:1;
unsigned int     reserved_0:19;
unsigned int     valid_len:4;
unsigned int     wrp:4;
unsigned int     rdp:4;
}ISO_IRTX_FIFO_ST;

typedef struct 
{
unsigned int     data:32;
}ISO_IRTX_FIFO;

typedef struct 
{
unsigned int     len_11:8;
unsigned int     len_10:8;
unsigned int     len_01:8;
unsigned int     len_00:8;
}ISO_IRRCMM_TIMING;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     dec_by_min_max:1;
}ISO_IR_CR1;

typedef struct 
{
unsigned int     rcmm_ap_max:8;
unsigned int     rcmm_ap_min:8;
unsigned int     rcmm_kb_max:8;
unsigned int     rcmm_kb_min:8;
}ISO_IRRCMM_APKB;

typedef struct 
{
unsigned int     rcmm_apoint:1;
unsigned int     rcmm_kboard:1;
unsigned int     remote_cnt_lead_high:14;
unsigned int     remote_cnt_lead_low:16;
}ISO_IRRXRCLFIFO;

typedef struct 
{
unsigned int     cec_mode:2;
unsigned int     reserved_0:1;
unsigned int     test_mode_pad_en:1;
unsigned int     logical_addr0:4;
unsigned int     timer_div:8;
unsigned int     pre_div:8;
unsigned int     unreg_ack_en:1;
unsigned int     reserved_1:1;
unsigned int     cdc_arbitration_en:1;
unsigned int     test_mode_pad_data:5;
}ISO_CEC_CR0;

typedef struct 
{
unsigned int     cec_pad_in:1;
unsigned int     dummy0:3;
unsigned int     logical_addr3:4;
unsigned int     logical_addr2:4;
unsigned int     logical_addr1:4;
unsigned int     dummy1:4;
unsigned int     clear_cec_int:1;
unsigned int     wt_cnt:6;
unsigned int     lattest:1;
unsigned int     retry_no:4;
}ISO_CEC_RTCR0;

typedef struct 
{
unsigned int     broadcast_addr:1;
unsigned int     reserved_0:11;
unsigned int     dest_addr:4;
unsigned int     rx_en:1;
unsigned int     rx_rst:1;
unsigned int     rx_continuous:1;
unsigned int     rx_int_en:1;
unsigned int     init_addr:4;
unsigned int     rx_eom:1;
unsigned int     rx_int:1;
unsigned int     rx_fifo_ov:1;
unsigned int     rx_fifo_cnt:5;
}ISO_CEC_RXCR0;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     tx_addr_en:1;
unsigned int     tx_addr:4;
unsigned int     tx_en:1;
unsigned int     tx_rst:1;
unsigned int     tx_continuous:1;
unsigned int     tx_int_en:1;
unsigned int     dest_addr:4;
unsigned int     tx_eom:1;
unsigned int     tx_int:1;
unsigned int     tx_fifo_ud:1;
unsigned int     tx_fifo_cnt:5;
}ISO_CEC_TXCR0;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     tx_add_cnt:1;
unsigned int     rx_sub_cnt:1;
unsigned int     fifo_cnt:5;
}ISO_CEC_TXDR0;

typedef struct 
{
unsigned int     tx_fifo_0:8;
unsigned int     tx_fifo_1:8;
unsigned int     tx_fifo_2:8;
unsigned int     tx_fifo_3:8;
}ISO_CEC_TXDR1;

typedef struct 
{
unsigned int     tx_fifo_4:8;
unsigned int     tx_fifo_5:8;
unsigned int     tx_fifo_6:8;
unsigned int     tx_fifo_7:8;
}ISO_CEC_TXDR2;

typedef struct 
{
unsigned int     tx_fifo_8:8;
unsigned int     tx_fifo_9:8;
unsigned int     tx_fifo_a:8;
unsigned int     tx_fifo_b:8;
}ISO_CEC_TXDR3;

typedef struct 
{
unsigned int     tx_fifo_c:8;
unsigned int     tx_fifo_d:8;
unsigned int     tx_fifo_e:8;
unsigned int     tx_fifo_f:8;
}ISO_CEC_TXDR4;

typedef struct 
{
unsigned int     rx_fifo_0:8;
unsigned int     rx_fifo_1:8;
unsigned int     rx_fifo_2:8;
unsigned int     rx_fifo_3:8;
}ISO_CEC_RXDR1;

typedef struct 
{
unsigned int     rx_fifo_4:8;
unsigned int     rx_fifo_5:8;
unsigned int     rx_fifo_6:8;
unsigned int     rx_fifo_7:8;
}ISO_CEC_RXDR2;

typedef struct 
{
unsigned int     rx_fifo_8:8;
unsigned int     rx_fifo_9:8;
unsigned int     rx_fifo_a:8;
unsigned int     rx_fifo_b:8;
}ISO_CEC_RXDR3;

typedef struct 
{
unsigned int     rx_fifo_c:8;
unsigned int     rx_fifo_d:8;
unsigned int     rx_fifo_e:8;
unsigned int     rx_fifo_f:8;
}ISO_CEC_RXDR4;

typedef struct 
{
unsigned int     rx_start_low:8;
unsigned int     rx_start_period:8;
unsigned int     rx_data_sample:8;
unsigned int     rx_data_period:8;
}ISO_CEC_RXTCR0;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     tx_start_low:8;
unsigned int     tx_start_high:8;
}ISO_CEC_TXTCR0;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     tx_data_low:8;
unsigned int     tx_data_01:8;
unsigned int     tx_data_high:8;
}ISO_CEC_TXTCR1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_01:8;
}ISO_GDI_CEC_COMPARE_OPCODE_01;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     send_opcode_01:8;
}ISO_GDI_CEC_SEND_OPCODE_01;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     operand_number_01:2;
}ISO_GDI_CEC_SEND_OPRAND_NUMBER_01;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_01:8;
}ISO_GDI_CEC_OPRAND_01;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_02:8;
}ISO_GDI_CEC_OPRAND_02;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_03:8;
}ISO_GDI_CEC_OPRAND_03;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_02:8;
}ISO_GDI_CEC_COMPARE_OPCODE_02;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     send_opcode_02:8;
}ISO_GDI_CEC_SEND_OPCODE_02;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     operand_number_02:2;
}ISO_GDI_CEC_SEND_OPRAND_NUMBER_02;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_04:8;
}ISO_GDI_CEC_OPRAND_04;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_05:8;
}ISO_GDI_CEC_OPRAND_05;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_06:8;
}ISO_GDI_CEC_OPRAND_06;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_03:8;
}ISO_GDI_CEC_COMPARE_OPCODE_03;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     send_opcode_03:8;
}ISO_GDI_CEC_SEND_OPCODE_03;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     operand_number_03:2;
}ISO_GDI_CEC_SEND_OPRAND_NUMBER_03;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_07:8;
}ISO_GDI_CEC_OPRAND_07;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_08:8;
}ISO_GDI_CEC_OPRAND_08;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_09:8;
}ISO_GDI_CEC_OPRAND_09;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_04:8;
}ISO_GDI_CEC_COMPARE_OPCODE_04;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     send_opcode_04:8;
}ISO_GDI_CEC_SEND_OPCODE_04;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     operand_number_04:2;
}ISO_GDI_CEC_SEND_OPRAND_NUMBER_04;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_10:8;
}ISO_GDI_CEC_OPRAND_10;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_11:8;
}ISO_GDI_CEC_OPRAND_11;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_12:8;
}ISO_GDI_CEC_OPRAND_12;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_05:8;
}ISO_GDI_CEC_COMPARE_OPCODE_05;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_06:8;
}ISO_GDI_CEC_COMPARE_OPCODE_06;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_07:8;
}ISO_GDI_CEC_COMPARE_OPCODE_07;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_08:8;
}ISO_GDI_CEC_COMPARE_OPCODE_08;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_09:8;
}ISO_GDI_CEC_COMPARE_OPCODE_09;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_10:8;
}ISO_GDI_CEC_COMPARE_OPCODE_10;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_11:8;
}ISO_GDI_CEC_COMPARE_OPCODE_11;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_12:8;
}ISO_GDI_CEC_COMPARE_OPCODE_12;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_13:8;
}ISO_GDI_CEC_COMPARE_OPCODE_13;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_14:8;
}ISO_GDI_CEC_COMPARE_OPCODE_14;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_15:8;
}ISO_GDI_CEC_COMPARE_OPCODE_15;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     en_compare_opcode_15:1;
unsigned int     en_compare_opcode_14:1;
unsigned int     en_compare_opcode_13:1;
unsigned int     en_compare_opcode_12:1;
unsigned int     en_compare_opcode_11:1;
unsigned int     en_compare_opcode_10:1;
unsigned int     en_compare_opcode_09:1;
unsigned int     en_compare_opcode_08:1;
unsigned int     en_compare_opcode_07:1;
unsigned int     en_compare_opcode_06:1;
unsigned int     en_compare_opcode_05:1;
unsigned int     en_compare_opcode_04:1;
unsigned int     en_compare_opcode_03:1;
unsigned int     en_compare_opcode_02:1;
unsigned int     en_compare_opcode_01:1;
}ISO_GDI_CEC_OPCODE_ENABLE;

typedef struct 
{
unsigned int     irq_pending:1;
unsigned int     reserved_0:5;
unsigned int     cec_msg_status_01:1;
unsigned int     cec_msg_status_02:1;
unsigned int     reserved_1:15;
unsigned int     irq_by_cec_receive_special_cmd:1;
unsigned int     reserved_2:8;
}ISO_GDI_POWER_SAVING_MODE;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     reg_cec_rpu_en:1;
unsigned int     reg_cec_rsel:3;
}ISO_CEC_ANALOG;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     set:1;
}ISO_DRM_ST;

typedef struct 
{
unsigned int     val:32;
}ISO_DRM_SECURE_CLK;

typedef struct 
{
unsigned int     val:32;
}ISO_DRM_ELAPSED;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST1;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST2;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     clk_div_en:1;
unsigned int     clk_sel:1;
}ISO_DRM_CTRL;

typedef struct 
{
unsigned int     init:32;
}ISO_DRM_CLK_DIV;

typedef struct 
{
unsigned int     tc3tvr:32;
}ISO_TC3TVR;

typedef struct 
{
unsigned int     tc3cvr:32;
}ISO_TC3CVR;

typedef struct 
{
unsigned int     tc3en:1;
unsigned int     tc3mode:1;
unsigned int     tc3pause:1;
unsigned int     rvda:5;
unsigned int     reserved_0:24;
}ISO_TC3CR;

typedef struct 
{
unsigned int     tc3ie:1;
unsigned int     reserved_0:31;
}ISO_TC3ICR;

typedef struct 
{
unsigned int     tc4tvr:32;
}ISO_TC4TVR;

typedef struct 
{
unsigned int     tc4cvr:32;
}ISO_TC4CVR;

typedef struct 
{
unsigned int     tc4en:1;
unsigned int     tc4mode:1;
unsigned int     tc4pause:1;
unsigned int     rvda:5;
unsigned int     reserved_0:24;
}ISO_TC4CR;

typedef struct 
{
unsigned int     tc4ie:1;
unsigned int     reserved_0:31;
}ISO_TC4ICR;

typedef struct 
{
unsigned int     dat:32;
}ISO_NORST;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST3;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST4;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST5;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST6;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST7;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST8;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST9;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST10;

typedef struct 
{
unsigned int     wd_int_en:1;
unsigned int     reserved_0:15;
unsigned int     nmic:4;
unsigned int     wdc:4;
unsigned int     wden:8;
}ISO_TCWCR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     wdclr:1;
}ISO_TCWTR;

typedef struct 
{
unsigned int     sel:32;
}ISO_TCWNMI;

typedef struct 
{
unsigned int     sel:32;
}ISO_TCWOV;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     set:1;
}ISO_DRM_ST_SWC;

typedef struct 
{
unsigned int     val:32;
}ISO_DRM_SECURE_CLK_SWC;

typedef struct 
{
unsigned int     val:32;
}ISO_DRM_ELAPSED_SWC;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     clk_div_en:1;
unsigned int     clk_sel:1;
}ISO_DRM_CTRL_SWC;

typedef struct 
{
unsigned int     init:32;
}ISO_DRM_CLK_DIV_SWC;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST_SWC;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST1_SWC;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST2_SWC;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST3_SWC;

typedef struct 
{
unsigned int     dat:32;
}ISO_NORST_SWC;

typedef struct 
{
unsigned int     dat:32;
}ISO_NORST1_SWC;

typedef struct 
{
unsigned int     dat:32;
}ISO_NORST2_SWC;

typedef struct 
{
unsigned int     sel:32;
}ISO_TCWOV_RSTB_CNT;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     scpu_boot_info_valid:1;
}ISO_CPU_ST2V;

typedef struct 
{
unsigned int     scpu_boot_info:32;
}ISO_CPU_ST2;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     write_enable3:1;
unsigned int     sel1:5;
unsigned int     write_enable2:1;
unsigned int     sel0:5;
unsigned int     write_enable1:1;
unsigned int     enable:1;
}ISO_ACPU_DBG;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     analogy_mode_in:1;
}ISO_ANLG;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dll:8;
}ISO_U0RBR_THR_DLL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dlh:8;
}ISO_U0IER_DLH;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     fifo16:2;
unsigned int     reserved_1:2;
unsigned int     iid:4;
}ISO_U0IIR_FCR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dlab:1;
unsigned int     brk:1;
unsigned int     reserved_1:1;
unsigned int     eps:1;
unsigned int     pen:1;
unsigned int     stb:1;
unsigned int     wls:2;
}ISO_U0LCR;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     afce:1;
unsigned int     loop:1;
unsigned int     reserved_1:2;
unsigned int     rts:1;
unsigned int     dtr:1;
}ISO_U0MCR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rfe:1;
unsigned int     temt:1;
unsigned int     thre:1;
unsigned int     bi:1;
unsigned int     fe:1;
unsigned int     pe:1;
unsigned int     oe:1;
unsigned int     dr:1;
}ISO_U0LSR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dcd:1;
unsigned int     ri:1;
unsigned int     dsr:1;
unsigned int     cts:1;
unsigned int     ddcd:1;
unsigned int     teri:1;
unsigned int     ddsr:1;
unsigned int     dcts:1;
}ISO_U0MSR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     scr:8;
}ISO_U0SCR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rbd:8;
}ISO_U0SRBR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     far:1;
}ISO_U0FAR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     far:8;
}ISO_U0TFR;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     rffe:1;
unsigned int     rfpf:1;
unsigned int     rfwd:8;
}ISO_U0RFW;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     rff:1;
unsigned int     rfne:1;
unsigned int     tfe:1;
unsigned int     tfnf:1;
unsigned int     busy:1;
}ISO_U0USR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tfl:8;
}ISO_U0TFL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rfl:8;
}ISO_U0RFL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     xfr:1;
unsigned int     rfr:1;
unsigned int     ur:1;
}ISO_U0SRR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sbcr:1;
}ISO_U0SBCR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sdmam:1;
}ISO_U0SDMAM;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sfe:1;
}ISO_U0SFE;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     srt:2;
}ISO_U0SRT;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     stet:2;
}ISO_U0STET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     htx:1;
}ISO_U0HTX;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     dmasa:1;
}ISO_U0DMASA;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     fifo_mode:8;
unsigned int     reserved_1:2;
unsigned int     dma_extra:1;
unsigned int     uart_add_encoded_params:1;
unsigned int     shadow:1;
unsigned int     fifo_stat:1;
unsigned int     fifo_access:1;
unsigned int     additional_feat:1;
unsigned int     sir_lp_mode:1;
unsigned int     sir_mode:1;
unsigned int     thre_mode:1;
unsigned int     afce_mode:1;
unsigned int     reserved_2:2;
unsigned int     apb_data_width:2;
}ISO_U0CPR;

typedef struct 
{
unsigned int     ucv:32;
}ISO_U0UCV;

typedef struct 
{
unsigned int     ctr:32;
}ISO_U0CTR;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     ic_slave_disable:1;
unsigned int     ic_restart_en:1;
unsigned int     ic_10bitaddr_master:1;
unsigned int     ic_10bitaddr_slave:1;
unsigned int     speed:2;
unsigned int     master_mode:1;
}ISO_IC0_CON;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     ic_10bitaddr_master:1;
unsigned int     special:1;
unsigned int     gc_or_start:1;
unsigned int     ic_tar:10;
}ISO_IC0_TAR;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     ic_sar:10;
}ISO_IC0_SAR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     ic_hs_mar:3;
}ISO_IC0_HS_MADDR;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     restart:1;
unsigned int     stop:1;
unsigned int     cmd:1;
unsigned int     dat:8;
}ISO_IC0_DATA_CMD;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_ss_scl_hcnt:16;
}ISO_IC0_SS_SCL_HCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_ss_scl_lcnt:16;
}ISO_IC0_SS_SCL_LCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_fs_scl_hcnt:16;
}ISO_IC0_FS_SCL_HCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_fs_scl_lcnt:16;
}ISO_IC0_FS_SCL_LCNT;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     r_gen_call:1;
unsigned int     r_start_det:1;
unsigned int     r_stop_det:1;
unsigned int     r_activity:1;
unsigned int     r_rx_done:1;
unsigned int     r_tx_abrt:1;
unsigned int     r_rd_req:1;
unsigned int     r_tx_empty:1;
unsigned int     r_tx_over:1;
unsigned int     r_rx_full:1;
unsigned int     r_rx_over:1;
unsigned int     r_rx_under:1;
}ISO_IC0_INTR_STAT;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     m_gen_call:1;
unsigned int     m_start_det:1;
unsigned int     m_stop_det:1;
unsigned int     m_activity:1;
unsigned int     m_rx_done:1;
unsigned int     m_tx_abrt:1;
unsigned int     m_rd_req:1;
unsigned int     m_tx_empty:1;
unsigned int     m_tx_over:1;
unsigned int     m_rx_full:1;
unsigned int     m_rx_over:1;
unsigned int     m_rx_under:1;
}ISO_IC0_INTR_MASK;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     gen_call:1;
unsigned int     start_det:1;
unsigned int     stop_det:1;
unsigned int     activity:1;
unsigned int     rx_done:1;
unsigned int     tx_abrt:1;
unsigned int     rd_req:1;
unsigned int     tx_empty:1;
unsigned int     tx_over:1;
unsigned int     rx_full:1;
unsigned int     rx_over:1;
unsigned int     rx_under:1;
}ISO_IC0_RAW_INTR_STAT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rx_tl:8;
}ISO_IC0_RX_TL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tx_tl:8;
}ISO_IC0_TX_TL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_intr:1;
}ISO_IC0_CLR_INTR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_under:1;
}ISO_IC0_CLR_RX_UNDER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_over:1;
}ISO_IC0_CLR_RX_OVER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_tx_over:1;
}ISO_IC0_CLR_TX_OVER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rd_req:1;
}ISO_IC0_CLR_RD_REQ;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_tx_abrt:1;
}ISO_IC0_CLR_TX_ABRT;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_done:1;
}ISO_IC0_CLR_RX_DONE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_activity:1;
}ISO_IC0_CLR_ACTIVITY;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_stop_det:1;
}ISO_IC0_CLR_STOP_DET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_start_det:1;
}ISO_IC0_CLR_START_DET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_gen_call:1;
}ISO_IC0_CLR_GEN_CALL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     enable:1;
}ISO_IC0_ENABLE;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     slv_activity:1;
unsigned int     mst_activity:1;
unsigned int     rff:1;
unsigned int     rfne:1;
unsigned int     tfe:1;
unsigned int     tfnf:1;
unsigned int     activity:1;
}ISO_IC0_STATUS;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     txflr:4;
}ISO_IC0_TXFLR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     rxflr:4;
}ISO_IC0_RXFLR;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_sda_hold:16;
}ISO_IC0_SDA_HOLD;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     abrt_slvrd_intx:1;
unsigned int     abrt_slv_arblost:1;
unsigned int     abrt_slvflush_txfifo:1;
unsigned int     arb_lost:1;
unsigned int     arb_master_dis:1;
unsigned int     abrt_10b_rd_norstrt:1;
unsigned int     abrt_sbyte_norstrt:1;
unsigned int     abrt_hs_norstrt:1;
unsigned int     abrt_sbyte_ackdet:1;
unsigned int     abrt_hs_ackdet:1;
unsigned int     abrt_gcall_read:1;
unsigned int     abrt_gcall_noack:1;
unsigned int     abrt_txdata_noack:1;
unsigned int     abrt_10addr2_noack:1;
unsigned int     abrt_10addr1_noack:1;
unsigned int     abrt_7b_addr_noack:1;
}ISO_IC0_TX_ABRT_SOURCE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     nack:1;
}ISO_IC0_SLV_DATA_NACK_ONLY;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     tdmae:1;
unsigned int     rdmae:1;
}ISO_IC0_DMA_CR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     dmatdl:3;
}ISO_IC0_DMA_TDLR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     dmardl:4;
}ISO_IC0_DMA_RDLR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sda_setup:8;
}ISO_IC0_SDA_SETUP;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     ack_gen_call:1;
}ISO_IC0_ACK_GENERAL_CALL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     slv_rx_data_lost:1;
unsigned int     slv_disabled_whi:1;
unsigned int     ic_en:1;
}ISO_IC0_ENABLE_STATUS;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     tx_buffer_depth:8;
unsigned int     rx_buffer_depth:8;
unsigned int     add_encoded_params:1;
unsigned int     has_dma:1;
unsigned int     intr_io:1;
unsigned int     hc_count_values:1;
unsigned int     max_speed_mode:2;
unsigned int     apb_data_width:2;
}ISO_IC0_COMP_PARAM_1;

typedef struct 
{
unsigned int     ic_comp_version:32;
}ISO_IC0_COMP_VERSION;

typedef struct 
{
unsigned int     ic_comp_type:32;
}ISO_IC0_COMP_TYPE;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     ic_slave_disable:1;
unsigned int     ic_restart_en:1;
unsigned int     ic_10bitaddr_master:1;
unsigned int     ic_10bitaddr_slave:1;
unsigned int     speed:2;
unsigned int     master_mode:1;
}ISO_IC6_CON;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     ic_10bitaddr_master:1;
unsigned int     special:1;
unsigned int     gc_or_start:1;
unsigned int     ic_tar:10;
}ISO_IC6_TAR;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     ic_sar:10;
}ISO_IC6_SAR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     ic_hs_mar:3;
}ISO_IC6_HS_MADDR;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     restart:1;
unsigned int     stop:1;
unsigned int     cmd:1;
unsigned int     dat:8;
}ISO_IC6_DATA_CMD;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_ss_scl_hcnt:16;
}ISO_IC6_SS_SCL_HCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_ss_scl_lcnt:16;
}ISO_IC6_SS_SCL_LCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_fs_scl_hcnt:16;
}ISO_IC6_FS_SCL_HCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_fs_scl_lcnt:16;
}ISO_IC6_FS_SCL_LCNT;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     r_gen_call:1;
unsigned int     r_start_det:1;
unsigned int     r_stop_det:1;
unsigned int     r_activity:1;
unsigned int     r_rx_done:1;
unsigned int     r_tx_abrt:1;
unsigned int     r_rd_req:1;
unsigned int     r_tx_empty:1;
unsigned int     r_tx_over:1;
unsigned int     r_rx_full:1;
unsigned int     r_rx_over:1;
unsigned int     r_rx_under:1;
}ISO_IC6_INTR_STAT;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     m_gen_call:1;
unsigned int     m_start_det:1;
unsigned int     m_stop_det:1;
unsigned int     m_activity:1;
unsigned int     m_rx_done:1;
unsigned int     m_tx_abrt:1;
unsigned int     m_rd_req:1;
unsigned int     m_tx_empty:1;
unsigned int     m_tx_over:1;
unsigned int     m_rx_full:1;
unsigned int     m_rx_over:1;
unsigned int     m_rx_under:1;
}ISO_IC6_INTR_MASK;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     gen_call:1;
unsigned int     start_det:1;
unsigned int     stop_det:1;
unsigned int     activity:1;
unsigned int     rx_done:1;
unsigned int     tx_abrt:1;
unsigned int     rd_req:1;
unsigned int     tx_empty:1;
unsigned int     tx_over:1;
unsigned int     rx_full:1;
unsigned int     rx_over:1;
unsigned int     rx_under:1;
}ISO_IC6_RAW_INTR_STAT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rx_tl:8;
}ISO_IC6_RX_TL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tx_tl:8;
}ISO_IC6_TX_TL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_intr:1;
}ISO_IC6_CLR_INTR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_under:1;
}ISO_IC6_CLR_RX_UNDER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_over:1;
}ISO_IC6_CLR_RX_OVER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_tx_over:1;
}ISO_IC6_CLR_TX_OVER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rd_req:1;
}ISO_IC6_CLR_RD_REQ;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_tx_abrt:1;
}ISO_IC6_CLR_TX_ABRT;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_done:1;
}ISO_IC6_CLR_RX_DONE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_activity:1;
}ISO_IC6_CLR_ACTIVITY;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_stop_det:1;
}ISO_IC6_CLR_STOP_DET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_start_det:1;
}ISO_IC6_CLR_START_DET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_gen_call:1;
}ISO_IC6_CLR_GEN_CALL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     enable:1;
}ISO_IC6_ENABLE;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     slv_activity:1;
unsigned int     mst_activity:1;
unsigned int     rff:1;
unsigned int     rfne:1;
unsigned int     tfe:1;
unsigned int     tfnf:1;
unsigned int     activity:1;
}ISO_IC6_STATUS;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     txflr:4;
}ISO_IC6_TXFLR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     rxflr:4;
}ISO_IC6_RXFLR;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_sda_hold:16;
}ISO_IC6_SDA_HOLD;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     abrt_slvrd_intx:1;
unsigned int     abrt_slv_arblost:1;
unsigned int     abrt_slvflush_txfifo:1;
unsigned int     arb_lost:1;
unsigned int     arb_master_dis:1;
unsigned int     abrt_10b_rd_norstrt:1;
unsigned int     abrt_sbyte_norstrt:1;
unsigned int     abrt_hs_norstrt:1;
unsigned int     abrt_sbyte_ackdet:1;
unsigned int     abrt_hs_ackdet:1;
unsigned int     abrt_gcall_read:1;
unsigned int     abrt_gcall_noack:1;
unsigned int     abrt_txdata_noack:1;
unsigned int     abrt_10addr2_noack:1;
unsigned int     abrt_10addr1_noack:1;
unsigned int     abrt_7b_addr_noack:1;
}ISO_IC6_TX_ABRT_SOURCE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     nack:1;
}ISO_IC6_SLV_DATA_NACK_ONLY;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     tdmae:1;
unsigned int     rdmae:1;
}ISO_IC6_DMA_CR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     dmatdl:3;
}ISO_IC6_DMA_TDLR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     dmardl:4;
}ISO_IC6_DMA_RDLR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sda_setup:8;
}ISO_IC6_SDA_SETUP;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     ack_gen_call:1;
}ISO_IC6_ACK_GENERAL_CALL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     slv_rx_data_lost:1;
unsigned int     slv_disabled_whi:1;
unsigned int     ic_en:1;
}ISO_IC6_ENABLE_STATUS;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     tx_buffer_depth:8;
unsigned int     rx_buffer_depth:8;
unsigned int     add_encoded_params:1;
unsigned int     has_dma:1;
unsigned int     intr_io:1;
unsigned int     hc_count_values:1;
unsigned int     max_speed_mode:2;
unsigned int     apb_data_width:2;
}ISO_IC6_COMP_PARAM_1;

typedef struct 
{
unsigned int     ic_comp_version:32;
}ISO_IC6_COMP_VERSION;

typedef struct 
{
unsigned int     ic_comp_type:32;
}ISO_IC6_COMP_TYPE;

typedef struct 
{
unsigned int     3:8;
unsigned int     2:8;
unsigned int     1:8;
unsigned int     0:8;
}ISO_PWM_OCD;

typedef struct 
{
unsigned int     3:8;
unsigned int     2:8;
unsigned int     1:8;
unsigned int     0:8;
}ISO_PWM_CD;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     3:4;
unsigned int     2:4;
unsigned int     1:4;
unsigned int     0:4;
}ISO_PWM_CSD;

#endif

#define ISO_ISR                                                                      0x18007000
#define ISO_ISR_reg_addr                                                             "0xB8007000"
#define ISO_ISR_reg                                                                  0xB8007000
#define set_ISO_ISR_reg(data)   (*((volatile unsigned int*) ISO_ISR_reg)=data)
#define get_ISO_ISR_reg   (*((volatile unsigned int*) ISO_ISR_reg))
#define ISO_ISR_inst_adr                                                             "0x0000"
#define ISO_ISR_inst                                                                 0x0000
#define ISO_ISR_cec_int_shift                                                        (22)
#define ISO_ISR_cec_int_mask                                                         (0x00400000)
#define ISO_ISR_cec_int(data)                                                        (0x00400000&((data)<<22))
#define ISO_ISR_cec_int_src(data)                                                    ((0x00400000&(data))>>22)
#define ISO_ISR_get_cec_int(data)                                                    ((0x00400000&(data))>>22)
#define ISO_ISR_gpioda_int_shift                                                     (20)
#define ISO_ISR_gpioda_int_mask                                                      (0x00100000)
#define ISO_ISR_gpioda_int(data)                                                     (0x00100000&((data)<<20))
#define ISO_ISR_gpioda_int_src(data)                                                 ((0x00100000&(data))>>20)
#define ISO_ISR_get_gpioda_int(data)                                                 ((0x00100000&(data))>>20)
#define ISO_ISR_gpioa_int_shift                                                      (19)
#define ISO_ISR_gpioa_int_mask                                                       (0x00080000)
#define ISO_ISR_gpioa_int(data)                                                      (0x00080000&((data)<<19))
#define ISO_ISR_gpioa_int_src(data)                                                  ((0x00080000&(data))>>19)
#define ISO_ISR_get_gpioa_int(data)                                                  ((0x00080000&(data))>>19)
#define ISO_ISR_vfd_ardswda_int_shift                                                (18)
#define ISO_ISR_vfd_ardswda_int_mask                                                 (0x00040000)
#define ISO_ISR_vfd_ardswda_int(data)                                                (0x00040000&((data)<<18))
#define ISO_ISR_vfd_ardswda_int_src(data)                                            ((0x00040000&(data))>>18)
#define ISO_ISR_get_vfd_ardswda_int(data)                                            ((0x00040000&(data))>>18)
#define ISO_ISR_vfd_ardswa_int_shift                                                 (17)
#define ISO_ISR_vfd_ardswa_int_mask                                                  (0x00020000)
#define ISO_ISR_vfd_ardswa_int(data)                                                 (0x00020000&((data)<<17))
#define ISO_ISR_vfd_ardswa_int_src(data)                                             ((0x00020000&(data))>>17)
#define ISO_ISR_get_vfd_ardswa_int(data)                                             ((0x00020000&(data))>>17)
#define ISO_ISR_vfd_ardkpadda_int_shift                                              (16)
#define ISO_ISR_vfd_ardkpadda_int_mask                                               (0x00010000)
#define ISO_ISR_vfd_ardkpadda_int(data)                                              (0x00010000&((data)<<16))
#define ISO_ISR_vfd_ardkpadda_int_src(data)                                          ((0x00010000&(data))>>16)
#define ISO_ISR_get_vfd_ardkpadda_int(data)                                          ((0x00010000&(data))>>16)
#define ISO_ISR_vfd_ardkpada_int_shift                                               (15)
#define ISO_ISR_vfd_ardkpada_int_mask                                                (0x00008000)
#define ISO_ISR_vfd_ardkpada_int(data)                                               (0x00008000&((data)<<15))
#define ISO_ISR_vfd_ardkpada_int_src(data)                                           ((0x00008000&(data))>>15)
#define ISO_ISR_get_vfd_ardkpada_int(data)                                           ((0x00008000&(data))>>15)
#define ISO_ISR_vfd_wdone_int_shift                                                  (14)
#define ISO_ISR_vfd_wdone_int_mask                                                   (0x00004000)
#define ISO_ISR_vfd_wdone_int(data)                                                  (0x00004000&((data)<<14))
#define ISO_ISR_vfd_wdone_int_src(data)                                              ((0x00004000&(data))>>14)
#define ISO_ISR_get_vfd_wdone_int(data)                                              ((0x00004000&(data))>>14)
#define ISO_ISR_rtc_alarm_int_shift                                                  (13)
#define ISO_ISR_rtc_alarm_int_mask                                                   (0x00002000)
#define ISO_ISR_rtc_alarm_int(data)                                                  (0x00002000&((data)<<13))
#define ISO_ISR_rtc_alarm_int_src(data)                                              ((0x00002000&(data))>>13)
#define ISO_ISR_get_rtc_alarm_int(data)                                              ((0x00002000&(data))>>13)
#define ISO_ISR_rtc_hsec_int_shift                                                   (12)
#define ISO_ISR_rtc_hsec_int_mask                                                    (0x00001000)
#define ISO_ISR_rtc_hsec_int(data)                                                   (0x00001000&((data)<<12))
#define ISO_ISR_rtc_hsec_int_src(data)                                               ((0x00001000&(data))>>12)
#define ISO_ISR_get_rtc_hsec_int(data)                                               ((0x00001000&(data))>>12)
#define ISO_ISR_i2c6_int_shift                                                       (10)
#define ISO_ISR_i2c6_int_mask                                                        (0x00000400)
#define ISO_ISR_i2c6_int(data)                                                       (0x00000400&((data)<<10))
#define ISO_ISR_i2c6_int_src(data)                                                   ((0x00000400&(data))>>10)
#define ISO_ISR_get_i2c6_int(data)                                                   ((0x00000400&(data))>>10)
#define ISO_ISR_tc4_int_shift                                                        (9)
#define ISO_ISR_tc4_int_mask                                                         (0x00000200)
#define ISO_ISR_tc4_int(data)                                                        (0x00000200&((data)<<9))
#define ISO_ISR_tc4_int_src(data)                                                    ((0x00000200&(data))>>9)
#define ISO_ISR_get_tc4_int(data)                                                    ((0x00000200&(data))>>9)
#define ISO_ISR_i2c0_int_shift                                                       (8)
#define ISO_ISR_i2c0_int_mask                                                        (0x00000100)
#define ISO_ISR_i2c0_int(data)                                                       (0x00000100&((data)<<8))
#define ISO_ISR_i2c0_int_src(data)                                                   ((0x00000100&(data))>>8)
#define ISO_ISR_get_i2c0_int(data)                                                   ((0x00000100&(data))>>8)
#define ISO_ISR_wdog_nmi_int_shift                                                   (7)
#define ISO_ISR_wdog_nmi_int_mask                                                    (0x00000080)
#define ISO_ISR_wdog_nmi_int(data)                                                   (0x00000080&((data)<<7))
#define ISO_ISR_wdog_nmi_int_src(data)                                               ((0x00000080&(data))>>7)
#define ISO_ISR_get_wdog_nmi_int(data)                                               ((0x00000080&(data))>>7)
#define ISO_ISR_irda_int_shift                                                       (5)
#define ISO_ISR_irda_int_mask                                                        (0x00000020)
#define ISO_ISR_irda_int(data)                                                       (0x00000020&((data)<<5))
#define ISO_ISR_irda_int_src(data)                                                   ((0x00000020&(data))>>5)
#define ISO_ISR_get_irda_int(data)                                                   ((0x00000020&(data))>>5)
#define ISO_ISR_ur0_int_shift                                                        (2)
#define ISO_ISR_ur0_int_mask                                                         (0x00000004)
#define ISO_ISR_ur0_int(data)                                                        (0x00000004&((data)<<2))
#define ISO_ISR_ur0_int_src(data)                                                    ((0x00000004&(data))>>2)
#define ISO_ISR_get_ur0_int(data)                                                    ((0x00000004&(data))>>2)
#define ISO_ISR_tc3_int_shift                                                        (1)
#define ISO_ISR_tc3_int_mask                                                         (0x00000002)
#define ISO_ISR_tc3_int(data)                                                        (0x00000002&((data)<<1))
#define ISO_ISR_tc3_int_src(data)                                                    ((0x00000002&(data))>>1)
#define ISO_ISR_get_tc3_int(data)                                                    ((0x00000002&(data))>>1)
#define ISO_ISR_write_data_shift                                                     (0)
#define ISO_ISR_write_data_mask                                                      (0x00000001)
#define ISO_ISR_write_data(data)                                                     (0x00000001&((data)<<0))
#define ISO_ISR_write_data_src(data)                                                 ((0x00000001&(data))>>0)
#define ISO_ISR_get_write_data(data)                                                 ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR                                                                 0x18007004
#define ISO_UMSK_ISR_reg_addr                                                        "0xB8007004"
#define ISO_UMSK_ISR_reg                                                             0xB8007004
#define set_ISO_UMSK_ISR_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_reg)=data)
#define get_ISO_UMSK_ISR_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_reg))
#define ISO_UMSK_ISR_inst_adr                                                        "0x0001"
#define ISO_UMSK_ISR_inst                                                            0x0001
#define ISO_UMSK_ISR_gpioda_int_shift                                                (20)
#define ISO_UMSK_ISR_gpioda_int_mask                                                 (0x00100000)
#define ISO_UMSK_ISR_gpioda_int(data)                                                (0x00100000&((data)<<20))
#define ISO_UMSK_ISR_gpioda_int_src(data)                                            ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_get_gpioda_int(data)                                            ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_gpioa_int_shift                                                 (19)
#define ISO_UMSK_ISR_gpioa_int_mask                                                  (0x00080000)
#define ISO_UMSK_ISR_gpioa_int(data)                                                 (0x00080000&((data)<<19))
#define ISO_UMSK_ISR_gpioa_int_src(data)                                             ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_get_gpioa_int(data)                                             ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_vfd_ardswda_int_shift                                           (18)
#define ISO_UMSK_ISR_vfd_ardswda_int_mask                                            (0x00040000)
#define ISO_UMSK_ISR_vfd_ardswda_int(data)                                           (0x00040000&((data)<<18))
#define ISO_UMSK_ISR_vfd_ardswda_int_src(data)                                       ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_get_vfd_ardswda_int(data)                                       ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_vfd_ardswa_int_shift                                            (17)
#define ISO_UMSK_ISR_vfd_ardswa_int_mask                                             (0x00020000)
#define ISO_UMSK_ISR_vfd_ardswa_int(data)                                            (0x00020000&((data)<<17))
#define ISO_UMSK_ISR_vfd_ardswa_int_src(data)                                        ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_get_vfd_ardswa_int(data)                                        ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_vfd_ardkpadda_int_shift                                         (16)
#define ISO_UMSK_ISR_vfd_ardkpadda_int_mask                                          (0x00010000)
#define ISO_UMSK_ISR_vfd_ardkpadda_int(data)                                         (0x00010000&((data)<<16))
#define ISO_UMSK_ISR_vfd_ardkpadda_int_src(data)                                     ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_get_vfd_ardkpadda_int(data)                                     ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_vfd_ardkpada_int_shift                                          (15)
#define ISO_UMSK_ISR_vfd_ardkpada_int_mask                                           (0x00008000)
#define ISO_UMSK_ISR_vfd_ardkpada_int(data)                                          (0x00008000&((data)<<15))
#define ISO_UMSK_ISR_vfd_ardkpada_int_src(data)                                      ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_get_vfd_ardkpada_int(data)                                      ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_vfd_wdone_int_shift                                             (14)
#define ISO_UMSK_ISR_vfd_wdone_int_mask                                              (0x00004000)
#define ISO_UMSK_ISR_vfd_wdone_int(data)                                             (0x00004000&((data)<<14))
#define ISO_UMSK_ISR_vfd_wdone_int_src(data)                                         ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_get_vfd_wdone_int(data)                                         ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_rtc_alarm_int_shift                                             (13)
#define ISO_UMSK_ISR_rtc_alarm_int_mask                                              (0x00002000)
#define ISO_UMSK_ISR_rtc_alarm_int(data)                                             (0x00002000&((data)<<13))
#define ISO_UMSK_ISR_rtc_alarm_int_src(data)                                         ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_get_rtc_alarm_int(data)                                         ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_rtc_hsec_int_shift                                              (12)
#define ISO_UMSK_ISR_rtc_hsec_int_mask                                               (0x00001000)
#define ISO_UMSK_ISR_rtc_hsec_int(data)                                              (0x00001000&((data)<<12))
#define ISO_UMSK_ISR_rtc_hsec_int_src(data)                                          ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_get_rtc_hsec_int(data)                                          ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_tc4_int_shift                                                   (9)
#define ISO_UMSK_ISR_tc4_int_mask                                                    (0x00000200)
#define ISO_UMSK_ISR_tc4_int(data)                                                   (0x00000200&((data)<<9))
#define ISO_UMSK_ISR_tc4_int_src(data)                                               ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_get_tc4_int(data)                                               ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_wdog_nmi_int_shift                                              (7)
#define ISO_UMSK_ISR_wdog_nmi_int_mask                                               (0x00000080)
#define ISO_UMSK_ISR_wdog_nmi_int(data)                                              (0x00000080&((data)<<7))
#define ISO_UMSK_ISR_wdog_nmi_int_src(data)                                          ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_get_wdog_nmi_int(data)                                          ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_irda_int_shift                                                  (5)
#define ISO_UMSK_ISR_irda_int_mask                                                   (0x00000020)
#define ISO_UMSK_ISR_irda_int(data)                                                  (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_irda_int_src(data)                                              ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_get_irda_int(data)                                              ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_tc3_int_shift                                                   (1)
#define ISO_UMSK_ISR_tc3_int_mask                                                    (0x00000002)
#define ISO_UMSK_ISR_tc3_int(data)                                                   (0x00000002&((data)<<1))
#define ISO_UMSK_ISR_tc3_int_src(data)                                               ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_get_tc3_int(data)                                               ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_write_data_shift                                                (0)
#define ISO_UMSK_ISR_write_data_mask                                                 (0x00000001)
#define ISO_UMSK_ISR_write_data(data)                                                (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_write_data_src(data)                                            ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_get_write_data(data)                                            ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR_GPA                                                             0x18007008
#define ISO_UMSK_ISR_GPA_reg_addr                                                    "0xB8007008"
#define ISO_UMSK_ISR_GPA_reg                                                         0xB8007008
#define set_ISO_UMSK_ISR_GPA_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_GPA_reg)=data)
#define get_ISO_UMSK_ISR_GPA_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_GPA_reg))
#define ISO_UMSK_ISR_GPA_inst_adr                                                    "0x0002"
#define ISO_UMSK_ISR_GPA_inst                                                        0x0002
#define ISO_UMSK_ISR_GPA_int20_a_shift                                               (21)
#define ISO_UMSK_ISR_GPA_int20_a_mask                                                (0x00200000)
#define ISO_UMSK_ISR_GPA_int20_a(data)                                               (0x00200000&((data)<<21))
#define ISO_UMSK_ISR_GPA_int20_a_src(data)                                           ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_GPA_get_int20_a(data)                                           ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_GPA_int19_a_shift                                               (20)
#define ISO_UMSK_ISR_GPA_int19_a_mask                                                (0x00100000)
#define ISO_UMSK_ISR_GPA_int19_a(data)                                               (0x00100000&((data)<<20))
#define ISO_UMSK_ISR_GPA_int19_a_src(data)                                           ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_GPA_get_int19_a(data)                                           ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_GPA_int18_a_shift                                               (19)
#define ISO_UMSK_ISR_GPA_int18_a_mask                                                (0x00080000)
#define ISO_UMSK_ISR_GPA_int18_a(data)                                               (0x00080000&((data)<<19))
#define ISO_UMSK_ISR_GPA_int18_a_src(data)                                           ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_GPA_get_int18_a(data)                                           ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_GPA_int17_a_shift                                               (18)
#define ISO_UMSK_ISR_GPA_int17_a_mask                                                (0x00040000)
#define ISO_UMSK_ISR_GPA_int17_a(data)                                               (0x00040000&((data)<<18))
#define ISO_UMSK_ISR_GPA_int17_a_src(data)                                           ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_GPA_get_int17_a(data)                                           ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_GPA_int16_a_shift                                               (17)
#define ISO_UMSK_ISR_GPA_int16_a_mask                                                (0x00020000)
#define ISO_UMSK_ISR_GPA_int16_a(data)                                               (0x00020000&((data)<<17))
#define ISO_UMSK_ISR_GPA_int16_a_src(data)                                           ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_GPA_get_int16_a(data)                                           ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_GPA_int15_a_shift                                               (16)
#define ISO_UMSK_ISR_GPA_int15_a_mask                                                (0x00010000)
#define ISO_UMSK_ISR_GPA_int15_a(data)                                               (0x00010000&((data)<<16))
#define ISO_UMSK_ISR_GPA_int15_a_src(data)                                           ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_GPA_get_int15_a(data)                                           ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_GPA_int14_a_shift                                               (15)
#define ISO_UMSK_ISR_GPA_int14_a_mask                                                (0x00008000)
#define ISO_UMSK_ISR_GPA_int14_a(data)                                               (0x00008000&((data)<<15))
#define ISO_UMSK_ISR_GPA_int14_a_src(data)                                           ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_GPA_get_int14_a(data)                                           ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_GPA_int13_a_shift                                               (14)
#define ISO_UMSK_ISR_GPA_int13_a_mask                                                (0x00004000)
#define ISO_UMSK_ISR_GPA_int13_a(data)                                               (0x00004000&((data)<<14))
#define ISO_UMSK_ISR_GPA_int13_a_src(data)                                           ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_GPA_get_int13_a(data)                                           ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_GPA_int12_a_shift                                               (13)
#define ISO_UMSK_ISR_GPA_int12_a_mask                                                (0x00002000)
#define ISO_UMSK_ISR_GPA_int12_a(data)                                               (0x00002000&((data)<<13))
#define ISO_UMSK_ISR_GPA_int12_a_src(data)                                           ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_GPA_get_int12_a(data)                                           ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_GPA_int11_a_shift                                               (12)
#define ISO_UMSK_ISR_GPA_int11_a_mask                                                (0x00001000)
#define ISO_UMSK_ISR_GPA_int11_a(data)                                               (0x00001000&((data)<<12))
#define ISO_UMSK_ISR_GPA_int11_a_src(data)                                           ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_GPA_get_int11_a(data)                                           ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_GPA_int10_a_shift                                               (11)
#define ISO_UMSK_ISR_GPA_int10_a_mask                                                (0x00000800)
#define ISO_UMSK_ISR_GPA_int10_a(data)                                               (0x00000800&((data)<<11))
#define ISO_UMSK_ISR_GPA_int10_a_src(data)                                           ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_GPA_get_int10_a(data)                                           ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_GPA_int9_a_shift                                                (10)
#define ISO_UMSK_ISR_GPA_int9_a_mask                                                 (0x00000400)
#define ISO_UMSK_ISR_GPA_int9_a(data)                                                (0x00000400&((data)<<10))
#define ISO_UMSK_ISR_GPA_int9_a_src(data)                                            ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_GPA_get_int9_a(data)                                            ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_GPA_int8_a_shift                                                (9)
#define ISO_UMSK_ISR_GPA_int8_a_mask                                                 (0x00000200)
#define ISO_UMSK_ISR_GPA_int8_a(data)                                                (0x00000200&((data)<<9))
#define ISO_UMSK_ISR_GPA_int8_a_src(data)                                            ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_GPA_get_int8_a(data)                                            ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_GPA_int7_a_shift                                                (8)
#define ISO_UMSK_ISR_GPA_int7_a_mask                                                 (0x00000100)
#define ISO_UMSK_ISR_GPA_int7_a(data)                                                (0x00000100&((data)<<8))
#define ISO_UMSK_ISR_GPA_int7_a_src(data)                                            ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_GPA_get_int7_a(data)                                            ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_GPA_int6_a_shift                                                (7)
#define ISO_UMSK_ISR_GPA_int6_a_mask                                                 (0x00000080)
#define ISO_UMSK_ISR_GPA_int6_a(data)                                                (0x00000080&((data)<<7))
#define ISO_UMSK_ISR_GPA_int6_a_src(data)                                            ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_GPA_get_int6_a(data)                                            ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_GPA_int5_a_shift                                                (6)
#define ISO_UMSK_ISR_GPA_int5_a_mask                                                 (0x00000040)
#define ISO_UMSK_ISR_GPA_int5_a(data)                                                (0x00000040&((data)<<6))
#define ISO_UMSK_ISR_GPA_int5_a_src(data)                                            ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_GPA_get_int5_a(data)                                            ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_GPA_int4_a_shift                                                (5)
#define ISO_UMSK_ISR_GPA_int4_a_mask                                                 (0x00000020)
#define ISO_UMSK_ISR_GPA_int4_a(data)                                                (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_GPA_int4_a_src(data)                                            ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_GPA_get_int4_a(data)                                            ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_GPA_int3_a_shift                                                (4)
#define ISO_UMSK_ISR_GPA_int3_a_mask                                                 (0x00000010)
#define ISO_UMSK_ISR_GPA_int3_a(data)                                                (0x00000010&((data)<<4))
#define ISO_UMSK_ISR_GPA_int3_a_src(data)                                            ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_GPA_get_int3_a(data)                                            ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_GPA_int2_a_shift                                                (3)
#define ISO_UMSK_ISR_GPA_int2_a_mask                                                 (0x00000008)
#define ISO_UMSK_ISR_GPA_int2_a(data)                                                (0x00000008&((data)<<3))
#define ISO_UMSK_ISR_GPA_int2_a_src(data)                                            ((0x00000008&(data))>>3)
#define ISO_UMSK_ISR_GPA_get_int2_a(data)                                            ((0x00000008&(data))>>3)
#define ISO_UMSK_ISR_GPA_int1_a_shift                                                (2)
#define ISO_UMSK_ISR_GPA_int1_a_mask                                                 (0x00000004)
#define ISO_UMSK_ISR_GPA_int1_a(data)                                                (0x00000004&((data)<<2))
#define ISO_UMSK_ISR_GPA_int1_a_src(data)                                            ((0x00000004&(data))>>2)
#define ISO_UMSK_ISR_GPA_get_int1_a(data)                                            ((0x00000004&(data))>>2)
#define ISO_UMSK_ISR_GPA_int0_a_shift                                                (1)
#define ISO_UMSK_ISR_GPA_int0_a_mask                                                 (0x00000002)
#define ISO_UMSK_ISR_GPA_int0_a(data)                                                (0x00000002&((data)<<1))
#define ISO_UMSK_ISR_GPA_int0_a_src(data)                                            ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_GPA_get_int0_a(data)                                            ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_GPA_write_data_shift                                            (0)
#define ISO_UMSK_ISR_GPA_write_data_mask                                             (0x00000001)
#define ISO_UMSK_ISR_GPA_write_data(data)                                            (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_GPA_write_data_src(data)                                        ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_GPA_get_write_data(data)                                        ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR_GPDA                                                            0x1800700C
#define ISO_UMSK_ISR_GPDA_reg_addr                                                   "0xB800700C"
#define ISO_UMSK_ISR_GPDA_reg                                                        0xB800700C
#define set_ISO_UMSK_ISR_GPDA_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_GPDA_reg)=data)
#define get_ISO_UMSK_ISR_GPDA_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_GPDA_reg))
#define ISO_UMSK_ISR_GPDA_inst_adr                                                   "0x0003"
#define ISO_UMSK_ISR_GPDA_inst                                                       0x0003
#define ISO_UMSK_ISR_GPDA_int20_da_shift                                             (21)
#define ISO_UMSK_ISR_GPDA_int20_da_mask                                              (0x00200000)
#define ISO_UMSK_ISR_GPDA_int20_da(data)                                             (0x00200000&((data)<<21))
#define ISO_UMSK_ISR_GPDA_int20_da_src(data)                                         ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_GPDA_get_int20_da(data)                                         ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_GPDA_int19_da_shift                                             (20)
#define ISO_UMSK_ISR_GPDA_int19_da_mask                                              (0x00100000)
#define ISO_UMSK_ISR_GPDA_int19_da(data)                                             (0x00100000&((data)<<20))
#define ISO_UMSK_ISR_GPDA_int19_da_src(data)                                         ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_GPDA_get_int19_da(data)                                         ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_GPDA_int18_da_shift                                             (19)
#define ISO_UMSK_ISR_GPDA_int18_da_mask                                              (0x00080000)
#define ISO_UMSK_ISR_GPDA_int18_da(data)                                             (0x00080000&((data)<<19))
#define ISO_UMSK_ISR_GPDA_int18_da_src(data)                                         ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_GPDA_get_int18_da(data)                                         ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_GPDA_int17_da_shift                                             (18)
#define ISO_UMSK_ISR_GPDA_int17_da_mask                                              (0x00040000)
#define ISO_UMSK_ISR_GPDA_int17_da(data)                                             (0x00040000&((data)<<18))
#define ISO_UMSK_ISR_GPDA_int17_da_src(data)                                         ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_GPDA_get_int17_da(data)                                         ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_GPDA_int16_da_shift                                             (17)
#define ISO_UMSK_ISR_GPDA_int16_da_mask                                              (0x00020000)
#define ISO_UMSK_ISR_GPDA_int16_da(data)                                             (0x00020000&((data)<<17))
#define ISO_UMSK_ISR_GPDA_int16_da_src(data)                                         ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_GPDA_get_int16_da(data)                                         ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_GPDA_int15_da_shift                                             (16)
#define ISO_UMSK_ISR_GPDA_int15_da_mask                                              (0x00010000)
#define ISO_UMSK_ISR_GPDA_int15_da(data)                                             (0x00010000&((data)<<16))
#define ISO_UMSK_ISR_GPDA_int15_da_src(data)                                         ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_GPDA_get_int15_da(data)                                         ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_GPDA_int14_da_shift                                             (15)
#define ISO_UMSK_ISR_GPDA_int14_da_mask                                              (0x00008000)
#define ISO_UMSK_ISR_GPDA_int14_da(data)                                             (0x00008000&((data)<<15))
#define ISO_UMSK_ISR_GPDA_int14_da_src(data)                                         ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_GPDA_get_int14_da(data)                                         ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_GPDA_int13_da_shift                                             (14)
#define ISO_UMSK_ISR_GPDA_int13_da_mask                                              (0x00004000)
#define ISO_UMSK_ISR_GPDA_int13_da(data)                                             (0x00004000&((data)<<14))
#define ISO_UMSK_ISR_GPDA_int13_da_src(data)                                         ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_GPDA_get_int13_da(data)                                         ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_GPDA_int12_da_shift                                             (13)
#define ISO_UMSK_ISR_GPDA_int12_da_mask                                              (0x00002000)
#define ISO_UMSK_ISR_GPDA_int12_da(data)                                             (0x00002000&((data)<<13))
#define ISO_UMSK_ISR_GPDA_int12_da_src(data)                                         ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_GPDA_get_int12_da(data)                                         ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_GPDA_int11_da_shift                                             (12)
#define ISO_UMSK_ISR_GPDA_int11_da_mask                                              (0x00001000)
#define ISO_UMSK_ISR_GPDA_int11_da(data)                                             (0x00001000&((data)<<12))
#define ISO_UMSK_ISR_GPDA_int11_da_src(data)                                         ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_GPDA_get_int11_da(data)                                         ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_GPDA_int10_da_shift                                             (11)
#define ISO_UMSK_ISR_GPDA_int10_da_mask                                              (0x00000800)
#define ISO_UMSK_ISR_GPDA_int10_da(data)                                             (0x00000800&((data)<<11))
#define ISO_UMSK_ISR_GPDA_int10_da_src(data)                                         ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_GPDA_get_int10_da(data)                                         ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_GPDA_int9_da_shift                                              (10)
#define ISO_UMSK_ISR_GPDA_int9_da_mask                                               (0x00000400)
#define ISO_UMSK_ISR_GPDA_int9_da(data)                                              (0x00000400&((data)<<10))
#define ISO_UMSK_ISR_GPDA_int9_da_src(data)                                          ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_GPDA_get_int9_da(data)                                          ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_GPDA_int8_da_shift                                              (9)
#define ISO_UMSK_ISR_GPDA_int8_da_mask                                               (0x00000200)
#define ISO_UMSK_ISR_GPDA_int8_da(data)                                              (0x00000200&((data)<<9))
#define ISO_UMSK_ISR_GPDA_int8_da_src(data)                                          ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_GPDA_get_int8_da(data)                                          ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_GPDA_int7_da_shift                                              (8)
#define ISO_UMSK_ISR_GPDA_int7_da_mask                                               (0x00000100)
#define ISO_UMSK_ISR_GPDA_int7_da(data)                                              (0x00000100&((data)<<8))
#define ISO_UMSK_ISR_GPDA_int7_da_src(data)                                          ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_GPDA_get_int7_da(data)                                          ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_GPDA_int6_da_shift                                              (7)
#define ISO_UMSK_ISR_GPDA_int6_da_mask                                               (0x00000080)
#define ISO_UMSK_ISR_GPDA_int6_da(data)                                              (0x00000080&((data)<<7))
#define ISO_UMSK_ISR_GPDA_int6_da_src(data)                                          ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_GPDA_get_int6_da(data)                                          ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_GPDA_int5_da_shift                                              (6)
#define ISO_UMSK_ISR_GPDA_int5_da_mask                                               (0x00000040)
#define ISO_UMSK_ISR_GPDA_int5_da(data)                                              (0x00000040&((data)<<6))
#define ISO_UMSK_ISR_GPDA_int5_da_src(data)                                          ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_GPDA_get_int5_da(data)                                          ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_GPDA_int4_da_shift                                              (5)
#define ISO_UMSK_ISR_GPDA_int4_da_mask                                               (0x00000020)
#define ISO_UMSK_ISR_GPDA_int4_da(data)                                              (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_GPDA_int4_da_src(data)                                          ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_GPDA_get_int4_da(data)                                          ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_GPDA_int3_da_shift                                              (4)
#define ISO_UMSK_ISR_GPDA_int3_da_mask                                               (0x00000010)
#define ISO_UMSK_ISR_GPDA_int3_da(data)                                              (0x00000010&((data)<<4))
#define ISO_UMSK_ISR_GPDA_int3_da_src(data)                                          ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_GPDA_get_int3_da(data)                                          ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_GPDA_int2_da_shift                                              (3)
#define ISO_UMSK_ISR_GPDA_int2_da_mask                                               (0x00000008)
#define ISO_UMSK_ISR_GPDA_int2_da(data)                                              (0x00000008&((data)<<3))
#define ISO_UMSK_ISR_GPDA_int2_da_src(data)                                          ((0x00000008&(data))>>3)
#define ISO_UMSK_ISR_GPDA_get_int2_da(data)                                          ((0x00000008&(data))>>3)
#define ISO_UMSK_ISR_GPDA_int1_da_shift                                              (2)
#define ISO_UMSK_ISR_GPDA_int1_da_mask                                               (0x00000004)
#define ISO_UMSK_ISR_GPDA_int1_da(data)                                              (0x00000004&((data)<<2))
#define ISO_UMSK_ISR_GPDA_int1_da_src(data)                                          ((0x00000004&(data))>>2)
#define ISO_UMSK_ISR_GPDA_get_int1_da(data)                                          ((0x00000004&(data))>>2)
#define ISO_UMSK_ISR_GPDA_int0_da_shift                                              (1)
#define ISO_UMSK_ISR_GPDA_int0_da_mask                                               (0x00000002)
#define ISO_UMSK_ISR_GPDA_int0_da(data)                                              (0x00000002&((data)<<1))
#define ISO_UMSK_ISR_GPDA_int0_da_src(data)                                          ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_GPDA_get_int0_da(data)                                          ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_GPDA_write_data_shift                                           (0)
#define ISO_UMSK_ISR_GPDA_write_data_mask                                            (0x00000001)
#define ISO_UMSK_ISR_GPDA_write_data(data)                                           (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_GPDA_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_GPDA_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR_KPADAH                                                          0x18007010
#define ISO_UMSK_ISR_KPADAH_reg_addr                                                 "0xB8007010"
#define ISO_UMSK_ISR_KPADAH_reg                                                      0xB8007010
#define set_ISO_UMSK_ISR_KPADAH_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_KPADAH_reg)=data)
#define get_ISO_UMSK_ISR_KPADAH_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_KPADAH_reg))
#define ISO_UMSK_ISR_KPADAH_inst_adr                                                 "0x0004"
#define ISO_UMSK_ISR_KPADAH_inst                                                     0x0004
#define ISO_UMSK_ISR_KPADAH_int47_shift                                              (23)
#define ISO_UMSK_ISR_KPADAH_int47_mask                                               (0x00800000)
#define ISO_UMSK_ISR_KPADAH_int47(data)                                              (0x00800000&((data)<<23))
#define ISO_UMSK_ISR_KPADAH_int47_src(data)                                          ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_KPADAH_get_int47(data)                                          ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_KPADAH_int46_shift                                              (22)
#define ISO_UMSK_ISR_KPADAH_int46_mask                                               (0x00400000)
#define ISO_UMSK_ISR_KPADAH_int46(data)                                              (0x00400000&((data)<<22))
#define ISO_UMSK_ISR_KPADAH_int46_src(data)                                          ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_KPADAH_get_int46(data)                                          ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_KPADAH_int45_shift                                              (21)
#define ISO_UMSK_ISR_KPADAH_int45_mask                                               (0x00200000)
#define ISO_UMSK_ISR_KPADAH_int45(data)                                              (0x00200000&((data)<<21))
#define ISO_UMSK_ISR_KPADAH_int45_src(data)                                          ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_KPADAH_get_int45(data)                                          ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_KPADAH_int44_shift                                              (20)
#define ISO_UMSK_ISR_KPADAH_int44_mask                                               (0x00100000)
#define ISO_UMSK_ISR_KPADAH_int44(data)                                              (0x00100000&((data)<<20))
#define ISO_UMSK_ISR_KPADAH_int44_src(data)                                          ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_KPADAH_get_int44(data)                                          ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_KPADAH_int43_shift                                              (19)
#define ISO_UMSK_ISR_KPADAH_int43_mask                                               (0x00080000)
#define ISO_UMSK_ISR_KPADAH_int43(data)                                              (0x00080000&((data)<<19))
#define ISO_UMSK_ISR_KPADAH_int43_src(data)                                          ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_KPADAH_get_int43(data)                                          ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_KPADAH_int42_shift                                              (18)
#define ISO_UMSK_ISR_KPADAH_int42_mask                                               (0x00040000)
#define ISO_UMSK_ISR_KPADAH_int42(data)                                              (0x00040000&((data)<<18))
#define ISO_UMSK_ISR_KPADAH_int42_src(data)                                          ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_KPADAH_get_int42(data)                                          ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_KPADAH_int41_shift                                              (17)
#define ISO_UMSK_ISR_KPADAH_int41_mask                                               (0x00020000)
#define ISO_UMSK_ISR_KPADAH_int41(data)                                              (0x00020000&((data)<<17))
#define ISO_UMSK_ISR_KPADAH_int41_src(data)                                          ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_KPADAH_get_int41(data)                                          ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_KPADAH_int40_shift                                              (16)
#define ISO_UMSK_ISR_KPADAH_int40_mask                                               (0x00010000)
#define ISO_UMSK_ISR_KPADAH_int40(data)                                              (0x00010000&((data)<<16))
#define ISO_UMSK_ISR_KPADAH_int40_src(data)                                          ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_KPADAH_get_int40(data)                                          ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_KPADAH_int39_shift                                              (15)
#define ISO_UMSK_ISR_KPADAH_int39_mask                                               (0x00008000)
#define ISO_UMSK_ISR_KPADAH_int39(data)                                              (0x00008000&((data)<<15))
#define ISO_UMSK_ISR_KPADAH_int39_src(data)                                          ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_KPADAH_get_int39(data)                                          ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_KPADAH_int38_shift                                              (14)
#define ISO_UMSK_ISR_KPADAH_int38_mask                                               (0x00004000)
#define ISO_UMSK_ISR_KPADAH_int38(data)                                              (0x00004000&((data)<<14))
#define ISO_UMSK_ISR_KPADAH_int38_src(data)                                          ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_KPADAH_get_int38(data)                                          ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_KPADAH_int37_shift                                              (13)
#define ISO_UMSK_ISR_KPADAH_int37_mask                                               (0x00002000)
#define ISO_UMSK_ISR_KPADAH_int37(data)                                              (0x00002000&((data)<<13))
#define ISO_UMSK_ISR_KPADAH_int37_src(data)                                          ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_KPADAH_get_int37(data)                                          ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_KPADAH_int36_shift                                              (12)
#define ISO_UMSK_ISR_KPADAH_int36_mask                                               (0x00001000)
#define ISO_UMSK_ISR_KPADAH_int36(data)                                              (0x00001000&((data)<<12))
#define ISO_UMSK_ISR_KPADAH_int36_src(data)                                          ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_KPADAH_get_int36(data)                                          ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_KPADAH_int35_shift                                              (11)
#define ISO_UMSK_ISR_KPADAH_int35_mask                                               (0x00000800)
#define ISO_UMSK_ISR_KPADAH_int35(data)                                              (0x00000800&((data)<<11))
#define ISO_UMSK_ISR_KPADAH_int35_src(data)                                          ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_KPADAH_get_int35(data)                                          ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_KPADAH_int34_shift                                              (10)
#define ISO_UMSK_ISR_KPADAH_int34_mask                                               (0x00000400)
#define ISO_UMSK_ISR_KPADAH_int34(data)                                              (0x00000400&((data)<<10))
#define ISO_UMSK_ISR_KPADAH_int34_src(data)                                          ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_KPADAH_get_int34(data)                                          ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_KPADAH_int33_shift                                              (9)
#define ISO_UMSK_ISR_KPADAH_int33_mask                                               (0x00000200)
#define ISO_UMSK_ISR_KPADAH_int33(data)                                              (0x00000200&((data)<<9))
#define ISO_UMSK_ISR_KPADAH_int33_src(data)                                          ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_KPADAH_get_int33(data)                                          ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_KPADAH_int32_shift                                              (8)
#define ISO_UMSK_ISR_KPADAH_int32_mask                                               (0x00000100)
#define ISO_UMSK_ISR_KPADAH_int32(data)                                              (0x00000100&((data)<<8))
#define ISO_UMSK_ISR_KPADAH_int32_src(data)                                          ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_KPADAH_get_int32(data)                                          ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_KPADAH_int31_shift                                              (7)
#define ISO_UMSK_ISR_KPADAH_int31_mask                                               (0x00000080)
#define ISO_UMSK_ISR_KPADAH_int31(data)                                              (0x00000080&((data)<<7))
#define ISO_UMSK_ISR_KPADAH_int31_src(data)                                          ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_KPADAH_get_int31(data)                                          ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_KPADAH_int30_shift                                              (6)
#define ISO_UMSK_ISR_KPADAH_int30_mask                                               (0x00000040)
#define ISO_UMSK_ISR_KPADAH_int30(data)                                              (0x00000040&((data)<<6))
#define ISO_UMSK_ISR_KPADAH_int30_src(data)                                          ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_KPADAH_get_int30(data)                                          ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_KPADAH_int29_shift                                              (5)
#define ISO_UMSK_ISR_KPADAH_int29_mask                                               (0x00000020)
#define ISO_UMSK_ISR_KPADAH_int29(data)                                              (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_KPADAH_int29_src(data)                                          ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_KPADAH_get_int29(data)                                          ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_KPADAH_int28_shift                                              (4)
#define ISO_UMSK_ISR_KPADAH_int28_mask                                               (0x00000010)
#define ISO_UMSK_ISR_KPADAH_int28(data)                                              (0x00000010&((data)<<4))
#define ISO_UMSK_ISR_KPADAH_int28_src(data)                                          ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_KPADAH_get_int28(data)                                          ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_KPADAH_write_data_shift                                         (0)
#define ISO_UMSK_ISR_KPADAH_write_data_mask                                          (0x00000001)
#define ISO_UMSK_ISR_KPADAH_write_data(data)                                         (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_KPADAH_write_data_src(data)                                     ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_KPADAH_get_write_data(data)                                     ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR_KPADAL                                                          0x18007014
#define ISO_UMSK_ISR_KPADAL_reg_addr                                                 "0xB8007014"
#define ISO_UMSK_ISR_KPADAL_reg                                                      0xB8007014
#define set_ISO_UMSK_ISR_KPADAL_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_KPADAL_reg)=data)
#define get_ISO_UMSK_ISR_KPADAL_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_KPADAL_reg))
#define ISO_UMSK_ISR_KPADAL_inst_adr                                                 "0x0005"
#define ISO_UMSK_ISR_KPADAL_inst                                                     0x0005
#define ISO_UMSK_ISR_KPADAL_int27_shift                                              (31)
#define ISO_UMSK_ISR_KPADAL_int27_mask                                               (0x80000000)
#define ISO_UMSK_ISR_KPADAL_int27(data)                                              (0x80000000&((data)<<31))
#define ISO_UMSK_ISR_KPADAL_int27_src(data)                                          ((0x80000000&(data))>>31)
#define ISO_UMSK_ISR_KPADAL_get_int27(data)                                          ((0x80000000&(data))>>31)
#define ISO_UMSK_ISR_KPADAL_int26_shift                                              (30)
#define ISO_UMSK_ISR_KPADAL_int26_mask                                               (0x40000000)
#define ISO_UMSK_ISR_KPADAL_int26(data)                                              (0x40000000&((data)<<30))
#define ISO_UMSK_ISR_KPADAL_int26_src(data)                                          ((0x40000000&(data))>>30)
#define ISO_UMSK_ISR_KPADAL_get_int26(data)                                          ((0x40000000&(data))>>30)
#define ISO_UMSK_ISR_KPADAL_int25_shift                                              (29)
#define ISO_UMSK_ISR_KPADAL_int25_mask                                               (0x20000000)
#define ISO_UMSK_ISR_KPADAL_int25(data)                                              (0x20000000&((data)<<29))
#define ISO_UMSK_ISR_KPADAL_int25_src(data)                                          ((0x20000000&(data))>>29)
#define ISO_UMSK_ISR_KPADAL_get_int25(data)                                          ((0x20000000&(data))>>29)
#define ISO_UMSK_ISR_KPADAL_int24_shift                                              (28)
#define ISO_UMSK_ISR_KPADAL_int24_mask                                               (0x10000000)
#define ISO_UMSK_ISR_KPADAL_int24(data)                                              (0x10000000&((data)<<28))
#define ISO_UMSK_ISR_KPADAL_int24_src(data)                                          ((0x10000000&(data))>>28)
#define ISO_UMSK_ISR_KPADAL_get_int24(data)                                          ((0x10000000&(data))>>28)
#define ISO_UMSK_ISR_KPADAL_int23_shift                                              (27)
#define ISO_UMSK_ISR_KPADAL_int23_mask                                               (0x08000000)
#define ISO_UMSK_ISR_KPADAL_int23(data)                                              (0x08000000&((data)<<27))
#define ISO_UMSK_ISR_KPADAL_int23_src(data)                                          ((0x08000000&(data))>>27)
#define ISO_UMSK_ISR_KPADAL_get_int23(data)                                          ((0x08000000&(data))>>27)
#define ISO_UMSK_ISR_KPADAL_int22_shift                                              (26)
#define ISO_UMSK_ISR_KPADAL_int22_mask                                               (0x04000000)
#define ISO_UMSK_ISR_KPADAL_int22(data)                                              (0x04000000&((data)<<26))
#define ISO_UMSK_ISR_KPADAL_int22_src(data)                                          ((0x04000000&(data))>>26)
#define ISO_UMSK_ISR_KPADAL_get_int22(data)                                          ((0x04000000&(data))>>26)
#define ISO_UMSK_ISR_KPADAL_int21_shift                                              (25)
#define ISO_UMSK_ISR_KPADAL_int21_mask                                               (0x02000000)
#define ISO_UMSK_ISR_KPADAL_int21(data)                                              (0x02000000&((data)<<25))
#define ISO_UMSK_ISR_KPADAL_int21_src(data)                                          ((0x02000000&(data))>>25)
#define ISO_UMSK_ISR_KPADAL_get_int21(data)                                          ((0x02000000&(data))>>25)
#define ISO_UMSK_ISR_KPADAL_int20_shift                                              (24)
#define ISO_UMSK_ISR_KPADAL_int20_mask                                               (0x01000000)
#define ISO_UMSK_ISR_KPADAL_int20(data)                                              (0x01000000&((data)<<24))
#define ISO_UMSK_ISR_KPADAL_int20_src(data)                                          ((0x01000000&(data))>>24)
#define ISO_UMSK_ISR_KPADAL_get_int20(data)                                          ((0x01000000&(data))>>24)
#define ISO_UMSK_ISR_KPADAL_int19_shift                                              (23)
#define ISO_UMSK_ISR_KPADAL_int19_mask                                               (0x00800000)
#define ISO_UMSK_ISR_KPADAL_int19(data)                                              (0x00800000&((data)<<23))
#define ISO_UMSK_ISR_KPADAL_int19_src(data)                                          ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_KPADAL_get_int19(data)                                          ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_KPADAL_int18_shift                                              (22)
#define ISO_UMSK_ISR_KPADAL_int18_mask                                               (0x00400000)
#define ISO_UMSK_ISR_KPADAL_int18(data)                                              (0x00400000&((data)<<22))
#define ISO_UMSK_ISR_KPADAL_int18_src(data)                                          ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_KPADAL_get_int18(data)                                          ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_KPADAL_int17_shift                                              (21)
#define ISO_UMSK_ISR_KPADAL_int17_mask                                               (0x00200000)
#define ISO_UMSK_ISR_KPADAL_int17(data)                                              (0x00200000&((data)<<21))
#define ISO_UMSK_ISR_KPADAL_int17_src(data)                                          ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_KPADAL_get_int17(data)                                          ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_KPADAL_int16_shift                                              (20)
#define ISO_UMSK_ISR_KPADAL_int16_mask                                               (0x00100000)
#define ISO_UMSK_ISR_KPADAL_int16(data)                                              (0x00100000&((data)<<20))
#define ISO_UMSK_ISR_KPADAL_int16_src(data)                                          ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_KPADAL_get_int16(data)                                          ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_KPADAL_int15_shift                                              (19)
#define ISO_UMSK_ISR_KPADAL_int15_mask                                               (0x00080000)
#define ISO_UMSK_ISR_KPADAL_int15(data)                                              (0x00080000&((data)<<19))
#define ISO_UMSK_ISR_KPADAL_int15_src(data)                                          ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_KPADAL_get_int15(data)                                          ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_KPADAL_int14_shift                                              (18)
#define ISO_UMSK_ISR_KPADAL_int14_mask                                               (0x00040000)
#define ISO_UMSK_ISR_KPADAL_int14(data)                                              (0x00040000&((data)<<18))
#define ISO_UMSK_ISR_KPADAL_int14_src(data)                                          ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_KPADAL_get_int14(data)                                          ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_KPADAL_int13_shift                                              (17)
#define ISO_UMSK_ISR_KPADAL_int13_mask                                               (0x00020000)
#define ISO_UMSK_ISR_KPADAL_int13(data)                                              (0x00020000&((data)<<17))
#define ISO_UMSK_ISR_KPADAL_int13_src(data)                                          ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_KPADAL_get_int13(data)                                          ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_KPADAL_int12_shift                                              (16)
#define ISO_UMSK_ISR_KPADAL_int12_mask                                               (0x00010000)
#define ISO_UMSK_ISR_KPADAL_int12(data)                                              (0x00010000&((data)<<16))
#define ISO_UMSK_ISR_KPADAL_int12_src(data)                                          ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_KPADAL_get_int12(data)                                          ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_KPADAL_int11_shift                                              (15)
#define ISO_UMSK_ISR_KPADAL_int11_mask                                               (0x00008000)
#define ISO_UMSK_ISR_KPADAL_int11(data)                                              (0x00008000&((data)<<15))
#define ISO_UMSK_ISR_KPADAL_int11_src(data)                                          ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_KPADAL_get_int11(data)                                          ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_KPADAL_int10_shift                                              (14)
#define ISO_UMSK_ISR_KPADAL_int10_mask                                               (0x00004000)
#define ISO_UMSK_ISR_KPADAL_int10(data)                                              (0x00004000&((data)<<14))
#define ISO_UMSK_ISR_KPADAL_int10_src(data)                                          ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_KPADAL_get_int10(data)                                          ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_KPADAL_int9_shift                                               (13)
#define ISO_UMSK_ISR_KPADAL_int9_mask                                                (0x00002000)
#define ISO_UMSK_ISR_KPADAL_int9(data)                                               (0x00002000&((data)<<13))
#define ISO_UMSK_ISR_KPADAL_int9_src(data)                                           ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_KPADAL_get_int9(data)                                           ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_KPADAL_int8_shift                                               (12)
#define ISO_UMSK_ISR_KPADAL_int8_mask                                                (0x00001000)
#define ISO_UMSK_ISR_KPADAL_int8(data)                                               (0x00001000&((data)<<12))
#define ISO_UMSK_ISR_KPADAL_int8_src(data)                                           ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_KPADAL_get_int8(data)                                           ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_KPADAL_int7_shift                                               (11)
#define ISO_UMSK_ISR_KPADAL_int7_mask                                                (0x00000800)
#define ISO_UMSK_ISR_KPADAL_int7(data)                                               (0x00000800&((data)<<11))
#define ISO_UMSK_ISR_KPADAL_int7_src(data)                                           ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_KPADAL_get_int7(data)                                           ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_KPADAL_int6_shift                                               (10)
#define ISO_UMSK_ISR_KPADAL_int6_mask                                                (0x00000400)
#define ISO_UMSK_ISR_KPADAL_int6(data)                                               (0x00000400&((data)<<10))
#define ISO_UMSK_ISR_KPADAL_int6_src(data)                                           ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_KPADAL_get_int6(data)                                           ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_KPADAL_int5_shift                                               (9)
#define ISO_UMSK_ISR_KPADAL_int5_mask                                                (0x00000200)
#define ISO_UMSK_ISR_KPADAL_int5(data)                                               (0x00000200&((data)<<9))
#define ISO_UMSK_ISR_KPADAL_int5_src(data)                                           ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_KPADAL_get_int5(data)                                           ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_KPADAL_int4_shift                                               (8)
#define ISO_UMSK_ISR_KPADAL_int4_mask                                                (0x00000100)
#define ISO_UMSK_ISR_KPADAL_int4(data)                                               (0x00000100&((data)<<8))
#define ISO_UMSK_ISR_KPADAL_int4_src(data)                                           ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_KPADAL_get_int4(data)                                           ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_KPADAL_int3_shift                                               (7)
#define ISO_UMSK_ISR_KPADAL_int3_mask                                                (0x00000080)
#define ISO_UMSK_ISR_KPADAL_int3(data)                                               (0x00000080&((data)<<7))
#define ISO_UMSK_ISR_KPADAL_int3_src(data)                                           ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_KPADAL_get_int3(data)                                           ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_KPADAL_int2_shift                                               (6)
#define ISO_UMSK_ISR_KPADAL_int2_mask                                                (0x00000040)
#define ISO_UMSK_ISR_KPADAL_int2(data)                                               (0x00000040&((data)<<6))
#define ISO_UMSK_ISR_KPADAL_int2_src(data)                                           ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_KPADAL_get_int2(data)                                           ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_KPADAL_int1_shift                                               (5)
#define ISO_UMSK_ISR_KPADAL_int1_mask                                                (0x00000020)
#define ISO_UMSK_ISR_KPADAL_int1(data)                                               (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_KPADAL_int1_src(data)                                           ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_KPADAL_get_int1(data)                                           ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_KPADAL_int0_shift                                               (4)
#define ISO_UMSK_ISR_KPADAL_int0_mask                                                (0x00000010)
#define ISO_UMSK_ISR_KPADAL_int0(data)                                               (0x00000010&((data)<<4))
#define ISO_UMSK_ISR_KPADAL_int0_src(data)                                           ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_KPADAL_get_int0(data)                                           ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_KPADAL_write_data_shift                                         (0)
#define ISO_UMSK_ISR_KPADAL_write_data_mask                                          (0x00000001)
#define ISO_UMSK_ISR_KPADAL_write_data(data)                                         (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_KPADAL_write_data_src(data)                                     ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_KPADAL_get_write_data(data)                                     ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR_KPADDAH                                                         0x18007018
#define ISO_UMSK_ISR_KPADDAH_reg_addr                                                "0xB8007018"
#define ISO_UMSK_ISR_KPADDAH_reg                                                     0xB8007018
#define set_ISO_UMSK_ISR_KPADDAH_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_KPADDAH_reg)=data)
#define get_ISO_UMSK_ISR_KPADDAH_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_KPADDAH_reg))
#define ISO_UMSK_ISR_KPADDAH_inst_adr                                                "0x0006"
#define ISO_UMSK_ISR_KPADDAH_inst                                                    0x0006
#define ISO_UMSK_ISR_KPADDAH_int47_shift                                             (23)
#define ISO_UMSK_ISR_KPADDAH_int47_mask                                              (0x00800000)
#define ISO_UMSK_ISR_KPADDAH_int47(data)                                             (0x00800000&((data)<<23))
#define ISO_UMSK_ISR_KPADDAH_int47_src(data)                                         ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_KPADDAH_get_int47(data)                                         ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_KPADDAH_int46_shift                                             (22)
#define ISO_UMSK_ISR_KPADDAH_int46_mask                                              (0x00400000)
#define ISO_UMSK_ISR_KPADDAH_int46(data)                                             (0x00400000&((data)<<22))
#define ISO_UMSK_ISR_KPADDAH_int46_src(data)                                         ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_KPADDAH_get_int46(data)                                         ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_KPADDAH_int45_shift                                             (21)
#define ISO_UMSK_ISR_KPADDAH_int45_mask                                              (0x00200000)
#define ISO_UMSK_ISR_KPADDAH_int45(data)                                             (0x00200000&((data)<<21))
#define ISO_UMSK_ISR_KPADDAH_int45_src(data)                                         ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_KPADDAH_get_int45(data)                                         ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_KPADDAH_int44_shift                                             (20)
#define ISO_UMSK_ISR_KPADDAH_int44_mask                                              (0x00100000)
#define ISO_UMSK_ISR_KPADDAH_int44(data)                                             (0x00100000&((data)<<20))
#define ISO_UMSK_ISR_KPADDAH_int44_src(data)                                         ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_KPADDAH_get_int44(data)                                         ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_KPADDAH_int43_shift                                             (19)
#define ISO_UMSK_ISR_KPADDAH_int43_mask                                              (0x00080000)
#define ISO_UMSK_ISR_KPADDAH_int43(data)                                             (0x00080000&((data)<<19))
#define ISO_UMSK_ISR_KPADDAH_int43_src(data)                                         ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_KPADDAH_get_int43(data)                                         ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_KPADDAH_int42_shift                                             (18)
#define ISO_UMSK_ISR_KPADDAH_int42_mask                                              (0x00040000)
#define ISO_UMSK_ISR_KPADDAH_int42(data)                                             (0x00040000&((data)<<18))
#define ISO_UMSK_ISR_KPADDAH_int42_src(data)                                         ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_KPADDAH_get_int42(data)                                         ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_KPADDAH_int41_shift                                             (17)
#define ISO_UMSK_ISR_KPADDAH_int41_mask                                              (0x00020000)
#define ISO_UMSK_ISR_KPADDAH_int41(data)                                             (0x00020000&((data)<<17))
#define ISO_UMSK_ISR_KPADDAH_int41_src(data)                                         ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_KPADDAH_get_int41(data)                                         ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_KPADDAH_int40_shift                                             (16)
#define ISO_UMSK_ISR_KPADDAH_int40_mask                                              (0x00010000)
#define ISO_UMSK_ISR_KPADDAH_int40(data)                                             (0x00010000&((data)<<16))
#define ISO_UMSK_ISR_KPADDAH_int40_src(data)                                         ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_KPADDAH_get_int40(data)                                         ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_KPADDAH_int39_shift                                             (15)
#define ISO_UMSK_ISR_KPADDAH_int39_mask                                              (0x00008000)
#define ISO_UMSK_ISR_KPADDAH_int39(data)                                             (0x00008000&((data)<<15))
#define ISO_UMSK_ISR_KPADDAH_int39_src(data)                                         ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_KPADDAH_get_int39(data)                                         ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_KPADDAH_int38_shift                                             (14)
#define ISO_UMSK_ISR_KPADDAH_int38_mask                                              (0x00004000)
#define ISO_UMSK_ISR_KPADDAH_int38(data)                                             (0x00004000&((data)<<14))
#define ISO_UMSK_ISR_KPADDAH_int38_src(data)                                         ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_KPADDAH_get_int38(data)                                         ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_KPADDAH_int37_shift                                             (13)
#define ISO_UMSK_ISR_KPADDAH_int37_mask                                              (0x00002000)
#define ISO_UMSK_ISR_KPADDAH_int37(data)                                             (0x00002000&((data)<<13))
#define ISO_UMSK_ISR_KPADDAH_int37_src(data)                                         ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_KPADDAH_get_int37(data)                                         ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_KPADDAH_int36_shift                                             (12)
#define ISO_UMSK_ISR_KPADDAH_int36_mask                                              (0x00001000)
#define ISO_UMSK_ISR_KPADDAH_int36(data)                                             (0x00001000&((data)<<12))
#define ISO_UMSK_ISR_KPADDAH_int36_src(data)                                         ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_KPADDAH_get_int36(data)                                         ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_KPADDAH_int35_shift                                             (11)
#define ISO_UMSK_ISR_KPADDAH_int35_mask                                              (0x00000800)
#define ISO_UMSK_ISR_KPADDAH_int35(data)                                             (0x00000800&((data)<<11))
#define ISO_UMSK_ISR_KPADDAH_int35_src(data)                                         ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_KPADDAH_get_int35(data)                                         ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_KPADDAH_int34_shift                                             (10)
#define ISO_UMSK_ISR_KPADDAH_int34_mask                                              (0x00000400)
#define ISO_UMSK_ISR_KPADDAH_int34(data)                                             (0x00000400&((data)<<10))
#define ISO_UMSK_ISR_KPADDAH_int34_src(data)                                         ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_KPADDAH_get_int34(data)                                         ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_KPADDAH_int33_shift                                             (9)
#define ISO_UMSK_ISR_KPADDAH_int33_mask                                              (0x00000200)
#define ISO_UMSK_ISR_KPADDAH_int33(data)                                             (0x00000200&((data)<<9))
#define ISO_UMSK_ISR_KPADDAH_int33_src(data)                                         ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_KPADDAH_get_int33(data)                                         ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_KPADDAH_int32_shift                                             (8)
#define ISO_UMSK_ISR_KPADDAH_int32_mask                                              (0x00000100)
#define ISO_UMSK_ISR_KPADDAH_int32(data)                                             (0x00000100&((data)<<8))
#define ISO_UMSK_ISR_KPADDAH_int32_src(data)                                         ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_KPADDAH_get_int32(data)                                         ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_KPADDAH_int31_shift                                             (7)
#define ISO_UMSK_ISR_KPADDAH_int31_mask                                              (0x00000080)
#define ISO_UMSK_ISR_KPADDAH_int31(data)                                             (0x00000080&((data)<<7))
#define ISO_UMSK_ISR_KPADDAH_int31_src(data)                                         ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_KPADDAH_get_int31(data)                                         ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_KPADDAH_int30_shift                                             (6)
#define ISO_UMSK_ISR_KPADDAH_int30_mask                                              (0x00000040)
#define ISO_UMSK_ISR_KPADDAH_int30(data)                                             (0x00000040&((data)<<6))
#define ISO_UMSK_ISR_KPADDAH_int30_src(data)                                         ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_KPADDAH_get_int30(data)                                         ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_KPADDAH_int29_shift                                             (5)
#define ISO_UMSK_ISR_KPADDAH_int29_mask                                              (0x00000020)
#define ISO_UMSK_ISR_KPADDAH_int29(data)                                             (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_KPADDAH_int29_src(data)                                         ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_KPADDAH_get_int29(data)                                         ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_KPADDAH_int28_shift                                             (4)
#define ISO_UMSK_ISR_KPADDAH_int28_mask                                              (0x00000010)
#define ISO_UMSK_ISR_KPADDAH_int28(data)                                             (0x00000010&((data)<<4))
#define ISO_UMSK_ISR_KPADDAH_int28_src(data)                                         ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_KPADDAH_get_int28(data)                                         ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_KPADDAH_write_data_shift                                        (0)
#define ISO_UMSK_ISR_KPADDAH_write_data_mask                                         (0x00000001)
#define ISO_UMSK_ISR_KPADDAH_write_data(data)                                        (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_KPADDAH_write_data_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_KPADDAH_get_write_data(data)                                    ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR_KPADDAL                                                         0x1800701C
#define ISO_UMSK_ISR_KPADDAL_reg_addr                                                "0xB800701C"
#define ISO_UMSK_ISR_KPADDAL_reg                                                     0xB800701C
#define set_ISO_UMSK_ISR_KPADDAL_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_KPADDAL_reg)=data)
#define get_ISO_UMSK_ISR_KPADDAL_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_KPADDAL_reg))
#define ISO_UMSK_ISR_KPADDAL_inst_adr                                                "0x0007"
#define ISO_UMSK_ISR_KPADDAL_inst                                                    0x0007
#define ISO_UMSK_ISR_KPADDAL_int27_shift                                             (31)
#define ISO_UMSK_ISR_KPADDAL_int27_mask                                              (0x80000000)
#define ISO_UMSK_ISR_KPADDAL_int27(data)                                             (0x80000000&((data)<<31))
#define ISO_UMSK_ISR_KPADDAL_int27_src(data)                                         ((0x80000000&(data))>>31)
#define ISO_UMSK_ISR_KPADDAL_get_int27(data)                                         ((0x80000000&(data))>>31)
#define ISO_UMSK_ISR_KPADDAL_int26_shift                                             (30)
#define ISO_UMSK_ISR_KPADDAL_int26_mask                                              (0x40000000)
#define ISO_UMSK_ISR_KPADDAL_int26(data)                                             (0x40000000&((data)<<30))
#define ISO_UMSK_ISR_KPADDAL_int26_src(data)                                         ((0x40000000&(data))>>30)
#define ISO_UMSK_ISR_KPADDAL_get_int26(data)                                         ((0x40000000&(data))>>30)
#define ISO_UMSK_ISR_KPADDAL_int25_shift                                             (29)
#define ISO_UMSK_ISR_KPADDAL_int25_mask                                              (0x20000000)
#define ISO_UMSK_ISR_KPADDAL_int25(data)                                             (0x20000000&((data)<<29))
#define ISO_UMSK_ISR_KPADDAL_int25_src(data)                                         ((0x20000000&(data))>>29)
#define ISO_UMSK_ISR_KPADDAL_get_int25(data)                                         ((0x20000000&(data))>>29)
#define ISO_UMSK_ISR_KPADDAL_int24_shift                                             (28)
#define ISO_UMSK_ISR_KPADDAL_int24_mask                                              (0x10000000)
#define ISO_UMSK_ISR_KPADDAL_int24(data)                                             (0x10000000&((data)<<28))
#define ISO_UMSK_ISR_KPADDAL_int24_src(data)                                         ((0x10000000&(data))>>28)
#define ISO_UMSK_ISR_KPADDAL_get_int24(data)                                         ((0x10000000&(data))>>28)
#define ISO_UMSK_ISR_KPADDAL_int23_shift                                             (27)
#define ISO_UMSK_ISR_KPADDAL_int23_mask                                              (0x08000000)
#define ISO_UMSK_ISR_KPADDAL_int23(data)                                             (0x08000000&((data)<<27))
#define ISO_UMSK_ISR_KPADDAL_int23_src(data)                                         ((0x08000000&(data))>>27)
#define ISO_UMSK_ISR_KPADDAL_get_int23(data)                                         ((0x08000000&(data))>>27)
#define ISO_UMSK_ISR_KPADDAL_int22_shift                                             (26)
#define ISO_UMSK_ISR_KPADDAL_int22_mask                                              (0x04000000)
#define ISO_UMSK_ISR_KPADDAL_int22(data)                                             (0x04000000&((data)<<26))
#define ISO_UMSK_ISR_KPADDAL_int22_src(data)                                         ((0x04000000&(data))>>26)
#define ISO_UMSK_ISR_KPADDAL_get_int22(data)                                         ((0x04000000&(data))>>26)
#define ISO_UMSK_ISR_KPADDAL_int21_shift                                             (25)
#define ISO_UMSK_ISR_KPADDAL_int21_mask                                              (0x02000000)
#define ISO_UMSK_ISR_KPADDAL_int21(data)                                             (0x02000000&((data)<<25))
#define ISO_UMSK_ISR_KPADDAL_int21_src(data)                                         ((0x02000000&(data))>>25)
#define ISO_UMSK_ISR_KPADDAL_get_int21(data)                                         ((0x02000000&(data))>>25)
#define ISO_UMSK_ISR_KPADDAL_int20_shift                                             (24)
#define ISO_UMSK_ISR_KPADDAL_int20_mask                                              (0x01000000)
#define ISO_UMSK_ISR_KPADDAL_int20(data)                                             (0x01000000&((data)<<24))
#define ISO_UMSK_ISR_KPADDAL_int20_src(data)                                         ((0x01000000&(data))>>24)
#define ISO_UMSK_ISR_KPADDAL_get_int20(data)                                         ((0x01000000&(data))>>24)
#define ISO_UMSK_ISR_KPADDAL_int19_shift                                             (23)
#define ISO_UMSK_ISR_KPADDAL_int19_mask                                              (0x00800000)
#define ISO_UMSK_ISR_KPADDAL_int19(data)                                             (0x00800000&((data)<<23))
#define ISO_UMSK_ISR_KPADDAL_int19_src(data)                                         ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_KPADDAL_get_int19(data)                                         ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_KPADDAL_int18_shift                                             (22)
#define ISO_UMSK_ISR_KPADDAL_int18_mask                                              (0x00400000)
#define ISO_UMSK_ISR_KPADDAL_int18(data)                                             (0x00400000&((data)<<22))
#define ISO_UMSK_ISR_KPADDAL_int18_src(data)                                         ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_KPADDAL_get_int18(data)                                         ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_KPADDAL_int17_shift                                             (21)
#define ISO_UMSK_ISR_KPADDAL_int17_mask                                              (0x00200000)
#define ISO_UMSK_ISR_KPADDAL_int17(data)                                             (0x00200000&((data)<<21))
#define ISO_UMSK_ISR_KPADDAL_int17_src(data)                                         ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_KPADDAL_get_int17(data)                                         ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_KPADDAL_int16_shift                                             (20)
#define ISO_UMSK_ISR_KPADDAL_int16_mask                                              (0x00100000)
#define ISO_UMSK_ISR_KPADDAL_int16(data)                                             (0x00100000&((data)<<20))
#define ISO_UMSK_ISR_KPADDAL_int16_src(data)                                         ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_KPADDAL_get_int16(data)                                         ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_KPADDAL_int15_shift                                             (19)
#define ISO_UMSK_ISR_KPADDAL_int15_mask                                              (0x00080000)
#define ISO_UMSK_ISR_KPADDAL_int15(data)                                             (0x00080000&((data)<<19))
#define ISO_UMSK_ISR_KPADDAL_int15_src(data)                                         ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_KPADDAL_get_int15(data)                                         ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_KPADDAL_int14_shift                                             (18)
#define ISO_UMSK_ISR_KPADDAL_int14_mask                                              (0x00040000)
#define ISO_UMSK_ISR_KPADDAL_int14(data)                                             (0x00040000&((data)<<18))
#define ISO_UMSK_ISR_KPADDAL_int14_src(data)                                         ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_KPADDAL_get_int14(data)                                         ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_KPADDAL_int13_shift                                             (17)
#define ISO_UMSK_ISR_KPADDAL_int13_mask                                              (0x00020000)
#define ISO_UMSK_ISR_KPADDAL_int13(data)                                             (0x00020000&((data)<<17))
#define ISO_UMSK_ISR_KPADDAL_int13_src(data)                                         ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_KPADDAL_get_int13(data)                                         ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_KPADDAL_int12_shift                                             (16)
#define ISO_UMSK_ISR_KPADDAL_int12_mask                                              (0x00010000)
#define ISO_UMSK_ISR_KPADDAL_int12(data)                                             (0x00010000&((data)<<16))
#define ISO_UMSK_ISR_KPADDAL_int12_src(data)                                         ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_KPADDAL_get_int12(data)                                         ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_KPADDAL_int11_shift                                             (15)
#define ISO_UMSK_ISR_KPADDAL_int11_mask                                              (0x00008000)
#define ISO_UMSK_ISR_KPADDAL_int11(data)                                             (0x00008000&((data)<<15))
#define ISO_UMSK_ISR_KPADDAL_int11_src(data)                                         ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_KPADDAL_get_int11(data)                                         ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_KPADDAL_int10_shift                                             (14)
#define ISO_UMSK_ISR_KPADDAL_int10_mask                                              (0x00004000)
#define ISO_UMSK_ISR_KPADDAL_int10(data)                                             (0x00004000&((data)<<14))
#define ISO_UMSK_ISR_KPADDAL_int10_src(data)                                         ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_KPADDAL_get_int10(data)                                         ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_KPADDAL_int9_shift                                              (13)
#define ISO_UMSK_ISR_KPADDAL_int9_mask                                               (0x00002000)
#define ISO_UMSK_ISR_KPADDAL_int9(data)                                              (0x00002000&((data)<<13))
#define ISO_UMSK_ISR_KPADDAL_int9_src(data)                                          ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_KPADDAL_get_int9(data)                                          ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_KPADDAL_int8_shift                                              (12)
#define ISO_UMSK_ISR_KPADDAL_int8_mask                                               (0x00001000)
#define ISO_UMSK_ISR_KPADDAL_int8(data)                                              (0x00001000&((data)<<12))
#define ISO_UMSK_ISR_KPADDAL_int8_src(data)                                          ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_KPADDAL_get_int8(data)                                          ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_KPADDAL_int7_shift                                              (11)
#define ISO_UMSK_ISR_KPADDAL_int7_mask                                               (0x00000800)
#define ISO_UMSK_ISR_KPADDAL_int7(data)                                              (0x00000800&((data)<<11))
#define ISO_UMSK_ISR_KPADDAL_int7_src(data)                                          ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_KPADDAL_get_int7(data)                                          ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_KPADDAL_int6_shift                                              (10)
#define ISO_UMSK_ISR_KPADDAL_int6_mask                                               (0x00000400)
#define ISO_UMSK_ISR_KPADDAL_int6(data)                                              (0x00000400&((data)<<10))
#define ISO_UMSK_ISR_KPADDAL_int6_src(data)                                          ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_KPADDAL_get_int6(data)                                          ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_KPADDAL_int5_shift                                              (9)
#define ISO_UMSK_ISR_KPADDAL_int5_mask                                               (0x00000200)
#define ISO_UMSK_ISR_KPADDAL_int5(data)                                              (0x00000200&((data)<<9))
#define ISO_UMSK_ISR_KPADDAL_int5_src(data)                                          ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_KPADDAL_get_int5(data)                                          ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_KPADDAL_int4_shift                                              (8)
#define ISO_UMSK_ISR_KPADDAL_int4_mask                                               (0x00000100)
#define ISO_UMSK_ISR_KPADDAL_int4(data)                                              (0x00000100&((data)<<8))
#define ISO_UMSK_ISR_KPADDAL_int4_src(data)                                          ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_KPADDAL_get_int4(data)                                          ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_KPADDAL_int3_shift                                              (7)
#define ISO_UMSK_ISR_KPADDAL_int3_mask                                               (0x00000080)
#define ISO_UMSK_ISR_KPADDAL_int3(data)                                              (0x00000080&((data)<<7))
#define ISO_UMSK_ISR_KPADDAL_int3_src(data)                                          ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_KPADDAL_get_int3(data)                                          ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_KPADDAL_int2_shift                                              (6)
#define ISO_UMSK_ISR_KPADDAL_int2_mask                                               (0x00000040)
#define ISO_UMSK_ISR_KPADDAL_int2(data)                                              (0x00000040&((data)<<6))
#define ISO_UMSK_ISR_KPADDAL_int2_src(data)                                          ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_KPADDAL_get_int2(data)                                          ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_KPADDAL_int1_shift                                              (5)
#define ISO_UMSK_ISR_KPADDAL_int1_mask                                               (0x00000020)
#define ISO_UMSK_ISR_KPADDAL_int1(data)                                              (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_KPADDAL_int1_src(data)                                          ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_KPADDAL_get_int1(data)                                          ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_KPADDAL_int0_shift                                              (4)
#define ISO_UMSK_ISR_KPADDAL_int0_mask                                               (0x00000010)
#define ISO_UMSK_ISR_KPADDAL_int0(data)                                              (0x00000010&((data)<<4))
#define ISO_UMSK_ISR_KPADDAL_int0_src(data)                                          ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_KPADDAL_get_int0(data)                                          ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_KPADDAL_write_data_shift                                        (0)
#define ISO_UMSK_ISR_KPADDAL_write_data_mask                                         (0x00000001)
#define ISO_UMSK_ISR_KPADDAL_write_data(data)                                        (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_KPADDAL_write_data_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_KPADDAL_get_write_data(data)                                    ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR_SW                                                              0x18007020
#define ISO_UMSK_ISR_SW_reg_addr                                                     "0xB8007020"
#define ISO_UMSK_ISR_SW_reg                                                          0xB8007020
#define set_ISO_UMSK_ISR_SW_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_SW_reg)=data)
#define get_ISO_UMSK_ISR_SW_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_SW_reg))
#define ISO_UMSK_ISR_SW_inst_adr                                                     "0x0008"
#define ISO_UMSK_ISR_SW_inst                                                         0x0008
#define ISO_UMSK_ISR_SW_da_int3_shift                                                (11)
#define ISO_UMSK_ISR_SW_da_int3_mask                                                 (0x00000800)
#define ISO_UMSK_ISR_SW_da_int3(data)                                                (0x00000800&((data)<<11))
#define ISO_UMSK_ISR_SW_da_int3_src(data)                                            ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_SW_get_da_int3(data)                                            ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_SW_da_int2_shift                                                (10)
#define ISO_UMSK_ISR_SW_da_int2_mask                                                 (0x00000400)
#define ISO_UMSK_ISR_SW_da_int2(data)                                                (0x00000400&((data)<<10))
#define ISO_UMSK_ISR_SW_da_int2_src(data)                                            ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_SW_get_da_int2(data)                                            ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_SW_da_int1_shift                                                (9)
#define ISO_UMSK_ISR_SW_da_int1_mask                                                 (0x00000200)
#define ISO_UMSK_ISR_SW_da_int1(data)                                                (0x00000200&((data)<<9))
#define ISO_UMSK_ISR_SW_da_int1_src(data)                                            ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_SW_get_da_int1(data)                                            ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_SW_da_int0_shift                                                (8)
#define ISO_UMSK_ISR_SW_da_int0_mask                                                 (0x00000100)
#define ISO_UMSK_ISR_SW_da_int0(data)                                                (0x00000100&((data)<<8))
#define ISO_UMSK_ISR_SW_da_int0_src(data)                                            ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_SW_get_da_int0(data)                                            ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_SW_a_int3_shift                                                 (7)
#define ISO_UMSK_ISR_SW_a_int3_mask                                                  (0x00000080)
#define ISO_UMSK_ISR_SW_a_int3(data)                                                 (0x00000080&((data)<<7))
#define ISO_UMSK_ISR_SW_a_int3_src(data)                                             ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_SW_get_a_int3(data)                                             ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_SW_a_int2_shift                                                 (6)
#define ISO_UMSK_ISR_SW_a_int2_mask                                                  (0x00000040)
#define ISO_UMSK_ISR_SW_a_int2(data)                                                 (0x00000040&((data)<<6))
#define ISO_UMSK_ISR_SW_a_int2_src(data)                                             ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_SW_get_a_int2(data)                                             ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_SW_a_int1_shift                                                 (5)
#define ISO_UMSK_ISR_SW_a_int1_mask                                                  (0x00000020)
#define ISO_UMSK_ISR_SW_a_int1(data)                                                 (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_SW_a_int1_src(data)                                             ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_SW_get_a_int1(data)                                             ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_SW_a_int0_shift                                                 (4)
#define ISO_UMSK_ISR_SW_a_int0_mask                                                  (0x00000010)
#define ISO_UMSK_ISR_SW_a_int0(data)                                                 (0x00000010&((data)<<4))
#define ISO_UMSK_ISR_SW_a_int0_src(data)                                             ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_SW_get_a_int0(data)                                             ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_SW_write_data_shift                                             (0)
#define ISO_UMSK_ISR_SW_write_data_mask                                              (0x00000001)
#define ISO_UMSK_ISR_SW_write_data(data)                                             (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_SW_write_data_src(data)                                         ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_SW_get_write_data(data)                                         ((0x00000001&(data))>>0)


#define ISO_DBG                                                                      0x18007024
#define ISO_DBG_reg_addr                                                             "0xB8007024"
#define ISO_DBG_reg                                                                  0xB8007024
#define set_ISO_DBG_reg(data)   (*((volatile unsigned int*) ISO_DBG_reg)=data)
#define get_ISO_DBG_reg   (*((volatile unsigned int*) ISO_DBG_reg))
#define ISO_DBG_inst_adr                                                             "0x0009"
#define ISO_DBG_inst                                                                 0x0009
#define ISO_DBG_write_en5_shift                                                      (31)
#define ISO_DBG_write_en5_mask                                                       (0x80000000)
#define ISO_DBG_write_en5(data)                                                      (0x80000000&((data)<<31))
#define ISO_DBG_write_en5_src(data)                                                  ((0x80000000&(data))>>31)
#define ISO_DBG_get_write_en5(data)                                                  ((0x80000000&(data))>>31)
#define ISO_DBG_standby_dbg_sel_shift                                                (24)
#define ISO_DBG_standby_dbg_sel_mask                                                 (0x7F000000)
#define ISO_DBG_standby_dbg_sel(data)                                                (0x7F000000&((data)<<24))
#define ISO_DBG_standby_dbg_sel_src(data)                                            ((0x7F000000&(data))>>24)
#define ISO_DBG_get_standby_dbg_sel(data)                                            ((0x7F000000&(data))>>24)
#define ISO_DBG_write_en4_shift                                                      (23)
#define ISO_DBG_write_en4_mask                                                       (0x00800000)
#define ISO_DBG_write_en4(data)                                                      (0x00800000&((data)<<23))
#define ISO_DBG_write_en4_src(data)                                                  ((0x00800000&(data))>>23)
#define ISO_DBG_get_write_en4(data)                                                  ((0x00800000&(data))>>23)
#define ISO_DBG_standby_dbg_en_shift                                                 (20)
#define ISO_DBG_standby_dbg_en_mask                                                  (0x00100000)
#define ISO_DBG_standby_dbg_en(data)                                                 (0x00100000&((data)<<20))
#define ISO_DBG_standby_dbg_en_src(data)                                             ((0x00100000&(data))>>20)
#define ISO_DBG_get_standby_dbg_en(data)                                             ((0x00100000&(data))>>20)
#define ISO_DBG_write_en3_shift                                                      (19)
#define ISO_DBG_write_en3_mask                                                       (0x00080000)
#define ISO_DBG_write_en3(data)                                                      (0x00080000&((data)<<19))
#define ISO_DBG_write_en3_src(data)                                                  ((0x00080000&(data))>>19)
#define ISO_DBG_get_write_en3(data)                                                  ((0x00080000&(data))>>19)
#define ISO_DBG_sel1_shift                                                           (12)
#define ISO_DBG_sel1_mask                                                            (0x0000F000)
#define ISO_DBG_sel1(data)                                                           (0x0000F000&((data)<<12))
#define ISO_DBG_sel1_src(data)                                                       ((0x0000F000&(data))>>12)
#define ISO_DBG_get_sel1(data)                                                       ((0x0000F000&(data))>>12)
#define ISO_DBG_write_en2_shift                                                      (11)
#define ISO_DBG_write_en2_mask                                                       (0x00000800)
#define ISO_DBG_write_en2(data)                                                      (0x00000800&((data)<<11))
#define ISO_DBG_write_en2_src(data)                                                  ((0x00000800&(data))>>11)
#define ISO_DBG_get_write_en2(data)                                                  ((0x00000800&(data))>>11)
#define ISO_DBG_sel0_shift                                                           (4)
#define ISO_DBG_sel0_mask                                                            (0x000000F0)
#define ISO_DBG_sel0(data)                                                           (0x000000F0&((data)<<4))
#define ISO_DBG_sel0_src(data)                                                       ((0x000000F0&(data))>>4)
#define ISO_DBG_get_sel0(data)                                                       ((0x000000F0&(data))>>4)
#define ISO_DBG_write_en1_shift                                                      (3)
#define ISO_DBG_write_en1_mask                                                       (0x00000008)
#define ISO_DBG_write_en1(data)                                                      (0x00000008&((data)<<3))
#define ISO_DBG_write_en1_src(data)                                                  ((0x00000008&(data))>>3)
#define ISO_DBG_get_write_en1(data)                                                  ((0x00000008&(data))>>3)
#define ISO_DBG_enable_shift                                                         (0)
#define ISO_DBG_enable_mask                                                          (0x00000001)
#define ISO_DBG_enable(data)                                                         (0x00000001&((data)<<0))
#define ISO_DBG_enable_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_DBG_get_enable(data)                                                     ((0x00000001&(data))>>0)


#define ISO_CHIP_INFO1                                                               0x18007028
#define ISO_CHIP_INFO1_reg_addr                                                      "0xB8007028"
#define ISO_CHIP_INFO1_reg                                                           0xB8007028
#define set_ISO_CHIP_INFO1_reg(data)   (*((volatile unsigned int*) ISO_CHIP_INFO1_reg)=data)
#define get_ISO_CHIP_INFO1_reg   (*((volatile unsigned int*) ISO_CHIP_INFO1_reg))
#define ISO_CHIP_INFO1_inst_adr                                                      "0x000A"
#define ISO_CHIP_INFO1_inst                                                          0x000A
#define ISO_CHIP_INFO1_testmode_shift                                                (14)
#define ISO_CHIP_INFO1_testmode_mask                                                 (0x00004000)
#define ISO_CHIP_INFO1_testmode(data)                                                (0x00004000&((data)<<14))
#define ISO_CHIP_INFO1_testmode_src(data)                                            ((0x00004000&(data))>>14)
#define ISO_CHIP_INFO1_get_testmode(data)                                            ((0x00004000&(data))>>14)
#define ISO_CHIP_INFO1_boot_sel_shift                                                (13)
#define ISO_CHIP_INFO1_boot_sel_mask                                                 (0x00002000)
#define ISO_CHIP_INFO1_boot_sel(data)                                                (0x00002000&((data)<<13))
#define ISO_CHIP_INFO1_boot_sel_src(data)                                            ((0x00002000&(data))>>13)
#define ISO_CHIP_INFO1_get_boot_sel(data)                                            ((0x00002000&(data))>>13)
#define ISO_CHIP_INFO1_bound_opt_shift                                               (0)
#define ISO_CHIP_INFO1_bound_opt_mask                                                (0x00001FFF)
#define ISO_CHIP_INFO1_bound_opt(data)                                               (0x00001FFF&((data)<<0))
#define ISO_CHIP_INFO1_bound_opt_src(data)                                           ((0x00001FFF&(data))>>0)
#define ISO_CHIP_INFO1_get_bound_opt(data)                                           ((0x00001FFF&(data))>>0)


#define ISO_CHIP_INFO2                                                               0x1800702C
#define ISO_CHIP_INFO2_reg_addr                                                      "0xB800702C"
#define ISO_CHIP_INFO2_reg                                                           0xB800702C
#define set_ISO_CHIP_INFO2_reg(data)   (*((volatile unsigned int*) ISO_CHIP_INFO2_reg)=data)
#define get_ISO_CHIP_INFO2_reg   (*((volatile unsigned int*) ISO_CHIP_INFO2_reg))
#define ISO_CHIP_INFO2_inst_adr                                                      "0x000B"
#define ISO_CHIP_INFO2_inst                                                          0x000B
#define ISO_CHIP_INFO2_pow_latch_shift                                               (0)
#define ISO_CHIP_INFO2_pow_latch_mask                                                (0x0007FFFF)
#define ISO_CHIP_INFO2_pow_latch(data)                                               (0x0007FFFF&((data)<<0))
#define ISO_CHIP_INFO2_pow_latch_src(data)                                           ((0x0007FFFF&(data))>>0)
#define ISO_CHIP_INFO2_get_pow_latch(data)                                           ((0x0007FFFF&(data))>>0)


#define ISO_CTRL                                                                     0x18007030
#define ISO_CTRL_reg_addr                                                            "0xB8007030"
#define ISO_CTRL_reg                                                                 0xB8007030
#define set_ISO_CTRL_reg(data)   (*((volatile unsigned int*) ISO_CTRL_reg)=data)
#define get_ISO_CTRL_reg   (*((volatile unsigned int*) ISO_CTRL_reg))
#define ISO_CTRL_inst_adr                                                            "0x000C"
#define ISO_CTRL_inst                                                                0x000C
#define ISO_CTRL_write_en9_shift                                                     (17)
#define ISO_CTRL_write_en9_mask                                                      (0x00020000)
#define ISO_CTRL_write_en9(data)                                                     (0x00020000&((data)<<17))
#define ISO_CTRL_write_en9_src(data)                                                 ((0x00020000&(data))>>17)
#define ISO_CTRL_get_write_en9(data)                                                 ((0x00020000&(data))>>17)
#define ISO_CTRL_iso_rst_wd_mask_shift                                               (16)
#define ISO_CTRL_iso_rst_wd_mask_mask                                                (0x00010000)
#define ISO_CTRL_iso_rst_wd_mask(data)                                               (0x00010000&((data)<<16))
#define ISO_CTRL_iso_rst_wd_mask_src(data)                                           ((0x00010000&(data))>>16)
#define ISO_CTRL_get_iso_rst_wd_mask(data)                                           ((0x00010000&(data))>>16)
#define ISO_CTRL_write_en8_shift                                                     (15)
#define ISO_CTRL_write_en8_mask                                                      (0x00008000)
#define ISO_CTRL_write_en8(data)                                                     (0x00008000&((data)<<15))
#define ISO_CTRL_write_en8_src(data)                                                 ((0x00008000&(data))>>15)
#define ISO_CTRL_get_write_en8(data)                                                 ((0x00008000&(data))>>15)
#define ISO_CTRL_dc_phy_cke_pd_shift                                                 (14)
#define ISO_CTRL_dc_phy_cke_pd_mask                                                  (0x00004000)
#define ISO_CTRL_dc_phy_cke_pd(data)                                                 (0x00004000&((data)<<14))
#define ISO_CTRL_dc_phy_cke_pd_src(data)                                             ((0x00004000&(data))>>14)
#define ISO_CTRL_get_dc_phy_cke_pd(data)                                             ((0x00004000&(data))>>14)
#define ISO_CTRL_write_en7_shift                                                     (13)
#define ISO_CTRL_write_en7_mask                                                      (0x00002000)
#define ISO_CTRL_write_en7(data)                                                     (0x00002000&((data)<<13))
#define ISO_CTRL_write_en7_src(data)                                                 ((0x00002000&(data))>>13)
#define ISO_CTRL_get_write_en7(data)                                                 ((0x00002000&(data))>>13)
#define ISO_CTRL_iso_mis_clk_en_shift                                                (12)
#define ISO_CTRL_iso_mis_clk_en_mask                                                 (0x00001000)
#define ISO_CTRL_iso_mis_clk_en(data)                                                (0x00001000&((data)<<12))
#define ISO_CTRL_iso_mis_clk_en_src(data)                                            ((0x00001000&(data))>>12)
#define ISO_CTRL_get_iso_mis_clk_en(data)                                            ((0x00001000&(data))>>12)
#define ISO_CTRL_write_en6_shift                                                     (11)
#define ISO_CTRL_write_en6_mask                                                      (0x00000800)
#define ISO_CTRL_write_en6(data)                                                     (0x00000800&((data)<<11))
#define ISO_CTRL_write_en6_src(data)                                                 ((0x00000800&(data))>>11)
#define ISO_CTRL_get_write_en6(data)                                                 ((0x00000800&(data))>>11)
#define ISO_CTRL_iso_rbus_sel_shift                                                  (10)
#define ISO_CTRL_iso_rbus_sel_mask                                                   (0x00000400)
#define ISO_CTRL_iso_rbus_sel(data)                                                  (0x00000400&((data)<<10))
#define ISO_CTRL_iso_rbus_sel_src(data)                                              ((0x00000400&(data))>>10)
#define ISO_CTRL_get_iso_rbus_sel(data)                                              ((0x00000400&(data))>>10)
#define ISO_CTRL_write_en5_shift                                                     (9)
#define ISO_CTRL_write_en5_mask                                                      (0x00000200)
#define ISO_CTRL_write_en5(data)                                                     (0x00000200&((data)<<9))
#define ISO_CTRL_write_en5_src(data)                                                 ((0x00000200&(data))>>9)
#define ISO_CTRL_get_write_en5(data)                                                 ((0x00000200&(data))>>9)
#define ISO_CTRL_iso_rst_mask_shift                                                  (8)
#define ISO_CTRL_iso_rst_mask_mask                                                   (0x00000100)
#define ISO_CTRL_iso_rst_mask(data)                                                  (0x00000100&((data)<<8))
#define ISO_CTRL_iso_rst_mask_src(data)                                              ((0x00000100&(data))>>8)
#define ISO_CTRL_get_iso_rst_mask(data)                                              ((0x00000100&(data))>>8)
#define ISO_CTRL_write_en4_shift                                                     (7)
#define ISO_CTRL_write_en4_mask                                                      (0x00000080)
#define ISO_CTRL_write_en4(data)                                                     (0x00000080&((data)<<7))
#define ISO_CTRL_write_en4_src(data)                                                 ((0x00000080&(data))>>7)
#define ISO_CTRL_get_write_en4(data)                                                 ((0x00000080&(data))>>7)
#define ISO_CTRL_clk_osc_on_en_shift                                                 (6)
#define ISO_CTRL_clk_osc_on_en_mask                                                  (0x00000040)
#define ISO_CTRL_clk_osc_on_en(data)                                                 (0x00000040&((data)<<6))
#define ISO_CTRL_clk_osc_on_en_src(data)                                             ((0x00000040&(data))>>6)
#define ISO_CTRL_get_clk_osc_on_en(data)                                             ((0x00000040&(data))>>6)
#define ISO_CTRL_write_en3_shift                                                     (5)
#define ISO_CTRL_write_en3_mask                                                      (0x00000020)
#define ISO_CTRL_write_en3(data)                                                     (0x00000020&((data)<<5))
#define ISO_CTRL_write_en3_src(data)                                                 ((0x00000020&(data))>>5)
#define ISO_CTRL_get_write_en3(data)                                                 ((0x00000020&(data))>>5)
#define ISO_CTRL_crt_sw_rstn_shift                                                   (4)
#define ISO_CTRL_crt_sw_rstn_mask                                                    (0x00000010)
#define ISO_CTRL_crt_sw_rstn(data)                                                   (0x00000010&((data)<<4))
#define ISO_CTRL_crt_sw_rstn_src(data)                                               ((0x00000010&(data))>>4)
#define ISO_CTRL_get_crt_sw_rstn(data)                                               ((0x00000010&(data))>>4)
#define ISO_CTRL_write_en2_shift                                                     (3)
#define ISO_CTRL_write_en2_mask                                                      (0x00000008)
#define ISO_CTRL_write_en2(data)                                                     (0x00000008&((data)<<3))
#define ISO_CTRL_write_en2_src(data)                                                 ((0x00000008&(data))>>3)
#define ISO_CTRL_get_write_en2(data)                                                 ((0x00000008&(data))>>3)
#define ISO_CTRL_iso_clk_sel_shift                                                   (2)
#define ISO_CTRL_iso_clk_sel_mask                                                    (0x00000004)
#define ISO_CTRL_iso_clk_sel(data)                                                   (0x00000004&((data)<<2))
#define ISO_CTRL_iso_clk_sel_src(data)                                               ((0x00000004&(data))>>2)
#define ISO_CTRL_get_iso_clk_sel(data)                                               ((0x00000004&(data))>>2)
#define ISO_CTRL_write_en1_shift                                                     (1)
#define ISO_CTRL_write_en1_mask                                                      (0x00000002)
#define ISO_CTRL_write_en1(data)                                                     (0x00000002&((data)<<1))
#define ISO_CTRL_write_en1_src(data)                                                 ((0x00000002&(data))>>1)
#define ISO_CTRL_get_write_en1(data)                                                 ((0x00000002&(data))>>1)
#define ISO_CTRL_ejtag_en_shift                                                      (0)
#define ISO_CTRL_ejtag_en_mask                                                       (0x00000001)
#define ISO_CTRL_ejtag_en(data)                                                      (0x00000001&((data)<<0))
#define ISO_CTRL_ejtag_en_src(data)                                                  ((0x00000001&(data))>>0)
#define ISO_CTRL_get_ejtag_en(data)                                                  ((0x00000001&(data))>>0)


#define ISO_RTC                                                                      0x18007034
#define ISO_RTC_reg_addr                                                             "0xB8007034"
#define ISO_RTC_reg                                                                  0xB8007034
#define set_ISO_RTC_reg(data)   (*((volatile unsigned int*) ISO_RTC_reg)=data)
#define get_ISO_RTC_reg   (*((volatile unsigned int*) ISO_RTC_reg))
#define ISO_RTC_inst_adr                                                             "0x000D"
#define ISO_RTC_inst                                                                 0x000D
#define ISO_RTC_hsec_int_en_shift                                                    (1)
#define ISO_RTC_hsec_int_en_mask                                                     (0x00000002)
#define ISO_RTC_hsec_int_en(data)                                                    (0x00000002&((data)<<1))
#define ISO_RTC_hsec_int_en_src(data)                                                ((0x00000002&(data))>>1)
#define ISO_RTC_get_hsec_int_en(data)                                                ((0x00000002&(data))>>1)
#define ISO_RTC_alarm_int_en_shift                                                   (0)
#define ISO_RTC_alarm_int_en_mask                                                    (0x00000001)
#define ISO_RTC_alarm_int_en(data)                                                   (0x00000001&((data)<<0))
#define ISO_RTC_alarm_int_en_src(data)                                               ((0x00000001&(data))>>0)
#define ISO_RTC_get_alarm_int_en(data)                                               ((0x00000001&(data))>>0)


#define ISO_CELL                                                                     0x18007038
#define ISO_CELL_reg_addr                                                            "0xB8007038"
#define ISO_CELL_reg                                                                 0xB8007038
#define set_ISO_CELL_reg(data)   (*((volatile unsigned int*) ISO_CELL_reg)=data)
#define get_ISO_CELL_reg   (*((volatile unsigned int*) ISO_CELL_reg))
#define ISO_CELL_inst_adr                                                            "0x000E"
#define ISO_CELL_inst                                                                0x000E
#define ISO_CELL_bi_bypass_shift                                                     (2)
#define ISO_CELL_bi_bypass_mask                                                      (0x00000004)
#define ISO_CELL_bi_bypass(data)                                                     (0x00000004&((data)<<2))
#define ISO_CELL_bi_bypass_src(data)                                                 ((0x00000004&(data))>>2)
#define ISO_CELL_get_bi_bypass(data)                                                 ((0x00000004&(data))>>2)
#define ISO_CELL_iso_ctrl_en1_shift                                                  (1)
#define ISO_CELL_iso_ctrl_en1_mask                                                   (0x00000002)
#define ISO_CELL_iso_ctrl_en1(data)                                                  (0x00000002&((data)<<1))
#define ISO_CELL_iso_ctrl_en1_src(data)                                              ((0x00000002&(data))>>1)
#define ISO_CELL_get_iso_ctrl_en1(data)                                              ((0x00000002&(data))>>1)
#define ISO_CELL_iso_ctrl_en0_shift                                                  (0)
#define ISO_CELL_iso_ctrl_en0_mask                                                   (0x00000001)
#define ISO_CELL_iso_ctrl_en0(data)                                                  (0x00000001&((data)<<0))
#define ISO_CELL_iso_ctrl_en0_src(data)                                              ((0x00000001&(data))>>0)
#define ISO_CELL_get_iso_ctrl_en0(data)                                              ((0x00000001&(data))>>0)


#define ISO_POWER                                                                    0x1800703C
#define ISO_POWER_reg_addr                                                           "0xB800703C"
#define ISO_POWER_reg                                                                0xB800703C
#define set_ISO_POWER_reg(data)   (*((volatile unsigned int*) ISO_POWER_reg)=data)
#define get_ISO_POWER_reg   (*((volatile unsigned int*) ISO_POWER_reg))
#define ISO_POWER_inst_adr                                                           "0x000F"
#define ISO_POWER_inst                                                               0x000F
#define ISO_POWER_top_vdd_on_shift                                                   (1)
#define ISO_POWER_top_vdd_on_mask                                                    (0x00000002)
#define ISO_POWER_top_vdd_on(data)                                                   (0x00000002&((data)<<1))
#define ISO_POWER_top_vdd_on_src(data)                                               ((0x00000002&(data))>>1)
#define ISO_POWER_get_top_vdd_on(data)                                               ((0x00000002&(data))>>1)
#define ISO_POWER_scpu_vdd_on_shift                                                  (0)
#define ISO_POWER_scpu_vdd_on_mask                                                   (0x00000001)
#define ISO_POWER_scpu_vdd_on(data)                                                  (0x00000001&((data)<<0))
#define ISO_POWER_scpu_vdd_on_src(data)                                              ((0x00000001&(data))>>0)
#define ISO_POWER_get_scpu_vdd_on(data)                                              ((0x00000001&(data))>>0)


#define ISO_SCPU_INT_EN                                                              0x18007040
#define ISO_SCPU_INT_EN_reg_addr                                                     "0xB8007040"
#define ISO_SCPU_INT_EN_reg                                                          0xB8007040
#define set_ISO_SCPU_INT_EN_reg(data)   (*((volatile unsigned int*) ISO_SCPU_INT_EN_reg)=data)
#define get_ISO_SCPU_INT_EN_reg   (*((volatile unsigned int*) ISO_SCPU_INT_EN_reg))
#define ISO_SCPU_INT_EN_inst_adr                                                     "0x0010"
#define ISO_SCPU_INT_EN_inst                                                         0x0010
#define ISO_SCPU_INT_EN_cec_shift                                                    (22)
#define ISO_SCPU_INT_EN_cec_mask                                                     (0x00400000)
#define ISO_SCPU_INT_EN_cec(data)                                                    (0x00400000&((data)<<22))
#define ISO_SCPU_INT_EN_cec_src(data)                                                ((0x00400000&(data))>>22)
#define ISO_SCPU_INT_EN_get_cec(data)                                                ((0x00400000&(data))>>22)
#define ISO_SCPU_INT_EN_gpioda_shift                                                 (20)
#define ISO_SCPU_INT_EN_gpioda_mask                                                  (0x00100000)
#define ISO_SCPU_INT_EN_gpioda(data)                                                 (0x00100000&((data)<<20))
#define ISO_SCPU_INT_EN_gpioda_src(data)                                             ((0x00100000&(data))>>20)
#define ISO_SCPU_INT_EN_get_gpioda(data)                                             ((0x00100000&(data))>>20)
#define ISO_SCPU_INT_EN_gpioa_shift                                                  (19)
#define ISO_SCPU_INT_EN_gpioa_mask                                                   (0x00080000)
#define ISO_SCPU_INT_EN_gpioa(data)                                                  (0x00080000&((data)<<19))
#define ISO_SCPU_INT_EN_gpioa_src(data)                                              ((0x00080000&(data))>>19)
#define ISO_SCPU_INT_EN_get_gpioa(data)                                              ((0x00080000&(data))>>19)
#define ISO_SCPU_INT_EN_vfd_ardswda_shift                                            (18)
#define ISO_SCPU_INT_EN_vfd_ardswda_mask                                             (0x00040000)
#define ISO_SCPU_INT_EN_vfd_ardswda(data)                                            (0x00040000&((data)<<18))
#define ISO_SCPU_INT_EN_vfd_ardswda_src(data)                                        ((0x00040000&(data))>>18)
#define ISO_SCPU_INT_EN_get_vfd_ardswda(data)                                        ((0x00040000&(data))>>18)
#define ISO_SCPU_INT_EN_vfd_ardswa_shift                                             (17)
#define ISO_SCPU_INT_EN_vfd_ardswa_mask                                              (0x00020000)
#define ISO_SCPU_INT_EN_vfd_ardswa(data)                                             (0x00020000&((data)<<17))
#define ISO_SCPU_INT_EN_vfd_ardswa_src(data)                                         ((0x00020000&(data))>>17)
#define ISO_SCPU_INT_EN_get_vfd_ardswa(data)                                         ((0x00020000&(data))>>17)
#define ISO_SCPU_INT_EN_vfd_ardkpadda_shift                                          (16)
#define ISO_SCPU_INT_EN_vfd_ardkpadda_mask                                           (0x00010000)
#define ISO_SCPU_INT_EN_vfd_ardkpadda(data)                                          (0x00010000&((data)<<16))
#define ISO_SCPU_INT_EN_vfd_ardkpadda_src(data)                                      ((0x00010000&(data))>>16)
#define ISO_SCPU_INT_EN_get_vfd_ardkpadda(data)                                      ((0x00010000&(data))>>16)
#define ISO_SCPU_INT_EN_vfd_ardkpada_shift                                           (15)
#define ISO_SCPU_INT_EN_vfd_ardkpada_mask                                            (0x00008000)
#define ISO_SCPU_INT_EN_vfd_ardkpada(data)                                           (0x00008000&((data)<<15))
#define ISO_SCPU_INT_EN_vfd_ardkpada_src(data)                                       ((0x00008000&(data))>>15)
#define ISO_SCPU_INT_EN_get_vfd_ardkpada(data)                                       ((0x00008000&(data))>>15)
#define ISO_SCPU_INT_EN_vfd_wdone_shift                                              (14)
#define ISO_SCPU_INT_EN_vfd_wdone_mask                                               (0x00004000)
#define ISO_SCPU_INT_EN_vfd_wdone(data)                                              (0x00004000&((data)<<14))
#define ISO_SCPU_INT_EN_vfd_wdone_src(data)                                          ((0x00004000&(data))>>14)
#define ISO_SCPU_INT_EN_get_vfd_wdone(data)                                          ((0x00004000&(data))>>14)
#define ISO_SCPU_INT_EN_rtc_alarm_shift                                              (13)
#define ISO_SCPU_INT_EN_rtc_alarm_mask                                               (0x00002000)
#define ISO_SCPU_INT_EN_rtc_alarm(data)                                              (0x00002000&((data)<<13))
#define ISO_SCPU_INT_EN_rtc_alarm_src(data)                                          ((0x00002000&(data))>>13)
#define ISO_SCPU_INT_EN_get_rtc_alarm(data)                                          ((0x00002000&(data))>>13)
#define ISO_SCPU_INT_EN_rtc_hsec_shift                                               (12)
#define ISO_SCPU_INT_EN_rtc_hsec_mask                                                (0x00001000)
#define ISO_SCPU_INT_EN_rtc_hsec(data)                                               (0x00001000&((data)<<12))
#define ISO_SCPU_INT_EN_rtc_hsec_src(data)                                           ((0x00001000&(data))>>12)
#define ISO_SCPU_INT_EN_get_rtc_hsec(data)                                           ((0x00001000&(data))>>12)
#define ISO_SCPU_INT_EN_i2c6_shift                                                   (10)
#define ISO_SCPU_INT_EN_i2c6_mask                                                    (0x00000400)
#define ISO_SCPU_INT_EN_i2c6(data)                                                   (0x00000400&((data)<<10))
#define ISO_SCPU_INT_EN_i2c6_src(data)                                               ((0x00000400&(data))>>10)
#define ISO_SCPU_INT_EN_get_i2c6(data)                                               ((0x00000400&(data))>>10)
#define ISO_SCPU_INT_EN_i2c0_shift                                                   (8)
#define ISO_SCPU_INT_EN_i2c0_mask                                                    (0x00000100)
#define ISO_SCPU_INT_EN_i2c0(data)                                                   (0x00000100&((data)<<8))
#define ISO_SCPU_INT_EN_i2c0_src(data)                                               ((0x00000100&(data))>>8)
#define ISO_SCPU_INT_EN_get_i2c0(data)                                               ((0x00000100&(data))>>8)
#define ISO_SCPU_INT_EN_irda_shift                                                   (5)
#define ISO_SCPU_INT_EN_irda_mask                                                    (0x00000020)
#define ISO_SCPU_INT_EN_irda(data)                                                   (0x00000020&((data)<<5))
#define ISO_SCPU_INT_EN_irda_src(data)                                               ((0x00000020&(data))>>5)
#define ISO_SCPU_INT_EN_get_irda(data)                                               ((0x00000020&(data))>>5)
#define ISO_SCPU_INT_EN_ur0_shift                                                    (2)
#define ISO_SCPU_INT_EN_ur0_mask                                                     (0x00000004)
#define ISO_SCPU_INT_EN_ur0(data)                                                    (0x00000004&((data)<<2))
#define ISO_SCPU_INT_EN_ur0_src(data)                                                ((0x00000004&(data))>>2)
#define ISO_SCPU_INT_EN_get_ur0(data)                                                ((0x00000004&(data))>>2)


#define ISO_USB                                                                      0x18007044
#define ISO_USB_reg_addr                                                             "0xB8007044"
#define ISO_USB_reg                                                                  0xB8007044
#define set_ISO_USB_reg(data)   (*((volatile unsigned int*) ISO_USB_reg)=data)
#define get_ISO_USB_reg   (*((volatile unsigned int*) ISO_USB_reg))
#define ISO_USB_inst_adr                                                             "0x0011"
#define ISO_USB_inst                                                                 0x0011
#define ISO_USB_dcp_ctrl1_shift                                                      (1)
#define ISO_USB_dcp_ctrl1_mask                                                       (0x00000002)
#define ISO_USB_dcp_ctrl1(data)                                                      (0x00000002&((data)<<1))
#define ISO_USB_dcp_ctrl1_src(data)                                                  ((0x00000002&(data))>>1)
#define ISO_USB_get_dcp_ctrl1(data)                                                  ((0x00000002&(data))>>1)
#define ISO_USB_dcp_ctrl0_shift                                                      (0)
#define ISO_USB_dcp_ctrl0_mask                                                       (0x00000001)
#define ISO_USB_dcp_ctrl0(data)                                                      (0x00000001&((data)<<0))
#define ISO_USB_dcp_ctrl0_src(data)                                                  ((0x00000001&(data))>>0)
#define ISO_USB_get_dcp_ctrl0(data)                                                  ((0x00000001&(data))>>0)


#define ISO_ACPU_INT_EN                                                              0x18007048
#define ISO_ACPU_INT_EN_reg_addr                                                     "0xB8007048"
#define ISO_ACPU_INT_EN_reg                                                          0xB8007048
#define set_ISO_ACPU_INT_EN_reg(data)   (*((volatile unsigned int*) ISO_ACPU_INT_EN_reg)=data)
#define get_ISO_ACPU_INT_EN_reg   (*((volatile unsigned int*) ISO_ACPU_INT_EN_reg))
#define ISO_ACPU_INT_EN_inst_adr                                                     "0x0012"
#define ISO_ACPU_INT_EN_inst                                                         0x0012
#define ISO_ACPU_INT_EN_cec_shift                                                    (22)
#define ISO_ACPU_INT_EN_cec_mask                                                     (0x00400000)
#define ISO_ACPU_INT_EN_cec(data)                                                    (0x00400000&((data)<<22))
#define ISO_ACPU_INT_EN_cec_src(data)                                                ((0x00400000&(data))>>22)
#define ISO_ACPU_INT_EN_get_cec(data)                                                ((0x00400000&(data))>>22)
#define ISO_ACPU_INT_EN_gpioda_shift                                                 (20)
#define ISO_ACPU_INT_EN_gpioda_mask                                                  (0x00100000)
#define ISO_ACPU_INT_EN_gpioda(data)                                                 (0x00100000&((data)<<20))
#define ISO_ACPU_INT_EN_gpioda_src(data)                                             ((0x00100000&(data))>>20)
#define ISO_ACPU_INT_EN_get_gpioda(data)                                             ((0x00100000&(data))>>20)
#define ISO_ACPU_INT_EN_gpioa_shift                                                  (19)
#define ISO_ACPU_INT_EN_gpioa_mask                                                   (0x00080000)
#define ISO_ACPU_INT_EN_gpioa(data)                                                  (0x00080000&((data)<<19))
#define ISO_ACPU_INT_EN_gpioa_src(data)                                              ((0x00080000&(data))>>19)
#define ISO_ACPU_INT_EN_get_gpioa(data)                                              ((0x00080000&(data))>>19)
#define ISO_ACPU_INT_EN_vfd_ardswda_shift                                            (18)
#define ISO_ACPU_INT_EN_vfd_ardswda_mask                                             (0x00040000)
#define ISO_ACPU_INT_EN_vfd_ardswda(data)                                            (0x00040000&((data)<<18))
#define ISO_ACPU_INT_EN_vfd_ardswda_src(data)                                        ((0x00040000&(data))>>18)
#define ISO_ACPU_INT_EN_get_vfd_ardswda(data)                                        ((0x00040000&(data))>>18)
#define ISO_ACPU_INT_EN_vfd_ardswa_shift                                             (17)
#define ISO_ACPU_INT_EN_vfd_ardswa_mask                                              (0x00020000)
#define ISO_ACPU_INT_EN_vfd_ardswa(data)                                             (0x00020000&((data)<<17))
#define ISO_ACPU_INT_EN_vfd_ardswa_src(data)                                         ((0x00020000&(data))>>17)
#define ISO_ACPU_INT_EN_get_vfd_ardswa(data)                                         ((0x00020000&(data))>>17)
#define ISO_ACPU_INT_EN_vfd_ardkpadda_shift                                          (16)
#define ISO_ACPU_INT_EN_vfd_ardkpadda_mask                                           (0x00010000)
#define ISO_ACPU_INT_EN_vfd_ardkpadda(data)                                          (0x00010000&((data)<<16))
#define ISO_ACPU_INT_EN_vfd_ardkpadda_src(data)                                      ((0x00010000&(data))>>16)
#define ISO_ACPU_INT_EN_get_vfd_ardkpadda(data)                                      ((0x00010000&(data))>>16)
#define ISO_ACPU_INT_EN_vfd_ardkpada_shift                                           (15)
#define ISO_ACPU_INT_EN_vfd_ardkpada_mask                                            (0x00008000)
#define ISO_ACPU_INT_EN_vfd_ardkpada(data)                                           (0x00008000&((data)<<15))
#define ISO_ACPU_INT_EN_vfd_ardkpada_src(data)                                       ((0x00008000&(data))>>15)
#define ISO_ACPU_INT_EN_get_vfd_ardkpada(data)                                       ((0x00008000&(data))>>15)
#define ISO_ACPU_INT_EN_vfd_wdone_shift                                              (14)
#define ISO_ACPU_INT_EN_vfd_wdone_mask                                               (0x00004000)
#define ISO_ACPU_INT_EN_vfd_wdone(data)                                              (0x00004000&((data)<<14))
#define ISO_ACPU_INT_EN_vfd_wdone_src(data)                                          ((0x00004000&(data))>>14)
#define ISO_ACPU_INT_EN_get_vfd_wdone(data)                                          ((0x00004000&(data))>>14)
#define ISO_ACPU_INT_EN_rtc_alarm_shift                                              (13)
#define ISO_ACPU_INT_EN_rtc_alarm_mask                                               (0x00002000)
#define ISO_ACPU_INT_EN_rtc_alarm(data)                                              (0x00002000&((data)<<13))
#define ISO_ACPU_INT_EN_rtc_alarm_src(data)                                          ((0x00002000&(data))>>13)
#define ISO_ACPU_INT_EN_get_rtc_alarm(data)                                          ((0x00002000&(data))>>13)
#define ISO_ACPU_INT_EN_rtc_hsec_shift                                               (12)
#define ISO_ACPU_INT_EN_rtc_hsec_mask                                                (0x00001000)
#define ISO_ACPU_INT_EN_rtc_hsec(data)                                               (0x00001000&((data)<<12))
#define ISO_ACPU_INT_EN_rtc_hsec_src(data)                                           ((0x00001000&(data))>>12)
#define ISO_ACPU_INT_EN_get_rtc_hsec(data)                                           ((0x00001000&(data))>>12)
#define ISO_ACPU_INT_EN_i2c6_shift                                                   (10)
#define ISO_ACPU_INT_EN_i2c6_mask                                                    (0x00000400)
#define ISO_ACPU_INT_EN_i2c6(data)                                                   (0x00000400&((data)<<10))
#define ISO_ACPU_INT_EN_i2c6_src(data)                                               ((0x00000400&(data))>>10)
#define ISO_ACPU_INT_EN_get_i2c6(data)                                               ((0x00000400&(data))>>10)
#define ISO_ACPU_INT_EN_i2c0_shift                                                   (8)
#define ISO_ACPU_INT_EN_i2c0_mask                                                    (0x00000100)
#define ISO_ACPU_INT_EN_i2c0(data)                                                   (0x00000100&((data)<<8))
#define ISO_ACPU_INT_EN_i2c0_src(data)                                               ((0x00000100&(data))>>8)
#define ISO_ACPU_INT_EN_get_i2c0(data)                                               ((0x00000100&(data))>>8)
#define ISO_ACPU_INT_EN_irda_shift                                                   (5)
#define ISO_ACPU_INT_EN_irda_mask                                                    (0x00000020)
#define ISO_ACPU_INT_EN_irda(data)                                                   (0x00000020&((data)<<5))
#define ISO_ACPU_INT_EN_irda_src(data)                                               ((0x00000020&(data))>>5)
#define ISO_ACPU_INT_EN_get_irda(data)                                               ((0x00000020&(data))>>5)
#define ISO_ACPU_INT_EN_ur0_shift                                                    (2)
#define ISO_ACPU_INT_EN_ur0_mask                                                     (0x00000004)
#define ISO_ACPU_INT_EN_ur0(data)                                                    (0x00000004&((data)<<2))
#define ISO_ACPU_INT_EN_ur0_src(data)                                                ((0x00000004&(data))>>2)
#define ISO_ACPU_INT_EN_get_ur0(data)                                                ((0x00000004&(data))>>2)


#define ISO_CPU_ST1                                                                  0x1800704C
#define ISO_CPU_ST1_reg_addr                                                         "0xB800704C"
#define ISO_CPU_ST1_reg                                                              0xB800704C
#define set_ISO_CPU_ST1_reg(data)   (*((volatile unsigned int*) ISO_CPU_ST1_reg)=data)
#define get_ISO_CPU_ST1_reg   (*((volatile unsigned int*) ISO_CPU_ST1_reg))
#define ISO_CPU_ST1_inst_adr                                                         "0x0013"
#define ISO_CPU_ST1_inst                                                             0x0013
#define ISO_CPU_ST1_acpu_boot_info_shift                                             (0)
#define ISO_CPU_ST1_acpu_boot_info_mask                                              (0xFFFFFFFF)
#define ISO_CPU_ST1_acpu_boot_info(data)                                             (0xFFFFFFFF&((data)<<0))
#define ISO_CPU_ST1_acpu_boot_info_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define ISO_CPU_ST1_get_acpu_boot_info(data)                                         ((0xFFFFFFFF&(data))>>0)


#define ISO_CPU_ST1V                                                                 0x18007050
#define ISO_CPU_ST1V_reg_addr                                                        "0xB8007050"
#define ISO_CPU_ST1V_reg                                                             0xB8007050
#define set_ISO_CPU_ST1V_reg(data)   (*((volatile unsigned int*) ISO_CPU_ST1V_reg)=data)
#define get_ISO_CPU_ST1V_reg   (*((volatile unsigned int*) ISO_CPU_ST1V_reg))
#define ISO_CPU_ST1V_inst_adr                                                        "0x0014"
#define ISO_CPU_ST1V_inst                                                            0x0014
#define ISO_CPU_ST1V_acpu_boot_info_valid_shift                                      (0)
#define ISO_CPU_ST1V_acpu_boot_info_valid_mask                                       (0x00000001)
#define ISO_CPU_ST1V_acpu_boot_info_valid(data)                                      (0x00000001&((data)<<0))
#define ISO_CPU_ST1V_acpu_boot_info_valid_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_CPU_ST1V_get_acpu_boot_info_valid(data)                                  ((0x00000001&(data))>>0)


#define ISO_DUMMY1                                                                   0x18007054
#define ISO_DUMMY1_reg_addr                                                          "0xB8007054"
#define ISO_DUMMY1_reg                                                               0xB8007054
#define set_ISO_DUMMY1_reg(data)   (*((volatile unsigned int*) ISO_DUMMY1_reg)=data)
#define get_ISO_DUMMY1_reg   (*((volatile unsigned int*) ISO_DUMMY1_reg))
#define ISO_DUMMY1_inst_adr                                                          "0x0015"
#define ISO_DUMMY1_inst                                                              0x0015
#define ISO_DUMMY1_rvd31_shift                                                       (31)
#define ISO_DUMMY1_rvd31_mask                                                        (0x80000000)
#define ISO_DUMMY1_rvd31(data)                                                       (0x80000000&((data)<<31))
#define ISO_DUMMY1_rvd31_src(data)                                                   ((0x80000000&(data))>>31)
#define ISO_DUMMY1_get_rvd31(data)                                                   ((0x80000000&(data))>>31)
#define ISO_DUMMY1_rvd30_shift                                                       (30)
#define ISO_DUMMY1_rvd30_mask                                                        (0x40000000)
#define ISO_DUMMY1_rvd30(data)                                                       (0x40000000&((data)<<30))
#define ISO_DUMMY1_rvd30_src(data)                                                   ((0x40000000&(data))>>30)
#define ISO_DUMMY1_get_rvd30(data)                                                   ((0x40000000&(data))>>30)
#define ISO_DUMMY1_rvd29_shift                                                       (29)
#define ISO_DUMMY1_rvd29_mask                                                        (0x20000000)
#define ISO_DUMMY1_rvd29(data)                                                       (0x20000000&((data)<<29))
#define ISO_DUMMY1_rvd29_src(data)                                                   ((0x20000000&(data))>>29)
#define ISO_DUMMY1_get_rvd29(data)                                                   ((0x20000000&(data))>>29)
#define ISO_DUMMY1_rvd28_shift                                                       (28)
#define ISO_DUMMY1_rvd28_mask                                                        (0x10000000)
#define ISO_DUMMY1_rvd28(data)                                                       (0x10000000&((data)<<28))
#define ISO_DUMMY1_rvd28_src(data)                                                   ((0x10000000&(data))>>28)
#define ISO_DUMMY1_get_rvd28(data)                                                   ((0x10000000&(data))>>28)
#define ISO_DUMMY1_rvd27_shift                                                       (27)
#define ISO_DUMMY1_rvd27_mask                                                        (0x08000000)
#define ISO_DUMMY1_rvd27(data)                                                       (0x08000000&((data)<<27))
#define ISO_DUMMY1_rvd27_src(data)                                                   ((0x08000000&(data))>>27)
#define ISO_DUMMY1_get_rvd27(data)                                                   ((0x08000000&(data))>>27)
#define ISO_DUMMY1_rvd26_shift                                                       (26)
#define ISO_DUMMY1_rvd26_mask                                                        (0x04000000)
#define ISO_DUMMY1_rvd26(data)                                                       (0x04000000&((data)<<26))
#define ISO_DUMMY1_rvd26_src(data)                                                   ((0x04000000&(data))>>26)
#define ISO_DUMMY1_get_rvd26(data)                                                   ((0x04000000&(data))>>26)
#define ISO_DUMMY1_rvd25_shift                                                       (25)
#define ISO_DUMMY1_rvd25_mask                                                        (0x02000000)
#define ISO_DUMMY1_rvd25(data)                                                       (0x02000000&((data)<<25))
#define ISO_DUMMY1_rvd25_src(data)                                                   ((0x02000000&(data))>>25)
#define ISO_DUMMY1_get_rvd25(data)                                                   ((0x02000000&(data))>>25)
#define ISO_DUMMY1_rvd24_shift                                                       (24)
#define ISO_DUMMY1_rvd24_mask                                                        (0x01000000)
#define ISO_DUMMY1_rvd24(data)                                                       (0x01000000&((data)<<24))
#define ISO_DUMMY1_rvd24_src(data)                                                   ((0x01000000&(data))>>24)
#define ISO_DUMMY1_get_rvd24(data)                                                   ((0x01000000&(data))>>24)
#define ISO_DUMMY1_rvd23_shift                                                       (23)
#define ISO_DUMMY1_rvd23_mask                                                        (0x00800000)
#define ISO_DUMMY1_rvd23(data)                                                       (0x00800000&((data)<<23))
#define ISO_DUMMY1_rvd23_src(data)                                                   ((0x00800000&(data))>>23)
#define ISO_DUMMY1_get_rvd23(data)                                                   ((0x00800000&(data))>>23)
#define ISO_DUMMY1_rvd22_shift                                                       (22)
#define ISO_DUMMY1_rvd22_mask                                                        (0x00400000)
#define ISO_DUMMY1_rvd22(data)                                                       (0x00400000&((data)<<22))
#define ISO_DUMMY1_rvd22_src(data)                                                   ((0x00400000&(data))>>22)
#define ISO_DUMMY1_get_rvd22(data)                                                   ((0x00400000&(data))>>22)
#define ISO_DUMMY1_rvd21_shift                                                       (21)
#define ISO_DUMMY1_rvd21_mask                                                        (0x00200000)
#define ISO_DUMMY1_rvd21(data)                                                       (0x00200000&((data)<<21))
#define ISO_DUMMY1_rvd21_src(data)                                                   ((0x00200000&(data))>>21)
#define ISO_DUMMY1_get_rvd21(data)                                                   ((0x00200000&(data))>>21)
#define ISO_DUMMY1_rvd20_shift                                                       (20)
#define ISO_DUMMY1_rvd20_mask                                                        (0x00100000)
#define ISO_DUMMY1_rvd20(data)                                                       (0x00100000&((data)<<20))
#define ISO_DUMMY1_rvd20_src(data)                                                   ((0x00100000&(data))>>20)
#define ISO_DUMMY1_get_rvd20(data)                                                   ((0x00100000&(data))>>20)
#define ISO_DUMMY1_rvd19_shift                                                       (19)
#define ISO_DUMMY1_rvd19_mask                                                        (0x00080000)
#define ISO_DUMMY1_rvd19(data)                                                       (0x00080000&((data)<<19))
#define ISO_DUMMY1_rvd19_src(data)                                                   ((0x00080000&(data))>>19)
#define ISO_DUMMY1_get_rvd19(data)                                                   ((0x00080000&(data))>>19)
#define ISO_DUMMY1_rvd18_shift                                                       (18)
#define ISO_DUMMY1_rvd18_mask                                                        (0x00040000)
#define ISO_DUMMY1_rvd18(data)                                                       (0x00040000&((data)<<18))
#define ISO_DUMMY1_rvd18_src(data)                                                   ((0x00040000&(data))>>18)
#define ISO_DUMMY1_get_rvd18(data)                                                   ((0x00040000&(data))>>18)
#define ISO_DUMMY1_rvd17_shift                                                       (17)
#define ISO_DUMMY1_rvd17_mask                                                        (0x00020000)
#define ISO_DUMMY1_rvd17(data)                                                       (0x00020000&((data)<<17))
#define ISO_DUMMY1_rvd17_src(data)                                                   ((0x00020000&(data))>>17)
#define ISO_DUMMY1_get_rvd17(data)                                                   ((0x00020000&(data))>>17)
#define ISO_DUMMY1_rvd16_shift                                                       (16)
#define ISO_DUMMY1_rvd16_mask                                                        (0x00010000)
#define ISO_DUMMY1_rvd16(data)                                                       (0x00010000&((data)<<16))
#define ISO_DUMMY1_rvd16_src(data)                                                   ((0x00010000&(data))>>16)
#define ISO_DUMMY1_get_rvd16(data)                                                   ((0x00010000&(data))>>16)
#define ISO_DUMMY1_rvd15_shift                                                       (15)
#define ISO_DUMMY1_rvd15_mask                                                        (0x00008000)
#define ISO_DUMMY1_rvd15(data)                                                       (0x00008000&((data)<<15))
#define ISO_DUMMY1_rvd15_src(data)                                                   ((0x00008000&(data))>>15)
#define ISO_DUMMY1_get_rvd15(data)                                                   ((0x00008000&(data))>>15)
#define ISO_DUMMY1_rvd14_shift                                                       (14)
#define ISO_DUMMY1_rvd14_mask                                                        (0x00004000)
#define ISO_DUMMY1_rvd14(data)                                                       (0x00004000&((data)<<14))
#define ISO_DUMMY1_rvd14_src(data)                                                   ((0x00004000&(data))>>14)
#define ISO_DUMMY1_get_rvd14(data)                                                   ((0x00004000&(data))>>14)
#define ISO_DUMMY1_rvd13_shift                                                       (13)
#define ISO_DUMMY1_rvd13_mask                                                        (0x00002000)
#define ISO_DUMMY1_rvd13(data)                                                       (0x00002000&((data)<<13))
#define ISO_DUMMY1_rvd13_src(data)                                                   ((0x00002000&(data))>>13)
#define ISO_DUMMY1_get_rvd13(data)                                                   ((0x00002000&(data))>>13)
#define ISO_DUMMY1_rvd12_shift                                                       (12)
#define ISO_DUMMY1_rvd12_mask                                                        (0x00001000)
#define ISO_DUMMY1_rvd12(data)                                                       (0x00001000&((data)<<12))
#define ISO_DUMMY1_rvd12_src(data)                                                   ((0x00001000&(data))>>12)
#define ISO_DUMMY1_get_rvd12(data)                                                   ((0x00001000&(data))>>12)
#define ISO_DUMMY1_rvd11_shift                                                       (11)
#define ISO_DUMMY1_rvd11_mask                                                        (0x00000800)
#define ISO_DUMMY1_rvd11(data)                                                       (0x00000800&((data)<<11))
#define ISO_DUMMY1_rvd11_src(data)                                                   ((0x00000800&(data))>>11)
#define ISO_DUMMY1_get_rvd11(data)                                                   ((0x00000800&(data))>>11)
#define ISO_DUMMY1_rvd10_shift                                                       (10)
#define ISO_DUMMY1_rvd10_mask                                                        (0x00000400)
#define ISO_DUMMY1_rvd10(data)                                                       (0x00000400&((data)<<10))
#define ISO_DUMMY1_rvd10_src(data)                                                   ((0x00000400&(data))>>10)
#define ISO_DUMMY1_get_rvd10(data)                                                   ((0x00000400&(data))>>10)
#define ISO_DUMMY1_rvd9_shift                                                        (9)
#define ISO_DUMMY1_rvd9_mask                                                         (0x00000200)
#define ISO_DUMMY1_rvd9(data)                                                        (0x00000200&((data)<<9))
#define ISO_DUMMY1_rvd9_src(data)                                                    ((0x00000200&(data))>>9)
#define ISO_DUMMY1_get_rvd9(data)                                                    ((0x00000200&(data))>>9)
#define ISO_DUMMY1_rvd8_shift                                                        (8)
#define ISO_DUMMY1_rvd8_mask                                                         (0x00000100)
#define ISO_DUMMY1_rvd8(data)                                                        (0x00000100&((data)<<8))
#define ISO_DUMMY1_rvd8_src(data)                                                    ((0x00000100&(data))>>8)
#define ISO_DUMMY1_get_rvd8(data)                                                    ((0x00000100&(data))>>8)
#define ISO_DUMMY1_rvd7_shift                                                        (7)
#define ISO_DUMMY1_rvd7_mask                                                         (0x00000080)
#define ISO_DUMMY1_rvd7(data)                                                        (0x00000080&((data)<<7))
#define ISO_DUMMY1_rvd7_src(data)                                                    ((0x00000080&(data))>>7)
#define ISO_DUMMY1_get_rvd7(data)                                                    ((0x00000080&(data))>>7)
#define ISO_DUMMY1_rvd6_shift                                                        (6)
#define ISO_DUMMY1_rvd6_mask                                                         (0x00000040)
#define ISO_DUMMY1_rvd6(data)                                                        (0x00000040&((data)<<6))
#define ISO_DUMMY1_rvd6_src(data)                                                    ((0x00000040&(data))>>6)
#define ISO_DUMMY1_get_rvd6(data)                                                    ((0x00000040&(data))>>6)
#define ISO_DUMMY1_rvd5_shift                                                        (5)
#define ISO_DUMMY1_rvd5_mask                                                         (0x00000020)
#define ISO_DUMMY1_rvd5(data)                                                        (0x00000020&((data)<<5))
#define ISO_DUMMY1_rvd5_src(data)                                                    ((0x00000020&(data))>>5)
#define ISO_DUMMY1_get_rvd5(data)                                                    ((0x00000020&(data))>>5)
#define ISO_DUMMY1_rvd4_shift                                                        (4)
#define ISO_DUMMY1_rvd4_mask                                                         (0x00000010)
#define ISO_DUMMY1_rvd4(data)                                                        (0x00000010&((data)<<4))
#define ISO_DUMMY1_rvd4_src(data)                                                    ((0x00000010&(data))>>4)
#define ISO_DUMMY1_get_rvd4(data)                                                    ((0x00000010&(data))>>4)
#define ISO_DUMMY1_rvd3_shift                                                        (3)
#define ISO_DUMMY1_rvd3_mask                                                         (0x00000008)
#define ISO_DUMMY1_rvd3(data)                                                        (0x00000008&((data)<<3))
#define ISO_DUMMY1_rvd3_src(data)                                                    ((0x00000008&(data))>>3)
#define ISO_DUMMY1_get_rvd3(data)                                                    ((0x00000008&(data))>>3)
#define ISO_DUMMY1_rvd2_shift                                                        (2)
#define ISO_DUMMY1_rvd2_mask                                                         (0x00000004)
#define ISO_DUMMY1_rvd2(data)                                                        (0x00000004&((data)<<2))
#define ISO_DUMMY1_rvd2_src(data)                                                    ((0x00000004&(data))>>2)
#define ISO_DUMMY1_get_rvd2(data)                                                    ((0x00000004&(data))>>2)
#define ISO_DUMMY1_rvd1_shift                                                        (1)
#define ISO_DUMMY1_rvd1_mask                                                         (0x00000002)
#define ISO_DUMMY1_rvd1(data)                                                        (0x00000002&((data)<<1))
#define ISO_DUMMY1_rvd1_src(data)                                                    ((0x00000002&(data))>>1)
#define ISO_DUMMY1_get_rvd1(data)                                                    ((0x00000002&(data))>>1)
#define ISO_DUMMY1_rvd0_shift                                                        (0)
#define ISO_DUMMY1_rvd0_mask                                                         (0x00000001)
#define ISO_DUMMY1_rvd0(data)                                                        (0x00000001&((data)<<0))
#define ISO_DUMMY1_rvd0_src(data)                                                    ((0x00000001&(data))>>0)
#define ISO_DUMMY1_get_rvd0(data)                                                    ((0x00000001&(data))>>0)


#define ISO_DUMMY2                                                                   0x18007058
#define ISO_DUMMY2_reg_addr                                                          "0xB8007058"
#define ISO_DUMMY2_reg                                                               0xB8007058
#define set_ISO_DUMMY2_reg(data)   (*((volatile unsigned int*) ISO_DUMMY2_reg)=data)
#define get_ISO_DUMMY2_reg   (*((volatile unsigned int*) ISO_DUMMY2_reg))
#define ISO_DUMMY2_inst_adr                                                          "0x0016"
#define ISO_DUMMY2_inst                                                              0x0016
#define ISO_DUMMY2_rvd31_shift                                                       (31)
#define ISO_DUMMY2_rvd31_mask                                                        (0x80000000)
#define ISO_DUMMY2_rvd31(data)                                                       (0x80000000&((data)<<31))
#define ISO_DUMMY2_rvd31_src(data)                                                   ((0x80000000&(data))>>31)
#define ISO_DUMMY2_get_rvd31(data)                                                   ((0x80000000&(data))>>31)
#define ISO_DUMMY2_rvd30_shift                                                       (30)
#define ISO_DUMMY2_rvd30_mask                                                        (0x40000000)
#define ISO_DUMMY2_rvd30(data)                                                       (0x40000000&((data)<<30))
#define ISO_DUMMY2_rvd30_src(data)                                                   ((0x40000000&(data))>>30)
#define ISO_DUMMY2_get_rvd30(data)                                                   ((0x40000000&(data))>>30)
#define ISO_DUMMY2_rvd29_shift                                                       (29)
#define ISO_DUMMY2_rvd29_mask                                                        (0x20000000)
#define ISO_DUMMY2_rvd29(data)                                                       (0x20000000&((data)<<29))
#define ISO_DUMMY2_rvd29_src(data)                                                   ((0x20000000&(data))>>29)
#define ISO_DUMMY2_get_rvd29(data)                                                   ((0x20000000&(data))>>29)
#define ISO_DUMMY2_rvd28_shift                                                       (28)
#define ISO_DUMMY2_rvd28_mask                                                        (0x10000000)
#define ISO_DUMMY2_rvd28(data)                                                       (0x10000000&((data)<<28))
#define ISO_DUMMY2_rvd28_src(data)                                                   ((0x10000000&(data))>>28)
#define ISO_DUMMY2_get_rvd28(data)                                                   ((0x10000000&(data))>>28)
#define ISO_DUMMY2_rvd27_shift                                                       (27)
#define ISO_DUMMY2_rvd27_mask                                                        (0x08000000)
#define ISO_DUMMY2_rvd27(data)                                                       (0x08000000&((data)<<27))
#define ISO_DUMMY2_rvd27_src(data)                                                   ((0x08000000&(data))>>27)
#define ISO_DUMMY2_get_rvd27(data)                                                   ((0x08000000&(data))>>27)
#define ISO_DUMMY2_rvd26_shift                                                       (26)
#define ISO_DUMMY2_rvd26_mask                                                        (0x04000000)
#define ISO_DUMMY2_rvd26(data)                                                       (0x04000000&((data)<<26))
#define ISO_DUMMY2_rvd26_src(data)                                                   ((0x04000000&(data))>>26)
#define ISO_DUMMY2_get_rvd26(data)                                                   ((0x04000000&(data))>>26)
#define ISO_DUMMY2_rvd25_shift                                                       (25)
#define ISO_DUMMY2_rvd25_mask                                                        (0x02000000)
#define ISO_DUMMY2_rvd25(data)                                                       (0x02000000&((data)<<25))
#define ISO_DUMMY2_rvd25_src(data)                                                   ((0x02000000&(data))>>25)
#define ISO_DUMMY2_get_rvd25(data)                                                   ((0x02000000&(data))>>25)
#define ISO_DUMMY2_rvd24_shift                                                       (24)
#define ISO_DUMMY2_rvd24_mask                                                        (0x01000000)
#define ISO_DUMMY2_rvd24(data)                                                       (0x01000000&((data)<<24))
#define ISO_DUMMY2_rvd24_src(data)                                                   ((0x01000000&(data))>>24)
#define ISO_DUMMY2_get_rvd24(data)                                                   ((0x01000000&(data))>>24)
#define ISO_DUMMY2_rvd23_shift                                                       (23)
#define ISO_DUMMY2_rvd23_mask                                                        (0x00800000)
#define ISO_DUMMY2_rvd23(data)                                                       (0x00800000&((data)<<23))
#define ISO_DUMMY2_rvd23_src(data)                                                   ((0x00800000&(data))>>23)
#define ISO_DUMMY2_get_rvd23(data)                                                   ((0x00800000&(data))>>23)
#define ISO_DUMMY2_rvd22_shift                                                       (22)
#define ISO_DUMMY2_rvd22_mask                                                        (0x00400000)
#define ISO_DUMMY2_rvd22(data)                                                       (0x00400000&((data)<<22))
#define ISO_DUMMY2_rvd22_src(data)                                                   ((0x00400000&(data))>>22)
#define ISO_DUMMY2_get_rvd22(data)                                                   ((0x00400000&(data))>>22)
#define ISO_DUMMY2_rvd21_shift                                                       (21)
#define ISO_DUMMY2_rvd21_mask                                                        (0x00200000)
#define ISO_DUMMY2_rvd21(data)                                                       (0x00200000&((data)<<21))
#define ISO_DUMMY2_rvd21_src(data)                                                   ((0x00200000&(data))>>21)
#define ISO_DUMMY2_get_rvd21(data)                                                   ((0x00200000&(data))>>21)
#define ISO_DUMMY2_rvd20_shift                                                       (20)
#define ISO_DUMMY2_rvd20_mask                                                        (0x00100000)
#define ISO_DUMMY2_rvd20(data)                                                       (0x00100000&((data)<<20))
#define ISO_DUMMY2_rvd20_src(data)                                                   ((0x00100000&(data))>>20)
#define ISO_DUMMY2_get_rvd20(data)                                                   ((0x00100000&(data))>>20)
#define ISO_DUMMY2_rvd19_shift                                                       (19)
#define ISO_DUMMY2_rvd19_mask                                                        (0x00080000)
#define ISO_DUMMY2_rvd19(data)                                                       (0x00080000&((data)<<19))
#define ISO_DUMMY2_rvd19_src(data)                                                   ((0x00080000&(data))>>19)
#define ISO_DUMMY2_get_rvd19(data)                                                   ((0x00080000&(data))>>19)
#define ISO_DUMMY2_rvd18_shift                                                       (18)
#define ISO_DUMMY2_rvd18_mask                                                        (0x00040000)
#define ISO_DUMMY2_rvd18(data)                                                       (0x00040000&((data)<<18))
#define ISO_DUMMY2_rvd18_src(data)                                                   ((0x00040000&(data))>>18)
#define ISO_DUMMY2_get_rvd18(data)                                                   ((0x00040000&(data))>>18)
#define ISO_DUMMY2_rvd17_shift                                                       (17)
#define ISO_DUMMY2_rvd17_mask                                                        (0x00020000)
#define ISO_DUMMY2_rvd17(data)                                                       (0x00020000&((data)<<17))
#define ISO_DUMMY2_rvd17_src(data)                                                   ((0x00020000&(data))>>17)
#define ISO_DUMMY2_get_rvd17(data)                                                   ((0x00020000&(data))>>17)
#define ISO_DUMMY2_rvd16_shift                                                       (16)
#define ISO_DUMMY2_rvd16_mask                                                        (0x00010000)
#define ISO_DUMMY2_rvd16(data)                                                       (0x00010000&((data)<<16))
#define ISO_DUMMY2_rvd16_src(data)                                                   ((0x00010000&(data))>>16)
#define ISO_DUMMY2_get_rvd16(data)                                                   ((0x00010000&(data))>>16)
#define ISO_DUMMY2_rvd15_shift                                                       (15)
#define ISO_DUMMY2_rvd15_mask                                                        (0x00008000)
#define ISO_DUMMY2_rvd15(data)                                                       (0x00008000&((data)<<15))
#define ISO_DUMMY2_rvd15_src(data)                                                   ((0x00008000&(data))>>15)
#define ISO_DUMMY2_get_rvd15(data)                                                   ((0x00008000&(data))>>15)
#define ISO_DUMMY2_rvd14_shift                                                       (14)
#define ISO_DUMMY2_rvd14_mask                                                        (0x00004000)
#define ISO_DUMMY2_rvd14(data)                                                       (0x00004000&((data)<<14))
#define ISO_DUMMY2_rvd14_src(data)                                                   ((0x00004000&(data))>>14)
#define ISO_DUMMY2_get_rvd14(data)                                                   ((0x00004000&(data))>>14)
#define ISO_DUMMY2_rvd13_shift                                                       (13)
#define ISO_DUMMY2_rvd13_mask                                                        (0x00002000)
#define ISO_DUMMY2_rvd13(data)                                                       (0x00002000&((data)<<13))
#define ISO_DUMMY2_rvd13_src(data)                                                   ((0x00002000&(data))>>13)
#define ISO_DUMMY2_get_rvd13(data)                                                   ((0x00002000&(data))>>13)
#define ISO_DUMMY2_rvd12_shift                                                       (12)
#define ISO_DUMMY2_rvd12_mask                                                        (0x00001000)
#define ISO_DUMMY2_rvd12(data)                                                       (0x00001000&((data)<<12))
#define ISO_DUMMY2_rvd12_src(data)                                                   ((0x00001000&(data))>>12)
#define ISO_DUMMY2_get_rvd12(data)                                                   ((0x00001000&(data))>>12)
#define ISO_DUMMY2_rvd11_shift                                                       (11)
#define ISO_DUMMY2_rvd11_mask                                                        (0x00000800)
#define ISO_DUMMY2_rvd11(data)                                                       (0x00000800&((data)<<11))
#define ISO_DUMMY2_rvd11_src(data)                                                   ((0x00000800&(data))>>11)
#define ISO_DUMMY2_get_rvd11(data)                                                   ((0x00000800&(data))>>11)
#define ISO_DUMMY2_rvd10_shift                                                       (10)
#define ISO_DUMMY2_rvd10_mask                                                        (0x00000400)
#define ISO_DUMMY2_rvd10(data)                                                       (0x00000400&((data)<<10))
#define ISO_DUMMY2_rvd10_src(data)                                                   ((0x00000400&(data))>>10)
#define ISO_DUMMY2_get_rvd10(data)                                                   ((0x00000400&(data))>>10)
#define ISO_DUMMY2_rvd9_shift                                                        (9)
#define ISO_DUMMY2_rvd9_mask                                                         (0x00000200)
#define ISO_DUMMY2_rvd9(data)                                                        (0x00000200&((data)<<9))
#define ISO_DUMMY2_rvd9_src(data)                                                    ((0x00000200&(data))>>9)
#define ISO_DUMMY2_get_rvd9(data)                                                    ((0x00000200&(data))>>9)
#define ISO_DUMMY2_rvd8_shift                                                        (8)
#define ISO_DUMMY2_rvd8_mask                                                         (0x00000100)
#define ISO_DUMMY2_rvd8(data)                                                        (0x00000100&((data)<<8))
#define ISO_DUMMY2_rvd8_src(data)                                                    ((0x00000100&(data))>>8)
#define ISO_DUMMY2_get_rvd8(data)                                                    ((0x00000100&(data))>>8)
#define ISO_DUMMY2_rvd7_shift                                                        (7)
#define ISO_DUMMY2_rvd7_mask                                                         (0x00000080)
#define ISO_DUMMY2_rvd7(data)                                                        (0x00000080&((data)<<7))
#define ISO_DUMMY2_rvd7_src(data)                                                    ((0x00000080&(data))>>7)
#define ISO_DUMMY2_get_rvd7(data)                                                    ((0x00000080&(data))>>7)
#define ISO_DUMMY2_rvd6_shift                                                        (6)
#define ISO_DUMMY2_rvd6_mask                                                         (0x00000040)
#define ISO_DUMMY2_rvd6(data)                                                        (0x00000040&((data)<<6))
#define ISO_DUMMY2_rvd6_src(data)                                                    ((0x00000040&(data))>>6)
#define ISO_DUMMY2_get_rvd6(data)                                                    ((0x00000040&(data))>>6)
#define ISO_DUMMY2_rvd5_shift                                                        (5)
#define ISO_DUMMY2_rvd5_mask                                                         (0x00000020)
#define ISO_DUMMY2_rvd5(data)                                                        (0x00000020&((data)<<5))
#define ISO_DUMMY2_rvd5_src(data)                                                    ((0x00000020&(data))>>5)
#define ISO_DUMMY2_get_rvd5(data)                                                    ((0x00000020&(data))>>5)
#define ISO_DUMMY2_rvd4_shift                                                        (4)
#define ISO_DUMMY2_rvd4_mask                                                         (0x00000010)
#define ISO_DUMMY2_rvd4(data)                                                        (0x00000010&((data)<<4))
#define ISO_DUMMY2_rvd4_src(data)                                                    ((0x00000010&(data))>>4)
#define ISO_DUMMY2_get_rvd4(data)                                                    ((0x00000010&(data))>>4)
#define ISO_DUMMY2_rvd3_shift                                                        (3)
#define ISO_DUMMY2_rvd3_mask                                                         (0x00000008)
#define ISO_DUMMY2_rvd3(data)                                                        (0x00000008&((data)<<3))
#define ISO_DUMMY2_rvd3_src(data)                                                    ((0x00000008&(data))>>3)
#define ISO_DUMMY2_get_rvd3(data)                                                    ((0x00000008&(data))>>3)
#define ISO_DUMMY2_rvd2_shift                                                        (2)
#define ISO_DUMMY2_rvd2_mask                                                         (0x00000004)
#define ISO_DUMMY2_rvd2(data)                                                        (0x00000004&((data)<<2))
#define ISO_DUMMY2_rvd2_src(data)                                                    ((0x00000004&(data))>>2)
#define ISO_DUMMY2_get_rvd2(data)                                                    ((0x00000004&(data))>>2)
#define ISO_DUMMY2_rvd1_shift                                                        (1)
#define ISO_DUMMY2_rvd1_mask                                                         (0x00000002)
#define ISO_DUMMY2_rvd1(data)                                                        (0x00000002&((data)<<1))
#define ISO_DUMMY2_rvd1_src(data)                                                    ((0x00000002&(data))>>1)
#define ISO_DUMMY2_get_rvd1(data)                                                    ((0x00000002&(data))>>1)
#define ISO_DUMMY2_rvd0_shift                                                        (0)
#define ISO_DUMMY2_rvd0_mask                                                         (0x00000001)
#define ISO_DUMMY2_rvd0(data)                                                        (0x00000001&((data)<<0))
#define ISO_DUMMY2_rvd0_src(data)                                                    ((0x00000001&(data))>>0)
#define ISO_DUMMY2_get_rvd0(data)                                                    ((0x00000001&(data))>>0)


#define ISO_POWERCUT_ETN                                                             0x1800705C
#define ISO_POWERCUT_ETN_reg_addr                                                    "0xB800705C"
#define ISO_POWERCUT_ETN_reg                                                         0xB800705C
#define set_ISO_POWERCUT_ETN_reg(data)   (*((volatile unsigned int*) ISO_POWERCUT_ETN_reg)=data)
#define get_ISO_POWERCUT_ETN_reg   (*((volatile unsigned int*) ISO_POWERCUT_ETN_reg))
#define ISO_POWERCUT_ETN_inst_adr                                                    "0x0017"
#define ISO_POWERCUT_ETN_inst                                                        0x0017
#define ISO_POWERCUT_ETN_powercut_ana_d2a_isolate_b_shift                            (1)
#define ISO_POWERCUT_ETN_powercut_ana_d2a_isolate_b_mask                             (0x00000002)
#define ISO_POWERCUT_ETN_powercut_ana_d2a_isolate_b(data)                            (0x00000002&((data)<<1))
#define ISO_POWERCUT_ETN_powercut_ana_d2a_isolate_b_src(data)                        ((0x00000002&(data))>>1)
#define ISO_POWERCUT_ETN_get_powercut_ana_d2a_isolate_b(data)                        ((0x00000002&(data))>>1)
#define ISO_POWERCUT_ETN_powercut_ana_a2d_isolate_b_shift                            (0)
#define ISO_POWERCUT_ETN_powercut_ana_a2d_isolate_b_mask                             (0x00000001)
#define ISO_POWERCUT_ETN_powercut_ana_a2d_isolate_b(data)                            (0x00000001&((data)<<0))
#define ISO_POWERCUT_ETN_powercut_ana_a2d_isolate_b_src(data)                        ((0x00000001&(data))>>0)
#define ISO_POWERCUT_ETN_get_powercut_ana_a2d_isolate_b(data)                        ((0x00000001&(data))>>0)


#define ISO_ETN_TESTIO                                                               0x18007060
#define ISO_ETN_TESTIO_reg_addr                                                      "0xB8007060"
#define ISO_ETN_TESTIO_reg                                                           0xB8007060
#define set_ISO_ETN_TESTIO_reg(data)   (*((volatile unsigned int*) ISO_ETN_TESTIO_reg)=data)
#define get_ISO_ETN_TESTIO_reg   (*((volatile unsigned int*) ISO_ETN_TESTIO_reg))
#define ISO_ETN_TESTIO_inst_adr                                                      "0x0018"
#define ISO_ETN_TESTIO_inst                                                          0x0018
#define ISO_ETN_TESTIO_etn_bpsgphy_mode_shift                                        (1)
#define ISO_ETN_TESTIO_etn_bpsgphy_mode_mask                                         (0x00000002)
#define ISO_ETN_TESTIO_etn_bpsgphy_mode(data)                                        (0x00000002&((data)<<1))
#define ISO_ETN_TESTIO_etn_bpsgphy_mode_src(data)                                    ((0x00000002&(data))>>1)
#define ISO_ETN_TESTIO_get_etn_bpsgphy_mode(data)                                    ((0x00000002&(data))>>1)
#define ISO_ETN_TESTIO_etn_ocd_mode_shift                                            (0)
#define ISO_ETN_TESTIO_etn_ocd_mode_mask                                             (0x00000001)
#define ISO_ETN_TESTIO_etn_ocd_mode(data)                                            (0x00000001&((data)<<0))
#define ISO_ETN_TESTIO_etn_ocd_mode_src(data)                                        ((0x00000001&(data))>>0)
#define ISO_ETN_TESTIO_get_etn_ocd_mode(data)                                        ((0x00000001&(data))>>0)


#define ISO_RESERVED_USE_0                                                           0x18007064
#define ISO_RESERVED_USE_0_reg_addr                                                  "0xB8007064"
#define ISO_RESERVED_USE_0_reg                                                       0xB8007064
#define set_ISO_RESERVED_USE_0_reg(data)   (*((volatile unsigned int*) ISO_RESERVED_USE_0_reg)=data)
#define get_ISO_RESERVED_USE_0_reg   (*((volatile unsigned int*) ISO_RESERVED_USE_0_reg))
#define ISO_RESERVED_USE_0_inst_adr                                                  "0x0019"
#define ISO_RESERVED_USE_0_inst                                                      0x0019
#define ISO_RESERVED_USE_0_dmy_shift                                                 (0)
#define ISO_RESERVED_USE_0_dmy_mask                                                  (0xFFFFFFFF)
#define ISO_RESERVED_USE_0_dmy(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ISO_RESERVED_USE_0_dmy_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ISO_RESERVED_USE_0_get_dmy(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ISO_LPI                                                                      0x18007068
#define ISO_LPI_reg_addr                                                             "0xB8007068"
#define ISO_LPI_reg                                                                  0xB8007068
#define set_ISO_LPI_reg(data)   (*((volatile unsigned int*) ISO_LPI_reg)=data)
#define get_ISO_LPI_reg   (*((volatile unsigned int*) ISO_LPI_reg))
#define ISO_LPI_inst_adr                                                             "0x001A"
#define ISO_LPI_inst                                                                 0x001A
#define ISO_LPI_ir_tx_shift                                                          (1)
#define ISO_LPI_ir_tx_mask                                                           (0x00000002)
#define ISO_LPI_ir_tx(data)                                                          (0x00000002&((data)<<1))
#define ISO_LPI_ir_tx_src(data)                                                      ((0x00000002&(data))>>1)
#define ISO_LPI_get_ir_tx(data)                                                      ((0x00000002&(data))>>1)
#define ISO_LPI_ir_raw_shift                                                         (0)
#define ISO_LPI_ir_raw_mask                                                          (0x00000001)
#define ISO_LPI_ir_raw(data)                                                         (0x00000001&((data)<<0))
#define ISO_LPI_ir_raw_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_LPI_get_ir_raw(data)                                                     ((0x00000001&(data))>>0)


#define ISO_WD                                                                       0x1800706C
#define ISO_WD_reg_addr                                                              "0xB800706C"
#define ISO_WD_reg                                                                   0xB800706C
#define set_ISO_WD_reg(data)   (*((volatile unsigned int*) ISO_WD_reg)=data)
#define get_ISO_WD_reg   (*((volatile unsigned int*) ISO_WD_reg))
#define ISO_WD_inst_adr                                                              "0x001B"
#define ISO_WD_inst                                                                  0x001B
#define ISO_WD_cnt_wait_pwr_shift                                                    (0)
#define ISO_WD_cnt_wait_pwr_mask                                                     (0x0000FFFF)
#define ISO_WD_cnt_wait_pwr(data)                                                    (0x0000FFFF&((data)<<0))
#define ISO_WD_cnt_wait_pwr_src(data)                                                ((0x0000FFFF&(data))>>0)
#define ISO_WD_get_cnt_wait_pwr(data)                                                ((0x0000FFFF&(data))>>0)


#define ISO_PLL_WDOUT                                                                0x18007070
#define ISO_PLL_WDOUT_reg_addr                                                       "0xB8007070"
#define ISO_PLL_WDOUT_reg                                                            0xB8007070
#define set_ISO_PLL_WDOUT_reg(data)   (*((volatile unsigned int*) ISO_PLL_WDOUT_reg)=data)
#define get_ISO_PLL_WDOUT_reg   (*((volatile unsigned int*) ISO_PLL_WDOUT_reg))
#define ISO_PLL_WDOUT_inst_adr                                                       "0x001C"
#define ISO_PLL_WDOUT_inst                                                           0x001C
#define ISO_PLL_WDOUT_plletn_wdout_shift                                             (0)
#define ISO_PLL_WDOUT_plletn_wdout_mask                                              (0x00000001)
#define ISO_PLL_WDOUT_plletn_wdout(data)                                             (0x00000001&((data)<<0))
#define ISO_PLL_WDOUT_plletn_wdout_src(data)                                         ((0x00000001&(data))>>0)
#define ISO_PLL_WDOUT_get_plletn_wdout(data)                                         ((0x00000001&(data))>>0)


#define ISO_PLL_ETN                                                                  0x18007074
#define ISO_PLL_ETN_reg_addr                                                         "0xB8007074"
#define ISO_PLL_ETN_reg                                                              0xB8007074
#define set_ISO_PLL_ETN_reg(data)   (*((volatile unsigned int*) ISO_PLL_ETN_reg)=data)
#define get_ISO_PLL_ETN_reg   (*((volatile unsigned int*) ISO_PLL_ETN_reg))
#define ISO_PLL_ETN_inst_adr                                                         "0x001D"
#define ISO_PLL_ETN_inst                                                             0x001D
#define ISO_PLL_ETN_plletn_oeb_shift                                                 (27)
#define ISO_PLL_ETN_plletn_oeb_mask                                                  (0x08000000)
#define ISO_PLL_ETN_plletn_oeb(data)                                                 (0x08000000&((data)<<27))
#define ISO_PLL_ETN_plletn_oeb_src(data)                                             ((0x08000000&(data))>>27)
#define ISO_PLL_ETN_get_plletn_oeb(data)                                             ((0x08000000&(data))>>27)
#define ISO_PLL_ETN_plletn_rstb_shift                                                (26)
#define ISO_PLL_ETN_plletn_rstb_mask                                                 (0x04000000)
#define ISO_PLL_ETN_plletn_rstb(data)                                                (0x04000000&((data)<<26))
#define ISO_PLL_ETN_plletn_rstb_src(data)                                            ((0x04000000&(data))>>26)
#define ISO_PLL_ETN_get_plletn_rstb(data)                                            ((0x04000000&(data))>>26)
#define ISO_PLL_ETN_plletn_o_shift                                                   (22)
#define ISO_PLL_ETN_plletn_o_mask                                                    (0x03C00000)
#define ISO_PLL_ETN_plletn_o(data)                                                   (0x03C00000&((data)<<22))
#define ISO_PLL_ETN_plletn_o_src(data)                                               ((0x03C00000&(data))>>22)
#define ISO_PLL_ETN_get_plletn_o(data)                                               ((0x03C00000&(data))>>22)
#define ISO_PLL_ETN_plletn_m_shift                                                   (15)
#define ISO_PLL_ETN_plletn_m_mask                                                    (0x003F8000)
#define ISO_PLL_ETN_plletn_m(data)                                                   (0x003F8000&((data)<<15))
#define ISO_PLL_ETN_plletn_m_src(data)                                               ((0x003F8000&(data))>>15)
#define ISO_PLL_ETN_get_plletn_m(data)                                               ((0x003F8000&(data))>>15)
#define ISO_PLL_ETN_plletn_ldo_pow_shift                                             (14)
#define ISO_PLL_ETN_plletn_ldo_pow_mask                                              (0x00004000)
#define ISO_PLL_ETN_plletn_ldo_pow(data)                                             (0x00004000&((data)<<14))
#define ISO_PLL_ETN_plletn_ldo_pow_src(data)                                         ((0x00004000&(data))>>14)
#define ISO_PLL_ETN_get_plletn_ldo_pow(data)                                         ((0x00004000&(data))>>14)
#define ISO_PLL_ETN_plletn_pow_shift                                                 (13)
#define ISO_PLL_ETN_plletn_pow_mask                                                  (0x00002000)
#define ISO_PLL_ETN_plletn_pow(data)                                                 (0x00002000&((data)<<13))
#define ISO_PLL_ETN_plletn_pow_src(data)                                             ((0x00002000&(data))>>13)
#define ISO_PLL_ETN_get_plletn_pow(data)                                             ((0x00002000&(data))>>13)
#define ISO_PLL_ETN_plletn_ldo_sel_shift                                             (11)
#define ISO_PLL_ETN_plletn_ldo_sel_mask                                              (0x00001800)
#define ISO_PLL_ETN_plletn_ldo_sel(data)                                             (0x00001800&((data)<<11))
#define ISO_PLL_ETN_plletn_ldo_sel_src(data)                                         ((0x00001800&(data))>>11)
#define ISO_PLL_ETN_get_plletn_ldo_sel(data)                                         ((0x00001800&(data))>>11)
#define ISO_PLL_ETN_plletn_wdmode_shift                                              (9)
#define ISO_PLL_ETN_plletn_wdmode_mask                                               (0x00000600)
#define ISO_PLL_ETN_plletn_wdmode(data)                                              (0x00000600&((data)<<9))
#define ISO_PLL_ETN_plletn_wdmode_src(data)                                          ((0x00000600&(data))>>9)
#define ISO_PLL_ETN_get_plletn_wdmode(data)                                          ((0x00000600&(data))>>9)
#define ISO_PLL_ETN_plletn_n_shift                                                   (7)
#define ISO_PLL_ETN_plletn_n_mask                                                    (0x00000180)
#define ISO_PLL_ETN_plletn_n(data)                                                   (0x00000180&((data)<<7))
#define ISO_PLL_ETN_plletn_n_src(data)                                               ((0x00000180&(data))>>7)
#define ISO_PLL_ETN_get_plletn_n(data)                                               ((0x00000180&(data))>>7)
#define ISO_PLL_ETN_plletn_lf_rs_shift                                               (5)
#define ISO_PLL_ETN_plletn_lf_rs_mask                                                (0x00000060)
#define ISO_PLL_ETN_plletn_lf_rs(data)                                               (0x00000060&((data)<<5))
#define ISO_PLL_ETN_plletn_lf_rs_src(data)                                           ((0x00000060&(data))>>5)
#define ISO_PLL_ETN_get_plletn_lf_rs(data)                                           ((0x00000060&(data))>>5)
#define ISO_PLL_ETN_plletn_lf_cp_shift                                               (3)
#define ISO_PLL_ETN_plletn_lf_cp_mask                                                (0x00000018)
#define ISO_PLL_ETN_plletn_lf_cp(data)                                               (0x00000018&((data)<<3))
#define ISO_PLL_ETN_plletn_lf_cp_src(data)                                           ((0x00000018&(data))>>3)
#define ISO_PLL_ETN_get_plletn_lf_cp(data)                                           ((0x00000018&(data))>>3)
#define ISO_PLL_ETN_plletn_ip_shift                                                  (0)
#define ISO_PLL_ETN_plletn_ip_mask                                                   (0x00000007)
#define ISO_PLL_ETN_plletn_ip(data)                                                  (0x00000007&((data)<<0))
#define ISO_PLL_ETN_plletn_ip_src(data)                                              ((0x00000007&(data))>>0)
#define ISO_PLL_ETN_get_plletn_ip(data)                                              ((0x00000007&(data))>>0)


#define ISO_RESERVED_USE_1                                                           0x18007078
#define ISO_RESERVED_USE_1_reg_addr                                                  "0xB8007078"
#define ISO_RESERVED_USE_1_reg                                                       0xB8007078
#define set_ISO_RESERVED_USE_1_reg(data)   (*((volatile unsigned int*) ISO_RESERVED_USE_1_reg)=data)
#define get_ISO_RESERVED_USE_1_reg   (*((volatile unsigned int*) ISO_RESERVED_USE_1_reg))
#define ISO_RESERVED_USE_1_inst_adr                                                  "0x001E"
#define ISO_RESERVED_USE_1_inst                                                      0x001E
#define ISO_RESERVED_USE_1_dmy_shift                                                 (0)
#define ISO_RESERVED_USE_1_dmy_mask                                                  (0xFFFFFFFF)
#define ISO_RESERVED_USE_1_dmy(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ISO_RESERVED_USE_1_dmy_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ISO_RESERVED_USE_1_get_dmy(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ISO_RESERVED_USE_2                                                           0x1800707C
#define ISO_RESERVED_USE_2_reg_addr                                                  "0xB800707C"
#define ISO_RESERVED_USE_2_reg                                                       0xB800707C
#define set_ISO_RESERVED_USE_2_reg(data)   (*((volatile unsigned int*) ISO_RESERVED_USE_2_reg)=data)
#define get_ISO_RESERVED_USE_2_reg   (*((volatile unsigned int*) ISO_RESERVED_USE_2_reg))
#define ISO_RESERVED_USE_2_inst_adr                                                  "0x001F"
#define ISO_RESERVED_USE_2_inst                                                      0x001F
#define ISO_RESERVED_USE_2_dmy_shift                                                 (0)
#define ISO_RESERVED_USE_2_dmy_mask                                                  (0xFFFFFFFF)
#define ISO_RESERVED_USE_2_dmy(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ISO_RESERVED_USE_2_dmy_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ISO_RESERVED_USE_2_get_dmy(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ISO_RESERVED_USE_3                                                           0x18007080
#define ISO_RESERVED_USE_3_reg_addr                                                  "0xB8007080"
#define ISO_RESERVED_USE_3_reg                                                       0xB8007080
#define set_ISO_RESERVED_USE_3_reg(data)   (*((volatile unsigned int*) ISO_RESERVED_USE_3_reg)=data)
#define get_ISO_RESERVED_USE_3_reg   (*((volatile unsigned int*) ISO_RESERVED_USE_3_reg))
#define ISO_RESERVED_USE_3_inst_adr                                                  "0x0020"
#define ISO_RESERVED_USE_3_inst                                                      0x0020
#define ISO_RESERVED_USE_3_dmy_shift                                                 (0)
#define ISO_RESERVED_USE_3_dmy_mask                                                  (0xFFFFFFFF)
#define ISO_RESERVED_USE_3_dmy(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ISO_RESERVED_USE_3_dmy_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ISO_RESERVED_USE_3_get_dmy(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ISO_I2C0_SDA_DEL                                                             0x18007084
#define ISO_I2C0_SDA_DEL_reg_addr                                                    "0xB8007084"
#define ISO_I2C0_SDA_DEL_reg                                                         0xB8007084
#define set_ISO_I2C0_SDA_DEL_reg(data)   (*((volatile unsigned int*) ISO_I2C0_SDA_DEL_reg)=data)
#define get_ISO_I2C0_SDA_DEL_reg   (*((volatile unsigned int*) ISO_I2C0_SDA_DEL_reg))
#define ISO_I2C0_SDA_DEL_inst_adr                                                    "0x0021"
#define ISO_I2C0_SDA_DEL_inst                                                        0x0021
#define ISO_I2C0_SDA_DEL_dmy1_shift                                                  (12)
#define ISO_I2C0_SDA_DEL_dmy1_mask                                                   (0xFFFFF000)
#define ISO_I2C0_SDA_DEL_dmy1(data)                                                  (0xFFFFF000&((data)<<12))
#define ISO_I2C0_SDA_DEL_dmy1_src(data)                                              ((0xFFFFF000&(data))>>12)
#define ISO_I2C0_SDA_DEL_get_dmy1(data)                                              ((0xFFFFF000&(data))>>12)
#define ISO_I2C0_SDA_DEL_en_shift                                                    (8)
#define ISO_I2C0_SDA_DEL_en_mask                                                     (0x00000100)
#define ISO_I2C0_SDA_DEL_en(data)                                                    (0x00000100&((data)<<8))
#define ISO_I2C0_SDA_DEL_en_src(data)                                                ((0x00000100&(data))>>8)
#define ISO_I2C0_SDA_DEL_get_en(data)                                                ((0x00000100&(data))>>8)
#define ISO_I2C0_SDA_DEL_sel_shift                                                   (0)
#define ISO_I2C0_SDA_DEL_sel_mask                                                    (0x0000001F)
#define ISO_I2C0_SDA_DEL_sel(data)                                                   (0x0000001F&((data)<<0))
#define ISO_I2C0_SDA_DEL_sel_src(data)                                               ((0x0000001F&(data))>>0)
#define ISO_I2C0_SDA_DEL_get_sel(data)                                               ((0x0000001F&(data))>>0)


#define ISO_SOFT_RESET                                                               0x18007088
#define ISO_SOFT_RESET_reg_addr                                                      "0xB8007088"
#define ISO_SOFT_RESET_reg                                                           0xB8007088
#define set_ISO_SOFT_RESET_reg(data)   (*((volatile unsigned int*) ISO_SOFT_RESET_reg)=data)
#define get_ISO_SOFT_RESET_reg   (*((volatile unsigned int*) ISO_SOFT_RESET_reg))
#define ISO_SOFT_RESET_inst_adr                                                      "0x0022"
#define ISO_SOFT_RESET_inst                                                          0x0022
#define ISO_SOFT_RESET_rstn_cbus_shift                                               (13)
#define ISO_SOFT_RESET_rstn_cbus_mask                                                (0x00002000)
#define ISO_SOFT_RESET_rstn_cbus(data)                                               (0x00002000&((data)<<13))
#define ISO_SOFT_RESET_rstn_cbus_src(data)                                           ((0x00002000&(data))>>13)
#define ISO_SOFT_RESET_get_rstn_cbus(data)                                           ((0x00002000&(data))>>13)
#define ISO_SOFT_RESET_rstn_i2c_6_shift                                              (12)
#define ISO_SOFT_RESET_rstn_i2c_6_mask                                               (0x00001000)
#define ISO_SOFT_RESET_rstn_i2c_6(data)                                              (0x00001000&((data)<<12))
#define ISO_SOFT_RESET_rstn_i2c_6_src(data)                                          ((0x00001000&(data))>>12)
#define ISO_SOFT_RESET_get_rstn_i2c_6(data)                                          ((0x00001000&(data))>>12)
#define ISO_SOFT_RESET_rstn_i2c_0_shift                                              (11)
#define ISO_SOFT_RESET_rstn_i2c_0_mask                                               (0x00000800)
#define ISO_SOFT_RESET_rstn_i2c_0(data)                                              (0x00000800&((data)<<11))
#define ISO_SOFT_RESET_rstn_i2c_0_src(data)                                          ((0x00000800&(data))>>11)
#define ISO_SOFT_RESET_get_rstn_i2c_0(data)                                          ((0x00000800&(data))>>11)
#define ISO_SOFT_RESET_rstn_gphy_shift                                               (10)
#define ISO_SOFT_RESET_rstn_gphy_mask                                                (0x00000400)
#define ISO_SOFT_RESET_rstn_gphy(data)                                               (0x00000400&((data)<<10))
#define ISO_SOFT_RESET_rstn_gphy_src(data)                                           ((0x00000400&(data))>>10)
#define ISO_SOFT_RESET_get_rstn_gphy(data)                                           ((0x00000400&(data))>>10)
#define ISO_SOFT_RESET_rstn_gmac_shift                                               (9)
#define ISO_SOFT_RESET_rstn_gmac_mask                                                (0x00000200)
#define ISO_SOFT_RESET_rstn_gmac(data)                                               (0x00000200&((data)<<9))
#define ISO_SOFT_RESET_rstn_gmac_src(data)                                           ((0x00000200&(data))>>9)
#define ISO_SOFT_RESET_get_rstn_gmac(data)                                           ((0x00000200&(data))>>9)
#define ISO_SOFT_RESET_rstn_ur0_shift                                                (8)
#define ISO_SOFT_RESET_rstn_ur0_mask                                                 (0x00000100)
#define ISO_SOFT_RESET_rstn_ur0(data)                                                (0x00000100&((data)<<8))
#define ISO_SOFT_RESET_rstn_ur0_src(data)                                            ((0x00000100&(data))>>8)
#define ISO_SOFT_RESET_get_rstn_ur0(data)                                            ((0x00000100&(data))>>8)
#define ISO_SOFT_RESET_rstn_efuse_shift                                              (7)
#define ISO_SOFT_RESET_rstn_efuse_mask                                               (0x00000080)
#define ISO_SOFT_RESET_rstn_efuse(data)                                              (0x00000080&((data)<<7))
#define ISO_SOFT_RESET_rstn_efuse_src(data)                                          ((0x00000080&(data))>>7)
#define ISO_SOFT_RESET_get_rstn_efuse(data)                                          ((0x00000080&(data))>>7)
#define ISO_SOFT_RESET_rstn_cbusrx_shift                                             (6)
#define ISO_SOFT_RESET_rstn_cbusrx_mask                                              (0x00000040)
#define ISO_SOFT_RESET_rstn_cbusrx(data)                                             (0x00000040&((data)<<6))
#define ISO_SOFT_RESET_rstn_cbusrx_src(data)                                         ((0x00000040&(data))>>6)
#define ISO_SOFT_RESET_get_rstn_cbusrx(data)                                         ((0x00000040&(data))>>6)
#define ISO_SOFT_RESET_rstn_cbustx_shift                                             (5)
#define ISO_SOFT_RESET_rstn_cbustx_mask                                              (0x00000020)
#define ISO_SOFT_RESET_rstn_cbustx(data)                                             (0x00000020&((data)<<5))
#define ISO_SOFT_RESET_rstn_cbustx_src(data)                                         ((0x00000020&(data))>>5)
#define ISO_SOFT_RESET_get_rstn_cbustx(data)                                         ((0x00000020&(data))>>5)
#define ISO_SOFT_RESET_rstn_dp_shift                                                 (4)
#define ISO_SOFT_RESET_rstn_dp_mask                                                  (0x00000010)
#define ISO_SOFT_RESET_rstn_dp(data)                                                 (0x00000010&((data)<<4))
#define ISO_SOFT_RESET_rstn_dp_src(data)                                             ((0x00000010&(data))>>4)
#define ISO_SOFT_RESET_get_rstn_dp(data)                                             ((0x00000010&(data))>>4)
#define ISO_SOFT_RESET_rstn_cec1_shift                                               (3)
#define ISO_SOFT_RESET_rstn_cec1_mask                                                (0x00000008)
#define ISO_SOFT_RESET_rstn_cec1(data)                                               (0x00000008&((data)<<3))
#define ISO_SOFT_RESET_rstn_cec1_src(data)                                           ((0x00000008&(data))>>3)
#define ISO_SOFT_RESET_get_rstn_cec1(data)                                           ((0x00000008&(data))>>3)
#define ISO_SOFT_RESET_rstn_cec0_shift                                               (2)
#define ISO_SOFT_RESET_rstn_cec0_mask                                                (0x00000004)
#define ISO_SOFT_RESET_rstn_cec0(data)                                               (0x00000004&((data)<<2))
#define ISO_SOFT_RESET_rstn_cec0_src(data)                                           ((0x00000004&(data))>>2)
#define ISO_SOFT_RESET_get_rstn_cec0(data)                                           ((0x00000004&(data))>>2)
#define ISO_SOFT_RESET_rstn_ir_shift                                                 (1)
#define ISO_SOFT_RESET_rstn_ir_mask                                                  (0x00000002)
#define ISO_SOFT_RESET_rstn_ir(data)                                                 (0x00000002&((data)<<1))
#define ISO_SOFT_RESET_rstn_ir_src(data)                                             ((0x00000002&(data))>>1)
#define ISO_SOFT_RESET_get_rstn_ir(data)                                             ((0x00000002&(data))>>1)
#define ISO_SOFT_RESET_rstn_vfd_shift                                                (0)
#define ISO_SOFT_RESET_rstn_vfd_mask                                                 (0x00000001)
#define ISO_SOFT_RESET_rstn_vfd(data)                                                (0x00000001&((data)<<0))
#define ISO_SOFT_RESET_rstn_vfd_src(data)                                            ((0x00000001&(data))>>0)
#define ISO_SOFT_RESET_get_rstn_vfd(data)                                            ((0x00000001&(data))>>0)


#define ISO_CLOCK_ENABLE                                                             0x1800708C
#define ISO_CLOCK_ENABLE_reg_addr                                                    "0xB800708C"
#define ISO_CLOCK_ENABLE_reg                                                         0xB800708C
#define set_ISO_CLOCK_ENABLE_reg(data)   (*((volatile unsigned int*) ISO_CLOCK_ENABLE_reg)=data)
#define get_ISO_CLOCK_ENABLE_reg   (*((volatile unsigned int*) ISO_CLOCK_ENABLE_reg))
#define ISO_CLOCK_ENABLE_inst_adr                                                    "0x0023"
#define ISO_CLOCK_ENABLE_inst                                                        0x0023
#define ISO_CLOCK_ENABLE_clk_en_etn_sys_shift                                        (12)
#define ISO_CLOCK_ENABLE_clk_en_etn_sys_mask                                         (0x00001000)
#define ISO_CLOCK_ENABLE_clk_en_etn_sys(data)                                        (0x00001000&((data)<<12))
#define ISO_CLOCK_ENABLE_clk_en_etn_sys_src(data)                                    ((0x00001000&(data))>>12)
#define ISO_CLOCK_ENABLE_get_clk_en_etn_sys(data)                                    ((0x00001000&(data))>>12)
#define ISO_CLOCK_ENABLE_clk_en_etn_250m_shift                                       (11)
#define ISO_CLOCK_ENABLE_clk_en_etn_250m_mask                                        (0x00000800)
#define ISO_CLOCK_ENABLE_clk_en_etn_250m(data)                                       (0x00000800&((data)<<11))
#define ISO_CLOCK_ENABLE_clk_en_etn_250m_src(data)                                   ((0x00000800&(data))>>11)
#define ISO_CLOCK_ENABLE_get_clk_en_etn_250m(data)                                   ((0x00000800&(data))>>11)
#define ISO_CLOCK_ENABLE_clk_en_i2c6_shift                                           (10)
#define ISO_CLOCK_ENABLE_clk_en_i2c6_mask                                            (0x00000400)
#define ISO_CLOCK_ENABLE_clk_en_i2c6(data)                                           (0x00000400&((data)<<10))
#define ISO_CLOCK_ENABLE_clk_en_i2c6_src(data)                                       ((0x00000400&(data))>>10)
#define ISO_CLOCK_ENABLE_get_clk_en_i2c6(data)                                       ((0x00000400&(data))>>10)
#define ISO_CLOCK_ENABLE_clk_en_i2c0_shift                                           (9)
#define ISO_CLOCK_ENABLE_clk_en_i2c0_mask                                            (0x00000200)
#define ISO_CLOCK_ENABLE_clk_en_i2c0(data)                                           (0x00000200&((data)<<9))
#define ISO_CLOCK_ENABLE_clk_en_i2c0_src(data)                                       ((0x00000200&(data))>>9)
#define ISO_CLOCK_ENABLE_get_clk_en_i2c0(data)                                       ((0x00000200&(data))>>9)
#define ISO_CLOCK_ENABLE_clk_en_misc_ur0_shift                                       (8)
#define ISO_CLOCK_ENABLE_clk_en_misc_ur0_mask                                        (0x00000100)
#define ISO_CLOCK_ENABLE_clk_en_misc_ur0(data)                                       (0x00000100&((data)<<8))
#define ISO_CLOCK_ENABLE_clk_en_misc_ur0_src(data)                                   ((0x00000100&(data))>>8)
#define ISO_CLOCK_ENABLE_get_clk_en_misc_ur0(data)                                   ((0x00000100&(data))>>8)
#define ISO_CLOCK_ENABLE_clk_en_misc_ir_shift                                        (7)
#define ISO_CLOCK_ENABLE_clk_en_misc_ir_mask                                         (0x00000080)
#define ISO_CLOCK_ENABLE_clk_en_misc_ir(data)                                        (0x00000080&((data)<<7))
#define ISO_CLOCK_ENABLE_clk_en_misc_ir_src(data)                                    ((0x00000080&(data))>>7)
#define ISO_CLOCK_ENABLE_get_clk_en_misc_ir(data)                                    ((0x00000080&(data))>>7)
#define ISO_CLOCK_ENABLE_clk_en_cbus_osc_shift                                       (6)
#define ISO_CLOCK_ENABLE_clk_en_cbus_osc_mask                                        (0x00000040)
#define ISO_CLOCK_ENABLE_clk_en_cbus_osc(data)                                       (0x00000040&((data)<<6))
#define ISO_CLOCK_ENABLE_clk_en_cbus_osc_src(data)                                   ((0x00000040&(data))>>6)
#define ISO_CLOCK_ENABLE_get_clk_en_cbus_osc(data)                                   ((0x00000040&(data))>>6)
#define ISO_CLOCK_ENABLE_clk_en_cbus_sys_shift                                       (5)
#define ISO_CLOCK_ENABLE_clk_en_cbus_sys_mask                                        (0x00000020)
#define ISO_CLOCK_ENABLE_clk_en_cbus_sys(data)                                       (0x00000020&((data)<<5))
#define ISO_CLOCK_ENABLE_clk_en_cbus_sys_src(data)                                   ((0x00000020&(data))>>5)
#define ISO_CLOCK_ENABLE_get_clk_en_cbus_sys(data)                                   ((0x00000020&(data))>>5)
#define ISO_CLOCK_ENABLE_clk_en_cbustx_sys_shift                                     (4)
#define ISO_CLOCK_ENABLE_clk_en_cbustx_sys_mask                                      (0x00000010)
#define ISO_CLOCK_ENABLE_clk_en_cbustx_sys(data)                                     (0x00000010&((data)<<4))
#define ISO_CLOCK_ENABLE_clk_en_cbustx_sys_src(data)                                 ((0x00000010&(data))>>4)
#define ISO_CLOCK_ENABLE_get_clk_en_cbustx_sys(data)                                 ((0x00000010&(data))>>4)
#define ISO_CLOCK_ENABLE_clk_en_cbusrx_sys_shift                                     (3)
#define ISO_CLOCK_ENABLE_clk_en_cbusrx_sys_mask                                      (0x00000008)
#define ISO_CLOCK_ENABLE_clk_en_cbusrx_sys(data)                                     (0x00000008&((data)<<3))
#define ISO_CLOCK_ENABLE_clk_en_cbusrx_sys_src(data)                                 ((0x00000008&(data))>>3)
#define ISO_CLOCK_ENABLE_get_clk_en_cbusrx_sys(data)                                 ((0x00000008&(data))>>3)
#define ISO_CLOCK_ENABLE_clk_en_misc_cec0_shift                                      (2)
#define ISO_CLOCK_ENABLE_clk_en_misc_cec0_mask                                       (0x00000004)
#define ISO_CLOCK_ENABLE_clk_en_misc_cec0(data)                                      (0x00000004&((data)<<2))
#define ISO_CLOCK_ENABLE_clk_en_misc_cec0_src(data)                                  ((0x00000004&(data))>>2)
#define ISO_CLOCK_ENABLE_get_clk_en_misc_cec0(data)                                  ((0x00000004&(data))>>2)
#define ISO_CLOCK_ENABLE_clk_en_misc_vfd_shift                                       (1)
#define ISO_CLOCK_ENABLE_clk_en_misc_vfd_mask                                        (0x00000002)
#define ISO_CLOCK_ENABLE_clk_en_misc_vfd(data)                                       (0x00000002&((data)<<1))
#define ISO_CLOCK_ENABLE_clk_en_misc_vfd_src(data)                                   ((0x00000002&(data))>>1)
#define ISO_CLOCK_ENABLE_get_clk_en_misc_vfd(data)                                   ((0x00000002&(data))>>1)
#define ISO_CLOCK_ENABLE_clk_en_misc_mix_shift                                       (0)
#define ISO_CLOCK_ENABLE_clk_en_misc_mix_mask                                        (0x00000001)
#define ISO_CLOCK_ENABLE_clk_en_misc_mix(data)                                       (0x00000001&((data)<<0))
#define ISO_CLOCK_ENABLE_clk_en_misc_mix_src(data)                                   ((0x00000001&(data))>>0)
#define ISO_CLOCK_ENABLE_get_clk_en_misc_mix(data)                                   ((0x00000001&(data))>>0)


#define ISO_DC_0                                                                     0x18007090
#define ISO_DC_0_reg_addr                                                            "0xB8007090"
#define ISO_DC_0_reg                                                                 0xB8007090
#define set_ISO_DC_0_reg(data)   (*((volatile unsigned int*) ISO_DC_0_reg)=data)
#define get_ISO_DC_0_reg   (*((volatile unsigned int*) ISO_DC_0_reg))
#define ISO_DC_0_inst_adr                                                            "0x0024"
#define ISO_DC_0_inst                                                                0x0024
#define ISO_DC_0_rd_only_0_en_shift                                                  (24)
#define ISO_DC_0_rd_only_0_en_mask                                                   (0x01000000)
#define ISO_DC_0_rd_only_0_en(data)                                                  (0x01000000&((data)<<24))
#define ISO_DC_0_rd_only_0_en_src(data)                                              ((0x01000000&(data))>>24)
#define ISO_DC_0_get_rd_only_0_en(data)                                              ((0x01000000&(data))>>24)
#define ISO_DC_0_blk_protect_0_wpro_en_shift                                         (21)
#define ISO_DC_0_blk_protect_0_wpro_en_mask                                          (0x00200000)
#define ISO_DC_0_blk_protect_0_wpro_en(data)                                         (0x00200000&((data)<<21))
#define ISO_DC_0_blk_protect_0_wpro_en_src(data)                                     ((0x00200000&(data))>>21)
#define ISO_DC_0_get_blk_protect_0_wpro_en(data)                                     ((0x00200000&(data))>>21)
#define ISO_DC_0_blk_protect_0_en_shift                                              (18)
#define ISO_DC_0_blk_protect_0_en_mask                                               (0x00040000)
#define ISO_DC_0_blk_protect_0_en(data)                                              (0x00040000&((data)<<18))
#define ISO_DC_0_blk_protect_0_en_src(data)                                          ((0x00040000&(data))>>18)
#define ISO_DC_0_get_blk_protect_0_en(data)                                          ((0x00040000&(data))>>18)
#define ISO_DC_0_protect_0_wpro_en_shift                                             (9)
#define ISO_DC_0_protect_0_wpro_en_mask                                              (0x00000200)
#define ISO_DC_0_protect_0_wpro_en(data)                                             (0x00000200&((data)<<9))
#define ISO_DC_0_protect_0_wpro_en_src(data)                                         ((0x00000200&(data))>>9)
#define ISO_DC_0_get_protect_0_wpro_en(data)                                         ((0x00000200&(data))>>9)
#define ISO_DC_0_protect_0_en_shift                                                  (0)
#define ISO_DC_0_protect_0_en_mask                                                   (0x00000001)
#define ISO_DC_0_protect_0_en(data)                                                  (0x00000001&((data)<<0))
#define ISO_DC_0_protect_0_en_src(data)                                              ((0x00000001&(data))>>0)
#define ISO_DC_0_get_protect_0_en(data)                                              ((0x00000001&(data))>>0)


#define ISO_DC_1                                                                     0x18007094
#define ISO_DC_1_reg_addr                                                            "0xB8007094"
#define ISO_DC_1_reg                                                                 0xB8007094
#define set_ISO_DC_1_reg(data)   (*((volatile unsigned int*) ISO_DC_1_reg)=data)
#define get_ISO_DC_1_reg   (*((volatile unsigned int*) ISO_DC_1_reg))
#define ISO_DC_1_inst_adr                                                            "0x0025"
#define ISO_DC_1_inst                                                                0x0025
#define ISO_DC_1_mem_saddr0_shift                                                    (12)
#define ISO_DC_1_mem_saddr0_mask                                                     (0xFFFFF000)
#define ISO_DC_1_mem_saddr0(data)                                                    (0xFFFFF000&((data)<<12))
#define ISO_DC_1_mem_saddr0_src(data)                                                ((0xFFFFF000&(data))>>12)
#define ISO_DC_1_get_mem_saddr0(data)                                                ((0xFFFFF000&(data))>>12)


#define ISO_DC_2                                                                     0x18007098
#define ISO_DC_2_reg_addr                                                            "0xB8007098"
#define ISO_DC_2_reg                                                                 0xB8007098
#define set_ISO_DC_2_reg(data)   (*((volatile unsigned int*) ISO_DC_2_reg)=data)
#define get_ISO_DC_2_reg   (*((volatile unsigned int*) ISO_DC_2_reg))
#define ISO_DC_2_inst_adr                                                            "0x0026"
#define ISO_DC_2_inst                                                                0x0026
#define ISO_DC_2_mem_eaddr0_shift                                                    (12)
#define ISO_DC_2_mem_eaddr0_mask                                                     (0xFFFFF000)
#define ISO_DC_2_mem_eaddr0(data)                                                    (0xFFFFF000&((data)<<12))
#define ISO_DC_2_mem_eaddr0_src(data)                                                ((0xFFFFF000&(data))>>12)
#define ISO_DC_2_get_mem_eaddr0(data)                                                ((0xFFFFF000&(data))>>12)


#define ISO_DC_3                                                                     0x1800709C
#define ISO_DC_3_reg_addr                                                            "0xB800709C"
#define ISO_DC_3_reg                                                                 0xB800709C
#define set_ISO_DC_3_reg(data)   (*((volatile unsigned int*) ISO_DC_3_reg)=data)
#define get_ISO_DC_3_reg   (*((volatile unsigned int*) ISO_DC_3_reg))
#define ISO_DC_3_inst_adr                                                            "0x0027"
#define ISO_DC_3_inst                                                                0x0027
#define ISO_DC_3_blk_saddr0_shift                                                    (12)
#define ISO_DC_3_blk_saddr0_mask                                                     (0xFFFFF000)
#define ISO_DC_3_blk_saddr0(data)                                                    (0xFFFFF000&((data)<<12))
#define ISO_DC_3_blk_saddr0_src(data)                                                ((0xFFFFF000&(data))>>12)
#define ISO_DC_3_get_blk_saddr0(data)                                                ((0xFFFFF000&(data))>>12)


#define ISO_DC_4                                                                     0x180070A0
#define ISO_DC_4_reg_addr                                                            "0xB80070A0"
#define ISO_DC_4_reg                                                                 0xB80070A0
#define set_ISO_DC_4_reg(data)   (*((volatile unsigned int*) ISO_DC_4_reg)=data)
#define get_ISO_DC_4_reg   (*((volatile unsigned int*) ISO_DC_4_reg))
#define ISO_DC_4_inst_adr                                                            "0x0028"
#define ISO_DC_4_inst                                                                0x0028
#define ISO_DC_4_blk_eaddr0_shift                                                    (12)
#define ISO_DC_4_blk_eaddr0_mask                                                     (0xFFFFF000)
#define ISO_DC_4_blk_eaddr0(data)                                                    (0xFFFFF000&((data)<<12))
#define ISO_DC_4_blk_eaddr0_src(data)                                                ((0xFFFFF000&(data))>>12)
#define ISO_DC_4_get_blk_eaddr0(data)                                                ((0xFFFFF000&(data))>>12)


#define ISO_DC_5                                                                     0x180070A4
#define ISO_DC_5_reg_addr                                                            "0xB80070A4"
#define ISO_DC_5_reg                                                                 0xB80070A4
#define set_ISO_DC_5_reg(data)   (*((volatile unsigned int*) ISO_DC_5_reg)=data)
#define get_ISO_DC_5_reg   (*((volatile unsigned int*) ISO_DC_5_reg))
#define ISO_DC_5_inst_adr                                                            "0x0029"
#define ISO_DC_5_inst                                                                0x0029
#define ISO_DC_5_ro_saddr0_shift                                                     (12)
#define ISO_DC_5_ro_saddr0_mask                                                      (0xFFFFF000)
#define ISO_DC_5_ro_saddr0(data)                                                     (0xFFFFF000&((data)<<12))
#define ISO_DC_5_ro_saddr0_src(data)                                                 ((0xFFFFF000&(data))>>12)
#define ISO_DC_5_get_ro_saddr0(data)                                                 ((0xFFFFF000&(data))>>12)


#define ISO_DC_6                                                                     0x180070A8
#define ISO_DC_6_reg_addr                                                            "0xB80070A8"
#define ISO_DC_6_reg                                                                 0xB80070A8
#define set_ISO_DC_6_reg(data)   (*((volatile unsigned int*) ISO_DC_6_reg)=data)
#define get_ISO_DC_6_reg   (*((volatile unsigned int*) ISO_DC_6_reg))
#define ISO_DC_6_inst_adr                                                            "0x002A"
#define ISO_DC_6_inst                                                                0x002A
#define ISO_DC_6_ro_eaddr0_shift                                                     (12)
#define ISO_DC_6_ro_eaddr0_mask                                                      (0xFFFFF000)
#define ISO_DC_6_ro_eaddr0(data)                                                     (0xFFFFF000&((data)<<12))
#define ISO_DC_6_ro_eaddr0_src(data)                                                 ((0xFFFFF000&(data))>>12)
#define ISO_DC_6_get_ro_eaddr0(data)                                                 ((0xFFFFF000&(data))>>12)


#define ISO_DC_7                                                                     0x180070AC
#define ISO_DC_7_reg_addr                                                            "0xB80070AC"
#define ISO_DC_7_reg                                                                 0xB80070AC
#define set_ISO_DC_7_reg(data)   (*((volatile unsigned int*) ISO_DC_7_reg)=data)
#define get_ISO_DC_7_reg   (*((volatile unsigned int*) ISO_DC_7_reg))
#define ISO_DC_7_inst_adr                                                            "0x002B"
#define ISO_DC_7_inst                                                                0x002B
#define ISO_DC_7_md_tee_protect_en_shift                                             (24)
#define ISO_DC_7_md_tee_protect_en_mask                                              (0x01000000)
#define ISO_DC_7_md_tee_protect_en(data)                                             (0x01000000&((data)<<24))
#define ISO_DC_7_md_tee_protect_en_src(data)                                         ((0x01000000&(data))>>24)
#define ISO_DC_7_get_md_tee_protect_en(data)                                         ((0x01000000&(data))>>24)
#define ISO_DC_7_cp_tee_protect_en_shift                                             (16)
#define ISO_DC_7_cp_tee_protect_en_mask                                              (0x00010000)
#define ISO_DC_7_cp_tee_protect_en(data)                                             (0x00010000&((data)<<16))
#define ISO_DC_7_cp_tee_protect_en_src(data)                                         ((0x00010000&(data))>>16)
#define ISO_DC_7_get_cp_tee_protect_en(data)                                         ((0x00010000&(data))>>16)
#define ISO_DC_7_vo_protect_en_shift                                                 (8)
#define ISO_DC_7_vo_protect_en_mask                                                  (0x00000100)
#define ISO_DC_7_vo_protect_en(data)                                                 (0x00000100&((data)<<8))
#define ISO_DC_7_vo_protect_en_src(data)                                             ((0x00000100&(data))>>8)
#define ISO_DC_7_get_vo_protect_en(data)                                             ((0x00000100&(data))>>8)
#define ISO_DC_7_nf_tee_protect_en_shift                                             (0)
#define ISO_DC_7_nf_tee_protect_en_mask                                              (0x00000001)
#define ISO_DC_7_nf_tee_protect_en(data)                                             (0x00000001&((data)<<0))
#define ISO_DC_7_nf_tee_protect_en_src(data)                                         ((0x00000001&(data))>>0)
#define ISO_DC_7_get_nf_tee_protect_en(data)                                         ((0x00000001&(data))>>0)


#define ISO_DC_8                                                                     0x180070B0
#define ISO_DC_8_reg_addr                                                            "0xB80070B0"
#define ISO_DC_8_reg                                                                 0xB80070B0
#define set_ISO_DC_8_reg(data)   (*((volatile unsigned int*) ISO_DC_8_reg)=data)
#define get_ISO_DC_8_reg   (*((volatile unsigned int*) ISO_DC_8_reg))
#define ISO_DC_8_inst_adr                                                            "0x002C"
#define ISO_DC_8_inst                                                                0x002C
#define ISO_DC_8_scpu_tee_protect_en_shift                                           (24)
#define ISO_DC_8_scpu_tee_protect_en_mask                                            (0x01000000)
#define ISO_DC_8_scpu_tee_protect_en(data)                                           (0x01000000&((data)<<24))
#define ISO_DC_8_scpu_tee_protect_en_src(data)                                       ((0x01000000&(data))>>24)
#define ISO_DC_8_get_scpu_tee_protect_en(data)                                       ((0x01000000&(data))>>24)
#define ISO_DC_8_acpu_protect_en_shift                                               (16)
#define ISO_DC_8_acpu_protect_en_mask                                                (0x00010000)
#define ISO_DC_8_acpu_protect_en(data)                                               (0x00010000&((data)<<16))
#define ISO_DC_8_acpu_protect_en_src(data)                                           ((0x00010000&(data))>>16)
#define ISO_DC_8_get_acpu_protect_en(data)                                           ((0x00010000&(data))>>16)
#define ISO_DC_8_video_protect_en_shift                                              (8)
#define ISO_DC_8_video_protect_en_mask                                               (0x00000100)
#define ISO_DC_8_video_protect_en(data)                                              (0x00000100&((data)<<8))
#define ISO_DC_8_video_protect_en_src(data)                                          ((0x00000100&(data))>>8)
#define ISO_DC_8_get_video_protect_en(data)                                          ((0x00000100&(data))>>8)
#define ISO_DC_8_audio_protect_en_shift                                              (0)
#define ISO_DC_8_audio_protect_en_mask                                               (0x00000001)
#define ISO_DC_8_audio_protect_en(data)                                              (0x00000001&((data)<<0))
#define ISO_DC_8_audio_protect_en_src(data)                                          ((0x00000001&(data))>>0)
#define ISO_DC_8_get_audio_protect_en(data)                                          ((0x00000001&(data))>>0)


#define ISO_DC_9                                                                     0x180070B4
#define ISO_DC_9_reg_addr                                                            "0xB80070B4"
#define ISO_DC_9_reg                                                                 0xB80070B4
#define set_ISO_DC_9_reg(data)   (*((volatile unsigned int*) ISO_DC_9_reg)=data)
#define get_ISO_DC_9_reg   (*((volatile unsigned int*) ISO_DC_9_reg))
#define ISO_DC_9_inst_adr                                                            "0x002D"
#define ISO_DC_9_inst                                                                0x002D
#define ISO_DC_9_scpu_tee_blk_protect_en_shift                                       (14)
#define ISO_DC_9_scpu_tee_blk_protect_en_mask                                        (0x00004000)
#define ISO_DC_9_scpu_tee_blk_protect_en(data)                                       (0x00004000&((data)<<14))
#define ISO_DC_9_scpu_tee_blk_protect_en_src(data)                                   ((0x00004000&(data))>>14)
#define ISO_DC_9_get_scpu_tee_blk_protect_en(data)                                   ((0x00004000&(data))>>14)
#define ISO_DC_9_acpu_blk_protect_en_shift                                           (12)
#define ISO_DC_9_acpu_blk_protect_en_mask                                            (0x00001000)
#define ISO_DC_9_acpu_blk_protect_en(data)                                           (0x00001000&((data)<<12))
#define ISO_DC_9_acpu_blk_protect_en_src(data)                                       ((0x00001000&(data))>>12)
#define ISO_DC_9_get_acpu_blk_protect_en(data)                                       ((0x00001000&(data))>>12)
#define ISO_DC_9_video_blk_protect_en_shift                                          (10)
#define ISO_DC_9_video_blk_protect_en_mask                                           (0x00000400)
#define ISO_DC_9_video_blk_protect_en(data)                                          (0x00000400&((data)<<10))
#define ISO_DC_9_video_blk_protect_en_src(data)                                      ((0x00000400&(data))>>10)
#define ISO_DC_9_get_video_blk_protect_en(data)                                      ((0x00000400&(data))>>10)
#define ISO_DC_9_audio_blk_protect_en_shift                                          (8)
#define ISO_DC_9_audio_blk_protect_en_mask                                           (0x00000100)
#define ISO_DC_9_audio_blk_protect_en(data)                                          (0x00000100&((data)<<8))
#define ISO_DC_9_audio_blk_protect_en_src(data)                                      ((0x00000100&(data))>>8)
#define ISO_DC_9_get_audio_blk_protect_en(data)                                      ((0x00000100&(data))>>8)
#define ISO_DC_9_md_tee_blk_protect_en_shift                                         (6)
#define ISO_DC_9_md_tee_blk_protect_en_mask                                          (0x00000040)
#define ISO_DC_9_md_tee_blk_protect_en(data)                                         (0x00000040&((data)<<6))
#define ISO_DC_9_md_tee_blk_protect_en_src(data)                                     ((0x00000040&(data))>>6)
#define ISO_DC_9_get_md_tee_blk_protect_en(data)                                     ((0x00000040&(data))>>6)
#define ISO_DC_9_cp_tee_blk_protect_en_shift                                         (4)
#define ISO_DC_9_cp_tee_blk_protect_en_mask                                          (0x00000010)
#define ISO_DC_9_cp_tee_blk_protect_en(data)                                         (0x00000010&((data)<<4))
#define ISO_DC_9_cp_tee_blk_protect_en_src(data)                                     ((0x00000010&(data))>>4)
#define ISO_DC_9_get_cp_tee_blk_protect_en(data)                                     ((0x00000010&(data))>>4)
#define ISO_DC_9_vo_blk_protect_en_shift                                             (2)
#define ISO_DC_9_vo_blk_protect_en_mask                                              (0x00000004)
#define ISO_DC_9_vo_blk_protect_en(data)                                             (0x00000004&((data)<<2))
#define ISO_DC_9_vo_blk_protect_en_src(data)                                         ((0x00000004&(data))>>2)
#define ISO_DC_9_get_vo_blk_protect_en(data)                                         ((0x00000004&(data))>>2)
#define ISO_DC_9_nf_tee_blk_protect_en_shift                                         (0)
#define ISO_DC_9_nf_tee_blk_protect_en_mask                                          (0x00000001)
#define ISO_DC_9_nf_tee_blk_protect_en(data)                                         (0x00000001&((data)<<0))
#define ISO_DC_9_nf_tee_blk_protect_en_src(data)                                     ((0x00000001&(data))>>0)
#define ISO_DC_9_get_nf_tee_blk_protect_en(data)                                     ((0x00000001&(data))>>0)


#define ISO_DC_A                                                                     0x180070B8
#define ISO_DC_A_reg_addr                                                            "0xB80070B8"
#define ISO_DC_A_reg                                                                 0xB80070B8
#define set_ISO_DC_A_reg(data)   (*((volatile unsigned int*) ISO_DC_A_reg)=data)
#define get_ISO_DC_A_reg   (*((volatile unsigned int*) ISO_DC_A_reg))
#define ISO_DC_A_inst_adr                                                            "0x002E"
#define ISO_DC_A_inst                                                                0x002E
#define ISO_DC_A_scpu_tee_ro_protect_en_shift                                        (28)
#define ISO_DC_A_scpu_tee_ro_protect_en_mask                                         (0x10000000)
#define ISO_DC_A_scpu_tee_ro_protect_en(data)                                        (0x10000000&((data)<<28))
#define ISO_DC_A_scpu_tee_ro_protect_en_src(data)                                    ((0x10000000&(data))>>28)
#define ISO_DC_A_get_scpu_tee_ro_protect_en(data)                                    ((0x10000000&(data))>>28)
#define ISO_DC_A_acpu_ro_protect_en_shift                                            (24)
#define ISO_DC_A_acpu_ro_protect_en_mask                                             (0x01000000)
#define ISO_DC_A_acpu_ro_protect_en(data)                                            (0x01000000&((data)<<24))
#define ISO_DC_A_acpu_ro_protect_en_src(data)                                        ((0x01000000&(data))>>24)
#define ISO_DC_A_get_acpu_ro_protect_en(data)                                        ((0x01000000&(data))>>24)
#define ISO_DC_A_video_ro_protect_en_shift                                           (20)
#define ISO_DC_A_video_ro_protect_en_mask                                            (0x00100000)
#define ISO_DC_A_video_ro_protect_en(data)                                           (0x00100000&((data)<<20))
#define ISO_DC_A_video_ro_protect_en_src(data)                                       ((0x00100000&(data))>>20)
#define ISO_DC_A_get_video_ro_protect_en(data)                                       ((0x00100000&(data))>>20)
#define ISO_DC_A_audio_ro_protect_en_shift                                           (16)
#define ISO_DC_A_audio_ro_protect_en_mask                                            (0x00010000)
#define ISO_DC_A_audio_ro_protect_en(data)                                           (0x00010000&((data)<<16))
#define ISO_DC_A_audio_ro_protect_en_src(data)                                       ((0x00010000&(data))>>16)
#define ISO_DC_A_get_audio_ro_protect_en(data)                                       ((0x00010000&(data))>>16)
#define ISO_DC_A_md_tee_ro_protect_en_shift                                          (12)
#define ISO_DC_A_md_tee_ro_protect_en_mask                                           (0x00001000)
#define ISO_DC_A_md_tee_ro_protect_en(data)                                          (0x00001000&((data)<<12))
#define ISO_DC_A_md_tee_ro_protect_en_src(data)                                      ((0x00001000&(data))>>12)
#define ISO_DC_A_get_md_tee_ro_protect_en(data)                                      ((0x00001000&(data))>>12)
#define ISO_DC_A_cp_tee_ro_protect_en_shift                                          (8)
#define ISO_DC_A_cp_tee_ro_protect_en_mask                                           (0x00000100)
#define ISO_DC_A_cp_tee_ro_protect_en(data)                                          (0x00000100&((data)<<8))
#define ISO_DC_A_cp_tee_ro_protect_en_src(data)                                      ((0x00000100&(data))>>8)
#define ISO_DC_A_get_cp_tee_ro_protect_en(data)                                      ((0x00000100&(data))>>8)
#define ISO_DC_A_vo_ro_protect_en_shift                                              (4)
#define ISO_DC_A_vo_ro_protect_en_mask                                               (0x00000010)
#define ISO_DC_A_vo_ro_protect_en(data)                                              (0x00000010&((data)<<4))
#define ISO_DC_A_vo_ro_protect_en_src(data)                                          ((0x00000010&(data))>>4)
#define ISO_DC_A_get_vo_ro_protect_en(data)                                          ((0x00000010&(data))>>4)
#define ISO_DC_A_nf_tee_ro_protect_en_shift                                          (0)
#define ISO_DC_A_nf_tee_ro_protect_en_mask                                           (0x00000001)
#define ISO_DC_A_nf_tee_ro_protect_en(data)                                          (0x00000001&((data)<<0))
#define ISO_DC_A_nf_tee_ro_protect_en_src(data)                                      ((0x00000001&(data))>>0)
#define ISO_DC_A_get_nf_tee_ro_protect_en(data)                                      ((0x00000001&(data))>>0)


#define ISO_PLL_XTAL_CTRL                                                            0x180070BC
#define ISO_PLL_XTAL_CTRL_reg_addr                                                   "0xB80070BC"
#define ISO_PLL_XTAL_CTRL_reg                                                        0xB80070BC
#define set_ISO_PLL_XTAL_CTRL_reg(data)   (*((volatile unsigned int*) ISO_PLL_XTAL_CTRL_reg)=data)
#define get_ISO_PLL_XTAL_CTRL_reg   (*((volatile unsigned int*) ISO_PLL_XTAL_CTRL_reg))
#define ISO_PLL_XTAL_CTRL_inst_adr                                                   "0x002F"
#define ISO_PLL_XTAL_CTRL_inst                                                       0x002F
#define ISO_PLL_XTAL_CTRL_xtal_pad_drv_shift                                         (0)
#define ISO_PLL_XTAL_CTRL_xtal_pad_drv_mask                                          (0x00000003)
#define ISO_PLL_XTAL_CTRL_xtal_pad_drv(data)                                         (0x00000003&((data)<<0))
#define ISO_PLL_XTAL_CTRL_xtal_pad_drv_src(data)                                     ((0x00000003&(data))>>0)
#define ISO_PLL_XTAL_CTRL_get_xtal_pad_drv(data)                                     ((0x00000003&(data))>>0)


#define ISO_I2C6_SDA_DEL                                                             0x180070C0
#define ISO_I2C6_SDA_DEL_reg_addr                                                    "0xB80070C0"
#define ISO_I2C6_SDA_DEL_reg                                                         0xB80070C0
#define set_ISO_I2C6_SDA_DEL_reg(data)   (*((volatile unsigned int*) ISO_I2C6_SDA_DEL_reg)=data)
#define get_ISO_I2C6_SDA_DEL_reg   (*((volatile unsigned int*) ISO_I2C6_SDA_DEL_reg))
#define ISO_I2C6_SDA_DEL_inst_adr                                                    "0x0030"
#define ISO_I2C6_SDA_DEL_inst                                                        0x0030
#define ISO_I2C6_SDA_DEL_dmy1_shift                                                  (12)
#define ISO_I2C6_SDA_DEL_dmy1_mask                                                   (0xFFFFF000)
#define ISO_I2C6_SDA_DEL_dmy1(data)                                                  (0xFFFFF000&((data)<<12))
#define ISO_I2C6_SDA_DEL_dmy1_src(data)                                              ((0xFFFFF000&(data))>>12)
#define ISO_I2C6_SDA_DEL_get_dmy1(data)                                              ((0xFFFFF000&(data))>>12)
#define ISO_I2C6_SDA_DEL_en_shift                                                    (8)
#define ISO_I2C6_SDA_DEL_en_mask                                                     (0x00000100)
#define ISO_I2C6_SDA_DEL_en(data)                                                    (0x00000100&((data)<<8))
#define ISO_I2C6_SDA_DEL_en_src(data)                                                ((0x00000100&(data))>>8)
#define ISO_I2C6_SDA_DEL_get_en(data)                                                ((0x00000100&(data))>>8)
#define ISO_I2C6_SDA_DEL_sel_shift                                                   (0)
#define ISO_I2C6_SDA_DEL_sel_mask                                                    (0x0000001F)
#define ISO_I2C6_SDA_DEL_sel(data)                                                   (0x0000001F&((data)<<0))
#define ISO_I2C6_SDA_DEL_sel_src(data)                                               ((0x0000001F&(data))>>0)
#define ISO_I2C6_SDA_DEL_get_sel(data)                                               ((0x0000001F&(data))>>0)


#define ISO_HDMI_RX                                                                  0x180070C4
#define ISO_HDMI_RX_reg_addr                                                         "0xB80070C4"
#define ISO_HDMI_RX_reg                                                              0xB80070C4
#define set_ISO_HDMI_RX_reg(data)   (*((volatile unsigned int*) ISO_HDMI_RX_reg)=data)
#define get_ISO_HDMI_RX_reg   (*((volatile unsigned int*) ISO_HDMI_RX_reg))
#define ISO_HDMI_RX_inst_adr                                                         "0x0031"
#define ISO_HDMI_RX_inst                                                             0x0031
#define ISO_HDMI_RX_int_option_shift                                                 (0)
#define ISO_HDMI_RX_int_option_mask                                                  (0x00000001)
#define ISO_HDMI_RX_int_option(data)                                                 (0x00000001&((data)<<0))
#define ISO_HDMI_RX_int_option_src(data)                                             ((0x00000001&(data))>>0)
#define ISO_HDMI_RX_get_int_option(data)                                             ((0x00000001&(data))>>0)


#define ISO_I2C6_MUX                                                                 0x180070C8
#define ISO_I2C6_MUX_reg_addr                                                        "0xB80070C8"
#define ISO_I2C6_MUX_reg                                                             0xB80070C8
#define set_ISO_I2C6_MUX_reg(data)   (*((volatile unsigned int*) ISO_I2C6_MUX_reg)=data)
#define get_ISO_I2C6_MUX_reg   (*((volatile unsigned int*) ISO_I2C6_MUX_reg))
#define ISO_I2C6_MUX_inst_adr                                                        "0x0032"
#define ISO_I2C6_MUX_inst                                                            0x0032
#define ISO_I2C6_MUX_i2c6_mis_mux_shift                                              (0)
#define ISO_I2C6_MUX_i2c6_mis_mux_mask                                               (0x00000001)
#define ISO_I2C6_MUX_i2c6_mis_mux(data)                                              (0x00000001&((data)<<0))
#define ISO_I2C6_MUX_i2c6_mis_mux_src(data)                                          ((0x00000001&(data))>>0)
#define ISO_I2C6_MUX_get_i2c6_mis_mux(data)                                          ((0x00000001&(data))>>0)


#define ISO_SB2_0                                                                    0x18007F00
#define ISO_SB2_0_reg_addr                                                           "0xB8007F00"
#define ISO_SB2_0_reg                                                                0xB8007F00
#define set_ISO_SB2_0_reg(data)   (*((volatile unsigned int*) ISO_SB2_0_reg)=data)
#define get_ISO_SB2_0_reg   (*((volatile unsigned int*) ISO_SB2_0_reg))
#define ISO_SB2_0_inst_adr                                                           "0x00C0"
#define ISO_SB2_0_inst                                                               0x00C0
#define ISO_SB2_0_usb2sram_ctrl_shift                                                (5)
#define ISO_SB2_0_usb2sram_ctrl_mask                                                 (0x00000020)
#define ISO_SB2_0_usb2sram_ctrl(data)                                                (0x00000020&((data)<<5))
#define ISO_SB2_0_usb2sram_ctrl_src(data)                                            ((0x00000020&(data))>>5)
#define ISO_SB2_0_get_usb2sram_ctrl(data)                                            ((0x00000020&(data))>>5)
#define ISO_SB2_0_ve_encode_block_nwc_shift                                          (4)
#define ISO_SB2_0_ve_encode_block_nwc_mask                                           (0x00000010)
#define ISO_SB2_0_ve_encode_block_nwc(data)                                          (0x00000010&((data)<<4))
#define ISO_SB2_0_ve_encode_block_nwc_src(data)                                      ((0x00000010&(data))>>4)
#define ISO_SB2_0_get_ve_encode_block_nwc(data)                                      ((0x00000010&(data))>>4)
#define ISO_SB2_0_ve_block_nwc_shift                                                 (3)
#define ISO_SB2_0_ve_block_nwc_mask                                                  (0x00000008)
#define ISO_SB2_0_ve_block_nwc(data)                                                 (0x00000008&((data)<<3))
#define ISO_SB2_0_ve_block_nwc_src(data)                                             ((0x00000008&(data))>>3)
#define ISO_SB2_0_get_ve_block_nwc(data)                                             ((0x00000008&(data))>>3)
#define ISO_SB2_0_vo_block_nwc_shift                                                 (2)
#define ISO_SB2_0_vo_block_nwc_mask                                                  (0x00000004)
#define ISO_SB2_0_vo_block_nwc(data)                                                 (0x00000004&((data)<<2))
#define ISO_SB2_0_vo_block_nwc_src(data)                                             ((0x00000004&(data))>>2)
#define ISO_SB2_0_get_vo_block_nwc(data)                                             ((0x00000004&(data))>>2)
#define ISO_SB2_0_dc_mem_port_lock_shift                                             (1)
#define ISO_SB2_0_dc_mem_port_lock_mask                                              (0x00000002)
#define ISO_SB2_0_dc_mem_port_lock(data)                                             (0x00000002&((data)<<1))
#define ISO_SB2_0_dc_mem_port_lock_src(data)                                         ((0x00000002&(data))>>1)
#define ISO_SB2_0_get_dc_mem_port_lock(data)                                         ((0x00000002&(data))>>1)
#define ISO_SB2_0_secure_rbus_shift                                                  (0)
#define ISO_SB2_0_secure_rbus_mask                                                   (0x00000001)
#define ISO_SB2_0_secure_rbus(data)                                                  (0x00000001&((data)<<0))
#define ISO_SB2_0_secure_rbus_src(data)                                              ((0x00000001&(data))>>0)
#define ISO_SB2_0_get_secure_rbus(data)                                              ((0x00000001&(data))>>0)


#define ISO_GPDIR                                                                    0x18007100
#define ISO_GPDIR_reg_addr                                                           "0xB8007100"
#define ISO_GPDIR_reg                                                                0xB8007100
#define set_ISO_GPDIR_reg(data)   (*((volatile unsigned int*) ISO_GPDIR_reg)=data)
#define get_ISO_GPDIR_reg   (*((volatile unsigned int*) ISO_GPDIR_reg))
#define ISO_GPDIR_inst_adr                                                           "0x0040"
#define ISO_GPDIR_inst                                                               0x0040
#define ISO_GPDIR_gpdir_shift                                                        (0)
#define ISO_GPDIR_gpdir_mask                                                         (0x001FFFFF)
#define ISO_GPDIR_gpdir(data)                                                        (0x001FFFFF&((data)<<0))
#define ISO_GPDIR_gpdir_src(data)                                                    ((0x001FFFFF&(data))>>0)
#define ISO_GPDIR_get_gpdir(data)                                                    ((0x001FFFFF&(data))>>0)


#define ISO_GPDATO                                                                   0x18007104
#define ISO_GPDATO_reg_addr                                                          "0xB8007104"
#define ISO_GPDATO_reg                                                               0xB8007104
#define set_ISO_GPDATO_reg(data)   (*((volatile unsigned int*) ISO_GPDATO_reg)=data)
#define get_ISO_GPDATO_reg   (*((volatile unsigned int*) ISO_GPDATO_reg))
#define ISO_GPDATO_inst_adr                                                          "0x0041"
#define ISO_GPDATO_inst                                                              0x0041
#define ISO_GPDATO_gpdato_shift                                                      (0)
#define ISO_GPDATO_gpdato_mask                                                       (0x001FFFFF)
#define ISO_GPDATO_gpdato(data)                                                      (0x001FFFFF&((data)<<0))
#define ISO_GPDATO_gpdato_src(data)                                                  ((0x001FFFFF&(data))>>0)
#define ISO_GPDATO_get_gpdato(data)                                                  ((0x001FFFFF&(data))>>0)


#define ISO_GPDATI                                                                   0x18007108
#define ISO_GPDATI_reg_addr                                                          "0xB8007108"
#define ISO_GPDATI_reg                                                               0xB8007108
#define set_ISO_GPDATI_reg(data)   (*((volatile unsigned int*) ISO_GPDATI_reg)=data)
#define get_ISO_GPDATI_reg   (*((volatile unsigned int*) ISO_GPDATI_reg))
#define ISO_GPDATI_inst_adr                                                          "0x0042"
#define ISO_GPDATI_inst                                                              0x0042
#define ISO_GPDATI_gpdati_shift                                                      (0)
#define ISO_GPDATI_gpdati_mask                                                       (0x001FFFFF)
#define ISO_GPDATI_gpdati(data)                                                      (0x001FFFFF&((data)<<0))
#define ISO_GPDATI_gpdati_src(data)                                                  ((0x001FFFFF&(data))>>0)
#define ISO_GPDATI_get_gpdati(data)                                                  ((0x001FFFFF&(data))>>0)


#define ISO_GPIE                                                                     0x1800710C
#define ISO_GPIE_reg_addr                                                            "0xB800710C"
#define ISO_GPIE_reg                                                                 0xB800710C
#define set_ISO_GPIE_reg(data)   (*((volatile unsigned int*) ISO_GPIE_reg)=data)
#define get_ISO_GPIE_reg   (*((volatile unsigned int*) ISO_GPIE_reg))
#define ISO_GPIE_inst_adr                                                            "0x0043"
#define ISO_GPIE_inst                                                                0x0043
#define ISO_GPIE_gp_shift                                                            (0)
#define ISO_GPIE_gp_mask                                                             (0x001FFFFF)
#define ISO_GPIE_gp(data)                                                            (0x001FFFFF&((data)<<0))
#define ISO_GPIE_gp_src(data)                                                        ((0x001FFFFF&(data))>>0)
#define ISO_GPIE_get_gp(data)                                                        ((0x001FFFFF&(data))>>0)


#define ISO_GPDP                                                                     0x18007110
#define ISO_GPDP_reg_addr                                                            "0xB8007110"
#define ISO_GPDP_reg                                                                 0xB8007110
#define set_ISO_GPDP_reg(data)   (*((volatile unsigned int*) ISO_GPDP_reg)=data)
#define get_ISO_GPDP_reg   (*((volatile unsigned int*) ISO_GPDP_reg))
#define ISO_GPDP_inst_adr                                                            "0x0044"
#define ISO_GPDP_inst                                                                0x0044
#define ISO_GPDP_gpha_shift                                                          (0)
#define ISO_GPDP_gpha_mask                                                           (0x001FFFFF)
#define ISO_GPDP_gpha(data)                                                          (0x001FFFFF&((data)<<0))
#define ISO_GPDP_gpha_src(data)                                                      ((0x001FFFFF&(data))>>0)
#define ISO_GPDP_get_gpha(data)                                                      ((0x001FFFFF&(data))>>0)


#define ISO_GPDEB                                                                    0x18007114
#define ISO_GPDEB_reg_addr                                                           "0xB8007114"
#define ISO_GPDEB_reg                                                                0xB8007114
#define set_ISO_GPDEB_reg(data)   (*((volatile unsigned int*) ISO_GPDEB_reg)=data)
#define get_ISO_GPDEB_reg   (*((volatile unsigned int*) ISO_GPDEB_reg))
#define ISO_GPDEB_inst_adr                                                           "0x0045"
#define ISO_GPDEB_inst                                                               0x0045
#define ISO_GPDEB_write_en1_shift                                                    (3)
#define ISO_GPDEB_write_en1_mask                                                     (0x00000008)
#define ISO_GPDEB_write_en1(data)                                                    (0x00000008&((data)<<3))
#define ISO_GPDEB_write_en1_src(data)                                                ((0x00000008&(data))>>3)
#define ISO_GPDEB_get_write_en1(data)                                                ((0x00000008&(data))>>3)
#define ISO_GPDEB_clk1_shift                                                         (0)
#define ISO_GPDEB_clk1_mask                                                          (0x00000007)
#define ISO_GPDEB_clk1(data)                                                         (0x00000007&((data)<<0))
#define ISO_GPDEB_clk1_src(data)                                                     ((0x00000007&(data))>>0)
#define ISO_GPDEB_get_clk1(data)                                                     ((0x00000007&(data))>>0)


#define ISO_VFD_CTL                                                                  0x18007200
#define ISO_VFD_CTL_reg_addr                                                         "0xB8007200"
#define ISO_VFD_CTL_reg                                                              0xB8007200
#define set_ISO_VFD_CTL_reg(data)   (*((volatile unsigned int*) ISO_VFD_CTL_reg)=data)
#define get_ISO_VFD_CTL_reg   (*((volatile unsigned int*) ISO_VFD_CTL_reg))
#define ISO_VFD_CTL_inst_adr                                                         "0x0080"
#define ISO_VFD_CTL_inst                                                             0x0080
#define ISO_VFD_CTL_kpaden_shift                                                     (3)
#define ISO_VFD_CTL_kpaden_mask                                                      (0x00000008)
#define ISO_VFD_CTL_kpaden(data)                                                     (0x00000008&((data)<<3))
#define ISO_VFD_CTL_kpaden_src(data)                                                 ((0x00000008&(data))>>3)
#define ISO_VFD_CTL_get_kpaden(data)                                                 ((0x00000008&(data))>>3)
#define ISO_VFD_CTL_swen_shift                                                       (2)
#define ISO_VFD_CTL_swen_mask                                                        (0x00000004)
#define ISO_VFD_CTL_swen(data)                                                       (0x00000004&((data)<<2))
#define ISO_VFD_CTL_swen_src(data)                                                   ((0x00000004&(data))>>2)
#define ISO_VFD_CTL_get_swen(data)                                                   ((0x00000004&(data))>>2)
#define ISO_VFD_CTL_clksel_shift                                                     (1)
#define ISO_VFD_CTL_clksel_mask                                                      (0x00000002)
#define ISO_VFD_CTL_clksel(data)                                                     (0x00000002&((data)<<1))
#define ISO_VFD_CTL_clksel_src(data)                                                 ((0x00000002&(data))>>1)
#define ISO_VFD_CTL_get_clksel(data)                                                 ((0x00000002&(data))>>1)
#define ISO_VFD_CTL_envfd_shift                                                      (0)
#define ISO_VFD_CTL_envfd_mask                                                       (0x00000001)
#define ISO_VFD_CTL_envfd(data)                                                      (0x00000001&((data)<<0))
#define ISO_VFD_CTL_envfd_src(data)                                                  ((0x00000001&(data))>>0)
#define ISO_VFD_CTL_get_envfd(data)                                                  ((0x00000001&(data))>>0)


#define ISO_VFD_WRCTL                                                                0x18007204
#define ISO_VFD_WRCTL_reg_addr                                                       "0xB8007204"
#define ISO_VFD_WRCTL_reg                                                            0xB8007204
#define set_ISO_VFD_WRCTL_reg(data)   (*((volatile unsigned int*) ISO_VFD_WRCTL_reg)=data)
#define get_ISO_VFD_WRCTL_reg   (*((volatile unsigned int*) ISO_VFD_WRCTL_reg))
#define ISO_VFD_WRCTL_inst_adr                                                       "0x0081"
#define ISO_VFD_WRCTL_inst                                                           0x0081
#define ISO_VFD_WRCTL_nact_csn_shift                                                 (12)
#define ISO_VFD_WRCTL_nact_csn_mask                                                  (0x00001000)
#define ISO_VFD_WRCTL_nact_csn(data)                                                 (0x00001000&((data)<<12))
#define ISO_VFD_WRCTL_nact_csn_src(data)                                             ((0x00001000&(data))>>12)
#define ISO_VFD_WRCTL_get_nact_csn(data)                                             ((0x00001000&(data))>>12)
#define ISO_VFD_WRCTL_b3c_shift                                                      (11)
#define ISO_VFD_WRCTL_b3c_mask                                                       (0x00000800)
#define ISO_VFD_WRCTL_b3c(data)                                                      (0x00000800&((data)<<11))
#define ISO_VFD_WRCTL_b3c_src(data)                                                  ((0x00000800&(data))>>11)
#define ISO_VFD_WRCTL_get_b3c(data)                                                  ((0x00000800&(data))>>11)
#define ISO_VFD_WRCTL_b2c_shift                                                      (10)
#define ISO_VFD_WRCTL_b2c_mask                                                       (0x00000400)
#define ISO_VFD_WRCTL_b2c(data)                                                      (0x00000400&((data)<<10))
#define ISO_VFD_WRCTL_b2c_src(data)                                                  ((0x00000400&(data))>>10)
#define ISO_VFD_WRCTL_get_b2c(data)                                                  ((0x00000400&(data))>>10)
#define ISO_VFD_WRCTL_b1c_shift                                                      (9)
#define ISO_VFD_WRCTL_b1c_mask                                                       (0x00000200)
#define ISO_VFD_WRCTL_b1c(data)                                                      (0x00000200&((data)<<9))
#define ISO_VFD_WRCTL_b1c_src(data)                                                  ((0x00000200&(data))>>9)
#define ISO_VFD_WRCTL_get_b1c(data)                                                  ((0x00000200&(data))>>9)
#define ISO_VFD_WRCTL_b0c_shift                                                      (8)
#define ISO_VFD_WRCTL_b0c_mask                                                       (0x00000100)
#define ISO_VFD_WRCTL_b0c(data)                                                      (0x00000100&((data)<<8))
#define ISO_VFD_WRCTL_b0c_src(data)                                                  ((0x00000100&(data))>>8)
#define ISO_VFD_WRCTL_get_b0c(data)                                                  ((0x00000100&(data))>>8)
#define ISO_VFD_WRCTL_enb3_shift                                                     (7)
#define ISO_VFD_WRCTL_enb3_mask                                                      (0x00000080)
#define ISO_VFD_WRCTL_enb3(data)                                                     (0x00000080&((data)<<7))
#define ISO_VFD_WRCTL_enb3_src(data)                                                 ((0x00000080&(data))>>7)
#define ISO_VFD_WRCTL_get_enb3(data)                                                 ((0x00000080&(data))>>7)
#define ISO_VFD_WRCTL_enb2_shift                                                     (6)
#define ISO_VFD_WRCTL_enb2_mask                                                      (0x00000040)
#define ISO_VFD_WRCTL_enb2(data)                                                     (0x00000040&((data)<<6))
#define ISO_VFD_WRCTL_enb2_src(data)                                                 ((0x00000040&(data))>>6)
#define ISO_VFD_WRCTL_get_enb2(data)                                                 ((0x00000040&(data))>>6)
#define ISO_VFD_WRCTL_enb1_shift                                                     (5)
#define ISO_VFD_WRCTL_enb1_mask                                                      (0x00000020)
#define ISO_VFD_WRCTL_enb1(data)                                                     (0x00000020&((data)<<5))
#define ISO_VFD_WRCTL_enb1_src(data)                                                 ((0x00000020&(data))>>5)
#define ISO_VFD_WRCTL_get_enb1(data)                                                 ((0x00000020&(data))>>5)
#define ISO_VFD_WRCTL_enb0_shift                                                     (4)
#define ISO_VFD_WRCTL_enb0_mask                                                      (0x00000010)
#define ISO_VFD_WRCTL_enb0(data)                                                     (0x00000010&((data)<<4))
#define ISO_VFD_WRCTL_enb0_src(data)                                                 ((0x00000010&(data))>>4)
#define ISO_VFD_WRCTL_get_enb0(data)                                                 ((0x00000010&(data))>>4)
#define ISO_VFD_WRCTL_wd_shift                                                       (1)
#define ISO_VFD_WRCTL_wd_mask                                                        (0x00000002)
#define ISO_VFD_WRCTL_wd(data)                                                       (0x00000002&((data)<<1))
#define ISO_VFD_WRCTL_wd_src(data)                                                   ((0x00000002&(data))>>1)
#define ISO_VFD_WRCTL_get_wd(data)                                                   ((0x00000002&(data))>>1)
#define ISO_VFD_WRCTL_wdie_shift                                                     (0)
#define ISO_VFD_WRCTL_wdie_mask                                                      (0x00000001)
#define ISO_VFD_WRCTL_wdie(data)                                                     (0x00000001&((data)<<0))
#define ISO_VFD_WRCTL_wdie_src(data)                                                 ((0x00000001&(data))>>0)
#define ISO_VFD_WRCTL_get_wdie(data)                                                 ((0x00000001&(data))>>0)


#define ISO_VFDO                                                                     0x18007208
#define ISO_VFDO_reg_addr                                                            "0xB8007208"
#define ISO_VFDO_reg                                                                 0xB8007208
#define set_ISO_VFDO_reg(data)   (*((volatile unsigned int*) ISO_VFDO_reg)=data)
#define get_ISO_VFDO_reg   (*((volatile unsigned int*) ISO_VFDO_reg))
#define ISO_VFDO_inst_adr                                                            "0x0082"
#define ISO_VFDO_inst                                                                0x0082
#define ISO_VFDO_byte3_shift                                                         (24)
#define ISO_VFDO_byte3_mask                                                          (0xFF000000)
#define ISO_VFDO_byte3(data)                                                         (0xFF000000&((data)<<24))
#define ISO_VFDO_byte3_src(data)                                                     ((0xFF000000&(data))>>24)
#define ISO_VFDO_get_byte3(data)                                                     ((0xFF000000&(data))>>24)
#define ISO_VFDO_byte2_shift                                                         (16)
#define ISO_VFDO_byte2_mask                                                          (0x00FF0000)
#define ISO_VFDO_byte2(data)                                                         (0x00FF0000&((data)<<16))
#define ISO_VFDO_byte2_src(data)                                                     ((0x00FF0000&(data))>>16)
#define ISO_VFDO_get_byte2(data)                                                     ((0x00FF0000&(data))>>16)
#define ISO_VFDO_byte1_shift                                                         (8)
#define ISO_VFDO_byte1_mask                                                          (0x0000FF00)
#define ISO_VFDO_byte1(data)                                                         (0x0000FF00&((data)<<8))
#define ISO_VFDO_byte1_src(data)                                                     ((0x0000FF00&(data))>>8)
#define ISO_VFDO_get_byte1(data)                                                     ((0x0000FF00&(data))>>8)
#define ISO_VFDO_byte0_shift                                                         (0)
#define ISO_VFDO_byte0_mask                                                          (0x000000FF)
#define ISO_VFDO_byte0(data)                                                         (0x000000FF&((data)<<0))
#define ISO_VFDO_byte0_src(data)                                                     ((0x000000FF&(data))>>0)
#define ISO_VFDO_get_byte0(data)                                                     ((0x000000FF&(data))>>0)


#define ISO_VFD_ARDCTL                                                               0x1800720C
#define ISO_VFD_ARDCTL_reg_addr                                                      "0xB800720C"
#define ISO_VFD_ARDCTL_reg                                                           0xB800720C
#define set_ISO_VFD_ARDCTL_reg(data)   (*((volatile unsigned int*) ISO_VFD_ARDCTL_reg)=data)
#define get_ISO_VFD_ARDCTL_reg   (*((volatile unsigned int*) ISO_VFD_ARDCTL_reg))
#define ISO_VFD_ARDCTL_inst_adr                                                      "0x0083"
#define ISO_VFD_ARDCTL_inst                                                          0x0083
#define ISO_VFD_ARDCTL_kpadbn_shift                                                  (8)
#define ISO_VFD_ARDCTL_kpadbn_mask                                                   (0x00000700)
#define ISO_VFD_ARDCTL_kpadbn(data)                                                  (0x00000700&((data)<<8))
#define ISO_VFD_ARDCTL_kpadbn_src(data)                                              ((0x00000700&(data))>>8)
#define ISO_VFD_ARDCTL_get_kpadbn(data)                                              ((0x00000700&(data))>>8)
#define ISO_VFD_ARDCTL_swha_shift                                                    (5)
#define ISO_VFD_ARDCTL_swha_mask                                                     (0x00000020)
#define ISO_VFD_ARDCTL_swha(data)                                                    (0x00000020&((data)<<5))
#define ISO_VFD_ARDCTL_swha_src(data)                                                ((0x00000020&(data))>>5)
#define ISO_VFD_ARDCTL_get_swha(data)                                                ((0x00000020&(data))>>5)
#define ISO_VFD_ARDCTL_kpadha_shift                                                  (4)
#define ISO_VFD_ARDCTL_kpadha_mask                                                   (0x00000010)
#define ISO_VFD_ARDCTL_kpadha(data)                                                  (0x00000010&((data)<<4))
#define ISO_VFD_ARDCTL_kpadha_src(data)                                              ((0x00000010&(data))>>4)
#define ISO_VFD_ARDCTL_get_kpadha(data)                                              ((0x00000010&(data))>>4)
#define ISO_VFD_ARDCTL_ardp_shift                                                    (0)
#define ISO_VFD_ARDCTL_ardp_mask                                                     (0x00000003)
#define ISO_VFD_ARDCTL_ardp(data)                                                    (0x00000003&((data)<<0))
#define ISO_VFD_ARDCTL_ardp_src(data)                                                ((0x00000003&(data))>>0)
#define ISO_VFD_ARDCTL_get_ardp(data)                                                ((0x00000003&(data))>>0)


#define ISO_VFD_KPADLIE                                                              0x18007210
#define ISO_VFD_KPADLIE_reg_addr                                                     "0xB8007210"
#define ISO_VFD_KPADLIE_reg                                                          0xB8007210
#define set_ISO_VFD_KPADLIE_reg(data)   (*((volatile unsigned int*) ISO_VFD_KPADLIE_reg)=data)
#define get_ISO_VFD_KPADLIE_reg   (*((volatile unsigned int*) ISO_VFD_KPADLIE_reg))
#define ISO_VFD_KPADLIE_inst_adr                                                     "0x0084"
#define ISO_VFD_KPADLIE_inst                                                         0x0084
#define ISO_VFD_KPADLIE_kpadie_shift                                                 (0)
#define ISO_VFD_KPADLIE_kpadie_mask                                                  (0xFFFFFFFF)
#define ISO_VFD_KPADLIE_kpadie(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ISO_VFD_KPADLIE_kpadie_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ISO_VFD_KPADLIE_get_kpadie(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ISO_VFD_KPADHIE                                                              0x18007214
#define ISO_VFD_KPADHIE_reg_addr                                                     "0xB8007214"
#define ISO_VFD_KPADHIE_reg                                                          0xB8007214
#define set_ISO_VFD_KPADHIE_reg(data)   (*((volatile unsigned int*) ISO_VFD_KPADHIE_reg)=data)
#define get_ISO_VFD_KPADHIE_reg   (*((volatile unsigned int*) ISO_VFD_KPADHIE_reg))
#define ISO_VFD_KPADHIE_inst_adr                                                     "0x0085"
#define ISO_VFD_KPADHIE_inst                                                         0x0085
#define ISO_VFD_KPADHIE_kpadie_shift                                                 (0)
#define ISO_VFD_KPADHIE_kpadie_mask                                                  (0x0000FFFF)
#define ISO_VFD_KPADHIE_kpadie(data)                                                 (0x0000FFFF&((data)<<0))
#define ISO_VFD_KPADHIE_kpadie_src(data)                                             ((0x0000FFFF&(data))>>0)
#define ISO_VFD_KPADHIE_get_kpadie(data)                                             ((0x0000FFFF&(data))>>0)


#define ISO_VFD_SWIE                                                                 0x18007218
#define ISO_VFD_SWIE_reg_addr                                                        "0xB8007218"
#define ISO_VFD_SWIE_reg                                                             0xB8007218
#define set_ISO_VFD_SWIE_reg(data)   (*((volatile unsigned int*) ISO_VFD_SWIE_reg)=data)
#define get_ISO_VFD_SWIE_reg   (*((volatile unsigned int*) ISO_VFD_SWIE_reg))
#define ISO_VFD_SWIE_inst_adr                                                        "0x0086"
#define ISO_VFD_SWIE_inst                                                            0x0086
#define ISO_VFD_SWIE_swie_shift                                                      (0)
#define ISO_VFD_SWIE_swie_mask                                                       (0x0000000F)
#define ISO_VFD_SWIE_swie(data)                                                      (0x0000000F&((data)<<0))
#define ISO_VFD_SWIE_swie_src(data)                                                  ((0x0000000F&(data))>>0)
#define ISO_VFD_SWIE_get_swie(data)                                                  ((0x0000000F&(data))>>0)


#define ISO_VFD_ARDKPADL                                                             0x1800721C
#define ISO_VFD_ARDKPADL_reg_addr                                                    "0xB800721C"
#define ISO_VFD_ARDKPADL_reg                                                         0xB800721C
#define set_ISO_VFD_ARDKPADL_reg(data)   (*((volatile unsigned int*) ISO_VFD_ARDKPADL_reg)=data)
#define get_ISO_VFD_ARDKPADL_reg   (*((volatile unsigned int*) ISO_VFD_ARDKPADL_reg))
#define ISO_VFD_ARDKPADL_inst_adr                                                    "0x0087"
#define ISO_VFD_ARDKPADL_inst                                                        0x0087
#define ISO_VFD_ARDKPADL_st_31_24_shift                                              (24)
#define ISO_VFD_ARDKPADL_st_31_24_mask                                               (0xFF000000)
#define ISO_VFD_ARDKPADL_st_31_24(data)                                              (0xFF000000&((data)<<24))
#define ISO_VFD_ARDKPADL_st_31_24_src(data)                                          ((0xFF000000&(data))>>24)
#define ISO_VFD_ARDKPADL_get_st_31_24(data)                                          ((0xFF000000&(data))>>24)
#define ISO_VFD_ARDKPADL_st_23_16_shift                                              (16)
#define ISO_VFD_ARDKPADL_st_23_16_mask                                               (0x00FF0000)
#define ISO_VFD_ARDKPADL_st_23_16(data)                                              (0x00FF0000&((data)<<16))
#define ISO_VFD_ARDKPADL_st_23_16_src(data)                                          ((0x00FF0000&(data))>>16)
#define ISO_VFD_ARDKPADL_get_st_23_16(data)                                          ((0x00FF0000&(data))>>16)
#define ISO_VFD_ARDKPADL_st_15_8_shift                                               (8)
#define ISO_VFD_ARDKPADL_st_15_8_mask                                                (0x0000FF00)
#define ISO_VFD_ARDKPADL_st_15_8(data)                                               (0x0000FF00&((data)<<8))
#define ISO_VFD_ARDKPADL_st_15_8_src(data)                                           ((0x0000FF00&(data))>>8)
#define ISO_VFD_ARDKPADL_get_st_15_8(data)                                           ((0x0000FF00&(data))>>8)
#define ISO_VFD_ARDKPADL_st_7_0_shift                                                (0)
#define ISO_VFD_ARDKPADL_st_7_0_mask                                                 (0x000000FF)
#define ISO_VFD_ARDKPADL_st_7_0(data)                                                (0x000000FF&((data)<<0))
#define ISO_VFD_ARDKPADL_st_7_0_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_VFD_ARDKPADL_get_st_7_0(data)                                            ((0x000000FF&(data))>>0)


#define ISO_VFD_ARDKPADH                                                             0x18007220
#define ISO_VFD_ARDKPADH_reg_addr                                                    "0xB8007220"
#define ISO_VFD_ARDKPADH_reg                                                         0xB8007220
#define set_ISO_VFD_ARDKPADH_reg(data)   (*((volatile unsigned int*) ISO_VFD_ARDKPADH_reg)=data)
#define get_ISO_VFD_ARDKPADH_reg   (*((volatile unsigned int*) ISO_VFD_ARDKPADH_reg))
#define ISO_VFD_ARDKPADH_inst_adr                                                    "0x0088"
#define ISO_VFD_ARDKPADH_inst                                                        0x0088
#define ISO_VFD_ARDKPADH_st_15_8_shift                                               (8)
#define ISO_VFD_ARDKPADH_st_15_8_mask                                                (0x0000FF00)
#define ISO_VFD_ARDKPADH_st_15_8(data)                                               (0x0000FF00&((data)<<8))
#define ISO_VFD_ARDKPADH_st_15_8_src(data)                                           ((0x0000FF00&(data))>>8)
#define ISO_VFD_ARDKPADH_get_st_15_8(data)                                           ((0x0000FF00&(data))>>8)
#define ISO_VFD_ARDKPADH_st_7_0_shift                                                (0)
#define ISO_VFD_ARDKPADH_st_7_0_mask                                                 (0x000000FF)
#define ISO_VFD_ARDKPADH_st_7_0(data)                                                (0x000000FF&((data)<<0))
#define ISO_VFD_ARDKPADH_st_7_0_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_VFD_ARDKPADH_get_st_7_0(data)                                            ((0x000000FF&(data))>>0)


#define ISO_VFD_ARDSW                                                                0x18007224
#define ISO_VFD_ARDSW_reg_addr                                                       "0xB8007224"
#define ISO_VFD_ARDSW_reg                                                            0xB8007224
#define set_ISO_VFD_ARDSW_reg(data)   (*((volatile unsigned int*) ISO_VFD_ARDSW_reg)=data)
#define get_ISO_VFD_ARDSW_reg   (*((volatile unsigned int*) ISO_VFD_ARDSW_reg))
#define ISO_VFD_ARDSW_inst_adr                                                       "0x0089"
#define ISO_VFD_ARDSW_inst                                                           0x0089
#define ISO_VFD_ARDSW_rvda_shift                                                     (4)
#define ISO_VFD_ARDSW_rvda_mask                                                      (0x0000FFF0)
#define ISO_VFD_ARDSW_rvda(data)                                                     (0x0000FFF0&((data)<<4))
#define ISO_VFD_ARDSW_rvda_src(data)                                                 ((0x0000FFF0&(data))>>4)
#define ISO_VFD_ARDSW_get_rvda(data)                                                 ((0x0000FFF0&(data))>>4)
#define ISO_VFD_ARDSW_st_shift                                                       (0)
#define ISO_VFD_ARDSW_st_mask                                                        (0x0000000F)
#define ISO_VFD_ARDSW_st(data)                                                       (0x0000000F&((data)<<0))
#define ISO_VFD_ARDSW_st_src(data)                                                   ((0x0000000F&(data))>>0)
#define ISO_VFD_ARDSW_get_st(data)                                                   ((0x0000000F&(data))>>0)


#define ISO_VFD_CTL1                                                                 0x18007228
#define ISO_VFD_CTL1_reg_addr                                                        "0xB8007228"
#define ISO_VFD_CTL1_reg                                                             0xB8007228
#define set_ISO_VFD_CTL1_reg(data)   (*((volatile unsigned int*) ISO_VFD_CTL1_reg)=data)
#define get_ISO_VFD_CTL1_reg   (*((volatile unsigned int*) ISO_VFD_CTL1_reg))
#define ISO_VFD_CTL1_inst_adr                                                        "0x008A"
#define ISO_VFD_CTL1_inst                                                            0x008A
#define ISO_VFD_CTL1_clksel_1_shift                                                  (16)
#define ISO_VFD_CTL1_clksel_1_mask                                                   (0x00010000)
#define ISO_VFD_CTL1_clksel_1(data)                                                  (0x00010000&((data)<<16))
#define ISO_VFD_CTL1_clksel_1_src(data)                                              ((0x00010000&(data))>>16)
#define ISO_VFD_CTL1_get_clksel_1(data)                                              ((0x00010000&(data))>>16)
#define ISO_VFD_CTL1_tclk_csn_shift                                                  (8)
#define ISO_VFD_CTL1_tclk_csn_mask                                                   (0x0000FF00)
#define ISO_VFD_CTL1_tclk_csn(data)                                                  (0x0000FF00&((data)<<8))
#define ISO_VFD_CTL1_tclk_csn_src(data)                                              ((0x0000FF00&(data))>>8)
#define ISO_VFD_CTL1_get_tclk_csn(data)                                              ((0x0000FF00&(data))>>8)
#define ISO_VFD_CTL1_twait1_shift                                                    (0)
#define ISO_VFD_CTL1_twait1_mask                                                     (0x000000FF)
#define ISO_VFD_CTL1_twait1(data)                                                    (0x000000FF&((data)<<0))
#define ISO_VFD_CTL1_twait1_src(data)                                                ((0x000000FF&(data))>>0)
#define ISO_VFD_CTL1_get_twait1(data)                                                ((0x000000FF&(data))>>0)


#define ISO_PFUNC0                                                                   0x18007300
#define ISO_PFUNC0_reg_addr                                                          "0xB8007300"
#define ISO_PFUNC0_reg                                                               0xB8007300
#define set_ISO_PFUNC0_reg(data)   (*((volatile unsigned int*) ISO_PFUNC0_reg)=data)
#define get_ISO_PFUNC0_reg   (*((volatile unsigned int*) ISO_PFUNC0_reg))
#define ISO_PFUNC0_inst_adr                                                          "0x00C0"
#define ISO_PFUNC0_inst                                                              0x00C0
#define ISO_PFUNC0_i2c_scl_0_smt_shift                                               (31)
#define ISO_PFUNC0_i2c_scl_0_smt_mask                                                (0x80000000)
#define ISO_PFUNC0_i2c_scl_0_smt(data)                                               (0x80000000&((data)<<31))
#define ISO_PFUNC0_i2c_scl_0_smt_src(data)                                           ((0x80000000&(data))>>31)
#define ISO_PFUNC0_get_i2c_scl_0_smt(data)                                           ((0x80000000&(data))>>31)
#define ISO_PFUNC0_i2c_scl_0_e2_shift                                                (30)
#define ISO_PFUNC0_i2c_scl_0_e2_mask                                                 (0x40000000)
#define ISO_PFUNC0_i2c_scl_0_e2(data)                                                (0x40000000&((data)<<30))
#define ISO_PFUNC0_i2c_scl_0_e2_src(data)                                            ((0x40000000&(data))>>30)
#define ISO_PFUNC0_get_i2c_scl_0_e2(data)                                            ((0x40000000&(data))>>30)
#define ISO_PFUNC0_i2c_scl_0_pud_en_shift                                            (29)
#define ISO_PFUNC0_i2c_scl_0_pud_en_mask                                             (0x20000000)
#define ISO_PFUNC0_i2c_scl_0_pud_en(data)                                            (0x20000000&((data)<<29))
#define ISO_PFUNC0_i2c_scl_0_pud_en_src(data)                                        ((0x20000000&(data))>>29)
#define ISO_PFUNC0_get_i2c_scl_0_pud_en(data)                                        ((0x20000000&(data))>>29)
#define ISO_PFUNC0_i2c_scl_0_pud_sel_shift                                           (28)
#define ISO_PFUNC0_i2c_scl_0_pud_sel_mask                                            (0x10000000)
#define ISO_PFUNC0_i2c_scl_0_pud_sel(data)                                           (0x10000000&((data)<<28))
#define ISO_PFUNC0_i2c_scl_0_pud_sel_src(data)                                       ((0x10000000&(data))>>28)
#define ISO_PFUNC0_get_i2c_scl_0_pud_sel(data)                                       ((0x10000000&(data))>>28)
#define ISO_PFUNC0_i2c_sda_0_smt_shift                                               (27)
#define ISO_PFUNC0_i2c_sda_0_smt_mask                                                (0x08000000)
#define ISO_PFUNC0_i2c_sda_0_smt(data)                                               (0x08000000&((data)<<27))
#define ISO_PFUNC0_i2c_sda_0_smt_src(data)                                           ((0x08000000&(data))>>27)
#define ISO_PFUNC0_get_i2c_sda_0_smt(data)                                           ((0x08000000&(data))>>27)
#define ISO_PFUNC0_i2c_sda_0_e2_shift                                                (26)
#define ISO_PFUNC0_i2c_sda_0_e2_mask                                                 (0x04000000)
#define ISO_PFUNC0_i2c_sda_0_e2(data)                                                (0x04000000&((data)<<26))
#define ISO_PFUNC0_i2c_sda_0_e2_src(data)                                            ((0x04000000&(data))>>26)
#define ISO_PFUNC0_get_i2c_sda_0_e2(data)                                            ((0x04000000&(data))>>26)
#define ISO_PFUNC0_i2c_sda_0_pud_en_shift                                            (25)
#define ISO_PFUNC0_i2c_sda_0_pud_en_mask                                             (0x02000000)
#define ISO_PFUNC0_i2c_sda_0_pud_en(data)                                            (0x02000000&((data)<<25))
#define ISO_PFUNC0_i2c_sda_0_pud_en_src(data)                                        ((0x02000000&(data))>>25)
#define ISO_PFUNC0_get_i2c_sda_0_pud_en(data)                                        ((0x02000000&(data))>>25)
#define ISO_PFUNC0_i2c_sda_0_pud_sel_shift                                           (24)
#define ISO_PFUNC0_i2c_sda_0_pud_sel_mask                                            (0x01000000)
#define ISO_PFUNC0_i2c_sda_0_pud_sel(data)                                           (0x01000000&((data)<<24))
#define ISO_PFUNC0_i2c_sda_0_pud_sel_src(data)                                       ((0x01000000&(data))>>24)
#define ISO_PFUNC0_get_i2c_sda_0_pud_sel(data)                                       ((0x01000000&(data))>>24)
#define ISO_PFUNC0_vfd_d_smt_shift                                                   (23)
#define ISO_PFUNC0_vfd_d_smt_mask                                                    (0x00800000)
#define ISO_PFUNC0_vfd_d_smt(data)                                                   (0x00800000&((data)<<23))
#define ISO_PFUNC0_vfd_d_smt_src(data)                                               ((0x00800000&(data))>>23)
#define ISO_PFUNC0_get_vfd_d_smt(data)                                               ((0x00800000&(data))>>23)
#define ISO_PFUNC0_vfd_d_e2_shift                                                    (22)
#define ISO_PFUNC0_vfd_d_e2_mask                                                     (0x00400000)
#define ISO_PFUNC0_vfd_d_e2(data)                                                    (0x00400000&((data)<<22))
#define ISO_PFUNC0_vfd_d_e2_src(data)                                                ((0x00400000&(data))>>22)
#define ISO_PFUNC0_get_vfd_d_e2(data)                                                ((0x00400000&(data))>>22)
#define ISO_PFUNC0_vfd_d_pud_en_shift                                                (21)
#define ISO_PFUNC0_vfd_d_pud_en_mask                                                 (0x00200000)
#define ISO_PFUNC0_vfd_d_pud_en(data)                                                (0x00200000&((data)<<21))
#define ISO_PFUNC0_vfd_d_pud_en_src(data)                                            ((0x00200000&(data))>>21)
#define ISO_PFUNC0_get_vfd_d_pud_en(data)                                            ((0x00200000&(data))>>21)
#define ISO_PFUNC0_vfd_d_pud_sel_shift                                               (20)
#define ISO_PFUNC0_vfd_d_pud_sel_mask                                                (0x00100000)
#define ISO_PFUNC0_vfd_d_pud_sel(data)                                               (0x00100000&((data)<<20))
#define ISO_PFUNC0_vfd_d_pud_sel_src(data)                                           ((0x00100000&(data))>>20)
#define ISO_PFUNC0_get_vfd_d_pud_sel(data)                                           ((0x00100000&(data))>>20)
#define ISO_PFUNC0_vfd_clk_smt_shift                                                 (19)
#define ISO_PFUNC0_vfd_clk_smt_mask                                                  (0x00080000)
#define ISO_PFUNC0_vfd_clk_smt(data)                                                 (0x00080000&((data)<<19))
#define ISO_PFUNC0_vfd_clk_smt_src(data)                                             ((0x00080000&(data))>>19)
#define ISO_PFUNC0_get_vfd_clk_smt(data)                                             ((0x00080000&(data))>>19)
#define ISO_PFUNC0_vfd_clk_e2_shift                                                  (18)
#define ISO_PFUNC0_vfd_clk_e2_mask                                                   (0x00040000)
#define ISO_PFUNC0_vfd_clk_e2(data)                                                  (0x00040000&((data)<<18))
#define ISO_PFUNC0_vfd_clk_e2_src(data)                                              ((0x00040000&(data))>>18)
#define ISO_PFUNC0_get_vfd_clk_e2(data)                                              ((0x00040000&(data))>>18)
#define ISO_PFUNC0_vfd_clk_pud_en_shift                                              (17)
#define ISO_PFUNC0_vfd_clk_pud_en_mask                                               (0x00020000)
#define ISO_PFUNC0_vfd_clk_pud_en(data)                                              (0x00020000&((data)<<17))
#define ISO_PFUNC0_vfd_clk_pud_en_src(data)                                          ((0x00020000&(data))>>17)
#define ISO_PFUNC0_get_vfd_clk_pud_en(data)                                          ((0x00020000&(data))>>17)
#define ISO_PFUNC0_vfd_clk_pud_sel_shift                                             (16)
#define ISO_PFUNC0_vfd_clk_pud_sel_mask                                              (0x00010000)
#define ISO_PFUNC0_vfd_clk_pud_sel(data)                                             (0x00010000&((data)<<16))
#define ISO_PFUNC0_vfd_clk_pud_sel_src(data)                                         ((0x00010000&(data))>>16)
#define ISO_PFUNC0_get_vfd_clk_pud_sel(data)                                         ((0x00010000&(data))>>16)
#define ISO_PFUNC0_vfd_cs_n_smt_shift                                                (15)
#define ISO_PFUNC0_vfd_cs_n_smt_mask                                                 (0x00008000)
#define ISO_PFUNC0_vfd_cs_n_smt(data)                                                (0x00008000&((data)<<15))
#define ISO_PFUNC0_vfd_cs_n_smt_src(data)                                            ((0x00008000&(data))>>15)
#define ISO_PFUNC0_get_vfd_cs_n_smt(data)                                            ((0x00008000&(data))>>15)
#define ISO_PFUNC0_vfd_cs_n_e2_shift                                                 (14)
#define ISO_PFUNC0_vfd_cs_n_e2_mask                                                  (0x00004000)
#define ISO_PFUNC0_vfd_cs_n_e2(data)                                                 (0x00004000&((data)<<14))
#define ISO_PFUNC0_vfd_cs_n_e2_src(data)                                             ((0x00004000&(data))>>14)
#define ISO_PFUNC0_get_vfd_cs_n_e2(data)                                             ((0x00004000&(data))>>14)
#define ISO_PFUNC0_vfd_cs_n_pud_en_shift                                             (13)
#define ISO_PFUNC0_vfd_cs_n_pud_en_mask                                              (0x00002000)
#define ISO_PFUNC0_vfd_cs_n_pud_en(data)                                             (0x00002000&((data)<<13))
#define ISO_PFUNC0_vfd_cs_n_pud_en_src(data)                                         ((0x00002000&(data))>>13)
#define ISO_PFUNC0_get_vfd_cs_n_pud_en(data)                                         ((0x00002000&(data))>>13)
#define ISO_PFUNC0_vfd_cs_n_pud_sel_shift                                            (12)
#define ISO_PFUNC0_vfd_cs_n_pud_sel_mask                                             (0x00001000)
#define ISO_PFUNC0_vfd_cs_n_pud_sel(data)                                            (0x00001000&((data)<<12))
#define ISO_PFUNC0_vfd_cs_n_pud_sel_src(data)                                        ((0x00001000&(data))>>12)
#define ISO_PFUNC0_get_vfd_cs_n_pud_sel(data)                                        ((0x00001000&(data))>>12)
#define ISO_PFUNC0_ir_rx_smt_shift                                                   (11)
#define ISO_PFUNC0_ir_rx_smt_mask                                                    (0x00000800)
#define ISO_PFUNC0_ir_rx_smt(data)                                                   (0x00000800&((data)<<11))
#define ISO_PFUNC0_ir_rx_smt_src(data)                                               ((0x00000800&(data))>>11)
#define ISO_PFUNC0_get_ir_rx_smt(data)                                               ((0x00000800&(data))>>11)
#define ISO_PFUNC0_ir_rx_e2_shift                                                    (10)
#define ISO_PFUNC0_ir_rx_e2_mask                                                     (0x00000400)
#define ISO_PFUNC0_ir_rx_e2(data)                                                    (0x00000400&((data)<<10))
#define ISO_PFUNC0_ir_rx_e2_src(data)                                                ((0x00000400&(data))>>10)
#define ISO_PFUNC0_get_ir_rx_e2(data)                                                ((0x00000400&(data))>>10)
#define ISO_PFUNC0_ir_rx_pud_en_shift                                                (9)
#define ISO_PFUNC0_ir_rx_pud_en_mask                                                 (0x00000200)
#define ISO_PFUNC0_ir_rx_pud_en(data)                                                (0x00000200&((data)<<9))
#define ISO_PFUNC0_ir_rx_pud_en_src(data)                                            ((0x00000200&(data))>>9)
#define ISO_PFUNC0_get_ir_rx_pud_en(data)                                            ((0x00000200&(data))>>9)
#define ISO_PFUNC0_ir_rx_pud_sel_shift                                               (8)
#define ISO_PFUNC0_ir_rx_pud_sel_mask                                                (0x00000100)
#define ISO_PFUNC0_ir_rx_pud_sel(data)                                               (0x00000100&((data)<<8))
#define ISO_PFUNC0_ir_rx_pud_sel_src(data)                                           ((0x00000100&(data))>>8)
#define ISO_PFUNC0_get_ir_rx_pud_sel(data)                                           ((0x00000100&(data))>>8)
#define ISO_PFUNC0_usb_ovrcur_flag_n_1_smt_shift                                     (7)
#define ISO_PFUNC0_usb_ovrcur_flag_n_1_smt_mask                                      (0x00000080)
#define ISO_PFUNC0_usb_ovrcur_flag_n_1_smt(data)                                     (0x00000080&((data)<<7))
#define ISO_PFUNC0_usb_ovrcur_flag_n_1_smt_src(data)                                 ((0x00000080&(data))>>7)
#define ISO_PFUNC0_get_usb_ovrcur_flag_n_1_smt(data)                                 ((0x00000080&(data))>>7)
#define ISO_PFUNC0_usb_ovrcur_flag_n_1_e2_shift                                      (6)
#define ISO_PFUNC0_usb_ovrcur_flag_n_1_e2_mask                                       (0x00000040)
#define ISO_PFUNC0_usb_ovrcur_flag_n_1_e2(data)                                      (0x00000040&((data)<<6))
#define ISO_PFUNC0_usb_ovrcur_flag_n_1_e2_src(data)                                  ((0x00000040&(data))>>6)
#define ISO_PFUNC0_get_usb_ovrcur_flag_n_1_e2(data)                                  ((0x00000040&(data))>>6)
#define ISO_PFUNC0_usb_ovrcur_flag_n_1_pud_en_shift                                  (5)
#define ISO_PFUNC0_usb_ovrcur_flag_n_1_pud_en_mask                                   (0x00000020)
#define ISO_PFUNC0_usb_ovrcur_flag_n_1_pud_en(data)                                  (0x00000020&((data)<<5))
#define ISO_PFUNC0_usb_ovrcur_flag_n_1_pud_en_src(data)                              ((0x00000020&(data))>>5)
#define ISO_PFUNC0_get_usb_ovrcur_flag_n_1_pud_en(data)                              ((0x00000020&(data))>>5)
#define ISO_PFUNC0_usb_ovrcur_flag_n_1_pud_sel_shift                                 (4)
#define ISO_PFUNC0_usb_ovrcur_flag_n_1_pud_sel_mask                                  (0x00000010)
#define ISO_PFUNC0_usb_ovrcur_flag_n_1_pud_sel(data)                                 (0x00000010&((data)<<4))
#define ISO_PFUNC0_usb_ovrcur_flag_n_1_pud_sel_src(data)                             ((0x00000010&(data))>>4)
#define ISO_PFUNC0_get_usb_ovrcur_flag_n_1_pud_sel(data)                             ((0x00000010&(data))>>4)
#define ISO_PFUNC0_usb_ovrcur_flag_n_0_smt_shift                                     (3)
#define ISO_PFUNC0_usb_ovrcur_flag_n_0_smt_mask                                      (0x00000008)
#define ISO_PFUNC0_usb_ovrcur_flag_n_0_smt(data)                                     (0x00000008&((data)<<3))
#define ISO_PFUNC0_usb_ovrcur_flag_n_0_smt_src(data)                                 ((0x00000008&(data))>>3)
#define ISO_PFUNC0_get_usb_ovrcur_flag_n_0_smt(data)                                 ((0x00000008&(data))>>3)
#define ISO_PFUNC0_usb_ovrcur_flag_n_0_e2_shift                                      (2)
#define ISO_PFUNC0_usb_ovrcur_flag_n_0_e2_mask                                       (0x00000004)
#define ISO_PFUNC0_usb_ovrcur_flag_n_0_e2(data)                                      (0x00000004&((data)<<2))
#define ISO_PFUNC0_usb_ovrcur_flag_n_0_e2_src(data)                                  ((0x00000004&(data))>>2)
#define ISO_PFUNC0_get_usb_ovrcur_flag_n_0_e2(data)                                  ((0x00000004&(data))>>2)
#define ISO_PFUNC0_usb_ovrcur_flag_n_0_pud_en_shift                                  (1)
#define ISO_PFUNC0_usb_ovrcur_flag_n_0_pud_en_mask                                   (0x00000002)
#define ISO_PFUNC0_usb_ovrcur_flag_n_0_pud_en(data)                                  (0x00000002&((data)<<1))
#define ISO_PFUNC0_usb_ovrcur_flag_n_0_pud_en_src(data)                              ((0x00000002&(data))>>1)
#define ISO_PFUNC0_get_usb_ovrcur_flag_n_0_pud_en(data)                              ((0x00000002&(data))>>1)
#define ISO_PFUNC0_usb_ovrcur_flag_n_0_pud_sel_shift                                 (0)
#define ISO_PFUNC0_usb_ovrcur_flag_n_0_pud_sel_mask                                  (0x00000001)
#define ISO_PFUNC0_usb_ovrcur_flag_n_0_pud_sel(data)                                 (0x00000001&((data)<<0))
#define ISO_PFUNC0_usb_ovrcur_flag_n_0_pud_sel_src(data)                             ((0x00000001&(data))>>0)
#define ISO_PFUNC0_get_usb_ovrcur_flag_n_0_pud_sel(data)                             ((0x00000001&(data))>>0)


#define ISO_PFUNC1                                                                   0x18007304
#define ISO_PFUNC1_reg_addr                                                          "0xB8007304"
#define ISO_PFUNC1_reg                                                               0xB8007304
#define set_ISO_PFUNC1_reg(data)   (*((volatile unsigned int*) ISO_PFUNC1_reg)=data)
#define get_ISO_PFUNC1_reg   (*((volatile unsigned int*) ISO_PFUNC1_reg))
#define ISO_PFUNC1_inst_adr                                                          "0x00C1"
#define ISO_PFUNC1_inst                                                              0x00C1
#define ISO_PFUNC1_etn_led_rxtx_smt_shift                                            (31)
#define ISO_PFUNC1_etn_led_rxtx_smt_mask                                             (0x80000000)
#define ISO_PFUNC1_etn_led_rxtx_smt(data)                                            (0x80000000&((data)<<31))
#define ISO_PFUNC1_etn_led_rxtx_smt_src(data)                                        ((0x80000000&(data))>>31)
#define ISO_PFUNC1_get_etn_led_rxtx_smt(data)                                        ((0x80000000&(data))>>31)
#define ISO_PFUNC1_etn_led_rxtx_e2_shift                                             (30)
#define ISO_PFUNC1_etn_led_rxtx_e2_mask                                              (0x40000000)
#define ISO_PFUNC1_etn_led_rxtx_e2(data)                                             (0x40000000&((data)<<30))
#define ISO_PFUNC1_etn_led_rxtx_e2_src(data)                                         ((0x40000000&(data))>>30)
#define ISO_PFUNC1_get_etn_led_rxtx_e2(data)                                         ((0x40000000&(data))>>30)
#define ISO_PFUNC1_etn_led_rxtx_pud_en_shift                                         (29)
#define ISO_PFUNC1_etn_led_rxtx_pud_en_mask                                          (0x20000000)
#define ISO_PFUNC1_etn_led_rxtx_pud_en(data)                                         (0x20000000&((data)<<29))
#define ISO_PFUNC1_etn_led_rxtx_pud_en_src(data)                                     ((0x20000000&(data))>>29)
#define ISO_PFUNC1_get_etn_led_rxtx_pud_en(data)                                     ((0x20000000&(data))>>29)
#define ISO_PFUNC1_etn_led_rxtx_pud_sel_shift                                        (28)
#define ISO_PFUNC1_etn_led_rxtx_pud_sel_mask                                         (0x10000000)
#define ISO_PFUNC1_etn_led_rxtx_pud_sel(data)                                        (0x10000000&((data)<<28))
#define ISO_PFUNC1_etn_led_rxtx_pud_sel_src(data)                                    ((0x10000000&(data))>>28)
#define ISO_PFUNC1_get_etn_led_rxtx_pud_sel(data)                                    ((0x10000000&(data))>>28)
#define ISO_PFUNC1_etn_led_link_smt_shift                                            (27)
#define ISO_PFUNC1_etn_led_link_smt_mask                                             (0x08000000)
#define ISO_PFUNC1_etn_led_link_smt(data)                                            (0x08000000&((data)<<27))
#define ISO_PFUNC1_etn_led_link_smt_src(data)                                        ((0x08000000&(data))>>27)
#define ISO_PFUNC1_get_etn_led_link_smt(data)                                        ((0x08000000&(data))>>27)
#define ISO_PFUNC1_etn_led_link_e2_shift                                             (26)
#define ISO_PFUNC1_etn_led_link_e2_mask                                              (0x04000000)
#define ISO_PFUNC1_etn_led_link_e2(data)                                             (0x04000000&((data)<<26))
#define ISO_PFUNC1_etn_led_link_e2_src(data)                                         ((0x04000000&(data))>>26)
#define ISO_PFUNC1_get_etn_led_link_e2(data)                                         ((0x04000000&(data))>>26)
#define ISO_PFUNC1_etn_led_link_pud_en_shift                                         (25)
#define ISO_PFUNC1_etn_led_link_pud_en_mask                                          (0x02000000)
#define ISO_PFUNC1_etn_led_link_pud_en(data)                                         (0x02000000&((data)<<25))
#define ISO_PFUNC1_etn_led_link_pud_en_src(data)                                     ((0x02000000&(data))>>25)
#define ISO_PFUNC1_get_etn_led_link_pud_en(data)                                     ((0x02000000&(data))>>25)
#define ISO_PFUNC1_etn_led_link_pud_sel_shift                                        (24)
#define ISO_PFUNC1_etn_led_link_pud_sel_mask                                         (0x01000000)
#define ISO_PFUNC1_etn_led_link_pud_sel(data)                                        (0x01000000&((data)<<24))
#define ISO_PFUNC1_etn_led_link_pud_sel_src(data)                                    ((0x01000000&(data))>>24)
#define ISO_PFUNC1_get_etn_led_link_pud_sel(data)                                    ((0x01000000&(data))>>24)
#define ISO_PFUNC1_ur0_tx_smt_shift                                                  (23)
#define ISO_PFUNC1_ur0_tx_smt_mask                                                   (0x00800000)
#define ISO_PFUNC1_ur0_tx_smt(data)                                                  (0x00800000&((data)<<23))
#define ISO_PFUNC1_ur0_tx_smt_src(data)                                              ((0x00800000&(data))>>23)
#define ISO_PFUNC1_get_ur0_tx_smt(data)                                              ((0x00800000&(data))>>23)
#define ISO_PFUNC1_ur0_tx_e2_shift                                                   (22)
#define ISO_PFUNC1_ur0_tx_e2_mask                                                    (0x00400000)
#define ISO_PFUNC1_ur0_tx_e2(data)                                                   (0x00400000&((data)<<22))
#define ISO_PFUNC1_ur0_tx_e2_src(data)                                               ((0x00400000&(data))>>22)
#define ISO_PFUNC1_get_ur0_tx_e2(data)                                               ((0x00400000&(data))>>22)
#define ISO_PFUNC1_ur0_tx_pud_en_shift                                               (21)
#define ISO_PFUNC1_ur0_tx_pud_en_mask                                                (0x00200000)
#define ISO_PFUNC1_ur0_tx_pud_en(data)                                               (0x00200000&((data)<<21))
#define ISO_PFUNC1_ur0_tx_pud_en_src(data)                                           ((0x00200000&(data))>>21)
#define ISO_PFUNC1_get_ur0_tx_pud_en(data)                                           ((0x00200000&(data))>>21)
#define ISO_PFUNC1_ur0_tx_pud_sel_shift                                              (20)
#define ISO_PFUNC1_ur0_tx_pud_sel_mask                                               (0x00100000)
#define ISO_PFUNC1_ur0_tx_pud_sel(data)                                              (0x00100000&((data)<<20))
#define ISO_PFUNC1_ur0_tx_pud_sel_src(data)                                          ((0x00100000&(data))>>20)
#define ISO_PFUNC1_get_ur0_tx_pud_sel(data)                                          ((0x00100000&(data))>>20)
#define ISO_PFUNC1_ur0_rx_smt_shift                                                  (19)
#define ISO_PFUNC1_ur0_rx_smt_mask                                                   (0x00080000)
#define ISO_PFUNC1_ur0_rx_smt(data)                                                  (0x00080000&((data)<<19))
#define ISO_PFUNC1_ur0_rx_smt_src(data)                                              ((0x00080000&(data))>>19)
#define ISO_PFUNC1_get_ur0_rx_smt(data)                                              ((0x00080000&(data))>>19)
#define ISO_PFUNC1_ur0_rx_e2_shift                                                   (18)
#define ISO_PFUNC1_ur0_rx_e2_mask                                                    (0x00040000)
#define ISO_PFUNC1_ur0_rx_e2(data)                                                   (0x00040000&((data)<<18))
#define ISO_PFUNC1_ur0_rx_e2_src(data)                                               ((0x00040000&(data))>>18)
#define ISO_PFUNC1_get_ur0_rx_e2(data)                                               ((0x00040000&(data))>>18)
#define ISO_PFUNC1_ur0_rx_pud_en_shift                                               (17)
#define ISO_PFUNC1_ur0_rx_pud_en_mask                                                (0x00020000)
#define ISO_PFUNC1_ur0_rx_pud_en(data)                                               (0x00020000&((data)<<17))
#define ISO_PFUNC1_ur0_rx_pud_en_src(data)                                           ((0x00020000&(data))>>17)
#define ISO_PFUNC1_get_ur0_rx_pud_en(data)                                           ((0x00020000&(data))>>17)
#define ISO_PFUNC1_ur0_rx_pud_sel_shift                                              (16)
#define ISO_PFUNC1_ur0_rx_pud_sel_mask                                               (0x00010000)
#define ISO_PFUNC1_ur0_rx_pud_sel(data)                                              (0x00010000&((data)<<16))
#define ISO_PFUNC1_ur0_rx_pud_sel_src(data)                                          ((0x00010000&(data))>>16)
#define ISO_PFUNC1_get_ur0_rx_pud_sel(data)                                          ((0x00010000&(data))>>16)
#define ISO_PFUNC1_ur1_cts_n_smt_shift                                               (15)
#define ISO_PFUNC1_ur1_cts_n_smt_mask                                                (0x00008000)
#define ISO_PFUNC1_ur1_cts_n_smt(data)                                               (0x00008000&((data)<<15))
#define ISO_PFUNC1_ur1_cts_n_smt_src(data)                                           ((0x00008000&(data))>>15)
#define ISO_PFUNC1_get_ur1_cts_n_smt(data)                                           ((0x00008000&(data))>>15)
#define ISO_PFUNC1_ur1_cts_n_e2_shift                                                (14)
#define ISO_PFUNC1_ur1_cts_n_e2_mask                                                 (0x00004000)
#define ISO_PFUNC1_ur1_cts_n_e2(data)                                                (0x00004000&((data)<<14))
#define ISO_PFUNC1_ur1_cts_n_e2_src(data)                                            ((0x00004000&(data))>>14)
#define ISO_PFUNC1_get_ur1_cts_n_e2(data)                                            ((0x00004000&(data))>>14)
#define ISO_PFUNC1_ur1_cts_n_pud_en_shift                                            (13)
#define ISO_PFUNC1_ur1_cts_n_pud_en_mask                                             (0x00002000)
#define ISO_PFUNC1_ur1_cts_n_pud_en(data)                                            (0x00002000&((data)<<13))
#define ISO_PFUNC1_ur1_cts_n_pud_en_src(data)                                        ((0x00002000&(data))>>13)
#define ISO_PFUNC1_get_ur1_cts_n_pud_en(data)                                        ((0x00002000&(data))>>13)
#define ISO_PFUNC1_ur1_cts_n_pud_sel_shift                                           (12)
#define ISO_PFUNC1_ur1_cts_n_pud_sel_mask                                            (0x00001000)
#define ISO_PFUNC1_ur1_cts_n_pud_sel(data)                                           (0x00001000&((data)<<12))
#define ISO_PFUNC1_ur1_cts_n_pud_sel_src(data)                                       ((0x00001000&(data))>>12)
#define ISO_PFUNC1_get_ur1_cts_n_pud_sel(data)                                       ((0x00001000&(data))>>12)
#define ISO_PFUNC1_ur1_rts_n_smt_shift                                               (11)
#define ISO_PFUNC1_ur1_rts_n_smt_mask                                                (0x00000800)
#define ISO_PFUNC1_ur1_rts_n_smt(data)                                               (0x00000800&((data)<<11))
#define ISO_PFUNC1_ur1_rts_n_smt_src(data)                                           ((0x00000800&(data))>>11)
#define ISO_PFUNC1_get_ur1_rts_n_smt(data)                                           ((0x00000800&(data))>>11)
#define ISO_PFUNC1_ur1_rts_n_e2_shift                                                (10)
#define ISO_PFUNC1_ur1_rts_n_e2_mask                                                 (0x00000400)
#define ISO_PFUNC1_ur1_rts_n_e2(data)                                                (0x00000400&((data)<<10))
#define ISO_PFUNC1_ur1_rts_n_e2_src(data)                                            ((0x00000400&(data))>>10)
#define ISO_PFUNC1_get_ur1_rts_n_e2(data)                                            ((0x00000400&(data))>>10)
#define ISO_PFUNC1_ur1_rts_n_pud_en_shift                                            (9)
#define ISO_PFUNC1_ur1_rts_n_pud_en_mask                                             (0x00000200)
#define ISO_PFUNC1_ur1_rts_n_pud_en(data)                                            (0x00000200&((data)<<9))
#define ISO_PFUNC1_ur1_rts_n_pud_en_src(data)                                        ((0x00000200&(data))>>9)
#define ISO_PFUNC1_get_ur1_rts_n_pud_en(data)                                        ((0x00000200&(data))>>9)
#define ISO_PFUNC1_ur1_rts_n_pud_sel_shift                                           (8)
#define ISO_PFUNC1_ur1_rts_n_pud_sel_mask                                            (0x00000100)
#define ISO_PFUNC1_ur1_rts_n_pud_sel(data)                                           (0x00000100&((data)<<8))
#define ISO_PFUNC1_ur1_rts_n_pud_sel_src(data)                                       ((0x00000100&(data))>>8)
#define ISO_PFUNC1_get_ur1_rts_n_pud_sel(data)                                       ((0x00000100&(data))>>8)
#define ISO_PFUNC1_ur1_tx_smt_shift                                                  (7)
#define ISO_PFUNC1_ur1_tx_smt_mask                                                   (0x00000080)
#define ISO_PFUNC1_ur1_tx_smt(data)                                                  (0x00000080&((data)<<7))
#define ISO_PFUNC1_ur1_tx_smt_src(data)                                              ((0x00000080&(data))>>7)
#define ISO_PFUNC1_get_ur1_tx_smt(data)                                              ((0x00000080&(data))>>7)
#define ISO_PFUNC1_ur1_tx_e2_shift                                                   (6)
#define ISO_PFUNC1_ur1_tx_e2_mask                                                    (0x00000040)
#define ISO_PFUNC1_ur1_tx_e2(data)                                                   (0x00000040&((data)<<6))
#define ISO_PFUNC1_ur1_tx_e2_src(data)                                               ((0x00000040&(data))>>6)
#define ISO_PFUNC1_get_ur1_tx_e2(data)                                               ((0x00000040&(data))>>6)
#define ISO_PFUNC1_ur1_tx_pud_en_shift                                               (5)
#define ISO_PFUNC1_ur1_tx_pud_en_mask                                                (0x00000020)
#define ISO_PFUNC1_ur1_tx_pud_en(data)                                               (0x00000020&((data)<<5))
#define ISO_PFUNC1_ur1_tx_pud_en_src(data)                                           ((0x00000020&(data))>>5)
#define ISO_PFUNC1_get_ur1_tx_pud_en(data)                                           ((0x00000020&(data))>>5)
#define ISO_PFUNC1_ur1_tx_pud_sel_shift                                              (4)
#define ISO_PFUNC1_ur1_tx_pud_sel_mask                                               (0x00000010)
#define ISO_PFUNC1_ur1_tx_pud_sel(data)                                              (0x00000010&((data)<<4))
#define ISO_PFUNC1_ur1_tx_pud_sel_src(data)                                          ((0x00000010&(data))>>4)
#define ISO_PFUNC1_get_ur1_tx_pud_sel(data)                                          ((0x00000010&(data))>>4)
#define ISO_PFUNC1_ur1_rx_smt_shift                                                  (3)
#define ISO_PFUNC1_ur1_rx_smt_mask                                                   (0x00000008)
#define ISO_PFUNC1_ur1_rx_smt(data)                                                  (0x00000008&((data)<<3))
#define ISO_PFUNC1_ur1_rx_smt_src(data)                                              ((0x00000008&(data))>>3)
#define ISO_PFUNC1_get_ur1_rx_smt(data)                                              ((0x00000008&(data))>>3)
#define ISO_PFUNC1_ur1_rx_e2_shift                                                   (2)
#define ISO_PFUNC1_ur1_rx_e2_mask                                                    (0x00000004)
#define ISO_PFUNC1_ur1_rx_e2(data)                                                   (0x00000004&((data)<<2))
#define ISO_PFUNC1_ur1_rx_e2_src(data)                                               ((0x00000004&(data))>>2)
#define ISO_PFUNC1_get_ur1_rx_e2(data)                                               ((0x00000004&(data))>>2)
#define ISO_PFUNC1_ur1_rx_pud_en_shift                                               (1)
#define ISO_PFUNC1_ur1_rx_pud_en_mask                                                (0x00000002)
#define ISO_PFUNC1_ur1_rx_pud_en(data)                                               (0x00000002&((data)<<1))
#define ISO_PFUNC1_ur1_rx_pud_en_src(data)                                           ((0x00000002&(data))>>1)
#define ISO_PFUNC1_get_ur1_rx_pud_en(data)                                           ((0x00000002&(data))>>1)
#define ISO_PFUNC1_ur1_rx_pud_sel_shift                                              (0)
#define ISO_PFUNC1_ur1_rx_pud_sel_mask                                               (0x00000001)
#define ISO_PFUNC1_ur1_rx_pud_sel(data)                                              (0x00000001&((data)<<0))
#define ISO_PFUNC1_ur1_rx_pud_sel_src(data)                                          ((0x00000001&(data))>>0)
#define ISO_PFUNC1_get_ur1_rx_pud_sel(data)                                          ((0x00000001&(data))>>0)


#define ISO_PFUNC2                                                                   0x18007308
#define ISO_PFUNC2_reg_addr                                                          "0xB8007308"
#define ISO_PFUNC2_reg                                                               0xB8007308
#define set_ISO_PFUNC2_reg(data)   (*((volatile unsigned int*) ISO_PFUNC2_reg)=data)
#define get_ISO_PFUNC2_reg   (*((volatile unsigned int*) ISO_PFUNC2_reg))
#define ISO_PFUNC2_inst_adr                                                          "0x00C2"
#define ISO_PFUNC2_inst                                                              0x00C2
#define ISO_PFUNC2_ir_tx_smt_shift                                                   (23)
#define ISO_PFUNC2_ir_tx_smt_mask                                                    (0x00800000)
#define ISO_PFUNC2_ir_tx_smt(data)                                                   (0x00800000&((data)<<23))
#define ISO_PFUNC2_ir_tx_smt_src(data)                                               ((0x00800000&(data))>>23)
#define ISO_PFUNC2_get_ir_tx_smt(data)                                               ((0x00800000&(data))>>23)
#define ISO_PFUNC2_ir_tx_e2_shift                                                    (22)
#define ISO_PFUNC2_ir_tx_e2_mask                                                     (0x00400000)
#define ISO_PFUNC2_ir_tx_e2(data)                                                    (0x00400000&((data)<<22))
#define ISO_PFUNC2_ir_tx_e2_src(data)                                                ((0x00400000&(data))>>22)
#define ISO_PFUNC2_get_ir_tx_e2(data)                                                ((0x00400000&(data))>>22)
#define ISO_PFUNC2_ir_tx_pud_en_shift                                                (21)
#define ISO_PFUNC2_ir_tx_pud_en_mask                                                 (0x00200000)
#define ISO_PFUNC2_ir_tx_pud_en(data)                                                (0x00200000&((data)<<21))
#define ISO_PFUNC2_ir_tx_pud_en_src(data)                                            ((0x00200000&(data))>>21)
#define ISO_PFUNC2_get_ir_tx_pud_en(data)                                            ((0x00200000&(data))>>21)
#define ISO_PFUNC2_ir_tx_pud_sel_shift                                               (20)
#define ISO_PFUNC2_ir_tx_pud_sel_mask                                                (0x00100000)
#define ISO_PFUNC2_ir_tx_pud_sel(data)                                               (0x00100000&((data)<<20))
#define ISO_PFUNC2_ir_tx_pud_sel_src(data)                                           ((0x00100000&(data))>>20)
#define ISO_PFUNC2_get_ir_tx_pud_sel(data)                                           ((0x00100000&(data))>>20)
#define ISO_PFUNC2_i2c_scl_6_smt_shift                                               (19)
#define ISO_PFUNC2_i2c_scl_6_smt_mask                                                (0x00080000)
#define ISO_PFUNC2_i2c_scl_6_smt(data)                                               (0x00080000&((data)<<19))
#define ISO_PFUNC2_i2c_scl_6_smt_src(data)                                           ((0x00080000&(data))>>19)
#define ISO_PFUNC2_get_i2c_scl_6_smt(data)                                           ((0x00080000&(data))>>19)
#define ISO_PFUNC2_i2c_scl_6_e2_shift                                                (18)
#define ISO_PFUNC2_i2c_scl_6_e2_mask                                                 (0x00040000)
#define ISO_PFUNC2_i2c_scl_6_e2(data)                                                (0x00040000&((data)<<18))
#define ISO_PFUNC2_i2c_scl_6_e2_src(data)                                            ((0x00040000&(data))>>18)
#define ISO_PFUNC2_get_i2c_scl_6_e2(data)                                            ((0x00040000&(data))>>18)
#define ISO_PFUNC2_i2c_scl_6_pud_en_shift                                            (17)
#define ISO_PFUNC2_i2c_scl_6_pud_en_mask                                             (0x00020000)
#define ISO_PFUNC2_i2c_scl_6_pud_en(data)                                            (0x00020000&((data)<<17))
#define ISO_PFUNC2_i2c_scl_6_pud_en_src(data)                                        ((0x00020000&(data))>>17)
#define ISO_PFUNC2_get_i2c_scl_6_pud_en(data)                                        ((0x00020000&(data))>>17)
#define ISO_PFUNC2_i2c_scl_6_pud_sel_shift                                           (16)
#define ISO_PFUNC2_i2c_scl_6_pud_sel_mask                                            (0x00010000)
#define ISO_PFUNC2_i2c_scl_6_pud_sel(data)                                           (0x00010000&((data)<<16))
#define ISO_PFUNC2_i2c_scl_6_pud_sel_src(data)                                       ((0x00010000&(data))>>16)
#define ISO_PFUNC2_get_i2c_scl_6_pud_sel(data)                                       ((0x00010000&(data))>>16)
#define ISO_PFUNC2_i2c_sda_6_smt_shift                                               (15)
#define ISO_PFUNC2_i2c_sda_6_smt_mask                                                (0x00008000)
#define ISO_PFUNC2_i2c_sda_6_smt(data)                                               (0x00008000&((data)<<15))
#define ISO_PFUNC2_i2c_sda_6_smt_src(data)                                           ((0x00008000&(data))>>15)
#define ISO_PFUNC2_get_i2c_sda_6_smt(data)                                           ((0x00008000&(data))>>15)
#define ISO_PFUNC2_i2c_sda_6_e2_shift                                                (14)
#define ISO_PFUNC2_i2c_sda_6_e2_mask                                                 (0x00004000)
#define ISO_PFUNC2_i2c_sda_6_e2(data)                                                (0x00004000&((data)<<14))
#define ISO_PFUNC2_i2c_sda_6_e2_src(data)                                            ((0x00004000&(data))>>14)
#define ISO_PFUNC2_get_i2c_sda_6_e2(data)                                            ((0x00004000&(data))>>14)
#define ISO_PFUNC2_i2c_sda_6_pud_en_shift                                            (13)
#define ISO_PFUNC2_i2c_sda_6_pud_en_mask                                             (0x00002000)
#define ISO_PFUNC2_i2c_sda_6_pud_en(data)                                            (0x00002000&((data)<<13))
#define ISO_PFUNC2_i2c_sda_6_pud_en_src(data)                                        ((0x00002000&(data))>>13)
#define ISO_PFUNC2_get_i2c_sda_6_pud_en(data)                                        ((0x00002000&(data))>>13)
#define ISO_PFUNC2_i2c_sda_6_pud_sel_shift                                           (12)
#define ISO_PFUNC2_i2c_sda_6_pud_sel_mask                                            (0x00001000)
#define ISO_PFUNC2_i2c_sda_6_pud_sel(data)                                           (0x00001000&((data)<<12))
#define ISO_PFUNC2_i2c_sda_6_pud_sel_src(data)                                       ((0x00001000&(data))>>12)
#define ISO_PFUNC2_get_i2c_sda_6_pud_sel(data)                                       ((0x00001000&(data))>>12)
#define ISO_PFUNC2_boot_sel_pud_en_shift                                             (11)
#define ISO_PFUNC2_boot_sel_pud_en_mask                                              (0x00000800)
#define ISO_PFUNC2_boot_sel_pud_en(data)                                             (0x00000800&((data)<<11))
#define ISO_PFUNC2_boot_sel_pud_en_src(data)                                         ((0x00000800&(data))>>11)
#define ISO_PFUNC2_get_boot_sel_pud_en(data)                                         ((0x00000800&(data))>>11)
#define ISO_PFUNC2_boot_sel_pud_sel_shift                                            (10)
#define ISO_PFUNC2_boot_sel_pud_sel_mask                                             (0x00000400)
#define ISO_PFUNC2_boot_sel_pud_sel(data)                                            (0x00000400&((data)<<10))
#define ISO_PFUNC2_boot_sel_pud_sel_src(data)                                        ((0x00000400&(data))>>10)
#define ISO_PFUNC2_get_boot_sel_pud_sel(data)                                        ((0x00000400&(data))>>10)
#define ISO_PFUNC2_testmode_pud_en_shift                                             (9)
#define ISO_PFUNC2_testmode_pud_en_mask                                              (0x00000200)
#define ISO_PFUNC2_testmode_pud_en(data)                                             (0x00000200&((data)<<9))
#define ISO_PFUNC2_testmode_pud_en_src(data)                                         ((0x00000200&(data))>>9)
#define ISO_PFUNC2_get_testmode_pud_en(data)                                         ((0x00000200&(data))>>9)
#define ISO_PFUNC2_testmode_pud_sel_shift                                            (8)
#define ISO_PFUNC2_testmode_pud_sel_mask                                             (0x00000100)
#define ISO_PFUNC2_testmode_pud_sel(data)                                            (0x00000100&((data)<<8))
#define ISO_PFUNC2_testmode_pud_sel_src(data)                                        ((0x00000100&(data))>>8)
#define ISO_PFUNC2_get_testmode_pud_sel(data)                                        ((0x00000100&(data))>>8)
#define ISO_PFUNC2_standby1_smt_shift                                                (7)
#define ISO_PFUNC2_standby1_smt_mask                                                 (0x00000080)
#define ISO_PFUNC2_standby1_smt(data)                                                (0x00000080&((data)<<7))
#define ISO_PFUNC2_standby1_smt_src(data)                                            ((0x00000080&(data))>>7)
#define ISO_PFUNC2_get_standby1_smt(data)                                            ((0x00000080&(data))>>7)
#define ISO_PFUNC2_standby1_e2_shift                                                 (6)
#define ISO_PFUNC2_standby1_e2_mask                                                  (0x00000040)
#define ISO_PFUNC2_standby1_e2(data)                                                 (0x00000040&((data)<<6))
#define ISO_PFUNC2_standby1_e2_src(data)                                             ((0x00000040&(data))>>6)
#define ISO_PFUNC2_get_standby1_e2(data)                                             ((0x00000040&(data))>>6)
#define ISO_PFUNC2_standby1_pud_en_shift                                             (5)
#define ISO_PFUNC2_standby1_pud_en_mask                                              (0x00000020)
#define ISO_PFUNC2_standby1_pud_en(data)                                             (0x00000020&((data)<<5))
#define ISO_PFUNC2_standby1_pud_en_src(data)                                         ((0x00000020&(data))>>5)
#define ISO_PFUNC2_get_standby1_pud_en(data)                                         ((0x00000020&(data))>>5)
#define ISO_PFUNC2_standby1_pud_sel_shift                                            (4)
#define ISO_PFUNC2_standby1_pud_sel_mask                                             (0x00000010)
#define ISO_PFUNC2_standby1_pud_sel(data)                                            (0x00000010&((data)<<4))
#define ISO_PFUNC2_standby1_pud_sel_src(data)                                        ((0x00000010&(data))>>4)
#define ISO_PFUNC2_get_standby1_pud_sel(data)                                        ((0x00000010&(data))>>4)
#define ISO_PFUNC2_standby_smt_shift                                                 (3)
#define ISO_PFUNC2_standby_smt_mask                                                  (0x00000008)
#define ISO_PFUNC2_standby_smt(data)                                                 (0x00000008&((data)<<3))
#define ISO_PFUNC2_standby_smt_src(data)                                             ((0x00000008&(data))>>3)
#define ISO_PFUNC2_get_standby_smt(data)                                             ((0x00000008&(data))>>3)
#define ISO_PFUNC2_standby_e2_shift                                                  (2)
#define ISO_PFUNC2_standby_e2_mask                                                   (0x00000004)
#define ISO_PFUNC2_standby_e2(data)                                                  (0x00000004&((data)<<2))
#define ISO_PFUNC2_standby_e2_src(data)                                              ((0x00000004&(data))>>2)
#define ISO_PFUNC2_get_standby_e2(data)                                              ((0x00000004&(data))>>2)
#define ISO_PFUNC2_standby_pud_en_shift                                              (1)
#define ISO_PFUNC2_standby_pud_en_mask                                               (0x00000002)
#define ISO_PFUNC2_standby_pud_en(data)                                              (0x00000002&((data)<<1))
#define ISO_PFUNC2_standby_pud_en_src(data)                                          ((0x00000002&(data))>>1)
#define ISO_PFUNC2_get_standby_pud_en(data)                                          ((0x00000002&(data))>>1)
#define ISO_PFUNC2_standby_pud_sel_shift                                             (0)
#define ISO_PFUNC2_standby_pud_sel_mask                                              (0x00000001)
#define ISO_PFUNC2_standby_pud_sel(data)                                             (0x00000001&((data)<<0))
#define ISO_PFUNC2_standby_pud_sel_src(data)                                         ((0x00000001&(data))>>0)
#define ISO_PFUNC2_get_standby_pud_sel(data)                                         ((0x00000001&(data))>>0)


#define ISO_PFUNC3                                                                   0x1800730C
#define ISO_PFUNC3_reg_addr                                                          "0xB800730C"
#define ISO_PFUNC3_reg                                                               0xB800730C
#define set_ISO_PFUNC3_reg(data)   (*((volatile unsigned int*) ISO_PFUNC3_reg)=data)
#define get_ISO_PFUNC3_reg   (*((volatile unsigned int*) ISO_PFUNC3_reg))
#define ISO_PFUNC3_inst_adr                                                          "0x00C3"
#define ISO_PFUNC3_inst                                                              0x00C3
#define ISO_PFUNC3_boption12_en_shift                                                (7)
#define ISO_PFUNC3_boption12_en_mask                                                 (0x00000080)
#define ISO_PFUNC3_boption12_en(data)                                                (0x00000080&((data)<<7))
#define ISO_PFUNC3_boption12_en_src(data)                                            ((0x00000080&(data))>>7)
#define ISO_PFUNC3_get_boption12_en(data)                                            ((0x00000080&(data))>>7)
#define ISO_PFUNC3_boption12_sel_shift                                               (6)
#define ISO_PFUNC3_boption12_sel_mask                                                (0x00000040)
#define ISO_PFUNC3_boption12_sel(data)                                               (0x00000040&((data)<<6))
#define ISO_PFUNC3_boption12_sel_src(data)                                           ((0x00000040&(data))>>6)
#define ISO_PFUNC3_get_boption12_sel(data)                                           ((0x00000040&(data))>>6)
#define ISO_PFUNC3_boption11_en_shift                                                (5)
#define ISO_PFUNC3_boption11_en_mask                                                 (0x00000020)
#define ISO_PFUNC3_boption11_en(data)                                                (0x00000020&((data)<<5))
#define ISO_PFUNC3_boption11_en_src(data)                                            ((0x00000020&(data))>>5)
#define ISO_PFUNC3_get_boption11_en(data)                                            ((0x00000020&(data))>>5)
#define ISO_PFUNC3_boption11_sel_shift                                               (4)
#define ISO_PFUNC3_boption11_sel_mask                                                (0x00000010)
#define ISO_PFUNC3_boption11_sel(data)                                               (0x00000010&((data)<<4))
#define ISO_PFUNC3_boption11_sel_src(data)                                           ((0x00000010&(data))>>4)
#define ISO_PFUNC3_get_boption11_sel(data)                                           ((0x00000010&(data))>>4)
#define ISO_PFUNC3_boption10_en_shift                                                (3)
#define ISO_PFUNC3_boption10_en_mask                                                 (0x00000008)
#define ISO_PFUNC3_boption10_en(data)                                                (0x00000008&((data)<<3))
#define ISO_PFUNC3_boption10_en_src(data)                                            ((0x00000008&(data))>>3)
#define ISO_PFUNC3_get_boption10_en(data)                                            ((0x00000008&(data))>>3)
#define ISO_PFUNC3_boption10_sel_shift                                               (2)
#define ISO_PFUNC3_boption10_sel_mask                                                (0x00000004)
#define ISO_PFUNC3_boption10_sel(data)                                               (0x00000004&((data)<<2))
#define ISO_PFUNC3_boption10_sel_src(data)                                           ((0x00000004&(data))>>2)
#define ISO_PFUNC3_get_boption10_sel(data)                                           ((0x00000004&(data))>>2)
#define ISO_PFUNC3_boption2_en_shift                                                 (1)
#define ISO_PFUNC3_boption2_en_mask                                                  (0x00000002)
#define ISO_PFUNC3_boption2_en(data)                                                 (0x00000002&((data)<<1))
#define ISO_PFUNC3_boption2_en_src(data)                                             ((0x00000002&(data))>>1)
#define ISO_PFUNC3_get_boption2_en(data)                                             ((0x00000002&(data))>>1)
#define ISO_PFUNC3_boption2_sel_shift                                                (0)
#define ISO_PFUNC3_boption2_sel_mask                                                 (0x00000001)
#define ISO_PFUNC3_boption2_sel(data)                                                (0x00000001&((data)<<0))
#define ISO_PFUNC3_boption2_sel_src(data)                                            ((0x00000001&(data))>>0)
#define ISO_PFUNC3_get_boption2_sel(data)                                            ((0x00000001&(data))>>0)


#define ISO_MUXPAD0                                                                  0x18007310
#define ISO_MUXPAD0_reg_addr                                                         "0xB8007310"
#define ISO_MUXPAD0_reg                                                              0xB8007310
#define set_ISO_MUXPAD0_reg(data)   (*((volatile unsigned int*) ISO_MUXPAD0_reg)=data)
#define get_ISO_MUXPAD0_reg   (*((volatile unsigned int*) ISO_MUXPAD0_reg))
#define ISO_MUXPAD0_inst_adr                                                         "0x00C4"
#define ISO_MUXPAD0_inst                                                             0x00C4
#define ISO_MUXPAD0_etn_led_rxtx_shift                                               (30)
#define ISO_MUXPAD0_etn_led_rxtx_mask                                                (0xC0000000)
#define ISO_MUXPAD0_etn_led_rxtx(data)                                               (0xC0000000&((data)<<30))
#define ISO_MUXPAD0_etn_led_rxtx_src(data)                                           ((0xC0000000&(data))>>30)
#define ISO_MUXPAD0_get_etn_led_rxtx(data)                                           ((0xC0000000&(data))>>30)
#define ISO_MUXPAD0_etn_led_link_shift                                               (28)
#define ISO_MUXPAD0_etn_led_link_mask                                                (0x30000000)
#define ISO_MUXPAD0_etn_led_link(data)                                               (0x30000000&((data)<<28))
#define ISO_MUXPAD0_etn_led_link_src(data)                                           ((0x30000000&(data))>>28)
#define ISO_MUXPAD0_get_etn_led_link(data)                                           ((0x30000000&(data))>>28)
#define ISO_MUXPAD0_i2c_sda_0_shift                                                  (26)
#define ISO_MUXPAD0_i2c_sda_0_mask                                                   (0x0C000000)
#define ISO_MUXPAD0_i2c_sda_0(data)                                                  (0x0C000000&((data)<<26))
#define ISO_MUXPAD0_i2c_sda_0_src(data)                                              ((0x0C000000&(data))>>26)
#define ISO_MUXPAD0_get_i2c_sda_0(data)                                              ((0x0C000000&(data))>>26)
#define ISO_MUXPAD0_i2c_scl_0_shift                                                  (24)
#define ISO_MUXPAD0_i2c_scl_0_mask                                                   (0x03000000)
#define ISO_MUXPAD0_i2c_scl_0(data)                                                  (0x03000000&((data)<<24))
#define ISO_MUXPAD0_i2c_scl_0_src(data)                                              ((0x03000000&(data))>>24)
#define ISO_MUXPAD0_get_i2c_scl_0(data)                                              ((0x03000000&(data))>>24)
#define ISO_MUXPAD0_ur0_tx_shift                                                     (22)
#define ISO_MUXPAD0_ur0_tx_mask                                                      (0x00C00000)
#define ISO_MUXPAD0_ur0_tx(data)                                                     (0x00C00000&((data)<<22))
#define ISO_MUXPAD0_ur0_tx_src(data)                                                 ((0x00C00000&(data))>>22)
#define ISO_MUXPAD0_get_ur0_tx(data)                                                 ((0x00C00000&(data))>>22)
#define ISO_MUXPAD0_ur0_rx_shift                                                     (20)
#define ISO_MUXPAD0_ur0_rx_mask                                                      (0x00300000)
#define ISO_MUXPAD0_ur0_rx(data)                                                     (0x00300000&((data)<<20))
#define ISO_MUXPAD0_ur0_rx_src(data)                                                 ((0x00300000&(data))>>20)
#define ISO_MUXPAD0_get_ur0_rx(data)                                                 ((0x00300000&(data))>>20)
#define ISO_MUXPAD0_ur1_cts_n_shift                                                  (18)
#define ISO_MUXPAD0_ur1_cts_n_mask                                                   (0x000C0000)
#define ISO_MUXPAD0_ur1_cts_n(data)                                                  (0x000C0000&((data)<<18))
#define ISO_MUXPAD0_ur1_cts_n_src(data)                                              ((0x000C0000&(data))>>18)
#define ISO_MUXPAD0_get_ur1_cts_n(data)                                              ((0x000C0000&(data))>>18)
#define ISO_MUXPAD0_ur1_rts_n_shift                                                  (16)
#define ISO_MUXPAD0_ur1_rts_n_mask                                                   (0x00030000)
#define ISO_MUXPAD0_ur1_rts_n(data)                                                  (0x00030000&((data)<<16))
#define ISO_MUXPAD0_ur1_rts_n_src(data)                                              ((0x00030000&(data))>>16)
#define ISO_MUXPAD0_get_ur1_rts_n(data)                                              ((0x00030000&(data))>>16)
#define ISO_MUXPAD0_ur1_tx_shift                                                     (14)
#define ISO_MUXPAD0_ur1_tx_mask                                                      (0x0000C000)
#define ISO_MUXPAD0_ur1_tx(data)                                                     (0x0000C000&((data)<<14))
#define ISO_MUXPAD0_ur1_tx_src(data)                                                 ((0x0000C000&(data))>>14)
#define ISO_MUXPAD0_get_ur1_tx(data)                                                 ((0x0000C000&(data))>>14)
#define ISO_MUXPAD0_ur1_rx_shift                                                     (12)
#define ISO_MUXPAD0_ur1_rx_mask                                                      (0x00003000)
#define ISO_MUXPAD0_ur1_rx(data)                                                     (0x00003000&((data)<<12))
#define ISO_MUXPAD0_ur1_rx_src(data)                                                 ((0x00003000&(data))>>12)
#define ISO_MUXPAD0_get_ur1_rx(data)                                                 ((0x00003000&(data))>>12)
#define ISO_MUXPAD0_usb1_shift                                                       (10)
#define ISO_MUXPAD0_usb1_mask                                                        (0x00000C00)
#define ISO_MUXPAD0_usb1(data)                                                       (0x00000C00&((data)<<10))
#define ISO_MUXPAD0_usb1_src(data)                                                   ((0x00000C00&(data))>>10)
#define ISO_MUXPAD0_get_usb1(data)                                                   ((0x00000C00&(data))>>10)
#define ISO_MUXPAD0_usb0_shift                                                       (8)
#define ISO_MUXPAD0_usb0_mask                                                        (0x00000300)
#define ISO_MUXPAD0_usb0(data)                                                       (0x00000300&((data)<<8))
#define ISO_MUXPAD0_usb0_src(data)                                                   ((0x00000300&(data))>>8)
#define ISO_MUXPAD0_get_usb0(data)                                                   ((0x00000300&(data))>>8)
#define ISO_MUXPAD0_ir_rx_shift                                                      (6)
#define ISO_MUXPAD0_ir_rx_mask                                                       (0x000000C0)
#define ISO_MUXPAD0_ir_rx(data)                                                      (0x000000C0&((data)<<6))
#define ISO_MUXPAD0_ir_rx_src(data)                                                  ((0x000000C0&(data))>>6)
#define ISO_MUXPAD0_get_ir_rx(data)                                                  ((0x000000C0&(data))>>6)
#define ISO_MUXPAD0_vfd_cs_n_shift                                                   (4)
#define ISO_MUXPAD0_vfd_cs_n_mask                                                    (0x00000030)
#define ISO_MUXPAD0_vfd_cs_n(data)                                                   (0x00000030&((data)<<4))
#define ISO_MUXPAD0_vfd_cs_n_src(data)                                               ((0x00000030&(data))>>4)
#define ISO_MUXPAD0_get_vfd_cs_n(data)                                               ((0x00000030&(data))>>4)
#define ISO_MUXPAD0_vfd_clk_shift                                                    (2)
#define ISO_MUXPAD0_vfd_clk_mask                                                     (0x0000000C)
#define ISO_MUXPAD0_vfd_clk(data)                                                    (0x0000000C&((data)<<2))
#define ISO_MUXPAD0_vfd_clk_src(data)                                                ((0x0000000C&(data))>>2)
#define ISO_MUXPAD0_get_vfd_clk(data)                                                ((0x0000000C&(data))>>2)
#define ISO_MUXPAD0_vfd_d_shift                                                      (0)
#define ISO_MUXPAD0_vfd_d_mask                                                       (0x00000003)
#define ISO_MUXPAD0_vfd_d(data)                                                      (0x00000003&((data)<<0))
#define ISO_MUXPAD0_vfd_d_src(data)                                                  ((0x00000003&(data))>>0)
#define ISO_MUXPAD0_get_vfd_d(data)                                                  ((0x00000003&(data))>>0)


#define ISO_MUXPAD1                                                                  0x18007314
#define ISO_MUXPAD1_reg_addr                                                         "0xB8007314"
#define ISO_MUXPAD1_reg                                                              0xB8007314
#define set_ISO_MUXPAD1_reg(data)   (*((volatile unsigned int*) ISO_MUXPAD1_reg)=data)
#define get_ISO_MUXPAD1_reg   (*((volatile unsigned int*) ISO_MUXPAD1_reg))
#define ISO_MUXPAD1_inst_adr                                                         "0x00C5"
#define ISO_MUXPAD1_inst                                                             0x00C5
#define ISO_MUXPAD1_ai_loc_shift                                                     (30)
#define ISO_MUXPAD1_ai_loc_mask                                                      (0xC0000000)
#define ISO_MUXPAD1_ai_loc(data)                                                     (0xC0000000&((data)<<30))
#define ISO_MUXPAD1_ai_loc_src(data)                                                 ((0xC0000000&(data))>>30)
#define ISO_MUXPAD1_get_ai_loc(data)                                                 ((0xC0000000&(data))>>30)
#define ISO_MUXPAD1_ejtag_avcpu_loc_shift                                            (28)
#define ISO_MUXPAD1_ejtag_avcpu_loc_mask                                             (0x30000000)
#define ISO_MUXPAD1_ejtag_avcpu_loc(data)                                            (0x30000000&((data)<<28))
#define ISO_MUXPAD1_ejtag_avcpu_loc_src(data)                                        ((0x30000000&(data))>>28)
#define ISO_MUXPAD1_get_ejtag_avcpu_loc(data)                                        ((0x30000000&(data))>>28)
#define ISO_MUXPAD1_ur1_loc_shift                                                    (26)
#define ISO_MUXPAD1_ur1_loc_mask                                                     (0x0C000000)
#define ISO_MUXPAD1_ur1_loc(data)                                                    (0x0C000000&((data)<<26))
#define ISO_MUXPAD1_ur1_loc_src(data)                                                ((0x0C000000&(data))>>26)
#define ISO_MUXPAD1_get_ur1_loc(data)                                                ((0x0C000000&(data))>>26)
#define ISO_MUXPAD1_pwm_01_open_drain_switch_shift                                   (25)
#define ISO_MUXPAD1_pwm_01_open_drain_switch_mask                                    (0x02000000)
#define ISO_MUXPAD1_pwm_01_open_drain_switch(data)                                   (0x02000000&((data)<<25))
#define ISO_MUXPAD1_pwm_01_open_drain_switch_src(data)                               ((0x02000000&(data))>>25)
#define ISO_MUXPAD1_get_pwm_01_open_drain_switch(data)                               ((0x02000000&(data))>>25)
#define ISO_MUXPAD1_pwm_23_open_drain_switch_shift                                   (24)
#define ISO_MUXPAD1_pwm_23_open_drain_switch_mask                                    (0x01000000)
#define ISO_MUXPAD1_pwm_23_open_drain_switch(data)                                   (0x01000000&((data)<<24))
#define ISO_MUXPAD1_pwm_23_open_drain_switch_src(data)                               ((0x01000000&(data))>>24)
#define ISO_MUXPAD1_get_pwm_23_open_drain_switch(data)                               ((0x01000000&(data))>>24)
#define ISO_MUXPAD1_ir_tx_shift                                                      (4)
#define ISO_MUXPAD1_ir_tx_mask                                                       (0x00000030)
#define ISO_MUXPAD1_ir_tx(data)                                                      (0x00000030&((data)<<4))
#define ISO_MUXPAD1_ir_tx_src(data)                                                  ((0x00000030&(data))>>4)
#define ISO_MUXPAD1_get_ir_tx(data)                                                  ((0x00000030&(data))>>4)
#define ISO_MUXPAD1_i2c_sda_6_shift                                                  (2)
#define ISO_MUXPAD1_i2c_sda_6_mask                                                   (0x0000000C)
#define ISO_MUXPAD1_i2c_sda_6(data)                                                  (0x0000000C&((data)<<2))
#define ISO_MUXPAD1_i2c_sda_6_src(data)                                              ((0x0000000C&(data))>>2)
#define ISO_MUXPAD1_get_i2c_sda_6(data)                                              ((0x0000000C&(data))>>2)
#define ISO_MUXPAD1_i2c_scl_6_shift                                                  (0)
#define ISO_MUXPAD1_i2c_scl_6_mask                                                   (0x00000003)
#define ISO_MUXPAD1_i2c_scl_6(data)                                                  (0x00000003&((data)<<0))
#define ISO_MUXPAD1_i2c_scl_6_src(data)                                              ((0x00000003&(data))>>0)
#define ISO_MUXPAD1_get_i2c_scl_6(data)                                              ((0x00000003&(data))>>0)


#define ISO_IR_PSR                                                                   0x18007400
#define ISO_IR_PSR_reg_addr                                                          "0xB8007400"
#define ISO_IR_PSR_reg                                                               0xB8007400
#define set_ISO_IR_PSR_reg(data)   (*((volatile unsigned int*) ISO_IR_PSR_reg)=data)
#define get_ISO_IR_PSR_reg   (*((volatile unsigned int*) ISO_IR_PSR_reg))
#define ISO_IR_PSR_inst_adr                                                          "0x0000"
#define ISO_IR_PSR_inst                                                              0x0000
#define ISO_IR_PSR_irrbl_shift                                                       (24)
#define ISO_IR_PSR_irrbl_mask                                                        (0xFF000000)
#define ISO_IR_PSR_irrbl(data)                                                       (0xFF000000&((data)<<24))
#define ISO_IR_PSR_irrbl_src(data)                                                   ((0xFF000000&(data))>>24)
#define ISO_IR_PSR_get_irrbl(data)                                                   ((0xFF000000&(data))>>24)
#define ISO_IR_PSR_irrml_shift                                                       (16)
#define ISO_IR_PSR_irrml_mask                                                        (0x00FF0000)
#define ISO_IR_PSR_irrml(data)                                                       (0x00FF0000&((data)<<16))
#define ISO_IR_PSR_irrml_src(data)                                                   ((0x00FF0000&(data))>>16)
#define ISO_IR_PSR_get_irrml(data)                                                   ((0x00FF0000&(data))>>16)
#define ISO_IR_PSR_irrdzl_shift                                                      (8)
#define ISO_IR_PSR_irrdzl_mask                                                       (0x0000FF00)
#define ISO_IR_PSR_irrdzl(data)                                                      (0x0000FF00&((data)<<8))
#define ISO_IR_PSR_irrdzl_src(data)                                                  ((0x0000FF00&(data))>>8)
#define ISO_IR_PSR_get_irrdzl(data)                                                  ((0x0000FF00&(data))>>8)
#define ISO_IR_PSR_irrdol_shift                                                      (0)
#define ISO_IR_PSR_irrdol_mask                                                       (0x000000FF)
#define ISO_IR_PSR_irrdol(data)                                                      (0x000000FF&((data)<<0))
#define ISO_IR_PSR_irrdol_src(data)                                                  ((0x000000FF&(data))>>0)
#define ISO_IR_PSR_get_irrdol(data)                                                  ((0x000000FF&(data))>>0)


#define ISO_IR_PER                                                                   0x18007404
#define ISO_IR_PER_reg_addr                                                          "0xB8007404"
#define ISO_IR_PER_reg                                                               0xB8007404
#define set_ISO_IR_PER_reg(data)   (*((volatile unsigned int*) ISO_IR_PER_reg)=data)
#define get_ISO_IR_PER_reg   (*((volatile unsigned int*) ISO_IR_PER_reg))
#define ISO_IR_PER_inst_adr                                                          "0x0001"
#define ISO_IR_PER_inst                                                              0x0001
#define ISO_IR_PER_irrdl_shift                                                       (16)
#define ISO_IR_PER_irrdl_mask                                                        (0x003F0000)
#define ISO_IR_PER_irrdl(data)                                                       (0x003F0000&((data)<<16))
#define ISO_IR_PER_irrdl_src(data)                                                   ((0x003F0000&(data))>>16)
#define ISO_IR_PER_get_irrdl(data)                                                   ((0x003F0000&(data))>>16)
#define ISO_IR_PER_irrrl_shift                                                       (8)
#define ISO_IR_PER_irrrl_mask                                                        (0x0000FF00)
#define ISO_IR_PER_irrrl(data)                                                       (0x0000FF00&((data)<<8))
#define ISO_IR_PER_irrrl_src(data)                                                   ((0x0000FF00&(data))>>8)
#define ISO_IR_PER_get_irrrl(data)                                                   ((0x0000FF00&(data))>>8)
#define ISO_IR_PER_irrsl_shift                                                       (0)
#define ISO_IR_PER_irrsl_mask                                                        (0x000000FF)
#define ISO_IR_PER_irrsl(data)                                                       (0x000000FF&((data)<<0))
#define ISO_IR_PER_irrsl_src(data)                                                   ((0x000000FF&(data))>>0)
#define ISO_IR_PER_get_irrsl(data)                                                   ((0x000000FF&(data))>>0)


#define ISO_IR_SF                                                                    0x18007408
#define ISO_IR_SF_reg_addr                                                           "0xB8007408"
#define ISO_IR_SF_reg                                                                0xB8007408
#define set_ISO_IR_SF_reg(data)   (*((volatile unsigned int*) ISO_IR_SF_reg)=data)
#define get_ISO_IR_SF_reg   (*((volatile unsigned int*) ISO_IR_SF_reg))
#define ISO_IR_SF_inst_adr                                                           "0x0002"
#define ISO_IR_SF_inst                                                               0x0002
#define ISO_IR_SF_irfd_shift                                                         (0)
#define ISO_IR_SF_irfd_mask                                                          (0x0000FFFF)
#define ISO_IR_SF_irfd(data)                                                         (0x0000FFFF&((data)<<0))
#define ISO_IR_SF_irfd_src(data)                                                     ((0x0000FFFF&(data))>>0)
#define ISO_IR_SF_get_irfd(data)                                                     ((0x0000FFFF&(data))>>0)


#define ISO_IR_DPIR                                                                  0x1800740C
#define ISO_IR_DPIR_reg_addr                                                         "0xB800740C"
#define ISO_IR_DPIR_reg                                                              0xB800740C
#define set_ISO_IR_DPIR_reg(data)   (*((volatile unsigned int*) ISO_IR_DPIR_reg)=data)
#define get_ISO_IR_DPIR_reg   (*((volatile unsigned int*) ISO_IR_DPIR_reg))
#define ISO_IR_DPIR_inst_adr                                                         "0x0003"
#define ISO_IR_DPIR_inst                                                             0x0003
#define ISO_IR_DPIR_iriotcdp_shift                                                   (0)
#define ISO_IR_DPIR_iriotcdp_mask                                                    (0x0000FFFF)
#define ISO_IR_DPIR_iriotcdp(data)                                                   (0x0000FFFF&((data)<<0))
#define ISO_IR_DPIR_iriotcdp_src(data)                                               ((0x0000FFFF&(data))>>0)
#define ISO_IR_DPIR_get_iriotcdp(data)                                               ((0x0000FFFF&(data))>>0)


#define ISO_IR_CR                                                                    0x18007410
#define ISO_IR_CR_reg_addr                                                           "0xB8007410"
#define ISO_IR_CR_reg                                                                0xB8007410
#define set_ISO_IR_CR_reg(data)   (*((volatile unsigned int*) ISO_IR_CR_reg)=data)
#define get_ISO_IR_CR_reg   (*((volatile unsigned int*) ISO_IR_CR_reg))
#define ISO_IR_CR_inst_adr                                                           "0x0004"
#define ISO_IR_CR_inst                                                               0x0004
#define ISO_IR_CR_irsr_shift                                                         (31)
#define ISO_IR_CR_irsr_mask                                                          (0x80000000)
#define ISO_IR_CR_irsr(data)                                                         (0x80000000&((data)<<31))
#define ISO_IR_CR_irsr_src(data)                                                     ((0x80000000&(data))>>31)
#define ISO_IR_CR_get_irsr(data)                                                     ((0x80000000&(data))>>31)
#define ISO_IR_CR_rcmm_en_shift                                                      (25)
#define ISO_IR_CR_rcmm_en_mask                                                       (0x02000000)
#define ISO_IR_CR_rcmm_en(data)                                                      (0x02000000&((data)<<25))
#define ISO_IR_CR_rcmm_en_src(data)                                                  ((0x02000000&(data))>>25)
#define ISO_IR_CR_get_rcmm_en(data)                                                  ((0x02000000&(data))>>25)
#define ISO_IR_CR_toshiba_en_shift                                                   (24)
#define ISO_IR_CR_toshiba_en_mask                                                    (0x01000000)
#define ISO_IR_CR_toshiba_en(data)                                                   (0x01000000&((data)<<24))
#define ISO_IR_CR_toshiba_en_src(data)                                               ((0x01000000&(data))>>24)
#define ISO_IR_CR_get_toshiba_en(data)                                               ((0x01000000&(data))>>24)
#define ISO_IR_CR_irednm_shift                                                       (23)
#define ISO_IR_CR_irednm_mask                                                        (0x00800000)
#define ISO_IR_CR_irednm(data)                                                       (0x00800000&((data)<<23))
#define ISO_IR_CR_irednm_src(data)                                                   ((0x00800000&(data))>>23)
#define ISO_IR_CR_get_irednm(data)                                                   ((0x00800000&(data))>>23)
#define ISO_IR_CR_iredn_shift                                                        (16)
#define ISO_IR_CR_iredn_mask                                                         (0x003F0000)
#define ISO_IR_CR_iredn(data)                                                        (0x003F0000&((data)<<16))
#define ISO_IR_CR_iredn_src(data)                                                    ((0x003F0000&(data))>>16)
#define ISO_IR_CR_get_iredn(data)                                                    ((0x003F0000&(data))>>16)
#define ISO_IR_CR_raw_fifo_ov_shift                                                  (14)
#define ISO_IR_CR_raw_fifo_ov_mask                                                   (0x00004000)
#define ISO_IR_CR_raw_fifo_ov(data)                                                  (0x00004000&((data)<<14))
#define ISO_IR_CR_raw_fifo_ov_src(data)                                              ((0x00004000&(data))>>14)
#define ISO_IR_CR_get_raw_fifo_ov(data)                                              ((0x00004000&(data))>>14)
#define ISO_IR_CR_raw_fifo_val_shift                                                 (13)
#define ISO_IR_CR_raw_fifo_val_mask                                                  (0x00002000)
#define ISO_IR_CR_raw_fifo_val(data)                                                 (0x00002000&((data)<<13))
#define ISO_IR_CR_raw_fifo_val_src(data)                                             ((0x00002000&(data))>>13)
#define ISO_IR_CR_get_raw_fifo_val(data)                                             ((0x00002000&(data))>>13)
#define ISO_IR_CR_raw_en_shift                                                       (12)
#define ISO_IR_CR_raw_en_mask                                                        (0x00001000)
#define ISO_IR_CR_raw_en(data)                                                       (0x00001000&((data)<<12))
#define ISO_IR_CR_raw_en_src(data)                                                   ((0x00001000&(data))>>12)
#define ISO_IR_CR_get_raw_en(data)                                                   ((0x00001000&(data))>>12)
#define ISO_IR_CR_mlae_shift                                                         (11)
#define ISO_IR_CR_mlae_mask                                                          (0x00000800)
#define ISO_IR_CR_mlae(data)                                                         (0x00000800&((data)<<11))
#define ISO_IR_CR_mlae_src(data)                                                     ((0x00000800&(data))>>11)
#define ISO_IR_CR_get_mlae(data)                                                     ((0x00000800&(data))>>11)
#define ISO_IR_CR_irie_shift                                                         (10)
#define ISO_IR_CR_irie_mask                                                          (0x00000400)
#define ISO_IR_CR_irie(data)                                                         (0x00000400&((data)<<10))
#define ISO_IR_CR_irie_src(data)                                                     ((0x00000400&(data))>>10)
#define ISO_IR_CR_get_irie(data)                                                     ((0x00000400&(data))>>10)
#define ISO_IR_CR_irres_shift                                                        (9)
#define ISO_IR_CR_irres_mask                                                         (0x00000200)
#define ISO_IR_CR_irres(data)                                                        (0x00000200&((data)<<9))
#define ISO_IR_CR_irres_src(data)                                                    ((0x00000200&(data))>>9)
#define ISO_IR_CR_get_irres(data)                                                    ((0x00000200&(data))>>9)
#define ISO_IR_CR_irue_shift                                                         (8)
#define ISO_IR_CR_irue_mask                                                          (0x00000100)
#define ISO_IR_CR_irue(data)                                                         (0x00000100&((data)<<8))
#define ISO_IR_CR_irue_src(data)                                                     ((0x00000100&(data))>>8)
#define ISO_IR_CR_get_irue(data)                                                     ((0x00000100&(data))>>8)
#define ISO_IR_CR_ircm_shift                                                         (7)
#define ISO_IR_CR_ircm_mask                                                          (0x00000080)
#define ISO_IR_CR_ircm(data)                                                         (0x00000080&((data)<<7))
#define ISO_IR_CR_ircm_src(data)                                                     ((0x00000080&(data))>>7)
#define ISO_IR_CR_get_ircm(data)                                                     ((0x00000080&(data))>>7)
#define ISO_IR_CR_irbme_shift                                                        (6)
#define ISO_IR_CR_irbme_mask                                                         (0x00000040)
#define ISO_IR_CR_irbme(data)                                                        (0x00000040&((data)<<6))
#define ISO_IR_CR_irbme_src(data)                                                    ((0x00000040&(data))>>6)
#define ISO_IR_CR_get_irbme(data)                                                    ((0x00000040&(data))>>6)
#define ISO_IR_CR_irdpm_shift                                                        (5)
#define ISO_IR_CR_irdpm_mask                                                         (0x00000020)
#define ISO_IR_CR_irdpm(data)                                                        (0x00000020&((data)<<5))
#define ISO_IR_CR_irdpm_src(data)                                                    ((0x00000020&(data))>>5)
#define ISO_IR_CR_get_irdpm(data)                                                    ((0x00000020&(data))>>5)
#define ISO_IR_CR_irdn_shift                                                         (0)
#define ISO_IR_CR_irdn_mask                                                          (0x0000001F)
#define ISO_IR_CR_irdn(data)                                                         (0x0000001F&((data)<<0))
#define ISO_IR_CR_irdn_src(data)                                                     ((0x0000001F&(data))>>0)
#define ISO_IR_CR_get_irdn(data)                                                     ((0x0000001F&(data))>>0)


#define ISO_IR_RP                                                                    0x18007414
#define ISO_IR_RP_reg_addr                                                           "0xB8007414"
#define ISO_IR_RP_reg                                                                0xB8007414
#define set_ISO_IR_RP_reg(data)   (*((volatile unsigned int*) ISO_IR_RP_reg)=data)
#define get_ISO_IR_RP_reg   (*((volatile unsigned int*) ISO_IR_RP_reg))
#define ISO_IR_RP_inst_adr                                                           "0x0005"
#define ISO_IR_RP_inst                                                               0x0005
#define ISO_IR_RP_irrp_shift                                                         (0)
#define ISO_IR_RP_irrp_mask                                                          (0xFFFFFFFF)
#define ISO_IR_RP_irrp(data)                                                         (0xFFFFFFFF&((data)<<0))
#define ISO_IR_RP_irrp_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define ISO_IR_RP_get_irrp(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define ISO_IR_SR                                                                    0x18007418
#define ISO_IR_SR_reg_addr                                                           "0xB8007418"
#define ISO_IR_SR_reg                                                                0xB8007418
#define set_ISO_IR_SR_reg(data)   (*((volatile unsigned int*) ISO_IR_SR_reg)=data)
#define get_ISO_IR_SR_reg   (*((volatile unsigned int*) ISO_IR_SR_reg))
#define ISO_IR_SR_inst_adr                                                           "0x0006"
#define ISO_IR_SR_inst                                                               0x0006
#define ISO_IR_SR_slen_big_shift                                                     (5)
#define ISO_IR_SR_slen_big_mask                                                      (0x00000020)
#define ISO_IR_SR_slen_big(data)                                                     (0x00000020&((data)<<5))
#define ISO_IR_SR_slen_big_src(data)                                                 ((0x00000020&(data))>>5)
#define ISO_IR_SR_get_slen_big(data)                                                 ((0x00000020&(data))>>5)
#define ISO_IR_SR_blen_big_shift                                                     (4)
#define ISO_IR_SR_blen_big_mask                                                      (0x00000010)
#define ISO_IR_SR_blen_big(data)                                                     (0x00000010&((data)<<4))
#define ISO_IR_SR_blen_big_src(data)                                                 ((0x00000010&(data))>>4)
#define ISO_IR_SR_get_blen_big(data)                                                 ((0x00000010&(data))>>4)
#define ISO_IR_SR_raw_fifo_ov_shift                                                  (3)
#define ISO_IR_SR_raw_fifo_ov_mask                                                   (0x00000008)
#define ISO_IR_SR_raw_fifo_ov(data)                                                  (0x00000008&((data)<<3))
#define ISO_IR_SR_raw_fifo_ov_src(data)                                              ((0x00000008&(data))>>3)
#define ISO_IR_SR_get_raw_fifo_ov(data)                                              ((0x00000008&(data))>>3)
#define ISO_IR_SR_raw_fifo_val_shift                                                 (2)
#define ISO_IR_SR_raw_fifo_val_mask                                                  (0x00000004)
#define ISO_IR_SR_raw_fifo_val(data)                                                 (0x00000004&((data)<<2))
#define ISO_IR_SR_raw_fifo_val_src(data)                                             ((0x00000004&(data))>>2)
#define ISO_IR_SR_get_raw_fifo_val(data)                                             ((0x00000004&(data))>>2)
#define ISO_IR_SR_irrf_shift                                                         (1)
#define ISO_IR_SR_irrf_mask                                                          (0x00000002)
#define ISO_IR_SR_irrf(data)                                                         (0x00000002&((data)<<1))
#define ISO_IR_SR_irrf_src(data)                                                     ((0x00000002&(data))>>1)
#define ISO_IR_SR_get_irrf(data)                                                     ((0x00000002&(data))>>1)
#define ISO_IR_SR_irdvf_shift                                                        (0)
#define ISO_IR_SR_irdvf_mask                                                         (0x00000001)
#define ISO_IR_SR_irdvf(data)                                                        (0x00000001&((data)<<0))
#define ISO_IR_SR_irdvf_src(data)                                                    ((0x00000001&(data))>>0)
#define ISO_IR_SR_get_irdvf(data)                                                    ((0x00000001&(data))>>0)


#define ISO_IR_RAW_CTRL                                                              0x1800741C
#define ISO_IR_RAW_CTRL_reg_addr                                                     "0xB800741C"
#define ISO_IR_RAW_CTRL_reg                                                          0xB800741C
#define set_ISO_IR_RAW_CTRL_reg(data)   (*((volatile unsigned int*) ISO_IR_RAW_CTRL_reg)=data)
#define get_ISO_IR_RAW_CTRL_reg   (*((volatile unsigned int*) ISO_IR_RAW_CTRL_reg))
#define ISO_IR_RAW_CTRL_inst_adr                                                     "0x0007"
#define ISO_IR_RAW_CTRL_inst                                                         0x0007
#define ISO_IR_RAW_CTRL_write_en2_shift                                              (25)
#define ISO_IR_RAW_CTRL_write_en2_mask                                               (0x02000000)
#define ISO_IR_RAW_CTRL_write_en2(data)                                              (0x02000000&((data)<<25))
#define ISO_IR_RAW_CTRL_write_en2_src(data)                                          ((0x02000000&(data))>>25)
#define ISO_IR_RAW_CTRL_get_write_en2(data)                                          ((0x02000000&(data))>>25)
#define ISO_IR_RAW_CTRL_stop_sample_shift                                            (24)
#define ISO_IR_RAW_CTRL_stop_sample_mask                                             (0x01000000)
#define ISO_IR_RAW_CTRL_stop_sample(data)                                            (0x01000000&((data)<<24))
#define ISO_IR_RAW_CTRL_stop_sample_src(data)                                        ((0x01000000&(data))>>24)
#define ISO_IR_RAW_CTRL_get_stop_sample(data)                                        ((0x01000000&(data))>>24)
#define ISO_IR_RAW_CTRL_stop_time_shift                                              (8)
#define ISO_IR_RAW_CTRL_stop_time_mask                                               (0x00FFFF00)
#define ISO_IR_RAW_CTRL_stop_time(data)                                              (0x00FFFF00&((data)<<8))
#define ISO_IR_RAW_CTRL_stop_time_src(data)                                          ((0x00FFFF00&(data))>>8)
#define ISO_IR_RAW_CTRL_get_stop_time(data)                                          ((0x00FFFF00&(data))>>8)
#define ISO_IR_RAW_CTRL_write_en1_shift                                              (6)
#define ISO_IR_RAW_CTRL_write_en1_mask                                               (0x00000040)
#define ISO_IR_RAW_CTRL_write_en1(data)                                              (0x00000040&((data)<<6))
#define ISO_IR_RAW_CTRL_write_en1_src(data)                                          ((0x00000040&(data))>>6)
#define ISO_IR_RAW_CTRL_get_write_en1(data)                                          ((0x00000040&(data))>>6)
#define ISO_IR_RAW_CTRL_fifo_thr_shift                                               (0)
#define ISO_IR_RAW_CTRL_fifo_thr_mask                                                (0x0000003F)
#define ISO_IR_RAW_CTRL_fifo_thr(data)                                               (0x0000003F&((data)<<0))
#define ISO_IR_RAW_CTRL_fifo_thr_src(data)                                           ((0x0000003F&(data))>>0)
#define ISO_IR_RAW_CTRL_get_fifo_thr(data)                                           ((0x0000003F&(data))>>0)


#define ISO_IR_RAW_FF                                                                0x18007420
#define ISO_IR_RAW_FF_reg_addr                                                       "0xB8007420"
#define ISO_IR_RAW_FF_reg                                                            0xB8007420
#define set_ISO_IR_RAW_FF_reg(data)   (*((volatile unsigned int*) ISO_IR_RAW_FF_reg)=data)
#define get_ISO_IR_RAW_FF_reg   (*((volatile unsigned int*) ISO_IR_RAW_FF_reg))
#define ISO_IR_RAW_FF_inst_adr                                                       "0x0008"
#define ISO_IR_RAW_FF_inst                                                           0x0008
#define ISO_IR_RAW_FF_dat_shift                                                      (0)
#define ISO_IR_RAW_FF_dat_mask                                                       (0xFFFFFFFF)
#define ISO_IR_RAW_FF_dat(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_IR_RAW_FF_dat_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_IR_RAW_FF_get_dat(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_IR_RAW_SAMPLE_TIME                                                       0x18007424
#define ISO_IR_RAW_SAMPLE_TIME_reg_addr                                              "0xB8007424"
#define ISO_IR_RAW_SAMPLE_TIME_reg                                                   0xB8007424
#define set_ISO_IR_RAW_SAMPLE_TIME_reg(data)   (*((volatile unsigned int*) ISO_IR_RAW_SAMPLE_TIME_reg)=data)
#define get_ISO_IR_RAW_SAMPLE_TIME_reg   (*((volatile unsigned int*) ISO_IR_RAW_SAMPLE_TIME_reg))
#define ISO_IR_RAW_SAMPLE_TIME_inst_adr                                              "0x0009"
#define ISO_IR_RAW_SAMPLE_TIME_inst                                                  0x0009
#define ISO_IR_RAW_SAMPLE_TIME_cnt_shift                                             (0)
#define ISO_IR_RAW_SAMPLE_TIME_cnt_mask                                              (0x0000FFFF)
#define ISO_IR_RAW_SAMPLE_TIME_cnt(data)                                             (0x0000FFFF&((data)<<0))
#define ISO_IR_RAW_SAMPLE_TIME_cnt_src(data)                                         ((0x0000FFFF&(data))>>0)
#define ISO_IR_RAW_SAMPLE_TIME_get_cnt(data)                                         ((0x0000FFFF&(data))>>0)


#define ISO_IR_RAW_WL                                                                0x18007428
#define ISO_IR_RAW_WL_reg_addr                                                       "0xB8007428"
#define ISO_IR_RAW_WL_reg                                                            0xB8007428
#define set_ISO_IR_RAW_WL_reg(data)   (*((volatile unsigned int*) ISO_IR_RAW_WL_reg)=data)
#define get_ISO_IR_RAW_WL_reg   (*((volatile unsigned int*) ISO_IR_RAW_WL_reg))
#define ISO_IR_RAW_WL_inst_adr                                                       "0x000A"
#define ISO_IR_RAW_WL_inst                                                           0x000A
#define ISO_IR_RAW_WL_val_shift                                                      (0)
#define ISO_IR_RAW_WL_val_mask                                                       (0x0000003F)
#define ISO_IR_RAW_WL_val(data)                                                      (0x0000003F&((data)<<0))
#define ISO_IR_RAW_WL_val_src(data)                                                  ((0x0000003F&(data))>>0)
#define ISO_IR_RAW_WL_get_val(data)                                                  ((0x0000003F&(data))>>0)


#define ISO_IR_RAW_DEB                                                               0x1800742C
#define ISO_IR_RAW_DEB_reg_addr                                                      "0xB800742C"
#define ISO_IR_RAW_DEB_reg                                                           0xB800742C
#define set_ISO_IR_RAW_DEB_reg(data)   (*((volatile unsigned int*) ISO_IR_RAW_DEB_reg)=data)
#define get_ISO_IR_RAW_DEB_reg   (*((volatile unsigned int*) ISO_IR_RAW_DEB_reg))
#define ISO_IR_RAW_DEB_inst_adr                                                      "0x000B"
#define ISO_IR_RAW_DEB_inst                                                          0x000B
#define ISO_IR_RAW_DEB_len_shift                                                     (16)
#define ISO_IR_RAW_DEB_len_mask                                                      (0x00FF0000)
#define ISO_IR_RAW_DEB_len(data)                                                     (0x00FF0000&((data)<<16))
#define ISO_IR_RAW_DEB_len_src(data)                                                 ((0x00FF0000&(data))>>16)
#define ISO_IR_RAW_DEB_get_len(data)                                                 ((0x00FF0000&(data))>>16)
#define ISO_IR_RAW_DEB_clk_shift                                                     (0)
#define ISO_IR_RAW_DEB_clk_mask                                                      (0x0000FFFF)
#define ISO_IR_RAW_DEB_clk(data)                                                     (0x0000FFFF&((data)<<0))
#define ISO_IR_RAW_DEB_clk_src(data)                                                 ((0x0000FFFF&(data))>>0)
#define ISO_IR_RAW_DEB_get_clk(data)                                                 ((0x0000FFFF&(data))>>0)


#define ISO_IR_PSR_UP                                                                0x18007430
#define ISO_IR_PSR_UP_reg_addr                                                       "0xB8007430"
#define ISO_IR_PSR_UP_reg                                                            0xB8007430
#define set_ISO_IR_PSR_UP_reg(data)   (*((volatile unsigned int*) ISO_IR_PSR_UP_reg)=data)
#define get_ISO_IR_PSR_UP_reg   (*((volatile unsigned int*) ISO_IR_PSR_UP_reg))
#define ISO_IR_PSR_UP_inst_adr                                                       "0x000C"
#define ISO_IR_PSR_UP_inst                                                           0x000C
#define ISO_IR_PSR_UP_irrbl_shift                                                    (24)
#define ISO_IR_PSR_UP_irrbl_mask                                                     (0xFF000000)
#define ISO_IR_PSR_UP_irrbl(data)                                                    (0xFF000000&((data)<<24))
#define ISO_IR_PSR_UP_irrbl_src(data)                                                ((0xFF000000&(data))>>24)
#define ISO_IR_PSR_UP_get_irrbl(data)                                                ((0xFF000000&(data))>>24)
#define ISO_IR_PSR_UP_irrml_shift                                                    (16)
#define ISO_IR_PSR_UP_irrml_mask                                                     (0x00FF0000)
#define ISO_IR_PSR_UP_irrml(data)                                                    (0x00FF0000&((data)<<16))
#define ISO_IR_PSR_UP_irrml_src(data)                                                ((0x00FF0000&(data))>>16)
#define ISO_IR_PSR_UP_get_irrml(data)                                                ((0x00FF0000&(data))>>16)
#define ISO_IR_PSR_UP_irrdzl_shift                                                   (8)
#define ISO_IR_PSR_UP_irrdzl_mask                                                    (0x0000FF00)
#define ISO_IR_PSR_UP_irrdzl(data)                                                   (0x0000FF00&((data)<<8))
#define ISO_IR_PSR_UP_irrdzl_src(data)                                               ((0x0000FF00&(data))>>8)
#define ISO_IR_PSR_UP_get_irrdzl(data)                                               ((0x0000FF00&(data))>>8)
#define ISO_IR_PSR_UP_irrdol_shift                                                   (0)
#define ISO_IR_PSR_UP_irrdol_mask                                                    (0x000000FF)
#define ISO_IR_PSR_UP_irrdol(data)                                                   (0x000000FF&((data)<<0))
#define ISO_IR_PSR_UP_irrdol_src(data)                                               ((0x000000FF&(data))>>0)
#define ISO_IR_PSR_UP_get_irrdol(data)                                               ((0x000000FF&(data))>>0)


#define ISO_IR_PER_UP                                                                0x18007434
#define ISO_IR_PER_UP_reg_addr                                                       "0xB8007434"
#define ISO_IR_PER_UP_reg                                                            0xB8007434
#define set_ISO_IR_PER_UP_reg(data)   (*((volatile unsigned int*) ISO_IR_PER_UP_reg)=data)
#define get_ISO_IR_PER_UP_reg   (*((volatile unsigned int*) ISO_IR_PER_UP_reg))
#define ISO_IR_PER_UP_inst_adr                                                       "0x000D"
#define ISO_IR_PER_UP_inst                                                           0x000D
#define ISO_IR_PER_UP_irrrl_shift                                                    (8)
#define ISO_IR_PER_UP_irrrl_mask                                                     (0x0000FF00)
#define ISO_IR_PER_UP_irrrl(data)                                                    (0x0000FF00&((data)<<8))
#define ISO_IR_PER_UP_irrrl_src(data)                                                ((0x0000FF00&(data))>>8)
#define ISO_IR_PER_UP_get_irrrl(data)                                                ((0x0000FF00&(data))>>8)
#define ISO_IR_PER_UP_irrsl_shift                                                    (0)
#define ISO_IR_PER_UP_irrsl_mask                                                     (0x000000FF)
#define ISO_IR_PER_UP_irrsl(data)                                                    (0x000000FF&((data)<<0))
#define ISO_IR_PER_UP_irrsl_src(data)                                                ((0x000000FF&(data))>>0)
#define ISO_IR_PER_UP_get_irrsl(data)                                                ((0x000000FF&(data))>>0)


#define ISO_IR_CTRL_RC6                                                              0x18007438
#define ISO_IR_CTRL_RC6_reg_addr                                                     "0xB8007438"
#define ISO_IR_CTRL_RC6_reg                                                          0xB8007438
#define set_ISO_IR_CTRL_RC6_reg(data)   (*((volatile unsigned int*) ISO_IR_CTRL_RC6_reg)=data)
#define get_ISO_IR_CTRL_RC6_reg   (*((volatile unsigned int*) ISO_IR_CTRL_RC6_reg))
#define ISO_IR_CTRL_RC6_inst_adr                                                     "0x000E"
#define ISO_IR_CTRL_RC6_inst                                                         0x000E
#define ISO_IR_CTRL_RC6_rc6_en_shift                                                 (8)
#define ISO_IR_CTRL_RC6_rc6_en_mask                                                  (0x00000100)
#define ISO_IR_CTRL_RC6_rc6_en(data)                                                 (0x00000100&((data)<<8))
#define ISO_IR_CTRL_RC6_rc6_en_src(data)                                             ((0x00000100&(data))>>8)
#define ISO_IR_CTRL_RC6_get_rc6_en(data)                                             ((0x00000100&(data))>>8)
#define ISO_IR_CTRL_RC6_irtr_shift                                                   (0)
#define ISO_IR_CTRL_RC6_irtr_mask                                                    (0x000000FF)
#define ISO_IR_CTRL_RC6_irtr(data)                                                   (0x000000FF&((data)<<0))
#define ISO_IR_CTRL_RC6_irtr_src(data)                                               ((0x000000FF&(data))>>0)
#define ISO_IR_CTRL_RC6_get_irtr(data)                                               ((0x000000FF&(data))>>0)


#define ISO_IR_RP2                                                                   0x1800743C
#define ISO_IR_RP2_reg_addr                                                          "0xB800743C"
#define ISO_IR_RP2_reg                                                               0xB800743C
#define set_ISO_IR_RP2_reg(data)   (*((volatile unsigned int*) ISO_IR_RP2_reg)=data)
#define get_ISO_IR_RP2_reg   (*((volatile unsigned int*) ISO_IR_RP2_reg))
#define ISO_IR_RP2_inst_adr                                                          "0x000F"
#define ISO_IR_RP2_inst                                                              0x000F
#define ISO_IR_RP2_irrp_shift                                                        (0)
#define ISO_IR_RP2_irrp_mask                                                         (0xFFFFFFFF)
#define ISO_IR_RP2_irrp(data)                                                        (0xFFFFFFFF&((data)<<0))
#define ISO_IR_RP2_irrp_src(data)                                                    ((0xFFFFFFFF&(data))>>0)
#define ISO_IR_RP2_get_irrp(data)                                                    ((0xFFFFFFFF&(data))>>0)


#define ISO_IRTX_CFG                                                                 0x18007440
#define ISO_IRTX_CFG_reg_addr                                                        "0xB8007440"
#define ISO_IRTX_CFG_reg                                                             0xB8007440
#define set_ISO_IRTX_CFG_reg(data)   (*((volatile unsigned int*) ISO_IRTX_CFG_reg)=data)
#define get_ISO_IRTX_CFG_reg   (*((volatile unsigned int*) ISO_IRTX_CFG_reg))
#define ISO_IRTX_CFG_inst_adr                                                        "0x0010"
#define ISO_IRTX_CFG_inst                                                            0x0010
#define ISO_IRTX_CFG_irtx_en_shift                                                   (31)
#define ISO_IRTX_CFG_irtx_en_mask                                                    (0x80000000)
#define ISO_IRTX_CFG_irtx_en(data)                                                   (0x80000000&((data)<<31))
#define ISO_IRTX_CFG_irtx_en_src(data)                                               ((0x80000000&(data))>>31)
#define ISO_IRTX_CFG_get_irtx_en(data)                                               ((0x80000000&(data))>>31)
#define ISO_IRTX_CFG_iact_lvl_shift                                                  (10)
#define ISO_IRTX_CFG_iact_lvl_mask                                                   (0x00000400)
#define ISO_IRTX_CFG_iact_lvl(data)                                                  (0x00000400&((data)<<10))
#define ISO_IRTX_CFG_iact_lvl_src(data)                                              ((0x00000400&(data))>>10)
#define ISO_IRTX_CFG_get_iact_lvl(data)                                              ((0x00000400&(data))>>10)
#define ISO_IRTX_CFG_modulation_shift                                                (9)
#define ISO_IRTX_CFG_modulation_mask                                                 (0x00000200)
#define ISO_IRTX_CFG_modulation(data)                                                (0x00000200&((data)<<9))
#define ISO_IRTX_CFG_modulation_src(data)                                            ((0x00000200&(data))>>9)
#define ISO_IRTX_CFG_get_modulation(data)                                            ((0x00000200&(data))>>9)
#define ISO_IRTX_CFG_endian_shift                                                    (8)
#define ISO_IRTX_CFG_endian_mask                                                     (0x00000100)
#define ISO_IRTX_CFG_endian(data)                                                    (0x00000100&((data)<<8))
#define ISO_IRTX_CFG_endian_src(data)                                                ((0x00000100&(data))>>8)
#define ISO_IRTX_CFG_get_endian(data)                                                ((0x00000100&(data))>>8)
#define ISO_IRTX_CFG_dummy_shift                                                     (6)
#define ISO_IRTX_CFG_dummy_mask                                                      (0x000000C0)
#define ISO_IRTX_CFG_dummy(data)                                                     (0x000000C0&((data)<<6))
#define ISO_IRTX_CFG_dummy_src(data)                                                 ((0x000000C0&(data))>>6)
#define ISO_IRTX_CFG_get_dummy(data)                                                 ((0x000000C0&(data))>>6)
#define ISO_IRTX_CFG_fifoout_inv_shift                                               (5)
#define ISO_IRTX_CFG_fifoout_inv_mask                                                (0x00000020)
#define ISO_IRTX_CFG_fifoout_inv(data)                                               (0x00000020&((data)<<5))
#define ISO_IRTX_CFG_fifoout_inv_src(data)                                           ((0x00000020&(data))>>5)
#define ISO_IRTX_CFG_get_fifoout_inv(data)                                           ((0x00000020&(data))>>5)
#define ISO_IRTX_CFG_irtxout_inv_shift                                               (4)
#define ISO_IRTX_CFG_irtxout_inv_mask                                                (0x00000010)
#define ISO_IRTX_CFG_irtxout_inv(data)                                               (0x00000010&((data)<<4))
#define ISO_IRTX_CFG_irtxout_inv_src(data)                                           ((0x00000010&(data))>>4)
#define ISO_IRTX_CFG_get_irtxout_inv(data)                                           ((0x00000010&(data))>>4)
#define ISO_IRTX_CFG_start_shift                                                     (0)
#define ISO_IRTX_CFG_start_mask                                                      (0x00000001)
#define ISO_IRTX_CFG_start(data)                                                     (0x00000001&((data)<<0))
#define ISO_IRTX_CFG_start_src(data)                                                 ((0x00000001&(data))>>0)
#define ISO_IRTX_CFG_get_start(data)                                                 ((0x00000001&(data))>>0)


#define ISO_IRTX_TIM                                                                 0x18007444
#define ISO_IRTX_TIM_reg_addr                                                        "0xB8007444"
#define ISO_IRTX_TIM_reg                                                             0xB8007444
#define set_ISO_IRTX_TIM_reg(data)   (*((volatile unsigned int*) ISO_IRTX_TIM_reg)=data)
#define get_ISO_IRTX_TIM_reg   (*((volatile unsigned int*) ISO_IRTX_TIM_reg))
#define ISO_IRTX_TIM_inst_adr                                                        "0x0011"
#define ISO_IRTX_TIM_inst                                                            0x0011
#define ISO_IRTX_TIM_irtx_fd_shift                                                   (0)
#define ISO_IRTX_TIM_irtx_fd_mask                                                    (0x0000FFFF)
#define ISO_IRTX_TIM_irtx_fd(data)                                                   (0x0000FFFF&((data)<<0))
#define ISO_IRTX_TIM_irtx_fd_src(data)                                               ((0x0000FFFF&(data))>>0)
#define ISO_IRTX_TIM_get_irtx_fd(data)                                               ((0x0000FFFF&(data))>>0)


#define ISO_IRTX_PWM_SETTING                                                         0x18007448
#define ISO_IRTX_PWM_SETTING_reg_addr                                                "0xB8007448"
#define ISO_IRTX_PWM_SETTING_reg                                                     0xB8007448
#define set_ISO_IRTX_PWM_SETTING_reg(data)   (*((volatile unsigned int*) ISO_IRTX_PWM_SETTING_reg)=data)
#define get_ISO_IRTX_PWM_SETTING_reg   (*((volatile unsigned int*) ISO_IRTX_PWM_SETTING_reg))
#define ISO_IRTX_PWM_SETTING_inst_adr                                                "0x0012"
#define ISO_IRTX_PWM_SETTING_inst                                                    0x0012
#define ISO_IRTX_PWM_SETTING_pwm_clksrc_div_shift                                    (16)
#define ISO_IRTX_PWM_SETTING_pwm_clksrc_div_mask                                     (0x000F0000)
#define ISO_IRTX_PWM_SETTING_pwm_clksrc_div(data)                                    (0x000F0000&((data)<<16))
#define ISO_IRTX_PWM_SETTING_pwm_clksrc_div_src(data)                                ((0x000F0000&(data))>>16)
#define ISO_IRTX_PWM_SETTING_get_pwm_clksrc_div(data)                                ((0x000F0000&(data))>>16)
#define ISO_IRTX_PWM_SETTING_pwm_clk_duty_shift                                      (8)
#define ISO_IRTX_PWM_SETTING_pwm_clk_duty_mask                                       (0x0000FF00)
#define ISO_IRTX_PWM_SETTING_pwm_clk_duty(data)                                      (0x0000FF00&((data)<<8))
#define ISO_IRTX_PWM_SETTING_pwm_clk_duty_src(data)                                  ((0x0000FF00&(data))>>8)
#define ISO_IRTX_PWM_SETTING_get_pwm_clk_duty(data)                                  ((0x0000FF00&(data))>>8)
#define ISO_IRTX_PWM_SETTING_pwm_clk_div_shift                                       (0)
#define ISO_IRTX_PWM_SETTING_pwm_clk_div_mask                                        (0x000000FF)
#define ISO_IRTX_PWM_SETTING_pwm_clk_div(data)                                       (0x000000FF&((data)<<0))
#define ISO_IRTX_PWM_SETTING_pwm_clk_div_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_IRTX_PWM_SETTING_get_pwm_clk_div(data)                                   ((0x000000FF&(data))>>0)


#define ISO_IRTX_INT_EN                                                              0x1800744C
#define ISO_IRTX_INT_EN_reg_addr                                                     "0xB800744C"
#define ISO_IRTX_INT_EN_reg                                                          0xB800744C
#define set_ISO_IRTX_INT_EN_reg(data)   (*((volatile unsigned int*) ISO_IRTX_INT_EN_reg)=data)
#define get_ISO_IRTX_INT_EN_reg   (*((volatile unsigned int*) ISO_IRTX_INT_EN_reg))
#define ISO_IRTX_INT_EN_inst_adr                                                     "0x0013"
#define ISO_IRTX_INT_EN_inst                                                         0x0013
#define ISO_IRTX_INT_EN_data_thr_shift                                               (8)
#define ISO_IRTX_INT_EN_data_thr_mask                                                (0x00003F00)
#define ISO_IRTX_INT_EN_data_thr(data)                                               (0x00003F00&((data)<<8))
#define ISO_IRTX_INT_EN_data_thr_src(data)                                           ((0x00003F00&(data))>>8)
#define ISO_IRTX_INT_EN_get_data_thr(data)                                           ((0x00003F00&(data))>>8)
#define ISO_IRTX_INT_EN_fin_en_shift                                                 (2)
#define ISO_IRTX_INT_EN_fin_en_mask                                                  (0x00000004)
#define ISO_IRTX_INT_EN_fin_en(data)                                                 (0x00000004&((data)<<2))
#define ISO_IRTX_INT_EN_fin_en_src(data)                                             ((0x00000004&(data))>>2)
#define ISO_IRTX_INT_EN_get_fin_en(data)                                             ((0x00000004&(data))>>2)
#define ISO_IRTX_INT_EN_emp_en_shift                                                 (1)
#define ISO_IRTX_INT_EN_emp_en_mask                                                  (0x00000002)
#define ISO_IRTX_INT_EN_emp_en(data)                                                 (0x00000002&((data)<<1))
#define ISO_IRTX_INT_EN_emp_en_src(data)                                             ((0x00000002&(data))>>1)
#define ISO_IRTX_INT_EN_get_emp_en(data)                                             ((0x00000002&(data))>>1)
#define ISO_IRTX_INT_EN_req_en_shift                                                 (0)
#define ISO_IRTX_INT_EN_req_en_mask                                                  (0x00000001)
#define ISO_IRTX_INT_EN_req_en(data)                                                 (0x00000001&((data)<<0))
#define ISO_IRTX_INT_EN_req_en_src(data)                                             ((0x00000001&(data))>>0)
#define ISO_IRTX_INT_EN_get_req_en(data)                                             ((0x00000001&(data))>>0)


#define ISO_IRTX_INT_ST                                                              0x18007450
#define ISO_IRTX_INT_ST_reg_addr                                                     "0xB8007450"
#define ISO_IRTX_INT_ST_reg                                                          0xB8007450
#define set_ISO_IRTX_INT_ST_reg(data)   (*((volatile unsigned int*) ISO_IRTX_INT_ST_reg)=data)
#define get_ISO_IRTX_INT_ST_reg   (*((volatile unsigned int*) ISO_IRTX_INT_ST_reg))
#define ISO_IRTX_INT_ST_inst_adr                                                     "0x0014"
#define ISO_IRTX_INT_ST_inst                                                         0x0014
#define ISO_IRTX_INT_ST_fin_flag_shift                                               (2)
#define ISO_IRTX_INT_ST_fin_flag_mask                                                (0x00000004)
#define ISO_IRTX_INT_ST_fin_flag(data)                                               (0x00000004&((data)<<2))
#define ISO_IRTX_INT_ST_fin_flag_src(data)                                           ((0x00000004&(data))>>2)
#define ISO_IRTX_INT_ST_get_fin_flag(data)                                           ((0x00000004&(data))>>2)
#define ISO_IRTX_INT_ST_emp_flag_shift                                               (1)
#define ISO_IRTX_INT_ST_emp_flag_mask                                                (0x00000002)
#define ISO_IRTX_INT_ST_emp_flag(data)                                               (0x00000002&((data)<<1))
#define ISO_IRTX_INT_ST_emp_flag_src(data)                                           ((0x00000002&(data))>>1)
#define ISO_IRTX_INT_ST_get_emp_flag(data)                                           ((0x00000002&(data))>>1)
#define ISO_IRTX_INT_ST_req_flag_shift                                               (0)
#define ISO_IRTX_INT_ST_req_flag_mask                                                (0x00000001)
#define ISO_IRTX_INT_ST_req_flag(data)                                               (0x00000001&((data)<<0))
#define ISO_IRTX_INT_ST_req_flag_src(data)                                           ((0x00000001&(data))>>0)
#define ISO_IRTX_INT_ST_get_req_flag(data)                                           ((0x00000001&(data))>>0)


#define ISO_IRTX_FIFO_ST                                                             0x18007454
#define ISO_IRTX_FIFO_ST_reg_addr                                                    "0xB8007454"
#define ISO_IRTX_FIFO_ST_reg                                                         0xB8007454
#define set_ISO_IRTX_FIFO_ST_reg(data)   (*((volatile unsigned int*) ISO_IRTX_FIFO_ST_reg)=data)
#define get_ISO_IRTX_FIFO_ST_reg   (*((volatile unsigned int*) ISO_IRTX_FIFO_ST_reg))
#define ISO_IRTX_FIFO_ST_inst_adr                                                    "0x0015"
#define ISO_IRTX_FIFO_ST_inst                                                        0x0015
#define ISO_IRTX_FIFO_ST_fifo_rst_shift                                              (31)
#define ISO_IRTX_FIFO_ST_fifo_rst_mask                                               (0x80000000)
#define ISO_IRTX_FIFO_ST_fifo_rst(data)                                              (0x80000000&((data)<<31))
#define ISO_IRTX_FIFO_ST_fifo_rst_src(data)                                          ((0x80000000&(data))>>31)
#define ISO_IRTX_FIFO_ST_get_fifo_rst(data)                                          ((0x80000000&(data))>>31)
#define ISO_IRTX_FIFO_ST_valid_len_shift                                             (8)
#define ISO_IRTX_FIFO_ST_valid_len_mask                                              (0x00000F00)
#define ISO_IRTX_FIFO_ST_valid_len(data)                                             (0x00000F00&((data)<<8))
#define ISO_IRTX_FIFO_ST_valid_len_src(data)                                         ((0x00000F00&(data))>>8)
#define ISO_IRTX_FIFO_ST_get_valid_len(data)                                         ((0x00000F00&(data))>>8)
#define ISO_IRTX_FIFO_ST_wrp_shift                                                   (4)
#define ISO_IRTX_FIFO_ST_wrp_mask                                                    (0x000000F0)
#define ISO_IRTX_FIFO_ST_wrp(data)                                                   (0x000000F0&((data)<<4))
#define ISO_IRTX_FIFO_ST_wrp_src(data)                                               ((0x000000F0&(data))>>4)
#define ISO_IRTX_FIFO_ST_get_wrp(data)                                               ((0x000000F0&(data))>>4)
#define ISO_IRTX_FIFO_ST_rdp_shift                                                   (0)
#define ISO_IRTX_FIFO_ST_rdp_mask                                                    (0x0000000F)
#define ISO_IRTX_FIFO_ST_rdp(data)                                                   (0x0000000F&((data)<<0))
#define ISO_IRTX_FIFO_ST_rdp_src(data)                                               ((0x0000000F&(data))>>0)
#define ISO_IRTX_FIFO_ST_get_rdp(data)                                               ((0x0000000F&(data))>>0)


#define ISO_IRTX_FIFO                                                                0x18007458
#define ISO_IRTX_FIFO_reg_addr                                                       "0xB8007458"
#define ISO_IRTX_FIFO_reg                                                            0xB8007458
#define set_ISO_IRTX_FIFO_reg(data)   (*((volatile unsigned int*) ISO_IRTX_FIFO_reg)=data)
#define get_ISO_IRTX_FIFO_reg   (*((volatile unsigned int*) ISO_IRTX_FIFO_reg))
#define ISO_IRTX_FIFO_inst_adr                                                       "0x0016"
#define ISO_IRTX_FIFO_inst                                                           0x0016
#define ISO_IRTX_FIFO_data_shift                                                     (0)
#define ISO_IRTX_FIFO_data_mask                                                      (0xFFFFFFFF)
#define ISO_IRTX_FIFO_data(data)                                                     (0xFFFFFFFF&((data)<<0))
#define ISO_IRTX_FIFO_data_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define ISO_IRTX_FIFO_get_data(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define ISO_IRRCMM_TIMING                                                            0x18007460
#define ISO_IRRCMM_TIMING_reg_addr                                                   "0xB8007460"
#define ISO_IRRCMM_TIMING_reg                                                        0xB8007460
#define set_ISO_IRRCMM_TIMING_reg(data)   (*((volatile unsigned int*) ISO_IRRCMM_TIMING_reg)=data)
#define get_ISO_IRRCMM_TIMING_reg   (*((volatile unsigned int*) ISO_IRRCMM_TIMING_reg))
#define ISO_IRRCMM_TIMING_inst_adr                                                   "0x0018"
#define ISO_IRRCMM_TIMING_inst                                                       0x0018
#define ISO_IRRCMM_TIMING_len_11_shift                                               (24)
#define ISO_IRRCMM_TIMING_len_11_mask                                                (0xFF000000)
#define ISO_IRRCMM_TIMING_len_11(data)                                               (0xFF000000&((data)<<24))
#define ISO_IRRCMM_TIMING_len_11_src(data)                                           ((0xFF000000&(data))>>24)
#define ISO_IRRCMM_TIMING_get_len_11(data)                                           ((0xFF000000&(data))>>24)
#define ISO_IRRCMM_TIMING_len_10_shift                                               (16)
#define ISO_IRRCMM_TIMING_len_10_mask                                                (0x00FF0000)
#define ISO_IRRCMM_TIMING_len_10(data)                                               (0x00FF0000&((data)<<16))
#define ISO_IRRCMM_TIMING_len_10_src(data)                                           ((0x00FF0000&(data))>>16)
#define ISO_IRRCMM_TIMING_get_len_10(data)                                           ((0x00FF0000&(data))>>16)
#define ISO_IRRCMM_TIMING_len_01_shift                                               (8)
#define ISO_IRRCMM_TIMING_len_01_mask                                                (0x0000FF00)
#define ISO_IRRCMM_TIMING_len_01(data)                                               (0x0000FF00&((data)<<8))
#define ISO_IRRCMM_TIMING_len_01_src(data)                                           ((0x0000FF00&(data))>>8)
#define ISO_IRRCMM_TIMING_get_len_01(data)                                           ((0x0000FF00&(data))>>8)
#define ISO_IRRCMM_TIMING_len_00_shift                                               (0)
#define ISO_IRRCMM_TIMING_len_00_mask                                                (0x000000FF)
#define ISO_IRRCMM_TIMING_len_00(data)                                               (0x000000FF&((data)<<0))
#define ISO_IRRCMM_TIMING_len_00_src(data)                                           ((0x000000FF&(data))>>0)
#define ISO_IRRCMM_TIMING_get_len_00(data)                                           ((0x000000FF&(data))>>0)


#define ISO_IR_CR1                                                                   0x18007464
#define ISO_IR_CR1_reg_addr                                                          "0xB8007464"
#define ISO_IR_CR1_reg                                                               0xB8007464
#define set_ISO_IR_CR1_reg(data)   (*((volatile unsigned int*) ISO_IR_CR1_reg)=data)
#define get_ISO_IR_CR1_reg   (*((volatile unsigned int*) ISO_IR_CR1_reg))
#define ISO_IR_CR1_inst_adr                                                          "0x0019"
#define ISO_IR_CR1_inst                                                              0x0019
#define ISO_IR_CR1_dec_by_min_max_shift                                              (0)
#define ISO_IR_CR1_dec_by_min_max_mask                                               (0x00000001)
#define ISO_IR_CR1_dec_by_min_max(data)                                              (0x00000001&((data)<<0))
#define ISO_IR_CR1_dec_by_min_max_src(data)                                          ((0x00000001&(data))>>0)
#define ISO_IR_CR1_get_dec_by_min_max(data)                                          ((0x00000001&(data))>>0)


#define ISO_IRRCMM_APKB                                                              0x18007468
#define ISO_IRRCMM_APKB_reg_addr                                                     "0xB8007468"
#define ISO_IRRCMM_APKB_reg                                                          0xB8007468
#define set_ISO_IRRCMM_APKB_reg(data)   (*((volatile unsigned int*) ISO_IRRCMM_APKB_reg)=data)
#define get_ISO_IRRCMM_APKB_reg   (*((volatile unsigned int*) ISO_IRRCMM_APKB_reg))
#define ISO_IRRCMM_APKB_inst_adr                                                     "0x001A"
#define ISO_IRRCMM_APKB_inst                                                         0x001A
#define ISO_IRRCMM_APKB_rcmm_ap_max_shift                                            (24)
#define ISO_IRRCMM_APKB_rcmm_ap_max_mask                                             (0xFF000000)
#define ISO_IRRCMM_APKB_rcmm_ap_max(data)                                            (0xFF000000&((data)<<24))
#define ISO_IRRCMM_APKB_rcmm_ap_max_src(data)                                        ((0xFF000000&(data))>>24)
#define ISO_IRRCMM_APKB_get_rcmm_ap_max(data)                                        ((0xFF000000&(data))>>24)
#define ISO_IRRCMM_APKB_rcmm_ap_min_shift                                            (16)
#define ISO_IRRCMM_APKB_rcmm_ap_min_mask                                             (0x00FF0000)
#define ISO_IRRCMM_APKB_rcmm_ap_min(data)                                            (0x00FF0000&((data)<<16))
#define ISO_IRRCMM_APKB_rcmm_ap_min_src(data)                                        ((0x00FF0000&(data))>>16)
#define ISO_IRRCMM_APKB_get_rcmm_ap_min(data)                                        ((0x00FF0000&(data))>>16)
#define ISO_IRRCMM_APKB_rcmm_kb_max_shift                                            (8)
#define ISO_IRRCMM_APKB_rcmm_kb_max_mask                                             (0x0000FF00)
#define ISO_IRRCMM_APKB_rcmm_kb_max(data)                                            (0x0000FF00&((data)<<8))
#define ISO_IRRCMM_APKB_rcmm_kb_max_src(data)                                        ((0x0000FF00&(data))>>8)
#define ISO_IRRCMM_APKB_get_rcmm_kb_max(data)                                        ((0x0000FF00&(data))>>8)
#define ISO_IRRCMM_APKB_rcmm_kb_min_shift                                            (0)
#define ISO_IRRCMM_APKB_rcmm_kb_min_mask                                             (0x000000FF)
#define ISO_IRRCMM_APKB_rcmm_kb_min(data)                                            (0x000000FF&((data)<<0))
#define ISO_IRRCMM_APKB_rcmm_kb_min_src(data)                                        ((0x000000FF&(data))>>0)
#define ISO_IRRCMM_APKB_get_rcmm_kb_min(data)                                        ((0x000000FF&(data))>>0)


#define ISO_IRRXRCLFIFO                                                              0x1800746C
#define ISO_IRRXRCLFIFO_reg_addr                                                     "0xB800746C"
#define ISO_IRRXRCLFIFO_reg                                                          0xB800746C
#define set_ISO_IRRXRCLFIFO_reg(data)   (*((volatile unsigned int*) ISO_IRRXRCLFIFO_reg)=data)
#define get_ISO_IRRXRCLFIFO_reg   (*((volatile unsigned int*) ISO_IRRXRCLFIFO_reg))
#define ISO_IRRXRCLFIFO_inst_adr                                                     "0x001B"
#define ISO_IRRXRCLFIFO_inst                                                         0x001B
#define ISO_IRRXRCLFIFO_rcmm_apoint_shift                                            (31)
#define ISO_IRRXRCLFIFO_rcmm_apoint_mask                                             (0x80000000)
#define ISO_IRRXRCLFIFO_rcmm_apoint(data)                                            (0x80000000&((data)<<31))
#define ISO_IRRXRCLFIFO_rcmm_apoint_src(data)                                        ((0x80000000&(data))>>31)
#define ISO_IRRXRCLFIFO_get_rcmm_apoint(data)                                        ((0x80000000&(data))>>31)
#define ISO_IRRXRCLFIFO_rcmm_kboard_shift                                            (30)
#define ISO_IRRXRCLFIFO_rcmm_kboard_mask                                             (0x40000000)
#define ISO_IRRXRCLFIFO_rcmm_kboard(data)                                            (0x40000000&((data)<<30))
#define ISO_IRRXRCLFIFO_rcmm_kboard_src(data)                                        ((0x40000000&(data))>>30)
#define ISO_IRRXRCLFIFO_get_rcmm_kboard(data)                                        ((0x40000000&(data))>>30)
#define ISO_IRRXRCLFIFO_remote_cnt_lead_high_shift                                   (16)
#define ISO_IRRXRCLFIFO_remote_cnt_lead_high_mask                                    (0x3FFF0000)
#define ISO_IRRXRCLFIFO_remote_cnt_lead_high(data)                                   (0x3FFF0000&((data)<<16))
#define ISO_IRRXRCLFIFO_remote_cnt_lead_high_src(data)                               ((0x3FFF0000&(data))>>16)
#define ISO_IRRXRCLFIFO_get_remote_cnt_lead_high(data)                               ((0x3FFF0000&(data))>>16)
#define ISO_IRRXRCLFIFO_remote_cnt_lead_low_shift                                    (0)
#define ISO_IRRXRCLFIFO_remote_cnt_lead_low_mask                                     (0x0000FFFF)
#define ISO_IRRXRCLFIFO_remote_cnt_lead_low(data)                                    (0x0000FFFF&((data)<<0))
#define ISO_IRRXRCLFIFO_remote_cnt_lead_low_src(data)                                ((0x0000FFFF&(data))>>0)
#define ISO_IRRXRCLFIFO_get_remote_cnt_lead_low(data)                                ((0x0000FFFF&(data))>>0)


#define ISO_CEC_CR0                                                                  0x18007500
#define ISO_CEC_CR0_reg_addr                                                         "0xB8007500"
#define ISO_CEC_CR0_reg                                                              0xB8007500
#define set_ISO_CEC_CR0_reg(data)   (*((volatile unsigned int*) ISO_CEC_CR0_reg)=data)
#define get_ISO_CEC_CR0_reg   (*((volatile unsigned int*) ISO_CEC_CR0_reg))
#define ISO_CEC_CR0_inst_adr                                                         "0x0040"
#define ISO_CEC_CR0_inst                                                             0x0040
#define ISO_CEC_CR0_cec_mode_shift                                                   (30)
#define ISO_CEC_CR0_cec_mode_mask                                                    (0xC0000000)
#define ISO_CEC_CR0_cec_mode(data)                                                   (0xC0000000&((data)<<30))
#define ISO_CEC_CR0_cec_mode_src(data)                                               ((0xC0000000&(data))>>30)
#define ISO_CEC_CR0_get_cec_mode(data)                                               ((0xC0000000&(data))>>30)
#define ISO_CEC_CR0_test_mode_pad_en_shift                                           (28)
#define ISO_CEC_CR0_test_mode_pad_en_mask                                            (0x10000000)
#define ISO_CEC_CR0_test_mode_pad_en(data)                                           (0x10000000&((data)<<28))
#define ISO_CEC_CR0_test_mode_pad_en_src(data)                                       ((0x10000000&(data))>>28)
#define ISO_CEC_CR0_get_test_mode_pad_en(data)                                       ((0x10000000&(data))>>28)
#define ISO_CEC_CR0_logical_addr0_shift                                              (24)
#define ISO_CEC_CR0_logical_addr0_mask                                               (0x0F000000)
#define ISO_CEC_CR0_logical_addr0(data)                                              (0x0F000000&((data)<<24))
#define ISO_CEC_CR0_logical_addr0_src(data)                                          ((0x0F000000&(data))>>24)
#define ISO_CEC_CR0_get_logical_addr0(data)                                          ((0x0F000000&(data))>>24)
#define ISO_CEC_CR0_timer_div_shift                                                  (16)
#define ISO_CEC_CR0_timer_div_mask                                                   (0x00FF0000)
#define ISO_CEC_CR0_timer_div(data)                                                  (0x00FF0000&((data)<<16))
#define ISO_CEC_CR0_timer_div_src(data)                                              ((0x00FF0000&(data))>>16)
#define ISO_CEC_CR0_get_timer_div(data)                                              ((0x00FF0000&(data))>>16)
#define ISO_CEC_CR0_pre_div_shift                                                    (8)
#define ISO_CEC_CR0_pre_div_mask                                                     (0x0000FF00)
#define ISO_CEC_CR0_pre_div(data)                                                    (0x0000FF00&((data)<<8))
#define ISO_CEC_CR0_pre_div_src(data)                                                ((0x0000FF00&(data))>>8)
#define ISO_CEC_CR0_get_pre_div(data)                                                ((0x0000FF00&(data))>>8)
#define ISO_CEC_CR0_unreg_ack_en_shift                                               (7)
#define ISO_CEC_CR0_unreg_ack_en_mask                                                (0x00000080)
#define ISO_CEC_CR0_unreg_ack_en(data)                                               (0x00000080&((data)<<7))
#define ISO_CEC_CR0_unreg_ack_en_src(data)                                           ((0x00000080&(data))>>7)
#define ISO_CEC_CR0_get_unreg_ack_en(data)                                           ((0x00000080&(data))>>7)
#define ISO_CEC_CR0_cdc_arbitration_en_shift                                         (5)
#define ISO_CEC_CR0_cdc_arbitration_en_mask                                          (0x00000020)
#define ISO_CEC_CR0_cdc_arbitration_en(data)                                         (0x00000020&((data)<<5))
#define ISO_CEC_CR0_cdc_arbitration_en_src(data)                                     ((0x00000020&(data))>>5)
#define ISO_CEC_CR0_get_cdc_arbitration_en(data)                                     ((0x00000020&(data))>>5)
#define ISO_CEC_CR0_test_mode_pad_data_shift                                         (0)
#define ISO_CEC_CR0_test_mode_pad_data_mask                                          (0x0000001F)
#define ISO_CEC_CR0_test_mode_pad_data(data)                                         (0x0000001F&((data)<<0))
#define ISO_CEC_CR0_test_mode_pad_data_src(data)                                     ((0x0000001F&(data))>>0)
#define ISO_CEC_CR0_get_test_mode_pad_data(data)                                     ((0x0000001F&(data))>>0)


#define ISO_CEC_RTCR0                                                                0x18007504
#define ISO_CEC_RTCR0_reg_addr                                                       "0xB8007504"
#define ISO_CEC_RTCR0_reg                                                            0xB8007504
#define set_ISO_CEC_RTCR0_reg(data)   (*((volatile unsigned int*) ISO_CEC_RTCR0_reg)=data)
#define get_ISO_CEC_RTCR0_reg   (*((volatile unsigned int*) ISO_CEC_RTCR0_reg))
#define ISO_CEC_RTCR0_inst_adr                                                       "0x0041"
#define ISO_CEC_RTCR0_inst                                                           0x0041
#define ISO_CEC_RTCR0_cec_pad_in_shift                                               (31)
#define ISO_CEC_RTCR0_cec_pad_in_mask                                                (0x80000000)
#define ISO_CEC_RTCR0_cec_pad_in(data)                                               (0x80000000&((data)<<31))
#define ISO_CEC_RTCR0_cec_pad_in_src(data)                                           ((0x80000000&(data))>>31)
#define ISO_CEC_RTCR0_get_cec_pad_in(data)                                           ((0x80000000&(data))>>31)
#define ISO_CEC_RTCR0_dummy0_shift                                                   (28)
#define ISO_CEC_RTCR0_dummy0_mask                                                    (0x70000000)
#define ISO_CEC_RTCR0_dummy0(data)                                                   (0x70000000&((data)<<28))
#define ISO_CEC_RTCR0_dummy0_src(data)                                               ((0x70000000&(data))>>28)
#define ISO_CEC_RTCR0_get_dummy0(data)                                               ((0x70000000&(data))>>28)
#define ISO_CEC_RTCR0_logical_addr3_shift                                            (24)
#define ISO_CEC_RTCR0_logical_addr3_mask                                             (0x0F000000)
#define ISO_CEC_RTCR0_logical_addr3(data)                                            (0x0F000000&((data)<<24))
#define ISO_CEC_RTCR0_logical_addr3_src(data)                                        ((0x0F000000&(data))>>24)
#define ISO_CEC_RTCR0_get_logical_addr3(data)                                        ((0x0F000000&(data))>>24)
#define ISO_CEC_RTCR0_logical_addr2_shift                                            (20)
#define ISO_CEC_RTCR0_logical_addr2_mask                                             (0x00F00000)
#define ISO_CEC_RTCR0_logical_addr2(data)                                            (0x00F00000&((data)<<20))
#define ISO_CEC_RTCR0_logical_addr2_src(data)                                        ((0x00F00000&(data))>>20)
#define ISO_CEC_RTCR0_get_logical_addr2(data)                                        ((0x00F00000&(data))>>20)
#define ISO_CEC_RTCR0_logical_addr1_shift                                            (16)
#define ISO_CEC_RTCR0_logical_addr1_mask                                             (0x000F0000)
#define ISO_CEC_RTCR0_logical_addr1(data)                                            (0x000F0000&((data)<<16))
#define ISO_CEC_RTCR0_logical_addr1_src(data)                                        ((0x000F0000&(data))>>16)
#define ISO_CEC_RTCR0_get_logical_addr1(data)                                        ((0x000F0000&(data))>>16)
#define ISO_CEC_RTCR0_dummy1_shift                                                   (12)
#define ISO_CEC_RTCR0_dummy1_mask                                                    (0x0000F000)
#define ISO_CEC_RTCR0_dummy1(data)                                                   (0x0000F000&((data)<<12))
#define ISO_CEC_RTCR0_dummy1_src(data)                                               ((0x0000F000&(data))>>12)
#define ISO_CEC_RTCR0_get_dummy1(data)                                               ((0x0000F000&(data))>>12)
#define ISO_CEC_RTCR0_clear_cec_int_shift                                            (11)
#define ISO_CEC_RTCR0_clear_cec_int_mask                                             (0x00000800)
#define ISO_CEC_RTCR0_clear_cec_int(data)                                            (0x00000800&((data)<<11))
#define ISO_CEC_RTCR0_clear_cec_int_src(data)                                        ((0x00000800&(data))>>11)
#define ISO_CEC_RTCR0_get_clear_cec_int(data)                                        ((0x00000800&(data))>>11)
#define ISO_CEC_RTCR0_wt_cnt_shift                                                   (5)
#define ISO_CEC_RTCR0_wt_cnt_mask                                                    (0x000007E0)
#define ISO_CEC_RTCR0_wt_cnt(data)                                                   (0x000007E0&((data)<<5))
#define ISO_CEC_RTCR0_wt_cnt_src(data)                                               ((0x000007E0&(data))>>5)
#define ISO_CEC_RTCR0_get_wt_cnt(data)                                               ((0x000007E0&(data))>>5)
#define ISO_CEC_RTCR0_lattest_shift                                                  (4)
#define ISO_CEC_RTCR0_lattest_mask                                                   (0x00000010)
#define ISO_CEC_RTCR0_lattest(data)                                                  (0x00000010&((data)<<4))
#define ISO_CEC_RTCR0_lattest_src(data)                                              ((0x00000010&(data))>>4)
#define ISO_CEC_RTCR0_get_lattest(data)                                              ((0x00000010&(data))>>4)
#define ISO_CEC_RTCR0_retry_no_shift                                                 (0)
#define ISO_CEC_RTCR0_retry_no_mask                                                  (0x0000000F)
#define ISO_CEC_RTCR0_retry_no(data)                                                 (0x0000000F&((data)<<0))
#define ISO_CEC_RTCR0_retry_no_src(data)                                             ((0x0000000F&(data))>>0)
#define ISO_CEC_RTCR0_get_retry_no(data)                                             ((0x0000000F&(data))>>0)


#define ISO_CEC_RXCR0                                                                0x18007508
#define ISO_CEC_RXCR0_reg_addr                                                       "0xB8007508"
#define ISO_CEC_RXCR0_reg                                                            0xB8007508
#define set_ISO_CEC_RXCR0_reg(data)   (*((volatile unsigned int*) ISO_CEC_RXCR0_reg)=data)
#define get_ISO_CEC_RXCR0_reg   (*((volatile unsigned int*) ISO_CEC_RXCR0_reg))
#define ISO_CEC_RXCR0_inst_adr                                                       "0x0042"
#define ISO_CEC_RXCR0_inst                                                           0x0042
#define ISO_CEC_RXCR0_broadcast_addr_shift                                           (31)
#define ISO_CEC_RXCR0_broadcast_addr_mask                                            (0x80000000)
#define ISO_CEC_RXCR0_broadcast_addr(data)                                           (0x80000000&((data)<<31))
#define ISO_CEC_RXCR0_broadcast_addr_src(data)                                       ((0x80000000&(data))>>31)
#define ISO_CEC_RXCR0_get_broadcast_addr(data)                                       ((0x80000000&(data))>>31)
#define ISO_CEC_RXCR0_dest_addr_shift                                                (16)
#define ISO_CEC_RXCR0_dest_addr_mask                                                 (0x000F0000)
#define ISO_CEC_RXCR0_dest_addr(data)                                                (0x000F0000&((data)<<16))
#define ISO_CEC_RXCR0_dest_addr_src(data)                                            ((0x000F0000&(data))>>16)
#define ISO_CEC_RXCR0_get_dest_addr(data)                                            ((0x000F0000&(data))>>16)
#define ISO_CEC_RXCR0_rx_en_shift                                                    (15)
#define ISO_CEC_RXCR0_rx_en_mask                                                     (0x00008000)
#define ISO_CEC_RXCR0_rx_en(data)                                                    (0x00008000&((data)<<15))
#define ISO_CEC_RXCR0_rx_en_src(data)                                                ((0x00008000&(data))>>15)
#define ISO_CEC_RXCR0_get_rx_en(data)                                                ((0x00008000&(data))>>15)
#define ISO_CEC_RXCR0_rx_rst_shift                                                   (14)
#define ISO_CEC_RXCR0_rx_rst_mask                                                    (0x00004000)
#define ISO_CEC_RXCR0_rx_rst(data)                                                   (0x00004000&((data)<<14))
#define ISO_CEC_RXCR0_rx_rst_src(data)                                               ((0x00004000&(data))>>14)
#define ISO_CEC_RXCR0_get_rx_rst(data)                                               ((0x00004000&(data))>>14)
#define ISO_CEC_RXCR0_rx_continuous_shift                                            (13)
#define ISO_CEC_RXCR0_rx_continuous_mask                                             (0x00002000)
#define ISO_CEC_RXCR0_rx_continuous(data)                                            (0x00002000&((data)<<13))
#define ISO_CEC_RXCR0_rx_continuous_src(data)                                        ((0x00002000&(data))>>13)
#define ISO_CEC_RXCR0_get_rx_continuous(data)                                        ((0x00002000&(data))>>13)
#define ISO_CEC_RXCR0_rx_int_en_shift                                                (12)
#define ISO_CEC_RXCR0_rx_int_en_mask                                                 (0x00001000)
#define ISO_CEC_RXCR0_rx_int_en(data)                                                (0x00001000&((data)<<12))
#define ISO_CEC_RXCR0_rx_int_en_src(data)                                            ((0x00001000&(data))>>12)
#define ISO_CEC_RXCR0_get_rx_int_en(data)                                            ((0x00001000&(data))>>12)
#define ISO_CEC_RXCR0_init_addr_shift                                                (8)
#define ISO_CEC_RXCR0_init_addr_mask                                                 (0x00000F00)
#define ISO_CEC_RXCR0_init_addr(data)                                                (0x00000F00&((data)<<8))
#define ISO_CEC_RXCR0_init_addr_src(data)                                            ((0x00000F00&(data))>>8)
#define ISO_CEC_RXCR0_get_init_addr(data)                                            ((0x00000F00&(data))>>8)
#define ISO_CEC_RXCR0_rx_eom_shift                                                   (7)
#define ISO_CEC_RXCR0_rx_eom_mask                                                    (0x00000080)
#define ISO_CEC_RXCR0_rx_eom(data)                                                   (0x00000080&((data)<<7))
#define ISO_CEC_RXCR0_rx_eom_src(data)                                               ((0x00000080&(data))>>7)
#define ISO_CEC_RXCR0_get_rx_eom(data)                                               ((0x00000080&(data))>>7)
#define ISO_CEC_RXCR0_rx_int_shift                                                   (6)
#define ISO_CEC_RXCR0_rx_int_mask                                                    (0x00000040)
#define ISO_CEC_RXCR0_rx_int(data)                                                   (0x00000040&((data)<<6))
#define ISO_CEC_RXCR0_rx_int_src(data)                                               ((0x00000040&(data))>>6)
#define ISO_CEC_RXCR0_get_rx_int(data)                                               ((0x00000040&(data))>>6)
#define ISO_CEC_RXCR0_rx_fifo_ov_shift                                               (5)
#define ISO_CEC_RXCR0_rx_fifo_ov_mask                                                (0x00000020)
#define ISO_CEC_RXCR0_rx_fifo_ov(data)                                               (0x00000020&((data)<<5))
#define ISO_CEC_RXCR0_rx_fifo_ov_src(data)                                           ((0x00000020&(data))>>5)
#define ISO_CEC_RXCR0_get_rx_fifo_ov(data)                                           ((0x00000020&(data))>>5)
#define ISO_CEC_RXCR0_rx_fifo_cnt_shift                                              (0)
#define ISO_CEC_RXCR0_rx_fifo_cnt_mask                                               (0x0000001F)
#define ISO_CEC_RXCR0_rx_fifo_cnt(data)                                              (0x0000001F&((data)<<0))
#define ISO_CEC_RXCR0_rx_fifo_cnt_src(data)                                          ((0x0000001F&(data))>>0)
#define ISO_CEC_RXCR0_get_rx_fifo_cnt(data)                                          ((0x0000001F&(data))>>0)


#define ISO_CEC_TXCR0                                                                0x1800750C
#define ISO_CEC_TXCR0_reg_addr                                                       "0xB800750C"
#define ISO_CEC_TXCR0_reg                                                            0xB800750C
#define set_ISO_CEC_TXCR0_reg(data)   (*((volatile unsigned int*) ISO_CEC_TXCR0_reg)=data)
#define get_ISO_CEC_TXCR0_reg   (*((volatile unsigned int*) ISO_CEC_TXCR0_reg))
#define ISO_CEC_TXCR0_inst_adr                                                       "0x0043"
#define ISO_CEC_TXCR0_inst                                                           0x0043
#define ISO_CEC_TXCR0_tx_addr_en_shift                                               (20)
#define ISO_CEC_TXCR0_tx_addr_en_mask                                                (0x00100000)
#define ISO_CEC_TXCR0_tx_addr_en(data)                                               (0x00100000&((data)<<20))
#define ISO_CEC_TXCR0_tx_addr_en_src(data)                                           ((0x00100000&(data))>>20)
#define ISO_CEC_TXCR0_get_tx_addr_en(data)                                           ((0x00100000&(data))>>20)
#define ISO_CEC_TXCR0_tx_addr_shift                                                  (16)
#define ISO_CEC_TXCR0_tx_addr_mask                                                   (0x000F0000)
#define ISO_CEC_TXCR0_tx_addr(data)                                                  (0x000F0000&((data)<<16))
#define ISO_CEC_TXCR0_tx_addr_src(data)                                              ((0x000F0000&(data))>>16)
#define ISO_CEC_TXCR0_get_tx_addr(data)                                              ((0x000F0000&(data))>>16)
#define ISO_CEC_TXCR0_tx_en_shift                                                    (15)
#define ISO_CEC_TXCR0_tx_en_mask                                                     (0x00008000)
#define ISO_CEC_TXCR0_tx_en(data)                                                    (0x00008000&((data)<<15))
#define ISO_CEC_TXCR0_tx_en_src(data)                                                ((0x00008000&(data))>>15)
#define ISO_CEC_TXCR0_get_tx_en(data)                                                ((0x00008000&(data))>>15)
#define ISO_CEC_TXCR0_tx_rst_shift                                                   (14)
#define ISO_CEC_TXCR0_tx_rst_mask                                                    (0x00004000)
#define ISO_CEC_TXCR0_tx_rst(data)                                                   (0x00004000&((data)<<14))
#define ISO_CEC_TXCR0_tx_rst_src(data)                                               ((0x00004000&(data))>>14)
#define ISO_CEC_TXCR0_get_tx_rst(data)                                               ((0x00004000&(data))>>14)
#define ISO_CEC_TXCR0_tx_continuous_shift                                            (13)
#define ISO_CEC_TXCR0_tx_continuous_mask                                             (0x00002000)
#define ISO_CEC_TXCR0_tx_continuous(data)                                            (0x00002000&((data)<<13))
#define ISO_CEC_TXCR0_tx_continuous_src(data)                                        ((0x00002000&(data))>>13)
#define ISO_CEC_TXCR0_get_tx_continuous(data)                                        ((0x00002000&(data))>>13)
#define ISO_CEC_TXCR0_tx_int_en_shift                                                (12)
#define ISO_CEC_TXCR0_tx_int_en_mask                                                 (0x00001000)
#define ISO_CEC_TXCR0_tx_int_en(data)                                                (0x00001000&((data)<<12))
#define ISO_CEC_TXCR0_tx_int_en_src(data)                                            ((0x00001000&(data))>>12)
#define ISO_CEC_TXCR0_get_tx_int_en(data)                                            ((0x00001000&(data))>>12)
#define ISO_CEC_TXCR0_dest_addr_shift                                                (8)
#define ISO_CEC_TXCR0_dest_addr_mask                                                 (0x00000F00)
#define ISO_CEC_TXCR0_dest_addr(data)                                                (0x00000F00&((data)<<8))
#define ISO_CEC_TXCR0_dest_addr_src(data)                                            ((0x00000F00&(data))>>8)
#define ISO_CEC_TXCR0_get_dest_addr(data)                                            ((0x00000F00&(data))>>8)
#define ISO_CEC_TXCR0_tx_eom_shift                                                   (7)
#define ISO_CEC_TXCR0_tx_eom_mask                                                    (0x00000080)
#define ISO_CEC_TXCR0_tx_eom(data)                                                   (0x00000080&((data)<<7))
#define ISO_CEC_TXCR0_tx_eom_src(data)                                               ((0x00000080&(data))>>7)
#define ISO_CEC_TXCR0_get_tx_eom(data)                                               ((0x00000080&(data))>>7)
#define ISO_CEC_TXCR0_tx_int_shift                                                   (6)
#define ISO_CEC_TXCR0_tx_int_mask                                                    (0x00000040)
#define ISO_CEC_TXCR0_tx_int(data)                                                   (0x00000040&((data)<<6))
#define ISO_CEC_TXCR0_tx_int_src(data)                                               ((0x00000040&(data))>>6)
#define ISO_CEC_TXCR0_get_tx_int(data)                                               ((0x00000040&(data))>>6)
#define ISO_CEC_TXCR0_tx_fifo_ud_shift                                               (5)
#define ISO_CEC_TXCR0_tx_fifo_ud_mask                                                (0x00000020)
#define ISO_CEC_TXCR0_tx_fifo_ud(data)                                               (0x00000020&((data)<<5))
#define ISO_CEC_TXCR0_tx_fifo_ud_src(data)                                           ((0x00000020&(data))>>5)
#define ISO_CEC_TXCR0_get_tx_fifo_ud(data)                                           ((0x00000020&(data))>>5)
#define ISO_CEC_TXCR0_tx_fifo_cnt_shift                                              (0)
#define ISO_CEC_TXCR0_tx_fifo_cnt_mask                                               (0x0000001F)
#define ISO_CEC_TXCR0_tx_fifo_cnt(data)                                              (0x0000001F&((data)<<0))
#define ISO_CEC_TXCR0_tx_fifo_cnt_src(data)                                          ((0x0000001F&(data))>>0)
#define ISO_CEC_TXCR0_get_tx_fifo_cnt(data)                                          ((0x0000001F&(data))>>0)


#define ISO_CEC_TXDR0                                                                0x18007510
#define ISO_CEC_TXDR0_reg_addr                                                       "0xB8007510"
#define ISO_CEC_TXDR0_reg                                                            0xB8007510
#define set_ISO_CEC_TXDR0_reg(data)   (*((volatile unsigned int*) ISO_CEC_TXDR0_reg)=data)
#define get_ISO_CEC_TXDR0_reg   (*((volatile unsigned int*) ISO_CEC_TXDR0_reg))
#define ISO_CEC_TXDR0_inst_adr                                                       "0x0044"
#define ISO_CEC_TXDR0_inst                                                           0x0044
#define ISO_CEC_TXDR0_tx_add_cnt_shift                                               (6)
#define ISO_CEC_TXDR0_tx_add_cnt_mask                                                (0x00000040)
#define ISO_CEC_TXDR0_tx_add_cnt(data)                                               (0x00000040&((data)<<6))
#define ISO_CEC_TXDR0_tx_add_cnt_src(data)                                           ((0x00000040&(data))>>6)
#define ISO_CEC_TXDR0_get_tx_add_cnt(data)                                           ((0x00000040&(data))>>6)
#define ISO_CEC_TXDR0_rx_sub_cnt_shift                                               (5)
#define ISO_CEC_TXDR0_rx_sub_cnt_mask                                                (0x00000020)
#define ISO_CEC_TXDR0_rx_sub_cnt(data)                                               (0x00000020&((data)<<5))
#define ISO_CEC_TXDR0_rx_sub_cnt_src(data)                                           ((0x00000020&(data))>>5)
#define ISO_CEC_TXDR0_get_rx_sub_cnt(data)                                           ((0x00000020&(data))>>5)
#define ISO_CEC_TXDR0_fifo_cnt_shift                                                 (0)
#define ISO_CEC_TXDR0_fifo_cnt_mask                                                  (0x0000001F)
#define ISO_CEC_TXDR0_fifo_cnt(data)                                                 (0x0000001F&((data)<<0))
#define ISO_CEC_TXDR0_fifo_cnt_src(data)                                             ((0x0000001F&(data))>>0)
#define ISO_CEC_TXDR0_get_fifo_cnt(data)                                             ((0x0000001F&(data))>>0)


#define ISO_CEC_TXDR1                                                                0x18007514
#define ISO_CEC_TXDR1_reg_addr                                                       "0xB8007514"
#define ISO_CEC_TXDR1_reg                                                            0xB8007514
#define set_ISO_CEC_TXDR1_reg(data)   (*((volatile unsigned int*) ISO_CEC_TXDR1_reg)=data)
#define get_ISO_CEC_TXDR1_reg   (*((volatile unsigned int*) ISO_CEC_TXDR1_reg))
#define ISO_CEC_TXDR1_inst_adr                                                       "0x0045"
#define ISO_CEC_TXDR1_inst                                                           0x0045
#define ISO_CEC_TXDR1_tx_fifo_0_shift                                                (24)
#define ISO_CEC_TXDR1_tx_fifo_0_mask                                                 (0xFF000000)
#define ISO_CEC_TXDR1_tx_fifo_0(data)                                                (0xFF000000&((data)<<24))
#define ISO_CEC_TXDR1_tx_fifo_0_src(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_TXDR1_get_tx_fifo_0(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_TXDR1_tx_fifo_1_shift                                                (16)
#define ISO_CEC_TXDR1_tx_fifo_1_mask                                                 (0x00FF0000)
#define ISO_CEC_TXDR1_tx_fifo_1(data)                                                (0x00FF0000&((data)<<16))
#define ISO_CEC_TXDR1_tx_fifo_1_src(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXDR1_get_tx_fifo_1(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXDR1_tx_fifo_2_shift                                                (8)
#define ISO_CEC_TXDR1_tx_fifo_2_mask                                                 (0x0000FF00)
#define ISO_CEC_TXDR1_tx_fifo_2(data)                                                (0x0000FF00&((data)<<8))
#define ISO_CEC_TXDR1_tx_fifo_2_src(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXDR1_get_tx_fifo_2(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXDR1_tx_fifo_3_shift                                                (0)
#define ISO_CEC_TXDR1_tx_fifo_3_mask                                                 (0x000000FF)
#define ISO_CEC_TXDR1_tx_fifo_3(data)                                                (0x000000FF&((data)<<0))
#define ISO_CEC_TXDR1_tx_fifo_3_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_CEC_TXDR1_get_tx_fifo_3(data)                                            ((0x000000FF&(data))>>0)


#define ISO_CEC_TXDR2                                                                0x18007518
#define ISO_CEC_TXDR2_reg_addr                                                       "0xB8007518"
#define ISO_CEC_TXDR2_reg                                                            0xB8007518
#define set_ISO_CEC_TXDR2_reg(data)   (*((volatile unsigned int*) ISO_CEC_TXDR2_reg)=data)
#define get_ISO_CEC_TXDR2_reg   (*((volatile unsigned int*) ISO_CEC_TXDR2_reg))
#define ISO_CEC_TXDR2_inst_adr                                                       "0x0046"
#define ISO_CEC_TXDR2_inst                                                           0x0046
#define ISO_CEC_TXDR2_tx_fifo_4_shift                                                (24)
#define ISO_CEC_TXDR2_tx_fifo_4_mask                                                 (0xFF000000)
#define ISO_CEC_TXDR2_tx_fifo_4(data)                                                (0xFF000000&((data)<<24))
#define ISO_CEC_TXDR2_tx_fifo_4_src(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_TXDR2_get_tx_fifo_4(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_TXDR2_tx_fifo_5_shift                                                (16)
#define ISO_CEC_TXDR2_tx_fifo_5_mask                                                 (0x00FF0000)
#define ISO_CEC_TXDR2_tx_fifo_5(data)                                                (0x00FF0000&((data)<<16))
#define ISO_CEC_TXDR2_tx_fifo_5_src(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXDR2_get_tx_fifo_5(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXDR2_tx_fifo_6_shift                                                (8)
#define ISO_CEC_TXDR2_tx_fifo_6_mask                                                 (0x0000FF00)
#define ISO_CEC_TXDR2_tx_fifo_6(data)                                                (0x0000FF00&((data)<<8))
#define ISO_CEC_TXDR2_tx_fifo_6_src(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXDR2_get_tx_fifo_6(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXDR2_tx_fifo_7_shift                                                (0)
#define ISO_CEC_TXDR2_tx_fifo_7_mask                                                 (0x000000FF)
#define ISO_CEC_TXDR2_tx_fifo_7(data)                                                (0x000000FF&((data)<<0))
#define ISO_CEC_TXDR2_tx_fifo_7_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_CEC_TXDR2_get_tx_fifo_7(data)                                            ((0x000000FF&(data))>>0)


#define ISO_CEC_TXDR3                                                                0x1800751C
#define ISO_CEC_TXDR3_reg_addr                                                       "0xB800751C"
#define ISO_CEC_TXDR3_reg                                                            0xB800751C
#define set_ISO_CEC_TXDR3_reg(data)   (*((volatile unsigned int*) ISO_CEC_TXDR3_reg)=data)
#define get_ISO_CEC_TXDR3_reg   (*((volatile unsigned int*) ISO_CEC_TXDR3_reg))
#define ISO_CEC_TXDR3_inst_adr                                                       "0x0047"
#define ISO_CEC_TXDR3_inst                                                           0x0047
#define ISO_CEC_TXDR3_tx_fifo_8_shift                                                (24)
#define ISO_CEC_TXDR3_tx_fifo_8_mask                                                 (0xFF000000)
#define ISO_CEC_TXDR3_tx_fifo_8(data)                                                (0xFF000000&((data)<<24))
#define ISO_CEC_TXDR3_tx_fifo_8_src(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_TXDR3_get_tx_fifo_8(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_TXDR3_tx_fifo_9_shift                                                (16)
#define ISO_CEC_TXDR3_tx_fifo_9_mask                                                 (0x00FF0000)
#define ISO_CEC_TXDR3_tx_fifo_9(data)                                                (0x00FF0000&((data)<<16))
#define ISO_CEC_TXDR3_tx_fifo_9_src(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXDR3_get_tx_fifo_9(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXDR3_tx_fifo_a_shift                                                (8)
#define ISO_CEC_TXDR3_tx_fifo_a_mask                                                 (0x0000FF00)
#define ISO_CEC_TXDR3_tx_fifo_a(data)                                                (0x0000FF00&((data)<<8))
#define ISO_CEC_TXDR3_tx_fifo_a_src(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXDR3_get_tx_fifo_a(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXDR3_tx_fifo_b_shift                                                (0)
#define ISO_CEC_TXDR3_tx_fifo_b_mask                                                 (0x000000FF)
#define ISO_CEC_TXDR3_tx_fifo_b(data)                                                (0x000000FF&((data)<<0))
#define ISO_CEC_TXDR3_tx_fifo_b_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_CEC_TXDR3_get_tx_fifo_b(data)                                            ((0x000000FF&(data))>>0)


#define ISO_CEC_TXDR4                                                                0x18007520
#define ISO_CEC_TXDR4_reg_addr                                                       "0xB8007520"
#define ISO_CEC_TXDR4_reg                                                            0xB8007520
#define set_ISO_CEC_TXDR4_reg(data)   (*((volatile unsigned int*) ISO_CEC_TXDR4_reg)=data)
#define get_ISO_CEC_TXDR4_reg   (*((volatile unsigned int*) ISO_CEC_TXDR4_reg))
#define ISO_CEC_TXDR4_inst_adr                                                       "0x0048"
#define ISO_CEC_TXDR4_inst                                                           0x0048
#define ISO_CEC_TXDR4_tx_fifo_c_shift                                                (24)
#define ISO_CEC_TXDR4_tx_fifo_c_mask                                                 (0xFF000000)
#define ISO_CEC_TXDR4_tx_fifo_c(data)                                                (0xFF000000&((data)<<24))
#define ISO_CEC_TXDR4_tx_fifo_c_src(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_TXDR4_get_tx_fifo_c(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_TXDR4_tx_fifo_d_shift                                                (16)
#define ISO_CEC_TXDR4_tx_fifo_d_mask                                                 (0x00FF0000)
#define ISO_CEC_TXDR4_tx_fifo_d(data)                                                (0x00FF0000&((data)<<16))
#define ISO_CEC_TXDR4_tx_fifo_d_src(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXDR4_get_tx_fifo_d(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXDR4_tx_fifo_e_shift                                                (8)
#define ISO_CEC_TXDR4_tx_fifo_e_mask                                                 (0x0000FF00)
#define ISO_CEC_TXDR4_tx_fifo_e(data)                                                (0x0000FF00&((data)<<8))
#define ISO_CEC_TXDR4_tx_fifo_e_src(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXDR4_get_tx_fifo_e(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXDR4_tx_fifo_f_shift                                                (0)
#define ISO_CEC_TXDR4_tx_fifo_f_mask                                                 (0x000000FF)
#define ISO_CEC_TXDR4_tx_fifo_f(data)                                                (0x000000FF&((data)<<0))
#define ISO_CEC_TXDR4_tx_fifo_f_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_CEC_TXDR4_get_tx_fifo_f(data)                                            ((0x000000FF&(data))>>0)


#define ISO_CEC_RXDR1                                                                0x18007524
#define ISO_CEC_RXDR1_reg_addr                                                       "0xB8007524"
#define ISO_CEC_RXDR1_reg                                                            0xB8007524
#define set_ISO_CEC_RXDR1_reg(data)   (*((volatile unsigned int*) ISO_CEC_RXDR1_reg)=data)
#define get_ISO_CEC_RXDR1_reg   (*((volatile unsigned int*) ISO_CEC_RXDR1_reg))
#define ISO_CEC_RXDR1_inst_adr                                                       "0x0049"
#define ISO_CEC_RXDR1_inst                                                           0x0049
#define ISO_CEC_RXDR1_rx_fifo_0_shift                                                (24)
#define ISO_CEC_RXDR1_rx_fifo_0_mask                                                 (0xFF000000)
#define ISO_CEC_RXDR1_rx_fifo_0(data)                                                (0xFF000000&((data)<<24))
#define ISO_CEC_RXDR1_rx_fifo_0_src(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_RXDR1_get_rx_fifo_0(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_RXDR1_rx_fifo_1_shift                                                (16)
#define ISO_CEC_RXDR1_rx_fifo_1_mask                                                 (0x00FF0000)
#define ISO_CEC_RXDR1_rx_fifo_1(data)                                                (0x00FF0000&((data)<<16))
#define ISO_CEC_RXDR1_rx_fifo_1_src(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXDR1_get_rx_fifo_1(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXDR1_rx_fifo_2_shift                                                (8)
#define ISO_CEC_RXDR1_rx_fifo_2_mask                                                 (0x0000FF00)
#define ISO_CEC_RXDR1_rx_fifo_2(data)                                                (0x0000FF00&((data)<<8))
#define ISO_CEC_RXDR1_rx_fifo_2_src(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXDR1_get_rx_fifo_2(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXDR1_rx_fifo_3_shift                                                (0)
#define ISO_CEC_RXDR1_rx_fifo_3_mask                                                 (0x000000FF)
#define ISO_CEC_RXDR1_rx_fifo_3(data)                                                (0x000000FF&((data)<<0))
#define ISO_CEC_RXDR1_rx_fifo_3_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_CEC_RXDR1_get_rx_fifo_3(data)                                            ((0x000000FF&(data))>>0)


#define ISO_CEC_RXDR2                                                                0x18007528
#define ISO_CEC_RXDR2_reg_addr                                                       "0xB8007528"
#define ISO_CEC_RXDR2_reg                                                            0xB8007528
#define set_ISO_CEC_RXDR2_reg(data)   (*((volatile unsigned int*) ISO_CEC_RXDR2_reg)=data)
#define get_ISO_CEC_RXDR2_reg   (*((volatile unsigned int*) ISO_CEC_RXDR2_reg))
#define ISO_CEC_RXDR2_inst_adr                                                       "0x004A"
#define ISO_CEC_RXDR2_inst                                                           0x004A
#define ISO_CEC_RXDR2_rx_fifo_4_shift                                                (24)
#define ISO_CEC_RXDR2_rx_fifo_4_mask                                                 (0xFF000000)
#define ISO_CEC_RXDR2_rx_fifo_4(data)                                                (0xFF000000&((data)<<24))
#define ISO_CEC_RXDR2_rx_fifo_4_src(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_RXDR2_get_rx_fifo_4(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_RXDR2_rx_fifo_5_shift                                                (16)
#define ISO_CEC_RXDR2_rx_fifo_5_mask                                                 (0x00FF0000)
#define ISO_CEC_RXDR2_rx_fifo_5(data)                                                (0x00FF0000&((data)<<16))
#define ISO_CEC_RXDR2_rx_fifo_5_src(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXDR2_get_rx_fifo_5(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXDR2_rx_fifo_6_shift                                                (8)
#define ISO_CEC_RXDR2_rx_fifo_6_mask                                                 (0x0000FF00)
#define ISO_CEC_RXDR2_rx_fifo_6(data)                                                (0x0000FF00&((data)<<8))
#define ISO_CEC_RXDR2_rx_fifo_6_src(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXDR2_get_rx_fifo_6(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXDR2_rx_fifo_7_shift                                                (0)
#define ISO_CEC_RXDR2_rx_fifo_7_mask                                                 (0x000000FF)
#define ISO_CEC_RXDR2_rx_fifo_7(data)                                                (0x000000FF&((data)<<0))
#define ISO_CEC_RXDR2_rx_fifo_7_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_CEC_RXDR2_get_rx_fifo_7(data)                                            ((0x000000FF&(data))>>0)


#define ISO_CEC_RXDR3                                                                0x1800752C
#define ISO_CEC_RXDR3_reg_addr                                                       "0xB800752C"
#define ISO_CEC_RXDR3_reg                                                            0xB800752C
#define set_ISO_CEC_RXDR3_reg(data)   (*((volatile unsigned int*) ISO_CEC_RXDR3_reg)=data)
#define get_ISO_CEC_RXDR3_reg   (*((volatile unsigned int*) ISO_CEC_RXDR3_reg))
#define ISO_CEC_RXDR3_inst_adr                                                       "0x004B"
#define ISO_CEC_RXDR3_inst                                                           0x004B
#define ISO_CEC_RXDR3_rx_fifo_8_shift                                                (24)
#define ISO_CEC_RXDR3_rx_fifo_8_mask                                                 (0xFF000000)
#define ISO_CEC_RXDR3_rx_fifo_8(data)                                                (0xFF000000&((data)<<24))
#define ISO_CEC_RXDR3_rx_fifo_8_src(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_RXDR3_get_rx_fifo_8(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_RXDR3_rx_fifo_9_shift                                                (16)
#define ISO_CEC_RXDR3_rx_fifo_9_mask                                                 (0x00FF0000)
#define ISO_CEC_RXDR3_rx_fifo_9(data)                                                (0x00FF0000&((data)<<16))
#define ISO_CEC_RXDR3_rx_fifo_9_src(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXDR3_get_rx_fifo_9(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXDR3_rx_fifo_a_shift                                                (8)
#define ISO_CEC_RXDR3_rx_fifo_a_mask                                                 (0x0000FF00)
#define ISO_CEC_RXDR3_rx_fifo_a(data)                                                (0x0000FF00&((data)<<8))
#define ISO_CEC_RXDR3_rx_fifo_a_src(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXDR3_get_rx_fifo_a(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXDR3_rx_fifo_b_shift                                                (0)
#define ISO_CEC_RXDR3_rx_fifo_b_mask                                                 (0x000000FF)
#define ISO_CEC_RXDR3_rx_fifo_b(data)                                                (0x000000FF&((data)<<0))
#define ISO_CEC_RXDR3_rx_fifo_b_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_CEC_RXDR3_get_rx_fifo_b(data)                                            ((0x000000FF&(data))>>0)


#define ISO_CEC_RXDR4                                                                0x18007530
#define ISO_CEC_RXDR4_reg_addr                                                       "0xB8007530"
#define ISO_CEC_RXDR4_reg                                                            0xB8007530
#define set_ISO_CEC_RXDR4_reg(data)   (*((volatile unsigned int*) ISO_CEC_RXDR4_reg)=data)
#define get_ISO_CEC_RXDR4_reg   (*((volatile unsigned int*) ISO_CEC_RXDR4_reg))
#define ISO_CEC_RXDR4_inst_adr                                                       "0x004C"
#define ISO_CEC_RXDR4_inst                                                           0x004C
#define ISO_CEC_RXDR4_rx_fifo_c_shift                                                (24)
#define ISO_CEC_RXDR4_rx_fifo_c_mask                                                 (0xFF000000)
#define ISO_CEC_RXDR4_rx_fifo_c(data)                                                (0xFF000000&((data)<<24))
#define ISO_CEC_RXDR4_rx_fifo_c_src(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_RXDR4_get_rx_fifo_c(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_RXDR4_rx_fifo_d_shift                                                (16)
#define ISO_CEC_RXDR4_rx_fifo_d_mask                                                 (0x00FF0000)
#define ISO_CEC_RXDR4_rx_fifo_d(data)                                                (0x00FF0000&((data)<<16))
#define ISO_CEC_RXDR4_rx_fifo_d_src(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXDR4_get_rx_fifo_d(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXDR4_rx_fifo_e_shift                                                (8)
#define ISO_CEC_RXDR4_rx_fifo_e_mask                                                 (0x0000FF00)
#define ISO_CEC_RXDR4_rx_fifo_e(data)                                                (0x0000FF00&((data)<<8))
#define ISO_CEC_RXDR4_rx_fifo_e_src(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXDR4_get_rx_fifo_e(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXDR4_rx_fifo_f_shift                                                (0)
#define ISO_CEC_RXDR4_rx_fifo_f_mask                                                 (0x000000FF)
#define ISO_CEC_RXDR4_rx_fifo_f(data)                                                (0x000000FF&((data)<<0))
#define ISO_CEC_RXDR4_rx_fifo_f_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_CEC_RXDR4_get_rx_fifo_f(data)                                            ((0x000000FF&(data))>>0)


#define ISO_CEC_RXTCR0                                                               0x18007534
#define ISO_CEC_RXTCR0_reg_addr                                                      "0xB8007534"
#define ISO_CEC_RXTCR0_reg                                                           0xB8007534
#define set_ISO_CEC_RXTCR0_reg(data)   (*((volatile unsigned int*) ISO_CEC_RXTCR0_reg)=data)
#define get_ISO_CEC_RXTCR0_reg   (*((volatile unsigned int*) ISO_CEC_RXTCR0_reg))
#define ISO_CEC_RXTCR0_inst_adr                                                      "0x004D"
#define ISO_CEC_RXTCR0_inst                                                          0x004D
#define ISO_CEC_RXTCR0_rx_start_low_shift                                            (24)
#define ISO_CEC_RXTCR0_rx_start_low_mask                                             (0xFF000000)
#define ISO_CEC_RXTCR0_rx_start_low(data)                                            (0xFF000000&((data)<<24))
#define ISO_CEC_RXTCR0_rx_start_low_src(data)                                        ((0xFF000000&(data))>>24)
#define ISO_CEC_RXTCR0_get_rx_start_low(data)                                        ((0xFF000000&(data))>>24)
#define ISO_CEC_RXTCR0_rx_start_period_shift                                         (16)
#define ISO_CEC_RXTCR0_rx_start_period_mask                                          (0x00FF0000)
#define ISO_CEC_RXTCR0_rx_start_period(data)                                         (0x00FF0000&((data)<<16))
#define ISO_CEC_RXTCR0_rx_start_period_src(data)                                     ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXTCR0_get_rx_start_period(data)                                     ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXTCR0_rx_data_sample_shift                                          (8)
#define ISO_CEC_RXTCR0_rx_data_sample_mask                                           (0x0000FF00)
#define ISO_CEC_RXTCR0_rx_data_sample(data)                                          (0x0000FF00&((data)<<8))
#define ISO_CEC_RXTCR0_rx_data_sample_src(data)                                      ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXTCR0_get_rx_data_sample(data)                                      ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXTCR0_rx_data_period_shift                                          (0)
#define ISO_CEC_RXTCR0_rx_data_period_mask                                           (0x000000FF)
#define ISO_CEC_RXTCR0_rx_data_period(data)                                          (0x000000FF&((data)<<0))
#define ISO_CEC_RXTCR0_rx_data_period_src(data)                                      ((0x000000FF&(data))>>0)
#define ISO_CEC_RXTCR0_get_rx_data_period(data)                                      ((0x000000FF&(data))>>0)


#define ISO_CEC_TXTCR0                                                               0x18007538
#define ISO_CEC_TXTCR0_reg_addr                                                      "0xB8007538"
#define ISO_CEC_TXTCR0_reg                                                           0xB8007538
#define set_ISO_CEC_TXTCR0_reg(data)   (*((volatile unsigned int*) ISO_CEC_TXTCR0_reg)=data)
#define get_ISO_CEC_TXTCR0_reg   (*((volatile unsigned int*) ISO_CEC_TXTCR0_reg))
#define ISO_CEC_TXTCR0_inst_adr                                                      "0x004E"
#define ISO_CEC_TXTCR0_inst                                                          0x004E
#define ISO_CEC_TXTCR0_tx_start_low_shift                                            (8)
#define ISO_CEC_TXTCR0_tx_start_low_mask                                             (0x0000FF00)
#define ISO_CEC_TXTCR0_tx_start_low(data)                                            (0x0000FF00&((data)<<8))
#define ISO_CEC_TXTCR0_tx_start_low_src(data)                                        ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXTCR0_get_tx_start_low(data)                                        ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXTCR0_tx_start_high_shift                                           (0)
#define ISO_CEC_TXTCR0_tx_start_high_mask                                            (0x000000FF)
#define ISO_CEC_TXTCR0_tx_start_high(data)                                           (0x000000FF&((data)<<0))
#define ISO_CEC_TXTCR0_tx_start_high_src(data)                                       ((0x000000FF&(data))>>0)
#define ISO_CEC_TXTCR0_get_tx_start_high(data)                                       ((0x000000FF&(data))>>0)


#define ISO_CEC_TXTCR1                                                               0x1800753C
#define ISO_CEC_TXTCR1_reg_addr                                                      "0xB800753C"
#define ISO_CEC_TXTCR1_reg                                                           0xB800753C
#define set_ISO_CEC_TXTCR1_reg(data)   (*((volatile unsigned int*) ISO_CEC_TXTCR1_reg)=data)
#define get_ISO_CEC_TXTCR1_reg   (*((volatile unsigned int*) ISO_CEC_TXTCR1_reg))
#define ISO_CEC_TXTCR1_inst_adr                                                      "0x004F"
#define ISO_CEC_TXTCR1_inst                                                          0x004F
#define ISO_CEC_TXTCR1_tx_data_low_shift                                             (16)
#define ISO_CEC_TXTCR1_tx_data_low_mask                                              (0x00FF0000)
#define ISO_CEC_TXTCR1_tx_data_low(data)                                             (0x00FF0000&((data)<<16))
#define ISO_CEC_TXTCR1_tx_data_low_src(data)                                         ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXTCR1_get_tx_data_low(data)                                         ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXTCR1_tx_data_01_shift                                              (8)
#define ISO_CEC_TXTCR1_tx_data_01_mask                                               (0x0000FF00)
#define ISO_CEC_TXTCR1_tx_data_01(data)                                              (0x0000FF00&((data)<<8))
#define ISO_CEC_TXTCR1_tx_data_01_src(data)                                          ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXTCR1_get_tx_data_01(data)                                          ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXTCR1_tx_data_high_shift                                            (0)
#define ISO_CEC_TXTCR1_tx_data_high_mask                                             (0x000000FF)
#define ISO_CEC_TXTCR1_tx_data_high(data)                                            (0x000000FF&((data)<<0))
#define ISO_CEC_TXTCR1_tx_data_high_src(data)                                        ((0x000000FF&(data))>>0)
#define ISO_CEC_TXTCR1_get_tx_data_high(data)                                        ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_01                                                0x18007540
#define ISO_GDI_CEC_COMPARE_OPCODE_01_reg_addr                                       "0xB8007540"
#define ISO_GDI_CEC_COMPARE_OPCODE_01_reg                                            0xB8007540
#define set_ISO_GDI_CEC_COMPARE_OPCODE_01_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_01_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_01_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_01_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_01_inst_adr                                       "0x0050"
#define ISO_GDI_CEC_COMPARE_OPCODE_01_inst                                           0x0050
#define ISO_GDI_CEC_COMPARE_OPCODE_01_compare_opcode_01_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_01_compare_opcode_01_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_01_compare_opcode_01(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_01_compare_opcode_01_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_01_get_compare_opcode_01(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_SEND_OPCODE_01                                                   0x18007544
#define ISO_GDI_CEC_SEND_OPCODE_01_reg_addr                                          "0xB8007544"
#define ISO_GDI_CEC_SEND_OPCODE_01_reg                                               0xB8007544
#define set_ISO_GDI_CEC_SEND_OPCODE_01_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPCODE_01_reg)=data)
#define get_ISO_GDI_CEC_SEND_OPCODE_01_reg   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPCODE_01_reg))
#define ISO_GDI_CEC_SEND_OPCODE_01_inst_adr                                          "0x0051"
#define ISO_GDI_CEC_SEND_OPCODE_01_inst                                              0x0051
#define ISO_GDI_CEC_SEND_OPCODE_01_send_opcode_01_shift                              (0)
#define ISO_GDI_CEC_SEND_OPCODE_01_send_opcode_01_mask                               (0x000000FF)
#define ISO_GDI_CEC_SEND_OPCODE_01_send_opcode_01(data)                              (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_SEND_OPCODE_01_send_opcode_01_src(data)                          ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_SEND_OPCODE_01_get_send_opcode_01(data)                          ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01                                            0x18007548
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_reg_addr                                   "0xB8007548"
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_reg                                        0xB8007548
#define set_ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_reg)=data)
#define get_ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_reg   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_reg))
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_inst_adr                                   "0x0052"
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_inst                                       0x0052
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_operand_number_01_shift                    (0)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_operand_number_01_mask                     (0x00000003)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_operand_number_01(data)                    (0x00000003&((data)<<0))
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_operand_number_01_src(data)                ((0x00000003&(data))>>0)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_get_operand_number_01(data)                ((0x00000003&(data))>>0)


#define ISO_GDI_CEC_OPRAND_01                                                        0x1800754C
#define ISO_GDI_CEC_OPRAND_01_reg_addr                                               "0xB800754C"
#define ISO_GDI_CEC_OPRAND_01_reg                                                    0xB800754C
#define set_ISO_GDI_CEC_OPRAND_01_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_01_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_01_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_01_reg))
#define ISO_GDI_CEC_OPRAND_01_inst_adr                                               "0x0053"
#define ISO_GDI_CEC_OPRAND_01_inst                                                   0x0053
#define ISO_GDI_CEC_OPRAND_01_operand_01_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_01_operand_01_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_01_operand_01(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_01_operand_01_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_01_get_operand_01(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_OPRAND_02                                                        0x18007550
#define ISO_GDI_CEC_OPRAND_02_reg_addr                                               "0xB8007550"
#define ISO_GDI_CEC_OPRAND_02_reg                                                    0xB8007550
#define set_ISO_GDI_CEC_OPRAND_02_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_02_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_02_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_02_reg))
#define ISO_GDI_CEC_OPRAND_02_inst_adr                                               "0x0054"
#define ISO_GDI_CEC_OPRAND_02_inst                                                   0x0054
#define ISO_GDI_CEC_OPRAND_02_operand_02_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_02_operand_02_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_02_operand_02(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_02_operand_02_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_02_get_operand_02(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_OPRAND_03                                                        0x18007554
#define ISO_GDI_CEC_OPRAND_03_reg_addr                                               "0xB8007554"
#define ISO_GDI_CEC_OPRAND_03_reg                                                    0xB8007554
#define set_ISO_GDI_CEC_OPRAND_03_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_03_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_03_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_03_reg))
#define ISO_GDI_CEC_OPRAND_03_inst_adr                                               "0x0055"
#define ISO_GDI_CEC_OPRAND_03_inst                                                   0x0055
#define ISO_GDI_CEC_OPRAND_03_operand_03_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_03_operand_03_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_03_operand_03(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_03_operand_03_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_03_get_operand_03(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_02                                                0x18007558
#define ISO_GDI_CEC_COMPARE_OPCODE_02_reg_addr                                       "0xB8007558"
#define ISO_GDI_CEC_COMPARE_OPCODE_02_reg                                            0xB8007558
#define set_ISO_GDI_CEC_COMPARE_OPCODE_02_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_02_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_02_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_02_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_02_inst_adr                                       "0x0056"
#define ISO_GDI_CEC_COMPARE_OPCODE_02_inst                                           0x0056
#define ISO_GDI_CEC_COMPARE_OPCODE_02_compare_opcode_02_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_02_compare_opcode_02_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_02_compare_opcode_02(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_02_compare_opcode_02_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_02_get_compare_opcode_02(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_SEND_OPCODE_02                                                   0x1800755C
#define ISO_GDI_CEC_SEND_OPCODE_02_reg_addr                                          "0xB800755C"
#define ISO_GDI_CEC_SEND_OPCODE_02_reg                                               0xB800755C
#define set_ISO_GDI_CEC_SEND_OPCODE_02_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPCODE_02_reg)=data)
#define get_ISO_GDI_CEC_SEND_OPCODE_02_reg   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPCODE_02_reg))
#define ISO_GDI_CEC_SEND_OPCODE_02_inst_adr                                          "0x0057"
#define ISO_GDI_CEC_SEND_OPCODE_02_inst                                              0x0057
#define ISO_GDI_CEC_SEND_OPCODE_02_send_opcode_02_shift                              (0)
#define ISO_GDI_CEC_SEND_OPCODE_02_send_opcode_02_mask                               (0x000000FF)
#define ISO_GDI_CEC_SEND_OPCODE_02_send_opcode_02(data)                              (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_SEND_OPCODE_02_send_opcode_02_src(data)                          ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_SEND_OPCODE_02_get_send_opcode_02(data)                          ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02                                            0x18007560
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_reg_addr                                   "0xB8007560"
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_reg                                        0xB8007560
#define set_ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_reg)=data)
#define get_ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_reg   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_reg))
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_inst_adr                                   "0x0058"
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_inst                                       0x0058
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_operand_number_02_shift                    (0)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_operand_number_02_mask                     (0x00000003)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_operand_number_02(data)                    (0x00000003&((data)<<0))
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_operand_number_02_src(data)                ((0x00000003&(data))>>0)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_get_operand_number_02(data)                ((0x00000003&(data))>>0)


#define ISO_GDI_CEC_OPRAND_04                                                        0x18007564
#define ISO_GDI_CEC_OPRAND_04_reg_addr                                               "0xB8007564"
#define ISO_GDI_CEC_OPRAND_04_reg                                                    0xB8007564
#define set_ISO_GDI_CEC_OPRAND_04_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_04_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_04_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_04_reg))
#define ISO_GDI_CEC_OPRAND_04_inst_adr                                               "0x0059"
#define ISO_GDI_CEC_OPRAND_04_inst                                                   0x0059
#define ISO_GDI_CEC_OPRAND_04_operand_04_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_04_operand_04_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_04_operand_04(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_04_operand_04_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_04_get_operand_04(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_OPRAND_05                                                        0x18007568
#define ISO_GDI_CEC_OPRAND_05_reg_addr                                               "0xB8007568"
#define ISO_GDI_CEC_OPRAND_05_reg                                                    0xB8007568
#define set_ISO_GDI_CEC_OPRAND_05_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_05_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_05_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_05_reg))
#define ISO_GDI_CEC_OPRAND_05_inst_adr                                               "0x005A"
#define ISO_GDI_CEC_OPRAND_05_inst                                                   0x005A
#define ISO_GDI_CEC_OPRAND_05_operand_05_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_05_operand_05_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_05_operand_05(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_05_operand_05_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_05_get_operand_05(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_OPRAND_06                                                        0x1800756C
#define ISO_GDI_CEC_OPRAND_06_reg_addr                                               "0xB800756C"
#define ISO_GDI_CEC_OPRAND_06_reg                                                    0xB800756C
#define set_ISO_GDI_CEC_OPRAND_06_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_06_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_06_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_06_reg))
#define ISO_GDI_CEC_OPRAND_06_inst_adr                                               "0x005B"
#define ISO_GDI_CEC_OPRAND_06_inst                                                   0x005B
#define ISO_GDI_CEC_OPRAND_06_operand_06_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_06_operand_06_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_06_operand_06(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_06_operand_06_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_06_get_operand_06(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_03                                                0x18007570
#define ISO_GDI_CEC_COMPARE_OPCODE_03_reg_addr                                       "0xB8007570"
#define ISO_GDI_CEC_COMPARE_OPCODE_03_reg                                            0xB8007570
#define set_ISO_GDI_CEC_COMPARE_OPCODE_03_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_03_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_03_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_03_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_03_inst_adr                                       "0x005C"
#define ISO_GDI_CEC_COMPARE_OPCODE_03_inst                                           0x005C
#define ISO_GDI_CEC_COMPARE_OPCODE_03_compare_opcode_03_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_03_compare_opcode_03_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_03_compare_opcode_03(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_03_compare_opcode_03_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_03_get_compare_opcode_03(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_SEND_OPCODE_03                                                   0x18007574
#define ISO_GDI_CEC_SEND_OPCODE_03_reg_addr                                          "0xB8007574"
#define ISO_GDI_CEC_SEND_OPCODE_03_reg                                               0xB8007574
#define set_ISO_GDI_CEC_SEND_OPCODE_03_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPCODE_03_reg)=data)
#define get_ISO_GDI_CEC_SEND_OPCODE_03_reg   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPCODE_03_reg))
#define ISO_GDI_CEC_SEND_OPCODE_03_inst_adr                                          "0x005D"
#define ISO_GDI_CEC_SEND_OPCODE_03_inst                                              0x005D
#define ISO_GDI_CEC_SEND_OPCODE_03_send_opcode_03_shift                              (0)
#define ISO_GDI_CEC_SEND_OPCODE_03_send_opcode_03_mask                               (0x000000FF)
#define ISO_GDI_CEC_SEND_OPCODE_03_send_opcode_03(data)                              (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_SEND_OPCODE_03_send_opcode_03_src(data)                          ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_SEND_OPCODE_03_get_send_opcode_03(data)                          ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03                                            0x18007578
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_reg_addr                                   "0xB8007578"
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_reg                                        0xB8007578
#define set_ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_reg)=data)
#define get_ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_reg   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_reg))
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_inst_adr                                   "0x005E"
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_inst                                       0x005E
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_operand_number_03_shift                    (0)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_operand_number_03_mask                     (0x00000003)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_operand_number_03(data)                    (0x00000003&((data)<<0))
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_operand_number_03_src(data)                ((0x00000003&(data))>>0)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_get_operand_number_03(data)                ((0x00000003&(data))>>0)


#define ISO_GDI_CEC_OPRAND_07                                                        0x1800757C
#define ISO_GDI_CEC_OPRAND_07_reg_addr                                               "0xB800757C"
#define ISO_GDI_CEC_OPRAND_07_reg                                                    0xB800757C
#define set_ISO_GDI_CEC_OPRAND_07_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_07_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_07_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_07_reg))
#define ISO_GDI_CEC_OPRAND_07_inst_adr                                               "0x005F"
#define ISO_GDI_CEC_OPRAND_07_inst                                                   0x005F
#define ISO_GDI_CEC_OPRAND_07_operand_07_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_07_operand_07_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_07_operand_07(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_07_operand_07_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_07_get_operand_07(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_OPRAND_08                                                        0x18007580
#define ISO_GDI_CEC_OPRAND_08_reg_addr                                               "0xB8007580"
#define ISO_GDI_CEC_OPRAND_08_reg                                                    0xB8007580
#define set_ISO_GDI_CEC_OPRAND_08_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_08_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_08_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_08_reg))
#define ISO_GDI_CEC_OPRAND_08_inst_adr                                               "0x0060"
#define ISO_GDI_CEC_OPRAND_08_inst                                                   0x0060
#define ISO_GDI_CEC_OPRAND_08_operand_08_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_08_operand_08_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_08_operand_08(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_08_operand_08_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_08_get_operand_08(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_OPRAND_09                                                        0x18007584
#define ISO_GDI_CEC_OPRAND_09_reg_addr                                               "0xB8007584"
#define ISO_GDI_CEC_OPRAND_09_reg                                                    0xB8007584
#define set_ISO_GDI_CEC_OPRAND_09_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_09_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_09_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_09_reg))
#define ISO_GDI_CEC_OPRAND_09_inst_adr                                               "0x0061"
#define ISO_GDI_CEC_OPRAND_09_inst                                                   0x0061
#define ISO_GDI_CEC_OPRAND_09_operand_09_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_09_operand_09_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_09_operand_09(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_09_operand_09_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_09_get_operand_09(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_04                                                0x18007588
#define ISO_GDI_CEC_COMPARE_OPCODE_04_reg_addr                                       "0xB8007588"
#define ISO_GDI_CEC_COMPARE_OPCODE_04_reg                                            0xB8007588
#define set_ISO_GDI_CEC_COMPARE_OPCODE_04_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_04_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_04_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_04_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_04_inst_adr                                       "0x0062"
#define ISO_GDI_CEC_COMPARE_OPCODE_04_inst                                           0x0062
#define ISO_GDI_CEC_COMPARE_OPCODE_04_compare_opcode_04_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_04_compare_opcode_04_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_04_compare_opcode_04(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_04_compare_opcode_04_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_04_get_compare_opcode_04(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_SEND_OPCODE_04                                                   0x1800758C
#define ISO_GDI_CEC_SEND_OPCODE_04_reg_addr                                          "0xB800758C"
#define ISO_GDI_CEC_SEND_OPCODE_04_reg                                               0xB800758C
#define set_ISO_GDI_CEC_SEND_OPCODE_04_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPCODE_04_reg)=data)
#define get_ISO_GDI_CEC_SEND_OPCODE_04_reg   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPCODE_04_reg))
#define ISO_GDI_CEC_SEND_OPCODE_04_inst_adr                                          "0x0063"
#define ISO_GDI_CEC_SEND_OPCODE_04_inst                                              0x0063
#define ISO_GDI_CEC_SEND_OPCODE_04_send_opcode_04_shift                              (0)
#define ISO_GDI_CEC_SEND_OPCODE_04_send_opcode_04_mask                               (0x000000FF)
#define ISO_GDI_CEC_SEND_OPCODE_04_send_opcode_04(data)                              (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_SEND_OPCODE_04_send_opcode_04_src(data)                          ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_SEND_OPCODE_04_get_send_opcode_04(data)                          ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04                                            0x18007590
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_reg_addr                                   "0xB8007590"
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_reg                                        0xB8007590
#define set_ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_reg)=data)
#define get_ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_reg   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_reg))
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_inst_adr                                   "0x0064"
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_inst                                       0x0064
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_operand_number_04_shift                    (0)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_operand_number_04_mask                     (0x00000003)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_operand_number_04(data)                    (0x00000003&((data)<<0))
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_operand_number_04_src(data)                ((0x00000003&(data))>>0)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_get_operand_number_04(data)                ((0x00000003&(data))>>0)


#define ISO_GDI_CEC_OPRAND_10                                                        0x18007594
#define ISO_GDI_CEC_OPRAND_10_reg_addr                                               "0xB8007594"
#define ISO_GDI_CEC_OPRAND_10_reg                                                    0xB8007594
#define set_ISO_GDI_CEC_OPRAND_10_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_10_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_10_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_10_reg))
#define ISO_GDI_CEC_OPRAND_10_inst_adr                                               "0x0065"
#define ISO_GDI_CEC_OPRAND_10_inst                                                   0x0065
#define ISO_GDI_CEC_OPRAND_10_operand_10_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_10_operand_10_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_10_operand_10(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_10_operand_10_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_10_get_operand_10(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_OPRAND_11                                                        0x18007598
#define ISO_GDI_CEC_OPRAND_11_reg_addr                                               "0xB8007598"
#define ISO_GDI_CEC_OPRAND_11_reg                                                    0xB8007598
#define set_ISO_GDI_CEC_OPRAND_11_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_11_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_11_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_11_reg))
#define ISO_GDI_CEC_OPRAND_11_inst_adr                                               "0x0066"
#define ISO_GDI_CEC_OPRAND_11_inst                                                   0x0066
#define ISO_GDI_CEC_OPRAND_11_operand_11_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_11_operand_11_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_11_operand_11(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_11_operand_11_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_11_get_operand_11(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_OPRAND_12                                                        0x1800759C
#define ISO_GDI_CEC_OPRAND_12_reg_addr                                               "0xB800759C"
#define ISO_GDI_CEC_OPRAND_12_reg                                                    0xB800759C
#define set_ISO_GDI_CEC_OPRAND_12_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_12_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_12_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_12_reg))
#define ISO_GDI_CEC_OPRAND_12_inst_adr                                               "0x0067"
#define ISO_GDI_CEC_OPRAND_12_inst                                                   0x0067
#define ISO_GDI_CEC_OPRAND_12_operand_12_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_12_operand_12_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_12_operand_12(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_12_operand_12_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_12_get_operand_12(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_05                                                0x180075A0
#define ISO_GDI_CEC_COMPARE_OPCODE_05_reg_addr                                       "0xB80075A0"
#define ISO_GDI_CEC_COMPARE_OPCODE_05_reg                                            0xB80075A0
#define set_ISO_GDI_CEC_COMPARE_OPCODE_05_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_05_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_05_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_05_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_05_inst_adr                                       "0x0068"
#define ISO_GDI_CEC_COMPARE_OPCODE_05_inst                                           0x0068
#define ISO_GDI_CEC_COMPARE_OPCODE_05_compare_opcode_05_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_05_compare_opcode_05_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_05_compare_opcode_05(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_05_compare_opcode_05_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_05_get_compare_opcode_05(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_06                                                0x180075A4
#define ISO_GDI_CEC_COMPARE_OPCODE_06_reg_addr                                       "0xB80075A4"
#define ISO_GDI_CEC_COMPARE_OPCODE_06_reg                                            0xB80075A4
#define set_ISO_GDI_CEC_COMPARE_OPCODE_06_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_06_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_06_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_06_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_06_inst_adr                                       "0x0069"
#define ISO_GDI_CEC_COMPARE_OPCODE_06_inst                                           0x0069
#define ISO_GDI_CEC_COMPARE_OPCODE_06_compare_opcode_06_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_06_compare_opcode_06_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_06_compare_opcode_06(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_06_compare_opcode_06_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_06_get_compare_opcode_06(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_07                                                0x180075A8
#define ISO_GDI_CEC_COMPARE_OPCODE_07_reg_addr                                       "0xB80075A8"
#define ISO_GDI_CEC_COMPARE_OPCODE_07_reg                                            0xB80075A8
#define set_ISO_GDI_CEC_COMPARE_OPCODE_07_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_07_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_07_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_07_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_07_inst_adr                                       "0x006A"
#define ISO_GDI_CEC_COMPARE_OPCODE_07_inst                                           0x006A
#define ISO_GDI_CEC_COMPARE_OPCODE_07_compare_opcode_07_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_07_compare_opcode_07_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_07_compare_opcode_07(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_07_compare_opcode_07_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_07_get_compare_opcode_07(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_08                                                0x180075AC
#define ISO_GDI_CEC_COMPARE_OPCODE_08_reg_addr                                       "0xB80075AC"
#define ISO_GDI_CEC_COMPARE_OPCODE_08_reg                                            0xB80075AC
#define set_ISO_GDI_CEC_COMPARE_OPCODE_08_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_08_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_08_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_08_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_08_inst_adr                                       "0x006B"
#define ISO_GDI_CEC_COMPARE_OPCODE_08_inst                                           0x006B
#define ISO_GDI_CEC_COMPARE_OPCODE_08_compare_opcode_08_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_08_compare_opcode_08_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_08_compare_opcode_08(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_08_compare_opcode_08_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_08_get_compare_opcode_08(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_09                                                0x180075B0
#define ISO_GDI_CEC_COMPARE_OPCODE_09_reg_addr                                       "0xB80075B0"
#define ISO_GDI_CEC_COMPARE_OPCODE_09_reg                                            0xB80075B0
#define set_ISO_GDI_CEC_COMPARE_OPCODE_09_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_09_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_09_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_09_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_09_inst_adr                                       "0x006C"
#define ISO_GDI_CEC_COMPARE_OPCODE_09_inst                                           0x006C
#define ISO_GDI_CEC_COMPARE_OPCODE_09_compare_opcode_09_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_09_compare_opcode_09_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_09_compare_opcode_09(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_09_compare_opcode_09_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_09_get_compare_opcode_09(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_10                                                0x180075B4
#define ISO_GDI_CEC_COMPARE_OPCODE_10_reg_addr                                       "0xB80075B4"
#define ISO_GDI_CEC_COMPARE_OPCODE_10_reg                                            0xB80075B4
#define set_ISO_GDI_CEC_COMPARE_OPCODE_10_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_10_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_10_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_10_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_10_inst_adr                                       "0x006D"
#define ISO_GDI_CEC_COMPARE_OPCODE_10_inst                                           0x006D
#define ISO_GDI_CEC_COMPARE_OPCODE_10_compare_opcode_10_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_10_compare_opcode_10_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_10_compare_opcode_10(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_10_compare_opcode_10_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_10_get_compare_opcode_10(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_11                                                0x180075B8
#define ISO_GDI_CEC_COMPARE_OPCODE_11_reg_addr                                       "0xB80075B8"
#define ISO_GDI_CEC_COMPARE_OPCODE_11_reg                                            0xB80075B8
#define set_ISO_GDI_CEC_COMPARE_OPCODE_11_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_11_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_11_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_11_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_11_inst_adr                                       "0x006E"
#define ISO_GDI_CEC_COMPARE_OPCODE_11_inst                                           0x006E
#define ISO_GDI_CEC_COMPARE_OPCODE_11_compare_opcode_11_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_11_compare_opcode_11_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_11_compare_opcode_11(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_11_compare_opcode_11_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_11_get_compare_opcode_11(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_12                                                0x180075BC
#define ISO_GDI_CEC_COMPARE_OPCODE_12_reg_addr                                       "0xB80075BC"
#define ISO_GDI_CEC_COMPARE_OPCODE_12_reg                                            0xB80075BC
#define set_ISO_GDI_CEC_COMPARE_OPCODE_12_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_12_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_12_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_12_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_12_inst_adr                                       "0x006F"
#define ISO_GDI_CEC_COMPARE_OPCODE_12_inst                                           0x006F
#define ISO_GDI_CEC_COMPARE_OPCODE_12_compare_opcode_12_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_12_compare_opcode_12_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_12_compare_opcode_12(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_12_compare_opcode_12_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_12_get_compare_opcode_12(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_13                                                0x180075C0
#define ISO_GDI_CEC_COMPARE_OPCODE_13_reg_addr                                       "0xB80075C0"
#define ISO_GDI_CEC_COMPARE_OPCODE_13_reg                                            0xB80075C0
#define set_ISO_GDI_CEC_COMPARE_OPCODE_13_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_13_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_13_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_13_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_13_inst_adr                                       "0x0070"
#define ISO_GDI_CEC_COMPARE_OPCODE_13_inst                                           0x0070
#define ISO_GDI_CEC_COMPARE_OPCODE_13_compare_opcode_13_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_13_compare_opcode_13_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_13_compare_opcode_13(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_13_compare_opcode_13_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_13_get_compare_opcode_13(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_14                                                0x180075C4
#define ISO_GDI_CEC_COMPARE_OPCODE_14_reg_addr                                       "0xB80075C4"
#define ISO_GDI_CEC_COMPARE_OPCODE_14_reg                                            0xB80075C4
#define set_ISO_GDI_CEC_COMPARE_OPCODE_14_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_14_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_14_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_14_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_14_inst_adr                                       "0x0071"
#define ISO_GDI_CEC_COMPARE_OPCODE_14_inst                                           0x0071
#define ISO_GDI_CEC_COMPARE_OPCODE_14_compare_opcode_14_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_14_compare_opcode_14_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_14_compare_opcode_14(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_14_compare_opcode_14_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_14_get_compare_opcode_14(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_15                                                0x180075C8
#define ISO_GDI_CEC_COMPARE_OPCODE_15_reg_addr                                       "0xB80075C8"
#define ISO_GDI_CEC_COMPARE_OPCODE_15_reg                                            0xB80075C8
#define set_ISO_GDI_CEC_COMPARE_OPCODE_15_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_15_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_15_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_15_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_15_inst_adr                                       "0x0072"
#define ISO_GDI_CEC_COMPARE_OPCODE_15_inst                                           0x0072
#define ISO_GDI_CEC_COMPARE_OPCODE_15_compare_opcode_15_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_15_compare_opcode_15_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_15_compare_opcode_15(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_15_compare_opcode_15_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_15_get_compare_opcode_15(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_OPCODE_ENABLE                                                    0x180075CC
#define ISO_GDI_CEC_OPCODE_ENABLE_reg_addr                                           "0xB80075CC"
#define ISO_GDI_CEC_OPCODE_ENABLE_reg                                                0xB80075CC
#define set_ISO_GDI_CEC_OPCODE_ENABLE_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPCODE_ENABLE_reg)=data)
#define get_ISO_GDI_CEC_OPCODE_ENABLE_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPCODE_ENABLE_reg))
#define ISO_GDI_CEC_OPCODE_ENABLE_inst_adr                                           "0x0073"
#define ISO_GDI_CEC_OPCODE_ENABLE_inst                                               0x0073
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_15_shift                         (14)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_15_mask                          (0x00004000)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_15(data)                         (0x00004000&((data)<<14))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_15_src(data)                     ((0x00004000&(data))>>14)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_15(data)                     ((0x00004000&(data))>>14)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_14_shift                         (13)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_14_mask                          (0x00002000)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_14(data)                         (0x00002000&((data)<<13))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_14_src(data)                     ((0x00002000&(data))>>13)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_14(data)                     ((0x00002000&(data))>>13)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_13_shift                         (12)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_13_mask                          (0x00001000)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_13(data)                         (0x00001000&((data)<<12))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_13_src(data)                     ((0x00001000&(data))>>12)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_13(data)                     ((0x00001000&(data))>>12)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_12_shift                         (11)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_12_mask                          (0x00000800)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_12(data)                         (0x00000800&((data)<<11))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_12_src(data)                     ((0x00000800&(data))>>11)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_12(data)                     ((0x00000800&(data))>>11)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_11_shift                         (10)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_11_mask                          (0x00000400)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_11(data)                         (0x00000400&((data)<<10))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_11_src(data)                     ((0x00000400&(data))>>10)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_11(data)                     ((0x00000400&(data))>>10)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_10_shift                         (9)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_10_mask                          (0x00000200)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_10(data)                         (0x00000200&((data)<<9))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_10_src(data)                     ((0x00000200&(data))>>9)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_10(data)                     ((0x00000200&(data))>>9)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_09_shift                         (8)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_09_mask                          (0x00000100)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_09(data)                         (0x00000100&((data)<<8))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_09_src(data)                     ((0x00000100&(data))>>8)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_09(data)                     ((0x00000100&(data))>>8)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_08_shift                         (7)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_08_mask                          (0x00000080)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_08(data)                         (0x00000080&((data)<<7))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_08_src(data)                     ((0x00000080&(data))>>7)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_08(data)                     ((0x00000080&(data))>>7)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_07_shift                         (6)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_07_mask                          (0x00000040)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_07(data)                         (0x00000040&((data)<<6))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_07_src(data)                     ((0x00000040&(data))>>6)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_07(data)                     ((0x00000040&(data))>>6)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_06_shift                         (5)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_06_mask                          (0x00000020)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_06(data)                         (0x00000020&((data)<<5))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_06_src(data)                     ((0x00000020&(data))>>5)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_06(data)                     ((0x00000020&(data))>>5)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_05_shift                         (4)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_05_mask                          (0x00000010)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_05(data)                         (0x00000010&((data)<<4))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_05_src(data)                     ((0x00000010&(data))>>4)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_05(data)                     ((0x00000010&(data))>>4)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_04_shift                         (3)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_04_mask                          (0x00000008)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_04(data)                         (0x00000008&((data)<<3))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_04_src(data)                     ((0x00000008&(data))>>3)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_04(data)                     ((0x00000008&(data))>>3)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_03_shift                         (2)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_03_mask                          (0x00000004)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_03(data)                         (0x00000004&((data)<<2))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_03_src(data)                     ((0x00000004&(data))>>2)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_03(data)                     ((0x00000004&(data))>>2)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_02_shift                         (1)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_02_mask                          (0x00000002)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_02(data)                         (0x00000002&((data)<<1))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_02_src(data)                     ((0x00000002&(data))>>1)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_02(data)                     ((0x00000002&(data))>>1)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_01_shift                         (0)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_01_mask                          (0x00000001)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_01(data)                         (0x00000001&((data)<<0))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_01_src(data)                     ((0x00000001&(data))>>0)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_01(data)                     ((0x00000001&(data))>>0)


#define ISO_GDI_POWER_SAVING_MODE                                                    0x180075D0
#define ISO_GDI_POWER_SAVING_MODE_reg_addr                                           "0xB80075D0"
#define ISO_GDI_POWER_SAVING_MODE_reg                                                0xB80075D0
#define set_ISO_GDI_POWER_SAVING_MODE_reg(data)   (*((volatile unsigned int*) ISO_GDI_POWER_SAVING_MODE_reg)=data)
#define get_ISO_GDI_POWER_SAVING_MODE_reg   (*((volatile unsigned int*) ISO_GDI_POWER_SAVING_MODE_reg))
#define ISO_GDI_POWER_SAVING_MODE_inst_adr                                           "0x0074"
#define ISO_GDI_POWER_SAVING_MODE_inst                                               0x0074
#define ISO_GDI_POWER_SAVING_MODE_irq_pending_shift                                  (31)
#define ISO_GDI_POWER_SAVING_MODE_irq_pending_mask                                   (0x80000000)
#define ISO_GDI_POWER_SAVING_MODE_irq_pending(data)                                  (0x80000000&((data)<<31))
#define ISO_GDI_POWER_SAVING_MODE_irq_pending_src(data)                              ((0x80000000&(data))>>31)
#define ISO_GDI_POWER_SAVING_MODE_get_irq_pending(data)                              ((0x80000000&(data))>>31)
#define ISO_GDI_POWER_SAVING_MODE_cec_msg_status_01_shift                            (25)
#define ISO_GDI_POWER_SAVING_MODE_cec_msg_status_01_mask                             (0x02000000)
#define ISO_GDI_POWER_SAVING_MODE_cec_msg_status_01(data)                            (0x02000000&((data)<<25))
#define ISO_GDI_POWER_SAVING_MODE_cec_msg_status_01_src(data)                        ((0x02000000&(data))>>25)
#define ISO_GDI_POWER_SAVING_MODE_get_cec_msg_status_01(data)                        ((0x02000000&(data))>>25)
#define ISO_GDI_POWER_SAVING_MODE_cec_msg_status_02_shift                            (24)
#define ISO_GDI_POWER_SAVING_MODE_cec_msg_status_02_mask                             (0x01000000)
#define ISO_GDI_POWER_SAVING_MODE_cec_msg_status_02(data)                            (0x01000000&((data)<<24))
#define ISO_GDI_POWER_SAVING_MODE_cec_msg_status_02_src(data)                        ((0x01000000&(data))>>24)
#define ISO_GDI_POWER_SAVING_MODE_get_cec_msg_status_02(data)                        ((0x01000000&(data))>>24)
#define ISO_GDI_POWER_SAVING_MODE_irq_by_cec_receive_special_cmd_shift               (8)
#define ISO_GDI_POWER_SAVING_MODE_irq_by_cec_receive_special_cmd_mask                (0x00000100)
#define ISO_GDI_POWER_SAVING_MODE_irq_by_cec_receive_special_cmd(data)               (0x00000100&((data)<<8))
#define ISO_GDI_POWER_SAVING_MODE_irq_by_cec_receive_special_cmd_src(data)           ((0x00000100&(data))>>8)
#define ISO_GDI_POWER_SAVING_MODE_get_irq_by_cec_receive_special_cmd(data)           ((0x00000100&(data))>>8)


#define ISO_CEC_ANALOG                                                               0x180075E0
#define ISO_CEC_ANALOG_reg_addr                                                      "0xB80075E0"
#define ISO_CEC_ANALOG_reg                                                           0xB80075E0
#define set_ISO_CEC_ANALOG_reg(data)   (*((volatile unsigned int*) ISO_CEC_ANALOG_reg)=data)
#define get_ISO_CEC_ANALOG_reg   (*((volatile unsigned int*) ISO_CEC_ANALOG_reg))
#define ISO_CEC_ANALOG_inst_adr                                                      "0x0078"
#define ISO_CEC_ANALOG_inst                                                          0x0078
#define ISO_CEC_ANALOG_reg_cec_rpu_en_shift                                          (3)
#define ISO_CEC_ANALOG_reg_cec_rpu_en_mask                                           (0x00000008)
#define ISO_CEC_ANALOG_reg_cec_rpu_en(data)                                          (0x00000008&((data)<<3))
#define ISO_CEC_ANALOG_reg_cec_rpu_en_src(data)                                      ((0x00000008&(data))>>3)
#define ISO_CEC_ANALOG_get_reg_cec_rpu_en(data)                                      ((0x00000008&(data))>>3)
#define ISO_CEC_ANALOG_reg_cec_rsel_shift                                            (0)
#define ISO_CEC_ANALOG_reg_cec_rsel_mask                                             (0x00000007)
#define ISO_CEC_ANALOG_reg_cec_rsel(data)                                            (0x00000007&((data)<<0))
#define ISO_CEC_ANALOG_reg_cec_rsel_src(data)                                        ((0x00000007&(data))>>0)
#define ISO_CEC_ANALOG_get_reg_cec_rsel(data)                                        ((0x00000007&(data))>>0)


#define ISO_DRM_ST                                                                   0x18007600
#define ISO_DRM_ST_reg_addr                                                          "0xB8007600"
#define ISO_DRM_ST_reg                                                               0xB8007600
#define set_ISO_DRM_ST_reg(data)   (*((volatile unsigned int*) ISO_DRM_ST_reg)=data)
#define get_ISO_DRM_ST_reg   (*((volatile unsigned int*) ISO_DRM_ST_reg))
#define ISO_DRM_ST_inst_adr                                                          "0x0080"
#define ISO_DRM_ST_inst                                                              0x0080
#define ISO_DRM_ST_set_shift                                                         (0)
#define ISO_DRM_ST_set_mask                                                          (0x00000001)
#define ISO_DRM_ST_set(data)                                                         (0x00000001&((data)<<0))
#define ISO_DRM_ST_set_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_DRM_ST_get_set(data)                                                     ((0x00000001&(data))>>0)


#define ISO_DRM_SECURE_CLK                                                           0x18007604
#define ISO_DRM_SECURE_CLK_reg_addr                                                  "0xB8007604"
#define ISO_DRM_SECURE_CLK_reg                                                       0xB8007604
#define set_ISO_DRM_SECURE_CLK_reg(data)   (*((volatile unsigned int*) ISO_DRM_SECURE_CLK_reg)=data)
#define get_ISO_DRM_SECURE_CLK_reg   (*((volatile unsigned int*) ISO_DRM_SECURE_CLK_reg))
#define ISO_DRM_SECURE_CLK_inst_adr                                                  "0x0081"
#define ISO_DRM_SECURE_CLK_inst                                                      0x0081
#define ISO_DRM_SECURE_CLK_val_shift                                                 (0)
#define ISO_DRM_SECURE_CLK_val_mask                                                  (0xFFFFFFFF)
#define ISO_DRM_SECURE_CLK_val(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ISO_DRM_SECURE_CLK_val_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ISO_DRM_SECURE_CLK_get_val(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ISO_DRM_ELAPSED                                                              0x18007608
#define ISO_DRM_ELAPSED_reg_addr                                                     "0xB8007608"
#define ISO_DRM_ELAPSED_reg                                                          0xB8007608
#define set_ISO_DRM_ELAPSED_reg(data)   (*((volatile unsigned int*) ISO_DRM_ELAPSED_reg)=data)
#define get_ISO_DRM_ELAPSED_reg   (*((volatile unsigned int*) ISO_DRM_ELAPSED_reg))
#define ISO_DRM_ELAPSED_inst_adr                                                     "0x0082"
#define ISO_DRM_ELAPSED_inst                                                         0x0082
#define ISO_DRM_ELAPSED_val_shift                                                    (0)
#define ISO_DRM_ELAPSED_val_mask                                                     (0xFFFFFFFF)
#define ISO_DRM_ELAPSED_val(data)                                                    (0xFFFFFFFF&((data)<<0))
#define ISO_DRM_ELAPSED_val_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define ISO_DRM_ELAPSED_get_val(data)                                                ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST                                                                 0x1800760C
#define ISO_COLD_RST_reg_addr                                                        "0xB800760C"
#define ISO_COLD_RST_reg                                                             0xB800760C
#define set_ISO_COLD_RST_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST_reg)=data)
#define get_ISO_COLD_RST_reg   (*((volatile unsigned int*) ISO_COLD_RST_reg))
#define ISO_COLD_RST_inst_adr                                                        "0x0083"
#define ISO_COLD_RST_inst                                                            0x0083
#define ISO_COLD_RST_val_shift                                                       (0)
#define ISO_COLD_RST_val_mask                                                        (0xFFFFFFFF)
#define ISO_COLD_RST_val(data)                                                       (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST_val_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST_get_val(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST1                                                                0x18007610
#define ISO_COLD_RST1_reg_addr                                                       "0xB8007610"
#define ISO_COLD_RST1_reg                                                            0xB8007610
#define set_ISO_COLD_RST1_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST1_reg)=data)
#define get_ISO_COLD_RST1_reg   (*((volatile unsigned int*) ISO_COLD_RST1_reg))
#define ISO_COLD_RST1_inst_adr                                                       "0x0084"
#define ISO_COLD_RST1_inst                                                           0x0084
#define ISO_COLD_RST1_val_shift                                                      (0)
#define ISO_COLD_RST1_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST1_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST1_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST1_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST2                                                                0x18007614
#define ISO_COLD_RST2_reg_addr                                                       "0xB8007614"
#define ISO_COLD_RST2_reg                                                            0xB8007614
#define set_ISO_COLD_RST2_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST2_reg)=data)
#define get_ISO_COLD_RST2_reg   (*((volatile unsigned int*) ISO_COLD_RST2_reg))
#define ISO_COLD_RST2_inst_adr                                                       "0x0085"
#define ISO_COLD_RST2_inst                                                           0x0085
#define ISO_COLD_RST2_val_shift                                                      (0)
#define ISO_COLD_RST2_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST2_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST2_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST2_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_DRM_CTRL                                                                 0x18007618
#define ISO_DRM_CTRL_reg_addr                                                        "0xB8007618"
#define ISO_DRM_CTRL_reg                                                             0xB8007618
#define set_ISO_DRM_CTRL_reg(data)   (*((volatile unsigned int*) ISO_DRM_CTRL_reg)=data)
#define get_ISO_DRM_CTRL_reg   (*((volatile unsigned int*) ISO_DRM_CTRL_reg))
#define ISO_DRM_CTRL_inst_adr                                                        "0x0086"
#define ISO_DRM_CTRL_inst                                                            0x0086
#define ISO_DRM_CTRL_clk_div_en_shift                                                (1)
#define ISO_DRM_CTRL_clk_div_en_mask                                                 (0x00000002)
#define ISO_DRM_CTRL_clk_div_en(data)                                                (0x00000002&((data)<<1))
#define ISO_DRM_CTRL_clk_div_en_src(data)                                            ((0x00000002&(data))>>1)
#define ISO_DRM_CTRL_get_clk_div_en(data)                                            ((0x00000002&(data))>>1)
#define ISO_DRM_CTRL_clk_sel_shift                                                   (0)
#define ISO_DRM_CTRL_clk_sel_mask                                                    (0x00000001)
#define ISO_DRM_CTRL_clk_sel(data)                                                   (0x00000001&((data)<<0))
#define ISO_DRM_CTRL_clk_sel_src(data)                                               ((0x00000001&(data))>>0)
#define ISO_DRM_CTRL_get_clk_sel(data)                                               ((0x00000001&(data))>>0)


#define ISO_DRM_CLK_DIV                                                              0x1800761c
#define ISO_DRM_CLK_DIV_reg_addr                                                     "0xB800761C"
#define ISO_DRM_CLK_DIV_reg                                                          0xB800761C
#define set_ISO_DRM_CLK_DIV_reg(data)   (*((volatile unsigned int*) ISO_DRM_CLK_DIV_reg)=data)
#define get_ISO_DRM_CLK_DIV_reg   (*((volatile unsigned int*) ISO_DRM_CLK_DIV_reg))
#define ISO_DRM_CLK_DIV_inst_adr                                                     "0x0087"
#define ISO_DRM_CLK_DIV_inst                                                         0x0087
#define ISO_DRM_CLK_DIV_init_shift                                                   (0)
#define ISO_DRM_CLK_DIV_init_mask                                                    (0xFFFFFFFF)
#define ISO_DRM_CLK_DIV_init(data)                                                   (0xFFFFFFFF&((data)<<0))
#define ISO_DRM_CLK_DIV_init_src(data)                                               ((0xFFFFFFFF&(data))>>0)
#define ISO_DRM_CLK_DIV_get_init(data)                                               ((0xFFFFFFFF&(data))>>0)


#define ISO_TC3TVR                                                                   0x18007620
#define ISO_TC3TVR_reg_addr                                                          "0xB8007620"
#define ISO_TC3TVR_reg                                                               0xB8007620
#define set_ISO_TC3TVR_reg(data)   (*((volatile unsigned int*) ISO_TC3TVR_reg)=data)
#define get_ISO_TC3TVR_reg   (*((volatile unsigned int*) ISO_TC3TVR_reg))
#define ISO_TC3TVR_inst_adr                                                          "0x0088"
#define ISO_TC3TVR_inst                                                              0x0088
#define ISO_TC3TVR_tc3tvr_shift                                                      (0)
#define ISO_TC3TVR_tc3tvr_mask                                                       (0xFFFFFFFF)
#define ISO_TC3TVR_tc3tvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_TC3TVR_tc3tvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_TC3TVR_get_tc3tvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_TC3CVR                                                                   0x18007624
#define ISO_TC3CVR_reg_addr                                                          "0xB8007624"
#define ISO_TC3CVR_reg                                                               0xB8007624
#define set_ISO_TC3CVR_reg(data)   (*((volatile unsigned int*) ISO_TC3CVR_reg)=data)
#define get_ISO_TC3CVR_reg   (*((volatile unsigned int*) ISO_TC3CVR_reg))
#define ISO_TC3CVR_inst_adr                                                          "0x0089"
#define ISO_TC3CVR_inst                                                              0x0089
#define ISO_TC3CVR_tc3cvr_shift                                                      (0)
#define ISO_TC3CVR_tc3cvr_mask                                                       (0xFFFFFFFF)
#define ISO_TC3CVR_tc3cvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_TC3CVR_tc3cvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_TC3CVR_get_tc3cvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_TC3CR                                                                    0x18007628
#define ISO_TC3CR_reg_addr                                                           "0xB8007628"
#define ISO_TC3CR_reg                                                                0xB8007628
#define set_ISO_TC3CR_reg(data)   (*((volatile unsigned int*) ISO_TC3CR_reg)=data)
#define get_ISO_TC3CR_reg   (*((volatile unsigned int*) ISO_TC3CR_reg))
#define ISO_TC3CR_inst_adr                                                           "0x008A"
#define ISO_TC3CR_inst                                                               0x008A
#define ISO_TC3CR_tc3en_shift                                                        (31)
#define ISO_TC3CR_tc3en_mask                                                         (0x80000000)
#define ISO_TC3CR_tc3en(data)                                                        (0x80000000&((data)<<31))
#define ISO_TC3CR_tc3en_src(data)                                                    ((0x80000000&(data))>>31)
#define ISO_TC3CR_get_tc3en(data)                                                    ((0x80000000&(data))>>31)
#define ISO_TC3CR_tc3mode_shift                                                      (30)
#define ISO_TC3CR_tc3mode_mask                                                       (0x40000000)
#define ISO_TC3CR_tc3mode(data)                                                      (0x40000000&((data)<<30))
#define ISO_TC3CR_tc3mode_src(data)                                                  ((0x40000000&(data))>>30)
#define ISO_TC3CR_get_tc3mode(data)                                                  ((0x40000000&(data))>>30)
#define ISO_TC3CR_tc3pause_shift                                                     (29)
#define ISO_TC3CR_tc3pause_mask                                                      (0x20000000)
#define ISO_TC3CR_tc3pause(data)                                                     (0x20000000&((data)<<29))
#define ISO_TC3CR_tc3pause_src(data)                                                 ((0x20000000&(data))>>29)
#define ISO_TC3CR_get_tc3pause(data)                                                 ((0x20000000&(data))>>29)
#define ISO_TC3CR_rvda_shift                                                         (24)
#define ISO_TC3CR_rvda_mask                                                          (0x1F000000)
#define ISO_TC3CR_rvda(data)                                                         (0x1F000000&((data)<<24))
#define ISO_TC3CR_rvda_src(data)                                                     ((0x1F000000&(data))>>24)
#define ISO_TC3CR_get_rvda(data)                                                     ((0x1F000000&(data))>>24)


#define ISO_TC3ICR                                                                   0x1800762C
#define ISO_TC3ICR_reg_addr                                                          "0xB800762C"
#define ISO_TC3ICR_reg                                                               0xB800762C
#define set_ISO_TC3ICR_reg(data)   (*((volatile unsigned int*) ISO_TC3ICR_reg)=data)
#define get_ISO_TC3ICR_reg   (*((volatile unsigned int*) ISO_TC3ICR_reg))
#define ISO_TC3ICR_inst_adr                                                          "0x008B"
#define ISO_TC3ICR_inst                                                              0x008B
#define ISO_TC3ICR_tc3ie_shift                                                       (31)
#define ISO_TC3ICR_tc3ie_mask                                                        (0x80000000)
#define ISO_TC3ICR_tc3ie(data)                                                       (0x80000000&((data)<<31))
#define ISO_TC3ICR_tc3ie_src(data)                                                   ((0x80000000&(data))>>31)
#define ISO_TC3ICR_get_tc3ie(data)                                                   ((0x80000000&(data))>>31)


#define ISO_TC4TVR                                                                   0x18007630
#define ISO_TC4TVR_reg_addr                                                          "0xB8007630"
#define ISO_TC4TVR_reg                                                               0xB8007630
#define set_ISO_TC4TVR_reg(data)   (*((volatile unsigned int*) ISO_TC4TVR_reg)=data)
#define get_ISO_TC4TVR_reg   (*((volatile unsigned int*) ISO_TC4TVR_reg))
#define ISO_TC4TVR_inst_adr                                                          "0x008C"
#define ISO_TC4TVR_inst                                                              0x008C
#define ISO_TC4TVR_tc4tvr_shift                                                      (0)
#define ISO_TC4TVR_tc4tvr_mask                                                       (0xFFFFFFFF)
#define ISO_TC4TVR_tc4tvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_TC4TVR_tc4tvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_TC4TVR_get_tc4tvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_TC4CVR                                                                   0x18007634
#define ISO_TC4CVR_reg_addr                                                          "0xB8007634"
#define ISO_TC4CVR_reg                                                               0xB8007634
#define set_ISO_TC4CVR_reg(data)   (*((volatile unsigned int*) ISO_TC4CVR_reg)=data)
#define get_ISO_TC4CVR_reg   (*((volatile unsigned int*) ISO_TC4CVR_reg))
#define ISO_TC4CVR_inst_adr                                                          "0x008D"
#define ISO_TC4CVR_inst                                                              0x008D
#define ISO_TC4CVR_tc4cvr_shift                                                      (0)
#define ISO_TC4CVR_tc4cvr_mask                                                       (0xFFFFFFFF)
#define ISO_TC4CVR_tc4cvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_TC4CVR_tc4cvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_TC4CVR_get_tc4cvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_TC4CR                                                                    0x18007638
#define ISO_TC4CR_reg_addr                                                           "0xB8007638"
#define ISO_TC4CR_reg                                                                0xB8007638
#define set_ISO_TC4CR_reg(data)   (*((volatile unsigned int*) ISO_TC4CR_reg)=data)
#define get_ISO_TC4CR_reg   (*((volatile unsigned int*) ISO_TC4CR_reg))
#define ISO_TC4CR_inst_adr                                                           "0x008E"
#define ISO_TC4CR_inst                                                               0x008E
#define ISO_TC4CR_tc4en_shift                                                        (31)
#define ISO_TC4CR_tc4en_mask                                                         (0x80000000)
#define ISO_TC4CR_tc4en(data)                                                        (0x80000000&((data)<<31))
#define ISO_TC4CR_tc4en_src(data)                                                    ((0x80000000&(data))>>31)
#define ISO_TC4CR_get_tc4en(data)                                                    ((0x80000000&(data))>>31)
#define ISO_TC4CR_tc4mode_shift                                                      (30)
#define ISO_TC4CR_tc4mode_mask                                                       (0x40000000)
#define ISO_TC4CR_tc4mode(data)                                                      (0x40000000&((data)<<30))
#define ISO_TC4CR_tc4mode_src(data)                                                  ((0x40000000&(data))>>30)
#define ISO_TC4CR_get_tc4mode(data)                                                  ((0x40000000&(data))>>30)
#define ISO_TC4CR_tc4pause_shift                                                     (29)
#define ISO_TC4CR_tc4pause_mask                                                      (0x20000000)
#define ISO_TC4CR_tc4pause(data)                                                     (0x20000000&((data)<<29))
#define ISO_TC4CR_tc4pause_src(data)                                                 ((0x20000000&(data))>>29)
#define ISO_TC4CR_get_tc4pause(data)                                                 ((0x20000000&(data))>>29)
#define ISO_TC4CR_rvda_shift                                                         (24)
#define ISO_TC4CR_rvda_mask                                                          (0x1F000000)
#define ISO_TC4CR_rvda(data)                                                         (0x1F000000&((data)<<24))
#define ISO_TC4CR_rvda_src(data)                                                     ((0x1F000000&(data))>>24)
#define ISO_TC4CR_get_rvda(data)                                                     ((0x1F000000&(data))>>24)


#define ISO_TC4ICR                                                                   0x1800763C
#define ISO_TC4ICR_reg_addr                                                          "0xB800763C"
#define ISO_TC4ICR_reg                                                               0xB800763C
#define set_ISO_TC4ICR_reg(data)   (*((volatile unsigned int*) ISO_TC4ICR_reg)=data)
#define get_ISO_TC4ICR_reg   (*((volatile unsigned int*) ISO_TC4ICR_reg))
#define ISO_TC4ICR_inst_adr                                                          "0x008F"
#define ISO_TC4ICR_inst                                                              0x008F
#define ISO_TC4ICR_tc4ie_shift                                                       (31)
#define ISO_TC4ICR_tc4ie_mask                                                        (0x80000000)
#define ISO_TC4ICR_tc4ie(data)                                                       (0x80000000&((data)<<31))
#define ISO_TC4ICR_tc4ie_src(data)                                                   ((0x80000000&(data))>>31)
#define ISO_TC4ICR_get_tc4ie(data)                                                   ((0x80000000&(data))>>31)


#define ISO_NORST_0                                                                  0x18007640
#define ISO_NORST_1                                                                  0x18007644
#define ISO_NORST_2                                                                  0x18007648
#define ISO_NORST_3                                                                  0x1800764C
#define ISO_NORST_4                                                                  0x18007650
#define ISO_NORST_5                                                                  0x18007654
#define ISO_NORST_6                                                                  0x18007658
#define ISO_NORST_7                                                                  0x1800765C
#define ISO_NORST_0_reg_addr                                                         "0xB8007640"
#define ISO_NORST_1_reg_addr                                                         "0xB8007644"
#define ISO_NORST_2_reg_addr                                                         "0xB8007648"
#define ISO_NORST_3_reg_addr                                                         "0xB800764C"
#define ISO_NORST_4_reg_addr                                                         "0xB8007650"
#define ISO_NORST_5_reg_addr                                                         "0xB8007654"
#define ISO_NORST_6_reg_addr                                                         "0xB8007658"
#define ISO_NORST_7_reg_addr                                                         "0xB800765C"
#define ISO_NORST_0_reg                                                              0xB8007640
#define ISO_NORST_1_reg                                                              0xB8007644
#define ISO_NORST_2_reg                                                              0xB8007648
#define ISO_NORST_3_reg                                                              0xB800764C
#define ISO_NORST_4_reg                                                              0xB8007650
#define ISO_NORST_5_reg                                                              0xB8007654
#define ISO_NORST_6_reg                                                              0xB8007658
#define ISO_NORST_7_reg                                                              0xB800765C
#define set_ISO_NORST_0_reg(data)   (*((volatile unsigned int*) ISO_NORST_0_reg)=data)
#define set_ISO_NORST_1_reg(data)   (*((volatile unsigned int*) ISO_NORST_1_reg)=data)
#define set_ISO_NORST_2_reg(data)   (*((volatile unsigned int*) ISO_NORST_2_reg)=data)
#define set_ISO_NORST_3_reg(data)   (*((volatile unsigned int*) ISO_NORST_3_reg)=data)
#define set_ISO_NORST_4_reg(data)   (*((volatile unsigned int*) ISO_NORST_4_reg)=data)
#define set_ISO_NORST_5_reg(data)   (*((volatile unsigned int*) ISO_NORST_5_reg)=data)
#define set_ISO_NORST_6_reg(data)   (*((volatile unsigned int*) ISO_NORST_6_reg)=data)
#define set_ISO_NORST_7_reg(data)   (*((volatile unsigned int*) ISO_NORST_7_reg)=data)
#define get_ISO_NORST_0_reg   (*((volatile unsigned int*) ISO_NORST_0_reg))
#define get_ISO_NORST_1_reg   (*((volatile unsigned int*) ISO_NORST_1_reg))
#define get_ISO_NORST_2_reg   (*((volatile unsigned int*) ISO_NORST_2_reg))
#define get_ISO_NORST_3_reg   (*((volatile unsigned int*) ISO_NORST_3_reg))
#define get_ISO_NORST_4_reg   (*((volatile unsigned int*) ISO_NORST_4_reg))
#define get_ISO_NORST_5_reg   (*((volatile unsigned int*) ISO_NORST_5_reg))
#define get_ISO_NORST_6_reg   (*((volatile unsigned int*) ISO_NORST_6_reg))
#define get_ISO_NORST_7_reg   (*((volatile unsigned int*) ISO_NORST_7_reg))
#define ISO_NORST_0_inst_adr                                                         "0x0090"
#define ISO_NORST_1_inst_adr                                                         "0x0091"
#define ISO_NORST_2_inst_adr                                                         "0x0092"
#define ISO_NORST_3_inst_adr                                                         "0x0093"
#define ISO_NORST_4_inst_adr                                                         "0x0094"
#define ISO_NORST_5_inst_adr                                                         "0x0095"
#define ISO_NORST_6_inst_adr                                                         "0x0096"
#define ISO_NORST_7_inst_adr                                                         "0x0097"
#define ISO_NORST_0_inst                                                             0x0090
#define ISO_NORST_1_inst                                                             0x0091
#define ISO_NORST_2_inst                                                             0x0092
#define ISO_NORST_3_inst                                                             0x0093
#define ISO_NORST_4_inst                                                             0x0094
#define ISO_NORST_5_inst                                                             0x0095
#define ISO_NORST_6_inst                                                             0x0096
#define ISO_NORST_7_inst                                                             0x0097
#define ISO_NORST_dat_shift                                                          (0)
#define ISO_NORST_dat_mask                                                           (0xFFFFFFFF)
#define ISO_NORST_dat(data)                                                          (0xFFFFFFFF&((data)<<0))
#define ISO_NORST_dat_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define ISO_NORST_get_dat(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST3                                                                0x18007660
#define ISO_COLD_RST3_reg_addr                                                       "0xB8007660"
#define ISO_COLD_RST3_reg                                                            0xB8007660
#define set_ISO_COLD_RST3_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST3_reg)=data)
#define get_ISO_COLD_RST3_reg   (*((volatile unsigned int*) ISO_COLD_RST3_reg))
#define ISO_COLD_RST3_inst_adr                                                       "0x0098"
#define ISO_COLD_RST3_inst                                                           0x0098
#define ISO_COLD_RST3_val_shift                                                      (0)
#define ISO_COLD_RST3_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST3_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST3_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST3_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST4                                                                0x18007664
#define ISO_COLD_RST4_reg_addr                                                       "0xB8007664"
#define ISO_COLD_RST4_reg                                                            0xB8007664
#define set_ISO_COLD_RST4_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST4_reg)=data)
#define get_ISO_COLD_RST4_reg   (*((volatile unsigned int*) ISO_COLD_RST4_reg))
#define ISO_COLD_RST4_inst_adr                                                       "0x0099"
#define ISO_COLD_RST4_inst                                                           0x0099
#define ISO_COLD_RST4_val_shift                                                      (0)
#define ISO_COLD_RST4_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST4_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST4_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST4_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST5                                                                0x18007668
#define ISO_COLD_RST5_reg_addr                                                       "0xB8007668"
#define ISO_COLD_RST5_reg                                                            0xB8007668
#define set_ISO_COLD_RST5_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST5_reg)=data)
#define get_ISO_COLD_RST5_reg   (*((volatile unsigned int*) ISO_COLD_RST5_reg))
#define ISO_COLD_RST5_inst_adr                                                       "0x009A"
#define ISO_COLD_RST5_inst                                                           0x009A
#define ISO_COLD_RST5_val_shift                                                      (0)
#define ISO_COLD_RST5_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST5_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST5_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST5_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST6                                                                0x1800766C
#define ISO_COLD_RST6_reg_addr                                                       "0xB800766C"
#define ISO_COLD_RST6_reg                                                            0xB800766C
#define set_ISO_COLD_RST6_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST6_reg)=data)
#define get_ISO_COLD_RST6_reg   (*((volatile unsigned int*) ISO_COLD_RST6_reg))
#define ISO_COLD_RST6_inst_adr                                                       "0x009B"
#define ISO_COLD_RST6_inst                                                           0x009B
#define ISO_COLD_RST6_val_shift                                                      (0)
#define ISO_COLD_RST6_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST6_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST6_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST6_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST7                                                                0x18007670
#define ISO_COLD_RST7_reg_addr                                                       "0xB8007670"
#define ISO_COLD_RST7_reg                                                            0xB8007670
#define set_ISO_COLD_RST7_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST7_reg)=data)
#define get_ISO_COLD_RST7_reg   (*((volatile unsigned int*) ISO_COLD_RST7_reg))
#define ISO_COLD_RST7_inst_adr                                                       "0x009C"
#define ISO_COLD_RST7_inst                                                           0x009C
#define ISO_COLD_RST7_val_shift                                                      (0)
#define ISO_COLD_RST7_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST7_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST7_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST7_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST8                                                                0x18007674
#define ISO_COLD_RST8_reg_addr                                                       "0xB8007674"
#define ISO_COLD_RST8_reg                                                            0xB8007674
#define set_ISO_COLD_RST8_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST8_reg)=data)
#define get_ISO_COLD_RST8_reg   (*((volatile unsigned int*) ISO_COLD_RST8_reg))
#define ISO_COLD_RST8_inst_adr                                                       "0x009D"
#define ISO_COLD_RST8_inst                                                           0x009D
#define ISO_COLD_RST8_val_shift                                                      (0)
#define ISO_COLD_RST8_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST8_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST8_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST8_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST9                                                                0x18007678
#define ISO_COLD_RST9_reg_addr                                                       "0xB8007678"
#define ISO_COLD_RST9_reg                                                            0xB8007678
#define set_ISO_COLD_RST9_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST9_reg)=data)
#define get_ISO_COLD_RST9_reg   (*((volatile unsigned int*) ISO_COLD_RST9_reg))
#define ISO_COLD_RST9_inst_adr                                                       "0x009E"
#define ISO_COLD_RST9_inst                                                           0x009E
#define ISO_COLD_RST9_val_shift                                                      (0)
#define ISO_COLD_RST9_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST9_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST9_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST9_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST10                                                               0x1800767C
#define ISO_COLD_RST10_reg_addr                                                      "0xB800767C"
#define ISO_COLD_RST10_reg                                                           0xB800767C
#define set_ISO_COLD_RST10_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST10_reg)=data)
#define get_ISO_COLD_RST10_reg   (*((volatile unsigned int*) ISO_COLD_RST10_reg))
#define ISO_COLD_RST10_inst_adr                                                      "0x009F"
#define ISO_COLD_RST10_inst                                                          0x009F
#define ISO_COLD_RST10_val_shift                                                     (0)
#define ISO_COLD_RST10_val_mask                                                      (0xFFFFFFFF)
#define ISO_COLD_RST10_val(data)                                                     (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST10_val_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST10_get_val(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define ISO_TCWCR                                                                    0x18007680
#define ISO_TCWCR_reg_addr                                                           "0xB8007680"
#define ISO_TCWCR_reg                                                                0xB8007680
#define set_ISO_TCWCR_reg(data)   (*((volatile unsigned int*) ISO_TCWCR_reg)=data)
#define get_ISO_TCWCR_reg   (*((volatile unsigned int*) ISO_TCWCR_reg))
#define ISO_TCWCR_inst_adr                                                           "0x00A0"
#define ISO_TCWCR_inst                                                               0x00A0
#define ISO_TCWCR_wd_int_en_shift                                                    (31)
#define ISO_TCWCR_wd_int_en_mask                                                     (0x80000000)
#define ISO_TCWCR_wd_int_en(data)                                                    (0x80000000&((data)<<31))
#define ISO_TCWCR_wd_int_en_src(data)                                                ((0x80000000&(data))>>31)
#define ISO_TCWCR_get_wd_int_en(data)                                                ((0x80000000&(data))>>31)
#define ISO_TCWCR_nmic_shift                                                         (12)
#define ISO_TCWCR_nmic_mask                                                          (0x0000F000)
#define ISO_TCWCR_nmic(data)                                                         (0x0000F000&((data)<<12))
#define ISO_TCWCR_nmic_src(data)                                                     ((0x0000F000&(data))>>12)
#define ISO_TCWCR_get_nmic(data)                                                     ((0x0000F000&(data))>>12)
#define ISO_TCWCR_wdc_shift                                                          (8)
#define ISO_TCWCR_wdc_mask                                                           (0x00000F00)
#define ISO_TCWCR_wdc(data)                                                          (0x00000F00&((data)<<8))
#define ISO_TCWCR_wdc_src(data)                                                      ((0x00000F00&(data))>>8)
#define ISO_TCWCR_get_wdc(data)                                                      ((0x00000F00&(data))>>8)
#define ISO_TCWCR_wden_shift                                                         (0)
#define ISO_TCWCR_wden_mask                                                          (0x000000FF)
#define ISO_TCWCR_wden(data)                                                         (0x000000FF&((data)<<0))
#define ISO_TCWCR_wden_src(data)                                                     ((0x000000FF&(data))>>0)
#define ISO_TCWCR_get_wden(data)                                                     ((0x000000FF&(data))>>0)


#define ISO_TCWTR                                                                    0x18007684
#define ISO_TCWTR_reg_addr                                                           "0xB8007684"
#define ISO_TCWTR_reg                                                                0xB8007684
#define set_ISO_TCWTR_reg(data)   (*((volatile unsigned int*) ISO_TCWTR_reg)=data)
#define get_ISO_TCWTR_reg   (*((volatile unsigned int*) ISO_TCWTR_reg))
#define ISO_TCWTR_inst_adr                                                           "0x00A1"
#define ISO_TCWTR_inst                                                               0x00A1
#define ISO_TCWTR_wdclr_shift                                                        (0)
#define ISO_TCWTR_wdclr_mask                                                         (0x00000001)
#define ISO_TCWTR_wdclr(data)                                                        (0x00000001&((data)<<0))
#define ISO_TCWTR_wdclr_src(data)                                                    ((0x00000001&(data))>>0)
#define ISO_TCWTR_get_wdclr(data)                                                    ((0x00000001&(data))>>0)


#define ISO_TCWNMI                                                                   0x18007688
#define ISO_TCWNMI_reg_addr                                                          "0xB8007688"
#define ISO_TCWNMI_reg                                                               0xB8007688
#define set_ISO_TCWNMI_reg(data)   (*((volatile unsigned int*) ISO_TCWNMI_reg)=data)
#define get_ISO_TCWNMI_reg   (*((volatile unsigned int*) ISO_TCWNMI_reg))
#define ISO_TCWNMI_inst_adr                                                          "0x00A2"
#define ISO_TCWNMI_inst                                                              0x00A2
#define ISO_TCWNMI_sel_shift                                                         (0)
#define ISO_TCWNMI_sel_mask                                                          (0xFFFFFFFF)
#define ISO_TCWNMI_sel(data)                                                         (0xFFFFFFFF&((data)<<0))
#define ISO_TCWNMI_sel_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define ISO_TCWNMI_get_sel(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define ISO_TCWOV                                                                    0x1800768C
#define ISO_TCWOV_reg_addr                                                           "0xB800768C"
#define ISO_TCWOV_reg                                                                0xB800768C
#define set_ISO_TCWOV_reg(data)   (*((volatile unsigned int*) ISO_TCWOV_reg)=data)
#define get_ISO_TCWOV_reg   (*((volatile unsigned int*) ISO_TCWOV_reg))
#define ISO_TCWOV_inst_adr                                                           "0x00A3"
#define ISO_TCWOV_inst                                                               0x00A3
#define ISO_TCWOV_sel_shift                                                          (0)
#define ISO_TCWOV_sel_mask                                                           (0xFFFFFFFF)
#define ISO_TCWOV_sel(data)                                                          (0xFFFFFFFF&((data)<<0))
#define ISO_TCWOV_sel_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define ISO_TCWOV_get_sel(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define ISO_DRM_ST_SWC                                                               0x18007690
#define ISO_DRM_ST_SWC_reg_addr                                                      "0xB8007690"
#define ISO_DRM_ST_SWC_reg                                                           0xB8007690
#define set_ISO_DRM_ST_SWC_reg(data)   (*((volatile unsigned int*) ISO_DRM_ST_SWC_reg)=data)
#define get_ISO_DRM_ST_SWC_reg   (*((volatile unsigned int*) ISO_DRM_ST_SWC_reg))
#define ISO_DRM_ST_SWC_inst_adr                                                      "0x00A4"
#define ISO_DRM_ST_SWC_inst                                                          0x00A4
#define ISO_DRM_ST_SWC_set_shift                                                     (0)
#define ISO_DRM_ST_SWC_set_mask                                                      (0x00000001)
#define ISO_DRM_ST_SWC_set(data)                                                     (0x00000001&((data)<<0))
#define ISO_DRM_ST_SWC_set_src(data)                                                 ((0x00000001&(data))>>0)
#define ISO_DRM_ST_SWC_get_set(data)                                                 ((0x00000001&(data))>>0)


#define ISO_DRM_SECURE_CLK_SWC                                                       0x18007694
#define ISO_DRM_SECURE_CLK_SWC_reg_addr                                              "0xB8007694"
#define ISO_DRM_SECURE_CLK_SWC_reg                                                   0xB8007694
#define set_ISO_DRM_SECURE_CLK_SWC_reg(data)   (*((volatile unsigned int*) ISO_DRM_SECURE_CLK_SWC_reg)=data)
#define get_ISO_DRM_SECURE_CLK_SWC_reg   (*((volatile unsigned int*) ISO_DRM_SECURE_CLK_SWC_reg))
#define ISO_DRM_SECURE_CLK_SWC_inst_adr                                              "0x00A5"
#define ISO_DRM_SECURE_CLK_SWC_inst                                                  0x00A5
#define ISO_DRM_SECURE_CLK_SWC_val_shift                                             (0)
#define ISO_DRM_SECURE_CLK_SWC_val_mask                                              (0xFFFFFFFF)
#define ISO_DRM_SECURE_CLK_SWC_val(data)                                             (0xFFFFFFFF&((data)<<0))
#define ISO_DRM_SECURE_CLK_SWC_val_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define ISO_DRM_SECURE_CLK_SWC_get_val(data)                                         ((0xFFFFFFFF&(data))>>0)


#define ISO_DRM_ELAPSED_SWC                                                          0x18007698
#define ISO_DRM_ELAPSED_SWC_reg_addr                                                 "0xB8007698"
#define ISO_DRM_ELAPSED_SWC_reg                                                      0xB8007698
#define set_ISO_DRM_ELAPSED_SWC_reg(data)   (*((volatile unsigned int*) ISO_DRM_ELAPSED_SWC_reg)=data)
#define get_ISO_DRM_ELAPSED_SWC_reg   (*((volatile unsigned int*) ISO_DRM_ELAPSED_SWC_reg))
#define ISO_DRM_ELAPSED_SWC_inst_adr                                                 "0x00A6"
#define ISO_DRM_ELAPSED_SWC_inst                                                     0x00A6
#define ISO_DRM_ELAPSED_SWC_val_shift                                                (0)
#define ISO_DRM_ELAPSED_SWC_val_mask                                                 (0xFFFFFFFF)
#define ISO_DRM_ELAPSED_SWC_val(data)                                                (0xFFFFFFFF&((data)<<0))
#define ISO_DRM_ELAPSED_SWC_val_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define ISO_DRM_ELAPSED_SWC_get_val(data)                                            ((0xFFFFFFFF&(data))>>0)


#define ISO_DRM_CTRL_SWC                                                             0x1800769C
#define ISO_DRM_CTRL_SWC_reg_addr                                                    "0xB800769C"
#define ISO_DRM_CTRL_SWC_reg                                                         0xB800769C
#define set_ISO_DRM_CTRL_SWC_reg(data)   (*((volatile unsigned int*) ISO_DRM_CTRL_SWC_reg)=data)
#define get_ISO_DRM_CTRL_SWC_reg   (*((volatile unsigned int*) ISO_DRM_CTRL_SWC_reg))
#define ISO_DRM_CTRL_SWC_inst_adr                                                    "0x00A7"
#define ISO_DRM_CTRL_SWC_inst                                                        0x00A7
#define ISO_DRM_CTRL_SWC_clk_div_en_shift                                            (1)
#define ISO_DRM_CTRL_SWC_clk_div_en_mask                                             (0x00000002)
#define ISO_DRM_CTRL_SWC_clk_div_en(data)                                            (0x00000002&((data)<<1))
#define ISO_DRM_CTRL_SWC_clk_div_en_src(data)                                        ((0x00000002&(data))>>1)
#define ISO_DRM_CTRL_SWC_get_clk_div_en(data)                                        ((0x00000002&(data))>>1)
#define ISO_DRM_CTRL_SWC_clk_sel_shift                                               (0)
#define ISO_DRM_CTRL_SWC_clk_sel_mask                                                (0x00000001)
#define ISO_DRM_CTRL_SWC_clk_sel(data)                                               (0x00000001&((data)<<0))
#define ISO_DRM_CTRL_SWC_clk_sel_src(data)                                           ((0x00000001&(data))>>0)
#define ISO_DRM_CTRL_SWC_get_clk_sel(data)                                           ((0x00000001&(data))>>0)


#define ISO_DRM_CLK_DIV_SWC                                                          0x180076A0
#define ISO_DRM_CLK_DIV_SWC_reg_addr                                                 "0xB80076A0"
#define ISO_DRM_CLK_DIV_SWC_reg                                                      0xB80076A0
#define set_ISO_DRM_CLK_DIV_SWC_reg(data)   (*((volatile unsigned int*) ISO_DRM_CLK_DIV_SWC_reg)=data)
#define get_ISO_DRM_CLK_DIV_SWC_reg   (*((volatile unsigned int*) ISO_DRM_CLK_DIV_SWC_reg))
#define ISO_DRM_CLK_DIV_SWC_inst_adr                                                 "0x00A8"
#define ISO_DRM_CLK_DIV_SWC_inst                                                     0x00A8
#define ISO_DRM_CLK_DIV_SWC_init_shift                                               (0)
#define ISO_DRM_CLK_DIV_SWC_init_mask                                                (0xFFFFFFFF)
#define ISO_DRM_CLK_DIV_SWC_init(data)                                               (0xFFFFFFFF&((data)<<0))
#define ISO_DRM_CLK_DIV_SWC_init_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define ISO_DRM_CLK_DIV_SWC_get_init(data)                                           ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST_SWC                                                             0x180076A4
#define ISO_COLD_RST_SWC_reg_addr                                                    "0xB80076A4"
#define ISO_COLD_RST_SWC_reg                                                         0xB80076A4
#define set_ISO_COLD_RST_SWC_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST_SWC_reg)=data)
#define get_ISO_COLD_RST_SWC_reg   (*((volatile unsigned int*) ISO_COLD_RST_SWC_reg))
#define ISO_COLD_RST_SWC_inst_adr                                                    "0x00A9"
#define ISO_COLD_RST_SWC_inst                                                        0x00A9
#define ISO_COLD_RST_SWC_val_shift                                                   (0)
#define ISO_COLD_RST_SWC_val_mask                                                    (0xFFFFFFFF)
#define ISO_COLD_RST_SWC_val(data)                                                   (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST_SWC_val_src(data)                                               ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST_SWC_get_val(data)                                               ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST1_SWC                                                            0x180076A8
#define ISO_COLD_RST1_SWC_reg_addr                                                   "0xB80076A8"
#define ISO_COLD_RST1_SWC_reg                                                        0xB80076A8
#define set_ISO_COLD_RST1_SWC_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST1_SWC_reg)=data)
#define get_ISO_COLD_RST1_SWC_reg   (*((volatile unsigned int*) ISO_COLD_RST1_SWC_reg))
#define ISO_COLD_RST1_SWC_inst_adr                                                   "0x00AA"
#define ISO_COLD_RST1_SWC_inst                                                       0x00AA
#define ISO_COLD_RST1_SWC_val_shift                                                  (0)
#define ISO_COLD_RST1_SWC_val_mask                                                   (0xFFFFFFFF)
#define ISO_COLD_RST1_SWC_val(data)                                                  (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST1_SWC_val_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST1_SWC_get_val(data)                                              ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST2_SWC                                                            0x180076AC
#define ISO_COLD_RST2_SWC_reg_addr                                                   "0xB80076AC"
#define ISO_COLD_RST2_SWC_reg                                                        0xB80076AC
#define set_ISO_COLD_RST2_SWC_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST2_SWC_reg)=data)
#define get_ISO_COLD_RST2_SWC_reg   (*((volatile unsigned int*) ISO_COLD_RST2_SWC_reg))
#define ISO_COLD_RST2_SWC_inst_adr                                                   "0x00AB"
#define ISO_COLD_RST2_SWC_inst                                                       0x00AB
#define ISO_COLD_RST2_SWC_val_shift                                                  (0)
#define ISO_COLD_RST2_SWC_val_mask                                                   (0xFFFFFFFF)
#define ISO_COLD_RST2_SWC_val(data)                                                  (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST2_SWC_val_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST2_SWC_get_val(data)                                              ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST3_SWC                                                            0x180076B0
#define ISO_COLD_RST3_SWC_reg_addr                                                   "0xB80076B0"
#define ISO_COLD_RST3_SWC_reg                                                        0xB80076B0
#define set_ISO_COLD_RST3_SWC_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST3_SWC_reg)=data)
#define get_ISO_COLD_RST3_SWC_reg   (*((volatile unsigned int*) ISO_COLD_RST3_SWC_reg))
#define ISO_COLD_RST3_SWC_inst_adr                                                   "0x00AC"
#define ISO_COLD_RST3_SWC_inst                                                       0x00AC
#define ISO_COLD_RST3_SWC_val_shift                                                  (0)
#define ISO_COLD_RST3_SWC_val_mask                                                   (0xFFFFFFFF)
#define ISO_COLD_RST3_SWC_val(data)                                                  (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST3_SWC_val_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST3_SWC_get_val(data)                                              ((0xFFFFFFFF&(data))>>0)


#define ISO_NORST_SWC                                                                0x180076B4
#define ISO_NORST_SWC_reg_addr                                                       "0xB80076B4"
#define ISO_NORST_SWC_reg                                                            0xB80076B4
#define set_ISO_NORST_SWC_reg(data)   (*((volatile unsigned int*) ISO_NORST_SWC_reg)=data)
#define get_ISO_NORST_SWC_reg   (*((volatile unsigned int*) ISO_NORST_SWC_reg))
#define ISO_NORST_SWC_inst_adr                                                       "0x00AD"
#define ISO_NORST_SWC_inst                                                           0x00AD
#define ISO_NORST_SWC_dat_shift                                                      (0)
#define ISO_NORST_SWC_dat_mask                                                       (0xFFFFFFFF)
#define ISO_NORST_SWC_dat(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_NORST_SWC_dat_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_NORST_SWC_get_dat(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_NORST1_SWC                                                               0x180076B8
#define ISO_NORST1_SWC_reg_addr                                                      "0xB80076B8"
#define ISO_NORST1_SWC_reg                                                           0xB80076B8
#define set_ISO_NORST1_SWC_reg(data)   (*((volatile unsigned int*) ISO_NORST1_SWC_reg)=data)
#define get_ISO_NORST1_SWC_reg   (*((volatile unsigned int*) ISO_NORST1_SWC_reg))
#define ISO_NORST1_SWC_inst_adr                                                      "0x00AE"
#define ISO_NORST1_SWC_inst                                                          0x00AE
#define ISO_NORST1_SWC_dat_shift                                                     (0)
#define ISO_NORST1_SWC_dat_mask                                                      (0xFFFFFFFF)
#define ISO_NORST1_SWC_dat(data)                                                     (0xFFFFFFFF&((data)<<0))
#define ISO_NORST1_SWC_dat_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define ISO_NORST1_SWC_get_dat(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define ISO_NORST2_SWC                                                               0x180076BC
#define ISO_NORST2_SWC_reg_addr                                                      "0xB80076BC"
#define ISO_NORST2_SWC_reg                                                           0xB80076BC
#define set_ISO_NORST2_SWC_reg(data)   (*((volatile unsigned int*) ISO_NORST2_SWC_reg)=data)
#define get_ISO_NORST2_SWC_reg   (*((volatile unsigned int*) ISO_NORST2_SWC_reg))
#define ISO_NORST2_SWC_inst_adr                                                      "0x00AF"
#define ISO_NORST2_SWC_inst                                                          0x00AF
#define ISO_NORST2_SWC_dat_shift                                                     (0)
#define ISO_NORST2_SWC_dat_mask                                                      (0xFFFFFFFF)
#define ISO_NORST2_SWC_dat(data)                                                     (0xFFFFFFFF&((data)<<0))
#define ISO_NORST2_SWC_dat_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define ISO_NORST2_SWC_get_dat(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define ISO_TCWOV_RSTB_CNT                                                           0x180076C0
#define ISO_TCWOV_RSTB_CNT_reg_addr                                                  "0xB80076C0"
#define ISO_TCWOV_RSTB_CNT_reg                                                       0xB80076C0
#define set_ISO_TCWOV_RSTB_CNT_reg(data)   (*((volatile unsigned int*) ISO_TCWOV_RSTB_CNT_reg)=data)
#define get_ISO_TCWOV_RSTB_CNT_reg   (*((volatile unsigned int*) ISO_TCWOV_RSTB_CNT_reg))
#define ISO_TCWOV_RSTB_CNT_inst_adr                                                  "0x00B0"
#define ISO_TCWOV_RSTB_CNT_inst                                                      0x00B0
#define ISO_TCWOV_RSTB_CNT_sel_shift                                                 (0)
#define ISO_TCWOV_RSTB_CNT_sel_mask                                                  (0xFFFFFFFF)
#define ISO_TCWOV_RSTB_CNT_sel(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ISO_TCWOV_RSTB_CNT_sel_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ISO_TCWOV_RSTB_CNT_get_sel(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ISO_CPU_ST2V                                                                 0x18007738
#define ISO_CPU_ST2V_reg_addr                                                        "0xB8007738"
#define ISO_CPU_ST2V_reg                                                             0xB8007738
#define set_ISO_CPU_ST2V_reg(data)   (*((volatile unsigned int*) ISO_CPU_ST2V_reg)=data)
#define get_ISO_CPU_ST2V_reg   (*((volatile unsigned int*) ISO_CPU_ST2V_reg))
#define ISO_CPU_ST2V_inst_adr                                                        "0x00CE"
#define ISO_CPU_ST2V_inst                                                            0x00CE
#define ISO_CPU_ST2V_scpu_boot_info_valid_shift                                      (0)
#define ISO_CPU_ST2V_scpu_boot_info_valid_mask                                       (0x00000001)
#define ISO_CPU_ST2V_scpu_boot_info_valid(data)                                      (0x00000001&((data)<<0))
#define ISO_CPU_ST2V_scpu_boot_info_valid_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_CPU_ST2V_get_scpu_boot_info_valid(data)                                  ((0x00000001&(data))>>0)


#define ISO_CPU_ST2                                                                  0x1800773C
#define ISO_CPU_ST2_reg_addr                                                         "0xB800773C"
#define ISO_CPU_ST2_reg                                                              0xB800773C
#define set_ISO_CPU_ST2_reg(data)   (*((volatile unsigned int*) ISO_CPU_ST2_reg)=data)
#define get_ISO_CPU_ST2_reg   (*((volatile unsigned int*) ISO_CPU_ST2_reg))
#define ISO_CPU_ST2_inst_adr                                                         "0x00CF"
#define ISO_CPU_ST2_inst                                                             0x00CF
#define ISO_CPU_ST2_scpu_boot_info_shift                                             (0)
#define ISO_CPU_ST2_scpu_boot_info_mask                                              (0xFFFFFFFF)
#define ISO_CPU_ST2_scpu_boot_info(data)                                             (0xFFFFFFFF&((data)<<0))
#define ISO_CPU_ST2_scpu_boot_info_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define ISO_CPU_ST2_get_scpu_boot_info(data)                                         ((0xFFFFFFFF&(data))>>0)


#define ISO_ACPU_DBG                                                                 0x18007740
#define ISO_ACPU_DBG_reg_addr                                                        "0xB8007740"
#define ISO_ACPU_DBG_reg                                                             0xB8007740
#define set_ISO_ACPU_DBG_reg(data)   (*((volatile unsigned int*) ISO_ACPU_DBG_reg)=data)
#define get_ISO_ACPU_DBG_reg   (*((volatile unsigned int*) ISO_ACPU_DBG_reg))
#define ISO_ACPU_DBG_inst_adr                                                        "0x00D0"
#define ISO_ACPU_DBG_inst                                                            0x00D0
#define ISO_ACPU_DBG_write_enable3_shift                                             (13)
#define ISO_ACPU_DBG_write_enable3_mask                                              (0x00002000)
#define ISO_ACPU_DBG_write_enable3(data)                                             (0x00002000&((data)<<13))
#define ISO_ACPU_DBG_write_enable3_src(data)                                         ((0x00002000&(data))>>13)
#define ISO_ACPU_DBG_get_write_enable3(data)                                         ((0x00002000&(data))>>13)
#define ISO_ACPU_DBG_sel1_shift                                                      (8)
#define ISO_ACPU_DBG_sel1_mask                                                       (0x00001F00)
#define ISO_ACPU_DBG_sel1(data)                                                      (0x00001F00&((data)<<8))
#define ISO_ACPU_DBG_sel1_src(data)                                                  ((0x00001F00&(data))>>8)
#define ISO_ACPU_DBG_get_sel1(data)                                                  ((0x00001F00&(data))>>8)
#define ISO_ACPU_DBG_write_enable2_shift                                             (7)
#define ISO_ACPU_DBG_write_enable2_mask                                              (0x00000080)
#define ISO_ACPU_DBG_write_enable2(data)                                             (0x00000080&((data)<<7))
#define ISO_ACPU_DBG_write_enable2_src(data)                                         ((0x00000080&(data))>>7)
#define ISO_ACPU_DBG_get_write_enable2(data)                                         ((0x00000080&(data))>>7)
#define ISO_ACPU_DBG_sel0_shift                                                      (2)
#define ISO_ACPU_DBG_sel0_mask                                                       (0x0000007C)
#define ISO_ACPU_DBG_sel0(data)                                                      (0x0000007C&((data)<<2))
#define ISO_ACPU_DBG_sel0_src(data)                                                  ((0x0000007C&(data))>>2)
#define ISO_ACPU_DBG_get_sel0(data)                                                  ((0x0000007C&(data))>>2)
#define ISO_ACPU_DBG_write_enable1_shift                                             (1)
#define ISO_ACPU_DBG_write_enable1_mask                                              (0x00000002)
#define ISO_ACPU_DBG_write_enable1(data)                                             (0x00000002&((data)<<1))
#define ISO_ACPU_DBG_write_enable1_src(data)                                         ((0x00000002&(data))>>1)
#define ISO_ACPU_DBG_get_write_enable1(data)                                         ((0x00000002&(data))>>1)
#define ISO_ACPU_DBG_enable_shift                                                    (0)
#define ISO_ACPU_DBG_enable_mask                                                     (0x00000001)
#define ISO_ACPU_DBG_enable(data)                                                    (0x00000001&((data)<<0))
#define ISO_ACPU_DBG_enable_src(data)                                                ((0x00000001&(data))>>0)
#define ISO_ACPU_DBG_get_enable(data)                                                ((0x00000001&(data))>>0)


#define ISO_ANLG                                                                     0x18007744
#define ISO_ANLG_reg_addr                                                            "0xB8007744"
#define ISO_ANLG_reg                                                                 0xB8007744
#define set_ISO_ANLG_reg(data)   (*((volatile unsigned int*) ISO_ANLG_reg)=data)
#define get_ISO_ANLG_reg   (*((volatile unsigned int*) ISO_ANLG_reg))
#define ISO_ANLG_inst_adr                                                            "0x00D1"
#define ISO_ANLG_inst                                                                0x00D1
#define ISO_ANLG_analogy_mode_in_shift                                               (0)
#define ISO_ANLG_analogy_mode_in_mask                                                (0x00000001)
#define ISO_ANLG_analogy_mode_in(data)                                               (0x00000001&((data)<<0))
#define ISO_ANLG_analogy_mode_in_src(data)                                           ((0x00000001&(data))>>0)
#define ISO_ANLG_get_analogy_mode_in(data)                                           ((0x00000001&(data))>>0)


#define ISO_U0RBR_THR_DLL                                                            0x18007800
#define ISO_U0RBR_THR_DLL_reg_addr                                                   "0xB8007800"
#define ISO_U0RBR_THR_DLL_reg                                                        0xB8007800
#define set_ISO_U0RBR_THR_DLL_reg(data)   (*((volatile unsigned int*) ISO_U0RBR_THR_DLL_reg)=data)
#define get_ISO_U0RBR_THR_DLL_reg   (*((volatile unsigned int*) ISO_U0RBR_THR_DLL_reg))
#define ISO_U0RBR_THR_DLL_inst_adr                                                   "0x0000"
#define ISO_U0RBR_THR_DLL_inst                                                       0x0000
#define ISO_U0RBR_THR_DLL_dll_shift                                                  (0)
#define ISO_U0RBR_THR_DLL_dll_mask                                                   (0x000000FF)
#define ISO_U0RBR_THR_DLL_dll(data)                                                  (0x000000FF&((data)<<0))
#define ISO_U0RBR_THR_DLL_dll_src(data)                                              ((0x000000FF&(data))>>0)
#define ISO_U0RBR_THR_DLL_get_dll(data)                                              ((0x000000FF&(data))>>0)


#define ISO_U0IER_DLH                                                                0x18007804
#define ISO_U0IER_DLH_reg_addr                                                       "0xB8007804"
#define ISO_U0IER_DLH_reg                                                            0xB8007804
#define set_ISO_U0IER_DLH_reg(data)   (*((volatile unsigned int*) ISO_U0IER_DLH_reg)=data)
#define get_ISO_U0IER_DLH_reg   (*((volatile unsigned int*) ISO_U0IER_DLH_reg))
#define ISO_U0IER_DLH_inst_adr                                                       "0x0001"
#define ISO_U0IER_DLH_inst                                                           0x0001
#define ISO_U0IER_DLH_dlh_shift                                                      (0)
#define ISO_U0IER_DLH_dlh_mask                                                       (0x000000FF)
#define ISO_U0IER_DLH_dlh(data)                                                      (0x000000FF&((data)<<0))
#define ISO_U0IER_DLH_dlh_src(data)                                                  ((0x000000FF&(data))>>0)
#define ISO_U0IER_DLH_get_dlh(data)                                                  ((0x000000FF&(data))>>0)


#define ISO_U0IIR_FCR                                                                0x18007808
#define ISO_U0IIR_FCR_reg_addr                                                       "0xB8007808"
#define ISO_U0IIR_FCR_reg                                                            0xB8007808
#define set_ISO_U0IIR_FCR_reg(data)   (*((volatile unsigned int*) ISO_U0IIR_FCR_reg)=data)
#define get_ISO_U0IIR_FCR_reg   (*((volatile unsigned int*) ISO_U0IIR_FCR_reg))
#define ISO_U0IIR_FCR_inst_adr                                                       "0x0002"
#define ISO_U0IIR_FCR_inst                                                           0x0002
#define ISO_U0IIR_FCR_fifo16_shift                                                   (6)
#define ISO_U0IIR_FCR_fifo16_mask                                                    (0x000000C0)
#define ISO_U0IIR_FCR_fifo16(data)                                                   (0x000000C0&((data)<<6))
#define ISO_U0IIR_FCR_fifo16_src(data)                                               ((0x000000C0&(data))>>6)
#define ISO_U0IIR_FCR_get_fifo16(data)                                               ((0x000000C0&(data))>>6)
#define ISO_U0IIR_FCR_iid_shift                                                      (0)
#define ISO_U0IIR_FCR_iid_mask                                                       (0x0000000F)
#define ISO_U0IIR_FCR_iid(data)                                                      (0x0000000F&((data)<<0))
#define ISO_U0IIR_FCR_iid_src(data)                                                  ((0x0000000F&(data))>>0)
#define ISO_U0IIR_FCR_get_iid(data)                                                  ((0x0000000F&(data))>>0)


#define ISO_U0LCR                                                                    0x1800780C
#define ISO_U0LCR_reg_addr                                                           "0xB800780C"
#define ISO_U0LCR_reg                                                                0xB800780C
#define set_ISO_U0LCR_reg(data)   (*((volatile unsigned int*) ISO_U0LCR_reg)=data)
#define get_ISO_U0LCR_reg   (*((volatile unsigned int*) ISO_U0LCR_reg))
#define ISO_U0LCR_inst_adr                                                           "0x0003"
#define ISO_U0LCR_inst                                                               0x0003
#define ISO_U0LCR_dlab_shift                                                         (7)
#define ISO_U0LCR_dlab_mask                                                          (0x00000080)
#define ISO_U0LCR_dlab(data)                                                         (0x00000080&((data)<<7))
#define ISO_U0LCR_dlab_src(data)                                                     ((0x00000080&(data))>>7)
#define ISO_U0LCR_get_dlab(data)                                                     ((0x00000080&(data))>>7)
#define ISO_U0LCR_brk_shift                                                          (6)
#define ISO_U0LCR_brk_mask                                                           (0x00000040)
#define ISO_U0LCR_brk(data)                                                          (0x00000040&((data)<<6))
#define ISO_U0LCR_brk_src(data)                                                      ((0x00000040&(data))>>6)
#define ISO_U0LCR_get_brk(data)                                                      ((0x00000040&(data))>>6)
#define ISO_U0LCR_eps_shift                                                          (4)
#define ISO_U0LCR_eps_mask                                                           (0x00000010)
#define ISO_U0LCR_eps(data)                                                          (0x00000010&((data)<<4))
#define ISO_U0LCR_eps_src(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U0LCR_get_eps(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U0LCR_pen_shift                                                          (3)
#define ISO_U0LCR_pen_mask                                                           (0x00000008)
#define ISO_U0LCR_pen(data)                                                          (0x00000008&((data)<<3))
#define ISO_U0LCR_pen_src(data)                                                      ((0x00000008&(data))>>3)
#define ISO_U0LCR_get_pen(data)                                                      ((0x00000008&(data))>>3)
#define ISO_U0LCR_stb_shift                                                          (2)
#define ISO_U0LCR_stb_mask                                                           (0x00000004)
#define ISO_U0LCR_stb(data)                                                          (0x00000004&((data)<<2))
#define ISO_U0LCR_stb_src(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U0LCR_get_stb(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U0LCR_wls_shift                                                          (0)
#define ISO_U0LCR_wls_mask                                                           (0x00000003)
#define ISO_U0LCR_wls(data)                                                          (0x00000003&((data)<<0))
#define ISO_U0LCR_wls_src(data)                                                      ((0x00000003&(data))>>0)
#define ISO_U0LCR_get_wls(data)                                                      ((0x00000003&(data))>>0)


#define ISO_U0MCR                                                                    0x18007810
#define ISO_U0MCR_reg_addr                                                           "0xB8007810"
#define ISO_U0MCR_reg                                                                0xB8007810
#define set_ISO_U0MCR_reg(data)   (*((volatile unsigned int*) ISO_U0MCR_reg)=data)
#define get_ISO_U0MCR_reg   (*((volatile unsigned int*) ISO_U0MCR_reg))
#define ISO_U0MCR_inst_adr                                                           "0x0004"
#define ISO_U0MCR_inst                                                               0x0004
#define ISO_U0MCR_afce_shift                                                         (5)
#define ISO_U0MCR_afce_mask                                                          (0x00000020)
#define ISO_U0MCR_afce(data)                                                         (0x00000020&((data)<<5))
#define ISO_U0MCR_afce_src(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U0MCR_get_afce(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U0MCR_loop_shift                                                         (4)
#define ISO_U0MCR_loop_mask                                                          (0x00000010)
#define ISO_U0MCR_loop(data)                                                         (0x00000010&((data)<<4))
#define ISO_U0MCR_loop_src(data)                                                     ((0x00000010&(data))>>4)
#define ISO_U0MCR_get_loop(data)                                                     ((0x00000010&(data))>>4)
#define ISO_U0MCR_rts_shift                                                          (1)
#define ISO_U0MCR_rts_mask                                                           (0x00000002)
#define ISO_U0MCR_rts(data)                                                          (0x00000002&((data)<<1))
#define ISO_U0MCR_rts_src(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U0MCR_get_rts(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U0MCR_dtr_shift                                                          (0)
#define ISO_U0MCR_dtr_mask                                                           (0x00000001)
#define ISO_U0MCR_dtr(data)                                                          (0x00000001&((data)<<0))
#define ISO_U0MCR_dtr_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U0MCR_get_dtr(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U0LSR                                                                    0x18007814
#define ISO_U0LSR_reg_addr                                                           "0xB8007814"
#define ISO_U0LSR_reg                                                                0xB8007814
#define set_ISO_U0LSR_reg(data)   (*((volatile unsigned int*) ISO_U0LSR_reg)=data)
#define get_ISO_U0LSR_reg   (*((volatile unsigned int*) ISO_U0LSR_reg))
#define ISO_U0LSR_inst_adr                                                           "0x0005"
#define ISO_U0LSR_inst                                                               0x0005
#define ISO_U0LSR_rfe_shift                                                          (7)
#define ISO_U0LSR_rfe_mask                                                           (0x00000080)
#define ISO_U0LSR_rfe(data)                                                          (0x00000080&((data)<<7))
#define ISO_U0LSR_rfe_src(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U0LSR_get_rfe(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U0LSR_temt_shift                                                         (6)
#define ISO_U0LSR_temt_mask                                                          (0x00000040)
#define ISO_U0LSR_temt(data)                                                         (0x00000040&((data)<<6))
#define ISO_U0LSR_temt_src(data)                                                     ((0x00000040&(data))>>6)
#define ISO_U0LSR_get_temt(data)                                                     ((0x00000040&(data))>>6)
#define ISO_U0LSR_thre_shift                                                         (5)
#define ISO_U0LSR_thre_mask                                                          (0x00000020)
#define ISO_U0LSR_thre(data)                                                         (0x00000020&((data)<<5))
#define ISO_U0LSR_thre_src(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U0LSR_get_thre(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U0LSR_bi_shift                                                           (4)
#define ISO_U0LSR_bi_mask                                                            (0x00000010)
#define ISO_U0LSR_bi(data)                                                           (0x00000010&((data)<<4))
#define ISO_U0LSR_bi_src(data)                                                       ((0x00000010&(data))>>4)
#define ISO_U0LSR_get_bi(data)                                                       ((0x00000010&(data))>>4)
#define ISO_U0LSR_fe_shift                                                           (3)
#define ISO_U0LSR_fe_mask                                                            (0x00000008)
#define ISO_U0LSR_fe(data)                                                           (0x00000008&((data)<<3))
#define ISO_U0LSR_fe_src(data)                                                       ((0x00000008&(data))>>3)
#define ISO_U0LSR_get_fe(data)                                                       ((0x00000008&(data))>>3)
#define ISO_U0LSR_pe_shift                                                           (2)
#define ISO_U0LSR_pe_mask                                                            (0x00000004)
#define ISO_U0LSR_pe(data)                                                           (0x00000004&((data)<<2))
#define ISO_U0LSR_pe_src(data)                                                       ((0x00000004&(data))>>2)
#define ISO_U0LSR_get_pe(data)                                                       ((0x00000004&(data))>>2)
#define ISO_U0LSR_oe_shift                                                           (1)
#define ISO_U0LSR_oe_mask                                                            (0x00000002)
#define ISO_U0LSR_oe(data)                                                           (0x00000002&((data)<<1))
#define ISO_U0LSR_oe_src(data)                                                       ((0x00000002&(data))>>1)
#define ISO_U0LSR_get_oe(data)                                                       ((0x00000002&(data))>>1)
#define ISO_U0LSR_dr_shift                                                           (0)
#define ISO_U0LSR_dr_mask                                                            (0x00000001)
#define ISO_U0LSR_dr(data)                                                           (0x00000001&((data)<<0))
#define ISO_U0LSR_dr_src(data)                                                       ((0x00000001&(data))>>0)
#define ISO_U0LSR_get_dr(data)                                                       ((0x00000001&(data))>>0)


#define ISO_U0MSR                                                                    0x18007818
#define ISO_U0MSR_reg_addr                                                           "0xB8007818"
#define ISO_U0MSR_reg                                                                0xB8007818
#define set_ISO_U0MSR_reg(data)   (*((volatile unsigned int*) ISO_U0MSR_reg)=data)
#define get_ISO_U0MSR_reg   (*((volatile unsigned int*) ISO_U0MSR_reg))
#define ISO_U0MSR_inst_adr                                                           "0x0006"
#define ISO_U0MSR_inst                                                               0x0006
#define ISO_U0MSR_dcd_shift                                                          (7)
#define ISO_U0MSR_dcd_mask                                                           (0x00000080)
#define ISO_U0MSR_dcd(data)                                                          (0x00000080&((data)<<7))
#define ISO_U0MSR_dcd_src(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U0MSR_get_dcd(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U0MSR_ri_shift                                                           (6)
#define ISO_U0MSR_ri_mask                                                            (0x00000040)
#define ISO_U0MSR_ri(data)                                                           (0x00000040&((data)<<6))
#define ISO_U0MSR_ri_src(data)                                                       ((0x00000040&(data))>>6)
#define ISO_U0MSR_get_ri(data)                                                       ((0x00000040&(data))>>6)
#define ISO_U0MSR_dsr_shift                                                          (5)
#define ISO_U0MSR_dsr_mask                                                           (0x00000020)
#define ISO_U0MSR_dsr(data)                                                          (0x00000020&((data)<<5))
#define ISO_U0MSR_dsr_src(data)                                                      ((0x00000020&(data))>>5)
#define ISO_U0MSR_get_dsr(data)                                                      ((0x00000020&(data))>>5)
#define ISO_U0MSR_cts_shift                                                          (4)
#define ISO_U0MSR_cts_mask                                                           (0x00000010)
#define ISO_U0MSR_cts(data)                                                          (0x00000010&((data)<<4))
#define ISO_U0MSR_cts_src(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U0MSR_get_cts(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U0MSR_ddcd_shift                                                         (3)
#define ISO_U0MSR_ddcd_mask                                                          (0x00000008)
#define ISO_U0MSR_ddcd(data)                                                         (0x00000008&((data)<<3))
#define ISO_U0MSR_ddcd_src(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U0MSR_get_ddcd(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U0MSR_teri_shift                                                         (2)
#define ISO_U0MSR_teri_mask                                                          (0x00000004)
#define ISO_U0MSR_teri(data)                                                         (0x00000004&((data)<<2))
#define ISO_U0MSR_teri_src(data)                                                     ((0x00000004&(data))>>2)
#define ISO_U0MSR_get_teri(data)                                                     ((0x00000004&(data))>>2)
#define ISO_U0MSR_ddsr_shift                                                         (1)
#define ISO_U0MSR_ddsr_mask                                                          (0x00000002)
#define ISO_U0MSR_ddsr(data)                                                         (0x00000002&((data)<<1))
#define ISO_U0MSR_ddsr_src(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U0MSR_get_ddsr(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U0MSR_dcts_shift                                                         (0)
#define ISO_U0MSR_dcts_mask                                                          (0x00000001)
#define ISO_U0MSR_dcts(data)                                                         (0x00000001&((data)<<0))
#define ISO_U0MSR_dcts_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_U0MSR_get_dcts(data)                                                     ((0x00000001&(data))>>0)


#define ISO_U0SCR                                                                    0x1800781C
#define ISO_U0SCR_reg_addr                                                           "0xB800781C"
#define ISO_U0SCR_reg                                                                0xB800781C
#define set_ISO_U0SCR_reg(data)   (*((volatile unsigned int*) ISO_U0SCR_reg)=data)
#define get_ISO_U0SCR_reg   (*((volatile unsigned int*) ISO_U0SCR_reg))
#define ISO_U0SCR_inst_adr                                                           "0x0007"
#define ISO_U0SCR_inst                                                               0x0007
#define ISO_U0SCR_scr_shift                                                          (0)
#define ISO_U0SCR_scr_mask                                                           (0x000000FF)
#define ISO_U0SCR_scr(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U0SCR_scr_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U0SCR_get_scr(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U0SRBR_0                                                                 0x18007830
#define ISO_U0SRBR_1                                                                 0x18007834
#define ISO_U0SRBR_2                                                                 0x18007838
#define ISO_U0SRBR_3                                                                 0x1800783C
#define ISO_U0SRBR_4                                                                 0x18007840
#define ISO_U0SRBR_5                                                                 0x18007844
#define ISO_U0SRBR_6                                                                 0x18007848
#define ISO_U0SRBR_7                                                                 0x1800784C
#define ISO_U0SRBR_8                                                                 0x18007850
#define ISO_U0SRBR_9                                                                 0x18007854
#define ISO_U0SRBR_10                                                                 0x18007858
#define ISO_U0SRBR_11                                                                 0x1800785C
#define ISO_U0SRBR_12                                                                 0x18007860
#define ISO_U0SRBR_13                                                                 0x18007864
#define ISO_U0SRBR_14                                                                 0x18007868
#define ISO_U0SRBR_15                                                                 0x1800786C
#define ISO_U0SRBR_0_reg_addr                                                        "0xB8007830"
#define ISO_U0SRBR_1_reg_addr                                                        "0xB8007834"
#define ISO_U0SRBR_2_reg_addr                                                        "0xB8007838"
#define ISO_U0SRBR_3_reg_addr                                                        "0xB800783C"
#define ISO_U0SRBR_4_reg_addr                                                        "0xB8007840"
#define ISO_U0SRBR_5_reg_addr                                                        "0xB8007844"
#define ISO_U0SRBR_6_reg_addr                                                        "0xB8007848"
#define ISO_U0SRBR_7_reg_addr                                                        "0xB800784C"
#define ISO_U0SRBR_8_reg_addr                                                        "0xB8007850"
#define ISO_U0SRBR_9_reg_addr                                                        "0xB8007854"
#define ISO_U0SRBR_10_reg_addr                                                        "0xB8007858"
#define ISO_U0SRBR_11_reg_addr                                                        "0xB800785C"
#define ISO_U0SRBR_12_reg_addr                                                        "0xB8007860"
#define ISO_U0SRBR_13_reg_addr                                                        "0xB8007864"
#define ISO_U0SRBR_14_reg_addr                                                        "0xB8007868"
#define ISO_U0SRBR_15_reg_addr                                                        "0xB800786C"
#define ISO_U0SRBR_0_reg                                                             0xB8007830
#define ISO_U0SRBR_1_reg                                                             0xB8007834
#define ISO_U0SRBR_2_reg                                                             0xB8007838
#define ISO_U0SRBR_3_reg                                                             0xB800783C
#define ISO_U0SRBR_4_reg                                                             0xB8007840
#define ISO_U0SRBR_5_reg                                                             0xB8007844
#define ISO_U0SRBR_6_reg                                                             0xB8007848
#define ISO_U0SRBR_7_reg                                                             0xB800784C
#define ISO_U0SRBR_8_reg                                                             0xB8007850
#define ISO_U0SRBR_9_reg                                                             0xB8007854
#define ISO_U0SRBR_10_reg                                                             0xB8007858
#define ISO_U0SRBR_11_reg                                                             0xB800785C
#define ISO_U0SRBR_12_reg                                                             0xB8007860
#define ISO_U0SRBR_13_reg                                                             0xB8007864
#define ISO_U0SRBR_14_reg                                                             0xB8007868
#define ISO_U0SRBR_15_reg                                                             0xB800786C
#define set_ISO_U0SRBR_0_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_0_reg)=data)
#define set_ISO_U0SRBR_1_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_1_reg)=data)
#define set_ISO_U0SRBR_2_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_2_reg)=data)
#define set_ISO_U0SRBR_3_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_3_reg)=data)
#define set_ISO_U0SRBR_4_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_4_reg)=data)
#define set_ISO_U0SRBR_5_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_5_reg)=data)
#define set_ISO_U0SRBR_6_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_6_reg)=data)
#define set_ISO_U0SRBR_7_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_7_reg)=data)
#define set_ISO_U0SRBR_8_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_8_reg)=data)
#define set_ISO_U0SRBR_9_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_9_reg)=data)
#define set_ISO_U0SRBR_10_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_10_reg)=data)
#define set_ISO_U0SRBR_11_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_11_reg)=data)
#define set_ISO_U0SRBR_12_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_12_reg)=data)
#define set_ISO_U0SRBR_13_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_13_reg)=data)
#define set_ISO_U0SRBR_14_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_14_reg)=data)
#define set_ISO_U0SRBR_15_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_15_reg)=data)
#define get_ISO_U0SRBR_0_reg   (*((volatile unsigned int*) ISO_U0SRBR_0_reg))
#define get_ISO_U0SRBR_1_reg   (*((volatile unsigned int*) ISO_U0SRBR_1_reg))
#define get_ISO_U0SRBR_2_reg   (*((volatile unsigned int*) ISO_U0SRBR_2_reg))
#define get_ISO_U0SRBR_3_reg   (*((volatile unsigned int*) ISO_U0SRBR_3_reg))
#define get_ISO_U0SRBR_4_reg   (*((volatile unsigned int*) ISO_U0SRBR_4_reg))
#define get_ISO_U0SRBR_5_reg   (*((volatile unsigned int*) ISO_U0SRBR_5_reg))
#define get_ISO_U0SRBR_6_reg   (*((volatile unsigned int*) ISO_U0SRBR_6_reg))
#define get_ISO_U0SRBR_7_reg   (*((volatile unsigned int*) ISO_U0SRBR_7_reg))
#define get_ISO_U0SRBR_8_reg   (*((volatile unsigned int*) ISO_U0SRBR_8_reg))
#define get_ISO_U0SRBR_9_reg   (*((volatile unsigned int*) ISO_U0SRBR_9_reg))
#define get_ISO_U0SRBR_10_reg   (*((volatile unsigned int*) ISO_U0SRBR_10_reg))
#define get_ISO_U0SRBR_11_reg   (*((volatile unsigned int*) ISO_U0SRBR_11_reg))
#define get_ISO_U0SRBR_12_reg   (*((volatile unsigned int*) ISO_U0SRBR_12_reg))
#define get_ISO_U0SRBR_13_reg   (*((volatile unsigned int*) ISO_U0SRBR_13_reg))
#define get_ISO_U0SRBR_14_reg   (*((volatile unsigned int*) ISO_U0SRBR_14_reg))
#define get_ISO_U0SRBR_15_reg   (*((volatile unsigned int*) ISO_U0SRBR_15_reg))
#define ISO_U0SRBR_0_inst_adr                                                        "0x000C"
#define ISO_U0SRBR_1_inst_adr                                                        "0x000D"
#define ISO_U0SRBR_2_inst_adr                                                        "0x000E"
#define ISO_U0SRBR_3_inst_adr                                                        "0x000F"
#define ISO_U0SRBR_4_inst_adr                                                        "0x0010"
#define ISO_U0SRBR_5_inst_adr                                                        "0x0011"
#define ISO_U0SRBR_6_inst_adr                                                        "0x0012"
#define ISO_U0SRBR_7_inst_adr                                                        "0x0013"
#define ISO_U0SRBR_8_inst_adr                                                        "0x0014"
#define ISO_U0SRBR_9_inst_adr                                                        "0x0015"
#define ISO_U0SRBR_10_inst_adr                                                        "0x0016"
#define ISO_U0SRBR_11_inst_adr                                                        "0x0017"
#define ISO_U0SRBR_12_inst_adr                                                        "0x0018"
#define ISO_U0SRBR_13_inst_adr                                                        "0x0019"
#define ISO_U0SRBR_14_inst_adr                                                        "0x001A"
#define ISO_U0SRBR_15_inst_adr                                                        "0x001B"
#define ISO_U0SRBR_0_inst                                                            0x000C
#define ISO_U0SRBR_1_inst                                                            0x000D
#define ISO_U0SRBR_2_inst                                                            0x000E
#define ISO_U0SRBR_3_inst                                                            0x000F
#define ISO_U0SRBR_4_inst                                                            0x0010
#define ISO_U0SRBR_5_inst                                                            0x0011
#define ISO_U0SRBR_6_inst                                                            0x0012
#define ISO_U0SRBR_7_inst                                                            0x0013
#define ISO_U0SRBR_8_inst                                                            0x0014
#define ISO_U0SRBR_9_inst                                                            0x0015
#define ISO_U0SRBR_10_inst                                                            0x0016
#define ISO_U0SRBR_11_inst                                                            0x0017
#define ISO_U0SRBR_12_inst                                                            0x0018
#define ISO_U0SRBR_13_inst                                                            0x0019
#define ISO_U0SRBR_14_inst                                                            0x001A
#define ISO_U0SRBR_15_inst                                                            0x001B
#define ISO_U0SRBR_rbd_shift                                                         (0)
#define ISO_U0SRBR_rbd_mask                                                          (0x000000FF)
#define ISO_U0SRBR_rbd(data)                                                         (0x000000FF&((data)<<0))
#define ISO_U0SRBR_rbd_src(data)                                                     ((0x000000FF&(data))>>0)
#define ISO_U0SRBR_get_rbd(data)                                                     ((0x000000FF&(data))>>0)


#define ISO_U0FAR                                                                    0x18007870
#define ISO_U0FAR_reg_addr                                                           "0xB8007870"
#define ISO_U0FAR_reg                                                                0xB8007870
#define set_ISO_U0FAR_reg(data)   (*((volatile unsigned int*) ISO_U0FAR_reg)=data)
#define get_ISO_U0FAR_reg   (*((volatile unsigned int*) ISO_U0FAR_reg))
#define ISO_U0FAR_inst_adr                                                           "0x001C"
#define ISO_U0FAR_inst                                                               0x001C
#define ISO_U0FAR_far_shift                                                          (0)
#define ISO_U0FAR_far_mask                                                           (0x00000001)
#define ISO_U0FAR_far(data)                                                          (0x00000001&((data)<<0))
#define ISO_U0FAR_far_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U0FAR_get_far(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U0TFR                                                                    0x18007874
#define ISO_U0TFR_reg_addr                                                           "0xB8007874"
#define ISO_U0TFR_reg                                                                0xB8007874
#define set_ISO_U0TFR_reg(data)   (*((volatile unsigned int*) ISO_U0TFR_reg)=data)
#define get_ISO_U0TFR_reg   (*((volatile unsigned int*) ISO_U0TFR_reg))
#define ISO_U0TFR_inst_adr                                                           "0x001D"
#define ISO_U0TFR_inst                                                               0x001D
#define ISO_U0TFR_far_shift                                                          (0)
#define ISO_U0TFR_far_mask                                                           (0x000000FF)
#define ISO_U0TFR_far(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U0TFR_far_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U0TFR_get_far(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U0RFW                                                                    0x18007878
#define ISO_U0RFW_reg_addr                                                           "0xB8007878"
#define ISO_U0RFW_reg                                                                0xB8007878
#define set_ISO_U0RFW_reg(data)   (*((volatile unsigned int*) ISO_U0RFW_reg)=data)
#define get_ISO_U0RFW_reg   (*((volatile unsigned int*) ISO_U0RFW_reg))
#define ISO_U0RFW_inst_adr                                                           "0x001E"
#define ISO_U0RFW_inst                                                               0x001E
#define ISO_U0RFW_rffe_shift                                                         (9)
#define ISO_U0RFW_rffe_mask                                                          (0x00000200)
#define ISO_U0RFW_rffe(data)                                                         (0x00000200&((data)<<9))
#define ISO_U0RFW_rffe_src(data)                                                     ((0x00000200&(data))>>9)
#define ISO_U0RFW_get_rffe(data)                                                     ((0x00000200&(data))>>9)
#define ISO_U0RFW_rfpf_shift                                                         (8)
#define ISO_U0RFW_rfpf_mask                                                          (0x00000100)
#define ISO_U0RFW_rfpf(data)                                                         (0x00000100&((data)<<8))
#define ISO_U0RFW_rfpf_src(data)                                                     ((0x00000100&(data))>>8)
#define ISO_U0RFW_get_rfpf(data)                                                     ((0x00000100&(data))>>8)
#define ISO_U0RFW_rfwd_shift                                                         (0)
#define ISO_U0RFW_rfwd_mask                                                          (0x000000FF)
#define ISO_U0RFW_rfwd(data)                                                         (0x000000FF&((data)<<0))
#define ISO_U0RFW_rfwd_src(data)                                                     ((0x000000FF&(data))>>0)
#define ISO_U0RFW_get_rfwd(data)                                                     ((0x000000FF&(data))>>0)


#define ISO_U0USR                                                                    0x1800787C
#define ISO_U0USR_reg_addr                                                           "0xB800787C"
#define ISO_U0USR_reg                                                                0xB800787C
#define set_ISO_U0USR_reg(data)   (*((volatile unsigned int*) ISO_U0USR_reg)=data)
#define get_ISO_U0USR_reg   (*((volatile unsigned int*) ISO_U0USR_reg))
#define ISO_U0USR_inst_adr                                                           "0x001F"
#define ISO_U0USR_inst                                                               0x001F
#define ISO_U0USR_rff_shift                                                          (4)
#define ISO_U0USR_rff_mask                                                           (0x00000010)
#define ISO_U0USR_rff(data)                                                          (0x00000010&((data)<<4))
#define ISO_U0USR_rff_src(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U0USR_get_rff(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U0USR_rfne_shift                                                         (3)
#define ISO_U0USR_rfne_mask                                                          (0x00000008)
#define ISO_U0USR_rfne(data)                                                         (0x00000008&((data)<<3))
#define ISO_U0USR_rfne_src(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U0USR_get_rfne(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U0USR_tfe_shift                                                          (2)
#define ISO_U0USR_tfe_mask                                                           (0x00000004)
#define ISO_U0USR_tfe(data)                                                          (0x00000004&((data)<<2))
#define ISO_U0USR_tfe_src(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U0USR_get_tfe(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U0USR_tfnf_shift                                                         (1)
#define ISO_U0USR_tfnf_mask                                                          (0x00000002)
#define ISO_U0USR_tfnf(data)                                                         (0x00000002&((data)<<1))
#define ISO_U0USR_tfnf_src(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U0USR_get_tfnf(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U0USR_busy_shift                                                         (0)
#define ISO_U0USR_busy_mask                                                          (0x00000001)
#define ISO_U0USR_busy(data)                                                         (0x00000001&((data)<<0))
#define ISO_U0USR_busy_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_U0USR_get_busy(data)                                                     ((0x00000001&(data))>>0)


#define ISO_U0TFL                                                                    0x18007880
#define ISO_U0TFL_reg_addr                                                           "0xB8007880"
#define ISO_U0TFL_reg                                                                0xB8007880
#define set_ISO_U0TFL_reg(data)   (*((volatile unsigned int*) ISO_U0TFL_reg)=data)
#define get_ISO_U0TFL_reg   (*((volatile unsigned int*) ISO_U0TFL_reg))
#define ISO_U0TFL_inst_adr                                                           "0x0020"
#define ISO_U0TFL_inst                                                               0x0020
#define ISO_U0TFL_tfl_shift                                                          (0)
#define ISO_U0TFL_tfl_mask                                                           (0x000000FF)
#define ISO_U0TFL_tfl(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U0TFL_tfl_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U0TFL_get_tfl(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U0RFL                                                                    0x18007884
#define ISO_U0RFL_reg_addr                                                           "0xB8007884"
#define ISO_U0RFL_reg                                                                0xB8007884
#define set_ISO_U0RFL_reg(data)   (*((volatile unsigned int*) ISO_U0RFL_reg)=data)
#define get_ISO_U0RFL_reg   (*((volatile unsigned int*) ISO_U0RFL_reg))
#define ISO_U0RFL_inst_adr                                                           "0x0021"
#define ISO_U0RFL_inst                                                               0x0021
#define ISO_U0RFL_rfl_shift                                                          (0)
#define ISO_U0RFL_rfl_mask                                                           (0x000000FF)
#define ISO_U0RFL_rfl(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U0RFL_rfl_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U0RFL_get_rfl(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U0SRR                                                                    0x18007888
#define ISO_U0SRR_reg_addr                                                           "0xB8007888"
#define ISO_U0SRR_reg                                                                0xB8007888
#define set_ISO_U0SRR_reg(data)   (*((volatile unsigned int*) ISO_U0SRR_reg)=data)
#define get_ISO_U0SRR_reg   (*((volatile unsigned int*) ISO_U0SRR_reg))
#define ISO_U0SRR_inst_adr                                                           "0x0022"
#define ISO_U0SRR_inst                                                               0x0022
#define ISO_U0SRR_xfr_shift                                                          (2)
#define ISO_U0SRR_xfr_mask                                                           (0x00000004)
#define ISO_U0SRR_xfr(data)                                                          (0x00000004&((data)<<2))
#define ISO_U0SRR_xfr_src(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U0SRR_get_xfr(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U0SRR_rfr_shift                                                          (1)
#define ISO_U0SRR_rfr_mask                                                           (0x00000002)
#define ISO_U0SRR_rfr(data)                                                          (0x00000002&((data)<<1))
#define ISO_U0SRR_rfr_src(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U0SRR_get_rfr(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U0SRR_ur_shift                                                           (0)
#define ISO_U0SRR_ur_mask                                                            (0x00000001)
#define ISO_U0SRR_ur(data)                                                           (0x00000001&((data)<<0))
#define ISO_U0SRR_ur_src(data)                                                       ((0x00000001&(data))>>0)
#define ISO_U0SRR_get_ur(data)                                                       ((0x00000001&(data))>>0)


#define ISO_U0SBCR                                                                   0x18007890
#define ISO_U0SBCR_reg_addr                                                          "0xB8007890"
#define ISO_U0SBCR_reg                                                               0xB8007890
#define set_ISO_U0SBCR_reg(data)   (*((volatile unsigned int*) ISO_U0SBCR_reg)=data)
#define get_ISO_U0SBCR_reg   (*((volatile unsigned int*) ISO_U0SBCR_reg))
#define ISO_U0SBCR_inst_adr                                                          "0x0024"
#define ISO_U0SBCR_inst                                                              0x0024
#define ISO_U0SBCR_sbcr_shift                                                        (0)
#define ISO_U0SBCR_sbcr_mask                                                         (0x00000001)
#define ISO_U0SBCR_sbcr(data)                                                        (0x00000001&((data)<<0))
#define ISO_U0SBCR_sbcr_src(data)                                                    ((0x00000001&(data))>>0)
#define ISO_U0SBCR_get_sbcr(data)                                                    ((0x00000001&(data))>>0)


#define ISO_U0SDMAM                                                                  0x18007894
#define ISO_U0SDMAM_reg_addr                                                         "0xB8007894"
#define ISO_U0SDMAM_reg                                                              0xB8007894
#define set_ISO_U0SDMAM_reg(data)   (*((volatile unsigned int*) ISO_U0SDMAM_reg)=data)
#define get_ISO_U0SDMAM_reg   (*((volatile unsigned int*) ISO_U0SDMAM_reg))
#define ISO_U0SDMAM_inst_adr                                                         "0x0025"
#define ISO_U0SDMAM_inst                                                             0x0025
#define ISO_U0SDMAM_sdmam_shift                                                      (0)
#define ISO_U0SDMAM_sdmam_mask                                                       (0x00000001)
#define ISO_U0SDMAM_sdmam(data)                                                      (0x00000001&((data)<<0))
#define ISO_U0SDMAM_sdmam_src(data)                                                  ((0x00000001&(data))>>0)
#define ISO_U0SDMAM_get_sdmam(data)                                                  ((0x00000001&(data))>>0)


#define ISO_U0SFE                                                                    0x18007898
#define ISO_U0SFE_reg_addr                                                           "0xB8007898"
#define ISO_U0SFE_reg                                                                0xB8007898
#define set_ISO_U0SFE_reg(data)   (*((volatile unsigned int*) ISO_U0SFE_reg)=data)
#define get_ISO_U0SFE_reg   (*((volatile unsigned int*) ISO_U0SFE_reg))
#define ISO_U0SFE_inst_adr                                                           "0x0026"
#define ISO_U0SFE_inst                                                               0x0026
#define ISO_U0SFE_sfe_shift                                                          (0)
#define ISO_U0SFE_sfe_mask                                                           (0x00000001)
#define ISO_U0SFE_sfe(data)                                                          (0x00000001&((data)<<0))
#define ISO_U0SFE_sfe_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U0SFE_get_sfe(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U0SRT                                                                    0x1800789C
#define ISO_U0SRT_reg_addr                                                           "0xB800789C"
#define ISO_U0SRT_reg                                                                0xB800789C
#define set_ISO_U0SRT_reg(data)   (*((volatile unsigned int*) ISO_U0SRT_reg)=data)
#define get_ISO_U0SRT_reg   (*((volatile unsigned int*) ISO_U0SRT_reg))
#define ISO_U0SRT_inst_adr                                                           "0x0027"
#define ISO_U0SRT_inst                                                               0x0027
#define ISO_U0SRT_srt_shift                                                          (0)
#define ISO_U0SRT_srt_mask                                                           (0x00000003)
#define ISO_U0SRT_srt(data)                                                          (0x00000003&((data)<<0))
#define ISO_U0SRT_srt_src(data)                                                      ((0x00000003&(data))>>0)
#define ISO_U0SRT_get_srt(data)                                                      ((0x00000003&(data))>>0)


#define ISO_U0STET                                                                   0x180078A0
#define ISO_U0STET_reg_addr                                                          "0xB80078A0"
#define ISO_U0STET_reg                                                               0xB80078A0
#define set_ISO_U0STET_reg(data)   (*((volatile unsigned int*) ISO_U0STET_reg)=data)
#define get_ISO_U0STET_reg   (*((volatile unsigned int*) ISO_U0STET_reg))
#define ISO_U0STET_inst_adr                                                          "0x0028"
#define ISO_U0STET_inst                                                              0x0028
#define ISO_U0STET_stet_shift                                                        (0)
#define ISO_U0STET_stet_mask                                                         (0x00000003)
#define ISO_U0STET_stet(data)                                                        (0x00000003&((data)<<0))
#define ISO_U0STET_stet_src(data)                                                    ((0x00000003&(data))>>0)
#define ISO_U0STET_get_stet(data)                                                    ((0x00000003&(data))>>0)


#define ISO_U0HTX                                                                    0x180078A4
#define ISO_U0HTX_reg_addr                                                           "0xB80078A4"
#define ISO_U0HTX_reg                                                                0xB80078A4
#define set_ISO_U0HTX_reg(data)   (*((volatile unsigned int*) ISO_U0HTX_reg)=data)
#define get_ISO_U0HTX_reg   (*((volatile unsigned int*) ISO_U0HTX_reg))
#define ISO_U0HTX_inst_adr                                                           "0x0029"
#define ISO_U0HTX_inst                                                               0x0029
#define ISO_U0HTX_htx_shift                                                          (0)
#define ISO_U0HTX_htx_mask                                                           (0x00000001)
#define ISO_U0HTX_htx(data)                                                          (0x00000001&((data)<<0))
#define ISO_U0HTX_htx_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U0HTX_get_htx(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U0DMASA                                                                  0x180078A8
#define ISO_U0DMASA_reg_addr                                                         "0xB80078A8"
#define ISO_U0DMASA_reg                                                              0xB80078A8
#define set_ISO_U0DMASA_reg(data)   (*((volatile unsigned int*) ISO_U0DMASA_reg)=data)
#define get_ISO_U0DMASA_reg   (*((volatile unsigned int*) ISO_U0DMASA_reg))
#define ISO_U0DMASA_inst_adr                                                         "0x002A"
#define ISO_U0DMASA_inst                                                             0x002A
#define ISO_U0DMASA_dmasa_shift                                                      (0)
#define ISO_U0DMASA_dmasa_mask                                                       (0x00000001)
#define ISO_U0DMASA_dmasa(data)                                                      (0x00000001&((data)<<0))
#define ISO_U0DMASA_dmasa_src(data)                                                  ((0x00000001&(data))>>0)
#define ISO_U0DMASA_get_dmasa(data)                                                  ((0x00000001&(data))>>0)


#define ISO_U0CPR                                                                    0x180078F4
#define ISO_U0CPR_reg_addr                                                           "0xB80078F4"
#define ISO_U0CPR_reg                                                                0xB80078F4
#define set_ISO_U0CPR_reg(data)   (*((volatile unsigned int*) ISO_U0CPR_reg)=data)
#define get_ISO_U0CPR_reg   (*((volatile unsigned int*) ISO_U0CPR_reg))
#define ISO_U0CPR_inst_adr                                                           "0x003D"
#define ISO_U0CPR_inst                                                               0x003D
#define ISO_U0CPR_fifo_mode_shift                                                    (16)
#define ISO_U0CPR_fifo_mode_mask                                                     (0x00FF0000)
#define ISO_U0CPR_fifo_mode(data)                                                    (0x00FF0000&((data)<<16))
#define ISO_U0CPR_fifo_mode_src(data)                                                ((0x00FF0000&(data))>>16)
#define ISO_U0CPR_get_fifo_mode(data)                                                ((0x00FF0000&(data))>>16)
#define ISO_U0CPR_dma_extra_shift                                                    (13)
#define ISO_U0CPR_dma_extra_mask                                                     (0x00002000)
#define ISO_U0CPR_dma_extra(data)                                                    (0x00002000&((data)<<13))
#define ISO_U0CPR_dma_extra_src(data)                                                ((0x00002000&(data))>>13)
#define ISO_U0CPR_get_dma_extra(data)                                                ((0x00002000&(data))>>13)
#define ISO_U0CPR_uart_add_encoded_params_shift                                      (12)
#define ISO_U0CPR_uart_add_encoded_params_mask                                       (0x00001000)
#define ISO_U0CPR_uart_add_encoded_params(data)                                      (0x00001000&((data)<<12))
#define ISO_U0CPR_uart_add_encoded_params_src(data)                                  ((0x00001000&(data))>>12)
#define ISO_U0CPR_get_uart_add_encoded_params(data)                                  ((0x00001000&(data))>>12)
#define ISO_U0CPR_shadow_shift                                                       (11)
#define ISO_U0CPR_shadow_mask                                                        (0x00000800)
#define ISO_U0CPR_shadow(data)                                                       (0x00000800&((data)<<11))
#define ISO_U0CPR_shadow_src(data)                                                   ((0x00000800&(data))>>11)
#define ISO_U0CPR_get_shadow(data)                                                   ((0x00000800&(data))>>11)
#define ISO_U0CPR_fifo_stat_shift                                                    (10)
#define ISO_U0CPR_fifo_stat_mask                                                     (0x00000400)
#define ISO_U0CPR_fifo_stat(data)                                                    (0x00000400&((data)<<10))
#define ISO_U0CPR_fifo_stat_src(data)                                                ((0x00000400&(data))>>10)
#define ISO_U0CPR_get_fifo_stat(data)                                                ((0x00000400&(data))>>10)
#define ISO_U0CPR_fifo_access_shift                                                  (9)
#define ISO_U0CPR_fifo_access_mask                                                   (0x00000200)
#define ISO_U0CPR_fifo_access(data)                                                  (0x00000200&((data)<<9))
#define ISO_U0CPR_fifo_access_src(data)                                              ((0x00000200&(data))>>9)
#define ISO_U0CPR_get_fifo_access(data)                                              ((0x00000200&(data))>>9)
#define ISO_U0CPR_additional_feat_shift                                              (8)
#define ISO_U0CPR_additional_feat_mask                                               (0x00000100)
#define ISO_U0CPR_additional_feat(data)                                              (0x00000100&((data)<<8))
#define ISO_U0CPR_additional_feat_src(data)                                          ((0x00000100&(data))>>8)
#define ISO_U0CPR_get_additional_feat(data)                                          ((0x00000100&(data))>>8)
#define ISO_U0CPR_sir_lp_mode_shift                                                  (7)
#define ISO_U0CPR_sir_lp_mode_mask                                                   (0x00000080)
#define ISO_U0CPR_sir_lp_mode(data)                                                  (0x00000080&((data)<<7))
#define ISO_U0CPR_sir_lp_mode_src(data)                                              ((0x00000080&(data))>>7)
#define ISO_U0CPR_get_sir_lp_mode(data)                                              ((0x00000080&(data))>>7)
#define ISO_U0CPR_sir_mode_shift                                                     (6)
#define ISO_U0CPR_sir_mode_mask                                                      (0x00000040)
#define ISO_U0CPR_sir_mode(data)                                                     (0x00000040&((data)<<6))
#define ISO_U0CPR_sir_mode_src(data)                                                 ((0x00000040&(data))>>6)
#define ISO_U0CPR_get_sir_mode(data)                                                 ((0x00000040&(data))>>6)
#define ISO_U0CPR_thre_mode_shift                                                    (5)
#define ISO_U0CPR_thre_mode_mask                                                     (0x00000020)
#define ISO_U0CPR_thre_mode(data)                                                    (0x00000020&((data)<<5))
#define ISO_U0CPR_thre_mode_src(data)                                                ((0x00000020&(data))>>5)
#define ISO_U0CPR_get_thre_mode(data)                                                ((0x00000020&(data))>>5)
#define ISO_U0CPR_afce_mode_shift                                                    (4)
#define ISO_U0CPR_afce_mode_mask                                                     (0x00000010)
#define ISO_U0CPR_afce_mode(data)                                                    (0x00000010&((data)<<4))
#define ISO_U0CPR_afce_mode_src(data)                                                ((0x00000010&(data))>>4)
#define ISO_U0CPR_get_afce_mode(data)                                                ((0x00000010&(data))>>4)
#define ISO_U0CPR_apb_data_width_shift                                               (0)
#define ISO_U0CPR_apb_data_width_mask                                                (0x00000003)
#define ISO_U0CPR_apb_data_width(data)                                               (0x00000003&((data)<<0))
#define ISO_U0CPR_apb_data_width_src(data)                                           ((0x00000003&(data))>>0)
#define ISO_U0CPR_get_apb_data_width(data)                                           ((0x00000003&(data))>>0)


#define ISO_U0UCV                                                                    0x180078F8
#define ISO_U0UCV_reg_addr                                                           "0xB80078F8"
#define ISO_U0UCV_reg                                                                0xB80078F8
#define set_ISO_U0UCV_reg(data)   (*((volatile unsigned int*) ISO_U0UCV_reg)=data)
#define get_ISO_U0UCV_reg   (*((volatile unsigned int*) ISO_U0UCV_reg))
#define ISO_U0UCV_inst_adr                                                           "0x003E"
#define ISO_U0UCV_inst                                                               0x003E
#define ISO_U0UCV_ucv_shift                                                          (0)
#define ISO_U0UCV_ucv_mask                                                           (0xFFFFFFFF)
#define ISO_U0UCV_ucv(data)                                                          (0xFFFFFFFF&((data)<<0))
#define ISO_U0UCV_ucv_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define ISO_U0UCV_get_ucv(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define ISO_U0CTR                                                                    0x180078FC
#define ISO_U0CTR_reg_addr                                                           "0xB80078FC"
#define ISO_U0CTR_reg                                                                0xB80078FC
#define set_ISO_U0CTR_reg(data)   (*((volatile unsigned int*) ISO_U0CTR_reg)=data)
#define get_ISO_U0CTR_reg   (*((volatile unsigned int*) ISO_U0CTR_reg))
#define ISO_U0CTR_inst_adr                                                           "0x003F"
#define ISO_U0CTR_inst                                                               0x003F
#define ISO_U0CTR_ctr_shift                                                          (0)
#define ISO_U0CTR_ctr_mask                                                           (0xFFFFFFFF)
#define ISO_U0CTR_ctr(data)                                                          (0xFFFFFFFF&((data)<<0))
#define ISO_U0CTR_ctr_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define ISO_U0CTR_get_ctr(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define ISO_IC0_CON                                                                  0x18007D00
#define ISO_IC0_CON_reg_addr                                                         "0xB8007D00"
#define ISO_IC0_CON_reg                                                              0xB8007D00
#define set_ISO_IC0_CON_reg(data)   (*((volatile unsigned int*) ISO_IC0_CON_reg)=data)
#define get_ISO_IC0_CON_reg   (*((volatile unsigned int*) ISO_IC0_CON_reg))
#define ISO_IC0_CON_inst_adr                                                         "0x0040"
#define ISO_IC0_CON_inst                                                             0x0040
#define ISO_IC0_CON_ic_slave_disable_shift                                           (6)
#define ISO_IC0_CON_ic_slave_disable_mask                                            (0x00000040)
#define ISO_IC0_CON_ic_slave_disable(data)                                           (0x00000040&((data)<<6))
#define ISO_IC0_CON_ic_slave_disable_src(data)                                       ((0x00000040&(data))>>6)
#define ISO_IC0_CON_get_ic_slave_disable(data)                                       ((0x00000040&(data))>>6)
#define ISO_IC0_CON_ic_restart_en_shift                                              (5)
#define ISO_IC0_CON_ic_restart_en_mask                                               (0x00000020)
#define ISO_IC0_CON_ic_restart_en(data)                                              (0x00000020&((data)<<5))
#define ISO_IC0_CON_ic_restart_en_src(data)                                          ((0x00000020&(data))>>5)
#define ISO_IC0_CON_get_ic_restart_en(data)                                          ((0x00000020&(data))>>5)
#define ISO_IC0_CON_ic_10bitaddr_master_shift                                        (4)
#define ISO_IC0_CON_ic_10bitaddr_master_mask                                         (0x00000010)
#define ISO_IC0_CON_ic_10bitaddr_master(data)                                        (0x00000010&((data)<<4))
#define ISO_IC0_CON_ic_10bitaddr_master_src(data)                                    ((0x00000010&(data))>>4)
#define ISO_IC0_CON_get_ic_10bitaddr_master(data)                                    ((0x00000010&(data))>>4)
#define ISO_IC0_CON_ic_10bitaddr_slave_shift                                         (3)
#define ISO_IC0_CON_ic_10bitaddr_slave_mask                                          (0x00000008)
#define ISO_IC0_CON_ic_10bitaddr_slave(data)                                         (0x00000008&((data)<<3))
#define ISO_IC0_CON_ic_10bitaddr_slave_src(data)                                     ((0x00000008&(data))>>3)
#define ISO_IC0_CON_get_ic_10bitaddr_slave(data)                                     ((0x00000008&(data))>>3)
#define ISO_IC0_CON_speed_shift                                                      (1)
#define ISO_IC0_CON_speed_mask                                                       (0x00000006)
#define ISO_IC0_CON_speed(data)                                                      (0x00000006&((data)<<1))
#define ISO_IC0_CON_speed_src(data)                                                  ((0x00000006&(data))>>1)
#define ISO_IC0_CON_get_speed(data)                                                  ((0x00000006&(data))>>1)
#define ISO_IC0_CON_master_mode_shift                                                (0)
#define ISO_IC0_CON_master_mode_mask                                                 (0x00000001)
#define ISO_IC0_CON_master_mode(data)                                                (0x00000001&((data)<<0))
#define ISO_IC0_CON_master_mode_src(data)                                            ((0x00000001&(data))>>0)
#define ISO_IC0_CON_get_master_mode(data)                                            ((0x00000001&(data))>>0)


#define ISO_IC0_TAR                                                                  0x18007D04
#define ISO_IC0_TAR_reg_addr                                                         "0xB8007D04"
#define ISO_IC0_TAR_reg                                                              0xB8007D04
#define set_ISO_IC0_TAR_reg(data)   (*((volatile unsigned int*) ISO_IC0_TAR_reg)=data)
#define get_ISO_IC0_TAR_reg   (*((volatile unsigned int*) ISO_IC0_TAR_reg))
#define ISO_IC0_TAR_inst_adr                                                         "0x0041"
#define ISO_IC0_TAR_inst                                                             0x0041
#define ISO_IC0_TAR_ic_10bitaddr_master_shift                                        (12)
#define ISO_IC0_TAR_ic_10bitaddr_master_mask                                         (0x00001000)
#define ISO_IC0_TAR_ic_10bitaddr_master(data)                                        (0x00001000&((data)<<12))
#define ISO_IC0_TAR_ic_10bitaddr_master_src(data)                                    ((0x00001000&(data))>>12)
#define ISO_IC0_TAR_get_ic_10bitaddr_master(data)                                    ((0x00001000&(data))>>12)
#define ISO_IC0_TAR_special_shift                                                    (11)
#define ISO_IC0_TAR_special_mask                                                     (0x00000800)
#define ISO_IC0_TAR_special(data)                                                    (0x00000800&((data)<<11))
#define ISO_IC0_TAR_special_src(data)                                                ((0x00000800&(data))>>11)
#define ISO_IC0_TAR_get_special(data)                                                ((0x00000800&(data))>>11)
#define ISO_IC0_TAR_gc_or_start_shift                                                (10)
#define ISO_IC0_TAR_gc_or_start_mask                                                 (0x00000400)
#define ISO_IC0_TAR_gc_or_start(data)                                                (0x00000400&((data)<<10))
#define ISO_IC0_TAR_gc_or_start_src(data)                                            ((0x00000400&(data))>>10)
#define ISO_IC0_TAR_get_gc_or_start(data)                                            ((0x00000400&(data))>>10)
#define ISO_IC0_TAR_ic_tar_shift                                                     (0)
#define ISO_IC0_TAR_ic_tar_mask                                                      (0x000003FF)
#define ISO_IC0_TAR_ic_tar(data)                                                     (0x000003FF&((data)<<0))
#define ISO_IC0_TAR_ic_tar_src(data)                                                 ((0x000003FF&(data))>>0)
#define ISO_IC0_TAR_get_ic_tar(data)                                                 ((0x000003FF&(data))>>0)


#define ISO_IC0_SAR                                                                  0x18007D08
#define ISO_IC0_SAR_reg_addr                                                         "0xB8007D08"
#define ISO_IC0_SAR_reg                                                              0xB8007D08
#define set_ISO_IC0_SAR_reg(data)   (*((volatile unsigned int*) ISO_IC0_SAR_reg)=data)
#define get_ISO_IC0_SAR_reg   (*((volatile unsigned int*) ISO_IC0_SAR_reg))
#define ISO_IC0_SAR_inst_adr                                                         "0x0042"
#define ISO_IC0_SAR_inst                                                             0x0042
#define ISO_IC0_SAR_ic_sar_shift                                                     (0)
#define ISO_IC0_SAR_ic_sar_mask                                                      (0x000003FF)
#define ISO_IC0_SAR_ic_sar(data)                                                     (0x000003FF&((data)<<0))
#define ISO_IC0_SAR_ic_sar_src(data)                                                 ((0x000003FF&(data))>>0)
#define ISO_IC0_SAR_get_ic_sar(data)                                                 ((0x000003FF&(data))>>0)


#define ISO_IC0_HS_MADDR                                                             0x18007D0C
#define ISO_IC0_HS_MADDR_reg_addr                                                    "0xB8007D0C"
#define ISO_IC0_HS_MADDR_reg                                                         0xB8007D0C
#define set_ISO_IC0_HS_MADDR_reg(data)   (*((volatile unsigned int*) ISO_IC0_HS_MADDR_reg)=data)
#define get_ISO_IC0_HS_MADDR_reg   (*((volatile unsigned int*) ISO_IC0_HS_MADDR_reg))
#define ISO_IC0_HS_MADDR_inst_adr                                                    "0x0043"
#define ISO_IC0_HS_MADDR_inst                                                        0x0043
#define ISO_IC0_HS_MADDR_ic_hs_mar_shift                                             (0)
#define ISO_IC0_HS_MADDR_ic_hs_mar_mask                                              (0x00000007)
#define ISO_IC0_HS_MADDR_ic_hs_mar(data)                                             (0x00000007&((data)<<0))
#define ISO_IC0_HS_MADDR_ic_hs_mar_src(data)                                         ((0x00000007&(data))>>0)
#define ISO_IC0_HS_MADDR_get_ic_hs_mar(data)                                         ((0x00000007&(data))>>0)


#define ISO_IC0_DATA_CMD                                                             0x18007D10
#define ISO_IC0_DATA_CMD_reg_addr                                                    "0xB8007D10"
#define ISO_IC0_DATA_CMD_reg                                                         0xB8007D10
#define set_ISO_IC0_DATA_CMD_reg(data)   (*((volatile unsigned int*) ISO_IC0_DATA_CMD_reg)=data)
#define get_ISO_IC0_DATA_CMD_reg   (*((volatile unsigned int*) ISO_IC0_DATA_CMD_reg))
#define ISO_IC0_DATA_CMD_inst_adr                                                    "0x0044"
#define ISO_IC0_DATA_CMD_inst                                                        0x0044
#define ISO_IC0_DATA_CMD_restart_shift                                               (10)
#define ISO_IC0_DATA_CMD_restart_mask                                                (0x00000400)
#define ISO_IC0_DATA_CMD_restart(data)                                               (0x00000400&((data)<<10))
#define ISO_IC0_DATA_CMD_restart_src(data)                                           ((0x00000400&(data))>>10)
#define ISO_IC0_DATA_CMD_get_restart(data)                                           ((0x00000400&(data))>>10)
#define ISO_IC0_DATA_CMD_stop_shift                                                  (9)
#define ISO_IC0_DATA_CMD_stop_mask                                                   (0x00000200)
#define ISO_IC0_DATA_CMD_stop(data)                                                  (0x00000200&((data)<<9))
#define ISO_IC0_DATA_CMD_stop_src(data)                                              ((0x00000200&(data))>>9)
#define ISO_IC0_DATA_CMD_get_stop(data)                                              ((0x00000200&(data))>>9)
#define ISO_IC0_DATA_CMD_cmd_shift                                                   (8)
#define ISO_IC0_DATA_CMD_cmd_mask                                                    (0x00000100)
#define ISO_IC0_DATA_CMD_cmd(data)                                                   (0x00000100&((data)<<8))
#define ISO_IC0_DATA_CMD_cmd_src(data)                                               ((0x00000100&(data))>>8)
#define ISO_IC0_DATA_CMD_get_cmd(data)                                               ((0x00000100&(data))>>8)
#define ISO_IC0_DATA_CMD_dat_shift                                                   (0)
#define ISO_IC0_DATA_CMD_dat_mask                                                    (0x000000FF)
#define ISO_IC0_DATA_CMD_dat(data)                                                   (0x000000FF&((data)<<0))
#define ISO_IC0_DATA_CMD_dat_src(data)                                               ((0x000000FF&(data))>>0)
#define ISO_IC0_DATA_CMD_get_dat(data)                                               ((0x000000FF&(data))>>0)


#define ISO_IC0_SS_SCL_HCNT                                                          0x18007D14
#define ISO_IC0_SS_SCL_HCNT_reg_addr                                                 "0xB8007D14"
#define ISO_IC0_SS_SCL_HCNT_reg                                                      0xB8007D14
#define set_ISO_IC0_SS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) ISO_IC0_SS_SCL_HCNT_reg)=data)
#define get_ISO_IC0_SS_SCL_HCNT_reg   (*((volatile unsigned int*) ISO_IC0_SS_SCL_HCNT_reg))
#define ISO_IC0_SS_SCL_HCNT_inst_adr                                                 "0x0045"
#define ISO_IC0_SS_SCL_HCNT_inst                                                     0x0045
#define ISO_IC0_SS_SCL_HCNT_ic_ss_scl_hcnt_shift                                     (0)
#define ISO_IC0_SS_SCL_HCNT_ic_ss_scl_hcnt_mask                                      (0x0000FFFF)
#define ISO_IC0_SS_SCL_HCNT_ic_ss_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define ISO_IC0_SS_SCL_HCNT_ic_ss_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define ISO_IC0_SS_SCL_HCNT_get_ic_ss_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define ISO_IC0_SS_SCL_LCNT                                                          0x18007D18
#define ISO_IC0_SS_SCL_LCNT_reg_addr                                                 "0xB8007D18"
#define ISO_IC0_SS_SCL_LCNT_reg                                                      0xB8007D18
#define set_ISO_IC0_SS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) ISO_IC0_SS_SCL_LCNT_reg)=data)
#define get_ISO_IC0_SS_SCL_LCNT_reg   (*((volatile unsigned int*) ISO_IC0_SS_SCL_LCNT_reg))
#define ISO_IC0_SS_SCL_LCNT_inst_adr                                                 "0x0046"
#define ISO_IC0_SS_SCL_LCNT_inst                                                     0x0046
#define ISO_IC0_SS_SCL_LCNT_ic_ss_scl_lcnt_shift                                     (0)
#define ISO_IC0_SS_SCL_LCNT_ic_ss_scl_lcnt_mask                                      (0x0000FFFF)
#define ISO_IC0_SS_SCL_LCNT_ic_ss_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define ISO_IC0_SS_SCL_LCNT_ic_ss_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define ISO_IC0_SS_SCL_LCNT_get_ic_ss_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define ISO_IC0_FS_SCL_HCNT                                                          0x18007D1C
#define ISO_IC0_FS_SCL_HCNT_reg_addr                                                 "0xB8007D1C"
#define ISO_IC0_FS_SCL_HCNT_reg                                                      0xB8007D1C
#define set_ISO_IC0_FS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) ISO_IC0_FS_SCL_HCNT_reg)=data)
#define get_ISO_IC0_FS_SCL_HCNT_reg   (*((volatile unsigned int*) ISO_IC0_FS_SCL_HCNT_reg))
#define ISO_IC0_FS_SCL_HCNT_inst_adr                                                 "0x0047"
#define ISO_IC0_FS_SCL_HCNT_inst                                                     0x0047
#define ISO_IC0_FS_SCL_HCNT_ic_fs_scl_hcnt_shift                                     (0)
#define ISO_IC0_FS_SCL_HCNT_ic_fs_scl_hcnt_mask                                      (0x0000FFFF)
#define ISO_IC0_FS_SCL_HCNT_ic_fs_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define ISO_IC0_FS_SCL_HCNT_ic_fs_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define ISO_IC0_FS_SCL_HCNT_get_ic_fs_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define ISO_IC0_FS_SCL_LCNT                                                          0x18007D20
#define ISO_IC0_FS_SCL_LCNT_reg_addr                                                 "0xB8007D20"
#define ISO_IC0_FS_SCL_LCNT_reg                                                      0xB8007D20
#define set_ISO_IC0_FS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) ISO_IC0_FS_SCL_LCNT_reg)=data)
#define get_ISO_IC0_FS_SCL_LCNT_reg   (*((volatile unsigned int*) ISO_IC0_FS_SCL_LCNT_reg))
#define ISO_IC0_FS_SCL_LCNT_inst_adr                                                 "0x0048"
#define ISO_IC0_FS_SCL_LCNT_inst                                                     0x0048
#define ISO_IC0_FS_SCL_LCNT_ic_fs_scl_lcnt_shift                                     (0)
#define ISO_IC0_FS_SCL_LCNT_ic_fs_scl_lcnt_mask                                      (0x0000FFFF)
#define ISO_IC0_FS_SCL_LCNT_ic_fs_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define ISO_IC0_FS_SCL_LCNT_ic_fs_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define ISO_IC0_FS_SCL_LCNT_get_ic_fs_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define ISO_IC0_INTR_STAT                                                            0x18007D2C
#define ISO_IC0_INTR_STAT_reg_addr                                                   "0xB8007D2C"
#define ISO_IC0_INTR_STAT_reg                                                        0xB8007D2C
#define set_ISO_IC0_INTR_STAT_reg(data)   (*((volatile unsigned int*) ISO_IC0_INTR_STAT_reg)=data)
#define get_ISO_IC0_INTR_STAT_reg   (*((volatile unsigned int*) ISO_IC0_INTR_STAT_reg))
#define ISO_IC0_INTR_STAT_inst_adr                                                   "0x004B"
#define ISO_IC0_INTR_STAT_inst                                                       0x004B
#define ISO_IC0_INTR_STAT_r_gen_call_shift                                           (11)
#define ISO_IC0_INTR_STAT_r_gen_call_mask                                            (0x00000800)
#define ISO_IC0_INTR_STAT_r_gen_call(data)                                           (0x00000800&((data)<<11))
#define ISO_IC0_INTR_STAT_r_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define ISO_IC0_INTR_STAT_get_r_gen_call(data)                                       ((0x00000800&(data))>>11)
#define ISO_IC0_INTR_STAT_r_start_det_shift                                          (10)
#define ISO_IC0_INTR_STAT_r_start_det_mask                                           (0x00000400)
#define ISO_IC0_INTR_STAT_r_start_det(data)                                          (0x00000400&((data)<<10))
#define ISO_IC0_INTR_STAT_r_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define ISO_IC0_INTR_STAT_get_r_start_det(data)                                      ((0x00000400&(data))>>10)
#define ISO_IC0_INTR_STAT_r_stop_det_shift                                           (9)
#define ISO_IC0_INTR_STAT_r_stop_det_mask                                            (0x00000200)
#define ISO_IC0_INTR_STAT_r_stop_det(data)                                           (0x00000200&((data)<<9))
#define ISO_IC0_INTR_STAT_r_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define ISO_IC0_INTR_STAT_get_r_stop_det(data)                                       ((0x00000200&(data))>>9)
#define ISO_IC0_INTR_STAT_r_activity_shift                                           (8)
#define ISO_IC0_INTR_STAT_r_activity_mask                                            (0x00000100)
#define ISO_IC0_INTR_STAT_r_activity(data)                                           (0x00000100&((data)<<8))
#define ISO_IC0_INTR_STAT_r_activity_src(data)                                       ((0x00000100&(data))>>8)
#define ISO_IC0_INTR_STAT_get_r_activity(data)                                       ((0x00000100&(data))>>8)
#define ISO_IC0_INTR_STAT_r_rx_done_shift                                            (7)
#define ISO_IC0_INTR_STAT_r_rx_done_mask                                             (0x00000080)
#define ISO_IC0_INTR_STAT_r_rx_done(data)                                            (0x00000080&((data)<<7))
#define ISO_IC0_INTR_STAT_r_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define ISO_IC0_INTR_STAT_get_r_rx_done(data)                                        ((0x00000080&(data))>>7)
#define ISO_IC0_INTR_STAT_r_tx_abrt_shift                                            (6)
#define ISO_IC0_INTR_STAT_r_tx_abrt_mask                                             (0x00000040)
#define ISO_IC0_INTR_STAT_r_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define ISO_IC0_INTR_STAT_r_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC0_INTR_STAT_get_r_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC0_INTR_STAT_r_rd_req_shift                                             (5)
#define ISO_IC0_INTR_STAT_r_rd_req_mask                                              (0x00000020)
#define ISO_IC0_INTR_STAT_r_rd_req(data)                                             (0x00000020&((data)<<5))
#define ISO_IC0_INTR_STAT_r_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define ISO_IC0_INTR_STAT_get_r_rd_req(data)                                         ((0x00000020&(data))>>5)
#define ISO_IC0_INTR_STAT_r_tx_empty_shift                                           (4)
#define ISO_IC0_INTR_STAT_r_tx_empty_mask                                            (0x00000010)
#define ISO_IC0_INTR_STAT_r_tx_empty(data)                                           (0x00000010&((data)<<4))
#define ISO_IC0_INTR_STAT_r_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define ISO_IC0_INTR_STAT_get_r_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define ISO_IC0_INTR_STAT_r_tx_over_shift                                            (3)
#define ISO_IC0_INTR_STAT_r_tx_over_mask                                             (0x00000008)
#define ISO_IC0_INTR_STAT_r_tx_over(data)                                            (0x00000008&((data)<<3))
#define ISO_IC0_INTR_STAT_r_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define ISO_IC0_INTR_STAT_get_r_tx_over(data)                                        ((0x00000008&(data))>>3)
#define ISO_IC0_INTR_STAT_r_rx_full_shift                                            (2)
#define ISO_IC0_INTR_STAT_r_rx_full_mask                                             (0x00000004)
#define ISO_IC0_INTR_STAT_r_rx_full(data)                                            (0x00000004&((data)<<2))
#define ISO_IC0_INTR_STAT_r_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define ISO_IC0_INTR_STAT_get_r_rx_full(data)                                        ((0x00000004&(data))>>2)
#define ISO_IC0_INTR_STAT_r_rx_over_shift                                            (1)
#define ISO_IC0_INTR_STAT_r_rx_over_mask                                             (0x00000002)
#define ISO_IC0_INTR_STAT_r_rx_over(data)                                            (0x00000002&((data)<<1))
#define ISO_IC0_INTR_STAT_r_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define ISO_IC0_INTR_STAT_get_r_rx_over(data)                                        ((0x00000002&(data))>>1)
#define ISO_IC0_INTR_STAT_r_rx_under_shift                                           (0)
#define ISO_IC0_INTR_STAT_r_rx_under_mask                                            (0x00000001)
#define ISO_IC0_INTR_STAT_r_rx_under(data)                                           (0x00000001&((data)<<0))
#define ISO_IC0_INTR_STAT_r_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define ISO_IC0_INTR_STAT_get_r_rx_under(data)                                       ((0x00000001&(data))>>0)


#define ISO_IC0_INTR_MASK                                                            0x18007D30
#define ISO_IC0_INTR_MASK_reg_addr                                                   "0xB8007D30"
#define ISO_IC0_INTR_MASK_reg                                                        0xB8007D30
#define set_ISO_IC0_INTR_MASK_reg(data)   (*((volatile unsigned int*) ISO_IC0_INTR_MASK_reg)=data)
#define get_ISO_IC0_INTR_MASK_reg   (*((volatile unsigned int*) ISO_IC0_INTR_MASK_reg))
#define ISO_IC0_INTR_MASK_inst_adr                                                   "0x004C"
#define ISO_IC0_INTR_MASK_inst                                                       0x004C
#define ISO_IC0_INTR_MASK_m_gen_call_shift                                           (11)
#define ISO_IC0_INTR_MASK_m_gen_call_mask                                            (0x00000800)
#define ISO_IC0_INTR_MASK_m_gen_call(data)                                           (0x00000800&((data)<<11))
#define ISO_IC0_INTR_MASK_m_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define ISO_IC0_INTR_MASK_get_m_gen_call(data)                                       ((0x00000800&(data))>>11)
#define ISO_IC0_INTR_MASK_m_start_det_shift                                          (10)
#define ISO_IC0_INTR_MASK_m_start_det_mask                                           (0x00000400)
#define ISO_IC0_INTR_MASK_m_start_det(data)                                          (0x00000400&((data)<<10))
#define ISO_IC0_INTR_MASK_m_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define ISO_IC0_INTR_MASK_get_m_start_det(data)                                      ((0x00000400&(data))>>10)
#define ISO_IC0_INTR_MASK_m_stop_det_shift                                           (9)
#define ISO_IC0_INTR_MASK_m_stop_det_mask                                            (0x00000200)
#define ISO_IC0_INTR_MASK_m_stop_det(data)                                           (0x00000200&((data)<<9))
#define ISO_IC0_INTR_MASK_m_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define ISO_IC0_INTR_MASK_get_m_stop_det(data)                                       ((0x00000200&(data))>>9)
#define ISO_IC0_INTR_MASK_m_activity_shift                                           (8)
#define ISO_IC0_INTR_MASK_m_activity_mask                                            (0x00000100)
#define ISO_IC0_INTR_MASK_m_activity(data)                                           (0x00000100&((data)<<8))
#define ISO_IC0_INTR_MASK_m_activity_src(data)                                       ((0x00000100&(data))>>8)
#define ISO_IC0_INTR_MASK_get_m_activity(data)                                       ((0x00000100&(data))>>8)
#define ISO_IC0_INTR_MASK_m_rx_done_shift                                            (7)
#define ISO_IC0_INTR_MASK_m_rx_done_mask                                             (0x00000080)
#define ISO_IC0_INTR_MASK_m_rx_done(data)                                            (0x00000080&((data)<<7))
#define ISO_IC0_INTR_MASK_m_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define ISO_IC0_INTR_MASK_get_m_rx_done(data)                                        ((0x00000080&(data))>>7)
#define ISO_IC0_INTR_MASK_m_tx_abrt_shift                                            (6)
#define ISO_IC0_INTR_MASK_m_tx_abrt_mask                                             (0x00000040)
#define ISO_IC0_INTR_MASK_m_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define ISO_IC0_INTR_MASK_m_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC0_INTR_MASK_get_m_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC0_INTR_MASK_m_rd_req_shift                                             (5)
#define ISO_IC0_INTR_MASK_m_rd_req_mask                                              (0x00000020)
#define ISO_IC0_INTR_MASK_m_rd_req(data)                                             (0x00000020&((data)<<5))
#define ISO_IC0_INTR_MASK_m_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define ISO_IC0_INTR_MASK_get_m_rd_req(data)                                         ((0x00000020&(data))>>5)
#define ISO_IC0_INTR_MASK_m_tx_empty_shift                                           (4)
#define ISO_IC0_INTR_MASK_m_tx_empty_mask                                            (0x00000010)
#define ISO_IC0_INTR_MASK_m_tx_empty(data)                                           (0x00000010&((data)<<4))
#define ISO_IC0_INTR_MASK_m_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define ISO_IC0_INTR_MASK_get_m_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define ISO_IC0_INTR_MASK_m_tx_over_shift                                            (3)
#define ISO_IC0_INTR_MASK_m_tx_over_mask                                             (0x00000008)
#define ISO_IC0_INTR_MASK_m_tx_over(data)                                            (0x00000008&((data)<<3))
#define ISO_IC0_INTR_MASK_m_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define ISO_IC0_INTR_MASK_get_m_tx_over(data)                                        ((0x00000008&(data))>>3)
#define ISO_IC0_INTR_MASK_m_rx_full_shift                                            (2)
#define ISO_IC0_INTR_MASK_m_rx_full_mask                                             (0x00000004)
#define ISO_IC0_INTR_MASK_m_rx_full(data)                                            (0x00000004&((data)<<2))
#define ISO_IC0_INTR_MASK_m_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define ISO_IC0_INTR_MASK_get_m_rx_full(data)                                        ((0x00000004&(data))>>2)
#define ISO_IC0_INTR_MASK_m_rx_over_shift                                            (1)
#define ISO_IC0_INTR_MASK_m_rx_over_mask                                             (0x00000002)
#define ISO_IC0_INTR_MASK_m_rx_over(data)                                            (0x00000002&((data)<<1))
#define ISO_IC0_INTR_MASK_m_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define ISO_IC0_INTR_MASK_get_m_rx_over(data)                                        ((0x00000002&(data))>>1)
#define ISO_IC0_INTR_MASK_m_rx_under_shift                                           (0)
#define ISO_IC0_INTR_MASK_m_rx_under_mask                                            (0x00000001)
#define ISO_IC0_INTR_MASK_m_rx_under(data)                                           (0x00000001&((data)<<0))
#define ISO_IC0_INTR_MASK_m_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define ISO_IC0_INTR_MASK_get_m_rx_under(data)                                       ((0x00000001&(data))>>0)


#define ISO_IC0_RAW_INTR_STAT                                                        0x18007D34
#define ISO_IC0_RAW_INTR_STAT_reg_addr                                               "0xB8007D34"
#define ISO_IC0_RAW_INTR_STAT_reg                                                    0xB8007D34
#define set_ISO_IC0_RAW_INTR_STAT_reg(data)   (*((volatile unsigned int*) ISO_IC0_RAW_INTR_STAT_reg)=data)
#define get_ISO_IC0_RAW_INTR_STAT_reg   (*((volatile unsigned int*) ISO_IC0_RAW_INTR_STAT_reg))
#define ISO_IC0_RAW_INTR_STAT_inst_adr                                               "0x004D"
#define ISO_IC0_RAW_INTR_STAT_inst                                                   0x004D
#define ISO_IC0_RAW_INTR_STAT_gen_call_shift                                         (11)
#define ISO_IC0_RAW_INTR_STAT_gen_call_mask                                          (0x00000800)
#define ISO_IC0_RAW_INTR_STAT_gen_call(data)                                         (0x00000800&((data)<<11))
#define ISO_IC0_RAW_INTR_STAT_gen_call_src(data)                                     ((0x00000800&(data))>>11)
#define ISO_IC0_RAW_INTR_STAT_get_gen_call(data)                                     ((0x00000800&(data))>>11)
#define ISO_IC0_RAW_INTR_STAT_start_det_shift                                        (10)
#define ISO_IC0_RAW_INTR_STAT_start_det_mask                                         (0x00000400)
#define ISO_IC0_RAW_INTR_STAT_start_det(data)                                        (0x00000400&((data)<<10))
#define ISO_IC0_RAW_INTR_STAT_start_det_src(data)                                    ((0x00000400&(data))>>10)
#define ISO_IC0_RAW_INTR_STAT_get_start_det(data)                                    ((0x00000400&(data))>>10)
#define ISO_IC0_RAW_INTR_STAT_stop_det_shift                                         (9)
#define ISO_IC0_RAW_INTR_STAT_stop_det_mask                                          (0x00000200)
#define ISO_IC0_RAW_INTR_STAT_stop_det(data)                                         (0x00000200&((data)<<9))
#define ISO_IC0_RAW_INTR_STAT_stop_det_src(data)                                     ((0x00000200&(data))>>9)
#define ISO_IC0_RAW_INTR_STAT_get_stop_det(data)                                     ((0x00000200&(data))>>9)
#define ISO_IC0_RAW_INTR_STAT_activity_shift                                         (8)
#define ISO_IC0_RAW_INTR_STAT_activity_mask                                          (0x00000100)
#define ISO_IC0_RAW_INTR_STAT_activity(data)                                         (0x00000100&((data)<<8))
#define ISO_IC0_RAW_INTR_STAT_activity_src(data)                                     ((0x00000100&(data))>>8)
#define ISO_IC0_RAW_INTR_STAT_get_activity(data)                                     ((0x00000100&(data))>>8)
#define ISO_IC0_RAW_INTR_STAT_rx_done_shift                                          (7)
#define ISO_IC0_RAW_INTR_STAT_rx_done_mask                                           (0x00000080)
#define ISO_IC0_RAW_INTR_STAT_rx_done(data)                                          (0x00000080&((data)<<7))
#define ISO_IC0_RAW_INTR_STAT_rx_done_src(data)                                      ((0x00000080&(data))>>7)
#define ISO_IC0_RAW_INTR_STAT_get_rx_done(data)                                      ((0x00000080&(data))>>7)
#define ISO_IC0_RAW_INTR_STAT_tx_abrt_shift                                          (6)
#define ISO_IC0_RAW_INTR_STAT_tx_abrt_mask                                           (0x00000040)
#define ISO_IC0_RAW_INTR_STAT_tx_abrt(data)                                          (0x00000040&((data)<<6))
#define ISO_IC0_RAW_INTR_STAT_tx_abrt_src(data)                                      ((0x00000040&(data))>>6)
#define ISO_IC0_RAW_INTR_STAT_get_tx_abrt(data)                                      ((0x00000040&(data))>>6)
#define ISO_IC0_RAW_INTR_STAT_rd_req_shift                                           (5)
#define ISO_IC0_RAW_INTR_STAT_rd_req_mask                                            (0x00000020)
#define ISO_IC0_RAW_INTR_STAT_rd_req(data)                                           (0x00000020&((data)<<5))
#define ISO_IC0_RAW_INTR_STAT_rd_req_src(data)                                       ((0x00000020&(data))>>5)
#define ISO_IC0_RAW_INTR_STAT_get_rd_req(data)                                       ((0x00000020&(data))>>5)
#define ISO_IC0_RAW_INTR_STAT_tx_empty_shift                                         (4)
#define ISO_IC0_RAW_INTR_STAT_tx_empty_mask                                          (0x00000010)
#define ISO_IC0_RAW_INTR_STAT_tx_empty(data)                                         (0x00000010&((data)<<4))
#define ISO_IC0_RAW_INTR_STAT_tx_empty_src(data)                                     ((0x00000010&(data))>>4)
#define ISO_IC0_RAW_INTR_STAT_get_tx_empty(data)                                     ((0x00000010&(data))>>4)
#define ISO_IC0_RAW_INTR_STAT_tx_over_shift                                          (3)
#define ISO_IC0_RAW_INTR_STAT_tx_over_mask                                           (0x00000008)
#define ISO_IC0_RAW_INTR_STAT_tx_over(data)                                          (0x00000008&((data)<<3))
#define ISO_IC0_RAW_INTR_STAT_tx_over_src(data)                                      ((0x00000008&(data))>>3)
#define ISO_IC0_RAW_INTR_STAT_get_tx_over(data)                                      ((0x00000008&(data))>>3)
#define ISO_IC0_RAW_INTR_STAT_rx_full_shift                                          (2)
#define ISO_IC0_RAW_INTR_STAT_rx_full_mask                                           (0x00000004)
#define ISO_IC0_RAW_INTR_STAT_rx_full(data)                                          (0x00000004&((data)<<2))
#define ISO_IC0_RAW_INTR_STAT_rx_full_src(data)                                      ((0x00000004&(data))>>2)
#define ISO_IC0_RAW_INTR_STAT_get_rx_full(data)                                      ((0x00000004&(data))>>2)
#define ISO_IC0_RAW_INTR_STAT_rx_over_shift                                          (1)
#define ISO_IC0_RAW_INTR_STAT_rx_over_mask                                           (0x00000002)
#define ISO_IC0_RAW_INTR_STAT_rx_over(data)                                          (0x00000002&((data)<<1))
#define ISO_IC0_RAW_INTR_STAT_rx_over_src(data)                                      ((0x00000002&(data))>>1)
#define ISO_IC0_RAW_INTR_STAT_get_rx_over(data)                                      ((0x00000002&(data))>>1)
#define ISO_IC0_RAW_INTR_STAT_rx_under_shift                                         (0)
#define ISO_IC0_RAW_INTR_STAT_rx_under_mask                                          (0x00000001)
#define ISO_IC0_RAW_INTR_STAT_rx_under(data)                                         (0x00000001&((data)<<0))
#define ISO_IC0_RAW_INTR_STAT_rx_under_src(data)                                     ((0x00000001&(data))>>0)
#define ISO_IC0_RAW_INTR_STAT_get_rx_under(data)                                     ((0x00000001&(data))>>0)


#define ISO_IC0_RX_TL                                                                0x18007D38
#define ISO_IC0_RX_TL_reg_addr                                                       "0xB8007D38"
#define ISO_IC0_RX_TL_reg                                                            0xB8007D38
#define set_ISO_IC0_RX_TL_reg(data)   (*((volatile unsigned int*) ISO_IC0_RX_TL_reg)=data)
#define get_ISO_IC0_RX_TL_reg   (*((volatile unsigned int*) ISO_IC0_RX_TL_reg))
#define ISO_IC0_RX_TL_inst_adr                                                       "0x004E"
#define ISO_IC0_RX_TL_inst                                                           0x004E
#define ISO_IC0_RX_TL_rx_tl_shift                                                    (0)
#define ISO_IC0_RX_TL_rx_tl_mask                                                     (0x000000FF)
#define ISO_IC0_RX_TL_rx_tl(data)                                                    (0x000000FF&((data)<<0))
#define ISO_IC0_RX_TL_rx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define ISO_IC0_RX_TL_get_rx_tl(data)                                                ((0x000000FF&(data))>>0)


#define ISO_IC0_TX_TL                                                                0x18007D3C
#define ISO_IC0_TX_TL_reg_addr                                                       "0xB8007D3C"
#define ISO_IC0_TX_TL_reg                                                            0xB8007D3C
#define set_ISO_IC0_TX_TL_reg(data)   (*((volatile unsigned int*) ISO_IC0_TX_TL_reg)=data)
#define get_ISO_IC0_TX_TL_reg   (*((volatile unsigned int*) ISO_IC0_TX_TL_reg))
#define ISO_IC0_TX_TL_inst_adr                                                       "0x004F"
#define ISO_IC0_TX_TL_inst                                                           0x004F
#define ISO_IC0_TX_TL_tx_tl_shift                                                    (0)
#define ISO_IC0_TX_TL_tx_tl_mask                                                     (0x000000FF)
#define ISO_IC0_TX_TL_tx_tl(data)                                                    (0x000000FF&((data)<<0))
#define ISO_IC0_TX_TL_tx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define ISO_IC0_TX_TL_get_tx_tl(data)                                                ((0x000000FF&(data))>>0)


#define ISO_IC0_CLR_INTR                                                             0x18007D40
#define ISO_IC0_CLR_INTR_reg_addr                                                    "0xB8007D40"
#define ISO_IC0_CLR_INTR_reg                                                         0xB8007D40
#define set_ISO_IC0_CLR_INTR_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_INTR_reg)=data)
#define get_ISO_IC0_CLR_INTR_reg   (*((volatile unsigned int*) ISO_IC0_CLR_INTR_reg))
#define ISO_IC0_CLR_INTR_inst_adr                                                    "0x0050"
#define ISO_IC0_CLR_INTR_inst                                                        0x0050
#define ISO_IC0_CLR_INTR_clr_intr_shift                                              (0)
#define ISO_IC0_CLR_INTR_clr_intr_mask                                               (0x00000001)
#define ISO_IC0_CLR_INTR_clr_intr(data)                                              (0x00000001&((data)<<0))
#define ISO_IC0_CLR_INTR_clr_intr_src(data)                                          ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_INTR_get_clr_intr(data)                                          ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_RX_UNDER                                                         0x18007D44
#define ISO_IC0_CLR_RX_UNDER_reg_addr                                                "0xB8007D44"
#define ISO_IC0_CLR_RX_UNDER_reg                                                     0xB8007D44
#define set_ISO_IC0_CLR_RX_UNDER_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_RX_UNDER_reg)=data)
#define get_ISO_IC0_CLR_RX_UNDER_reg   (*((volatile unsigned int*) ISO_IC0_CLR_RX_UNDER_reg))
#define ISO_IC0_CLR_RX_UNDER_inst_adr                                                "0x0051"
#define ISO_IC0_CLR_RX_UNDER_inst                                                    0x0051
#define ISO_IC0_CLR_RX_UNDER_clr_rx_under_shift                                      (0)
#define ISO_IC0_CLR_RX_UNDER_clr_rx_under_mask                                       (0x00000001)
#define ISO_IC0_CLR_RX_UNDER_clr_rx_under(data)                                      (0x00000001&((data)<<0))
#define ISO_IC0_CLR_RX_UNDER_clr_rx_under_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_RX_UNDER_get_clr_rx_under(data)                                  ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_RX_OVER                                                          0x18007D48
#define ISO_IC0_CLR_RX_OVER_reg_addr                                                 "0xB8007D48"
#define ISO_IC0_CLR_RX_OVER_reg                                                      0xB8007D48
#define set_ISO_IC0_CLR_RX_OVER_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_RX_OVER_reg)=data)
#define get_ISO_IC0_CLR_RX_OVER_reg   (*((volatile unsigned int*) ISO_IC0_CLR_RX_OVER_reg))
#define ISO_IC0_CLR_RX_OVER_inst_adr                                                 "0x0052"
#define ISO_IC0_CLR_RX_OVER_inst                                                     0x0052
#define ISO_IC0_CLR_RX_OVER_clr_rx_over_shift                                        (0)
#define ISO_IC0_CLR_RX_OVER_clr_rx_over_mask                                         (0x00000001)
#define ISO_IC0_CLR_RX_OVER_clr_rx_over(data)                                        (0x00000001&((data)<<0))
#define ISO_IC0_CLR_RX_OVER_clr_rx_over_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_RX_OVER_get_clr_rx_over(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_TX_OVER                                                          0x18007D4C
#define ISO_IC0_CLR_TX_OVER_reg_addr                                                 "0xB8007D4C"
#define ISO_IC0_CLR_TX_OVER_reg                                                      0xB8007D4C
#define set_ISO_IC0_CLR_TX_OVER_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_TX_OVER_reg)=data)
#define get_ISO_IC0_CLR_TX_OVER_reg   (*((volatile unsigned int*) ISO_IC0_CLR_TX_OVER_reg))
#define ISO_IC0_CLR_TX_OVER_inst_adr                                                 "0x0053"
#define ISO_IC0_CLR_TX_OVER_inst                                                     0x0053
#define ISO_IC0_CLR_TX_OVER_clr_tx_over_shift                                        (0)
#define ISO_IC0_CLR_TX_OVER_clr_tx_over_mask                                         (0x00000001)
#define ISO_IC0_CLR_TX_OVER_clr_tx_over(data)                                        (0x00000001&((data)<<0))
#define ISO_IC0_CLR_TX_OVER_clr_tx_over_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_TX_OVER_get_clr_tx_over(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_RD_REQ                                                           0x18007D50
#define ISO_IC0_CLR_RD_REQ_reg_addr                                                  "0xB8007D50"
#define ISO_IC0_CLR_RD_REQ_reg                                                       0xB8007D50
#define set_ISO_IC0_CLR_RD_REQ_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_RD_REQ_reg)=data)
#define get_ISO_IC0_CLR_RD_REQ_reg   (*((volatile unsigned int*) ISO_IC0_CLR_RD_REQ_reg))
#define ISO_IC0_CLR_RD_REQ_inst_adr                                                  "0x0054"
#define ISO_IC0_CLR_RD_REQ_inst                                                      0x0054
#define ISO_IC0_CLR_RD_REQ_clr_rd_req_shift                                          (0)
#define ISO_IC0_CLR_RD_REQ_clr_rd_req_mask                                           (0x00000001)
#define ISO_IC0_CLR_RD_REQ_clr_rd_req(data)                                          (0x00000001&((data)<<0))
#define ISO_IC0_CLR_RD_REQ_clr_rd_req_src(data)                                      ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_RD_REQ_get_clr_rd_req(data)                                      ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_TX_ABRT                                                          0x18007D54
#define ISO_IC0_CLR_TX_ABRT_reg_addr                                                 "0xB8007D54"
#define ISO_IC0_CLR_TX_ABRT_reg                                                      0xB8007D54
#define set_ISO_IC0_CLR_TX_ABRT_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_TX_ABRT_reg)=data)
#define get_ISO_IC0_CLR_TX_ABRT_reg   (*((volatile unsigned int*) ISO_IC0_CLR_TX_ABRT_reg))
#define ISO_IC0_CLR_TX_ABRT_inst_adr                                                 "0x0055"
#define ISO_IC0_CLR_TX_ABRT_inst                                                     0x0055
#define ISO_IC0_CLR_TX_ABRT_clr_tx_abrt_shift                                        (0)
#define ISO_IC0_CLR_TX_ABRT_clr_tx_abrt_mask                                         (0x00000001)
#define ISO_IC0_CLR_TX_ABRT_clr_tx_abrt(data)                                        (0x00000001&((data)<<0))
#define ISO_IC0_CLR_TX_ABRT_clr_tx_abrt_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_TX_ABRT_get_clr_tx_abrt(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_RX_DONE                                                          0x18007D58
#define ISO_IC0_CLR_RX_DONE_reg_addr                                                 "0xB8007D58"
#define ISO_IC0_CLR_RX_DONE_reg                                                      0xB8007D58
#define set_ISO_IC0_CLR_RX_DONE_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_RX_DONE_reg)=data)
#define get_ISO_IC0_CLR_RX_DONE_reg   (*((volatile unsigned int*) ISO_IC0_CLR_RX_DONE_reg))
#define ISO_IC0_CLR_RX_DONE_inst_adr                                                 "0x0056"
#define ISO_IC0_CLR_RX_DONE_inst                                                     0x0056
#define ISO_IC0_CLR_RX_DONE_clr_rx_done_shift                                        (0)
#define ISO_IC0_CLR_RX_DONE_clr_rx_done_mask                                         (0x00000001)
#define ISO_IC0_CLR_RX_DONE_clr_rx_done(data)                                        (0x00000001&((data)<<0))
#define ISO_IC0_CLR_RX_DONE_clr_rx_done_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_RX_DONE_get_clr_rx_done(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_ACTIVITY                                                         0x18007D5C
#define ISO_IC0_CLR_ACTIVITY_reg_addr                                                "0xB8007D5C"
#define ISO_IC0_CLR_ACTIVITY_reg                                                     0xB8007D5C
#define set_ISO_IC0_CLR_ACTIVITY_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_ACTIVITY_reg)=data)
#define get_ISO_IC0_CLR_ACTIVITY_reg   (*((volatile unsigned int*) ISO_IC0_CLR_ACTIVITY_reg))
#define ISO_IC0_CLR_ACTIVITY_inst_adr                                                "0x0057"
#define ISO_IC0_CLR_ACTIVITY_inst                                                    0x0057
#define ISO_IC0_CLR_ACTIVITY_clr_activity_shift                                      (0)
#define ISO_IC0_CLR_ACTIVITY_clr_activity_mask                                       (0x00000001)
#define ISO_IC0_CLR_ACTIVITY_clr_activity(data)                                      (0x00000001&((data)<<0))
#define ISO_IC0_CLR_ACTIVITY_clr_activity_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_ACTIVITY_get_clr_activity(data)                                  ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_STOP_DET                                                         0x18007D60
#define ISO_IC0_CLR_STOP_DET_reg_addr                                                "0xB8007D60"
#define ISO_IC0_CLR_STOP_DET_reg                                                     0xB8007D60
#define set_ISO_IC0_CLR_STOP_DET_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_STOP_DET_reg)=data)
#define get_ISO_IC0_CLR_STOP_DET_reg   (*((volatile unsigned int*) ISO_IC0_CLR_STOP_DET_reg))
#define ISO_IC0_CLR_STOP_DET_inst_adr                                                "0x0058"
#define ISO_IC0_CLR_STOP_DET_inst                                                    0x0058
#define ISO_IC0_CLR_STOP_DET_clr_stop_det_shift                                      (0)
#define ISO_IC0_CLR_STOP_DET_clr_stop_det_mask                                       (0x00000001)
#define ISO_IC0_CLR_STOP_DET_clr_stop_det(data)                                      (0x00000001&((data)<<0))
#define ISO_IC0_CLR_STOP_DET_clr_stop_det_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_STOP_DET_get_clr_stop_det(data)                                  ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_START_DET                                                        0x18007D64
#define ISO_IC0_CLR_START_DET_reg_addr                                               "0xB8007D64"
#define ISO_IC0_CLR_START_DET_reg                                                    0xB8007D64
#define set_ISO_IC0_CLR_START_DET_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_START_DET_reg)=data)
#define get_ISO_IC0_CLR_START_DET_reg   (*((volatile unsigned int*) ISO_IC0_CLR_START_DET_reg))
#define ISO_IC0_CLR_START_DET_inst_adr                                               "0x0059"
#define ISO_IC0_CLR_START_DET_inst                                                   0x0059
#define ISO_IC0_CLR_START_DET_clr_start_det_shift                                    (0)
#define ISO_IC0_CLR_START_DET_clr_start_det_mask                                     (0x00000001)
#define ISO_IC0_CLR_START_DET_clr_start_det(data)                                    (0x00000001&((data)<<0))
#define ISO_IC0_CLR_START_DET_clr_start_det_src(data)                                ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_START_DET_get_clr_start_det(data)                                ((0x00000001&(data))>>0)


#define ISO_IC0_CLR_GEN_CALL                                                         0x18007D68
#define ISO_IC0_CLR_GEN_CALL_reg_addr                                                "0xB8007D68"
#define ISO_IC0_CLR_GEN_CALL_reg                                                     0xB8007D68
#define set_ISO_IC0_CLR_GEN_CALL_reg(data)   (*((volatile unsigned int*) ISO_IC0_CLR_GEN_CALL_reg)=data)
#define get_ISO_IC0_CLR_GEN_CALL_reg   (*((volatile unsigned int*) ISO_IC0_CLR_GEN_CALL_reg))
#define ISO_IC0_CLR_GEN_CALL_inst_adr                                                "0x005A"
#define ISO_IC0_CLR_GEN_CALL_inst                                                    0x005A
#define ISO_IC0_CLR_GEN_CALL_clr_gen_call_shift                                      (0)
#define ISO_IC0_CLR_GEN_CALL_clr_gen_call_mask                                       (0x00000001)
#define ISO_IC0_CLR_GEN_CALL_clr_gen_call(data)                                      (0x00000001&((data)<<0))
#define ISO_IC0_CLR_GEN_CALL_clr_gen_call_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_IC0_CLR_GEN_CALL_get_clr_gen_call(data)                                  ((0x00000001&(data))>>0)


#define ISO_IC0_ENABLE                                                               0x18007D6C
#define ISO_IC0_ENABLE_reg_addr                                                      "0xB8007D6C"
#define ISO_IC0_ENABLE_reg                                                           0xB8007D6C
#define set_ISO_IC0_ENABLE_reg(data)   (*((volatile unsigned int*) ISO_IC0_ENABLE_reg)=data)
#define get_ISO_IC0_ENABLE_reg   (*((volatile unsigned int*) ISO_IC0_ENABLE_reg))
#define ISO_IC0_ENABLE_inst_adr                                                      "0x005B"
#define ISO_IC0_ENABLE_inst                                                          0x005B
#define ISO_IC0_ENABLE_enable_shift                                                  (0)
#define ISO_IC0_ENABLE_enable_mask                                                   (0x00000001)
#define ISO_IC0_ENABLE_enable(data)                                                  (0x00000001&((data)<<0))
#define ISO_IC0_ENABLE_enable_src(data)                                              ((0x00000001&(data))>>0)
#define ISO_IC0_ENABLE_get_enable(data)                                              ((0x00000001&(data))>>0)


#define ISO_IC0_STATUS                                                               0x18007D70
#define ISO_IC0_STATUS_reg_addr                                                      "0xB8007D70"
#define ISO_IC0_STATUS_reg                                                           0xB8007D70
#define set_ISO_IC0_STATUS_reg(data)   (*((volatile unsigned int*) ISO_IC0_STATUS_reg)=data)
#define get_ISO_IC0_STATUS_reg   (*((volatile unsigned int*) ISO_IC0_STATUS_reg))
#define ISO_IC0_STATUS_inst_adr                                                      "0x005C"
#define ISO_IC0_STATUS_inst                                                          0x005C
#define ISO_IC0_STATUS_slv_activity_shift                                            (6)
#define ISO_IC0_STATUS_slv_activity_mask                                             (0x00000040)
#define ISO_IC0_STATUS_slv_activity(data)                                            (0x00000040&((data)<<6))
#define ISO_IC0_STATUS_slv_activity_src(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC0_STATUS_get_slv_activity(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC0_STATUS_mst_activity_shift                                            (5)
#define ISO_IC0_STATUS_mst_activity_mask                                             (0x00000020)
#define ISO_IC0_STATUS_mst_activity(data)                                            (0x00000020&((data)<<5))
#define ISO_IC0_STATUS_mst_activity_src(data)                                        ((0x00000020&(data))>>5)
#define ISO_IC0_STATUS_get_mst_activity(data)                                        ((0x00000020&(data))>>5)
#define ISO_IC0_STATUS_rff_shift                                                     (4)
#define ISO_IC0_STATUS_rff_mask                                                      (0x00000010)
#define ISO_IC0_STATUS_rff(data)                                                     (0x00000010&((data)<<4))
#define ISO_IC0_STATUS_rff_src(data)                                                 ((0x00000010&(data))>>4)
#define ISO_IC0_STATUS_get_rff(data)                                                 ((0x00000010&(data))>>4)
#define ISO_IC0_STATUS_rfne_shift                                                    (3)
#define ISO_IC0_STATUS_rfne_mask                                                     (0x00000008)
#define ISO_IC0_STATUS_rfne(data)                                                    (0x00000008&((data)<<3))
#define ISO_IC0_STATUS_rfne_src(data)                                                ((0x00000008&(data))>>3)
#define ISO_IC0_STATUS_get_rfne(data)                                                ((0x00000008&(data))>>3)
#define ISO_IC0_STATUS_tfe_shift                                                     (2)
#define ISO_IC0_STATUS_tfe_mask                                                      (0x00000004)
#define ISO_IC0_STATUS_tfe(data)                                                     (0x00000004&((data)<<2))
#define ISO_IC0_STATUS_tfe_src(data)                                                 ((0x00000004&(data))>>2)
#define ISO_IC0_STATUS_get_tfe(data)                                                 ((0x00000004&(data))>>2)
#define ISO_IC0_STATUS_tfnf_shift                                                    (1)
#define ISO_IC0_STATUS_tfnf_mask                                                     (0x00000002)
#define ISO_IC0_STATUS_tfnf(data)                                                    (0x00000002&((data)<<1))
#define ISO_IC0_STATUS_tfnf_src(data)                                                ((0x00000002&(data))>>1)
#define ISO_IC0_STATUS_get_tfnf(data)                                                ((0x00000002&(data))>>1)
#define ISO_IC0_STATUS_activity_shift                                                (0)
#define ISO_IC0_STATUS_activity_mask                                                 (0x00000001)
#define ISO_IC0_STATUS_activity(data)                                                (0x00000001&((data)<<0))
#define ISO_IC0_STATUS_activity_src(data)                                            ((0x00000001&(data))>>0)
#define ISO_IC0_STATUS_get_activity(data)                                            ((0x00000001&(data))>>0)


#define ISO_IC0_TXFLR                                                                0x18007D74
#define ISO_IC0_TXFLR_reg_addr                                                       "0xB8007D74"
#define ISO_IC0_TXFLR_reg                                                            0xB8007D74
#define set_ISO_IC0_TXFLR_reg(data)   (*((volatile unsigned int*) ISO_IC0_TXFLR_reg)=data)
#define get_ISO_IC0_TXFLR_reg   (*((volatile unsigned int*) ISO_IC0_TXFLR_reg))
#define ISO_IC0_TXFLR_inst_adr                                                       "0x005D"
#define ISO_IC0_TXFLR_inst                                                           0x005D
#define ISO_IC0_TXFLR_txflr_shift                                                    (0)
#define ISO_IC0_TXFLR_txflr_mask                                                     (0x0000000F)
#define ISO_IC0_TXFLR_txflr(data)                                                    (0x0000000F&((data)<<0))
#define ISO_IC0_TXFLR_txflr_src(data)                                                ((0x0000000F&(data))>>0)
#define ISO_IC0_TXFLR_get_txflr(data)                                                ((0x0000000F&(data))>>0)


#define ISO_IC0_RXFLR                                                                0x18007D78
#define ISO_IC0_RXFLR_reg_addr                                                       "0xB8007D78"
#define ISO_IC0_RXFLR_reg                                                            0xB8007D78
#define set_ISO_IC0_RXFLR_reg(data)   (*((volatile unsigned int*) ISO_IC0_RXFLR_reg)=data)
#define get_ISO_IC0_RXFLR_reg   (*((volatile unsigned int*) ISO_IC0_RXFLR_reg))
#define ISO_IC0_RXFLR_inst_adr                                                       "0x005E"
#define ISO_IC0_RXFLR_inst                                                           0x005E
#define ISO_IC0_RXFLR_rxflr_shift                                                    (0)
#define ISO_IC0_RXFLR_rxflr_mask                                                     (0x0000000F)
#define ISO_IC0_RXFLR_rxflr(data)                                                    (0x0000000F&((data)<<0))
#define ISO_IC0_RXFLR_rxflr_src(data)                                                ((0x0000000F&(data))>>0)
#define ISO_IC0_RXFLR_get_rxflr(data)                                                ((0x0000000F&(data))>>0)


#define ISO_IC0_SDA_HOLD                                                             0x18007D7C
#define ISO_IC0_SDA_HOLD_reg_addr                                                    "0xB8007D7C"
#define ISO_IC0_SDA_HOLD_reg                                                         0xB8007D7C
#define set_ISO_IC0_SDA_HOLD_reg(data)   (*((volatile unsigned int*) ISO_IC0_SDA_HOLD_reg)=data)
#define get_ISO_IC0_SDA_HOLD_reg   (*((volatile unsigned int*) ISO_IC0_SDA_HOLD_reg))
#define ISO_IC0_SDA_HOLD_inst_adr                                                    "0x005F"
#define ISO_IC0_SDA_HOLD_inst                                                        0x005F
#define ISO_IC0_SDA_HOLD_ic_sda_hold_shift                                           (0)
#define ISO_IC0_SDA_HOLD_ic_sda_hold_mask                                            (0x0000FFFF)
#define ISO_IC0_SDA_HOLD_ic_sda_hold(data)                                           (0x0000FFFF&((data)<<0))
#define ISO_IC0_SDA_HOLD_ic_sda_hold_src(data)                                       ((0x0000FFFF&(data))>>0)
#define ISO_IC0_SDA_HOLD_get_ic_sda_hold(data)                                       ((0x0000FFFF&(data))>>0)


#define ISO_IC0_TX_ABRT_SOURCE                                                       0x18007D80
#define ISO_IC0_TX_ABRT_SOURCE_reg_addr                                              "0xB8007D80"
#define ISO_IC0_TX_ABRT_SOURCE_reg                                                   0xB8007D80
#define set_ISO_IC0_TX_ABRT_SOURCE_reg(data)   (*((volatile unsigned int*) ISO_IC0_TX_ABRT_SOURCE_reg)=data)
#define get_ISO_IC0_TX_ABRT_SOURCE_reg   (*((volatile unsigned int*) ISO_IC0_TX_ABRT_SOURCE_reg))
#define ISO_IC0_TX_ABRT_SOURCE_inst_adr                                              "0x0060"
#define ISO_IC0_TX_ABRT_SOURCE_inst                                                  0x0060
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slvrd_intx_shift                                 (15)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slvrd_intx_mask                                  (0x00008000)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slvrd_intx(data)                                 (0x00008000&((data)<<15))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slvrd_intx_src(data)                             ((0x00008000&(data))>>15)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_slvrd_intx(data)                             ((0x00008000&(data))>>15)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slv_arblost_shift                                (14)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slv_arblost_mask                                 (0x00004000)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slv_arblost(data)                                (0x00004000&((data)<<14))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slv_arblost_src(data)                            ((0x00004000&(data))>>14)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_slv_arblost(data)                            ((0x00004000&(data))>>14)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slvflush_txfifo_shift                            (13)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slvflush_txfifo_mask                             (0x00002000)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slvflush_txfifo(data)                            (0x00002000&((data)<<13))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_slvflush_txfifo_src(data)                        ((0x00002000&(data))>>13)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_slvflush_txfifo(data)                        ((0x00002000&(data))>>13)
#define ISO_IC0_TX_ABRT_SOURCE_arb_lost_shift                                        (12)
#define ISO_IC0_TX_ABRT_SOURCE_arb_lost_mask                                         (0x00001000)
#define ISO_IC0_TX_ABRT_SOURCE_arb_lost(data)                                        (0x00001000&((data)<<12))
#define ISO_IC0_TX_ABRT_SOURCE_arb_lost_src(data)                                    ((0x00001000&(data))>>12)
#define ISO_IC0_TX_ABRT_SOURCE_get_arb_lost(data)                                    ((0x00001000&(data))>>12)
#define ISO_IC0_TX_ABRT_SOURCE_arb_master_dis_shift                                  (11)
#define ISO_IC0_TX_ABRT_SOURCE_arb_master_dis_mask                                   (0x00000800)
#define ISO_IC0_TX_ABRT_SOURCE_arb_master_dis(data)                                  (0x00000800&((data)<<11))
#define ISO_IC0_TX_ABRT_SOURCE_arb_master_dis_src(data)                              ((0x00000800&(data))>>11)
#define ISO_IC0_TX_ABRT_SOURCE_get_arb_master_dis(data)                              ((0x00000800&(data))>>11)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_shift                             (10)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_mask                              (0x00000400)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10b_rd_norstrt(data)                             (0x00000400&((data)<<10))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_src(data)                         ((0x00000400&(data))>>10)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_10b_rd_norstrt(data)                         ((0x00000400&(data))>>10)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_sbyte_norstrt_shift                              (9)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_sbyte_norstrt_mask                               (0x00000200)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_sbyte_norstrt(data)                              (0x00000200&((data)<<9))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_sbyte_norstrt_src(data)                          ((0x00000200&(data))>>9)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_sbyte_norstrt(data)                          ((0x00000200&(data))>>9)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_hs_norstrt_shift                                 (8)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_hs_norstrt_mask                                  (0x00000100)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_hs_norstrt(data)                                 (0x00000100&((data)<<8))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_hs_norstrt_src(data)                             ((0x00000100&(data))>>8)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_hs_norstrt(data)                             ((0x00000100&(data))>>8)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_sbyte_ackdet_shift                               (7)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_sbyte_ackdet_mask                                (0x00000080)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_sbyte_ackdet(data)                               (0x00000080&((data)<<7))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_sbyte_ackdet_src(data)                           ((0x00000080&(data))>>7)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_sbyte_ackdet(data)                           ((0x00000080&(data))>>7)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_hs_ackdet_shift                                  (6)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_hs_ackdet_mask                                   (0x00000040)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_hs_ackdet(data)                                  (0x00000040&((data)<<6))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_hs_ackdet_src(data)                              ((0x00000040&(data))>>6)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_hs_ackdet(data)                              ((0x00000040&(data))>>6)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_gcall_read_shift                                 (5)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_gcall_read_mask                                  (0x00000020)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_gcall_read(data)                                 (0x00000020&((data)<<5))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_gcall_read_src(data)                             ((0x00000020&(data))>>5)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_gcall_read(data)                             ((0x00000020&(data))>>5)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_gcall_noack_shift                                (4)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_gcall_noack_mask                                 (0x00000010)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_gcall_noack(data)                                (0x00000010&((data)<<4))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_gcall_noack_src(data)                            ((0x00000010&(data))>>4)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_gcall_noack(data)                            ((0x00000010&(data))>>4)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_txdata_noack_shift                               (3)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_txdata_noack_mask                                (0x00000008)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_txdata_noack(data)                               (0x00000008&((data)<<3))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_txdata_noack_src(data)                           ((0x00000008&(data))>>3)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_txdata_noack(data)                           ((0x00000008&(data))>>3)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10addr2_noack_shift                              (2)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10addr2_noack_mask                               (0x00000004)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10addr2_noack(data)                              (0x00000004&((data)<<2))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10addr2_noack_src(data)                          ((0x00000004&(data))>>2)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_10addr2_noack(data)                          ((0x00000004&(data))>>2)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10addr1_noack_shift                              (1)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10addr1_noack_mask                               (0x00000002)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10addr1_noack(data)                              (0x00000002&((data)<<1))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_10addr1_noack_src(data)                          ((0x00000002&(data))>>1)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_10addr1_noack(data)                          ((0x00000002&(data))>>1)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_7b_addr_noack_shift                              (0)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_7b_addr_noack_mask                               (0x00000001)
#define ISO_IC0_TX_ABRT_SOURCE_abrt_7b_addr_noack(data)                              (0x00000001&((data)<<0))
#define ISO_IC0_TX_ABRT_SOURCE_abrt_7b_addr_noack_src(data)                          ((0x00000001&(data))>>0)
#define ISO_IC0_TX_ABRT_SOURCE_get_abrt_7b_addr_noack(data)                          ((0x00000001&(data))>>0)


#define ISO_IC0_SLV_DATA_NACK_ONLY                                                   0x18007D84
#define ISO_IC0_SLV_DATA_NACK_ONLY_reg_addr                                          "0xB8007D84"
#define ISO_IC0_SLV_DATA_NACK_ONLY_reg                                               0xB8007D84
#define set_ISO_IC0_SLV_DATA_NACK_ONLY_reg(data)   (*((volatile unsigned int*) ISO_IC0_SLV_DATA_NACK_ONLY_reg)=data)
#define get_ISO_IC0_SLV_DATA_NACK_ONLY_reg   (*((volatile unsigned int*) ISO_IC0_SLV_DATA_NACK_ONLY_reg))
#define ISO_IC0_SLV_DATA_NACK_ONLY_inst_adr                                          "0x0061"
#define ISO_IC0_SLV_DATA_NACK_ONLY_inst                                              0x0061
#define ISO_IC0_SLV_DATA_NACK_ONLY_nack_shift                                        (0)
#define ISO_IC0_SLV_DATA_NACK_ONLY_nack_mask                                         (0x00000001)
#define ISO_IC0_SLV_DATA_NACK_ONLY_nack(data)                                        (0x00000001&((data)<<0))
#define ISO_IC0_SLV_DATA_NACK_ONLY_nack_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC0_SLV_DATA_NACK_ONLY_get_nack(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC0_DMA_CR                                                               0x18007D88
#define ISO_IC0_DMA_CR_reg_addr                                                      "0xB8007D88"
#define ISO_IC0_DMA_CR_reg                                                           0xB8007D88
#define set_ISO_IC0_DMA_CR_reg(data)   (*((volatile unsigned int*) ISO_IC0_DMA_CR_reg)=data)
#define get_ISO_IC0_DMA_CR_reg   (*((volatile unsigned int*) ISO_IC0_DMA_CR_reg))
#define ISO_IC0_DMA_CR_inst_adr                                                      "0x0062"
#define ISO_IC0_DMA_CR_inst                                                          0x0062
#define ISO_IC0_DMA_CR_tdmae_shift                                                   (1)
#define ISO_IC0_DMA_CR_tdmae_mask                                                    (0x00000002)
#define ISO_IC0_DMA_CR_tdmae(data)                                                   (0x00000002&((data)<<1))
#define ISO_IC0_DMA_CR_tdmae_src(data)                                               ((0x00000002&(data))>>1)
#define ISO_IC0_DMA_CR_get_tdmae(data)                                               ((0x00000002&(data))>>1)
#define ISO_IC0_DMA_CR_rdmae_shift                                                   (0)
#define ISO_IC0_DMA_CR_rdmae_mask                                                    (0x00000001)
#define ISO_IC0_DMA_CR_rdmae(data)                                                   (0x00000001&((data)<<0))
#define ISO_IC0_DMA_CR_rdmae_src(data)                                               ((0x00000001&(data))>>0)
#define ISO_IC0_DMA_CR_get_rdmae(data)                                               ((0x00000001&(data))>>0)


#define ISO_IC0_DMA_TDLR                                                             0x18007D8C
#define ISO_IC0_DMA_TDLR_reg_addr                                                    "0xB8007D8C"
#define ISO_IC0_DMA_TDLR_reg                                                         0xB8007D8C
#define set_ISO_IC0_DMA_TDLR_reg(data)   (*((volatile unsigned int*) ISO_IC0_DMA_TDLR_reg)=data)
#define get_ISO_IC0_DMA_TDLR_reg   (*((volatile unsigned int*) ISO_IC0_DMA_TDLR_reg))
#define ISO_IC0_DMA_TDLR_inst_adr                                                    "0x0063"
#define ISO_IC0_DMA_TDLR_inst                                                        0x0063
#define ISO_IC0_DMA_TDLR_dmatdl_shift                                                (0)
#define ISO_IC0_DMA_TDLR_dmatdl_mask                                                 (0x00000007)
#define ISO_IC0_DMA_TDLR_dmatdl(data)                                                (0x00000007&((data)<<0))
#define ISO_IC0_DMA_TDLR_dmatdl_src(data)                                            ((0x00000007&(data))>>0)
#define ISO_IC0_DMA_TDLR_get_dmatdl(data)                                            ((0x00000007&(data))>>0)


#define ISO_IC0_DMA_RDLR                                                             0x18007D90
#define ISO_IC0_DMA_RDLR_reg_addr                                                    "0xB8007D90"
#define ISO_IC0_DMA_RDLR_reg                                                         0xB8007D90
#define set_ISO_IC0_DMA_RDLR_reg(data)   (*((volatile unsigned int*) ISO_IC0_DMA_RDLR_reg)=data)
#define get_ISO_IC0_DMA_RDLR_reg   (*((volatile unsigned int*) ISO_IC0_DMA_RDLR_reg))
#define ISO_IC0_DMA_RDLR_inst_adr                                                    "0x0064"
#define ISO_IC0_DMA_RDLR_inst                                                        0x0064
#define ISO_IC0_DMA_RDLR_dmardl_shift                                                (0)
#define ISO_IC0_DMA_RDLR_dmardl_mask                                                 (0x0000000F)
#define ISO_IC0_DMA_RDLR_dmardl(data)                                                (0x0000000F&((data)<<0))
#define ISO_IC0_DMA_RDLR_dmardl_src(data)                                            ((0x0000000F&(data))>>0)
#define ISO_IC0_DMA_RDLR_get_dmardl(data)                                            ((0x0000000F&(data))>>0)


#define ISO_IC0_SDA_SETUP                                                            0x18007D94
#define ISO_IC0_SDA_SETUP_reg_addr                                                   "0xB8007D94"
#define ISO_IC0_SDA_SETUP_reg                                                        0xB8007D94
#define set_ISO_IC0_SDA_SETUP_reg(data)   (*((volatile unsigned int*) ISO_IC0_SDA_SETUP_reg)=data)
#define get_ISO_IC0_SDA_SETUP_reg   (*((volatile unsigned int*) ISO_IC0_SDA_SETUP_reg))
#define ISO_IC0_SDA_SETUP_inst_adr                                                   "0x0065"
#define ISO_IC0_SDA_SETUP_inst                                                       0x0065
#define ISO_IC0_SDA_SETUP_sda_setup_shift                                            (0)
#define ISO_IC0_SDA_SETUP_sda_setup_mask                                             (0x000000FF)
#define ISO_IC0_SDA_SETUP_sda_setup(data)                                            (0x000000FF&((data)<<0))
#define ISO_IC0_SDA_SETUP_sda_setup_src(data)                                        ((0x000000FF&(data))>>0)
#define ISO_IC0_SDA_SETUP_get_sda_setup(data)                                        ((0x000000FF&(data))>>0)


#define ISO_IC0_ACK_GENERAL_CALL                                                     0x18007D98
#define ISO_IC0_ACK_GENERAL_CALL_reg_addr                                            "0xB8007D98"
#define ISO_IC0_ACK_GENERAL_CALL_reg                                                 0xB8007D98
#define set_ISO_IC0_ACK_GENERAL_CALL_reg(data)   (*((volatile unsigned int*) ISO_IC0_ACK_GENERAL_CALL_reg)=data)
#define get_ISO_IC0_ACK_GENERAL_CALL_reg   (*((volatile unsigned int*) ISO_IC0_ACK_GENERAL_CALL_reg))
#define ISO_IC0_ACK_GENERAL_CALL_inst_adr                                            "0x0066"
#define ISO_IC0_ACK_GENERAL_CALL_inst                                                0x0066
#define ISO_IC0_ACK_GENERAL_CALL_ack_gen_call_shift                                  (0)
#define ISO_IC0_ACK_GENERAL_CALL_ack_gen_call_mask                                   (0x00000001)
#define ISO_IC0_ACK_GENERAL_CALL_ack_gen_call(data)                                  (0x00000001&((data)<<0))
#define ISO_IC0_ACK_GENERAL_CALL_ack_gen_call_src(data)                              ((0x00000001&(data))>>0)
#define ISO_IC0_ACK_GENERAL_CALL_get_ack_gen_call(data)                              ((0x00000001&(data))>>0)


#define ISO_IC0_ENABLE_STATUS                                                        0x18007D9C
#define ISO_IC0_ENABLE_STATUS_reg_addr                                               "0xB8007D9C"
#define ISO_IC0_ENABLE_STATUS_reg                                                    0xB8007D9C
#define set_ISO_IC0_ENABLE_STATUS_reg(data)   (*((volatile unsigned int*) ISO_IC0_ENABLE_STATUS_reg)=data)
#define get_ISO_IC0_ENABLE_STATUS_reg   (*((volatile unsigned int*) ISO_IC0_ENABLE_STATUS_reg))
#define ISO_IC0_ENABLE_STATUS_inst_adr                                               "0x0067"
#define ISO_IC0_ENABLE_STATUS_inst                                                   0x0067
#define ISO_IC0_ENABLE_STATUS_slv_rx_data_lost_shift                                 (2)
#define ISO_IC0_ENABLE_STATUS_slv_rx_data_lost_mask                                  (0x00000004)
#define ISO_IC0_ENABLE_STATUS_slv_rx_data_lost(data)                                 (0x00000004&((data)<<2))
#define ISO_IC0_ENABLE_STATUS_slv_rx_data_lost_src(data)                             ((0x00000004&(data))>>2)
#define ISO_IC0_ENABLE_STATUS_get_slv_rx_data_lost(data)                             ((0x00000004&(data))>>2)
#define ISO_IC0_ENABLE_STATUS_slv_disabled_whi_shift                                 (1)
#define ISO_IC0_ENABLE_STATUS_slv_disabled_whi_mask                                  (0x00000002)
#define ISO_IC0_ENABLE_STATUS_slv_disabled_whi(data)                                 (0x00000002&((data)<<1))
#define ISO_IC0_ENABLE_STATUS_slv_disabled_whi_src(data)                             ((0x00000002&(data))>>1)
#define ISO_IC0_ENABLE_STATUS_get_slv_disabled_whi(data)                             ((0x00000002&(data))>>1)
#define ISO_IC0_ENABLE_STATUS_ic_en_shift                                            (0)
#define ISO_IC0_ENABLE_STATUS_ic_en_mask                                             (0x00000001)
#define ISO_IC0_ENABLE_STATUS_ic_en(data)                                            (0x00000001&((data)<<0))
#define ISO_IC0_ENABLE_STATUS_ic_en_src(data)                                        ((0x00000001&(data))>>0)
#define ISO_IC0_ENABLE_STATUS_get_ic_en(data)                                        ((0x00000001&(data))>>0)


#define ISO_IC0_COMP_PARAM_1                                                         0x18007DF4
#define ISO_IC0_COMP_PARAM_1_reg_addr                                                "0xB8007DF4"
#define ISO_IC0_COMP_PARAM_1_reg                                                     0xB8007DF4
#define set_ISO_IC0_COMP_PARAM_1_reg(data)   (*((volatile unsigned int*) ISO_IC0_COMP_PARAM_1_reg)=data)
#define get_ISO_IC0_COMP_PARAM_1_reg   (*((volatile unsigned int*) ISO_IC0_COMP_PARAM_1_reg))
#define ISO_IC0_COMP_PARAM_1_inst_adr                                                "0x007D"
#define ISO_IC0_COMP_PARAM_1_inst                                                    0x007D
#define ISO_IC0_COMP_PARAM_1_tx_buffer_depth_shift                                   (16)
#define ISO_IC0_COMP_PARAM_1_tx_buffer_depth_mask                                    (0x00FF0000)
#define ISO_IC0_COMP_PARAM_1_tx_buffer_depth(data)                                   (0x00FF0000&((data)<<16))
#define ISO_IC0_COMP_PARAM_1_tx_buffer_depth_src(data)                               ((0x00FF0000&(data))>>16)
#define ISO_IC0_COMP_PARAM_1_get_tx_buffer_depth(data)                               ((0x00FF0000&(data))>>16)
#define ISO_IC0_COMP_PARAM_1_rx_buffer_depth_shift                                   (8)
#define ISO_IC0_COMP_PARAM_1_rx_buffer_depth_mask                                    (0x0000FF00)
#define ISO_IC0_COMP_PARAM_1_rx_buffer_depth(data)                                   (0x0000FF00&((data)<<8))
#define ISO_IC0_COMP_PARAM_1_rx_buffer_depth_src(data)                               ((0x0000FF00&(data))>>8)
#define ISO_IC0_COMP_PARAM_1_get_rx_buffer_depth(data)                               ((0x0000FF00&(data))>>8)
#define ISO_IC0_COMP_PARAM_1_add_encoded_params_shift                                (7)
#define ISO_IC0_COMP_PARAM_1_add_encoded_params_mask                                 (0x00000080)
#define ISO_IC0_COMP_PARAM_1_add_encoded_params(data)                                (0x00000080&((data)<<7))
#define ISO_IC0_COMP_PARAM_1_add_encoded_params_src(data)                            ((0x00000080&(data))>>7)
#define ISO_IC0_COMP_PARAM_1_get_add_encoded_params(data)                            ((0x00000080&(data))>>7)
#define ISO_IC0_COMP_PARAM_1_has_dma_shift                                           (6)
#define ISO_IC0_COMP_PARAM_1_has_dma_mask                                            (0x00000040)
#define ISO_IC0_COMP_PARAM_1_has_dma(data)                                           (0x00000040&((data)<<6))
#define ISO_IC0_COMP_PARAM_1_has_dma_src(data)                                       ((0x00000040&(data))>>6)
#define ISO_IC0_COMP_PARAM_1_get_has_dma(data)                                       ((0x00000040&(data))>>6)
#define ISO_IC0_COMP_PARAM_1_intr_io_shift                                           (5)
#define ISO_IC0_COMP_PARAM_1_intr_io_mask                                            (0x00000020)
#define ISO_IC0_COMP_PARAM_1_intr_io(data)                                           (0x00000020&((data)<<5))
#define ISO_IC0_COMP_PARAM_1_intr_io_src(data)                                       ((0x00000020&(data))>>5)
#define ISO_IC0_COMP_PARAM_1_get_intr_io(data)                                       ((0x00000020&(data))>>5)
#define ISO_IC0_COMP_PARAM_1_hc_count_values_shift                                   (4)
#define ISO_IC0_COMP_PARAM_1_hc_count_values_mask                                    (0x00000010)
#define ISO_IC0_COMP_PARAM_1_hc_count_values(data)                                   (0x00000010&((data)<<4))
#define ISO_IC0_COMP_PARAM_1_hc_count_values_src(data)                               ((0x00000010&(data))>>4)
#define ISO_IC0_COMP_PARAM_1_get_hc_count_values(data)                               ((0x00000010&(data))>>4)
#define ISO_IC0_COMP_PARAM_1_max_speed_mode_shift                                    (2)
#define ISO_IC0_COMP_PARAM_1_max_speed_mode_mask                                     (0x0000000C)
#define ISO_IC0_COMP_PARAM_1_max_speed_mode(data)                                    (0x0000000C&((data)<<2))
#define ISO_IC0_COMP_PARAM_1_max_speed_mode_src(data)                                ((0x0000000C&(data))>>2)
#define ISO_IC0_COMP_PARAM_1_get_max_speed_mode(data)                                ((0x0000000C&(data))>>2)
#define ISO_IC0_COMP_PARAM_1_apb_data_width_shift                                    (0)
#define ISO_IC0_COMP_PARAM_1_apb_data_width_mask                                     (0x00000003)
#define ISO_IC0_COMP_PARAM_1_apb_data_width(data)                                    (0x00000003&((data)<<0))
#define ISO_IC0_COMP_PARAM_1_apb_data_width_src(data)                                ((0x00000003&(data))>>0)
#define ISO_IC0_COMP_PARAM_1_get_apb_data_width(data)                                ((0x00000003&(data))>>0)


#define ISO_IC0_COMP_VERSION                                                         0x18007DF8
#define ISO_IC0_COMP_VERSION_reg_addr                                                "0xB8007DF8"
#define ISO_IC0_COMP_VERSION_reg                                                     0xB8007DF8
#define set_ISO_IC0_COMP_VERSION_reg(data)   (*((volatile unsigned int*) ISO_IC0_COMP_VERSION_reg)=data)
#define get_ISO_IC0_COMP_VERSION_reg   (*((volatile unsigned int*) ISO_IC0_COMP_VERSION_reg))
#define ISO_IC0_COMP_VERSION_inst_adr                                                "0x007E"
#define ISO_IC0_COMP_VERSION_inst                                                    0x007E
#define ISO_IC0_COMP_VERSION_ic_comp_version_shift                                   (0)
#define ISO_IC0_COMP_VERSION_ic_comp_version_mask                                    (0xFFFFFFFF)
#define ISO_IC0_COMP_VERSION_ic_comp_version(data)                                   (0xFFFFFFFF&((data)<<0))
#define ISO_IC0_COMP_VERSION_ic_comp_version_src(data)                               ((0xFFFFFFFF&(data))>>0)
#define ISO_IC0_COMP_VERSION_get_ic_comp_version(data)                               ((0xFFFFFFFF&(data))>>0)


#define ISO_IC0_COMP_TYPE                                                            0x18007DFC
#define ISO_IC0_COMP_TYPE_reg_addr                                                   "0xB8007DFC"
#define ISO_IC0_COMP_TYPE_reg                                                        0xB8007DFC
#define set_ISO_IC0_COMP_TYPE_reg(data)   (*((volatile unsigned int*) ISO_IC0_COMP_TYPE_reg)=data)
#define get_ISO_IC0_COMP_TYPE_reg   (*((volatile unsigned int*) ISO_IC0_COMP_TYPE_reg))
#define ISO_IC0_COMP_TYPE_inst_adr                                                   "0x007F"
#define ISO_IC0_COMP_TYPE_inst                                                       0x007F
#define ISO_IC0_COMP_TYPE_ic_comp_type_shift                                         (0)
#define ISO_IC0_COMP_TYPE_ic_comp_type_mask                                          (0xFFFFFFFF)
#define ISO_IC0_COMP_TYPE_ic_comp_type(data)                                         (0xFFFFFFFF&((data)<<0))
#define ISO_IC0_COMP_TYPE_ic_comp_type_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define ISO_IC0_COMP_TYPE_get_ic_comp_type(data)                                     ((0xFFFFFFFF&(data))>>0)


#define ISO_IC6_CON                                                                  0x18007E00
#define ISO_IC6_CON_reg_addr                                                         "0xB8007E00"
#define ISO_IC6_CON_reg                                                              0xB8007E00
#define set_ISO_IC6_CON_reg(data)   (*((volatile unsigned int*) ISO_IC6_CON_reg)=data)
#define get_ISO_IC6_CON_reg   (*((volatile unsigned int*) ISO_IC6_CON_reg))
#define ISO_IC6_CON_inst_adr                                                         "0x0080"
#define ISO_IC6_CON_inst                                                             0x0080
#define ISO_IC6_CON_ic_slave_disable_shift                                           (6)
#define ISO_IC6_CON_ic_slave_disable_mask                                            (0x00000040)
#define ISO_IC6_CON_ic_slave_disable(data)                                           (0x00000040&((data)<<6))
#define ISO_IC6_CON_ic_slave_disable_src(data)                                       ((0x00000040&(data))>>6)
#define ISO_IC6_CON_get_ic_slave_disable(data)                                       ((0x00000040&(data))>>6)
#define ISO_IC6_CON_ic_restart_en_shift                                              (5)
#define ISO_IC6_CON_ic_restart_en_mask                                               (0x00000020)
#define ISO_IC6_CON_ic_restart_en(data)                                              (0x00000020&((data)<<5))
#define ISO_IC6_CON_ic_restart_en_src(data)                                          ((0x00000020&(data))>>5)
#define ISO_IC6_CON_get_ic_restart_en(data)                                          ((0x00000020&(data))>>5)
#define ISO_IC6_CON_ic_10bitaddr_master_shift                                        (4)
#define ISO_IC6_CON_ic_10bitaddr_master_mask                                         (0x00000010)
#define ISO_IC6_CON_ic_10bitaddr_master(data)                                        (0x00000010&((data)<<4))
#define ISO_IC6_CON_ic_10bitaddr_master_src(data)                                    ((0x00000010&(data))>>4)
#define ISO_IC6_CON_get_ic_10bitaddr_master(data)                                    ((0x00000010&(data))>>4)
#define ISO_IC6_CON_ic_10bitaddr_slave_shift                                         (3)
#define ISO_IC6_CON_ic_10bitaddr_slave_mask                                          (0x00000008)
#define ISO_IC6_CON_ic_10bitaddr_slave(data)                                         (0x00000008&((data)<<3))
#define ISO_IC6_CON_ic_10bitaddr_slave_src(data)                                     ((0x00000008&(data))>>3)
#define ISO_IC6_CON_get_ic_10bitaddr_slave(data)                                     ((0x00000008&(data))>>3)
#define ISO_IC6_CON_speed_shift                                                      (1)
#define ISO_IC6_CON_speed_mask                                                       (0x00000006)
#define ISO_IC6_CON_speed(data)                                                      (0x00000006&((data)<<1))
#define ISO_IC6_CON_speed_src(data)                                                  ((0x00000006&(data))>>1)
#define ISO_IC6_CON_get_speed(data)                                                  ((0x00000006&(data))>>1)
#define ISO_IC6_CON_master_mode_shift                                                (0)
#define ISO_IC6_CON_master_mode_mask                                                 (0x00000001)
#define ISO_IC6_CON_master_mode(data)                                                (0x00000001&((data)<<0))
#define ISO_IC6_CON_master_mode_src(data)                                            ((0x00000001&(data))>>0)
#define ISO_IC6_CON_get_master_mode(data)                                            ((0x00000001&(data))>>0)


#define ISO_IC6_TAR                                                                  0x18007E04
#define ISO_IC6_TAR_reg_addr                                                         "0xB8007E04"
#define ISO_IC6_TAR_reg                                                              0xB8007E04
#define set_ISO_IC6_TAR_reg(data)   (*((volatile unsigned int*) ISO_IC6_TAR_reg)=data)
#define get_ISO_IC6_TAR_reg   (*((volatile unsigned int*) ISO_IC6_TAR_reg))
#define ISO_IC6_TAR_inst_adr                                                         "0x0081"
#define ISO_IC6_TAR_inst                                                             0x0081
#define ISO_IC6_TAR_ic_10bitaddr_master_shift                                        (12)
#define ISO_IC6_TAR_ic_10bitaddr_master_mask                                         (0x00001000)
#define ISO_IC6_TAR_ic_10bitaddr_master(data)                                        (0x00001000&((data)<<12))
#define ISO_IC6_TAR_ic_10bitaddr_master_src(data)                                    ((0x00001000&(data))>>12)
#define ISO_IC6_TAR_get_ic_10bitaddr_master(data)                                    ((0x00001000&(data))>>12)
#define ISO_IC6_TAR_special_shift                                                    (11)
#define ISO_IC6_TAR_special_mask                                                     (0x00000800)
#define ISO_IC6_TAR_special(data)                                                    (0x00000800&((data)<<11))
#define ISO_IC6_TAR_special_src(data)                                                ((0x00000800&(data))>>11)
#define ISO_IC6_TAR_get_special(data)                                                ((0x00000800&(data))>>11)
#define ISO_IC6_TAR_gc_or_start_shift                                                (10)
#define ISO_IC6_TAR_gc_or_start_mask                                                 (0x00000400)
#define ISO_IC6_TAR_gc_or_start(data)                                                (0x00000400&((data)<<10))
#define ISO_IC6_TAR_gc_or_start_src(data)                                            ((0x00000400&(data))>>10)
#define ISO_IC6_TAR_get_gc_or_start(data)                                            ((0x00000400&(data))>>10)
#define ISO_IC6_TAR_ic_tar_shift                                                     (0)
#define ISO_IC6_TAR_ic_tar_mask                                                      (0x000003FF)
#define ISO_IC6_TAR_ic_tar(data)                                                     (0x000003FF&((data)<<0))
#define ISO_IC6_TAR_ic_tar_src(data)                                                 ((0x000003FF&(data))>>0)
#define ISO_IC6_TAR_get_ic_tar(data)                                                 ((0x000003FF&(data))>>0)


#define ISO_IC6_SAR                                                                  0x18007E08
#define ISO_IC6_SAR_reg_addr                                                         "0xB8007E08"
#define ISO_IC6_SAR_reg                                                              0xB8007E08
#define set_ISO_IC6_SAR_reg(data)   (*((volatile unsigned int*) ISO_IC6_SAR_reg)=data)
#define get_ISO_IC6_SAR_reg   (*((volatile unsigned int*) ISO_IC6_SAR_reg))
#define ISO_IC6_SAR_inst_adr                                                         "0x0082"
#define ISO_IC6_SAR_inst                                                             0x0082
#define ISO_IC6_SAR_ic_sar_shift                                                     (0)
#define ISO_IC6_SAR_ic_sar_mask                                                      (0x000003FF)
#define ISO_IC6_SAR_ic_sar(data)                                                     (0x000003FF&((data)<<0))
#define ISO_IC6_SAR_ic_sar_src(data)                                                 ((0x000003FF&(data))>>0)
#define ISO_IC6_SAR_get_ic_sar(data)                                                 ((0x000003FF&(data))>>0)


#define ISO_IC6_HS_MADDR                                                             0x18007E0C
#define ISO_IC6_HS_MADDR_reg_addr                                                    "0xB8007E0C"
#define ISO_IC6_HS_MADDR_reg                                                         0xB8007E0C
#define set_ISO_IC6_HS_MADDR_reg(data)   (*((volatile unsigned int*) ISO_IC6_HS_MADDR_reg)=data)
#define get_ISO_IC6_HS_MADDR_reg   (*((volatile unsigned int*) ISO_IC6_HS_MADDR_reg))
#define ISO_IC6_HS_MADDR_inst_adr                                                    "0x0083"
#define ISO_IC6_HS_MADDR_inst                                                        0x0083
#define ISO_IC6_HS_MADDR_ic_hs_mar_shift                                             (0)
#define ISO_IC6_HS_MADDR_ic_hs_mar_mask                                              (0x00000007)
#define ISO_IC6_HS_MADDR_ic_hs_mar(data)                                             (0x00000007&((data)<<0))
#define ISO_IC6_HS_MADDR_ic_hs_mar_src(data)                                         ((0x00000007&(data))>>0)
#define ISO_IC6_HS_MADDR_get_ic_hs_mar(data)                                         ((0x00000007&(data))>>0)


#define ISO_IC6_DATA_CMD                                                             0x18007E10
#define ISO_IC6_DATA_CMD_reg_addr                                                    "0xB8007E10"
#define ISO_IC6_DATA_CMD_reg                                                         0xB8007E10
#define set_ISO_IC6_DATA_CMD_reg(data)   (*((volatile unsigned int*) ISO_IC6_DATA_CMD_reg)=data)
#define get_ISO_IC6_DATA_CMD_reg   (*((volatile unsigned int*) ISO_IC6_DATA_CMD_reg))
#define ISO_IC6_DATA_CMD_inst_adr                                                    "0x0084"
#define ISO_IC6_DATA_CMD_inst                                                        0x0084
#define ISO_IC6_DATA_CMD_restart_shift                                               (10)
#define ISO_IC6_DATA_CMD_restart_mask                                                (0x00000400)
#define ISO_IC6_DATA_CMD_restart(data)                                               (0x00000400&((data)<<10))
#define ISO_IC6_DATA_CMD_restart_src(data)                                           ((0x00000400&(data))>>10)
#define ISO_IC6_DATA_CMD_get_restart(data)                                           ((0x00000400&(data))>>10)
#define ISO_IC6_DATA_CMD_stop_shift                                                  (9)
#define ISO_IC6_DATA_CMD_stop_mask                                                   (0x00000200)
#define ISO_IC6_DATA_CMD_stop(data)                                                  (0x00000200&((data)<<9))
#define ISO_IC6_DATA_CMD_stop_src(data)                                              ((0x00000200&(data))>>9)
#define ISO_IC6_DATA_CMD_get_stop(data)                                              ((0x00000200&(data))>>9)
#define ISO_IC6_DATA_CMD_cmd_shift                                                   (8)
#define ISO_IC6_DATA_CMD_cmd_mask                                                    (0x00000100)
#define ISO_IC6_DATA_CMD_cmd(data)                                                   (0x00000100&((data)<<8))
#define ISO_IC6_DATA_CMD_cmd_src(data)                                               ((0x00000100&(data))>>8)
#define ISO_IC6_DATA_CMD_get_cmd(data)                                               ((0x00000100&(data))>>8)
#define ISO_IC6_DATA_CMD_dat_shift                                                   (0)
#define ISO_IC6_DATA_CMD_dat_mask                                                    (0x000000FF)
#define ISO_IC6_DATA_CMD_dat(data)                                                   (0x000000FF&((data)<<0))
#define ISO_IC6_DATA_CMD_dat_src(data)                                               ((0x000000FF&(data))>>0)
#define ISO_IC6_DATA_CMD_get_dat(data)                                               ((0x000000FF&(data))>>0)


#define ISO_IC6_SS_SCL_HCNT                                                          0x18007E14
#define ISO_IC6_SS_SCL_HCNT_reg_addr                                                 "0xB8007E14"
#define ISO_IC6_SS_SCL_HCNT_reg                                                      0xB8007E14
#define set_ISO_IC6_SS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) ISO_IC6_SS_SCL_HCNT_reg)=data)
#define get_ISO_IC6_SS_SCL_HCNT_reg   (*((volatile unsigned int*) ISO_IC6_SS_SCL_HCNT_reg))
#define ISO_IC6_SS_SCL_HCNT_inst_adr                                                 "0x0085"
#define ISO_IC6_SS_SCL_HCNT_inst                                                     0x0085
#define ISO_IC6_SS_SCL_HCNT_ic_ss_scl_hcnt_shift                                     (0)
#define ISO_IC6_SS_SCL_HCNT_ic_ss_scl_hcnt_mask                                      (0x0000FFFF)
#define ISO_IC6_SS_SCL_HCNT_ic_ss_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define ISO_IC6_SS_SCL_HCNT_ic_ss_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define ISO_IC6_SS_SCL_HCNT_get_ic_ss_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define ISO_IC6_SS_SCL_LCNT                                                          0x18007E18
#define ISO_IC6_SS_SCL_LCNT_reg_addr                                                 "0xB8007E18"
#define ISO_IC6_SS_SCL_LCNT_reg                                                      0xB8007E18
#define set_ISO_IC6_SS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) ISO_IC6_SS_SCL_LCNT_reg)=data)
#define get_ISO_IC6_SS_SCL_LCNT_reg   (*((volatile unsigned int*) ISO_IC6_SS_SCL_LCNT_reg))
#define ISO_IC6_SS_SCL_LCNT_inst_adr                                                 "0x0086"
#define ISO_IC6_SS_SCL_LCNT_inst                                                     0x0086
#define ISO_IC6_SS_SCL_LCNT_ic_ss_scl_lcnt_shift                                     (0)
#define ISO_IC6_SS_SCL_LCNT_ic_ss_scl_lcnt_mask                                      (0x0000FFFF)
#define ISO_IC6_SS_SCL_LCNT_ic_ss_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define ISO_IC6_SS_SCL_LCNT_ic_ss_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define ISO_IC6_SS_SCL_LCNT_get_ic_ss_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define ISO_IC6_FS_SCL_HCNT                                                          0x18007E1C
#define ISO_IC6_FS_SCL_HCNT_reg_addr                                                 "0xB8007E1C"
#define ISO_IC6_FS_SCL_HCNT_reg                                                      0xB8007E1C
#define set_ISO_IC6_FS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) ISO_IC6_FS_SCL_HCNT_reg)=data)
#define get_ISO_IC6_FS_SCL_HCNT_reg   (*((volatile unsigned int*) ISO_IC6_FS_SCL_HCNT_reg))
#define ISO_IC6_FS_SCL_HCNT_inst_adr                                                 "0x0087"
#define ISO_IC6_FS_SCL_HCNT_inst                                                     0x0087
#define ISO_IC6_FS_SCL_HCNT_ic_fs_scl_hcnt_shift                                     (0)
#define ISO_IC6_FS_SCL_HCNT_ic_fs_scl_hcnt_mask                                      (0x0000FFFF)
#define ISO_IC6_FS_SCL_HCNT_ic_fs_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define ISO_IC6_FS_SCL_HCNT_ic_fs_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define ISO_IC6_FS_SCL_HCNT_get_ic_fs_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define ISO_IC6_FS_SCL_LCNT                                                          0x18007E20
#define ISO_IC6_FS_SCL_LCNT_reg_addr                                                 "0xB8007E20"
#define ISO_IC6_FS_SCL_LCNT_reg                                                      0xB8007E20
#define set_ISO_IC6_FS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) ISO_IC6_FS_SCL_LCNT_reg)=data)
#define get_ISO_IC6_FS_SCL_LCNT_reg   (*((volatile unsigned int*) ISO_IC6_FS_SCL_LCNT_reg))
#define ISO_IC6_FS_SCL_LCNT_inst_adr                                                 "0x0088"
#define ISO_IC6_FS_SCL_LCNT_inst                                                     0x0088
#define ISO_IC6_FS_SCL_LCNT_ic_fs_scl_lcnt_shift                                     (0)
#define ISO_IC6_FS_SCL_LCNT_ic_fs_scl_lcnt_mask                                      (0x0000FFFF)
#define ISO_IC6_FS_SCL_LCNT_ic_fs_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define ISO_IC6_FS_SCL_LCNT_ic_fs_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define ISO_IC6_FS_SCL_LCNT_get_ic_fs_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define ISO_IC6_INTR_STAT                                                            0x18007E2C
#define ISO_IC6_INTR_STAT_reg_addr                                                   "0xB8007E2C"
#define ISO_IC6_INTR_STAT_reg                                                        0xB8007E2C
#define set_ISO_IC6_INTR_STAT_reg(data)   (*((volatile unsigned int*) ISO_IC6_INTR_STAT_reg)=data)
#define get_ISO_IC6_INTR_STAT_reg   (*((volatile unsigned int*) ISO_IC6_INTR_STAT_reg))
#define ISO_IC6_INTR_STAT_inst_adr                                                   "0x008B"
#define ISO_IC6_INTR_STAT_inst                                                       0x008B
#define ISO_IC6_INTR_STAT_r_gen_call_shift                                           (11)
#define ISO_IC6_INTR_STAT_r_gen_call_mask                                            (0x00000800)
#define ISO_IC6_INTR_STAT_r_gen_call(data)                                           (0x00000800&((data)<<11))
#define ISO_IC6_INTR_STAT_r_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define ISO_IC6_INTR_STAT_get_r_gen_call(data)                                       ((0x00000800&(data))>>11)
#define ISO_IC6_INTR_STAT_r_start_det_shift                                          (10)
#define ISO_IC6_INTR_STAT_r_start_det_mask                                           (0x00000400)
#define ISO_IC6_INTR_STAT_r_start_det(data)                                          (0x00000400&((data)<<10))
#define ISO_IC6_INTR_STAT_r_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define ISO_IC6_INTR_STAT_get_r_start_det(data)                                      ((0x00000400&(data))>>10)
#define ISO_IC6_INTR_STAT_r_stop_det_shift                                           (9)
#define ISO_IC6_INTR_STAT_r_stop_det_mask                                            (0x00000200)
#define ISO_IC6_INTR_STAT_r_stop_det(data)                                           (0x00000200&((data)<<9))
#define ISO_IC6_INTR_STAT_r_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define ISO_IC6_INTR_STAT_get_r_stop_det(data)                                       ((0x00000200&(data))>>9)
#define ISO_IC6_INTR_STAT_r_activity_shift                                           (8)
#define ISO_IC6_INTR_STAT_r_activity_mask                                            (0x00000100)
#define ISO_IC6_INTR_STAT_r_activity(data)                                           (0x00000100&((data)<<8))
#define ISO_IC6_INTR_STAT_r_activity_src(data)                                       ((0x00000100&(data))>>8)
#define ISO_IC6_INTR_STAT_get_r_activity(data)                                       ((0x00000100&(data))>>8)
#define ISO_IC6_INTR_STAT_r_rx_done_shift                                            (7)
#define ISO_IC6_INTR_STAT_r_rx_done_mask                                             (0x00000080)
#define ISO_IC6_INTR_STAT_r_rx_done(data)                                            (0x00000080&((data)<<7))
#define ISO_IC6_INTR_STAT_r_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define ISO_IC6_INTR_STAT_get_r_rx_done(data)                                        ((0x00000080&(data))>>7)
#define ISO_IC6_INTR_STAT_r_tx_abrt_shift                                            (6)
#define ISO_IC6_INTR_STAT_r_tx_abrt_mask                                             (0x00000040)
#define ISO_IC6_INTR_STAT_r_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define ISO_IC6_INTR_STAT_r_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC6_INTR_STAT_get_r_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC6_INTR_STAT_r_rd_req_shift                                             (5)
#define ISO_IC6_INTR_STAT_r_rd_req_mask                                              (0x00000020)
#define ISO_IC6_INTR_STAT_r_rd_req(data)                                             (0x00000020&((data)<<5))
#define ISO_IC6_INTR_STAT_r_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define ISO_IC6_INTR_STAT_get_r_rd_req(data)                                         ((0x00000020&(data))>>5)
#define ISO_IC6_INTR_STAT_r_tx_empty_shift                                           (4)
#define ISO_IC6_INTR_STAT_r_tx_empty_mask                                            (0x00000010)
#define ISO_IC6_INTR_STAT_r_tx_empty(data)                                           (0x00000010&((data)<<4))
#define ISO_IC6_INTR_STAT_r_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define ISO_IC6_INTR_STAT_get_r_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define ISO_IC6_INTR_STAT_r_tx_over_shift                                            (3)
#define ISO_IC6_INTR_STAT_r_tx_over_mask                                             (0x00000008)
#define ISO_IC6_INTR_STAT_r_tx_over(data)                                            (0x00000008&((data)<<3))
#define ISO_IC6_INTR_STAT_r_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define ISO_IC6_INTR_STAT_get_r_tx_over(data)                                        ((0x00000008&(data))>>3)
#define ISO_IC6_INTR_STAT_r_rx_full_shift                                            (2)
#define ISO_IC6_INTR_STAT_r_rx_full_mask                                             (0x00000004)
#define ISO_IC6_INTR_STAT_r_rx_full(data)                                            (0x00000004&((data)<<2))
#define ISO_IC6_INTR_STAT_r_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define ISO_IC6_INTR_STAT_get_r_rx_full(data)                                        ((0x00000004&(data))>>2)
#define ISO_IC6_INTR_STAT_r_rx_over_shift                                            (1)
#define ISO_IC6_INTR_STAT_r_rx_over_mask                                             (0x00000002)
#define ISO_IC6_INTR_STAT_r_rx_over(data)                                            (0x00000002&((data)<<1))
#define ISO_IC6_INTR_STAT_r_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define ISO_IC6_INTR_STAT_get_r_rx_over(data)                                        ((0x00000002&(data))>>1)
#define ISO_IC6_INTR_STAT_r_rx_under_shift                                           (0)
#define ISO_IC6_INTR_STAT_r_rx_under_mask                                            (0x00000001)
#define ISO_IC6_INTR_STAT_r_rx_under(data)                                           (0x00000001&((data)<<0))
#define ISO_IC6_INTR_STAT_r_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define ISO_IC6_INTR_STAT_get_r_rx_under(data)                                       ((0x00000001&(data))>>0)


#define ISO_IC6_INTR_MASK                                                            0x18007E30
#define ISO_IC6_INTR_MASK_reg_addr                                                   "0xB8007E30"
#define ISO_IC6_INTR_MASK_reg                                                        0xB8007E30
#define set_ISO_IC6_INTR_MASK_reg(data)   (*((volatile unsigned int*) ISO_IC6_INTR_MASK_reg)=data)
#define get_ISO_IC6_INTR_MASK_reg   (*((volatile unsigned int*) ISO_IC6_INTR_MASK_reg))
#define ISO_IC6_INTR_MASK_inst_adr                                                   "0x008C"
#define ISO_IC6_INTR_MASK_inst                                                       0x008C
#define ISO_IC6_INTR_MASK_m_gen_call_shift                                           (11)
#define ISO_IC6_INTR_MASK_m_gen_call_mask                                            (0x00000800)
#define ISO_IC6_INTR_MASK_m_gen_call(data)                                           (0x00000800&((data)<<11))
#define ISO_IC6_INTR_MASK_m_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define ISO_IC6_INTR_MASK_get_m_gen_call(data)                                       ((0x00000800&(data))>>11)
#define ISO_IC6_INTR_MASK_m_start_det_shift                                          (10)
#define ISO_IC6_INTR_MASK_m_start_det_mask                                           (0x00000400)
#define ISO_IC6_INTR_MASK_m_start_det(data)                                          (0x00000400&((data)<<10))
#define ISO_IC6_INTR_MASK_m_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define ISO_IC6_INTR_MASK_get_m_start_det(data)                                      ((0x00000400&(data))>>10)
#define ISO_IC6_INTR_MASK_m_stop_det_shift                                           (9)
#define ISO_IC6_INTR_MASK_m_stop_det_mask                                            (0x00000200)
#define ISO_IC6_INTR_MASK_m_stop_det(data)                                           (0x00000200&((data)<<9))
#define ISO_IC6_INTR_MASK_m_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define ISO_IC6_INTR_MASK_get_m_stop_det(data)                                       ((0x00000200&(data))>>9)
#define ISO_IC6_INTR_MASK_m_activity_shift                                           (8)
#define ISO_IC6_INTR_MASK_m_activity_mask                                            (0x00000100)
#define ISO_IC6_INTR_MASK_m_activity(data)                                           (0x00000100&((data)<<8))
#define ISO_IC6_INTR_MASK_m_activity_src(data)                                       ((0x00000100&(data))>>8)
#define ISO_IC6_INTR_MASK_get_m_activity(data)                                       ((0x00000100&(data))>>8)
#define ISO_IC6_INTR_MASK_m_rx_done_shift                                            (7)
#define ISO_IC6_INTR_MASK_m_rx_done_mask                                             (0x00000080)
#define ISO_IC6_INTR_MASK_m_rx_done(data)                                            (0x00000080&((data)<<7))
#define ISO_IC6_INTR_MASK_m_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define ISO_IC6_INTR_MASK_get_m_rx_done(data)                                        ((0x00000080&(data))>>7)
#define ISO_IC6_INTR_MASK_m_tx_abrt_shift                                            (6)
#define ISO_IC6_INTR_MASK_m_tx_abrt_mask                                             (0x00000040)
#define ISO_IC6_INTR_MASK_m_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define ISO_IC6_INTR_MASK_m_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC6_INTR_MASK_get_m_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC6_INTR_MASK_m_rd_req_shift                                             (5)
#define ISO_IC6_INTR_MASK_m_rd_req_mask                                              (0x00000020)
#define ISO_IC6_INTR_MASK_m_rd_req(data)                                             (0x00000020&((data)<<5))
#define ISO_IC6_INTR_MASK_m_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define ISO_IC6_INTR_MASK_get_m_rd_req(data)                                         ((0x00000020&(data))>>5)
#define ISO_IC6_INTR_MASK_m_tx_empty_shift                                           (4)
#define ISO_IC6_INTR_MASK_m_tx_empty_mask                                            (0x00000010)
#define ISO_IC6_INTR_MASK_m_tx_empty(data)                                           (0x00000010&((data)<<4))
#define ISO_IC6_INTR_MASK_m_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define ISO_IC6_INTR_MASK_get_m_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define ISO_IC6_INTR_MASK_m_tx_over_shift                                            (3)
#define ISO_IC6_INTR_MASK_m_tx_over_mask                                             (0x00000008)
#define ISO_IC6_INTR_MASK_m_tx_over(data)                                            (0x00000008&((data)<<3))
#define ISO_IC6_INTR_MASK_m_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define ISO_IC6_INTR_MASK_get_m_tx_over(data)                                        ((0x00000008&(data))>>3)
#define ISO_IC6_INTR_MASK_m_rx_full_shift                                            (2)
#define ISO_IC6_INTR_MASK_m_rx_full_mask                                             (0x00000004)
#define ISO_IC6_INTR_MASK_m_rx_full(data)                                            (0x00000004&((data)<<2))
#define ISO_IC6_INTR_MASK_m_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define ISO_IC6_INTR_MASK_get_m_rx_full(data)                                        ((0x00000004&(data))>>2)
#define ISO_IC6_INTR_MASK_m_rx_over_shift                                            (1)
#define ISO_IC6_INTR_MASK_m_rx_over_mask                                             (0x00000002)
#define ISO_IC6_INTR_MASK_m_rx_over(data)                                            (0x00000002&((data)<<1))
#define ISO_IC6_INTR_MASK_m_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define ISO_IC6_INTR_MASK_get_m_rx_over(data)                                        ((0x00000002&(data))>>1)
#define ISO_IC6_INTR_MASK_m_rx_under_shift                                           (0)
#define ISO_IC6_INTR_MASK_m_rx_under_mask                                            (0x00000001)
#define ISO_IC6_INTR_MASK_m_rx_under(data)                                           (0x00000001&((data)<<0))
#define ISO_IC6_INTR_MASK_m_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define ISO_IC6_INTR_MASK_get_m_rx_under(data)                                       ((0x00000001&(data))>>0)


#define ISO_IC6_RAW_INTR_STAT                                                        0x18007E34
#define ISO_IC6_RAW_INTR_STAT_reg_addr                                               "0xB8007E34"
#define ISO_IC6_RAW_INTR_STAT_reg                                                    0xB8007E34
#define set_ISO_IC6_RAW_INTR_STAT_reg(data)   (*((volatile unsigned int*) ISO_IC6_RAW_INTR_STAT_reg)=data)
#define get_ISO_IC6_RAW_INTR_STAT_reg   (*((volatile unsigned int*) ISO_IC6_RAW_INTR_STAT_reg))
#define ISO_IC6_RAW_INTR_STAT_inst_adr                                               "0x008D"
#define ISO_IC6_RAW_INTR_STAT_inst                                                   0x008D
#define ISO_IC6_RAW_INTR_STAT_gen_call_shift                                         (11)
#define ISO_IC6_RAW_INTR_STAT_gen_call_mask                                          (0x00000800)
#define ISO_IC6_RAW_INTR_STAT_gen_call(data)                                         (0x00000800&((data)<<11))
#define ISO_IC6_RAW_INTR_STAT_gen_call_src(data)                                     ((0x00000800&(data))>>11)
#define ISO_IC6_RAW_INTR_STAT_get_gen_call(data)                                     ((0x00000800&(data))>>11)
#define ISO_IC6_RAW_INTR_STAT_start_det_shift                                        (10)
#define ISO_IC6_RAW_INTR_STAT_start_det_mask                                         (0x00000400)
#define ISO_IC6_RAW_INTR_STAT_start_det(data)                                        (0x00000400&((data)<<10))
#define ISO_IC6_RAW_INTR_STAT_start_det_src(data)                                    ((0x00000400&(data))>>10)
#define ISO_IC6_RAW_INTR_STAT_get_start_det(data)                                    ((0x00000400&(data))>>10)
#define ISO_IC6_RAW_INTR_STAT_stop_det_shift                                         (9)
#define ISO_IC6_RAW_INTR_STAT_stop_det_mask                                          (0x00000200)
#define ISO_IC6_RAW_INTR_STAT_stop_det(data)                                         (0x00000200&((data)<<9))
#define ISO_IC6_RAW_INTR_STAT_stop_det_src(data)                                     ((0x00000200&(data))>>9)
#define ISO_IC6_RAW_INTR_STAT_get_stop_det(data)                                     ((0x00000200&(data))>>9)
#define ISO_IC6_RAW_INTR_STAT_activity_shift                                         (8)
#define ISO_IC6_RAW_INTR_STAT_activity_mask                                          (0x00000100)
#define ISO_IC6_RAW_INTR_STAT_activity(data)                                         (0x00000100&((data)<<8))
#define ISO_IC6_RAW_INTR_STAT_activity_src(data)                                     ((0x00000100&(data))>>8)
#define ISO_IC6_RAW_INTR_STAT_get_activity(data)                                     ((0x00000100&(data))>>8)
#define ISO_IC6_RAW_INTR_STAT_rx_done_shift                                          (7)
#define ISO_IC6_RAW_INTR_STAT_rx_done_mask                                           (0x00000080)
#define ISO_IC6_RAW_INTR_STAT_rx_done(data)                                          (0x00000080&((data)<<7))
#define ISO_IC6_RAW_INTR_STAT_rx_done_src(data)                                      ((0x00000080&(data))>>7)
#define ISO_IC6_RAW_INTR_STAT_get_rx_done(data)                                      ((0x00000080&(data))>>7)
#define ISO_IC6_RAW_INTR_STAT_tx_abrt_shift                                          (6)
#define ISO_IC6_RAW_INTR_STAT_tx_abrt_mask                                           (0x00000040)
#define ISO_IC6_RAW_INTR_STAT_tx_abrt(data)                                          (0x00000040&((data)<<6))
#define ISO_IC6_RAW_INTR_STAT_tx_abrt_src(data)                                      ((0x00000040&(data))>>6)
#define ISO_IC6_RAW_INTR_STAT_get_tx_abrt(data)                                      ((0x00000040&(data))>>6)
#define ISO_IC6_RAW_INTR_STAT_rd_req_shift                                           (5)
#define ISO_IC6_RAW_INTR_STAT_rd_req_mask                                            (0x00000020)
#define ISO_IC6_RAW_INTR_STAT_rd_req(data)                                           (0x00000020&((data)<<5))
#define ISO_IC6_RAW_INTR_STAT_rd_req_src(data)                                       ((0x00000020&(data))>>5)
#define ISO_IC6_RAW_INTR_STAT_get_rd_req(data)                                       ((0x00000020&(data))>>5)
#define ISO_IC6_RAW_INTR_STAT_tx_empty_shift                                         (4)
#define ISO_IC6_RAW_INTR_STAT_tx_empty_mask                                          (0x00000010)
#define ISO_IC6_RAW_INTR_STAT_tx_empty(data)                                         (0x00000010&((data)<<4))
#define ISO_IC6_RAW_INTR_STAT_tx_empty_src(data)                                     ((0x00000010&(data))>>4)
#define ISO_IC6_RAW_INTR_STAT_get_tx_empty(data)                                     ((0x00000010&(data))>>4)
#define ISO_IC6_RAW_INTR_STAT_tx_over_shift                                          (3)
#define ISO_IC6_RAW_INTR_STAT_tx_over_mask                                           (0x00000008)
#define ISO_IC6_RAW_INTR_STAT_tx_over(data)                                          (0x00000008&((data)<<3))
#define ISO_IC6_RAW_INTR_STAT_tx_over_src(data)                                      ((0x00000008&(data))>>3)
#define ISO_IC6_RAW_INTR_STAT_get_tx_over(data)                                      ((0x00000008&(data))>>3)
#define ISO_IC6_RAW_INTR_STAT_rx_full_shift                                          (2)
#define ISO_IC6_RAW_INTR_STAT_rx_full_mask                                           (0x00000004)
#define ISO_IC6_RAW_INTR_STAT_rx_full(data)                                          (0x00000004&((data)<<2))
#define ISO_IC6_RAW_INTR_STAT_rx_full_src(data)                                      ((0x00000004&(data))>>2)
#define ISO_IC6_RAW_INTR_STAT_get_rx_full(data)                                      ((0x00000004&(data))>>2)
#define ISO_IC6_RAW_INTR_STAT_rx_over_shift                                          (1)
#define ISO_IC6_RAW_INTR_STAT_rx_over_mask                                           (0x00000002)
#define ISO_IC6_RAW_INTR_STAT_rx_over(data)                                          (0x00000002&((data)<<1))
#define ISO_IC6_RAW_INTR_STAT_rx_over_src(data)                                      ((0x00000002&(data))>>1)
#define ISO_IC6_RAW_INTR_STAT_get_rx_over(data)                                      ((0x00000002&(data))>>1)
#define ISO_IC6_RAW_INTR_STAT_rx_under_shift                                         (0)
#define ISO_IC6_RAW_INTR_STAT_rx_under_mask                                          (0x00000001)
#define ISO_IC6_RAW_INTR_STAT_rx_under(data)                                         (0x00000001&((data)<<0))
#define ISO_IC6_RAW_INTR_STAT_rx_under_src(data)                                     ((0x00000001&(data))>>0)
#define ISO_IC6_RAW_INTR_STAT_get_rx_under(data)                                     ((0x00000001&(data))>>0)


#define ISO_IC6_RX_TL                                                                0x18007E38
#define ISO_IC6_RX_TL_reg_addr                                                       "0xB8007E38"
#define ISO_IC6_RX_TL_reg                                                            0xB8007E38
#define set_ISO_IC6_RX_TL_reg(data)   (*((volatile unsigned int*) ISO_IC6_RX_TL_reg)=data)
#define get_ISO_IC6_RX_TL_reg   (*((volatile unsigned int*) ISO_IC6_RX_TL_reg))
#define ISO_IC6_RX_TL_inst_adr                                                       "0x008E"
#define ISO_IC6_RX_TL_inst                                                           0x008E
#define ISO_IC6_RX_TL_rx_tl_shift                                                    (0)
#define ISO_IC6_RX_TL_rx_tl_mask                                                     (0x000000FF)
#define ISO_IC6_RX_TL_rx_tl(data)                                                    (0x000000FF&((data)<<0))
#define ISO_IC6_RX_TL_rx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define ISO_IC6_RX_TL_get_rx_tl(data)                                                ((0x000000FF&(data))>>0)


#define ISO_IC6_TX_TL                                                                0x18007E3C
#define ISO_IC6_TX_TL_reg_addr                                                       "0xB8007E3C"
#define ISO_IC6_TX_TL_reg                                                            0xB8007E3C
#define set_ISO_IC6_TX_TL_reg(data)   (*((volatile unsigned int*) ISO_IC6_TX_TL_reg)=data)
#define get_ISO_IC6_TX_TL_reg   (*((volatile unsigned int*) ISO_IC6_TX_TL_reg))
#define ISO_IC6_TX_TL_inst_adr                                                       "0x008F"
#define ISO_IC6_TX_TL_inst                                                           0x008F
#define ISO_IC6_TX_TL_tx_tl_shift                                                    (0)
#define ISO_IC6_TX_TL_tx_tl_mask                                                     (0x000000FF)
#define ISO_IC6_TX_TL_tx_tl(data)                                                    (0x000000FF&((data)<<0))
#define ISO_IC6_TX_TL_tx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define ISO_IC6_TX_TL_get_tx_tl(data)                                                ((0x000000FF&(data))>>0)


#define ISO_IC6_CLR_INTR                                                             0x18007E40
#define ISO_IC6_CLR_INTR_reg_addr                                                    "0xB8007E40"
#define ISO_IC6_CLR_INTR_reg                                                         0xB8007E40
#define set_ISO_IC6_CLR_INTR_reg(data)   (*((volatile unsigned int*) ISO_IC6_CLR_INTR_reg)=data)
#define get_ISO_IC6_CLR_INTR_reg   (*((volatile unsigned int*) ISO_IC6_CLR_INTR_reg))
#define ISO_IC6_CLR_INTR_inst_adr                                                    "0x0090"
#define ISO_IC6_CLR_INTR_inst                                                        0x0090
#define ISO_IC6_CLR_INTR_clr_intr_shift                                              (0)
#define ISO_IC6_CLR_INTR_clr_intr_mask                                               (0x00000001)
#define ISO_IC6_CLR_INTR_clr_intr(data)                                              (0x00000001&((data)<<0))
#define ISO_IC6_CLR_INTR_clr_intr_src(data)                                          ((0x00000001&(data))>>0)
#define ISO_IC6_CLR_INTR_get_clr_intr(data)                                          ((0x00000001&(data))>>0)


#define ISO_IC6_CLR_RX_UNDER                                                         0x18007E44
#define ISO_IC6_CLR_RX_UNDER_reg_addr                                                "0xB8007E44"
#define ISO_IC6_CLR_RX_UNDER_reg                                                     0xB8007E44
#define set_ISO_IC6_CLR_RX_UNDER_reg(data)   (*((volatile unsigned int*) ISO_IC6_CLR_RX_UNDER_reg)=data)
#define get_ISO_IC6_CLR_RX_UNDER_reg   (*((volatile unsigned int*) ISO_IC6_CLR_RX_UNDER_reg))
#define ISO_IC6_CLR_RX_UNDER_inst_adr                                                "0x0091"
#define ISO_IC6_CLR_RX_UNDER_inst                                                    0x0091
#define ISO_IC6_CLR_RX_UNDER_clr_rx_under_shift                                      (0)
#define ISO_IC6_CLR_RX_UNDER_clr_rx_under_mask                                       (0x00000001)
#define ISO_IC6_CLR_RX_UNDER_clr_rx_under(data)                                      (0x00000001&((data)<<0))
#define ISO_IC6_CLR_RX_UNDER_clr_rx_under_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_IC6_CLR_RX_UNDER_get_clr_rx_under(data)                                  ((0x00000001&(data))>>0)


#define ISO_IC6_CLR_RX_OVER                                                          0x18007E48
#define ISO_IC6_CLR_RX_OVER_reg_addr                                                 "0xB8007E48"
#define ISO_IC6_CLR_RX_OVER_reg                                                      0xB8007E48
#define set_ISO_IC6_CLR_RX_OVER_reg(data)   (*((volatile unsigned int*) ISO_IC6_CLR_RX_OVER_reg)=data)
#define get_ISO_IC6_CLR_RX_OVER_reg   (*((volatile unsigned int*) ISO_IC6_CLR_RX_OVER_reg))
#define ISO_IC6_CLR_RX_OVER_inst_adr                                                 "0x0092"
#define ISO_IC6_CLR_RX_OVER_inst                                                     0x0092
#define ISO_IC6_CLR_RX_OVER_clr_rx_over_shift                                        (0)
#define ISO_IC6_CLR_RX_OVER_clr_rx_over_mask                                         (0x00000001)
#define ISO_IC6_CLR_RX_OVER_clr_rx_over(data)                                        (0x00000001&((data)<<0))
#define ISO_IC6_CLR_RX_OVER_clr_rx_over_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC6_CLR_RX_OVER_get_clr_rx_over(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC6_CLR_TX_OVER                                                          0x18007E4C
#define ISO_IC6_CLR_TX_OVER_reg_addr                                                 "0xB8007E4C"
#define ISO_IC6_CLR_TX_OVER_reg                                                      0xB8007E4C
#define set_ISO_IC6_CLR_TX_OVER_reg(data)   (*((volatile unsigned int*) ISO_IC6_CLR_TX_OVER_reg)=data)
#define get_ISO_IC6_CLR_TX_OVER_reg   (*((volatile unsigned int*) ISO_IC6_CLR_TX_OVER_reg))
#define ISO_IC6_CLR_TX_OVER_inst_adr                                                 "0x0093"
#define ISO_IC6_CLR_TX_OVER_inst                                                     0x0093
#define ISO_IC6_CLR_TX_OVER_clr_tx_over_shift                                        (0)
#define ISO_IC6_CLR_TX_OVER_clr_tx_over_mask                                         (0x00000001)
#define ISO_IC6_CLR_TX_OVER_clr_tx_over(data)                                        (0x00000001&((data)<<0))
#define ISO_IC6_CLR_TX_OVER_clr_tx_over_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC6_CLR_TX_OVER_get_clr_tx_over(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC6_CLR_RD_REQ                                                           0x18007E50
#define ISO_IC6_CLR_RD_REQ_reg_addr                                                  "0xB8007E50"
#define ISO_IC6_CLR_RD_REQ_reg                                                       0xB8007E50
#define set_ISO_IC6_CLR_RD_REQ_reg(data)   (*((volatile unsigned int*) ISO_IC6_CLR_RD_REQ_reg)=data)
#define get_ISO_IC6_CLR_RD_REQ_reg   (*((volatile unsigned int*) ISO_IC6_CLR_RD_REQ_reg))
#define ISO_IC6_CLR_RD_REQ_inst_adr                                                  "0x0094"
#define ISO_IC6_CLR_RD_REQ_inst                                                      0x0094
#define ISO_IC6_CLR_RD_REQ_clr_rd_req_shift                                          (0)
#define ISO_IC6_CLR_RD_REQ_clr_rd_req_mask                                           (0x00000001)
#define ISO_IC6_CLR_RD_REQ_clr_rd_req(data)                                          (0x00000001&((data)<<0))
#define ISO_IC6_CLR_RD_REQ_clr_rd_req_src(data)                                      ((0x00000001&(data))>>0)
#define ISO_IC6_CLR_RD_REQ_get_clr_rd_req(data)                                      ((0x00000001&(data))>>0)


#define ISO_IC6_CLR_TX_ABRT                                                          0x18007E54
#define ISO_IC6_CLR_TX_ABRT_reg_addr                                                 "0xB8007E54"
#define ISO_IC6_CLR_TX_ABRT_reg                                                      0xB8007E54
#define set_ISO_IC6_CLR_TX_ABRT_reg(data)   (*((volatile unsigned int*) ISO_IC6_CLR_TX_ABRT_reg)=data)
#define get_ISO_IC6_CLR_TX_ABRT_reg   (*((volatile unsigned int*) ISO_IC6_CLR_TX_ABRT_reg))
#define ISO_IC6_CLR_TX_ABRT_inst_adr                                                 "0x0095"
#define ISO_IC6_CLR_TX_ABRT_inst                                                     0x0095
#define ISO_IC6_CLR_TX_ABRT_clr_tx_abrt_shift                                        (0)
#define ISO_IC6_CLR_TX_ABRT_clr_tx_abrt_mask                                         (0x00000001)
#define ISO_IC6_CLR_TX_ABRT_clr_tx_abrt(data)                                        (0x00000001&((data)<<0))
#define ISO_IC6_CLR_TX_ABRT_clr_tx_abrt_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC6_CLR_TX_ABRT_get_clr_tx_abrt(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC6_CLR_RX_DONE                                                          0x18007E58
#define ISO_IC6_CLR_RX_DONE_reg_addr                                                 "0xB8007E58"
#define ISO_IC6_CLR_RX_DONE_reg                                                      0xB8007E58
#define set_ISO_IC6_CLR_RX_DONE_reg(data)   (*((volatile unsigned int*) ISO_IC6_CLR_RX_DONE_reg)=data)
#define get_ISO_IC6_CLR_RX_DONE_reg   (*((volatile unsigned int*) ISO_IC6_CLR_RX_DONE_reg))
#define ISO_IC6_CLR_RX_DONE_inst_adr                                                 "0x0096"
#define ISO_IC6_CLR_RX_DONE_inst                                                     0x0096
#define ISO_IC6_CLR_RX_DONE_clr_rx_done_shift                                        (0)
#define ISO_IC6_CLR_RX_DONE_clr_rx_done_mask                                         (0x00000001)
#define ISO_IC6_CLR_RX_DONE_clr_rx_done(data)                                        (0x00000001&((data)<<0))
#define ISO_IC6_CLR_RX_DONE_clr_rx_done_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC6_CLR_RX_DONE_get_clr_rx_done(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC6_CLR_ACTIVITY                                                         0x18007E5C
#define ISO_IC6_CLR_ACTIVITY_reg_addr                                                "0xB8007E5C"
#define ISO_IC6_CLR_ACTIVITY_reg                                                     0xB8007E5C
#define set_ISO_IC6_CLR_ACTIVITY_reg(data)   (*((volatile unsigned int*) ISO_IC6_CLR_ACTIVITY_reg)=data)
#define get_ISO_IC6_CLR_ACTIVITY_reg   (*((volatile unsigned int*) ISO_IC6_CLR_ACTIVITY_reg))
#define ISO_IC6_CLR_ACTIVITY_inst_adr                                                "0x0097"
#define ISO_IC6_CLR_ACTIVITY_inst                                                    0x0097
#define ISO_IC6_CLR_ACTIVITY_clr_activity_shift                                      (0)
#define ISO_IC6_CLR_ACTIVITY_clr_activity_mask                                       (0x00000001)
#define ISO_IC6_CLR_ACTIVITY_clr_activity(data)                                      (0x00000001&((data)<<0))
#define ISO_IC6_CLR_ACTIVITY_clr_activity_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_IC6_CLR_ACTIVITY_get_clr_activity(data)                                  ((0x00000001&(data))>>0)


#define ISO_IC6_CLR_STOP_DET                                                         0x18007E60
#define ISO_IC6_CLR_STOP_DET_reg_addr                                                "0xB8007E60"
#define ISO_IC6_CLR_STOP_DET_reg                                                     0xB8007E60
#define set_ISO_IC6_CLR_STOP_DET_reg(data)   (*((volatile unsigned int*) ISO_IC6_CLR_STOP_DET_reg)=data)
#define get_ISO_IC6_CLR_STOP_DET_reg   (*((volatile unsigned int*) ISO_IC6_CLR_STOP_DET_reg))
#define ISO_IC6_CLR_STOP_DET_inst_adr                                                "0x0098"
#define ISO_IC6_CLR_STOP_DET_inst                                                    0x0098
#define ISO_IC6_CLR_STOP_DET_clr_stop_det_shift                                      (0)
#define ISO_IC6_CLR_STOP_DET_clr_stop_det_mask                                       (0x00000001)
#define ISO_IC6_CLR_STOP_DET_clr_stop_det(data)                                      (0x00000001&((data)<<0))
#define ISO_IC6_CLR_STOP_DET_clr_stop_det_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_IC6_CLR_STOP_DET_get_clr_stop_det(data)                                  ((0x00000001&(data))>>0)


#define ISO_IC6_CLR_START_DET                                                        0x18007E64
#define ISO_IC6_CLR_START_DET_reg_addr                                               "0xB8007E64"
#define ISO_IC6_CLR_START_DET_reg                                                    0xB8007E64
#define set_ISO_IC6_CLR_START_DET_reg(data)   (*((volatile unsigned int*) ISO_IC6_CLR_START_DET_reg)=data)
#define get_ISO_IC6_CLR_START_DET_reg   (*((volatile unsigned int*) ISO_IC6_CLR_START_DET_reg))
#define ISO_IC6_CLR_START_DET_inst_adr                                               "0x0099"
#define ISO_IC6_CLR_START_DET_inst                                                   0x0099
#define ISO_IC6_CLR_START_DET_clr_start_det_shift                                    (0)
#define ISO_IC6_CLR_START_DET_clr_start_det_mask                                     (0x00000001)
#define ISO_IC6_CLR_START_DET_clr_start_det(data)                                    (0x00000001&((data)<<0))
#define ISO_IC6_CLR_START_DET_clr_start_det_src(data)                                ((0x00000001&(data))>>0)
#define ISO_IC6_CLR_START_DET_get_clr_start_det(data)                                ((0x00000001&(data))>>0)


#define ISO_IC6_CLR_GEN_CALL                                                         0x18007E68
#define ISO_IC6_CLR_GEN_CALL_reg_addr                                                "0xB8007E68"
#define ISO_IC6_CLR_GEN_CALL_reg                                                     0xB8007E68
#define set_ISO_IC6_CLR_GEN_CALL_reg(data)   (*((volatile unsigned int*) ISO_IC6_CLR_GEN_CALL_reg)=data)
#define get_ISO_IC6_CLR_GEN_CALL_reg   (*((volatile unsigned int*) ISO_IC6_CLR_GEN_CALL_reg))
#define ISO_IC6_CLR_GEN_CALL_inst_adr                                                "0x009A"
#define ISO_IC6_CLR_GEN_CALL_inst                                                    0x009A
#define ISO_IC6_CLR_GEN_CALL_clr_gen_call_shift                                      (0)
#define ISO_IC6_CLR_GEN_CALL_clr_gen_call_mask                                       (0x00000001)
#define ISO_IC6_CLR_GEN_CALL_clr_gen_call(data)                                      (0x00000001&((data)<<0))
#define ISO_IC6_CLR_GEN_CALL_clr_gen_call_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_IC6_CLR_GEN_CALL_get_clr_gen_call(data)                                  ((0x00000001&(data))>>0)


#define ISO_IC6_ENABLE                                                               0x18007E6C
#define ISO_IC6_ENABLE_reg_addr                                                      "0xB8007E6C"
#define ISO_IC6_ENABLE_reg                                                           0xB8007E6C
#define set_ISO_IC6_ENABLE_reg(data)   (*((volatile unsigned int*) ISO_IC6_ENABLE_reg)=data)
#define get_ISO_IC6_ENABLE_reg   (*((volatile unsigned int*) ISO_IC6_ENABLE_reg))
#define ISO_IC6_ENABLE_inst_adr                                                      "0x009B"
#define ISO_IC6_ENABLE_inst                                                          0x009B
#define ISO_IC6_ENABLE_enable_shift                                                  (0)
#define ISO_IC6_ENABLE_enable_mask                                                   (0x00000001)
#define ISO_IC6_ENABLE_enable(data)                                                  (0x00000001&((data)<<0))
#define ISO_IC6_ENABLE_enable_src(data)                                              ((0x00000001&(data))>>0)
#define ISO_IC6_ENABLE_get_enable(data)                                              ((0x00000001&(data))>>0)


#define ISO_IC6_STATUS                                                               0x18007E70
#define ISO_IC6_STATUS_reg_addr                                                      "0xB8007E70"
#define ISO_IC6_STATUS_reg                                                           0xB8007E70
#define set_ISO_IC6_STATUS_reg(data)   (*((volatile unsigned int*) ISO_IC6_STATUS_reg)=data)
#define get_ISO_IC6_STATUS_reg   (*((volatile unsigned int*) ISO_IC6_STATUS_reg))
#define ISO_IC6_STATUS_inst_adr                                                      "0x009C"
#define ISO_IC6_STATUS_inst                                                          0x009C
#define ISO_IC6_STATUS_slv_activity_shift                                            (6)
#define ISO_IC6_STATUS_slv_activity_mask                                             (0x00000040)
#define ISO_IC6_STATUS_slv_activity(data)                                            (0x00000040&((data)<<6))
#define ISO_IC6_STATUS_slv_activity_src(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC6_STATUS_get_slv_activity(data)                                        ((0x00000040&(data))>>6)
#define ISO_IC6_STATUS_mst_activity_shift                                            (5)
#define ISO_IC6_STATUS_mst_activity_mask                                             (0x00000020)
#define ISO_IC6_STATUS_mst_activity(data)                                            (0x00000020&((data)<<5))
#define ISO_IC6_STATUS_mst_activity_src(data)                                        ((0x00000020&(data))>>5)
#define ISO_IC6_STATUS_get_mst_activity(data)                                        ((0x00000020&(data))>>5)
#define ISO_IC6_STATUS_rff_shift                                                     (4)
#define ISO_IC6_STATUS_rff_mask                                                      (0x00000010)
#define ISO_IC6_STATUS_rff(data)                                                     (0x00000010&((data)<<4))
#define ISO_IC6_STATUS_rff_src(data)                                                 ((0x00000010&(data))>>4)
#define ISO_IC6_STATUS_get_rff(data)                                                 ((0x00000010&(data))>>4)
#define ISO_IC6_STATUS_rfne_shift                                                    (3)
#define ISO_IC6_STATUS_rfne_mask                                                     (0x00000008)
#define ISO_IC6_STATUS_rfne(data)                                                    (0x00000008&((data)<<3))
#define ISO_IC6_STATUS_rfne_src(data)                                                ((0x00000008&(data))>>3)
#define ISO_IC6_STATUS_get_rfne(data)                                                ((0x00000008&(data))>>3)
#define ISO_IC6_STATUS_tfe_shift                                                     (2)
#define ISO_IC6_STATUS_tfe_mask                                                      (0x00000004)
#define ISO_IC6_STATUS_tfe(data)                                                     (0x00000004&((data)<<2))
#define ISO_IC6_STATUS_tfe_src(data)                                                 ((0x00000004&(data))>>2)
#define ISO_IC6_STATUS_get_tfe(data)                                                 ((0x00000004&(data))>>2)
#define ISO_IC6_STATUS_tfnf_shift                                                    (1)
#define ISO_IC6_STATUS_tfnf_mask                                                     (0x00000002)
#define ISO_IC6_STATUS_tfnf(data)                                                    (0x00000002&((data)<<1))
#define ISO_IC6_STATUS_tfnf_src(data)                                                ((0x00000002&(data))>>1)
#define ISO_IC6_STATUS_get_tfnf(data)                                                ((0x00000002&(data))>>1)
#define ISO_IC6_STATUS_activity_shift                                                (0)
#define ISO_IC6_STATUS_activity_mask                                                 (0x00000001)
#define ISO_IC6_STATUS_activity(data)                                                (0x00000001&((data)<<0))
#define ISO_IC6_STATUS_activity_src(data)                                            ((0x00000001&(data))>>0)
#define ISO_IC6_STATUS_get_activity(data)                                            ((0x00000001&(data))>>0)


#define ISO_IC6_TXFLR                                                                0x18007E74
#define ISO_IC6_TXFLR_reg_addr                                                       "0xB8007E74"
#define ISO_IC6_TXFLR_reg                                                            0xB8007E74
#define set_ISO_IC6_TXFLR_reg(data)   (*((volatile unsigned int*) ISO_IC6_TXFLR_reg)=data)
#define get_ISO_IC6_TXFLR_reg   (*((volatile unsigned int*) ISO_IC6_TXFLR_reg))
#define ISO_IC6_TXFLR_inst_adr                                                       "0x009D"
#define ISO_IC6_TXFLR_inst                                                           0x009D
#define ISO_IC6_TXFLR_txflr_shift                                                    (0)
#define ISO_IC6_TXFLR_txflr_mask                                                     (0x0000000F)
#define ISO_IC6_TXFLR_txflr(data)                                                    (0x0000000F&((data)<<0))
#define ISO_IC6_TXFLR_txflr_src(data)                                                ((0x0000000F&(data))>>0)
#define ISO_IC6_TXFLR_get_txflr(data)                                                ((0x0000000F&(data))>>0)


#define ISO_IC6_RXFLR                                                                0x18007E78
#define ISO_IC6_RXFLR_reg_addr                                                       "0xB8007E78"
#define ISO_IC6_RXFLR_reg                                                            0xB8007E78
#define set_ISO_IC6_RXFLR_reg(data)   (*((volatile unsigned int*) ISO_IC6_RXFLR_reg)=data)
#define get_ISO_IC6_RXFLR_reg   (*((volatile unsigned int*) ISO_IC6_RXFLR_reg))
#define ISO_IC6_RXFLR_inst_adr                                                       "0x009E"
#define ISO_IC6_RXFLR_inst                                                           0x009E
#define ISO_IC6_RXFLR_rxflr_shift                                                    (0)
#define ISO_IC6_RXFLR_rxflr_mask                                                     (0x0000000F)
#define ISO_IC6_RXFLR_rxflr(data)                                                    (0x0000000F&((data)<<0))
#define ISO_IC6_RXFLR_rxflr_src(data)                                                ((0x0000000F&(data))>>0)
#define ISO_IC6_RXFLR_get_rxflr(data)                                                ((0x0000000F&(data))>>0)


#define ISO_IC6_SDA_HOLD                                                             0x18007E7C
#define ISO_IC6_SDA_HOLD_reg_addr                                                    "0xB8007E7C"
#define ISO_IC6_SDA_HOLD_reg                                                         0xB8007E7C
#define set_ISO_IC6_SDA_HOLD_reg(data)   (*((volatile unsigned int*) ISO_IC6_SDA_HOLD_reg)=data)
#define get_ISO_IC6_SDA_HOLD_reg   (*((volatile unsigned int*) ISO_IC6_SDA_HOLD_reg))
#define ISO_IC6_SDA_HOLD_inst_adr                                                    "0x009F"
#define ISO_IC6_SDA_HOLD_inst                                                        0x009F
#define ISO_IC6_SDA_HOLD_ic_sda_hold_shift                                           (0)
#define ISO_IC6_SDA_HOLD_ic_sda_hold_mask                                            (0x0000FFFF)
#define ISO_IC6_SDA_HOLD_ic_sda_hold(data)                                           (0x0000FFFF&((data)<<0))
#define ISO_IC6_SDA_HOLD_ic_sda_hold_src(data)                                       ((0x0000FFFF&(data))>>0)
#define ISO_IC6_SDA_HOLD_get_ic_sda_hold(data)                                       ((0x0000FFFF&(data))>>0)


#define ISO_IC6_TX_ABRT_SOURCE                                                       0x18007E80
#define ISO_IC6_TX_ABRT_SOURCE_reg_addr                                              "0xB8007E80"
#define ISO_IC6_TX_ABRT_SOURCE_reg                                                   0xB8007E80
#define set_ISO_IC6_TX_ABRT_SOURCE_reg(data)   (*((volatile unsigned int*) ISO_IC6_TX_ABRT_SOURCE_reg)=data)
#define get_ISO_IC6_TX_ABRT_SOURCE_reg   (*((volatile unsigned int*) ISO_IC6_TX_ABRT_SOURCE_reg))
#define ISO_IC6_TX_ABRT_SOURCE_inst_adr                                              "0x00A0"
#define ISO_IC6_TX_ABRT_SOURCE_inst                                                  0x00A0
#define ISO_IC6_TX_ABRT_SOURCE_abrt_slvrd_intx_shift                                 (15)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_slvrd_intx_mask                                  (0x00008000)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_slvrd_intx(data)                                 (0x00008000&((data)<<15))
#define ISO_IC6_TX_ABRT_SOURCE_abrt_slvrd_intx_src(data)                             ((0x00008000&(data))>>15)
#define ISO_IC6_TX_ABRT_SOURCE_get_abrt_slvrd_intx(data)                             ((0x00008000&(data))>>15)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_slv_arblost_shift                                (14)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_slv_arblost_mask                                 (0x00004000)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_slv_arblost(data)                                (0x00004000&((data)<<14))
#define ISO_IC6_TX_ABRT_SOURCE_abrt_slv_arblost_src(data)                            ((0x00004000&(data))>>14)
#define ISO_IC6_TX_ABRT_SOURCE_get_abrt_slv_arblost(data)                            ((0x00004000&(data))>>14)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_slvflush_txfifo_shift                            (13)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_slvflush_txfifo_mask                             (0x00002000)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_slvflush_txfifo(data)                            (0x00002000&((data)<<13))
#define ISO_IC6_TX_ABRT_SOURCE_abrt_slvflush_txfifo_src(data)                        ((0x00002000&(data))>>13)
#define ISO_IC6_TX_ABRT_SOURCE_get_abrt_slvflush_txfifo(data)                        ((0x00002000&(data))>>13)
#define ISO_IC6_TX_ABRT_SOURCE_arb_lost_shift                                        (12)
#define ISO_IC6_TX_ABRT_SOURCE_arb_lost_mask                                         (0x00001000)
#define ISO_IC6_TX_ABRT_SOURCE_arb_lost(data)                                        (0x00001000&((data)<<12))
#define ISO_IC6_TX_ABRT_SOURCE_arb_lost_src(data)                                    ((0x00001000&(data))>>12)
#define ISO_IC6_TX_ABRT_SOURCE_get_arb_lost(data)                                    ((0x00001000&(data))>>12)
#define ISO_IC6_TX_ABRT_SOURCE_arb_master_dis_shift                                  (11)
#define ISO_IC6_TX_ABRT_SOURCE_arb_master_dis_mask                                   (0x00000800)
#define ISO_IC6_TX_ABRT_SOURCE_arb_master_dis(data)                                  (0x00000800&((data)<<11))
#define ISO_IC6_TX_ABRT_SOURCE_arb_master_dis_src(data)                              ((0x00000800&(data))>>11)
#define ISO_IC6_TX_ABRT_SOURCE_get_arb_master_dis(data)                              ((0x00000800&(data))>>11)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_shift                             (10)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_mask                              (0x00000400)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_10b_rd_norstrt(data)                             (0x00000400&((data)<<10))
#define ISO_IC6_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_src(data)                         ((0x00000400&(data))>>10)
#define ISO_IC6_TX_ABRT_SOURCE_get_abrt_10b_rd_norstrt(data)                         ((0x00000400&(data))>>10)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_sbyte_norstrt_shift                              (9)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_sbyte_norstrt_mask                               (0x00000200)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_sbyte_norstrt(data)                              (0x00000200&((data)<<9))
#define ISO_IC6_TX_ABRT_SOURCE_abrt_sbyte_norstrt_src(data)                          ((0x00000200&(data))>>9)
#define ISO_IC6_TX_ABRT_SOURCE_get_abrt_sbyte_norstrt(data)                          ((0x00000200&(data))>>9)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_hs_norstrt_shift                                 (8)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_hs_norstrt_mask                                  (0x00000100)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_hs_norstrt(data)                                 (0x00000100&((data)<<8))
#define ISO_IC6_TX_ABRT_SOURCE_abrt_hs_norstrt_src(data)                             ((0x00000100&(data))>>8)
#define ISO_IC6_TX_ABRT_SOURCE_get_abrt_hs_norstrt(data)                             ((0x00000100&(data))>>8)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_sbyte_ackdet_shift                               (7)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_sbyte_ackdet_mask                                (0x00000080)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_sbyte_ackdet(data)                               (0x00000080&((data)<<7))
#define ISO_IC6_TX_ABRT_SOURCE_abrt_sbyte_ackdet_src(data)                           ((0x00000080&(data))>>7)
#define ISO_IC6_TX_ABRT_SOURCE_get_abrt_sbyte_ackdet(data)                           ((0x00000080&(data))>>7)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_hs_ackdet_shift                                  (6)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_hs_ackdet_mask                                   (0x00000040)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_hs_ackdet(data)                                  (0x00000040&((data)<<6))
#define ISO_IC6_TX_ABRT_SOURCE_abrt_hs_ackdet_src(data)                              ((0x00000040&(data))>>6)
#define ISO_IC6_TX_ABRT_SOURCE_get_abrt_hs_ackdet(data)                              ((0x00000040&(data))>>6)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_gcall_read_shift                                 (5)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_gcall_read_mask                                  (0x00000020)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_gcall_read(data)                                 (0x00000020&((data)<<5))
#define ISO_IC6_TX_ABRT_SOURCE_abrt_gcall_read_src(data)                             ((0x00000020&(data))>>5)
#define ISO_IC6_TX_ABRT_SOURCE_get_abrt_gcall_read(data)                             ((0x00000020&(data))>>5)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_gcall_noack_shift                                (4)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_gcall_noack_mask                                 (0x00000010)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_gcall_noack(data)                                (0x00000010&((data)<<4))
#define ISO_IC6_TX_ABRT_SOURCE_abrt_gcall_noack_src(data)                            ((0x00000010&(data))>>4)
#define ISO_IC6_TX_ABRT_SOURCE_get_abrt_gcall_noack(data)                            ((0x00000010&(data))>>4)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_txdata_noack_shift                               (3)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_txdata_noack_mask                                (0x00000008)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_txdata_noack(data)                               (0x00000008&((data)<<3))
#define ISO_IC6_TX_ABRT_SOURCE_abrt_txdata_noack_src(data)                           ((0x00000008&(data))>>3)
#define ISO_IC6_TX_ABRT_SOURCE_get_abrt_txdata_noack(data)                           ((0x00000008&(data))>>3)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_10addr2_noack_shift                              (2)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_10addr2_noack_mask                               (0x00000004)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_10addr2_noack(data)                              (0x00000004&((data)<<2))
#define ISO_IC6_TX_ABRT_SOURCE_abrt_10addr2_noack_src(data)                          ((0x00000004&(data))>>2)
#define ISO_IC6_TX_ABRT_SOURCE_get_abrt_10addr2_noack(data)                          ((0x00000004&(data))>>2)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_10addr1_noack_shift                              (1)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_10addr1_noack_mask                               (0x00000002)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_10addr1_noack(data)                              (0x00000002&((data)<<1))
#define ISO_IC6_TX_ABRT_SOURCE_abrt_10addr1_noack_src(data)                          ((0x00000002&(data))>>1)
#define ISO_IC6_TX_ABRT_SOURCE_get_abrt_10addr1_noack(data)                          ((0x00000002&(data))>>1)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_7b_addr_noack_shift                              (0)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_7b_addr_noack_mask                               (0x00000001)
#define ISO_IC6_TX_ABRT_SOURCE_abrt_7b_addr_noack(data)                              (0x00000001&((data)<<0))
#define ISO_IC6_TX_ABRT_SOURCE_abrt_7b_addr_noack_src(data)                          ((0x00000001&(data))>>0)
#define ISO_IC6_TX_ABRT_SOURCE_get_abrt_7b_addr_noack(data)                          ((0x00000001&(data))>>0)


#define ISO_IC6_SLV_DATA_NACK_ONLY                                                   0x18007E84
#define ISO_IC6_SLV_DATA_NACK_ONLY_reg_addr                                          "0xB8007E84"
#define ISO_IC6_SLV_DATA_NACK_ONLY_reg                                               0xB8007E84
#define set_ISO_IC6_SLV_DATA_NACK_ONLY_reg(data)   (*((volatile unsigned int*) ISO_IC6_SLV_DATA_NACK_ONLY_reg)=data)
#define get_ISO_IC6_SLV_DATA_NACK_ONLY_reg   (*((volatile unsigned int*) ISO_IC6_SLV_DATA_NACK_ONLY_reg))
#define ISO_IC6_SLV_DATA_NACK_ONLY_inst_adr                                          "0x00A1"
#define ISO_IC6_SLV_DATA_NACK_ONLY_inst                                              0x00A1
#define ISO_IC6_SLV_DATA_NACK_ONLY_nack_shift                                        (0)
#define ISO_IC6_SLV_DATA_NACK_ONLY_nack_mask                                         (0x00000001)
#define ISO_IC6_SLV_DATA_NACK_ONLY_nack(data)                                        (0x00000001&((data)<<0))
#define ISO_IC6_SLV_DATA_NACK_ONLY_nack_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_IC6_SLV_DATA_NACK_ONLY_get_nack(data)                                    ((0x00000001&(data))>>0)


#define ISO_IC6_DMA_CR                                                               0x18007E88
#define ISO_IC6_DMA_CR_reg_addr                                                      "0xB8007E88"
#define ISO_IC6_DMA_CR_reg                                                           0xB8007E88
#define set_ISO_IC6_DMA_CR_reg(data)   (*((volatile unsigned int*) ISO_IC6_DMA_CR_reg)=data)
#define get_ISO_IC6_DMA_CR_reg   (*((volatile unsigned int*) ISO_IC6_DMA_CR_reg))
#define ISO_IC6_DMA_CR_inst_adr                                                      "0x00A2"
#define ISO_IC6_DMA_CR_inst                                                          0x00A2
#define ISO_IC6_DMA_CR_tdmae_shift                                                   (1)
#define ISO_IC6_DMA_CR_tdmae_mask                                                    (0x00000002)
#define ISO_IC6_DMA_CR_tdmae(data)                                                   (0x00000002&((data)<<1))
#define ISO_IC6_DMA_CR_tdmae_src(data)                                               ((0x00000002&(data))>>1)
#define ISO_IC6_DMA_CR_get_tdmae(data)                                               ((0x00000002&(data))>>1)
#define ISO_IC6_DMA_CR_rdmae_shift                                                   (0)
#define ISO_IC6_DMA_CR_rdmae_mask                                                    (0x00000001)
#define ISO_IC6_DMA_CR_rdmae(data)                                                   (0x00000001&((data)<<0))
#define ISO_IC6_DMA_CR_rdmae_src(data)                                               ((0x00000001&(data))>>0)
#define ISO_IC6_DMA_CR_get_rdmae(data)                                               ((0x00000001&(data))>>0)


#define ISO_IC6_DMA_TDLR                                                             0x18007E8C
#define ISO_IC6_DMA_TDLR_reg_addr                                                    "0xB8007E8C"
#define ISO_IC6_DMA_TDLR_reg                                                         0xB8007E8C
#define set_ISO_IC6_DMA_TDLR_reg(data)   (*((volatile unsigned int*) ISO_IC6_DMA_TDLR_reg)=data)
#define get_ISO_IC6_DMA_TDLR_reg   (*((volatile unsigned int*) ISO_IC6_DMA_TDLR_reg))
#define ISO_IC6_DMA_TDLR_inst_adr                                                    "0x00A3"
#define ISO_IC6_DMA_TDLR_inst                                                        0x00A3
#define ISO_IC6_DMA_TDLR_dmatdl_shift                                                (0)
#define ISO_IC6_DMA_TDLR_dmatdl_mask                                                 (0x00000007)
#define ISO_IC6_DMA_TDLR_dmatdl(data)                                                (0x00000007&((data)<<0))
#define ISO_IC6_DMA_TDLR_dmatdl_src(data)                                            ((0x00000007&(data))>>0)
#define ISO_IC6_DMA_TDLR_get_dmatdl(data)                                            ((0x00000007&(data))>>0)


#define ISO_IC6_DMA_RDLR                                                             0x18007E90
#define ISO_IC6_DMA_RDLR_reg_addr                                                    "0xB8007E90"
#define ISO_IC6_DMA_RDLR_reg                                                         0xB8007E90
#define set_ISO_IC6_DMA_RDLR_reg(data)   (*((volatile unsigned int*) ISO_IC6_DMA_RDLR_reg)=data)
#define get_ISO_IC6_DMA_RDLR_reg   (*((volatile unsigned int*) ISO_IC6_DMA_RDLR_reg))
#define ISO_IC6_DMA_RDLR_inst_adr                                                    "0x00A4"
#define ISO_IC6_DMA_RDLR_inst                                                        0x00A4
#define ISO_IC6_DMA_RDLR_dmardl_shift                                                (0)
#define ISO_IC6_DMA_RDLR_dmardl_mask                                                 (0x0000000F)
#define ISO_IC6_DMA_RDLR_dmardl(data)                                                (0x0000000F&((data)<<0))
#define ISO_IC6_DMA_RDLR_dmardl_src(data)                                            ((0x0000000F&(data))>>0)
#define ISO_IC6_DMA_RDLR_get_dmardl(data)                                            ((0x0000000F&(data))>>0)


#define ISO_IC6_SDA_SETUP                                                            0x18007E94
#define ISO_IC6_SDA_SETUP_reg_addr                                                   "0xB8007E94"
#define ISO_IC6_SDA_SETUP_reg                                                        0xB8007E94
#define set_ISO_IC6_SDA_SETUP_reg(data)   (*((volatile unsigned int*) ISO_IC6_SDA_SETUP_reg)=data)
#define get_ISO_IC6_SDA_SETUP_reg   (*((volatile unsigned int*) ISO_IC6_SDA_SETUP_reg))
#define ISO_IC6_SDA_SETUP_inst_adr                                                   "0x00A5"
#define ISO_IC6_SDA_SETUP_inst                                                       0x00A5
#define ISO_IC6_SDA_SETUP_sda_setup_shift                                            (0)
#define ISO_IC6_SDA_SETUP_sda_setup_mask                                             (0x000000FF)
#define ISO_IC6_SDA_SETUP_sda_setup(data)                                            (0x000000FF&((data)<<0))
#define ISO_IC6_SDA_SETUP_sda_setup_src(data)                                        ((0x000000FF&(data))>>0)
#define ISO_IC6_SDA_SETUP_get_sda_setup(data)                                        ((0x000000FF&(data))>>0)


#define ISO_IC6_ACK_GENERAL_CALL                                                     0x18007E98
#define ISO_IC6_ACK_GENERAL_CALL_reg_addr                                            "0xB8007E98"
#define ISO_IC6_ACK_GENERAL_CALL_reg                                                 0xB8007E98
#define set_ISO_IC6_ACK_GENERAL_CALL_reg(data)   (*((volatile unsigned int*) ISO_IC6_ACK_GENERAL_CALL_reg)=data)
#define get_ISO_IC6_ACK_GENERAL_CALL_reg   (*((volatile unsigned int*) ISO_IC6_ACK_GENERAL_CALL_reg))
#define ISO_IC6_ACK_GENERAL_CALL_inst_adr                                            "0x00A6"
#define ISO_IC6_ACK_GENERAL_CALL_inst                                                0x00A6
#define ISO_IC6_ACK_GENERAL_CALL_ack_gen_call_shift                                  (0)
#define ISO_IC6_ACK_GENERAL_CALL_ack_gen_call_mask                                   (0x00000001)
#define ISO_IC6_ACK_GENERAL_CALL_ack_gen_call(data)                                  (0x00000001&((data)<<0))
#define ISO_IC6_ACK_GENERAL_CALL_ack_gen_call_src(data)                              ((0x00000001&(data))>>0)
#define ISO_IC6_ACK_GENERAL_CALL_get_ack_gen_call(data)                              ((0x00000001&(data))>>0)


#define ISO_IC6_ENABLE_STATUS                                                        0x18007E9C
#define ISO_IC6_ENABLE_STATUS_reg_addr                                               "0xB8007E9C"
#define ISO_IC6_ENABLE_STATUS_reg                                                    0xB8007E9C
#define set_ISO_IC6_ENABLE_STATUS_reg(data)   (*((volatile unsigned int*) ISO_IC6_ENABLE_STATUS_reg)=data)
#define get_ISO_IC6_ENABLE_STATUS_reg   (*((volatile unsigned int*) ISO_IC6_ENABLE_STATUS_reg))
#define ISO_IC6_ENABLE_STATUS_inst_adr                                               "0x00A7"
#define ISO_IC6_ENABLE_STATUS_inst                                                   0x00A7
#define ISO_IC6_ENABLE_STATUS_slv_rx_data_lost_shift                                 (2)
#define ISO_IC6_ENABLE_STATUS_slv_rx_data_lost_mask                                  (0x00000004)
#define ISO_IC6_ENABLE_STATUS_slv_rx_data_lost(data)                                 (0x00000004&((data)<<2))
#define ISO_IC6_ENABLE_STATUS_slv_rx_data_lost_src(data)                             ((0x00000004&(data))>>2)
#define ISO_IC6_ENABLE_STATUS_get_slv_rx_data_lost(data)                             ((0x00000004&(data))>>2)
#define ISO_IC6_ENABLE_STATUS_slv_disabled_whi_shift                                 (1)
#define ISO_IC6_ENABLE_STATUS_slv_disabled_whi_mask                                  (0x00000002)
#define ISO_IC6_ENABLE_STATUS_slv_disabled_whi(data)                                 (0x00000002&((data)<<1))
#define ISO_IC6_ENABLE_STATUS_slv_disabled_whi_src(data)                             ((0x00000002&(data))>>1)
#define ISO_IC6_ENABLE_STATUS_get_slv_disabled_whi(data)                             ((0x00000002&(data))>>1)
#define ISO_IC6_ENABLE_STATUS_ic_en_shift                                            (0)
#define ISO_IC6_ENABLE_STATUS_ic_en_mask                                             (0x00000001)
#define ISO_IC6_ENABLE_STATUS_ic_en(data)                                            (0x00000001&((data)<<0))
#define ISO_IC6_ENABLE_STATUS_ic_en_src(data)                                        ((0x00000001&(data))>>0)
#define ISO_IC6_ENABLE_STATUS_get_ic_en(data)                                        ((0x00000001&(data))>>0)


#define ISO_IC6_COMP_PARAM_1                                                         0x18007EF4
#define ISO_IC6_COMP_PARAM_1_reg_addr                                                "0xB8007EF4"
#define ISO_IC6_COMP_PARAM_1_reg                                                     0xB8007EF4
#define set_ISO_IC6_COMP_PARAM_1_reg(data)   (*((volatile unsigned int*) ISO_IC6_COMP_PARAM_1_reg)=data)
#define get_ISO_IC6_COMP_PARAM_1_reg   (*((volatile unsigned int*) ISO_IC6_COMP_PARAM_1_reg))
#define ISO_IC6_COMP_PARAM_1_inst_adr                                                "0x00BD"
#define ISO_IC6_COMP_PARAM_1_inst                                                    0x00BD
#define ISO_IC6_COMP_PARAM_1_tx_buffer_depth_shift                                   (16)
#define ISO_IC6_COMP_PARAM_1_tx_buffer_depth_mask                                    (0x00FF0000)
#define ISO_IC6_COMP_PARAM_1_tx_buffer_depth(data)                                   (0x00FF0000&((data)<<16))
#define ISO_IC6_COMP_PARAM_1_tx_buffer_depth_src(data)                               ((0x00FF0000&(data))>>16)
#define ISO_IC6_COMP_PARAM_1_get_tx_buffer_depth(data)                               ((0x00FF0000&(data))>>16)
#define ISO_IC6_COMP_PARAM_1_rx_buffer_depth_shift                                   (8)
#define ISO_IC6_COMP_PARAM_1_rx_buffer_depth_mask                                    (0x0000FF00)
#define ISO_IC6_COMP_PARAM_1_rx_buffer_depth(data)                                   (0x0000FF00&((data)<<8))
#define ISO_IC6_COMP_PARAM_1_rx_buffer_depth_src(data)                               ((0x0000FF00&(data))>>8)
#define ISO_IC6_COMP_PARAM_1_get_rx_buffer_depth(data)                               ((0x0000FF00&(data))>>8)
#define ISO_IC6_COMP_PARAM_1_add_encoded_params_shift                                (7)
#define ISO_IC6_COMP_PARAM_1_add_encoded_params_mask                                 (0x00000080)
#define ISO_IC6_COMP_PARAM_1_add_encoded_params(data)                                (0x00000080&((data)<<7))
#define ISO_IC6_COMP_PARAM_1_add_encoded_params_src(data)                            ((0x00000080&(data))>>7)
#define ISO_IC6_COMP_PARAM_1_get_add_encoded_params(data)                            ((0x00000080&(data))>>7)
#define ISO_IC6_COMP_PARAM_1_has_dma_shift                                           (6)
#define ISO_IC6_COMP_PARAM_1_has_dma_mask                                            (0x00000040)
#define ISO_IC6_COMP_PARAM_1_has_dma(data)                                           (0x00000040&((data)<<6))
#define ISO_IC6_COMP_PARAM_1_has_dma_src(data)                                       ((0x00000040&(data))>>6)
#define ISO_IC6_COMP_PARAM_1_get_has_dma(data)                                       ((0x00000040&(data))>>6)
#define ISO_IC6_COMP_PARAM_1_intr_io_shift                                           (5)
#define ISO_IC6_COMP_PARAM_1_intr_io_mask                                            (0x00000020)
#define ISO_IC6_COMP_PARAM_1_intr_io(data)                                           (0x00000020&((data)<<5))
#define ISO_IC6_COMP_PARAM_1_intr_io_src(data)                                       ((0x00000020&(data))>>5)
#define ISO_IC6_COMP_PARAM_1_get_intr_io(data)                                       ((0x00000020&(data))>>5)
#define ISO_IC6_COMP_PARAM_1_hc_count_values_shift                                   (4)
#define ISO_IC6_COMP_PARAM_1_hc_count_values_mask                                    (0x00000010)
#define ISO_IC6_COMP_PARAM_1_hc_count_values(data)                                   (0x00000010&((data)<<4))
#define ISO_IC6_COMP_PARAM_1_hc_count_values_src(data)                               ((0x00000010&(data))>>4)
#define ISO_IC6_COMP_PARAM_1_get_hc_count_values(data)                               ((0x00000010&(data))>>4)
#define ISO_IC6_COMP_PARAM_1_max_speed_mode_shift                                    (2)
#define ISO_IC6_COMP_PARAM_1_max_speed_mode_mask                                     (0x0000000C)
#define ISO_IC6_COMP_PARAM_1_max_speed_mode(data)                                    (0x0000000C&((data)<<2))
#define ISO_IC6_COMP_PARAM_1_max_speed_mode_src(data)                                ((0x0000000C&(data))>>2)
#define ISO_IC6_COMP_PARAM_1_get_max_speed_mode(data)                                ((0x0000000C&(data))>>2)
#define ISO_IC6_COMP_PARAM_1_apb_data_width_shift                                    (0)
#define ISO_IC6_COMP_PARAM_1_apb_data_width_mask                                     (0x00000003)
#define ISO_IC6_COMP_PARAM_1_apb_data_width(data)                                    (0x00000003&((data)<<0))
#define ISO_IC6_COMP_PARAM_1_apb_data_width_src(data)                                ((0x00000003&(data))>>0)
#define ISO_IC6_COMP_PARAM_1_get_apb_data_width(data)                                ((0x00000003&(data))>>0)


#define ISO_IC6_COMP_VERSION                                                         0x18007EF8
#define ISO_IC6_COMP_VERSION_reg_addr                                                "0xB8007EF8"
#define ISO_IC6_COMP_VERSION_reg                                                     0xB8007EF8
#define set_ISO_IC6_COMP_VERSION_reg(data)   (*((volatile unsigned int*) ISO_IC6_COMP_VERSION_reg)=data)
#define get_ISO_IC6_COMP_VERSION_reg   (*((volatile unsigned int*) ISO_IC6_COMP_VERSION_reg))
#define ISO_IC6_COMP_VERSION_inst_adr                                                "0x00BE"
#define ISO_IC6_COMP_VERSION_inst                                                    0x00BE
#define ISO_IC6_COMP_VERSION_ic_comp_version_shift                                   (0)
#define ISO_IC6_COMP_VERSION_ic_comp_version_mask                                    (0xFFFFFFFF)
#define ISO_IC6_COMP_VERSION_ic_comp_version(data)                                   (0xFFFFFFFF&((data)<<0))
#define ISO_IC6_COMP_VERSION_ic_comp_version_src(data)                               ((0xFFFFFFFF&(data))>>0)
#define ISO_IC6_COMP_VERSION_get_ic_comp_version(data)                               ((0xFFFFFFFF&(data))>>0)


#define ISO_IC6_COMP_TYPE                                                            0x18007EFC
#define ISO_IC6_COMP_TYPE_reg_addr                                                   "0xB8007EFC"
#define ISO_IC6_COMP_TYPE_reg                                                        0xB8007EFC
#define set_ISO_IC6_COMP_TYPE_reg(data)   (*((volatile unsigned int*) ISO_IC6_COMP_TYPE_reg)=data)
#define get_ISO_IC6_COMP_TYPE_reg   (*((volatile unsigned int*) ISO_IC6_COMP_TYPE_reg))
#define ISO_IC6_COMP_TYPE_inst_adr                                                   "0x00BF"
#define ISO_IC6_COMP_TYPE_inst                                                       0x00BF
#define ISO_IC6_COMP_TYPE_ic_comp_type_shift                                         (0)
#define ISO_IC6_COMP_TYPE_ic_comp_type_mask                                          (0xFFFFFFFF)
#define ISO_IC6_COMP_TYPE_ic_comp_type(data)                                         (0xFFFFFFFF&((data)<<0))
#define ISO_IC6_COMP_TYPE_ic_comp_type_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define ISO_IC6_COMP_TYPE_get_ic_comp_type(data)                                     ((0xFFFFFFFF&(data))>>0)


#define ISO_PWM_OCD                                                                  0x180070D0
#define ISO_PWM_OCD_reg_addr                                                         "0xB80070D0"
#define ISO_PWM_OCD_reg                                                              0xB80070D0
#define set_ISO_PWM_OCD_reg(data)   (*((volatile unsigned int*) ISO_PWM_OCD_reg)=data)
#define get_ISO_PWM_OCD_reg   (*((volatile unsigned int*) ISO_PWM_OCD_reg))
#define ISO_PWM_OCD_inst_adr                                                         "0x0034"
#define ISO_PWM_OCD_inst                                                             0x0034
#define ISO_PWM_OCD_3_shift                                                          (24)
#define ISO_PWM_OCD_3_mask                                                           (0xFF000000)
#define ISO_PWM_OCD_3(data)                                                          (0xFF000000&((data)<<24))
#define ISO_PWM_OCD_3_src(data)                                                      ((0xFF000000&(data))>>24)
#define ISO_PWM_OCD_get_3(data)                                                      ((0xFF000000&(data))>>24)
#define ISO_PWM_OCD_2_shift                                                          (16)
#define ISO_PWM_OCD_2_mask                                                           (0x00FF0000)
#define ISO_PWM_OCD_2(data)                                                          (0x00FF0000&((data)<<16))
#define ISO_PWM_OCD_2_src(data)                                                      ((0x00FF0000&(data))>>16)
#define ISO_PWM_OCD_get_2(data)                                                      ((0x00FF0000&(data))>>16)
#define ISO_PWM_OCD_1_shift                                                          (8)
#define ISO_PWM_OCD_1_mask                                                           (0x0000FF00)
#define ISO_PWM_OCD_1(data)                                                          (0x0000FF00&((data)<<8))
#define ISO_PWM_OCD_1_src(data)                                                      ((0x0000FF00&(data))>>8)
#define ISO_PWM_OCD_get_1(data)                                                      ((0x0000FF00&(data))>>8)
#define ISO_PWM_OCD_0_shift                                                          (0)
#define ISO_PWM_OCD_0_mask                                                           (0x000000FF)
#define ISO_PWM_OCD_0(data)                                                          (0x000000FF&((data)<<0))
#define ISO_PWM_OCD_0_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_PWM_OCD_get_0(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_PWM_CD                                                                   0x180070D4
#define ISO_PWM_CD_reg_addr                                                          "0xB80070D4"
#define ISO_PWM_CD_reg                                                               0xB80070D4
#define set_ISO_PWM_CD_reg(data)   (*((volatile unsigned int*) ISO_PWM_CD_reg)=data)
#define get_ISO_PWM_CD_reg   (*((volatile unsigned int*) ISO_PWM_CD_reg))
#define ISO_PWM_CD_inst_adr                                                          "0x0035"
#define ISO_PWM_CD_inst                                                              0x0035
#define ISO_PWM_CD_3_shift                                                           (24)
#define ISO_PWM_CD_3_mask                                                            (0xFF000000)
#define ISO_PWM_CD_3(data)                                                           (0xFF000000&((data)<<24))
#define ISO_PWM_CD_3_src(data)                                                       ((0xFF000000&(data))>>24)
#define ISO_PWM_CD_get_3(data)                                                       ((0xFF000000&(data))>>24)
#define ISO_PWM_CD_2_shift                                                           (16)
#define ISO_PWM_CD_2_mask                                                            (0x00FF0000)
#define ISO_PWM_CD_2(data)                                                           (0x00FF0000&((data)<<16))
#define ISO_PWM_CD_2_src(data)                                                       ((0x00FF0000&(data))>>16)
#define ISO_PWM_CD_get_2(data)                                                       ((0x00FF0000&(data))>>16)
#define ISO_PWM_CD_1_shift                                                           (8)
#define ISO_PWM_CD_1_mask                                                            (0x0000FF00)
#define ISO_PWM_CD_1(data)                                                           (0x0000FF00&((data)<<8))
#define ISO_PWM_CD_1_src(data)                                                       ((0x0000FF00&(data))>>8)
#define ISO_PWM_CD_get_1(data)                                                       ((0x0000FF00&(data))>>8)
#define ISO_PWM_CD_0_shift                                                           (0)
#define ISO_PWM_CD_0_mask                                                            (0x000000FF)
#define ISO_PWM_CD_0(data)                                                           (0x000000FF&((data)<<0))
#define ISO_PWM_CD_0_src(data)                                                       ((0x000000FF&(data))>>0)
#define ISO_PWM_CD_get_0(data)                                                       ((0x000000FF&(data))>>0)


#define ISO_PWM_CSD                                                                  0x180070D8
#define ISO_PWM_CSD_reg_addr                                                         "0xB80070D8"
#define ISO_PWM_CSD_reg                                                              0xB80070D8
#define set_ISO_PWM_CSD_reg(data)   (*((volatile unsigned int*) ISO_PWM_CSD_reg)=data)
#define get_ISO_PWM_CSD_reg   (*((volatile unsigned int*) ISO_PWM_CSD_reg))
#define ISO_PWM_CSD_inst_adr                                                         "0x0036"
#define ISO_PWM_CSD_inst                                                             0x0036
#define ISO_PWM_CSD_3_shift                                                          (12)
#define ISO_PWM_CSD_3_mask                                                           (0x0000F000)
#define ISO_PWM_CSD_3(data)                                                          (0x0000F000&((data)<<12))
#define ISO_PWM_CSD_3_src(data)                                                      ((0x0000F000&(data))>>12)
#define ISO_PWM_CSD_get_3(data)                                                      ((0x0000F000&(data))>>12)
#define ISO_PWM_CSD_2_shift                                                          (8)
#define ISO_PWM_CSD_2_mask                                                           (0x00000F00)
#define ISO_PWM_CSD_2(data)                                                          (0x00000F00&((data)<<8))
#define ISO_PWM_CSD_2_src(data)                                                      ((0x00000F00&(data))>>8)
#define ISO_PWM_CSD_get_2(data)                                                      ((0x00000F00&(data))>>8)
#define ISO_PWM_CSD_1_shift                                                          (4)
#define ISO_PWM_CSD_1_mask                                                           (0x000000F0)
#define ISO_PWM_CSD_1(data)                                                          (0x000000F0&((data)<<4))
#define ISO_PWM_CSD_1_src(data)                                                      ((0x000000F0&(data))>>4)
#define ISO_PWM_CSD_get_1(data)                                                      ((0x000000F0&(data))>>4)
#define ISO_PWM_CSD_0_shift                                                          (0)
#define ISO_PWM_CSD_0_mask                                                           (0x0000000F)
#define ISO_PWM_CSD_0(data)                                                          (0x0000000F&((data)<<0))
#define ISO_PWM_CSD_0_src(data)                                                      ((0x0000000F&(data))>>0)
#define ISO_PWM_CSD_get_0(data)                                                      ((0x0000000F&(data))>>0)


#endif
