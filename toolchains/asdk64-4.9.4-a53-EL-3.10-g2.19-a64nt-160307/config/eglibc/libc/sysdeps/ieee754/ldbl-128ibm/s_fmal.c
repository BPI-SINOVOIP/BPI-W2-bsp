/* Compute x * y + z as ternary operation.
   Copyright (C) 2011-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by David Flaherty <flaherty@linux.vnet.ibm.com>.

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
#include <math_ldbl_opt.h>

long double
__fmal (long double x, long double y, long double z)
{
	/* An IBM long double 128 is really just 2 IEEE64 doubles, and in
	 * the case of inf/nan only the first double counts. So we use the
	 * (double) cast to avoid any data movement.   */
       if ((finite ((double)x) && finite ((double)y)) && isinf ((double)z))
               return (z);

       /* If z is zero and x are y are nonzero, compute the result
	  as x * y to avoid the wrong sign of a zero result if x * y
	  underflows to 0.  */
       if (z == 0 && x != 0 && y != 0)
	 return x * y;

       return (x * y) + z;
}
#ifdef IS_IN_libm
long_double_symbol (libm, __fmal, fmal);
#else
long_double_symbol (libc, __fmal, fmal);
#endif
