#include "../decimal_type.h"
#include "binary_level.h"
#include "decimal_level.h"
#include "output.h"
#include <stdio.h>
#include "common.h"
#include <string.h>

unsigned int max32bit = 4294967295;
unsigned int maxScale = 1835008;

unsigned isSetBit(int number, int index) {
    return (number&(1<<index))!=0;
}

/**
 * Gets nth bit
 * Works correctly with 0 >= n <= 127
**/
int get_bit(s21_decimal value, int n) {
    int index = n / 32;
    int shift = n % 32;
    return (value.bits_u32_t[index] >> shift) & 1U;
}

/**
 * Sets bit to n position
 * Works correctly with 0 >= n <= 127
**/
void set_bit(s21_decimal *value, int n, int bit) {
    int index = n / 32;
    int shift = n % 32;
    value->bits_u32_t[index] = (value->bits_u32_t[index] & ~(1U << shift)) | (bit << shift);
}

/**
 * Shifts all bits to left by given value
 * Returns 1 if overflow occurs
**/
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

/**
 * Shifts all bits to right by given value
**/
void right_shift(const s21_decimal *value, s21_decimal *result, size_t shift) {
    copy_full(result, value);
    for (size_t i = 0; i < shift; i++) {
        int bit1 = get_bit(*result, 64);
        int bit2 = get_bit(*result, 32);
        result->bits_u32_t[0] >>= 1;
        result->bits_u32_t[1] >>= 1;
        result->bits_u32_t[2] >>= 1;
        set_bit(result, 63, bit1);
        set_bit(result, 31, bit2);
    }
}

/**
 * Gets position of first bit from the end equal to 1
 * If value iz 
**/
unsigned last_bit(s21_decimal value) {
    unsigned bit = 0;
    int i = 95;
    while (!bit && i) {
        bit = get_bit(value, i);
        if (!bit) i--;
    }
    return i;
}

/**
 * Checks if bits in first 3 chunks are equal
 * Does not care about scale and sign
**/
int bits_eq(s21_decimal value1, s21_decimal value2) {
    return value1.bits_u32_t[0] == value2.bits_u32_t[0] &&
           value1.bits_u32_t[1] == value2.bits_u32_t[1] &&
           value1.bits_u32_t[2] == value2.bits_u32_t[2];
}

/**
 * Checks if value1 less than value2
 * Does not care about scale and sign
**/
int bits_lt(s21_decimal value1, s21_decimal value2) {
    return value1.bits_u32_t[2] < value2.bits_u32_t[2] ||
           (value1.bits_u32_t[2] == value2.bits_u32_t[2] && value1.bits_u32_t[1] < value2.bits_u32_t[1]) ||
           (value1.bits_u32_t[2] == value2.bits_u32_t[2] && value1.bits_u32_t[1] == value2.bits_u32_t[1] &&
            value1.bits_u32_t[0] < value2.bits_u32_t[0]);
}

/**
 * Checks if value1 greater than value2
 * Does not care about scale and sign
**/
int bits_gt(s21_decimal value1, s21_decimal value2) {
    return value1.bits_u32_t[2] > value2.bits_u32_t[2] ||
           (value1.bits_u32_t[2] == value2.bits_u32_t[2] && value1.bits_u32_t[1] > value2.bits_u32_t[1]) ||
           (value1.bits_u32_t[2] == value2.bits_u32_t[2] && value1.bits_u32_t[1] == value2.bits_u32_t[1] &&
            value1.bits_u32_t[0] > value2.bits_u32_t[0]);
}

unsigned get_scale(s21_decimal value) {
    unsigned scale = (value.bits_u32_t[3] >> SCALE_SHIFT) & 0xffU;
    return scale;
}

int set_scale(s21_decimal *value, int scale) {
    unsigned error = scale < 0 || scale > 28;
    if (!error)
        value->bits_u32_t[3] =
            (get_sign(*value) << SIGN_SHIFT) | (scale << SCALE_SHIFT);
    return error;
}

bool get_sign(s21_decimal value) { return value.bits_u32_t[3] >> SIGN_SHIFT; }

void set_sign(s21_decimal *value, bool negative) {
    value->bits_u32_t[3] =
        (negative << SIGN_SHIFT) | (get_scale(*value) << SCALE_SHIFT);
}

/**
 * Addition of two decimals
 * Ignores scale and sign
 * Returns nonzero value if overflow occurs
 **/
