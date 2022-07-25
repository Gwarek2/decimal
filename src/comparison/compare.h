#ifndef _COMPARE_H
#define _COMPARE_H

#include "s21_decimal.h"
#include "common.h"
#include "decimal_level.h"
//#include "decimal_type.h"
#include <stdlib.h>

int compare(const s21_decimal a, const s21_decimal b);
int simple_comp(const s21_decimal a, const s21_decimal b);
int bin_comp(const s21_decimal a, const s21_decimal b);

#endif  // _COMPARE_H
