/**************************************************************
// Spec Version                  : 1.0
// Parser Version                : DVR_Parser_6.8(110516)
// CModelGen Version             : 5.0 2009.04.09
// Naming Rule                   :  Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2011/9/8 15:10:45
***************************************************************/


#ifndef _VC_REG_H_INCLUDED_
#define _VC_REG_H_INCLUDED_
#ifdef  _VC_USE_STRUCT
typedef struct 
{
unsigned int     src:29;
unsigned int     reserved_0:3;
}VC_DMA_SRC;

typedef struct 
{
unsigned int     dst:29;
unsigned int     reserved_0:3;
}VC_DMA_DST;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     valid:1;
unsigned int     dir:1;
unsigned int     size:11;
unsigned int     reserved_1:2;
unsigned int     dma_type:1;
}VC_DMA_SIZE;

typedef struct 
{
unsigned int     blk_h:6;
unsigned int     blk_w:4;
unsigned int     blk_y:12;
unsigned int     blk_x:10;
}VC_DMA_BLK;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     field_mode:1;
unsigned int     pic_index:7;
unsigned int     chroma:1;
unsigned int     row_offset:5;
unsigned int     chroma_pitch:11;
}VC_DMA_BLKINFO;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_enable1:1;
unsigned int     max_xfer:6;
unsigned int     reserved_1:5;
unsigned int     write_enable3:1;
unsigned int     dmem_req_en:1;
unsigned int     write_enable4:1;
unsigned int     stop:1;
unsigned int     write_enable5:1;
unsigned int     go:1;
}VC_DMA_CNTL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     int_done:1;
}VC_DMA_INT;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     int_done_en:1;
}VC_DMA_INT_EN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     done_7:1;
unsigned int     done_6:1;
unsigned int     done_5:1;
unsigned int     done_4:1;
unsigned int     done_3:1;
unsigned int     done_2:1;
unsigned int     done_1:1;
unsigned int     done_0:1;
}VC_DMA_STATUS;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     write_enable3:1;
unsigned int     sel1:4;
unsigned int     write_enable2:1;
unsigned int     sel0:4;
unsigned int     write_enable1:1;
unsigned int     enable:1;
}VC_DMA_DEBUG;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     write_enable1:1;
unsigned int     delay_timer:5;
}VC_DMA_TIMER;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     RMEA:1;
unsigned int     RMA_3:1;
unsigned int     RMA_2:1;
unsigned int     RMA_1:1;
unsigned int     RMA_0:1;
unsigned int     reserved_1:3;
unsigned int     RMEB:1;
unsigned int     RMB_3:1;
unsigned int     RMB_2:1;
unsigned int     RMB_1:1;
unsigned int     RMB_0:1;
}VC_DMA_BIST_RM;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     bist_fail0:1;
unsigned int     bist_done:1;
}VC_DMA_BIST_ST;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     drf_start_pause:1;
unsigned int     reserved_1:14;
unsigned int     drf_fail0:1;
unsigned int     drf_done:1;
}VC_DMA_DRF_ST;

#endif

#define VC_DMA_SRC_0                                                                 0x18001000
#define VC_DMA_SRC_1                                                                 0x18001004
#define VC_DMA_SRC_2                                                                 0x18001008
#define VC_DMA_SRC_3                                                                 0x1800100C
#define VC_DMA_SRC_4                                                                 0x18001010
#define VC_DMA_SRC_5                                                                 0x18001014
#define VC_DMA_SRC_6                                                                 0x18001018
#define VC_DMA_SRC_7                                                                 0x1800101C
#define VC_DMA_SRC_0_reg_addr                                                        "0xB8001000"
#define VC_DMA_SRC_1_reg_addr                                                        "0xB8001004"
#define VC_DMA_SRC_2_reg_addr                                                        "0xB8001008"
#define VC_DMA_SRC_3_reg_addr                                                        "0xB800100C"
#define VC_DMA_SRC_4_reg_addr                                                        "0xB8001010"
#define VC_DMA_SRC_5_reg_addr                                                        "0xB8001014"
#define VC_DMA_SRC_6_reg_addr                                                        "0xB8001018"
#define VC_DMA_SRC_7_reg_addr                                                        "0xB800101C"
#define VC_DMA_SRC_0_reg                                                             0xB8001000
#define VC_DMA_SRC_1_reg                                                             0xB8001004
#define VC_DMA_SRC_2_reg                                                             0xB8001008
#define VC_DMA_SRC_3_reg                                                             0xB800100C
#define VC_DMA_SRC_4_reg                                                             0xB8001010
#define VC_DMA_SRC_5_reg                                                             0xB8001014
#define VC_DMA_SRC_6_reg                                                             0xB8001018
#define VC_DMA_SRC_7_reg                                                             0xB800101C
#define set_VC_DMA_SRC_0_reg(data)   (*((volatile unsigned int*) VC_DMA_SRC_0_reg)=data)
#define set_VC_DMA_SRC_1_reg(data)   (*((volatile unsigned int*) VC_DMA_SRC_1_reg)=data)
#define set_VC_DMA_SRC_2_reg(data)   (*((volatile unsigned int*) VC_DMA_SRC_2_reg)=data)
#define set_VC_DMA_SRC_3_reg(data)   (*((volatile unsigned int*) VC_DMA_SRC_3_reg)=data)
#define set_VC_DMA_SRC_4_reg(data)   (*((volatile unsigned int*) VC_DMA_SRC_4_reg)=data)
#define set_VC_DMA_SRC_5_reg(data)   (*((volatile unsigned int*) VC_DMA_SRC_5_reg)=data)
#define set_VC_DMA_SRC_6_reg(data)   (*((volatile unsigned int*) VC_DMA_SRC_6_reg)=data)
#define set_VC_DMA_SRC_7_reg(data)   (*((volatile unsigned int*) VC_DMA_SRC_7_reg)=data)
#define get_VC_DMA_SRC_0_reg   (*((volatile unsigned int*) VC_DMA_SRC_0_reg))
#define get_VC_DMA_SRC_1_reg   (*((volatile unsigned int*) VC_DMA_SRC_1_reg))
#define get_VC_DMA_SRC_2_reg   (*((volatile unsigned int*) VC_DMA_SRC_2_reg))
#define get_VC_DMA_SRC_3_reg   (*((volatile unsigned int*) VC_DMA_SRC_3_reg))
#define get_VC_DMA_SRC_4_reg   (*((volatile unsigned int*) VC_DMA_SRC_4_reg))
#define get_VC_DMA_SRC_5_reg   (*((volatile unsigned int*) VC_DMA_SRC_5_reg))
#define get_VC_DMA_SRC_6_reg   (*((volatile unsigned int*) VC_DMA_SRC_6_reg))
#define get_VC_DMA_SRC_7_reg   (*((volatile unsigned int*) VC_DMA_SRC_7_reg))
#define VC_DMA_SRC_0_inst_adr                                                        "0x0000"
#define VC_DMA_SRC_1_inst_adr                                                        "0x0001"
#define VC_DMA_SRC_2_inst_adr                                                        "0x0002"
#define VC_DMA_SRC_3_inst_adr                                                        "0x0003"
#define VC_DMA_SRC_4_inst_adr                                                        "0x0004"
#define VC_DMA_SRC_5_inst_adr                                                        "0x0005"
#define VC_DMA_SRC_6_inst_adr                                                        "0x0006"
#define VC_DMA_SRC_7_inst_adr                                                        "0x0007"
#define VC_DMA_SRC_0_inst                                                            0x0000
#define VC_DMA_SRC_1_inst                                                            0x0001
#define VC_DMA_SRC_2_inst                                                            0x0002
#define VC_DMA_SRC_3_inst                                                            0x0003
#define VC_DMA_SRC_4_inst                                                            0x0004
#define VC_DMA_SRC_5_inst                                                            0x0005
#define VC_DMA_SRC_6_inst                                                            0x0006
#define VC_DMA_SRC_7_inst                                                            0x0007
#define VC_DMA_SRC_src_shift                                                         (3)
#define VC_DMA_SRC_src_mask                                                          (0xFFFFFFF8)
#define VC_DMA_SRC_src(data)                                                         (0xFFFFFFF8&((data)<<3))
#define VC_DMA_SRC_src_src(data)                                                     ((0xFFFFFFF8&(data))>>3)
#define VC_DMA_SRC_get_src(data)                                                     ((0xFFFFFFF8&(data))>>3)


