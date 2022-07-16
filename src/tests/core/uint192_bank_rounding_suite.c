#include "test_main.h"

START_TEST(test_gt_five) {
    uint192 input = {{0xf27eab8f, 0x37d,}};
    uint192 expected = {{0x650caac2, 0x59}};
    uint192 result = {{0}};
    bank_rounding_uint192(input, &result);
    assert_uint192_eq(result, expected);
}

START_TEST(test_lt_five) {
    uint192 input = {{0x3efab304, 0x9d2}};
    uint192 expected = {{0x6cb2ab80, 0xfb}};
    uint192 result = {{0}};
    bank_rounding_uint192(input, &result);
    assert_uint192_eq(result, expected);
}

START_TEST(test_eq_five_even_end) {
    uint192 input = {{0x139fc305, 0xabb}};
    uint192 expected = {{0xb5299380, 0x112}};
    uint192 result = {{0}};
    bank_rounding_uint192(input, &result);
    assert_uint192_eq(result, expected);
}

START_TEST(test_eq_five_odd_end) {
    uint192 input = {{0xb51a512c, 0x112}};
    uint192 expected = {{0x7882a1b8, 0x1b}};
    uint192 result = {{0}};
    bank_rounding_uint192(input, &result);
    assert_uint192_eq(result, expected);
}

Suite *bank_rounding_uint192_suite() {
    Suite *s = suite_create("suite_bank_rounding_uint192");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_gt_five);
    tcase_add_test(tc, test_lt_five);
    tcase_add_test(tc, test_eq_five_even_end);
    tcase_add_test(tc, test_eq_five_odd_end);
    suite_add_tcase(s, tc);
    return s;
}
