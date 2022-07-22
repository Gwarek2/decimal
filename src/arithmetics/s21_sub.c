#include "decimal_level.h"
#include "uint192.h"

/*************************************************************************
 * Signed and exponential subtraction 
 * returns an error if writing to s21 decimal format is not possible
**************************************************************************/
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
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

    // в случае отрицательных значений
    if (sign_value_1 && sign_value_2) { // оба числа отрицательные
        if (gt_uint192(value_1_192, value_2_192)) { // если value_1 > value_2
            sub_uint192(value_1_192, value_2_192, &result_192);
            set_sign(result, 1);
        } else {
            sub_uint192(value_2_192, value_1_192, &result_192);
        }
    } else if (sign_value_1 && !sign_value_2) { // первое число отрицательное 
            add_uint192(value_1_192, value_2_192, &result_192);
            set_sign(result, 1);
    } else if (!sign_value_1 && sign_value_2) { // второе число отрицательное
        add_uint192(value_1_192, value_2_192, &result_192);
    } else if (!sign_value_1 && !sign_value_2) { // оба числа положительные
        if (gt_uint192(value_2_192, value_1_192)) { // если value_2 > value_1
        sub_uint192(value_2_192, value_1_192, &result_192);
        set_sign(result, 1);
        } else {
            sub_uint192(value_1_192, value_2_192, &result_192);
        }
    }

    int scale = get_scale(value_1);
    int result_function = round_result(result_192, result, &scale); // удаление переполнениия из значения
    set_scale(result, scale);
    int op_status = result_function && get_sign(*result) ? DEC_SMALL : result_function;
    if (op_status) set_sign(result, 0);
    return op_status;
}