/* Copyright (C) 1995-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, August 1995.

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
#include <sys/msg.h>
#include <ipc_priv.h>

#include <sysdep-cancel.h>
#include <sys/syscall.h>

int
__libc_msgsnd (msqid, msgp, msgsz, msgflg)
     int msqid;
     const void *msgp;
     size_t msgsz;
     int msgflg;
{
  if (SINGLE_THREAD_P)
    return INLINE_SYSCALL (ipc, 5, IPCOP_msgsnd, msqid, msgsz,
			   msgflg, (void *) msgp);

  int oldtype = LIBC_CANCEL_ASYNC ();

  int result = INLINE_SYSCALL (ipc, 5, IPCOP_msgsnd, msqid, msgsz,
			       msgflg, (void *) msgp);

  LIBC_CANCEL_RESET (oldtype);

  return result;
}
weak_alias (__libc_msgsnd, msgsnd)
