// This file is generated using the spec version 1.39, firmware template version 1.39and SRIF Parser                                                                                source code SVN rev:793                    Version flow no.:1.1.44
#ifndef _CEC_REG_H_INCLUDED_
#define _CEC_REG_H_INCLUDED_

//#define  _DEFAULT_USE_STRUCT
#ifdef _DEFAULT_USE_STRUCT

typedef struct
{
    unsigned int    cec_mode:2;
    unsigned int    reserved_0:1;
    unsigned int    test_mode_pad_en:1;
    unsigned int    logical_addr:4;
    unsigned int    timer_div:8;
    unsigned int    pre_div:8;
    unsigned int    unreg_ack_en:1;
    unsigned int    reserved_1:1;
    unsigned int    cdc_arbitration_en:1;
    unsigned int    test_mode_pad_data:5;
}CEC_cr0;

typedef struct
{
    unsigned int    cec_pad_in:1;
    unsigned int    reserved_0:11;
    unsigned int    dummy18007504_19_12:8;
    unsigned int    clear_cec_int:1;
    unsigned int    wt_cnt:6;
    unsigned int    lattest:1;
    unsigned int    retry_no:4;
}CEC_rtcr0;

typedef struct
{
    unsigned int    broadcast_addr:1;
    unsigned int    reserved_0:15;
    unsigned int    rx_en:1;
    unsigned int    rx_rst:1;
    unsigned int    rx_continuous:1;
    unsigned int    rx_int_en:1;
    unsigned int    init_addr:4;
    unsigned int    rx_eom:1;
    unsigned int    rx_int:1;
    unsigned int    rx_fifo_ov:1;
    unsigned int    rx_fifo_cnt:5;
}CEC_rxcr0;

typedef struct
{
    unsigned int    reserved_0:11;
    unsigned int    tx_addr_en:1;
    unsigned int    tx_addr:4;
    unsigned int    tx_en:1;
    unsigned int    tx_rst:1;
    unsigned int    tx_continuous:1;
    unsigned int    tx_int_en:1;
    unsigned int    dest_addr:4;
    unsigned int    tx_eom:1;
    unsigned int    tx_int:1;
    unsigned int    tx_fifo_ud:1;
    unsigned int    tx_fifo_cnt:5;
}CEC_txcr0;

typedef struct
{
    unsigned int    reserved_0:25;
    unsigned int    tx_add_cnt:1;
    unsigned int    rx_sub_cnt:1;
    unsigned int    fifo_cnt:5;
}CEC_txdr0;

typedef struct
{
    unsigned int    tx_fifo_0:8;
    unsigned int    tx_fifo_1:8;
    unsigned int    tx_fifo_2:8;
    unsigned int    tx_fifo_3:8;
}CEC_txdr1;

typedef struct
{
    unsigned int    tx_fifo_4:8;
    unsigned int    tx_fifo_5:8;
    unsigned int    tx_fifo_6:8;
    unsigned int    tx_fifo_7:8;
}CEC_txdr2;

typedef struct
{
    unsigned int    tx_fifo_8:8;
    unsigned int    tx_fifo_9:8;
    unsigned int    tx_fifo_a:8;
    unsigned int    tx_fifo_b:8;
}CEC_txdr3;

typedef struct
{
    unsigned int    tx_fifo_c:8;
    unsigned int    tx_fifo_d:8;
    unsigned int    tx_fifo_e:8;
    unsigned int    tx_fifo_f:8;
}CEC_txdr4;

typedef struct
{
    unsigned int    rx_fifo_0:8;
    unsigned int    rx_fifo_1:8;
    unsigned int    rx_fifo_2:8;
    unsigned int    rx_fifo_3:8;
}CEC_rxdr1;

typedef struct
{
    unsigned int    rx_fifo_4:8;
    unsigned int    rx_fifo_5:8;
    unsigned int    rx_fifo_6:8;
    unsigned int    rx_fifo_7:8;
}CEC_rxdr2;

typedef struct
{
    unsigned int    rx_fifo_8:8;
    unsigned int    rx_fifo_9:8;
    unsigned int    rx_fifo_a:8;
    unsigned int    rx_fifo_b:8;
}CEC_rxdr3;

typedef struct
{
    unsigned int    rx_fifo_c:8;
    unsigned int    rx_fifo_d:8;
    unsigned int    rx_fifo_e:8;
    unsigned int    rx_fifo_f:8;
}CEC_rxdr4;

typedef struct
{
    unsigned int    rx_start_low:8;
    unsigned int    rx_start_period:8;
    unsigned int    rx_data_sample:8;
    unsigned int    rx_data_period:8;
}CEC_rxtcr0;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    tx_start_low:8;
    unsigned int    tx_start_high:8;
}CEC_txtcr0;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    tx_data_low:8;
    unsigned int    tx_data_01:8;
    unsigned int    tx_data_high:8;
}CEC_txtcr1;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    compare_opcode_01:8;
}GDI_cec_compare_opcode_01;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    send_opcode_01:8;
}GDI_cec_send_opcode_01;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    reserved_1:6;
    unsigned int    operand_number_01:2;
}GDI_cec_send_operand_number_01;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    operand_01:8;
}GDI_cec_operand_01;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    operand_02:8;
}GDI_cec_operand_02;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    operand_03:8;
}GDI_cec_operand_03;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    compare_opcode_02:8;
}GDI_cec_compare_opcode_02;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    send_opcode_02:8;
}GDI_cec_send_opcode_02;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    reserved_1:6;
    unsigned int    operand_number_02:2;
}GDI_cec_send_operand_number_02;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    operand_04:8;
}GDI_cec_operand_04;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    operand_05:8;
}GDI_cec_operand_05;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    operand_06:8;
}GDI_cec_operand_06;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    compare_opcode_03:8;
}GDI_cec_compare_opcode_03;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    send_opcode_03:8;
}GDI_cec_send_opcode_03;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    reserved_1:6;
    unsigned int    operand_number_03:2;
}GDI_cec_send_operand_number_03;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    operand_07:8;
}GDI_cec_operand_07;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    operand_08:8;
}GDI_cec_operand_08;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    operand_09:8;
}GDI_cec_operand_09;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    compare_opcode_04:8;
}GDI_cec_compare_opcode_04;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    send_opcode_04:8;
}GDI_cec_send_opcode_04;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    reserved_1:6;
    unsigned int    operand_number_04:2;
}GDI_cec_send_operand_number_04;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    operand_10:8;
}GDI_cec_operand_10;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    operand_11:8;
}GDI_cec_operand_11;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    operand_12:8;
}GDI_cec_operand_12;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    compare_opcode_05:8;
}GDI_cec_compare_opcode_05;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    compare_opcode_06:8;
}GDI_cec_compare_opcode_06;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    compare_opcode_07:8;
}GDI_cec_compare_opcode_07;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    compare_opcode_08:8;
}GDI_cec_compare_opcode_08;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    compare_opcode_09:8;
}GDI_cec_compare_opcode_09;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    compare_opcode_10:8;
}GDI_cec_compare_opcode_10;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    compare_opcode_11:8;
}GDI_cec_compare_opcode_11;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    compare_opcode_12:8;
}GDI_cec_compare_opcode_12;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    compare_opcode_13:8;
}GDI_cec_compare_opcode_13;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    compare_opcode_14:8;
}GDI_cec_compare_opcode_14;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    compare_opcode_15:8;
}GDI_cec_compare_opcode_15;

typedef struct
{
    unsigned int    reserved_0:17;
    unsigned int    en_compare_opcode_15:1;
    unsigned int    en_compare_opcode_14:1;
    unsigned int    en_compare_opcode_13:1;
    unsigned int    en_compare_opcode_12:1;
    unsigned int    en_compare_opcode_11:1;
    unsigned int    en_compare_opcode_10:1;
    unsigned int    en_compare_opcode_09:1;
    unsigned int    en_compare_opcode_08:1;
    unsigned int    en_compare_opcode_07:1;
    unsigned int    en_compare_opcode_06:1;
    unsigned int    en_compare_opcode_05:1;
    unsigned int    en_compare_opcode_04:1;
    unsigned int    en_compare_opcode_03:1;
    unsigned int    en_compare_opcode_02:1;
    unsigned int    en_compare_opcode_01:1;
}GDI_cec_opcode_enable;

typedef struct
{
    unsigned int    irq_pending:1;
    unsigned int    reserved_0:5;
    unsigned int    cec_msg_status_01:1;
    unsigned int    cec_msg_status_02:1;
    unsigned int    reserved_1:15;
    unsigned int    irq_by_cec_receive_special_cmd:1;
    unsigned int    reserved_2:4;
    unsigned int    reserved_3:4;
}GDI_power_saving_mode;

typedef struct
{
    unsigned int    reserved_0:31;
    unsigned int    vcckoff_33v:1;
}CEC_analog_01;
#endif


