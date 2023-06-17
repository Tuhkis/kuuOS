#include "string.h"

u16 strlen(const char* s) {
	u16 c;
	for (c = 0; *s != '\0'; ++c) {
		++s;
	}
	return c;
}

char num2char(const u8 c) {
	return c + '0';
}

