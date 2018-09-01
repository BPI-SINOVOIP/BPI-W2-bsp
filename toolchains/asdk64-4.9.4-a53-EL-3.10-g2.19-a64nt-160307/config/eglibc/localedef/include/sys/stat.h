#ifdef HAVE_SYS_STAT_H
#include_next <sys/stat.h>
#endif

#ifndef HAVE_STAT64
#define HAVE_STAT64 1
/* Don't define this as a function macro.  We want 'struct stat64' to be
   treated as 'struct stat'.  */
#define stat64 stat
#define fstat64(FD, BUF) fstat (FD, BUF)
#endif
