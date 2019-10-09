//=================================================================================================
// Copyright (c) 2008 Realtek Semiconductor Corp. All Rights Reserved.
//
// Filename: SeReg.h
// Abstract:
//   Related Definitions of Register Set for Columbus Streaming Engine
//
// History:
//   2008-02-14         cyyang          Initial Version
//   2011-01-18         zack            Modify for Saturn
//=================================================================================================

#ifndef _SE_REG_H_
#define _SE_REG_H_

//=================================================================================================
#define SEREG_BASE_ADDRESS              	0xB800C000

//=================================================================================================
typedef union _SEREG_CMDBASE
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CMDBASE (0x1800_C000)
        uint32_t  Reserved0: 4;             //IO[3:0]: Reserved 
        uint32_t  base: 27;                 //IO[30:4]: Command ring buffer SDRAM base address, 16B alignment
        uint32_t  Reserved1: 1;             //IO[31:31]: Reserved    
        
    } Fields;
    
} SEREG_CMDBASE;

//=================================================================================================
typedef union _SEREG_CMDLMT
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CMDLMT (0x1800_C00C)
        uint32_t  Reserved0: 4;             //IO[3:0]: Reserved   
        uint32_t  limit: 27;                //IO[30:4]: Command ring buffer limit SDRAM address, 16B alignment
        uint32_t  Reserved1: 1;             //IO[31:31]: Reserved  
        
    } Fields;
    
} SEREG_CMDLMT;

//=================================================================================================
typedef union _SEREG_CMDRPTR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CMDRPTR (0x1800_C018)
        uint32_t  Reserved0: 4;             //IO[3:0]: Reserved 
        uint32_t  rptr: 27;                 //IO[30:4]: Command ring buffer read pointer, 16B alignment 
        uint32_t  Reserved1: 1;             //IO[31:31]: Reserved    
        
    } Fields;
    
} SEREG_CMDRPTR;

//=================================================================================================
typedef union _SEREG_CMDWPTR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CMDWPTR (0x1800_C024)  
        uint32_t  Reserved0: 4; 			      //IO[3:0]: Reserved 
        uint32_t  wptr: 27;                 //IO[30:4]: Command ring buffer write pointer, 16B alignment   
        uint32_t  Reserved1: 1;             //IO[31:31]: Reserved  
        
    } Fields;
    
} SEREG_CMDWPTR;

//=================================================================================================
typedef union _SEREG_SRWORDCNT
{
    uint32_t  Value;
    struct
    {    
                                            //Register: SRWORDCNT (0x1800_C030)
        uint32_t  srwordcnt: 7;             //IO[6:0]: Number of 4B word inside SE command FIFO SRAM. 
                                            //		   This is used for debugging only. 	

        uint32_t  Reserved: 25;             //IO[31:7]: Reserved    
        
    } Fields;
    
} SEREG_SRWORDCNT;

//=================================================================================================
typedef union _SEREG_Q_PRIORITY
{
    uint32_t  Value;
    struct
    {    
                                            //Register: Q_PRIORITY (0x1800_C03C)
        uint32_t  pri1: 2;                  //IO[1:0]: Priority number of command queue1.
        uint32_t  pri2: 2;                  //IO[3:2]: Priority number of command queue2.
        uint32_t  pri3: 2;                  //IO[5:4]: Priority number of command queue3.
        uint32_t  Reserved: 26;             //IO[31:6]: Reserved    
       
    } Fields;
    
} SEREG_Q_PRIORITY;

//=================================================================================================
typedef union _SEREG_CLR_FMT
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CLR_FMT (0x1800_C040)
        uint32_t  Format: 4;                //IO[3:0]: Format
                                            //		   - 4¡¦b0010: Index8
                                            //		   - 4¡¦b0100: RGB565
                                            //		   - 4¡¦b0101: ARGB1555
                                            //		   - 4¡¦b0110: ARGB4444
                                            //		   - 4¡¦b0111: ARGB8888
                                            //		   - 4¡¦b1000: Y (stretch and rotate command only)
                                            //		   - 4¡¦b1001: CbCr (stretch and rotate command only)
                                            //		   - 4¡¦b1010: YCbCr 420 (alpha only)
                                            //		   - 4¡¦b1011: YCbCr 422 (alpha only)
                                            //		   - 4¡¦b1111: RGB888
                                            //		   - else: reserved
                                   
        uint32_t  write_enable1: 1;         //IO[4]: Write enable for IO[3:0]

        uint32_t  alpha_loc: 1;             //IO[5]: Location of alpha pixel if the format is 8888, 4444, 1555 mode, this bit 
                                            //		 specifies whether the alpha pixel location is the leftmost (=0) or rightmost 
                                            //		 of a pixel

        uint32_t  write_enable2: 1;         //IO[6]: Write enable for IO[5]

        uint32_t  Reserved1: 6;             //IO[12:7]: Reserved

        uint32_t  alpha_loc2: 1;            //IO[13]: Specify the output alpha location in format conversion ARGB to ARGB mode

        uint32_t  write_enable5: 1;         //IO[14]: Write enable for IO[13]
	
        uint32_t  big_endian_i1: 1;         //IO[15]: SE works on big endian. If input color format is little endian, SE will swap data to big endian before operation
	
        uint32_t  write_enable6: 1;         //IO[16]: Write enable for IO[15]

        uint32_t  big_endian_i2: 1;         //IO[17]: Specify input color format for bitblit/alpha destination data (source data is specified by big_endian_i1)

        uint32_t  write_enable7: 1;         //IO[18]: Write enable for IO[17]

        uint32_t  big_endian_o: 1;          //IO[19]: Specify endian type for output color format. If output color format is little endian, SE will swap data to little endian after operation

        uint32_t  write_enable8: 1;         //IO[20]: Write enable for IO[19]

        uint32_t  rounding_en: 1;           //IO[21]: Rounding option for color format truncation (i.e. RGB888 to RGB565)
                                            //        - 0: disable rounding
                                            //        - 1: enable rounding

        uint32_t  write_enable10: 1;        //IO[22]: Write enable for IO[21]
        uint32_t  Reserved2: 9;             //IO[31:23]: Reserved    

    } Fields;
    
} SEREG_CLR_FMT;

