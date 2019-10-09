/**************************************************************
// Spec Version                  : 1.4
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2012/3/15 11:19:38
***************************************************************/


#ifndef _OTP_REG_H_INCLUDED_
#define _OTP_REG_H_INCLUDED_
#ifdef  _OTP_USE_STRUCT
typedef struct 
{
unsigned int     datao:32;
}OTP_DATA;

typedef struct 
{
unsigned int     write_en2:1;
unsigned int     rvd3:6;
unsigned int     auto_rd_otp_all:1;
unsigned int     write_en1:1;
unsigned int     rvd2:2;
unsigned int     max_prog_num:5;
unsigned int     rvd1:2;
unsigned int     prog:1;
unsigned int     a:13;
}OTP_CTRL;

typedef struct 
{
unsigned int     write_en3:1;
unsigned int     rvd2:17;
unsigned int     write_en2:1;
unsigned int     crc_en:1;
unsigned int     rvd1:3;
unsigned int     write_en1:1;
unsigned int     en_prog_func:8;
}OTP_CTRL1;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     backdoor_allkeys_1:1;
unsigned int     backdoor_f:1;
unsigned int     reserved_1:2;
unsigned int     ate_prog_otp_a_ov:1;
unsigned int     reg_prog_otp_a_ov:1;
unsigned int     otp_fail:1;
unsigned int     otp_done:1;
unsigned int     rd_hw_info_done:1;
unsigned int     rd_boot_info_done:1;
}OTP_STATUS;

typedef struct 
{
unsigned int     crc_ini:16;
unsigned int     crc_out:16;
}OTP_CRC;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     trs:7;
unsigned int     reserved_1:1;
unsigned int     tcsrst:7;
unsigned int     op_hold:16;
}OTP_RW1;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     twcad:10;
}OTP_RW2;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     treaden:4;
}OTP_RD;

typedef struct 
{
unsigned int     tcph:8;
unsigned int     tpw:8;
unsigned int     tcps:8;
unsigned int     tpes:8;
}OTP_PROG1;

typedef struct 
{
unsigned int     tpvsa:4;
unsigned int     tpvhr:4;
unsigned int     trwh:4;
unsigned int     tpgsv:4;
unsigned int     tpvsr:8;
unsigned int     tpeh:8;
}OTP_PROG2;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     tbcacc:4;
unsigned int     tcpes:4;
unsigned int     reserved_1:2;
unsigned int     tcprd:6;
}OTP_BC;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tacct:4;
unsigned int     trdes:4;
}OTP_TD;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     enable:1;
unsigned int     sel1:4;
unsigned int     sel0:4;
}OTP_DBG;

#endif

