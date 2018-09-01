#ifdef HAVE_STDBOOL_H
#include_next <stdbool.h>
#else
#ifndef STDBOOL_H
#define STDBOOL_H

typedef unsigned char bool;
#define true 1
#define false 0

#endif
#endif
