/* IFUNC resolver function for CPU specific functions.
   64 bit S/390 version.
   Copyright (C) 2012-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <unistd.h>
#include <dl-procinfo.h>

#define STFLE_BITS_Z10  34 /* General instructions extension */
#define STFLE_BITS_Z196 45 /* Distinct operands, pop ... */

#ifndef NOT_IN_libc

#define IFUNC_RESOLVE(FUNC)						\
  asm (".globl " #FUNC "\n\t"						\
       ".type  " #FUNC ",@gnu_indirect_function\n\t"			\
       ".set   " #FUNC ",resolve_" #FUNC "\n\t"				\
       ".globl __GI_" #FUNC "\n\t"					\
       ".set   __GI_" #FUNC "," #FUNC "\n");				\
									\
  /* Make the declarations of the optimized functions hidden in order
     to prevent GOT slots being generated for them. */			\
  extern void *FUNC##_z196 attribute_hidden;				\
  extern void *FUNC##_z10 attribute_hidden;				\
  extern void *FUNC##_z900 attribute_hidden;				\
									\
  void *resolve_##FUNC (unsigned long int dl_hwcap)			\
  {									\
    if (dl_hwcap & HWCAP_S390_STFLE)					\
      {									\
	/* We want just 1 double word to be returned.  */		\
	register unsigned long reg0 asm("0") = 0;			\
	unsigned long stfle_bits;					\
									\
	asm volatile(".machine push"        "\n\t"			\
		     ".machine \"z9-109\""  "\n\t"			\
		     "stfle %0"             "\n\t"			\
		     ".machine pop"         "\n"			\
		     : "=QS" (stfle_bits), "+d" (reg0)			\
		     : : "cc");						\
									\
	if ((stfle_bits & (1UL << (63 - STFLE_BITS_Z196))) != 0)	\
	  return &FUNC##_z196;						\
	else if ((stfle_bits & (1UL << (63 - STFLE_BITS_Z10))) != 0)	\
	  return &FUNC##_z10;						\
	else								\
	  return &FUNC##_z900;						\
      }									\
    else								\
      return &FUNC##_z900;						\
  }

IFUNC_RESOLVE(memset)
IFUNC_RESOLVE(memcmp)
asm(".weak bcmp ; bcmp = memcmp");

/* In the static lib memcpy is needed before the reloc is resolved.  */
#ifdef SHARED
IFUNC_RESOLVE(memcpy)
#endif

#endif
