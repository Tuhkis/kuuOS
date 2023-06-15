#ifndef KERNEL_H
#define KERNEL_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

#define NULL 0

enum vga_color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARK_GREY,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_MAGENTA,
    YELLOW,
    WHITE,
};

#endif
