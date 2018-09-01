/**************************************************************
// Spec Version                  : 0.0.7
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/7/25 16:46:20
***************************************************************/


#ifndef _MIS_REG_H_INCLUDED_
#define _MIS_REG_H_INCLUDED_
#ifdef  _MIS_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     gspi_int:1;
unsigned int     reserved_1:6;
unsigned int     gpioda_int:1;
unsigned int     gpioa_int:1;
unsigned int     reserved_2:6;
unsigned int     rtc_date_int:1;
unsigned int     rtc_hour_int:1;
unsigned int     rtc_min_int:1;
unsigned int     rtc_hsec_int:1;
unsigned int     reserved_3:1;
unsigned int     tc1_int:1;
unsigned int     tc0_int:1;
unsigned int     ur1_to_int:1;
unsigned int     reserved_4:2;
unsigned int     wdog_nmi_int:1;
unsigned int     reserved_5:1;
unsigned int     write_data:1;
}MIS_UMSK_ISR;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     gspi_int:1;
unsigned int     i2c2_int:1;
unsigned int     reserved_1:2;
unsigned int     i2c3_int:1;
unsigned int     reserved_2:1;
unsigned int     lsadc_int:1;
unsigned int     gpioda_int:1;
unsigned int     gpioa_int:1;
unsigned int     reserved_3:3;
unsigned int     i2c4_int:1;
unsigned int     i2c5_int:1;
unsigned int     reserved_4:1;
unsigned int     rtc_date_int:1;
unsigned int     rtc_hour_int:1;
unsigned int     rtc_min_int:1;
unsigned int     rtc_hsec_int:1;
unsigned int     reserved_5:1;
unsigned int     tc1_int:1;
unsigned int     tc0_int:1;
unsigned int     ur1_to_int:1;
unsigned int     i2c1_int:1;
unsigned int     ur1_int:1;
unsigned int     wdog_nmi_int:1;
unsigned int     reserved_6:1;
unsigned int     write_data:1;
}MIS_ISR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     wdog_nmi_int:1;
unsigned int     reserved_1:1;
unsigned int     tc2_int:1;
unsigned int     write_data:1;
}MIS_UMSK_ISR_SWC;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     wdog_nmi_int:1;
unsigned int     i2c_2_int:1;
unsigned int     tc2_int:1;
unsigned int     write_data:1;
}MIS_ISR_SWC;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     i2c_2_swc_en:1;
unsigned int     i2c_2_en:1;
}MIS_SETTING_SWC;

typedef struct 
{
unsigned int     gp_int:31;
unsigned int     reserved_0:1;
}MIS_FAST_INT_EN_0;

typedef struct 
{
unsigned int     gspi_int:1;
unsigned int     i2c3_int:1;
unsigned int     gp_int:29;
unsigned int     i2c2_int:1;
}MIS_FAST_INT_EN_1;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     i2c2_int:1;
unsigned int     gspi_int:1;
unsigned int     i2c3_int:1;
unsigned int     gpioda_int:1;
unsigned int     gpioa_int:1;
unsigned int     write_data:1;
}MIS_FAST_ISR;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     write_enable3:1;
unsigned int     sel1:4;
unsigned int     write_enable2:1;
unsigned int     sel0:4;
unsigned int     write_enable1:1;
unsigned int     enable:1;
}MIS_DBG;

typedef struct 
{
unsigned int     write_enable4:1;
unsigned int     rvd4:7;
unsigned int     write_enable3:1;
unsigned int     rvd3:7;
unsigned int     write_enable2:1;
unsigned int     rvd2:7;
unsigned int     write_enable1:1;
unsigned int     rvd1:7;
}MIS_DUMMY;

typedef struct 
{
unsigned int     int30:1;
unsigned int     int29:1;
unsigned int     int28:1;
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
unsigned int     write_data:1;
}MIS_UMSK_ISR_GP0A;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     int59:1;
unsigned int     int58:1;
unsigned int     int57:1;
unsigned int     int56:1;
unsigned int     int55:1;
unsigned int     int54:1;
unsigned int     int53:1;
unsigned int     int52:1;
unsigned int     int51:1;
unsigned int     int50:1;
unsigned int     int49:1;
unsigned int     int48:1;
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
unsigned int     write_data:1;
}MIS_UMSK_ISR_GP1A;

typedef struct 
{
unsigned int     int30:1;
unsigned int     int29:1;
unsigned int     int28:1;
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
unsigned int     write_data:1;
}MIS_UMSK_ISR_GP0DA;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     int59:1;
unsigned int     int58:1;
unsigned int     int57:1;
unsigned int     int56:1;
unsigned int     int55:1;
unsigned int     int54:1;
unsigned int     int53:1;
unsigned int     int52:1;
unsigned int     int51:1;
unsigned int     int50:1;
unsigned int     int49:1;
unsigned int     int48:1;
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
unsigned int     write_data:1;
}MIS_UMSK_ISR_GP1DA;

typedef struct 
{
unsigned int     write_enable2:1;
unsigned int     rvd2:15;
unsigned int     write_enable1:1;
unsigned int     rvd1:15;
}MIS_DUMMY1;

typedef struct 
{
unsigned int     rvd3:3;
unsigned int     reserved_0:1;
unsigned int     to_len:8;
unsigned int     to_int_en:1;
unsigned int     toauareq:1;
unsigned int     flow_pol:1;
unsigned int     mdifen:1;
unsigned int     reserved_1:2;
unsigned int     txempthr:6;
unsigned int     reserved_2:2;
unsigned int     rxfulthr:6;
}MIS_UR_CTRL;

typedef struct 
{
unsigned int     int_30:1;
unsigned int     int_29:1;
unsigned int     int_28:1;
unsigned int     int_27:1;
unsigned int     int_26:1;
unsigned int     int_25:1;
unsigned int     int_24:1;
unsigned int     int_23:1;
unsigned int     int_22:1;
unsigned int     int_21:1;
unsigned int     int_20:1;
unsigned int     int_19:1;
unsigned int     int_18:1;
unsigned int     int_17:1;
unsigned int     int_16:1;
unsigned int     int_15:1;
unsigned int     int_14:1;
unsigned int     int_13:1;
unsigned int     int_12:1;
unsigned int     int_11:1;
unsigned int     int_10:1;
unsigned int     int_9:1;
unsigned int     int_8:1;
unsigned int     int_7:1;
unsigned int     int_6:1;
unsigned int     int_5:1;
unsigned int     int_4:1;
unsigned int     int_3:1;
unsigned int     int_2:1;
unsigned int     int_1:1;
unsigned int     int_0:1;
unsigned int     write_data:1;
}MIS_FAST_ISR_GPIO0_A;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     int_59:1;
unsigned int     int_58:1;
unsigned int     int_57:1;
unsigned int     int_56:1;
unsigned int     int_55:1;
unsigned int     int_54:1;
unsigned int     int_53:1;
unsigned int     int_52:1;
unsigned int     int_51:1;
unsigned int     int_50:1;
unsigned int     int_49:1;
unsigned int     int_48:1;
unsigned int     int_47:1;
unsigned int     int_46:1;
unsigned int     int_45:1;
unsigned int     int_44:1;
unsigned int     int_43:1;
unsigned int     int_42:1;
unsigned int     int_41:1;
unsigned int     int_40:1;
unsigned int     int_39:1;
unsigned int     int_38:1;
unsigned int     int_37:1;
unsigned int     int_36:1;
unsigned int     int_35:1;
unsigned int     int_34:1;
unsigned int     int_33:1;
unsigned int     int_32:1;
unsigned int     int_31:1;
unsigned int     write_data:1;
}MIS_FAST_ISR_GPIO1_A;

typedef struct 
{
unsigned int     int_30:1;
unsigned int     int_29:1;
unsigned int     int_28:1;
unsigned int     int_27:1;
unsigned int     int_26:1;
unsigned int     int_25:1;
unsigned int     int_24:1;
unsigned int     int_23:1;
unsigned int     int_22:1;
unsigned int     int_21:1;
unsigned int     int_20:1;
unsigned int     int_19:1;
unsigned int     int_18:1;
unsigned int     int_17:1;
unsigned int     int_16:1;
unsigned int     int_15:1;
unsigned int     int_14:1;
unsigned int     int_13:1;
unsigned int     int_12:1;
unsigned int     int_11:1;
unsigned int     int_10:1;
unsigned int     int_9:1;
unsigned int     int_8:1;
unsigned int     int_7:1;
unsigned int     int_6:1;
unsigned int     int_5:1;
unsigned int     int_4:1;
unsigned int     int_3:1;
unsigned int     int_2:1;
unsigned int     int_1:1;
unsigned int     int_0:1;
unsigned int     write_data:1;
}MIS_FAST_ISR_GPIO0_DA;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     int_59:1;
unsigned int     int_58:1;
unsigned int     int_57:1;
unsigned int     int_56:1;
unsigned int     int_55:1;
unsigned int     int_54:1;
unsigned int     int_53:1;
unsigned int     int_52:1;
unsigned int     int_51:1;
unsigned int     int_50:1;
unsigned int     int_49:1;
unsigned int     int_48:1;
unsigned int     int_47:1;
unsigned int     int_46:1;
unsigned int     int_45:1;
unsigned int     int_44:1;
unsigned int     int_43:1;
unsigned int     int_42:1;
unsigned int     int_41:1;
unsigned int     int_40:1;
unsigned int     int_39:1;
unsigned int     int_38:1;
unsigned int     int_37:1;
unsigned int     int_36:1;
unsigned int     int_35:1;
unsigned int     int_34:1;
unsigned int     int_33:1;
unsigned int     int_32:1;
unsigned int     int_31:1;
unsigned int     write_data:1;
}MIS_FAST_ISR_GPIO1_DA;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     i2c3:1;
unsigned int     gspi:1;
unsigned int     i2c2:1;
unsigned int     reserved_1:4;
unsigned int     lsadc:1;
unsigned int     gpioda:1;
unsigned int     gpioa:1;
unsigned int     reserved_2:3;
unsigned int     i2c4:1;
unsigned int     i2c5:1;
unsigned int     reserved_3:1;
unsigned int     rtc_date:1;
unsigned int     rtc_hour:1;
unsigned int     rtc_min:1;
unsigned int     reserved_4:4;
unsigned int     ur1_to:1;
unsigned int     i2c1:1;
unsigned int     ur1:1;
unsigned int     reserved_5:3;
}MIS_SCPU_INT_EN;

typedef struct 
{
unsigned int     dmy1:20;
unsigned int     reserved_0:3;
unsigned int     en:1;
unsigned int     reserved_1:3;
unsigned int     sel:5;
}MIS_I2C1_SDA_DEL;

typedef struct 
{
unsigned int     dmy1:20;
unsigned int     reserved_0:3;
unsigned int     en:1;
unsigned int     reserved_1:3;
unsigned int     sel:5;
}MIS_I2C2_SDA_DEL;

typedef struct 
{
unsigned int     dmy1:20;
unsigned int     reserved_0:3;
unsigned int     en:1;
unsigned int     reserved_1:3;
unsigned int     sel:5;
}MIS_I2C3_SDA_DEL;

typedef struct 
{
unsigned int     dmy1:20;
unsigned int     reserved_0:3;
unsigned int     en:1;
unsigned int     reserved_1:3;
unsigned int     sel:5;
}MIS_I2C4_SDA_DEL;

typedef struct 
{
unsigned int     dmy1:20;
unsigned int     reserved_0:3;
unsigned int     en:1;
unsigned int     reserved_1:3;
unsigned int     sel:5;
}MIS_I2C5_SDA_DEL;

typedef struct 
{
unsigned int     gpdir:32;
}MIS_GP0DIR;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     gpdir:28;
}MIS_GP1DIR;

typedef struct 
{
unsigned int     gpdato:32;
}MIS_GP0DATO;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     gpdato:28;
}MIS_GP1DATO;

typedef struct 
{
unsigned int     gpdati:32;
}MIS_GP0DATI;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     gpdati:28;
}MIS_GP1DATI;

typedef struct 
{
unsigned int     gp:32;
}MIS_GP0IE;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     gp:28;
}MIS_GP1IE;

typedef struct 
{
unsigned int     gpha:32;
}MIS_GP0DP;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     gpha:28;
}MIS_GP1DP;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     write_enable4:1;
unsigned int     clk4:3;
unsigned int     write_enable3:1;
unsigned int     clk3:3;
unsigned int     write_enable2:1;
unsigned int     clk2:3;
unsigned int     write_enable1:1;
unsigned int     clk1:3;
}MIS_GPDEB;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dll:8;
}MIS_U1RBR_THR_DLL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dlh:8;
}MIS_U1IER_DLH;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     fifo16:2;
unsigned int     reserved_1:2;
unsigned int     iid:4;
}MIS_U1IIR_FCR;

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
}MIS_U1LCR;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     afce:1;
unsigned int     loop:1;
unsigned int     reserved_1:2;
unsigned int     rts:1;
unsigned int     dtr:1;
}MIS_U1MCR;

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
}MIS_U1LSR;

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
}MIS_U1MSR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     scr:8;
}MIS_U1SCR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rbd:8;
}MIS_U1SRBR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     far:1;
}MIS_U1FAR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     far:8;
}MIS_U1TFR;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     rffe:1;
unsigned int     rfpf:1;
unsigned int     rfwd:8;
}MIS_U1RFW;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     rff:1;
unsigned int     rfne:1;
unsigned int     tfe:1;
unsigned int     tfnf:1;
unsigned int     busy:1;
}MIS_U1USR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tfl:8;
}MIS_U1TFL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rfl:8;
}MIS_U1RFL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     xfr:1;
unsigned int     rfr:1;
unsigned int     ur:1;
}MIS_U1SRR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sbcr:1;
}MIS_U1SBCR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sdmam:1;
}MIS_U1SDMAM;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sfe:1;
}MIS_U1SFE;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     srt:2;
}MIS_U1SRT;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     stet:2;
}MIS_U1STET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     htx:1;
}MIS_U1HTX;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     dmasa:1;
}MIS_U1DMASA;

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
}MIS_U1CPR;

typedef struct 
{
unsigned int     ucv:32;
}MIS_U1UCV;

typedef struct 
{
unsigned int     ctr:32;
}MIS_U1CTR;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     ic_slave_disable:1;
unsigned int     ic_restart_en:1;
unsigned int     ic_10bitaddr_master:1;
unsigned int     ic_10bitaddr_slave:1;
unsigned int     speed:2;
unsigned int     master_mode:1;
}MIS_IC1_CON;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     ic_10bitaddr_master:1;
unsigned int     special:1;
unsigned int     gc_or_start:1;
unsigned int     ic_tar:10;
}MIS_IC1_TAR;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     ic_sar:10;
}MIS_IC1_SAR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     ic_hs_mar:3;
}MIS_IC1_HS_MADDR;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     restart:1;
unsigned int     stop:1;
unsigned int     cmd:1;
unsigned int     dat:8;
}MIS_IC1_DATA_CMD;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_ss_scl_hcnt:16;
}MIS_IC1_SS_SCL_HCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_ss_scl_lcnt:16;
}MIS_IC1_SS_SCL_LCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_fs_scl_hcnt:16;
}MIS_IC1_FS_SCL_HCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_fs_scl_lcnt:16;
}MIS_IC1_FS_SCL_LCNT;

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
}MIS_IC1_INTR_STAT;

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
}MIS_IC1_INTR_MASK;

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
}MIS_IC1_RAW_INTR_STAT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rx_tl:8;
}MIS_IC1_RX_TL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tx_tl:8;
}MIS_IC1_TX_TL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_intr:1;
}MIS_IC1_CLR_INTR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_under:1;
}MIS_IC1_CLR_RX_UNDER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_over:1;
}MIS_IC1_CLR_RX_OVER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_tx_over:1;
}MIS_IC1_CLR_TX_OVER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rd_req:1;
}MIS_IC1_CLR_RD_REQ;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_tx_abrt:1;
}MIS_IC1_CLR_TX_ABRT;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_done:1;
}MIS_IC1_CLR_RX_DONE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_activity:1;
}MIS_IC1_CLR_ACTIVITY;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_stop_det:1;
}MIS_IC1_CLR_STOP_DET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_start_det:1;
}MIS_IC1_CLR_START_DET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_gen_call:1;
}MIS_IC1_CLR_GEN_CALL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     enable:1;
}MIS_IC1_ENABLE;

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
}MIS_IC1_STATUS;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     txflr:4;
}MIS_IC1_TXFLR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     rxflr:4;
}MIS_IC1_RXFLR;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     sda_hold:16;
}MIS_IC1_SDA_HOLD;

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
}MIS_IC1_TX_ABRT_SOURCE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     nack:1;
}MIS_IC1_SLV_DATA_NACK_ONLY;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     tdmae:1;
unsigned int     rdmae:1;
}MIS_IC1_DMA_CR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     dmatdl:3;
}MIS_IC1_DMA_TDLR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     dmardl:4;
}MIS_IC1_DMA_RDLR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sda_setup:8;
}MIS_IC1_SDA_SETUP;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     ack_gen_call:1;
}MIS_IC1_ACK_GENERAL_CALL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     slv_rx_data_lost:1;
unsigned int     slv_disabled_whi:1;
unsigned int     ic_en:1;
}MIS_IC1_ENABLE_STATUS;

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
}MIS_IC1_COMP_PARAM_1;

typedef struct 
{
unsigned int     ic_comp_version:32;
}MIS_IC1_COMP_VERSION;

typedef struct 
{
unsigned int     ic_comp_type:32;
}MIS_IC1_COMP_TYPE;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     ic_slave_disable:1;
unsigned int     ic_restart_en:1;
unsigned int     ic_10bitaddr_master:1;
unsigned int     ic_10bitaddr_slave:1;
unsigned int     speed:2;
unsigned int     master_mode:1;
}MIS_IC2_CON;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     ic_10bitaddr_master:1;
unsigned int     special:1;
unsigned int     gc_or_start:1;
unsigned int     ic_tar:10;
}MIS_IC2_TAR;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     ic_sar:10;
}MIS_IC2_SAR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     ic_hs_mar:3;
}MIS_IC2_HS_MADDR;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     restart:1;
unsigned int     stop:1;
unsigned int     cmd:1;
unsigned int     dat:8;
}MIS_IC2_DATA_CMD;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_ss_scl_hcnt:16;
}MIS_IC2_SS_SCL_HCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_ss_scl_lcnt:16;
}MIS_IC2_SS_SCL_LCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_fs_scl_hcnt:16;
}MIS_IC2_FS_SCL_HCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_fs_scl_lcnt:16;
}MIS_IC2_FS_SCL_LCNT;

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
}MIS_IC2_INTR_STAT;

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
}MIS_IC2_INTR_MASK;

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
}MIS_IC2_RAW_INTR_STAT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rx_tl:8;
}MIS_IC2_RX_TL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tx_tl:8;
}MIS_IC2_TX_TL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_intr:1;
}MIS_IC2_CLR_INTR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_under:1;
}MIS_IC2_CLR_RX_UNDER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_over:1;
}MIS_IC2_CLR_RX_OVER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_tx_over:1;
}MIS_IC2_CLR_TX_OVER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rd_req:1;
}MIS_IC2_CLR_RD_REQ;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_tx_abrt:1;
}MIS_IC2_CLR_TX_ABRT;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_done:1;
}MIS_IC2_CLR_RX_DONE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_activity:1;
}MIS_IC2_CLR_ACTIVITY;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_stop_det:1;
}MIS_IC2_CLR_STOP_DET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_start_det:1;
}MIS_IC2_CLR_START_DET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_gen_call:1;
}MIS_IC2_CLR_GEN_CALL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     enable:1;
}MIS_IC2_ENABLE;

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
}MIS_IC2_STATUS;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     txflr:4;
}MIS_IC2_TXFLR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     rxflr:4;
}MIS_IC2_RXFLR;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     sda_hold:16;
}MIS_IC2_SDA_HOLD;

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
}MIS_IC2_TX_ABRT_SOURCE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     nack:1;
}MIS_IC2_SLV_DATA_NACK_ONLY;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     tdmae:1;
unsigned int     rdmae:1;
}MIS_IC2_DMA_CR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     dmatdl:3;
}MIS_IC2_DMA_TDLR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     dmardl:4;
}MIS_IC2_DMA_RDLR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sda_setup:8;
}MIS_IC2_SDA_SETUP;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     ack_gen_call:1;
}MIS_IC2_ACK_GENERAL_CALL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     slv_rx_data_lost:1;
unsigned int     slv_disabled_whi:1;
unsigned int     ic_en:1;
}MIS_IC2_ENABLE_STATUS;

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
}MIS_IC2_COMP_PARAM_1;

typedef struct 
{
unsigned int     ic_comp_version:32;
}MIS_IC2_COMP_VERSION;

typedef struct 
{
unsigned int     ic_comp_type:32;
}MIS_IC2_COMP_TYPE;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     ic_slave_disable:1;
unsigned int     ic_restart_en:1;
unsigned int     ic_10bitaddr_master:1;
unsigned int     ic_10bitaddr_slave:1;
unsigned int     speed:2;
unsigned int     master_mode:1;
}MIS_IC3_CON;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     ic_10bitaddr_master:1;
unsigned int     special:1;
unsigned int     gc_or_start:1;
unsigned int     ic_tar:10;
}MIS_IC3_TAR;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     ic_sar:10;
}MIS_IC3_SAR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     ic_hs_mar:3;
}MIS_IC3_HS_MADDR;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     restart:1;
unsigned int     stop:1;
unsigned int     cmd:1;
unsigned int     dat:8;
}MIS_IC3_DATA_CMD;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_ss_scl_hcnt:16;
}MIS_IC3_SS_SCL_HCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_ss_scl_lcnt:16;
}MIS_IC3_SS_SCL_LCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_fs_scl_hcnt:16;
}MIS_IC3_FS_SCL_HCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_fs_scl_lcnt:16;
}MIS_IC3_FS_SCL_LCNT;

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
}MIS_IC3_INTR_STAT;

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
}MIS_IC3_INTR_MASK;

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
}MIS_IC3_RAW_INTR_STAT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rx_tl:8;
}MIS_IC3_RX_TL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tx_tl:8;
}MIS_IC3_TX_TL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_intr:1;
}MIS_IC3_CLR_INTR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_under:1;
}MIS_IC3_CLR_RX_UNDER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_over:1;
}MIS_IC3_CLR_RX_OVER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_tx_over:1;
}MIS_IC3_CLR_TX_OVER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rd_req:1;
}MIS_IC3_CLR_RD_REQ;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_tx_abrt:1;
}MIS_IC3_CLR_TX_ABRT;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_done:1;
}MIS_IC3_CLR_RX_DONE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_activity:1;
}MIS_IC3_CLR_ACTIVITY;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_stop_det:1;
}MIS_IC3_CLR_STOP_DET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_start_det:1;
}MIS_IC3_CLR_START_DET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_gen_call:1;
}MIS_IC3_CLR_GEN_CALL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     enable:1;
}MIS_IC3_ENABLE;

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
}MIS_IC3_STATUS;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     txflr:4;
}MIS_IC3_TXFLR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     rxflr:4;
}MIS_IC3_RXFLR;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     sda_hold:16;
}MIS_IC3_SDA_HOLD;

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
}MIS_IC3_TX_ABRT_SOURCE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     nack:1;
}MIS_IC3_SLV_DATA_NACK_ONLY;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     tdmae:1;
unsigned int     rdmae:1;
}MIS_IC3_DMA_CR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     dmatdl:3;
}MIS_IC3_DMA_TDLR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     dmardl:4;
}MIS_IC3_DMA_RDLR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sda_setup:8;
}MIS_IC3_SDA_SETUP;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     ack_gen_call:1;
}MIS_IC3_ACK_GENERAL_CALL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     slv_rx_data_lost:1;
unsigned int     slv_disabled_whi:1;
unsigned int     ic_en:1;
}MIS_IC3_ENABLE_STATUS;

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
}MIS_IC3_COMP_PARAM_1;

typedef struct 
{
unsigned int     ic_comp_version:32;
}MIS_IC3_COMP_VERSION;

typedef struct 
{
unsigned int     ic_comp_type:32;
}MIS_IC3_COMP_TYPE;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     ic_slave_disable:1;
unsigned int     ic_restart_en:1;
unsigned int     ic_10bitaddr_master:1;
unsigned int     ic_10bitaddr_slave:1;
unsigned int     speed:2;
unsigned int     master_mode:1;
}MIS_IC4_CON;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     ic_10bitaddr_master:1;
unsigned int     special:1;
unsigned int     gc_or_start:1;
unsigned int     ic_tar:10;
}MIS_IC4_TAR;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     ic_sar:10;
}MIS_IC4_SAR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     ic_hs_mar:3;
}MIS_IC4_HS_MADDR;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     restart:1;
unsigned int     stop:1;
unsigned int     cmd:1;
unsigned int     dat:8;
}MIS_IC4_DATA_CMD;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_ss_scl_hcnt:16;
}MIS_IC4_SS_SCL_HCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_ss_scl_lcnt:16;
}MIS_IC4_SS_SCL_LCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_fs_scl_hcnt:16;
}MIS_IC4_FS_SCL_HCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_fs_scl_lcnt:16;
}MIS_IC4_FS_SCL_LCNT;

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
}MIS_IC4_INTR_STAT;

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
}MIS_IC4_INTR_MASK;

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
}MIS_IC4_RAW_INTR_STAT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rx_tl:8;
}MIS_IC4_RX_TL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tx_tl:8;
}MIS_IC4_TX_TL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_intr:1;
}MIS_IC4_CLR_INTR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_under:1;
}MIS_IC4_CLR_RX_UNDER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_over:1;
}MIS_IC4_CLR_RX_OVER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_tx_over:1;
}MIS_IC4_CLR_TX_OVER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rd_req:1;
}MIS_IC4_CLR_RD_REQ;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_tx_abrt:1;
}MIS_IC4_CLR_TX_ABRT;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_done:1;
}MIS_IC4_CLR_RX_DONE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_activity:1;
}MIS_IC4_CLR_ACTIVITY;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_stop_det:1;
}MIS_IC4_CLR_STOP_DET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_start_det:1;
}MIS_IC4_CLR_START_DET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_gen_call:1;
}MIS_IC4_CLR_GEN_CALL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     enable:1;
}MIS_IC4_ENABLE;

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
}MIS_IC4_STATUS;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     txflr:4;
}MIS_IC4_TXFLR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     rxflr:4;
}MIS_IC4_RXFLR;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     sda_hold:16;
}MIS_IC4_SDA_HOLD;

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
}MIS_IC4_TX_ABRT_SOURCE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     nack:1;
}MIS_IC4_SLV_DATA_NACK_ONLY;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     tdmae:1;
unsigned int     rdmae:1;
}MIS_IC4_DMA_CR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     dmatdl:3;
}MIS_IC4_DMA_TDLR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     dmardl:4;
}MIS_IC4_DMA_RDLR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sda_setup:8;
}MIS_IC4_SDA_SETUP;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     ack_gen_call:1;
}MIS_IC4_ACK_GENERAL_CALL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     slv_rx_data_lost:1;
unsigned int     slv_disabled_whi:1;
unsigned int     ic_en:1;
}MIS_IC4_ENABLE_STATUS;

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
}MIS_IC4_COMP_PARAM_1;

typedef struct 
{
unsigned int     ic_comp_version:32;
}MIS_IC4_COMP_VERSION;

typedef struct 
{
unsigned int     ic_comp_type:32;
}MIS_IC4_COMP_TYPE;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     ic_slave_disable:1;
unsigned int     ic_restart_en:1;
unsigned int     ic_10bitaddr_master:1;
unsigned int     ic_10bitaddr_slave:1;
unsigned int     speed:2;
unsigned int     master_mode:1;
}MIS_IC5_CON;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     ic_10bitaddr_master:1;
unsigned int     special:1;
unsigned int     gc_or_start:1;
unsigned int     ic_tar:10;
}MIS_IC5_TAR;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     ic_sar:10;
}MIS_IC5_SAR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     ic_hs_mar:3;
}MIS_IC5_HS_MADDR;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     restart:1;
unsigned int     stop:1;
unsigned int     cmd:1;
unsigned int     dat:8;
}MIS_IC5_DATA_CMD;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_ss_scl_hcnt:16;
}MIS_IC5_SS_SCL_HCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_ss_scl_lcnt:16;
}MIS_IC5_SS_SCL_LCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_fs_scl_hcnt:16;
}MIS_IC5_FS_SCL_HCNT;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     ic_fs_scl_lcnt:16;
}MIS_IC5_FS_SCL_LCNT;

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
}MIS_IC5_INTR_STAT;

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
}MIS_IC5_INTR_MASK;

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
}MIS_IC5_RAW_INTR_STAT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rx_tl:8;
}MIS_IC5_RX_TL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tx_tl:8;
}MIS_IC5_TX_TL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_intr:1;
}MIS_IC5_CLR_INTR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_under:1;
}MIS_IC5_CLR_RX_UNDER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_over:1;
}MIS_IC5_CLR_RX_OVER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_tx_over:1;
}MIS_IC5_CLR_TX_OVER;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rd_req:1;
}MIS_IC5_CLR_RD_REQ;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_tx_abrt:1;
}MIS_IC5_CLR_TX_ABRT;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_rx_done:1;
}MIS_IC5_CLR_RX_DONE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_activity:1;
}MIS_IC5_CLR_ACTIVITY;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_stop_det:1;
}MIS_IC5_CLR_STOP_DET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_start_det:1;
}MIS_IC5_CLR_START_DET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     clr_gen_call:1;
}MIS_IC5_CLR_GEN_CALL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     enable:1;
}MIS_IC5_ENABLE;

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
}MIS_IC5_STATUS;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     txflr:4;
}MIS_IC5_TXFLR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     rxflr:4;
}MIS_IC5_RXFLR;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     sda_hold:16;
}MIS_IC5_SDA_HOLD;

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
}MIS_IC5_TX_ABRT_SOURCE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     nack:1;
}MIS_IC5_SLV_DATA_NACK_ONLY;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     tdmae:1;
unsigned int     rdmae:1;
}MIS_IC5_DMA_CR;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     dmatdl:3;
}MIS_IC5_DMA_TDLR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     dmardl:4;
}MIS_IC5_DMA_RDLR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     sda_setup:8;
}MIS_IC5_SDA_SETUP;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     ack_gen_call:1;
}MIS_IC5_ACK_GENERAL_CALL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     slv_rx_data_lost:1;
unsigned int     slv_disabled_whi:1;
unsigned int     ic_en:1;
}MIS_IC5_ENABLE_STATUS;

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
}MIS_IC5_COMP_PARAM_1;

typedef struct 
{
unsigned int     ic_comp_version:32;
}MIS_IC5_COMP_VERSION;

typedef struct 
{
unsigned int     ic_comp_type:32;
}MIS_IC5_COMP_TYPE;

typedef struct 
{
unsigned int     tc0tvr:32;
}MIS_TC0TVR;

typedef struct 
{
unsigned int     tc1tvr:32;
}MIS_TC1TVR;

typedef struct 
{
unsigned int     tc2tvr:32;
}MIS_TC2TVR;

typedef struct 
{
unsigned int     tc0cvr:32;
}MIS_TC0CVR;

typedef struct 
{
unsigned int     tc1cvr:32;
}MIS_TC1CVR;

typedef struct 
{
unsigned int     tc2vr:32;
}MIS_TC2CVR;

typedef struct 
{
unsigned int     tc0en:1;
unsigned int     tc0mode:1;
unsigned int     tc0pause:1;
unsigned int     rvda:5;
unsigned int     reserved_0:24;
}MIS_TC0CR;

typedef struct 
{
unsigned int     tc1en:1;
unsigned int     tc1mode:1;
unsigned int     tc1pause:1;
unsigned int     rvda:5;
unsigned int     reserved_0:24;
}MIS_TC1CR;

typedef struct 
{
unsigned int     tc2en:1;
unsigned int     tc2mode:1;
unsigned int     tc2pause:1;
unsigned int     rvda:5;
unsigned int     reserved_0:24;
}MIS_TC2CR;

typedef struct 
{
unsigned int     tc0ie:1;
unsigned int     reserved_0:31;
}MIS_TC0ICR;

typedef struct 
{
unsigned int     tc1ie:1;
unsigned int     reserved_0:31;
}MIS_TC1ICR;

typedef struct 
{
unsigned int     tc2ie:1;
unsigned int     reserved_0:31;
}MIS_TC2ICR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     en:1;
}MIS_CLK90K_CTRL;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     cnt:9;
}MIS_SCPU_CLK27M_90K;

typedef struct 
{
unsigned int     val:32;
}MIS_SCPU_CLK90K_LO;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     val:16;
}MIS_SCPU_CLK90K_HI;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     cnt:9;
}MIS_ACPU_CLK27M_90K;

typedef struct 
{
unsigned int     val:32;
}MIS_ACPU_CLK90K_LO;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     val:16;
}MIS_ACPU_CLK90K_HI;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     en:1;
}MIS_PCR_CLK90K_CTRL;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     cnt:9;
}MIS_PCR_SCPU_CLK27M_90K;

typedef struct 
{
unsigned int     val:32;
}MIS_PCR_SCPU_CLK90K_LO;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     val:16;
}MIS_PCR_SCPU_CLK90K_HI;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     cnt:9;
}MIS_PCR_ACPU_CLK27M_90K;

typedef struct 
{
unsigned int     val:32;
}MIS_PCR_ACPU_CLK90K_LO;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     val:16;
}MIS_PCR_ACPU_CLK90K_HI;

typedef struct 
{
unsigned int     wd_int_en:1;
unsigned int     reserved_0:15;
unsigned int     nmic:4;
unsigned int     wdc:4;
unsigned int     wden:8;
}MIS_TCWCR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     wdclr:1;
}MIS_TCWTR;

typedef struct 
{
unsigned int     sel:32;
}MIS_TCWNMI;

typedef struct 
{
unsigned int     sel:32;
}MIS_TCWOV;

typedef struct 
{
unsigned int     wd_int_en:1;
unsigned int     reserved_0:15;
unsigned int     nmic:4;
unsigned int     wdc:4;
unsigned int     wden:8;
}MIS_TCWCR_SWC;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     wdclr:1;
}MIS_TCWTR_SWC;

typedef struct 
{
unsigned int     sel:32;
}MIS_TCWNMI_SWC;

typedef struct 
{
unsigned int     sel:32;
}MIS_TCWOV_SWC;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     rtcsec:7;
}MIS_RTCSEC;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     rtcmin:6;
}MIS_RTCMIN;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     rtchr:5;
}MIS_RTCHR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rtcdate1:8;
}MIS_RTCDATE1;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     rtcdate2:7;
}MIS_RTCDATE2;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     almmin:6;
}MIS_ALMMIN;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     almhr:5;
}MIS_ALMHR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     almdate1:8;
}MIS_ALMDATE1;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     almdate2:7;
}MIS_ALMDATE2;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     vref:2;
unsigned int     rtcstop:1;
}MIS_RTCSTOP;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rtcpwr:1;
unsigned int     co:2;
unsigned int     ci:2;
unsigned int     clksel:1;
unsigned int     bc:2;
}MIS_RTCACR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rtcen:8;
}MIS_RTCEN;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     rtcrst:1;
unsigned int     reserved_1:2;
unsigned int     dainte:1;
unsigned int     huinte:1;
unsigned int     muinte:1;
unsigned int     hsuinte:1;
}MIS_RTCCR;

typedef struct 
{
unsigned int     pad0_active:1;
unsigned int     reserved_0:7;
unsigned int     pad0_thred:8;
unsigned int     pad0_sw:4;
unsigned int     reserved_1:3;
unsigned int     pad0_ctrl:1;
unsigned int     reserved_2:2;
unsigned int     adc_val0:6;
}MIS_ST_PAD0;

typedef struct 
{
unsigned int     pad1_active:1;
unsigned int     reserved_0:7;
unsigned int     pad1_thred:8;
unsigned int     pad1_sw:4;
unsigned int     reserved_1:3;
unsigned int     pad1_ctrl:1;
unsigned int     reserved_2:2;
unsigned int     50:6;
}MIS_ST_PAD1;

typedef struct 
{
unsigned int     sel_wait:4;
unsigned int     sel_adc_ck:4;
unsigned int     debounce_cnt:4;
unsigned int     reserved_0:4;
unsigned int     dout_test_in:8;
unsigned int     reserved_1:6;
unsigned int     test_en:1;
unsigned int     enable:1;
}MIS_ST_LSADC_CTRL;

typedef struct 
{
unsigned int     irq_en:8;
unsigned int     pad_cnt:4;
unsigned int     adc_busy:1;
unsigned int     reserved_0:2;
unsigned int     pad_ctrl:5;
unsigned int     reserved_1:10;
unsigned int     pad1_status:1;
unsigned int     pad0_status:1;
}MIS_ST_LSADC_STATUS;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     jd_sbias:2;
unsigned int     reserved_1:2;
unsigned int     jd_adsbias:2;
unsigned int     jd_dummy:2;
unsigned int     reserved_2:1;
unsigned int     jd_svr:1;
unsigned int     reserved_3:3;
unsigned int     jd_adcksel:1;
unsigned int     reserved_4:3;
unsigned int     jd_power:1;
}MIS_ST_LSADC_ANALOG_CTRL;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     lsadc_2_ifd_data_sel:3;
unsigned int     reserved_1:1;
unsigned int     power_saving_enable:1;
unsigned int     power_saving_cycle_time:3;
unsigned int     power_saving_disable_time:3;
unsigned int     peri_top_debug:8;
}MIS_ST_LSADC_PERI_TOP_DEBUG;

typedef struct 
{
unsigned int     level_0_top_bound:8;
unsigned int     level_0_low_bound:8;
unsigned int     block0_en:1;
unsigned int     reserved_0:13;
unsigned int     int_en0:1;
unsigned int     int_pending_bit0:1;
}MIS_LSADC_PAD0_LEVEL_SET0;

typedef struct 
{
unsigned int     level_1_top_bound:8;
unsigned int     level_0_low_bound:8;
unsigned int     block1_en:1;
unsigned int     reserved_0:13;
unsigned int     int_en1:1;
unsigned int     int_pending_bit1:1;
}MIS_LSADC_PAD0_LEVEL_SET1;

typedef struct 
{
unsigned int     level_2_top_bound:8;
unsigned int     level_2_low_bound:8;
unsigned int     block2_en:1;
unsigned int     reserved_0:13;
unsigned int     int_en2:1;
unsigned int     int_pending_bit2:1;
}MIS_LSADC_PAD0_LEVEL_SET2;

typedef struct 
{
unsigned int     level_3_top_bound:8;
unsigned int     level_3_low_bound:8;
unsigned int     block3_en:1;
unsigned int     reserved_0:13;
unsigned int     int_en3:1;
unsigned int     int_pending_bit3:1;
}MIS_LSADC_PAD0_LEVEL_SET3;

typedef struct 
{
unsigned int     level_4_top_bound:8;
unsigned int     level_4_low_bound:8;
unsigned int     block4_en:1;
unsigned int     reserved_0:13;
unsigned int     int_en4:1;
unsigned int     int_pending_bit4:1;
}MIS_LSADC_PAD0_LEVEL_SET4;

typedef struct 
{
unsigned int     level_5_top_bound:8;
unsigned int     level_5_low_bound:8;
unsigned int     block5_en:1;
unsigned int     reserved_0:13;
unsigned int     int_en5:1;
unsigned int     int_pending_bit5:1;
}MIS_LSADC_PAD0_LEVEL_SET5;

typedef struct 
{
unsigned int     level_0_top_bound:8;
unsigned int     level_0_low_bound:8;
unsigned int     block0_en:1;
unsigned int     reserved_0:13;
unsigned int     int_en0:1;
unsigned int     int_pending_bit0:1;
}MIS_LSADC_PAD1_LEVEL_SET0;

typedef struct 
{
unsigned int     level_1_top_bound:8;
unsigned int     level_0_low_bound:8;
unsigned int     block1_en:1;
unsigned int     reserved_0:13;
unsigned int     int_en1:1;
unsigned int     int_pending_bit1:1;
}MIS_LSADC_PAD1_LEVEL_SET1;

typedef struct 
{
unsigned int     level_2_top_bound:8;
unsigned int     level_2_low_bound:8;
unsigned int     block2_en:1;
unsigned int     reserved_0:13;
unsigned int     int_en2:1;
unsigned int     int_pending_bit2:1;
}MIS_LSADC_PAD1_LEVEL_SET2;

typedef struct 
{
unsigned int     level_3_top_bound:8;
unsigned int     level_3_low_bound:8;
unsigned int     block3_en:1;
unsigned int     reserved_0:13;
unsigned int     int_en3:1;
unsigned int     int_pending_bit3:1;
}MIS_LSADC_PAD1_LEVEL_SET3;

typedef struct 
{
unsigned int     level_4_top_bound:8;
unsigned int     level_4_low_bound:8;
unsigned int     block4_en:1;
unsigned int     reserved_0:13;
unsigned int     int_en4:1;
unsigned int     int_pending_bit4:1;
}MIS_LSADC_PAD1_LEVEL_SET4;

typedef struct 
{
unsigned int     level_5_top_bound:8;
unsigned int     level_5_low_bound:8;
unsigned int     block5_en:1;
unsigned int     reserved_0:13;
unsigned int     int_en5:1;
unsigned int     int_pending_bit5:1;
}MIS_LSADC_PAD1_LEVEL_SET5;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     reserved_1:2;
unsigned int     adc_value0latch:6;
unsigned int     reserved_2:7;
unsigned int     int_latchstatus:1;
}MIS_LSADC_INT_PAD0;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     reserved_1:2;
unsigned int     adc_value1latch:6;
unsigned int     reserved_2:7;
unsigned int     int_latchstatus:1;
}MIS_LSADC_INT_PAD1;

#endif

#define MIS_UMSK_ISR                                                                 0x1801B008
#define MIS_UMSK_ISR_reg_addr                                                        "0xB801B008"
#define MIS_UMSK_ISR_reg                                                             0xB801B008
#define set_MIS_UMSK_ISR_reg(data)   (*((volatile unsigned int*) MIS_UMSK_ISR_reg)=data)
#define get_MIS_UMSK_ISR_reg   (*((volatile unsigned int*) MIS_UMSK_ISR_reg))
#define MIS_UMSK_ISR_inst_adr                                                        "0x0002"
#define MIS_UMSK_ISR_inst                                                            0x0002
#define MIS_UMSK_ISR_gspi_int_shift                                                  (27)
#define MIS_UMSK_ISR_gspi_int_mask                                                   (0x08000000)
#define MIS_UMSK_ISR_gspi_int(data)                                                  (0x08000000&((data)<<27))
#define MIS_UMSK_ISR_gspi_int_src(data)                                              ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_get_gspi_int(data)                                              ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_gpioda_int_shift                                                (20)
#define MIS_UMSK_ISR_gpioda_int_mask                                                 (0x00100000)
#define MIS_UMSK_ISR_gpioda_int(data)                                                (0x00100000&((data)<<20))
#define MIS_UMSK_ISR_gpioda_int_src(data)                                            ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_get_gpioda_int(data)                                            ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_gpioa_int_shift                                                 (19)
#define MIS_UMSK_ISR_gpioa_int_mask                                                  (0x00080000)
#define MIS_UMSK_ISR_gpioa_int(data)                                                 (0x00080000&((data)<<19))
#define MIS_UMSK_ISR_gpioa_int_src(data)                                             ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_get_gpioa_int(data)                                             ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_rtc_date_int_shift                                              (12)
#define MIS_UMSK_ISR_rtc_date_int_mask                                               (0x00001000)
#define MIS_UMSK_ISR_rtc_date_int(data)                                              (0x00001000&((data)<<12))
#define MIS_UMSK_ISR_rtc_date_int_src(data)                                          ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_get_rtc_date_int(data)                                          ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_rtc_hour_int_shift                                              (11)
#define MIS_UMSK_ISR_rtc_hour_int_mask                                               (0x00000800)
#define MIS_UMSK_ISR_rtc_hour_int(data)                                              (0x00000800&((data)<<11))
#define MIS_UMSK_ISR_rtc_hour_int_src(data)                                          ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_get_rtc_hour_int(data)                                          ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_rtc_min_int_shift                                               (10)
#define MIS_UMSK_ISR_rtc_min_int_mask                                                (0x00000400)
#define MIS_UMSK_ISR_rtc_min_int(data)                                               (0x00000400&((data)<<10))
#define MIS_UMSK_ISR_rtc_min_int_src(data)                                           ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_get_rtc_min_int(data)                                           ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_rtc_hsec_int_shift                                              (9)
#define MIS_UMSK_ISR_rtc_hsec_int_mask                                               (0x00000200)
#define MIS_UMSK_ISR_rtc_hsec_int(data)                                              (0x00000200&((data)<<9))
#define MIS_UMSK_ISR_rtc_hsec_int_src(data)                                          ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_get_rtc_hsec_int(data)                                          ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_tc1_int_shift                                                   (7)
#define MIS_UMSK_ISR_tc1_int_mask                                                    (0x00000080)
#define MIS_UMSK_ISR_tc1_int(data)                                                   (0x00000080&((data)<<7))
#define MIS_UMSK_ISR_tc1_int_src(data)                                               ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_get_tc1_int(data)                                               ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_tc0_int_shift                                                   (6)
#define MIS_UMSK_ISR_tc0_int_mask                                                    (0x00000040)
#define MIS_UMSK_ISR_tc0_int(data)                                                   (0x00000040&((data)<<6))
#define MIS_UMSK_ISR_tc0_int_src(data)                                               ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_get_tc0_int(data)                                               ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_ur1_to_int_shift                                                (5)
#define MIS_UMSK_ISR_ur1_to_int_mask                                                 (0x00000020)
#define MIS_UMSK_ISR_ur1_to_int(data)                                                (0x00000020&((data)<<5))
#define MIS_UMSK_ISR_ur1_to_int_src(data)                                            ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_get_ur1_to_int(data)                                            ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_wdog_nmi_int_shift                                              (2)
#define MIS_UMSK_ISR_wdog_nmi_int_mask                                               (0x00000004)
#define MIS_UMSK_ISR_wdog_nmi_int(data)                                              (0x00000004&((data)<<2))
#define MIS_UMSK_ISR_wdog_nmi_int_src(data)                                          ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_get_wdog_nmi_int(data)                                          ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_write_data_shift                                                (0)
#define MIS_UMSK_ISR_write_data_mask                                                 (0x00000001)
#define MIS_UMSK_ISR_write_data(data)                                                (0x00000001&((data)<<0))
#define MIS_UMSK_ISR_write_data_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_UMSK_ISR_get_write_data(data)                                            ((0x00000001&(data))>>0)


#define MIS_ISR                                                                      0x1801B00C
#define MIS_ISR_reg_addr                                                             "0xB801B00C"
#define MIS_ISR_reg                                                                  0xB801B00C
#define set_MIS_ISR_reg(data)   (*((volatile unsigned int*) MIS_ISR_reg)=data)
#define get_MIS_ISR_reg   (*((volatile unsigned int*) MIS_ISR_reg))
#define MIS_ISR_inst_adr                                                             "0x0003"
#define MIS_ISR_inst                                                                 0x0003
#define MIS_ISR_gspi_int_shift                                                       (27)
#define MIS_ISR_gspi_int_mask                                                        (0x08000000)
#define MIS_ISR_gspi_int(data)                                                       (0x08000000&((data)<<27))
#define MIS_ISR_gspi_int_src(data)                                                   ((0x08000000&(data))>>27)
#define MIS_ISR_get_gspi_int(data)                                                   ((0x08000000&(data))>>27)
#define MIS_ISR_i2c2_int_shift                                                       (26)
#define MIS_ISR_i2c2_int_mask                                                        (0x04000000)
#define MIS_ISR_i2c2_int(data)                                                       (0x04000000&((data)<<26))
#define MIS_ISR_i2c2_int_src(data)                                                   ((0x04000000&(data))>>26)
#define MIS_ISR_get_i2c2_int(data)                                                   ((0x04000000&(data))>>26)
#define MIS_ISR_i2c3_int_shift                                                       (23)
#define MIS_ISR_i2c3_int_mask                                                        (0x00800000)
#define MIS_ISR_i2c3_int(data)                                                       (0x00800000&((data)<<23))
#define MIS_ISR_i2c3_int_src(data)                                                   ((0x00800000&(data))>>23)
#define MIS_ISR_get_i2c3_int(data)                                                   ((0x00800000&(data))>>23)
#define MIS_ISR_lsadc_int_shift                                                      (21)
#define MIS_ISR_lsadc_int_mask                                                       (0x00200000)
#define MIS_ISR_lsadc_int(data)                                                      (0x00200000&((data)<<21))
#define MIS_ISR_lsadc_int_src(data)                                                  ((0x00200000&(data))>>21)
#define MIS_ISR_get_lsadc_int(data)                                                  ((0x00200000&(data))>>21)
#define MIS_ISR_gpioda_int_shift                                                     (20)
#define MIS_ISR_gpioda_int_mask                                                      (0x00100000)
#define MIS_ISR_gpioda_int(data)                                                     (0x00100000&((data)<<20))
#define MIS_ISR_gpioda_int_src(data)                                                 ((0x00100000&(data))>>20)
#define MIS_ISR_get_gpioda_int(data)                                                 ((0x00100000&(data))>>20)
#define MIS_ISR_gpioa_int_shift                                                      (19)
#define MIS_ISR_gpioa_int_mask                                                       (0x00080000)
#define MIS_ISR_gpioa_int(data)                                                      (0x00080000&((data)<<19))
#define MIS_ISR_gpioa_int_src(data)                                                  ((0x00080000&(data))>>19)
#define MIS_ISR_get_gpioa_int(data)                                                  ((0x00080000&(data))>>19)
#define MIS_ISR_i2c4_int_shift                                                       (15)
#define MIS_ISR_i2c4_int_mask                                                        (0x00008000)
#define MIS_ISR_i2c4_int(data)                                                       (0x00008000&((data)<<15))
#define MIS_ISR_i2c4_int_src(data)                                                   ((0x00008000&(data))>>15)
#define MIS_ISR_get_i2c4_int(data)                                                   ((0x00008000&(data))>>15)
#define MIS_ISR_i2c5_int_shift                                                       (14)
#define MIS_ISR_i2c5_int_mask                                                        (0x00004000)
#define MIS_ISR_i2c5_int(data)                                                       (0x00004000&((data)<<14))
#define MIS_ISR_i2c5_int_src(data)                                                   ((0x00004000&(data))>>14)
#define MIS_ISR_get_i2c5_int(data)                                                   ((0x00004000&(data))>>14)
#define MIS_ISR_rtc_date_int_shift                                                   (12)
#define MIS_ISR_rtc_date_int_mask                                                    (0x00001000)
#define MIS_ISR_rtc_date_int(data)                                                   (0x00001000&((data)<<12))
#define MIS_ISR_rtc_date_int_src(data)                                               ((0x00001000&(data))>>12)
#define MIS_ISR_get_rtc_date_int(data)                                               ((0x00001000&(data))>>12)
#define MIS_ISR_rtc_hour_int_shift                                                   (11)
#define MIS_ISR_rtc_hour_int_mask                                                    (0x00000800)
#define MIS_ISR_rtc_hour_int(data)                                                   (0x00000800&((data)<<11))
#define MIS_ISR_rtc_hour_int_src(data)                                               ((0x00000800&(data))>>11)
#define MIS_ISR_get_rtc_hour_int(data)                                               ((0x00000800&(data))>>11)
#define MIS_ISR_rtc_min_int_shift                                                    (10)
#define MIS_ISR_rtc_min_int_mask                                                     (0x00000400)
#define MIS_ISR_rtc_min_int(data)                                                    (0x00000400&((data)<<10))
#define MIS_ISR_rtc_min_int_src(data)                                                ((0x00000400&(data))>>10)
#define MIS_ISR_get_rtc_min_int(data)                                                ((0x00000400&(data))>>10)
#define MIS_ISR_rtc_hsec_int_shift                                                   (9)
#define MIS_ISR_rtc_hsec_int_mask                                                    (0x00000200)
#define MIS_ISR_rtc_hsec_int(data)                                                   (0x00000200&((data)<<9))
#define MIS_ISR_rtc_hsec_int_src(data)                                               ((0x00000200&(data))>>9)
#define MIS_ISR_get_rtc_hsec_int(data)                                               ((0x00000200&(data))>>9)
#define MIS_ISR_tc1_int_shift                                                        (7)
#define MIS_ISR_tc1_int_mask                                                         (0x00000080)
#define MIS_ISR_tc1_int(data)                                                        (0x00000080&((data)<<7))
#define MIS_ISR_tc1_int_src(data)                                                    ((0x00000080&(data))>>7)
#define MIS_ISR_get_tc1_int(data)                                                    ((0x00000080&(data))>>7)
#define MIS_ISR_tc0_int_shift                                                        (6)
#define MIS_ISR_tc0_int_mask                                                         (0x00000040)
#define MIS_ISR_tc0_int(data)                                                        (0x00000040&((data)<<6))
#define MIS_ISR_tc0_int_src(data)                                                    ((0x00000040&(data))>>6)
#define MIS_ISR_get_tc0_int(data)                                                    ((0x00000040&(data))>>6)
#define MIS_ISR_ur1_to_int_shift                                                     (5)
#define MIS_ISR_ur1_to_int_mask                                                      (0x00000020)
#define MIS_ISR_ur1_to_int(data)                                                     (0x00000020&((data)<<5))
#define MIS_ISR_ur1_to_int_src(data)                                                 ((0x00000020&(data))>>5)
#define MIS_ISR_get_ur1_to_int(data)                                                 ((0x00000020&(data))>>5)
#define MIS_ISR_i2c1_int_shift                                                       (4)
#define MIS_ISR_i2c1_int_mask                                                        (0x00000010)
#define MIS_ISR_i2c1_int(data)                                                       (0x00000010&((data)<<4))
#define MIS_ISR_i2c1_int_src(data)                                                   ((0x00000010&(data))>>4)
#define MIS_ISR_get_i2c1_int(data)                                                   ((0x00000010&(data))>>4)
#define MIS_ISR_ur1_int_shift                                                        (3)
#define MIS_ISR_ur1_int_mask                                                         (0x00000008)
#define MIS_ISR_ur1_int(data)                                                        (0x00000008&((data)<<3))
#define MIS_ISR_ur1_int_src(data)                                                    ((0x00000008&(data))>>3)
#define MIS_ISR_get_ur1_int(data)                                                    ((0x00000008&(data))>>3)
#define MIS_ISR_wdog_nmi_int_shift                                                   (2)
#define MIS_ISR_wdog_nmi_int_mask                                                    (0x00000004)
#define MIS_ISR_wdog_nmi_int(data)                                                   (0x00000004&((data)<<2))
#define MIS_ISR_wdog_nmi_int_src(data)                                               ((0x00000004&(data))>>2)
#define MIS_ISR_get_wdog_nmi_int(data)                                               ((0x00000004&(data))>>2)
#define MIS_ISR_write_data_shift                                                     (0)
#define MIS_ISR_write_data_mask                                                      (0x00000001)
#define MIS_ISR_write_data(data)                                                     (0x00000001&((data)<<0))
#define MIS_ISR_write_data_src(data)                                                 ((0x00000001&(data))>>0)
#define MIS_ISR_get_write_data(data)                                                 ((0x00000001&(data))>>0)


#define MIS_UMSK_ISR_SWC                                                             0x1801B010
#define MIS_UMSK_ISR_SWC_reg_addr                                                    "0xB801B010"
#define MIS_UMSK_ISR_SWC_reg                                                         0xB801B010
#define set_MIS_UMSK_ISR_SWC_reg(data)   (*((volatile unsigned int*) MIS_UMSK_ISR_SWC_reg)=data)
#define get_MIS_UMSK_ISR_SWC_reg   (*((volatile unsigned int*) MIS_UMSK_ISR_SWC_reg))
#define MIS_UMSK_ISR_SWC_inst_adr                                                    "0x0004"
#define MIS_UMSK_ISR_SWC_inst                                                        0x0004
#define MIS_UMSK_ISR_SWC_wdog_nmi_int_shift                                          (3)
#define MIS_UMSK_ISR_SWC_wdog_nmi_int_mask                                           (0x00000008)
#define MIS_UMSK_ISR_SWC_wdog_nmi_int(data)                                          (0x00000008&((data)<<3))
#define MIS_UMSK_ISR_SWC_wdog_nmi_int_src(data)                                      ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_SWC_get_wdog_nmi_int(data)                                      ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_SWC_tc2_int_shift                                               (1)
#define MIS_UMSK_ISR_SWC_tc2_int_mask                                                (0x00000002)
#define MIS_UMSK_ISR_SWC_tc2_int(data)                                               (0x00000002&((data)<<1))
#define MIS_UMSK_ISR_SWC_tc2_int_src(data)                                           ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_SWC_get_tc2_int(data)                                           ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_SWC_write_data_shift                                            (0)
#define MIS_UMSK_ISR_SWC_write_data_mask                                             (0x00000001)
#define MIS_UMSK_ISR_SWC_write_data(data)                                            (0x00000001&((data)<<0))
#define MIS_UMSK_ISR_SWC_write_data_src(data)                                        ((0x00000001&(data))>>0)
#define MIS_UMSK_ISR_SWC_get_write_data(data)                                        ((0x00000001&(data))>>0)


#define MIS_ISR_SWC                                                                  0x1801B014
#define MIS_ISR_SWC_reg_addr                                                         "0xB801B014"
#define MIS_ISR_SWC_reg                                                              0xB801B014
#define set_MIS_ISR_SWC_reg(data)   (*((volatile unsigned int*) MIS_ISR_SWC_reg)=data)
#define get_MIS_ISR_SWC_reg   (*((volatile unsigned int*) MIS_ISR_SWC_reg))
#define MIS_ISR_SWC_inst_adr                                                         "0x0005"
#define MIS_ISR_SWC_inst                                                             0x0005
#define MIS_ISR_SWC_wdog_nmi_int_shift                                               (3)
#define MIS_ISR_SWC_wdog_nmi_int_mask                                                (0x00000008)
#define MIS_ISR_SWC_wdog_nmi_int(data)                                               (0x00000008&((data)<<3))
#define MIS_ISR_SWC_wdog_nmi_int_src(data)                                           ((0x00000008&(data))>>3)
#define MIS_ISR_SWC_get_wdog_nmi_int(data)                                           ((0x00000008&(data))>>3)
#define MIS_ISR_SWC_i2c_2_int_shift                                                  (2)
#define MIS_ISR_SWC_i2c_2_int_mask                                                   (0x00000004)
#define MIS_ISR_SWC_i2c_2_int(data)                                                  (0x00000004&((data)<<2))
#define MIS_ISR_SWC_i2c_2_int_src(data)                                              ((0x00000004&(data))>>2)
#define MIS_ISR_SWC_get_i2c_2_int(data)                                              ((0x00000004&(data))>>2)
#define MIS_ISR_SWC_tc2_int_shift                                                    (1)
#define MIS_ISR_SWC_tc2_int_mask                                                     (0x00000002)
#define MIS_ISR_SWC_tc2_int(data)                                                    (0x00000002&((data)<<1))
#define MIS_ISR_SWC_tc2_int_src(data)                                                ((0x00000002&(data))>>1)
#define MIS_ISR_SWC_get_tc2_int(data)                                                ((0x00000002&(data))>>1)
#define MIS_ISR_SWC_write_data_shift                                                 (0)
#define MIS_ISR_SWC_write_data_mask                                                  (0x00000001)
#define MIS_ISR_SWC_write_data(data)                                                 (0x00000001&((data)<<0))
#define MIS_ISR_SWC_write_data_src(data)                                             ((0x00000001&(data))>>0)
#define MIS_ISR_SWC_get_write_data(data)                                             ((0x00000001&(data))>>0)


#define MIS_SETTING_SWC                                                              0x1801B018
#define MIS_SETTING_SWC_reg_addr                                                     "0xB801B018"
#define MIS_SETTING_SWC_reg                                                          0xB801B018
#define set_MIS_SETTING_SWC_reg(data)   (*((volatile unsigned int*) MIS_SETTING_SWC_reg)=data)
#define get_MIS_SETTING_SWC_reg   (*((volatile unsigned int*) MIS_SETTING_SWC_reg))
#define MIS_SETTING_SWC_inst_adr                                                     "0x0006"
#define MIS_SETTING_SWC_inst                                                         0x0006
#define MIS_SETTING_SWC_i2c_2_swc_en_shift                                           (1)
#define MIS_SETTING_SWC_i2c_2_swc_en_mask                                            (0x00000002)
#define MIS_SETTING_SWC_i2c_2_swc_en(data)                                           (0x00000002&((data)<<1))
#define MIS_SETTING_SWC_i2c_2_swc_en_src(data)                                       ((0x00000002&(data))>>1)
#define MIS_SETTING_SWC_get_i2c_2_swc_en(data)                                       ((0x00000002&(data))>>1)
#define MIS_SETTING_SWC_i2c_2_en_shift                                               (0)
#define MIS_SETTING_SWC_i2c_2_en_mask                                                (0x00000001)
#define MIS_SETTING_SWC_i2c_2_en(data)                                               (0x00000001&((data)<<0))
#define MIS_SETTING_SWC_i2c_2_en_src(data)                                           ((0x00000001&(data))>>0)
#define MIS_SETTING_SWC_get_i2c_2_en(data)                                           ((0x00000001&(data))>>0)


#define MIS_FAST_INT_EN_0                                                            0x1801B01C
#define MIS_FAST_INT_EN_0_reg_addr                                                   "0xB801B01C"
#define MIS_FAST_INT_EN_0_reg                                                        0xB801B01C
#define set_MIS_FAST_INT_EN_0_reg(data)   (*((volatile unsigned int*) MIS_FAST_INT_EN_0_reg)=data)
#define get_MIS_FAST_INT_EN_0_reg   (*((volatile unsigned int*) MIS_FAST_INT_EN_0_reg))
#define MIS_FAST_INT_EN_0_inst_adr                                                   "0x0007"
#define MIS_FAST_INT_EN_0_inst                                                       0x0007
#define MIS_FAST_INT_EN_0_gp_int_shift                                               (1)
#define MIS_FAST_INT_EN_0_gp_int_mask                                                (0xFFFFFFFE)
#define MIS_FAST_INT_EN_0_gp_int(data)                                               (0xFFFFFFFE&((data)<<1))
#define MIS_FAST_INT_EN_0_gp_int_src(data)                                           ((0xFFFFFFFE&(data))>>1)
#define MIS_FAST_INT_EN_0_get_gp_int(data)                                           ((0xFFFFFFFE&(data))>>1)


#define MIS_FAST_INT_EN_1                                                            0x1801B020
#define MIS_FAST_INT_EN_1_reg_addr                                                   "0xB801B020"
#define MIS_FAST_INT_EN_1_reg                                                        0xB801B020
#define set_MIS_FAST_INT_EN_1_reg(data)   (*((volatile unsigned int*) MIS_FAST_INT_EN_1_reg)=data)
#define get_MIS_FAST_INT_EN_1_reg   (*((volatile unsigned int*) MIS_FAST_INT_EN_1_reg))
#define MIS_FAST_INT_EN_1_inst_adr                                                   "0x0008"
#define MIS_FAST_INT_EN_1_inst                                                       0x0008
#define MIS_FAST_INT_EN_1_gspi_int_shift                                             (31)
#define MIS_FAST_INT_EN_1_gspi_int_mask                                              (0x80000000)
#define MIS_FAST_INT_EN_1_gspi_int(data)                                             (0x80000000&((data)<<31))
#define MIS_FAST_INT_EN_1_gspi_int_src(data)                                         ((0x80000000&(data))>>31)
#define MIS_FAST_INT_EN_1_get_gspi_int(data)                                         ((0x80000000&(data))>>31)
#define MIS_FAST_INT_EN_1_i2c3_int_shift                                             (30)
#define MIS_FAST_INT_EN_1_i2c3_int_mask                                              (0x40000000)
#define MIS_FAST_INT_EN_1_i2c3_int(data)                                             (0x40000000&((data)<<30))
#define MIS_FAST_INT_EN_1_i2c3_int_src(data)                                         ((0x40000000&(data))>>30)
#define MIS_FAST_INT_EN_1_get_i2c3_int(data)                                         ((0x40000000&(data))>>30)
#define MIS_FAST_INT_EN_1_gp_int_shift                                               (1)
#define MIS_FAST_INT_EN_1_gp_int_mask                                                (0x3FFFFFFE)
#define MIS_FAST_INT_EN_1_gp_int(data)                                               (0x3FFFFFFE&((data)<<1))
#define MIS_FAST_INT_EN_1_gp_int_src(data)                                           ((0x3FFFFFFE&(data))>>1)
#define MIS_FAST_INT_EN_1_get_gp_int(data)                                           ((0x3FFFFFFE&(data))>>1)
#define MIS_FAST_INT_EN_1_i2c2_int_shift                                             (0)
#define MIS_FAST_INT_EN_1_i2c2_int_mask                                              (0x00000001)
#define MIS_FAST_INT_EN_1_i2c2_int(data)                                             (0x00000001&((data)<<0))
#define MIS_FAST_INT_EN_1_i2c2_int_src(data)                                         ((0x00000001&(data))>>0)
#define MIS_FAST_INT_EN_1_get_i2c2_int(data)                                         ((0x00000001&(data))>>0)


#define MIS_FAST_ISR                                                                 0x1801B024
#define MIS_FAST_ISR_reg_addr                                                        "0xB801B024"
#define MIS_FAST_ISR_reg                                                             0xB801B024
#define set_MIS_FAST_ISR_reg(data)   (*((volatile unsigned int*) MIS_FAST_ISR_reg)=data)
#define get_MIS_FAST_ISR_reg   (*((volatile unsigned int*) MIS_FAST_ISR_reg))
#define MIS_FAST_ISR_inst_adr                                                        "0x0009"
#define MIS_FAST_ISR_inst                                                            0x0009
#define MIS_FAST_ISR_i2c2_int_shift                                                  (5)
#define MIS_FAST_ISR_i2c2_int_mask                                                   (0x00000020)
#define MIS_FAST_ISR_i2c2_int(data)                                                  (0x00000020&((data)<<5))
#define MIS_FAST_ISR_i2c2_int_src(data)                                              ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_get_i2c2_int(data)                                              ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_gspi_int_shift                                                  (4)
#define MIS_FAST_ISR_gspi_int_mask                                                   (0x00000010)
#define MIS_FAST_ISR_gspi_int(data)                                                  (0x00000010&((data)<<4))
#define MIS_FAST_ISR_gspi_int_src(data)                                              ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_get_gspi_int(data)                                              ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_i2c3_int_shift                                                  (3)
#define MIS_FAST_ISR_i2c3_int_mask                                                   (0x00000008)
#define MIS_FAST_ISR_i2c3_int(data)                                                  (0x00000008&((data)<<3))
#define MIS_FAST_ISR_i2c3_int_src(data)                                              ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_get_i2c3_int(data)                                              ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_gpioda_int_shift                                                (2)
#define MIS_FAST_ISR_gpioda_int_mask                                                 (0x00000004)
#define MIS_FAST_ISR_gpioda_int(data)                                                (0x00000004&((data)<<2))
#define MIS_FAST_ISR_gpioda_int_src(data)                                            ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_get_gpioda_int(data)                                            ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_gpioa_int_shift                                                 (1)
#define MIS_FAST_ISR_gpioa_int_mask                                                  (0x00000002)
#define MIS_FAST_ISR_gpioa_int(data)                                                 (0x00000002&((data)<<1))
#define MIS_FAST_ISR_gpioa_int_src(data)                                             ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_get_gpioa_int(data)                                             ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_write_data_shift                                                (0)
#define MIS_FAST_ISR_write_data_mask                                                 (0x00000001)
#define MIS_FAST_ISR_write_data(data)                                                (0x00000001&((data)<<0))
#define MIS_FAST_ISR_write_data_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_FAST_ISR_get_write_data(data)                                            ((0x00000001&(data))>>0)


#define MIS_DBG                                                                      0x1801B02C
#define MIS_DBG_reg_addr                                                             "0xB801B02C"
#define MIS_DBG_reg                                                                  0xB801B02C
#define set_MIS_DBG_reg(data)   (*((volatile unsigned int*) MIS_DBG_reg)=data)
#define get_MIS_DBG_reg   (*((volatile unsigned int*) MIS_DBG_reg))
#define MIS_DBG_inst_adr                                                             "0x000B"
#define MIS_DBG_inst                                                                 0x000B
#define MIS_DBG_write_enable3_shift                                                  (11)
#define MIS_DBG_write_enable3_mask                                                   (0x00000800)
#define MIS_DBG_write_enable3(data)                                                  (0x00000800&((data)<<11))
#define MIS_DBG_write_enable3_src(data)                                              ((0x00000800&(data))>>11)
#define MIS_DBG_get_write_enable3(data)                                              ((0x00000800&(data))>>11)
#define MIS_DBG_sel1_shift                                                           (7)
#define MIS_DBG_sel1_mask                                                            (0x00000780)
#define MIS_DBG_sel1(data)                                                           (0x00000780&((data)<<7))
#define MIS_DBG_sel1_src(data)                                                       ((0x00000780&(data))>>7)
#define MIS_DBG_get_sel1(data)                                                       ((0x00000780&(data))>>7)
#define MIS_DBG_write_enable2_shift                                                  (6)
#define MIS_DBG_write_enable2_mask                                                   (0x00000040)
#define MIS_DBG_write_enable2(data)                                                  (0x00000040&((data)<<6))
#define MIS_DBG_write_enable2_src(data)                                              ((0x00000040&(data))>>6)
#define MIS_DBG_get_write_enable2(data)                                              ((0x00000040&(data))>>6)
#define MIS_DBG_sel0_shift                                                           (2)
#define MIS_DBG_sel0_mask                                                            (0x0000003C)
#define MIS_DBG_sel0(data)                                                           (0x0000003C&((data)<<2))
#define MIS_DBG_sel0_src(data)                                                       ((0x0000003C&(data))>>2)
#define MIS_DBG_get_sel0(data)                                                       ((0x0000003C&(data))>>2)
#define MIS_DBG_write_enable1_shift                                                  (1)
#define MIS_DBG_write_enable1_mask                                                   (0x00000002)
#define MIS_DBG_write_enable1(data)                                                  (0x00000002&((data)<<1))
#define MIS_DBG_write_enable1_src(data)                                              ((0x00000002&(data))>>1)
#define MIS_DBG_get_write_enable1(data)                                              ((0x00000002&(data))>>1)
#define MIS_DBG_enable_shift                                                         (0)
#define MIS_DBG_enable_mask                                                          (0x00000001)
#define MIS_DBG_enable(data)                                                         (0x00000001&((data)<<0))
#define MIS_DBG_enable_src(data)                                                     ((0x00000001&(data))>>0)
#define MIS_DBG_get_enable(data)                                                     ((0x00000001&(data))>>0)


#define MIS_DUMMY                                                                    0x1801B030
#define MIS_DUMMY_reg_addr                                                           "0xB801B030"
#define MIS_DUMMY_reg                                                                0xB801B030
#define set_MIS_DUMMY_reg(data)   (*((volatile unsigned int*) MIS_DUMMY_reg)=data)
#define get_MIS_DUMMY_reg   (*((volatile unsigned int*) MIS_DUMMY_reg))
#define MIS_DUMMY_inst_adr                                                           "0x000C"
#define MIS_DUMMY_inst                                                               0x000C
#define MIS_DUMMY_write_enable4_shift                                                (31)
#define MIS_DUMMY_write_enable4_mask                                                 (0x80000000)
#define MIS_DUMMY_write_enable4(data)                                                (0x80000000&((data)<<31))
#define MIS_DUMMY_write_enable4_src(data)                                            ((0x80000000&(data))>>31)
#define MIS_DUMMY_get_write_enable4(data)                                            ((0x80000000&(data))>>31)
#define MIS_DUMMY_rvd4_shift                                                         (24)
#define MIS_DUMMY_rvd4_mask                                                          (0x7F000000)
#define MIS_DUMMY_rvd4(data)                                                         (0x7F000000&((data)<<24))
#define MIS_DUMMY_rvd4_src(data)                                                     ((0x7F000000&(data))>>24)
#define MIS_DUMMY_get_rvd4(data)                                                     ((0x7F000000&(data))>>24)
#define MIS_DUMMY_write_enable3_shift                                                (23)
#define MIS_DUMMY_write_enable3_mask                                                 (0x00800000)
#define MIS_DUMMY_write_enable3(data)                                                (0x00800000&((data)<<23))
#define MIS_DUMMY_write_enable3_src(data)                                            ((0x00800000&(data))>>23)
#define MIS_DUMMY_get_write_enable3(data)                                            ((0x00800000&(data))>>23)
#define MIS_DUMMY_rvd3_shift                                                         (16)
#define MIS_DUMMY_rvd3_mask                                                          (0x007F0000)
#define MIS_DUMMY_rvd3(data)                                                         (0x007F0000&((data)<<16))
#define MIS_DUMMY_rvd3_src(data)                                                     ((0x007F0000&(data))>>16)
#define MIS_DUMMY_get_rvd3(data)                                                     ((0x007F0000&(data))>>16)
#define MIS_DUMMY_write_enable2_shift                                                (15)
#define MIS_DUMMY_write_enable2_mask                                                 (0x00008000)
#define MIS_DUMMY_write_enable2(data)                                                (0x00008000&((data)<<15))
#define MIS_DUMMY_write_enable2_src(data)                                            ((0x00008000&(data))>>15)
#define MIS_DUMMY_get_write_enable2(data)                                            ((0x00008000&(data))>>15)
#define MIS_DUMMY_rvd2_shift                                                         (8)
#define MIS_DUMMY_rvd2_mask                                                          (0x00007F00)
#define MIS_DUMMY_rvd2(data)                                                         (0x00007F00&((data)<<8))
#define MIS_DUMMY_rvd2_src(data)                                                     ((0x00007F00&(data))>>8)
#define MIS_DUMMY_get_rvd2(data)                                                     ((0x00007F00&(data))>>8)
#define MIS_DUMMY_write_enable1_shift                                                (7)
#define MIS_DUMMY_write_enable1_mask                                                 (0x00000080)
#define MIS_DUMMY_write_enable1(data)                                                (0x00000080&((data)<<7))
#define MIS_DUMMY_write_enable1_src(data)                                            ((0x00000080&(data))>>7)
#define MIS_DUMMY_get_write_enable1(data)                                            ((0x00000080&(data))>>7)
#define MIS_DUMMY_rvd1_shift                                                         (0)
#define MIS_DUMMY_rvd1_mask                                                          (0x0000007F)
#define MIS_DUMMY_rvd1(data)                                                         (0x0000007F&((data)<<0))
#define MIS_DUMMY_rvd1_src(data)                                                     ((0x0000007F&(data))>>0)
#define MIS_DUMMY_get_rvd1(data)                                                     ((0x0000007F&(data))>>0)


#define MIS_UMSK_ISR_GP0A                                                            0x1801B040
#define MIS_UMSK_ISR_GP0A_reg_addr                                                   "0xB801B040"
#define MIS_UMSK_ISR_GP0A_reg                                                        0xB801B040
#define set_MIS_UMSK_ISR_GP0A_reg(data)   (*((volatile unsigned int*) MIS_UMSK_ISR_GP0A_reg)=data)
#define get_MIS_UMSK_ISR_GP0A_reg   (*((volatile unsigned int*) MIS_UMSK_ISR_GP0A_reg))
#define MIS_UMSK_ISR_GP0A_inst_adr                                                   "0x0010"
#define MIS_UMSK_ISR_GP0A_inst                                                       0x0010
#define MIS_UMSK_ISR_GP0A_int30_shift                                                (31)
#define MIS_UMSK_ISR_GP0A_int30_mask                                                 (0x80000000)
#define MIS_UMSK_ISR_GP0A_int30(data)                                                (0x80000000&((data)<<31))
#define MIS_UMSK_ISR_GP0A_int30_src(data)                                            ((0x80000000&(data))>>31)
#define MIS_UMSK_ISR_GP0A_get_int30(data)                                            ((0x80000000&(data))>>31)
#define MIS_UMSK_ISR_GP0A_int29_shift                                                (30)
#define MIS_UMSK_ISR_GP0A_int29_mask                                                 (0x40000000)
#define MIS_UMSK_ISR_GP0A_int29(data)                                                (0x40000000&((data)<<30))
#define MIS_UMSK_ISR_GP0A_int29_src(data)                                            ((0x40000000&(data))>>30)
#define MIS_UMSK_ISR_GP0A_get_int29(data)                                            ((0x40000000&(data))>>30)
#define MIS_UMSK_ISR_GP0A_int28_shift                                                (29)
#define MIS_UMSK_ISR_GP0A_int28_mask                                                 (0x20000000)
#define MIS_UMSK_ISR_GP0A_int28(data)                                                (0x20000000&((data)<<29))
#define MIS_UMSK_ISR_GP0A_int28_src(data)                                            ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP0A_get_int28(data)                                            ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP0A_int27_shift                                                (28)
#define MIS_UMSK_ISR_GP0A_int27_mask                                                 (0x10000000)
#define MIS_UMSK_ISR_GP0A_int27(data)                                                (0x10000000&((data)<<28))
#define MIS_UMSK_ISR_GP0A_int27_src(data)                                            ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP0A_get_int27(data)                                            ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP0A_int26_shift                                                (27)
#define MIS_UMSK_ISR_GP0A_int26_mask                                                 (0x08000000)
#define MIS_UMSK_ISR_GP0A_int26(data)                                                (0x08000000&((data)<<27))
#define MIS_UMSK_ISR_GP0A_int26_src(data)                                            ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP0A_get_int26(data)                                            ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP0A_int25_shift                                                (26)
#define MIS_UMSK_ISR_GP0A_int25_mask                                                 (0x04000000)
#define MIS_UMSK_ISR_GP0A_int25(data)                                                (0x04000000&((data)<<26))
#define MIS_UMSK_ISR_GP0A_int25_src(data)                                            ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP0A_get_int25(data)                                            ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP0A_int24_shift                                                (25)
#define MIS_UMSK_ISR_GP0A_int24_mask                                                 (0x02000000)
#define MIS_UMSK_ISR_GP0A_int24(data)                                                (0x02000000&((data)<<25))
#define MIS_UMSK_ISR_GP0A_int24_src(data)                                            ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP0A_get_int24(data)                                            ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP0A_int23_shift                                                (24)
#define MIS_UMSK_ISR_GP0A_int23_mask                                                 (0x01000000)
#define MIS_UMSK_ISR_GP0A_int23(data)                                                (0x01000000&((data)<<24))
#define MIS_UMSK_ISR_GP0A_int23_src(data)                                            ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP0A_get_int23(data)                                            ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP0A_int22_shift                                                (23)
#define MIS_UMSK_ISR_GP0A_int22_mask                                                 (0x00800000)
#define MIS_UMSK_ISR_GP0A_int22(data)                                                (0x00800000&((data)<<23))
#define MIS_UMSK_ISR_GP0A_int22_src(data)                                            ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP0A_get_int22(data)                                            ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP0A_int21_shift                                                (22)
#define MIS_UMSK_ISR_GP0A_int21_mask                                                 (0x00400000)
#define MIS_UMSK_ISR_GP0A_int21(data)                                                (0x00400000&((data)<<22))
#define MIS_UMSK_ISR_GP0A_int21_src(data)                                            ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP0A_get_int21(data)                                            ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP0A_int20_shift                                                (21)
#define MIS_UMSK_ISR_GP0A_int20_mask                                                 (0x00200000)
#define MIS_UMSK_ISR_GP0A_int20(data)                                                (0x00200000&((data)<<21))
#define MIS_UMSK_ISR_GP0A_int20_src(data)                                            ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP0A_get_int20(data)                                            ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP0A_int19_shift                                                (20)
#define MIS_UMSK_ISR_GP0A_int19_mask                                                 (0x00100000)
#define MIS_UMSK_ISR_GP0A_int19(data)                                                (0x00100000&((data)<<20))
#define MIS_UMSK_ISR_GP0A_int19_src(data)                                            ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP0A_get_int19(data)                                            ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP0A_int18_shift                                                (19)
#define MIS_UMSK_ISR_GP0A_int18_mask                                                 (0x00080000)
#define MIS_UMSK_ISR_GP0A_int18(data)                                                (0x00080000&((data)<<19))
#define MIS_UMSK_ISR_GP0A_int18_src(data)                                            ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP0A_get_int18(data)                                            ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP0A_int17_shift                                                (18)
#define MIS_UMSK_ISR_GP0A_int17_mask                                                 (0x00040000)
#define MIS_UMSK_ISR_GP0A_int17(data)                                                (0x00040000&((data)<<18))
#define MIS_UMSK_ISR_GP0A_int17_src(data)                                            ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP0A_get_int17(data)                                            ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP0A_int16_shift                                                (17)
#define MIS_UMSK_ISR_GP0A_int16_mask                                                 (0x00020000)
#define MIS_UMSK_ISR_GP0A_int16(data)                                                (0x00020000&((data)<<17))
#define MIS_UMSK_ISR_GP0A_int16_src(data)                                            ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP0A_get_int16(data)                                            ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP0A_int15_shift                                                (16)
#define MIS_UMSK_ISR_GP0A_int15_mask                                                 (0x00010000)
#define MIS_UMSK_ISR_GP0A_int15(data)                                                (0x00010000&((data)<<16))
#define MIS_UMSK_ISR_GP0A_int15_src(data)                                            ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP0A_get_int15(data)                                            ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP0A_int14_shift                                                (15)
#define MIS_UMSK_ISR_GP0A_int14_mask                                                 (0x00008000)
#define MIS_UMSK_ISR_GP0A_int14(data)                                                (0x00008000&((data)<<15))
#define MIS_UMSK_ISR_GP0A_int14_src(data)                                            ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP0A_get_int14(data)                                            ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP0A_int13_shift                                                (14)
#define MIS_UMSK_ISR_GP0A_int13_mask                                                 (0x00004000)
#define MIS_UMSK_ISR_GP0A_int13(data)                                                (0x00004000&((data)<<14))
#define MIS_UMSK_ISR_GP0A_int13_src(data)                                            ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP0A_get_int13(data)                                            ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP0A_int12_shift                                                (13)
#define MIS_UMSK_ISR_GP0A_int12_mask                                                 (0x00002000)
#define MIS_UMSK_ISR_GP0A_int12(data)                                                (0x00002000&((data)<<13))
#define MIS_UMSK_ISR_GP0A_int12_src(data)                                            ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP0A_get_int12(data)                                            ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP0A_int11_shift                                                (12)
#define MIS_UMSK_ISR_GP0A_int11_mask                                                 (0x00001000)
#define MIS_UMSK_ISR_GP0A_int11(data)                                                (0x00001000&((data)<<12))
#define MIS_UMSK_ISR_GP0A_int11_src(data)                                            ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP0A_get_int11(data)                                            ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP0A_int10_shift                                                (11)
#define MIS_UMSK_ISR_GP0A_int10_mask                                                 (0x00000800)
#define MIS_UMSK_ISR_GP0A_int10(data)                                                (0x00000800&((data)<<11))
#define MIS_UMSK_ISR_GP0A_int10_src(data)                                            ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP0A_get_int10(data)                                            ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP0A_int9_shift                                                 (10)
#define MIS_UMSK_ISR_GP0A_int9_mask                                                  (0x00000400)
#define MIS_UMSK_ISR_GP0A_int9(data)                                                 (0x00000400&((data)<<10))
#define MIS_UMSK_ISR_GP0A_int9_src(data)                                             ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP0A_get_int9(data)                                             ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP0A_int8_shift                                                 (9)
#define MIS_UMSK_ISR_GP0A_int8_mask                                                  (0x00000200)
#define MIS_UMSK_ISR_GP0A_int8(data)                                                 (0x00000200&((data)<<9))
#define MIS_UMSK_ISR_GP0A_int8_src(data)                                             ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP0A_get_int8(data)                                             ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP0A_int7_shift                                                 (8)
#define MIS_UMSK_ISR_GP0A_int7_mask                                                  (0x00000100)
#define MIS_UMSK_ISR_GP0A_int7(data)                                                 (0x00000100&((data)<<8))
#define MIS_UMSK_ISR_GP0A_int7_src(data)                                             ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP0A_get_int7(data)                                             ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP0A_int6_shift                                                 (7)
#define MIS_UMSK_ISR_GP0A_int6_mask                                                  (0x00000080)
#define MIS_UMSK_ISR_GP0A_int6(data)                                                 (0x00000080&((data)<<7))
#define MIS_UMSK_ISR_GP0A_int6_src(data)                                             ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP0A_get_int6(data)                                             ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP0A_int5_shift                                                 (6)
#define MIS_UMSK_ISR_GP0A_int5_mask                                                  (0x00000040)
#define MIS_UMSK_ISR_GP0A_int5(data)                                                 (0x00000040&((data)<<6))
#define MIS_UMSK_ISR_GP0A_int5_src(data)                                             ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP0A_get_int5(data)                                             ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP0A_int4_shift                                                 (5)
#define MIS_UMSK_ISR_GP0A_int4_mask                                                  (0x00000020)
#define MIS_UMSK_ISR_GP0A_int4(data)                                                 (0x00000020&((data)<<5))
#define MIS_UMSK_ISR_GP0A_int4_src(data)                                             ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP0A_get_int4(data)                                             ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP0A_int3_shift                                                 (4)
#define MIS_UMSK_ISR_GP0A_int3_mask                                                  (0x00000010)
#define MIS_UMSK_ISR_GP0A_int3(data)                                                 (0x00000010&((data)<<4))
#define MIS_UMSK_ISR_GP0A_int3_src(data)                                             ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP0A_get_int3(data)                                             ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP0A_int2_shift                                                 (3)
#define MIS_UMSK_ISR_GP0A_int2_mask                                                  (0x00000008)
#define MIS_UMSK_ISR_GP0A_int2(data)                                                 (0x00000008&((data)<<3))
#define MIS_UMSK_ISR_GP0A_int2_src(data)                                             ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP0A_get_int2(data)                                             ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP0A_int1_shift                                                 (2)
#define MIS_UMSK_ISR_GP0A_int1_mask                                                  (0x00000004)
#define MIS_UMSK_ISR_GP0A_int1(data)                                                 (0x00000004&((data)<<2))
#define MIS_UMSK_ISR_GP0A_int1_src(data)                                             ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP0A_get_int1(data)                                             ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP0A_int0_shift                                                 (1)
#define MIS_UMSK_ISR_GP0A_int0_mask                                                  (0x00000002)
#define MIS_UMSK_ISR_GP0A_int0(data)                                                 (0x00000002&((data)<<1))
#define MIS_UMSK_ISR_GP0A_int0_src(data)                                             ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP0A_get_int0(data)                                             ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP0A_write_data_shift                                           (0)
#define MIS_UMSK_ISR_GP0A_write_data_mask                                            (0x00000001)
#define MIS_UMSK_ISR_GP0A_write_data(data)                                           (0x00000001&((data)<<0))
#define MIS_UMSK_ISR_GP0A_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_UMSK_ISR_GP0A_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define MIS_UMSK_ISR_GP1A                                                            0x1801B044
#define MIS_UMSK_ISR_GP1A_reg_addr                                                   "0xB801B044"
#define MIS_UMSK_ISR_GP1A_reg                                                        0xB801B044
#define set_MIS_UMSK_ISR_GP1A_reg(data)   (*((volatile unsigned int*) MIS_UMSK_ISR_GP1A_reg)=data)
#define get_MIS_UMSK_ISR_GP1A_reg   (*((volatile unsigned int*) MIS_UMSK_ISR_GP1A_reg))
#define MIS_UMSK_ISR_GP1A_inst_adr                                                   "0x0011"
#define MIS_UMSK_ISR_GP1A_inst                                                       0x0011
#define MIS_UMSK_ISR_GP1A_int59_shift                                                (29)
#define MIS_UMSK_ISR_GP1A_int59_mask                                                 (0x20000000)
#define MIS_UMSK_ISR_GP1A_int59(data)                                                (0x20000000&((data)<<29))
#define MIS_UMSK_ISR_GP1A_int59_src(data)                                            ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP1A_get_int59(data)                                            ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP1A_int58_shift                                                (28)
#define MIS_UMSK_ISR_GP1A_int58_mask                                                 (0x10000000)
#define MIS_UMSK_ISR_GP1A_int58(data)                                                (0x10000000&((data)<<28))
#define MIS_UMSK_ISR_GP1A_int58_src(data)                                            ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP1A_get_int58(data)                                            ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP1A_int57_shift                                                (27)
#define MIS_UMSK_ISR_GP1A_int57_mask                                                 (0x08000000)
#define MIS_UMSK_ISR_GP1A_int57(data)                                                (0x08000000&((data)<<27))
#define MIS_UMSK_ISR_GP1A_int57_src(data)                                            ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP1A_get_int57(data)                                            ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP1A_int56_shift                                                (26)
#define MIS_UMSK_ISR_GP1A_int56_mask                                                 (0x04000000)
#define MIS_UMSK_ISR_GP1A_int56(data)                                                (0x04000000&((data)<<26))
#define MIS_UMSK_ISR_GP1A_int56_src(data)                                            ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP1A_get_int56(data)                                            ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP1A_int55_shift                                                (25)
#define MIS_UMSK_ISR_GP1A_int55_mask                                                 (0x02000000)
#define MIS_UMSK_ISR_GP1A_int55(data)                                                (0x02000000&((data)<<25))
#define MIS_UMSK_ISR_GP1A_int55_src(data)                                            ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP1A_get_int55(data)                                            ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP1A_int54_shift                                                (24)
#define MIS_UMSK_ISR_GP1A_int54_mask                                                 (0x01000000)
#define MIS_UMSK_ISR_GP1A_int54(data)                                                (0x01000000&((data)<<24))
#define MIS_UMSK_ISR_GP1A_int54_src(data)                                            ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP1A_get_int54(data)                                            ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP1A_int53_shift                                                (23)
#define MIS_UMSK_ISR_GP1A_int53_mask                                                 (0x00800000)
#define MIS_UMSK_ISR_GP1A_int53(data)                                                (0x00800000&((data)<<23))
#define MIS_UMSK_ISR_GP1A_int53_src(data)                                            ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP1A_get_int53(data)                                            ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP1A_int52_shift                                                (22)
#define MIS_UMSK_ISR_GP1A_int52_mask                                                 (0x00400000)
#define MIS_UMSK_ISR_GP1A_int52(data)                                                (0x00400000&((data)<<22))
#define MIS_UMSK_ISR_GP1A_int52_src(data)                                            ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP1A_get_int52(data)                                            ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP1A_int51_shift                                                (21)
#define MIS_UMSK_ISR_GP1A_int51_mask                                                 (0x00200000)
#define MIS_UMSK_ISR_GP1A_int51(data)                                                (0x00200000&((data)<<21))
#define MIS_UMSK_ISR_GP1A_int51_src(data)                                            ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP1A_get_int51(data)                                            ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP1A_int50_shift                                                (20)
#define MIS_UMSK_ISR_GP1A_int50_mask                                                 (0x00100000)
#define MIS_UMSK_ISR_GP1A_int50(data)                                                (0x00100000&((data)<<20))
#define MIS_UMSK_ISR_GP1A_int50_src(data)                                            ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP1A_get_int50(data)                                            ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP1A_int49_shift                                                (19)
#define MIS_UMSK_ISR_GP1A_int49_mask                                                 (0x00080000)
#define MIS_UMSK_ISR_GP1A_int49(data)                                                (0x00080000&((data)<<19))
#define MIS_UMSK_ISR_GP1A_int49_src(data)                                            ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP1A_get_int49(data)                                            ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP1A_int48_shift                                                (18)
#define MIS_UMSK_ISR_GP1A_int48_mask                                                 (0x00040000)
#define MIS_UMSK_ISR_GP1A_int48(data)                                                (0x00040000&((data)<<18))
#define MIS_UMSK_ISR_GP1A_int48_src(data)                                            ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP1A_get_int48(data)                                            ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP1A_int47_shift                                                (17)
#define MIS_UMSK_ISR_GP1A_int47_mask                                                 (0x00020000)
#define MIS_UMSK_ISR_GP1A_int47(data)                                                (0x00020000&((data)<<17))
#define MIS_UMSK_ISR_GP1A_int47_src(data)                                            ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP1A_get_int47(data)                                            ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP1A_int46_shift                                                (16)
#define MIS_UMSK_ISR_GP1A_int46_mask                                                 (0x00010000)
#define MIS_UMSK_ISR_GP1A_int46(data)                                                (0x00010000&((data)<<16))
#define MIS_UMSK_ISR_GP1A_int46_src(data)                                            ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP1A_get_int46(data)                                            ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP1A_int45_shift                                                (15)
#define MIS_UMSK_ISR_GP1A_int45_mask                                                 (0x00008000)
#define MIS_UMSK_ISR_GP1A_int45(data)                                                (0x00008000&((data)<<15))
#define MIS_UMSK_ISR_GP1A_int45_src(data)                                            ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP1A_get_int45(data)                                            ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP1A_int44_shift                                                (14)
#define MIS_UMSK_ISR_GP1A_int44_mask                                                 (0x00004000)
#define MIS_UMSK_ISR_GP1A_int44(data)                                                (0x00004000&((data)<<14))
#define MIS_UMSK_ISR_GP1A_int44_src(data)                                            ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP1A_get_int44(data)                                            ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP1A_int43_shift                                                (13)
#define MIS_UMSK_ISR_GP1A_int43_mask                                                 (0x00002000)
#define MIS_UMSK_ISR_GP1A_int43(data)                                                (0x00002000&((data)<<13))
#define MIS_UMSK_ISR_GP1A_int43_src(data)                                            ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP1A_get_int43(data)                                            ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP1A_int42_shift                                                (12)
#define MIS_UMSK_ISR_GP1A_int42_mask                                                 (0x00001000)
#define MIS_UMSK_ISR_GP1A_int42(data)                                                (0x00001000&((data)<<12))
#define MIS_UMSK_ISR_GP1A_int42_src(data)                                            ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP1A_get_int42(data)                                            ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP1A_int41_shift                                                (11)
#define MIS_UMSK_ISR_GP1A_int41_mask                                                 (0x00000800)
#define MIS_UMSK_ISR_GP1A_int41(data)                                                (0x00000800&((data)<<11))
#define MIS_UMSK_ISR_GP1A_int41_src(data)                                            ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP1A_get_int41(data)                                            ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP1A_int40_shift                                                (10)
#define MIS_UMSK_ISR_GP1A_int40_mask                                                 (0x00000400)
#define MIS_UMSK_ISR_GP1A_int40(data)                                                (0x00000400&((data)<<10))
#define MIS_UMSK_ISR_GP1A_int40_src(data)                                            ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP1A_get_int40(data)                                            ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP1A_int39_shift                                                (9)
#define MIS_UMSK_ISR_GP1A_int39_mask                                                 (0x00000200)
#define MIS_UMSK_ISR_GP1A_int39(data)                                                (0x00000200&((data)<<9))
#define MIS_UMSK_ISR_GP1A_int39_src(data)                                            ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP1A_get_int39(data)                                            ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP1A_int38_shift                                                (8)
#define MIS_UMSK_ISR_GP1A_int38_mask                                                 (0x00000100)
#define MIS_UMSK_ISR_GP1A_int38(data)                                                (0x00000100&((data)<<8))
#define MIS_UMSK_ISR_GP1A_int38_src(data)                                            ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP1A_get_int38(data)                                            ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP1A_int37_shift                                                (7)
#define MIS_UMSK_ISR_GP1A_int37_mask                                                 (0x00000080)
#define MIS_UMSK_ISR_GP1A_int37(data)                                                (0x00000080&((data)<<7))
#define MIS_UMSK_ISR_GP1A_int37_src(data)                                            ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP1A_get_int37(data)                                            ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP1A_int36_shift                                                (6)
#define MIS_UMSK_ISR_GP1A_int36_mask                                                 (0x00000040)
#define MIS_UMSK_ISR_GP1A_int36(data)                                                (0x00000040&((data)<<6))
#define MIS_UMSK_ISR_GP1A_int36_src(data)                                            ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP1A_get_int36(data)                                            ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP1A_int35_shift                                                (5)
#define MIS_UMSK_ISR_GP1A_int35_mask                                                 (0x00000020)
#define MIS_UMSK_ISR_GP1A_int35(data)                                                (0x00000020&((data)<<5))
#define MIS_UMSK_ISR_GP1A_int35_src(data)                                            ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP1A_get_int35(data)                                            ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP1A_int34_shift                                                (4)
#define MIS_UMSK_ISR_GP1A_int34_mask                                                 (0x00000010)
#define MIS_UMSK_ISR_GP1A_int34(data)                                                (0x00000010&((data)<<4))
#define MIS_UMSK_ISR_GP1A_int34_src(data)                                            ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP1A_get_int34(data)                                            ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP1A_int33_shift                                                (3)
#define MIS_UMSK_ISR_GP1A_int33_mask                                                 (0x00000008)
#define MIS_UMSK_ISR_GP1A_int33(data)                                                (0x00000008&((data)<<3))
#define MIS_UMSK_ISR_GP1A_int33_src(data)                                            ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP1A_get_int33(data)                                            ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP1A_int32_shift                                                (2)
#define MIS_UMSK_ISR_GP1A_int32_mask                                                 (0x00000004)
#define MIS_UMSK_ISR_GP1A_int32(data)                                                (0x00000004&((data)<<2))
#define MIS_UMSK_ISR_GP1A_int32_src(data)                                            ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP1A_get_int32(data)                                            ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP1A_int31_shift                                                (1)
#define MIS_UMSK_ISR_GP1A_int31_mask                                                 (0x00000002)
#define MIS_UMSK_ISR_GP1A_int31(data)                                                (0x00000002&((data)<<1))
#define MIS_UMSK_ISR_GP1A_int31_src(data)                                            ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP1A_get_int31(data)                                            ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP1A_write_data_shift                                           (0)
#define MIS_UMSK_ISR_GP1A_write_data_mask                                            (0x00000001)
#define MIS_UMSK_ISR_GP1A_write_data(data)                                           (0x00000001&((data)<<0))
#define MIS_UMSK_ISR_GP1A_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_UMSK_ISR_GP1A_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define MIS_UMSK_ISR_GP0DA                                                           0x1801B054
#define MIS_UMSK_ISR_GP0DA_reg_addr                                                  "0xB801B054"
#define MIS_UMSK_ISR_GP0DA_reg                                                       0xB801B054
#define set_MIS_UMSK_ISR_GP0DA_reg(data)   (*((volatile unsigned int*) MIS_UMSK_ISR_GP0DA_reg)=data)
#define get_MIS_UMSK_ISR_GP0DA_reg   (*((volatile unsigned int*) MIS_UMSK_ISR_GP0DA_reg))
#define MIS_UMSK_ISR_GP0DA_inst_adr                                                  "0x0015"
#define MIS_UMSK_ISR_GP0DA_inst                                                      0x0015
#define MIS_UMSK_ISR_GP0DA_int30_shift                                               (31)
#define MIS_UMSK_ISR_GP0DA_int30_mask                                                (0x80000000)
#define MIS_UMSK_ISR_GP0DA_int30(data)                                               (0x80000000&((data)<<31))
#define MIS_UMSK_ISR_GP0DA_int30_src(data)                                           ((0x80000000&(data))>>31)
#define MIS_UMSK_ISR_GP0DA_get_int30(data)                                           ((0x80000000&(data))>>31)
#define MIS_UMSK_ISR_GP0DA_int29_shift                                               (30)
#define MIS_UMSK_ISR_GP0DA_int29_mask                                                (0x40000000)
#define MIS_UMSK_ISR_GP0DA_int29(data)                                               (0x40000000&((data)<<30))
#define MIS_UMSK_ISR_GP0DA_int29_src(data)                                           ((0x40000000&(data))>>30)
#define MIS_UMSK_ISR_GP0DA_get_int29(data)                                           ((0x40000000&(data))>>30)
#define MIS_UMSK_ISR_GP0DA_int28_shift                                               (29)
#define MIS_UMSK_ISR_GP0DA_int28_mask                                                (0x20000000)
#define MIS_UMSK_ISR_GP0DA_int28(data)                                               (0x20000000&((data)<<29))
#define MIS_UMSK_ISR_GP0DA_int28_src(data)                                           ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP0DA_get_int28(data)                                           ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP0DA_int27_shift                                               (28)
#define MIS_UMSK_ISR_GP0DA_int27_mask                                                (0x10000000)
#define MIS_UMSK_ISR_GP0DA_int27(data)                                               (0x10000000&((data)<<28))
#define MIS_UMSK_ISR_GP0DA_int27_src(data)                                           ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP0DA_get_int27(data)                                           ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP0DA_int26_shift                                               (27)
#define MIS_UMSK_ISR_GP0DA_int26_mask                                                (0x08000000)
#define MIS_UMSK_ISR_GP0DA_int26(data)                                               (0x08000000&((data)<<27))
#define MIS_UMSK_ISR_GP0DA_int26_src(data)                                           ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP0DA_get_int26(data)                                           ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP0DA_int25_shift                                               (26)
#define MIS_UMSK_ISR_GP0DA_int25_mask                                                (0x04000000)
#define MIS_UMSK_ISR_GP0DA_int25(data)                                               (0x04000000&((data)<<26))
#define MIS_UMSK_ISR_GP0DA_int25_src(data)                                           ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP0DA_get_int25(data)                                           ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP0DA_int24_shift                                               (25)
#define MIS_UMSK_ISR_GP0DA_int24_mask                                                (0x02000000)
#define MIS_UMSK_ISR_GP0DA_int24(data)                                               (0x02000000&((data)<<25))
#define MIS_UMSK_ISR_GP0DA_int24_src(data)                                           ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP0DA_get_int24(data)                                           ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP0DA_int23_shift                                               (24)
#define MIS_UMSK_ISR_GP0DA_int23_mask                                                (0x01000000)
#define MIS_UMSK_ISR_GP0DA_int23(data)                                               (0x01000000&((data)<<24))
#define MIS_UMSK_ISR_GP0DA_int23_src(data)                                           ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP0DA_get_int23(data)                                           ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP0DA_int22_shift                                               (23)
#define MIS_UMSK_ISR_GP0DA_int22_mask                                                (0x00800000)
#define MIS_UMSK_ISR_GP0DA_int22(data)                                               (0x00800000&((data)<<23))
#define MIS_UMSK_ISR_GP0DA_int22_src(data)                                           ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP0DA_get_int22(data)                                           ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP0DA_int21_shift                                               (22)
#define MIS_UMSK_ISR_GP0DA_int21_mask                                                (0x00400000)
#define MIS_UMSK_ISR_GP0DA_int21(data)                                               (0x00400000&((data)<<22))
#define MIS_UMSK_ISR_GP0DA_int21_src(data)                                           ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP0DA_get_int21(data)                                           ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP0DA_int20_shift                                               (21)
#define MIS_UMSK_ISR_GP0DA_int20_mask                                                (0x00200000)
#define MIS_UMSK_ISR_GP0DA_int20(data)                                               (0x00200000&((data)<<21))
#define MIS_UMSK_ISR_GP0DA_int20_src(data)                                           ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP0DA_get_int20(data)                                           ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP0DA_int19_shift                                               (20)
#define MIS_UMSK_ISR_GP0DA_int19_mask                                                (0x00100000)
#define MIS_UMSK_ISR_GP0DA_int19(data)                                               (0x00100000&((data)<<20))
#define MIS_UMSK_ISR_GP0DA_int19_src(data)                                           ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP0DA_get_int19(data)                                           ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP0DA_int18_shift                                               (19)
#define MIS_UMSK_ISR_GP0DA_int18_mask                                                (0x00080000)
#define MIS_UMSK_ISR_GP0DA_int18(data)                                               (0x00080000&((data)<<19))
#define MIS_UMSK_ISR_GP0DA_int18_src(data)                                           ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP0DA_get_int18(data)                                           ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP0DA_int17_shift                                               (18)
#define MIS_UMSK_ISR_GP0DA_int17_mask                                                (0x00040000)
#define MIS_UMSK_ISR_GP0DA_int17(data)                                               (0x00040000&((data)<<18))
#define MIS_UMSK_ISR_GP0DA_int17_src(data)                                           ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP0DA_get_int17(data)                                           ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP0DA_int16_shift                                               (17)
#define MIS_UMSK_ISR_GP0DA_int16_mask                                                (0x00020000)
#define MIS_UMSK_ISR_GP0DA_int16(data)                                               (0x00020000&((data)<<17))
#define MIS_UMSK_ISR_GP0DA_int16_src(data)                                           ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP0DA_get_int16(data)                                           ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP0DA_int15_shift                                               (16)
#define MIS_UMSK_ISR_GP0DA_int15_mask                                                (0x00010000)
#define MIS_UMSK_ISR_GP0DA_int15(data)                                               (0x00010000&((data)<<16))
#define MIS_UMSK_ISR_GP0DA_int15_src(data)                                           ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP0DA_get_int15(data)                                           ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP0DA_int14_shift                                               (15)
#define MIS_UMSK_ISR_GP0DA_int14_mask                                                (0x00008000)
#define MIS_UMSK_ISR_GP0DA_int14(data)                                               (0x00008000&((data)<<15))
#define MIS_UMSK_ISR_GP0DA_int14_src(data)                                           ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP0DA_get_int14(data)                                           ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP0DA_int13_shift                                               (14)
#define MIS_UMSK_ISR_GP0DA_int13_mask                                                (0x00004000)
#define MIS_UMSK_ISR_GP0DA_int13(data)                                               (0x00004000&((data)<<14))
#define MIS_UMSK_ISR_GP0DA_int13_src(data)                                           ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP0DA_get_int13(data)                                           ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP0DA_int12_shift                                               (13)
#define MIS_UMSK_ISR_GP0DA_int12_mask                                                (0x00002000)
#define MIS_UMSK_ISR_GP0DA_int12(data)                                               (0x00002000&((data)<<13))
#define MIS_UMSK_ISR_GP0DA_int12_src(data)                                           ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP0DA_get_int12(data)                                           ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP0DA_int11_shift                                               (12)
#define MIS_UMSK_ISR_GP0DA_int11_mask                                                (0x00001000)
#define MIS_UMSK_ISR_GP0DA_int11(data)                                               (0x00001000&((data)<<12))
#define MIS_UMSK_ISR_GP0DA_int11_src(data)                                           ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP0DA_get_int11(data)                                           ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP0DA_int10_shift                                               (11)
#define MIS_UMSK_ISR_GP0DA_int10_mask                                                (0x00000800)
#define MIS_UMSK_ISR_GP0DA_int10(data)                                               (0x00000800&((data)<<11))
#define MIS_UMSK_ISR_GP0DA_int10_src(data)                                           ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP0DA_get_int10(data)                                           ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP0DA_int9_shift                                                (10)
#define MIS_UMSK_ISR_GP0DA_int9_mask                                                 (0x00000400)
#define MIS_UMSK_ISR_GP0DA_int9(data)                                                (0x00000400&((data)<<10))
#define MIS_UMSK_ISR_GP0DA_int9_src(data)                                            ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP0DA_get_int9(data)                                            ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP0DA_int8_shift                                                (9)
#define MIS_UMSK_ISR_GP0DA_int8_mask                                                 (0x00000200)
#define MIS_UMSK_ISR_GP0DA_int8(data)                                                (0x00000200&((data)<<9))
#define MIS_UMSK_ISR_GP0DA_int8_src(data)                                            ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP0DA_get_int8(data)                                            ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP0DA_int7_shift                                                (8)
#define MIS_UMSK_ISR_GP0DA_int7_mask                                                 (0x00000100)
#define MIS_UMSK_ISR_GP0DA_int7(data)                                                (0x00000100&((data)<<8))
#define MIS_UMSK_ISR_GP0DA_int7_src(data)                                            ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP0DA_get_int7(data)                                            ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP0DA_int6_shift                                                (7)
#define MIS_UMSK_ISR_GP0DA_int6_mask                                                 (0x00000080)
#define MIS_UMSK_ISR_GP0DA_int6(data)                                                (0x00000080&((data)<<7))
#define MIS_UMSK_ISR_GP0DA_int6_src(data)                                            ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP0DA_get_int6(data)                                            ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP0DA_int5_shift                                                (6)
#define MIS_UMSK_ISR_GP0DA_int5_mask                                                 (0x00000040)
#define MIS_UMSK_ISR_GP0DA_int5(data)                                                (0x00000040&((data)<<6))
#define MIS_UMSK_ISR_GP0DA_int5_src(data)                                            ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP0DA_get_int5(data)                                            ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP0DA_int4_shift                                                (5)
#define MIS_UMSK_ISR_GP0DA_int4_mask                                                 (0x00000020)
#define MIS_UMSK_ISR_GP0DA_int4(data)                                                (0x00000020&((data)<<5))
#define MIS_UMSK_ISR_GP0DA_int4_src(data)                                            ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP0DA_get_int4(data)                                            ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP0DA_int3_shift                                                (4)
#define MIS_UMSK_ISR_GP0DA_int3_mask                                                 (0x00000010)
#define MIS_UMSK_ISR_GP0DA_int3(data)                                                (0x00000010&((data)<<4))
#define MIS_UMSK_ISR_GP0DA_int3_src(data)                                            ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP0DA_get_int3(data)                                            ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP0DA_int2_shift                                                (3)
#define MIS_UMSK_ISR_GP0DA_int2_mask                                                 (0x00000008)
#define MIS_UMSK_ISR_GP0DA_int2(data)                                                (0x00000008&((data)<<3))
#define MIS_UMSK_ISR_GP0DA_int2_src(data)                                            ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP0DA_get_int2(data)                                            ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP0DA_int1_shift                                                (2)
#define MIS_UMSK_ISR_GP0DA_int1_mask                                                 (0x00000004)
#define MIS_UMSK_ISR_GP0DA_int1(data)                                                (0x00000004&((data)<<2))
#define MIS_UMSK_ISR_GP0DA_int1_src(data)                                            ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP0DA_get_int1(data)                                            ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP0DA_int0_shift                                                (1)
#define MIS_UMSK_ISR_GP0DA_int0_mask                                                 (0x00000002)
#define MIS_UMSK_ISR_GP0DA_int0(data)                                                (0x00000002&((data)<<1))
#define MIS_UMSK_ISR_GP0DA_int0_src(data)                                            ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP0DA_get_int0(data)                                            ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP0DA_write_data_shift                                          (0)
#define MIS_UMSK_ISR_GP0DA_write_data_mask                                           (0x00000001)
#define MIS_UMSK_ISR_GP0DA_write_data(data)                                          (0x00000001&((data)<<0))
#define MIS_UMSK_ISR_GP0DA_write_data_src(data)                                      ((0x00000001&(data))>>0)
#define MIS_UMSK_ISR_GP0DA_get_write_data(data)                                      ((0x00000001&(data))>>0)


#define MIS_UMSK_ISR_GP1DA                                                           0x1801B058
#define MIS_UMSK_ISR_GP1DA_reg_addr                                                  "0xB801B058"
#define MIS_UMSK_ISR_GP1DA_reg                                                       0xB801B058
#define set_MIS_UMSK_ISR_GP1DA_reg(data)   (*((volatile unsigned int*) MIS_UMSK_ISR_GP1DA_reg)=data)
#define get_MIS_UMSK_ISR_GP1DA_reg   (*((volatile unsigned int*) MIS_UMSK_ISR_GP1DA_reg))
#define MIS_UMSK_ISR_GP1DA_inst_adr                                                  "0x0016"
#define MIS_UMSK_ISR_GP1DA_inst                                                      0x0016
#define MIS_UMSK_ISR_GP1DA_int59_shift                                               (29)
#define MIS_UMSK_ISR_GP1DA_int59_mask                                                (0x20000000)
#define MIS_UMSK_ISR_GP1DA_int59(data)                                               (0x20000000&((data)<<29))
#define MIS_UMSK_ISR_GP1DA_int59_src(data)                                           ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP1DA_get_int59(data)                                           ((0x20000000&(data))>>29)
#define MIS_UMSK_ISR_GP1DA_int58_shift                                               (28)
#define MIS_UMSK_ISR_GP1DA_int58_mask                                                (0x10000000)
#define MIS_UMSK_ISR_GP1DA_int58(data)                                               (0x10000000&((data)<<28))
#define MIS_UMSK_ISR_GP1DA_int58_src(data)                                           ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP1DA_get_int58(data)                                           ((0x10000000&(data))>>28)
#define MIS_UMSK_ISR_GP1DA_int57_shift                                               (27)
#define MIS_UMSK_ISR_GP1DA_int57_mask                                                (0x08000000)
#define MIS_UMSK_ISR_GP1DA_int57(data)                                               (0x08000000&((data)<<27))
#define MIS_UMSK_ISR_GP1DA_int57_src(data)                                           ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP1DA_get_int57(data)                                           ((0x08000000&(data))>>27)
#define MIS_UMSK_ISR_GP1DA_int56_shift                                               (26)
#define MIS_UMSK_ISR_GP1DA_int56_mask                                                (0x04000000)
#define MIS_UMSK_ISR_GP1DA_int56(data)                                               (0x04000000&((data)<<26))
#define MIS_UMSK_ISR_GP1DA_int56_src(data)                                           ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP1DA_get_int56(data)                                           ((0x04000000&(data))>>26)
#define MIS_UMSK_ISR_GP1DA_int55_shift                                               (25)
#define MIS_UMSK_ISR_GP1DA_int55_mask                                                (0x02000000)
#define MIS_UMSK_ISR_GP1DA_int55(data)                                               (0x02000000&((data)<<25))
#define MIS_UMSK_ISR_GP1DA_int55_src(data)                                           ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP1DA_get_int55(data)                                           ((0x02000000&(data))>>25)
#define MIS_UMSK_ISR_GP1DA_int54_shift                                               (24)
#define MIS_UMSK_ISR_GP1DA_int54_mask                                                (0x01000000)
#define MIS_UMSK_ISR_GP1DA_int54(data)                                               (0x01000000&((data)<<24))
#define MIS_UMSK_ISR_GP1DA_int54_src(data)                                           ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP1DA_get_int54(data)                                           ((0x01000000&(data))>>24)
#define MIS_UMSK_ISR_GP1DA_int53_shift                                               (23)
#define MIS_UMSK_ISR_GP1DA_int53_mask                                                (0x00800000)
#define MIS_UMSK_ISR_GP1DA_int53(data)                                               (0x00800000&((data)<<23))
#define MIS_UMSK_ISR_GP1DA_int53_src(data)                                           ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP1DA_get_int53(data)                                           ((0x00800000&(data))>>23)
#define MIS_UMSK_ISR_GP1DA_int52_shift                                               (22)
#define MIS_UMSK_ISR_GP1DA_int52_mask                                                (0x00400000)
#define MIS_UMSK_ISR_GP1DA_int52(data)                                               (0x00400000&((data)<<22))
#define MIS_UMSK_ISR_GP1DA_int52_src(data)                                           ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP1DA_get_int52(data)                                           ((0x00400000&(data))>>22)
#define MIS_UMSK_ISR_GP1DA_int51_shift                                               (21)
#define MIS_UMSK_ISR_GP1DA_int51_mask                                                (0x00200000)
#define MIS_UMSK_ISR_GP1DA_int51(data)                                               (0x00200000&((data)<<21))
#define MIS_UMSK_ISR_GP1DA_int51_src(data)                                           ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP1DA_get_int51(data)                                           ((0x00200000&(data))>>21)
#define MIS_UMSK_ISR_GP1DA_int50_shift                                               (20)
#define MIS_UMSK_ISR_GP1DA_int50_mask                                                (0x00100000)
#define MIS_UMSK_ISR_GP1DA_int50(data)                                               (0x00100000&((data)<<20))
#define MIS_UMSK_ISR_GP1DA_int50_src(data)                                           ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP1DA_get_int50(data)                                           ((0x00100000&(data))>>20)
#define MIS_UMSK_ISR_GP1DA_int49_shift                                               (19)
#define MIS_UMSK_ISR_GP1DA_int49_mask                                                (0x00080000)
#define MIS_UMSK_ISR_GP1DA_int49(data)                                               (0x00080000&((data)<<19))
#define MIS_UMSK_ISR_GP1DA_int49_src(data)                                           ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP1DA_get_int49(data)                                           ((0x00080000&(data))>>19)
#define MIS_UMSK_ISR_GP1DA_int48_shift                                               (18)
#define MIS_UMSK_ISR_GP1DA_int48_mask                                                (0x00040000)
#define MIS_UMSK_ISR_GP1DA_int48(data)                                               (0x00040000&((data)<<18))
#define MIS_UMSK_ISR_GP1DA_int48_src(data)                                           ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP1DA_get_int48(data)                                           ((0x00040000&(data))>>18)
#define MIS_UMSK_ISR_GP1DA_int47_shift                                               (17)
#define MIS_UMSK_ISR_GP1DA_int47_mask                                                (0x00020000)
#define MIS_UMSK_ISR_GP1DA_int47(data)                                               (0x00020000&((data)<<17))
#define MIS_UMSK_ISR_GP1DA_int47_src(data)                                           ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP1DA_get_int47(data)                                           ((0x00020000&(data))>>17)
#define MIS_UMSK_ISR_GP1DA_int46_shift                                               (16)
#define MIS_UMSK_ISR_GP1DA_int46_mask                                                (0x00010000)
#define MIS_UMSK_ISR_GP1DA_int46(data)                                               (0x00010000&((data)<<16))
#define MIS_UMSK_ISR_GP1DA_int46_src(data)                                           ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP1DA_get_int46(data)                                           ((0x00010000&(data))>>16)
#define MIS_UMSK_ISR_GP1DA_int45_shift                                               (15)
#define MIS_UMSK_ISR_GP1DA_int45_mask                                                (0x00008000)
#define MIS_UMSK_ISR_GP1DA_int45(data)                                               (0x00008000&((data)<<15))
#define MIS_UMSK_ISR_GP1DA_int45_src(data)                                           ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP1DA_get_int45(data)                                           ((0x00008000&(data))>>15)
#define MIS_UMSK_ISR_GP1DA_int44_shift                                               (14)
#define MIS_UMSK_ISR_GP1DA_int44_mask                                                (0x00004000)
#define MIS_UMSK_ISR_GP1DA_int44(data)                                               (0x00004000&((data)<<14))
#define MIS_UMSK_ISR_GP1DA_int44_src(data)                                           ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP1DA_get_int44(data)                                           ((0x00004000&(data))>>14)
#define MIS_UMSK_ISR_GP1DA_int43_shift                                               (13)
#define MIS_UMSK_ISR_GP1DA_int43_mask                                                (0x00002000)
#define MIS_UMSK_ISR_GP1DA_int43(data)                                               (0x00002000&((data)<<13))
#define MIS_UMSK_ISR_GP1DA_int43_src(data)                                           ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP1DA_get_int43(data)                                           ((0x00002000&(data))>>13)
#define MIS_UMSK_ISR_GP1DA_int42_shift                                               (12)
#define MIS_UMSK_ISR_GP1DA_int42_mask                                                (0x00001000)
#define MIS_UMSK_ISR_GP1DA_int42(data)                                               (0x00001000&((data)<<12))
#define MIS_UMSK_ISR_GP1DA_int42_src(data)                                           ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP1DA_get_int42(data)                                           ((0x00001000&(data))>>12)
#define MIS_UMSK_ISR_GP1DA_int41_shift                                               (11)
#define MIS_UMSK_ISR_GP1DA_int41_mask                                                (0x00000800)
#define MIS_UMSK_ISR_GP1DA_int41(data)                                               (0x00000800&((data)<<11))
#define MIS_UMSK_ISR_GP1DA_int41_src(data)                                           ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP1DA_get_int41(data)                                           ((0x00000800&(data))>>11)
#define MIS_UMSK_ISR_GP1DA_int40_shift                                               (10)
#define MIS_UMSK_ISR_GP1DA_int40_mask                                                (0x00000400)
#define MIS_UMSK_ISR_GP1DA_int40(data)                                               (0x00000400&((data)<<10))
#define MIS_UMSK_ISR_GP1DA_int40_src(data)                                           ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP1DA_get_int40(data)                                           ((0x00000400&(data))>>10)
#define MIS_UMSK_ISR_GP1DA_int39_shift                                               (9)
#define MIS_UMSK_ISR_GP1DA_int39_mask                                                (0x00000200)
#define MIS_UMSK_ISR_GP1DA_int39(data)                                               (0x00000200&((data)<<9))
#define MIS_UMSK_ISR_GP1DA_int39_src(data)                                           ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP1DA_get_int39(data)                                           ((0x00000200&(data))>>9)
#define MIS_UMSK_ISR_GP1DA_int38_shift                                               (8)
#define MIS_UMSK_ISR_GP1DA_int38_mask                                                (0x00000100)
#define MIS_UMSK_ISR_GP1DA_int38(data)                                               (0x00000100&((data)<<8))
#define MIS_UMSK_ISR_GP1DA_int38_src(data)                                           ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP1DA_get_int38(data)                                           ((0x00000100&(data))>>8)
#define MIS_UMSK_ISR_GP1DA_int37_shift                                               (7)
#define MIS_UMSK_ISR_GP1DA_int37_mask                                                (0x00000080)
#define MIS_UMSK_ISR_GP1DA_int37(data)                                               (0x00000080&((data)<<7))
#define MIS_UMSK_ISR_GP1DA_int37_src(data)                                           ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP1DA_get_int37(data)                                           ((0x00000080&(data))>>7)
#define MIS_UMSK_ISR_GP1DA_int36_shift                                               (6)
#define MIS_UMSK_ISR_GP1DA_int36_mask                                                (0x00000040)
#define MIS_UMSK_ISR_GP1DA_int36(data)                                               (0x00000040&((data)<<6))
#define MIS_UMSK_ISR_GP1DA_int36_src(data)                                           ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP1DA_get_int36(data)                                           ((0x00000040&(data))>>6)
#define MIS_UMSK_ISR_GP1DA_int35_shift                                               (5)
#define MIS_UMSK_ISR_GP1DA_int35_mask                                                (0x00000020)
#define MIS_UMSK_ISR_GP1DA_int35(data)                                               (0x00000020&((data)<<5))
#define MIS_UMSK_ISR_GP1DA_int35_src(data)                                           ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP1DA_get_int35(data)                                           ((0x00000020&(data))>>5)
#define MIS_UMSK_ISR_GP1DA_int34_shift                                               (4)
#define MIS_UMSK_ISR_GP1DA_int34_mask                                                (0x00000010)
#define MIS_UMSK_ISR_GP1DA_int34(data)                                               (0x00000010&((data)<<4))
#define MIS_UMSK_ISR_GP1DA_int34_src(data)                                           ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP1DA_get_int34(data)                                           ((0x00000010&(data))>>4)
#define MIS_UMSK_ISR_GP1DA_int33_shift                                               (3)
#define MIS_UMSK_ISR_GP1DA_int33_mask                                                (0x00000008)
#define MIS_UMSK_ISR_GP1DA_int33(data)                                               (0x00000008&((data)<<3))
#define MIS_UMSK_ISR_GP1DA_int33_src(data)                                           ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP1DA_get_int33(data)                                           ((0x00000008&(data))>>3)
#define MIS_UMSK_ISR_GP1DA_int32_shift                                               (2)
#define MIS_UMSK_ISR_GP1DA_int32_mask                                                (0x00000004)
#define MIS_UMSK_ISR_GP1DA_int32(data)                                               (0x00000004&((data)<<2))
#define MIS_UMSK_ISR_GP1DA_int32_src(data)                                           ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP1DA_get_int32(data)                                           ((0x00000004&(data))>>2)
#define MIS_UMSK_ISR_GP1DA_int31_shift                                               (1)
#define MIS_UMSK_ISR_GP1DA_int31_mask                                                (0x00000002)
#define MIS_UMSK_ISR_GP1DA_int31(data)                                               (0x00000002&((data)<<1))
#define MIS_UMSK_ISR_GP1DA_int31_src(data)                                           ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP1DA_get_int31(data)                                           ((0x00000002&(data))>>1)
#define MIS_UMSK_ISR_GP1DA_write_data_shift                                          (0)
#define MIS_UMSK_ISR_GP1DA_write_data_mask                                           (0x00000001)
#define MIS_UMSK_ISR_GP1DA_write_data(data)                                          (0x00000001&((data)<<0))
#define MIS_UMSK_ISR_GP1DA_write_data_src(data)                                      ((0x00000001&(data))>>0)
#define MIS_UMSK_ISR_GP1DA_get_write_data(data)                                      ((0x00000001&(data))>>0)


#define MIS_DUMMY1                                                                   0x1801B068
#define MIS_DUMMY1_reg_addr                                                          "0xB801B068"
#define MIS_DUMMY1_reg                                                               0xB801B068
#define set_MIS_DUMMY1_reg(data)   (*((volatile unsigned int*) MIS_DUMMY1_reg)=data)
#define get_MIS_DUMMY1_reg   (*((volatile unsigned int*) MIS_DUMMY1_reg))
#define MIS_DUMMY1_inst_adr                                                          "0x001A"
#define MIS_DUMMY1_inst                                                              0x001A
#define MIS_DUMMY1_write_enable2_shift                                               (31)
#define MIS_DUMMY1_write_enable2_mask                                                (0x80000000)
#define MIS_DUMMY1_write_enable2(data)                                               (0x80000000&((data)<<31))
#define MIS_DUMMY1_write_enable2_src(data)                                           ((0x80000000&(data))>>31)
#define MIS_DUMMY1_get_write_enable2(data)                                           ((0x80000000&(data))>>31)
#define MIS_DUMMY1_rvd2_shift                                                        (16)
#define MIS_DUMMY1_rvd2_mask                                                         (0x7FFF0000)
#define MIS_DUMMY1_rvd2(data)                                                        (0x7FFF0000&((data)<<16))
#define MIS_DUMMY1_rvd2_src(data)                                                    ((0x7FFF0000&(data))>>16)
#define MIS_DUMMY1_get_rvd2(data)                                                    ((0x7FFF0000&(data))>>16)
#define MIS_DUMMY1_write_enable1_shift                                               (15)
#define MIS_DUMMY1_write_enable1_mask                                                (0x00008000)
#define MIS_DUMMY1_write_enable1(data)                                               (0x00008000&((data)<<15))
#define MIS_DUMMY1_write_enable1_src(data)                                           ((0x00008000&(data))>>15)
#define MIS_DUMMY1_get_write_enable1(data)                                           ((0x00008000&(data))>>15)
#define MIS_DUMMY1_rvd1_shift                                                        (0)
#define MIS_DUMMY1_rvd1_mask                                                         (0x00007FFF)
#define MIS_DUMMY1_rvd1(data)                                                        (0x00007FFF&((data)<<0))
#define MIS_DUMMY1_rvd1_src(data)                                                    ((0x00007FFF&(data))>>0)
#define MIS_DUMMY1_get_rvd1(data)                                                    ((0x00007FFF&(data))>>0)


#define MIS_UR_CTRL                                                                  0x1801B06C
#define MIS_UR_CTRL_reg_addr                                                         "0xB801B06C"
#define MIS_UR_CTRL_reg                                                              0xB801B06C
#define set_MIS_UR_CTRL_reg(data)   (*((volatile unsigned int*) MIS_UR_CTRL_reg)=data)
#define get_MIS_UR_CTRL_reg   (*((volatile unsigned int*) MIS_UR_CTRL_reg))
#define MIS_UR_CTRL_inst_adr                                                         "0x001B"
#define MIS_UR_CTRL_inst                                                             0x001B
#define MIS_UR_CTRL_rvd3_shift                                                       (29)
#define MIS_UR_CTRL_rvd3_mask                                                        (0xE0000000)
#define MIS_UR_CTRL_rvd3(data)                                                       (0xE0000000&((data)<<29))
#define MIS_UR_CTRL_rvd3_src(data)                                                   ((0xE0000000&(data))>>29)
#define MIS_UR_CTRL_get_rvd3(data)                                                   ((0xE0000000&(data))>>29)
#define MIS_UR_CTRL_to_len_shift                                                     (20)
#define MIS_UR_CTRL_to_len_mask                                                      (0x0FF00000)
#define MIS_UR_CTRL_to_len(data)                                                     (0x0FF00000&((data)<<20))
#define MIS_UR_CTRL_to_len_src(data)                                                 ((0x0FF00000&(data))>>20)
#define MIS_UR_CTRL_get_to_len(data)                                                 ((0x0FF00000&(data))>>20)
#define MIS_UR_CTRL_to_int_en_shift                                                  (19)
#define MIS_UR_CTRL_to_int_en_mask                                                   (0x00080000)
#define MIS_UR_CTRL_to_int_en(data)                                                  (0x00080000&((data)<<19))
#define MIS_UR_CTRL_to_int_en_src(data)                                              ((0x00080000&(data))>>19)
#define MIS_UR_CTRL_get_to_int_en(data)                                              ((0x00080000&(data))>>19)
#define MIS_UR_CTRL_toauareq_shift                                                   (18)
#define MIS_UR_CTRL_toauareq_mask                                                    (0x00040000)
#define MIS_UR_CTRL_toauareq(data)                                                   (0x00040000&((data)<<18))
#define MIS_UR_CTRL_toauareq_src(data)                                               ((0x00040000&(data))>>18)
#define MIS_UR_CTRL_get_toauareq(data)                                               ((0x00040000&(data))>>18)
#define MIS_UR_CTRL_flow_pol_shift                                                   (17)
#define MIS_UR_CTRL_flow_pol_mask                                                    (0x00020000)
#define MIS_UR_CTRL_flow_pol(data)                                                   (0x00020000&((data)<<17))
#define MIS_UR_CTRL_flow_pol_src(data)                                               ((0x00020000&(data))>>17)
#define MIS_UR_CTRL_get_flow_pol(data)                                               ((0x00020000&(data))>>17)
#define MIS_UR_CTRL_mdifen_shift                                                     (16)
#define MIS_UR_CTRL_mdifen_mask                                                      (0x00010000)
#define MIS_UR_CTRL_mdifen(data)                                                     (0x00010000&((data)<<16))
#define MIS_UR_CTRL_mdifen_src(data)                                                 ((0x00010000&(data))>>16)
#define MIS_UR_CTRL_get_mdifen(data)                                                 ((0x00010000&(data))>>16)
#define MIS_UR_CTRL_txempthr_shift                                                   (8)
#define MIS_UR_CTRL_txempthr_mask                                                    (0x00003F00)
#define MIS_UR_CTRL_txempthr(data)                                                   (0x00003F00&((data)<<8))
#define MIS_UR_CTRL_txempthr_src(data)                                               ((0x00003F00&(data))>>8)
#define MIS_UR_CTRL_get_txempthr(data)                                               ((0x00003F00&(data))>>8)
#define MIS_UR_CTRL_rxfulthr_shift                                                   (0)
#define MIS_UR_CTRL_rxfulthr_mask                                                    (0x0000003F)
#define MIS_UR_CTRL_rxfulthr(data)                                                   (0x0000003F&((data)<<0))
#define MIS_UR_CTRL_rxfulthr_src(data)                                               ((0x0000003F&(data))>>0)
#define MIS_UR_CTRL_get_rxfulthr(data)                                               ((0x0000003F&(data))>>0)


#define MIS_FAST_ISR_GPIO0_A                                                         0x1801B070
#define MIS_FAST_ISR_GPIO0_A_reg_addr                                                "0xB801B070"
#define MIS_FAST_ISR_GPIO0_A_reg                                                     0xB801B070
#define set_MIS_FAST_ISR_GPIO0_A_reg(data)   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO0_A_reg)=data)
#define get_MIS_FAST_ISR_GPIO0_A_reg   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO0_A_reg))
#define MIS_FAST_ISR_GPIO0_A_inst_adr                                                "0x001C"
#define MIS_FAST_ISR_GPIO0_A_inst                                                    0x001C
#define MIS_FAST_ISR_GPIO0_A_int_30_shift                                            (31)
#define MIS_FAST_ISR_GPIO0_A_int_30_mask                                             (0x80000000)
#define MIS_FAST_ISR_GPIO0_A_int_30(data)                                            (0x80000000&((data)<<31))
#define MIS_FAST_ISR_GPIO0_A_int_30_src(data)                                        ((0x80000000&(data))>>31)
#define MIS_FAST_ISR_GPIO0_A_get_int_30(data)                                        ((0x80000000&(data))>>31)
#define MIS_FAST_ISR_GPIO0_A_int_29_shift                                            (30)
#define MIS_FAST_ISR_GPIO0_A_int_29_mask                                             (0x40000000)
#define MIS_FAST_ISR_GPIO0_A_int_29(data)                                            (0x40000000&((data)<<30))
#define MIS_FAST_ISR_GPIO0_A_int_29_src(data)                                        ((0x40000000&(data))>>30)
#define MIS_FAST_ISR_GPIO0_A_get_int_29(data)                                        ((0x40000000&(data))>>30)
#define MIS_FAST_ISR_GPIO0_A_int_28_shift                                            (29)
#define MIS_FAST_ISR_GPIO0_A_int_28_mask                                             (0x20000000)
#define MIS_FAST_ISR_GPIO0_A_int_28(data)                                            (0x20000000&((data)<<29))
#define MIS_FAST_ISR_GPIO0_A_int_28_src(data)                                        ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO0_A_get_int_28(data)                                        ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO0_A_int_27_shift                                            (28)
#define MIS_FAST_ISR_GPIO0_A_int_27_mask                                             (0x10000000)
#define MIS_FAST_ISR_GPIO0_A_int_27(data)                                            (0x10000000&((data)<<28))
#define MIS_FAST_ISR_GPIO0_A_int_27_src(data)                                        ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO0_A_get_int_27(data)                                        ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO0_A_int_26_shift                                            (27)
#define MIS_FAST_ISR_GPIO0_A_int_26_mask                                             (0x08000000)
#define MIS_FAST_ISR_GPIO0_A_int_26(data)                                            (0x08000000&((data)<<27))
#define MIS_FAST_ISR_GPIO0_A_int_26_src(data)                                        ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO0_A_get_int_26(data)                                        ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO0_A_int_25_shift                                            (26)
#define MIS_FAST_ISR_GPIO0_A_int_25_mask                                             (0x04000000)
#define MIS_FAST_ISR_GPIO0_A_int_25(data)                                            (0x04000000&((data)<<26))
#define MIS_FAST_ISR_GPIO0_A_int_25_src(data)                                        ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO0_A_get_int_25(data)                                        ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO0_A_int_24_shift                                            (25)
#define MIS_FAST_ISR_GPIO0_A_int_24_mask                                             (0x02000000)
#define MIS_FAST_ISR_GPIO0_A_int_24(data)                                            (0x02000000&((data)<<25))
#define MIS_FAST_ISR_GPIO0_A_int_24_src(data)                                        ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO0_A_get_int_24(data)                                        ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO0_A_int_23_shift                                            (24)
#define MIS_FAST_ISR_GPIO0_A_int_23_mask                                             (0x01000000)
#define MIS_FAST_ISR_GPIO0_A_int_23(data)                                            (0x01000000&((data)<<24))
#define MIS_FAST_ISR_GPIO0_A_int_23_src(data)                                        ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO0_A_get_int_23(data)                                        ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO0_A_int_22_shift                                            (23)
#define MIS_FAST_ISR_GPIO0_A_int_22_mask                                             (0x00800000)
#define MIS_FAST_ISR_GPIO0_A_int_22(data)                                            (0x00800000&((data)<<23))
#define MIS_FAST_ISR_GPIO0_A_int_22_src(data)                                        ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO0_A_get_int_22(data)                                        ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO0_A_int_21_shift                                            (22)
#define MIS_FAST_ISR_GPIO0_A_int_21_mask                                             (0x00400000)
#define MIS_FAST_ISR_GPIO0_A_int_21(data)                                            (0x00400000&((data)<<22))
#define MIS_FAST_ISR_GPIO0_A_int_21_src(data)                                        ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO0_A_get_int_21(data)                                        ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO0_A_int_20_shift                                            (21)
#define MIS_FAST_ISR_GPIO0_A_int_20_mask                                             (0x00200000)
#define MIS_FAST_ISR_GPIO0_A_int_20(data)                                            (0x00200000&((data)<<21))
#define MIS_FAST_ISR_GPIO0_A_int_20_src(data)                                        ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO0_A_get_int_20(data)                                        ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO0_A_int_19_shift                                            (20)
#define MIS_FAST_ISR_GPIO0_A_int_19_mask                                             (0x00100000)
#define MIS_FAST_ISR_GPIO0_A_int_19(data)                                            (0x00100000&((data)<<20))
#define MIS_FAST_ISR_GPIO0_A_int_19_src(data)                                        ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO0_A_get_int_19(data)                                        ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO0_A_int_18_shift                                            (19)
#define MIS_FAST_ISR_GPIO0_A_int_18_mask                                             (0x00080000)
#define MIS_FAST_ISR_GPIO0_A_int_18(data)                                            (0x00080000&((data)<<19))
#define MIS_FAST_ISR_GPIO0_A_int_18_src(data)                                        ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO0_A_get_int_18(data)                                        ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO0_A_int_17_shift                                            (18)
#define MIS_FAST_ISR_GPIO0_A_int_17_mask                                             (0x00040000)
#define MIS_FAST_ISR_GPIO0_A_int_17(data)                                            (0x00040000&((data)<<18))
#define MIS_FAST_ISR_GPIO0_A_int_17_src(data)                                        ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO0_A_get_int_17(data)                                        ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO0_A_int_16_shift                                            (17)
#define MIS_FAST_ISR_GPIO0_A_int_16_mask                                             (0x00020000)
#define MIS_FAST_ISR_GPIO0_A_int_16(data)                                            (0x00020000&((data)<<17))
#define MIS_FAST_ISR_GPIO0_A_int_16_src(data)                                        ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO0_A_get_int_16(data)                                        ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO0_A_int_15_shift                                            (16)
#define MIS_FAST_ISR_GPIO0_A_int_15_mask                                             (0x00010000)
#define MIS_FAST_ISR_GPIO0_A_int_15(data)                                            (0x00010000&((data)<<16))
#define MIS_FAST_ISR_GPIO0_A_int_15_src(data)                                        ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO0_A_get_int_15(data)                                        ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO0_A_int_14_shift                                            (15)
#define MIS_FAST_ISR_GPIO0_A_int_14_mask                                             (0x00008000)
#define MIS_FAST_ISR_GPIO0_A_int_14(data)                                            (0x00008000&((data)<<15))
#define MIS_FAST_ISR_GPIO0_A_int_14_src(data)                                        ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO0_A_get_int_14(data)                                        ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO0_A_int_13_shift                                            (14)
#define MIS_FAST_ISR_GPIO0_A_int_13_mask                                             (0x00004000)
#define MIS_FAST_ISR_GPIO0_A_int_13(data)                                            (0x00004000&((data)<<14))
#define MIS_FAST_ISR_GPIO0_A_int_13_src(data)                                        ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO0_A_get_int_13(data)                                        ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO0_A_int_12_shift                                            (13)
#define MIS_FAST_ISR_GPIO0_A_int_12_mask                                             (0x00002000)
#define MIS_FAST_ISR_GPIO0_A_int_12(data)                                            (0x00002000&((data)<<13))
#define MIS_FAST_ISR_GPIO0_A_int_12_src(data)                                        ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO0_A_get_int_12(data)                                        ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO0_A_int_11_shift                                            (12)
#define MIS_FAST_ISR_GPIO0_A_int_11_mask                                             (0x00001000)
#define MIS_FAST_ISR_GPIO0_A_int_11(data)                                            (0x00001000&((data)<<12))
#define MIS_FAST_ISR_GPIO0_A_int_11_src(data)                                        ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO0_A_get_int_11(data)                                        ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO0_A_int_10_shift                                            (11)
#define MIS_FAST_ISR_GPIO0_A_int_10_mask                                             (0x00000800)
#define MIS_FAST_ISR_GPIO0_A_int_10(data)                                            (0x00000800&((data)<<11))
#define MIS_FAST_ISR_GPIO0_A_int_10_src(data)                                        ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO0_A_get_int_10(data)                                        ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO0_A_int_9_shift                                             (10)
#define MIS_FAST_ISR_GPIO0_A_int_9_mask                                              (0x00000400)
#define MIS_FAST_ISR_GPIO0_A_int_9(data)                                             (0x00000400&((data)<<10))
#define MIS_FAST_ISR_GPIO0_A_int_9_src(data)                                         ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO0_A_get_int_9(data)                                         ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO0_A_int_8_shift                                             (9)
#define MIS_FAST_ISR_GPIO0_A_int_8_mask                                              (0x00000200)
#define MIS_FAST_ISR_GPIO0_A_int_8(data)                                             (0x00000200&((data)<<9))
#define MIS_FAST_ISR_GPIO0_A_int_8_src(data)                                         ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO0_A_get_int_8(data)                                         ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO0_A_int_7_shift                                             (8)
#define MIS_FAST_ISR_GPIO0_A_int_7_mask                                              (0x00000100)
#define MIS_FAST_ISR_GPIO0_A_int_7(data)                                             (0x00000100&((data)<<8))
#define MIS_FAST_ISR_GPIO0_A_int_7_src(data)                                         ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO0_A_get_int_7(data)                                         ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO0_A_int_6_shift                                             (7)
#define MIS_FAST_ISR_GPIO0_A_int_6_mask                                              (0x00000080)
#define MIS_FAST_ISR_GPIO0_A_int_6(data)                                             (0x00000080&((data)<<7))
#define MIS_FAST_ISR_GPIO0_A_int_6_src(data)                                         ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO0_A_get_int_6(data)                                         ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO0_A_int_5_shift                                             (6)
#define MIS_FAST_ISR_GPIO0_A_int_5_mask                                              (0x00000040)
#define MIS_FAST_ISR_GPIO0_A_int_5(data)                                             (0x00000040&((data)<<6))
#define MIS_FAST_ISR_GPIO0_A_int_5_src(data)                                         ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO0_A_get_int_5(data)                                         ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO0_A_int_4_shift                                             (5)
#define MIS_FAST_ISR_GPIO0_A_int_4_mask                                              (0x00000020)
#define MIS_FAST_ISR_GPIO0_A_int_4(data)                                             (0x00000020&((data)<<5))
#define MIS_FAST_ISR_GPIO0_A_int_4_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO0_A_get_int_4(data)                                         ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO0_A_int_3_shift                                             (4)
#define MIS_FAST_ISR_GPIO0_A_int_3_mask                                              (0x00000010)
#define MIS_FAST_ISR_GPIO0_A_int_3(data)                                             (0x00000010&((data)<<4))
#define MIS_FAST_ISR_GPIO0_A_int_3_src(data)                                         ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO0_A_get_int_3(data)                                         ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO0_A_int_2_shift                                             (3)
#define MIS_FAST_ISR_GPIO0_A_int_2_mask                                              (0x00000008)
#define MIS_FAST_ISR_GPIO0_A_int_2(data)                                             (0x00000008&((data)<<3))
#define MIS_FAST_ISR_GPIO0_A_int_2_src(data)                                         ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO0_A_get_int_2(data)                                         ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO0_A_int_1_shift                                             (2)
#define MIS_FAST_ISR_GPIO0_A_int_1_mask                                              (0x00000004)
#define MIS_FAST_ISR_GPIO0_A_int_1(data)                                             (0x00000004&((data)<<2))
#define MIS_FAST_ISR_GPIO0_A_int_1_src(data)                                         ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO0_A_get_int_1(data)                                         ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO0_A_int_0_shift                                             (1)
#define MIS_FAST_ISR_GPIO0_A_int_0_mask                                              (0x00000002)
#define MIS_FAST_ISR_GPIO0_A_int_0(data)                                             (0x00000002&((data)<<1))
#define MIS_FAST_ISR_GPIO0_A_int_0_src(data)                                         ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO0_A_get_int_0(data)                                         ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO0_A_write_data_shift                                        (0)
#define MIS_FAST_ISR_GPIO0_A_write_data_mask                                         (0x00000001)
#define MIS_FAST_ISR_GPIO0_A_write_data(data)                                        (0x00000001&((data)<<0))
#define MIS_FAST_ISR_GPIO0_A_write_data_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_FAST_ISR_GPIO0_A_get_write_data(data)                                    ((0x00000001&(data))>>0)


#define MIS_FAST_ISR_GPIO1_A                                                         0x1801B074
#define MIS_FAST_ISR_GPIO1_A_reg_addr                                                "0xB801B074"
#define MIS_FAST_ISR_GPIO1_A_reg                                                     0xB801B074
#define set_MIS_FAST_ISR_GPIO1_A_reg(data)   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO1_A_reg)=data)
#define get_MIS_FAST_ISR_GPIO1_A_reg   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO1_A_reg))
#define MIS_FAST_ISR_GPIO1_A_inst_adr                                                "0x001D"
#define MIS_FAST_ISR_GPIO1_A_inst                                                    0x001D
#define MIS_FAST_ISR_GPIO1_A_int_59_shift                                            (29)
#define MIS_FAST_ISR_GPIO1_A_int_59_mask                                             (0x20000000)
#define MIS_FAST_ISR_GPIO1_A_int_59(data)                                            (0x20000000&((data)<<29))
#define MIS_FAST_ISR_GPIO1_A_int_59_src(data)                                        ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO1_A_get_int_59(data)                                        ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO1_A_int_58_shift                                            (28)
#define MIS_FAST_ISR_GPIO1_A_int_58_mask                                             (0x10000000)
#define MIS_FAST_ISR_GPIO1_A_int_58(data)                                            (0x10000000&((data)<<28))
#define MIS_FAST_ISR_GPIO1_A_int_58_src(data)                                        ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO1_A_get_int_58(data)                                        ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO1_A_int_57_shift                                            (27)
#define MIS_FAST_ISR_GPIO1_A_int_57_mask                                             (0x08000000)
#define MIS_FAST_ISR_GPIO1_A_int_57(data)                                            (0x08000000&((data)<<27))
#define MIS_FAST_ISR_GPIO1_A_int_57_src(data)                                        ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO1_A_get_int_57(data)                                        ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO1_A_int_56_shift                                            (26)
#define MIS_FAST_ISR_GPIO1_A_int_56_mask                                             (0x04000000)
#define MIS_FAST_ISR_GPIO1_A_int_56(data)                                            (0x04000000&((data)<<26))
#define MIS_FAST_ISR_GPIO1_A_int_56_src(data)                                        ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO1_A_get_int_56(data)                                        ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO1_A_int_55_shift                                            (25)
#define MIS_FAST_ISR_GPIO1_A_int_55_mask                                             (0x02000000)
#define MIS_FAST_ISR_GPIO1_A_int_55(data)                                            (0x02000000&((data)<<25))
#define MIS_FAST_ISR_GPIO1_A_int_55_src(data)                                        ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO1_A_get_int_55(data)                                        ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO1_A_int_54_shift                                            (24)
#define MIS_FAST_ISR_GPIO1_A_int_54_mask                                             (0x01000000)
#define MIS_FAST_ISR_GPIO1_A_int_54(data)                                            (0x01000000&((data)<<24))
#define MIS_FAST_ISR_GPIO1_A_int_54_src(data)                                        ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO1_A_get_int_54(data)                                        ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO1_A_int_53_shift                                            (23)
#define MIS_FAST_ISR_GPIO1_A_int_53_mask                                             (0x00800000)
#define MIS_FAST_ISR_GPIO1_A_int_53(data)                                            (0x00800000&((data)<<23))
#define MIS_FAST_ISR_GPIO1_A_int_53_src(data)                                        ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO1_A_get_int_53(data)                                        ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO1_A_int_52_shift                                            (22)
#define MIS_FAST_ISR_GPIO1_A_int_52_mask                                             (0x00400000)
#define MIS_FAST_ISR_GPIO1_A_int_52(data)                                            (0x00400000&((data)<<22))
#define MIS_FAST_ISR_GPIO1_A_int_52_src(data)                                        ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO1_A_get_int_52(data)                                        ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO1_A_int_51_shift                                            (21)
#define MIS_FAST_ISR_GPIO1_A_int_51_mask                                             (0x00200000)
#define MIS_FAST_ISR_GPIO1_A_int_51(data)                                            (0x00200000&((data)<<21))
#define MIS_FAST_ISR_GPIO1_A_int_51_src(data)                                        ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO1_A_get_int_51(data)                                        ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO1_A_int_50_shift                                            (20)
#define MIS_FAST_ISR_GPIO1_A_int_50_mask                                             (0x00100000)
#define MIS_FAST_ISR_GPIO1_A_int_50(data)                                            (0x00100000&((data)<<20))
#define MIS_FAST_ISR_GPIO1_A_int_50_src(data)                                        ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO1_A_get_int_50(data)                                        ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO1_A_int_49_shift                                            (19)
#define MIS_FAST_ISR_GPIO1_A_int_49_mask                                             (0x00080000)
#define MIS_FAST_ISR_GPIO1_A_int_49(data)                                            (0x00080000&((data)<<19))
#define MIS_FAST_ISR_GPIO1_A_int_49_src(data)                                        ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO1_A_get_int_49(data)                                        ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO1_A_int_48_shift                                            (18)
#define MIS_FAST_ISR_GPIO1_A_int_48_mask                                             (0x00040000)
#define MIS_FAST_ISR_GPIO1_A_int_48(data)                                            (0x00040000&((data)<<18))
#define MIS_FAST_ISR_GPIO1_A_int_48_src(data)                                        ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO1_A_get_int_48(data)                                        ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO1_A_int_47_shift                                            (17)
#define MIS_FAST_ISR_GPIO1_A_int_47_mask                                             (0x00020000)
#define MIS_FAST_ISR_GPIO1_A_int_47(data)                                            (0x00020000&((data)<<17))
#define MIS_FAST_ISR_GPIO1_A_int_47_src(data)                                        ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO1_A_get_int_47(data)                                        ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO1_A_int_46_shift                                            (16)
#define MIS_FAST_ISR_GPIO1_A_int_46_mask                                             (0x00010000)
#define MIS_FAST_ISR_GPIO1_A_int_46(data)                                            (0x00010000&((data)<<16))
#define MIS_FAST_ISR_GPIO1_A_int_46_src(data)                                        ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO1_A_get_int_46(data)                                        ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO1_A_int_45_shift                                            (15)
#define MIS_FAST_ISR_GPIO1_A_int_45_mask                                             (0x00008000)
#define MIS_FAST_ISR_GPIO1_A_int_45(data)                                            (0x00008000&((data)<<15))
#define MIS_FAST_ISR_GPIO1_A_int_45_src(data)                                        ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO1_A_get_int_45(data)                                        ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO1_A_int_44_shift                                            (14)
#define MIS_FAST_ISR_GPIO1_A_int_44_mask                                             (0x00004000)
#define MIS_FAST_ISR_GPIO1_A_int_44(data)                                            (0x00004000&((data)<<14))
#define MIS_FAST_ISR_GPIO1_A_int_44_src(data)                                        ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO1_A_get_int_44(data)                                        ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO1_A_int_43_shift                                            (13)
#define MIS_FAST_ISR_GPIO1_A_int_43_mask                                             (0x00002000)
#define MIS_FAST_ISR_GPIO1_A_int_43(data)                                            (0x00002000&((data)<<13))
#define MIS_FAST_ISR_GPIO1_A_int_43_src(data)                                        ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO1_A_get_int_43(data)                                        ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO1_A_int_42_shift                                            (12)
#define MIS_FAST_ISR_GPIO1_A_int_42_mask                                             (0x00001000)
#define MIS_FAST_ISR_GPIO1_A_int_42(data)                                            (0x00001000&((data)<<12))
#define MIS_FAST_ISR_GPIO1_A_int_42_src(data)                                        ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO1_A_get_int_42(data)                                        ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO1_A_int_41_shift                                            (11)
#define MIS_FAST_ISR_GPIO1_A_int_41_mask                                             (0x00000800)
#define MIS_FAST_ISR_GPIO1_A_int_41(data)                                            (0x00000800&((data)<<11))
#define MIS_FAST_ISR_GPIO1_A_int_41_src(data)                                        ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO1_A_get_int_41(data)                                        ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO1_A_int_40_shift                                            (10)
#define MIS_FAST_ISR_GPIO1_A_int_40_mask                                             (0x00000400)
#define MIS_FAST_ISR_GPIO1_A_int_40(data)                                            (0x00000400&((data)<<10))
#define MIS_FAST_ISR_GPIO1_A_int_40_src(data)                                        ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO1_A_get_int_40(data)                                        ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO1_A_int_39_shift                                            (9)
#define MIS_FAST_ISR_GPIO1_A_int_39_mask                                             (0x00000200)
#define MIS_FAST_ISR_GPIO1_A_int_39(data)                                            (0x00000200&((data)<<9))
#define MIS_FAST_ISR_GPIO1_A_int_39_src(data)                                        ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO1_A_get_int_39(data)                                        ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO1_A_int_38_shift                                            (8)
#define MIS_FAST_ISR_GPIO1_A_int_38_mask                                             (0x00000100)
#define MIS_FAST_ISR_GPIO1_A_int_38(data)                                            (0x00000100&((data)<<8))
#define MIS_FAST_ISR_GPIO1_A_int_38_src(data)                                        ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO1_A_get_int_38(data)                                        ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO1_A_int_37_shift                                            (7)
#define MIS_FAST_ISR_GPIO1_A_int_37_mask                                             (0x00000080)
#define MIS_FAST_ISR_GPIO1_A_int_37(data)                                            (0x00000080&((data)<<7))
#define MIS_FAST_ISR_GPIO1_A_int_37_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO1_A_get_int_37(data)                                        ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO1_A_int_36_shift                                            (6)
#define MIS_FAST_ISR_GPIO1_A_int_36_mask                                             (0x00000040)
#define MIS_FAST_ISR_GPIO1_A_int_36(data)                                            (0x00000040&((data)<<6))
#define MIS_FAST_ISR_GPIO1_A_int_36_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO1_A_get_int_36(data)                                        ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO1_A_int_35_shift                                            (5)
#define MIS_FAST_ISR_GPIO1_A_int_35_mask                                             (0x00000020)
#define MIS_FAST_ISR_GPIO1_A_int_35(data)                                            (0x00000020&((data)<<5))
#define MIS_FAST_ISR_GPIO1_A_int_35_src(data)                                        ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO1_A_get_int_35(data)                                        ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO1_A_int_34_shift                                            (4)
#define MIS_FAST_ISR_GPIO1_A_int_34_mask                                             (0x00000010)
#define MIS_FAST_ISR_GPIO1_A_int_34(data)                                            (0x00000010&((data)<<4))
#define MIS_FAST_ISR_GPIO1_A_int_34_src(data)                                        ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO1_A_get_int_34(data)                                        ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO1_A_int_33_shift                                            (3)
#define MIS_FAST_ISR_GPIO1_A_int_33_mask                                             (0x00000008)
#define MIS_FAST_ISR_GPIO1_A_int_33(data)                                            (0x00000008&((data)<<3))
#define MIS_FAST_ISR_GPIO1_A_int_33_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO1_A_get_int_33(data)                                        ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO1_A_int_32_shift                                            (2)
#define MIS_FAST_ISR_GPIO1_A_int_32_mask                                             (0x00000004)
#define MIS_FAST_ISR_GPIO1_A_int_32(data)                                            (0x00000004&((data)<<2))
#define MIS_FAST_ISR_GPIO1_A_int_32_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO1_A_get_int_32(data)                                        ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO1_A_int_31_shift                                            (1)
#define MIS_FAST_ISR_GPIO1_A_int_31_mask                                             (0x00000002)
#define MIS_FAST_ISR_GPIO1_A_int_31(data)                                            (0x00000002&((data)<<1))
#define MIS_FAST_ISR_GPIO1_A_int_31_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO1_A_get_int_31(data)                                        ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO1_A_write_data_shift                                        (0)
#define MIS_FAST_ISR_GPIO1_A_write_data_mask                                         (0x00000001)
#define MIS_FAST_ISR_GPIO1_A_write_data(data)                                        (0x00000001&((data)<<0))
#define MIS_FAST_ISR_GPIO1_A_write_data_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_FAST_ISR_GPIO1_A_get_write_data(data)                                    ((0x00000001&(data))>>0)


#define MIS_FAST_ISR_GPIO0_DA                                                        0x1801B078
#define MIS_FAST_ISR_GPIO0_DA_reg_addr                                               "0xB801B078"
#define MIS_FAST_ISR_GPIO0_DA_reg                                                    0xB801B078
#define set_MIS_FAST_ISR_GPIO0_DA_reg(data)   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO0_DA_reg)=data)
#define get_MIS_FAST_ISR_GPIO0_DA_reg   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO0_DA_reg))
#define MIS_FAST_ISR_GPIO0_DA_inst_adr                                               "0x001E"
#define MIS_FAST_ISR_GPIO0_DA_inst                                                   0x001E
#define MIS_FAST_ISR_GPIO0_DA_int_30_shift                                           (31)
#define MIS_FAST_ISR_GPIO0_DA_int_30_mask                                            (0x80000000)
#define MIS_FAST_ISR_GPIO0_DA_int_30(data)                                           (0x80000000&((data)<<31))
#define MIS_FAST_ISR_GPIO0_DA_int_30_src(data)                                       ((0x80000000&(data))>>31)
#define MIS_FAST_ISR_GPIO0_DA_get_int_30(data)                                       ((0x80000000&(data))>>31)
#define MIS_FAST_ISR_GPIO0_DA_int_29_shift                                           (30)
#define MIS_FAST_ISR_GPIO0_DA_int_29_mask                                            (0x40000000)
#define MIS_FAST_ISR_GPIO0_DA_int_29(data)                                           (0x40000000&((data)<<30))
#define MIS_FAST_ISR_GPIO0_DA_int_29_src(data)                                       ((0x40000000&(data))>>30)
#define MIS_FAST_ISR_GPIO0_DA_get_int_29(data)                                       ((0x40000000&(data))>>30)
#define MIS_FAST_ISR_GPIO0_DA_int_28_shift                                           (29)
#define MIS_FAST_ISR_GPIO0_DA_int_28_mask                                            (0x20000000)
#define MIS_FAST_ISR_GPIO0_DA_int_28(data)                                           (0x20000000&((data)<<29))
#define MIS_FAST_ISR_GPIO0_DA_int_28_src(data)                                       ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO0_DA_get_int_28(data)                                       ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO0_DA_int_27_shift                                           (28)
#define MIS_FAST_ISR_GPIO0_DA_int_27_mask                                            (0x10000000)
#define MIS_FAST_ISR_GPIO0_DA_int_27(data)                                           (0x10000000&((data)<<28))
#define MIS_FAST_ISR_GPIO0_DA_int_27_src(data)                                       ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO0_DA_get_int_27(data)                                       ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO0_DA_int_26_shift                                           (27)
#define MIS_FAST_ISR_GPIO0_DA_int_26_mask                                            (0x08000000)
#define MIS_FAST_ISR_GPIO0_DA_int_26(data)                                           (0x08000000&((data)<<27))
#define MIS_FAST_ISR_GPIO0_DA_int_26_src(data)                                       ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO0_DA_get_int_26(data)                                       ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO0_DA_int_25_shift                                           (26)
#define MIS_FAST_ISR_GPIO0_DA_int_25_mask                                            (0x04000000)
#define MIS_FAST_ISR_GPIO0_DA_int_25(data)                                           (0x04000000&((data)<<26))
#define MIS_FAST_ISR_GPIO0_DA_int_25_src(data)                                       ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO0_DA_get_int_25(data)                                       ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO0_DA_int_24_shift                                           (25)
#define MIS_FAST_ISR_GPIO0_DA_int_24_mask                                            (0x02000000)
#define MIS_FAST_ISR_GPIO0_DA_int_24(data)                                           (0x02000000&((data)<<25))
#define MIS_FAST_ISR_GPIO0_DA_int_24_src(data)                                       ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO0_DA_get_int_24(data)                                       ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO0_DA_int_23_shift                                           (24)
#define MIS_FAST_ISR_GPIO0_DA_int_23_mask                                            (0x01000000)
#define MIS_FAST_ISR_GPIO0_DA_int_23(data)                                           (0x01000000&((data)<<24))
#define MIS_FAST_ISR_GPIO0_DA_int_23_src(data)                                       ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO0_DA_get_int_23(data)                                       ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO0_DA_int_22_shift                                           (23)
#define MIS_FAST_ISR_GPIO0_DA_int_22_mask                                            (0x00800000)
#define MIS_FAST_ISR_GPIO0_DA_int_22(data)                                           (0x00800000&((data)<<23))
#define MIS_FAST_ISR_GPIO0_DA_int_22_src(data)                                       ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO0_DA_get_int_22(data)                                       ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO0_DA_int_21_shift                                           (22)
#define MIS_FAST_ISR_GPIO0_DA_int_21_mask                                            (0x00400000)
#define MIS_FAST_ISR_GPIO0_DA_int_21(data)                                           (0x00400000&((data)<<22))
#define MIS_FAST_ISR_GPIO0_DA_int_21_src(data)                                       ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO0_DA_get_int_21(data)                                       ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO0_DA_int_20_shift                                           (21)
#define MIS_FAST_ISR_GPIO0_DA_int_20_mask                                            (0x00200000)
#define MIS_FAST_ISR_GPIO0_DA_int_20(data)                                           (0x00200000&((data)<<21))
#define MIS_FAST_ISR_GPIO0_DA_int_20_src(data)                                       ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO0_DA_get_int_20(data)                                       ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO0_DA_int_19_shift                                           (20)
#define MIS_FAST_ISR_GPIO0_DA_int_19_mask                                            (0x00100000)
#define MIS_FAST_ISR_GPIO0_DA_int_19(data)                                           (0x00100000&((data)<<20))
#define MIS_FAST_ISR_GPIO0_DA_int_19_src(data)                                       ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO0_DA_get_int_19(data)                                       ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO0_DA_int_18_shift                                           (19)
#define MIS_FAST_ISR_GPIO0_DA_int_18_mask                                            (0x00080000)
#define MIS_FAST_ISR_GPIO0_DA_int_18(data)                                           (0x00080000&((data)<<19))
#define MIS_FAST_ISR_GPIO0_DA_int_18_src(data)                                       ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO0_DA_get_int_18(data)                                       ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO0_DA_int_17_shift                                           (18)
#define MIS_FAST_ISR_GPIO0_DA_int_17_mask                                            (0x00040000)
#define MIS_FAST_ISR_GPIO0_DA_int_17(data)                                           (0x00040000&((data)<<18))
#define MIS_FAST_ISR_GPIO0_DA_int_17_src(data)                                       ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO0_DA_get_int_17(data)                                       ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO0_DA_int_16_shift                                           (17)
#define MIS_FAST_ISR_GPIO0_DA_int_16_mask                                            (0x00020000)
#define MIS_FAST_ISR_GPIO0_DA_int_16(data)                                           (0x00020000&((data)<<17))
#define MIS_FAST_ISR_GPIO0_DA_int_16_src(data)                                       ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO0_DA_get_int_16(data)                                       ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO0_DA_int_15_shift                                           (16)
#define MIS_FAST_ISR_GPIO0_DA_int_15_mask                                            (0x00010000)
#define MIS_FAST_ISR_GPIO0_DA_int_15(data)                                           (0x00010000&((data)<<16))
#define MIS_FAST_ISR_GPIO0_DA_int_15_src(data)                                       ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO0_DA_get_int_15(data)                                       ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO0_DA_int_14_shift                                           (15)
#define MIS_FAST_ISR_GPIO0_DA_int_14_mask                                            (0x00008000)
#define MIS_FAST_ISR_GPIO0_DA_int_14(data)                                           (0x00008000&((data)<<15))
#define MIS_FAST_ISR_GPIO0_DA_int_14_src(data)                                       ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO0_DA_get_int_14(data)                                       ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO0_DA_int_13_shift                                           (14)
#define MIS_FAST_ISR_GPIO0_DA_int_13_mask                                            (0x00004000)
#define MIS_FAST_ISR_GPIO0_DA_int_13(data)                                           (0x00004000&((data)<<14))
#define MIS_FAST_ISR_GPIO0_DA_int_13_src(data)                                       ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO0_DA_get_int_13(data)                                       ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO0_DA_int_12_shift                                           (13)
#define MIS_FAST_ISR_GPIO0_DA_int_12_mask                                            (0x00002000)
#define MIS_FAST_ISR_GPIO0_DA_int_12(data)                                           (0x00002000&((data)<<13))
#define MIS_FAST_ISR_GPIO0_DA_int_12_src(data)                                       ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO0_DA_get_int_12(data)                                       ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO0_DA_int_11_shift                                           (12)
#define MIS_FAST_ISR_GPIO0_DA_int_11_mask                                            (0x00001000)
#define MIS_FAST_ISR_GPIO0_DA_int_11(data)                                           (0x00001000&((data)<<12))
#define MIS_FAST_ISR_GPIO0_DA_int_11_src(data)                                       ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO0_DA_get_int_11(data)                                       ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO0_DA_int_10_shift                                           (11)
#define MIS_FAST_ISR_GPIO0_DA_int_10_mask                                            (0x00000800)
#define MIS_FAST_ISR_GPIO0_DA_int_10(data)                                           (0x00000800&((data)<<11))
#define MIS_FAST_ISR_GPIO0_DA_int_10_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO0_DA_get_int_10(data)                                       ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO0_DA_int_9_shift                                            (10)
#define MIS_FAST_ISR_GPIO0_DA_int_9_mask                                             (0x00000400)
#define MIS_FAST_ISR_GPIO0_DA_int_9(data)                                            (0x00000400&((data)<<10))
#define MIS_FAST_ISR_GPIO0_DA_int_9_src(data)                                        ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO0_DA_get_int_9(data)                                        ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO0_DA_int_8_shift                                            (9)
#define MIS_FAST_ISR_GPIO0_DA_int_8_mask                                             (0x00000200)
#define MIS_FAST_ISR_GPIO0_DA_int_8(data)                                            (0x00000200&((data)<<9))
#define MIS_FAST_ISR_GPIO0_DA_int_8_src(data)                                        ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO0_DA_get_int_8(data)                                        ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO0_DA_int_7_shift                                            (8)
#define MIS_FAST_ISR_GPIO0_DA_int_7_mask                                             (0x00000100)
#define MIS_FAST_ISR_GPIO0_DA_int_7(data)                                            (0x00000100&((data)<<8))
#define MIS_FAST_ISR_GPIO0_DA_int_7_src(data)                                        ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO0_DA_get_int_7(data)                                        ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO0_DA_int_6_shift                                            (7)
#define MIS_FAST_ISR_GPIO0_DA_int_6_mask                                             (0x00000080)
#define MIS_FAST_ISR_GPIO0_DA_int_6(data)                                            (0x00000080&((data)<<7))
#define MIS_FAST_ISR_GPIO0_DA_int_6_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO0_DA_get_int_6(data)                                        ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO0_DA_int_5_shift                                            (6)
#define MIS_FAST_ISR_GPIO0_DA_int_5_mask                                             (0x00000040)
#define MIS_FAST_ISR_GPIO0_DA_int_5(data)                                            (0x00000040&((data)<<6))
#define MIS_FAST_ISR_GPIO0_DA_int_5_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO0_DA_get_int_5(data)                                        ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO0_DA_int_4_shift                                            (5)
#define MIS_FAST_ISR_GPIO0_DA_int_4_mask                                             (0x00000020)
#define MIS_FAST_ISR_GPIO0_DA_int_4(data)                                            (0x00000020&((data)<<5))
#define MIS_FAST_ISR_GPIO0_DA_int_4_src(data)                                        ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO0_DA_get_int_4(data)                                        ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO0_DA_int_3_shift                                            (4)
#define MIS_FAST_ISR_GPIO0_DA_int_3_mask                                             (0x00000010)
#define MIS_FAST_ISR_GPIO0_DA_int_3(data)                                            (0x00000010&((data)<<4))
#define MIS_FAST_ISR_GPIO0_DA_int_3_src(data)                                        ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO0_DA_get_int_3(data)                                        ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO0_DA_int_2_shift                                            (3)
#define MIS_FAST_ISR_GPIO0_DA_int_2_mask                                             (0x00000008)
#define MIS_FAST_ISR_GPIO0_DA_int_2(data)                                            (0x00000008&((data)<<3))
#define MIS_FAST_ISR_GPIO0_DA_int_2_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO0_DA_get_int_2(data)                                        ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO0_DA_int_1_shift                                            (2)
#define MIS_FAST_ISR_GPIO0_DA_int_1_mask                                             (0x00000004)
#define MIS_FAST_ISR_GPIO0_DA_int_1(data)                                            (0x00000004&((data)<<2))
#define MIS_FAST_ISR_GPIO0_DA_int_1_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO0_DA_get_int_1(data)                                        ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO0_DA_int_0_shift                                            (1)
#define MIS_FAST_ISR_GPIO0_DA_int_0_mask                                             (0x00000002)
#define MIS_FAST_ISR_GPIO0_DA_int_0(data)                                            (0x00000002&((data)<<1))
#define MIS_FAST_ISR_GPIO0_DA_int_0_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO0_DA_get_int_0(data)                                        ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO0_DA_write_data_shift                                       (0)
#define MIS_FAST_ISR_GPIO0_DA_write_data_mask                                        (0x00000001)
#define MIS_FAST_ISR_GPIO0_DA_write_data(data)                                       (0x00000001&((data)<<0))
#define MIS_FAST_ISR_GPIO0_DA_write_data_src(data)                                   ((0x00000001&(data))>>0)
#define MIS_FAST_ISR_GPIO0_DA_get_write_data(data)                                   ((0x00000001&(data))>>0)


#define MIS_FAST_ISR_GPIO1_DA                                                        0x1801B07C
#define MIS_FAST_ISR_GPIO1_DA_reg_addr                                               "0xB801B07C"
#define MIS_FAST_ISR_GPIO1_DA_reg                                                    0xB801B07C
#define set_MIS_FAST_ISR_GPIO1_DA_reg(data)   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO1_DA_reg)=data)
#define get_MIS_FAST_ISR_GPIO1_DA_reg   (*((volatile unsigned int*) MIS_FAST_ISR_GPIO1_DA_reg))
#define MIS_FAST_ISR_GPIO1_DA_inst_adr                                               "0x001F"
#define MIS_FAST_ISR_GPIO1_DA_inst                                                   0x001F
#define MIS_FAST_ISR_GPIO1_DA_int_59_shift                                           (29)
#define MIS_FAST_ISR_GPIO1_DA_int_59_mask                                            (0x20000000)
#define MIS_FAST_ISR_GPIO1_DA_int_59(data)                                           (0x20000000&((data)<<29))
#define MIS_FAST_ISR_GPIO1_DA_int_59_src(data)                                       ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO1_DA_get_int_59(data)                                       ((0x20000000&(data))>>29)
#define MIS_FAST_ISR_GPIO1_DA_int_58_shift                                           (28)
#define MIS_FAST_ISR_GPIO1_DA_int_58_mask                                            (0x10000000)
#define MIS_FAST_ISR_GPIO1_DA_int_58(data)                                           (0x10000000&((data)<<28))
#define MIS_FAST_ISR_GPIO1_DA_int_58_src(data)                                       ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO1_DA_get_int_58(data)                                       ((0x10000000&(data))>>28)
#define MIS_FAST_ISR_GPIO1_DA_int_57_shift                                           (27)
#define MIS_FAST_ISR_GPIO1_DA_int_57_mask                                            (0x08000000)
#define MIS_FAST_ISR_GPIO1_DA_int_57(data)                                           (0x08000000&((data)<<27))
#define MIS_FAST_ISR_GPIO1_DA_int_57_src(data)                                       ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO1_DA_get_int_57(data)                                       ((0x08000000&(data))>>27)
#define MIS_FAST_ISR_GPIO1_DA_int_56_shift                                           (26)
#define MIS_FAST_ISR_GPIO1_DA_int_56_mask                                            (0x04000000)
#define MIS_FAST_ISR_GPIO1_DA_int_56(data)                                           (0x04000000&((data)<<26))
#define MIS_FAST_ISR_GPIO1_DA_int_56_src(data)                                       ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO1_DA_get_int_56(data)                                       ((0x04000000&(data))>>26)
#define MIS_FAST_ISR_GPIO1_DA_int_55_shift                                           (25)
#define MIS_FAST_ISR_GPIO1_DA_int_55_mask                                            (0x02000000)
#define MIS_FAST_ISR_GPIO1_DA_int_55(data)                                           (0x02000000&((data)<<25))
#define MIS_FAST_ISR_GPIO1_DA_int_55_src(data)                                       ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO1_DA_get_int_55(data)                                       ((0x02000000&(data))>>25)
#define MIS_FAST_ISR_GPIO1_DA_int_54_shift                                           (24)
#define MIS_FAST_ISR_GPIO1_DA_int_54_mask                                            (0x01000000)
#define MIS_FAST_ISR_GPIO1_DA_int_54(data)                                           (0x01000000&((data)<<24))
#define MIS_FAST_ISR_GPIO1_DA_int_54_src(data)                                       ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO1_DA_get_int_54(data)                                       ((0x01000000&(data))>>24)
#define MIS_FAST_ISR_GPIO1_DA_int_53_shift                                           (23)
#define MIS_FAST_ISR_GPIO1_DA_int_53_mask                                            (0x00800000)
#define MIS_FAST_ISR_GPIO1_DA_int_53(data)                                           (0x00800000&((data)<<23))
#define MIS_FAST_ISR_GPIO1_DA_int_53_src(data)                                       ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO1_DA_get_int_53(data)                                       ((0x00800000&(data))>>23)
#define MIS_FAST_ISR_GPIO1_DA_int_52_shift                                           (22)
#define MIS_FAST_ISR_GPIO1_DA_int_52_mask                                            (0x00400000)
#define MIS_FAST_ISR_GPIO1_DA_int_52(data)                                           (0x00400000&((data)<<22))
#define MIS_FAST_ISR_GPIO1_DA_int_52_src(data)                                       ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO1_DA_get_int_52(data)                                       ((0x00400000&(data))>>22)
#define MIS_FAST_ISR_GPIO1_DA_int_51_shift                                           (21)
#define MIS_FAST_ISR_GPIO1_DA_int_51_mask                                            (0x00200000)
#define MIS_FAST_ISR_GPIO1_DA_int_51(data)                                           (0x00200000&((data)<<21))
#define MIS_FAST_ISR_GPIO1_DA_int_51_src(data)                                       ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO1_DA_get_int_51(data)                                       ((0x00200000&(data))>>21)
#define MIS_FAST_ISR_GPIO1_DA_int_50_shift                                           (20)
#define MIS_FAST_ISR_GPIO1_DA_int_50_mask                                            (0x00100000)
#define MIS_FAST_ISR_GPIO1_DA_int_50(data)                                           (0x00100000&((data)<<20))
#define MIS_FAST_ISR_GPIO1_DA_int_50_src(data)                                       ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO1_DA_get_int_50(data)                                       ((0x00100000&(data))>>20)
#define MIS_FAST_ISR_GPIO1_DA_int_49_shift                                           (19)
#define MIS_FAST_ISR_GPIO1_DA_int_49_mask                                            (0x00080000)
#define MIS_FAST_ISR_GPIO1_DA_int_49(data)                                           (0x00080000&((data)<<19))
#define MIS_FAST_ISR_GPIO1_DA_int_49_src(data)                                       ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO1_DA_get_int_49(data)                                       ((0x00080000&(data))>>19)
#define MIS_FAST_ISR_GPIO1_DA_int_48_shift                                           (18)
#define MIS_FAST_ISR_GPIO1_DA_int_48_mask                                            (0x00040000)
#define MIS_FAST_ISR_GPIO1_DA_int_48(data)                                           (0x00040000&((data)<<18))
#define MIS_FAST_ISR_GPIO1_DA_int_48_src(data)                                       ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO1_DA_get_int_48(data)                                       ((0x00040000&(data))>>18)
#define MIS_FAST_ISR_GPIO1_DA_int_47_shift                                           (17)
#define MIS_FAST_ISR_GPIO1_DA_int_47_mask                                            (0x00020000)
#define MIS_FAST_ISR_GPIO1_DA_int_47(data)                                           (0x00020000&((data)<<17))
#define MIS_FAST_ISR_GPIO1_DA_int_47_src(data)                                       ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO1_DA_get_int_47(data)                                       ((0x00020000&(data))>>17)
#define MIS_FAST_ISR_GPIO1_DA_int_46_shift                                           (16)
#define MIS_FAST_ISR_GPIO1_DA_int_46_mask                                            (0x00010000)
#define MIS_FAST_ISR_GPIO1_DA_int_46(data)                                           (0x00010000&((data)<<16))
#define MIS_FAST_ISR_GPIO1_DA_int_46_src(data)                                       ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO1_DA_get_int_46(data)                                       ((0x00010000&(data))>>16)
#define MIS_FAST_ISR_GPIO1_DA_int_45_shift                                           (15)
#define MIS_FAST_ISR_GPIO1_DA_int_45_mask                                            (0x00008000)
#define MIS_FAST_ISR_GPIO1_DA_int_45(data)                                           (0x00008000&((data)<<15))
#define MIS_FAST_ISR_GPIO1_DA_int_45_src(data)                                       ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO1_DA_get_int_45(data)                                       ((0x00008000&(data))>>15)
#define MIS_FAST_ISR_GPIO1_DA_int_44_shift                                           (14)
#define MIS_FAST_ISR_GPIO1_DA_int_44_mask                                            (0x00004000)
#define MIS_FAST_ISR_GPIO1_DA_int_44(data)                                           (0x00004000&((data)<<14))
#define MIS_FAST_ISR_GPIO1_DA_int_44_src(data)                                       ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO1_DA_get_int_44(data)                                       ((0x00004000&(data))>>14)
#define MIS_FAST_ISR_GPIO1_DA_int_43_shift                                           (13)
#define MIS_FAST_ISR_GPIO1_DA_int_43_mask                                            (0x00002000)
#define MIS_FAST_ISR_GPIO1_DA_int_43(data)                                           (0x00002000&((data)<<13))
#define MIS_FAST_ISR_GPIO1_DA_int_43_src(data)                                       ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO1_DA_get_int_43(data)                                       ((0x00002000&(data))>>13)
#define MIS_FAST_ISR_GPIO1_DA_int_42_shift                                           (12)
#define MIS_FAST_ISR_GPIO1_DA_int_42_mask                                            (0x00001000)
#define MIS_FAST_ISR_GPIO1_DA_int_42(data)                                           (0x00001000&((data)<<12))
#define MIS_FAST_ISR_GPIO1_DA_int_42_src(data)                                       ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO1_DA_get_int_42(data)                                       ((0x00001000&(data))>>12)
#define MIS_FAST_ISR_GPIO1_DA_int_41_shift                                           (11)
#define MIS_FAST_ISR_GPIO1_DA_int_41_mask                                            (0x00000800)
#define MIS_FAST_ISR_GPIO1_DA_int_41(data)                                           (0x00000800&((data)<<11))
#define MIS_FAST_ISR_GPIO1_DA_int_41_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO1_DA_get_int_41(data)                                       ((0x00000800&(data))>>11)
#define MIS_FAST_ISR_GPIO1_DA_int_40_shift                                           (10)
#define MIS_FAST_ISR_GPIO1_DA_int_40_mask                                            (0x00000400)
#define MIS_FAST_ISR_GPIO1_DA_int_40(data)                                           (0x00000400&((data)<<10))
#define MIS_FAST_ISR_GPIO1_DA_int_40_src(data)                                       ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO1_DA_get_int_40(data)                                       ((0x00000400&(data))>>10)
#define MIS_FAST_ISR_GPIO1_DA_int_39_shift                                           (9)
#define MIS_FAST_ISR_GPIO1_DA_int_39_mask                                            (0x00000200)
#define MIS_FAST_ISR_GPIO1_DA_int_39(data)                                           (0x00000200&((data)<<9))
#define MIS_FAST_ISR_GPIO1_DA_int_39_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO1_DA_get_int_39(data)                                       ((0x00000200&(data))>>9)
#define MIS_FAST_ISR_GPIO1_DA_int_38_shift                                           (8)
#define MIS_FAST_ISR_GPIO1_DA_int_38_mask                                            (0x00000100)
#define MIS_FAST_ISR_GPIO1_DA_int_38(data)                                           (0x00000100&((data)<<8))
#define MIS_FAST_ISR_GPIO1_DA_int_38_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO1_DA_get_int_38(data)                                       ((0x00000100&(data))>>8)
#define MIS_FAST_ISR_GPIO1_DA_int_37_shift                                           (7)
#define MIS_FAST_ISR_GPIO1_DA_int_37_mask                                            (0x00000080)
#define MIS_FAST_ISR_GPIO1_DA_int_37(data)                                           (0x00000080&((data)<<7))
#define MIS_FAST_ISR_GPIO1_DA_int_37_src(data)                                       ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO1_DA_get_int_37(data)                                       ((0x00000080&(data))>>7)
#define MIS_FAST_ISR_GPIO1_DA_int_36_shift                                           (6)
#define MIS_FAST_ISR_GPIO1_DA_int_36_mask                                            (0x00000040)
#define MIS_FAST_ISR_GPIO1_DA_int_36(data)                                           (0x00000040&((data)<<6))
#define MIS_FAST_ISR_GPIO1_DA_int_36_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO1_DA_get_int_36(data)                                       ((0x00000040&(data))>>6)
#define MIS_FAST_ISR_GPIO1_DA_int_35_shift                                           (5)
#define MIS_FAST_ISR_GPIO1_DA_int_35_mask                                            (0x00000020)
#define MIS_FAST_ISR_GPIO1_DA_int_35(data)                                           (0x00000020&((data)<<5))
#define MIS_FAST_ISR_GPIO1_DA_int_35_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO1_DA_get_int_35(data)                                       ((0x00000020&(data))>>5)
#define MIS_FAST_ISR_GPIO1_DA_int_34_shift                                           (4)
#define MIS_FAST_ISR_GPIO1_DA_int_34_mask                                            (0x00000010)
#define MIS_FAST_ISR_GPIO1_DA_int_34(data)                                           (0x00000010&((data)<<4))
#define MIS_FAST_ISR_GPIO1_DA_int_34_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO1_DA_get_int_34(data)                                       ((0x00000010&(data))>>4)
#define MIS_FAST_ISR_GPIO1_DA_int_33_shift                                           (3)
#define MIS_FAST_ISR_GPIO1_DA_int_33_mask                                            (0x00000008)
#define MIS_FAST_ISR_GPIO1_DA_int_33(data)                                           (0x00000008&((data)<<3))
#define MIS_FAST_ISR_GPIO1_DA_int_33_src(data)                                       ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO1_DA_get_int_33(data)                                       ((0x00000008&(data))>>3)
#define MIS_FAST_ISR_GPIO1_DA_int_32_shift                                           (2)
#define MIS_FAST_ISR_GPIO1_DA_int_32_mask                                            (0x00000004)
#define MIS_FAST_ISR_GPIO1_DA_int_32(data)                                           (0x00000004&((data)<<2))
#define MIS_FAST_ISR_GPIO1_DA_int_32_src(data)                                       ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO1_DA_get_int_32(data)                                       ((0x00000004&(data))>>2)
#define MIS_FAST_ISR_GPIO1_DA_int_31_shift                                           (1)
#define MIS_FAST_ISR_GPIO1_DA_int_31_mask                                            (0x00000002)
#define MIS_FAST_ISR_GPIO1_DA_int_31(data)                                           (0x00000002&((data)<<1))
#define MIS_FAST_ISR_GPIO1_DA_int_31_src(data)                                       ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO1_DA_get_int_31(data)                                       ((0x00000002&(data))>>1)
#define MIS_FAST_ISR_GPIO1_DA_write_data_shift                                       (0)
#define MIS_FAST_ISR_GPIO1_DA_write_data_mask                                        (0x00000001)
#define MIS_FAST_ISR_GPIO1_DA_write_data(data)                                       (0x00000001&((data)<<0))
#define MIS_FAST_ISR_GPIO1_DA_write_data_src(data)                                   ((0x00000001&(data))>>0)
#define MIS_FAST_ISR_GPIO1_DA_get_write_data(data)                                   ((0x00000001&(data))>>0)


#define MIS_SCPU_INT_EN                                                              0x1801B080
#define MIS_SCPU_INT_EN_reg_addr                                                     "0xB801B080"
#define MIS_SCPU_INT_EN_reg                                                          0xB801B080
#define set_MIS_SCPU_INT_EN_reg(data)   (*((volatile unsigned int*) MIS_SCPU_INT_EN_reg)=data)
#define get_MIS_SCPU_INT_EN_reg   (*((volatile unsigned int*) MIS_SCPU_INT_EN_reg))
#define MIS_SCPU_INT_EN_inst_adr                                                     "0x0020"
#define MIS_SCPU_INT_EN_inst                                                         0x0020
#define MIS_SCPU_INT_EN_i2c3_shift                                                   (28)
#define MIS_SCPU_INT_EN_i2c3_mask                                                    (0x10000000)
#define MIS_SCPU_INT_EN_i2c3(data)                                                   (0x10000000&((data)<<28))
#define MIS_SCPU_INT_EN_i2c3_src(data)                                               ((0x10000000&(data))>>28)
#define MIS_SCPU_INT_EN_get_i2c3(data)                                               ((0x10000000&(data))>>28)
#define MIS_SCPU_INT_EN_gspi_shift                                                   (27)
#define MIS_SCPU_INT_EN_gspi_mask                                                    (0x08000000)
#define MIS_SCPU_INT_EN_gspi(data)                                                   (0x08000000&((data)<<27))
#define MIS_SCPU_INT_EN_gspi_src(data)                                               ((0x08000000&(data))>>27)
#define MIS_SCPU_INT_EN_get_gspi(data)                                               ((0x08000000&(data))>>27)
#define MIS_SCPU_INT_EN_i2c2_shift                                                   (26)
#define MIS_SCPU_INT_EN_i2c2_mask                                                    (0x04000000)
#define MIS_SCPU_INT_EN_i2c2(data)                                                   (0x04000000&((data)<<26))
#define MIS_SCPU_INT_EN_i2c2_src(data)                                               ((0x04000000&(data))>>26)
#define MIS_SCPU_INT_EN_get_i2c2(data)                                               ((0x04000000&(data))>>26)
#define MIS_SCPU_INT_EN_lsadc_shift                                                  (21)
#define MIS_SCPU_INT_EN_lsadc_mask                                                   (0x00200000)
#define MIS_SCPU_INT_EN_lsadc(data)                                                  (0x00200000&((data)<<21))
#define MIS_SCPU_INT_EN_lsadc_src(data)                                              ((0x00200000&(data))>>21)
#define MIS_SCPU_INT_EN_get_lsadc(data)                                              ((0x00200000&(data))>>21)
#define MIS_SCPU_INT_EN_gpioda_shift                                                 (20)
#define MIS_SCPU_INT_EN_gpioda_mask                                                  (0x00100000)
#define MIS_SCPU_INT_EN_gpioda(data)                                                 (0x00100000&((data)<<20))
#define MIS_SCPU_INT_EN_gpioda_src(data)                                             ((0x00100000&(data))>>20)
#define MIS_SCPU_INT_EN_get_gpioda(data)                                             ((0x00100000&(data))>>20)
#define MIS_SCPU_INT_EN_gpioa_shift                                                  (19)
#define MIS_SCPU_INT_EN_gpioa_mask                                                   (0x00080000)
#define MIS_SCPU_INT_EN_gpioa(data)                                                  (0x00080000&((data)<<19))
#define MIS_SCPU_INT_EN_gpioa_src(data)                                              ((0x00080000&(data))>>19)
#define MIS_SCPU_INT_EN_get_gpioa(data)                                              ((0x00080000&(data))>>19)
#define MIS_SCPU_INT_EN_i2c4_shift                                                   (15)
#define MIS_SCPU_INT_EN_i2c4_mask                                                    (0x00008000)
#define MIS_SCPU_INT_EN_i2c4(data)                                                   (0x00008000&((data)<<15))
#define MIS_SCPU_INT_EN_i2c4_src(data)                                               ((0x00008000&(data))>>15)
#define MIS_SCPU_INT_EN_get_i2c4(data)                                               ((0x00008000&(data))>>15)
#define MIS_SCPU_INT_EN_i2c5_shift                                                   (14)
#define MIS_SCPU_INT_EN_i2c5_mask                                                    (0x00004000)
#define MIS_SCPU_INT_EN_i2c5(data)                                                   (0x00004000&((data)<<14))
#define MIS_SCPU_INT_EN_i2c5_src(data)                                               ((0x00004000&(data))>>14)
#define MIS_SCPU_INT_EN_get_i2c5(data)                                               ((0x00004000&(data))>>14)
#define MIS_SCPU_INT_EN_rtc_date_shift                                               (12)
#define MIS_SCPU_INT_EN_rtc_date_mask                                                (0x00001000)
#define MIS_SCPU_INT_EN_rtc_date(data)                                               (0x00001000&((data)<<12))
#define MIS_SCPU_INT_EN_rtc_date_src(data)                                           ((0x00001000&(data))>>12)
#define MIS_SCPU_INT_EN_get_rtc_date(data)                                           ((0x00001000&(data))>>12)
#define MIS_SCPU_INT_EN_rtc_hour_shift                                               (11)
#define MIS_SCPU_INT_EN_rtc_hour_mask                                                (0x00000800)
#define MIS_SCPU_INT_EN_rtc_hour(data)                                               (0x00000800&((data)<<11))
#define MIS_SCPU_INT_EN_rtc_hour_src(data)                                           ((0x00000800&(data))>>11)
#define MIS_SCPU_INT_EN_get_rtc_hour(data)                                           ((0x00000800&(data))>>11)
#define MIS_SCPU_INT_EN_rtc_min_shift                                                (10)
#define MIS_SCPU_INT_EN_rtc_min_mask                                                 (0x00000400)
#define MIS_SCPU_INT_EN_rtc_min(data)                                                (0x00000400&((data)<<10))
#define MIS_SCPU_INT_EN_rtc_min_src(data)                                            ((0x00000400&(data))>>10)
#define MIS_SCPU_INT_EN_get_rtc_min(data)                                            ((0x00000400&(data))>>10)
#define MIS_SCPU_INT_EN_ur1_to_shift                                                 (5)
#define MIS_SCPU_INT_EN_ur1_to_mask                                                  (0x00000020)
#define MIS_SCPU_INT_EN_ur1_to(data)                                                 (0x00000020&((data)<<5))
#define MIS_SCPU_INT_EN_ur1_to_src(data)                                             ((0x00000020&(data))>>5)
#define MIS_SCPU_INT_EN_get_ur1_to(data)                                             ((0x00000020&(data))>>5)
#define MIS_SCPU_INT_EN_i2c1_shift                                                   (4)
#define MIS_SCPU_INT_EN_i2c1_mask                                                    (0x00000010)
#define MIS_SCPU_INT_EN_i2c1(data)                                                   (0x00000010&((data)<<4))
#define MIS_SCPU_INT_EN_i2c1_src(data)                                               ((0x00000010&(data))>>4)
#define MIS_SCPU_INT_EN_get_i2c1(data)                                               ((0x00000010&(data))>>4)
#define MIS_SCPU_INT_EN_ur1_shift                                                    (3)
#define MIS_SCPU_INT_EN_ur1_mask                                                     (0x00000008)
#define MIS_SCPU_INT_EN_ur1(data)                                                    (0x00000008&((data)<<3))
#define MIS_SCPU_INT_EN_ur1_src(data)                                                ((0x00000008&(data))>>3)
#define MIS_SCPU_INT_EN_get_ur1(data)                                                ((0x00000008&(data))>>3)


#define MIS_I2C1_SDA_DEL                                                             0x1801B088
#define MIS_I2C1_SDA_DEL_reg_addr                                                    "0xB801B088"
#define MIS_I2C1_SDA_DEL_reg                                                         0xB801B088
#define set_MIS_I2C1_SDA_DEL_reg(data)   (*((volatile unsigned int*) MIS_I2C1_SDA_DEL_reg)=data)
#define get_MIS_I2C1_SDA_DEL_reg   (*((volatile unsigned int*) MIS_I2C1_SDA_DEL_reg))
#define MIS_I2C1_SDA_DEL_inst_adr                                                    "0x0022"
#define MIS_I2C1_SDA_DEL_inst                                                        0x0022
#define MIS_I2C1_SDA_DEL_dmy1_shift                                                  (12)
#define MIS_I2C1_SDA_DEL_dmy1_mask                                                   (0xFFFFF000)
#define MIS_I2C1_SDA_DEL_dmy1(data)                                                  (0xFFFFF000&((data)<<12))
#define MIS_I2C1_SDA_DEL_dmy1_src(data)                                              ((0xFFFFF000&(data))>>12)
#define MIS_I2C1_SDA_DEL_get_dmy1(data)                                              ((0xFFFFF000&(data))>>12)
#define MIS_I2C1_SDA_DEL_en_shift                                                    (8)
#define MIS_I2C1_SDA_DEL_en_mask                                                     (0x00000100)
#define MIS_I2C1_SDA_DEL_en(data)                                                    (0x00000100&((data)<<8))
#define MIS_I2C1_SDA_DEL_en_src(data)                                                ((0x00000100&(data))>>8)
#define MIS_I2C1_SDA_DEL_get_en(data)                                                ((0x00000100&(data))>>8)
#define MIS_I2C1_SDA_DEL_sel_shift                                                   (0)
#define MIS_I2C1_SDA_DEL_sel_mask                                                    (0x0000001F)
#define MIS_I2C1_SDA_DEL_sel(data)                                                   (0x0000001F&((data)<<0))
#define MIS_I2C1_SDA_DEL_sel_src(data)                                               ((0x0000001F&(data))>>0)
#define MIS_I2C1_SDA_DEL_get_sel(data)                                               ((0x0000001F&(data))>>0)


#define MIS_I2C2_SDA_DEL                                                             0x1801B08c
#define MIS_I2C2_SDA_DEL_reg_addr                                                    "0xB801B08C"
#define MIS_I2C2_SDA_DEL_reg                                                         0xB801B08C
#define set_MIS_I2C2_SDA_DEL_reg(data)   (*((volatile unsigned int*) MIS_I2C2_SDA_DEL_reg)=data)
#define get_MIS_I2C2_SDA_DEL_reg   (*((volatile unsigned int*) MIS_I2C2_SDA_DEL_reg))
#define MIS_I2C2_SDA_DEL_inst_adr                                                    "0x0023"
#define MIS_I2C2_SDA_DEL_inst                                                        0x0023
#define MIS_I2C2_SDA_DEL_dmy1_shift                                                  (12)
#define MIS_I2C2_SDA_DEL_dmy1_mask                                                   (0xFFFFF000)
#define MIS_I2C2_SDA_DEL_dmy1(data)                                                  (0xFFFFF000&((data)<<12))
#define MIS_I2C2_SDA_DEL_dmy1_src(data)                                              ((0xFFFFF000&(data))>>12)
#define MIS_I2C2_SDA_DEL_get_dmy1(data)                                              ((0xFFFFF000&(data))>>12)
#define MIS_I2C2_SDA_DEL_en_shift                                                    (8)
#define MIS_I2C2_SDA_DEL_en_mask                                                     (0x00000100)
#define MIS_I2C2_SDA_DEL_en(data)                                                    (0x00000100&((data)<<8))
#define MIS_I2C2_SDA_DEL_en_src(data)                                                ((0x00000100&(data))>>8)
#define MIS_I2C2_SDA_DEL_get_en(data)                                                ((0x00000100&(data))>>8)
#define MIS_I2C2_SDA_DEL_sel_shift                                                   (0)
#define MIS_I2C2_SDA_DEL_sel_mask                                                    (0x0000001F)
#define MIS_I2C2_SDA_DEL_sel(data)                                                   (0x0000001F&((data)<<0))
#define MIS_I2C2_SDA_DEL_sel_src(data)                                               ((0x0000001F&(data))>>0)
#define MIS_I2C2_SDA_DEL_get_sel(data)                                               ((0x0000001F&(data))>>0)


#define MIS_I2C3_SDA_DEL                                                             0x1801B090
#define MIS_I2C3_SDA_DEL_reg_addr                                                    "0xB801B090"
#define MIS_I2C3_SDA_DEL_reg                                                         0xB801B090
#define set_MIS_I2C3_SDA_DEL_reg(data)   (*((volatile unsigned int*) MIS_I2C3_SDA_DEL_reg)=data)
#define get_MIS_I2C3_SDA_DEL_reg   (*((volatile unsigned int*) MIS_I2C3_SDA_DEL_reg))
#define MIS_I2C3_SDA_DEL_inst_adr                                                    "0x0024"
#define MIS_I2C3_SDA_DEL_inst                                                        0x0024
#define MIS_I2C3_SDA_DEL_dmy1_shift                                                  (12)
#define MIS_I2C3_SDA_DEL_dmy1_mask                                                   (0xFFFFF000)
#define MIS_I2C3_SDA_DEL_dmy1(data)                                                  (0xFFFFF000&((data)<<12))
#define MIS_I2C3_SDA_DEL_dmy1_src(data)                                              ((0xFFFFF000&(data))>>12)
#define MIS_I2C3_SDA_DEL_get_dmy1(data)                                              ((0xFFFFF000&(data))>>12)
#define MIS_I2C3_SDA_DEL_en_shift                                                    (8)
#define MIS_I2C3_SDA_DEL_en_mask                                                     (0x00000100)
#define MIS_I2C3_SDA_DEL_en(data)                                                    (0x00000100&((data)<<8))
#define MIS_I2C3_SDA_DEL_en_src(data)                                                ((0x00000100&(data))>>8)
#define MIS_I2C3_SDA_DEL_get_en(data)                                                ((0x00000100&(data))>>8)
#define MIS_I2C3_SDA_DEL_sel_shift                                                   (0)
#define MIS_I2C3_SDA_DEL_sel_mask                                                    (0x0000001F)
#define MIS_I2C3_SDA_DEL_sel(data)                                                   (0x0000001F&((data)<<0))
#define MIS_I2C3_SDA_DEL_sel_src(data)                                               ((0x0000001F&(data))>>0)
#define MIS_I2C3_SDA_DEL_get_sel(data)                                               ((0x0000001F&(data))>>0)


#define MIS_I2C4_SDA_DEL                                                             0x1801B094
#define MIS_I2C4_SDA_DEL_reg_addr                                                    "0xB801B094"
#define MIS_I2C4_SDA_DEL_reg                                                         0xB801B094
#define set_MIS_I2C4_SDA_DEL_reg(data)   (*((volatile unsigned int*) MIS_I2C4_SDA_DEL_reg)=data)
#define get_MIS_I2C4_SDA_DEL_reg   (*((volatile unsigned int*) MIS_I2C4_SDA_DEL_reg))
#define MIS_I2C4_SDA_DEL_inst_adr                                                    "0x0025"
#define MIS_I2C4_SDA_DEL_inst                                                        0x0025
#define MIS_I2C4_SDA_DEL_dmy1_shift                                                  (12)
#define MIS_I2C4_SDA_DEL_dmy1_mask                                                   (0xFFFFF000)
#define MIS_I2C4_SDA_DEL_dmy1(data)                                                  (0xFFFFF000&((data)<<12))
#define MIS_I2C4_SDA_DEL_dmy1_src(data)                                              ((0xFFFFF000&(data))>>12)
#define MIS_I2C4_SDA_DEL_get_dmy1(data)                                              ((0xFFFFF000&(data))>>12)
#define MIS_I2C4_SDA_DEL_en_shift                                                    (8)
#define MIS_I2C4_SDA_DEL_en_mask                                                     (0x00000100)
#define MIS_I2C4_SDA_DEL_en(data)                                                    (0x00000100&((data)<<8))
#define MIS_I2C4_SDA_DEL_en_src(data)                                                ((0x00000100&(data))>>8)
#define MIS_I2C4_SDA_DEL_get_en(data)                                                ((0x00000100&(data))>>8)
#define MIS_I2C4_SDA_DEL_sel_shift                                                   (0)
#define MIS_I2C4_SDA_DEL_sel_mask                                                    (0x0000001F)
#define MIS_I2C4_SDA_DEL_sel(data)                                                   (0x0000001F&((data)<<0))
#define MIS_I2C4_SDA_DEL_sel_src(data)                                               ((0x0000001F&(data))>>0)
#define MIS_I2C4_SDA_DEL_get_sel(data)                                               ((0x0000001F&(data))>>0)


#define MIS_I2C5_SDA_DEL                                                             0x1801B098
#define MIS_I2C5_SDA_DEL_reg_addr                                                    "0xB801B098"
#define MIS_I2C5_SDA_DEL_reg                                                         0xB801B098
#define set_MIS_I2C5_SDA_DEL_reg(data)   (*((volatile unsigned int*) MIS_I2C5_SDA_DEL_reg)=data)
#define get_MIS_I2C5_SDA_DEL_reg   (*((volatile unsigned int*) MIS_I2C5_SDA_DEL_reg))
#define MIS_I2C5_SDA_DEL_inst_adr                                                    "0x0026"
#define MIS_I2C5_SDA_DEL_inst                                                        0x0026
#define MIS_I2C5_SDA_DEL_dmy1_shift                                                  (12)
#define MIS_I2C5_SDA_DEL_dmy1_mask                                                   (0xFFFFF000)
#define MIS_I2C5_SDA_DEL_dmy1(data)                                                  (0xFFFFF000&((data)<<12))
#define MIS_I2C5_SDA_DEL_dmy1_src(data)                                              ((0xFFFFF000&(data))>>12)
#define MIS_I2C5_SDA_DEL_get_dmy1(data)                                              ((0xFFFFF000&(data))>>12)
#define MIS_I2C5_SDA_DEL_en_shift                                                    (8)
#define MIS_I2C5_SDA_DEL_en_mask                                                     (0x00000100)
#define MIS_I2C5_SDA_DEL_en(data)                                                    (0x00000100&((data)<<8))
#define MIS_I2C5_SDA_DEL_en_src(data)                                                ((0x00000100&(data))>>8)
#define MIS_I2C5_SDA_DEL_get_en(data)                                                ((0x00000100&(data))>>8)
#define MIS_I2C5_SDA_DEL_sel_shift                                                   (0)
#define MIS_I2C5_SDA_DEL_sel_mask                                                    (0x0000001F)
#define MIS_I2C5_SDA_DEL_sel(data)                                                   (0x0000001F&((data)<<0))
#define MIS_I2C5_SDA_DEL_sel_src(data)                                               ((0x0000001F&(data))>>0)
#define MIS_I2C5_SDA_DEL_get_sel(data)                                               ((0x0000001F&(data))>>0)


#define MIS_GP0DIR                                                                   0x1801B100
#define MIS_GP0DIR_reg_addr                                                          "0xB801B100"
#define MIS_GP0DIR_reg                                                               0xB801B100
#define set_MIS_GP0DIR_reg(data)   (*((volatile unsigned int*) MIS_GP0DIR_reg)=data)
#define get_MIS_GP0DIR_reg   (*((volatile unsigned int*) MIS_GP0DIR_reg))
#define MIS_GP0DIR_inst_adr                                                          "0x0040"
#define MIS_GP0DIR_inst                                                              0x0040
#define MIS_GP0DIR_gpdir_shift                                                       (0)
#define MIS_GP0DIR_gpdir_mask                                                        (0xFFFFFFFF)
#define MIS_GP0DIR_gpdir(data)                                                       (0xFFFFFFFF&((data)<<0))
#define MIS_GP0DIR_gpdir_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define MIS_GP0DIR_get_gpdir(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define MIS_GP1DIR                                                                   0x1801B104
#define MIS_GP1DIR_reg_addr                                                          "0xB801B104"
#define MIS_GP1DIR_reg                                                               0xB801B104
#define set_MIS_GP1DIR_reg(data)   (*((volatile unsigned int*) MIS_GP1DIR_reg)=data)
#define get_MIS_GP1DIR_reg   (*((volatile unsigned int*) MIS_GP1DIR_reg))
#define MIS_GP1DIR_inst_adr                                                          "0x0041"
#define MIS_GP1DIR_inst                                                              0x0041
#define MIS_GP1DIR_gpdir_shift                                                       (0)
#define MIS_GP1DIR_gpdir_mask                                                        (0x0FFFFFFF)
#define MIS_GP1DIR_gpdir(data)                                                       (0x0FFFFFFF&((data)<<0))
#define MIS_GP1DIR_gpdir_src(data)                                                   ((0x0FFFFFFF&(data))>>0)
#define MIS_GP1DIR_get_gpdir(data)                                                   ((0x0FFFFFFF&(data))>>0)


#define MIS_GP0DATO                                                                  0x1801B110
#define MIS_GP0DATO_reg_addr                                                         "0xB801B110"
#define MIS_GP0DATO_reg                                                              0xB801B110
#define set_MIS_GP0DATO_reg(data)   (*((volatile unsigned int*) MIS_GP0DATO_reg)=data)
#define get_MIS_GP0DATO_reg   (*((volatile unsigned int*) MIS_GP0DATO_reg))
#define MIS_GP0DATO_inst_adr                                                         "0x0044"
#define MIS_GP0DATO_inst                                                             0x0044
#define MIS_GP0DATO_gpdato_shift                                                     (0)
#define MIS_GP0DATO_gpdato_mask                                                      (0xFFFFFFFF)
#define MIS_GP0DATO_gpdato(data)                                                     (0xFFFFFFFF&((data)<<0))
#define MIS_GP0DATO_gpdato_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define MIS_GP0DATO_get_gpdato(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define MIS_GP1DATO                                                                  0x1801B114
#define MIS_GP1DATO_reg_addr                                                         "0xB801B114"
#define MIS_GP1DATO_reg                                                              0xB801B114
#define set_MIS_GP1DATO_reg(data)   (*((volatile unsigned int*) MIS_GP1DATO_reg)=data)
#define get_MIS_GP1DATO_reg   (*((volatile unsigned int*) MIS_GP1DATO_reg))
#define MIS_GP1DATO_inst_adr                                                         "0x0045"
#define MIS_GP1DATO_inst                                                             0x0045
#define MIS_GP1DATO_gpdato_shift                                                     (0)
#define MIS_GP1DATO_gpdato_mask                                                      (0x0FFFFFFF)
#define MIS_GP1DATO_gpdato(data)                                                     (0x0FFFFFFF&((data)<<0))
#define MIS_GP1DATO_gpdato_src(data)                                                 ((0x0FFFFFFF&(data))>>0)
#define MIS_GP1DATO_get_gpdato(data)                                                 ((0x0FFFFFFF&(data))>>0)


#define MIS_GP0DATI                                                                  0x1801B120
#define MIS_GP0DATI_reg_addr                                                         "0xB801B120"
#define MIS_GP0DATI_reg                                                              0xB801B120
#define set_MIS_GP0DATI_reg(data)   (*((volatile unsigned int*) MIS_GP0DATI_reg)=data)
#define get_MIS_GP0DATI_reg   (*((volatile unsigned int*) MIS_GP0DATI_reg))
#define MIS_GP0DATI_inst_adr                                                         "0x0048"
#define MIS_GP0DATI_inst                                                             0x0048
#define MIS_GP0DATI_gpdati_shift                                                     (0)
#define MIS_GP0DATI_gpdati_mask                                                      (0xFFFFFFFF)
#define MIS_GP0DATI_gpdati(data)                                                     (0xFFFFFFFF&((data)<<0))
#define MIS_GP0DATI_gpdati_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define MIS_GP0DATI_get_gpdati(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define MIS_GP1DATI                                                                  0x1801B124
#define MIS_GP1DATI_reg_addr                                                         "0xB801B124"
#define MIS_GP1DATI_reg                                                              0xB801B124
#define set_MIS_GP1DATI_reg(data)   (*((volatile unsigned int*) MIS_GP1DATI_reg)=data)
#define get_MIS_GP1DATI_reg   (*((volatile unsigned int*) MIS_GP1DATI_reg))
#define MIS_GP1DATI_inst_adr                                                         "0x0049"
#define MIS_GP1DATI_inst                                                             0x0049
#define MIS_GP1DATI_gpdati_shift                                                     (0)
#define MIS_GP1DATI_gpdati_mask                                                      (0x0FFFFFFF)
#define MIS_GP1DATI_gpdati(data)                                                     (0x0FFFFFFF&((data)<<0))
#define MIS_GP1DATI_gpdati_src(data)                                                 ((0x0FFFFFFF&(data))>>0)
#define MIS_GP1DATI_get_gpdati(data)                                                 ((0x0FFFFFFF&(data))>>0)


#define MIS_GP0IE                                                                    0x1801B130
#define MIS_GP0IE_reg_addr                                                           "0xB801B130"
#define MIS_GP0IE_reg                                                                0xB801B130
#define set_MIS_GP0IE_reg(data)   (*((volatile unsigned int*) MIS_GP0IE_reg)=data)
#define get_MIS_GP0IE_reg   (*((volatile unsigned int*) MIS_GP0IE_reg))
#define MIS_GP0IE_inst_adr                                                           "0x004C"
#define MIS_GP0IE_inst                                                               0x004C
#define MIS_GP0IE_gp_shift                                                           (0)
#define MIS_GP0IE_gp_mask                                                            (0xFFFFFFFF)
#define MIS_GP0IE_gp(data)                                                           (0xFFFFFFFF&((data)<<0))
#define MIS_GP0IE_gp_src(data)                                                       ((0xFFFFFFFF&(data))>>0)
#define MIS_GP0IE_get_gp(data)                                                       ((0xFFFFFFFF&(data))>>0)


#define MIS_GP1IE                                                                    0x1801B134
#define MIS_GP1IE_reg_addr                                                           "0xB801B134"
#define MIS_GP1IE_reg                                                                0xB801B134
#define set_MIS_GP1IE_reg(data)   (*((volatile unsigned int*) MIS_GP1IE_reg)=data)
#define get_MIS_GP1IE_reg   (*((volatile unsigned int*) MIS_GP1IE_reg))
#define MIS_GP1IE_inst_adr                                                           "0x004D"
#define MIS_GP1IE_inst                                                               0x004D
#define MIS_GP1IE_gp_shift                                                           (0)
#define MIS_GP1IE_gp_mask                                                            (0x0FFFFFFF)
#define MIS_GP1IE_gp(data)                                                           (0x0FFFFFFF&((data)<<0))
#define MIS_GP1IE_gp_src(data)                                                       ((0x0FFFFFFF&(data))>>0)
#define MIS_GP1IE_get_gp(data)                                                       ((0x0FFFFFFF&(data))>>0)


#define MIS_GP0DP                                                                    0x1801B140
#define MIS_GP0DP_reg_addr                                                           "0xB801B140"
#define MIS_GP0DP_reg                                                                0xB801B140
#define set_MIS_GP0DP_reg(data)   (*((volatile unsigned int*) MIS_GP0DP_reg)=data)
#define get_MIS_GP0DP_reg   (*((volatile unsigned int*) MIS_GP0DP_reg))
#define MIS_GP0DP_inst_adr                                                           "0x0050"
#define MIS_GP0DP_inst                                                               0x0050
#define MIS_GP0DP_gpha_shift                                                         (0)
#define MIS_GP0DP_gpha_mask                                                          (0xFFFFFFFF)
#define MIS_GP0DP_gpha(data)                                                         (0xFFFFFFFF&((data)<<0))
#define MIS_GP0DP_gpha_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define MIS_GP0DP_get_gpha(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define MIS_GP1DP                                                                    0x1801B144
#define MIS_GP1DP_reg_addr                                                           "0xB801B144"
#define MIS_GP1DP_reg                                                                0xB801B144
#define set_MIS_GP1DP_reg(data)   (*((volatile unsigned int*) MIS_GP1DP_reg)=data)
#define get_MIS_GP1DP_reg   (*((volatile unsigned int*) MIS_GP1DP_reg))
#define MIS_GP1DP_inst_adr                                                           "0x0051"
#define MIS_GP1DP_inst                                                               0x0051
#define MIS_GP1DP_gpha_shift                                                         (0)
#define MIS_GP1DP_gpha_mask                                                          (0x0FFFFFFF)
#define MIS_GP1DP_gpha(data)                                                         (0x0FFFFFFF&((data)<<0))
#define MIS_GP1DP_gpha_src(data)                                                     ((0x0FFFFFFF&(data))>>0)
#define MIS_GP1DP_get_gpha(data)                                                     ((0x0FFFFFFF&(data))>>0)


#define MIS_GPDEB                                                                    0x1801B150
#define MIS_GPDEB_reg_addr                                                           "0xB801B150"
#define MIS_GPDEB_reg                                                                0xB801B150
#define set_MIS_GPDEB_reg(data)   (*((volatile unsigned int*) MIS_GPDEB_reg)=data)
#define get_MIS_GPDEB_reg   (*((volatile unsigned int*) MIS_GPDEB_reg))
#define MIS_GPDEB_inst_adr                                                           "0x0054"
#define MIS_GPDEB_inst                                                               0x0054
#define MIS_GPDEB_write_enable4_shift                                                (15)
#define MIS_GPDEB_write_enable4_mask                                                 (0x00008000)
#define MIS_GPDEB_write_enable4(data)                                                (0x00008000&((data)<<15))
#define MIS_GPDEB_write_enable4_src(data)                                            ((0x00008000&(data))>>15)
#define MIS_GPDEB_get_write_enable4(data)                                            ((0x00008000&(data))>>15)
#define MIS_GPDEB_clk4_shift                                                         (12)
#define MIS_GPDEB_clk4_mask                                                          (0x00007000)
#define MIS_GPDEB_clk4(data)                                                         (0x00007000&((data)<<12))
#define MIS_GPDEB_clk4_src(data)                                                     ((0x00007000&(data))>>12)
#define MIS_GPDEB_get_clk4(data)                                                     ((0x00007000&(data))>>12)
#define MIS_GPDEB_write_enable3_shift                                                (11)
#define MIS_GPDEB_write_enable3_mask                                                 (0x00000800)
#define MIS_GPDEB_write_enable3(data)                                                (0x00000800&((data)<<11))
#define MIS_GPDEB_write_enable3_src(data)                                            ((0x00000800&(data))>>11)
#define MIS_GPDEB_get_write_enable3(data)                                            ((0x00000800&(data))>>11)
#define MIS_GPDEB_clk3_shift                                                         (8)
#define MIS_GPDEB_clk3_mask                                                          (0x00000700)
#define MIS_GPDEB_clk3(data)                                                         (0x00000700&((data)<<8))
#define MIS_GPDEB_clk3_src(data)                                                     ((0x00000700&(data))>>8)
#define MIS_GPDEB_get_clk3(data)                                                     ((0x00000700&(data))>>8)
#define MIS_GPDEB_write_enable2_shift                                                (7)
#define MIS_GPDEB_write_enable2_mask                                                 (0x00000080)
#define MIS_GPDEB_write_enable2(data)                                                (0x00000080&((data)<<7))
#define MIS_GPDEB_write_enable2_src(data)                                            ((0x00000080&(data))>>7)
#define MIS_GPDEB_get_write_enable2(data)                                            ((0x00000080&(data))>>7)
#define MIS_GPDEB_clk2_shift                                                         (4)
#define MIS_GPDEB_clk2_mask                                                          (0x00000070)
#define MIS_GPDEB_clk2(data)                                                         (0x00000070&((data)<<4))
#define MIS_GPDEB_clk2_src(data)                                                     ((0x00000070&(data))>>4)
#define MIS_GPDEB_get_clk2(data)                                                     ((0x00000070&(data))>>4)
#define MIS_GPDEB_write_enable1_shift                                                (3)
#define MIS_GPDEB_write_enable1_mask                                                 (0x00000008)
#define MIS_GPDEB_write_enable1(data)                                                (0x00000008&((data)<<3))
#define MIS_GPDEB_write_enable1_src(data)                                            ((0x00000008&(data))>>3)
#define MIS_GPDEB_get_write_enable1(data)                                            ((0x00000008&(data))>>3)
#define MIS_GPDEB_clk1_shift                                                         (0)
#define MIS_GPDEB_clk1_mask                                                          (0x00000007)
#define MIS_GPDEB_clk1(data)                                                         (0x00000007&((data)<<0))
#define MIS_GPDEB_clk1_src(data)                                                     ((0x00000007&(data))>>0)
#define MIS_GPDEB_get_clk1(data)                                                     ((0x00000007&(data))>>0)


#define MIS_U1RBR_THR_DLL                                                            0x1801B200
#define MIS_U1RBR_THR_DLL_reg_addr                                                   "0xB801B200"
#define MIS_U1RBR_THR_DLL_reg                                                        0xB801B200
#define set_MIS_U1RBR_THR_DLL_reg(data)   (*((volatile unsigned int*) MIS_U1RBR_THR_DLL_reg)=data)
#define get_MIS_U1RBR_THR_DLL_reg   (*((volatile unsigned int*) MIS_U1RBR_THR_DLL_reg))
#define MIS_U1RBR_THR_DLL_inst_adr                                                   "0x0080"
#define MIS_U1RBR_THR_DLL_inst                                                       0x0080
#define MIS_U1RBR_THR_DLL_dll_shift                                                  (0)
#define MIS_U1RBR_THR_DLL_dll_mask                                                   (0x000000FF)
#define MIS_U1RBR_THR_DLL_dll(data)                                                  (0x000000FF&((data)<<0))
#define MIS_U1RBR_THR_DLL_dll_src(data)                                              ((0x000000FF&(data))>>0)
#define MIS_U1RBR_THR_DLL_get_dll(data)                                              ((0x000000FF&(data))>>0)


#define MIS_U1IER_DLH                                                                0x1801B204
#define MIS_U1IER_DLH_reg_addr                                                       "0xB801B204"
#define MIS_U1IER_DLH_reg                                                            0xB801B204
#define set_MIS_U1IER_DLH_reg(data)   (*((volatile unsigned int*) MIS_U1IER_DLH_reg)=data)
#define get_MIS_U1IER_DLH_reg   (*((volatile unsigned int*) MIS_U1IER_DLH_reg))
#define MIS_U1IER_DLH_inst_adr                                                       "0x0081"
#define MIS_U1IER_DLH_inst                                                           0x0081
#define MIS_U1IER_DLH_dlh_shift                                                      (0)
#define MIS_U1IER_DLH_dlh_mask                                                       (0x000000FF)
#define MIS_U1IER_DLH_dlh(data)                                                      (0x000000FF&((data)<<0))
#define MIS_U1IER_DLH_dlh_src(data)                                                  ((0x000000FF&(data))>>0)
#define MIS_U1IER_DLH_get_dlh(data)                                                  ((0x000000FF&(data))>>0)


#define MIS_U1IIR_FCR                                                                0x1801B208
#define MIS_U1IIR_FCR_reg_addr                                                       "0xB801B208"
#define MIS_U1IIR_FCR_reg                                                            0xB801B208
#define set_MIS_U1IIR_FCR_reg(data)   (*((volatile unsigned int*) MIS_U1IIR_FCR_reg)=data)
#define get_MIS_U1IIR_FCR_reg   (*((volatile unsigned int*) MIS_U1IIR_FCR_reg))
#define MIS_U1IIR_FCR_inst_adr                                                       "0x0082"
#define MIS_U1IIR_FCR_inst                                                           0x0082
#define MIS_U1IIR_FCR_fifo16_shift                                                   (6)
#define MIS_U1IIR_FCR_fifo16_mask                                                    (0x000000C0)
#define MIS_U1IIR_FCR_fifo16(data)                                                   (0x000000C0&((data)<<6))
#define MIS_U1IIR_FCR_fifo16_src(data)                                               ((0x000000C0&(data))>>6)
#define MIS_U1IIR_FCR_get_fifo16(data)                                               ((0x000000C0&(data))>>6)
#define MIS_U1IIR_FCR_iid_shift                                                      (0)
#define MIS_U1IIR_FCR_iid_mask                                                       (0x0000000F)
#define MIS_U1IIR_FCR_iid(data)                                                      (0x0000000F&((data)<<0))
#define MIS_U1IIR_FCR_iid_src(data)                                                  ((0x0000000F&(data))>>0)
#define MIS_U1IIR_FCR_get_iid(data)                                                  ((0x0000000F&(data))>>0)


#define MIS_U1LCR                                                                    0x1801B20C
#define MIS_U1LCR_reg_addr                                                           "0xB801B20C"
#define MIS_U1LCR_reg                                                                0xB801B20C
#define set_MIS_U1LCR_reg(data)   (*((volatile unsigned int*) MIS_U1LCR_reg)=data)
#define get_MIS_U1LCR_reg   (*((volatile unsigned int*) MIS_U1LCR_reg))
#define MIS_U1LCR_inst_adr                                                           "0x0083"
#define MIS_U1LCR_inst                                                               0x0083
#define MIS_U1LCR_dlab_shift                                                         (7)
#define MIS_U1LCR_dlab_mask                                                          (0x00000080)
#define MIS_U1LCR_dlab(data)                                                         (0x00000080&((data)<<7))
#define MIS_U1LCR_dlab_src(data)                                                     ((0x00000080&(data))>>7)
#define MIS_U1LCR_get_dlab(data)                                                     ((0x00000080&(data))>>7)
#define MIS_U1LCR_brk_shift                                                          (6)
#define MIS_U1LCR_brk_mask                                                           (0x00000040)
#define MIS_U1LCR_brk(data)                                                          (0x00000040&((data)<<6))
#define MIS_U1LCR_brk_src(data)                                                      ((0x00000040&(data))>>6)
#define MIS_U1LCR_get_brk(data)                                                      ((0x00000040&(data))>>6)
#define MIS_U1LCR_eps_shift                                                          (4)
#define MIS_U1LCR_eps_mask                                                           (0x00000010)
#define MIS_U1LCR_eps(data)                                                          (0x00000010&((data)<<4))
#define MIS_U1LCR_eps_src(data)                                                      ((0x00000010&(data))>>4)
#define MIS_U1LCR_get_eps(data)                                                      ((0x00000010&(data))>>4)
#define MIS_U1LCR_pen_shift                                                          (3)
#define MIS_U1LCR_pen_mask                                                           (0x00000008)
#define MIS_U1LCR_pen(data)                                                          (0x00000008&((data)<<3))
#define MIS_U1LCR_pen_src(data)                                                      ((0x00000008&(data))>>3)
#define MIS_U1LCR_get_pen(data)                                                      ((0x00000008&(data))>>3)
#define MIS_U1LCR_stb_shift                                                          (2)
#define MIS_U1LCR_stb_mask                                                           (0x00000004)
#define MIS_U1LCR_stb(data)                                                          (0x00000004&((data)<<2))
#define MIS_U1LCR_stb_src(data)                                                      ((0x00000004&(data))>>2)
#define MIS_U1LCR_get_stb(data)                                                      ((0x00000004&(data))>>2)
#define MIS_U1LCR_wls_shift                                                          (0)
#define MIS_U1LCR_wls_mask                                                           (0x00000003)
#define MIS_U1LCR_wls(data)                                                          (0x00000003&((data)<<0))
#define MIS_U1LCR_wls_src(data)                                                      ((0x00000003&(data))>>0)
#define MIS_U1LCR_get_wls(data)                                                      ((0x00000003&(data))>>0)


#define MIS_U1MCR                                                                    0x1801B210
#define MIS_U1MCR_reg_addr                                                           "0xB801B210"
#define MIS_U1MCR_reg                                                                0xB801B210
#define set_MIS_U1MCR_reg(data)   (*((volatile unsigned int*) MIS_U1MCR_reg)=data)
#define get_MIS_U1MCR_reg   (*((volatile unsigned int*) MIS_U1MCR_reg))
#define MIS_U1MCR_inst_adr                                                           "0x0084"
#define MIS_U1MCR_inst                                                               0x0084
#define MIS_U1MCR_afce_shift                                                         (5)
#define MIS_U1MCR_afce_mask                                                          (0x00000020)
#define MIS_U1MCR_afce(data)                                                         (0x00000020&((data)<<5))
#define MIS_U1MCR_afce_src(data)                                                     ((0x00000020&(data))>>5)
#define MIS_U1MCR_get_afce(data)                                                     ((0x00000020&(data))>>5)
#define MIS_U1MCR_loop_shift                                                         (4)
#define MIS_U1MCR_loop_mask                                                          (0x00000010)
#define MIS_U1MCR_loop(data)                                                         (0x00000010&((data)<<4))
#define MIS_U1MCR_loop_src(data)                                                     ((0x00000010&(data))>>4)
#define MIS_U1MCR_get_loop(data)                                                     ((0x00000010&(data))>>4)
#define MIS_U1MCR_rts_shift                                                          (1)
#define MIS_U1MCR_rts_mask                                                           (0x00000002)
#define MIS_U1MCR_rts(data)                                                          (0x00000002&((data)<<1))
#define MIS_U1MCR_rts_src(data)                                                      ((0x00000002&(data))>>1)
#define MIS_U1MCR_get_rts(data)                                                      ((0x00000002&(data))>>1)
#define MIS_U1MCR_dtr_shift                                                          (0)
#define MIS_U1MCR_dtr_mask                                                           (0x00000001)
#define MIS_U1MCR_dtr(data)                                                          (0x00000001&((data)<<0))
#define MIS_U1MCR_dtr_src(data)                                                      ((0x00000001&(data))>>0)
#define MIS_U1MCR_get_dtr(data)                                                      ((0x00000001&(data))>>0)


#define MIS_U1LSR                                                                    0x1801B214
#define MIS_U1LSR_reg_addr                                                           "0xB801B214"
#define MIS_U1LSR_reg                                                                0xB801B214
#define set_MIS_U1LSR_reg(data)   (*((volatile unsigned int*) MIS_U1LSR_reg)=data)
#define get_MIS_U1LSR_reg   (*((volatile unsigned int*) MIS_U1LSR_reg))
#define MIS_U1LSR_inst_adr                                                           "0x0085"
#define MIS_U1LSR_inst                                                               0x0085
#define MIS_U1LSR_rfe_shift                                                          (7)
#define MIS_U1LSR_rfe_mask                                                           (0x00000080)
#define MIS_U1LSR_rfe(data)                                                          (0x00000080&((data)<<7))
#define MIS_U1LSR_rfe_src(data)                                                      ((0x00000080&(data))>>7)
#define MIS_U1LSR_get_rfe(data)                                                      ((0x00000080&(data))>>7)
#define MIS_U1LSR_temt_shift                                                         (6)
#define MIS_U1LSR_temt_mask                                                          (0x00000040)
#define MIS_U1LSR_temt(data)                                                         (0x00000040&((data)<<6))
#define MIS_U1LSR_temt_src(data)                                                     ((0x00000040&(data))>>6)
#define MIS_U1LSR_get_temt(data)                                                     ((0x00000040&(data))>>6)
#define MIS_U1LSR_thre_shift                                                         (5)
#define MIS_U1LSR_thre_mask                                                          (0x00000020)
#define MIS_U1LSR_thre(data)                                                         (0x00000020&((data)<<5))
#define MIS_U1LSR_thre_src(data)                                                     ((0x00000020&(data))>>5)
#define MIS_U1LSR_get_thre(data)                                                     ((0x00000020&(data))>>5)
#define MIS_U1LSR_bi_shift                                                           (4)
#define MIS_U1LSR_bi_mask                                                            (0x00000010)
#define MIS_U1LSR_bi(data)                                                           (0x00000010&((data)<<4))
#define MIS_U1LSR_bi_src(data)                                                       ((0x00000010&(data))>>4)
#define MIS_U1LSR_get_bi(data)                                                       ((0x00000010&(data))>>4)
#define MIS_U1LSR_fe_shift                                                           (3)
#define MIS_U1LSR_fe_mask                                                            (0x00000008)
#define MIS_U1LSR_fe(data)                                                           (0x00000008&((data)<<3))
#define MIS_U1LSR_fe_src(data)                                                       ((0x00000008&(data))>>3)
#define MIS_U1LSR_get_fe(data)                                                       ((0x00000008&(data))>>3)
#define MIS_U1LSR_pe_shift                                                           (2)
#define MIS_U1LSR_pe_mask                                                            (0x00000004)
#define MIS_U1LSR_pe(data)                                                           (0x00000004&((data)<<2))
#define MIS_U1LSR_pe_src(data)                                                       ((0x00000004&(data))>>2)
#define MIS_U1LSR_get_pe(data)                                                       ((0x00000004&(data))>>2)
#define MIS_U1LSR_oe_shift                                                           (1)
#define MIS_U1LSR_oe_mask                                                            (0x00000002)
#define MIS_U1LSR_oe(data)                                                           (0x00000002&((data)<<1))
#define MIS_U1LSR_oe_src(data)                                                       ((0x00000002&(data))>>1)
#define MIS_U1LSR_get_oe(data)                                                       ((0x00000002&(data))>>1)
#define MIS_U1LSR_dr_shift                                                           (0)
#define MIS_U1LSR_dr_mask                                                            (0x00000001)
#define MIS_U1LSR_dr(data)                                                           (0x00000001&((data)<<0))
#define MIS_U1LSR_dr_src(data)                                                       ((0x00000001&(data))>>0)
#define MIS_U1LSR_get_dr(data)                                                       ((0x00000001&(data))>>0)


#define MIS_U1MSR                                                                    0x1801B218
#define MIS_U1MSR_reg_addr                                                           "0xB801B218"
#define MIS_U1MSR_reg                                                                0xB801B218
#define set_MIS_U1MSR_reg(data)   (*((volatile unsigned int*) MIS_U1MSR_reg)=data)
#define get_MIS_U1MSR_reg   (*((volatile unsigned int*) MIS_U1MSR_reg))
#define MIS_U1MSR_inst_adr                                                           "0x0086"
#define MIS_U1MSR_inst                                                               0x0086
#define MIS_U1MSR_dcd_shift                                                          (7)
#define MIS_U1MSR_dcd_mask                                                           (0x00000080)
#define MIS_U1MSR_dcd(data)                                                          (0x00000080&((data)<<7))
#define MIS_U1MSR_dcd_src(data)                                                      ((0x00000080&(data))>>7)
#define MIS_U1MSR_get_dcd(data)                                                      ((0x00000080&(data))>>7)
#define MIS_U1MSR_ri_shift                                                           (6)
#define MIS_U1MSR_ri_mask                                                            (0x00000040)
#define MIS_U1MSR_ri(data)                                                           (0x00000040&((data)<<6))
#define MIS_U1MSR_ri_src(data)                                                       ((0x00000040&(data))>>6)
#define MIS_U1MSR_get_ri(data)                                                       ((0x00000040&(data))>>6)
#define MIS_U1MSR_dsr_shift                                                          (5)
#define MIS_U1MSR_dsr_mask                                                           (0x00000020)
#define MIS_U1MSR_dsr(data)                                                          (0x00000020&((data)<<5))
#define MIS_U1MSR_dsr_src(data)                                                      ((0x00000020&(data))>>5)
#define MIS_U1MSR_get_dsr(data)                                                      ((0x00000020&(data))>>5)
#define MIS_U1MSR_cts_shift                                                          (4)
#define MIS_U1MSR_cts_mask                                                           (0x00000010)
#define MIS_U1MSR_cts(data)                                                          (0x00000010&((data)<<4))
#define MIS_U1MSR_cts_src(data)                                                      ((0x00000010&(data))>>4)
#define MIS_U1MSR_get_cts(data)                                                      ((0x00000010&(data))>>4)
#define MIS_U1MSR_ddcd_shift                                                         (3)
#define MIS_U1MSR_ddcd_mask                                                          (0x00000008)
#define MIS_U1MSR_ddcd(data)                                                         (0x00000008&((data)<<3))
#define MIS_U1MSR_ddcd_src(data)                                                     ((0x00000008&(data))>>3)
#define MIS_U1MSR_get_ddcd(data)                                                     ((0x00000008&(data))>>3)
#define MIS_U1MSR_teri_shift                                                         (2)
#define MIS_U1MSR_teri_mask                                                          (0x00000004)
#define MIS_U1MSR_teri(data)                                                         (0x00000004&((data)<<2))
#define MIS_U1MSR_teri_src(data)                                                     ((0x00000004&(data))>>2)
#define MIS_U1MSR_get_teri(data)                                                     ((0x00000004&(data))>>2)
#define MIS_U1MSR_ddsr_shift                                                         (1)
#define MIS_U1MSR_ddsr_mask                                                          (0x00000002)
#define MIS_U1MSR_ddsr(data)                                                         (0x00000002&((data)<<1))
#define MIS_U1MSR_ddsr_src(data)                                                     ((0x00000002&(data))>>1)
#define MIS_U1MSR_get_ddsr(data)                                                     ((0x00000002&(data))>>1)
#define MIS_U1MSR_dcts_shift                                                         (0)
#define MIS_U1MSR_dcts_mask                                                          (0x00000001)
#define MIS_U1MSR_dcts(data)                                                         (0x00000001&((data)<<0))
#define MIS_U1MSR_dcts_src(data)                                                     ((0x00000001&(data))>>0)
#define MIS_U1MSR_get_dcts(data)                                                     ((0x00000001&(data))>>0)


#define MIS_U1SCR                                                                    0x1801B21C
#define MIS_U1SCR_reg_addr                                                           "0xB801B21C"
#define MIS_U1SCR_reg                                                                0xB801B21C
#define set_MIS_U1SCR_reg(data)   (*((volatile unsigned int*) MIS_U1SCR_reg)=data)
#define get_MIS_U1SCR_reg   (*((volatile unsigned int*) MIS_U1SCR_reg))
#define MIS_U1SCR_inst_adr                                                           "0x0087"
#define MIS_U1SCR_inst                                                               0x0087
#define MIS_U1SCR_scr_shift                                                          (0)
#define MIS_U1SCR_scr_mask                                                           (0x000000FF)
#define MIS_U1SCR_scr(data)                                                          (0x000000FF&((data)<<0))
#define MIS_U1SCR_scr_src(data)                                                      ((0x000000FF&(data))>>0)
#define MIS_U1SCR_get_scr(data)                                                      ((0x000000FF&(data))>>0)


#define MIS_U1SRBR_0                                                                 0x1801B230
#define MIS_U1SRBR_1                                                                 0x1801B234
#define MIS_U1SRBR_2                                                                 0x1801B238
#define MIS_U1SRBR_3                                                                 0x1801B23C
#define MIS_U1SRBR_4                                                                 0x1801B240
#define MIS_U1SRBR_5                                                                 0x1801B244
#define MIS_U1SRBR_6                                                                 0x1801B248
#define MIS_U1SRBR_7                                                                 0x1801B24C
#define MIS_U1SRBR_8                                                                 0x1801B250
#define MIS_U1SRBR_9                                                                 0x1801B254
#define MIS_U1SRBR_10                                                                 0x1801B258
#define MIS_U1SRBR_11                                                                 0x1801B25C
#define MIS_U1SRBR_12                                                                 0x1801B260
#define MIS_U1SRBR_13                                                                 0x1801B264
#define MIS_U1SRBR_14                                                                 0x1801B268
#define MIS_U1SRBR_15                                                                 0x1801B26C
#define MIS_U1SRBR_0_reg_addr                                                        "0xB801B230"
#define MIS_U1SRBR_1_reg_addr                                                        "0xB801B234"
#define MIS_U1SRBR_2_reg_addr                                                        "0xB801B238"
#define MIS_U1SRBR_3_reg_addr                                                        "0xB801B23C"
#define MIS_U1SRBR_4_reg_addr                                                        "0xB801B240"
#define MIS_U1SRBR_5_reg_addr                                                        "0xB801B244"
#define MIS_U1SRBR_6_reg_addr                                                        "0xB801B248"
#define MIS_U1SRBR_7_reg_addr                                                        "0xB801B24C"
#define MIS_U1SRBR_8_reg_addr                                                        "0xB801B250"
#define MIS_U1SRBR_9_reg_addr                                                        "0xB801B254"
#define MIS_U1SRBR_10_reg_addr                                                        "0xB801B258"
#define MIS_U1SRBR_11_reg_addr                                                        "0xB801B25C"
#define MIS_U1SRBR_12_reg_addr                                                        "0xB801B260"
#define MIS_U1SRBR_13_reg_addr                                                        "0xB801B264"
#define MIS_U1SRBR_14_reg_addr                                                        "0xB801B268"
#define MIS_U1SRBR_15_reg_addr                                                        "0xB801B26C"
#define MIS_U1SRBR_0_reg                                                             0xB801B230
#define MIS_U1SRBR_1_reg                                                             0xB801B234
#define MIS_U1SRBR_2_reg                                                             0xB801B238
#define MIS_U1SRBR_3_reg                                                             0xB801B23C
#define MIS_U1SRBR_4_reg                                                             0xB801B240
#define MIS_U1SRBR_5_reg                                                             0xB801B244
#define MIS_U1SRBR_6_reg                                                             0xB801B248
#define MIS_U1SRBR_7_reg                                                             0xB801B24C
#define MIS_U1SRBR_8_reg                                                             0xB801B250
#define MIS_U1SRBR_9_reg                                                             0xB801B254
#define MIS_U1SRBR_10_reg                                                             0xB801B258
#define MIS_U1SRBR_11_reg                                                             0xB801B25C
#define MIS_U1SRBR_12_reg                                                             0xB801B260
#define MIS_U1SRBR_13_reg                                                             0xB801B264
#define MIS_U1SRBR_14_reg                                                             0xB801B268
#define MIS_U1SRBR_15_reg                                                             0xB801B26C
#define set_MIS_U1SRBR_0_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_0_reg)=data)
#define set_MIS_U1SRBR_1_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_1_reg)=data)
#define set_MIS_U1SRBR_2_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_2_reg)=data)
#define set_MIS_U1SRBR_3_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_3_reg)=data)
#define set_MIS_U1SRBR_4_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_4_reg)=data)
#define set_MIS_U1SRBR_5_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_5_reg)=data)
#define set_MIS_U1SRBR_6_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_6_reg)=data)
#define set_MIS_U1SRBR_7_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_7_reg)=data)
#define set_MIS_U1SRBR_8_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_8_reg)=data)
#define set_MIS_U1SRBR_9_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_9_reg)=data)
#define set_MIS_U1SRBR_10_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_10_reg)=data)
#define set_MIS_U1SRBR_11_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_11_reg)=data)
#define set_MIS_U1SRBR_12_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_12_reg)=data)
#define set_MIS_U1SRBR_13_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_13_reg)=data)
#define set_MIS_U1SRBR_14_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_14_reg)=data)
#define set_MIS_U1SRBR_15_reg(data)   (*((volatile unsigned int*) MIS_U1SRBR_15_reg)=data)
#define get_MIS_U1SRBR_0_reg   (*((volatile unsigned int*) MIS_U1SRBR_0_reg))
#define get_MIS_U1SRBR_1_reg   (*((volatile unsigned int*) MIS_U1SRBR_1_reg))
#define get_MIS_U1SRBR_2_reg   (*((volatile unsigned int*) MIS_U1SRBR_2_reg))
#define get_MIS_U1SRBR_3_reg   (*((volatile unsigned int*) MIS_U1SRBR_3_reg))
#define get_MIS_U1SRBR_4_reg   (*((volatile unsigned int*) MIS_U1SRBR_4_reg))
#define get_MIS_U1SRBR_5_reg   (*((volatile unsigned int*) MIS_U1SRBR_5_reg))
#define get_MIS_U1SRBR_6_reg   (*((volatile unsigned int*) MIS_U1SRBR_6_reg))
#define get_MIS_U1SRBR_7_reg   (*((volatile unsigned int*) MIS_U1SRBR_7_reg))
#define get_MIS_U1SRBR_8_reg   (*((volatile unsigned int*) MIS_U1SRBR_8_reg))
#define get_MIS_U1SRBR_9_reg   (*((volatile unsigned int*) MIS_U1SRBR_9_reg))
#define get_MIS_U1SRBR_10_reg   (*((volatile unsigned int*) MIS_U1SRBR_10_reg))
#define get_MIS_U1SRBR_11_reg   (*((volatile unsigned int*) MIS_U1SRBR_11_reg))
#define get_MIS_U1SRBR_12_reg   (*((volatile unsigned int*) MIS_U1SRBR_12_reg))
#define get_MIS_U1SRBR_13_reg   (*((volatile unsigned int*) MIS_U1SRBR_13_reg))
#define get_MIS_U1SRBR_14_reg   (*((volatile unsigned int*) MIS_U1SRBR_14_reg))
#define get_MIS_U1SRBR_15_reg   (*((volatile unsigned int*) MIS_U1SRBR_15_reg))
#define MIS_U1SRBR_0_inst_adr                                                        "0x008C"
#define MIS_U1SRBR_1_inst_adr                                                        "0x008D"
#define MIS_U1SRBR_2_inst_adr                                                        "0x008E"
#define MIS_U1SRBR_3_inst_adr                                                        "0x008F"
#define MIS_U1SRBR_4_inst_adr                                                        "0x0090"
#define MIS_U1SRBR_5_inst_adr                                                        "0x0091"
#define MIS_U1SRBR_6_inst_adr                                                        "0x0092"
#define MIS_U1SRBR_7_inst_adr                                                        "0x0093"
#define MIS_U1SRBR_8_inst_adr                                                        "0x0094"
#define MIS_U1SRBR_9_inst_adr                                                        "0x0095"
#define MIS_U1SRBR_10_inst_adr                                                        "0x0096"
#define MIS_U1SRBR_11_inst_adr                                                        "0x0097"
#define MIS_U1SRBR_12_inst_adr                                                        "0x0098"
#define MIS_U1SRBR_13_inst_adr                                                        "0x0099"
#define MIS_U1SRBR_14_inst_adr                                                        "0x009A"
#define MIS_U1SRBR_15_inst_adr                                                        "0x009B"
#define MIS_U1SRBR_0_inst                                                            0x008C
#define MIS_U1SRBR_1_inst                                                            0x008D
#define MIS_U1SRBR_2_inst                                                            0x008E
#define MIS_U1SRBR_3_inst                                                            0x008F
#define MIS_U1SRBR_4_inst                                                            0x0090
#define MIS_U1SRBR_5_inst                                                            0x0091
#define MIS_U1SRBR_6_inst                                                            0x0092
#define MIS_U1SRBR_7_inst                                                            0x0093
#define MIS_U1SRBR_8_inst                                                            0x0094
#define MIS_U1SRBR_9_inst                                                            0x0095
#define MIS_U1SRBR_10_inst                                                            0x0096
#define MIS_U1SRBR_11_inst                                                            0x0097
#define MIS_U1SRBR_12_inst                                                            0x0098
#define MIS_U1SRBR_13_inst                                                            0x0099
#define MIS_U1SRBR_14_inst                                                            0x009A
#define MIS_U1SRBR_15_inst                                                            0x009B
#define MIS_U1SRBR_rbd_shift                                                         (0)
#define MIS_U1SRBR_rbd_mask                                                          (0x000000FF)
#define MIS_U1SRBR_rbd(data)                                                         (0x000000FF&((data)<<0))
#define MIS_U1SRBR_rbd_src(data)                                                     ((0x000000FF&(data))>>0)
#define MIS_U1SRBR_get_rbd(data)                                                     ((0x000000FF&(data))>>0)


#define MIS_U1FAR                                                                    0x1801B270
#define MIS_U1FAR_reg_addr                                                           "0xB801B270"
#define MIS_U1FAR_reg                                                                0xB801B270
#define set_MIS_U1FAR_reg(data)   (*((volatile unsigned int*) MIS_U1FAR_reg)=data)
#define get_MIS_U1FAR_reg   (*((volatile unsigned int*) MIS_U1FAR_reg))
#define MIS_U1FAR_inst_adr                                                           "0x009C"
#define MIS_U1FAR_inst                                                               0x009C
#define MIS_U1FAR_far_shift                                                          (0)
#define MIS_U1FAR_far_mask                                                           (0x00000001)
#define MIS_U1FAR_far(data)                                                          (0x00000001&((data)<<0))
#define MIS_U1FAR_far_src(data)                                                      ((0x00000001&(data))>>0)
#define MIS_U1FAR_get_far(data)                                                      ((0x00000001&(data))>>0)


#define MIS_U1TFR                                                                    0x1801B274
#define MIS_U1TFR_reg_addr                                                           "0xB801B274"
#define MIS_U1TFR_reg                                                                0xB801B274
#define set_MIS_U1TFR_reg(data)   (*((volatile unsigned int*) MIS_U1TFR_reg)=data)
#define get_MIS_U1TFR_reg   (*((volatile unsigned int*) MIS_U1TFR_reg))
#define MIS_U1TFR_inst_adr                                                           "0x009D"
#define MIS_U1TFR_inst                                                               0x009D
#define MIS_U1TFR_far_shift                                                          (0)
#define MIS_U1TFR_far_mask                                                           (0x000000FF)
#define MIS_U1TFR_far(data)                                                          (0x000000FF&((data)<<0))
#define MIS_U1TFR_far_src(data)                                                      ((0x000000FF&(data))>>0)
#define MIS_U1TFR_get_far(data)                                                      ((0x000000FF&(data))>>0)


#define MIS_U1RFW                                                                    0x1801B278
#define MIS_U1RFW_reg_addr                                                           "0xB801B278"
#define MIS_U1RFW_reg                                                                0xB801B278
#define set_MIS_U1RFW_reg(data)   (*((volatile unsigned int*) MIS_U1RFW_reg)=data)
#define get_MIS_U1RFW_reg   (*((volatile unsigned int*) MIS_U1RFW_reg))
#define MIS_U1RFW_inst_adr                                                           "0x009E"
#define MIS_U1RFW_inst                                                               0x009E
#define MIS_U1RFW_rffe_shift                                                         (9)
#define MIS_U1RFW_rffe_mask                                                          (0x00000200)
#define MIS_U1RFW_rffe(data)                                                         (0x00000200&((data)<<9))
#define MIS_U1RFW_rffe_src(data)                                                     ((0x00000200&(data))>>9)
#define MIS_U1RFW_get_rffe(data)                                                     ((0x00000200&(data))>>9)
#define MIS_U1RFW_rfpf_shift                                                         (8)
#define MIS_U1RFW_rfpf_mask                                                          (0x00000100)
#define MIS_U1RFW_rfpf(data)                                                         (0x00000100&((data)<<8))
#define MIS_U1RFW_rfpf_src(data)                                                     ((0x00000100&(data))>>8)
#define MIS_U1RFW_get_rfpf(data)                                                     ((0x00000100&(data))>>8)
#define MIS_U1RFW_rfwd_shift                                                         (0)
#define MIS_U1RFW_rfwd_mask                                                          (0x000000FF)
#define MIS_U1RFW_rfwd(data)                                                         (0x000000FF&((data)<<0))
#define MIS_U1RFW_rfwd_src(data)                                                     ((0x000000FF&(data))>>0)
#define MIS_U1RFW_get_rfwd(data)                                                     ((0x000000FF&(data))>>0)


#define MIS_U1USR                                                                    0x1801B27C
#define MIS_U1USR_reg_addr                                                           "0xB801B27C"
#define MIS_U1USR_reg                                                                0xB801B27C
#define set_MIS_U1USR_reg(data)   (*((volatile unsigned int*) MIS_U1USR_reg)=data)
#define get_MIS_U1USR_reg   (*((volatile unsigned int*) MIS_U1USR_reg))
#define MIS_U1USR_inst_adr                                                           "0x009F"
#define MIS_U1USR_inst                                                               0x009F
#define MIS_U1USR_rff_shift                                                          (4)
#define MIS_U1USR_rff_mask                                                           (0x00000010)
#define MIS_U1USR_rff(data)                                                          (0x00000010&((data)<<4))
#define MIS_U1USR_rff_src(data)                                                      ((0x00000010&(data))>>4)
#define MIS_U1USR_get_rff(data)                                                      ((0x00000010&(data))>>4)
#define MIS_U1USR_rfne_shift                                                         (3)
#define MIS_U1USR_rfne_mask                                                          (0x00000008)
#define MIS_U1USR_rfne(data)                                                         (0x00000008&((data)<<3))
#define MIS_U1USR_rfne_src(data)                                                     ((0x00000008&(data))>>3)
#define MIS_U1USR_get_rfne(data)                                                     ((0x00000008&(data))>>3)
#define MIS_U1USR_tfe_shift                                                          (2)
#define MIS_U1USR_tfe_mask                                                           (0x00000004)
#define MIS_U1USR_tfe(data)                                                          (0x00000004&((data)<<2))
#define MIS_U1USR_tfe_src(data)                                                      ((0x00000004&(data))>>2)
#define MIS_U1USR_get_tfe(data)                                                      ((0x00000004&(data))>>2)
#define MIS_U1USR_tfnf_shift                                                         (1)
#define MIS_U1USR_tfnf_mask                                                          (0x00000002)
#define MIS_U1USR_tfnf(data)                                                         (0x00000002&((data)<<1))
#define MIS_U1USR_tfnf_src(data)                                                     ((0x00000002&(data))>>1)
#define MIS_U1USR_get_tfnf(data)                                                     ((0x00000002&(data))>>1)
#define MIS_U1USR_busy_shift                                                         (0)
#define MIS_U1USR_busy_mask                                                          (0x00000001)
#define MIS_U1USR_busy(data)                                                         (0x00000001&((data)<<0))
#define MIS_U1USR_busy_src(data)                                                     ((0x00000001&(data))>>0)
#define MIS_U1USR_get_busy(data)                                                     ((0x00000001&(data))>>0)


#define MIS_U1TFL                                                                    0x1801B280
#define MIS_U1TFL_reg_addr                                                           "0xB801B280"
#define MIS_U1TFL_reg                                                                0xB801B280
#define set_MIS_U1TFL_reg(data)   (*((volatile unsigned int*) MIS_U1TFL_reg)=data)
#define get_MIS_U1TFL_reg   (*((volatile unsigned int*) MIS_U1TFL_reg))
#define MIS_U1TFL_inst_adr                                                           "0x00A0"
#define MIS_U1TFL_inst                                                               0x00A0
#define MIS_U1TFL_tfl_shift                                                          (0)
#define MIS_U1TFL_tfl_mask                                                           (0x000000FF)
#define MIS_U1TFL_tfl(data)                                                          (0x000000FF&((data)<<0))
#define MIS_U1TFL_tfl_src(data)                                                      ((0x000000FF&(data))>>0)
#define MIS_U1TFL_get_tfl(data)                                                      ((0x000000FF&(data))>>0)


#define MIS_U1RFL                                                                    0x1801B284
#define MIS_U1RFL_reg_addr                                                           "0xB801B284"
#define MIS_U1RFL_reg                                                                0xB801B284
#define set_MIS_U1RFL_reg(data)   (*((volatile unsigned int*) MIS_U1RFL_reg)=data)
#define get_MIS_U1RFL_reg   (*((volatile unsigned int*) MIS_U1RFL_reg))
#define MIS_U1RFL_inst_adr                                                           "0x00A1"
#define MIS_U1RFL_inst                                                               0x00A1
#define MIS_U1RFL_rfl_shift                                                          (0)
#define MIS_U1RFL_rfl_mask                                                           (0x000000FF)
#define MIS_U1RFL_rfl(data)                                                          (0x000000FF&((data)<<0))
#define MIS_U1RFL_rfl_src(data)                                                      ((0x000000FF&(data))>>0)
#define MIS_U1RFL_get_rfl(data)                                                      ((0x000000FF&(data))>>0)


#define MIS_U1SRR                                                                    0x1801B288
#define MIS_U1SRR_reg_addr                                                           "0xB801B288"
#define MIS_U1SRR_reg                                                                0xB801B288
#define set_MIS_U1SRR_reg(data)   (*((volatile unsigned int*) MIS_U1SRR_reg)=data)
#define get_MIS_U1SRR_reg   (*((volatile unsigned int*) MIS_U1SRR_reg))
#define MIS_U1SRR_inst_adr                                                           "0x00A2"
#define MIS_U1SRR_inst                                                               0x00A2
#define MIS_U1SRR_xfr_shift                                                          (2)
#define MIS_U1SRR_xfr_mask                                                           (0x00000004)
#define MIS_U1SRR_xfr(data)                                                          (0x00000004&((data)<<2))
#define MIS_U1SRR_xfr_src(data)                                                      ((0x00000004&(data))>>2)
#define MIS_U1SRR_get_xfr(data)                                                      ((0x00000004&(data))>>2)
#define MIS_U1SRR_rfr_shift                                                          (1)
#define MIS_U1SRR_rfr_mask                                                           (0x00000002)
#define MIS_U1SRR_rfr(data)                                                          (0x00000002&((data)<<1))
#define MIS_U1SRR_rfr_src(data)                                                      ((0x00000002&(data))>>1)
#define MIS_U1SRR_get_rfr(data)                                                      ((0x00000002&(data))>>1)
#define MIS_U1SRR_ur_shift                                                           (0)
#define MIS_U1SRR_ur_mask                                                            (0x00000001)
#define MIS_U1SRR_ur(data)                                                           (0x00000001&((data)<<0))
#define MIS_U1SRR_ur_src(data)                                                       ((0x00000001&(data))>>0)
#define MIS_U1SRR_get_ur(data)                                                       ((0x00000001&(data))>>0)


#define MIS_U1SBCR                                                                   0x1801B290
#define MIS_U1SBCR_reg_addr                                                          "0xB801B290"
#define MIS_U1SBCR_reg                                                               0xB801B290
#define set_MIS_U1SBCR_reg(data)   (*((volatile unsigned int*) MIS_U1SBCR_reg)=data)
#define get_MIS_U1SBCR_reg   (*((volatile unsigned int*) MIS_U1SBCR_reg))
#define MIS_U1SBCR_inst_adr                                                          "0x00A4"
#define MIS_U1SBCR_inst                                                              0x00A4
#define MIS_U1SBCR_sbcr_shift                                                        (0)
#define MIS_U1SBCR_sbcr_mask                                                         (0x00000001)
#define MIS_U1SBCR_sbcr(data)                                                        (0x00000001&((data)<<0))
#define MIS_U1SBCR_sbcr_src(data)                                                    ((0x00000001&(data))>>0)
#define MIS_U1SBCR_get_sbcr(data)                                                    ((0x00000001&(data))>>0)


#define MIS_U1SDMAM                                                                  0x1801B294
#define MIS_U1SDMAM_reg_addr                                                         "0xB801B294"
#define MIS_U1SDMAM_reg                                                              0xB801B294
#define set_MIS_U1SDMAM_reg(data)   (*((volatile unsigned int*) MIS_U1SDMAM_reg)=data)
#define get_MIS_U1SDMAM_reg   (*((volatile unsigned int*) MIS_U1SDMAM_reg))
#define MIS_U1SDMAM_inst_adr                                                         "0x00A5"
#define MIS_U1SDMAM_inst                                                             0x00A5
#define MIS_U1SDMAM_sdmam_shift                                                      (0)
#define MIS_U1SDMAM_sdmam_mask                                                       (0x00000001)
#define MIS_U1SDMAM_sdmam(data)                                                      (0x00000001&((data)<<0))
#define MIS_U1SDMAM_sdmam_src(data)                                                  ((0x00000001&(data))>>0)
#define MIS_U1SDMAM_get_sdmam(data)                                                  ((0x00000001&(data))>>0)


#define MIS_U1SFE                                                                    0x1801B298
#define MIS_U1SFE_reg_addr                                                           "0xB801B298"
#define MIS_U1SFE_reg                                                                0xB801B298
#define set_MIS_U1SFE_reg(data)   (*((volatile unsigned int*) MIS_U1SFE_reg)=data)
#define get_MIS_U1SFE_reg   (*((volatile unsigned int*) MIS_U1SFE_reg))
#define MIS_U1SFE_inst_adr                                                           "0x00A6"
#define MIS_U1SFE_inst                                                               0x00A6
#define MIS_U1SFE_sfe_shift                                                          (0)
#define MIS_U1SFE_sfe_mask                                                           (0x00000001)
#define MIS_U1SFE_sfe(data)                                                          (0x00000001&((data)<<0))
#define MIS_U1SFE_sfe_src(data)                                                      ((0x00000001&(data))>>0)
#define MIS_U1SFE_get_sfe(data)                                                      ((0x00000001&(data))>>0)


#define MIS_U1SRT                                                                    0x1801B29C
#define MIS_U1SRT_reg_addr                                                           "0xB801B29C"
#define MIS_U1SRT_reg                                                                0xB801B29C
#define set_MIS_U1SRT_reg(data)   (*((volatile unsigned int*) MIS_U1SRT_reg)=data)
#define get_MIS_U1SRT_reg   (*((volatile unsigned int*) MIS_U1SRT_reg))
#define MIS_U1SRT_inst_adr                                                           "0x00A7"
#define MIS_U1SRT_inst                                                               0x00A7
#define MIS_U1SRT_srt_shift                                                          (0)
#define MIS_U1SRT_srt_mask                                                           (0x00000003)
#define MIS_U1SRT_srt(data)                                                          (0x00000003&((data)<<0))
#define MIS_U1SRT_srt_src(data)                                                      ((0x00000003&(data))>>0)
#define MIS_U1SRT_get_srt(data)                                                      ((0x00000003&(data))>>0)


#define MIS_U1STET                                                                   0x1801B2A0
#define MIS_U1STET_reg_addr                                                          "0xB801B2A0"
#define MIS_U1STET_reg                                                               0xB801B2A0
#define set_MIS_U1STET_reg(data)   (*((volatile unsigned int*) MIS_U1STET_reg)=data)
#define get_MIS_U1STET_reg   (*((volatile unsigned int*) MIS_U1STET_reg))
#define MIS_U1STET_inst_adr                                                          "0x00A8"
#define MIS_U1STET_inst                                                              0x00A8
#define MIS_U1STET_stet_shift                                                        (0)
#define MIS_U1STET_stet_mask                                                         (0x00000003)
#define MIS_U1STET_stet(data)                                                        (0x00000003&((data)<<0))
#define MIS_U1STET_stet_src(data)                                                    ((0x00000003&(data))>>0)
#define MIS_U1STET_get_stet(data)                                                    ((0x00000003&(data))>>0)


#define MIS_U1HTX                                                                    0x1801B2A4
#define MIS_U1HTX_reg_addr                                                           "0xB801B2A4"
#define MIS_U1HTX_reg                                                                0xB801B2A4
#define set_MIS_U1HTX_reg(data)   (*((volatile unsigned int*) MIS_U1HTX_reg)=data)
#define get_MIS_U1HTX_reg   (*((volatile unsigned int*) MIS_U1HTX_reg))
#define MIS_U1HTX_inst_adr                                                           "0x00A9"
#define MIS_U1HTX_inst                                                               0x00A9
#define MIS_U1HTX_htx_shift                                                          (0)
#define MIS_U1HTX_htx_mask                                                           (0x00000001)
#define MIS_U1HTX_htx(data)                                                          (0x00000001&((data)<<0))
#define MIS_U1HTX_htx_src(data)                                                      ((0x00000001&(data))>>0)
#define MIS_U1HTX_get_htx(data)                                                      ((0x00000001&(data))>>0)


#define MIS_U1DMASA                                                                  0x1801B2A8
#define MIS_U1DMASA_reg_addr                                                         "0xB801B2A8"
#define MIS_U1DMASA_reg                                                              0xB801B2A8
#define set_MIS_U1DMASA_reg(data)   (*((volatile unsigned int*) MIS_U1DMASA_reg)=data)
#define get_MIS_U1DMASA_reg   (*((volatile unsigned int*) MIS_U1DMASA_reg))
#define MIS_U1DMASA_inst_adr                                                         "0x00AA"
#define MIS_U1DMASA_inst                                                             0x00AA
#define MIS_U1DMASA_dmasa_shift                                                      (0)
#define MIS_U1DMASA_dmasa_mask                                                       (0x00000001)
#define MIS_U1DMASA_dmasa(data)                                                      (0x00000001&((data)<<0))
#define MIS_U1DMASA_dmasa_src(data)                                                  ((0x00000001&(data))>>0)
#define MIS_U1DMASA_get_dmasa(data)                                                  ((0x00000001&(data))>>0)


#define MIS_U1CPR                                                                    0x1801B2F4
#define MIS_U1CPR_reg_addr                                                           "0xB801B2F4"
#define MIS_U1CPR_reg                                                                0xB801B2F4
#define set_MIS_U1CPR_reg(data)   (*((volatile unsigned int*) MIS_U1CPR_reg)=data)
#define get_MIS_U1CPR_reg   (*((volatile unsigned int*) MIS_U1CPR_reg))
#define MIS_U1CPR_inst_adr                                                           "0x00BD"
#define MIS_U1CPR_inst                                                               0x00BD
#define MIS_U1CPR_fifo_mode_shift                                                    (16)
#define MIS_U1CPR_fifo_mode_mask                                                     (0x00FF0000)
#define MIS_U1CPR_fifo_mode(data)                                                    (0x00FF0000&((data)<<16))
#define MIS_U1CPR_fifo_mode_src(data)                                                ((0x00FF0000&(data))>>16)
#define MIS_U1CPR_get_fifo_mode(data)                                                ((0x00FF0000&(data))>>16)
#define MIS_U1CPR_dma_extra_shift                                                    (13)
#define MIS_U1CPR_dma_extra_mask                                                     (0x00002000)
#define MIS_U1CPR_dma_extra(data)                                                    (0x00002000&((data)<<13))
#define MIS_U1CPR_dma_extra_src(data)                                                ((0x00002000&(data))>>13)
#define MIS_U1CPR_get_dma_extra(data)                                                ((0x00002000&(data))>>13)
#define MIS_U1CPR_uart_add_encoded_params_shift                                      (12)
#define MIS_U1CPR_uart_add_encoded_params_mask                                       (0x00001000)
#define MIS_U1CPR_uart_add_encoded_params(data)                                      (0x00001000&((data)<<12))
#define MIS_U1CPR_uart_add_encoded_params_src(data)                                  ((0x00001000&(data))>>12)
#define MIS_U1CPR_get_uart_add_encoded_params(data)                                  ((0x00001000&(data))>>12)
#define MIS_U1CPR_shadow_shift                                                       (11)
#define MIS_U1CPR_shadow_mask                                                        (0x00000800)
#define MIS_U1CPR_shadow(data)                                                       (0x00000800&((data)<<11))
#define MIS_U1CPR_shadow_src(data)                                                   ((0x00000800&(data))>>11)
#define MIS_U1CPR_get_shadow(data)                                                   ((0x00000800&(data))>>11)
#define MIS_U1CPR_fifo_stat_shift                                                    (10)
#define MIS_U1CPR_fifo_stat_mask                                                     (0x00000400)
#define MIS_U1CPR_fifo_stat(data)                                                    (0x00000400&((data)<<10))
#define MIS_U1CPR_fifo_stat_src(data)                                                ((0x00000400&(data))>>10)
#define MIS_U1CPR_get_fifo_stat(data)                                                ((0x00000400&(data))>>10)
#define MIS_U1CPR_fifo_access_shift                                                  (9)
#define MIS_U1CPR_fifo_access_mask                                                   (0x00000200)
#define MIS_U1CPR_fifo_access(data)                                                  (0x00000200&((data)<<9))
#define MIS_U1CPR_fifo_access_src(data)                                              ((0x00000200&(data))>>9)
#define MIS_U1CPR_get_fifo_access(data)                                              ((0x00000200&(data))>>9)
#define MIS_U1CPR_additional_feat_shift                                              (8)
#define MIS_U1CPR_additional_feat_mask                                               (0x00000100)
#define MIS_U1CPR_additional_feat(data)                                              (0x00000100&((data)<<8))
#define MIS_U1CPR_additional_feat_src(data)                                          ((0x00000100&(data))>>8)
#define MIS_U1CPR_get_additional_feat(data)                                          ((0x00000100&(data))>>8)
#define MIS_U1CPR_sir_lp_mode_shift                                                  (7)
#define MIS_U1CPR_sir_lp_mode_mask                                                   (0x00000080)
#define MIS_U1CPR_sir_lp_mode(data)                                                  (0x00000080&((data)<<7))
#define MIS_U1CPR_sir_lp_mode_src(data)                                              ((0x00000080&(data))>>7)
#define MIS_U1CPR_get_sir_lp_mode(data)                                              ((0x00000080&(data))>>7)
#define MIS_U1CPR_sir_mode_shift                                                     (6)
#define MIS_U1CPR_sir_mode_mask                                                      (0x00000040)
#define MIS_U1CPR_sir_mode(data)                                                     (0x00000040&((data)<<6))
#define MIS_U1CPR_sir_mode_src(data)                                                 ((0x00000040&(data))>>6)
#define MIS_U1CPR_get_sir_mode(data)                                                 ((0x00000040&(data))>>6)
#define MIS_U1CPR_thre_mode_shift                                                    (5)
#define MIS_U1CPR_thre_mode_mask                                                     (0x00000020)
#define MIS_U1CPR_thre_mode(data)                                                    (0x00000020&((data)<<5))
#define MIS_U1CPR_thre_mode_src(data)                                                ((0x00000020&(data))>>5)
#define MIS_U1CPR_get_thre_mode(data)                                                ((0x00000020&(data))>>5)
#define MIS_U1CPR_afce_mode_shift                                                    (4)
#define MIS_U1CPR_afce_mode_mask                                                     (0x00000010)
#define MIS_U1CPR_afce_mode(data)                                                    (0x00000010&((data)<<4))
#define MIS_U1CPR_afce_mode_src(data)                                                ((0x00000010&(data))>>4)
#define MIS_U1CPR_get_afce_mode(data)                                                ((0x00000010&(data))>>4)
#define MIS_U1CPR_apb_data_width_shift                                               (0)
#define MIS_U1CPR_apb_data_width_mask                                                (0x00000003)
#define MIS_U1CPR_apb_data_width(data)                                               (0x00000003&((data)<<0))
#define MIS_U1CPR_apb_data_width_src(data)                                           ((0x00000003&(data))>>0)
#define MIS_U1CPR_get_apb_data_width(data)                                           ((0x00000003&(data))>>0)


#define MIS_U1UCV                                                                    0x1801B2F8
#define MIS_U1UCV_reg_addr                                                           "0xB801B2F8"
#define MIS_U1UCV_reg                                                                0xB801B2F8
#define set_MIS_U1UCV_reg(data)   (*((volatile unsigned int*) MIS_U1UCV_reg)=data)
#define get_MIS_U1UCV_reg   (*((volatile unsigned int*) MIS_U1UCV_reg))
#define MIS_U1UCV_inst_adr                                                           "0x00BE"
#define MIS_U1UCV_inst                                                               0x00BE
#define MIS_U1UCV_ucv_shift                                                          (0)
#define MIS_U1UCV_ucv_mask                                                           (0xFFFFFFFF)
#define MIS_U1UCV_ucv(data)                                                          (0xFFFFFFFF&((data)<<0))
#define MIS_U1UCV_ucv_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define MIS_U1UCV_get_ucv(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define MIS_U1CTR                                                                    0x1801B2FC
#define MIS_U1CTR_reg_addr                                                           "0xB801B2FC"
#define MIS_U1CTR_reg                                                                0xB801B2FC
#define set_MIS_U1CTR_reg(data)   (*((volatile unsigned int*) MIS_U1CTR_reg)=data)
#define get_MIS_U1CTR_reg   (*((volatile unsigned int*) MIS_U1CTR_reg))
#define MIS_U1CTR_inst_adr                                                           "0x00BF"
#define MIS_U1CTR_inst                                                               0x00BF
#define MIS_U1CTR_ctr_shift                                                          (0)
#define MIS_U1CTR_ctr_mask                                                           (0xFFFFFFFF)
#define MIS_U1CTR_ctr(data)                                                          (0xFFFFFFFF&((data)<<0))
#define MIS_U1CTR_ctr_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define MIS_U1CTR_get_ctr(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define MIS_IC1_CON                                                                  0x1801B300
#define MIS_IC1_CON_reg_addr                                                         "0xB801B300"
#define MIS_IC1_CON_reg                                                              0xB801B300
#define set_MIS_IC1_CON_reg(data)   (*((volatile unsigned int*) MIS_IC1_CON_reg)=data)
#define get_MIS_IC1_CON_reg   (*((volatile unsigned int*) MIS_IC1_CON_reg))
#define MIS_IC1_CON_inst_adr                                                         "0x00C0"
#define MIS_IC1_CON_inst                                                             0x00C0
#define MIS_IC1_CON_ic_slave_disable_shift                                           (6)
#define MIS_IC1_CON_ic_slave_disable_mask                                            (0x00000040)
#define MIS_IC1_CON_ic_slave_disable(data)                                           (0x00000040&((data)<<6))
#define MIS_IC1_CON_ic_slave_disable_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC1_CON_get_ic_slave_disable(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC1_CON_ic_restart_en_shift                                              (5)
#define MIS_IC1_CON_ic_restart_en_mask                                               (0x00000020)
#define MIS_IC1_CON_ic_restart_en(data)                                              (0x00000020&((data)<<5))
#define MIS_IC1_CON_ic_restart_en_src(data)                                          ((0x00000020&(data))>>5)
#define MIS_IC1_CON_get_ic_restart_en(data)                                          ((0x00000020&(data))>>5)
#define MIS_IC1_CON_ic_10bitaddr_master_shift                                        (4)
#define MIS_IC1_CON_ic_10bitaddr_master_mask                                         (0x00000010)
#define MIS_IC1_CON_ic_10bitaddr_master(data)                                        (0x00000010&((data)<<4))
#define MIS_IC1_CON_ic_10bitaddr_master_src(data)                                    ((0x00000010&(data))>>4)
#define MIS_IC1_CON_get_ic_10bitaddr_master(data)                                    ((0x00000010&(data))>>4)
#define MIS_IC1_CON_ic_10bitaddr_slave_shift                                         (3)
#define MIS_IC1_CON_ic_10bitaddr_slave_mask                                          (0x00000008)
#define MIS_IC1_CON_ic_10bitaddr_slave(data)                                         (0x00000008&((data)<<3))
#define MIS_IC1_CON_ic_10bitaddr_slave_src(data)                                     ((0x00000008&(data))>>3)
#define MIS_IC1_CON_get_ic_10bitaddr_slave(data)                                     ((0x00000008&(data))>>3)
#define MIS_IC1_CON_speed_shift                                                      (1)
#define MIS_IC1_CON_speed_mask                                                       (0x00000006)
#define MIS_IC1_CON_speed(data)                                                      (0x00000006&((data)<<1))
#define MIS_IC1_CON_speed_src(data)                                                  ((0x00000006&(data))>>1)
#define MIS_IC1_CON_get_speed(data)                                                  ((0x00000006&(data))>>1)
#define MIS_IC1_CON_master_mode_shift                                                (0)
#define MIS_IC1_CON_master_mode_mask                                                 (0x00000001)
#define MIS_IC1_CON_master_mode(data)                                                (0x00000001&((data)<<0))
#define MIS_IC1_CON_master_mode_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_IC1_CON_get_master_mode(data)                                            ((0x00000001&(data))>>0)


#define MIS_IC1_TAR                                                                  0x1801B304
#define MIS_IC1_TAR_reg_addr                                                         "0xB801B304"
#define MIS_IC1_TAR_reg                                                              0xB801B304
#define set_MIS_IC1_TAR_reg(data)   (*((volatile unsigned int*) MIS_IC1_TAR_reg)=data)
#define get_MIS_IC1_TAR_reg   (*((volatile unsigned int*) MIS_IC1_TAR_reg))
#define MIS_IC1_TAR_inst_adr                                                         "0x00C1"
#define MIS_IC1_TAR_inst                                                             0x00C1
#define MIS_IC1_TAR_ic_10bitaddr_master_shift                                        (12)
#define MIS_IC1_TAR_ic_10bitaddr_master_mask                                         (0x00001000)
#define MIS_IC1_TAR_ic_10bitaddr_master(data)                                        (0x00001000&((data)<<12))
#define MIS_IC1_TAR_ic_10bitaddr_master_src(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC1_TAR_get_ic_10bitaddr_master(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC1_TAR_special_shift                                                    (11)
#define MIS_IC1_TAR_special_mask                                                     (0x00000800)
#define MIS_IC1_TAR_special(data)                                                    (0x00000800&((data)<<11))
#define MIS_IC1_TAR_special_src(data)                                                ((0x00000800&(data))>>11)
#define MIS_IC1_TAR_get_special(data)                                                ((0x00000800&(data))>>11)
#define MIS_IC1_TAR_gc_or_start_shift                                                (10)
#define MIS_IC1_TAR_gc_or_start_mask                                                 (0x00000400)
#define MIS_IC1_TAR_gc_or_start(data)                                                (0x00000400&((data)<<10))
#define MIS_IC1_TAR_gc_or_start_src(data)                                            ((0x00000400&(data))>>10)
#define MIS_IC1_TAR_get_gc_or_start(data)                                            ((0x00000400&(data))>>10)
#define MIS_IC1_TAR_ic_tar_shift                                                     (0)
#define MIS_IC1_TAR_ic_tar_mask                                                      (0x000003FF)
#define MIS_IC1_TAR_ic_tar(data)                                                     (0x000003FF&((data)<<0))
#define MIS_IC1_TAR_ic_tar_src(data)                                                 ((0x000003FF&(data))>>0)
#define MIS_IC1_TAR_get_ic_tar(data)                                                 ((0x000003FF&(data))>>0)


#define MIS_IC1_SAR                                                                  0x1801B308
#define MIS_IC1_SAR_reg_addr                                                         "0xB801B308"
#define MIS_IC1_SAR_reg                                                              0xB801B308
#define set_MIS_IC1_SAR_reg(data)   (*((volatile unsigned int*) MIS_IC1_SAR_reg)=data)
#define get_MIS_IC1_SAR_reg   (*((volatile unsigned int*) MIS_IC1_SAR_reg))
#define MIS_IC1_SAR_inst_adr                                                         "0x00C2"
#define MIS_IC1_SAR_inst                                                             0x00C2
#define MIS_IC1_SAR_ic_sar_shift                                                     (0)
#define MIS_IC1_SAR_ic_sar_mask                                                      (0x000003FF)
#define MIS_IC1_SAR_ic_sar(data)                                                     (0x000003FF&((data)<<0))
#define MIS_IC1_SAR_ic_sar_src(data)                                                 ((0x000003FF&(data))>>0)
#define MIS_IC1_SAR_get_ic_sar(data)                                                 ((0x000003FF&(data))>>0)


#define MIS_IC1_HS_MADDR                                                             0x1801B30C
#define MIS_IC1_HS_MADDR_reg_addr                                                    "0xB801B30C"
#define MIS_IC1_HS_MADDR_reg                                                         0xB801B30C
#define set_MIS_IC1_HS_MADDR_reg(data)   (*((volatile unsigned int*) MIS_IC1_HS_MADDR_reg)=data)
#define get_MIS_IC1_HS_MADDR_reg   (*((volatile unsigned int*) MIS_IC1_HS_MADDR_reg))
#define MIS_IC1_HS_MADDR_inst_adr                                                    "0x00C3"
#define MIS_IC1_HS_MADDR_inst                                                        0x00C3
#define MIS_IC1_HS_MADDR_ic_hs_mar_shift                                             (0)
#define MIS_IC1_HS_MADDR_ic_hs_mar_mask                                              (0x00000007)
#define MIS_IC1_HS_MADDR_ic_hs_mar(data)                                             (0x00000007&((data)<<0))
#define MIS_IC1_HS_MADDR_ic_hs_mar_src(data)                                         ((0x00000007&(data))>>0)
#define MIS_IC1_HS_MADDR_get_ic_hs_mar(data)                                         ((0x00000007&(data))>>0)


#define MIS_IC1_DATA_CMD                                                             0x1801B310
#define MIS_IC1_DATA_CMD_reg_addr                                                    "0xB801B310"
#define MIS_IC1_DATA_CMD_reg                                                         0xB801B310
#define set_MIS_IC1_DATA_CMD_reg(data)   (*((volatile unsigned int*) MIS_IC1_DATA_CMD_reg)=data)
#define get_MIS_IC1_DATA_CMD_reg   (*((volatile unsigned int*) MIS_IC1_DATA_CMD_reg))
#define MIS_IC1_DATA_CMD_inst_adr                                                    "0x00C4"
#define MIS_IC1_DATA_CMD_inst                                                        0x00C4
#define MIS_IC1_DATA_CMD_restart_shift                                               (10)
#define MIS_IC1_DATA_CMD_restart_mask                                                (0x00000400)
#define MIS_IC1_DATA_CMD_restart(data)                                               (0x00000400&((data)<<10))
#define MIS_IC1_DATA_CMD_restart_src(data)                                           ((0x00000400&(data))>>10)
#define MIS_IC1_DATA_CMD_get_restart(data)                                           ((0x00000400&(data))>>10)
#define MIS_IC1_DATA_CMD_stop_shift                                                  (9)
#define MIS_IC1_DATA_CMD_stop_mask                                                   (0x00000200)
#define MIS_IC1_DATA_CMD_stop(data)                                                  (0x00000200&((data)<<9))
#define MIS_IC1_DATA_CMD_stop_src(data)                                              ((0x00000200&(data))>>9)
#define MIS_IC1_DATA_CMD_get_stop(data)                                              ((0x00000200&(data))>>9)
#define MIS_IC1_DATA_CMD_cmd_shift                                                   (8)
#define MIS_IC1_DATA_CMD_cmd_mask                                                    (0x00000100)
#define MIS_IC1_DATA_CMD_cmd(data)                                                   (0x00000100&((data)<<8))
#define MIS_IC1_DATA_CMD_cmd_src(data)                                               ((0x00000100&(data))>>8)
#define MIS_IC1_DATA_CMD_get_cmd(data)                                               ((0x00000100&(data))>>8)
#define MIS_IC1_DATA_CMD_dat_shift                                                   (0)
#define MIS_IC1_DATA_CMD_dat_mask                                                    (0x000000FF)
#define MIS_IC1_DATA_CMD_dat(data)                                                   (0x000000FF&((data)<<0))
#define MIS_IC1_DATA_CMD_dat_src(data)                                               ((0x000000FF&(data))>>0)
#define MIS_IC1_DATA_CMD_get_dat(data)                                               ((0x000000FF&(data))>>0)


#define MIS_IC1_SS_SCL_HCNT                                                          0x1801B314
#define MIS_IC1_SS_SCL_HCNT_reg_addr                                                 "0xB801B314"
#define MIS_IC1_SS_SCL_HCNT_reg                                                      0xB801B314
#define set_MIS_IC1_SS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) MIS_IC1_SS_SCL_HCNT_reg)=data)
#define get_MIS_IC1_SS_SCL_HCNT_reg   (*((volatile unsigned int*) MIS_IC1_SS_SCL_HCNT_reg))
#define MIS_IC1_SS_SCL_HCNT_inst_adr                                                 "0x00C5"
#define MIS_IC1_SS_SCL_HCNT_inst                                                     0x00C5
#define MIS_IC1_SS_SCL_HCNT_ic_ss_scl_hcnt_shift                                     (0)
#define MIS_IC1_SS_SCL_HCNT_ic_ss_scl_hcnt_mask                                      (0x0000FFFF)
#define MIS_IC1_SS_SCL_HCNT_ic_ss_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC1_SS_SCL_HCNT_ic_ss_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC1_SS_SCL_HCNT_get_ic_ss_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC1_SS_SCL_LCNT                                                          0x1801B318
#define MIS_IC1_SS_SCL_LCNT_reg_addr                                                 "0xB801B318"
#define MIS_IC1_SS_SCL_LCNT_reg                                                      0xB801B318
#define set_MIS_IC1_SS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) MIS_IC1_SS_SCL_LCNT_reg)=data)
#define get_MIS_IC1_SS_SCL_LCNT_reg   (*((volatile unsigned int*) MIS_IC1_SS_SCL_LCNT_reg))
#define MIS_IC1_SS_SCL_LCNT_inst_adr                                                 "0x00C6"
#define MIS_IC1_SS_SCL_LCNT_inst                                                     0x00C6
#define MIS_IC1_SS_SCL_LCNT_ic_ss_scl_lcnt_shift                                     (0)
#define MIS_IC1_SS_SCL_LCNT_ic_ss_scl_lcnt_mask                                      (0x0000FFFF)
#define MIS_IC1_SS_SCL_LCNT_ic_ss_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC1_SS_SCL_LCNT_ic_ss_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC1_SS_SCL_LCNT_get_ic_ss_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC1_FS_SCL_HCNT                                                          0x1801B31C
#define MIS_IC1_FS_SCL_HCNT_reg_addr                                                 "0xB801B31C"
#define MIS_IC1_FS_SCL_HCNT_reg                                                      0xB801B31C
#define set_MIS_IC1_FS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) MIS_IC1_FS_SCL_HCNT_reg)=data)
#define get_MIS_IC1_FS_SCL_HCNT_reg   (*((volatile unsigned int*) MIS_IC1_FS_SCL_HCNT_reg))
#define MIS_IC1_FS_SCL_HCNT_inst_adr                                                 "0x00C7"
#define MIS_IC1_FS_SCL_HCNT_inst                                                     0x00C7
#define MIS_IC1_FS_SCL_HCNT_ic_fs_scl_hcnt_shift                                     (0)
#define MIS_IC1_FS_SCL_HCNT_ic_fs_scl_hcnt_mask                                      (0x0000FFFF)
#define MIS_IC1_FS_SCL_HCNT_ic_fs_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC1_FS_SCL_HCNT_ic_fs_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC1_FS_SCL_HCNT_get_ic_fs_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC1_FS_SCL_LCNT                                                          0x1801B320
#define MIS_IC1_FS_SCL_LCNT_reg_addr                                                 "0xB801B320"
#define MIS_IC1_FS_SCL_LCNT_reg                                                      0xB801B320
#define set_MIS_IC1_FS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) MIS_IC1_FS_SCL_LCNT_reg)=data)
#define get_MIS_IC1_FS_SCL_LCNT_reg   (*((volatile unsigned int*) MIS_IC1_FS_SCL_LCNT_reg))
#define MIS_IC1_FS_SCL_LCNT_inst_adr                                                 "0x00C8"
#define MIS_IC1_FS_SCL_LCNT_inst                                                     0x00C8
#define MIS_IC1_FS_SCL_LCNT_ic_fs_scl_lcnt_shift                                     (0)
#define MIS_IC1_FS_SCL_LCNT_ic_fs_scl_lcnt_mask                                      (0x0000FFFF)
#define MIS_IC1_FS_SCL_LCNT_ic_fs_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC1_FS_SCL_LCNT_ic_fs_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC1_FS_SCL_LCNT_get_ic_fs_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC1_INTR_STAT                                                            0x1801B32C
#define MIS_IC1_INTR_STAT_reg_addr                                                   "0xB801B32C"
#define MIS_IC1_INTR_STAT_reg                                                        0xB801B32C
#define set_MIS_IC1_INTR_STAT_reg(data)   (*((volatile unsigned int*) MIS_IC1_INTR_STAT_reg)=data)
#define get_MIS_IC1_INTR_STAT_reg   (*((volatile unsigned int*) MIS_IC1_INTR_STAT_reg))
#define MIS_IC1_INTR_STAT_inst_adr                                                   "0x00CB"
#define MIS_IC1_INTR_STAT_inst                                                       0x00CB
#define MIS_IC1_INTR_STAT_r_gen_call_shift                                           (11)
#define MIS_IC1_INTR_STAT_r_gen_call_mask                                            (0x00000800)
#define MIS_IC1_INTR_STAT_r_gen_call(data)                                           (0x00000800&((data)<<11))
#define MIS_IC1_INTR_STAT_r_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC1_INTR_STAT_get_r_gen_call(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC1_INTR_STAT_r_start_det_shift                                          (10)
#define MIS_IC1_INTR_STAT_r_start_det_mask                                           (0x00000400)
#define MIS_IC1_INTR_STAT_r_start_det(data)                                          (0x00000400&((data)<<10))
#define MIS_IC1_INTR_STAT_r_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC1_INTR_STAT_get_r_start_det(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC1_INTR_STAT_r_stop_det_shift                                           (9)
#define MIS_IC1_INTR_STAT_r_stop_det_mask                                            (0x00000200)
#define MIS_IC1_INTR_STAT_r_stop_det(data)                                           (0x00000200&((data)<<9))
#define MIS_IC1_INTR_STAT_r_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC1_INTR_STAT_get_r_stop_det(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC1_INTR_STAT_r_activity_shift                                           (8)
#define MIS_IC1_INTR_STAT_r_activity_mask                                            (0x00000100)
#define MIS_IC1_INTR_STAT_r_activity(data)                                           (0x00000100&((data)<<8))
#define MIS_IC1_INTR_STAT_r_activity_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC1_INTR_STAT_get_r_activity(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC1_INTR_STAT_r_rx_done_shift                                            (7)
#define MIS_IC1_INTR_STAT_r_rx_done_mask                                             (0x00000080)
#define MIS_IC1_INTR_STAT_r_rx_done(data)                                            (0x00000080&((data)<<7))
#define MIS_IC1_INTR_STAT_r_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC1_INTR_STAT_get_r_rx_done(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC1_INTR_STAT_r_tx_abrt_shift                                            (6)
#define MIS_IC1_INTR_STAT_r_tx_abrt_mask                                             (0x00000040)
#define MIS_IC1_INTR_STAT_r_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define MIS_IC1_INTR_STAT_r_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC1_INTR_STAT_get_r_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC1_INTR_STAT_r_rd_req_shift                                             (5)
#define MIS_IC1_INTR_STAT_r_rd_req_mask                                              (0x00000020)
#define MIS_IC1_INTR_STAT_r_rd_req(data)                                             (0x00000020&((data)<<5))
#define MIS_IC1_INTR_STAT_r_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC1_INTR_STAT_get_r_rd_req(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC1_INTR_STAT_r_tx_empty_shift                                           (4)
#define MIS_IC1_INTR_STAT_r_tx_empty_mask                                            (0x00000010)
#define MIS_IC1_INTR_STAT_r_tx_empty(data)                                           (0x00000010&((data)<<4))
#define MIS_IC1_INTR_STAT_r_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC1_INTR_STAT_get_r_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC1_INTR_STAT_r_tx_over_shift                                            (3)
#define MIS_IC1_INTR_STAT_r_tx_over_mask                                             (0x00000008)
#define MIS_IC1_INTR_STAT_r_tx_over(data)                                            (0x00000008&((data)<<3))
#define MIS_IC1_INTR_STAT_r_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC1_INTR_STAT_get_r_tx_over(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC1_INTR_STAT_r_rx_full_shift                                            (2)
#define MIS_IC1_INTR_STAT_r_rx_full_mask                                             (0x00000004)
#define MIS_IC1_INTR_STAT_r_rx_full(data)                                            (0x00000004&((data)<<2))
#define MIS_IC1_INTR_STAT_r_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC1_INTR_STAT_get_r_rx_full(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC1_INTR_STAT_r_rx_over_shift                                            (1)
#define MIS_IC1_INTR_STAT_r_rx_over_mask                                             (0x00000002)
#define MIS_IC1_INTR_STAT_r_rx_over(data)                                            (0x00000002&((data)<<1))
#define MIS_IC1_INTR_STAT_r_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC1_INTR_STAT_get_r_rx_over(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC1_INTR_STAT_r_rx_under_shift                                           (0)
#define MIS_IC1_INTR_STAT_r_rx_under_mask                                            (0x00000001)
#define MIS_IC1_INTR_STAT_r_rx_under(data)                                           (0x00000001&((data)<<0))
#define MIS_IC1_INTR_STAT_r_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_IC1_INTR_STAT_get_r_rx_under(data)                                       ((0x00000001&(data))>>0)


#define MIS_IC1_INTR_MASK                                                            0x1801B330
#define MIS_IC1_INTR_MASK_reg_addr                                                   "0xB801B330"
#define MIS_IC1_INTR_MASK_reg                                                        0xB801B330
#define set_MIS_IC1_INTR_MASK_reg(data)   (*((volatile unsigned int*) MIS_IC1_INTR_MASK_reg)=data)
#define get_MIS_IC1_INTR_MASK_reg   (*((volatile unsigned int*) MIS_IC1_INTR_MASK_reg))
#define MIS_IC1_INTR_MASK_inst_adr                                                   "0x00CC"
#define MIS_IC1_INTR_MASK_inst                                                       0x00CC
#define MIS_IC1_INTR_MASK_m_gen_call_shift                                           (11)
#define MIS_IC1_INTR_MASK_m_gen_call_mask                                            (0x00000800)
#define MIS_IC1_INTR_MASK_m_gen_call(data)                                           (0x00000800&((data)<<11))
#define MIS_IC1_INTR_MASK_m_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC1_INTR_MASK_get_m_gen_call(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC1_INTR_MASK_m_start_det_shift                                          (10)
#define MIS_IC1_INTR_MASK_m_start_det_mask                                           (0x00000400)
#define MIS_IC1_INTR_MASK_m_start_det(data)                                          (0x00000400&((data)<<10))
#define MIS_IC1_INTR_MASK_m_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC1_INTR_MASK_get_m_start_det(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC1_INTR_MASK_m_stop_det_shift                                           (9)
#define MIS_IC1_INTR_MASK_m_stop_det_mask                                            (0x00000200)
#define MIS_IC1_INTR_MASK_m_stop_det(data)                                           (0x00000200&((data)<<9))
#define MIS_IC1_INTR_MASK_m_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC1_INTR_MASK_get_m_stop_det(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC1_INTR_MASK_m_activity_shift                                           (8)
#define MIS_IC1_INTR_MASK_m_activity_mask                                            (0x00000100)
#define MIS_IC1_INTR_MASK_m_activity(data)                                           (0x00000100&((data)<<8))
#define MIS_IC1_INTR_MASK_m_activity_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC1_INTR_MASK_get_m_activity(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC1_INTR_MASK_m_rx_done_shift                                            (7)
#define MIS_IC1_INTR_MASK_m_rx_done_mask                                             (0x00000080)
#define MIS_IC1_INTR_MASK_m_rx_done(data)                                            (0x00000080&((data)<<7))
#define MIS_IC1_INTR_MASK_m_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC1_INTR_MASK_get_m_rx_done(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC1_INTR_MASK_m_tx_abrt_shift                                            (6)
#define MIS_IC1_INTR_MASK_m_tx_abrt_mask                                             (0x00000040)
#define MIS_IC1_INTR_MASK_m_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define MIS_IC1_INTR_MASK_m_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC1_INTR_MASK_get_m_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC1_INTR_MASK_m_rd_req_shift                                             (5)
#define MIS_IC1_INTR_MASK_m_rd_req_mask                                              (0x00000020)
#define MIS_IC1_INTR_MASK_m_rd_req(data)                                             (0x00000020&((data)<<5))
#define MIS_IC1_INTR_MASK_m_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC1_INTR_MASK_get_m_rd_req(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC1_INTR_MASK_m_tx_empty_shift                                           (4)
#define MIS_IC1_INTR_MASK_m_tx_empty_mask                                            (0x00000010)
#define MIS_IC1_INTR_MASK_m_tx_empty(data)                                           (0x00000010&((data)<<4))
#define MIS_IC1_INTR_MASK_m_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC1_INTR_MASK_get_m_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC1_INTR_MASK_m_tx_over_shift                                            (3)
#define MIS_IC1_INTR_MASK_m_tx_over_mask                                             (0x00000008)
#define MIS_IC1_INTR_MASK_m_tx_over(data)                                            (0x00000008&((data)<<3))
#define MIS_IC1_INTR_MASK_m_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC1_INTR_MASK_get_m_tx_over(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC1_INTR_MASK_m_rx_full_shift                                            (2)
#define MIS_IC1_INTR_MASK_m_rx_full_mask                                             (0x00000004)
#define MIS_IC1_INTR_MASK_m_rx_full(data)                                            (0x00000004&((data)<<2))
#define MIS_IC1_INTR_MASK_m_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC1_INTR_MASK_get_m_rx_full(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC1_INTR_MASK_m_rx_over_shift                                            (1)
#define MIS_IC1_INTR_MASK_m_rx_over_mask                                             (0x00000002)
#define MIS_IC1_INTR_MASK_m_rx_over(data)                                            (0x00000002&((data)<<1))
#define MIS_IC1_INTR_MASK_m_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC1_INTR_MASK_get_m_rx_over(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC1_INTR_MASK_m_rx_under_shift                                           (0)
#define MIS_IC1_INTR_MASK_m_rx_under_mask                                            (0x00000001)
#define MIS_IC1_INTR_MASK_m_rx_under(data)                                           (0x00000001&((data)<<0))
#define MIS_IC1_INTR_MASK_m_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_IC1_INTR_MASK_get_m_rx_under(data)                                       ((0x00000001&(data))>>0)


#define MIS_IC1_RAW_INTR_STAT                                                        0x1801B334
#define MIS_IC1_RAW_INTR_STAT_reg_addr                                               "0xB801B334"
#define MIS_IC1_RAW_INTR_STAT_reg                                                    0xB801B334
#define set_MIS_IC1_RAW_INTR_STAT_reg(data)   (*((volatile unsigned int*) MIS_IC1_RAW_INTR_STAT_reg)=data)
#define get_MIS_IC1_RAW_INTR_STAT_reg   (*((volatile unsigned int*) MIS_IC1_RAW_INTR_STAT_reg))
#define MIS_IC1_RAW_INTR_STAT_inst_adr                                               "0x00CD"
#define MIS_IC1_RAW_INTR_STAT_inst                                                   0x00CD
#define MIS_IC1_RAW_INTR_STAT_gen_call_shift                                         (11)
#define MIS_IC1_RAW_INTR_STAT_gen_call_mask                                          (0x00000800)
#define MIS_IC1_RAW_INTR_STAT_gen_call(data)                                         (0x00000800&((data)<<11))
#define MIS_IC1_RAW_INTR_STAT_gen_call_src(data)                                     ((0x00000800&(data))>>11)
#define MIS_IC1_RAW_INTR_STAT_get_gen_call(data)                                     ((0x00000800&(data))>>11)
#define MIS_IC1_RAW_INTR_STAT_start_det_shift                                        (10)
#define MIS_IC1_RAW_INTR_STAT_start_det_mask                                         (0x00000400)
#define MIS_IC1_RAW_INTR_STAT_start_det(data)                                        (0x00000400&((data)<<10))
#define MIS_IC1_RAW_INTR_STAT_start_det_src(data)                                    ((0x00000400&(data))>>10)
#define MIS_IC1_RAW_INTR_STAT_get_start_det(data)                                    ((0x00000400&(data))>>10)
#define MIS_IC1_RAW_INTR_STAT_stop_det_shift                                         (9)
#define MIS_IC1_RAW_INTR_STAT_stop_det_mask                                          (0x00000200)
#define MIS_IC1_RAW_INTR_STAT_stop_det(data)                                         (0x00000200&((data)<<9))
#define MIS_IC1_RAW_INTR_STAT_stop_det_src(data)                                     ((0x00000200&(data))>>9)
#define MIS_IC1_RAW_INTR_STAT_get_stop_det(data)                                     ((0x00000200&(data))>>9)
#define MIS_IC1_RAW_INTR_STAT_activity_shift                                         (8)
#define MIS_IC1_RAW_INTR_STAT_activity_mask                                          (0x00000100)
#define MIS_IC1_RAW_INTR_STAT_activity(data)                                         (0x00000100&((data)<<8))
#define MIS_IC1_RAW_INTR_STAT_activity_src(data)                                     ((0x00000100&(data))>>8)
#define MIS_IC1_RAW_INTR_STAT_get_activity(data)                                     ((0x00000100&(data))>>8)
#define MIS_IC1_RAW_INTR_STAT_rx_done_shift                                          (7)
#define MIS_IC1_RAW_INTR_STAT_rx_done_mask                                           (0x00000080)
#define MIS_IC1_RAW_INTR_STAT_rx_done(data)                                          (0x00000080&((data)<<7))
#define MIS_IC1_RAW_INTR_STAT_rx_done_src(data)                                      ((0x00000080&(data))>>7)
#define MIS_IC1_RAW_INTR_STAT_get_rx_done(data)                                      ((0x00000080&(data))>>7)
#define MIS_IC1_RAW_INTR_STAT_tx_abrt_shift                                          (6)
#define MIS_IC1_RAW_INTR_STAT_tx_abrt_mask                                           (0x00000040)
#define MIS_IC1_RAW_INTR_STAT_tx_abrt(data)                                          (0x00000040&((data)<<6))
#define MIS_IC1_RAW_INTR_STAT_tx_abrt_src(data)                                      ((0x00000040&(data))>>6)
#define MIS_IC1_RAW_INTR_STAT_get_tx_abrt(data)                                      ((0x00000040&(data))>>6)
#define MIS_IC1_RAW_INTR_STAT_rd_req_shift                                           (5)
#define MIS_IC1_RAW_INTR_STAT_rd_req_mask                                            (0x00000020)
#define MIS_IC1_RAW_INTR_STAT_rd_req(data)                                           (0x00000020&((data)<<5))
#define MIS_IC1_RAW_INTR_STAT_rd_req_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC1_RAW_INTR_STAT_get_rd_req(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC1_RAW_INTR_STAT_tx_empty_shift                                         (4)
#define MIS_IC1_RAW_INTR_STAT_tx_empty_mask                                          (0x00000010)
#define MIS_IC1_RAW_INTR_STAT_tx_empty(data)                                         (0x00000010&((data)<<4))
#define MIS_IC1_RAW_INTR_STAT_tx_empty_src(data)                                     ((0x00000010&(data))>>4)
#define MIS_IC1_RAW_INTR_STAT_get_tx_empty(data)                                     ((0x00000010&(data))>>4)
#define MIS_IC1_RAW_INTR_STAT_tx_over_shift                                          (3)
#define MIS_IC1_RAW_INTR_STAT_tx_over_mask                                           (0x00000008)
#define MIS_IC1_RAW_INTR_STAT_tx_over(data)                                          (0x00000008&((data)<<3))
#define MIS_IC1_RAW_INTR_STAT_tx_over_src(data)                                      ((0x00000008&(data))>>3)
#define MIS_IC1_RAW_INTR_STAT_get_tx_over(data)                                      ((0x00000008&(data))>>3)
#define MIS_IC1_RAW_INTR_STAT_rx_full_shift                                          (2)
#define MIS_IC1_RAW_INTR_STAT_rx_full_mask                                           (0x00000004)
#define MIS_IC1_RAW_INTR_STAT_rx_full(data)                                          (0x00000004&((data)<<2))
#define MIS_IC1_RAW_INTR_STAT_rx_full_src(data)                                      ((0x00000004&(data))>>2)
#define MIS_IC1_RAW_INTR_STAT_get_rx_full(data)                                      ((0x00000004&(data))>>2)
#define MIS_IC1_RAW_INTR_STAT_rx_over_shift                                          (1)
#define MIS_IC1_RAW_INTR_STAT_rx_over_mask                                           (0x00000002)
#define MIS_IC1_RAW_INTR_STAT_rx_over(data)                                          (0x00000002&((data)<<1))
#define MIS_IC1_RAW_INTR_STAT_rx_over_src(data)                                      ((0x00000002&(data))>>1)
#define MIS_IC1_RAW_INTR_STAT_get_rx_over(data)                                      ((0x00000002&(data))>>1)
#define MIS_IC1_RAW_INTR_STAT_rx_under_shift                                         (0)
#define MIS_IC1_RAW_INTR_STAT_rx_under_mask                                          (0x00000001)
#define MIS_IC1_RAW_INTR_STAT_rx_under(data)                                         (0x00000001&((data)<<0))
#define MIS_IC1_RAW_INTR_STAT_rx_under_src(data)                                     ((0x00000001&(data))>>0)
#define MIS_IC1_RAW_INTR_STAT_get_rx_under(data)                                     ((0x00000001&(data))>>0)


#define MIS_IC1_RX_TL                                                                0x1801B338
#define MIS_IC1_RX_TL_reg_addr                                                       "0xB801B338"
#define MIS_IC1_RX_TL_reg                                                            0xB801B338
#define set_MIS_IC1_RX_TL_reg(data)   (*((volatile unsigned int*) MIS_IC1_RX_TL_reg)=data)
#define get_MIS_IC1_RX_TL_reg   (*((volatile unsigned int*) MIS_IC1_RX_TL_reg))
#define MIS_IC1_RX_TL_inst_adr                                                       "0x00CE"
#define MIS_IC1_RX_TL_inst                                                           0x00CE
#define MIS_IC1_RX_TL_rx_tl_shift                                                    (0)
#define MIS_IC1_RX_TL_rx_tl_mask                                                     (0x000000FF)
#define MIS_IC1_RX_TL_rx_tl(data)                                                    (0x000000FF&((data)<<0))
#define MIS_IC1_RX_TL_rx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define MIS_IC1_RX_TL_get_rx_tl(data)                                                ((0x000000FF&(data))>>0)


#define MIS_IC1_TX_TL                                                                0x1801B33C
#define MIS_IC1_TX_TL_reg_addr                                                       "0xB801B33C"
#define MIS_IC1_TX_TL_reg                                                            0xB801B33C
#define set_MIS_IC1_TX_TL_reg(data)   (*((volatile unsigned int*) MIS_IC1_TX_TL_reg)=data)
#define get_MIS_IC1_TX_TL_reg   (*((volatile unsigned int*) MIS_IC1_TX_TL_reg))
#define MIS_IC1_TX_TL_inst_adr                                                       "0x00CF"
#define MIS_IC1_TX_TL_inst                                                           0x00CF
#define MIS_IC1_TX_TL_tx_tl_shift                                                    (0)
#define MIS_IC1_TX_TL_tx_tl_mask                                                     (0x000000FF)
#define MIS_IC1_TX_TL_tx_tl(data)                                                    (0x000000FF&((data)<<0))
#define MIS_IC1_TX_TL_tx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define MIS_IC1_TX_TL_get_tx_tl(data)                                                ((0x000000FF&(data))>>0)


#define MIS_IC1_CLR_INTR                                                             0x1801B340
#define MIS_IC1_CLR_INTR_reg_addr                                                    "0xB801B340"
#define MIS_IC1_CLR_INTR_reg                                                         0xB801B340
#define set_MIS_IC1_CLR_INTR_reg(data)   (*((volatile unsigned int*) MIS_IC1_CLR_INTR_reg)=data)
#define get_MIS_IC1_CLR_INTR_reg   (*((volatile unsigned int*) MIS_IC1_CLR_INTR_reg))
#define MIS_IC1_CLR_INTR_inst_adr                                                    "0x00D0"
#define MIS_IC1_CLR_INTR_inst                                                        0x00D0
#define MIS_IC1_CLR_INTR_clr_intr_shift                                              (0)
#define MIS_IC1_CLR_INTR_clr_intr_mask                                               (0x00000001)
#define MIS_IC1_CLR_INTR_clr_intr(data)                                              (0x00000001&((data)<<0))
#define MIS_IC1_CLR_INTR_clr_intr_src(data)                                          ((0x00000001&(data))>>0)
#define MIS_IC1_CLR_INTR_get_clr_intr(data)                                          ((0x00000001&(data))>>0)


#define MIS_IC1_CLR_RX_UNDER                                                         0x1801B344
#define MIS_IC1_CLR_RX_UNDER_reg_addr                                                "0xB801B344"
#define MIS_IC1_CLR_RX_UNDER_reg                                                     0xB801B344
#define set_MIS_IC1_CLR_RX_UNDER_reg(data)   (*((volatile unsigned int*) MIS_IC1_CLR_RX_UNDER_reg)=data)
#define get_MIS_IC1_CLR_RX_UNDER_reg   (*((volatile unsigned int*) MIS_IC1_CLR_RX_UNDER_reg))
#define MIS_IC1_CLR_RX_UNDER_inst_adr                                                "0x00D1"
#define MIS_IC1_CLR_RX_UNDER_inst                                                    0x00D1
#define MIS_IC1_CLR_RX_UNDER_clr_rx_under_shift                                      (0)
#define MIS_IC1_CLR_RX_UNDER_clr_rx_under_mask                                       (0x00000001)
#define MIS_IC1_CLR_RX_UNDER_clr_rx_under(data)                                      (0x00000001&((data)<<0))
#define MIS_IC1_CLR_RX_UNDER_clr_rx_under_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC1_CLR_RX_UNDER_get_clr_rx_under(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC1_CLR_RX_OVER                                                          0x1801B348
#define MIS_IC1_CLR_RX_OVER_reg_addr                                                 "0xB801B348"
#define MIS_IC1_CLR_RX_OVER_reg                                                      0xB801B348
#define set_MIS_IC1_CLR_RX_OVER_reg(data)   (*((volatile unsigned int*) MIS_IC1_CLR_RX_OVER_reg)=data)
#define get_MIS_IC1_CLR_RX_OVER_reg   (*((volatile unsigned int*) MIS_IC1_CLR_RX_OVER_reg))
#define MIS_IC1_CLR_RX_OVER_inst_adr                                                 "0x00D2"
#define MIS_IC1_CLR_RX_OVER_inst                                                     0x00D2
#define MIS_IC1_CLR_RX_OVER_clr_rx_over_shift                                        (0)
#define MIS_IC1_CLR_RX_OVER_clr_rx_over_mask                                         (0x00000001)
#define MIS_IC1_CLR_RX_OVER_clr_rx_over(data)                                        (0x00000001&((data)<<0))
#define MIS_IC1_CLR_RX_OVER_clr_rx_over_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC1_CLR_RX_OVER_get_clr_rx_over(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC1_CLR_TX_OVER                                                          0x1801B34C
#define MIS_IC1_CLR_TX_OVER_reg_addr                                                 "0xB801B34C"
#define MIS_IC1_CLR_TX_OVER_reg                                                      0xB801B34C
#define set_MIS_IC1_CLR_TX_OVER_reg(data)   (*((volatile unsigned int*) MIS_IC1_CLR_TX_OVER_reg)=data)
#define get_MIS_IC1_CLR_TX_OVER_reg   (*((volatile unsigned int*) MIS_IC1_CLR_TX_OVER_reg))
#define MIS_IC1_CLR_TX_OVER_inst_adr                                                 "0x00D3"
#define MIS_IC1_CLR_TX_OVER_inst                                                     0x00D3
#define MIS_IC1_CLR_TX_OVER_clr_tx_over_shift                                        (0)
#define MIS_IC1_CLR_TX_OVER_clr_tx_over_mask                                         (0x00000001)
#define MIS_IC1_CLR_TX_OVER_clr_tx_over(data)                                        (0x00000001&((data)<<0))
#define MIS_IC1_CLR_TX_OVER_clr_tx_over_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC1_CLR_TX_OVER_get_clr_tx_over(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC1_CLR_RD_REQ                                                           0x1801B350
#define MIS_IC1_CLR_RD_REQ_reg_addr                                                  "0xB801B350"
#define MIS_IC1_CLR_RD_REQ_reg                                                       0xB801B350
#define set_MIS_IC1_CLR_RD_REQ_reg(data)   (*((volatile unsigned int*) MIS_IC1_CLR_RD_REQ_reg)=data)
#define get_MIS_IC1_CLR_RD_REQ_reg   (*((volatile unsigned int*) MIS_IC1_CLR_RD_REQ_reg))
#define MIS_IC1_CLR_RD_REQ_inst_adr                                                  "0x00D4"
#define MIS_IC1_CLR_RD_REQ_inst                                                      0x00D4
#define MIS_IC1_CLR_RD_REQ_clr_rd_req_shift                                          (0)
#define MIS_IC1_CLR_RD_REQ_clr_rd_req_mask                                           (0x00000001)
#define MIS_IC1_CLR_RD_REQ_clr_rd_req(data)                                          (0x00000001&((data)<<0))
#define MIS_IC1_CLR_RD_REQ_clr_rd_req_src(data)                                      ((0x00000001&(data))>>0)
#define MIS_IC1_CLR_RD_REQ_get_clr_rd_req(data)                                      ((0x00000001&(data))>>0)


#define MIS_IC1_CLR_TX_ABRT                                                          0x1801B354
#define MIS_IC1_CLR_TX_ABRT_reg_addr                                                 "0xB801B354"
#define MIS_IC1_CLR_TX_ABRT_reg                                                      0xB801B354
#define set_MIS_IC1_CLR_TX_ABRT_reg(data)   (*((volatile unsigned int*) MIS_IC1_CLR_TX_ABRT_reg)=data)
#define get_MIS_IC1_CLR_TX_ABRT_reg   (*((volatile unsigned int*) MIS_IC1_CLR_TX_ABRT_reg))
#define MIS_IC1_CLR_TX_ABRT_inst_adr                                                 "0x00D5"
#define MIS_IC1_CLR_TX_ABRT_inst                                                     0x00D5
#define MIS_IC1_CLR_TX_ABRT_clr_tx_abrt_shift                                        (0)
#define MIS_IC1_CLR_TX_ABRT_clr_tx_abrt_mask                                         (0x00000001)
#define MIS_IC1_CLR_TX_ABRT_clr_tx_abrt(data)                                        (0x00000001&((data)<<0))
#define MIS_IC1_CLR_TX_ABRT_clr_tx_abrt_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC1_CLR_TX_ABRT_get_clr_tx_abrt(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC1_CLR_RX_DONE                                                          0x1801B358
#define MIS_IC1_CLR_RX_DONE_reg_addr                                                 "0xB801B358"
#define MIS_IC1_CLR_RX_DONE_reg                                                      0xB801B358
#define set_MIS_IC1_CLR_RX_DONE_reg(data)   (*((volatile unsigned int*) MIS_IC1_CLR_RX_DONE_reg)=data)
#define get_MIS_IC1_CLR_RX_DONE_reg   (*((volatile unsigned int*) MIS_IC1_CLR_RX_DONE_reg))
#define MIS_IC1_CLR_RX_DONE_inst_adr                                                 "0x00D6"
#define MIS_IC1_CLR_RX_DONE_inst                                                     0x00D6
#define MIS_IC1_CLR_RX_DONE_clr_rx_done_shift                                        (0)
#define MIS_IC1_CLR_RX_DONE_clr_rx_done_mask                                         (0x00000001)
#define MIS_IC1_CLR_RX_DONE_clr_rx_done(data)                                        (0x00000001&((data)<<0))
#define MIS_IC1_CLR_RX_DONE_clr_rx_done_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC1_CLR_RX_DONE_get_clr_rx_done(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC1_CLR_ACTIVITY                                                         0x1801B35C
#define MIS_IC1_CLR_ACTIVITY_reg_addr                                                "0xB801B35C"
#define MIS_IC1_CLR_ACTIVITY_reg                                                     0xB801B35C
#define set_MIS_IC1_CLR_ACTIVITY_reg(data)   (*((volatile unsigned int*) MIS_IC1_CLR_ACTIVITY_reg)=data)
#define get_MIS_IC1_CLR_ACTIVITY_reg   (*((volatile unsigned int*) MIS_IC1_CLR_ACTIVITY_reg))
#define MIS_IC1_CLR_ACTIVITY_inst_adr                                                "0x00D7"
#define MIS_IC1_CLR_ACTIVITY_inst                                                    0x00D7
#define MIS_IC1_CLR_ACTIVITY_clr_activity_shift                                      (0)
#define MIS_IC1_CLR_ACTIVITY_clr_activity_mask                                       (0x00000001)
#define MIS_IC1_CLR_ACTIVITY_clr_activity(data)                                      (0x00000001&((data)<<0))
#define MIS_IC1_CLR_ACTIVITY_clr_activity_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC1_CLR_ACTIVITY_get_clr_activity(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC1_CLR_STOP_DET                                                         0x1801B360
#define MIS_IC1_CLR_STOP_DET_reg_addr                                                "0xB801B360"
#define MIS_IC1_CLR_STOP_DET_reg                                                     0xB801B360
#define set_MIS_IC1_CLR_STOP_DET_reg(data)   (*((volatile unsigned int*) MIS_IC1_CLR_STOP_DET_reg)=data)
#define get_MIS_IC1_CLR_STOP_DET_reg   (*((volatile unsigned int*) MIS_IC1_CLR_STOP_DET_reg))
#define MIS_IC1_CLR_STOP_DET_inst_adr                                                "0x00D8"
#define MIS_IC1_CLR_STOP_DET_inst                                                    0x00D8
#define MIS_IC1_CLR_STOP_DET_clr_stop_det_shift                                      (0)
#define MIS_IC1_CLR_STOP_DET_clr_stop_det_mask                                       (0x00000001)
#define MIS_IC1_CLR_STOP_DET_clr_stop_det(data)                                      (0x00000001&((data)<<0))
#define MIS_IC1_CLR_STOP_DET_clr_stop_det_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC1_CLR_STOP_DET_get_clr_stop_det(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC1_CLR_START_DET                                                        0x1801B364
#define MIS_IC1_CLR_START_DET_reg_addr                                               "0xB801B364"
#define MIS_IC1_CLR_START_DET_reg                                                    0xB801B364
#define set_MIS_IC1_CLR_START_DET_reg(data)   (*((volatile unsigned int*) MIS_IC1_CLR_START_DET_reg)=data)
#define get_MIS_IC1_CLR_START_DET_reg   (*((volatile unsigned int*) MIS_IC1_CLR_START_DET_reg))
#define MIS_IC1_CLR_START_DET_inst_adr                                               "0x00D9"
#define MIS_IC1_CLR_START_DET_inst                                                   0x00D9
#define MIS_IC1_CLR_START_DET_clr_start_det_shift                                    (0)
#define MIS_IC1_CLR_START_DET_clr_start_det_mask                                     (0x00000001)
#define MIS_IC1_CLR_START_DET_clr_start_det(data)                                    (0x00000001&((data)<<0))
#define MIS_IC1_CLR_START_DET_clr_start_det_src(data)                                ((0x00000001&(data))>>0)
#define MIS_IC1_CLR_START_DET_get_clr_start_det(data)                                ((0x00000001&(data))>>0)


#define MIS_IC1_CLR_GEN_CALL                                                         0x1801B368
#define MIS_IC1_CLR_GEN_CALL_reg_addr                                                "0xB801B368"
#define MIS_IC1_CLR_GEN_CALL_reg                                                     0xB801B368
#define set_MIS_IC1_CLR_GEN_CALL_reg(data)   (*((volatile unsigned int*) MIS_IC1_CLR_GEN_CALL_reg)=data)
#define get_MIS_IC1_CLR_GEN_CALL_reg   (*((volatile unsigned int*) MIS_IC1_CLR_GEN_CALL_reg))
#define MIS_IC1_CLR_GEN_CALL_inst_adr                                                "0x00DA"
#define MIS_IC1_CLR_GEN_CALL_inst                                                    0x00DA
#define MIS_IC1_CLR_GEN_CALL_clr_gen_call_shift                                      (0)
#define MIS_IC1_CLR_GEN_CALL_clr_gen_call_mask                                       (0x00000001)
#define MIS_IC1_CLR_GEN_CALL_clr_gen_call(data)                                      (0x00000001&((data)<<0))
#define MIS_IC1_CLR_GEN_CALL_clr_gen_call_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC1_CLR_GEN_CALL_get_clr_gen_call(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC1_ENABLE                                                               0x1801B36C
#define MIS_IC1_ENABLE_reg_addr                                                      "0xB801B36C"
#define MIS_IC1_ENABLE_reg                                                           0xB801B36C
#define set_MIS_IC1_ENABLE_reg(data)   (*((volatile unsigned int*) MIS_IC1_ENABLE_reg)=data)
#define get_MIS_IC1_ENABLE_reg   (*((volatile unsigned int*) MIS_IC1_ENABLE_reg))
#define MIS_IC1_ENABLE_inst_adr                                                      "0x00DB"
#define MIS_IC1_ENABLE_inst                                                          0x00DB
#define MIS_IC1_ENABLE_enable_shift                                                  (0)
#define MIS_IC1_ENABLE_enable_mask                                                   (0x00000001)
#define MIS_IC1_ENABLE_enable(data)                                                  (0x00000001&((data)<<0))
#define MIS_IC1_ENABLE_enable_src(data)                                              ((0x00000001&(data))>>0)
#define MIS_IC1_ENABLE_get_enable(data)                                              ((0x00000001&(data))>>0)


#define MIS_IC1_STATUS                                                               0x1801B370
#define MIS_IC1_STATUS_reg_addr                                                      "0xB801B370"
#define MIS_IC1_STATUS_reg                                                           0xB801B370
#define set_MIS_IC1_STATUS_reg(data)   (*((volatile unsigned int*) MIS_IC1_STATUS_reg)=data)
#define get_MIS_IC1_STATUS_reg   (*((volatile unsigned int*) MIS_IC1_STATUS_reg))
#define MIS_IC1_STATUS_inst_adr                                                      "0x00DC"
#define MIS_IC1_STATUS_inst                                                          0x00DC
#define MIS_IC1_STATUS_slv_activity_shift                                            (6)
#define MIS_IC1_STATUS_slv_activity_mask                                             (0x00000040)
#define MIS_IC1_STATUS_slv_activity(data)                                            (0x00000040&((data)<<6))
#define MIS_IC1_STATUS_slv_activity_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC1_STATUS_get_slv_activity(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC1_STATUS_mst_activity_shift                                            (5)
#define MIS_IC1_STATUS_mst_activity_mask                                             (0x00000020)
#define MIS_IC1_STATUS_mst_activity(data)                                            (0x00000020&((data)<<5))
#define MIS_IC1_STATUS_mst_activity_src(data)                                        ((0x00000020&(data))>>5)
#define MIS_IC1_STATUS_get_mst_activity(data)                                        ((0x00000020&(data))>>5)
#define MIS_IC1_STATUS_rff_shift                                                     (4)
#define MIS_IC1_STATUS_rff_mask                                                      (0x00000010)
#define MIS_IC1_STATUS_rff(data)                                                     (0x00000010&((data)<<4))
#define MIS_IC1_STATUS_rff_src(data)                                                 ((0x00000010&(data))>>4)
#define MIS_IC1_STATUS_get_rff(data)                                                 ((0x00000010&(data))>>4)
#define MIS_IC1_STATUS_rfne_shift                                                    (3)
#define MIS_IC1_STATUS_rfne_mask                                                     (0x00000008)
#define MIS_IC1_STATUS_rfne(data)                                                    (0x00000008&((data)<<3))
#define MIS_IC1_STATUS_rfne_src(data)                                                ((0x00000008&(data))>>3)
#define MIS_IC1_STATUS_get_rfne(data)                                                ((0x00000008&(data))>>3)
#define MIS_IC1_STATUS_tfe_shift                                                     (2)
#define MIS_IC1_STATUS_tfe_mask                                                      (0x00000004)
#define MIS_IC1_STATUS_tfe(data)                                                     (0x00000004&((data)<<2))
#define MIS_IC1_STATUS_tfe_src(data)                                                 ((0x00000004&(data))>>2)
#define MIS_IC1_STATUS_get_tfe(data)                                                 ((0x00000004&(data))>>2)
#define MIS_IC1_STATUS_tfnf_shift                                                    (1)
#define MIS_IC1_STATUS_tfnf_mask                                                     (0x00000002)
#define MIS_IC1_STATUS_tfnf(data)                                                    (0x00000002&((data)<<1))
#define MIS_IC1_STATUS_tfnf_src(data)                                                ((0x00000002&(data))>>1)
#define MIS_IC1_STATUS_get_tfnf(data)                                                ((0x00000002&(data))>>1)
#define MIS_IC1_STATUS_activity_shift                                                (0)
#define MIS_IC1_STATUS_activity_mask                                                 (0x00000001)
#define MIS_IC1_STATUS_activity(data)                                                (0x00000001&((data)<<0))
#define MIS_IC1_STATUS_activity_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_IC1_STATUS_get_activity(data)                                            ((0x00000001&(data))>>0)


#define MIS_IC1_TXFLR                                                                0x1801B374
#define MIS_IC1_TXFLR_reg_addr                                                       "0xB801B374"
#define MIS_IC1_TXFLR_reg                                                            0xB801B374
#define set_MIS_IC1_TXFLR_reg(data)   (*((volatile unsigned int*) MIS_IC1_TXFLR_reg)=data)
#define get_MIS_IC1_TXFLR_reg   (*((volatile unsigned int*) MIS_IC1_TXFLR_reg))
#define MIS_IC1_TXFLR_inst_adr                                                       "0x00DD"
#define MIS_IC1_TXFLR_inst                                                           0x00DD
#define MIS_IC1_TXFLR_txflr_shift                                                    (0)
#define MIS_IC1_TXFLR_txflr_mask                                                     (0x0000000F)
#define MIS_IC1_TXFLR_txflr(data)                                                    (0x0000000F&((data)<<0))
#define MIS_IC1_TXFLR_txflr_src(data)                                                ((0x0000000F&(data))>>0)
#define MIS_IC1_TXFLR_get_txflr(data)                                                ((0x0000000F&(data))>>0)


#define MIS_IC1_RXFLR                                                                0x1801B378
#define MIS_IC1_RXFLR_reg_addr                                                       "0xB801B378"
#define MIS_IC1_RXFLR_reg                                                            0xB801B378
#define set_MIS_IC1_RXFLR_reg(data)   (*((volatile unsigned int*) MIS_IC1_RXFLR_reg)=data)
#define get_MIS_IC1_RXFLR_reg   (*((volatile unsigned int*) MIS_IC1_RXFLR_reg))
#define MIS_IC1_RXFLR_inst_adr                                                       "0x00DE"
#define MIS_IC1_RXFLR_inst                                                           0x00DE
#define MIS_IC1_RXFLR_rxflr_shift                                                    (0)
#define MIS_IC1_RXFLR_rxflr_mask                                                     (0x0000000F)
#define MIS_IC1_RXFLR_rxflr(data)                                                    (0x0000000F&((data)<<0))
#define MIS_IC1_RXFLR_rxflr_src(data)                                                ((0x0000000F&(data))>>0)
#define MIS_IC1_RXFLR_get_rxflr(data)                                                ((0x0000000F&(data))>>0)


#define MIS_IC1_SDA_HOLD                                                             0x1801B37C
#define MIS_IC1_SDA_HOLD_reg_addr                                                    "0xB801B37C"
#define MIS_IC1_SDA_HOLD_reg                                                         0xB801B37C
#define set_MIS_IC1_SDA_HOLD_reg(data)   (*((volatile unsigned int*) MIS_IC1_SDA_HOLD_reg)=data)
#define get_MIS_IC1_SDA_HOLD_reg   (*((volatile unsigned int*) MIS_IC1_SDA_HOLD_reg))
#define MIS_IC1_SDA_HOLD_inst_adr                                                    "0x00DF"
#define MIS_IC1_SDA_HOLD_inst                                                        0x00DF
#define MIS_IC1_SDA_HOLD_sda_hold_shift                                              (0)
#define MIS_IC1_SDA_HOLD_sda_hold_mask                                               (0x0000FFFF)
#define MIS_IC1_SDA_HOLD_sda_hold(data)                                              (0x0000FFFF&((data)<<0))
#define MIS_IC1_SDA_HOLD_sda_hold_src(data)                                          ((0x0000FFFF&(data))>>0)
#define MIS_IC1_SDA_HOLD_get_sda_hold(data)                                          ((0x0000FFFF&(data))>>0)


#define MIS_IC1_TX_ABRT_SOURCE                                                       0x1801B380
#define MIS_IC1_TX_ABRT_SOURCE_reg_addr                                              "0xB801B380"
#define MIS_IC1_TX_ABRT_SOURCE_reg                                                   0xB801B380
#define set_MIS_IC1_TX_ABRT_SOURCE_reg(data)   (*((volatile unsigned int*) MIS_IC1_TX_ABRT_SOURCE_reg)=data)
#define get_MIS_IC1_TX_ABRT_SOURCE_reg   (*((volatile unsigned int*) MIS_IC1_TX_ABRT_SOURCE_reg))
#define MIS_IC1_TX_ABRT_SOURCE_inst_adr                                              "0x00E0"
#define MIS_IC1_TX_ABRT_SOURCE_inst                                                  0x00E0
#define MIS_IC1_TX_ABRT_SOURCE_abrt_slvrd_intx_shift                                 (15)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_slvrd_intx_mask                                  (0x00008000)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_slvrd_intx(data)                                 (0x00008000&((data)<<15))
#define MIS_IC1_TX_ABRT_SOURCE_abrt_slvrd_intx_src(data)                             ((0x00008000&(data))>>15)
#define MIS_IC1_TX_ABRT_SOURCE_get_abrt_slvrd_intx(data)                             ((0x00008000&(data))>>15)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_slv_arblost_shift                                (14)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_slv_arblost_mask                                 (0x00004000)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_slv_arblost(data)                                (0x00004000&((data)<<14))
#define MIS_IC1_TX_ABRT_SOURCE_abrt_slv_arblost_src(data)                            ((0x00004000&(data))>>14)
#define MIS_IC1_TX_ABRT_SOURCE_get_abrt_slv_arblost(data)                            ((0x00004000&(data))>>14)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_slvflush_txfifo_shift                            (13)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_slvflush_txfifo_mask                             (0x00002000)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_slvflush_txfifo(data)                            (0x00002000&((data)<<13))
#define MIS_IC1_TX_ABRT_SOURCE_abrt_slvflush_txfifo_src(data)                        ((0x00002000&(data))>>13)
#define MIS_IC1_TX_ABRT_SOURCE_get_abrt_slvflush_txfifo(data)                        ((0x00002000&(data))>>13)
#define MIS_IC1_TX_ABRT_SOURCE_arb_lost_shift                                        (12)
#define MIS_IC1_TX_ABRT_SOURCE_arb_lost_mask                                         (0x00001000)
#define MIS_IC1_TX_ABRT_SOURCE_arb_lost(data)                                        (0x00001000&((data)<<12))
#define MIS_IC1_TX_ABRT_SOURCE_arb_lost_src(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC1_TX_ABRT_SOURCE_get_arb_lost(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC1_TX_ABRT_SOURCE_arb_master_dis_shift                                  (11)
#define MIS_IC1_TX_ABRT_SOURCE_arb_master_dis_mask                                   (0x00000800)
#define MIS_IC1_TX_ABRT_SOURCE_arb_master_dis(data)                                  (0x00000800&((data)<<11))
#define MIS_IC1_TX_ABRT_SOURCE_arb_master_dis_src(data)                              ((0x00000800&(data))>>11)
#define MIS_IC1_TX_ABRT_SOURCE_get_arb_master_dis(data)                              ((0x00000800&(data))>>11)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_shift                             (10)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_mask                              (0x00000400)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_10b_rd_norstrt(data)                             (0x00000400&((data)<<10))
#define MIS_IC1_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_src(data)                         ((0x00000400&(data))>>10)
#define MIS_IC1_TX_ABRT_SOURCE_get_abrt_10b_rd_norstrt(data)                         ((0x00000400&(data))>>10)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_sbyte_norstrt_shift                              (9)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_sbyte_norstrt_mask                               (0x00000200)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_sbyte_norstrt(data)                              (0x00000200&((data)<<9))
#define MIS_IC1_TX_ABRT_SOURCE_abrt_sbyte_norstrt_src(data)                          ((0x00000200&(data))>>9)
#define MIS_IC1_TX_ABRT_SOURCE_get_abrt_sbyte_norstrt(data)                          ((0x00000200&(data))>>9)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_hs_norstrt_shift                                 (8)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_hs_norstrt_mask                                  (0x00000100)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_hs_norstrt(data)                                 (0x00000100&((data)<<8))
#define MIS_IC1_TX_ABRT_SOURCE_abrt_hs_norstrt_src(data)                             ((0x00000100&(data))>>8)
#define MIS_IC1_TX_ABRT_SOURCE_get_abrt_hs_norstrt(data)                             ((0x00000100&(data))>>8)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_sbyte_ackdet_shift                               (7)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_sbyte_ackdet_mask                                (0x00000080)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_sbyte_ackdet(data)                               (0x00000080&((data)<<7))
#define MIS_IC1_TX_ABRT_SOURCE_abrt_sbyte_ackdet_src(data)                           ((0x00000080&(data))>>7)
#define MIS_IC1_TX_ABRT_SOURCE_get_abrt_sbyte_ackdet(data)                           ((0x00000080&(data))>>7)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_hs_ackdet_shift                                  (6)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_hs_ackdet_mask                                   (0x00000040)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_hs_ackdet(data)                                  (0x00000040&((data)<<6))
#define MIS_IC1_TX_ABRT_SOURCE_abrt_hs_ackdet_src(data)                              ((0x00000040&(data))>>6)
#define MIS_IC1_TX_ABRT_SOURCE_get_abrt_hs_ackdet(data)                              ((0x00000040&(data))>>6)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_gcall_read_shift                                 (5)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_gcall_read_mask                                  (0x00000020)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_gcall_read(data)                                 (0x00000020&((data)<<5))
#define MIS_IC1_TX_ABRT_SOURCE_abrt_gcall_read_src(data)                             ((0x00000020&(data))>>5)
#define MIS_IC1_TX_ABRT_SOURCE_get_abrt_gcall_read(data)                             ((0x00000020&(data))>>5)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_gcall_noack_shift                                (4)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_gcall_noack_mask                                 (0x00000010)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_gcall_noack(data)                                (0x00000010&((data)<<4))
#define MIS_IC1_TX_ABRT_SOURCE_abrt_gcall_noack_src(data)                            ((0x00000010&(data))>>4)
#define MIS_IC1_TX_ABRT_SOURCE_get_abrt_gcall_noack(data)                            ((0x00000010&(data))>>4)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_txdata_noack_shift                               (3)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_txdata_noack_mask                                (0x00000008)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_txdata_noack(data)                               (0x00000008&((data)<<3))
#define MIS_IC1_TX_ABRT_SOURCE_abrt_txdata_noack_src(data)                           ((0x00000008&(data))>>3)
#define MIS_IC1_TX_ABRT_SOURCE_get_abrt_txdata_noack(data)                           ((0x00000008&(data))>>3)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_10addr2_noack_shift                              (2)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_10addr2_noack_mask                               (0x00000004)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_10addr2_noack(data)                              (0x00000004&((data)<<2))
#define MIS_IC1_TX_ABRT_SOURCE_abrt_10addr2_noack_src(data)                          ((0x00000004&(data))>>2)
#define MIS_IC1_TX_ABRT_SOURCE_get_abrt_10addr2_noack(data)                          ((0x00000004&(data))>>2)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_10addr1_noack_shift                              (1)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_10addr1_noack_mask                               (0x00000002)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_10addr1_noack(data)                              (0x00000002&((data)<<1))
#define MIS_IC1_TX_ABRT_SOURCE_abrt_10addr1_noack_src(data)                          ((0x00000002&(data))>>1)
#define MIS_IC1_TX_ABRT_SOURCE_get_abrt_10addr1_noack(data)                          ((0x00000002&(data))>>1)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_7b_addr_noack_shift                              (0)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_7b_addr_noack_mask                               (0x00000001)
#define MIS_IC1_TX_ABRT_SOURCE_abrt_7b_addr_noack(data)                              (0x00000001&((data)<<0))
#define MIS_IC1_TX_ABRT_SOURCE_abrt_7b_addr_noack_src(data)                          ((0x00000001&(data))>>0)
#define MIS_IC1_TX_ABRT_SOURCE_get_abrt_7b_addr_noack(data)                          ((0x00000001&(data))>>0)


#define MIS_IC1_SLV_DATA_NACK_ONLY                                                   0x1801B384
#define MIS_IC1_SLV_DATA_NACK_ONLY_reg_addr                                          "0xB801B384"
#define MIS_IC1_SLV_DATA_NACK_ONLY_reg                                               0xB801B384
#define set_MIS_IC1_SLV_DATA_NACK_ONLY_reg(data)   (*((volatile unsigned int*) MIS_IC1_SLV_DATA_NACK_ONLY_reg)=data)
#define get_MIS_IC1_SLV_DATA_NACK_ONLY_reg   (*((volatile unsigned int*) MIS_IC1_SLV_DATA_NACK_ONLY_reg))
#define MIS_IC1_SLV_DATA_NACK_ONLY_inst_adr                                          "0x00E1"
#define MIS_IC1_SLV_DATA_NACK_ONLY_inst                                              0x00E1
#define MIS_IC1_SLV_DATA_NACK_ONLY_nack_shift                                        (0)
#define MIS_IC1_SLV_DATA_NACK_ONLY_nack_mask                                         (0x00000001)
#define MIS_IC1_SLV_DATA_NACK_ONLY_nack(data)                                        (0x00000001&((data)<<0))
#define MIS_IC1_SLV_DATA_NACK_ONLY_nack_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC1_SLV_DATA_NACK_ONLY_get_nack(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC1_DMA_CR                                                               0x1801B388
#define MIS_IC1_DMA_CR_reg_addr                                                      "0xB801B388"
#define MIS_IC1_DMA_CR_reg                                                           0xB801B388
#define set_MIS_IC1_DMA_CR_reg(data)   (*((volatile unsigned int*) MIS_IC1_DMA_CR_reg)=data)
#define get_MIS_IC1_DMA_CR_reg   (*((volatile unsigned int*) MIS_IC1_DMA_CR_reg))
#define MIS_IC1_DMA_CR_inst_adr                                                      "0x00E2"
#define MIS_IC1_DMA_CR_inst                                                          0x00E2
#define MIS_IC1_DMA_CR_tdmae_shift                                                   (1)
#define MIS_IC1_DMA_CR_tdmae_mask                                                    (0x00000002)
#define MIS_IC1_DMA_CR_tdmae(data)                                                   (0x00000002&((data)<<1))
#define MIS_IC1_DMA_CR_tdmae_src(data)                                               ((0x00000002&(data))>>1)
#define MIS_IC1_DMA_CR_get_tdmae(data)                                               ((0x00000002&(data))>>1)
#define MIS_IC1_DMA_CR_rdmae_shift                                                   (0)
#define MIS_IC1_DMA_CR_rdmae_mask                                                    (0x00000001)
#define MIS_IC1_DMA_CR_rdmae(data)                                                   (0x00000001&((data)<<0))
#define MIS_IC1_DMA_CR_rdmae_src(data)                                               ((0x00000001&(data))>>0)
#define MIS_IC1_DMA_CR_get_rdmae(data)                                               ((0x00000001&(data))>>0)


#define MIS_IC1_DMA_TDLR                                                             0x1801B38C
#define MIS_IC1_DMA_TDLR_reg_addr                                                    "0xB801B38C"
#define MIS_IC1_DMA_TDLR_reg                                                         0xB801B38C
#define set_MIS_IC1_DMA_TDLR_reg(data)   (*((volatile unsigned int*) MIS_IC1_DMA_TDLR_reg)=data)
#define get_MIS_IC1_DMA_TDLR_reg   (*((volatile unsigned int*) MIS_IC1_DMA_TDLR_reg))
#define MIS_IC1_DMA_TDLR_inst_adr                                                    "0x00E3"
#define MIS_IC1_DMA_TDLR_inst                                                        0x00E3
#define MIS_IC1_DMA_TDLR_dmatdl_shift                                                (0)
#define MIS_IC1_DMA_TDLR_dmatdl_mask                                                 (0x00000007)
#define MIS_IC1_DMA_TDLR_dmatdl(data)                                                (0x00000007&((data)<<0))
#define MIS_IC1_DMA_TDLR_dmatdl_src(data)                                            ((0x00000007&(data))>>0)
#define MIS_IC1_DMA_TDLR_get_dmatdl(data)                                            ((0x00000007&(data))>>0)


#define MIS_IC1_DMA_RDLR                                                             0x1801B390
#define MIS_IC1_DMA_RDLR_reg_addr                                                    "0xB801B390"
#define MIS_IC1_DMA_RDLR_reg                                                         0xB801B390
#define set_MIS_IC1_DMA_RDLR_reg(data)   (*((volatile unsigned int*) MIS_IC1_DMA_RDLR_reg)=data)
#define get_MIS_IC1_DMA_RDLR_reg   (*((volatile unsigned int*) MIS_IC1_DMA_RDLR_reg))
#define MIS_IC1_DMA_RDLR_inst_adr                                                    "0x00E4"
#define MIS_IC1_DMA_RDLR_inst                                                        0x00E4
#define MIS_IC1_DMA_RDLR_dmardl_shift                                                (0)
#define MIS_IC1_DMA_RDLR_dmardl_mask                                                 (0x0000000F)
#define MIS_IC1_DMA_RDLR_dmardl(data)                                                (0x0000000F&((data)<<0))
#define MIS_IC1_DMA_RDLR_dmardl_src(data)                                            ((0x0000000F&(data))>>0)
#define MIS_IC1_DMA_RDLR_get_dmardl(data)                                            ((0x0000000F&(data))>>0)


#define MIS_IC1_SDA_SETUP                                                            0x1801B394
#define MIS_IC1_SDA_SETUP_reg_addr                                                   "0xB801B394"
#define MIS_IC1_SDA_SETUP_reg                                                        0xB801B394
#define set_MIS_IC1_SDA_SETUP_reg(data)   (*((volatile unsigned int*) MIS_IC1_SDA_SETUP_reg)=data)
#define get_MIS_IC1_SDA_SETUP_reg   (*((volatile unsigned int*) MIS_IC1_SDA_SETUP_reg))
#define MIS_IC1_SDA_SETUP_inst_adr                                                   "0x00E5"
#define MIS_IC1_SDA_SETUP_inst                                                       0x00E5
#define MIS_IC1_SDA_SETUP_sda_setup_shift                                            (0)
#define MIS_IC1_SDA_SETUP_sda_setup_mask                                             (0x000000FF)
#define MIS_IC1_SDA_SETUP_sda_setup(data)                                            (0x000000FF&((data)<<0))
#define MIS_IC1_SDA_SETUP_sda_setup_src(data)                                        ((0x000000FF&(data))>>0)
#define MIS_IC1_SDA_SETUP_get_sda_setup(data)                                        ((0x000000FF&(data))>>0)


#define MIS_IC1_ACK_GENERAL_CALL                                                     0x1801B398
#define MIS_IC1_ACK_GENERAL_CALL_reg_addr                                            "0xB801B398"
#define MIS_IC1_ACK_GENERAL_CALL_reg                                                 0xB801B398
#define set_MIS_IC1_ACK_GENERAL_CALL_reg(data)   (*((volatile unsigned int*) MIS_IC1_ACK_GENERAL_CALL_reg)=data)
#define get_MIS_IC1_ACK_GENERAL_CALL_reg   (*((volatile unsigned int*) MIS_IC1_ACK_GENERAL_CALL_reg))
#define MIS_IC1_ACK_GENERAL_CALL_inst_adr                                            "0x00E6"
#define MIS_IC1_ACK_GENERAL_CALL_inst                                                0x00E6
#define MIS_IC1_ACK_GENERAL_CALL_ack_gen_call_shift                                  (0)
#define MIS_IC1_ACK_GENERAL_CALL_ack_gen_call_mask                                   (0x00000001)
#define MIS_IC1_ACK_GENERAL_CALL_ack_gen_call(data)                                  (0x00000001&((data)<<0))
#define MIS_IC1_ACK_GENERAL_CALL_ack_gen_call_src(data)                              ((0x00000001&(data))>>0)
#define MIS_IC1_ACK_GENERAL_CALL_get_ack_gen_call(data)                              ((0x00000001&(data))>>0)


#define MIS_IC1_ENABLE_STATUS                                                        0x1801B39C
#define MIS_IC1_ENABLE_STATUS_reg_addr                                               "0xB801B39C"
#define MIS_IC1_ENABLE_STATUS_reg                                                    0xB801B39C
#define set_MIS_IC1_ENABLE_STATUS_reg(data)   (*((volatile unsigned int*) MIS_IC1_ENABLE_STATUS_reg)=data)
#define get_MIS_IC1_ENABLE_STATUS_reg   (*((volatile unsigned int*) MIS_IC1_ENABLE_STATUS_reg))
#define MIS_IC1_ENABLE_STATUS_inst_adr                                               "0x00E7"
#define MIS_IC1_ENABLE_STATUS_inst                                                   0x00E7
#define MIS_IC1_ENABLE_STATUS_slv_rx_data_lost_shift                                 (2)
#define MIS_IC1_ENABLE_STATUS_slv_rx_data_lost_mask                                  (0x00000004)
#define MIS_IC1_ENABLE_STATUS_slv_rx_data_lost(data)                                 (0x00000004&((data)<<2))
#define MIS_IC1_ENABLE_STATUS_slv_rx_data_lost_src(data)                             ((0x00000004&(data))>>2)
#define MIS_IC1_ENABLE_STATUS_get_slv_rx_data_lost(data)                             ((0x00000004&(data))>>2)
#define MIS_IC1_ENABLE_STATUS_slv_disabled_whi_shift                                 (1)
#define MIS_IC1_ENABLE_STATUS_slv_disabled_whi_mask                                  (0x00000002)
#define MIS_IC1_ENABLE_STATUS_slv_disabled_whi(data)                                 (0x00000002&((data)<<1))
#define MIS_IC1_ENABLE_STATUS_slv_disabled_whi_src(data)                             ((0x00000002&(data))>>1)
#define MIS_IC1_ENABLE_STATUS_get_slv_disabled_whi(data)                             ((0x00000002&(data))>>1)
#define MIS_IC1_ENABLE_STATUS_ic_en_shift                                            (0)
#define MIS_IC1_ENABLE_STATUS_ic_en_mask                                             (0x00000001)
#define MIS_IC1_ENABLE_STATUS_ic_en(data)                                            (0x00000001&((data)<<0))
#define MIS_IC1_ENABLE_STATUS_ic_en_src(data)                                        ((0x00000001&(data))>>0)
#define MIS_IC1_ENABLE_STATUS_get_ic_en(data)                                        ((0x00000001&(data))>>0)


#define MIS_IC1_COMP_PARAM_1                                                         0x1801B3F4
#define MIS_IC1_COMP_PARAM_1_reg_addr                                                "0xB801B3F4"
#define MIS_IC1_COMP_PARAM_1_reg                                                     0xB801B3F4
#define set_MIS_IC1_COMP_PARAM_1_reg(data)   (*((volatile unsigned int*) MIS_IC1_COMP_PARAM_1_reg)=data)
#define get_MIS_IC1_COMP_PARAM_1_reg   (*((volatile unsigned int*) MIS_IC1_COMP_PARAM_1_reg))
#define MIS_IC1_COMP_PARAM_1_inst_adr                                                "0x00FD"
#define MIS_IC1_COMP_PARAM_1_inst                                                    0x00FD
#define MIS_IC1_COMP_PARAM_1_tx_buffer_depth_shift                                   (16)
#define MIS_IC1_COMP_PARAM_1_tx_buffer_depth_mask                                    (0x00FF0000)
#define MIS_IC1_COMP_PARAM_1_tx_buffer_depth(data)                                   (0x00FF0000&((data)<<16))
#define MIS_IC1_COMP_PARAM_1_tx_buffer_depth_src(data)                               ((0x00FF0000&(data))>>16)
#define MIS_IC1_COMP_PARAM_1_get_tx_buffer_depth(data)                               ((0x00FF0000&(data))>>16)
#define MIS_IC1_COMP_PARAM_1_rx_buffer_depth_shift                                   (8)
#define MIS_IC1_COMP_PARAM_1_rx_buffer_depth_mask                                    (0x0000FF00)
#define MIS_IC1_COMP_PARAM_1_rx_buffer_depth(data)                                   (0x0000FF00&((data)<<8))
#define MIS_IC1_COMP_PARAM_1_rx_buffer_depth_src(data)                               ((0x0000FF00&(data))>>8)
#define MIS_IC1_COMP_PARAM_1_get_rx_buffer_depth(data)                               ((0x0000FF00&(data))>>8)
#define MIS_IC1_COMP_PARAM_1_add_encoded_params_shift                                (7)
#define MIS_IC1_COMP_PARAM_1_add_encoded_params_mask                                 (0x00000080)
#define MIS_IC1_COMP_PARAM_1_add_encoded_params(data)                                (0x00000080&((data)<<7))
#define MIS_IC1_COMP_PARAM_1_add_encoded_params_src(data)                            ((0x00000080&(data))>>7)
#define MIS_IC1_COMP_PARAM_1_get_add_encoded_params(data)                            ((0x00000080&(data))>>7)
#define MIS_IC1_COMP_PARAM_1_has_dma_shift                                           (6)
#define MIS_IC1_COMP_PARAM_1_has_dma_mask                                            (0x00000040)
#define MIS_IC1_COMP_PARAM_1_has_dma(data)                                           (0x00000040&((data)<<6))
#define MIS_IC1_COMP_PARAM_1_has_dma_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC1_COMP_PARAM_1_get_has_dma(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC1_COMP_PARAM_1_intr_io_shift                                           (5)
#define MIS_IC1_COMP_PARAM_1_intr_io_mask                                            (0x00000020)
#define MIS_IC1_COMP_PARAM_1_intr_io(data)                                           (0x00000020&((data)<<5))
#define MIS_IC1_COMP_PARAM_1_intr_io_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC1_COMP_PARAM_1_get_intr_io(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC1_COMP_PARAM_1_hc_count_values_shift                                   (4)
#define MIS_IC1_COMP_PARAM_1_hc_count_values_mask                                    (0x00000010)
#define MIS_IC1_COMP_PARAM_1_hc_count_values(data)                                   (0x00000010&((data)<<4))
#define MIS_IC1_COMP_PARAM_1_hc_count_values_src(data)                               ((0x00000010&(data))>>4)
#define MIS_IC1_COMP_PARAM_1_get_hc_count_values(data)                               ((0x00000010&(data))>>4)
#define MIS_IC1_COMP_PARAM_1_max_speed_mode_shift                                    (2)
#define MIS_IC1_COMP_PARAM_1_max_speed_mode_mask                                     (0x0000000C)
#define MIS_IC1_COMP_PARAM_1_max_speed_mode(data)                                    (0x0000000C&((data)<<2))
#define MIS_IC1_COMP_PARAM_1_max_speed_mode_src(data)                                ((0x0000000C&(data))>>2)
#define MIS_IC1_COMP_PARAM_1_get_max_speed_mode(data)                                ((0x0000000C&(data))>>2)
#define MIS_IC1_COMP_PARAM_1_apb_data_width_shift                                    (0)
#define MIS_IC1_COMP_PARAM_1_apb_data_width_mask                                     (0x00000003)
#define MIS_IC1_COMP_PARAM_1_apb_data_width(data)                                    (0x00000003&((data)<<0))
#define MIS_IC1_COMP_PARAM_1_apb_data_width_src(data)                                ((0x00000003&(data))>>0)
#define MIS_IC1_COMP_PARAM_1_get_apb_data_width(data)                                ((0x00000003&(data))>>0)


#define MIS_IC1_COMP_VERSION                                                         0x1801B3F8
#define MIS_IC1_COMP_VERSION_reg_addr                                                "0xB801B3F8"
#define MIS_IC1_COMP_VERSION_reg                                                     0xB801B3F8
#define set_MIS_IC1_COMP_VERSION_reg(data)   (*((volatile unsigned int*) MIS_IC1_COMP_VERSION_reg)=data)
#define get_MIS_IC1_COMP_VERSION_reg   (*((volatile unsigned int*) MIS_IC1_COMP_VERSION_reg))
#define MIS_IC1_COMP_VERSION_inst_adr                                                "0x00FE"
#define MIS_IC1_COMP_VERSION_inst                                                    0x00FE
#define MIS_IC1_COMP_VERSION_ic_comp_version_shift                                   (0)
#define MIS_IC1_COMP_VERSION_ic_comp_version_mask                                    (0xFFFFFFFF)
#define MIS_IC1_COMP_VERSION_ic_comp_version(data)                                   (0xFFFFFFFF&((data)<<0))
#define MIS_IC1_COMP_VERSION_ic_comp_version_src(data)                               ((0xFFFFFFFF&(data))>>0)
#define MIS_IC1_COMP_VERSION_get_ic_comp_version(data)                               ((0xFFFFFFFF&(data))>>0)


#define MIS_IC1_COMP_TYPE                                                            0x1801B3FC
#define MIS_IC1_COMP_TYPE_reg_addr                                                   "0xB801B3FC"
#define MIS_IC1_COMP_TYPE_reg                                                        0xB801B3FC
#define set_MIS_IC1_COMP_TYPE_reg(data)   (*((volatile unsigned int*) MIS_IC1_COMP_TYPE_reg)=data)
#define get_MIS_IC1_COMP_TYPE_reg   (*((volatile unsigned int*) MIS_IC1_COMP_TYPE_reg))
#define MIS_IC1_COMP_TYPE_inst_adr                                                   "0x00FF"
#define MIS_IC1_COMP_TYPE_inst                                                       0x00FF
#define MIS_IC1_COMP_TYPE_ic_comp_type_shift                                         (0)
#define MIS_IC1_COMP_TYPE_ic_comp_type_mask                                          (0xFFFFFFFF)
#define MIS_IC1_COMP_TYPE_ic_comp_type(data)                                         (0xFFFFFFFF&((data)<<0))
#define MIS_IC1_COMP_TYPE_ic_comp_type_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define MIS_IC1_COMP_TYPE_get_ic_comp_type(data)                                     ((0xFFFFFFFF&(data))>>0)


#define MIS_IC2_CON                                                                  0x1801B700
#define MIS_IC2_CON_reg_addr                                                         "0xB801B700"
#define MIS_IC2_CON_reg                                                              0xB801B700
#define set_MIS_IC2_CON_reg(data)   (*((volatile unsigned int*) MIS_IC2_CON_reg)=data)
#define get_MIS_IC2_CON_reg   (*((volatile unsigned int*) MIS_IC2_CON_reg))
#define MIS_IC2_CON_inst_adr                                                         "0x00C0"
#define MIS_IC2_CON_inst                                                             0x00C0
#define MIS_IC2_CON_ic_slave_disable_shift                                           (6)
#define MIS_IC2_CON_ic_slave_disable_mask                                            (0x00000040)
#define MIS_IC2_CON_ic_slave_disable(data)                                           (0x00000040&((data)<<6))
#define MIS_IC2_CON_ic_slave_disable_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC2_CON_get_ic_slave_disable(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC2_CON_ic_restart_en_shift                                              (5)
#define MIS_IC2_CON_ic_restart_en_mask                                               (0x00000020)
#define MIS_IC2_CON_ic_restart_en(data)                                              (0x00000020&((data)<<5))
#define MIS_IC2_CON_ic_restart_en_src(data)                                          ((0x00000020&(data))>>5)
#define MIS_IC2_CON_get_ic_restart_en(data)                                          ((0x00000020&(data))>>5)
#define MIS_IC2_CON_ic_10bitaddr_master_shift                                        (4)
#define MIS_IC2_CON_ic_10bitaddr_master_mask                                         (0x00000010)
#define MIS_IC2_CON_ic_10bitaddr_master(data)                                        (0x00000010&((data)<<4))
#define MIS_IC2_CON_ic_10bitaddr_master_src(data)                                    ((0x00000010&(data))>>4)
#define MIS_IC2_CON_get_ic_10bitaddr_master(data)                                    ((0x00000010&(data))>>4)
#define MIS_IC2_CON_ic_10bitaddr_slave_shift                                         (3)
#define MIS_IC2_CON_ic_10bitaddr_slave_mask                                          (0x00000008)
#define MIS_IC2_CON_ic_10bitaddr_slave(data)                                         (0x00000008&((data)<<3))
#define MIS_IC2_CON_ic_10bitaddr_slave_src(data)                                     ((0x00000008&(data))>>3)
#define MIS_IC2_CON_get_ic_10bitaddr_slave(data)                                     ((0x00000008&(data))>>3)
#define MIS_IC2_CON_speed_shift                                                      (1)
#define MIS_IC2_CON_speed_mask                                                       (0x00000006)
#define MIS_IC2_CON_speed(data)                                                      (0x00000006&((data)<<1))
#define MIS_IC2_CON_speed_src(data)                                                  ((0x00000006&(data))>>1)
#define MIS_IC2_CON_get_speed(data)                                                  ((0x00000006&(data))>>1)
#define MIS_IC2_CON_master_mode_shift                                                (0)
#define MIS_IC2_CON_master_mode_mask                                                 (0x00000001)
#define MIS_IC2_CON_master_mode(data)                                                (0x00000001&((data)<<0))
#define MIS_IC2_CON_master_mode_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_IC2_CON_get_master_mode(data)                                            ((0x00000001&(data))>>0)


#define MIS_IC2_TAR                                                                  0x1801B704
#define MIS_IC2_TAR_reg_addr                                                         "0xB801B704"
#define MIS_IC2_TAR_reg                                                              0xB801B704
#define set_MIS_IC2_TAR_reg(data)   (*((volatile unsigned int*) MIS_IC2_TAR_reg)=data)
#define get_MIS_IC2_TAR_reg   (*((volatile unsigned int*) MIS_IC2_TAR_reg))
#define MIS_IC2_TAR_inst_adr                                                         "0x00C1"
#define MIS_IC2_TAR_inst                                                             0x00C1
#define MIS_IC2_TAR_ic_10bitaddr_master_shift                                        (12)
#define MIS_IC2_TAR_ic_10bitaddr_master_mask                                         (0x00001000)
#define MIS_IC2_TAR_ic_10bitaddr_master(data)                                        (0x00001000&((data)<<12))
#define MIS_IC2_TAR_ic_10bitaddr_master_src(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC2_TAR_get_ic_10bitaddr_master(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC2_TAR_special_shift                                                    (11)
#define MIS_IC2_TAR_special_mask                                                     (0x00000800)
#define MIS_IC2_TAR_special(data)                                                    (0x00000800&((data)<<11))
#define MIS_IC2_TAR_special_src(data)                                                ((0x00000800&(data))>>11)
#define MIS_IC2_TAR_get_special(data)                                                ((0x00000800&(data))>>11)
#define MIS_IC2_TAR_gc_or_start_shift                                                (10)
#define MIS_IC2_TAR_gc_or_start_mask                                                 (0x00000400)
#define MIS_IC2_TAR_gc_or_start(data)                                                (0x00000400&((data)<<10))
#define MIS_IC2_TAR_gc_or_start_src(data)                                            ((0x00000400&(data))>>10)
#define MIS_IC2_TAR_get_gc_or_start(data)                                            ((0x00000400&(data))>>10)
#define MIS_IC2_TAR_ic_tar_shift                                                     (0)
#define MIS_IC2_TAR_ic_tar_mask                                                      (0x000003FF)
#define MIS_IC2_TAR_ic_tar(data)                                                     (0x000003FF&((data)<<0))
#define MIS_IC2_TAR_ic_tar_src(data)                                                 ((0x000003FF&(data))>>0)
#define MIS_IC2_TAR_get_ic_tar(data)                                                 ((0x000003FF&(data))>>0)


#define MIS_IC2_SAR                                                                  0x1801B708
#define MIS_IC2_SAR_reg_addr                                                         "0xB801B708"
#define MIS_IC2_SAR_reg                                                              0xB801B708
#define set_MIS_IC2_SAR_reg(data)   (*((volatile unsigned int*) MIS_IC2_SAR_reg)=data)
#define get_MIS_IC2_SAR_reg   (*((volatile unsigned int*) MIS_IC2_SAR_reg))
#define MIS_IC2_SAR_inst_adr                                                         "0x00C2"
#define MIS_IC2_SAR_inst                                                             0x00C2
#define MIS_IC2_SAR_ic_sar_shift                                                     (0)
#define MIS_IC2_SAR_ic_sar_mask                                                      (0x000003FF)
#define MIS_IC2_SAR_ic_sar(data)                                                     (0x000003FF&((data)<<0))
#define MIS_IC2_SAR_ic_sar_src(data)                                                 ((0x000003FF&(data))>>0)
#define MIS_IC2_SAR_get_ic_sar(data)                                                 ((0x000003FF&(data))>>0)


#define MIS_IC2_HS_MADDR                                                             0x1801B70C
#define MIS_IC2_HS_MADDR_reg_addr                                                    "0xB801B70C"
#define MIS_IC2_HS_MADDR_reg                                                         0xB801B70C
#define set_MIS_IC2_HS_MADDR_reg(data)   (*((volatile unsigned int*) MIS_IC2_HS_MADDR_reg)=data)
#define get_MIS_IC2_HS_MADDR_reg   (*((volatile unsigned int*) MIS_IC2_HS_MADDR_reg))
#define MIS_IC2_HS_MADDR_inst_adr                                                    "0x00C3"
#define MIS_IC2_HS_MADDR_inst                                                        0x00C3
#define MIS_IC2_HS_MADDR_ic_hs_mar_shift                                             (0)
#define MIS_IC2_HS_MADDR_ic_hs_mar_mask                                              (0x00000007)
#define MIS_IC2_HS_MADDR_ic_hs_mar(data)                                             (0x00000007&((data)<<0))
#define MIS_IC2_HS_MADDR_ic_hs_mar_src(data)                                         ((0x00000007&(data))>>0)
#define MIS_IC2_HS_MADDR_get_ic_hs_mar(data)                                         ((0x00000007&(data))>>0)


#define MIS_IC2_DATA_CMD                                                             0x1801B710
#define MIS_IC2_DATA_CMD_reg_addr                                                    "0xB801B710"
#define MIS_IC2_DATA_CMD_reg                                                         0xB801B710
#define set_MIS_IC2_DATA_CMD_reg(data)   (*((volatile unsigned int*) MIS_IC2_DATA_CMD_reg)=data)
#define get_MIS_IC2_DATA_CMD_reg   (*((volatile unsigned int*) MIS_IC2_DATA_CMD_reg))
#define MIS_IC2_DATA_CMD_inst_adr                                                    "0x00C4"
#define MIS_IC2_DATA_CMD_inst                                                        0x00C4
#define MIS_IC2_DATA_CMD_restart_shift                                               (10)
#define MIS_IC2_DATA_CMD_restart_mask                                                (0x00000400)
#define MIS_IC2_DATA_CMD_restart(data)                                               (0x00000400&((data)<<10))
#define MIS_IC2_DATA_CMD_restart_src(data)                                           ((0x00000400&(data))>>10)
#define MIS_IC2_DATA_CMD_get_restart(data)                                           ((0x00000400&(data))>>10)
#define MIS_IC2_DATA_CMD_stop_shift                                                  (9)
#define MIS_IC2_DATA_CMD_stop_mask                                                   (0x00000200)
#define MIS_IC2_DATA_CMD_stop(data)                                                  (0x00000200&((data)<<9))
#define MIS_IC2_DATA_CMD_stop_src(data)                                              ((0x00000200&(data))>>9)
#define MIS_IC2_DATA_CMD_get_stop(data)                                              ((0x00000200&(data))>>9)
#define MIS_IC2_DATA_CMD_cmd_shift                                                   (8)
#define MIS_IC2_DATA_CMD_cmd_mask                                                    (0x00000100)
#define MIS_IC2_DATA_CMD_cmd(data)                                                   (0x00000100&((data)<<8))
#define MIS_IC2_DATA_CMD_cmd_src(data)                                               ((0x00000100&(data))>>8)
#define MIS_IC2_DATA_CMD_get_cmd(data)                                               ((0x00000100&(data))>>8)
#define MIS_IC2_DATA_CMD_dat_shift                                                   (0)
#define MIS_IC2_DATA_CMD_dat_mask                                                    (0x000000FF)
#define MIS_IC2_DATA_CMD_dat(data)                                                   (0x000000FF&((data)<<0))
#define MIS_IC2_DATA_CMD_dat_src(data)                                               ((0x000000FF&(data))>>0)
#define MIS_IC2_DATA_CMD_get_dat(data)                                               ((0x000000FF&(data))>>0)


#define MIS_IC2_SS_SCL_HCNT                                                          0x1801B714
#define MIS_IC2_SS_SCL_HCNT_reg_addr                                                 "0xB801B714"
#define MIS_IC2_SS_SCL_HCNT_reg                                                      0xB801B714
#define set_MIS_IC2_SS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) MIS_IC2_SS_SCL_HCNT_reg)=data)
#define get_MIS_IC2_SS_SCL_HCNT_reg   (*((volatile unsigned int*) MIS_IC2_SS_SCL_HCNT_reg))
#define MIS_IC2_SS_SCL_HCNT_inst_adr                                                 "0x00C5"
#define MIS_IC2_SS_SCL_HCNT_inst                                                     0x00C5
#define MIS_IC2_SS_SCL_HCNT_ic_ss_scl_hcnt_shift                                     (0)
#define MIS_IC2_SS_SCL_HCNT_ic_ss_scl_hcnt_mask                                      (0x0000FFFF)
#define MIS_IC2_SS_SCL_HCNT_ic_ss_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC2_SS_SCL_HCNT_ic_ss_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC2_SS_SCL_HCNT_get_ic_ss_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC2_SS_SCL_LCNT                                                          0x1801B718
#define MIS_IC2_SS_SCL_LCNT_reg_addr                                                 "0xB801B718"
#define MIS_IC2_SS_SCL_LCNT_reg                                                      0xB801B718
#define set_MIS_IC2_SS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) MIS_IC2_SS_SCL_LCNT_reg)=data)
#define get_MIS_IC2_SS_SCL_LCNT_reg   (*((volatile unsigned int*) MIS_IC2_SS_SCL_LCNT_reg))
#define MIS_IC2_SS_SCL_LCNT_inst_adr                                                 "0x00C6"
#define MIS_IC2_SS_SCL_LCNT_inst                                                     0x00C6
#define MIS_IC2_SS_SCL_LCNT_ic_ss_scl_lcnt_shift                                     (0)
#define MIS_IC2_SS_SCL_LCNT_ic_ss_scl_lcnt_mask                                      (0x0000FFFF)
#define MIS_IC2_SS_SCL_LCNT_ic_ss_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC2_SS_SCL_LCNT_ic_ss_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC2_SS_SCL_LCNT_get_ic_ss_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC2_FS_SCL_HCNT                                                          0x1801B71C
#define MIS_IC2_FS_SCL_HCNT_reg_addr                                                 "0xB801B71C"
#define MIS_IC2_FS_SCL_HCNT_reg                                                      0xB801B71C
#define set_MIS_IC2_FS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) MIS_IC2_FS_SCL_HCNT_reg)=data)
#define get_MIS_IC2_FS_SCL_HCNT_reg   (*((volatile unsigned int*) MIS_IC2_FS_SCL_HCNT_reg))
#define MIS_IC2_FS_SCL_HCNT_inst_adr                                                 "0x00C7"
#define MIS_IC2_FS_SCL_HCNT_inst                                                     0x00C7
#define MIS_IC2_FS_SCL_HCNT_ic_fs_scl_hcnt_shift                                     (0)
#define MIS_IC2_FS_SCL_HCNT_ic_fs_scl_hcnt_mask                                      (0x0000FFFF)
#define MIS_IC2_FS_SCL_HCNT_ic_fs_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC2_FS_SCL_HCNT_ic_fs_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC2_FS_SCL_HCNT_get_ic_fs_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC2_FS_SCL_LCNT                                                          0x1801B720
#define MIS_IC2_FS_SCL_LCNT_reg_addr                                                 "0xB801B720"
#define MIS_IC2_FS_SCL_LCNT_reg                                                      0xB801B720
#define set_MIS_IC2_FS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) MIS_IC2_FS_SCL_LCNT_reg)=data)
#define get_MIS_IC2_FS_SCL_LCNT_reg   (*((volatile unsigned int*) MIS_IC2_FS_SCL_LCNT_reg))
#define MIS_IC2_FS_SCL_LCNT_inst_adr                                                 "0x00C8"
#define MIS_IC2_FS_SCL_LCNT_inst                                                     0x00C8
#define MIS_IC2_FS_SCL_LCNT_ic_fs_scl_lcnt_shift                                     (0)
#define MIS_IC2_FS_SCL_LCNT_ic_fs_scl_lcnt_mask                                      (0x0000FFFF)
#define MIS_IC2_FS_SCL_LCNT_ic_fs_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC2_FS_SCL_LCNT_ic_fs_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC2_FS_SCL_LCNT_get_ic_fs_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC2_INTR_STAT                                                            0x1801B72C
#define MIS_IC2_INTR_STAT_reg_addr                                                   "0xB801B72C"
#define MIS_IC2_INTR_STAT_reg                                                        0xB801B72C
#define set_MIS_IC2_INTR_STAT_reg(data)   (*((volatile unsigned int*) MIS_IC2_INTR_STAT_reg)=data)
#define get_MIS_IC2_INTR_STAT_reg   (*((volatile unsigned int*) MIS_IC2_INTR_STAT_reg))
#define MIS_IC2_INTR_STAT_inst_adr                                                   "0x00CB"
#define MIS_IC2_INTR_STAT_inst                                                       0x00CB
#define MIS_IC2_INTR_STAT_r_gen_call_shift                                           (11)
#define MIS_IC2_INTR_STAT_r_gen_call_mask                                            (0x00000800)
#define MIS_IC2_INTR_STAT_r_gen_call(data)                                           (0x00000800&((data)<<11))
#define MIS_IC2_INTR_STAT_r_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC2_INTR_STAT_get_r_gen_call(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC2_INTR_STAT_r_start_det_shift                                          (10)
#define MIS_IC2_INTR_STAT_r_start_det_mask                                           (0x00000400)
#define MIS_IC2_INTR_STAT_r_start_det(data)                                          (0x00000400&((data)<<10))
#define MIS_IC2_INTR_STAT_r_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC2_INTR_STAT_get_r_start_det(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC2_INTR_STAT_r_stop_det_shift                                           (9)
#define MIS_IC2_INTR_STAT_r_stop_det_mask                                            (0x00000200)
#define MIS_IC2_INTR_STAT_r_stop_det(data)                                           (0x00000200&((data)<<9))
#define MIS_IC2_INTR_STAT_r_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC2_INTR_STAT_get_r_stop_det(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC2_INTR_STAT_r_activity_shift                                           (8)
#define MIS_IC2_INTR_STAT_r_activity_mask                                            (0x00000100)
#define MIS_IC2_INTR_STAT_r_activity(data)                                           (0x00000100&((data)<<8))
#define MIS_IC2_INTR_STAT_r_activity_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC2_INTR_STAT_get_r_activity(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC2_INTR_STAT_r_rx_done_shift                                            (7)
#define MIS_IC2_INTR_STAT_r_rx_done_mask                                             (0x00000080)
#define MIS_IC2_INTR_STAT_r_rx_done(data)                                            (0x00000080&((data)<<7))
#define MIS_IC2_INTR_STAT_r_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC2_INTR_STAT_get_r_rx_done(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC2_INTR_STAT_r_tx_abrt_shift                                            (6)
#define MIS_IC2_INTR_STAT_r_tx_abrt_mask                                             (0x00000040)
#define MIS_IC2_INTR_STAT_r_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define MIS_IC2_INTR_STAT_r_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC2_INTR_STAT_get_r_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC2_INTR_STAT_r_rd_req_shift                                             (5)
#define MIS_IC2_INTR_STAT_r_rd_req_mask                                              (0x00000020)
#define MIS_IC2_INTR_STAT_r_rd_req(data)                                             (0x00000020&((data)<<5))
#define MIS_IC2_INTR_STAT_r_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC2_INTR_STAT_get_r_rd_req(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC2_INTR_STAT_r_tx_empty_shift                                           (4)
#define MIS_IC2_INTR_STAT_r_tx_empty_mask                                            (0x00000010)
#define MIS_IC2_INTR_STAT_r_tx_empty(data)                                           (0x00000010&((data)<<4))
#define MIS_IC2_INTR_STAT_r_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC2_INTR_STAT_get_r_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC2_INTR_STAT_r_tx_over_shift                                            (3)
#define MIS_IC2_INTR_STAT_r_tx_over_mask                                             (0x00000008)
#define MIS_IC2_INTR_STAT_r_tx_over(data)                                            (0x00000008&((data)<<3))
#define MIS_IC2_INTR_STAT_r_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC2_INTR_STAT_get_r_tx_over(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC2_INTR_STAT_r_rx_full_shift                                            (2)
#define MIS_IC2_INTR_STAT_r_rx_full_mask                                             (0x00000004)
#define MIS_IC2_INTR_STAT_r_rx_full(data)                                            (0x00000004&((data)<<2))
#define MIS_IC2_INTR_STAT_r_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC2_INTR_STAT_get_r_rx_full(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC2_INTR_STAT_r_rx_over_shift                                            (1)
#define MIS_IC2_INTR_STAT_r_rx_over_mask                                             (0x00000002)
#define MIS_IC2_INTR_STAT_r_rx_over(data)                                            (0x00000002&((data)<<1))
#define MIS_IC2_INTR_STAT_r_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC2_INTR_STAT_get_r_rx_over(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC2_INTR_STAT_r_rx_under_shift                                           (0)
#define MIS_IC2_INTR_STAT_r_rx_under_mask                                            (0x00000001)
#define MIS_IC2_INTR_STAT_r_rx_under(data)                                           (0x00000001&((data)<<0))
#define MIS_IC2_INTR_STAT_r_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_IC2_INTR_STAT_get_r_rx_under(data)                                       ((0x00000001&(data))>>0)


#define MIS_IC2_INTR_MASK                                                            0x1801B730
#define MIS_IC2_INTR_MASK_reg_addr                                                   "0xB801B730"
#define MIS_IC2_INTR_MASK_reg                                                        0xB801B730
#define set_MIS_IC2_INTR_MASK_reg(data)   (*((volatile unsigned int*) MIS_IC2_INTR_MASK_reg)=data)
#define get_MIS_IC2_INTR_MASK_reg   (*((volatile unsigned int*) MIS_IC2_INTR_MASK_reg))
#define MIS_IC2_INTR_MASK_inst_adr                                                   "0x00CC"
#define MIS_IC2_INTR_MASK_inst                                                       0x00CC
#define MIS_IC2_INTR_MASK_m_gen_call_shift                                           (11)
#define MIS_IC2_INTR_MASK_m_gen_call_mask                                            (0x00000800)
#define MIS_IC2_INTR_MASK_m_gen_call(data)                                           (0x00000800&((data)<<11))
#define MIS_IC2_INTR_MASK_m_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC2_INTR_MASK_get_m_gen_call(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC2_INTR_MASK_m_start_det_shift                                          (10)
#define MIS_IC2_INTR_MASK_m_start_det_mask                                           (0x00000400)
#define MIS_IC2_INTR_MASK_m_start_det(data)                                          (0x00000400&((data)<<10))
#define MIS_IC2_INTR_MASK_m_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC2_INTR_MASK_get_m_start_det(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC2_INTR_MASK_m_stop_det_shift                                           (9)
#define MIS_IC2_INTR_MASK_m_stop_det_mask                                            (0x00000200)
#define MIS_IC2_INTR_MASK_m_stop_det(data)                                           (0x00000200&((data)<<9))
#define MIS_IC2_INTR_MASK_m_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC2_INTR_MASK_get_m_stop_det(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC2_INTR_MASK_m_activity_shift                                           (8)
#define MIS_IC2_INTR_MASK_m_activity_mask                                            (0x00000100)
#define MIS_IC2_INTR_MASK_m_activity(data)                                           (0x00000100&((data)<<8))
#define MIS_IC2_INTR_MASK_m_activity_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC2_INTR_MASK_get_m_activity(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC2_INTR_MASK_m_rx_done_shift                                            (7)
#define MIS_IC2_INTR_MASK_m_rx_done_mask                                             (0x00000080)
#define MIS_IC2_INTR_MASK_m_rx_done(data)                                            (0x00000080&((data)<<7))
#define MIS_IC2_INTR_MASK_m_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC2_INTR_MASK_get_m_rx_done(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC2_INTR_MASK_m_tx_abrt_shift                                            (6)
#define MIS_IC2_INTR_MASK_m_tx_abrt_mask                                             (0x00000040)
#define MIS_IC2_INTR_MASK_m_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define MIS_IC2_INTR_MASK_m_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC2_INTR_MASK_get_m_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC2_INTR_MASK_m_rd_req_shift                                             (5)
#define MIS_IC2_INTR_MASK_m_rd_req_mask                                              (0x00000020)
#define MIS_IC2_INTR_MASK_m_rd_req(data)                                             (0x00000020&((data)<<5))
#define MIS_IC2_INTR_MASK_m_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC2_INTR_MASK_get_m_rd_req(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC2_INTR_MASK_m_tx_empty_shift                                           (4)
#define MIS_IC2_INTR_MASK_m_tx_empty_mask                                            (0x00000010)
#define MIS_IC2_INTR_MASK_m_tx_empty(data)                                           (0x00000010&((data)<<4))
#define MIS_IC2_INTR_MASK_m_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC2_INTR_MASK_get_m_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC2_INTR_MASK_m_tx_over_shift                                            (3)
#define MIS_IC2_INTR_MASK_m_tx_over_mask                                             (0x00000008)
#define MIS_IC2_INTR_MASK_m_tx_over(data)                                            (0x00000008&((data)<<3))
#define MIS_IC2_INTR_MASK_m_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC2_INTR_MASK_get_m_tx_over(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC2_INTR_MASK_m_rx_full_shift                                            (2)
#define MIS_IC2_INTR_MASK_m_rx_full_mask                                             (0x00000004)
#define MIS_IC2_INTR_MASK_m_rx_full(data)                                            (0x00000004&((data)<<2))
#define MIS_IC2_INTR_MASK_m_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC2_INTR_MASK_get_m_rx_full(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC2_INTR_MASK_m_rx_over_shift                                            (1)
#define MIS_IC2_INTR_MASK_m_rx_over_mask                                             (0x00000002)
#define MIS_IC2_INTR_MASK_m_rx_over(data)                                            (0x00000002&((data)<<1))
#define MIS_IC2_INTR_MASK_m_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC2_INTR_MASK_get_m_rx_over(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC2_INTR_MASK_m_rx_under_shift                                           (0)
#define MIS_IC2_INTR_MASK_m_rx_under_mask                                            (0x00000001)
#define MIS_IC2_INTR_MASK_m_rx_under(data)                                           (0x00000001&((data)<<0))
#define MIS_IC2_INTR_MASK_m_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_IC2_INTR_MASK_get_m_rx_under(data)                                       ((0x00000001&(data))>>0)


#define MIS_IC2_RAW_INTR_STAT                                                        0x1801B734
#define MIS_IC2_RAW_INTR_STAT_reg_addr                                               "0xB801B734"
#define MIS_IC2_RAW_INTR_STAT_reg                                                    0xB801B734
#define set_MIS_IC2_RAW_INTR_STAT_reg(data)   (*((volatile unsigned int*) MIS_IC2_RAW_INTR_STAT_reg)=data)
#define get_MIS_IC2_RAW_INTR_STAT_reg   (*((volatile unsigned int*) MIS_IC2_RAW_INTR_STAT_reg))
#define MIS_IC2_RAW_INTR_STAT_inst_adr                                               "0x00CD"
#define MIS_IC2_RAW_INTR_STAT_inst                                                   0x00CD
#define MIS_IC2_RAW_INTR_STAT_gen_call_shift                                         (11)
#define MIS_IC2_RAW_INTR_STAT_gen_call_mask                                          (0x00000800)
#define MIS_IC2_RAW_INTR_STAT_gen_call(data)                                         (0x00000800&((data)<<11))
#define MIS_IC2_RAW_INTR_STAT_gen_call_src(data)                                     ((0x00000800&(data))>>11)
#define MIS_IC2_RAW_INTR_STAT_get_gen_call(data)                                     ((0x00000800&(data))>>11)
#define MIS_IC2_RAW_INTR_STAT_start_det_shift                                        (10)
#define MIS_IC2_RAW_INTR_STAT_start_det_mask                                         (0x00000400)
#define MIS_IC2_RAW_INTR_STAT_start_det(data)                                        (0x00000400&((data)<<10))
#define MIS_IC2_RAW_INTR_STAT_start_det_src(data)                                    ((0x00000400&(data))>>10)
#define MIS_IC2_RAW_INTR_STAT_get_start_det(data)                                    ((0x00000400&(data))>>10)
#define MIS_IC2_RAW_INTR_STAT_stop_det_shift                                         (9)
#define MIS_IC2_RAW_INTR_STAT_stop_det_mask                                          (0x00000200)
#define MIS_IC2_RAW_INTR_STAT_stop_det(data)                                         (0x00000200&((data)<<9))
#define MIS_IC2_RAW_INTR_STAT_stop_det_src(data)                                     ((0x00000200&(data))>>9)
#define MIS_IC2_RAW_INTR_STAT_get_stop_det(data)                                     ((0x00000200&(data))>>9)
#define MIS_IC2_RAW_INTR_STAT_activity_shift                                         (8)
#define MIS_IC2_RAW_INTR_STAT_activity_mask                                          (0x00000100)
#define MIS_IC2_RAW_INTR_STAT_activity(data)                                         (0x00000100&((data)<<8))
#define MIS_IC2_RAW_INTR_STAT_activity_src(data)                                     ((0x00000100&(data))>>8)
#define MIS_IC2_RAW_INTR_STAT_get_activity(data)                                     ((0x00000100&(data))>>8)
#define MIS_IC2_RAW_INTR_STAT_rx_done_shift                                          (7)
#define MIS_IC2_RAW_INTR_STAT_rx_done_mask                                           (0x00000080)
#define MIS_IC2_RAW_INTR_STAT_rx_done(data)                                          (0x00000080&((data)<<7))
#define MIS_IC2_RAW_INTR_STAT_rx_done_src(data)                                      ((0x00000080&(data))>>7)
#define MIS_IC2_RAW_INTR_STAT_get_rx_done(data)                                      ((0x00000080&(data))>>7)
#define MIS_IC2_RAW_INTR_STAT_tx_abrt_shift                                          (6)
#define MIS_IC2_RAW_INTR_STAT_tx_abrt_mask                                           (0x00000040)
#define MIS_IC2_RAW_INTR_STAT_tx_abrt(data)                                          (0x00000040&((data)<<6))
#define MIS_IC2_RAW_INTR_STAT_tx_abrt_src(data)                                      ((0x00000040&(data))>>6)
#define MIS_IC2_RAW_INTR_STAT_get_tx_abrt(data)                                      ((0x00000040&(data))>>6)
#define MIS_IC2_RAW_INTR_STAT_rd_req_shift                                           (5)
#define MIS_IC2_RAW_INTR_STAT_rd_req_mask                                            (0x00000020)
#define MIS_IC2_RAW_INTR_STAT_rd_req(data)                                           (0x00000020&((data)<<5))
#define MIS_IC2_RAW_INTR_STAT_rd_req_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC2_RAW_INTR_STAT_get_rd_req(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC2_RAW_INTR_STAT_tx_empty_shift                                         (4)
#define MIS_IC2_RAW_INTR_STAT_tx_empty_mask                                          (0x00000010)
#define MIS_IC2_RAW_INTR_STAT_tx_empty(data)                                         (0x00000010&((data)<<4))
#define MIS_IC2_RAW_INTR_STAT_tx_empty_src(data)                                     ((0x00000010&(data))>>4)
#define MIS_IC2_RAW_INTR_STAT_get_tx_empty(data)                                     ((0x00000010&(data))>>4)
#define MIS_IC2_RAW_INTR_STAT_tx_over_shift                                          (3)
#define MIS_IC2_RAW_INTR_STAT_tx_over_mask                                           (0x00000008)
#define MIS_IC2_RAW_INTR_STAT_tx_over(data)                                          (0x00000008&((data)<<3))
#define MIS_IC2_RAW_INTR_STAT_tx_over_src(data)                                      ((0x00000008&(data))>>3)
#define MIS_IC2_RAW_INTR_STAT_get_tx_over(data)                                      ((0x00000008&(data))>>3)
#define MIS_IC2_RAW_INTR_STAT_rx_full_shift                                          (2)
#define MIS_IC2_RAW_INTR_STAT_rx_full_mask                                           (0x00000004)
#define MIS_IC2_RAW_INTR_STAT_rx_full(data)                                          (0x00000004&((data)<<2))
#define MIS_IC2_RAW_INTR_STAT_rx_full_src(data)                                      ((0x00000004&(data))>>2)
#define MIS_IC2_RAW_INTR_STAT_get_rx_full(data)                                      ((0x00000004&(data))>>2)
#define MIS_IC2_RAW_INTR_STAT_rx_over_shift                                          (1)
#define MIS_IC2_RAW_INTR_STAT_rx_over_mask                                           (0x00000002)
#define MIS_IC2_RAW_INTR_STAT_rx_over(data)                                          (0x00000002&((data)<<1))
#define MIS_IC2_RAW_INTR_STAT_rx_over_src(data)                                      ((0x00000002&(data))>>1)
#define MIS_IC2_RAW_INTR_STAT_get_rx_over(data)                                      ((0x00000002&(data))>>1)
#define MIS_IC2_RAW_INTR_STAT_rx_under_shift                                         (0)
#define MIS_IC2_RAW_INTR_STAT_rx_under_mask                                          (0x00000001)
#define MIS_IC2_RAW_INTR_STAT_rx_under(data)                                         (0x00000001&((data)<<0))
#define MIS_IC2_RAW_INTR_STAT_rx_under_src(data)                                     ((0x00000001&(data))>>0)
#define MIS_IC2_RAW_INTR_STAT_get_rx_under(data)                                     ((0x00000001&(data))>>0)


#define MIS_IC2_RX_TL                                                                0x1801B738
#define MIS_IC2_RX_TL_reg_addr                                                       "0xB801B738"
#define MIS_IC2_RX_TL_reg                                                            0xB801B738
#define set_MIS_IC2_RX_TL_reg(data)   (*((volatile unsigned int*) MIS_IC2_RX_TL_reg)=data)
#define get_MIS_IC2_RX_TL_reg   (*((volatile unsigned int*) MIS_IC2_RX_TL_reg))
#define MIS_IC2_RX_TL_inst_adr                                                       "0x00CE"
#define MIS_IC2_RX_TL_inst                                                           0x00CE
#define MIS_IC2_RX_TL_rx_tl_shift                                                    (0)
#define MIS_IC2_RX_TL_rx_tl_mask                                                     (0x000000FF)
#define MIS_IC2_RX_TL_rx_tl(data)                                                    (0x000000FF&((data)<<0))
#define MIS_IC2_RX_TL_rx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define MIS_IC2_RX_TL_get_rx_tl(data)                                                ((0x000000FF&(data))>>0)


#define MIS_IC2_TX_TL                                                                0x1801B73C
#define MIS_IC2_TX_TL_reg_addr                                                       "0xB801B73C"
#define MIS_IC2_TX_TL_reg                                                            0xB801B73C
#define set_MIS_IC2_TX_TL_reg(data)   (*((volatile unsigned int*) MIS_IC2_TX_TL_reg)=data)
#define get_MIS_IC2_TX_TL_reg   (*((volatile unsigned int*) MIS_IC2_TX_TL_reg))
#define MIS_IC2_TX_TL_inst_adr                                                       "0x00CF"
#define MIS_IC2_TX_TL_inst                                                           0x00CF
#define MIS_IC2_TX_TL_tx_tl_shift                                                    (0)
#define MIS_IC2_TX_TL_tx_tl_mask                                                     (0x000000FF)
#define MIS_IC2_TX_TL_tx_tl(data)                                                    (0x000000FF&((data)<<0))
#define MIS_IC2_TX_TL_tx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define MIS_IC2_TX_TL_get_tx_tl(data)                                                ((0x000000FF&(data))>>0)


#define MIS_IC2_CLR_INTR                                                             0x1801B740
#define MIS_IC2_CLR_INTR_reg_addr                                                    "0xB801B740"
#define MIS_IC2_CLR_INTR_reg                                                         0xB801B740
#define set_MIS_IC2_CLR_INTR_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_INTR_reg)=data)
#define get_MIS_IC2_CLR_INTR_reg   (*((volatile unsigned int*) MIS_IC2_CLR_INTR_reg))
#define MIS_IC2_CLR_INTR_inst_adr                                                    "0x00D0"
#define MIS_IC2_CLR_INTR_inst                                                        0x00D0
#define MIS_IC2_CLR_INTR_clr_intr_shift                                              (0)
#define MIS_IC2_CLR_INTR_clr_intr_mask                                               (0x00000001)
#define MIS_IC2_CLR_INTR_clr_intr(data)                                              (0x00000001&((data)<<0))
#define MIS_IC2_CLR_INTR_clr_intr_src(data)                                          ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_INTR_get_clr_intr(data)                                          ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_RX_UNDER                                                         0x1801B744
#define MIS_IC2_CLR_RX_UNDER_reg_addr                                                "0xB801B744"
#define MIS_IC2_CLR_RX_UNDER_reg                                                     0xB801B744
#define set_MIS_IC2_CLR_RX_UNDER_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_RX_UNDER_reg)=data)
#define get_MIS_IC2_CLR_RX_UNDER_reg   (*((volatile unsigned int*) MIS_IC2_CLR_RX_UNDER_reg))
#define MIS_IC2_CLR_RX_UNDER_inst_adr                                                "0x00D1"
#define MIS_IC2_CLR_RX_UNDER_inst                                                    0x00D1
#define MIS_IC2_CLR_RX_UNDER_clr_rx_under_shift                                      (0)
#define MIS_IC2_CLR_RX_UNDER_clr_rx_under_mask                                       (0x00000001)
#define MIS_IC2_CLR_RX_UNDER_clr_rx_under(data)                                      (0x00000001&((data)<<0))
#define MIS_IC2_CLR_RX_UNDER_clr_rx_under_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_RX_UNDER_get_clr_rx_under(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_RX_OVER                                                          0x1801B748
#define MIS_IC2_CLR_RX_OVER_reg_addr                                                 "0xB801B748"
#define MIS_IC2_CLR_RX_OVER_reg                                                      0xB801B748
#define set_MIS_IC2_CLR_RX_OVER_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_RX_OVER_reg)=data)
#define get_MIS_IC2_CLR_RX_OVER_reg   (*((volatile unsigned int*) MIS_IC2_CLR_RX_OVER_reg))
#define MIS_IC2_CLR_RX_OVER_inst_adr                                                 "0x00D2"
#define MIS_IC2_CLR_RX_OVER_inst                                                     0x00D2
#define MIS_IC2_CLR_RX_OVER_clr_rx_over_shift                                        (0)
#define MIS_IC2_CLR_RX_OVER_clr_rx_over_mask                                         (0x00000001)
#define MIS_IC2_CLR_RX_OVER_clr_rx_over(data)                                        (0x00000001&((data)<<0))
#define MIS_IC2_CLR_RX_OVER_clr_rx_over_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_RX_OVER_get_clr_rx_over(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_TX_OVER                                                          0x1801B74C
#define MIS_IC2_CLR_TX_OVER_reg_addr                                                 "0xB801B74C"
#define MIS_IC2_CLR_TX_OVER_reg                                                      0xB801B74C
#define set_MIS_IC2_CLR_TX_OVER_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_TX_OVER_reg)=data)
#define get_MIS_IC2_CLR_TX_OVER_reg   (*((volatile unsigned int*) MIS_IC2_CLR_TX_OVER_reg))
#define MIS_IC2_CLR_TX_OVER_inst_adr                                                 "0x00D3"
#define MIS_IC2_CLR_TX_OVER_inst                                                     0x00D3
#define MIS_IC2_CLR_TX_OVER_clr_tx_over_shift                                        (0)
#define MIS_IC2_CLR_TX_OVER_clr_tx_over_mask                                         (0x00000001)
#define MIS_IC2_CLR_TX_OVER_clr_tx_over(data)                                        (0x00000001&((data)<<0))
#define MIS_IC2_CLR_TX_OVER_clr_tx_over_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_TX_OVER_get_clr_tx_over(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_RD_REQ                                                           0x1801B750
#define MIS_IC2_CLR_RD_REQ_reg_addr                                                  "0xB801B750"
#define MIS_IC2_CLR_RD_REQ_reg                                                       0xB801B750
#define set_MIS_IC2_CLR_RD_REQ_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_RD_REQ_reg)=data)
#define get_MIS_IC2_CLR_RD_REQ_reg   (*((volatile unsigned int*) MIS_IC2_CLR_RD_REQ_reg))
#define MIS_IC2_CLR_RD_REQ_inst_adr                                                  "0x00D4"
#define MIS_IC2_CLR_RD_REQ_inst                                                      0x00D4
#define MIS_IC2_CLR_RD_REQ_clr_rd_req_shift                                          (0)
#define MIS_IC2_CLR_RD_REQ_clr_rd_req_mask                                           (0x00000001)
#define MIS_IC2_CLR_RD_REQ_clr_rd_req(data)                                          (0x00000001&((data)<<0))
#define MIS_IC2_CLR_RD_REQ_clr_rd_req_src(data)                                      ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_RD_REQ_get_clr_rd_req(data)                                      ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_TX_ABRT                                                          0x1801B754
#define MIS_IC2_CLR_TX_ABRT_reg_addr                                                 "0xB801B754"
#define MIS_IC2_CLR_TX_ABRT_reg                                                      0xB801B754
#define set_MIS_IC2_CLR_TX_ABRT_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_TX_ABRT_reg)=data)
#define get_MIS_IC2_CLR_TX_ABRT_reg   (*((volatile unsigned int*) MIS_IC2_CLR_TX_ABRT_reg))
#define MIS_IC2_CLR_TX_ABRT_inst_adr                                                 "0x00D5"
#define MIS_IC2_CLR_TX_ABRT_inst                                                     0x00D5
#define MIS_IC2_CLR_TX_ABRT_clr_tx_abrt_shift                                        (0)
#define MIS_IC2_CLR_TX_ABRT_clr_tx_abrt_mask                                         (0x00000001)
#define MIS_IC2_CLR_TX_ABRT_clr_tx_abrt(data)                                        (0x00000001&((data)<<0))
#define MIS_IC2_CLR_TX_ABRT_clr_tx_abrt_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_TX_ABRT_get_clr_tx_abrt(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_RX_DONE                                                          0x1801B758
#define MIS_IC2_CLR_RX_DONE_reg_addr                                                 "0xB801B758"
#define MIS_IC2_CLR_RX_DONE_reg                                                      0xB801B758
#define set_MIS_IC2_CLR_RX_DONE_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_RX_DONE_reg)=data)
#define get_MIS_IC2_CLR_RX_DONE_reg   (*((volatile unsigned int*) MIS_IC2_CLR_RX_DONE_reg))
#define MIS_IC2_CLR_RX_DONE_inst_adr                                                 "0x00D6"
#define MIS_IC2_CLR_RX_DONE_inst                                                     0x00D6
#define MIS_IC2_CLR_RX_DONE_clr_rx_done_shift                                        (0)
#define MIS_IC2_CLR_RX_DONE_clr_rx_done_mask                                         (0x00000001)
#define MIS_IC2_CLR_RX_DONE_clr_rx_done(data)                                        (0x00000001&((data)<<0))
#define MIS_IC2_CLR_RX_DONE_clr_rx_done_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_RX_DONE_get_clr_rx_done(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_ACTIVITY                                                         0x1801B75C
#define MIS_IC2_CLR_ACTIVITY_reg_addr                                                "0xB801B75C"
#define MIS_IC2_CLR_ACTIVITY_reg                                                     0xB801B75C
#define set_MIS_IC2_CLR_ACTIVITY_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_ACTIVITY_reg)=data)
#define get_MIS_IC2_CLR_ACTIVITY_reg   (*((volatile unsigned int*) MIS_IC2_CLR_ACTIVITY_reg))
#define MIS_IC2_CLR_ACTIVITY_inst_adr                                                "0x00D7"
#define MIS_IC2_CLR_ACTIVITY_inst                                                    0x00D7
#define MIS_IC2_CLR_ACTIVITY_clr_activity_shift                                      (0)
#define MIS_IC2_CLR_ACTIVITY_clr_activity_mask                                       (0x00000001)
#define MIS_IC2_CLR_ACTIVITY_clr_activity(data)                                      (0x00000001&((data)<<0))
#define MIS_IC2_CLR_ACTIVITY_clr_activity_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_ACTIVITY_get_clr_activity(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_STOP_DET                                                         0x1801B760
#define MIS_IC2_CLR_STOP_DET_reg_addr                                                "0xB801B760"
#define MIS_IC2_CLR_STOP_DET_reg                                                     0xB801B760
#define set_MIS_IC2_CLR_STOP_DET_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_STOP_DET_reg)=data)
#define get_MIS_IC2_CLR_STOP_DET_reg   (*((volatile unsigned int*) MIS_IC2_CLR_STOP_DET_reg))
#define MIS_IC2_CLR_STOP_DET_inst_adr                                                "0x00D8"
#define MIS_IC2_CLR_STOP_DET_inst                                                    0x00D8
#define MIS_IC2_CLR_STOP_DET_clr_stop_det_shift                                      (0)
#define MIS_IC2_CLR_STOP_DET_clr_stop_det_mask                                       (0x00000001)
#define MIS_IC2_CLR_STOP_DET_clr_stop_det(data)                                      (0x00000001&((data)<<0))
#define MIS_IC2_CLR_STOP_DET_clr_stop_det_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_STOP_DET_get_clr_stop_det(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_START_DET                                                        0x1801B764
#define MIS_IC2_CLR_START_DET_reg_addr                                               "0xB801B764"
#define MIS_IC2_CLR_START_DET_reg                                                    0xB801B764
#define set_MIS_IC2_CLR_START_DET_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_START_DET_reg)=data)
#define get_MIS_IC2_CLR_START_DET_reg   (*((volatile unsigned int*) MIS_IC2_CLR_START_DET_reg))
#define MIS_IC2_CLR_START_DET_inst_adr                                               "0x00D9"
#define MIS_IC2_CLR_START_DET_inst                                                   0x00D9
#define MIS_IC2_CLR_START_DET_clr_start_det_shift                                    (0)
#define MIS_IC2_CLR_START_DET_clr_start_det_mask                                     (0x00000001)
#define MIS_IC2_CLR_START_DET_clr_start_det(data)                                    (0x00000001&((data)<<0))
#define MIS_IC2_CLR_START_DET_clr_start_det_src(data)                                ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_START_DET_get_clr_start_det(data)                                ((0x00000001&(data))>>0)


#define MIS_IC2_CLR_GEN_CALL                                                         0x1801B768
#define MIS_IC2_CLR_GEN_CALL_reg_addr                                                "0xB801B768"
#define MIS_IC2_CLR_GEN_CALL_reg                                                     0xB801B768
#define set_MIS_IC2_CLR_GEN_CALL_reg(data)   (*((volatile unsigned int*) MIS_IC2_CLR_GEN_CALL_reg)=data)
#define get_MIS_IC2_CLR_GEN_CALL_reg   (*((volatile unsigned int*) MIS_IC2_CLR_GEN_CALL_reg))
#define MIS_IC2_CLR_GEN_CALL_inst_adr                                                "0x00DA"
#define MIS_IC2_CLR_GEN_CALL_inst                                                    0x00DA
#define MIS_IC2_CLR_GEN_CALL_clr_gen_call_shift                                      (0)
#define MIS_IC2_CLR_GEN_CALL_clr_gen_call_mask                                       (0x00000001)
#define MIS_IC2_CLR_GEN_CALL_clr_gen_call(data)                                      (0x00000001&((data)<<0))
#define MIS_IC2_CLR_GEN_CALL_clr_gen_call_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC2_CLR_GEN_CALL_get_clr_gen_call(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC2_ENABLE                                                               0x1801B76C
#define MIS_IC2_ENABLE_reg_addr                                                      "0xB801B76C"
#define MIS_IC2_ENABLE_reg                                                           0xB801B76C
#define set_MIS_IC2_ENABLE_reg(data)   (*((volatile unsigned int*) MIS_IC2_ENABLE_reg)=data)
#define get_MIS_IC2_ENABLE_reg   (*((volatile unsigned int*) MIS_IC2_ENABLE_reg))
#define MIS_IC2_ENABLE_inst_adr                                                      "0x00DB"
#define MIS_IC2_ENABLE_inst                                                          0x00DB
#define MIS_IC2_ENABLE_enable_shift                                                  (0)
#define MIS_IC2_ENABLE_enable_mask                                                   (0x00000001)
#define MIS_IC2_ENABLE_enable(data)                                                  (0x00000001&((data)<<0))
#define MIS_IC2_ENABLE_enable_src(data)                                              ((0x00000001&(data))>>0)
#define MIS_IC2_ENABLE_get_enable(data)                                              ((0x00000001&(data))>>0)


#define MIS_IC2_STATUS                                                               0x1801B770
#define MIS_IC2_STATUS_reg_addr                                                      "0xB801B770"
#define MIS_IC2_STATUS_reg                                                           0xB801B770
#define set_MIS_IC2_STATUS_reg(data)   (*((volatile unsigned int*) MIS_IC2_STATUS_reg)=data)
#define get_MIS_IC2_STATUS_reg   (*((volatile unsigned int*) MIS_IC2_STATUS_reg))
#define MIS_IC2_STATUS_inst_adr                                                      "0x00DC"
#define MIS_IC2_STATUS_inst                                                          0x00DC
#define MIS_IC2_STATUS_slv_activity_shift                                            (6)
#define MIS_IC2_STATUS_slv_activity_mask                                             (0x00000040)
#define MIS_IC2_STATUS_slv_activity(data)                                            (0x00000040&((data)<<6))
#define MIS_IC2_STATUS_slv_activity_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC2_STATUS_get_slv_activity(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC2_STATUS_mst_activity_shift                                            (5)
#define MIS_IC2_STATUS_mst_activity_mask                                             (0x00000020)
#define MIS_IC2_STATUS_mst_activity(data)                                            (0x00000020&((data)<<5))
#define MIS_IC2_STATUS_mst_activity_src(data)                                        ((0x00000020&(data))>>5)
#define MIS_IC2_STATUS_get_mst_activity(data)                                        ((0x00000020&(data))>>5)
#define MIS_IC2_STATUS_rff_shift                                                     (4)
#define MIS_IC2_STATUS_rff_mask                                                      (0x00000010)
#define MIS_IC2_STATUS_rff(data)                                                     (0x00000010&((data)<<4))
#define MIS_IC2_STATUS_rff_src(data)                                                 ((0x00000010&(data))>>4)
#define MIS_IC2_STATUS_get_rff(data)                                                 ((0x00000010&(data))>>4)
#define MIS_IC2_STATUS_rfne_shift                                                    (3)
#define MIS_IC2_STATUS_rfne_mask                                                     (0x00000008)
#define MIS_IC2_STATUS_rfne(data)                                                    (0x00000008&((data)<<3))
#define MIS_IC2_STATUS_rfne_src(data)                                                ((0x00000008&(data))>>3)
#define MIS_IC2_STATUS_get_rfne(data)                                                ((0x00000008&(data))>>3)
#define MIS_IC2_STATUS_tfe_shift                                                     (2)
#define MIS_IC2_STATUS_tfe_mask                                                      (0x00000004)
#define MIS_IC2_STATUS_tfe(data)                                                     (0x00000004&((data)<<2))
#define MIS_IC2_STATUS_tfe_src(data)                                                 ((0x00000004&(data))>>2)
#define MIS_IC2_STATUS_get_tfe(data)                                                 ((0x00000004&(data))>>2)
#define MIS_IC2_STATUS_tfnf_shift                                                    (1)
#define MIS_IC2_STATUS_tfnf_mask                                                     (0x00000002)
#define MIS_IC2_STATUS_tfnf(data)                                                    (0x00000002&((data)<<1))
#define MIS_IC2_STATUS_tfnf_src(data)                                                ((0x00000002&(data))>>1)
#define MIS_IC2_STATUS_get_tfnf(data)                                                ((0x00000002&(data))>>1)
#define MIS_IC2_STATUS_activity_shift                                                (0)
#define MIS_IC2_STATUS_activity_mask                                                 (0x00000001)
#define MIS_IC2_STATUS_activity(data)                                                (0x00000001&((data)<<0))
#define MIS_IC2_STATUS_activity_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_IC2_STATUS_get_activity(data)                                            ((0x00000001&(data))>>0)


#define MIS_IC2_TXFLR                                                                0x1801B774
#define MIS_IC2_TXFLR_reg_addr                                                       "0xB801B774"
#define MIS_IC2_TXFLR_reg                                                            0xB801B774
#define set_MIS_IC2_TXFLR_reg(data)   (*((volatile unsigned int*) MIS_IC2_TXFLR_reg)=data)
#define get_MIS_IC2_TXFLR_reg   (*((volatile unsigned int*) MIS_IC2_TXFLR_reg))
#define MIS_IC2_TXFLR_inst_adr                                                       "0x00DD"
#define MIS_IC2_TXFLR_inst                                                           0x00DD
#define MIS_IC2_TXFLR_txflr_shift                                                    (0)
#define MIS_IC2_TXFLR_txflr_mask                                                     (0x0000000F)
#define MIS_IC2_TXFLR_txflr(data)                                                    (0x0000000F&((data)<<0))
#define MIS_IC2_TXFLR_txflr_src(data)                                                ((0x0000000F&(data))>>0)
#define MIS_IC2_TXFLR_get_txflr(data)                                                ((0x0000000F&(data))>>0)


#define MIS_IC2_RXFLR                                                                0x1801B778
#define MIS_IC2_RXFLR_reg_addr                                                       "0xB801B778"
#define MIS_IC2_RXFLR_reg                                                            0xB801B778
#define set_MIS_IC2_RXFLR_reg(data)   (*((volatile unsigned int*) MIS_IC2_RXFLR_reg)=data)
#define get_MIS_IC2_RXFLR_reg   (*((volatile unsigned int*) MIS_IC2_RXFLR_reg))
#define MIS_IC2_RXFLR_inst_adr                                                       "0x00DE"
#define MIS_IC2_RXFLR_inst                                                           0x00DE
#define MIS_IC2_RXFLR_rxflr_shift                                                    (0)
#define MIS_IC2_RXFLR_rxflr_mask                                                     (0x0000000F)
#define MIS_IC2_RXFLR_rxflr(data)                                                    (0x0000000F&((data)<<0))
#define MIS_IC2_RXFLR_rxflr_src(data)                                                ((0x0000000F&(data))>>0)
#define MIS_IC2_RXFLR_get_rxflr(data)                                                ((0x0000000F&(data))>>0)


#define MIS_IC2_SDA_HOLD                                                             0x1801B77C
#define MIS_IC2_SDA_HOLD_reg_addr                                                    "0xB801B77C"
#define MIS_IC2_SDA_HOLD_reg                                                         0xB801B77C
#define set_MIS_IC2_SDA_HOLD_reg(data)   (*((volatile unsigned int*) MIS_IC2_SDA_HOLD_reg)=data)
#define get_MIS_IC2_SDA_HOLD_reg   (*((volatile unsigned int*) MIS_IC2_SDA_HOLD_reg))
#define MIS_IC2_SDA_HOLD_inst_adr                                                    "0x00DF"
#define MIS_IC2_SDA_HOLD_inst                                                        0x00DF
#define MIS_IC2_SDA_HOLD_sda_hold_shift                                              (0)
#define MIS_IC2_SDA_HOLD_sda_hold_mask                                               (0x0000FFFF)
#define MIS_IC2_SDA_HOLD_sda_hold(data)                                              (0x0000FFFF&((data)<<0))
#define MIS_IC2_SDA_HOLD_sda_hold_src(data)                                          ((0x0000FFFF&(data))>>0)
#define MIS_IC2_SDA_HOLD_get_sda_hold(data)                                          ((0x0000FFFF&(data))>>0)


#define MIS_IC2_TX_ABRT_SOURCE                                                       0x1801B780
#define MIS_IC2_TX_ABRT_SOURCE_reg_addr                                              "0xB801B780"
#define MIS_IC2_TX_ABRT_SOURCE_reg                                                   0xB801B780
#define set_MIS_IC2_TX_ABRT_SOURCE_reg(data)   (*((volatile unsigned int*) MIS_IC2_TX_ABRT_SOURCE_reg)=data)
#define get_MIS_IC2_TX_ABRT_SOURCE_reg   (*((volatile unsigned int*) MIS_IC2_TX_ABRT_SOURCE_reg))
#define MIS_IC2_TX_ABRT_SOURCE_inst_adr                                              "0x00E0"
#define MIS_IC2_TX_ABRT_SOURCE_inst                                                  0x00E0
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slvrd_intx_shift                                 (15)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slvrd_intx_mask                                  (0x00008000)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slvrd_intx(data)                                 (0x00008000&((data)<<15))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slvrd_intx_src(data)                             ((0x00008000&(data))>>15)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_slvrd_intx(data)                             ((0x00008000&(data))>>15)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slv_arblost_shift                                (14)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slv_arblost_mask                                 (0x00004000)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slv_arblost(data)                                (0x00004000&((data)<<14))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slv_arblost_src(data)                            ((0x00004000&(data))>>14)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_slv_arblost(data)                            ((0x00004000&(data))>>14)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slvflush_txfifo_shift                            (13)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slvflush_txfifo_mask                             (0x00002000)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slvflush_txfifo(data)                            (0x00002000&((data)<<13))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_slvflush_txfifo_src(data)                        ((0x00002000&(data))>>13)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_slvflush_txfifo(data)                        ((0x00002000&(data))>>13)
#define MIS_IC2_TX_ABRT_SOURCE_arb_lost_shift                                        (12)
#define MIS_IC2_TX_ABRT_SOURCE_arb_lost_mask                                         (0x00001000)
#define MIS_IC2_TX_ABRT_SOURCE_arb_lost(data)                                        (0x00001000&((data)<<12))
#define MIS_IC2_TX_ABRT_SOURCE_arb_lost_src(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC2_TX_ABRT_SOURCE_get_arb_lost(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC2_TX_ABRT_SOURCE_arb_master_dis_shift                                  (11)
#define MIS_IC2_TX_ABRT_SOURCE_arb_master_dis_mask                                   (0x00000800)
#define MIS_IC2_TX_ABRT_SOURCE_arb_master_dis(data)                                  (0x00000800&((data)<<11))
#define MIS_IC2_TX_ABRT_SOURCE_arb_master_dis_src(data)                              ((0x00000800&(data))>>11)
#define MIS_IC2_TX_ABRT_SOURCE_get_arb_master_dis(data)                              ((0x00000800&(data))>>11)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_shift                             (10)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_mask                              (0x00000400)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10b_rd_norstrt(data)                             (0x00000400&((data)<<10))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_src(data)                         ((0x00000400&(data))>>10)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_10b_rd_norstrt(data)                         ((0x00000400&(data))>>10)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_sbyte_norstrt_shift                              (9)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_sbyte_norstrt_mask                               (0x00000200)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_sbyte_norstrt(data)                              (0x00000200&((data)<<9))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_sbyte_norstrt_src(data)                          ((0x00000200&(data))>>9)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_sbyte_norstrt(data)                          ((0x00000200&(data))>>9)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_hs_norstrt_shift                                 (8)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_hs_norstrt_mask                                  (0x00000100)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_hs_norstrt(data)                                 (0x00000100&((data)<<8))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_hs_norstrt_src(data)                             ((0x00000100&(data))>>8)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_hs_norstrt(data)                             ((0x00000100&(data))>>8)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_sbyte_ackdet_shift                               (7)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_sbyte_ackdet_mask                                (0x00000080)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_sbyte_ackdet(data)                               (0x00000080&((data)<<7))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_sbyte_ackdet_src(data)                           ((0x00000080&(data))>>7)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_sbyte_ackdet(data)                           ((0x00000080&(data))>>7)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_hs_ackdet_shift                                  (6)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_hs_ackdet_mask                                   (0x00000040)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_hs_ackdet(data)                                  (0x00000040&((data)<<6))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_hs_ackdet_src(data)                              ((0x00000040&(data))>>6)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_hs_ackdet(data)                              ((0x00000040&(data))>>6)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_gcall_read_shift                                 (5)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_gcall_read_mask                                  (0x00000020)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_gcall_read(data)                                 (0x00000020&((data)<<5))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_gcall_read_src(data)                             ((0x00000020&(data))>>5)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_gcall_read(data)                             ((0x00000020&(data))>>5)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_gcall_noack_shift                                (4)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_gcall_noack_mask                                 (0x00000010)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_gcall_noack(data)                                (0x00000010&((data)<<4))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_gcall_noack_src(data)                            ((0x00000010&(data))>>4)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_gcall_noack(data)                            ((0x00000010&(data))>>4)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_txdata_noack_shift                               (3)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_txdata_noack_mask                                (0x00000008)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_txdata_noack(data)                               (0x00000008&((data)<<3))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_txdata_noack_src(data)                           ((0x00000008&(data))>>3)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_txdata_noack(data)                           ((0x00000008&(data))>>3)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10addr2_noack_shift                              (2)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10addr2_noack_mask                               (0x00000004)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10addr2_noack(data)                              (0x00000004&((data)<<2))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10addr2_noack_src(data)                          ((0x00000004&(data))>>2)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_10addr2_noack(data)                          ((0x00000004&(data))>>2)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10addr1_noack_shift                              (1)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10addr1_noack_mask                               (0x00000002)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10addr1_noack(data)                              (0x00000002&((data)<<1))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_10addr1_noack_src(data)                          ((0x00000002&(data))>>1)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_10addr1_noack(data)                          ((0x00000002&(data))>>1)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_7b_addr_noack_shift                              (0)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_7b_addr_noack_mask                               (0x00000001)
#define MIS_IC2_TX_ABRT_SOURCE_abrt_7b_addr_noack(data)                              (0x00000001&((data)<<0))
#define MIS_IC2_TX_ABRT_SOURCE_abrt_7b_addr_noack_src(data)                          ((0x00000001&(data))>>0)
#define MIS_IC2_TX_ABRT_SOURCE_get_abrt_7b_addr_noack(data)                          ((0x00000001&(data))>>0)


#define MIS_IC2_SLV_DATA_NACK_ONLY                                                   0x1801B784
#define MIS_IC2_SLV_DATA_NACK_ONLY_reg_addr                                          "0xB801B784"
#define MIS_IC2_SLV_DATA_NACK_ONLY_reg                                               0xB801B784
#define set_MIS_IC2_SLV_DATA_NACK_ONLY_reg(data)   (*((volatile unsigned int*) MIS_IC2_SLV_DATA_NACK_ONLY_reg)=data)
#define get_MIS_IC2_SLV_DATA_NACK_ONLY_reg   (*((volatile unsigned int*) MIS_IC2_SLV_DATA_NACK_ONLY_reg))
#define MIS_IC2_SLV_DATA_NACK_ONLY_inst_adr                                          "0x00E1"
#define MIS_IC2_SLV_DATA_NACK_ONLY_inst                                              0x00E1
#define MIS_IC2_SLV_DATA_NACK_ONLY_nack_shift                                        (0)
#define MIS_IC2_SLV_DATA_NACK_ONLY_nack_mask                                         (0x00000001)
#define MIS_IC2_SLV_DATA_NACK_ONLY_nack(data)                                        (0x00000001&((data)<<0))
#define MIS_IC2_SLV_DATA_NACK_ONLY_nack_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC2_SLV_DATA_NACK_ONLY_get_nack(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC2_DMA_CR                                                               0x1801B788
#define MIS_IC2_DMA_CR_reg_addr                                                      "0xB801B788"
#define MIS_IC2_DMA_CR_reg                                                           0xB801B788
#define set_MIS_IC2_DMA_CR_reg(data)   (*((volatile unsigned int*) MIS_IC2_DMA_CR_reg)=data)
#define get_MIS_IC2_DMA_CR_reg   (*((volatile unsigned int*) MIS_IC2_DMA_CR_reg))
#define MIS_IC2_DMA_CR_inst_adr                                                      "0x00E2"
#define MIS_IC2_DMA_CR_inst                                                          0x00E2
#define MIS_IC2_DMA_CR_tdmae_shift                                                   (1)
#define MIS_IC2_DMA_CR_tdmae_mask                                                    (0x00000002)
#define MIS_IC2_DMA_CR_tdmae(data)                                                   (0x00000002&((data)<<1))
#define MIS_IC2_DMA_CR_tdmae_src(data)                                               ((0x00000002&(data))>>1)
#define MIS_IC2_DMA_CR_get_tdmae(data)                                               ((0x00000002&(data))>>1)
#define MIS_IC2_DMA_CR_rdmae_shift                                                   (0)
#define MIS_IC2_DMA_CR_rdmae_mask                                                    (0x00000001)
#define MIS_IC2_DMA_CR_rdmae(data)                                                   (0x00000001&((data)<<0))
#define MIS_IC2_DMA_CR_rdmae_src(data)                                               ((0x00000001&(data))>>0)
#define MIS_IC2_DMA_CR_get_rdmae(data)                                               ((0x00000001&(data))>>0)


#define MIS_IC2_DMA_TDLR                                                             0x1801B78C
#define MIS_IC2_DMA_TDLR_reg_addr                                                    "0xB801B78C"
#define MIS_IC2_DMA_TDLR_reg                                                         0xB801B78C
#define set_MIS_IC2_DMA_TDLR_reg(data)   (*((volatile unsigned int*) MIS_IC2_DMA_TDLR_reg)=data)
#define get_MIS_IC2_DMA_TDLR_reg   (*((volatile unsigned int*) MIS_IC2_DMA_TDLR_reg))
#define MIS_IC2_DMA_TDLR_inst_adr                                                    "0x00E3"
#define MIS_IC2_DMA_TDLR_inst                                                        0x00E3
#define MIS_IC2_DMA_TDLR_dmatdl_shift                                                (0)
#define MIS_IC2_DMA_TDLR_dmatdl_mask                                                 (0x00000007)
#define MIS_IC2_DMA_TDLR_dmatdl(data)                                                (0x00000007&((data)<<0))
#define MIS_IC2_DMA_TDLR_dmatdl_src(data)                                            ((0x00000007&(data))>>0)
#define MIS_IC2_DMA_TDLR_get_dmatdl(data)                                            ((0x00000007&(data))>>0)


#define MIS_IC2_DMA_RDLR                                                             0x1801B790
#define MIS_IC2_DMA_RDLR_reg_addr                                                    "0xB801B790"
#define MIS_IC2_DMA_RDLR_reg                                                         0xB801B790
#define set_MIS_IC2_DMA_RDLR_reg(data)   (*((volatile unsigned int*) MIS_IC2_DMA_RDLR_reg)=data)
#define get_MIS_IC2_DMA_RDLR_reg   (*((volatile unsigned int*) MIS_IC2_DMA_RDLR_reg))
#define MIS_IC2_DMA_RDLR_inst_adr                                                    "0x00E4"
#define MIS_IC2_DMA_RDLR_inst                                                        0x00E4
#define MIS_IC2_DMA_RDLR_dmardl_shift                                                (0)
#define MIS_IC2_DMA_RDLR_dmardl_mask                                                 (0x0000000F)
#define MIS_IC2_DMA_RDLR_dmardl(data)                                                (0x0000000F&((data)<<0))
#define MIS_IC2_DMA_RDLR_dmardl_src(data)                                            ((0x0000000F&(data))>>0)
#define MIS_IC2_DMA_RDLR_get_dmardl(data)                                            ((0x0000000F&(data))>>0)


#define MIS_IC2_SDA_SETUP                                                            0x1801B794
#define MIS_IC2_SDA_SETUP_reg_addr                                                   "0xB801B794"
#define MIS_IC2_SDA_SETUP_reg                                                        0xB801B794
#define set_MIS_IC2_SDA_SETUP_reg(data)   (*((volatile unsigned int*) MIS_IC2_SDA_SETUP_reg)=data)
#define get_MIS_IC2_SDA_SETUP_reg   (*((volatile unsigned int*) MIS_IC2_SDA_SETUP_reg))
#define MIS_IC2_SDA_SETUP_inst_adr                                                   "0x00E5"
#define MIS_IC2_SDA_SETUP_inst                                                       0x00E5
#define MIS_IC2_SDA_SETUP_sda_setup_shift                                            (0)
#define MIS_IC2_SDA_SETUP_sda_setup_mask                                             (0x000000FF)
#define MIS_IC2_SDA_SETUP_sda_setup(data)                                            (0x000000FF&((data)<<0))
#define MIS_IC2_SDA_SETUP_sda_setup_src(data)                                        ((0x000000FF&(data))>>0)
#define MIS_IC2_SDA_SETUP_get_sda_setup(data)                                        ((0x000000FF&(data))>>0)


#define MIS_IC2_ACK_GENERAL_CALL                                                     0x1801B798
#define MIS_IC2_ACK_GENERAL_CALL_reg_addr                                            "0xB801B798"
#define MIS_IC2_ACK_GENERAL_CALL_reg                                                 0xB801B798
#define set_MIS_IC2_ACK_GENERAL_CALL_reg(data)   (*((volatile unsigned int*) MIS_IC2_ACK_GENERAL_CALL_reg)=data)
#define get_MIS_IC2_ACK_GENERAL_CALL_reg   (*((volatile unsigned int*) MIS_IC2_ACK_GENERAL_CALL_reg))
#define MIS_IC2_ACK_GENERAL_CALL_inst_adr                                            "0x00E6"
#define MIS_IC2_ACK_GENERAL_CALL_inst                                                0x00E6
#define MIS_IC2_ACK_GENERAL_CALL_ack_gen_call_shift                                  (0)
#define MIS_IC2_ACK_GENERAL_CALL_ack_gen_call_mask                                   (0x00000001)
#define MIS_IC2_ACK_GENERAL_CALL_ack_gen_call(data)                                  (0x00000001&((data)<<0))
#define MIS_IC2_ACK_GENERAL_CALL_ack_gen_call_src(data)                              ((0x00000001&(data))>>0)
#define MIS_IC2_ACK_GENERAL_CALL_get_ack_gen_call(data)                              ((0x00000001&(data))>>0)


#define MIS_IC2_ENABLE_STATUS                                                        0x1801B79C
#define MIS_IC2_ENABLE_STATUS_reg_addr                                               "0xB801B79C"
#define MIS_IC2_ENABLE_STATUS_reg                                                    0xB801B79C
#define set_MIS_IC2_ENABLE_STATUS_reg(data)   (*((volatile unsigned int*) MIS_IC2_ENABLE_STATUS_reg)=data)
#define get_MIS_IC2_ENABLE_STATUS_reg   (*((volatile unsigned int*) MIS_IC2_ENABLE_STATUS_reg))
#define MIS_IC2_ENABLE_STATUS_inst_adr                                               "0x00E7"
#define MIS_IC2_ENABLE_STATUS_inst                                                   0x00E7
#define MIS_IC2_ENABLE_STATUS_slv_rx_data_lost_shift                                 (2)
#define MIS_IC2_ENABLE_STATUS_slv_rx_data_lost_mask                                  (0x00000004)
#define MIS_IC2_ENABLE_STATUS_slv_rx_data_lost(data)                                 (0x00000004&((data)<<2))
#define MIS_IC2_ENABLE_STATUS_slv_rx_data_lost_src(data)                             ((0x00000004&(data))>>2)
#define MIS_IC2_ENABLE_STATUS_get_slv_rx_data_lost(data)                             ((0x00000004&(data))>>2)
#define MIS_IC2_ENABLE_STATUS_slv_disabled_whi_shift                                 (1)
#define MIS_IC2_ENABLE_STATUS_slv_disabled_whi_mask                                  (0x00000002)
#define MIS_IC2_ENABLE_STATUS_slv_disabled_whi(data)                                 (0x00000002&((data)<<1))
#define MIS_IC2_ENABLE_STATUS_slv_disabled_whi_src(data)                             ((0x00000002&(data))>>1)
#define MIS_IC2_ENABLE_STATUS_get_slv_disabled_whi(data)                             ((0x00000002&(data))>>1)
#define MIS_IC2_ENABLE_STATUS_ic_en_shift                                            (0)
#define MIS_IC2_ENABLE_STATUS_ic_en_mask                                             (0x00000001)
#define MIS_IC2_ENABLE_STATUS_ic_en(data)                                            (0x00000001&((data)<<0))
#define MIS_IC2_ENABLE_STATUS_ic_en_src(data)                                        ((0x00000001&(data))>>0)
#define MIS_IC2_ENABLE_STATUS_get_ic_en(data)                                        ((0x00000001&(data))>>0)


#define MIS_IC2_COMP_PARAM_1                                                         0x1801B7F4
#define MIS_IC2_COMP_PARAM_1_reg_addr                                                "0xB801B7F4"
#define MIS_IC2_COMP_PARAM_1_reg                                                     0xB801B7F4
#define set_MIS_IC2_COMP_PARAM_1_reg(data)   (*((volatile unsigned int*) MIS_IC2_COMP_PARAM_1_reg)=data)
#define get_MIS_IC2_COMP_PARAM_1_reg   (*((volatile unsigned int*) MIS_IC2_COMP_PARAM_1_reg))
#define MIS_IC2_COMP_PARAM_1_inst_adr                                                "0x00FD"
#define MIS_IC2_COMP_PARAM_1_inst                                                    0x00FD
#define MIS_IC2_COMP_PARAM_1_tx_buffer_depth_shift                                   (16)
#define MIS_IC2_COMP_PARAM_1_tx_buffer_depth_mask                                    (0x00FF0000)
#define MIS_IC2_COMP_PARAM_1_tx_buffer_depth(data)                                   (0x00FF0000&((data)<<16))
#define MIS_IC2_COMP_PARAM_1_tx_buffer_depth_src(data)                               ((0x00FF0000&(data))>>16)
#define MIS_IC2_COMP_PARAM_1_get_tx_buffer_depth(data)                               ((0x00FF0000&(data))>>16)
#define MIS_IC2_COMP_PARAM_1_rx_buffer_depth_shift                                   (8)
#define MIS_IC2_COMP_PARAM_1_rx_buffer_depth_mask                                    (0x0000FF00)
#define MIS_IC2_COMP_PARAM_1_rx_buffer_depth(data)                                   (0x0000FF00&((data)<<8))
#define MIS_IC2_COMP_PARAM_1_rx_buffer_depth_src(data)                               ((0x0000FF00&(data))>>8)
#define MIS_IC2_COMP_PARAM_1_get_rx_buffer_depth(data)                               ((0x0000FF00&(data))>>8)
#define MIS_IC2_COMP_PARAM_1_add_encoded_params_shift                                (7)
#define MIS_IC2_COMP_PARAM_1_add_encoded_params_mask                                 (0x00000080)
#define MIS_IC2_COMP_PARAM_1_add_encoded_params(data)                                (0x00000080&((data)<<7))
#define MIS_IC2_COMP_PARAM_1_add_encoded_params_src(data)                            ((0x00000080&(data))>>7)
#define MIS_IC2_COMP_PARAM_1_get_add_encoded_params(data)                            ((0x00000080&(data))>>7)
#define MIS_IC2_COMP_PARAM_1_has_dma_shift                                           (6)
#define MIS_IC2_COMP_PARAM_1_has_dma_mask                                            (0x00000040)
#define MIS_IC2_COMP_PARAM_1_has_dma(data)                                           (0x00000040&((data)<<6))
#define MIS_IC2_COMP_PARAM_1_has_dma_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC2_COMP_PARAM_1_get_has_dma(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC2_COMP_PARAM_1_intr_io_shift                                           (5)
#define MIS_IC2_COMP_PARAM_1_intr_io_mask                                            (0x00000020)
#define MIS_IC2_COMP_PARAM_1_intr_io(data)                                           (0x00000020&((data)<<5))
#define MIS_IC2_COMP_PARAM_1_intr_io_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC2_COMP_PARAM_1_get_intr_io(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC2_COMP_PARAM_1_hc_count_values_shift                                   (4)
#define MIS_IC2_COMP_PARAM_1_hc_count_values_mask                                    (0x00000010)
#define MIS_IC2_COMP_PARAM_1_hc_count_values(data)                                   (0x00000010&((data)<<4))
#define MIS_IC2_COMP_PARAM_1_hc_count_values_src(data)                               ((0x00000010&(data))>>4)
#define MIS_IC2_COMP_PARAM_1_get_hc_count_values(data)                               ((0x00000010&(data))>>4)
#define MIS_IC2_COMP_PARAM_1_max_speed_mode_shift                                    (2)
#define MIS_IC2_COMP_PARAM_1_max_speed_mode_mask                                     (0x0000000C)
#define MIS_IC2_COMP_PARAM_1_max_speed_mode(data)                                    (0x0000000C&((data)<<2))
#define MIS_IC2_COMP_PARAM_1_max_speed_mode_src(data)                                ((0x0000000C&(data))>>2)
#define MIS_IC2_COMP_PARAM_1_get_max_speed_mode(data)                                ((0x0000000C&(data))>>2)
#define MIS_IC2_COMP_PARAM_1_apb_data_width_shift                                    (0)
#define MIS_IC2_COMP_PARAM_1_apb_data_width_mask                                     (0x00000003)
#define MIS_IC2_COMP_PARAM_1_apb_data_width(data)                                    (0x00000003&((data)<<0))
#define MIS_IC2_COMP_PARAM_1_apb_data_width_src(data)                                ((0x00000003&(data))>>0)
#define MIS_IC2_COMP_PARAM_1_get_apb_data_width(data)                                ((0x00000003&(data))>>0)


#define MIS_IC2_COMP_VERSION                                                         0x1801B7F8
#define MIS_IC2_COMP_VERSION_reg_addr                                                "0xB801B7F8"
#define MIS_IC2_COMP_VERSION_reg                                                     0xB801B7F8
#define set_MIS_IC2_COMP_VERSION_reg(data)   (*((volatile unsigned int*) MIS_IC2_COMP_VERSION_reg)=data)
#define get_MIS_IC2_COMP_VERSION_reg   (*((volatile unsigned int*) MIS_IC2_COMP_VERSION_reg))
#define MIS_IC2_COMP_VERSION_inst_adr                                                "0x00FE"
#define MIS_IC2_COMP_VERSION_inst                                                    0x00FE
#define MIS_IC2_COMP_VERSION_ic_comp_version_shift                                   (0)
#define MIS_IC2_COMP_VERSION_ic_comp_version_mask                                    (0xFFFFFFFF)
#define MIS_IC2_COMP_VERSION_ic_comp_version(data)                                   (0xFFFFFFFF&((data)<<0))
#define MIS_IC2_COMP_VERSION_ic_comp_version_src(data)                               ((0xFFFFFFFF&(data))>>0)
#define MIS_IC2_COMP_VERSION_get_ic_comp_version(data)                               ((0xFFFFFFFF&(data))>>0)


#define MIS_IC2_COMP_TYPE                                                            0x1801B7FC
#define MIS_IC2_COMP_TYPE_reg_addr                                                   "0xB801B7FC"
#define MIS_IC2_COMP_TYPE_reg                                                        0xB801B7FC
#define set_MIS_IC2_COMP_TYPE_reg(data)   (*((volatile unsigned int*) MIS_IC2_COMP_TYPE_reg)=data)
#define get_MIS_IC2_COMP_TYPE_reg   (*((volatile unsigned int*) MIS_IC2_COMP_TYPE_reg))
#define MIS_IC2_COMP_TYPE_inst_adr                                                   "0x00FF"
#define MIS_IC2_COMP_TYPE_inst                                                       0x00FF
#define MIS_IC2_COMP_TYPE_ic_comp_type_shift                                         (0)
#define MIS_IC2_COMP_TYPE_ic_comp_type_mask                                          (0xFFFFFFFF)
#define MIS_IC2_COMP_TYPE_ic_comp_type(data)                                         (0xFFFFFFFF&((data)<<0))
#define MIS_IC2_COMP_TYPE_ic_comp_type_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define MIS_IC2_COMP_TYPE_get_ic_comp_type(data)                                     ((0xFFFFFFFF&(data))>>0)


#define MIS_IC3_CON                                                                  0x1801B900
#define MIS_IC3_CON_reg_addr                                                         "0xB801B900"
#define MIS_IC3_CON_reg                                                              0xB801B900
#define set_MIS_IC3_CON_reg(data)   (*((volatile unsigned int*) MIS_IC3_CON_reg)=data)
#define get_MIS_IC3_CON_reg   (*((volatile unsigned int*) MIS_IC3_CON_reg))
#define MIS_IC3_CON_inst_adr                                                         "0x0040"
#define MIS_IC3_CON_inst                                                             0x0040
#define MIS_IC3_CON_ic_slave_disable_shift                                           (6)
#define MIS_IC3_CON_ic_slave_disable_mask                                            (0x00000040)
#define MIS_IC3_CON_ic_slave_disable(data)                                           (0x00000040&((data)<<6))
#define MIS_IC3_CON_ic_slave_disable_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC3_CON_get_ic_slave_disable(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC3_CON_ic_restart_en_shift                                              (5)
#define MIS_IC3_CON_ic_restart_en_mask                                               (0x00000020)
#define MIS_IC3_CON_ic_restart_en(data)                                              (0x00000020&((data)<<5))
#define MIS_IC3_CON_ic_restart_en_src(data)                                          ((0x00000020&(data))>>5)
#define MIS_IC3_CON_get_ic_restart_en(data)                                          ((0x00000020&(data))>>5)
#define MIS_IC3_CON_ic_10bitaddr_master_shift                                        (4)
#define MIS_IC3_CON_ic_10bitaddr_master_mask                                         (0x00000010)
#define MIS_IC3_CON_ic_10bitaddr_master(data)                                        (0x00000010&((data)<<4))
#define MIS_IC3_CON_ic_10bitaddr_master_src(data)                                    ((0x00000010&(data))>>4)
#define MIS_IC3_CON_get_ic_10bitaddr_master(data)                                    ((0x00000010&(data))>>4)
#define MIS_IC3_CON_ic_10bitaddr_slave_shift                                         (3)
#define MIS_IC3_CON_ic_10bitaddr_slave_mask                                          (0x00000008)
#define MIS_IC3_CON_ic_10bitaddr_slave(data)                                         (0x00000008&((data)<<3))
#define MIS_IC3_CON_ic_10bitaddr_slave_src(data)                                     ((0x00000008&(data))>>3)
#define MIS_IC3_CON_get_ic_10bitaddr_slave(data)                                     ((0x00000008&(data))>>3)
#define MIS_IC3_CON_speed_shift                                                      (1)
#define MIS_IC3_CON_speed_mask                                                       (0x00000006)
#define MIS_IC3_CON_speed(data)                                                      (0x00000006&((data)<<1))
#define MIS_IC3_CON_speed_src(data)                                                  ((0x00000006&(data))>>1)
#define MIS_IC3_CON_get_speed(data)                                                  ((0x00000006&(data))>>1)
#define MIS_IC3_CON_master_mode_shift                                                (0)
#define MIS_IC3_CON_master_mode_mask                                                 (0x00000001)
#define MIS_IC3_CON_master_mode(data)                                                (0x00000001&((data)<<0))
#define MIS_IC3_CON_master_mode_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_IC3_CON_get_master_mode(data)                                            ((0x00000001&(data))>>0)


#define MIS_IC3_TAR                                                                  0x1801B904
#define MIS_IC3_TAR_reg_addr                                                         "0xB801B904"
#define MIS_IC3_TAR_reg                                                              0xB801B904
#define set_MIS_IC3_TAR_reg(data)   (*((volatile unsigned int*) MIS_IC3_TAR_reg)=data)
#define get_MIS_IC3_TAR_reg   (*((volatile unsigned int*) MIS_IC3_TAR_reg))
#define MIS_IC3_TAR_inst_adr                                                         "0x0041"
#define MIS_IC3_TAR_inst                                                             0x0041
#define MIS_IC3_TAR_ic_10bitaddr_master_shift                                        (12)
#define MIS_IC3_TAR_ic_10bitaddr_master_mask                                         (0x00001000)
#define MIS_IC3_TAR_ic_10bitaddr_master(data)                                        (0x00001000&((data)<<12))
#define MIS_IC3_TAR_ic_10bitaddr_master_src(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC3_TAR_get_ic_10bitaddr_master(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC3_TAR_special_shift                                                    (11)
#define MIS_IC3_TAR_special_mask                                                     (0x00000800)
#define MIS_IC3_TAR_special(data)                                                    (0x00000800&((data)<<11))
#define MIS_IC3_TAR_special_src(data)                                                ((0x00000800&(data))>>11)
#define MIS_IC3_TAR_get_special(data)                                                ((0x00000800&(data))>>11)
#define MIS_IC3_TAR_gc_or_start_shift                                                (10)
#define MIS_IC3_TAR_gc_or_start_mask                                                 (0x00000400)
#define MIS_IC3_TAR_gc_or_start(data)                                                (0x00000400&((data)<<10))
#define MIS_IC3_TAR_gc_or_start_src(data)                                            ((0x00000400&(data))>>10)
#define MIS_IC3_TAR_get_gc_or_start(data)                                            ((0x00000400&(data))>>10)
#define MIS_IC3_TAR_ic_tar_shift                                                     (0)
#define MIS_IC3_TAR_ic_tar_mask                                                      (0x000003FF)
#define MIS_IC3_TAR_ic_tar(data)                                                     (0x000003FF&((data)<<0))
#define MIS_IC3_TAR_ic_tar_src(data)                                                 ((0x000003FF&(data))>>0)
#define MIS_IC3_TAR_get_ic_tar(data)                                                 ((0x000003FF&(data))>>0)


#define MIS_IC3_SAR                                                                  0x1801B908
#define MIS_IC3_SAR_reg_addr                                                         "0xB801B908"
#define MIS_IC3_SAR_reg                                                              0xB801B908
#define set_MIS_IC3_SAR_reg(data)   (*((volatile unsigned int*) MIS_IC3_SAR_reg)=data)
#define get_MIS_IC3_SAR_reg   (*((volatile unsigned int*) MIS_IC3_SAR_reg))
#define MIS_IC3_SAR_inst_adr                                                         "0x0042"
#define MIS_IC3_SAR_inst                                                             0x0042
#define MIS_IC3_SAR_ic_sar_shift                                                     (0)
#define MIS_IC3_SAR_ic_sar_mask                                                      (0x000003FF)
#define MIS_IC3_SAR_ic_sar(data)                                                     (0x000003FF&((data)<<0))
#define MIS_IC3_SAR_ic_sar_src(data)                                                 ((0x000003FF&(data))>>0)
#define MIS_IC3_SAR_get_ic_sar(data)                                                 ((0x000003FF&(data))>>0)


#define MIS_IC3_HS_MADDR                                                             0x1801B90C
#define MIS_IC3_HS_MADDR_reg_addr                                                    "0xB801B90C"
#define MIS_IC3_HS_MADDR_reg                                                         0xB801B90C
#define set_MIS_IC3_HS_MADDR_reg(data)   (*((volatile unsigned int*) MIS_IC3_HS_MADDR_reg)=data)
#define get_MIS_IC3_HS_MADDR_reg   (*((volatile unsigned int*) MIS_IC3_HS_MADDR_reg))
#define MIS_IC3_HS_MADDR_inst_adr                                                    "0x0043"
#define MIS_IC3_HS_MADDR_inst                                                        0x0043
#define MIS_IC3_HS_MADDR_ic_hs_mar_shift                                             (0)
#define MIS_IC3_HS_MADDR_ic_hs_mar_mask                                              (0x00000007)
#define MIS_IC3_HS_MADDR_ic_hs_mar(data)                                             (0x00000007&((data)<<0))
#define MIS_IC3_HS_MADDR_ic_hs_mar_src(data)                                         ((0x00000007&(data))>>0)
#define MIS_IC3_HS_MADDR_get_ic_hs_mar(data)                                         ((0x00000007&(data))>>0)


#define MIS_IC3_DATA_CMD                                                             0x1801B910
#define MIS_IC3_DATA_CMD_reg_addr                                                    "0xB801B910"
#define MIS_IC3_DATA_CMD_reg                                                         0xB801B910
#define set_MIS_IC3_DATA_CMD_reg(data)   (*((volatile unsigned int*) MIS_IC3_DATA_CMD_reg)=data)
#define get_MIS_IC3_DATA_CMD_reg   (*((volatile unsigned int*) MIS_IC3_DATA_CMD_reg))
#define MIS_IC3_DATA_CMD_inst_adr                                                    "0x0044"
#define MIS_IC3_DATA_CMD_inst                                                        0x0044
#define MIS_IC3_DATA_CMD_restart_shift                                               (10)
#define MIS_IC3_DATA_CMD_restart_mask                                                (0x00000400)
#define MIS_IC3_DATA_CMD_restart(data)                                               (0x00000400&((data)<<10))
#define MIS_IC3_DATA_CMD_restart_src(data)                                           ((0x00000400&(data))>>10)
#define MIS_IC3_DATA_CMD_get_restart(data)                                           ((0x00000400&(data))>>10)
#define MIS_IC3_DATA_CMD_stop_shift                                                  (9)
#define MIS_IC3_DATA_CMD_stop_mask                                                   (0x00000200)
#define MIS_IC3_DATA_CMD_stop(data)                                                  (0x00000200&((data)<<9))
#define MIS_IC3_DATA_CMD_stop_src(data)                                              ((0x00000200&(data))>>9)
#define MIS_IC3_DATA_CMD_get_stop(data)                                              ((0x00000200&(data))>>9)
#define MIS_IC3_DATA_CMD_cmd_shift                                                   (8)
#define MIS_IC3_DATA_CMD_cmd_mask                                                    (0x00000100)
#define MIS_IC3_DATA_CMD_cmd(data)                                                   (0x00000100&((data)<<8))
#define MIS_IC3_DATA_CMD_cmd_src(data)                                               ((0x00000100&(data))>>8)
#define MIS_IC3_DATA_CMD_get_cmd(data)                                               ((0x00000100&(data))>>8)
#define MIS_IC3_DATA_CMD_dat_shift                                                   (0)
#define MIS_IC3_DATA_CMD_dat_mask                                                    (0x000000FF)
#define MIS_IC3_DATA_CMD_dat(data)                                                   (0x000000FF&((data)<<0))
#define MIS_IC3_DATA_CMD_dat_src(data)                                               ((0x000000FF&(data))>>0)
#define MIS_IC3_DATA_CMD_get_dat(data)                                               ((0x000000FF&(data))>>0)


#define MIS_IC3_SS_SCL_HCNT                                                          0x1801B914
#define MIS_IC3_SS_SCL_HCNT_reg_addr                                                 "0xB801B914"
#define MIS_IC3_SS_SCL_HCNT_reg                                                      0xB801B914
#define set_MIS_IC3_SS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) MIS_IC3_SS_SCL_HCNT_reg)=data)
#define get_MIS_IC3_SS_SCL_HCNT_reg   (*((volatile unsigned int*) MIS_IC3_SS_SCL_HCNT_reg))
#define MIS_IC3_SS_SCL_HCNT_inst_adr                                                 "0x0045"
#define MIS_IC3_SS_SCL_HCNT_inst                                                     0x0045
#define MIS_IC3_SS_SCL_HCNT_ic_ss_scl_hcnt_shift                                     (0)
#define MIS_IC3_SS_SCL_HCNT_ic_ss_scl_hcnt_mask                                      (0x0000FFFF)
#define MIS_IC3_SS_SCL_HCNT_ic_ss_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC3_SS_SCL_HCNT_ic_ss_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC3_SS_SCL_HCNT_get_ic_ss_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC3_SS_SCL_LCNT                                                          0x1801B918
#define MIS_IC3_SS_SCL_LCNT_reg_addr                                                 "0xB801B918"
#define MIS_IC3_SS_SCL_LCNT_reg                                                      0xB801B918
#define set_MIS_IC3_SS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) MIS_IC3_SS_SCL_LCNT_reg)=data)
#define get_MIS_IC3_SS_SCL_LCNT_reg   (*((volatile unsigned int*) MIS_IC3_SS_SCL_LCNT_reg))
#define MIS_IC3_SS_SCL_LCNT_inst_adr                                                 "0x0046"
#define MIS_IC3_SS_SCL_LCNT_inst                                                     0x0046
#define MIS_IC3_SS_SCL_LCNT_ic_ss_scl_lcnt_shift                                     (0)
#define MIS_IC3_SS_SCL_LCNT_ic_ss_scl_lcnt_mask                                      (0x0000FFFF)
#define MIS_IC3_SS_SCL_LCNT_ic_ss_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC3_SS_SCL_LCNT_ic_ss_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC3_SS_SCL_LCNT_get_ic_ss_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC3_FS_SCL_HCNT                                                          0x1801B91C
#define MIS_IC3_FS_SCL_HCNT_reg_addr                                                 "0xB801B91C"
#define MIS_IC3_FS_SCL_HCNT_reg                                                      0xB801B91C
#define set_MIS_IC3_FS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) MIS_IC3_FS_SCL_HCNT_reg)=data)
#define get_MIS_IC3_FS_SCL_HCNT_reg   (*((volatile unsigned int*) MIS_IC3_FS_SCL_HCNT_reg))
#define MIS_IC3_FS_SCL_HCNT_inst_adr                                                 "0x0047"
#define MIS_IC3_FS_SCL_HCNT_inst                                                     0x0047
#define MIS_IC3_FS_SCL_HCNT_ic_fs_scl_hcnt_shift                                     (0)
#define MIS_IC3_FS_SCL_HCNT_ic_fs_scl_hcnt_mask                                      (0x0000FFFF)
#define MIS_IC3_FS_SCL_HCNT_ic_fs_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC3_FS_SCL_HCNT_ic_fs_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC3_FS_SCL_HCNT_get_ic_fs_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC3_FS_SCL_LCNT                                                          0x1801B920
#define MIS_IC3_FS_SCL_LCNT_reg_addr                                                 "0xB801B920"
#define MIS_IC3_FS_SCL_LCNT_reg                                                      0xB801B920
#define set_MIS_IC3_FS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) MIS_IC3_FS_SCL_LCNT_reg)=data)
#define get_MIS_IC3_FS_SCL_LCNT_reg   (*((volatile unsigned int*) MIS_IC3_FS_SCL_LCNT_reg))
#define MIS_IC3_FS_SCL_LCNT_inst_adr                                                 "0x0048"
#define MIS_IC3_FS_SCL_LCNT_inst                                                     0x0048
#define MIS_IC3_FS_SCL_LCNT_ic_fs_scl_lcnt_shift                                     (0)
#define MIS_IC3_FS_SCL_LCNT_ic_fs_scl_lcnt_mask                                      (0x0000FFFF)
#define MIS_IC3_FS_SCL_LCNT_ic_fs_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC3_FS_SCL_LCNT_ic_fs_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC3_FS_SCL_LCNT_get_ic_fs_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC3_INTR_STAT                                                            0x1801B92C
#define MIS_IC3_INTR_STAT_reg_addr                                                   "0xB801B92C"
#define MIS_IC3_INTR_STAT_reg                                                        0xB801B92C
#define set_MIS_IC3_INTR_STAT_reg(data)   (*((volatile unsigned int*) MIS_IC3_INTR_STAT_reg)=data)
#define get_MIS_IC3_INTR_STAT_reg   (*((volatile unsigned int*) MIS_IC3_INTR_STAT_reg))
#define MIS_IC3_INTR_STAT_inst_adr                                                   "0x004B"
#define MIS_IC3_INTR_STAT_inst                                                       0x004B
#define MIS_IC3_INTR_STAT_r_gen_call_shift                                           (11)
#define MIS_IC3_INTR_STAT_r_gen_call_mask                                            (0x00000800)
#define MIS_IC3_INTR_STAT_r_gen_call(data)                                           (0x00000800&((data)<<11))
#define MIS_IC3_INTR_STAT_r_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC3_INTR_STAT_get_r_gen_call(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC3_INTR_STAT_r_start_det_shift                                          (10)
#define MIS_IC3_INTR_STAT_r_start_det_mask                                           (0x00000400)
#define MIS_IC3_INTR_STAT_r_start_det(data)                                          (0x00000400&((data)<<10))
#define MIS_IC3_INTR_STAT_r_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC3_INTR_STAT_get_r_start_det(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC3_INTR_STAT_r_stop_det_shift                                           (9)
#define MIS_IC3_INTR_STAT_r_stop_det_mask                                            (0x00000200)
#define MIS_IC3_INTR_STAT_r_stop_det(data)                                           (0x00000200&((data)<<9))
#define MIS_IC3_INTR_STAT_r_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC3_INTR_STAT_get_r_stop_det(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC3_INTR_STAT_r_activity_shift                                           (8)
#define MIS_IC3_INTR_STAT_r_activity_mask                                            (0x00000100)
#define MIS_IC3_INTR_STAT_r_activity(data)                                           (0x00000100&((data)<<8))
#define MIS_IC3_INTR_STAT_r_activity_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC3_INTR_STAT_get_r_activity(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC3_INTR_STAT_r_rx_done_shift                                            (7)
#define MIS_IC3_INTR_STAT_r_rx_done_mask                                             (0x00000080)
#define MIS_IC3_INTR_STAT_r_rx_done(data)                                            (0x00000080&((data)<<7))
#define MIS_IC3_INTR_STAT_r_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC3_INTR_STAT_get_r_rx_done(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC3_INTR_STAT_r_tx_abrt_shift                                            (6)
#define MIS_IC3_INTR_STAT_r_tx_abrt_mask                                             (0x00000040)
#define MIS_IC3_INTR_STAT_r_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define MIS_IC3_INTR_STAT_r_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC3_INTR_STAT_get_r_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC3_INTR_STAT_r_rd_req_shift                                             (5)
#define MIS_IC3_INTR_STAT_r_rd_req_mask                                              (0x00000020)
#define MIS_IC3_INTR_STAT_r_rd_req(data)                                             (0x00000020&((data)<<5))
#define MIS_IC3_INTR_STAT_r_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC3_INTR_STAT_get_r_rd_req(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC3_INTR_STAT_r_tx_empty_shift                                           (4)
#define MIS_IC3_INTR_STAT_r_tx_empty_mask                                            (0x00000010)
#define MIS_IC3_INTR_STAT_r_tx_empty(data)                                           (0x00000010&((data)<<4))
#define MIS_IC3_INTR_STAT_r_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC3_INTR_STAT_get_r_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC3_INTR_STAT_r_tx_over_shift                                            (3)
#define MIS_IC3_INTR_STAT_r_tx_over_mask                                             (0x00000008)
#define MIS_IC3_INTR_STAT_r_tx_over(data)                                            (0x00000008&((data)<<3))
#define MIS_IC3_INTR_STAT_r_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC3_INTR_STAT_get_r_tx_over(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC3_INTR_STAT_r_rx_full_shift                                            (2)
#define MIS_IC3_INTR_STAT_r_rx_full_mask                                             (0x00000004)
#define MIS_IC3_INTR_STAT_r_rx_full(data)                                            (0x00000004&((data)<<2))
#define MIS_IC3_INTR_STAT_r_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC3_INTR_STAT_get_r_rx_full(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC3_INTR_STAT_r_rx_over_shift                                            (1)
#define MIS_IC3_INTR_STAT_r_rx_over_mask                                             (0x00000002)
#define MIS_IC3_INTR_STAT_r_rx_over(data)                                            (0x00000002&((data)<<1))
#define MIS_IC3_INTR_STAT_r_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC3_INTR_STAT_get_r_rx_over(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC3_INTR_STAT_r_rx_under_shift                                           (0)
#define MIS_IC3_INTR_STAT_r_rx_under_mask                                            (0x00000001)
#define MIS_IC3_INTR_STAT_r_rx_under(data)                                           (0x00000001&((data)<<0))
#define MIS_IC3_INTR_STAT_r_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_IC3_INTR_STAT_get_r_rx_under(data)                                       ((0x00000001&(data))>>0)


#define MIS_IC3_INTR_MASK                                                            0x1801B930
#define MIS_IC3_INTR_MASK_reg_addr                                                   "0xB801B930"
#define MIS_IC3_INTR_MASK_reg                                                        0xB801B930
#define set_MIS_IC3_INTR_MASK_reg(data)   (*((volatile unsigned int*) MIS_IC3_INTR_MASK_reg)=data)
#define get_MIS_IC3_INTR_MASK_reg   (*((volatile unsigned int*) MIS_IC3_INTR_MASK_reg))
#define MIS_IC3_INTR_MASK_inst_adr                                                   "0x004C"
#define MIS_IC3_INTR_MASK_inst                                                       0x004C
#define MIS_IC3_INTR_MASK_m_gen_call_shift                                           (11)
#define MIS_IC3_INTR_MASK_m_gen_call_mask                                            (0x00000800)
#define MIS_IC3_INTR_MASK_m_gen_call(data)                                           (0x00000800&((data)<<11))
#define MIS_IC3_INTR_MASK_m_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC3_INTR_MASK_get_m_gen_call(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC3_INTR_MASK_m_start_det_shift                                          (10)
#define MIS_IC3_INTR_MASK_m_start_det_mask                                           (0x00000400)
#define MIS_IC3_INTR_MASK_m_start_det(data)                                          (0x00000400&((data)<<10))
#define MIS_IC3_INTR_MASK_m_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC3_INTR_MASK_get_m_start_det(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC3_INTR_MASK_m_stop_det_shift                                           (9)
#define MIS_IC3_INTR_MASK_m_stop_det_mask                                            (0x00000200)
#define MIS_IC3_INTR_MASK_m_stop_det(data)                                           (0x00000200&((data)<<9))
#define MIS_IC3_INTR_MASK_m_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC3_INTR_MASK_get_m_stop_det(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC3_INTR_MASK_m_activity_shift                                           (8)
#define MIS_IC3_INTR_MASK_m_activity_mask                                            (0x00000100)
#define MIS_IC3_INTR_MASK_m_activity(data)                                           (0x00000100&((data)<<8))
#define MIS_IC3_INTR_MASK_m_activity_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC3_INTR_MASK_get_m_activity(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC3_INTR_MASK_m_rx_done_shift                                            (7)
#define MIS_IC3_INTR_MASK_m_rx_done_mask                                             (0x00000080)
#define MIS_IC3_INTR_MASK_m_rx_done(data)                                            (0x00000080&((data)<<7))
#define MIS_IC3_INTR_MASK_m_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC3_INTR_MASK_get_m_rx_done(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC3_INTR_MASK_m_tx_abrt_shift                                            (6)
#define MIS_IC3_INTR_MASK_m_tx_abrt_mask                                             (0x00000040)
#define MIS_IC3_INTR_MASK_m_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define MIS_IC3_INTR_MASK_m_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC3_INTR_MASK_get_m_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC3_INTR_MASK_m_rd_req_shift                                             (5)
#define MIS_IC3_INTR_MASK_m_rd_req_mask                                              (0x00000020)
#define MIS_IC3_INTR_MASK_m_rd_req(data)                                             (0x00000020&((data)<<5))
#define MIS_IC3_INTR_MASK_m_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC3_INTR_MASK_get_m_rd_req(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC3_INTR_MASK_m_tx_empty_shift                                           (4)
#define MIS_IC3_INTR_MASK_m_tx_empty_mask                                            (0x00000010)
#define MIS_IC3_INTR_MASK_m_tx_empty(data)                                           (0x00000010&((data)<<4))
#define MIS_IC3_INTR_MASK_m_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC3_INTR_MASK_get_m_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC3_INTR_MASK_m_tx_over_shift                                            (3)
#define MIS_IC3_INTR_MASK_m_tx_over_mask                                             (0x00000008)
#define MIS_IC3_INTR_MASK_m_tx_over(data)                                            (0x00000008&((data)<<3))
#define MIS_IC3_INTR_MASK_m_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC3_INTR_MASK_get_m_tx_over(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC3_INTR_MASK_m_rx_full_shift                                            (2)
#define MIS_IC3_INTR_MASK_m_rx_full_mask                                             (0x00000004)
#define MIS_IC3_INTR_MASK_m_rx_full(data)                                            (0x00000004&((data)<<2))
#define MIS_IC3_INTR_MASK_m_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC3_INTR_MASK_get_m_rx_full(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC3_INTR_MASK_m_rx_over_shift                                            (1)
#define MIS_IC3_INTR_MASK_m_rx_over_mask                                             (0x00000002)
#define MIS_IC3_INTR_MASK_m_rx_over(data)                                            (0x00000002&((data)<<1))
#define MIS_IC3_INTR_MASK_m_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC3_INTR_MASK_get_m_rx_over(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC3_INTR_MASK_m_rx_under_shift                                           (0)
#define MIS_IC3_INTR_MASK_m_rx_under_mask                                            (0x00000001)
#define MIS_IC3_INTR_MASK_m_rx_under(data)                                           (0x00000001&((data)<<0))
#define MIS_IC3_INTR_MASK_m_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_IC3_INTR_MASK_get_m_rx_under(data)                                       ((0x00000001&(data))>>0)


#define MIS_IC3_RAW_INTR_STAT                                                        0x1801B934
#define MIS_IC3_RAW_INTR_STAT_reg_addr                                               "0xB801B934"
#define MIS_IC3_RAW_INTR_STAT_reg                                                    0xB801B934
#define set_MIS_IC3_RAW_INTR_STAT_reg(data)   (*((volatile unsigned int*) MIS_IC3_RAW_INTR_STAT_reg)=data)
#define get_MIS_IC3_RAW_INTR_STAT_reg   (*((volatile unsigned int*) MIS_IC3_RAW_INTR_STAT_reg))
#define MIS_IC3_RAW_INTR_STAT_inst_adr                                               "0x004D"
#define MIS_IC3_RAW_INTR_STAT_inst                                                   0x004D
#define MIS_IC3_RAW_INTR_STAT_gen_call_shift                                         (11)
#define MIS_IC3_RAW_INTR_STAT_gen_call_mask                                          (0x00000800)
#define MIS_IC3_RAW_INTR_STAT_gen_call(data)                                         (0x00000800&((data)<<11))
#define MIS_IC3_RAW_INTR_STAT_gen_call_src(data)                                     ((0x00000800&(data))>>11)
#define MIS_IC3_RAW_INTR_STAT_get_gen_call(data)                                     ((0x00000800&(data))>>11)
#define MIS_IC3_RAW_INTR_STAT_start_det_shift                                        (10)
#define MIS_IC3_RAW_INTR_STAT_start_det_mask                                         (0x00000400)
#define MIS_IC3_RAW_INTR_STAT_start_det(data)                                        (0x00000400&((data)<<10))
#define MIS_IC3_RAW_INTR_STAT_start_det_src(data)                                    ((0x00000400&(data))>>10)
#define MIS_IC3_RAW_INTR_STAT_get_start_det(data)                                    ((0x00000400&(data))>>10)
#define MIS_IC3_RAW_INTR_STAT_stop_det_shift                                         (9)
#define MIS_IC3_RAW_INTR_STAT_stop_det_mask                                          (0x00000200)
#define MIS_IC3_RAW_INTR_STAT_stop_det(data)                                         (0x00000200&((data)<<9))
#define MIS_IC3_RAW_INTR_STAT_stop_det_src(data)                                     ((0x00000200&(data))>>9)
#define MIS_IC3_RAW_INTR_STAT_get_stop_det(data)                                     ((0x00000200&(data))>>9)
#define MIS_IC3_RAW_INTR_STAT_activity_shift                                         (8)
#define MIS_IC3_RAW_INTR_STAT_activity_mask                                          (0x00000100)
#define MIS_IC3_RAW_INTR_STAT_activity(data)                                         (0x00000100&((data)<<8))
#define MIS_IC3_RAW_INTR_STAT_activity_src(data)                                     ((0x00000100&(data))>>8)
#define MIS_IC3_RAW_INTR_STAT_get_activity(data)                                     ((0x00000100&(data))>>8)
#define MIS_IC3_RAW_INTR_STAT_rx_done_shift                                          (7)
#define MIS_IC3_RAW_INTR_STAT_rx_done_mask                                           (0x00000080)
#define MIS_IC3_RAW_INTR_STAT_rx_done(data)                                          (0x00000080&((data)<<7))
#define MIS_IC3_RAW_INTR_STAT_rx_done_src(data)                                      ((0x00000080&(data))>>7)
#define MIS_IC3_RAW_INTR_STAT_get_rx_done(data)                                      ((0x00000080&(data))>>7)
#define MIS_IC3_RAW_INTR_STAT_tx_abrt_shift                                          (6)
#define MIS_IC3_RAW_INTR_STAT_tx_abrt_mask                                           (0x00000040)
#define MIS_IC3_RAW_INTR_STAT_tx_abrt(data)                                          (0x00000040&((data)<<6))
#define MIS_IC3_RAW_INTR_STAT_tx_abrt_src(data)                                      ((0x00000040&(data))>>6)
#define MIS_IC3_RAW_INTR_STAT_get_tx_abrt(data)                                      ((0x00000040&(data))>>6)
#define MIS_IC3_RAW_INTR_STAT_rd_req_shift                                           (5)
#define MIS_IC3_RAW_INTR_STAT_rd_req_mask                                            (0x00000020)
#define MIS_IC3_RAW_INTR_STAT_rd_req(data)                                           (0x00000020&((data)<<5))
#define MIS_IC3_RAW_INTR_STAT_rd_req_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC3_RAW_INTR_STAT_get_rd_req(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC3_RAW_INTR_STAT_tx_empty_shift                                         (4)
#define MIS_IC3_RAW_INTR_STAT_tx_empty_mask                                          (0x00000010)
#define MIS_IC3_RAW_INTR_STAT_tx_empty(data)                                         (0x00000010&((data)<<4))
#define MIS_IC3_RAW_INTR_STAT_tx_empty_src(data)                                     ((0x00000010&(data))>>4)
#define MIS_IC3_RAW_INTR_STAT_get_tx_empty(data)                                     ((0x00000010&(data))>>4)
#define MIS_IC3_RAW_INTR_STAT_tx_over_shift                                          (3)
#define MIS_IC3_RAW_INTR_STAT_tx_over_mask                                           (0x00000008)
#define MIS_IC3_RAW_INTR_STAT_tx_over(data)                                          (0x00000008&((data)<<3))
#define MIS_IC3_RAW_INTR_STAT_tx_over_src(data)                                      ((0x00000008&(data))>>3)
#define MIS_IC3_RAW_INTR_STAT_get_tx_over(data)                                      ((0x00000008&(data))>>3)
#define MIS_IC3_RAW_INTR_STAT_rx_full_shift                                          (2)
#define MIS_IC3_RAW_INTR_STAT_rx_full_mask                                           (0x00000004)
#define MIS_IC3_RAW_INTR_STAT_rx_full(data)                                          (0x00000004&((data)<<2))
#define MIS_IC3_RAW_INTR_STAT_rx_full_src(data)                                      ((0x00000004&(data))>>2)
#define MIS_IC3_RAW_INTR_STAT_get_rx_full(data)                                      ((0x00000004&(data))>>2)
#define MIS_IC3_RAW_INTR_STAT_rx_over_shift                                          (1)
#define MIS_IC3_RAW_INTR_STAT_rx_over_mask                                           (0x00000002)
#define MIS_IC3_RAW_INTR_STAT_rx_over(data)                                          (0x00000002&((data)<<1))
#define MIS_IC3_RAW_INTR_STAT_rx_over_src(data)                                      ((0x00000002&(data))>>1)
#define MIS_IC3_RAW_INTR_STAT_get_rx_over(data)                                      ((0x00000002&(data))>>1)
#define MIS_IC3_RAW_INTR_STAT_rx_under_shift                                         (0)
#define MIS_IC3_RAW_INTR_STAT_rx_under_mask                                          (0x00000001)
#define MIS_IC3_RAW_INTR_STAT_rx_under(data)                                         (0x00000001&((data)<<0))
#define MIS_IC3_RAW_INTR_STAT_rx_under_src(data)                                     ((0x00000001&(data))>>0)
#define MIS_IC3_RAW_INTR_STAT_get_rx_under(data)                                     ((0x00000001&(data))>>0)


#define MIS_IC3_RX_TL                                                                0x1801B938
#define MIS_IC3_RX_TL_reg_addr                                                       "0xB801B938"
#define MIS_IC3_RX_TL_reg                                                            0xB801B938
#define set_MIS_IC3_RX_TL_reg(data)   (*((volatile unsigned int*) MIS_IC3_RX_TL_reg)=data)
#define get_MIS_IC3_RX_TL_reg   (*((volatile unsigned int*) MIS_IC3_RX_TL_reg))
#define MIS_IC3_RX_TL_inst_adr                                                       "0x004E"
#define MIS_IC3_RX_TL_inst                                                           0x004E
#define MIS_IC3_RX_TL_rx_tl_shift                                                    (0)
#define MIS_IC3_RX_TL_rx_tl_mask                                                     (0x000000FF)
#define MIS_IC3_RX_TL_rx_tl(data)                                                    (0x000000FF&((data)<<0))
#define MIS_IC3_RX_TL_rx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define MIS_IC3_RX_TL_get_rx_tl(data)                                                ((0x000000FF&(data))>>0)


#define MIS_IC3_TX_TL                                                                0x1801B93C
#define MIS_IC3_TX_TL_reg_addr                                                       "0xB801B93C"
#define MIS_IC3_TX_TL_reg                                                            0xB801B93C
#define set_MIS_IC3_TX_TL_reg(data)   (*((volatile unsigned int*) MIS_IC3_TX_TL_reg)=data)
#define get_MIS_IC3_TX_TL_reg   (*((volatile unsigned int*) MIS_IC3_TX_TL_reg))
#define MIS_IC3_TX_TL_inst_adr                                                       "0x004F"
#define MIS_IC3_TX_TL_inst                                                           0x004F
#define MIS_IC3_TX_TL_tx_tl_shift                                                    (0)
#define MIS_IC3_TX_TL_tx_tl_mask                                                     (0x000000FF)
#define MIS_IC3_TX_TL_tx_tl(data)                                                    (0x000000FF&((data)<<0))
#define MIS_IC3_TX_TL_tx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define MIS_IC3_TX_TL_get_tx_tl(data)                                                ((0x000000FF&(data))>>0)


#define MIS_IC3_CLR_INTR                                                             0x1801B940
#define MIS_IC3_CLR_INTR_reg_addr                                                    "0xB801B940"
#define MIS_IC3_CLR_INTR_reg                                                         0xB801B940
#define set_MIS_IC3_CLR_INTR_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_INTR_reg)=data)
#define get_MIS_IC3_CLR_INTR_reg   (*((volatile unsigned int*) MIS_IC3_CLR_INTR_reg))
#define MIS_IC3_CLR_INTR_inst_adr                                                    "0x0050"
#define MIS_IC3_CLR_INTR_inst                                                        0x0050
#define MIS_IC3_CLR_INTR_clr_intr_shift                                              (0)
#define MIS_IC3_CLR_INTR_clr_intr_mask                                               (0x00000001)
#define MIS_IC3_CLR_INTR_clr_intr(data)                                              (0x00000001&((data)<<0))
#define MIS_IC3_CLR_INTR_clr_intr_src(data)                                          ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_INTR_get_clr_intr(data)                                          ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_RX_UNDER                                                         0x1801B944
#define MIS_IC3_CLR_RX_UNDER_reg_addr                                                "0xB801B944"
#define MIS_IC3_CLR_RX_UNDER_reg                                                     0xB801B944
#define set_MIS_IC3_CLR_RX_UNDER_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_RX_UNDER_reg)=data)
#define get_MIS_IC3_CLR_RX_UNDER_reg   (*((volatile unsigned int*) MIS_IC3_CLR_RX_UNDER_reg))
#define MIS_IC3_CLR_RX_UNDER_inst_adr                                                "0x0051"
#define MIS_IC3_CLR_RX_UNDER_inst                                                    0x0051
#define MIS_IC3_CLR_RX_UNDER_clr_rx_under_shift                                      (0)
#define MIS_IC3_CLR_RX_UNDER_clr_rx_under_mask                                       (0x00000001)
#define MIS_IC3_CLR_RX_UNDER_clr_rx_under(data)                                      (0x00000001&((data)<<0))
#define MIS_IC3_CLR_RX_UNDER_clr_rx_under_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_RX_UNDER_get_clr_rx_under(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_RX_OVER                                                          0x1801B948
#define MIS_IC3_CLR_RX_OVER_reg_addr                                                 "0xB801B948"
#define MIS_IC3_CLR_RX_OVER_reg                                                      0xB801B948
#define set_MIS_IC3_CLR_RX_OVER_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_RX_OVER_reg)=data)
#define get_MIS_IC3_CLR_RX_OVER_reg   (*((volatile unsigned int*) MIS_IC3_CLR_RX_OVER_reg))
#define MIS_IC3_CLR_RX_OVER_inst_adr                                                 "0x0052"
#define MIS_IC3_CLR_RX_OVER_inst                                                     0x0052
#define MIS_IC3_CLR_RX_OVER_clr_rx_over_shift                                        (0)
#define MIS_IC3_CLR_RX_OVER_clr_rx_over_mask                                         (0x00000001)
#define MIS_IC3_CLR_RX_OVER_clr_rx_over(data)                                        (0x00000001&((data)<<0))
#define MIS_IC3_CLR_RX_OVER_clr_rx_over_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_RX_OVER_get_clr_rx_over(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_TX_OVER                                                          0x1801B94C
#define MIS_IC3_CLR_TX_OVER_reg_addr                                                 "0xB801B94C"
#define MIS_IC3_CLR_TX_OVER_reg                                                      0xB801B94C
#define set_MIS_IC3_CLR_TX_OVER_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_TX_OVER_reg)=data)
#define get_MIS_IC3_CLR_TX_OVER_reg   (*((volatile unsigned int*) MIS_IC3_CLR_TX_OVER_reg))
#define MIS_IC3_CLR_TX_OVER_inst_adr                                                 "0x0053"
#define MIS_IC3_CLR_TX_OVER_inst                                                     0x0053
#define MIS_IC3_CLR_TX_OVER_clr_tx_over_shift                                        (0)
#define MIS_IC3_CLR_TX_OVER_clr_tx_over_mask                                         (0x00000001)
#define MIS_IC3_CLR_TX_OVER_clr_tx_over(data)                                        (0x00000001&((data)<<0))
#define MIS_IC3_CLR_TX_OVER_clr_tx_over_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_TX_OVER_get_clr_tx_over(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_RD_REQ                                                           0x1801B950
#define MIS_IC3_CLR_RD_REQ_reg_addr                                                  "0xB801B950"
#define MIS_IC3_CLR_RD_REQ_reg                                                       0xB801B950
#define set_MIS_IC3_CLR_RD_REQ_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_RD_REQ_reg)=data)
#define get_MIS_IC3_CLR_RD_REQ_reg   (*((volatile unsigned int*) MIS_IC3_CLR_RD_REQ_reg))
#define MIS_IC3_CLR_RD_REQ_inst_adr                                                  "0x0054"
#define MIS_IC3_CLR_RD_REQ_inst                                                      0x0054
#define MIS_IC3_CLR_RD_REQ_clr_rd_req_shift                                          (0)
#define MIS_IC3_CLR_RD_REQ_clr_rd_req_mask                                           (0x00000001)
#define MIS_IC3_CLR_RD_REQ_clr_rd_req(data)                                          (0x00000001&((data)<<0))
#define MIS_IC3_CLR_RD_REQ_clr_rd_req_src(data)                                      ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_RD_REQ_get_clr_rd_req(data)                                      ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_TX_ABRT                                                          0x1801B954
#define MIS_IC3_CLR_TX_ABRT_reg_addr                                                 "0xB801B954"
#define MIS_IC3_CLR_TX_ABRT_reg                                                      0xB801B954
#define set_MIS_IC3_CLR_TX_ABRT_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_TX_ABRT_reg)=data)
#define get_MIS_IC3_CLR_TX_ABRT_reg   (*((volatile unsigned int*) MIS_IC3_CLR_TX_ABRT_reg))
#define MIS_IC3_CLR_TX_ABRT_inst_adr                                                 "0x0055"
#define MIS_IC3_CLR_TX_ABRT_inst                                                     0x0055
#define MIS_IC3_CLR_TX_ABRT_clr_tx_abrt_shift                                        (0)
#define MIS_IC3_CLR_TX_ABRT_clr_tx_abrt_mask                                         (0x00000001)
#define MIS_IC3_CLR_TX_ABRT_clr_tx_abrt(data)                                        (0x00000001&((data)<<0))
#define MIS_IC3_CLR_TX_ABRT_clr_tx_abrt_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_TX_ABRT_get_clr_tx_abrt(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_RX_DONE                                                          0x1801B958
#define MIS_IC3_CLR_RX_DONE_reg_addr                                                 "0xB801B958"
#define MIS_IC3_CLR_RX_DONE_reg                                                      0xB801B958
#define set_MIS_IC3_CLR_RX_DONE_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_RX_DONE_reg)=data)
#define get_MIS_IC3_CLR_RX_DONE_reg   (*((volatile unsigned int*) MIS_IC3_CLR_RX_DONE_reg))
#define MIS_IC3_CLR_RX_DONE_inst_adr                                                 "0x0056"
#define MIS_IC3_CLR_RX_DONE_inst                                                     0x0056
#define MIS_IC3_CLR_RX_DONE_clr_rx_done_shift                                        (0)
#define MIS_IC3_CLR_RX_DONE_clr_rx_done_mask                                         (0x00000001)
#define MIS_IC3_CLR_RX_DONE_clr_rx_done(data)                                        (0x00000001&((data)<<0))
#define MIS_IC3_CLR_RX_DONE_clr_rx_done_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_RX_DONE_get_clr_rx_done(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_ACTIVITY                                                         0x1801B95C
#define MIS_IC3_CLR_ACTIVITY_reg_addr                                                "0xB801B95C"
#define MIS_IC3_CLR_ACTIVITY_reg                                                     0xB801B95C
#define set_MIS_IC3_CLR_ACTIVITY_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_ACTIVITY_reg)=data)
#define get_MIS_IC3_CLR_ACTIVITY_reg   (*((volatile unsigned int*) MIS_IC3_CLR_ACTIVITY_reg))
#define MIS_IC3_CLR_ACTIVITY_inst_adr                                                "0x0057"
#define MIS_IC3_CLR_ACTIVITY_inst                                                    0x0057
#define MIS_IC3_CLR_ACTIVITY_clr_activity_shift                                      (0)
#define MIS_IC3_CLR_ACTIVITY_clr_activity_mask                                       (0x00000001)
#define MIS_IC3_CLR_ACTIVITY_clr_activity(data)                                      (0x00000001&((data)<<0))
#define MIS_IC3_CLR_ACTIVITY_clr_activity_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_ACTIVITY_get_clr_activity(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_STOP_DET                                                         0x1801B960
#define MIS_IC3_CLR_STOP_DET_reg_addr                                                "0xB801B960"
#define MIS_IC3_CLR_STOP_DET_reg                                                     0xB801B960
#define set_MIS_IC3_CLR_STOP_DET_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_STOP_DET_reg)=data)
#define get_MIS_IC3_CLR_STOP_DET_reg   (*((volatile unsigned int*) MIS_IC3_CLR_STOP_DET_reg))
#define MIS_IC3_CLR_STOP_DET_inst_adr                                                "0x0058"
#define MIS_IC3_CLR_STOP_DET_inst                                                    0x0058
#define MIS_IC3_CLR_STOP_DET_clr_stop_det_shift                                      (0)
#define MIS_IC3_CLR_STOP_DET_clr_stop_det_mask                                       (0x00000001)
#define MIS_IC3_CLR_STOP_DET_clr_stop_det(data)                                      (0x00000001&((data)<<0))
#define MIS_IC3_CLR_STOP_DET_clr_stop_det_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_STOP_DET_get_clr_stop_det(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_START_DET                                                        0x1801B964
#define MIS_IC3_CLR_START_DET_reg_addr                                               "0xB801B964"
#define MIS_IC3_CLR_START_DET_reg                                                    0xB801B964
#define set_MIS_IC3_CLR_START_DET_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_START_DET_reg)=data)
#define get_MIS_IC3_CLR_START_DET_reg   (*((volatile unsigned int*) MIS_IC3_CLR_START_DET_reg))
#define MIS_IC3_CLR_START_DET_inst_adr                                               "0x0059"
#define MIS_IC3_CLR_START_DET_inst                                                   0x0059
#define MIS_IC3_CLR_START_DET_clr_start_det_shift                                    (0)
#define MIS_IC3_CLR_START_DET_clr_start_det_mask                                     (0x00000001)
#define MIS_IC3_CLR_START_DET_clr_start_det(data)                                    (0x00000001&((data)<<0))
#define MIS_IC3_CLR_START_DET_clr_start_det_src(data)                                ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_START_DET_get_clr_start_det(data)                                ((0x00000001&(data))>>0)


#define MIS_IC3_CLR_GEN_CALL                                                         0x1801B968
#define MIS_IC3_CLR_GEN_CALL_reg_addr                                                "0xB801B968"
#define MIS_IC3_CLR_GEN_CALL_reg                                                     0xB801B968
#define set_MIS_IC3_CLR_GEN_CALL_reg(data)   (*((volatile unsigned int*) MIS_IC3_CLR_GEN_CALL_reg)=data)
#define get_MIS_IC3_CLR_GEN_CALL_reg   (*((volatile unsigned int*) MIS_IC3_CLR_GEN_CALL_reg))
#define MIS_IC3_CLR_GEN_CALL_inst_adr                                                "0x005A"
#define MIS_IC3_CLR_GEN_CALL_inst                                                    0x005A
#define MIS_IC3_CLR_GEN_CALL_clr_gen_call_shift                                      (0)
#define MIS_IC3_CLR_GEN_CALL_clr_gen_call_mask                                       (0x00000001)
#define MIS_IC3_CLR_GEN_CALL_clr_gen_call(data)                                      (0x00000001&((data)<<0))
#define MIS_IC3_CLR_GEN_CALL_clr_gen_call_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC3_CLR_GEN_CALL_get_clr_gen_call(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC3_ENABLE                                                               0x1801B96C
#define MIS_IC3_ENABLE_reg_addr                                                      "0xB801B96C"
#define MIS_IC3_ENABLE_reg                                                           0xB801B96C
#define set_MIS_IC3_ENABLE_reg(data)   (*((volatile unsigned int*) MIS_IC3_ENABLE_reg)=data)
#define get_MIS_IC3_ENABLE_reg   (*((volatile unsigned int*) MIS_IC3_ENABLE_reg))
#define MIS_IC3_ENABLE_inst_adr                                                      "0x005B"
#define MIS_IC3_ENABLE_inst                                                          0x005B
#define MIS_IC3_ENABLE_enable_shift                                                  (0)
#define MIS_IC3_ENABLE_enable_mask                                                   (0x00000001)
#define MIS_IC3_ENABLE_enable(data)                                                  (0x00000001&((data)<<0))
#define MIS_IC3_ENABLE_enable_src(data)                                              ((0x00000001&(data))>>0)
#define MIS_IC3_ENABLE_get_enable(data)                                              ((0x00000001&(data))>>0)


#define MIS_IC3_STATUS                                                               0x1801B970
#define MIS_IC3_STATUS_reg_addr                                                      "0xB801B970"
#define MIS_IC3_STATUS_reg                                                           0xB801B970
#define set_MIS_IC3_STATUS_reg(data)   (*((volatile unsigned int*) MIS_IC3_STATUS_reg)=data)
#define get_MIS_IC3_STATUS_reg   (*((volatile unsigned int*) MIS_IC3_STATUS_reg))
#define MIS_IC3_STATUS_inst_adr                                                      "0x005C"
#define MIS_IC3_STATUS_inst                                                          0x005C
#define MIS_IC3_STATUS_slv_activity_shift                                            (6)
#define MIS_IC3_STATUS_slv_activity_mask                                             (0x00000040)
#define MIS_IC3_STATUS_slv_activity(data)                                            (0x00000040&((data)<<6))
#define MIS_IC3_STATUS_slv_activity_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC3_STATUS_get_slv_activity(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC3_STATUS_mst_activity_shift                                            (5)
#define MIS_IC3_STATUS_mst_activity_mask                                             (0x00000020)
#define MIS_IC3_STATUS_mst_activity(data)                                            (0x00000020&((data)<<5))
#define MIS_IC3_STATUS_mst_activity_src(data)                                        ((0x00000020&(data))>>5)
#define MIS_IC3_STATUS_get_mst_activity(data)                                        ((0x00000020&(data))>>5)
#define MIS_IC3_STATUS_rff_shift                                                     (4)
#define MIS_IC3_STATUS_rff_mask                                                      (0x00000010)
#define MIS_IC3_STATUS_rff(data)                                                     (0x00000010&((data)<<4))
#define MIS_IC3_STATUS_rff_src(data)                                                 ((0x00000010&(data))>>4)
#define MIS_IC3_STATUS_get_rff(data)                                                 ((0x00000010&(data))>>4)
#define MIS_IC3_STATUS_rfne_shift                                                    (3)
#define MIS_IC3_STATUS_rfne_mask                                                     (0x00000008)
#define MIS_IC3_STATUS_rfne(data)                                                    (0x00000008&((data)<<3))
#define MIS_IC3_STATUS_rfne_src(data)                                                ((0x00000008&(data))>>3)
#define MIS_IC3_STATUS_get_rfne(data)                                                ((0x00000008&(data))>>3)
#define MIS_IC3_STATUS_tfe_shift                                                     (2)
#define MIS_IC3_STATUS_tfe_mask                                                      (0x00000004)
#define MIS_IC3_STATUS_tfe(data)                                                     (0x00000004&((data)<<2))
#define MIS_IC3_STATUS_tfe_src(data)                                                 ((0x00000004&(data))>>2)
#define MIS_IC3_STATUS_get_tfe(data)                                                 ((0x00000004&(data))>>2)
#define MIS_IC3_STATUS_tfnf_shift                                                    (1)
#define MIS_IC3_STATUS_tfnf_mask                                                     (0x00000002)
#define MIS_IC3_STATUS_tfnf(data)                                                    (0x00000002&((data)<<1))
#define MIS_IC3_STATUS_tfnf_src(data)                                                ((0x00000002&(data))>>1)
#define MIS_IC3_STATUS_get_tfnf(data)                                                ((0x00000002&(data))>>1)
#define MIS_IC3_STATUS_activity_shift                                                (0)
#define MIS_IC3_STATUS_activity_mask                                                 (0x00000001)
#define MIS_IC3_STATUS_activity(data)                                                (0x00000001&((data)<<0))
#define MIS_IC3_STATUS_activity_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_IC3_STATUS_get_activity(data)                                            ((0x00000001&(data))>>0)


#define MIS_IC3_TXFLR                                                                0x1801B974
#define MIS_IC3_TXFLR_reg_addr                                                       "0xB801B974"
#define MIS_IC3_TXFLR_reg                                                            0xB801B974
#define set_MIS_IC3_TXFLR_reg(data)   (*((volatile unsigned int*) MIS_IC3_TXFLR_reg)=data)
#define get_MIS_IC3_TXFLR_reg   (*((volatile unsigned int*) MIS_IC3_TXFLR_reg))
#define MIS_IC3_TXFLR_inst_adr                                                       "0x005D"
#define MIS_IC3_TXFLR_inst                                                           0x005D
#define MIS_IC3_TXFLR_txflr_shift                                                    (0)
#define MIS_IC3_TXFLR_txflr_mask                                                     (0x0000000F)
#define MIS_IC3_TXFLR_txflr(data)                                                    (0x0000000F&((data)<<0))
#define MIS_IC3_TXFLR_txflr_src(data)                                                ((0x0000000F&(data))>>0)
#define MIS_IC3_TXFLR_get_txflr(data)                                                ((0x0000000F&(data))>>0)


#define MIS_IC3_RXFLR                                                                0x1801B978
#define MIS_IC3_RXFLR_reg_addr                                                       "0xB801B978"
#define MIS_IC3_RXFLR_reg                                                            0xB801B978
#define set_MIS_IC3_RXFLR_reg(data)   (*((volatile unsigned int*) MIS_IC3_RXFLR_reg)=data)
#define get_MIS_IC3_RXFLR_reg   (*((volatile unsigned int*) MIS_IC3_RXFLR_reg))
#define MIS_IC3_RXFLR_inst_adr                                                       "0x005E"
#define MIS_IC3_RXFLR_inst                                                           0x005E
#define MIS_IC3_RXFLR_rxflr_shift                                                    (0)
#define MIS_IC3_RXFLR_rxflr_mask                                                     (0x0000000F)
#define MIS_IC3_RXFLR_rxflr(data)                                                    (0x0000000F&((data)<<0))
#define MIS_IC3_RXFLR_rxflr_src(data)                                                ((0x0000000F&(data))>>0)
#define MIS_IC3_RXFLR_get_rxflr(data)                                                ((0x0000000F&(data))>>0)


#define MIS_IC3_SDA_HOLD                                                             0x1801B97C
#define MIS_IC3_SDA_HOLD_reg_addr                                                    "0xB801B97C"
#define MIS_IC3_SDA_HOLD_reg                                                         0xB801B97C
#define set_MIS_IC3_SDA_HOLD_reg(data)   (*((volatile unsigned int*) MIS_IC3_SDA_HOLD_reg)=data)
#define get_MIS_IC3_SDA_HOLD_reg   (*((volatile unsigned int*) MIS_IC3_SDA_HOLD_reg))
#define MIS_IC3_SDA_HOLD_inst_adr                                                    "0x005F"
#define MIS_IC3_SDA_HOLD_inst                                                        0x005F
#define MIS_IC3_SDA_HOLD_sda_hold_shift                                              (0)
#define MIS_IC3_SDA_HOLD_sda_hold_mask                                               (0x0000FFFF)
#define MIS_IC3_SDA_HOLD_sda_hold(data)                                              (0x0000FFFF&((data)<<0))
#define MIS_IC3_SDA_HOLD_sda_hold_src(data)                                          ((0x0000FFFF&(data))>>0)
#define MIS_IC3_SDA_HOLD_get_sda_hold(data)                                          ((0x0000FFFF&(data))>>0)


#define MIS_IC3_TX_ABRT_SOURCE                                                       0x1801B980
#define MIS_IC3_TX_ABRT_SOURCE_reg_addr                                              "0xB801B980"
#define MIS_IC3_TX_ABRT_SOURCE_reg                                                   0xB801B980
#define set_MIS_IC3_TX_ABRT_SOURCE_reg(data)   (*((volatile unsigned int*) MIS_IC3_TX_ABRT_SOURCE_reg)=data)
#define get_MIS_IC3_TX_ABRT_SOURCE_reg   (*((volatile unsigned int*) MIS_IC3_TX_ABRT_SOURCE_reg))
#define MIS_IC3_TX_ABRT_SOURCE_inst_adr                                              "0x0060"
#define MIS_IC3_TX_ABRT_SOURCE_inst                                                  0x0060
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slvrd_intx_shift                                 (15)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slvrd_intx_mask                                  (0x00008000)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slvrd_intx(data)                                 (0x00008000&((data)<<15))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slvrd_intx_src(data)                             ((0x00008000&(data))>>15)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_slvrd_intx(data)                             ((0x00008000&(data))>>15)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slv_arblost_shift                                (14)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slv_arblost_mask                                 (0x00004000)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slv_arblost(data)                                (0x00004000&((data)<<14))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slv_arblost_src(data)                            ((0x00004000&(data))>>14)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_slv_arblost(data)                            ((0x00004000&(data))>>14)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slvflush_txfifo_shift                            (13)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slvflush_txfifo_mask                             (0x00002000)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slvflush_txfifo(data)                            (0x00002000&((data)<<13))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_slvflush_txfifo_src(data)                        ((0x00002000&(data))>>13)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_slvflush_txfifo(data)                        ((0x00002000&(data))>>13)
#define MIS_IC3_TX_ABRT_SOURCE_arb_lost_shift                                        (12)
#define MIS_IC3_TX_ABRT_SOURCE_arb_lost_mask                                         (0x00001000)
#define MIS_IC3_TX_ABRT_SOURCE_arb_lost(data)                                        (0x00001000&((data)<<12))
#define MIS_IC3_TX_ABRT_SOURCE_arb_lost_src(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC3_TX_ABRT_SOURCE_get_arb_lost(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC3_TX_ABRT_SOURCE_arb_master_dis_shift                                  (11)
#define MIS_IC3_TX_ABRT_SOURCE_arb_master_dis_mask                                   (0x00000800)
#define MIS_IC3_TX_ABRT_SOURCE_arb_master_dis(data)                                  (0x00000800&((data)<<11))
#define MIS_IC3_TX_ABRT_SOURCE_arb_master_dis_src(data)                              ((0x00000800&(data))>>11)
#define MIS_IC3_TX_ABRT_SOURCE_get_arb_master_dis(data)                              ((0x00000800&(data))>>11)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_shift                             (10)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_mask                              (0x00000400)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10b_rd_norstrt(data)                             (0x00000400&((data)<<10))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_src(data)                         ((0x00000400&(data))>>10)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_10b_rd_norstrt(data)                         ((0x00000400&(data))>>10)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_sbyte_norstrt_shift                              (9)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_sbyte_norstrt_mask                               (0x00000200)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_sbyte_norstrt(data)                              (0x00000200&((data)<<9))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_sbyte_norstrt_src(data)                          ((0x00000200&(data))>>9)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_sbyte_norstrt(data)                          ((0x00000200&(data))>>9)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_hs_norstrt_shift                                 (8)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_hs_norstrt_mask                                  (0x00000100)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_hs_norstrt(data)                                 (0x00000100&((data)<<8))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_hs_norstrt_src(data)                             ((0x00000100&(data))>>8)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_hs_norstrt(data)                             ((0x00000100&(data))>>8)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_sbyte_ackdet_shift                               (7)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_sbyte_ackdet_mask                                (0x00000080)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_sbyte_ackdet(data)                               (0x00000080&((data)<<7))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_sbyte_ackdet_src(data)                           ((0x00000080&(data))>>7)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_sbyte_ackdet(data)                           ((0x00000080&(data))>>7)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_hs_ackdet_shift                                  (6)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_hs_ackdet_mask                                   (0x00000040)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_hs_ackdet(data)                                  (0x00000040&((data)<<6))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_hs_ackdet_src(data)                              ((0x00000040&(data))>>6)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_hs_ackdet(data)                              ((0x00000040&(data))>>6)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_gcall_read_shift                                 (5)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_gcall_read_mask                                  (0x00000020)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_gcall_read(data)                                 (0x00000020&((data)<<5))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_gcall_read_src(data)                             ((0x00000020&(data))>>5)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_gcall_read(data)                             ((0x00000020&(data))>>5)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_gcall_noack_shift                                (4)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_gcall_noack_mask                                 (0x00000010)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_gcall_noack(data)                                (0x00000010&((data)<<4))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_gcall_noack_src(data)                            ((0x00000010&(data))>>4)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_gcall_noack(data)                            ((0x00000010&(data))>>4)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_txdata_noack_shift                               (3)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_txdata_noack_mask                                (0x00000008)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_txdata_noack(data)                               (0x00000008&((data)<<3))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_txdata_noack_src(data)                           ((0x00000008&(data))>>3)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_txdata_noack(data)                           ((0x00000008&(data))>>3)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10addr2_noack_shift                              (2)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10addr2_noack_mask                               (0x00000004)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10addr2_noack(data)                              (0x00000004&((data)<<2))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10addr2_noack_src(data)                          ((0x00000004&(data))>>2)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_10addr2_noack(data)                          ((0x00000004&(data))>>2)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10addr1_noack_shift                              (1)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10addr1_noack_mask                               (0x00000002)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10addr1_noack(data)                              (0x00000002&((data)<<1))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_10addr1_noack_src(data)                          ((0x00000002&(data))>>1)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_10addr1_noack(data)                          ((0x00000002&(data))>>1)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_7b_addr_noack_shift                              (0)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_7b_addr_noack_mask                               (0x00000001)
#define MIS_IC3_TX_ABRT_SOURCE_abrt_7b_addr_noack(data)                              (0x00000001&((data)<<0))
#define MIS_IC3_TX_ABRT_SOURCE_abrt_7b_addr_noack_src(data)                          ((0x00000001&(data))>>0)
#define MIS_IC3_TX_ABRT_SOURCE_get_abrt_7b_addr_noack(data)                          ((0x00000001&(data))>>0)


#define MIS_IC3_SLV_DATA_NACK_ONLY                                                   0x1801B984
#define MIS_IC3_SLV_DATA_NACK_ONLY_reg_addr                                          "0xB801B984"
#define MIS_IC3_SLV_DATA_NACK_ONLY_reg                                               0xB801B984
#define set_MIS_IC3_SLV_DATA_NACK_ONLY_reg(data)   (*((volatile unsigned int*) MIS_IC3_SLV_DATA_NACK_ONLY_reg)=data)
#define get_MIS_IC3_SLV_DATA_NACK_ONLY_reg   (*((volatile unsigned int*) MIS_IC3_SLV_DATA_NACK_ONLY_reg))
#define MIS_IC3_SLV_DATA_NACK_ONLY_inst_adr                                          "0x0061"
#define MIS_IC3_SLV_DATA_NACK_ONLY_inst                                              0x0061
#define MIS_IC3_SLV_DATA_NACK_ONLY_nack_shift                                        (0)
#define MIS_IC3_SLV_DATA_NACK_ONLY_nack_mask                                         (0x00000001)
#define MIS_IC3_SLV_DATA_NACK_ONLY_nack(data)                                        (0x00000001&((data)<<0))
#define MIS_IC3_SLV_DATA_NACK_ONLY_nack_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC3_SLV_DATA_NACK_ONLY_get_nack(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC3_DMA_CR                                                               0x1801B988
#define MIS_IC3_DMA_CR_reg_addr                                                      "0xB801B988"
#define MIS_IC3_DMA_CR_reg                                                           0xB801B988
#define set_MIS_IC3_DMA_CR_reg(data)   (*((volatile unsigned int*) MIS_IC3_DMA_CR_reg)=data)
#define get_MIS_IC3_DMA_CR_reg   (*((volatile unsigned int*) MIS_IC3_DMA_CR_reg))
#define MIS_IC3_DMA_CR_inst_adr                                                      "0x0062"
#define MIS_IC3_DMA_CR_inst                                                          0x0062
#define MIS_IC3_DMA_CR_tdmae_shift                                                   (1)
#define MIS_IC3_DMA_CR_tdmae_mask                                                    (0x00000002)
#define MIS_IC3_DMA_CR_tdmae(data)                                                   (0x00000002&((data)<<1))
#define MIS_IC3_DMA_CR_tdmae_src(data)                                               ((0x00000002&(data))>>1)
#define MIS_IC3_DMA_CR_get_tdmae(data)                                               ((0x00000002&(data))>>1)
#define MIS_IC3_DMA_CR_rdmae_shift                                                   (0)
#define MIS_IC3_DMA_CR_rdmae_mask                                                    (0x00000001)
#define MIS_IC3_DMA_CR_rdmae(data)                                                   (0x00000001&((data)<<0))
#define MIS_IC3_DMA_CR_rdmae_src(data)                                               ((0x00000001&(data))>>0)
#define MIS_IC3_DMA_CR_get_rdmae(data)                                               ((0x00000001&(data))>>0)


#define MIS_IC3_DMA_TDLR                                                             0x1801B98C
#define MIS_IC3_DMA_TDLR_reg_addr                                                    "0xB801B98C"
#define MIS_IC3_DMA_TDLR_reg                                                         0xB801B98C
#define set_MIS_IC3_DMA_TDLR_reg(data)   (*((volatile unsigned int*) MIS_IC3_DMA_TDLR_reg)=data)
#define get_MIS_IC3_DMA_TDLR_reg   (*((volatile unsigned int*) MIS_IC3_DMA_TDLR_reg))
#define MIS_IC3_DMA_TDLR_inst_adr                                                    "0x0063"
#define MIS_IC3_DMA_TDLR_inst                                                        0x0063
#define MIS_IC3_DMA_TDLR_dmatdl_shift                                                (0)
#define MIS_IC3_DMA_TDLR_dmatdl_mask                                                 (0x00000007)
#define MIS_IC3_DMA_TDLR_dmatdl(data)                                                (0x00000007&((data)<<0))
#define MIS_IC3_DMA_TDLR_dmatdl_src(data)                                            ((0x00000007&(data))>>0)
#define MIS_IC3_DMA_TDLR_get_dmatdl(data)                                            ((0x00000007&(data))>>0)


#define MIS_IC3_DMA_RDLR                                                             0x1801B990
#define MIS_IC3_DMA_RDLR_reg_addr                                                    "0xB801B990"
#define MIS_IC3_DMA_RDLR_reg                                                         0xB801B990
#define set_MIS_IC3_DMA_RDLR_reg(data)   (*((volatile unsigned int*) MIS_IC3_DMA_RDLR_reg)=data)
#define get_MIS_IC3_DMA_RDLR_reg   (*((volatile unsigned int*) MIS_IC3_DMA_RDLR_reg))
#define MIS_IC3_DMA_RDLR_inst_adr                                                    "0x0064"
#define MIS_IC3_DMA_RDLR_inst                                                        0x0064
#define MIS_IC3_DMA_RDLR_dmardl_shift                                                (0)
#define MIS_IC3_DMA_RDLR_dmardl_mask                                                 (0x0000000F)
#define MIS_IC3_DMA_RDLR_dmardl(data)                                                (0x0000000F&((data)<<0))
#define MIS_IC3_DMA_RDLR_dmardl_src(data)                                            ((0x0000000F&(data))>>0)
#define MIS_IC3_DMA_RDLR_get_dmardl(data)                                            ((0x0000000F&(data))>>0)


#define MIS_IC3_SDA_SETUP                                                            0x1801B994
#define MIS_IC3_SDA_SETUP_reg_addr                                                   "0xB801B994"
#define MIS_IC3_SDA_SETUP_reg                                                        0xB801B994
#define set_MIS_IC3_SDA_SETUP_reg(data)   (*((volatile unsigned int*) MIS_IC3_SDA_SETUP_reg)=data)
#define get_MIS_IC3_SDA_SETUP_reg   (*((volatile unsigned int*) MIS_IC3_SDA_SETUP_reg))
#define MIS_IC3_SDA_SETUP_inst_adr                                                   "0x0065"
#define MIS_IC3_SDA_SETUP_inst                                                       0x0065
#define MIS_IC3_SDA_SETUP_sda_setup_shift                                            (0)
#define MIS_IC3_SDA_SETUP_sda_setup_mask                                             (0x000000FF)
#define MIS_IC3_SDA_SETUP_sda_setup(data)                                            (0x000000FF&((data)<<0))
#define MIS_IC3_SDA_SETUP_sda_setup_src(data)                                        ((0x000000FF&(data))>>0)
#define MIS_IC3_SDA_SETUP_get_sda_setup(data)                                        ((0x000000FF&(data))>>0)


#define MIS_IC3_ACK_GENERAL_CALL                                                     0x1801B998
#define MIS_IC3_ACK_GENERAL_CALL_reg_addr                                            "0xB801B998"
#define MIS_IC3_ACK_GENERAL_CALL_reg                                                 0xB801B998
#define set_MIS_IC3_ACK_GENERAL_CALL_reg(data)   (*((volatile unsigned int*) MIS_IC3_ACK_GENERAL_CALL_reg)=data)
#define get_MIS_IC3_ACK_GENERAL_CALL_reg   (*((volatile unsigned int*) MIS_IC3_ACK_GENERAL_CALL_reg))
#define MIS_IC3_ACK_GENERAL_CALL_inst_adr                                            "0x0066"
#define MIS_IC3_ACK_GENERAL_CALL_inst                                                0x0066
#define MIS_IC3_ACK_GENERAL_CALL_ack_gen_call_shift                                  (0)
#define MIS_IC3_ACK_GENERAL_CALL_ack_gen_call_mask                                   (0x00000001)
#define MIS_IC3_ACK_GENERAL_CALL_ack_gen_call(data)                                  (0x00000001&((data)<<0))
#define MIS_IC3_ACK_GENERAL_CALL_ack_gen_call_src(data)                              ((0x00000001&(data))>>0)
#define MIS_IC3_ACK_GENERAL_CALL_get_ack_gen_call(data)                              ((0x00000001&(data))>>0)


#define MIS_IC3_ENABLE_STATUS                                                        0x1801B99C
#define MIS_IC3_ENABLE_STATUS_reg_addr                                               "0xB801B99C"
#define MIS_IC3_ENABLE_STATUS_reg                                                    0xB801B99C
#define set_MIS_IC3_ENABLE_STATUS_reg(data)   (*((volatile unsigned int*) MIS_IC3_ENABLE_STATUS_reg)=data)
#define get_MIS_IC3_ENABLE_STATUS_reg   (*((volatile unsigned int*) MIS_IC3_ENABLE_STATUS_reg))
#define MIS_IC3_ENABLE_STATUS_inst_adr                                               "0x0067"
#define MIS_IC3_ENABLE_STATUS_inst                                                   0x0067
#define MIS_IC3_ENABLE_STATUS_slv_rx_data_lost_shift                                 (2)
#define MIS_IC3_ENABLE_STATUS_slv_rx_data_lost_mask                                  (0x00000004)
#define MIS_IC3_ENABLE_STATUS_slv_rx_data_lost(data)                                 (0x00000004&((data)<<2))
#define MIS_IC3_ENABLE_STATUS_slv_rx_data_lost_src(data)                             ((0x00000004&(data))>>2)
#define MIS_IC3_ENABLE_STATUS_get_slv_rx_data_lost(data)                             ((0x00000004&(data))>>2)
#define MIS_IC3_ENABLE_STATUS_slv_disabled_whi_shift                                 (1)
#define MIS_IC3_ENABLE_STATUS_slv_disabled_whi_mask                                  (0x00000002)
#define MIS_IC3_ENABLE_STATUS_slv_disabled_whi(data)                                 (0x00000002&((data)<<1))
#define MIS_IC3_ENABLE_STATUS_slv_disabled_whi_src(data)                             ((0x00000002&(data))>>1)
#define MIS_IC3_ENABLE_STATUS_get_slv_disabled_whi(data)                             ((0x00000002&(data))>>1)
#define MIS_IC3_ENABLE_STATUS_ic_en_shift                                            (0)
#define MIS_IC3_ENABLE_STATUS_ic_en_mask                                             (0x00000001)
#define MIS_IC3_ENABLE_STATUS_ic_en(data)                                            (0x00000001&((data)<<0))
#define MIS_IC3_ENABLE_STATUS_ic_en_src(data)                                        ((0x00000001&(data))>>0)
#define MIS_IC3_ENABLE_STATUS_get_ic_en(data)                                        ((0x00000001&(data))>>0)


#define MIS_IC3_COMP_PARAM_1                                                         0x1801B9F4
#define MIS_IC3_COMP_PARAM_1_reg_addr                                                "0xB801B9F4"
#define MIS_IC3_COMP_PARAM_1_reg                                                     0xB801B9F4
#define set_MIS_IC3_COMP_PARAM_1_reg(data)   (*((volatile unsigned int*) MIS_IC3_COMP_PARAM_1_reg)=data)
#define get_MIS_IC3_COMP_PARAM_1_reg   (*((volatile unsigned int*) MIS_IC3_COMP_PARAM_1_reg))
#define MIS_IC3_COMP_PARAM_1_inst_adr                                                "0x007D"
#define MIS_IC3_COMP_PARAM_1_inst                                                    0x007D
#define MIS_IC3_COMP_PARAM_1_tx_buffer_depth_shift                                   (16)
#define MIS_IC3_COMP_PARAM_1_tx_buffer_depth_mask                                    (0x00FF0000)
#define MIS_IC3_COMP_PARAM_1_tx_buffer_depth(data)                                   (0x00FF0000&((data)<<16))
#define MIS_IC3_COMP_PARAM_1_tx_buffer_depth_src(data)                               ((0x00FF0000&(data))>>16)
#define MIS_IC3_COMP_PARAM_1_get_tx_buffer_depth(data)                               ((0x00FF0000&(data))>>16)
#define MIS_IC3_COMP_PARAM_1_rx_buffer_depth_shift                                   (8)
#define MIS_IC3_COMP_PARAM_1_rx_buffer_depth_mask                                    (0x0000FF00)
#define MIS_IC3_COMP_PARAM_1_rx_buffer_depth(data)                                   (0x0000FF00&((data)<<8))
#define MIS_IC3_COMP_PARAM_1_rx_buffer_depth_src(data)                               ((0x0000FF00&(data))>>8)
#define MIS_IC3_COMP_PARAM_1_get_rx_buffer_depth(data)                               ((0x0000FF00&(data))>>8)
#define MIS_IC3_COMP_PARAM_1_add_encoded_params_shift                                (7)
#define MIS_IC3_COMP_PARAM_1_add_encoded_params_mask                                 (0x00000080)
#define MIS_IC3_COMP_PARAM_1_add_encoded_params(data)                                (0x00000080&((data)<<7))
#define MIS_IC3_COMP_PARAM_1_add_encoded_params_src(data)                            ((0x00000080&(data))>>7)
#define MIS_IC3_COMP_PARAM_1_get_add_encoded_params(data)                            ((0x00000080&(data))>>7)
#define MIS_IC3_COMP_PARAM_1_has_dma_shift                                           (6)
#define MIS_IC3_COMP_PARAM_1_has_dma_mask                                            (0x00000040)
#define MIS_IC3_COMP_PARAM_1_has_dma(data)                                           (0x00000040&((data)<<6))
#define MIS_IC3_COMP_PARAM_1_has_dma_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC3_COMP_PARAM_1_get_has_dma(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC3_COMP_PARAM_1_intr_io_shift                                           (5)
#define MIS_IC3_COMP_PARAM_1_intr_io_mask                                            (0x00000020)
#define MIS_IC3_COMP_PARAM_1_intr_io(data)                                           (0x00000020&((data)<<5))
#define MIS_IC3_COMP_PARAM_1_intr_io_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC3_COMP_PARAM_1_get_intr_io(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC3_COMP_PARAM_1_hc_count_values_shift                                   (4)
#define MIS_IC3_COMP_PARAM_1_hc_count_values_mask                                    (0x00000010)
#define MIS_IC3_COMP_PARAM_1_hc_count_values(data)                                   (0x00000010&((data)<<4))
#define MIS_IC3_COMP_PARAM_1_hc_count_values_src(data)                               ((0x00000010&(data))>>4)
#define MIS_IC3_COMP_PARAM_1_get_hc_count_values(data)                               ((0x00000010&(data))>>4)
#define MIS_IC3_COMP_PARAM_1_max_speed_mode_shift                                    (2)
#define MIS_IC3_COMP_PARAM_1_max_speed_mode_mask                                     (0x0000000C)
#define MIS_IC3_COMP_PARAM_1_max_speed_mode(data)                                    (0x0000000C&((data)<<2))
#define MIS_IC3_COMP_PARAM_1_max_speed_mode_src(data)                                ((0x0000000C&(data))>>2)
#define MIS_IC3_COMP_PARAM_1_get_max_speed_mode(data)                                ((0x0000000C&(data))>>2)
#define MIS_IC3_COMP_PARAM_1_apb_data_width_shift                                    (0)
#define MIS_IC3_COMP_PARAM_1_apb_data_width_mask                                     (0x00000003)
#define MIS_IC3_COMP_PARAM_1_apb_data_width(data)                                    (0x00000003&((data)<<0))
#define MIS_IC3_COMP_PARAM_1_apb_data_width_src(data)                                ((0x00000003&(data))>>0)
#define MIS_IC3_COMP_PARAM_1_get_apb_data_width(data)                                ((0x00000003&(data))>>0)


#define MIS_IC3_COMP_VERSION                                                         0x1801B9F8
#define MIS_IC3_COMP_VERSION_reg_addr                                                "0xB801B9F8"
#define MIS_IC3_COMP_VERSION_reg                                                     0xB801B9F8
#define set_MIS_IC3_COMP_VERSION_reg(data)   (*((volatile unsigned int*) MIS_IC3_COMP_VERSION_reg)=data)
#define get_MIS_IC3_COMP_VERSION_reg   (*((volatile unsigned int*) MIS_IC3_COMP_VERSION_reg))
#define MIS_IC3_COMP_VERSION_inst_adr                                                "0x007E"
#define MIS_IC3_COMP_VERSION_inst                                                    0x007E
#define MIS_IC3_COMP_VERSION_ic_comp_version_shift                                   (0)
#define MIS_IC3_COMP_VERSION_ic_comp_version_mask                                    (0xFFFFFFFF)
#define MIS_IC3_COMP_VERSION_ic_comp_version(data)                                   (0xFFFFFFFF&((data)<<0))
#define MIS_IC3_COMP_VERSION_ic_comp_version_src(data)                               ((0xFFFFFFFF&(data))>>0)
#define MIS_IC3_COMP_VERSION_get_ic_comp_version(data)                               ((0xFFFFFFFF&(data))>>0)


#define MIS_IC3_COMP_TYPE                                                            0x1801B9FC
#define MIS_IC3_COMP_TYPE_reg_addr                                                   "0xB801B9FC"
#define MIS_IC3_COMP_TYPE_reg                                                        0xB801B9FC
#define set_MIS_IC3_COMP_TYPE_reg(data)   (*((volatile unsigned int*) MIS_IC3_COMP_TYPE_reg)=data)
#define get_MIS_IC3_COMP_TYPE_reg   (*((volatile unsigned int*) MIS_IC3_COMP_TYPE_reg))
#define MIS_IC3_COMP_TYPE_inst_adr                                                   "0x007F"
#define MIS_IC3_COMP_TYPE_inst                                                       0x007F
#define MIS_IC3_COMP_TYPE_ic_comp_type_shift                                         (0)
#define MIS_IC3_COMP_TYPE_ic_comp_type_mask                                          (0xFFFFFFFF)
#define MIS_IC3_COMP_TYPE_ic_comp_type(data)                                         (0xFFFFFFFF&((data)<<0))
#define MIS_IC3_COMP_TYPE_ic_comp_type_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define MIS_IC3_COMP_TYPE_get_ic_comp_type(data)                                     ((0xFFFFFFFF&(data))>>0)


#define MIS_IC4_CON                                                                  0x1801BA00
#define MIS_IC4_CON_reg_addr                                                         "0xB801BA00"
#define MIS_IC4_CON_reg                                                              0xB801BA00
#define set_MIS_IC4_CON_reg(data)   (*((volatile unsigned int*) MIS_IC4_CON_reg)=data)
#define get_MIS_IC4_CON_reg   (*((volatile unsigned int*) MIS_IC4_CON_reg))
#define MIS_IC4_CON_inst_adr                                                         "0x0080"
#define MIS_IC4_CON_inst                                                             0x0080
#define MIS_IC4_CON_ic_slave_disable_shift                                           (6)
#define MIS_IC4_CON_ic_slave_disable_mask                                            (0x00000040)
#define MIS_IC4_CON_ic_slave_disable(data)                                           (0x00000040&((data)<<6))
#define MIS_IC4_CON_ic_slave_disable_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC4_CON_get_ic_slave_disable(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC4_CON_ic_restart_en_shift                                              (5)
#define MIS_IC4_CON_ic_restart_en_mask                                               (0x00000020)
#define MIS_IC4_CON_ic_restart_en(data)                                              (0x00000020&((data)<<5))
#define MIS_IC4_CON_ic_restart_en_src(data)                                          ((0x00000020&(data))>>5)
#define MIS_IC4_CON_get_ic_restart_en(data)                                          ((0x00000020&(data))>>5)
#define MIS_IC4_CON_ic_10bitaddr_master_shift                                        (4)
#define MIS_IC4_CON_ic_10bitaddr_master_mask                                         (0x00000010)
#define MIS_IC4_CON_ic_10bitaddr_master(data)                                        (0x00000010&((data)<<4))
#define MIS_IC4_CON_ic_10bitaddr_master_src(data)                                    ((0x00000010&(data))>>4)
#define MIS_IC4_CON_get_ic_10bitaddr_master(data)                                    ((0x00000010&(data))>>4)
#define MIS_IC4_CON_ic_10bitaddr_slave_shift                                         (3)
#define MIS_IC4_CON_ic_10bitaddr_slave_mask                                          (0x00000008)
#define MIS_IC4_CON_ic_10bitaddr_slave(data)                                         (0x00000008&((data)<<3))
#define MIS_IC4_CON_ic_10bitaddr_slave_src(data)                                     ((0x00000008&(data))>>3)
#define MIS_IC4_CON_get_ic_10bitaddr_slave(data)                                     ((0x00000008&(data))>>3)
#define MIS_IC4_CON_speed_shift                                                      (1)
#define MIS_IC4_CON_speed_mask                                                       (0x00000006)
#define MIS_IC4_CON_speed(data)                                                      (0x00000006&((data)<<1))
#define MIS_IC4_CON_speed_src(data)                                                  ((0x00000006&(data))>>1)
#define MIS_IC4_CON_get_speed(data)                                                  ((0x00000006&(data))>>1)
#define MIS_IC4_CON_master_mode_shift                                                (0)
#define MIS_IC4_CON_master_mode_mask                                                 (0x00000001)
#define MIS_IC4_CON_master_mode(data)                                                (0x00000001&((data)<<0))
#define MIS_IC4_CON_master_mode_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_IC4_CON_get_master_mode(data)                                            ((0x00000001&(data))>>0)


#define MIS_IC4_TAR                                                                  0x1801BA04
#define MIS_IC4_TAR_reg_addr                                                         "0xB801BA04"
#define MIS_IC4_TAR_reg                                                              0xB801BA04
#define set_MIS_IC4_TAR_reg(data)   (*((volatile unsigned int*) MIS_IC4_TAR_reg)=data)
#define get_MIS_IC4_TAR_reg   (*((volatile unsigned int*) MIS_IC4_TAR_reg))
#define MIS_IC4_TAR_inst_adr                                                         "0x0081"
#define MIS_IC4_TAR_inst                                                             0x0081
#define MIS_IC4_TAR_ic_10bitaddr_master_shift                                        (12)
#define MIS_IC4_TAR_ic_10bitaddr_master_mask                                         (0x00001000)
#define MIS_IC4_TAR_ic_10bitaddr_master(data)                                        (0x00001000&((data)<<12))
#define MIS_IC4_TAR_ic_10bitaddr_master_src(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC4_TAR_get_ic_10bitaddr_master(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC4_TAR_special_shift                                                    (11)
#define MIS_IC4_TAR_special_mask                                                     (0x00000800)
#define MIS_IC4_TAR_special(data)                                                    (0x00000800&((data)<<11))
#define MIS_IC4_TAR_special_src(data)                                                ((0x00000800&(data))>>11)
#define MIS_IC4_TAR_get_special(data)                                                ((0x00000800&(data))>>11)
#define MIS_IC4_TAR_gc_or_start_shift                                                (10)
#define MIS_IC4_TAR_gc_or_start_mask                                                 (0x00000400)
#define MIS_IC4_TAR_gc_or_start(data)                                                (0x00000400&((data)<<10))
#define MIS_IC4_TAR_gc_or_start_src(data)                                            ((0x00000400&(data))>>10)
#define MIS_IC4_TAR_get_gc_or_start(data)                                            ((0x00000400&(data))>>10)
#define MIS_IC4_TAR_ic_tar_shift                                                     (0)
#define MIS_IC4_TAR_ic_tar_mask                                                      (0x000003FF)
#define MIS_IC4_TAR_ic_tar(data)                                                     (0x000003FF&((data)<<0))
#define MIS_IC4_TAR_ic_tar_src(data)                                                 ((0x000003FF&(data))>>0)
#define MIS_IC4_TAR_get_ic_tar(data)                                                 ((0x000003FF&(data))>>0)


#define MIS_IC4_SAR                                                                  0x1801BA08
#define MIS_IC4_SAR_reg_addr                                                         "0xB801BA08"
#define MIS_IC4_SAR_reg                                                              0xB801BA08
#define set_MIS_IC4_SAR_reg(data)   (*((volatile unsigned int*) MIS_IC4_SAR_reg)=data)
#define get_MIS_IC4_SAR_reg   (*((volatile unsigned int*) MIS_IC4_SAR_reg))
#define MIS_IC4_SAR_inst_adr                                                         "0x0082"
#define MIS_IC4_SAR_inst                                                             0x0082
#define MIS_IC4_SAR_ic_sar_shift                                                     (0)
#define MIS_IC4_SAR_ic_sar_mask                                                      (0x000003FF)
#define MIS_IC4_SAR_ic_sar(data)                                                     (0x000003FF&((data)<<0))
#define MIS_IC4_SAR_ic_sar_src(data)                                                 ((0x000003FF&(data))>>0)
#define MIS_IC4_SAR_get_ic_sar(data)                                                 ((0x000003FF&(data))>>0)


#define MIS_IC4_HS_MADDR                                                             0x1801BA0C
#define MIS_IC4_HS_MADDR_reg_addr                                                    "0xB801BA0C"
#define MIS_IC4_HS_MADDR_reg                                                         0xB801BA0C
#define set_MIS_IC4_HS_MADDR_reg(data)   (*((volatile unsigned int*) MIS_IC4_HS_MADDR_reg)=data)
#define get_MIS_IC4_HS_MADDR_reg   (*((volatile unsigned int*) MIS_IC4_HS_MADDR_reg))
#define MIS_IC4_HS_MADDR_inst_adr                                                    "0x0083"
#define MIS_IC4_HS_MADDR_inst                                                        0x0083
#define MIS_IC4_HS_MADDR_ic_hs_mar_shift                                             (0)
#define MIS_IC4_HS_MADDR_ic_hs_mar_mask                                              (0x00000007)
#define MIS_IC4_HS_MADDR_ic_hs_mar(data)                                             (0x00000007&((data)<<0))
#define MIS_IC4_HS_MADDR_ic_hs_mar_src(data)                                         ((0x00000007&(data))>>0)
#define MIS_IC4_HS_MADDR_get_ic_hs_mar(data)                                         ((0x00000007&(data))>>0)


#define MIS_IC4_DATA_CMD                                                             0x1801BA10
#define MIS_IC4_DATA_CMD_reg_addr                                                    "0xB801BA10"
#define MIS_IC4_DATA_CMD_reg                                                         0xB801BA10
#define set_MIS_IC4_DATA_CMD_reg(data)   (*((volatile unsigned int*) MIS_IC4_DATA_CMD_reg)=data)
#define get_MIS_IC4_DATA_CMD_reg   (*((volatile unsigned int*) MIS_IC4_DATA_CMD_reg))
#define MIS_IC4_DATA_CMD_inst_adr                                                    "0x0084"
#define MIS_IC4_DATA_CMD_inst                                                        0x0084
#define MIS_IC4_DATA_CMD_restart_shift                                               (10)
#define MIS_IC4_DATA_CMD_restart_mask                                                (0x00000400)
#define MIS_IC4_DATA_CMD_restart(data)                                               (0x00000400&((data)<<10))
#define MIS_IC4_DATA_CMD_restart_src(data)                                           ((0x00000400&(data))>>10)
#define MIS_IC4_DATA_CMD_get_restart(data)                                           ((0x00000400&(data))>>10)
#define MIS_IC4_DATA_CMD_stop_shift                                                  (9)
#define MIS_IC4_DATA_CMD_stop_mask                                                   (0x00000200)
#define MIS_IC4_DATA_CMD_stop(data)                                                  (0x00000200&((data)<<9))
#define MIS_IC4_DATA_CMD_stop_src(data)                                              ((0x00000200&(data))>>9)
#define MIS_IC4_DATA_CMD_get_stop(data)                                              ((0x00000200&(data))>>9)
#define MIS_IC4_DATA_CMD_cmd_shift                                                   (8)
#define MIS_IC4_DATA_CMD_cmd_mask                                                    (0x00000100)
#define MIS_IC4_DATA_CMD_cmd(data)                                                   (0x00000100&((data)<<8))
#define MIS_IC4_DATA_CMD_cmd_src(data)                                               ((0x00000100&(data))>>8)
#define MIS_IC4_DATA_CMD_get_cmd(data)                                               ((0x00000100&(data))>>8)
#define MIS_IC4_DATA_CMD_dat_shift                                                   (0)
#define MIS_IC4_DATA_CMD_dat_mask                                                    (0x000000FF)
#define MIS_IC4_DATA_CMD_dat(data)                                                   (0x000000FF&((data)<<0))
#define MIS_IC4_DATA_CMD_dat_src(data)                                               ((0x000000FF&(data))>>0)
#define MIS_IC4_DATA_CMD_get_dat(data)                                               ((0x000000FF&(data))>>0)


#define MIS_IC4_SS_SCL_HCNT                                                          0x1801BA14
#define MIS_IC4_SS_SCL_HCNT_reg_addr                                                 "0xB801BA14"
#define MIS_IC4_SS_SCL_HCNT_reg                                                      0xB801BA14
#define set_MIS_IC4_SS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) MIS_IC4_SS_SCL_HCNT_reg)=data)
#define get_MIS_IC4_SS_SCL_HCNT_reg   (*((volatile unsigned int*) MIS_IC4_SS_SCL_HCNT_reg))
#define MIS_IC4_SS_SCL_HCNT_inst_adr                                                 "0x0085"
#define MIS_IC4_SS_SCL_HCNT_inst                                                     0x0085
#define MIS_IC4_SS_SCL_HCNT_ic_ss_scl_hcnt_shift                                     (0)
#define MIS_IC4_SS_SCL_HCNT_ic_ss_scl_hcnt_mask                                      (0x0000FFFF)
#define MIS_IC4_SS_SCL_HCNT_ic_ss_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC4_SS_SCL_HCNT_ic_ss_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC4_SS_SCL_HCNT_get_ic_ss_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC4_SS_SCL_LCNT                                                          0x1801BA18
#define MIS_IC4_SS_SCL_LCNT_reg_addr                                                 "0xB801BA18"
#define MIS_IC4_SS_SCL_LCNT_reg                                                      0xB801BA18
#define set_MIS_IC4_SS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) MIS_IC4_SS_SCL_LCNT_reg)=data)
#define get_MIS_IC4_SS_SCL_LCNT_reg   (*((volatile unsigned int*) MIS_IC4_SS_SCL_LCNT_reg))
#define MIS_IC4_SS_SCL_LCNT_inst_adr                                                 "0x0086"
#define MIS_IC4_SS_SCL_LCNT_inst                                                     0x0086
#define MIS_IC4_SS_SCL_LCNT_ic_ss_scl_lcnt_shift                                     (0)
#define MIS_IC4_SS_SCL_LCNT_ic_ss_scl_lcnt_mask                                      (0x0000FFFF)
#define MIS_IC4_SS_SCL_LCNT_ic_ss_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC4_SS_SCL_LCNT_ic_ss_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC4_SS_SCL_LCNT_get_ic_ss_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC4_FS_SCL_HCNT                                                          0x1801BA1C
#define MIS_IC4_FS_SCL_HCNT_reg_addr                                                 "0xB801BA1C"
#define MIS_IC4_FS_SCL_HCNT_reg                                                      0xB801BA1C
#define set_MIS_IC4_FS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) MIS_IC4_FS_SCL_HCNT_reg)=data)
#define get_MIS_IC4_FS_SCL_HCNT_reg   (*((volatile unsigned int*) MIS_IC4_FS_SCL_HCNT_reg))
#define MIS_IC4_FS_SCL_HCNT_inst_adr                                                 "0x0087"
#define MIS_IC4_FS_SCL_HCNT_inst                                                     0x0087
#define MIS_IC4_FS_SCL_HCNT_ic_fs_scl_hcnt_shift                                     (0)
#define MIS_IC4_FS_SCL_HCNT_ic_fs_scl_hcnt_mask                                      (0x0000FFFF)
#define MIS_IC4_FS_SCL_HCNT_ic_fs_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC4_FS_SCL_HCNT_ic_fs_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC4_FS_SCL_HCNT_get_ic_fs_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC4_FS_SCL_LCNT                                                          0x1801BA20
#define MIS_IC4_FS_SCL_LCNT_reg_addr                                                 "0xB801BA20"
#define MIS_IC4_FS_SCL_LCNT_reg                                                      0xB801BA20
#define set_MIS_IC4_FS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) MIS_IC4_FS_SCL_LCNT_reg)=data)
#define get_MIS_IC4_FS_SCL_LCNT_reg   (*((volatile unsigned int*) MIS_IC4_FS_SCL_LCNT_reg))
#define MIS_IC4_FS_SCL_LCNT_inst_adr                                                 "0x0088"
#define MIS_IC4_FS_SCL_LCNT_inst                                                     0x0088
#define MIS_IC4_FS_SCL_LCNT_ic_fs_scl_lcnt_shift                                     (0)
#define MIS_IC4_FS_SCL_LCNT_ic_fs_scl_lcnt_mask                                      (0x0000FFFF)
#define MIS_IC4_FS_SCL_LCNT_ic_fs_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC4_FS_SCL_LCNT_ic_fs_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC4_FS_SCL_LCNT_get_ic_fs_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC4_INTR_STAT                                                            0x1801BA2C
#define MIS_IC4_INTR_STAT_reg_addr                                                   "0xB801BA2C"
#define MIS_IC4_INTR_STAT_reg                                                        0xB801BA2C
#define set_MIS_IC4_INTR_STAT_reg(data)   (*((volatile unsigned int*) MIS_IC4_INTR_STAT_reg)=data)
#define get_MIS_IC4_INTR_STAT_reg   (*((volatile unsigned int*) MIS_IC4_INTR_STAT_reg))
#define MIS_IC4_INTR_STAT_inst_adr                                                   "0x008B"
#define MIS_IC4_INTR_STAT_inst                                                       0x008B
#define MIS_IC4_INTR_STAT_r_gen_call_shift                                           (11)
#define MIS_IC4_INTR_STAT_r_gen_call_mask                                            (0x00000800)
#define MIS_IC4_INTR_STAT_r_gen_call(data)                                           (0x00000800&((data)<<11))
#define MIS_IC4_INTR_STAT_r_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC4_INTR_STAT_get_r_gen_call(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC4_INTR_STAT_r_start_det_shift                                          (10)
#define MIS_IC4_INTR_STAT_r_start_det_mask                                           (0x00000400)
#define MIS_IC4_INTR_STAT_r_start_det(data)                                          (0x00000400&((data)<<10))
#define MIS_IC4_INTR_STAT_r_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC4_INTR_STAT_get_r_start_det(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC4_INTR_STAT_r_stop_det_shift                                           (9)
#define MIS_IC4_INTR_STAT_r_stop_det_mask                                            (0x00000200)
#define MIS_IC4_INTR_STAT_r_stop_det(data)                                           (0x00000200&((data)<<9))
#define MIS_IC4_INTR_STAT_r_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC4_INTR_STAT_get_r_stop_det(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC4_INTR_STAT_r_activity_shift                                           (8)
#define MIS_IC4_INTR_STAT_r_activity_mask                                            (0x00000100)
#define MIS_IC4_INTR_STAT_r_activity(data)                                           (0x00000100&((data)<<8))
#define MIS_IC4_INTR_STAT_r_activity_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC4_INTR_STAT_get_r_activity(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC4_INTR_STAT_r_rx_done_shift                                            (7)
#define MIS_IC4_INTR_STAT_r_rx_done_mask                                             (0x00000080)
#define MIS_IC4_INTR_STAT_r_rx_done(data)                                            (0x00000080&((data)<<7))
#define MIS_IC4_INTR_STAT_r_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC4_INTR_STAT_get_r_rx_done(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC4_INTR_STAT_r_tx_abrt_shift                                            (6)
#define MIS_IC4_INTR_STAT_r_tx_abrt_mask                                             (0x00000040)
#define MIS_IC4_INTR_STAT_r_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define MIS_IC4_INTR_STAT_r_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC4_INTR_STAT_get_r_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC4_INTR_STAT_r_rd_req_shift                                             (5)
#define MIS_IC4_INTR_STAT_r_rd_req_mask                                              (0x00000020)
#define MIS_IC4_INTR_STAT_r_rd_req(data)                                             (0x00000020&((data)<<5))
#define MIS_IC4_INTR_STAT_r_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC4_INTR_STAT_get_r_rd_req(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC4_INTR_STAT_r_tx_empty_shift                                           (4)
#define MIS_IC4_INTR_STAT_r_tx_empty_mask                                            (0x00000010)
#define MIS_IC4_INTR_STAT_r_tx_empty(data)                                           (0x00000010&((data)<<4))
#define MIS_IC4_INTR_STAT_r_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC4_INTR_STAT_get_r_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC4_INTR_STAT_r_tx_over_shift                                            (3)
#define MIS_IC4_INTR_STAT_r_tx_over_mask                                             (0x00000008)
#define MIS_IC4_INTR_STAT_r_tx_over(data)                                            (0x00000008&((data)<<3))
#define MIS_IC4_INTR_STAT_r_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC4_INTR_STAT_get_r_tx_over(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC4_INTR_STAT_r_rx_full_shift                                            (2)
#define MIS_IC4_INTR_STAT_r_rx_full_mask                                             (0x00000004)
#define MIS_IC4_INTR_STAT_r_rx_full(data)                                            (0x00000004&((data)<<2))
#define MIS_IC4_INTR_STAT_r_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC4_INTR_STAT_get_r_rx_full(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC4_INTR_STAT_r_rx_over_shift                                            (1)
#define MIS_IC4_INTR_STAT_r_rx_over_mask                                             (0x00000002)
#define MIS_IC4_INTR_STAT_r_rx_over(data)                                            (0x00000002&((data)<<1))
#define MIS_IC4_INTR_STAT_r_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC4_INTR_STAT_get_r_rx_over(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC4_INTR_STAT_r_rx_under_shift                                           (0)
#define MIS_IC4_INTR_STAT_r_rx_under_mask                                            (0x00000001)
#define MIS_IC4_INTR_STAT_r_rx_under(data)                                           (0x00000001&((data)<<0))
#define MIS_IC4_INTR_STAT_r_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_IC4_INTR_STAT_get_r_rx_under(data)                                       ((0x00000001&(data))>>0)


#define MIS_IC4_INTR_MASK                                                            0x1801BA30
#define MIS_IC4_INTR_MASK_reg_addr                                                   "0xB801BA30"
#define MIS_IC4_INTR_MASK_reg                                                        0xB801BA30
#define set_MIS_IC4_INTR_MASK_reg(data)   (*((volatile unsigned int*) MIS_IC4_INTR_MASK_reg)=data)
#define get_MIS_IC4_INTR_MASK_reg   (*((volatile unsigned int*) MIS_IC4_INTR_MASK_reg))
#define MIS_IC4_INTR_MASK_inst_adr                                                   "0x008C"
#define MIS_IC4_INTR_MASK_inst                                                       0x008C
#define MIS_IC4_INTR_MASK_m_gen_call_shift                                           (11)
#define MIS_IC4_INTR_MASK_m_gen_call_mask                                            (0x00000800)
#define MIS_IC4_INTR_MASK_m_gen_call(data)                                           (0x00000800&((data)<<11))
#define MIS_IC4_INTR_MASK_m_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC4_INTR_MASK_get_m_gen_call(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC4_INTR_MASK_m_start_det_shift                                          (10)
#define MIS_IC4_INTR_MASK_m_start_det_mask                                           (0x00000400)
#define MIS_IC4_INTR_MASK_m_start_det(data)                                          (0x00000400&((data)<<10))
#define MIS_IC4_INTR_MASK_m_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC4_INTR_MASK_get_m_start_det(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC4_INTR_MASK_m_stop_det_shift                                           (9)
#define MIS_IC4_INTR_MASK_m_stop_det_mask                                            (0x00000200)
#define MIS_IC4_INTR_MASK_m_stop_det(data)                                           (0x00000200&((data)<<9))
#define MIS_IC4_INTR_MASK_m_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC4_INTR_MASK_get_m_stop_det(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC4_INTR_MASK_m_activity_shift                                           (8)
#define MIS_IC4_INTR_MASK_m_activity_mask                                            (0x00000100)
#define MIS_IC4_INTR_MASK_m_activity(data)                                           (0x00000100&((data)<<8))
#define MIS_IC4_INTR_MASK_m_activity_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC4_INTR_MASK_get_m_activity(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC4_INTR_MASK_m_rx_done_shift                                            (7)
#define MIS_IC4_INTR_MASK_m_rx_done_mask                                             (0x00000080)
#define MIS_IC4_INTR_MASK_m_rx_done(data)                                            (0x00000080&((data)<<7))
#define MIS_IC4_INTR_MASK_m_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC4_INTR_MASK_get_m_rx_done(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC4_INTR_MASK_m_tx_abrt_shift                                            (6)
#define MIS_IC4_INTR_MASK_m_tx_abrt_mask                                             (0x00000040)
#define MIS_IC4_INTR_MASK_m_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define MIS_IC4_INTR_MASK_m_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC4_INTR_MASK_get_m_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC4_INTR_MASK_m_rd_req_shift                                             (5)
#define MIS_IC4_INTR_MASK_m_rd_req_mask                                              (0x00000020)
#define MIS_IC4_INTR_MASK_m_rd_req(data)                                             (0x00000020&((data)<<5))
#define MIS_IC4_INTR_MASK_m_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC4_INTR_MASK_get_m_rd_req(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC4_INTR_MASK_m_tx_empty_shift                                           (4)
#define MIS_IC4_INTR_MASK_m_tx_empty_mask                                            (0x00000010)
#define MIS_IC4_INTR_MASK_m_tx_empty(data)                                           (0x00000010&((data)<<4))
#define MIS_IC4_INTR_MASK_m_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC4_INTR_MASK_get_m_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC4_INTR_MASK_m_tx_over_shift                                            (3)
#define MIS_IC4_INTR_MASK_m_tx_over_mask                                             (0x00000008)
#define MIS_IC4_INTR_MASK_m_tx_over(data)                                            (0x00000008&((data)<<3))
#define MIS_IC4_INTR_MASK_m_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC4_INTR_MASK_get_m_tx_over(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC4_INTR_MASK_m_rx_full_shift                                            (2)
#define MIS_IC4_INTR_MASK_m_rx_full_mask                                             (0x00000004)
#define MIS_IC4_INTR_MASK_m_rx_full(data)                                            (0x00000004&((data)<<2))
#define MIS_IC4_INTR_MASK_m_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC4_INTR_MASK_get_m_rx_full(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC4_INTR_MASK_m_rx_over_shift                                            (1)
#define MIS_IC4_INTR_MASK_m_rx_over_mask                                             (0x00000002)
#define MIS_IC4_INTR_MASK_m_rx_over(data)                                            (0x00000002&((data)<<1))
#define MIS_IC4_INTR_MASK_m_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC4_INTR_MASK_get_m_rx_over(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC4_INTR_MASK_m_rx_under_shift                                           (0)
#define MIS_IC4_INTR_MASK_m_rx_under_mask                                            (0x00000001)
#define MIS_IC4_INTR_MASK_m_rx_under(data)                                           (0x00000001&((data)<<0))
#define MIS_IC4_INTR_MASK_m_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_IC4_INTR_MASK_get_m_rx_under(data)                                       ((0x00000001&(data))>>0)


#define MIS_IC4_RAW_INTR_STAT                                                        0x1801BA34
#define MIS_IC4_RAW_INTR_STAT_reg_addr                                               "0xB801BA34"
#define MIS_IC4_RAW_INTR_STAT_reg                                                    0xB801BA34
#define set_MIS_IC4_RAW_INTR_STAT_reg(data)   (*((volatile unsigned int*) MIS_IC4_RAW_INTR_STAT_reg)=data)
#define get_MIS_IC4_RAW_INTR_STAT_reg   (*((volatile unsigned int*) MIS_IC4_RAW_INTR_STAT_reg))
#define MIS_IC4_RAW_INTR_STAT_inst_adr                                               "0x008D"
#define MIS_IC4_RAW_INTR_STAT_inst                                                   0x008D
#define MIS_IC4_RAW_INTR_STAT_gen_call_shift                                         (11)
#define MIS_IC4_RAW_INTR_STAT_gen_call_mask                                          (0x00000800)
#define MIS_IC4_RAW_INTR_STAT_gen_call(data)                                         (0x00000800&((data)<<11))
#define MIS_IC4_RAW_INTR_STAT_gen_call_src(data)                                     ((0x00000800&(data))>>11)
#define MIS_IC4_RAW_INTR_STAT_get_gen_call(data)                                     ((0x00000800&(data))>>11)
#define MIS_IC4_RAW_INTR_STAT_start_det_shift                                        (10)
#define MIS_IC4_RAW_INTR_STAT_start_det_mask                                         (0x00000400)
#define MIS_IC4_RAW_INTR_STAT_start_det(data)                                        (0x00000400&((data)<<10))
#define MIS_IC4_RAW_INTR_STAT_start_det_src(data)                                    ((0x00000400&(data))>>10)
#define MIS_IC4_RAW_INTR_STAT_get_start_det(data)                                    ((0x00000400&(data))>>10)
#define MIS_IC4_RAW_INTR_STAT_stop_det_shift                                         (9)
#define MIS_IC4_RAW_INTR_STAT_stop_det_mask                                          (0x00000200)
#define MIS_IC4_RAW_INTR_STAT_stop_det(data)                                         (0x00000200&((data)<<9))
#define MIS_IC4_RAW_INTR_STAT_stop_det_src(data)                                     ((0x00000200&(data))>>9)
#define MIS_IC4_RAW_INTR_STAT_get_stop_det(data)                                     ((0x00000200&(data))>>9)
#define MIS_IC4_RAW_INTR_STAT_activity_shift                                         (8)
#define MIS_IC4_RAW_INTR_STAT_activity_mask                                          (0x00000100)
#define MIS_IC4_RAW_INTR_STAT_activity(data)                                         (0x00000100&((data)<<8))
#define MIS_IC4_RAW_INTR_STAT_activity_src(data)                                     ((0x00000100&(data))>>8)
#define MIS_IC4_RAW_INTR_STAT_get_activity(data)                                     ((0x00000100&(data))>>8)
#define MIS_IC4_RAW_INTR_STAT_rx_done_shift                                          (7)
#define MIS_IC4_RAW_INTR_STAT_rx_done_mask                                           (0x00000080)
#define MIS_IC4_RAW_INTR_STAT_rx_done(data)                                          (0x00000080&((data)<<7))
#define MIS_IC4_RAW_INTR_STAT_rx_done_src(data)                                      ((0x00000080&(data))>>7)
#define MIS_IC4_RAW_INTR_STAT_get_rx_done(data)                                      ((0x00000080&(data))>>7)
#define MIS_IC4_RAW_INTR_STAT_tx_abrt_shift                                          (6)
#define MIS_IC4_RAW_INTR_STAT_tx_abrt_mask                                           (0x00000040)
#define MIS_IC4_RAW_INTR_STAT_tx_abrt(data)                                          (0x00000040&((data)<<6))
#define MIS_IC4_RAW_INTR_STAT_tx_abrt_src(data)                                      ((0x00000040&(data))>>6)
#define MIS_IC4_RAW_INTR_STAT_get_tx_abrt(data)                                      ((0x00000040&(data))>>6)
#define MIS_IC4_RAW_INTR_STAT_rd_req_shift                                           (5)
#define MIS_IC4_RAW_INTR_STAT_rd_req_mask                                            (0x00000020)
#define MIS_IC4_RAW_INTR_STAT_rd_req(data)                                           (0x00000020&((data)<<5))
#define MIS_IC4_RAW_INTR_STAT_rd_req_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC4_RAW_INTR_STAT_get_rd_req(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC4_RAW_INTR_STAT_tx_empty_shift                                         (4)
#define MIS_IC4_RAW_INTR_STAT_tx_empty_mask                                          (0x00000010)
#define MIS_IC4_RAW_INTR_STAT_tx_empty(data)                                         (0x00000010&((data)<<4))
#define MIS_IC4_RAW_INTR_STAT_tx_empty_src(data)                                     ((0x00000010&(data))>>4)
#define MIS_IC4_RAW_INTR_STAT_get_tx_empty(data)                                     ((0x00000010&(data))>>4)
#define MIS_IC4_RAW_INTR_STAT_tx_over_shift                                          (3)
#define MIS_IC4_RAW_INTR_STAT_tx_over_mask                                           (0x00000008)
#define MIS_IC4_RAW_INTR_STAT_tx_over(data)                                          (0x00000008&((data)<<3))
#define MIS_IC4_RAW_INTR_STAT_tx_over_src(data)                                      ((0x00000008&(data))>>3)
#define MIS_IC4_RAW_INTR_STAT_get_tx_over(data)                                      ((0x00000008&(data))>>3)
#define MIS_IC4_RAW_INTR_STAT_rx_full_shift                                          (2)
#define MIS_IC4_RAW_INTR_STAT_rx_full_mask                                           (0x00000004)
#define MIS_IC4_RAW_INTR_STAT_rx_full(data)                                          (0x00000004&((data)<<2))
#define MIS_IC4_RAW_INTR_STAT_rx_full_src(data)                                      ((0x00000004&(data))>>2)
#define MIS_IC4_RAW_INTR_STAT_get_rx_full(data)                                      ((0x00000004&(data))>>2)
#define MIS_IC4_RAW_INTR_STAT_rx_over_shift                                          (1)
#define MIS_IC4_RAW_INTR_STAT_rx_over_mask                                           (0x00000002)
#define MIS_IC4_RAW_INTR_STAT_rx_over(data)                                          (0x00000002&((data)<<1))
#define MIS_IC4_RAW_INTR_STAT_rx_over_src(data)                                      ((0x00000002&(data))>>1)
#define MIS_IC4_RAW_INTR_STAT_get_rx_over(data)                                      ((0x00000002&(data))>>1)
#define MIS_IC4_RAW_INTR_STAT_rx_under_shift                                         (0)
#define MIS_IC4_RAW_INTR_STAT_rx_under_mask                                          (0x00000001)
#define MIS_IC4_RAW_INTR_STAT_rx_under(data)                                         (0x00000001&((data)<<0))
#define MIS_IC4_RAW_INTR_STAT_rx_under_src(data)                                     ((0x00000001&(data))>>0)
#define MIS_IC4_RAW_INTR_STAT_get_rx_under(data)                                     ((0x00000001&(data))>>0)


#define MIS_IC4_RX_TL                                                                0x1801BA38
#define MIS_IC4_RX_TL_reg_addr                                                       "0xB801BA38"
#define MIS_IC4_RX_TL_reg                                                            0xB801BA38
#define set_MIS_IC4_RX_TL_reg(data)   (*((volatile unsigned int*) MIS_IC4_RX_TL_reg)=data)
#define get_MIS_IC4_RX_TL_reg   (*((volatile unsigned int*) MIS_IC4_RX_TL_reg))
#define MIS_IC4_RX_TL_inst_adr                                                       "0x008E"
#define MIS_IC4_RX_TL_inst                                                           0x008E
#define MIS_IC4_RX_TL_rx_tl_shift                                                    (0)
#define MIS_IC4_RX_TL_rx_tl_mask                                                     (0x000000FF)
#define MIS_IC4_RX_TL_rx_tl(data)                                                    (0x000000FF&((data)<<0))
#define MIS_IC4_RX_TL_rx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define MIS_IC4_RX_TL_get_rx_tl(data)                                                ((0x000000FF&(data))>>0)


#define MIS_IC4_TX_TL                                                                0x1801BA3C
#define MIS_IC4_TX_TL_reg_addr                                                       "0xB801BA3C"
#define MIS_IC4_TX_TL_reg                                                            0xB801BA3C
#define set_MIS_IC4_TX_TL_reg(data)   (*((volatile unsigned int*) MIS_IC4_TX_TL_reg)=data)
#define get_MIS_IC4_TX_TL_reg   (*((volatile unsigned int*) MIS_IC4_TX_TL_reg))
#define MIS_IC4_TX_TL_inst_adr                                                       "0x008F"
#define MIS_IC4_TX_TL_inst                                                           0x008F
#define MIS_IC4_TX_TL_tx_tl_shift                                                    (0)
#define MIS_IC4_TX_TL_tx_tl_mask                                                     (0x000000FF)
#define MIS_IC4_TX_TL_tx_tl(data)                                                    (0x000000FF&((data)<<0))
#define MIS_IC4_TX_TL_tx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define MIS_IC4_TX_TL_get_tx_tl(data)                                                ((0x000000FF&(data))>>0)


#define MIS_IC4_CLR_INTR                                                             0x1801BA40
#define MIS_IC4_CLR_INTR_reg_addr                                                    "0xB801BA40"
#define MIS_IC4_CLR_INTR_reg                                                         0xB801BA40
#define set_MIS_IC4_CLR_INTR_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_INTR_reg)=data)
#define get_MIS_IC4_CLR_INTR_reg   (*((volatile unsigned int*) MIS_IC4_CLR_INTR_reg))
#define MIS_IC4_CLR_INTR_inst_adr                                                    "0x0090"
#define MIS_IC4_CLR_INTR_inst                                                        0x0090
#define MIS_IC4_CLR_INTR_clr_intr_shift                                              (0)
#define MIS_IC4_CLR_INTR_clr_intr_mask                                               (0x00000001)
#define MIS_IC4_CLR_INTR_clr_intr(data)                                              (0x00000001&((data)<<0))
#define MIS_IC4_CLR_INTR_clr_intr_src(data)                                          ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_INTR_get_clr_intr(data)                                          ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_RX_UNDER                                                         0x1801BA44
#define MIS_IC4_CLR_RX_UNDER_reg_addr                                                "0xB801BA44"
#define MIS_IC4_CLR_RX_UNDER_reg                                                     0xB801BA44
#define set_MIS_IC4_CLR_RX_UNDER_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_RX_UNDER_reg)=data)
#define get_MIS_IC4_CLR_RX_UNDER_reg   (*((volatile unsigned int*) MIS_IC4_CLR_RX_UNDER_reg))
#define MIS_IC4_CLR_RX_UNDER_inst_adr                                                "0x0091"
#define MIS_IC4_CLR_RX_UNDER_inst                                                    0x0091
#define MIS_IC4_CLR_RX_UNDER_clr_rx_under_shift                                      (0)
#define MIS_IC4_CLR_RX_UNDER_clr_rx_under_mask                                       (0x00000001)
#define MIS_IC4_CLR_RX_UNDER_clr_rx_under(data)                                      (0x00000001&((data)<<0))
#define MIS_IC4_CLR_RX_UNDER_clr_rx_under_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_RX_UNDER_get_clr_rx_under(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_RX_OVER                                                          0x1801BA48
#define MIS_IC4_CLR_RX_OVER_reg_addr                                                 "0xB801BA48"
#define MIS_IC4_CLR_RX_OVER_reg                                                      0xB801BA48
#define set_MIS_IC4_CLR_RX_OVER_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_RX_OVER_reg)=data)
#define get_MIS_IC4_CLR_RX_OVER_reg   (*((volatile unsigned int*) MIS_IC4_CLR_RX_OVER_reg))
#define MIS_IC4_CLR_RX_OVER_inst_adr                                                 "0x0092"
#define MIS_IC4_CLR_RX_OVER_inst                                                     0x0092
#define MIS_IC4_CLR_RX_OVER_clr_rx_over_shift                                        (0)
#define MIS_IC4_CLR_RX_OVER_clr_rx_over_mask                                         (0x00000001)
#define MIS_IC4_CLR_RX_OVER_clr_rx_over(data)                                        (0x00000001&((data)<<0))
#define MIS_IC4_CLR_RX_OVER_clr_rx_over_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_RX_OVER_get_clr_rx_over(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_TX_OVER                                                          0x1801BA4C
#define MIS_IC4_CLR_TX_OVER_reg_addr                                                 "0xB801BA4C"
#define MIS_IC4_CLR_TX_OVER_reg                                                      0xB801BA4C
#define set_MIS_IC4_CLR_TX_OVER_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_TX_OVER_reg)=data)
#define get_MIS_IC4_CLR_TX_OVER_reg   (*((volatile unsigned int*) MIS_IC4_CLR_TX_OVER_reg))
#define MIS_IC4_CLR_TX_OVER_inst_adr                                                 "0x0093"
#define MIS_IC4_CLR_TX_OVER_inst                                                     0x0093
#define MIS_IC4_CLR_TX_OVER_clr_tx_over_shift                                        (0)
#define MIS_IC4_CLR_TX_OVER_clr_tx_over_mask                                         (0x00000001)
#define MIS_IC4_CLR_TX_OVER_clr_tx_over(data)                                        (0x00000001&((data)<<0))
#define MIS_IC4_CLR_TX_OVER_clr_tx_over_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_TX_OVER_get_clr_tx_over(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_RD_REQ                                                           0x1801BA50
#define MIS_IC4_CLR_RD_REQ_reg_addr                                                  "0xB801BA50"
#define MIS_IC4_CLR_RD_REQ_reg                                                       0xB801BA50
#define set_MIS_IC4_CLR_RD_REQ_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_RD_REQ_reg)=data)
#define get_MIS_IC4_CLR_RD_REQ_reg   (*((volatile unsigned int*) MIS_IC4_CLR_RD_REQ_reg))
#define MIS_IC4_CLR_RD_REQ_inst_adr                                                  "0x0094"
#define MIS_IC4_CLR_RD_REQ_inst                                                      0x0094
#define MIS_IC4_CLR_RD_REQ_clr_rd_req_shift                                          (0)
#define MIS_IC4_CLR_RD_REQ_clr_rd_req_mask                                           (0x00000001)
#define MIS_IC4_CLR_RD_REQ_clr_rd_req(data)                                          (0x00000001&((data)<<0))
#define MIS_IC4_CLR_RD_REQ_clr_rd_req_src(data)                                      ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_RD_REQ_get_clr_rd_req(data)                                      ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_TX_ABRT                                                          0x1801BA54
#define MIS_IC4_CLR_TX_ABRT_reg_addr                                                 "0xB801BA54"
#define MIS_IC4_CLR_TX_ABRT_reg                                                      0xB801BA54
#define set_MIS_IC4_CLR_TX_ABRT_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_TX_ABRT_reg)=data)
#define get_MIS_IC4_CLR_TX_ABRT_reg   (*((volatile unsigned int*) MIS_IC4_CLR_TX_ABRT_reg))
#define MIS_IC4_CLR_TX_ABRT_inst_adr                                                 "0x0095"
#define MIS_IC4_CLR_TX_ABRT_inst                                                     0x0095
#define MIS_IC4_CLR_TX_ABRT_clr_tx_abrt_shift                                        (0)
#define MIS_IC4_CLR_TX_ABRT_clr_tx_abrt_mask                                         (0x00000001)
#define MIS_IC4_CLR_TX_ABRT_clr_tx_abrt(data)                                        (0x00000001&((data)<<0))
#define MIS_IC4_CLR_TX_ABRT_clr_tx_abrt_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_TX_ABRT_get_clr_tx_abrt(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_RX_DONE                                                          0x1801BA58
#define MIS_IC4_CLR_RX_DONE_reg_addr                                                 "0xB801BA58"
#define MIS_IC4_CLR_RX_DONE_reg                                                      0xB801BA58
#define set_MIS_IC4_CLR_RX_DONE_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_RX_DONE_reg)=data)
#define get_MIS_IC4_CLR_RX_DONE_reg   (*((volatile unsigned int*) MIS_IC4_CLR_RX_DONE_reg))
#define MIS_IC4_CLR_RX_DONE_inst_adr                                                 "0x0096"
#define MIS_IC4_CLR_RX_DONE_inst                                                     0x0096
#define MIS_IC4_CLR_RX_DONE_clr_rx_done_shift                                        (0)
#define MIS_IC4_CLR_RX_DONE_clr_rx_done_mask                                         (0x00000001)
#define MIS_IC4_CLR_RX_DONE_clr_rx_done(data)                                        (0x00000001&((data)<<0))
#define MIS_IC4_CLR_RX_DONE_clr_rx_done_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_RX_DONE_get_clr_rx_done(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_ACTIVITY                                                         0x1801BA5C
#define MIS_IC4_CLR_ACTIVITY_reg_addr                                                "0xB801BA5C"
#define MIS_IC4_CLR_ACTIVITY_reg                                                     0xB801BA5C
#define set_MIS_IC4_CLR_ACTIVITY_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_ACTIVITY_reg)=data)
#define get_MIS_IC4_CLR_ACTIVITY_reg   (*((volatile unsigned int*) MIS_IC4_CLR_ACTIVITY_reg))
#define MIS_IC4_CLR_ACTIVITY_inst_adr                                                "0x0097"
#define MIS_IC4_CLR_ACTIVITY_inst                                                    0x0097
#define MIS_IC4_CLR_ACTIVITY_clr_activity_shift                                      (0)
#define MIS_IC4_CLR_ACTIVITY_clr_activity_mask                                       (0x00000001)
#define MIS_IC4_CLR_ACTIVITY_clr_activity(data)                                      (0x00000001&((data)<<0))
#define MIS_IC4_CLR_ACTIVITY_clr_activity_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_ACTIVITY_get_clr_activity(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_STOP_DET                                                         0x1801BA60
#define MIS_IC4_CLR_STOP_DET_reg_addr                                                "0xB801BA60"
#define MIS_IC4_CLR_STOP_DET_reg                                                     0xB801BA60
#define set_MIS_IC4_CLR_STOP_DET_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_STOP_DET_reg)=data)
#define get_MIS_IC4_CLR_STOP_DET_reg   (*((volatile unsigned int*) MIS_IC4_CLR_STOP_DET_reg))
#define MIS_IC4_CLR_STOP_DET_inst_adr                                                "0x0098"
#define MIS_IC4_CLR_STOP_DET_inst                                                    0x0098
#define MIS_IC4_CLR_STOP_DET_clr_stop_det_shift                                      (0)
#define MIS_IC4_CLR_STOP_DET_clr_stop_det_mask                                       (0x00000001)
#define MIS_IC4_CLR_STOP_DET_clr_stop_det(data)                                      (0x00000001&((data)<<0))
#define MIS_IC4_CLR_STOP_DET_clr_stop_det_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_STOP_DET_get_clr_stop_det(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_START_DET                                                        0x1801BA64
#define MIS_IC4_CLR_START_DET_reg_addr                                               "0xB801BA64"
#define MIS_IC4_CLR_START_DET_reg                                                    0xB801BA64
#define set_MIS_IC4_CLR_START_DET_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_START_DET_reg)=data)
#define get_MIS_IC4_CLR_START_DET_reg   (*((volatile unsigned int*) MIS_IC4_CLR_START_DET_reg))
#define MIS_IC4_CLR_START_DET_inst_adr                                               "0x0099"
#define MIS_IC4_CLR_START_DET_inst                                                   0x0099
#define MIS_IC4_CLR_START_DET_clr_start_det_shift                                    (0)
#define MIS_IC4_CLR_START_DET_clr_start_det_mask                                     (0x00000001)
#define MIS_IC4_CLR_START_DET_clr_start_det(data)                                    (0x00000001&((data)<<0))
#define MIS_IC4_CLR_START_DET_clr_start_det_src(data)                                ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_START_DET_get_clr_start_det(data)                                ((0x00000001&(data))>>0)


#define MIS_IC4_CLR_GEN_CALL                                                         0x1801BA68
#define MIS_IC4_CLR_GEN_CALL_reg_addr                                                "0xB801BA68"
#define MIS_IC4_CLR_GEN_CALL_reg                                                     0xB801BA68
#define set_MIS_IC4_CLR_GEN_CALL_reg(data)   (*((volatile unsigned int*) MIS_IC4_CLR_GEN_CALL_reg)=data)
#define get_MIS_IC4_CLR_GEN_CALL_reg   (*((volatile unsigned int*) MIS_IC4_CLR_GEN_CALL_reg))
#define MIS_IC4_CLR_GEN_CALL_inst_adr                                                "0x009A"
#define MIS_IC4_CLR_GEN_CALL_inst                                                    0x009A
#define MIS_IC4_CLR_GEN_CALL_clr_gen_call_shift                                      (0)
#define MIS_IC4_CLR_GEN_CALL_clr_gen_call_mask                                       (0x00000001)
#define MIS_IC4_CLR_GEN_CALL_clr_gen_call(data)                                      (0x00000001&((data)<<0))
#define MIS_IC4_CLR_GEN_CALL_clr_gen_call_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC4_CLR_GEN_CALL_get_clr_gen_call(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC4_ENABLE                                                               0x1801BA6C
#define MIS_IC4_ENABLE_reg_addr                                                      "0xB801BA6C"
#define MIS_IC4_ENABLE_reg                                                           0xB801BA6C
#define set_MIS_IC4_ENABLE_reg(data)   (*((volatile unsigned int*) MIS_IC4_ENABLE_reg)=data)
#define get_MIS_IC4_ENABLE_reg   (*((volatile unsigned int*) MIS_IC4_ENABLE_reg))
#define MIS_IC4_ENABLE_inst_adr                                                      "0x009B"
#define MIS_IC4_ENABLE_inst                                                          0x009B
#define MIS_IC4_ENABLE_enable_shift                                                  (0)
#define MIS_IC4_ENABLE_enable_mask                                                   (0x00000001)
#define MIS_IC4_ENABLE_enable(data)                                                  (0x00000001&((data)<<0))
#define MIS_IC4_ENABLE_enable_src(data)                                              ((0x00000001&(data))>>0)
#define MIS_IC4_ENABLE_get_enable(data)                                              ((0x00000001&(data))>>0)


#define MIS_IC4_STATUS                                                               0x1801BA70
#define MIS_IC4_STATUS_reg_addr                                                      "0xB801BA70"
#define MIS_IC4_STATUS_reg                                                           0xB801BA70
#define set_MIS_IC4_STATUS_reg(data)   (*((volatile unsigned int*) MIS_IC4_STATUS_reg)=data)
#define get_MIS_IC4_STATUS_reg   (*((volatile unsigned int*) MIS_IC4_STATUS_reg))
#define MIS_IC4_STATUS_inst_adr                                                      "0x009C"
#define MIS_IC4_STATUS_inst                                                          0x009C
#define MIS_IC4_STATUS_slv_activity_shift                                            (6)
#define MIS_IC4_STATUS_slv_activity_mask                                             (0x00000040)
#define MIS_IC4_STATUS_slv_activity(data)                                            (0x00000040&((data)<<6))
#define MIS_IC4_STATUS_slv_activity_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC4_STATUS_get_slv_activity(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC4_STATUS_mst_activity_shift                                            (5)
#define MIS_IC4_STATUS_mst_activity_mask                                             (0x00000020)
#define MIS_IC4_STATUS_mst_activity(data)                                            (0x00000020&((data)<<5))
#define MIS_IC4_STATUS_mst_activity_src(data)                                        ((0x00000020&(data))>>5)
#define MIS_IC4_STATUS_get_mst_activity(data)                                        ((0x00000020&(data))>>5)
#define MIS_IC4_STATUS_rff_shift                                                     (4)
#define MIS_IC4_STATUS_rff_mask                                                      (0x00000010)
#define MIS_IC4_STATUS_rff(data)                                                     (0x00000010&((data)<<4))
#define MIS_IC4_STATUS_rff_src(data)                                                 ((0x00000010&(data))>>4)
#define MIS_IC4_STATUS_get_rff(data)                                                 ((0x00000010&(data))>>4)
#define MIS_IC4_STATUS_rfne_shift                                                    (3)
#define MIS_IC4_STATUS_rfne_mask                                                     (0x00000008)
#define MIS_IC4_STATUS_rfne(data)                                                    (0x00000008&((data)<<3))
#define MIS_IC4_STATUS_rfne_src(data)                                                ((0x00000008&(data))>>3)
#define MIS_IC4_STATUS_get_rfne(data)                                                ((0x00000008&(data))>>3)
#define MIS_IC4_STATUS_tfe_shift                                                     (2)
#define MIS_IC4_STATUS_tfe_mask                                                      (0x00000004)
#define MIS_IC4_STATUS_tfe(data)                                                     (0x00000004&((data)<<2))
#define MIS_IC4_STATUS_tfe_src(data)                                                 ((0x00000004&(data))>>2)
#define MIS_IC4_STATUS_get_tfe(data)                                                 ((0x00000004&(data))>>2)
#define MIS_IC4_STATUS_tfnf_shift                                                    (1)
#define MIS_IC4_STATUS_tfnf_mask                                                     (0x00000002)
#define MIS_IC4_STATUS_tfnf(data)                                                    (0x00000002&((data)<<1))
#define MIS_IC4_STATUS_tfnf_src(data)                                                ((0x00000002&(data))>>1)
#define MIS_IC4_STATUS_get_tfnf(data)                                                ((0x00000002&(data))>>1)
#define MIS_IC4_STATUS_activity_shift                                                (0)
#define MIS_IC4_STATUS_activity_mask                                                 (0x00000001)
#define MIS_IC4_STATUS_activity(data)                                                (0x00000001&((data)<<0))
#define MIS_IC4_STATUS_activity_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_IC4_STATUS_get_activity(data)                                            ((0x00000001&(data))>>0)


#define MIS_IC4_TXFLR                                                                0x1801BA74
#define MIS_IC4_TXFLR_reg_addr                                                       "0xB801BA74"
#define MIS_IC4_TXFLR_reg                                                            0xB801BA74
#define set_MIS_IC4_TXFLR_reg(data)   (*((volatile unsigned int*) MIS_IC4_TXFLR_reg)=data)
#define get_MIS_IC4_TXFLR_reg   (*((volatile unsigned int*) MIS_IC4_TXFLR_reg))
#define MIS_IC4_TXFLR_inst_adr                                                       "0x009D"
#define MIS_IC4_TXFLR_inst                                                           0x009D
#define MIS_IC4_TXFLR_txflr_shift                                                    (0)
#define MIS_IC4_TXFLR_txflr_mask                                                     (0x0000000F)
#define MIS_IC4_TXFLR_txflr(data)                                                    (0x0000000F&((data)<<0))
#define MIS_IC4_TXFLR_txflr_src(data)                                                ((0x0000000F&(data))>>0)
#define MIS_IC4_TXFLR_get_txflr(data)                                                ((0x0000000F&(data))>>0)


#define MIS_IC4_RXFLR                                                                0x1801BA78
#define MIS_IC4_RXFLR_reg_addr                                                       "0xB801BA78"
#define MIS_IC4_RXFLR_reg                                                            0xB801BA78
#define set_MIS_IC4_RXFLR_reg(data)   (*((volatile unsigned int*) MIS_IC4_RXFLR_reg)=data)
#define get_MIS_IC4_RXFLR_reg   (*((volatile unsigned int*) MIS_IC4_RXFLR_reg))
#define MIS_IC4_RXFLR_inst_adr                                                       "0x009E"
#define MIS_IC4_RXFLR_inst                                                           0x009E
#define MIS_IC4_RXFLR_rxflr_shift                                                    (0)
#define MIS_IC4_RXFLR_rxflr_mask                                                     (0x0000000F)
#define MIS_IC4_RXFLR_rxflr(data)                                                    (0x0000000F&((data)<<0))
#define MIS_IC4_RXFLR_rxflr_src(data)                                                ((0x0000000F&(data))>>0)
#define MIS_IC4_RXFLR_get_rxflr(data)                                                ((0x0000000F&(data))>>0)


#define MIS_IC4_SDA_HOLD                                                             0x1801BA7C
#define MIS_IC4_SDA_HOLD_reg_addr                                                    "0xB801BA7C"
#define MIS_IC4_SDA_HOLD_reg                                                         0xB801BA7C
#define set_MIS_IC4_SDA_HOLD_reg(data)   (*((volatile unsigned int*) MIS_IC4_SDA_HOLD_reg)=data)
#define get_MIS_IC4_SDA_HOLD_reg   (*((volatile unsigned int*) MIS_IC4_SDA_HOLD_reg))
#define MIS_IC4_SDA_HOLD_inst_adr                                                    "0x009F"
#define MIS_IC4_SDA_HOLD_inst                                                        0x009F
#define MIS_IC4_SDA_HOLD_sda_hold_shift                                              (0)
#define MIS_IC4_SDA_HOLD_sda_hold_mask                                               (0x0000FFFF)
#define MIS_IC4_SDA_HOLD_sda_hold(data)                                              (0x0000FFFF&((data)<<0))
#define MIS_IC4_SDA_HOLD_sda_hold_src(data)                                          ((0x0000FFFF&(data))>>0)
#define MIS_IC4_SDA_HOLD_get_sda_hold(data)                                          ((0x0000FFFF&(data))>>0)


#define MIS_IC4_TX_ABRT_SOURCE                                                       0x1801BA80
#define MIS_IC4_TX_ABRT_SOURCE_reg_addr                                              "0xB801BA80"
#define MIS_IC4_TX_ABRT_SOURCE_reg                                                   0xB801BA80
#define set_MIS_IC4_TX_ABRT_SOURCE_reg(data)   (*((volatile unsigned int*) MIS_IC4_TX_ABRT_SOURCE_reg)=data)
#define get_MIS_IC4_TX_ABRT_SOURCE_reg   (*((volatile unsigned int*) MIS_IC4_TX_ABRT_SOURCE_reg))
#define MIS_IC4_TX_ABRT_SOURCE_inst_adr                                              "0x00A0"
#define MIS_IC4_TX_ABRT_SOURCE_inst                                                  0x00A0
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slvrd_intx_shift                                 (15)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slvrd_intx_mask                                  (0x00008000)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slvrd_intx(data)                                 (0x00008000&((data)<<15))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slvrd_intx_src(data)                             ((0x00008000&(data))>>15)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_slvrd_intx(data)                             ((0x00008000&(data))>>15)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slv_arblost_shift                                (14)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slv_arblost_mask                                 (0x00004000)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slv_arblost(data)                                (0x00004000&((data)<<14))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slv_arblost_src(data)                            ((0x00004000&(data))>>14)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_slv_arblost(data)                            ((0x00004000&(data))>>14)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slvflush_txfifo_shift                            (13)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slvflush_txfifo_mask                             (0x00002000)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slvflush_txfifo(data)                            (0x00002000&((data)<<13))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_slvflush_txfifo_src(data)                        ((0x00002000&(data))>>13)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_slvflush_txfifo(data)                        ((0x00002000&(data))>>13)
#define MIS_IC4_TX_ABRT_SOURCE_arb_lost_shift                                        (12)
#define MIS_IC4_TX_ABRT_SOURCE_arb_lost_mask                                         (0x00001000)
#define MIS_IC4_TX_ABRT_SOURCE_arb_lost(data)                                        (0x00001000&((data)<<12))
#define MIS_IC4_TX_ABRT_SOURCE_arb_lost_src(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC4_TX_ABRT_SOURCE_get_arb_lost(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC4_TX_ABRT_SOURCE_arb_master_dis_shift                                  (11)
#define MIS_IC4_TX_ABRT_SOURCE_arb_master_dis_mask                                   (0x00000800)
#define MIS_IC4_TX_ABRT_SOURCE_arb_master_dis(data)                                  (0x00000800&((data)<<11))
#define MIS_IC4_TX_ABRT_SOURCE_arb_master_dis_src(data)                              ((0x00000800&(data))>>11)
#define MIS_IC4_TX_ABRT_SOURCE_get_arb_master_dis(data)                              ((0x00000800&(data))>>11)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_shift                             (10)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_mask                              (0x00000400)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10b_rd_norstrt(data)                             (0x00000400&((data)<<10))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_src(data)                         ((0x00000400&(data))>>10)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_10b_rd_norstrt(data)                         ((0x00000400&(data))>>10)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_sbyte_norstrt_shift                              (9)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_sbyte_norstrt_mask                               (0x00000200)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_sbyte_norstrt(data)                              (0x00000200&((data)<<9))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_sbyte_norstrt_src(data)                          ((0x00000200&(data))>>9)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_sbyte_norstrt(data)                          ((0x00000200&(data))>>9)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_hs_norstrt_shift                                 (8)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_hs_norstrt_mask                                  (0x00000100)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_hs_norstrt(data)                                 (0x00000100&((data)<<8))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_hs_norstrt_src(data)                             ((0x00000100&(data))>>8)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_hs_norstrt(data)                             ((0x00000100&(data))>>8)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_sbyte_ackdet_shift                               (7)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_sbyte_ackdet_mask                                (0x00000080)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_sbyte_ackdet(data)                               (0x00000080&((data)<<7))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_sbyte_ackdet_src(data)                           ((0x00000080&(data))>>7)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_sbyte_ackdet(data)                           ((0x00000080&(data))>>7)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_hs_ackdet_shift                                  (6)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_hs_ackdet_mask                                   (0x00000040)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_hs_ackdet(data)                                  (0x00000040&((data)<<6))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_hs_ackdet_src(data)                              ((0x00000040&(data))>>6)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_hs_ackdet(data)                              ((0x00000040&(data))>>6)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_gcall_read_shift                                 (5)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_gcall_read_mask                                  (0x00000020)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_gcall_read(data)                                 (0x00000020&((data)<<5))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_gcall_read_src(data)                             ((0x00000020&(data))>>5)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_gcall_read(data)                             ((0x00000020&(data))>>5)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_gcall_noack_shift                                (4)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_gcall_noack_mask                                 (0x00000010)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_gcall_noack(data)                                (0x00000010&((data)<<4))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_gcall_noack_src(data)                            ((0x00000010&(data))>>4)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_gcall_noack(data)                            ((0x00000010&(data))>>4)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_txdata_noack_shift                               (3)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_txdata_noack_mask                                (0x00000008)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_txdata_noack(data)                               (0x00000008&((data)<<3))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_txdata_noack_src(data)                           ((0x00000008&(data))>>3)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_txdata_noack(data)                           ((0x00000008&(data))>>3)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10addr2_noack_shift                              (2)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10addr2_noack_mask                               (0x00000004)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10addr2_noack(data)                              (0x00000004&((data)<<2))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10addr2_noack_src(data)                          ((0x00000004&(data))>>2)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_10addr2_noack(data)                          ((0x00000004&(data))>>2)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10addr1_noack_shift                              (1)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10addr1_noack_mask                               (0x00000002)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10addr1_noack(data)                              (0x00000002&((data)<<1))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_10addr1_noack_src(data)                          ((0x00000002&(data))>>1)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_10addr1_noack(data)                          ((0x00000002&(data))>>1)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_7b_addr_noack_shift                              (0)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_7b_addr_noack_mask                               (0x00000001)
#define MIS_IC4_TX_ABRT_SOURCE_abrt_7b_addr_noack(data)                              (0x00000001&((data)<<0))
#define MIS_IC4_TX_ABRT_SOURCE_abrt_7b_addr_noack_src(data)                          ((0x00000001&(data))>>0)
#define MIS_IC4_TX_ABRT_SOURCE_get_abrt_7b_addr_noack(data)                          ((0x00000001&(data))>>0)


#define MIS_IC4_SLV_DATA_NACK_ONLY                                                   0x1801BA84
#define MIS_IC4_SLV_DATA_NACK_ONLY_reg_addr                                          "0xB801BA84"
#define MIS_IC4_SLV_DATA_NACK_ONLY_reg                                               0xB801BA84
#define set_MIS_IC4_SLV_DATA_NACK_ONLY_reg(data)   (*((volatile unsigned int*) MIS_IC4_SLV_DATA_NACK_ONLY_reg)=data)
#define get_MIS_IC4_SLV_DATA_NACK_ONLY_reg   (*((volatile unsigned int*) MIS_IC4_SLV_DATA_NACK_ONLY_reg))
#define MIS_IC4_SLV_DATA_NACK_ONLY_inst_adr                                          "0x00A1"
#define MIS_IC4_SLV_DATA_NACK_ONLY_inst                                              0x00A1
#define MIS_IC4_SLV_DATA_NACK_ONLY_nack_shift                                        (0)
#define MIS_IC4_SLV_DATA_NACK_ONLY_nack_mask                                         (0x00000001)
#define MIS_IC4_SLV_DATA_NACK_ONLY_nack(data)                                        (0x00000001&((data)<<0))
#define MIS_IC4_SLV_DATA_NACK_ONLY_nack_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC4_SLV_DATA_NACK_ONLY_get_nack(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC4_DMA_CR                                                               0x1801BA88
#define MIS_IC4_DMA_CR_reg_addr                                                      "0xB801BA88"
#define MIS_IC4_DMA_CR_reg                                                           0xB801BA88
#define set_MIS_IC4_DMA_CR_reg(data)   (*((volatile unsigned int*) MIS_IC4_DMA_CR_reg)=data)
#define get_MIS_IC4_DMA_CR_reg   (*((volatile unsigned int*) MIS_IC4_DMA_CR_reg))
#define MIS_IC4_DMA_CR_inst_adr                                                      "0x00A2"
#define MIS_IC4_DMA_CR_inst                                                          0x00A2
#define MIS_IC4_DMA_CR_tdmae_shift                                                   (1)
#define MIS_IC4_DMA_CR_tdmae_mask                                                    (0x00000002)
#define MIS_IC4_DMA_CR_tdmae(data)                                                   (0x00000002&((data)<<1))
#define MIS_IC4_DMA_CR_tdmae_src(data)                                               ((0x00000002&(data))>>1)
#define MIS_IC4_DMA_CR_get_tdmae(data)                                               ((0x00000002&(data))>>1)
#define MIS_IC4_DMA_CR_rdmae_shift                                                   (0)
#define MIS_IC4_DMA_CR_rdmae_mask                                                    (0x00000001)
#define MIS_IC4_DMA_CR_rdmae(data)                                                   (0x00000001&((data)<<0))
#define MIS_IC4_DMA_CR_rdmae_src(data)                                               ((0x00000001&(data))>>0)
#define MIS_IC4_DMA_CR_get_rdmae(data)                                               ((0x00000001&(data))>>0)


#define MIS_IC4_DMA_TDLR                                                             0x1801BA8C
#define MIS_IC4_DMA_TDLR_reg_addr                                                    "0xB801BA8C"
#define MIS_IC4_DMA_TDLR_reg                                                         0xB801BA8C
#define set_MIS_IC4_DMA_TDLR_reg(data)   (*((volatile unsigned int*) MIS_IC4_DMA_TDLR_reg)=data)
#define get_MIS_IC4_DMA_TDLR_reg   (*((volatile unsigned int*) MIS_IC4_DMA_TDLR_reg))
#define MIS_IC4_DMA_TDLR_inst_adr                                                    "0x00A3"
#define MIS_IC4_DMA_TDLR_inst                                                        0x00A3
#define MIS_IC4_DMA_TDLR_dmatdl_shift                                                (0)
#define MIS_IC4_DMA_TDLR_dmatdl_mask                                                 (0x00000007)
#define MIS_IC4_DMA_TDLR_dmatdl(data)                                                (0x00000007&((data)<<0))
#define MIS_IC4_DMA_TDLR_dmatdl_src(data)                                            ((0x00000007&(data))>>0)
#define MIS_IC4_DMA_TDLR_get_dmatdl(data)                                            ((0x00000007&(data))>>0)


#define MIS_IC4_DMA_RDLR                                                             0x1801BA90
#define MIS_IC4_DMA_RDLR_reg_addr                                                    "0xB801BA90"
#define MIS_IC4_DMA_RDLR_reg                                                         0xB801BA90
#define set_MIS_IC4_DMA_RDLR_reg(data)   (*((volatile unsigned int*) MIS_IC4_DMA_RDLR_reg)=data)
#define get_MIS_IC4_DMA_RDLR_reg   (*((volatile unsigned int*) MIS_IC4_DMA_RDLR_reg))
#define MIS_IC4_DMA_RDLR_inst_adr                                                    "0x00A4"
#define MIS_IC4_DMA_RDLR_inst                                                        0x00A4
#define MIS_IC4_DMA_RDLR_dmardl_shift                                                (0)
#define MIS_IC4_DMA_RDLR_dmardl_mask                                                 (0x0000000F)
#define MIS_IC4_DMA_RDLR_dmardl(data)                                                (0x0000000F&((data)<<0))
#define MIS_IC4_DMA_RDLR_dmardl_src(data)                                            ((0x0000000F&(data))>>0)
#define MIS_IC4_DMA_RDLR_get_dmardl(data)                                            ((0x0000000F&(data))>>0)


#define MIS_IC4_SDA_SETUP                                                            0x1801BA94
#define MIS_IC4_SDA_SETUP_reg_addr                                                   "0xB801BA94"
#define MIS_IC4_SDA_SETUP_reg                                                        0xB801BA94
#define set_MIS_IC4_SDA_SETUP_reg(data)   (*((volatile unsigned int*) MIS_IC4_SDA_SETUP_reg)=data)
#define get_MIS_IC4_SDA_SETUP_reg   (*((volatile unsigned int*) MIS_IC4_SDA_SETUP_reg))
#define MIS_IC4_SDA_SETUP_inst_adr                                                   "0x00A5"
#define MIS_IC4_SDA_SETUP_inst                                                       0x00A5
#define MIS_IC4_SDA_SETUP_sda_setup_shift                                            (0)
#define MIS_IC4_SDA_SETUP_sda_setup_mask                                             (0x000000FF)
#define MIS_IC4_SDA_SETUP_sda_setup(data)                                            (0x000000FF&((data)<<0))
#define MIS_IC4_SDA_SETUP_sda_setup_src(data)                                        ((0x000000FF&(data))>>0)
#define MIS_IC4_SDA_SETUP_get_sda_setup(data)                                        ((0x000000FF&(data))>>0)


#define MIS_IC4_ACK_GENERAL_CALL                                                     0x1801BA98
#define MIS_IC4_ACK_GENERAL_CALL_reg_addr                                            "0xB801BA98"
#define MIS_IC4_ACK_GENERAL_CALL_reg                                                 0xB801BA98
#define set_MIS_IC4_ACK_GENERAL_CALL_reg(data)   (*((volatile unsigned int*) MIS_IC4_ACK_GENERAL_CALL_reg)=data)
#define get_MIS_IC4_ACK_GENERAL_CALL_reg   (*((volatile unsigned int*) MIS_IC4_ACK_GENERAL_CALL_reg))
#define MIS_IC4_ACK_GENERAL_CALL_inst_adr                                            "0x00A6"
#define MIS_IC4_ACK_GENERAL_CALL_inst                                                0x00A6
#define MIS_IC4_ACK_GENERAL_CALL_ack_gen_call_shift                                  (0)
#define MIS_IC4_ACK_GENERAL_CALL_ack_gen_call_mask                                   (0x00000001)
#define MIS_IC4_ACK_GENERAL_CALL_ack_gen_call(data)                                  (0x00000001&((data)<<0))
#define MIS_IC4_ACK_GENERAL_CALL_ack_gen_call_src(data)                              ((0x00000001&(data))>>0)
#define MIS_IC4_ACK_GENERAL_CALL_get_ack_gen_call(data)                              ((0x00000001&(data))>>0)


#define MIS_IC4_ENABLE_STATUS                                                        0x1801BA9C
#define MIS_IC4_ENABLE_STATUS_reg_addr                                               "0xB801BA9C"
#define MIS_IC4_ENABLE_STATUS_reg                                                    0xB801BA9C
#define set_MIS_IC4_ENABLE_STATUS_reg(data)   (*((volatile unsigned int*) MIS_IC4_ENABLE_STATUS_reg)=data)
#define get_MIS_IC4_ENABLE_STATUS_reg   (*((volatile unsigned int*) MIS_IC4_ENABLE_STATUS_reg))
#define MIS_IC4_ENABLE_STATUS_inst_adr                                               "0x00A7"
#define MIS_IC4_ENABLE_STATUS_inst                                                   0x00A7
#define MIS_IC4_ENABLE_STATUS_slv_rx_data_lost_shift                                 (2)
#define MIS_IC4_ENABLE_STATUS_slv_rx_data_lost_mask                                  (0x00000004)
#define MIS_IC4_ENABLE_STATUS_slv_rx_data_lost(data)                                 (0x00000004&((data)<<2))
#define MIS_IC4_ENABLE_STATUS_slv_rx_data_lost_src(data)                             ((0x00000004&(data))>>2)
#define MIS_IC4_ENABLE_STATUS_get_slv_rx_data_lost(data)                             ((0x00000004&(data))>>2)
#define MIS_IC4_ENABLE_STATUS_slv_disabled_whi_shift                                 (1)
#define MIS_IC4_ENABLE_STATUS_slv_disabled_whi_mask                                  (0x00000002)
#define MIS_IC4_ENABLE_STATUS_slv_disabled_whi(data)                                 (0x00000002&((data)<<1))
#define MIS_IC4_ENABLE_STATUS_slv_disabled_whi_src(data)                             ((0x00000002&(data))>>1)
#define MIS_IC4_ENABLE_STATUS_get_slv_disabled_whi(data)                             ((0x00000002&(data))>>1)
#define MIS_IC4_ENABLE_STATUS_ic_en_shift                                            (0)
#define MIS_IC4_ENABLE_STATUS_ic_en_mask                                             (0x00000001)
#define MIS_IC4_ENABLE_STATUS_ic_en(data)                                            (0x00000001&((data)<<0))
#define MIS_IC4_ENABLE_STATUS_ic_en_src(data)                                        ((0x00000001&(data))>>0)
#define MIS_IC4_ENABLE_STATUS_get_ic_en(data)                                        ((0x00000001&(data))>>0)


#define MIS_IC4_COMP_PARAM_1                                                         0x1801BAF4
#define MIS_IC4_COMP_PARAM_1_reg_addr                                                "0xB801BAF4"
#define MIS_IC4_COMP_PARAM_1_reg                                                     0xB801BAF4
#define set_MIS_IC4_COMP_PARAM_1_reg(data)   (*((volatile unsigned int*) MIS_IC4_COMP_PARAM_1_reg)=data)
#define get_MIS_IC4_COMP_PARAM_1_reg   (*((volatile unsigned int*) MIS_IC4_COMP_PARAM_1_reg))
#define MIS_IC4_COMP_PARAM_1_inst_adr                                                "0x00BD"
#define MIS_IC4_COMP_PARAM_1_inst                                                    0x00BD
#define MIS_IC4_COMP_PARAM_1_tx_buffer_depth_shift                                   (16)
#define MIS_IC4_COMP_PARAM_1_tx_buffer_depth_mask                                    (0x00FF0000)
#define MIS_IC4_COMP_PARAM_1_tx_buffer_depth(data)                                   (0x00FF0000&((data)<<16))
#define MIS_IC4_COMP_PARAM_1_tx_buffer_depth_src(data)                               ((0x00FF0000&(data))>>16)
#define MIS_IC4_COMP_PARAM_1_get_tx_buffer_depth(data)                               ((0x00FF0000&(data))>>16)
#define MIS_IC4_COMP_PARAM_1_rx_buffer_depth_shift                                   (8)
#define MIS_IC4_COMP_PARAM_1_rx_buffer_depth_mask                                    (0x0000FF00)
#define MIS_IC4_COMP_PARAM_1_rx_buffer_depth(data)                                   (0x0000FF00&((data)<<8))
#define MIS_IC4_COMP_PARAM_1_rx_buffer_depth_src(data)                               ((0x0000FF00&(data))>>8)
#define MIS_IC4_COMP_PARAM_1_get_rx_buffer_depth(data)                               ((0x0000FF00&(data))>>8)
#define MIS_IC4_COMP_PARAM_1_add_encoded_params_shift                                (7)
#define MIS_IC4_COMP_PARAM_1_add_encoded_params_mask                                 (0x00000080)
#define MIS_IC4_COMP_PARAM_1_add_encoded_params(data)                                (0x00000080&((data)<<7))
#define MIS_IC4_COMP_PARAM_1_add_encoded_params_src(data)                            ((0x00000080&(data))>>7)
#define MIS_IC4_COMP_PARAM_1_get_add_encoded_params(data)                            ((0x00000080&(data))>>7)
#define MIS_IC4_COMP_PARAM_1_has_dma_shift                                           (6)
#define MIS_IC4_COMP_PARAM_1_has_dma_mask                                            (0x00000040)
#define MIS_IC4_COMP_PARAM_1_has_dma(data)                                           (0x00000040&((data)<<6))
#define MIS_IC4_COMP_PARAM_1_has_dma_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC4_COMP_PARAM_1_get_has_dma(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC4_COMP_PARAM_1_intr_io_shift                                           (5)
#define MIS_IC4_COMP_PARAM_1_intr_io_mask                                            (0x00000020)
#define MIS_IC4_COMP_PARAM_1_intr_io(data)                                           (0x00000020&((data)<<5))
#define MIS_IC4_COMP_PARAM_1_intr_io_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC4_COMP_PARAM_1_get_intr_io(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC4_COMP_PARAM_1_hc_count_values_shift                                   (4)
#define MIS_IC4_COMP_PARAM_1_hc_count_values_mask                                    (0x00000010)
#define MIS_IC4_COMP_PARAM_1_hc_count_values(data)                                   (0x00000010&((data)<<4))
#define MIS_IC4_COMP_PARAM_1_hc_count_values_src(data)                               ((0x00000010&(data))>>4)
#define MIS_IC4_COMP_PARAM_1_get_hc_count_values(data)                               ((0x00000010&(data))>>4)
#define MIS_IC4_COMP_PARAM_1_max_speed_mode_shift                                    (2)
#define MIS_IC4_COMP_PARAM_1_max_speed_mode_mask                                     (0x0000000C)
#define MIS_IC4_COMP_PARAM_1_max_speed_mode(data)                                    (0x0000000C&((data)<<2))
#define MIS_IC4_COMP_PARAM_1_max_speed_mode_src(data)                                ((0x0000000C&(data))>>2)
#define MIS_IC4_COMP_PARAM_1_get_max_speed_mode(data)                                ((0x0000000C&(data))>>2)
#define MIS_IC4_COMP_PARAM_1_apb_data_width_shift                                    (0)
#define MIS_IC4_COMP_PARAM_1_apb_data_width_mask                                     (0x00000003)
#define MIS_IC4_COMP_PARAM_1_apb_data_width(data)                                    (0x00000003&((data)<<0))
#define MIS_IC4_COMP_PARAM_1_apb_data_width_src(data)                                ((0x00000003&(data))>>0)
#define MIS_IC4_COMP_PARAM_1_get_apb_data_width(data)                                ((0x00000003&(data))>>0)


#define MIS_IC4_COMP_VERSION                                                         0x1801BAF8
#define MIS_IC4_COMP_VERSION_reg_addr                                                "0xB801BAF8"
#define MIS_IC4_COMP_VERSION_reg                                                     0xB801BAF8
#define set_MIS_IC4_COMP_VERSION_reg(data)   (*((volatile unsigned int*) MIS_IC4_COMP_VERSION_reg)=data)
#define get_MIS_IC4_COMP_VERSION_reg   (*((volatile unsigned int*) MIS_IC4_COMP_VERSION_reg))
#define MIS_IC4_COMP_VERSION_inst_adr                                                "0x00BE"
#define MIS_IC4_COMP_VERSION_inst                                                    0x00BE
#define MIS_IC4_COMP_VERSION_ic_comp_version_shift                                   (0)
#define MIS_IC4_COMP_VERSION_ic_comp_version_mask                                    (0xFFFFFFFF)
#define MIS_IC4_COMP_VERSION_ic_comp_version(data)                                   (0xFFFFFFFF&((data)<<0))
#define MIS_IC4_COMP_VERSION_ic_comp_version_src(data)                               ((0xFFFFFFFF&(data))>>0)
#define MIS_IC4_COMP_VERSION_get_ic_comp_version(data)                               ((0xFFFFFFFF&(data))>>0)


#define MIS_IC4_COMP_TYPE                                                            0x1801BAFC
#define MIS_IC4_COMP_TYPE_reg_addr                                                   "0xB801BAFC"
#define MIS_IC4_COMP_TYPE_reg                                                        0xB801BAFC
#define set_MIS_IC4_COMP_TYPE_reg(data)   (*((volatile unsigned int*) MIS_IC4_COMP_TYPE_reg)=data)
#define get_MIS_IC4_COMP_TYPE_reg   (*((volatile unsigned int*) MIS_IC4_COMP_TYPE_reg))
#define MIS_IC4_COMP_TYPE_inst_adr                                                   "0x00BF"
#define MIS_IC4_COMP_TYPE_inst                                                       0x00BF
#define MIS_IC4_COMP_TYPE_ic_comp_type_shift                                         (0)
#define MIS_IC4_COMP_TYPE_ic_comp_type_mask                                          (0xFFFFFFFF)
#define MIS_IC4_COMP_TYPE_ic_comp_type(data)                                         (0xFFFFFFFF&((data)<<0))
#define MIS_IC4_COMP_TYPE_ic_comp_type_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define MIS_IC4_COMP_TYPE_get_ic_comp_type(data)                                     ((0xFFFFFFFF&(data))>>0)


#define MIS_IC5_CON                                                                  0x1801BB00
#define MIS_IC5_CON_reg_addr                                                         "0xB801BB00"
#define MIS_IC5_CON_reg                                                              0xB801BB00
#define set_MIS_IC5_CON_reg(data)   (*((volatile unsigned int*) MIS_IC5_CON_reg)=data)
#define get_MIS_IC5_CON_reg   (*((volatile unsigned int*) MIS_IC5_CON_reg))
#define MIS_IC5_CON_inst_adr                                                         "0x00C0"
#define MIS_IC5_CON_inst                                                             0x00C0
#define MIS_IC5_CON_ic_slave_disable_shift                                           (6)
#define MIS_IC5_CON_ic_slave_disable_mask                                            (0x00000040)
#define MIS_IC5_CON_ic_slave_disable(data)                                           (0x00000040&((data)<<6))
#define MIS_IC5_CON_ic_slave_disable_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC5_CON_get_ic_slave_disable(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC5_CON_ic_restart_en_shift                                              (5)
#define MIS_IC5_CON_ic_restart_en_mask                                               (0x00000020)
#define MIS_IC5_CON_ic_restart_en(data)                                              (0x00000020&((data)<<5))
#define MIS_IC5_CON_ic_restart_en_src(data)                                          ((0x00000020&(data))>>5)
#define MIS_IC5_CON_get_ic_restart_en(data)                                          ((0x00000020&(data))>>5)
#define MIS_IC5_CON_ic_10bitaddr_master_shift                                        (4)
#define MIS_IC5_CON_ic_10bitaddr_master_mask                                         (0x00000010)
#define MIS_IC5_CON_ic_10bitaddr_master(data)                                        (0x00000010&((data)<<4))
#define MIS_IC5_CON_ic_10bitaddr_master_src(data)                                    ((0x00000010&(data))>>4)
#define MIS_IC5_CON_get_ic_10bitaddr_master(data)                                    ((0x00000010&(data))>>4)
#define MIS_IC5_CON_ic_10bitaddr_slave_shift                                         (3)
#define MIS_IC5_CON_ic_10bitaddr_slave_mask                                          (0x00000008)
#define MIS_IC5_CON_ic_10bitaddr_slave(data)                                         (0x00000008&((data)<<3))
#define MIS_IC5_CON_ic_10bitaddr_slave_src(data)                                     ((0x00000008&(data))>>3)
#define MIS_IC5_CON_get_ic_10bitaddr_slave(data)                                     ((0x00000008&(data))>>3)
#define MIS_IC5_CON_speed_shift                                                      (1)
#define MIS_IC5_CON_speed_mask                                                       (0x00000006)
#define MIS_IC5_CON_speed(data)                                                      (0x00000006&((data)<<1))
#define MIS_IC5_CON_speed_src(data)                                                  ((0x00000006&(data))>>1)
#define MIS_IC5_CON_get_speed(data)                                                  ((0x00000006&(data))>>1)
#define MIS_IC5_CON_master_mode_shift                                                (0)
#define MIS_IC5_CON_master_mode_mask                                                 (0x00000001)
#define MIS_IC5_CON_master_mode(data)                                                (0x00000001&((data)<<0))
#define MIS_IC5_CON_master_mode_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_IC5_CON_get_master_mode(data)                                            ((0x00000001&(data))>>0)


#define MIS_IC5_TAR                                                                  0x1801BB04
#define MIS_IC5_TAR_reg_addr                                                         "0xB801BB04"
#define MIS_IC5_TAR_reg                                                              0xB801BB04
#define set_MIS_IC5_TAR_reg(data)   (*((volatile unsigned int*) MIS_IC5_TAR_reg)=data)
#define get_MIS_IC5_TAR_reg   (*((volatile unsigned int*) MIS_IC5_TAR_reg))
#define MIS_IC5_TAR_inst_adr                                                         "0x00C1"
#define MIS_IC5_TAR_inst                                                             0x00C1
#define MIS_IC5_TAR_ic_10bitaddr_master_shift                                        (12)
#define MIS_IC5_TAR_ic_10bitaddr_master_mask                                         (0x00001000)
#define MIS_IC5_TAR_ic_10bitaddr_master(data)                                        (0x00001000&((data)<<12))
#define MIS_IC5_TAR_ic_10bitaddr_master_src(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC5_TAR_get_ic_10bitaddr_master(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC5_TAR_special_shift                                                    (11)
#define MIS_IC5_TAR_special_mask                                                     (0x00000800)
#define MIS_IC5_TAR_special(data)                                                    (0x00000800&((data)<<11))
#define MIS_IC5_TAR_special_src(data)                                                ((0x00000800&(data))>>11)
#define MIS_IC5_TAR_get_special(data)                                                ((0x00000800&(data))>>11)
#define MIS_IC5_TAR_gc_or_start_shift                                                (10)
#define MIS_IC5_TAR_gc_or_start_mask                                                 (0x00000400)
#define MIS_IC5_TAR_gc_or_start(data)                                                (0x00000400&((data)<<10))
#define MIS_IC5_TAR_gc_or_start_src(data)                                            ((0x00000400&(data))>>10)
#define MIS_IC5_TAR_get_gc_or_start(data)                                            ((0x00000400&(data))>>10)
#define MIS_IC5_TAR_ic_tar_shift                                                     (0)
#define MIS_IC5_TAR_ic_tar_mask                                                      (0x000003FF)
#define MIS_IC5_TAR_ic_tar(data)                                                     (0x000003FF&((data)<<0))
#define MIS_IC5_TAR_ic_tar_src(data)                                                 ((0x000003FF&(data))>>0)
#define MIS_IC5_TAR_get_ic_tar(data)                                                 ((0x000003FF&(data))>>0)


#define MIS_IC5_SAR                                                                  0x1801BB08
#define MIS_IC5_SAR_reg_addr                                                         "0xB801BB08"
#define MIS_IC5_SAR_reg                                                              0xB801BB08
#define set_MIS_IC5_SAR_reg(data)   (*((volatile unsigned int*) MIS_IC5_SAR_reg)=data)
#define get_MIS_IC5_SAR_reg   (*((volatile unsigned int*) MIS_IC5_SAR_reg))
#define MIS_IC5_SAR_inst_adr                                                         "0x00C2"
#define MIS_IC5_SAR_inst                                                             0x00C2
#define MIS_IC5_SAR_ic_sar_shift                                                     (0)
#define MIS_IC5_SAR_ic_sar_mask                                                      (0x000003FF)
#define MIS_IC5_SAR_ic_sar(data)                                                     (0x000003FF&((data)<<0))
#define MIS_IC5_SAR_ic_sar_src(data)                                                 ((0x000003FF&(data))>>0)
#define MIS_IC5_SAR_get_ic_sar(data)                                                 ((0x000003FF&(data))>>0)


#define MIS_IC5_HS_MADDR                                                             0x1801BB0C
#define MIS_IC5_HS_MADDR_reg_addr                                                    "0xB801BB0C"
#define MIS_IC5_HS_MADDR_reg                                                         0xB801BB0C
#define set_MIS_IC5_HS_MADDR_reg(data)   (*((volatile unsigned int*) MIS_IC5_HS_MADDR_reg)=data)
#define get_MIS_IC5_HS_MADDR_reg   (*((volatile unsigned int*) MIS_IC5_HS_MADDR_reg))
#define MIS_IC5_HS_MADDR_inst_adr                                                    "0x00C3"
#define MIS_IC5_HS_MADDR_inst                                                        0x00C3
#define MIS_IC5_HS_MADDR_ic_hs_mar_shift                                             (0)
#define MIS_IC5_HS_MADDR_ic_hs_mar_mask                                              (0x00000007)
#define MIS_IC5_HS_MADDR_ic_hs_mar(data)                                             (0x00000007&((data)<<0))
#define MIS_IC5_HS_MADDR_ic_hs_mar_src(data)                                         ((0x00000007&(data))>>0)
#define MIS_IC5_HS_MADDR_get_ic_hs_mar(data)                                         ((0x00000007&(data))>>0)


#define MIS_IC5_DATA_CMD                                                             0x1801BB10
#define MIS_IC5_DATA_CMD_reg_addr                                                    "0xB801BB10"
#define MIS_IC5_DATA_CMD_reg                                                         0xB801BB10
#define set_MIS_IC5_DATA_CMD_reg(data)   (*((volatile unsigned int*) MIS_IC5_DATA_CMD_reg)=data)
#define get_MIS_IC5_DATA_CMD_reg   (*((volatile unsigned int*) MIS_IC5_DATA_CMD_reg))
#define MIS_IC5_DATA_CMD_inst_adr                                                    "0x00C4"
#define MIS_IC5_DATA_CMD_inst                                                        0x00C4
#define MIS_IC5_DATA_CMD_restart_shift                                               (10)
#define MIS_IC5_DATA_CMD_restart_mask                                                (0x00000400)
#define MIS_IC5_DATA_CMD_restart(data)                                               (0x00000400&((data)<<10))
#define MIS_IC5_DATA_CMD_restart_src(data)                                           ((0x00000400&(data))>>10)
#define MIS_IC5_DATA_CMD_get_restart(data)                                           ((0x00000400&(data))>>10)
#define MIS_IC5_DATA_CMD_stop_shift                                                  (9)
#define MIS_IC5_DATA_CMD_stop_mask                                                   (0x00000200)
#define MIS_IC5_DATA_CMD_stop(data)                                                  (0x00000200&((data)<<9))
#define MIS_IC5_DATA_CMD_stop_src(data)                                              ((0x00000200&(data))>>9)
#define MIS_IC5_DATA_CMD_get_stop(data)                                              ((0x00000200&(data))>>9)
#define MIS_IC5_DATA_CMD_cmd_shift                                                   (8)
#define MIS_IC5_DATA_CMD_cmd_mask                                                    (0x00000100)
#define MIS_IC5_DATA_CMD_cmd(data)                                                   (0x00000100&((data)<<8))
#define MIS_IC5_DATA_CMD_cmd_src(data)                                               ((0x00000100&(data))>>8)
#define MIS_IC5_DATA_CMD_get_cmd(data)                                               ((0x00000100&(data))>>8)
#define MIS_IC5_DATA_CMD_dat_shift                                                   (0)
#define MIS_IC5_DATA_CMD_dat_mask                                                    (0x000000FF)
#define MIS_IC5_DATA_CMD_dat(data)                                                   (0x000000FF&((data)<<0))
#define MIS_IC5_DATA_CMD_dat_src(data)                                               ((0x000000FF&(data))>>0)
#define MIS_IC5_DATA_CMD_get_dat(data)                                               ((0x000000FF&(data))>>0)


#define MIS_IC5_SS_SCL_HCNT                                                          0x1801BB14
#define MIS_IC5_SS_SCL_HCNT_reg_addr                                                 "0xB801BB14"
#define MIS_IC5_SS_SCL_HCNT_reg                                                      0xB801BB14
#define set_MIS_IC5_SS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) MIS_IC5_SS_SCL_HCNT_reg)=data)
#define get_MIS_IC5_SS_SCL_HCNT_reg   (*((volatile unsigned int*) MIS_IC5_SS_SCL_HCNT_reg))
#define MIS_IC5_SS_SCL_HCNT_inst_adr                                                 "0x00C5"
#define MIS_IC5_SS_SCL_HCNT_inst                                                     0x00C5
#define MIS_IC5_SS_SCL_HCNT_ic_ss_scl_hcnt_shift                                     (0)
#define MIS_IC5_SS_SCL_HCNT_ic_ss_scl_hcnt_mask                                      (0x0000FFFF)
#define MIS_IC5_SS_SCL_HCNT_ic_ss_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC5_SS_SCL_HCNT_ic_ss_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC5_SS_SCL_HCNT_get_ic_ss_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC5_SS_SCL_LCNT                                                          0x1801BB18
#define MIS_IC5_SS_SCL_LCNT_reg_addr                                                 "0xB801BB18"
#define MIS_IC5_SS_SCL_LCNT_reg                                                      0xB801BB18
#define set_MIS_IC5_SS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) MIS_IC5_SS_SCL_LCNT_reg)=data)
#define get_MIS_IC5_SS_SCL_LCNT_reg   (*((volatile unsigned int*) MIS_IC5_SS_SCL_LCNT_reg))
#define MIS_IC5_SS_SCL_LCNT_inst_adr                                                 "0x00C6"
#define MIS_IC5_SS_SCL_LCNT_inst                                                     0x00C6
#define MIS_IC5_SS_SCL_LCNT_ic_ss_scl_lcnt_shift                                     (0)
#define MIS_IC5_SS_SCL_LCNT_ic_ss_scl_lcnt_mask                                      (0x0000FFFF)
#define MIS_IC5_SS_SCL_LCNT_ic_ss_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC5_SS_SCL_LCNT_ic_ss_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC5_SS_SCL_LCNT_get_ic_ss_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC5_FS_SCL_HCNT                                                          0x1801BB1C
#define MIS_IC5_FS_SCL_HCNT_reg_addr                                                 "0xB801BB1C"
#define MIS_IC5_FS_SCL_HCNT_reg                                                      0xB801BB1C
#define set_MIS_IC5_FS_SCL_HCNT_reg(data)   (*((volatile unsigned int*) MIS_IC5_FS_SCL_HCNT_reg)=data)
#define get_MIS_IC5_FS_SCL_HCNT_reg   (*((volatile unsigned int*) MIS_IC5_FS_SCL_HCNT_reg))
#define MIS_IC5_FS_SCL_HCNT_inst_adr                                                 "0x00C7"
#define MIS_IC5_FS_SCL_HCNT_inst                                                     0x00C7
#define MIS_IC5_FS_SCL_HCNT_ic_fs_scl_hcnt_shift                                     (0)
#define MIS_IC5_FS_SCL_HCNT_ic_fs_scl_hcnt_mask                                      (0x0000FFFF)
#define MIS_IC5_FS_SCL_HCNT_ic_fs_scl_hcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC5_FS_SCL_HCNT_ic_fs_scl_hcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC5_FS_SCL_HCNT_get_ic_fs_scl_hcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC5_FS_SCL_LCNT                                                          0x1801BB20
#define MIS_IC5_FS_SCL_LCNT_reg_addr                                                 "0xB801BB20"
#define MIS_IC5_FS_SCL_LCNT_reg                                                      0xB801BB20
#define set_MIS_IC5_FS_SCL_LCNT_reg(data)   (*((volatile unsigned int*) MIS_IC5_FS_SCL_LCNT_reg)=data)
#define get_MIS_IC5_FS_SCL_LCNT_reg   (*((volatile unsigned int*) MIS_IC5_FS_SCL_LCNT_reg))
#define MIS_IC5_FS_SCL_LCNT_inst_adr                                                 "0x00C8"
#define MIS_IC5_FS_SCL_LCNT_inst                                                     0x00C8
#define MIS_IC5_FS_SCL_LCNT_ic_fs_scl_lcnt_shift                                     (0)
#define MIS_IC5_FS_SCL_LCNT_ic_fs_scl_lcnt_mask                                      (0x0000FFFF)
#define MIS_IC5_FS_SCL_LCNT_ic_fs_scl_lcnt(data)                                     (0x0000FFFF&((data)<<0))
#define MIS_IC5_FS_SCL_LCNT_ic_fs_scl_lcnt_src(data)                                 ((0x0000FFFF&(data))>>0)
#define MIS_IC5_FS_SCL_LCNT_get_ic_fs_scl_lcnt(data)                                 ((0x0000FFFF&(data))>>0)


#define MIS_IC5_INTR_STAT                                                            0x1801BB2C
#define MIS_IC5_INTR_STAT_reg_addr                                                   "0xB801BB2C"
#define MIS_IC5_INTR_STAT_reg                                                        0xB801BB2C
#define set_MIS_IC5_INTR_STAT_reg(data)   (*((volatile unsigned int*) MIS_IC5_INTR_STAT_reg)=data)
#define get_MIS_IC5_INTR_STAT_reg   (*((volatile unsigned int*) MIS_IC5_INTR_STAT_reg))
#define MIS_IC5_INTR_STAT_inst_adr                                                   "0x00CB"
#define MIS_IC5_INTR_STAT_inst                                                       0x00CB
#define MIS_IC5_INTR_STAT_r_gen_call_shift                                           (11)
#define MIS_IC5_INTR_STAT_r_gen_call_mask                                            (0x00000800)
#define MIS_IC5_INTR_STAT_r_gen_call(data)                                           (0x00000800&((data)<<11))
#define MIS_IC5_INTR_STAT_r_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC5_INTR_STAT_get_r_gen_call(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC5_INTR_STAT_r_start_det_shift                                          (10)
#define MIS_IC5_INTR_STAT_r_start_det_mask                                           (0x00000400)
#define MIS_IC5_INTR_STAT_r_start_det(data)                                          (0x00000400&((data)<<10))
#define MIS_IC5_INTR_STAT_r_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC5_INTR_STAT_get_r_start_det(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC5_INTR_STAT_r_stop_det_shift                                           (9)
#define MIS_IC5_INTR_STAT_r_stop_det_mask                                            (0x00000200)
#define MIS_IC5_INTR_STAT_r_stop_det(data)                                           (0x00000200&((data)<<9))
#define MIS_IC5_INTR_STAT_r_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC5_INTR_STAT_get_r_stop_det(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC5_INTR_STAT_r_activity_shift                                           (8)
#define MIS_IC5_INTR_STAT_r_activity_mask                                            (0x00000100)
#define MIS_IC5_INTR_STAT_r_activity(data)                                           (0x00000100&((data)<<8))
#define MIS_IC5_INTR_STAT_r_activity_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC5_INTR_STAT_get_r_activity(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC5_INTR_STAT_r_rx_done_shift                                            (7)
#define MIS_IC5_INTR_STAT_r_rx_done_mask                                             (0x00000080)
#define MIS_IC5_INTR_STAT_r_rx_done(data)                                            (0x00000080&((data)<<7))
#define MIS_IC5_INTR_STAT_r_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC5_INTR_STAT_get_r_rx_done(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC5_INTR_STAT_r_tx_abrt_shift                                            (6)
#define MIS_IC5_INTR_STAT_r_tx_abrt_mask                                             (0x00000040)
#define MIS_IC5_INTR_STAT_r_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define MIS_IC5_INTR_STAT_r_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC5_INTR_STAT_get_r_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC5_INTR_STAT_r_rd_req_shift                                             (5)
#define MIS_IC5_INTR_STAT_r_rd_req_mask                                              (0x00000020)
#define MIS_IC5_INTR_STAT_r_rd_req(data)                                             (0x00000020&((data)<<5))
#define MIS_IC5_INTR_STAT_r_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC5_INTR_STAT_get_r_rd_req(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC5_INTR_STAT_r_tx_empty_shift                                           (4)
#define MIS_IC5_INTR_STAT_r_tx_empty_mask                                            (0x00000010)
#define MIS_IC5_INTR_STAT_r_tx_empty(data)                                           (0x00000010&((data)<<4))
#define MIS_IC5_INTR_STAT_r_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC5_INTR_STAT_get_r_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC5_INTR_STAT_r_tx_over_shift                                            (3)
#define MIS_IC5_INTR_STAT_r_tx_over_mask                                             (0x00000008)
#define MIS_IC5_INTR_STAT_r_tx_over(data)                                            (0x00000008&((data)<<3))
#define MIS_IC5_INTR_STAT_r_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC5_INTR_STAT_get_r_tx_over(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC5_INTR_STAT_r_rx_full_shift                                            (2)
#define MIS_IC5_INTR_STAT_r_rx_full_mask                                             (0x00000004)
#define MIS_IC5_INTR_STAT_r_rx_full(data)                                            (0x00000004&((data)<<2))
#define MIS_IC5_INTR_STAT_r_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC5_INTR_STAT_get_r_rx_full(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC5_INTR_STAT_r_rx_over_shift                                            (1)
#define MIS_IC5_INTR_STAT_r_rx_over_mask                                             (0x00000002)
#define MIS_IC5_INTR_STAT_r_rx_over(data)                                            (0x00000002&((data)<<1))
#define MIS_IC5_INTR_STAT_r_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC5_INTR_STAT_get_r_rx_over(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC5_INTR_STAT_r_rx_under_shift                                           (0)
#define MIS_IC5_INTR_STAT_r_rx_under_mask                                            (0x00000001)
#define MIS_IC5_INTR_STAT_r_rx_under(data)                                           (0x00000001&((data)<<0))
#define MIS_IC5_INTR_STAT_r_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_IC5_INTR_STAT_get_r_rx_under(data)                                       ((0x00000001&(data))>>0)


#define MIS_IC5_INTR_MASK                                                            0x1801BB30
#define MIS_IC5_INTR_MASK_reg_addr                                                   "0xB801BB30"
#define MIS_IC5_INTR_MASK_reg                                                        0xB801BB30
#define set_MIS_IC5_INTR_MASK_reg(data)   (*((volatile unsigned int*) MIS_IC5_INTR_MASK_reg)=data)
#define get_MIS_IC5_INTR_MASK_reg   (*((volatile unsigned int*) MIS_IC5_INTR_MASK_reg))
#define MIS_IC5_INTR_MASK_inst_adr                                                   "0x00CC"
#define MIS_IC5_INTR_MASK_inst                                                       0x00CC
#define MIS_IC5_INTR_MASK_m_gen_call_shift                                           (11)
#define MIS_IC5_INTR_MASK_m_gen_call_mask                                            (0x00000800)
#define MIS_IC5_INTR_MASK_m_gen_call(data)                                           (0x00000800&((data)<<11))
#define MIS_IC5_INTR_MASK_m_gen_call_src(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC5_INTR_MASK_get_m_gen_call(data)                                       ((0x00000800&(data))>>11)
#define MIS_IC5_INTR_MASK_m_start_det_shift                                          (10)
#define MIS_IC5_INTR_MASK_m_start_det_mask                                           (0x00000400)
#define MIS_IC5_INTR_MASK_m_start_det(data)                                          (0x00000400&((data)<<10))
#define MIS_IC5_INTR_MASK_m_start_det_src(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC5_INTR_MASK_get_m_start_det(data)                                      ((0x00000400&(data))>>10)
#define MIS_IC5_INTR_MASK_m_stop_det_shift                                           (9)
#define MIS_IC5_INTR_MASK_m_stop_det_mask                                            (0x00000200)
#define MIS_IC5_INTR_MASK_m_stop_det(data)                                           (0x00000200&((data)<<9))
#define MIS_IC5_INTR_MASK_m_stop_det_src(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC5_INTR_MASK_get_m_stop_det(data)                                       ((0x00000200&(data))>>9)
#define MIS_IC5_INTR_MASK_m_activity_shift                                           (8)
#define MIS_IC5_INTR_MASK_m_activity_mask                                            (0x00000100)
#define MIS_IC5_INTR_MASK_m_activity(data)                                           (0x00000100&((data)<<8))
#define MIS_IC5_INTR_MASK_m_activity_src(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC5_INTR_MASK_get_m_activity(data)                                       ((0x00000100&(data))>>8)
#define MIS_IC5_INTR_MASK_m_rx_done_shift                                            (7)
#define MIS_IC5_INTR_MASK_m_rx_done_mask                                             (0x00000080)
#define MIS_IC5_INTR_MASK_m_rx_done(data)                                            (0x00000080&((data)<<7))
#define MIS_IC5_INTR_MASK_m_rx_done_src(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC5_INTR_MASK_get_m_rx_done(data)                                        ((0x00000080&(data))>>7)
#define MIS_IC5_INTR_MASK_m_tx_abrt_shift                                            (6)
#define MIS_IC5_INTR_MASK_m_tx_abrt_mask                                             (0x00000040)
#define MIS_IC5_INTR_MASK_m_tx_abrt(data)                                            (0x00000040&((data)<<6))
#define MIS_IC5_INTR_MASK_m_tx_abrt_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC5_INTR_MASK_get_m_tx_abrt(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC5_INTR_MASK_m_rd_req_shift                                             (5)
#define MIS_IC5_INTR_MASK_m_rd_req_mask                                              (0x00000020)
#define MIS_IC5_INTR_MASK_m_rd_req(data)                                             (0x00000020&((data)<<5))
#define MIS_IC5_INTR_MASK_m_rd_req_src(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC5_INTR_MASK_get_m_rd_req(data)                                         ((0x00000020&(data))>>5)
#define MIS_IC5_INTR_MASK_m_tx_empty_shift                                           (4)
#define MIS_IC5_INTR_MASK_m_tx_empty_mask                                            (0x00000010)
#define MIS_IC5_INTR_MASK_m_tx_empty(data)                                           (0x00000010&((data)<<4))
#define MIS_IC5_INTR_MASK_m_tx_empty_src(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC5_INTR_MASK_get_m_tx_empty(data)                                       ((0x00000010&(data))>>4)
#define MIS_IC5_INTR_MASK_m_tx_over_shift                                            (3)
#define MIS_IC5_INTR_MASK_m_tx_over_mask                                             (0x00000008)
#define MIS_IC5_INTR_MASK_m_tx_over(data)                                            (0x00000008&((data)<<3))
#define MIS_IC5_INTR_MASK_m_tx_over_src(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC5_INTR_MASK_get_m_tx_over(data)                                        ((0x00000008&(data))>>3)
#define MIS_IC5_INTR_MASK_m_rx_full_shift                                            (2)
#define MIS_IC5_INTR_MASK_m_rx_full_mask                                             (0x00000004)
#define MIS_IC5_INTR_MASK_m_rx_full(data)                                            (0x00000004&((data)<<2))
#define MIS_IC5_INTR_MASK_m_rx_full_src(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC5_INTR_MASK_get_m_rx_full(data)                                        ((0x00000004&(data))>>2)
#define MIS_IC5_INTR_MASK_m_rx_over_shift                                            (1)
#define MIS_IC5_INTR_MASK_m_rx_over_mask                                             (0x00000002)
#define MIS_IC5_INTR_MASK_m_rx_over(data)                                            (0x00000002&((data)<<1))
#define MIS_IC5_INTR_MASK_m_rx_over_src(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC5_INTR_MASK_get_m_rx_over(data)                                        ((0x00000002&(data))>>1)
#define MIS_IC5_INTR_MASK_m_rx_under_shift                                           (0)
#define MIS_IC5_INTR_MASK_m_rx_under_mask                                            (0x00000001)
#define MIS_IC5_INTR_MASK_m_rx_under(data)                                           (0x00000001&((data)<<0))
#define MIS_IC5_INTR_MASK_m_rx_under_src(data)                                       ((0x00000001&(data))>>0)
#define MIS_IC5_INTR_MASK_get_m_rx_under(data)                                       ((0x00000001&(data))>>0)


#define MIS_IC5_RAW_INTR_STAT                                                        0x1801BB34
#define MIS_IC5_RAW_INTR_STAT_reg_addr                                               "0xB801BB34"
#define MIS_IC5_RAW_INTR_STAT_reg                                                    0xB801BB34
#define set_MIS_IC5_RAW_INTR_STAT_reg(data)   (*((volatile unsigned int*) MIS_IC5_RAW_INTR_STAT_reg)=data)
#define get_MIS_IC5_RAW_INTR_STAT_reg   (*((volatile unsigned int*) MIS_IC5_RAW_INTR_STAT_reg))
#define MIS_IC5_RAW_INTR_STAT_inst_adr                                               "0x00CD"
#define MIS_IC5_RAW_INTR_STAT_inst                                                   0x00CD
#define MIS_IC5_RAW_INTR_STAT_gen_call_shift                                         (11)
#define MIS_IC5_RAW_INTR_STAT_gen_call_mask                                          (0x00000800)
#define MIS_IC5_RAW_INTR_STAT_gen_call(data)                                         (0x00000800&((data)<<11))
#define MIS_IC5_RAW_INTR_STAT_gen_call_src(data)                                     ((0x00000800&(data))>>11)
#define MIS_IC5_RAW_INTR_STAT_get_gen_call(data)                                     ((0x00000800&(data))>>11)
#define MIS_IC5_RAW_INTR_STAT_start_det_shift                                        (10)
#define MIS_IC5_RAW_INTR_STAT_start_det_mask                                         (0x00000400)
#define MIS_IC5_RAW_INTR_STAT_start_det(data)                                        (0x00000400&((data)<<10))
#define MIS_IC5_RAW_INTR_STAT_start_det_src(data)                                    ((0x00000400&(data))>>10)
#define MIS_IC5_RAW_INTR_STAT_get_start_det(data)                                    ((0x00000400&(data))>>10)
#define MIS_IC5_RAW_INTR_STAT_stop_det_shift                                         (9)
#define MIS_IC5_RAW_INTR_STAT_stop_det_mask                                          (0x00000200)
#define MIS_IC5_RAW_INTR_STAT_stop_det(data)                                         (0x00000200&((data)<<9))
#define MIS_IC5_RAW_INTR_STAT_stop_det_src(data)                                     ((0x00000200&(data))>>9)
#define MIS_IC5_RAW_INTR_STAT_get_stop_det(data)                                     ((0x00000200&(data))>>9)
#define MIS_IC5_RAW_INTR_STAT_activity_shift                                         (8)
#define MIS_IC5_RAW_INTR_STAT_activity_mask                                          (0x00000100)
#define MIS_IC5_RAW_INTR_STAT_activity(data)                                         (0x00000100&((data)<<8))
#define MIS_IC5_RAW_INTR_STAT_activity_src(data)                                     ((0x00000100&(data))>>8)
#define MIS_IC5_RAW_INTR_STAT_get_activity(data)                                     ((0x00000100&(data))>>8)
#define MIS_IC5_RAW_INTR_STAT_rx_done_shift                                          (7)
#define MIS_IC5_RAW_INTR_STAT_rx_done_mask                                           (0x00000080)
#define MIS_IC5_RAW_INTR_STAT_rx_done(data)                                          (0x00000080&((data)<<7))
#define MIS_IC5_RAW_INTR_STAT_rx_done_src(data)                                      ((0x00000080&(data))>>7)
#define MIS_IC5_RAW_INTR_STAT_get_rx_done(data)                                      ((0x00000080&(data))>>7)
#define MIS_IC5_RAW_INTR_STAT_tx_abrt_shift                                          (6)
#define MIS_IC5_RAW_INTR_STAT_tx_abrt_mask                                           (0x00000040)
#define MIS_IC5_RAW_INTR_STAT_tx_abrt(data)                                          (0x00000040&((data)<<6))
#define MIS_IC5_RAW_INTR_STAT_tx_abrt_src(data)                                      ((0x00000040&(data))>>6)
#define MIS_IC5_RAW_INTR_STAT_get_tx_abrt(data)                                      ((0x00000040&(data))>>6)
#define MIS_IC5_RAW_INTR_STAT_rd_req_shift                                           (5)
#define MIS_IC5_RAW_INTR_STAT_rd_req_mask                                            (0x00000020)
#define MIS_IC5_RAW_INTR_STAT_rd_req(data)                                           (0x00000020&((data)<<5))
#define MIS_IC5_RAW_INTR_STAT_rd_req_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC5_RAW_INTR_STAT_get_rd_req(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC5_RAW_INTR_STAT_tx_empty_shift                                         (4)
#define MIS_IC5_RAW_INTR_STAT_tx_empty_mask                                          (0x00000010)
#define MIS_IC5_RAW_INTR_STAT_tx_empty(data)                                         (0x00000010&((data)<<4))
#define MIS_IC5_RAW_INTR_STAT_tx_empty_src(data)                                     ((0x00000010&(data))>>4)
#define MIS_IC5_RAW_INTR_STAT_get_tx_empty(data)                                     ((0x00000010&(data))>>4)
#define MIS_IC5_RAW_INTR_STAT_tx_over_shift                                          (3)
#define MIS_IC5_RAW_INTR_STAT_tx_over_mask                                           (0x00000008)
#define MIS_IC5_RAW_INTR_STAT_tx_over(data)                                          (0x00000008&((data)<<3))
#define MIS_IC5_RAW_INTR_STAT_tx_over_src(data)                                      ((0x00000008&(data))>>3)
#define MIS_IC5_RAW_INTR_STAT_get_tx_over(data)                                      ((0x00000008&(data))>>3)
#define MIS_IC5_RAW_INTR_STAT_rx_full_shift                                          (2)
#define MIS_IC5_RAW_INTR_STAT_rx_full_mask                                           (0x00000004)
#define MIS_IC5_RAW_INTR_STAT_rx_full(data)                                          (0x00000004&((data)<<2))
#define MIS_IC5_RAW_INTR_STAT_rx_full_src(data)                                      ((0x00000004&(data))>>2)
#define MIS_IC5_RAW_INTR_STAT_get_rx_full(data)                                      ((0x00000004&(data))>>2)
#define MIS_IC5_RAW_INTR_STAT_rx_over_shift                                          (1)
#define MIS_IC5_RAW_INTR_STAT_rx_over_mask                                           (0x00000002)
#define MIS_IC5_RAW_INTR_STAT_rx_over(data)                                          (0x00000002&((data)<<1))
#define MIS_IC5_RAW_INTR_STAT_rx_over_src(data)                                      ((0x00000002&(data))>>1)
#define MIS_IC5_RAW_INTR_STAT_get_rx_over(data)                                      ((0x00000002&(data))>>1)
#define MIS_IC5_RAW_INTR_STAT_rx_under_shift                                         (0)
#define MIS_IC5_RAW_INTR_STAT_rx_under_mask                                          (0x00000001)
#define MIS_IC5_RAW_INTR_STAT_rx_under(data)                                         (0x00000001&((data)<<0))
#define MIS_IC5_RAW_INTR_STAT_rx_under_src(data)                                     ((0x00000001&(data))>>0)
#define MIS_IC5_RAW_INTR_STAT_get_rx_under(data)                                     ((0x00000001&(data))>>0)


#define MIS_IC5_RX_TL                                                                0x1801BB38
#define MIS_IC5_RX_TL_reg_addr                                                       "0xB801BB38"
#define MIS_IC5_RX_TL_reg                                                            0xB801BB38
#define set_MIS_IC5_RX_TL_reg(data)   (*((volatile unsigned int*) MIS_IC5_RX_TL_reg)=data)
#define get_MIS_IC5_RX_TL_reg   (*((volatile unsigned int*) MIS_IC5_RX_TL_reg))
#define MIS_IC5_RX_TL_inst_adr                                                       "0x00CE"
#define MIS_IC5_RX_TL_inst                                                           0x00CE
#define MIS_IC5_RX_TL_rx_tl_shift                                                    (0)
#define MIS_IC5_RX_TL_rx_tl_mask                                                     (0x000000FF)
#define MIS_IC5_RX_TL_rx_tl(data)                                                    (0x000000FF&((data)<<0))
#define MIS_IC5_RX_TL_rx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define MIS_IC5_RX_TL_get_rx_tl(data)                                                ((0x000000FF&(data))>>0)


#define MIS_IC5_TX_TL                                                                0x1801BB3C
#define MIS_IC5_TX_TL_reg_addr                                                       "0xB801BB3C"
#define MIS_IC5_TX_TL_reg                                                            0xB801BB3C
#define set_MIS_IC5_TX_TL_reg(data)   (*((volatile unsigned int*) MIS_IC5_TX_TL_reg)=data)
#define get_MIS_IC5_TX_TL_reg   (*((volatile unsigned int*) MIS_IC5_TX_TL_reg))
#define MIS_IC5_TX_TL_inst_adr                                                       "0x00CF"
#define MIS_IC5_TX_TL_inst                                                           0x00CF
#define MIS_IC5_TX_TL_tx_tl_shift                                                    (0)
#define MIS_IC5_TX_TL_tx_tl_mask                                                     (0x000000FF)
#define MIS_IC5_TX_TL_tx_tl(data)                                                    (0x000000FF&((data)<<0))
#define MIS_IC5_TX_TL_tx_tl_src(data)                                                ((0x000000FF&(data))>>0)
#define MIS_IC5_TX_TL_get_tx_tl(data)                                                ((0x000000FF&(data))>>0)


#define MIS_IC5_CLR_INTR                                                             0x1801BB40
#define MIS_IC5_CLR_INTR_reg_addr                                                    "0xB801BB40"
#define MIS_IC5_CLR_INTR_reg                                                         0xB801BB40
#define set_MIS_IC5_CLR_INTR_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_INTR_reg)=data)
#define get_MIS_IC5_CLR_INTR_reg   (*((volatile unsigned int*) MIS_IC5_CLR_INTR_reg))
#define MIS_IC5_CLR_INTR_inst_adr                                                    "0x00D0"
#define MIS_IC5_CLR_INTR_inst                                                        0x00D0
#define MIS_IC5_CLR_INTR_clr_intr_shift                                              (0)
#define MIS_IC5_CLR_INTR_clr_intr_mask                                               (0x00000001)
#define MIS_IC5_CLR_INTR_clr_intr(data)                                              (0x00000001&((data)<<0))
#define MIS_IC5_CLR_INTR_clr_intr_src(data)                                          ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_INTR_get_clr_intr(data)                                          ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_RX_UNDER                                                         0x1801BB44
#define MIS_IC5_CLR_RX_UNDER_reg_addr                                                "0xB801BB44"
#define MIS_IC5_CLR_RX_UNDER_reg                                                     0xB801BB44
#define set_MIS_IC5_CLR_RX_UNDER_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_RX_UNDER_reg)=data)
#define get_MIS_IC5_CLR_RX_UNDER_reg   (*((volatile unsigned int*) MIS_IC5_CLR_RX_UNDER_reg))
#define MIS_IC5_CLR_RX_UNDER_inst_adr                                                "0x00D1"
#define MIS_IC5_CLR_RX_UNDER_inst                                                    0x00D1
#define MIS_IC5_CLR_RX_UNDER_clr_rx_under_shift                                      (0)
#define MIS_IC5_CLR_RX_UNDER_clr_rx_under_mask                                       (0x00000001)
#define MIS_IC5_CLR_RX_UNDER_clr_rx_under(data)                                      (0x00000001&((data)<<0))
#define MIS_IC5_CLR_RX_UNDER_clr_rx_under_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_RX_UNDER_get_clr_rx_under(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_RX_OVER                                                          0x1801BB48
#define MIS_IC5_CLR_RX_OVER_reg_addr                                                 "0xB801BB48"
#define MIS_IC5_CLR_RX_OVER_reg                                                      0xB801BB48
#define set_MIS_IC5_CLR_RX_OVER_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_RX_OVER_reg)=data)
#define get_MIS_IC5_CLR_RX_OVER_reg   (*((volatile unsigned int*) MIS_IC5_CLR_RX_OVER_reg))
#define MIS_IC5_CLR_RX_OVER_inst_adr                                                 "0x00D2"
#define MIS_IC5_CLR_RX_OVER_inst                                                     0x00D2
#define MIS_IC5_CLR_RX_OVER_clr_rx_over_shift                                        (0)
#define MIS_IC5_CLR_RX_OVER_clr_rx_over_mask                                         (0x00000001)
#define MIS_IC5_CLR_RX_OVER_clr_rx_over(data)                                        (0x00000001&((data)<<0))
#define MIS_IC5_CLR_RX_OVER_clr_rx_over_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_RX_OVER_get_clr_rx_over(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_TX_OVER                                                          0x1801BB4C
#define MIS_IC5_CLR_TX_OVER_reg_addr                                                 "0xB801BB4C"
#define MIS_IC5_CLR_TX_OVER_reg                                                      0xB801BB4C
#define set_MIS_IC5_CLR_TX_OVER_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_TX_OVER_reg)=data)
#define get_MIS_IC5_CLR_TX_OVER_reg   (*((volatile unsigned int*) MIS_IC5_CLR_TX_OVER_reg))
#define MIS_IC5_CLR_TX_OVER_inst_adr                                                 "0x00D3"
#define MIS_IC5_CLR_TX_OVER_inst                                                     0x00D3
#define MIS_IC5_CLR_TX_OVER_clr_tx_over_shift                                        (0)
#define MIS_IC5_CLR_TX_OVER_clr_tx_over_mask                                         (0x00000001)
#define MIS_IC5_CLR_TX_OVER_clr_tx_over(data)                                        (0x00000001&((data)<<0))
#define MIS_IC5_CLR_TX_OVER_clr_tx_over_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_TX_OVER_get_clr_tx_over(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_RD_REQ                                                           0x1801BB50
#define MIS_IC5_CLR_RD_REQ_reg_addr                                                  "0xB801BB50"
#define MIS_IC5_CLR_RD_REQ_reg                                                       0xB801BB50
#define set_MIS_IC5_CLR_RD_REQ_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_RD_REQ_reg)=data)
#define get_MIS_IC5_CLR_RD_REQ_reg   (*((volatile unsigned int*) MIS_IC5_CLR_RD_REQ_reg))
#define MIS_IC5_CLR_RD_REQ_inst_adr                                                  "0x00D4"
#define MIS_IC5_CLR_RD_REQ_inst                                                      0x00D4
#define MIS_IC5_CLR_RD_REQ_clr_rd_req_shift                                          (0)
#define MIS_IC5_CLR_RD_REQ_clr_rd_req_mask                                           (0x00000001)
#define MIS_IC5_CLR_RD_REQ_clr_rd_req(data)                                          (0x00000001&((data)<<0))
#define MIS_IC5_CLR_RD_REQ_clr_rd_req_src(data)                                      ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_RD_REQ_get_clr_rd_req(data)                                      ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_TX_ABRT                                                          0x1801BB54
#define MIS_IC5_CLR_TX_ABRT_reg_addr                                                 "0xB801BB54"
#define MIS_IC5_CLR_TX_ABRT_reg                                                      0xB801BB54
#define set_MIS_IC5_CLR_TX_ABRT_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_TX_ABRT_reg)=data)
#define get_MIS_IC5_CLR_TX_ABRT_reg   (*((volatile unsigned int*) MIS_IC5_CLR_TX_ABRT_reg))
#define MIS_IC5_CLR_TX_ABRT_inst_adr                                                 "0x00D5"
#define MIS_IC5_CLR_TX_ABRT_inst                                                     0x00D5
#define MIS_IC5_CLR_TX_ABRT_clr_tx_abrt_shift                                        (0)
#define MIS_IC5_CLR_TX_ABRT_clr_tx_abrt_mask                                         (0x00000001)
#define MIS_IC5_CLR_TX_ABRT_clr_tx_abrt(data)                                        (0x00000001&((data)<<0))
#define MIS_IC5_CLR_TX_ABRT_clr_tx_abrt_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_TX_ABRT_get_clr_tx_abrt(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_RX_DONE                                                          0x1801BB58
#define MIS_IC5_CLR_RX_DONE_reg_addr                                                 "0xB801BB58"
#define MIS_IC5_CLR_RX_DONE_reg                                                      0xB801BB58
#define set_MIS_IC5_CLR_RX_DONE_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_RX_DONE_reg)=data)
#define get_MIS_IC5_CLR_RX_DONE_reg   (*((volatile unsigned int*) MIS_IC5_CLR_RX_DONE_reg))
#define MIS_IC5_CLR_RX_DONE_inst_adr                                                 "0x00D6"
#define MIS_IC5_CLR_RX_DONE_inst                                                     0x00D6
#define MIS_IC5_CLR_RX_DONE_clr_rx_done_shift                                        (0)
#define MIS_IC5_CLR_RX_DONE_clr_rx_done_mask                                         (0x00000001)
#define MIS_IC5_CLR_RX_DONE_clr_rx_done(data)                                        (0x00000001&((data)<<0))
#define MIS_IC5_CLR_RX_DONE_clr_rx_done_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_RX_DONE_get_clr_rx_done(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_ACTIVITY                                                         0x1801BB5C
#define MIS_IC5_CLR_ACTIVITY_reg_addr                                                "0xB801BB5C"
#define MIS_IC5_CLR_ACTIVITY_reg                                                     0xB801BB5C
#define set_MIS_IC5_CLR_ACTIVITY_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_ACTIVITY_reg)=data)
#define get_MIS_IC5_CLR_ACTIVITY_reg   (*((volatile unsigned int*) MIS_IC5_CLR_ACTIVITY_reg))
#define MIS_IC5_CLR_ACTIVITY_inst_adr                                                "0x00D7"
#define MIS_IC5_CLR_ACTIVITY_inst                                                    0x00D7
#define MIS_IC5_CLR_ACTIVITY_clr_activity_shift                                      (0)
#define MIS_IC5_CLR_ACTIVITY_clr_activity_mask                                       (0x00000001)
#define MIS_IC5_CLR_ACTIVITY_clr_activity(data)                                      (0x00000001&((data)<<0))
#define MIS_IC5_CLR_ACTIVITY_clr_activity_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_ACTIVITY_get_clr_activity(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_STOP_DET                                                         0x1801BB60
#define MIS_IC5_CLR_STOP_DET_reg_addr                                                "0xB801BB60"
#define MIS_IC5_CLR_STOP_DET_reg                                                     0xB801BB60
#define set_MIS_IC5_CLR_STOP_DET_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_STOP_DET_reg)=data)
#define get_MIS_IC5_CLR_STOP_DET_reg   (*((volatile unsigned int*) MIS_IC5_CLR_STOP_DET_reg))
#define MIS_IC5_CLR_STOP_DET_inst_adr                                                "0x00D8"
#define MIS_IC5_CLR_STOP_DET_inst                                                    0x00D8
#define MIS_IC5_CLR_STOP_DET_clr_stop_det_shift                                      (0)
#define MIS_IC5_CLR_STOP_DET_clr_stop_det_mask                                       (0x00000001)
#define MIS_IC5_CLR_STOP_DET_clr_stop_det(data)                                      (0x00000001&((data)<<0))
#define MIS_IC5_CLR_STOP_DET_clr_stop_det_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_STOP_DET_get_clr_stop_det(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_START_DET                                                        0x1801BB64
#define MIS_IC5_CLR_START_DET_reg_addr                                               "0xB801BB64"
#define MIS_IC5_CLR_START_DET_reg                                                    0xB801BB64
#define set_MIS_IC5_CLR_START_DET_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_START_DET_reg)=data)
#define get_MIS_IC5_CLR_START_DET_reg   (*((volatile unsigned int*) MIS_IC5_CLR_START_DET_reg))
#define MIS_IC5_CLR_START_DET_inst_adr                                               "0x00D9"
#define MIS_IC5_CLR_START_DET_inst                                                   0x00D9
#define MIS_IC5_CLR_START_DET_clr_start_det_shift                                    (0)
#define MIS_IC5_CLR_START_DET_clr_start_det_mask                                     (0x00000001)
#define MIS_IC5_CLR_START_DET_clr_start_det(data)                                    (0x00000001&((data)<<0))
#define MIS_IC5_CLR_START_DET_clr_start_det_src(data)                                ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_START_DET_get_clr_start_det(data)                                ((0x00000001&(data))>>0)


#define MIS_IC5_CLR_GEN_CALL                                                         0x1801BB68
#define MIS_IC5_CLR_GEN_CALL_reg_addr                                                "0xB801BB68"
#define MIS_IC5_CLR_GEN_CALL_reg                                                     0xB801BB68
#define set_MIS_IC5_CLR_GEN_CALL_reg(data)   (*((volatile unsigned int*) MIS_IC5_CLR_GEN_CALL_reg)=data)
#define get_MIS_IC5_CLR_GEN_CALL_reg   (*((volatile unsigned int*) MIS_IC5_CLR_GEN_CALL_reg))
#define MIS_IC5_CLR_GEN_CALL_inst_adr                                                "0x00DA"
#define MIS_IC5_CLR_GEN_CALL_inst                                                    0x00DA
#define MIS_IC5_CLR_GEN_CALL_clr_gen_call_shift                                      (0)
#define MIS_IC5_CLR_GEN_CALL_clr_gen_call_mask                                       (0x00000001)
#define MIS_IC5_CLR_GEN_CALL_clr_gen_call(data)                                      (0x00000001&((data)<<0))
#define MIS_IC5_CLR_GEN_CALL_clr_gen_call_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_IC5_CLR_GEN_CALL_get_clr_gen_call(data)                                  ((0x00000001&(data))>>0)


#define MIS_IC5_ENABLE                                                               0x1801BB6C
#define MIS_IC5_ENABLE_reg_addr                                                      "0xB801BB6C"
#define MIS_IC5_ENABLE_reg                                                           0xB801BB6C
#define set_MIS_IC5_ENABLE_reg(data)   (*((volatile unsigned int*) MIS_IC5_ENABLE_reg)=data)
#define get_MIS_IC5_ENABLE_reg   (*((volatile unsigned int*) MIS_IC5_ENABLE_reg))
#define MIS_IC5_ENABLE_inst_adr                                                      "0x00DB"
#define MIS_IC5_ENABLE_inst                                                          0x00DB
#define MIS_IC5_ENABLE_enable_shift                                                  (0)
#define MIS_IC5_ENABLE_enable_mask                                                   (0x00000001)
#define MIS_IC5_ENABLE_enable(data)                                                  (0x00000001&((data)<<0))
#define MIS_IC5_ENABLE_enable_src(data)                                              ((0x00000001&(data))>>0)
#define MIS_IC5_ENABLE_get_enable(data)                                              ((0x00000001&(data))>>0)


#define MIS_IC5_STATUS                                                               0x1801BB70
#define MIS_IC5_STATUS_reg_addr                                                      "0xB801BB70"
#define MIS_IC5_STATUS_reg                                                           0xB801BB70
#define set_MIS_IC5_STATUS_reg(data)   (*((volatile unsigned int*) MIS_IC5_STATUS_reg)=data)
#define get_MIS_IC5_STATUS_reg   (*((volatile unsigned int*) MIS_IC5_STATUS_reg))
#define MIS_IC5_STATUS_inst_adr                                                      "0x00DC"
#define MIS_IC5_STATUS_inst                                                          0x00DC
#define MIS_IC5_STATUS_slv_activity_shift                                            (6)
#define MIS_IC5_STATUS_slv_activity_mask                                             (0x00000040)
#define MIS_IC5_STATUS_slv_activity(data)                                            (0x00000040&((data)<<6))
#define MIS_IC5_STATUS_slv_activity_src(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC5_STATUS_get_slv_activity(data)                                        ((0x00000040&(data))>>6)
#define MIS_IC5_STATUS_mst_activity_shift                                            (5)
#define MIS_IC5_STATUS_mst_activity_mask                                             (0x00000020)
#define MIS_IC5_STATUS_mst_activity(data)                                            (0x00000020&((data)<<5))
#define MIS_IC5_STATUS_mst_activity_src(data)                                        ((0x00000020&(data))>>5)
#define MIS_IC5_STATUS_get_mst_activity(data)                                        ((0x00000020&(data))>>5)
#define MIS_IC5_STATUS_rff_shift                                                     (4)
#define MIS_IC5_STATUS_rff_mask                                                      (0x00000010)
#define MIS_IC5_STATUS_rff(data)                                                     (0x00000010&((data)<<4))
#define MIS_IC5_STATUS_rff_src(data)                                                 ((0x00000010&(data))>>4)
#define MIS_IC5_STATUS_get_rff(data)                                                 ((0x00000010&(data))>>4)
#define MIS_IC5_STATUS_rfne_shift                                                    (3)
#define MIS_IC5_STATUS_rfne_mask                                                     (0x00000008)
#define MIS_IC5_STATUS_rfne(data)                                                    (0x00000008&((data)<<3))
#define MIS_IC5_STATUS_rfne_src(data)                                                ((0x00000008&(data))>>3)
#define MIS_IC5_STATUS_get_rfne(data)                                                ((0x00000008&(data))>>3)
#define MIS_IC5_STATUS_tfe_shift                                                     (2)
#define MIS_IC5_STATUS_tfe_mask                                                      (0x00000004)
#define MIS_IC5_STATUS_tfe(data)                                                     (0x00000004&((data)<<2))
#define MIS_IC5_STATUS_tfe_src(data)                                                 ((0x00000004&(data))>>2)
#define MIS_IC5_STATUS_get_tfe(data)                                                 ((0x00000004&(data))>>2)
#define MIS_IC5_STATUS_tfnf_shift                                                    (1)
#define MIS_IC5_STATUS_tfnf_mask                                                     (0x00000002)
#define MIS_IC5_STATUS_tfnf(data)                                                    (0x00000002&((data)<<1))
#define MIS_IC5_STATUS_tfnf_src(data)                                                ((0x00000002&(data))>>1)
#define MIS_IC5_STATUS_get_tfnf(data)                                                ((0x00000002&(data))>>1)
#define MIS_IC5_STATUS_activity_shift                                                (0)
#define MIS_IC5_STATUS_activity_mask                                                 (0x00000001)
#define MIS_IC5_STATUS_activity(data)                                                (0x00000001&((data)<<0))
#define MIS_IC5_STATUS_activity_src(data)                                            ((0x00000001&(data))>>0)
#define MIS_IC5_STATUS_get_activity(data)                                            ((0x00000001&(data))>>0)


#define MIS_IC5_TXFLR                                                                0x1801BB74
#define MIS_IC5_TXFLR_reg_addr                                                       "0xB801BB74"
#define MIS_IC5_TXFLR_reg                                                            0xB801BB74
#define set_MIS_IC5_TXFLR_reg(data)   (*((volatile unsigned int*) MIS_IC5_TXFLR_reg)=data)
#define get_MIS_IC5_TXFLR_reg   (*((volatile unsigned int*) MIS_IC5_TXFLR_reg))
#define MIS_IC5_TXFLR_inst_adr                                                       "0x00DD"
#define MIS_IC5_TXFLR_inst                                                           0x00DD
#define MIS_IC5_TXFLR_txflr_shift                                                    (0)
#define MIS_IC5_TXFLR_txflr_mask                                                     (0x0000000F)
#define MIS_IC5_TXFLR_txflr(data)                                                    (0x0000000F&((data)<<0))
#define MIS_IC5_TXFLR_txflr_src(data)                                                ((0x0000000F&(data))>>0)
#define MIS_IC5_TXFLR_get_txflr(data)                                                ((0x0000000F&(data))>>0)


#define MIS_IC5_RXFLR                                                                0x1801BB78
#define MIS_IC5_RXFLR_reg_addr                                                       "0xB801BB78"
#define MIS_IC5_RXFLR_reg                                                            0xB801BB78
#define set_MIS_IC5_RXFLR_reg(data)   (*((volatile unsigned int*) MIS_IC5_RXFLR_reg)=data)
#define get_MIS_IC5_RXFLR_reg   (*((volatile unsigned int*) MIS_IC5_RXFLR_reg))
#define MIS_IC5_RXFLR_inst_adr                                                       "0x00DE"
#define MIS_IC5_RXFLR_inst                                                           0x00DE
#define MIS_IC5_RXFLR_rxflr_shift                                                    (0)
#define MIS_IC5_RXFLR_rxflr_mask                                                     (0x0000000F)
#define MIS_IC5_RXFLR_rxflr(data)                                                    (0x0000000F&((data)<<0))
#define MIS_IC5_RXFLR_rxflr_src(data)                                                ((0x0000000F&(data))>>0)
#define MIS_IC5_RXFLR_get_rxflr(data)                                                ((0x0000000F&(data))>>0)


#define MIS_IC5_SDA_HOLD                                                             0x1801BB7C
#define MIS_IC5_SDA_HOLD_reg_addr                                                    "0xB801BB7C"
#define MIS_IC5_SDA_HOLD_reg                                                         0xB801BB7C
#define set_MIS_IC5_SDA_HOLD_reg(data)   (*((volatile unsigned int*) MIS_IC5_SDA_HOLD_reg)=data)
#define get_MIS_IC5_SDA_HOLD_reg   (*((volatile unsigned int*) MIS_IC5_SDA_HOLD_reg))
#define MIS_IC5_SDA_HOLD_inst_adr                                                    "0x00DF"
#define MIS_IC5_SDA_HOLD_inst                                                        0x00DF
#define MIS_IC5_SDA_HOLD_sda_hold_shift                                              (0)
#define MIS_IC5_SDA_HOLD_sda_hold_mask                                               (0x0000FFFF)
#define MIS_IC5_SDA_HOLD_sda_hold(data)                                              (0x0000FFFF&((data)<<0))
#define MIS_IC5_SDA_HOLD_sda_hold_src(data)                                          ((0x0000FFFF&(data))>>0)
#define MIS_IC5_SDA_HOLD_get_sda_hold(data)                                          ((0x0000FFFF&(data))>>0)


#define MIS_IC5_TX_ABRT_SOURCE                                                       0x1801BB80
#define MIS_IC5_TX_ABRT_SOURCE_reg_addr                                              "0xB801BB80"
#define MIS_IC5_TX_ABRT_SOURCE_reg                                                   0xB801BB80
#define set_MIS_IC5_TX_ABRT_SOURCE_reg(data)   (*((volatile unsigned int*) MIS_IC5_TX_ABRT_SOURCE_reg)=data)
#define get_MIS_IC5_TX_ABRT_SOURCE_reg   (*((volatile unsigned int*) MIS_IC5_TX_ABRT_SOURCE_reg))
#define MIS_IC5_TX_ABRT_SOURCE_inst_adr                                              "0x00E0"
#define MIS_IC5_TX_ABRT_SOURCE_inst                                                  0x00E0
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slvrd_intx_shift                                 (15)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slvrd_intx_mask                                  (0x00008000)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slvrd_intx(data)                                 (0x00008000&((data)<<15))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slvrd_intx_src(data)                             ((0x00008000&(data))>>15)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_slvrd_intx(data)                             ((0x00008000&(data))>>15)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slv_arblost_shift                                (14)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slv_arblost_mask                                 (0x00004000)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slv_arblost(data)                                (0x00004000&((data)<<14))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slv_arblost_src(data)                            ((0x00004000&(data))>>14)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_slv_arblost(data)                            ((0x00004000&(data))>>14)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slvflush_txfifo_shift                            (13)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slvflush_txfifo_mask                             (0x00002000)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slvflush_txfifo(data)                            (0x00002000&((data)<<13))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_slvflush_txfifo_src(data)                        ((0x00002000&(data))>>13)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_slvflush_txfifo(data)                        ((0x00002000&(data))>>13)
#define MIS_IC5_TX_ABRT_SOURCE_arb_lost_shift                                        (12)
#define MIS_IC5_TX_ABRT_SOURCE_arb_lost_mask                                         (0x00001000)
#define MIS_IC5_TX_ABRT_SOURCE_arb_lost(data)                                        (0x00001000&((data)<<12))
#define MIS_IC5_TX_ABRT_SOURCE_arb_lost_src(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC5_TX_ABRT_SOURCE_get_arb_lost(data)                                    ((0x00001000&(data))>>12)
#define MIS_IC5_TX_ABRT_SOURCE_arb_master_dis_shift                                  (11)
#define MIS_IC5_TX_ABRT_SOURCE_arb_master_dis_mask                                   (0x00000800)
#define MIS_IC5_TX_ABRT_SOURCE_arb_master_dis(data)                                  (0x00000800&((data)<<11))
#define MIS_IC5_TX_ABRT_SOURCE_arb_master_dis_src(data)                              ((0x00000800&(data))>>11)
#define MIS_IC5_TX_ABRT_SOURCE_get_arb_master_dis(data)                              ((0x00000800&(data))>>11)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_shift                             (10)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_mask                              (0x00000400)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10b_rd_norstrt(data)                             (0x00000400&((data)<<10))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10b_rd_norstrt_src(data)                         ((0x00000400&(data))>>10)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_10b_rd_norstrt(data)                         ((0x00000400&(data))>>10)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_sbyte_norstrt_shift                              (9)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_sbyte_norstrt_mask                               (0x00000200)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_sbyte_norstrt(data)                              (0x00000200&((data)<<9))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_sbyte_norstrt_src(data)                          ((0x00000200&(data))>>9)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_sbyte_norstrt(data)                          ((0x00000200&(data))>>9)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_hs_norstrt_shift                                 (8)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_hs_norstrt_mask                                  (0x00000100)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_hs_norstrt(data)                                 (0x00000100&((data)<<8))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_hs_norstrt_src(data)                             ((0x00000100&(data))>>8)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_hs_norstrt(data)                             ((0x00000100&(data))>>8)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_sbyte_ackdet_shift                               (7)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_sbyte_ackdet_mask                                (0x00000080)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_sbyte_ackdet(data)                               (0x00000080&((data)<<7))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_sbyte_ackdet_src(data)                           ((0x00000080&(data))>>7)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_sbyte_ackdet(data)                           ((0x00000080&(data))>>7)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_hs_ackdet_shift                                  (6)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_hs_ackdet_mask                                   (0x00000040)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_hs_ackdet(data)                                  (0x00000040&((data)<<6))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_hs_ackdet_src(data)                              ((0x00000040&(data))>>6)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_hs_ackdet(data)                              ((0x00000040&(data))>>6)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_gcall_read_shift                                 (5)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_gcall_read_mask                                  (0x00000020)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_gcall_read(data)                                 (0x00000020&((data)<<5))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_gcall_read_src(data)                             ((0x00000020&(data))>>5)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_gcall_read(data)                             ((0x00000020&(data))>>5)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_gcall_noack_shift                                (4)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_gcall_noack_mask                                 (0x00000010)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_gcall_noack(data)                                (0x00000010&((data)<<4))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_gcall_noack_src(data)                            ((0x00000010&(data))>>4)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_gcall_noack(data)                            ((0x00000010&(data))>>4)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_txdata_noack_shift                               (3)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_txdata_noack_mask                                (0x00000008)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_txdata_noack(data)                               (0x00000008&((data)<<3))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_txdata_noack_src(data)                           ((0x00000008&(data))>>3)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_txdata_noack(data)                           ((0x00000008&(data))>>3)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10addr2_noack_shift                              (2)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10addr2_noack_mask                               (0x00000004)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10addr2_noack(data)                              (0x00000004&((data)<<2))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10addr2_noack_src(data)                          ((0x00000004&(data))>>2)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_10addr2_noack(data)                          ((0x00000004&(data))>>2)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10addr1_noack_shift                              (1)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10addr1_noack_mask                               (0x00000002)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10addr1_noack(data)                              (0x00000002&((data)<<1))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_10addr1_noack_src(data)                          ((0x00000002&(data))>>1)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_10addr1_noack(data)                          ((0x00000002&(data))>>1)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_7b_addr_noack_shift                              (0)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_7b_addr_noack_mask                               (0x00000001)
#define MIS_IC5_TX_ABRT_SOURCE_abrt_7b_addr_noack(data)                              (0x00000001&((data)<<0))
#define MIS_IC5_TX_ABRT_SOURCE_abrt_7b_addr_noack_src(data)                          ((0x00000001&(data))>>0)
#define MIS_IC5_TX_ABRT_SOURCE_get_abrt_7b_addr_noack(data)                          ((0x00000001&(data))>>0)


#define MIS_IC5_SLV_DATA_NACK_ONLY                                                   0x1801BB84
#define MIS_IC5_SLV_DATA_NACK_ONLY_reg_addr                                          "0xB801BB84"
#define MIS_IC5_SLV_DATA_NACK_ONLY_reg                                               0xB801BB84
#define set_MIS_IC5_SLV_DATA_NACK_ONLY_reg(data)   (*((volatile unsigned int*) MIS_IC5_SLV_DATA_NACK_ONLY_reg)=data)
#define get_MIS_IC5_SLV_DATA_NACK_ONLY_reg   (*((volatile unsigned int*) MIS_IC5_SLV_DATA_NACK_ONLY_reg))
#define MIS_IC5_SLV_DATA_NACK_ONLY_inst_adr                                          "0x00E1"
#define MIS_IC5_SLV_DATA_NACK_ONLY_inst                                              0x00E1
#define MIS_IC5_SLV_DATA_NACK_ONLY_nack_shift                                        (0)
#define MIS_IC5_SLV_DATA_NACK_ONLY_nack_mask                                         (0x00000001)
#define MIS_IC5_SLV_DATA_NACK_ONLY_nack(data)                                        (0x00000001&((data)<<0))
#define MIS_IC5_SLV_DATA_NACK_ONLY_nack_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_IC5_SLV_DATA_NACK_ONLY_get_nack(data)                                    ((0x00000001&(data))>>0)


#define MIS_IC5_DMA_CR                                                               0x1801BB88
#define MIS_IC5_DMA_CR_reg_addr                                                      "0xB801BB88"
#define MIS_IC5_DMA_CR_reg                                                           0xB801BB88
#define set_MIS_IC5_DMA_CR_reg(data)   (*((volatile unsigned int*) MIS_IC5_DMA_CR_reg)=data)
#define get_MIS_IC5_DMA_CR_reg   (*((volatile unsigned int*) MIS_IC5_DMA_CR_reg))
#define MIS_IC5_DMA_CR_inst_adr                                                      "0x00E2"
#define MIS_IC5_DMA_CR_inst                                                          0x00E2
#define MIS_IC5_DMA_CR_tdmae_shift                                                   (1)
#define MIS_IC5_DMA_CR_tdmae_mask                                                    (0x00000002)
#define MIS_IC5_DMA_CR_tdmae(data)                                                   (0x00000002&((data)<<1))
#define MIS_IC5_DMA_CR_tdmae_src(data)                                               ((0x00000002&(data))>>1)
#define MIS_IC5_DMA_CR_get_tdmae(data)                                               ((0x00000002&(data))>>1)
#define MIS_IC5_DMA_CR_rdmae_shift                                                   (0)
#define MIS_IC5_DMA_CR_rdmae_mask                                                    (0x00000001)
#define MIS_IC5_DMA_CR_rdmae(data)                                                   (0x00000001&((data)<<0))
#define MIS_IC5_DMA_CR_rdmae_src(data)                                               ((0x00000001&(data))>>0)
#define MIS_IC5_DMA_CR_get_rdmae(data)                                               ((0x00000001&(data))>>0)


#define MIS_IC5_DMA_TDLR                                                             0x1801BB8C
#define MIS_IC5_DMA_TDLR_reg_addr                                                    "0xB801BB8C"
#define MIS_IC5_DMA_TDLR_reg                                                         0xB801BB8C
#define set_MIS_IC5_DMA_TDLR_reg(data)   (*((volatile unsigned int*) MIS_IC5_DMA_TDLR_reg)=data)
#define get_MIS_IC5_DMA_TDLR_reg   (*((volatile unsigned int*) MIS_IC5_DMA_TDLR_reg))
#define MIS_IC5_DMA_TDLR_inst_adr                                                    "0x00E3"
#define MIS_IC5_DMA_TDLR_inst                                                        0x00E3
#define MIS_IC5_DMA_TDLR_dmatdl_shift                                                (0)
#define MIS_IC5_DMA_TDLR_dmatdl_mask                                                 (0x00000007)
#define MIS_IC5_DMA_TDLR_dmatdl(data)                                                (0x00000007&((data)<<0))
#define MIS_IC5_DMA_TDLR_dmatdl_src(data)                                            ((0x00000007&(data))>>0)
#define MIS_IC5_DMA_TDLR_get_dmatdl(data)                                            ((0x00000007&(data))>>0)


#define MIS_IC5_DMA_RDLR                                                             0x1801BB90
#define MIS_IC5_DMA_RDLR_reg_addr                                                    "0xB801BB90"
#define MIS_IC5_DMA_RDLR_reg                                                         0xB801BB90
#define set_MIS_IC5_DMA_RDLR_reg(data)   (*((volatile unsigned int*) MIS_IC5_DMA_RDLR_reg)=data)
#define get_MIS_IC5_DMA_RDLR_reg   (*((volatile unsigned int*) MIS_IC5_DMA_RDLR_reg))
#define MIS_IC5_DMA_RDLR_inst_adr                                                    "0x00E4"
#define MIS_IC5_DMA_RDLR_inst                                                        0x00E4
#define MIS_IC5_DMA_RDLR_dmardl_shift                                                (0)
#define MIS_IC5_DMA_RDLR_dmardl_mask                                                 (0x0000000F)
#define MIS_IC5_DMA_RDLR_dmardl(data)                                                (0x0000000F&((data)<<0))
#define MIS_IC5_DMA_RDLR_dmardl_src(data)                                            ((0x0000000F&(data))>>0)
#define MIS_IC5_DMA_RDLR_get_dmardl(data)                                            ((0x0000000F&(data))>>0)


#define MIS_IC5_SDA_SETUP                                                            0x1801BB94
#define MIS_IC5_SDA_SETUP_reg_addr                                                   "0xB801BB94"
#define MIS_IC5_SDA_SETUP_reg                                                        0xB801BB94
#define set_MIS_IC5_SDA_SETUP_reg(data)   (*((volatile unsigned int*) MIS_IC5_SDA_SETUP_reg)=data)
#define get_MIS_IC5_SDA_SETUP_reg   (*((volatile unsigned int*) MIS_IC5_SDA_SETUP_reg))
#define MIS_IC5_SDA_SETUP_inst_adr                                                   "0x00E5"
#define MIS_IC5_SDA_SETUP_inst                                                       0x00E5
#define MIS_IC5_SDA_SETUP_sda_setup_shift                                            (0)
#define MIS_IC5_SDA_SETUP_sda_setup_mask                                             (0x000000FF)
#define MIS_IC5_SDA_SETUP_sda_setup(data)                                            (0x000000FF&((data)<<0))
#define MIS_IC5_SDA_SETUP_sda_setup_src(data)                                        ((0x000000FF&(data))>>0)
#define MIS_IC5_SDA_SETUP_get_sda_setup(data)                                        ((0x000000FF&(data))>>0)


#define MIS_IC5_ACK_GENERAL_CALL                                                     0x1801BB98
#define MIS_IC5_ACK_GENERAL_CALL_reg_addr                                            "0xB801BB98"
#define MIS_IC5_ACK_GENERAL_CALL_reg                                                 0xB801BB98
#define set_MIS_IC5_ACK_GENERAL_CALL_reg(data)   (*((volatile unsigned int*) MIS_IC5_ACK_GENERAL_CALL_reg)=data)
#define get_MIS_IC5_ACK_GENERAL_CALL_reg   (*((volatile unsigned int*) MIS_IC5_ACK_GENERAL_CALL_reg))
#define MIS_IC5_ACK_GENERAL_CALL_inst_adr                                            "0x00E6"
#define MIS_IC5_ACK_GENERAL_CALL_inst                                                0x00E6
#define MIS_IC5_ACK_GENERAL_CALL_ack_gen_call_shift                                  (0)
#define MIS_IC5_ACK_GENERAL_CALL_ack_gen_call_mask                                   (0x00000001)
#define MIS_IC5_ACK_GENERAL_CALL_ack_gen_call(data)                                  (0x00000001&((data)<<0))
#define MIS_IC5_ACK_GENERAL_CALL_ack_gen_call_src(data)                              ((0x00000001&(data))>>0)
#define MIS_IC5_ACK_GENERAL_CALL_get_ack_gen_call(data)                              ((0x00000001&(data))>>0)


#define MIS_IC5_ENABLE_STATUS                                                        0x1801BB9C
#define MIS_IC5_ENABLE_STATUS_reg_addr                                               "0xB801BB9C"
#define MIS_IC5_ENABLE_STATUS_reg                                                    0xB801BB9C
#define set_MIS_IC5_ENABLE_STATUS_reg(data)   (*((volatile unsigned int*) MIS_IC5_ENABLE_STATUS_reg)=data)
#define get_MIS_IC5_ENABLE_STATUS_reg   (*((volatile unsigned int*) MIS_IC5_ENABLE_STATUS_reg))
#define MIS_IC5_ENABLE_STATUS_inst_adr                                               "0x00E7"
#define MIS_IC5_ENABLE_STATUS_inst                                                   0x00E7
#define MIS_IC5_ENABLE_STATUS_slv_rx_data_lost_shift                                 (2)
#define MIS_IC5_ENABLE_STATUS_slv_rx_data_lost_mask                                  (0x00000004)
#define MIS_IC5_ENABLE_STATUS_slv_rx_data_lost(data)                                 (0x00000004&((data)<<2))
#define MIS_IC5_ENABLE_STATUS_slv_rx_data_lost_src(data)                             ((0x00000004&(data))>>2)
#define MIS_IC5_ENABLE_STATUS_get_slv_rx_data_lost(data)                             ((0x00000004&(data))>>2)
#define MIS_IC5_ENABLE_STATUS_slv_disabled_whi_shift                                 (1)
#define MIS_IC5_ENABLE_STATUS_slv_disabled_whi_mask                                  (0x00000002)
#define MIS_IC5_ENABLE_STATUS_slv_disabled_whi(data)                                 (0x00000002&((data)<<1))
#define MIS_IC5_ENABLE_STATUS_slv_disabled_whi_src(data)                             ((0x00000002&(data))>>1)
#define MIS_IC5_ENABLE_STATUS_get_slv_disabled_whi(data)                             ((0x00000002&(data))>>1)
#define MIS_IC5_ENABLE_STATUS_ic_en_shift                                            (0)
#define MIS_IC5_ENABLE_STATUS_ic_en_mask                                             (0x00000001)
#define MIS_IC5_ENABLE_STATUS_ic_en(data)                                            (0x00000001&((data)<<0))
#define MIS_IC5_ENABLE_STATUS_ic_en_src(data)                                        ((0x00000001&(data))>>0)
#define MIS_IC5_ENABLE_STATUS_get_ic_en(data)                                        ((0x00000001&(data))>>0)


#define MIS_IC5_COMP_PARAM_1                                                         0x1801BBF4
#define MIS_IC5_COMP_PARAM_1_reg_addr                                                "0xB801BBF4"
#define MIS_IC5_COMP_PARAM_1_reg                                                     0xB801BBF4
#define set_MIS_IC5_COMP_PARAM_1_reg(data)   (*((volatile unsigned int*) MIS_IC5_COMP_PARAM_1_reg)=data)
#define get_MIS_IC5_COMP_PARAM_1_reg   (*((volatile unsigned int*) MIS_IC5_COMP_PARAM_1_reg))
#define MIS_IC5_COMP_PARAM_1_inst_adr                                                "0x00FD"
#define MIS_IC5_COMP_PARAM_1_inst                                                    0x00FD
#define MIS_IC5_COMP_PARAM_1_tx_buffer_depth_shift                                   (16)
#define MIS_IC5_COMP_PARAM_1_tx_buffer_depth_mask                                    (0x00FF0000)
#define MIS_IC5_COMP_PARAM_1_tx_buffer_depth(data)                                   (0x00FF0000&((data)<<16))
#define MIS_IC5_COMP_PARAM_1_tx_buffer_depth_src(data)                               ((0x00FF0000&(data))>>16)
#define MIS_IC5_COMP_PARAM_1_get_tx_buffer_depth(data)                               ((0x00FF0000&(data))>>16)
#define MIS_IC5_COMP_PARAM_1_rx_buffer_depth_shift                                   (8)
#define MIS_IC5_COMP_PARAM_1_rx_buffer_depth_mask                                    (0x0000FF00)
#define MIS_IC5_COMP_PARAM_1_rx_buffer_depth(data)                                   (0x0000FF00&((data)<<8))
#define MIS_IC5_COMP_PARAM_1_rx_buffer_depth_src(data)                               ((0x0000FF00&(data))>>8)
#define MIS_IC5_COMP_PARAM_1_get_rx_buffer_depth(data)                               ((0x0000FF00&(data))>>8)
#define MIS_IC5_COMP_PARAM_1_add_encoded_params_shift                                (7)
#define MIS_IC5_COMP_PARAM_1_add_encoded_params_mask                                 (0x00000080)
#define MIS_IC5_COMP_PARAM_1_add_encoded_params(data)                                (0x00000080&((data)<<7))
#define MIS_IC5_COMP_PARAM_1_add_encoded_params_src(data)                            ((0x00000080&(data))>>7)
#define MIS_IC5_COMP_PARAM_1_get_add_encoded_params(data)                            ((0x00000080&(data))>>7)
#define MIS_IC5_COMP_PARAM_1_has_dma_shift                                           (6)
#define MIS_IC5_COMP_PARAM_1_has_dma_mask                                            (0x00000040)
#define MIS_IC5_COMP_PARAM_1_has_dma(data)                                           (0x00000040&((data)<<6))
#define MIS_IC5_COMP_PARAM_1_has_dma_src(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC5_COMP_PARAM_1_get_has_dma(data)                                       ((0x00000040&(data))>>6)
#define MIS_IC5_COMP_PARAM_1_intr_io_shift                                           (5)
#define MIS_IC5_COMP_PARAM_1_intr_io_mask                                            (0x00000020)
#define MIS_IC5_COMP_PARAM_1_intr_io(data)                                           (0x00000020&((data)<<5))
#define MIS_IC5_COMP_PARAM_1_intr_io_src(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC5_COMP_PARAM_1_get_intr_io(data)                                       ((0x00000020&(data))>>5)
#define MIS_IC5_COMP_PARAM_1_hc_count_values_shift                                   (4)
#define MIS_IC5_COMP_PARAM_1_hc_count_values_mask                                    (0x00000010)
#define MIS_IC5_COMP_PARAM_1_hc_count_values(data)                                   (0x00000010&((data)<<4))
#define MIS_IC5_COMP_PARAM_1_hc_count_values_src(data)                               ((0x00000010&(data))>>4)
#define MIS_IC5_COMP_PARAM_1_get_hc_count_values(data)                               ((0x00000010&(data))>>4)
#define MIS_IC5_COMP_PARAM_1_max_speed_mode_shift                                    (2)
#define MIS_IC5_COMP_PARAM_1_max_speed_mode_mask                                     (0x0000000C)
#define MIS_IC5_COMP_PARAM_1_max_speed_mode(data)                                    (0x0000000C&((data)<<2))
#define MIS_IC5_COMP_PARAM_1_max_speed_mode_src(data)                                ((0x0000000C&(data))>>2)
#define MIS_IC5_COMP_PARAM_1_get_max_speed_mode(data)                                ((0x0000000C&(data))>>2)
#define MIS_IC5_COMP_PARAM_1_apb_data_width_shift                                    (0)
#define MIS_IC5_COMP_PARAM_1_apb_data_width_mask                                     (0x00000003)
#define MIS_IC5_COMP_PARAM_1_apb_data_width(data)                                    (0x00000003&((data)<<0))
#define MIS_IC5_COMP_PARAM_1_apb_data_width_src(data)                                ((0x00000003&(data))>>0)
#define MIS_IC5_COMP_PARAM_1_get_apb_data_width(data)                                ((0x00000003&(data))>>0)


#define MIS_IC5_COMP_VERSION                                                         0x1801BBF8
#define MIS_IC5_COMP_VERSION_reg_addr                                                "0xB801BBF8"
#define MIS_IC5_COMP_VERSION_reg                                                     0xB801BBF8
#define set_MIS_IC5_COMP_VERSION_reg(data)   (*((volatile unsigned int*) MIS_IC5_COMP_VERSION_reg)=data)
#define get_MIS_IC5_COMP_VERSION_reg   (*((volatile unsigned int*) MIS_IC5_COMP_VERSION_reg))
#define MIS_IC5_COMP_VERSION_inst_adr                                                "0x00FE"
#define MIS_IC5_COMP_VERSION_inst                                                    0x00FE
#define MIS_IC5_COMP_VERSION_ic_comp_version_shift                                   (0)
#define MIS_IC5_COMP_VERSION_ic_comp_version_mask                                    (0xFFFFFFFF)
#define MIS_IC5_COMP_VERSION_ic_comp_version(data)                                   (0xFFFFFFFF&((data)<<0))
#define MIS_IC5_COMP_VERSION_ic_comp_version_src(data)                               ((0xFFFFFFFF&(data))>>0)
#define MIS_IC5_COMP_VERSION_get_ic_comp_version(data)                               ((0xFFFFFFFF&(data))>>0)


#define MIS_IC5_COMP_TYPE                                                            0x1801BBFC
#define MIS_IC5_COMP_TYPE_reg_addr                                                   "0xB801BBFC"
#define MIS_IC5_COMP_TYPE_reg                                                        0xB801BBFC
#define set_MIS_IC5_COMP_TYPE_reg(data)   (*((volatile unsigned int*) MIS_IC5_COMP_TYPE_reg)=data)
#define get_MIS_IC5_COMP_TYPE_reg   (*((volatile unsigned int*) MIS_IC5_COMP_TYPE_reg))
#define MIS_IC5_COMP_TYPE_inst_adr                                                   "0x00FF"
#define MIS_IC5_COMP_TYPE_inst                                                       0x00FF
#define MIS_IC5_COMP_TYPE_ic_comp_type_shift                                         (0)
#define MIS_IC5_COMP_TYPE_ic_comp_type_mask                                          (0xFFFFFFFF)
#define MIS_IC5_COMP_TYPE_ic_comp_type(data)                                         (0xFFFFFFFF&((data)<<0))
#define MIS_IC5_COMP_TYPE_ic_comp_type_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define MIS_IC5_COMP_TYPE_get_ic_comp_type(data)                                     ((0xFFFFFFFF&(data))>>0)


#define MIS_TC0TVR                                                                   0x1801B500
#define MIS_TC0TVR_reg_addr                                                          "0xB801B500"
#define MIS_TC0TVR_reg                                                               0xB801B500
#define set_MIS_TC0TVR_reg(data)   (*((volatile unsigned int*) MIS_TC0TVR_reg)=data)
#define get_MIS_TC0TVR_reg   (*((volatile unsigned int*) MIS_TC0TVR_reg))
#define MIS_TC0TVR_inst_adr                                                          "0x0040"
#define MIS_TC0TVR_inst                                                              0x0040
#define MIS_TC0TVR_tc0tvr_shift                                                      (0)
#define MIS_TC0TVR_tc0tvr_mask                                                       (0xFFFFFFFF)
#define MIS_TC0TVR_tc0tvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define MIS_TC0TVR_tc0tvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define MIS_TC0TVR_get_tc0tvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define MIS_TC1TVR                                                                   0x1801B504
#define MIS_TC1TVR_reg_addr                                                          "0xB801B504"
#define MIS_TC1TVR_reg                                                               0xB801B504
#define set_MIS_TC1TVR_reg(data)   (*((volatile unsigned int*) MIS_TC1TVR_reg)=data)
#define get_MIS_TC1TVR_reg   (*((volatile unsigned int*) MIS_TC1TVR_reg))
#define MIS_TC1TVR_inst_adr                                                          "0x0041"
#define MIS_TC1TVR_inst                                                              0x0041
#define MIS_TC1TVR_tc1tvr_shift                                                      (0)
#define MIS_TC1TVR_tc1tvr_mask                                                       (0xFFFFFFFF)
#define MIS_TC1TVR_tc1tvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define MIS_TC1TVR_tc1tvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define MIS_TC1TVR_get_tc1tvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define MIS_TC2TVR                                                                   0x1801B508
#define MIS_TC2TVR_reg_addr                                                          "0xB801B508"
#define MIS_TC2TVR_reg                                                               0xB801B508
#define set_MIS_TC2TVR_reg(data)   (*((volatile unsigned int*) MIS_TC2TVR_reg)=data)
#define get_MIS_TC2TVR_reg   (*((volatile unsigned int*) MIS_TC2TVR_reg))
#define MIS_TC2TVR_inst_adr                                                          "0x0042"
#define MIS_TC2TVR_inst                                                              0x0042
#define MIS_TC2TVR_tc2tvr_shift                                                      (0)
#define MIS_TC2TVR_tc2tvr_mask                                                       (0xFFFFFFFF)
#define MIS_TC2TVR_tc2tvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define MIS_TC2TVR_tc2tvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define MIS_TC2TVR_get_tc2tvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define MIS_TC0CVR                                                                   0x1801B50C
#define MIS_TC0CVR_reg_addr                                                          "0xB801B50C"
#define MIS_TC0CVR_reg                                                               0xB801B50C
#define set_MIS_TC0CVR_reg(data)   (*((volatile unsigned int*) MIS_TC0CVR_reg)=data)
#define get_MIS_TC0CVR_reg   (*((volatile unsigned int*) MIS_TC0CVR_reg))
#define MIS_TC0CVR_inst_adr                                                          "0x0043"
#define MIS_TC0CVR_inst                                                              0x0043
#define MIS_TC0CVR_tc0cvr_shift                                                      (0)
#define MIS_TC0CVR_tc0cvr_mask                                                       (0xFFFFFFFF)
#define MIS_TC0CVR_tc0cvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define MIS_TC0CVR_tc0cvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define MIS_TC0CVR_get_tc0cvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define MIS_TC1CVR                                                                   0x1801B510
#define MIS_TC1CVR_reg_addr                                                          "0xB801B510"
#define MIS_TC1CVR_reg                                                               0xB801B510
#define set_MIS_TC1CVR_reg(data)   (*((volatile unsigned int*) MIS_TC1CVR_reg)=data)
#define get_MIS_TC1CVR_reg   (*((volatile unsigned int*) MIS_TC1CVR_reg))
#define MIS_TC1CVR_inst_adr                                                          "0x0044"
#define MIS_TC1CVR_inst                                                              0x0044
#define MIS_TC1CVR_tc1cvr_shift                                                      (0)
#define MIS_TC1CVR_tc1cvr_mask                                                       (0xFFFFFFFF)
#define MIS_TC1CVR_tc1cvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define MIS_TC1CVR_tc1cvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define MIS_TC1CVR_get_tc1cvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define MIS_TC2CVR                                                                   0x1801B514
#define MIS_TC2CVR_reg_addr                                                          "0xB801B514"
#define MIS_TC2CVR_reg                                                               0xB801B514
#define set_MIS_TC2CVR_reg(data)   (*((volatile unsigned int*) MIS_TC2CVR_reg)=data)
#define get_MIS_TC2CVR_reg   (*((volatile unsigned int*) MIS_TC2CVR_reg))
#define MIS_TC2CVR_inst_adr                                                          "0x0045"
#define MIS_TC2CVR_inst                                                              0x0045
#define MIS_TC2CVR_tc2vr_shift                                                       (0)
#define MIS_TC2CVR_tc2vr_mask                                                        (0xFFFFFFFF)
#define MIS_TC2CVR_tc2vr(data)                                                       (0xFFFFFFFF&((data)<<0))
#define MIS_TC2CVR_tc2vr_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define MIS_TC2CVR_get_tc2vr(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define MIS_TC0CR                                                                    0x1801B518
#define MIS_TC0CR_reg_addr                                                           "0xB801B518"
#define MIS_TC0CR_reg                                                                0xB801B518
#define set_MIS_TC0CR_reg(data)   (*((volatile unsigned int*) MIS_TC0CR_reg)=data)
#define get_MIS_TC0CR_reg   (*((volatile unsigned int*) MIS_TC0CR_reg))
#define MIS_TC0CR_inst_adr                                                           "0x0046"
#define MIS_TC0CR_inst                                                               0x0046
#define MIS_TC0CR_tc0en_shift                                                        (31)
#define MIS_TC0CR_tc0en_mask                                                         (0x80000000)
#define MIS_TC0CR_tc0en(data)                                                        (0x80000000&((data)<<31))
#define MIS_TC0CR_tc0en_src(data)                                                    ((0x80000000&(data))>>31)
#define MIS_TC0CR_get_tc0en(data)                                                    ((0x80000000&(data))>>31)
#define MIS_TC0CR_tc0mode_shift                                                      (30)
#define MIS_TC0CR_tc0mode_mask                                                       (0x40000000)
#define MIS_TC0CR_tc0mode(data)                                                      (0x40000000&((data)<<30))
#define MIS_TC0CR_tc0mode_src(data)                                                  ((0x40000000&(data))>>30)
#define MIS_TC0CR_get_tc0mode(data)                                                  ((0x40000000&(data))>>30)
#define MIS_TC0CR_tc0pause_shift                                                     (29)
#define MIS_TC0CR_tc0pause_mask                                                      (0x20000000)
#define MIS_TC0CR_tc0pause(data)                                                     (0x20000000&((data)<<29))
#define MIS_TC0CR_tc0pause_src(data)                                                 ((0x20000000&(data))>>29)
#define MIS_TC0CR_get_tc0pause(data)                                                 ((0x20000000&(data))>>29)
#define MIS_TC0CR_rvda_shift                                                         (24)
#define MIS_TC0CR_rvda_mask                                                          (0x1F000000)
#define MIS_TC0CR_rvda(data)                                                         (0x1F000000&((data)<<24))
#define MIS_TC0CR_rvda_src(data)                                                     ((0x1F000000&(data))>>24)
#define MIS_TC0CR_get_rvda(data)                                                     ((0x1F000000&(data))>>24)


#define MIS_TC1CR                                                                    0x1801B51C
#define MIS_TC1CR_reg_addr                                                           "0xB801B51C"
#define MIS_TC1CR_reg                                                                0xB801B51C
#define set_MIS_TC1CR_reg(data)   (*((volatile unsigned int*) MIS_TC1CR_reg)=data)
#define get_MIS_TC1CR_reg   (*((volatile unsigned int*) MIS_TC1CR_reg))
#define MIS_TC1CR_inst_adr                                                           "0x0047"
#define MIS_TC1CR_inst                                                               0x0047
#define MIS_TC1CR_tc1en_shift                                                        (31)
#define MIS_TC1CR_tc1en_mask                                                         (0x80000000)
#define MIS_TC1CR_tc1en(data)                                                        (0x80000000&((data)<<31))
#define MIS_TC1CR_tc1en_src(data)                                                    ((0x80000000&(data))>>31)
#define MIS_TC1CR_get_tc1en(data)                                                    ((0x80000000&(data))>>31)
#define MIS_TC1CR_tc1mode_shift                                                      (30)
#define MIS_TC1CR_tc1mode_mask                                                       (0x40000000)
#define MIS_TC1CR_tc1mode(data)                                                      (0x40000000&((data)<<30))
#define MIS_TC1CR_tc1mode_src(data)                                                  ((0x40000000&(data))>>30)
#define MIS_TC1CR_get_tc1mode(data)                                                  ((0x40000000&(data))>>30)
#define MIS_TC1CR_tc1pause_shift                                                     (29)
#define MIS_TC1CR_tc1pause_mask                                                      (0x20000000)
#define MIS_TC1CR_tc1pause(data)                                                     (0x20000000&((data)<<29))
#define MIS_TC1CR_tc1pause_src(data)                                                 ((0x20000000&(data))>>29)
#define MIS_TC1CR_get_tc1pause(data)                                                 ((0x20000000&(data))>>29)
#define MIS_TC1CR_rvda_shift                                                         (24)
#define MIS_TC1CR_rvda_mask                                                          (0x1F000000)
#define MIS_TC1CR_rvda(data)                                                         (0x1F000000&((data)<<24))
#define MIS_TC1CR_rvda_src(data)                                                     ((0x1F000000&(data))>>24)
#define MIS_TC1CR_get_rvda(data)                                                     ((0x1F000000&(data))>>24)


#define MIS_TC2CR                                                                    0x1801B520
#define MIS_TC2CR_reg_addr                                                           "0xB801B520"
#define MIS_TC2CR_reg                                                                0xB801B520
#define set_MIS_TC2CR_reg(data)   (*((volatile unsigned int*) MIS_TC2CR_reg)=data)
#define get_MIS_TC2CR_reg   (*((volatile unsigned int*) MIS_TC2CR_reg))
#define MIS_TC2CR_inst_adr                                                           "0x0048"
#define MIS_TC2CR_inst                                                               0x0048
#define MIS_TC2CR_tc2en_shift                                                        (31)
#define MIS_TC2CR_tc2en_mask                                                         (0x80000000)
#define MIS_TC2CR_tc2en(data)                                                        (0x80000000&((data)<<31))
#define MIS_TC2CR_tc2en_src(data)                                                    ((0x80000000&(data))>>31)
#define MIS_TC2CR_get_tc2en(data)                                                    ((0x80000000&(data))>>31)
#define MIS_TC2CR_tc2mode_shift                                                      (30)
#define MIS_TC2CR_tc2mode_mask                                                       (0x40000000)
#define MIS_TC2CR_tc2mode(data)                                                      (0x40000000&((data)<<30))
#define MIS_TC2CR_tc2mode_src(data)                                                  ((0x40000000&(data))>>30)
#define MIS_TC2CR_get_tc2mode(data)                                                  ((0x40000000&(data))>>30)
#define MIS_TC2CR_tc2pause_shift                                                     (29)
#define MIS_TC2CR_tc2pause_mask                                                      (0x20000000)
#define MIS_TC2CR_tc2pause(data)                                                     (0x20000000&((data)<<29))
#define MIS_TC2CR_tc2pause_src(data)                                                 ((0x20000000&(data))>>29)
#define MIS_TC2CR_get_tc2pause(data)                                                 ((0x20000000&(data))>>29)
#define MIS_TC2CR_rvda_shift                                                         (24)
#define MIS_TC2CR_rvda_mask                                                          (0x1F000000)
#define MIS_TC2CR_rvda(data)                                                         (0x1F000000&((data)<<24))
#define MIS_TC2CR_rvda_src(data)                                                     ((0x1F000000&(data))>>24)
#define MIS_TC2CR_get_rvda(data)                                                     ((0x1F000000&(data))>>24)


#define MIS_TC0ICR                                                                   0x1801B524
#define MIS_TC0ICR_reg_addr                                                          "0xB801B524"
#define MIS_TC0ICR_reg                                                               0xB801B524
#define set_MIS_TC0ICR_reg(data)   (*((volatile unsigned int*) MIS_TC0ICR_reg)=data)
#define get_MIS_TC0ICR_reg   (*((volatile unsigned int*) MIS_TC0ICR_reg))
#define MIS_TC0ICR_inst_adr                                                          "0x0049"
#define MIS_TC0ICR_inst                                                              0x0049
#define MIS_TC0ICR_tc0ie_shift                                                       (31)
#define MIS_TC0ICR_tc0ie_mask                                                        (0x80000000)
#define MIS_TC0ICR_tc0ie(data)                                                       (0x80000000&((data)<<31))
#define MIS_TC0ICR_tc0ie_src(data)                                                   ((0x80000000&(data))>>31)
#define MIS_TC0ICR_get_tc0ie(data)                                                   ((0x80000000&(data))>>31)


#define MIS_TC1ICR                                                                   0x1801B528
#define MIS_TC1ICR_reg_addr                                                          "0xB801B528"
#define MIS_TC1ICR_reg                                                               0xB801B528
#define set_MIS_TC1ICR_reg(data)   (*((volatile unsigned int*) MIS_TC1ICR_reg)=data)
#define get_MIS_TC1ICR_reg   (*((volatile unsigned int*) MIS_TC1ICR_reg))
#define MIS_TC1ICR_inst_adr                                                          "0x004A"
#define MIS_TC1ICR_inst                                                              0x004A
#define MIS_TC1ICR_tc1ie_shift                                                       (31)
#define MIS_TC1ICR_tc1ie_mask                                                        (0x80000000)
#define MIS_TC1ICR_tc1ie(data)                                                       (0x80000000&((data)<<31))
#define MIS_TC1ICR_tc1ie_src(data)                                                   ((0x80000000&(data))>>31)
#define MIS_TC1ICR_get_tc1ie(data)                                                   ((0x80000000&(data))>>31)


#define MIS_TC2ICR                                                                   0x1801B52C
#define MIS_TC2ICR_reg_addr                                                          "0xB801B52C"
#define MIS_TC2ICR_reg                                                               0xB801B52C
#define set_MIS_TC2ICR_reg(data)   (*((volatile unsigned int*) MIS_TC2ICR_reg)=data)
#define get_MIS_TC2ICR_reg   (*((volatile unsigned int*) MIS_TC2ICR_reg))
#define MIS_TC2ICR_inst_adr                                                          "0x004B"
#define MIS_TC2ICR_inst                                                              0x004B
#define MIS_TC2ICR_tc2ie_shift                                                       (31)
#define MIS_TC2ICR_tc2ie_mask                                                        (0x80000000)
#define MIS_TC2ICR_tc2ie(data)                                                       (0x80000000&((data)<<31))
#define MIS_TC2ICR_tc2ie_src(data)                                                   ((0x80000000&(data))>>31)
#define MIS_TC2ICR_get_tc2ie(data)                                                   ((0x80000000&(data))>>31)


#define MIS_CLK90K_CTRL                                                              0x1801B538
#define MIS_CLK90K_CTRL_reg_addr                                                     "0xB801B538"
#define MIS_CLK90K_CTRL_reg                                                          0xB801B538
#define set_MIS_CLK90K_CTRL_reg(data)   (*((volatile unsigned int*) MIS_CLK90K_CTRL_reg)=data)
#define get_MIS_CLK90K_CTRL_reg   (*((volatile unsigned int*) MIS_CLK90K_CTRL_reg))
#define MIS_CLK90K_CTRL_inst_adr                                                     "0x004E"
#define MIS_CLK90K_CTRL_inst                                                         0x004E
#define MIS_CLK90K_CTRL_en_shift                                                     (0)
#define MIS_CLK90K_CTRL_en_mask                                                      (0x00000001)
#define MIS_CLK90K_CTRL_en(data)                                                     (0x00000001&((data)<<0))
#define MIS_CLK90K_CTRL_en_src(data)                                                 ((0x00000001&(data))>>0)
#define MIS_CLK90K_CTRL_get_en(data)                                                 ((0x00000001&(data))>>0)


#define MIS_SCPU_CLK27M_90K                                                          0x1801B53C
#define MIS_SCPU_CLK27M_90K_reg_addr                                                 "0xB801B53C"
#define MIS_SCPU_CLK27M_90K_reg                                                      0xB801B53C
#define set_MIS_SCPU_CLK27M_90K_reg(data)   (*((volatile unsigned int*) MIS_SCPU_CLK27M_90K_reg)=data)
#define get_MIS_SCPU_CLK27M_90K_reg   (*((volatile unsigned int*) MIS_SCPU_CLK27M_90K_reg))
#define MIS_SCPU_CLK27M_90K_inst_adr                                                 "0x004F"
#define MIS_SCPU_CLK27M_90K_inst                                                     0x004F
#define MIS_SCPU_CLK27M_90K_cnt_shift                                                (0)
#define MIS_SCPU_CLK27M_90K_cnt_mask                                                 (0x000001FF)
#define MIS_SCPU_CLK27M_90K_cnt(data)                                                (0x000001FF&((data)<<0))
#define MIS_SCPU_CLK27M_90K_cnt_src(data)                                            ((0x000001FF&(data))>>0)
#define MIS_SCPU_CLK27M_90K_get_cnt(data)                                            ((0x000001FF&(data))>>0)


#define MIS_SCPU_CLK90K_LO                                                           0x1801B540
#define MIS_SCPU_CLK90K_LO_reg_addr                                                  "0xB801B540"
#define MIS_SCPU_CLK90K_LO_reg                                                       0xB801B540
#define set_MIS_SCPU_CLK90K_LO_reg(data)   (*((volatile unsigned int*) MIS_SCPU_CLK90K_LO_reg)=data)
#define get_MIS_SCPU_CLK90K_LO_reg   (*((volatile unsigned int*) MIS_SCPU_CLK90K_LO_reg))
#define MIS_SCPU_CLK90K_LO_inst_adr                                                  "0x0050"
#define MIS_SCPU_CLK90K_LO_inst                                                      0x0050
#define MIS_SCPU_CLK90K_LO_val_shift                                                 (0)
#define MIS_SCPU_CLK90K_LO_val_mask                                                  (0xFFFFFFFF)
#define MIS_SCPU_CLK90K_LO_val(data)                                                 (0xFFFFFFFF&((data)<<0))
#define MIS_SCPU_CLK90K_LO_val_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define MIS_SCPU_CLK90K_LO_get_val(data)                                             ((0xFFFFFFFF&(data))>>0)


#define MIS_SCPU_CLK90K_HI                                                           0x1801B544
#define MIS_SCPU_CLK90K_HI_reg_addr                                                  "0xB801B544"
#define MIS_SCPU_CLK90K_HI_reg                                                       0xB801B544
#define set_MIS_SCPU_CLK90K_HI_reg(data)   (*((volatile unsigned int*) MIS_SCPU_CLK90K_HI_reg)=data)
#define get_MIS_SCPU_CLK90K_HI_reg   (*((volatile unsigned int*) MIS_SCPU_CLK90K_HI_reg))
#define MIS_SCPU_CLK90K_HI_inst_adr                                                  "0x0051"
#define MIS_SCPU_CLK90K_HI_inst                                                      0x0051
#define MIS_SCPU_CLK90K_HI_val_shift                                                 (0)
#define MIS_SCPU_CLK90K_HI_val_mask                                                  (0x0000FFFF)
#define MIS_SCPU_CLK90K_HI_val(data)                                                 (0x0000FFFF&((data)<<0))
#define MIS_SCPU_CLK90K_HI_val_src(data)                                             ((0x0000FFFF&(data))>>0)
#define MIS_SCPU_CLK90K_HI_get_val(data)                                             ((0x0000FFFF&(data))>>0)


#define MIS_ACPU_CLK27M_90K                                                          0x1801B548
#define MIS_ACPU_CLK27M_90K_reg_addr                                                 "0xB801B548"
#define MIS_ACPU_CLK27M_90K_reg                                                      0xB801B548
#define set_MIS_ACPU_CLK27M_90K_reg(data)   (*((volatile unsigned int*) MIS_ACPU_CLK27M_90K_reg)=data)
#define get_MIS_ACPU_CLK27M_90K_reg   (*((volatile unsigned int*) MIS_ACPU_CLK27M_90K_reg))
#define MIS_ACPU_CLK27M_90K_inst_adr                                                 "0x0052"
#define MIS_ACPU_CLK27M_90K_inst                                                     0x0052
#define MIS_ACPU_CLK27M_90K_cnt_shift                                                (0)
#define MIS_ACPU_CLK27M_90K_cnt_mask                                                 (0x000001FF)
#define MIS_ACPU_CLK27M_90K_cnt(data)                                                (0x000001FF&((data)<<0))
#define MIS_ACPU_CLK27M_90K_cnt_src(data)                                            ((0x000001FF&(data))>>0)
#define MIS_ACPU_CLK27M_90K_get_cnt(data)                                            ((0x000001FF&(data))>>0)


#define MIS_ACPU_CLK90K_LO                                                           0x1801B54C
#define MIS_ACPU_CLK90K_LO_reg_addr                                                  "0xB801B54C"
#define MIS_ACPU_CLK90K_LO_reg                                                       0xB801B54C
#define set_MIS_ACPU_CLK90K_LO_reg(data)   (*((volatile unsigned int*) MIS_ACPU_CLK90K_LO_reg)=data)
#define get_MIS_ACPU_CLK90K_LO_reg   (*((volatile unsigned int*) MIS_ACPU_CLK90K_LO_reg))
#define MIS_ACPU_CLK90K_LO_inst_adr                                                  "0x0053"
#define MIS_ACPU_CLK90K_LO_inst                                                      0x0053
#define MIS_ACPU_CLK90K_LO_val_shift                                                 (0)
#define MIS_ACPU_CLK90K_LO_val_mask                                                  (0xFFFFFFFF)
#define MIS_ACPU_CLK90K_LO_val(data)                                                 (0xFFFFFFFF&((data)<<0))
#define MIS_ACPU_CLK90K_LO_val_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define MIS_ACPU_CLK90K_LO_get_val(data)                                             ((0xFFFFFFFF&(data))>>0)


#define MIS_ACPU_CLK90K_HI                                                           0x1801B550
#define MIS_ACPU_CLK90K_HI_reg_addr                                                  "0xB801B550"
#define MIS_ACPU_CLK90K_HI_reg                                                       0xB801B550
#define set_MIS_ACPU_CLK90K_HI_reg(data)   (*((volatile unsigned int*) MIS_ACPU_CLK90K_HI_reg)=data)
#define get_MIS_ACPU_CLK90K_HI_reg   (*((volatile unsigned int*) MIS_ACPU_CLK90K_HI_reg))
#define MIS_ACPU_CLK90K_HI_inst_adr                                                  "0x0054"
#define MIS_ACPU_CLK90K_HI_inst                                                      0x0054
#define MIS_ACPU_CLK90K_HI_val_shift                                                 (0)
#define MIS_ACPU_CLK90K_HI_val_mask                                                  (0x0000FFFF)
#define MIS_ACPU_CLK90K_HI_val(data)                                                 (0x0000FFFF&((data)<<0))
#define MIS_ACPU_CLK90K_HI_val_src(data)                                             ((0x0000FFFF&(data))>>0)
#define MIS_ACPU_CLK90K_HI_get_val(data)                                             ((0x0000FFFF&(data))>>0)


#define MIS_PCR_CLK90K_CTRL                                                          0x1801B570
#define MIS_PCR_CLK90K_CTRL_reg_addr                                                 "0xB801B570"
#define MIS_PCR_CLK90K_CTRL_reg                                                      0xB801B570
#define set_MIS_PCR_CLK90K_CTRL_reg(data)   (*((volatile unsigned int*) MIS_PCR_CLK90K_CTRL_reg)=data)
#define get_MIS_PCR_CLK90K_CTRL_reg   (*((volatile unsigned int*) MIS_PCR_CLK90K_CTRL_reg))
#define MIS_PCR_CLK90K_CTRL_inst_adr                                                 "0x005C"
#define MIS_PCR_CLK90K_CTRL_inst                                                     0x005C
#define MIS_PCR_CLK90K_CTRL_en_shift                                                 (0)
#define MIS_PCR_CLK90K_CTRL_en_mask                                                  (0x00000001)
#define MIS_PCR_CLK90K_CTRL_en(data)                                                 (0x00000001&((data)<<0))
#define MIS_PCR_CLK90K_CTRL_en_src(data)                                             ((0x00000001&(data))>>0)
#define MIS_PCR_CLK90K_CTRL_get_en(data)                                             ((0x00000001&(data))>>0)


#define MIS_PCR_SCPU_CLK27M_90K                                                      0x1801B574
#define MIS_PCR_SCPU_CLK27M_90K_reg_addr                                             "0xB801B574"
#define MIS_PCR_SCPU_CLK27M_90K_reg                                                  0xB801B574
#define set_MIS_PCR_SCPU_CLK27M_90K_reg(data)   (*((volatile unsigned int*) MIS_PCR_SCPU_CLK27M_90K_reg)=data)
#define get_MIS_PCR_SCPU_CLK27M_90K_reg   (*((volatile unsigned int*) MIS_PCR_SCPU_CLK27M_90K_reg))
#define MIS_PCR_SCPU_CLK27M_90K_inst_adr                                             "0x005D"
#define MIS_PCR_SCPU_CLK27M_90K_inst                                                 0x005D
#define MIS_PCR_SCPU_CLK27M_90K_cnt_shift                                            (0)
#define MIS_PCR_SCPU_CLK27M_90K_cnt_mask                                             (0x000001FF)
#define MIS_PCR_SCPU_CLK27M_90K_cnt(data)                                            (0x000001FF&((data)<<0))
#define MIS_PCR_SCPU_CLK27M_90K_cnt_src(data)                                        ((0x000001FF&(data))>>0)
#define MIS_PCR_SCPU_CLK27M_90K_get_cnt(data)                                        ((0x000001FF&(data))>>0)


#define MIS_PCR_SCPU_CLK90K_LO                                                       0x1801B578
#define MIS_PCR_SCPU_CLK90K_LO_reg_addr                                              "0xB801B578"
#define MIS_PCR_SCPU_CLK90K_LO_reg                                                   0xB801B578
#define set_MIS_PCR_SCPU_CLK90K_LO_reg(data)   (*((volatile unsigned int*) MIS_PCR_SCPU_CLK90K_LO_reg)=data)
#define get_MIS_PCR_SCPU_CLK90K_LO_reg   (*((volatile unsigned int*) MIS_PCR_SCPU_CLK90K_LO_reg))
#define MIS_PCR_SCPU_CLK90K_LO_inst_adr                                              "0x005E"
#define MIS_PCR_SCPU_CLK90K_LO_inst                                                  0x005E
#define MIS_PCR_SCPU_CLK90K_LO_val_shift                                             (0)
#define MIS_PCR_SCPU_CLK90K_LO_val_mask                                              (0xFFFFFFFF)
#define MIS_PCR_SCPU_CLK90K_LO_val(data)                                             (0xFFFFFFFF&((data)<<0))
#define MIS_PCR_SCPU_CLK90K_LO_val_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define MIS_PCR_SCPU_CLK90K_LO_get_val(data)                                         ((0xFFFFFFFF&(data))>>0)


#define MIS_PCR_SCPU_CLK90K_HI                                                       0x1801B57C
#define MIS_PCR_SCPU_CLK90K_HI_reg_addr                                              "0xB801B57C"
#define MIS_PCR_SCPU_CLK90K_HI_reg                                                   0xB801B57C
#define set_MIS_PCR_SCPU_CLK90K_HI_reg(data)   (*((volatile unsigned int*) MIS_PCR_SCPU_CLK90K_HI_reg)=data)
#define get_MIS_PCR_SCPU_CLK90K_HI_reg   (*((volatile unsigned int*) MIS_PCR_SCPU_CLK90K_HI_reg))
#define MIS_PCR_SCPU_CLK90K_HI_inst_adr                                              "0x005F"
#define MIS_PCR_SCPU_CLK90K_HI_inst                                                  0x005F
#define MIS_PCR_SCPU_CLK90K_HI_val_shift                                             (0)
#define MIS_PCR_SCPU_CLK90K_HI_val_mask                                              (0x0000FFFF)
#define MIS_PCR_SCPU_CLK90K_HI_val(data)                                             (0x0000FFFF&((data)<<0))
#define MIS_PCR_SCPU_CLK90K_HI_val_src(data)                                         ((0x0000FFFF&(data))>>0)
#define MIS_PCR_SCPU_CLK90K_HI_get_val(data)                                         ((0x0000FFFF&(data))>>0)


#define MIS_PCR_ACPU_CLK27M_90K                                                      0x1801B580
#define MIS_PCR_ACPU_CLK27M_90K_reg_addr                                             "0xB801B580"
#define MIS_PCR_ACPU_CLK27M_90K_reg                                                  0xB801B580
#define set_MIS_PCR_ACPU_CLK27M_90K_reg(data)   (*((volatile unsigned int*) MIS_PCR_ACPU_CLK27M_90K_reg)=data)
#define get_MIS_PCR_ACPU_CLK27M_90K_reg   (*((volatile unsigned int*) MIS_PCR_ACPU_CLK27M_90K_reg))
#define MIS_PCR_ACPU_CLK27M_90K_inst_adr                                             "0x0060"
#define MIS_PCR_ACPU_CLK27M_90K_inst                                                 0x0060
#define MIS_PCR_ACPU_CLK27M_90K_cnt_shift                                            (0)
#define MIS_PCR_ACPU_CLK27M_90K_cnt_mask                                             (0x000001FF)
#define MIS_PCR_ACPU_CLK27M_90K_cnt(data)                                            (0x000001FF&((data)<<0))
#define MIS_PCR_ACPU_CLK27M_90K_cnt_src(data)                                        ((0x000001FF&(data))>>0)
#define MIS_PCR_ACPU_CLK27M_90K_get_cnt(data)                                        ((0x000001FF&(data))>>0)


#define MIS_PCR_ACPU_CLK90K_LO                                                       0x1801B584
#define MIS_PCR_ACPU_CLK90K_LO_reg_addr                                              "0xB801B584"
#define MIS_PCR_ACPU_CLK90K_LO_reg                                                   0xB801B584
#define set_MIS_PCR_ACPU_CLK90K_LO_reg(data)   (*((volatile unsigned int*) MIS_PCR_ACPU_CLK90K_LO_reg)=data)
#define get_MIS_PCR_ACPU_CLK90K_LO_reg   (*((volatile unsigned int*) MIS_PCR_ACPU_CLK90K_LO_reg))
#define MIS_PCR_ACPU_CLK90K_LO_inst_adr                                              "0x0061"
#define MIS_PCR_ACPU_CLK90K_LO_inst                                                  0x0061
#define MIS_PCR_ACPU_CLK90K_LO_val_shift                                             (0)
#define MIS_PCR_ACPU_CLK90K_LO_val_mask                                              (0xFFFFFFFF)
#define MIS_PCR_ACPU_CLK90K_LO_val(data)                                             (0xFFFFFFFF&((data)<<0))
#define MIS_PCR_ACPU_CLK90K_LO_val_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define MIS_PCR_ACPU_CLK90K_LO_get_val(data)                                         ((0xFFFFFFFF&(data))>>0)


#define MIS_PCR_ACPU_CLK90K_HI                                                       0x1801B588
#define MIS_PCR_ACPU_CLK90K_HI_reg_addr                                              "0xB801B588"
#define MIS_PCR_ACPU_CLK90K_HI_reg                                                   0xB801B588
#define set_MIS_PCR_ACPU_CLK90K_HI_reg(data)   (*((volatile unsigned int*) MIS_PCR_ACPU_CLK90K_HI_reg)=data)
#define get_MIS_PCR_ACPU_CLK90K_HI_reg   (*((volatile unsigned int*) MIS_PCR_ACPU_CLK90K_HI_reg))
#define MIS_PCR_ACPU_CLK90K_HI_inst_adr                                              "0x0062"
#define MIS_PCR_ACPU_CLK90K_HI_inst                                                  0x0062
#define MIS_PCR_ACPU_CLK90K_HI_val_shift                                             (0)
#define MIS_PCR_ACPU_CLK90K_HI_val_mask                                              (0x0000FFFF)
#define MIS_PCR_ACPU_CLK90K_HI_val(data)                                             (0x0000FFFF&((data)<<0))
#define MIS_PCR_ACPU_CLK90K_HI_val_src(data)                                         ((0x0000FFFF&(data))>>0)
#define MIS_PCR_ACPU_CLK90K_HI_get_val(data)                                         ((0x0000FFFF&(data))>>0)


#define MIS_TCWCR                                                                    0x1801B5B0
#define MIS_TCWCR_reg_addr                                                           "0xB801B5B0"
#define MIS_TCWCR_reg                                                                0xB801B5B0
#define set_MIS_TCWCR_reg(data)   (*((volatile unsigned int*) MIS_TCWCR_reg)=data)
#define get_MIS_TCWCR_reg   (*((volatile unsigned int*) MIS_TCWCR_reg))
#define MIS_TCWCR_inst_adr                                                           "0x006C"
#define MIS_TCWCR_inst                                                               0x006C
#define MIS_TCWCR_wd_int_en_shift                                                    (31)
#define MIS_TCWCR_wd_int_en_mask                                                     (0x80000000)
#define MIS_TCWCR_wd_int_en(data)                                                    (0x80000000&((data)<<31))
#define MIS_TCWCR_wd_int_en_src(data)                                                ((0x80000000&(data))>>31)
#define MIS_TCWCR_get_wd_int_en(data)                                                ((0x80000000&(data))>>31)
#define MIS_TCWCR_nmic_shift                                                         (12)
#define MIS_TCWCR_nmic_mask                                                          (0x0000F000)
#define MIS_TCWCR_nmic(data)                                                         (0x0000F000&((data)<<12))
#define MIS_TCWCR_nmic_src(data)                                                     ((0x0000F000&(data))>>12)
#define MIS_TCWCR_get_nmic(data)                                                     ((0x0000F000&(data))>>12)
#define MIS_TCWCR_wdc_shift                                                          (8)
#define MIS_TCWCR_wdc_mask                                                           (0x00000F00)
#define MIS_TCWCR_wdc(data)                                                          (0x00000F00&((data)<<8))
#define MIS_TCWCR_wdc_src(data)                                                      ((0x00000F00&(data))>>8)
#define MIS_TCWCR_get_wdc(data)                                                      ((0x00000F00&(data))>>8)
#define MIS_TCWCR_wden_shift                                                         (0)
#define MIS_TCWCR_wden_mask                                                          (0x000000FF)
#define MIS_TCWCR_wden(data)                                                         (0x000000FF&((data)<<0))
#define MIS_TCWCR_wden_src(data)                                                     ((0x000000FF&(data))>>0)
#define MIS_TCWCR_get_wden(data)                                                     ((0x000000FF&(data))>>0)


#define MIS_TCWTR                                                                    0x1801B5B4
#define MIS_TCWTR_reg_addr                                                           "0xB801B5B4"
#define MIS_TCWTR_reg                                                                0xB801B5B4
#define set_MIS_TCWTR_reg(data)   (*((volatile unsigned int*) MIS_TCWTR_reg)=data)
#define get_MIS_TCWTR_reg   (*((volatile unsigned int*) MIS_TCWTR_reg))
#define MIS_TCWTR_inst_adr                                                           "0x006D"
#define MIS_TCWTR_inst                                                               0x006D
#define MIS_TCWTR_wdclr_shift                                                        (0)
#define MIS_TCWTR_wdclr_mask                                                         (0x00000001)
#define MIS_TCWTR_wdclr(data)                                                        (0x00000001&((data)<<0))
#define MIS_TCWTR_wdclr_src(data)                                                    ((0x00000001&(data))>>0)
#define MIS_TCWTR_get_wdclr(data)                                                    ((0x00000001&(data))>>0)


#define MIS_TCWNMI                                                                   0x1801B5B8
#define MIS_TCWNMI_reg_addr                                                          "0xB801B5B8"
#define MIS_TCWNMI_reg                                                               0xB801B5B8
#define set_MIS_TCWNMI_reg(data)   (*((volatile unsigned int*) MIS_TCWNMI_reg)=data)
#define get_MIS_TCWNMI_reg   (*((volatile unsigned int*) MIS_TCWNMI_reg))
#define MIS_TCWNMI_inst_adr                                                          "0x006E"
#define MIS_TCWNMI_inst                                                              0x006E
#define MIS_TCWNMI_sel_shift                                                         (0)
#define MIS_TCWNMI_sel_mask                                                          (0xFFFFFFFF)
#define MIS_TCWNMI_sel(data)                                                         (0xFFFFFFFF&((data)<<0))
#define MIS_TCWNMI_sel_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define MIS_TCWNMI_get_sel(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define MIS_TCWOV                                                                    0x1801B5BC
#define MIS_TCWOV_reg_addr                                                           "0xB801B5BC"
#define MIS_TCWOV_reg                                                                0xB801B5BC
#define set_MIS_TCWOV_reg(data)   (*((volatile unsigned int*) MIS_TCWOV_reg)=data)
#define get_MIS_TCWOV_reg   (*((volatile unsigned int*) MIS_TCWOV_reg))
#define MIS_TCWOV_inst_adr                                                           "0x006F"
#define MIS_TCWOV_inst                                                               0x006F
#define MIS_TCWOV_sel_shift                                                          (0)
#define MIS_TCWOV_sel_mask                                                           (0xFFFFFFFF)
#define MIS_TCWOV_sel(data)                                                          (0xFFFFFFFF&((data)<<0))
#define MIS_TCWOV_sel_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define MIS_TCWOV_get_sel(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define MIS_TCWCR_SWC                                                                0x1801B5C0
#define MIS_TCWCR_SWC_reg_addr                                                       "0xB801B5C0"
#define MIS_TCWCR_SWC_reg                                                            0xB801B5C0
#define set_MIS_TCWCR_SWC_reg(data)   (*((volatile unsigned int*) MIS_TCWCR_SWC_reg)=data)
#define get_MIS_TCWCR_SWC_reg   (*((volatile unsigned int*) MIS_TCWCR_SWC_reg))
#define MIS_TCWCR_SWC_inst_adr                                                       "0x0070"
#define MIS_TCWCR_SWC_inst                                                           0x0070
#define MIS_TCWCR_SWC_wd_int_en_shift                                                (31)
#define MIS_TCWCR_SWC_wd_int_en_mask                                                 (0x80000000)
#define MIS_TCWCR_SWC_wd_int_en(data)                                                (0x80000000&((data)<<31))
#define MIS_TCWCR_SWC_wd_int_en_src(data)                                            ((0x80000000&(data))>>31)
#define MIS_TCWCR_SWC_get_wd_int_en(data)                                            ((0x80000000&(data))>>31)
#define MIS_TCWCR_SWC_nmic_shift                                                     (12)
#define MIS_TCWCR_SWC_nmic_mask                                                      (0x0000F000)
#define MIS_TCWCR_SWC_nmic(data)                                                     (0x0000F000&((data)<<12))
#define MIS_TCWCR_SWC_nmic_src(data)                                                 ((0x0000F000&(data))>>12)
#define MIS_TCWCR_SWC_get_nmic(data)                                                 ((0x0000F000&(data))>>12)
#define MIS_TCWCR_SWC_wdc_shift                                                      (8)
#define MIS_TCWCR_SWC_wdc_mask                                                       (0x00000F00)
#define MIS_TCWCR_SWC_wdc(data)                                                      (0x00000F00&((data)<<8))
#define MIS_TCWCR_SWC_wdc_src(data)                                                  ((0x00000F00&(data))>>8)
#define MIS_TCWCR_SWC_get_wdc(data)                                                  ((0x00000F00&(data))>>8)
#define MIS_TCWCR_SWC_wden_shift                                                     (0)
#define MIS_TCWCR_SWC_wden_mask                                                      (0x000000FF)
#define MIS_TCWCR_SWC_wden(data)                                                     (0x000000FF&((data)<<0))
#define MIS_TCWCR_SWC_wden_src(data)                                                 ((0x000000FF&(data))>>0)
#define MIS_TCWCR_SWC_get_wden(data)                                                 ((0x000000FF&(data))>>0)


#define MIS_TCWTR_SWC                                                                0x1801B5C4
#define MIS_TCWTR_SWC_reg_addr                                                       "0xB801B5C4"
#define MIS_TCWTR_SWC_reg                                                            0xB801B5C4
#define set_MIS_TCWTR_SWC_reg(data)   (*((volatile unsigned int*) MIS_TCWTR_SWC_reg)=data)
#define get_MIS_TCWTR_SWC_reg   (*((volatile unsigned int*) MIS_TCWTR_SWC_reg))
#define MIS_TCWTR_SWC_inst_adr                                                       "0x0071"
#define MIS_TCWTR_SWC_inst                                                           0x0071
#define MIS_TCWTR_SWC_wdclr_shift                                                    (0)
#define MIS_TCWTR_SWC_wdclr_mask                                                     (0x00000001)
#define MIS_TCWTR_SWC_wdclr(data)                                                    (0x00000001&((data)<<0))
#define MIS_TCWTR_SWC_wdclr_src(data)                                                ((0x00000001&(data))>>0)
#define MIS_TCWTR_SWC_get_wdclr(data)                                                ((0x00000001&(data))>>0)


#define MIS_TCWNMI_SWC                                                               0x1801B5C8
#define MIS_TCWNMI_SWC_reg_addr                                                      "0xB801B5C8"
#define MIS_TCWNMI_SWC_reg                                                           0xB801B5C8
#define set_MIS_TCWNMI_SWC_reg(data)   (*((volatile unsigned int*) MIS_TCWNMI_SWC_reg)=data)
#define get_MIS_TCWNMI_SWC_reg   (*((volatile unsigned int*) MIS_TCWNMI_SWC_reg))
#define MIS_TCWNMI_SWC_inst_adr                                                      "0x0072"
#define MIS_TCWNMI_SWC_inst                                                          0x0072
#define MIS_TCWNMI_SWC_sel_shift                                                     (0)
#define MIS_TCWNMI_SWC_sel_mask                                                      (0xFFFFFFFF)
#define MIS_TCWNMI_SWC_sel(data)                                                     (0xFFFFFFFF&((data)<<0))
#define MIS_TCWNMI_SWC_sel_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define MIS_TCWNMI_SWC_get_sel(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define MIS_TCWOV_SWC                                                                0x1801B5CC
#define MIS_TCWOV_SWC_reg_addr                                                       "0xB801B5CC"
#define MIS_TCWOV_SWC_reg                                                            0xB801B5CC
#define set_MIS_TCWOV_SWC_reg(data)   (*((volatile unsigned int*) MIS_TCWOV_SWC_reg)=data)
#define get_MIS_TCWOV_SWC_reg   (*((volatile unsigned int*) MIS_TCWOV_SWC_reg))
#define MIS_TCWOV_SWC_inst_adr                                                       "0x0073"
#define MIS_TCWOV_SWC_inst                                                           0x0073
#define MIS_TCWOV_SWC_sel_shift                                                      (0)
#define MIS_TCWOV_SWC_sel_mask                                                       (0xFFFFFFFF)
#define MIS_TCWOV_SWC_sel(data)                                                      (0xFFFFFFFF&((data)<<0))
#define MIS_TCWOV_SWC_sel_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define MIS_TCWOV_SWC_get_sel(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define MIS_RTCSEC                                                                   0x1801B600
#define MIS_RTCSEC_reg_addr                                                          "0xB801B600"
#define MIS_RTCSEC_reg                                                               0xB801B600
#define set_MIS_RTCSEC_reg(data)   (*((volatile unsigned int*) MIS_RTCSEC_reg)=data)
#define get_MIS_RTCSEC_reg   (*((volatile unsigned int*) MIS_RTCSEC_reg))
#define MIS_RTCSEC_inst_adr                                                          "0x0080"
#define MIS_RTCSEC_inst                                                              0x0080
#define MIS_RTCSEC_rtcsec_shift                                                      (0)
#define MIS_RTCSEC_rtcsec_mask                                                       (0x0000007F)
#define MIS_RTCSEC_rtcsec(data)                                                      (0x0000007F&((data)<<0))
#define MIS_RTCSEC_rtcsec_src(data)                                                  ((0x0000007F&(data))>>0)
#define MIS_RTCSEC_get_rtcsec(data)                                                  ((0x0000007F&(data))>>0)


#define MIS_RTCMIN                                                                   0x1801B604
#define MIS_RTCMIN_reg_addr                                                          "0xB801B604"
#define MIS_RTCMIN_reg                                                               0xB801B604
#define set_MIS_RTCMIN_reg(data)   (*((volatile unsigned int*) MIS_RTCMIN_reg)=data)
#define get_MIS_RTCMIN_reg   (*((volatile unsigned int*) MIS_RTCMIN_reg))
#define MIS_RTCMIN_inst_adr                                                          "0x0081"
#define MIS_RTCMIN_inst                                                              0x0081
#define MIS_RTCMIN_rtcmin_shift                                                      (0)
#define MIS_RTCMIN_rtcmin_mask                                                       (0x0000003F)
#define MIS_RTCMIN_rtcmin(data)                                                      (0x0000003F&((data)<<0))
#define MIS_RTCMIN_rtcmin_src(data)                                                  ((0x0000003F&(data))>>0)
#define MIS_RTCMIN_get_rtcmin(data)                                                  ((0x0000003F&(data))>>0)


#define MIS_RTCHR                                                                    0x1801B608
#define MIS_RTCHR_reg_addr                                                           "0xB801B608"
#define MIS_RTCHR_reg                                                                0xB801B608
#define set_MIS_RTCHR_reg(data)   (*((volatile unsigned int*) MIS_RTCHR_reg)=data)
#define get_MIS_RTCHR_reg   (*((volatile unsigned int*) MIS_RTCHR_reg))
#define MIS_RTCHR_inst_adr                                                           "0x0082"
#define MIS_RTCHR_inst                                                               0x0082
#define MIS_RTCHR_rtchr_shift                                                        (0)
#define MIS_RTCHR_rtchr_mask                                                         (0x0000001F)
#define MIS_RTCHR_rtchr(data)                                                        (0x0000001F&((data)<<0))
#define MIS_RTCHR_rtchr_src(data)                                                    ((0x0000001F&(data))>>0)
#define MIS_RTCHR_get_rtchr(data)                                                    ((0x0000001F&(data))>>0)


#define MIS_RTCDATE1                                                                 0x1801B60C
#define MIS_RTCDATE1_reg_addr                                                        "0xB801B60C"
#define MIS_RTCDATE1_reg                                                             0xB801B60C
#define set_MIS_RTCDATE1_reg(data)   (*((volatile unsigned int*) MIS_RTCDATE1_reg)=data)
#define get_MIS_RTCDATE1_reg   (*((volatile unsigned int*) MIS_RTCDATE1_reg))
#define MIS_RTCDATE1_inst_adr                                                        "0x0083"
#define MIS_RTCDATE1_inst                                                            0x0083
#define MIS_RTCDATE1_rtcdate1_shift                                                  (0)
#define MIS_RTCDATE1_rtcdate1_mask                                                   (0x000000FF)
#define MIS_RTCDATE1_rtcdate1(data)                                                  (0x000000FF&((data)<<0))
#define MIS_RTCDATE1_rtcdate1_src(data)                                              ((0x000000FF&(data))>>0)
#define MIS_RTCDATE1_get_rtcdate1(data)                                              ((0x000000FF&(data))>>0)


#define MIS_RTCDATE2                                                                 0x1801B610
#define MIS_RTCDATE2_reg_addr                                                        "0xB801B610"
#define MIS_RTCDATE2_reg                                                             0xB801B610
#define set_MIS_RTCDATE2_reg(data)   (*((volatile unsigned int*) MIS_RTCDATE2_reg)=data)
#define get_MIS_RTCDATE2_reg   (*((volatile unsigned int*) MIS_RTCDATE2_reg))
#define MIS_RTCDATE2_inst_adr                                                        "0x0084"
#define MIS_RTCDATE2_inst                                                            0x0084
#define MIS_RTCDATE2_rtcdate2_shift                                                  (0)
#define MIS_RTCDATE2_rtcdate2_mask                                                   (0x0000007F)
#define MIS_RTCDATE2_rtcdate2(data)                                                  (0x0000007F&((data)<<0))
#define MIS_RTCDATE2_rtcdate2_src(data)                                              ((0x0000007F&(data))>>0)
#define MIS_RTCDATE2_get_rtcdate2(data)                                              ((0x0000007F&(data))>>0)


#define MIS_ALMMIN                                                                   0x1801B614
#define MIS_ALMMIN_reg_addr                                                          "0xB801B614"
#define MIS_ALMMIN_reg                                                               0xB801B614
#define set_MIS_ALMMIN_reg(data)   (*((volatile unsigned int*) MIS_ALMMIN_reg)=data)
#define get_MIS_ALMMIN_reg   (*((volatile unsigned int*) MIS_ALMMIN_reg))
#define MIS_ALMMIN_inst_adr                                                          "0x0085"
#define MIS_ALMMIN_inst                                                              0x0085
#define MIS_ALMMIN_almmin_shift                                                      (0)
#define MIS_ALMMIN_almmin_mask                                                       (0x0000003F)
#define MIS_ALMMIN_almmin(data)                                                      (0x0000003F&((data)<<0))
#define MIS_ALMMIN_almmin_src(data)                                                  ((0x0000003F&(data))>>0)
#define MIS_ALMMIN_get_almmin(data)                                                  ((0x0000003F&(data))>>0)


#define MIS_ALMHR                                                                    0x1801B618
#define MIS_ALMHR_reg_addr                                                           "0xB801B618"
#define MIS_ALMHR_reg                                                                0xB801B618
#define set_MIS_ALMHR_reg(data)   (*((volatile unsigned int*) MIS_ALMHR_reg)=data)
#define get_MIS_ALMHR_reg   (*((volatile unsigned int*) MIS_ALMHR_reg))
#define MIS_ALMHR_inst_adr                                                           "0x0086"
#define MIS_ALMHR_inst                                                               0x0086
#define MIS_ALMHR_almhr_shift                                                        (0)
#define MIS_ALMHR_almhr_mask                                                         (0x0000001F)
#define MIS_ALMHR_almhr(data)                                                        (0x0000001F&((data)<<0))
#define MIS_ALMHR_almhr_src(data)                                                    ((0x0000001F&(data))>>0)
#define MIS_ALMHR_get_almhr(data)                                                    ((0x0000001F&(data))>>0)


#define MIS_ALMDATE1                                                                 0x1801B61C
#define MIS_ALMDATE1_reg_addr                                                        "0xB801B61C"
#define MIS_ALMDATE1_reg                                                             0xB801B61C
#define set_MIS_ALMDATE1_reg(data)   (*((volatile unsigned int*) MIS_ALMDATE1_reg)=data)
#define get_MIS_ALMDATE1_reg   (*((volatile unsigned int*) MIS_ALMDATE1_reg))
#define MIS_ALMDATE1_inst_adr                                                        "0x0087"
#define MIS_ALMDATE1_inst                                                            0x0087
#define MIS_ALMDATE1_almdate1_shift                                                  (0)
#define MIS_ALMDATE1_almdate1_mask                                                   (0x000000FF)
#define MIS_ALMDATE1_almdate1(data)                                                  (0x000000FF&((data)<<0))
#define MIS_ALMDATE1_almdate1_src(data)                                              ((0x000000FF&(data))>>0)
#define MIS_ALMDATE1_get_almdate1(data)                                              ((0x000000FF&(data))>>0)


#define MIS_ALMDATE2                                                                 0x1801B620
#define MIS_ALMDATE2_reg_addr                                                        "0xB801B620"
#define MIS_ALMDATE2_reg                                                             0xB801B620
#define set_MIS_ALMDATE2_reg(data)   (*((volatile unsigned int*) MIS_ALMDATE2_reg)=data)
#define get_MIS_ALMDATE2_reg   (*((volatile unsigned int*) MIS_ALMDATE2_reg))
#define MIS_ALMDATE2_inst_adr                                                        "0x0088"
#define MIS_ALMDATE2_inst                                                            0x0088
#define MIS_ALMDATE2_almdate2_shift                                                  (0)
#define MIS_ALMDATE2_almdate2_mask                                                   (0x0000007F)
#define MIS_ALMDATE2_almdate2(data)                                                  (0x0000007F&((data)<<0))
#define MIS_ALMDATE2_almdate2_src(data)                                              ((0x0000007F&(data))>>0)
#define MIS_ALMDATE2_get_almdate2(data)                                              ((0x0000007F&(data))>>0)


#define MIS_RTCSTOP                                                                  0x1801B624
#define MIS_RTCSTOP_reg_addr                                                         "0xB801B624"
#define MIS_RTCSTOP_reg                                                              0xB801B624
#define set_MIS_RTCSTOP_reg(data)   (*((volatile unsigned int*) MIS_RTCSTOP_reg)=data)
#define get_MIS_RTCSTOP_reg   (*((volatile unsigned int*) MIS_RTCSTOP_reg))
#define MIS_RTCSTOP_inst_adr                                                         "0x0089"
#define MIS_RTCSTOP_inst                                                             0x0089
#define MIS_RTCSTOP_vref_shift                                                       (1)
#define MIS_RTCSTOP_vref_mask                                                        (0x00000006)
#define MIS_RTCSTOP_vref(data)                                                       (0x00000006&((data)<<1))
#define MIS_RTCSTOP_vref_src(data)                                                   ((0x00000006&(data))>>1)
#define MIS_RTCSTOP_get_vref(data)                                                   ((0x00000006&(data))>>1)
#define MIS_RTCSTOP_rtcstop_shift                                                    (0)
#define MIS_RTCSTOP_rtcstop_mask                                                     (0x00000001)
#define MIS_RTCSTOP_rtcstop(data)                                                    (0x00000001&((data)<<0))
#define MIS_RTCSTOP_rtcstop_src(data)                                                ((0x00000001&(data))>>0)
#define MIS_RTCSTOP_get_rtcstop(data)                                                ((0x00000001&(data))>>0)


#define MIS_RTCACR                                                                   0x1801B628
#define MIS_RTCACR_reg_addr                                                          "0xB801B628"
#define MIS_RTCACR_reg                                                               0xB801B628
#define set_MIS_RTCACR_reg(data)   (*((volatile unsigned int*) MIS_RTCACR_reg)=data)
#define get_MIS_RTCACR_reg   (*((volatile unsigned int*) MIS_RTCACR_reg))
#define MIS_RTCACR_inst_adr                                                          "0x008A"
#define MIS_RTCACR_inst                                                              0x008A
#define MIS_RTCACR_rtcpwr_shift                                                      (7)
#define MIS_RTCACR_rtcpwr_mask                                                       (0x00000080)
#define MIS_RTCACR_rtcpwr(data)                                                      (0x00000080&((data)<<7))
#define MIS_RTCACR_rtcpwr_src(data)                                                  ((0x00000080&(data))>>7)
#define MIS_RTCACR_get_rtcpwr(data)                                                  ((0x00000080&(data))>>7)
#define MIS_RTCACR_co_shift                                                          (5)
#define MIS_RTCACR_co_mask                                                           (0x00000060)
#define MIS_RTCACR_co(data)                                                          (0x00000060&((data)<<5))
#define MIS_RTCACR_co_src(data)                                                      ((0x00000060&(data))>>5)
#define MIS_RTCACR_get_co(data)                                                      ((0x00000060&(data))>>5)
#define MIS_RTCACR_ci_shift                                                          (3)
#define MIS_RTCACR_ci_mask                                                           (0x00000018)
#define MIS_RTCACR_ci(data)                                                          (0x00000018&((data)<<3))
#define MIS_RTCACR_ci_src(data)                                                      ((0x00000018&(data))>>3)
#define MIS_RTCACR_get_ci(data)                                                      ((0x00000018&(data))>>3)
#define MIS_RTCACR_clksel_shift                                                      (2)
#define MIS_RTCACR_clksel_mask                                                       (0x00000004)
#define MIS_RTCACR_clksel(data)                                                      (0x00000004&((data)<<2))
#define MIS_RTCACR_clksel_src(data)                                                  ((0x00000004&(data))>>2)
#define MIS_RTCACR_get_clksel(data)                                                  ((0x00000004&(data))>>2)
#define MIS_RTCACR_bc_shift                                                          (0)
#define MIS_RTCACR_bc_mask                                                           (0x00000003)
#define MIS_RTCACR_bc(data)                                                          (0x00000003&((data)<<0))
#define MIS_RTCACR_bc_src(data)                                                      ((0x00000003&(data))>>0)
#define MIS_RTCACR_get_bc(data)                                                      ((0x00000003&(data))>>0)


#define MIS_RTCEN                                                                    0x1801B62C
#define MIS_RTCEN_reg_addr                                                           "0xB801B62C"
#define MIS_RTCEN_reg                                                                0xB801B62C
#define set_MIS_RTCEN_reg(data)   (*((volatile unsigned int*) MIS_RTCEN_reg)=data)
#define get_MIS_RTCEN_reg   (*((volatile unsigned int*) MIS_RTCEN_reg))
#define MIS_RTCEN_inst_adr                                                           "0x008B"
#define MIS_RTCEN_inst                                                               0x008B
#define MIS_RTCEN_rtcen_shift                                                        (0)
#define MIS_RTCEN_rtcen_mask                                                         (0x000000FF)
#define MIS_RTCEN_rtcen(data)                                                        (0x000000FF&((data)<<0))
#define MIS_RTCEN_rtcen_src(data)                                                    ((0x000000FF&(data))>>0)
#define MIS_RTCEN_get_rtcen(data)                                                    ((0x000000FF&(data))>>0)


#define MIS_RTCCR                                                                    0x1801B630
#define MIS_RTCCR_reg_addr                                                           "0xB801B630"
#define MIS_RTCCR_reg                                                                0xB801B630
#define set_MIS_RTCCR_reg(data)   (*((volatile unsigned int*) MIS_RTCCR_reg)=data)
#define get_MIS_RTCCR_reg   (*((volatile unsigned int*) MIS_RTCCR_reg))
#define MIS_RTCCR_inst_adr                                                           "0x008C"
#define MIS_RTCCR_inst                                                               0x008C
#define MIS_RTCCR_rtcrst_shift                                                       (6)
#define MIS_RTCCR_rtcrst_mask                                                        (0x00000040)
#define MIS_RTCCR_rtcrst(data)                                                       (0x00000040&((data)<<6))
#define MIS_RTCCR_rtcrst_src(data)                                                   ((0x00000040&(data))>>6)
#define MIS_RTCCR_get_rtcrst(data)                                                   ((0x00000040&(data))>>6)
#define MIS_RTCCR_dainte_shift                                                       (3)
#define MIS_RTCCR_dainte_mask                                                        (0x00000008)
#define MIS_RTCCR_dainte(data)                                                       (0x00000008&((data)<<3))
#define MIS_RTCCR_dainte_src(data)                                                   ((0x00000008&(data))>>3)
#define MIS_RTCCR_get_dainte(data)                                                   ((0x00000008&(data))>>3)
#define MIS_RTCCR_huinte_shift                                                       (2)
#define MIS_RTCCR_huinte_mask                                                        (0x00000004)
#define MIS_RTCCR_huinte(data)                                                       (0x00000004&((data)<<2))
#define MIS_RTCCR_huinte_src(data)                                                   ((0x00000004&(data))>>2)
#define MIS_RTCCR_get_huinte(data)                                                   ((0x00000004&(data))>>2)
#define MIS_RTCCR_muinte_shift                                                       (1)
#define MIS_RTCCR_muinte_mask                                                        (0x00000002)
#define MIS_RTCCR_muinte(data)                                                       (0x00000002&((data)<<1))
#define MIS_RTCCR_muinte_src(data)                                                   ((0x00000002&(data))>>1)
#define MIS_RTCCR_get_muinte(data)                                                   ((0x00000002&(data))>>1)
#define MIS_RTCCR_hsuinte_shift                                                      (0)
#define MIS_RTCCR_hsuinte_mask                                                       (0x00000001)
#define MIS_RTCCR_hsuinte(data)                                                      (0x00000001&((data)<<0))
#define MIS_RTCCR_hsuinte_src(data)                                                  ((0x00000001&(data))>>0)
#define MIS_RTCCR_get_hsuinte(data)                                                  ((0x00000001&(data))>>0)


#define MIS_ST_PAD0                                                                  0x1801BC00
#define MIS_ST_PAD0_reg_addr                                                         "0xB801BC00"
#define MIS_ST_PAD0_reg                                                              0xB801BC00
#define set_MIS_ST_PAD0_reg(data)   (*((volatile unsigned int*) MIS_ST_PAD0_reg)=data)
#define get_MIS_ST_PAD0_reg   (*((volatile unsigned int*) MIS_ST_PAD0_reg))
#define MIS_ST_PAD0_inst_adr                                                         "0x0000"
#define MIS_ST_PAD0_inst                                                             0x0000
#define MIS_ST_PAD0_pad0_active_shift                                                (31)
#define MIS_ST_PAD0_pad0_active_mask                                                 (0x80000000)
#define MIS_ST_PAD0_pad0_active(data)                                                (0x80000000&((data)<<31))
#define MIS_ST_PAD0_pad0_active_src(data)                                            ((0x80000000&(data))>>31)
#define MIS_ST_PAD0_get_pad0_active(data)                                            ((0x80000000&(data))>>31)
#define MIS_ST_PAD0_pad0_thred_shift                                                 (16)
#define MIS_ST_PAD0_pad0_thred_mask                                                  (0x00FF0000)
#define MIS_ST_PAD0_pad0_thred(data)                                                 (0x00FF0000&((data)<<16))
#define MIS_ST_PAD0_pad0_thred_src(data)                                             ((0x00FF0000&(data))>>16)
#define MIS_ST_PAD0_get_pad0_thred(data)                                             ((0x00FF0000&(data))>>16)
#define MIS_ST_PAD0_pad0_sw_shift                                                    (12)
#define MIS_ST_PAD0_pad0_sw_mask                                                     (0x0000F000)
#define MIS_ST_PAD0_pad0_sw(data)                                                    (0x0000F000&((data)<<12))
#define MIS_ST_PAD0_pad0_sw_src(data)                                                ((0x0000F000&(data))>>12)
#define MIS_ST_PAD0_get_pad0_sw(data)                                                ((0x0000F000&(data))>>12)
#define MIS_ST_PAD0_pad0_ctrl_shift                                                  (8)
#define MIS_ST_PAD0_pad0_ctrl_mask                                                   (0x00000100)
#define MIS_ST_PAD0_pad0_ctrl(data)                                                  (0x00000100&((data)<<8))
#define MIS_ST_PAD0_pad0_ctrl_src(data)                                              ((0x00000100&(data))>>8)
#define MIS_ST_PAD0_get_pad0_ctrl(data)                                              ((0x00000100&(data))>>8)
#define MIS_ST_PAD0_adc_val0_shift                                                   (0)
#define MIS_ST_PAD0_adc_val0_mask                                                    (0x0000003F)
#define MIS_ST_PAD0_adc_val0(data)                                                   (0x0000003F&((data)<<0))
#define MIS_ST_PAD0_adc_val0_src(data)                                               ((0x0000003F&(data))>>0)
#define MIS_ST_PAD0_get_adc_val0(data)                                               ((0x0000003F&(data))>>0)


#define MIS_ST_PAD1                                                                  0x1801BC04
#define MIS_ST_PAD1_reg_addr                                                         "0xB801BC04"
#define MIS_ST_PAD1_reg                                                              0xB801BC04
#define set_MIS_ST_PAD1_reg(data)   (*((volatile unsigned int*) MIS_ST_PAD1_reg)=data)
#define get_MIS_ST_PAD1_reg   (*((volatile unsigned int*) MIS_ST_PAD1_reg))
#define MIS_ST_PAD1_inst_adr                                                         "0x0001"
#define MIS_ST_PAD1_inst                                                             0x0001
#define MIS_ST_PAD1_pad1_active_shift                                                (31)
#define MIS_ST_PAD1_pad1_active_mask                                                 (0x80000000)
#define MIS_ST_PAD1_pad1_active(data)                                                (0x80000000&((data)<<31))
#define MIS_ST_PAD1_pad1_active_src(data)                                            ((0x80000000&(data))>>31)
#define MIS_ST_PAD1_get_pad1_active(data)                                            ((0x80000000&(data))>>31)
#define MIS_ST_PAD1_pad1_thred_shift                                                 (16)
#define MIS_ST_PAD1_pad1_thred_mask                                                  (0x00FF0000)
#define MIS_ST_PAD1_pad1_thred(data)                                                 (0x00FF0000&((data)<<16))
#define MIS_ST_PAD1_pad1_thred_src(data)                                             ((0x00FF0000&(data))>>16)
#define MIS_ST_PAD1_get_pad1_thred(data)                                             ((0x00FF0000&(data))>>16)
#define MIS_ST_PAD1_pad1_sw_shift                                                    (12)
#define MIS_ST_PAD1_pad1_sw_mask                                                     (0x0000F000)
#define MIS_ST_PAD1_pad1_sw(data)                                                    (0x0000F000&((data)<<12))
#define MIS_ST_PAD1_pad1_sw_src(data)                                                ((0x0000F000&(data))>>12)
#define MIS_ST_PAD1_get_pad1_sw(data)                                                ((0x0000F000&(data))>>12)
#define MIS_ST_PAD1_pad1_ctrl_shift                                                  (8)
#define MIS_ST_PAD1_pad1_ctrl_mask                                                   (0x00000100)
#define MIS_ST_PAD1_pad1_ctrl(data)                                                  (0x00000100&((data)<<8))
#define MIS_ST_PAD1_pad1_ctrl_src(data)                                              ((0x00000100&(data))>>8)
#define MIS_ST_PAD1_get_pad1_ctrl(data)                                              ((0x00000100&(data))>>8)
#define MIS_ST_PAD1_50_shift                                                         (0)
#define MIS_ST_PAD1_50_mask                                                          (0x0000003F)
#define MIS_ST_PAD1_50(data)                                                         (0x0000003F&((data)<<0))
#define MIS_ST_PAD1_50_src(data)                                                     ((0x0000003F&(data))>>0)
#define MIS_ST_PAD1_get_50(data)                                                     ((0x0000003F&(data))>>0)


#define MIS_ST_LSADC_CTRL                                                            0x1801BC20
#define MIS_ST_LSADC_CTRL_reg_addr                                                   "0xB801BC20"
#define MIS_ST_LSADC_CTRL_reg                                                        0xB801BC20
#define set_MIS_ST_LSADC_CTRL_reg(data)   (*((volatile unsigned int*) MIS_ST_LSADC_CTRL_reg)=data)
#define get_MIS_ST_LSADC_CTRL_reg   (*((volatile unsigned int*) MIS_ST_LSADC_CTRL_reg))
#define MIS_ST_LSADC_CTRL_inst_adr                                                   "0x0008"
#define MIS_ST_LSADC_CTRL_inst                                                       0x0008
#define MIS_ST_LSADC_CTRL_sel_wait_shift                                             (28)
#define MIS_ST_LSADC_CTRL_sel_wait_mask                                              (0xF0000000)
#define MIS_ST_LSADC_CTRL_sel_wait(data)                                             (0xF0000000&((data)<<28))
#define MIS_ST_LSADC_CTRL_sel_wait_src(data)                                         ((0xF0000000&(data))>>28)
#define MIS_ST_LSADC_CTRL_get_sel_wait(data)                                         ((0xF0000000&(data))>>28)
#define MIS_ST_LSADC_CTRL_sel_adc_ck_shift                                           (24)
#define MIS_ST_LSADC_CTRL_sel_adc_ck_mask                                            (0x0F000000)
#define MIS_ST_LSADC_CTRL_sel_adc_ck(data)                                           (0x0F000000&((data)<<24))
#define MIS_ST_LSADC_CTRL_sel_adc_ck_src(data)                                       ((0x0F000000&(data))>>24)
#define MIS_ST_LSADC_CTRL_get_sel_adc_ck(data)                                       ((0x0F000000&(data))>>24)
#define MIS_ST_LSADC_CTRL_debounce_cnt_shift                                         (20)
#define MIS_ST_LSADC_CTRL_debounce_cnt_mask                                          (0x00F00000)
#define MIS_ST_LSADC_CTRL_debounce_cnt(data)                                         (0x00F00000&((data)<<20))
#define MIS_ST_LSADC_CTRL_debounce_cnt_src(data)                                     ((0x00F00000&(data))>>20)
#define MIS_ST_LSADC_CTRL_get_debounce_cnt(data)                                     ((0x00F00000&(data))>>20)
#define MIS_ST_LSADC_CTRL_dout_test_in_shift                                         (8)
#define MIS_ST_LSADC_CTRL_dout_test_in_mask                                          (0x0000FF00)
#define MIS_ST_LSADC_CTRL_dout_test_in(data)                                         (0x0000FF00&((data)<<8))
#define MIS_ST_LSADC_CTRL_dout_test_in_src(data)                                     ((0x0000FF00&(data))>>8)
#define MIS_ST_LSADC_CTRL_get_dout_test_in(data)                                     ((0x0000FF00&(data))>>8)
#define MIS_ST_LSADC_CTRL_test_en_shift                                              (1)
#define MIS_ST_LSADC_CTRL_test_en_mask                                               (0x00000002)
#define MIS_ST_LSADC_CTRL_test_en(data)                                              (0x00000002&((data)<<1))
#define MIS_ST_LSADC_CTRL_test_en_src(data)                                          ((0x00000002&(data))>>1)
#define MIS_ST_LSADC_CTRL_get_test_en(data)                                          ((0x00000002&(data))>>1)
#define MIS_ST_LSADC_CTRL_enable_shift                                               (0)
#define MIS_ST_LSADC_CTRL_enable_mask                                                (0x00000001)
#define MIS_ST_LSADC_CTRL_enable(data)                                               (0x00000001&((data)<<0))
#define MIS_ST_LSADC_CTRL_enable_src(data)                                           ((0x00000001&(data))>>0)
#define MIS_ST_LSADC_CTRL_get_enable(data)                                           ((0x00000001&(data))>>0)


#define MIS_ST_LSADC_STATUS                                                          0x1801BC24
#define MIS_ST_LSADC_STATUS_reg_addr                                                 "0xB801BC24"
#define MIS_ST_LSADC_STATUS_reg                                                      0xB801BC24
#define set_MIS_ST_LSADC_STATUS_reg(data)   (*((volatile unsigned int*) MIS_ST_LSADC_STATUS_reg)=data)
#define get_MIS_ST_LSADC_STATUS_reg   (*((volatile unsigned int*) MIS_ST_LSADC_STATUS_reg))
#define MIS_ST_LSADC_STATUS_inst_adr                                                 "0x0009"
#define MIS_ST_LSADC_STATUS_inst                                                     0x0009
#define MIS_ST_LSADC_STATUS_irq_en_shift                                             (24)
#define MIS_ST_LSADC_STATUS_irq_en_mask                                              (0xFF000000)
#define MIS_ST_LSADC_STATUS_irq_en(data)                                             (0xFF000000&((data)<<24))
#define MIS_ST_LSADC_STATUS_irq_en_src(data)                                         ((0xFF000000&(data))>>24)
#define MIS_ST_LSADC_STATUS_get_irq_en(data)                                         ((0xFF000000&(data))>>24)
#define MIS_ST_LSADC_STATUS_pad_cnt_shift                                            (20)
#define MIS_ST_LSADC_STATUS_pad_cnt_mask                                             (0x00F00000)
#define MIS_ST_LSADC_STATUS_pad_cnt(data)                                            (0x00F00000&((data)<<20))
#define MIS_ST_LSADC_STATUS_pad_cnt_src(data)                                        ((0x00F00000&(data))>>20)
#define MIS_ST_LSADC_STATUS_get_pad_cnt(data)                                        ((0x00F00000&(data))>>20)
#define MIS_ST_LSADC_STATUS_adc_busy_shift                                           (19)
#define MIS_ST_LSADC_STATUS_adc_busy_mask                                            (0x00080000)
#define MIS_ST_LSADC_STATUS_adc_busy(data)                                           (0x00080000&((data)<<19))
#define MIS_ST_LSADC_STATUS_adc_busy_src(data)                                       ((0x00080000&(data))>>19)
#define MIS_ST_LSADC_STATUS_get_adc_busy(data)                                       ((0x00080000&(data))>>19)
#define MIS_ST_LSADC_STATUS_pad_ctrl_shift                                           (12)
#define MIS_ST_LSADC_STATUS_pad_ctrl_mask                                            (0x0001F000)
#define MIS_ST_LSADC_STATUS_pad_ctrl(data)                                           (0x0001F000&((data)<<12))
#define MIS_ST_LSADC_STATUS_pad_ctrl_src(data)                                       ((0x0001F000&(data))>>12)
#define MIS_ST_LSADC_STATUS_get_pad_ctrl(data)                                       ((0x0001F000&(data))>>12)
#define MIS_ST_LSADC_STATUS_pad1_status_shift                                        (1)
#define MIS_ST_LSADC_STATUS_pad1_status_mask                                         (0x00000002)
#define MIS_ST_LSADC_STATUS_pad1_status(data)                                        (0x00000002&((data)<<1))
#define MIS_ST_LSADC_STATUS_pad1_status_src(data)                                    ((0x00000002&(data))>>1)
#define MIS_ST_LSADC_STATUS_get_pad1_status(data)                                    ((0x00000002&(data))>>1)
#define MIS_ST_LSADC_STATUS_pad0_status_shift                                        (0)
#define MIS_ST_LSADC_STATUS_pad0_status_mask                                         (0x00000001)
#define MIS_ST_LSADC_STATUS_pad0_status(data)                                        (0x00000001&((data)<<0))
#define MIS_ST_LSADC_STATUS_pad0_status_src(data)                                    ((0x00000001&(data))>>0)
#define MIS_ST_LSADC_STATUS_get_pad0_status(data)                                    ((0x00000001&(data))>>0)


#define MIS_ST_LSADC_ANALOG_CTRL                                                     0x1801BC28
#define MIS_ST_LSADC_ANALOG_CTRL_reg_addr                                            "0xB801BC28"
#define MIS_ST_LSADC_ANALOG_CTRL_reg                                                 0xB801BC28
#define set_MIS_ST_LSADC_ANALOG_CTRL_reg(data)   (*((volatile unsigned int*) MIS_ST_LSADC_ANALOG_CTRL_reg)=data)
#define get_MIS_ST_LSADC_ANALOG_CTRL_reg   (*((volatile unsigned int*) MIS_ST_LSADC_ANALOG_CTRL_reg))
#define MIS_ST_LSADC_ANALOG_CTRL_inst_adr                                            "0x000A"
#define MIS_ST_LSADC_ANALOG_CTRL_inst                                                0x000A
#define MIS_ST_LSADC_ANALOG_CTRL_jd_sbias_shift                                      (16)
#define MIS_ST_LSADC_ANALOG_CTRL_jd_sbias_mask                                       (0x00030000)
#define MIS_ST_LSADC_ANALOG_CTRL_jd_sbias(data)                                      (0x00030000&((data)<<16))
#define MIS_ST_LSADC_ANALOG_CTRL_jd_sbias_src(data)                                  ((0x00030000&(data))>>16)
#define MIS_ST_LSADC_ANALOG_CTRL_get_jd_sbias(data)                                  ((0x00030000&(data))>>16)
#define MIS_ST_LSADC_ANALOG_CTRL_jd_adsbias_shift                                    (12)
#define MIS_ST_LSADC_ANALOG_CTRL_jd_adsbias_mask                                     (0x00003000)
#define MIS_ST_LSADC_ANALOG_CTRL_jd_adsbias(data)                                    (0x00003000&((data)<<12))
#define MIS_ST_LSADC_ANALOG_CTRL_jd_adsbias_src(data)                                ((0x00003000&(data))>>12)
#define MIS_ST_LSADC_ANALOG_CTRL_get_jd_adsbias(data)                                ((0x00003000&(data))>>12)
#define MIS_ST_LSADC_ANALOG_CTRL_jd_dummy_shift                                      (10)
#define MIS_ST_LSADC_ANALOG_CTRL_jd_dummy_mask                                       (0x00000C00)
#define MIS_ST_LSADC_ANALOG_CTRL_jd_dummy(data)                                      (0x00000C00&((data)<<10))
#define MIS_ST_LSADC_ANALOG_CTRL_jd_dummy_src(data)                                  ((0x00000C00&(data))>>10)
#define MIS_ST_LSADC_ANALOG_CTRL_get_jd_dummy(data)                                  ((0x00000C00&(data))>>10)
#define MIS_ST_LSADC_ANALOG_CTRL_jd_svr_shift                                        (8)
#define MIS_ST_LSADC_ANALOG_CTRL_jd_svr_mask                                         (0x00000100)
#define MIS_ST_LSADC_ANALOG_CTRL_jd_svr(data)                                        (0x00000100&((data)<<8))
#define MIS_ST_LSADC_ANALOG_CTRL_jd_svr_src(data)                                    ((0x00000100&(data))>>8)
#define MIS_ST_LSADC_ANALOG_CTRL_get_jd_svr(data)                                    ((0x00000100&(data))>>8)
#define MIS_ST_LSADC_ANALOG_CTRL_jd_adcksel_shift                                    (4)
#define MIS_ST_LSADC_ANALOG_CTRL_jd_adcksel_mask                                     (0x00000010)
#define MIS_ST_LSADC_ANALOG_CTRL_jd_adcksel(data)                                    (0x00000010&((data)<<4))
#define MIS_ST_LSADC_ANALOG_CTRL_jd_adcksel_src(data)                                ((0x00000010&(data))>>4)
#define MIS_ST_LSADC_ANALOG_CTRL_get_jd_adcksel(data)                                ((0x00000010&(data))>>4)
#define MIS_ST_LSADC_ANALOG_CTRL_jd_power_shift                                      (0)
#define MIS_ST_LSADC_ANALOG_CTRL_jd_power_mask                                       (0x00000001)
#define MIS_ST_LSADC_ANALOG_CTRL_jd_power(data)                                      (0x00000001&((data)<<0))
#define MIS_ST_LSADC_ANALOG_CTRL_jd_power_src(data)                                  ((0x00000001&(data))>>0)
#define MIS_ST_LSADC_ANALOG_CTRL_get_jd_power(data)                                  ((0x00000001&(data))>>0)


#define MIS_ST_LSADC_PERI_TOP_DEBUG                                                  0x1801BC2C
#define MIS_ST_LSADC_PERI_TOP_DEBUG_reg_addr                                         "0xB801BC2C"
#define MIS_ST_LSADC_PERI_TOP_DEBUG_reg                                              0xB801BC2C
#define set_MIS_ST_LSADC_PERI_TOP_DEBUG_reg(data)   (*((volatile unsigned int*) MIS_ST_LSADC_PERI_TOP_DEBUG_reg)=data)
#define get_MIS_ST_LSADC_PERI_TOP_DEBUG_reg   (*((volatile unsigned int*) MIS_ST_LSADC_PERI_TOP_DEBUG_reg))
#define MIS_ST_LSADC_PERI_TOP_DEBUG_inst_adr                                         "0x000B"
#define MIS_ST_LSADC_PERI_TOP_DEBUG_inst                                             0x000B
#define MIS_ST_LSADC_PERI_TOP_DEBUG_lsadc_2_ifd_data_sel_shift                       (16)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_lsadc_2_ifd_data_sel_mask                        (0x00070000)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_lsadc_2_ifd_data_sel(data)                       (0x00070000&((data)<<16))
#define MIS_ST_LSADC_PERI_TOP_DEBUG_lsadc_2_ifd_data_sel_src(data)                   ((0x00070000&(data))>>16)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_get_lsadc_2_ifd_data_sel(data)                   ((0x00070000&(data))>>16)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_power_saving_enable_shift                        (14)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_power_saving_enable_mask                         (0x00004000)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_power_saving_enable(data)                        (0x00004000&((data)<<14))
#define MIS_ST_LSADC_PERI_TOP_DEBUG_power_saving_enable_src(data)                    ((0x00004000&(data))>>14)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_get_power_saving_enable(data)                    ((0x00004000&(data))>>14)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_power_saving_cycle_time_shift                    (11)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_power_saving_cycle_time_mask                     (0x00003800)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_power_saving_cycle_time(data)                    (0x00003800&((data)<<11))
#define MIS_ST_LSADC_PERI_TOP_DEBUG_power_saving_cycle_time_src(data)                ((0x00003800&(data))>>11)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_get_power_saving_cycle_time(data)                ((0x00003800&(data))>>11)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_power_saving_disable_time_shift                  (8)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_power_saving_disable_time_mask                   (0x00000700)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_power_saving_disable_time(data)                  (0x00000700&((data)<<8))
#define MIS_ST_LSADC_PERI_TOP_DEBUG_power_saving_disable_time_src(data)              ((0x00000700&(data))>>8)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_get_power_saving_disable_time(data)              ((0x00000700&(data))>>8)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_peri_top_debug_shift                             (0)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_peri_top_debug_mask                              (0x000000FF)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_peri_top_debug(data)                             (0x000000FF&((data)<<0))
#define MIS_ST_LSADC_PERI_TOP_DEBUG_peri_top_debug_src(data)                         ((0x000000FF&(data))>>0)
#define MIS_ST_LSADC_PERI_TOP_DEBUG_get_peri_top_debug(data)                         ((0x000000FF&(data))>>0)


#define MIS_LSADC_PAD0_LEVEL_SET0                                                    0x1801BC30
#define MIS_LSADC_PAD0_LEVEL_SET0_reg_addr                                           "0xB801BC30"
#define MIS_LSADC_PAD0_LEVEL_SET0_reg                                                0xB801BC30
#define set_MIS_LSADC_PAD0_LEVEL_SET0_reg(data)   (*((volatile unsigned int*) MIS_LSADC_PAD0_LEVEL_SET0_reg)=data)
#define get_MIS_LSADC_PAD0_LEVEL_SET0_reg   (*((volatile unsigned int*) MIS_LSADC_PAD0_LEVEL_SET0_reg))
#define MIS_LSADC_PAD0_LEVEL_SET0_inst_adr                                           "0x000C"
#define MIS_LSADC_PAD0_LEVEL_SET0_inst                                               0x000C
#define MIS_LSADC_PAD0_LEVEL_SET0_level_0_top_bound_shift                            (24)
#define MIS_LSADC_PAD0_LEVEL_SET0_level_0_top_bound_mask                             (0xFF000000)
#define MIS_LSADC_PAD0_LEVEL_SET0_level_0_top_bound(data)                            (0xFF000000&((data)<<24))
#define MIS_LSADC_PAD0_LEVEL_SET0_level_0_top_bound_src(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD0_LEVEL_SET0_get_level_0_top_bound(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD0_LEVEL_SET0_level_0_low_bound_shift                            (16)
#define MIS_LSADC_PAD0_LEVEL_SET0_level_0_low_bound_mask                             (0x00FF0000)
#define MIS_LSADC_PAD0_LEVEL_SET0_level_0_low_bound(data)                            (0x00FF0000&((data)<<16))
#define MIS_LSADC_PAD0_LEVEL_SET0_level_0_low_bound_src(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD0_LEVEL_SET0_get_level_0_low_bound(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD0_LEVEL_SET0_block0_en_shift                                    (15)
#define MIS_LSADC_PAD0_LEVEL_SET0_block0_en_mask                                     (0x00008000)
#define MIS_LSADC_PAD0_LEVEL_SET0_block0_en(data)                                    (0x00008000&((data)<<15))
#define MIS_LSADC_PAD0_LEVEL_SET0_block0_en_src(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD0_LEVEL_SET0_get_block0_en(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD0_LEVEL_SET0_int_en0_shift                                      (1)
#define MIS_LSADC_PAD0_LEVEL_SET0_int_en0_mask                                       (0x00000002)
#define MIS_LSADC_PAD0_LEVEL_SET0_int_en0(data)                                      (0x00000002&((data)<<1))
#define MIS_LSADC_PAD0_LEVEL_SET0_int_en0_src(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD0_LEVEL_SET0_get_int_en0(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD0_LEVEL_SET0_int_pending_bit0_shift                             (0)
#define MIS_LSADC_PAD0_LEVEL_SET0_int_pending_bit0_mask                              (0x00000001)
#define MIS_LSADC_PAD0_LEVEL_SET0_int_pending_bit0(data)                             (0x00000001&((data)<<0))
#define MIS_LSADC_PAD0_LEVEL_SET0_int_pending_bit0_src(data)                         ((0x00000001&(data))>>0)
#define MIS_LSADC_PAD0_LEVEL_SET0_get_int_pending_bit0(data)                         ((0x00000001&(data))>>0)


#define MIS_LSADC_PAD0_LEVEL_SET1                                                    0x1801BC34
#define MIS_LSADC_PAD0_LEVEL_SET1_reg_addr                                           "0xB801BC34"
#define MIS_LSADC_PAD0_LEVEL_SET1_reg                                                0xB801BC34
#define set_MIS_LSADC_PAD0_LEVEL_SET1_reg(data)   (*((volatile unsigned int*) MIS_LSADC_PAD0_LEVEL_SET1_reg)=data)
#define get_MIS_LSADC_PAD0_LEVEL_SET1_reg   (*((volatile unsigned int*) MIS_LSADC_PAD0_LEVEL_SET1_reg))
#define MIS_LSADC_PAD0_LEVEL_SET1_inst_adr                                           "0x000D"
#define MIS_LSADC_PAD0_LEVEL_SET1_inst                                               0x000D
#define MIS_LSADC_PAD0_LEVEL_SET1_level_1_top_bound_shift                            (24)
#define MIS_LSADC_PAD0_LEVEL_SET1_level_1_top_bound_mask                             (0xFF000000)
#define MIS_LSADC_PAD0_LEVEL_SET1_level_1_top_bound(data)                            (0xFF000000&((data)<<24))
#define MIS_LSADC_PAD0_LEVEL_SET1_level_1_top_bound_src(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD0_LEVEL_SET1_get_level_1_top_bound(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD0_LEVEL_SET1_level_0_low_bound_shift                            (16)
#define MIS_LSADC_PAD0_LEVEL_SET1_level_0_low_bound_mask                             (0x00FF0000)
#define MIS_LSADC_PAD0_LEVEL_SET1_level_0_low_bound(data)                            (0x00FF0000&((data)<<16))
#define MIS_LSADC_PAD0_LEVEL_SET1_level_0_low_bound_src(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD0_LEVEL_SET1_get_level_0_low_bound(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD0_LEVEL_SET1_block1_en_shift                                    (15)
#define MIS_LSADC_PAD0_LEVEL_SET1_block1_en_mask                                     (0x00008000)
#define MIS_LSADC_PAD0_LEVEL_SET1_block1_en(data)                                    (0x00008000&((data)<<15))
#define MIS_LSADC_PAD0_LEVEL_SET1_block1_en_src(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD0_LEVEL_SET1_get_block1_en(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD0_LEVEL_SET1_int_en1_shift                                      (1)
#define MIS_LSADC_PAD0_LEVEL_SET1_int_en1_mask                                       (0x00000002)
#define MIS_LSADC_PAD0_LEVEL_SET1_int_en1(data)                                      (0x00000002&((data)<<1))
#define MIS_LSADC_PAD0_LEVEL_SET1_int_en1_src(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD0_LEVEL_SET1_get_int_en1(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD0_LEVEL_SET1_int_pending_bit1_shift                             (0)
#define MIS_LSADC_PAD0_LEVEL_SET1_int_pending_bit1_mask                              (0x00000001)
#define MIS_LSADC_PAD0_LEVEL_SET1_int_pending_bit1(data)                             (0x00000001&((data)<<0))
#define MIS_LSADC_PAD0_LEVEL_SET1_int_pending_bit1_src(data)                         ((0x00000001&(data))>>0)
#define MIS_LSADC_PAD0_LEVEL_SET1_get_int_pending_bit1(data)                         ((0x00000001&(data))>>0)


#define MIS_LSADC_PAD0_LEVEL_SET2                                                    0x1801BC38
#define MIS_LSADC_PAD0_LEVEL_SET2_reg_addr                                           "0xB801BC38"
#define MIS_LSADC_PAD0_LEVEL_SET2_reg                                                0xB801BC38
#define set_MIS_LSADC_PAD0_LEVEL_SET2_reg(data)   (*((volatile unsigned int*) MIS_LSADC_PAD0_LEVEL_SET2_reg)=data)
#define get_MIS_LSADC_PAD0_LEVEL_SET2_reg   (*((volatile unsigned int*) MIS_LSADC_PAD0_LEVEL_SET2_reg))
#define MIS_LSADC_PAD0_LEVEL_SET2_inst_adr                                           "0x000E"
#define MIS_LSADC_PAD0_LEVEL_SET2_inst                                               0x000E
#define MIS_LSADC_PAD0_LEVEL_SET2_level_2_top_bound_shift                            (24)
#define MIS_LSADC_PAD0_LEVEL_SET2_level_2_top_bound_mask                             (0xFF000000)
#define MIS_LSADC_PAD0_LEVEL_SET2_level_2_top_bound(data)                            (0xFF000000&((data)<<24))
#define MIS_LSADC_PAD0_LEVEL_SET2_level_2_top_bound_src(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD0_LEVEL_SET2_get_level_2_top_bound(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD0_LEVEL_SET2_level_2_low_bound_shift                            (16)
#define MIS_LSADC_PAD0_LEVEL_SET2_level_2_low_bound_mask                             (0x00FF0000)
#define MIS_LSADC_PAD0_LEVEL_SET2_level_2_low_bound(data)                            (0x00FF0000&((data)<<16))
#define MIS_LSADC_PAD0_LEVEL_SET2_level_2_low_bound_src(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD0_LEVEL_SET2_get_level_2_low_bound(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD0_LEVEL_SET2_block2_en_shift                                    (15)
#define MIS_LSADC_PAD0_LEVEL_SET2_block2_en_mask                                     (0x00008000)
#define MIS_LSADC_PAD0_LEVEL_SET2_block2_en(data)                                    (0x00008000&((data)<<15))
#define MIS_LSADC_PAD0_LEVEL_SET2_block2_en_src(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD0_LEVEL_SET2_get_block2_en(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD0_LEVEL_SET2_int_en2_shift                                      (1)
#define MIS_LSADC_PAD0_LEVEL_SET2_int_en2_mask                                       (0x00000002)
#define MIS_LSADC_PAD0_LEVEL_SET2_int_en2(data)                                      (0x00000002&((data)<<1))
#define MIS_LSADC_PAD0_LEVEL_SET2_int_en2_src(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD0_LEVEL_SET2_get_int_en2(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD0_LEVEL_SET2_int_pending_bit2_shift                             (0)
#define MIS_LSADC_PAD0_LEVEL_SET2_int_pending_bit2_mask                              (0x00000001)
#define MIS_LSADC_PAD0_LEVEL_SET2_int_pending_bit2(data)                             (0x00000001&((data)<<0))
#define MIS_LSADC_PAD0_LEVEL_SET2_int_pending_bit2_src(data)                         ((0x00000001&(data))>>0)
#define MIS_LSADC_PAD0_LEVEL_SET2_get_int_pending_bit2(data)                         ((0x00000001&(data))>>0)


#define MIS_LSADC_PAD0_LEVEL_SET3                                                    0x1801BC3C
#define MIS_LSADC_PAD0_LEVEL_SET3_reg_addr                                           "0xB801BC3C"
#define MIS_LSADC_PAD0_LEVEL_SET3_reg                                                0xB801BC3C
#define set_MIS_LSADC_PAD0_LEVEL_SET3_reg(data)   (*((volatile unsigned int*) MIS_LSADC_PAD0_LEVEL_SET3_reg)=data)
#define get_MIS_LSADC_PAD0_LEVEL_SET3_reg   (*((volatile unsigned int*) MIS_LSADC_PAD0_LEVEL_SET3_reg))
#define MIS_LSADC_PAD0_LEVEL_SET3_inst_adr                                           "0x000F"
#define MIS_LSADC_PAD0_LEVEL_SET3_inst                                               0x000F
#define MIS_LSADC_PAD0_LEVEL_SET3_level_3_top_bound_shift                            (24)
#define MIS_LSADC_PAD0_LEVEL_SET3_level_3_top_bound_mask                             (0xFF000000)
#define MIS_LSADC_PAD0_LEVEL_SET3_level_3_top_bound(data)                            (0xFF000000&((data)<<24))
#define MIS_LSADC_PAD0_LEVEL_SET3_level_3_top_bound_src(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD0_LEVEL_SET3_get_level_3_top_bound(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD0_LEVEL_SET3_level_3_low_bound_shift                            (16)
#define MIS_LSADC_PAD0_LEVEL_SET3_level_3_low_bound_mask                             (0x00FF0000)
#define MIS_LSADC_PAD0_LEVEL_SET3_level_3_low_bound(data)                            (0x00FF0000&((data)<<16))
#define MIS_LSADC_PAD0_LEVEL_SET3_level_3_low_bound_src(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD0_LEVEL_SET3_get_level_3_low_bound(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD0_LEVEL_SET3_block3_en_shift                                    (15)
#define MIS_LSADC_PAD0_LEVEL_SET3_block3_en_mask                                     (0x00008000)
#define MIS_LSADC_PAD0_LEVEL_SET3_block3_en(data)                                    (0x00008000&((data)<<15))
#define MIS_LSADC_PAD0_LEVEL_SET3_block3_en_src(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD0_LEVEL_SET3_get_block3_en(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD0_LEVEL_SET3_int_en3_shift                                      (1)
#define MIS_LSADC_PAD0_LEVEL_SET3_int_en3_mask                                       (0x00000002)
#define MIS_LSADC_PAD0_LEVEL_SET3_int_en3(data)                                      (0x00000002&((data)<<1))
#define MIS_LSADC_PAD0_LEVEL_SET3_int_en3_src(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD0_LEVEL_SET3_get_int_en3(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD0_LEVEL_SET3_int_pending_bit3_shift                             (0)
#define MIS_LSADC_PAD0_LEVEL_SET3_int_pending_bit3_mask                              (0x00000001)
#define MIS_LSADC_PAD0_LEVEL_SET3_int_pending_bit3(data)                             (0x00000001&((data)<<0))
#define MIS_LSADC_PAD0_LEVEL_SET3_int_pending_bit3_src(data)                         ((0x00000001&(data))>>0)
#define MIS_LSADC_PAD0_LEVEL_SET3_get_int_pending_bit3(data)                         ((0x00000001&(data))>>0)


#define MIS_LSADC_PAD0_LEVEL_SET4                                                    0x1801BC40
#define MIS_LSADC_PAD0_LEVEL_SET4_reg_addr                                           "0xB801BC40"
#define MIS_LSADC_PAD0_LEVEL_SET4_reg                                                0xB801BC40
#define set_MIS_LSADC_PAD0_LEVEL_SET4_reg(data)   (*((volatile unsigned int*) MIS_LSADC_PAD0_LEVEL_SET4_reg)=data)
#define get_MIS_LSADC_PAD0_LEVEL_SET4_reg   (*((volatile unsigned int*) MIS_LSADC_PAD0_LEVEL_SET4_reg))
#define MIS_LSADC_PAD0_LEVEL_SET4_inst_adr                                           "0x0010"
#define MIS_LSADC_PAD0_LEVEL_SET4_inst                                               0x0010
#define MIS_LSADC_PAD0_LEVEL_SET4_level_4_top_bound_shift                            (24)
#define MIS_LSADC_PAD0_LEVEL_SET4_level_4_top_bound_mask                             (0xFF000000)
#define MIS_LSADC_PAD0_LEVEL_SET4_level_4_top_bound(data)                            (0xFF000000&((data)<<24))
#define MIS_LSADC_PAD0_LEVEL_SET4_level_4_top_bound_src(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD0_LEVEL_SET4_get_level_4_top_bound(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD0_LEVEL_SET4_level_4_low_bound_shift                            (16)
#define MIS_LSADC_PAD0_LEVEL_SET4_level_4_low_bound_mask                             (0x00FF0000)
#define MIS_LSADC_PAD0_LEVEL_SET4_level_4_low_bound(data)                            (0x00FF0000&((data)<<16))
#define MIS_LSADC_PAD0_LEVEL_SET4_level_4_low_bound_src(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD0_LEVEL_SET4_get_level_4_low_bound(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD0_LEVEL_SET4_block4_en_shift                                    (15)
#define MIS_LSADC_PAD0_LEVEL_SET4_block4_en_mask                                     (0x00008000)
#define MIS_LSADC_PAD0_LEVEL_SET4_block4_en(data)                                    (0x00008000&((data)<<15))
#define MIS_LSADC_PAD0_LEVEL_SET4_block4_en_src(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD0_LEVEL_SET4_get_block4_en(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD0_LEVEL_SET4_int_en4_shift                                      (1)
#define MIS_LSADC_PAD0_LEVEL_SET4_int_en4_mask                                       (0x00000002)
#define MIS_LSADC_PAD0_LEVEL_SET4_int_en4(data)                                      (0x00000002&((data)<<1))
#define MIS_LSADC_PAD0_LEVEL_SET4_int_en4_src(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD0_LEVEL_SET4_get_int_en4(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD0_LEVEL_SET4_int_pending_bit4_shift                             (0)
#define MIS_LSADC_PAD0_LEVEL_SET4_int_pending_bit4_mask                              (0x00000001)
#define MIS_LSADC_PAD0_LEVEL_SET4_int_pending_bit4(data)                             (0x00000001&((data)<<0))
#define MIS_LSADC_PAD0_LEVEL_SET4_int_pending_bit4_src(data)                         ((0x00000001&(data))>>0)
#define MIS_LSADC_PAD0_LEVEL_SET4_get_int_pending_bit4(data)                         ((0x00000001&(data))>>0)


#define MIS_LSADC_PAD0_LEVEL_SET5                                                    0x1801BC44
#define MIS_LSADC_PAD0_LEVEL_SET5_reg_addr                                           "0xB801BC44"
#define MIS_LSADC_PAD0_LEVEL_SET5_reg                                                0xB801BC44
#define set_MIS_LSADC_PAD0_LEVEL_SET5_reg(data)   (*((volatile unsigned int*) MIS_LSADC_PAD0_LEVEL_SET5_reg)=data)
#define get_MIS_LSADC_PAD0_LEVEL_SET5_reg   (*((volatile unsigned int*) MIS_LSADC_PAD0_LEVEL_SET5_reg))
#define MIS_LSADC_PAD0_LEVEL_SET5_inst_adr                                           "0x0011"
#define MIS_LSADC_PAD0_LEVEL_SET5_inst                                               0x0011
#define MIS_LSADC_PAD0_LEVEL_SET5_level_5_top_bound_shift                            (24)
#define MIS_LSADC_PAD0_LEVEL_SET5_level_5_top_bound_mask                             (0xFF000000)
#define MIS_LSADC_PAD0_LEVEL_SET5_level_5_top_bound(data)                            (0xFF000000&((data)<<24))
#define MIS_LSADC_PAD0_LEVEL_SET5_level_5_top_bound_src(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD0_LEVEL_SET5_get_level_5_top_bound(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD0_LEVEL_SET5_level_5_low_bound_shift                            (16)
#define MIS_LSADC_PAD0_LEVEL_SET5_level_5_low_bound_mask                             (0x00FF0000)
#define MIS_LSADC_PAD0_LEVEL_SET5_level_5_low_bound(data)                            (0x00FF0000&((data)<<16))
#define MIS_LSADC_PAD0_LEVEL_SET5_level_5_low_bound_src(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD0_LEVEL_SET5_get_level_5_low_bound(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD0_LEVEL_SET5_block5_en_shift                                    (15)
#define MIS_LSADC_PAD0_LEVEL_SET5_block5_en_mask                                     (0x00008000)
#define MIS_LSADC_PAD0_LEVEL_SET5_block5_en(data)                                    (0x00008000&((data)<<15))
#define MIS_LSADC_PAD0_LEVEL_SET5_block5_en_src(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD0_LEVEL_SET5_get_block5_en(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD0_LEVEL_SET5_int_en5_shift                                      (1)
#define MIS_LSADC_PAD0_LEVEL_SET5_int_en5_mask                                       (0x00000002)
#define MIS_LSADC_PAD0_LEVEL_SET5_int_en5(data)                                      (0x00000002&((data)<<1))
#define MIS_LSADC_PAD0_LEVEL_SET5_int_en5_src(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD0_LEVEL_SET5_get_int_en5(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD0_LEVEL_SET5_int_pending_bit5_shift                             (0)
#define MIS_LSADC_PAD0_LEVEL_SET5_int_pending_bit5_mask                              (0x00000001)
#define MIS_LSADC_PAD0_LEVEL_SET5_int_pending_bit5(data)                             (0x00000001&((data)<<0))
#define MIS_LSADC_PAD0_LEVEL_SET5_int_pending_bit5_src(data)                         ((0x00000001&(data))>>0)
#define MIS_LSADC_PAD0_LEVEL_SET5_get_int_pending_bit5(data)                         ((0x00000001&(data))>>0)


#define MIS_LSADC_PAD1_LEVEL_SET0                                                    0x1801BC48
#define MIS_LSADC_PAD1_LEVEL_SET0_reg_addr                                           "0xB801BC48"
#define MIS_LSADC_PAD1_LEVEL_SET0_reg                                                0xB801BC48
#define set_MIS_LSADC_PAD1_LEVEL_SET0_reg(data)   (*((volatile unsigned int*) MIS_LSADC_PAD1_LEVEL_SET0_reg)=data)
#define get_MIS_LSADC_PAD1_LEVEL_SET0_reg   (*((volatile unsigned int*) MIS_LSADC_PAD1_LEVEL_SET0_reg))
#define MIS_LSADC_PAD1_LEVEL_SET0_inst_adr                                           "0x0012"
#define MIS_LSADC_PAD1_LEVEL_SET0_inst                                               0x0012
#define MIS_LSADC_PAD1_LEVEL_SET0_level_0_top_bound_shift                            (24)
#define MIS_LSADC_PAD1_LEVEL_SET0_level_0_top_bound_mask                             (0xFF000000)
#define MIS_LSADC_PAD1_LEVEL_SET0_level_0_top_bound(data)                            (0xFF000000&((data)<<24))
#define MIS_LSADC_PAD1_LEVEL_SET0_level_0_top_bound_src(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD1_LEVEL_SET0_get_level_0_top_bound(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD1_LEVEL_SET0_level_0_low_bound_shift                            (16)
#define MIS_LSADC_PAD1_LEVEL_SET0_level_0_low_bound_mask                             (0x00FF0000)
#define MIS_LSADC_PAD1_LEVEL_SET0_level_0_low_bound(data)                            (0x00FF0000&((data)<<16))
#define MIS_LSADC_PAD1_LEVEL_SET0_level_0_low_bound_src(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD1_LEVEL_SET0_get_level_0_low_bound(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD1_LEVEL_SET0_block0_en_shift                                    (15)
#define MIS_LSADC_PAD1_LEVEL_SET0_block0_en_mask                                     (0x00008000)
#define MIS_LSADC_PAD1_LEVEL_SET0_block0_en(data)                                    (0x00008000&((data)<<15))
#define MIS_LSADC_PAD1_LEVEL_SET0_block0_en_src(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD1_LEVEL_SET0_get_block0_en(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD1_LEVEL_SET0_int_en0_shift                                      (1)
#define MIS_LSADC_PAD1_LEVEL_SET0_int_en0_mask                                       (0x00000002)
#define MIS_LSADC_PAD1_LEVEL_SET0_int_en0(data)                                      (0x00000002&((data)<<1))
#define MIS_LSADC_PAD1_LEVEL_SET0_int_en0_src(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD1_LEVEL_SET0_get_int_en0(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD1_LEVEL_SET0_int_pending_bit0_shift                             (0)
#define MIS_LSADC_PAD1_LEVEL_SET0_int_pending_bit0_mask                              (0x00000001)
#define MIS_LSADC_PAD1_LEVEL_SET0_int_pending_bit0(data)                             (0x00000001&((data)<<0))
#define MIS_LSADC_PAD1_LEVEL_SET0_int_pending_bit0_src(data)                         ((0x00000001&(data))>>0)
#define MIS_LSADC_PAD1_LEVEL_SET0_get_int_pending_bit0(data)                         ((0x00000001&(data))>>0)


#define MIS_LSADC_PAD1_LEVEL_SET1                                                    0x1801BC4C
#define MIS_LSADC_PAD1_LEVEL_SET1_reg_addr                                           "0xB801BC4C"
#define MIS_LSADC_PAD1_LEVEL_SET1_reg                                                0xB801BC4C
#define set_MIS_LSADC_PAD1_LEVEL_SET1_reg(data)   (*((volatile unsigned int*) MIS_LSADC_PAD1_LEVEL_SET1_reg)=data)
#define get_MIS_LSADC_PAD1_LEVEL_SET1_reg   (*((volatile unsigned int*) MIS_LSADC_PAD1_LEVEL_SET1_reg))
#define MIS_LSADC_PAD1_LEVEL_SET1_inst_adr                                           "0x0013"
#define MIS_LSADC_PAD1_LEVEL_SET1_inst                                               0x0013
#define MIS_LSADC_PAD1_LEVEL_SET1_level_1_top_bound_shift                            (24)
#define MIS_LSADC_PAD1_LEVEL_SET1_level_1_top_bound_mask                             (0xFF000000)
#define MIS_LSADC_PAD1_LEVEL_SET1_level_1_top_bound(data)                            (0xFF000000&((data)<<24))
#define MIS_LSADC_PAD1_LEVEL_SET1_level_1_top_bound_src(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD1_LEVEL_SET1_get_level_1_top_bound(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD1_LEVEL_SET1_level_0_low_bound_shift                            (16)
#define MIS_LSADC_PAD1_LEVEL_SET1_level_0_low_bound_mask                             (0x00FF0000)
#define MIS_LSADC_PAD1_LEVEL_SET1_level_0_low_bound(data)                            (0x00FF0000&((data)<<16))
#define MIS_LSADC_PAD1_LEVEL_SET1_level_0_low_bound_src(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD1_LEVEL_SET1_get_level_0_low_bound(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD1_LEVEL_SET1_block1_en_shift                                    (15)
#define MIS_LSADC_PAD1_LEVEL_SET1_block1_en_mask                                     (0x00008000)
#define MIS_LSADC_PAD1_LEVEL_SET1_block1_en(data)                                    (0x00008000&((data)<<15))
#define MIS_LSADC_PAD1_LEVEL_SET1_block1_en_src(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD1_LEVEL_SET1_get_block1_en(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD1_LEVEL_SET1_int_en1_shift                                      (1)
#define MIS_LSADC_PAD1_LEVEL_SET1_int_en1_mask                                       (0x00000002)
#define MIS_LSADC_PAD1_LEVEL_SET1_int_en1(data)                                      (0x00000002&((data)<<1))
#define MIS_LSADC_PAD1_LEVEL_SET1_int_en1_src(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD1_LEVEL_SET1_get_int_en1(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD1_LEVEL_SET1_int_pending_bit1_shift                             (0)
#define MIS_LSADC_PAD1_LEVEL_SET1_int_pending_bit1_mask                              (0x00000001)
#define MIS_LSADC_PAD1_LEVEL_SET1_int_pending_bit1(data)                             (0x00000001&((data)<<0))
#define MIS_LSADC_PAD1_LEVEL_SET1_int_pending_bit1_src(data)                         ((0x00000001&(data))>>0)
#define MIS_LSADC_PAD1_LEVEL_SET1_get_int_pending_bit1(data)                         ((0x00000001&(data))>>0)


#define MIS_LSADC_PAD1_LEVEL_SET2                                                    0x1801BC50
#define MIS_LSADC_PAD1_LEVEL_SET2_reg_addr                                           "0xB801BC50"
#define MIS_LSADC_PAD1_LEVEL_SET2_reg                                                0xB801BC50
#define set_MIS_LSADC_PAD1_LEVEL_SET2_reg(data)   (*((volatile unsigned int*) MIS_LSADC_PAD1_LEVEL_SET2_reg)=data)
#define get_MIS_LSADC_PAD1_LEVEL_SET2_reg   (*((volatile unsigned int*) MIS_LSADC_PAD1_LEVEL_SET2_reg))
#define MIS_LSADC_PAD1_LEVEL_SET2_inst_adr                                           "0x0014"
#define MIS_LSADC_PAD1_LEVEL_SET2_inst                                               0x0014
#define MIS_LSADC_PAD1_LEVEL_SET2_level_2_top_bound_shift                            (24)
#define MIS_LSADC_PAD1_LEVEL_SET2_level_2_top_bound_mask                             (0xFF000000)
#define MIS_LSADC_PAD1_LEVEL_SET2_level_2_top_bound(data)                            (0xFF000000&((data)<<24))
#define MIS_LSADC_PAD1_LEVEL_SET2_level_2_top_bound_src(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD1_LEVEL_SET2_get_level_2_top_bound(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD1_LEVEL_SET2_level_2_low_bound_shift                            (16)
#define MIS_LSADC_PAD1_LEVEL_SET2_level_2_low_bound_mask                             (0x00FF0000)
#define MIS_LSADC_PAD1_LEVEL_SET2_level_2_low_bound(data)                            (0x00FF0000&((data)<<16))
#define MIS_LSADC_PAD1_LEVEL_SET2_level_2_low_bound_src(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD1_LEVEL_SET2_get_level_2_low_bound(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD1_LEVEL_SET2_block2_en_shift                                    (15)
#define MIS_LSADC_PAD1_LEVEL_SET2_block2_en_mask                                     (0x00008000)
#define MIS_LSADC_PAD1_LEVEL_SET2_block2_en(data)                                    (0x00008000&((data)<<15))
#define MIS_LSADC_PAD1_LEVEL_SET2_block2_en_src(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD1_LEVEL_SET2_get_block2_en(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD1_LEVEL_SET2_int_en2_shift                                      (1)
#define MIS_LSADC_PAD1_LEVEL_SET2_int_en2_mask                                       (0x00000002)
#define MIS_LSADC_PAD1_LEVEL_SET2_int_en2(data)                                      (0x00000002&((data)<<1))
#define MIS_LSADC_PAD1_LEVEL_SET2_int_en2_src(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD1_LEVEL_SET2_get_int_en2(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD1_LEVEL_SET2_int_pending_bit2_shift                             (0)
#define MIS_LSADC_PAD1_LEVEL_SET2_int_pending_bit2_mask                              (0x00000001)
#define MIS_LSADC_PAD1_LEVEL_SET2_int_pending_bit2(data)                             (0x00000001&((data)<<0))
#define MIS_LSADC_PAD1_LEVEL_SET2_int_pending_bit2_src(data)                         ((0x00000001&(data))>>0)
#define MIS_LSADC_PAD1_LEVEL_SET2_get_int_pending_bit2(data)                         ((0x00000001&(data))>>0)


#define MIS_LSADC_PAD1_LEVEL_SET3                                                    0x1801BC54
#define MIS_LSADC_PAD1_LEVEL_SET3_reg_addr                                           "0xB801BC54"
#define MIS_LSADC_PAD1_LEVEL_SET3_reg                                                0xB801BC54
#define set_MIS_LSADC_PAD1_LEVEL_SET3_reg(data)   (*((volatile unsigned int*) MIS_LSADC_PAD1_LEVEL_SET3_reg)=data)
#define get_MIS_LSADC_PAD1_LEVEL_SET3_reg   (*((volatile unsigned int*) MIS_LSADC_PAD1_LEVEL_SET3_reg))
#define MIS_LSADC_PAD1_LEVEL_SET3_inst_adr                                           "0x0015"
#define MIS_LSADC_PAD1_LEVEL_SET3_inst                                               0x0015
#define MIS_LSADC_PAD1_LEVEL_SET3_level_3_top_bound_shift                            (24)
#define MIS_LSADC_PAD1_LEVEL_SET3_level_3_top_bound_mask                             (0xFF000000)
#define MIS_LSADC_PAD1_LEVEL_SET3_level_3_top_bound(data)                            (0xFF000000&((data)<<24))
#define MIS_LSADC_PAD1_LEVEL_SET3_level_3_top_bound_src(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD1_LEVEL_SET3_get_level_3_top_bound(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD1_LEVEL_SET3_level_3_low_bound_shift                            (16)
#define MIS_LSADC_PAD1_LEVEL_SET3_level_3_low_bound_mask                             (0x00FF0000)
#define MIS_LSADC_PAD1_LEVEL_SET3_level_3_low_bound(data)                            (0x00FF0000&((data)<<16))
#define MIS_LSADC_PAD1_LEVEL_SET3_level_3_low_bound_src(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD1_LEVEL_SET3_get_level_3_low_bound(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD1_LEVEL_SET3_block3_en_shift                                    (15)
#define MIS_LSADC_PAD1_LEVEL_SET3_block3_en_mask                                     (0x00008000)
#define MIS_LSADC_PAD1_LEVEL_SET3_block3_en(data)                                    (0x00008000&((data)<<15))
#define MIS_LSADC_PAD1_LEVEL_SET3_block3_en_src(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD1_LEVEL_SET3_get_block3_en(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD1_LEVEL_SET3_int_en3_shift                                      (1)
#define MIS_LSADC_PAD1_LEVEL_SET3_int_en3_mask                                       (0x00000002)
#define MIS_LSADC_PAD1_LEVEL_SET3_int_en3(data)                                      (0x00000002&((data)<<1))
#define MIS_LSADC_PAD1_LEVEL_SET3_int_en3_src(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD1_LEVEL_SET3_get_int_en3(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD1_LEVEL_SET3_int_pending_bit3_shift                             (0)
#define MIS_LSADC_PAD1_LEVEL_SET3_int_pending_bit3_mask                              (0x00000001)
#define MIS_LSADC_PAD1_LEVEL_SET3_int_pending_bit3(data)                             (0x00000001&((data)<<0))
#define MIS_LSADC_PAD1_LEVEL_SET3_int_pending_bit3_src(data)                         ((0x00000001&(data))>>0)
#define MIS_LSADC_PAD1_LEVEL_SET3_get_int_pending_bit3(data)                         ((0x00000001&(data))>>0)


#define MIS_LSADC_PAD1_LEVEL_SET4                                                    0x1801BC58
#define MIS_LSADC_PAD1_LEVEL_SET4_reg_addr                                           "0xB801BC58"
#define MIS_LSADC_PAD1_LEVEL_SET4_reg                                                0xB801BC58
#define set_MIS_LSADC_PAD1_LEVEL_SET4_reg(data)   (*((volatile unsigned int*) MIS_LSADC_PAD1_LEVEL_SET4_reg)=data)
#define get_MIS_LSADC_PAD1_LEVEL_SET4_reg   (*((volatile unsigned int*) MIS_LSADC_PAD1_LEVEL_SET4_reg))
#define MIS_LSADC_PAD1_LEVEL_SET4_inst_adr                                           "0x0016"
#define MIS_LSADC_PAD1_LEVEL_SET4_inst                                               0x0016
#define MIS_LSADC_PAD1_LEVEL_SET4_level_4_top_bound_shift                            (24)
#define MIS_LSADC_PAD1_LEVEL_SET4_level_4_top_bound_mask                             (0xFF000000)
#define MIS_LSADC_PAD1_LEVEL_SET4_level_4_top_bound(data)                            (0xFF000000&((data)<<24))
#define MIS_LSADC_PAD1_LEVEL_SET4_level_4_top_bound_src(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD1_LEVEL_SET4_get_level_4_top_bound(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD1_LEVEL_SET4_level_4_low_bound_shift                            (16)
#define MIS_LSADC_PAD1_LEVEL_SET4_level_4_low_bound_mask                             (0x00FF0000)
#define MIS_LSADC_PAD1_LEVEL_SET4_level_4_low_bound(data)                            (0x00FF0000&((data)<<16))
#define MIS_LSADC_PAD1_LEVEL_SET4_level_4_low_bound_src(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD1_LEVEL_SET4_get_level_4_low_bound(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD1_LEVEL_SET4_block4_en_shift                                    (15)
#define MIS_LSADC_PAD1_LEVEL_SET4_block4_en_mask                                     (0x00008000)
#define MIS_LSADC_PAD1_LEVEL_SET4_block4_en(data)                                    (0x00008000&((data)<<15))
#define MIS_LSADC_PAD1_LEVEL_SET4_block4_en_src(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD1_LEVEL_SET4_get_block4_en(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD1_LEVEL_SET4_int_en4_shift                                      (1)
#define MIS_LSADC_PAD1_LEVEL_SET4_int_en4_mask                                       (0x00000002)
#define MIS_LSADC_PAD1_LEVEL_SET4_int_en4(data)                                      (0x00000002&((data)<<1))
#define MIS_LSADC_PAD1_LEVEL_SET4_int_en4_src(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD1_LEVEL_SET4_get_int_en4(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD1_LEVEL_SET4_int_pending_bit4_shift                             (0)
#define MIS_LSADC_PAD1_LEVEL_SET4_int_pending_bit4_mask                              (0x00000001)
#define MIS_LSADC_PAD1_LEVEL_SET4_int_pending_bit4(data)                             (0x00000001&((data)<<0))
#define MIS_LSADC_PAD1_LEVEL_SET4_int_pending_bit4_src(data)                         ((0x00000001&(data))>>0)
#define MIS_LSADC_PAD1_LEVEL_SET4_get_int_pending_bit4(data)                         ((0x00000001&(data))>>0)


#define MIS_LSADC_PAD1_LEVEL_SET5                                                    0x1801BC5C
#define MIS_LSADC_PAD1_LEVEL_SET5_reg_addr                                           "0xB801BC5C"
#define MIS_LSADC_PAD1_LEVEL_SET5_reg                                                0xB801BC5C
#define set_MIS_LSADC_PAD1_LEVEL_SET5_reg(data)   (*((volatile unsigned int*) MIS_LSADC_PAD1_LEVEL_SET5_reg)=data)
#define get_MIS_LSADC_PAD1_LEVEL_SET5_reg   (*((volatile unsigned int*) MIS_LSADC_PAD1_LEVEL_SET5_reg))
#define MIS_LSADC_PAD1_LEVEL_SET5_inst_adr                                           "0x0017"
#define MIS_LSADC_PAD1_LEVEL_SET5_inst                                               0x0017
#define MIS_LSADC_PAD1_LEVEL_SET5_level_5_top_bound_shift                            (24)
#define MIS_LSADC_PAD1_LEVEL_SET5_level_5_top_bound_mask                             (0xFF000000)
#define MIS_LSADC_PAD1_LEVEL_SET5_level_5_top_bound(data)                            (0xFF000000&((data)<<24))
#define MIS_LSADC_PAD1_LEVEL_SET5_level_5_top_bound_src(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD1_LEVEL_SET5_get_level_5_top_bound(data)                        ((0xFF000000&(data))>>24)
#define MIS_LSADC_PAD1_LEVEL_SET5_level_5_low_bound_shift                            (16)
#define MIS_LSADC_PAD1_LEVEL_SET5_level_5_low_bound_mask                             (0x00FF0000)
#define MIS_LSADC_PAD1_LEVEL_SET5_level_5_low_bound(data)                            (0x00FF0000&((data)<<16))
#define MIS_LSADC_PAD1_LEVEL_SET5_level_5_low_bound_src(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD1_LEVEL_SET5_get_level_5_low_bound(data)                        ((0x00FF0000&(data))>>16)
#define MIS_LSADC_PAD1_LEVEL_SET5_block5_en_shift                                    (15)
#define MIS_LSADC_PAD1_LEVEL_SET5_block5_en_mask                                     (0x00008000)
#define MIS_LSADC_PAD1_LEVEL_SET5_block5_en(data)                                    (0x00008000&((data)<<15))
#define MIS_LSADC_PAD1_LEVEL_SET5_block5_en_src(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD1_LEVEL_SET5_get_block5_en(data)                                ((0x00008000&(data))>>15)
#define MIS_LSADC_PAD1_LEVEL_SET5_int_en5_shift                                      (1)
#define MIS_LSADC_PAD1_LEVEL_SET5_int_en5_mask                                       (0x00000002)
#define MIS_LSADC_PAD1_LEVEL_SET5_int_en5(data)                                      (0x00000002&((data)<<1))
#define MIS_LSADC_PAD1_LEVEL_SET5_int_en5_src(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD1_LEVEL_SET5_get_int_en5(data)                                  ((0x00000002&(data))>>1)
#define MIS_LSADC_PAD1_LEVEL_SET5_int_pending_bit5_shift                             (0)
#define MIS_LSADC_PAD1_LEVEL_SET5_int_pending_bit5_mask                              (0x00000001)
#define MIS_LSADC_PAD1_LEVEL_SET5_int_pending_bit5(data)                             (0x00000001&((data)<<0))
#define MIS_LSADC_PAD1_LEVEL_SET5_int_pending_bit5_src(data)                         ((0x00000001&(data))>>0)
#define MIS_LSADC_PAD1_LEVEL_SET5_get_int_pending_bit5(data)                         ((0x00000001&(data))>>0)


#define MIS_LSADC_INT_PAD0                                                           0x1801BC78
#define MIS_LSADC_INT_PAD0_reg_addr                                                  "0xB801BC78"
#define MIS_LSADC_INT_PAD0_reg                                                       0xB801BC78
#define set_MIS_LSADC_INT_PAD0_reg(data)   (*((volatile unsigned int*) MIS_LSADC_INT_PAD0_reg)=data)
#define get_MIS_LSADC_INT_PAD0_reg   (*((volatile unsigned int*) MIS_LSADC_INT_PAD0_reg))
#define MIS_LSADC_INT_PAD0_inst_adr                                                  "0x001E"
#define MIS_LSADC_INT_PAD0_inst                                                      0x001E
#define MIS_LSADC_INT_PAD0_adc_value0latch_shift                                     (8)
#define MIS_LSADC_INT_PAD0_adc_value0latch_mask                                      (0x00003F00)
#define MIS_LSADC_INT_PAD0_adc_value0latch(data)                                     (0x00003F00&((data)<<8))
#define MIS_LSADC_INT_PAD0_adc_value0latch_src(data)                                 ((0x00003F00&(data))>>8)
#define MIS_LSADC_INT_PAD0_get_adc_value0latch(data)                                 ((0x00003F00&(data))>>8)
#define MIS_LSADC_INT_PAD0_int_latchstatus_shift                                     (0)
#define MIS_LSADC_INT_PAD0_int_latchstatus_mask                                      (0x00000001)
#define MIS_LSADC_INT_PAD0_int_latchstatus(data)                                     (0x00000001&((data)<<0))
#define MIS_LSADC_INT_PAD0_int_latchstatus_src(data)                                 ((0x00000001&(data))>>0)
#define MIS_LSADC_INT_PAD0_get_int_latchstatus(data)                                 ((0x00000001&(data))>>0)


#define MIS_LSADC_INT_PAD1                                                           0x1801BC7C
#define MIS_LSADC_INT_PAD1_reg_addr                                                  "0xB801BC7C"
#define MIS_LSADC_INT_PAD1_reg                                                       0xB801BC7C
#define set_MIS_LSADC_INT_PAD1_reg(data)   (*((volatile unsigned int*) MIS_LSADC_INT_PAD1_reg)=data)
#define get_MIS_LSADC_INT_PAD1_reg   (*((volatile unsigned int*) MIS_LSADC_INT_PAD1_reg))
#define MIS_LSADC_INT_PAD1_inst_adr                                                  "0x001F"
#define MIS_LSADC_INT_PAD1_inst                                                      0x001F
#define MIS_LSADC_INT_PAD1_adc_value1latch_shift                                     (8)
#define MIS_LSADC_INT_PAD1_adc_value1latch_mask                                      (0x00003F00)
#define MIS_LSADC_INT_PAD1_adc_value1latch(data)                                     (0x00003F00&((data)<<8))
#define MIS_LSADC_INT_PAD1_adc_value1latch_src(data)                                 ((0x00003F00&(data))>>8)
#define MIS_LSADC_INT_PAD1_get_adc_value1latch(data)                                 ((0x00003F00&(data))>>8)
#define MIS_LSADC_INT_PAD1_int_latchstatus_shift                                     (0)
#define MIS_LSADC_INT_PAD1_int_latchstatus_mask                                      (0x00000001)
#define MIS_LSADC_INT_PAD1_int_latchstatus(data)                                     (0x00000001&((data)<<0))
#define MIS_LSADC_INT_PAD1_int_latchstatus_src(data)                                 ((0x00000001&(data))>>0)
#define MIS_LSADC_INT_PAD1_get_int_latchstatus(data)                                 ((0x00000001&(data))>>0)


#endif
