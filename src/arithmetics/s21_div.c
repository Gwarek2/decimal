#include "binary_level.h"
#include "common.h"
#include "output.h"
#include "decimal_level.h"
#include "uint192.h"

void maximize_divt(uint192 divt, uint192 *result, int *scale);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (is_zero(value_2)) return DEC_DIV_BY_ZERO;
    if (is_zero(value_1)) {
        init_default(result);
        return DEC_OK;
    }

    uint192 divr, divd, rem;
    s21_decimal res, lower, higher;
    int sign = get_sign(value_1) ^ get_sign(value_2);
    int scale = get_scale(value_1) + 28 - get_scale(value_2);

    base_multiply(value_1, ten_power[28], &lower, &higher);
    convert_to_uint192(higher, lower, &divr);
    convert_to_uint192(DEC_ZERO, value_2, &divd);
    maximize_divr(divr, &divr, &scale);

    divide_uint192(divr, divd, &divr, &rem);
    if (round_result(divr, &res, &scale))
        return sign ? DEC_SMALL : DEC_HUGE;

    set_scale(&res, scale);
    remove_trailing_zeros(res, &res);
    set_sign(&res, sign);
    *result = res;

    return DEC_OK;
}

void maximize_divt(uint192 divt, uint192 *result, int *scale) {
    while (true) {
        uint192 tmp;
        if (mul_uint192(divr, UINT192_TEN, &tmp)) break;
        copy_uint192(&divr, tmp);
        (*scale)++;
    }
    *result = divr;
}
