// This file is generated using the spec version 2.1.0, firmware template version 1.39and DVR_Parser_0.43
#ifndef _ATA0_REG_H_INCLUDED_
#define _ATA0_REG_H_INCLUDED_

//#define  _ATA0_USE_STRUCT
#ifdef _ATA0_USE_STRUCT

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    data:16;
}ata0_CMD0;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    data:8;
}ata0_CMD1;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    data:8;
}ata0_CMD2;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    data:8;
}ata0_CMD3;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    data:8;
}ata0_CMD4;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    data:8;
}ata0_CMD5;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    data:8;
}ata0_CMD6;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    data:8;
}ata0_CMD7;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    data:8;
}ata0_CTL6;

typedef struct
{
    unsigned int    trp:6;
    unsigned int    tmli:3;
    unsigned int    tss:4;
    unsigned int    udmahold:3;
    unsigned int    cyc:4;
    unsigned int    toutcyc:9;
    unsigned int    sample:1;
    unsigned int    mode:2;
}ata0_DEV0;

typedef struct
{
    unsigned int    trp:6;
    unsigned int    tmli:3;
    unsigned int    tss:4;
    unsigned int    udmahold:3;
    unsigned int    cyc:4;
    unsigned int    toutcyc:9;
    unsigned int    sample:1;
    unsigned int    mode:2;
}ata0_DEV1;

typedef struct
{
    unsigned int    t3d:5;
    unsigned int    t2d:6;
    unsigned int    t1d:5;
    unsigned int    t3r:5;
    unsigned int    t2r:6;
    unsigned int    t1r:5;
}ata0_PIO0;

typedef struct
{
    unsigned int    t3d:5;
    unsigned int    t2d:6;
    unsigned int    t1d:5;
    unsigned int    t3r:5;
    unsigned int    t2r:6;
    unsigned int    t1r:5;
}ata0_PIO1;

typedef struct
{
    unsigned int    t9:5;
    unsigned int    t8:6;
    unsigned int    t7:5;
    unsigned int    t6:5;
    unsigned int    t5:6;
    unsigned int    t4:5;
}ata0_DMA0;

typedef struct
{
    unsigned int    t9:5;
    unsigned int    t8:6;
    unsigned int    t7:5;
    unsigned int    t6:5;
    unsigned int    t5:6;
    unsigned int    t4:5;
}ata0_DMA1;

typedef struct
{
    unsigned int    cnt:32;
}ata0_DLEN;

typedef struct
{
    unsigned int    reserved_0:27;
    unsigned int    cpen:1;
    unsigned int    swap:1;
    unsigned int    write:1;
    unsigned int    device:1;
    unsigned int    reserved_1:1;
}ata0_CTL;

typedef struct
{
    unsigned int    reserved_0:31;
    unsigned int    go:1;
}ata0_GO;

typedef struct
{
    unsigned int    reserved_0:27;
    unsigned int    timeout:1;
    unsigned int    intrq:1;
    unsigned int    reserved_1:1;
    unsigned int    data_done:1;
    unsigned int    write_data:1;
}ata0_STATUS;

typedef struct
{
    unsigned int    reserved_0:27;
    unsigned int    timeout_en:1;
    unsigned int    intrq_en:1;
    unsigned int    reserved_1:1;
    unsigned int    data_done_en:1;
    unsigned int    write_data:1;
}ata0_EN;

typedef struct
{
    unsigned int    reserved_0:6;
    unsigned int    adr:26;
}ata0_INADR;

typedef struct
{
    unsigned int    reserved_0:6;
    unsigned int    adr:26;
}ata0_OUTADR;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    crc_ini:16;
}ata0_CRC;

typedef struct
{
    unsigned int    reserved_0:31;
    unsigned int    dev_rstn:1;
}ata0_RST;
#endif

