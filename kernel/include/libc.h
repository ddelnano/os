#include "types.h"
#include "va_list.h"

void * memcpy(void * dest, const void * src, size_t n);

unsigned int strlen(const char *s);
size_t vasprintf(char * buf, size_t size, char * fmt, ...);

int strcmp(const char * l, const char * r);
