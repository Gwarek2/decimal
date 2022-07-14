#include "test_main.h"

START_TEST(test_gt_five) {
    s21_decimal input = {{0xf27eab8f, 0x37d, 0, 0}};
    s21_decimal expected = {{0x650caac2, 0x59, 0, 0}};
    s21_decimal result = {{0}};
    base_bank_rounding(input, &result);
    assert_decimal_eq(result, expected);
}

START_TEST(test_lt_five) {
    s21_decimal input = {{0x3efab304, 0x9d2, 0, 0}};
    s21_decimal expected = {{0x6cb2ab80, 0xfb, 0, 0}};
    s21_decimal result = {{0}};
    base_bank_rounding(input, &result);
    assert_decimal_eq(result, expected);
}

START_TEST(test_eq_five_even_end) {
    s21_decimal input = {{0x139fc305, 0xabb, 0, 0}};
    s21_decimal expected = {{0xb5299380, 0x112, 0, 0}};
    s21_decimal result = {{0}};
    base_bank_rounding(input, &result);
    assert_decimal_eq(result, expected);
}

START_TEST(test_eq_five_odd_end) {
    s21_decimal input = {{0xb51a512c, 0x112, 0, 0}};
    s21_decimal expected = {{0x7882a1b8, 0x1b, 0, 0}};
    s21_decimal result = {{0}};
    base_bank_rounding(input, &result);
    assert_decimal_eq(result, expected);
}

Suite *base_bank_rounding_suite() {
    Suite *s = suite_create("suite_bank_rounding");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_gt_five);
    tcase_add_test(tc, test_lt_five);
    tcase_add_test(tc, test_eq_five_even_end);
    tcase_add_test(tc, test_eq_five_odd_end);
    suite_add_tcase(s, tc);
    return s;
}
