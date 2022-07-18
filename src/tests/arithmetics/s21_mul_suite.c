#include "test_main.h"

START_TEST(test_32_bit_1) {
    s21_decimal input1 = {{0x26687e73, 0, 0, init_sign_and_scale(0, 4)}};  // 64438.2323
    s21_decimal input2 = {{0xd3, 0, 0, init_sign_and_scale(0, 1)}};  // 21.1
    s21_decimal expected = {{0xa82038c9, 0x1f, 0, init_sign_and_scale(0, 5)}};  // 1359646.70153
    s21_decimal result = {{0}};
    int status = s21_mul(input1, input2, &result);
    assert_decimal_eq(result, expected);
    ck_assert_int_eq(status, DEC_OK);
}

START_TEST(test_32_bit_2) {
    s21_decimal input1 = {{0x400, 0, 0, init_sign_and_scale(1, 2)}};  // -10.24
    s21_decimal input2 = {{0x400, 0, 0, init_sign_and_scale(1, 2)}};  // -10.24
    s21_decimal expected = {{0x100000, 0, 0, init_sign_and_scale(0, 4)}};  // 104.8576
    s21_decimal result = {{0}};
    int status = s21_mul(input1, input2, &result);
    assert_decimal_eq(result, expected);
    ck_assert_int_eq(status, DEC_OK);
}

START_TEST(test_small_value_1) {
    s21_decimal input1 = {{0x1, 0, 0, init_sign_and_scale(0, 28)}};  // 1e-28
    s21_decimal input2 = {{0x1, 0, 0, init_sign_and_scale(0, 28)}};  // 1e-28
    s21_decimal expected = {{0x0, 0, 0, init_sign_and_scale(0, 28)}};  // 0
    s21_decimal result = {{0}};
    int status = s21_mul(input1, input2, &result);
    assert_decimal_eq(result, expected);
    ck_assert_int_eq(status, DEC_OK);
}

START_TEST(test_small_value_2) {
    s21_decimal input1 = {{0x1, 0, 0, init_sign_and_scale(1, 14)}};  // 1e-14
    s21_decimal input2 = {{0x1, 0, 0, init_sign_and_scale(1, 14)}};  // 1e-14
    s21_decimal expected = {{0x1, 0, 0, init_sign_and_scale(0, 28)}};  // 1e-28
    s21_decimal result = {{0}};
    int status = s21_mul(input1, input2, &result);
    assert_decimal_eq(result, expected);
    ck_assert_int_eq(status, DEC_OK);
}

START_TEST(test_small_value_3) {
    s21_decimal input1 = {{0x6, 0, 0, init_sign_and_scale(1, 15)}};  // 6e-15
    s21_decimal input2 = {{0x1, 0, 0, init_sign_and_scale(1, 14)}};  // 1e-14
    s21_decimal expected = {{0x1, 0, 0, init_sign_and_scale(0, 28)}};  // 1e-28
    s21_decimal result = {{0}};
    int status = s21_mul(input1, input2, &result);
    assert_decimal_eq(result, expected);
    ck_assert_int_eq(status, DEC_OK);
}

START_TEST(test_zero) {
    s21_decimal input1 = {{0}};  // 0
    s21_decimal input2 = {{0xffffffff, 0, 0, init_sign_and_scale(1, 2)}};  // -42949672.95
    s21_decimal expected = {{0, 0, 0, init_sign_and_scale(1, 2)}};  // 0
    s21_decimal result = {{0}};
    int status = s21_mul(input1, input2, &result);
    assert_decimal_eq(result, expected);
    ck_assert_int_eq(status, DEC_OK);
}

START_TEST(test_one) {
    s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0, init_sign_and_scale(1, 6)}};  // 18446744073709.551615
    s21_decimal input2 = {{1}};  // 1
    s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0, init_sign_and_scale(1, 6)}};  // 18446744073709.551615
    s21_decimal result = {{0}};
    int status = s21_mul(input1, input2, &result);
    assert_decimal_eq(result, expected);
    ck_assert_int_eq(status, DEC_OK);
}

START_TEST(test_64_bit_1) {
    s21_decimal input1 = {{0x4fd9f63, 0xe4eeca, 0, init_sign_and_scale(0, 8)}};  // 644388461.24564323
    s21_decimal input2 = {{0x64, 0, 0, init_sign_and_scale(0, 0)}};  // 100
    s21_decimal expected = {{0xf31242ac, 0x596d46e9, 0, init_sign_and_scale(0, 8)}};  // 64438846124.56432300
    s21_decimal result = {{0}};
    int status = s21_mul(input1, input2, &result);
    assert_decimal_eq(result, expected);
    ck_assert_int_eq(status, DEC_OK);
}

START_TEST(test_64_bit_2) {
    s21_decimal input1 = {{0xee7f4fb6, 0xff8f4bd9, 0x28, init_sign_and_scale(0, 16)}};  // 75628.4783749104619446
    s21_decimal input2 = {{0x17565d3a, 0x1ade5f, 0, init_sign_and_scale(0, 9)}};  // 7562849.389272378
    s21_decimal expected = {{0xebedb93d, 0x9c7bbf94, 0xb8cffbed, init_sign_and_scale(0, 17)}};  // 571966791489.29083373022722365
    s21_decimal result = {{0}};
    int status = s21_mul(input1, input2, &result);
    assert_decimal_eq(result, expected);
    ck_assert_int_eq(status, DEC_OK);
}

START_TEST(test_64_bit_3) {
    s21_decimal input1 = {{0x97daf5a3, 0x198e5462, 0x4, init_sign_and_scale(0, 15)}};  // 75628.478374910555555
    s21_decimal input2 = {{0x175aaf63, 0x1ade5f, 0, init_sign_and_scale(0, 9)}};  // 7562849.389555555
    s21_decimal expected = {{0xaf4f00c7, 0xba349429, 0xb8cffbed, init_sign_and_scale(0, 17)}};  // 571966791510.70778731235573959
    s21_decimal result = {{0}};
    int status = s21_mul(input1, input2, &result);
    assert_decimal_eq(result, expected);
    ck_assert_int_eq(status, DEC_OK);
}

START_TEST(test_96_bit_1) {
    s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, init_sign_and_scale(1, 28)}};  // 644388461.24564323
    s21_decimal input2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, init_sign_and_scale(0, 28)}};  // 100
    s21_decimal expected = {{0x96EE456, 0x359A3B3E, 0xCAD2F7F5, init_sign_and_scale(1, 27)}};  // 64438846124.56432300
    s21_decimal result = {{0}};
    int status = s21_mul(input1, input2, &result);
    assert_decimal_eq(result, expected);
    ck_assert_int_eq(status, DEC_OK);
}

START_TEST(test_96_bit_2) {
    s21_decimal input1 = {{0x4903e782, 0xd68fe40c, 0x96, init_sign_and_scale(1, 11)}};  // 27824724378.43634677634
    s21_decimal input2 = {{0xce2cbf83, 0x1a708, 0, init_sign_and_scale(0, 10)}};  // 46513.1237326723
    s21_decimal expected = {{0xffa304c4, 0xd8b3a201, 0x29d17e8a, init_sign_and_scale(1, 13)}};  // 1294214847841713.1524935845060
    s21_decimal result = {{0}};
    int status = s21_mul(input1, input2, &result);
    assert_decimal_eq(result, expected);
    ck_assert_int_eq(status, DEC_OK);
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

    suite_add_tcase(s, tc);

    return s;
}
