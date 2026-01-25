#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define FIX_IMPLEMENTATION
#include <S_fixed.h>

static int testsCounter = 0;

// Check 4 decimal places max as trigonometry isn't spot-on in fixed point.
#define Epsilon (1e-4)
#define AssertEq(num, expr)                                                    \
	do {                                                                   \
		printf("Test #%d: ", testsCounter);                            \
		double res = Fx2Double((expr));                                \
		if (fabs(res - (num)) > Epsilon) {                             \
			printf("FAIL\n\n\"%s\" is %lf != %f\n", #expr, res,    \
				(num));                                        \
			fflush(stdout);                                        \
			return EXIT_FAILURE;                                   \
		}                                                              \
		printf("SUCCESS (%.4lf ~== %.4f)\n", res, (num));              \
		testsCounter++;                                                \
	} while (0)

#define Pi (3.1415926535897932384626433832795)
#define DegToRad (Pi / 180.0)

int main(int argc, char* argv[]) {
	AssertEq(0.0, FxZero);
	AssertEq(0.5, FxHalf);
	AssertEq(1.0, FxOne);

	AssertEq(90.0 * DegToRad, FxPi2);
	AssertEq(180.0 * DegToRad, FxPi);
	AssertEq(360.0 * DegToRad, Fx2Pi);

	AssertEq(13.0, Fadd(FxFrom(4L), FxFrom(9L)));
	AssertEq(-3.0, Fsub(FxFrom(5L), FxFrom(8L)));
	AssertEq(42.0, Fmul(FxFrom(6L), FxFrom(7L)));
	AssertEq(7.0 / 6.0, Fdiv(FxFrom(7L), FxFrom(6L)));
	AssertEq(1.5, Fmod(FxFrom(7.5), FxFrom(6L)));

	AssertEq(4.5, Fhalf(FxFrom(9L)));
	AssertEq(18.0, Fdouble(FxFrom(9L)));

	AssertEq(0.0509, Ffrac(FxFrom(127.0509)));
	AssertEq(127.0, Ffloor(FxFrom(127.0509)));
	AssertEq(128.0, Fceil(FxFrom(127.0509)));

	AssertEq(123.123, Fabs(FxFrom(-123.123)));
	AssertEq(81.0, Fsqr(FxFrom(9L)));
	AssertEq(9.0, Fsqrt(FxFrom(81L)));

	AssertEq(1.0, Ftan(FxPi4));
	AssertEq(45.0 * DegToRad, Fasin(Fsin(FxPi4)));
	AssertEq(45.0 * DegToRad, Facos(Fcos(FxPi4)));
	AssertEq(45.0 * DegToRad, Fatan(Ftan(FxPi4)));

	printf("\nAll good!!!\n");
	fflush(stdout);

	return EXIT_SUCCESS;
}
