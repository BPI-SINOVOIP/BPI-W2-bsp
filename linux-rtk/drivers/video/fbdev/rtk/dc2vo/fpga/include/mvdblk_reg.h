/**************************************************************
// Spec Version                  : 0.2
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2012/6/22 11:40:33
***************************************************************/


#ifndef _MVDBLK_REG_H_INCLUDED_
#define _MVDBLK_REG_H_INCLUDED_
#ifdef  _MVDBLK_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     PicType:3;
unsigned int     FirstMbOfPic:1;
unsigned int     FirstMbOfSlice:1;
}MVDBLK_COMM;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     LdPxmemCount:16;
}MVDBLK_COMM1;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     DbgDumpCount:16;
}MVDBLK_COMM2;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     SetAddr:1;
unsigned int     MbAddrY:7;
unsigned int     MbAddrX:7;
unsigned int     MbAddr:13;
}MVDBLK_COMM3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     HwCtrl:7;
unsigned int     SoftReset:1;
}MVDBLK_COMM4;

typedef struct 
{
unsigned int     DbgWriteBuf:32;
}MVDBLK_COMM5;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     DbgStoreCount:16;
}MVDBLK_COMM6;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     RefPicList10Short:1;
unsigned int     BotLeTopAbsDiffPOC:1;
unsigned int     DirectSpatial:1;
unsigned int     ColPicStruct:2;
unsigned int     CurrPicStruct:2;
unsigned int     Direct8x8Inf:1;
}MVDBLK_H264PIC;

typedef struct 
{
unsigned int     CurrFrmPoc:32;
}MVDBLK_H264PIC1;

typedef struct 
{
unsigned int     CurrTopPoc:32;
}MVDBLK_H264PIC2;

typedef struct 
{
unsigned int     CurrBotPoc:32;
}MVDBLK_H264PIC3;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     CoMem8x8:1;
}MVDBLK_H264CO;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     StCoMemSAddr:31;
}MVDBLK_H264CO1;

typedef struct 
{
unsigned int     MbaffAddr:1;
unsigned int     LdCoMemSAddr:31;
}MVDBLK_H264CO2;

typedef struct 
{
unsigned int     EnableLdCoMem1:1;
unsigned int     LdCoMemSAddr1:31;
}MVDBLK_H264CO3;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     AutoLdStOff:1;
unsigned int     InitNhMemCmd:1;
unsigned int     LdNhMemCmd:1;
unsigned int     StNhMemCmd:1;
}MVDBLK_H264NH;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     StNhMemSAddr:31;
}MVDBLK_H264NH1;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     LdNhMemSAddr:31;
}MVDBLK_H264NH2;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     StDiMemPicIndex:7;
}MVDBLK_H264DI;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     StDiEnable:1;
unsigned int     StDiMvThres:8;
}MVDBLK_H264DI1;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     List1Size:5;
unsigned int     List0Size:5;
}MVDBLK_H264PX;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     FrmPocAddrL0:16;
}MVDBLK_H264PX1;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     TopPocAddrL0:16;
}MVDBLK_H264PX2;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     BotPocAddrL0:16;
}MVDBLK_H264PX3;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     FrmPocAddrL1:16;
}MVDBLK_H264PX4;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     TopPocAddrL1:16;
}MVDBLK_H264PX5;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     BotPocAddrL1:16;
}MVDBLK_H264PX6;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     PicInfoAddr:16;
}MVDBLK_H264PX7;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     RefField:1;
unsigned int     FastUVmc:1;
unsigned int     ScaleFactor:11;
}MVDBLK_VC1PIC;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     Scale_fw:8;
unsigned int     Scale1_fw:12;
unsigned int     Scale2_fw:8;
}MVDBLK_VC1PIC1;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     ScaleUpOpp_fw:1;
unsigned int     ScaleZone1X_fw:6;
unsigned int     ScaleZone1Y_fw:4;
unsigned int     Zone1OffsetX_fw:6;
unsigned int     Zone1OffsetY_fw:4;
}MVDBLK_VC1PIC2;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     Scale_bw:8;
unsigned int     Scale1_bw:12;
unsigned int     Scale2_bw:8;
}MVDBLK_VC1PIC3;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     ScaleUpOpp_bw:1;
unsigned int     ScaleZone1X_bw:6;
unsigned int     ScaleZone1Y_bw:4;
unsigned int     Zone1OffsetX_bw:6;
unsigned int     Zone1OffsetY_bw:4;
}MVDBLK_VC1PIC4;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     RangeY:12;
unsigned int     RangeX:13;
}MVDBLK_VC1PIC5;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     AecEnable:1;
unsigned int     PFieldSkip:1;
unsigned int     BFieldEnhanced:1;
unsigned int     PicRefFlag:1;
unsigned int     PicStructure:1;
}MVDBLK_AVSPIC;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     BlockDist0:9;
unsigned int     reserved_1:7;
unsigned int     BlockDist1:9;
}MVDBLK_AVSPIC1;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     BlockDist2:9;
unsigned int     reserved_1:7;
unsigned int     BlockDist3:9;
}MVDBLK_AVSPIC2;

typedef struct 
{
unsigned int     B16384DiviTRp0:16;
unsigned int     B16384DiviTRp1:16;
}MVDBLK_AVSPIC3;

typedef struct 
{
unsigned int     B16384DiviTRp2:16;
unsigned int     B16384DiviTRp3:16;
}MVDBLK_AVSPIC4;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     iTRb0:9;
unsigned int     reserved_1:7;
unsigned int     iTRb1:9;
}MVDBLK_AVSPIC5;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     iTRb2:9;
unsigned int     reserved_1:7;
unsigned int     iTRb3:9;
}MVDBLK_AVSPIC6;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     iTRd:9;
}MVDBLK_AVSPIC7;

typedef struct 
{
unsigned int     iRatio0:32;
}MVDBLK_RM89PIC;

typedef struct 
{
unsigned int     iRatio1:32;
}MVDBLK_RM89PIC1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hix:14;
unsigned int     reserved_1:2;
unsigned int     lox:14;
}MVDBLK_RM89DIRECT;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hiy:14;
unsigned int     reserved_1:2;
unsigned int     loy:14;
}MVDBLK_RM89DIRECT1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hicx:14;
unsigned int     reserved_1:2;
unsigned int     locx:14;
}MVDBLK_RM89DIRECT2;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hicy:14;
unsigned int     reserved_1:2;
unsigned int     locy:14;
}MVDBLK_RM89DIRECT3;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     ZeroMvd:1;
}MVDBLK_RM89PIC2;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hix_4v:14;
unsigned int     reserved_1:2;
unsigned int     lox_4v:14;
}MVDBLK_RM89DIRECT4;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hiy_4v:14;
unsigned int     reserved_1:2;
unsigned int     loy_4v:14;
}MVDBLK_RM89DIRECT5;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hicx_4v:14;
unsigned int     reserved_1:2;
unsigned int     locx_4v:14;
}MVDBLK_RM89DIRECT6;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hicy_4v:14;
unsigned int     reserved_1:2;
unsigned int     locy_4v:14;
}MVDBLK_RM89DIRECT7;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     entry:28;
}MVDBLK_SEPOOL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     SetNhAvail:1;
}MVDBLK_H264BASE;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     LeftAvail:1;
unsigned int     TopAvail:1;
unsigned int     TopRightAvail:1;
unsigned int     TopLeftAvail:1;
}MVDBLK_H264BASE1;

typedef struct 
{
unsigned int     GenPulse:1;
unsigned int     PicCount:15;
unsigned int     DbgCtrl:3;
unsigned int     MbAddr:13;
}MVDBLK_DBG;

#endif

#define MVDBLK_COMM                                                                  0x1800e660
#define MVDBLK_COMM_reg_addr                                                         "0xB800E660"
#define MVDBLK_COMM_reg                                                              0xB800E660
#define set_MVDBLK_COMM_reg(data)   (*((volatile unsigned int*) MVDBLK_COMM_reg)=data)
#define get_MVDBLK_COMM_reg   (*((volatile unsigned int*) MVDBLK_COMM_reg))
#define MVDBLK_COMM_inst_adr                                                         "0x0098"
#define MVDBLK_COMM_inst                                                             0x0098
#define MVDBLK_COMM_PicType_shift                                                    (2)
#define MVDBLK_COMM_PicType_mask                                                     (0x0000001C)
#define MVDBLK_COMM_PicType(data)                                                    (0x0000001C&((data)<<2))
#define MVDBLK_COMM_PicType_src(data)                                                ((0x0000001C&(data))>>2)
#define MVDBLK_COMM_get_PicType(data)                                                ((0x0000001C&(data))>>2)
#define MVDBLK_COMM_FirstMbOfPic_shift                                               (1)
#define MVDBLK_COMM_FirstMbOfPic_mask                                                (0x00000002)
#define MVDBLK_COMM_FirstMbOfPic(data)                                               (0x00000002&((data)<<1))
#define MVDBLK_COMM_FirstMbOfPic_src(data)                                           ((0x00000002&(data))>>1)
#define MVDBLK_COMM_get_FirstMbOfPic(data)                                           ((0x00000002&(data))>>1)
#define MVDBLK_COMM_FirstMbOfSlice_shift                                             (0)
#define MVDBLK_COMM_FirstMbOfSlice_mask                                              (0x00000001)
#define MVDBLK_COMM_FirstMbOfSlice(data)                                             (0x00000001&((data)<<0))
#define MVDBLK_COMM_FirstMbOfSlice_src(data)                                         ((0x00000001&(data))>>0)
#define MVDBLK_COMM_get_FirstMbOfSlice(data)                                         ((0x00000001&(data))>>0)


#define MVDBLK_COMM1                                                                 0x1800e664
#define MVDBLK_COMM1_reg_addr                                                        "0xB800E664"
#define MVDBLK_COMM1_reg                                                             0xB800E664
#define set_MVDBLK_COMM1_reg(data)   (*((volatile unsigned int*) MVDBLK_COMM1_reg)=data)
#define get_MVDBLK_COMM1_reg   (*((volatile unsigned int*) MVDBLK_COMM1_reg))
#define MVDBLK_COMM1_inst_adr                                                        "0x0099"
#define MVDBLK_COMM1_inst                                                            0x0099
#define MVDBLK_COMM1_LdPxmemCount_shift                                              (0)
#define MVDBLK_COMM1_LdPxmemCount_mask                                               (0x0000FFFF)
#define MVDBLK_COMM1_LdPxmemCount(data)                                              (0x0000FFFF&((data)<<0))
#define MVDBLK_COMM1_LdPxmemCount_src(data)                                          ((0x0000FFFF&(data))>>0)
#define MVDBLK_COMM1_get_LdPxmemCount(data)                                          ((0x0000FFFF&(data))>>0)


#define MVDBLK_COMM2                                                                 0x1800e668
#define MVDBLK_COMM2_reg_addr                                                        "0xB800E668"
#define MVDBLK_COMM2_reg                                                             0xB800E668
#define set_MVDBLK_COMM2_reg(data)   (*((volatile unsigned int*) MVDBLK_COMM2_reg)=data)
#define get_MVDBLK_COMM2_reg   (*((volatile unsigned int*) MVDBLK_COMM2_reg))
#define MVDBLK_COMM2_inst_adr                                                        "0x009A"
#define MVDBLK_COMM2_inst                                                            0x009A
#define MVDBLK_COMM2_DbgDumpCount_shift                                              (0)
#define MVDBLK_COMM2_DbgDumpCount_mask                                               (0x0000FFFF)
#define MVDBLK_COMM2_DbgDumpCount(data)                                              (0x0000FFFF&((data)<<0))
#define MVDBLK_COMM2_DbgDumpCount_src(data)                                          ((0x0000FFFF&(data))>>0)
#define MVDBLK_COMM2_get_DbgDumpCount(data)                                          ((0x0000FFFF&(data))>>0)


#define MVDBLK_COMM3                                                                 0x1800e66c
#define MVDBLK_COMM3_reg_addr                                                        "0xB800E66C"
#define MVDBLK_COMM3_reg                                                             0xB800E66C
#define set_MVDBLK_COMM3_reg(data)   (*((volatile unsigned int*) MVDBLK_COMM3_reg)=data)
#define get_MVDBLK_COMM3_reg   (*((volatile unsigned int*) MVDBLK_COMM3_reg))
#define MVDBLK_COMM3_inst_adr                                                        "0x009B"
#define MVDBLK_COMM3_inst                                                            0x009B
#define MVDBLK_COMM3_SetAddr_shift                                                   (27)
#define MVDBLK_COMM3_SetAddr_mask                                                    (0x08000000)
#define MVDBLK_COMM3_SetAddr(data)                                                   (0x08000000&((data)<<27))
#define MVDBLK_COMM3_SetAddr_src(data)                                               ((0x08000000&(data))>>27)
#define MVDBLK_COMM3_get_SetAddr(data)                                               ((0x08000000&(data))>>27)
#define MVDBLK_COMM3_MbAddrY_shift                                                   (20)
#define MVDBLK_COMM3_MbAddrY_mask                                                    (0x07F00000)
#define MVDBLK_COMM3_MbAddrY(data)                                                   (0x07F00000&((data)<<20))
#define MVDBLK_COMM3_MbAddrY_src(data)                                               ((0x07F00000&(data))>>20)
#define MVDBLK_COMM3_get_MbAddrY(data)                                               ((0x07F00000&(data))>>20)
#define MVDBLK_COMM3_MbAddrX_shift                                                   (13)
#define MVDBLK_COMM3_MbAddrX_mask                                                    (0x000FE000)
#define MVDBLK_COMM3_MbAddrX(data)                                                   (0x000FE000&((data)<<13))
#define MVDBLK_COMM3_MbAddrX_src(data)                                               ((0x000FE000&(data))>>13)
#define MVDBLK_COMM3_get_MbAddrX(data)                                               ((0x000FE000&(data))>>13)
#define MVDBLK_COMM3_MbAddr_shift                                                    (0)
#define MVDBLK_COMM3_MbAddr_mask                                                     (0x00001FFF)
#define MVDBLK_COMM3_MbAddr(data)                                                    (0x00001FFF&((data)<<0))
#define MVDBLK_COMM3_MbAddr_src(data)                                                ((0x00001FFF&(data))>>0)
#define MVDBLK_COMM3_get_MbAddr(data)                                                ((0x00001FFF&(data))>>0)


