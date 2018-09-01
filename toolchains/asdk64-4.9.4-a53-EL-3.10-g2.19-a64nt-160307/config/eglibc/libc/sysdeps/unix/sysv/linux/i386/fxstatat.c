/* Copyright (C) 2005-2014 Free Software Foundation, Inc.
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

/* Ho hum, if fxstatat == fxstatat64 we must get rid of the prototype or gcc
   will complain since they don't strictly match.  */
#define __fxstatat64 __fxstatat64_disable

#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <kernel_stat.h>

#include <sysdep.h>
#include <sys/syscall.h>

#include <kernel-features.h>

#include <xstatconv.h>


/* Get information about the file NAME relative to FD in ST.  */
int
__fxstatat (int vers, int fd, const char *file, struct stat *st, int flag)
{
  int result;
  INTERNAL_SYSCALL_DECL (err);
  struct stat64 st64;

#ifdef __NR_fstatat64
# ifndef __ASSUME_ATFCTS
  if (__have_atfcts >= 0)
# endif
    {
      result = INTERNAL_SYSCALL (fstatat64, err, 4, fd, file, &st64, flag);
# ifndef __ASSUME_ATFCTS
      if (__builtin_expect (INTERNAL_SYSCALL_ERROR_P (result, err), 1)
	  && INTERNAL_SYSCALL_ERRNO (result, err) == ENOSYS)
	__have_atfcts = -1;
      else
# endif
	if (!__builtin_expect (INTERNAL_SYSCALL_ERROR_P (result, err), 1))
	  return __xstat32_conv (vers, &st64, st);
	else
	  {
	    __set_errno (INTERNAL_SYSCALL_ERRNO (result, err));
	    return -1;
	  }
    }
#endif

#ifndef __ASSUME_ATFCTS
  if (__builtin_expect (flag & ~AT_SYMLINK_NOFOLLOW, 0))
    {
      __set_errno (EINVAL);
      return -1;
    }

  char *buf = NULL;

  if (fd != AT_FDCWD && file[0] != '/')
    {
      size_t filelen = strlen (file);
      if (__builtin_expect (filelen == 0, 0))
	{
	  __set_errno (ENOENT);
	  return -1;
	}

      static const char procfd[] = "/proc/self/fd/%d/%s";
      /* Buffer for the path name we are going to use.  It consists of
	 - the string /proc/self/fd/
	 - the file descriptor number
	 - the file name provided.
	 The final NUL is included in the sizeof.   A bit of overhead
	 due to the format elements compensates for possible negative
	 numbers.  */
      size_t buflen = sizeof (procfd) + sizeof (int) * 3 + filelen;
      buf = alloca (buflen);

      __snprintf (buf, buflen, procfd, fd, file);
      file = buf;
    }

  if (vers == _STAT_VER_KERNEL)
    {
      if (flag & AT_SYMLINK_NOFOLLOW)
	result = INTERNAL_SYSCALL (lstat, err, 2, file,
				   (struct kernel_stat *) st);
      else
	result = INTERNAL_SYSCALL (stat, err, 2, file,
				   (struct kernel_stat *) st);
      goto out;
    }

  if (flag & AT_SYMLINK_NOFOLLOW)
    result = INTERNAL_SYSCALL (lstat64, err, 2, file, &st64);
  else
    result = INTERNAL_SYSCALL (stat64, err, 2, file, &st64);
  if (__builtin_expect (!INTERNAL_SYSCALL_ERROR_P (result, err), 1))
    return __xstat32_conv (vers, &st64, st);

 out:
  if (__builtin_expect (INTERNAL_SYSCALL_ERROR_P (result, err), 0))
    {
      __atfct_seterrno (INTERNAL_SYSCALL_ERRNO (result, err), fd, buf);
      result = -1;
    }

  return result;
#endif
}
libc_hidden_def (__fxstatat)
#ifdef XSTAT_IS_XSTAT64
# undef __fxstatat64
strong_alias (__fxstatat, __fxstatat64);
libc_hidden_ver (__fxstatat, __fxstatat64)
#endif
