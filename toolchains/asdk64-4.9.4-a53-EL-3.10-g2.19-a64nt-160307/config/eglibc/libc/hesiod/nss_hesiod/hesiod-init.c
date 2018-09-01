/* Copyright (C) 2000-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Mark Kettenis <kettenis@phys.uva.nl>, 2000.

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

#include <sys/cdefs.h>		/* Needs to come before <hesiod.h>.  */
#include <hesiod.h>
#include <resolv.h>
#include <stddef.h>

#include "nss_hesiod.h"

void *
_nss_hesiod_init (void)
{
  void *context;

  if (hesiod_init (&context) == -1)
    return NULL;

  /* Use the default (per-thread) resolver state.  */
  __hesiod_res_set (context, &_res, NULL);

  return context;
}
