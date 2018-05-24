#include "io.h"
#include "fb.h"
#include "serial.h"
#include "gdt.h"
#include "idt.h"
#include "libc.h"
#include "timer.h"
#include "cmos.h"

/* The C function */
int sum_of_three(int arg1, int arg2, int arg3)
{
    return arg1 + arg2 + arg3;
}

void fb_write_cell()
{
    char *fb = (char *) 0x000B8000;
    fb[0] = 'A';
    fb[1] = 0x28;
    fb[2] = 'B';
    fb[3] = 0xf0;
    fb[4] = 0x43;
    fb[5] = 0xf0;
}

int main()
{
    /* for (int i = 0; i < 401; i++) { */
    /*     fb_write(text, len); */
    /* } */

    serial_init();
    serial_write("Booting the OS\n");
    gdt_init();
    idt_init();
    asm volatile("sti");
    timer_init(1000); // Initialise timer to 50Hz
    serial_write("Hello\n");
    /* asm volatile ("int $0x1"); */
    /* asm volatile ("int $0x2"); */
    struct timeval tv;
    gettimeofday(&tv, NULL);
    char buf[100];
    /* vasprintf(buf, sizeof buf / sizeof(buf[0]), "This number is\n"); */
    /* serial_write(buf); */
    /* /1* vasprintf(buf, "The next number is %d\n", 150); *1/ */
    /* /1* serial_write(buf); *1/ */
    /* vasprintf(buf, sizeof buf / sizeof(buf[0]), "The next number %s\n", "testasdfasdfds"); */
    /* serial_write(buf); */
    vasprintf(buf, sizeof buf / sizeof(buf[0]), "Current %d  time is: %d  \n", 2500, 150);
    serial_write(buf);
    return 0;
}

