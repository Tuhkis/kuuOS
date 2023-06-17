#ifndef VGA_H
#define VGA_H

#include "kernel.h"

#define VGA_ADDRESS 0xB8000
#define VGA_BUFSIZE 2200

typedef struct {
	u16* vgaBuffer;
	u32 count;
	u32 cursorX, cursorY;
} VgaContext;

typedef enum {
    VGA_BLACK,
    VGA_BLUE,
    VGA_GREEN,
    VGA_CYAN,
    VGA_RED,
    VGA_MAGENTA,
    VGA_BROWN,
    VGA_GREY,
    VGA_DARK_GREY,
    VGA_BRIGHT_BLUE,
    VGA_BRIGHT_GREEN,
    VGA_BRIGHT_CYAN,
    VGA_BRIGHT_RED,
    VGA_BRIGHT_MAGENTA,
    VGA_YELLOW,
    VGA_WHITE,
} VgaColor;

u16 vgaEntry(unsigned char ch, VgaColor fore_color, VgaColor back_color);
void clearVgaBuffer(u16** buffer, VgaColor fore_color, VgaColor back_color);
void initVga(u16** buffer, VgaColor fore_color, VgaColor back_color);
void vgaMoveCursor(VgaContext vga);

void print(VgaContext* vga, const char* text);
void printNum(VgaContext* vga, u32 num);
void printf(VgaContext* vga, const char* t, ...);

#endif // VGA_H
