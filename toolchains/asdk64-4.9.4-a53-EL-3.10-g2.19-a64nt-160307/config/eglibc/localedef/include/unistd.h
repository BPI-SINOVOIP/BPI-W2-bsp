#ifdef HAVE_UNISTD_H
#include_next <unistd.h>
#endif

/* From posix/unistd.h.  */
#ifndef TEMP_FAILURE_RETRY
# define TEMP_FAILURE_RETRY(expression) \
  (__extension__							      \
    ({ long int __result;						      \
       do __result = (long int) (expression);				      \
       while (__result == -1L && errno == EINTR);			      \
       __result; }))
#endif

#ifndef HAVE_FTRUNCATE64
#define HAVE_FTRUNCATE64 1
#define ftruncate64(FD, LEN) ftruncate (FD, LEN)
#endif

#ifndef HAVE_LSEEK64
#define HAVE_LSEEK64 1
#define lseek64(FD, OFF, WHENCE) lseek (FD, OFF, WHENCE)
#endif
