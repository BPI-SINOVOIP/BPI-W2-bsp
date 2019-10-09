/**************************************************************
// Spec Version                  : 1.1
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/7/8 10:34:40
***************************************************************/


#ifndef _DP_REG_H_INCLUDED_
#define _DP_REG_H_INCLUDED_
#ifdef  _DP_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     secure_state:3;
}DP_STATE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     cmp_en:1;
}DP_CTRL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     equal:1;
}DP_PW_STATUS;

typedef struct 
{
unsigned int     dat:32;
}DP_PW;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     uart_tx_disable:1;
unsigned int     uart_rx_disable:1;
unsigned int     hif_disable:1;
unsigned int     jtag_lx_disable:1;
}DP_DBG_STATUS;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     bist_drf_test_resume:1;
unsigned int     bist_drf_en:1;
unsigned int     bist_en:1;
}DP_BIST_CTRL;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     rme:1;
unsigned int     rm:4;
}DP_BIST_RM;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     bist_fail0:1;
unsigned int     bist_done:1;
}DP_BIST_ST;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     drf_bist_start_pause:1;
unsigned int     reserved_1:14;
unsigned int     drf_bist_fail0:1;
unsigned int     drf_bist_done:1;
}DP_DRF_ST;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     rx_off:1;
unsigned int     tx_off:1;
}DP_UART_CTL;

#endif

#define DP_STATE                                                                     0x18017800
#define DP_STATE_reg_addr                                                            "0xB8017800"
#define DP_STATE_reg                                                                 0xB8017800
#define set_DP_STATE_reg(data)   (*((volatile unsigned int*) DP_STATE_reg)=data)
#define get_DP_STATE_reg   (*((volatile unsigned int*) DP_STATE_reg))
#define DP_STATE_inst_adr                                                            "0x0000"
#define DP_STATE_inst                                                                0x0000
#define DP_STATE_secure_state_shift                                                  (0)
#define DP_STATE_secure_state_mask                                                   (0x00000007)
#define DP_STATE_secure_state(data)                                                  (0x00000007&((data)<<0))
#define DP_STATE_secure_state_src(data)                                              ((0x00000007&(data))>>0)
#define DP_STATE_get_secure_state(data)                                              ((0x00000007&(data))>>0)


#define DP_CTRL                                                                      0x18017804
#define DP_CTRL_reg_addr                                                             "0xB8017804"
#define DP_CTRL_reg                                                                  0xB8017804
#define set_DP_CTRL_reg(data)   (*((volatile unsigned int*) DP_CTRL_reg)=data)
#define get_DP_CTRL_reg   (*((volatile unsigned int*) DP_CTRL_reg))
#define DP_CTRL_inst_adr                                                             "0x0001"
#define DP_CTRL_inst                                                                 0x0001
#define DP_CTRL_cmp_en_shift                                                         (0)
#define DP_CTRL_cmp_en_mask                                                          (0x00000001)
#define DP_CTRL_cmp_en(data)                                                         (0x00000001&((data)<<0))
#define DP_CTRL_cmp_en_src(data)                                                     ((0x00000001&(data))>>0)
#define DP_CTRL_get_cmp_en(data)                                                     ((0x00000001&(data))>>0)


#define DP_PW_STATUS                                                                 0x18017808
#define DP_PW_STATUS_reg_addr                                                        "0xB8017808"
#define DP_PW_STATUS_reg                                                             0xB8017808
#define set_DP_PW_STATUS_reg(data)   (*((volatile unsigned int*) DP_PW_STATUS_reg)=data)
#define get_DP_PW_STATUS_reg   (*((volatile unsigned int*) DP_PW_STATUS_reg))
#define DP_PW_STATUS_inst_adr                                                        "0x0002"
#define DP_PW_STATUS_inst                                                            0x0002
#define DP_PW_STATUS_equal_shift                                                     (0)
#define DP_PW_STATUS_equal_mask                                                      (0x00000001)
#define DP_PW_STATUS_equal(data)                                                     (0x00000001&((data)<<0))
#define DP_PW_STATUS_equal_src(data)                                                 ((0x00000001&(data))>>0)
#define DP_PW_STATUS_get_equal(data)                                                 ((0x00000001&(data))>>0)


