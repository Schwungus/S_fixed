# S_fixed

16.16 fixed point math library for C.

## Notes

The type you should primarily use with this library is `fixed16_t`.
`fixed32_t` is only used internally for multiplication and division.

The trigonometry functions were based on libfixmath's implementations and
simplified for this library.

## Functions

### Basic

| Function             | Description                    |
| -------------------- | ------------------------------ |
| `fix_from_int(x)`    | Integer to fixed point         |
| `fix_from_float(x)`  | Float to fixed point[^3]       |
| `fix_from_double(x)` | Double to fixed point[^3]      |
| `fix_to_int(x)`      | Fixed point to integer         |
| `fix_to_float(x)`    | Fixed point to float           |
| `fix_to_double(x)`   | Fixed point to double          |
| `fix_add(a, b)`      | Add `+`[^1]                    |
| `fix_sub(a, b)`      | Subtract `-`[^1]               |
| `fix_mul(a, b)`      | Multiply `*`[^1]               |
| `fix_div(a, b)`      | Divide `/`[^1][^2]             |
| `fix_half(x)`        | Halve `x / 2`[^1]              |
| `fix_double(x)`      | Double `x * 2`[^1]             |
| `fix_frac(x)`        | Fractional part                |
| `fix_floor(x)`       | Round down                     |
| `fix_ceil(x)`        | Round up[^1]                   |
| `fix_abs(x)`         | Absolute value                 |
| `fix_min(a, b)`      | Minimum                        |
| `fix_max(a, b)`      | Maximum                        |
| `fix_clamp(x, a, b)` | Clamp                          |
| `fix_lerp(a, b, x)`  | Linearly interpolate[^1]       |
| `fix_sqr(x)`         | Squared[^1]                    |
| `fix_sqrt(x)`        | Square root[^2]                |
| `fix_sin(x)`         | Sine                           |
| `fix_cos(x)`         | Cosine                         |
| `fix_tan(x)`         | Tangent[^1][^2]                |
| `fix_asin(x)`        | Arc sine[^2]                   |
| `fix_acos(x)`        | Arc cosine[^2]                 |
| `fix_atan(x)`        | Arc tangent[^1][^2]            |
| `fix_atan2(x, y)`    | 2-argument arc tangent[^1][^2] |

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
