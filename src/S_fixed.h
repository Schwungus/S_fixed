#pragma once

#include <stdint.h>

#define FIX_FBITS 16
#define FIX_WMASK (fix16_t)(0xFFFF0000)
#define FIX_FMASK (fix16_t)(0x0000FFFF)

typedef int32_t fix16_t;
typedef int64_t fix32_t;

#define FIX_ONE (fix16_t)(0x00010000)
#define FIX_HALF (fix16_t)(0x00008000)
#define FIX_ZERO (fix16_t)(0)

#define int_to_fix(x) (fix16_t)((x) * FIX_ONE)
#define float_to_fix(x) (fix16_t)((x) * (float)FIX_ONE)   /* ! Unsafe ! */
#define double_to_fix(x) (fix16_t)((x) * (double)FIX_ONE) /* ! Unsafe ! */
#define fix_to_int(x) (int)((fix16_t)(x) / FIX_ONE)
#define fix_to_float(x) (float)((float)(x) / (float)(FIX_ONE))     /* ! Unsafe ! */
#define fix_to_double(x) (double)((double)(x) / (double)(FIX_ONE)) /* ! Unsafe ! */

#define fix_add(a, b) ((fix16_t)(a) + (fix16_t)(b))
#define fix_sub(a, b) ((fix16_t)(a) - (fix16_t)(b))
#define fix_mul(a, b) (fix16_t)(((fix32_t)(a) * (fix32_t)(b)) >> FIX_FBITS)
#define fix_div(a, b) (fix16_t)(((fix32_t)(a) << FIX_FBITS) / (fix32_t)(b))

#define fix_half(a) ((fix16_t)(a) >> 1)
#define fix_double(a) ((fix16_t)(a) << 1)

#define fix_frac(x) ((fix16_t)(x) & FIX_FMASK)
#define fix_floor(x) ((fix16_t)(x) & FIX_WMASK)
fix16_t fix_ceil(fix16_t);
fix16_t fix_abs(fix16_t);

fix16_t fix_min(fix16_t, fix16_t);
fix16_t fix_max(fix16_t, fix16_t);
fix16_t fix_clamp(fix16_t, fix16_t, fix16_t);
fix16_t fix_lerp(fix16_t, fix16_t, fix16_t);

#define FIX_PI (fix16_t)(0x0003243F)
#define FIX_QUARTER_PI (FIX_PI >> 2)
#define FIX_HALF_PI (FIX_PI >> 1)
#define FIX_DOUBLE_PI (FIX_PI << 1)
#define FIX_QUARTER_3_PI ((FIX_DOUBLE_PI + FIX_PI) >> 2)

fix16_t fix_sqr(fix16_t);
fix16_t fix_sqrt(fix16_t);

fix16_t fix_sin(fix16_t);
#define fix_cos(x) fix_sin(fix_add(x, FIX_HALF_PI))
fix16_t fix_tan(fix16_t);
fix16_t fix_asin(fix16_t);
#define fix_acos(x) fix_sub(FIX_HALF_PI, fix_asin(x))
fix16_t fix_atan2(fix16_t, fix16_t);
#define fix_atan(x) fix_atan2(x, FIX_ONE)