//=================================================================================================
typedef union _SEREG_COLOR_KEY
{
    uint32_t  Value;
    struct
    {    
                                            //Register: COLOR_KEY (0x1800_C04C)
        uint32_t  color_key: 24;            //IO[23:0]: color key in variable color formats. 
                                            //          - Index2: use color_key[1:0] as color_key
                                            //          - Index4: use color_key[3:0] as color_key
                                            //          - Index8: use color_key[7:0] as color_key
                                            //          - RGB332: use color_key[7:0] as color_key
                                            //          - RGB565: use color_key[15:0] as color_key
                                            //          - ARGB1555: use color_key[14:0] as color_key
                                            //          - ARGB4444: use color_key[11:0] as color_key
                                            //          - ARGB8888: use color_key[23:0] as color_key

        uint32_t  Reserved: 8;              //IO[31:24]: Reserved    

    } Fields;
    
} SEREG_COLOR_KEY;

//=================================================================================================
typedef union _SEREG_DST_COLOR_KEY
{
    uint32_t  Value;
    struct
    {    
                                            //Register: DST_COLOR_KEY (0x1800_C54C)
        uint32_t  dst_color_key: 24;        //IO[23:0]: This destination color key is used for Bitblit with directFB only. 
                                            //            The color key in variable color formats. 
                                            //            RGB565: use color_key[15:0] as color_key
                                            //            ARGB8888: use color_key[23:0] as color_key
                                            //            
                                            //            [Note] In directFB, SW can enable source and destination 
                                            //                      color key simultaneously, so two color keys are needed 
                                            //                      in Bitblit instruction.
        uint32_t  Reserved: 8;              //IO[31:24]: Reserved    

    } Fields;
    
} SEREG_DST_COLOR_KEY;

//=================================================================================================
typedef union _SEREG_SRC_COLOR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: SRC_COLOR (0x1800_C058)
        uint32_t  src_color: 24;            //IO[23:0]: constant source color in variable color formats.
                                            //          - Index8: use src_color[7:0]
                                            //          - RGB565: use src_color[15:0]
                                            //          - RGB888: use src_color[23:0]
                                            //          - ARGB1555: use src_color[14:0]
                                            //          - ARGB4444: use src_color[11:0]
                                            //          - ARGB8888: use src_color[23:0]
                                            
        uint32_t  Reserved: 8;              //IO[31:24]: Reserved    

    } Fields;
    
} SEREG_SRC_COLOR;

//=================================================================================================
typedef union _SEREG_SRC_ALPHA
{
    uint32_t  Value;
    struct
    {    
                                            //Register: SRC_ALPHA (0x1800_C070)
        uint32_t  src_alpha: 8;             //IO[7:0]: constant source alpha; 
                                            //         if 4444, use the LSB [3:0]; if 1555, use the LSB [0]
                                            
        uint32_t  Reserved: 24;             //IO[31:8]: Reserved    

    } Fields;
    
} SEREG_SRC_ALPHA;

//=================================================================================================
typedef union _SEREG_DEST_ALPHA
{
    uint32_t  Value;
    struct
    {    
                                            //Register: DEST_ALPHA (0x1800_C07C)
        uint32_t  dest_alpha: 8;           	//IO[7:0]: constant dest alpha; used for dest-alpha calculation by select_dest_alpha; 
                                            //         if 4444, use the LSB [3:0]; if 1555, use the LSB [0]. 

        uint32_t  Reserved: 24;             //IO[31:8]: Reserved	  

    } Fields;
    
} SEREG_DEST_ALPHA;

//=================================================================================================
typedef union _SEREG_RSLT_ALPHA
{
    uint32_t  Value;
    struct
    {    
                                            //Register: RSLT_ALPHA (0x1800_C088)
        uint32_t  rslt_alpha: 8;            //IO[7:0]: constant result alpha, to overwrite the alpha results after operation. 
                                            //         if 4444, use the LSB [3:0]; if 1555, use the LSB [0].
                                            
        uint32_t  Reserved: 24;             //IO[31:8]: Reserved	  

    } Fields;
    
} SEREG_RSLT_ALPHA;

//=================================================================================================
typedef union _SEREG_BADDR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: BADDR1 (0x1800_C094)
        uint32_t  baddr: 31;                //IO[30:0]: Base address of a SE address set; 16B-align
        uint32_t  Reserved: 1;              //IO[31]: Reserved    

    } Fields;
    
} SEREG_BADDR;

//=================================================================================================
typedef union _SEREG_PITCH
{
    uint32_t  Value;
    struct
    {    
                                            //Register: PITCH1 (0x1800_C0A4)
        uint32_t  pitch: 16;                //IO[15:0]: Pitch of a SE address set, unit in byte. 0 means 16384 bytes. 16B-align.
        uint32_t  interleave: 1;            //IO[16]: interleaving mode for the picture index.
        uint32_t  Reserved: 15;             //IO[31:17]: Reserved    

    } Fields;
    
} SEREG_PITCH;

typedef struct _SEREG_DMAINFO
{
		SEREG_BADDR		SeRegBaseAddress[4];
		SEREG_PITCH		SeRegPitch[4];
	
} SEREG_DMAINFO;


