#ifndef INCLUDE_CMOS_H
#define INCLUDE_CMOS_H

#include "types.h"

uint32_t read_cmos();
uint32_t secs_of_years(int years);
uint32_t secs_of_month(int months, int year);
int gettimeofday(struct timeval *tv, void *tz);
uint32_t get_timestamp_from_cmos_registers(
    uint32_t secs,
    uint32_t mins,
    uint32_t hours,
    uint32_t days,
    uint32_t months,
    uint32_t years
);

#endif
