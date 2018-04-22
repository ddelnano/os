#include "pic.h"
#include "io.h"

#define ICW1_INIT	0x10		/* Initialization - required! */
#define ICW1_ICW4       0x01

void pic_init()
{
    // ICW1
    outb(PIC1_COMM, ICW1_INIT + ICW1_ICW4);
    outb(PIC2_COMM, ICW1_INIT + ICW1_ICW4);

    // Rest of Initialization command words get sent to data port
    // Map PIC1 to interrupts 32 - 39
    outb(PIC1_DATA, 0x20);
    // Map PIC2 to interrupts 40 - 47
    outb(PIC2_DATA, 0x28);

    // ICW3

    // Each bit represents if IR is connected to a slave.  We want to remap IR 2
    // to the slave so we want the third bit to be 1.
    outb(PIC1_DATA, 0x04);
    // Came from Slave ID table in 8259A manual
    outb(PIC2_DATA, 0x02);

    // ICW4
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);

    // Not sure what this is
    outb(PIC1_DATA, 0x0);
    outb(PIC2_DATA, 0x0);

    /* outb(PIC1_DATA, 0xfe); */
    /* outb(PIC2_DATA, 0xff); */
}
