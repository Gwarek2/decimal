#include "test_main.h"


START_TEST(test_32_bits_1) {
    s21_decimal value_1 = {{55555, 0, 0, 0 }};
    s21_decimal value_2 = {{66666, 0, 0, 262144}};
    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{555616666, 0, 0, 262144}};
    int function_returned = s21_add(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_OK);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
} END_TEST

START_TEST(test_32_bits_2) {
    s21_decimal value_1 = {{5555, 0, 0, 2147483648}};
    s21_decimal value_2 = {{333333333, 0, 0, 327680}};
    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{222166667, 0, 0, 2147811328}};
    int function_returned = s21_add(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_OK);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
} END_TEST

START_TEST(test_64_bits_1) {
    s21_decimal value_1 = {{max32bit, 0, 0, 327680}};
    s21_decimal value_2 = {{max32bit, 100, 0, 2148139008}};
    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{4294867297, 99898, 0, 655360}};
    int function_returned = s21_add(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_OK);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
} END_TEST

START_TEST(test_64_bits_2) {
    s21_decimal value_1 = {{max32bit, 613566756, 0, 2147811328}};
    s21_decimal value_2 = {{max32bit, 214748364, 0, 2147745792}};
    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{4294967285, 2761050406, 0, 2147811328}};
    int function_returned = s21_add(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_OK);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
} END_TEST

START_TEST(test_64_bits_3) {
    s21_decimal value_1 = {{346456, 53345, 0, 2147942400}};
    s21_decimal value_2 = {{567567, 3456567, 0, 262144}};
    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{567220544, 3456513655, 0, 458752}};
    int function_returned = s21_add(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_OK);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
} END_TEST

START_TEST(test_96_bits_1) {
    s21_decimal value_1 = {{max32bit, max32bit, 2147483647, 1638400}};
    s21_decimal value_2 = {{max32bit, max32bit, 0, 2148466688}};
    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{4153960755, 858993458, 785251635, 2149056512}};
    int function_returned = s21_add(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_OK);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
}

START_TEST(test_96_bits_2) {
    s21_decimal value_1 = {{max32bit, max32bit, max32bit, 1638400}};
    s21_decimal value_2 = {{max32bit, max32bit, max32bit, 2148466688}}; 
    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{2701727008, 2450292888, max32bit, 2148466688}};
    int function_returned = s21_add(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_OK);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
}

// 79228162514264337593543950335 + (-0.54) = 79228162514264337593543950334
START_TEST(test_96_bits_3) {
    s21_decimal value_1 = {{max32bit, max32bit, max32bit}};
    s21_decimal value_2 = {{54, 0, 0, init_sign_and_scale(1, 2)}}; 
    s21_decimal result = {{0}};
    s21_decimal expected = {{0xFFFFFFFE, max32bit, max32bit}};
    int function_returned = s21_add(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_OK);
    ASSERT_DECIMAL_EQ
}

// 79228162514264337593543950334 + 1.5 = INF
START_TEST(test_96_bits_overflow) {
    s21_decimal value_1 = {{4294967294, max32bit, max32bit, 0}};
    s21_decimal value_2 = {{15, 0, 0, 65536}};

    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{0, 0, 0, 0}};
    int function_returned = s21_add(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_HUGE);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
} END_TEST

START_TEST(test_96_bits_overflow_2) {
    s21_decimal value_1 = {{max32bit, max32bit, max32bit, 2147483648}};
    s21_decimal value_2 = {{1, 0, 0, 2147483648}};

    s21_decimal result = {{0}};
    s21_decimal correct_answer = {{0, 0, 0, 0}};
    int function_returned = s21_add(value_1, value_2, &result);

    ck_assert_uint_eq(function_returned, DEC_SMALL);
    ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
    ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
    ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
    ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
} END_TEST

Suite *s21_add_suite(void) {
    Suite *s = suite_create("s21_add_suite");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_32_bits_1);
    tcase_add_test(tc, test_32_bits_2);
    tcase_add_test(tc, test_64_bits_1);
    tcase_add_test(tc, test_64_bits_2);
    tcase_add_test(tc, test_64_bits_3);
    tcase_add_test(tc, test_96_bits_1);
    tcase_add_test(tc, test_96_bits_2);
    tcase_add_test(tc, test_96_bits_3);
    tcase_add_test(tc, test_96_bits_overflow);
    tcase_add_test(tc, test_96_bits_overflow_2);

    suite_add_tcase(s, tc);
    return s;
}