#define ATA0_CMD0                                                     0x18012000
#define ATA0_CMD0_reg_addr                                            "0xB8012000"
#define ATA0_CMD0_reg                                                 0xB8012000
#define ATA0_CMD0_inst_addr                                           "0x0000"
#define ATA0_CMD0_inst                                                0x0000
#define ATA0_CMD0_data_shift                                          (0)
#define ATA0_CMD0_data_mask                                           (0x0000FFFF)
#define ATA0_CMD0_data(data)                                          (0x0000FFFF&(data))
#define ATA0_CMD0_get_data(data)                                      (0x0000FFFF&(data))

#define ATA0_CMD1                                                     0x18012004
#define ATA0_CMD1_reg_addr                                            "0xB8012004"
#define ATA0_CMD1_reg                                                 0xB8012004
#define ATA0_CMD1_inst_addr                                           "0x0001"
#define ATA0_CMD1_inst                                                0x0001
#define ATA0_CMD1_data_shift                                          (0)
#define ATA0_CMD1_data_mask                                           (0x000000FF)
#define ATA0_CMD1_data(data)                                          (0x000000FF&(data))
#define ATA0_CMD1_get_data(data)                                      (0x000000FF&(data))

#define ATA0_CMD2                                                     0x18012008
#define ATA0_CMD2_reg_addr                                            "0xB8012008"
#define ATA0_CMD2_reg                                                 0xB8012008
#define ATA0_CMD2_inst_addr                                           "0x0002"
#define ATA0_CMD2_inst                                                0x0002
#define ATA0_CMD2_data_shift                                          (0)
#define ATA0_CMD2_data_mask                                           (0x000000FF)
#define ATA0_CMD2_data(data)                                          (0x000000FF&(data))
#define ATA0_CMD2_get_data(data)                                      (0x000000FF&(data))

#define ATA0_CMD3                                                     0x1801200C
#define ATA0_CMD3_reg_addr                                            "0xB801200C"
#define ATA0_CMD3_reg                                                 0xB801200C
#define ATA0_CMD3_inst_addr                                           "0x0003"
#define ATA0_CMD3_inst                                                0x0003
#define ATA0_CMD3_data_shift                                          (0)
#define ATA0_CMD3_data_mask                                           (0x000000FF)
#define ATA0_CMD3_data(data)                                          (0x000000FF&(data))
#define ATA0_CMD3_get_data(data)                                      (0x000000FF&(data))

#define ATA0_CMD4                                                     0x18012010
#define ATA0_CMD4_reg_addr                                            "0xB8012010"
#define ATA0_CMD4_reg                                                 0xB8012010
#define ATA0_CMD4_inst_addr                                           "0x0004"
#define ATA0_CMD4_inst                                                0x0004
#define ATA0_CMD4_data_shift                                          (0)
#define ATA0_CMD4_data_mask                                           (0x000000FF)
#define ATA0_CMD4_data(data)                                          (0x000000FF&(data))
#define ATA0_CMD4_get_data(data)                                      (0x000000FF&(data))

#define ATA0_CMD5                                                     0x18012014
#define ATA0_CMD5_reg_addr                                            "0xB8012014"
#define ATA0_CMD5_reg                                                 0xB8012014
#define ATA0_CMD5_inst_addr                                           "0x0005"
#define ATA0_CMD5_inst                                                0x0005
#define ATA0_CMD5_data_shift                                          (0)
#define ATA0_CMD5_data_mask                                           (0x000000FF)
#define ATA0_CMD5_data(data)                                          (0x000000FF&(data))
#define ATA0_CMD5_get_data(data)                                      (0x000000FF&(data))

#define ATA0_CMD6                                                     0x18012018
#define ATA0_CMD6_reg_addr                                            "0xB8012018"
#define ATA0_CMD6_reg                                                 0xB8012018
#define ATA0_CMD6_inst_addr                                           "0x0006"
#define ATA0_CMD6_inst                                                0x0006
#define ATA0_CMD6_data_shift                                          (0)
#define ATA0_CMD6_data_mask                                           (0x000000FF)
#define ATA0_CMD6_data(data)                                          (0x000000FF&(data))
#define ATA0_CMD6_get_data(data)                                      (0x000000FF&(data))

