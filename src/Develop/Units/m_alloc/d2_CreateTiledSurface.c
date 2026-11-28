#include <string.h>

#include "Develop/Units/d2.v1/rgb.h"

typedef struct TexDesc {
	int pad0;
	int w;
	int h;
	int rest[7];
	int fmt;
	int rest2[0xc];
} TexDesc;
// SIZE 0x5c

typedef struct Tex {
	char pad0[0x24];
	void* surf;
	char pad28[0x4c - 0x28];
	int bytes;
} Tex;

typedef struct Img {
	char pad0[0x28];
	int fmt;
} Img;

typedef struct Tiles {
	short x;
	short w;
	short y;
	short h;
	char pad8[0x28 - 8];
	Tex** tex;
	int pad2c;
	int* hdr;
	int tile;
} Tiles;
// SIZE 0x38

extern int g_67dac0;
extern int g_67dabc;
extern int g_67dab8;
extern int g_77260c;
extern int g_772610;
extern RGB_COLOR g_100f1a0;

Tiles* __cdecl d2_AllocShapeBuffer(int, int);
Tex* __cdecl d2_CreateSurface(TexDesc* d, int fmt);
void __cdecl d2_BlitSurfaceToSurface(int, int, int, int, Img*, int, int, Tex*);
int __cdecl d2_LockSurface(Tex*);
void __cdecl d2_ReadSurfacePixel(int, int, Tex*, RGB_COLOR*);
void __cdecl d2_WriteSurfacePixel(int, int, unsigned char, unsigned char, unsigned char, Tex*);
void __cdecl d2_UnlockSurface(Tex*);
void __cdecl d2_ReleaseSurface(Tex*);
void __cdecl d2_UpdateTextureBytes(Tex*);
long __stdcall fcn_006114ff(void*, void*, void*, void*, void*, void*, int, unsigned int);

/* ADDRESS: GOLDTL 0x0047b640 */
Tiles* __cdecl d2_CreateTiledSurface(int x, int y, int w, int h, Img* img, int size)
{
	TexDesc d;
	Tiles* res;
	Tex* t;
	Tex* t2;
	int tile;
	int cols;
	int rows;
	int cells;
	int i;
	int px_x;
	int px_y;

	tile = w < h ? w : h;
	if (size) {
		tile = size;
	}
	if (tile >= g_67dac0) {
		tile = g_67dac0;
	}
	cols = (int) (w / (float) tile + 0.99f);
	rows = (int) (h / (float) tile + 0.99f);
	cells = cols * rows;
	res = d2_AllocShapeBuffer(cells, cells);
	res->w = (short) w;
	res->h = (short) h;
	res->x = 0;
	res->y = 0;
	res->hdr[0] = 0;
	res->hdr[1] = 0;
	res->tile = tile;
	for (i = 0; i < cells; i++) {
		memset(&d, 0, sizeof(d));
		d.w = tile;
		d.h = tile;
		d.fmt = img->fmt;
		t = d2_CreateSurface(&d, 0);
		g_77260c++;
		d2_BlitSurfaceToSurface(i % cols * tile + x, i / cols * tile + y, tile, tile, img, 0, 0, t);
		if (g_100f1a0.r || g_100f1a0.g || g_100f1a0.b) {
			RGB_COLOR px;

			d2_LockSurface(t);
			for (px_y = 0; px_y < tile; px_y++) {
				for (px_x = 0; px_x < tile; px_x++) {
					d2_ReadSurfacePixel(px_x, px_y, t, &px);
					if (px.r == g_100f1a0.r && px.g == g_100f1a0.g && px.b == g_100f1a0.b) {
						d2_WriteSurfacePixel(px_x, px_y, 0, 0, 0, t);
					}
				}
			}
			d2_UnlockSurface(t);
		}
		memset(&d, 0, sizeof(d));
		d.w = tile;
		d.h = tile;
		if (g_67dabc) {
			d.fmt = 0x35545844;
		} else {
			d.fmt = g_67dab8;
		}
		t2 = d2_CreateSurface(&d, 0);
		fcn_006114ff(t2->surf, 0, 0, t->surf, 0, 0, -1, 0xff000000);
		d2_ReleaseSurface(t);
		d2_UpdateTextureBytes(t2);
		g_772610 += t2->bytes;
		res->tex[i] = t2;
	}
	return res;
}
