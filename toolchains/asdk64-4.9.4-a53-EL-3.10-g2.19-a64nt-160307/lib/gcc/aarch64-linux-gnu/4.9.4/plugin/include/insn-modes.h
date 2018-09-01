/* Generated automatically from machmode.def and config/aarch64/aarch64-modes.def
   by genmodes.  */

#ifndef GCC_INSN_MODES_H
#define GCC_INSN_MODES_H

enum machine_mode
{
  VOIDmode,                /* machmode.def:172 */
  BLKmode,                 /* machmode.def:176 */
  CCmode,                  /* machmode.def:209 */
  CCFPmode,                /* config/aarch64/aarch64-modes.def:21 */
  CCFPEmode,               /* config/aarch64/aarch64-modes.def:22 */
  CC_SWPmode,              /* config/aarch64/aarch64-modes.def:23 */
  CC_ZESWPmode,            /* config/aarch64/aarch64-modes.def:24 */
  CC_SESWPmode,            /* config/aarch64/aarch64-modes.def:25 */
  CC_NZmode,               /* config/aarch64/aarch64-modes.def:26 */
  CC_Zmode,                /* config/aarch64/aarch64-modes.def:27 */
  BImode,                  /* machmode.def:179 */
  QImode,                  /* machmode.def:187 */
  HImode,                  /* machmode.def:188 */
  SImode,                  /* machmode.def:189 */
  DImode,                  /* machmode.def:190 */
  TImode,                  /* machmode.def:191 */
  EImode,                  /* config/aarch64/aarch64-modes.def:41 */
  OImode,                  /* config/aarch64/aarch64-modes.def:37 */
  CImode,                  /* config/aarch64/aarch64-modes.def:42 */
  XImode,                  /* config/aarch64/aarch64-modes.def:43 */
  QQmode,                  /* machmode.def:212 */
  HQmode,                  /* machmode.def:213 */
  SQmode,                  /* machmode.def:214 */
  DQmode,                  /* machmode.def:215 */
  TQmode,                  /* machmode.def:216 */
  UQQmode,                 /* machmode.def:218 */
  UHQmode,                 /* machmode.def:219 */
  USQmode,                 /* machmode.def:220 */
  UDQmode,                 /* machmode.def:221 */
  UTQmode,                 /* machmode.def:222 */
  HAmode,                  /* machmode.def:224 */
  SAmode,                  /* machmode.def:225 */
  DAmode,                  /* machmode.def:226 */
  TAmode,                  /* machmode.def:227 */
  UHAmode,                 /* machmode.def:229 */
  USAmode,                 /* machmode.def:230 */
  UDAmode,                 /* machmode.def:231 */
  UTAmode,                 /* machmode.def:232 */
  SFmode,                  /* machmode.def:202 */
  DFmode,                  /* machmode.def:203 */
  FSFmode,                 /* machmode.def:204 */
  FDFmode,                 /* machmode.def:205 */
  TFmode,                  /* config/aarch64/aarch64-modes.def:56 */
  SDmode,                  /* machmode.def:244 */
  DDmode,                  /* machmode.def:245 */
  TDmode,                  /* machmode.def:246 */
  CQImode,                 /* machmode.def:240 */
  CHImode,                 /* machmode.def:240 */
  CSImode,                 /* machmode.def:240 */
  CDImode,                 /* machmode.def:240 */
  CTImode,                 /* machmode.def:240 */
  CEImode,                 /* machmode.def:240 */
  COImode,                 /* machmode.def:240 */
  CCImode,                 /* machmode.def:240 */
  CXImode,                 /* machmode.def:240 */
  SCmode,                  /* machmode.def:241 */
  DCmode,                  /* machmode.def:241 */
  FSCmode,                 /* machmode.def:241 */
  FDCmode,                 /* machmode.def:241 */
  TCmode,                  /* machmode.def:241 */
  V8QImode,                /* config/aarch64/aarch64-modes.def:30 */
  V4HImode,                /* config/aarch64/aarch64-modes.def:30 */
  V2SImode,                /* config/aarch64/aarch64-modes.def:30 */
  V16QImode,               /* config/aarch64/aarch64-modes.def:31 */
  V8HImode,                /* config/aarch64/aarch64-modes.def:31 */
  V4SImode,                /* config/aarch64/aarch64-modes.def:31 */
  V2DImode,                /* config/aarch64/aarch64-modes.def:31 */
  V32QImode,               /* config/aarch64/aarch64-modes.def:46 */
  V16HImode,               /* config/aarch64/aarch64-modes.def:46 */
  V8SImode,                /* config/aarch64/aarch64-modes.def:46 */
  V4DImode,                /* config/aarch64/aarch64-modes.def:46 */
  V2TImode,                /* config/aarch64/aarch64-modes.def:46 */
  V48QImode,               /* config/aarch64/aarch64-modes.def:49 */
  V24HImode,               /* config/aarch64/aarch64-modes.def:49 */
  V12SImode,               /* config/aarch64/aarch64-modes.def:49 */
  V6DImode,                /* config/aarch64/aarch64-modes.def:49 */
  V3TImode,                /* config/aarch64/aarch64-modes.def:49 */
  V2EImode,                /* config/aarch64/aarch64-modes.def:49 */
  V64QImode,               /* config/aarch64/aarch64-modes.def:52 */
  V32HImode,               /* config/aarch64/aarch64-modes.def:52 */
  V16SImode,               /* config/aarch64/aarch64-modes.def:52 */
  V8DImode,                /* config/aarch64/aarch64-modes.def:52 */
  V4TImode,                /* config/aarch64/aarch64-modes.def:52 */
  V2OImode,                /* config/aarch64/aarch64-modes.def:52 */
  V2SFmode,                /* config/aarch64/aarch64-modes.def:32 */
  V1DFmode,                /* config/aarch64/aarch64-modes.def:34 */
  V4SFmode,                /* config/aarch64/aarch64-modes.def:33 */
  V2DFmode,                /* config/aarch64/aarch64-modes.def:33 */
  V8SFmode,                /* config/aarch64/aarch64-modes.def:47 */
  V4DFmode,                /* config/aarch64/aarch64-modes.def:47 */
  V12SFmode,               /* config/aarch64/aarch64-modes.def:50 */
  V6DFmode,                /* config/aarch64/aarch64-modes.def:50 */
  V16SFmode,               /* config/aarch64/aarch64-modes.def:53 */
  V8DFmode,                /* config/aarch64/aarch64-modes.def:53 */
  MAX_MACHINE_MODE,

