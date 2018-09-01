#ifdef HAVE_FCNTL_H
#include_next <fcntl.h>
#endif

#ifndef HAVE_OPEN64
#define HAVE_OPEN64 1
#define open64 open
#endif
