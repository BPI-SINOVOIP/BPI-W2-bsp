/* brk system call for Linux/am33.
   Copyright (C) 1995-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Alexandre Oliva <aoliva@redhat.com>.
   Based on ../i386/brk.c.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#include <errno.h>
#include <unistd.h>
#include <sysdep.h>

/* This must be initialized data because commons can't have aliases.  */
void *__curbrk = 0;

int
__brk (void *addr)
{
  void *newbrk;

  newbrk = INLINE_SYSCALL (brk, 1, addr);

  __curbrk = newbrk;

  if (newbrk < addr)
    {
      __set_errno (ENOMEM);
      return -1;
    }

  return 0;
}
weak_alias (__brk, brk)
