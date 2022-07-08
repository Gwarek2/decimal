#ifndef _TEST_MAIN_H

#define _TEST_MAIN_H

#include <check.h>
#include <limits.h>

#include "s21_decimal.h"
#include "bit_operations.h"
#include "core_operations.h"

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

Suite *bit_addition_suite();
Suite *bit_subtraction_suite();
Suite *bits_eq_suite();
Suite *bits_lt_suite();
Suite *divide_by_ten_suite();
Suite *multiply_by_ten_suite();
Suite *base_addition_suite();
Suite *base_subtraction_suite();
Suite *base_multiply_suite();
Suite *base_divide_suite();
Suite *base_fmod_suite();

#endif  // _TEST_MAIN_H
