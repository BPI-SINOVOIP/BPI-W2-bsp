// This file is generated using the spec version 1.39, firmware template version 1.39and SRIF Parser                                                                                source code SVN rev:802                    Version flow no.:1.1.66
#ifndef _CEC_REG_H_INCLUDED_
#define _CEC_REG_H_INCLUDED_

//#define  _CEC_USE_STRUCT
#ifdef _CEC_USE_STRUCT

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
    unsigned int    dummy18037204_30_18:13;
    unsigned int    cec_pad_en:1;
    unsigned int    cec_pad_en_mode:1;
    unsigned int    dummy18037204_15_13:3;
    unsigned int    cec_hw_retry_en:1;
    unsigned int    clear_cec_int:1;
    unsigned int    wt_cnt:6;
    unsigned int    lattest:1;
    unsigned int    retry_no:4;
}CEC_rtcr0;

typedef struct
{
    unsigned int    broadcast_addr:1;
    unsigned int    reserved_0:10;
    unsigned int    standby_addr_sel:1;
    unsigned int    standby_init_addr:4;
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
    unsigned int    reserved_0:19;
    unsigned int    send_init_address_01:1;
    unsigned int    init_address_01:4;
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
    unsigned int    reserved_0:19;
    unsigned int    send_init_address_02:1;
    unsigned int    init_address_02:4;
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
    unsigned int    reserved_0:19;
    unsigned int    send_init_address_03:1;
    unsigned int    init_address_03:4;
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
    unsigned int    reserved_0:19;
    unsigned int    send_init_address_04:1;
    unsigned int    init_address_04:4;
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
    unsigned int    reserved_2:3;
    unsigned int    cec_rpu_en:1;
    unsigned int    reserved_3:1;
    unsigned int    cec_rsel:3;
}GDI_power_saving_mode;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    rx_ack_wait_1_sel:1;
    unsigned int    rx_ack_wait_2_sel:1;
    unsigned int    rx_ack_wait_3_sel:1;
    unsigned int    rx_ack_wait_1:8;
    unsigned int    rx_ack_wait_2:8;
    unsigned int    rx_ack_wait_3:8;
}CEC_rxacktcr0;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    rx_ack_low_sel:1;
    unsigned int    rx_ack_bit_sel:1;
    unsigned int    rx_ack_line_err_sel:1;
    unsigned int    rx_ack_low:8;
    unsigned int    rx_ack_bit:8;
    unsigned int    rx_ack_line_err:8;
}CEC_rxacktcr1;
#endif


#define CEC_CR0                                                       0x18037200
#define CEC_CR0_reg_addr                                              "0xb8037200"
#define CEC_CR0_reg                                                   0xb8037200
#define CEC_CR0_inst_addr                                             "0x0080"
#define CEC_CR0_inst                                                  0x0080
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


#define CEC_RTCR0                                                     0x18037204
#define CEC_RTCR0_reg_addr                                            "0xb8037204"
#define CEC_RTCR0_reg                                                 0xb8037204
#define CEC_RTCR0_inst_addr                                           "0x0081"
#define CEC_RTCR0_inst                                                0x0081
#define CEC_RTCR0_cec_pad_in_shift                                    (31)
#define CEC_RTCR0_dummy18037204_30_18_shift                           (18)
#define CEC_RTCR0_cec_pad_en_shift                                    (17)
#define CEC_RTCR0_cec_pad_en_mode_shift                               (16)
#define CEC_RTCR0_dummy18037204_15_13_shift                           (13)
#define CEC_RTCR0_cec_hw_retry_en_shift                               (12)
#define CEC_RTCR0_clear_cec_int_shift                                 (11)
#define CEC_RTCR0_wt_cnt_shift                                        (5)
#define CEC_RTCR0_lattest_shift                                       (4)
#define CEC_RTCR0_retry_no_shift                                      (0)
#define CEC_RTCR0_cec_pad_in_mask                                     (0x80000000)
#define CEC_RTCR0_dummy18037204_30_18_mask                            (0x7FFC0000)
#define CEC_RTCR0_cec_pad_en_mask                                     (0x00020000)
#define CEC_RTCR0_cec_pad_en_mode_mask                                (0x00010000)
#define CEC_RTCR0_dummy18037204_15_13_mask                            (0x0000E000)
#define CEC_RTCR0_cec_hw_retry_en_mask                                (0x00001000)
#define CEC_RTCR0_clear_cec_int_mask                                  (0x00000800)
#define CEC_RTCR0_wt_cnt_mask                                         (0x000007E0)
#define CEC_RTCR0_lattest_mask                                        (0x00000010)
#define CEC_RTCR0_retry_no_mask                                       (0x0000000F)
#define CEC_RTCR0_cec_pad_in(data)                                    (0x80000000&((data)<<31))
#define CEC_RTCR0_dummy18037204_30_18(data)                           (0x7FFC0000&((data)<<18))
#define CEC_RTCR0_cec_pad_en(data)                                    (0x00020000&((data)<<17))
#define CEC_RTCR0_cec_pad_en_mode(data)                               (0x00010000&((data)<<16))
#define CEC_RTCR0_dummy18037204_15_13(data)                           (0x0000E000&((data)<<13))
#define CEC_RTCR0_cec_hw_retry_en(data)                               (0x00001000&((data)<<12))
#define CEC_RTCR0_clear_cec_int(data)                                 (0x00000800&((data)<<11))
#define CEC_RTCR0_wt_cnt(data)                                        (0x000007E0&((data)<<5))
#define CEC_RTCR0_lattest(data)                                       (0x00000010&((data)<<4))
#define CEC_RTCR0_retry_no(data)                                      (0x0000000F&(data))
#define CEC_RTCR0_get_cec_pad_in(data)                                ((0x80000000&(data))>>31)
#define CEC_RTCR0_get_dummy18037204_30_18(data)                       ((0x7FFC0000&(data))>>18)
#define CEC_RTCR0_get_cec_pad_en(data)                                ((0x00020000&(data))>>17)
#define CEC_RTCR0_get_cec_pad_en_mode(data)                           ((0x00010000&(data))>>16)
#define CEC_RTCR0_get_dummy18037204_15_13(data)                       ((0x0000E000&(data))>>13)
#define CEC_RTCR0_get_cec_hw_retry_en(data)                           ((0x00001000&(data))>>12)
#define CEC_RTCR0_get_clear_cec_int(data)                             ((0x00000800&(data))>>11)
#define CEC_RTCR0_get_wt_cnt(data)                                    ((0x000007E0&(data))>>5)
#define CEC_RTCR0_get_lattest(data)                                   ((0x00000010&(data))>>4)
#define CEC_RTCR0_get_retry_no(data)                                  (0x0000000F&(data))


