/*
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
 *++
 * File: ArchDefs.h
 *
 * Description:
 *	Architecture definitions
 *
 * Compile Options:
 *	MIPSAVPENV  selects the special MIPS AVP environment
 *
 * Notes:
 *
 * ArchDefs.h: 1.126
 */

#ifndef _ArchDefs_h_
#define _ArchDefs_h_

/*
 * Define __ASSEMBLER__ if a different tool specific define indicating
 * the an assembly language file is being processed is set.  This allows
 * support for new tools to be added in one place (here).  The remainder
 * of ArchDefs.h simply uses __ASSEMBLER__ to separate assembly specific
 * code from C or C++ code.
 */
#if defined(MIPSAVPENV) || defined(__LANGUAGE_ASM__) || defined(__assembler)
#undef __ASSEMBLER__
#define __ASSEMBLER__
#endif

/*
 * Utility defines for cross platform handling of 64bit constants.
 */

#if defined(__ASSEMBLER__)
    #undef UINT64_C
    #undef INT64_C

    #define UINT64_C(c) c
    #define INT64_C(c) c
#endif /* defined(__ASSEMBLER__) */


/*
 ************************************************************************
 *                I N S T R U C T I O N   F O R M A T S                 *
 ************************************************************************
 *
 * The following definitions describe each field in an instruction.  There
 * is one diagram for each type of instruction, with field definitions
 * following the diagram for that instruction.  Note that if a field of
 * the same name and position is defined in an earlier diagram, it is
 * not defined again in the subsequent diagram.  Only new fields are
 * defined for each diagram.
 *
 * R-Type (operate)
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |           |   rs    |   rt    |   rd    |   sa    |           |
 * |   Opcode  |         |         |       Tcode       |   func    |
 * |           |                  Bcode                |           |
 * |           |       |s|                   |h|       |s|         |
 * |           |       |r|                   |b| hint  |c|   | sel |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define S_InstnOpcode		26
#define M_InstnOpcode		(0x3f << S_InstnOpcode)
#define S_InstnRS		21
#define M_InstnRS		(0x1f << S_InstnRS)
#define S_InstnRT		16
#define M_InstnRT		(0x1f << S_InstnRT)
#define S_InstnRD		11
#define M_InstnRD		(0x1f << S_InstnRD)
#define S_InstnSA		6
#define M_InstnSA		(0x1f << S_InstnSA)
#define S_InstnTcode		6
#define M_InstnTcode		(0x3ff << S_InstnTcode)
#define S_InstnBcode		6
#define M_InstnBcode		(0xfffff << S_InstnBcode)
#define S_InstnFunc		0
#define M_InstnFunc		(0x3f << S_InstnFunc)
#define S_InstnSel		0
#define M_InstnSel		(0x7 << S_InstnSel)

/* to distinguish release2 DI/EI */
#define S_InstnSC		5
#define M_InstnSC		(0x1 << S_InstnSC)

/* to distinguish release2 shift/rotate */
#define S_InstnSR		21
#define M_InstnSR		(0x1 << S_InstnSR)

/* to distinguish release2 jump with hazard barrier */
#define S_InstnHB		10
#define M_InstnHB		(0x1 << S_InstnHB)

/*
 * I-Type (load, store, branch, immediate)
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Opcode  |   rs    |   rt    |             Offset            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define S_InstnOffset		0
#define M_InstnOffset		(0xffff << S_InstnOffset)

/*
 * I-Type (pref)
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Opcode  |   rs    |  hint   |             Offset            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define S_InstnHint		S_InstnRT
#define M_InstnHint		M_InstnRT

/*
 * J-Type (jump)
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Opcode  |                    JIndex                         |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define S_InstnJIndex		0
#define M_InstnJIndex		(0x03ffffff << S_InstnJIndex)

/*
 * FP R-Type (operate)
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Opcode  |   fmt   |   ft    |   fs    |   fd    |   func    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define S_InstnFmt		S_InstnRS
#define M_InstnFmt		M_InstnRS
#define S_InstnFT		S_InstnRT
#define M_InstnFT		M_InstnRT
#define S_InstnFS		S_InstnRD
#define M_InstnFS		M_InstnRD
#define S_InstnFD		S_InstnSA
#define M_InstnFD		M_InstnSA

/*
 * FP R-Type (cpu <-> cpu data movement))
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Opcode  |   sub   |   rt    |   fs    |          0          |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define S_InstnSub		S_InstnRS
#define M_InstnSub		M_InstnRS

/*
 * FP R-Type (compare)
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |           |         |         |         |     | |C|           |
 * |   Opcode  |   fmt   |   ft    |   fs    |  cc |0|A|   func    |
 * |           |         |         |         |     | |B|           |
 * |           |         |         |         |     | |S|           |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define S_InstnCCcmp		8
#define M_InstnCCcmp		(0x7 << S_InstnCCcmp)
#define S_InstnCABS		6
#define M_InstnCABS		(0x1 << S_InstnCABS)

/*
 * FP R-Type (FPR conditional move on FP cc)
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Opcode  |   fmt   |  cc |n|t|   fs    |   fd    |   func    |
 * |           |         |     |d|f|         |         |           |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define S_InstnCC		18
#define M_InstnCC		(0x7 << S_InstnCC)
#define S_InstnND		17
#define M_InstnND		(0x1 << S_InstnND)
#define S_InstnTF		16
#define M_InstnTF		(0x1 << S_InstnTF)

/*
 * FP R-Type (3-operand operate)
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Opcode  |   fr    |   ft    |   fs    |   fd    | op4 | fmt3|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define S_InstnFR		S_InstnRS
#define M_InstnFR		M_InstnRS
#define S_InstnOp4		3
#define M_InstnOp4		(0x7 << S_InstnOp4)
#define S_InstnFmt3		0
#define M_InstnFmt3		(0x7 << S_InstnFmt3)

/*
 * FP R-Type (Indexed load, store)
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Opcode  |   rs    |   rt    |   0     |   fd    |   func    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
/*
 * FP R-Type (prefx)
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Opcode  |   rs    |   rt    |  hint   |    0    |   func    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define S_InstnHintX		S_InstnRD
#define M_InstnHintX		M_InstnRD

/*
 * FP R-Type (GPR conditional move on FP cc)
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Opcode  |    rs   |  cc |n|t|   rd    |    0    |   func    |
 * |           |         |     |d|f|         |         |           |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

/*
 * FP I-Type (load, store)
 * 
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Opcode  |   rs    |    ft   |           Offset              |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

/*
 * FP I-Type (branch)
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Opcode  |   fmt   |  cc |n|t|           Offset              |
 * |           |         |     |d|f|                               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */


/*
 * Vector Type
 *
 * bit[25:21]  This field is mostly format select (fmtsel), or combind
 *             with operation select for shuffle, read/write accumulator,
 *             or fourth register (rs) for variable alignment, or
 *             immediate for constant alignment.
 * bit[10]     L bit is only used for VMac instructions.
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Opcode  |  fmtsel |   vt    |   vs    |   vd    |   func    |
 * |           |  fmt/op |         |         |         |           |
 * |           |   rs    |         |         |         |           |
 * |           | 0 | imm |         |         |L|       |           |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define S_InstnVT		S_InstnRT
#define M_InstnVT		M_InstnRT
#define S_InstnVS		S_InstnRD
#define M_InstnVS		M_InstnRD
#define S_InstnVD		S_InstnSA
#define M_InstnVD		M_InstnSA

#define S_InstnFmtsel		S_InstnFmt
#define M_InstnFmtsel		(0x1 << S_InstnFmtsel)
#define S_InstnVImm		S_InstnFmt
#define M_InstnVImm		(0x7 << S_InstnVImm)

#define S_InstnL		10
#define M_InstnL		(0x1 << S_InstnL)



/*
 ************************************************************************
 *      M I P S 1 6  I N S T R U C T I O N   F O R M A T S              *
 ************************************************************************
 */

/*
 * MIPS16 I Type (operate)
 *
 *  1 1 1 1 1 1
 *  5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Opcode |      Immediate      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define S_M16_InstnOpcode	11
#define M_M16_InstnOpcode	(0x1f << S_M16_InstnOpcode)
#define S_M16_InstnOffset	0
#define M_M16_InstnOffset	(0x7ff << S_M16_InstnOffset)

/*
 * MIPS16 RI Type
 *
 *  1 1 1 1 1 1
 *  5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Opcode | rx  |  Immediate    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define	S_M16_InstnRX		8
#define	M_M16_InstnRX		(0x7 << S_M16_InstnRX)
#define S_M16_InstnOffset7	0
#define M_M16_InstnOffset7	(0xff << S_M16_InstnOffset7)

/*
 * MIPS16 Breakpoint Type
 *
 *  1 1 1 1 1 1
 *  5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Opcode |   code    |  func   |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define S_M16_InstnBPcode	5
#define M_M16_InstnBPcode	(0x3f << S_M16_InstnBPcode)

/*
 * MIPS16 RR Type
 *
 *  1 1 1 1 1 1
 *  5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Opcode | rx  | ry  |  func   |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
/*
 * MIPS16 RRI Type
 *
 *  1 1 1 1 1 1
 *  5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Opcode | rx  | ry  |Immediate|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define	S_M16_InstnRY		5
#define	M_M16_InstnRY		(0x7  << S_M16_InstnRY)
#define S_M16_InstnFunc		0
#define M_M16_InstnFunc		(0x1f << S_M16_InstnFunc)

/*
 * MIPS16 RRR Type
 *
 *  1 1 1 1 1 1
 *  5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Opcode | rx  | ry  | rz  | f |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

/*
 * MIPS16 Shift1 Type
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Extend | sa[4:0] |5|    0    |  Opcode | rx  | ry  | sa  | f |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define S_M16_InstnExtendSA4    22
#define M_M16_InstnExtendSA4    (0x1f << S_M16_InstnExtendSA4)
#define S_M16_InstnExtendSA5    21
#define M_M16_InstnExtendSA5    (0x1 << S_M16_InstnExtendSA5)
#define	S_M16_InstnShiftF	0
#define	M_M16_InstnShiftF	(0x3 << S_M16_InstnShiftF)
#define	S_M16_InstnRZ		2
#define	M_M16_InstnRZ		(0x7 << S_M16_InstnRZ)
#define	S_M16_InstnSA		2
#define	M_M16_InstnSA		(0x7 << S_M16_InstnSA)

/*
 * MIPS16 EXTEND
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Extend |  [10:5]   | [15:11] |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define S_M16_InstnExtendOffset15       16
#define M_M16_InstnExtendOffset15	(0x1f << S_M16_InstnExtendOffset15)
#define S_M16_InstnExtendOffset10	21
#define M_M16_InstnExtendOffset10	(0x3f << S_M16_InstnExtendOffset10)

/*
 * MIPS16 RRI-A Type
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Extend |    [10:4]   |[14:11]|  Opcode | rx  | ry  |f| immed |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

 */

#define	S_M16_InstnF		        4
#define	M_M16_InstnF		        (0x1 << S_M16_InstnF)
#define S_M16_InstnOffset3	        0
#define M_M16_InstnOffset3	        (0xf << S_M16_InstnOffset3)
#define S_M16_InstnExtendOffset14       16
#define M_M16_InstnExtendOffset14       (0xf << S_M16_InstnExtendOffset14)
#define S_M16_InstnExtendOffset10_4     20
#define M_M16_InstnExtendOffset10_4     (0x7f << S_M16_InstnExtendOffset10_4)


/*
 * MIPS16 JALX
 *
 *  3 3 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Opcode |x| [20:16] | [25:21] |         target[15:0]          |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define S_M16_InstnX		26
#define M_M16_InstnX		(0x1 << S_M16_InstnX)
#define S_M16_InstnTarget2	21
#define M_M16_InstnTarget2	(0x1f << S_M16_InstnTarget2)
#define S_M16_InstnTarget1	16
#define M_M16_InstnTarget1	(0x1f << S_M16_InstnTarget1)
#define S_M16_InstnTarget0	0
#define M_M16_InstnTarget0	(0xffff << S_M16_InstnTarget0)

/*
 * MIPS16 MOVE32R
 *
 *  1 1 1 1 1 1
 *  5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   I8    |mv32r| 2:0 |4:3| rz  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define S_M16_InstnRZ0		0
#define M_M16_InstnRZ0		(0x7 << S_M16_InstnRZ0)
#define S_M16_InstnR32u		3
#define M_M16_InstnR32u		(0x3 << S_M16_InstnR32u)
#define S_M16_InstnR32l		5
#define M_M16_InstnR32l		(0x7 << S_M16_InstnR32l)

/*
 * MIPS16 save/restore
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Extend |xsreg|f[7:4] | aregs |   I8    |svrs |S|a|0|1|frmsize|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define S_M16_InstnXsregs       24
#define M_M16_InstnXsregs       (0x7 << S_M16_InstnXsregs)
#define S_M16_InstnFrameSize7   20
#define M_M16_InstnFrameSize7   (0xf << S_M16_InstnFrameSize7)
#define S_M16_InstnAregs        16
#define M_M16_InstnAregs        (0xf << S_M16_InstnAregs)
#define S_M16_InstnS		7
#define M_M16_InstnS		(0x1 << S_M16_InstnS)
#define S_M16_InstnRa		6
#define M_M16_InstnRa		(0x1 << S_M16_InstnRa)
#define S_M16_InstnS0		5
#define M_M16_InstnS0		(0x1 << S_M16_InstnS0)
#define S_M16_InstnS1		4
#define M_M16_InstnS1		(0x1 << S_M16_InstnS1)
#define S_M16_InstnFrameSize    0
#define M_M16_InstnFrameSize    (0xf << S_M16_InstnFrameSize)



/*
 *************************************************************************
 *         V I R T U A L   A D D R E S S   D E F I N I T I O N S         *
 *************************************************************************
 */

#ifdef MIPSADDR64
#define A_K0BASE		UINT64_C(0xffffffff80000000)
#define A_K1BASE		UINT64_C(0xffffffffa0000000)
#define A_K2BASE		UINT64_C(0xffffffffc0000000)
#define A_K3BASE		UINT64_C(0xffffffffe0000000)
#define A_REGION		UINT64_C(0xc000000000000000)
#define A_XKPHYS_ATTR		UINT64_C(0x3800000000000000)
#else
#define A_K0BASE		0x80000000
#define A_K1BASE		0xa0000000
#define A_K2BASE		0xc0000000
#define A_K3BASE		0xe0000000
#endif
#define M_KMAPPED		0x40000000		/* KnSEG address is mapped if bit is one */


#ifdef MIPS_Model64

#define S_VMAP64                62
#define M_VMAP64                UINT64_C(0xc000000000000000)

#define K_VMode11               3
#define K_VMode10               2
#define K_VMode01               1
#define K_VMode00               0

#define S_KSEG3                 29
#define M_KSEG3                 (0x7 << S_KSEG3)
#define K_KSEG3                 7

#define S_SSEG                  29
#define M_SSEG                  (0x7 << S_KSEG3)
#define K_SSEG                  6

#define S_KSSEG                 29
#define M_KSSEG                 (0x7 << S_KSEG3)
#define K_KSSEG                 6

#define S_KSEG1                 29
#define M_KSEG1                 (0x7 << S_KSEG3)
#define K_KSEG1                 5

#define S_KSEG0                 29
#define M_KSEG0                 (0x7 << S_KSEG3)
#define K_KSEG0                 4

#define S_XKSEG                 29
#define M_XKSEG                 (0x7 << S_KSEG3)
#define K_XKSEG                 3

#define S_USEG                  31
#define M_USEG                  (0x1 << S_USEG)
#define K_USEG                  0

