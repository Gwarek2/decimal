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
    printf("%#10X %#10X %#10X    %#10X\n", value.bits[2], value.bits[1], value.bits[0], value.bits[3]);
}
