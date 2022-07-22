#include "binary_level.h"
#include "common.h"
#include "decimal_level.h"

int s21_round(s21_decimal value, s21_decimal *result) {
    if (result == NULL) return 1;

    int sign = get_sign(value);
    int scale = get_scale(value);
    *result = value;
    while (scale) {
        s21_decimal first_digit;
        base_divide(*result, DEC_TEN, result, &first_digit);
        if (bits_gt(first_digit, DEC_FIVE) || bits_eq(first_digit, DEC_FIVE)) {
            base_addition(*result, DEC_ONE, result);
        }
        scale--;
    }
    set_sign(result, sign);
    set_scale(result, 0);
    return 0;
}
