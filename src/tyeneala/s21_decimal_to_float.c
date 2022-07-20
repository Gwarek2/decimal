#include "dev_decimal.h"

// Функция преобразует значение типа decimal в значение типа float
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int res = 1;
    if (dst != NULL) {
        s21_decimal tmp;
        copy_decimal(&tmp, src);
        *dst = 0;
        int bit = 0;
        long double val = 0;
        for (int i = 0; i < 96; i++) {
            bit = shift_right(&tmp);
            if (bit != 0)
                val += pow(2, i);
        }

        int exp = src.bits[3];
        int sign = (exp >> 31) & 1;
        if (sign == 1)
            exp -= SIGN_MASK;
        exp >>= 16;
        for (int i = 0; i < exp; i++)
            val /= 10;
        *dst = (float)(sign == 0 ? val : -val);
        res = 0;
    }
    return res;
}
