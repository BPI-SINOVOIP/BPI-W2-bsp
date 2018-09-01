/* Measure strncat functions.
   Copyright (C) 2013-2014 Free Software Foundation, Inc.
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

#define TEST_MAIN
#define TEST_NAME "strncat"
#include "bench-string.h"

typedef char *(*proto_t) (char *, const char *, size_t);
char *stupid_strncat (char *, const char *, size_t);
char *simple_strncat (char *, const char *, size_t);

IMPL (stupid_strncat, 0)
IMPL (strncat, 2)

char *
stupid_strncat (char *dst, const char *src, size_t n)
{
  char *ret = dst;
  while (*dst++ != '\0');
  --dst;
  while (n--)
    if ( (*dst++ = *src++) == '\0')
      return ret;
  *dst = '\0';
  return ret;
}

static void
do_one_test (impl_t *impl, char *dst, const char *src, size_t n)
{
  size_t k = strlen (dst), i, iters = INNER_LOOP_ITERS;
  timing_t start, stop, cur;

  if (CALL (impl, dst, src, n) != dst)
    {
      error (0, 0, "Wrong result in function %s %p != %p", impl->name,
	     CALL (impl, dst, src, n), dst);
      ret = 1;
      return;
    }

  size_t len = strlen (src);
  if (memcmp (dst + k, src, len + 1 > n ? n : len + 1) != 0)
    {
      error (0, 0, "Incorrect cancatination in function %s",
	     impl->name);
      ret = 1;
      return;
    }
  if (n < len && dst[k + n] != '\0')
    {
      error (0, 0, "There is no zero in the end of output string in %s",
	     impl->name);
      ret = 1;
      return;
    }

  TIMING_NOW (start);
  for (i = 0; i < iters; ++i)
    {
      dst[k] = '\0';
      CALL (impl, dst, src, n);
    }
  TIMING_NOW (stop);

  TIMING_DIFF (cur, start, stop);

  TIMING_PRINT_MEAN ((double) cur, (double) iters);
}

static void
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 size_t n, int max_char)
{
  size_t i;
  char *s1, *s2;

  align1 &= 7;
  if (align1 + len1 >= page_size)
    return;
  if (align1 + n > page_size)
    return;
  align2 &= 7;
  if (align2 + len1 + len2 >= page_size)
    return;
  if (align2 + len1 + n > page_size)
    return;
  s1 = (char *) (buf1 + align1);
  s2 = (char *) (buf2 + align2);

  for (i = 0; i < len1; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len1] = '\0';

  for (i = 0; i < len2; i++)
    s2[i] = 32 + 23 * i % (max_char - 32);

  printf ("Length %4zd/%4zd, alignment %2zd/%2zd, N %4zd:",
	  len1, len2, align1, align2, n);

  FOR_EACH_IMPL (impl, 0)
    {
      s2[len2] = '\0';
      do_one_test (impl, s2, s1, n);
    }

  putchar ('\n');
}

int
main (void)
{
  size_t i, n;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  for (n = 2; n <= 2048; n*=4)
    {
      do_test (0, 2, 2, 2, n, 127);
      do_test (0, 0, 4, 4, n, 127);
      do_test (4, 0, 4, 4, n, 255);
      do_test (0, 0, 8, 8, n, 127);
      do_test (0, 8, 8, 8, n, 127);

      for (i = 1; i < 8; ++i)
	{
	  do_test (0, 0, 8 << i, 8 << i, n, 127);
	  do_test (8 - i, 2 * i, 8 << i, 8 << i, n, 127);
	  do_test (0, 0, 8 << i, 2 << i, n, 127);
	  do_test (8 - i, 2 * i, 8 << i, 2 << i, n, 127);
	}

      for (i = 1; i < 8; ++i)
	{
	  do_test (i, 2 * i, 8 << i, 1, n, 127);
	  do_test (2 * i, i, 8 << i, 1, n, 255);
	  do_test (i, i, 8 << i, 10, n, 127);
	}
    }

  return ret;
}
