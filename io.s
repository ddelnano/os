global outb
global inb
global print

section .data
msg db  'Hello, world! asdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfsssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss',0xa ;our dear string
len equ $ - msg         ;length of our dear string

outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret

inb:
    mov dx, [esp + 4]
    in al, dx
    ret

; to be used in qemu in user mode only!
; This OS does not have support for a write syscall
; at the moment!
print:
    mov edx, [esp + 8]
    mov ecx, [esp + 4]
    mov ebx,1   ;file descriptor (stdout)
    mov eax,4   ;system call number (sys_write)
    int 0x80    ;call kernel
    ret
