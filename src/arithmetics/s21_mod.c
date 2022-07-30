#include "uint96.h"
#include "uint192.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    init_default(result);
    if (is_zero(value_2))
        return DEC_DIV_BY_ZERO;

    if (get_sign(value_1))
        set_sign(result, 1);
    int result_scale = get_scale(value_1) - get_scale(value_2);
    s21_decimal overflow = {0};
    uint192 value_1_192 = {0};
    uint192 value_2_192 = {0};
    uint192 result_192 = {0};
    uint192 remainder = {0};
    int scale = get_scale(result_scale < 0 ? value_2 : value_1);
    equalize_scales(&value_1, &value_2, &overflow);
    convert_to_uint192(result_scale < 0 ? overflow : DEC_ZERO, value_1, &value_1_192);
    convert_to_uint192(result_scale < 0 ? DEC_ZERO : overflow, value_2, &value_2_192);
    divide_uint192(value_1_192, value_2_192, &result_192, &remainder);
    round_result(remainder, result, &scale);
    set_scale(result, scale);

    return DEC_OK;
}