#define CEC_CR0                                                       0x18007500
#define CEC_CR0_reg_addr                                              "0xb8007500"
#define CEC_CR0_reg                                                   0xb8007500
#define CEC_CR0_inst_addr                                             "0x0380"
#define CEC_CR0_inst                                                  0x0380
#define CEC_CR0_cec_mode_shift                                        (30)
#define CEC_CR0_test_mode_pad_en_shift                                (28)
#define CEC_CR0_logical_addr_shift                                    (24)
#define CEC_CR0_timer_div_shift                                       (16)
#define CEC_CR0_pre_div_shift                                         (8)
#define CEC_CR0_unreg_ack_en_shift                                    (7)
#define CEC_CR0_cdc_arbitration_en_shift                              (5)
#define CEC_CR0_test_mode_pad_data_shift                              (0)
#define CEC_CR0_cec_mode_mask                                         (0xC0000000)
#define CEC_CR0_test_mode_pad_en_mask                                 (0x10000000)
#define CEC_CR0_logical_addr_mask                                     (0x0F000000)
#define CEC_CR0_timer_div_mask                                        (0x00FF0000)
#define CEC_CR0_pre_div_mask                                          (0x0000FF00)
#define CEC_CR0_unreg_ack_en_mask                                     (0x00000080)
#define CEC_CR0_cdc_arbitration_en_mask                               (0x00000020)
#define CEC_CR0_test_mode_pad_data_mask                               (0x0000001F)
#define CEC_CR0_cec_mode(data)                                        (0xC0000000&((data)<<30))
#define CEC_CR0_test_mode_pad_en(data)                                (0x10000000&((data)<<28))
#define CEC_CR0_logical_addr(data)                                    (0x0F000000&((data)<<24))
#define CEC_CR0_timer_div(data)                                       (0x00FF0000&((data)<<16))
#define CEC_CR0_pre_div(data)                                         (0x0000FF00&((data)<<8))
#define CEC_CR0_unreg_ack_en(data)                                    (0x00000080&((data)<<7))
#define CEC_CR0_cdc_arbitration_en(data)                              (0x00000020&((data)<<5))
#define CEC_CR0_test_mode_pad_data(data)                              (0x0000001F&(data))
#define CEC_CR0_get_cec_mode(data)                                    ((0xC0000000&(data))>>30)
#define CEC_CR0_get_test_mode_pad_en(data)                            ((0x10000000&(data))>>28)
#define CEC_CR0_get_logical_addr(data)                                ((0x0F000000&(data))>>24)
#define CEC_CR0_get_timer_div(data)                                   ((0x00FF0000&(data))>>16)
#define CEC_CR0_get_pre_div(data)                                     ((0x0000FF00&(data))>>8)
#define CEC_CR0_get_unreg_ack_en(data)                                ((0x00000080&(data))>>7)
#define CEC_CR0_get_cdc_arbitration_en(data)                          ((0x00000020&(data))>>5)
#define CEC_CR0_get_test_mode_pad_data(data)                          (0x0000001F&(data))


#define CEC_RTCR0                                                     0x18007504
#define CEC_RTCR0_reg_addr                                            "0xb8007504"
#define CEC_RTCR0_reg                                                 0xb8007504
#define CEC_RTCR0_inst_addr                                           "0x0381"
#define CEC_RTCR0_inst                                                0x0381
#define CEC_RTCR0_cec_pad_in_shift                                    (31)
#define CEC_RTCR0_dummy18007504_19_12_shift                           (12)
#define CEC_RTCR0_clear_cec_int_shift                                 (11)
#define CEC_RTCR0_wt_cnt_shift                                        (5)
#define CEC_RTCR0_lattest_shift                                       (4)
#define CEC_RTCR0_retry_no_shift                                      (0)
#define CEC_RTCR0_cec_pad_in_mask                                     (0x80000000)
#define CEC_RTCR0_dummy18007504_19_12_mask                            (0x000FF000)
#define CEC_RTCR0_clear_cec_int_mask                                  (0x00000800)
#define CEC_RTCR0_wt_cnt_mask                                         (0x000007E0)
#define CEC_RTCR0_lattest_mask                                        (0x00000010)
#define CEC_RTCR0_retry_no_mask                                       (0x0000000F)
#define CEC_RTCR0_cec_pad_in(data)                                    (0x80000000&((data)<<31))
#define CEC_RTCR0_dummy18007504_19_12(data)                           (0x000FF000&((data)<<12))
#define CEC_RTCR0_clear_cec_int(data)                                 (0x00000800&((data)<<11))
#define CEC_RTCR0_wt_cnt(data)                                        (0x000007E0&((data)<<5))
#define CEC_RTCR0_lattest(data)                                       (0x00000010&((data)<<4))
#define CEC_RTCR0_retry_no(data)                                      (0x0000000F&(data))
#define CEC_RTCR0_get_cec_pad_in(data)                                ((0x80000000&(data))>>31)
#define CEC_RTCR0_get_dummy18007504_19_12(data)                       ((0x000FF000&(data))>>12)
#define CEC_RTCR0_get_clear_cec_int(data)                             ((0x00000800&(data))>>11)
#define CEC_RTCR0_get_wt_cnt(data)                                    ((0x000007E0&(data))>>5)
#define CEC_RTCR0_get_lattest(data)                                   ((0x00000010&(data))>>4)
#define CEC_RTCR0_get_retry_no(data)                                  (0x0000000F&(data))


#define CEC_RXCR0                                                     0x18007508
#define CEC_RXCR0_reg_addr                                            "0xb8007508"
#define CEC_RXCR0_reg                                                 0xb8007508
#define CEC_RXCR0_inst_addr                                           "0x0382"
#define CEC_RXCR0_inst                                                0x0382
#define CEC_RXCR0_broadcast_addr_shift                                (31)
#define CEC_RXCR0_rx_en_shift                                         (15)
#define CEC_RXCR0_rx_rst_shift                                        (14)
#define CEC_RXCR0_rx_continuous_shift                                 (13)
#define CEC_RXCR0_rx_int_en_shift                                     (12)
#define CEC_RXCR0_init_addr_shift                                     (8)
#define CEC_RXCR0_rx_eom_shift                                        (7)
#define CEC_RXCR0_rx_int_shift                                        (6)
#define CEC_RXCR0_rx_fifo_ov_shift                                    (5)
#define CEC_RXCR0_rx_fifo_cnt_shift                                   (0)
#define CEC_RXCR0_broadcast_addr_mask                                 (0x80000000)
#define CEC_RXCR0_rx_en_mask                                          (0x00008000)
#define CEC_RXCR0_rx_rst_mask                                         (0x00004000)
#define CEC_RXCR0_rx_continuous_mask                                  (0x00002000)
#define CEC_RXCR0_rx_int_en_mask                                      (0x00001000)
#define CEC_RXCR0_init_addr_mask                                      (0x00000F00)
#define CEC_RXCR0_rx_eom_mask                                         (0x00000080)
#define CEC_RXCR0_rx_int_mask                                         (0x00000040)
#define CEC_RXCR0_rx_fifo_ov_mask                                     (0x00000020)
#define CEC_RXCR0_rx_fifo_cnt_mask                                    (0x0000001F)
#define CEC_RXCR0_broadcast_addr(data)                                (0x80000000&((data)<<31))
#define CEC_RXCR0_rx_en(data)                                         (0x00008000&((data)<<15))
#define CEC_RXCR0_rx_rst(data)                                        (0x00004000&((data)<<14))
#define CEC_RXCR0_rx_continuous(data)                                 (0x00002000&((data)<<13))
#define CEC_RXCR0_rx_int_en(data)                                     (0x00001000&((data)<<12))
#define CEC_RXCR0_init_addr(data)                                     (0x00000F00&((data)<<8))
#define CEC_RXCR0_rx_eom(data)                                        (0x00000080&((data)<<7))
#define CEC_RXCR0_rx_int(data)                                        (0x00000040&((data)<<6))
#define CEC_RXCR0_rx_fifo_ov(data)                                    (0x00000020&((data)<<5))
#define CEC_RXCR0_rx_fifo_cnt(data)                                   (0x0000001F&(data))
#define CEC_RXCR0_get_broadcast_addr(data)                            ((0x80000000&(data))>>31)
#define CEC_RXCR0_get_rx_en(data)                                     ((0x00008000&(data))>>15)
#define CEC_RXCR0_get_rx_rst(data)                                    ((0x00004000&(data))>>14)
#define CEC_RXCR0_get_rx_continuous(data)                             ((0x00002000&(data))>>13)
#define CEC_RXCR0_get_rx_int_en(data)                                 ((0x00001000&(data))>>12)
#define CEC_RXCR0_get_init_addr(data)                                 ((0x00000F00&(data))>>8)
#define CEC_RXCR0_get_rx_eom(data)                                    ((0x00000080&(data))>>7)
#define CEC_RXCR0_get_rx_int(data)                                    ((0x00000040&(data))>>6)
#define CEC_RXCR0_get_rx_fifo_ov(data)                                ((0x00000020&(data))>>5)
#define CEC_RXCR0_get_rx_fifo_cnt(data)                               (0x0000001F&(data))


