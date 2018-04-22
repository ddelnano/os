#include "io.h"
#include "util.h"
#include "fb.h"
#include "serial.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"

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

char text[] = "Hello";
void hello()
{
    unsigned int len = strlen(text);
    /* for (int i = 0; i < 401; i++) { */
    /*     fb_write(text, len); */
    /* } */

    serial_init();
    gdt_init();
    idt_init();
    asm volatile("sti");
    timer_init(50); // Initialise timer to 50Hz
    serial_write(text, len);
    /* asm volatile ("int $0x1"); */
    /* asm volatile ("int $0x2"); */
}

