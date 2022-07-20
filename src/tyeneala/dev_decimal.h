#ifndef _USERS_TYENEALA_DESKTOP_MY_PROJECT_REALISE_C5_DEV_DECIMAL_H_
#define _USERS_TYENEALA_DESKTOP_MY_PROJECT_REALISE_C5_DEV_DECIMAL_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define SIGN_MASK  0x80000000  //  -2147483648

typedef struct {
    unsigned int bits[4];
} s21_decimal;

int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
    int float_to_str(char *str, float val, int *sign, int *exp);

// general
void copy_decimal(s21_decimal *dst, s21_decimal src);
int shift_right(s21_decimal *src);
void add_atr(s21_decimal *dst, int sign, int exp);
void ini_zero(s21_decimal *dst);


// out_decimal.c
void out_decimal(s21_decimal dst);
void ini_arr(char *str);
int zero_shift(const char *str);
int add_degree(char *str, int d);


#endif  // _USERS_TYENEALA_DESKTOP_MY_PROJECT_REALISE_C5_DEV_DECIMAL_H_
