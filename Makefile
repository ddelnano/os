OBJECTS = kmain.o loader.o io.o fb.o serial.o gdt.o descriptor_tables.o idt.o isr.o util.o pic.o timer.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	 -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -ggdb
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf -Fdwarf -g

DOCKER_IMAGE := littleosbook

all: os.iso

os.iso: kernel.elf
	mkdir -p img/boot/grub
	cp kernel.elf img/boot/
	cp grub.cfg img/boot/grub/
	grub-mkrescue -o os.iso img

kernel.elf: $(OBJECTS)
	mkdir -p img/boot
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf
	grub-file --is-x86-multiboot kernel.elf

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o img os.iso