#define CEC_RXCR0                                                     0x18037208
#define CEC_RXCR0_reg_addr                                            "0xb8037208"
#define CEC_RXCR0_reg                                                 0xb8037208
#define CEC_RXCR0_inst_addr                                           "0x0082"
#define CEC_RXCR0_inst                                                0x0082
#define CEC_RXCR0_broadcast_addr_shift                                (31)
#define CEC_RXCR0_standby_addr_sel_shift                              (20)
#define CEC_RXCR0_standby_init_addr_shift                             (16)
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
#define CEC_RXCR0_standby_addr_sel_mask                               (0x00100000)
#define CEC_RXCR0_standby_init_addr_mask                              (0x000F0000)
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
#define CEC_RXCR0_standby_addr_sel(data)                              (0x00100000&((data)<<20))
#define CEC_RXCR0_standby_init_addr(data)                             (0x000F0000&((data)<<16))
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
#define CEC_RXCR0_get_standby_addr_sel(data)                          ((0x00100000&(data))>>20)
#define CEC_RXCR0_get_standby_init_addr(data)                         ((0x000F0000&(data))>>16)
#define CEC_RXCR0_get_rx_en(data)                                     ((0x00008000&(data))>>15)
#define CEC_RXCR0_get_rx_rst(data)                                    ((0x00004000&(data))>>14)
#define CEC_RXCR0_get_rx_continuous(data)                             ((0x00002000&(data))>>13)
#define CEC_RXCR0_get_rx_int_en(data)                                 ((0x00001000&(data))>>12)
#define CEC_RXCR0_get_init_addr(data)                                 ((0x00000F00&(data))>>8)
#define CEC_RXCR0_get_rx_eom(data)                                    ((0x00000080&(data))>>7)
#define CEC_RXCR0_get_rx_int(data)                                    ((0x00000040&(data))>>6)
#define CEC_RXCR0_get_rx_fifo_ov(data)                                ((0x00000020&(data))>>5)
#define CEC_RXCR0_get_rx_fifo_cnt(data)                               (0x0000001F&(data))


#define CEC_TXCR0                                                     0x1803720c
#define CEC_TXCR0_reg_addr                                            "0xb803720c"
#define CEC_TXCR0_reg                                                 0xb803720c
#define CEC_TXCR0_inst_addr                                           "0x0083"
#define CEC_TXCR0_inst                                                0x0083
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


#define CEC_TXDR0                                                     0x18037210
#define CEC_TXDR0_reg_addr                                            "0xb8037210"
#define CEC_TXDR0_reg                                                 0xb8037210
#define CEC_TXDR0_inst_addr                                           "0x0084"
#define CEC_TXDR0_inst                                                0x0084
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


#define CEC_TXDR1                                                     0x18037214
#define CEC_TXDR1_reg_addr                                            "0xb8037214"
#define CEC_TXDR1_reg                                                 0xb8037214
#define CEC_TXDR1_inst_addr                                           "0x0085"
#define CEC_TXDR1_inst                                                0x0085
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


#define CEC_TXDR2                                                     0x18037218
#define CEC_TXDR2_reg_addr                                            "0xb8037218"
#define CEC_TXDR2_reg                                                 0xb8037218
#define CEC_TXDR2_inst_addr                                           "0x0086"
#define CEC_TXDR2_inst                                                0x0086
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


#define CEC_TXDR3                                                     0x1803721c
#define CEC_TXDR3_reg_addr                                            "0xb803721c"
#define CEC_TXDR3_reg                                                 0xb803721c
#define CEC_TXDR3_inst_addr                                           "0x0087"
#define CEC_TXDR3_inst                                                0x0087
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


#define CEC_TXDR4                                                     0x18037220
#define CEC_TXDR4_reg_addr                                            "0xb8037220"
#define CEC_TXDR4_reg                                                 0xb8037220
#define CEC_TXDR4_inst_addr                                           "0x0088"
#define CEC_TXDR4_inst                                                0x0088
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


#define CEC_RXDR1                                                     0x18037224
#define CEC_RXDR1_reg_addr                                            "0xb8037224"
#define CEC_RXDR1_reg                                                 0xb8037224
#define CEC_RXDR1_inst_addr                                           "0x0089"
#define CEC_RXDR1_inst                                                0x0089
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


#define CEC_RXDR2                                                     0x18037228
#define CEC_RXDR2_reg_addr                                            "0xb8037228"
#define CEC_RXDR2_reg                                                 0xb8037228
#define CEC_RXDR2_inst_addr                                           "0x008A"
#define CEC_RXDR2_inst                                                0x008A
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


#define CEC_RXDR3                                                     0x1803722c
#define CEC_RXDR3_reg_addr                                            "0xb803722c"
#define CEC_RXDR3_reg                                                 0xb803722c
#define CEC_RXDR3_inst_addr                                           "0x008B"
#define CEC_RXDR3_inst                                                0x008B
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


#define CEC_RXDR4                                                     0x18037230
#define CEC_RXDR4_reg_addr                                            "0xb8037230"
#define CEC_RXDR4_reg                                                 0xb8037230
#define CEC_RXDR4_inst_addr                                           "0x008C"
#define CEC_RXDR4_inst                                                0x008C
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


#define CEC_RXTCR0                                                    0x18037234
#define CEC_RXTCR0_reg_addr                                           "0xb8037234"
#define CEC_RXTCR0_reg                                                0xb8037234
#define CEC_RXTCR0_inst_addr                                          "0x008D"
#define CEC_RXTCR0_inst                                               0x008D
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


