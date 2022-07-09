#include <string.h>

#include "bit_operations.h"
#include "core_operations.h"

int init_value(s21_decimal *value, const unsigned bits[3], bool negative, unsigned scale) {
    int error = scale > 28;
    if (!error) {
        memcpy(value->bits, bits, 3 * sizeof(unsigned));
        unsigned last_chunk = (negative << SIGN_SHIFT) | (scale << SCALE_SHIFT);
        value->bits_u32_t[3] = last_chunk;
    }
    return error;
}

void init_default(s21_decimal *value) {
    unsigned zero[3] = {0, 0, 0};
    init_value(value, zero, 0, 0);
}

unsigned get_scale(s21_decimal value) {
    unsigned scale = (value.bits_u32_t[3] >> SCALE_SHIFT) & 0xffU;
    return scale;
}

int set_scale(s21_decimal *value, int scale) {
    unsigned error = scale < 0 || scale > 28;
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
int base_addition(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
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
int base_multiply(s21_decimal value1, s21_decimal value2,
                      s21_decimal *result, s21_decimal *overflow) {
    int is_overflow = 0;
    init_default(overflow);
    for (size_t i = 0; i < 3; i++) {
        uint32_t m_carrial = 0;
        uint32_t a_carrial = 0;
        for (size_t j = 0; j < 3; j++) {
            uint64_t r = (uint64_t) value1.bits[i] *
                         (uint64_t) value2.bits[j] +
                                         m_carrial +
                                         a_carrial;
            m_carrial = r >> 32;
            if (j + i < 3) {
                r = (r & MASK_32) + result->bits[j + i];
                a_carrial = r >> 32;
                result->bits_u32_t[i + j] = r & MASK_32;
            } else {
                r = (r & MASK_32) + overflow->bits[j];
                a_carrial = r >> 32;
                overflow->bits_u32_t[j] = r & MASK_32;
            }
        }
        is_overflow |= m_carrial || a_carrial;

        s21_decimal a_value, m_value;
        unsigned a_buff[3] = {a_carrial, 0, 0};
        unsigned m_buff[3] = {m_carrial, 0, 0};
        init_value(&a_value, a_buff, 0, 0);
        init_value(&m_value, m_buff, 0, 0);
        base_addition(a_value, *overflow, overflow);
        base_addition(m_value, *overflow, overflow);
    }
    return is_overflow;
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
int base_divide(s21_decimal value1, s21_decimal value2,
                    s21_decimal *result, s21_decimal *remainder) {
    if (is_zero(value2)) return DEC_DIV_BY_ZERO;
    init_default(result);
    init_default(remainder);
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

/**
 * Removes trailing zeroes from fractional part of decimal
**/
void remove_trailing_zeros(s21_decimal value, s21_decimal *result) {
    unsigned scale = get_scale(value);
    while (true) {
        s21_decimal res_tmp, rem_tmp;
        base_divide(value, d_ten, &res_tmp, &rem_tmp);
        if (!is_zero(rem_tmp) || !scale) break;
        copy_mantiss(&value, &res_tmp);
        set_scale(&value, --scale);
    }
    copy_full(result, &value);
}

