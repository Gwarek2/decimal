#include "test_main.h"

// 64438.2323 * 21.1 = 1359646.70153
START_TEST(test_32_bit_1) {
    s21_decimal input1 = {{0x26687e73, 0, 0, init_sign_and_scale(0, 4)}};  
    s21_decimal input2 = {{0xd3, 0, 0, init_sign_and_scale(0, 1)}};
    s21_decimal expected = {{0xa82038c9, 0x1f, 0, init_sign_and_scale(0, 5)}};
    s21_decimal result;
    int status = s21_mul(input1, input2, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, DEC_OK);
}

// -10.24 * 10.24 = 104.8576
START_TEST(test_32_bit_2) {
    s21_decimal input1 = {{0x400, 0, 0, init_sign_and_scale(1, 2)}};
    s21_decimal input2 = {{0x400, 0, 0, init_sign_and_scale(1, 2)}};
    s21_decimal expected = {{0x100000, 0, 0, init_sign_and_scale(0, 4)}};
    s21_decimal result;
    int status = s21_mul(input1, input2, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, DEC_OK);
}

// 1e-28 * 1e-28 = 0
START_TEST(test_small_value_1) {
    s21_decimal input1 = {{0x1, 0, 0, init_sign_and_scale(0, 28)}};
    s21_decimal input2 = {{0x1, 0, 0, init_sign_and_scale(0, 28)}};
    s21_decimal expected = {{0x0, 0, 0, init_sign_and_scale(0, 28)}};
    s21_decimal result;
    int status = s21_mul(input1, input2, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, DEC_OK);
}

// 1e-14 * 1e-14 = 1e-28
START_TEST(test_small_value_2) {
    s21_decimal input1 = {{0x1, 0, 0, init_sign_and_scale(1, 14)}};
    s21_decimal input2 = {{0x1, 0, 0, init_sign_and_scale(1, 14)}};
    s21_decimal expected = {{0x1, 0, 0, init_sign_and_scale(0, 28)}};
    s21_decimal result;
    int status = s21_mul(input1, input2, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, DEC_OK);
}

// 6e-15 * 1e-14 = 1e-28
START_TEST(test_small_value_3) {
    s21_decimal input1 = {{0x6, 0, 0, init_sign_and_scale(1, 15)}};
    s21_decimal input2 = {{0x1, 0, 0, init_sign_and_scale(1, 14)}};
    s21_decimal expected = {{0x1, 0, 0, init_sign_and_scale(0, 28)}};
    s21_decimal result;
    int status = s21_mul(input1, input2, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, DEC_OK);
}

// 0 * -42949672.95 = 0
START_TEST(test_zero) {
    s21_decimal input1 = {{0}};
    s21_decimal input2 = {{0xffffffff, 0, 0, init_sign_and_scale(1, 2)}};
    s21_decimal expected = {{0, 0, 0, init_sign_and_scale(1, 2)}};
    s21_decimal result;
    int status = s21_mul(input1, input2, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, DEC_OK);
}

// 18446744073709.551615 * 1 = 18446744073709.551615
START_TEST(test_one) {
    s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0, init_sign_and_scale(1, 6)}};
    s21_decimal input2 = {{1}};
    s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0, init_sign_and_scale(1, 6)}};
    s21_decimal result;
    int status = s21_mul(input1, input2, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, DEC_OK);
}

// 644388461.24564323 * 100 = 64438846124.56432300
START_TEST(test_64_bit_1) {
    s21_decimal input1 = {{0x4fd9f63, 0xe4eeca, 0, init_sign_and_scale(0, 8)}};
    s21_decimal input2 = {{0x64, 0, 0, init_sign_and_scale(0, 0)}};
    s21_decimal expected = {{0xf31242ac, 0x596d46e9, 0, init_sign_and_scale(0, 8)}};
    s21_decimal result;
    int status = s21_mul(input1, input2, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, DEC_OK);
}

