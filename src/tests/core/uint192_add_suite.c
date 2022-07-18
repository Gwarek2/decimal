#include "test_main.h"

START_TEST(test_192bit_1) {
    uint192 input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    uint192 input2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    uint192 res = {{0}};
    uint192 expected_res = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1}};
    add_uint192(input1, input2, &res); 
    assert_uint192_eq(res, expected_res);
} END_TEST

START_TEST(test_192bit_2) {
    uint192 input = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    uint192 expected_res = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    uint192 res = {{0}};
    left_shift_uint192(input, 32, &res);
    assert_uint192_eq(res, expected_res);
} END_TEST

START_TEST(test_192bit_3) {
    s21_decimal input = {{0xFFFFFFFF, 0xFFFFFFFF}};
    s21_decimal expected_res = {{0xFFFFFFF0, 0xFFFFFFFF, 0xF}};
    s21_decimal res = {{0}};
    left_shift(&input, &res, 4);
    assert_decimal_eq(res, expected_res);
} END_TEST

Suite *uint192_add_suite() {
    Suite *s = suite_create("suite_uint192_add");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_192bit_1);
    tcase_add_test(tc, test_192bit_2);
    tcase_add_test(tc, test_192bit_3);
    suite_add_tcase(s, tc);
    return s;
}