#define CEC_TXCR0                                                     0x1800750c
#define CEC_TXCR0_reg_addr                                            "0xb800750c"
#define CEC_TXCR0_reg                                                 0xb800750c
#define CEC_TXCR0_inst_addr                                           "0x0383"
#define CEC_TXCR0_inst                                                0x0383
#define CEC_TXCR0_tx_addr_en_shift                                    (20)
#define CEC_TXCR0_tx_addr_shift                                       (16)
#define CEC_TXCR0_tx_en_shift                                         (15)
#define CEC_TXCR0_tx_rst_shift                                        (14)
#define CEC_TXCR0_tx_continuous_shift                                 (13)
#define CEC_TXCR0_tx_int_en_shift                                     (12)
#define CEC_TXCR0_dest_addr_shift                                     (8)
#define CEC_TXCR0_tx_eom_shift                                        (7)
#define CEC_TXCR0_tx_int_shift                                        (6)
#define CEC_TXCR0_tx_fifo_ud_shift                                    (5)
#define CEC_TXCR0_tx_fifo_cnt_shift                                   (0)
#define CEC_TXCR0_tx_addr_en_mask                                     (0x00100000)
#define CEC_TXCR0_tx_addr_mask                                        (0x000F0000)
#define CEC_TXCR0_tx_en_mask                                          (0x00008000)
#define CEC_TXCR0_tx_rst_mask                                         (0x00004000)
#define CEC_TXCR0_tx_continuous_mask                                  (0x00002000)
#define CEC_TXCR0_tx_int_en_mask                                      (0x00001000)
#define CEC_TXCR0_dest_addr_mask                                      (0x00000F00)
#define CEC_TXCR0_tx_eom_mask                                         (0x00000080)
#define CEC_TXCR0_tx_int_mask                                         (0x00000040)
#define CEC_TXCR0_tx_fifo_ud_mask                                     (0x00000020)
#define CEC_TXCR0_tx_fifo_cnt_mask                                    (0x0000001F)
#define CEC_TXCR0_tx_addr_en(data)                                    (0x00100000&((data)<<20))
#define CEC_TXCR0_tx_addr(data)                                       (0x000F0000&((data)<<16))
#define CEC_TXCR0_tx_en(data)                                         (0x00008000&((data)<<15))
#define CEC_TXCR0_tx_rst(data)                                        (0x00004000&((data)<<14))
#define CEC_TXCR0_tx_continuous(data)                                 (0x00002000&((data)<<13))
#define CEC_TXCR0_tx_int_en(data)                                     (0x00001000&((data)<<12))
#define CEC_TXCR0_dest_addr(data)                                     (0x00000F00&((data)<<8))
#define CEC_TXCR0_tx_eom(data)                                        (0x00000080&((data)<<7))
#define CEC_TXCR0_tx_int(data)                                        (0x00000040&((data)<<6))
#define CEC_TXCR0_tx_fifo_ud(data)                                    (0x00000020&((data)<<5))
#define CEC_TXCR0_tx_fifo_cnt(data)                                   (0x0000001F&(data))
#define CEC_TXCR0_get_tx_addr_en(data)                                ((0x00100000&(data))>>20)
#define CEC_TXCR0_get_tx_addr(data)                                   ((0x000F0000&(data))>>16)
#define CEC_TXCR0_get_tx_en(data)                                     ((0x00008000&(data))>>15)
#define CEC_TXCR0_get_tx_rst(data)                                    ((0x00004000&(data))>>14)
#define CEC_TXCR0_get_tx_continuous(data)                             ((0x00002000&(data))>>13)
#define CEC_TXCR0_get_tx_int_en(data)                                 ((0x00001000&(data))>>12)
#define CEC_TXCR0_get_dest_addr(data)                                 ((0x00000F00&(data))>>8)
#define CEC_TXCR0_get_tx_eom(data)                                    ((0x00000080&(data))>>7)
#define CEC_TXCR0_get_tx_int(data)                                    ((0x00000040&(data))>>6)
#define CEC_TXCR0_get_tx_fifo_ud(data)                                ((0x00000020&(data))>>5)
#define CEC_TXCR0_get_tx_fifo_cnt(data)                               (0x0000001F&(data))


#define CEC_TXDR0                                                     0x18007510
#define CEC_TXDR0_reg_addr                                            "0xb8007510"
#define CEC_TXDR0_reg                                                 0xb8007510
#define CEC_TXDR0_inst_addr                                           "0x0384"
#define CEC_TXDR0_inst                                                0x0384
#define CEC_TXDR0_tx_add_cnt_shift                                    (6)
#define CEC_TXDR0_rx_sub_cnt_shift                                    (5)
#define CEC_TXDR0_fifo_cnt_shift                                      (0)
#define CEC_TXDR0_tx_add_cnt_mask                                     (0x00000040)
#define CEC_TXDR0_rx_sub_cnt_mask                                     (0x00000020)
#define CEC_TXDR0_fifo_cnt_mask                                       (0x0000001F)
#define CEC_TXDR0_tx_add_cnt(data)                                    (0x00000040&((data)<<6))
#define CEC_TXDR0_rx_sub_cnt(data)                                    (0x00000020&((data)<<5))
#define CEC_TXDR0_fifo_cnt(data)                                      (0x0000001F&(data))
#define CEC_TXDR0_get_tx_add_cnt(data)                                ((0x00000040&(data))>>6)
#define CEC_TXDR0_get_rx_sub_cnt(data)                                ((0x00000020&(data))>>5)
#define CEC_TXDR0_get_fifo_cnt(data)                                  (0x0000001F&(data))


#define CEC_TXDR1                                                     0x18007514
#define CEC_TXDR1_reg_addr                                            "0xb8007514"
#define CEC_TXDR1_reg                                                 0xb8007514
#define CEC_TXDR1_inst_addr                                           "0x0385"
#define CEC_TXDR1_inst                                                0x0385
#define CEC_TXDR1_tx_fifo_0_shift                                     (24)
#define CEC_TXDR1_tx_fifo_1_shift                                     (16)
#define CEC_TXDR1_tx_fifo_2_shift                                     (8)
#define CEC_TXDR1_tx_fifo_3_shift                                     (0)
#define CEC_TXDR1_tx_fifo_0_mask                                      (0xFF000000)
#define CEC_TXDR1_tx_fifo_1_mask                                      (0x00FF0000)
#define CEC_TXDR1_tx_fifo_2_mask                                      (0x0000FF00)
#define CEC_TXDR1_tx_fifo_3_mask                                      (0x000000FF)
#define CEC_TXDR1_tx_fifo_0(data)                                     (0xFF000000&((data)<<24))
#define CEC_TXDR1_tx_fifo_1(data)                                     (0x00FF0000&((data)<<16))
#define CEC_TXDR1_tx_fifo_2(data)                                     (0x0000FF00&((data)<<8))
#define CEC_TXDR1_tx_fifo_3(data)                                     (0x000000FF&(data))
#define CEC_TXDR1_get_tx_fifo_0(data)                                 ((0xFF000000&(data))>>24)
#define CEC_TXDR1_get_tx_fifo_1(data)                                 ((0x00FF0000&(data))>>16)
#define CEC_TXDR1_get_tx_fifo_2(data)                                 ((0x0000FF00&(data))>>8)
#define CEC_TXDR1_get_tx_fifo_3(data)                                 (0x000000FF&(data))


#define CEC_TXDR2                                                     0x18007518
#define CEC_TXDR2_reg_addr                                            "0xb8007518"
#define CEC_TXDR2_reg                                                 0xb8007518
#define CEC_TXDR2_inst_addr                                           "0x0386"
#define CEC_TXDR2_inst                                                0x0386
#define CEC_TXDR2_tx_fifo_4_shift                                     (24)
#define CEC_TXDR2_tx_fifo_5_shift                                     (16)
#define CEC_TXDR2_tx_fifo_6_shift                                     (8)
#define CEC_TXDR2_tx_fifo_7_shift                                     (0)
#define CEC_TXDR2_tx_fifo_4_mask                                      (0xFF000000)
#define CEC_TXDR2_tx_fifo_5_mask                                      (0x00FF0000)
#define CEC_TXDR2_tx_fifo_6_mask                                      (0x0000FF00)
#define CEC_TXDR2_tx_fifo_7_mask                                      (0x000000FF)
#define CEC_TXDR2_tx_fifo_4(data)                                     (0xFF000000&((data)<<24))
#define CEC_TXDR2_tx_fifo_5(data)                                     (0x00FF0000&((data)<<16))
#define CEC_TXDR2_tx_fifo_6(data)                                     (0x0000FF00&((data)<<8))
#define CEC_TXDR2_tx_fifo_7(data)                                     (0x000000FF&(data))
#define CEC_TXDR2_get_tx_fifo_4(data)                                 ((0xFF000000&(data))>>24)
#define CEC_TXDR2_get_tx_fifo_5(data)                                 ((0x00FF0000&(data))>>16)
#define CEC_TXDR2_get_tx_fifo_6(data)                                 ((0x0000FF00&(data))>>8)
#define CEC_TXDR2_get_tx_fifo_7(data)                                 (0x000000FF&(data))


