#include "uint96.h"
#include <string.h>

/**************************************************************
 * Initializes decimal value with given mantiss, sign and scale
 **************************************************************/
int init_value(s21_decimal *value, const uint32_t mantiss[3], bool negative,
               uint32_t scale) {
    int error = scale > 28;
    if (!error) {
        memcpy(value->bits, mantiss, 3 * sizeof(uint32_t));
        uint32_t last_chunk = init_sign_and_scale(negative, scale);
        value->bits[3] = last_chunk;
    }
    return error;
}

void init_default(s21_decimal *value) { memset(value, 0, sizeof(s21_decimal)); }

/***************************************
 * Converts sign and scale to uint field
 * Returns converted field
 ***************************************/
uint32_t init_sign_and_scale(int sign, int scale) {
    return (sign << SIGN_SHIFT) | (scale << SCALE_SHIFT);
}

/**************************************
 * Copies all 128 bits from src to dest
 **************************************/
void copy_full(s21_decimal *dest, const s21_decimal *src) {
    memcpy(dest, src, sizeof(s21_decimal));
}

/***********************************************************
 * Copies first 96 bits (represent mantiss) from src to dest
 ***********************************************************/
void copy_mantiss(s21_decimal *dest, const s21_decimal *src) {
    memcpy(dest->bits, src->bits, sizeof(uint32_t) * 3);
}

int get_atr(s21_decimal src, int *exp) {
    *exp = get_scale(src);
    return get_sign(src);
}

unsigned get_scale(s21_decimal value) {
    unsigned scale = (value.bits[3] >> SCALE_SHIFT) & 0xff;
    return scale;
}

int set_scale(s21_decimal *value, int scale) {
    unsigned error = scale < 0 || scale > 28;
    if (!error)
        value->bits[3] =
            (get_sign(*value) << SIGN_SHIFT) | (scale << SCALE_SHIFT);
    return error;
}

bool get_sign(s21_decimal value) { return value.bits[3] >> SIGN_SHIFT; }

void set_sign(s21_decimal *value, bool negative) {
    value->bits[3] =
        (negative << SIGN_SHIFT) | (get_scale(*value) << SCALE_SHIFT);
}

/************************************
 * Gets nth bit
 * Works correctly with 0 >= n <= 127
 ************************************/
int get_bit(s21_decimal value, int n) {
    int index = n / 32;
    int shift = n % 32;
    return (value.bits[index] >> shift) & 1;
}

/************************************
 * Sets bit to n position
 * Works correctly with 0 >= n <= 127
 ************************************/
void set_bit(s21_decimal *value, int n, int bit) {
    int index = n / 32;
    int shift = n % 32;
    value->bits[index] = (value->bits[index] & ~(1U << shift)) | (bit << shift);
}

/****************************************
 * Shifts all bits to left by given value
 * Returns 1 if overflow occurs
 ****************************************/
int left_shift(const s21_decimal *value, s21_decimal *result, size_t shift) {
    int overflow = 0;
    copy_full(result, value);
    for (size_t i = 0; i < shift; i++) {
        int bit1 = get_bit(*result, 31);
        int bit2 = get_bit(*result, 63);
        overflow = get_bit(*result, 95);
        result->bits[0] <<= 1;
        result->bits[1] <<= 1;
        result->bits[2] <<= 1;
        set_bit(result, 32, bit1);
        set_bit(result, 64, bit2);
    }
    return overflow ? DEC_HUGE : DEC_OK;
}

/**************************************************************************************
 * The function returns the lowest bit and shifts the values in the buffers to
 *the right
 **************************************************************************************/
int right_shift(s21_decimal *src) {
    int bit = 0;
    for (int i = 2; i >= 0; i--) {
        int tmp_bit = src->bits[i] & 1;
        src->bits[i] >>= 1;
        if ((i != 2) && (bit != 0))
            src->bits[i] = src->bits[i] | (1u << 31);
        bit = tmp_bit;
    }
    return bit;
}

/****************************************************
 * Gets position of first bit from the end equal to 1
 * Returns 0 if value is equal to 0
 *****************************************************/
uint32_t last_bit(s21_decimal value) {
    int i = 95;
    while (!get_bit(value, i) && i) {
        i--;
    }
    return i;
}

int cmp(const s21_decimal value1, const s21_decimal value2) {
    int result = EQ;
    for (int i = 2; i >= 0 && result == EQ; i--) {
        if (value1.bits[i] < value2.bits[i]) {
            result = LT;
        } else if (value1.bits[i] > value2.bits[i]) {
            result = GT;
        }
    }
    return result;
}

int eq(const s21_decimal value1, const s21_decimal value2) {
    return cmp(value1, value2) == 0;
}

int lt(const s21_decimal value1, const s21_decimal value2) {
    return cmp(value1, value2) == -1;
}

int gt(const s21_decimal value1, const s21_decimal value2) {
    return cmp(value1, value2) == 1;
}

bool is_zero(const s21_decimal value) { return eq(value, DEC_ZERO); }

/******************************************
 * Addition of two decimals
 * Ignores scale and sign
 * Returns nonzero value if overflow occurs
 *****************************************/
int base_addition(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
    uint32_t carrial = 0;
    for (size_t i = 0; i < 3; i++) {
        uint64_t r =
            (uint64_t)value1.bits[i] + (uint64_t)value2.bits[i] + carrial;
        carrial = r >> 32;
        result->bits[i] = r;
    }
    return carrial;
}

