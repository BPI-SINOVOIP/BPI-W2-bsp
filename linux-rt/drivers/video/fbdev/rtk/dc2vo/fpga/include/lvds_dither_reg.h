/**************************************************************
// Spec Version                  : 1.0.6
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Register_Name
// Naming Rule                   : Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/4/11 16:51:21
***************************************************************/


#ifndef _DITHER_REG_H_INCLUDED_
#define _DITHER_REG_H_INCLUDED_
#ifdef  _DITHER_USE_STRUCT
typedef struct 
{
unsigned int     Seq_2nd_B_th:8;
unsigned int     Seq_2nd_G_th:8;
unsigned int     Seq_2nd_R_th:8;
unsigned int     Seq_2nd_mode:1;
unsigned int     reserved_0:1;
unsigned int     Function_Enable:1;
unsigned int     Temporal_Enable:1;
unsigned int     Value_Sign:1;
unsigned int     Dithering_Mode:1;
unsigned int     V_Modulation:1;
unsigned int     H_Modulation:1;
}DITHERING_CTRL;

typedef struct 
{
unsigned int     Seq_R_7:4;
unsigned int     Seq_R_6:4;
unsigned int     Seq_R_5:4;
unsigned int     Seq_R_4:4;
unsigned int     Seq_R_3:4;
unsigned int     Seq_R_2:4;
unsigned int     Seq_R_1:4;
unsigned int     Seq_R_0:4;
}DITHERING_SEQ_R_0;

typedef struct 
{
unsigned int     Seq_R_15:4;
unsigned int     Seq_R_14:4;
unsigned int     Seq_R_13:4;
unsigned int     Seq_R_12:4;
unsigned int     Seq_R_11:4;
unsigned int     Seq_R_10:4;
unsigned int     Seq_R_9:4;
unsigned int     Seq_R_8:4;
}DITHERING_SEQ_R_1;

typedef struct 
{
unsigned int     Seq_R_23:4;
unsigned int     Seq_R_22:4;
unsigned int     Seq_R_21:4;
unsigned int     Seq_R_20:4;
unsigned int     Seq_R_19:4;
unsigned int     Seq_R_18:4;
unsigned int     Seq_R_17:4;
unsigned int     Seq_R_16:4;
}DITHERING_SEQ_R_2;

typedef struct 
{
unsigned int     Seq_R_31:4;
unsigned int     Seq_R_30:4;
unsigned int     Seq_R_29:4;
unsigned int     Seq_R_28:4;
unsigned int     Seq_R_27:4;
unsigned int     Seq_R_26:4;
unsigned int     Seq_R_25:4;
unsigned int     Seq_R_24:4;
}DITHERING_SEQ_R_3;

typedef struct 
{
unsigned int     Seq_G_7:4;
unsigned int     Seq_G_6:4;
unsigned int     Seq_G_5:4;
unsigned int     Seq_G_4:4;
unsigned int     Seq_G_3:4;
unsigned int     Seq_G_2:4;
unsigned int     Seq_G_1:4;
unsigned int     Seq_G_0:4;
}DITHERING_SEQ_G_0;

typedef struct 
{
unsigned int     Seq_G_15:4;
unsigned int     Seq_G_14:4;
unsigned int     Seq_G_13:4;
unsigned int     Seq_G_12:4;
unsigned int     Seq_G_11:4;
unsigned int     Seq_G_10:4;
unsigned int     Seq_G_9:4;
unsigned int     Seq_G_8:4;
}DITHERING_SEQ_G_1;

typedef struct 
{
unsigned int     Seq_G_23:4;
unsigned int     Seq_G_22:4;
unsigned int     Seq_G_21:4;
unsigned int     Seq_G_20:4;
unsigned int     Seq_G_19:4;
unsigned int     Seq_G_18:4;
unsigned int     Seq_G_17:4;
unsigned int     Seq_G_16:4;
}DITHERING_SEQ_G_2;

typedef struct 
{
unsigned int     Seq_G_31:4;
unsigned int     Seq_G_30:4;
unsigned int     Seq_G_29:4;
unsigned int     Seq_G_28:4;
unsigned int     Seq_G_27:4;
unsigned int     Seq_G_26:4;
unsigned int     Seq_G_25:4;
unsigned int     Seq_G_24:4;
}DITHERING_SEQ_G_3;

typedef struct 
{
unsigned int     Seq_B_7:4;
unsigned int     Seq_B_6:4;
unsigned int     Seq_B_5:4;
unsigned int     Seq_B_4:4;
unsigned int     Seq_B_3:4;
unsigned int     Seq_B_2:4;
unsigned int     Seq_B_1:4;
unsigned int     Seq_B_0:4;
}DITHERING_SEQ_B_0;

typedef struct 
{
unsigned int     Seq_B_15:4;
unsigned int     Seq_B_14:4;
unsigned int     Seq_B_13:4;
unsigned int     Seq_B_12:4;
unsigned int     Seq_B_11:4;
unsigned int     Seq_B_10:4;
unsigned int     Seq_B_9:4;
unsigned int     Seq_B_8:4;
}DITHERING_SEQ_B_1;

typedef struct 
{
unsigned int     Seq_B_23:4;
unsigned int     Seq_B_22:4;
unsigned int     Seq_B_21:4;
unsigned int     Seq_B_20:4;
unsigned int     Seq_B_19:4;
unsigned int     Seq_B_18:4;
unsigned int     Seq_B_17:4;
unsigned int     Seq_B_16:4;
}DITHERING_SEQ_B_2;

typedef struct 
{
unsigned int     Seq_B_31:4;
unsigned int     Seq_B_30:4;
unsigned int     Seq_B_29:4;
unsigned int     Seq_B_28:4;
unsigned int     Seq_B_27:4;
unsigned int     Seq_B_26:4;
unsigned int     Seq_B_25:4;
unsigned int     Seq_B_24:4;
}DITHERING_SEQ_B_3;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_R_03:6;
unsigned int     Tab_R_02:6;
unsigned int     Tab_R_01:6;
unsigned int     Tab_R_00:6;
}DITHERING_TAB_R_0;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_R_13:6;
unsigned int     Tab_R_12:6;
unsigned int     Tab_R_11:6;
unsigned int     Tab_R_10:6;
}DITHERING_TAB_R_1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_R_23:6;
unsigned int     Tab_R_22:6;
unsigned int     Tab_R_21:6;
unsigned int     Tab_R_20:6;
}DITHERING_TAB_R_2;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_R_33:6;
unsigned int     Tab_R_32:6;
unsigned int     Tab_R_31:6;
unsigned int     Tab_R_30:6;
}DITHERING_TAB_R_3;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_R_43:6;
unsigned int     Tab_R_42:6;
unsigned int     Tab_R_41:6;
unsigned int     Tab_R_40:6;
}DITHERING_TAB_R_4;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_R_53:6;
unsigned int     Tab_R_52:6;
unsigned int     Tab_R_51:6;
unsigned int     Tab_R_50:6;
}DITHERING_TAB_R_5;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_R_63:6;
unsigned int     Tab_R_62:6;
unsigned int     Tab_R_61:6;
unsigned int     Tab_R_60:6;
}DITHERING_TAB_R_6;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_R_73:6;
unsigned int     Tab_R_72:6;
unsigned int     Tab_R_71:6;
unsigned int     Tab_R_70:6;
}DITHERING_TAB_R_7;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_R_83:6;
unsigned int     Tab_R_82:6;
unsigned int     Tab_R_81:6;
unsigned int     Tab_R_80:6;
}DITHERING_TAB_R_8;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_R_93:6;
unsigned int     Tab_R_92:6;
unsigned int     Tab_R_91:6;
unsigned int     Tab_R_90:6;
}DITHERING_TAB_R_9;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_R_A3:6;
unsigned int     Tab_R_A2:6;
unsigned int     Tab_R_A1:6;
unsigned int     Tab_R_A0:6;
}DITHERING_TAB_R_10;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_R_B3:6;
unsigned int     Tab_R_B2:6;
unsigned int     Tab_R_B1:6;
unsigned int     Tab_R_B0:6;
}DITHERING_TAB_R_11;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_R_C3:6;
unsigned int     Tab_R_C2:6;
unsigned int     Tab_R_C1:6;
unsigned int     Tab_R_C0:6;
}DITHERING_TAB_R_12;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_R_D3:6;
unsigned int     Tab_R_D2:6;
unsigned int     Tab_R_D1:6;
unsigned int     Tab_R_D0:6;
}DITHERING_TAB_R_13;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_R_E3:6;
unsigned int     Tab_R_E2:6;
unsigned int     Tab_R_E1:6;
unsigned int     Tab_R_E0:6;
}DITHERING_TAB_R_14;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_R_F3:6;
unsigned int     Tab_R_F2:6;
unsigned int     Tab_R_F1:6;
unsigned int     Tab_R_F0:6;
}DITHERING_TAB_R_15;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_G_03:6;
unsigned int     Tab_G_02:6;
unsigned int     Tab_G_01:6;
unsigned int     Tab_G_00:6;
}DITHERING_TAB_G_0;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_G_13:6;
unsigned int     Tab_G_12:6;
unsigned int     Tab_G_11:6;
unsigned int     Tab_G_10:6;
}DITHERING_TAB_G_1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_G_23:6;
unsigned int     Tab_G_22:6;
unsigned int     Tab_G_21:6;
unsigned int     Tab_G_20:6;
}DITHERING_TAB_G_2;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_G_33:6;
unsigned int     Tab_G_32:6;
unsigned int     Tab_G_31:6;
unsigned int     Tab_G_30:6;
}DITHERING_TAB_G_3;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_G_43:6;
unsigned int     Tab_G_42:6;
unsigned int     Tab_G_41:6;
unsigned int     Tab_G_40:6;
}DITHERING_TAB_G_4;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_G_53:6;
unsigned int     Tab_G_52:6;
unsigned int     Tab_G_51:6;
unsigned int     Tab_G_50:6;
}DITHERING_TAB_G_5;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_G_63:6;
unsigned int     Tab_G_62:6;
unsigned int     Tab_G_61:6;
unsigned int     Tab_G_60:6;
}DITHERING_TAB_G_6;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_G_73:6;
unsigned int     Tab_G_72:6;
unsigned int     Tab_G_71:6;
unsigned int     Tab_G_70:6;
}DITHERING_TAB_G_7;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_G_83:6;
unsigned int     Tab_G_82:6;
unsigned int     Tab_G_81:6;
unsigned int     Tab_G_80:6;
}DITHERING_TAB_G_8;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_G_93:6;
unsigned int     Tab_G_92:6;
unsigned int     Tab_G_91:6;
unsigned int     Tab_G_90:6;
}DITHERING_TAB_G_9;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_G_A3:6;
unsigned int     Tab_G_A2:6;
unsigned int     Tab_G_A1:6;
unsigned int     Tab_G_A0:6;
}DITHERING_TAB_G_10;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_G_B3:6;
unsigned int     Tab_G_B2:6;
unsigned int     Tab_G_B1:6;
unsigned int     Tab_G_B0:6;
}DITHERING_TAB_G_11;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_G_C3:6;
unsigned int     Tab_G_C2:6;
unsigned int     Tab_G_C1:6;
unsigned int     Tab_G_C0:6;
}DITHERING_TAB_G_12;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_G_D3:6;
unsigned int     Tab_G_D2:6;
unsigned int     Tab_G_D1:6;
unsigned int     Tab_G_D0:6;
}DITHERING_TAB_G_13;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_G_E3:6;
unsigned int     Tab_G_E2:6;
unsigned int     Tab_G_E1:6;
unsigned int     Tab_G_E0:6;
}DITHERING_TAB_G_14;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_G_F3:6;
unsigned int     Tab_G_F2:6;
unsigned int     Tab_G_F1:6;
unsigned int     Tab_G_F0:6;
}DITHERING_TAB_G_15;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_B_03:6;
unsigned int     Tab_B_02:6;
unsigned int     Tab_B_01:6;
unsigned int     Tab_B_00:6;
}DITHERING_TAB_B_0;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_B_13:6;
unsigned int     Tab_B_12:6;
unsigned int     Tab_B_11:6;
unsigned int     Tab_B_10:6;
}DITHERING_TAB_B_1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_B_23:6;
unsigned int     Tab_B_22:6;
unsigned int     Tab_B_21:6;
unsigned int     Tab_B_20:6;
}DITHERING_TAB_B_2;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_B_33:6;
unsigned int     Tab_B_32:6;
unsigned int     Tab_B_31:6;
unsigned int     Tab_B_30:6;
}DITHERING_TAB_B_3;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_B_43:6;
unsigned int     Tab_B_42:6;
unsigned int     Tab_B_41:6;
unsigned int     Tab_B_40:6;
}DITHERING_TAB_B_4;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_B_53:6;
unsigned int     Tab_B_52:6;
unsigned int     Tab_B_51:6;
unsigned int     Tab_B_50:6;
}DITHERING_TAB_B_5;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_B_63:6;
unsigned int     Tab_B_62:6;
unsigned int     Tab_B_61:6;
unsigned int     Tab_B_60:6;
}DITHERING_TAB_B_6;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_B_73:6;
unsigned int     Tab_B_72:6;
unsigned int     Tab_B_71:6;
unsigned int     Tab_B_70:6;
}DITHERING_TAB_B_7;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_B_83:6;
unsigned int     Tab_B_82:6;
unsigned int     Tab_B_81:6;
unsigned int     Tab_B_80:6;
}DITHERING_TAB_B_8;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_B_93:6;
unsigned int     Tab_B_92:6;
unsigned int     Tab_B_91:6;
unsigned int     Tab_B_90:6;
}DITHERING_TAB_B_9;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_B_A3:6;
unsigned int     Tab_B_A2:6;
unsigned int     Tab_B_A1:6;
unsigned int     Tab_B_A0:6;
}DITHERING_TAB_B_10;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_B_B3:6;
unsigned int     Tab_B_B2:6;
unsigned int     Tab_B_B1:6;
unsigned int     Tab_B_B0:6;
}DITHERING_TAB_B_11;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_B_C3:6;
unsigned int     Tab_B_C2:6;
unsigned int     Tab_B_C1:6;
unsigned int     Tab_B_C0:6;
}DITHERING_TAB_B_12;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_B_D3:6;
unsigned int     Tab_B_D2:6;
unsigned int     Tab_B_D1:6;
unsigned int     Tab_B_D0:6;
}DITHERING_TAB_B_13;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_B_E3:6;
unsigned int     Tab_B_E2:6;
unsigned int     Tab_B_E1:6;
unsigned int     Tab_B_E0:6;
}DITHERING_TAB_B_14;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     Tab_B_F3:6;
unsigned int     Tab_B_F2:6;
unsigned int     Tab_B_F1:6;
unsigned int     Tab_B_F0:6;
}DITHERING_TAB_B_15;

typedef struct 
{
unsigned int     Temp_offset_15:2;
unsigned int     Temp_offset_14:2;
unsigned int     Temp_offset_13:2;
unsigned int     Temp_offset_12:2;
unsigned int     Temp_offset_11:2;
unsigned int     Temp_offset_10:2;
unsigned int     Temp_offset_9:2;
unsigned int     Temp_offset_8:2;
unsigned int     Temp_offset_7:2;
unsigned int     Temp_offset_6:2;
unsigned int     Temp_offset_5:2;
unsigned int     Temp_offset_4:2;
unsigned int     Temp_offset_3:2;
unsigned int     Temp_offset_2:2;
unsigned int     Temp_offset_1:2;
unsigned int     Temp_offset_0:2;
}TEMPORAL_OFFSET;

typedef struct 
{
unsigned int     Seq_R_7:4;
unsigned int     Seq_R_6:4;
unsigned int     Seq_R_5:4;
unsigned int     Seq_R_4:4;
unsigned int     Seq_R_3:4;
unsigned int     Seq_R_2:4;
unsigned int     Seq_R_1:4;
unsigned int     Seq_R_0:4;
}DITHERING_2ND_SEQ_R_0;

typedef struct 
{
unsigned int     Seq_R_15:4;
unsigned int     Seq_R_14:4;
unsigned int     Seq_R_13:4;
unsigned int     Seq_R_12:4;
unsigned int     Seq_R_11:4;
unsigned int     Seq_R_10:4;
unsigned int     Seq_R_9:4;
unsigned int     Seq_R_8:4;
}DITHERING_2ND_SEQ_R_1;

typedef struct 
{
unsigned int     Seq_R_23:4;
unsigned int     Seq_R_22:4;
unsigned int     Seq_R_21:4;
unsigned int     Seq_R_20:4;
unsigned int     Seq_R_19:4;
unsigned int     Seq_R_18:4;
unsigned int     Seq_R_17:4;
unsigned int     Seq_R_16:4;
}DITHERING_2ND_SEQ_R_2;

typedef struct 
{
unsigned int     Seq_R_31:4;
unsigned int     Seq_R_30:4;
unsigned int     Seq_R_29:4;
unsigned int     Seq_R_28:4;
unsigned int     Seq_R_27:4;
unsigned int     Seq_R_26:4;
unsigned int     Seq_R_25:4;
unsigned int     Seq_R_24:4;
}DITHERING_2ND_SEQ_R_3;

typedef struct 
{
unsigned int     Seq_G_7:4;
unsigned int     Seq_G_6:4;
unsigned int     Seq_G_5:4;
unsigned int     Seq_G_4:4;
unsigned int     Seq_G_3:4;
unsigned int     Seq_G_2:4;
unsigned int     Seq_G_1:4;
unsigned int     Seq_G_0:4;
}DITHERING_2ND_SEQ_G_0;

typedef struct 
{
unsigned int     Seq_G_15:4;
unsigned int     Seq_G_14:4;
unsigned int     Seq_G_13:4;
unsigned int     Seq_G_12:4;
unsigned int     Seq_G_11:4;
unsigned int     Seq_G_10:4;
unsigned int     Seq_G_9:4;
unsigned int     Seq_G_8:4;
}DITHERING_2ND_SEQ_G_1;

typedef struct 
{
unsigned int     Seq_G_23:4;
unsigned int     Seq_G_22:4;
unsigned int     Seq_G_21:4;
unsigned int     Seq_G_20:4;
unsigned int     Seq_G_19:4;
unsigned int     Seq_G_18:4;
unsigned int     Seq_G_17:4;
unsigned int     Seq_G_16:4;
}DITHERING_2ND_SEQ_G_2;

typedef struct 
{
unsigned int     Seq_G_31:4;
unsigned int     Seq_G_30:4;
unsigned int     Seq_G_29:4;
unsigned int     Seq_G_28:4;
unsigned int     Seq_G_27:4;
unsigned int     Seq_G_26:4;
unsigned int     Seq_G_25:4;
unsigned int     Seq_G_24:4;
}DITHERING_2ND_SEQ_G_3;

typedef struct 
{
unsigned int     Seq_B_7:4;
unsigned int     Seq_B_6:4;
unsigned int     Seq_B_5:4;
unsigned int     Seq_B_4:4;
unsigned int     Seq_B_3:4;
unsigned int     Seq_B_2:4;
unsigned int     Seq_B_1:4;
unsigned int     Seq_B_0:4;
}DITHERING_2ND_SEQ_B_0;

typedef struct 
{
unsigned int     Seq_B_15:4;
unsigned int     Seq_B_14:4;
unsigned int     Seq_B_13:4;
unsigned int     Seq_B_12:4;
unsigned int     Seq_B_11:4;
unsigned int     Seq_B_10:4;
unsigned int     Seq_B_9:4;
unsigned int     Seq_B_8:4;
}DITHERING_2ND_SEQ_B_1;

typedef struct 
{
unsigned int     Seq_B_23:4;
unsigned int     Seq_B_22:4;
unsigned int     Seq_B_21:4;
unsigned int     Seq_B_20:4;
unsigned int     Seq_B_19:4;
unsigned int     Seq_B_18:4;
unsigned int     Seq_B_17:4;
unsigned int     Seq_B_16:4;
}DITHERING_2ND_SEQ_B_2;

typedef struct 
{
unsigned int     Seq_B_31:4;
unsigned int     Seq_B_30:4;
unsigned int     Seq_B_29:4;
unsigned int     Seq_B_28:4;
unsigned int     Seq_B_27:4;
unsigned int     Seq_B_26:4;
unsigned int     Seq_B_25:4;
unsigned int     Seq_B_24:4;
}DITHERING_2ND_SEQ_B_3;

#endif

#define DITHERING_CTRL                                                               0x180098b4
#define DITHERING_CTRL_reg_addr                                                      "0xB80098B4"
#define DITHERING_CTRL_reg                                                           0xB80098B4
#define set_DITHERING_CTRL_reg(data)   (*((volatile unsigned int*) DITHERING_CTRL_reg)=data)
#define get_DITHERING_CTRL_reg   (*((volatile unsigned int*) DITHERING_CTRL_reg))
#define DITHERING_CTRL_inst_adr                                                      "0x002D"
#define DITHERING_CTRL_inst                                                          0x002D
#define DITHERING_CTRL_Seq_2nd_B_th_shift                                            (24)
#define DITHERING_CTRL_Seq_2nd_B_th_mask                                             (0xFF000000)
#define DITHERING_CTRL_Seq_2nd_B_th(data)                                            (0xFF000000&((data)<<24))
#define DITHERING_CTRL_Seq_2nd_B_th_src(data)                                        ((0xFF000000&(data))>>24)
#define DITHERING_CTRL_get_Seq_2nd_B_th(data)                                        ((0xFF000000&(data))>>24)
#define DITHERING_CTRL_Seq_2nd_G_th_shift                                            (16)
#define DITHERING_CTRL_Seq_2nd_G_th_mask                                             (0x00FF0000)
#define DITHERING_CTRL_Seq_2nd_G_th(data)                                            (0x00FF0000&((data)<<16))
#define DITHERING_CTRL_Seq_2nd_G_th_src(data)                                        ((0x00FF0000&(data))>>16)
#define DITHERING_CTRL_get_Seq_2nd_G_th(data)                                        ((0x00FF0000&(data))>>16)
#define DITHERING_CTRL_Seq_2nd_R_th_shift                                            (8)
#define DITHERING_CTRL_Seq_2nd_R_th_mask                                             (0x0000FF00)
#define DITHERING_CTRL_Seq_2nd_R_th(data)                                            (0x0000FF00&((data)<<8))
#define DITHERING_CTRL_Seq_2nd_R_th_src(data)                                        ((0x0000FF00&(data))>>8)
#define DITHERING_CTRL_get_Seq_2nd_R_th(data)                                        ((0x0000FF00&(data))>>8)
#define DITHERING_CTRL_Seq_2nd_mode_shift                                            (7)
#define DITHERING_CTRL_Seq_2nd_mode_mask                                             (0x00000080)
#define DITHERING_CTRL_Seq_2nd_mode(data)                                            (0x00000080&((data)<<7))
#define DITHERING_CTRL_Seq_2nd_mode_src(data)                                        ((0x00000080&(data))>>7)
#define DITHERING_CTRL_get_Seq_2nd_mode(data)                                        ((0x00000080&(data))>>7)
#define DITHERING_CTRL_Function_Enable_shift                                         (5)
#define DITHERING_CTRL_Function_Enable_mask                                          (0x00000020)
#define DITHERING_CTRL_Function_Enable(data)                                         (0x00000020&((data)<<5))
#define DITHERING_CTRL_Function_Enable_src(data)                                     ((0x00000020&(data))>>5)
#define DITHERING_CTRL_get_Function_Enable(data)                                     ((0x00000020&(data))>>5)
#define DITHERING_CTRL_Temporal_Enable_shift                                         (4)
#define DITHERING_CTRL_Temporal_Enable_mask                                          (0x00000010)
#define DITHERING_CTRL_Temporal_Enable(data)                                         (0x00000010&((data)<<4))
#define DITHERING_CTRL_Temporal_Enable_src(data)                                     ((0x00000010&(data))>>4)
#define DITHERING_CTRL_get_Temporal_Enable(data)                                     ((0x00000010&(data))>>4)
#define DITHERING_CTRL_Value_Sign_shift                                              (3)
#define DITHERING_CTRL_Value_Sign_mask                                               (0x00000008)
#define DITHERING_CTRL_Value_Sign(data)                                              (0x00000008&((data)<<3))
#define DITHERING_CTRL_Value_Sign_src(data)                                          ((0x00000008&(data))>>3)
#define DITHERING_CTRL_get_Value_Sign(data)                                          ((0x00000008&(data))>>3)
#define DITHERING_CTRL_Dithering_Mode_shift                                          (2)
#define DITHERING_CTRL_Dithering_Mode_mask                                           (0x00000004)
#define DITHERING_CTRL_Dithering_Mode(data)                                          (0x00000004&((data)<<2))
#define DITHERING_CTRL_Dithering_Mode_src(data)                                      ((0x00000004&(data))>>2)
#define DITHERING_CTRL_get_Dithering_Mode(data)                                      ((0x00000004&(data))>>2)
#define DITHERING_CTRL_V_Modulation_shift                                            (1)
#define DITHERING_CTRL_V_Modulation_mask                                             (0x00000002)
#define DITHERING_CTRL_V_Modulation(data)                                            (0x00000002&((data)<<1))
#define DITHERING_CTRL_V_Modulation_src(data)                                        ((0x00000002&(data))>>1)
#define DITHERING_CTRL_get_V_Modulation(data)                                        ((0x00000002&(data))>>1)
#define DITHERING_CTRL_H_Modulation_shift                                            (0)
#define DITHERING_CTRL_H_Modulation_mask                                             (0x00000001)
#define DITHERING_CTRL_H_Modulation(data)                                            (0x00000001&((data)<<0))
#define DITHERING_CTRL_H_Modulation_src(data)                                        ((0x00000001&(data))>>0)
#define DITHERING_CTRL_get_H_Modulation(data)                                        ((0x00000001&(data))>>0)


#define DITHERING_SEQ_R_0                                                            0x180098b8
#define DITHERING_SEQ_R_0_reg_addr                                                   "0xB80098B8"
#define DITHERING_SEQ_R_0_reg                                                        0xB80098B8
#define set_DITHERING_SEQ_R_0_reg(data)   (*((volatile unsigned int*) DITHERING_SEQ_R_0_reg)=data)
#define get_DITHERING_SEQ_R_0_reg   (*((volatile unsigned int*) DITHERING_SEQ_R_0_reg))
#define DITHERING_SEQ_R_0_inst_adr                                                   "0x002E"
#define DITHERING_SEQ_R_0_inst                                                       0x002E
#define DITHERING_SEQ_R_0_Seq_R_7_shift                                              (28)
#define DITHERING_SEQ_R_0_Seq_R_7_mask                                               (0xF0000000)
#define DITHERING_SEQ_R_0_Seq_R_7(data)                                              (0xF0000000&((data)<<28))
#define DITHERING_SEQ_R_0_Seq_R_7_src(data)                                          ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_R_0_get_Seq_R_7(data)                                          ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_R_0_Seq_R_6_shift                                              (24)
#define DITHERING_SEQ_R_0_Seq_R_6_mask                                               (0x0F000000)
#define DITHERING_SEQ_R_0_Seq_R_6(data)                                              (0x0F000000&((data)<<24))
#define DITHERING_SEQ_R_0_Seq_R_6_src(data)                                          ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_R_0_get_Seq_R_6(data)                                          ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_R_0_Seq_R_5_shift                                              (20)
#define DITHERING_SEQ_R_0_Seq_R_5_mask                                               (0x00F00000)
#define DITHERING_SEQ_R_0_Seq_R_5(data)                                              (0x00F00000&((data)<<20))
#define DITHERING_SEQ_R_0_Seq_R_5_src(data)                                          ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_R_0_get_Seq_R_5(data)                                          ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_R_0_Seq_R_4_shift                                              (16)
#define DITHERING_SEQ_R_0_Seq_R_4_mask                                               (0x000F0000)
#define DITHERING_SEQ_R_0_Seq_R_4(data)                                              (0x000F0000&((data)<<16))
#define DITHERING_SEQ_R_0_Seq_R_4_src(data)                                          ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_R_0_get_Seq_R_4(data)                                          ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_R_0_Seq_R_3_shift                                              (12)
#define DITHERING_SEQ_R_0_Seq_R_3_mask                                               (0x0000F000)
#define DITHERING_SEQ_R_0_Seq_R_3(data)                                              (0x0000F000&((data)<<12))
#define DITHERING_SEQ_R_0_Seq_R_3_src(data)                                          ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_R_0_get_Seq_R_3(data)                                          ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_R_0_Seq_R_2_shift                                              (8)
#define DITHERING_SEQ_R_0_Seq_R_2_mask                                               (0x00000F00)
#define DITHERING_SEQ_R_0_Seq_R_2(data)                                              (0x00000F00&((data)<<8))
#define DITHERING_SEQ_R_0_Seq_R_2_src(data)                                          ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_R_0_get_Seq_R_2(data)                                          ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_R_0_Seq_R_1_shift                                              (4)
#define DITHERING_SEQ_R_0_Seq_R_1_mask                                               (0x000000F0)
#define DITHERING_SEQ_R_0_Seq_R_1(data)                                              (0x000000F0&((data)<<4))
#define DITHERING_SEQ_R_0_Seq_R_1_src(data)                                          ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_R_0_get_Seq_R_1(data)                                          ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_R_0_Seq_R_0_shift                                              (0)
#define DITHERING_SEQ_R_0_Seq_R_0_mask                                               (0x0000000F)
#define DITHERING_SEQ_R_0_Seq_R_0(data)                                              (0x0000000F&((data)<<0))
#define DITHERING_SEQ_R_0_Seq_R_0_src(data)                                          ((0x0000000F&(data))>>0)
#define DITHERING_SEQ_R_0_get_Seq_R_0(data)                                          ((0x0000000F&(data))>>0)


