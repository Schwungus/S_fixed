#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define FIX_IMPLEMENTATION
#include "S_fixed.h"

static int testsCounter = 0;

// Check 4 decimal places max as trigonometry isn't spot-on in fixed point
#define Epsilon (1e-4)
#define AssertEq(num, expr)                                                                                            \
	do {                                                                                                           \
		printf("Test #%d: ", testsCounter);                                                                    \
		double res = fix_to_double((expr));                                                                    \
		if (fabs(res - (num)) > Epsilon) {                                                                     \
			printf("FAIL\n\n\"%s\" is %lf != %f\n", #expr, res, (num));                                    \
			fflush(stdout);                                                                                \
			return EXIT_FAILURE;                                                                           \
		}                                                                                                      \
		printf("SUCCESS\n");                                                                                   \
		testsCounter++;                                                                                        \
	} while (0)

#define Pi (3.1415926535897932384626433832795)
#define DegToRad (Pi / 180.0)

int main(int argc, char* argv[]) {
	AssertEq(0.0, FIX_ZERO);
	AssertEq(0.5, FIX_HALF);
	AssertEq(1.0, FIX_ONE);

	AssertEq(90.0 * DegToRad, FIX_HALF_PI);
	AssertEq(180.0 * DegToRad, FIX_PI);
	AssertEq(360 * DegToRad, FIX_DOUBLE_PI);

	AssertEq(13.0, fix_add(fix_from_int(4L), fix_from_int(9L)));
	AssertEq(-3.0, fix_sub(fix_from_int(5L), fix_from_int(8L)));
	AssertEq(42.0, fix_mul(fix_from_int(6L), fix_from_int(7L)));
	AssertEq(7.0 / 6.0, fix_div(fix_from_int(7L), fix_from_int(6L)));

	AssertEq(4.5, fix_half(fix_from_int(9L)));
	AssertEq(18.0, fix_double(fix_from_int(9L)));

	AssertEq(0.0509, fix_frac(fix_from_double(127.0509)));
	AssertEq(127.0, fix_floor(fix_from_double(127.0509)));
	AssertEq(128.0, fix_ceil(fix_from_double(127.0509)));

	AssertEq(123.123, fix_abs(fix_from_double(-123.123)));
	AssertEq(81.0, fix_sqr(fix_from_int(9L)));
	AssertEq(9.0, fix_sqrt(fix_from_int(81L)));

	AssertEq(1.0, fix_tan(FIX_QUARTER_PI));
	AssertEq(45.0 * DegToRad, fix_asin(fix_sin(FIX_QUARTER_PI)));
	AssertEq(45.0 * DegToRad, fix_acos(fix_cos(FIX_QUARTER_PI)));
	AssertEq(45.0 * DegToRad, fix_atan(fix_tan(FIX_QUARTER_PI)));

	printf("\nAll good!!!\n");
	fflush(stdout);

	return EXIT_SUCCESS;
}
