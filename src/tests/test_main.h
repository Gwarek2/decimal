#ifndef _TEST_MAIN_H

#define _TEST_MAIN_H

#include <check.h>
#include <limits.h>

#include "s21_decimal.h"
#include "common.h"
#include "output.h"
#include "binary_level.h"
#include "decimal_level.h"

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

Suite *bits_eq_suite();
Suite *bits_lt_suite();
Suite *base_addition_suite();
Suite *base_subtraction_suite();
Suite *base_multiply_suite();
Suite *base_divide_suite();
Suite *remove_trailing_zeros_suite();

#endif  // _TEST_MAIN_H
