#include "timer.h"
#include "isr.h"
#include "io.h"
#include "serial.h"
#include "cmos.h"
#include "libc.h"
#include "system.h"

#define SUBTICKS_PER_TICK 1000
#define RESYNC_TIME 1

static int behind = 0;

/*
 * Internal timer counters
 */
unsigned long timer_ticks = 0;
unsigned long timer_subticks = 0;
signed long timer_drift = 0;
signed long _timer_drift = 0;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
// This algorithm was taken from toaruos https://gitlab.com/toaruos/toaruos
static void timer_callback(registers_t reg)
{
    if (++timer_subticks == SUBTICKS_PER_TICK || (behind && ++timer_subticks == SUBTICKS_PER_TICK)) {
        timer_ticks++;
        timer_subticks = 0;
        if (timer_ticks % RESYNC_TIME == 0) {
            uint32_t new_time = read_cmos();
            _timer_drift = new_time - boot_time - timer_ticks;
            if (_timer_drift > 0) behind = 1;
            else behind = 0;
        }
    }
}
#pragma GCC diagnostic pop

void timer_init(uint32_t freq)
{
    register_interrupt_handler(IRQ0, &timer_callback);

    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    uint32_t divisor = 1193180 / freq;

    // Send the command byte.
    outb(0x43, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    uint8_t l = (uint8_t)(divisor & 0xFF);
    uint8_t h = (uint8_t)( (divisor>>8) & 0xFF );

    // Send the frequency divisor.
    outb(0x40, l);
    outb(0x40, h);

    boot_time = read_cmos();
}