#define DP_PW_0                                                                      0x18017810
#define DP_PW_1                                                                      0x18017814
#define DP_PW_2                                                                      0x18017818
#define DP_PW_3                                                                      0x1801781C
#define DP_PW_0_reg_addr                                                             "0xB8017810"
#define DP_PW_1_reg_addr                                                             "0xB8017814"
#define DP_PW_2_reg_addr                                                             "0xB8017818"
#define DP_PW_3_reg_addr                                                             "0xB801781C"
#define DP_PW_0_reg                                                                  0xB8017810
#define DP_PW_1_reg                                                                  0xB8017814
#define DP_PW_2_reg                                                                  0xB8017818
#define DP_PW_3_reg                                                                  0xB801781C
#define set_DP_PW_0_reg(data)   (*((volatile unsigned int*) DP_PW_0_reg)=data)
#define set_DP_PW_1_reg(data)   (*((volatile unsigned int*) DP_PW_1_reg)=data)
#define set_DP_PW_2_reg(data)   (*((volatile unsigned int*) DP_PW_2_reg)=data)
#define set_DP_PW_3_reg(data)   (*((volatile unsigned int*) DP_PW_3_reg)=data)
#define get_DP_PW_0_reg   (*((volatile unsigned int*) DP_PW_0_reg))
#define get_DP_PW_1_reg   (*((volatile unsigned int*) DP_PW_1_reg))
#define get_DP_PW_2_reg   (*((volatile unsigned int*) DP_PW_2_reg))
#define get_DP_PW_3_reg   (*((volatile unsigned int*) DP_PW_3_reg))
#define DP_PW_0_inst_adr                                                             "0x0004"
#define DP_PW_1_inst_adr                                                             "0x0005"
#define DP_PW_2_inst_adr                                                             "0x0006"
#define DP_PW_3_inst_adr                                                             "0x0007"
#define DP_PW_0_inst                                                                 0x0004
#define DP_PW_1_inst                                                                 0x0005
#define DP_PW_2_inst                                                                 0x0006
#define DP_PW_3_inst                                                                 0x0007
#define DP_PW_dat_shift                                                              (0)
#define DP_PW_dat_mask                                                               (0xFFFFFFFF)
#define DP_PW_dat(data)                                                              (0xFFFFFFFF&((data)<<0))
#define DP_PW_dat_src(data)                                                          ((0xFFFFFFFF&(data))>>0)
#define DP_PW_get_dat(data)                                                          ((0xFFFFFFFF&(data))>>0)


#define DP_DBG_STATUS                                                                0x18017820
#define DP_DBG_STATUS_reg_addr                                                       "0xB8017820"
#define DP_DBG_STATUS_reg                                                            0xB8017820
#define set_DP_DBG_STATUS_reg(data)   (*((volatile unsigned int*) DP_DBG_STATUS_reg)=data)
#define get_DP_DBG_STATUS_reg   (*((volatile unsigned int*) DP_DBG_STATUS_reg))
#define DP_DBG_STATUS_inst_adr                                                       "0x0008"
#define DP_DBG_STATUS_inst                                                           0x0008
#define DP_DBG_STATUS_uart_tx_disable_shift                                          (3)
#define DP_DBG_STATUS_uart_tx_disable_mask                                           (0x00000008)
#define DP_DBG_STATUS_uart_tx_disable(data)                                          (0x00000008&((data)<<3))
#define DP_DBG_STATUS_uart_tx_disable_src(data)                                      ((0x00000008&(data))>>3)
#define DP_DBG_STATUS_get_uart_tx_disable(data)                                      ((0x00000008&(data))>>3)
#define DP_DBG_STATUS_uart_rx_disable_shift                                          (2)
#define DP_DBG_STATUS_uart_rx_disable_mask                                           (0x00000004)
#define DP_DBG_STATUS_uart_rx_disable(data)                                          (0x00000004&((data)<<2))
#define DP_DBG_STATUS_uart_rx_disable_src(data)                                      ((0x00000004&(data))>>2)
#define DP_DBG_STATUS_get_uart_rx_disable(data)                                      ((0x00000004&(data))>>2)
#define DP_DBG_STATUS_hif_disable_shift                                              (1)
#define DP_DBG_STATUS_hif_disable_mask                                               (0x00000002)
#define DP_DBG_STATUS_hif_disable(data)                                              (0x00000002&((data)<<1))
#define DP_DBG_STATUS_hif_disable_src(data)                                          ((0x00000002&(data))>>1)
#define DP_DBG_STATUS_get_hif_disable(data)                                          ((0x00000002&(data))>>1)
#define DP_DBG_STATUS_jtag_lx_disable_shift                                          (0)
#define DP_DBG_STATUS_jtag_lx_disable_mask                                           (0x00000001)
#define DP_DBG_STATUS_jtag_lx_disable(data)                                          (0x00000001&((data)<<0))
#define DP_DBG_STATUS_jtag_lx_disable_src(data)                                      ((0x00000001&(data))>>0)
#define DP_DBG_STATUS_get_jtag_lx_disable(data)                                      ((0x00000001&(data))>>0)