#define ATA0_CMD7                                                     0x1801201C
#define ATA0_CMD7_reg_addr                                            "0xB801201C"
#define ATA0_CMD7_reg                                                 0xB801201C
#define ATA0_CMD7_inst_addr                                           "0x0007"
#define ATA0_CMD7_inst                                                0x0007
#define ATA0_CMD7_data_shift                                          (0)
#define ATA0_CMD7_data_mask                                           (0x000000FF)
#define ATA0_CMD7_data(data)                                          (0x000000FF&(data))
#define ATA0_CMD7_get_data(data)                                      (0x000000FF&(data))

#define ATA0_CTL6                                                     0x18012020
#define ATA0_CTL6_reg_addr                                            "0xB8012020"
#define ATA0_CTL6_reg                                                 0xB8012020
#define ATA0_CTL6_inst_addr                                           "0x0008"
#define ATA0_CTL6_inst                                                0x0008
#define ATA0_CTL6_data_shift                                          (0)
#define ATA0_CTL6_data_mask                                           (0x000000FF)
#define ATA0_CTL6_data(data)                                          (0x000000FF&(data))
#define ATA0_CTL6_get_data(data)                                      (0x000000FF&(data))

#define ATA0_DEV0                                                     0x18012024
#define ATA0_DEV0_reg_addr                                            "0xB8012024"
#define ATA0_DEV0_reg                                                 0xB8012024
#define ATA0_DEV0_inst_addr                                           "0x0009"
#define ATA0_DEV0_inst                                                0x0009
#define ATA0_DEV0_trp_shift                                           (26)
#define ATA0_DEV0_tmli_shift                                          (23)
#define ATA0_DEV0_tss_shift                                           (19)
#define ATA0_DEV0_udmahold_shift                                      (16)
#define ATA0_DEV0_cyc_shift                                           (12)
#define ATA0_DEV0_toutcyc_shift                                       (3)
#define ATA0_DEV0_sample_shift                                        (2)
#define ATA0_DEV0_mode_shift                                          (0)
#define ATA0_DEV0_trp_mask                                            (0xFC000000)
#define ATA0_DEV0_tmli_mask                                           (0x03800000)
#define ATA0_DEV0_tss_mask                                            (0x00780000)
#define ATA0_DEV0_udmahold_mask                                       (0x00070000)
#define ATA0_DEV0_cyc_mask                                            (0x0000F000)
#define ATA0_DEV0_toutcyc_mask                                        (0x00000FF8)
#define ATA0_DEV0_sample_mask                                         (0x00000004)
#define ATA0_DEV0_mode_mask                                           (0x00000003)
#define ATA0_DEV0_trp(data)                                           (0xFC000000&((data)<<26))
#define ATA0_DEV0_tmli(data)                                          (0x03800000&((data)<<23))
#define ATA0_DEV0_tss(data)                                           (0x00780000&((data)<<19))
#define ATA0_DEV0_udmahold(data)                                      (0x00070000&((data)<<16))
#define ATA0_DEV0_cyc(data)                                           (0x0000F000&((data)<<12))
#define ATA0_DEV0_toutcyc(data)                                       (0x00000FF8&((data)<<3))
#define ATA0_DEV0_sample(data)                                        (0x00000004&((data)<<2))
#define ATA0_DEV0_mode(data)                                          (0x00000003&(data))
#define ATA0_DEV0_get_trp(data)                                       ((0xFC000000&(data))>>26)
#define ATA0_DEV0_get_tmli(data)                                      ((0x03800000&(data))>>23)
#define ATA0_DEV0_get_tss(data)                                       ((0x00780000&(data))>>19)
#define ATA0_DEV0_get_udmahold(data)                                  ((0x00070000&(data))>>16)
#define ATA0_DEV0_get_cyc(data)                                       ((0x0000F000&(data))>>12)
#define ATA0_DEV0_get_toutcyc(data)                                   ((0x00000FF8&(data))>>3)
#define ATA0_DEV0_get_sample(data)                                    ((0x00000004&(data))>>2)
#define ATA0_DEV0_get_mode(data)                                      (0x00000003&(data))

