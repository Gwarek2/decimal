#include "test_main.h"

START_TEST(test_32_bits_1) {
    s21_decimal n1, result, expected;
    unsigned v1[3] = {10, 0, 0};
    unsigned v2[3] = {100, 0, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v2, 0, 0);
    int overflow = multiply_by_ten(n1, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
    ck_assert_uint_eq(overflow, 0);
} END_TEST

START_TEST(test_32_bits_2) {
    s21_decimal n1, result, expected;
    unsigned v1[3] = {234, 0, 0};
    unsigned v2[3] = {2340, 0, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v2, 0, 0);
    int overflow = multiply_by_ten(n1, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
    ck_assert_uint_eq(overflow, 0);
} END_TEST

START_TEST(test_32_bits_3) {
    s21_decimal n1, result, expected;
    unsigned v1[3] = {UINT_MAX, 0, 0};
    unsigned v2[3] = {0xFFFFFFF6, 0x9, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v2, 0, 0);
    int overflow = multiply_by_ten(n1, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
    ck_assert_uint_eq(overflow, 0);
} END_TEST

START_TEST(test_32_bits_4) {
    s21_decimal n1, result, expected;
    unsigned v1[3] = {12345678, 0, 0};
    unsigned v2[3] = {123456780, 0, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v2, 0, 0);
    int overflow = multiply_by_ten(n1, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
    ck_assert_uint_eq(overflow, 0);
} END_TEST

// START_TEST(test_64_bits_1) {
//     s21_decimal n1, result, expected;
//     unsigned v1[3] = {0, 1, 0};
//     unsigned v2[3] = {429496729, 0, 0};
//     init_value(&n1, v1, 1, 23);
//     init_value(&result, b_zero, 0, 0);
//     init_value(&expected, v2, 0, 0);
//     multiply_by_ten(n1, &result);
// 
//     ck_assert_uint_eq(expected.bits[0], result.bits[0]);
//     ck_assert_uint_eq(expected.bits[1], result.bits[1]);
//     ck_assert_uint_eq(expected.bits[2], result.bits[2]);
//     ck_assert_uint_eq(expected.bits[3], result.bits[3]);
// } END_TEST

Suite *multiply_by_ten_suite(void) {
    Suite *s = suite_create("suite_multiply_by_ten");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_32_bits_1);
    tcase_add_test(tc, test_32_bits_2);
    tcase_add_test(tc, test_32_bits_3);
    tcase_add_test(tc, test_32_bits_4);
    // tcase_add_test(tc, test_64_bits_1);
    suite_add_tcase(s, tc);
    return s;
}
