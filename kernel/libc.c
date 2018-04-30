#include "types.h"

void * memcpy(void * dest, void * src, size_t n)
{
    asm volatile("cld; rep movsb"
                : "=c"((int){0})
                : "D"(dest), "S"(src), "c"(n)
                : "flags", "memory");
    return dest;
}

unsigned int strlen(char *s)
{
    unsigned int len = 0;
    while (s[len] != '\0') {
        len++;
    }

    return len;
}
