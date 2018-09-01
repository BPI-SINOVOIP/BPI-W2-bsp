/* Copyright (C) 2011-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@gmail.com>, 2011.

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

#include <inttypes.h>
#include <math.h>
#include <math_private.h>

/*
 * for non-zero, finite x
 *	x = frexp(arg,&exp);
 * return a double fp quantity x such that 0.5 <= |x| <1.0
 * and the corresponding binary exponent "exp". That is
 *	arg = x*2^exp.
 * If arg is inf, 0.0, or NaN, then frexp(arg,&exp) returns arg
 * with *exp=0.
 */


double
__frexp (double x, int *eptr)
{
  int64_t ix;
  EXTRACT_WORDS64 (ix, x);
  int32_t ex = 0x7ff & (ix >> 52);
  int e = 0;

  if (__builtin_expect (ex != 0x7ff && x != 0.0, 1))
    {
      /* Not zero and finite.  */
      e = ex - 1022;
      if (__builtin_expect (ex == 0, 0))
	{
	  /* Subnormal.  */
	  x *= 0x1p54;
	  EXTRACT_WORDS64 (ix, x);
	  ex = 0x7ff & (ix >> 52);
	  e = ex - 1022 - 54;
	}

      ix = (ix & INT64_C (0x800fffffffffffff)) | INT64_C (0x3fe0000000000000);
      INSERT_WORDS64 (x, ix);
    }

  *eptr = e;
  return x;
}
weak_alias (__frexp, frexp)
#ifdef NO_LONG_DOUBLE
strong_alias (__frexp, __frexpl)
weak_alias (__frexp, frexpl)
#endif