#define CEC_TXDR3                                                     0x1800751c
#define CEC_TXDR3_reg_addr                                            "0xb800751c"
#define CEC_TXDR3_reg                                                 0xb800751c
#define CEC_TXDR3_inst_addr                                           "0x0387"
#define CEC_TXDR3_inst                                                0x0387
#define CEC_TXDR3_tx_fifo_8_shift                                     (24)
#define CEC_TXDR3_tx_fifo_9_shift                                     (16)
#define CEC_TXDR3_tx_fifo_a_shift                                     (8)
#define CEC_TXDR3_tx_fifo_b_shift                                     (0)
#define CEC_TXDR3_tx_fifo_8_mask                                      (0xFF000000)
#define CEC_TXDR3_tx_fifo_9_mask                                      (0x00FF0000)
#define CEC_TXDR3_tx_fifo_a_mask                                      (0x0000FF00)
#define CEC_TXDR3_tx_fifo_b_mask                                      (0x000000FF)
#define CEC_TXDR3_tx_fifo_8(data)                                     (0xFF000000&((data)<<24))
#define CEC_TXDR3_tx_fifo_9(data)                                     (0x00FF0000&((data)<<16))
#define CEC_TXDR3_tx_fifo_a(data)                                     (0x0000FF00&((data)<<8))
#define CEC_TXDR3_tx_fifo_b(data)                                     (0x000000FF&(data))
#define CEC_TXDR3_get_tx_fifo_8(data)                                 ((0xFF000000&(data))>>24)
#define CEC_TXDR3_get_tx_fifo_9(data)                                 ((0x00FF0000&(data))>>16)
#define CEC_TXDR3_get_tx_fifo_a(data)                                 ((0x0000FF00&(data))>>8)
#define CEC_TXDR3_get_tx_fifo_b(data)                                 (0x000000FF&(data))


#define CEC_TXDR4                                                     0x18007520
#define CEC_TXDR4_reg_addr                                            "0xb8007520"
#define CEC_TXDR4_reg                                                 0xb8007520
#define CEC_TXDR4_inst_addr                                           "0x0388"
#define CEC_TXDR4_inst                                                0x0388
#define CEC_TXDR4_tx_fifo_c_shift                                     (24)
#define CEC_TXDR4_tx_fifo_d_shift                                     (16)
#define CEC_TXDR4_tx_fifo_e_shift                                     (8)
#define CEC_TXDR4_tx_fifo_f_shift                                     (0)
#define CEC_TXDR4_tx_fifo_c_mask                                      (0xFF000000)
#define CEC_TXDR4_tx_fifo_d_mask                                      (0x00FF0000)
#define CEC_TXDR4_tx_fifo_e_mask                                      (0x0000FF00)
#define CEC_TXDR4_tx_fifo_f_mask                                      (0x000000FF)
#define CEC_TXDR4_tx_fifo_c(data)                                     (0xFF000000&((data)<<24))
#define CEC_TXDR4_tx_fifo_d(data)                                     (0x00FF0000&((data)<<16))
#define CEC_TXDR4_tx_fifo_e(data)                                     (0x0000FF00&((data)<<8))
#define CEC_TXDR4_tx_fifo_f(data)                                     (0x000000FF&(data))
#define CEC_TXDR4_get_tx_fifo_c(data)                                 ((0xFF000000&(data))>>24)
#define CEC_TXDR4_get_tx_fifo_d(data)                                 ((0x00FF0000&(data))>>16)
#define CEC_TXDR4_get_tx_fifo_e(data)                                 ((0x0000FF00&(data))>>8)
#define CEC_TXDR4_get_tx_fifo_f(data)                                 (0x000000FF&(data))


#define CEC_RXDR1                                                     0x18007524
#define CEC_RXDR1_reg_addr                                            "0xb8007524"
#define CEC_RXDR1_reg                                                 0xb8007524
#define CEC_RXDR1_inst_addr                                           "0x0389"
#define CEC_RXDR1_inst                                                0x0389
#define CEC_RXDR1_rx_fifo_0_shift                                     (24)
#define CEC_RXDR1_rx_fifo_1_shift                                     (16)
#define CEC_RXDR1_rx_fifo_2_shift                                     (8)
#define CEC_RXDR1_rx_fifo_3_shift                                     (0)
#define CEC_RXDR1_rx_fifo_0_mask                                      (0xFF000000)
#define CEC_RXDR1_rx_fifo_1_mask                                      (0x00FF0000)
#define CEC_RXDR1_rx_fifo_2_mask                                      (0x0000FF00)
#define CEC_RXDR1_rx_fifo_3_mask                                      (0x000000FF)
#define CEC_RXDR1_rx_fifo_0(data)                                     (0xFF000000&((data)<<24))
#define CEC_RXDR1_rx_fifo_1(data)                                     (0x00FF0000&((data)<<16))
#define CEC_RXDR1_rx_fifo_2(data)                                     (0x0000FF00&((data)<<8))
#define CEC_RXDR1_rx_fifo_3(data)                                     (0x000000FF&(data))
#define CEC_RXDR1_get_rx_fifo_0(data)                                 ((0xFF000000&(data))>>24)
#define CEC_RXDR1_get_rx_fifo_1(data)                                 ((0x00FF0000&(data))>>16)
#define CEC_RXDR1_get_rx_fifo_2(data)                                 ((0x0000FF00&(data))>>8)
#define CEC_RXDR1_get_rx_fifo_3(data)                                 (0x000000FF&(data))


#define CEC_RXDR2                                                     0x18007528
#define CEC_RXDR2_reg_addr                                            "0xb8007528"
#define CEC_RXDR2_reg                                                 0xb8007528
#define CEC_RXDR2_inst_addr                                           "0x038A"
#define CEC_RXDR2_inst                                                0x038A
#define CEC_RXDR2_rx_fifo_4_shift                                     (24)
#define CEC_RXDR2_rx_fifo_5_shift                                     (16)
#define CEC_RXDR2_rx_fifo_6_shift                                     (8)
#define CEC_RXDR2_rx_fifo_7_shift                                     (0)
#define CEC_RXDR2_rx_fifo_4_mask                                      (0xFF000000)
#define CEC_RXDR2_rx_fifo_5_mask                                      (0x00FF0000)
#define CEC_RXDR2_rx_fifo_6_mask                                      (0x0000FF00)
#define CEC_RXDR2_rx_fifo_7_mask                                      (0x000000FF)
#define CEC_RXDR2_rx_fifo_4(data)                                     (0xFF000000&((data)<<24))
#define CEC_RXDR2_rx_fifo_5(data)                                     (0x00FF0000&((data)<<16))
#define CEC_RXDR2_rx_fifo_6(data)                                     (0x0000FF00&((data)<<8))
#define CEC_RXDR2_rx_fifo_7(data)                                     (0x000000FF&(data))
#define CEC_RXDR2_get_rx_fifo_4(data)                                 ((0xFF000000&(data))>>24)
#define CEC_RXDR2_get_rx_fifo_5(data)                                 ((0x00FF0000&(data))>>16)
#define CEC_RXDR2_get_rx_fifo_6(data)                                 ((0x0000FF00&(data))>>8)
#define CEC_RXDR2_get_rx_fifo_7(data)                                 (0x000000FF&(data))


#define CEC_RXDR3                                                     0x1800752c
#define CEC_RXDR3_reg_addr                                            "0xb800752c"
#define CEC_RXDR3_reg                                                 0xb800752c
#define CEC_RXDR3_inst_addr                                           "0x038B"
#define CEC_RXDR3_inst                                                0x038B
#define CEC_RXDR3_rx_fifo_8_shift                                     (24)
#define CEC_RXDR3_rx_fifo_9_shift                                     (16)
#define CEC_RXDR3_rx_fifo_a_shift                                     (8)
#define CEC_RXDR3_rx_fifo_b_shift                                     (0)
#define CEC_RXDR3_rx_fifo_8_mask                                      (0xFF000000)
#define CEC_RXDR3_rx_fifo_9_mask                                      (0x00FF0000)
#define CEC_RXDR3_rx_fifo_a_mask                                      (0x0000FF00)
#define CEC_RXDR3_rx_fifo_b_mask                                      (0x000000FF)
#define CEC_RXDR3_rx_fifo_8(data)                                     (0xFF000000&((data)<<24))
#define CEC_RXDR3_rx_fifo_9(data)                                     (0x00FF0000&((data)<<16))
#define CEC_RXDR3_rx_fifo_a(data)                                     (0x0000FF00&((data)<<8))
#define CEC_RXDR3_rx_fifo_b(data)                                     (0x000000FF&(data))
#define CEC_RXDR3_get_rx_fifo_8(data)                                 ((0xFF000000&(data))>>24)
#define CEC_RXDR3_get_rx_fifo_9(data)                                 ((0x00FF0000&(data))>>16)
#define CEC_RXDR3_get_rx_fifo_a(data)                                 ((0x0000FF00&(data))>>8)
#define CEC_RXDR3_get_rx_fifo_b(data)                                 (0x000000FF&(data))


