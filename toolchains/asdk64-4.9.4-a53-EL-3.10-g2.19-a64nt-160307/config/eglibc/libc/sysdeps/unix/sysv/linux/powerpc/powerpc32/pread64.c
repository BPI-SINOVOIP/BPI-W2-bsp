/* Copyright (C) 1997-2014 Free Software Foundation, Inc.
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

#include <errno.h>
#include <unistd.h>

#include <sysdep-cancel.h>
#include <sys/syscall.h>

#include <kernel-features.h>


ssize_t
__libc_pread64 (fd, buf, count, offset)
     int fd;
     void *buf;
     size_t count;
     off64_t offset;
{
  ssize_t result;

  if (SINGLE_THREAD_P)
    {
      /* On PPC32 64bit values are aligned in odd/even register pairs.  */
      result = INLINE_SYSCALL (pread, 6, fd, buf, count,
			       0, (long) (offset >> 32),
			       (long) offset);

      return result;
    }

  int oldtype = LIBC_CANCEL_ASYNC ();

  /* On PPC32 64bit values are aligned in odd/even register pairs.  */
  result = INLINE_SYSCALL (pread, 6, fd, buf, count,
			   0, (long) (offset >> 32),
			   (long) offset);

  LIBC_CANCEL_RESET (oldtype);

  return result;
}

weak_alias (__libc_pread64, __pread64)
weak_alias (__libc_pread64, pread64)
