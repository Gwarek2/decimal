#ifndef _TEST_MAIN_H

#define _TEST_MAIN_H

#include <check.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "binary_level.h"
#include "common.h"
#include "decimal_level.h"
#include "output.h"
#include "s21_decimal.h"
#include "uint192.h"

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

void assert_decimal_eq(s21_decimal result, s21_decimal expected);
void assert_uint192_eq(uint192 result, uint192 expected);

// Core
Suite *bits_eq_suite();
Suite *bits_lt_suite();
Suite *base_addition_suite();
Suite *base_subtraction_suite();
Suite *base_multiply_suite();
Suite *base_divide_suite();
Suite *remove_trailing_zeros_suite();
Suite *base_bank_rounding_suite();
Suite *uint192_add_suite();
Suite *uint192_division_suite();
Suite *bank_rounding_uint192_suite();

// Arithmetics
Suite *s21_mul_suite();
Suite *s21_negate_suite();

// Conversion
Suite *s21_from_int_to_decimal_suite();
Suite *s21_from_decimal_to_int_suite();

#endif  // _TEST_MAIN_H
