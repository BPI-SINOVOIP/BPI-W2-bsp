
/*=============================================================
 * Copyright C        Realtek Semiconductor Corporation, 2006 *
 * All rights reserved.                                       *
 *============================================================*/

/*======================= Description ========================*/
/**
 * @file
 *   This header file for Dragon's defines.
 * @Author Temin Kuo
 * @date 2006/10/12
 * @version { 1.0 }
 *
 */

/*======================= CVS Headers =========================
  $Header: $

  $Log: $
 *=============================================================*/

#ifndef _DRAGON_VERIFY_H

#define _DRAGON_VERIFY_H

#define CONFIG_SYS_202000

#ifdef CONFIG_SYS_189000
#undef CPU_CLOCK
#define CPU_CLOCK       (189000*1000)
#endif

#ifdef CONFIG_SYS_202000
#undef CPU_CLOCK
#define CPU_CLOCK       (202000*1000)
#endif


#ifndef CPU_CLOCK
#define CPU_CLOCK		(27000*1000)
#endif

#define BIT(x)	(1 << (x))

#define rtd_inb(offset)		(*(volatile unsigned char *)( offset))
#define rtd_inw(offset)	(*(volatile unsigned short *)(offset))
#define rtd_inl(offset)		(*(volatile unsigned long *)(offset))

#define rtd_outb(offset,val)	(*(volatile unsigned char *)(offset) = val)
#define rtd_outw(offset,val)	(*(volatile unsigned short *)(offset) = val)
#define rtd_outl(offset,val)		(*(volatile unsigned long *)(offset) = val)

#ifndef MAX
#define MAX(x,y)		((x)>(y)?(x):(y))
#endif
#ifndef ALIGNED
#define ALIGNED(addr, size)	(((addr)+(size)-1)  & ~((size)-1))
#endif

/// ****************************

//For Memory Controller

///////////////////////////////////////////////////////
//
// Memory Mapping Area
//
///////////////////////////////////////////////////////
#define MMA_CODE_PHY_START 	(0x1000)		///< Physical address for verifier code/data, just for info.
#define MMA_STACK_PHY_START 	(0x100000)	///< Physical address for verifier stack

/// Audio delay buffers
#define MMA_AUDIO_PHY_START	MMA_STACK_PHY_START
#define MMA_AUDIO_SIZE			(3820*4*8)	///< 3820 samples * 4 Byte/sample * 8 channels
#define MMA_AUDIO_PHY_END		(MMA_AUDIO_PHY_START+MMA_AUDIO_SIZE)

/// Video Decoder 3D-mode field buffers
#define MMA_VDC_NTSC_SIZE		((((910*525*2-256*64*4)*10/8)+4) & (~3))		///< Word-aligned
#define MMA_VDC_PAL_SIZE		((((1135*625*2-256*64*4)*10/8)+4) & (~3))	///< Word-aligned, 0x19CF7D

#define MMA_VDC_PHY_START		MMA_AUDIO_PHY_END	
#define MMA_VDC_SIZE			MMA_VDC_PAL_SIZE
#define MMA_VDC_PHY_END		(MMA_VDC_PHY_START+MMA_VDC_SIZE)

#define DDR_ROW_SIZE                    (2*512*4*2)             ///< 16-bit DDR, 9/8 bit column address, 4 banks