#define OTP_DATA_0                                                                   0x18017000
#define OTP_DATA_1                                                                   0x18017004
#define OTP_DATA_2                                                                   0x18017008
#define OTP_DATA_3                                                                   0x1801700C
#define OTP_DATA_4                                                                   0x18017010
#define OTP_DATA_5                                                                   0x18017014
#define OTP_DATA_6                                                                   0x18017018
#define OTP_DATA_7                                                                   0x1801701C
#define OTP_DATA_8                                                                   0x18017020
#define OTP_DATA_9                                                                   0x18017024
#define OTP_DATA_10                                                                   0x18017028
#define OTP_DATA_11                                                                   0x1801702C
#define OTP_DATA_12                                                                   0x18017030
#define OTP_DATA_13                                                                   0x18017034
#define OTP_DATA_14                                                                   0x18017038
#define OTP_DATA_15                                                                   0x1801703C
#define OTP_DATA_16                                                                   0x18017040
#define OTP_DATA_17                                                                   0x18017044
#define OTP_DATA_18                                                                   0x18017048
#define OTP_DATA_19                                                                   0x1801704C
#define OTP_DATA_20                                                                   0x18017050
#define OTP_DATA_21                                                                   0x18017054
#define OTP_DATA_22                                                                   0x18017058
#define OTP_DATA_23                                                                   0x1801705C
#define OTP_DATA_24                                                                   0x18017060
#define OTP_DATA_25                                                                   0x18017064
#define OTP_DATA_26                                                                   0x18017068
#define OTP_DATA_27                                                                   0x1801706C
#define OTP_DATA_28                                                                   0x18017070
#define OTP_DATA_29                                                                   0x18017074
#define OTP_DATA_30                                                                   0x18017078
#define OTP_DATA_31                                                                   0x1801707C
#define OTP_DATA_32                                                                   0x18017080
#define OTP_DATA_33                                                                   0x18017084
#define OTP_DATA_34                                                                   0x18017088
#define OTP_DATA_35                                                                   0x1801708C
#define OTP_DATA_36                                                                   0x18017090
#define OTP_DATA_37                                                                   0x18017094
#define OTP_DATA_38                                                                   0x18017098
#define OTP_DATA_39                                                                   0x1801709C
#define OTP_DATA_40                                                                   0x180170A0
#define OTP_DATA_41                                                                   0x180170A4
#define OTP_DATA_42                                                                   0x180170A8
#define OTP_DATA_43                                                                   0x180170AC
#define OTP_DATA_44                                                                   0x180170B0
#define OTP_DATA_45                                                                   0x180170B4
#define OTP_DATA_46                                                                   0x180170B8
#define OTP_DATA_47                                                                   0x180170BC
#define OTP_DATA_48                                                                   0x180170C0
#define OTP_DATA_49                                                                   0x180170C4
#define OTP_DATA_50                                                                   0x180170C8
#define OTP_DATA_51                                                                   0x180170CC
#define OTP_DATA_52                                                                   0x180170D0
#define OTP_DATA_53                                                                   0x180170D4
#define OTP_DATA_54                                                                   0x180170D8
#define OTP_DATA_55                                                                   0x180170DC
#define OTP_DATA_56                                                                   0x180170E0
#define OTP_DATA_57                                                                   0x180170E4
#define OTP_DATA_58                                                                   0x180170E8
#define OTP_DATA_59                                                                   0x180170EC
#define OTP_DATA_60                                                                   0x180170F0
#define OTP_DATA_61                                                                   0x180170F4
#define OTP_DATA_62                                                                   0x180170F8
#define OTP_DATA_63                                                                   0x180170FC
#define OTP_DATA_64                                                                   0x18017100
#define OTP_DATA_65                                                                   0x18017104
#define OTP_DATA_66                                                                   0x18017108
#define OTP_DATA_67                                                                   0x1801710C
#define OTP_DATA_68                                                                   0x18017110
#define OTP_DATA_69                                                                   0x18017114
#define OTP_DATA_70                                                                   0x18017118
#define OTP_DATA_71                                                                   0x1801711C
#define OTP_DATA_72                                                                   0x18017120
#define OTP_DATA_73                                                                   0x18017124
#define OTP_DATA_74                                                                   0x18017128
#define OTP_DATA_75                                                                   0x1801712C
#define OTP_DATA_76                                                                   0x18017130
#define OTP_DATA_77                                                                   0x18017134
#define OTP_DATA_78                                                                   0x18017138
#define OTP_DATA_79                                                                   0x1801713C
#define OTP_DATA_80                                                                   0x18017140
#define OTP_DATA_81                                                                   0x18017144
#define OTP_DATA_82                                                                   0x18017148
#define OTP_DATA_83                                                                   0x1801714C
#define OTP_DATA_84                                                                   0x18017150
#define OTP_DATA_85                                                                   0x18017154
#define OTP_DATA_86                                                                   0x18017158
#define OTP_DATA_87                                                                   0x1801715C
#define OTP_DATA_88                                                                   0x18017160
#define OTP_DATA_89                                                                   0x18017164
#define OTP_DATA_90                                                                   0x18017168
#define OTP_DATA_91                                                                   0x1801716C
#define OTP_DATA_92                                                                   0x18017170
#define OTP_DATA_93                                                                   0x18017174
#define OTP_DATA_94                                                                   0x18017178
#define OTP_DATA_95                                                                   0x1801717C
#define OTP_DATA_96                                                                   0x18017180
#define OTP_DATA_97                                                                   0x18017184
#define OTP_DATA_98                                                                   0x18017188
#define OTP_DATA_99                                                                   0x1801718C
#define OTP_DATA_100                                                                   0x18017190
#define OTP_DATA_101                                                                   0x18017194
#define OTP_DATA_102                                                                   0x18017198
#define OTP_DATA_103                                                                   0x1801719C
#define OTP_DATA_104                                                                   0x180171A0
#define OTP_DATA_105                                                                   0x180171A4
#define OTP_DATA_106                                                                   0x180171A8
#define OTP_DATA_107                                                                   0x180171AC
#define OTP_DATA_108                                                                   0x180171B0
#define OTP_DATA_109                                                                   0x180171B4
#define OTP_DATA_110                                                                   0x180171B8
#define OTP_DATA_111                                                                   0x180171BC
#define OTP_DATA_112                                                                   0x180171C0
#define OTP_DATA_113                                                                   0x180171C4
#define OTP_DATA_114                                                                   0x180171C8
#define OTP_DATA_115                                                                   0x180171CC
#define OTP_DATA_116                                                                   0x180171D0
#define OTP_DATA_117                                                                   0x180171D4
#define OTP_DATA_118                                                                   0x180171D8
#define OTP_DATA_119                                                                   0x180171DC
#define OTP_DATA_120                                                                   0x180171E0
#define OTP_DATA_121                                                                   0x180171E4
#define OTP_DATA_122                                                                   0x180171E8
#define OTP_DATA_123                                                                   0x180171EC
#define OTP_DATA_124                                                                   0x180171F0
#define OTP_DATA_125                                                                   0x180171F4
#define OTP_DATA_126                                                                   0x180171F8
#define OTP_DATA_127                                                                   0x180171FC
#define OTP_DATA_0_reg_addr                                                          "0xB8017000"
#define OTP_DATA_1_reg_addr                                                          "0xB8017004"
#define OTP_DATA_2_reg_addr                                                          "0xB8017008"
#define OTP_DATA_3_reg_addr                                                          "0xB801700C"
#define OTP_DATA_4_reg_addr                                                          "0xB8017010"
#define OTP_DATA_5_reg_addr                                                          "0xB8017014"
#define OTP_DATA_6_reg_addr                                                          "0xB8017018"
#define OTP_DATA_7_reg_addr                                                          "0xB801701C"
#define OTP_DATA_8_reg_addr                                                          "0xB8017020"
#define OTP_DATA_9_reg_addr                                                          "0xB8017024"
#define OTP_DATA_10_reg_addr                                                          "0xB8017028"
#define OTP_DATA_11_reg_addr                                                          "0xB801702C"
#define OTP_DATA_12_reg_addr                                                          "0xB8017030"
#define OTP_DATA_13_reg_addr                                                          "0xB8017034"
#define OTP_DATA_14_reg_addr                                                          "0xB8017038"
#define OTP_DATA_15_reg_addr                                                          "0xB801703C"
#define OTP_DATA_16_reg_addr                                                          "0xB8017040"
#define OTP_DATA_17_reg_addr                                                          "0xB8017044"
#define OTP_DATA_18_reg_addr                                                          "0xB8017048"
#define OTP_DATA_19_reg_addr                                                          "0xB801704C"
#define OTP_DATA_20_reg_addr                                                          "0xB8017050"
#define OTP_DATA_21_reg_addr                                                          "0xB8017054"
#define OTP_DATA_22_reg_addr                                                          "0xB8017058"
#define OTP_DATA_23_reg_addr                                                          "0xB801705C"
#define OTP_DATA_24_reg_addr                                                          "0xB8017060"
#define OTP_DATA_25_reg_addr                                                          "0xB8017064"
#define OTP_DATA_26_reg_addr                                                          "0xB8017068"
#define OTP_DATA_27_reg_addr                                                          "0xB801706C"
#define OTP_DATA_28_reg_addr                                                          "0xB8017070"
#define OTP_DATA_29_reg_addr                                                          "0xB8017074"
#define OTP_DATA_30_reg_addr                                                          "0xB8017078"
#define OTP_DATA_31_reg_addr                                                          "0xB801707C"
#define OTP_DATA_32_reg_addr                                                          "0xB8017080"
#define OTP_DATA_33_reg_addr                                                          "0xB8017084"
#define OTP_DATA_34_reg_addr                                                          "0xB8017088"
#define OTP_DATA_35_reg_addr                                                          "0xB801708C"
#define OTP_DATA_36_reg_addr                                                          "0xB8017090"
#define OTP_DATA_37_reg_addr                                                          "0xB8017094"
#define OTP_DATA_38_reg_addr                                                          "0xB8017098"
#define OTP_DATA_39_reg_addr                                                          "0xB801709C"
#define OTP_DATA_40_reg_addr                                                          "0xB80170A0"
#define OTP_DATA_41_reg_addr                                                          "0xB80170A4"
#define OTP_DATA_42_reg_addr                                                          "0xB80170A8"
#define OTP_DATA_43_reg_addr                                                          "0xB80170AC"
#define OTP_DATA_44_reg_addr                                                          "0xB80170B0"
#define OTP_DATA_45_reg_addr                                                          "0xB80170B4"
#define OTP_DATA_46_reg_addr                                                          "0xB80170B8"
#define OTP_DATA_47_reg_addr                                                          "0xB80170BC"
#define OTP_DATA_48_reg_addr                                                          "0xB80170C0"
#define OTP_DATA_49_reg_addr                                                          "0xB80170C4"
#define OTP_DATA_50_reg_addr                                                          "0xB80170C8"
#define OTP_DATA_51_reg_addr                                                          "0xB80170CC"
#define OTP_DATA_52_reg_addr                                                          "0xB80170D0"
#define OTP_DATA_53_reg_addr                                                          "0xB80170D4"
#define OTP_DATA_54_reg_addr                                                          "0xB80170D8"
#define OTP_DATA_55_reg_addr                                                          "0xB80170DC"
#define OTP_DATA_56_reg_addr                                                          "0xB80170E0"
#define OTP_DATA_57_reg_addr                                                          "0xB80170E4"
#define OTP_DATA_58_reg_addr                                                          "0xB80170E8"
#define OTP_DATA_59_reg_addr                                                          "0xB80170EC"
#define OTP_DATA_60_reg_addr                                                          "0xB80170F0"
#define OTP_DATA_61_reg_addr                                                          "0xB80170F4"
#define OTP_DATA_62_reg_addr                                                          "0xB80170F8"
#define OTP_DATA_63_reg_addr                                                          "0xB80170FC"
#define OTP_DATA_64_reg_addr                                                          "0xB8017100"
#define OTP_DATA_65_reg_addr                                                          "0xB8017104"
#define OTP_DATA_66_reg_addr                                                          "0xB8017108"
#define OTP_DATA_67_reg_addr                                                          "0xB801710C"
#define OTP_DATA_68_reg_addr                                                          "0xB8017110"
#define OTP_DATA_69_reg_addr                                                          "0xB8017114"
#define OTP_DATA_70_reg_addr                                                          "0xB8017118"
#define OTP_DATA_71_reg_addr                                                          "0xB801711C"
#define OTP_DATA_72_reg_addr                                                          "0xB8017120"
#define OTP_DATA_73_reg_addr                                                          "0xB8017124"
#define OTP_DATA_74_reg_addr                                                          "0xB8017128"
#define OTP_DATA_75_reg_addr                                                          "0xB801712C"
#define OTP_DATA_76_reg_addr                                                          "0xB8017130"
#define OTP_DATA_77_reg_addr                                                          "0xB8017134"
#define OTP_DATA_78_reg_addr                                                          "0xB8017138"
#define OTP_DATA_79_reg_addr                                                          "0xB801713C"
#define OTP_DATA_80_reg_addr                                                          "0xB8017140"
#define OTP_DATA_81_reg_addr                                                          "0xB8017144"
#define OTP_DATA_82_reg_addr                                                          "0xB8017148"
#define OTP_DATA_83_reg_addr                                                          "0xB801714C"
#define OTP_DATA_84_reg_addr                                                          "0xB8017150"
#define OTP_DATA_85_reg_addr                                                          "0xB8017154"
#define OTP_DATA_86_reg_addr                                                          "0xB8017158"
#define OTP_DATA_87_reg_addr                                                          "0xB801715C"
#define OTP_DATA_88_reg_addr                                                          "0xB8017160"
#define OTP_DATA_89_reg_addr                                                          "0xB8017164"
#define OTP_DATA_90_reg_addr                                                          "0xB8017168"
#define OTP_DATA_91_reg_addr                                                          "0xB801716C"
#define OTP_DATA_92_reg_addr                                                          "0xB8017170"
#define OTP_DATA_93_reg_addr                                                          "0xB8017174"
#define OTP_DATA_94_reg_addr                                                          "0xB8017178"
#define OTP_DATA_95_reg_addr                                                          "0xB801717C"
#define OTP_DATA_96_reg_addr                                                          "0xB8017180"
#define OTP_DATA_97_reg_addr                                                          "0xB8017184"
#define OTP_DATA_98_reg_addr                                                          "0xB8017188"
#define OTP_DATA_99_reg_addr                                                          "0xB801718C"
#define OTP_DATA_100_reg_addr                                                          "0xB8017190"
#define OTP_DATA_101_reg_addr                                                          "0xB8017194"
#define OTP_DATA_102_reg_addr                                                          "0xB8017198"
#define OTP_DATA_103_reg_addr                                                          "0xB801719C"
#define OTP_DATA_104_reg_addr                                                          "0xB80171A0"
#define OTP_DATA_105_reg_addr                                                          "0xB80171A4"
#define OTP_DATA_106_reg_addr                                                          "0xB80171A8"
#define OTP_DATA_107_reg_addr                                                          "0xB80171AC"
#define OTP_DATA_108_reg_addr                                                          "0xB80171B0"
#define OTP_DATA_109_reg_addr                                                          "0xB80171B4"
#define OTP_DATA_110_reg_addr                                                          "0xB80171B8"
#define OTP_DATA_111_reg_addr                                                          "0xB80171BC"
#define OTP_DATA_112_reg_addr                                                          "0xB80171C0"
#define OTP_DATA_113_reg_addr                                                          "0xB80171C4"
#define OTP_DATA_114_reg_addr                                                          "0xB80171C8"
#define OTP_DATA_115_reg_addr                                                          "0xB80171CC"
#define OTP_DATA_116_reg_addr                                                          "0xB80171D0"
#define OTP_DATA_117_reg_addr                                                          "0xB80171D4"
#define OTP_DATA_118_reg_addr                                                          "0xB80171D8"
#define OTP_DATA_119_reg_addr                                                          "0xB80171DC"
#define OTP_DATA_120_reg_addr                                                          "0xB80171E0"
#define OTP_DATA_121_reg_addr                                                          "0xB80171E4"
#define OTP_DATA_122_reg_addr                                                          "0xB80171E8"
#define OTP_DATA_123_reg_addr                                                          "0xB80171EC"
#define OTP_DATA_124_reg_addr                                                          "0xB80171F0"
#define OTP_DATA_125_reg_addr                                                          "0xB80171F4"
#define OTP_DATA_126_reg_addr                                                          "0xB80171F8"
#define OTP_DATA_127_reg_addr                                                          "0xB80171FC"
#define OTP_DATA_0_reg                                                               0xB8017000
#define OTP_DATA_1_reg                                                               0xB8017004
#define OTP_DATA_2_reg                                                               0xB8017008
#define OTP_DATA_3_reg                                                               0xB801700C
#define OTP_DATA_4_reg                                                               0xB8017010
#define OTP_DATA_5_reg                                                               0xB8017014
#define OTP_DATA_6_reg                                                               0xB8017018
#define OTP_DATA_7_reg                                                               0xB801701C
#define OTP_DATA_8_reg                                                               0xB8017020
#define OTP_DATA_9_reg                                                               0xB8017024
#define OTP_DATA_10_reg                                                               0xB8017028
#define OTP_DATA_11_reg                                                               0xB801702C
#define OTP_DATA_12_reg                                                               0xB8017030
#define OTP_DATA_13_reg                                                               0xB8017034
#define OTP_DATA_14_reg                                                               0xB8017038
#define OTP_DATA_15_reg                                                               0xB801703C
#define OTP_DATA_16_reg                                                               0xB8017040
#define OTP_DATA_17_reg                                                               0xB8017044
#define OTP_DATA_18_reg                                                               0xB8017048
#define OTP_DATA_19_reg                                                               0xB801704C
#define OTP_DATA_20_reg                                                               0xB8017050
#define OTP_DATA_21_reg                                                               0xB8017054
#define OTP_DATA_22_reg                                                               0xB8017058
#define OTP_DATA_23_reg                                                               0xB801705C
#define OTP_DATA_24_reg                                                               0xB8017060
#define OTP_DATA_25_reg                                                               0xB8017064
#define OTP_DATA_26_reg                                                               0xB8017068
#define OTP_DATA_27_reg                                                               0xB801706C
#define OTP_DATA_28_reg                                                               0xB8017070
#define OTP_DATA_29_reg                                                               0xB8017074
#define OTP_DATA_30_reg                                                               0xB8017078
#define OTP_DATA_31_reg                                                               0xB801707C
#define OTP_DATA_32_reg                                                               0xB8017080
#define OTP_DATA_33_reg                                                               0xB8017084
#define OTP_DATA_34_reg                                                               0xB8017088
#define OTP_DATA_35_reg                                                               0xB801708C
#define OTP_DATA_36_reg                                                               0xB8017090
#define OTP_DATA_37_reg                                                               0xB8017094
#define OTP_DATA_38_reg                                                               0xB8017098
#define OTP_DATA_39_reg                                                               0xB801709C
#define OTP_DATA_40_reg                                                               0xB80170A0
#define OTP_DATA_41_reg                                                               0xB80170A4
#define OTP_DATA_42_reg                                                               0xB80170A8
#define OTP_DATA_43_reg                                                               0xB80170AC
#define OTP_DATA_44_reg                                                               0xB80170B0
#define OTP_DATA_45_reg                                                               0xB80170B4
#define OTP_DATA_46_reg                                                               0xB80170B8
#define OTP_DATA_47_reg                                                               0xB80170BC
#define OTP_DATA_48_reg                                                               0xB80170C0
#define OTP_DATA_49_reg                                                               0xB80170C4
#define OTP_DATA_50_reg                                                               0xB80170C8
#define OTP_DATA_51_reg                                                               0xB80170CC
#define OTP_DATA_52_reg                                                               0xB80170D0
#define OTP_DATA_53_reg                                                               0xB80170D4
#define OTP_DATA_54_reg                                                               0xB80170D8
#define OTP_DATA_55_reg                                                               0xB80170DC
#define OTP_DATA_56_reg                                                               0xB80170E0
#define OTP_DATA_57_reg                                                               0xB80170E4
#define OTP_DATA_58_reg                                                               0xB80170E8
#define OTP_DATA_59_reg                                                               0xB80170EC
#define OTP_DATA_60_reg                                                               0xB80170F0
#define OTP_DATA_61_reg                                                               0xB80170F4
#define OTP_DATA_62_reg                                                               0xB80170F8
#define OTP_DATA_63_reg                                                               0xB80170FC
#define OTP_DATA_64_reg                                                               0xB8017100
#define OTP_DATA_65_reg                                                               0xB8017104
#define OTP_DATA_66_reg                                                               0xB8017108
#define OTP_DATA_67_reg                                                               0xB801710C
#define OTP_DATA_68_reg                                                               0xB8017110
#define OTP_DATA_69_reg                                                               0xB8017114
#define OTP_DATA_70_reg                                                               0xB8017118
#define OTP_DATA_71_reg                                                               0xB801711C
#define OTP_DATA_72_reg                                                               0xB8017120
#define OTP_DATA_73_reg                                                               0xB8017124
#define OTP_DATA_74_reg                                                               0xB8017128
#define OTP_DATA_75_reg                                                               0xB801712C
#define OTP_DATA_76_reg                                                               0xB8017130
#define OTP_DATA_77_reg                                                               0xB8017134
#define OTP_DATA_78_reg                                                               0xB8017138
#define OTP_DATA_79_reg                                                               0xB801713C
#define OTP_DATA_80_reg                                                               0xB8017140
#define OTP_DATA_81_reg                                                               0xB8017144
#define OTP_DATA_82_reg                                                               0xB8017148
#define OTP_DATA_83_reg                                                               0xB801714C
#define OTP_DATA_84_reg                                                               0xB8017150
#define OTP_DATA_85_reg                                                               0xB8017154
#define OTP_DATA_86_reg                                                               0xB8017158
#define OTP_DATA_87_reg                                                               0xB801715C
#define OTP_DATA_88_reg                                                               0xB8017160
#define OTP_DATA_89_reg                                                               0xB8017164
#define OTP_DATA_90_reg                                                               0xB8017168
#define OTP_DATA_91_reg                                                               0xB801716C
#define OTP_DATA_92_reg                                                               0xB8017170
#define OTP_DATA_93_reg                                                               0xB8017174
#define OTP_DATA_94_reg                                                               0xB8017178
#define OTP_DATA_95_reg                                                               0xB801717C
#define OTP_DATA_96_reg                                                               0xB8017180
#define OTP_DATA_97_reg                                                               0xB8017184
#define OTP_DATA_98_reg                                                               0xB8017188
#define OTP_DATA_99_reg                                                               0xB801718C
#define OTP_DATA_100_reg                                                               0xB8017190
#define OTP_DATA_101_reg                                                               0xB8017194
#define OTP_DATA_102_reg                                                               0xB8017198
#define OTP_DATA_103_reg                                                               0xB801719C
#define OTP_DATA_104_reg                                                               0xB80171A0
#define OTP_DATA_105_reg                                                               0xB80171A4
#define OTP_DATA_106_reg                                                               0xB80171A8
#define OTP_DATA_107_reg                                                               0xB80171AC
#define OTP_DATA_108_reg                                                               0xB80171B0
#define OTP_DATA_109_reg                                                               0xB80171B4
#define OTP_DATA_110_reg                                                               0xB80171B8
#define OTP_DATA_111_reg                                                               0xB80171BC
#define OTP_DATA_112_reg                                                               0xB80171C0
#define OTP_DATA_113_reg                                                               0xB80171C4
#define OTP_DATA_114_reg                                                               0xB80171C8
#define OTP_DATA_115_reg                                                               0xB80171CC
#define OTP_DATA_116_reg                                                               0xB80171D0
#define OTP_DATA_117_reg                                                               0xB80171D4
#define OTP_DATA_118_reg                                                               0xB80171D8
#define OTP_DATA_119_reg                                                               0xB80171DC
#define OTP_DATA_120_reg                                                               0xB80171E0
#define OTP_DATA_121_reg                                                               0xB80171E4
#define OTP_DATA_122_reg                                                               0xB80171E8
#define OTP_DATA_123_reg                                                               0xB80171EC
#define OTP_DATA_124_reg                                                               0xB80171F0
#define OTP_DATA_125_reg                                                               0xB80171F4
#define OTP_DATA_126_reg                                                               0xB80171F8
#define OTP_DATA_127_reg                                                               0xB80171FC
#define set_OTP_DATA_0_reg(data)   (*((volatile unsigned int*) OTP_DATA_0_reg)=data)
#define set_OTP_DATA_1_reg(data)   (*((volatile unsigned int*) OTP_DATA_1_reg)=data)
#define set_OTP_DATA_2_reg(data)   (*((volatile unsigned int*) OTP_DATA_2_reg)=data)
#define set_OTP_DATA_3_reg(data)   (*((volatile unsigned int*) OTP_DATA_3_reg)=data)
#define set_OTP_DATA_4_reg(data)   (*((volatile unsigned int*) OTP_DATA_4_reg)=data)
#define set_OTP_DATA_5_reg(data)   (*((volatile unsigned int*) OTP_DATA_5_reg)=data)
#define set_OTP_DATA_6_reg(data)   (*((volatile unsigned int*) OTP_DATA_6_reg)=data)
#define set_OTP_DATA_7_reg(data)   (*((volatile unsigned int*) OTP_DATA_7_reg)=data)
#define set_OTP_DATA_8_reg(data)   (*((volatile unsigned int*) OTP_DATA_8_reg)=data)
#define set_OTP_DATA_9_reg(data)   (*((volatile unsigned int*) OTP_DATA_9_reg)=data)
#define set_OTP_DATA_10_reg(data)   (*((volatile unsigned int*) OTP_DATA_10_reg)=data)
#define set_OTP_DATA_11_reg(data)   (*((volatile unsigned int*) OTP_DATA_11_reg)=data)
#define set_OTP_DATA_12_reg(data)   (*((volatile unsigned int*) OTP_DATA_12_reg)=data)
#define set_OTP_DATA_13_reg(data)   (*((volatile unsigned int*) OTP_DATA_13_reg)=data)
#define set_OTP_DATA_14_reg(data)   (*((volatile unsigned int*) OTP_DATA_14_reg)=data)
#define set_OTP_DATA_15_reg(data)   (*((volatile unsigned int*) OTP_DATA_15_reg)=data)
#define set_OTP_DATA_16_reg(data)   (*((volatile unsigned int*) OTP_DATA_16_reg)=data)
#define set_OTP_DATA_17_reg(data)   (*((volatile unsigned int*) OTP_DATA_17_reg)=data)
#define set_OTP_DATA_18_reg(data)   (*((volatile unsigned int*) OTP_DATA_18_reg)=data)
#define set_OTP_DATA_19_reg(data)   (*((volatile unsigned int*) OTP_DATA_19_reg)=data)
#define set_OTP_DATA_20_reg(data)   (*((volatile unsigned int*) OTP_DATA_20_reg)=data)
#define set_OTP_DATA_21_reg(data)   (*((volatile unsigned int*) OTP_DATA_21_reg)=data)
#define set_OTP_DATA_22_reg(data)   (*((volatile unsigned int*) OTP_DATA_22_reg)=data)
#define set_OTP_DATA_23_reg(data)   (*((volatile unsigned int*) OTP_DATA_23_reg)=data)
#define set_OTP_DATA_24_reg(data)   (*((volatile unsigned int*) OTP_DATA_24_reg)=data)
#define set_OTP_DATA_25_reg(data)   (*((volatile unsigned int*) OTP_DATA_25_reg)=data)
#define set_OTP_DATA_26_reg(data)   (*((volatile unsigned int*) OTP_DATA_26_reg)=data)
#define set_OTP_DATA_27_reg(data)   (*((volatile unsigned int*) OTP_DATA_27_reg)=data)
#define set_OTP_DATA_28_reg(data)   (*((volatile unsigned int*) OTP_DATA_28_reg)=data)
#define set_OTP_DATA_29_reg(data)   (*((volatile unsigned int*) OTP_DATA_29_reg)=data)
#define set_OTP_DATA_30_reg(data)   (*((volatile unsigned int*) OTP_DATA_30_reg)=data)
#define set_OTP_DATA_31_reg(data)   (*((volatile unsigned int*) OTP_DATA_31_reg)=data)
#define set_OTP_DATA_32_reg(data)   (*((volatile unsigned int*) OTP_DATA_32_reg)=data)
#define set_OTP_DATA_33_reg(data)   (*((volatile unsigned int*) OTP_DATA_33_reg)=data)
#define set_OTP_DATA_34_reg(data)   (*((volatile unsigned int*) OTP_DATA_34_reg)=data)
#define set_OTP_DATA_35_reg(data)   (*((volatile unsigned int*) OTP_DATA_35_reg)=data)
#define set_OTP_DATA_36_reg(data)   (*((volatile unsigned int*) OTP_DATA_36_reg)=data)
#define set_OTP_DATA_37_reg(data)   (*((volatile unsigned int*) OTP_DATA_37_reg)=data)
#define set_OTP_DATA_38_reg(data)   (*((volatile unsigned int*) OTP_DATA_38_reg)=data)
#define set_OTP_DATA_39_reg(data)   (*((volatile unsigned int*) OTP_DATA_39_reg)=data)
#define set_OTP_DATA_40_reg(data)   (*((volatile unsigned int*) OTP_DATA_40_reg)=data)
#define set_OTP_DATA_41_reg(data)   (*((volatile unsigned int*) OTP_DATA_41_reg)=data)
#define set_OTP_DATA_42_reg(data)   (*((volatile unsigned int*) OTP_DATA_42_reg)=data)
#define set_OTP_DATA_43_reg(data)   (*((volatile unsigned int*) OTP_DATA_43_reg)=data)
#define set_OTP_DATA_44_reg(data)   (*((volatile unsigned int*) OTP_DATA_44_reg)=data)
#define set_OTP_DATA_45_reg(data)   (*((volatile unsigned int*) OTP_DATA_45_reg)=data)
#define set_OTP_DATA_46_reg(data)   (*((volatile unsigned int*) OTP_DATA_46_reg)=data)
#define set_OTP_DATA_47_reg(data)   (*((volatile unsigned int*) OTP_DATA_47_reg)=data)
#define set_OTP_DATA_48_reg(data)   (*((volatile unsigned int*) OTP_DATA_48_reg)=data)
#define set_OTP_DATA_49_reg(data)   (*((volatile unsigned int*) OTP_DATA_49_reg)=data)
#define set_OTP_DATA_50_reg(data)   (*((volatile unsigned int*) OTP_DATA_50_reg)=data)
#define set_OTP_DATA_51_reg(data)   (*((volatile unsigned int*) OTP_DATA_51_reg)=data)
#define set_OTP_DATA_52_reg(data)   (*((volatile unsigned int*) OTP_DATA_52_reg)=data)
#define set_OTP_DATA_53_reg(data)   (*((volatile unsigned int*) OTP_DATA_53_reg)=data)
#define set_OTP_DATA_54_reg(data)   (*((volatile unsigned int*) OTP_DATA_54_reg)=data)
#define set_OTP_DATA_55_reg(data)   (*((volatile unsigned int*) OTP_DATA_55_reg)=data)
#define set_OTP_DATA_56_reg(data)   (*((volatile unsigned int*) OTP_DATA_56_reg)=data)
#define set_OTP_DATA_57_reg(data)   (*((volatile unsigned int*) OTP_DATA_57_reg)=data)
#define set_OTP_DATA_58_reg(data)   (*((volatile unsigned int*) OTP_DATA_58_reg)=data)
#define set_OTP_DATA_59_reg(data)   (*((volatile unsigned int*) OTP_DATA_59_reg)=data)
#define set_OTP_DATA_60_reg(data)   (*((volatile unsigned int*) OTP_DATA_60_reg)=data)
#define set_OTP_DATA_61_reg(data)   (*((volatile unsigned int*) OTP_DATA_61_reg)=data)
#define set_OTP_DATA_62_reg(data)   (*((volatile unsigned int*) OTP_DATA_62_reg)=data)
#define set_OTP_DATA_63_reg(data)   (*((volatile unsigned int*) OTP_DATA_63_reg)=data)
#define set_OTP_DATA_64_reg(data)   (*((volatile unsigned int*) OTP_DATA_64_reg)=data)
#define set_OTP_DATA_65_reg(data)   (*((volatile unsigned int*) OTP_DATA_65_reg)=data)
#define set_OTP_DATA_66_reg(data)   (*((volatile unsigned int*) OTP_DATA_66_reg)=data)
#define set_OTP_DATA_67_reg(data)   (*((volatile unsigned int*) OTP_DATA_67_reg)=data)
#define set_OTP_DATA_68_reg(data)   (*((volatile unsigned int*) OTP_DATA_68_reg)=data)
#define set_OTP_DATA_69_reg(data)   (*((volatile unsigned int*) OTP_DATA_69_reg)=data)
#define set_OTP_DATA_70_reg(data)   (*((volatile unsigned int*) OTP_DATA_70_reg)=data)
#define set_OTP_DATA_71_reg(data)   (*((volatile unsigned int*) OTP_DATA_71_reg)=data)
#define set_OTP_DATA_72_reg(data)   (*((volatile unsigned int*) OTP_DATA_72_reg)=data)
#define set_OTP_DATA_73_reg(data)   (*((volatile unsigned int*) OTP_DATA_73_reg)=data)
#define set_OTP_DATA_74_reg(data)   (*((volatile unsigned int*) OTP_DATA_74_reg)=data)
#define set_OTP_DATA_75_reg(data)   (*((volatile unsigned int*) OTP_DATA_75_reg)=data)
#define set_OTP_DATA_76_reg(data)   (*((volatile unsigned int*) OTP_DATA_76_reg)=data)
#define set_OTP_DATA_77_reg(data)   (*((volatile unsigned int*) OTP_DATA_77_reg)=data)
#define set_OTP_DATA_78_reg(data)   (*((volatile unsigned int*) OTP_DATA_78_reg)=data)
#define set_OTP_DATA_79_reg(data)   (*((volatile unsigned int*) OTP_DATA_79_reg)=data)
#define set_OTP_DATA_80_reg(data)   (*((volatile unsigned int*) OTP_DATA_80_reg)=data)
#define set_OTP_DATA_81_reg(data)   (*((volatile unsigned int*) OTP_DATA_81_reg)=data)
#define set_OTP_DATA_82_reg(data)   (*((volatile unsigned int*) OTP_DATA_82_reg)=data)
#define set_OTP_DATA_83_reg(data)   (*((volatile unsigned int*) OTP_DATA_83_reg)=data)
#define set_OTP_DATA_84_reg(data)   (*((volatile unsigned int*) OTP_DATA_84_reg)=data)
#define set_OTP_DATA_85_reg(data)   (*((volatile unsigned int*) OTP_DATA_85_reg)=data)
#define set_OTP_DATA_86_reg(data)   (*((volatile unsigned int*) OTP_DATA_86_reg)=data)
#define set_OTP_DATA_87_reg(data)   (*((volatile unsigned int*) OTP_DATA_87_reg)=data)
#define set_OTP_DATA_88_reg(data)   (*((volatile unsigned int*) OTP_DATA_88_reg)=data)
#define set_OTP_DATA_89_reg(data)   (*((volatile unsigned int*) OTP_DATA_89_reg)=data)
#define set_OTP_DATA_90_reg(data)   (*((volatile unsigned int*) OTP_DATA_90_reg)=data)
#define set_OTP_DATA_91_reg(data)   (*((volatile unsigned int*) OTP_DATA_91_reg)=data)
#define set_OTP_DATA_92_reg(data)   (*((volatile unsigned int*) OTP_DATA_92_reg)=data)
#define set_OTP_DATA_93_reg(data)   (*((volatile unsigned int*) OTP_DATA_93_reg)=data)
#define set_OTP_DATA_94_reg(data)   (*((volatile unsigned int*) OTP_DATA_94_reg)=data)
#define set_OTP_DATA_95_reg(data)   (*((volatile unsigned int*) OTP_DATA_95_reg)=data)
#define set_OTP_DATA_96_reg(data)   (*((volatile unsigned int*) OTP_DATA_96_reg)=data)
#define set_OTP_DATA_97_reg(data)   (*((volatile unsigned int*) OTP_DATA_97_reg)=data)
#define set_OTP_DATA_98_reg(data)   (*((volatile unsigned int*) OTP_DATA_98_reg)=data)
#define set_OTP_DATA_99_reg(data)   (*((volatile unsigned int*) OTP_DATA_99_reg)=data)
#define set_OTP_DATA_100_reg(data)   (*((volatile unsigned int*) OTP_DATA_100_reg)=data)
#define set_OTP_DATA_101_reg(data)   (*((volatile unsigned int*) OTP_DATA_101_reg)=data)
#define set_OTP_DATA_102_reg(data)   (*((volatile unsigned int*) OTP_DATA_102_reg)=data)
#define set_OTP_DATA_103_reg(data)   (*((volatile unsigned int*) OTP_DATA_103_reg)=data)
#define set_OTP_DATA_104_reg(data)   (*((volatile unsigned int*) OTP_DATA_104_reg)=data)
#define set_OTP_DATA_105_reg(data)   (*((volatile unsigned int*) OTP_DATA_105_reg)=data)
#define set_OTP_DATA_106_reg(data)   (*((volatile unsigned int*) OTP_DATA_106_reg)=data)
#define set_OTP_DATA_107_reg(data)   (*((volatile unsigned int*) OTP_DATA_107_reg)=data)
#define set_OTP_DATA_108_reg(data)   (*((volatile unsigned int*) OTP_DATA_108_reg)=data)
#define set_OTP_DATA_109_reg(data)   (*((volatile unsigned int*) OTP_DATA_109_reg)=data)
#define set_OTP_DATA_110_reg(data)   (*((volatile unsigned int*) OTP_DATA_110_reg)=data)
#define set_OTP_DATA_111_reg(data)   (*((volatile unsigned int*) OTP_DATA_111_reg)=data)
#define set_OTP_DATA_112_reg(data)   (*((volatile unsigned int*) OTP_DATA_112_reg)=data)
#define set_OTP_DATA_113_reg(data)   (*((volatile unsigned int*) OTP_DATA_113_reg)=data)
#define set_OTP_DATA_114_reg(data)   (*((volatile unsigned int*) OTP_DATA_114_reg)=data)
#define set_OTP_DATA_115_reg(data)   (*((volatile unsigned int*) OTP_DATA_115_reg)=data)
#define set_OTP_DATA_116_reg(data)   (*((volatile unsigned int*) OTP_DATA_116_reg)=data)
#define set_OTP_DATA_117_reg(data)   (*((volatile unsigned int*) OTP_DATA_117_reg)=data)
#define set_OTP_DATA_118_reg(data)   (*((volatile unsigned int*) OTP_DATA_118_reg)=data)
#define set_OTP_DATA_119_reg(data)   (*((volatile unsigned int*) OTP_DATA_119_reg)=data)
#define set_OTP_DATA_120_reg(data)   (*((volatile unsigned int*) OTP_DATA_120_reg)=data)
#define set_OTP_DATA_121_reg(data)   (*((volatile unsigned int*) OTP_DATA_121_reg)=data)
#define set_OTP_DATA_122_reg(data)   (*((volatile unsigned int*) OTP_DATA_122_reg)=data)
#define set_OTP_DATA_123_reg(data)   (*((volatile unsigned int*) OTP_DATA_123_reg)=data)
#define set_OTP_DATA_124_reg(data)   (*((volatile unsigned int*) OTP_DATA_124_reg)=data)
#define set_OTP_DATA_125_reg(data)   (*((volatile unsigned int*) OTP_DATA_125_reg)=data)
#define set_OTP_DATA_126_reg(data)   (*((volatile unsigned int*) OTP_DATA_126_reg)=data)
#define set_OTP_DATA_127_reg(data)   (*((volatile unsigned int*) OTP_DATA_127_reg)=data)
#define get_OTP_DATA_0_reg   (*((volatile unsigned int*) OTP_DATA_0_reg))
#define get_OTP_DATA_1_reg   (*((volatile unsigned int*) OTP_DATA_1_reg))
#define get_OTP_DATA_2_reg   (*((volatile unsigned int*) OTP_DATA_2_reg))
#define get_OTP_DATA_3_reg   (*((volatile unsigned int*) OTP_DATA_3_reg))
#define get_OTP_DATA_4_reg   (*((volatile unsigned int*) OTP_DATA_4_reg))
#define get_OTP_DATA_5_reg   (*((volatile unsigned int*) OTP_DATA_5_reg))
#define get_OTP_DATA_6_reg   (*((volatile unsigned int*) OTP_DATA_6_reg))
#define get_OTP_DATA_7_reg   (*((volatile unsigned int*) OTP_DATA_7_reg))
#define get_OTP_DATA_8_reg   (*((volatile unsigned int*) OTP_DATA_8_reg))
#define get_OTP_DATA_9_reg   (*((volatile unsigned int*) OTP_DATA_9_reg))
#define get_OTP_DATA_10_reg   (*((volatile unsigned int*) OTP_DATA_10_reg))
#define get_OTP_DATA_11_reg   (*((volatile unsigned int*) OTP_DATA_11_reg))
#define get_OTP_DATA_12_reg   (*((volatile unsigned int*) OTP_DATA_12_reg))
#define get_OTP_DATA_13_reg   (*((volatile unsigned int*) OTP_DATA_13_reg))
#define get_OTP_DATA_14_reg   (*((volatile unsigned int*) OTP_DATA_14_reg))
#define get_OTP_DATA_15_reg   (*((volatile unsigned int*) OTP_DATA_15_reg))
#define get_OTP_DATA_16_reg   (*((volatile unsigned int*) OTP_DATA_16_reg))
#define get_OTP_DATA_17_reg   (*((volatile unsigned int*) OTP_DATA_17_reg))
#define get_OTP_DATA_18_reg   (*((volatile unsigned int*) OTP_DATA_18_reg))
#define get_OTP_DATA_19_reg   (*((volatile unsigned int*) OTP_DATA_19_reg))
#define get_OTP_DATA_20_reg   (*((volatile unsigned int*) OTP_DATA_20_reg))
#define get_OTP_DATA_21_reg   (*((volatile unsigned int*) OTP_DATA_21_reg))
#define get_OTP_DATA_22_reg   (*((volatile unsigned int*) OTP_DATA_22_reg))
#define get_OTP_DATA_23_reg   (*((volatile unsigned int*) OTP_DATA_23_reg))
#define get_OTP_DATA_24_reg   (*((volatile unsigned int*) OTP_DATA_24_reg))
#define get_OTP_DATA_25_reg   (*((volatile unsigned int*) OTP_DATA_25_reg))
#define get_OTP_DATA_26_reg   (*((volatile unsigned int*) OTP_DATA_26_reg))
#define get_OTP_DATA_27_reg   (*((volatile unsigned int*) OTP_DATA_27_reg))
#define get_OTP_DATA_28_reg   (*((volatile unsigned int*) OTP_DATA_28_reg))
#define get_OTP_DATA_29_reg   (*((volatile unsigned int*) OTP_DATA_29_reg))
#define get_OTP_DATA_30_reg   (*((volatile unsigned int*) OTP_DATA_30_reg))
#define get_OTP_DATA_31_reg   (*((volatile unsigned int*) OTP_DATA_31_reg))
#define get_OTP_DATA_32_reg   (*((volatile unsigned int*) OTP_DATA_32_reg))
#define get_OTP_DATA_33_reg   (*((volatile unsigned int*) OTP_DATA_33_reg))
#define get_OTP_DATA_34_reg   (*((volatile unsigned int*) OTP_DATA_34_reg))
#define get_OTP_DATA_35_reg   (*((volatile unsigned int*) OTP_DATA_35_reg))
#define get_OTP_DATA_36_reg   (*((volatile unsigned int*) OTP_DATA_36_reg))
#define get_OTP_DATA_37_reg   (*((volatile unsigned int*) OTP_DATA_37_reg))
#define get_OTP_DATA_38_reg   (*((volatile unsigned int*) OTP_DATA_38_reg))
#define get_OTP_DATA_39_reg   (*((volatile unsigned int*) OTP_DATA_39_reg))
#define get_OTP_DATA_40_reg   (*((volatile unsigned int*) OTP_DATA_40_reg))
#define get_OTP_DATA_41_reg   (*((volatile unsigned int*) OTP_DATA_41_reg))
#define get_OTP_DATA_42_reg   (*((volatile unsigned int*) OTP_DATA_42_reg))
#define get_OTP_DATA_43_reg   (*((volatile unsigned int*) OTP_DATA_43_reg))
#define get_OTP_DATA_44_reg   (*((volatile unsigned int*) OTP_DATA_44_reg))
#define get_OTP_DATA_45_reg   (*((volatile unsigned int*) OTP_DATA_45_reg))
#define get_OTP_DATA_46_reg   (*((volatile unsigned int*) OTP_DATA_46_reg))
#define get_OTP_DATA_47_reg   (*((volatile unsigned int*) OTP_DATA_47_reg))
#define get_OTP_DATA_48_reg   (*((volatile unsigned int*) OTP_DATA_48_reg))
#define get_OTP_DATA_49_reg   (*((volatile unsigned int*) OTP_DATA_49_reg))
#define get_OTP_DATA_50_reg   (*((volatile unsigned int*) OTP_DATA_50_reg))
#define get_OTP_DATA_51_reg   (*((volatile unsigned int*) OTP_DATA_51_reg))
#define get_OTP_DATA_52_reg   (*((volatile unsigned int*) OTP_DATA_52_reg))
#define get_OTP_DATA_53_reg   (*((volatile unsigned int*) OTP_DATA_53_reg))
#define get_OTP_DATA_54_reg   (*((volatile unsigned int*) OTP_DATA_54_reg))
#define get_OTP_DATA_55_reg   (*((volatile unsigned int*) OTP_DATA_55_reg))
#define get_OTP_DATA_56_reg   (*((volatile unsigned int*) OTP_DATA_56_reg))
#define get_OTP_DATA_57_reg   (*((volatile unsigned int*) OTP_DATA_57_reg))
#define get_OTP_DATA_58_reg   (*((volatile unsigned int*) OTP_DATA_58_reg))
#define get_OTP_DATA_59_reg   (*((volatile unsigned int*) OTP_DATA_59_reg))
#define get_OTP_DATA_60_reg   (*((volatile unsigned int*) OTP_DATA_60_reg))
#define get_OTP_DATA_61_reg   (*((volatile unsigned int*) OTP_DATA_61_reg))
#define get_OTP_DATA_62_reg   (*((volatile unsigned int*) OTP_DATA_62_reg))
#define get_OTP_DATA_63_reg   (*((volatile unsigned int*) OTP_DATA_63_reg))
#define get_OTP_DATA_64_reg   (*((volatile unsigned int*) OTP_DATA_64_reg))
#define get_OTP_DATA_65_reg   (*((volatile unsigned int*) OTP_DATA_65_reg))
#define get_OTP_DATA_66_reg   (*((volatile unsigned int*) OTP_DATA_66_reg))
#define get_OTP_DATA_67_reg   (*((volatile unsigned int*) OTP_DATA_67_reg))
#define get_OTP_DATA_68_reg   (*((volatile unsigned int*) OTP_DATA_68_reg))
#define get_OTP_DATA_69_reg   (*((volatile unsigned int*) OTP_DATA_69_reg))
#define get_OTP_DATA_70_reg   (*((volatile unsigned int*) OTP_DATA_70_reg))
#define get_OTP_DATA_71_reg   (*((volatile unsigned int*) OTP_DATA_71_reg))
#define get_OTP_DATA_72_reg   (*((volatile unsigned int*) OTP_DATA_72_reg))
#define get_OTP_DATA_73_reg   (*((volatile unsigned int*) OTP_DATA_73_reg))
#define get_OTP_DATA_74_reg   (*((volatile unsigned int*) OTP_DATA_74_reg))
#define get_OTP_DATA_75_reg   (*((volatile unsigned int*) OTP_DATA_75_reg))
#define get_OTP_DATA_76_reg   (*((volatile unsigned int*) OTP_DATA_76_reg))
#define get_OTP_DATA_77_reg   (*((volatile unsigned int*) OTP_DATA_77_reg))
#define get_OTP_DATA_78_reg   (*((volatile unsigned int*) OTP_DATA_78_reg))
#define get_OTP_DATA_79_reg   (*((volatile unsigned int*) OTP_DATA_79_reg))
#define get_OTP_DATA_80_reg   (*((volatile unsigned int*) OTP_DATA_80_reg))
#define get_OTP_DATA_81_reg   (*((volatile unsigned int*) OTP_DATA_81_reg))
#define get_OTP_DATA_82_reg   (*((volatile unsigned int*) OTP_DATA_82_reg))
#define get_OTP_DATA_83_reg   (*((volatile unsigned int*) OTP_DATA_83_reg))
#define get_OTP_DATA_84_reg   (*((volatile unsigned int*) OTP_DATA_84_reg))
#define get_OTP_DATA_85_reg   (*((volatile unsigned int*) OTP_DATA_85_reg))
#define get_OTP_DATA_86_reg   (*((volatile unsigned int*) OTP_DATA_86_reg))
#define get_OTP_DATA_87_reg   (*((volatile unsigned int*) OTP_DATA_87_reg))
#define get_OTP_DATA_88_reg   (*((volatile unsigned int*) OTP_DATA_88_reg))
#define get_OTP_DATA_89_reg   (*((volatile unsigned int*) OTP_DATA_89_reg))
#define get_OTP_DATA_90_reg   (*((volatile unsigned int*) OTP_DATA_90_reg))
#define get_OTP_DATA_91_reg   (*((volatile unsigned int*) OTP_DATA_91_reg))
#define get_OTP_DATA_92_reg   (*((volatile unsigned int*) OTP_DATA_92_reg))
#define get_OTP_DATA_93_reg   (*((volatile unsigned int*) OTP_DATA_93_reg))
#define get_OTP_DATA_94_reg   (*((volatile unsigned int*) OTP_DATA_94_reg))
#define get_OTP_DATA_95_reg   (*((volatile unsigned int*) OTP_DATA_95_reg))
#define get_OTP_DATA_96_reg   (*((volatile unsigned int*) OTP_DATA_96_reg))
#define get_OTP_DATA_97_reg   (*((volatile unsigned int*) OTP_DATA_97_reg))
#define get_OTP_DATA_98_reg   (*((volatile unsigned int*) OTP_DATA_98_reg))
#define get_OTP_DATA_99_reg   (*((volatile unsigned int*) OTP_DATA_99_reg))
#define get_OTP_DATA_100_reg   (*((volatile unsigned int*) OTP_DATA_100_reg))
#define get_OTP_DATA_101_reg   (*((volatile unsigned int*) OTP_DATA_101_reg))
#define get_OTP_DATA_102_reg   (*((volatile unsigned int*) OTP_DATA_102_reg))
#define get_OTP_DATA_103_reg   (*((volatile unsigned int*) OTP_DATA_103_reg))
#define get_OTP_DATA_104_reg   (*((volatile unsigned int*) OTP_DATA_104_reg))
#define get_OTP_DATA_105_reg   (*((volatile unsigned int*) OTP_DATA_105_reg))
#define get_OTP_DATA_106_reg   (*((volatile unsigned int*) OTP_DATA_106_reg))
#define get_OTP_DATA_107_reg   (*((volatile unsigned int*) OTP_DATA_107_reg))
#define get_OTP_DATA_108_reg   (*((volatile unsigned int*) OTP_DATA_108_reg))
#define get_OTP_DATA_109_reg   (*((volatile unsigned int*) OTP_DATA_109_reg))
#define get_OTP_DATA_110_reg   (*((volatile unsigned int*) OTP_DATA_110_reg))
#define get_OTP_DATA_111_reg   (*((volatile unsigned int*) OTP_DATA_111_reg))
#define get_OTP_DATA_112_reg   (*((volatile unsigned int*) OTP_DATA_112_reg))
#define get_OTP_DATA_113_reg   (*((volatile unsigned int*) OTP_DATA_113_reg))
#define get_OTP_DATA_114_reg   (*((volatile unsigned int*) OTP_DATA_114_reg))
#define get_OTP_DATA_115_reg   (*((volatile unsigned int*) OTP_DATA_115_reg))
#define get_OTP_DATA_116_reg   (*((volatile unsigned int*) OTP_DATA_116_reg))
#define get_OTP_DATA_117_reg   (*((volatile unsigned int*) OTP_DATA_117_reg))
#define get_OTP_DATA_118_reg   (*((volatile unsigned int*) OTP_DATA_118_reg))
#define get_OTP_DATA_119_reg   (*((volatile unsigned int*) OTP_DATA_119_reg))
#define get_OTP_DATA_120_reg   (*((volatile unsigned int*) OTP_DATA_120_reg))
#define get_OTP_DATA_121_reg   (*((volatile unsigned int*) OTP_DATA_121_reg))
#define get_OTP_DATA_122_reg   (*((volatile unsigned int*) OTP_DATA_122_reg))
#define get_OTP_DATA_123_reg   (*((volatile unsigned int*) OTP_DATA_123_reg))
#define get_OTP_DATA_124_reg   (*((volatile unsigned int*) OTP_DATA_124_reg))
#define get_OTP_DATA_125_reg   (*((volatile unsigned int*) OTP_DATA_125_reg))
#define get_OTP_DATA_126_reg   (*((volatile unsigned int*) OTP_DATA_126_reg))
#define get_OTP_DATA_127_reg   (*((volatile unsigned int*) OTP_DATA_127_reg))
#define OTP_DATA_0_inst_adr                                                          "0x0000"
#define OTP_DATA_1_inst_adr                                                          "0x0001"
#define OTP_DATA_2_inst_adr                                                          "0x0002"
#define OTP_DATA_3_inst_adr                                                          "0x0003"
#define OTP_DATA_4_inst_adr                                                          "0x0004"
#define OTP_DATA_5_inst_adr                                                          "0x0005"
#define OTP_DATA_6_inst_adr                                                          "0x0006"
#define OTP_DATA_7_inst_adr                                                          "0x0007"
#define OTP_DATA_8_inst_adr                                                          "0x0008"
#define OTP_DATA_9_inst_adr                                                          "0x0009"
#define OTP_DATA_10_inst_adr                                                          "0x000A"
#define OTP_DATA_11_inst_adr                                                          "0x000B"
#define OTP_DATA_12_inst_adr                                                          "0x000C"
#define OTP_DATA_13_inst_adr                                                          "0x000D"
#define OTP_DATA_14_inst_adr                                                          "0x000E"
#define OTP_DATA_15_inst_adr                                                          "0x000F"
#define OTP_DATA_16_inst_adr                                                          "0x0010"
#define OTP_DATA_17_inst_adr                                                          "0x0011"
#define OTP_DATA_18_inst_adr                                                          "0x0012"
#define OTP_DATA_19_inst_adr                                                          "0x0013"
#define OTP_DATA_20_inst_adr                                                          "0x0014"
#define OTP_DATA_21_inst_adr                                                          "0x0015"
#define OTP_DATA_22_inst_adr                                                          "0x0016"
#define OTP_DATA_23_inst_adr                                                          "0x0017"
#define OTP_DATA_24_inst_adr                                                          "0x0018"
#define OTP_DATA_25_inst_adr                                                          "0x0019"
#define OTP_DATA_26_inst_adr                                                          "0x001A"
#define OTP_DATA_27_inst_adr                                                          "0x001B"
#define OTP_DATA_28_inst_adr                                                          "0x001C"
#define OTP_DATA_29_inst_adr                                                          "0x001D"
#define OTP_DATA_30_inst_adr                                                          "0x001E"
#define OTP_DATA_31_inst_adr                                                          "0x001F"
#define OTP_DATA_32_inst_adr                                                          "0x0020"
#define OTP_DATA_33_inst_adr                                                          "0x0021"
#define OTP_DATA_34_inst_adr                                                          "0x0022"
#define OTP_DATA_35_inst_adr                                                          "0x0023"
#define OTP_DATA_36_inst_adr                                                          "0x0024"
#define OTP_DATA_37_inst_adr                                                          "0x0025"
#define OTP_DATA_38_inst_adr                                                          "0x0026"
#define OTP_DATA_39_inst_adr                                                          "0x0027"
#define OTP_DATA_40_inst_adr                                                          "0x0028"
#define OTP_DATA_41_inst_adr                                                          "0x0029"
#define OTP_DATA_42_inst_adr                                                          "0x002A"
#define OTP_DATA_43_inst_adr                                                          "0x002B"
#define OTP_DATA_44_inst_adr                                                          "0x002C"
#define OTP_DATA_45_inst_adr                                                          "0x002D"
#define OTP_DATA_46_inst_adr                                                          "0x002E"
#define OTP_DATA_47_inst_adr                                                          "0x002F"
#define OTP_DATA_48_inst_adr                                                          "0x0030"
#define OTP_DATA_49_inst_adr                                                          "0x0031"
#define OTP_DATA_50_inst_adr                                                          "0x0032"
#define OTP_DATA_51_inst_adr                                                          "0x0033"
#define OTP_DATA_52_inst_adr                                                          "0x0034"
#define OTP_DATA_53_inst_adr                                                          "0x0035"
#define OTP_DATA_54_inst_adr                                                          "0x0036"
#define OTP_DATA_55_inst_adr                                                          "0x0037"
#define OTP_DATA_56_inst_adr                                                          "0x0038"
#define OTP_DATA_57_inst_adr                                                          "0x0039"
#define OTP_DATA_58_inst_adr                                                          "0x003A"
#define OTP_DATA_59_inst_adr                                                          "0x003B"
#define OTP_DATA_60_inst_adr                                                          "0x003C"
#define OTP_DATA_61_inst_adr                                                          "0x003D"
#define OTP_DATA_62_inst_adr                                                          "0x003E"
#define OTP_DATA_63_inst_adr                                                          "0x003F"
#define OTP_DATA_64_inst_adr                                                          "0x0040"
#define OTP_DATA_65_inst_adr                                                          "0x0041"
#define OTP_DATA_66_inst_adr                                                          "0x0042"
#define OTP_DATA_67_inst_adr                                                          "0x0043"
#define OTP_DATA_68_inst_adr                                                          "0x0044"
#define OTP_DATA_69_inst_adr                                                          "0x0045"
#define OTP_DATA_70_inst_adr                                                          "0x0046"
#define OTP_DATA_71_inst_adr                                                          "0x0047"
#define OTP_DATA_72_inst_adr                                                          "0x0048"
#define OTP_DATA_73_inst_adr                                                          "0x0049"
#define OTP_DATA_74_inst_adr                                                          "0x004A"
#define OTP_DATA_75_inst_adr                                                          "0x004B"
#define OTP_DATA_76_inst_adr                                                          "0x004C"
#define OTP_DATA_77_inst_adr                                                          "0x004D"
#define OTP_DATA_78_inst_adr                                                          "0x004E"
#define OTP_DATA_79_inst_adr                                                          "0x004F"
#define OTP_DATA_80_inst_adr                                                          "0x0050"
#define OTP_DATA_81_inst_adr                                                          "0x0051"
#define OTP_DATA_82_inst_adr                                                          "0x0052"
#define OTP_DATA_83_inst_adr                                                          "0x0053"
#define OTP_DATA_84_inst_adr                                                          "0x0054"
#define OTP_DATA_85_inst_adr                                                          "0x0055"
#define OTP_DATA_86_inst_adr                                                          "0x0056"
#define OTP_DATA_87_inst_adr                                                          "0x0057"
#define OTP_DATA_88_inst_adr                                                          "0x0058"
#define OTP_DATA_89_inst_adr                                                          "0x0059"
#define OTP_DATA_90_inst_adr                                                          "0x005A"
#define OTP_DATA_91_inst_adr                                                          "0x005B"
#define OTP_DATA_92_inst_adr                                                          "0x005C"
#define OTP_DATA_93_inst_adr                                                          "0x005D"
#define OTP_DATA_94_inst_adr                                                          "0x005E"
#define OTP_DATA_95_inst_adr                                                          "0x005F"
#define OTP_DATA_96_inst_adr                                                          "0x0060"
#define OTP_DATA_97_inst_adr                                                          "0x0061"
#define OTP_DATA_98_inst_adr                                                          "0x0062"
#define OTP_DATA_99_inst_adr                                                          "0x0063"
#define OTP_DATA_100_inst_adr                                                          "0x0064"
#define OTP_DATA_101_inst_adr                                                          "0x0065"
#define OTP_DATA_102_inst_adr                                                          "0x0066"
#define OTP_DATA_103_inst_adr                                                          "0x0067"
#define OTP_DATA_104_inst_adr                                                          "0x0068"
#define OTP_DATA_105_inst_adr                                                          "0x0069"
#define OTP_DATA_106_inst_adr                                                          "0x006A"
#define OTP_DATA_107_inst_adr                                                          "0x006B"
#define OTP_DATA_108_inst_adr                                                          "0x006C"
#define OTP_DATA_109_inst_adr                                                          "0x006D"
#define OTP_DATA_110_inst_adr                                                          "0x006E"
#define OTP_DATA_111_inst_adr                                                          "0x006F"
#define OTP_DATA_112_inst_adr                                                          "0x0070"
#define OTP_DATA_113_inst_adr                                                          "0x0071"
#define OTP_DATA_114_inst_adr                                                          "0x0072"
#define OTP_DATA_115_inst_adr                                                          "0x0073"
#define OTP_DATA_116_inst_adr                                                          "0x0074"
#define OTP_DATA_117_inst_adr                                                          "0x0075"
#define OTP_DATA_118_inst_adr                                                          "0x0076"
#define OTP_DATA_119_inst_adr                                                          "0x0077"
#define OTP_DATA_120_inst_adr                                                          "0x0078"
#define OTP_DATA_121_inst_adr                                                          "0x0079"
#define OTP_DATA_122_inst_adr                                                          "0x007A"
#define OTP_DATA_123_inst_adr                                                          "0x007B"
#define OTP_DATA_124_inst_adr                                                          "0x007C"
#define OTP_DATA_125_inst_adr                                                          "0x007D"
#define OTP_DATA_126_inst_adr                                                          "0x007E"
#define OTP_DATA_127_inst_adr                                                          "0x007F"
#define OTP_DATA_0_inst                                                              0x0000
#define OTP_DATA_1_inst                                                              0x0001
#define OTP_DATA_2_inst                                                              0x0002
#define OTP_DATA_3_inst                                                              0x0003
#define OTP_DATA_4_inst                                                              0x0004
#define OTP_DATA_5_inst                                                              0x0005
#define OTP_DATA_6_inst                                                              0x0006
#define OTP_DATA_7_inst                                                              0x0007
#define OTP_DATA_8_inst                                                              0x0008
#define OTP_DATA_9_inst                                                              0x0009
#define OTP_DATA_10_inst                                                              0x000A
#define OTP_DATA_11_inst                                                              0x000B
#define OTP_DATA_12_inst                                                              0x000C
#define OTP_DATA_13_inst                                                              0x000D
#define OTP_DATA_14_inst                                                              0x000E
#define OTP_DATA_15_inst                                                              0x000F
#define OTP_DATA_16_inst                                                              0x0010
#define OTP_DATA_17_inst                                                              0x0011
#define OTP_DATA_18_inst                                                              0x0012
#define OTP_DATA_19_inst                                                              0x0013
#define OTP_DATA_20_inst                                                              0x0014
#define OTP_DATA_21_inst                                                              0x0015
#define OTP_DATA_22_inst                                                              0x0016
#define OTP_DATA_23_inst                                                              0x0017
#define OTP_DATA_24_inst                                                              0x0018
#define OTP_DATA_25_inst                                                              0x0019
#define OTP_DATA_26_inst                                                              0x001A
#define OTP_DATA_27_inst                                                              0x001B
#define OTP_DATA_28_inst                                                              0x001C
#define OTP_DATA_29_inst                                                              0x001D
#define OTP_DATA_30_inst                                                              0x001E
#define OTP_DATA_31_inst                                                              0x001F
#define OTP_DATA_32_inst                                                              0x0020
#define OTP_DATA_33_inst                                                              0x0021
#define OTP_DATA_34_inst                                                              0x0022
#define OTP_DATA_35_inst                                                              0x0023
#define OTP_DATA_36_inst                                                              0x0024
#define OTP_DATA_37_inst                                                              0x0025
#define OTP_DATA_38_inst                                                              0x0026
#define OTP_DATA_39_inst                                                              0x0027
#define OTP_DATA_40_inst                                                              0x0028
#define OTP_DATA_41_inst                                                              0x0029
#define OTP_DATA_42_inst                                                              0x002A
#define OTP_DATA_43_inst                                                              0x002B
#define OTP_DATA_44_inst                                                              0x002C
#define OTP_DATA_45_inst                                                              0x002D
#define OTP_DATA_46_inst                                                              0x002E
#define OTP_DATA_47_inst                                                              0x002F
#define OTP_DATA_48_inst                                                              0x0030
#define OTP_DATA_49_inst                                                              0x0031
#define OTP_DATA_50_inst                                                              0x0032
#define OTP_DATA_51_inst                                                              0x0033
#define OTP_DATA_52_inst                                                              0x0034
#define OTP_DATA_53_inst                                                              0x0035
#define OTP_DATA_54_inst                                                              0x0036
#define OTP_DATA_55_inst                                                              0x0037
#define OTP_DATA_56_inst                                                              0x0038
#define OTP_DATA_57_inst                                                              0x0039
#define OTP_DATA_58_inst                                                              0x003A
#define OTP_DATA_59_inst                                                              0x003B
#define OTP_DATA_60_inst                                                              0x003C
#define OTP_DATA_61_inst                                                              0x003D
#define OTP_DATA_62_inst                                                              0x003E
#define OTP_DATA_63_inst                                                              0x003F
#define OTP_DATA_64_inst                                                              0x0040
#define OTP_DATA_65_inst                                                              0x0041
#define OTP_DATA_66_inst                                                              0x0042
#define OTP_DATA_67_inst                                                              0x0043
#define OTP_DATA_68_inst                                                              0x0044
#define OTP_DATA_69_inst                                                              0x0045
#define OTP_DATA_70_inst                                                              0x0046
#define OTP_DATA_71_inst                                                              0x0047
#define OTP_DATA_72_inst                                                              0x0048
#define OTP_DATA_73_inst                                                              0x0049
#define OTP_DATA_74_inst                                                              0x004A
#define OTP_DATA_75_inst                                                              0x004B
#define OTP_DATA_76_inst                                                              0x004C
#define OTP_DATA_77_inst                                                              0x004D
#define OTP_DATA_78_inst                                                              0x004E
#define OTP_DATA_79_inst                                                              0x004F
#define OTP_DATA_80_inst                                                              0x0050
#define OTP_DATA_81_inst                                                              0x0051
#define OTP_DATA_82_inst                                                              0x0052
#define OTP_DATA_83_inst                                                              0x0053
#define OTP_DATA_84_inst                                                              0x0054
#define OTP_DATA_85_inst                                                              0x0055
#define OTP_DATA_86_inst                                                              0x0056
#define OTP_DATA_87_inst                                                              0x0057
#define OTP_DATA_88_inst                                                              0x0058
#define OTP_DATA_89_inst                                                              0x0059
#define OTP_DATA_90_inst                                                              0x005A
#define OTP_DATA_91_inst                                                              0x005B
#define OTP_DATA_92_inst                                                              0x005C
#define OTP_DATA_93_inst                                                              0x005D
#define OTP_DATA_94_inst                                                              0x005E
#define OTP_DATA_95_inst                                                              0x005F
#define OTP_DATA_96_inst                                                              0x0060
#define OTP_DATA_97_inst                                                              0x0061
#define OTP_DATA_98_inst                                                              0x0062
#define OTP_DATA_99_inst                                                              0x0063
#define OTP_DATA_100_inst                                                              0x0064
#define OTP_DATA_101_inst                                                              0x0065
#define OTP_DATA_102_inst                                                              0x0066
#define OTP_DATA_103_inst                                                              0x0067
#define OTP_DATA_104_inst                                                              0x0068
#define OTP_DATA_105_inst                                                              0x0069
#define OTP_DATA_106_inst                                                              0x006A
#define OTP_DATA_107_inst                                                              0x006B
#define OTP_DATA_108_inst                                                              0x006C
#define OTP_DATA_109_inst                                                              0x006D
#define OTP_DATA_110_inst                                                              0x006E
#define OTP_DATA_111_inst                                                              0x006F
#define OTP_DATA_112_inst                                                              0x0070
#define OTP_DATA_113_inst                                                              0x0071
#define OTP_DATA_114_inst                                                              0x0072
#define OTP_DATA_115_inst                                                              0x0073
#define OTP_DATA_116_inst                                                              0x0074
#define OTP_DATA_117_inst                                                              0x0075
#define OTP_DATA_118_inst                                                              0x0076
#define OTP_DATA_119_inst                                                              0x0077
#define OTP_DATA_120_inst                                                              0x0078
#define OTP_DATA_121_inst                                                              0x0079
#define OTP_DATA_122_inst                                                              0x007A
#define OTP_DATA_123_inst                                                              0x007B
#define OTP_DATA_124_inst                                                              0x007C
#define OTP_DATA_125_inst                                                              0x007D
#define OTP_DATA_126_inst                                                              0x007E
#define OTP_DATA_127_inst                                                              0x007F
#define OTP_DATA_datao_shift                                                         (0)
#define OTP_DATA_datao_mask                                                          (0xFFFFFFFF)
#define OTP_DATA_datao(data)                                                         (0xFFFFFFFF&((data)<<0))
#define OTP_DATA_datao_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define OTP_DATA_get_datao(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define OTP_CTRL                                                                     0x18017300
#define OTP_CTRL_reg_addr                                                            "0xB8017300"
#define OTP_CTRL_reg                                                                 0xB8017300
#define set_OTP_CTRL_reg(data)   (*((volatile unsigned int*) OTP_CTRL_reg)=data)
#define get_OTP_CTRL_reg   (*((volatile unsigned int*) OTP_CTRL_reg))
#define OTP_CTRL_inst_adr                                                            "0x00C0"
#define OTP_CTRL_inst                                                                0x00C0
#define OTP_CTRL_write_en2_shift                                                     (31)
#define OTP_CTRL_write_en2_mask                                                      (0x80000000)
#define OTP_CTRL_write_en2(data)                                                     (0x80000000&((data)<<31))
#define OTP_CTRL_write_en2_src(data)                                                 ((0x80000000&(data))>>31)
#define OTP_CTRL_get_write_en2(data)                                                 ((0x80000000&(data))>>31)
#define OTP_CTRL_rvd3_shift                                                          (25)
#define OTP_CTRL_rvd3_mask                                                           (0x7E000000)
#define OTP_CTRL_rvd3(data)                                                          (0x7E000000&((data)<<25))
#define OTP_CTRL_rvd3_src(data)                                                      ((0x7E000000&(data))>>25)
#define OTP_CTRL_get_rvd3(data)                                                      ((0x7E000000&(data))>>25)
#define OTP_CTRL_auto_rd_otp_all_shift                                               (24)
#define OTP_CTRL_auto_rd_otp_all_mask                                                (0x01000000)
#define OTP_CTRL_auto_rd_otp_all(data)                                               (0x01000000&((data)<<24))
#define OTP_CTRL_auto_rd_otp_all_src(data)                                           ((0x01000000&(data))>>24)
#define OTP_CTRL_get_auto_rd_otp_all(data)                                           ((0x01000000&(data))>>24)
#define OTP_CTRL_write_en1_shift                                                     (23)
#define OTP_CTRL_write_en1_mask                                                      (0x00800000)
#define OTP_CTRL_write_en1(data)                                                     (0x00800000&((data)<<23))
#define OTP_CTRL_write_en1_src(data)                                                 ((0x00800000&(data))>>23)
#define OTP_CTRL_get_write_en1(data)                                                 ((0x00800000&(data))>>23)
#define OTP_CTRL_rvd2_shift                                                          (21)
#define OTP_CTRL_rvd2_mask                                                           (0x00600000)
#define OTP_CTRL_rvd2(data)                                                          (0x00600000&((data)<<21))
#define OTP_CTRL_rvd2_src(data)                                                      ((0x00600000&(data))>>21)
#define OTP_CTRL_get_rvd2(data)                                                      ((0x00600000&(data))>>21)
#define OTP_CTRL_max_prog_num_shift                                                  (16)
#define OTP_CTRL_max_prog_num_mask                                                   (0x001F0000)
#define OTP_CTRL_max_prog_num(data)                                                  (0x001F0000&((data)<<16))
#define OTP_CTRL_max_prog_num_src(data)                                              ((0x001F0000&(data))>>16)
#define OTP_CTRL_get_max_prog_num(data)                                              ((0x001F0000&(data))>>16)
#define OTP_CTRL_rvd1_shift                                                          (14)
#define OTP_CTRL_rvd1_mask                                                           (0x0000C000)
#define OTP_CTRL_rvd1(data)                                                          (0x0000C000&((data)<<14))
#define OTP_CTRL_rvd1_src(data)                                                      ((0x0000C000&(data))>>14)
#define OTP_CTRL_get_rvd1(data)                                                      ((0x0000C000&(data))>>14)
#define OTP_CTRL_prog_shift                                                          (13)
#define OTP_CTRL_prog_mask                                                           (0x00002000)
#define OTP_CTRL_prog(data)                                                          (0x00002000&((data)<<13))
#define OTP_CTRL_prog_src(data)                                                      ((0x00002000&(data))>>13)
#define OTP_CTRL_get_prog(data)                                                      ((0x00002000&(data))>>13)
#define OTP_CTRL_a_shift                                                             (0)
#define OTP_CTRL_a_mask                                                              (0x00001FFF)
#define OTP_CTRL_a(data)                                                             (0x00001FFF&((data)<<0))
#define OTP_CTRL_a_src(data)                                                         ((0x00001FFF&(data))>>0)
#define OTP_CTRL_get_a(data)                                                         ((0x00001FFF&(data))>>0)


