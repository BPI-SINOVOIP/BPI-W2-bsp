#include <math.h>
#include <stdio.h>
#include <errno.h>

long double
__ieee754_sqrtl (long double x)
{
  fputs ("__ieee754_sqrtl not implemented\n", stderr);
  __set_errno (ENOSYS);
  return 0.0;
}
strong_alias (__ieee754_sqrtl, __sqrtl_finite)

stub_warning (sqrtl)
