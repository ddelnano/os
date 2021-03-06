#include "gdt.h"

// TODO: Play around with finding this in memory
gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;

extern void gdt_flush(uint32_t gdt);

// Set the value of one GDT entry.
static void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_entries[num].base_low = (base & 0xffff);
    gdt_entries[num].base_middle = (base >> 16 & 0xff);
    gdt_entries[num].base_high = (base >> 24 & 0xff);

    gdt_entries[num].limit_low = (limit & 0xffff);

    gdt_entries[num].granularity = (limit >> 16 & 0x0f);
    gdt_entries[num].granularity |= gran & 0xf0;

    gdt_entries[num].access = access;
}

void gdt_init()
{
   gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
   gdt_ptr.base  = (uint32_t)&gdt_entries;

   gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
   gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
   gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
   gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
   gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

   gdt_flush((uint32_t)&gdt_ptr);
}

