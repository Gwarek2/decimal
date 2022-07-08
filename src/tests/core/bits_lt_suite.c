#include "test_main.h"

START_TEST(test_less_1) {
    s21_decimal n1, n2;
    unsigned v1[3] = {123, 0, 0};
    unsigned v2[3] = {124, 0, 0};
    init_value(&n1, v1, 6, 0);
    init_value(&n2, v2, 2, 1);

    ck_assert_int_eq(bits_lt(n1, n2), 1);
} END_TEST

START_TEST(test_less_2) {
    s21_decimal n1, n2;
    unsigned v1[3] = {1212, 4352, 12};
    unsigned v2[3] = {1, 0, 13};
    init_value(&n1, v1, 6, 0);
    init_value(&n2, v2, 2, 1);

    ck_assert_int_eq(bits_lt(n1, n2), 1);
} END_TEST

START_TEST(test_less_3) {
    s21_decimal n1, n2;
    unsigned v1[3] = {0, 123, 78};
    unsigned v2[3] = {1, 123, 78};
    init_value(&n1, v1, 6, 0);
    init_value(&n2, v2, 2, 1);

    ck_assert_int_eq(bits_lt(n1, n2), 1);
} END_TEST

START_TEST(test_less_4) {
    s21_decimal n1, n2;
    unsigned v1[3] = {434, 1, 221};
    unsigned v2[3] = {1, 123, 221};
    init_value(&n1, v1, 6, 0);
    init_value(&n2, v2, 2, 1);

    ck_assert_int_eq(bits_lt(n1, n2), 1);
} END_TEST

START_TEST(test_nless_1) {
    s21_decimal n1, n2;
    unsigned v1[3] = {1, 2, 3};
    unsigned v2[3] = {3, 2, 1};
    init_value(&n1, v1, 6, 0);
    init_value(&n2, v2, 3, 1);

    ck_assert_int_eq(bits_lt(n1, n2), 0);
} END_TEST

START_TEST(test_nless_2) {
    s21_decimal n1, n2;
    unsigned v1[3] = {123, 1234, 12345};
    unsigned v2[3] = {123, 1234, 12345};
    init_value(&n1, v1, 6, 0);
    init_value(&n2, v2, 3, 1);

    ck_assert_int_eq(bits_lt(n1, n2), 0);
} END_TEST

Suite *bits_lt_suite(void) {
    Suite *s = suite_create("suite_bits_lt");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_less_1);
    tcase_add_test(tc, test_less_2);
    tcase_add_test(tc, test_less_3);
    tcase_add_test(tc, test_less_4);
    tcase_add_test(tc, test_nless_1);
    tcase_add_test(tc, test_nless_2);

    suite_add_tcase(s, tc);
    return s;
}