#define VC_DMA_DST_0                                                                 0x18001020
#define VC_DMA_DST_1                                                                 0x18001024
#define VC_DMA_DST_2                                                                 0x18001028
#define VC_DMA_DST_3                                                                 0x1800102C
#define VC_DMA_DST_4                                                                 0x18001030
#define VC_DMA_DST_5                                                                 0x18001034
#define VC_DMA_DST_6                                                                 0x18001038
#define VC_DMA_DST_7                                                                 0x1800103C
#define VC_DMA_DST_0_reg_addr                                                        "0xB8001020"
#define VC_DMA_DST_1_reg_addr                                                        "0xB8001024"
#define VC_DMA_DST_2_reg_addr                                                        "0xB8001028"
#define VC_DMA_DST_3_reg_addr                                                        "0xB800102C"
#define VC_DMA_DST_4_reg_addr                                                        "0xB8001030"
#define VC_DMA_DST_5_reg_addr                                                        "0xB8001034"
#define VC_DMA_DST_6_reg_addr                                                        "0xB8001038"
#define VC_DMA_DST_7_reg_addr                                                        "0xB800103C"
#define VC_DMA_DST_0_reg                                                             0xB8001020
#define VC_DMA_DST_1_reg                                                             0xB8001024
#define VC_DMA_DST_2_reg                                                             0xB8001028
#define VC_DMA_DST_3_reg                                                             0xB800102C
#define VC_DMA_DST_4_reg                                                             0xB8001030
#define VC_DMA_DST_5_reg                                                             0xB8001034
#define VC_DMA_DST_6_reg                                                             0xB8001038
#define VC_DMA_DST_7_reg                                                             0xB800103C
#define set_VC_DMA_DST_0_reg(data)   (*((volatile unsigned int*) VC_DMA_DST_0_reg)=data)
#define set_VC_DMA_DST_1_reg(data)   (*((volatile unsigned int*) VC_DMA_DST_1_reg)=data)
#define set_VC_DMA_DST_2_reg(data)   (*((volatile unsigned int*) VC_DMA_DST_2_reg)=data)
#define set_VC_DMA_DST_3_reg(data)   (*((volatile unsigned int*) VC_DMA_DST_3_reg)=data)
#define set_VC_DMA_DST_4_reg(data)   (*((volatile unsigned int*) VC_DMA_DST_4_reg)=data)
#define set_VC_DMA_DST_5_reg(data)   (*((volatile unsigned int*) VC_DMA_DST_5_reg)=data)
#define set_VC_DMA_DST_6_reg(data)   (*((volatile unsigned int*) VC_DMA_DST_6_reg)=data)
#define set_VC_DMA_DST_7_reg(data)   (*((volatile unsigned int*) VC_DMA_DST_7_reg)=data)
#define get_VC_DMA_DST_0_reg   (*((volatile unsigned int*) VC_DMA_DST_0_reg))
#define get_VC_DMA_DST_1_reg   (*((volatile unsigned int*) VC_DMA_DST_1_reg))
#define get_VC_DMA_DST_2_reg   (*((volatile unsigned int*) VC_DMA_DST_2_reg))
#define get_VC_DMA_DST_3_reg   (*((volatile unsigned int*) VC_DMA_DST_3_reg))
#define get_VC_DMA_DST_4_reg   (*((volatile unsigned int*) VC_DMA_DST_4_reg))
#define get_VC_DMA_DST_5_reg   (*((volatile unsigned int*) VC_DMA_DST_5_reg))
#define get_VC_DMA_DST_6_reg   (*((volatile unsigned int*) VC_DMA_DST_6_reg))
#define get_VC_DMA_DST_7_reg   (*((volatile unsigned int*) VC_DMA_DST_7_reg))
#define VC_DMA_DST_0_inst_adr                                                        "0x0008"
#define VC_DMA_DST_1_inst_adr                                                        "0x0009"
#define VC_DMA_DST_2_inst_adr                                                        "0x000A"
#define VC_DMA_DST_3_inst_adr                                                        "0x000B"
#define VC_DMA_DST_4_inst_adr                                                        "0x000C"
#define VC_DMA_DST_5_inst_adr                                                        "0x000D"
#define VC_DMA_DST_6_inst_adr                                                        "0x000E"
#define VC_DMA_DST_7_inst_adr                                                        "0x000F"
#define VC_DMA_DST_0_inst                                                            0x0008
#define VC_DMA_DST_1_inst                                                            0x0009
#define VC_DMA_DST_2_inst                                                            0x000A
#define VC_DMA_DST_3_inst                                                            0x000B
#define VC_DMA_DST_4_inst                                                            0x000C
#define VC_DMA_DST_5_inst                                                            0x000D
#define VC_DMA_DST_6_inst                                                            0x000E
#define VC_DMA_DST_7_inst                                                            0x000F
#define VC_DMA_DST_dst_shift                                                         (3)
#define VC_DMA_DST_dst_mask                                                          (0xFFFFFFF8)
#define VC_DMA_DST_dst(data)                                                         (0xFFFFFFF8&((data)<<3))
#define VC_DMA_DST_dst_src(data)                                                     ((0xFFFFFFF8&(data))>>3)
#define VC_DMA_DST_get_dst(data)                                                     ((0xFFFFFFF8&(data))>>3)


