/* Copyright (C) 2006  Free Software Foundation, Inc.
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
   02111-1307 USA.  */

#include "localeinfo.h"

/* Define an array of category names (also the environment variable names).  */
const union catnamestr_t _nl_category_names attribute_hidden =
  {
    {
#define DEFINE_CATEGORY(category, category_name, items, a) \
      category_name,
#include "categories.def"
#undef DEFINE_CATEGORY
    }
  };

const uint8_t _nl_category_name_idxs[__LC_LAST] attribute_hidden =
  {
#define DEFINE_CATEGORY(category, category_name, items, a) \
    [category] = offsetof (union catnamestr_t, CATNAMEMF (__LINE__)),
#include "categories.def"
#undef DEFINE_CATEGORY
  };

/* An array of their lengths, for convenience.  */
const uint8_t _nl_category_name_sizes[] attribute_hidden =
  {
#define DEFINE_CATEGORY(category, category_name, items, a) \
    [category] = sizeof (category_name) - 1,
#include "categories.def"
#undef	DEFINE_CATEGORY
    [LC_ALL] = sizeof ("LC_ALL") - 1
  };
