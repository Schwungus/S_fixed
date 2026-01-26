#pragma once

#ifndef FIX_NOSTD
#include <stdint.h>
#endif

#define FxFBits (16L)
#define FxWMask ((fix16_t)(0xFFFF0000))
#define FxFMask ((fix16_t)(0x0000FFFF))

typedef int32_t fix16_t;
typedef int64_t fix32_t;

#define FxOne ((fix16_t)(65536L))
#define FxHalf ((fix16_t)(32768L))
#define FxZero ((fix16_t)(0L))

#define Fx1 FxOne
#define Fx0 FxZero

#define Int2Fx(x) ((fix16_t)((int32_t)(x) * (int32_t)Fx1))
#define Float2Fx(x) ((fix16_t)((float)(x) * (float)Fx1))    // ! Unsafe !
#define Double2Fx(x) ((fix16_t)((double)(x) * (double)Fx1)) // ! Unsafe !
#define Fx2Int(x) ((int32_t)((int32_t)(x) / (int32_t)Fx1))
#define Fx2Float(x) ((float)((float)(x) / (float)(Fx1)))     // ! Unsafe !
#define Fx2Double(x) ((double)((double)(x) / (double)(Fx1))) // ! Unsafe !

// Use C11 `_Generic` tricks, if available:
#if __STDC_VERSION__ >= 201112L

#define FxFrom(x)                                                              \
	_Generic((x),                                                          \
		int: Int2Fx(x),                                                \
		long int: Int2Fx(x),                                           \
		float: Float2Fx(x),                                            \
		double: Double2Fx(x))

#endif

#define Fadd(a, b) (((fix16_t)(a)) + ((fix16_t)(b)))
#define FxAdd Fadd

#define Fsub(a, b) (((fix16_t)(a)) - ((fix16_t)(b)))
#define FxSub Fsub

#define Fmul(a, b) ((fix16_t)((((fix32_t)(a)) * ((fix32_t)(b))) >> FxFBits))
#define FxMul Fmul

fix16_t Fdiv(const fix16_t a, const fix16_t b)
#define FxDiv Fdiv
#ifdef FIX_IMPLEMENTATION
{
	if (b == Fx0)
		return Fx0;
	return (fix16_t)(((fix32_t)(a) << FxFBits) / (fix32_t)(b));
}
#else
	;
#endif

fix16_t Fmod(const fix16_t a, const fix16_t b)
#define FxMod Fmod
#ifdef FIX_IMPLEMENTATION
{
	if (b == Fx0)
		return Fx0;
	return a % b;
}
#else
	;
#endif

#define Fhalf(a) (((fix16_t)(a)) >> 1L)
#define FxHalve Fhalf

#define Fdouble(a) (((fix16_t)(a)) << 1L)
#define FxDouble Fdouble

#define Ffrac(x) (((fix16_t)(x)) & FxFMask)
#define FxFrac Ffrac

#define Ffloor(x) (((fix16_t)(x)) & FxWMask)
#define FxFloor Ffloor

fix16_t Fceil(const fix16_t x)
#define FxCeil Fceil
#ifdef FIX_IMPLEMENTATION
{
	return Ffrac(x) ? Fadd(Ffloor(x), Fx1) : x;
}
#else
	;
#endif

fix16_t Fabs(const fix16_t x)
#define FxAbs Fabs
#ifdef FIX_IMPLEMENTATION
{
	return x < Fx0 ? -x : x;
}
#else
	;
#endif

fix16_t Fmin(const fix16_t a, const fix16_t b)
#define FxMin Fmin
#ifdef FIX_IMPLEMENTATION
{
	return a < b ? a : b;
}
#else
	;
#endif

fix16_t Fmax(const fix16_t a, const fix16_t b)
#define FxMax Fmax
#ifdef FIX_IMPLEMENTATION
{
	return a > b ? a : b;
}
#else
	;
#endif

fix16_t Fclamp(const fix16_t x, const fix16_t a, const fix16_t b)
#define FxClamp Fclamp
#ifdef FIX_IMPLEMENTATION
{
	return Fmin(Fmax(x, a), b);
}
#else
	;
#endif

