#include "vga.h"
#include "string.h"
#include "int.h"

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

void print(VgaContext* vga, const char* text) {
	for (u16 i = 0; i < strlen(text); ++i) {
		if (text[i] == '\n') {
			vga->count += 30;
		} else {
			vga->vgaBuffer[vga->count] = vgaEntry(text[i], VGA_WHITE, VGA_BLACK);
			++vga->count;
		}
	}
}

void printNum(VgaContext* vga, u32 num) {
	u16 c = 0;
	u32 nr = reverseInt(num);
	for (u16 i = 0; i < countDigits(nr); ++i) {
 		unsigned long vpow = 1;
 		for(u8 d = 0; d < (i); d++)
   			vpow *= 10;
		u8 n = (nr / vpow) % 10;

		char* a = "0";
		a[0] = num2char(n);
		print(vga, a);
	}
}