#define ATA0_DEV1                                                     0x18012028
#define ATA0_DEV1_reg_addr                                            "0xB8012028"
#define ATA0_DEV1_reg                                                 0xB8012028
#define ATA0_DEV1_inst_addr                                           "0x000A"
#define ATA0_DEV1_inst                                                0x000A
#define ATA0_DEV1_trp_shift                                           (26)
#define ATA0_DEV1_tmli_shift                                          (23)
#define ATA0_DEV1_tss_shift                                           (19)
#define ATA0_DEV1_udmahold_shift                                      (16)
#define ATA0_DEV1_cyc_shift                                           (12)
#define ATA0_DEV1_toutcyc_shift                                       (3)
#define ATA0_DEV1_sample_shift                                        (2)
#define ATA0_DEV1_mode_shift                                          (0)
#define ATA0_DEV1_trp_mask                                            (0xFC000000)
#define ATA0_DEV1_tmli_mask                                           (0x03800000)
#define ATA0_DEV1_tss_mask                                            (0x00780000)
#define ATA0_DEV1_udmahold_mask                                       (0x00070000)
#define ATA0_DEV1_cyc_mask                                            (0x0000F000)
#define ATA0_DEV1_toutcyc_mask                                        (0x00000FF8)
#define ATA0_DEV1_sample_mask                                         (0x00000004)
#define ATA0_DEV1_mode_mask                                           (0x00000003)
#define ATA0_DEV1_trp(data)                                           (0xFC000000&((data)<<26))
#define ATA0_DEV1_tmli(data)                                          (0x03800000&((data)<<23))
#define ATA0_DEV1_tss(data)                                           (0x00780000&((data)<<19))
#define ATA0_DEV1_udmahold(data)                                      (0x00070000&((data)<<16))
#define ATA0_DEV1_cyc(data)                                           (0x0000F000&((data)<<12))
#define ATA0_DEV1_toutcyc(data)                                       (0x00000FF8&((data)<<3))
#define ATA0_DEV1_sample(data)                                        (0x00000004&((data)<<2))
#define ATA0_DEV1_mode(data)                                          (0x00000003&(data))
#define ATA0_DEV1_get_trp(data)                                       ((0xFC000000&(data))>>26)
#define ATA0_DEV1_get_tmli(data)                                      ((0x03800000&(data))>>23)
#define ATA0_DEV1_get_tss(data)                                       ((0x00780000&(data))>>19)
#define ATA0_DEV1_get_udmahold(data)                                  ((0x00070000&(data))>>16)
#define ATA0_DEV1_get_cyc(data)                                       ((0x0000F000&(data))>>12)
#define ATA0_DEV1_get_toutcyc(data)                                   ((0x00000FF8&(data))>>3)
#define ATA0_DEV1_get_sample(data)                                    ((0x00000004&(data))>>2)
#define ATA0_DEV1_get_mode(data)                                      (0x00000003&(data))

#define ATA0_PIO0                                                     0x1801202C
#define ATA0_PIO0_reg_addr                                            "0xB801202C"
#define ATA0_PIO0_reg                                                 0xB801202C
#define ATA0_PIO0_inst_addr                                           "0x000B"
#define ATA0_PIO0_inst                                                0x000B
#define ATA0_PIO0_t3d_shift                                           (27)
#define ATA0_PIO0_t2d_shift                                           (21)
#define ATA0_PIO0_t1d_shift                                           (16)
#define ATA0_PIO0_t3r_shift                                           (11)
#define ATA0_PIO0_t2r_shift                                           (5)
#define ATA0_PIO0_t1r_shift                                           (0)
#define ATA0_PIO0_t3d_mask                                            (0xF8000000)
#define ATA0_PIO0_t2d_mask                                            (0x07E00000)
#define ATA0_PIO0_t1d_mask                                            (0x001F0000)
#define ATA0_PIO0_t3r_mask                                            (0x0000F800)
#define ATA0_PIO0_t2r_mask                                            (0x000007E0)
#define ATA0_PIO0_t1r_mask                                            (0x0000001F)
#define ATA0_PIO0_t3d(data)                                           (0xF8000000&((data)<<27))
#define ATA0_PIO0_t2d(data)                                           (0x07E00000&((data)<<21))
#define ATA0_PIO0_t1d(data)                                           (0x001F0000&((data)<<16))
#define ATA0_PIO0_t3r(data)                                           (0x0000F800&((data)<<11))
#define ATA0_PIO0_t2r(data)                                           (0x000007E0&((data)<<5))
#define ATA0_PIO0_t1r(data)                                           (0x0000001F&(data))
#define ATA0_PIO0_get_t3d(data)                                       ((0xF8000000&(data))>>27)
#define ATA0_PIO0_get_t2d(data)                                       ((0x07E00000&(data))>>21)
#define ATA0_PIO0_get_t1d(data)                                       ((0x001F0000&(data))>>16)
#define ATA0_PIO0_get_t3r(data)                                       ((0x0000F800&(data))>>11)
#define ATA0_PIO0_get_t2r(data)                                       ((0x000007E0&(data))>>5)
#define ATA0_PIO0_get_t1r(data)                                       (0x0000001F&(data))

