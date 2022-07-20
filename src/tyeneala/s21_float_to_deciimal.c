#include "dev_decimal.h"

// Функция преобразует значение типа float в значение типа decimal
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    ini_zero(dst);
    char str[33] = {0};
    int exp = 0, sign = 0;
    int res = float_to_str(str, src, &sign, &exp);

    if ((res == 0) && (src != 0)) {
        int i = 0;
        dst->bits[0] = str[i++] - 48;
        for (; i < 30; i++) {
            if (str[i] == '.')
                continue;
            uint64_t b0 = dst->bits[0];
            b0 = (b0 << 1) + (b0 << 3) + (str[i] - 48);
            uint64_t b1 = dst->bits[1];
            b1 = (b1 << 1) + (b1 << 3) + (b0 >> 32);
            uint64_t b2 = dst->bits[2];
            b2 = (b2 << 1) + (b2 << 3) + (b1 >> 32);
            if ((b2 >> 32) > 0) {
                res = 1;
                ini_zero(dst);
                break;
            }
            dst->bits[0] = (unsigned int)b0;
            dst->bits[1] = (unsigned int)b1;
            dst->bits[2] = (unsigned int)b2;
        }
        add_atr(dst, sign, 28 - exp);
    }
    return (res == 0 ? 0 : 1);
}

/* Функция преобразует значение типа float в str с проверкой float и возвращает:
0 - ошибок нет, 1 - значение меньше 1e-28, 2 - значение типа +/-inf, 3 - не число
 */
int float_to_str(char *str, float val, int *sign, int *exp) {
    int res = 0;
    float zero = 0.0;
    if (val != val) {
        res = 3;
    } else if ((val >= 1.0 / zero) || (val <= -1.0 / zero)) {
        res = 2;
    } else if (fabs(val) < 1e-28) {
        res = 1;
    }

    if (res == 0) {
        float tmp = val;
        if (val < 0) {
            *sign = 1;
            tmp = -tmp;
        }
        while (tmp > 10) {
            tmp /= 10;
            *exp += 1;
        }
        sprintf(str, "%30.*f", (29 - *exp), fabs(val));
    }
    return res;
}