#define OTP_CTRL1                                                                    0x18017304
#define OTP_CTRL1_reg_addr                                                           "0xB8017304"
#define OTP_CTRL1_reg                                                                0xB8017304
#define set_OTP_CTRL1_reg(data)   (*((volatile unsigned int*) OTP_CTRL1_reg)=data)
#define get_OTP_CTRL1_reg   (*((volatile unsigned int*) OTP_CTRL1_reg))
#define OTP_CTRL1_inst_adr                                                           "0x00C1"
#define OTP_CTRL1_inst                                                               0x00C1
#define OTP_CTRL1_write_en3_shift                                                    (31)
#define OTP_CTRL1_write_en3_mask                                                     (0x80000000)
#define OTP_CTRL1_write_en3(data)                                                    (0x80000000&((data)<<31))
#define OTP_CTRL1_write_en3_src(data)                                                ((0x80000000&(data))>>31)
#define OTP_CTRL1_get_write_en3(data)                                                ((0x80000000&(data))>>31)
#define OTP_CTRL1_rvd2_shift                                                         (14)
#define OTP_CTRL1_rvd2_mask                                                          (0x7FFFC000)
#define OTP_CTRL1_rvd2(data)                                                         (0x7FFFC000&((data)<<14))
#define OTP_CTRL1_rvd2_src(data)                                                     ((0x7FFFC000&(data))>>14)
#define OTP_CTRL1_get_rvd2(data)                                                     ((0x7FFFC000&(data))>>14)
#define OTP_CTRL1_write_en2_shift                                                    (13)
#define OTP_CTRL1_write_en2_mask                                                     (0x00002000)
#define OTP_CTRL1_write_en2(data)                                                    (0x00002000&((data)<<13))
#define OTP_CTRL1_write_en2_src(data)                                                ((0x00002000&(data))>>13)
#define OTP_CTRL1_get_write_en2(data)                                                ((0x00002000&(data))>>13)
#define OTP_CTRL1_crc_en_shift                                                       (12)
#define OTP_CTRL1_crc_en_mask                                                        (0x00001000)
#define OTP_CTRL1_crc_en(data)                                                       (0x00001000&((data)<<12))
#define OTP_CTRL1_crc_en_src(data)                                                   ((0x00001000&(data))>>12)
#define OTP_CTRL1_get_crc_en(data)                                                   ((0x00001000&(data))>>12)
#define OTP_CTRL1_rvd1_shift                                                         (9)
#define OTP_CTRL1_rvd1_mask                                                          (0x00000E00)
#define OTP_CTRL1_rvd1(data)                                                         (0x00000E00&((data)<<9))
#define OTP_CTRL1_rvd1_src(data)                                                     ((0x00000E00&(data))>>9)
#define OTP_CTRL1_get_rvd1(data)                                                     ((0x00000E00&(data))>>9)
#define OTP_CTRL1_write_en1_shift                                                    (8)
#define OTP_CTRL1_write_en1_mask                                                     (0x00000100)
#define OTP_CTRL1_write_en1(data)                                                    (0x00000100&((data)<<8))
#define OTP_CTRL1_write_en1_src(data)                                                ((0x00000100&(data))>>8)
#define OTP_CTRL1_get_write_en1(data)                                                ((0x00000100&(data))>>8)
#define OTP_CTRL1_en_prog_func_shift                                                 (0)
#define OTP_CTRL1_en_prog_func_mask                                                  (0x000000FF)
#define OTP_CTRL1_en_prog_func(data)                                                 (0x000000FF&((data)<<0))
#define OTP_CTRL1_en_prog_func_src(data)                                             ((0x000000FF&(data))>>0)
#define OTP_CTRL1_get_en_prog_func(data)                                             ((0x000000FF&(data))>>0)


