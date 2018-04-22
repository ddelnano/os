#include "descriptor_tables.h"
#include "types.h"

#ifndef INCLUDE_GDT_H
#define INCLUDE_GDT_H

// This structure contains the value of one GDT entry.
// We use the attribute 'packed' to tell GCC not to change
// any of the alignment in the structure.
struct gdt_entry_struct
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

typedef struct gdt_ptr_struct gdt_ptr_t;

// Lets us access our ASM functions from our C code.
/* extern void gdt_flush(u32int); */

void gdt_init();

#endif /* INCLUDE_GDT_H */