int base_addition(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
    uint32_t carrial = 0;
    for (size_t i = 0; i < 3; i++) {
        uint64_t r = (uint64_t)value1.bits_u32_t[i] +
                     (uint64_t)value2.bits_u32_t[i] + carrial;
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
void base_subtraction(s21_decimal value1, s21_decimal value2,
                      s21_decimal *result) {
    uint32_t borrow = 0;
    for (size_t i = 0; i < 3; i++) {
        uint64_t r = (uint64_t)value1.bits_u32_t[i] -
                     (uint64_t)value2.bits_u32_t[i] - borrow;
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
int base_multiply(s21_decimal value1, s21_decimal value2, s21_decimal *result, s21_decimal *overflow) {
    int is_overflow = 0;
    init_default(overflow);
    for (size_t i = 0; i < 3; i++) {
        uint32_t m_carrial = 0;
        uint32_t a_carrial = 0;

        for (size_t j = 0; j < 3; j++) {
            uint64_t r = (uint64_t)value1.bits[i] * (uint64_t)value2.bits[j] + m_carrial + a_carrial;

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

bool is_zero(s21_decimal value) { return bits_eq(value, DEC_ZERO); }

bool is_one(s21_decimal value) { return bits_eq(value, DEC_ONE); }

/**
 * Divides value1 by value2
 * Ignores sign and scale
 * Writes result of division in *result
 * Writes remainder of division in *remainder
 **/

int32_t base_divide(s21_decimal value1, s21_decimal value2, s21_decimal *result,
                    s21_decimal *remainder) {
    // int32_t status = DEC_OC;

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
        if ((bits_lt(tmp1, *remainder) || bits_eq(tmp1, *remainder)) &&
            !is_zero(tmp1)) {
            base_subtraction(*remainder, tmp1, remainder);
            left_shift(&DEC_ONE, &tmp2, i);
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
        base_divide(value, DEC_TEN, &res_tmp, &rem_tmp);
        if (!is_zero(rem_tmp) || !scale) break;
        copy_mantiss(&value, &res_tmp);
        set_scale(&value, --scale);
    }
    copy_full(result, &value);
}

/**
 * Initializes decimal value with given mantiss, sign and scale
**/
int init_value(s21_decimal *value, const unsigned mantiss[3], bool negative, unsigned scale) {
    int error = scale > 28;
    if (!error) {
        memcpy(value->bits, mantiss, 3 * sizeof(unsigned));
        unsigned last_chunk = (negative << SIGN_SHIFT) | (scale << SCALE_SHIFT);
        value->bits_u32_t[3] = last_chunk;
    }
    return error;
}

/**
 * Initializes decimal with zero value
**/
void init_default(s21_decimal *value) {
    unsigned zero[3] = {0, 0, 0};
    init_value(value, zero, 0, 0);
}

/**
 * Copies all 128 bits from src to dest
**/
void copy_full(s21_decimal *dest, const s21_decimal *src) {
    memcpy(dest, src, sizeof(s21_decimal));
}

/**
 * Copies first 96 bits (represent mantiss) from src to dest
**/
void copy_mantiss(s21_decimal *dest, const s21_decimal *src) {
    memcpy(dest->bits, src->bits, sizeof(unsigned) * 3);
}

/**
 * Outputs decimal in binary format
**/
void print_bin(s21_decimal value) {
    char bin[129];
    for (size_t i = 0; i < 127; i++) {
        bin[i] = get_bit(value, 127 - i - 1) + '0';
    }
    bin[128] = '\0';
    printf("%s\n", bin);
}

/**
 * Outputs decimal in hex format
**/
void print_hex(s21_decimal value) {
    if (value.bits[2]) {
        printf("%#x", value.bits[2]);
    }

    if (!value.bits[2] && value.bits[1]) {
        printf("%#x", value.bits[1]);
    } else if (value.bits[1]) {
        printf("%08x", value.bits[1]);
    }

    if (!value.bits[2] && !value.bits[1] && value.bits[0]) {
        printf("%#x", value.bits[0]);
    } else if (value.bits[0]) {
        printf("%08x", value.bits[0]);
    } else {
        printf("0x0");
    }

    printf(" %#x\n", value.bits[3]);
}


int alignment_scale(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *overflow) {
    int output = DEC_OK;
    int scale_value_1 = get_scale(*value_1);
    int scale_value_2 = get_scale(*value_2);
    int difference = scale_value_1 - scale_value_2;
    s21_decimal overflow_in_function = {0};
    s21_decimal result = {0};
    if (difference > 0) {
        base_multiply(*value_2, ten_power[difference], &result, &overflow_in_function);
        *value_2 = result;
        value_2->bits[3] = value_1->bits[3];
    } else if (difference < 0) {
        difference = -difference;
        base_multiply(*value_1, ten_power[difference], &result, &overflow_in_function);
        *value_1 = result;
        value_1->bits[3] = value_2->bits[3];
    }

    if (!is_zero(overflow_in_function)) {
        *overflow = overflow_in_function;
        output = DEC_HUGE;
    }

    return output;
}

void my_print(s21_decimal num) {
   for (int i = 3; i > -1; i--) {
        for (int n = 31; n > -1; n--) {
        printf("%d", isSetBit(num.bits[i], n));
        }
        printf(" ");
    }
    printf("\n"); 
}




int main(void) {
    // s21_decimal num_1 = {0, 0, 0, 983040};
    // s21_decimal num_2 = {maxInt, 0, 0, 196608};
    s21_decimal result = {{3053453312, 871104183, 369867699, maxScale}};
    s21_decimal expected = {{max32bit, 0, 0, 196608}};
    s21_decimal scale = {{0, 0, 0, maxScale}};
    s21_decimal owerflow = {0};
    s21_decimal result_overflow = {{542101, 0, 0, 0}};
    // my_print(num_1);
    my_print(scale);
    my_print(expected);
    my_print(result);
    
    // s21_decimal num_2 = {maxInt, 0, 0, maxScale};
    // print_hex(num_2);
    // print_bin(num_2);
    printf("%d\n", alignment_scale(&expected, &scale, &owerflow));
    // my_print(owerflow);
    // my_print(scale);
    my_print(expected);
    // my_print(result);
    my_print(owerflow);
    my_print(result_overflow);
    printf("%u\n", owerflow.bits[0]);
    printf("%u\n", result_overflow.bits[0]);
    // s21_decimal result = {0};
    // s21_decimal overflow = {0};
    // // s21_decimal num_1 = {4294967294, 0, 0, 0};
    // // print_bin(num_1);
    // // base_multiply(num_1, d_ten, &result, &overflow);
    // my_print(num_1);
    // my_print(num_2);
    // print_bin(num_2);
    // print_bin(num_1);
    // print_bin(num_2);

    return 0;
}