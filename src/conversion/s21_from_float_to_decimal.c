#include "uint96.h"
#include <math.h>
#include <stdio.h>

#define DEC_EPS 1e-28

int float_to_str(char *str, float val, int *sign, int *scale);

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    init_default(dst);
    char str[33] = {0};
    int scale = 0, sign = 0;
    int status = float_to_str(str, src, &sign, &scale);

    if (status == 0) {
        int i = 0;
        dst->bits[0] = str[i++] - 48;
        int overflow = 0;
        for (; i < 30 && !overflow; i++) {
            if (str[i] == '.')
                continue;
            s21_decimal ov, digit = {{str[i] - 48}};
            overflow = base_multiply(*dst, DEC_TEN, dst, &ov) ||
                           base_addition(*dst, digit, dst);
        }
        if (!overflow) {
            set_scale(dst, 28 - scale);
            set_sign(dst, sign);
        } else {
            init_default(dst);
            status = 1;
        }
    }
    return status;
}

int float_to_str(char *str, float val, int *sign, int *scale) {
    if (isnan(val) || isinf(val) || fabs(val) < DEC_EPS) {
        return 1;
    }

    float tmp = val;
    if (val < 0) {
        *sign = 1;
        tmp = -tmp;
    }
    while (tmp > 10) {
        tmp /= 10;
        (*scale)++;
    }
    snprintf(str, sizeof(char) * 32, "%30.*f", (29 - *scale), fabs(val));
    return 0;
}
