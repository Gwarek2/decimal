#include "test_main.h"

START_TEST(test_32_bits_1) {
    s21_decimal value_1 = {{55555, 0, 0, 0}};
    s21_decimal value_2 = {{66666, 0, 0, 262144}};
    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{555483334, 0, 0, 262144}};
    int function_returned = s21_sub(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_OK);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
} END_TEST

START_TEST(test_64_bits_1) {
    s21_decimal value_1 = {{max32bit, 0, 0, 0}};
    s21_decimal value_2 = {{max32bit, 100, 0, 0}};
    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{0, 100, 0, 2147483648 }};
    int function_returned = s21_sub(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_OK);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
} END_TEST

START_TEST(test_96_bits_1) {
    s21_decimal value_1 = {{max32bit, max32bit, 2147483647, 1638400}};
    s21_decimal value_2 = {{max32bit, max32bit, 0, 983040}};
    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{4153960755, 858993458, 785251635, 2149056512}};
    int function_returned = s21_sub(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_OK);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
}

START_TEST(test_96_bits_2) {
    s21_decimal value_1 = {{max32bit, max32bit, max32bit, 0}};
    s21_decimal value_2 = {{4294967294, max32bit, max32bit, 0}}; 
    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{1, 0, 0, 0 }};
    int function_returned = s21_sub(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_OK);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
}

START_TEST(test_96_bits_3) {
    s21_decimal value_1 = {{max32bit, max32bit, max32bit, 1835008}};
    s21_decimal value_2 = {{4294967294, max32bit, max32bit, 0}};

    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{4294967286, max32bit, max32bit, 2147483648}};
    int function_returned = s21_sub(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_OK);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
} END_TEST

Suite *s21_sub_suite(void) {
    Suite *s = suite_create("s21_sub_suite");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_32_bits_1);
    tcase_add_test(tc, test_64_bits_1);
    tcase_add_test(tc, test_96_bits_1);
    tcase_add_test(tc, test_96_bits_2);
    tcase_add_test(tc, test_96_bits_3);

    suite_add_tcase(s, tc);
    return s;
}