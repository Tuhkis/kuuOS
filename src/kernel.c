#include "kernel.h"
#include "vga.h"
#include "keyboard.h"

 void enableNmi() {
	outb(0x70, inb(0x70) & 0x7F);
	inb(0x71);
 }
 
 void disableNmi() {
	outb(0x70, inb(0x70) | 0x80);
	inb(0x71);
 }

void kernel_entry() {
	disableNmi();

	VgaContext vga = {0, 0};
	initVga(&vga.vgaBuffer, VGA_WHITE, VGA_BLACK);

	const char* text = "NEVER GONNA GIVE YOU UP, NEVER GONNA LET YOU DOWN.\nAA";
	print(&vga, text);
}