#define S_EjtagProbeMem         20
#define M_EjtagProbeMem         (0x1 << S_EjtagProbeMem)
#define K_EjtagProbeMem         0



#else

#define S_KSEG3                 29
#define M_KSEG3                 (0x7 << S_KSEG3)
#define K_KSEG3                 7

#define S_KSSEG                 29
#define M_KSSEG                 (0x7 << S_KSSEG)
#define K_KSSEG                 6

#define S_SSEG                  29
#define M_SSEG                  (0x7 << S_SSEG)
#define K_SSEG                  6

#define S_KSEG1                 29
#define M_KSEG1                 (0x7 << S_KSEG1)
#define K_KSEG1                 5

#define S_KSEG0                 29
#define M_KSEG0                 (0x7 << S_KSEG0)
#define K_KSEG0                 4

#define S_KUSEG                 31
#define M_KUSEG                 (0x1 << S_KUSEG)
#define K_KUSEG                 0

#define S_SUSEG                 31
#define M_SUSEG                 (0x1 << S_SUSEG)
#define K_SUSEG                 0

#define S_USEG                  31
#define M_USEG                  (0x1 << S_USEG)
#define K_USEG                  0

#define K_EjtagLower            0xff200000
#define K_EjtagUpper            0xff3fffff

#define S_EjtagProbeMem         20
#define M_EjtagProbeMem         (0x1 << S_EjtagProbeMem)
#define K_EjtagProbeMem         0

#endif



/*
 *************************************************************************
 *   C A C H E   I N S T R U C T I O N   O P E R A T I O N   C O D E S   *
 *************************************************************************
 */

/*
 * Cache encodings
 */
#define K_CachePriI		0			/* Primary Icache */
#define K_CachePriD		1			/* Primary Dcache */
#define K_CachePriU		1			/* Unified primary */
#define K_CacheTerU		2			/* Unified Tertiary */
#define K_CacheSecU		3			/* Unified secondary */


/*
 * Function encodings
 */
#define S_CacheFunc		2			/* Amount to shift function encoding within 5-bit field */
#define K_CacheIndexInv		0			/* Index invalidate */
#define K_CacheIndexWBInv       0			/* Index writeback invalidate */
#define K_CacheIndexLdTag	1			/* Index load tag */
#define K_CacheIndexStTag	2			/* Index store tag */
#define K_CacheHitInv		4			/* Hit Invalidate */
#define K_CacheFill		5			/* Fill (Icache only) */
#define K_CacheHitWBInv		5			/* Hit writeback invalidate */
#define K_CacheHitWB		6			/* Hit writeback */
#define K_CacheFetchLock	7			/* Fetch and lock */

#define ICIndexInv		((K_CacheIndexInv << S_CacheFunc) | K_CachePriI)
#define DCIndexWBInv		((K_CacheIndexWBInv << S_CacheFunc) | K_CachePriD)
#define DCIndexInv		DCIndexWBInv
#define ICIndexLdTag		((K_CacheIndexLdTag << S_CacheFunc) | K_CachePriI)
#define DCIndexLdTag		((K_CacheIndexLdTag << S_CacheFunc) | K_CachePriD)
#define ICIndexStTag		((K_CacheIndexStTag << S_CacheFunc) | K_CachePriI)
#define DCIndexStTag		((K_CacheIndexStTag << S_CacheFunc) | K_CachePriD)
#define ICHitInv		((K_CacheHitInv << S_CacheFunc) | K_CachePriI)
#define DCHitInv		((K_CacheHitInv << S_CacheFunc) | K_CachePriD)
#define ICFill			((K_CacheFill << S_CacheFunc) | K_CachePriI)
#define DCHitWBInv		((K_CacheHitWBInv << S_CacheFunc) | K_CachePriD)
#define DCHitWB			((K_CacheHitWB << S_CacheFunc) | K_CachePriD)
#define ICFetchLock		((K_CacheFetchLock << S_CacheFunc) | K_CachePriI)
#define DCFetchLock		((K_CacheFetchLock << S_CacheFunc) | K_CachePriD)

#define SCIndexWBInv        	((K_CacheIndexWBInv 	<< S_CacheFunc) | K_CacheSecU)
#define SCIndexInv		SCIndexWBInv
#define SCIndexLdTag        	((K_CacheIndexLdTag 	<< S_CacheFunc) | K_CacheSecU)
#define SCIndexStTag        	((K_CacheIndexStTag 	<< S_CacheFunc) | K_CacheSecU)
#define SCHitInv            	((K_CacheHitInv 	<< S_CacheFunc) | K_CacheSecU)
#define SCHitWBInv          	((K_CacheHitWBInv 	<< S_CacheFunc) | K_CacheSecU)
#define SCHitWB             	((K_CacheHitWB 		<< S_CacheFunc)	| K_CacheSecU)

#define TCIndexWBInv        	((K_CacheIndexWBInv 	<< S_CacheFunc) | K_CacheTerU)
#define TCIndexInv		TCIndexWBInv
#define TCIndexLdTag        	((K_CacheIndexLdTag 	<< S_CacheFunc) | K_CacheTerU)
#define TCIndexStTag        	((K_CacheIndexStTag 	<< S_CacheFunc) | K_CacheTerU)
#define TCHitInv            	((K_CacheHitInv 	<< S_CacheFunc) | K_CacheTerU)
#define TCHitWBInv          	((K_CacheHitWBInv 	<< S_CacheFunc) | K_CacheTerU)
#define TCHitWB             	((K_CacheHitWB 		<< S_CacheFunc)	| K_CacheTerU)

/*
 *************************************************************************
 *          P R E F E T C H   I N S T R U C T I O N   H I N T S          *
 *************************************************************************
 */

#define PrefLoad		0
#define PrefStore		1
#define PrefLoadStreamed	4
#define PrefStoreStreamed	5
#define PrefLoadRetained	6
#define PrefStoreRetained	7
#define PrefWBInval		25
#define PrefNudge		25


/*
 *************************************************************************
 *             C P U   R E G I S T E R   D E F I N I T I O N S           *
 *************************************************************************
 */


/*
 *************************************************************************
 *                  S O F T W A R E   G P R   N A M E S                  *
 *************************************************************************
 */

#if defined(__ASSEMBLER__)
#define zero			 $0
#define AT			 $1
#define v0			 $2
#define v1			 $3
#define a0			 $4
#define a1			 $5
#define a2			 $6
#define a3			 $7
#define t0			 $8
#define t1			 $9
#define t2			$10
#define t3			$11
#define t4			$12
#define t5			$13
#define t6			$14
#define t7			$15
#define s0			$16
#define s1			$17
#define s2			$18
#define s3			$19
#define s4			$20
#define s5			$21
#define s6			$22
#define s7			$23
#define t8			$24
#define t9			$25
#define k0			$26
#define k1			$27
#define gp			$28
#define sp			$29
#define fp			$30
#define ra			$31
#endif

/*
 * The following registers are used by the AVP environment and
 * are not part of the normal software definitions.
 */

#ifdef MIPSAVPENV
#define repc			$25			/* Expected exception PC */
#define tid			$30			/* Current test case address */
#endif


/*
 *************************************************************************
 *                  H A R D W A R E   G P R   N A M E S                  *
 *************************************************************************
 *
 * In the AVP environment, several of the `r' names are removed from the
 * name space because they are used by the kernel for special purposes.
 * Removing them causes assembly rather than runtime errors for tests that
 * use the `r' names.
 *
 *	- r25 (repc) is used as the expected PC on an exception
 *	- r26-r27 (k0, k1) are used in the exception handler
 *	- r30 (tid) is used as the current test address
 */

#if defined(__ASSEMBLER__)
#define r0			 $0
#define r1			 $1
#define r2			 $2
#define r3			 $3
#define r4			 $4
#define r5			 $5
#define r6			 $6
#define r7			 $7
#define r8			 $8
#define r9			 $9
#define r10			$10
#define r11			$11
#define r12			$12
#define r13			$13
#define r14			$14
#define r15			$15
#define r16			$16
#define r17			$17
#define r18			$18
#define r19			$19
#define r20			$20
#define r21			$21
#define r22			$22
#define r23			$23
#define r24			$24
#ifdef MIPSAVPENV
#define r25			r25_unknown
#define r26			r26_unknown
#define r27			r27_unknown
#else
#define r25			$25
#define r26			$26
#define r27			$27
#endif
#define r28			$28
#define r29			$29
#ifdef MIPSAVPENV
#define r30			r30_unknown
#else
#define r30			$30
#endif
#define r31			$31
#endif /* defined(__ASSEMBLER__) */


/*
 *************************************************************************
 *                H A R D W A R E   G P R   I N D I C E S                *
 *************************************************************************
 *
 * These definitions provide the index (number) of the GPR, as opposed
 * to the assembler register name ($n).
 */

#define R_r0			 0
#define R_r1			 1
#define R_r2			 2
#define R_r3			 3
#define R_r4			 4
#define R_r5			 5
#define R_r6			 6
#define R_r7			 7
#define R_r8			 8
#define R_r9			 9
#define R_r10			10
#define R_r11			11
#define R_r12			12
#define R_r13			13
#define R_r14			14
#define R_r15			15
#define R_r16			16
#define R_r17			17
#define R_r18			18
#define R_r19			19
#define R_r20			20
#define R_r21			21
#define R_r22			22
#define R_r23			23
#define R_r24			24
#define R_r25			25
#define R_r26			26
#define R_r27			27
#define R_r28			28
#define R_r29			29
#define R_r30			30
#define R_r31			31
#define R_hi			32			/* Hi register */
#define R_lo			33			/* Lo register */


/*
 *************************************************************************
 *                S O F T W A R E   G P R   I N D I C E S                *
 *************************************************************************
 *
 * These definitions provide the index (number) of the GPR, as opposed
 * to the assembler register name ($n).
 */

#define R_zero			 0
#define R_AT			 1
#define R_v0			 2
#define R_v1			 3
#define R_a0			 4
#define R_a1			 5
#define R_a2			 6
#define R_a3			 7
#define R_t0			 8
#define R_t1			 9
#define R_t2			10
#define R_t3			11
#define R_t4			12
#define R_t5			13
#define R_t6			14
#define R_t7			15
#define R_s0			16
#define R_s1			17
#define R_s2			18
#define R_s3			19
#define R_s4			20
#define R_s5			21
#define R_s6			22
#define R_s7			23
#define R_t8			24
#define R_t9			25
#define R_k0			26
#define R_k1			27
#define R_gp			28
#define R_sp			29
#define R_fp			30
#define R_s8			30
#define R_ra			31


/*
 *************************************************************************
 *                  S O F T W A R E   G P R   M A S K S                  *
 *************************************************************************
 *
 * These definitions provide the bit mask corresponding to the GPR number
 */

#define M_AT			 (1<<1)
#define M_v0			 (1<<2)
#define M_v1			 (1<<3)
#define M_a0			 (1<<4)
#define M_a1			 (1<<5)
#define M_a2			 (1<<6)
#define M_a3			 (1<<7)
#define M_t0			 (1<<8)
#define M_t1			 (1<<9)
#define M_t2			(1<<10)
#define M_t3			(1<<11)
#define M_t4			(1<<12)
#define M_t5			(1<<13)
#define M_t6			(1<<14)
#define M_t7			(1<<15)
#define M_s0			(1<<16)
#define M_s1			(1<<17)
#define M_s2			(1<<18)
#define M_s3			(1<<19)
#define M_s4			(1<<20)
#define M_s5			(1<<21)
#define M_s6			(1<<22)
#define M_s7			(1<<23)
#define M_t8			(1<<24)
#define M_t9			(1<<25)
#define M_k0			(1<<26)
#define M_k1			(1<<27)
#define M_gp			(1<<28)
#define M_sp			(1<<29)
#define M_fp			(1<<30)
#define M_ra			(1<<31)


/*
 *************************************************************************
 *             C P 0   R E G I S T E R   D E F I N I T I O N S           *
 *************************************************************************
 * Each register has the following definitions:
 *
 *	C0_rrr		The register number (as a $n value)
 *	R_C0_rrr	The register index (as an integer corresponding
 *			to the register number)
 *	R_C0_Selrrr	The register select (as an integer corresponding
 *			to the register select)
 *
 * Each field in a register has the following definitions:
 *
 *	S_rrrfff	The shift count required to right-justify
 *			the field.  This corresponds to the bit
 *			number of the right-most bit in the field.
 *	M_rrrfff	The Mask required to isolate the field.
 *
 * Register diagrams included below as comments correspond to the
 * MIPS32 and MIPS64 architecture specifications.  Refer to other
 * sources for register diagrams for older architectures.
 */


/*
 ************************************************************************
 *                 I N D E X   R E G I S T E R   ( 0 )                  *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |P|                         0                       |   Index   | Index
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_Index		$0
#define R_C0_Index		0
#define R_C0_SelIndex		0
#define C0_INX			C0_Index		/* OBSOLETE - DO NOT USE IN NEW CODE */

#define S_IndexP		31			/* Probe failure (R)*/
#define M_IndexP		(0x1 << S_IndexP)

#define S_IndexIndex		0			/* TLB index (R/W)*/
#define M_IndexIndex		(0x3f << S_IndexIndex)

#define M_Index0Fields		0x7fffffc0
#define M_IndexRFields		0x80000000


/*
 ************************************************************************
 *                R A N D O M   R E G I S T E R   ( 1 )                 *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                            0                      |   Index   | Random
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_Random		$1
#define R_C0_Random		1
#define R_C0_SelRandom		0
#define C0_RAND			$1			/* OBSOLETE - DO NOT USE IN NEW CODE */

#define S_RandomIndex		0			/* TLB random index (R)*/
#define M_RandomIndex		(0x3f << S_RandomIndex)

#define M_Random0Fields		0xffffffc0
#define M_RandomRFields		0x0000003f


/*
 ************************************************************************
 *              E N T R Y L O 0   R E G I S T E R   ( 2 )               *
 ************************************************************************
 * 	
 *  6 6 6 6 5 // 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  3 2 1 0 9 // 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | Fill (0) //|R|X|                     PFN                       |  C  |D|V|G| EntryLo0
 * |          //|I|I|                                               |     | | | |
 * +-+-+-+-+-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_EntryLo0		$2
#define R_C0_EntryLo0		2
#define R_C0_SelEntryLo0	0
#define C0_TLBLO_0		C0_EntryLo0		/* OBSOLETE - DO NOT USE IN NEW CODE */

#if defined(MIPS_SmartMIPS_ASE)
/*
 * SmartMIPS MMU has RI and XI bits for further access qualification.
 * Non-SmartMIPS MMUs have bits 31 and 30 as reserved/zero bits.
 */
#define S_EntryLoRI		31		    /* Read Inhibit (R/W) */
#define M_EntryLoRI		(0x1 << S_EntryLoRI)
#define S_EntryLoXI		30		    /* Execute Inhibit (R/W) */
#define M_EntryLoXI		(0x1 << S_EntryLoXI)
#endif /* MIPS_SmartMIPS_ASE */

#define S_EntryLoPFN		6			/* PFN (R/W) */
#define M_EntryLoPFN		(0xffffff << S_EntryLoPFN)
#define S_EntryLoC		3			/* Coherency attribute (R/W) */
#define M_EntryLoC		(0x7 << S_EntryLoC)
#define S_EntryLoD		2			/* Dirty (R/W) */
#define M_EntryLoD		(0x1 << S_EntryLoD)
#define S_EntryLoV		1			/* Valid (R/W) */
#define M_EntryLoV		(0x1 << S_EntryLoV)
#define S_EntryLoG		0			/* Global (R/W) */
#define M_EntryLoG		(0x1 << S_EntryLoG)
#define M_EntryLoOddPFN		(0x1 << S_EntryLoPFN)	/* Odd PFN bit */
#define S_EntryLo_RS		K_PageAlign		/* ? */
/* Shift to put PFN in its position within a physical address */
#ifndef MIPS_SmartMIPS_ASE
#define S_EntryLo_LS		(12 - S_EntryLoPFN)
#else
#define S_EntryLo_LS		((12 - S_EntryLoPFN) - (12 - C0_PageGrainMSOne))
#endif /* MIPS_SmartMIPS_ASE */

