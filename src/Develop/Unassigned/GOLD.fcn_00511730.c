extern unsigned char* g_7e3f30;


/* Twin of GOLDTL 0x514e80; GOLD keeps the flag byte at 0x212 and uses bits 2/3, not 0/1. */

#include <string.h>

char __cdecl fcn_00511730(char* o)
{
	unsigned char* t;

	if (strncmp(o, "gb_", 3) == 0) {
		t = 0;
		if (o[0x4b] == 2) {
			t = g_7e3f30 + (*(int*) (o + 0x48) & 0xffffff) * 0x24d;
		}
		if (t == 0) {
			if (strstr(o, "_TOR_") == 0) {
				o[0x212] = (o[0x212] & 0xf7) | 4;
				return 1;
			}
		} else if (*t != 0x1f) {
			o[0x212] = (o[0x212] & 0xf7) | 4;
			return 1;
		} else {
			o[0x212] |= 0xc;
		}
	}
	return 1;
}