#define VC_DMA_SIZE_0                                                                0x18001040
#define VC_DMA_SIZE_1                                                                0x18001044
#define VC_DMA_SIZE_2                                                                0x18001048
#define VC_DMA_SIZE_3                                                                0x1800104C
#define VC_DMA_SIZE_4                                                                0x18001050
#define VC_DMA_SIZE_5                                                                0x18001054
#define VC_DMA_SIZE_6                                                                0x18001058
#define VC_DMA_SIZE_7                                                                0x1800105C
#define VC_DMA_SIZE_0_reg_addr                                                       "0xB8001040"
#define VC_DMA_SIZE_1_reg_addr                                                       "0xB8001044"
#define VC_DMA_SIZE_2_reg_addr                                                       "0xB8001048"
#define VC_DMA_SIZE_3_reg_addr                                                       "0xB800104C"
#define VC_DMA_SIZE_4_reg_addr                                                       "0xB8001050"
#define VC_DMA_SIZE_5_reg_addr                                                       "0xB8001054"
#define VC_DMA_SIZE_6_reg_addr                                                       "0xB8001058"
#define VC_DMA_SIZE_7_reg_addr                                                       "0xB800105C"
#define VC_DMA_SIZE_0_reg                                                            0xB8001040
#define VC_DMA_SIZE_1_reg                                                            0xB8001044
#define VC_DMA_SIZE_2_reg                                                            0xB8001048
#define VC_DMA_SIZE_3_reg                                                            0xB800104C
#define VC_DMA_SIZE_4_reg                                                            0xB8001050
#define VC_DMA_SIZE_5_reg                                                            0xB8001054
#define VC_DMA_SIZE_6_reg                                                            0xB8001058
#define VC_DMA_SIZE_7_reg                                                            0xB800105C
#define set_VC_DMA_SIZE_0_reg(data)   (*((volatile unsigned int*) VC_DMA_SIZE_0_reg)=data)
#define set_VC_DMA_SIZE_1_reg(data)   (*((volatile unsigned int*) VC_DMA_SIZE_1_reg)=data)
#define set_VC_DMA_SIZE_2_reg(data)   (*((volatile unsigned int*) VC_DMA_SIZE_2_reg)=data)
#define set_VC_DMA_SIZE_3_reg(data)   (*((volatile unsigned int*) VC_DMA_SIZE_3_reg)=data)
#define set_VC_DMA_SIZE_4_reg(data)   (*((volatile unsigned int*) VC_DMA_SIZE_4_reg)=data)
#define set_VC_DMA_SIZE_5_reg(data)   (*((volatile unsigned int*) VC_DMA_SIZE_5_reg)=data)
#define set_VC_DMA_SIZE_6_reg(data)   (*((volatile unsigned int*) VC_DMA_SIZE_6_reg)=data)
#define set_VC_DMA_SIZE_7_reg(data)   (*((volatile unsigned int*) VC_DMA_SIZE_7_reg)=data)
#define get_VC_DMA_SIZE_0_reg   (*((volatile unsigned int*) VC_DMA_SIZE_0_reg))
#define get_VC_DMA_SIZE_1_reg   (*((volatile unsigned int*) VC_DMA_SIZE_1_reg))
#define get_VC_DMA_SIZE_2_reg   (*((volatile unsigned int*) VC_DMA_SIZE_2_reg))
#define get_VC_DMA_SIZE_3_reg   (*((volatile unsigned int*) VC_DMA_SIZE_3_reg))
#define get_VC_DMA_SIZE_4_reg   (*((volatile unsigned int*) VC_DMA_SIZE_4_reg))
#define get_VC_DMA_SIZE_5_reg   (*((volatile unsigned int*) VC_DMA_SIZE_5_reg))
#define get_VC_DMA_SIZE_6_reg   (*((volatile unsigned int*) VC_DMA_SIZE_6_reg))
#define get_VC_DMA_SIZE_7_reg   (*((volatile unsigned int*) VC_DMA_SIZE_7_reg))
#define VC_DMA_SIZE_0_inst_adr                                                       "0x0010"
#define VC_DMA_SIZE_1_inst_adr                                                       "0x0011"
#define VC_DMA_SIZE_2_inst_adr                                                       "0x0012"
#define VC_DMA_SIZE_3_inst_adr                                                       "0x0013"
#define VC_DMA_SIZE_4_inst_adr                                                       "0x0014"
#define VC_DMA_SIZE_5_inst_adr                                                       "0x0015"
#define VC_DMA_SIZE_6_inst_adr                                                       "0x0016"
#define VC_DMA_SIZE_7_inst_adr                                                       "0x0017"
#define VC_DMA_SIZE_0_inst                                                           0x0010
#define VC_DMA_SIZE_1_inst                                                           0x0011
#define VC_DMA_SIZE_2_inst                                                           0x0012
#define VC_DMA_SIZE_3_inst                                                           0x0013
#define VC_DMA_SIZE_4_inst                                                           0x0014
#define VC_DMA_SIZE_5_inst                                                           0x0015
#define VC_DMA_SIZE_6_inst                                                           0x0016
#define VC_DMA_SIZE_7_inst                                                           0x0017
#define VC_DMA_SIZE_valid_shift                                                      (15)
#define VC_DMA_SIZE_valid_mask                                                       (0x00008000)
#define VC_DMA_SIZE_valid(data)                                                      (0x00008000&((data)<<15))
#define VC_DMA_SIZE_valid_src(data)                                                  ((0x00008000&(data))>>15)
#define VC_DMA_SIZE_get_valid(data)                                                  ((0x00008000&(data))>>15)
#define VC_DMA_SIZE_dir_shift                                                        (14)
#define VC_DMA_SIZE_dir_mask                                                         (0x00004000)
#define VC_DMA_SIZE_dir(data)                                                        (0x00004000&((data)<<14))
#define VC_DMA_SIZE_dir_src(data)                                                    ((0x00004000&(data))>>14)
#define VC_DMA_SIZE_get_dir(data)                                                    ((0x00004000&(data))>>14)
#define VC_DMA_SIZE_size_shift                                                       (3)
#define VC_DMA_SIZE_size_mask                                                        (0x00003FF8)
#define VC_DMA_SIZE_size(data)                                                       (0x00003FF8&((data)<<3))
#define VC_DMA_SIZE_size_src(data)                                                   ((0x00003FF8&(data))>>3)
#define VC_DMA_SIZE_get_size(data)                                                   ((0x00003FF8&(data))>>3)
#define VC_DMA_SIZE_dma_type_shift                                                   (0)
#define VC_DMA_SIZE_dma_type_mask                                                    (0x00000001)
#define VC_DMA_SIZE_dma_type(data)                                                   (0x00000001&((data)<<0))
#define VC_DMA_SIZE_dma_type_src(data)                                               ((0x00000001&(data))>>0)
#define VC_DMA_SIZE_get_dma_type(data)                                               ((0x00000001&(data))>>0)