#define OTP_STATUS                                                                   0x18017308
#define OTP_STATUS_reg_addr                                                          "0xB8017308"
#define OTP_STATUS_reg                                                               0xB8017308
#define set_OTP_STATUS_reg(data)   (*((volatile unsigned int*) OTP_STATUS_reg)=data)
#define get_OTP_STATUS_reg   (*((volatile unsigned int*) OTP_STATUS_reg))
#define OTP_STATUS_inst_adr                                                          "0x00C2"
#define OTP_STATUS_inst                                                              0x00C2
#define OTP_STATUS_backdoor_allkeys_1_shift                                          (9)
#define OTP_STATUS_backdoor_allkeys_1_mask                                           (0x00000200)
#define OTP_STATUS_backdoor_allkeys_1(data)                                          (0x00000200&((data)<<9))
#define OTP_STATUS_backdoor_allkeys_1_src(data)                                      ((0x00000200&(data))>>9)
#define OTP_STATUS_get_backdoor_allkeys_1(data)                                      ((0x00000200&(data))>>9)
#define OTP_STATUS_backdoor_f_shift                                                  (8)
#define OTP_STATUS_backdoor_f_mask                                                   (0x00000100)
#define OTP_STATUS_backdoor_f(data)                                                  (0x00000100&((data)<<8))
#define OTP_STATUS_backdoor_f_src(data)                                              ((0x00000100&(data))>>8)
#define OTP_STATUS_get_backdoor_f(data)                                              ((0x00000100&(data))>>8)
#define OTP_STATUS_ate_prog_otp_a_ov_shift                                           (5)
#define OTP_STATUS_ate_prog_otp_a_ov_mask                                            (0x00000020)
#define OTP_STATUS_ate_prog_otp_a_ov(data)                                           (0x00000020&((data)<<5))
#define OTP_STATUS_ate_prog_otp_a_ov_src(data)                                       ((0x00000020&(data))>>5)
#define OTP_STATUS_get_ate_prog_otp_a_ov(data)                                       ((0x00000020&(data))>>5)
#define OTP_STATUS_reg_prog_otp_a_ov_shift                                           (4)
#define OTP_STATUS_reg_prog_otp_a_ov_mask                                            (0x00000010)
#define OTP_STATUS_reg_prog_otp_a_ov(data)                                           (0x00000010&((data)<<4))
#define OTP_STATUS_reg_prog_otp_a_ov_src(data)                                       ((0x00000010&(data))>>4)
#define OTP_STATUS_get_reg_prog_otp_a_ov(data)                                       ((0x00000010&(data))>>4)
#define OTP_STATUS_otp_fail_shift                                                    (3)
#define OTP_STATUS_otp_fail_mask                                                     (0x00000008)
#define OTP_STATUS_otp_fail(data)                                                    (0x00000008&((data)<<3))
#define OTP_STATUS_otp_fail_src(data)                                                ((0x00000008&(data))>>3)
#define OTP_STATUS_get_otp_fail(data)                                                ((0x00000008&(data))>>3)
#define OTP_STATUS_otp_done_shift                                                    (2)
#define OTP_STATUS_otp_done_mask                                                     (0x00000004)
#define OTP_STATUS_otp_done(data)                                                    (0x00000004&((data)<<2))
#define OTP_STATUS_otp_done_src(data)                                                ((0x00000004&(data))>>2)
#define OTP_STATUS_get_otp_done(data)                                                ((0x00000004&(data))>>2)
#define OTP_STATUS_rd_hw_info_done_shift                                             (1)
#define OTP_STATUS_rd_hw_info_done_mask                                              (0x00000002)
#define OTP_STATUS_rd_hw_info_done(data)                                             (0x00000002&((data)<<1))
#define OTP_STATUS_rd_hw_info_done_src(data)                                         ((0x00000002&(data))>>1)
#define OTP_STATUS_get_rd_hw_info_done(data)                                         ((0x00000002&(data))>>1)
#define OTP_STATUS_rd_boot_info_done_shift                                           (0)
#define OTP_STATUS_rd_boot_info_done_mask                                            (0x00000001)
#define OTP_STATUS_rd_boot_info_done(data)                                           (0x00000001&((data)<<0))
#define OTP_STATUS_rd_boot_info_done_src(data)                                       ((0x00000001&(data))>>0)
#define OTP_STATUS_get_rd_boot_info_done(data)                                       ((0x00000001&(data))>>0)


