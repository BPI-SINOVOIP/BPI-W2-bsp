#ifdef HAVE_LIBINTL_H
#include_next <libintl.h>
#endif

#ifndef _
#define _(X) (X)
#endif

#ifndef N_
#define N_(X) (X)
#endif

#ifndef _libc_intl_domainname
#define _libc_intl_domainname "libc"
#endif