#define MVDBLK_COMM4                                                                 0x1800e670
#define MVDBLK_COMM4_reg_addr                                                        "0xB800E670"
#define MVDBLK_COMM4_reg                                                             0xB800E670
#define set_MVDBLK_COMM4_reg(data)   (*((volatile unsigned int*) MVDBLK_COMM4_reg)=data)
#define get_MVDBLK_COMM4_reg   (*((volatile unsigned int*) MVDBLK_COMM4_reg))
#define MVDBLK_COMM4_inst_adr                                                        "0x009C"
#define MVDBLK_COMM4_inst                                                            0x009C
#define MVDBLK_COMM4_HwCtrl_shift                                                    (1)
#define MVDBLK_COMM4_HwCtrl_mask                                                     (0x000000FE)
#define MVDBLK_COMM4_HwCtrl(data)                                                    (0x000000FE&((data)<<1))
#define MVDBLK_COMM4_HwCtrl_src(data)                                                ((0x000000FE&(data))>>1)
#define MVDBLK_COMM4_get_HwCtrl(data)                                                ((0x000000FE&(data))>>1)
#define MVDBLK_COMM4_SoftReset_shift                                                 (0)
#define MVDBLK_COMM4_SoftReset_mask                                                  (0x00000001)
#define MVDBLK_COMM4_SoftReset(data)                                                 (0x00000001&((data)<<0))
#define MVDBLK_COMM4_SoftReset_src(data)                                             ((0x00000001&(data))>>0)
#define MVDBLK_COMM4_get_SoftReset(data)                                             ((0x00000001&(data))>>0)


#define MVDBLK_COMM5_0                                                               0x1800E674
#define MVDBLK_COMM5_1                                                               0x1800E678
#define MVDBLK_COMM5_2                                                               0x1800E67C
#define MVDBLK_COMM5_0_reg_addr                                                      "0xB800E674"
#define MVDBLK_COMM5_1_reg_addr                                                      "0xB800E678"
#define MVDBLK_COMM5_2_reg_addr                                                      "0xB800E67C"
#define MVDBLK_COMM5_0_reg                                                           0xB800E674
#define MVDBLK_COMM5_1_reg                                                           0xB800E678
#define MVDBLK_COMM5_2_reg                                                           0xB800E67C
#define set_MVDBLK_COMM5_0_reg(data)   (*((volatile unsigned int*) MVDBLK_COMM5_0_reg)=data)
#define set_MVDBLK_COMM5_1_reg(data)   (*((volatile unsigned int*) MVDBLK_COMM5_1_reg)=data)
#define set_MVDBLK_COMM5_2_reg(data)   (*((volatile unsigned int*) MVDBLK_COMM5_2_reg)=data)
#define get_MVDBLK_COMM5_0_reg   (*((volatile unsigned int*) MVDBLK_COMM5_0_reg))
#define get_MVDBLK_COMM5_1_reg   (*((volatile unsigned int*) MVDBLK_COMM5_1_reg))
#define get_MVDBLK_COMM5_2_reg   (*((volatile unsigned int*) MVDBLK_COMM5_2_reg))
#define MVDBLK_COMM5_0_inst_adr                                                      "0x009D"
#define MVDBLK_COMM5_1_inst_adr                                                      "0x009E"
#define MVDBLK_COMM5_2_inst_adr                                                      "0x009F"
#define MVDBLK_COMM5_0_inst                                                          0x009D
#define MVDBLK_COMM5_1_inst                                                          0x009E
#define MVDBLK_COMM5_2_inst                                                          0x009F
#define MVDBLK_COMM5_DbgWriteBuf_shift                                               (0)
#define MVDBLK_COMM5_DbgWriteBuf_mask                                                (0xFFFFFFFF)
#define MVDBLK_COMM5_DbgWriteBuf(data)                                               (0xFFFFFFFF&((data)<<0))
#define MVDBLK_COMM5_DbgWriteBuf_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define MVDBLK_COMM5_get_DbgWriteBuf(data)                                           ((0xFFFFFFFF&(data))>>0)


#define MVDBLK_COMM6                                                                 0x1800e690
#define MVDBLK_COMM6_reg_addr                                                        "0xB800E690"
#define MVDBLK_COMM6_reg                                                             0xB800E690
#define set_MVDBLK_COMM6_reg(data)   (*((volatile unsigned int*) MVDBLK_COMM6_reg)=data)
#define get_MVDBLK_COMM6_reg   (*((volatile unsigned int*) MVDBLK_COMM6_reg))
#define MVDBLK_COMM6_inst_adr                                                        "0x00A4"
#define MVDBLK_COMM6_inst                                                            0x00A4
#define MVDBLK_COMM6_DbgStoreCount_shift                                             (0)
#define MVDBLK_COMM6_DbgStoreCount_mask                                              (0x0000FFFF)
#define MVDBLK_COMM6_DbgStoreCount(data)                                             (0x0000FFFF&((data)<<0))
#define MVDBLK_COMM6_DbgStoreCount_src(data)                                         ((0x0000FFFF&(data))>>0)
#define MVDBLK_COMM6_get_DbgStoreCount(data)                                         ((0x0000FFFF&(data))>>0)


#define MVDBLK_H264PIC                                                               0x1800e600
#define MVDBLK_H264PIC_reg_addr                                                      "0xB800E600"
#define MVDBLK_H264PIC_reg                                                           0xB800E600
#define set_MVDBLK_H264PIC_reg(data)   (*((volatile unsigned int*) MVDBLK_H264PIC_reg)=data)
#define get_MVDBLK_H264PIC_reg   (*((volatile unsigned int*) MVDBLK_H264PIC_reg))
#define MVDBLK_H264PIC_inst_adr                                                      "0x0080"
#define MVDBLK_H264PIC_inst                                                          0x0080
#define MVDBLK_H264PIC_RefPicList10Short_shift                                       (7)
#define MVDBLK_H264PIC_RefPicList10Short_mask                                        (0x00000080)
#define MVDBLK_H264PIC_RefPicList10Short(data)                                       (0x00000080&((data)<<7))
#define MVDBLK_H264PIC_RefPicList10Short_src(data)                                   ((0x00000080&(data))>>7)
#define MVDBLK_H264PIC_get_RefPicList10Short(data)                                   ((0x00000080&(data))>>7)
#define MVDBLK_H264PIC_BotLeTopAbsDiffPOC_shift                                      (6)
#define MVDBLK_H264PIC_BotLeTopAbsDiffPOC_mask                                       (0x00000040)
#define MVDBLK_H264PIC_BotLeTopAbsDiffPOC(data)                                      (0x00000040&((data)<<6))
#define MVDBLK_H264PIC_BotLeTopAbsDiffPOC_src(data)                                  ((0x00000040&(data))>>6)
#define MVDBLK_H264PIC_get_BotLeTopAbsDiffPOC(data)                                  ((0x00000040&(data))>>6)
#define MVDBLK_H264PIC_DirectSpatial_shift                                           (5)
#define MVDBLK_H264PIC_DirectSpatial_mask                                            (0x00000020)
#define MVDBLK_H264PIC_DirectSpatial(data)                                           (0x00000020&((data)<<5))
#define MVDBLK_H264PIC_DirectSpatial_src(data)                                       ((0x00000020&(data))>>5)
#define MVDBLK_H264PIC_get_DirectSpatial(data)                                       ((0x00000020&(data))>>5)
#define MVDBLK_H264PIC_ColPicStruct_shift                                            (3)
#define MVDBLK_H264PIC_ColPicStruct_mask                                             (0x00000018)
#define MVDBLK_H264PIC_ColPicStruct(data)                                            (0x00000018&((data)<<3))
#define MVDBLK_H264PIC_ColPicStruct_src(data)                                        ((0x00000018&(data))>>3)
#define MVDBLK_H264PIC_get_ColPicStruct(data)                                        ((0x00000018&(data))>>3)
#define MVDBLK_H264PIC_CurrPicStruct_shift                                           (1)
#define MVDBLK_H264PIC_CurrPicStruct_mask                                            (0x00000006)
#define MVDBLK_H264PIC_CurrPicStruct(data)                                           (0x00000006&((data)<<1))
#define MVDBLK_H264PIC_CurrPicStruct_src(data)                                       ((0x00000006&(data))>>1)
#define MVDBLK_H264PIC_get_CurrPicStruct(data)                                       ((0x00000006&(data))>>1)
#define MVDBLK_H264PIC_Direct8x8Inf_shift                                            (0)
#define MVDBLK_H264PIC_Direct8x8Inf_mask                                             (0x00000001)
#define MVDBLK_H264PIC_Direct8x8Inf(data)                                            (0x00000001&((data)<<0))
#define MVDBLK_H264PIC_Direct8x8Inf_src(data)                                        ((0x00000001&(data))>>0)
#define MVDBLK_H264PIC_get_Direct8x8Inf(data)                                        ((0x00000001&(data))>>0)


#define MVDBLK_H264PIC1                                                              0x1800e604
#define MVDBLK_H264PIC1_reg_addr                                                     "0xB800E604"
#define MVDBLK_H264PIC1_reg                                                          0xB800E604
#define set_MVDBLK_H264PIC1_reg(data)   (*((volatile unsigned int*) MVDBLK_H264PIC1_reg)=data)
#define get_MVDBLK_H264PIC1_reg   (*((volatile unsigned int*) MVDBLK_H264PIC1_reg))
#define MVDBLK_H264PIC1_inst_adr                                                     "0x0081"
#define MVDBLK_H264PIC1_inst                                                         0x0081
#define MVDBLK_H264PIC1_CurrFrmPoc_shift                                             (0)
#define MVDBLK_H264PIC1_CurrFrmPoc_mask                                              (0xFFFFFFFF)
#define MVDBLK_H264PIC1_CurrFrmPoc(data)                                             (0xFFFFFFFF&((data)<<0))
#define MVDBLK_H264PIC1_CurrFrmPoc_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define MVDBLK_H264PIC1_get_CurrFrmPoc(data)                                         ((0xFFFFFFFF&(data))>>0)


#define MVDBLK_H264PIC2                                                              0x1800e608
#define MVDBLK_H264PIC2_reg_addr                                                     "0xB800E608"
#define MVDBLK_H264PIC2_reg                                                          0xB800E608
#define set_MVDBLK_H264PIC2_reg(data)   (*((volatile unsigned int*) MVDBLK_H264PIC2_reg)=data)
#define get_MVDBLK_H264PIC2_reg   (*((volatile unsigned int*) MVDBLK_H264PIC2_reg))
#define MVDBLK_H264PIC2_inst_adr                                                     "0x0082"
#define MVDBLK_H264PIC2_inst                                                         0x0082
#define MVDBLK_H264PIC2_CurrTopPoc_shift                                             (0)
#define MVDBLK_H264PIC2_CurrTopPoc_mask                                              (0xFFFFFFFF)
#define MVDBLK_H264PIC2_CurrTopPoc(data)                                             (0xFFFFFFFF&((data)<<0))
#define MVDBLK_H264PIC2_CurrTopPoc_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define MVDBLK_H264PIC2_get_CurrTopPoc(data)                                         ((0xFFFFFFFF&(data))>>0)


#define MVDBLK_H264PIC3                                                              0x1800e60c
#define MVDBLK_H264PIC3_reg_addr                                                     "0xB800E60C"
#define MVDBLK_H264PIC3_reg                                                          0xB800E60C
#define set_MVDBLK_H264PIC3_reg(data)   (*((volatile unsigned int*) MVDBLK_H264PIC3_reg)=data)
#define get_MVDBLK_H264PIC3_reg   (*((volatile unsigned int*) MVDBLK_H264PIC3_reg))
#define MVDBLK_H264PIC3_inst_adr                                                     "0x0083"
#define MVDBLK_H264PIC3_inst                                                         0x0083
#define MVDBLK_H264PIC3_CurrBotPoc_shift                                             (0)
#define MVDBLK_H264PIC3_CurrBotPoc_mask                                              (0xFFFFFFFF)
#define MVDBLK_H264PIC3_CurrBotPoc(data)                                             (0xFFFFFFFF&((data)<<0))
#define MVDBLK_H264PIC3_CurrBotPoc_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define MVDBLK_H264PIC3_get_CurrBotPoc(data)                                         ((0xFFFFFFFF&(data))>>0)


#define MVDBLK_H264CO                                                                0x1800e610
#define MVDBLK_H264CO_reg_addr                                                       "0xB800E610"
#define MVDBLK_H264CO_reg                                                            0xB800E610
#define set_MVDBLK_H264CO_reg(data)   (*((volatile unsigned int*) MVDBLK_H264CO_reg)=data)
#define get_MVDBLK_H264CO_reg   (*((volatile unsigned int*) MVDBLK_H264CO_reg))
#define MVDBLK_H264CO_inst_adr                                                       "0x0084"
#define MVDBLK_H264CO_inst                                                           0x0084
#define MVDBLK_H264CO_CoMem8x8_shift                                                 (0)
#define MVDBLK_H264CO_CoMem8x8_mask                                                  (0x00000001)
#define MVDBLK_H264CO_CoMem8x8(data)                                                 (0x00000001&((data)<<0))
#define MVDBLK_H264CO_CoMem8x8_src(data)                                             ((0x00000001&(data))>>0)
#define MVDBLK_H264CO_get_CoMem8x8(data)                                             ((0x00000001&(data))>>0)


#define MVDBLK_H264CO1                                                               0x1800e614
#define MVDBLK_H264CO1_reg_addr                                                      "0xB800E614"
#define MVDBLK_H264CO1_reg                                                           0xB800E614
#define set_MVDBLK_H264CO1_reg(data)   (*((volatile unsigned int*) MVDBLK_H264CO1_reg)=data)
#define get_MVDBLK_H264CO1_reg   (*((volatile unsigned int*) MVDBLK_H264CO1_reg))
#define MVDBLK_H264CO1_inst_adr                                                      "0x0085"
#define MVDBLK_H264CO1_inst                                                          0x0085
#define MVDBLK_H264CO1_StCoMemSAddr_shift                                            (0)
#define MVDBLK_H264CO1_StCoMemSAddr_mask                                             (0x7FFFFFFF)
#define MVDBLK_H264CO1_StCoMemSAddr(data)                                            (0x7FFFFFFF&((data)<<0))
#define MVDBLK_H264CO1_StCoMemSAddr_src(data)                                        ((0x7FFFFFFF&(data))>>0)
#define MVDBLK_H264CO1_get_StCoMemSAddr(data)                                        ((0x7FFFFFFF&(data))>>0)


