#include "timer.h"
#include "isr.h"
#include "io.h"
#include "serial.h"
#include "util.h"

uint32_t tick = 0;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
static void timer_callback(registers_t reg)
{
    tick++;
    char tick_str[] = "Tick: ";
    serial_write(tick_str, strlen(tick_str));
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
}