#define M_EntryLo0Fields	0x00000000
#define M_EntryLo0Fields64	UINT64_C(0x0000000000000000)
#ifdef MIPS_SmartMIPS_ASE
#define M_EntryLoRFields	0x00000000
#define M_EntryLoRFields64	UINT64_C(0xffffffff00000000)
#else
#define M_EntryLoRFields	0xc0000000
#define M_EntryLoRFields64	UINT64_C(0xffffffffc0000000)
#endif /* MIPS_SmartMIPS_ASE */

/*
 * Cache attribute values in the C field of EntryLo and the
 * K0 field of Config
 */
#define K_CacheAttrCWTnWA	0			/* Cacheable, write-thru, no write allocate */
#define K_CacheAttrCWTWA	1			/* Cacheable, write-thru, write allocate */
#define K_CacheAttrU		2			/* Uncached */
#define K_CacheAttrC		3			/* Cacheable */
#define K_CacheAttrCN		3			/* Cacheable, non-coherent */
#define K_CacheAttrCCE		4			/* Cacheable, coherent, exclusive */
#define K_CacheAttrCCS		5			/* Cacheable, coherent, shared */
#define K_CacheAttrCCU		6			/* Cacheable, coherent, update */
#define K_CacheAttrUA		7			/* Uncached accelerated */


/*
 ************************************************************************
 *              E N T R Y L O 1   R E G I S T E R   ( 3 )               *
 ************************************************************************
 * 	
 *  6 6 6 6 5 // 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  3 2 1 0 9 // 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | Fill (0) //| 0 |                     PFN                       |  C  |D|V|G| EntryLo1
 * +-+-+-+-+-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_EntryLo1		$3
#define R_C0_EntryLo1		3
#define R_C0_SelEntryLo1	0
#define C0_TLBLO_1		C0_EntryLo1		/* OBSOLETE - DO NOT USE IN NEW CODE */

/*
 * Field definitions are as given for EntryLo0 above
 */


/*
 ************************************************************************
 *               C O N T E X T   R E G I S T E R   ( 4, SELECT 0 )      *
 ************************************************************************
 * 	
 *  6 // 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  3 // 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  //       PTEBase    |            BadVPN<31:13>            |   0   | Context
 * +-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_Context		$4
#define R_C0_Context		4
#define R_C0_SelContext		0
#define C0_CTXT			C0_Context		/* OBSOLETE - DO NOT USE IN NEW CODE */

#ifndef MIPS_SmartMIPS_ASE
#define S_ContextPTEBase	23			/* PTE base (R/W) */
#define S_ContextBadVPN		4			/* BadVPN2 (R) */

#else

/*
 * Definitions for Context as configured by ContextConfig.
 * Assumes that ContextConfigMSOne and ContextConfigLSOne
 * value are available at evaluation time. Whether these
 * are constants, variables, or returned by a function call 
 * is outside the scope of ArchDefs.h
 */

#define S_ContextPTEBase	(C0_ContextConfigMSOne + 1)

#define S_ContextBadVPN		(C0_ContextConfigLSOne)

#endif /* MIPS_SmartMIPS_ASE */

/*
 * Definitions that can be derived from the above two,
 * regardless of whether or not ContextConfig is implemented.
 */

#define M_Context0Fields	((1 << S_ContextBadVPN) - 1)
#define M_ContextRFields	(((1 << S_ContextPTEBase) - 1) \
				  & ~(M_Context0Fields))
#define M_Context0Fields64	((UINT64_C(1) << S_ContextBadVPN) - 1)
#define M_ContextRFields64	(((UINT64_C(1) << S_ContextPTEBase) - 1) \
				  & ~(M_Context0Fields))
#define M_ContextPTEBase	(((1 << S_ContextBadVPN_LS) - 1) \
                                       << S_ContextPTEBase)
#define M_ContextBadVPN		(((1 << (S_ContextPTEBase - S_ContextBadVPN))\
                                  - 1) << S_ContextBadVPN)
/* Position BadVPN to bit 31. */
#define S_ContextBadVPN_LS	(32 - S_ContextPTEBase)
/* Right-justify shifted BadVPN field, i.e. VA bits not in BadVPN2 */
#define S_ContextBadVPN_RS	(32 - (S_ContextPTEBase - S_ContextBadVPN))

#if defined(MIPS_SmartMIPS_ASE) || defined(MIPS_Release2)
/*
 ************************************************************************
 *       C O N T E X T C O N F I G  R E G I S T E R  ( 4, SELECT 1 )    *
 ************************************************************************
 * 	
 *  6 // 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  3 // 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  //                     VirtualIndex                               |ContextConfig
 * +-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * ContextConfig, if implemented, makes the definitions of the Context
 * register "soft".  The number of bits in the PTEBase and BadVPN fields
 * become variable.  The leading zero field of the ContextConfig register
 * corresponds to the set of bits to be treated as a read/write PTEBase
 * field.  The following field of ones corrsponds to the set of bits to
 * be treated as the virtual page number, into which as many high order
 * bits of the VA are copied as there are bits set in the field.
 */

#define C0_ContextConfig	$4,1
#define R_C0_ContextConfig	4	/* Overload */
#define R_C0_SelContextConfig	1

/*
 * It is possible to write definition for the Context register above
 * in terms of the word value of ContextConfig, but with gcc in particular,
 * it is extrememly ineffecient both at compile and run-time. Contex
 * is therefore defined in terms of two values, C0_ContextConfigMSOne
 * and C0_ContextConfigLSOne, which are the bit numbers of the most
 * significant and least significant one-valued bits of the 
 * ContextConfig register.  The default reset values are defined
 * here, BUT SHOULD BE OVERRIDDEN WITH A FUNCTION CALL OR A REFERENCE
 * TO A RUN-TIME VALUE IN ANY DYNAMIC MODEL OF A SmartMIPS CPU.
 */

#ifndef C0_ContextConfigMSOne
#define C0_ContextConfigMSOne	22
#endif /* C0_ContextConfigMSOne */

#ifndef C0_ContextConfigLSOne	
#define C0_ContextConfigLSOne	4
#endif /* C0_ContextConfigLSOne */


#endif /* MIPS_SmartMIPS_ASE */

/*
 ************************************************************************
 *              P A G E M A S K   R E G I S T E R   ( 5, SELECT 0 )     *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  0  |             Mask              |            0            | PageMask
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_PageMask		$5
#define R_C0_PageMask		5			/* Mask (R/W) */
#define R_C0_SelPageMask	0
#define C0_PGMASK		C0_PageMask		/* OBSOLETE - DO NOT USE IN NEW CODE */

#ifndef MIPS_SmartMIPS_ASE

#define S_PageMaskMask		13
#define M_PageMaskMask		(0xffff << S_PageMaskMask)
#define S_PageMaskMaskX		11
#define M_PageMaskMaskX		(0x3 << S_PageMaskMaskX)

#define M_PageMask0Fields	0xe0001fff
#define M_PageMaskRFields	0x00000000

/*
 * Values in the Mask field
 */
#define K_PageMask4K		0x0000			/* K_PageMasknn values are values for use */
#define K_PageMask16K		0x0003			/* with KReqPageAttributes or KReqPageMask macros */
#define K_PageMask64K		0x000f
#define K_PageMask256K		0x003f
#define K_PageMask1M		0x00ff
#define K_PageMask4M		0x03ff
#define K_PageMask16M		0x0fff
#define K_PageMask64M		0x3fff
#define K_PageMask256M		0xffff

#else /* MIPS_SmartMIPS_ASE */

/*
 * In a SmartMIPS MMU, the PageGrain register can be used to
 * enable extending the PageMask Mask field downward by another
 * two bits.  The writable/useable bits of PageMask are thus
 * variable, and depend on the value of the PageGrain register.
 */

#define S_PageMaskMask		(C0_PageGrainMSOne + 1)
#define M_PageMaskMask		(((0x1 << (12 + (12 - C0_PageGrainMSOne))) - 1)\
				    << S_PageMaskMask)

#define M_PageMask0Fields	(0xfe0007ff | \
				(C0_PageGrainValue & M_PageGrainMask))
#define M_PageMaskRFields	0x00000000

/*
 * 1K Pages are only possible if the PageGrain Mask field is zero
 */

#define	K_PageMask1K		((0x1 << (10 - C0_PageGrainMSOne)) - 1)
#define M_PageMask1K		(K_PageMask1K << S_PageMaskMask)

/*
 * 2K Pages are possible if the PageGrain Mask field is zero or one.
 */

#define	K_PageMask2K		((0x1 << (11 - C0_PageGrainMSOne)) - 1)
#define M_PageMask2K		(K_PageMask2K << S_PageMaskMask)

/*
 * 4K and larger pages are expressed differently depending on PageGrain
 */

#define	K_PageMask4K		((0x1 << (12 - C0_PageGrainMSOne)) - 1)
#define	K_PageMask16K		((0x1 << (14 - C0_PageGrainMSOne)) - 1)
#define	K_PageMask64K		((0x1 << (16 - C0_PageGrainMSOne)) - 1)
#define	K_PageMask256K		((0x1 << (18 - C0_PageGrainMSOne)) - 1)
#define	K_PageMask1M		((0x1 << (20 - C0_PageGrainMSOne)) - 1)
#define	K_PageMask4M		((0x1 << (22 - C0_PageGrainMSOne)) - 1)
#define	K_PageMask16M		((0x1 << (24 - C0_PageGrainMSOne)) - 1)
#define	K_PageMask64M		((0x1 << (26 - C0_PageGrainMSOne)) - 1)
#define	K_PageMask256M		((0x1 << (28 - C0_PageGrainMSOne)) - 1)

#endif /* MIPS_SmartMIPS_ASE */

#define M_PageMask4K		(K_PageMask4K << S_PageMaskMask) /* M_PageMasknn values are masks */
#define M_PageMask16K		(K_PageMask16K << S_PageMaskMask) /* in position in the PageMask register */
#define M_PageMask64K		(K_PageMask64K << S_PageMaskMask)
#define M_PageMask256K		(K_PageMask256K << S_PageMaskMask)
#define M_PageMask1M		(K_PageMask1M << S_PageMaskMask)
#define M_PageMask4M		(K_PageMask4M << S_PageMaskMask)
#define M_PageMask16M		(K_PageMask16M << S_PageMaskMask)
#define M_PageMask64M		(K_PageMask64M << S_PageMaskMask)
#define M_PageMask256M		(K_PageMask256M << S_PageMaskMask)

/* Shift amounts for different Page Size */
#define S_PAGE1K	10
#define S_PAGE2K	11
#define S_PAGE4K	12
#define S_PAGE16K	14
#define S_PAGE64K	16
#define S_PAGE256K	18
#define S_PAGE1M	20
#define S_PAGE4M	22
#define S_PAGE16M	24
#define S_PAGE64M	26
#define S_PAGE256M	28

#define S_PageMask1K	(S_PAGE1K   + 1)
#define S_PageMask2K	(S_PAGE2K   + 1)
#define S_PageMask4K	(S_PAGE4K   + 1)
#define S_PageMask16K	(S_PAGE16K  + 1)
#define S_PageMask64K	(S_PAGE64K  + 1)
#define S_PageMask256K	(S_PAGE256K + 1)
#define S_PageMask1M	(S_PAGE1M   + 1)
#define S_PageMask4M	(S_PAGE4M   + 1)
#define S_PageMask16M	(S_PAGE16M  + 1)
#define S_PageMask64M	(S_PAGE64M  + 1)
#define S_PageMask256M	(S_PAGE256M + 1)
/* For Release 2 we need to write correct value to pagemask, default to 4k page*/
#define K_1KPAGEMASK	(0x00000)
#define K_2KPAGEMASK	(0x00800)
#define K_4KPAGEMASK	(0x01800)
#define K_16KPAGEMASK	(0x07800)
#define K_64KPAGEMASK	(0x1f800)
#define K_256KPAGEMASK	(0x7f800)
#define K_1MPAGEMASK	(0x1ff800)
#define K_4MPAGEMASK	(0x7ff800)
#define K_16MPAGEMASK	(0x1fff800)
#define K_64MPAGEMASK	(0x7fff800)
#define K_256MPAGEMASK	(0x1ffff800)


#if defined(MIPS_SmartMIPS_ASE) || defined(MIPS_Release2)

/*
 ************************************************************************
 *              P A G E G R A I N   R E G I S T E R   ( 5, SELECT 1 )   *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | | |E| |                             |   |     |               |
 * |R|X|L|E|                             |   |     |               |
 * |I|I|P|S|          0                  |Msk|1 1 1|       0       | PageGrain
 * |E|E|A|P|                             |   |     |               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * The PageGrain register, if implemented, allows for finer grained
 * pages than would be provided by the default behavior of PageMask
 * and EntryHi.  The Mask bits can be cleared to enable 2K or 4K 
 * page granularity.
 */

#define C0_PageGrain		$5,1
#define R_C0_PageGrain		5			/* Mask (R/W) */
#define R_C0_SelPageGrain	1

#define S_PageGrainOnes		8
#define M_PageGrainOnes		(0x7 << S_PageGrainOnes)

#define S_PageGrainMask		11
#define M_PageGrainMask		(0x3 << S_PageGrainMask)

/*
 * To allow full backward compatibility, the RI/XI bits
 * in EntryLo0/EntryLo1 are write-enabled by the corresponding
 * enable bits of PageGrain.
 */
#define S_PageGrainRIE		31	/* Read Inhibit Enable (R/W) */
#define M_PageGrainRIE		(0x1 << S_PageGrainRIE)
#define S_PageGrainXIE		30	/* Execute Inhibit Enable (R/W) */
#define M_PageGrainXIE		(0x1 << S_PageGrainXIE)

#define S_PageGrainELPA		29	/* Large Physical Page support */
#define M_PageGrainELPA		(0x1 << S_PageGrainELPA)
#define S_PageGrainESP		28	/* 1k page support */
#define M_PageGrainESP		(0x1 << S_PageGrainESP)

#if defined(MIPS_SmartMIPS_ASE) && defined(MIPS_Release2)
#define M_PageGrain0Fields	0x0fffe0ff
#define M_PageGrainRFields	0x00000700
#else
#if defined(MIPS_Release2)
#define M_PageGrain0Fields	0xcfffffff
#define M_PageGrainRFields	0x00000000
#else
#define M_PageGrain0Fields	0x3fffe0ff
#define M_PageGrainRFields	0x00000700
#endif
#endif

/*
 * The Value of the PageGrain register affects the observable
 * behavior of PageMask and EntryHi.  These effects are dynamic,
 * and as such THE FOLLOWING SYMBOLS SHOULD BE OVERRIDDEN WITH
 * FUNCTION CALLS OR REFERENCES TO RUN-TIME VARIABLES IN ANY
 * DYNAMIC MODEL OF A SmartMIPS CPU.  They are defined here as
 * contstants with the reset default value.
 */

#ifndef C0_PageGrainMSOne
#define C0_PageGrainMSOne	12
#endif /* C0_PageGrainMSOne */