#define DP_BIST_CTRL                                                                 0x18017824
#define DP_BIST_CTRL_reg_addr                                                        "0xB8017824"
#define DP_BIST_CTRL_reg                                                             0xB8017824
#define set_DP_BIST_CTRL_reg(data)   (*((volatile unsigned int*) DP_BIST_CTRL_reg)=data)
#define get_DP_BIST_CTRL_reg   (*((volatile unsigned int*) DP_BIST_CTRL_reg))
#define DP_BIST_CTRL_inst_adr                                                        "0x0009"
#define DP_BIST_CTRL_inst                                                            0x0009
#define DP_BIST_CTRL_bist_drf_test_resume_shift                                      (2)
#define DP_BIST_CTRL_bist_drf_test_resume_mask                                       (0x00000004)
#define DP_BIST_CTRL_bist_drf_test_resume(data)                                      (0x00000004&((data)<<2))
#define DP_BIST_CTRL_bist_drf_test_resume_src(data)                                  ((0x00000004&(data))>>2)
#define DP_BIST_CTRL_get_bist_drf_test_resume(data)                                  ((0x00000004&(data))>>2)
#define DP_BIST_CTRL_bist_drf_en_shift                                               (1)
#define DP_BIST_CTRL_bist_drf_en_mask                                                (0x00000002)
#define DP_BIST_CTRL_bist_drf_en(data)                                               (0x00000002&((data)<<1))
#define DP_BIST_CTRL_bist_drf_en_src(data)                                           ((0x00000002&(data))>>1)
#define DP_BIST_CTRL_get_bist_drf_en(data)                                           ((0x00000002&(data))>>1)
#define DP_BIST_CTRL_bist_en_shift                                                   (0)
#define DP_BIST_CTRL_bist_en_mask                                                    (0x00000001)
#define DP_BIST_CTRL_bist_en(data)                                                   (0x00000001&((data)<<0))
#define DP_BIST_CTRL_bist_en_src(data)                                               ((0x00000001&(data))>>0)
#define DP_BIST_CTRL_get_bist_en(data)                                               ((0x00000001&(data))>>0)


#define DP_BIST_RM                                                                   0x18017828
#define DP_BIST_RM_reg_addr                                                          "0xB8017828"
#define DP_BIST_RM_reg                                                               0xB8017828
#define set_DP_BIST_RM_reg(data)   (*((volatile unsigned int*) DP_BIST_RM_reg)=data)
#define get_DP_BIST_RM_reg   (*((volatile unsigned int*) DP_BIST_RM_reg))
#define DP_BIST_RM_inst_adr                                                          "0x000A"
#define DP_BIST_RM_inst                                                              0x000A
#define DP_BIST_RM_rme_shift                                                         (4)
#define DP_BIST_RM_rme_mask                                                          (0x00000010)
#define DP_BIST_RM_rme(data)                                                         (0x00000010&((data)<<4))
#define DP_BIST_RM_rme_src(data)                                                     ((0x00000010&(data))>>4)
#define DP_BIST_RM_get_rme(data)                                                     ((0x00000010&(data))>>4)
#define DP_BIST_RM_rm_shift                                                          (0)
#define DP_BIST_RM_rm_mask                                                           (0x0000000F)
#define DP_BIST_RM_rm(data)                                                          (0x0000000F&((data)<<0))
#define DP_BIST_RM_rm_src(data)                                                      ((0x0000000F&(data))>>0)
#define DP_BIST_RM_get_rm(data)                                                      ((0x0000000F&(data))>>0)


