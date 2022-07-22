#include "binary_level.h"
#include "common.h"
#include "output.h"
#include "decimal_level.h"
#include "uint192.h"

void maximize_divd(s21_decimal value, uint192 *result, int *scale);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (is_zero(value_2)) return DEC_DIV_BY_ZERO;
    if (is_zero(value_1)) {
        init_default(result);
        return DEC_OK;
    }

    s21_decimal res; 
    uint192 divr, divd, rem;
    int sign = get_sign(value_1) ^ get_sign(value_2);
    int scale = get_scale(value_1) - get_scale(value_2);

    maximize_divd(value_1, &divd, &scale);
    convert_to_uint192(DEC_ZERO, value_2, &divr);
    divide_uint192(divd, divr, &divd, &rem);
    if (round_result(divd, &res, &scale))
        return sign ? DEC_SMALL : DEC_HUGE;

    set_scale(&res, scale);
    remove_trailing_zeros(res, &res);
    set_sign(&res, sign);
    *result = res;

    return DEC_OK;
}

/***************************************************************
 * Adds zeros to divident until it reaches uint192 maximum value
***************************************************************/
void maximize_divd(s21_decimal value, uint192 *divd, int *scale) {
    s21_decimal lower, higher;
    base_multiply(value, ten_power[28], &lower, &higher);
    *scale += 28;
    convert_to_uint192(higher, lower, divd);
    while (true) {
        uint192 tmp;
        if (mul_uint192(*divd, UINT192_TEN, &tmp)) break;
        copy_uint192(divd, tmp);
        (*scale)++;
    }
}
