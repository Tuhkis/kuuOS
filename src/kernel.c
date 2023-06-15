#include "kernel.h"
#include "vga.h"

void kernel_entry() {
	u16* vgaBuffer;
	initVga(&vgaBuffer, VGA_WHITE, VGA_BLACK);

	const char* text = "Hello world!";
	for (u8 i = 0; i < 12; ++i)
		vgaBuffer[i] = vgaEntry(text[i], VGA_BLACK, VGA_WHITE);
}