#define MVDBLK_H264CO2                                                               0x1800e618
#define MVDBLK_H264CO2_reg_addr                                                      "0xB800E618"
#define MVDBLK_H264CO2_reg                                                           0xB800E618
#define set_MVDBLK_H264CO2_reg(data)   (*((volatile unsigned int*) MVDBLK_H264CO2_reg)=data)
#define get_MVDBLK_H264CO2_reg   (*((volatile unsigned int*) MVDBLK_H264CO2_reg))
#define MVDBLK_H264CO2_inst_adr                                                      "0x0086"
#define MVDBLK_H264CO2_inst                                                          0x0086
#define MVDBLK_H264CO2_MbaffAddr_shift                                               (31)
#define MVDBLK_H264CO2_MbaffAddr_mask                                                (0x80000000)
#define MVDBLK_H264CO2_MbaffAddr(data)                                               (0x80000000&((data)<<31))
#define MVDBLK_H264CO2_MbaffAddr_src(data)                                           ((0x80000000&(data))>>31)
#define MVDBLK_H264CO2_get_MbaffAddr(data)                                           ((0x80000000&(data))>>31)
#define MVDBLK_H264CO2_LdCoMemSAddr_shift                                            (0)
#define MVDBLK_H264CO2_LdCoMemSAddr_mask                                             (0x7FFFFFFF)
#define MVDBLK_H264CO2_LdCoMemSAddr(data)                                            (0x7FFFFFFF&((data)<<0))
#define MVDBLK_H264CO2_LdCoMemSAddr_src(data)                                        ((0x7FFFFFFF&(data))>>0)
#define MVDBLK_H264CO2_get_LdCoMemSAddr(data)                                        ((0x7FFFFFFF&(data))>>0)


#define MVDBLK_H264CO3                                                               0x1800e61c
#define MVDBLK_H264CO3_reg_addr                                                      "0xB800E61C"
#define MVDBLK_H264CO3_reg                                                           0xB800E61C
#define set_MVDBLK_H264CO3_reg(data)   (*((volatile unsigned int*) MVDBLK_H264CO3_reg)=data)
#define get_MVDBLK_H264CO3_reg   (*((volatile unsigned int*) MVDBLK_H264CO3_reg))
#define MVDBLK_H264CO3_inst_adr                                                      "0x0087"
#define MVDBLK_H264CO3_inst                                                          0x0087
#define MVDBLK_H264CO3_EnableLdCoMem1_shift                                          (31)
#define MVDBLK_H264CO3_EnableLdCoMem1_mask                                           (0x80000000)
#define MVDBLK_H264CO3_EnableLdCoMem1(data)                                          (0x80000000&((data)<<31))
#define MVDBLK_H264CO3_EnableLdCoMem1_src(data)                                      ((0x80000000&(data))>>31)
#define MVDBLK_H264CO3_get_EnableLdCoMem1(data)                                      ((0x80000000&(data))>>31)
#define MVDBLK_H264CO3_LdCoMemSAddr1_shift                                           (0)
#define MVDBLK_H264CO3_LdCoMemSAddr1_mask                                            (0x7FFFFFFF)
#define MVDBLK_H264CO3_LdCoMemSAddr1(data)                                           (0x7FFFFFFF&((data)<<0))
#define MVDBLK_H264CO3_LdCoMemSAddr1_src(data)                                       ((0x7FFFFFFF&(data))>>0)
#define MVDBLK_H264CO3_get_LdCoMemSAddr1(data)                                       ((0x7FFFFFFF&(data))>>0)


#define MVDBLK_H264NH                                                                0x1800e6d0
#define MVDBLK_H264NH_reg_addr                                                       "0xB800E6D0"
#define MVDBLK_H264NH_reg                                                            0xB800E6D0
#define set_MVDBLK_H264NH_reg(data)   (*((volatile unsigned int*) MVDBLK_H264NH_reg)=data)
#define get_MVDBLK_H264NH_reg   (*((volatile unsigned int*) MVDBLK_H264NH_reg))
#define MVDBLK_H264NH_inst_adr                                                       "0x00B4"
#define MVDBLK_H264NH_inst                                                           0x00B4
#define MVDBLK_H264NH_AutoLdStOff_shift                                              (3)
#define MVDBLK_H264NH_AutoLdStOff_mask                                               (0x00000008)
#define MVDBLK_H264NH_AutoLdStOff(data)                                              (0x00000008&((data)<<3))
#define MVDBLK_H264NH_AutoLdStOff_src(data)                                          ((0x00000008&(data))>>3)
#define MVDBLK_H264NH_get_AutoLdStOff(data)                                          ((0x00000008&(data))>>3)
#define MVDBLK_H264NH_InitNhMemCmd_shift                                             (2)
#define MVDBLK_H264NH_InitNhMemCmd_mask                                              (0x00000004)
#define MVDBLK_H264NH_InitNhMemCmd(data)                                             (0x00000004&((data)<<2))
#define MVDBLK_H264NH_InitNhMemCmd_src(data)                                         ((0x00000004&(data))>>2)
#define MVDBLK_H264NH_get_InitNhMemCmd(data)                                         ((0x00000004&(data))>>2)
#define MVDBLK_H264NH_LdNhMemCmd_shift                                               (1)
#define MVDBLK_H264NH_LdNhMemCmd_mask                                                (0x00000002)
#define MVDBLK_H264NH_LdNhMemCmd(data)                                               (0x00000002&((data)<<1))
#define MVDBLK_H264NH_LdNhMemCmd_src(data)                                           ((0x00000002&(data))>>1)
#define MVDBLK_H264NH_get_LdNhMemCmd(data)                                           ((0x00000002&(data))>>1)
#define MVDBLK_H264NH_StNhMemCmd_shift                                               (0)
#define MVDBLK_H264NH_StNhMemCmd_mask                                                (0x00000001)
#define MVDBLK_H264NH_StNhMemCmd(data)                                               (0x00000001&((data)<<0))
#define MVDBLK_H264NH_StNhMemCmd_src(data)                                           ((0x00000001&(data))>>0)
#define MVDBLK_H264NH_get_StNhMemCmd(data)                                           ((0x00000001&(data))>>0)


#define MVDBLK_H264NH1                                                               0x1800e6d4
#define MVDBLK_H264NH1_reg_addr                                                      "0xB800E6D4"
#define MVDBLK_H264NH1_reg                                                           0xB800E6D4
#define set_MVDBLK_H264NH1_reg(data)   (*((volatile unsigned int*) MVDBLK_H264NH1_reg)=data)
#define get_MVDBLK_H264NH1_reg   (*((volatile unsigned int*) MVDBLK_H264NH1_reg))
#define MVDBLK_H264NH1_inst_adr                                                      "0x00B5"
#define MVDBLK_H264NH1_inst                                                          0x00B5
#define MVDBLK_H264NH1_StNhMemSAddr_shift                                            (0)
#define MVDBLK_H264NH1_StNhMemSAddr_mask                                             (0x7FFFFFFF)
#define MVDBLK_H264NH1_StNhMemSAddr(data)                                            (0x7FFFFFFF&((data)<<0))
#define MVDBLK_H264NH1_StNhMemSAddr_src(data)                                        ((0x7FFFFFFF&(data))>>0)
#define MVDBLK_H264NH1_get_StNhMemSAddr(data)                                        ((0x7FFFFFFF&(data))>>0)


#define MVDBLK_H264NH2                                                               0x1800e6d8
#define MVDBLK_H264NH2_reg_addr                                                      "0xB800E6D8"
#define MVDBLK_H264NH2_reg                                                           0xB800E6D8
#define set_MVDBLK_H264NH2_reg(data)   (*((volatile unsigned int*) MVDBLK_H264NH2_reg)=data)
#define get_MVDBLK_H264NH2_reg   (*((volatile unsigned int*) MVDBLK_H264NH2_reg))
#define MVDBLK_H264NH2_inst_adr                                                      "0x00B6"
#define MVDBLK_H264NH2_inst                                                          0x00B6
#define MVDBLK_H264NH2_LdNhMemSAddr_shift                                            (0)
#define MVDBLK_H264NH2_LdNhMemSAddr_mask                                             (0x7FFFFFFF)
#define MVDBLK_H264NH2_LdNhMemSAddr(data)                                            (0x7FFFFFFF&((data)<<0))
#define MVDBLK_H264NH2_LdNhMemSAddr_src(data)                                        ((0x7FFFFFFF&(data))>>0)
#define MVDBLK_H264NH2_get_LdNhMemSAddr(data)                                        ((0x7FFFFFFF&(data))>>0)


#define MVDBLK_H264DI                                                                0x1800e6dc
#define MVDBLK_H264DI_reg_addr                                                       "0xB800E6DC"
#define MVDBLK_H264DI_reg                                                            0xB800E6DC
#define set_MVDBLK_H264DI_reg(data)   (*((volatile unsigned int*) MVDBLK_H264DI_reg)=data)
#define get_MVDBLK_H264DI_reg   (*((volatile unsigned int*) MVDBLK_H264DI_reg))
#define MVDBLK_H264DI_inst_adr                                                       "0x00B7"
#define MVDBLK_H264DI_inst                                                           0x00B7
#define MVDBLK_H264DI_StDiMemPicIndex_shift                                          (0)
#define MVDBLK_H264DI_StDiMemPicIndex_mask                                           (0x0000007F)
#define MVDBLK_H264DI_StDiMemPicIndex(data)                                          (0x0000007F&((data)<<0))
#define MVDBLK_H264DI_StDiMemPicIndex_src(data)                                      ((0x0000007F&(data))>>0)
#define MVDBLK_H264DI_get_StDiMemPicIndex(data)                                      ((0x0000007F&(data))>>0)


#define MVDBLK_H264DI1                                                               0x1800e6e0
#define MVDBLK_H264DI1_reg_addr                                                      "0xB800E6E0"
#define MVDBLK_H264DI1_reg                                                           0xB800E6E0
#define set_MVDBLK_H264DI1_reg(data)   (*((volatile unsigned int*) MVDBLK_H264DI1_reg)=data)
#define get_MVDBLK_H264DI1_reg   (*((volatile unsigned int*) MVDBLK_H264DI1_reg))
#define MVDBLK_H264DI1_inst_adr                                                      "0x00B8"
#define MVDBLK_H264DI1_inst                                                          0x00B8
#define MVDBLK_H264DI1_StDiEnable_shift                                              (8)
#define MVDBLK_H264DI1_StDiEnable_mask                                               (0x00000100)
#define MVDBLK_H264DI1_StDiEnable(data)                                              (0x00000100&((data)<<8))
#define MVDBLK_H264DI1_StDiEnable_src(data)                                          ((0x00000100&(data))>>8)
#define MVDBLK_H264DI1_get_StDiEnable(data)                                          ((0x00000100&(data))>>8)
#define MVDBLK_H264DI1_StDiMvThres_shift                                             (0)
#define MVDBLK_H264DI1_StDiMvThres_mask                                              (0x000000FF)
#define MVDBLK_H264DI1_StDiMvThres(data)                                             (0x000000FF&((data)<<0))
#define MVDBLK_H264DI1_StDiMvThres_src(data)                                         ((0x000000FF&(data))>>0)
#define MVDBLK_H264DI1_get_StDiMvThres(data)                                         ((0x000000FF&(data))>>0)


#define MVDBLK_H264PX                                                                0x1800e620
#define MVDBLK_H264PX_reg_addr                                                       "0xB800E620"
#define MVDBLK_H264PX_reg                                                            0xB800E620
#define set_MVDBLK_H264PX_reg(data)   (*((volatile unsigned int*) MVDBLK_H264PX_reg)=data)
#define get_MVDBLK_H264PX_reg   (*((volatile unsigned int*) MVDBLK_H264PX_reg))
#define MVDBLK_H264PX_inst_adr                                                       "0x0088"
#define MVDBLK_H264PX_inst                                                           0x0088
#define MVDBLK_H264PX_List1Size_shift                                                (5)
#define MVDBLK_H264PX_List1Size_mask                                                 (0x000003E0)
#define MVDBLK_H264PX_List1Size(data)                                                (0x000003E0&((data)<<5))
#define MVDBLK_H264PX_List1Size_src(data)                                            ((0x000003E0&(data))>>5)
#define MVDBLK_H264PX_get_List1Size(data)                                            ((0x000003E0&(data))>>5)
#define MVDBLK_H264PX_List0Size_shift                                                (0)
#define MVDBLK_H264PX_List0Size_mask                                                 (0x0000001F)
#define MVDBLK_H264PX_List0Size(data)                                                (0x0000001F&((data)<<0))
#define MVDBLK_H264PX_List0Size_src(data)                                            ((0x0000001F&(data))>>0)
#define MVDBLK_H264PX_get_List0Size(data)                                            ((0x0000001F&(data))>>0)


#define MVDBLK_H264PX1                                                               0x1800e624
#define MVDBLK_H264PX1_reg_addr                                                      "0xB800E624"
#define MVDBLK_H264PX1_reg                                                           0xB800E624
#define set_MVDBLK_H264PX1_reg(data)   (*((volatile unsigned int*) MVDBLK_H264PX1_reg)=data)
#define get_MVDBLK_H264PX1_reg   (*((volatile unsigned int*) MVDBLK_H264PX1_reg))
#define MVDBLK_H264PX1_inst_adr                                                      "0x0089"
#define MVDBLK_H264PX1_inst                                                          0x0089
#define MVDBLK_H264PX1_FrmPocAddrL0_shift                                            (0)
#define MVDBLK_H264PX1_FrmPocAddrL0_mask                                             (0x0000FFFF)
#define MVDBLK_H264PX1_FrmPocAddrL0(data)                                            (0x0000FFFF&((data)<<0))
#define MVDBLK_H264PX1_FrmPocAddrL0_src(data)                                        ((0x0000FFFF&(data))>>0)
#define MVDBLK_H264PX1_get_FrmPocAddrL0(data)                                        ((0x0000FFFF&(data))>>0)


#define MVDBLK_H264PX2                                                               0x1800e628
#define MVDBLK_H264PX2_reg_addr                                                      "0xB800E628"
#define MVDBLK_H264PX2_reg                                                           0xB800E628
#define set_MVDBLK_H264PX2_reg(data)   (*((volatile unsigned int*) MVDBLK_H264PX2_reg)=data)
#define get_MVDBLK_H264PX2_reg   (*((volatile unsigned int*) MVDBLK_H264PX2_reg))
#define MVDBLK_H264PX2_inst_adr                                                      "0x008A"
#define MVDBLK_H264PX2_inst                                                          0x008A
#define MVDBLK_H264PX2_TopPocAddrL0_shift                                            (0)
#define MVDBLK_H264PX2_TopPocAddrL0_mask                                             (0x0000FFFF)
#define MVDBLK_H264PX2_TopPocAddrL0(data)                                            (0x0000FFFF&((data)<<0))
#define MVDBLK_H264PX2_TopPocAddrL0_src(data)                                        ((0x0000FFFF&(data))>>0)
#define MVDBLK_H264PX2_get_TopPocAddrL0(data)                                        ((0x0000FFFF&(data))>>0)


