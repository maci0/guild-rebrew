

#include <stdio.h>
#include <stdlib.h>

extern int g_00f8a630; /* 0x00f8a630 */
extern int g_005fed64; /* 0x005fed64 */
extern short g_006f044c; /* 0x006f044c */
extern short g_006f044e; /* 0x006f044e */
extern char g_005feea8[]; /* 0x005feea8 */

int __cdecl d2_DrawScaledRemappedRleSprite(int x, int y, char* surface, char* e, int s);
int __cdecl d2_DrawScaledRleSprite(int x, int y, char* surface, char* e, int s);

int __cdecl d2_DrawOrMeasureSpriteFrame(int x, int y, char* context, char* h, unsigned char idx, char scale, int alt)
{
	char buf[0x80];
	char* e;
	int save;
	int s;
	int r;

	r = 1;
	if (h == 0) {
		return 0;
	}
	if (idx > *(unsigned short*) (h + 0x2a)) {
		sprintf(buf, g_005feea8, h + 0xa);
		return 0;
	}
	e = h + *(int*) (h + idx * 4 + 0x45);
	if (g_00f8a630 == 0) {
		save = g_005fed64;
		g_005fed64 = *(int*) (context + 0x10);
		switch (*(unsigned char*) (e + 0xc)) {
		case 0:
			return 0;
		case 1:
			if (scale < 0) {
				if (alt != 0) {
					r = d2_DrawScaledRemappedRleSprite(x, y, context, e, abs(scale));
				} else {
					r = d2_DrawScaledRleSprite(x, y, context, e, abs(scale));
				}
			}
			return r;
		case 2:
			return r;
		}
		g_005fed64 = save;
	}
	s = abs(scale);
	g_006f044c = *(unsigned short*) (e + 6) / s;
	g_006f044e = *(unsigned short*) (e + 0xa) / s;
	return r;
}
