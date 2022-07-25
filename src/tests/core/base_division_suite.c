#include "test_main.h"

START_TEST(test_32_bits_1) {
    s21_decimal n1, result, expected, remainder;
    unsigned v1[3] = {0, 0, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&expected, b_zero, 0, 0);
    init_value(&result, b_zero, 0, 0);
    base_divide(n1, DEC_TEN, &result, &remainder);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_32_bits_2) {
    s21_decimal n1, n2, result, expected, remainder;
    unsigned v1[3] = {0xfffffffe, 0, 0};
    unsigned v2[3] = {2, 0, 0};
    unsigned v3[3] = {0x7fffffff, 0, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&n2, v2, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v3, 0, 0);
    base_divide(n1, n2, &result, &remainder);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_32_bits_3) {
    s21_decimal n1, n2, result, expected, remainder;
    unsigned v1[3] = {556890, 0, 0};
    unsigned v2[3] = {3, 0, 0};
    unsigned v3[3] = {185630, 0, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&n2, v2, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v3, 0, 0);
    base_divide(n1, n2, &result, &remainder);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_64_bits_1) {
    s21_decimal n1, n2, result, expected, remainder;
    unsigned v1[3] = {0xffffffff, 0xffffffff, 0};
    unsigned v2[3] = {2, 0, 0};
    unsigned v3[3] = {0xffffffff, 0x7fffffff, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&n2, v2, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v3, 0, 0);
    base_divide(n1, n2, &result, &remainder);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_64_bits_2) {
    s21_decimal n1, n2, result, expected, remainder;
    unsigned v1[3] = {0x1, 0xfffffffe, 0};
    unsigned v2[3] = {0xffffffff, 0, 0};
    unsigned v3[3] = {0xffffffff, 0, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&n2, v2, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v3, 0, 0);
    base_divide(n1, n2, &result, &remainder);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_64_bits_3) {
    s21_decimal n1, n2, result, expected, remainder;
    unsigned v1[3] = {0x1, 0xfffffffe, 0};
    unsigned v2[3] = {5, 0, 0};
    unsigned v3[3] = {0xcccccccd, 0x33333332, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&n2, v2, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v3, 0, 0);
    base_divide(n1, n2, &result, &remainder);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_96_bits_1) {
    s21_decimal n1, n2, result, expected, remainder;
    unsigned v1[3] = {0xfffffff0, 0xffffffff, 0xffffffff};
    unsigned v2[3] = {2, 0, 0};
    unsigned v3[3] = {0xfffffff8, 0xffffffff, 0x7fffffff};
    init_value(&n1, v1, 1, 23);
    init_value(&n2, v2, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v3, 0, 0);
    base_divide(n1, n2, &result, &remainder);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_96_bits_2) {
    s21_decimal n1, result, expected_res, remainder, expected_rem;
    unsigned v1[3] = {0xffffffff, 0xffffffff, 0xffffffff};
    unsigned v2[3] = {0x99999999, 0x99999999, 0x19999999};
    unsigned v3[3] = {5, 0, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&remainder, b_zero, 0, 0);
    init_value(&expected_res, v2, 0, 0);
    init_value(&expected_rem, v3, 0, 0);
    base_divide(n1, DEC_TEN, &result, &remainder);

    ck_assert_uint_eq(expected_res.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected_res.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected_res.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected_res.bits[3], result.bits[3]);

    ck_assert_uint_eq(expected_rem.bits[0], remainder.bits[0]);
    ck_assert_uint_eq(expected_rem.bits[1], remainder.bits[1]);
    ck_assert_uint_eq(expected_rem.bits[2], remainder.bits[2]);
    ck_assert_uint_eq(expected_rem.bits[3], remainder.bits[3]);
}
END_TEST

Suite *base_divide_suite(void) {
    Suite *s = suite_create("suite_base_divide");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_32_bits_1);
    tcase_add_test(tc, test_32_bits_2);
    tcase_add_test(tc, test_32_bits_3);
    tcase_add_test(tc, test_64_bits_1);
    tcase_add_test(tc, test_64_bits_2);
    tcase_add_test(tc, test_64_bits_3);
    tcase_add_test(tc, test_96_bits_1);
    tcase_add_test(tc, test_96_bits_2);
    suite_add_tcase(s, tc);
    return s;
}
