#include_next <locale.h>

#ifndef HAVE_LOCALE_T
#ifndef DUMMY_LOCALE_T
#define DUMMY_LOCALE_T 1
typedef int locale_t;
#define newlocale(a, b, c) 0
#endif
#endif