#define ATA0_PIO1                                                     0x18012030
#define ATA0_PIO1_reg_addr                                            "0xB8012030"
#define ATA0_PIO1_reg                                                 0xB8012030
#define ATA0_PIO1_inst_addr                                           "0x000C"
#define ATA0_PIO1_inst                                                0x000C
#define ATA0_PIO1_t3d_shift                                           (27)
#define ATA0_PIO1_t2d_shift                                           (21)
#define ATA0_PIO1_t1d_shift                                           (16)
#define ATA0_PIO1_t3r_shift                                           (11)
#define ATA0_PIO1_t2r_shift                                           (5)
#define ATA0_PIO1_t1r_shift                                           (0)
#define ATA0_PIO1_t3d_mask                                            (0xF8000000)
#define ATA0_PIO1_t2d_mask                                            (0x07E00000)
#define ATA0_PIO1_t1d_mask                                            (0x001F0000)
#define ATA0_PIO1_t3r_mask                                            (0x0000F800)
#define ATA0_PIO1_t2r_mask                                            (0x000007E0)
#define ATA0_PIO1_t1r_mask                                            (0x0000001F)
#define ATA0_PIO1_t3d(data)                                           (0xF8000000&((data)<<27))
#define ATA0_PIO1_t2d(data)                                           (0x07E00000&((data)<<21))
#define ATA0_PIO1_t1d(data)                                           (0x001F0000&((data)<<16))
#define ATA0_PIO1_t3r(data)                                           (0x0000F800&((data)<<11))
#define ATA0_PIO1_t2r(data)                                           (0x000007E0&((data)<<5))
#define ATA0_PIO1_t1r(data)                                           (0x0000001F&(data))
#define ATA0_PIO1_get_t3d(data)                                       ((0xF8000000&(data))>>27)
#define ATA0_PIO1_get_t2d(data)                                       ((0x07E00000&(data))>>21)
#define ATA0_PIO1_get_t1d(data)                                       ((0x001F0000&(data))>>16)
#define ATA0_PIO1_get_t3r(data)                                       ((0x0000F800&(data))>>11)
#define ATA0_PIO1_get_t2r(data)                                       ((0x000007E0&(data))>>5)
#define ATA0_PIO1_get_t1r(data)                                       (0x0000001F&(data))

