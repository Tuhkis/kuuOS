CC=gcc
AS=as
LD=ld

CFLAGS=-m32 -std=gnu99 -ffreestanding -O3 -Wall -Wextra
OUT=kuuOS
COMP=$(CC) $(CFLAGS) -c

all: kernel.o boot.o vga.o keyboard.o string.o int.o
	ld -m elf_i386 -T linker.ld *.o -o $(OUT).bin -nostdlib
	grub-file --is-x86-multiboot kuuOS.bin
	mkdir -p iso/boot/grub
	cp $(OUT).bin iso/boot/$(OUT).bin
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o $(OUT).iso iso

kernel.o: src/kernel.c src/kernel.h
	$(COMP) src/kernel.c

vga.o: src/vga.c src/vga.h
	$(COMP) src/vga.c

keyboard.o: src/keyboard.c src/keyboard.h
	$(COMP) src/keyboard.c

string.o: src/string.c src/string.h
	$(COMP) src/string.c

int.o: src/int.c src/int.h
	$(COMP) src/int.c

boot.o: src/boot.s
	$(AS) --32 src/boot.s -o boot.o

a20.o: src/a20.s
	$(AS) --32 src/a20.s -o a20.o

run:
	qemu-system-x86_64 -cdrom $(OUT).iso

clean:
	rm *.o
	rm -rf iso
	rm $(OUT).bin
	rm $(OUT).iso

