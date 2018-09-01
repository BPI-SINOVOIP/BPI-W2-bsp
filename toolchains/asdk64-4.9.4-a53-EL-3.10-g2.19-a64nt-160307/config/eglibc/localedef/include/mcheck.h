#ifdef HAVE_MCHECK_H
#include_next <mcheck.h>
#else
#ifndef mcheck
#define mcheck(X)
#endif
#endif
