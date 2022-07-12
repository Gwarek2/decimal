#include "common.h"
#include "binary_level.h"

/**
 * Gets nth bit
 * Works correctly with 0 >= n <= 127
**/
int get_bit(s21_decimal value, int n) {
    int index = n / 32;
    int shift = n % 32;
    return (value.bits[index] >> shift) & 1;
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

