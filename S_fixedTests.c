#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef FIX_IMPLEMENTATION // hide clangd warnings about macro redefinition because of how the linting is configured
#define FIX_IMPLEMENTATION
#endif

#include "S_fixed.h"

static int testsCounter = 0;

// Check 4 decimal places max as trigonometry isn't spot-on in fixed point.
#define Epsilon (1e-4)
#define AssertEq(num, expr)                                                                                            \
	do {                                                                                                           \
		printf("Test #%d: ", testsCounter);                                                                    \
		double res = FtDouble((expr));                                                                         \
		if (fabs(res - (num)) > Epsilon) {                                                                     \
			printf("FAIL\n\n\"%s\" is %lf != %f\n", #expr, res, (num));                                    \
			fflush(stdout);                                                                                \
			return EXIT_FAILURE;                                                                           \
		}                                                                                                      \
		printf("SUCCESS (%.4lf ~== %.4f)\n", res, (num));                                                      \
		testsCounter++;                                                                                        \
	} while (0)

#define Pi (3.1415926535897932384626433832795)
#define DegToRad (Pi / 180.0)

int main(int argc, char* argv[]) {
	AssertEq(0.0, FxZero);
	AssertEq(0.5, FxHalf);
	AssertEq(1.0, FxOne);

	AssertEq(90.0 * DegToRad, FxPiD2);
	AssertEq(180.0 * DegToRad, FxPi);
	AssertEq(360.0 * DegToRad, Fx2Pi);

	AssertEq(13.0, Fadd(FfInt(4L), FfInt(9L)));
	AssertEq(-3.0, Fsub(FfInt(5L), FfInt(8L)));
	AssertEq(42.0, Fmul(FfInt(6L), FfInt(7L)));
	AssertEq(7.0 / 6.0, Fdiv(FfInt(7L), FfInt(6L)));
	AssertEq(1.5, Fmod(FfDouble(7.5), FfInt(6L)));

	AssertEq(4.5, Fhalf(FfInt(9L)));
	AssertEq(18.0, Fdouble(FfInt(9L)));

	AssertEq(0.0509, Ffrac(FfDouble(127.0509)));
	AssertEq(127.0, Ffloor(FfDouble(127.0509)));
	AssertEq(128.0, Fceil(FfDouble(127.0509)));

	AssertEq(123.123, Fabs(FfDouble(-123.123)));
	AssertEq(81.0, Fsqr(FfInt(9L)));
	AssertEq(9.0, Fsqrt(FfInt(81L)));

	AssertEq(1.0, Ftan(FxPiD4));
	AssertEq(45.0 * DegToRad, Fasin(Fsin(FxPiD4)));
	AssertEq(45.0 * DegToRad, Facos(Fcos(FxPiD4)));
	AssertEq(45.0 * DegToRad, Fatan(Ftan(FxPiD4)));

	printf("\nAll good!!!\n");
	fflush(stdout);

	return EXIT_SUCCESS;
}