#define OTP_CRC                                                                      0x1801730C
#define OTP_CRC_reg_addr                                                             "0xB801730C"
#define OTP_CRC_reg                                                                  0xB801730C
#define set_OTP_CRC_reg(data)   (*((volatile unsigned int*) OTP_CRC_reg)=data)
#define get_OTP_CRC_reg   (*((volatile unsigned int*) OTP_CRC_reg))
#define OTP_CRC_inst_adr                                                             "0x00C3"
#define OTP_CRC_inst                                                                 0x00C3
#define OTP_CRC_crc_ini_shift                                                        (16)
#define OTP_CRC_crc_ini_mask                                                         (0xFFFF0000)
#define OTP_CRC_crc_ini(data)                                                        (0xFFFF0000&((data)<<16))
#define OTP_CRC_crc_ini_src(data)                                                    ((0xFFFF0000&(data))>>16)
#define OTP_CRC_get_crc_ini(data)                                                    ((0xFFFF0000&(data))>>16)
#define OTP_CRC_crc_out_shift                                                        (0)
#define OTP_CRC_crc_out_mask                                                         (0x0000FFFF)
#define OTP_CRC_crc_out(data)                                                        (0x0000FFFF&((data)<<0))
#define OTP_CRC_crc_out_src(data)                                                    ((0x0000FFFF&(data))>>0)
#define OTP_CRC_get_crc_out(data)                                                    ((0x0000FFFF&(data))>>0)


