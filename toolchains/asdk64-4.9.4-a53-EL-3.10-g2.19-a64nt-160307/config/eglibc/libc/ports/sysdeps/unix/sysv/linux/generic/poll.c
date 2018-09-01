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

#include <errno.h>
#include <sys/poll.h>

#include <sysdep-cancel.h>
#include <sys/syscall.h>

#include <kernel-features.h>

int
__poll (struct pollfd *fds, nfds_t nfds, int timeout)
{
  struct timespec timeout_ts;
  struct timespec *timeout_ts_p = NULL;

  if (timeout >= 0)
    {
      timeout_ts.tv_sec = timeout / 1000;
      timeout_ts.tv_nsec = (timeout % 1000) * 1000000;
      timeout_ts_p = &timeout_ts;
    }

  if (SINGLE_THREAD_P)
    return INLINE_SYSCALL (ppoll, 5, fds, nfds, timeout_ts_p, NULL, 0);

  int oldtype = LIBC_CANCEL_ASYNC ();

  int result = INLINE_SYSCALL (ppoll, 5, fds, nfds, timeout_ts_p, NULL, 0);

  LIBC_CANCEL_RESET (oldtype);

  return result;
}
libc_hidden_def (__poll)
weak_alias (__poll, poll)
strong_alias (__poll, __libc_poll)