#define ATA0_DMA0                                                     0x18012034
#define ATA0_DMA0_reg_addr                                            "0xB8012034"
#define ATA0_DMA0_reg                                                 0xB8012034
#define ATA0_DMA0_inst_addr                                           "0x000D"
#define ATA0_DMA0_inst                                                0x000D
#define ATA0_DMA0_t9_shift                                            (27)
#define ATA0_DMA0_t8_shift                                            (21)
#define ATA0_DMA0_t7_shift                                            (16)
#define ATA0_DMA0_t6_shift                                            (11)
#define ATA0_DMA0_t5_shift                                            (5)
#define ATA0_DMA0_t4_shift                                            (0)
#define ATA0_DMA0_t9_mask                                             (0xF8000000)
#define ATA0_DMA0_t8_mask                                             (0x07E00000)
#define ATA0_DMA0_t7_mask                                             (0x001F0000)
#define ATA0_DMA0_t6_mask                                             (0x0000F800)
#define ATA0_DMA0_t5_mask                                             (0x000007E0)
#define ATA0_DMA0_t4_mask                                             (0x0000001F)
#define ATA0_DMA0_t9(data)                                            (0xF8000000&((data)<<27))
#define ATA0_DMA0_t8(data)                                            (0x07E00000&((data)<<21))
#define ATA0_DMA0_t7(data)                                            (0x001F0000&((data)<<16))
#define ATA0_DMA0_t6(data)                                            (0x0000F800&((data)<<11))
#define ATA0_DMA0_t5(data)                                            (0x000007E0&((data)<<5))
#define ATA0_DMA0_t4(data)                                            (0x0000001F&(data))
#define ATA0_DMA0_get_t9(data)                                        ((0xF8000000&(data))>>27)
#define ATA0_DMA0_get_t8(data)                                        ((0x07E00000&(data))>>21)
#define ATA0_DMA0_get_t7(data)                                        ((0x001F0000&(data))>>16)
#define ATA0_DMA0_get_t6(data)                                        ((0x0000F800&(data))>>11)
#define ATA0_DMA0_get_t5(data)                                        ((0x000007E0&(data))>>5)
#define ATA0_DMA0_get_t4(data)                                        (0x0000001F&(data))

#define ATA0_DMA1                                                     0x18012038
#define ATA0_DMA1_reg_addr                                            "0xB8012038"
#define ATA0_DMA1_reg                                                 0xB8012038
#define ATA0_DMA1_inst_addr                                           "0x000E"
#define ATA0_DMA1_inst                                                0x000E
#define ATA0_DMA1_t9_shift                                            (27)
#define ATA0_DMA1_t8_shift                                            (21)
#define ATA0_DMA1_t7_shift                                            (16)
#define ATA0_DMA1_t6_shift                                            (11)
#define ATA0_DMA1_t5_shift                                            (5)
#define ATA0_DMA1_t4_shift                                            (0)
#define ATA0_DMA1_t9_mask                                             (0xF8000000)
#define ATA0_DMA1_t8_mask                                             (0x07E00000)
#define ATA0_DMA1_t7_mask                                             (0x001F0000)
#define ATA0_DMA1_t6_mask                                             (0x0000F800)
#define ATA0_DMA1_t5_mask                                             (0x000007E0)
#define ATA0_DMA1_t4_mask                                             (0x0000001F)
#define ATA0_DMA1_t9(data)                                            (0xF8000000&((data)<<27))
#define ATA0_DMA1_t8(data)                                            (0x07E00000&((data)<<21))
#define ATA0_DMA1_t7(data)                                            (0x001F0000&((data)<<16))
#define ATA0_DMA1_t6(data)                                            (0x0000F800&((data)<<11))
#define ATA0_DMA1_t5(data)                                            (0x000007E0&((data)<<5))
#define ATA0_DMA1_t4(data)                                            (0x0000001F&(data))
#define ATA0_DMA1_get_t9(data)                                        ((0xF8000000&(data))>>27)
#define ATA0_DMA1_get_t8(data)                                        ((0x07E00000&(data))>>21)
#define ATA0_DMA1_get_t7(data)                                        ((0x001F0000&(data))>>16)
#define ATA0_DMA1_get_t6(data)                                        ((0x0000F800&(data))>>11)
#define ATA0_DMA1_get_t5(data)                                        ((0x000007E0&(data))>>5)
#define ATA0_DMA1_get_t4(data)                                        (0x0000001F&(data))