#define OTP_RW1                                                                      0x18017310
#define OTP_RW1_reg_addr                                                             "0xB8017310"
#define OTP_RW1_reg                                                                  0xB8017310
#define set_OTP_RW1_reg(data)   (*((volatile unsigned int*) OTP_RW1_reg)=data)
#define get_OTP_RW1_reg   (*((volatile unsigned int*) OTP_RW1_reg))
#define OTP_RW1_inst_adr                                                             "0x00C4"
#define OTP_RW1_inst                                                                 0x00C4
#define OTP_RW1_trs_shift                                                            (24)
#define OTP_RW1_trs_mask                                                             (0x7F000000)
#define OTP_RW1_trs(data)                                                            (0x7F000000&((data)<<24))
#define OTP_RW1_trs_src(data)                                                        ((0x7F000000&(data))>>24)
#define OTP_RW1_get_trs(data)                                                        ((0x7F000000&(data))>>24)
#define OTP_RW1_tcsrst_shift                                                         (16)
#define OTP_RW1_tcsrst_mask                                                          (0x007F0000)
#define OTP_RW1_tcsrst(data)                                                         (0x007F0000&((data)<<16))
#define OTP_RW1_tcsrst_src(data)                                                     ((0x007F0000&(data))>>16)
#define OTP_RW1_get_tcsrst(data)                                                     ((0x007F0000&(data))>>16)
#define OTP_RW1_op_hold_shift                                                        (0)
#define OTP_RW1_op_hold_mask                                                         (0x0000FFFF)
#define OTP_RW1_op_hold(data)                                                        (0x0000FFFF&((data)<<0))
#define OTP_RW1_op_hold_src(data)                                                    ((0x0000FFFF&(data))>>0)
#define OTP_RW1_get_op_hold(data)                                                    ((0x0000FFFF&(data))>>0)


