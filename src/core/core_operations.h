#ifndef _CORE_OPERATIONS_H
#define _CORE_OPERATIONS_H

#include <stdbool.h>
#include <stdint.h>

#include "decimal_type.h"

#define SCALE_SHIFT 16
#define SIGN_SHIFT 31

#define MASK_32 0xFFFFFFFFl

static const s21_decimal d_zero = {{0, 0, 0, 0}};
static const s21_decimal d_one = {{1, 0, 0, 0}};
static const s21_decimal d_ten = {{10, 0, 0, 0}};
static const s21_decimal d_max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

static const unsigned b_zero[3] = {0};
static const unsigned b_one[3] = {1, 0, 0};
static const unsigned b_nine[3] = {9, 0, 0};
static const unsigned b_ten[3] = {10, 0, 0};
static const unsigned b_64max[3] = {0xFFFFFFFF, 0xFFFFFFFF, 0};

static const s21_decimal ten_power[29] = {
    {{ 0x1, 0, 0}},
    {{ 0xa, 0, 0}},
    {{ 0x64, 0, 0}},
    {{ 0x3e8, 0, 0}},
    {{ 0x2710, 0, 0}},
    {{ 0x186a0, 0, 0}},
    {{ 0xf4240, 0, 0}},
    {{ 0x989680, 0, 0}},
    {{ 0x5f5e100, 0, 0}},
    {{ 0x3b9aca00, 0, 0}},
    {{ 0x540be400, 0x2, 0}},
    {{ 0x4876e800, 0x17, 0}},
    {{ 0xd4a51000, 0xe8, 0}},
    {{ 0x4e72a000, 0x918, 0}},
    {{ 0x107a4000, 0x5af3, 0}},
    {{ 0xa4c68000, 0x38d7e, 0}},
    {{ 0x6fc10000, 0x2386f2, 0}},
    {{ 0x5d8a0000, 0x1634578, 0}},
    {{ 0xa7640000, 0xde0b6b3, 0}},
    {{ 0x89e80000, 0x8ac72304, 0}},
    {{ 0x63100000, 0x6bc75e2d, 0x5}},
    {{ 0xdea00000, 0x35c9adc5, 0x36}},
    {{ 0xb2400000, 0x19e0c9ba, 0x21e}},
    {{ 0xf6800000, 0x02c7e14a, 0x152d}},
    {{ 0xa1000000, 0x1bcecced, 0xd3c2}},
    {{ 0x4a000000, 0x16140148, 0x84595}},
    {{ 0xe4000000, 0xdcc80cd2, 0x52b7d2}},
    {{ 0xe8000000, 0x9fd0803c, 0x33b2e3c}},
    {{ 0x10000000, 0x3e250261, 0x204fce5e}},
};

int init_value(s21_decimal *value, const unsigned bits[3], bool negative, int scale);
int get_scale(s21_decimal value);
int set_scale(s21_decimal *value, int scale);
bool get_sign(s21_decimal value);
void set_sign(s21_decimal *value, bool negative);
int32_t increment(s21_decimal *value);
int multiply_by_ten(s21_decimal value, s21_decimal *result);
int32_t base_addition(s21_decimal value1, s21_decimal value2, s21_decimal *result);
void base_subtraction(s21_decimal value1, s21_decimal value2, s21_decimal *result);
int32_t base_multiply(s21_decimal value1, s21_decimal value2, s21_decimal *result);
void base_div10(s21_decimal value, s21_decimal *result);
int32_t base_divide(s21_decimal value1, s21_decimal value2, s21_decimal *result, s21_decimal *remainder);
void base_fmod(s21_decimal value1, s21_decimal value2, s21_decimal *result);
bool is_zero(s21_decimal value);
bool is_one(s21_decimal value);

#endif  // _CORE_OPERATIONS_H
