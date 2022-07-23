#include <stdio.h>
#include <string.h>

#include "common.h"

/**************************************************************
 * Initializes decimal value with given mantiss, sign and scale
**************************************************************/
int init_value(s21_decimal *value, const unsigned mantiss[3], bool negative, unsigned scale) {
    int error = scale > 28;
    if (!error) {
        memcpy(value->bits, mantiss, 3 * sizeof(unsigned));
        unsigned last_chunk = (negative << SIGN_SHIFT) | (scale << SCALE_SHIFT);
        value->bits_u32_t[3] = last_chunk;
    }
    return error;
}

/*************************************
 * Initializes decimal with zero value
*************************************/
void init_default(s21_decimal *value) {
    memset(value, 0, sizeof(s21_decimal));
}

/***************************************
 * Converts sign and scale to uint field
 * Returns converted field
***************************************/
unsigned init_sign_and_scale(int sign, int scale) {
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
    memcpy(dest->bits, src->bits, sizeof(unsigned) * 3);
}