#define DITHERING_SEQ_R_1                                                            0x180098bc
#define DITHERING_SEQ_R_1_reg_addr                                                   "0xB80098BC"
#define DITHERING_SEQ_R_1_reg                                                        0xB80098BC
#define set_DITHERING_SEQ_R_1_reg(data)   (*((volatile unsigned int*) DITHERING_SEQ_R_1_reg)=data)
#define get_DITHERING_SEQ_R_1_reg   (*((volatile unsigned int*) DITHERING_SEQ_R_1_reg))
#define DITHERING_SEQ_R_1_inst_adr                                                   "0x002F"
#define DITHERING_SEQ_R_1_inst                                                       0x002F
#define DITHERING_SEQ_R_1_Seq_R_15_shift                                             (28)
#define DITHERING_SEQ_R_1_Seq_R_15_mask                                              (0xF0000000)
#define DITHERING_SEQ_R_1_Seq_R_15(data)                                             (0xF0000000&((data)<<28))
#define DITHERING_SEQ_R_1_Seq_R_15_src(data)                                         ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_R_1_get_Seq_R_15(data)                                         ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_R_1_Seq_R_14_shift                                             (24)
#define DITHERING_SEQ_R_1_Seq_R_14_mask                                              (0x0F000000)
#define DITHERING_SEQ_R_1_Seq_R_14(data)                                             (0x0F000000&((data)<<24))
#define DITHERING_SEQ_R_1_Seq_R_14_src(data)                                         ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_R_1_get_Seq_R_14(data)                                         ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_R_1_Seq_R_13_shift                                             (20)
#define DITHERING_SEQ_R_1_Seq_R_13_mask                                              (0x00F00000)
#define DITHERING_SEQ_R_1_Seq_R_13(data)                                             (0x00F00000&((data)<<20))
#define DITHERING_SEQ_R_1_Seq_R_13_src(data)                                         ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_R_1_get_Seq_R_13(data)                                         ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_R_1_Seq_R_12_shift                                             (16)
#define DITHERING_SEQ_R_1_Seq_R_12_mask                                              (0x000F0000)
#define DITHERING_SEQ_R_1_Seq_R_12(data)                                             (0x000F0000&((data)<<16))
#define DITHERING_SEQ_R_1_Seq_R_12_src(data)                                         ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_R_1_get_Seq_R_12(data)                                         ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_R_1_Seq_R_11_shift                                             (12)
#define DITHERING_SEQ_R_1_Seq_R_11_mask                                              (0x0000F000)
#define DITHERING_SEQ_R_1_Seq_R_11(data)                                             (0x0000F000&((data)<<12))
#define DITHERING_SEQ_R_1_Seq_R_11_src(data)                                         ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_R_1_get_Seq_R_11(data)                                         ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_R_1_Seq_R_10_shift                                             (8)
#define DITHERING_SEQ_R_1_Seq_R_10_mask                                              (0x00000F00)
#define DITHERING_SEQ_R_1_Seq_R_10(data)                                             (0x00000F00&((data)<<8))
#define DITHERING_SEQ_R_1_Seq_R_10_src(data)                                         ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_R_1_get_Seq_R_10(data)                                         ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_R_1_Seq_R_9_shift                                              (4)
#define DITHERING_SEQ_R_1_Seq_R_9_mask                                               (0x000000F0)
#define DITHERING_SEQ_R_1_Seq_R_9(data)                                              (0x000000F0&((data)<<4))
#define DITHERING_SEQ_R_1_Seq_R_9_src(data)                                          ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_R_1_get_Seq_R_9(data)                                          ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_R_1_Seq_R_8_shift                                              (0)
#define DITHERING_SEQ_R_1_Seq_R_8_mask                                               (0x0000000F)
#define DITHERING_SEQ_R_1_Seq_R_8(data)                                              (0x0000000F&((data)<<0))
#define DITHERING_SEQ_R_1_Seq_R_8_src(data)                                          ((0x0000000F&(data))>>0)
#define DITHERING_SEQ_R_1_get_Seq_R_8(data)                                          ((0x0000000F&(data))>>0)


#define DITHERING_SEQ_R_2                                                            0x180098c0
#define DITHERING_SEQ_R_2_reg_addr                                                   "0xB80098C0"
#define DITHERING_SEQ_R_2_reg                                                        0xB80098C0
#define set_DITHERING_SEQ_R_2_reg(data)   (*((volatile unsigned int*) DITHERING_SEQ_R_2_reg)=data)
#define get_DITHERING_SEQ_R_2_reg   (*((volatile unsigned int*) DITHERING_SEQ_R_2_reg))
#define DITHERING_SEQ_R_2_inst_adr                                                   "0x0030"
#define DITHERING_SEQ_R_2_inst                                                       0x0030
#define DITHERING_SEQ_R_2_Seq_R_23_shift                                             (28)
#define DITHERING_SEQ_R_2_Seq_R_23_mask                                              (0xF0000000)
#define DITHERING_SEQ_R_2_Seq_R_23(data)                                             (0xF0000000&((data)<<28))
#define DITHERING_SEQ_R_2_Seq_R_23_src(data)                                         ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_R_2_get_Seq_R_23(data)                                         ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_R_2_Seq_R_22_shift                                             (24)
#define DITHERING_SEQ_R_2_Seq_R_22_mask                                              (0x0F000000)
#define DITHERING_SEQ_R_2_Seq_R_22(data)                                             (0x0F000000&((data)<<24))
#define DITHERING_SEQ_R_2_Seq_R_22_src(data)                                         ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_R_2_get_Seq_R_22(data)                                         ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_R_2_Seq_R_21_shift                                             (20)
#define DITHERING_SEQ_R_2_Seq_R_21_mask                                              (0x00F00000)
#define DITHERING_SEQ_R_2_Seq_R_21(data)                                             (0x00F00000&((data)<<20))
#define DITHERING_SEQ_R_2_Seq_R_21_src(data)                                         ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_R_2_get_Seq_R_21(data)                                         ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_R_2_Seq_R_20_shift                                             (16)
#define DITHERING_SEQ_R_2_Seq_R_20_mask                                              (0x000F0000)
#define DITHERING_SEQ_R_2_Seq_R_20(data)                                             (0x000F0000&((data)<<16))
#define DITHERING_SEQ_R_2_Seq_R_20_src(data)                                         ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_R_2_get_Seq_R_20(data)                                         ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_R_2_Seq_R_19_shift                                             (12)
#define DITHERING_SEQ_R_2_Seq_R_19_mask                                              (0x0000F000)
#define DITHERING_SEQ_R_2_Seq_R_19(data)                                             (0x0000F000&((data)<<12))
#define DITHERING_SEQ_R_2_Seq_R_19_src(data)                                         ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_R_2_get_Seq_R_19(data)                                         ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_R_2_Seq_R_18_shift                                             (8)
#define DITHERING_SEQ_R_2_Seq_R_18_mask                                              (0x00000F00)
#define DITHERING_SEQ_R_2_Seq_R_18(data)                                             (0x00000F00&((data)<<8))
#define DITHERING_SEQ_R_2_Seq_R_18_src(data)                                         ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_R_2_get_Seq_R_18(data)                                         ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_R_2_Seq_R_17_shift                                             (4)
#define DITHERING_SEQ_R_2_Seq_R_17_mask                                              (0x000000F0)
#define DITHERING_SEQ_R_2_Seq_R_17(data)                                             (0x000000F0&((data)<<4))
#define DITHERING_SEQ_R_2_Seq_R_17_src(data)                                         ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_R_2_get_Seq_R_17(data)                                         ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_R_2_Seq_R_16_shift                                             (0)
#define DITHERING_SEQ_R_2_Seq_R_16_mask                                              (0x0000000F)
#define DITHERING_SEQ_R_2_Seq_R_16(data)                                             (0x0000000F&((data)<<0))
#define DITHERING_SEQ_R_2_Seq_R_16_src(data)                                         ((0x0000000F&(data))>>0)
#define DITHERING_SEQ_R_2_get_Seq_R_16(data)                                         ((0x0000000F&(data))>>0)


#define DITHERING_SEQ_R_3                                                            0x180098c4
#define DITHERING_SEQ_R_3_reg_addr                                                   "0xB80098C4"
#define DITHERING_SEQ_R_3_reg                                                        0xB80098C4
#define set_DITHERING_SEQ_R_3_reg(data)   (*((volatile unsigned int*) DITHERING_SEQ_R_3_reg)=data)
#define get_DITHERING_SEQ_R_3_reg   (*((volatile unsigned int*) DITHERING_SEQ_R_3_reg))
#define DITHERING_SEQ_R_3_inst_adr                                                   "0x0031"
#define DITHERING_SEQ_R_3_inst                                                       0x0031
#define DITHERING_SEQ_R_3_Seq_R_31_shift                                             (28)
#define DITHERING_SEQ_R_3_Seq_R_31_mask                                              (0xF0000000)
#define DITHERING_SEQ_R_3_Seq_R_31(data)                                             (0xF0000000&((data)<<28))
#define DITHERING_SEQ_R_3_Seq_R_31_src(data)                                         ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_R_3_get_Seq_R_31(data)                                         ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_R_3_Seq_R_30_shift                                             (24)
#define DITHERING_SEQ_R_3_Seq_R_30_mask                                              (0x0F000000)
#define DITHERING_SEQ_R_3_Seq_R_30(data)                                             (0x0F000000&((data)<<24))
#define DITHERING_SEQ_R_3_Seq_R_30_src(data)                                         ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_R_3_get_Seq_R_30(data)                                         ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_R_3_Seq_R_29_shift                                             (20)
#define DITHERING_SEQ_R_3_Seq_R_29_mask                                              (0x00F00000)
#define DITHERING_SEQ_R_3_Seq_R_29(data)                                             (0x00F00000&((data)<<20))
#define DITHERING_SEQ_R_3_Seq_R_29_src(data)                                         ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_R_3_get_Seq_R_29(data)                                         ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_R_3_Seq_R_28_shift                                             (16)
#define DITHERING_SEQ_R_3_Seq_R_28_mask                                              (0x000F0000)
#define DITHERING_SEQ_R_3_Seq_R_28(data)                                             (0x000F0000&((data)<<16))
#define DITHERING_SEQ_R_3_Seq_R_28_src(data)                                         ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_R_3_get_Seq_R_28(data)                                         ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_R_3_Seq_R_27_shift                                             (12)
#define DITHERING_SEQ_R_3_Seq_R_27_mask                                              (0x0000F000)
#define DITHERING_SEQ_R_3_Seq_R_27(data)                                             (0x0000F000&((data)<<12))
#define DITHERING_SEQ_R_3_Seq_R_27_src(data)                                         ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_R_3_get_Seq_R_27(data)                                         ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_R_3_Seq_R_26_shift                                             (8)
#define DITHERING_SEQ_R_3_Seq_R_26_mask                                              (0x00000F00)
#define DITHERING_SEQ_R_3_Seq_R_26(data)                                             (0x00000F00&((data)<<8))
#define DITHERING_SEQ_R_3_Seq_R_26_src(data)                                         ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_R_3_get_Seq_R_26(data)                                         ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_R_3_Seq_R_25_shift                                             (4)
#define DITHERING_SEQ_R_3_Seq_R_25_mask                                              (0x000000F0)
#define DITHERING_SEQ_R_3_Seq_R_25(data)                                             (0x000000F0&((data)<<4))
#define DITHERING_SEQ_R_3_Seq_R_25_src(data)                                         ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_R_3_get_Seq_R_25(data)                                         ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_R_3_Seq_R_24_shift                                             (0)
#define DITHERING_SEQ_R_3_Seq_R_24_mask                                              (0x0000000F)
#define DITHERING_SEQ_R_3_Seq_R_24(data)                                             (0x0000000F&((data)<<0))
#define DITHERING_SEQ_R_3_Seq_R_24_src(data)                                         ((0x0000000F&(data))>>0)
#define DITHERING_SEQ_R_3_get_Seq_R_24(data)                                         ((0x0000000F&(data))>>0)


#define DITHERING_SEQ_G_0                                                            0x180098c8
#define DITHERING_SEQ_G_0_reg_addr                                                   "0xB80098C8"
#define DITHERING_SEQ_G_0_reg                                                        0xB80098C8
#define set_DITHERING_SEQ_G_0_reg(data)   (*((volatile unsigned int*) DITHERING_SEQ_G_0_reg)=data)
#define get_DITHERING_SEQ_G_0_reg   (*((volatile unsigned int*) DITHERING_SEQ_G_0_reg))
#define DITHERING_SEQ_G_0_inst_adr                                                   "0x0032"
#define DITHERING_SEQ_G_0_inst                                                       0x0032
#define DITHERING_SEQ_G_0_Seq_G_7_shift                                              (28)
#define DITHERING_SEQ_G_0_Seq_G_7_mask                                               (0xF0000000)
#define DITHERING_SEQ_G_0_Seq_G_7(data)                                              (0xF0000000&((data)<<28))
#define DITHERING_SEQ_G_0_Seq_G_7_src(data)                                          ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_G_0_get_Seq_G_7(data)                                          ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_G_0_Seq_G_6_shift                                              (24)
#define DITHERING_SEQ_G_0_Seq_G_6_mask                                               (0x0F000000)
#define DITHERING_SEQ_G_0_Seq_G_6(data)                                              (0x0F000000&((data)<<24))
#define DITHERING_SEQ_G_0_Seq_G_6_src(data)                                          ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_G_0_get_Seq_G_6(data)                                          ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_G_0_Seq_G_5_shift                                              (20)
#define DITHERING_SEQ_G_0_Seq_G_5_mask                                               (0x00F00000)
#define DITHERING_SEQ_G_0_Seq_G_5(data)                                              (0x00F00000&((data)<<20))
#define DITHERING_SEQ_G_0_Seq_G_5_src(data)                                          ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_G_0_get_Seq_G_5(data)                                          ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_G_0_Seq_G_4_shift                                              (16)
#define DITHERING_SEQ_G_0_Seq_G_4_mask                                               (0x000F0000)
#define DITHERING_SEQ_G_0_Seq_G_4(data)                                              (0x000F0000&((data)<<16))
#define DITHERING_SEQ_G_0_Seq_G_4_src(data)                                          ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_G_0_get_Seq_G_4(data)                                          ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_G_0_Seq_G_3_shift                                              (12)
#define DITHERING_SEQ_G_0_Seq_G_3_mask                                               (0x0000F000)
#define DITHERING_SEQ_G_0_Seq_G_3(data)                                              (0x0000F000&((data)<<12))
#define DITHERING_SEQ_G_0_Seq_G_3_src(data)                                          ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_G_0_get_Seq_G_3(data)                                          ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_G_0_Seq_G_2_shift                                              (8)
#define DITHERING_SEQ_G_0_Seq_G_2_mask                                               (0x00000F00)
#define DITHERING_SEQ_G_0_Seq_G_2(data)                                              (0x00000F00&((data)<<8))
#define DITHERING_SEQ_G_0_Seq_G_2_src(data)                                          ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_G_0_get_Seq_G_2(data)                                          ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_G_0_Seq_G_1_shift                                              (4)
#define DITHERING_SEQ_G_0_Seq_G_1_mask                                               (0x000000F0)
#define DITHERING_SEQ_G_0_Seq_G_1(data)                                              (0x000000F0&((data)<<4))
#define DITHERING_SEQ_G_0_Seq_G_1_src(data)                                          ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_G_0_get_Seq_G_1(data)                                          ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_G_0_Seq_G_0_shift                                              (0)
#define DITHERING_SEQ_G_0_Seq_G_0_mask                                               (0x0000000F)
#define DITHERING_SEQ_G_0_Seq_G_0(data)                                              (0x0000000F&((data)<<0))
#define DITHERING_SEQ_G_0_Seq_G_0_src(data)                                          ((0x0000000F&(data))>>0)
#define DITHERING_SEQ_G_0_get_Seq_G_0(data)                                          ((0x0000000F&(data))>>0)


#define DITHERING_SEQ_G_1                                                            0x180098cc
#define DITHERING_SEQ_G_1_reg_addr                                                   "0xB80098CC"
#define DITHERING_SEQ_G_1_reg                                                        0xB80098CC
#define set_DITHERING_SEQ_G_1_reg(data)   (*((volatile unsigned int*) DITHERING_SEQ_G_1_reg)=data)
#define get_DITHERING_SEQ_G_1_reg   (*((volatile unsigned int*) DITHERING_SEQ_G_1_reg))
#define DITHERING_SEQ_G_1_inst_adr                                                   "0x0033"
#define DITHERING_SEQ_G_1_inst                                                       0x0033
#define DITHERING_SEQ_G_1_Seq_G_15_shift                                             (28)
#define DITHERING_SEQ_G_1_Seq_G_15_mask                                              (0xF0000000)
#define DITHERING_SEQ_G_1_Seq_G_15(data)                                             (0xF0000000&((data)<<28))
#define DITHERING_SEQ_G_1_Seq_G_15_src(data)                                         ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_G_1_get_Seq_G_15(data)                                         ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_G_1_Seq_G_14_shift                                             (24)
#define DITHERING_SEQ_G_1_Seq_G_14_mask                                              (0x0F000000)
#define DITHERING_SEQ_G_1_Seq_G_14(data)                                             (0x0F000000&((data)<<24))
#define DITHERING_SEQ_G_1_Seq_G_14_src(data)                                         ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_G_1_get_Seq_G_14(data)                                         ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_G_1_Seq_G_13_shift                                             (20)
#define DITHERING_SEQ_G_1_Seq_G_13_mask                                              (0x00F00000)
#define DITHERING_SEQ_G_1_Seq_G_13(data)                                             (0x00F00000&((data)<<20))
#define DITHERING_SEQ_G_1_Seq_G_13_src(data)                                         ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_G_1_get_Seq_G_13(data)                                         ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_G_1_Seq_G_12_shift                                             (16)
#define DITHERING_SEQ_G_1_Seq_G_12_mask                                              (0x000F0000)
#define DITHERING_SEQ_G_1_Seq_G_12(data)                                             (0x000F0000&((data)<<16))
#define DITHERING_SEQ_G_1_Seq_G_12_src(data)                                         ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_G_1_get_Seq_G_12(data)                                         ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_G_1_Seq_G_11_shift                                             (12)
#define DITHERING_SEQ_G_1_Seq_G_11_mask                                              (0x0000F000)
#define DITHERING_SEQ_G_1_Seq_G_11(data)                                             (0x0000F000&((data)<<12))
#define DITHERING_SEQ_G_1_Seq_G_11_src(data)                                         ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_G_1_get_Seq_G_11(data)                                         ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_G_1_Seq_G_10_shift                                             (8)
#define DITHERING_SEQ_G_1_Seq_G_10_mask                                              (0x00000F00)
#define DITHERING_SEQ_G_1_Seq_G_10(data)                                             (0x00000F00&((data)<<8))
#define DITHERING_SEQ_G_1_Seq_G_10_src(data)                                         ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_G_1_get_Seq_G_10(data)                                         ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_G_1_Seq_G_9_shift                                              (4)
#define DITHERING_SEQ_G_1_Seq_G_9_mask                                               (0x000000F0)
#define DITHERING_SEQ_G_1_Seq_G_9(data)                                              (0x000000F0&((data)<<4))
#define DITHERING_SEQ_G_1_Seq_G_9_src(data)                                          ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_G_1_get_Seq_G_9(data)                                          ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_G_1_Seq_G_8_shift                                              (0)
#define DITHERING_SEQ_G_1_Seq_G_8_mask                                               (0x0000000F)
#define DITHERING_SEQ_G_1_Seq_G_8(data)                                              (0x0000000F&((data)<<0))
#define DITHERING_SEQ_G_1_Seq_G_8_src(data)                                          ((0x0000000F&(data))>>0)
#define DITHERING_SEQ_G_1_get_Seq_G_8(data)                                          ((0x0000000F&(data))>>0)


#define DITHERING_SEQ_G_2                                                            0x180098d0
#define DITHERING_SEQ_G_2_reg_addr                                                   "0xB80098D0"
#define DITHERING_SEQ_G_2_reg                                                        0xB80098D0
#define set_DITHERING_SEQ_G_2_reg(data)   (*((volatile unsigned int*) DITHERING_SEQ_G_2_reg)=data)
#define get_DITHERING_SEQ_G_2_reg   (*((volatile unsigned int*) DITHERING_SEQ_G_2_reg))
#define DITHERING_SEQ_G_2_inst_adr                                                   "0x0034"
#define DITHERING_SEQ_G_2_inst                                                       0x0034
#define DITHERING_SEQ_G_2_Seq_G_23_shift                                             (28)
#define DITHERING_SEQ_G_2_Seq_G_23_mask                                              (0xF0000000)
#define DITHERING_SEQ_G_2_Seq_G_23(data)                                             (0xF0000000&((data)<<28))
#define DITHERING_SEQ_G_2_Seq_G_23_src(data)                                         ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_G_2_get_Seq_G_23(data)                                         ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_G_2_Seq_G_22_shift                                             (24)
#define DITHERING_SEQ_G_2_Seq_G_22_mask                                              (0x0F000000)
#define DITHERING_SEQ_G_2_Seq_G_22(data)                                             (0x0F000000&((data)<<24))
#define DITHERING_SEQ_G_2_Seq_G_22_src(data)                                         ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_G_2_get_Seq_G_22(data)                                         ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_G_2_Seq_G_21_shift                                             (20)
#define DITHERING_SEQ_G_2_Seq_G_21_mask                                              (0x00F00000)
#define DITHERING_SEQ_G_2_Seq_G_21(data)                                             (0x00F00000&((data)<<20))
#define DITHERING_SEQ_G_2_Seq_G_21_src(data)                                         ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_G_2_get_Seq_G_21(data)                                         ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_G_2_Seq_G_20_shift                                             (16)
#define DITHERING_SEQ_G_2_Seq_G_20_mask                                              (0x000F0000)
#define DITHERING_SEQ_G_2_Seq_G_20(data)                                             (0x000F0000&((data)<<16))
#define DITHERING_SEQ_G_2_Seq_G_20_src(data)                                         ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_G_2_get_Seq_G_20(data)                                         ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_G_2_Seq_G_19_shift                                             (12)
#define DITHERING_SEQ_G_2_Seq_G_19_mask                                              (0x0000F000)
#define DITHERING_SEQ_G_2_Seq_G_19(data)                                             (0x0000F000&((data)<<12))
#define DITHERING_SEQ_G_2_Seq_G_19_src(data)                                         ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_G_2_get_Seq_G_19(data)                                         ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_G_2_Seq_G_18_shift                                             (8)
#define DITHERING_SEQ_G_2_Seq_G_18_mask                                              (0x00000F00)
#define DITHERING_SEQ_G_2_Seq_G_18(data)                                             (0x00000F00&((data)<<8))
#define DITHERING_SEQ_G_2_Seq_G_18_src(data)                                         ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_G_2_get_Seq_G_18(data)                                         ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_G_2_Seq_G_17_shift                                             (4)
#define DITHERING_SEQ_G_2_Seq_G_17_mask                                              (0x000000F0)
#define DITHERING_SEQ_G_2_Seq_G_17(data)                                             (0x000000F0&((data)<<4))
#define DITHERING_SEQ_G_2_Seq_G_17_src(data)                                         ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_G_2_get_Seq_G_17(data)                                         ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_G_2_Seq_G_16_shift                                             (0)
#define DITHERING_SEQ_G_2_Seq_G_16_mask                                              (0x0000000F)
#define DITHERING_SEQ_G_2_Seq_G_16(data)                                             (0x0000000F&((data)<<0))
#define DITHERING_SEQ_G_2_Seq_G_16_src(data)                                         ((0x0000000F&(data))>>0)
#define DITHERING_SEQ_G_2_get_Seq_G_16(data)                                         ((0x0000000F&(data))>>0)


#define DITHERING_SEQ_G_3                                                            0x180098d4
#define DITHERING_SEQ_G_3_reg_addr                                                   "0xB80098D4"
#define DITHERING_SEQ_G_3_reg                                                        0xB80098D4
#define set_DITHERING_SEQ_G_3_reg(data)   (*((volatile unsigned int*) DITHERING_SEQ_G_3_reg)=data)
#define get_DITHERING_SEQ_G_3_reg   (*((volatile unsigned int*) DITHERING_SEQ_G_3_reg))
#define DITHERING_SEQ_G_3_inst_adr                                                   "0x0035"
#define DITHERING_SEQ_G_3_inst                                                       0x0035
#define DITHERING_SEQ_G_3_Seq_G_31_shift                                             (28)
#define DITHERING_SEQ_G_3_Seq_G_31_mask                                              (0xF0000000)
#define DITHERING_SEQ_G_3_Seq_G_31(data)                                             (0xF0000000&((data)<<28))
#define DITHERING_SEQ_G_3_Seq_G_31_src(data)                                         ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_G_3_get_Seq_G_31(data)                                         ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_G_3_Seq_G_30_shift                                             (24)
#define DITHERING_SEQ_G_3_Seq_G_30_mask                                              (0x0F000000)
#define DITHERING_SEQ_G_3_Seq_G_30(data)                                             (0x0F000000&((data)<<24))
#define DITHERING_SEQ_G_3_Seq_G_30_src(data)                                         ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_G_3_get_Seq_G_30(data)                                         ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_G_3_Seq_G_29_shift                                             (20)
#define DITHERING_SEQ_G_3_Seq_G_29_mask                                              (0x00F00000)
#define DITHERING_SEQ_G_3_Seq_G_29(data)                                             (0x00F00000&((data)<<20))
#define DITHERING_SEQ_G_3_Seq_G_29_src(data)                                         ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_G_3_get_Seq_G_29(data)                                         ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_G_3_Seq_G_28_shift                                             (16)
#define DITHERING_SEQ_G_3_Seq_G_28_mask                                              (0x000F0000)
#define DITHERING_SEQ_G_3_Seq_G_28(data)                                             (0x000F0000&((data)<<16))
#define DITHERING_SEQ_G_3_Seq_G_28_src(data)                                         ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_G_3_get_Seq_G_28(data)                                         ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_G_3_Seq_G_27_shift                                             (12)
#define DITHERING_SEQ_G_3_Seq_G_27_mask                                              (0x0000F000)
#define DITHERING_SEQ_G_3_Seq_G_27(data)                                             (0x0000F000&((data)<<12))
#define DITHERING_SEQ_G_3_Seq_G_27_src(data)                                         ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_G_3_get_Seq_G_27(data)                                         ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_G_3_Seq_G_26_shift                                             (8)
#define DITHERING_SEQ_G_3_Seq_G_26_mask                                              (0x00000F00)
#define DITHERING_SEQ_G_3_Seq_G_26(data)                                             (0x00000F00&((data)<<8))
#define DITHERING_SEQ_G_3_Seq_G_26_src(data)                                         ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_G_3_get_Seq_G_26(data)                                         ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_G_3_Seq_G_25_shift                                             (4)
#define DITHERING_SEQ_G_3_Seq_G_25_mask                                              (0x000000F0)
#define DITHERING_SEQ_G_3_Seq_G_25(data)                                             (0x000000F0&((data)<<4))
#define DITHERING_SEQ_G_3_Seq_G_25_src(data)                                         ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_G_3_get_Seq_G_25(data)                                         ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_G_3_Seq_G_24_shift                                             (0)
#define DITHERING_SEQ_G_3_Seq_G_24_mask                                              (0x0000000F)
#define DITHERING_SEQ_G_3_Seq_G_24(data)                                             (0x0000000F&((data)<<0))
#define DITHERING_SEQ_G_3_Seq_G_24_src(data)                                         ((0x0000000F&(data))>>0)
#define DITHERING_SEQ_G_3_get_Seq_G_24(data)                                         ((0x0000000F&(data))>>0)


