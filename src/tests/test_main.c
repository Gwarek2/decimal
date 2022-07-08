#include "test_main.h"

int main(void) {
    Suite *test_suites[] = { bits_eq_suite(), bits_lt_suite(),
                             base_addition_suite(), base_subtraction_suite(),
                             base_multiply_suite(), base_divide_suite() };

    SRunner *sr = srunner_create(test_suites[0]);
    srunner_set_fork_status(sr, CK_NOFORK);

    for (size_t i = 1; i < ARRAY_SIZE(test_suites); i++)
        srunner_add_suite(sr, test_suites[i]);

    srunner_run_all(sr, CK_ENV);
    int nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
