/* Copyright (C) 1999-2014 Free Software Foundation, Inc.
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

#include <math.h>

/* The actual implementation for all floating point sizes is in strtod.c.
   These macros tell it to produce the `long double' version, `strtold'.  */

#define FLOAT		long double
#define FLT		LDBL
#ifdef USE_WIDE_CHAR
# define STRTOF		wcstold_l
# define __STRTOF	__wcstold_l
#else
# define STRTOF		strtold_l
# define __STRTOF	__strtold_l
#endif
#define MPN2FLOAT	__mpn_construct_long_double
#define FLOAT_HUGE_VAL	HUGE_VALL
#define SET_MANTISSA(flt, mant) \
  do { union ieee854_long_double u;					      \
       u.d = (flt);							      \
       u.ieee_nan.mantissa0 = (mant) >> 32;				      \
       u.ieee_nan.mantissa1 = (mant);					      \
       if ((u.ieee.mantissa0 | u.ieee.mantissa1) != 0)			      \
	 (flt) = u.d;							      \
  } while (0)

#include <stdlib/strtod_l.c>
