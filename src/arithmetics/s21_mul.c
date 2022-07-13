#include "decimal_level.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (result == NULL) return 1;
    int res_sign = get_sign(value_1) ^ get_sign(value_2);
    int res_scale = get_scale(value_1) + get_scale(value_2);

    s21_decimal res, overflow;
    init_default(res);
    init_default(overflow);
    base_multiply(value_1, value_2, &res, &overflow);
    while (!is_zero(overflow) && res_scale) {
    }
    return 0;
}