//=================================================================================================
typedef union _SEREG_CLUT_LOCK_ST
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CLUT_LOCK_ST (0x1800_C4C8)
        uint32_t clut_lock_st: 2;           //IO[1:0]: Indicate which command queue has locked the CLUT Table
                                            //         - 00: lock by command queue0
                                            //         - 01: lock by command queue1
                                            //         - 10: lock by command queue2
                                            //         - 11: unlock
        uint32_t Reserved:30;               //IO[31:2]: Reserved
    } Fields;
} SEREG_CLUT_LOCK_ST;

//=================================================================================================
typedef union _SEREG_CLIP_XCOOR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CLIP_XCOOR1 (0x1800_C128)
        uint32_t  xmax: 12;                 //IO[11:0]: Max X coordinate for clipping; When YC422/420, 
                                            //          this value should be an odd number.

        uint32_t  xmin: 12;                 //IO[23:12]: Min X coordinate for clipping; When YC422/420, 
                                            //           this value should be an even number.
                                            
        uint32_t  clipen: 1;                //IO[24]: Enable clipping function
        	
        uint32_t  Reserved: 7;              //IO[31:25]: Reserved  

    } Fields;
    
} SEREG_CLIP_XCOOR;

//=================================================================================================
typedef union _SEREG_CLIP_YCOOR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CLIP_YCOOR1 (0x1800_C138)
        uint32_t  ymax: 12;                 //IO[11:0]: Max Y coordinate for clipping; When YC420, 
                                            //          this value should be an odd number.

        uint32_t  ymin: 12;                 //IO[23:12]: Min Y coordinate for clipping; When YC420, 
                                            //           this value should be an even number.
              	                                    
        uint32_t  Reserved: 8;              //IO[31:24]: Reserved  

    } Fields;
    
} SEREG_CLIP_YCOOR;

//=================================================================================================
typedef struct _SEREG_CLIP_INFO
{
    SEREG_CLIP_XCOOR	SeRegClipXCoor[4];
    SEREG_CLIP_YCOOR	SeRegClipYCoor[4];

} SEREG_CLIP_INFO;

//=================================================================================================
typedef union _SEREG_CONVSCALING
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CONVSCALING (0x1800_C188)
        uint32_t  vup: 1;                   //IO[0]: Vertical interpolation when 420 to 444
                                            //       - 0: repeat
                                            //       - 1: [1 1]/2

        uint32_t  hup: 1;                   //IO[1]: Horizontal interpolation when 422/420 to 444
                                            //       - 0: repeat
                                            //       - 1: [1 1]/2

        uint32_t  vdown: 1;                 //IO[2]: Vertical decimation when 444 to 420
                                            //       - 0: drop
                                            //       - 1: [1 1]/2

        uint32_t  hdown: 1;                 //IO[3]: Horizontal decimation when 444 to 422/420
                                            //       - 0: drop
                                            //       - 1: [1 1]/2

        uint32_t  Reserved: 28;             //IO[31:4]: Reserved  
     
    } Fields;
    
} SEREG_CONVSCALING;

//=================================================================================================
typedef union _SEREG_CONVCOEF1
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CONVCOEF1 (0x1800_C194)
        uint32_t  m00: 13;                  //IO[12:0]: Coefficient with format (sign,2,10)
        uint32_t  m01: 13;                  //IO[25:13]: Coefficient with format (sign,2,10)
        uint32_t  Reserved: 6;              //IO[31:26]: Reserved  

    } Fields;
    
} SEREG_CONVCOEF1;

//=================================================================================================
typedef union _SEREG_CONVCOEF2
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CONVCOEF2 (0x1800_C1A0)
        uint32_t  m02: 13;                  //IO[12:0]: Coefficient with format (sign,2,10)
        uint32_t  m10: 13;                  //IO[25:13]: Coefficient with format (sign,2,10) 
        uint32_t  Reserved: 6;              //IO[31:26]: Reserved  

    } Fields;
    
} SEREG_CONVCOEF2;

//=================================================================================================
typedef union _SEREG_CONVCOEF3
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CONVCOEF3 (0x1800_C1AC)
        uint32_t  m11: 13;                  //IO[11:0]: Coefficient with format (sign,2,10)
        uint32_t  m12: 13;                  //IO[23:12]: Coefficient with format (sign,2,10)
        uint32_t  Reserved: 6;              //IO[31:24]: Reserved  
         
        

    } Fields;
    
} SEREG_CONVCOEF3;

//=================================================================================================
typedef union _SEREG_CONVCOEF4
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CONVCOEF4 (0x1800_C1B8)
        uint32_t  m20: 13;                  //IO[11:0]: Coefficient with format (sign,2,10)
        uint32_t  m21: 13;                  //IO[23:12]: Coefficient with format (sign,2,10)
        uint32_t  Reserved: 6;              //IO[31:24]: Reserved  

    } Fields;
    
} SEREG_CONVCOEF4;

//=================================================================================================
typedef union _SEREG_CONVCOEF5
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CONVCOEF5 (0x1800_C1C4)
        uint32_t  m22: 13;                  //IO[12:0]: Coefficient with format (sign,2,10) 
        uint32_t  Reserved: 19;             //IO[31:13]: Reserved  

    } Fields;
    
} SEREG_CONVCOEF5;

//=================================================================================================
typedef union _SEREG_CONVCOEF6
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CONVCOEF1 (0x1800_C1D0)
        uint32_t  a0: 10;                   //IO[9:0]: Coefficient with format of (sign,9)
        uint32_t  a1: 10;                   //IO[10:19]: Coefficient with format of (sign,9)
        uint32_t  a2: 10;                   //IO[20:29]: Coefficient with format of (sign,9)
        uint32_t  Reserved: 2;              //IO[31:30]: Reserved  
  
    } Fields;
    
} SEREG_CONVCOEF6;

