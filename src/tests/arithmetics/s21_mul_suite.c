#include "test_main.h"

START_TEST(test_32_bit_1) {
    s21_decimal input1 = {{0x26687e73, 0, 0, init_sign_and_scale(0, 4)}};  // 64438.2323
    s21_decimal input2 = {{0xd3, 0, 0, init_sign_and_scale(0, 1)}};  // 21.1
    s21_decimal expected = {{0xa82038c9, 0x1f, 0, init_sign_and_scale(0, 5)}};  // 1359646.70153
    s21_decimal result = {{0}};
    int status = s21_mul(input1, input2, &result);
    assert_decimal_eq(result, expected);
    ck_assert_int_eq(status, DEC_OK);
}

START_TEST(test_32_bit_2) {
    s21_decimal input1 = {{0x400, 0, 0, init_sign_and_scale(1, 2)}};  // -10.24
    s21_decimal input2 = {{0x400, 0, 0, init_sign_and_scale(1, 2)}};  // -10.24
    s21_decimal expected = {{0x100000, 0, 0, init_sign_and_scale(0, 4)}};  // 104.8576
    s21_decimal result = {{0}};
    int status = s21_mul(input1, input2, &result);
    assert_decimal_eq(result, expected);
    ck_assert_int_eq(status, DEC_OK);
}

START_TEST(test_zero) {
    s21_decimal input1 = {{0}};  // 0
    s21_decimal input2 = {{0xffffffff, 0, 0, init_sign_and_scale(1, 2)}};  // -42949672.95
    s21_decimal expected = {{0}};  // 0
    s21_decimal result = {{0}};
    int status = s21_mul(input1, input2, &result);
    assert_decimal_eq(result, expected);
    ck_assert_int_eq(status, DEC_OK);
}

START_TEST(test_one) {
    s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0, init_sign_and_scale(1, 6)}};  // 18446744073709.551615
    s21_decimal input2 = {{1}};  // 1
    s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0, init_sign_and_scale(1, 6)}};  // 18446744073709.551615
    s21_decimal result = {{0}};
    int status = s21_mul(input1, input2, &result);
    assert_decimal_eq(result, expected);
    ck_assert_int_eq(status, DEC_OK);
}

START_TEST(test_64_bit_1) {
    s21_decimal input1 = {{0x4fd9f63, 0xe4eeca, 0, init_sign_and_scale(0, 8)}};  // 644388461.24564323
    s21_decimal input2 = {{0x64, 0, 0, init_sign_and_scale(0, 0)}};  // 100
    s21_decimal expected = {{0xf31242ac, 0x596d46e9, 0, init_sign_and_scale(0, 8)}};  // 64438846124.56432300
    s21_decimal result = {{0}};
    int status = s21_mul(input1, input2, &result);
    assert_decimal_eq(result, expected);
    ck_assert_int_eq(status, DEC_OK);
}

Suite *s21_mul_suite() {
    Suite *s  = suite_create("suite_s21_mul");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_32_bit_1);
    tcase_add_test(tc, test_32_bit_2);
    tcase_add_test(tc, test_zero);
    tcase_add_test(tc, test_one);
    tcase_add_test(tc, test_64_bit_1);

    suite_add_tcase(s, tc);

    return s;
}
