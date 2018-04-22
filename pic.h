#ifndef INCLUDE_PIC_H
#define INCLUDE_PIC_H

#define PIC1_COMM 0x20
#define PIC1_DATA (PIC1_COMM+1)

#define PIC2_COMM 0xa0
#define PIC2_DATA (PIC2_COMM+1)

void pic_init();

#endif