#define OTP_RW2                                                                      0x18017314
#define OTP_RW2_reg_addr                                                             "0xB8017314"
#define OTP_RW2_reg                                                                  0xB8017314
#define set_OTP_RW2_reg(data)   (*((volatile unsigned int*) OTP_RW2_reg)=data)
#define get_OTP_RW2_reg   (*((volatile unsigned int*) OTP_RW2_reg))
#define OTP_RW2_inst_adr                                                             "0x00C5"
#define OTP_RW2_inst                                                                 0x00C5
#define OTP_RW2_twcad_shift                                                          (0)
#define OTP_RW2_twcad_mask                                                           (0x000003FF)
#define OTP_RW2_twcad(data)                                                          (0x000003FF&((data)<<0))
#define OTP_RW2_twcad_src(data)                                                      ((0x000003FF&(data))>>0)
#define OTP_RW2_get_twcad(data)                                                      ((0x000003FF&(data))>>0)


#define OTP_RD                                                                       0x18017318
#define OTP_RD_reg_addr                                                              "0xB8017318"
#define OTP_RD_reg                                                                   0xB8017318
#define set_OTP_RD_reg(data)   (*((volatile unsigned int*) OTP_RD_reg)=data)
#define get_OTP_RD_reg   (*((volatile unsigned int*) OTP_RD_reg))
#define OTP_RD_inst_adr                                                              "0x00C6"
#define OTP_RD_inst                                                                  0x00C6
#define OTP_RD_treaden_shift                                                         (0)
#define OTP_RD_treaden_mask                                                          (0x0000000F)
#define OTP_RD_treaden(data)                                                         (0x0000000F&((data)<<0))
#define OTP_RD_treaden_src(data)                                                     ((0x0000000F&(data))>>0)
#define OTP_RD_get_treaden(data)                                                     ((0x0000000F&(data))>>0)


