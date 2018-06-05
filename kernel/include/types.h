#ifndef INCLUDE_TYPES_H
#define INCLUDE_TYPES_H

#define NULL ((void *)0)
#define UINT32_MAX 0xffffffff

typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
typedef unsigned int            uint32_t;
typedef unsigned long size_t;

// sys/time.h
struct timeval {
   uint32_t tv_sec;     /* seconds */
   uint32_t tv_usec;    /* microseconds */
};

#endif
