#include "test_main.h"

START_TEST(test_9_overflow_start) {
    s21_decimal input = {{0x9fffffff, 0xd902d61f, 0x5c0e8d21, init_sign_and_scale(0, 3)}};
    s21_decimal overflow = {{0xc, 0, 0, 0}};
    s21_decimal result;
    s21_decimal expected = {{0x50f5c28f, 0x94171180, 0x1fa3fc4a}};

    round_overflowed_decimal(input, overflow, &result, 3);
    assert_decimal_eq(result, expected);
} END_TEST

Suite *round_overflowed_decimal_suite() {
    Suite *s = suite_create("suite_round_overflowed_decimal");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_9_overflow_start);

    suite_add_tcase(s, tc);
    return s;
}
