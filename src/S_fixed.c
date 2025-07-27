#include "S_fixed.h"

fix16_t fix_ceil(fix16_t x) {
    return fix_frac(x) ? fix_add(fix_floor(x), FIX_ONE) : x;
}

fix16_t fix_abs(fix16_t x) {
    return (x < FIX_ZERO) ? -x : x;
}

fix16_t fix_min(fix16_t a, fix16_t b) {
    return (a < b) ? a : b;
}

fix16_t fix_max(fix16_t a, fix16_t b) {
    return (a > b) ? a : b;
}

fix16_t fix_clamp(fix16_t x, fix16_t a, fix16_t b) {
    return (x < a) ? a : ((x > b) ? b : x);
}

fix16_t fix_lerp(fix16_t a, fix16_t b, fix16_t x) {
    return fix_add(a, fix_mul(fix_sub(b, a), x));
}

fix16_t fix_sqr(fix16_t x) {
    return fix_mul(x, x);
}

fix16_t fix_sqrt(fix16_t x) {
    // https://github.com/PetteriAimonen/libfixmath/blob/master/libfixmath/fix16_sqrt.c
    uint8_t neg = x < FIX_ZERO;
    uint32_t num = fix_abs(x);

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
    return neg ? -(fix16_t)out : (fix16_t)out;
}

fix16_t fix_sin(fix16_t x) {
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

fix16_t fix_tan(fix16_t x) {
    return fix_div(fix_sin(x), fix_cos(x));
}

fix16_t fix_asin(fix16_t x) {
    if (x > FIX_ONE || x < -FIX_ONE)
        return FIX_ZERO;

    fix16_t out = fix_sub(FIX_ONE, fix_mul(x, x));
    out = fix_div(x, fix_sqrt(out));
    out = fix_atan(out);
    return out;
}

fix16_t fix_atan2(fix16_t y, fix16_t x) {
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
