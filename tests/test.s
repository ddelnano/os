section .text
; Export the entry point to the ELF linker or loader.  The conventional
; entry point is "_start". Use "ld -e foo" to override the default.
global _start
extern testsuite

section .text

; linker puts the entry point here:
_start:

; Exit via the kernel:

    call testsuite
    mov al, 1 ; Function 1: exit()
    mov ebx, 0 ; Return code
    int 0x80 ; The only interrupt Linux uses!
