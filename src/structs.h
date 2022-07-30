#ifndef _STRUCTS_H
#define _STRUCTS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum arithmetics_status {
    DEC_OK,
    DEC_HUGE,
    DEC_SMALL,
    DEC_DIV_BY_ZERO
};

typedef struct {
    uint32_t bits[4];
} s21_decimal;

typedef struct {
    uint32_t bits[6];
} uint192;


#endif  // _STRUCTS_H
