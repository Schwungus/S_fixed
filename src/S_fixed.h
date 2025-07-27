#pragma once

#include <stdint.h>

#define FIX_FBITS 16
#define FIX_WMASK ((fix16_t)(0xFFFF0000))
#define FIX_FMASK ((fix16_t)(0x0000FFFF))

typedef int32_t fix16_t;
typedef int64_t fix32_t;

#define FIX_ONE ((fix16_t)(0x00010000))
#define FIX_HALF ((fix16_t)(0x00008000))
#define FIX_ZERO ((fix16_t)(0))

#define fix_from_int(x) (fix16_t)((x) * FIX_ONE)
#define fix_from_float(x) (fix16_t)((x) * (float)FIX_ONE)   /* ! Unsafe ! */
#define fix_from_double(x) (fix16_t)((x) * (double)FIX_ONE) /* ! Unsafe ! */
#define fix_to_int(x) ((int)((fix16_t)(x) / FIX_ONE))
#define fix_to_float(x) ((float)((float)(x) / (float)(FIX_ONE)))     /* ! Unsafe ! */
#define fix_to_double(x) ((double)((double)(x) / (double)(FIX_ONE))) /* ! Unsafe ! */

#define fix_add(a, b) ((fix16_t)(a) + (fix16_t)(b))
#define fix_sub(a, b) ((fix16_t)(a) - (fix16_t)(b))
#define fix_mul(a, b) (fix16_t)(((fix32_t)(a) * (fix32_t)(b)) >> FIX_FBITS)

fix16_t fix_div(fix16_t a, fix16_t b)
#ifdef FIX_IMPLEMENTATION
{
	if (b == FIX_ZERO)
		return FIX_ZERO;
	return (fix16_t)(((fix32_t)(a) << FIX_FBITS) / (fix32_t)(b));
}
#else
    ;
#endif

#define fix_half(a) ((fix16_t)(a) >> 1)
#define fix_double(a) ((fix16_t)(a) << 1)

#define fix_frac(x) ((fix16_t)(x) & FIX_FMASK)
#define fix_floor(x) ((fix16_t)(x) & FIX_WMASK)

fix16_t fix_ceil(fix16_t x)
#ifdef FIX_IMPLEMENTATION
{
	return fix_frac(x) ? fix_add(fix_floor(x), FIX_ONE) : x;
}
#else
    ;
#endif

fix16_t fix_abs(fix16_t x)
#ifdef FIX_IMPLEMENTATION
{
	return (x < FIX_ZERO) ? -x : x;
}
#else
    ;
#endif

fix16_t fix_min(fix16_t a, fix16_t b)
#ifdef FIX_IMPLEMENTATION
{
	return (a < b) ? a : b;
}
#else
    ;
#endif

fix16_t fix_max(fix16_t a, fix16_t b)
#ifdef FIX_IMPLEMENTATION
{
	return (a > b) ? a : b;
}
#else
    ;
#endif

fix16_t fix_clamp(fix16_t x, fix16_t a, fix16_t b)
#ifdef FIX_IMPLEMENTATION
{
	return (x < a) ? a : ((x > b) ? b : x);
}
#else
    ;
#endif

fix16_t fix_lerp(fix16_t a, fix16_t b, fix16_t x)
#ifdef FIX_IMPLEMENTATION
{
	return fix_add(a, fix_mul(fix_sub(b, a), x));
}
#else
    ;
#endif

#define FIX_PI ((fix16_t)(0x0003243F))
#define FIX_QUARTER_PI (FIX_PI >> 2)
#define FIX_HALF_PI (FIX_PI >> 1)
#define FIX_DOUBLE_PI (FIX_PI << 1)
#define FIX_QUARTER_3_PI ((FIX_DOUBLE_PI + FIX_PI) >> 2)

fix16_t fix_sqr(fix16_t x)
#ifdef FIX_IMPLEMENTATION
{
	return fix_mul(x, x);
}
#else
    ;
#endif