// 75628.4783749104619446 * 7562849.389272378 = 571966791489.29083373022722365
START_TEST(test_64_bit_2) {
    s21_decimal input1 = {{0xee7f4fb6, 0xff8f4bd9, 0x28, init_sign_and_scale(0, 16)}};
    s21_decimal input2 = {{0x17565d3a, 0x1ade5f, 0, init_sign_and_scale(0, 9)}};
    s21_decimal expected = {{0xebedb93d, 0x9c7bbf94, 0xb8cffbed, init_sign_and_scale(0, 17)}};
    s21_decimal result;
    int status = s21_mul(input1, input2, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, DEC_OK);
}

// 75628.478374910555555 * 7562849.389555555 = 571966791510.70778731235573959
START_TEST(test_64_bit_3) {
    s21_decimal input1 = {{0x97daf5a3, 0x198e5462, 0x4, init_sign_and_scale(0, 15)}};
    s21_decimal input2 = {{0x175aaf63, 0x1ade5f, 0, init_sign_and_scale(0, 9)}};
    s21_decimal expected = {{0xaf4f00c7, 0xba349429, 0xb8cffbed, init_sign_and_scale(0, 17)}};
    s21_decimal result;
    int status = s21_mul(input1, input2, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, DEC_OK);
}

// -7.9228162514264337593543950335 * 7.9228162514264337593543950335 = -62.771017353866807638357894230
START_TEST(test_96_bit_1) {
    s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, init_sign_and_scale(1, 28)}};
    s21_decimal input2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, init_sign_and_scale(0, 28)}};
    s21_decimal expected = {{0x96EE456, 0x359A3B3E, 0xCAD2F7F5, init_sign_and_scale(1, 27)}};
    s21_decimal result;
    int status = s21_mul(input1, input2, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, DEC_OK);
}

// 27824724378.43634677634 * 46513.1237326723 = 1294214847841713.1524935845060
START_TEST(test_96_bit_2) {
    s21_decimal input1 = {{0x4903e782, 0xd68fe40c, 0x96, init_sign_and_scale(1, 11)}};
    s21_decimal input2 = {{0xce2cbf83, 0x1a708, 0, init_sign_and_scale(0, 10)}};
    s21_decimal expected = {{0xffa304c4, 0xd8b3a201, 0x29d17e8a, init_sign_and_scale(1, 13)}};
    s21_decimal result;
    int status = s21_mul(input1, input2, &result);

    ASSERT_DECIMAL_EQ
    ck_assert_int_eq(status, DEC_OK);
}

// 79228162514264337593543950335 * 1.1 = INF
START_TEST(test_96_bit_3) {
    s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    s21_decimal input2 = {{11, 0, 0, init_sign_and_scale(0, 1)}};
    s21_decimal result;
    int status = s21_mul(input1, input2, &result);

    ck_assert_int_eq(status, DEC_HUGE);
}

// -79228162514264337593543950335 * 79228162514264337593543950335 = -INF
START_TEST(test_96_bit_4) {
    s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, init_sign_and_scale(1, 0)}};
    s21_decimal input2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    s21_decimal result;
    int status = s21_mul(input1, input2, &result);

    ck_assert_int_eq(status, DEC_SMALL);
}

Suite *s21_mul_suite() {
    Suite *s  = suite_create("suite_s21_mul");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_32_bit_1);
    tcase_add_test(tc, test_32_bit_2);
    tcase_add_test(tc, test_small_value_1);
    tcase_add_test(tc, test_small_value_2);
    tcase_add_test(tc, test_small_value_3);
    tcase_add_test(tc, test_zero);
    tcase_add_test(tc, test_one);
    tcase_add_test(tc, test_64_bit_1);
    tcase_add_test(tc, test_64_bit_2);
    tcase_add_test(tc, test_64_bit_3);
    tcase_add_test(tc, test_96_bit_1);
    tcase_add_test(tc, test_96_bit_2);
    tcase_add_test(tc, test_96_bit_3);
    tcase_add_test(tc, test_96_bit_4);

    suite_add_tcase(s, tc);

    return s;
}
