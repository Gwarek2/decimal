#include "test_main.h"

// 4294967295 / 0 = NaN
START_TEST(test_zero_divisor) {
    s21_decimal input1 = {{0xFFFFFFFF, 0, 0, init_sign_and_scale(0, 2)}};
    s21_decimal input2 = {{0, 0, 0, init_sign_and_scale(1, 23)}};
    s21_decimal result;
    int status = s21_div(input1, input2, &result);
    ck_assert_int_eq(status, DEC_DIV_BY_ZERO);
} END_TEST

// 2.25 / -1.5 = -1.5
START_TEST(test_32_bit_1) {
    s21_decimal input1 = {{225, 0, 0, init_sign_and_scale(0, 2)}};
    s21_decimal input2 = {{15, 0, 0, init_sign_and_scale(1, 1)}};
    s21_decimal expected = {{15, 0, 0, init_sign_and_scale(1, 1)}};
    s21_decimal result;
    int status = s21_div(input1, input2, &result);
    ck_assert_int_eq(status, DEC_OK);
    ASSERT_DECIMAL_EQ
} END_TEST

// 2 / 3 = 0.6666666666666666666666666667
START_TEST(test_32_bit_2) {
    s21_decimal input1 = {{2, 0, 0, init_sign_and_scale(0, 0)}};
    s21_decimal input2 = {{3, 0, 0, init_sign_and_scale(0, 0)}};
    s21_decimal expected = {{0xaaaaaab, 0x296e0196, 0x158a8994, init_sign_and_scale(0, 28)}};
    s21_decimal result;
    int status = s21_div(input1, input2, &result);
    ck_assert_int_eq(status, DEC_OK);
    ASSERT_DECIMAL_EQ
} END_TEST

// 1e-28 / 5 = 0
START_TEST(test_32_bit_3) {
    s21_decimal input1 = {{1, 0, 0, init_sign_and_scale(0, 28)}};
    s21_decimal input2 = {{5, 0, 0, init_sign_and_scale(0, 0)}};
    s21_decimal expected = {{0}};
    s21_decimal result;
    int status = s21_div(input1, input2, &result);
    ck_assert_int_eq(status, DEC_OK);
    ASSERT_DECIMAL_EQ
} END_TEST

// 20 / 1e-5 = 400000
START_TEST(test_32_bit_4) {
    s21_decimal input1 = {{20, 0, 0, init_sign_and_scale(0, 0)}};
    s21_decimal input2 = {{5, 0, 0, init_sign_and_scale(0, 5)}};
    s21_decimal expected = {{400000}};
    s21_decimal result;
    int status = s21_div(input1, input2, &result);
    ck_assert_int_eq(status, DEC_OK);
    ASSERT_DECIMAL_EQ
} END_TEST

// Too much precision
// 4449249363747.434387 / 43764 = 101664595.64362111294671419432
START_TEST(test_64_bit_1) {
    s21_decimal input1 = {{0x234C6F93, 0x3DBEE8B9, 0, init_sign_and_scale(0, 6)}};
    s21_decimal input2 = {{0xAAF4, 0, 0, init_sign_and_scale(0, 0)}};
    s21_decimal expected = {{0x373BF828, 0x4ef17458, 0x20d97f8d, init_sign_and_scale(0, 20)}};
    s21_decimal result;
    int status = s21_div(input1, input2, &result);
    ck_assert_int_eq(status, DEC_OK);
    ASSERT_DECIMAL_EQ
} END_TEST

// -936582642837 / 0.1041747302401649 = 8990497414083.03230156190427
START_TEST(test_64_bit_2) {
    s21_decimal input1 = {{0x10ACFC95, 0xDA, 0, init_sign_and_scale(1, 0)}};
    s21_decimal input2 = {{0xB1E7C671, 0x3B376, 0, init_sign_and_scale(0, 16)}};
    s21_decimal expected = {{0x662EB2DB, 0x23EF54FF, 0x2E7AD30, init_sign_and_scale(1, 14)}};
    s21_decimal result;
    int status = s21_div(input1, input2, &result);
    ck_assert_int_eq(status, DEC_OK);
    ASSERT_DECIMAL_EQ
} END_TEST

// -0.3183718237812378127 / -0.3183718237812378127 = 1
START_TEST(test_64_bit_3) {
    s21_decimal input1 = {{0x85BD4A0F, 0x2c2ed6de, 0, init_sign_and_scale(1, 19)}};
    s21_decimal input2 = {{0x85BD4A0F, 0x2c2ed6de, 0, init_sign_and_scale(1, 19)}};
    s21_decimal expected = {{1}};
    s21_decimal result;
    int status = s21_div(input1, input2, &result);
    ck_assert_int_eq(status, DEC_OK);
    ASSERT_DECIMAL_EQ
} END_TEST

