#include "test_main.h"

START_TEST(test_all_eq_1) {
    s21_decimal n1, n2;
    unsigned v1[3] = {UINT_MAX, UINT_MAX, UINT_MAX};
    unsigned v2[3] = {UINT_MAX, UINT_MAX, UINT_MAX};
    init_value(&n1, v1, 6, 0);
    init_value(&n2, v2, 2, 1);

    ck_assert_int_eq(bits_eq(n1, n2), 1);
}
END_TEST

START_TEST(test_neq_1) {
    s21_decimal n1, n2;
    unsigned v1[3] = {0, UINT_MAX, UINT_MAX};
    unsigned v2[3] = {UINT_MAX, UINT_MAX, UINT_MAX};
    init_value(&n1, v1, 6, 0);
    init_value(&n2, v2, 3, 1);

    ck_assert_int_eq(bits_eq(n1, n2), 0);
}
END_TEST

START_TEST(test_neq_2) {
    s21_decimal n1, n2;
    unsigned v1[3] = {0, UINT_MAX, 0};
    unsigned v2[3] = {0, 0, 0};
    init_value(&n1, v1, 6, 0);
    init_value(&n2, v2, 3, 1);

    ck_assert_int_eq(bits_eq(n1, n2), 0);
}
END_TEST

Suite *bits_eq_suite(void) {
    Suite *s = suite_create("suite_bits_eq");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_all_eq_1);
    tcase_add_test(tc, test_neq_1);
    tcase_add_test(tc, test_neq_2);

    suite_add_tcase(s, tc);
    return s;
}
