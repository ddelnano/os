#include "types.h"

unsigned int strlen(char *s)
{
    unsigned int len = 0;
    while (s[len] != '\0') {
        len++;
    }

    return len;
}

extern uint32_t end;
uint32_t placement_address = (uint32_t) &end;

uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys)
{
    if (placement_address & 0xFFFFF000) // If the address is not already page-aligned
    {
        // Align it.
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    if (phys)
    {
        *phys = placement_address;
    }
    uint32_t tmp = placement_address;
    placement_address += sz;
    return tmp;
}

uint32_t kmalloc_p(uint32_t sz, uint32_t *phys)
{
    *phys = placement_address;
    uint32_t tmp = placement_address;
    placement_address += sz;
    return tmp;
}

uint32_t kmalloc_a(uint32_t sz)
{
    if (placement_address & 0xFFFFF000) // If the address is not already page-aligned
    {
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;

    }
    uint32_t tmp = placement_address;
    placement_address += sz;
    return tmp;
}

uint32_t kmalloc(uint32_t sz)
{
    uint32_t tmp = placement_address;
    placement_address += sz;
    return tmp;
}
