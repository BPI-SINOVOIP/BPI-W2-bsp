/* Copyright (C) 1991-2014 Free Software Foundation, Inc.
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

/* Definitions relevant to functions that operate on `sigset_t's.  */

#include <errno.h>
#include <signal.h>
#include <string.h>

#define	BITS		(_NSIG - 1)
#define	ELT(signo)	(((signo) - 1) / BITS)
#define	MASK(signo)	(1 << (((signo) - 1) % BITS))

#undef	sigemptyset
#undef	sigfillset
#undef	sigaddset
#undef	sigdelset
#undef	sigismember
