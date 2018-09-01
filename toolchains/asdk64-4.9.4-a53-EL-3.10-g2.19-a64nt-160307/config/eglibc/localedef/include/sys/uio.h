#ifdef HAVE_SYS_UIO_H
#include_next <sys/uio.h>
#endif

#ifndef UIO_MAXIOV
#include <limits.h>
#ifdef IOV_MAX
#define UIO_MAXIOV IOV_MAX
#endif
#endif
