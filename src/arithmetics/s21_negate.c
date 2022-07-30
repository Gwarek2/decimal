#include "uint96.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
    *result = value;
    set_sign(result, is_zero(value) ? 0 : !get_sign(value));
    return DEC_OK;
}
