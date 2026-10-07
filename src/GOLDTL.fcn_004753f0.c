#include <stdio.h>
#include <string.h>

typedef struct BmpInfo {
	int size;
	int width;
	int height;
	unsigned short planes;
	unsigned short bits;
	int compression;
	int image_size;
	int xppm;
	int yppm;
	int clr_used;
	int clr_important;
} BmpInfo;
// SIZE 0x28

typedef struct Quad {
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
} Quad;
// SIZE 4

extern char s_6750e8[];

// FUNCTION: GOLDTL 0x4753f0
void __cdecl fcn_004753f0(const char* name, unsigned char* pal)
{
	BmpInfo bi;
	Quad quads[0x100];
	FILE* f;
	int i;

	memset(pal, 0, 0x300);
	f = fopen(name, s_6750e8);
	if (!f) {
		return;
	}
	fseek(f, 14, SEEK_SET);
	fread(&bi, 1, 0x28, f);
	if (bi.clr_used == 0) {
		bi.clr_used = 0x100;
	}
	fread(quads, 4, bi.clr_used, f);
	fclose(f);
	for (i = 0; i < bi.clr_used; i++) {
		pal[i * 4] = quads[i].r;
		pal[i * 4 + 1] = quads[i].g;
		pal[i * 4 + 2] = quads[i].b;
	}
}
