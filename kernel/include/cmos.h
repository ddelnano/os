#ifndef INCLUDE_CMOS_H
#define INCLUDE_CMOS_H

#include "types.h"

uint32_t read_cmos();
uint32_t secs_of_years(int years);
uint32_t secs_of_month(int months, int year);
int gettimeofday(struct timeval *tv, void *tz);

#endif
