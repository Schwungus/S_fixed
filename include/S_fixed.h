#pragma once

#ifndef FIX_NOSTD
#include <stdint.h>
#endif

#define FxFBits (16L)
#define FxWMask ((Fixed)(0xFFFF0000L))
#define FxFMask ((Fixed)(0x0000FFFFL))

typedef int32_t Fixed;
typedef int64_t Fixed64;

#define FxOne ((Fixed)(65536L))
#define FxHalf ((Fixed)(32768L))
#define FxZero ((Fixed)(0L))

#define Fx1 FxOne
#define Fx0 FxZero

#define Int2Fx(x) ((Fixed)((int32_t)(x) * (int32_t)Fx1))
#define Float2Fx(x) ((Fixed)((float)(x) * (float)Fx1))    // ! Unsafe !
#define Double2Fx(x) ((Fixed)((double)(x) * (double)Fx1)) // ! Unsafe !

#define Fx2Int(x) ((int32_t)(x) / (int32_t)Fx1)
#define Fx2Float(x) ((float)(x) / (float)(Fx1))    // ! Unsafe !
#define Fx2Double(x) ((double)(x) / (double)(Fx1)) // ! Unsafe !

#define IntToFx Int2Fx
#define FloatToFx Float2Fx
#define DoubleToFx Double2Fx

#define FxToInt Fx2Int
#define FxToFloat Fx2Float
#define FxToDouble Fx2Double

// Use C11 `_Generic` tricks, if available:
#if __STDC_VERSION__ >= 201112L

#define FxFrom(x) _Generic((x), int: Int2Fx(x), long int: Int2Fx(x), float: Float2Fx(x), double: Double2Fx(x))

#endif

#define Fadd(a, b) (((Fixed)(a)) + ((Fixed)(b)))
#define FxAdd Fadd

#define Fsub(a, b) (((Fixed)(a)) - ((Fixed)(b)))
#define FxSub Fsub

#define Fmul(a, b) ((Fixed)((((Fixed64)(a)) * ((Fixed64)(b))) >> FxFBits))
#define FxMul Fmul

Fixed Fdiv(register Fixed a, register Fixed b)
#define FxDiv Fdiv
#ifdef FIX_IMPLEMENTATION
{
    return (b == Fx0) ? Fx0 : (Fixed)(((Fixed64)(a) << FxFBits) / (Fixed64)(b));
}
#else
    ;
#endif

Fixed Fmod(register Fixed a, register Fixed b)
#define FxMod Fmod
#ifdef FIX_IMPLEMENTATION
{
    return (b == Fx0) ? Fx0 : (Fixed)(a % b);
}
#else
    ;
#endif

#define Fhalf(a) (((Fixed)(a)) >> 1L)
#define FxHalve Fhalf

#define Fdouble(a) (((Fixed)(a)) << 1L)
#define FxDouble Fdouble

#define Ffrac(x) (((Fixed)(x)) & FxFMask)
#define FxFrac Ffrac

#define Ffloor(x) (((Fixed)(x)) & FxWMask)
#define FxFloor Ffloor

Fixed Fceil(register Fixed x)
#define FxCeil Fceil
#ifdef FIX_IMPLEMENTATION
{
    return Ffrac(x) ? Fadd(Ffloor(x), Fx1) : x;
}
#else
    ;
#endif

Fixed Fabs(register Fixed x)
#define FxAbs Fabs
#ifdef FIX_IMPLEMENTATION
{
    return (x < Fx0) ? -x : x;
}
#else
    ;
#endif

Fixed Fmin(register Fixed a, register Fixed b)
#define FxMin Fmin
#ifdef FIX_IMPLEMENTATION
{
    return (a < b) ? a : b;
}
#else
    ;
#endif

Fixed Fmax(register Fixed a, register Fixed b)
#define FxMax Fmax
#ifdef FIX_IMPLEMENTATION
{
    return (a > b) ? a : b;
}
#else
    ;
#endif

#define Fclamp(x) Fmin(Fmax(x, a), b)
#define FxClamp Fclamp

Fixed Flerp(register Fixed a, register Fixed b, register Fixed x)
#define FxLerp Flerp
#ifdef FIX_IMPLEMENTATION
{
    return Fadd(a, Fmul(Fsub(b, a), x));
}
#else
    ;
#endif

#define FxPi ((Fixed)(205887L))
#define FxPi4 ((Fixed)(FxPi >> 2L))
#define FxPi2 Fhalf(FxPi)
#define Fx2Pi Fdouble(FxPi)
#define Fx3Pi4 ((Fixed)(Fadd(Fx2Pi, FxPi) >> 2L))

#define FxDeg(x) Fmul(x, 3754936L)
#define FxRad(x) Fmul(x, 1144L)

Fixed Fsqr(register Fixed x)
#define FxSqr Fsqr
#ifdef FIX_IMPLEMENTATION
{
    return Fmul(x, x);
}
#else
    ;
#endif

Fixed Fcube(register Fixed x)
#define FxCube Fcube
#ifdef FIX_IMPLEMENTATION
{
    return Fmul(x, Fsqr(x));
}
#else
    ;
#endif

Fixed Fsqrt(register Fixed x)
#define FxSqrt Fsqrt
#ifdef FIX_IMPLEMENTATION
{
    if (x <= Fx0)
        return Fx0;

    // https://github.com/PetteriAimonen/libfixmath/blob/master/libfixmath/fix16_sqrt.c
    uint32_t num = (uint32_t)x;
    uint32_t bit = (num & 0xFFF00000L) ? (1L << 30L) : (1L << 18L);
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

    return (Fixed)out;
}
#else
    ;
#endif

Fixed Fsin(register Fixed x)
#define FxSin Fsin
#ifdef FIX_IMPLEMENTATION
{
    x = x % Fx2Pi;
    while (x > FxPi)
        x -= Fx2Pi;
    while (x < -FxPi)
        x += Fx2Pi;

    // https://github.com/PetteriAimonen/libfixmath/blob/master/libfixmath/fix16_trig.c#L89
    const Fixed x2 = Fsqr(x);
    Fixed out = x;
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

Fixed Ftan(register Fixed x)
#define FxTan Ftan
#ifdef FIX_IMPLEMENTATION
{
    return Fdiv(Fsin(x), Fcos(x));
}
#else
    ;
#endif

Fixed Fatan2(register Fixed y, register Fixed x)
#define FxAtan2 Fatan2
#ifdef FIX_IMPLEMENTATION
{
    // https://github.com/PetteriAimonen/libfixmath/blob/master/libfixmath/fix16_trig.c#L150
    const Fixed mask = y >> (sizeof(Fixed) * 7L);
    const Fixed abs_y = (y + mask) ^ mask;

    Fixed angle = Fx0;
    if (x >= 0L) {
        const Fixed r = Fdiv(x - abs_y, x + abs_y);
        angle = Fmul(12864L, Fcube(r)) - Fmul(64336L, r) + FxPi4;
    } else {
        const Fixed r = Fdiv(x + abs_y, abs_y - x);
        angle = Fmul(12864L, Fcube(r)) - Fmul(64336L, r) + Fx3Pi4;
    }

    return (y < Fx0) ? -angle : angle;
}
#else
    ;
#endif

Fixed Fasin(register Fixed x)
#define FxAsin Fasin
#ifdef FIX_IMPLEMENTATION
{
    if (x > Fx1 || x < -Fx1)
        return Fx0;

    Fixed out = Fsub(Fx1, Fsqr(x));
    out = Fdiv(x, Fsqrt(out));

    return Fatan(out);
}
#else
    ;
#endif
