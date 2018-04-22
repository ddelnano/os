#ifndef INCLUDE_PAGING_H
#define INCLUDE_PAGING_H

struct page {
    present: 1;  // If present in memory
    rw: 1; // This does not apply when code is running in kernel-mode (unless a flag in CR0 is set
    user: 1;   // If it is a kernel or user space page
    reserved: 2; // Used by the CPU internally and cannot be trampled
    accessed: 1; // Gets set by the CPU
    dirty: 1;
}

#endif
