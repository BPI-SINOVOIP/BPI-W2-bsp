/* Operating system support for run-time dynamic linker.  Linux/PPC version.
   Copyright (C) 1997-2014 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <config.h>
#include <kernel-features.h>
#include <ldsodefs.h>

int __cache_line_size attribute_hidden;

/* Scan the Aux Vector for the "Data Cache Block Size" entry.  If found
   verify that the static extern __cache_line_size is defined by checking
   for not NULL.  If it is defined then assign the cache block size
   value to __cache_line_size.  This is used by memset to
   optimize setting to zero.  We have to detect 8xx processors, which
   have buggy dcbz implementations that cannot report page faults
   correctly.  That requires reading SPR, which is a privileged
   operation.  Fortunately 2.2.18 and later emulates PowerPC mfspr
   reads from the PVR register.   */
#define DL_PLATFORM_AUXV						      \
      case AT_DCACHEBSIZE:						      \
	if (__LINUX_KERNEL_VERSION >= 0x020218)				      \
	  {								      \
	    unsigned pvr = 0;						      \
	    asm ("mfspr %0, 287" : "=r" (pvr));				      \
	    if ((pvr & 0xffff0000) == 0x00500000)			      \
	      break;							      \
	  }								      \
	__cache_line_size = av->a_un.a_val;				      \
	break;

#include <sysdeps/unix/sysv/linux/dl-sysdep.c>
