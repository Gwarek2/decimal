#ifndef DEV_DECIMAL_H
#define DEV_DECIMAL_H

#define SIGN_MASK -2147483648 // 0x80000000

typedef struct {
    int bits[4];
} s21_decimal;

// out_decimal.c
void out_decimal(s21_decimal dst);
void ini_arr(char *str);
int zero_shift(const char *str);
int add_degree(char *str, int d);


#endif // DEV_DECIMAL_H