#define CEC_TXTCR0                                                    0x18037238
#define CEC_TXTCR0_reg_addr                                           "0xb8037238"
#define CEC_TXTCR0_reg                                                0xb8037238
#define CEC_TXTCR0_inst_addr                                          "0x008E"
#define CEC_TXTCR0_inst                                               0x008E
#define CEC_TXTCR0_tx_start_low_shift                                 (8)
#define CEC_TXTCR0_tx_start_high_shift                                (0)
#define CEC_TXTCR0_tx_start_low_mask                                  (0x0000FF00)
#define CEC_TXTCR0_tx_start_high_mask                                 (0x000000FF)
#define CEC_TXTCR0_tx_start_low(data)                                 (0x0000FF00&((data)<<8))
#define CEC_TXTCR0_tx_start_high(data)                                (0x000000FF&(data))
#define CEC_TXTCR0_get_tx_start_low(data)                             ((0x0000FF00&(data))>>8)
#define CEC_TXTCR0_get_tx_start_high(data)                            (0x000000FF&(data))


#define CEC_TXTCR1                                                    0x1803723c
#define CEC_TXTCR1_reg_addr                                           "0xb803723c"
#define CEC_TXTCR1_reg                                                0xb803723c
#define CEC_TXTCR1_inst_addr                                          "0x008F"
#define CEC_TXTCR1_inst                                               0x008F
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


#define GDI_CEC_COMPARE_OPCODE_01                                     0x18037240
#define GDI_CEC_COMPARE_OPCODE_01_reg_addr                            "0xb8037240"
#define GDI_CEC_COMPARE_OPCODE_01_reg                                 0xb8037240
#define GDI_CEC_COMPARE_OPCODE_01_inst_addr                           "0x0090"
#define GDI_CEC_COMPARE_OPCODE_01_inst                                0x0090
#define GDI_CEC_COMPARE_OPCODE_01_compare_opcode_01_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_01_compare_opcode_01_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_01_compare_opcode_01(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_01_get_compare_opcode_01(data)         (0x000000FF&(data))


#define GDI_CEC_SEND_OPCODE_01                                        0x18037244
#define GDI_CEC_SEND_OPCODE_01_reg_addr                               "0xb8037244"
#define GDI_CEC_SEND_OPCODE_01_reg                                    0xb8037244
#define GDI_CEC_SEND_OPCODE_01_inst_addr                              "0x0091"
#define GDI_CEC_SEND_OPCODE_01_inst                                   0x0091
#define GDI_CEC_SEND_OPCODE_01_send_init_address_01_shift             (12)
#define GDI_CEC_SEND_OPCODE_01_init_address_01_shift                  (8)
#define GDI_CEC_SEND_OPCODE_01_send_opcode_01_shift                   (0)
#define GDI_CEC_SEND_OPCODE_01_send_init_address_01_mask              (0x00001000)
#define GDI_CEC_SEND_OPCODE_01_init_address_01_mask                   (0x00000F00)
#define GDI_CEC_SEND_OPCODE_01_send_opcode_01_mask                    (0x000000FF)
#define GDI_CEC_SEND_OPCODE_01_send_init_address_01(data)             (0x00001000&((data)<<12))
#define GDI_CEC_SEND_OPCODE_01_init_address_01(data)                  (0x00000F00&((data)<<8))
#define GDI_CEC_SEND_OPCODE_01_send_opcode_01(data)                   (0x000000FF&(data))
#define GDI_CEC_SEND_OPCODE_01_get_send_init_address_01(data)         ((0x00001000&(data))>>12)
#define GDI_CEC_SEND_OPCODE_01_get_init_address_01(data)              ((0x00000F00&(data))>>8)
#define GDI_CEC_SEND_OPCODE_01_get_send_opcode_01(data)               (0x000000FF&(data))


#define GDI_CEC_SEND_OPERAND_NUMBER_01                                0x18037248
#define GDI_CEC_SEND_OPERAND_NUMBER_01_reg_addr                       "0xb8037248"
#define GDI_CEC_SEND_OPERAND_NUMBER_01_reg                            0xb8037248
#define GDI_CEC_SEND_OPERAND_NUMBER_01_inst_addr                      "0x0092"
#define GDI_CEC_SEND_OPERAND_NUMBER_01_inst                           0x0092
#define GDI_CEC_SEND_OPERAND_NUMBER_01_operand_number_01_shift        (0)
#define GDI_CEC_SEND_OPERAND_NUMBER_01_operand_number_01_mask         (0x00000003)
#define GDI_CEC_SEND_OPERAND_NUMBER_01_operand_number_01(data)        (0x00000003&(data))
#define GDI_CEC_SEND_OPERAND_NUMBER_01_get_operand_number_01(data)    (0x00000003&(data))


#define GDI_CEC_OPERAND_01                                            0x1803724c
#define GDI_CEC_OPERAND_01_reg_addr                                   "0xb803724c"
#define GDI_CEC_OPERAND_01_reg                                        0xb803724c
#define GDI_CEC_OPERAND_01_inst_addr                                  "0x0093"
#define GDI_CEC_OPERAND_01_inst                                       0x0093
#define GDI_CEC_OPERAND_01_operand_01_shift                           (0)
#define GDI_CEC_OPERAND_01_operand_01_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_01_operand_01(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_01_get_operand_01(data)                       (0x000000FF&(data))


#define GDI_CEC_OPERAND_02                                            0x18037250
#define GDI_CEC_OPERAND_02_reg_addr                                   "0xb8037250"
#define GDI_CEC_OPERAND_02_reg                                        0xb8037250
#define GDI_CEC_OPERAND_02_inst_addr                                  "0x0094"
#define GDI_CEC_OPERAND_02_inst                                       0x0094
#define GDI_CEC_OPERAND_02_operand_02_shift                           (0)
#define GDI_CEC_OPERAND_02_operand_02_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_02_operand_02(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_02_get_operand_02(data)                       (0x000000FF&(data))


#define GDI_CEC_OPERAND_03                                            0x18037254
#define GDI_CEC_OPERAND_03_reg_addr                                   "0xb8037254"
#define GDI_CEC_OPERAND_03_reg                                        0xb8037254
#define GDI_CEC_OPERAND_03_inst_addr                                  "0x0095"
#define GDI_CEC_OPERAND_03_inst                                       0x0095
#define GDI_CEC_OPERAND_03_operand_03_shift                           (0)
#define GDI_CEC_OPERAND_03_operand_03_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_03_operand_03(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_03_get_operand_03(data)                       (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_02                                     0x18037258
#define GDI_CEC_COMPARE_OPCODE_02_reg_addr                            "0xb8037258"
#define GDI_CEC_COMPARE_OPCODE_02_reg                                 0xb8037258
#define GDI_CEC_COMPARE_OPCODE_02_inst_addr                           "0x0096"
#define GDI_CEC_COMPARE_OPCODE_02_inst                                0x0096
#define GDI_CEC_COMPARE_OPCODE_02_compare_opcode_02_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_02_compare_opcode_02_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_02_compare_opcode_02(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_02_get_compare_opcode_02(data)         (0x000000FF&(data))


