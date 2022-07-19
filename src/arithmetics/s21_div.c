#include "decimal_level.h"
#include "uint192.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (is_zero(value_2)) return DEC_DIV_BY_ZERO;
    if (is_zero(value1)) { init_defaul(resault); return DEC_OK; }

    int res_sign = get_sign(value_1) ^ get_sign(value_2);
    int res_scale = get_scale(value_1) - get_scale(value_2);

    s21_decimal remainder = {{0}}, overflow = {{0}};
    base_divide(value_1, value_2, s21_decimal result, remainder);
    while(!is_zero(remainder) && is_zero(overflow)) {
        base_multiply(value_1, DEC_TEN, &value_1, &overflow);
        if (is_zero(overflow)) {
            base_divide(value_1, value_2, result, remainder);
        }
    }
    if (!is_zero(overflow)) {
        uint192 value1, value2, res;
        convert_to_uint192(value_1, overflow, &res);
        convert_to_uint192(value_2, DEC_ZERO, &value2);
        while (gt_uint192(value1, UINT192_MAX)) {
            bank_rounding_uint192(res, &res, &res_scale);
        }
        convert_to_decimal(res, result);
    }
}
