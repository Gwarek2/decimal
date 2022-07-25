#include "test_main.h"

void assert_uint192_eq(uint192 result, uint192 expected) {
    for (size_t i = 0; i < 6; i++) {
        ck_assert_msg(result.bits[i] == expected.bits[i],
                      "[%zu] %#x != %#x", i, result.bits[i], expected.bits[i]);
    }
}

START_TEST(test_192bit_1) {
    uint192 input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    uint192 input2 = {{2}};
    uint192 res = {{0}};
    uint192 res_rem = {{0}};
    uint192 expected_res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
    uint192 expected_rem = {{1}};
    divide_uint192(input1, input2, &res, &res_rem); 
    assert_uint192_eq(res, expected_res);
    assert_uint192_eq(res_rem, expected_rem);
} END_TEST

START_TEST(test_192bit_2) {
    uint192 input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    uint192 input2 = {{0xFFFFFFFF, 0xFFFFFFFF}};
    uint192 res = {{0}};
    uint192 res_rem = {{0}};
    uint192 expected_res = {{0x1, 0, 0x1, 0, 0x1}};
    uint192 expected_rem = {{0}};
    divide_uint192(input1, input2, &res, &res_rem); 
    assert_uint192_eq(res, expected_res);
    assert_uint192_eq(res_rem, expected_rem);
} END_TEST

START_TEST(test_192bit_3) {
    uint192 input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    uint192 res = {{0}};
    uint192 res_rem = {{0}};
    uint192 expected_res = {{0x99999999, 0x99999999, 0x99999999, 0x99999999, 0x99999999, 0x19999999}};
    uint192 expected_rem = {{0x5}};
    divide_uint192(input1, UINT192_TEN, &res, &res_rem); 
    assert_uint192_eq(res, expected_res);
    assert_uint192_eq(res_rem, expected_rem);
} END_TEST

START_TEST(test_192bit_4) {
    uint192 input1 = {{0x3efab304, 0x9d2}};
    uint192 res = {{0}};
    uint192 res_rem = {{0}};
    uint192 expected_res = {{0x6cb2ab80, 0xfb}};
    uint192 expected_rem = {{0x4}};
    divide_uint192(input1, UINT192_TEN, &res, &res_rem); 
    assert_uint192_eq(res, expected_res);
    assert_uint192_eq(res_rem, expected_rem);
} END_TEST

Suite *uint192_division_suite() {
    Suite *s = suite_create("suite_uint192_division");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_192bit_1);
    tcase_add_test(tc, test_192bit_2);
    tcase_add_test(tc, test_192bit_3);
    tcase_add_test(tc, test_192bit_4);
    suite_add_tcase(s, tc);
    return s;
}