#define C0_PageGrainValue	((((0x1 << \
			 	(C0_PageGrainMSOne - S_PageGrainMask + 1)) - 1)\
				    <<  S_PageGrainMask) | M_PageGrainOnes)

#endif /* MIPS_SmartMIPS_ASE */

/*
 ************************************************************************
 *                 W I R E D   R E G I S T E R   ( 6 )                  *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                            0                      |   Index   | Wired
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_Wired		$6
#define R_C0_Wired		6
#define R_C0_SelWired		0
#define C0_TLBWIRED		C0_Wired		/* OBSOLETE - DO NOT USE IN NEW CODE */

#define S_WiredIndex		0			/* TLB wired boundary (R/W) */
#define M_WiredIndex		(0x3f << S_WiredIndex)

#define M_Wired0Fields		0xffffffc0
#define M_WiredRFields		0x00000000


#ifdef MIPS_Release2 
/*
 ************************************************************************
 *                H W R E n a   R E G I S T E R   ( 7 )                 *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                            0                          | mask  | HWREna
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_HWREna		$7
#define R_C0_HWREna		7
#define R_C0_SelHWREna		0

#define S_HWREnaMask		0			/* Mask bits (R/W) */
#define M_HWREnaMask		(0xF << S_HWREnaMask)

/*
 * The following defines both the individual mask bits, and the RDHWR
 * register numbers that correspond to the masks.
 */
#define S_HWREnaMask_CPUNum 	0
#define M_HWREnaMask_CPUNum 	(1 << S_HWREnaMask_CPUNum)
#define S_HWREnaMask_CycleCount 2
#define M_HWREnaMask_CycleCount (1 << S_HWREnaMask_CycleCount)
#define S_HWREnaMask_SYNCI_Step 1
#define M_HWREnaMask_SYNCI_Step (1 << S_HWREnaMask_SYNCI_Step)
#define S_HWREnaMask_CC 	2
#define M_HWREnaMask_CC 	(1 << S_HWREnaMask_CC)
#define S_HWREnaMask_CCRes 	3
#define M_HWREnaMask_CCRes 	(1 << S_HWREnaMask_CCRes)

#define HWR_CPUNum		$0			/* CPUNum */
#define R_HWR_CPUNum		S_HWREnaMask_CPUNum
#define HWR_SYNCI_Step		$1			/* Address step for SYNCI */
#define R_HWR_SYNCI_Step	S_HWREnaMask_SYNCI_Step
#define HWR_CycleCount		$2			/* Cycle counter */
#define R_HWR_CycleCount	S_HWREnaMask_CycleCount
#define HWR_CC			$2			/* CycleCounter */
#define R_HWR_CC		S_HWREnaMask_CC
#define HWR_CCRes		$3			/* CCRes */
#define R_HWR_CCRes		S_HWREnaMask_CCRes

#define M_HWREna0Fields		0xfffffff0
#define M_HWREnaRFields		0x00000000

#endif /* ifdef MIPS_Release2 */


/*
 ************************************************************************
 *              B A D V A D D R   R E G I S T E R   ( 8 )               *
 ************************************************************************
 * 	
 *  6 // 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  3 // 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  //                     Bad Virtual Address                        | BadVAddr
 * +-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_BadVAddr		$8
#define R_C0_BadVAddr		8
#define R_C0_SelBadVAddr	0
#define C0_BADVADDR		C0_BadVAddr		/* OBSOLETE - DO NOT USE IN NEW CODE */

#define M_BadVAddrOddPage	K_PageSize		/* Even/Odd VA bit for pair of PAs */

#define M_BadVAddr0Fields	0x00000000
#define M_BadVAddrRFields	0xffffffff
#define M_BadVAddr0Fields64	UINT64_C(0x0000000000000000)
#define M_BadVAddrRFields64	UINT64_C(0xffffffffffffffff)

/*
 ************************************************************************
 *                 C O U N T   R E G I S T E R   ( 9 )                  *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                         Count Value                           | Count
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_Count		$9
#define R_C0_Count		9
#define R_C0_SelCount		0
#define C0_COUNT		C0_Count		/* OBSOLETE - DO NOT USE IN NEW CODE */

#define M_Count0Fields		0x00000000
#define M_CountRFields		0x00000000


/*
 ************************************************************************
 *              E N T R Y H I   R E G I S T E R   ( 1 0 )               *
 ************************************************************************
 * 	
 *  6 6 6 6 5 // 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  3 2 1 0 9 // 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | R | Fill //                 VPN2                 |    0    |     ASID      | EntryHi
 * +-+-+-+-+-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_EntryHi		$10
#define R_C0_EntryHi		10
#define R_C0_SelEntryHi		0
#define C0_TLBHI		C0_EntryHi		/* OBSOLETE - DO NOT USE IN NEW CODE */

#define S_EntryHiR64		62			/* Region (R/W) */
#define M_EntryHiR64		UINT64_C(0xc000000000000000)

#ifndef MIPS_SmartMIPS_ASE

#define S_EntryHiVPN2		13			/* VPN/2 (R/W) */
#define M_EntryHiVPN2		(0x7ffff << S_EntryHiVPN2)
#define M_EntryHiVPN264		UINT64_C(0x000000ffffffe000)

#ifdef MIPS_Release2 
#define S_EntryHiVPN2X		11
#define M_EntryHiVPN2X		(0x3 << S_EntryHiVPN2X)
#endif

#define M_EntryHi0Fields	0x00001f00
#define M_EntryHiRFields	0x00000000
#define M_EntryHi0Fields64	UINT64_C(0x0000000000001f00)

#else /* MIPS_SmartMIPS_ASE */

#define S_EntryHiVPN2		(C0_PageGrainMSOne + 1)
#define M_EntryHiVPN2		(((0x1 << (19 + (12 - C0_PageGrainMSOne)))-1)\
				    << S_EntryHiVPN2)
#define M_EntryHiVPN264		(((UINT64_C(0x1) << \
				    (27 + (12 - C0_PageGrainMSOne)))-1)\
				    << S_EntryHiVPN2)

#define M_EntryHi0Fields	(0x00000700 | \
				    (C0_PageGrainValue & M_PageGrainMask))
#define M_EntryHiRFields	0x00000000

#define M_EntryHi0Fields64	(UINT64_C(0x0000000000001f00) | \
				    (C0_PageGrainValue & M_PageGrainMask))

#endif /* MIPS_SmartMIPS_ASE */

#define M_EntryHiRFields64	UINT64_C(0x3fffff0000000000)
#define S_EntryHiASID		0			/* ASID (R/W) */
#define M_EntryHiASID		(0xff << S_EntryHiASID)
#define S_EntryHiVPN_Shf	S_EntryHiVPN2

/*
 ************************************************************************
 *              C O M P A R E   R E G I S T E R   ( 1 1 )               *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                        Compare Value                          | Compare
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_Compare		$11
#define R_C0_Compare		11
#define R_C0_SelCompare		0
#define C0_COMPARE		C0_Compare		/* OBSOLETE - DO NOT USE IN NEW CODE */

#define M_Compare0Fields	0x00000000
#define M_CompareRFields	0x00000000


/*
 ************************************************************************
 *               S T A T U S   R E G I S T E R   ( 1 2 )                *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |C|C|C|C|R|F|R|M|P|B|T|S|M| | R |I|I|I|I|I|I|I|I|K|S|U|U|R|E|E|I|
 * |U|U|U|U|P|R|E|X|X|E|S|R|M| | s |M|M|M|M|M|M|M|M|X|X|X|M|s|R|X|E| Status
 * |3|2|1|0| | | | | |V| | |I| | v |7|6|5|4|3|2|1|0| | | | |v|L|L| |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_Status		$12
#define R_C0_Status		12
#define R_C0_SelStatus		0
#define C0_SR			C0_Status		/* OBSOLETE - DO NOT USE IN NEW CODE */

#define S_StatusCU		28			/* Coprocessor enable (R/W) */
#define M_StatusCU		(0xf << S_StatusCU)
#define S_StatusCU3		31 			/* No longer used in Release 2 */
#define M_StatusCU3     	(0x1 << S_StatusCU3)
#define S_StatusCU2		30
#define M_StatusCU2		(0x1 << S_StatusCU2)
#define S_StatusCU1		29
#define M_StatusCU1		(0x1 << S_StatusCU1)
#define S_StatusCU0		28
#define M_StatusCU0		(0x1 << S_StatusCU0)
#define S_StatusRP		27			/* Enable reduced power mode (R/W) */
#define M_StatusRP		(0x1 << S_StatusRP)
#define S_StatusFR		26			/* Enable 64-bit FPRs (R/W) */
#define M_StatusFR		(0x1 << S_StatusFR)
#define S_StatusRE		25			/* Enable reverse endian (R/W) */
#define M_StatusRE		(0x1 << S_StatusRE)
#define S_StatusMX		24			/* Enable access to MDMX resources (MIPS64 only) (R/W) */
#define M_StatusMX		(0x1 << S_StatusMX)
#define S_StatusPX		23			/* Enable access to 64-bit instructions/data (MIPS64 only) (R/W) */
#define M_StatusPX		(0x1 << S_StatusPX)
#define S_StatusBEV		22			/* Enable Boot Exception Vectors (R/W) */
#define M_StatusBEV		(0x1 << S_StatusBEV)
#define S_StatusTS		21			/* Denote TLB shutdown (R/W) */
#define M_StatusTS		(0x1 << S_StatusTS)
#define S_StatusSR		20			/* Denote soft reset (R/W) */
#define M_StatusSR		(0x1 << S_StatusSR)
#define S_StatusNMI		19
#define M_StatusNMI		(0x1 << S_StatusNMI)	/* Denote NMI (R/W) */
#define S_StatusIM		8			/* Interrupt mask (R/W) */
#define M_StatusIM		(0xff << S_StatusIM)
#define S_StatusIM7		15
#define M_StatusIM7		(0x1 << S_StatusIM7)
#define S_StatusIM6		14
#define M_StatusIM6		(0x1 << S_StatusIM6)
#define S_StatusIM5		13
#define M_StatusIM5		(0x1 << S_StatusIM5)
#define S_StatusIM4		12
#define M_StatusIM4		(0x1 << S_StatusIM4)
#define S_StatusIM3		11
#define M_StatusIM3		(0x1 << S_StatusIM3)
#define S_StatusIM2		10
#define M_StatusIM2		(0x1 << S_StatusIM2)
#define S_StatusIM1		9
#define M_StatusIM1		(0x1 << S_StatusIM1)
#define S_StatusIM0		8
#define M_StatusIM0		(0x1 << S_StatusIM0)
#define S_StatusIPL     10
#define M_StatusIPL     (0x3f << S_StatusIPL)
#define S_StatusKX		7			/* Enable access to extended kernel addresses (MIPS64 only) (R/W) */
#define M_StatusKX		(0x1 << S_StatusKX)
#define S_StatusSX		6			/* Enable access to extended supervisor addresses (MIPS64 only) (R/W) */
#define M_StatusSX		(0x1 << S_StatusSX)
#define S_StatusUX		5			/* Enable access to extended user addresses (MIPS64 only) (R/W) */
#define M_StatusUX		(0x1 << S_StatusUX)
#define S_StatusKSU		3			/* Two-bit current mode (R/W) */
#define M_StatusKSU		(0x3 << S_StatusKSU)
#define S_StatusUM		4			/* User mode if supervisor mode not implemented (R/W) */
#define M_StatusUM		(0x1 << S_StatusUM)
#define S_StatusSM		3			/* Supervisor mode (R/W) */
#define M_StatusSM		(0x1 << S_StatusSM)
#define S_StatusERL		2			/* Denotes error level (R/W) */
#define M_StatusERL		(0x1 << S_StatusERL)
#define S_StatusEXL		1			/* Denotes exception level (R/W) */
#define M_StatusEXL		(0x1 << S_StatusEXL)
#define S_StatusIE		0			/* Enables interrupts (R/W) */
#define M_StatusIE		(0x1 << S_StatusIE)

#define M_Status0Fields		0x00040000
#define M_StatusRFields		0x058000e0		/* FR, MX, PX, KX, SX, UX unused in MIPS32 */
#define M_Status0Fields64	0x00040000
#define M_StatusRFields64	0x00000000

/*
 * Values in the KSU field
 */
#define K_StatusKSU_U		2			/* User mode in KSU field */
#define K_StatusKSU_S		1			/* Supervisor mode in KSU field */
#define K_StatusKSU_K		0			/* Kernel mode in KSU field */


#ifdef MIPS_Release2  
/*
 ************************************************************************
 *          I N T C T L   R E G I S T E R   ( 1 2, SELECT 1 )           *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  I  |  I  |                               |         |         |
 * |  P  |  P  |         0                     |   VS    |   0     |  IntCtl
 * |  T  |  P  |                               |         |         |
 * |  I  |  C  |                               |         |         |
 * |     |  I  |                               |         |         |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_IntCtl		$12,1
#define R_C0_IntCtl		12
#define R_C0_SelIntCtl		1

#define S_IntCtlIPTI    29
#define M_IntCtlIPTI    (0x7 << S_IntCtlIPTI)
#define S_IntCtlIPPCI   26
#define M_IntCtlIPPCI   (0x7 << S_IntCtlIPPCI)
#define S_IntCtlVS      5
#define M_IntCtlVS      (0x1f << S_IntCtlVS)

#define M_IntCtl0Fields		0x03fffc1f
#define M_IntCtlRFields		0xfc000000

/*
 * Constants in the VS field
 */

#define K_IntCtlVS0	0x00				/* 0 bytes */
#define K_IntCtlVS32	0x01				/* 32 bytes */
#define K_IntCtlVS64	0x02				/* 64 bytes */
#define K_IntCtlVS128	0x04				/* 128 bytes */
#define K_IntCtlVS256	0x08				/* 256 bytes */
#define K_IntCtlVS512	0x10				/* 512 bytes */


/*
 ************************************************************************
 *          S R S C t l   R E G I S T E R   ( 1 2, SELECT 2 )           *
 ************************************************************************
 *   
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | 0 | HSS   |   0   | EICSS | 0 | ESS   | 0 |  PSS  | 0 | CSS   | : SRSCtl
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+                                             *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *
 */

#define C0_SRSCtl		$12,2
#define R_C0_SRSCtl		12
#define R_C0_SelSRSCtl		2

#define S_SRSCtlHSS		26			/* Highest shadow set (R) */
#define W_SRSCtlHSS		4
#define M_SRSCtlHSS		(0xf << S_SRSCtlHSS)
#define S_SRSCtlEICSS		18			/* Exception shadow set (R/W) */
#define W_SRSCtlEICSS		4
#define M_SRSCtlEICSS		(0xf << S_SRSCtlEICSS)
#define S_SRSCtlESS		12			/* Exception shadow set (R/W) */
#define W_SRSCtlESS		4
#define M_SRSCtlESS		(0xf << S_SRSCtlESS)
#define S_SRSCtlPSS		6			/* Previous shadow set (R/W) */
#define W_SRSCtlPSS		4
#define M_SRSCtlPSS		(0xf << S_SRSCtlPSS)
#define S_SRSCtlCSS		0
#define W_SRSCtlCSS		4
#define M_SRSCtlCSS		(0xf << S_SRSCtlCSS)	/* Current Shadow set (R/W) */

#define M_SRSCtl0Fields		0xc3c30c30
#define M_SRSCtlRFields		0x3c3c000f