#define VC_DMA_BLK_0                                                                 0x18001090
#define VC_DMA_BLK_1                                                                 0x18001094
#define VC_DMA_BLK_2                                                                 0x18001098
#define VC_DMA_BLK_3                                                                 0x1800109C
#define VC_DMA_BLK_4                                                                 0x180010A0
#define VC_DMA_BLK_5                                                                 0x180010A4
#define VC_DMA_BLK_6                                                                 0x180010A8
#define VC_DMA_BLK_7                                                                 0x180010AC
#define VC_DMA_BLK_0_reg_addr                                                        "0xB8001090"
#define VC_DMA_BLK_1_reg_addr                                                        "0xB8001094"
#define VC_DMA_BLK_2_reg_addr                                                        "0xB8001098"
#define VC_DMA_BLK_3_reg_addr                                                        "0xB800109C"
#define VC_DMA_BLK_4_reg_addr                                                        "0xB80010A0"
#define VC_DMA_BLK_5_reg_addr                                                        "0xB80010A4"
#define VC_DMA_BLK_6_reg_addr                                                        "0xB80010A8"
#define VC_DMA_BLK_7_reg_addr                                                        "0xB80010AC"
#define VC_DMA_BLK_0_reg                                                             0xB8001090
#define VC_DMA_BLK_1_reg                                                             0xB8001094
#define VC_DMA_BLK_2_reg                                                             0xB8001098
#define VC_DMA_BLK_3_reg                                                             0xB800109C
#define VC_DMA_BLK_4_reg                                                             0xB80010A0
#define VC_DMA_BLK_5_reg                                                             0xB80010A4
#define VC_DMA_BLK_6_reg                                                             0xB80010A8
#define VC_DMA_BLK_7_reg                                                             0xB80010AC
#define set_VC_DMA_BLK_0_reg(data)   (*((volatile unsigned int*) VC_DMA_BLK_0_reg)=data)
#define set_VC_DMA_BLK_1_reg(data)   (*((volatile unsigned int*) VC_DMA_BLK_1_reg)=data)
#define set_VC_DMA_BLK_2_reg(data)   (*((volatile unsigned int*) VC_DMA_BLK_2_reg)=data)
#define set_VC_DMA_BLK_3_reg(data)   (*((volatile unsigned int*) VC_DMA_BLK_3_reg)=data)
#define set_VC_DMA_BLK_4_reg(data)   (*((volatile unsigned int*) VC_DMA_BLK_4_reg)=data)
#define set_VC_DMA_BLK_5_reg(data)   (*((volatile unsigned int*) VC_DMA_BLK_5_reg)=data)
#define set_VC_DMA_BLK_6_reg(data)   (*((volatile unsigned int*) VC_DMA_BLK_6_reg)=data)
#define set_VC_DMA_BLK_7_reg(data)   (*((volatile unsigned int*) VC_DMA_BLK_7_reg)=data)
#define get_VC_DMA_BLK_0_reg   (*((volatile unsigned int*) VC_DMA_BLK_0_reg))
#define get_VC_DMA_BLK_1_reg   (*((volatile unsigned int*) VC_DMA_BLK_1_reg))
#define get_VC_DMA_BLK_2_reg   (*((volatile unsigned int*) VC_DMA_BLK_2_reg))
#define get_VC_DMA_BLK_3_reg   (*((volatile unsigned int*) VC_DMA_BLK_3_reg))
#define get_VC_DMA_BLK_4_reg   (*((volatile unsigned int*) VC_DMA_BLK_4_reg))
#define get_VC_DMA_BLK_5_reg   (*((volatile unsigned int*) VC_DMA_BLK_5_reg))
#define get_VC_DMA_BLK_6_reg   (*((volatile unsigned int*) VC_DMA_BLK_6_reg))
#define get_VC_DMA_BLK_7_reg   (*((volatile unsigned int*) VC_DMA_BLK_7_reg))
#define VC_DMA_BLK_0_inst_adr                                                        "0x0024"
#define VC_DMA_BLK_1_inst_adr                                                        "0x0025"
#define VC_DMA_BLK_2_inst_adr                                                        "0x0026"
#define VC_DMA_BLK_3_inst_adr                                                        "0x0027"
#define VC_DMA_BLK_4_inst_adr                                                        "0x0028"
#define VC_DMA_BLK_5_inst_adr                                                        "0x0029"
#define VC_DMA_BLK_6_inst_adr                                                        "0x002A"
#define VC_DMA_BLK_7_inst_adr                                                        "0x002B"
#define VC_DMA_BLK_0_inst                                                            0x0024
#define VC_DMA_BLK_1_inst                                                            0x0025
#define VC_DMA_BLK_2_inst                                                            0x0026
#define VC_DMA_BLK_3_inst                                                            0x0027
#define VC_DMA_BLK_4_inst                                                            0x0028
#define VC_DMA_BLK_5_inst                                                            0x0029
#define VC_DMA_BLK_6_inst                                                            0x002A
#define VC_DMA_BLK_7_inst                                                            0x002B
#define VC_DMA_BLK_blk_h_shift                                                       (26)
#define VC_DMA_BLK_blk_h_mask                                                        (0xFC000000)
#define VC_DMA_BLK_blk_h(data)                                                       (0xFC000000&((data)<<26))
#define VC_DMA_BLK_blk_h_src(data)                                                   ((0xFC000000&(data))>>26)
#define VC_DMA_BLK_get_blk_h(data)                                                   ((0xFC000000&(data))>>26)
#define VC_DMA_BLK_blk_w_shift                                                       (22)
#define VC_DMA_BLK_blk_w_mask                                                        (0x03C00000)
#define VC_DMA_BLK_blk_w(data)                                                       (0x03C00000&((data)<<22))
#define VC_DMA_BLK_blk_w_src(data)                                                   ((0x03C00000&(data))>>22)
#define VC_DMA_BLK_get_blk_w(data)                                                   ((0x03C00000&(data))>>22)
#define VC_DMA_BLK_blk_y_shift                                                       (10)
#define VC_DMA_BLK_blk_y_mask                                                        (0x003FFC00)
#define VC_DMA_BLK_blk_y(data)                                                       (0x003FFC00&((data)<<10))
#define VC_DMA_BLK_blk_y_src(data)                                                   ((0x003FFC00&(data))>>10)
#define VC_DMA_BLK_get_blk_y(data)                                                   ((0x003FFC00&(data))>>10)
#define VC_DMA_BLK_blk_x_shift                                                       (0)
#define VC_DMA_BLK_blk_x_mask                                                        (0x000003FF)
#define VC_DMA_BLK_blk_x(data)                                                       (0x000003FF&((data)<<0))
#define VC_DMA_BLK_blk_x_src(data)                                                   ((0x000003FF&(data))>>0)
#define VC_DMA_BLK_get_blk_x(data)                                                   ((0x000003FF&(data))>>0)