#define MVDBLK_H264PX3                                                               0x1800e62c
#define MVDBLK_H264PX3_reg_addr                                                      "0xB800E62C"
#define MVDBLK_H264PX3_reg                                                           0xB800E62C
#define set_MVDBLK_H264PX3_reg(data)   (*((volatile unsigned int*) MVDBLK_H264PX3_reg)=data)
#define get_MVDBLK_H264PX3_reg   (*((volatile unsigned int*) MVDBLK_H264PX3_reg))
#define MVDBLK_H264PX3_inst_adr                                                      "0x008B"
#define MVDBLK_H264PX3_inst                                                          0x008B
#define MVDBLK_H264PX3_BotPocAddrL0_shift                                            (0)
#define MVDBLK_H264PX3_BotPocAddrL0_mask                                             (0x0000FFFF)
#define MVDBLK_H264PX3_BotPocAddrL0(data)                                            (0x0000FFFF&((data)<<0))
#define MVDBLK_H264PX3_BotPocAddrL0_src(data)                                        ((0x0000FFFF&(data))>>0)
#define MVDBLK_H264PX3_get_BotPocAddrL0(data)                                        ((0x0000FFFF&(data))>>0)


#define MVDBLK_H264PX4                                                               0x1800e630
#define MVDBLK_H264PX4_reg_addr                                                      "0xB800E630"
#define MVDBLK_H264PX4_reg                                                           0xB800E630
#define set_MVDBLK_H264PX4_reg(data)   (*((volatile unsigned int*) MVDBLK_H264PX4_reg)=data)
#define get_MVDBLK_H264PX4_reg   (*((volatile unsigned int*) MVDBLK_H264PX4_reg))
#define MVDBLK_H264PX4_inst_adr                                                      "0x008C"
#define MVDBLK_H264PX4_inst                                                          0x008C
#define MVDBLK_H264PX4_FrmPocAddrL1_shift                                            (0)
#define MVDBLK_H264PX4_FrmPocAddrL1_mask                                             (0x0000FFFF)
#define MVDBLK_H264PX4_FrmPocAddrL1(data)                                            (0x0000FFFF&((data)<<0))
#define MVDBLK_H264PX4_FrmPocAddrL1_src(data)                                        ((0x0000FFFF&(data))>>0)
#define MVDBLK_H264PX4_get_FrmPocAddrL1(data)                                        ((0x0000FFFF&(data))>>0)


#define MVDBLK_H264PX5                                                               0x1800e634
#define MVDBLK_H264PX5_reg_addr                                                      "0xB800E634"
#define MVDBLK_H264PX5_reg                                                           0xB800E634
#define set_MVDBLK_H264PX5_reg(data)   (*((volatile unsigned int*) MVDBLK_H264PX5_reg)=data)
#define get_MVDBLK_H264PX5_reg   (*((volatile unsigned int*) MVDBLK_H264PX5_reg))
#define MVDBLK_H264PX5_inst_adr                                                      "0x008D"
#define MVDBLK_H264PX5_inst                                                          0x008D
#define MVDBLK_H264PX5_TopPocAddrL1_shift                                            (0)
#define MVDBLK_H264PX5_TopPocAddrL1_mask                                             (0x0000FFFF)
#define MVDBLK_H264PX5_TopPocAddrL1(data)                                            (0x0000FFFF&((data)<<0))
#define MVDBLK_H264PX5_TopPocAddrL1_src(data)                                        ((0x0000FFFF&(data))>>0)
#define MVDBLK_H264PX5_get_TopPocAddrL1(data)                                        ((0x0000FFFF&(data))>>0)


#define MVDBLK_H264PX6                                                               0x1800e638
#define MVDBLK_H264PX6_reg_addr                                                      "0xB800E638"
#define MVDBLK_H264PX6_reg                                                           0xB800E638
#define set_MVDBLK_H264PX6_reg(data)   (*((volatile unsigned int*) MVDBLK_H264PX6_reg)=data)
#define get_MVDBLK_H264PX6_reg   (*((volatile unsigned int*) MVDBLK_H264PX6_reg))
#define MVDBLK_H264PX6_inst_adr                                                      "0x008E"
#define MVDBLK_H264PX6_inst                                                          0x008E
#define MVDBLK_H264PX6_BotPocAddrL1_shift                                            (0)
#define MVDBLK_H264PX6_BotPocAddrL1_mask                                             (0x0000FFFF)
#define MVDBLK_H264PX6_BotPocAddrL1(data)                                            (0x0000FFFF&((data)<<0))
#define MVDBLK_H264PX6_BotPocAddrL1_src(data)                                        ((0x0000FFFF&(data))>>0)
#define MVDBLK_H264PX6_get_BotPocAddrL1(data)                                        ((0x0000FFFF&(data))>>0)


#define MVDBLK_H264PX7                                                               0x1800e63c
#define MVDBLK_H264PX7_reg_addr                                                      "0xB800E63C"
#define MVDBLK_H264PX7_reg                                                           0xB800E63C
#define set_MVDBLK_H264PX7_reg(data)   (*((volatile unsigned int*) MVDBLK_H264PX7_reg)=data)
#define get_MVDBLK_H264PX7_reg   (*((volatile unsigned int*) MVDBLK_H264PX7_reg))
#define MVDBLK_H264PX7_inst_adr                                                      "0x008F"
#define MVDBLK_H264PX7_inst                                                          0x008F
#define MVDBLK_H264PX7_PicInfoAddr_shift                                             (0)
#define MVDBLK_H264PX7_PicInfoAddr_mask                                              (0x0000FFFF)
#define MVDBLK_H264PX7_PicInfoAddr(data)                                             (0x0000FFFF&((data)<<0))
#define MVDBLK_H264PX7_PicInfoAddr_src(data)                                         ((0x0000FFFF&(data))>>0)
#define MVDBLK_H264PX7_get_PicInfoAddr(data)                                         ((0x0000FFFF&(data))>>0)


#define MVDBLK_VC1PIC                                                                0x1800e640
#define MVDBLK_VC1PIC_reg_addr                                                       "0xB800E640"
#define MVDBLK_VC1PIC_reg                                                            0xB800E640
#define set_MVDBLK_VC1PIC_reg(data)   (*((volatile unsigned int*) MVDBLK_VC1PIC_reg)=data)
#define get_MVDBLK_VC1PIC_reg   (*((volatile unsigned int*) MVDBLK_VC1PIC_reg))
#define MVDBLK_VC1PIC_inst_adr                                                       "0x0090"
#define MVDBLK_VC1PIC_inst                                                           0x0090
#define MVDBLK_VC1PIC_RefField_shift                                                 (12)
#define MVDBLK_VC1PIC_RefField_mask                                                  (0x00001000)
#define MVDBLK_VC1PIC_RefField(data)                                                 (0x00001000&((data)<<12))
#define MVDBLK_VC1PIC_RefField_src(data)                                             ((0x00001000&(data))>>12)
#define MVDBLK_VC1PIC_get_RefField(data)                                             ((0x00001000&(data))>>12)
#define MVDBLK_VC1PIC_FastUVmc_shift                                                 (11)
#define MVDBLK_VC1PIC_FastUVmc_mask                                                  (0x00000800)
#define MVDBLK_VC1PIC_FastUVmc(data)                                                 (0x00000800&((data)<<11))
#define MVDBLK_VC1PIC_FastUVmc_src(data)                                             ((0x00000800&(data))>>11)
#define MVDBLK_VC1PIC_get_FastUVmc(data)                                             ((0x00000800&(data))>>11)
#define MVDBLK_VC1PIC_ScaleFactor_shift                                              (0)
#define MVDBLK_VC1PIC_ScaleFactor_mask                                               (0x000007FF)
#define MVDBLK_VC1PIC_ScaleFactor(data)                                              (0x000007FF&((data)<<0))
#define MVDBLK_VC1PIC_ScaleFactor_src(data)                                          ((0x000007FF&(data))>>0)
#define MVDBLK_VC1PIC_get_ScaleFactor(data)                                          ((0x000007FF&(data))>>0)


#define MVDBLK_VC1PIC1                                                               0x1800e644
#define MVDBLK_VC1PIC1_reg_addr                                                      "0xB800E644"
#define MVDBLK_VC1PIC1_reg                                                           0xB800E644
#define set_MVDBLK_VC1PIC1_reg(data)   (*((volatile unsigned int*) MVDBLK_VC1PIC1_reg)=data)
#define get_MVDBLK_VC1PIC1_reg   (*((volatile unsigned int*) MVDBLK_VC1PIC1_reg))
#define MVDBLK_VC1PIC1_inst_adr                                                      "0x0091"
#define MVDBLK_VC1PIC1_inst                                                          0x0091
#define MVDBLK_VC1PIC1_Scale_fw_shift                                                (20)
#define MVDBLK_VC1PIC1_Scale_fw_mask                                                 (0x0FF00000)
#define MVDBLK_VC1PIC1_Scale_fw(data)                                                (0x0FF00000&((data)<<20))
#define MVDBLK_VC1PIC1_Scale_fw_src(data)                                            ((0x0FF00000&(data))>>20)
#define MVDBLK_VC1PIC1_get_Scale_fw(data)                                            ((0x0FF00000&(data))>>20)
#define MVDBLK_VC1PIC1_Scale1_fw_shift                                               (8)
#define MVDBLK_VC1PIC1_Scale1_fw_mask                                                (0x000FFF00)
#define MVDBLK_VC1PIC1_Scale1_fw(data)                                               (0x000FFF00&((data)<<8))
#define MVDBLK_VC1PIC1_Scale1_fw_src(data)                                           ((0x000FFF00&(data))>>8)
#define MVDBLK_VC1PIC1_get_Scale1_fw(data)                                           ((0x000FFF00&(data))>>8)
#define MVDBLK_VC1PIC1_Scale2_fw_shift                                               (0)
#define MVDBLK_VC1PIC1_Scale2_fw_mask                                                (0x000000FF)
#define MVDBLK_VC1PIC1_Scale2_fw(data)                                               (0x000000FF&((data)<<0))
#define MVDBLK_VC1PIC1_Scale2_fw_src(data)                                           ((0x000000FF&(data))>>0)
#define MVDBLK_VC1PIC1_get_Scale2_fw(data)                                           ((0x000000FF&(data))>>0)


#define MVDBLK_VC1PIC2                                                               0x1800e648
#define MVDBLK_VC1PIC2_reg_addr                                                      "0xB800E648"
#define MVDBLK_VC1PIC2_reg                                                           0xB800E648
#define set_MVDBLK_VC1PIC2_reg(data)   (*((volatile unsigned int*) MVDBLK_VC1PIC2_reg)=data)
#define get_MVDBLK_VC1PIC2_reg   (*((volatile unsigned int*) MVDBLK_VC1PIC2_reg))
#define MVDBLK_VC1PIC2_inst_adr                                                      "0x0092"
#define MVDBLK_VC1PIC2_inst                                                          0x0092
#define MVDBLK_VC1PIC2_ScaleUpOpp_fw_shift                                           (20)
#define MVDBLK_VC1PIC2_ScaleUpOpp_fw_mask                                            (0x00100000)
#define MVDBLK_VC1PIC2_ScaleUpOpp_fw(data)                                           (0x00100000&((data)<<20))
#define MVDBLK_VC1PIC2_ScaleUpOpp_fw_src(data)                                       ((0x00100000&(data))>>20)
#define MVDBLK_VC1PIC2_get_ScaleUpOpp_fw(data)                                       ((0x00100000&(data))>>20)
#define MVDBLK_VC1PIC2_ScaleZone1X_fw_shift                                          (14)
#define MVDBLK_VC1PIC2_ScaleZone1X_fw_mask                                           (0x000FC000)
#define MVDBLK_VC1PIC2_ScaleZone1X_fw(data)                                          (0x000FC000&((data)<<14))
#define MVDBLK_VC1PIC2_ScaleZone1X_fw_src(data)                                      ((0x000FC000&(data))>>14)
#define MVDBLK_VC1PIC2_get_ScaleZone1X_fw(data)                                      ((0x000FC000&(data))>>14)
#define MVDBLK_VC1PIC2_ScaleZone1Y_fw_shift                                          (10)
#define MVDBLK_VC1PIC2_ScaleZone1Y_fw_mask                                           (0x00003C00)
#define MVDBLK_VC1PIC2_ScaleZone1Y_fw(data)                                          (0x00003C00&((data)<<10))
#define MVDBLK_VC1PIC2_ScaleZone1Y_fw_src(data)                                      ((0x00003C00&(data))>>10)
#define MVDBLK_VC1PIC2_get_ScaleZone1Y_fw(data)                                      ((0x00003C00&(data))>>10)
#define MVDBLK_VC1PIC2_Zone1OffsetX_fw_shift                                         (4)
#define MVDBLK_VC1PIC2_Zone1OffsetX_fw_mask                                          (0x000003F0)
#define MVDBLK_VC1PIC2_Zone1OffsetX_fw(data)                                         (0x000003F0&((data)<<4))
#define MVDBLK_VC1PIC2_Zone1OffsetX_fw_src(data)                                     ((0x000003F0&(data))>>4)
#define MVDBLK_VC1PIC2_get_Zone1OffsetX_fw(data)                                     ((0x000003F0&(data))>>4)
#define MVDBLK_VC1PIC2_Zone1OffsetY_fw_shift                                         (0)
#define MVDBLK_VC1PIC2_Zone1OffsetY_fw_mask                                          (0x0000000F)
#define MVDBLK_VC1PIC2_Zone1OffsetY_fw(data)                                         (0x0000000F&((data)<<0))
#define MVDBLK_VC1PIC2_Zone1OffsetY_fw_src(data)                                     ((0x0000000F&(data))>>0)
#define MVDBLK_VC1PIC2_get_Zone1OffsetY_fw(data)                                     ((0x0000000F&(data))>>0)