/*
 ************************************************************************
 *          S R S Map   R E G I S T E R   ( 1 2, SELECT 3  )            *
 ************************************************************************
 *   
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | SSV7  |  SSV6 |  SSV5 |  SSV4 |  SSV3 |  SSV2 |  SSV1 |  SSV0 | SRSMap
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_SRSMap		$12, 3
#define R_C0_SRSMap		12
#define R_C0_SelSRSMap		3

#define S_SRSMapSSV7		28			/* Shadow Register for SSV7 */
#define W_SRSMapSSV7		4
#define M_SRSMapSSV7		(0xf << S_SRSMapSSV7)
#define S_SRSMapSSV6		24			/* Shadow Register for SSV6 */
#define W_SRSMapSSV6		4
#define M_SRSMapSSV6		(0xf << S_SRSMapSSV6)
#define S_SRSMapSSV5		20			/* Shadow Register for SSV5 */
#define W_SRSMapSSV5		4
#define M_SRSMapSSV5		(0xf << S_SRSMapSSV5)
#define S_SRSMapSSV4		16			/* Shadow Register for SSV4 */
#define W_SRSMapSSV4		4
#define M_SRSMapSSV4		(0xf << S_SRSMapSSV4)
#define S_SRSMapSSV3		12			/* Shadow Register for SSV3 */
#define W_SRSMapSSV3		4
#define M_SRSMapSSV3		(0xf << S_SRSMapSSV3)
#define S_SRSMapSSV2		8			/* Shadow Register for SSV2 */
#define W_SRSMapSSV2		4
#define M_SRSMapSSV2		(0xf << S_SRSMapSSV2)
#define S_SRSMapSSV1		4			/* Shadow Register for SSV1 */
#define W_SRSMapSSV1		4
#define M_SRSMapSSV1		(0xf << S_SRSMapSSV1)
#define S_SRSMapSSV0		0			/* Shadow Register for SSV0 */
#define W_SRSMapSSV0		4
#define M_SRSMapSSV0		(0xf << S_SRSMapSSV0)


#define M_SRSMap0Fields		0x00000000
#define M_SRSMapRFields		0xffffffff

/*
 ************************************************************************
 *          S R S H i   R E G I S T E R   ( 1 2, SELECT 4  )            *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |            0          | IPL12 | IPL11 | IPL10 |  IPL9 |  IPL8 |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_SRSHi		$12, 4
#define R_C0_SRSHi		12
#define R_C0_SelSRSHi		4

#define S_SRSHiIPL12		16			/* Shadow Register for IPL12 */
#define W_SRSHiIPL12		4
#define M_SRSHiIPL12		(0xf << S_SRSHiIPL12)
#define S_SRSHiIPL11		12			/* Shadow Register for IPL11 */
#define W_SRSHiIPL11		4
#define M_SRSHiIPL11		(0xf << S_SRSHiIPL11)
#define S_SRSHiIPL10		8			/* Shadow Register for IPL10 */
#define W_SRSHiIPL10		4
#define M_SRSHiIPL10		(0xf << S_SRSHiIPL10)
#define S_SRSHiIPL9		4			/* Shadow Register for IPL9  */
#define W_SRSHiIPL9		4
#define M_SRSHiIPL9		(0xf << S_SRSHiIPL9)
#define S_SRSHiIPL8		0			/* Shadow Register for IPL8  */
#define W_SRSHiIPL8		4
#define M_SRSHiIPL8		(0xf << S_SRSHiIPL8)

#define M_SRSHi0Fields		0xfff00000
#define M_SRSHiRFields		0x000fffff


#endif  /* Release2 */




/*
 ************************************************************************
 *                C A U S E   R E G I S T E R   ( 1 3 )                 *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | | |   | | |   |I|W| | | | | | |I|I|I|I|I|I|I|I| |         |   |
 * |B|0| C |0|0| 0 |V|P| | | | | | |P|P|P|P|P|P|P|P|0| ExcCode | 0 | Cause
 * |D| | E | | |   | | | | | | | | |7|6|5|4|3|2|1|0| |         |   |
 * | | |   | | |   | | | | | | | | | | | | | | | | | |         |   |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *    T     D P                    \---RIPL----/
 *    I     C C                      Release 2
 *            I
 */

#define C0_Cause		$13
#define R_C0_Cause		13
#define R_C0_SelCause	0
#define C0_CAUSE		C0_Cause		/* OBSOLETE - DO NOT USE IN NEW CODE */

#define S_CauseBD		31
#define M_CauseBD		(0x1 << S_CauseBD)
#define S_CauseCE		28
#define M_CauseCE		(0x3<< S_CauseCE)
#define S_CauseDC		27
#define M_CauseDC		(0x1 << S_CauseDC)
#define S_CauseIV		23
#define M_CauseIV		(0x1 << S_CauseIV)
#define S_CauseWP		22
#define M_CauseWP		(0x1 << S_CauseWP)


#define S_CauseIP		8
#define M_CauseIP		(0xff << S_CauseIP)
#define S_CauseIPEXT	10
#define M_CauseIPEXT	(0x3f << S_CauseIPEXT)

#define S_CausePCI      26
#define M_CausePCI      (0x1 << S_CausePCI)
#define S_CauseDC       27
#define M_CauseDC       (0x1 << S_CauseDC)
#define S_CauseTI       30
#define M_CauseTI       (0x1 << S_CauseTI)
#define S_CauseRIPL     10
#define M_CauseRIPL     (0x3f << S_CauseRIPL)

#define S_CauseIP13		21
#define M_CauseIP13		(0x1 << S_CauseIP13)
#define S_CauseIP12		20
#define M_CauseIP12		(0x1 << S_CauseIP12)
#define S_CauseIP11		19
#define M_CauseIP11		(0x1 << S_CauseIP10)
#define S_CauseIP10		18
#define M_CauseIP10		(0x1 << S_CauseIP9)
#define S_CauseIP9		17
#define M_CauseIP9		(0x1 << S_CauseIP8)
#define S_CauseIP8		16
#define M_CauseIP8		(0x1 << S_CauseIP7)

#define S_CauseIP7		15
#define M_CauseIP7		(0x1 << S_CauseIP7)
#define S_CauseIP6		14
#define M_CauseIP6		(0x1 << S_CauseIP6)
#define S_CauseIP5		13
#define M_CauseIP5		(0x1 << S_CauseIP5)
#define S_CauseIP4		12
#define M_CauseIP4		(0x1 << S_CauseIP4)
#define S_CauseIP3		11
#define M_CauseIP3		(0x1 << S_CauseIP3)
#define S_CauseIP2		10
#define M_CauseIP2		(0x1 << S_CauseIP2)
#define S_CauseIP1		9
#define M_CauseIP1		(0x1 << S_CauseIP1)
#define S_CauseIP0		8
#define M_CauseIP0		(0x1 << S_CauseIP0)
#define S_CauseExcCode	2
#define M_CauseExcCode	(0x1f << S_CauseExcCode)

#ifdef MIPS_Release2
#define M_Cause0FieldsR2	0x033f0083
#define M_CauseRFieldsR2	0xf400fc7c
#endif
#define M_Cause0Fields		0x4f3f0083
#define M_CauseRFields		0xb000fc7c

/*
 * Values in the CE field
 */
#define K_CauseCE0		0			/* Coprocessor 0 in the CE field */
#define K_CauseCE1		1			/* Coprocessor 1 in the CE field */
#define K_CauseCE2		2			/* Coprocessor 2 in the CE field */
#define K_CauseCE3		3			/* Coprocessor 3 in the CE field */

/*
 * Values in the ExcCode field
 */
#define	EX_INT			0			/* Interrupt */
#define	EXC_INT			(EX_INT << S_CauseExcCode)
#define	EX_MOD			1			/* TLB modified */
#define	EXC_MOD			(EX_MOD << S_CauseExcCode)
#define	EX_TLBL		    2			/* TLB exception (load or ifetch) */
#define	EXC_TLBL		(EX_TLBL << S_CauseExcCode)
#define	EX_TLBS		    3			/* TLB exception (store) */
#define	EXC_TLBS		(EX_TLBS << S_CauseExcCode)
#define	EX_ADEL		    4			/* Address error (load or ifetch) */
#define	EXC_ADEL		(EX_ADEL << S_CauseExcCode)
#define	EX_ADES		    5			/* Address error (store) */
#define	EXC_ADES		(EX_ADES << S_CauseExcCode)
#define	EX_IBE			6			/* Instruction Bus Error */
#define	EXC_IBE			(EX_IBE << S_CauseExcCode)
#define	EX_DBE			7			/* Data Bus Error */
#define	EXC_DBE			(EX_DBE << S_CauseExcCode)
#define	EX_SYS			8			/* Syscall */
#define	EXC_SYS			(EX_SYS << S_CauseExcCode)
#define	EX_SYSCALL		EX_SYS
#define	EXC_SYSCALL		EXC_SYS
#define	EX_BP			9			/* Breakpoint */
#define	EXC_BP			(EX_BP << S_CauseExcCode)
#define	EX_BREAK		EX_BP
#define	EXC_BREAK		EXC_BP
#define	EX_RI			10			/* Reserved instruction */
#define	EXC_RI			(EX_RI << S_CauseExcCode)
#define	EX_CPU			11			/* CoProcessor Unusable */
#define	EXC_CPU			(EX_CPU << S_CauseExcCode)
#define	EX_OV			12			/* OVerflow */
#define	EXC_OV			(EX_OV << S_CauseExcCode)
#define	EX_TR		    13			/* Trap instruction */
#define	EXC_TR			(EX_TR << S_CauseExcCode)
#define	EX_TRAP			EX_TR
#define	EXC_TRAP		EXC_TR
#define EX_FPE			15			/* floating point exception */
#define EXC_FPE			(EX_FPE << S_CauseExcCode)
#define EX_C2E			18			/* COP2 exception */
#define EXC_C2E			(EX_C2E << S_CauseExcCode)
#define EX_MDMX			22			/* MDMX exception */
#define EXC_MDMX		(EX_MDMX << S_CauseExcCode)
#define EX_WATCH		23			/* Watch exception */
#define EXC_WATCH		(EX_WATCH << S_CauseExcCode)
#define	EX_MCHECK	    24			/* Machine check exception */
#define	EXC_MCHECK 		(EX_MCHECK << S_CauseExcCode)
#define	EX_CacheErr	    30			/* Cache error caused re-entry to Debug Mode */
#define	EXC_CacheErr 	(EX_CacheErr << S_CauseExcCode)


/*
 ************************************************************************
 *                   E P C   R E G I S T E R   ( 1 4 )                  *
 ************************************************************************
 * 	
 *  6 // 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  3 // 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  //                        Exception PC                            | EPC
 * +-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_EPC			$14
#define R_C0_EPC		14
#define R_C0_SelEPC		0

#define M_EPC0Fields		0x00000000
#define M_EPCRFields		0x00000000
#define M_EPC0Fields64		UINT64_C(0x0000000000000000)
#define M_EPCRFields64		UINT64_C(0x0000000000000000)

/*
 ************************************************************************
 *                  P R I D   R E G I S T E R   ( 1 5 )                 *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Company Opts |   Company ID  |  Procesor ID  |   Revision    | PRId
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_PRId			$15
#define R_C0_PRId		15
#define R_C0_SelPRId		0
#define C0_PRID			C0_PRID			/* OBSOLETE - DO NOT USE IN NEW CODE */

#define S_PRIdCoOpt		24			/* Company options (R) */
#define M_PRIdCoOpt		(0xff << S_PRIdCoOpt)
#define S_PRIdCoID		16			/* Company ID (R) */
#define M_PRIdCoID		(0xff << S_PRIdCoID)
#define S_PRIdImp		8			/* Implementation ID (R) */
#define M_PRIdImp		(0xff << S_PRIdImp)
#define S_PRIdRev		0			/* Revision (R) */
#define M_PRIdRev		(0xff << S_PRIdRev)

#define M_PRId0Fields		0x00000000
#define M_PRIdRFields		0xffffffff
/*
 * Values in the Company ID field
 */
#define K_PRIdCoID_MIPS	1
#define K_PRIdCoID_Broadcom 2
#define K_PRIdCoID_Alchemy 3
#define K_PRIdCoID_SiByte 4
#define K_PRIdCoID_SandCraft 5
#define K_PRIdCoID_Philips 6
#define K_PRIdCoID_Toshiba 7
#define K_PRIdCoID_LSI 8
#define K_PRIdCoID_UNANNOUNCED9 9
#define K_PRIdCoID_UNANNOUNCED10 10
#define K_PRIdCoID_Lexra 11
#define K_PRIdCoID_NextAvailable 12 /* Next available encoding */


/*
 * Values in the implementation number field
 */
#define K_PRIdImp_4KC		0x80	/* MIPS32 4Kc with TLB MMU and Release 1 Architecture*/
#define K_PRIdImp_Jade		0x80	/*   Alternate (obsolete) name */
#define K_PRIdImp_5KC		0x81	/* MIPS64 5Kc/5Kf with TLB MMU and Release 1 Architecture */
#define K_PRIdImp_Opal		0x81	/*   Alternate (obsolete) name */
#define K_PRIdImp_20KC		0x82	/* MIPS64 20Kc with TLB MMU and Release 1 Architecture */
#define K_PRIdImp_Ruby		0x82	/*   Alternate (obsolete) name */
#define K_PRIdImp_4KMP		0x83	/* MIPS32 4Kp/4Km with FM MMU and Release 1 Architectur */
#define K_PRIdImp_JadeLite	0x83	/*   Alternate (obsolete) name */
#define K_PRIdImp_4KEc		0x84	/* MIPS32 4KEc with TLB MMU and Release 1 Architecture */
#define K_PRIdImp_4KEmp		0x85	/* MIPS32 4KEm/4KEp with FM MMU and Release 1 Architecture */
#define K_PRIdImp_4KSc		0x86	/* MIPS32 4KSc with TLB MMU and Release 1 Architecture */
#define K_PRIdImp_M4K		0x87	/* MIPS32 M4K with FM MMU and Release 2 Architecture */
#define K_PRIdImp_25Kf		0x88	/* MIPS64 25Kf with TLB MMU and Release 1 Architecture */
#define K_PRIdImp_Amethyst	0x88	/*   Alternate (obsolete) name */
#define K_PRIdImp_5KE		0x89	/* MIPS64 5KE with TLB MMU and Release 2 Architecture */
#define K_PRIdImp_4KEc_R2	0x90	/* MIPS32 4KEc with TLB MMU and Release 2 Architecture */
#define K_PRIdImp_4KEmp_R2	0x91	/* MIPS32 4KEm/4KEp with FM MMU and Release 2 Architecture */
#define K_PRIdImp_4KSd		0x92	/* MIPS32 4KSd with TLB MMU and Release 2 Architecture */

#define K_PRIdImp_24K		0x93	/* MIPS32 24K (Topaz) with Release 2 Architecture */
#define K_PRIdImp_Topaz		0x93	/*   Alternate (obsolete) name */
#define K_PRIdImp_TopazTLB	0x93	/*   Alternate (obsolete) name */

#define K_PRIdImp_R3000		0x01
#define K_PRIdImp_R4000		0x04
#define K_PRIdImp_R10000	0x09
#define K_PRIdImp_R4300		0x0b
#define K_PRIdImp_R5000		0x23
#define K_PRIdImp_R5200		0x28
#define K_PRIdImp_R5400		0x54

#ifdef MIPS_Release2
/*
 ************************************************************************
 *           E B A S E   R E G I S T E R   ( 1 5, SELECT 1 )            *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |1|0|           Exception Base          |0 0|       CPUNum      | EBase
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_EBase		$15,1
#define R_C0_EBase		15
#define R_C0_SelEBase		1

#define S_EBaseVA		12	 		/* Exception Base (R/W) */
#define M_EBaseVA		(0xfffff << S_EBaseVA)
#define S_EBaseCPUNum		0			/* CPU Number (R) */
#define M_EBaseCPUNum		(0x3ff << S_EBaseCPUNum)

