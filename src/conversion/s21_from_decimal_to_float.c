#include "binary_level.h"
#include "common.h"
#include "decimal_level.h"

// Функция преобразует значение типа decimal в значение типа float
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int res = 0;
    if (is_zero(src) == 0) {
        s21_decimal tmp;
        copy_full(&tmp, &src);
        long double val = 0;
        for (int i = 0; i < 96; i++) {
            int bit = right_shift(&tmp);
            if (bit != 0)
                val += pow(2, i);
        }
        int exp, sign = get_atr(src, &exp);
        for (int i = 0; i < exp; i++)
            val /= 10;
        *dst = (float)(sign == 0 ? val : -val);
    } else {
        *dst = 0;
    }
    return res;
}
