#include "vga.h"

u16 vgaEntry(unsigned char ch, VgaColor fore_color, VgaColor back_color) {
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

void clearVgaBuffer(u16** buffer, VgaColor fore_color, VgaColor back_color) {
	for(u32 i = 0; i < VGA_BUFSIZE; i++){
		(*buffer)[i] = vgaEntry(NULL, fore_color, back_color);
	}
}

void initVga(u16** buffer, VgaColor fore_color, VgaColor back_color) {
	*buffer = (u16*)VGA_ADDRESS;  //point buffer pointer to VGA_ADDRESS 
	clearVgaBuffer(buffer, fore_color, back_color);  //clear buffer
}

void printf(const char* text, ...) {
	
}

