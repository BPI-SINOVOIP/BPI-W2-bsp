//=================================================================================================
// Copyright (c) 2008 Realtek Mdmiconductor Corp. All Rights Reserved.
//
// Filename: MdReg.h
// Abstract:
//   Related Definitions of Register Mdt for Columbus Streaming Engine
//
// History:
//   2008-02-14         cyyang          Initial Version
//=================================================================================================

#ifndef _MD_REG_H_
#define _MD_REG_H_

//=================================================================================================
#define MDREG_BASE_ADDRESS              	0xB800B000

//=================================================================================================
typedef union _MDREG_CTRL
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CTRL (0x1800_B000)
        uint32_t  write_data: 1;            //IO[0]: write_data
        
        uint32_t  go: 1;                    //IO[1]: MD operation of the command queue can only start when go = 1. 
                                            //       Once it starts the command queue will only stop when this bit is 
                                            //       set to 0 and when it completes the current instruction
        
        uint32_t  endiswap: 1;              //IO[2]: When this bit is == 1, the command endianness will be swapped. 
                                            //       It will change the byte order to {cmd[7:0],cmd[15:8], cmd[23:16], cmd[31:24]}
                                            	
        uint32_t  idle: 1;

        uint32_t  Reserved: 28;             //IO[31:4]: Reserved  

    } Fields;
    
} MDREG_CTRL;

//=================================================================================================
typedef union _MDREG_INTS
{
    uint32_t  Value;
    struct
    {    
        uint32_t  write_data: 1;
        uint32_t  smq_inst_err: 1;
        uint32_t  smq_length_err: 1;
        uint32_t  smq_empty: 1;
        uint32_t  fdma_done: 1;
        uint32_t  smq_mode_2b4b_err: 1;
        uint32_t  ur_tx_thd: 1;
        uint32_t  ur_rx_thd: 1;
        uint32_t  ur_rx_timeout: 1;
        uint32_t  ur_length_err: 1;
        uint32_t  smq_chksum_err: 1;
        uint32_t  gsp_tx_thd_ints: 1;
        uint32_t  gsp_txbasic_thd_ints: 1;
        uint32_t  gsp_txdat_thd_ints: 1;
        uint32_t  gsp_rx_thd_ints: 1;
        uint32_t  gsp_length_err: 1;
		uint32_t  Reserved: 16;             //IO[31:16]: Reserved  
    } Fields;   
                
} MDREG_INTS;   

//=================================================================================================
typedef union _MDREG_INTE
{
    uint32_t  Value;
    struct
    {    
		uint32_t  write_data: 1;
		uint32_t  smq_inst_err_en: 1;
		uint32_t  smq_length_err_en: 1;
		uint32_t  smq_empty_en: 1;
		uint32_t  fdma_done_en: 1;
		uint32_t  smq_mode_2b4b_err_en: 1;
		uint32_t  ur_tx_thd_en: 1;
    uint32_t  ur_rx_thd_en: 1;
    uint32_t  ur_rx_timeout_en: 1;
    uint32_t  ur_length_err_en: 1;
    uint32_t  smq_chksum_err_en: 1;
    uint32_t  gsp_tx_thd_en: 1;
    uint32_t  gsp_txbasic_thd_en: 1;
    uint32_t  gsp_txdat_thd_en: 1;
    uint32_t  gsp_rx_thd_en: 1;
    uint32_t  gsp_length_err_en: 1;
		uint32_t  scpu_int_en: 1;
		uint32_t  Reserved: 15;
                                             
    } Fields;   
                
} MDREG_INTE; 
 
//=================================================================================================
typedef union _MDREG_CMDBASE
{
    uint32_t  Value;
    struct
    {    
											//Register: CMDBASE (0x1800_B00C)
		uint32_t  Reserved0: 4; 			//IO[3:0]: Reserved 
        uint32_t  base: 25;                 //IO[27:4]: Command ring buffer SDRAM base address, 16B alignment
        uint32_t  Reserved1: 3;             //IO[31:28]: Reserved    
        
    } Fields;
    
} MDREG_CMDBASE;

//=================================================================================================
typedef union _MDREG_CMDLMT
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CMDLMT (0x1800_B010)
		uint32_t  Reserved0: 4;             //IO[3:0]: Reserved   
        uint32_t  limit: 25;                //IO[27:4]: Command ring buffer limit SDRAM address, 16B alignment
        uint32_t  Reserved1: 3;             //IO[31:28]: Reserved  
        
    } Fields;
    
} MDREG_CMDLMT;

//=================================================================================================
typedef union _MDREG_CMDRPTR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CMDRPTR (0x1800_B014)
		uint32_t  Reserved0: 4;             //IO[3:0]: Reserved 
        uint32_t  rptr: 25;                 //IO[27:4]: Command ring buffer read pointer, 16B alignment 
        uint32_t  Reserved1: 3;             //IO[31:28]: Reserved    
        
    } Fields;
    
} MDREG_CMDRPTR;

//=================================================================================================
typedef union _MDREG_CMDWPTR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CMDWPTR (0x1800_B018)  
		uint32_t  Reserved0: 4; 			//IO[3:0]: Reserved 
        uint32_t  wptr: 25;                 //IO[27:4]: Command ring buffer write pointer, 16B alignment   
        uint32_t  Reserved1: 3;             //IO[31:28]: Reserved  
        
    } Fields;
    
} MDREG_CMDWPTR;

//=================================================================================================
typedef union _MDREG_FIFOSTATE
{
    uint32_t  Value;
    struct
    {    
        uint32_t  smq_inst_remain: 5;
        uint32_t  Reserved: 27;
    } Fields;
    
} MDREG_FIFOSTATE; 

//=================================================================================================
typedef union _MDREG_INSTCNT
{
    uint32_t  Value;
    struct
    {    
                                            //Register: INSTCNT (0x1800_B020)
        uint32_t  instcnt: 16;              //IO[15:0]: number of commands encountered.  This field will increment by 1 
                                            //          whenever an command is completed execution. It will wrap to 0 after 16¡¦hffff.
        
        uint32_t  Reserved: 16;             //IO[31:16]: Reserved  
                                    
    } Fields;
    
} MDREG_INSTCNT; 

//=================================================================================================
typedef struct _MDREG_INFO
{               
    MDREG_CTRL              MdCtrl[1];              //0x1800_B000: Register: CTRL
    MDREG_INTS              MdInts[1];              //0x1800_B004: Register: INTS
    MDREG_INTE              MdInte[1];              //0x1800_B008: Register: INTE
    MDREG_CMDBASE           MdCmdBase[1];           //0x1800_B00C: Register: CMDBASE
    MDREG_CMDLMT            MdCmdLimit[1];          //0x1800_B010: Register: MDREG_CMDLMT
    MDREG_CMDRPTR           MdCmdReadPtr[1];        //0x1800_B014: Register: CMDRPTR
    MDREG_CMDWPTR           MdCmdWritePtr[1];       //0x1800_B018: Register: CMDWPTR
    MDREG_FIFOSTATE         MdFifoState[1];         //0x1800_B01C: Register: FIFOSTATE
    MDREG_INSTCNT           MdInstCnt[1];           //0x1800_B020: Register: INSTCNT
} MDREG_INFO;

//=================================================================================================

#endif

//=================================================================================================
// End of File
