#include "test_main.h"

void add_trailing_zeroes(s21_decimal *value, int scale) {
    s21_decimal ov;
    base_multiply(*value, ten_power[scale], value, &ov);
    set_scale(value, scale);
}

START_TEST(test_int_max) {
    s21_decimal src;
    int expected = INT_MAX, result = 0;
    unsigned mantiss[3] = {INT_MAX, 0, 0};

    init_value(&src, mantiss, 0, 0);
    add_trailing_zeroes(&src, _i);
    int status = s21_from_decimal_to_int(src, &result);

    ck_assert_int_eq(result, expected);
    ck_assert_int_eq(status, 0);
}

Suite *s21_from_decimal_to_int_suite() {
    Suite *s = suite_create("suite_from_decimal_to_int_suite");
    TCase *tc = tcase_create("core");

    tcase_add_loop_test(tc, test_int_max, 0, 18);

    suite_add_tcase(s, tc);
    return s;
}
