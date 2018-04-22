global gdt_flush
global idt_flush
extern isr_handler
extern irq_handler

%macro ISR_NO_ERRNO 1
global isr%1
isr%1:
  cli                 ; Disable interrupts
  push byte 0         ; Push a dummy error code (if ISR0 doesn't push it's own error code)
  push byte %1        ; Push the interrupt number (0)
  jmp isr_common_stub ; Go to our common handler.
%endmacro

; The specific CPU interrupts that put an error code
; on the stack are 8, 10, 11, 12, 13, 14 and 17.
; This macro should be used for those interrupts.
%macro ISR_ERRNO 1
global isr%1
isr%1:
  cli                 ; Disable interrupts
  push byte %1        ; Push the interrupt number (0)
  jmp isr_common_stub ; Go to our common handler.
%endmacro

; This macro creates a stub for an IRQ - the first parameter is
; the IRQ number, the second is the ISR number it is remapped to.
%macro IRQ 2
  global irq%1
  irq%1:
    cli
    push byte 0
    push byte %2
    jmp irq_common_stub
%endmacro

gdt_flush:
   mov eax, [esp+4]  ; Get the pointer to the GDT, passed as a parameter.
   lgdt [eax]        ; Load the new GDT pointer

   mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
   mov ds, ax        ; Load all data segment selectors
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov ss, ax
   jmp 0x08:.flush   ; 0x08 is the offset to our code segment: Far jump!
.flush:
    ret

idt_flush:
   mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter.
   lidt [eax]
   ret

ISR_NO_ERRNO 0
ISR_NO_ERRNO 1
ISR_NO_ERRNO 2
ISR_NO_ERRNO 3
ISR_NO_ERRNO 4
ISR_NO_ERRNO 5
ISR_NO_ERRNO 6
ISR_NO_ERRNO 7
ISR_ERRNO 8
ISR_NO_ERRNO 9
ISR_ERRNO 10
ISR_ERRNO 11
ISR_ERRNO 12
ISR_ERRNO 13
ISR_ERRNO 14
ISR_NO_ERRNO 15
ISR_NO_ERRNO 16
ISR_ERRNO 17
ISR_NO_ERRNO 18
ISR_NO_ERRNO 19
ISR_NO_ERRNO 20
ISR_NO_ERRNO 21
ISR_NO_ERRNO 22
ISR_NO_ERRNO 23
ISR_NO_ERRNO 24
ISR_NO_ERRNO 25
ISR_NO_ERRNO 26
ISR_NO_ERRNO 27
ISR_NO_ERRNO 28
ISR_NO_ERRNO 29
ISR_NO_ERRNO 30
ISR_NO_ERRNO 31

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
isr_common_stub:
   pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov ax, ds               ; Lower 16-bits of eax = ds.
   push eax                 ; save the data segment descriptor

   mov ax, 0x10  ; load the kernel data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   call isr_handler

   pop eax        ; reload the original data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   popa                     ; Pops edi,esi,ebp...
   add esp, 8     ; Cleans up the pushed error code and pushed ISR number
   sti
   iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

; This is our common IRQ stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame. 
irq_common_stub:
   pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov ax, ds               ; Lower 16-bits of eax = ds.
   push eax                 ; save the data segment descriptor

   mov ax, 0x10  ; load the kernel data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   call irq_handler

   pop ebx        ; reload the original data segment descriptor
   mov ds, bx
   mov es, bx
   mov fs, bx
   mov gs, bx

   popa                     ; Pops edi,esi,ebp...
   add esp, 8     ; Cleans up the pushed error code and pushed ISR number
   sti
   iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