#define CEC_RXDR4                                                     0x18007530
#define CEC_RXDR4_reg_addr                                            "0xb8007530"
#define CEC_RXDR4_reg                                                 0xb8007530
#define CEC_RXDR4_inst_addr                                           "0x038C"
#define CEC_RXDR4_inst                                                0x038C
#define CEC_RXDR4_rx_fifo_c_shift                                     (24)
#define CEC_RXDR4_rx_fifo_d_shift                                     (16)
#define CEC_RXDR4_rx_fifo_e_shift                                     (8)
#define CEC_RXDR4_rx_fifo_f_shift                                     (0)
#define CEC_RXDR4_rx_fifo_c_mask                                      (0xFF000000)
#define CEC_RXDR4_rx_fifo_d_mask                                      (0x00FF0000)
#define CEC_RXDR4_rx_fifo_e_mask                                      (0x0000FF00)
#define CEC_RXDR4_rx_fifo_f_mask                                      (0x000000FF)
#define CEC_RXDR4_rx_fifo_c(data)                                     (0xFF000000&((data)<<24))
#define CEC_RXDR4_rx_fifo_d(data)                                     (0x00FF0000&((data)<<16))
#define CEC_RXDR4_rx_fifo_e(data)                                     (0x0000FF00&((data)<<8))
#define CEC_RXDR4_rx_fifo_f(data)                                     (0x000000FF&(data))
#define CEC_RXDR4_get_rx_fifo_c(data)                                 ((0xFF000000&(data))>>24)
#define CEC_RXDR4_get_rx_fifo_d(data)                                 ((0x00FF0000&(data))>>16)
#define CEC_RXDR4_get_rx_fifo_e(data)                                 ((0x0000FF00&(data))>>8)
#define CEC_RXDR4_get_rx_fifo_f(data)                                 (0x000000FF&(data))


#define CEC_RXTCR0                                                    0x18007534
#define CEC_RXTCR0_reg_addr                                           "0xb8007534"
#define CEC_RXTCR0_reg                                                0xb8007534
#define CEC_RXTCR0_inst_addr                                          "0x038D"
#define CEC_RXTCR0_inst                                               0x038D
#define CEC_RXTCR0_rx_start_low_shift                                 (24)
#define CEC_RXTCR0_rx_start_period_shift                              (16)
#define CEC_RXTCR0_rx_data_sample_shift                               (8)
#define CEC_RXTCR0_rx_data_period_shift                               (0)
#define CEC_RXTCR0_rx_start_low_mask                                  (0xFF000000)
#define CEC_RXTCR0_rx_start_period_mask                               (0x00FF0000)
#define CEC_RXTCR0_rx_data_sample_mask                                (0x0000FF00)
#define CEC_RXTCR0_rx_data_period_mask                                (0x000000FF)
#define CEC_RXTCR0_rx_start_low(data)                                 (0xFF000000&((data)<<24))
#define CEC_RXTCR0_rx_start_period(data)                              (0x00FF0000&((data)<<16))
#define CEC_RXTCR0_rx_data_sample(data)                               (0x0000FF00&((data)<<8))
#define CEC_RXTCR0_rx_data_period(data)                               (0x000000FF&(data))
#define CEC_RXTCR0_get_rx_start_low(data)                             ((0xFF000000&(data))>>24)
#define CEC_RXTCR0_get_rx_start_period(data)                          ((0x00FF0000&(data))>>16)
#define CEC_RXTCR0_get_rx_data_sample(data)                           ((0x0000FF00&(data))>>8)
#define CEC_RXTCR0_get_rx_data_period(data)                           (0x000000FF&(data))


#define CEC_TXTCR0                                                    0x18007538
#define CEC_TXTCR0_reg_addr                                           "0xb8007538"
#define CEC_TXTCR0_reg                                                0xb8007538
#define CEC_TXTCR0_inst_addr                                          "0x038E"
#define CEC_TXTCR0_inst                                               0x038E
#define CEC_TXTCR0_tx_start_low_shift                                 (8)
#define CEC_TXTCR0_tx_start_high_shift                                (0)
#define CEC_TXTCR0_tx_start_low_mask                                  (0x0000FF00)
#define CEC_TXTCR0_tx_start_high_mask                                 (0x000000FF)
#define CEC_TXTCR0_tx_start_low(data)                                 (0x0000FF00&((data)<<8))
#define CEC_TXTCR0_tx_start_high(data)                                (0x000000FF&(data))
#define CEC_TXTCR0_get_tx_start_low(data)                             ((0x0000FF00&(data))>>8)
#define CEC_TXTCR0_get_tx_start_high(data)                            (0x000000FF&(data))


#define CEC_TXTCR1                                                    0x1800753c
#define CEC_TXTCR1_reg_addr                                           "0xb800753c"
#define CEC_TXTCR1_reg                                                0xb800753c
#define CEC_TXTCR1_inst_addr                                          "0x038F"
#define CEC_TXTCR1_inst                                               0x038F
#define CEC_TXTCR1_tx_data_low_shift                                  (16)
#define CEC_TXTCR1_tx_data_01_shift                                   (8)
#define CEC_TXTCR1_tx_data_high_shift                                 (0)
#define CEC_TXTCR1_tx_data_low_mask                                   (0x00FF0000)
#define CEC_TXTCR1_tx_data_01_mask                                    (0x0000FF00)
#define CEC_TXTCR1_tx_data_high_mask                                  (0x000000FF)
#define CEC_TXTCR1_tx_data_low(data)                                  (0x00FF0000&((data)<<16))
#define CEC_TXTCR1_tx_data_01(data)                                   (0x0000FF00&((data)<<8))
#define CEC_TXTCR1_tx_data_high(data)                                 (0x000000FF&(data))
#define CEC_TXTCR1_get_tx_data_low(data)                              ((0x00FF0000&(data))>>16)
#define CEC_TXTCR1_get_tx_data_01(data)                               ((0x0000FF00&(data))>>8)
#define CEC_TXTCR1_get_tx_data_high(data)                             (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_01                                     0x18007540
#define GDI_CEC_COMPARE_OPCODE_01_reg_addr                            "0xb8007540"
#define GDI_CEC_COMPARE_OPCODE_01_reg                                 0xb8007540
#define GDI_CEC_COMPARE_OPCODE_01_inst_addr                           "0x0390"
#define GDI_CEC_COMPARE_OPCODE_01_inst                                0x0390
#define GDI_CEC_COMPARE_OPCODE_01_compare_opcode_01_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_01_compare_opcode_01_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_01_compare_opcode_01(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_01_get_compare_opcode_01(data)         (0x000000FF&(data))


#define GDI_CEC_SEND_OPCODE_01                                        0x18007544
#define GDI_CEC_SEND_OPCODE_01_reg_addr                               "0xb8007544"
#define GDI_CEC_SEND_OPCODE_01_reg                                    0xb8007544
#define GDI_CEC_SEND_OPCODE_01_inst_addr                              "0x0391"
#define GDI_CEC_SEND_OPCODE_01_inst                                   0x0391
#define GDI_CEC_SEND_OPCODE_01_send_opcode_01_shift                   (0)
#define GDI_CEC_SEND_OPCODE_01_send_opcode_01_mask                    (0x000000FF)
#define GDI_CEC_SEND_OPCODE_01_send_opcode_01(data)                   (0x000000FF&(data))
#define GDI_CEC_SEND_OPCODE_01_get_send_opcode_01(data)               (0x000000FF&(data))


#define GDI_CEC_SEND_OPERAND_NUMBER_01                                0x18007548
#define GDI_CEC_SEND_OPERAND_NUMBER_01_reg_addr                       "0xb8007548"
#define GDI_CEC_SEND_OPERAND_NUMBER_01_reg                            0xb8007548
#define GDI_CEC_SEND_OPERAND_NUMBER_01_inst_addr                      "0x0392"
#define GDI_CEC_SEND_OPERAND_NUMBER_01_inst                           0x0392
#define GDI_CEC_SEND_OPERAND_NUMBER_01_operand_number_01_shift        (0)
#define GDI_CEC_SEND_OPERAND_NUMBER_01_operand_number_01_mask         (0x00000003)
#define GDI_CEC_SEND_OPERAND_NUMBER_01_operand_number_01(data)        (0x00000003&(data))
#define GDI_CEC_SEND_OPERAND_NUMBER_01_get_operand_number_01(data)    (0x00000003&(data))


