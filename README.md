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

| Function             | Description                                 |
| -------------------- | ------------------------------------------- |
| `fix_from_int(x)`    | Integer to fixed point                      |
| `fix_from_float(x)`  | Float to fixed point[^3]                    |
| `fix_from_double(x)` | Double to fixed point[^3]                   |
| `fix_to_int(x)`      | Fixed point to integer                      |
| `fix_to_float(x)`    | Fixed point to float                        |
| `fix_to_double(x)`   | Fixed point to double                       |
| `fix_add(a, b)`      | Add `+`[^1]                                 |
| `fix_sub(a, b)`      | Subtract `-`[^1]                            |
| `fix_mul(a, b)`      | Multiply `*`[^1]                            |
| `fix_div(a, b)`      | Divide `/`[^1][^2]                          |
| `fix_half(x)`        | Halve `x / 2`[^1]                           |
| `fix_double(x)`      | Double `x * 2`[^1]                          |
| `fix_frac(x)`        | Fractional part                             |
| `fix_floor(x)`       | Round down                                  |
| `fix_ceil(x)`        | Round up[^1]                                |
| `fix_abs(x)`         | Absolute value                              |
| `fix_min(a, b)`      | Minimum of `a` and `b`                      |
| `fix_max(a, b)`      | Maximum of `a` and `b`                      |
| `fix_clamp(x, a, b)` | Clamp `x` between `a` and `b`               |
| `fix_lerp(a, b, x)`  | Linear interpolation[^1]                    |
| `fix_sqr(x)`         | Square[^1]                                  |
| `fix_sqrt(x)`        | Square root[^2]                             |
| `fix_sin(x)`         | Sine                                        |
| `fix_cos(x)`         | Cosine                                      |
| `fix_tan(x)`         | Tangent[^1][^2]                             |
| `fix_asin(x)`        | Arcsine[^2]                                 |
| `fix_acos(x)`        | Arccosine[^2]                               |
| `fix_atan(x)`        | Arctangent[^1][^2]                          |
| `fix_atan2(y, x)`    | Arctangent of `y / x` with benefits[^1][^2] |

[^1]: Overflow is possible.
[^2]: Returns `0` on failure.
[^3]: You should probably use this with common sense. Floats and fixed point don't go well together.

## Constants

| Constant           | Description                                                |
| ------------------ | ---------------------------------------------------------- |
| `FIX_ONE`          | Fixed point representation of `1`                          |
| `FIX_HALF`         | Fixed point representation of `0.5`                        |
| `FIX_ZERO`         | Fixed point representation of `0`                          |
| `FIX_PI`           | Fixed point representation of `pi` (16 decimals)           |
| `FIX_QUARTER_PI`   | Fixed point representation of `pi / 4` (16 decimals)       |
| `FIX_HALF_PI`      | Fixed point representation of `pi / 2` (16 decimals)       |
| `FIX_DOUBLE_PI`    | Fixed point representation of `2 * pi` (16 decimals)       |
| `FIX_QUARTER_3_PI` | Fixed point representation of `(3 * pi) / 4` (16 decimals) |