#define DITHERING_SEQ_B_0                                                            0x180098d8
#define DITHERING_SEQ_B_0_reg_addr                                                   "0xB80098D8"
#define DITHERING_SEQ_B_0_reg                                                        0xB80098D8
#define set_DITHERING_SEQ_B_0_reg(data)   (*((volatile unsigned int*) DITHERING_SEQ_B_0_reg)=data)
#define get_DITHERING_SEQ_B_0_reg   (*((volatile unsigned int*) DITHERING_SEQ_B_0_reg))
#define DITHERING_SEQ_B_0_inst_adr                                                   "0x0036"
#define DITHERING_SEQ_B_0_inst                                                       0x0036
#define DITHERING_SEQ_B_0_Seq_B_7_shift                                              (28)
#define DITHERING_SEQ_B_0_Seq_B_7_mask                                               (0xF0000000)
#define DITHERING_SEQ_B_0_Seq_B_7(data)                                              (0xF0000000&((data)<<28))
#define DITHERING_SEQ_B_0_Seq_B_7_src(data)                                          ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_B_0_get_Seq_B_7(data)                                          ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_B_0_Seq_B_6_shift                                              (24)
#define DITHERING_SEQ_B_0_Seq_B_6_mask                                               (0x0F000000)
#define DITHERING_SEQ_B_0_Seq_B_6(data)                                              (0x0F000000&((data)<<24))
#define DITHERING_SEQ_B_0_Seq_B_6_src(data)                                          ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_B_0_get_Seq_B_6(data)                                          ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_B_0_Seq_B_5_shift                                              (20)
#define DITHERING_SEQ_B_0_Seq_B_5_mask                                               (0x00F00000)
#define DITHERING_SEQ_B_0_Seq_B_5(data)                                              (0x00F00000&((data)<<20))
#define DITHERING_SEQ_B_0_Seq_B_5_src(data)                                          ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_B_0_get_Seq_B_5(data)                                          ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_B_0_Seq_B_4_shift                                              (16)
#define DITHERING_SEQ_B_0_Seq_B_4_mask                                               (0x000F0000)
#define DITHERING_SEQ_B_0_Seq_B_4(data)                                              (0x000F0000&((data)<<16))
#define DITHERING_SEQ_B_0_Seq_B_4_src(data)                                          ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_B_0_get_Seq_B_4(data)                                          ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_B_0_Seq_B_3_shift                                              (12)
#define DITHERING_SEQ_B_0_Seq_B_3_mask                                               (0x0000F000)
#define DITHERING_SEQ_B_0_Seq_B_3(data)                                              (0x0000F000&((data)<<12))
#define DITHERING_SEQ_B_0_Seq_B_3_src(data)                                          ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_B_0_get_Seq_B_3(data)                                          ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_B_0_Seq_B_2_shift                                              (8)
#define DITHERING_SEQ_B_0_Seq_B_2_mask                                               (0x00000F00)
#define DITHERING_SEQ_B_0_Seq_B_2(data)                                              (0x00000F00&((data)<<8))
#define DITHERING_SEQ_B_0_Seq_B_2_src(data)                                          ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_B_0_get_Seq_B_2(data)                                          ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_B_0_Seq_B_1_shift                                              (4)
#define DITHERING_SEQ_B_0_Seq_B_1_mask                                               (0x000000F0)
#define DITHERING_SEQ_B_0_Seq_B_1(data)                                              (0x000000F0&((data)<<4))
#define DITHERING_SEQ_B_0_Seq_B_1_src(data)                                          ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_B_0_get_Seq_B_1(data)                                          ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_B_0_Seq_B_0_shift                                              (0)
#define DITHERING_SEQ_B_0_Seq_B_0_mask                                               (0x0000000F)
#define DITHERING_SEQ_B_0_Seq_B_0(data)                                              (0x0000000F&((data)<<0))
#define DITHERING_SEQ_B_0_Seq_B_0_src(data)                                          ((0x0000000F&(data))>>0)
#define DITHERING_SEQ_B_0_get_Seq_B_0(data)                                          ((0x0000000F&(data))>>0)


#define DITHERING_SEQ_B_1                                                            0x180098dc
#define DITHERING_SEQ_B_1_reg_addr                                                   "0xB80098DC"
#define DITHERING_SEQ_B_1_reg                                                        0xB80098DC
#define set_DITHERING_SEQ_B_1_reg(data)   (*((volatile unsigned int*) DITHERING_SEQ_B_1_reg)=data)
#define get_DITHERING_SEQ_B_1_reg   (*((volatile unsigned int*) DITHERING_SEQ_B_1_reg))
#define DITHERING_SEQ_B_1_inst_adr                                                   "0x0037"
#define DITHERING_SEQ_B_1_inst                                                       0x0037
#define DITHERING_SEQ_B_1_Seq_B_15_shift                                             (28)
#define DITHERING_SEQ_B_1_Seq_B_15_mask                                              (0xF0000000)
#define DITHERING_SEQ_B_1_Seq_B_15(data)                                             (0xF0000000&((data)<<28))
#define DITHERING_SEQ_B_1_Seq_B_15_src(data)                                         ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_B_1_get_Seq_B_15(data)                                         ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_B_1_Seq_B_14_shift                                             (24)
#define DITHERING_SEQ_B_1_Seq_B_14_mask                                              (0x0F000000)
#define DITHERING_SEQ_B_1_Seq_B_14(data)                                             (0x0F000000&((data)<<24))
#define DITHERING_SEQ_B_1_Seq_B_14_src(data)                                         ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_B_1_get_Seq_B_14(data)                                         ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_B_1_Seq_B_13_shift                                             (20)
#define DITHERING_SEQ_B_1_Seq_B_13_mask                                              (0x00F00000)
#define DITHERING_SEQ_B_1_Seq_B_13(data)                                             (0x00F00000&((data)<<20))
#define DITHERING_SEQ_B_1_Seq_B_13_src(data)                                         ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_B_1_get_Seq_B_13(data)                                         ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_B_1_Seq_B_12_shift                                             (16)
#define DITHERING_SEQ_B_1_Seq_B_12_mask                                              (0x000F0000)
#define DITHERING_SEQ_B_1_Seq_B_12(data)                                             (0x000F0000&((data)<<16))
#define DITHERING_SEQ_B_1_Seq_B_12_src(data)                                         ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_B_1_get_Seq_B_12(data)                                         ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_B_1_Seq_B_11_shift                                             (12)
#define DITHERING_SEQ_B_1_Seq_B_11_mask                                              (0x0000F000)
#define DITHERING_SEQ_B_1_Seq_B_11(data)                                             (0x0000F000&((data)<<12))
#define DITHERING_SEQ_B_1_Seq_B_11_src(data)                                         ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_B_1_get_Seq_B_11(data)                                         ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_B_1_Seq_B_10_shift                                             (8)
#define DITHERING_SEQ_B_1_Seq_B_10_mask                                              (0x00000F00)
#define DITHERING_SEQ_B_1_Seq_B_10(data)                                             (0x00000F00&((data)<<8))
#define DITHERING_SEQ_B_1_Seq_B_10_src(data)                                         ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_B_1_get_Seq_B_10(data)                                         ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_B_1_Seq_B_9_shift                                              (4)
#define DITHERING_SEQ_B_1_Seq_B_9_mask                                               (0x000000F0)
#define DITHERING_SEQ_B_1_Seq_B_9(data)                                              (0x000000F0&((data)<<4))
#define DITHERING_SEQ_B_1_Seq_B_9_src(data)                                          ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_B_1_get_Seq_B_9(data)                                          ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_B_1_Seq_B_8_shift                                              (0)
#define DITHERING_SEQ_B_1_Seq_B_8_mask                                               (0x0000000F)
#define DITHERING_SEQ_B_1_Seq_B_8(data)                                              (0x0000000F&((data)<<0))
#define DITHERING_SEQ_B_1_Seq_B_8_src(data)                                          ((0x0000000F&(data))>>0)
#define DITHERING_SEQ_B_1_get_Seq_B_8(data)                                          ((0x0000000F&(data))>>0)


#define DITHERING_SEQ_B_2                                                            0x180098e0
#define DITHERING_SEQ_B_2_reg_addr                                                   "0xB80098E0"
#define DITHERING_SEQ_B_2_reg                                                        0xB80098E0
#define set_DITHERING_SEQ_B_2_reg(data)   (*((volatile unsigned int*) DITHERING_SEQ_B_2_reg)=data)
#define get_DITHERING_SEQ_B_2_reg   (*((volatile unsigned int*) DITHERING_SEQ_B_2_reg))
#define DITHERING_SEQ_B_2_inst_adr                                                   "0x0038"
#define DITHERING_SEQ_B_2_inst                                                       0x0038
#define DITHERING_SEQ_B_2_Seq_B_23_shift                                             (28)
#define DITHERING_SEQ_B_2_Seq_B_23_mask                                              (0xF0000000)
#define DITHERING_SEQ_B_2_Seq_B_23(data)                                             (0xF0000000&((data)<<28))
#define DITHERING_SEQ_B_2_Seq_B_23_src(data)                                         ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_B_2_get_Seq_B_23(data)                                         ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_B_2_Seq_B_22_shift                                             (24)
#define DITHERING_SEQ_B_2_Seq_B_22_mask                                              (0x0F000000)
#define DITHERING_SEQ_B_2_Seq_B_22(data)                                             (0x0F000000&((data)<<24))
#define DITHERING_SEQ_B_2_Seq_B_22_src(data)                                         ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_B_2_get_Seq_B_22(data)                                         ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_B_2_Seq_B_21_shift                                             (20)
#define DITHERING_SEQ_B_2_Seq_B_21_mask                                              (0x00F00000)
#define DITHERING_SEQ_B_2_Seq_B_21(data)                                             (0x00F00000&((data)<<20))
#define DITHERING_SEQ_B_2_Seq_B_21_src(data)                                         ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_B_2_get_Seq_B_21(data)                                         ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_B_2_Seq_B_20_shift                                             (16)
#define DITHERING_SEQ_B_2_Seq_B_20_mask                                              (0x000F0000)
#define DITHERING_SEQ_B_2_Seq_B_20(data)                                             (0x000F0000&((data)<<16))
#define DITHERING_SEQ_B_2_Seq_B_20_src(data)                                         ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_B_2_get_Seq_B_20(data)                                         ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_B_2_Seq_B_19_shift                                             (12)
#define DITHERING_SEQ_B_2_Seq_B_19_mask                                              (0x0000F000)
#define DITHERING_SEQ_B_2_Seq_B_19(data)                                             (0x0000F000&((data)<<12))
#define DITHERING_SEQ_B_2_Seq_B_19_src(data)                                         ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_B_2_get_Seq_B_19(data)                                         ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_B_2_Seq_B_18_shift                                             (8)
#define DITHERING_SEQ_B_2_Seq_B_18_mask                                              (0x00000F00)
#define DITHERING_SEQ_B_2_Seq_B_18(data)                                             (0x00000F00&((data)<<8))
#define DITHERING_SEQ_B_2_Seq_B_18_src(data)                                         ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_B_2_get_Seq_B_18(data)                                         ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_B_2_Seq_B_17_shift                                             (4)
#define DITHERING_SEQ_B_2_Seq_B_17_mask                                              (0x000000F0)
#define DITHERING_SEQ_B_2_Seq_B_17(data)                                             (0x000000F0&((data)<<4))
#define DITHERING_SEQ_B_2_Seq_B_17_src(data)                                         ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_B_2_get_Seq_B_17(data)                                         ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_B_2_Seq_B_16_shift                                             (0)
#define DITHERING_SEQ_B_2_Seq_B_16_mask                                              (0x0000000F)
#define DITHERING_SEQ_B_2_Seq_B_16(data)                                             (0x0000000F&((data)<<0))
#define DITHERING_SEQ_B_2_Seq_B_16_src(data)                                         ((0x0000000F&(data))>>0)
#define DITHERING_SEQ_B_2_get_Seq_B_16(data)                                         ((0x0000000F&(data))>>0)


#define DITHERING_SEQ_B_3                                                            0x180098e4
#define DITHERING_SEQ_B_3_reg_addr                                                   "0xB80098E4"
#define DITHERING_SEQ_B_3_reg                                                        0xB80098E4
#define set_DITHERING_SEQ_B_3_reg(data)   (*((volatile unsigned int*) DITHERING_SEQ_B_3_reg)=data)
#define get_DITHERING_SEQ_B_3_reg   (*((volatile unsigned int*) DITHERING_SEQ_B_3_reg))
#define DITHERING_SEQ_B_3_inst_adr                                                   "0x0039"
#define DITHERING_SEQ_B_3_inst                                                       0x0039
#define DITHERING_SEQ_B_3_Seq_B_31_shift                                             (28)
#define DITHERING_SEQ_B_3_Seq_B_31_mask                                              (0xF0000000)
#define DITHERING_SEQ_B_3_Seq_B_31(data)                                             (0xF0000000&((data)<<28))
#define DITHERING_SEQ_B_3_Seq_B_31_src(data)                                         ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_B_3_get_Seq_B_31(data)                                         ((0xF0000000&(data))>>28)
#define DITHERING_SEQ_B_3_Seq_B_30_shift                                             (24)
#define DITHERING_SEQ_B_3_Seq_B_30_mask                                              (0x0F000000)
#define DITHERING_SEQ_B_3_Seq_B_30(data)                                             (0x0F000000&((data)<<24))
#define DITHERING_SEQ_B_3_Seq_B_30_src(data)                                         ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_B_3_get_Seq_B_30(data)                                         ((0x0F000000&(data))>>24)
#define DITHERING_SEQ_B_3_Seq_B_29_shift                                             (20)
#define DITHERING_SEQ_B_3_Seq_B_29_mask                                              (0x00F00000)
#define DITHERING_SEQ_B_3_Seq_B_29(data)                                             (0x00F00000&((data)<<20))
#define DITHERING_SEQ_B_3_Seq_B_29_src(data)                                         ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_B_3_get_Seq_B_29(data)                                         ((0x00F00000&(data))>>20)
#define DITHERING_SEQ_B_3_Seq_B_28_shift                                             (16)
#define DITHERING_SEQ_B_3_Seq_B_28_mask                                              (0x000F0000)
#define DITHERING_SEQ_B_3_Seq_B_28(data)                                             (0x000F0000&((data)<<16))
#define DITHERING_SEQ_B_3_Seq_B_28_src(data)                                         ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_B_3_get_Seq_B_28(data)                                         ((0x000F0000&(data))>>16)
#define DITHERING_SEQ_B_3_Seq_B_27_shift                                             (12)
#define DITHERING_SEQ_B_3_Seq_B_27_mask                                              (0x0000F000)
#define DITHERING_SEQ_B_3_Seq_B_27(data)                                             (0x0000F000&((data)<<12))
#define DITHERING_SEQ_B_3_Seq_B_27_src(data)                                         ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_B_3_get_Seq_B_27(data)                                         ((0x0000F000&(data))>>12)
#define DITHERING_SEQ_B_3_Seq_B_26_shift                                             (8)
#define DITHERING_SEQ_B_3_Seq_B_26_mask                                              (0x00000F00)
#define DITHERING_SEQ_B_3_Seq_B_26(data)                                             (0x00000F00&((data)<<8))
#define DITHERING_SEQ_B_3_Seq_B_26_src(data)                                         ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_B_3_get_Seq_B_26(data)                                         ((0x00000F00&(data))>>8)
#define DITHERING_SEQ_B_3_Seq_B_25_shift                                             (4)
#define DITHERING_SEQ_B_3_Seq_B_25_mask                                              (0x000000F0)
#define DITHERING_SEQ_B_3_Seq_B_25(data)                                             (0x000000F0&((data)<<4))
#define DITHERING_SEQ_B_3_Seq_B_25_src(data)                                         ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_B_3_get_Seq_B_25(data)                                         ((0x000000F0&(data))>>4)
#define DITHERING_SEQ_B_3_Seq_B_24_shift                                             (0)
#define DITHERING_SEQ_B_3_Seq_B_24_mask                                              (0x0000000F)
#define DITHERING_SEQ_B_3_Seq_B_24(data)                                             (0x0000000F&((data)<<0))
#define DITHERING_SEQ_B_3_Seq_B_24_src(data)                                         ((0x0000000F&(data))>>0)
#define DITHERING_SEQ_B_3_get_Seq_B_24(data)                                         ((0x0000000F&(data))>>0)


#define DITHERING_TAB_R_0                                                            0x180098e8
#define DITHERING_TAB_R_0_reg_addr                                                   "0xB80098E8"
#define DITHERING_TAB_R_0_reg                                                        0xB80098E8
#define set_DITHERING_TAB_R_0_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_R_0_reg)=data)
#define get_DITHERING_TAB_R_0_reg   (*((volatile unsigned int*) DITHERING_TAB_R_0_reg))
#define DITHERING_TAB_R_0_inst_adr                                                   "0x003A"
#define DITHERING_TAB_R_0_inst                                                       0x003A
#define DITHERING_TAB_R_0_Tab_R_03_shift                                             (18)
#define DITHERING_TAB_R_0_Tab_R_03_mask                                              (0x00FC0000)
#define DITHERING_TAB_R_0_Tab_R_03(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_R_0_Tab_R_03_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_0_get_Tab_R_03(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_0_Tab_R_02_shift                                             (12)
#define DITHERING_TAB_R_0_Tab_R_02_mask                                              (0x0003F000)
#define DITHERING_TAB_R_0_Tab_R_02(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_R_0_Tab_R_02_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_0_get_Tab_R_02(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_0_Tab_R_01_shift                                             (6)
#define DITHERING_TAB_R_0_Tab_R_01_mask                                              (0x00000FC0)
#define DITHERING_TAB_R_0_Tab_R_01(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_R_0_Tab_R_01_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_0_get_Tab_R_01(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_0_Tab_R_00_shift                                             (0)
#define DITHERING_TAB_R_0_Tab_R_00_mask                                              (0x0000003F)
#define DITHERING_TAB_R_0_Tab_R_00(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_R_0_Tab_R_00_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_R_0_get_Tab_R_00(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_R_1                                                            0x180098ec
#define DITHERING_TAB_R_1_reg_addr                                                   "0xB80098EC"
#define DITHERING_TAB_R_1_reg                                                        0xB80098EC
#define set_DITHERING_TAB_R_1_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_R_1_reg)=data)
#define get_DITHERING_TAB_R_1_reg   (*((volatile unsigned int*) DITHERING_TAB_R_1_reg))
#define DITHERING_TAB_R_1_inst_adr                                                   "0x003B"
#define DITHERING_TAB_R_1_inst                                                       0x003B
#define DITHERING_TAB_R_1_Tab_R_13_shift                                             (18)
#define DITHERING_TAB_R_1_Tab_R_13_mask                                              (0x00FC0000)
#define DITHERING_TAB_R_1_Tab_R_13(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_R_1_Tab_R_13_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_1_get_Tab_R_13(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_1_Tab_R_12_shift                                             (12)
#define DITHERING_TAB_R_1_Tab_R_12_mask                                              (0x0003F000)
#define DITHERING_TAB_R_1_Tab_R_12(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_R_1_Tab_R_12_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_1_get_Tab_R_12(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_1_Tab_R_11_shift                                             (6)
#define DITHERING_TAB_R_1_Tab_R_11_mask                                              (0x00000FC0)
#define DITHERING_TAB_R_1_Tab_R_11(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_R_1_Tab_R_11_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_1_get_Tab_R_11(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_1_Tab_R_10_shift                                             (0)
#define DITHERING_TAB_R_1_Tab_R_10_mask                                              (0x0000003F)
#define DITHERING_TAB_R_1_Tab_R_10(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_R_1_Tab_R_10_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_R_1_get_Tab_R_10(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_R_2                                                            0x180098f0
#define DITHERING_TAB_R_2_reg_addr                                                   "0xB80098F0"
#define DITHERING_TAB_R_2_reg                                                        0xB80098F0
#define set_DITHERING_TAB_R_2_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_R_2_reg)=data)
#define get_DITHERING_TAB_R_2_reg   (*((volatile unsigned int*) DITHERING_TAB_R_2_reg))
#define DITHERING_TAB_R_2_inst_adr                                                   "0x003C"
#define DITHERING_TAB_R_2_inst                                                       0x003C
#define DITHERING_TAB_R_2_Tab_R_23_shift                                             (18)
#define DITHERING_TAB_R_2_Tab_R_23_mask                                              (0x00FC0000)
#define DITHERING_TAB_R_2_Tab_R_23(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_R_2_Tab_R_23_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_2_get_Tab_R_23(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_2_Tab_R_22_shift                                             (12)
#define DITHERING_TAB_R_2_Tab_R_22_mask                                              (0x0003F000)
#define DITHERING_TAB_R_2_Tab_R_22(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_R_2_Tab_R_22_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_2_get_Tab_R_22(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_2_Tab_R_21_shift                                             (6)
#define DITHERING_TAB_R_2_Tab_R_21_mask                                              (0x00000FC0)
#define DITHERING_TAB_R_2_Tab_R_21(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_R_2_Tab_R_21_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_2_get_Tab_R_21(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_2_Tab_R_20_shift                                             (0)
#define DITHERING_TAB_R_2_Tab_R_20_mask                                              (0x0000003F)
#define DITHERING_TAB_R_2_Tab_R_20(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_R_2_Tab_R_20_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_R_2_get_Tab_R_20(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_R_3                                                            0x180098f4
#define DITHERING_TAB_R_3_reg_addr                                                   "0xB80098F4"
#define DITHERING_TAB_R_3_reg                                                        0xB80098F4
#define set_DITHERING_TAB_R_3_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_R_3_reg)=data)
#define get_DITHERING_TAB_R_3_reg   (*((volatile unsigned int*) DITHERING_TAB_R_3_reg))
#define DITHERING_TAB_R_3_inst_adr                                                   "0x003D"
#define DITHERING_TAB_R_3_inst                                                       0x003D
#define DITHERING_TAB_R_3_Tab_R_33_shift                                             (18)
#define DITHERING_TAB_R_3_Tab_R_33_mask                                              (0x00FC0000)
#define DITHERING_TAB_R_3_Tab_R_33(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_R_3_Tab_R_33_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_3_get_Tab_R_33(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_3_Tab_R_32_shift                                             (12)
#define DITHERING_TAB_R_3_Tab_R_32_mask                                              (0x0003F000)
#define DITHERING_TAB_R_3_Tab_R_32(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_R_3_Tab_R_32_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_3_get_Tab_R_32(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_3_Tab_R_31_shift                                             (6)
#define DITHERING_TAB_R_3_Tab_R_31_mask                                              (0x00000FC0)
#define DITHERING_TAB_R_3_Tab_R_31(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_R_3_Tab_R_31_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_3_get_Tab_R_31(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_3_Tab_R_30_shift                                             (0)
#define DITHERING_TAB_R_3_Tab_R_30_mask                                              (0x0000003F)
#define DITHERING_TAB_R_3_Tab_R_30(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_R_3_Tab_R_30_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_R_3_get_Tab_R_30(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_R_4                                                            0x180098f8
#define DITHERING_TAB_R_4_reg_addr                                                   "0xB80098F8"
#define DITHERING_TAB_R_4_reg                                                        0xB80098F8
#define set_DITHERING_TAB_R_4_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_R_4_reg)=data)
#define get_DITHERING_TAB_R_4_reg   (*((volatile unsigned int*) DITHERING_TAB_R_4_reg))
#define DITHERING_TAB_R_4_inst_adr                                                   "0x003E"
#define DITHERING_TAB_R_4_inst                                                       0x003E
#define DITHERING_TAB_R_4_Tab_R_43_shift                                             (18)
#define DITHERING_TAB_R_4_Tab_R_43_mask                                              (0x00FC0000)
#define DITHERING_TAB_R_4_Tab_R_43(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_R_4_Tab_R_43_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_4_get_Tab_R_43(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_4_Tab_R_42_shift                                             (12)
#define DITHERING_TAB_R_4_Tab_R_42_mask                                              (0x0003F000)
#define DITHERING_TAB_R_4_Tab_R_42(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_R_4_Tab_R_42_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_4_get_Tab_R_42(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_4_Tab_R_41_shift                                             (6)
#define DITHERING_TAB_R_4_Tab_R_41_mask                                              (0x00000FC0)
#define DITHERING_TAB_R_4_Tab_R_41(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_R_4_Tab_R_41_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_4_get_Tab_R_41(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_4_Tab_R_40_shift                                             (0)
#define DITHERING_TAB_R_4_Tab_R_40_mask                                              (0x0000003F)
#define DITHERING_TAB_R_4_Tab_R_40(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_R_4_Tab_R_40_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_R_4_get_Tab_R_40(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_R_5                                                            0x180098fc
#define DITHERING_TAB_R_5_reg_addr                                                   "0xB80098FC"
#define DITHERING_TAB_R_5_reg                                                        0xB80098FC
#define set_DITHERING_TAB_R_5_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_R_5_reg)=data)
#define get_DITHERING_TAB_R_5_reg   (*((volatile unsigned int*) DITHERING_TAB_R_5_reg))
#define DITHERING_TAB_R_5_inst_adr                                                   "0x003F"
#define DITHERING_TAB_R_5_inst                                                       0x003F
#define DITHERING_TAB_R_5_Tab_R_53_shift                                             (18)
#define DITHERING_TAB_R_5_Tab_R_53_mask                                              (0x00FC0000)
#define DITHERING_TAB_R_5_Tab_R_53(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_R_5_Tab_R_53_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_5_get_Tab_R_53(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_5_Tab_R_52_shift                                             (12)
#define DITHERING_TAB_R_5_Tab_R_52_mask                                              (0x0003F000)
#define DITHERING_TAB_R_5_Tab_R_52(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_R_5_Tab_R_52_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_5_get_Tab_R_52(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_5_Tab_R_51_shift                                             (6)
#define DITHERING_TAB_R_5_Tab_R_51_mask                                              (0x00000FC0)
#define DITHERING_TAB_R_5_Tab_R_51(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_R_5_Tab_R_51_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_5_get_Tab_R_51(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_5_Tab_R_50_shift                                             (0)
#define DITHERING_TAB_R_5_Tab_R_50_mask                                              (0x0000003F)
#define DITHERING_TAB_R_5_Tab_R_50(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_R_5_Tab_R_50_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_R_5_get_Tab_R_50(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_R_6                                                            0x18009900
#define DITHERING_TAB_R_6_reg_addr                                                   "0xB8009900"
#define DITHERING_TAB_R_6_reg                                                        0xB8009900
#define set_DITHERING_TAB_R_6_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_R_6_reg)=data)
#define get_DITHERING_TAB_R_6_reg   (*((volatile unsigned int*) DITHERING_TAB_R_6_reg))
#define DITHERING_TAB_R_6_inst_adr                                                   "0x0040"
#define DITHERING_TAB_R_6_inst                                                       0x0040
#define DITHERING_TAB_R_6_Tab_R_63_shift                                             (18)
#define DITHERING_TAB_R_6_Tab_R_63_mask                                              (0x00FC0000)
#define DITHERING_TAB_R_6_Tab_R_63(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_R_6_Tab_R_63_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_6_get_Tab_R_63(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_6_Tab_R_62_shift                                             (12)
#define DITHERING_TAB_R_6_Tab_R_62_mask                                              (0x0003F000)
#define DITHERING_TAB_R_6_Tab_R_62(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_R_6_Tab_R_62_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_6_get_Tab_R_62(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_6_Tab_R_61_shift                                             (6)
#define DITHERING_TAB_R_6_Tab_R_61_mask                                              (0x00000FC0)
#define DITHERING_TAB_R_6_Tab_R_61(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_R_6_Tab_R_61_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_6_get_Tab_R_61(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_6_Tab_R_60_shift                                             (0)
#define DITHERING_TAB_R_6_Tab_R_60_mask                                              (0x0000003F)
#define DITHERING_TAB_R_6_Tab_R_60(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_R_6_Tab_R_60_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_R_6_get_Tab_R_60(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_R_7                                                            0x18009904
#define DITHERING_TAB_R_7_reg_addr                                                   "0xB8009904"
#define DITHERING_TAB_R_7_reg                                                        0xB8009904
#define set_DITHERING_TAB_R_7_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_R_7_reg)=data)
#define get_DITHERING_TAB_R_7_reg   (*((volatile unsigned int*) DITHERING_TAB_R_7_reg))
#define DITHERING_TAB_R_7_inst_adr                                                   "0x0041"
#define DITHERING_TAB_R_7_inst                                                       0x0041
#define DITHERING_TAB_R_7_Tab_R_73_shift                                             (18)
#define DITHERING_TAB_R_7_Tab_R_73_mask                                              (0x00FC0000)
#define DITHERING_TAB_R_7_Tab_R_73(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_R_7_Tab_R_73_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_7_get_Tab_R_73(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_7_Tab_R_72_shift                                             (12)
#define DITHERING_TAB_R_7_Tab_R_72_mask                                              (0x0003F000)
#define DITHERING_TAB_R_7_Tab_R_72(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_R_7_Tab_R_72_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_7_get_Tab_R_72(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_7_Tab_R_71_shift                                             (6)
#define DITHERING_TAB_R_7_Tab_R_71_mask                                              (0x00000FC0)
#define DITHERING_TAB_R_7_Tab_R_71(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_R_7_Tab_R_71_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_7_get_Tab_R_71(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_7_Tab_R_70_shift                                             (0)
#define DITHERING_TAB_R_7_Tab_R_70_mask                                              (0x0000003F)
#define DITHERING_TAB_R_7_Tab_R_70(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_R_7_Tab_R_70_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_R_7_get_Tab_R_70(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_R_8                                                            0x18009908
#define DITHERING_TAB_R_8_reg_addr                                                   "0xB8009908"
#define DITHERING_TAB_R_8_reg                                                        0xB8009908
#define set_DITHERING_TAB_R_8_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_R_8_reg)=data)
#define get_DITHERING_TAB_R_8_reg   (*((volatile unsigned int*) DITHERING_TAB_R_8_reg))
#define DITHERING_TAB_R_8_inst_adr                                                   "0x0042"
#define DITHERING_TAB_R_8_inst                                                       0x0042
#define DITHERING_TAB_R_8_Tab_R_83_shift                                             (18)
#define DITHERING_TAB_R_8_Tab_R_83_mask                                              (0x00FC0000)
#define DITHERING_TAB_R_8_Tab_R_83(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_R_8_Tab_R_83_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_8_get_Tab_R_83(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_8_Tab_R_82_shift                                             (12)
#define DITHERING_TAB_R_8_Tab_R_82_mask                                              (0x0003F000)
#define DITHERING_TAB_R_8_Tab_R_82(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_R_8_Tab_R_82_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_8_get_Tab_R_82(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_8_Tab_R_81_shift                                             (6)
#define DITHERING_TAB_R_8_Tab_R_81_mask                                              (0x00000FC0)
#define DITHERING_TAB_R_8_Tab_R_81(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_R_8_Tab_R_81_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_8_get_Tab_R_81(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_8_Tab_R_80_shift                                             (0)
#define DITHERING_TAB_R_8_Tab_R_80_mask                                              (0x0000003F)
#define DITHERING_TAB_R_8_Tab_R_80(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_R_8_Tab_R_80_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_R_8_get_Tab_R_80(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_R_9                                                            0x1800990c
#define DITHERING_TAB_R_9_reg_addr                                                   "0xB800990C"
#define DITHERING_TAB_R_9_reg                                                        0xB800990C
#define set_DITHERING_TAB_R_9_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_R_9_reg)=data)
#define get_DITHERING_TAB_R_9_reg   (*((volatile unsigned int*) DITHERING_TAB_R_9_reg))
#define DITHERING_TAB_R_9_inst_adr                                                   "0x0043"
#define DITHERING_TAB_R_9_inst                                                       0x0043
#define DITHERING_TAB_R_9_Tab_R_93_shift                                             (18)
#define DITHERING_TAB_R_9_Tab_R_93_mask                                              (0x00FC0000)
#define DITHERING_TAB_R_9_Tab_R_93(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_R_9_Tab_R_93_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_9_get_Tab_R_93(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_9_Tab_R_92_shift                                             (12)
#define DITHERING_TAB_R_9_Tab_R_92_mask                                              (0x0003F000)
#define DITHERING_TAB_R_9_Tab_R_92(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_R_9_Tab_R_92_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_9_get_Tab_R_92(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_9_Tab_R_91_shift                                             (6)
#define DITHERING_TAB_R_9_Tab_R_91_mask                                              (0x00000FC0)
#define DITHERING_TAB_R_9_Tab_R_91(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_R_9_Tab_R_91_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_9_get_Tab_R_91(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_9_Tab_R_90_shift                                             (0)
#define DITHERING_TAB_R_9_Tab_R_90_mask                                              (0x0000003F)
#define DITHERING_TAB_R_9_Tab_R_90(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_R_9_Tab_R_90_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_R_9_get_Tab_R_90(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_R_10                                                           0x18009910
#define DITHERING_TAB_R_10_reg_addr                                                  "0xB8009910"
#define DITHERING_TAB_R_10_reg                                                       0xB8009910
#define set_DITHERING_TAB_R_10_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_R_10_reg)=data)
#define get_DITHERING_TAB_R_10_reg   (*((volatile unsigned int*) DITHERING_TAB_R_10_reg))
#define DITHERING_TAB_R_10_inst_adr                                                  "0x0044"
#define DITHERING_TAB_R_10_inst                                                      0x0044
#define DITHERING_TAB_R_10_Tab_R_A3_shift                                            (18)
#define DITHERING_TAB_R_10_Tab_R_A3_mask                                             (0x00FC0000)
#define DITHERING_TAB_R_10_Tab_R_A3(data)                                            (0x00FC0000&((data)<<18))
#define DITHERING_TAB_R_10_Tab_R_A3_src(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_10_get_Tab_R_A3(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_10_Tab_R_A2_shift                                            (12)
#define DITHERING_TAB_R_10_Tab_R_A2_mask                                             (0x0003F000)
#define DITHERING_TAB_R_10_Tab_R_A2(data)                                            (0x0003F000&((data)<<12))
#define DITHERING_TAB_R_10_Tab_R_A2_src(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_10_get_Tab_R_A2(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_10_Tab_R_A1_shift                                            (6)
#define DITHERING_TAB_R_10_Tab_R_A1_mask                                             (0x00000FC0)
#define DITHERING_TAB_R_10_Tab_R_A1(data)                                            (0x00000FC0&((data)<<6))
#define DITHERING_TAB_R_10_Tab_R_A1_src(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_10_get_Tab_R_A1(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_10_Tab_R_A0_shift                                            (0)
#define DITHERING_TAB_R_10_Tab_R_A0_mask                                             (0x0000003F)
#define DITHERING_TAB_R_10_Tab_R_A0(data)                                            (0x0000003F&((data)<<0))
#define DITHERING_TAB_R_10_Tab_R_A0_src(data)                                        ((0x0000003F&(data))>>0)
#define DITHERING_TAB_R_10_get_Tab_R_A0(data)                                        ((0x0000003F&(data))>>0)


