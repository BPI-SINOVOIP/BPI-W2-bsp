/************************************************************************
 *
 *  ctype.h
 *
 *  Definitions for control characters
 *
 * ######################################################################
 *
 * mips_start_of_legal_notice
 * 
 * Copyright (c) 2003 MIPS Technologies, Inc. All rights reserved.
 *
 *
 * Unpublished rights (if any) reserved under the copyright laws of the
 * United States of America and other countries.
 *
 * This code is proprietary to MIPS Technologies, Inc. ("MIPS
 * Technologies"). Any copying, reproducing, modifying or use of this code
 * (in whole or in part) that is not expressly permitted in writing by MIPS
 * Technologies or an authorized third party is strictly prohibited. At a
 * minimum, this code is protected under unfair competition and copyright
 * laws. Violations thereof may result in criminal penalties and fines.
 *
 * MIPS Technologies reserves the right to change this code to improve
 * function, design or otherwise. MIPS Technologies does not assume any
 * liability arising out of the application or use of this code, or of any
 * error or omission in such code. Any warranties, whether express,
 * statutory, implied or otherwise, including but not limited to the implied
 * warranties of merchantability or fitness for a particular purpose, are
 * excluded. Except as expressly provided in any written license agreement
 * from MIPS Technologies or an authorized third party, the furnishing of
 * this code does not give recipient any license to any intellectual
 * property rights, including any patent rights, that cover this code.
 *
 * This code shall not be exported or transferred for the purpose of
 * reexporting in violation of any U.S. or non-U.S. regulation, treaty,
 * Executive Order, law, statute, amendment or supplement thereto.
 *
 * This code constitutes one or more of the following: commercial computer
 * software, commercial computer software documentation or other commercial
 * items. If the user of this code, or any related documentation of any
 * kind, including related technical data or manuals, is an agency,
 * department, or other entity of the United States government
 * ("Government"), the use, duplication, reproduction, release,
 * modification, disclosure, or transfer of this code, or any related
 * documentation of any kind, is restricted in accordance with Federal
 * Acquisition Regulation 12.212 for civilian agencies and Defense Federal
 * Acquisition Regulation Supplement 227.7202 for military agencies. The use
 * of this code by the Government is further restricted in accordance with
 * the terms of the license agreement(s) and/or applicable contract terms
 * and conditions covering this code from MIPS Technologies or an authorized
 * third party.
 *
 * 
 * mips_end_of_legal_notice
 * 
 *
 ************************************************************************/

#ifndef	_CTYPE_
#define	_CTYPE_		1

#define _UPC	0x1
#define _LWR	0x2
#define _DIG	0x4
#define _SPC	0x8
#define _PUN	0x10
#define _CTR	0x20
#define _HEX	0x40
#define _BLK	0x80

extern	char	_ctype[];

#define	isalpha(c)	((_ctype)[(unsigned char)(c)]&(_UPC|_LWR))
#define	isupper(c)	((_ctype)[(unsigned char)(c)]&_UPC)
#define	islower(c)	((_ctype)[(unsigned char)(c)]&_LWR)
#define	isdigit(c)	((_ctype)[(unsigned char)(c)]&_DIG)
#define	isxdigit(c)	((_ctype)[(unsigned char)(c)]&(_DIG|_HEX))
#define	isspace(c)	((_ctype)[(unsigned char)(c)]&_SPC)
#define ispunct(c)	((_ctype)[(unsigned char)(c)]&_PUN)
#define isalnum(c)	((_ctype)[(unsigned char)(c)]&(_UPC|_LWR|_DIG))
#define isprint(c)	((_ctype)[(unsigned char)(c)]&(_PUN|_UPC|_LWR|_DIG|_BLK))
#define isgraph(c)	((_ctype)[(unsigned char)(c)]&(_PUN|_UPC|_LWR|_DIG))
#define iscntrl(c)	((_ctype)[(unsigned char)(c)]&_CTL)
#define isascii(c)	((unsigned)(c)<=0x7f)
extern int toupper(int);
extern int tolower(int);
#define toascii(c)	((unsigned char)(c)&0x7f)

#endif	/* _CTYPE_ */