#define M_EBase0Fields		0x40000C00
#define M_EBaseRFields		0x800003ff

#endif  

/*
 ************************************************************************
 *               C O N F I G   R E G I S T E R   ( 1 6 )                *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |M|                             |B| A |  A  |  M  |RSVD |V|  K  | Config
 * | | Reserved for Implementations|E| T |  R  |  T  |     |I|  0  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_Config		$16
#define R_C0_Config		16
#define R_C0_SelConfig		0
#define C0_CONFIG		C0_Config		/* OBSOLETE - DO NOT USE IN NEW CODE */


#define S_ConfigMore		31			/* Additional config registers present (R) */
#define M_ConfigMore		(0x1 << S_ConfigMore)
#define S_ConfigImpl		16			/* Implementation-specific fields */
#define M_ConfigImpl		(0x7fff << S_ConfigImpl)
#define S_ConfigBE		15			/* Denotes big-endian operation (R) */
#define M_ConfigBE		(0x1 << S_ConfigBE)
#define S_ConfigAT		13			/* Architecture type (R) */
#define M_ConfigAT		(0x3 << S_ConfigAT)
#define S_ConfigAR		10			/* Architecture revision (R) */
#define M_ConfigAR		(0x7 << S_ConfigAR)
#define S_ConfigMT		7			/* MMU Type (R) */
#define M_ConfigMT		(0x7 << S_ConfigMT)
#define S_ConfigVI		3			/* Icache is virtual (R) */
#define M_ConfigVI		(0x1 << S_ConfigVI)
#define S_ConfigK0		0			/* Kseg0 coherency algorithm (R/W) */
#define M_ConfigK0		(0x7 << S_ConfigK0)

/*
 * The following definitions are technically part of the "reserved for
 * implementations" field, but are the semi-standard definition used in
 * fixed-mapping MMUs to control the cacheability of kuseg and kseg2/3
 * references.  For that reason, they are included here, but may be
 * overridden by true implementation-specific definitions
 */
#define S_ConfigK23		28			/* Kseg2/3 coherency algorithm (FM MMU only) (R/W) */
#define M_ConfigK23		(0x7 << S_ConfigK23)
#define S_ConfigKU		25			/* Kuseg coherency algorithm (FM MMU only) (R/W) */
#define M_ConfigKU		(0x7 << S_ConfigKU)

#define M_Config0Fields		0x00000070
#define M_ConfigRFields		0x8000ff88

/*
 * Values in the AT field
 */
#define K_ConfigAT_MIPS32	0			/* MIPS32 */
#define K_ConfigAT_MIPS64S	1			/* MIPS64 with 32-bit addresses */
#define K_ConfigAT_MIPS64	2			/* MIPS64 with 32/64-bit addresses */
#define K_ConfigAT_MAX		2			/* Max value */

/*
 * Values in the AR field
 */

#define K_ConfigAR_Rel1		0			/* Release 1 of the architecture */
#define K_ConfigAR_Rel2		1			/* Release 2 of the architecture */

/*
 * Values in the MT field
 */
#define K_ConfigMT_NoMMU	0			/* No MMU */
#define K_ConfigMT_TLBMMU	1			/* Standard TLB MMU */
#define K_ConfigMT_BATMMU	2			/* Standard BAT MMU */
#define K_ConfigMT_FMTMMU	3			/* Standard FMT MMU */
#define K_ConfigMT_FMMMU	K_ConfigMT_FMTMMU       /* alias for compatibility */


/*
 ************************************************************************
 *         C O N F I G 1   R E G I S T E R   ( 1 6, SELECT 1 )          *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |M|  MMU Size |  IS |  IL |  IA |  DS |  DL |  DA |C|M|P|W|C|E|F| Config1
 * | |           |     |     |     |     |     |     |2|D|C|R|A|P|P|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_Config1		$16,1
#define R_C0_Config1		16
#define R_C0_SelConfig1		1

#define S_Config1M		31			/* Additional Config registers present (R) */
#define M_Config1M		(0x1 << S_Config1More)
#define S_Config1More		S_Config1M		/* OBSOLETE */
#define M_Config1More		(0x1 << S_Config1M)
#define S_Config1MMUSize 	25			/* Number of MMU entries - 1 (R) */
#define M_Config1MMUSize 	(0x3f << S_Config1MMUSize)
#define S_Config1IS		22			/* Icache sets per way (R) */
#define M_Config1IS		(0x7 << S_Config1IS)
#define S_Config1IL		19			/* Icache line size (R) */
#define M_Config1IL		(0x7 << S_Config1IL)
#define S_Config1IA		16			/* Icache associativity - 1 (R) */
#define M_Config1IA		(0x7 << S_Config1IA)
#define S_Config1DS		13			/* Dcache sets per way (R) */
#define M_Config1DS		(0x7 << S_Config1DS)
#define S_Config1DL		10			/* Dcache line size (R) */
#define M_Config1DL		(0x7 << S_Config1DL)
#define S_Config1DA		7			/* Dcache associativity (R) */
#define M_Config1DA		(0x7 << S_Config1DA)
#define S_Config1C2		6			/* Coprocessor 2 present (R) */
#define M_Config1C2		(0x1 << S_Config1C2)
#define S_Config1MD		5			/* Denotes MDMX present (R) */
#define M_Config1MD		(0x1 << S_Config1MD)
#define S_Config1PC		4			/* Denotes performance counters present (R) */
#define M_Config1PC		(0x1 << S_Config1PC)
#define S_Config1WR		3			/* Denotes watch registers present (R) */
#define M_Config1WR		(0x1 << S_Config1WR)
#define S_Config1CA		2			/* Denotes MIPS-16 present (R) */
#define M_Config1CA		(0x1 << S_Config1CA)
#define S_Config1EP		1			/* Denotes EJTAG present (R) */
#define M_Config1EP		(0x1 << S_Config1EP)
#define S_Config1FP		0			/* Denotes floating point present (R) */
#define M_Config1FP		(0x1 << S_Config1FP)

#define M_Config10Fields	0x00000000
#define M_Config1RFields	0xffffffff

/*
 * The following macro generates a table that is indexed
 * by the Icache or Dcache sets field in Config1 or the
 * Scache or Tcache sets field in Config2 and
 * contains the decoded value of sets per way
 */
#define Config1CacheSets()	\
	HALF(64);		\
	HALF(128);		\
	HALF(256);		\
	HALF(512);		\
	HALF(1024);		\
	HALF(2048);		\
	HALF(4096);		\
	HALF(8192);		\
	HALF(0);		\
	HALF(0);		\
	HALF(0);		\
	HALF(0);		\
	HALF(0);		\
	HALF(0);		\
	HALF(0);		\
	HALF(0);

/*
 * The following macro generates a table that is indexed
 * by the Icache or Dcache line size field in Config1 or
 * the Scache or Tcache line size field in Config2 and
 * contains the decoded value of the cache line size, in bytes
 */
#define Config1CacheLineSize()	\
	HALF(0);		\
	HALF(4);		\
	HALF(8);		\
	HALF(16);		\
	HALF(32);		\
	HALF(64);		\
	HALF(128);		\
	HALF(256);		\
	HALF(0);		\
	HALF(0);		\
	HALF(0);		\
	HALF(0);		\
	HALF(0);		\
	HALF(0);		\
	HALF(0);		\
	HALF(0);

/*
 ************************************************************************
 *         C O N F I G 2   R E G I S T E R   ( 1 6, SELECT 2 )          *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |M| TU  |  TS   |  TL   |  TA   |  SU |L|  SS   |  SL   |  SA   | Config2
 * | |     |       |       |       |     |2|       |       |       |
 * | |     |       |       |       |     |B|       |       |       |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_Config2		$16,2
#define R_C0_Config2		16
#define R_C0_SelConfig2		2

#define S_Config2M		31			/* Additional Config registers present (R) */
#define M_Config2M		(0x1 << S_Config2M)

#define M_Config20Fields	0xffffffff
#define M_Config2RFields	0x00000000

/*
 * The following definitions are not inside a MIPS_Release2 conditional
 * because a number of Release 1 chips have stanardized on this
 * definition.
 */
#define S_Config2TU             28
#define M_Config2TU             (0x7 << S_Config2TU)	/* Implementation-dependent tertiary cache control (R/W) */
#define S_Config2TS             24
#define M_Config2TS             (0xf << S_Config2TS)	/* Tertiary cache sets per way (R) */
#define S_Config2TL             20
#define M_Config2TL             (0xf << S_Config2TL)	/* Tertiary cache line size (R) */
#define S_Config2TA             16
#define M_Config2TA             (0xf << S_Config2TA)	/* Tertiary cache associativity (R) */

#define S_Config2SU             13
#define M_Config2SU             (0x7 << S_Config2SU)	/* Implementation-dependent secondary cache control (R/W) */
#define S_Config2L2B            12
#define M_Config2L2B            (0x1 << S_Config2L2B)	/* L2 bypass/L2_Bypassed (R/W) */

#define S_Config2SS             8
#define M_Config2SS             (0xf << S_Config2SS)	/* Secondary cache sets per way (R) */
#define S_Config2SL             4
#define M_Config2SL             (0xf << S_Config2SL)	/* Secondary cache line size (R) */
#define S_Config2SA             0
#define M_Config2SA             (0xf << S_Config2SA)	/* Secondary cache associativity (R) */



/*
 ************************************************************************
 *         C O N F I G 3   R E G I S T E R   ( 1 6, SELECT 3 )          *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | |                                             | |V|V| |   | | |
 * | |                                             |L|E|I| |   | | |
 * |M|                                             |P|I|n|S|   |S|T| Config3
 * | |                                             |A|C|t|P|   |M|L|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_Config3		$16,3
#define R_C0_Config3		16
#define R_C0_SelConfig3		3

#define S_Config3M		31			/* Additional Config registers present (R) */
#define M_Config3M		(0x1 << S_Config3M)
#define S_Config3SM		1			/* Denotes SmartMIPS ASE present (R) */
#define M_Config3SM		(0x1 << S_Config3SM)
#define S_Config3TL		0			/* Denotes Tracing Logic present (R) */
#define M_Config3TL		(0x1 << S_Config3TL)

#define S_Config3LPA  		7			/* Large Physical address support */
#define M_Config3LPA  		(0x1 << S_Config3LPA)
#define S_Config3VEIC  		6
#define M_Config3VEIC  		(0x1 << S_Config3VEIC)
#define S_Config3VInt  		5			/* External Interrupt controller support*/
#define M_Config3VInt  		(0x1 << S_Config3VInt)
#define S_Config3SP             4			/* Small Page & PageGrain present */
#define M_Config3SP             (0x1 << S_Config3SP)


#ifdef MIPS_Release2
#define M_Config30Fields	0xffffff00
#define M_Config3RFields	0x000000ff
#else
#define M_Config30Fields	0xfffffff0
#define M_Config3RFields	0x0000000f
#endif



/*
 ************************************************************************
 *         C O N F I G 7   R E G I S T E R   ( 1 6, SELECT 7 )          *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                           | | |             | |     | | | | | |
 * |                           |F| |             | |     |U| |R|B| |
 * |                           |P|A|             |E|     |L|B|P|H|S| Config7
 * |                           |R|R|             |S|     |B|P|S|T|L|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_Config7		$16,7
#define R_C0_Config7		16
#define R_C0_SelConfig7		7

#define S_Config7FPR		17			/* Denotes Floating Point Ratio (R) */
#define M_Config7FPR		(0x1 << S_Config7FPR)
#define S_Config7AR		16			/* Denotes Alias removed (R) */
#define M_Config7AR		(0x1 << S_Config7AR)
#define S_Config7ES		8			/* Denotes Externalize Sync (R/W) */
#define M_Config7ES		(0x1 << S_Config7ES)
#define S_Config7ULB		4			/* Denotes Uncached Loads Blocking (R/W) */
#define M_Config7ULB		(0x1 << S_Config7ULB)
#define S_Config7BP		3			/* Denotes Branch Prediction (R/W) */
#define M_Config7BP		(0x1 << S_Config7BP)
#define S_Config7RPS		2			/* Denotes Return Prediction Stack (R/W) */
#define M_Config7RPS		(0x1 << S_Config7RPS)
#define S_Config7BHT		1			/* Denotes Branch History Table (R/W) */
#define M_Config7BHT		(0x1 << S_Config7BHT)
#define S_Config7SL		0			/* Denotes Scheduled Loads (R/W) */
#define M_Config7SL		(0x1 << S_Config7SL)



/*
 ************************************************************************
 *                L L A D D R   R E G I S T E R   ( 1 7 )               *
 ************************************************************************
 * 	
 *  6 6    3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  3 2    1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |    //                      LL Physical Address                       | LLAddr
 * +-+-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_LLAddr		$17
#define R_C0_LLAddr		17
#define R_C0_SelLLAddr		0
#define C0_LLADDR		C0_LLAddr		/* OBSOLETE - DO NOT USE IN NEW CODE */

#define M_LLAddr0Fields		0x00000000
#define M_LLAddrRFields		0x00000000
#define M_LLAddr0Fields64	UINT64_C(0x0000000000000000)
#define M_LLAddrRFields64	UINT64_C(0x0000000000000000)


/*
 ************************************************************************
 *               W A T C H L O   R E G I S T E R   ( 1 8 )              *
 ************************************************************************
 * 	
 *  6 // 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  3 // 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  //                    Watch Virtual Address                 |I|R|W| WatchLo
 * +-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_WatchLo		$18
#define R_C0_WatchLo		18
#define R_C0_SelWatchLo		0
#define C0_WATCHLO		C0_WatchLo		/* OBSOLETE - DO NOT USE IN NEW CODE */

#define S_WatchLoVAddr		3			/* Watch virtual address (R/W) */
#define M_WatchLoVAddr		(0x1fffffff << S_WatchLoVAddr)
#define S_WatchLoI		2			/* Enable Istream watch (R/W) */
#define M_WatchLoI		(0x1 << S_WatchLoI)
#define S_WatchLoR		1			/* Enable data read watch (R/W) */
#define M_WatchLoR		(0x1 << S_WatchLoR)
#define S_WatchLoW		0			/* Enable data write watch (R/W) */
#define M_WatchLoW		(0x1 << S_WatchLoW)

#define M_WatchLo0Fields	0x00000000
#define M_WatchLoRFields	0x00000000
#define M_WatchLo0Fields64	UINT64_C(0x0000000000000000)
#define M_WatchLoRFields64	UINT64_C(0x0000000000000000)

#define M_WatchLoEnables	(M_WatchLoI | M_WatchLoR | M_WatchLoW)


/*
 ************************************************************************
 *               W A T C H H I   R E G I S T E R   ( 1 9 )              *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |M|G|    Rsvd   |      ASID     |  Rsvd |       Mask      |  0  | WatchHi
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_WatchHi		$19
#define R_C0_WatchHi		19
#define R_C0_SelWatchHi		0
#define C0_WATCHHI		C0_WatchHi		/* OBSOLETE - DO NOT USE IN NEW CODE */

#define S_WatchHiM		31			/* Denotes additional Watch registers present (R) */
#define M_WatchHiM		(0x1 << S_WatchHiM)
#define S_WatchHiG		30			/* Enable ASID-independent Watch match (R/W) */
#define M_WatchHiG		(0x1 << S_WatchHiG)
#define S_WatchHiASID		16			/* ASID value to match (R/W) */
#define M_WatchHiASID		(0xff << S_WatchHiASID)
#define S_WatchHiMask		3			/* Address inhibit mask (R/W) */
#define M_WatchHiMask		(0x1ff << S_WatchHiMask)

