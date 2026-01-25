#pragma once

#include <stdint.h>

#define FxFBits (16)
#define FxWMask ((fix16_t)(0xFFFF0000))
#define FxFMask ((fix16_t)(0x0000FFFF))

typedef int32_t fix16_t;
typedef int64_t fix32_t;

#define FxOne ((fix16_t)(0x00010000))
#define FxHalf ((fix16_t)(0x00008000))
#define FxZero ((fix16_t)(0))

#define Int2Fx(x) ((fix16_t)((int32_t)(x) * FxOne))
#define Float2Fx(x) ((fix16_t)((float)(x) * (float)FxOne))    /* ! Unsafe ! */
#define Double2Fx(x) ((fix16_t)((double)(x) * (double)FxOne)) /* ! Unsafe ! */
#define Fx2Int(x) ((int32_t)((fix16_t)(x) / FxOne))
#define Fx2Float(x) ((float)((float)(x) / (float)(FxOne)))     /* ! Unsafe ! */
#define Fx2Double(x) ((double)((double)(x) / (double)(FxOne))) /* ! Unsafe ! */

// C11 `_Generic` tricks, if available:
#if __STDC_VERSION__ >= 201112L

#ifdef FIX_IMPLEMENTATION
#define FIX_INLINE_FROM(name, type, conversion)                                                                        \
	inline fix16_t name(type x) {                                                                                  \
		return conversion(x);                                                                                  \
	}
#else
#define FIX_INLINE_FROM(name, type, conversion) inline fix16_t name(type x);
#endif

FIX_INLINE_FROM(FxFromInt, int32_t, Int2Fx);
FIX_INLINE_FROM(FxFromFloat, float, Float2Fx);
FIX_INLINE_FROM(FxFromDouble, double, Double2Fx);

#define FxFrom(x) (_Generic((x), int: FxFromInt, long int: FxFromInt, float: FxFromFloat, double: FxFromDouble)(x))

#endif

#define Fadd(a, b) (((fix16_t)(a)) + ((fix16_t)(b)))
#define Fsub(a, b) (((fix16_t)(a)) - ((fix16_t)(b)))
#define Fmul(a, b) ((fix16_t)((((fix32_t)(a)) * ((fix32_t)(b))) >> FxFBits))

fix16_t Fdiv(fix16_t a, fix16_t b)
#ifdef FIX_IMPLEMENTATION
{
	if (b == FxZero)
		return FxZero;
	return (fix16_t)(((fix32_t)(a) << FxFBits) / (fix32_t)(b));
}
#else
	;
#endif

fix16_t Fmod(fix16_t a, fix16_t b)
#ifdef FIX_IMPLEMENTATION
{
	if (b == FxZero)
		return FxZero;
	return (fix16_t)(a % b);
}
#else
	;
#endif

#define Fhalf(a) (((fix16_t)(a)) >> 1)
#define Fdouble(a) (((fix16_t)(a)) << 1)

#define Ffrac(x) (((fix16_t)(x)) & FxFMask)
#define Ffloor(x) (((fix16_t)(x)) & FxWMask)

fix16_t Fceil(fix16_t x)
#ifdef FIX_IMPLEMENTATION
{
	return Ffrac(x) ? Fadd(Ffloor(x), FxOne) : x;
}
#else
	;
#endif

fix16_t Fabs(fix16_t x)
#ifdef FIX_IMPLEMENTATION
{
	return (x < FxZero) ? -x : x;
}
#else
	;
#endif

fix16_t Fmin(fix16_t a, fix16_t b)
#ifdef FIX_IMPLEMENTATION
{
	return (a < b) ? a : b;
}
#else
	;
#endif

fix16_t Fmax(fix16_t a, fix16_t b)
#ifdef FIX_IMPLEMENTATION
{
	return (a > b) ? a : b;
}
#else
	;
#endif

fix16_t Fclamp(fix16_t x, fix16_t a, fix16_t b)
#ifdef FIX_IMPLEMENTATION
{
	return (x < a) ? a : ((x > b) ? b : x);
}
#else
	;
