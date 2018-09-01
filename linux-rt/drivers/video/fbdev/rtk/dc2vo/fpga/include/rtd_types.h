/*=============================================================
 * Copyright (c)      Realtek Semiconductor Corporation, 2004 *
 * All rights reserved.                                       *
 *============================================================*/
/*======================= Description ========================*/
/**
  * @file 
 * We define the usual types in this file.
 * We define the usual types in this file such as INT8,uin8,etc.
 * Please include this file in all source file. And declare your
 * variables with this re-defined type.
 * @Author Moya Yu
 * @date  2004/4/7
 * @version 1.0
 */

/*======================= CVS Headers =========================
  $Header: /cvsroot/dtv/include/rtd_types.h,v 1.20 2004/10/29 07:46:14 tzungder Exp $
  
  $Log: rtd_types.h,v $
  Revision 1.20  2004/10/29 07:46:14  tzungder
  +add #ifdef _WIN32 for models which compiled by VC on windows platform

  Revision 1.19  2004/10/27 08:52:26  waynelee
  +: <waynelee> FLOAT32, FLOAT64

  Revision 1.18  2004/10/27 03:20:01  tzungder
  refine rtd_types.h definitions and apply to all

  Revision 1.17  2004/10/26 14:22:57  waynelee
  -: remove bool define

  Revision 1.16  2004/10/26 12:52:04  ljshuenn
  *: <ljshuenn> Remove the definition for BOOL because it is definited in
  previous.

  Revision 1.15  2004/10/26 12:37:15  ljshuenn
  +: <ljshuenn> Add the definition for Boolean declaration

  Revision 1.14  2004/08/11 06:26:05  ghyu
  	Add definition of memaddr.

  Revision 1.13  2004/08/09 05:38:08  ghyu
  	Redefine _SIZE_T

  Revision 1.12  2004/08/09 04:24:54  tzungder
  add defines for NIC

  Revision 1.11  2004/08/05 08:11:41  ghyu
  	Loader code includes real header file here.

  Revision 1.10  2004/07/13 03:31:59  ghyu
  add flash control module

  Revision 1.9  2004/07/09 10:23:22  ghyu

    add drTPcontrol Module

  Revision 1.8  2004/06/18 07:14:26  ghyu
  Doc Tree Refine.

  Revision 1.7  2004/06/10 10:44:18  ghyu
  rearrange doc's architecture

  Revision 1.6  2004/06/09 12:37:19  ghyu
  add some file for models document

  Revision 1.5  2004/06/09 02:22:45  herman
  Add Audio Interface API

  Revision 1.4  2004/06/08 03:26:57  tzungder
  move ir.h, scd.h to peripheral moudule

  Revision 1.3  2004/05/07 09:03:09  ghyu
  add i2c & uart APIs

  Revision 1.2  2004/04/22 03:23:54  swchen
  Add MVD Functions

  Revision 1.1  2004/04/12 09:22:01  ghyu
  add rtd_types.h

  Revision 1.2  2004/04/06 10:58:36  waynelee
  +add ds defgroup and describes it

  Revision 1.1.1.1  2004/04/01 03:25:11  ghyu
  DTV Project Start
  
 *=============================================================*/


#ifndef _RTD_TYPES_H
#define _RTD_TYPES_H

/*
 * Internal names for basic integral types.  Omit the typedef if
 * not possible for a machine/compiler combination.
 */
#ifdef _WIN32 //for platform-acrossing of models, _WIN32: the pre-defined keyword of VC compiler
typedef 	unsigned __int64         UINT64; //!<for unsigned 64 bits integer in VC windows platform
typedef  __int64				INT64;//!<for signed 64 bits integer in VC windows platform
#else
typedef unsigned long long		UINT64; //!< for unsigned 64 bits integer
typedef long long				INT64;     //!< for signed 64 bits integer
#endif
typedef unsigned int			UINT32;   //!< for unsigned integer (32 bits)
typedef int					INT32;    //!< for signed integer (32 bits)
typedef unsigned short			UINT16;  //!< for unsigned short (16 bits)
typedef short					INT16;    //!< for signed short (16 bits)
typedef unsigned char			UINT8;   //!< for unsigned character (8 bits)
typedef char					INT8;    //!< for character (8 bits)
//typedef int BOOL;  //!< for boolean value
typedef float					FLOAT32;	//!< for float point (32 bits)
typedef double				FLOAT64;	//!< for float point (64 bits)

typedef unsigned int size_t;

#ifndef bool
//typedef unsigned char	bool ;	//!< For Boolean declaration
typedef enum{FALSE = 0, TRUE} bool;
#endif

#ifndef BOOL
#define BOOL bool
#endif

#ifndef NULL
#define NULL (void *)0
#endif
/*
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
*/
#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAILED
#define FAILED -1
#endif

#define CLEARBITS(a,b)	((a) &= ~(b))
#define SETBITS(a,b)		((a) |= (b))
#define ISSET(a,b)		(((a) & (b))!=0)
#define ISCLEARED(a,b)	(((a) & (b))==0)


#ifndef MAX
#define MAX(a,b)  (((a) > (b)) ? (a) : (b))
#endif			   /* max */

#ifndef MIN
#define MIN(a,b)  (((a) < (b)) ? (a) : (b))
#endif			   /* min */

#define ASSERT_CSP(x) if (!(x)) {printk("\nAssertion fail at file %s, function %s, line number %d:, expression '%s'", __FILE__, __FUNCTION__, __LINE__, #x); while(1);}
#define ASSERT_ISR(x) if (!(x)) {printk("\nAssertion fail at file %s, function %s, line number %d:, expression '%s'", __FILE__, __FUNCTION__, __LINE__, #x); while(1);}



#endif