#define ATA0_DLEN                                                     0x1801203C
#define ATA0_DLEN_reg_addr                                            "0xB801203C"
#define ATA0_DLEN_reg                                                 0xB801203C
#define ATA0_DLEN_inst_addr                                           "0x000F"
#define ATA0_DLEN_inst                                                0x000F
#define ATA0_DLEN_cnt_shift                                           (0)
#define ATA0_DLEN_cnt_mask                                            (0xFFFFFFFF)
#define ATA0_DLEN_cnt(data)                                           (0xFFFFFFFF&(data))
#define ATA0_DLEN_get_cnt(data)                                       (0xFFFFFFFF&(data))

#define ATA0_CTL                                                      0x18012040
#define ATA0_CTL_reg_addr                                             "0xB8012040"
#define ATA0_CTL_reg                                                  0xB8012040
#define ATA0_CTL_inst_addr                                            "0x0010"
#define ATA0_CTL_inst                                                 0x0010
#define ATA0_CTL_cpen_shift                                           (4)
#define ATA0_CTL_swap_shift                                           (3)
#define ATA0_CTL_write_shift                                          (2)
#define ATA0_CTL_device_shift                                         (1)
#define ATA0_CTL_cpen_mask                                            (0x00000010)
#define ATA0_CTL_swap_mask                                            (0x00000008)
#define ATA0_CTL_write_mask                                           (0x00000004)
#define ATA0_CTL_device_mask                                          (0x00000002)
#define ATA0_CTL_cpen(data)                                           (0x00000010&((data)<<4))
#define ATA0_CTL_swap(data)                                           (0x00000008&((data)<<3))
#define ATA0_CTL_write(data)                                          (0x00000004&((data)<<2))
#define ATA0_CTL_device(data)                                         (0x00000002&((data)<<1))
#define ATA0_CTL_get_cpen(data)                                       ((0x00000010&(data))>>4)
#define ATA0_CTL_get_swap(data)                                       ((0x00000008&(data))>>3)
#define ATA0_CTL_get_write(data)                                      ((0x00000004&(data))>>2)
#define ATA0_CTL_get_device(data)                                     ((0x00000002&(data))>>1)

#define ATA0_GO                                                       0x18012044
#define ATA0_GO_reg_addr                                              "0xB8012044"
#define ATA0_GO_reg                                                   0xB8012044
#define ATA0_GO_inst_addr                                             "0x0011"
#define ATA0_GO_inst                                                  0x0011
#define ATA0_GO_go_shift                                              (0)
#define ATA0_GO_go_mask                                               (0x00000001)
#define ATA0_GO_go(data)                                              (0x00000001&(data))
#define ATA0_GO_get_go(data)                                          (0x00000001&(data))

#define ATA0_STATUS                                                   0x18012048
#define ATA0_STATUS_reg_addr                                          "0xB8012048"
#define ATA0_STATUS_reg                                               0xB8012048
#define ATA0_STATUS_inst_addr                                         "0x0012"
#define ATA0_STATUS_inst                                              0x0012
#define ATA0_STATUS_timeout_shift                                     (4)
#define ATA0_STATUS_intrq_shift                                       (3)
#define ATA0_STATUS_data_done_shift                                   (1)
#define ATA0_STATUS_write_data_shift                                  (0)
#define ATA0_STATUS_timeout_mask                                      (0x00000010)
#define ATA0_STATUS_intrq_mask                                        (0x00000008)
#define ATA0_STATUS_data_done_mask                                    (0x00000002)
#define ATA0_STATUS_write_data_mask                                   (0x00000001)
#define ATA0_STATUS_timeout(data)                                     (0x00000010&((data)<<4))
#define ATA0_STATUS_intrq(data)                                       (0x00000008&((data)<<3))
#define ATA0_STATUS_data_done(data)                                   (0x00000002&((data)<<1))
#define ATA0_STATUS_write_data(data)                                  (0x00000001&(data))
#define ATA0_STATUS_get_timeout(data)                                 ((0x00000010&(data))>>4)
#define ATA0_STATUS_get_intrq(data)                                   ((0x00000008&(data))>>3)
#define ATA0_STATUS_get_data_done(data)                               ((0x00000002&(data))>>1)
#define ATA0_STATUS_get_write_data(data)                              (0x00000001&(data))