#define VC_DMA_BLKINFO_0                                                             0x180010B0
#define VC_DMA_BLKINFO_1                                                             0x180010B4
#define VC_DMA_BLKINFO_2                                                             0x180010B8
#define VC_DMA_BLKINFO_3                                                             0x180010BC
#define VC_DMA_BLKINFO_4                                                             0x180010C0
#define VC_DMA_BLKINFO_5                                                             0x180010C4
#define VC_DMA_BLKINFO_6                                                             0x180010C8
#define VC_DMA_BLKINFO_7                                                             0x180010CC
#define VC_DMA_BLKINFO_0_reg_addr                                                    "0xB80010B0"
#define VC_DMA_BLKINFO_1_reg_addr                                                    "0xB80010B4"
#define VC_DMA_BLKINFO_2_reg_addr                                                    "0xB80010B8"
#define VC_DMA_BLKINFO_3_reg_addr                                                    "0xB80010BC"
#define VC_DMA_BLKINFO_4_reg_addr                                                    "0xB80010C0"
#define VC_DMA_BLKINFO_5_reg_addr                                                    "0xB80010C4"
#define VC_DMA_BLKINFO_6_reg_addr                                                    "0xB80010C8"
#define VC_DMA_BLKINFO_7_reg_addr                                                    "0xB80010CC"
#define VC_DMA_BLKINFO_0_reg                                                         0xB80010B0
#define VC_DMA_BLKINFO_1_reg                                                         0xB80010B4
#define VC_DMA_BLKINFO_2_reg                                                         0xB80010B8
#define VC_DMA_BLKINFO_3_reg                                                         0xB80010BC
#define VC_DMA_BLKINFO_4_reg                                                         0xB80010C0
#define VC_DMA_BLKINFO_5_reg                                                         0xB80010C4
#define VC_DMA_BLKINFO_6_reg                                                         0xB80010C8
#define VC_DMA_BLKINFO_7_reg                                                         0xB80010CC
#define set_VC_DMA_BLKINFO_0_reg(data)   (*((volatile unsigned int*) VC_DMA_BLKINFO_0_reg)=data)
#define set_VC_DMA_BLKINFO_1_reg(data)   (*((volatile unsigned int*) VC_DMA_BLKINFO_1_reg)=data)
#define set_VC_DMA_BLKINFO_2_reg(data)   (*((volatile unsigned int*) VC_DMA_BLKINFO_2_reg)=data)
#define set_VC_DMA_BLKINFO_3_reg(data)   (*((volatile unsigned int*) VC_DMA_BLKINFO_3_reg)=data)
#define set_VC_DMA_BLKINFO_4_reg(data)   (*((volatile unsigned int*) VC_DMA_BLKINFO_4_reg)=data)
#define set_VC_DMA_BLKINFO_5_reg(data)   (*((volatile unsigned int*) VC_DMA_BLKINFO_5_reg)=data)
#define set_VC_DMA_BLKINFO_6_reg(data)   (*((volatile unsigned int*) VC_DMA_BLKINFO_6_reg)=data)
#define set_VC_DMA_BLKINFO_7_reg(data)   (*((volatile unsigned int*) VC_DMA_BLKINFO_7_reg)=data)
#define get_VC_DMA_BLKINFO_0_reg   (*((volatile unsigned int*) VC_DMA_BLKINFO_0_reg))
#define get_VC_DMA_BLKINFO_1_reg   (*((volatile unsigned int*) VC_DMA_BLKINFO_1_reg))
#define get_VC_DMA_BLKINFO_2_reg   (*((volatile unsigned int*) VC_DMA_BLKINFO_2_reg))
#define get_VC_DMA_BLKINFO_3_reg   (*((volatile unsigned int*) VC_DMA_BLKINFO_3_reg))
#define get_VC_DMA_BLKINFO_4_reg   (*((volatile unsigned int*) VC_DMA_BLKINFO_4_reg))
#define get_VC_DMA_BLKINFO_5_reg   (*((volatile unsigned int*) VC_DMA_BLKINFO_5_reg))
#define get_VC_DMA_BLKINFO_6_reg   (*((volatile unsigned int*) VC_DMA_BLKINFO_6_reg))
#define get_VC_DMA_BLKINFO_7_reg   (*((volatile unsigned int*) VC_DMA_BLKINFO_7_reg))
#define VC_DMA_BLKINFO_0_inst_adr                                                    "0x002C"
#define VC_DMA_BLKINFO_1_inst_adr                                                    "0x002D"
#define VC_DMA_BLKINFO_2_inst_adr                                                    "0x002E"
#define VC_DMA_BLKINFO_3_inst_adr                                                    "0x002F"
#define VC_DMA_BLKINFO_4_inst_adr                                                    "0x0030"
#define VC_DMA_BLKINFO_5_inst_adr                                                    "0x0031"
#define VC_DMA_BLKINFO_6_inst_adr                                                    "0x0032"
#define VC_DMA_BLKINFO_7_inst_adr                                                    "0x0033"
#define VC_DMA_BLKINFO_0_inst                                                        0x002C
#define VC_DMA_BLKINFO_1_inst                                                        0x002D
#define VC_DMA_BLKINFO_2_inst                                                        0x002E
#define VC_DMA_BLKINFO_3_inst                                                        0x002F
#define VC_DMA_BLKINFO_4_inst                                                        0x0030
#define VC_DMA_BLKINFO_5_inst                                                        0x0031
#define VC_DMA_BLKINFO_6_inst                                                        0x0032
#define VC_DMA_BLKINFO_7_inst                                                        0x0033
#define VC_DMA_BLKINFO_field_mode_shift                                              (24)
#define VC_DMA_BLKINFO_field_mode_mask                                               (0x01000000)
#define VC_DMA_BLKINFO_field_mode(data)                                              (0x01000000&((data)<<24))
#define VC_DMA_BLKINFO_field_mode_src(data)                                          ((0x01000000&(data))>>24)
#define VC_DMA_BLKINFO_get_field_mode(data)                                          ((0x01000000&(data))>>24)
#define VC_DMA_BLKINFO_pic_index_shift                                               (17)
#define VC_DMA_BLKINFO_pic_index_mask                                                (0x00FE0000)
#define VC_DMA_BLKINFO_pic_index(data)                                               (0x00FE0000&((data)<<17))
#define VC_DMA_BLKINFO_pic_index_src(data)                                           ((0x00FE0000&(data))>>17)
#define VC_DMA_BLKINFO_get_pic_index(data)                                           ((0x00FE0000&(data))>>17)
#define VC_DMA_BLKINFO_chroma_shift                                                  (16)
#define VC_DMA_BLKINFO_chroma_mask                                                   (0x00010000)
#define VC_DMA_BLKINFO_chroma(data)                                                  (0x00010000&((data)<<16))
#define VC_DMA_BLKINFO_chroma_src(data)                                              ((0x00010000&(data))>>16)
#define VC_DMA_BLKINFO_get_chroma(data)                                              ((0x00010000&(data))>>16)
#define VC_DMA_BLKINFO_row_offset_shift                                              (11)
#define VC_DMA_BLKINFO_row_offset_mask                                               (0x0000F800)
#define VC_DMA_BLKINFO_row_offset(data)                                              (0x0000F800&((data)<<11))
#define VC_DMA_BLKINFO_row_offset_src(data)                                          ((0x0000F800&(data))>>11)
#define VC_DMA_BLKINFO_get_row_offset(data)                                          ((0x0000F800&(data))>>11)
#define VC_DMA_BLKINFO_chroma_pitch_shift                                            (0)
#define VC_DMA_BLKINFO_chroma_pitch_mask                                             (0x000007FF)
#define VC_DMA_BLKINFO_chroma_pitch(data)                                            (0x000007FF&((data)<<0))
#define VC_DMA_BLKINFO_chroma_pitch_src(data)                                        ((0x000007FF&(data))>>0)
#define VC_DMA_BLKINFO_get_chroma_pitch(data)                                        ((0x000007FF&(data))>>0)


#define VC_DMA_CNTL                                                                  0x18001064
#define VC_DMA_CNTL_reg_addr                                                         "0xB8001064"
#define VC_DMA_CNTL_reg                                                              0xB8001064
#define set_VC_DMA_CNTL_reg(data)   (*((volatile unsigned int*) VC_DMA_CNTL_reg)=data)
#define get_VC_DMA_CNTL_reg   (*((volatile unsigned int*) VC_DMA_CNTL_reg))
#define VC_DMA_CNTL_inst_adr                                                         "0x0019"
#define VC_DMA_CNTL_inst                                                             0x0019
#define VC_DMA_CNTL_write_enable1_shift                                              (17)
#define VC_DMA_CNTL_write_enable1_mask                                               (0x00020000)
#define VC_DMA_CNTL_write_enable1(data)                                              (0x00020000&((data)<<17))
#define VC_DMA_CNTL_write_enable1_src(data)                                          ((0x00020000&(data))>>17)
#define VC_DMA_CNTL_get_write_enable1(data)                                          ((0x00020000&(data))>>17)
#define VC_DMA_CNTL_max_xfer_shift                                                   (11)
#define VC_DMA_CNTL_max_xfer_mask                                                    (0x0001F800)
#define VC_DMA_CNTL_max_xfer(data)                                                   (0x0001F800&((data)<<11))
#define VC_DMA_CNTL_max_xfer_src(data)                                               ((0x0001F800&(data))>>11)
#define VC_DMA_CNTL_get_max_xfer(data)                                               ((0x0001F800&(data))>>11)
#define VC_DMA_CNTL_write_enable3_shift                                              (5)
#define VC_DMA_CNTL_write_enable3_mask                                               (0x00000020)
#define VC_DMA_CNTL_write_enable3(data)                                              (0x00000020&((data)<<5))
#define VC_DMA_CNTL_write_enable3_src(data)                                          ((0x00000020&(data))>>5)
#define VC_DMA_CNTL_get_write_enable3(data)                                          ((0x00000020&(data))>>5)
#define VC_DMA_CNTL_dmem_req_en_shift                                                (4)
#define VC_DMA_CNTL_dmem_req_en_mask                                                 (0x00000010)
#define VC_DMA_CNTL_dmem_req_en(data)                                                (0x00000010&((data)<<4))
#define VC_DMA_CNTL_dmem_req_en_src(data)                                            ((0x00000010&(data))>>4)
#define VC_DMA_CNTL_get_dmem_req_en(data)                                            ((0x00000010&(data))>>4)
#define VC_DMA_CNTL_write_enable4_shift                                              (3)
#define VC_DMA_CNTL_write_enable4_mask                                               (0x00000008)
#define VC_DMA_CNTL_write_enable4(data)                                              (0x00000008&((data)<<3))
#define VC_DMA_CNTL_write_enable4_src(data)                                          ((0x00000008&(data))>>3)
#define VC_DMA_CNTL_get_write_enable4(data)                                          ((0x00000008&(data))>>3)
#define VC_DMA_CNTL_stop_shift                                                       (2)
#define VC_DMA_CNTL_stop_mask                                                        (0x00000004)
#define VC_DMA_CNTL_stop(data)                                                       (0x00000004&((data)<<2))
#define VC_DMA_CNTL_stop_src(data)                                                   ((0x00000004&(data))>>2)
#define VC_DMA_CNTL_get_stop(data)                                                   ((0x00000004&(data))>>2)
#define VC_DMA_CNTL_write_enable5_shift                                              (1)
#define VC_DMA_CNTL_write_enable5_mask                                               (0x00000002)
#define VC_DMA_CNTL_write_enable5(data)                                              (0x00000002&((data)<<1))
#define VC_DMA_CNTL_write_enable5_src(data)                                          ((0x00000002&(data))>>1)
#define VC_DMA_CNTL_get_write_enable5(data)                                          ((0x00000002&(data))>>1)
#define VC_DMA_CNTL_go_shift                                                         (0)
#define VC_DMA_CNTL_go_mask                                                          (0x00000001)
#define VC_DMA_CNTL_go(data)                                                         (0x00000001&((data)<<0))
#define VC_DMA_CNTL_go_src(data)                                                     ((0x00000001&(data))>>0)
#define VC_DMA_CNTL_get_go(data)                                                     ((0x00000001&(data))>>0)