#define DITHERING_TAB_R_11                                                           0x18009914
#define DITHERING_TAB_R_11_reg_addr                                                  "0xB8009914"
#define DITHERING_TAB_R_11_reg                                                       0xB8009914
#define set_DITHERING_TAB_R_11_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_R_11_reg)=data)
#define get_DITHERING_TAB_R_11_reg   (*((volatile unsigned int*) DITHERING_TAB_R_11_reg))
#define DITHERING_TAB_R_11_inst_adr                                                  "0x0045"
#define DITHERING_TAB_R_11_inst                                                      0x0045
#define DITHERING_TAB_R_11_Tab_R_B3_shift                                            (18)
#define DITHERING_TAB_R_11_Tab_R_B3_mask                                             (0x00FC0000)
#define DITHERING_TAB_R_11_Tab_R_B3(data)                                            (0x00FC0000&((data)<<18))
#define DITHERING_TAB_R_11_Tab_R_B3_src(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_11_get_Tab_R_B3(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_11_Tab_R_B2_shift                                            (12)
#define DITHERING_TAB_R_11_Tab_R_B2_mask                                             (0x0003F000)
#define DITHERING_TAB_R_11_Tab_R_B2(data)                                            (0x0003F000&((data)<<12))
#define DITHERING_TAB_R_11_Tab_R_B2_src(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_11_get_Tab_R_B2(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_11_Tab_R_B1_shift                                            (6)
#define DITHERING_TAB_R_11_Tab_R_B1_mask                                             (0x00000FC0)
#define DITHERING_TAB_R_11_Tab_R_B1(data)                                            (0x00000FC0&((data)<<6))
#define DITHERING_TAB_R_11_Tab_R_B1_src(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_11_get_Tab_R_B1(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_11_Tab_R_B0_shift                                            (0)
#define DITHERING_TAB_R_11_Tab_R_B0_mask                                             (0x0000003F)
#define DITHERING_TAB_R_11_Tab_R_B0(data)                                            (0x0000003F&((data)<<0))
#define DITHERING_TAB_R_11_Tab_R_B0_src(data)                                        ((0x0000003F&(data))>>0)
#define DITHERING_TAB_R_11_get_Tab_R_B0(data)                                        ((0x0000003F&(data))>>0)


#define DITHERING_TAB_R_12                                                           0x18009918
#define DITHERING_TAB_R_12_reg_addr                                                  "0xB8009918"
#define DITHERING_TAB_R_12_reg                                                       0xB8009918
#define set_DITHERING_TAB_R_12_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_R_12_reg)=data)
#define get_DITHERING_TAB_R_12_reg   (*((volatile unsigned int*) DITHERING_TAB_R_12_reg))
#define DITHERING_TAB_R_12_inst_adr                                                  "0x0046"
#define DITHERING_TAB_R_12_inst                                                      0x0046
#define DITHERING_TAB_R_12_Tab_R_C3_shift                                            (18)
#define DITHERING_TAB_R_12_Tab_R_C3_mask                                             (0x00FC0000)
#define DITHERING_TAB_R_12_Tab_R_C3(data)                                            (0x00FC0000&((data)<<18))
#define DITHERING_TAB_R_12_Tab_R_C3_src(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_12_get_Tab_R_C3(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_12_Tab_R_C2_shift                                            (12)
#define DITHERING_TAB_R_12_Tab_R_C2_mask                                             (0x0003F000)
#define DITHERING_TAB_R_12_Tab_R_C2(data)                                            (0x0003F000&((data)<<12))
#define DITHERING_TAB_R_12_Tab_R_C2_src(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_12_get_Tab_R_C2(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_12_Tab_R_C1_shift                                            (6)
#define DITHERING_TAB_R_12_Tab_R_C1_mask                                             (0x00000FC0)
#define DITHERING_TAB_R_12_Tab_R_C1(data)                                            (0x00000FC0&((data)<<6))
#define DITHERING_TAB_R_12_Tab_R_C1_src(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_12_get_Tab_R_C1(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_12_Tab_R_C0_shift                                            (0)
#define DITHERING_TAB_R_12_Tab_R_C0_mask                                             (0x0000003F)
#define DITHERING_TAB_R_12_Tab_R_C0(data)                                            (0x0000003F&((data)<<0))
#define DITHERING_TAB_R_12_Tab_R_C0_src(data)                                        ((0x0000003F&(data))>>0)
#define DITHERING_TAB_R_12_get_Tab_R_C0(data)                                        ((0x0000003F&(data))>>0)


#define DITHERING_TAB_R_13                                                           0x1800991c
#define DITHERING_TAB_R_13_reg_addr                                                  "0xB800991C"
#define DITHERING_TAB_R_13_reg                                                       0xB800991C
#define set_DITHERING_TAB_R_13_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_R_13_reg)=data)
#define get_DITHERING_TAB_R_13_reg   (*((volatile unsigned int*) DITHERING_TAB_R_13_reg))
#define DITHERING_TAB_R_13_inst_adr                                                  "0x0047"
#define DITHERING_TAB_R_13_inst                                                      0x0047
#define DITHERING_TAB_R_13_Tab_R_D3_shift                                            (18)
#define DITHERING_TAB_R_13_Tab_R_D3_mask                                             (0x00FC0000)
#define DITHERING_TAB_R_13_Tab_R_D3(data)                                            (0x00FC0000&((data)<<18))
#define DITHERING_TAB_R_13_Tab_R_D3_src(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_13_get_Tab_R_D3(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_13_Tab_R_D2_shift                                            (12)
#define DITHERING_TAB_R_13_Tab_R_D2_mask                                             (0x0003F000)
#define DITHERING_TAB_R_13_Tab_R_D2(data)                                            (0x0003F000&((data)<<12))
#define DITHERING_TAB_R_13_Tab_R_D2_src(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_13_get_Tab_R_D2(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_13_Tab_R_D1_shift                                            (6)
#define DITHERING_TAB_R_13_Tab_R_D1_mask                                             (0x00000FC0)
#define DITHERING_TAB_R_13_Tab_R_D1(data)                                            (0x00000FC0&((data)<<6))
#define DITHERING_TAB_R_13_Tab_R_D1_src(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_13_get_Tab_R_D1(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_13_Tab_R_D0_shift                                            (0)
#define DITHERING_TAB_R_13_Tab_R_D0_mask                                             (0x0000003F)
#define DITHERING_TAB_R_13_Tab_R_D0(data)                                            (0x0000003F&((data)<<0))
#define DITHERING_TAB_R_13_Tab_R_D0_src(data)                                        ((0x0000003F&(data))>>0)
#define DITHERING_TAB_R_13_get_Tab_R_D0(data)                                        ((0x0000003F&(data))>>0)


#define DITHERING_TAB_R_14                                                           0x18009920
#define DITHERING_TAB_R_14_reg_addr                                                  "0xB8009920"
#define DITHERING_TAB_R_14_reg                                                       0xB8009920
#define set_DITHERING_TAB_R_14_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_R_14_reg)=data)
#define get_DITHERING_TAB_R_14_reg   (*((volatile unsigned int*) DITHERING_TAB_R_14_reg))
#define DITHERING_TAB_R_14_inst_adr                                                  "0x0048"
#define DITHERING_TAB_R_14_inst                                                      0x0048
#define DITHERING_TAB_R_14_Tab_R_E3_shift                                            (18)
#define DITHERING_TAB_R_14_Tab_R_E3_mask                                             (0x00FC0000)
#define DITHERING_TAB_R_14_Tab_R_E3(data)                                            (0x00FC0000&((data)<<18))
#define DITHERING_TAB_R_14_Tab_R_E3_src(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_14_get_Tab_R_E3(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_14_Tab_R_E2_shift                                            (12)
#define DITHERING_TAB_R_14_Tab_R_E2_mask                                             (0x0003F000)
#define DITHERING_TAB_R_14_Tab_R_E2(data)                                            (0x0003F000&((data)<<12))
#define DITHERING_TAB_R_14_Tab_R_E2_src(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_14_get_Tab_R_E2(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_14_Tab_R_E1_shift                                            (6)
#define DITHERING_TAB_R_14_Tab_R_E1_mask                                             (0x00000FC0)
#define DITHERING_TAB_R_14_Tab_R_E1(data)                                            (0x00000FC0&((data)<<6))
#define DITHERING_TAB_R_14_Tab_R_E1_src(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_14_get_Tab_R_E1(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_14_Tab_R_E0_shift                                            (0)
#define DITHERING_TAB_R_14_Tab_R_E0_mask                                             (0x0000003F)
#define DITHERING_TAB_R_14_Tab_R_E0(data)                                            (0x0000003F&((data)<<0))
#define DITHERING_TAB_R_14_Tab_R_E0_src(data)                                        ((0x0000003F&(data))>>0)
#define DITHERING_TAB_R_14_get_Tab_R_E0(data)                                        ((0x0000003F&(data))>>0)


#define DITHERING_TAB_R_15                                                           0x18009924
#define DITHERING_TAB_R_15_reg_addr                                                  "0xB8009924"
#define DITHERING_TAB_R_15_reg                                                       0xB8009924
#define set_DITHERING_TAB_R_15_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_R_15_reg)=data)
#define get_DITHERING_TAB_R_15_reg   (*((volatile unsigned int*) DITHERING_TAB_R_15_reg))
#define DITHERING_TAB_R_15_inst_adr                                                  "0x0049"
#define DITHERING_TAB_R_15_inst                                                      0x0049
#define DITHERING_TAB_R_15_Tab_R_F3_shift                                            (18)
#define DITHERING_TAB_R_15_Tab_R_F3_mask                                             (0x00FC0000)
#define DITHERING_TAB_R_15_Tab_R_F3(data)                                            (0x00FC0000&((data)<<18))
#define DITHERING_TAB_R_15_Tab_R_F3_src(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_15_get_Tab_R_F3(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_R_15_Tab_R_F2_shift                                            (12)
#define DITHERING_TAB_R_15_Tab_R_F2_mask                                             (0x0003F000)
#define DITHERING_TAB_R_15_Tab_R_F2(data)                                            (0x0003F000&((data)<<12))
#define DITHERING_TAB_R_15_Tab_R_F2_src(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_15_get_Tab_R_F2(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_R_15_Tab_R_F1_shift                                            (6)
#define DITHERING_TAB_R_15_Tab_R_F1_mask                                             (0x00000FC0)
#define DITHERING_TAB_R_15_Tab_R_F1(data)                                            (0x00000FC0&((data)<<6))
#define DITHERING_TAB_R_15_Tab_R_F1_src(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_15_get_Tab_R_F1(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_R_15_Tab_R_F0_shift                                            (0)
#define DITHERING_TAB_R_15_Tab_R_F0_mask                                             (0x0000003F)
#define DITHERING_TAB_R_15_Tab_R_F0(data)                                            (0x0000003F&((data)<<0))
#define DITHERING_TAB_R_15_Tab_R_F0_src(data)                                        ((0x0000003F&(data))>>0)
#define DITHERING_TAB_R_15_get_Tab_R_F0(data)                                        ((0x0000003F&(data))>>0)


