/************************************************
 * Uint192 type implemented for handling overflows
 * in arithmetic operations with s21_decimal type
************************************************/

#ifndef _UINT192_OPERATIONS_H
#define _UINT192_OPERATIONS_H

#include "decimal_type.h"

typedef struct {
    unsigned bits[6];
} uint192;

void convert_to_uint192(s21_decimal higher, s21_decimal lower, uint192 *result);

#endif  // _INT192_OPERATIONS_H
