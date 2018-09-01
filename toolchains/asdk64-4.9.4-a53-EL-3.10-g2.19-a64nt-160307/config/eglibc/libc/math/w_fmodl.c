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

#include <math.h>
#include <math_private.h>

/* wrapper fmodl */
long double
__fmodl (long double x, long double y)
{
  if (__builtin_expect (__isinf_nsl (x) || y == 0.0L, 0)
      && _LIB_VERSION != _IEEE_ && !__isnanl (y) && !__isnanl (x))
    /* fmod(+-Inf,y) or fmod(x,0) */
    return __kernel_standard_l (x, y, 227);

  return __ieee754_fmodl (x, y);
}
weak_alias (__fmodl, fmodl)