/// Cross Color, De-interlace, Noise_Reduction field buffers
#define MMA_XCDINR_PHY_START	  MMA_VDC_PHY_END
#define MMA_XCDINR_3A_SIZE	  (1920*(1080/2)*2*2) ///< each pixel with 2 bytes, 2 field buffes, 0x7E9000
#define MMA_XCDINR_5A_SIZE	  (720*(576/2)*2*4) ///< each pixel with 2 bytes, 4 field buffes, 0x195000
#define MMA_XCDINR_SIZE		  MAX(MMA_XCDINR_3A_SIZE, MMA_XCDINR_5A_SIZE)
#define MMA_XCDINR_FIELD_SIZE     ((1920*(1080/2)*20)/8) ///each pixel is 20 bits  
#define MMA_XCDINR_ADDR1_PHY_ADDR ALIGNED(MMA_XCDINR_PHY_START, DDR_ROW_SIZE)
#define MMA_XCDINR_ADDR1_PHY_END  (MMA_XCDINR_ADDR1_PHY_ADDR+MMA_XCDINR_FIELD_SIZE)
#define MMA_XCDINR_ADDR2_PHY_ADDR ALIGNED(MMA_XCDINR_ADDR1_PHY_END, DDR_ROW_SIZE)
#define MMA_XCDINR_ADDR2_PHY_END  (MMA_XCDINR_ADDR2_PHY_ADDR+MMA_XCDINR_FIELD_SIZE)
#define MMA_XCDINR_ADDR3_PHY_ADDR ALIGNED(MMA_XCDINR_ADDR2_PHY_END, DDR_ROW_SIZE)
#define MMA_XCDINR_ADDR3_PHY_END  (MMA_XCDINR_ADDR3_PHY_ADDR+MMA_XCDINR_FIELD_SIZE)
#define MMA_XCDINR_ADDR4_PHY_ADDR ALIGNED(MMA_XCDINR_ADDR3_PHY_END, DDR_ROW_SIZE)
#define MMA_XCDINR_ADDR4_PHY_END  (MMA_XCDINR_ADDR4_PHY_ADDR+MMA_XCDINR_FIELD_SIZE)

#define MMA_XCDINR_ADDR1_3D_PHY_ADDR ALIGNED(MMA_XCDINR_ADDR4_PHY_END, DDR_ROW_SIZE)
#define MMA_XCDINR_ADDR1_3D_PHY_END  (MMA_XCDINR_ADDR1_3D_PHY_ADDR+MMA_XCDINR_FIELD_SIZE)
#define MMA_XCDINR_ADDR2_3D_PHY_ADDR ALIGNED(MMA_XCDINR_ADDR1_3D_PHY_END, DDR_ROW_SIZE)
#define MMA_XCDINR_ADDR2_3D_PHY_END  (MMA_XCDINR_ADDR2_3D_PHY_ADDR+MMA_XCDINR_FIELD_SIZE)
#define MMA_XCDINR_ADDR3_3D_PHY_ADDR ALIGNED(MMA_XCDINR_ADDR2_3D_PHY_END, DDR_ROW_SIZE)
#define MMA_XCDINR_ADDR3_3D_PHY_END  (MMA_XCDINR_ADDR3_3D_PHY_ADDR+MMA_XCDINR_FIELD_SIZE)
#define MMA_XCDINR_ADDR4_3D_PHY_ADDR ALIGNED(MMA_XCDINR_ADDR3_3D_PHY_END, DDR_ROW_SIZE)
#define MMA_XCDINR_ADDR4_3D_PHY_END  (MMA_XCDINR_ADDR4_3D_PHY_ADDR+MMA_XCDINR_FIELD_SIZE)


//#define MMA_XCDINR_PHY_END	(MMA_XCDINR_PHY_START+MMA_XCDINR_SIZE)
#define MMA_XCDINR_PHY_END    (MMA_XCDINR_ADDR4_3D_PHY_END)

/// Disp2 FRC buffers, double buffer ( 2 blocks)
//#define MMA_FRC2B1_PHY_ADDR		ALIGNED(MMA_XCDINR_PHY_END, DDR_ROW_SIZE)	///< Physical address for frame rate conversion
#define MMA_FRC2B1_PHY_ADDR		ALIGNED((MMA_FRC1B1_PHY_START+0x40000000), DDR_ROW_SIZE)
//#define MMA_FRC2B1_SIZE			(1366*768*2)	///< each pixel with 16bits, 0xCA8000
#define MMA_FRC2B1_SIZE                 (1920*1080*2)    ///< each pixel with 16bits, 0xCA8000
#define MMA_FRC2B1_PHY_END		(MMA_FRC2B1_PHY_ADDR+MMA_FRC2B1_SIZE)
#define MMA_FRC2B2_PHY_ADDR		ALIGNED(MMA_FRC2B1_PHY_END, DDR_ROW_SIZE)
#define MMA_FRC2B2_SIZE			MMA_FRC2B1_SIZE
#define MMA_FRC2B2_PHY_END		(MMA_FRC2B2_PHY_ADDR+MMA_FRC2B2_SIZE)
#define MMA_FRC2B3_PHY_ADDR		ALIGNED(MMA_FRC2B2_PHY_END, DDR_ROW_SIZE)
#define MMA_FRC2B3_SIZE			MMA_FRC2B1_SIZE
#define MMA_FRC2B3_PHY_END		(MMA_FRC2B3_PHY_ADDR+MMA_FRC2B3_SIZE)