#ifdef MIPS_Release2
#define S_WatchHiI		2
#define M_WatchHiI		(0x1 << S_WatchHiI)
#define S_WatchHiR		1
#define M_WatchHiR		(0x1 << S_WatchHiR)
#define S_WatchHiW		0
#define M_WatchHiW		(0x1 << S_WatchHiW)

#define M_WatchHi0Fields	0x3f00f000
#define M_WatchHiRFields	0x80000000
#else
#define M_WatchHi0Fields	0x3f00f007
#define M_WatchHiRFields	0x80000000
#endif


/*
 ************************************************************************
 *             X C O N T E X T   R E G I S T E R   ( 2 0 )              *
 ************************************************************************
 * 	
 *  6 // 3 3 3 3 3 3 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  3 // 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  // PTEBase  | R |                      BadVPN2<39:13>                 |   0   | XContext
 * +-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_XContext		$20
#define R_C0_XContext		20
#define R_C0_SelXContext	0
#define C0_EXTCTXT		C0_XContext		/* OBSOLETE - DO NOT USE IN NEW CODE */

#define S_XContextBadVPN2	4			/* BadVPN2 (R) */
#define S_XContextBadVPN	S_XContextBadVPN2

#define M_XContext0Fields	0x0000000f


/*
 ************************************************************************
 *                 D E B U G   R E G I S T E R   ( 2 3 )                *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |D|D|N|L|D|H|C|I|M|C|D|I|D|D|     |         |N|S|   |D|D|D|D|D|D|
 * |B|M|o|S|o|a|o|B|C|a|B|E|D|D|EJTAG|DExcCode |o|S|   |I|I|D|D|B|S|
 * |D| |D|N|z|l|u|u|h|c|u|X|B|B| ver |         |S|t|   |N|B|B|B|p|S|
 * | | |C|M|e|t|n|s|e|h|s|I|S|L|     |         |S| | 0 |T| |S|L| | | Debug
 * | | |R| | | |t|E|c|e|E| |I|I|     |         |t| |   | | | | | | |
 * | | | | | | |D|P|k|E|P| |m|m|     |         | | |   | | | | | | |
 * | | | | | | |M| |P|P| | |p|p|     |         | | |   | | | | | | |
 * | | | | | | | | | | | | |r|r|     |         | | |   | | | | | | |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_Debug		$23	/* EJTAG */
#define R_C0_Debug		23
#define R_C0_SelDebug		0

#define S_DebugDBD		31			/* Debug branch delay (R) */
#define M_DebugDBD		(0x1 << S_DebugDBD)
#define S_DebugDM		30			/* Debug mode (R) */
#define M_DebugDM		(0x1 << S_DebugDM)
#define S_DebugNoDCR		29			/* No debug control register present (R) */
#define M_DebugNoDCR		(0x1 << S_DebugNoDCR)
#define S_DebugLSNM		28			/* Load/Store Normal Memory (R/W) */
#define M_DebugLSNM		(0x1 << S_DebugLSNM)
#define S_DebugDoze		27			/* Doze (R) */
#define M_DebugDoze		(0x1 << S_DebugDoze)
#define S_DebugHalt		26			/* Halt (R) */
#define M_DebugHalt		(0x1 << S_DebugHalt)
#define S_DebugCountDM		25			/* Count register behavior in debug mode (R/W) */
#define M_DebugCountDM		(0x1 << S_DebugCountDM)
#define S_DebugIBusEP		24			/* Imprecise Instn Bus Error Pending (R/W) */
#define M_DebugIBusEP		(0x1 << S_DebugIBusEP)
#define S_DebugMCheckP		23			/* Imprecise Machine Check Pending (R/W) */
#define M_DebugMCheckP		(0x1 << S_DebugMCheckP)
#define S_DebugCacheEP		22			/* Imprecise Cache Error Pending (R/W) */
#define M_DebugCacheEP		(0x1 << S_DebugCacheEP)
#define S_DebugDBusEP		21			/* Imprecise Data Bus Error Pending (R/W) */
#define M_DebugDBusEP		(0x1 << S_DebugDBusEP)
#define S_DebugIEXI		20			/* Imprecise Exception Inhibit (R/W) */
#define M_DebugIEXI		(0x1 << S_DebugIEXI)
#define S_DebugDDBSImpr		19			/* Debug data break store imprecise (R) */
#define M_DebugDDBSImpr		(0x1 << S_DebugDDBSImpr)
#define S_DebugDDBLImpr		18			/* Debug data break load imprecise (R) */
#define M_DebugDDBLImpr		(0x1 << S_DebugDDBLImpr)
#define S_DebugEJTAGver		15			/* EJTAG version number (R) */
#define M_DebugEJTAGver		(0x7 << S_DebugEJTAGver)
#define S_DebugDExcCode		10			/* Debug exception code (R) */
#define M_DebugDExcCode		(0x1f << S_DebugDExcCode)
#define S_DebugNoSSt		9			/* No single step implemented (R) */
#define M_DebugNoSSt		(0x1 << S_DebugNoSSt)
#define S_DebugSSt		8			/* Single step enable (R/W) */
#define M_DebugSSt		(0x1 << S_DebugSSt)
#define S_DebugDINT		5			/* Debug interrupt (R) */
#define M_DebugDINT		(0x1 << S_DebugDINT)
#define S_DebugDIB		4			/* Debug instruction break (R) */
#define M_DebugDIB		(0x1 << S_DebugDIB)
#define S_DebugDDBS		3			/* Debug data break store (R) */
#define M_DebugDDBS		(0x1 << S_DebugDDBS)
#define S_DebugDDBL		2			/* Debug data break load (R) */
#define M_DebugDDBL		(0x1 << S_DebugDDBL)
#define S_DebugDBp		1			/* Debug breakpoint (R) */
#define M_DebugDBp		(0x1 << S_DebugDBp)
#define S_DebugDSS		0			/* Debug single step (R) */
#define M_DebugDSS		(0x1 << S_DebugDSS)

#define M_Debug0Fields	0x01f000c0
#define M_DebugRFields	0xec0ffe3f


/*
 ************************************************************************
 *                 D E P C   R E G I S T E R   ( 2 4 )                  *
 ************************************************************************
 * 	
 *  6 // 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  3 // 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  //                  EJTAG Debug Exception PC                      | DEPC
 * +-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */


#define C0_DEPC			$24
#define R_C0_DEPC		24
#define R_C0_SelDEPC		0

#define M_DEEPC0Fields		0x00000000
#define M_DEEPCRFields		0x00000000
#define M_DEEPC0Fields64	UINT64_C(0x0000000000000000)
#define M_DEEPCRFields64	UINT64_C(0x0000000000000000)


/*
 ************************************************************************
 *              P E R F C N T   R E G I S T E R   ( 2 5 )               *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | |                                       |           |I| | | |E|
 * |M|                    0                  |   Event   |E|U|S|K|X| PerfCnt
 * | |                                       |           | | | | |L|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                          Event Count                          | PerfCnt
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_PerfCnt		$25
#define R_C0_PerfCnt		25
#define R_C0_SelPerfCnt		0
#define C0_PRFCNT0		C0_PerfCnt		/* OBSOLETE - DO NOT USE IN NEW CODE */
#define C0_PRFCNT1		C0_PerfCnt		/* OBSOLETE - DO NOT USE IN NEW CODE */

#define S_PerfCntM		31			/* More performance counters exist (R) */
#define M_PerfCntM		(1 << S_PerfCntM)
#define S_PerfCntEvent		5			/* Enabled event (R/W) */
#define M_PerfCntEvent		(0x3f << S_PerfCntEvent)
#define S_PerfCntIE		4			/* Interrupt Enable (R/W) */
#define M_PerfCntIE		(1 << S_PerfCntIE)
#define S_PerfCntU		3			/* Enable counting in User Mode (R/W) */
#define M_PerfCntU		(1 << S_PerfCntU)
#define S_PerfCntS		2			/* Enable counting in Supervisor Mode (R/W) */
#define M_PerfCntS		(1 << S_PerfCntS)
#define S_PerfCntK		1			/* Enable counting in Kernel Mode (R/W) */
#define M_PerfCntK		(1 << S_PerfCntK)
#define S_PerfCntEXL		0			/* Enable counting while EXL==1 (R/W) */
#define M_PerfCntEXL		(1 << S_PerfCntEXL)

#define M_PerfCnt0Fields	0x7ffff800
#define M_PerfCntRFields	0x80000000


/*
 ************************************************************************
 *               E R R C T L   R E G I S T E R   ( 2 6 )                *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                        Error Control                          | ErrCtl
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_ErrCtl		$26
#define R_C0_ErrCtl		26
#define R_C0_SelErrCtl		0
#define C0_ECC			$26		/* OBSOLETE - DO NOT USE IN NEW CODE */
#define R_C0_ECC		26		/* OBSOLETE - DO NOT USE IN NEW CODE */

#define M_ErrCtl0Fields		0x00000000
#define M_ErrCtlRFields		0x00000000


/*
 ************************************************************************
 *             C A C H E E R R   R E G I S T E R   ( 2 7 )              * CacheErr
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                     Cache Error Control                       | CacheErr
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_CacheErr		$27
#define R_C0_CacheErr		27
#define R_C0_SelCacheErr	0
#define C0_CACHE_ERR		C0_CacheErr		/* OBSOLETE - DO NOT USE IN NEW CODE */

#define M_CacheErr0Fields	0x00000000
#define M_CachErrRFields	0x00000000


/*
 ************************************************************************
 *                T A G L O   R E G I S T E R   ( 2 8 )                 * TagLo
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                            TagLo                              | TagLo
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_TagLo		$28
#define R_C0_TagLo		28
#define R_C0_SelTagLo		0
#define C0_TAGLO		C0_TagLo		/* OBSOLETE - DO NOT USE IN NEW CODE */

/*
 * Some implementations use separate TagLo registers for the
 * instruction and data caches.  In those cases, the following
 * definitions can be used in relevant code
 */

#define C0_ITagLo		$28,0
#define C0_DTagLo		$28,2

#define M_TagLo0Fields		0x00000000
#define M_TagLoRFields		0x00000000


/*
 ************************************************************************
 *        D A T A L O   R E G I S T E R   ( 2 8, SELECT 1 )             * DataLo
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                           DataLo                              | DataLo
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_DataLo		$28,1
#define R_C0_DataLo		28
#define R_C0_SelDataLo		1

/*
 * Some implementations use separate DataLo registers for the
 * instruction and data caches.  In those cases, the following
 * definitions can be used in relevant code
 */

#define C0_IDataLo		$28,1
#define C0_DDataLo		$28,3

#define M_DataLo0Fields		0x00000000
#define M_DataLoRFields		0xffffffff


/*
 ************************************************************************
 *                T A G H I   R E G I S T E R   ( 2 9 )                 * TagHi
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                            TagHi                              | TagHi
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_TagHi		$29
#define R_C0_TagHi		29
#define R_C0_SelTagHi		0
#define C0_TAGHI		C0_TagHi		/* OBSOLETE - DO NOT USE IN NEW CODE */

/*
 * Some implementations use separate TagHi registers for the
 * instruction and data caches.  In those cases, the following
 * definitions can be used in relevant code
 */

#define C0_ITagHi		$29,0
#define C0_DTagHi		$29,2

#define M_TagHi0Fields		0x00000000
#define M_TagHiRFields		0x00000000


/*
 ************************************************************************
 *        D A T A H I   R E G I S T E R   ( 2 9, SELECT 1 )             * DataHi
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                           DataHi                              | DataHi
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_DataHi		$29,1
#define R_C0_DataHi		29
#define R_C0_SelDataHi		1

/*
 * Some implementations use separate DataHi registers for the
 * instruction and data caches.  In those cases, the following
 * definitions can be used in relevant code
 */

#define C0_IDataHi		$29,1
#define C0_DDataHi		$29,3

#define M_DataHi0Fields		0x00000000
#define M_DataHiRFields		0xffffffff


/*
 ************************************************************************
 *            E R R O R E P C   R E G I S T E R   ( 3 0 )               *
 ************************************************************************
 * 	
 *  6 // 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  3 // 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  //                          Error PC                              | ErrorEPC
 * +-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_ErrorEPC		$30
#define R_C0_ErrorEPC		30
#define R_C0_SelErrorEPC	0
#define C0_ERROR_EPC		C0_ErrorEPC		/* OBSOLETE - DO NOT USE IN NEW CODE */

#define M_ErrorEPC0Fields	0x00000000
#define M_ErrorEPCRFields	0x00000000
#define M_ErrorEPC0Fields64	UINT64_C(0x0000000000000000)
#define M_ErrorEPCRFields64	UINT64_C(0x0000000000000000)


/*
 ************************************************************************
 *            D E S A V E   R E G I S T E R   ( 3 1 )                   *
 ************************************************************************
 * 	
 *  6 // 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  3 // 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  //                   EJTAG Register Save Value                    | DESAVE
 * +-+//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C0_DESAVE		$31
#define R_C0_DESAVE		31
#define R_C0_SelDESAVE		0

#define M_DESAVE0Fields		0x00000000
#define M_DESAVERFields		0x00000000
#define M_DESAVE0Fields64	UINT64_C(0x0000000000000000)
#define M_DESAVERFields64	UINT64_C(0x0000000000000000)


/*
 *************************************************************************
 *             C P 1   R E G I S T E R   D E F I N I T I O N S           *
 *************************************************************************
 */


/*
 *************************************************************************
 *                  H A R D W A R E   F P R   N A M E S                  *
 *************************************************************************
 */

#if defined(__ASSEMBLER__)
#define fp0			$f0
#define fp1			$f1
#define fp2			$f2
#define fp3			$f3
#define fp4			$f4
#define fp5			$f5
#define fp6			$f6
#define fp7			$f7
#define fp8			$f8
#define fp9			$f9
#define fp10			$f10
#define fp11			$f11
#define fp12			$f12
#define fp13			$f13
#define fp14			$f14
#define fp15			$f15
#define fp16			$f16
#define fp17			$f17
#define fp18			$f18
#define fp19			$f19
#define fp20			$f20
#define fp21			$f21
#define fp22			$f22
#define fp23			$f23
#define fp24			$f24
#define fp25			$f25
#define fp26			$f26
#define fp27			$f27
#define fp28			$f28
#define fp29			$f29
#define fp30			$f30
#define fp31			$f31
#endif

/*
 * The following definitions are used to convert an FPR name
 * into the corresponding even or odd name, respectively.
 * This is used in macro substitution in the AVPs.
 */

#if defined(__ASSEMBLER__)
#define fp1_even		$f0
#define fp3_even		$f2
#define fp5_even		$f4
#define fp7_even		$f6
#define fp9_even		$f8
#define fp11_even		$f10
#define fp13_even		$f12
#define fp15_even		$f14
#define fp17_even		$f16
#define fp19_even		$f18
#define fp21_even		$f20
#define fp23_even		$f22
#define fp25_even		$f24
#define fp27_even		$f26
#define fp29_even		$f28
#define fp31_even		$f30

#define fp0_odd			$f1
#define fp2_odd			$f3
#define fp4_odd			$f5
#define fp6_odd			$f7
#define fp8_odd			$f9
#define fp10_odd		$f11
#define fp12_odd		$f13
#define fp14_odd		$f15
#define fp16_odd		$f17
#define fp18_odd		$f19
#define fp20_odd		$f21
#define fp22_odd		$f23
#define fp24_odd		$f25
#define fp26_odd		$f27
#define fp28_odd		$f29
#define fp30_odd		$f31
#endif


/*
 *************************************************************************
 *                H A R D W A R E   F P R   I N D I C E S                *
 *************************************************************************
 *
 * These definitions provide the index (number) of the FPR, as opposed
 * to the assembler register name ($n).
 */

