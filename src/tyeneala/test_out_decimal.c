#include "dev_decimal.h"

int main() {
    s21_decimal dst;
    dst.bits[0] = -2147483648;
    dst.bits[1] = 123;
    dst.bits[2] = 123;
    dst.bits[3] = 0; // 458752, -2147024896, 0
    
    out_decimal(dst);
    
    return 0;
}
