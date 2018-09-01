/* Round double to integer away from zero.
   Copyright (C) 2011-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 2011.

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

/* Based on a version which carries the following copyright:  */

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
#include <stdint.h>

/*
 * floor(x)
 * Return x rounded toward -inf to integral value
 * Method:
 *	Bit twiddling.
 * Exception:
 *	Inexact flag raised if x not equal to floor(x).
 */

static const double huge = 1.0e300;


double
__floor (double x)
{
	int64_t i0;
	EXTRACT_WORDS64(i0,x);
	int32_t j0 = ((i0>>52)&0x7ff)-0x3ff;
	if(__builtin_expect(j0<52, 1)) {
	    if(j0<0) {	/* raise inexact if x != 0 */
		math_force_eval(huge+x);/* return 0*sign(x) if |x|<1 */
		if(i0>=0) {i0=0;}
		else if((i0&0x7fffffffffffffffl)!=0)
		  { i0=0xbff0000000000000l;}
	    } else {
		uint64_t i = (0x000fffffffffffffl)>>j0;
		if((i0&i)==0) return x; /* x is integral */
		math_force_eval(huge+x);	/* raise inexact flag */
		if(i0<0) i0 += (0x0010000000000000l)>>j0;
		i0 &= (~i);
	    }
	    INSERT_WORDS64(x,i0);
	} else if (j0==0x400)
	    return x+x;	/* inf or NaN */
	return x;
}
#ifndef __floor
weak_alias (__floor, floor)
# ifdef NO_LONG_DOUBLE
strong_alias (__floor, __floorl)
weak_alias (__floor, floorl)
# endif
#endif