#define R_fp0			 0
#define R_fp1			 1
#define R_fp2			 2
#define R_fp3			 3
#define R_fp4			 4
#define R_fp5			 5
#define R_fp6			 6
#define R_fp7			 7
#define R_fp8			 8
#define R_fp9			 9
#define R_fp10			10
#define R_fp11			11
#define R_fp12			12
#define R_fp13			13
#define R_fp14			14
#define R_fp15			15
#define R_fp16			16
#define R_fp17			17
#define R_fp18			18
#define R_fp19			19
#define R_fp20			20
#define R_fp21			21
#define R_fp22			22
#define R_fp23			23
#define R_fp24			24
#define R_fp25			25
#define R_fp26			26
#define R_fp27			27
#define R_fp28			28
#define R_fp29			29
#define R_fp30			30
#define R_fp31			31


/*
 *************************************************************************
 *                  H A R D W A R E   F C R   N A M E S                  *
 *************************************************************************
 */

#if defined(__ASSEMBLER__)
#define fc0			$0
#define fc25			$25
#define fc26			$26
#define fc28			$28
#define fc31			$31
#endif


/*
 *************************************************************************
 *                H A R D W A R E   F C R   I N D I C E S                *
 *************************************************************************
 *
 * These definitions provide the index (number) of the FCR, as opposed
 * to the assembler register name ($n).
 */

#define R_fc0			 0
#define R_fc25			25
#define R_fc26			26
#define R_fc28			28
#define R_fc31			31


/*
 *************************************************************************
 *                  H A R D W A R E   F C C   N A M E S                  *
 *************************************************************************
 */

#if defined(__ASSEMBLER__)
#define cc0			$fcc0
#define cc1			$fcc1
#define cc2			$fcc2
#define cc3			$fcc3
#define cc4			$fcc4
#define cc5			$fcc5
#define cc6			$fcc6
#define cc7			$fcc7
#endif


/*
 *************************************************************************
 *                H A R D W A R E   F C C   I N D I C E S                *
 *************************************************************************
 *
 * These definitions provide the index (number) of the CC, as opposed
 * to the assembler register name ($n).
 */

#define R_cc0			0
#define R_cc1			1
#define R_cc2			2
#define R_cc3			3
#define R_cc4			4
#define R_cc5			5
#define R_cc6			6
#define R_cc7			7


/*
 ************************************************************************
 *             I M P L E M E N T A T I O N   R E G I S T E R            *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |       |       | |F| | |3|P| | |               |               |
 * | Rsvd  | Impl  | |6|L|W|D|S|D|S| Implementation|   Revision    | FIR
 * |       |       | |4| | | | | | |               |               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C1_FIR			$0
#define R_C1_FIR			0

#ifdef MIPS_Release2
#define S_FIRConfigF64		22
#define M_FIRConfigF64		(0x1 << S_FIRConfigF64)
#define S_FIRConfigL		21
#define M_FIRConfigL		(0x1 << S_FIRConfigL)
#define S_FIRConfigW		20
#define M_FIRConfigW	   	(0x1 << S_FIRConfigW)
#endif
#define S_FIRConfig3D		19
#define M_FIRConfig3D		(0x1 << S_FIRConfig3D)
#define S_FIRConfigPS		18
#define M_FIRConfigPS   	(0x1 << S_FIRConfigPS)
#define S_FIRConfigD		17
#define M_FIRConfigD		(0x1 << S_FIRConfigD)
#define S_FIRConfigS		16
#define M_FIRConfigS		(0x1 << S_FIRConfigS)
#ifdef MIPS_Release2
#define M_FIRConfigAll		(M_FIRConfigS|M_FIRConfigD|M_FIRConfigPS|M_FIRConfig3D|M_FIRConfigW|M_FIRConfigL|M_FIRConfigF64)
#else
#define M_FIRConfigAll		(M_FIRConfigS|M_FIRConfigD|M_FIRConfigPS|M_FIRConfig3D)
#endif
#define S_FIRConfigAll		16

#define S_FIRImp		8
#define M_FIRImp		(0xff << S_FIRImp)

#define S_FIRRev		0
#define M_FIRRev		(0xff << S_FIRRev)

#ifdef MIPS_Release2
#define M_FIR0FieldsR2		0xf0800000
#define M_FIRRFieldsR2		0x007fffff
#endif
#define M_FIR0Fields		0xfff00000
#define M_FIRRFields		0x000fffff

/*
 ************************************************************************
 *          C O N D I T I O N   C O D E S   R E G I S T E R             *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                      0                        |      CC       | FCCR
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C1_FCCR			$25
#define R_C1_FCCR		25

#define S_FCCRCC		0
#define M_FCCRCC		(0xff << S_FCCRCC)
#define S_FCCRCC7		7
#define M_FCCRCC7		(0x1 << S_FCCRCC7)
#define S_FCCRCC6		6
#define M_FCCRCC6		(0x1 << S_FCCRCC6)
#define S_FCCRCC5		5
#define M_FCCRCC5		(0x1 << S_FCCRCC5)
#define S_FCCRCC4		4
#define M_FCCRCC4		(0x1 << S_FCCRCC4)
#define S_FCCRCC3		3
#define M_FCCRCC3		(0x1 << S_FCCRCC3)
#define S_FCCRCC2		2
#define M_FCCRCC2		(0x1 << S_FCCRCC2)
#define S_FCCRCC1		1
#define M_FCCRCC1		(0x1 << S_FCCRCC1)
#define S_FCCRCC0		0
#define M_FCCRCC0		(0x1 << S_FCCRCC0)

#define M_FCCR0Fields		0xffffff00
#define M_FCCRRFields		0x000000ff


/*
 ************************************************************************
 *                 E X C E P T I O N S   R E G I S T E R                *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |             0             |   Cause   |    0    |  Flags  | 0 | FEXR
 * |                           |E|V|Z|O|U|I|         |V|Z|O|U|I|   |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C1_FEXR			$26
#define R_C1_FEXR		26

#define S_FEXRExc		12
#define M_FEXRExc		(0x3f << S_FEXRExc)
#define S_FEXRExcE		17
#define M_FEXRExcE		(0x1 << S_FEXRExcE)
#define S_FEXRExcV		16
#define M_FEXRExcV		(0x1 << S_FEXRExcV)
#define S_FEXRExcZ		15
#define M_FEXRExcZ		(0x1 << S_FEXRExcZ)
#define S_FEXRExcO		14
#define M_FEXRExcO		(0x1 << S_FEXRExcO)
#define S_FEXRExcU		13
#define M_FEXRExcU		(0x1 << S_FEXRExcU)
#define S_FEXRExcI		12
#define M_FEXRExcI		(0x1 << S_FEXRExcI)

#define S_FEXRFlg		2
#define M_FEXRFlg		(0x1f << S_FEXRFlg)
#define S_FEXRFlgV		6
#define M_FEXRFlgV		(0x1 << S_FEXRFlgV)
#define S_FEXRFlgZ		5
#define M_FEXRFlgZ		(0x1 << S_FEXRFlgZ)
#define S_FEXRFlgO		4
#define M_FEXRFlgO		(0x1 << S_FEXRFlgO)
#define S_FEXRFlgU		3
#define M_FEXRFlgU		(0x1 << S_FEXRFlgU)
#define S_FEXRFlgI		2
#define M_FEXRFlgI		(0x1 << S_FEXRFlgI)

#define M_FEXR0Fields		0xfffc0f83
#define M_FEXRRFields		0x00000000


/*
 ************************************************************************
 *                    E N A B L E S   R E G I S T E R                   *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                   0                   | Enables |   0   |F|RM | FENR
 * |                                       |V|Z|O|U|I|       |S|   |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C1_FENR			$28
#define R_C1_FENR		28

#define S_FENREna		7
#define M_FENREna		(0x1f << S_FENREna)
#define S_FENREnaV		11
#define M_FENREnaV		(0x1 << S_FENREnaV)
#define S_FENREnaZ		10
#define M_FENREnaZ		(0x1 << S_FENREnaZ)
#define S_FENREnaO		9
#define M_FENREnaO		(0x1 << S_FENREnaO)
#define S_FENREnaU		8
#define M_FENREnaU		(0x1 << S_FENREnaU)
#define S_FENREnaI		7
#define M_FENREnaI		(0x1 << S_FENREnaI)

#define S_FENRFS		2
#define M_FENRFS		(0x1 << S_FENRFS)

#define S_FENRRM		0
#define M_FENRRM		(0x3 << S_FENRRM)

#define M_FENR0Fields		0xfffff078
#define M_FENRRFields		0x00000000


/*
 ************************************************************************
 *           C O N T R O L  /  S T A T U S   R E G I S T E R            *
 ************************************************************************
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |     FCC     |F|C|Imp|  0  |   Cause   | Enables |  Flags  | RM| FCSR
 * |7|6|5|4|3|2|1|S|C|   |     |E|V|Z|O|U|I|V|Z|O|U|I|V|Z|O|U|I|   |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define C1_FCSR			$31
#define R_C1_FCSR		31

#define S_FCSRFCC7_1		25			/* Floating point condition codes 7..1 (R/W) */
#define M_FCSRFCC7_1		(0x7f << S_FCSRFCC7_1)
#define S_FCSRCC7		31
#define M_FCSRCC7		(0x1 << S_FCSRCC7)
#define S_FCSRCC6		30
#define M_FCSRCC6		(0x1 << S_FCSRCC6)
#define S_FCSRCC5		29
#define M_FCSRCC5		(0x1 << S_FCSRCC5)
#define S_FCSRCC4		28
#define M_FCSRCC4		(0x1 << S_FCSRCC4)
#define S_FCSRCC3		27
#define M_FCSRCC3		(0x1 << S_FCSRCC3)
#define S_FCSRCC2		26
#define M_FCSRCC2		(0x1 << S_FCSRCC2)
#define S_FCSRCC1		25
#define M_FCSRCC1		(0x1 << S_FCSRCC1)

#define S_FCSRFS		24			/* Flush denorms to zero (R/W) */
#define M_FCSRFS		(0x1 << S_FCSRFS)

#define S_FCSRCC0		23			/* Floating point condition code 0 (R/W) */
#define M_FCSRCC0		(0x1 << S_FCSRCC0)
#define S_FCSRCC		S_FCSRCC0
#define M_FCSRCC		M_FCSRCC0

#define S_FCSRImpl		21			/* Implementation-specific control bits (R/W) */
#define M_FCSRImpl		(0x3 << S_FCSRImpl)

#define S_FCSRExc		12			/* Exception cause (R/W) */
#define M_FCSRExc		(0x3f << S_FCSRExc)
#define S_FCSRExcE		17
#define M_FCSRExcE		(0x1 << S_FCSRExcE)
#define S_FCSRExcV		16
#define M_FCSRExcV		(0x1 << S_FCSRExcV)
#define S_FCSRExcZ		15
#define M_FCSRExcZ		(0x1 << S_FCSRExcZ)
#define S_FCSRExcO		14
#define M_FCSRExcO		(0x1 << S_FCSRExcO)
#define S_FCSRExcU		13
#define M_FCSRExcU		(0x1 << S_FCSRExcU)
#define S_FCSRExcI		12
#define M_FCSRExcI		(0x1 << S_FCSRExcI)

#define S_FCSREna		7			/* Exception enable (R/W) */
#define M_FCSREna		(0x1f << S_FCSREna)
#define S_FCSREnaV		11
#define M_FCSREnaV		(0x1 << S_FCSREnaV)
#define S_FCSREnaZ		10
#define M_FCSREnaZ		(0x1 << S_FCSREnaZ)
#define S_FCSREnaO		9
#define M_FCSREnaO		(0x1 << S_FCSREnaO)
#define S_FCSREnaU		8
#define M_FCSREnaU		(0x1 << S_FCSREnaU)
#define S_FCSREnaI		7
#define M_FCSREnaI		(0x1 << S_FCSREnaI)

#define S_FCSRFlg		2			/* Exception flags (R/W) */
#define M_FCSRFlg		(0x1f << S_FCSRFlg)
#define S_FCSRFlgV		6
#define M_FCSRFlgV		(0x1 << S_FCSRFlgV)
#define S_FCSRFlgZ		5
#define M_FCSRFlgZ		(0x1 << S_FCSRFlgZ)
#define S_FCSRFlgO		4
#define M_FCSRFlgO		(0x1 << S_FCSRFlgO)
#define S_FCSRFlgU		3
#define M_FCSRFlgU		(0x1 << S_FCSRFlgU)
#define S_FCSRFlgI		2
#define M_FCSRFlgI		(0x1 << S_FCSRFlgI)

#define S_FCSRRM		0			/* Rounding mode (R/W) */
#define M_FCSRRM		(0x3 << S_FCSRRM)

#define M_FCSR0Fields		0x001c0000
#define M_FCSRRFields		0x00000000

/*
 * Values in the rounding mode field (of both FCSR and FCCR)
 */
#define K_FCSRRM_RN		0
#define K_FCSRRM_RZ		1
#define K_FCSRRM_RP		2
#define K_FCSRRM_RM		3


/*
 * Floating point data format
 * 	
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |S|    exponent   |                  fraction                   |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define	S_FP_SINGLE_SIGN	31
#define	M_FP_SINGLE_SIGN	(0x1 << S_FP_SINGLE_SIGN)
#define	S_FP_SINGLE_EXPO	23
#define	M_FP_SINGLE_EXPO	(0xff << S_FP_SINGLE_SIGN)
#define	S_FP_SINGLE_FRAC	0
#define	M_FP_SINGLE_FRAC	(0x7fffff << S_FP_SINGLE_SIGN)
#define	S_FP_DOUBLE_SIGN	63
#define	M_FP_DOUBLE_SIGN	(UINT64_C(0x1) << S_FP_DOUBLE_SIGN)
#define	S_FP_DOUBLE_EXPO	52
#define	M_FP_DOUBLE_EXPO	(UINT64_C(0x7ff) << S_FP_DOUBLE_SIGN)
#define	S_FP_DOUBLE_FRAC	0
#define	M_FP_DOUBLE_FRAC	(UINT64_C(0xfffffffffffff) << S_FP_DOUBLE_SIGN)
/* only upper half, use ?_FP_SINGLE_* for lower half */
#define	S_FP_PAIREDSINGLE_SIGN	63
#define	M_FP_PAIREDSINGLE_SIGN	(UINT64_C(0x1) << S_FP_PAIREDSINGLE_SIGN)
#define	S_FP_PAIREDSINGLE_EXPO	52
#define	M_FP_PAIREDSINGLE_EXPO	(UINT64_C(0xff) << S_FP_PAIREDSINGLE_SIGN)
#define	S_FP_PAIREDSINGLE_FRAC	32
#define	M_FP_PAIREDSINGLE_FRAC	(UINT64_C(0x7fffff) << S_FP_PAIREDSINGLE_SIGN)

/*
 * fixed point data format
 */
#define S_FIX_WORD_SIGN 	31
#define M_FIX_WORD_SIGN 	(0x1 << S_FIX_WORD_SIGN)
#define S_FIX_WORD_VALUE	0
#define M_FIX_WORD_VALUE	(0x7fffffff << S_FIX_WORD_VALUE)
#define S_FIX_LONG_SIGN 	63
#define M_FIX_LONG_SIGN 	(UINT64_C(0x1) << S_FIX_LONG_SIGN)
#define S_FIX_LONG_VALUE	0
#define M_FIX_LONG_VALUE	(UINT64_C(0x7fffffffffffffff) << S_FIX_LONG_VALUE)

#endif /* _ArchDefs_h_ */
