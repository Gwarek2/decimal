#include "uint192_operations.h"

void convert_to_uint192(s21_decimal higher, s21_decimal lower, uint192 *result) {
    result->bits[0] = lower.bits[0];
    result->bits[1] = lower.bits[1];
    result->bits[2] = lower.bits[2];
    result->bits[3] = higher.bits[3];
    result->bits[4] = higher.bits[4];
    result->bits[5] = higher.bits[5];
}

int get_bit_uint192(uint192 value, int index) {
    int field = index / 32;
    int shift = index % 32;
    return (value.bits[field] >> shift) & 1U;
}

int set_bit_uint192(uint192 *value, int bit, int index) {
    int field = index / 32;
    int shift = index % 32;
    value->bits_u32_t[field] = (value->bits_u32_t[field] & ~(1U << shift)) | (bit << shift);
}

void left_shift_uint192(uint192 value, size_t shift, uint192 *result) {
    for (size_t i = 0; i < shift; i++) {
        unsigned bits[5] = {0};
        for (size_t j = 31; j < 191; j += 32) bits[j / 32] = get_bit_uint192(value, j);
        for (size_t j = 0; j < 6; j++) value.bits[j] <<= 1;
        for (size_t j = 32; j < 191; j += 32) set_bit_uint192(&value, bits[j / 32], j);
    }
    *result = value;
}

void subtract_uint192(uint192 value1, uint192 value2, uint192 *result) {
    int borrow = 0;
    for (size_t i = 0; i < 6; i++) {
        result->bits[i] = value1.bits[i] - value2.bits[i] - borrow;
        borrow = (uint64_t) value1.bits[i] < (uint64_t) value1.bits[i] + borrow;
    }
}

void divide_uint192(uint192 value1, uint192 value2, uint192 *result, uint192 *remainder) {

}

