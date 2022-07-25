#include "test_main.h"

START_TEST(float_01) {
    float zero = 0.0, val = zero;
    s21_decimal dec_1, dec_2;
    s21_from_float_to_decimal(val, &dec_1);
    ck_assert_float_eq(val, 0.0);
    copy_full(&dec_2, &dec_1);
    float res;
    s21_from_decimal_to_float(dec_2, &res);
    ck_assert_float_eq(val, res);
} END_TEST

START_TEST(float_02) {
    float zero = 0.0, val = (0 / zero);
    s21_decimal dec_1;
    int res = s21_from_float_to_decimal(val, &dec_1);
    ck_assert_int_eq(res, 1);
} END_TEST

START_TEST(float_03) {
    float zero = 0.0, val = (1.0 / zero);
    s21_decimal dec_1;
    int res = s21_from_float_to_decimal(val, &dec_1);
    ck_assert_int_eq(res, 1);
} END_TEST

START_TEST(float_04) {
    float val = 1e-29;
    s21_decimal dec_1;
    int res = s21_from_float_to_decimal(val, &dec_1);
    ck_assert_int_eq(res, 1);
    ck_assert_int_eq(dec_1.bits[0], 0);
} END_TEST

START_TEST(float_05) {
    float val = 79228162514264337593543950336.0;
    s21_decimal dec_1;
    int res = s21_from_float_to_decimal(val, &dec_1);
    ck_assert_int_eq(res, 1);
} END_TEST

START_TEST(float_06) {
    float val = -79228162514264337593543950336.0;
    s21_decimal dec_1;
    int res = s21_from_float_to_decimal(val, &dec_1);
    ck_assert_int_eq(res, 1);
} END_TEST

START_TEST(float_07) {
    float val = 792281625142643.3;
    s21_decimal dec_1, dec_2;
    s21_from_float_to_decimal(val, &dec_1);
    copy_full(&dec_2, &dec_1);
    float res;
    s21_from_decimal_to_float(dec_2, &res);
    ck_assert_float_eq(val, res);
} END_TEST

START_TEST(float_08) {
    float val = -792281625142643.3;
    s21_decimal dec_1, dec_2;
    s21_from_float_to_decimal(val, &dec_1);
    copy_full(&dec_2, &dec_1);
    float res;
    s21_from_decimal_to_float(dec_2, &res);
    ck_assert_float_eq(val, res);
} END_TEST

START_TEST(float_09) {
    float val = 0.7922816251426433, res;
    s21_decimal dec_1, dec_2;
    s21_from_float_to_decimal(val, &dec_1);
    copy_full(&dec_2, &dec_1);
    s21_from_decimal_to_float(dec_2, &res);
    ck_assert_float_eq(val, res);
} END_TEST

START_TEST(float_10) {
    float val = -0.7922816251426433, res;
    s21_decimal dec_1, dec_2;
    s21_from_float_to_decimal(val, &dec_1);
    copy_full(&dec_2, &dec_1);
    s21_from_decimal_to_float(dec_2, &res);
    ck_assert_float_eq(val, res);
} END_TEST

START_TEST(float_11) {
    float val = 0.0000000000000001, res;
    s21_decimal dec_1, dec_2;
    s21_from_float_to_decimal(val, &dec_1);
    copy_full(&dec_2, &dec_1);
    s21_from_decimal_to_float(dec_2, &res);
    ck_assert_float_eq(val, res);
} END_TEST

START_TEST(float_12) {
    float val = 10000000000000000.0, res;
    s21_decimal dec_1, dec_2;
    s21_from_float_to_decimal(val, &dec_1);
    copy_full(&dec_2, &dec_1);
    s21_from_decimal_to_float(dec_2, &res);
    ck_assert_float_eq(val, res);
} END_TEST

START_TEST(float_13) {
    s21_decimal dec_1 = {{123456, 0, 0, 196608}};
    float res;
    s21_from_decimal_to_float(dec_1, &res);
    ck_assert_float_eq(res, 123.456);
} END_TEST

START_TEST(float_14) {
    s21_decimal dec_1 = {{12345678, 0, 0, -2147155968}};
    float res;
    s21_from_decimal_to_float(dec_1, &res);
    ck_assert_float_eq(res, -123.45678);
} END_TEST

START_TEST(float_15) {
    s21_decimal dec_1 = {{1, 0, 0, -2147418112}};
    float res;
    s21_from_decimal_to_float(dec_1, &res);
    ck_assert_float_eq(res, -0.1);
} END_TEST

Suite *s21_float_decimal_float_suite() {
    Suite *s = suite_create("suite_float_decimal_float_suite");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, float_01);
    tcase_add_test(tc, float_02);
    tcase_add_test(tc, float_03);
    tcase_add_test(tc, float_04);
    tcase_add_test(tc, float_05);
    tcase_add_test(tc, float_06);
    tcase_add_test(tc, float_07);
    tcase_add_test(tc, float_08);
    tcase_add_test(tc, float_09);
    tcase_add_test(tc, float_10);
    tcase_add_test(tc, float_11);
    tcase_add_test(tc, float_12);
    tcase_add_test(tc, float_13);
    tcase_add_test(tc, float_14);
    tcase_add_test(tc, float_15);

    suite_add_tcase(s, tc);
    return s;
}
