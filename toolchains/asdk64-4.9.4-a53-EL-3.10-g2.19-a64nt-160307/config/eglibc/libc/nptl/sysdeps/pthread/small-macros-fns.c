/* EGLIBC: function wrappers for big macros.
   Copyright (C) 2009 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#include <gnu/option-groups.h>

/* Handle macros from ./bits/libc-lock.h.  */
#if defined _LIBC && (!defined NOT_IN_libc || defined IS_IN_libpthread)

/* Get the macros for function bodies through a back door.  */
# undef __OPTION_EGLIBC_BIG_MACROS
# define __OPTION_EGLIBC_BIG_MACROS 2
# include <bits/libc-lock.h>

void
__libc_lock_lock_fn (__libc_lock_t *name)
{
  __libc_lock_lock (*name);
}
libc_hidden_def (__libc_lock_lock_fn);

void
__libc_lock_lock_recursive_fn (__libc_lock_recursive_t *name)
{
  __libc_lock_lock_recursive (*name);
}
libc_hidden_def (__libc_lock_lock_recursive_fn);

int
__libc_lock_trylock_fn (__libc_lock_t *name)
{
  return __libc_lock_trylock (*name);
}
libc_hidden_def (__libc_lock_trylock_fn);

int
__libc_lock_trylock_recursive_fn (__libc_lock_recursive_t *name)
{
  return __libc_lock_trylock_recursive (*name);
}
libc_hidden_def (__libc_lock_trylock_recursive_fn);

void
__libc_lock_unlock_fn (__libc_lock_t *name)
{
  __libc_lock_unlock (*name);
}
libc_hidden_def (__libc_lock_unlock_fn);

void
__libc_lock_unlock_recursive_fn (__libc_lock_recursive_t *name)
{
  __libc_lock_unlock_recursive (*name);
}
libc_hidden_def (__libc_lock_unlock_recursive_fn);

#endif /*defined _LIBC && (!defined NOT_IN_libc || defined IS_IN_libpthread)*/