#define GDI_CEC_SEND_OPCODE_02                                        0x1803725c
#define GDI_CEC_SEND_OPCODE_02_reg_addr                               "0xb803725c"
#define GDI_CEC_SEND_OPCODE_02_reg                                    0xb803725c
#define GDI_CEC_SEND_OPCODE_02_inst_addr                              "0x0097"
#define GDI_CEC_SEND_OPCODE_02_inst                                   0x0097
#define GDI_CEC_SEND_OPCODE_02_send_init_address_02_shift             (12)
#define GDI_CEC_SEND_OPCODE_02_init_address_02_shift                  (8)
#define GDI_CEC_SEND_OPCODE_02_send_opcode_02_shift                   (0)
#define GDI_CEC_SEND_OPCODE_02_send_init_address_02_mask              (0x00001000)
#define GDI_CEC_SEND_OPCODE_02_init_address_02_mask                   (0x00000F00)
#define GDI_CEC_SEND_OPCODE_02_send_opcode_02_mask                    (0x000000FF)
#define GDI_CEC_SEND_OPCODE_02_send_init_address_02(data)             (0x00001000&((data)<<12))
#define GDI_CEC_SEND_OPCODE_02_init_address_02(data)                  (0x00000F00&((data)<<8))
#define GDI_CEC_SEND_OPCODE_02_send_opcode_02(data)                   (0x000000FF&(data))
#define GDI_CEC_SEND_OPCODE_02_get_send_init_address_02(data)         ((0x00001000&(data))>>12)
#define GDI_CEC_SEND_OPCODE_02_get_init_address_02(data)              ((0x00000F00&(data))>>8)
#define GDI_CEC_SEND_OPCODE_02_get_send_opcode_02(data)               (0x000000FF&(data))


#define GDI_CEC_SEND_OPERAND_NUMBER_02                                0x18037260
#define GDI_CEC_SEND_OPERAND_NUMBER_02_reg_addr                       "0xb8037260"
#define GDI_CEC_SEND_OPERAND_NUMBER_02_reg                            0xb8037260
#define GDI_CEC_SEND_OPERAND_NUMBER_02_inst_addr                      "0x0098"
#define GDI_CEC_SEND_OPERAND_NUMBER_02_inst                           0x0098
#define GDI_CEC_SEND_OPERAND_NUMBER_02_operand_number_02_shift        (0)
#define GDI_CEC_SEND_OPERAND_NUMBER_02_operand_number_02_mask         (0x00000003)
#define GDI_CEC_SEND_OPERAND_NUMBER_02_operand_number_02(data)        (0x00000003&(data))
#define GDI_CEC_SEND_OPERAND_NUMBER_02_get_operand_number_02(data)    (0x00000003&(data))


#define GDI_CEC_OPERAND_04                                            0x18037264
#define GDI_CEC_OPERAND_04_reg_addr                                   "0xb8037264"
#define GDI_CEC_OPERAND_04_reg                                        0xb8037264
#define GDI_CEC_OPERAND_04_inst_addr                                  "0x0099"
#define GDI_CEC_OPERAND_04_inst                                       0x0099
#define GDI_CEC_OPERAND_04_operand_04_shift                           (0)
#define GDI_CEC_OPERAND_04_operand_04_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_04_operand_04(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_04_get_operand_04(data)                       (0x000000FF&(data))


#define GDI_CEC_OPERAND_05                                            0x18037268
#define GDI_CEC_OPERAND_05_reg_addr                                   "0xb8037268"
#define GDI_CEC_OPERAND_05_reg                                        0xb8037268
#define GDI_CEC_OPERAND_05_inst_addr                                  "0x009A"
#define GDI_CEC_OPERAND_05_inst                                       0x009A
#define GDI_CEC_OPERAND_05_operand_05_shift                           (0)
#define GDI_CEC_OPERAND_05_operand_05_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_05_operand_05(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_05_get_operand_05(data)                       (0x000000FF&(data))


#define GDI_CEC_OPERAND_06                                            0x1803726c
#define GDI_CEC_OPERAND_06_reg_addr                                   "0xb803726c"
#define GDI_CEC_OPERAND_06_reg                                        0xb803726c
#define GDI_CEC_OPERAND_06_inst_addr                                  "0x009B"
#define GDI_CEC_OPERAND_06_inst                                       0x009B
#define GDI_CEC_OPERAND_06_operand_06_shift                           (0)
#define GDI_CEC_OPERAND_06_operand_06_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_06_operand_06(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_06_get_operand_06(data)                       (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_03                                     0x18037270
#define GDI_CEC_COMPARE_OPCODE_03_reg_addr                            "0xb8037270"
#define GDI_CEC_COMPARE_OPCODE_03_reg                                 0xb8037270
#define GDI_CEC_COMPARE_OPCODE_03_inst_addr                           "0x009C"
#define GDI_CEC_COMPARE_OPCODE_03_inst                                0x009C
#define GDI_CEC_COMPARE_OPCODE_03_compare_opcode_03_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_03_compare_opcode_03_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_03_compare_opcode_03(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_03_get_compare_opcode_03(data)         (0x000000FF&(data))


