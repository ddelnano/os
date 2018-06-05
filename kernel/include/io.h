#include "types.h"

#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/** outb:
 *  Sends the given data to the given I/O port. Defined in io.s
 *
 *  @param port The I/O port to send the data to
 *  @param data The data to send to the I/O port
 */
void outb(unsigned short port, unsigned char data);

/** inb:
 *  Read a byte from an I/O port.
 *
 *  @param  port The address of the I/O port
 *  @return      The read byte
 */
unsigned char inb(unsigned short port);

/** print:
 *  Used for testing purposes in qemu user mode only!
 *  The OS does not have a 'stdout' just yet, but running
 *  code in qemu user mode means we can use linux syscalls.
 *  This is used for debugging for now.
 *
 *  @param  string you want to print to stdout
 *  @param  length of the string
 *  @return void
 */
void print(char* message, unsigned short len);

#endif /* INCLUDE_IO_H */