#define GDI_CEC_OPERAND_01                                            0x1800754c
#define GDI_CEC_OPERAND_01_reg_addr                                   "0xb800754c"
#define GDI_CEC_OPERAND_01_reg                                        0xb800754c
#define GDI_CEC_OPERAND_01_inst_addr                                  "0x0393"
#define GDI_CEC_OPERAND_01_inst                                       0x0393
#define GDI_CEC_OPERAND_01_operand_01_shift                           (0)
#define GDI_CEC_OPERAND_01_operand_01_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_01_operand_01(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_01_get_operand_01(data)                       (0x000000FF&(data))


#define GDI_CEC_OPERAND_02                                            0x18007550
#define GDI_CEC_OPERAND_02_reg_addr                                   "0xb8007550"
#define GDI_CEC_OPERAND_02_reg                                        0xb8007550
#define GDI_CEC_OPERAND_02_inst_addr                                  "0x0394"
#define GDI_CEC_OPERAND_02_inst                                       0x0394
#define GDI_CEC_OPERAND_02_operand_02_shift                           (0)
#define GDI_CEC_OPERAND_02_operand_02_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_02_operand_02(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_02_get_operand_02(data)                       (0x000000FF&(data))


#define GDI_CEC_OPERAND_03                                            0x18007554
#define GDI_CEC_OPERAND_03_reg_addr                                   "0xb8007554"
#define GDI_CEC_OPERAND_03_reg                                        0xb8007554
#define GDI_CEC_OPERAND_03_inst_addr                                  "0x0395"
#define GDI_CEC_OPERAND_03_inst                                       0x0395
#define GDI_CEC_OPERAND_03_operand_03_shift                           (0)
#define GDI_CEC_OPERAND_03_operand_03_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_03_operand_03(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_03_get_operand_03(data)                       (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_02                                     0x18007558
#define GDI_CEC_COMPARE_OPCODE_02_reg_addr                            "0xb8007558"
#define GDI_CEC_COMPARE_OPCODE_02_reg                                 0xb8007558
#define GDI_CEC_COMPARE_OPCODE_02_inst_addr                           "0x0396"
#define GDI_CEC_COMPARE_OPCODE_02_inst                                0x0396
#define GDI_CEC_COMPARE_OPCODE_02_compare_opcode_02_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_02_compare_opcode_02_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_02_compare_opcode_02(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_02_get_compare_opcode_02(data)         (0x000000FF&(data))


#define GDI_CEC_SEND_OPCODE_02                                        0x1800755c
#define GDI_CEC_SEND_OPCODE_02_reg_addr                               "0xb800755c"
#define GDI_CEC_SEND_OPCODE_02_reg                                    0xb800755c
#define GDI_CEC_SEND_OPCODE_02_inst_addr                              "0x0397"
#define GDI_CEC_SEND_OPCODE_02_inst                                   0x0397
#define GDI_CEC_SEND_OPCODE_02_send_opcode_02_shift                   (0)
#define GDI_CEC_SEND_OPCODE_02_send_opcode_02_mask                    (0x000000FF)
#define GDI_CEC_SEND_OPCODE_02_send_opcode_02(data)                   (0x000000FF&(data))
#define GDI_CEC_SEND_OPCODE_02_get_send_opcode_02(data)               (0x000000FF&(data))


#define GDI_CEC_SEND_OPERAND_NUMBER_02                                0x18007560
#define GDI_CEC_SEND_OPERAND_NUMBER_02_reg_addr                       "0xb8007560"
#define GDI_CEC_SEND_OPERAND_NUMBER_02_reg                            0xb8007560
#define GDI_CEC_SEND_OPERAND_NUMBER_02_inst_addr                      "0x0398"
#define GDI_CEC_SEND_OPERAND_NUMBER_02_inst                           0x0398
#define GDI_CEC_SEND_OPERAND_NUMBER_02_operand_number_02_shift        (0)
#define GDI_CEC_SEND_OPERAND_NUMBER_02_operand_number_02_mask         (0x00000003)
#define GDI_CEC_SEND_OPERAND_NUMBER_02_operand_number_02(data)        (0x00000003&(data))
#define GDI_CEC_SEND_OPERAND_NUMBER_02_get_operand_number_02(data)    (0x00000003&(data))


#define GDI_CEC_OPERAND_04                                            0x18007564
#define GDI_CEC_OPERAND_04_reg_addr                                   "0xb8007564"
#define GDI_CEC_OPERAND_04_reg                                        0xb8007564
#define GDI_CEC_OPERAND_04_inst_addr                                  "0x0399"
#define GDI_CEC_OPERAND_04_inst                                       0x0399
#define GDI_CEC_OPERAND_04_operand_04_shift                           (0)
#define GDI_CEC_OPERAND_04_operand_04_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_04_operand_04(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_04_get_operand_04(data)                       (0x000000FF&(data))


#define GDI_CEC_OPERAND_05                                            0x18007568
#define GDI_CEC_OPERAND_05_reg_addr                                   "0xb8007568"
#define GDI_CEC_OPERAND_05_reg                                        0xb8007568
#define GDI_CEC_OPERAND_05_inst_addr                                  "0x039A"
#define GDI_CEC_OPERAND_05_inst                                       0x039A
#define GDI_CEC_OPERAND_05_operand_05_shift                           (0)
#define GDI_CEC_OPERAND_05_operand_05_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_05_operand_05(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_05_get_operand_05(data)                       (0x000000FF&(data))


#define GDI_CEC_OPERAND_06                                            0x1800756c
#define GDI_CEC_OPERAND_06_reg_addr                                   "0xb800756c"
#define GDI_CEC_OPERAND_06_reg                                        0xb800756c
#define GDI_CEC_OPERAND_06_inst_addr                                  "0x039B"
#define GDI_CEC_OPERAND_06_inst                                       0x039B
#define GDI_CEC_OPERAND_06_operand_06_shift                           (0)
#define GDI_CEC_OPERAND_06_operand_06_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_06_operand_06(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_06_get_operand_06(data)                       (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_03                                     0x18007570
#define GDI_CEC_COMPARE_OPCODE_03_reg_addr                            "0xb8007570"
#define GDI_CEC_COMPARE_OPCODE_03_reg                                 0xb8007570
#define GDI_CEC_COMPARE_OPCODE_03_inst_addr                           "0x039C"
#define GDI_CEC_COMPARE_OPCODE_03_inst                                0x039C
#define GDI_CEC_COMPARE_OPCODE_03_compare_opcode_03_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_03_compare_opcode_03_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_03_compare_opcode_03(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_03_get_compare_opcode_03(data)         (0x000000FF&(data))


#define GDI_CEC_SEND_OPCODE_03                                        0x18007574
#define GDI_CEC_SEND_OPCODE_03_reg_addr                               "0xb8007574"
#define GDI_CEC_SEND_OPCODE_03_reg                                    0xb8007574
#define GDI_CEC_SEND_OPCODE_03_inst_addr                              "0x039D"
#define GDI_CEC_SEND_OPCODE_03_inst                                   0x039D
#define GDI_CEC_SEND_OPCODE_03_send_opcode_03_shift                   (0)
#define GDI_CEC_SEND_OPCODE_03_send_opcode_03_mask                    (0x000000FF)
#define GDI_CEC_SEND_OPCODE_03_send_opcode_03(data)                   (0x000000FF&(data))
#define GDI_CEC_SEND_OPCODE_03_get_send_opcode_03(data)               (0x000000FF&(data))


#define GDI_CEC_SEND_OPERAND_NUMBER_03                                0x18007578
#define GDI_CEC_SEND_OPERAND_NUMBER_03_reg_addr                       "0xb8007578"
#define GDI_CEC_SEND_OPERAND_NUMBER_03_reg                            0xb8007578
#define GDI_CEC_SEND_OPERAND_NUMBER_03_inst_addr                      "0x039E"
#define GDI_CEC_SEND_OPERAND_NUMBER_03_inst                           0x039E
#define GDI_CEC_SEND_OPERAND_NUMBER_03_operand_number_03_shift        (0)
#define GDI_CEC_SEND_OPERAND_NUMBER_03_operand_number_03_mask         (0x00000003)
#define GDI_CEC_SEND_OPERAND_NUMBER_03_operand_number_03(data)        (0x00000003&(data))
#define GDI_CEC_SEND_OPERAND_NUMBER_03_get_operand_number_03(data)    (0x00000003&(data))


#define GDI_CEC_OPERAND_07                                            0x1800757c
#define GDI_CEC_OPERAND_07_reg_addr                                   "0xb800757c"
#define GDI_CEC_OPERAND_07_reg                                        0xb800757c
#define GDI_CEC_OPERAND_07_inst_addr                                  "0x039F"
#define GDI_CEC_OPERAND_07_inst                                       0x039F
#define GDI_CEC_OPERAND_07_operand_07_shift                           (0)
#define GDI_CEC_OPERAND_07_operand_07_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_07_operand_07(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_07_get_operand_07(data)                       (0x000000FF&(data))


