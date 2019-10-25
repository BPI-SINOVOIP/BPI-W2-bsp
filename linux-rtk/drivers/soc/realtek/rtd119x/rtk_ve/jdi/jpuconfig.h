//------------------------------------------------------------------------------
// File: jpuconfig.h
//
// Copyright (c) 2006, Chips & Media.  All rights reserved.
// This file should be modified by some customers according to their SOC configuration.
//------------------------------------------------------------------------------

#ifndef _JPU_CONFIG_H_
#define _JPU_CONFIG_H_

//#include "../config.h"
//#include "jputypes.h"

#define MAX_NUM_INSTANCE				8
#define MAX_INST_HANDLE_SIZE	        (12*1024)

#define JPU_FRAME_ENDIAN			JDI_LITTLE_ENDIAN
#define JPU_STREAM_ENDIAN			JDI_LITTLE_ENDIAN

#define	JPU_CHROMA_INTERLEAVE			1		// 0 (chroma separate mode), 1 (chroma interleave mode) 


#define JPU_INTERRUPT_TIMEOUT_MS	5000

#define	JPU_STUFFING_BYTE_FF   		0		// 0 : ON ("0xFF"), 1 : OFF ("0x00") for stuffing

#define	JPU_PARTIAL_DECODE			1		// 0 : OFF, 1 : ON

#define MAX_MJPG_PIC_WIDTH   32768
#define MAX_MJPG_PIC_HEIGHT  32768


#define MAX_FRAME				(19*MAX_NUM_INSTANCE) // For AVC decoder, 16(reference) + 2(current) + 1(rotator)

#define STREAM_FILL_SIZE		0x10000
#define STREAM_END_SIZE			0

#define JPU_GBU_SIZE			512

#define	STREAM_BUF_SIZE			0x200000

#define JPU_CHECK_WRITE_RESPONSE_BVALID_SIGNAL 0


#endif	/* _JPU_CONFIG_H_ */
