/* C locale object.
   Copyright (C) 2001-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 2001.

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

#include <locale.h>
#include <gnu/option-groups.h>
#include "localeinfo.h"

#define DEFINE_CATEGORY(category, category_name, items, a) \
extern struct __locale_data _nl_C_##category;
#include "categories.def"
#undef	DEFINE_CATEGORY

/* If the locale support code isn't enabled, don't generate strong
   reference to the C locale_data structures here; let the Makefile
   decide which ones to include.  (In the static linking case, the
   strong reference to the 'class', 'toupper', and 'tolower' tables
   will cause C-ctype.o to be brought in, as it should be, even when
   the reference to _nl_C_LC_CTYPE will be weak.)  */
#if ! __OPTION_EGLIBC_LOCALE_CODE
# define DEFINE_CATEGORY(category, category_name, items, a) \
  weak_extern (_nl_C_##category)
# include "categories.def"
# undef	DEFINE_CATEGORY
#endif
 
/* Defined in locale/C-ctype.c.  */
extern const char _nl_C_LC_CTYPE_class[] attribute_hidden;
extern const char _nl_C_LC_CTYPE_toupper[] attribute_hidden;
extern const char _nl_C_LC_CTYPE_tolower[] attribute_hidden;


const struct __locale_struct _nl_C_locobj attribute_hidden =
  {
    .__locales =
    {
#define DEFINE_CATEGORY(category, category_name, items, a) \
      [category] = &_nl_C_##category,
#include "categories.def"
#undef	DEFINE_CATEGORY
    },
    .__names =
    {
      [LC_ALL] = _nl_C_name,
#define DEFINE_CATEGORY(category, category_name, items, a) \
      [category] = _nl_C_name,
#include "categories.def"
#undef	DEFINE_CATEGORY
    },
    .__ctype_b = (const unsigned short int *) _nl_C_LC_CTYPE_class + 128,
    .__ctype_tolower = (const int *) _nl_C_LC_CTYPE_tolower + 128,
    .__ctype_toupper = (const int *) _nl_C_LC_CTYPE_toupper + 128
  };


#if ! __OPTION_EGLIBC_LOCALE_CODE
/* When locale code is enabled, these are each defined in the
   appropriate lc-CATEGORY.c file, so that static links (when __thread
   is supported) bring in only those lc-CATEGORY.o files for
   categories the program actually uses; look for NL_CURRENT_INDIRECT
   in localeinfo.h.

   When locale code is disabled, the _nl_C_CATEGORY objects are the
   only possible referents.  At the moment, there isn't a way to get
   __OPTION_EGLIBC_LOCALE_CODE defined in every compilation unit that
   #includes localeinfo.h, so we can't just turn off
   NL_CURRENT_INDIRECT.  So we'll define the _nl_current_CATEGORY
   pointers here.  */
#if defined (NL_CURRENT_INDIRECT)
#define DEFINE_CATEGORY(category, category_name, items, a)      \
  __thread struct __locale_data * const *_nl_current_##category   \
  attribute_hidden = &_nl_C_locobj.__locales[category];
#include "categories.def"
#undef DEFINE_CATEGORY
#endif
#endif /* __OPTION_EGLIBC_LOCALE_CODE */
