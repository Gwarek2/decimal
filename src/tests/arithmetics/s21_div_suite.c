#include "test_main.h"
// 2.25 / -1.5 = -1.5
// START_TEST(test_32_bit_1) {
//     s21_decimal input1 = {{225, 0, 0, init_sign_and_scale(0, 2)}};
//     s21_decimal input2 = {{15, 0, 0, init_sign_and_scale(1, 1)}};
//     s21_decimal expected = {{15, 0, 0, init_sign_and_scale(1, 1)}};
//     s21_decimal result = {{0}};
//     s21_div(input1, input2, &result);
//     ASSERT_DECIMAL_EQ
// } END_TEST

START_TEST(test_32_bit_2) {
    s21_decimal input1 = {{2, 0, 0, init_sign_and_scale(0, 0)}};
    s21_decimal input2 = {{3, 0, 0, init_sign_and_scale(0, 0)}};
    s21_decimal expected = {{0xaaaaaab, 0x296e0196, 0x158a8994, init_sign_and_scale(0, 28)}};
    s21_decimal result = {{0}};
    s21_div(input1, input2, &result);
    // print_hex(result);
    // print_hex(expected);
    ASSERT_DECIMAL_EQ
} END_TEST

Suite *s21_div_suite() {
    Suite *s = suite_create("suite_s21_div");
    TCase *tc = tcase_create("core");

    // tcase_add_test(tc, test_32_bit_1);
    tcase_add_test(tc, test_32_bit_2);
    suite_add_tcase(s, tc);

    return s;
}
