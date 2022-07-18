#include "test_main.h"

void assert_decimal_eq(s21_decimal result, s21_decimal expected) {
    ck_assert_msg(result.bits[0] == expected.bits[0], "[0] %#x != %#x", result.bits[0], expected.bits[0]);
    ck_assert_msg(result.bits[1] == expected.bits[1], "[1] %#x != %#x", result.bits[1], expected.bits[1]);
    ck_assert_msg(result.bits[2] == expected.bits[2], "[2] %#x != %#x", result.bits[2], expected.bits[2]);
    ck_assert_msg(result.bits[3] == expected.bits[3], "[3] %#x != %#x", result.bits[3], expected.bits[3]);
}

void assert_uint192_eq(uint192 result, uint192 expected) {
    for (size_t i = 0; i < 6; i++) {
        ck_assert_msg(result.bits[i] == expected.bits[i],
                      "[%zu] %#x != %#x", i, result.bits[i], expected.bits[i]);
    }
}

int main(void) {
    srand(time(NULL));
    Suite *test_suites[] = {
        #if defined(TEST_CORE) || defined(TEST_ALL)
        bits_eq_suite(),
        bits_lt_suite(),
        base_addition_suite(),
        base_subtraction_suite(),
        base_multiply_suite(),
        base_divide_suite(),
        remove_trailing_zeros_suite(),
        alignment_scale_suite(),
        base_bank_rounding_suite(),
        uint192_add_suite(),
        uint192_division_suite(),
        bank_rounding_uint192_suite(),
        #endif
        #if defined(TEST_ARITHMETICS) || defined(TEST_ALL)
        s21_mul_suite(),
        s21_negate_suite(),
        #endif
        #if defined(TEST_CONVERSION) || defined(TEST_ALL)
        s21_from_decimal_to_int_suite(),
        s21_from_int_to_decimal_suite(),
        #endif
    };

    SRunner *sr = srunner_create(test_suites[0]);
    srunner_set_fork_status(sr, CK_NOFORK);

    for (size_t i = 1; i < ARRAY_SIZE(test_suites); i++)
        srunner_add_suite(sr, test_suites[i]);

    srunner_run_all(sr, CK_NORMAL);
    int nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
