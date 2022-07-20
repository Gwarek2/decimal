#include "common.h"
#include "decimal_level.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
    if (result == NULL) return 1;

    s21_decimal f_part = {{0}};
    init_default(result);
    int sign = get_sign(value);
    int scale = get_scale(value);

    if (!is_zero(value)) {
        base_divide(value, ten_power[scale], result, &f_part);
    }
    if (sign && !is_zero(f_part)) {
        base_addition(*result, DEC_ONE, result);
    }
    set_sign(result, sign);
    return 0;
}