#define GDI_CEC_SEND_OPCODE_03                                        0x18037274
#define GDI_CEC_SEND_OPCODE_03_reg_addr                               "0xb8037274"
#define GDI_CEC_SEND_OPCODE_03_reg                                    0xb8037274
#define GDI_CEC_SEND_OPCODE_03_inst_addr                              "0x009D"
#define GDI_CEC_SEND_OPCODE_03_inst                                   0x009D
#define GDI_CEC_SEND_OPCODE_03_send_init_address_03_shift             (12)
#define GDI_CEC_SEND_OPCODE_03_init_address_03_shift                  (8)
#define GDI_CEC_SEND_OPCODE_03_send_opcode_03_shift                   (0)
#define GDI_CEC_SEND_OPCODE_03_send_init_address_03_mask              (0x00001000)
#define GDI_CEC_SEND_OPCODE_03_init_address_03_mask                   (0x00000F00)
#define GDI_CEC_SEND_OPCODE_03_send_opcode_03_mask                    (0x000000FF)
#define GDI_CEC_SEND_OPCODE_03_send_init_address_03(data)             (0x00001000&((data)<<12))
#define GDI_CEC_SEND_OPCODE_03_init_address_03(data)                  (0x00000F00&((data)<<8))
#define GDI_CEC_SEND_OPCODE_03_send_opcode_03(data)                   (0x000000FF&(data))
#define GDI_CEC_SEND_OPCODE_03_get_send_init_address_03(data)         ((0x00001000&(data))>>12)
#define GDI_CEC_SEND_OPCODE_03_get_init_address_03(data)              ((0x00000F00&(data))>>8)
#define GDI_CEC_SEND_OPCODE_03_get_send_opcode_03(data)               (0x000000FF&(data))


#define GDI_CEC_SEND_OPERAND_NUMBER_03                                0x18037278
#define GDI_CEC_SEND_OPERAND_NUMBER_03_reg_addr                       "0xb8037278"
#define GDI_CEC_SEND_OPERAND_NUMBER_03_reg                            0xb8037278
#define GDI_CEC_SEND_OPERAND_NUMBER_03_inst_addr                      "0x009E"
#define GDI_CEC_SEND_OPERAND_NUMBER_03_inst                           0x009E
#define GDI_CEC_SEND_OPERAND_NUMBER_03_operand_number_03_shift        (0)
#define GDI_CEC_SEND_OPERAND_NUMBER_03_operand_number_03_mask         (0x00000003)
#define GDI_CEC_SEND_OPERAND_NUMBER_03_operand_number_03(data)        (0x00000003&(data))
#define GDI_CEC_SEND_OPERAND_NUMBER_03_get_operand_number_03(data)    (0x00000003&(data))


#define GDI_CEC_OPERAND_07                                            0x1803727c
#define GDI_CEC_OPERAND_07_reg_addr                                   "0xb803727c"
#define GDI_CEC_OPERAND_07_reg                                        0xb803727c
#define GDI_CEC_OPERAND_07_inst_addr                                  "0x009F"
#define GDI_CEC_OPERAND_07_inst                                       0x009F
#define GDI_CEC_OPERAND_07_operand_07_shift                           (0)
#define GDI_CEC_OPERAND_07_operand_07_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_07_operand_07(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_07_get_operand_07(data)                       (0x000000FF&(data))


#define GDI_CEC_OPERAND_08                                            0x18037280
#define GDI_CEC_OPERAND_08_reg_addr                                   "0xb8037280"
#define GDI_CEC_OPERAND_08_reg                                        0xb8037280
#define GDI_CEC_OPERAND_08_inst_addr                                  "0x00A0"
#define GDI_CEC_OPERAND_08_inst                                       0x00A0
#define GDI_CEC_OPERAND_08_operand_08_shift                           (0)
#define GDI_CEC_OPERAND_08_operand_08_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_08_operand_08(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_08_get_operand_08(data)                       (0x000000FF&(data))


#define GDI_CEC_OPERAND_09                                            0x18037284
#define GDI_CEC_OPERAND_09_reg_addr                                   "0xb8037284"
#define GDI_CEC_OPERAND_09_reg                                        0xb8037284
#define GDI_CEC_OPERAND_09_inst_addr                                  "0x00A1"
#define GDI_CEC_OPERAND_09_inst                                       0x00A1
#define GDI_CEC_OPERAND_09_operand_09_shift                           (0)
#define GDI_CEC_OPERAND_09_operand_09_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_09_operand_09(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_09_get_operand_09(data)                       (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_04                                     0x18037288
#define GDI_CEC_COMPARE_OPCODE_04_reg_addr                            "0xb8037288"
#define GDI_CEC_COMPARE_OPCODE_04_reg                                 0xb8037288
#define GDI_CEC_COMPARE_OPCODE_04_inst_addr                           "0x00A2"
#define GDI_CEC_COMPARE_OPCODE_04_inst                                0x00A2
#define GDI_CEC_COMPARE_OPCODE_04_compare_opcode_04_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_04_compare_opcode_04_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_04_compare_opcode_04(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_04_get_compare_opcode_04(data)         (0x000000FF&(data))


#define GDI_CEC_SEND_OPCODE_04                                        0x1803728c
#define GDI_CEC_SEND_OPCODE_04_reg_addr                               "0xb803728c"
#define GDI_CEC_SEND_OPCODE_04_reg                                    0xb803728c
#define GDI_CEC_SEND_OPCODE_04_inst_addr                              "0x00A3"
#define GDI_CEC_SEND_OPCODE_04_inst                                   0x00A3
#define GDI_CEC_SEND_OPCODE_04_send_init_address_04_shift             (12)
#define GDI_CEC_SEND_OPCODE_04_init_address_04_shift                  (8)
#define GDI_CEC_SEND_OPCODE_04_send_opcode_04_shift                   (0)
#define GDI_CEC_SEND_OPCODE_04_send_init_address_04_mask              (0x00001000)
#define GDI_CEC_SEND_OPCODE_04_init_address_04_mask                   (0x00000F00)
#define GDI_CEC_SEND_OPCODE_04_send_opcode_04_mask                    (0x000000FF)
#define GDI_CEC_SEND_OPCODE_04_send_init_address_04(data)             (0x00001000&((data)<<12))
#define GDI_CEC_SEND_OPCODE_04_init_address_04(data)                  (0x00000F00&((data)<<8))
#define GDI_CEC_SEND_OPCODE_04_send_opcode_04(data)                   (0x000000FF&(data))
#define GDI_CEC_SEND_OPCODE_04_get_send_init_address_04(data)         ((0x00001000&(data))>>12)
#define GDI_CEC_SEND_OPCODE_04_get_init_address_04(data)              ((0x00000F00&(data))>>8)
#define GDI_CEC_SEND_OPCODE_04_get_send_opcode_04(data)               (0x000000FF&(data))


