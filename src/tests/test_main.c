#include "test_main.h"

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
        uint192_mul_suite(),
        bank_rounding_uint192_suite(),
        #endif
        #if defined(TEST_ARITHMETICS) || defined(TEST_ALL)
        s21_mul_suite(),
        s21_div_suite(),
        s21_negate_suite(),
        #endif
        #if defined(TEST_CONVERSION) || defined(TEST_ALL)
        s21_from_decimal_to_int_suite(),
        s21_from_int_to_decimal_suite(),
        #endif
        #if defined(TEST_ROUNDING) || defined(TEST_ALL)
        s21_floor_suite(),
        s21_round_suite(),
        s21_truncate_suite(),
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
