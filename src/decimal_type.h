#ifndef _DECIMAL_TYPE_H
#define _DECIMAL_TYPE_H

#include <stddef.h>
#include <stdint.h>

enum op_status {
    DEC_OK,
    DEC_HUGE,
    DEC_SMALL,
    DEC_DIV_BY_ZERO
};

typedef struct {
    unsigned bits[4];
} s21_decimal;


#endif  // _DECIMAL_TYPE_H
