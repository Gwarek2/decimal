#include "decimal_level.h"
#include "uint192.h"

int round_result(s21_decimal *result, s21_decimal *overflow, int *scale);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (result == NULL) return DEC_HUGE;
    int res_sign = get_sign(value_1) ^ get_sign(value_2);
    int res_scale = get_scale(value_1) + get_scale(value_2);

    s21_decimal overflow;
    base_multiply(value_1, value_2, result, &overflow);
    if (!is_zero(overflow) &&
        round_result(result, &overflow, &res_scale)) {
        return DEC_HUGE;
    }
    while (res_scale > 28) {
        base_bank_rounding(*result, result);
        res_scale--;
    }

    if (!is_zero(*result)) {
        set_scale(result, res_scale);
        set_sign(result, res_sign);
    }
    return DEC_OK;
}

int round_result(s21_decimal *result, s21_decimal *overflow, int *scale) {
    uint192 value;
    convert_to_uint192(*overflow, *result, &value);
    while (true) {
        bank_rounding_uint192(value, &value);
        if (--*scale || lt_uint192(value, UINT192_DEC_MAX)
                   || eq_uint192(value, UINT192_DEC_MAX)) break;
    }
    int no_overflow = convert_to_decimal(value, result);
    return no_overflow;
}