#define GDI_CEC_OPERAND_08                                            0x18007580
#define GDI_CEC_OPERAND_08_reg_addr                                   "0xb8007580"
#define GDI_CEC_OPERAND_08_reg                                        0xb8007580
#define GDI_CEC_OPERAND_08_inst_addr                                  "0x03A0"
#define GDI_CEC_OPERAND_08_inst                                       0x03A0
#define GDI_CEC_OPERAND_08_operand_08_shift                           (0)
#define GDI_CEC_OPERAND_08_operand_08_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_08_operand_08(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_08_get_operand_08(data)                       (0x000000FF&(data))


#define GDI_CEC_OPERAND_09                                            0x18007584
#define GDI_CEC_OPERAND_09_reg_addr                                   "0xb8007584"
#define GDI_CEC_OPERAND_09_reg                                        0xb8007584
#define GDI_CEC_OPERAND_09_inst_addr                                  "0x03A1"
#define GDI_CEC_OPERAND_09_inst                                       0x03A1
#define GDI_CEC_OPERAND_09_operand_09_shift                           (0)
#define GDI_CEC_OPERAND_09_operand_09_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_09_operand_09(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_09_get_operand_09(data)                       (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_04                                     0x18007588
#define GDI_CEC_COMPARE_OPCODE_04_reg_addr                            "0xb8007588"
#define GDI_CEC_COMPARE_OPCODE_04_reg                                 0xb8007588
#define GDI_CEC_COMPARE_OPCODE_04_inst_addr                           "0x03A2"
#define GDI_CEC_COMPARE_OPCODE_04_inst                                0x03A2
#define GDI_CEC_COMPARE_OPCODE_04_compare_opcode_04_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_04_compare_opcode_04_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_04_compare_opcode_04(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_04_get_compare_opcode_04(data)         (0x000000FF&(data))


#define GDI_CEC_SEND_OPCODE_04                                        0x1800758c
#define GDI_CEC_SEND_OPCODE_04_reg_addr                               "0xb800758c"
#define GDI_CEC_SEND_OPCODE_04_reg                                    0xb800758c
#define GDI_CEC_SEND_OPCODE_04_inst_addr                              "0x03A3"
#define GDI_CEC_SEND_OPCODE_04_inst                                   0x03A3
#define GDI_CEC_SEND_OPCODE_04_send_opcode_04_shift                   (0)
#define GDI_CEC_SEND_OPCODE_04_send_opcode_04_mask                    (0x000000FF)
#define GDI_CEC_SEND_OPCODE_04_send_opcode_04(data)                   (0x000000FF&(data))
#define GDI_CEC_SEND_OPCODE_04_get_send_opcode_04(data)               (0x000000FF&(data))


#define GDI_CEC_SEND_OPERAND_NUMBER_04                                0x18007590
#define GDI_CEC_SEND_OPERAND_NUMBER_04_reg_addr                       "0xb8007590"
#define GDI_CEC_SEND_OPERAND_NUMBER_04_reg                            0xb8007590
#define GDI_CEC_SEND_OPERAND_NUMBER_04_inst_addr                      "0x03A4"
#define GDI_CEC_SEND_OPERAND_NUMBER_04_inst                           0x03A4
#define GDI_CEC_SEND_OPERAND_NUMBER_04_operand_number_04_shift        (0)
#define GDI_CEC_SEND_OPERAND_NUMBER_04_operand_number_04_mask         (0x00000003)
#define GDI_CEC_SEND_OPERAND_NUMBER_04_operand_number_04(data)        (0x00000003&(data))
#define GDI_CEC_SEND_OPERAND_NUMBER_04_get_operand_number_04(data)    (0x00000003&(data))


#define GDI_CEC_OPERAND_10                                            0x18007594
#define GDI_CEC_OPERAND_10_reg_addr                                   "0xb8007594"
#define GDI_CEC_OPERAND_10_reg                                        0xb8007594
#define GDI_CEC_OPERAND_10_inst_addr                                  "0x03A5"
#define GDI_CEC_OPERAND_10_inst                                       0x03A5
#define GDI_CEC_OPERAND_10_operand_10_shift                           (0)
#define GDI_CEC_OPERAND_10_operand_10_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_10_operand_10(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_10_get_operand_10(data)                       (0x000000FF&(data))


#define GDI_CEC_OPERAND_11                                            0x18007598
#define GDI_CEC_OPERAND_11_reg_addr                                   "0xb8007598"
#define GDI_CEC_OPERAND_11_reg                                        0xb8007598
#define GDI_CEC_OPERAND_11_inst_addr                                  "0x03A6"
#define GDI_CEC_OPERAND_11_inst                                       0x03A6
#define GDI_CEC_OPERAND_11_operand_11_shift                           (0)
#define GDI_CEC_OPERAND_11_operand_11_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_11_operand_11(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_11_get_operand_11(data)                       (0x000000FF&(data))


#define GDI_CEC_OPERAND_12                                            0x1800759c
#define GDI_CEC_OPERAND_12_reg_addr                                   "0xb800759c"
#define GDI_CEC_OPERAND_12_reg                                        0xb800759c
#define GDI_CEC_OPERAND_12_inst_addr                                  "0x03A7"
#define GDI_CEC_OPERAND_12_inst                                       0x03A7
#define GDI_CEC_OPERAND_12_operand_12_shift                           (0)
#define GDI_CEC_OPERAND_12_operand_12_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_12_operand_12(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_12_get_operand_12(data)                       (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_05                                     0x180075a0
#define GDI_CEC_COMPARE_OPCODE_05_reg_addr                            "0xb80075a0"
#define GDI_CEC_COMPARE_OPCODE_05_reg                                 0xb80075a0
#define GDI_CEC_COMPARE_OPCODE_05_inst_addr                           "0x03A8"
#define GDI_CEC_COMPARE_OPCODE_05_inst                                0x03A8
#define GDI_CEC_COMPARE_OPCODE_05_compare_opcode_05_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_05_compare_opcode_05_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_05_compare_opcode_05(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_05_get_compare_opcode_05(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_06                                     0x180075a4
#define GDI_CEC_COMPARE_OPCODE_06_reg_addr                            "0xb80075a4"
#define GDI_CEC_COMPARE_OPCODE_06_reg                                 0xb80075a4
#define GDI_CEC_COMPARE_OPCODE_06_inst_addr                           "0x03A9"
#define GDI_CEC_COMPARE_OPCODE_06_inst                                0x03A9
#define GDI_CEC_COMPARE_OPCODE_06_compare_opcode_06_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_06_compare_opcode_06_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_06_compare_opcode_06(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_06_get_compare_opcode_06(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_07                                     0x180075a8
#define GDI_CEC_COMPARE_OPCODE_07_reg_addr                            "0xb80075a8"
#define GDI_CEC_COMPARE_OPCODE_07_reg                                 0xb80075a8
#define GDI_CEC_COMPARE_OPCODE_07_inst_addr                           "0x03AA"
#define GDI_CEC_COMPARE_OPCODE_07_inst                                0x03AA
#define GDI_CEC_COMPARE_OPCODE_07_compare_opcode_07_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_07_compare_opcode_07_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_07_compare_opcode_07(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_07_get_compare_opcode_07(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_08                                     0x180075ac
#define GDI_CEC_COMPARE_OPCODE_08_reg_addr                            "0xb80075ac"
#define GDI_CEC_COMPARE_OPCODE_08_reg                                 0xb80075ac
#define GDI_CEC_COMPARE_OPCODE_08_inst_addr                           "0x03AB"
#define GDI_CEC_COMPARE_OPCODE_08_inst                                0x03AB
#define GDI_CEC_COMPARE_OPCODE_08_compare_opcode_08_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_08_compare_opcode_08_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_08_compare_opcode_08(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_08_get_compare_opcode_08(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_09                                     0x180075b0
#define GDI_CEC_COMPARE_OPCODE_09_reg_addr                            "0xb80075b0"
#define GDI_CEC_COMPARE_OPCODE_09_reg                                 0xb80075b0
#define GDI_CEC_COMPARE_OPCODE_09_inst_addr                           "0x03AC"
#define GDI_CEC_COMPARE_OPCODE_09_inst                                0x03AC
#define GDI_CEC_COMPARE_OPCODE_09_compare_opcode_09_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_09_compare_opcode_09_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_09_compare_opcode_09(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_09_get_compare_opcode_09(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_10                                     0x180075b4
#define GDI_CEC_COMPARE_OPCODE_10_reg_addr                            "0xb80075b4"
#define GDI_CEC_COMPARE_OPCODE_10_reg                                 0xb80075b4
#define GDI_CEC_COMPARE_OPCODE_10_inst_addr                           "0x03AD"
#define GDI_CEC_COMPARE_OPCODE_10_inst                                0x03AD
#define GDI_CEC_COMPARE_OPCODE_10_compare_opcode_10_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_10_compare_opcode_10_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_10_compare_opcode_10(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_10_get_compare_opcode_10(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_11                                     0x180075b8
#define GDI_CEC_COMPARE_OPCODE_11_reg_addr                            "0xb80075b8"
#define GDI_CEC_COMPARE_OPCODE_11_reg                                 0xb80075b8
#define GDI_CEC_COMPARE_OPCODE_11_inst_addr                           "0x03AE"
#define GDI_CEC_COMPARE_OPCODE_11_inst                                0x03AE
#define GDI_CEC_COMPARE_OPCODE_11_compare_opcode_11_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_11_compare_opcode_11_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_11_compare_opcode_11(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_11_get_compare_opcode_11(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_12                                     0x180075bc
#define GDI_CEC_COMPARE_OPCODE_12_reg_addr                            "0xb80075bc"
#define GDI_CEC_COMPARE_OPCODE_12_reg                                 0xb80075bc
#define GDI_CEC_COMPARE_OPCODE_12_inst_addr                           "0x03AF"
#define GDI_CEC_COMPARE_OPCODE_12_inst                                0x03AF
#define GDI_CEC_COMPARE_OPCODE_12_compare_opcode_12_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_12_compare_opcode_12_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_12_compare_opcode_12(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_12_get_compare_opcode_12(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_13                                     0x180075c0
#define GDI_CEC_COMPARE_OPCODE_13_reg_addr                            "0xb80075c0"
#define GDI_CEC_COMPARE_OPCODE_13_reg                                 0xb80075c0
#define GDI_CEC_COMPARE_OPCODE_13_inst_addr                           "0x03B0"
#define GDI_CEC_COMPARE_OPCODE_13_inst                                0x03B0
#define GDI_CEC_COMPARE_OPCODE_13_compare_opcode_13_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_13_compare_opcode_13_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_13_compare_opcode_13(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_13_get_compare_opcode_13(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_14                                     0x180075c4
#define GDI_CEC_COMPARE_OPCODE_14_reg_addr                            "0xb80075c4"
#define GDI_CEC_COMPARE_OPCODE_14_reg                                 0xb80075c4
#define GDI_CEC_COMPARE_OPCODE_14_inst_addr                           "0x03B1"
#define GDI_CEC_COMPARE_OPCODE_14_inst                                0x03B1
#define GDI_CEC_COMPARE_OPCODE_14_compare_opcode_14_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_14_compare_opcode_14_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_14_compare_opcode_14(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_14_get_compare_opcode_14(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_15                                     0x180075c8
#define GDI_CEC_COMPARE_OPCODE_15_reg_addr                            "0xb80075c8"
#define GDI_CEC_COMPARE_OPCODE_15_reg                                 0xb80075c8
#define GDI_CEC_COMPARE_OPCODE_15_inst_addr                           "0x03B2"
#define GDI_CEC_COMPARE_OPCODE_15_inst                                0x03B2
#define GDI_CEC_COMPARE_OPCODE_15_compare_opcode_15_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_15_compare_opcode_15_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_15_compare_opcode_15(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_15_get_compare_opcode_15(data)         (0x000000FF&(data))


