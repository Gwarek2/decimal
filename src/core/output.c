#include <stdio.h>

#include "decimal_type.h"
#include "binary_level.h"
#include "output.h"

/**
 * Outputs decimal in binary format
**/
void print_bin(s21_decimal value) {
    char bin[130];
    for (size_t i = 0; i < 128; i++) {
        bin[i] = get_bit(value, 127 - i) + '0';
    }
    bin[129] = '\0';
    printf("%s\n", bin);
}

/**
 * Outputs decimal in hex format
**/
void print_hex(s21_decimal value) {
    if (value.bits[2]) {
        printf("%#x", value.bits[2]);
    }

    if (!value.bits[2] && value.bits[1]) {
        printf("%#x", value.bits[1]);
    } else if (value.bits[1]) {
        printf("%08x", value.bits[1]);
    }

    if (!value.bits[2] && !value.bits[1] && value.bits[0]) {
        printf("%#x", value.bits[0]);
    } else if (value.bits[0]) {
        printf("%08x", value.bits[0]);
    } else {
        printf("0x0");
    }

    printf(" %#x\n", value.bits[3]);
}
