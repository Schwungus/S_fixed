# S_fixed

A header-only 16.16 fixed-point math library for C.

## Usage

In your `main.c` file, compile this library's function definitions by writing:

```c
#define FIX_IMPLEMENTATION
#include "S_fixed.h"

int main(int argc, char* argv[]) {
    // your code goes here...
}
```

Everywhere else, include the header normally to add the library's functions and constants to scope:

```c
#pragma once

#include "S_fixed.h"

int my_epic_function();
// and so on...
```

This is pretty much how every "header-only" library works.

## Notes

The type you should primarily use with this library is `fix16_t`. `fix32_t` is only used internally for multiplication and division.

The trigonometry functions were based on libfixmath's implementations and simplified for this library.

## Functions

### Basic

| Function          | Description                                 |
| ----------------- | ------------------------------------------- |
| `FfInt(x)`        | Integer to fixed point                      |
| `FfFloat(x)`      | Float to fixed point[^3]                    |
| `FfDouble(x)`     | Double to fixed point[^3]                   |
| `FtInt(x)`        | Fixed point to integer                      |
| `FtFloat(x)`      | Fixed point to float                        |
| `FtDouble(x)`     | Fixed point to double                       |
| `Fadd(a, b)`      | Add `+`[^1]                                 |
| `Fsub(a, b)`      | Subtract `-`[^1]                            |
| `Fmul(a, b)`      | Multiply `*`[^1]                            |
| `Fdiv(a, b)`      | Divide `/`[^1][^2]                          |
| `Fhalf(x)`        | Halve `x / 2`[^1]                           |
| `Fdouble(x)`      | Double `x * 2`[^1]                          |
| `Ffrac(x)`        | Fractional part                             |
| `Ffloor(x)`       | Round down                                  |
| `Fceil(x)`        | Round up[^1]                                |
| `Fabs(x)`         | Absolute value                              |
| `Fmin(a, b)`      | Minimum of `a` and `b`                      |
| `Fmax(a, b)`      | Maximum of `a` and `b`                      |
| `Fclamp(x, a, b)` | Clamp `x` between `a` and `b`               |
| `Flerp(a, b, x)`  | Linear interpolation[^1]                    |
| `Fsqr(x)`         | Square[^1]                                  |
| `Fsqrt(x)`        | Square root[^2]                             |
| `Fsin(x)`         | Sine                                        |
| `Fcos(x)`         | Cosine                                      |
| `Ftan(x)`         | Tangent[^1][^2]                             |
| `Fasin(x)`        | Arcsine[^2]                                 |
| `Facos(x)`        | Arccosine[^2]                               |
| `Fatan(x)`        | Arctangent[^1][^2]                          |
| `Fatan2(y, x)`    | Arctangent of `y / x` with benefits[^1][^2] |

[^1]: Overflow is possible.
[^2]: Returns `0` on failure.
[^3]: You should probably use this with common sense. Floats and fixed point don't go well together.

## Constants

| Constant  | Description                                                |
| --------- | ---------------------------------------------------------- |
| `FxOne`   | Fixed point representation of `1`                          |
| `FxHalf`  | Fixed point representation of `0.5`                        |
| `FxZero`  | Fixed point representation of `0`                          |
| `FxPi`    | Fixed point representation of `pi` (16 decimals)           |
| `FxPiD4`  | Fixed point representation of `pi / 4` (16 decimals)       |
| `FxPiD2`  | Fixed point representation of `pi / 2` (16 decimals)       |
| `Fx2Pi`   | Fixed point representation of `2 * pi` (16 decimals)       |
| `Fx3PiD4` | Fixed point representation of `(3 * pi) / 4` (16 decimals) |
