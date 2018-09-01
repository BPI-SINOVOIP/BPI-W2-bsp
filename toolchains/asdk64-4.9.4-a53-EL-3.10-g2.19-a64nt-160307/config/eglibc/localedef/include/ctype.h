#ifdef HAVE_CTYPE_H
#include_next <ctype.h>
#endif

/* From ctype/ctype.h.  */
#ifndef _ISbit
/* These are all the characteristics of characters.
   If there get to be more than 16 distinct characteristics,
   many things must be changed that use `unsigned short int's.

   The characteristics are stored always in network byte order (big
   endian).  We define the bit value interpretations here dependent on the
   machine's byte order.  */

# include <endian.h>
# if __BYTE_ORDER == __BIG_ENDIAN
#  define _ISbit(bit)	(1 << (bit))
# else /* __BYTE_ORDER == __LITTLE_ENDIAN */
#  define _ISbit(bit)	((bit) < 8 ? ((1 << (bit)) << 8) : ((1 << (bit)) >> 8))
# endif
#endif

#ifndef HAVE_LOCALE_T
#define __isalnum_l(c, l) isalnum (c)
#define __isalpha_l(c, l) isalpha (c)
#define __isdigit_l(c, l) isdigit (c)
#define __tolower_l(c, l) tolower (c)
#endif
