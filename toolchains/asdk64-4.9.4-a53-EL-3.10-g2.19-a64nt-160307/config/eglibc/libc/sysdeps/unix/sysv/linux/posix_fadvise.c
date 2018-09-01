/* Copyright (C) 2003-2014 Free Software Foundation, Inc.
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

#include <errno.h>
#include <fcntl.h>
#include <sysdep.h>

/* Advice the system about the expected behaviour of the application with
   respect to the file associated with FD.  */

int
posix_fadvise (int fd, off_t offset, off_t len, int advise)
{
#if defined(__NR_fadvise64) || defined(__NR_fadvise64_64)
  INTERNAL_SYSCALL_DECL (err);
# ifdef __NR_fadvise64
  int ret = INTERNAL_SYSCALL (fadvise64, err, 5, fd,
			      __LONG_LONG_PAIR (offset >> 31, offset), len,
			      advise);
# else
  int ret = INTERNAL_SYSCALL (fadvise64_64, err, 6, fd,
			      __LONG_LONG_PAIR ((long) (offset >> 31),
						(long) offset),
			      __LONG_LONG_PAIR ((long) (len >> 31),
						(long) len),
			      advise);
# endif
  if (INTERNAL_SYSCALL_ERROR_P (ret, err))
    return INTERNAL_SYSCALL_ERRNO (ret, err);
  return 0;
#else
  return ENOSYS;
#endif
}
