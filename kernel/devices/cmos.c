#include "cmos.h"
#include "io.h"
#include "serial.h"
#include "libc.h"

#define CMOS_ADDR 0x70
#define CMOS_DATA 0x71

uint32_t boot_time = 0;

int update_in_progress()
{
    outb(CMOS_ADDR, 0xa);
    return inb(CMOS_DATA) & 0x80;
}

void cmos_dump(uint16_t *values)
{
    for (int i = 0; i < 10; i++) {
        outb(CMOS_ADDR, i);
        values[i] = inb(CMOS_DATA);
    }
}

uint32_t read_cmos()
{
    uint16_t values[10];
    uint16_t old_values[10];

    while (update_in_progress()) {
    }

    cmos_dump(values);
    memcpy(values, old_values, 10);
    return 0;
}
