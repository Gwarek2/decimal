# Decimal 

## Introduction

This project implements library for working with decimal fixed-point numbers. This type is appropriate for financial calculations, where round-off errors could be critical.

Implementation of this library is a part of [School 21](https://21-school.ru/) curriculum.

## About decimal type

The decimal type bit structure mimics [C# built-in decimal type](https://docs.microsoft.com/en-us/dotnet/api/system.decimal?view=net-6.0).

Decimal value represents decimal numbers ranging from positive 79,228,162,514,264,337,593,543,950,335 (2^96) to negative 79,228,162,514,264,337,593,543,950,335 (-(2^96)). The default value of a Decimal is 0.

The binary representation of a Decimal value consists of a 1-bit sign, a 96-bit integer number, and a scaling factor used to divide the 96-bit integer and specify what portion of it is a decimal fraction. The scaling factor is implicitly the number 10, raised to an exponent ranging from 0 to 28. Therefore, the binary representation of a Decimal value the form, ((-2^96 to 2^96) / 10^(0 to 28)).

The scaling factor also can preserve any trailing zeros in a Decimal number. Trailing zeros do not affect the value of a Decimal number in arithmetic or comparison operations.

Decimal number represented as a four-element array of 32-bit unsigned integers (`uint32_t bits[4];`).

`bits[0]`, `bits[1]`, and `bits[2]` contain the low, middle, and high 32 bits of the 96-bit integer number accordingly.

`bits[3]` contains the scale factor and sign, and consists of following parts:
- Bits 0 to 15, the lower word, are unused and equal be zero.
- Bits 16 to 23 contain an exponent between 0 and 28, which indicates the power of 10 to divide the integer number.
- Bits 24 to 30 are unused and equal to zero.
- Bit 31 contains the sign; 0 meaning positive, and 1 meaning negative.

Negative and positive zero treated as equal

## Supported operations

### Arithmetic Operators
| Operator name | Operators  | Function                                                                           | 
| ------ | ------ |------------------------------------------------------------------------------------|
| Addition | + | int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)         |
| Subtraction | - | int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) |
| Multiplication | * | int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) | 
| Division | / | int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) |
| Modulo | Mod | int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) |
| Negate | unary - | int s21_negate(s21_decimal value, s21_decimal *result) |

The functions return the code:
- 0 - OK
- 1 - the number is too large or equal to infinity
- 2 - the number is too small or equal to negative infinity
- 3 - division by 0

### Comparison Operators
| Operator name | Operators  | Function | 
| ------ | ------ | ------ |
| Less than | < | int s21_is_less(s21_decimal, s21_decimal) |
| Less than or equal to | <= | int s21_is_less_or_equal(s21_decimal, s21_decimal) | 
| Greater than | > |  int s21_is_greater(s21_decimal, s21_decimal) |
| Greater than or equal to | >= | int s21_is_greater_or_equal(s21_decimal, s21_decimal) | 
| Equal to | == |  int s21_is_equal(s21_decimal, s21_decimal) |
| Not equal to | != |  int s21_is_not_equal(s21_decimal, s21_decimal) |

Return value:
- 0 - FALSE
- 1 - TRUE

### Convertors and parsers

| Convertor/parser | Function | 
| ------ | ------ |
| From int  | int s21_from_int_to_decimal(int src, s21_decimal *dst) |
| From float  | int s21_from_float_to_decimal(float src, s21_decimal *dst) |
| To int  | int s21_from_decimal_to_int(s21_decimal src, int *dst) |
| To float  | int s21_from_decimal_to_float(s21_decimal src, float *dst) |

Return value - code error:
- 0 - OK
- 1 - convertation error

### Rounding functions

| Description | Function                                                         | 
| ------ |------------------------------------------------------------------|
| Rounds a specified Decimal number to the closest integer toward negative infinity. | int s21_floor(s21_decimal value, s21_decimal *result)            |	
| Rounds a decimal value to the nearest integer. | int s21_round(s21_decimal value, s21_decimal *result)    |
| Returns the integral digits of the specified Decimal; any fractional digits are discarded, including trailing zeroes. | int s21_truncate(s21_decimal value, s21_decimal *result) |

Return value - code:
- 0 - OK
- 1 - calculation error

## Build instructions
- Build static library
`make build`
- Run tests
`make test`
- Run tests with coverage report generation
`make gcov_report`
