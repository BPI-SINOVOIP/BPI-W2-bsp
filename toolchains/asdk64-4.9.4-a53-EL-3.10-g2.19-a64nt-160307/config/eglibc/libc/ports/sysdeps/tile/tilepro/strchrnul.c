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

#include <string.h>
#include <stdint.h>

char *
__strchrnul (const char *s, int c)
{
  int z, g;

  /* Get an aligned pointer. */
  const uintptr_t s_int = (uintptr_t) s;
  const uint32_t *p = (const uint32_t *) (s_int & -4);

  /* Create four copies of the byte for which we are looking. */
  const uint32_t goal = 0x01010101 * (uint8_t) c;

  /* Read the first aligned word, but force bytes before the string to
     match neither zero nor goal (we make sure the high bit of each
     byte is 1, and the low 7 bits are all the opposite of the goal
     byte).  Note that this shift count expression works because we
     know shift counts are taken mod 32.  */
  const uint32_t before_mask = (1 << (s_int << 3)) - 1;
  uint32_t v = (*p | before_mask) ^ (goal & __insn_shrib (before_mask, 1));

  uint32_t zero_matches, goal_matches;
  while (1)
    {
      /* Look for a terminating '\0'. */
      zero_matches = __insn_seqb (v, 0);

      /* Look for the goal byte. */
      goal_matches = __insn_seqb (v, goal);

      if (__builtin_expect ((zero_matches | goal_matches) != 0, 0))
        break;

      v = *++p;
    }

  z = __insn_ctz (zero_matches);
  g = __insn_ctz (goal_matches);

  /* Return a pointer to the NUL or goal, whichever is first. */
  if (z < g)
    g = z;
  return ((char *) p) + (g >> 3);
}
weak_alias (__strchrnul, strchrnul)
