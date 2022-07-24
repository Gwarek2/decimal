#include "common.h"
#include "decimal_level.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
    init_default(result);

    s21_decimal int_part, f_part;
    int sign = get_sign(value);
    int scale = get_scale(value);

    if (!is_zero(value)) {
        base_divide(value, ten_power[scale], &int_part, &f_part);
    } else {
        init_default(&int_part);
    }
    if (sign && !is_zero(f_part)) {
        base_addition(int_part, DEC_ONE, &int_part);
    }
    set_sign(&int_part, sign);
    *result = int_part;
    return 0;
}
