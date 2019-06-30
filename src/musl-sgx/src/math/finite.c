#define _GNU_SOURCE
#include <math.h>

#include <stdint.h>


int finite(double x)
{
	return isfinite(x);
}

 int
 __finite(double x)
 {
   int_least64_t lx;
   //EXTRACT_WORDS64(lx,x);
   return (int)((uint_fast64_t)((lx&INT64_C(0x7fffffffffffffff))-INT64_C(0x7ff0000000000000))>>63);
 }

int
   __isnan (double x)
   {
     int_least32_t hx, lx;
     //EXTRACT_WORDS (hx, lx, x);
     hx &= 0x7fffffff;
     hx |= ( uint_least32_t) (lx | (-lx)) >> 31;
     hx = 0x7ff00000 - hx;
     return (int) ((( uint_least32_t) hx) >> 31);
   }