#define MVDBLK_VC1PIC3                                                               0x1800e64c
#define MVDBLK_VC1PIC3_reg_addr                                                      "0xB800E64C"
#define MVDBLK_VC1PIC3_reg                                                           0xB800E64C
#define set_MVDBLK_VC1PIC3_reg(data)   (*((volatile unsigned int*) MVDBLK_VC1PIC3_reg)=data)
#define get_MVDBLK_VC1PIC3_reg   (*((volatile unsigned int*) MVDBLK_VC1PIC3_reg))
#define MVDBLK_VC1PIC3_inst_adr                                                      "0x0093"
#define MVDBLK_VC1PIC3_inst                                                          0x0093
#define MVDBLK_VC1PIC3_Scale_bw_shift                                                (20)
#define MVDBLK_VC1PIC3_Scale_bw_mask                                                 (0x0FF00000)
#define MVDBLK_VC1PIC3_Scale_bw(data)                                                (0x0FF00000&((data)<<20))
#define MVDBLK_VC1PIC3_Scale_bw_src(data)                                            ((0x0FF00000&(data))>>20)
#define MVDBLK_VC1PIC3_get_Scale_bw(data)                                            ((0x0FF00000&(data))>>20)
#define MVDBLK_VC1PIC3_Scale1_bw_shift                                               (8)
#define MVDBLK_VC1PIC3_Scale1_bw_mask                                                (0x000FFF00)
#define MVDBLK_VC1PIC3_Scale1_bw(data)                                               (0x000FFF00&((data)<<8))
#define MVDBLK_VC1PIC3_Scale1_bw_src(data)                                           ((0x000FFF00&(data))>>8)
#define MVDBLK_VC1PIC3_get_Scale1_bw(data)                                           ((0x000FFF00&(data))>>8)
#define MVDBLK_VC1PIC3_Scale2_bw_shift                                               (0)
#define MVDBLK_VC1PIC3_Scale2_bw_mask                                                (0x000000FF)
#define MVDBLK_VC1PIC3_Scale2_bw(data)                                               (0x000000FF&((data)<<0))
#define MVDBLK_VC1PIC3_Scale2_bw_src(data)                                           ((0x000000FF&(data))>>0)
#define MVDBLK_VC1PIC3_get_Scale2_bw(data)                                           ((0x000000FF&(data))>>0)


#define MVDBLK_VC1PIC4                                                               0x1800e650
#define MVDBLK_VC1PIC4_reg_addr                                                      "0xB800E650"
#define MVDBLK_VC1PIC4_reg                                                           0xB800E650
#define set_MVDBLK_VC1PIC4_reg(data)   (*((volatile unsigned int*) MVDBLK_VC1PIC4_reg)=data)
#define get_MVDBLK_VC1PIC4_reg   (*((volatile unsigned int*) MVDBLK_VC1PIC4_reg))
#define MVDBLK_VC1PIC4_inst_adr                                                      "0x0094"
#define MVDBLK_VC1PIC4_inst                                                          0x0094
#define MVDBLK_VC1PIC4_ScaleUpOpp_bw_shift                                           (20)
#define MVDBLK_VC1PIC4_ScaleUpOpp_bw_mask                                            (0x00100000)
#define MVDBLK_VC1PIC4_ScaleUpOpp_bw(data)                                           (0x00100000&((data)<<20))
#define MVDBLK_VC1PIC4_ScaleUpOpp_bw_src(data)                                       ((0x00100000&(data))>>20)
#define MVDBLK_VC1PIC4_get_ScaleUpOpp_bw(data)                                       ((0x00100000&(data))>>20)
#define MVDBLK_VC1PIC4_ScaleZone1X_bw_shift                                          (14)
#define MVDBLK_VC1PIC4_ScaleZone1X_bw_mask                                           (0x000FC000)
#define MVDBLK_VC1PIC4_ScaleZone1X_bw(data)                                          (0x000FC000&((data)<<14))
#define MVDBLK_VC1PIC4_ScaleZone1X_bw_src(data)                                      ((0x000FC000&(data))>>14)
#define MVDBLK_VC1PIC4_get_ScaleZone1X_bw(data)                                      ((0x000FC000&(data))>>14)
#define MVDBLK_VC1PIC4_ScaleZone1Y_bw_shift                                          (10)
#define MVDBLK_VC1PIC4_ScaleZone1Y_bw_mask                                           (0x00003C00)
#define MVDBLK_VC1PIC4_ScaleZone1Y_bw(data)                                          (0x00003C00&((data)<<10))
#define MVDBLK_VC1PIC4_ScaleZone1Y_bw_src(data)                                      ((0x00003C00&(data))>>10)
#define MVDBLK_VC1PIC4_get_ScaleZone1Y_bw(data)                                      ((0x00003C00&(data))>>10)
#define MVDBLK_VC1PIC4_Zone1OffsetX_bw_shift                                         (4)
#define MVDBLK_VC1PIC4_Zone1OffsetX_bw_mask                                          (0x000003F0)
#define MVDBLK_VC1PIC4_Zone1OffsetX_bw(data)                                         (0x000003F0&((data)<<4))
#define MVDBLK_VC1PIC4_Zone1OffsetX_bw_src(data)                                     ((0x000003F0&(data))>>4)
#define MVDBLK_VC1PIC4_get_Zone1OffsetX_bw(data)                                     ((0x000003F0&(data))>>4)
#define MVDBLK_VC1PIC4_Zone1OffsetY_bw_shift                                         (0)
#define MVDBLK_VC1PIC4_Zone1OffsetY_bw_mask                                          (0x0000000F)
#define MVDBLK_VC1PIC4_Zone1OffsetY_bw(data)                                         (0x0000000F&((data)<<0))
#define MVDBLK_VC1PIC4_Zone1OffsetY_bw_src(data)                                     ((0x0000000F&(data))>>0)
#define MVDBLK_VC1PIC4_get_Zone1OffsetY_bw(data)                                     ((0x0000000F&(data))>>0)


#define MVDBLK_VC1PIC5                                                               0x1800e654
#define MVDBLK_VC1PIC5_reg_addr                                                      "0xB800E654"
#define MVDBLK_VC1PIC5_reg                                                           0xB800E654
#define set_MVDBLK_VC1PIC5_reg(data)   (*((volatile unsigned int*) MVDBLK_VC1PIC5_reg)=data)
#define get_MVDBLK_VC1PIC5_reg   (*((volatile unsigned int*) MVDBLK_VC1PIC5_reg))
#define MVDBLK_VC1PIC5_inst_adr                                                      "0x0095"
#define MVDBLK_VC1PIC5_inst                                                          0x0095
#define MVDBLK_VC1PIC5_RangeY_shift                                                  (13)
#define MVDBLK_VC1PIC5_RangeY_mask                                                   (0x01FFE000)
#define MVDBLK_VC1PIC5_RangeY(data)                                                  (0x01FFE000&((data)<<13))
#define MVDBLK_VC1PIC5_RangeY_src(data)                                              ((0x01FFE000&(data))>>13)
#define MVDBLK_VC1PIC5_get_RangeY(data)                                              ((0x01FFE000&(data))>>13)
#define MVDBLK_VC1PIC5_RangeX_shift                                                  (0)
#define MVDBLK_VC1PIC5_RangeX_mask                                                   (0x00001FFF)
#define MVDBLK_VC1PIC5_RangeX(data)                                                  (0x00001FFF&((data)<<0))
#define MVDBLK_VC1PIC5_RangeX_src(data)                                              ((0x00001FFF&(data))>>0)
#define MVDBLK_VC1PIC5_get_RangeX(data)                                              ((0x00001FFF&(data))>>0)


#define MVDBLK_AVSPIC                                                                0x1800e7d0
#define MVDBLK_AVSPIC_reg_addr                                                       "0xB800E7D0"
#define MVDBLK_AVSPIC_reg                                                            0xB800E7D0
#define set_MVDBLK_AVSPIC_reg(data)   (*((volatile unsigned int*) MVDBLK_AVSPIC_reg)=data)
#define get_MVDBLK_AVSPIC_reg   (*((volatile unsigned int*) MVDBLK_AVSPIC_reg))
#define MVDBLK_AVSPIC_inst_adr                                                       "0x00F4"
#define MVDBLK_AVSPIC_inst                                                           0x00F4
#define MVDBLK_AVSPIC_AecEnable_shift                                                (4)
#define MVDBLK_AVSPIC_AecEnable_mask                                                 (0x00000010)
#define MVDBLK_AVSPIC_AecEnable(data)                                                (0x00000010&((data)<<4))
#define MVDBLK_AVSPIC_AecEnable_src(data)                                            ((0x00000010&(data))>>4)
#define MVDBLK_AVSPIC_get_AecEnable(data)                                            ((0x00000010&(data))>>4)
#define MVDBLK_AVSPIC_PFieldSkip_shift                                               (3)
#define MVDBLK_AVSPIC_PFieldSkip_mask                                                (0x00000008)
#define MVDBLK_AVSPIC_PFieldSkip(data)                                               (0x00000008&((data)<<3))
#define MVDBLK_AVSPIC_PFieldSkip_src(data)                                           ((0x00000008&(data))>>3)
#define MVDBLK_AVSPIC_get_PFieldSkip(data)                                           ((0x00000008&(data))>>3)
#define MVDBLK_AVSPIC_BFieldEnhanced_shift                                           (2)
#define MVDBLK_AVSPIC_BFieldEnhanced_mask                                            (0x00000004)
#define MVDBLK_AVSPIC_BFieldEnhanced(data)                                           (0x00000004&((data)<<2))
#define MVDBLK_AVSPIC_BFieldEnhanced_src(data)                                       ((0x00000004&(data))>>2)
#define MVDBLK_AVSPIC_get_BFieldEnhanced(data)                                       ((0x00000004&(data))>>2)
#define MVDBLK_AVSPIC_PicRefFlag_shift                                               (1)
#define MVDBLK_AVSPIC_PicRefFlag_mask                                                (0x00000002)
#define MVDBLK_AVSPIC_PicRefFlag(data)                                               (0x00000002&((data)<<1))
#define MVDBLK_AVSPIC_PicRefFlag_src(data)                                           ((0x00000002&(data))>>1)
#define MVDBLK_AVSPIC_get_PicRefFlag(data)                                           ((0x00000002&(data))>>1)
#define MVDBLK_AVSPIC_PicStructure_shift                                             (0)
#define MVDBLK_AVSPIC_PicStructure_mask                                              (0x00000001)
#define MVDBLK_AVSPIC_PicStructure(data)                                             (0x00000001&((data)<<0))
#define MVDBLK_AVSPIC_PicStructure_src(data)                                         ((0x00000001&(data))>>0)
#define MVDBLK_AVSPIC_get_PicStructure(data)                                         ((0x00000001&(data))>>0)


#define MVDBLK_AVSPIC1                                                               0x1800e7d4
#define MVDBLK_AVSPIC1_reg_addr                                                      "0xB800E7D4"
#define MVDBLK_AVSPIC1_reg                                                           0xB800E7D4
#define set_MVDBLK_AVSPIC1_reg(data)   (*((volatile unsigned int*) MVDBLK_AVSPIC1_reg)=data)
#define get_MVDBLK_AVSPIC1_reg   (*((volatile unsigned int*) MVDBLK_AVSPIC1_reg))
#define MVDBLK_AVSPIC1_inst_adr                                                      "0x00F5"
#define MVDBLK_AVSPIC1_inst                                                          0x00F5
#define MVDBLK_AVSPIC1_BlockDist0_shift                                              (16)
#define MVDBLK_AVSPIC1_BlockDist0_mask                                               (0x01FF0000)
#define MVDBLK_AVSPIC1_BlockDist0(data)                                              (0x01FF0000&((data)<<16))
#define MVDBLK_AVSPIC1_BlockDist0_src(data)                                          ((0x01FF0000&(data))>>16)
#define MVDBLK_AVSPIC1_get_BlockDist0(data)                                          ((0x01FF0000&(data))>>16)
#define MVDBLK_AVSPIC1_BlockDist1_shift                                              (0)
#define MVDBLK_AVSPIC1_BlockDist1_mask                                               (0x000001FF)
#define MVDBLK_AVSPIC1_BlockDist1(data)                                              (0x000001FF&((data)<<0))
#define MVDBLK_AVSPIC1_BlockDist1_src(data)                                          ((0x000001FF&(data))>>0)
#define MVDBLK_AVSPIC1_get_BlockDist1(data)                                          ((0x000001FF&(data))>>0)


#define MVDBLK_AVSPIC2                                                               0x1800e7d8
#define MVDBLK_AVSPIC2_reg_addr                                                      "0xB800E7D8"
#define MVDBLK_AVSPIC2_reg                                                           0xB800E7D8
#define set_MVDBLK_AVSPIC2_reg(data)   (*((volatile unsigned int*) MVDBLK_AVSPIC2_reg)=data)
#define get_MVDBLK_AVSPIC2_reg   (*((volatile unsigned int*) MVDBLK_AVSPIC2_reg))
#define MVDBLK_AVSPIC2_inst_adr                                                      "0x00F6"
#define MVDBLK_AVSPIC2_inst                                                          0x00F6
#define MVDBLK_AVSPIC2_BlockDist2_shift                                              (16)
#define MVDBLK_AVSPIC2_BlockDist2_mask                                               (0x01FF0000)
#define MVDBLK_AVSPIC2_BlockDist2(data)                                              (0x01FF0000&((data)<<16))
#define MVDBLK_AVSPIC2_BlockDist2_src(data)                                          ((0x01FF0000&(data))>>16)
#define MVDBLK_AVSPIC2_get_BlockDist2(data)                                          ((0x01FF0000&(data))>>16)
#define MVDBLK_AVSPIC2_BlockDist3_shift                                              (0)
#define MVDBLK_AVSPIC2_BlockDist3_mask                                               (0x000001FF)
#define MVDBLK_AVSPIC2_BlockDist3(data)                                              (0x000001FF&((data)<<0))
#define MVDBLK_AVSPIC2_BlockDist3_src(data)                                          ((0x000001FF&(data))>>0)
#define MVDBLK_AVSPIC2_get_BlockDist3(data)                                          ((0x000001FF&(data))>>0)


