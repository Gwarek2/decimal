#include "test_main.h"

START_TEST(compare_01) {
    s21_decimal a = {{0, 0, 0, 0}};
    s21_decimal b = {{0, 0, 0, 0}};
    ck_assert_int_eq(s21_is_less(a, b), 0);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_greater(a, b), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_equal(a, b), 1);
    ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(compare_02) {
    s21_decimal a = {{123, 123, 123, 0}};
    s21_decimal b = {{123, 123, 123, 0}};
    ck_assert_int_eq(s21_is_less(a, b), 0);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_greater(a, b), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_equal(a, b), 1);
    ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(compare_03) {
    s21_decimal a = {{123, 0, 0, 0}};
    s21_decimal b = {{123, 0, 0, -2147483648}};
    ck_assert_int_eq(s21_is_less(a, b), 0);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
    ck_assert_int_eq(s21_is_greater(a, b), 1);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_equal(a, b), 0);
    ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_04) {
    s21_decimal a = {{0xffffffff, 0xffffffff, 0, 1835008}};
    s21_decimal b = {{0xffffffff, 0xfffffffe, 0, 1835008}};
    ck_assert_int_eq(s21_is_less(a, b), 0);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
    ck_assert_int_eq(s21_is_greater(a, b), 1);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_equal(a, b), 0);
    ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_05) {
    s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 65536}};
    s21_decimal b = {{0xffffffff, 0xffffffff, 0xffffffff, 196608}};
    ck_assert_int_eq(s21_is_less(a, b), 0);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
    ck_assert_int_eq(s21_is_greater(a, b), 1);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_equal(a, b), 0);
    ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_06) {
    s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 65536}};
    s21_decimal b = {{0xffffffff, 0xffffffff, 0xffffffff, 196608}};
    ck_assert_int_eq(s21_is_less(a, b), 0);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
    ck_assert_int_eq(s21_is_greater(a, b), 1);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_equal(a, b), 0);
    ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_07) {
    s21_decimal a = {{0x99999999, 0xfefefefe, 0xffffffff, -2147483648}};
    s21_decimal b = {{0x99999999, 0xfefefefe, 0xffffffee, -2147483648}};
    ck_assert_int_eq(s21_is_less(a, b), 1);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_greater(a, b), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
    ck_assert_int_eq(s21_is_equal(a, b), 0);
    ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_08) {
    s21_decimal a = {{12345600, 0, 0, 196608}};
    s21_decimal b = {{123456, 0, 0, 65536}};
    ck_assert_int_eq(s21_is_less(a, b), 0);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_greater(a, b), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_equal(a, b), 1);
    ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(compare_09) {
    s21_decimal a = {{12345678, 0, 0, 0}};
    s21_decimal b = {{123456781, 0, 0, 65536}};
    ck_assert_int_eq(s21_is_less(a, b), 1);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_greater(a, b), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
    ck_assert_int_eq(s21_is_equal(a, b), 0);
    ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_10) {
    s21_decimal a = {{0, 0, 0, 0}};
    s21_decimal b = {{0, 0, 0, -2147483648}};
    ck_assert_int_eq(s21_is_less(a, b), 0);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_greater(a, b), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_equal(a, b), 1);
    ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

Suite *s21_compare_suite() {
    Suite *s = suite_create("suite_compare_suite");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, compare_01);
    tcase_add_test(tc, compare_02);
    tcase_add_test(tc, compare_03);
    tcase_add_test(tc, compare_04);
    tcase_add_test(tc, compare_05);
    tcase_add_test(tc, compare_06);
    tcase_add_test(tc, compare_07);
    tcase_add_test(tc, compare_08);
    tcase_add_test(tc, compare_09);
    tcase_add_test(tc, compare_10);
    suite_add_tcase(s, tc);

    return s;
}
