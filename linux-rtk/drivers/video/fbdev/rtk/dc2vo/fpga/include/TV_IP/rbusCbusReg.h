/**
* @file rbusCBUSReg.h
* RBus systemc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2013/5/17
* @version 802
* @ingroup model_rbus
*
*/

#ifndef _RBUS_CBUS_REG_H_
#define _RBUS_CBUS_REG_H_

#include "rbusTypes.h"




// CBUS Register Address

#define CBUS_STANDBY_00_VADDR                 (0xb8037400)
#define CBUS_STANDBY_01_VADDR                 (0xb8037404)
#define CBUS_STANDBY_02_VADDR                 (0xb8037408)
#define CBUS_STANDBY_04_VADDR                 (0xb8037410)
#define CBUS_STANDBY_05_VADDR                 (0xb8037414)
#define CBUS_STANDBY_06_VADDR                 (0xb8037418)
#define CBUS_STANDBY_07_VADDR                 (0xb803741c)
#define CBUS_STANDBY_08_VADDR                 (0xb8037420)
#define CBUS_STANDBY_09_VADDR                 (0xb8037424)
#define CBUS_CBUS_PHY_0_VADDR                      (0xb8037430)
#define CBUS_CBUS_PHY_1_VADDR                      (0xb8037434)
#define CBUS_CBUS_PHY_2_VADDR                      (0xb8037438)
#define CBUS_CBUS_PHY_3_VADDR                      (0xb803743c)
#define CBUS_MSC_REG_00_VADDR                      (0xb800f000)
#define CBUS_MSC_REG_01_VADDR                      (0xb800f004)
#define CBUS_MSC_REG_02_VADDR                      (0xb800f008)
#define CBUS_MSC_REG_03_VADDR                      (0xb800f00c)
#define CBUS_MSC_REG_04_VADDR                      (0xb800f010)
#define CBUS_MSC_REG_05_VADDR                      (0xb800f014)
#define CBUS_MSC_REG_06_VADDR                      (0xb800f018)
#define CBUS_MSC_REG_07_VADDR                      (0xb800f01c)
#define CBUS_MSC_REG_08_VADDR                      (0xb800f020)
#define CBUS_MSC_REG_09_VADDR                      (0xb800f024)
#define CBUS_MSC_REG_0A_VADDR                      (0xb800f028)
#define CBUS_MSC_REG_0B_VADDR                      (0xb800f02c)
#define CBUS_MSC_REG_0C_VADDR                      (0xb800f030)
#define CBUS_MSC_REG_0D_VADDR                      (0xb800f034)
#define CBUS_MSC_REG_0E_VADDR                      (0xb800f038)
#define CBUS_MSC_REG_0F_VADDR                      (0xb800f03c)
#define CBUS_MSC_REG_20_VADDR                      (0xb800f080)
#define CBUS_MSC_REG_21_VADDR                      (0xb800f084)
#define CBUS_MSC_REG_22_VADDR                      (0xb800f088)
#define CBUS_MSC_REG_23_VADDR                      (0xb800f08c)
#define CBUS_MSC_REG_24_VADDR                      (0xb800f090)
#define CBUS_MSC_REG_25_VADDR                      (0xb800f094)
#define CBUS_MSC_REG_26_VADDR                      (0xb800f098)
#define CBUS_MSC_REG_27_VADDR                      (0xb800f09c)
#define CBUS_MSC_REG_30_VADDR                      (0xb800f0c0)
#define CBUS_MSC_REG_31_VADDR                      (0xb800f0c4)
#define CBUS_MSC_REG_32_VADDR                      (0xb800f0c8)
#define CBUS_MSC_REG_33_VADDR                      (0xb800f0cc)
#define CBUS_MSC_REG_34_VADDR                      (0xb800f0d0)
#define CBUS_MSC_REG_35_VADDR                      (0xb800f0d4)
#define CBUS_MSC_REG_36_VADDR                      (0xb800f0d8)
#define CBUS_MSC_REG_37_VADDR                      (0xb800f0dc)
#define CBUS_MSC_REG_40_VADDR                      (0xb800f100)
#define CBUS_MSC_REG_41_VADDR                      (0xb800f104)
#define CBUS_MSC_REG_42_VADDR                      (0xb800f108)
#define CBUS_MSC_REG_43_VADDR                      (0xb800f10c)
#define CBUS_MSC_REG_44_VADDR                      (0xb800f110)
#define CBUS_MSC_REG_45_VADDR                      (0xb800f114)
#define CBUS_MSC_REG_46_VADDR                      (0xb800f118)
#define CBUS_MSC_REG_47_VADDR                      (0xb800f11c)
#define CBUS_MSC_REG_48_VADDR                      (0xb800f120)
#define CBUS_MSC_REG_49_VADDR                      (0xb800f124)
#define CBUS_MSC_REG_4A_VADDR                      (0xb800f128)
#define CBUS_MSC_REG_4B_VADDR                      (0xb800f12c)
#define CBUS_MSC_REG_4C_VADDR                      (0xb800f130)
#define CBUS_MSC_REG_4D_VADDR                      (0xb800f134)
#define CBUS_MSC_REG_4E_VADDR                      (0xb800f138)
#define CBUS_MSC_REG_4F_VADDR                      (0xb800f13c)
#define CBUS_MSC_REG_50_VADDR                      (0xb800f140)
#define CBUS_MSC_REG_51_VADDR                      (0xb800f144)
#define CBUS_MSC_REG_52_VADDR                      (0xb800f148)
#define CBUS_MSC_REG_53_VADDR                      (0xb800f14c)
#define CBUS_MSC_REG_54_VADDR                      (0xb800f150)
#define CBUS_MSC_REG_55_VADDR                      (0xb800f154)
#define CBUS_MSC_REG_56_VADDR                      (0xb800f158)
#define CBUS_MSC_REG_57_VADDR                      (0xb800f15c)
#define CBUS_MSC_REG_58_VADDR                      (0xb800f160)
#define CBUS_MSC_REG_59_VADDR                      (0xb800f164)
#define CBUS_MSC_REG_5A_VADDR                      (0xb800f168)
#define CBUS_MSC_REG_5B_VADDR                      (0xb800f16c)
#define CBUS_MSC_REG_5C_VADDR                      (0xb800f170)
#define CBUS_MSC_REG_5D_VADDR                      (0xb800f174)
#define CBUS_MSC_REG_5E_VADDR                      (0xb800f178)
#define CBUS_MSC_REG_5F_VADDR                      (0xb800f17c)
#define CBUS_LINK_00_VADDR                    (0xb800f200)
#define CBUS_LINK_01_VADDR                    (0xb800f204)
#define CBUS_LINK_02_VADDR                    (0xb800f208)
#define CBUS_LINK_03_VADDR                    (0xb800f20c)
#define CBUS_LINK_04_VADDR                    (0xb800f210)
#define CBUS_LINK_05_VADDR                    (0xb800f214)
#define CBUS_LINK_06_VADDR                    (0xb800f218)
#define CBUS_LINK_07_VADDR                    (0xb800f21c)
#define CBUS_LINK_08_VADDR                    (0xb800f220)
#define CBUS_LINK_09_VADDR                    (0xb800f224)
#define CBUS_LINK_0A_VADDR                    (0xb800f228)
#define CBUS_LINK_0B_VADDR                    (0xb800f22c)
#define CBUS_LINK_0C_VADDR                    (0xb800f230)
#define CBUS_LINK_0D_VADDR                    (0xb800f234)
#define CBUS_LINK_0E_VADDR                    (0xb800f238)
#define CBUS_LINK_0F_VADDR                    (0xb800f23c)
#define CBUS_LINK_10_VADDR                    (0xb800f240)
#define CBUS_LINK_11_VADDR                    (0xb800f244)
#define CBUS_LINK_12_VADDR                    (0xb800f248)
#define CBUS_LINK_13_VADDR                    (0xb800f24c)
#define CBUS_LINK_14_VADDR                    (0xb800f250)
#define CBUS_MSC_00_VADDR                     (0xb800f260)
#define CBUS_MSC_01_VADDR                     (0xb800f264)
#define CBUS_MSC_02_VADDR                     (0xb800f268)
#define CBUS_MSC_03_VADDR                     (0xb800f26c)
#define CBUS_MSC_04_VADDR                     (0xb800f270)
#define CBUS_MSC_05_VADDR                     (0xb800f274)
#define CBUS_MSC_06_VADDR                     (0xb800f278)
#define CBUS_MSC_07_VADDR                     (0xb800f27c)
#define CBUS_MSC_08_VADDR                     (0xb800f280)
#define CBUS_MSC_09_VADDR                     (0xb800f284)
#define CBUS_MSC_0A_VADDR                     (0xb800f288)
#define CBUS_MSC_0B_VADDR                     (0xb800f28c)
#define CBUS_MSC_0C_VADDR                     (0xb800f290)
#define CBUS_MSC_0D_VADDR                     (0xb800f294)
#define CBUS_MSC_0E_VADDR                     (0xb800f298)
#define CBUS_MSC_0F_VADDR                     (0xb800f29c)
#define CBUS_MSC_10_VADDR                     (0xb800f2a0)
#define CBUS_MSC_11_VADDR                     (0xb800f2a4)
#define CBUS_MSC_12_VADDR                     (0xb800f2a8)
#define CBUS_MSC_13_VADDR                     (0xb800f2ac)
#define CBUS_MSC_14_VADDR                     (0xb800f2b0)
#define CBUS_MSC_15_VADDR                     (0xb800f2b4)
#define CBUS_MSC_16_VADDR                     (0xb800f2b8)
#define CBUS_MSC_17_VADDR                     (0xb800f2bc)
#define CBUS_MSC_18_VADDR                     (0xb800f2c0)
#define CBUS_MSC_19_VADDR                     (0xb800f2c4)
#define CBUS_MSC_1A_VADDR                     (0xb800f2c8)
#define CBUS_MSC_1B_VADDR                     (0xb800f2cc)
#define CBUS_MSC_1C_VADDR                     (0xb800f2d0)
#define CBUS_MSC_1D_VADDR                     (0xb800f2d4)
#define CBUS_MSC_1E_VADDR                     (0xb800f2d8)
#define CBUS_MSC_1F_VADDR                     (0xb800f2dc)
#define CBUS_MSC_20_VADDR                     (0xb800f2e0)
#define CBUS_MSC_21_VADDR                     (0xb800f2e4)
#define CBUS_MSC_22_VADDR                     (0xb800f2e8)
#define CBUS_FW0_REQ_00_VADDR                      (0xb800f300)
#define CBUS_FW0_REQ_01_VADDR                      (0xb800f304)
#define CBUS_FW0_REQ_02_VADDR                      (0xb800f308)
#define CBUS_FW0_REQ_03_VADDR                      (0xb800f30c)
#define CBUS_FW0_REQ_04_VADDR                      (0xb800f310)
#define CBUS_FW0_REQ_05_VADDR                      (0xb800f314)
#define CBUS_FW0_REQ_06_VADDR                      (0xb800f318)
#define CBUS_FW0_REQ_07_VADDR                      (0xb800f31c)
#define CBUS_FW0_REQ_08_VADDR                      (0xb800f320)
#define CBUS_FW1_REQ_00_VADDR                      (0xb800f340)
#define CBUS_FW1_REQ_01_VADDR                      (0xb800f344)
#define CBUS_FW1_REQ_02_VADDR                      (0xb800f348)
#define CBUS_FW1_REQ_03_VADDR                      (0xb800f34c)
#define CBUS_FW1_REQ_04_VADDR                      (0xb800f350)
#define CBUS_FW1_REQ_05_VADDR                      (0xb800f354)
#define CBUS_FW1_REQ_06_VADDR                      (0xb800f358)
#define CBUS_FW1_REQ_07_VADDR                      (0xb800f35c)
#define CBUS_FW1_REQ_08_VADDR                      (0xb800f360)
#define CBUS_FW2_REQ_00_VADDR                      (0xb800f380)
#define CBUS_FW2_REQ_01_VADDR                      (0xb800f384)
#define CBUS_FW2_REQ_02_VADDR                      (0xb800f388)
#define CBUS_FW2_REQ_03_VADDR                      (0xb800f38c)
#define CBUS_FW2_REQ_04_VADDR                      (0xb800f390)
#define CBUS_FW2_REQ_05_VADDR                      (0xb800f394)
#define CBUS_FW2_REQ_06_VADDR                      (0xb800f398)
#define CBUS_FW2_REQ_07_VADDR                      (0xb800f39c)
#define CBUS_FW2_REQ_08_VADDR                      (0xb800f3a0)
#define CBUS_DDC_00_VADDR                     (0xb800f3c0)
#define CBUS_DDC_01_VADDR                     (0xb800f3c4)
#define CBUS_DDC_02_VADDR                     (0xb800f3c8)
#define CBUS_DDC_03_VADDR                     (0xb800f3cc)
#define CBUS_DDC_04_VADDR                     (0xb800f3d0)
#define CBUS_DDC_05_VADDR                     (0xb800f3d4)
#define CBUS_DDC_06_VADDR                     (0xb800f3d8)
#define CBUS_CBUS_WDOG_VADDR                       (0xb800f3e0)
#define CBUS_INT_INDEX_VADDR                  (0xb800f3e4)
#define CBUS_TEST_VADDR                       (0xb800f3e8)
#define CBUS_DUMMY0_VADDR                     (0xb800f3ec)




