#ifndef _DECIMAL_TYPE_H
#define _DECIMAL_TYPE_H

#include <stdint.h>

enum op_status {
    DEC_OK,
    DEC_HUGE,
    DEC_SMALL,
    DEC_DIV_BY_ZERO
};

typedef union {
    unsigned bits[4];
    uint32_t bits_u32_t[4];
    uint64_t bits_u64_t[2];
} s21_decimal;


#endif