#define MVDBLK_AVSPIC3                                                               0x1800e7dc
#define MVDBLK_AVSPIC3_reg_addr                                                      "0xB800E7DC"
#define MVDBLK_AVSPIC3_reg                                                           0xB800E7DC
#define set_MVDBLK_AVSPIC3_reg(data)   (*((volatile unsigned int*) MVDBLK_AVSPIC3_reg)=data)
#define get_MVDBLK_AVSPIC3_reg   (*((volatile unsigned int*) MVDBLK_AVSPIC3_reg))
#define MVDBLK_AVSPIC3_inst_adr                                                      "0x00F7"
#define MVDBLK_AVSPIC3_inst                                                          0x00F7
#define MVDBLK_AVSPIC3_B16384DiviTRp0_shift                                          (16)
#define MVDBLK_AVSPIC3_B16384DiviTRp0_mask                                           (0xFFFF0000)
#define MVDBLK_AVSPIC3_B16384DiviTRp0(data)                                          (0xFFFF0000&((data)<<16))
#define MVDBLK_AVSPIC3_B16384DiviTRp0_src(data)                                      ((0xFFFF0000&(data))>>16)
#define MVDBLK_AVSPIC3_get_B16384DiviTRp0(data)                                      ((0xFFFF0000&(data))>>16)
#define MVDBLK_AVSPIC3_B16384DiviTRp1_shift                                          (0)
#define MVDBLK_AVSPIC3_B16384DiviTRp1_mask                                           (0x0000FFFF)
#define MVDBLK_AVSPIC3_B16384DiviTRp1(data)                                          (0x0000FFFF&((data)<<0))
#define MVDBLK_AVSPIC3_B16384DiviTRp1_src(data)                                      ((0x0000FFFF&(data))>>0)
#define MVDBLK_AVSPIC3_get_B16384DiviTRp1(data)                                      ((0x0000FFFF&(data))>>0)


#define MVDBLK_AVSPIC4                                                               0x1800e7e0
#define MVDBLK_AVSPIC4_reg_addr                                                      "0xB800E7E0"
#define MVDBLK_AVSPIC4_reg                                                           0xB800E7E0
#define set_MVDBLK_AVSPIC4_reg(data)   (*((volatile unsigned int*) MVDBLK_AVSPIC4_reg)=data)
#define get_MVDBLK_AVSPIC4_reg   (*((volatile unsigned int*) MVDBLK_AVSPIC4_reg))
#define MVDBLK_AVSPIC4_inst_adr                                                      "0x00F8"
#define MVDBLK_AVSPIC4_inst                                                          0x00F8
#define MVDBLK_AVSPIC4_B16384DiviTRp2_shift                                          (16)
#define MVDBLK_AVSPIC4_B16384DiviTRp2_mask                                           (0xFFFF0000)
#define MVDBLK_AVSPIC4_B16384DiviTRp2(data)                                          (0xFFFF0000&((data)<<16))
#define MVDBLK_AVSPIC4_B16384DiviTRp2_src(data)                                      ((0xFFFF0000&(data))>>16)
#define MVDBLK_AVSPIC4_get_B16384DiviTRp2(data)                                      ((0xFFFF0000&(data))>>16)
#define MVDBLK_AVSPIC4_B16384DiviTRp3_shift                                          (0)
#define MVDBLK_AVSPIC4_B16384DiviTRp3_mask                                           (0x0000FFFF)
#define MVDBLK_AVSPIC4_B16384DiviTRp3(data)                                          (0x0000FFFF&((data)<<0))
#define MVDBLK_AVSPIC4_B16384DiviTRp3_src(data)                                      ((0x0000FFFF&(data))>>0)
#define MVDBLK_AVSPIC4_get_B16384DiviTRp3(data)                                      ((0x0000FFFF&(data))>>0)


#define MVDBLK_AVSPIC5                                                               0x1800e7e4
#define MVDBLK_AVSPIC5_reg_addr                                                      "0xB800E7E4"
#define MVDBLK_AVSPIC5_reg                                                           0xB800E7E4
#define set_MVDBLK_AVSPIC5_reg(data)   (*((volatile unsigned int*) MVDBLK_AVSPIC5_reg)=data)
#define get_MVDBLK_AVSPIC5_reg   (*((volatile unsigned int*) MVDBLK_AVSPIC5_reg))
#define MVDBLK_AVSPIC5_inst_adr                                                      "0x00F9"
#define MVDBLK_AVSPIC5_inst                                                          0x00F9
#define MVDBLK_AVSPIC5_iTRb0_shift                                                   (16)
#define MVDBLK_AVSPIC5_iTRb0_mask                                                    (0x01FF0000)
#define MVDBLK_AVSPIC5_iTRb0(data)                                                   (0x01FF0000&((data)<<16))
#define MVDBLK_AVSPIC5_iTRb0_src(data)                                               ((0x01FF0000&(data))>>16)
#define MVDBLK_AVSPIC5_get_iTRb0(data)                                               ((0x01FF0000&(data))>>16)
#define MVDBLK_AVSPIC5_iTRb1_shift                                                   (0)
#define MVDBLK_AVSPIC5_iTRb1_mask                                                    (0x000001FF)
#define MVDBLK_AVSPIC5_iTRb1(data)                                                   (0x000001FF&((data)<<0))
#define MVDBLK_AVSPIC5_iTRb1_src(data)                                               ((0x000001FF&(data))>>0)
#define MVDBLK_AVSPIC5_get_iTRb1(data)                                               ((0x000001FF&(data))>>0)


#define MVDBLK_AVSPIC6                                                               0x1800e7e8
#define MVDBLK_AVSPIC6_reg_addr                                                      "0xB800E7E8"
#define MVDBLK_AVSPIC6_reg                                                           0xB800E7E8
#define set_MVDBLK_AVSPIC6_reg(data)   (*((volatile unsigned int*) MVDBLK_AVSPIC6_reg)=data)
#define get_MVDBLK_AVSPIC6_reg   (*((volatile unsigned int*) MVDBLK_AVSPIC6_reg))
#define MVDBLK_AVSPIC6_inst_adr                                                      "0x00FA"
#define MVDBLK_AVSPIC6_inst                                                          0x00FA
#define MVDBLK_AVSPIC6_iTRb2_shift                                                   (16)
#define MVDBLK_AVSPIC6_iTRb2_mask                                                    (0x01FF0000)
#define MVDBLK_AVSPIC6_iTRb2(data)                                                   (0x01FF0000&((data)<<16))
#define MVDBLK_AVSPIC6_iTRb2_src(data)                                               ((0x01FF0000&(data))>>16)
#define MVDBLK_AVSPIC6_get_iTRb2(data)                                               ((0x01FF0000&(data))>>16)
#define MVDBLK_AVSPIC6_iTRb3_shift                                                   (0)
#define MVDBLK_AVSPIC6_iTRb3_mask                                                    (0x000001FF)
#define MVDBLK_AVSPIC6_iTRb3(data)                                                   (0x000001FF&((data)<<0))
#define MVDBLK_AVSPIC6_iTRb3_src(data)                                               ((0x000001FF&(data))>>0)
#define MVDBLK_AVSPIC6_get_iTRb3(data)                                               ((0x000001FF&(data))>>0)


#define MVDBLK_AVSPIC7                                                               0x1800e7ec
#define MVDBLK_AVSPIC7_reg_addr                                                      "0xB800E7EC"
#define MVDBLK_AVSPIC7_reg                                                           0xB800E7EC
#define set_MVDBLK_AVSPIC7_reg(data)   (*((volatile unsigned int*) MVDBLK_AVSPIC7_reg)=data)
#define get_MVDBLK_AVSPIC7_reg   (*((volatile unsigned int*) MVDBLK_AVSPIC7_reg))
#define MVDBLK_AVSPIC7_inst_adr                                                      "0x00FB"
#define MVDBLK_AVSPIC7_inst                                                          0x00FB
#define MVDBLK_AVSPIC7_iTRd_shift                                                    (0)
#define MVDBLK_AVSPIC7_iTRd_mask                                                     (0x000001FF)
#define MVDBLK_AVSPIC7_iTRd(data)                                                    (0x000001FF&((data)<<0))
#define MVDBLK_AVSPIC7_iTRd_src(data)                                                ((0x000001FF&(data))>>0)
#define MVDBLK_AVSPIC7_get_iTRd(data)                                                ((0x000001FF&(data))>>0)


#define MVDBLK_RM89PIC                                                               0x1800e7c0
#define MVDBLK_RM89PIC_reg_addr                                                      "0xB800E7C0"
#define MVDBLK_RM89PIC_reg                                                           0xB800E7C0
#define set_MVDBLK_RM89PIC_reg(data)   (*((volatile unsigned int*) MVDBLK_RM89PIC_reg)=data)
#define get_MVDBLK_RM89PIC_reg   (*((volatile unsigned int*) MVDBLK_RM89PIC_reg))
#define MVDBLK_RM89PIC_inst_adr                                                      "0x00F0"
#define MVDBLK_RM89PIC_inst                                                          0x00F0
#define MVDBLK_RM89PIC_iRatio0_shift                                                 (0)
#define MVDBLK_RM89PIC_iRatio0_mask                                                  (0xFFFFFFFF)
#define MVDBLK_RM89PIC_iRatio0(data)                                                 (0xFFFFFFFF&((data)<<0))
#define MVDBLK_RM89PIC_iRatio0_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define MVDBLK_RM89PIC_get_iRatio0(data)                                             ((0xFFFFFFFF&(data))>>0)


#define MVDBLK_RM89PIC1                                                              0x1800e7c4
#define MVDBLK_RM89PIC1_reg_addr                                                     "0xB800E7C4"
#define MVDBLK_RM89PIC1_reg                                                          0xB800E7C4
#define set_MVDBLK_RM89PIC1_reg(data)   (*((volatile unsigned int*) MVDBLK_RM89PIC1_reg)=data)
#define get_MVDBLK_RM89PIC1_reg   (*((volatile unsigned int*) MVDBLK_RM89PIC1_reg))
#define MVDBLK_RM89PIC1_inst_adr                                                     "0x00F1"
#define MVDBLK_RM89PIC1_inst                                                         0x00F1
#define MVDBLK_RM89PIC1_iRatio1_shift                                                (0)
#define MVDBLK_RM89PIC1_iRatio1_mask                                                 (0xFFFFFFFF)
#define MVDBLK_RM89PIC1_iRatio1(data)                                                (0xFFFFFFFF&((data)<<0))
#define MVDBLK_RM89PIC1_iRatio1_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define MVDBLK_RM89PIC1_get_iRatio1(data)                                            ((0xFFFFFFFF&(data))>>0)


#define MVDBLK_RM89DIRECT                                                            0x1800e7c8
#define MVDBLK_RM89DIRECT_reg_addr                                                   "0xB800E7C8"
#define MVDBLK_RM89DIRECT_reg                                                        0xB800E7C8
#define set_MVDBLK_RM89DIRECT_reg(data)   (*((volatile unsigned int*) MVDBLK_RM89DIRECT_reg)=data)
#define get_MVDBLK_RM89DIRECT_reg   (*((volatile unsigned int*) MVDBLK_RM89DIRECT_reg))
#define MVDBLK_RM89DIRECT_inst_adr                                                   "0x00F2"
#define MVDBLK_RM89DIRECT_inst                                                       0x00F2
#define MVDBLK_RM89DIRECT_hix_shift                                                  (16)
#define MVDBLK_RM89DIRECT_hix_mask                                                   (0x3FFF0000)
#define MVDBLK_RM89DIRECT_hix(data)                                                  (0x3FFF0000&((data)<<16))
#define MVDBLK_RM89DIRECT_hix_src(data)                                              ((0x3FFF0000&(data))>>16)
#define MVDBLK_RM89DIRECT_get_hix(data)                                              ((0x3FFF0000&(data))>>16)
#define MVDBLK_RM89DIRECT_lox_shift                                                  (0)
#define MVDBLK_RM89DIRECT_lox_mask                                                   (0x00003FFF)
#define MVDBLK_RM89DIRECT_lox(data)                                                  (0x00003FFF&((data)<<0))
#define MVDBLK_RM89DIRECT_lox_src(data)                                              ((0x00003FFF&(data))>>0)
#define MVDBLK_RM89DIRECT_get_lox(data)                                              ((0x00003FFF&(data))>>0)


#define MVDBLK_RM89DIRECT1                                                           0x1800e7cc
#define MVDBLK_RM89DIRECT1_reg_addr                                                  "0xB800E7CC"
#define MVDBLK_RM89DIRECT1_reg                                                       0xB800E7CC
#define set_MVDBLK_RM89DIRECT1_reg(data)   (*((volatile unsigned int*) MVDBLK_RM89DIRECT1_reg)=data)
#define get_MVDBLK_RM89DIRECT1_reg   (*((volatile unsigned int*) MVDBLK_RM89DIRECT1_reg))
#define MVDBLK_RM89DIRECT1_inst_adr                                                  "0x00F3"
#define MVDBLK_RM89DIRECT1_inst                                                      0x00F3
#define MVDBLK_RM89DIRECT1_hiy_shift                                                 (16)
#define MVDBLK_RM89DIRECT1_hiy_mask                                                  (0x3FFF0000)
#define MVDBLK_RM89DIRECT1_hiy(data)                                                 (0x3FFF0000&((data)<<16))
#define MVDBLK_RM89DIRECT1_hiy_src(data)                                             ((0x3FFF0000&(data))>>16)
#define MVDBLK_RM89DIRECT1_get_hiy(data)                                             ((0x3FFF0000&(data))>>16)
#define MVDBLK_RM89DIRECT1_loy_shift                                                 (0)
#define MVDBLK_RM89DIRECT1_loy_mask                                                  (0x00003FFF)
#define MVDBLK_RM89DIRECT1_loy(data)                                                 (0x00003FFF&((data)<<0))
#define MVDBLK_RM89DIRECT1_loy_src(data)                                             ((0x00003FFF&(data))>>0)
#define MVDBLK_RM89DIRECT1_get_loy(data)                                             ((0x00003FFF&(data))>>0)