// 948347948.43877834 / 1e+16 = 9.4834794843877834e-11
START_TEST(test_64_bit_4) {
    s21_decimal input1 = {{0x530431CA, 0x150EBBE, 0, init_sign_and_scale(1, 8)}};
    s21_decimal input2 = {{0x89E80000, 0x8AC72304}};
    s21_decimal expected = {{0x530431CA, 0x150EBBE, 0, init_sign_and_scale(1, 27)}};
    s21_decimal result = {{0}};
    int status = s21_div(input1, input2, &result);
    ck_assert_int_eq(status, DEC_OK);
    ASSERT_DECIMAL_EQ
} END_TEST

// -184838746726726348023 / 0.00000000193289 = -INF
START_TEST(test_96_bit_1) {
    s21_decimal input1 = {{0x8EEBACF7, 0x52724D4, 0xA, init_sign_and_scale(1, 0)}};
    s21_decimal input2 = {{0x2F309, 0, 0, init_sign_and_scale(0, 14)}};
    s21_decimal result;
    int status = s21_div(input1, input2, &result);
    ck_assert_int_eq(status, DEC_SMALL);
} END_TEST

// 45284674874386437639m / 0.00000000048934 = INF
START_TEST(test_96_bit_2) {
    s21_decimal input1 = {{0xA8DC5607, 0x4737BDEA, 0x27, init_sign_and_scale(0, 0)}};
    s21_decimal input2 = {{0x2F309, 0, 0, init_sign_and_scale(0, 14)}};
    s21_decimal result;
    int status = s21_div(input1, input2, &result);
    ck_assert_int_eq(status, DEC_HUGE);
} END_TEST

// 75384834.34934734873487 / 1349.34984 = 55867.52383603302516037649658
START_TEST(test_96_bit_3) {
    s21_decimal input1 = {{0xE36AE38F, 0xA9793779, 0x198, init_sign_and_scale(0, 14)}};
    s21_decimal input2 = {{0x80AF1C8, 0, 0, init_sign_and_scale(0, 5)}};
    s21_decimal expected = {{0x972204FA, 0x9272C199, 0x120D40D5, init_sign_and_scale(0, 23)}};
    s21_decimal result;
    int status = s21_div(input1, input2, &result);
    ck_assert_int_eq(status, DEC_OK);
    ASSERT_DECIMAL_EQ
} END_TEST

// 7.9228162514264337593543950335 / 0.5 = 15.845632502852867518708790067
START_TEST(test_96_bit_4) {
    s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, init_sign_and_scale(0, 28)}};
    s21_decimal input2 = {{5, 0, 0, init_sign_and_scale(0, 1)}};
    s21_decimal expected = {{0x33333333, 0x33333333, 0x33333333, init_sign_and_scale(0, 27)}};
    s21_decimal result;
    int status = s21_div(input1, input2, &result);
    ck_assert_int_eq(status, DEC_OK);
    ASSERT_DECIMAL_EQ
} END_TEST

// 7922816251426433759354395033.5 / 0.01 = INF
START_TEST(test_96_bit_5) {
    s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, init_sign_and_scale(0, 1)}};
    s21_decimal input2 = {{1, 0, 0, init_sign_and_scale(0, 2)}};
    s21_decimal result;
    int status = s21_div(input1, input2, &result);
    ck_assert_int_eq(status, DEC_HUGE);
} END_TEST

Suite *s21_div_suite() {
    Suite *s = suite_create("suite_s21_div");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_zero_divisor);
    tcase_add_test(tc, test_32_bit_1);
    tcase_add_test(tc, test_32_bit_2);
    tcase_add_test(tc, test_32_bit_3);
    tcase_add_test(tc, test_32_bit_4);
    tcase_add_test(tc, test_64_bit_1);
    tcase_add_test(tc, test_64_bit_2);
    tcase_add_test(tc, test_64_bit_3);
    tcase_add_test(tc, test_64_bit_4);
    tcase_add_test(tc, test_96_bit_1);
    tcase_add_test(tc, test_96_bit_2);
    tcase_add_test(tc, test_96_bit_3);
    tcase_add_test(tc, test_96_bit_4);
    tcase_add_test(tc, test_96_bit_5);
    suite_add_tcase(s, tc);

    return s;
}
