#include "decimal_level.h"
#include "uint192.h"
/*****************************************************************************
 * Adition with degree and sign
 * returns an error if the write is not possible to the format s21_decimal
******************************************************************************/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int other_scale = get_scale(value_1) - get_scale(value_2); // разница степеней
    s21_decimal overflow = {0};
    uint192 result_192 = {0};
    int sign_value_1 = get_sign(value_1);
    int sign_value_2 = get_sign(value_2);
    uint192 value_1_192 = {0};
    uint192 value_2_192 = {0};

    alignment_scale(&value_1, &value_2, &overflow); // вырвнивание степеней и запись переполнения
    convert_to_uint192(other_scale < 0 ? overflow : DEC_ZERO, value_1, &value_1_192); // конвертация числа с переполнением в 192бит
    convert_to_uint192(other_scale < 0 ? DEC_ZERO : overflow, value_2, &value_2_192); // конвертация числа без переполнения в 192 бит

    if (sign_value_1 && sign_value_2) { // в случае отрицательных значений
        add_uint192(value_1_192, value_2_192, &result_192);
        set_sign(result, 1);
    }
    
    if (sign_value_1 && !sign_value_2) { // первое число отрицательное
        if (gt_uint192(value_1_192, value_2_192)) { // если value_1 > value_2
            sub_uint192(value_1_192, value_2_192, &result_192);
            set_sign(result, 1);
        } else {
           sub_uint192(value_2_192, value_1_192, &result_192);
        }
    }
    
    if (!sign_value_1 && sign_value_2) { // второе число отрицательное
        if (gt_uint192(value_2_192, value_1_192)) { // если value_2 > value_1
        sub_uint192(value_2_192, value_1_192, &result_192);
        set_sign(result, 1);
        } else {
            sub_uint192(value_1_192, value_2_192, &result_192);
        }
    } 
    
    if (!sign_value_1 && !sign_value_2) { //  в случае положительных
        add_uint192(value_1_192, value_2_192, &result_192);
    }

    int scale = get_scale(value_1);
    int result_function = round_result_192(&result_192, result, &scale); // удаление переполнениия из значения
    set_scale(result, scale);
    return result_function;
}