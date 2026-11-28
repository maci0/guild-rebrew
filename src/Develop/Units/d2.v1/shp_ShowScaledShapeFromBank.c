

#include <stdio.h>
#include <stdlib.h>

extern int shp_SuppressDraw;
extern int d2_RenderSurfaceWidth;
extern short g_7725f0;
extern short g_7725f2;
extern char g_67da68[];

int __cdecl gfx_CreateSurface(int a1, int a2, char* a3, char* e, int s);
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
	if (shp_SuppressDraw == 0) {
		save = d2_RenderSurfaceWidth;
		d2_RenderSurfaceWidth = *(int*) (surface + 0x10);
		switch (*(unsigned char*) (entry + 0xc)) {
		case 0:
			return 0;
		case 1:
			if (scale < 0) {
				if (alt != 0) {
					result = gfx_CreateSurface(x, y, surface, entry, abs(scale));
				} else {
					result = d2_DrawScaledRleSprite(x, y, surface, entry, abs(scale));
				}
			}
			return result;
		case 2:
			return result;
		}
		d2_RenderSurfaceWidth = save;
	}
	absScale = abs(scale);
	g_7725f0 = *(unsigned short*) (entry + 6) / absScale;
	g_7725f2 = *(unsigned short*) (entry + 0xa) / absScale;
	return result;
}
