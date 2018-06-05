#include "cmos.h"
#include "system.h"
#include "io.h"
#include "serial.h"
#include "libc.h"

#define CMOS_ADDR 0x70
#define CMOS_DATA 0x71

// When using qemu with the local clock it 
// is timezone dependent.
#define TZ_OFFSET 4

uint32_t boot_time = 0;

// Took this from qemu https://github.com/qemu/qemu/blob/master/tests/rtc-test.c#L24
static int bcd2dec(int value)
{
    return (((value >> 4) & 0x0F) * 10) + (value & 0x0F);
}

uint32_t secs_of_years(int years) {
	uint32_t days = 0;
	years += 2000;
	while (years > 1969) {
		days += 365;
		if (years % 4 == 0) {
			if (years % 100 == 0) {
				if (years % 400 == 0) {
					days++;
				}
			} else {
				days++;
			}
		}
		years--;
	}
	return days * 86400;
}

uint32_t secs_of_month(int months, int year) {
	year += 2000;

	uint32_t days = 0;
	switch(months) {
		case 11:
			days += 30;
		case 10:
			days += 31;
		case 9:
			days += 30;
		case 8:
			days += 31;
		case 7:
			days += 31;
		case 6:
			days += 30;
		case 5:
			days += 31;
		case 4:
			days += 30;
		case 3:
			days += 31;
		case 2:
			days += 28;
			if ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0))) {
				days++;
			}
		case 1:
			days += 31;
		default:
			break;
	}
	return days * 86400;
}

enum {
    CMOS_SECOND = 0x0,
    CMOS_MINUTE = 0x2,
    CMOS_HOUR = 0x4,
    CMOS_DAY_WEEK = 0x6,
    CMOS_DAY_MONTH = 0x7,
    CMOS_MONTH = 0x8,
    CMOS_YEAR = 0x9
};

int update_in_progress()
{
    outb(CMOS_ADDR, 0x0a);
    return inb(CMOS_DATA) & 0x80;
}

void cmos_dump(uint16_t *values)
{
    for (int i = 0; i < 10; i++) {
        outb(CMOS_ADDR, i);
        values[i] = inb(CMOS_DATA);
    }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
// TODO: Change tz to correct pointer

// This also needs to be validated that it works.
// Having issues because I think output buffering is
// causing the logs to appear to be delayed.
int gettimeofday(struct timeval *tv, void *tz)
{
    tv->tv_sec = boot_time + timer_ticks;
    tv->tv_usec = timer_subticks * 1000;
    return 0;
}
#pragma GCC diagnostic pop

uint32_t read_cmos()
{
    uint16_t values[10];
    uint16_t old_values[10];
    while (update_in_progress()) {
        serial_write("updating\n");
    }

    cmos_dump(values);
    // TODO: Stuck in infinite CMOS loop
    do {

        memcpy(old_values, values, 20);
        while (update_in_progress()) {
            serial_write("inner update\n");
        }

        cmos_dump(values);
    } while (
        values[CMOS_SECOND] != old_values[CMOS_SECOND] ||
        values[CMOS_MINUTE] != old_values[CMOS_MINUTE] ||
        values[CMOS_HOUR] != old_values[CMOS_HOUR] ||
        values[CMOS_DAY_WEEK] != old_values[CMOS_DAY_WEEK] ||
        values[CMOS_DAY_MONTH] != old_values[CMOS_DAY_MONTH] ||
        values[CMOS_MONTH] != old_values[CMOS_MONTH] ||
        values[CMOS_YEAR] != old_values[CMOS_YEAR]
    );
    serial_write("done updating cmos\n");
    char buf[1000];
    serial_write(buf);
    uint32_t time = bcd2dec(values[CMOS_SECOND]) +
        bcd2dec(values[CMOS_MINUTE]) * 60 +
        bcd2dec(values[CMOS_HOUR] + TZ_OFFSET) * 60 * 60 +
        (bcd2dec(values[CMOS_DAY_MONTH]) - 1) * 86400 + // 24 * 60 * 60
        secs_of_month(bcd2dec(values[CMOS_MONTH]) - 1,
                bcd2dec(values[CMOS_YEAR])) +
        secs_of_years(bcd2dec(values[CMOS_YEAR]) - 1);

    vasprintf(buf, sizeof(buf)/sizeof(buf[0]), "Booting at seconds: %d  mins: %d  hour: %d  day: %d month: %d  year: %d  unixtime: %d \n", bcd2dec(values[CMOS_SECOND]), bcd2dec(values[CMOS_MINUTE]), bcd2dec(values[CMOS_HOUR]), bcd2dec(values[CMOS_DAY_MONTH]), bcd2dec(values[CMOS_MONTH]), bcd2dec(values[CMOS_YEAR]), time);
    serial_write(buf);

    return time;
}

uint32_t get_timestamp_from_cmos_registers(
    uint32_t secs,
    uint32_t mins,
    uint32_t hours,
    uint32_t days,
    uint32_t months,
    uint32_t years
)
{
    return secs +
        mins * 60 +
        (hours + TZ_OFFSET ) * 60 * 60 +
        (days - 1) * 86400 + // 24 * 60 * 60
        secs_of_month(months - 1, years) +
        secs_of_years(years - 1);
}
