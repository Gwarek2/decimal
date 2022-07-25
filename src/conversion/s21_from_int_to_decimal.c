#include <limits.h>

#include "common.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    init_default(dst);
    unsigned mantiss[3] = {0};
    unsigned neg = src < 0;
    if (neg && src != INT_MIN)
        mantiss[0] = -src;
    else
        mantiss[0] = src;
    init_value(dst, mantiss, neg, 0);
    return 0;
}
