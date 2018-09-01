/* Return current rounding direction.
   Copyright (C) 2004-2014 Free Software Foundation, Inc.
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
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#include <fenv.h>
#include <fpu_control.h>
#include <arm-features.h>


int
fegetround (void)
{
  if (ARM_HAVE_VFP)
    {
      unsigned int temp;

      /* Get the current environment.  */
      _FPU_GETCW (temp);

      return temp & FE_TOWARDZERO;
    }

  /* The current soft-float implementation only handles TONEAREST.  */
  return FE_TONEAREST;
}
libm_hidden_def (fegetround)
