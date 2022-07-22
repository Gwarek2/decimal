#include "test_main.h"

START_TEST(test_decimal_max) {
    uint192 input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    uint192 input2 = {{0x10000000, 0x3E250261, 0x204FCE5E}};
    uint192 expected = {{0xF0000000, 0xC1DAFD9E, 0xDFB031A1, 0xFFFFFFF, 0x3E250261, 0x204FCE5E}};
    uint192 result = {{0}};
    mul_uint192(input1, input2, &result);
    ASSERT_UINT192_EQ
} END_TEST

Suite *uint192_mul_suite() {
    Suite *s = suite_create("suite_uint192_mul");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_decimal_max);
    suite_add_tcase(s, tc);
    return s;
}