/**
 * Subtracts value2 from value1
 * Ignores scale and sign
 * Does not work correctly if base of value1 less than base of value2
 **/
void base_subtraction(s21_decimal value1, s21_decimal value2,
                      s21_decimal *result) {
    uint32_t borrow = 0;
    for (size_t i = 0; i < 3; i++) {
        result->bits[i] = value1.bits[i] - value2.bits[i] - borrow;
        borrow = (uint64_t)value1.bits[i] < (uint64_t)value2.bits[i] + borrow;
    }
}

/*********************************
 * Helper for base_multiplication
 * Adds carrials to overflow value
 **********************************/
void add_carrials(s21_decimal *overflow, uint32_t mul_carrial,
                  uint32_t add_carrial, int index) {
    s21_decimal dec_mul_carrial = {{0}};
    s21_decimal dec_add_carrial = {{0}};
    dec_mul_carrial.bits[index] = mul_carrial;
    dec_add_carrial.bits[index] = add_carrial;
    base_addition(*overflow, dec_mul_carrial, overflow);
    base_addition(*overflow, dec_add_carrial, overflow);
}

/**********************************************************************************
 * Multiplication of two decimals.
 * Uses simple column multiplication algorithm.
 * Ignores scale and sign.
 * Returns nonzero value if overflow occurs.
 **********************************************************************************
 * s21_decimal *result:
 *     result of multiplication
 * s21_decimal *overflow:
 *     overflow of *result;
 *     *result and *overflow mantisses could be imagined as a single 192-bit
 * integer, where *overflow contains higher bit fields and *result - lower bit
 * fields
 **********************************************************************************/
int base_multiply(s21_decimal value1, s21_decimal value2, s21_decimal *result,
                  s21_decimal *overflow) {
    int is_overflow = 0;
    init_default(overflow);
    init_default(result);
    for (size_t i = 0; i < 3; i++) {
        uint32_t mul_carrial = 0;
        uint32_t add_carrial = 0;
        size_t overflow_index = 0;
        for (size_t j = 0; j < 3; j++) {
            uint64_t r = (uint64_t)value1.bits[i] * (uint64_t)value2.bits[j] +
                         mul_carrial + add_carrial;
            mul_carrial = r >> 32;
            if (j + i < 3) {
                r = (r & MASK_32) + result->bits[j + i];
                add_carrial = r >> 32;
                result->bits[i + j] = r & MASK_32;
            } else {
                r = (r & MASK_32) + overflow->bits[overflow_index];
                is_overflow |= r != 0;
                add_carrial = r >> 32;
                overflow->bits[overflow_index] = r & MASK_32;
                overflow_index++;
            }
        }
        add_carrials(overflow, mul_carrial, add_carrial, i);
    }
    return is_overflow;
}

/********************************************
 * Divides value1 by value2
 * Ignores sign and scale
 * Writes result of division in *result
 * Writes remainder of division in *remainder
 *******************************************/
void base_divide(s21_decimal value1, s21_decimal value2, s21_decimal *result,
                 s21_decimal *remainder) {
    init_default(result);
    init_default(remainder);
    copy_mantiss(remainder, &value1);
    for (int i = last_bit(*remainder) - last_bit(value2); i >= 0; i--) {
        s21_decimal tmp1, tmp2;
        left_shift(&value2, &tmp1, i);
        if ((lt(tmp1, *remainder) || eq(tmp1, *remainder)) &&
            !is_zero(tmp1)) {
            base_subtraction(*remainder, tmp1, remainder);
            left_shift(&DEC_ONE, &tmp2, i);
            base_addition(*result, tmp2, result);
        }
    }
}

/*********************************************************
 * Removes trailing zeroes from fractional part of decimal
 ****************************************************** **/
void remove_trailing_zeros(s21_decimal value, s21_decimal *result) {
    unsigned scale = get_scale(value);
    while (true) {
        s21_decimal res_tmp, rem_tmp;
        base_divide(value, DEC_TEN, &res_tmp, &rem_tmp);
        if (!is_zero(rem_tmp) || !scale)
            break;
        copy_mantiss(&value, &res_tmp);
        set_scale(&value, --scale);
    }
    copy_full(result, &value);
}

/************************************************************************
 * Equalizes the exponent before addition, subtraction and mod operation.
 * Returns 1 if overflow occured, otherwise returns 0
 ***********************************************************************/
int equalize_scales(s21_decimal *value_1, s21_decimal *value_2,
                    s21_decimal *overflow) {
    int output = DEC_OK;
    int scale_value_1 = get_scale(*value_1);
    int scale_value_2 = get_scale(*value_2);
    int difference = scale_value_1 - scale_value_2;
    s21_decimal overflow_in_function = {0};
    s21_decimal result = {0};
    if (difference > 0) {
        base_multiply(*value_2, ten_power[difference], &result,
                      &overflow_in_function);
        *value_2 = result;
        value_2->bits[3] = value_1->bits[3];
    } else if (difference < 0) {
        difference = -difference;
        base_multiply(*value_1, ten_power[difference], &result,
                      &overflow_in_function);
        *value_1 = result;
        value_1->bits[3] = value_2->bits[3];
    }
    *overflow = overflow_in_function;

    if (!is_zero(overflow_in_function)) {
        *overflow = overflow_in_function;
        output = DEC_HUGE;
    }

    return output;
}