#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======CBUS register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  wake_pulse_det:1;
        RBus_UInt32  dis_pulse_det:1;
        RBus_UInt32  wake_irq_en:1;
        RBus_UInt32  dis_irq_en:1;
    };
}cbus_standby_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  clk_1m_div:4;
        RBus_UInt32  clk_1k_div:10;
    };
}cbus_standby_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  dis_deb_lv:3;
        RBus_UInt32  deb_lv:3;
        RBus_UInt32  disconn:2;
    };
}cbus_standby_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  wake_offset_low2:3;
        RBus_UInt32  wake_offset_low:3;
        RBus_UInt32  wake_cnt:3;
        RBus_UInt32  wake_offset:3;
        RBus_UInt32  cbus_disconn:1;
        RBus_UInt32  disconn_irq_en:1;
    };
}cbus_standby_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  dis_upper:4;
        RBus_UInt32  dis_lower:3;
        RBus_UInt32  wake_eco_en:1;
    };
}cbus_standby_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  wake_num:3;
        RBus_UInt32  dis_num:5;
    };
}cbus_standby_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  cbus_imp_auto:1;
        RBus_UInt32  bypass_mode:1;
        RBus_UInt32  sink_fsm_st:3;
        RBus_UInt32  cbus_100k_en:1;
        RBus_UInt32  cbus_1k_en:1;
        RBus_UInt32  cbus_in_sig:1;
    };
}cbus_standby_07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  goto_sink1_pos:1;
        RBus_UInt32  goto_float:1;
        RBus_UInt32  goto_sink1:1;
        RBus_UInt32  cable_det:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  dbg_sel_phy:1;
    };
}cbus_standby_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ctrl_09_resv:32;
    };
}cbus_standby_09_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  cbus_sr:1;
        RBus_UInt32  cbus_smt:1;
        RBus_UInt32  cbus_pu:1;
        RBus_UInt32  cbus_pd:1;
        RBus_UInt32  cbus_i:1;
        RBus_UInt32  cbus_e2:1;
        RBus_UInt32  cbus_e:1;
    };
}cbus_phy_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adjr_1k:4;
        RBus_UInt32  adjr_100k:5;
        RBus_UInt32  auto_k_1k:1;
        RBus_UInt32  auto_k_100k:1;
        RBus_UInt32  en_res_cal_cbus:1;
        RBus_UInt32  sel_cbus0_input_high:2;
        RBus_UInt32  sel_cbus0_input_low:2;
        RBus_UInt32  sel_cbus_0_driving:3;
        RBus_UInt32  sel_vref_ldo:2;
        RBus_UInt32  trim_ldo_cbus:4;
        RBus_UInt32  triming_mode:1;
        RBus_UInt32  en_cbus:1;
        RBus_UInt32  en_cmp_cbus:1;
        RBus_UInt32  en_driver_cbus:1;
        RBus_UInt32  en_ldo_cbus:1;
        RBus_UInt32  psm_cbus:1;
        RBus_UInt32  sel_cbusb_gpio:1;
    };
}cbus_phy_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  cbus_o:1;
    };
}cbus_phy_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  sel_phy_soft_rst_n:1;
        RBus_UInt32  cbus_res_tst:10;
        RBus_UInt32  res_ok:1;
    };
}cbus_phy_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  dev_state:8;
    };
}msc_reg_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  mhl_ver:8;
    };
}msc_reg_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  dev_cat:1;
        RBus_UInt32  plim:2;
        RBus_UInt32  pow:1;
        RBus_UInt32  dev_type:4;
    };
}msc_reg_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  adop_id_h:8;
    };
}msc_reg_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  adop_id_l:8;
    };
}msc_reg_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vid_link_md:2;
        RBus_UInt32  supp_vga:1;
        RBus_UInt32  supp_islands:1;
        RBus_UInt32  supp_ppixel:1;
        RBus_UInt32  supp_yuv422:1;
        RBus_UInt32  supp_yuv444:1;
        RBus_UInt32  supp_rgb444:1;
    };
}msc_reg_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  aud_link_md:6;
        RBus_UInt32  aud_8ch:1;
        RBus_UInt32  aud_2ch:1;
    };
}msc_reg_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  supp_vt:1;
        RBus_UInt32  video_type:3;
        RBus_UInt32  vt_game:1;
        RBus_UInt32  vt_cinema:1;
        RBus_UInt32  vt_photo:1;
        RBus_UInt32  vt_graphics:1;
    };
}msc_reg_07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  ld_gui:1;
        RBus_UInt32  ld_speaker:1;
        RBus_UInt32  ld_record:1;
        RBus_UInt32  ld_tuner:1;
        RBus_UInt32  ld_media:1;
        RBus_UInt32  ld_audio:1;
        RBus_UInt32  ld_video:1;
        RBus_UInt32  ld_display:1;
    };
}msc_reg_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  bandwid:8;
    };
}msc_reg_09_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  feature_flag:3;
        RBus_UInt32  ucp_recv_supp:1;
        RBus_UInt32  ucp_send_supp:1;
        RBus_UInt32  sp_supp:1;
        RBus_UInt32  rap_supp:1;
        RBus_UInt32  rcp_supp:1;
    };
}msc_reg_0a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  device_id_h:8;
    };
}msc_reg_0b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  device_id_l:8;
    };
}msc_reg_0c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scr_size:8;
    };
}msc_reg_0d_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  stat_size:4;
        RBus_UInt32  int_size:4;
    };
}msc_reg_0e_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  cap_0f:8;
    };
}msc_reg_0f_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  rchg_int_7:1;
        RBus_UInt32  rchg_int_6:1;
        RBus_UInt32  rchg_int_5:1;
        RBus_UInt32  cbus_3d_req:1;
        RBus_UInt32  grt_wrt:1;
        RBus_UInt32  req_wrt:1;
        RBus_UInt32  dscr_chg:1;
        RBus_UInt32  dcap_chg:1;
    };
}msc_reg_20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  dchg_int_7:1;
        RBus_UInt32  dchg_int_6:1;
        RBus_UInt32  dchg_int_5:1;
        RBus_UInt32  dchg_int_4:1;
        RBus_UInt32  dchg_int_3:1;
        RBus_UInt32  dchg_int_2:1;
        RBus_UInt32  edid_chg:1;
        RBus_UInt32  dchg_int_0:1;
    };
}msc_reg_21_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  chg22_7:1;
        RBus_UInt32  chg22_6:1;
        RBus_UInt32  chg22_5:1;
        RBus_UInt32  chg22_4:1;
        RBus_UInt32  chg22_3:1;
        RBus_UInt32  chg22_2:1;
        RBus_UInt32  chg22_1:1;
        RBus_UInt32  chg22_0:1;
    };
}msc_reg_22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  chg23_7:1;
        RBus_UInt32  chg23_6:1;
        RBus_UInt32  chg23_5:1;
        RBus_UInt32  chg23_4:1;
        RBus_UInt32  chg23_3:1;
        RBus_UInt32  chg23_2:1;
        RBus_UInt32  chg23_1:1;
        RBus_UInt32  chg23_0:1;
    };
}msc_reg_23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  chg24_7:1;
        RBus_UInt32  chg24_6:1;
        RBus_UInt32  chg24_5:1;
        RBus_UInt32  chg24_4:1;
        RBus_UInt32  chg24_3:1;
        RBus_UInt32  chg24_2:1;
        RBus_UInt32  chg24_1:1;
        RBus_UInt32  chg24_0:1;
    };
}msc_reg_24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  chg25_7:1;
        RBus_UInt32  chg25_6:1;
        RBus_UInt32  chg25_5:1;
        RBus_UInt32  chg25_4:1;
        RBus_UInt32  chg25_3:1;
        RBus_UInt32  chg25_2:1;
        RBus_UInt32  chg25_1:1;
        RBus_UInt32  chg25_0:1;
    };
}msc_reg_25_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  chg26_7:1;
        RBus_UInt32  chg26_6:1;
        RBus_UInt32  chg26_5:1;
        RBus_UInt32  chg26_4:1;
        RBus_UInt32  chg26_3:1;
        RBus_UInt32  chg26_2:1;
        RBus_UInt32  chg26_1:1;
        RBus_UInt32  chg26_0:1;
    };
}msc_reg_26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  chg27_7:1;
        RBus_UInt32  chg27_6:1;
        RBus_UInt32  chg27_5:1;
        RBus_UInt32  chg27_4:1;
        RBus_UInt32  chg27_3:1;
        RBus_UInt32  chg27_2:1;
        RBus_UInt32  chg27_1:1;
        RBus_UInt32  chg27_0:1;
    };
}msc_reg_27_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  conn_rdy:7;
        RBus_UInt32  dcap_rdy:1;
    };
}msc_reg_30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  link_mode:3;
        RBus_UInt32  muted:1;
        RBus_UInt32  path_en:1;
        RBus_UInt32  clk_mode:3;
    };
}msc_reg_31_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  stat_32:8;
    };
}msc_reg_32_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  stat_33:8;
    };
}msc_reg_33_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  stat_34:8;
    };
}msc_reg_34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  stat_35:8;
    };
}msc_reg_35_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  stat_36:8;
    };
}msc_reg_36_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  stat_37:8;
    };
}msc_reg_37_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_40:8;
    };
}msc_reg_40_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_41:8;
    };
}msc_reg_41_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_42:8;
    };
}msc_reg_42_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_43:8;
    };
}msc_reg_43_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_44:8;
    };
}msc_reg_44_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_45:8;
    };
}msc_reg_45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_46:8;
    };
}msc_reg_46_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_47:8;
    };
}msc_reg_47_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_48:8;
    };
}msc_reg_48_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_49:8;
    };
}msc_reg_49_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_4a:8;
    };
}msc_reg_4a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_4b:8;
    };
}msc_reg_4b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_4c:8;
    };
}msc_reg_4c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_4d:8;
    };
}msc_reg_4d_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_4e:8;
    };
}msc_reg_4e_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_4f:8;
    };
}msc_reg_4f_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_50:8;
    };
}msc_reg_50_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_51:8;
    };
}msc_reg_51_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_52:8;
    };
}msc_reg_52_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_53:8;
    };
}msc_reg_53_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_54:8;
    };
}msc_reg_54_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_55:8;
    };
}msc_reg_55_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_56:8;
    };
}msc_reg_56_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_57:8;
    };
}msc_reg_57_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_58:8;
    };
}msc_reg_58_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_59:8;
    };
}msc_reg_59_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_5a:8;
    };
}msc_reg_5a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_5b:8;
    };
}msc_reg_5b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_5c:8;
    };
}msc_reg_5c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_5d:8;
    };
}msc_reg_5d_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_5e:8;
    };
}msc_reg_5e_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scratch_5f:8;
    };
}msc_reg_5f_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  sync0_hb:9;
        RBus_UInt32  sync0_lb:9;
    };
}cbus_link_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  sync1_hb:8;
        RBus_UInt32  sync1_lb:8;
    };
}cbus_link_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  sync_bit_time:8;
    };
}cbus_link_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  abs_thres_en:1;
        RBus_UInt32  abs_threshold:8;
    };
}cbus_link_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  parity_time:8;
    };
}cbus_link_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  parity_fail:1;
        RBus_UInt32  parity_irq_en:1;
        RBus_UInt32  ctrl_16_resv:1;
        RBus_UInt32  parity_limit:5;
    };
}cbus_link_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  ack_fall:7;
    };
}cbus_link_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  ack_0:7;
    };
}cbus_link_07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  tx_bit_time:8;
    };
}cbus_link_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  chk_win_up:3;
        RBus_UInt32  chk_win_lo:2;
        RBus_UInt32  fast_reply_en:1;
        RBus_UInt32  ctrl_1b_resv:2;
    };
}cbus_link_09_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  res2:1;
        RBus_UInt32  tx_ack_fal:7;
    };
}cbus_link_0a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  tx_ack_low_hb:7;
    };
}cbus_link_0b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  tx_ack_low_lb:7;
    };
}cbus_link_0c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  retry_lv:3;
        RBus_UInt32  retry_flag:1;
        RBus_UInt32  ctrl_1f_resv:4;
    };
}cbus_link_0d_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  drv_str:2;
        RBus_UInt32  drv_hi_cbus:6;
    };
}cbus_link_0e_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  wait:4;
        RBus_UInt32  req_opp_int:2;
    };
}cbus_link_0f_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  req_opp_flt:8;
    };
}cbus_link_10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  req_cont:8;
    };
}cbus_link_11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  req_hold:4;
        RBus_UInt32  resp_hold:4;
    };
}cbus_link_12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  glob_time:2;
        RBus_UInt32  link_time:5;
        RBus_UInt32  link_err:1;
    };
}cbus_link_13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  chk_point:6;
        RBus_UInt32  chk_err:1;
        RBus_UInt32  avoid_conf:1;
    };
}cbus_link_14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  mcumsc_en:1;
        RBus_UInt32  msc_wait_arb:1;
        RBus_UInt32  ctrl_28_resv:4;
    };
}cbus_msc_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  na_msc_cmd:8;
    };
}cbus_msc_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  na_msc_offset:8;
    };
}cbus_msc_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  rx_fifo_full:1;
        RBus_UInt32  rx_fifo_empty:1;
        RBus_UInt32  rx_fifo_clr:1;
        RBus_UInt32  na_rx_len:5;
    };
}cbus_msc_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  rx_fifo_data:8;
    };
}cbus_msc_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fwdef_cmd_rev:8;
    };
}cbus_msc_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  ucp_irq:1;
        RBus_UInt32  ucpk_irq:1;
        RBus_UInt32  ucpe_irq:1;
        RBus_UInt32  dcap_rdy_chg:1;
        RBus_UInt32  muted_chg:1;
        RBus_UInt32  path_en_chg:1;
        RBus_UInt32  clk_mode_chg:1;
        RBus_UInt32  msge_irq:1;
        RBus_UInt32  rcp_irq:1;
        RBus_UInt32  rcpk_irq:1;
        RBus_UInt32  rcpe_irq:1;
        RBus_UInt32  rap_irq:1;
        RBus_UInt32  rapk_irq:1;
        RBus_UInt32  msg_sub_irq:1;
        RBus_UInt32  wr_stat_irq:1;
        RBus_UInt32  rd_devcap_irq:1;
        RBus_UInt32  get_stat_irq:1;
        RBus_UInt32  get_id_irq:1;
        RBus_UInt32  get_msg_irq:1;
        RBus_UInt32  sc1_err_irq:1;
        RBus_UInt32  ddc_err_irq:1;
        RBus_UInt32  msc_err_irq:1;
        RBus_UInt32  wr_burst_irq:1;
        RBus_UInt32  sc3_err_irq:1;
        RBus_UInt32  fwdef_cmd_irq:1;
        RBus_UInt32  allmsc_cmd_irq:1;
        RBus_UInt32  abort_res_irq:1;
        RBus_UInt32  abort_req_irq:1;
        RBus_UInt32  ddc_abort_irq:1;
    };
}cbus_msc_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  ucp_irq_en:1;
        RBus_UInt32  ucpk_irq_en:1;
        RBus_UInt32  ucpe_irq_en:1;
        RBus_UInt32  dcap_rdy_irq_en:1;
        RBus_UInt32  muted_chg_irq_en:1;
        RBus_UInt32  path_en_irq_en:1;
        RBus_UInt32  clk_mode_irq_en:1;
        RBus_UInt32  msge_irq_en:1;
        RBus_UInt32  rcp_irq_en:1;
        RBus_UInt32  rcpk_irq_en:1;
        RBus_UInt32  rcpe_irq_en:1;
        RBus_UInt32  rap_irq_en:1;
        RBus_UInt32  rapk_irq_en:1;
        RBus_UInt32  msg_sub_irq_en:1;
        RBus_UInt32  wr_stat_irq_en:1;
        RBus_UInt32  rd_devcap_irq_en:1;
        RBus_UInt32  get_stat_irq_en:1;
        RBus_UInt32  get_id_irq_en:1;
        RBus_UInt32  get_msg_irq_en:1;
        RBus_UInt32  sc1_err_irq_en:1;
        RBus_UInt32  ddc_err_irq_en:1;
        RBus_UInt32  msc_err_irq_en:1;
        RBus_UInt32  wr_burst_irq_en:1;
        RBus_UInt32  sc3_err_irq_en:1;
        RBus_UInt32  fwdef_cmd_irq_en:1;
        RBus_UInt32  allmsc_cmd_irq_en:1;
        RBus_UInt32  abort_res_irq_en:1;
        RBus_UInt32  abort_req_irq_en:1;
        RBus_UInt32  ddc_abort_irq_en:1;
    };
}cbus_msc_07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rchg_irq_en:3;
        RBus_UInt32  cbus_3d_req_irq_en:1;
        RBus_UInt32  grt_irq_en:1;
        RBus_UInt32  req_irq_en:1;
        RBus_UInt32  dscr_irq_en:1;
        RBus_UInt32  dcap_irq_en:1;
        RBus_UInt32  dchg_bit7_irq_en:1;
        RBus_UInt32  dchg_bit6_irq_en:1;
        RBus_UInt32  dchg_bit5_irq_en:1;
        RBus_UInt32  dchg_bit4_irq_en:1;
        RBus_UInt32  dchg_bit3_irq_en:1;
        RBus_UInt32  dchg_bit2_irq_en:1;
        RBus_UInt32  edid_irq_en:1;
        RBus_UInt32  dchg_bit0_irq_en:1;
        RBus_UInt32  chg22_irq_en:8;
        RBus_UInt32  chg23_irq_en:8;
    };
}cbus_msc_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chg24_irq_en:8;
        RBus_UInt32  chg25_irq_en:8;
        RBus_UInt32  chg26_irq_en:8;
        RBus_UInt32  chg27_irq_en:8;
    };
}cbus_msc_09_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  msc_err_code:8;
    };
}cbus_msc_0a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  rcp_reply_abort:1;
        RBus_UInt32  rcp_reply_nack:1;
        RBus_UInt32  vendor_id:8;
    };
}cbus_msc_0b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  msg_cmd:8;
    };
}cbus_msc_0c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  msg_dat:8;
    };
}cbus_msc_0d_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  msge_rcv:8;
    };
}cbus_msc_0e_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  rcp_rcv:8;
    };
}cbus_msc_0f_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  rcpk_rcv:8;
    };
}cbus_msc_10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  rcpe_rcv:8;
    };
}cbus_msc_11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  rap_rcv:8;
    };
}cbus_msc_12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  rapk_rcv:8;
    };
}cbus_msc_13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  burst_timeout:1;
        RBus_UInt32  wb_id_chk:1;
        RBus_UInt32  burst_wait:4;
    };
}cbus_msc_14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  adop_idh_rcv:8;
        RBus_UInt32  adop_idl_rcv:8;
    };
}cbus_msc_15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  auto_handshake:1;
        RBus_UInt32  insert_id:1;
        RBus_UInt32  wb_byte_num0:6;
        RBus_UInt32  wb_byte_num1:6;
        RBus_UInt32  adop_txid_h:8;
        RBus_UInt32  adop_txid_l:8;
    };
}cbus_msc_16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  que_fsm_clr:1;
        RBus_UInt32  sch_fsm_clr:1;
        RBus_UInt32  spi_fsm_clr:1;
    };
}cbus_msc_17_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  que_fsm:4;
        RBus_UInt32  sch_fsm:4;
        RBus_UInt32  spi_fsm:4;
    };
}cbus_msc_18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  cap_offset:8;
    };
}cbus_msc_19_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  int_offset:8;
    };
}cbus_msc_1a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  sta_offset:8;
    };
}cbus_msc_1b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  scr_offset:8;
    };
}cbus_msc_1c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  ddc_err_force:1;
        RBus_UInt32  msc_err_force:1;
    };
}cbus_msc_1d_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  ddc_err_fw:8;
    };
}cbus_msc_1e_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  msc_err_fw:8;
    };
}cbus_msc_1f_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  ucp_rcv:8;
    };
}cbus_msc_20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  ucpk_rcv:8;
    };
}cbus_msc_21_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  ucpe_rcv:8;
    };
}cbus_msc_22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  fw0_req:1;
        RBus_UInt32  fw0_fifo_clr:1;
        RBus_UInt32  fw0_fifo_full:1;
        RBus_UInt32  fw0_fifo_empty:1;
        RBus_UInt32  fw0_tx_case:3;
        RBus_UInt32  fw0_head:2;
    };
}fw0_req_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fw0_cmd1:8;
    };
}fw0_req_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fw0_cmd2:8;
    };
}fw0_req_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fw0_offset:8;
    };
}fw0_req_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fw0_data:8;
    };
}fw0_req_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  fw0_rty_ovr:1;
        RBus_UInt32  fw0_fin:1;
        RBus_UInt32  fw0_cmd_event:1;
        RBus_UInt32  fw0_data_event:1;
        RBus_UInt32  fw0_rcv_err:1;
        RBus_UInt32  fw0_fin_irq_en:1;
        RBus_UInt32  fw0_cmd_irq_en:1;
        RBus_UInt32  fw0_data_irq_en:1;
        RBus_UInt32  fw0_wait_case:2;
    };
}fw0_req_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fw0_cmd_rcv:8;
    };
}fw0_req_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fw0_data_rcv:8;
    };
}fw0_req_07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  fw0_rd_en:1;
        RBus_UInt32  fw0_fifo_len:5;
        RBus_UInt32  fw0_rdata:8;
    };
}fw0_req_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  fw1_req:1;
        RBus_UInt32  fw1_fifo_clr:1;
        RBus_UInt32  fw1_fifo_full:1;
        RBus_UInt32  fw1_fifo_empty:1;
        RBus_UInt32  fw1_tx_case:3;
        RBus_UInt32  fw1_head:2;
    };
}fw1_req_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fw1_cmd1:8;
    };
}fw1_req_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fw1_cmd2:8;
    };
}fw1_req_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fw1_offset:8;
    };
}fw1_req_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fw1_data:8;
    };
}fw1_req_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  fw1_rty_ovr:1;
        RBus_UInt32  fw1_fin:1;
        RBus_UInt32  fw1_cmd_event:1;
        RBus_UInt32  fw1_data_event:1;
        RBus_UInt32  fw1_rcv_err:1;
        RBus_UInt32  fw1_fin_irq_en:1;
        RBus_UInt32  fw1_cmd_irq_en:1;
        RBus_UInt32  fw1_data_irq_en:1;
        RBus_UInt32  fw1_wait_case:2;
    };
}fw1_req_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fw1_cmd_rcv:8;
    };
}fw1_req_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fw1_data_rcv:8;
    };
}fw1_req_07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  fw1_rd_en:1;
        RBus_UInt32  fw1_fifo_len:5;
        RBus_UInt32  fw1_rdata:8;
    };
}fw1_req_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  fw2_req:1;
        RBus_UInt32  fw2_fifo_clr:1;
        RBus_UInt32  fw2_fifo_full:1;
        RBus_UInt32  fw2_fifo_empty:1;
        RBus_UInt32  fw2_tx_case:3;
        RBus_UInt32  fw2_head:2;
    };
}fw2_req_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fw2_cmd1:8;
    };
}fw2_req_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fw2_cmd2:8;
    };
}fw2_req_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fw2_offset:8;
    };
}fw2_req_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fw2_data:8;
    };
}fw2_req_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  fw2_rty_ovr:1;
        RBus_UInt32  fw2_fin:1;
        RBus_UInt32  fw2_cmd_event:1;
        RBus_UInt32  fw2_data_event:1;
        RBus_UInt32  fw2_rcv_err:1;
        RBus_UInt32  fw2_fin_irq_en:1;
        RBus_UInt32  fw2_cmd_irq_en:1;
        RBus_UInt32  fw2_data_irq_en:1;
        RBus_UInt32  fw2_wait_case:2;
    };
}fw2_req_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fw2_cmd_rcv:8;
    };
}fw2_req_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fw2_data_rcv:8;
    };
}fw2_req_07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  fw2_rd_en:1;
        RBus_UInt32  fw2_fifo_len:5;
        RBus_UInt32  fw2_rdata:8;
    };
}fw2_req_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  ddc_err_code:8;
    };
}cbus_ddc_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  iic_ck_tgt:8;
    };
}cbus_ddc_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  mcuddc_en:1;
        RBus_UInt32  ddc_prior_dis:1;
        RBus_UInt32  ddc_cmd_event:1;
        RBus_UInt32  ddc_data_event:1;
        RBus_UInt32  ddc_cmd_irq_en:1;
        RBus_UInt32  ddc_data_irq_en:1;
        RBus_UInt32  ddc_req_ctrl:1;
        RBus_UInt32  ddc_req:1;
    };
}cbus_ddc_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  ddc_rcv_cmd:8;
    };
}cbus_ddc_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  ddc_rcv_data:8;
    };
}cbus_ddc_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  ddc_data_fw:8;
    };
}cbus_ddc_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  ddc_eof_irq:1;
        RBus_UInt32  ddc_eof_irq_en:1;
        RBus_UInt32  ddcrd_rst_en:1;
        RBus_UInt32  ddcrd_new_md:1;
    };
}cbus_ddc_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  clk_mod_vwd:1;
        RBus_UInt32  clk_mod_awd:1;
        RBus_UInt32  mute_en_vwd:1;
        RBus_UInt32  mute_en_awd:1;
        RBus_UInt32  path_en_off_vwd:1;
        RBus_UInt32  path_en_off_awd:1;
    };
}cbus_wdog_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  arbiter_irq:1;
        RBus_UInt32  ddc_irq:1;
        RBus_UInt32  msc_ch_irq:1;
        RBus_UInt32  msc_int_irq:1;
        RBus_UInt32  msc_stat_irq:1;
        RBus_UInt32  ctrl_01_resv:1;
    };
}cbus_int_index_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  cbus_test_md:2;
        RBus_UInt32  fw_out:1;
        RBus_UInt32  dbg_sel:3;
        RBus_UInt32  res2:2;
    };
}cbus_test_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cbus_dummy0:32;
    };
}cbus_dummy0_RBUS;





