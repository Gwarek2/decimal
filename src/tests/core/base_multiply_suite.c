#include "test_main.h"

START_TEST(test_32_bits_1) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {2, 0, 0};
    unsigned v2[3] = {2, 0, 0};
    unsigned v3[3] = {4, 0, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&n2, v2, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v3, 0, 0);
    int overflow = base_multiply(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
    ck_assert_uint_eq(overflow, 0);
} END_TEST

START_TEST(test_32_bits_2) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {12345, 0, 0};
    unsigned v2[3] = {10, 0, 0};
    unsigned v3[3] = {123450, 0, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&n2, v2, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v3, 0, 0);
    int overflow = base_multiply(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
    ck_assert_uint_eq(overflow, 0);
} END_TEST
 
START_TEST(test_32_bits_3) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {556890, 0, 0};
    unsigned v2[3] = {3, 0, 0};
    unsigned v3[3] = {1670670, 0, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&n2, v2, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v3, 0, 0);
    int overflow = base_multiply(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
    ck_assert_uint_eq(overflow, 0);
} END_TEST
 
START_TEST(test_64_bits_1) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {0xffffffff, 0, 0};
    unsigned v2[3] = {0xffffffff, 0, 0};
    unsigned v3[3] = {1, 0xfffffffe, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&n2, v2, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v3, 0, 0);
    int overflow = base_multiply(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
    ck_assert_uint_eq(overflow, 0);
} END_TEST
 
START_TEST(test_64_bits_2) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {0x1, 0xfffffffe, 0};
    unsigned v2[3] = {0xffffffff, 0, 0};
    unsigned v3[3] = {0xffffffff, 0x2, 0xfffffffd};
    init_value(&n1, v1, 1, 23);
    init_value(&n2, v2, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v3, 0, 0);
    int overflow = base_multiply(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
    ck_assert_uint_eq(overflow, 0);
} END_TEST

START_TEST(test_64_bits_3) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {0x1, 0xfffffffe, 0};
    unsigned v2[3] = {0xffffffff, 0xf, 0};
    unsigned v3[3] = {0xffffffff, 0x11, 0xffffffdf};
    init_value(&n1, v1, 1, 23);
    init_value(&n2, v2, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v3, 0, 0);
    int overflow = base_multiply(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
    ck_assert_uint_eq(overflow, 1);
} END_TEST

START_TEST(test_96_bits_1) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {0xffffffff, 0xffffffff, 1};
    unsigned v2[3] = {2, 0, 0};
    unsigned v3[3] = {0xfffffffe, 0xffffffff, 3};
    init_value(&n1, v1, 1, 23);
    init_value(&n2, v2, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v3, 0, 0);
    int overflow = base_multiply(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
    ck_assert_uint_eq(overflow, 0);
} END_TEST

Suite *base_multiply_suite(void) {
    Suite *s = suite_create("suite_base_multiply");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_32_bits_1);
    tcase_add_test(tc, test_32_bits_2);
    tcase_add_test(tc, test_32_bits_3);
    // tcase_add_test(tc, test_32_bits_4);
    tcase_add_test(tc, test_64_bits_1);
    tcase_add_test(tc, test_64_bits_2);
    tcase_add_test(tc, test_64_bits_3);
    tcase_add_test(tc, test_96_bits_1);
    suite_add_tcase(s, tc);
    return s;
}
