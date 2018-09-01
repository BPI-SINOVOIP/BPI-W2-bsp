/* Copyright (C) 2007 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.

   As a special exception, if you link the code in this file with
   files compiled with a GNU compiler to produce an executable,
   that does not cause the resulting executable to be covered by
   the GNU Lesser General Public License.  This exception does not
   however invalidate any other reasons why the executable file
   might be covered by the GNU Lesser General Public License.
   This exception applies to code released by its copyright holders
   in files containing the exception.  */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <libioP.h>

static void __THROW __attribute__ ((__noreturn__))
_IO_wfile_wide_char_support_disabled (void)
{
  static const char errstr[]
    = ("The application tried to use wide character I/O, but libc.so"
       " was compiled\n"
       "with the OPTION_POSIX_C_LANG_WIDE_CHAR option group disabled.\n");
  __libc_write (STDERR_FILENO, errstr, sizeof (errstr) - 1);
  abort ();
}

static void
_IO_wfile_disabled_void_int (_IO_FILE *fp, int x)
{
  _IO_wfile_wide_char_support_disabled ();
}

static int
_IO_wfile_disabled_int_int (_IO_FILE *fp, int x)
{
  _IO_wfile_wide_char_support_disabled ();
}

static int
_IO_wfile_disabled_int_none (_IO_FILE *fp)
{
  _IO_wfile_wide_char_support_disabled ();
}

static _IO_size_t
_IO_wfile_disabled_xsputn (_IO_FILE *fp, const void *data, _IO_size_t n)
{
  _IO_wfile_wide_char_support_disabled ();
}

static _IO_size_t
_IO_wfile_disabled_xsgetn (_IO_FILE *fp, void *data, _IO_size_t n)
{
  _IO_wfile_wide_char_support_disabled ();
}

static _IO_off64_t
_IO_wfile_disabled_seekoff (_IO_FILE *fp, _IO_off64_t off, int dir, int mode)
{
  _IO_wfile_wide_char_support_disabled ();
}

static _IO_off64_t
_IO_wfile_disabled_seekpos (_IO_FILE *fp, _IO_off64_t pos, int flags)
{
  _IO_wfile_wide_char_support_disabled ();
}

static _IO_FILE *
_IO_wfile_disabled_setbuf (_IO_FILE *fp, char *buffer, _IO_ssize_t length)
{
  _IO_wfile_wide_char_support_disabled ();
}

static _IO_ssize_t
_IO_wfile_disabled_read (_IO_FILE *fp, void *buffer, _IO_ssize_t length)
{
  _IO_wfile_wide_char_support_disabled ();
}

static _IO_ssize_t
_IO_wfile_disabled_write (_IO_FILE *fp, const void *buffer, _IO_ssize_t length)
{
  _IO_wfile_wide_char_support_disabled ();
}

static _IO_off64_t
_IO_wfile_disabled_seek (_IO_FILE *fp, _IO_off64_t offset, int mode)
{
  _IO_wfile_wide_char_support_disabled ();
}

static int
_IO_wfile_disabled_close (_IO_FILE *fp)
{
  _IO_wfile_wide_char_support_disabled ();
}

static int
_IO_wfile_disabled_stat (_IO_FILE *fp, void *buf)
{
  _IO_wfile_wide_char_support_disabled ();
}

static int
_IO_wfile_disabled_showmanyc (_IO_FILE *fp)
{
  _IO_wfile_wide_char_support_disabled ();
}

static void
_IO_wfile_disabled_imbue (_IO_FILE *fp, void *locale)
{
  _IO_wfile_wide_char_support_disabled ();
}

static const struct _IO_jump_t _IO_wfile_jumps_disabled =
{
  JUMP_INIT_DUMMY,
  JUMP_INIT(finish, _IO_wfile_disabled_void_int),
  JUMP_INIT(overflow, _IO_wfile_disabled_int_int),
  JUMP_INIT(underflow, _IO_wfile_disabled_int_none),
  JUMP_INIT(uflow, _IO_wfile_disabled_int_none),
  JUMP_INIT(pbackfail, _IO_wfile_disabled_int_int),
  JUMP_INIT(xsputn, _IO_wfile_disabled_xsputn),
  JUMP_INIT(xsgetn, _IO_wfile_disabled_xsgetn),
  JUMP_INIT(seekoff, _IO_wfile_disabled_seekoff),
  JUMP_INIT(seekpos, _IO_wfile_disabled_seekpos),
  JUMP_INIT(setbuf, _IO_wfile_disabled_setbuf),
  JUMP_INIT(sync, _IO_wfile_disabled_int_none),
  JUMP_INIT(doallocate, _IO_wfile_disabled_int_none),
  JUMP_INIT(read, _IO_wfile_disabled_read),
  JUMP_INIT(write, _IO_wfile_disabled_write),
  JUMP_INIT(seek, _IO_wfile_disabled_seek),
  JUMP_INIT(close, _IO_wfile_disabled_close),
  JUMP_INIT(stat, _IO_wfile_disabled_stat),
  JUMP_INIT(showmanyc, _IO_wfile_disabled_showmanyc),
  JUMP_INIT(imbue, _IO_wfile_disabled_imbue)
};

strong_alias (_IO_wfile_jumps_disabled, _IO_wfile_jumps)
libc_hidden_data_def (_IO_wfile_jumps)
strong_alias (_IO_wfile_jumps_disabled, _IO_wfile_jumps_mmap)
strong_alias (_IO_wfile_jumps_disabled, _IO_wfile_jumps_maybe_mmap)
