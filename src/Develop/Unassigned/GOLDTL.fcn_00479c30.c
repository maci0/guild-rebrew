

#include <stdio.h>
#include <stdlib.h>

extern int g_100ef80;
extern int g_67d96c;
extern short g_7725f0;
extern short g_7725f2;
extern char g_67da68[];

int __cdecl fcn_00478cb0(int a1, int a2, char* a3, char* e, int s);
int __cdecl d2_DrawScaledRleSprite(int a1, int a2, char* a3, char* e, int s);

int __cdecl shp_ShowScaledShapeFromBank(int x, int y, char* surface, char* bank, int shapeIndex, char scale, int alt)
{
	char buf[0x80];
	char* entry;
	int save;
	int absScale;
	int result;

	result = 1;
	if (bank == 0) {
		return 0;
	}
	if (shapeIndex > *(unsigned short*) (bank + 0x2a)) {
		sprintf(buf, g_67da68, bank + 0xa);
		return 0;
	}
	entry = bank + *(int*) (bank + shapeIndex * 4 + 0x45);
	if (g_100ef80 == 0) {
		save = g_67d96c;
		g_67d96c = *(int*) (surface + 0x10);
		switch (*(unsigned char*) (entry + 0xc)) {
		case 0:
			return 0;
		case 1:
			if (scale < 0) {
				if (alt != 0) {
					result = fcn_00478cb0(x, y, surface, entry, abs(scale));
				} else {
					result = d2_DrawScaledRleSprite(x, y, surface, entry, abs(scale));
				}
			}
			return result;
		case 2:
			return result;
		}
		g_67d96c = save;
	}
	absScale = abs(scale);
	g_7725f0 = *(unsigned short*) (entry + 6) / absScale;
	g_7725f2 = *(unsigned short*) (entry + 0xa) / absScale;
	return result;
}