//=================================================================================================
typedef union _SEREG_FCV_BITBLIT_COLOR_KEY
{
    uint32_t  Value;
    struct
    {    
                                            //Register: FCV_BITBLIT_COLOR_KEY (0x1800_C4BC)
        uint32_t color_key: 24;             //IO[23:0]: For Bitblit instruction when ¿Format conversion + Bitblit?filed is set in the command
                                            //          - Index8: use src_color[7:0]
                                            //          - RGB565: use src_color[15:0]
                                            //          - RGB888: use src_color[23:0]
                                            //          - ARGB1555: use src_color[14:0]
                                            //          - ARGB4444: use src_color[11:0]
                                            //          - ARGB8888: use src_color[23:0]
        uint32_t Reserved: 8;               //IO[31:24]: Reserved

    } Fields;
} SEREG_FCV_BITBLIT_COLOR_KEY;

//=================================================================================================
typedef union _SEREG_SRC_CLR_RED
{
    uint32_t  Value;
    struct
    {    
                                            //Register: SRC_CLR_RED (0x1800_C51C)
        uint32_t  src_clr_mul_red: 9;       //IO[8:0]: Color multiplier coefficient of "R" component in format (0..256).
        uint32_t  Reserved: 7;              //IO[15:9]: Reserved
        uint32_t  src_clr_add_red: 9;       //IO[24:16]: Color offset coefficient of "R" component (-256 ~ 255)
        uint32_t  Reserved1: 7;             //IO[31:25]: Reserved
        
    } Fields;
    
} SEREG_SRC_CLR_RED; 

//=================================================================================================
typedef union _SEREG_SRC_CLR_GREEN
{
    uint32_t  Value;
    struct
    {    
                                            //Register: SRC_CLR_GREEN (0x1800_C528)
        uint32_t  src_clr_mul_green: 9;     //IO[8:0]: Color multiplier coefficient of "G" component in format (0..256).
        uint32_t  Reserved: 7;              //IO[15:9]: Reserved
        uint32_t  src_clr_add_green: 9;     //IO[24:16]: Color offset coefficient of "G" component (-256 ~ 255)
        uint32_t  Reserved1: 7;             //IO[31:25]: Reserved
        
    } Fields;
    
} SEREG_SRC_CLR_GREEN; 

//=================================================================================================
typedef union _SEREG_SRC_CLR_BLUE
{
    uint32_t  Value;
    struct
    {    
                                            //Register: SRC_CLR_BLUE (0x1800_C534)
        uint32_t  src_clr_mul_blue: 9;      //IO[8:0]: Color multiplier coefficient of "B" component in format (0..256).
        uint32_t  Reserved: 7;              //IO[15:9]: Reserved
        uint32_t  src_clr_add_blue: 9;      //IO[24:16]: Color offset coefficient of "B" component (-256 ~ 255)
        uint32_t  Reserved1: 7;             //IO[31:25]: Reserved
        
    } Fields;
    
} SEREG_SRC_CLR_BLUE; 

//=================================================================================================
typedef union _SEREG_SRC_CLR_ALPHA
{
    uint32_t  Value;
    struct
    {    
                                            //Register: SRC_CLR_ALPHA (0x1800_C540)
        uint32_t  src_clr_mul_alpha: 9;     //IO[8:0]: Color multiplier coefficient of "A" component in format (0..256).
        uint32_t  Reserved: 7;              //IO[15:9]: Reserved
        uint32_t  src_clr_add_alpha: 9;     //IO[24:16]: Color offset coefficient of "A" component (-256 ~ 255)
        uint32_t  Reserved1: 7;             //IO[31:25]: Reserved
        
    } Fields;
    
} SEREG_SRC_CLR_ALPHA; 

//=================================================================================================
typedef union _SEREG_SYNC_VO_MARGIN
{
    uint32_t  Value;
    struct
    {    
                                            //Register: SYNC_VO_MARGIN (0x1800_C4E0)
        uint32_t  margin_VOtoSE: 12;        //IO[11:0]: VO to SE margin.
        uint32_t  Reserved: 14;             //IO[25:12]: Reserved
        uint32_t  vo_osd_plane: 1;          //IO[26:26]: Which VO OSD plane to sync
        uint32_t  vbi: 1;                   //IO[27:27]: When sync_vo_en=1, allow bitblit during VBI period. 
        uint32_t  after_vo_cur: 1;          //IO[28:28]: Which VO OSD plane to sync
        uint32_t  before_vo_cur: 1;         //IO[29:29]: When sync_vo_en == 1, allow bitblit when the bitblit region is before the current VO current scan line.
        uint32_t  vo_plane: 1;              //IO[30:30]: Which VO plane to sync(0: OSD, 1: SUB)
        uint32_t  auto_dir_en: 1;           //IO[31:31]: 
                                            //    1: enable HW to calculate the bitblit direction automatically based on input X &Y and output X & Y.
                                            //    0: SW needs to set the direction in bitblit command.
        
    } Fields;
    
} SEREG_SYNC_VO_MARGIN; 

//=================================================================================================
typedef union _SEREG_SYNC_VO_LOCATION
{
    uint32_t  Value;
    struct
    {    
                                            //Register: SYNC_VO_LOCATION (0x1800_C4F8)
        uint32_t  VO_current_y: 12;         //IO[11:0]: VO current y location.
        uint32_t  Reserved: 20;             //IO[31:12]: Reserved
        
    } Fields;
    
} SEREG_SYNC_VO_LOCATION;