#define VC_DMA_INT                                                                   0x18001068
#define VC_DMA_INT_reg_addr                                                          "0xB8001068"
#define VC_DMA_INT_reg                                                               0xB8001068
#define set_VC_DMA_INT_reg(data)   (*((volatile unsigned int*) VC_DMA_INT_reg)=data)
#define get_VC_DMA_INT_reg   (*((volatile unsigned int*) VC_DMA_INT_reg))
#define VC_DMA_INT_inst_adr                                                          "0x001A"
#define VC_DMA_INT_inst                                                              0x001A
#define VC_DMA_INT_int_done_shift                                                    (0)
#define VC_DMA_INT_int_done_mask                                                     (0x00000001)
#define VC_DMA_INT_int_done(data)                                                    (0x00000001&((data)<<0))
#define VC_DMA_INT_int_done_src(data)                                                ((0x00000001&(data))>>0)
#define VC_DMA_INT_get_int_done(data)                                                ((0x00000001&(data))>>0)


#define VC_DMA_INT_EN                                                                0x1800106c
#define VC_DMA_INT_EN_reg_addr                                                       "0xB800106C"
#define VC_DMA_INT_EN_reg                                                            0xB800106C
#define set_VC_DMA_INT_EN_reg(data)   (*((volatile unsigned int*) VC_DMA_INT_EN_reg)=data)
#define get_VC_DMA_INT_EN_reg   (*((volatile unsigned int*) VC_DMA_INT_EN_reg))
#define VC_DMA_INT_EN_inst_adr                                                       "0x001B"
#define VC_DMA_INT_EN_inst                                                           0x001B
#define VC_DMA_INT_EN_int_done_en_shift                                              (0)
#define VC_DMA_INT_EN_int_done_en_mask                                               (0x00000001)
#define VC_DMA_INT_EN_int_done_en(data)                                              (0x00000001&((data)<<0))
#define VC_DMA_INT_EN_int_done_en_src(data)                                          ((0x00000001&(data))>>0)
#define VC_DMA_INT_EN_get_int_done_en(data)                                          ((0x00000001&(data))>>0)


#define VC_DMA_STATUS                                                                0x18001060
#define VC_DMA_STATUS_reg_addr                                                       "0xB8001060"
#define VC_DMA_STATUS_reg                                                            0xB8001060
#define set_VC_DMA_STATUS_reg(data)   (*((volatile unsigned int*) VC_DMA_STATUS_reg)=data)
#define get_VC_DMA_STATUS_reg   (*((volatile unsigned int*) VC_DMA_STATUS_reg))
#define VC_DMA_STATUS_inst_adr                                                       "0x0018"
#define VC_DMA_STATUS_inst                                                           0x0018
#define VC_DMA_STATUS_done_7_shift                                                   (7)
#define VC_DMA_STATUS_done_7_mask                                                    (0x00000080)
#define VC_DMA_STATUS_done_7(data)                                                   (0x00000080&((data)<<7))
#define VC_DMA_STATUS_done_7_src(data)                                               ((0x00000080&(data))>>7)
#define VC_DMA_STATUS_get_done_7(data)                                               ((0x00000080&(data))>>7)
#define VC_DMA_STATUS_done_6_shift                                                   (6)
#define VC_DMA_STATUS_done_6_mask                                                    (0x00000040)
#define VC_DMA_STATUS_done_6(data)                                                   (0x00000040&((data)<<6))
#define VC_DMA_STATUS_done_6_src(data)                                               ((0x00000040&(data))>>6)
#define VC_DMA_STATUS_get_done_6(data)                                               ((0x00000040&(data))>>6)
#define VC_DMA_STATUS_done_5_shift                                                   (5)
#define VC_DMA_STATUS_done_5_mask                                                    (0x00000020)
#define VC_DMA_STATUS_done_5(data)                                                   (0x00000020&((data)<<5))
#define VC_DMA_STATUS_done_5_src(data)                                               ((0x00000020&(data))>>5)
#define VC_DMA_STATUS_get_done_5(data)                                               ((0x00000020&(data))>>5)
#define VC_DMA_STATUS_done_4_shift                                                   (4)
#define VC_DMA_STATUS_done_4_mask                                                    (0x00000010)
#define VC_DMA_STATUS_done_4(data)                                                   (0x00000010&((data)<<4))
#define VC_DMA_STATUS_done_4_src(data)                                               ((0x00000010&(data))>>4)
#define VC_DMA_STATUS_get_done_4(data)                                               ((0x00000010&(data))>>4)
#define VC_DMA_STATUS_done_3_shift                                                   (3)
#define VC_DMA_STATUS_done_3_mask                                                    (0x00000008)
#define VC_DMA_STATUS_done_3(data)                                                   (0x00000008&((data)<<3))
#define VC_DMA_STATUS_done_3_src(data)                                               ((0x00000008&(data))>>3)
#define VC_DMA_STATUS_get_done_3(data)                                               ((0x00000008&(data))>>3)
#define VC_DMA_STATUS_done_2_shift                                                   (2)
#define VC_DMA_STATUS_done_2_mask                                                    (0x00000004)
#define VC_DMA_STATUS_done_2(data)                                                   (0x00000004&((data)<<2))
#define VC_DMA_STATUS_done_2_src(data)                                               ((0x00000004&(data))>>2)
#define VC_DMA_STATUS_get_done_2(data)                                               ((0x00000004&(data))>>2)
#define VC_DMA_STATUS_done_1_shift                                                   (1)
#define VC_DMA_STATUS_done_1_mask                                                    (0x00000002)
#define VC_DMA_STATUS_done_1(data)                                                   (0x00000002&((data)<<1))
#define VC_DMA_STATUS_done_1_src(data)                                               ((0x00000002&(data))>>1)
#define VC_DMA_STATUS_get_done_1(data)                                               ((0x00000002&(data))>>1)
#define VC_DMA_STATUS_done_0_shift                                                   (0)
#define VC_DMA_STATUS_done_0_mask                                                    (0x00000001)
#define VC_DMA_STATUS_done_0(data)                                                   (0x00000001&((data)<<0))
#define VC_DMA_STATUS_done_0_src(data)                                               ((0x00000001&(data))>>0)
#define VC_DMA_STATUS_get_done_0(data)                                               ((0x00000001&(data))>>0)


