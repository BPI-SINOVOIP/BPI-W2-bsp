/* Complex sine hyperbole function for float.
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

__complex__ float
__csinhf (__complex__ float x)
{
  __complex__ float retval;
  int negate = signbit (__real__ x);
  int rcls = fpclassify (__real__ x);
  int icls = fpclassify (__imag__ x);

  __real__ x = fabsf (__real__ x);

  if (__builtin_expect (rcls >= FP_ZERO, 1))
    {
      /* Real part is finite.  */
      if (__builtin_expect (icls >= FP_ZERO, 1))
	{
	  /* Imaginary part is finite.  */
	  const int t = (int) ((FLT_MAX_EXP - 1) * M_LN2);
	  float sinix, cosix;

	  if (__builtin_expect (icls != FP_SUBNORMAL, 1))
	    {
	      __sincosf (__imag__ x, &sinix, &cosix);
	    }
	  else
	    {
	      sinix = __imag__ x;
	      cosix = 1.0f;
	    }

	  if (fabsf (__real__ x) > t)
	    {
	      float exp_t = __ieee754_expf (t);
	      float rx = fabsf (__real__ x);
	      if (signbit (__real__ x))
		cosix = -cosix;
	      rx -= t;
	      sinix *= exp_t / 2.0f;
	      cosix *= exp_t / 2.0f;
	      if (rx > t)
		{
		  rx -= t;
		  sinix *= exp_t;
		  cosix *= exp_t;
		}
	      if (rx > t)
		{
		  /* Overflow (original real part of x > 3t).  */
		  __real__ retval = FLT_MAX * cosix;
		  __imag__ retval = FLT_MAX * sinix;
		}
	      else
		{
		  float exp_val = __ieee754_expf (rx);
		  __real__ retval = exp_val * cosix;
		  __imag__ retval = exp_val * sinix;
		}
	    }
	  else
	    {
	      __real__ retval = __ieee754_sinhf (__real__ x) * cosix;
	      __imag__ retval = __ieee754_coshf (__real__ x) * sinix;
	    }

	  if (negate)
	    __real__ retval = -__real__ retval;

	  if (fabsf (__real__ retval) < FLT_MIN)
	    {
	      volatile float force_underflow
		= __real__ retval * __real__ retval;
	      (void) force_underflow;
	    }
	  if (fabsf (__imag__ retval) < FLT_MIN)
	    {
	      volatile float force_underflow
		= __imag__ retval * __imag__ retval;
	      (void) force_underflow;
	    }
	}
      else
	{
	  if (rcls == FP_ZERO)
	    {
	      /* Real part is 0.0.  */
	      __real__ retval = __copysignf (0.0, negate ? -1.0 : 1.0);
	      __imag__ retval = __nanf ("") + __nanf ("");

	      if (icls == FP_INFINITE)
		feraiseexcept (FE_INVALID);
	    }
	  else
	    {
	      __real__ retval = __nanf ("");
	      __imag__ retval = __nanf ("");

	      feraiseexcept (FE_INVALID);
	    }
	}
    }
  else if (__builtin_expect (rcls == FP_INFINITE, 1))
    {
      /* Real part is infinite.  */
      if (__builtin_expect (icls > FP_ZERO, 1))
	{
	  /* Imaginary part is finite.  */
	  float sinix, cosix;

	  if (__builtin_expect (icls != FP_SUBNORMAL, 1))
	    {
	      __sincosf (__imag__ x, &sinix, &cosix);
	    }
	  else
	    {
	      sinix = __imag__ x;
	      cosix = 1.0f;
	    }

	  __real__ retval = __copysignf (HUGE_VALF, cosix);
	  __imag__ retval = __copysignf (HUGE_VALF, sinix);

	  if (negate)
	    __real__ retval = -__real__ retval;
	}
      else if (icls == FP_ZERO)
	{
	  /* Imaginary part is 0.0.  */
	  __real__ retval = negate ? -HUGE_VALF : HUGE_VALF;
	  __imag__ retval = __imag__ x;
	}
      else
	{
	  /* The addition raises the invalid exception.  */
	  __real__ retval = HUGE_VALF;
	  __imag__ retval = __nanf ("") + __nanf ("");

#ifdef FE_INVALID
	  if (icls == FP_INFINITE)
	    feraiseexcept (FE_INVALID);
#endif
	}
    }
  else
    {
      __real__ retval = __nanf ("");
      __imag__ retval = __imag__ x == 0.0 ? __imag__ x : __nanf ("");
    }

  return retval;
}
#ifndef __csinhf
weak_alias (__csinhf, csinhf)
#endif
