#include "common.h"
#include "decimal_level.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
    init_default(result);

    s21_decimal fr_part;
    int scale = get_scale(value);
    int sign = get_sign(value);

    base_divide(value, ten_power[scale], result, &fr_part);

    set_sign(result, sign);
    return 0;
}