#define DITHERING_TAB_G_0                                                            0x18009928
#define DITHERING_TAB_G_0_reg_addr                                                   "0xB8009928"
#define DITHERING_TAB_G_0_reg                                                        0xB8009928
#define set_DITHERING_TAB_G_0_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_G_0_reg)=data)
#define get_DITHERING_TAB_G_0_reg   (*((volatile unsigned int*) DITHERING_TAB_G_0_reg))
#define DITHERING_TAB_G_0_inst_adr                                                   "0x004A"
#define DITHERING_TAB_G_0_inst                                                       0x004A
#define DITHERING_TAB_G_0_Tab_G_03_shift                                             (18)
#define DITHERING_TAB_G_0_Tab_G_03_mask                                              (0x00FC0000)
#define DITHERING_TAB_G_0_Tab_G_03(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_G_0_Tab_G_03_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_0_get_Tab_G_03(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_0_Tab_G_02_shift                                             (12)
#define DITHERING_TAB_G_0_Tab_G_02_mask                                              (0x0003F000)
#define DITHERING_TAB_G_0_Tab_G_02(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_G_0_Tab_G_02_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_0_get_Tab_G_02(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_0_Tab_G_01_shift                                             (6)
#define DITHERING_TAB_G_0_Tab_G_01_mask                                              (0x00000FC0)
#define DITHERING_TAB_G_0_Tab_G_01(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_G_0_Tab_G_01_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_0_get_Tab_G_01(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_0_Tab_G_00_shift                                             (0)
#define DITHERING_TAB_G_0_Tab_G_00_mask                                              (0x0000003F)
#define DITHERING_TAB_G_0_Tab_G_00(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_G_0_Tab_G_00_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_G_0_get_Tab_G_00(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_G_1                                                            0x1800992c
#define DITHERING_TAB_G_1_reg_addr                                                   "0xB800992C"
#define DITHERING_TAB_G_1_reg                                                        0xB800992C
#define set_DITHERING_TAB_G_1_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_G_1_reg)=data)
#define get_DITHERING_TAB_G_1_reg   (*((volatile unsigned int*) DITHERING_TAB_G_1_reg))
#define DITHERING_TAB_G_1_inst_adr                                                   "0x004B"
#define DITHERING_TAB_G_1_inst                                                       0x004B
#define DITHERING_TAB_G_1_Tab_G_13_shift                                             (18)
#define DITHERING_TAB_G_1_Tab_G_13_mask                                              (0x00FC0000)
#define DITHERING_TAB_G_1_Tab_G_13(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_G_1_Tab_G_13_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_1_get_Tab_G_13(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_1_Tab_G_12_shift                                             (12)
#define DITHERING_TAB_G_1_Tab_G_12_mask                                              (0x0003F000)
#define DITHERING_TAB_G_1_Tab_G_12(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_G_1_Tab_G_12_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_1_get_Tab_G_12(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_1_Tab_G_11_shift                                             (6)
#define DITHERING_TAB_G_1_Tab_G_11_mask                                              (0x00000FC0)
#define DITHERING_TAB_G_1_Tab_G_11(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_G_1_Tab_G_11_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_1_get_Tab_G_11(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_1_Tab_G_10_shift                                             (0)
#define DITHERING_TAB_G_1_Tab_G_10_mask                                              (0x0000003F)
#define DITHERING_TAB_G_1_Tab_G_10(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_G_1_Tab_G_10_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_G_1_get_Tab_G_10(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_G_2                                                            0x18009930
#define DITHERING_TAB_G_2_reg_addr                                                   "0xB8009930"
#define DITHERING_TAB_G_2_reg                                                        0xB8009930
#define set_DITHERING_TAB_G_2_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_G_2_reg)=data)
#define get_DITHERING_TAB_G_2_reg   (*((volatile unsigned int*) DITHERING_TAB_G_2_reg))
#define DITHERING_TAB_G_2_inst_adr                                                   "0x004C"
#define DITHERING_TAB_G_2_inst                                                       0x004C
#define DITHERING_TAB_G_2_Tab_G_23_shift                                             (18)
#define DITHERING_TAB_G_2_Tab_G_23_mask                                              (0x00FC0000)
#define DITHERING_TAB_G_2_Tab_G_23(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_G_2_Tab_G_23_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_2_get_Tab_G_23(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_2_Tab_G_22_shift                                             (12)
#define DITHERING_TAB_G_2_Tab_G_22_mask                                              (0x0003F000)
#define DITHERING_TAB_G_2_Tab_G_22(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_G_2_Tab_G_22_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_2_get_Tab_G_22(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_2_Tab_G_21_shift                                             (6)
#define DITHERING_TAB_G_2_Tab_G_21_mask                                              (0x00000FC0)
#define DITHERING_TAB_G_2_Tab_G_21(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_G_2_Tab_G_21_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_2_get_Tab_G_21(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_2_Tab_G_20_shift                                             (0)
#define DITHERING_TAB_G_2_Tab_G_20_mask                                              (0x0000003F)
#define DITHERING_TAB_G_2_Tab_G_20(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_G_2_Tab_G_20_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_G_2_get_Tab_G_20(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_G_3                                                            0x18009934
#define DITHERING_TAB_G_3_reg_addr                                                   "0xB8009934"
#define DITHERING_TAB_G_3_reg                                                        0xB8009934
#define set_DITHERING_TAB_G_3_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_G_3_reg)=data)
#define get_DITHERING_TAB_G_3_reg   (*((volatile unsigned int*) DITHERING_TAB_G_3_reg))
#define DITHERING_TAB_G_3_inst_adr                                                   "0x004D"
#define DITHERING_TAB_G_3_inst                                                       0x004D
#define DITHERING_TAB_G_3_Tab_G_33_shift                                             (18)
#define DITHERING_TAB_G_3_Tab_G_33_mask                                              (0x00FC0000)
#define DITHERING_TAB_G_3_Tab_G_33(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_G_3_Tab_G_33_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_3_get_Tab_G_33(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_3_Tab_G_32_shift                                             (12)
#define DITHERING_TAB_G_3_Tab_G_32_mask                                              (0x0003F000)
#define DITHERING_TAB_G_3_Tab_G_32(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_G_3_Tab_G_32_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_3_get_Tab_G_32(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_3_Tab_G_31_shift                                             (6)
#define DITHERING_TAB_G_3_Tab_G_31_mask                                              (0x00000FC0)
#define DITHERING_TAB_G_3_Tab_G_31(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_G_3_Tab_G_31_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_3_get_Tab_G_31(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_3_Tab_G_30_shift                                             (0)
#define DITHERING_TAB_G_3_Tab_G_30_mask                                              (0x0000003F)
#define DITHERING_TAB_G_3_Tab_G_30(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_G_3_Tab_G_30_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_G_3_get_Tab_G_30(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_G_4                                                            0x18009938
#define DITHERING_TAB_G_4_reg_addr                                                   "0xB8009938"
#define DITHERING_TAB_G_4_reg                                                        0xB8009938
#define set_DITHERING_TAB_G_4_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_G_4_reg)=data)
#define get_DITHERING_TAB_G_4_reg   (*((volatile unsigned int*) DITHERING_TAB_G_4_reg))
#define DITHERING_TAB_G_4_inst_adr                                                   "0x004E"
#define DITHERING_TAB_G_4_inst                                                       0x004E
#define DITHERING_TAB_G_4_Tab_G_43_shift                                             (18)
#define DITHERING_TAB_G_4_Tab_G_43_mask                                              (0x00FC0000)
#define DITHERING_TAB_G_4_Tab_G_43(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_G_4_Tab_G_43_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_4_get_Tab_G_43(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_4_Tab_G_42_shift                                             (12)
#define DITHERING_TAB_G_4_Tab_G_42_mask                                              (0x0003F000)
#define DITHERING_TAB_G_4_Tab_G_42(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_G_4_Tab_G_42_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_4_get_Tab_G_42(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_4_Tab_G_41_shift                                             (6)
#define DITHERING_TAB_G_4_Tab_G_41_mask                                              (0x00000FC0)
#define DITHERING_TAB_G_4_Tab_G_41(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_G_4_Tab_G_41_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_4_get_Tab_G_41(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_4_Tab_G_40_shift                                             (0)
#define DITHERING_TAB_G_4_Tab_G_40_mask                                              (0x0000003F)
#define DITHERING_TAB_G_4_Tab_G_40(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_G_4_Tab_G_40_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_G_4_get_Tab_G_40(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_G_5                                                            0x1800993c
#define DITHERING_TAB_G_5_reg_addr                                                   "0xB800993C"
#define DITHERING_TAB_G_5_reg                                                        0xB800993C
#define set_DITHERING_TAB_G_5_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_G_5_reg)=data)
#define get_DITHERING_TAB_G_5_reg   (*((volatile unsigned int*) DITHERING_TAB_G_5_reg))
#define DITHERING_TAB_G_5_inst_adr                                                   "0x004F"
#define DITHERING_TAB_G_5_inst                                                       0x004F
#define DITHERING_TAB_G_5_Tab_G_53_shift                                             (18)
#define DITHERING_TAB_G_5_Tab_G_53_mask                                              (0x00FC0000)
#define DITHERING_TAB_G_5_Tab_G_53(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_G_5_Tab_G_53_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_5_get_Tab_G_53(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_5_Tab_G_52_shift                                             (12)
#define DITHERING_TAB_G_5_Tab_G_52_mask                                              (0x0003F000)
#define DITHERING_TAB_G_5_Tab_G_52(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_G_5_Tab_G_52_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_5_get_Tab_G_52(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_5_Tab_G_51_shift                                             (6)
#define DITHERING_TAB_G_5_Tab_G_51_mask                                              (0x00000FC0)
#define DITHERING_TAB_G_5_Tab_G_51(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_G_5_Tab_G_51_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_5_get_Tab_G_51(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_5_Tab_G_50_shift                                             (0)
#define DITHERING_TAB_G_5_Tab_G_50_mask                                              (0x0000003F)
#define DITHERING_TAB_G_5_Tab_G_50(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_G_5_Tab_G_50_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_G_5_get_Tab_G_50(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_G_6                                                            0x18009940
#define DITHERING_TAB_G_6_reg_addr                                                   "0xB8009940"
#define DITHERING_TAB_G_6_reg                                                        0xB8009940
#define set_DITHERING_TAB_G_6_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_G_6_reg)=data)
#define get_DITHERING_TAB_G_6_reg   (*((volatile unsigned int*) DITHERING_TAB_G_6_reg))
#define DITHERING_TAB_G_6_inst_adr                                                   "0x0050"
#define DITHERING_TAB_G_6_inst                                                       0x0050
#define DITHERING_TAB_G_6_Tab_G_63_shift                                             (18)
#define DITHERING_TAB_G_6_Tab_G_63_mask                                              (0x00FC0000)
#define DITHERING_TAB_G_6_Tab_G_63(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_G_6_Tab_G_63_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_6_get_Tab_G_63(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_6_Tab_G_62_shift                                             (12)
#define DITHERING_TAB_G_6_Tab_G_62_mask                                              (0x0003F000)
#define DITHERING_TAB_G_6_Tab_G_62(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_G_6_Tab_G_62_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_6_get_Tab_G_62(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_6_Tab_G_61_shift                                             (6)
#define DITHERING_TAB_G_6_Tab_G_61_mask                                              (0x00000FC0)
#define DITHERING_TAB_G_6_Tab_G_61(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_G_6_Tab_G_61_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_6_get_Tab_G_61(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_6_Tab_G_60_shift                                             (0)
#define DITHERING_TAB_G_6_Tab_G_60_mask                                              (0x0000003F)
#define DITHERING_TAB_G_6_Tab_G_60(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_G_6_Tab_G_60_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_G_6_get_Tab_G_60(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_G_7                                                            0x18009944
#define DITHERING_TAB_G_7_reg_addr                                                   "0xB8009944"
#define DITHERING_TAB_G_7_reg                                                        0xB8009944
#define set_DITHERING_TAB_G_7_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_G_7_reg)=data)
#define get_DITHERING_TAB_G_7_reg   (*((volatile unsigned int*) DITHERING_TAB_G_7_reg))
#define DITHERING_TAB_G_7_inst_adr                                                   "0x0051"
#define DITHERING_TAB_G_7_inst                                                       0x0051
#define DITHERING_TAB_G_7_Tab_G_73_shift                                             (18)
#define DITHERING_TAB_G_7_Tab_G_73_mask                                              (0x00FC0000)
#define DITHERING_TAB_G_7_Tab_G_73(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_G_7_Tab_G_73_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_7_get_Tab_G_73(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_7_Tab_G_72_shift                                             (12)
#define DITHERING_TAB_G_7_Tab_G_72_mask                                              (0x0003F000)
#define DITHERING_TAB_G_7_Tab_G_72(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_G_7_Tab_G_72_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_7_get_Tab_G_72(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_7_Tab_G_71_shift                                             (6)
#define DITHERING_TAB_G_7_Tab_G_71_mask                                              (0x00000FC0)
#define DITHERING_TAB_G_7_Tab_G_71(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_G_7_Tab_G_71_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_7_get_Tab_G_71(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_7_Tab_G_70_shift                                             (0)
#define DITHERING_TAB_G_7_Tab_G_70_mask                                              (0x0000003F)
#define DITHERING_TAB_G_7_Tab_G_70(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_G_7_Tab_G_70_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_G_7_get_Tab_G_70(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_G_8                                                            0x18009948
#define DITHERING_TAB_G_8_reg_addr                                                   "0xB8009948"
#define DITHERING_TAB_G_8_reg                                                        0xB8009948
#define set_DITHERING_TAB_G_8_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_G_8_reg)=data)
#define get_DITHERING_TAB_G_8_reg   (*((volatile unsigned int*) DITHERING_TAB_G_8_reg))
#define DITHERING_TAB_G_8_inst_adr                                                   "0x0052"
#define DITHERING_TAB_G_8_inst                                                       0x0052
#define DITHERING_TAB_G_8_Tab_G_83_shift                                             (18)
#define DITHERING_TAB_G_8_Tab_G_83_mask                                              (0x00FC0000)
#define DITHERING_TAB_G_8_Tab_G_83(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_G_8_Tab_G_83_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_8_get_Tab_G_83(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_8_Tab_G_82_shift                                             (12)
#define DITHERING_TAB_G_8_Tab_G_82_mask                                              (0x0003F000)
#define DITHERING_TAB_G_8_Tab_G_82(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_G_8_Tab_G_82_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_8_get_Tab_G_82(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_8_Tab_G_81_shift                                             (6)
#define DITHERING_TAB_G_8_Tab_G_81_mask                                              (0x00000FC0)
#define DITHERING_TAB_G_8_Tab_G_81(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_G_8_Tab_G_81_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_8_get_Tab_G_81(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_8_Tab_G_80_shift                                             (0)
#define DITHERING_TAB_G_8_Tab_G_80_mask                                              (0x0000003F)
#define DITHERING_TAB_G_8_Tab_G_80(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_G_8_Tab_G_80_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_G_8_get_Tab_G_80(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_G_9                                                            0x1800994c
#define DITHERING_TAB_G_9_reg_addr                                                   "0xB800994C"
#define DITHERING_TAB_G_9_reg                                                        0xB800994C
#define set_DITHERING_TAB_G_9_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_G_9_reg)=data)
#define get_DITHERING_TAB_G_9_reg   (*((volatile unsigned int*) DITHERING_TAB_G_9_reg))
#define DITHERING_TAB_G_9_inst_adr                                                   "0x0053"
#define DITHERING_TAB_G_9_inst                                                       0x0053
#define DITHERING_TAB_G_9_Tab_G_93_shift                                             (18)
#define DITHERING_TAB_G_9_Tab_G_93_mask                                              (0x00FC0000)
#define DITHERING_TAB_G_9_Tab_G_93(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_G_9_Tab_G_93_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_9_get_Tab_G_93(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_9_Tab_G_92_shift                                             (12)
#define DITHERING_TAB_G_9_Tab_G_92_mask                                              (0x0003F000)
#define DITHERING_TAB_G_9_Tab_G_92(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_G_9_Tab_G_92_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_9_get_Tab_G_92(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_9_Tab_G_91_shift                                             (6)
#define DITHERING_TAB_G_9_Tab_G_91_mask                                              (0x00000FC0)
#define DITHERING_TAB_G_9_Tab_G_91(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_G_9_Tab_G_91_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_9_get_Tab_G_91(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_9_Tab_G_90_shift                                             (0)
#define DITHERING_TAB_G_9_Tab_G_90_mask                                              (0x0000003F)
#define DITHERING_TAB_G_9_Tab_G_90(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_G_9_Tab_G_90_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_G_9_get_Tab_G_90(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_G_10                                                           0x18009950
#define DITHERING_TAB_G_10_reg_addr                                                  "0xB8009950"
#define DITHERING_TAB_G_10_reg                                                       0xB8009950
#define set_DITHERING_TAB_G_10_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_G_10_reg)=data)
#define get_DITHERING_TAB_G_10_reg   (*((volatile unsigned int*) DITHERING_TAB_G_10_reg))
#define DITHERING_TAB_G_10_inst_adr                                                  "0x0054"
#define DITHERING_TAB_G_10_inst                                                      0x0054
#define DITHERING_TAB_G_10_Tab_G_A3_shift                                            (18)
#define DITHERING_TAB_G_10_Tab_G_A3_mask                                             (0x00FC0000)
#define DITHERING_TAB_G_10_Tab_G_A3(data)                                            (0x00FC0000&((data)<<18))
#define DITHERING_TAB_G_10_Tab_G_A3_src(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_10_get_Tab_G_A3(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_10_Tab_G_A2_shift                                            (12)
#define DITHERING_TAB_G_10_Tab_G_A2_mask                                             (0x0003F000)
#define DITHERING_TAB_G_10_Tab_G_A2(data)                                            (0x0003F000&((data)<<12))
#define DITHERING_TAB_G_10_Tab_G_A2_src(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_10_get_Tab_G_A2(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_10_Tab_G_A1_shift                                            (6)
#define DITHERING_TAB_G_10_Tab_G_A1_mask                                             (0x00000FC0)
#define DITHERING_TAB_G_10_Tab_G_A1(data)                                            (0x00000FC0&((data)<<6))
#define DITHERING_TAB_G_10_Tab_G_A1_src(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_10_get_Tab_G_A1(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_10_Tab_G_A0_shift                                            (0)
#define DITHERING_TAB_G_10_Tab_G_A0_mask                                             (0x0000003F)
#define DITHERING_TAB_G_10_Tab_G_A0(data)                                            (0x0000003F&((data)<<0))
#define DITHERING_TAB_G_10_Tab_G_A0_src(data)                                        ((0x0000003F&(data))>>0)
#define DITHERING_TAB_G_10_get_Tab_G_A0(data)                                        ((0x0000003F&(data))>>0)


#define DITHERING_TAB_G_11                                                           0x18009954
#define DITHERING_TAB_G_11_reg_addr                                                  "0xB8009954"
#define DITHERING_TAB_G_11_reg                                                       0xB8009954
#define set_DITHERING_TAB_G_11_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_G_11_reg)=data)
#define get_DITHERING_TAB_G_11_reg   (*((volatile unsigned int*) DITHERING_TAB_G_11_reg))
#define DITHERING_TAB_G_11_inst_adr                                                  "0x0055"
#define DITHERING_TAB_G_11_inst                                                      0x0055
#define DITHERING_TAB_G_11_Tab_G_B3_shift                                            (18)
#define DITHERING_TAB_G_11_Tab_G_B3_mask                                             (0x00FC0000)
#define DITHERING_TAB_G_11_Tab_G_B3(data)                                            (0x00FC0000&((data)<<18))
#define DITHERING_TAB_G_11_Tab_G_B3_src(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_11_get_Tab_G_B3(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_11_Tab_G_B2_shift                                            (12)
#define DITHERING_TAB_G_11_Tab_G_B2_mask                                             (0x0003F000)
#define DITHERING_TAB_G_11_Tab_G_B2(data)                                            (0x0003F000&((data)<<12))
#define DITHERING_TAB_G_11_Tab_G_B2_src(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_11_get_Tab_G_B2(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_11_Tab_G_B1_shift                                            (6)
#define DITHERING_TAB_G_11_Tab_G_B1_mask                                             (0x00000FC0)
#define DITHERING_TAB_G_11_Tab_G_B1(data)                                            (0x00000FC0&((data)<<6))
#define DITHERING_TAB_G_11_Tab_G_B1_src(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_11_get_Tab_G_B1(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_11_Tab_G_B0_shift                                            (0)
#define DITHERING_TAB_G_11_Tab_G_B0_mask                                             (0x0000003F)
#define DITHERING_TAB_G_11_Tab_G_B0(data)                                            (0x0000003F&((data)<<0))
#define DITHERING_TAB_G_11_Tab_G_B0_src(data)                                        ((0x0000003F&(data))>>0)
#define DITHERING_TAB_G_11_get_Tab_G_B0(data)                                        ((0x0000003F&(data))>>0)


#define DITHERING_TAB_G_12                                                           0x18009958
#define DITHERING_TAB_G_12_reg_addr                                                  "0xB8009958"
#define DITHERING_TAB_G_12_reg                                                       0xB8009958
#define set_DITHERING_TAB_G_12_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_G_12_reg)=data)
#define get_DITHERING_TAB_G_12_reg   (*((volatile unsigned int*) DITHERING_TAB_G_12_reg))
#define DITHERING_TAB_G_12_inst_adr                                                  "0x0056"
#define DITHERING_TAB_G_12_inst                                                      0x0056
#define DITHERING_TAB_G_12_Tab_G_C3_shift                                            (18)
#define DITHERING_TAB_G_12_Tab_G_C3_mask                                             (0x00FC0000)
#define DITHERING_TAB_G_12_Tab_G_C3(data)                                            (0x00FC0000&((data)<<18))
#define DITHERING_TAB_G_12_Tab_G_C3_src(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_12_get_Tab_G_C3(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_12_Tab_G_C2_shift                                            (12)
#define DITHERING_TAB_G_12_Tab_G_C2_mask                                             (0x0003F000)
#define DITHERING_TAB_G_12_Tab_G_C2(data)                                            (0x0003F000&((data)<<12))
#define DITHERING_TAB_G_12_Tab_G_C2_src(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_12_get_Tab_G_C2(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_12_Tab_G_C1_shift                                            (6)
#define DITHERING_TAB_G_12_Tab_G_C1_mask                                             (0x00000FC0)
#define DITHERING_TAB_G_12_Tab_G_C1(data)                                            (0x00000FC0&((data)<<6))
#define DITHERING_TAB_G_12_Tab_G_C1_src(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_12_get_Tab_G_C1(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_12_Tab_G_C0_shift                                            (0)
#define DITHERING_TAB_G_12_Tab_G_C0_mask                                             (0x0000003F)
#define DITHERING_TAB_G_12_Tab_G_C0(data)                                            (0x0000003F&((data)<<0))
#define DITHERING_TAB_G_12_Tab_G_C0_src(data)                                        ((0x0000003F&(data))>>0)
#define DITHERING_TAB_G_12_get_Tab_G_C0(data)                                        ((0x0000003F&(data))>>0)


#define DITHERING_TAB_G_13                                                           0x1800995c
#define DITHERING_TAB_G_13_reg_addr                                                  "0xB800995C"
#define DITHERING_TAB_G_13_reg                                                       0xB800995C
#define set_DITHERING_TAB_G_13_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_G_13_reg)=data)
#define get_DITHERING_TAB_G_13_reg   (*((volatile unsigned int*) DITHERING_TAB_G_13_reg))
#define DITHERING_TAB_G_13_inst_adr                                                  "0x0057"
#define DITHERING_TAB_G_13_inst                                                      0x0057
#define DITHERING_TAB_G_13_Tab_G_D3_shift                                            (18)
#define DITHERING_TAB_G_13_Tab_G_D3_mask                                             (0x00FC0000)
#define DITHERING_TAB_G_13_Tab_G_D3(data)                                            (0x00FC0000&((data)<<18))
#define DITHERING_TAB_G_13_Tab_G_D3_src(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_13_get_Tab_G_D3(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_13_Tab_G_D2_shift                                            (12)
#define DITHERING_TAB_G_13_Tab_G_D2_mask                                             (0x0003F000)
#define DITHERING_TAB_G_13_Tab_G_D2(data)                                            (0x0003F000&((data)<<12))
#define DITHERING_TAB_G_13_Tab_G_D2_src(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_13_get_Tab_G_D2(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_13_Tab_G_D1_shift                                            (6)
#define DITHERING_TAB_G_13_Tab_G_D1_mask                                             (0x00000FC0)
#define DITHERING_TAB_G_13_Tab_G_D1(data)                                            (0x00000FC0&((data)<<6))
#define DITHERING_TAB_G_13_Tab_G_D1_src(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_13_get_Tab_G_D1(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_13_Tab_G_D0_shift                                            (0)
#define DITHERING_TAB_G_13_Tab_G_D0_mask                                             (0x0000003F)
#define DITHERING_TAB_G_13_Tab_G_D0(data)                                            (0x0000003F&((data)<<0))
#define DITHERING_TAB_G_13_Tab_G_D0_src(data)                                        ((0x0000003F&(data))>>0)
#define DITHERING_TAB_G_13_get_Tab_G_D0(data)                                        ((0x0000003F&(data))>>0)


#define DITHERING_TAB_G_14                                                           0x18009960
#define DITHERING_TAB_G_14_reg_addr                                                  "0xB8009960"
#define DITHERING_TAB_G_14_reg                                                       0xB8009960
#define set_DITHERING_TAB_G_14_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_G_14_reg)=data)
#define get_DITHERING_TAB_G_14_reg   (*((volatile unsigned int*) DITHERING_TAB_G_14_reg))
#define DITHERING_TAB_G_14_inst_adr                                                  "0x0058"
#define DITHERING_TAB_G_14_inst                                                      0x0058
#define DITHERING_TAB_G_14_Tab_G_E3_shift                                            (18)
#define DITHERING_TAB_G_14_Tab_G_E3_mask                                             (0x00FC0000)
#define DITHERING_TAB_G_14_Tab_G_E3(data)                                            (0x00FC0000&((data)<<18))
#define DITHERING_TAB_G_14_Tab_G_E3_src(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_14_get_Tab_G_E3(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_14_Tab_G_E2_shift                                            (12)
#define DITHERING_TAB_G_14_Tab_G_E2_mask                                             (0x0003F000)
#define DITHERING_TAB_G_14_Tab_G_E2(data)                                            (0x0003F000&((data)<<12))
#define DITHERING_TAB_G_14_Tab_G_E2_src(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_14_get_Tab_G_E2(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_14_Tab_G_E1_shift                                            (6)
#define DITHERING_TAB_G_14_Tab_G_E1_mask                                             (0x00000FC0)
#define DITHERING_TAB_G_14_Tab_G_E1(data)                                            (0x00000FC0&((data)<<6))
#define DITHERING_TAB_G_14_Tab_G_E1_src(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_14_get_Tab_G_E1(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_14_Tab_G_E0_shift                                            (0)
#define DITHERING_TAB_G_14_Tab_G_E0_mask                                             (0x0000003F)
#define DITHERING_TAB_G_14_Tab_G_E0(data)                                            (0x0000003F&((data)<<0))
#define DITHERING_TAB_G_14_Tab_G_E0_src(data)                                        ((0x0000003F&(data))>>0)
#define DITHERING_TAB_G_14_get_Tab_G_E0(data)                                        ((0x0000003F&(data))>>0)


#define DITHERING_TAB_G_15                                                           0x18009964
#define DITHERING_TAB_G_15_reg_addr                                                  "0xB8009964"
#define DITHERING_TAB_G_15_reg                                                       0xB8009964
#define set_DITHERING_TAB_G_15_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_G_15_reg)=data)
#define get_DITHERING_TAB_G_15_reg   (*((volatile unsigned int*) DITHERING_TAB_G_15_reg))
#define DITHERING_TAB_G_15_inst_adr                                                  "0x0059"
#define DITHERING_TAB_G_15_inst                                                      0x0059
#define DITHERING_TAB_G_15_Tab_G_F3_shift                                            (18)
#define DITHERING_TAB_G_15_Tab_G_F3_mask                                             (0x00FC0000)
#define DITHERING_TAB_G_15_Tab_G_F3(data)                                            (0x00FC0000&((data)<<18))
#define DITHERING_TAB_G_15_Tab_G_F3_src(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_15_get_Tab_G_F3(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_G_15_Tab_G_F2_shift                                            (12)
#define DITHERING_TAB_G_15_Tab_G_F2_mask                                             (0x0003F000)
#define DITHERING_TAB_G_15_Tab_G_F2(data)                                            (0x0003F000&((data)<<12))
#define DITHERING_TAB_G_15_Tab_G_F2_src(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_15_get_Tab_G_F2(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_G_15_Tab_G_F1_shift                                            (6)
#define DITHERING_TAB_G_15_Tab_G_F1_mask                                             (0x00000FC0)
#define DITHERING_TAB_G_15_Tab_G_F1(data)                                            (0x00000FC0&((data)<<6))
#define DITHERING_TAB_G_15_Tab_G_F1_src(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_15_get_Tab_G_F1(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_G_15_Tab_G_F0_shift                                            (0)
#define DITHERING_TAB_G_15_Tab_G_F0_mask                                             (0x0000003F)
#define DITHERING_TAB_G_15_Tab_G_F0(data)                                            (0x0000003F&((data)<<0))
#define DITHERING_TAB_G_15_Tab_G_F0_src(data)                                        ((0x0000003F&(data))>>0)
#define DITHERING_TAB_G_15_get_Tab_G_F0(data)                                        ((0x0000003F&(data))>>0)


