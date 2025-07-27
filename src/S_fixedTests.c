#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define FIX_IMPLEMENTATION
#include "S_fixed.h"

static int testsCounter = 0;

// are we really THAT inaccurate????
#define Epsilon (1e-4)
#define AssertEq(retardedNum, coolExpr)                                                                                \
    do {                                                                                                               \
        printf("Test #%d: ", testsCounter);                                                                            \
        double res = fix_to_double((coolExpr));                                                                        \
        if (fabs(res - (retardedNum)) > Epsilon) {                                                                     \
            printf("FAIL\n\n`%s` is %lf != %f\n", #coolExpr, res, (retardedNum));                                      \
            fflush(stdout);                                                                                            \
            return EXIT_FAILURE;                                                                                       \
        }                                                                                                              \
        printf("SUCCESS\n");                                                                                           \
        testsCounter++;                                                                                                \
    } while (0)

#define DeliciousPi (3.14159265358979323846)
#define DegToRad (DeliciousPi / 180.0)

int main(int argc, char* argv[]) {
    AssertEq(0.0, FIX_ZERO);
    AssertEq(0.5, FIX_HALF);
    AssertEq(1.0, FIX_ONE);

    AssertEq(90.0 * DegToRad, FIX_HALF_PI);
    AssertEq(180.0 * DegToRad, FIX_PI);
    AssertEq(360 * DegToRad, FIX_DOUBLE_PI);

    AssertEq(13.0, fix_add(fix_from_int(4), fix_from_int(9)));
    AssertEq(-3.0, fix_sub(fix_from_int(5), fix_from_int(8)));
    AssertEq(42.0, fix_mul(fix_from_int(6), fix_from_int(7)));
    AssertEq(7.0 / 6.0, fix_div(fix_from_int(7), fix_from_int(6)));

    AssertEq(4.5, fix_half(fix_from_int(9)));
    AssertEq(18.0, fix_double(fix_from_int(9)));

    AssertEq(0.0509, fix_frac(fix_from_double(127.0509)));
    AssertEq(127.0, fix_floor(fix_from_double(127.0509)));
    AssertEq(128.0, fix_ceil(fix_from_double(127.0509)));

    AssertEq(123.123, fix_abs(fix_from_double(-123.123)));
    AssertEq(81.0, fix_sqr(fix_from_int(9)));
    AssertEq(9.0, fix_sqrt(fix_from_int(81)));

    AssertEq(1.0, fix_tan(FIX_QUARTER_PI));
    AssertEq(45.0 * DegToRad, fix_asin(fix_sin(FIX_QUARTER_PI)));
    AssertEq(45.0 * DegToRad, fix_acos(fix_cos(FIX_QUARTER_PI)));
    AssertEq(45.0 * DegToRad, fix_atan(fix_tan(FIX_QUARTER_PI)));

    printf("\nAll good!!!\n");
    fflush(stdout);

    return EXIT_SUCCESS;
}
