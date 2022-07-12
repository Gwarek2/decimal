#include "common.h"
#include "decimal_level.h"
#include "decimal_type.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
    if (result == NULL) return 1;
    copy_full(result, &value);
    set_sign(result, is_zero(value) ? 0 : !get_sign(value));
    return 0;
}