#define MVDBLK_RM89DIRECT2                                                           0x1800e7f0
#define MVDBLK_RM89DIRECT2_reg_addr                                                  "0xB800E7F0"
#define MVDBLK_RM89DIRECT2_reg                                                       0xB800E7F0
#define set_MVDBLK_RM89DIRECT2_reg(data)   (*((volatile unsigned int*) MVDBLK_RM89DIRECT2_reg)=data)
#define get_MVDBLK_RM89DIRECT2_reg   (*((volatile unsigned int*) MVDBLK_RM89DIRECT2_reg))
#define MVDBLK_RM89DIRECT2_inst_adr                                                  "0x00FC"
#define MVDBLK_RM89DIRECT2_inst                                                      0x00FC
#define MVDBLK_RM89DIRECT2_hicx_shift                                                (16)
#define MVDBLK_RM89DIRECT2_hicx_mask                                                 (0x3FFF0000)
#define MVDBLK_RM89DIRECT2_hicx(data)                                                (0x3FFF0000&((data)<<16))
#define MVDBLK_RM89DIRECT2_hicx_src(data)                                            ((0x3FFF0000&(data))>>16)
#define MVDBLK_RM89DIRECT2_get_hicx(data)                                            ((0x3FFF0000&(data))>>16)
#define MVDBLK_RM89DIRECT2_locx_shift                                                (0)
#define MVDBLK_RM89DIRECT2_locx_mask                                                 (0x00003FFF)
#define MVDBLK_RM89DIRECT2_locx(data)                                                (0x00003FFF&((data)<<0))
#define MVDBLK_RM89DIRECT2_locx_src(data)                                            ((0x00003FFF&(data))>>0)
#define MVDBLK_RM89DIRECT2_get_locx(data)                                            ((0x00003FFF&(data))>>0)


#define MVDBLK_RM89DIRECT3                                                           0x1800e7f4
#define MVDBLK_RM89DIRECT3_reg_addr                                                  "0xB800E7F4"
#define MVDBLK_RM89DIRECT3_reg                                                       0xB800E7F4
#define set_MVDBLK_RM89DIRECT3_reg(data)   (*((volatile unsigned int*) MVDBLK_RM89DIRECT3_reg)=data)
#define get_MVDBLK_RM89DIRECT3_reg   (*((volatile unsigned int*) MVDBLK_RM89DIRECT3_reg))
#define MVDBLK_RM89DIRECT3_inst_adr                                                  "0x00FD"
#define MVDBLK_RM89DIRECT3_inst                                                      0x00FD
#define MVDBLK_RM89DIRECT3_hicy_shift                                                (16)
#define MVDBLK_RM89DIRECT3_hicy_mask                                                 (0x3FFF0000)
#define MVDBLK_RM89DIRECT3_hicy(data)                                                (0x3FFF0000&((data)<<16))
#define MVDBLK_RM89DIRECT3_hicy_src(data)                                            ((0x3FFF0000&(data))>>16)
#define MVDBLK_RM89DIRECT3_get_hicy(data)                                            ((0x3FFF0000&(data))>>16)
#define MVDBLK_RM89DIRECT3_locy_shift                                                (0)
#define MVDBLK_RM89DIRECT3_locy_mask                                                 (0x00003FFF)
#define MVDBLK_RM89DIRECT3_locy(data)                                                (0x00003FFF&((data)<<0))
#define MVDBLK_RM89DIRECT3_locy_src(data)                                            ((0x00003FFF&(data))>>0)
#define MVDBLK_RM89DIRECT3_get_locy(data)                                            ((0x00003FFF&(data))>>0)


#define MVDBLK_RM89PIC2                                                              0x1800e7f8
#define MVDBLK_RM89PIC2_reg_addr                                                     "0xB800E7F8"
#define MVDBLK_RM89PIC2_reg                                                          0xB800E7F8
#define set_MVDBLK_RM89PIC2_reg(data)   (*((volatile unsigned int*) MVDBLK_RM89PIC2_reg)=data)
#define get_MVDBLK_RM89PIC2_reg   (*((volatile unsigned int*) MVDBLK_RM89PIC2_reg))
#define MVDBLK_RM89PIC2_inst_adr                                                     "0x00FE"
#define MVDBLK_RM89PIC2_inst                                                         0x00FE
#define MVDBLK_RM89PIC2_ZeroMvd_shift                                                (0)
#define MVDBLK_RM89PIC2_ZeroMvd_mask                                                 (0x00000001)
#define MVDBLK_RM89PIC2_ZeroMvd(data)                                                (0x00000001&((data)<<0))
#define MVDBLK_RM89PIC2_ZeroMvd_src(data)                                            ((0x00000001&(data))>>0)
#define MVDBLK_RM89PIC2_get_ZeroMvd(data)                                            ((0x00000001&(data))>>0)


#define MVDBLK_RM89DIRECT4                                                           0x1800e7fc
#define MVDBLK_RM89DIRECT4_reg_addr                                                  "0xB800E7FC"
#define MVDBLK_RM89DIRECT4_reg                                                       0xB800E7FC
#define set_MVDBLK_RM89DIRECT4_reg(data)   (*((volatile unsigned int*) MVDBLK_RM89DIRECT4_reg)=data)
#define get_MVDBLK_RM89DIRECT4_reg   (*((volatile unsigned int*) MVDBLK_RM89DIRECT4_reg))
#define MVDBLK_RM89DIRECT4_inst_adr                                                  "0x00FF"
#define MVDBLK_RM89DIRECT4_inst                                                      0x00FF
#define MVDBLK_RM89DIRECT4_hix_4v_shift                                              (16)
#define MVDBLK_RM89DIRECT4_hix_4v_mask                                               (0x3FFF0000)
#define MVDBLK_RM89DIRECT4_hix_4v(data)                                              (0x3FFF0000&((data)<<16))
#define MVDBLK_RM89DIRECT4_hix_4v_src(data)                                          ((0x3FFF0000&(data))>>16)
#define MVDBLK_RM89DIRECT4_get_hix_4v(data)                                          ((0x3FFF0000&(data))>>16)
#define MVDBLK_RM89DIRECT4_lox_4v_shift                                              (0)
#define MVDBLK_RM89DIRECT4_lox_4v_mask                                               (0x00003FFF)
#define MVDBLK_RM89DIRECT4_lox_4v(data)                                              (0x00003FFF&((data)<<0))
#define MVDBLK_RM89DIRECT4_lox_4v_src(data)                                          ((0x00003FFF&(data))>>0)
#define MVDBLK_RM89DIRECT4_get_lox_4v(data)                                          ((0x00003FFF&(data))>>0)


#define MVDBLK_RM89DIRECT5                                                           0x1800e6cc
#define MVDBLK_RM89DIRECT5_reg_addr                                                  "0xB800E6CC"
#define MVDBLK_RM89DIRECT5_reg                                                       0xB800E6CC
#define set_MVDBLK_RM89DIRECT5_reg(data)   (*((volatile unsigned int*) MVDBLK_RM89DIRECT5_reg)=data)
#define get_MVDBLK_RM89DIRECT5_reg   (*((volatile unsigned int*) MVDBLK_RM89DIRECT5_reg))
#define MVDBLK_RM89DIRECT5_inst_adr                                                  "0x00B3"
#define MVDBLK_RM89DIRECT5_inst                                                      0x00B3
#define MVDBLK_RM89DIRECT5_hiy_4v_shift                                              (16)
#define MVDBLK_RM89DIRECT5_hiy_4v_mask                                               (0x3FFF0000)
#define MVDBLK_RM89DIRECT5_hiy_4v(data)                                              (0x3FFF0000&((data)<<16))
#define MVDBLK_RM89DIRECT5_hiy_4v_src(data)                                          ((0x3FFF0000&(data))>>16)
#define MVDBLK_RM89DIRECT5_get_hiy_4v(data)                                          ((0x3FFF0000&(data))>>16)
#define MVDBLK_RM89DIRECT5_loy_4v_shift                                              (0)
#define MVDBLK_RM89DIRECT5_loy_4v_mask                                               (0x00003FFF)
#define MVDBLK_RM89DIRECT5_loy_4v(data)                                              (0x00003FFF&((data)<<0))
#define MVDBLK_RM89DIRECT5_loy_4v_src(data)                                          ((0x00003FFF&(data))>>0)
#define MVDBLK_RM89DIRECT5_get_loy_4v(data)                                          ((0x00003FFF&(data))>>0)


#define MVDBLK_RM89DIRECT6                                                           0x1800e658
#define MVDBLK_RM89DIRECT6_reg_addr                                                  "0xB800E658"
#define MVDBLK_RM89DIRECT6_reg                                                       0xB800E658
#define set_MVDBLK_RM89DIRECT6_reg(data)   (*((volatile unsigned int*) MVDBLK_RM89DIRECT6_reg)=data)
#define get_MVDBLK_RM89DIRECT6_reg   (*((volatile unsigned int*) MVDBLK_RM89DIRECT6_reg))
#define MVDBLK_RM89DIRECT6_inst_adr                                                  "0x0096"
#define MVDBLK_RM89DIRECT6_inst                                                      0x0096
#define MVDBLK_RM89DIRECT6_hicx_4v_shift                                             (16)
#define MVDBLK_RM89DIRECT6_hicx_4v_mask                                              (0x3FFF0000)
#define MVDBLK_RM89DIRECT6_hicx_4v(data)                                             (0x3FFF0000&((data)<<16))
#define MVDBLK_RM89DIRECT6_hicx_4v_src(data)                                         ((0x3FFF0000&(data))>>16)
#define MVDBLK_RM89DIRECT6_get_hicx_4v(data)                                         ((0x3FFF0000&(data))>>16)
#define MVDBLK_RM89DIRECT6_locx_4v_shift                                             (0)
#define MVDBLK_RM89DIRECT6_locx_4v_mask                                              (0x00003FFF)
#define MVDBLK_RM89DIRECT6_locx_4v(data)                                             (0x00003FFF&((data)<<0))
#define MVDBLK_RM89DIRECT6_locx_4v_src(data)                                         ((0x00003FFF&(data))>>0)
#define MVDBLK_RM89DIRECT6_get_locx_4v(data)                                         ((0x00003FFF&(data))>>0)


#define MVDBLK_RM89DIRECT7                                                           0x1800e65c
#define MVDBLK_RM89DIRECT7_reg_addr                                                  "0xB800E65C"
#define MVDBLK_RM89DIRECT7_reg                                                       0xB800E65C
#define set_MVDBLK_RM89DIRECT7_reg(data)   (*((volatile unsigned int*) MVDBLK_RM89DIRECT7_reg)=data)
#define get_MVDBLK_RM89DIRECT7_reg   (*((volatile unsigned int*) MVDBLK_RM89DIRECT7_reg))
#define MVDBLK_RM89DIRECT7_inst_adr                                                  "0x0097"
#define MVDBLK_RM89DIRECT7_inst                                                      0x0097
#define MVDBLK_RM89DIRECT7_hicy_4v_shift                                             (16)
#define MVDBLK_RM89DIRECT7_hicy_4v_mask                                              (0x3FFF0000)
#define MVDBLK_RM89DIRECT7_hicy_4v(data)                                             (0x3FFF0000&((data)<<16))
#define MVDBLK_RM89DIRECT7_hicy_4v_src(data)                                         ((0x3FFF0000&(data))>>16)
#define MVDBLK_RM89DIRECT7_get_hicy_4v(data)                                         ((0x3FFF0000&(data))>>16)
#define MVDBLK_RM89DIRECT7_locy_4v_shift                                             (0)
#define MVDBLK_RM89DIRECT7_locy_4v_mask                                              (0x00003FFF)
#define MVDBLK_RM89DIRECT7_locy_4v(data)                                             (0x00003FFF&((data)<<0))
#define MVDBLK_RM89DIRECT7_locy_4v_src(data)                                         ((0x00003FFF&(data))>>0)
#define MVDBLK_RM89DIRECT7_get_locy_4v(data)                                         ((0x00003FFF&(data))>>0)


