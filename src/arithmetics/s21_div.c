#include "binary_level.h"
#include "common.h"
#include "decimal_level.h"
#include "uint192.h"


int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (is_zero(value_2)) return DEC_DIV_BY_ZERO;
    if (is_zero(value_1)) {
        init_default(result);
        return DEC_OK;
    }
    int sign = get_sign(value_1) ^ get_sign(value_2);
    int scale = get_scale(value_1) - get_scale(value_2);

    uint192 quot, div, res, rem;
    s21_decimal lower, higher;
    int added_scale = 28;
    base_multiply(value_1, ten_power[28], &lower, &higher);
    convert_to_uint192(higher, lower, &quot);
    convert_to_uint192(DEC_ZERO, value_2, &div);
    while (true) {
        uint192 tmp;
        if (mul_uint192(quot, UINT192_TEN, &tmp)) break;
        copy_uint192(&quot, tmp);
        added_scale++;
    }
    divide_uint192(quot, div, &res, &rem);
    round_result(res, &res, &added_scale);

    return DEC_OK;
}

// int fractional_div(s21_decimal value1, s21_decimal value_2, s21_decimal result) {
// }
