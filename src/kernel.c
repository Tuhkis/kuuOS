#include "kernel.h"

u16* vga_buffer;

/*
16 bit video buffer elements(register ax)
8 bits(ah) higher : 
  lower 4 bits - forec olor
  higher 4 bits - back color

8 bits(al) lower :
  8 bits : ASCII character to print
*/
u16 vga_entry(unsigned char ch, u8 fore_color, u8 back_color) {
  u16 ax = 0;
  u8 ah = 0, al = 0;

  ah = back_color;
  ah <<= 4;
  ah |= fore_color;
  ax = ah;
  ax <<= 8;
  al = ch;
  ax |= al;

  return ax;
}

//clear video buffer array
void clear_vga_buffer(u16 **buffer, u8 fore_color, u8 back_color) {
	u32 i;
	for(i = 0; i < BUFSIZE; i++){
		(*buffer)[i] = vga_entry(NULL, fore_color, back_color);
	}
}

//initialize vga buffer
void init_vga(u8 fore_color, u8 back_color) {
	vga_buffer = (u16*)VGA_ADDRESS;  //point vga_buffer pointer to VGA_ADDRESS 
	clear_vga_buffer(&vga_buffer, fore_color, back_color);  //clear buffer
}

void kernel_entry() {
	//first init vga with fore & back colors
	init_vga(WHITE, BLACK);

	//assign each ASCII character to video buffer
	//you can change colors here
	vga_buffer[0] = vga_entry('H', WHITE, BLACK);
	vga_buffer[1] = vga_entry('e', WHITE, BLACK);
	vga_buffer[2] = vga_entry('l', WHITE, BLACK);
	vga_buffer[3] = vga_entry('l', WHITE, BLACK);
	vga_buffer[4] = vga_entry('o', WHITE, BLACK);
	vga_buffer[5] = vga_entry(' ', WHITE, BLACK);
	vga_buffer[6] = vga_entry('W', WHITE, BLACK);
	vga_buffer[7] = vga_entry('o', WHITE, BLACK);
	vga_buffer[8] = vga_entry('r', WHITE, BLACK);
	vga_buffer[9] = vga_entry('l', WHITE, BLACK);
	vga_buffer[10] = vga_entry('d', WHITE, BLACK);
}

