

/* GOLD twin of GOLDTL fcn_0045c290: the texture slot is 0x80 bytes here,
 * 0x70 in GOLDTL. */

#include "g_fb9074.h"

// SIZE 0x4
typedef struct Col {
	unsigned char a;
	unsigned char b;
	unsigned char c0 : 1;
	unsigned char c1 : 1;
	unsigned char c2 : 6;
	unsigned char d;
} Col;

extern TexSlot* g_fb9074;
extern unsigned int g_fb9084;
extern unsigned int g_fb91a8;

TexSlot* __cdecl fcn_00460120(Col c, int* out)
{
	TexSlot* t;
	int i;

	if (g_fb91a8 == g_fb9084) {
		if (out != 0) {
			*out = -1;
		}
		return 0;
	}
	if (c.a >= 0xff && !c.c0) {
		for (i = 0, t = g_fb9074; t->refs > 0; i++, t++) {
		}
	} else {
		for (i = g_fb9084 - 1, t = &g_fb9074[i]; t->refs > 0; i--, t--) {
		}
	}
	if (out != 0) {
		*out = i;
	}
	return t;
}
