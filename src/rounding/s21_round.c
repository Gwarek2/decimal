#include "uint96.h"

int s21_round(s21_decimal value, s21_decimal *result) {
    init_default(result);

    s21_decimal res = value;
    int sign = get_sign(value);
    int scale = get_scale(value);
    while (scale) {
        s21_decimal first_digit;
        base_divide(res, DEC_TEN, &res, &first_digit);
        if (gt(first_digit, DEC_FIVE) || eq(first_digit, DEC_FIVE)) {
            base_addition(res, DEC_ONE, &res);
        }
        scale--;
    }
    set_sign(&res, sign);
    set_scale(&res, 0);
    *result = res;
    return 0;
}
