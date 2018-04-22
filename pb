root@588ee8029718:/opt/littleosbook# objdump -h kernel.elf

kernel.elf:     file format elf32-i386

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         0000014b  00100000  00100000  00001000  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .rodata       00000006  00101000  00101000  00002000  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  2 .eh_frame     000000b8  00101008  00101008  00002008  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  3 .text:        0000000c  001010c0  001010c0  000020c0  2**2

  4 .bss:         0000100c  001010cc  001010cc  000020cc  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  5 .data         00000004  00103000  00103000  00004000  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  6 .debug_info   00000181  00000000  00000000  00004004  2**0
                  CONTENTS, READONLY, DEBUGGING
  7 .debug_abbrev 0000011b  00000000  00000000  00004185  2**0
                  CONTENTS, READONLY, DEBUGGING
  8 .debug_aranges 00000040  00000000  00000000  000042a0  2**0
                  CONTENTS, READONLY, DEBUGGING
  9 .debug_line   000000a2  00000000  00000000  000042e0  2**0
                  CONTENTS, READONLY, DEBUGGING
 10 .debug_str    000000e3  00000000  00000000  00004382  2**0
                  CONTENTS, READONLY, DEBUGGING
 11 .comment      00000034  00000000  00000000  00004465  2**0
                  CONTENTS, READONLY
 12 .debug_pubnames 00000012  00000000  00000000  00004499  2**0
                  CONTENTS, READONLY, DEBUGGING
 13 .debug_frame  00000004  00000000  00000000  000044b0  2**3
                  CONTENTS, READONLY, DEBUGGING
 14 .debug_loc    00000010  00000000  00000000  000044b4  2**0
                  CONTENTS, READONLY, DEBUGGING
root@588ee8029718:/opt/littleosbook# objdump -h kernel.elf

kernel.elf:     file format elf32-i386

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         0000014b  00100000  00100000  00001000  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .eh_frame     000000b8  0010014c  0010014c  0000114c  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  2 .text:        0000000c  00100204  00100204  00001204  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  3 .bss:         0000100c  00100210  00100210  00001210  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .debug_info   00000165  00000000  00000000  0000221c  2**0
                  CONTENTS, READONLY, DEBUGGING
  5 .debug_abbrev 00000103  00000000  00000000  00002381  2**0
                  CONTENTS, READONLY, DEBUGGING
  6 .debug_aranges 00000040  00000000  00000000  00002484  2**0
                  CONTENTS, READONLY, DEBUGGING
  7 .debug_line   000000a2  00000000  00000000  000024c4  2**0
                  CONTENTS, READONLY, DEBUGGING
  8 .debug_str    000000de  00000000  00000000  00002566  2**0
                  CONTENTS, READONLY, DEBUGGING
  9 .comment      00000034  00000000  00000000  00002644  2**0
                  CONTENTS, READONLY
 10 .debug_pubnames 00000012  00000000  00000000  00002678  2**0
                  CONTENTS, READONLY, DEBUGGING
 11 .debug_frame  00000004  00000000  00000000  00002690  2**3
                  CONTENTS, READONLY, DEBUGGING
 12 .debug_loc    00000010  00000000  00000000  00002694  2**0
                  CONTENTS, READONLY, DEBUGGING