/// Disp1 FRC buffer shall not be used.  Use frame sync for bandwidth concern
//#define MMA_FRC1B1_PHY_START	ALIGNED(MMA_FRC2B3_PHY_END, DDR_ROW_SIZE)///< Physical address for frame rate conversion
#define MMA_FRC1B1_PHY_START	ALIGNED(0x4000000, DDR_ROW_SIZE)
//#define MMA_FRC1B1_SIZE		(720*610*2)
#define MMA_FRC1B1_SIZE		(1920*1080*2)  
#define MMA_FRC1B1_PHY_END	(MMA_FRC1B1_PHY_START+MMA_FRC1B1_SIZE)
#define MMA_FRC1B2_PHY_ADDR	ALIGNED(MMA_FRC1B1_PHY_END, DDR_ROW_SIZE)
#define MMA_FRC1B2_SIZE		MMA_FRC1B1_SIZE
#define MMA_FRC1B2_PHY_END	(MMA_FRC1B2_PHY_ADDR+MMA_FRC1B2_SIZE)
#define MMA_FRC1B3_PHY_ADDR	ALIGNED(MMA_FRC1B2_PHY_END, DDR_ROW_SIZE)
#define MMA_FRC1B3_SIZE		MMA_FRC1B1_SIZE
#define MMA_FRC1B3_PHY_END	(MMA_FRC1B3_PHY_ADDR+MMA_FRC1B3_SIZE)




/// Disp1 FRC buffer shall not be used.  Use frame sync for bandwidth concern
#define MMA_3DDMAB1_PHY_LADDR	ALIGNED(MMA_FRC1B3_PHY_END, DDR_ROW_SIZE)///< Physical address for frame rate conversion
#define MMA_3DDMAB1_SIZE	(1920*1080*4)	///< each pixel with 30bits, 
#define MMA_3DDMAB1_PHY_LEND	(MMA_3DDMAB1_PHY_LADDR+MMA_3DDMAB1_SIZE)
#define MMA_3DDMAB2_PHY_LADDR	ALIGNED(MMA_3DDMAB1_PHY_LEND, DDR_ROW_SIZE)
#define MMA_3DDMAB2_SIZE	MMA_3DDMAB1_SIZE
#define MMA_3DDMAB2_PHY_LEND	(MMA_3DDMAB2_PHY_LADDR+MMA_3DDMAB2_SIZE)

/// Disp1 FRC buffer shall not be used.  Use frame sync for bandwidth concern
#define MMA_3DDMAB1_PHY_RADDR	ALIGNED(MMA_3DDMAB2_PHY_LEND, DDR_ROW_SIZE)///< Physical address for frame rate conversion
#define MMA_3DDMAB1_SIZE	(1920*1080*4)	///< each pixel with 30bits, 
#define MMA_3DDMAB1_PHY_REND	(MMA_3DDMAB1_PHY_RADDR+MMA_3DDMAB1_SIZE)
#define MMA_3DDMAB2_PHY_RADDR	ALIGNED(MMA_3DDMAB1_PHY_REND, DDR_ROW_SIZE)
#define MMA_3DDMAB2_SIZE	MMA_3DDMAB1_SIZE
#define MMA_3DDMAB2_PHY_REND	(MMA_3DDMAB2_PHY_RADDR+MMA_3DDMAB2_SIZE)


#endif //_DRAGON_VERIFY_H