#define VC_DMA_DEBUG                                                                 0x18001080
#define VC_DMA_DEBUG_reg_addr                                                        "0xB8001080"
#define VC_DMA_DEBUG_reg                                                             0xB8001080
#define set_VC_DMA_DEBUG_reg(data)   (*((volatile unsigned int*) VC_DMA_DEBUG_reg)=data)
#define get_VC_DMA_DEBUG_reg   (*((volatile unsigned int*) VC_DMA_DEBUG_reg))
#define VC_DMA_DEBUG_inst_adr                                                        "0x0020"
#define VC_DMA_DEBUG_inst                                                            0x0020
#define VC_DMA_DEBUG_write_enable3_shift                                             (11)
#define VC_DMA_DEBUG_write_enable3_mask                                              (0x00000800)
#define VC_DMA_DEBUG_write_enable3(data)                                             (0x00000800&((data)<<11))
#define VC_DMA_DEBUG_write_enable3_src(data)                                         ((0x00000800&(data))>>11)
#define VC_DMA_DEBUG_get_write_enable3(data)                                         ((0x00000800&(data))>>11)
#define VC_DMA_DEBUG_sel1_shift                                                      (7)
#define VC_DMA_DEBUG_sel1_mask                                                       (0x00000780)
#define VC_DMA_DEBUG_sel1(data)                                                      (0x00000780&((data)<<7))
#define VC_DMA_DEBUG_sel1_src(data)                                                  ((0x00000780&(data))>>7)
#define VC_DMA_DEBUG_get_sel1(data)                                                  ((0x00000780&(data))>>7)
#define VC_DMA_DEBUG_write_enable2_shift                                             (6)
#define VC_DMA_DEBUG_write_enable2_mask                                              (0x00000040)
#define VC_DMA_DEBUG_write_enable2(data)                                             (0x00000040&((data)<<6))
#define VC_DMA_DEBUG_write_enable2_src(data)                                         ((0x00000040&(data))>>6)
#define VC_DMA_DEBUG_get_write_enable2(data)                                         ((0x00000040&(data))>>6)
#define VC_DMA_DEBUG_sel0_shift                                                      (2)
#define VC_DMA_DEBUG_sel0_mask                                                       (0x0000003C)
#define VC_DMA_DEBUG_sel0(data)                                                      (0x0000003C&((data)<<2))
#define VC_DMA_DEBUG_sel0_src(data)                                                  ((0x0000003C&(data))>>2)
#define VC_DMA_DEBUG_get_sel0(data)                                                  ((0x0000003C&(data))>>2)
#define VC_DMA_DEBUG_write_enable1_shift                                             (1)
#define VC_DMA_DEBUG_write_enable1_mask                                              (0x00000002)
#define VC_DMA_DEBUG_write_enable1(data)                                             (0x00000002&((data)<<1))
#define VC_DMA_DEBUG_write_enable1_src(data)                                         ((0x00000002&(data))>>1)
#define VC_DMA_DEBUG_get_write_enable1(data)                                         ((0x00000002&(data))>>1)
#define VC_DMA_DEBUG_enable_shift                                                    (0)
#define VC_DMA_DEBUG_enable_mask                                                     (0x00000001)
#define VC_DMA_DEBUG_enable(data)                                                    (0x00000001&((data)<<0))
#define VC_DMA_DEBUG_enable_src(data)                                                ((0x00000001&(data))>>0)
#define VC_DMA_DEBUG_get_enable(data)                                                ((0x00000001&(data))>>0)


#define VC_DMA_TIMER                                                                 0x18001084
#define VC_DMA_TIMER_reg_addr                                                        "0xB8001084"
#define VC_DMA_TIMER_reg                                                             0xB8001084
#define set_VC_DMA_TIMER_reg(data)   (*((volatile unsigned int*) VC_DMA_TIMER_reg)=data)
#define get_VC_DMA_TIMER_reg   (*((volatile unsigned int*) VC_DMA_TIMER_reg))
#define VC_DMA_TIMER_inst_adr                                                        "0x0021"
#define VC_DMA_TIMER_inst                                                            0x0021
#define VC_DMA_TIMER_write_enable1_shift                                             (5)
#define VC_DMA_TIMER_write_enable1_mask                                              (0x00000020)
#define VC_DMA_TIMER_write_enable1(data)                                             (0x00000020&((data)<<5))
#define VC_DMA_TIMER_write_enable1_src(data)                                         ((0x00000020&(data))>>5)
#define VC_DMA_TIMER_get_write_enable1(data)                                         ((0x00000020&(data))>>5)
#define VC_DMA_TIMER_delay_timer_shift                                               (0)
#define VC_DMA_TIMER_delay_timer_mask                                                (0x0000001F)
#define VC_DMA_TIMER_delay_timer(data)                                               (0x0000001F&((data)<<0))
#define VC_DMA_TIMER_delay_timer_src(data)                                           ((0x0000001F&(data))>>0)
#define VC_DMA_TIMER_get_delay_timer(data)                                           ((0x0000001F&(data))>>0)


