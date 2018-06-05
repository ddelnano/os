#include "libc.h"
#include "serial.h"

void * memcpy(void * dest, const void * src, size_t n)
{
    asm volatile("cld; rep movsb"
                : "=c"((int){0})
                : "D"(dest), "S"(src), "c"(n)
                : "flags", "memory");
    return dest;
}

unsigned int strlen(const char *s)
{
    unsigned int len = 0;
    while (s[len] != '\0') {
        len++;
    }

    return len;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
size_t vasprintf(char * buf, size_t size, char * fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char *c = buf;
    char *s;
    // Walk string until we reach a null byte
    for (char *f = fmt; *f; f++) {
        if (size < 1) {
            // We have reached end of our buffer
            return 1;
        }
        if (*f != '%') {
            *c++ = *f;
            size--;
            continue;
        }

        // TODO: Add argument width
        ++f;
        uint32_t test = 0;
        switch (*f) {
            case 's':
                s = va_arg(args, char *);
                while (*s) {
                    if (size < 1) return 1;
                    *c++ = *s++;
                    size--;
                }
                break;
            case '%':
                *c++ = '%';
                break;
            case 'd':
                test = va_arg(args, uint32_t); 
                uint32_t i = 9;
                // How many digits the number is
                uint32_t num_width = 1;
                while (test > i && i < UINT32_MAX) {
                    i *= 10;
                    i += 9;
                    num_width++;
                }
                // TODO: Nasty hack but I can't figure out
                // why numbers near UINT32_MAX end up with
                // a width of 12 at the moment.
                if (num_width == 12) num_width = 10;

                c += num_width - 1;
                char *start_pos = c + 1;
                while (num_width > 0) {
                    unsigned int value = test / 10;
                    unsigned int digit = test % 10;
                    *c-- = digit + '0';
                    test = value;
                    num_width--;
                }
                c = start_pos;
                break;
        }
        size--;
    }
    va_end(args);
    return 0;
}
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop

/* void dec_to_str(char * buf, unsigned int value, unsigned int width) */
/* { */
/*     unsigned int num_width = 1; */
/*     unsigned int n = 9; */
/*     while (value > 9 && value < UINT32_MAX) { */
/*         n *= 10; */
/*         n += 9; */
/*         num_width++; */
/*     } */

/*     while (num_width > 0) { */
/*         unsigned int next_divisor = value / 10; */
/*         unsigned int remainder = value % 10; */
/*         buf[num_width] = remainder + '0'; */
/*         num_width--; */
/*         value = next_divisor; */
/*     } */
/* } */

int strcmp(const char * l, const char * r) {
	for (; *l == *r && *l; l++, r++);
	return *(unsigned char *)l - *(unsigned char *)r;
}
