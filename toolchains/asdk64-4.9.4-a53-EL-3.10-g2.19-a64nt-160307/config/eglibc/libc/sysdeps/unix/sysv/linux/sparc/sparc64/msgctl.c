/* Copyright (C) 1995-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@gnu.ai.mit.edu>, August 1995.

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

#include <sysdep.h>
#include <sys/syscall.h>

/* Allows to control internal state and destruction of message queue
   objects.  */

int
msgctl (msqid, cmd, buf)
     int msqid;
     int cmd;
     struct msqid_ds *buf;
{
  return INLINE_SYSCALL (ipc, 5, IPCOP_msgctl, msqid, cmd, 0, buf);
}