//=================================================================================================
typedef union _SEREG_STRETCH
{
    uint32_t  Value;
    struct
    {    
                                            //Register: STRETCH (0x1800_C1DC)
        uint32_t  vodd: 1;                  //IO[0]: This bit is only used when apply FIR algorithm.
                                            //       - 1: Using odd type FIR for V-scaling. 
                                            //       - 0: Using even type FIR for V-scaling.
        
        uint32_t  hodd: 1;                  //IO[1]: This bit is only used when apply FIR algorithm.
                                            //       - 1: Using odd type FIR for H-scaling. 
                                            //       - 0: Using even type FIR for H-scaling. 

        uint32_t  vtype: 1;                 //IO[2]: vtype
                                            //       - 0: 2-tap FIR 
                                            //       - 1: 4-tap FIR

        uint32_t  htype: 2;                 //IO[4:3]: htype
                                            //         - 00: 2-tap FIR 
                                            //         - 01: 4-tap FIR
                                            //         - 10: 8-tap FIR

        uint32_t  ref_alpha: 1;             //IO[5]: Reference alpha option for transparency function

        uint32_t  Reserved: 26;             //IO[31:6]: Reserved  

    } Fields;
    
} SEREG_STRETCH;

//=================================================================================================
typedef union _SEREG_HDHS
{
    uint32_t  Value;
    struct
    {    
                                            //Register: HDHS (0x1800_C1E8)
        uint32_t  H_scaling_dph_lsb: 14;    //IO[13:0]: LSB of the H-scaling delta-phase in (4,14) format
        uint32_t  H_scaling_dph_msb: 4;     //IO[17:14]: MSB of the H-scaling delta-phase in (4,14) format
        uint32_t  H_scaling_iniph: 4;       //IO[21:18]: Initial phase of Y coordinate for H-scaling
        uint32_t  Reserved: 10;             //IO[31:22]: Reserved  

    } Fields;
    
} SEREG_HDHS;

//=================================================================================================
typedef union _SEREG_VDHS
{
    uint32_t  Value;
    struct
    {    
                                            //Register: VDHS (0x1800_C1F4)
        uint32_t  V_scaling_dph_lsb: 14;    //IO[13:0]: LSB of the V-scaling delta-phase in (4,14) format
        uint32_t  V_scaling_dph_msb: 4;     //IO[17:14]: MSB of the V-scaling delta-phase in (4,14) format
        uint32_t  V_scaling_iniph: 4;       //IO[21:18]: Initial phase of Y coordinate for V-scaling
        uint32_t  Reserved: 10;             //IO[31:22]: Reserved  
   
    } Fields;
    
} SEREG_VDHS;

//=================================================================================================
typedef union _SEREG_HCOEF
{
    uint32_t  Value;
    struct
    {    
                                            //Register: HCOEF1 (0x1800_C200)
        uint32_t  hcoef: 14;                //IO[13:0]: Coefficient in (sign, 1, 12) format (2¡¦s complement)
        uint32_t  Reserved: 18;             //IO[31:14]: Reserved  

    } Fields;
    
} SEREG_HCOEF;

//=================================================================================================
typedef union _SEREG_VCOEF
{
    uint32_t  Value;
    struct
    {    
                                            //Register: VCOEF1 (0x1800_C280)
        uint32_t  vcoef: 14;                //IO[13:0]: Coefficient in (sign, 1, 12) format (2¡¦s complement)
        uint32_t  Reserved: 18;             //IO[31:14]: Reserved  

    } Fields;
    
} SEREG_VCOEF;

typedef struct _SEREG_COEFINFO
{
    SEREG_HCOEF		SeRegHCoef[32];
    SEREG_VCOEF		SeRegVCoef[16];
	
} SEREG_COEFINFO;

//=================================================================================================
typedef union _SEREG_HCOEF_32
{
    uint32_t  Value;
    struct
    {    
                                            //Register: HCOEF1_32 (0x1800_C558)
        uint32_t  hcoef: 14;                //IO[13:0]: Coefficient in (sign, 1, 12) format (2¡¦s complement)
        uint32_t  Reserved: 18;             //IO[31:14]: Reserved  

    } Fields;
    
} SEREG_HCOEF_32;

//=================================================================================================
typedef union _SEREG_VCOEF_16
{
    uint32_t  Value;
    struct
    {    
                                            //Register: VCOEF1_16 (0x1800_C5D8)
        uint32_t  vcoef: 14;                //IO[13:0]: Coefficient in (sign, 1, 12) format (2¡¦s complement)
        uint32_t  Reserved: 18;             //IO[31:14]: Reserved  

    } Fields;
    
} SEREG_VCOEF_16;

typedef struct _SEREG_COEFINFO_2
{
    SEREG_HCOEF_32 SeRegHCoef[32];
    SEREG_VCOEF_16 SeRegVCoef[16];
	
} SEREG_COEFINFO_2;

//=================================================================================================
typedef union _SEREG_SC_BITBLIT_COLOR_KEY
{
    uint32_t  Value;
    struct
    {    
                                            //Register: SC_BITBLIT_COLOR_KEY (0x1800_C4EC)
		uint32_t color_key: 24;                 //IO[23:0]: For Bitblit instruction when ¿Format conversion + Bitblit?filed is set in the command
                                            //          - Index8: use src_color[7:0]
                                            //          - RGB565: use src_color[15:0]
                                            //          - RGB888: use src_color[23:0]
                                            //          - ARGB1555: use src_color[14:0]
                                            //          - ARGB4444: use src_color[11:0]
                                            //          - ARGB8888: use src_color[23:0]
		uint32_t Reserved: 8;                   //IO[31:24]: Reserved

	} Fields;
} SEREG_SC_BITBLIT_COLOR_KEY;