#define GDI_CEC_SEND_OPERAND_NUMBER_04                                0x18037290
#define GDI_CEC_SEND_OPERAND_NUMBER_04_reg_addr                       "0xb8037290"
#define GDI_CEC_SEND_OPERAND_NUMBER_04_reg                            0xb8037290
#define GDI_CEC_SEND_OPERAND_NUMBER_04_inst_addr                      "0x00A4"
#define GDI_CEC_SEND_OPERAND_NUMBER_04_inst                           0x00A4
#define GDI_CEC_SEND_OPERAND_NUMBER_04_operand_number_04_shift        (0)
#define GDI_CEC_SEND_OPERAND_NUMBER_04_operand_number_04_mask         (0x00000003)
#define GDI_CEC_SEND_OPERAND_NUMBER_04_operand_number_04(data)        (0x00000003&(data))
#define GDI_CEC_SEND_OPERAND_NUMBER_04_get_operand_number_04(data)    (0x00000003&(data))


#define GDI_CEC_OPERAND_10                                            0x18037294
#define GDI_CEC_OPERAND_10_reg_addr                                   "0xb8037294"
#define GDI_CEC_OPERAND_10_reg                                        0xb8037294
#define GDI_CEC_OPERAND_10_inst_addr                                  "0x00A5"
#define GDI_CEC_OPERAND_10_inst                                       0x00A5
#define GDI_CEC_OPERAND_10_operand_10_shift                           (0)
#define GDI_CEC_OPERAND_10_operand_10_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_10_operand_10(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_10_get_operand_10(data)                       (0x000000FF&(data))


#define GDI_CEC_OPERAND_11                                            0x18037298
#define GDI_CEC_OPERAND_11_reg_addr                                   "0xb8037298"
#define GDI_CEC_OPERAND_11_reg                                        0xb8037298
#define GDI_CEC_OPERAND_11_inst_addr                                  "0x00A6"
#define GDI_CEC_OPERAND_11_inst                                       0x00A6
#define GDI_CEC_OPERAND_11_operand_11_shift                           (0)
#define GDI_CEC_OPERAND_11_operand_11_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_11_operand_11(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_11_get_operand_11(data)                       (0x000000FF&(data))


#define GDI_CEC_OPERAND_12                                            0x1803729c
#define GDI_CEC_OPERAND_12_reg_addr                                   "0xb803729c"
#define GDI_CEC_OPERAND_12_reg                                        0xb803729c
#define GDI_CEC_OPERAND_12_inst_addr                                  "0x00A7"
#define GDI_CEC_OPERAND_12_inst                                       0x00A7
#define GDI_CEC_OPERAND_12_operand_12_shift                           (0)
#define GDI_CEC_OPERAND_12_operand_12_mask                            (0x000000FF)
#define GDI_CEC_OPERAND_12_operand_12(data)                           (0x000000FF&(data))
#define GDI_CEC_OPERAND_12_get_operand_12(data)                       (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_05                                     0x180372a0
#define GDI_CEC_COMPARE_OPCODE_05_reg_addr                            "0xb80372a0"
#define GDI_CEC_COMPARE_OPCODE_05_reg                                 0xb80372a0
#define GDI_CEC_COMPARE_OPCODE_05_inst_addr                           "0x00A8"
#define GDI_CEC_COMPARE_OPCODE_05_inst                                0x00A8
#define GDI_CEC_COMPARE_OPCODE_05_compare_opcode_05_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_05_compare_opcode_05_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_05_compare_opcode_05(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_05_get_compare_opcode_05(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_06                                     0x180372a4
#define GDI_CEC_COMPARE_OPCODE_06_reg_addr                            "0xb80372a4"
#define GDI_CEC_COMPARE_OPCODE_06_reg                                 0xb80372a4
#define GDI_CEC_COMPARE_OPCODE_06_inst_addr                           "0x00A9"
#define GDI_CEC_COMPARE_OPCODE_06_inst                                0x00A9
#define GDI_CEC_COMPARE_OPCODE_06_compare_opcode_06_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_06_compare_opcode_06_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_06_compare_opcode_06(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_06_get_compare_opcode_06(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_07                                     0x180372a8
#define GDI_CEC_COMPARE_OPCODE_07_reg_addr                            "0xb80372a8"
#define GDI_CEC_COMPARE_OPCODE_07_reg                                 0xb80372a8
#define GDI_CEC_COMPARE_OPCODE_07_inst_addr                           "0x00AA"
#define GDI_CEC_COMPARE_OPCODE_07_inst                                0x00AA
#define GDI_CEC_COMPARE_OPCODE_07_compare_opcode_07_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_07_compare_opcode_07_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_07_compare_opcode_07(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_07_get_compare_opcode_07(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_08                                     0x180372ac
#define GDI_CEC_COMPARE_OPCODE_08_reg_addr                            "0xb80372ac"
#define GDI_CEC_COMPARE_OPCODE_08_reg                                 0xb80372ac
#define GDI_CEC_COMPARE_OPCODE_08_inst_addr                           "0x00AB"
#define GDI_CEC_COMPARE_OPCODE_08_inst                                0x00AB
#define GDI_CEC_COMPARE_OPCODE_08_compare_opcode_08_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_08_compare_opcode_08_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_08_compare_opcode_08(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_08_get_compare_opcode_08(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_09                                     0x180372b0
#define GDI_CEC_COMPARE_OPCODE_09_reg_addr                            "0xb80372b0"
#define GDI_CEC_COMPARE_OPCODE_09_reg                                 0xb80372b0
#define GDI_CEC_COMPARE_OPCODE_09_inst_addr                           "0x00AC"
#define GDI_CEC_COMPARE_OPCODE_09_inst                                0x00AC
#define GDI_CEC_COMPARE_OPCODE_09_compare_opcode_09_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_09_compare_opcode_09_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_09_compare_opcode_09(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_09_get_compare_opcode_09(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_10                                     0x180372b4
#define GDI_CEC_COMPARE_OPCODE_10_reg_addr                            "0xb80372b4"
#define GDI_CEC_COMPARE_OPCODE_10_reg                                 0xb80372b4
#define GDI_CEC_COMPARE_OPCODE_10_inst_addr                           "0x00AD"
#define GDI_CEC_COMPARE_OPCODE_10_inst                                0x00AD
#define GDI_CEC_COMPARE_OPCODE_10_compare_opcode_10_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_10_compare_opcode_10_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_10_compare_opcode_10(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_10_get_compare_opcode_10(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_11                                     0x180372b8
#define GDI_CEC_COMPARE_OPCODE_11_reg_addr                            "0xb80372b8"
#define GDI_CEC_COMPARE_OPCODE_11_reg                                 0xb80372b8
#define GDI_CEC_COMPARE_OPCODE_11_inst_addr                           "0x00AE"
#define GDI_CEC_COMPARE_OPCODE_11_inst                                0x00AE
#define GDI_CEC_COMPARE_OPCODE_11_compare_opcode_11_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_11_compare_opcode_11_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_11_compare_opcode_11(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_11_get_compare_opcode_11(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_12                                     0x180372bc
#define GDI_CEC_COMPARE_OPCODE_12_reg_addr                            "0xb80372bc"
#define GDI_CEC_COMPARE_OPCODE_12_reg                                 0xb80372bc
#define GDI_CEC_COMPARE_OPCODE_12_inst_addr                           "0x00AF"
#define GDI_CEC_COMPARE_OPCODE_12_inst                                0x00AF
#define GDI_CEC_COMPARE_OPCODE_12_compare_opcode_12_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_12_compare_opcode_12_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_12_compare_opcode_12(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_12_get_compare_opcode_12(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_13                                     0x180372c0
#define GDI_CEC_COMPARE_OPCODE_13_reg_addr                            "0xb80372c0"
#define GDI_CEC_COMPARE_OPCODE_13_reg                                 0xb80372c0
#define GDI_CEC_COMPARE_OPCODE_13_inst_addr                           "0x00B0"
#define GDI_CEC_COMPARE_OPCODE_13_inst                                0x00B0
#define GDI_CEC_COMPARE_OPCODE_13_compare_opcode_13_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_13_compare_opcode_13_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_13_compare_opcode_13(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_13_get_compare_opcode_13(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_14                                     0x180372c4
#define GDI_CEC_COMPARE_OPCODE_14_reg_addr                            "0xb80372c4"
#define GDI_CEC_COMPARE_OPCODE_14_reg                                 0xb80372c4
#define GDI_CEC_COMPARE_OPCODE_14_inst_addr                           "0x00B1"
#define GDI_CEC_COMPARE_OPCODE_14_inst                                0x00B1
#define GDI_CEC_COMPARE_OPCODE_14_compare_opcode_14_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_14_compare_opcode_14_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_14_compare_opcode_14(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_14_get_compare_opcode_14(data)         (0x000000FF&(data))


