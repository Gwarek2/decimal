#include "test_main.h"

const unsigned max32bit = 4294967295;
const unsigned maxScale = 1835008;

START_TEST(test_32_bits_1) {
    s21_decimal result = {{555000, 0, 0, maxScale}};
    s21_decimal expected = {{555, 0, 0, 1638400}};
    s21_decimal scale = {{0, 0, 0, maxScale}};
    alignment_scale(&expected, &scale);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
} END_TEST

START_TEST(test_64_bits_1) {
    s21_decimal result = {{4294867296, 99999, 0, 327680}};
    s21_decimal expected = {{max32bit, 0, 0, 0}};
    s21_decimal scale = {{0, 0, 0, 327680}};
    alignment_scale(&expected, &scale);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
} END_TEST

START_TEST(test_96_bits_1) {
    s21_decimal result = {{727379968, 3567587095, 232, 983040}};
    s21_decimal expected = {{max32bit, 0, 0, 196608}};
    s21_decimal scale = {{0, 0, 0, 983040}};
    alignment_scale(&scale, &expected);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
} END_TEST

Suite *alignment_scale_suite(void) {
    Suite *s = suite_create("alignment_scale_suite");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_32_bits_1);
    tcase_add_test(tc, test_64_bits_1);
    tcase_add_test(tc, test_96_bits_1);
    suite_add_tcase(s, tc);
    return s;
}