//=================================================================================================
typedef union _SEREG_CTRL
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CTRL (0x1800_C458)
        uint32_t  write_data: 1;            //IO[0]: write_data
        
        uint32_t  go: 1;                    //IO[1]: SE operation of the command queue can only start when go = 1. 
                                            //       Once it starts the command queue will only stop when this bit is 
                                            //       set to 0 and when it completes the current instruction
        
        uint32_t  endiswap: 1;              //IO[2]: When this bit is == 1, the command endianness will be swapped. 
                                            //       It will change the byte order to {cmd[7:0],cmd[15:8], cmd[23:16], cmd[31:24]}
                                            	
        uint32_t  Reserved: 29;             //IO[31:3]: Reserved  

    } Fields;
    
} SEREG_CTRL;

//=================================================================================================
typedef union _SEREG_IDLE
{
    uint32_t  Value;
    struct
    {    
                                            //Register: IDLE (0x1800_C464)
        uint32_t  idle: 1;                  //IO[0]: indicate the command queue of SE is idle (all instruction has been 
                                            //       executed and in both the internal and external command list, or when 
                                            //       go bit = 0 and the command queue of SE is stopped.

        uint32_t  Reserved: 31;             //IO[31:1]: Reserved  
                                      
    } Fields;
    
} SEREG_IDLE;

//=================================================================================================
typedef union _SEREG_INTSEL
{
    uint32_t  Value;
    struct
    {    
                                            //Register: INTSEL (0x1800_C470)
        uint32_t  Sel1: 1;                  //IO[0]: Select which CPU to interrupt for command queue 1: 
                                            //       - 0: SCPU
                                            //       - 1: VCPU 

        uint32_t  Sel2: 1;                  //IO[1]: Select which CPU to interrupt for command queue 2: 
                                            //       - 0: SCPU
                                            //       - 1: VCPU

        uint32_t  Sel3: 1;                  //IO[2]: Select which CPU to interrupt for command queue 3: 
                                            //       - 0: SCPU
                                            //       - 1: VCPU

        uint32_t  Reserved: 29;             //IO[31:3]: Reserved  
                                
    } Fields;
    
} SEREG_INTSEL;

//=================================================================================================
typedef union _SEREG_INTS
{
    uint32_t  Value;
    struct
    {    
                                            //Register: INTS (0x1800_C474)
        uint32_t  write_data: 1;            //IO[0]: write_data
        uint32_t  sync: 1;                  //IO[1]: Interrupt enable of sync interrupt 	
        uint32_t  com_err: 1;               //IO[2]: Interrupt enable of command decoding error. The command will be ignored.
        uint32_t  com_empty: 1;             //IO[3]: Interrupt enable. SDRAM and internal command lists both empty, 
                                            //       and the execution of all commands is done.
                                            //       object is decompressed.
        uint32_t  Reserved1: 12;          	//IO[15:4]: Reserved
        uint32_t  fmt_err: 1;               //IO[16]: Interrupt for unsupported color format
        uint32_t  vo_sync_err: 1;           //IO[17]: Interrupt for vo_sync_en error when none of the vo_sync mode is selected. The command will be ignored
        uint32_t  Reserved2: 14;            //IO[31:18]: Reserved  
	
    } Fields;   
                
} SEREG_INTS;   

//=================================================================================================
typedef union _SEREG_INTE
{
    uint32_t  Value;
    struct
    {    
                                            //Register: INTE (0x1800_C480)
        uint32_t  write_data: 1;            //IO[0]: write_data
        uint32_t  sync: 1;                  //IO[1]: Interrupt enable of sync interrupt 
        uint32_t  com_err: 1;               //IO[2]: Interrupt enable of command decoding error. The command will be ignored.
        uint32_t  com_empty: 1;             //IO[3]: Interrupt enable. SDRAM and internal command lists both empty, 
                                            //       and the execution of all commands is done.
        uint32_t  Reserved1: 12;            //IO[15:4]: Reserved
        uint32_t  fmt_err: 1;               //IO[16]: Interrupt for unsupported color format
        uint32_t  vo_sync_err: 1;           //IO[17]: Interrupt for vo_sync_en error when none of the vo_sync mode is selected. The command will be ignored
        uint32_t  Reserved: 14;             //IO[31:18]: Reserved  
                                             
    } Fields;   
                
} SEREG_INTE; 
 
//=================================================================================================
typedef union _SEREG_INSTCNT_L
{
    uint32_t  Value;
    struct
    {    
                                            //Register: INSTCNT_L (0x1800_C48C)
        uint32_t instcnt_l;                 //IO[31:0]: number of commands encountered(lower 4 bytes).  This field will increment by 1 
                                            //          whenever an command is completed execution. It will wrap to 0 after 32¡¦hffffffff.
        
                                    
    } Fields;
    
} SEREG_INSTCNT_L; 

//=================================================================================================
typedef union _SEREG_INSTCNT_H
{
    uint32_t  Value;
    struct
    {    
                                            //Register: INSTCNT_H (0x1800_C510)
        uint32_t instcnt_h;                 //IO[31:0]: number of commands encountered(lower 4 bytes).  This field will increment by 1 
                                            //          whenever an command is completed execution. It will wrap to 0 after 32¡¦hffffffff.
        
                                    
    } Fields;
    
} SEREG_INSTCNT_H; 

//=================================================================================================
typedef union _SEREG_CLUT_RADR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CLUT_RADR (0x1800_C498)
        uint32_t  radr: 8;                  //IO[7:0]: CLUT SRAM read address. 
        uint32_t  Reserved: 24;             //IO[31:8]: Reserved  
                                  
    } Fields;
    
} SEREG_CLUT_RADR; 
 
//=================================================================================================
typedef union _SEREG_CLUT_VALUE
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CLUT_VALUE (0x1800_C49C)
        uint32_t  value;                    //IO[31:0]: The 32b content inside the CLUT SRAM addressed by SE_CLUT_RADR.
        
    } Fields;
    
} SEREG_CLUT_VALUE;  

