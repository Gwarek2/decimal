#include "decimal_level.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
    if (result == NULL) return 1;

    s21_decimal remainder;
    int scale = get_scale(value);
    int sign = get_sign(value);

    base_divide(value, ten_power[scale], result, &remainder);

    set_sign(result, sign);
    return 0;
}