#define VC_DMA_BIST_RM                                                               0x180010D0
#define VC_DMA_BIST_RM_reg_addr                                                      "0xB80010D0"
#define VC_DMA_BIST_RM_reg                                                           0xB80010D0
#define set_VC_DMA_BIST_RM_reg(data)   (*((volatile unsigned int*) VC_DMA_BIST_RM_reg)=data)
#define get_VC_DMA_BIST_RM_reg   (*((volatile unsigned int*) VC_DMA_BIST_RM_reg))
#define VC_DMA_BIST_RM_inst_adr                                                      "0x0034"
#define VC_DMA_BIST_RM_inst                                                          0x0034
#define VC_DMA_BIST_RM_RMEA_shift                                                    (12)
#define VC_DMA_BIST_RM_RMEA_mask                                                     (0x00001000)
#define VC_DMA_BIST_RM_RMEA(data)                                                    (0x00001000&((data)<<12))
#define VC_DMA_BIST_RM_RMEA_src(data)                                                ((0x00001000&(data))>>12)
#define VC_DMA_BIST_RM_get_RMEA(data)                                                ((0x00001000&(data))>>12)
#define VC_DMA_BIST_RM_RMA_3_shift                                                   (11)
#define VC_DMA_BIST_RM_RMA_3_mask                                                    (0x00000800)
#define VC_DMA_BIST_RM_RMA_3(data)                                                   (0x00000800&((data)<<11))
#define VC_DMA_BIST_RM_RMA_3_src(data)                                               ((0x00000800&(data))>>11)
#define VC_DMA_BIST_RM_get_RMA_3(data)                                               ((0x00000800&(data))>>11)
#define VC_DMA_BIST_RM_RMA_2_shift                                                   (10)
#define VC_DMA_BIST_RM_RMA_2_mask                                                    (0x00000400)
#define VC_DMA_BIST_RM_RMA_2(data)                                                   (0x00000400&((data)<<10))
#define VC_DMA_BIST_RM_RMA_2_src(data)                                               ((0x00000400&(data))>>10)
#define VC_DMA_BIST_RM_get_RMA_2(data)                                               ((0x00000400&(data))>>10)
#define VC_DMA_BIST_RM_RMA_1_shift                                                   (9)
#define VC_DMA_BIST_RM_RMA_1_mask                                                    (0x00000200)
#define VC_DMA_BIST_RM_RMA_1(data)                                                   (0x00000200&((data)<<9))
#define VC_DMA_BIST_RM_RMA_1_src(data)                                               ((0x00000200&(data))>>9)
#define VC_DMA_BIST_RM_get_RMA_1(data)                                               ((0x00000200&(data))>>9)
#define VC_DMA_BIST_RM_RMA_0_shift                                                   (8)
#define VC_DMA_BIST_RM_RMA_0_mask                                                    (0x00000100)
#define VC_DMA_BIST_RM_RMA_0(data)                                                   (0x00000100&((data)<<8))
#define VC_DMA_BIST_RM_RMA_0_src(data)                                               ((0x00000100&(data))>>8)
#define VC_DMA_BIST_RM_get_RMA_0(data)                                               ((0x00000100&(data))>>8)
#define VC_DMA_BIST_RM_RMEB_shift                                                    (4)
#define VC_DMA_BIST_RM_RMEB_mask                                                     (0x00000010)
#define VC_DMA_BIST_RM_RMEB(data)                                                    (0x00000010&((data)<<4))
#define VC_DMA_BIST_RM_RMEB_src(data)                                                ((0x00000010&(data))>>4)
#define VC_DMA_BIST_RM_get_RMEB(data)                                                ((0x00000010&(data))>>4)
#define VC_DMA_BIST_RM_RMB_3_shift                                                   (3)
#define VC_DMA_BIST_RM_RMB_3_mask                                                    (0x00000008)
#define VC_DMA_BIST_RM_RMB_3(data)                                                   (0x00000008&((data)<<3))
#define VC_DMA_BIST_RM_RMB_3_src(data)                                               ((0x00000008&(data))>>3)
#define VC_DMA_BIST_RM_get_RMB_3(data)                                               ((0x00000008&(data))>>3)
#define VC_DMA_BIST_RM_RMB_2_shift                                                   (2)
#define VC_DMA_BIST_RM_RMB_2_mask                                                    (0x00000004)
#define VC_DMA_BIST_RM_RMB_2(data)                                                   (0x00000004&((data)<<2))
#define VC_DMA_BIST_RM_RMB_2_src(data)                                               ((0x00000004&(data))>>2)
#define VC_DMA_BIST_RM_get_RMB_2(data)                                               ((0x00000004&(data))>>2)
#define VC_DMA_BIST_RM_RMB_1_shift                                                   (1)
#define VC_DMA_BIST_RM_RMB_1_mask                                                    (0x00000002)
#define VC_DMA_BIST_RM_RMB_1(data)                                                   (0x00000002&((data)<<1))
#define VC_DMA_BIST_RM_RMB_1_src(data)                                               ((0x00000002&(data))>>1)
#define VC_DMA_BIST_RM_get_RMB_1(data)                                               ((0x00000002&(data))>>1)
#define VC_DMA_BIST_RM_RMB_0_shift                                                   (0)
#define VC_DMA_BIST_RM_RMB_0_mask                                                    (0x00000001)
#define VC_DMA_BIST_RM_RMB_0(data)                                                   (0x00000001&((data)<<0))
#define VC_DMA_BIST_RM_RMB_0_src(data)                                               ((0x00000001&(data))>>0)
#define VC_DMA_BIST_RM_get_RMB_0(data)                                               ((0x00000001&(data))>>0)


#define VC_DMA_BIST_ST                                                               0x180010D4
#define VC_DMA_BIST_ST_reg_addr                                                      "0xB80010D4"
#define VC_DMA_BIST_ST_reg                                                           0xB80010D4
#define set_VC_DMA_BIST_ST_reg(data)   (*((volatile unsigned int*) VC_DMA_BIST_ST_reg)=data)
#define get_VC_DMA_BIST_ST_reg   (*((volatile unsigned int*) VC_DMA_BIST_ST_reg))
#define VC_DMA_BIST_ST_inst_adr                                                      "0x0035"
#define VC_DMA_BIST_ST_inst                                                          0x0035
#define VC_DMA_BIST_ST_bist_fail0_shift                                              (1)
#define VC_DMA_BIST_ST_bist_fail0_mask                                               (0x00000002)
#define VC_DMA_BIST_ST_bist_fail0(data)                                              (0x00000002&((data)<<1))
#define VC_DMA_BIST_ST_bist_fail0_src(data)                                          ((0x00000002&(data))>>1)
#define VC_DMA_BIST_ST_get_bist_fail0(data)                                          ((0x00000002&(data))>>1)
#define VC_DMA_BIST_ST_bist_done_shift                                               (0)
#define VC_DMA_BIST_ST_bist_done_mask                                                (0x00000001)
#define VC_DMA_BIST_ST_bist_done(data)                                               (0x00000001&((data)<<0))
#define VC_DMA_BIST_ST_bist_done_src(data)                                           ((0x00000001&(data))>>0)
#define VC_DMA_BIST_ST_get_bist_done(data)                                           ((0x00000001&(data))>>0)


#define VC_DMA_DRF_ST                                                                0x180010D8
#define VC_DMA_DRF_ST_reg_addr                                                       "0xB80010D8"
#define VC_DMA_DRF_ST_reg                                                            0xB80010D8
#define set_VC_DMA_DRF_ST_reg(data)   (*((volatile unsigned int*) VC_DMA_DRF_ST_reg)=data)
#define get_VC_DMA_DRF_ST_reg   (*((volatile unsigned int*) VC_DMA_DRF_ST_reg))
#define VC_DMA_DRF_ST_inst_adr                                                       "0x0036"
#define VC_DMA_DRF_ST_inst                                                           0x0036
#define VC_DMA_DRF_ST_drf_start_pause_shift                                          (16)
#define VC_DMA_DRF_ST_drf_start_pause_mask                                           (0x00010000)
#define VC_DMA_DRF_ST_drf_start_pause(data)                                          (0x00010000&((data)<<16))
#define VC_DMA_DRF_ST_drf_start_pause_src(data)                                      ((0x00010000&(data))>>16)
#define VC_DMA_DRF_ST_get_drf_start_pause(data)                                      ((0x00010000&(data))>>16)
#define VC_DMA_DRF_ST_drf_fail0_shift                                                (1)
#define VC_DMA_DRF_ST_drf_fail0_mask                                                 (0x00000002)
#define VC_DMA_DRF_ST_drf_fail0(data)                                                (0x00000002&((data)<<1))
#define VC_DMA_DRF_ST_drf_fail0_src(data)                                            ((0x00000002&(data))>>1)
#define VC_DMA_DRF_ST_get_drf_fail0(data)                                            ((0x00000002&(data))>>1)
#define VC_DMA_DRF_ST_drf_done_shift                                                 (0)
#define VC_DMA_DRF_ST_drf_done_mask                                                  (0x00000001)
#define VC_DMA_DRF_ST_drf_done(data)                                                 (0x00000001&((data)<<0))
#define VC_DMA_DRF_ST_drf_done_src(data)                                             ((0x00000001&(data))>>0)
#define VC_DMA_DRF_ST_get_drf_done(data)                                             ((0x00000001&(data))>>0)


#endif
