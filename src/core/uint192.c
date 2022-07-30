#include "uint192.h"
#include <stdio.h>
#include <string.h>

int get_bit_uint192(uint192 value, int index);
void set_bit_uint192(uint192 *value, int bit, int index);
int last_bit_uint192(uint192 value);

void init_default_uint192(uint192 *buffer) {
    memset(buffer, 0, sizeof(uint192));
}

void copy_uint192(uint192 *buffer, const uint192 value) {
    memcpy(buffer, &value, sizeof(uint192));
}

/**************************************************
 * Converts two s21_decimal buffers to uint192 type
 * Scale and sign are ingored
 **************************************************/
void convert_to_uint192(s21_decimal higher, s21_decimal lower,
                        uint192 *result) {
    memcpy(result->bits, lower.bits, sizeof(unsigned) * 3);
    memcpy(result->bits + 3, higher.bits, sizeof(unsigned) * 3);
}

/*******************************************************
 * Converts uint192 to s21_decimal
 * if value is less than or equal to s21_decimal maximum
 *******************************************************/
int convert_to_decimal(uint192 value, s21_decimal *buffer) {
    if (gt_uint192(value, UINT192_DEC_MAX))
        return 1;
    memcpy(buffer->bits, value.bits, sizeof(unsigned) * 3);
    return 0;
}

/**********************************************
 * Gets bit by index
 * Correctly works with range 0 <= index <= 191
 **********************************************/
int get_bit_uint192(uint192 value, int index) {
    int field = index / 32;
    int shift = index % 32;
    return (value.bits[field] >> shift) & 1U;
}

/**********************************************
 * Sets bit by index
 * Correctly works with range 0 <= index <= 191
 **********************************************/
void set_bit_uint192(uint192 *value, int bit, int index) {
    int field = index / 32;
    int shift = index % 32;
    value->bits[field] = (value->bits[field] & ~(1U << shift)) | (bit << shift);
}

/***********************************
 * Gets index of last bit equal to 1
 * if value is zero returns 0;
 ***********************************/
int last_bit_uint192(uint192 value) {
    size_t i = 191;
    while (!get_bit_uint192(value, i) && i) {
        i--;
    }
    return i;
}

/******************************
 * Shifts value to left n times
 ******************************/
void left_shift_uint192(uint192 value, size_t n, uint192 *result) {
    copy_uint192(result, value);
    for (size_t i = 0; i < n; i++) {
        unsigned bits[5] = {0};
        for (size_t j = 31; j < 191; j += 32)
            bits[j / 32] = get_bit_uint192(*result, j);
        for (size_t j = 0; j < 6; j++)
            result->bits[j] <<= 1;
        for (size_t j = 32; j < 192; j += 32)
            set_bit_uint192(result, bits[j / 32 - 1], j);
    }
}

/**********************************************************
 * Subtracts value2 from value1 and writes result to buffer
 **********************************************************/
void sub_uint192(uint192 value1, uint192 value2, uint192 *result) {
    int borrow = 0;
    for (size_t i = 0; i < 6; i++) {
        result->bits[i] = value1.bits[i] - value2.bits[i] - borrow;
        borrow = (uint64_t)value1.bits[i] < (uint64_t)value2.bits[i] + borrow;
    }
}

/*****************************************************
 * Adds value1 to value2 and writes result into buffer
 *****************************************************/
int add_uint192(uint192 value1, uint192 value2, uint192 *result) {
    int carrial = 0;
    for (size_t i = 0; i < 6; i++) {
        uint64_t r =
            (uint64_t)value1.bits[i] + (uint64_t)value2.bits[i] + carrial;
        carrial = r >> 32;
        result->bits[i] = r;
    }
    return carrial;
}

/*******************************
 * Multiplies two uint192 values
 *******************************/
bool mul_uint192(uint192 value1, uint192 value2, uint192 *result) {
    bool overflow = 0;
    init_default_uint192(result);
    for (size_t i = 0; i < 6; i++) {
        uint32_t mul_carrial = 0;
        uint32_t add_carrial = 0;
        for (size_t j = 0; j + i < 6; j++) {
            uint64_t r = (uint64_t)value1.bits[i] * (uint64_t)value2.bits[j] +
                         mul_carrial + add_carrial;
            mul_carrial = r >> 32;
            r = (r & 0xFFFFFFFF) + result->bits[j + i];
            add_carrial = r >> 32;
            result->bits[i + j] = r;
        }
        overflow = mul_carrial || add_carrial;
    }
    return overflow;
}

/*********************************************************************
 * Divides value1 by value2 and writes result and remainder to buffers
 *********************************************************************/
void divide_uint192(uint192 value1, uint192 value2, uint192 *result,
                    uint192 *remainder) {
    *remainder = value1;
    init_default_uint192(result);
    for (int i = last_bit_uint192(value1) - last_bit_uint192(value2); i >= 0;
         i--) {
        uint192 tmp1, tmp2;
        left_shift_uint192(value2, i, &tmp1);
        if ((lt_uint192(tmp1, *remainder) || eq_uint192(tmp1, *remainder)) &&
            !eq_uint192(tmp1, UINT192_ZERO)) {
            sub_uint192(*remainder, tmp1, remainder);
            left_shift_uint192(UINT192_ONE, i, &tmp2);
            add_uint192(*result, tmp2, result);
        }
    }
}

/***************************************
 * Checks if value1 and value2 are equal
 ***************************************/
bool eq_uint192(uint192 value1, uint192 value2) {
    bool eq = true;
    for (size_t i = 0; i < 6 && eq; i++) {
        eq = value1.bits[i] == value2.bits[i];
    }
    return eq;
}

/***********************************
 * Checks if value1 less than value2
 ***********************************/
bool lt_uint192(uint192 value1, uint192 value2) {
    bool less = false;
    bool eq = true;
    for (int i = 5; i >= 0 && !less && eq; i--) {
        less = value1.bits[i] < value2.bits[i];
        eq = value1.bits[i] == value2.bits[i];
    }
    return less;
}

/*****************************************
 * Checks if value1 is greater than value2
 *****************************************/
bool gt_uint192(uint192 value1, uint192 value2) {
    bool greater = false;
    bool eq = true;
    for (int i = 5; i >= 0 && !greater && eq; i--) {
        greater = value1.bits[i] > value2.bits[i];
        eq = value1.bits[i] == value2.bits[i];
    }
    return greater;
}

void bank_rounding(uint192 *value, uint192 last_digit) {
    if (gt_uint192(last_digit, UINT192_FIVE) ||
        (eq_uint192(last_digit, UINT192_FIVE) && get_bit_uint192(*value, 0))) {
        add_uint192(*value, UINT192_ONE, value);
    }
}

/***************************************************************************************************
 * Removes overflow from value and applies bank rounding considering only the
 *first overflowed digit Returns 1 if overflow remains after rounding Returns 0
 *if rounded suscesfully
 ***************************************************************************************************/
int round_result(uint192 value, s21_decimal *result, int *scale) {
    uint192 last_digit = {{0}};
    while (*scale && (gt_uint192(value, UINT192_DEC_MAX) || *scale > 28)) {
        divide_uint192(value, UINT192_TEN, &value, &last_digit);
        (*scale)--;
    }
    bank_rounding(&value, last_digit);
    return convert_to_decimal(value, result);
}