#define DITHERING_TAB_B_0                                                            0x18009968
#define DITHERING_TAB_B_0_reg_addr                                                   "0xB8009968"
#define DITHERING_TAB_B_0_reg                                                        0xB8009968
#define set_DITHERING_TAB_B_0_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_B_0_reg)=data)
#define get_DITHERING_TAB_B_0_reg   (*((volatile unsigned int*) DITHERING_TAB_B_0_reg))
#define DITHERING_TAB_B_0_inst_adr                                                   "0x005A"
#define DITHERING_TAB_B_0_inst                                                       0x005A
#define DITHERING_TAB_B_0_Tab_B_03_shift                                             (18)
#define DITHERING_TAB_B_0_Tab_B_03_mask                                              (0x00FC0000)
#define DITHERING_TAB_B_0_Tab_B_03(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_B_0_Tab_B_03_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_0_get_Tab_B_03(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_0_Tab_B_02_shift                                             (12)
#define DITHERING_TAB_B_0_Tab_B_02_mask                                              (0x0003F000)
#define DITHERING_TAB_B_0_Tab_B_02(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_B_0_Tab_B_02_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_0_get_Tab_B_02(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_0_Tab_B_01_shift                                             (6)
#define DITHERING_TAB_B_0_Tab_B_01_mask                                              (0x00000FC0)
#define DITHERING_TAB_B_0_Tab_B_01(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_B_0_Tab_B_01_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_0_get_Tab_B_01(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_0_Tab_B_00_shift                                             (0)
#define DITHERING_TAB_B_0_Tab_B_00_mask                                              (0x0000003F)
#define DITHERING_TAB_B_0_Tab_B_00(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_B_0_Tab_B_00_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_B_0_get_Tab_B_00(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_B_1                                                            0x1800996c
#define DITHERING_TAB_B_1_reg_addr                                                   "0xB800996C"
#define DITHERING_TAB_B_1_reg                                                        0xB800996C
#define set_DITHERING_TAB_B_1_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_B_1_reg)=data)
#define get_DITHERING_TAB_B_1_reg   (*((volatile unsigned int*) DITHERING_TAB_B_1_reg))
#define DITHERING_TAB_B_1_inst_adr                                                   "0x005B"
#define DITHERING_TAB_B_1_inst                                                       0x005B
#define DITHERING_TAB_B_1_Tab_B_13_shift                                             (18)
#define DITHERING_TAB_B_1_Tab_B_13_mask                                              (0x00FC0000)
#define DITHERING_TAB_B_1_Tab_B_13(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_B_1_Tab_B_13_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_1_get_Tab_B_13(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_1_Tab_B_12_shift                                             (12)
#define DITHERING_TAB_B_1_Tab_B_12_mask                                              (0x0003F000)
#define DITHERING_TAB_B_1_Tab_B_12(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_B_1_Tab_B_12_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_1_get_Tab_B_12(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_1_Tab_B_11_shift                                             (6)
#define DITHERING_TAB_B_1_Tab_B_11_mask                                              (0x00000FC0)
#define DITHERING_TAB_B_1_Tab_B_11(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_B_1_Tab_B_11_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_1_get_Tab_B_11(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_1_Tab_B_10_shift                                             (0)
#define DITHERING_TAB_B_1_Tab_B_10_mask                                              (0x0000003F)
#define DITHERING_TAB_B_1_Tab_B_10(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_B_1_Tab_B_10_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_B_1_get_Tab_B_10(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_B_2                                                            0x18009970
#define DITHERING_TAB_B_2_reg_addr                                                   "0xB8009970"
#define DITHERING_TAB_B_2_reg                                                        0xB8009970
#define set_DITHERING_TAB_B_2_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_B_2_reg)=data)
#define get_DITHERING_TAB_B_2_reg   (*((volatile unsigned int*) DITHERING_TAB_B_2_reg))
#define DITHERING_TAB_B_2_inst_adr                                                   "0x005C"
#define DITHERING_TAB_B_2_inst                                                       0x005C
#define DITHERING_TAB_B_2_Tab_B_23_shift                                             (18)
#define DITHERING_TAB_B_2_Tab_B_23_mask                                              (0x00FC0000)
#define DITHERING_TAB_B_2_Tab_B_23(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_B_2_Tab_B_23_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_2_get_Tab_B_23(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_2_Tab_B_22_shift                                             (12)
#define DITHERING_TAB_B_2_Tab_B_22_mask                                              (0x0003F000)
#define DITHERING_TAB_B_2_Tab_B_22(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_B_2_Tab_B_22_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_2_get_Tab_B_22(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_2_Tab_B_21_shift                                             (6)
#define DITHERING_TAB_B_2_Tab_B_21_mask                                              (0x00000FC0)
#define DITHERING_TAB_B_2_Tab_B_21(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_B_2_Tab_B_21_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_2_get_Tab_B_21(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_2_Tab_B_20_shift                                             (0)
#define DITHERING_TAB_B_2_Tab_B_20_mask                                              (0x0000003F)
#define DITHERING_TAB_B_2_Tab_B_20(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_B_2_Tab_B_20_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_B_2_get_Tab_B_20(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_B_3                                                            0x18009974
#define DITHERING_TAB_B_3_reg_addr                                                   "0xB8009974"
#define DITHERING_TAB_B_3_reg                                                        0xB8009974
#define set_DITHERING_TAB_B_3_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_B_3_reg)=data)
#define get_DITHERING_TAB_B_3_reg   (*((volatile unsigned int*) DITHERING_TAB_B_3_reg))
#define DITHERING_TAB_B_3_inst_adr                                                   "0x005D"
#define DITHERING_TAB_B_3_inst                                                       0x005D
#define DITHERING_TAB_B_3_Tab_B_33_shift                                             (18)
#define DITHERING_TAB_B_3_Tab_B_33_mask                                              (0x00FC0000)
#define DITHERING_TAB_B_3_Tab_B_33(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_B_3_Tab_B_33_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_3_get_Tab_B_33(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_3_Tab_B_32_shift                                             (12)
#define DITHERING_TAB_B_3_Tab_B_32_mask                                              (0x0003F000)
#define DITHERING_TAB_B_3_Tab_B_32(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_B_3_Tab_B_32_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_3_get_Tab_B_32(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_3_Tab_B_31_shift                                             (6)
#define DITHERING_TAB_B_3_Tab_B_31_mask                                              (0x00000FC0)
#define DITHERING_TAB_B_3_Tab_B_31(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_B_3_Tab_B_31_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_3_get_Tab_B_31(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_3_Tab_B_30_shift                                             (0)
#define DITHERING_TAB_B_3_Tab_B_30_mask                                              (0x0000003F)
#define DITHERING_TAB_B_3_Tab_B_30(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_B_3_Tab_B_30_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_B_3_get_Tab_B_30(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_B_4                                                            0x18009978
#define DITHERING_TAB_B_4_reg_addr                                                   "0xB8009978"
#define DITHERING_TAB_B_4_reg                                                        0xB8009978
#define set_DITHERING_TAB_B_4_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_B_4_reg)=data)
#define get_DITHERING_TAB_B_4_reg   (*((volatile unsigned int*) DITHERING_TAB_B_4_reg))
#define DITHERING_TAB_B_4_inst_adr                                                   "0x005E"
#define DITHERING_TAB_B_4_inst                                                       0x005E
#define DITHERING_TAB_B_4_Tab_B_43_shift                                             (18)
#define DITHERING_TAB_B_4_Tab_B_43_mask                                              (0x00FC0000)
#define DITHERING_TAB_B_4_Tab_B_43(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_B_4_Tab_B_43_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_4_get_Tab_B_43(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_4_Tab_B_42_shift                                             (12)
#define DITHERING_TAB_B_4_Tab_B_42_mask                                              (0x0003F000)
#define DITHERING_TAB_B_4_Tab_B_42(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_B_4_Tab_B_42_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_4_get_Tab_B_42(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_4_Tab_B_41_shift                                             (6)
#define DITHERING_TAB_B_4_Tab_B_41_mask                                              (0x00000FC0)
#define DITHERING_TAB_B_4_Tab_B_41(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_B_4_Tab_B_41_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_4_get_Tab_B_41(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_4_Tab_B_40_shift                                             (0)
#define DITHERING_TAB_B_4_Tab_B_40_mask                                              (0x0000003F)
#define DITHERING_TAB_B_4_Tab_B_40(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_B_4_Tab_B_40_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_B_4_get_Tab_B_40(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_B_5                                                            0x1800997c
#define DITHERING_TAB_B_5_reg_addr                                                   "0xB800997C"
#define DITHERING_TAB_B_5_reg                                                        0xB800997C
#define set_DITHERING_TAB_B_5_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_B_5_reg)=data)
#define get_DITHERING_TAB_B_5_reg   (*((volatile unsigned int*) DITHERING_TAB_B_5_reg))
#define DITHERING_TAB_B_5_inst_adr                                                   "0x005F"
#define DITHERING_TAB_B_5_inst                                                       0x005F
#define DITHERING_TAB_B_5_Tab_B_53_shift                                             (18)
#define DITHERING_TAB_B_5_Tab_B_53_mask                                              (0x00FC0000)
#define DITHERING_TAB_B_5_Tab_B_53(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_B_5_Tab_B_53_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_5_get_Tab_B_53(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_5_Tab_B_52_shift                                             (12)
#define DITHERING_TAB_B_5_Tab_B_52_mask                                              (0x0003F000)
#define DITHERING_TAB_B_5_Tab_B_52(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_B_5_Tab_B_52_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_5_get_Tab_B_52(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_5_Tab_B_51_shift                                             (6)
#define DITHERING_TAB_B_5_Tab_B_51_mask                                              (0x00000FC0)
#define DITHERING_TAB_B_5_Tab_B_51(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_B_5_Tab_B_51_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_5_get_Tab_B_51(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_5_Tab_B_50_shift                                             (0)
#define DITHERING_TAB_B_5_Tab_B_50_mask                                              (0x0000003F)
#define DITHERING_TAB_B_5_Tab_B_50(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_B_5_Tab_B_50_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_B_5_get_Tab_B_50(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_B_6                                                            0x18009980
#define DITHERING_TAB_B_6_reg_addr                                                   "0xB8009980"
#define DITHERING_TAB_B_6_reg                                                        0xB8009980
#define set_DITHERING_TAB_B_6_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_B_6_reg)=data)
#define get_DITHERING_TAB_B_6_reg   (*((volatile unsigned int*) DITHERING_TAB_B_6_reg))
#define DITHERING_TAB_B_6_inst_adr                                                   "0x0060"
#define DITHERING_TAB_B_6_inst                                                       0x0060
#define DITHERING_TAB_B_6_Tab_B_63_shift                                             (18)
#define DITHERING_TAB_B_6_Tab_B_63_mask                                              (0x00FC0000)
#define DITHERING_TAB_B_6_Tab_B_63(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_B_6_Tab_B_63_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_6_get_Tab_B_63(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_6_Tab_B_62_shift                                             (12)
#define DITHERING_TAB_B_6_Tab_B_62_mask                                              (0x0003F000)
#define DITHERING_TAB_B_6_Tab_B_62(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_B_6_Tab_B_62_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_6_get_Tab_B_62(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_6_Tab_B_61_shift                                             (6)
#define DITHERING_TAB_B_6_Tab_B_61_mask                                              (0x00000FC0)
#define DITHERING_TAB_B_6_Tab_B_61(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_B_6_Tab_B_61_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_6_get_Tab_B_61(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_6_Tab_B_60_shift                                             (0)
#define DITHERING_TAB_B_6_Tab_B_60_mask                                              (0x0000003F)
#define DITHERING_TAB_B_6_Tab_B_60(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_B_6_Tab_B_60_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_B_6_get_Tab_B_60(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_B_7                                                            0x18009984
#define DITHERING_TAB_B_7_reg_addr                                                   "0xB8009984"
#define DITHERING_TAB_B_7_reg                                                        0xB8009984
#define set_DITHERING_TAB_B_7_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_B_7_reg)=data)
#define get_DITHERING_TAB_B_7_reg   (*((volatile unsigned int*) DITHERING_TAB_B_7_reg))
#define DITHERING_TAB_B_7_inst_adr                                                   "0x0061"
#define DITHERING_TAB_B_7_inst                                                       0x0061
#define DITHERING_TAB_B_7_Tab_B_73_shift                                             (18)
#define DITHERING_TAB_B_7_Tab_B_73_mask                                              (0x00FC0000)
#define DITHERING_TAB_B_7_Tab_B_73(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_B_7_Tab_B_73_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_7_get_Tab_B_73(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_7_Tab_B_72_shift                                             (12)
#define DITHERING_TAB_B_7_Tab_B_72_mask                                              (0x0003F000)
#define DITHERING_TAB_B_7_Tab_B_72(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_B_7_Tab_B_72_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_7_get_Tab_B_72(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_7_Tab_B_71_shift                                             (6)
#define DITHERING_TAB_B_7_Tab_B_71_mask                                              (0x00000FC0)
#define DITHERING_TAB_B_7_Tab_B_71(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_B_7_Tab_B_71_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_7_get_Tab_B_71(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_7_Tab_B_70_shift                                             (0)
#define DITHERING_TAB_B_7_Tab_B_70_mask                                              (0x0000003F)
#define DITHERING_TAB_B_7_Tab_B_70(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_B_7_Tab_B_70_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_B_7_get_Tab_B_70(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_B_8                                                            0x18009988
#define DITHERING_TAB_B_8_reg_addr                                                   "0xB8009988"
#define DITHERING_TAB_B_8_reg                                                        0xB8009988
#define set_DITHERING_TAB_B_8_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_B_8_reg)=data)
#define get_DITHERING_TAB_B_8_reg   (*((volatile unsigned int*) DITHERING_TAB_B_8_reg))
#define DITHERING_TAB_B_8_inst_adr                                                   "0x0062"
#define DITHERING_TAB_B_8_inst                                                       0x0062
#define DITHERING_TAB_B_8_Tab_B_83_shift                                             (18)
#define DITHERING_TAB_B_8_Tab_B_83_mask                                              (0x00FC0000)
#define DITHERING_TAB_B_8_Tab_B_83(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_B_8_Tab_B_83_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_8_get_Tab_B_83(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_8_Tab_B_82_shift                                             (12)
#define DITHERING_TAB_B_8_Tab_B_82_mask                                              (0x0003F000)
#define DITHERING_TAB_B_8_Tab_B_82(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_B_8_Tab_B_82_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_8_get_Tab_B_82(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_8_Tab_B_81_shift                                             (6)
#define DITHERING_TAB_B_8_Tab_B_81_mask                                              (0x00000FC0)
#define DITHERING_TAB_B_8_Tab_B_81(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_B_8_Tab_B_81_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_8_get_Tab_B_81(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_8_Tab_B_80_shift                                             (0)
#define DITHERING_TAB_B_8_Tab_B_80_mask                                              (0x0000003F)
#define DITHERING_TAB_B_8_Tab_B_80(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_B_8_Tab_B_80_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_B_8_get_Tab_B_80(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_B_9                                                            0x1800998c
#define DITHERING_TAB_B_9_reg_addr                                                   "0xB800998C"
#define DITHERING_TAB_B_9_reg                                                        0xB800998C
#define set_DITHERING_TAB_B_9_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_B_9_reg)=data)
#define get_DITHERING_TAB_B_9_reg   (*((volatile unsigned int*) DITHERING_TAB_B_9_reg))
#define DITHERING_TAB_B_9_inst_adr                                                   "0x0063"
#define DITHERING_TAB_B_9_inst                                                       0x0063
#define DITHERING_TAB_B_9_Tab_B_93_shift                                             (18)
#define DITHERING_TAB_B_9_Tab_B_93_mask                                              (0x00FC0000)
#define DITHERING_TAB_B_9_Tab_B_93(data)                                             (0x00FC0000&((data)<<18))
#define DITHERING_TAB_B_9_Tab_B_93_src(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_9_get_Tab_B_93(data)                                         ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_9_Tab_B_92_shift                                             (12)
#define DITHERING_TAB_B_9_Tab_B_92_mask                                              (0x0003F000)
#define DITHERING_TAB_B_9_Tab_B_92(data)                                             (0x0003F000&((data)<<12))
#define DITHERING_TAB_B_9_Tab_B_92_src(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_9_get_Tab_B_92(data)                                         ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_9_Tab_B_91_shift                                             (6)
#define DITHERING_TAB_B_9_Tab_B_91_mask                                              (0x00000FC0)
#define DITHERING_TAB_B_9_Tab_B_91(data)                                             (0x00000FC0&((data)<<6))
#define DITHERING_TAB_B_9_Tab_B_91_src(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_9_get_Tab_B_91(data)                                         ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_9_Tab_B_90_shift                                             (0)
#define DITHERING_TAB_B_9_Tab_B_90_mask                                              (0x0000003F)
#define DITHERING_TAB_B_9_Tab_B_90(data)                                             (0x0000003F&((data)<<0))
#define DITHERING_TAB_B_9_Tab_B_90_src(data)                                         ((0x0000003F&(data))>>0)
#define DITHERING_TAB_B_9_get_Tab_B_90(data)                                         ((0x0000003F&(data))>>0)


#define DITHERING_TAB_B_10                                                           0x18009990
#define DITHERING_TAB_B_10_reg_addr                                                  "0xB8009990"
#define DITHERING_TAB_B_10_reg                                                       0xB8009990
#define set_DITHERING_TAB_B_10_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_B_10_reg)=data)
#define get_DITHERING_TAB_B_10_reg   (*((volatile unsigned int*) DITHERING_TAB_B_10_reg))
#define DITHERING_TAB_B_10_inst_adr                                                  "0x0064"
#define DITHERING_TAB_B_10_inst                                                      0x0064
#define DITHERING_TAB_B_10_Tab_B_A3_shift                                            (18)
#define DITHERING_TAB_B_10_Tab_B_A3_mask                                             (0x00FC0000)
#define DITHERING_TAB_B_10_Tab_B_A3(data)                                            (0x00FC0000&((data)<<18))
#define DITHERING_TAB_B_10_Tab_B_A3_src(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_10_get_Tab_B_A3(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_10_Tab_B_A2_shift                                            (12)
#define DITHERING_TAB_B_10_Tab_B_A2_mask                                             (0x0003F000)
#define DITHERING_TAB_B_10_Tab_B_A2(data)                                            (0x0003F000&((data)<<12))
#define DITHERING_TAB_B_10_Tab_B_A2_src(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_10_get_Tab_B_A2(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_10_Tab_B_A1_shift                                            (6)
#define DITHERING_TAB_B_10_Tab_B_A1_mask                                             (0x00000FC0)
#define DITHERING_TAB_B_10_Tab_B_A1(data)                                            (0x00000FC0&((data)<<6))
#define DITHERING_TAB_B_10_Tab_B_A1_src(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_10_get_Tab_B_A1(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_10_Tab_B_A0_shift                                            (0)
#define DITHERING_TAB_B_10_Tab_B_A0_mask                                             (0x0000003F)
#define DITHERING_TAB_B_10_Tab_B_A0(data)                                            (0x0000003F&((data)<<0))
#define DITHERING_TAB_B_10_Tab_B_A0_src(data)                                        ((0x0000003F&(data))>>0)
#define DITHERING_TAB_B_10_get_Tab_B_A0(data)                                        ((0x0000003F&(data))>>0)


#define DITHERING_TAB_B_11                                                           0x18009994
#define DITHERING_TAB_B_11_reg_addr                                                  "0xB8009994"
#define DITHERING_TAB_B_11_reg                                                       0xB8009994
#define set_DITHERING_TAB_B_11_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_B_11_reg)=data)
#define get_DITHERING_TAB_B_11_reg   (*((volatile unsigned int*) DITHERING_TAB_B_11_reg))
#define DITHERING_TAB_B_11_inst_adr                                                  "0x0065"
#define DITHERING_TAB_B_11_inst                                                      0x0065
#define DITHERING_TAB_B_11_Tab_B_B3_shift                                            (18)
#define DITHERING_TAB_B_11_Tab_B_B3_mask                                             (0x00FC0000)
#define DITHERING_TAB_B_11_Tab_B_B3(data)                                            (0x00FC0000&((data)<<18))
#define DITHERING_TAB_B_11_Tab_B_B3_src(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_11_get_Tab_B_B3(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_11_Tab_B_B2_shift                                            (12)
#define DITHERING_TAB_B_11_Tab_B_B2_mask                                             (0x0003F000)
#define DITHERING_TAB_B_11_Tab_B_B2(data)                                            (0x0003F000&((data)<<12))
#define DITHERING_TAB_B_11_Tab_B_B2_src(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_11_get_Tab_B_B2(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_11_Tab_B_B1_shift                                            (6)
#define DITHERING_TAB_B_11_Tab_B_B1_mask                                             (0x00000FC0)
#define DITHERING_TAB_B_11_Tab_B_B1(data)                                            (0x00000FC0&((data)<<6))
#define DITHERING_TAB_B_11_Tab_B_B1_src(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_11_get_Tab_B_B1(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_11_Tab_B_B0_shift                                            (0)
#define DITHERING_TAB_B_11_Tab_B_B0_mask                                             (0x0000003F)
#define DITHERING_TAB_B_11_Tab_B_B0(data)                                            (0x0000003F&((data)<<0))
#define DITHERING_TAB_B_11_Tab_B_B0_src(data)                                        ((0x0000003F&(data))>>0)
#define DITHERING_TAB_B_11_get_Tab_B_B0(data)                                        ((0x0000003F&(data))>>0)


#define DITHERING_TAB_B_12                                                           0x18009998
#define DITHERING_TAB_B_12_reg_addr                                                  "0xB8009998"
#define DITHERING_TAB_B_12_reg                                                       0xB8009998
#define set_DITHERING_TAB_B_12_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_B_12_reg)=data)
#define get_DITHERING_TAB_B_12_reg   (*((volatile unsigned int*) DITHERING_TAB_B_12_reg))
#define DITHERING_TAB_B_12_inst_adr                                                  "0x0066"
#define DITHERING_TAB_B_12_inst                                                      0x0066
#define DITHERING_TAB_B_12_Tab_B_C3_shift                                            (18)
#define DITHERING_TAB_B_12_Tab_B_C3_mask                                             (0x00FC0000)
#define DITHERING_TAB_B_12_Tab_B_C3(data)                                            (0x00FC0000&((data)<<18))
#define DITHERING_TAB_B_12_Tab_B_C3_src(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_12_get_Tab_B_C3(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_12_Tab_B_C2_shift                                            (12)
#define DITHERING_TAB_B_12_Tab_B_C2_mask                                             (0x0003F000)
#define DITHERING_TAB_B_12_Tab_B_C2(data)                                            (0x0003F000&((data)<<12))
#define DITHERING_TAB_B_12_Tab_B_C2_src(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_12_get_Tab_B_C2(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_12_Tab_B_C1_shift                                            (6)
#define DITHERING_TAB_B_12_Tab_B_C1_mask                                             (0x00000FC0)
#define DITHERING_TAB_B_12_Tab_B_C1(data)                                            (0x00000FC0&((data)<<6))
#define DITHERING_TAB_B_12_Tab_B_C1_src(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_12_get_Tab_B_C1(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_12_Tab_B_C0_shift                                            (0)
#define DITHERING_TAB_B_12_Tab_B_C0_mask                                             (0x0000003F)
#define DITHERING_TAB_B_12_Tab_B_C0(data)                                            (0x0000003F&((data)<<0))
#define DITHERING_TAB_B_12_Tab_B_C0_src(data)                                        ((0x0000003F&(data))>>0)
#define DITHERING_TAB_B_12_get_Tab_B_C0(data)                                        ((0x0000003F&(data))>>0)


#define DITHERING_TAB_B_13                                                           0x1800999c
#define DITHERING_TAB_B_13_reg_addr                                                  "0xB800999C"
#define DITHERING_TAB_B_13_reg                                                       0xB800999C
#define set_DITHERING_TAB_B_13_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_B_13_reg)=data)
#define get_DITHERING_TAB_B_13_reg   (*((volatile unsigned int*) DITHERING_TAB_B_13_reg))
#define DITHERING_TAB_B_13_inst_adr                                                  "0x0067"
#define DITHERING_TAB_B_13_inst                                                      0x0067
#define DITHERING_TAB_B_13_Tab_B_D3_shift                                            (18)
#define DITHERING_TAB_B_13_Tab_B_D3_mask                                             (0x00FC0000)
#define DITHERING_TAB_B_13_Tab_B_D3(data)                                            (0x00FC0000&((data)<<18))
#define DITHERING_TAB_B_13_Tab_B_D3_src(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_13_get_Tab_B_D3(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_13_Tab_B_D2_shift                                            (12)
#define DITHERING_TAB_B_13_Tab_B_D2_mask                                             (0x0003F000)
#define DITHERING_TAB_B_13_Tab_B_D2(data)                                            (0x0003F000&((data)<<12))
#define DITHERING_TAB_B_13_Tab_B_D2_src(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_13_get_Tab_B_D2(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_13_Tab_B_D1_shift                                            (6)
#define DITHERING_TAB_B_13_Tab_B_D1_mask                                             (0x00000FC0)
#define DITHERING_TAB_B_13_Tab_B_D1(data)                                            (0x00000FC0&((data)<<6))
#define DITHERING_TAB_B_13_Tab_B_D1_src(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_13_get_Tab_B_D1(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_13_Tab_B_D0_shift                                            (0)
#define DITHERING_TAB_B_13_Tab_B_D0_mask                                             (0x0000003F)
#define DITHERING_TAB_B_13_Tab_B_D0(data)                                            (0x0000003F&((data)<<0))
#define DITHERING_TAB_B_13_Tab_B_D0_src(data)                                        ((0x0000003F&(data))>>0)
#define DITHERING_TAB_B_13_get_Tab_B_D0(data)                                        ((0x0000003F&(data))>>0)


#define DITHERING_TAB_B_14                                                           0x180099a0
#define DITHERING_TAB_B_14_reg_addr                                                  "0xB80099A0"
#define DITHERING_TAB_B_14_reg                                                       0xB80099A0
#define set_DITHERING_TAB_B_14_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_B_14_reg)=data)
#define get_DITHERING_TAB_B_14_reg   (*((volatile unsigned int*) DITHERING_TAB_B_14_reg))
#define DITHERING_TAB_B_14_inst_adr                                                  "0x0068"
#define DITHERING_TAB_B_14_inst                                                      0x0068
#define DITHERING_TAB_B_14_Tab_B_E3_shift                                            (18)
#define DITHERING_TAB_B_14_Tab_B_E3_mask                                             (0x00FC0000)
#define DITHERING_TAB_B_14_Tab_B_E3(data)                                            (0x00FC0000&((data)<<18))
#define DITHERING_TAB_B_14_Tab_B_E3_src(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_14_get_Tab_B_E3(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_14_Tab_B_E2_shift                                            (12)
#define DITHERING_TAB_B_14_Tab_B_E2_mask                                             (0x0003F000)
#define DITHERING_TAB_B_14_Tab_B_E2(data)                                            (0x0003F000&((data)<<12))
#define DITHERING_TAB_B_14_Tab_B_E2_src(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_14_get_Tab_B_E2(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_14_Tab_B_E1_shift                                            (6)
#define DITHERING_TAB_B_14_Tab_B_E1_mask                                             (0x00000FC0)
#define DITHERING_TAB_B_14_Tab_B_E1(data)                                            (0x00000FC0&((data)<<6))
#define DITHERING_TAB_B_14_Tab_B_E1_src(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_14_get_Tab_B_E1(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_14_Tab_B_E0_shift                                            (0)
#define DITHERING_TAB_B_14_Tab_B_E0_mask                                             (0x0000003F)
#define DITHERING_TAB_B_14_Tab_B_E0(data)                                            (0x0000003F&((data)<<0))
#define DITHERING_TAB_B_14_Tab_B_E0_src(data)                                        ((0x0000003F&(data))>>0)
#define DITHERING_TAB_B_14_get_Tab_B_E0(data)                                        ((0x0000003F&(data))>>0)


#define DITHERING_TAB_B_15                                                           0x180099a4
#define DITHERING_TAB_B_15_reg_addr                                                  "0xB80099A4"
#define DITHERING_TAB_B_15_reg                                                       0xB80099A4
#define set_DITHERING_TAB_B_15_reg(data)   (*((volatile unsigned int*) DITHERING_TAB_B_15_reg)=data)
#define get_DITHERING_TAB_B_15_reg   (*((volatile unsigned int*) DITHERING_TAB_B_15_reg))
#define DITHERING_TAB_B_15_inst_adr                                                  "0x0069"
#define DITHERING_TAB_B_15_inst                                                      0x0069
#define DITHERING_TAB_B_15_Tab_B_F3_shift                                            (18)
#define DITHERING_TAB_B_15_Tab_B_F3_mask                                             (0x00FC0000)
#define DITHERING_TAB_B_15_Tab_B_F3(data)                                            (0x00FC0000&((data)<<18))
#define DITHERING_TAB_B_15_Tab_B_F3_src(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_15_get_Tab_B_F3(data)                                        ((0x00FC0000&(data))>>18)
#define DITHERING_TAB_B_15_Tab_B_F2_shift                                            (12)
#define DITHERING_TAB_B_15_Tab_B_F2_mask                                             (0x0003F000)
#define DITHERING_TAB_B_15_Tab_B_F2(data)                                            (0x0003F000&((data)<<12))
#define DITHERING_TAB_B_15_Tab_B_F2_src(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_15_get_Tab_B_F2(data)                                        ((0x0003F000&(data))>>12)
#define DITHERING_TAB_B_15_Tab_B_F1_shift                                            (6)
#define DITHERING_TAB_B_15_Tab_B_F1_mask                                             (0x00000FC0)
#define DITHERING_TAB_B_15_Tab_B_F1(data)                                            (0x00000FC0&((data)<<6))
#define DITHERING_TAB_B_15_Tab_B_F1_src(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_15_get_Tab_B_F1(data)                                        ((0x00000FC0&(data))>>6)
#define DITHERING_TAB_B_15_Tab_B_F0_shift                                            (0)
#define DITHERING_TAB_B_15_Tab_B_F0_mask                                             (0x0000003F)
#define DITHERING_TAB_B_15_Tab_B_F0(data)                                            (0x0000003F&((data)<<0))
#define DITHERING_TAB_B_15_Tab_B_F0_src(data)                                        ((0x0000003F&(data))>>0)
#define DITHERING_TAB_B_15_get_Tab_B_F0(data)                                        ((0x0000003F&(data))>>0)


#define TEMPORAL_OFFSET                                                              0x180099a8
#define TEMPORAL_OFFSET_reg_addr                                                     "0xB80099A8"
#define TEMPORAL_OFFSET_reg                                                          0xB80099A8
#define set_TEMPORAL_OFFSET_reg(data)   (*((volatile unsigned int*) TEMPORAL_OFFSET_reg)=data)
#define get_TEMPORAL_OFFSET_reg   (*((volatile unsigned int*) TEMPORAL_OFFSET_reg))
#define TEMPORAL_OFFSET_inst_adr                                                     "0x006A"
#define TEMPORAL_OFFSET_inst                                                         0x006A
#define TEMPORAL_OFFSET_Temp_offset_15_shift                                         (30)
#define TEMPORAL_OFFSET_Temp_offset_15_mask                                          (0xC0000000)
#define TEMPORAL_OFFSET_Temp_offset_15(data)                                         (0xC0000000&((data)<<30))
#define TEMPORAL_OFFSET_Temp_offset_15_src(data)                                     ((0xC0000000&(data))>>30)
#define TEMPORAL_OFFSET_get_Temp_offset_15(data)                                     ((0xC0000000&(data))>>30)
#define TEMPORAL_OFFSET_Temp_offset_14_shift                                         (28)
#define TEMPORAL_OFFSET_Temp_offset_14_mask                                          (0x30000000)
#define TEMPORAL_OFFSET_Temp_offset_14(data)                                         (0x30000000&((data)<<28))
#define TEMPORAL_OFFSET_Temp_offset_14_src(data)                                     ((0x30000000&(data))>>28)
#define TEMPORAL_OFFSET_get_Temp_offset_14(data)                                     ((0x30000000&(data))>>28)
#define TEMPORAL_OFFSET_Temp_offset_13_shift                                         (26)
#define TEMPORAL_OFFSET_Temp_offset_13_mask                                          (0x0C000000)
#define TEMPORAL_OFFSET_Temp_offset_13(data)                                         (0x0C000000&((data)<<26))
#define TEMPORAL_OFFSET_Temp_offset_13_src(data)                                     ((0x0C000000&(data))>>26)
#define TEMPORAL_OFFSET_get_Temp_offset_13(data)                                     ((0x0C000000&(data))>>26)
#define TEMPORAL_OFFSET_Temp_offset_12_shift                                         (24)
#define TEMPORAL_OFFSET_Temp_offset_12_mask                                          (0x03000000)
#define TEMPORAL_OFFSET_Temp_offset_12(data)                                         (0x03000000&((data)<<24))
#define TEMPORAL_OFFSET_Temp_offset_12_src(data)                                     ((0x03000000&(data))>>24)
#define TEMPORAL_OFFSET_get_Temp_offset_12(data)                                     ((0x03000000&(data))>>24)
#define TEMPORAL_OFFSET_Temp_offset_11_shift                                         (22)
#define TEMPORAL_OFFSET_Temp_offset_11_mask                                          (0x00C00000)
#define TEMPORAL_OFFSET_Temp_offset_11(data)                                         (0x00C00000&((data)<<22))
#define TEMPORAL_OFFSET_Temp_offset_11_src(data)                                     ((0x00C00000&(data))>>22)
#define TEMPORAL_OFFSET_get_Temp_offset_11(data)                                     ((0x00C00000&(data))>>22)
#define TEMPORAL_OFFSET_Temp_offset_10_shift                                         (20)
#define TEMPORAL_OFFSET_Temp_offset_10_mask                                          (0x00300000)
#define TEMPORAL_OFFSET_Temp_offset_10(data)                                         (0x00300000&((data)<<20))
#define TEMPORAL_OFFSET_Temp_offset_10_src(data)                                     ((0x00300000&(data))>>20)
#define TEMPORAL_OFFSET_get_Temp_offset_10(data)                                     ((0x00300000&(data))>>20)
#define TEMPORAL_OFFSET_Temp_offset_9_shift                                          (18)
#define TEMPORAL_OFFSET_Temp_offset_9_mask                                           (0x000C0000)
#define TEMPORAL_OFFSET_Temp_offset_9(data)                                          (0x000C0000&((data)<<18))
#define TEMPORAL_OFFSET_Temp_offset_9_src(data)                                      ((0x000C0000&(data))>>18)
#define TEMPORAL_OFFSET_get_Temp_offset_9(data)                                      ((0x000C0000&(data))>>18)
#define TEMPORAL_OFFSET_Temp_offset_8_shift                                          (16)
#define TEMPORAL_OFFSET_Temp_offset_8_mask                                           (0x00030000)
#define TEMPORAL_OFFSET_Temp_offset_8(data)                                          (0x00030000&((data)<<16))
#define TEMPORAL_OFFSET_Temp_offset_8_src(data)                                      ((0x00030000&(data))>>16)
#define TEMPORAL_OFFSET_get_Temp_offset_8(data)                                      ((0x00030000&(data))>>16)
#define TEMPORAL_OFFSET_Temp_offset_7_shift                                          (14)
#define TEMPORAL_OFFSET_Temp_offset_7_mask                                           (0x0000C000)
#define TEMPORAL_OFFSET_Temp_offset_7(data)                                          (0x0000C000&((data)<<14))
#define TEMPORAL_OFFSET_Temp_offset_7_src(data)                                      ((0x0000C000&(data))>>14)
#define TEMPORAL_OFFSET_get_Temp_offset_7(data)                                      ((0x0000C000&(data))>>14)
#define TEMPORAL_OFFSET_Temp_offset_6_shift                                          (12)
#define TEMPORAL_OFFSET_Temp_offset_6_mask                                           (0x00003000)
#define TEMPORAL_OFFSET_Temp_offset_6(data)                                          (0x00003000&((data)<<12))
#define TEMPORAL_OFFSET_Temp_offset_6_src(data)                                      ((0x00003000&(data))>>12)
#define TEMPORAL_OFFSET_get_Temp_offset_6(data)                                      ((0x00003000&(data))>>12)
#define TEMPORAL_OFFSET_Temp_offset_5_shift                                          (10)
#define TEMPORAL_OFFSET_Temp_offset_5_mask                                           (0x00000C00)
#define TEMPORAL_OFFSET_Temp_offset_5(data)                                          (0x00000C00&((data)<<10))
#define TEMPORAL_OFFSET_Temp_offset_5_src(data)                                      ((0x00000C00&(data))>>10)
#define TEMPORAL_OFFSET_get_Temp_offset_5(data)                                      ((0x00000C00&(data))>>10)
#define TEMPORAL_OFFSET_Temp_offset_4_shift                                          (8)
#define TEMPORAL_OFFSET_Temp_offset_4_mask                                           (0x00000300)
#define TEMPORAL_OFFSET_Temp_offset_4(data)                                          (0x00000300&((data)<<8))
#define TEMPORAL_OFFSET_Temp_offset_4_src(data)                                      ((0x00000300&(data))>>8)
#define TEMPORAL_OFFSET_get_Temp_offset_4(data)                                      ((0x00000300&(data))>>8)
#define TEMPORAL_OFFSET_Temp_offset_3_shift                                          (6)
#define TEMPORAL_OFFSET_Temp_offset_3_mask                                           (0x000000C0)
#define TEMPORAL_OFFSET_Temp_offset_3(data)                                          (0x000000C0&((data)<<6))
#define TEMPORAL_OFFSET_Temp_offset_3_src(data)                                      ((0x000000C0&(data))>>6)
#define TEMPORAL_OFFSET_get_Temp_offset_3(data)                                      ((0x000000C0&(data))>>6)
#define TEMPORAL_OFFSET_Temp_offset_2_shift                                          (4)
#define TEMPORAL_OFFSET_Temp_offset_2_mask                                           (0x00000030)
#define TEMPORAL_OFFSET_Temp_offset_2(data)                                          (0x00000030&((data)<<4))
#define TEMPORAL_OFFSET_Temp_offset_2_src(data)                                      ((0x00000030&(data))>>4)
#define TEMPORAL_OFFSET_get_Temp_offset_2(data)                                      ((0x00000030&(data))>>4)
#define TEMPORAL_OFFSET_Temp_offset_1_shift                                          (2)
#define TEMPORAL_OFFSET_Temp_offset_1_mask                                           (0x0000000C)
#define TEMPORAL_OFFSET_Temp_offset_1(data)                                          (0x0000000C&((data)<<2))
#define TEMPORAL_OFFSET_Temp_offset_1_src(data)                                      ((0x0000000C&(data))>>2)
#define TEMPORAL_OFFSET_get_Temp_offset_1(data)                                      ((0x0000000C&(data))>>2)
#define TEMPORAL_OFFSET_Temp_offset_0_shift                                          (0)
#define TEMPORAL_OFFSET_Temp_offset_0_mask                                           (0x00000003)
#define TEMPORAL_OFFSET_Temp_offset_0(data)                                          (0x00000003&((data)<<0))
#define TEMPORAL_OFFSET_Temp_offset_0_src(data)                                      ((0x00000003&(data))>>0)
#define TEMPORAL_OFFSET_get_Temp_offset_0(data)                                      ((0x00000003&(data))>>0)


