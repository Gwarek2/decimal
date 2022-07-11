#include <limits.h>

#include "binary_level.h"
#include "decimal_level.h"

static const s21_decimal DEC_INT_MAX = {{INT_MAX, 0, 0, 0}};
static const s21_decimal DEC_INT_MIN = {{INT_MIN, 0, 0, 1}};

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    if (dst == NULL) return 1;
    s21_decimal rem, int_part;
    int status = 0;
    unsigned neg = get_sign(src);
    base_divide(src, ten_power[get_scale(src)], &int_part, &rem);
    if ((neg && (bits_lt(int_part, DEC_INT_MIN) || bits_eq(int_part, DEC_INT_MIN))) ||
        (bits_lt(int_part, DEC_INT_MAX) || bits_eq(int_part, DEC_INT_MAX))) {
        if (neg && int_part.bits[0] != (unsigned) INT_MIN) *dst = -int_part.bits[0];
        else if (neg) status = 1;
        else *dst = int_part.bits[0];
    } else {
        status = 1;
    }
    return status;
}

