#include "common.h"
#include "binary_level.h"
#include "decimal_type.h"

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

/*****************************************
 * Shifts all bits to right by given value
*****************************************/
void right_shift(const s21_decimal *value, s21_decimal *result, size_t shift) {
    copy_full(result, value);
    for (size_t i = 0; i < shift; i++) {
        int bit1 = get_bit(*result, 64);
        int bit2 = get_bit(*result, 32);
        result->bits[0] >>= 1;
        result->bits[1] >>= 1;
        result->bits[2] >>= 1;
        set_bit(result, 63, bit1);
        set_bit(result, 31, bit2);
    }
}

/****************************************************
 * Gets position of first bit from the end equal to 1
 * Returns 0 if value is equal to 0
*****************************************************/
unsigned last_bit(s21_decimal value) {
    int i = 95;
    while (!get_bit(value, i) && i) {i--;}
    return i;
}

/********************************************
 * Checks if bits in first 3 chunks are equal
 * Does not care about scale and sign
********************************************/
int bits_eq(s21_decimal value1, s21_decimal value2) {
    bool eq = true;
    for (int i = 2; i >= 0 && eq; i--) {
        eq = value1.bits[i] == value2.bits[i];
    }
    return eq;
}

/************************************
 * Checks if value1 less than value2
 * Does not care about scale and sign
************************************/
int bits_lt(s21_decimal value1, s21_decimal value2) {
    bool less = false;
    bool eq = true;
    for (int i = 2; i >= 0 && !less && eq; i--) {
        less = value1.bits[i] < value2.bits[i];
        eq = value1.bits[i] == value2.bits[i];
    }
    return less;
}

/**************************************
 * Checks if value1 greater than value2
 * Does not care about scale and sign
**************************************/
int bits_gt(s21_decimal value1, s21_decimal value2) {
    bool more = false;
    bool eq = true;
    for (int i = 2; i >= 0 && !more && eq; i--) {
        more = value1.bits[i] > value2.bits[i];
        eq = value1.bits[i] == value2.bits[i];
    }
    return more;
}

// The function returns the lowest bit and shifts the values in the buffers to the right
int shift_right(s21_decimal *src) {
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
