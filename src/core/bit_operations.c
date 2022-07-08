#include <stdio.h>
#include <string.h>

#include "bit_operations.h"

/**
 * Gets nth bit
 * Works correctly with 0 > n <= 128
**/
int get_bit(s21_decimal value, int n) {
    n--;
    int index = n / 32;
    int shift = n % 32;
    return (value.bits_u32_t[index] >> shift) & 1U;
}

/**
 * Sets bit to n position
 * Works correctly with 0 > n <= 128
**/
void set_bit(s21_decimal *value, int n, int bit) {
    n--;
    int index = n / 32;
    int shift = n % 32;
    value->bits_u32_t[index] = (value->bits_u32_t[index] & ~(1U << shift)) | (bit << shift);
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
 * Shifts all bits to left by given value
 * Returns 1 if overflow occurs
**/
int left_shift(const s21_decimal *value, s21_decimal *result, size_t shift) {
    int overflow = 0;
    copy_full(result, value);
    for (size_t i = 0; i < shift; i++) {
        int bit1 = get_bit(*result, 32);
        int bit2 = get_bit(*result, 64);
        overflow = get_bit(*result, 96);
        result->bits[0] <<= 1;
        result->bits[1] <<= 1;
        result->bits[2] <<= 1;
        set_bit(result, 33, bit1);
        set_bit(result, 65, bit2);
    }
    return overflow ? DEC_HUGE : DEC_OK;
}

/**
 * Shifts all bits to right by given value
**/
void right_shift(const s21_decimal *value, s21_decimal *result, size_t shift) {
    copy_full(result, value);
    for (size_t i = 0; i < shift; i++) {
        int bit1 = get_bit(*result, 65);
        int bit2 = get_bit(*result, 33);
        result->bits_u32_t[0] >>= 1;
        result->bits_u32_t[1] >>= 1;
        result->bits_u32_t[2] >>= 1;
        set_bit(result, 64, bit1);
        set_bit(result, 32, bit2);
    }
}

/**
 * Gets position of first bit from the end equal to 1
 * If value iz 
**/
uint32_t last_bit(s21_decimal value) {
    uint32_t bit = 0;
    int32_t i = 96;
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

/**
 * Outputs decimal in binary format
 * !!Add output of scale and sign bit field
**/
void print_bin(s21_decimal value) {
    char bin[97];
    for (size_t i = 0; i < 96 ; i++) {
        bin[i] = get_bit(value, 96 - i) + '0';
    }
    bin[96] = '\0';
    printf("%s\n", bin);
}

/**
 * Outputs decimal in hex format
 * !!Add output of scale and sign hex field
**/
void print_hex(s21_decimal value) {
    if (value.bits[2]) printf("%#x", value.bits[2]);
    if (!value.bits[2] && value.bits[1]) printf("%#x", value.bits[1]);
    else if (value.bits[1]) printf("%08x", value.bits[1]);
    if (!value.bits[2] && !value.bits[1] && value.bits[0]) printf("%#x", value.bits[0]);
    else if (value.bits[0]) printf("%08x", value.bits[0]);
    else putchar('0');
    putchar('\n');
}
