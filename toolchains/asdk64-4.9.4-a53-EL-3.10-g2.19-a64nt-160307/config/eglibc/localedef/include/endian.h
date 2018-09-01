#ifdef HAVE_ENDIAN_H
#include_next <endian.h>
#endif

#ifndef __LITTLE_ENDIAN
#define __LITTLE_ENDIAN 1234
#endif

#ifndef __BIG_ENDIAN
#define __BIG_ENDIAN 4321
#endif

#ifndef __BYTE_ORDER
#define __BYTE_ORDER BUILD_BYTE_ORDER
#endif
