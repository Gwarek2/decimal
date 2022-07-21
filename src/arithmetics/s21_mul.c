#include "decimal_level.h"
#include "uint192.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int res_sign = get_sign(value_1) ^ get_sign(value_2);
    int res_scale = get_scale(value_1) + get_scale(value_2);

    s21_decimal overflow;
    base_multiply(value_1, value_2, result, &overflow);
    if (!is_zero(overflow) &&
        round_result(result, &overflow, &res_scale)) {
        return res_sign ? DEC_SMALL : DEC_HUGE;
    }
    while (res_scale > 28) {
        base_bank_rounding(*result, result);
        res_scale--;
    }

    set_scale(result, res_scale);
    set_sign(result, res_sign);

    return DEC_OK;
}
