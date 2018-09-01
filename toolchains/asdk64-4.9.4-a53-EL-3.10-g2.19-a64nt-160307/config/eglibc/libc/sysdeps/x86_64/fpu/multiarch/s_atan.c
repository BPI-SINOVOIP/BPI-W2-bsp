#if defined HAVE_FMA4_SUPPORT || defined HAVE_AVX_SUPPORT
# include <init-arch.h>
# include <math.h>

extern double __atan_sse2 (double);
extern double __atan_avx (double);
# ifdef HAVE_FMA4_SUPPORT
extern double __atan_fma4 (double);
# else
#  undef HAS_FMA4
#  define HAS_FMA4 0
#  define __atan_fma4 ((void *) 0)
# endif

libm_ifunc (atan, (HAS_FMA4 ? __atan_fma4 :
		   HAS_AVX ? __atan_avx : __atan_sse2));

# define atan __atan_sse2
#endif


#include <sysdeps/ieee754/dbl-64/s_atan.c>
