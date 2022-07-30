#include "uint96.h"

int base_comp(const s21_decimal a, const s21_decimal b);

int s21_is_less(s21_decimal a, s21_decimal b) {
    return base_comp(a, b) == LT;
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
    return base_comp(a, b) != GT;
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
    return base_comp(a, b) == GT;
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
    return base_comp(a, b) != LT;
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
    return base_comp(a, b) == EQ;
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
    return base_comp(a, b) != EQ;
}

/****************************************************
 * The function equalizes scales and compares results
 ***************************************************/
int base_comp(const s21_decimal a, const s21_decimal b) {
    if (is_zero(a) && is_zero(b)) {
        return EQ;
    }

    int sign1 = get_sign(a), sign2 = get_sign(b);
    if (!sign1 && sign2) {
        return GT;
    } else if (sign1 && !sign2) {
        return LT;
    }

    s21_decimal value1 = a, value2 = b, overflow;
    int scale_diff = get_scale(value1) - get_scale(value2);
    equalize_scales(&value1, &value2, &overflow);
    if (!is_zero(overflow) && scale_diff < 0) {
        return GT;
    } else if (!is_zero(overflow) && scale_diff > 0) {
        return LT;
    }

    int result = cmp(value1, value2);
    if (result != EQ && sign1 && sign2) {
        return -result;
    }
    return result;
}
