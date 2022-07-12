#include "test_main.h"

void add_trailing_numbers(s21_decimal *value, int scale, int sign) {
    s21_decimal ov;
    base_multiply(*value, ten_power[scale], value, &ov);
    set_scale(value, scale);
    set_sign(value, sign);
}

START_TEST(test_int_max) {
    s21_decimal src;
    int expected = INT_MAX, result = 0;
    unsigned mantiss[3] = {INT_MAX, 0, 0};

    init_value(&src, mantiss, 0, 0);
    add_trailing_numbers(&src, _i, 0);
    int status = s21_from_decimal_to_int(src, &result);

    ck_assert_int_eq(result, expected);
    ck_assert_int_eq(status, 0);
}

START_TEST(test_int_min) {
    s21_decimal src;
    int expected = INT_MIN, result = 0;
    unsigned mantiss[3] = {INT_MIN, 0, 0};

    init_value(&src, mantiss, 1, 0);
    add_trailing_numbers(&src, _i, 1);
    int status = s21_from_decimal_to_int(src, &result);

    ck_assert_int_eq(result, expected);
    ck_assert_int_eq(status, 0);
}

START_TEST(test_int_min_pos) {
    s21_decimal src;
    int expected = -1, result = -1;
    unsigned mantiss[3] = {INT_MIN, 0, 0};

    init_value(&src, mantiss, 0, 0);
    add_trailing_numbers(&src, _i, 0);
    int status = s21_from_decimal_to_int(src, &result);

    ck_assert_int_eq(result, expected);
    ck_assert_int_eq(status, 1);
}

START_TEST(test_int_pos_random) {
    s21_decimal src;
    int sign = rand() % 2;
    int expected = rand() % (sign ? INT_MIN : INT_MAX), result = 0;
    if (sign) expected = -expected;

    unsigned mantiss[3] = {sign ? -expected : expected, 0, 0};

    init_value(&src, mantiss, sign, 0);
    add_trailing_numbers(&src, rand() % 19, sign);
    int status = s21_from_decimal_to_int(src, &result);

    ck_assert_int_eq(result, expected);
    ck_assert_int_eq(status, 0);
}

Suite *s21_from_decimal_to_int_suite() {
    Suite *s = suite_create("suite_from_decimal_to_int_suite");
    TCase *tc = tcase_create("core");

    tcase_add_loop_test(tc, test_int_max, 0, 18);
    tcase_add_loop_test(tc, test_int_min, 0, 18);
    tcase_add_loop_test(tc, test_int_min_pos, 0, 18);
    tcase_add_loop_test(tc, test_int_pos_random, 0, 1000);

    suite_add_tcase(s, tc);
    return s;
}
