#include "test_main.h"

START_TEST(test_32_bits_1) {
    s21_decimal n, result, expected;
    unsigned v1[3] = {1234500000, 0, 0};
    unsigned v2[3] = {12345, 0, 0};
    init_value(&n, v1, 1, 9);         // 1.234500000
    init_value(&expected, v2, 1, 4);  // 1.2345
    remove_trailing_zeros(n, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_32_bits_2) {
    s21_decimal n, result, expected;
    unsigned v1[3] = {12345, 0, 0};
    unsigned v2[3] = {12345, 0, 0};
    init_value(&n, v1, 0, 0);         // 12345
    init_value(&expected, v2, 0, 0);  // 12345
    remove_trailing_zeros(n, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_32_bits_3) {
    s21_decimal n, result, expected;
    unsigned v1[3] = {12345, 0, 0};
    unsigned v2[3] = {12345, 0, 0};
    init_value(&n, v1, 0, 2);         // 123.45
    init_value(&expected, v2, 0, 2);  // 123.45
    remove_trailing_zeros(n, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_64_bits_1) {
    s21_decimal n, result, expected;
    unsigned v1[3] = {0x860daf40, 0x7048, 0};
    unsigned v2[3] = {0x75bcd15, 0, 0};
    init_value(&n, v1, 1, 7);         // 12345678.9000000
    init_value(&expected, v2, 1, 1);  // 12345678.9
    remove_trailing_zeros(n, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_64_bits_2) {
    s21_decimal n, result, expected;
    unsigned v1[3] = {0x860daf40, 0x7048, 0};
    unsigned v2[3] = {0x71fb0450, 0x11f, 0};
    init_value(&n, v1, 1, 2);         // 1234567890000.00
    init_value(&expected, v2, 1, 0);  // 1234567890000
    remove_trailing_zeros(n, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_64_bits_3) {
    s21_decimal n, result, expected;
    unsigned v1[3] = {0x860daf40, 0x7048, 0};
    unsigned v2[3] = {0x860daf40, 0x7048, 0};
    init_value(&n, v1, 0, 0);         // 123456789000000
    init_value(&expected, v2, 0, 0);  // 123456789000000
    remove_trailing_zeros(n, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_96_bits_1) {
    s21_decimal n, result, expected;
    unsigned v1[3] = {0xfd43d980, 0xf3f855cc, 0x10ea};
    unsigned v2[3] = {0x272b685f, 0x1c6222, 0};
    init_value(&n, v1, 1, 16);        // 7989198.1734646710000000
    init_value(&expected, v2, 1, 9);  // 7989198.173464671
    remove_trailing_zeros(n, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_96_bits_2) {
    s21_decimal n, result, expected;
    unsigned v1[3] = {0xcfc3b900, 0x4590f8dc, 0x9f1094e5};
    unsigned v2[3] = {0x58a5787a, 0xddcca279, 0x10a};
    init_value(&n, v1, 1, 23);         // 49228.162514264337593540000000
    init_value(&expected, v2, 1, 16);  // 49228.16251426433759354
    remove_trailing_zeros(n, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_96_bits_3) {
    s21_decimal n, result, expected;
    unsigned v1[3] = {0x991CEE8B, 0x128342B1, 0xCBD53600};
    unsigned v2[3] = {0x991CEE8B, 0x128342B1, 0xCBD53600};
    init_value(&n, v1, 1, 0);         // 47386182914269337599000000000
    init_value(&expected, v2, 1, 0);  // 47386182914269337599000000000
    remove_trailing_zeros(n, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
}
END_TEST

Suite *remove_trailing_zeros_suite() {
    Suite *s = suite_create("suite_remove_trailing_zeros");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_32_bits_1);
    tcase_add_test(tc, test_32_bits_2);
    tcase_add_test(tc, test_32_bits_3);
    tcase_add_test(tc, test_64_bits_1);
    tcase_add_test(tc, test_64_bits_2);
    tcase_add_test(tc, test_64_bits_3);
    tcase_add_test(tc, test_96_bits_1);
    tcase_add_test(tc, test_96_bits_2);
    tcase_add_test(tc, test_96_bits_3);

    suite_add_tcase(s, tc);
    return s;
}
