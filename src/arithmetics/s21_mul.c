#include "common.h"
#include "decimal_level.h"
#include "uint192.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    init_default(result);
    int res_sign = get_sign(value_1) ^ get_sign(value_2);
    int res_scale = get_scale(value_1) + get_scale(value_2);

    s21_decimal res, overflow;
    uint192 tmp;
    base_multiply(value_1, value_2, &res, &overflow);
    convert_to_uint192(overflow, res, &tmp);
    if (round_result(tmp, &res, &res_scale))
        return res_sign ? DEC_SMALL : DEC_HUGE;

    set_scale(&res, res_scale);
    set_sign(&res, res_sign);
    *result = res;

    return DEC_OK;
}