#define DITHERING_2ND_SEQ_R_0                                                        0x180099ac
#define DITHERING_2ND_SEQ_R_0_reg_addr                                               "0xB80099AC"
#define DITHERING_2ND_SEQ_R_0_reg                                                    0xB80099AC
#define set_DITHERING_2ND_SEQ_R_0_reg(data)   (*((volatile unsigned int*) DITHERING_2ND_SEQ_R_0_reg)=data)
#define get_DITHERING_2ND_SEQ_R_0_reg   (*((volatile unsigned int*) DITHERING_2ND_SEQ_R_0_reg))
#define DITHERING_2ND_SEQ_R_0_inst_adr                                               "0x006B"
#define DITHERING_2ND_SEQ_R_0_inst                                                   0x006B
#define DITHERING_2ND_SEQ_R_0_Seq_R_7_shift                                          (28)
#define DITHERING_2ND_SEQ_R_0_Seq_R_7_mask                                           (0xF0000000)
#define DITHERING_2ND_SEQ_R_0_Seq_R_7(data)                                          (0xF0000000&((data)<<28))
#define DITHERING_2ND_SEQ_R_0_Seq_R_7_src(data)                                      ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_R_0_get_Seq_R_7(data)                                      ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_R_0_Seq_R_6_shift                                          (24)
#define DITHERING_2ND_SEQ_R_0_Seq_R_6_mask                                           (0x0F000000)
#define DITHERING_2ND_SEQ_R_0_Seq_R_6(data)                                          (0x0F000000&((data)<<24))
#define DITHERING_2ND_SEQ_R_0_Seq_R_6_src(data)                                      ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_R_0_get_Seq_R_6(data)                                      ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_R_0_Seq_R_5_shift                                          (20)
#define DITHERING_2ND_SEQ_R_0_Seq_R_5_mask                                           (0x00F00000)
#define DITHERING_2ND_SEQ_R_0_Seq_R_5(data)                                          (0x00F00000&((data)<<20))
#define DITHERING_2ND_SEQ_R_0_Seq_R_5_src(data)                                      ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_R_0_get_Seq_R_5(data)                                      ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_R_0_Seq_R_4_shift                                          (16)
#define DITHERING_2ND_SEQ_R_0_Seq_R_4_mask                                           (0x000F0000)
#define DITHERING_2ND_SEQ_R_0_Seq_R_4(data)                                          (0x000F0000&((data)<<16))
#define DITHERING_2ND_SEQ_R_0_Seq_R_4_src(data)                                      ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_R_0_get_Seq_R_4(data)                                      ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_R_0_Seq_R_3_shift                                          (12)
#define DITHERING_2ND_SEQ_R_0_Seq_R_3_mask                                           (0x0000F000)
#define DITHERING_2ND_SEQ_R_0_Seq_R_3(data)                                          (0x0000F000&((data)<<12))
#define DITHERING_2ND_SEQ_R_0_Seq_R_3_src(data)                                      ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_R_0_get_Seq_R_3(data)                                      ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_R_0_Seq_R_2_shift                                          (8)
#define DITHERING_2ND_SEQ_R_0_Seq_R_2_mask                                           (0x00000F00)
#define DITHERING_2ND_SEQ_R_0_Seq_R_2(data)                                          (0x00000F00&((data)<<8))
#define DITHERING_2ND_SEQ_R_0_Seq_R_2_src(data)                                      ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_R_0_get_Seq_R_2(data)                                      ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_R_0_Seq_R_1_shift                                          (4)
#define DITHERING_2ND_SEQ_R_0_Seq_R_1_mask                                           (0x000000F0)
#define DITHERING_2ND_SEQ_R_0_Seq_R_1(data)                                          (0x000000F0&((data)<<4))
#define DITHERING_2ND_SEQ_R_0_Seq_R_1_src(data)                                      ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_R_0_get_Seq_R_1(data)                                      ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_R_0_Seq_R_0_shift                                          (0)
#define DITHERING_2ND_SEQ_R_0_Seq_R_0_mask                                           (0x0000000F)
#define DITHERING_2ND_SEQ_R_0_Seq_R_0(data)                                          (0x0000000F&((data)<<0))
#define DITHERING_2ND_SEQ_R_0_Seq_R_0_src(data)                                      ((0x0000000F&(data))>>0)
#define DITHERING_2ND_SEQ_R_0_get_Seq_R_0(data)                                      ((0x0000000F&(data))>>0)


#define DITHERING_2ND_SEQ_R_1                                                        0x180099b0
#define DITHERING_2ND_SEQ_R_1_reg_addr                                               "0xB80099B0"
#define DITHERING_2ND_SEQ_R_1_reg                                                    0xB80099B0
#define set_DITHERING_2ND_SEQ_R_1_reg(data)   (*((volatile unsigned int*) DITHERING_2ND_SEQ_R_1_reg)=data)
#define get_DITHERING_2ND_SEQ_R_1_reg   (*((volatile unsigned int*) DITHERING_2ND_SEQ_R_1_reg))
#define DITHERING_2ND_SEQ_R_1_inst_adr                                               "0x006C"
#define DITHERING_2ND_SEQ_R_1_inst                                                   0x006C
#define DITHERING_2ND_SEQ_R_1_Seq_R_15_shift                                         (28)
#define DITHERING_2ND_SEQ_R_1_Seq_R_15_mask                                          (0xF0000000)
#define DITHERING_2ND_SEQ_R_1_Seq_R_15(data)                                         (0xF0000000&((data)<<28))
#define DITHERING_2ND_SEQ_R_1_Seq_R_15_src(data)                                     ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_R_1_get_Seq_R_15(data)                                     ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_R_1_Seq_R_14_shift                                         (24)
#define DITHERING_2ND_SEQ_R_1_Seq_R_14_mask                                          (0x0F000000)
#define DITHERING_2ND_SEQ_R_1_Seq_R_14(data)                                         (0x0F000000&((data)<<24))
#define DITHERING_2ND_SEQ_R_1_Seq_R_14_src(data)                                     ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_R_1_get_Seq_R_14(data)                                     ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_R_1_Seq_R_13_shift                                         (20)
#define DITHERING_2ND_SEQ_R_1_Seq_R_13_mask                                          (0x00F00000)
#define DITHERING_2ND_SEQ_R_1_Seq_R_13(data)                                         (0x00F00000&((data)<<20))
#define DITHERING_2ND_SEQ_R_1_Seq_R_13_src(data)                                     ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_R_1_get_Seq_R_13(data)                                     ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_R_1_Seq_R_12_shift                                         (16)
#define DITHERING_2ND_SEQ_R_1_Seq_R_12_mask                                          (0x000F0000)
#define DITHERING_2ND_SEQ_R_1_Seq_R_12(data)                                         (0x000F0000&((data)<<16))
#define DITHERING_2ND_SEQ_R_1_Seq_R_12_src(data)                                     ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_R_1_get_Seq_R_12(data)                                     ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_R_1_Seq_R_11_shift                                         (12)
#define DITHERING_2ND_SEQ_R_1_Seq_R_11_mask                                          (0x0000F000)
#define DITHERING_2ND_SEQ_R_1_Seq_R_11(data)                                         (0x0000F000&((data)<<12))
#define DITHERING_2ND_SEQ_R_1_Seq_R_11_src(data)                                     ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_R_1_get_Seq_R_11(data)                                     ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_R_1_Seq_R_10_shift                                         (8)
#define DITHERING_2ND_SEQ_R_1_Seq_R_10_mask                                          (0x00000F00)
#define DITHERING_2ND_SEQ_R_1_Seq_R_10(data)                                         (0x00000F00&((data)<<8))
#define DITHERING_2ND_SEQ_R_1_Seq_R_10_src(data)                                     ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_R_1_get_Seq_R_10(data)                                     ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_R_1_Seq_R_9_shift                                          (4)
#define DITHERING_2ND_SEQ_R_1_Seq_R_9_mask                                           (0x000000F0)
#define DITHERING_2ND_SEQ_R_1_Seq_R_9(data)                                          (0x000000F0&((data)<<4))
#define DITHERING_2ND_SEQ_R_1_Seq_R_9_src(data)                                      ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_R_1_get_Seq_R_9(data)                                      ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_R_1_Seq_R_8_shift                                          (0)
#define DITHERING_2ND_SEQ_R_1_Seq_R_8_mask                                           (0x0000000F)
#define DITHERING_2ND_SEQ_R_1_Seq_R_8(data)                                          (0x0000000F&((data)<<0))
#define DITHERING_2ND_SEQ_R_1_Seq_R_8_src(data)                                      ((0x0000000F&(data))>>0)
#define DITHERING_2ND_SEQ_R_1_get_Seq_R_8(data)                                      ((0x0000000F&(data))>>0)


#define DITHERING_2ND_SEQ_R_2                                                        0x180099b4
#define DITHERING_2ND_SEQ_R_2_reg_addr                                               "0xB80099B4"
#define DITHERING_2ND_SEQ_R_2_reg                                                    0xB80099B4
#define set_DITHERING_2ND_SEQ_R_2_reg(data)   (*((volatile unsigned int*) DITHERING_2ND_SEQ_R_2_reg)=data)
#define get_DITHERING_2ND_SEQ_R_2_reg   (*((volatile unsigned int*) DITHERING_2ND_SEQ_R_2_reg))
#define DITHERING_2ND_SEQ_R_2_inst_adr                                               "0x006D"
#define DITHERING_2ND_SEQ_R_2_inst                                                   0x006D
#define DITHERING_2ND_SEQ_R_2_Seq_R_23_shift                                         (28)
#define DITHERING_2ND_SEQ_R_2_Seq_R_23_mask                                          (0xF0000000)
#define DITHERING_2ND_SEQ_R_2_Seq_R_23(data)                                         (0xF0000000&((data)<<28))
#define DITHERING_2ND_SEQ_R_2_Seq_R_23_src(data)                                     ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_R_2_get_Seq_R_23(data)                                     ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_R_2_Seq_R_22_shift                                         (24)
#define DITHERING_2ND_SEQ_R_2_Seq_R_22_mask                                          (0x0F000000)
#define DITHERING_2ND_SEQ_R_2_Seq_R_22(data)                                         (0x0F000000&((data)<<24))
#define DITHERING_2ND_SEQ_R_2_Seq_R_22_src(data)                                     ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_R_2_get_Seq_R_22(data)                                     ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_R_2_Seq_R_21_shift                                         (20)
#define DITHERING_2ND_SEQ_R_2_Seq_R_21_mask                                          (0x00F00000)
#define DITHERING_2ND_SEQ_R_2_Seq_R_21(data)                                         (0x00F00000&((data)<<20))
#define DITHERING_2ND_SEQ_R_2_Seq_R_21_src(data)                                     ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_R_2_get_Seq_R_21(data)                                     ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_R_2_Seq_R_20_shift                                         (16)
#define DITHERING_2ND_SEQ_R_2_Seq_R_20_mask                                          (0x000F0000)
#define DITHERING_2ND_SEQ_R_2_Seq_R_20(data)                                         (0x000F0000&((data)<<16))
#define DITHERING_2ND_SEQ_R_2_Seq_R_20_src(data)                                     ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_R_2_get_Seq_R_20(data)                                     ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_R_2_Seq_R_19_shift                                         (12)
#define DITHERING_2ND_SEQ_R_2_Seq_R_19_mask                                          (0x0000F000)
#define DITHERING_2ND_SEQ_R_2_Seq_R_19(data)                                         (0x0000F000&((data)<<12))
#define DITHERING_2ND_SEQ_R_2_Seq_R_19_src(data)                                     ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_R_2_get_Seq_R_19(data)                                     ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_R_2_Seq_R_18_shift                                         (8)
#define DITHERING_2ND_SEQ_R_2_Seq_R_18_mask                                          (0x00000F00)
#define DITHERING_2ND_SEQ_R_2_Seq_R_18(data)                                         (0x00000F00&((data)<<8))
#define DITHERING_2ND_SEQ_R_2_Seq_R_18_src(data)                                     ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_R_2_get_Seq_R_18(data)                                     ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_R_2_Seq_R_17_shift                                         (4)
#define DITHERING_2ND_SEQ_R_2_Seq_R_17_mask                                          (0x000000F0)
#define DITHERING_2ND_SEQ_R_2_Seq_R_17(data)                                         (0x000000F0&((data)<<4))
#define DITHERING_2ND_SEQ_R_2_Seq_R_17_src(data)                                     ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_R_2_get_Seq_R_17(data)                                     ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_R_2_Seq_R_16_shift                                         (0)
#define DITHERING_2ND_SEQ_R_2_Seq_R_16_mask                                          (0x0000000F)
#define DITHERING_2ND_SEQ_R_2_Seq_R_16(data)                                         (0x0000000F&((data)<<0))
#define DITHERING_2ND_SEQ_R_2_Seq_R_16_src(data)                                     ((0x0000000F&(data))>>0)
#define DITHERING_2ND_SEQ_R_2_get_Seq_R_16(data)                                     ((0x0000000F&(data))>>0)


#define DITHERING_2ND_SEQ_R_3                                                        0x180099b8
#define DITHERING_2ND_SEQ_R_3_reg_addr                                               "0xB80099B8"
#define DITHERING_2ND_SEQ_R_3_reg                                                    0xB80099B8
#define set_DITHERING_2ND_SEQ_R_3_reg(data)   (*((volatile unsigned int*) DITHERING_2ND_SEQ_R_3_reg)=data)
#define get_DITHERING_2ND_SEQ_R_3_reg   (*((volatile unsigned int*) DITHERING_2ND_SEQ_R_3_reg))
#define DITHERING_2ND_SEQ_R_3_inst_adr                                               "0x006E"
#define DITHERING_2ND_SEQ_R_3_inst                                                   0x006E
#define DITHERING_2ND_SEQ_R_3_Seq_R_31_shift                                         (28)
#define DITHERING_2ND_SEQ_R_3_Seq_R_31_mask                                          (0xF0000000)
#define DITHERING_2ND_SEQ_R_3_Seq_R_31(data)                                         (0xF0000000&((data)<<28))
#define DITHERING_2ND_SEQ_R_3_Seq_R_31_src(data)                                     ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_R_3_get_Seq_R_31(data)                                     ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_R_3_Seq_R_30_shift                                         (24)
#define DITHERING_2ND_SEQ_R_3_Seq_R_30_mask                                          (0x0F000000)
#define DITHERING_2ND_SEQ_R_3_Seq_R_30(data)                                         (0x0F000000&((data)<<24))
#define DITHERING_2ND_SEQ_R_3_Seq_R_30_src(data)                                     ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_R_3_get_Seq_R_30(data)                                     ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_R_3_Seq_R_29_shift                                         (20)
#define DITHERING_2ND_SEQ_R_3_Seq_R_29_mask                                          (0x00F00000)
#define DITHERING_2ND_SEQ_R_3_Seq_R_29(data)                                         (0x00F00000&((data)<<20))
#define DITHERING_2ND_SEQ_R_3_Seq_R_29_src(data)                                     ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_R_3_get_Seq_R_29(data)                                     ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_R_3_Seq_R_28_shift                                         (16)
#define DITHERING_2ND_SEQ_R_3_Seq_R_28_mask                                          (0x000F0000)
#define DITHERING_2ND_SEQ_R_3_Seq_R_28(data)                                         (0x000F0000&((data)<<16))
#define DITHERING_2ND_SEQ_R_3_Seq_R_28_src(data)                                     ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_R_3_get_Seq_R_28(data)                                     ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_R_3_Seq_R_27_shift                                         (12)
#define DITHERING_2ND_SEQ_R_3_Seq_R_27_mask                                          (0x0000F000)
#define DITHERING_2ND_SEQ_R_3_Seq_R_27(data)                                         (0x0000F000&((data)<<12))
#define DITHERING_2ND_SEQ_R_3_Seq_R_27_src(data)                                     ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_R_3_get_Seq_R_27(data)                                     ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_R_3_Seq_R_26_shift                                         (8)
#define DITHERING_2ND_SEQ_R_3_Seq_R_26_mask                                          (0x00000F00)
#define DITHERING_2ND_SEQ_R_3_Seq_R_26(data)                                         (0x00000F00&((data)<<8))
#define DITHERING_2ND_SEQ_R_3_Seq_R_26_src(data)                                     ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_R_3_get_Seq_R_26(data)                                     ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_R_3_Seq_R_25_shift                                         (4)
#define DITHERING_2ND_SEQ_R_3_Seq_R_25_mask                                          (0x000000F0)
#define DITHERING_2ND_SEQ_R_3_Seq_R_25(data)                                         (0x000000F0&((data)<<4))
#define DITHERING_2ND_SEQ_R_3_Seq_R_25_src(data)                                     ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_R_3_get_Seq_R_25(data)                                     ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_R_3_Seq_R_24_shift                                         (0)
#define DITHERING_2ND_SEQ_R_3_Seq_R_24_mask                                          (0x0000000F)
#define DITHERING_2ND_SEQ_R_3_Seq_R_24(data)                                         (0x0000000F&((data)<<0))
#define DITHERING_2ND_SEQ_R_3_Seq_R_24_src(data)                                     ((0x0000000F&(data))>>0)
#define DITHERING_2ND_SEQ_R_3_get_Seq_R_24(data)                                     ((0x0000000F&(data))>>0)


#define DITHERING_2ND_SEQ_G_0                                                        0x180099bc
#define DITHERING_2ND_SEQ_G_0_reg_addr                                               "0xB80099BC"
#define DITHERING_2ND_SEQ_G_0_reg                                                    0xB80099BC
#define set_DITHERING_2ND_SEQ_G_0_reg(data)   (*((volatile unsigned int*) DITHERING_2ND_SEQ_G_0_reg)=data)
#define get_DITHERING_2ND_SEQ_G_0_reg   (*((volatile unsigned int*) DITHERING_2ND_SEQ_G_0_reg))
#define DITHERING_2ND_SEQ_G_0_inst_adr                                               "0x006F"
#define DITHERING_2ND_SEQ_G_0_inst                                                   0x006F
#define DITHERING_2ND_SEQ_G_0_Seq_G_7_shift                                          (28)
#define DITHERING_2ND_SEQ_G_0_Seq_G_7_mask                                           (0xF0000000)
#define DITHERING_2ND_SEQ_G_0_Seq_G_7(data)                                          (0xF0000000&((data)<<28))
#define DITHERING_2ND_SEQ_G_0_Seq_G_7_src(data)                                      ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_G_0_get_Seq_G_7(data)                                      ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_G_0_Seq_G_6_shift                                          (24)
#define DITHERING_2ND_SEQ_G_0_Seq_G_6_mask                                           (0x0F000000)
#define DITHERING_2ND_SEQ_G_0_Seq_G_6(data)                                          (0x0F000000&((data)<<24))
#define DITHERING_2ND_SEQ_G_0_Seq_G_6_src(data)                                      ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_G_0_get_Seq_G_6(data)                                      ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_G_0_Seq_G_5_shift                                          (20)
#define DITHERING_2ND_SEQ_G_0_Seq_G_5_mask                                           (0x00F00000)
#define DITHERING_2ND_SEQ_G_0_Seq_G_5(data)                                          (0x00F00000&((data)<<20))
#define DITHERING_2ND_SEQ_G_0_Seq_G_5_src(data)                                      ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_G_0_get_Seq_G_5(data)                                      ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_G_0_Seq_G_4_shift                                          (16)
#define DITHERING_2ND_SEQ_G_0_Seq_G_4_mask                                           (0x000F0000)
#define DITHERING_2ND_SEQ_G_0_Seq_G_4(data)                                          (0x000F0000&((data)<<16))
#define DITHERING_2ND_SEQ_G_0_Seq_G_4_src(data)                                      ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_G_0_get_Seq_G_4(data)                                      ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_G_0_Seq_G_3_shift                                          (12)
#define DITHERING_2ND_SEQ_G_0_Seq_G_3_mask                                           (0x0000F000)
#define DITHERING_2ND_SEQ_G_0_Seq_G_3(data)                                          (0x0000F000&((data)<<12))
#define DITHERING_2ND_SEQ_G_0_Seq_G_3_src(data)                                      ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_G_0_get_Seq_G_3(data)                                      ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_G_0_Seq_G_2_shift                                          (8)
#define DITHERING_2ND_SEQ_G_0_Seq_G_2_mask                                           (0x00000F00)
#define DITHERING_2ND_SEQ_G_0_Seq_G_2(data)                                          (0x00000F00&((data)<<8))
#define DITHERING_2ND_SEQ_G_0_Seq_G_2_src(data)                                      ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_G_0_get_Seq_G_2(data)                                      ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_G_0_Seq_G_1_shift                                          (4)
#define DITHERING_2ND_SEQ_G_0_Seq_G_1_mask                                           (0x000000F0)
#define DITHERING_2ND_SEQ_G_0_Seq_G_1(data)                                          (0x000000F0&((data)<<4))
#define DITHERING_2ND_SEQ_G_0_Seq_G_1_src(data)                                      ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_G_0_get_Seq_G_1(data)                                      ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_G_0_Seq_G_0_shift                                          (0)
#define DITHERING_2ND_SEQ_G_0_Seq_G_0_mask                                           (0x0000000F)
#define DITHERING_2ND_SEQ_G_0_Seq_G_0(data)                                          (0x0000000F&((data)<<0))
#define DITHERING_2ND_SEQ_G_0_Seq_G_0_src(data)                                      ((0x0000000F&(data))>>0)
#define DITHERING_2ND_SEQ_G_0_get_Seq_G_0(data)                                      ((0x0000000F&(data))>>0)


#define DITHERING_2ND_SEQ_G_1                                                        0x180099c0
#define DITHERING_2ND_SEQ_G_1_reg_addr                                               "0xB80099C0"
#define DITHERING_2ND_SEQ_G_1_reg                                                    0xB80099C0
#define set_DITHERING_2ND_SEQ_G_1_reg(data)   (*((volatile unsigned int*) DITHERING_2ND_SEQ_G_1_reg)=data)
#define get_DITHERING_2ND_SEQ_G_1_reg   (*((volatile unsigned int*) DITHERING_2ND_SEQ_G_1_reg))
#define DITHERING_2ND_SEQ_G_1_inst_adr                                               "0x0070"
#define DITHERING_2ND_SEQ_G_1_inst                                                   0x0070
#define DITHERING_2ND_SEQ_G_1_Seq_G_15_shift                                         (28)
#define DITHERING_2ND_SEQ_G_1_Seq_G_15_mask                                          (0xF0000000)
#define DITHERING_2ND_SEQ_G_1_Seq_G_15(data)                                         (0xF0000000&((data)<<28))
#define DITHERING_2ND_SEQ_G_1_Seq_G_15_src(data)                                     ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_G_1_get_Seq_G_15(data)                                     ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_G_1_Seq_G_14_shift                                         (24)
#define DITHERING_2ND_SEQ_G_1_Seq_G_14_mask                                          (0x0F000000)
#define DITHERING_2ND_SEQ_G_1_Seq_G_14(data)                                         (0x0F000000&((data)<<24))
#define DITHERING_2ND_SEQ_G_1_Seq_G_14_src(data)                                     ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_G_1_get_Seq_G_14(data)                                     ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_G_1_Seq_G_13_shift                                         (20)
#define DITHERING_2ND_SEQ_G_1_Seq_G_13_mask                                          (0x00F00000)
#define DITHERING_2ND_SEQ_G_1_Seq_G_13(data)                                         (0x00F00000&((data)<<20))
#define DITHERING_2ND_SEQ_G_1_Seq_G_13_src(data)                                     ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_G_1_get_Seq_G_13(data)                                     ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_G_1_Seq_G_12_shift                                         (16)
#define DITHERING_2ND_SEQ_G_1_Seq_G_12_mask                                          (0x000F0000)
#define DITHERING_2ND_SEQ_G_1_Seq_G_12(data)                                         (0x000F0000&((data)<<16))
#define DITHERING_2ND_SEQ_G_1_Seq_G_12_src(data)                                     ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_G_1_get_Seq_G_12(data)                                     ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_G_1_Seq_G_11_shift                                         (12)
#define DITHERING_2ND_SEQ_G_1_Seq_G_11_mask                                          (0x0000F000)
#define DITHERING_2ND_SEQ_G_1_Seq_G_11(data)                                         (0x0000F000&((data)<<12))
#define DITHERING_2ND_SEQ_G_1_Seq_G_11_src(data)                                     ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_G_1_get_Seq_G_11(data)                                     ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_G_1_Seq_G_10_shift                                         (8)
#define DITHERING_2ND_SEQ_G_1_Seq_G_10_mask                                          (0x00000F00)
#define DITHERING_2ND_SEQ_G_1_Seq_G_10(data)                                         (0x00000F00&((data)<<8))
#define DITHERING_2ND_SEQ_G_1_Seq_G_10_src(data)                                     ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_G_1_get_Seq_G_10(data)                                     ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_G_1_Seq_G_9_shift                                          (4)
#define DITHERING_2ND_SEQ_G_1_Seq_G_9_mask                                           (0x000000F0)
#define DITHERING_2ND_SEQ_G_1_Seq_G_9(data)                                          (0x000000F0&((data)<<4))
#define DITHERING_2ND_SEQ_G_1_Seq_G_9_src(data)                                      ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_G_1_get_Seq_G_9(data)                                      ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_G_1_Seq_G_8_shift                                          (0)
#define DITHERING_2ND_SEQ_G_1_Seq_G_8_mask                                           (0x0000000F)
#define DITHERING_2ND_SEQ_G_1_Seq_G_8(data)                                          (0x0000000F&((data)<<0))
#define DITHERING_2ND_SEQ_G_1_Seq_G_8_src(data)                                      ((0x0000000F&(data))>>0)
#define DITHERING_2ND_SEQ_G_1_get_Seq_G_8(data)                                      ((0x0000000F&(data))>>0)


