/* Copyright (C) 2011-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Chris Metcalf <cmetcalf@tilera.com>, 2011.

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

#ifndef _SYS_DATAPLANE_H
#define _SYS_DATAPLANE_H 1

#include <features.h>

/* Get the kernel definition for the flag bits.  */
#include <asm/dataplane.h>

__BEGIN_DECLS

extern int set_dataplane (int flags);

__END_DECLS

#endif /* sys/dataplane.h */
