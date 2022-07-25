#include "compare.h"

// a < b ?
int s21_is_less(s21_decimal a, s21_decimal b) {
    return (compare(a, b) == -1 ? 1 : 0);
}
// a <= b ?
int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
    return (compare(a, b) != 1 ? 1 : 0);
}
// a > b ?
int s21_is_greater(s21_decimal a, s21_decimal b) {
    return (compare(a, b) == 1 ? 1 : 0);
}
// a >= b ?
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
    return (compare(a, b) != -1 ? 1 : 0);
}
// a == b ?
int s21_is_equal(s21_decimal a, s21_decimal b) {
    return (compare(a, b) == 0 ? 1 : 0);
}
// a != b ?
int s21_is_not_equal(s21_decimal a, s21_decimal b) {
    return (compare(a, b) != 0 ? 1 : 0);
}

/* The function compares two decimal values and returns:
    0 (a == b), 1 (a > b), -1 (b > a)
 */
int compare(const s21_decimal a, const s21_decimal b) {
    int res = (simple_comp(a, b) == 1 ? 0 : 2), inverse = 0;

    while (res == 2) {
        if ((is_mantissa_zero(a) == 1) && (is_mantissa_zero(b) == 1)) {
            res = 0;
            break;
        }

        int exp_a, sign_a = get_atr(a, &exp_a);
        int exp_b, sign_b = get_atr(b, &exp_b);
        if (sign_a != sign_b) {
            res = (sign_b > sign_a ? 1 : -1);
            break;
        }

        inverse = (sign_a == 1 ? 1 : 0);
        int dif = exp_a - exp_b;
        if (dif == 0) {
            res = bin_comp(a, b);
            break;
        }

        s21_decimal tmp;
        if (dif < 0)
            memcpy(&tmp, &a, sizeof(s21_decimal));
        else
            memcpy(&tmp, &b, sizeof(s21_decimal));
        for (int i = 0; i < abs(dif); i++) {
            s21_decimal buf;
            int owerflow = base_multiply(tmp, DEC_TEN, &tmp, &buf);
            if (owerflow != 0) {
                res = (dif < 0 ? 1 : -1);
                break;
            }
        }
        if (res != 2)
            break;

        if (dif < 0)
            res = bin_comp(tmp, b);
        else
            res = bin_comp(a, tmp);
    }
    res = (inverse == 1 ? res * -1 : res);
    return res;
}

// Simple buffer comparison: 1 - match; 0 - none
int simple_comp(const s21_decimal a, const s21_decimal b) {
    int res = 0;
    if ((a.bits[0] == b.bits[0]) &&
        (a.bits[1] == b.bits[1]) &&
        (a.bits[2] == b.bits[2]) &&
        (a.bits[3] == b.bits[3]))
        res = 1;
    return res;
}

/*  The function compares the binary value in the buffers bits[0 - 2] and returns:
    0 (a == b), 1 (a > b), -1 (b > a)
 */
int bin_comp(const s21_decimal a, const s21_decimal b) {
    int res = 0;
    for (int i = 95; i >=0; i--) {
        int bit_1 = (a.bits[i / 32] >> (i % 32)) & 1;
        int bit_2 = (b.bits[i / 32] >> (i % 32)) & 1;
        if (bit_1 != bit_2) {
            res = (bit_1 == 1 ? 1 : -1);
            break;
        }
    }
    return res;
}
