#include "test_main.h"

START_TEST(test_int_min) {
    s21_decimal result, expected;
    int src = INT_MIN;
    unsigned mantiss[3] = {INT_MIN, 0, 0};
    init_value(&expected, mantiss, 1, 0);
    int status = s21_from_int_to_decimal(src, &result);

    ck_assert_uint_eq(result.bits[0], expected.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected.bits[3]);

    ck_assert_int_eq(status, 0);
} END_TEST

START_TEST(test_int_max) {
    s21_decimal result, expected;
    int src = INT_MAX;
    unsigned mantiss[3] = {INT_MAX, 0, 0};
    init_value(&expected, mantiss, 0, 0);
    int status = s21_from_int_to_decimal(src, &result);

    ck_assert_uint_eq(result.bits[0], expected.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected.bits[3]);

    ck_assert_int_eq(status, 0);
} END_TEST

START_TEST(test_int_zero) {
    s21_decimal result, expected;
    int src = 0;
    unsigned mantiss[3] = {0, 0, 0};
    init_value(&expected, mantiss, 0, 0);
    int status = s21_from_int_to_decimal(src, &result);

    ck_assert_uint_eq(result.bits[0], expected.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected.bits[3]);

    ck_assert_int_eq(status, 0);
} END_TEST

START_TEST(test_int_random) {
    s21_decimal result, expected;
    int src = rand() % INT_MAX;
    int sign = rand() % 2;
    unsigned mantiss[3] = {src, 0, 0};
    if (sign) src = -src;
    init_value(&expected, mantiss, sign, 0);
    int status = s21_from_int_to_decimal(src, &result);

    ck_assert_uint_eq(result.bits[0], expected.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected.bits[3]);

    ck_assert_int_eq(status, 0);
} END_TEST

Suite *s21_from_int_to_decimal_suite() {
   Suite *s = suite_create("suite_from_int_to_decimal_suite");
   TCase *tc = tcase_create("core");

   tcase_add_test(tc, test_int_min);
   tcase_add_test(tc, test_int_max);
   tcase_add_test(tc, test_int_zero);
   tcase_add_loop_test(tc, test_int_random, 0, 1000);
   suite_add_tcase(s, tc);
   return s;
}
