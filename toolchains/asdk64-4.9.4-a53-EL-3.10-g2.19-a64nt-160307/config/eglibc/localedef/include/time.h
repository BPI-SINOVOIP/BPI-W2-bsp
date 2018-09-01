#ifdef HAVE_TIME_H
#include_next <time.h>
#endif

#ifndef __isleap
#define __isleap(year)	\
  ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))
#endif