#endif

fix16_t Flerp(fix16_t a, fix16_t b, fix16_t x)
#ifdef FIX_IMPLEMENTATION
{
	return Fadd(a, Fmul(Fsub(b, a), x));
}
#else
	;
#endif

#define FxPi ((fix16_t)(0x0003243F))
#define FxPi4 (FxPi >> 2)
#define FxPi2 (FxPi >> 1)
#define Fx2Pi (FxPi << 1)
#define Fx3Pi4 ((Fx2Pi + FxPi) >> 2)

#define Fdeg(x) Fmul(x, 0x00394BB8)
#define Frad(x) Fmul(x, 0x00000478)

fix16_t Fsqr(fix16_t x)
#ifdef FIX_IMPLEMENTATION
{
	return Fmul(x, x);
}
#else
	;
#endif

fix16_t Fsqrt(fix16_t x)
#ifdef FIX_IMPLEMENTATION
{
	if (x <= FxZero)
		return FxZero;

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
			if (num > FxFMask) {
				num -= out;
				num = (num << FxFBits) - FxHalf;
				out = (out << FxFBits) + FxHalf;
			} else {
				num <<= FxFBits;
				out <<= FxFBits;
			}
			bit = 1 << (FxFBits - 2);
		}
	}

	if (num > out)
		out++;
	return (fix16_t)out;
}
#else
	;
#endif

fix16_t Fsin(fix16_t x)
#ifdef FIX_IMPLEMENTATION
{
	x = x % Fx2Pi;
	if (x > FxPi)
		x -= Fx2Pi;
	else if (x < -FxPi)
		x += Fx2Pi;

	// https://github.com/PetteriAimonen/libfixmath/blob/master/libfixmath/fix16_trig.c#L89
	fix16_t x2 = Fmul(x, x);
	fix16_t out = x;
	x = Fmul(x, x2);
	out -= x / 6L;
	x = Fmul(x, x2);
	out += x / 120L;
	x = Fmul(x, x2);
	out -= x / 5040L;
	x = Fmul(x, x2);
	out += x / 362880L;
	x = Fmul(x, x2);
	out -= x / 39916800L;
	return out;
}
#else
	;
#endif

#define Fcos(x) (Fsin(Fadd(x, FxPi2)))
#define Facos(x) (Fsub(FxPi2, Fasin(x)))
#define Fatan(x) (Fatan2(x, FxOne))

fix16_t Ftan(fix16_t x)
#ifdef FIX_IMPLEMENTATION
{
	return Fdiv(Fsin(x), Fcos(x));
}
#else
	;
#endif

fix16_t Fatan2(fix16_t y, fix16_t x)
#ifdef FIX_IMPLEMENTATION
{
	// https://github.com/PetteriAimonen/libfixmath/blob/master/libfixmath/fix16_trig.c#L150
	fix16_t mask = y >> (sizeof(fix16_t) * 7);
	fix16_t abs_y = (y + mask) ^ mask;

	fix16_t angle = FxZero;
	if (x >= 0) {
		fix16_t r = Fdiv(x - abs_y, x + abs_y);
		fix16_t r3 = Fmul(Fmul(r, r), r);
		angle = Fmul(0x00003240, r3) - Fmul(0x0000FB50, r) + FxPi4;
	} else {
		fix16_t r = Fdiv(x + abs_y, abs_y - x);
		fix16_t r3 = Fmul(Fmul(r, r), r);
		angle = Fmul(0x00003240, r3) - Fmul(0x0000FB50, r) + Fx3Pi4;
	}

	return (y < 0) ? -angle : angle;
}
#else
	;
#endif

fix16_t Fasin(fix16_t x)
#ifdef FIX_IMPLEMENTATION
{
	if (x > FxOne || x < -FxOne)
		return FxZero;
	fix16_t out = Fsub(FxOne, Fmul(x, x));
	out = Fdiv(x, Fsqrt(out));
	out = Fatan(out);
	return out;
}
#else
	;
#endif
