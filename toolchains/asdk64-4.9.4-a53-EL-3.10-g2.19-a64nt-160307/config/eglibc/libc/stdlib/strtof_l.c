/* Convert string representing a number to float value, using given locale.
   Copyright (C) 1997-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.

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

#include <xlocale.h>

extern float ____strtof_l_internal (const char *, char **, int, __locale_t);
extern unsigned long long int ____strtoull_l_internal (const char *, char **,
						       int, int, __locale_t);

#define	FLOAT		float
#define	FLT		FLT
#ifdef USE_WIDE_CHAR
# define STRTOF		wcstof_l
# define __STRTOF	__wcstof_l
#else
# define STRTOF		strtof_l
# define __STRTOF	__strtof_l
#endif
#define	MPN2FLOAT	__mpn_construct_float
#define	FLOAT_HUGE_VAL	HUGE_VALF
#define SET_MANTISSA(flt, mant) \
  do { union ieee754_float u;						      \
       u.f = (flt);							      \
       u.ieee_nan.mantissa = (mant);					      \
       if (u.ieee.mantissa != 0)					      \
	 (flt) = u.f;							      \
  } while (0)

#include "strtod_l.c"