#define ATA0_EN                                                       0x1801204C
#define ATA0_EN_reg_addr                                              "0xB801204C"
#define ATA0_EN_reg                                                   0xB801204C
#define ATA0_EN_inst_addr                                             "0x0013"
#define ATA0_EN_inst                                                  0x0013
#define ATA0_EN_timeout_en_shift                                      (4)
#define ATA0_EN_intrq_en_shift                                        (3)
#define ATA0_EN_data_done_en_shift                                    (1)
#define ATA0_EN_write_data_shift                                      (0)
#define ATA0_EN_timeout_en_mask                                       (0x00000010)
#define ATA0_EN_intrq_en_mask                                         (0x00000008)
#define ATA0_EN_data_done_en_mask                                     (0x00000002)
#define ATA0_EN_write_data_mask                                       (0x00000001)
#define ATA0_EN_timeout_en(data)                                      (0x00000010&((data)<<4))
#define ATA0_EN_intrq_en(data)                                        (0x00000008&((data)<<3))
#define ATA0_EN_data_done_en(data)                                    (0x00000002&((data)<<1))
#define ATA0_EN_write_data(data)                                      (0x00000001&(data))
#define ATA0_EN_get_timeout_en(data)                                  ((0x00000010&(data))>>4)
#define ATA0_EN_get_intrq_en(data)                                    ((0x00000008&(data))>>3)
#define ATA0_EN_get_data_done_en(data)                                ((0x00000002&(data))>>1)
#define ATA0_EN_get_write_data(data)                                  (0x00000001&(data))

#define ATA0_INADR                                                    0x18012050
#define ATA0_INADR_reg_addr                                           "0xB8012050"
#define ATA0_INADR_reg                                                0xB8012050
#define ATA0_INADR_inst_addr                                          "0x0014"
#define ATA0_INADR_inst                                               0x0014
#define ATA0_INADR_adr_shift                                          (0)
#define ATA0_INADR_adr_mask                                           (0x03FFFFFF)
#define ATA0_INADR_adr(data)                                          (0x03FFFFFF&(data))
#define ATA0_INADR_get_adr(data)                                      (0x03FFFFFF&(data))

#define ATA0_OUTADR                                                   0x18012054
#define ATA0_OUTADR_reg_addr                                          "0xB8012054"
#define ATA0_OUTADR_reg                                               0xB8012054
#define ATA0_OUTADR_inst_addr                                         "0x0015"
#define ATA0_OUTADR_inst                                              0x0015
#define ATA0_OUTADR_adr_shift                                         (0)
#define ATA0_OUTADR_adr_mask                                          (0x03FFFFFF)
#define ATA0_OUTADR_adr(data)                                         (0x03FFFFFF&(data))
#define ATA0_OUTADR_get_adr(data)                                     (0x03FFFFFF&(data))

#define ATA0_CRC                                                      0x18012058
#define ATA0_CRC_reg_addr                                             "0xB8012058"
#define ATA0_CRC_reg                                                  0xB8012058
#define ATA0_CRC_inst_addr                                            "0x0016"
#define ATA0_CRC_inst                                                 0x0016
#define ATA0_CRC_crc_ini_shift                                        (0)
#define ATA0_CRC_crc_ini_mask                                         (0x0000FFFF)
#define ATA0_CRC_crc_ini(data)                                        (0x0000FFFF&(data))
#define ATA0_CRC_get_crc_ini(data)                                    (0x0000FFFF&(data))

#define ATA0_RST                                                      0x1801205C
#define ATA0_RST_reg_addr                                             "0xB801205C"
#define ATA0_RST_reg                                                  0xB801205C
#define ATA0_RST_inst_addr                                            "0x0017"
#define ATA0_RST_inst                                                 0x0017
#define ATA0_RST_dev_rstn_shift                                       (0)
#define ATA0_RST_dev_rstn_mask                                        (0x00000001)
#define ATA0_RST_dev_rstn(data)                                       (0x00000001&(data))
#define ATA0_RST_get_dev_rstn(data)                                   (0x00000001&(data))
#endif
