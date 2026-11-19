#include "rgb.h"

extern int g_100f1a8;
extern Rgb g_100f1b8;

int __cdecl d2_PackColorForPixelFormat(unsigned char r, unsigned char g, unsigned char b);

/* ADDRESS: GOLDTL 0x00479e00 */
void __cdecl fcn_00479e00(unsigned char r, unsigned char g, unsigned char b)
{
	int c;

	c = d2_PackColorForPixelFormat(r, g, b);
	g_100f1a8 = (c << 16) | c;
	g_100f1b8.r = r;
	g_100f1b8.g = g;
	g_100f1b8.b = b;
}
