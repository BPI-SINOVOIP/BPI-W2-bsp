/* e_fmodl.c -- long double version of e_fmod.c.
 * Conversion to IEEE quad long double by Jakub Jelinek, jj@ultra.linux.cz.
 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

/*
 * __ieee754_fmodl(x,y)
 * Return x mod y in exact arithmetic
 * Method: shift and subtract
 */

#include <math.h>
#include <math_private.h>
#include <ieee754.h>

static const long double one = 1.0, Zero[] = {0.0, -0.0,};

long double
__ieee754_fmodl (long double x, long double y)
{
	int64_t hx, hy, hz, sx, sy;
	uint64_t lx, ly, lz;
	int n, ix, iy;
	double xhi, xlo, yhi, ylo;

	ldbl_unpack (x, &xhi, &xlo);
	EXTRACT_WORDS64 (hx, xhi);
	EXTRACT_WORDS64 (lx, xlo);
	ldbl_unpack (y, &yhi, &ylo);
	EXTRACT_WORDS64 (hy, yhi);
	EXTRACT_WORDS64 (ly, ylo);
	sx = hx&0x8000000000000000ULL;		/* sign of x */
	hx ^= sx;				/* |x| */
	sy = hy&0x8000000000000000ULL;		/* sign of y */
	hy ^= sy;				/* |y| */

    /* purge off exception values */
	if(__builtin_expect(hy==0 ||
			    (hx>=0x7ff0000000000000LL)|| /* y=0,or x not finite */
			    (hy>0x7ff0000000000000LL),0))	/* or y is NaN */
	    return (x*y)/(x*y);
	if (__builtin_expect (hx <= hy, 0))
	  {
	    /* If |x| < |y| return x.  */
	    if (hx < hy)
	      return x;
	    /* At this point the absolute value of the high doubles of
	       x and y must be equal.  */
	    /* If the low double of y is the same sign as the high
	       double of y (ie. the low double increases |y|)...  */
	    if (((ly ^ sy) & 0x8000000000000000LL) == 0
		/* ... then a different sign low double to high double
		   for x or same sign but lower magnitude...  */
		&& (int64_t) (lx ^ sx) < (int64_t) (ly ^ sy))
	      /* ... means |x| < |y|.  */
	      return x;
	    /* If the low double of x differs in sign to the high
	       double of x (ie. the low double decreases |x|)...  */
	    if (((lx ^ sx) & 0x8000000000000000LL) != 0
		/* ... then a different sign low double to high double
		   for y with lower magnitude (we've already caught
		   the same sign for y case above)...  */
		&& (int64_t) (lx ^ sx) > (int64_t) (ly ^ sy))
	      /* ... means |x| < |y|.  */
	      return x;
	    /* If |x| == |y| return x*0.  */
	    if ((lx ^ sx) == (ly ^ sy))
	      return Zero[(uint64_t) sx >> 63];
	}

    /* Make the IBM extended format 105 bit mantissa look like the ieee854 112
       bit mantissa so the following operations will give the correct
       result.  */
	ldbl_extract_mantissa(&hx, &lx, &ix, x);
	ldbl_extract_mantissa(&hy, &ly, &iy, y);

	if (__builtin_expect (ix == -IEEE754_DOUBLE_BIAS, 0))
	  {
	    /* subnormal x, shift x to normal.  */
	    while ((hx & (1LL << 48)) == 0)
	      {
		hx = (hx << 1) | (lx >> 63);
		lx = lx << 1;
		ix -= 1;
	      }
	  }

	if (__builtin_expect (iy == -IEEE754_DOUBLE_BIAS, 0))
	  {
	    /* subnormal y, shift y to normal.  */
	    while ((hy & (1LL << 48)) == 0)
	      {
		hy = (hy << 1) | (ly >> 63);
		ly = ly << 1;
		iy -= 1;
	      }
	  }

    /* fix point fmod */
	n = ix - iy;
	while(n--) {
	    hz=hx-hy;lz=lx-ly; if(lx<ly) hz -= 1;
	    if(hz<0){hx = hx+hx+(lx>>63); lx = lx+lx;}
	    else {
		if((hz|lz)==0)		/* return sign(x)*0 */
		    return Zero[(u_int64_t)sx>>63];
		hx = hz+hz+(lz>>63); lx = lz+lz;
	    }
	}
	hz=hx-hy;lz=lx-ly; if(lx<ly) hz -= 1;
	if(hz>=0) {hx=hz;lx=lz;}

    /* convert back to floating value and restore the sign */
	if((hx|lx)==0)			/* return sign(x)*0 */
	    return Zero[(u_int64_t)sx>>63];
	while(hx<0x0001000000000000LL) {	/* normalize x */
	    hx = hx+hx+(lx>>63); lx = lx+lx;
	    iy -= 1;
	}
	if(__builtin_expect(iy>= -1022,0)) {	/* normalize output */
	    x = ldbl_insert_mantissa((sx>>63), iy, hx, lx);
	} else {		/* subnormal output */
	    n = -1022 - iy;
	    if(n<=48) {
		lx = (lx>>n)|((u_int64_t)hx<<(64-n));
		hx >>= n;
	    } else if (n<=63) {
		lx = (hx<<(64-n))|(lx>>n); hx = sx;
	    } else {
		lx = hx>>(n-64); hx = sx;
	    }
	    x = ldbl_insert_mantissa((sx>>63), iy, hx, lx);
	    x *= one;		/* create necessary signal */
	}
	return x;		/* exact output */
}
strong_alias (__ieee754_fmodl, __fmodl_finite)