fix16_t fix_sqrt(fix16_t x)
#ifdef FIX_IMPLEMENTATION
{
	if (x <= FIX_ZERO)
		return FIX_ZERO;

	// https://github.com/PetteriAimonen/libfixmath/blob/master/libfixmath/fix16_sqrt.c
	uint32_t num = (uint32_t)x;
	uint32_t bit = (num & 0xFFF00000) ? (uint32_t)(1 << 30) : (uint32_t)(1 << 18);
	while (bit > num)
		bit >>= 2;

	uint32_t out = 0;
	for (uint8_t n = 0; n < 2; n++) {
		while (bit) {
			if (num >= (out + bit)) {
				num -= out + bit;
				out = (out >> 1) + bit;
			} else {
				out >>= 1;
			}
			bit >>= 2;
		}
		if (n == 0) {
			if (num > FIX_FMASK) {
				num -= out;
				num = (num << FIX_FBITS) - FIX_HALF;
				out = (out << FIX_FBITS) + FIX_HALF;
			} else {
				num <<= FIX_FBITS;
				out <<= FIX_FBITS;
			}
			bit = 1 << (FIX_FBITS - 2);
		}
	}

	if (num > out)
		out++;
	return (fix16_t)out;
}
#else
    ;
#endif

fix16_t fix_sin(fix16_t x)
#ifdef FIX_IMPLEMENTATION
{
	x = x % FIX_DOUBLE_PI;
	if (x > FIX_PI)
		x -= FIX_DOUBLE_PI;
	else if (x < -FIX_PI)
		x += FIX_DOUBLE_PI;

	// https://github.com/PetteriAimonen/libfixmath/blob/master/libfixmath/fix16_trig.c#L89
	fix16_t x2 = fix_mul(x, x);
	fix16_t out = x;
	x = fix_mul(x, x2);
	out -= x / 6;
	x = fix_mul(x, x2);
	out += x / 120;
	x = fix_mul(x, x2);
	out -= x / 5040;
	x = fix_mul(x, x2);
	out += x / 362880;
	x = fix_mul(x, x2);
	out -= x / 39916800;
	return out;
}
#else
    ;
#endif

#define fix_cos(x) (fix_sin(fix_add(x, FIX_HALF_PI)))
#define fix_acos(x) (fix_sub(FIX_HALF_PI, fix_asin(x)))
#define fix_atan(x) (fix_atan2(x, FIX_ONE))

fix16_t fix_tan(fix16_t x)
#ifdef FIX_IMPLEMENTATION
{
	return fix_div(fix_sin(x), fix_cos(x));
}
#else
    ;
#endif

fix16_t fix_atan2(fix16_t y, fix16_t x)
#ifdef FIX_IMPLEMENTATION
{
	// https://github.com/PetteriAimonen/libfixmath/blob/master/libfixmath/fix16_trig.c#L150
	fix16_t mask = y >> (sizeof(fix16_t) * 7);
	fix16_t abs_y = (y + mask) ^ mask;

	fix16_t angle;
	if (x >= 0) {
		fix16_t r = fix_div(x - abs_y, x + abs_y);
		fix16_t r3 = fix_mul(fix_mul(r, r), r);
		angle = fix_mul(0x00003240, r3) - fix_mul(0x0000FB50, r) + FIX_QUARTER_PI;
	} else {
		fix16_t r = fix_div(x + abs_y, abs_y - x);
		fix16_t r3 = fix_mul(fix_mul(r, r), r);
		angle = fix_mul(0x00003240, r3) - fix_mul(0x0000FB50, r) + FIX_QUARTER_3_PI;
	}

	return (y < 0) ? -angle : angle;
}
#else
    ;
#endif

fix16_t fix_asin(fix16_t x)
#ifdef FIX_IMPLEMENTATION
{
	if (x > FIX_ONE || x < -FIX_ONE)
		return FIX_ZERO;
	fix16_t out = fix_sub(FIX_ONE, fix_mul(x, x));
	out = fix_div(x, fix_sqrt(out));
	out = fix_atan(out);
	return out;
}
#else
    ;
#endif
