#include "dev_decimal.h"

// ***************** decimal_to_float *****************

// Функция копирует значение типа decimal
void copy_decimal(s21_decimal *dst, s21_decimal src) {
    for (int i = 0; i < 4; i++)
        dst->bits[i] = src.bits[i];
}

// Функция возвращает младший бит и смещает значения в буферах вправо
int shift_right(s21_decimal *src) {
    int bit = 0;
    for (int i = 2; i >= 0; i--) {
        int tmp_bit = src->bits[i] & 1;
        src->bits[i] >>= 1;
        if ((i != 2) && (bit != 0))
            src->bits[i] = src->bits[i] | (1u << 31);
        bit = tmp_bit;
    }
    return bit;
}

// ***************** float_to_decimal *****************

// Функция записывает знак и мантису в s21_decimal
void add_atr(s21_decimal *dst, int sign, int exp) {
    dst->bits[3] = exp << 16;
    if (sign == 1)
        dst->bits[3] += SIGN_MASK;
}

// Функция инициализирует decimal нулевыми значениями
void ini_zero(s21_decimal *dst) {
    dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
}
