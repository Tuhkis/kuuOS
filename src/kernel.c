#include "kernel.h"
#include "vga.h"
#include "keyboard.h"
#include "string.h"
#include "int.h"

#include "../external/multiboot.h"

 void enableNmi() {
	outb(0x70, inb(0x70) & 0x7F);
	inb(0x71);
}
 
 void disableNmi() {
	outb(0x70, inb(0x70) | 0x80);
	inb(0x71);
}

void* memset(void* b, i32 val, u16 count) {
	asm volatile ("cld; rep stosb" : "+c" (count), "+D" (b) : "a" (val) : "memory");
	return b;
}

void kernelEntry(multiboot_info_t* mbd, u32 magic) {
	VgaContext vga = {0, 0, 0, 0};
	initVga(&vga.vgaBuffer, VGA_WHITE, VGA_BLACK);
	disableNmi();
	// WARN: That's bad, but I don't really care...
	/* if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		print(&vga, "INVALID HEADER MAGIC NUMBER\n");
	}*/
	if(!(mbd->flags >> 6 & 0x1)) {
		print(&vga, "ERROR: invalid memory map given by GRUB bootloader\n");
	}

	asm volatile ("int $0x3");
	asm volatile ("int $0x4"); 

	/* for(u32 i = 0; i < mbd->mmap_length; 
        i += sizeof(multiboot_memory_map_t)) {
		multiboot_memory_map_t* mmmt = 
		(multiboot_memory_map_t*) (mbd->mmap_addr + i);
 
		printf("Start Addr: %x | Length: %x | Size: %x | Type: %d\n",
		mmmt->addr, mmmt->len, mmmt->size, mmmt->type);
 
		if(mmmt->type == MULTIBOOT_MEMORY_AVAILABLE) {
		}
	}*/
}

