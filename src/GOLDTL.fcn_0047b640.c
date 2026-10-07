#include <string.h>

#include "rgb.h"

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
extern Rgb g_100f1a0;

Tiles* __cdecl fcn_0047abd0(int, int);
Tex* __cdecl fcn_004770a0(TexDesc* d, int fmt);
void __cdecl fcn_00476620(int, int, int, int, Img*, int, int, Tex*);
int __cdecl fcn_00475fd0(Tex*);
void __cdecl fcn_00476a50(int, int, Tex*, Rgb*);
void __cdecl fcn_00476b10(int, int, unsigned char, unsigned char, unsigned char, Tex*);
void __cdecl fcn_00476060(Tex*);
void __cdecl fcn_00475f80(Tex*);
void __cdecl fcn_004760e0(Tex*);
long __stdcall fcn_006114ff(void*, void*, void*, void*, void*, void*, int, unsigned int);

// FUNCTION: GOLDTL 0x47b640
Tiles* __cdecl fcn_0047b640(int x, int y, int w, int h, Img* img, int size)
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
	res = fcn_0047abd0(cells, cells);
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
		t = fcn_004770a0(&d, 0);
		g_77260c++;
		fcn_00476620(i % cols * tile + x, i / cols * tile + y, tile, tile, img, 0, 0, t);
		if (g_100f1a0.r || g_100f1a0.g || g_100f1a0.b) {
			Rgb px;

			fcn_00475fd0(t);
			for (px_y = 0; px_y < tile; px_y++) {
				for (px_x = 0; px_x < tile; px_x++) {
					fcn_00476a50(px_x, px_y, t, &px);
					if (px.r == g_100f1a0.r && px.g == g_100f1a0.g && px.b == g_100f1a0.b) {
						fcn_00476b10(px_x, px_y, 0, 0, 0, t);
					}
				}
			}
			fcn_00476060(t);
		}
		memset(&d, 0, sizeof(d));
		d.w = tile;
		d.h = tile;
		if (g_67dabc) {
			d.fmt = 0x35545844;
		} else {
			d.fmt = g_67dab8;
		}
		t2 = fcn_004770a0(&d, 0);
		fcn_006114ff(t2->surf, 0, 0, t->surf, 0, 0, -1, 0xff000000);
		fcn_00475f80(t);
		fcn_004760e0(t2);
		g_772610 += t2->bytes;
		res->tex[i] = t2;
	}
	return res;
}
