CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	 -nostartfiles -nodefaultlibs -Wall -Wextra -c -ggdb \
	 -I kernel/include
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf -Fdwarf -g

DOCKER_IMAGE := littleosbook

KERNEL_OBJS = $(patsubst %.c,%.o,$(wildcard kernel/*.c))
KERNEL_OBJS += $(patsubst %.s,%.o,$(wildcard *.s))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard *.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard kernel/devices/*.c))
TEST_OBJS = $(patsubst %.c,%.o,$(wildcard tests/*.c))
TEST_OBJS += $(patsubst %.s,%.o,$(wildcard tests/*.s))

all: os.iso

os.iso: kernel.elf
	mkdir -p img/boot/grub
	cp kernel.elf img/boot/
	cp grub.cfg img/boot/grub/
	grub-mkrescue -o os.iso img

kernel.elf: $(KERNEL_OBJS)
	mkdir -p img/boot
	ld $(LDFLAGS) $(KERNEL_OBJS) -o kernel.elf
	grub-file --is-x86-multiboot kernel.elf

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf **.o img os.iso

test: $(TEST_OBJS) $(KERNEL_OBJS)
	ld -melf_i386 $(KERNEL_OBJS) $(TEST_OBJS) -o tests/test.elf
	qemu-i386-static tests/test.elf | tappy