#define GDI_CEC_COMPARE_OPCODE_15                                     0x180372c8
#define GDI_CEC_COMPARE_OPCODE_15_reg_addr                            "0xb80372c8"
#define GDI_CEC_COMPARE_OPCODE_15_reg                                 0xb80372c8
#define GDI_CEC_COMPARE_OPCODE_15_inst_addr                           "0x00B2"
#define GDI_CEC_COMPARE_OPCODE_15_inst                                0x00B2
#define GDI_CEC_COMPARE_OPCODE_15_compare_opcode_15_shift             (0)
#define GDI_CEC_COMPARE_OPCODE_15_compare_opcode_15_mask              (0x000000FF)
#define GDI_CEC_COMPARE_OPCODE_15_compare_opcode_15(data)             (0x000000FF&(data))
#define GDI_CEC_COMPARE_OPCODE_15_get_compare_opcode_15(data)         (0x000000FF&(data))


#define GDI_CEC_OPCODE_ENABLE                                         0x180372cc
#define GDI_CEC_OPCODE_ENABLE_reg_addr                                "0xb80372cc"
#define GDI_CEC_OPCODE_ENABLE_reg                                     0xb80372cc
#define GDI_CEC_OPCODE_ENABLE_inst_addr                               "0x00B3"
#define GDI_CEC_OPCODE_ENABLE_inst                                    0x00B3
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


#define GDI_POWER_SAVING_MODE                                         0x180372d0
#define GDI_POWER_SAVING_MODE_reg_addr                                "0xb80372d0"
#define GDI_POWER_SAVING_MODE_reg                                     0xb80372d0
#define GDI_POWER_SAVING_MODE_inst_addr                               "0x00B4"
#define GDI_POWER_SAVING_MODE_inst                                    0x00B4
#define GDI_POWER_SAVING_MODE_irq_pending_shift                       (31)
#define GDI_POWER_SAVING_MODE_cec_msg_status_01_shift                 (25)
#define GDI_POWER_SAVING_MODE_cec_msg_status_02_shift                 (24)
#define GDI_POWER_SAVING_MODE_irq_by_cec_receive_special_cmd_shift    (8)
#define GDI_POWER_SAVING_MODE_cec_rpu_en_shift                        (4)
#define GDI_POWER_SAVING_MODE_cec_rsel_shift                          (0)
#define GDI_POWER_SAVING_MODE_irq_pending_mask                        (0x80000000)
#define GDI_POWER_SAVING_MODE_cec_msg_status_01_mask                  (0x02000000)
#define GDI_POWER_SAVING_MODE_cec_msg_status_02_mask                  (0x01000000)
#define GDI_POWER_SAVING_MODE_irq_by_cec_receive_special_cmd_mask     (0x00000100)
#define GDI_POWER_SAVING_MODE_cec_rpu_en_mask                         (0x00000010)
#define GDI_POWER_SAVING_MODE_cec_rsel_mask                           (0x00000007)
#define GDI_POWER_SAVING_MODE_irq_pending(data)                       (0x80000000&((data)<<31))
#define GDI_POWER_SAVING_MODE_cec_msg_status_01(data)                 (0x02000000&((data)<<25))
#define GDI_POWER_SAVING_MODE_cec_msg_status_02(data)                 (0x01000000&((data)<<24))
#define GDI_POWER_SAVING_MODE_irq_by_cec_receive_special_cmd(data)    (0x00000100&((data)<<8))
#define GDI_POWER_SAVING_MODE_cec_rpu_en(data)                        (0x00000010&((data)<<4))
#define GDI_POWER_SAVING_MODE_cec_rsel(data)                          (0x00000007&(data))
#define GDI_POWER_SAVING_MODE_get_irq_pending(data)                   ((0x80000000&(data))>>31)
#define GDI_POWER_SAVING_MODE_get_cec_msg_status_01(data)             ((0x02000000&(data))>>25)
#define GDI_POWER_SAVING_MODE_get_cec_msg_status_02(data)             ((0x01000000&(data))>>24)
#define GDI_POWER_SAVING_MODE_get_irq_by_cec_receive_special_cmd(data)  ((0x00000100&(data))>>8)
#define GDI_POWER_SAVING_MODE_get_cec_rpu_en(data)                    ((0x00000010&(data))>>4)
#define GDI_POWER_SAVING_MODE_get_cec_rsel(data)                      (0x00000007&(data))