#define GDI_CEC_OPCODE_ENABLE                                         0x180075cc
#define GDI_CEC_OPCODE_ENABLE_reg_addr                                "0xb80075cc"
#define GDI_CEC_OPCODE_ENABLE_reg                                     0xb80075cc
#define GDI_CEC_OPCODE_ENABLE_inst_addr                               "0x03B3"
#define GDI_CEC_OPCODE_ENABLE_inst                                    0x03B3
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_15_shift              (14)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_14_shift              (13)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_13_shift              (12)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_12_shift              (11)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_11_shift              (10)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_10_shift              (9)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_09_shift              (8)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_08_shift              (7)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_07_shift              (6)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_06_shift              (5)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_05_shift              (4)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_04_shift              (3)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_03_shift              (2)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_02_shift              (1)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_01_shift              (0)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_15_mask               (0x00004000)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_14_mask               (0x00002000)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_13_mask               (0x00001000)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_12_mask               (0x00000800)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_11_mask               (0x00000400)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_10_mask               (0x00000200)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_09_mask               (0x00000100)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_08_mask               (0x00000080)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_07_mask               (0x00000040)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_06_mask               (0x00000020)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_05_mask               (0x00000010)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_04_mask               (0x00000008)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_03_mask               (0x00000004)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_02_mask               (0x00000002)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_01_mask               (0x00000001)
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_15(data)              (0x00004000&((data)<<14))
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_14(data)              (0x00002000&((data)<<13))
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_13(data)              (0x00001000&((data)<<12))
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_12(data)              (0x00000800&((data)<<11))
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_11(data)              (0x00000400&((data)<<10))
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_10(data)              (0x00000200&((data)<<9))
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_09(data)              (0x00000100&((data)<<8))
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_08(data)              (0x00000080&((data)<<7))
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_07(data)              (0x00000040&((data)<<6))
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_06(data)              (0x00000020&((data)<<5))
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_05(data)              (0x00000010&((data)<<4))
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_04(data)              (0x00000008&((data)<<3))
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_03(data)              (0x00000004&((data)<<2))
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_02(data)              (0x00000002&((data)<<1))
#define GDI_CEC_OPCODE_ENABLE_en_compare_opcode_01(data)              (0x00000001&(data))
#define GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_15(data)          ((0x00004000&(data))>>14)
#define GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_14(data)          ((0x00002000&(data))>>13)
#define GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_13(data)          ((0x00001000&(data))>>12)
#define GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_12(data)          ((0x00000800&(data))>>11)
#define GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_11(data)          ((0x00000400&(data))>>10)
#define GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_10(data)          ((0x00000200&(data))>>9)
#define GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_09(data)          ((0x00000100&(data))>>8)
#define GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_08(data)          ((0x00000080&(data))>>7)
#define GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_07(data)          ((0x00000040&(data))>>6)
#define GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_06(data)          ((0x00000020&(data))>>5)
#define GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_05(data)          ((0x00000010&(data))>>4)
#define GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_04(data)          ((0x00000008&(data))>>3)
#define GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_03(data)          ((0x00000004&(data))>>2)
#define GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_02(data)          ((0x00000002&(data))>>1)
#define GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_01(data)          (0x00000001&(data))


#define GDI_POWER_SAVING_MODE                                         0x180075d0
#define GDI_POWER_SAVING_MODE_reg_addr                                "0xb80075d0"
#define GDI_POWER_SAVING_MODE_reg                                     0xb80075d0
#define GDI_POWER_SAVING_MODE_inst_addr                               "0x03B4"
#define GDI_POWER_SAVING_MODE_inst                                    0x03B4
#define GDI_POWER_SAVING_MODE_irq_pending_shift                       (31)
#define GDI_POWER_SAVING_MODE_cec_msg_status_01_shift                 (25)
#define GDI_POWER_SAVING_MODE_cec_msg_status_02_shift                 (24)
#define GDI_POWER_SAVING_MODE_irq_by_cec_receive_special_cmd_shift    (8)
#define GDI_POWER_SAVING_MODE_irq_pending_mask                        (0x80000000)
#define GDI_POWER_SAVING_MODE_cec_msg_status_01_mask                  (0x02000000)
#define GDI_POWER_SAVING_MODE_cec_msg_status_02_mask                  (0x01000000)
#define GDI_POWER_SAVING_MODE_irq_by_cec_receive_special_cmd_mask     (0x00000100)
#define GDI_POWER_SAVING_MODE_irq_pending(data)                       (0x80000000&((data)<<31))
#define GDI_POWER_SAVING_MODE_cec_msg_status_01(data)                 (0x02000000&((data)<<25))
#define GDI_POWER_SAVING_MODE_cec_msg_status_02(data)                 (0x01000000&((data)<<24))
#define GDI_POWER_SAVING_MODE_irq_by_cec_receive_special_cmd(data)    (0x00000100&((data)<<8))
#define GDI_POWER_SAVING_MODE_get_irq_pending(data)                   ((0x80000000&(data))>>31)
#define GDI_POWER_SAVING_MODE_get_cec_msg_status_01(data)             ((0x02000000&(data))>>25)
#define GDI_POWER_SAVING_MODE_get_cec_msg_status_02(data)             ((0x01000000&(data))>>24)
#define GDI_POWER_SAVING_MODE_get_irq_by_cec_receive_special_cmd(data)  ((0x00000100&(data))>>8)


#define CEC_ANALOG_01                                                 0x180075d4
#define CEC_ANALOG_01_reg_addr                                        "0xb80075d4"
#define CEC_ANALOG_01_reg                                             0xb80075d4
#define CEC_ANALOG_01_inst_addr                                       "0x03B5"
#define CEC_ANALOG_01_inst                                            0x03B5
#define CEC_ANALOG_01_vcckoff_33v_shift                               (0)
#define CEC_ANALOG_01_vcckoff_33v_mask                                (0x00000001)
#define CEC_ANALOG_01_vcckoff_33v(data)                               (0x00000001&(data))
#define CEC_ANALOG_01_get_vcckoff_33v(data)                           (0x00000001&(data))
#endif
