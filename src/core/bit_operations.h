#ifndef _BIT_OPERATIONS_H
#define _BIT_OPERATIONS_H

#include "decimal_type.h"

int get_bit(s21_decimal value, int n);
void set_bit(s21_decimal *value, int n, int bit);
void copy_full(s21_decimal *dest, const s21_decimal *src);
void copy_mantiss(s21_decimal *dest, const s21_decimal *src);
int left_shift(const s21_decimal *value, s21_decimal *result, size_t shift);
void right_shift(const s21_decimal *value, s21_decimal *result, size_t shift);
int bit_addition(s21_decimal value1, s21_decimal value2, s21_decimal *result);
void bit_subtraction(s21_decimal value1, s21_decimal value2, s21_decimal *result);
uint32_t last_bit(s21_decimal value);
int bits_eq(s21_decimal value1, s21_decimal value2);
int bits_lt(s21_decimal value1, s21_decimal value2);
int bits_gt(s21_decimal value1, s21_decimal value2);
void print_bin(s21_decimal value);
void print_hex(s21_decimal value);

#endif  // _BIT_OPERATIONS_H
