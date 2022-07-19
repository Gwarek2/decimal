#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "binary_level.h"
#include "common.h"
#include "decimal_level.h"
#include "../decimal_type.h"
#include "output.h"
#include "uint192.h"

#define SCALE_SHIFT 16
#define SIGN_SHIFT 31

unsigned isSetBit(int number, int index) {
    return (number&(1<<index))!=0;
}


unsigned int setBit(int number, int index) {
    return number | (1 << index);
}

int my_print(s21_decimal value) {
    for (int i = 3; i > -1; i--) {
            for (int n = 31; n > -1; n--) {
            printf("%d", isSetBit(value.bits[i], n));
            }
            printf(" ");
        }
    printf("\n");
}

int my_print_192(uint192 value) {
    for (int i = 5; i > -1; i--) {
            for (int n = 31; n > -1; n--) {
            printf("%d", isSetBit(value.bits[i], n));
            }
            printf(" ");
        }
    printf("\n");
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

/*****************************************
 * Shifts all bits to right by given value
 *****************************************/
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

/****************************************************
 * Gets position of first bit from the end equal to 1
 * Returns 0 if value is equal to 0
 *****************************************************/
unsigned last_bit(s21_decimal value) {
    int i = 95;
    while (!get_bit(value, i) && i) {
        i--;
    }
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

/**
 * Initializes decimal value with given mantiss, sign and scale
 **/
int init_value(s21_decimal *value, const unsigned mantiss[3], bool negative,
               unsigned scale) {
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
    unsigned buff[3] = {0};
    init_value(value, buff, 0, 0);
}

/**
 * Converts sign and scale to uint field
 * Returns converted field
 **/
unsigned init_sign_and_scale(int sign, int scale) {
    return (sign << SIGN_SHIFT) | (scale << SCALE_SHIFT);
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

unsigned get_scale(s21_decimal value) {
    unsigned scale = (value.bits_u32_t[3] >> SCALE_SHIFT) & 0xff;
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
 *integer, where *overflow contains higher bit fields and *result - lower bit
 *fields
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
                result->bits_u32_t[i + j] = r & MASK_32;
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
 * the function equalizes the exponent before multiplication, addition, and
 *division. Monitor overflow.
 *
 **/

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
    *overflow = overflow_in_function;

    if (!is_zero(overflow_in_function)) {
        *overflow = overflow_in_function;
        output = DEC_HUGE;
    }

    return output;
}
/*****************************************************************************
 * Removes one digit from beginning and implements bank rounding
 * Scale and sign remain unchanged
 * if removed digit < 5 - result remains unchanged
 * if removed digit > 5 - result increments by one
 * if removed digit == 5 and rightmost digit is odd
 *     result increments by one
 * if removed digit == 5 and rightmost digit is even (including zero)
 *     result remains unchanged
 * About bank rounding - https://rounding.to/understanding-the-bankers-rounding
 ******************************************************************************/
void base_bank_rounding(s21_decimal value, s21_decimal *result) {
    s21_decimal first_digit;
    base_divide(value, DEC_TEN, result, &first_digit);
    if (bits_gt(first_digit, DEC_FIVE) ||
        (bits_eq(first_digit, DEC_FIVE) && get_bit(*result, 0))) {
        base_addition(*result, DEC_ONE, result);
    }
}

/**
 * Outputs decimal in binary format
 **/
void print_bin(s21_decimal value) {
    char bin[130];
    for (size_t i = 0; i < 128; i++) {
        bin[i] = get_bit(value, 127 - i) + '0';
    }
    bin[129] = '\0';
    printf("%s\n", bin);
}

/**
 * Outputs decimal in hex format
 **/
void print_hex(s21_decimal value) {
    printf("%#10X %#10X %#10X    %#10X\n", value.bits[2], value.bits[1], value.bits[0], value.bits[3]);
}


int get_bit_uint192(uint192 value, int index);
void set_bit_uint192(uint192 *value, int bit, int index);
int last_bit_uint192(uint192 value);

/**************************************************
 * Converts two s21_decimal buffers to uint192 type
 * Scale and sign are ingored
**************************************************/
void convert_to_uint192(s21_decimal higher, s21_decimal lower, uint192 *result) {
    memcpy(result->bits, lower.bits, sizeof(unsigned) * 3);
    memcpy(result->bits + 3, higher.bits, sizeof(unsigned) * 3);
}

/*******************************************************
 * Converts uint192 to s21_decimal
 * if value is less than or equal to s21_decimal maximum
*******************************************************/
int convert_to_decimal(uint192 value, s21_decimal *buffer) {
    if (gt_uint192(value, UINT192_DEC_MAX)) return 1;
    memcpy(buffer->bits, value.bits, sizeof(unsigned) * 3);
    return 0;
}

void init_default_uint192(uint192 *buffer) {
    unsigned value[6] = {0};
    memcpy(buffer->bits, value, sizeof(unsigned) * 6);
}

void copy_uint192(uint192 *buffer, const uint192 value) {
    memcpy(buffer, &value, sizeof(uint192));
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
    while (!get_bit_uint192(value, i) && i) {i--;}
    return i;
}

/******************************
 * Shifts value to left n times
******************************/
void left_shift_uint192(uint192 value, size_t n, uint192 *result) {
    *result = value;
    for (size_t i = 0; i < n; i++) {
        unsigned bits[5] = {0};
        for (size_t j = 31; j < 192; j += 32) bits[j / 32] = get_bit_uint192(*result, j);
        for (size_t j = 0; j < 6; j++) result->bits[j] <<= 1;
        for (size_t j = 32; j < 192; j += 32) set_bit_uint192(result, bits[j / 32 - 1], j);
        // int bit1 = get_bit_uint192(*result, 31);
        // int bit2 = get_bit_uint192(*result, 63);
        // int bit3 = get_bit_uint192(*result, 95);
        // int bit4 = get_bit_uint192(*result, 127);
        // int bit5 = get_bit_uint192(*result, 159);
        // result->bits[0] <<= 1;
        // result->bits[1] <<= 1;
        // result->bits[2] <<= 1;
        // result->bits[3] <<= 1;
        // result->bits[4] <<= 1;
        // result->bits[5] <<= 1;
        // set_bit_uint192(result, 32, bit1);
        // set_bit_uint192(result, 64, bit2);
        // set_bit_uint192(result, 96, bit3);
        // set_bit_uint192(result, 128, bit4);
        // set_bit_uint192(result, 160, bit5);
    }
}

/**********************************************************
 * Subtracts value2 from value1 and writes result to buffer
**********************************************************/
void sub_uint192(uint192 value1, uint192 value2, uint192 *result) {
    int borrow = 0;
    for (size_t i = 0; i < 6; i++) {
        result->bits[i] = value1.bits[i] - value2.bits[i] - borrow;
        borrow = (uint64_t) value1.bits[i] < (uint64_t) value2.bits[i] + borrow;
    }
}

/*****************************************************
 * Adds value1 to value2 and writes result into buffer
*****************************************************/
int add_uint192(uint192 value1, uint192 value2, uint192 *result) {
    int carrial = 0;
    for (size_t i = 0; i < 6; i++) {
        uint64_t r = (uint64_t) value1.bits[i] +
                     (uint64_t) value2.bits[i] + carrial;
        carrial = r >> 32;
        result->bits[i] = r;
    }
    return carrial;
}

/*********************************************************************
 * Divides value1 by value2 and writes result and remainder to buffers
*********************************************************************/
void divide_uint192(uint192 value1, uint192 value2, uint192 *result, uint192 *remainder) {
    *remainder = value1;
    for (int i = last_bit_uint192(value1) - last_bit_uint192(value2); i >= 0; i--) {
        uint192 tmp1, tmp2;
        left_shift_uint192(value2, i, &tmp1);
        if ((lt_uint192(tmp1, *remainder) || eq_uint192(tmp1, *remainder)) && !eq_uint192(tmp1, UINT192_ZERO)) {
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

/****************************************************
 * Outputs uint192 in hex format higher bits to lower
****************************************************/
void print_hex_uint192(uint192 value) {
    for (int i = 5; i >= 0; i--) {
        printf("%#15x", value.bits[i]);
    }
    putchar('\n');
}

/************************************************
 * Removes first digit nad applies bank rounding
************************************************/
void bank_rounding_uint192(uint192 value, uint192 *result) {
    init_default_uint192(result);
    uint192 first_digit = {{0}};
    divide_uint192(value, UINT192_TEN, result, &first_digit);
    if (gt_uint192(first_digit, UINT192_FIVE) ||
        (eq_uint192(first_digit, UINT192_FIVE) && get_bit_uint192(*result, 0))) {
        add_uint192(*result, UINT192_ONE, result);
    }
}

int round_result(s21_decimal *result, s21_decimal *overflow, int *scale) {
    uint192 value = {{0}};
    convert_to_uint192(*overflow, *result, &value);
    while (*scale && gt_uint192(value, UINT192_DEC_MAX)) {
        bank_rounding_uint192(value, &value);
        *scale -= 1;
    }
    int is_overflow = convert_to_decimal(value, result);
    return is_overflow;
}

int round_result_192(uint192 *value, s21_decimal *result, int *scale) {
    while (*scale && gt_uint192(*value, UINT192_DEC_MAX)) {
        bank_rounding_uint192(*value, value);
        *scale -= 1;
    }
    int is_overflow = convert_to_decimal(*value, result);
    return is_overflow;
}



int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int other_scale = get_scale(value_1) - get_scale(value_2);
    if (other_scale != 0) {
        printf("ok\n");
        s21_decimal overflow = {0};
        alignment_scale(&value_1, &value_2, &overflow);
        if (!is_zero(overflow)) {
            uint192 with_overflow = {0};
            s21_decimal not_owerflov = other_scale > 0 ? value_1 : value_2;
            convert_to_uint192(overflow, not_owerflov, &with_overflow);
            uint192 without_overflow = {0};
            convert_to_uint192(DEC_ZERO, not_owerflov, &without_overflow);
            uint192 result_add_192 = {0};
            add_uint192(with_overflow, without_overflow, &result_add_192);
            convert_to_decimal(result_add_192, result);
        }  else {
            printf("Ok");
            base_addition(value_1, value_2, result);
        }
    } 



    return 0;
}



int main() {
    unsigned int maxInt = 4294967295;
    s21_decimal a = {maxInt, maxInt, maxInt, 0};
    s21_decimal b = {maxInt, maxInt, 0, 0};
    s21_decimal result = {0};
    uint192 bit_192 = {maxInt,maxInt, 0, 0, 0, 0};
    int scale = 28;
    s21_add(a, b, &result);
    // printf("%d\n", scale);
    // my_print_192(bit_192);
    // round_result_192(&bit_192, &result, &scale);
    // my_print_192(bit_192);
    // printf("%d\n", scale);
    my_print(result);


    return 0;
}
