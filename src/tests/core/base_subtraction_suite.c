#include "test_main.h"

START_TEST(test_32_bits) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {73, 0, 0};
    unsigned v2[3] = {10, 0, 0};
    unsigned v3[3] = {0, 0, 0};
    unsigned v4[3] = {63, 0, 0};
    init_value(&n1, v1, 0, 0);
    init_value(&n2, v2, 0, 0);
    init_value(&result, v3, 0, 0);
    init_value(&expected, v4, 0, 0);
    base_subtraction(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
} END_TEST

START_TEST(test_64_bits_1) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {0, 1, 0};
    unsigned v2[3] = {10, 0, 0};
    unsigned v3[3] = {0, 0, 0};
    unsigned v4[3] = {UINT_MAX - 9, 0, 0};
    init_value(&n1, v1, 0, 0);
    init_value(&n2, v2, 0, 0);
    init_value(&result, v3, 0, 0);
    init_value(&expected, v4, 0, 0);
    base_subtraction(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
} END_TEST

START_TEST(test_64_bits_2) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {UINT_MAX, 0, 0};
    unsigned v2[3] = {UINT_MAX, 0, 0};
    unsigned v3[3] = {0, 0, 0};
    unsigned v4[3] = {0, 0, 0};
    init_value(&n1, v1, 0, 0);
    init_value(&n2, v2, 0, 0);
    init_value(&result, v3, 0, 0);
    init_value(&expected, v4, 0, 0);
    base_subtraction(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
} END_TEST

START_TEST(test_96_bits_1) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {UINT_MAX, UINT_MAX, 0};
    unsigned v2[3] = {UINT_MAX, 0, 0};
    unsigned v3[3] = {0, 0, 0};
    unsigned v4[3] = {0, UINT_MAX, 0};
    init_value(&n1, v1, 0, 0);
    init_value(&n2, v2, 0, 0);
    init_value(&result, v3, 0, 0);
    init_value(&expected, v4, 0, 0);
    base_subtraction(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
} END_TEST

START_TEST(test_96_bits_2) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {UINT_MAX, 0, UINT_MAX};
    unsigned v2[3] = {UINT_MAX, 0, 0};
    unsigned v3[3] = {0, 0, 0};
    unsigned v4[3] = {0, 0, UINT_MAX};
    init_value(&n1, v1, 0, 0);
    init_value(&n2, v2, 0, 0);
    init_value(&result, v3, 0, 0);
    init_value(&expected, v4, 0, 0);
    base_subtraction(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
} END_TEST

START_TEST(test_96_bits_3) {
    s21_decimal input1 = {{0, 0xC, 0x7B}};
    s21_decimal input2 = {{1, 0xC, 0x7A}};
    s21_decimal result = {{0}};
    s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, }};
    base_subtraction(input1, input2, &result);
    assert_decimal_eq(result, expected);
}

Suite *base_subtraction_suite(void) {
    Suite *s = suite_create("suite_base_subtraction");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_32_bits);
    tcase_add_test(tc, test_64_bits_1);
    tcase_add_test(tc, test_64_bits_2);
    tcase_add_test(tc, test_96_bits_1);
    tcase_add_test(tc, test_96_bits_2);
    tcase_add_test(tc, test_96_bits_3);

    suite_add_tcase(s, tc);
    return s;
}
