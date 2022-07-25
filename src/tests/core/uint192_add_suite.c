#include "test_main.h"

START_TEST(test_192bit_1) {
    uint192 input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    uint192 input2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    uint192 result = {{0}};
    uint192 expected = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1}};
    add_uint192(input1, input2, &result);
    ASSERT_UINT192_EQ
}
END_TEST

Suite *uint192_add_suite() {
    Suite *s = suite_create("suite_uint192_add");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_192bit_1);
    suite_add_tcase(s, tc);
    return s;
}