  MIN_MODE_RANDOM = VOIDmode,
  MAX_MODE_RANDOM = BLKmode,

  MIN_MODE_CC = CCmode,
  MAX_MODE_CC = CC_Zmode,

  MIN_MODE_INT = QImode,
  MAX_MODE_INT = XImode,

  MIN_MODE_PARTIAL_INT = VOIDmode,
  MAX_MODE_PARTIAL_INT = VOIDmode,

  MIN_MODE_FRACT = QQmode,
  MAX_MODE_FRACT = TQmode,

  MIN_MODE_UFRACT = UQQmode,
  MAX_MODE_UFRACT = UTQmode,

  MIN_MODE_ACCUM = HAmode,
  MAX_MODE_ACCUM = TAmode,

  MIN_MODE_UACCUM = UHAmode,
  MAX_MODE_UACCUM = UTAmode,

  MIN_MODE_FLOAT = SFmode,
  MAX_MODE_FLOAT = TFmode,

  MIN_MODE_DECIMAL_FLOAT = SDmode,
  MAX_MODE_DECIMAL_FLOAT = TDmode,

  MIN_MODE_COMPLEX_INT = CQImode,
  MAX_MODE_COMPLEX_INT = CXImode,

  MIN_MODE_COMPLEX_FLOAT = SCmode,
  MAX_MODE_COMPLEX_FLOAT = TCmode,

  MIN_MODE_VECTOR_INT = V8QImode,
  MAX_MODE_VECTOR_INT = V2OImode,

  MIN_MODE_VECTOR_FRACT = VOIDmode,
  MAX_MODE_VECTOR_FRACT = VOIDmode,

  MIN_MODE_VECTOR_UFRACT = VOIDmode,
  MAX_MODE_VECTOR_UFRACT = VOIDmode,

  MIN_MODE_VECTOR_ACCUM = VOIDmode,
  MAX_MODE_VECTOR_ACCUM = VOIDmode,

  MIN_MODE_VECTOR_UACCUM = VOIDmode,
  MAX_MODE_VECTOR_UACCUM = VOIDmode,

  MIN_MODE_VECTOR_FLOAT = V2SFmode,
  MAX_MODE_VECTOR_FLOAT = V8DFmode,

  NUM_MACHINE_MODES = MAX_MACHINE_MODE
};

#define CONST_MODE_SIZE const
#define CONST_MODE_BASE_ALIGN const
#define CONST_MODE_IBIT const
#define CONST_MODE_FBIT const

#define BITS_PER_UNIT (8)
#define MAX_BITSIZE_MODE_ANY_INT (64*BITS_PER_UNIT)
#define MAX_BITSIZE_MODE_ANY_MODE (128*BITS_PER_UNIT)

#endif /* insn-modes.h */
