/*
 * Written by Ulrich Drepper <drepper@gmail.com>.
 */

/*
 * __isinf_ns(x) returns != 0 if x is ±inf, else 0;
 * no branching!
 */

#include <math.h>
#include <math_private.h>

#undef __isinf_ns
int
__isinf_ns (double x)
{
  int32_t hx, lx;
  EXTRACT_WORDS (hx, lx, x);
  return !(lx | ((hx & 0x7fffffff) ^ 0x7ff00000));
}