//=================================================================================================
typedef union _SEREG_DBG
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CLUT_RADR (0x1800_C4A0)
        uint32_t  dbg_sel0: 5;              //IO[4:0]: Select debug signal sets to be probed via se_dbg_out0
        uint32_t  Reserved1: 3;             //IO[7:5]: Reserved
        uint32_t  dbg_sel1: 5;              //IO[12:8]: Select debug signal sets to be probed via se_dbg_out1
        uint32_t  Reserved2: 3;             //IO[15:13]: Reserved
        uint32_t  dbg_module_sel0:4;        //IO[19:16]: Select module to be probed via se_dbg_out0
                                            //           - 4¿b0000: se_clut
                                            //           - 4¿b0001: se_cmd_queue
                                            //           - 4¿b0010: se_dbsctl
                                            //           - 4¿b0011: se_dma
                                            //           - 4¿b0100: se_globalctl
                                            //           - 4¿b0101: se_op
                                            //           - 4¿b0110: se_regif
                                            //           - 4¿b0111: se_regwrap

        uint32_t  dbg_module_sel1:4;        //IO[23:20]: Select module to be probed via se_dbg_out1
                                            //           - 4¿b0000: se_clut
                                            //           - 4¿b0001: se_cmd_queue
                                            //           - 4¿b0010: se_dbsctl
                                            //           - 4¿b0011: se_dma
                                            //           - 4¿b0100: se_globalctl
                                            //           - 4¿b0101: se_op
                                            //           - 4¿b0110: se_regif
                                            //           - 4¿b0111: se_regwrap

        uint32_t  dbg_en: 1;                //IO[24]: Debug enable
                                            //        When set, selected signals can be probed via debug ports. When clear, both se_dbg_out0 and se_dbg_out1 are static 16¿h0

        uint32_t  Reserved3: 7;             //IO[31:25]: Reserved  
                   
    } Fields;
    
} SEREG_DBG; 

//=================================================================================================
typedef union _SEREG_SCTCH
{
    uint32_t  Value;
    struct
    {    
                                            //Register: SCTCH (0x1800_C4A4)
        uint32_t  Reg0: 16;                 //IO[15:0]: Dummy registers with default value 0 
        uint32_t  Reg1: 16;                 //IO[31:16]: Dummy registers with default value 1
              
    } Fields;
    
} SEREG_SCTCH; 

//=================================================================================================
typedef union _SEREG_GCRA_CTRL
{
    uint32_t  Value;
    struct
    {    
                                            //Register: GCRA_CTRL (0x1800_C4A8)
        uint32_t  Gcra_en: 1;               //IO[0]: SE request GCRA algorithm enable
        uint32_t  Reserved: 31;             //IO[31:1]: Reserved
                    
    } Fields;
    
} SEREG_GCRA_CTRL; 

//=================================================================================================
typedef union _SEREG_GCRA_REQ_CNT
{
    uint32_t  Value;
    struct
    {    
                                            //Register: GCRA_REQ_CNT (0x1800_C4AC)
        uint32_t  Gcra_req_num: 24;         //IO[23:0]: Request number for current period.
        uint32_t  Reserved: 8;              //IO[31:24]: Reserved
                        
    } Fields;
    
} SEREG_GCRA_REQ_CNT; 

//=================================================================================================
typedef union _SEREG_GCRA_TIM_CNT
{
    uint32_t  Value;
    struct
    {    
                                            //Register: GCRA_TIM_CNT (0x1800_C4B0)
        uint32_t  Gcra_tim_cnt;             //IO[31:0]: Timer counter
                        
    } Fields;
    
} SEREG_GCRA_TIM_CNT; 

//=================================================================================================
typedef union _SEREG_GCRA_TIM_THR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: GCRA_TIM_THR (0x1800_C4B4)
        uint32_t  Gcra_tim_thr;             //IO[31:0]: Timer counter threshold. When timer reach this threshold, 
                                            //          HW will clear timer counter and request number
                        
    } Fields;
    
} SEREG_GCRA_TIM_THR; 

//=================================================================================================
typedef union _SEREG_GCRA_REQ_THR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: GCRA_REQ_THR (0x1800_C4B8)
        uint32_t  Gcra_req_thr: 24;         //IO[23:0]: Request number threshold. When SE request number reach this 
                                            //          threshold, HW will stop to access.
        uint32_t  Reserved: 8;              //IO[31:24]: Reserved
                       
    } Fields;
    
} SEREG_GCRA_REQ_THR; 