#define CEC_RXACKTCR0                                                 0x180372d4
#define CEC_RXACKTCR0_reg_addr                                        "0xb80372d4"
#define CEC_RXACKTCR0_reg                                             0xb80372d4
#define CEC_RXACKTCR0_inst_addr                                       "0x00B5"
#define CEC_RXACKTCR0_inst                                            0x00B5
#define CEC_RXACKTCR0_rx_ack_wait_1_sel_shift                         (26)
#define CEC_RXACKTCR0_rx_ack_wait_2_sel_shift                         (25)
#define CEC_RXACKTCR0_rx_ack_wait_3_sel_shift                         (24)
#define CEC_RXACKTCR0_rx_ack_wait_1_shift                             (16)
#define CEC_RXACKTCR0_rx_ack_wait_2_shift                             (8)
#define CEC_RXACKTCR0_rx_ack_wait_3_shift                             (0)
#define CEC_RXACKTCR0_rx_ack_wait_1_sel_mask                          (0x04000000)
#define CEC_RXACKTCR0_rx_ack_wait_2_sel_mask                          (0x02000000)
#define CEC_RXACKTCR0_rx_ack_wait_3_sel_mask                          (0x01000000)
#define CEC_RXACKTCR0_rx_ack_wait_1_mask                              (0x00FF0000)
#define CEC_RXACKTCR0_rx_ack_wait_2_mask                              (0x0000FF00)
#define CEC_RXACKTCR0_rx_ack_wait_3_mask                              (0x000000FF)
#define CEC_RXACKTCR0_rx_ack_wait_1_sel(data)                         (0x04000000&((data)<<26))
#define CEC_RXACKTCR0_rx_ack_wait_2_sel(data)                         (0x02000000&((data)<<25))
#define CEC_RXACKTCR0_rx_ack_wait_3_sel(data)                         (0x01000000&((data)<<24))
#define CEC_RXACKTCR0_rx_ack_wait_1(data)                             (0x00FF0000&((data)<<16))
#define CEC_RXACKTCR0_rx_ack_wait_2(data)                             (0x0000FF00&((data)<<8))
#define CEC_RXACKTCR0_rx_ack_wait_3(data)                             (0x000000FF&(data))
#define CEC_RXACKTCR0_get_rx_ack_wait_1_sel(data)                     ((0x04000000&(data))>>26)
#define CEC_RXACKTCR0_get_rx_ack_wait_2_sel(data)                     ((0x02000000&(data))>>25)
#define CEC_RXACKTCR0_get_rx_ack_wait_3_sel(data)                     ((0x01000000&(data))>>24)
#define CEC_RXACKTCR0_get_rx_ack_wait_1(data)                         ((0x00FF0000&(data))>>16)
#define CEC_RXACKTCR0_get_rx_ack_wait_2(data)                         ((0x0000FF00&(data))>>8)
#define CEC_RXACKTCR0_get_rx_ack_wait_3(data)                         (0x000000FF&(data))


#define CEC_RXACKTCR1                                                 0x180372d8
#define CEC_RXACKTCR1_reg_addr                                        "0xb80372d8"
#define CEC_RXACKTCR1_reg                                             0xb80372d8
#define CEC_RXACKTCR1_inst_addr                                       "0x00B6"
#define CEC_RXACKTCR1_inst                                            0x00B6
#define CEC_RXACKTCR1_rx_ack_low_sel_shift                            (26)
#define CEC_RXACKTCR1_rx_ack_bit_sel_shift                            (25)
#define CEC_RXACKTCR1_rx_ack_line_err_sel_shift                       (24)
#define CEC_RXACKTCR1_rx_ack_low_shift                                (16)
#define CEC_RXACKTCR1_rx_ack_bit_shift                                (8)
#define CEC_RXACKTCR1_rx_ack_line_err_shift                           (0)
#define CEC_RXACKTCR1_rx_ack_low_sel_mask                             (0x04000000)
#define CEC_RXACKTCR1_rx_ack_bit_sel_mask                             (0x02000000)
#define CEC_RXACKTCR1_rx_ack_line_err_sel_mask                        (0x01000000)
#define CEC_RXACKTCR1_rx_ack_low_mask                                 (0x00FF0000)
#define CEC_RXACKTCR1_rx_ack_bit_mask                                 (0x0000FF00)
#define CEC_RXACKTCR1_rx_ack_line_err_mask                            (0x000000FF)
#define CEC_RXACKTCR1_rx_ack_low_sel(data)                            (0x04000000&((data)<<26))
#define CEC_RXACKTCR1_rx_ack_bit_sel(data)                            (0x02000000&((data)<<25))
#define CEC_RXACKTCR1_rx_ack_line_err_sel(data)                       (0x01000000&((data)<<24))
#define CEC_RXACKTCR1_rx_ack_low(data)                                (0x00FF0000&((data)<<16))
#define CEC_RXACKTCR1_rx_ack_bit(data)                                (0x0000FF00&((data)<<8))
#define CEC_RXACKTCR1_rx_ack_line_err(data)                           (0x000000FF&(data))
#define CEC_RXACKTCR1_get_rx_ack_low_sel(data)                        ((0x04000000&(data))>>26)
#define CEC_RXACKTCR1_get_rx_ack_bit_sel(data)                        ((0x02000000&(data))>>25)
#define CEC_RXACKTCR1_get_rx_ack_line_err_sel(data)                   ((0x01000000&(data))>>24)
#define CEC_RXACKTCR1_get_rx_ack_low(data)                            ((0x00FF0000&(data))>>16)
#define CEC_RXACKTCR1_get_rx_ack_bit(data)                            ((0x0000FF00&(data))>>8)
#define CEC_RXACKTCR1_get_rx_ack_line_err(data)                       (0x000000FF&(data))
#endif
