#include <string.h>

#include "bit_operations.h"
#include "core_operations.h"

int init_value(s21_decimal *value, const unsigned bits[3], bool negative, int scale) {
    int error = scale < 0 || scale > 28;
    if (!error) {
        memcpy(value->bits, bits, 3 * sizeof(unsigned));
        int last_bit = (negative << SCALE_SHIFT) | (scale << SCALE_SHIFT);
        value->bits_u32_t[3] = last_bit;
    }
    return error;
}

int get_scale(s21_decimal value) {
    int scale = (value.bits_u32_t[3] >> 31) & 0xFF;
    if (scale < 0 || scale > 28) scale = -1;
    return scale;
}

int set_scale(s21_decimal *value, int scale) {
    int error = scale < 0 || scale > 28;
    if (!error) value->bits_u32_t[3] = (get_sign(*value) << SIGN_SHIFT) | (scale << SCALE_SHIFT);
    return error;
}

bool get_sign(s21_decimal value) {
    return value.bits_u32_t[3] >> SIGN_SHIFT;
}

void set_sign(s21_decimal *value, bool negative) {
    value->bits_u32_t[3] = (negative << SIGN_SHIFT) | (get_scale(*value) << SCALE_SHIFT);
}

/**
 * Addition of two decimals
 * Ignores scale and sign
 * Returns nonzero value if overflow occurs
**/
int32_t base_addition(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
    uint32_t carrial = 0;
    for (size_t i = 0; i < 3; i++) {
        uint64_t r = (uint64_t) value1.bits_u32_t[i] +
                     (uint64_t) value2.bits_u32_t[i] +
                     carrial;
        carrial = r >> 32;
        result->bits_u32_t[i] = r & MASK_32;
    }
    return carrial;
}

/**
 * Subtracts value2 from value1
 * Ignores scale and sign
 * Does not work correctly if base of value1 less than base of value2
**/
void base_subtraction(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
    uint32_t borrow = 0;
    for (size_t i = 0; i < 3; i++) {
        uint64_t r = (uint64_t) value1.bits_u32_t[i] -
                     (uint64_t) value2.bits_u32_t[i] -
                     borrow;
        borrow = value1.bits_u32_t[i] < value2.bits_u32_t[i];
        result->bits_u32_t[i] = r & MASK_32;
    }
}

/**
 * Multiplication of two decimals
 * Uses simple column multiplication algorithm
 * Ignores scale and sign
 * Returns nonzero value if overflow occurs
**/
int32_t base_multiply(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
    int32_t overflow = 0;
    for (size_t i = 0; i < 3; i++) {
        uint32_t m_carrial = 0;
        uint32_t a_carrial = 0;
        for (size_t j = 0; j + i < 3; j++) {
            uint64_t r = (uint64_t) value1.bits_u32_t[i] *
                         (uint64_t) value2.bits_u32_t[j] +
                                               m_carrial +
                                               a_carrial;
            m_carrial = r >> 32;
            r = (r & MASK_32) + result->bits_u32_t[j + i];
            a_carrial = r >> 32;
            result->bits_u32_t[i + j] = r & MASK_32;
        }
        overflow |= m_carrial || a_carrial;
    }
    return overflow;
}

bool is_zero(s21_decimal value) {
    return bits_eq(value, d_zero);
}

bool is_one(s21_decimal value) {
    return bits_eq(value, d_one);
}

/**
 * Divides value1 by value2
 * Ignores sign and scale
 * Writes result of division in *result
 * Writes remainder of division in *remainder
**/
int32_t base_divide(s21_decimal value1, s21_decimal value2,
                    s21_decimal *result, s21_decimal *remainder) {
    // int32_t status = DEC_OC;
    if (is_zero(value2)) return DEC_DIV_BY_ZERO;
    copy_full(result, &d_zero);
    if (is_zero(value1)) return DEC_OK;
    if (is_one(value2)) {
        copy_full(result, &value1);
        return DEC_OK;
    }
    copy_mantiss(remainder, &value1);
    for (int32_t i = last_bit(*remainder) - last_bit(value2); i >= 0; i--) {
        s21_decimal tmp1, tmp2;
        left_shift(&value2, &tmp1, i);
        if ((bits_lt(tmp1, *remainder) || bits_eq(tmp1, *remainder)) && !is_zero(tmp1)) {
            base_subtraction(*remainder, tmp1, remainder);
            left_shift(&d_one, &tmp2, i);
            base_addition(*result, tmp2, result);
        }
    }

    return DEC_OK;
}

