/* s_logbf.c -- float version of s_logb.c.
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

#include <math.h>
#include <math_private.h>

float
__logbf (float x)
{
  int32_t ix, rix;

  GET_FLOAT_WORD (ix, x);
  ix &= 0x7fffffff;		/* high |x| */
  if (ix == 0)
    return (float) -1.0 / fabsf (x);
  if (ix >= 0x7f800000)
    return x * x;
  if (__builtin_expect ((rix = ix >> 23) == 0, 0))
    {
      /* POSIX specifies that denormal number is treated as
         though it were normalized.  */
      rix -= __builtin_clz (ix) - 9;
    }
  return (float) (rix - 127);
}
weak_alias (__logbf, logbf)
