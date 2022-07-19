#ifndef _BINARY_LEVEL_H
#define _BINARY_LEVEL_H

#include "../decimal_type.h"

int get_bit(s21_decimal value, int n);
void set_bit(s21_decimal *value, int n, int bit);
int left_shift(const s21_decimal *value, s21_decimal *result, size_t shift);
void right_shift(const s21_decimal *value, s21_decimal *result, size_t shift);
int bit_addition(s21_decimal value1, s21_decimal value2, s21_decimal *result);
void bit_subtraction(s21_decimal value1, s21_decimal value2, s21_decimal *result);
unsigned last_bit(s21_decimal value);
int bits_eq(s21_decimal value1, s21_decimal value2);
int bits_lt(s21_decimal value1, s21_decimal value2);
int bits_gt(s21_decimal value1, s21_decimal value2);

#endif  // _BINARY_LEVEL_H
