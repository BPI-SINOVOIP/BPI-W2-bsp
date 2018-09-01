#if HAVE_STDINT_H
#include_next <stdint.h>
#elif HAVE_INTTYPES_H
#include <inttypes.h>
#endif

/* For off64_t.  */
#include <sys/types.h>
