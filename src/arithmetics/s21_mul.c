#include "decimal_level.h"
#include "uint192.h"

int round_result(s21_decimal *result, s21_decimal *overflow, int *scale);

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

int round_result(s21_decimal *result, s21_decimal *overflow, int *scale) {
    uint192 value = {{0}};
    convert_to_uint192(*overflow, *result, &value);
    while (*scale && gt_uint192(value, UINT192_DEC_MAX)) {
        bank_rounding_uint192(value, &value);
        *scale -= 1;
    }
    int is_overflow = convert_to_decimal(value, result);
    return is_overflow;
}
