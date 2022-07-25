#include "binary_level.h"
#include "common.h"
#include "decimal_level.h"
#include "uint192.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    init_default(result);
    int division_by_zero = is_zero(value_2);

    if (!division_by_zero) {
        if (get_sign(value_1)) set_sign(result, 1);
        int other_scale = get_scale(value_1) - get_scale(value_2); // разница степеней
        s21_decimal overflow = {0};
        uint192 value_1_192 = {0};
        uint192 value_2_192 = {0};
        uint192 result_192 = {0};
        uint192 remainder = {0};
        int scale = get_scale(other_scale < 0 ? value_2 : value_1);
        alignment_scale(&value_1, &value_2, &overflow); // вырвнивание степеней и запись переполнения
        convert_to_uint192(other_scale < 0 ? overflow : DEC_ZERO, value_1, &value_1_192); // конвертация числа с переполнением в 192бит
        convert_to_uint192(other_scale < 0 ? DEC_ZERO : overflow, value_2, &value_2_192); // конвертация числа без переполнения в 192 бит
        divide_uint192(value_1_192, value_2_192, &result_192, &remainder); // базовое деление
        round_result(remainder, result, &scale);
        set_scale(result, scale);
    }

    return division_by_zero ? DEC_DIV_BY_ZERO : DEC_OK;
}
