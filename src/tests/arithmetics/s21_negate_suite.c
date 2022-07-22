#include "test_main.h"

START_TEST(test_pos_max) {
    s21_decimal input, result, expected;
    init_default(&result);
    copy_full(&input, &DEC_MAX);
    copy_full(&expected, &DEC_MAX);
    set_sign(&expected, 1);

    int status = s21_negate(input, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, 0);
}

START_TEST(test_neg_max) {
    s21_decimal input, result, expected;
    init_default(&result);
    copy_full(&input, &DEC_MAX);
    set_sign(&input, 1);
    copy_full(&expected, &DEC_MAX);
    set_sign(&expected, 0);

    int status = s21_negate(input, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, 0);
}

START_TEST(test_null) {
    s21_decimal input;
    s21_decimal *result = NULL;
    init_default(&input);

    int status = s21_negate(input, result);
    ck_assert_int_eq(status, 1);
}

START_TEST(test_pos_zero) {
    s21_decimal result, input, expected;
    init_default(&input);
    init_default(&expected);
    set_sign(&expected, 0);

    int status = s21_negate(input, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, 0);
}

START_TEST(test_neg_zero) {
    s21_decimal result, input, expected;
    init_default(&input);
    set_sign(&input, 1);
    init_default(&expected);
    set_sign(&expected, 0);

    int status = s21_negate(input, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, 0);
}

Suite *s21_negate_suite() {
    Suite *s  = suite_create("suite_s21_negate");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_pos_max);
    tcase_add_test(tc, test_neg_max);
    tcase_add_test(tc, test_null);
    tcase_add_test(tc, test_pos_zero);
    tcase_add_test(tc, test_neg_zero);
    suite_add_tcase(s, tc);

    return s;
}
