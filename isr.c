#include "isr.h"
#include "io.h"
#include "pic.h"
#include "libc.h"
#include "serial.h"

isr_t interrupt_handlers[256];

// This gets called from our ASM interrupt handler stub.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void isr_handler(registers_t registers)
{
    serial_write("A");
}
#pragma GCC diagnostic pop

void register_interrupt_handler(uint8_t n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

// This gets called from our ASM interrupt handler stub.
void irq_handler(registers_t regs)
{
    /* serial_write("Received interrupt"); */
   // Send an EOI (end of interrupt) signal to the PICs.
   // If this interrupt involved the slave.
   if (regs.int_no >= 40)
   {
       // Send reset signal to slave.
       outb(PIC2_COMM, 0x20);
   }
   // Send reset signal to master. (As well as slave, if necessary).
   outb(PIC1_COMM, 0x20);

   if (interrupt_handlers[regs.int_no] != 0)
   {
       isr_t handler = interrupt_handlers[regs.int_no];
       handler(regs);
   }
}