fix16_t Flerp(const fix16_t a, const fix16_t b, const fix16_t x)
#define FxLerp Flerp
#ifdef FIX_IMPLEMENTATION
{
	return Fadd(a, Fmul(Fsub(b, a), x));
}
#else
	;
#endif

#define FxPi ((fix16_t)(205887L))
#define FxPi4 (FxPi >> 2L)
#define FxPi2 (FxPi >> 1L)
#define Fx2Pi (FxPi << 1L)
#define Fx3Pi4 ((Fx2Pi + FxPi) >> 2L)

#define FxDeg(x) Fmul(x, 3754936L)
#define FxRad(x) Fmul(x, 1144L)

fix16_t Fsqr(const fix16_t x)
#define FxSqr Fsqr
#ifdef FIX_IMPLEMENTATION
{
	return Fmul(x, x);
}
#else
	;
#endif

fix16_t Fcube(const fix16_t x)
#define FxCube Fcube
#ifdef FIX_IMPLEMENTATION
{
	return Fmul(x, Fsqr(x));
}
#else
	;
#endif

fix16_t Fsqrt(const fix16_t x)
#define FxSqrt Fsqrt
#ifdef FIX_IMPLEMENTATION
{
	if (x <= Fx0)
		return Fx0;

	// https://github.com/PetteriAimonen/libfixmath/blob/master/libfixmath/fix16_sqrt.c
	uint32_t num = (uint32_t)x;
	uint32_t bit = (num & 0xFFF00000) ? (1L << 30L) : (1L << 18L);
	while (bit > num)
		bit >>= 2L;

	uint32_t out = 0L;
	for (uint8_t n = 0L; n < 2L; n++) {
		while (bit > 0L) {
			if (num >= (out + bit)) {
				num -= out + bit;
				out = (out >> 1L) + bit;
			} else {
				out >>= 1L;
			}
			bit >>= 2L;
		}
		if (n == 0L) {
			if (num > FxFMask) {
				num -= out;
				num = (num << FxFBits) - FxHalf;
				out = (out << FxFBits) + FxHalf;
			} else {
				num <<= FxFBits;
				out <<= FxFBits;
			}
			bit = 1L << (FxFBits - 2L);
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
#define FxSin Fsin
#ifdef FIX_IMPLEMENTATION
{
	x = x % Fx2Pi;
	if (x > FxPi)
		x -= Fx2Pi;
	else if (x < -FxPi)
		x += Fx2Pi;

	// https://github.com/PetteriAimonen/libfixmath/blob/master/libfixmath/fix16_trig.c#L89
	const fix16_t x2 = Fsqr(x);
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
#define FxCos Fcos

#define Facos(x) (Fsub(FxPi2, Fasin(x)))
#define FxAcos Facos

#define Fatan(x) (Fatan2(x, Fx1))
#define FxAtan Fatan

fix16_t Ftan(fix16_t x)
#define FxTan Ftan
#ifdef FIX_IMPLEMENTATION
{
	return Fdiv(Fsin(x), Fcos(x));
}
#else
	;
#endif

fix16_t Fatan2(fix16_t y, fix16_t x)
#define FxAtan2 Fatan2
#ifdef FIX_IMPLEMENTATION
{
	// https://github.com/PetteriAimonen/libfixmath/blob/master/libfixmath/fix16_trig.c#L150
	const fix16_t mask = y >> (sizeof(fix16_t) * 7L);
	const fix16_t abs_y = (y + mask) ^ mask;

	fix16_t angle = Fx0;
	if (x >= 0L) {
		const fix16_t r = Fdiv(x - abs_y, x + abs_y);
		angle = Fmul(12864L, Fcube(r)) - Fmul(64336L, r) + FxPi4;
	} else {
		const fix16_t r = Fdiv(x + abs_y, abs_y - x);
		angle = Fmul(12864L, Fcube(r)) - Fmul(64336L, r) + Fx3Pi4;
	}

	return y < Fx0 ? -angle : angle;
}
#else
	;
#endif

fix16_t Fasin(const fix16_t x)
#define FxAsin Fasin
#ifdef FIX_IMPLEMENTATION
{
	if (x > Fx1 || x < -Fx1)
		return Fx0;
	fix16_t out = Fsub(Fx1, Fsqr(x));
	out = Fdiv(x, Fsqrt(out));
	return Fatan(out);
}
#else
	;
#endif
