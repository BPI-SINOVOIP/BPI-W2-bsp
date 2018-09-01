/* Complex cosine hyperbole function for double.
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

#include <complex.h>
#include <fenv.h>
#include <math.h>
#include <math_private.h>
#include <float.h>

__complex__ double
__ccosh (__complex__ double x)
{
  __complex__ double retval;
  int rcls = fpclassify (__real__ x);
  int icls = fpclassify (__imag__ x);

  if (__builtin_expect (rcls >= FP_ZERO, 1))
    {
      /* Real part is finite.  */
      if (__builtin_expect (icls >= FP_ZERO, 1))
	{
	  /* Imaginary part is finite.  */
	  const int t = (int) ((DBL_MAX_EXP - 1) * M_LN2);
	  double sinix, cosix;

	  if (__builtin_expect (icls != FP_SUBNORMAL, 1))
	    {
	      __sincos (__imag__ x, &sinix, &cosix);
	    }
	  else
	    {
	      sinix = __imag__ x;
	      cosix = 1.0;
	    }

	  if (fabs (__real__ x) > t)
	    {
	      double exp_t = __ieee754_exp (t);
	      double rx = fabs (__real__ x);
	      if (signbit (__real__ x))
		sinix = -sinix;
	      rx -= t;
	      sinix *= exp_t / 2.0;
	      cosix *= exp_t / 2.0;
	      if (rx > t)
		{
		  rx -= t;
		  sinix *= exp_t;
		  cosix *= exp_t;
		}
	      if (rx > t)
		{
		  /* Overflow (original real part of x > 3t).  */
		  __real__ retval = DBL_MAX * cosix;
		  __imag__ retval = DBL_MAX * sinix;
		}
	      else
		{
		  double exp_val = __ieee754_exp (rx);
		  __real__ retval = exp_val * cosix;
		  __imag__ retval = exp_val * sinix;
		}
	    }
	  else
	    {
	      __real__ retval = __ieee754_cosh (__real__ x) * cosix;
	      __imag__ retval = __ieee754_sinh (__real__ x) * sinix;
	    }

	  if (fabs (__real__ retval) < DBL_MIN)
	    {
	      volatile double force_underflow
		= __real__ retval * __real__ retval;
	      (void) force_underflow;
	    }
	  if (fabs (__imag__ retval) < DBL_MIN)
	    {
	      volatile double force_underflow
		= __imag__ retval * __imag__ retval;
	      (void) force_underflow;
	    }
	}
      else
	{
	  __imag__ retval = __real__ x == 0.0 ? 0.0 : __nan ("");
	  __real__ retval = __nan ("") + __nan ("");

	  if (icls == FP_INFINITE)
	    feraiseexcept (FE_INVALID);
	}
    }
  else if (rcls == FP_INFINITE)
    {
      /* Real part is infinite.  */
      if (__builtin_expect (icls > FP_ZERO, 1))
	{
	  /* Imaginary part is finite.  */
	  double sinix, cosix;

	  if (__builtin_expect (icls != FP_SUBNORMAL, 1))
	    {
	      __sincos (__imag__ x, &sinix, &cosix);
	    }
	  else
	    {
	      sinix = __imag__ x;
	      cosix = 1.0;
	    }

	  __real__ retval = __copysign (HUGE_VAL, cosix);
	  __imag__ retval = (__copysign (HUGE_VAL, sinix)
			     * __copysign (1.0, __real__ x));
	}
      else if (icls == FP_ZERO)
	{
	  /* Imaginary part is 0.0.  */
	  __real__ retval = HUGE_VAL;
	  __imag__ retval = __imag__ x * __copysign (1.0, __real__ x);
	}
      else
	{
	  /* The addition raises the invalid exception.  */
	  __real__ retval = HUGE_VAL;
	  __imag__ retval = __nan ("") + __nan ("");

	  if (icls == FP_INFINITE)
	    feraiseexcept (FE_INVALID);
	}
    }
  else
    {
      __real__ retval = __nan ("");
      __imag__ retval = __imag__ x == 0.0 ? __imag__ x : __nan ("");
    }

  return retval;
}
weak_alias (__ccosh, ccosh)
#ifdef NO_LONG_DOUBLE
strong_alias (__ccosh, __ccoshl)
weak_alias (__ccosh, ccoshl)
#endif
