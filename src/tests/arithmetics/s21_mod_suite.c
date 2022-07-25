#include "test_main.h"

START_TEST(test_32_bits_1) {
    s21_decimal value_1 = {{55555, 0, 0, 0}};
    s21_decimal value_2 = {{66666, 0, 0, 262144}};
    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{22222, 0, 0, 262144}};
    int function_returned = s21_mod(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_OK);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
}
END_TEST

START_TEST(test_64_bits_1) {
    s21_decimal value_1 = {{5555, 345635, 0, 327680}};
    s21_decimal value_2 = {{333333333, 56765, 0, 458752}};
    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{3492319244, 50332, 0, 458752}};
    int function_returned = s21_mod(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_OK);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
}
END_TEST

START_TEST(test_96_bits_1) {
    s21_decimal value_1 = {{5555, 345635, 3456, 786432}};
    s21_decimal value_2 = {{333333333, 56765, 4567, 1114112}};
    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{565121299, 203145210, 1416, 1114112}};
    int function_returned = s21_mod(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_OK);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
}
END_TEST

START_TEST(test_DEC_DIV_BY_ZERO) {
    s21_decimal value_1 = {{5555, 345635, 0, 327680}};
    s21_decimal value_2 = {{0, 0, 0, 0}};
    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{0, 0, 0, 0}};
    int function_returned = s21_mod(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_DIV_BY_ZERO);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
}
END_TEST

START_TEST(test_first_num_zero) {
    s21_decimal value_1 = {{0, 0, 0, 786432}};
    s21_decimal value_2 = {{2452, 45646, 4564, 1114112}};
    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{0, 0, 0, 1114112}};
    int function_returned = s21_mod(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_OK);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
}
END_TEST

Suite *s21_mod_suite(void) {
    Suite *s = suite_create("s21_mod_suite");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_32_bits_1);
    tcase_add_test(tc, test_64_bits_1);
    tcase_add_test(tc, test_96_bits_1);
    tcase_add_test(tc, test_DEC_DIV_BY_ZERO);
    tcase_add_test(tc, test_first_num_zero);

    suite_add_tcase(s, tc);
    return s;
}