#define MVDBLK_SEPOOL_0                                                              0x1800E700
#define MVDBLK_SEPOOL_1                                                              0x1800E704
#define MVDBLK_SEPOOL_2                                                              0x1800E708
#define MVDBLK_SEPOOL_3                                                              0x1800E70C
#define MVDBLK_SEPOOL_4                                                              0x1800E710
#define MVDBLK_SEPOOL_5                                                              0x1800E714
#define MVDBLK_SEPOOL_6                                                              0x1800E718
#define MVDBLK_SEPOOL_7                                                              0x1800E71C
#define MVDBLK_SEPOOL_8                                                              0x1800E720
#define MVDBLK_SEPOOL_9                                                              0x1800E724
#define MVDBLK_SEPOOL_10                                                              0x1800E728
#define MVDBLK_SEPOOL_11                                                              0x1800E72C
#define MVDBLK_SEPOOL_12                                                              0x1800E730
#define MVDBLK_SEPOOL_13                                                              0x1800E734
#define MVDBLK_SEPOOL_14                                                              0x1800E738
#define MVDBLK_SEPOOL_15                                                              0x1800E73C
#define MVDBLK_SEPOOL_0_reg_addr                                                     "0xB800E700"
#define MVDBLK_SEPOOL_1_reg_addr                                                     "0xB800E704"
#define MVDBLK_SEPOOL_2_reg_addr                                                     "0xB800E708"
#define MVDBLK_SEPOOL_3_reg_addr                                                     "0xB800E70C"
#define MVDBLK_SEPOOL_4_reg_addr                                                     "0xB800E710"
#define MVDBLK_SEPOOL_5_reg_addr                                                     "0xB800E714"
#define MVDBLK_SEPOOL_6_reg_addr                                                     "0xB800E718"
#define MVDBLK_SEPOOL_7_reg_addr                                                     "0xB800E71C"
#define MVDBLK_SEPOOL_8_reg_addr                                                     "0xB800E720"
#define MVDBLK_SEPOOL_9_reg_addr                                                     "0xB800E724"
#define MVDBLK_SEPOOL_10_reg_addr                                                     "0xB800E728"
#define MVDBLK_SEPOOL_11_reg_addr                                                     "0xB800E72C"
#define MVDBLK_SEPOOL_12_reg_addr                                                     "0xB800E730"
#define MVDBLK_SEPOOL_13_reg_addr                                                     "0xB800E734"
#define MVDBLK_SEPOOL_14_reg_addr                                                     "0xB800E738"
#define MVDBLK_SEPOOL_15_reg_addr                                                     "0xB800E73C"
#define MVDBLK_SEPOOL_0_reg                                                          0xB800E700
#define MVDBLK_SEPOOL_1_reg                                                          0xB800E704
#define MVDBLK_SEPOOL_2_reg                                                          0xB800E708
#define MVDBLK_SEPOOL_3_reg                                                          0xB800E70C
#define MVDBLK_SEPOOL_4_reg                                                          0xB800E710
#define MVDBLK_SEPOOL_5_reg                                                          0xB800E714
#define MVDBLK_SEPOOL_6_reg                                                          0xB800E718
#define MVDBLK_SEPOOL_7_reg                                                          0xB800E71C
#define MVDBLK_SEPOOL_8_reg                                                          0xB800E720
#define MVDBLK_SEPOOL_9_reg                                                          0xB800E724
#define MVDBLK_SEPOOL_10_reg                                                          0xB800E728
#define MVDBLK_SEPOOL_11_reg                                                          0xB800E72C
#define MVDBLK_SEPOOL_12_reg                                                          0xB800E730
#define MVDBLK_SEPOOL_13_reg                                                          0xB800E734
#define MVDBLK_SEPOOL_14_reg                                                          0xB800E738
#define MVDBLK_SEPOOL_15_reg                                                          0xB800E73C
#define set_MVDBLK_SEPOOL_0_reg(data)   (*((volatile unsigned int*) MVDBLK_SEPOOL_0_reg)=data)
#define set_MVDBLK_SEPOOL_1_reg(data)   (*((volatile unsigned int*) MVDBLK_SEPOOL_1_reg)=data)
#define set_MVDBLK_SEPOOL_2_reg(data)   (*((volatile unsigned int*) MVDBLK_SEPOOL_2_reg)=data)
#define set_MVDBLK_SEPOOL_3_reg(data)   (*((volatile unsigned int*) MVDBLK_SEPOOL_3_reg)=data)
#define set_MVDBLK_SEPOOL_4_reg(data)   (*((volatile unsigned int*) MVDBLK_SEPOOL_4_reg)=data)
#define set_MVDBLK_SEPOOL_5_reg(data)   (*((volatile unsigned int*) MVDBLK_SEPOOL_5_reg)=data)
#define set_MVDBLK_SEPOOL_6_reg(data)   (*((volatile unsigned int*) MVDBLK_SEPOOL_6_reg)=data)
#define set_MVDBLK_SEPOOL_7_reg(data)   (*((volatile unsigned int*) MVDBLK_SEPOOL_7_reg)=data)
#define set_MVDBLK_SEPOOL_8_reg(data)   (*((volatile unsigned int*) MVDBLK_SEPOOL_8_reg)=data)
#define set_MVDBLK_SEPOOL_9_reg(data)   (*((volatile unsigned int*) MVDBLK_SEPOOL_9_reg)=data)
#define set_MVDBLK_SEPOOL_10_reg(data)   (*((volatile unsigned int*) MVDBLK_SEPOOL_10_reg)=data)
#define set_MVDBLK_SEPOOL_11_reg(data)   (*((volatile unsigned int*) MVDBLK_SEPOOL_11_reg)=data)
#define set_MVDBLK_SEPOOL_12_reg(data)   (*((volatile unsigned int*) MVDBLK_SEPOOL_12_reg)=data)
#define set_MVDBLK_SEPOOL_13_reg(data)   (*((volatile unsigned int*) MVDBLK_SEPOOL_13_reg)=data)
#define set_MVDBLK_SEPOOL_14_reg(data)   (*((volatile unsigned int*) MVDBLK_SEPOOL_14_reg)=data)
#define set_MVDBLK_SEPOOL_15_reg(data)   (*((volatile unsigned int*) MVDBLK_SEPOOL_15_reg)=data)
#define get_MVDBLK_SEPOOL_0_reg   (*((volatile unsigned int*) MVDBLK_SEPOOL_0_reg))
#define get_MVDBLK_SEPOOL_1_reg   (*((volatile unsigned int*) MVDBLK_SEPOOL_1_reg))
#define get_MVDBLK_SEPOOL_2_reg   (*((volatile unsigned int*) MVDBLK_SEPOOL_2_reg))
#define get_MVDBLK_SEPOOL_3_reg   (*((volatile unsigned int*) MVDBLK_SEPOOL_3_reg))
#define get_MVDBLK_SEPOOL_4_reg   (*((volatile unsigned int*) MVDBLK_SEPOOL_4_reg))
#define get_MVDBLK_SEPOOL_5_reg   (*((volatile unsigned int*) MVDBLK_SEPOOL_5_reg))
#define get_MVDBLK_SEPOOL_6_reg   (*((volatile unsigned int*) MVDBLK_SEPOOL_6_reg))
#define get_MVDBLK_SEPOOL_7_reg   (*((volatile unsigned int*) MVDBLK_SEPOOL_7_reg))
#define get_MVDBLK_SEPOOL_8_reg   (*((volatile unsigned int*) MVDBLK_SEPOOL_8_reg))
#define get_MVDBLK_SEPOOL_9_reg   (*((volatile unsigned int*) MVDBLK_SEPOOL_9_reg))
#define get_MVDBLK_SEPOOL_10_reg   (*((volatile unsigned int*) MVDBLK_SEPOOL_10_reg))
#define get_MVDBLK_SEPOOL_11_reg   (*((volatile unsigned int*) MVDBLK_SEPOOL_11_reg))
#define get_MVDBLK_SEPOOL_12_reg   (*((volatile unsigned int*) MVDBLK_SEPOOL_12_reg))
#define get_MVDBLK_SEPOOL_13_reg   (*((volatile unsigned int*) MVDBLK_SEPOOL_13_reg))
#define get_MVDBLK_SEPOOL_14_reg   (*((volatile unsigned int*) MVDBLK_SEPOOL_14_reg))
#define get_MVDBLK_SEPOOL_15_reg   (*((volatile unsigned int*) MVDBLK_SEPOOL_15_reg))
#define MVDBLK_SEPOOL_0_inst_adr                                                     "0x00C0"
#define MVDBLK_SEPOOL_1_inst_adr                                                     "0x00C1"
#define MVDBLK_SEPOOL_2_inst_adr                                                     "0x00C2"
#define MVDBLK_SEPOOL_3_inst_adr                                                     "0x00C3"
#define MVDBLK_SEPOOL_4_inst_adr                                                     "0x00C4"
#define MVDBLK_SEPOOL_5_inst_adr                                                     "0x00C5"
#define MVDBLK_SEPOOL_6_inst_adr                                                     "0x00C6"
#define MVDBLK_SEPOOL_7_inst_adr                                                     "0x00C7"
#define MVDBLK_SEPOOL_8_inst_adr                                                     "0x00C8"
#define MVDBLK_SEPOOL_9_inst_adr                                                     "0x00C9"
#define MVDBLK_SEPOOL_10_inst_adr                                                     "0x00CA"
#define MVDBLK_SEPOOL_11_inst_adr                                                     "0x00CB"
#define MVDBLK_SEPOOL_12_inst_adr                                                     "0x00CC"
#define MVDBLK_SEPOOL_13_inst_adr                                                     "0x00CD"
#define MVDBLK_SEPOOL_14_inst_adr                                                     "0x00CE"
#define MVDBLK_SEPOOL_15_inst_adr                                                     "0x00CF"
#define MVDBLK_SEPOOL_0_inst                                                         0x00C0
#define MVDBLK_SEPOOL_1_inst                                                         0x00C1
#define MVDBLK_SEPOOL_2_inst                                                         0x00C2
#define MVDBLK_SEPOOL_3_inst                                                         0x00C3
#define MVDBLK_SEPOOL_4_inst                                                         0x00C4
#define MVDBLK_SEPOOL_5_inst                                                         0x00C5
#define MVDBLK_SEPOOL_6_inst                                                         0x00C6
#define MVDBLK_SEPOOL_7_inst                                                         0x00C7
#define MVDBLK_SEPOOL_8_inst                                                         0x00C8
#define MVDBLK_SEPOOL_9_inst                                                         0x00C9
#define MVDBLK_SEPOOL_10_inst                                                         0x00CA
#define MVDBLK_SEPOOL_11_inst                                                         0x00CB
#define MVDBLK_SEPOOL_12_inst                                                         0x00CC
#define MVDBLK_SEPOOL_13_inst                                                         0x00CD
#define MVDBLK_SEPOOL_14_inst                                                         0x00CE
#define MVDBLK_SEPOOL_15_inst                                                         0x00CF
#define MVDBLK_SEPOOL_entry_shift                                                    (0)
#define MVDBLK_SEPOOL_entry_mask                                                     (0x0FFFFFFF)
#define MVDBLK_SEPOOL_entry(data)                                                    (0x0FFFFFFF&((data)<<0))
#define MVDBLK_SEPOOL_entry_src(data)                                                ((0x0FFFFFFF&(data))>>0)
#define MVDBLK_SEPOOL_get_entry(data)                                                ((0x0FFFFFFF&(data))>>0)


#define MVDBLK_H264BASE                                                              0x1800e6c0
#define MVDBLK_H264BASE_reg_addr                                                     "0xB800E6C0"
#define MVDBLK_H264BASE_reg                                                          0xB800E6C0
#define set_MVDBLK_H264BASE_reg(data)   (*((volatile unsigned int*) MVDBLK_H264BASE_reg)=data)
#define get_MVDBLK_H264BASE_reg   (*((volatile unsigned int*) MVDBLK_H264BASE_reg))
#define MVDBLK_H264BASE_inst_adr                                                     "0x00B0"
#define MVDBLK_H264BASE_inst                                                         0x00B0
#define MVDBLK_H264BASE_SetNhAvail_shift                                             (0)
#define MVDBLK_H264BASE_SetNhAvail_mask                                              (0x00000001)
#define MVDBLK_H264BASE_SetNhAvail(data)                                             (0x00000001&((data)<<0))
#define MVDBLK_H264BASE_SetNhAvail_src(data)                                         ((0x00000001&(data))>>0)
#define MVDBLK_H264BASE_get_SetNhAvail(data)                                         ((0x00000001&(data))>>0)


#define MVDBLK_H264BASE1                                                             0x1800e6c4
#define MVDBLK_H264BASE1_reg_addr                                                    "0xB800E6C4"
#define MVDBLK_H264BASE1_reg                                                         0xB800E6C4
#define set_MVDBLK_H264BASE1_reg(data)   (*((volatile unsigned int*) MVDBLK_H264BASE1_reg)=data)
#define get_MVDBLK_H264BASE1_reg   (*((volatile unsigned int*) MVDBLK_H264BASE1_reg))
#define MVDBLK_H264BASE1_inst_adr                                                    "0x00B1"
#define MVDBLK_H264BASE1_inst                                                        0x00B1
#define MVDBLK_H264BASE1_LeftAvail_shift                                             (3)
#define MVDBLK_H264BASE1_LeftAvail_mask                                              (0x00000008)
#define MVDBLK_H264BASE1_LeftAvail(data)                                             (0x00000008&((data)<<3))
#define MVDBLK_H264BASE1_LeftAvail_src(data)                                         ((0x00000008&(data))>>3)
#define MVDBLK_H264BASE1_get_LeftAvail(data)                                         ((0x00000008&(data))>>3)
#define MVDBLK_H264BASE1_TopAvail_shift                                              (2)
#define MVDBLK_H264BASE1_TopAvail_mask                                               (0x00000004)
#define MVDBLK_H264BASE1_TopAvail(data)                                              (0x00000004&((data)<<2))
#define MVDBLK_H264BASE1_TopAvail_src(data)                                          ((0x00000004&(data))>>2)
#define MVDBLK_H264BASE1_get_TopAvail(data)                                          ((0x00000004&(data))>>2)
#define MVDBLK_H264BASE1_TopRightAvail_shift                                         (1)
#define MVDBLK_H264BASE1_TopRightAvail_mask                                          (0x00000002)
#define MVDBLK_H264BASE1_TopRightAvail(data)                                         (0x00000002&((data)<<1))
#define MVDBLK_H264BASE1_TopRightAvail_src(data)                                     ((0x00000002&(data))>>1)
#define MVDBLK_H264BASE1_get_TopRightAvail(data)                                     ((0x00000002&(data))>>1)
#define MVDBLK_H264BASE1_TopLeftAvail_shift                                          (0)
#define MVDBLK_H264BASE1_TopLeftAvail_mask                                           (0x00000001)
#define MVDBLK_H264BASE1_TopLeftAvail(data)                                          (0x00000001&((data)<<0))
#define MVDBLK_H264BASE1_TopLeftAvail_src(data)                                      ((0x00000001&(data))>>0)
#define MVDBLK_H264BASE1_get_TopLeftAvail(data)                                      ((0x00000001&(data))>>0)


#define MVDBLK_DBG                                                                   0x1800e6c8
#define MVDBLK_DBG_reg_addr                                                          "0xB800E6C8"
#define MVDBLK_DBG_reg                                                               0xB800E6C8
#define set_MVDBLK_DBG_reg(data)   (*((volatile unsigned int*) MVDBLK_DBG_reg)=data)
#define get_MVDBLK_DBG_reg   (*((volatile unsigned int*) MVDBLK_DBG_reg))
#define MVDBLK_DBG_inst_adr                                                          "0x00B2"
#define MVDBLK_DBG_inst                                                              0x00B2
#define MVDBLK_DBG_GenPulse_shift                                                    (31)
#define MVDBLK_DBG_GenPulse_mask                                                     (0x80000000)
#define MVDBLK_DBG_GenPulse(data)                                                    (0x80000000&((data)<<31))
#define MVDBLK_DBG_GenPulse_src(data)                                                ((0x80000000&(data))>>31)
#define MVDBLK_DBG_get_GenPulse(data)                                                ((0x80000000&(data))>>31)
#define MVDBLK_DBG_PicCount_shift                                                    (16)
#define MVDBLK_DBG_PicCount_mask                                                     (0x7FFF0000)
#define MVDBLK_DBG_PicCount(data)                                                    (0x7FFF0000&((data)<<16))
#define MVDBLK_DBG_PicCount_src(data)                                                ((0x7FFF0000&(data))>>16)
#define MVDBLK_DBG_get_PicCount(data)                                                ((0x7FFF0000&(data))>>16)
#define MVDBLK_DBG_DbgCtrl_shift                                                     (13)
#define MVDBLK_DBG_DbgCtrl_mask                                                      (0x0000E000)
#define MVDBLK_DBG_DbgCtrl(data)                                                     (0x0000E000&((data)<<13))
#define MVDBLK_DBG_DbgCtrl_src(data)                                                 ((0x0000E000&(data))>>13)
#define MVDBLK_DBG_get_DbgCtrl(data)                                                 ((0x0000E000&(data))>>13)
#define MVDBLK_DBG_MbAddr_shift                                                      (0)
#define MVDBLK_DBG_MbAddr_mask                                                       (0x00001FFF)
#define MVDBLK_DBG_MbAddr(data)                                                      (0x00001FFF&((data)<<0))
#define MVDBLK_DBG_MbAddr_src(data)                                                  ((0x00001FFF&(data))>>0)
#define MVDBLK_DBG_get_MbAddr(data)                                                  ((0x00001FFF&(data))>>0)


#endif
