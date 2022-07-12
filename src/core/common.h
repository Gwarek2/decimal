#ifndef _CORE_COMMON_H
#define _CORE_COMMON_H

#include <stdbool.h>

#include "decimal_type.h"

#define SCALE_SHIFT 16
#define SIGN_SHIFT 31

int init_value(s21_decimal *value, const unsigned mantiss[3], bool negative, unsigned scale);
void init_default(s21_decimal *value);
void copy_full(s21_decimal *dest, const s21_decimal *src);
void copy_mantiss(s21_decimal *dest, const s21_decimal *src);

#endif
