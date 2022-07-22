#include "test_main.h"

START_TEST(test_int_min) {
    int src = INT_MIN;
    s21_decimal expected = {{INT_MIN, 0, 0, init_sign_and_scale(1, 0)}};
    s21_decimal result;
    int status = s21_from_int_to_decimal(src, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, 0);
} END_TEST

START_TEST(test_int_max) {
    int src = INT_MAX;
    s21_decimal expected = {{INT_MAX, 0, 0, init_sign_and_scale(0, 0)}};
    s21_decimal result;
    int status = s21_from_int_to_decimal(src, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, 0);
} END_TEST

START_TEST(test_int_zero) {
    int src = 0;
    s21_decimal expected = {{0}};
    s21_decimal result;
    int status = s21_from_int_to_decimal(src, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, 0);
} END_TEST

START_TEST(test_int_random) {
    int src = rand() % INT_MAX;
    int sign = rand() % 2;
    s21_decimal expected  = {{src, 0, 0, init_sign_and_scale(sign, 0)}};
    s21_decimal result;
    if (sign) src = -src;
    int status = s21_from_int_to_decimal(src, &result);

    ASSERT_DECIMAL_EQ
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
