/* Copyright (C) 1996-2014 Free Software Foundation, Inc.
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
#include <signal.h>
#include <unistd.h>

#include <sysdep-cancel.h>
#include <sys/syscall.h>

#include <kernel-features.h>


static inline int __attribute__ ((always_inline))
do_sigsuspend (const sigset_t *set)
{
  return INLINE_SYSCALL (rt_sigsuspend, 2, set, _NSIG / 8);
}

/* Change the set of blocked signals to SET,
   wait until a signal arrives, and restore the set of blocked signals.  */
int
__sigsuspend (set)
     const sigset_t *set;
{
  if (SINGLE_THREAD_P)
    return do_sigsuspend (set);

  int oldtype = LIBC_CANCEL_ASYNC ();

  int result = do_sigsuspend (set);

  LIBC_CANCEL_RESET (oldtype);

  return result;
}
libc_hidden_def (__sigsuspend)
weak_alias (__sigsuspend, sigsuspend)
strong_alias (__sigsuspend, __libc_sigsuspend)

#ifndef NO_CANCELLATION
int
__sigsuspend_nocancel (set)
     const sigset_t *set;
{
  return do_sigsuspend (set);
}
#endif