//=================================================================================================
typedef struct _SEREG_INFO
{               
    SEREG_CMDBASE               SeCmdBase[3];            //0x1800_C000: Register: CMDBASE
    SEREG_CMDLMT                SeCmdLimit[3];           //0x1800_C00C: Register: SEREG_CMDLMT
    SEREG_CMDRPTR               SeCmdReadPtr[3];         //0x1800_C018: Register: CMDRPTR
    SEREG_CMDWPTR               SeCmdWritePtr[3];        //0x1800_C024: Register: CMDWPTR
    SEREG_SRWORDCNT             SeSramWordCount[3];      //0x1800_C030: Register: SRWORDCNT
    SEREG_Q_PRIORITY            SeQueuePriority;         //0x1800_C03C: Register: Q_PRIORITY
    
    SEREG_CLR_FMT               SeColorFormat[3];        //0x1800_C040: Register: CLR_FMT
    SEREG_COLOR_KEY             SeColorKey[3];           //0x1800_C04C: Register: COLOR_KEY
    SEREG_SRC_COLOR             SeSrcColor[3];           //0x1800_C058: Register: SRC_COLOR
    uint32_t                    Reserved00[3];           //0x1800_C064: Reserved on Saturn
    SEREG_SRC_ALPHA             SeSrcAlpha[3];           //0x1800_C070: Register: SRC_ALPHA
    SEREG_DEST_ALPHA            SeDestAlpha[3];          //0x1800_C07C: Register: DEST_ALPHA
    SEREG_RSLT_ALPHA            SeResultAlpha[3];        //0x1800_C088: Register: RSLT_ALPHA
    
    SEREG_DMAINFO               SeDmaInfo[3];            //0x1800_C094
    uint32_t                    Reserved01[13];          //0x1800_C0F4: Reserved on Saturn

    SEREG_CLIP_INFO        	    SeClipInfo[3];           //0x1800_C128 - 0x1800_C184

    SEREG_CONVSCALING           SeConvScaling[3];        //0x1800_C188: Register: CONVSCALING
    SEREG_CONVCOEF1             SeConvCoef1[3];          //0x1800_C194: Register: CONVCOEF1
    SEREG_CONVCOEF2             SeConvCoef2[3];          //0x1800_C1A0: Register: CONVCOEF2
    SEREG_CONVCOEF3             SeConvCoef3[3];          //0x1800_C1AC: Register: CONVCOEF3
    SEREG_CONVCOEF4             SeConvCoef4[3];          //0x1800_C1B8: Register: CONVCOEF4
    SEREG_CONVCOEF5             SeConvCoef5[3];          //0x1800_C1C4: Register: CONVCOEF5
    SEREG_CONVCOEF6             SeConvCoef6[3];          //0x1800_C1D0: Register: CONVCOEF6

    SEREG_STRETCH               SeStretch[3];            //0x1800_C1DC: Register: STRETCH
    SEREG_HDHS                  SeHdhs[3];               //0x1800_C1E8: Register: HDHS
    SEREG_VDHS                  SeVdhs[3];               //0x1800_C1F4: Register: VDHS
    SEREG_COEFINFO              SeCoefInfo[3];           //0x1800_C200 - 0x1800_C43C

    uint32_t                    Reserved02[6];           //0x1800_C440: Reserved On Saturn
    
    SEREG_CTRL                  SeCtrl[3];               //0x1800_C458: Register: CTRL
    SEREG_IDLE                  SeIdle[3];               //0x1800_C464: Register: IDLE

    SEREG_INTSEL                SeIntSel;                //0x1800_C470: Register: INTSEL
    SEREG_INTS                  SeInts[3];               //0x1800_C474: Register: INTS
    SEREG_INTE                  SeInte[3];               //0x1800_C480: Register: INTE
    SEREG_INSTCNT_L             SeInstCntL[3];           //0x1800_C48C: Register: INSTCNT

    SEREG_CLUT_RADR             SeClutReadAddress;       //0x1800_C498: Register: CLUT_RADR
    SEREG_CLUT_VALUE            SeClutValue;             //0x1800_C49C: Register: CLUT_VALUE
    SEREG_DBG                   SeDebug;                 //0x1800_C4A0: Register: DBG
    SEREG_SCTCH                 SeSctch;                 //0x1800_C4A4: Register: SCTCH  
    
    SEREG_GCRA_CTRL             SeGcraCtrl;              //0x1800_C4A8: Register: GCRA_CTRL
    SEREG_GCRA_REQ_CNT          SeGcraReqCnt;            //0x1800_C4AC: Register: GCRA_REQ_CNT
    SEREG_GCRA_TIM_CNT          SeGcraTimCnt;            //0x1800_C4B0: Register: GCRA_TIM_CNT
    SEREG_GCRA_TIM_THR          SeGcraTimThr;            //0x1800_C4B4: Register: GCRA_TIM_THR
    SEREG_GCRA_REQ_THR          SeGcraReqThr;            //0x1800_C4B8: Register: GCRA_REQ_THR

    SEREG_FCV_BITBLIT_COLOR_KEY SeFcvBitblitColorKey[3]; //0x1800_C4BC: Register: FCV_BITBLIT_COLOR_KEY
    SEREG_CLUT_LOCK_ST          SeClutLockSt;            //0x1800_C4C8: Register: CLUT_LOCK_ST
    uint32_t                    Reserved03[5];           //0x1800_C4CC: Reserved on Saturn

    SEREG_SYNC_VO_MARGIN        SeSyncVoMargin[3];       //0x1800_C4E0: Register: SYNC_VO_MARGIN
    SEREG_SC_BITBLIT_COLOR_KEY  SeScBitblitColorKey[3];  //0x1800_C4EC: Register: SC_BITBLIT_COLOR_KEY
    SEREG_SYNC_VO_LOCATION      SeSyncVoLocation[3];     //0x1800_C4F8: Register: SYNC_VO_LOCATION
    uint32_t                    Reserved04[3];           //0x1800_C504: Reserved on Saturn

    SEREG_INSTCNT_H             SeInstCntH[3];           //0x1800_C510: Register: INSTCNT_H    
    SEREG_SRC_CLR_RED           SeSrcClrRed[3];          //0x1800_C51C: Register: SRC_CLR_RED
    SEREG_SRC_CLR_GREEN         SeSrcClrGreen[3];        //0x1800_C528: Register: SRC_CLR_GREEN
    SEREG_SRC_CLR_BLUE          SeSrcClrBlue[3];         //0x1800_C534: Register: SRC_CLR_BLUE
    SEREG_SRC_CLR_ALPHA         SeSrcClrAlpha[3];        //0x1800_C540: Register: SRC_CLR_ALPHA
    SEREG_DST_COLOR_KEY         SeDstColorKey[3];        //0x1800_C54C: Register: DST_COLOR_KEY

    SEREG_COEFINFO_2            SeCoefInfo2[3];          //0x1800_C558
} SEREG_INFO;

//=================================================================================================

#endif

//=================================================================================================
// End of File