#define DP_BIST_ST                                                                   0x1801782c
#define DP_BIST_ST_reg_addr                                                          "0xB801782C"
#define DP_BIST_ST_reg                                                               0xB801782C
#define set_DP_BIST_ST_reg(data)   (*((volatile unsigned int*) DP_BIST_ST_reg)=data)
#define get_DP_BIST_ST_reg   (*((volatile unsigned int*) DP_BIST_ST_reg))
#define DP_BIST_ST_inst_adr                                                          "0x000B"
#define DP_BIST_ST_inst                                                              0x000B
#define DP_BIST_ST_bist_fail0_shift                                                  (1)
#define DP_BIST_ST_bist_fail0_mask                                                   (0x00000002)
#define DP_BIST_ST_bist_fail0(data)                                                  (0x00000002&((data)<<1))
#define DP_BIST_ST_bist_fail0_src(data)                                              ((0x00000002&(data))>>1)
#define DP_BIST_ST_get_bist_fail0(data)                                              ((0x00000002&(data))>>1)
#define DP_BIST_ST_bist_done_shift                                                   (0)
#define DP_BIST_ST_bist_done_mask                                                    (0x00000001)
#define DP_BIST_ST_bist_done(data)                                                   (0x00000001&((data)<<0))
#define DP_BIST_ST_bist_done_src(data)                                               ((0x00000001&(data))>>0)
#define DP_BIST_ST_get_bist_done(data)                                               ((0x00000001&(data))>>0)


#define DP_DRF_ST                                                                    0x18017830
#define DP_DRF_ST_reg_addr                                                           "0xB8017830"
#define DP_DRF_ST_reg                                                                0xB8017830
#define set_DP_DRF_ST_reg(data)   (*((volatile unsigned int*) DP_DRF_ST_reg)=data)
#define get_DP_DRF_ST_reg   (*((volatile unsigned int*) DP_DRF_ST_reg))
#define DP_DRF_ST_inst_adr                                                           "0x000C"
#define DP_DRF_ST_inst                                                               0x000C
#define DP_DRF_ST_drf_bist_start_pause_shift                                         (16)
#define DP_DRF_ST_drf_bist_start_pause_mask                                          (0x00010000)
#define DP_DRF_ST_drf_bist_start_pause(data)                                         (0x00010000&((data)<<16))
#define DP_DRF_ST_drf_bist_start_pause_src(data)                                     ((0x00010000&(data))>>16)
#define DP_DRF_ST_get_drf_bist_start_pause(data)                                     ((0x00010000&(data))>>16)
#define DP_DRF_ST_drf_bist_fail0_shift                                               (1)
#define DP_DRF_ST_drf_bist_fail0_mask                                                (0x00000002)
#define DP_DRF_ST_drf_bist_fail0(data)                                               (0x00000002&((data)<<1))
#define DP_DRF_ST_drf_bist_fail0_src(data)                                           ((0x00000002&(data))>>1)
#define DP_DRF_ST_get_drf_bist_fail0(data)                                           ((0x00000002&(data))>>1)
#define DP_DRF_ST_drf_bist_done_shift                                                (0)
#define DP_DRF_ST_drf_bist_done_mask                                                 (0x00000001)
#define DP_DRF_ST_drf_bist_done(data)                                                (0x00000001&((data)<<0))
#define DP_DRF_ST_drf_bist_done_src(data)                                            ((0x00000001&(data))>>0)
#define DP_DRF_ST_get_drf_bist_done(data)                                            ((0x00000001&(data))>>0)


#define DP_UART_CTL                                                                  0x18017840
#define DP_UART_CTL_reg_addr                                                         "0xB8017840"
#define DP_UART_CTL_reg                                                              0xB8017840
#define set_DP_UART_CTL_reg(data)   (*((volatile unsigned int*) DP_UART_CTL_reg)=data)
#define get_DP_UART_CTL_reg   (*((volatile unsigned int*) DP_UART_CTL_reg))
#define DP_UART_CTL_inst_adr                                                         "0x0010"
#define DP_UART_CTL_inst                                                             0x0010
#define DP_UART_CTL_rx_off_shift                                                     (1)
#define DP_UART_CTL_rx_off_mask                                                      (0x00000002)
#define DP_UART_CTL_rx_off(data)                                                     (0x00000002&((data)<<1))
#define DP_UART_CTL_rx_off_src(data)                                                 ((0x00000002&(data))>>1)
#define DP_UART_CTL_get_rx_off(data)                                                 ((0x00000002&(data))>>1)
#define DP_UART_CTL_tx_off_shift                                                     (0)
#define DP_UART_CTL_tx_off_mask                                                      (0x00000001)
#define DP_UART_CTL_tx_off(data)                                                     (0x00000001&((data)<<0))
#define DP_UART_CTL_tx_off_src(data)                                                 ((0x00000001&(data))>>0)
#define DP_UART_CTL_get_tx_off(data)                                                 ((0x00000001&(data))>>0)


#endif