#else //apply LITTLE_ENDIAN


//======CBUS register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dis_irq_en:1;
        RBus_UInt32  wake_irq_en:1;
        RBus_UInt32  dis_pulse_det:1;
        RBus_UInt32  wake_pulse_det:1;
        RBus_UInt32  res1:28;
    };
}cbus_standby_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  clk_1k_div:10;
        RBus_UInt32  clk_1m_div:4;
        RBus_UInt32  res1:18;
    };
}cbus_standby_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  disconn:2;
        RBus_UInt32  deb_lv:3;
        RBus_UInt32  dis_deb_lv:3;
        RBus_UInt32  res1:24;
    };
}cbus_standby_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  disconn_irq_en:1;
        RBus_UInt32  cbus_disconn:1;
        RBus_UInt32  wake_offset:3;
        RBus_UInt32  wake_cnt:3;
        RBus_UInt32  wake_offset_low:3;
        RBus_UInt32  wake_offset_low2:3;
        RBus_UInt32  res1:18;
    };
}cbus_standby_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wake_eco_en:1;
        RBus_UInt32  dis_lower:3;
        RBus_UInt32  dis_upper:4;
        RBus_UInt32  res1:24;
    };
}cbus_standby_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dis_num:5;
        RBus_UInt32  wake_num:3;
        RBus_UInt32  res1:24;
    };
}cbus_standby_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cbus_in_sig:1;
        RBus_UInt32  cbus_1k_en:1;
        RBus_UInt32  cbus_100k_en:1;
        RBus_UInt32  sink_fsm_st:3;
        RBus_UInt32  bypass_mode:1;
        RBus_UInt32  cbus_imp_auto:1;
        RBus_UInt32  res1:24;
    };
}cbus_standby_07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dbg_sel_phy:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  cable_det:1;
        RBus_UInt32  goto_sink1:1;
        RBus_UInt32  goto_float:1;
        RBus_UInt32  goto_sink1_pos:1;
        RBus_UInt32  res1:26;
    };
}cbus_standby_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ctrl_09_resv:32;
    };
}cbus_standby_09_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cbus_e:1;
        RBus_UInt32  cbus_e2:1;
        RBus_UInt32  cbus_i:1;
        RBus_UInt32  cbus_pd:1;
        RBus_UInt32  cbus_pu:1;
        RBus_UInt32  cbus_smt:1;
        RBus_UInt32  cbus_sr:1;
        RBus_UInt32  res1:25;
    };
}cbus_phy_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sel_cbusb_gpio:1;
        RBus_UInt32  psm_cbus:1;
        RBus_UInt32  en_ldo_cbus:1;
        RBus_UInt32  en_driver_cbus:1;
        RBus_UInt32  en_cmp_cbus:1;
        RBus_UInt32  en_cbus:1;
        RBus_UInt32  triming_mode:1;
        RBus_UInt32  trim_ldo_cbus:4;
        RBus_UInt32  sel_vref_ldo:2;
        RBus_UInt32  sel_cbus_0_driving:3;
        RBus_UInt32  sel_cbus0_input_low:2;
        RBus_UInt32  sel_cbus0_input_high:2;
        RBus_UInt32  en_res_cal_cbus:1;
        RBus_UInt32  auto_k_100k:1;
        RBus_UInt32  auto_k_1k:1;
        RBus_UInt32  adjr_100k:5;
        RBus_UInt32  adjr_1k:4;
    };
}cbus_phy_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cbus_o:1;
        RBus_UInt32  res1:31;
    };
}cbus_phy_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res_ok:1;
        RBus_UInt32  cbus_res_tst:10;
        RBus_UInt32  sel_phy_soft_rst_n:1;
        RBus_UInt32  res1:20;
    };
}cbus_phy_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dev_state:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mhl_ver:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dev_type:4;
        RBus_UInt32  pow:1;
        RBus_UInt32  plim:2;
        RBus_UInt32  dev_cat:1;
        RBus_UInt32  res1:24;
    };
}msc_reg_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adop_id_h:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adop_id_l:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  supp_rgb444:1;
        RBus_UInt32  supp_yuv444:1;
        RBus_UInt32  supp_yuv422:1;
        RBus_UInt32  supp_ppixel:1;
        RBus_UInt32  supp_islands:1;
        RBus_UInt32  supp_vga:1;
        RBus_UInt32  vid_link_md:2;
        RBus_UInt32  res1:24;
    };
}msc_reg_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  aud_2ch:1;
        RBus_UInt32  aud_8ch:1;
        RBus_UInt32  aud_link_md:6;
        RBus_UInt32  res1:24;
    };
}msc_reg_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vt_graphics:1;
        RBus_UInt32  vt_photo:1;
        RBus_UInt32  vt_cinema:1;
        RBus_UInt32  vt_game:1;
        RBus_UInt32  video_type:3;
        RBus_UInt32  supp_vt:1;
        RBus_UInt32  res1:24;
    };
}msc_reg_07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ld_display:1;
        RBus_UInt32  ld_video:1;
        RBus_UInt32  ld_audio:1;
        RBus_UInt32  ld_media:1;
        RBus_UInt32  ld_tuner:1;
        RBus_UInt32  ld_record:1;
        RBus_UInt32  ld_speaker:1;
        RBus_UInt32  ld_gui:1;
        RBus_UInt32  res1:24;
    };
}msc_reg_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bandwid:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_09_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rcp_supp:1;
        RBus_UInt32  rap_supp:1;
        RBus_UInt32  sp_supp:1;
        RBus_UInt32  ucp_send_supp:1;
        RBus_UInt32  ucp_recv_supp:1;
        RBus_UInt32  feature_flag:3;
        RBus_UInt32  res1:24;
    };
}msc_reg_0a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  device_id_h:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_0b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  device_id_l:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_0c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scr_size:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_0d_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  int_size:4;
        RBus_UInt32  stat_size:4;
        RBus_UInt32  res1:24;
    };
}msc_reg_0e_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cap_0f:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_0f_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dcap_chg:1;
        RBus_UInt32  dscr_chg:1;
        RBus_UInt32  req_wrt:1;
        RBus_UInt32  grt_wrt:1;
        RBus_UInt32  cbus_3d_req:1;
        RBus_UInt32  rchg_int_5:1;
        RBus_UInt32  rchg_int_6:1;
        RBus_UInt32  rchg_int_7:1;
        RBus_UInt32  res1:24;
    };
}msc_reg_20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dchg_int_0:1;
        RBus_UInt32  edid_chg:1;
        RBus_UInt32  dchg_int_2:1;
        RBus_UInt32  dchg_int_3:1;
        RBus_UInt32  dchg_int_4:1;
        RBus_UInt32  dchg_int_5:1;
        RBus_UInt32  dchg_int_6:1;
        RBus_UInt32  dchg_int_7:1;
        RBus_UInt32  res1:24;
    };
}msc_reg_21_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chg22_0:1;
        RBus_UInt32  chg22_1:1;
        RBus_UInt32  chg22_2:1;
        RBus_UInt32  chg22_3:1;
        RBus_UInt32  chg22_4:1;
        RBus_UInt32  chg22_5:1;
        RBus_UInt32  chg22_6:1;
        RBus_UInt32  chg22_7:1;
        RBus_UInt32  res1:24;
    };
}msc_reg_22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chg23_0:1;
        RBus_UInt32  chg23_1:1;
        RBus_UInt32  chg23_2:1;
        RBus_UInt32  chg23_3:1;
        RBus_UInt32  chg23_4:1;
        RBus_UInt32  chg23_5:1;
        RBus_UInt32  chg23_6:1;
        RBus_UInt32  chg23_7:1;
        RBus_UInt32  res1:24;
    };
}msc_reg_23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chg24_0:1;
        RBus_UInt32  chg24_1:1;
        RBus_UInt32  chg24_2:1;
        RBus_UInt32  chg24_3:1;
        RBus_UInt32  chg24_4:1;
        RBus_UInt32  chg24_5:1;
        RBus_UInt32  chg24_6:1;
        RBus_UInt32  chg24_7:1;
        RBus_UInt32  res1:24;
    };
}msc_reg_24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chg25_0:1;
        RBus_UInt32  chg25_1:1;
        RBus_UInt32  chg25_2:1;
        RBus_UInt32  chg25_3:1;
        RBus_UInt32  chg25_4:1;
        RBus_UInt32  chg25_5:1;
        RBus_UInt32  chg25_6:1;
        RBus_UInt32  chg25_7:1;
        RBus_UInt32  res1:24;
    };
}msc_reg_25_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chg26_0:1;
        RBus_UInt32  chg26_1:1;
        RBus_UInt32  chg26_2:1;
        RBus_UInt32  chg26_3:1;
        RBus_UInt32  chg26_4:1;
        RBus_UInt32  chg26_5:1;
        RBus_UInt32  chg26_6:1;
        RBus_UInt32  chg26_7:1;
        RBus_UInt32  res1:24;
    };
}msc_reg_26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chg27_0:1;
        RBus_UInt32  chg27_1:1;
        RBus_UInt32  chg27_2:1;
        RBus_UInt32  chg27_3:1;
        RBus_UInt32  chg27_4:1;
        RBus_UInt32  chg27_5:1;
        RBus_UInt32  chg27_6:1;
        RBus_UInt32  chg27_7:1;
        RBus_UInt32  res1:24;
    };
}msc_reg_27_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dcap_rdy:1;
        RBus_UInt32  conn_rdy:7;
        RBus_UInt32  res1:24;
    };
}msc_reg_30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  clk_mode:3;
        RBus_UInt32  path_en:1;
        RBus_UInt32  muted:1;
        RBus_UInt32  link_mode:3;
        RBus_UInt32  res1:24;
    };
}msc_reg_31_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  stat_32:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_32_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  stat_33:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_33_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  stat_34:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  stat_35:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_35_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  stat_36:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_36_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  stat_37:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_37_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_40:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_40_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_41:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_41_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_42:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_42_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_43:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_43_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_44:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_44_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_45:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_46:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_46_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_47:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_47_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_48:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_48_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_49:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_49_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_4a:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_4a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_4b:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_4b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_4c:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_4c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_4d:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_4d_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_4e:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_4e_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_4f:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_4f_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_50:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_50_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_51:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_51_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_52:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_52_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_53:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_53_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_54:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_54_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_55:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_55_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_56:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_56_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_57:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_57_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_58:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_58_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_59:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_59_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_5a:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_5a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_5b:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_5b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_5c:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_5c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_5d:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_5d_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_5e:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_5e_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scratch_5f:8;
        RBus_UInt32  res1:24;
    };
}msc_reg_5f_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sync0_lb_8_0:9;
        RBus_UInt32  sync0_hb_8_0:9;
        RBus_UInt32  res1:14;
    };
}cbus_link_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sync1_lb_7_0:8;
        RBus_UInt32  sync1_hb_7_0:8;
        RBus_UInt32  res1:16;
    };
}cbus_link_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sync_bit_time:8;
        RBus_UInt32  res1:24;
    };
}cbus_link_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  abs_threshold:8;
        RBus_UInt32  abs_thres_en:1;
        RBus_UInt32  res1:23;
    };
}cbus_link_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  parity_time:8;
        RBus_UInt32  res1:24;
    };
}cbus_link_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  parity_limit:5;
        RBus_UInt32  ctrl_16_resv:1;
        RBus_UInt32  parity_irq_en:1;
        RBus_UInt32  parity_fail:1;
        RBus_UInt32  res1:24;
    };
}cbus_link_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ack_fall:7;
        RBus_UInt32  res1:25;
    };
}cbus_link_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ack_0:7;
        RBus_UInt32  res1:25;
    };
}cbus_link_07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tx_bit_time:8;
        RBus_UInt32  res1:24;
    };
}cbus_link_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ctrl_1b_resv:2;
        RBus_UInt32  fast_reply_en:1;
        RBus_UInt32  chk_win_lo:2;
        RBus_UInt32  chk_win_up:3;
        RBus_UInt32  res1:24;
    };
}cbus_link_09_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tx_ack_fal:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  res1:24;
    };
}cbus_link_0a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tx_ack_low_hb:7;
        RBus_UInt32  res1:25;
    };
}cbus_link_0b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tx_ack_low_lb:7;
        RBus_UInt32  res1:25;
    };
}cbus_link_0c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ctrl_1f_resv:4;
        RBus_UInt32  retry_flag:1;
        RBus_UInt32  retry_lv:3;
        RBus_UInt32  res1:24;
    };
}cbus_link_0d_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  drv_hi_cbus:6;
        RBus_UInt32  drv_str:2;
        RBus_UInt32  res1:24;
    };
}cbus_link_0e_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  req_opp_int:2;
        RBus_UInt32  wait:4;
        RBus_UInt32  res1:26;
    };
}cbus_link_0f_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  req_opp_flt:8;
        RBus_UInt32  res1:24;
    };
}cbus_link_10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  req_cont:8;
        RBus_UInt32  res1:24;
    };
}cbus_link_11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  resp_hold:4;
        RBus_UInt32  req_hold:4;
        RBus_UInt32  res1:24;
    };
}cbus_link_12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  link_err:1;
        RBus_UInt32  link_time:5;
        RBus_UInt32  glob_time:2;
        RBus_UInt32  res1:24;
    };
}cbus_link_13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avoid_conf:1;
        RBus_UInt32  chk_err:1;
        RBus_UInt32  chk_point:6;
        RBus_UInt32  res1:24;
    };
}cbus_link_14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ctrl_28_resv:4;
        RBus_UInt32  msc_wait_arb:1;
        RBus_UInt32  mcumsc_en:1;
        RBus_UInt32  res1:26;
    };
}cbus_msc_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  na_msc_cmd:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  na_msc_offset:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  na_rx_len:5;
        RBus_UInt32  rx_fifo_clr:1;
        RBus_UInt32  rx_fifo_empty:1;
        RBus_UInt32  rx_fifo_full:1;
        RBus_UInt32  res1:24;
    };
}cbus_msc_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rx_fifo_data:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fwdef_cmd_rev:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ddc_abort_irq:1;
        RBus_UInt32  abort_req_irq:1;
        RBus_UInt32  abort_res_irq:1;
        RBus_UInt32  allmsc_cmd_irq:1;
        RBus_UInt32  fwdef_cmd_irq:1;
        RBus_UInt32  sc3_err_irq:1;
        RBus_UInt32  wr_burst_irq:1;
        RBus_UInt32  msc_err_irq:1;
        RBus_UInt32  ddc_err_irq:1;
        RBus_UInt32  sc1_err_irq:1;
        RBus_UInt32  get_msg_irq:1;
        RBus_UInt32  get_id_irq:1;
        RBus_UInt32  get_stat_irq:1;
        RBus_UInt32  rd_devcap_irq:1;
        RBus_UInt32  wr_stat_irq:1;
        RBus_UInt32  msg_sub_irq:1;
        RBus_UInt32  rapk_irq:1;
        RBus_UInt32  rap_irq:1;
        RBus_UInt32  rcpe_irq:1;
        RBus_UInt32  rcpk_irq:1;
        RBus_UInt32  rcp_irq:1;
        RBus_UInt32  msge_irq:1;
        RBus_UInt32  clk_mode_chg:1;
        RBus_UInt32  path_en_chg:1;
        RBus_UInt32  muted_chg:1;
        RBus_UInt32  dcap_rdy_chg:1;
        RBus_UInt32  ucpe_irq:1;
        RBus_UInt32  ucpk_irq:1;
        RBus_UInt32  ucp_irq:1;
        RBus_UInt32  res1:3;
    };
}cbus_msc_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ddc_abort_irq_en:1;
        RBus_UInt32  abort_req_irq_en:1;
        RBus_UInt32  abort_res_irq_en:1;
        RBus_UInt32  allmsc_cmd_irq_en:1;
        RBus_UInt32  fwdef_cmd_irq_en:1;
        RBus_UInt32  sc3_err_irq_en:1;
        RBus_UInt32  wr_burst_irq_en:1;
        RBus_UInt32  msc_err_irq_en:1;
        RBus_UInt32  ddc_err_irq_en:1;
        RBus_UInt32  sc1_err_irq_en:1;
        RBus_UInt32  get_msg_irq_en:1;
        RBus_UInt32  get_id_irq_en:1;
        RBus_UInt32  get_stat_irq_en:1;
        RBus_UInt32  rd_devcap_irq_en:1;
        RBus_UInt32  wr_stat_irq_en:1;
        RBus_UInt32  msg_sub_irq_en:1;
        RBus_UInt32  rapk_irq_en:1;
        RBus_UInt32  rap_irq_en:1;
        RBus_UInt32  rcpe_irq_en:1;
        RBus_UInt32  rcpk_irq_en:1;
        RBus_UInt32  rcp_irq_en:1;
        RBus_UInt32  msge_irq_en:1;
        RBus_UInt32  clk_mode_irq_en:1;
        RBus_UInt32  path_en_irq_en:1;
        RBus_UInt32  muted_chg_irq_en:1;
        RBus_UInt32  dcap_rdy_irq_en:1;
        RBus_UInt32  ucpe_irq_en:1;
        RBus_UInt32  ucpk_irq_en:1;
        RBus_UInt32  ucp_irq_en:1;
        RBus_UInt32  res1:3;
    };
}cbus_msc_07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chg23_irq_en:8;
        RBus_UInt32  chg22_irq_en:8;
        RBus_UInt32  dchg_bit0_irq_en:1;
        RBus_UInt32  edid_irq_en:1;
        RBus_UInt32  dchg_bit2_irq_en:1;
        RBus_UInt32  dchg_bit3_irq_en:1;
        RBus_UInt32  dchg_bit4_irq_en:1;
        RBus_UInt32  dchg_bit5_irq_en:1;
        RBus_UInt32  dchg_bit6_irq_en:1;
        RBus_UInt32  dchg_bit7_irq_en:1;
        RBus_UInt32  dcap_irq_en:1;
        RBus_UInt32  dscr_irq_en:1;
        RBus_UInt32  req_irq_en:1;
        RBus_UInt32  grt_irq_en:1;
        RBus_UInt32  cbus_3d_req_irq_en:1;
        RBus_UInt32  rchg_irq_en:3;
    };
}cbus_msc_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chg27_irq_en:8;
        RBus_UInt32  chg26_irq_en:8;
        RBus_UInt32  chg25_irq_en:8;
        RBus_UInt32  chg24_irq_en:8;
    };
}cbus_msc_09_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  msc_err_code:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_0a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vendor_id:8;
        RBus_UInt32  rcp_reply_nack:1;
        RBus_UInt32  rcp_reply_abort:1;
        RBus_UInt32  res1:22;
    };
}cbus_msc_0b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  msg_cmd:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_0c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  msg_dat:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_0d_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  msge_rcv:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_0e_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rcp_rcv:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_0f_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rcpk_rcv:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rcpe_rcv:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rap_rcv:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rapk_rcv:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  burst_wait:4;
        RBus_UInt32  wb_id_chk:1;
        RBus_UInt32  burst_timeout:1;
        RBus_UInt32  res1:26;
    };
}cbus_msc_14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adop_idl_rcv:8;
        RBus_UInt32  adop_idh_rcv:8;
        RBus_UInt32  res1:16;
    };
}cbus_msc_15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adop_txid_l:8;
        RBus_UInt32  adop_txid_h:8;
        RBus_UInt32  wb_byte_num1:6;
        RBus_UInt32  wb_byte_num0:6;
        RBus_UInt32  insert_id:1;
        RBus_UInt32  auto_handshake:1;
        RBus_UInt32  res1:2;
    };
}cbus_msc_16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  spi_fsm_clr:1;
        RBus_UInt32  sch_fsm_clr:1;
        RBus_UInt32  que_fsm_clr:1;
        RBus_UInt32  res1:29;
    };
}cbus_msc_17_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  spi_fsm:4;
        RBus_UInt32  sch_fsm:4;
        RBus_UInt32  que_fsm:4;
        RBus_UInt32  res1:20;
    };
}cbus_msc_18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cap_offset:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_19_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  int_offset:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_1a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sta_offset:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_1b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scr_offset:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_1c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  msc_err_force:1;
        RBus_UInt32  ddc_err_force:1;
        RBus_UInt32  res1:30;
    };
}cbus_msc_1d_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ddc_err_fw:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_1e_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  msc_err_fw:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_1f_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ucp_rcv:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ucpk_rcv:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_21_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ucpe_rcv:8;
        RBus_UInt32  res1:24;
    };
}cbus_msc_22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw0_head:2;
        RBus_UInt32  fw0_tx_case:3;
        RBus_UInt32  fw0_fifo_empty:1;
        RBus_UInt32  fw0_fifo_full:1;
        RBus_UInt32  fw0_fifo_clr:1;
        RBus_UInt32  fw0_req:1;
        RBus_UInt32  res1:23;
    };
}fw0_req_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw0_cmd1:8;
        RBus_UInt32  res1:24;
    };
}fw0_req_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw0_cmd2:8;
        RBus_UInt32  res1:24;
    };
}fw0_req_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw0_offset:8;
        RBus_UInt32  res1:24;
    };
}fw0_req_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw0_data:8;
        RBus_UInt32  res1:24;
    };
}fw0_req_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw0_wait_case:2;
        RBus_UInt32  fw0_data_irq_en:1;
        RBus_UInt32  fw0_cmd_irq_en:1;
        RBus_UInt32  fw0_fin_irq_en:1;
        RBus_UInt32  fw0_rcv_err:1;
        RBus_UInt32  fw0_data_event:1;
        RBus_UInt32  fw0_cmd_event:1;
        RBus_UInt32  fw0_fin:1;
        RBus_UInt32  fw0_rty_ovr:1;
        RBus_UInt32  res1:22;
    };
}fw0_req_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw0_cmd_rcv:8;
        RBus_UInt32  res1:24;
    };
}fw0_req_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw0_data_rcv:8;
        RBus_UInt32  res1:24;
    };
}fw0_req_07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw0_rdata:8;
        RBus_UInt32  fw0_fifo_len:5;
        RBus_UInt32  fw0_rd_en:1;
        RBus_UInt32  res1:18;
    };
}fw0_req_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw1_head:2;
        RBus_UInt32  fw1_tx_case:3;
        RBus_UInt32  fw1_fifo_empty:1;
        RBus_UInt32  fw1_fifo_full:1;
        RBus_UInt32  fw1_fifo_clr:1;
        RBus_UInt32  fw1_req:1;
        RBus_UInt32  res1:23;
    };
}fw1_req_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw1_cmd1:8;
        RBus_UInt32  res1:24;
    };
}fw1_req_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw1_cmd2:8;
        RBus_UInt32  res1:24;
    };
}fw1_req_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw1_offset:8;
        RBus_UInt32  res1:24;
    };
}fw1_req_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw1_data:8;
        RBus_UInt32  res1:24;
    };
}fw1_req_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw1_wait_case:2;
        RBus_UInt32  fw1_data_irq_en:1;
        RBus_UInt32  fw1_cmd_irq_en:1;
        RBus_UInt32  fw1_fin_irq_en:1;
        RBus_UInt32  fw1_rcv_err:1;
        RBus_UInt32  fw1_data_event:1;
        RBus_UInt32  fw1_cmd_event:1;
        RBus_UInt32  fw1_fin:1;
        RBus_UInt32  fw1_rty_ovr:1;
        RBus_UInt32  res1:22;
    };
}fw1_req_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw1_cmd_rcv:8;
        RBus_UInt32  res1:24;
    };
}fw1_req_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw1_data_rcv:8;
        RBus_UInt32  res1:24;
    };
}fw1_req_07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw1_rdata:8;
        RBus_UInt32  fw1_fifo_len:5;
        RBus_UInt32  fw1_rd_en:1;
        RBus_UInt32  res1:18;
    };
}fw1_req_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw2_head:2;
        RBus_UInt32  fw2_tx_case:3;
        RBus_UInt32  fw2_fifo_empty:1;
        RBus_UInt32  fw2_fifo_full:1;
        RBus_UInt32  fw2_fifo_clr:1;
        RBus_UInt32  fw2_req:1;
        RBus_UInt32  res1:23;
    };
}fw2_req_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw2_cmd1:8;
        RBus_UInt32  res1:24;
    };
}fw2_req_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw2_cmd2:8;
        RBus_UInt32  res1:24;
    };
}fw2_req_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw2_offset:8;
        RBus_UInt32  res1:24;
    };
}fw2_req_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw2_data:8;
        RBus_UInt32  res1:24;
    };
}fw2_req_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw2_wait_case:2;
        RBus_UInt32  fw2_data_irq_en:1;
        RBus_UInt32  fw2_cmd_irq_en:1;
        RBus_UInt32  fw2_fin_irq_en:1;
        RBus_UInt32  fw2_rcv_err:1;
        RBus_UInt32  fw2_data_event:1;
        RBus_UInt32  fw2_cmd_event:1;
        RBus_UInt32  fw2_fin:1;
        RBus_UInt32  fw2_rty_ovr:1;
        RBus_UInt32  res1:22;
    };
}fw2_req_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw2_cmd_rcv:8;
        RBus_UInt32  res1:24;
    };
}fw2_req_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw2_data_rcv:8;
        RBus_UInt32  res1:24;
    };
}fw2_req_07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw2_rdata:8;
        RBus_UInt32  fw2_fifo_len:5;
        RBus_UInt32  fw2_rd_en:1;
        RBus_UInt32  res1:18;
    };
}fw2_req_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ddc_err_code:8;
        RBus_UInt32  res1:24;
    };
}cbus_ddc_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  iic_ck_tgt:8;
        RBus_UInt32  res1:24;
    };
}cbus_ddc_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ddc_req:1;
        RBus_UInt32  ddc_req_ctrl:1;
        RBus_UInt32  ddc_data_irq_en:1;
        RBus_UInt32  ddc_cmd_irq_en:1;
        RBus_UInt32  ddc_data_event:1;
        RBus_UInt32  ddc_cmd_event:1;
        RBus_UInt32  ddc_prior_dis:1;
        RBus_UInt32  mcuddc_en:1;
        RBus_UInt32  res1:24;
    };
}cbus_ddc_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ddc_rcv_cmd:8;
        RBus_UInt32  res1:24;
    };
}cbus_ddc_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ddc_rcv_data:8;
        RBus_UInt32  res1:24;
    };
}cbus_ddc_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ddc_data_fw:8;
        RBus_UInt32  res1:24;
    };
}cbus_ddc_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ddcrd_new_md:1;
        RBus_UInt32  ddcrd_rst_en:1;
        RBus_UInt32  ddc_eof_irq_en:1;
        RBus_UInt32  ddc_eof_irq:1;
        RBus_UInt32  res1:28;
    };
}cbus_ddc_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  path_en_off_awd:1;
        RBus_UInt32  path_en_off_vwd:1;
        RBus_UInt32  mute_en_awd:1;
        RBus_UInt32  mute_en_vwd:1;
        RBus_UInt32  clk_mod_awd:1;
        RBus_UInt32  clk_mod_vwd:1;
        RBus_UInt32  res1:26;
    };
}cbus_wdog_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ctrl_01_resv:1;
        RBus_UInt32  msc_stat_irq:1;
        RBus_UInt32  msc_int_irq:1;
        RBus_UInt32  msc_ch_irq:1;
        RBus_UInt32  ddc_irq:1;
        RBus_UInt32  arbiter_irq:1;
        RBus_UInt32  res1:26;
    };
}cbus_int_index_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:2;
        RBus_UInt32  dbg_sel:3;
        RBus_UInt32  fw_out:1;
        RBus_UInt32  cbus_test_md:2;
        RBus_UInt32  res1:24;
    };
}cbus_test_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cbus_dummy0:32;
    };
}cbus_dummy0_RBUS;


#endif







#endif //_RBUS_CBUS_REG_H_