#define OTP_PROG1                                                                    0x1801731C
#define OTP_PROG1_reg_addr                                                           "0xB801731C"
#define OTP_PROG1_reg                                                                0xB801731C
#define set_OTP_PROG1_reg(data)   (*((volatile unsigned int*) OTP_PROG1_reg)=data)
#define get_OTP_PROG1_reg   (*((volatile unsigned int*) OTP_PROG1_reg))
#define OTP_PROG1_inst_adr                                                           "0x00C7"
#define OTP_PROG1_inst                                                               0x00C7
#define OTP_PROG1_tcph_shift                                                         (24)
#define OTP_PROG1_tcph_mask                                                          (0xFF000000)
#define OTP_PROG1_tcph(data)                                                         (0xFF000000&((data)<<24))
#define OTP_PROG1_tcph_src(data)                                                     ((0xFF000000&(data))>>24)
#define OTP_PROG1_get_tcph(data)                                                     ((0xFF000000&(data))>>24)
#define OTP_PROG1_tpw_shift                                                          (16)
#define OTP_PROG1_tpw_mask                                                           (0x00FF0000)
#define OTP_PROG1_tpw(data)                                                          (0x00FF0000&((data)<<16))
#define OTP_PROG1_tpw_src(data)                                                      ((0x00FF0000&(data))>>16)
#define OTP_PROG1_get_tpw(data)                                                      ((0x00FF0000&(data))>>16)
#define OTP_PROG1_tcps_shift                                                         (8)
#define OTP_PROG1_tcps_mask                                                          (0x0000FF00)
#define OTP_PROG1_tcps(data)                                                         (0x0000FF00&((data)<<8))
#define OTP_PROG1_tcps_src(data)                                                     ((0x0000FF00&(data))>>8)
#define OTP_PROG1_get_tcps(data)                                                     ((0x0000FF00&(data))>>8)
#define OTP_PROG1_tpes_shift                                                         (0)
#define OTP_PROG1_tpes_mask                                                          (0x000000FF)
#define OTP_PROG1_tpes(data)                                                         (0x000000FF&((data)<<0))
#define OTP_PROG1_tpes_src(data)                                                     ((0x000000FF&(data))>>0)
#define OTP_PROG1_get_tpes(data)                                                     ((0x000000FF&(data))>>0)


#define OTP_PROG2                                                                    0x18017320
#define OTP_PROG2_reg_addr                                                           "0xB8017320"
#define OTP_PROG2_reg                                                                0xB8017320
#define set_OTP_PROG2_reg(data)   (*((volatile unsigned int*) OTP_PROG2_reg)=data)
#define get_OTP_PROG2_reg   (*((volatile unsigned int*) OTP_PROG2_reg))
#define OTP_PROG2_inst_adr                                                           "0x00C8"
#define OTP_PROG2_inst                                                               0x00C8
#define OTP_PROG2_tpvsa_shift                                                        (28)
#define OTP_PROG2_tpvsa_mask                                                         (0xF0000000)
#define OTP_PROG2_tpvsa(data)                                                        (0xF0000000&((data)<<28))
#define OTP_PROG2_tpvsa_src(data)                                                    ((0xF0000000&(data))>>28)
#define OTP_PROG2_get_tpvsa(data)                                                    ((0xF0000000&(data))>>28)
#define OTP_PROG2_tpvhr_shift                                                        (24)
#define OTP_PROG2_tpvhr_mask                                                         (0x0F000000)
#define OTP_PROG2_tpvhr(data)                                                        (0x0F000000&((data)<<24))
#define OTP_PROG2_tpvhr_src(data)                                                    ((0x0F000000&(data))>>24)
#define OTP_PROG2_get_tpvhr(data)                                                    ((0x0F000000&(data))>>24)
#define OTP_PROG2_trwh_shift                                                         (20)
#define OTP_PROG2_trwh_mask                                                          (0x00F00000)
#define OTP_PROG2_trwh(data)                                                         (0x00F00000&((data)<<20))
#define OTP_PROG2_trwh_src(data)                                                     ((0x00F00000&(data))>>20)
#define OTP_PROG2_get_trwh(data)                                                     ((0x00F00000&(data))>>20)
#define OTP_PROG2_tpgsv_shift                                                        (16)
#define OTP_PROG2_tpgsv_mask                                                         (0x000F0000)
#define OTP_PROG2_tpgsv(data)                                                        (0x000F0000&((data)<<16))
#define OTP_PROG2_tpgsv_src(data)                                                    ((0x000F0000&(data))>>16)
#define OTP_PROG2_get_tpgsv(data)                                                    ((0x000F0000&(data))>>16)
#define OTP_PROG2_tpvsr_shift                                                        (8)
#define OTP_PROG2_tpvsr_mask                                                         (0x0000FF00)
#define OTP_PROG2_tpvsr(data)                                                        (0x0000FF00&((data)<<8))
#define OTP_PROG2_tpvsr_src(data)                                                    ((0x0000FF00&(data))>>8)
#define OTP_PROG2_get_tpvsr(data)                                                    ((0x0000FF00&(data))>>8)
#define OTP_PROG2_tpeh_shift                                                         (0)
#define OTP_PROG2_tpeh_mask                                                          (0x000000FF)
#define OTP_PROG2_tpeh(data)                                                         (0x000000FF&((data)<<0))
#define OTP_PROG2_tpeh_src(data)                                                     ((0x000000FF&(data))>>0)
#define OTP_PROG2_get_tpeh(data)                                                     ((0x000000FF&(data))>>0)


#define OTP_BC                                                                       0x18017324
#define OTP_BC_reg_addr                                                              "0xB8017324"
#define OTP_BC_reg                                                                   0xB8017324
#define set_OTP_BC_reg(data)   (*((volatile unsigned int*) OTP_BC_reg)=data)
#define get_OTP_BC_reg   (*((volatile unsigned int*) OTP_BC_reg))
#define OTP_BC_inst_adr                                                              "0x00C9"
#define OTP_BC_inst                                                                  0x00C9
#define OTP_BC_tbcacc_shift                                                          (12)
#define OTP_BC_tbcacc_mask                                                           (0x0000F000)
#define OTP_BC_tbcacc(data)                                                          (0x0000F000&((data)<<12))
#define OTP_BC_tbcacc_src(data)                                                      ((0x0000F000&(data))>>12)
#define OTP_BC_get_tbcacc(data)                                                      ((0x0000F000&(data))>>12)
#define OTP_BC_tcpes_shift                                                           (8)
#define OTP_BC_tcpes_mask                                                            (0x00000F00)
#define OTP_BC_tcpes(data)                                                           (0x00000F00&((data)<<8))
#define OTP_BC_tcpes_src(data)                                                       ((0x00000F00&(data))>>8)
#define OTP_BC_get_tcpes(data)                                                       ((0x00000F00&(data))>>8)
#define OTP_BC_tcprd_shift                                                           (0)
#define OTP_BC_tcprd_mask                                                            (0x0000003F)
#define OTP_BC_tcprd(data)                                                           (0x0000003F&((data)<<0))
#define OTP_BC_tcprd_src(data)                                                       ((0x0000003F&(data))>>0)
#define OTP_BC_get_tcprd(data)                                                       ((0x0000003F&(data))>>0)


#define OTP_TD                                                                       0x18017328
#define OTP_TD_reg_addr                                                              "0xB8017328"
#define OTP_TD_reg                                                                   0xB8017328
#define set_OTP_TD_reg(data)   (*((volatile unsigned int*) OTP_TD_reg)=data)
#define get_OTP_TD_reg   (*((volatile unsigned int*) OTP_TD_reg))
#define OTP_TD_inst_adr                                                              "0x00CA"
#define OTP_TD_inst                                                                  0x00CA
#define OTP_TD_tacct_shift                                                           (4)
#define OTP_TD_tacct_mask                                                            (0x000000F0)
#define OTP_TD_tacct(data)                                                           (0x000000F0&((data)<<4))
#define OTP_TD_tacct_src(data)                                                       ((0x000000F0&(data))>>4)
#define OTP_TD_get_tacct(data)                                                       ((0x000000F0&(data))>>4)
#define OTP_TD_trdes_shift                                                           (0)
#define OTP_TD_trdes_mask                                                            (0x0000000F)
#define OTP_TD_trdes(data)                                                           (0x0000000F&((data)<<0))
#define OTP_TD_trdes_src(data)                                                       ((0x0000000F&(data))>>0)
#define OTP_TD_get_trdes(data)                                                       ((0x0000000F&(data))>>0)


#define OTP_DBG                                                                      0x18017330
#define OTP_DBG_reg_addr                                                             "0xB8017330"
#define OTP_DBG_reg                                                                  0xB8017330
#define set_OTP_DBG_reg(data)   (*((volatile unsigned int*) OTP_DBG_reg)=data)
#define get_OTP_DBG_reg   (*((volatile unsigned int*) OTP_DBG_reg))
#define OTP_DBG_inst_adr                                                             "0x00CC"
#define OTP_DBG_inst                                                                 0x00CC
#define OTP_DBG_enable_shift                                                         (8)
#define OTP_DBG_enable_mask                                                          (0x00000100)
#define OTP_DBG_enable(data)                                                         (0x00000100&((data)<<8))
#define OTP_DBG_enable_src(data)                                                     ((0x00000100&(data))>>8)
#define OTP_DBG_get_enable(data)                                                     ((0x00000100&(data))>>8)
#define OTP_DBG_sel1_shift                                                           (4)
#define OTP_DBG_sel1_mask                                                            (0x000000F0)
#define OTP_DBG_sel1(data)                                                           (0x000000F0&((data)<<4))
#define OTP_DBG_sel1_src(data)                                                       ((0x000000F0&(data))>>4)
#define OTP_DBG_get_sel1(data)                                                       ((0x000000F0&(data))>>4)
#define OTP_DBG_sel0_shift                                                           (0)
#define OTP_DBG_sel0_mask                                                            (0x0000000F)
#define OTP_DBG_sel0(data)                                                           (0x0000000F&((data)<<0))
#define OTP_DBG_sel0_src(data)                                                       ((0x0000000F&(data))>>0)
#define OTP_DBG_get_sel0(data)                                                       ((0x0000000F&(data))>>0)


#endif
