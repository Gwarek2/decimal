#include "common.h"
#include "binary_level.h"

// Функция преобразует значение типа decimal в значение типа float
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int res = 1;
    if (dst != NULL) {
        s21_decimal tmp;
        copy_full(&tmp, &src);
        *dst = 0;
        long double val = 0;
        for (int i = 0; i < 96; i++) {
            int bit = reduction(&tmp);
            if (bit != 0)
                val += pow(2, i);
        }

        int exp = src.bits[3];
        int sign = (exp >> SIGN_SHIFT) & 1;
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