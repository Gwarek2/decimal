#include "test_main.h"

int main(void) {
    Suite *test_suites[] = { bit_addition_suite(), bit_subtraction_suite(),
                             bits_eq_suite(), bits_lt_suite(),
                             divide_by_ten_suite(), multiply_by_ten_suite(),
                             base_addition_suite(), base_subtraction_suite(),
                             base_multiply_suite(), base_divide_suite(),
                             base_fmod_suite(), };

    SRunner *sr = srunner_create(test_suites[0]);
    srunner_set_fork_status(sr, CK_NOFORK);

    for (size_t i = 1; i < ARRAY_SIZE(test_suites); i++)
        srunner_add_suite(sr, test_suites[i]);

    srunner_run_all(sr, CK_ENV);
    int nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