#define DITHERING_2ND_SEQ_G_2                                                        0x180099c4
#define DITHERING_2ND_SEQ_G_2_reg_addr                                               "0xB80099C4"
#define DITHERING_2ND_SEQ_G_2_reg                                                    0xB80099C4
#define set_DITHERING_2ND_SEQ_G_2_reg(data)   (*((volatile unsigned int*) DITHERING_2ND_SEQ_G_2_reg)=data)
#define get_DITHERING_2ND_SEQ_G_2_reg   (*((volatile unsigned int*) DITHERING_2ND_SEQ_G_2_reg))
#define DITHERING_2ND_SEQ_G_2_inst_adr                                               "0x0071"
#define DITHERING_2ND_SEQ_G_2_inst                                                   0x0071
#define DITHERING_2ND_SEQ_G_2_Seq_G_23_shift                                         (28)
#define DITHERING_2ND_SEQ_G_2_Seq_G_23_mask                                          (0xF0000000)
#define DITHERING_2ND_SEQ_G_2_Seq_G_23(data)                                         (0xF0000000&((data)<<28))
#define DITHERING_2ND_SEQ_G_2_Seq_G_23_src(data)                                     ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_G_2_get_Seq_G_23(data)                                     ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_G_2_Seq_G_22_shift                                         (24)
#define DITHERING_2ND_SEQ_G_2_Seq_G_22_mask                                          (0x0F000000)
#define DITHERING_2ND_SEQ_G_2_Seq_G_22(data)                                         (0x0F000000&((data)<<24))
#define DITHERING_2ND_SEQ_G_2_Seq_G_22_src(data)                                     ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_G_2_get_Seq_G_22(data)                                     ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_G_2_Seq_G_21_shift                                         (20)
#define DITHERING_2ND_SEQ_G_2_Seq_G_21_mask                                          (0x00F00000)
#define DITHERING_2ND_SEQ_G_2_Seq_G_21(data)                                         (0x00F00000&((data)<<20))
#define DITHERING_2ND_SEQ_G_2_Seq_G_21_src(data)                                     ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_G_2_get_Seq_G_21(data)                                     ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_G_2_Seq_G_20_shift                                         (16)
#define DITHERING_2ND_SEQ_G_2_Seq_G_20_mask                                          (0x000F0000)
#define DITHERING_2ND_SEQ_G_2_Seq_G_20(data)                                         (0x000F0000&((data)<<16))
#define DITHERING_2ND_SEQ_G_2_Seq_G_20_src(data)                                     ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_G_2_get_Seq_G_20(data)                                     ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_G_2_Seq_G_19_shift                                         (12)
#define DITHERING_2ND_SEQ_G_2_Seq_G_19_mask                                          (0x0000F000)
#define DITHERING_2ND_SEQ_G_2_Seq_G_19(data)                                         (0x0000F000&((data)<<12))
#define DITHERING_2ND_SEQ_G_2_Seq_G_19_src(data)                                     ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_G_2_get_Seq_G_19(data)                                     ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_G_2_Seq_G_18_shift                                         (8)
#define DITHERING_2ND_SEQ_G_2_Seq_G_18_mask                                          (0x00000F00)
#define DITHERING_2ND_SEQ_G_2_Seq_G_18(data)                                         (0x00000F00&((data)<<8))
#define DITHERING_2ND_SEQ_G_2_Seq_G_18_src(data)                                     ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_G_2_get_Seq_G_18(data)                                     ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_G_2_Seq_G_17_shift                                         (4)
#define DITHERING_2ND_SEQ_G_2_Seq_G_17_mask                                          (0x000000F0)
#define DITHERING_2ND_SEQ_G_2_Seq_G_17(data)                                         (0x000000F0&((data)<<4))
#define DITHERING_2ND_SEQ_G_2_Seq_G_17_src(data)                                     ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_G_2_get_Seq_G_17(data)                                     ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_G_2_Seq_G_16_shift                                         (0)
#define DITHERING_2ND_SEQ_G_2_Seq_G_16_mask                                          (0x0000000F)
#define DITHERING_2ND_SEQ_G_2_Seq_G_16(data)                                         (0x0000000F&((data)<<0))
#define DITHERING_2ND_SEQ_G_2_Seq_G_16_src(data)                                     ((0x0000000F&(data))>>0)
#define DITHERING_2ND_SEQ_G_2_get_Seq_G_16(data)                                     ((0x0000000F&(data))>>0)


#define DITHERING_2ND_SEQ_G_3                                                        0x180099c8
#define DITHERING_2ND_SEQ_G_3_reg_addr                                               "0xB80099C8"
#define DITHERING_2ND_SEQ_G_3_reg                                                    0xB80099C8
#define set_DITHERING_2ND_SEQ_G_3_reg(data)   (*((volatile unsigned int*) DITHERING_2ND_SEQ_G_3_reg)=data)
#define get_DITHERING_2ND_SEQ_G_3_reg   (*((volatile unsigned int*) DITHERING_2ND_SEQ_G_3_reg))
#define DITHERING_2ND_SEQ_G_3_inst_adr                                               "0x0072"
#define DITHERING_2ND_SEQ_G_3_inst                                                   0x0072
#define DITHERING_2ND_SEQ_G_3_Seq_G_31_shift                                         (28)
#define DITHERING_2ND_SEQ_G_3_Seq_G_31_mask                                          (0xF0000000)
#define DITHERING_2ND_SEQ_G_3_Seq_G_31(data)                                         (0xF0000000&((data)<<28))
#define DITHERING_2ND_SEQ_G_3_Seq_G_31_src(data)                                     ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_G_3_get_Seq_G_31(data)                                     ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_G_3_Seq_G_30_shift                                         (24)
#define DITHERING_2ND_SEQ_G_3_Seq_G_30_mask                                          (0x0F000000)
#define DITHERING_2ND_SEQ_G_3_Seq_G_30(data)                                         (0x0F000000&((data)<<24))
#define DITHERING_2ND_SEQ_G_3_Seq_G_30_src(data)                                     ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_G_3_get_Seq_G_30(data)                                     ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_G_3_Seq_G_29_shift                                         (20)
#define DITHERING_2ND_SEQ_G_3_Seq_G_29_mask                                          (0x00F00000)
#define DITHERING_2ND_SEQ_G_3_Seq_G_29(data)                                         (0x00F00000&((data)<<20))
#define DITHERING_2ND_SEQ_G_3_Seq_G_29_src(data)                                     ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_G_3_get_Seq_G_29(data)                                     ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_G_3_Seq_G_28_shift                                         (16)
#define DITHERING_2ND_SEQ_G_3_Seq_G_28_mask                                          (0x000F0000)
#define DITHERING_2ND_SEQ_G_3_Seq_G_28(data)                                         (0x000F0000&((data)<<16))
#define DITHERING_2ND_SEQ_G_3_Seq_G_28_src(data)                                     ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_G_3_get_Seq_G_28(data)                                     ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_G_3_Seq_G_27_shift                                         (12)
#define DITHERING_2ND_SEQ_G_3_Seq_G_27_mask                                          (0x0000F000)
#define DITHERING_2ND_SEQ_G_3_Seq_G_27(data)                                         (0x0000F000&((data)<<12))
#define DITHERING_2ND_SEQ_G_3_Seq_G_27_src(data)                                     ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_G_3_get_Seq_G_27(data)                                     ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_G_3_Seq_G_26_shift                                         (8)
#define DITHERING_2ND_SEQ_G_3_Seq_G_26_mask                                          (0x00000F00)
#define DITHERING_2ND_SEQ_G_3_Seq_G_26(data)                                         (0x00000F00&((data)<<8))
#define DITHERING_2ND_SEQ_G_3_Seq_G_26_src(data)                                     ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_G_3_get_Seq_G_26(data)                                     ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_G_3_Seq_G_25_shift                                         (4)
#define DITHERING_2ND_SEQ_G_3_Seq_G_25_mask                                          (0x000000F0)
#define DITHERING_2ND_SEQ_G_3_Seq_G_25(data)                                         (0x000000F0&((data)<<4))
#define DITHERING_2ND_SEQ_G_3_Seq_G_25_src(data)                                     ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_G_3_get_Seq_G_25(data)                                     ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_G_3_Seq_G_24_shift                                         (0)
#define DITHERING_2ND_SEQ_G_3_Seq_G_24_mask                                          (0x0000000F)
#define DITHERING_2ND_SEQ_G_3_Seq_G_24(data)                                         (0x0000000F&((data)<<0))
#define DITHERING_2ND_SEQ_G_3_Seq_G_24_src(data)                                     ((0x0000000F&(data))>>0)
#define DITHERING_2ND_SEQ_G_3_get_Seq_G_24(data)                                     ((0x0000000F&(data))>>0)


#define DITHERING_2ND_SEQ_B_0                                                        0x180099cc
#define DITHERING_2ND_SEQ_B_0_reg_addr                                               "0xB80099CC"
#define DITHERING_2ND_SEQ_B_0_reg                                                    0xB80099CC
#define set_DITHERING_2ND_SEQ_B_0_reg(data)   (*((volatile unsigned int*) DITHERING_2ND_SEQ_B_0_reg)=data)
#define get_DITHERING_2ND_SEQ_B_0_reg   (*((volatile unsigned int*) DITHERING_2ND_SEQ_B_0_reg))
#define DITHERING_2ND_SEQ_B_0_inst_adr                                               "0x0073"
#define DITHERING_2ND_SEQ_B_0_inst                                                   0x0073
#define DITHERING_2ND_SEQ_B_0_Seq_B_7_shift                                          (28)
#define DITHERING_2ND_SEQ_B_0_Seq_B_7_mask                                           (0xF0000000)
#define DITHERING_2ND_SEQ_B_0_Seq_B_7(data)                                          (0xF0000000&((data)<<28))
#define DITHERING_2ND_SEQ_B_0_Seq_B_7_src(data)                                      ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_B_0_get_Seq_B_7(data)                                      ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_B_0_Seq_B_6_shift                                          (24)
#define DITHERING_2ND_SEQ_B_0_Seq_B_6_mask                                           (0x0F000000)
#define DITHERING_2ND_SEQ_B_0_Seq_B_6(data)                                          (0x0F000000&((data)<<24))
#define DITHERING_2ND_SEQ_B_0_Seq_B_6_src(data)                                      ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_B_0_get_Seq_B_6(data)                                      ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_B_0_Seq_B_5_shift                                          (20)
#define DITHERING_2ND_SEQ_B_0_Seq_B_5_mask                                           (0x00F00000)
#define DITHERING_2ND_SEQ_B_0_Seq_B_5(data)                                          (0x00F00000&((data)<<20))
#define DITHERING_2ND_SEQ_B_0_Seq_B_5_src(data)                                      ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_B_0_get_Seq_B_5(data)                                      ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_B_0_Seq_B_4_shift                                          (16)
#define DITHERING_2ND_SEQ_B_0_Seq_B_4_mask                                           (0x000F0000)
#define DITHERING_2ND_SEQ_B_0_Seq_B_4(data)                                          (0x000F0000&((data)<<16))
#define DITHERING_2ND_SEQ_B_0_Seq_B_4_src(data)                                      ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_B_0_get_Seq_B_4(data)                                      ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_B_0_Seq_B_3_shift                                          (12)
#define DITHERING_2ND_SEQ_B_0_Seq_B_3_mask                                           (0x0000F000)
#define DITHERING_2ND_SEQ_B_0_Seq_B_3(data)                                          (0x0000F000&((data)<<12))
#define DITHERING_2ND_SEQ_B_0_Seq_B_3_src(data)                                      ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_B_0_get_Seq_B_3(data)                                      ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_B_0_Seq_B_2_shift                                          (8)
#define DITHERING_2ND_SEQ_B_0_Seq_B_2_mask                                           (0x00000F00)
#define DITHERING_2ND_SEQ_B_0_Seq_B_2(data)                                          (0x00000F00&((data)<<8))
#define DITHERING_2ND_SEQ_B_0_Seq_B_2_src(data)                                      ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_B_0_get_Seq_B_2(data)                                      ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_B_0_Seq_B_1_shift                                          (4)
#define DITHERING_2ND_SEQ_B_0_Seq_B_1_mask                                           (0x000000F0)
#define DITHERING_2ND_SEQ_B_0_Seq_B_1(data)                                          (0x000000F0&((data)<<4))
#define DITHERING_2ND_SEQ_B_0_Seq_B_1_src(data)                                      ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_B_0_get_Seq_B_1(data)                                      ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_B_0_Seq_B_0_shift                                          (0)
#define DITHERING_2ND_SEQ_B_0_Seq_B_0_mask                                           (0x0000000F)
#define DITHERING_2ND_SEQ_B_0_Seq_B_0(data)                                          (0x0000000F&((data)<<0))
#define DITHERING_2ND_SEQ_B_0_Seq_B_0_src(data)                                      ((0x0000000F&(data))>>0)
#define DITHERING_2ND_SEQ_B_0_get_Seq_B_0(data)                                      ((0x0000000F&(data))>>0)


#define DITHERING_2ND_SEQ_B_1                                                        0x180099d0
#define DITHERING_2ND_SEQ_B_1_reg_addr                                               "0xB80099D0"
#define DITHERING_2ND_SEQ_B_1_reg                                                    0xB80099D0
#define set_DITHERING_2ND_SEQ_B_1_reg(data)   (*((volatile unsigned int*) DITHERING_2ND_SEQ_B_1_reg)=data)
#define get_DITHERING_2ND_SEQ_B_1_reg   (*((volatile unsigned int*) DITHERING_2ND_SEQ_B_1_reg))
#define DITHERING_2ND_SEQ_B_1_inst_adr                                               "0x0074"
#define DITHERING_2ND_SEQ_B_1_inst                                                   0x0074
#define DITHERING_2ND_SEQ_B_1_Seq_B_15_shift                                         (28)
#define DITHERING_2ND_SEQ_B_1_Seq_B_15_mask                                          (0xF0000000)
#define DITHERING_2ND_SEQ_B_1_Seq_B_15(data)                                         (0xF0000000&((data)<<28))
#define DITHERING_2ND_SEQ_B_1_Seq_B_15_src(data)                                     ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_B_1_get_Seq_B_15(data)                                     ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_B_1_Seq_B_14_shift                                         (24)
#define DITHERING_2ND_SEQ_B_1_Seq_B_14_mask                                          (0x0F000000)
#define DITHERING_2ND_SEQ_B_1_Seq_B_14(data)                                         (0x0F000000&((data)<<24))
#define DITHERING_2ND_SEQ_B_1_Seq_B_14_src(data)                                     ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_B_1_get_Seq_B_14(data)                                     ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_B_1_Seq_B_13_shift                                         (20)
#define DITHERING_2ND_SEQ_B_1_Seq_B_13_mask                                          (0x00F00000)
#define DITHERING_2ND_SEQ_B_1_Seq_B_13(data)                                         (0x00F00000&((data)<<20))
#define DITHERING_2ND_SEQ_B_1_Seq_B_13_src(data)                                     ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_B_1_get_Seq_B_13(data)                                     ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_B_1_Seq_B_12_shift                                         (16)
#define DITHERING_2ND_SEQ_B_1_Seq_B_12_mask                                          (0x000F0000)
#define DITHERING_2ND_SEQ_B_1_Seq_B_12(data)                                         (0x000F0000&((data)<<16))
#define DITHERING_2ND_SEQ_B_1_Seq_B_12_src(data)                                     ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_B_1_get_Seq_B_12(data)                                     ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_B_1_Seq_B_11_shift                                         (12)
#define DITHERING_2ND_SEQ_B_1_Seq_B_11_mask                                          (0x0000F000)
#define DITHERING_2ND_SEQ_B_1_Seq_B_11(data)                                         (0x0000F000&((data)<<12))
#define DITHERING_2ND_SEQ_B_1_Seq_B_11_src(data)                                     ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_B_1_get_Seq_B_11(data)                                     ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_B_1_Seq_B_10_shift                                         (8)
#define DITHERING_2ND_SEQ_B_1_Seq_B_10_mask                                          (0x00000F00)
#define DITHERING_2ND_SEQ_B_1_Seq_B_10(data)                                         (0x00000F00&((data)<<8))
#define DITHERING_2ND_SEQ_B_1_Seq_B_10_src(data)                                     ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_B_1_get_Seq_B_10(data)                                     ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_B_1_Seq_B_9_shift                                          (4)
#define DITHERING_2ND_SEQ_B_1_Seq_B_9_mask                                           (0x000000F0)
#define DITHERING_2ND_SEQ_B_1_Seq_B_9(data)                                          (0x000000F0&((data)<<4))
#define DITHERING_2ND_SEQ_B_1_Seq_B_9_src(data)                                      ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_B_1_get_Seq_B_9(data)                                      ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_B_1_Seq_B_8_shift                                          (0)
#define DITHERING_2ND_SEQ_B_1_Seq_B_8_mask                                           (0x0000000F)
#define DITHERING_2ND_SEQ_B_1_Seq_B_8(data)                                          (0x0000000F&((data)<<0))
#define DITHERING_2ND_SEQ_B_1_Seq_B_8_src(data)                                      ((0x0000000F&(data))>>0)
#define DITHERING_2ND_SEQ_B_1_get_Seq_B_8(data)                                      ((0x0000000F&(data))>>0)


#define DITHERING_2ND_SEQ_B_2                                                        0x180099d4
#define DITHERING_2ND_SEQ_B_2_reg_addr                                               "0xB80099D4"
#define DITHERING_2ND_SEQ_B_2_reg                                                    0xB80099D4
#define set_DITHERING_2ND_SEQ_B_2_reg(data)   (*((volatile unsigned int*) DITHERING_2ND_SEQ_B_2_reg)=data)
#define get_DITHERING_2ND_SEQ_B_2_reg   (*((volatile unsigned int*) DITHERING_2ND_SEQ_B_2_reg))
#define DITHERING_2ND_SEQ_B_2_inst_adr                                               "0x0075"
#define DITHERING_2ND_SEQ_B_2_inst                                                   0x0075
#define DITHERING_2ND_SEQ_B_2_Seq_B_23_shift                                         (28)
#define DITHERING_2ND_SEQ_B_2_Seq_B_23_mask                                          (0xF0000000)
#define DITHERING_2ND_SEQ_B_2_Seq_B_23(data)                                         (0xF0000000&((data)<<28))
#define DITHERING_2ND_SEQ_B_2_Seq_B_23_src(data)                                     ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_B_2_get_Seq_B_23(data)                                     ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_B_2_Seq_B_22_shift                                         (24)
#define DITHERING_2ND_SEQ_B_2_Seq_B_22_mask                                          (0x0F000000)
#define DITHERING_2ND_SEQ_B_2_Seq_B_22(data)                                         (0x0F000000&((data)<<24))
#define DITHERING_2ND_SEQ_B_2_Seq_B_22_src(data)                                     ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_B_2_get_Seq_B_22(data)                                     ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_B_2_Seq_B_21_shift                                         (20)
#define DITHERING_2ND_SEQ_B_2_Seq_B_21_mask                                          (0x00F00000)
#define DITHERING_2ND_SEQ_B_2_Seq_B_21(data)                                         (0x00F00000&((data)<<20))
#define DITHERING_2ND_SEQ_B_2_Seq_B_21_src(data)                                     ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_B_2_get_Seq_B_21(data)                                     ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_B_2_Seq_B_20_shift                                         (16)
#define DITHERING_2ND_SEQ_B_2_Seq_B_20_mask                                          (0x000F0000)
#define DITHERING_2ND_SEQ_B_2_Seq_B_20(data)                                         (0x000F0000&((data)<<16))
#define DITHERING_2ND_SEQ_B_2_Seq_B_20_src(data)                                     ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_B_2_get_Seq_B_20(data)                                     ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_B_2_Seq_B_19_shift                                         (12)
#define DITHERING_2ND_SEQ_B_2_Seq_B_19_mask                                          (0x0000F000)
#define DITHERING_2ND_SEQ_B_2_Seq_B_19(data)                                         (0x0000F000&((data)<<12))
#define DITHERING_2ND_SEQ_B_2_Seq_B_19_src(data)                                     ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_B_2_get_Seq_B_19(data)                                     ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_B_2_Seq_B_18_shift                                         (8)
#define DITHERING_2ND_SEQ_B_2_Seq_B_18_mask                                          (0x00000F00)
#define DITHERING_2ND_SEQ_B_2_Seq_B_18(data)                                         (0x00000F00&((data)<<8))
#define DITHERING_2ND_SEQ_B_2_Seq_B_18_src(data)                                     ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_B_2_get_Seq_B_18(data)                                     ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_B_2_Seq_B_17_shift                                         (4)
#define DITHERING_2ND_SEQ_B_2_Seq_B_17_mask                                          (0x000000F0)
#define DITHERING_2ND_SEQ_B_2_Seq_B_17(data)                                         (0x000000F0&((data)<<4))
#define DITHERING_2ND_SEQ_B_2_Seq_B_17_src(data)                                     ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_B_2_get_Seq_B_17(data)                                     ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_B_2_Seq_B_16_shift                                         (0)
#define DITHERING_2ND_SEQ_B_2_Seq_B_16_mask                                          (0x0000000F)
#define DITHERING_2ND_SEQ_B_2_Seq_B_16(data)                                         (0x0000000F&((data)<<0))
#define DITHERING_2ND_SEQ_B_2_Seq_B_16_src(data)                                     ((0x0000000F&(data))>>0)
#define DITHERING_2ND_SEQ_B_2_get_Seq_B_16(data)                                     ((0x0000000F&(data))>>0)


#define DITHERING_2ND_SEQ_B_3                                                        0x180099d8
#define DITHERING_2ND_SEQ_B_3_reg_addr                                               "0xB80099D8"
#define DITHERING_2ND_SEQ_B_3_reg                                                    0xB80099D8
#define set_DITHERING_2ND_SEQ_B_3_reg(data)   (*((volatile unsigned int*) DITHERING_2ND_SEQ_B_3_reg)=data)
#define get_DITHERING_2ND_SEQ_B_3_reg   (*((volatile unsigned int*) DITHERING_2ND_SEQ_B_3_reg))
#define DITHERING_2ND_SEQ_B_3_inst_adr                                               "0x0076"
#define DITHERING_2ND_SEQ_B_3_inst                                                   0x0076
#define DITHERING_2ND_SEQ_B_3_Seq_B_31_shift                                         (28)
#define DITHERING_2ND_SEQ_B_3_Seq_B_31_mask                                          (0xF0000000)
#define DITHERING_2ND_SEQ_B_3_Seq_B_31(data)                                         (0xF0000000&((data)<<28))
#define DITHERING_2ND_SEQ_B_3_Seq_B_31_src(data)                                     ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_B_3_get_Seq_B_31(data)                                     ((0xF0000000&(data))>>28)
#define DITHERING_2ND_SEQ_B_3_Seq_B_30_shift                                         (24)
#define DITHERING_2ND_SEQ_B_3_Seq_B_30_mask                                          (0x0F000000)
#define DITHERING_2ND_SEQ_B_3_Seq_B_30(data)                                         (0x0F000000&((data)<<24))
#define DITHERING_2ND_SEQ_B_3_Seq_B_30_src(data)                                     ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_B_3_get_Seq_B_30(data)                                     ((0x0F000000&(data))>>24)
#define DITHERING_2ND_SEQ_B_3_Seq_B_29_shift                                         (20)
#define DITHERING_2ND_SEQ_B_3_Seq_B_29_mask                                          (0x00F00000)
#define DITHERING_2ND_SEQ_B_3_Seq_B_29(data)                                         (0x00F00000&((data)<<20))
#define DITHERING_2ND_SEQ_B_3_Seq_B_29_src(data)                                     ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_B_3_get_Seq_B_29(data)                                     ((0x00F00000&(data))>>20)
#define DITHERING_2ND_SEQ_B_3_Seq_B_28_shift                                         (16)
#define DITHERING_2ND_SEQ_B_3_Seq_B_28_mask                                          (0x000F0000)
#define DITHERING_2ND_SEQ_B_3_Seq_B_28(data)                                         (0x000F0000&((data)<<16))
#define DITHERING_2ND_SEQ_B_3_Seq_B_28_src(data)                                     ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_B_3_get_Seq_B_28(data)                                     ((0x000F0000&(data))>>16)
#define DITHERING_2ND_SEQ_B_3_Seq_B_27_shift                                         (12)
#define DITHERING_2ND_SEQ_B_3_Seq_B_27_mask                                          (0x0000F000)
#define DITHERING_2ND_SEQ_B_3_Seq_B_27(data)                                         (0x0000F000&((data)<<12))
#define DITHERING_2ND_SEQ_B_3_Seq_B_27_src(data)                                     ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_B_3_get_Seq_B_27(data)                                     ((0x0000F000&(data))>>12)
#define DITHERING_2ND_SEQ_B_3_Seq_B_26_shift                                         (8)
#define DITHERING_2ND_SEQ_B_3_Seq_B_26_mask                                          (0x00000F00)
#define DITHERING_2ND_SEQ_B_3_Seq_B_26(data)                                         (0x00000F00&((data)<<8))
#define DITHERING_2ND_SEQ_B_3_Seq_B_26_src(data)                                     ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_B_3_get_Seq_B_26(data)                                     ((0x00000F00&(data))>>8)
#define DITHERING_2ND_SEQ_B_3_Seq_B_25_shift                                         (4)
#define DITHERING_2ND_SEQ_B_3_Seq_B_25_mask                                          (0x000000F0)
#define DITHERING_2ND_SEQ_B_3_Seq_B_25(data)                                         (0x000000F0&((data)<<4))
#define DITHERING_2ND_SEQ_B_3_Seq_B_25_src(data)                                     ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_B_3_get_Seq_B_25(data)                                     ((0x000000F0&(data))>>4)
#define DITHERING_2ND_SEQ_B_3_Seq_B_24_shift                                         (0)
#define DITHERING_2ND_SEQ_B_3_Seq_B_24_mask                                          (0x0000000F)
#define DITHERING_2ND_SEQ_B_3_Seq_B_24(data)                                         (0x0000000F&((data)<<0))
#define DITHERING_2ND_SEQ_B_3_Seq_B_24_src(data)                                     ((0x0000000F&(data))>>0)
#define DITHERING_2ND_SEQ_B_3_get_Seq_B_24(data)                                     ((0x0000000F&(data))>>0)


#endif
