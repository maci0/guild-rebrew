#include <stdio.h>

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

extern char s_6750e8[];
#include <stdlib.h>
#include <string.h>

typedef struct TexDesc {
	int pad0;
	int w;
	int h;
	int pad0c[2];
	unsigned char bpp;
	char pad15[3];
	int rest[0x11];
} TexDesc;

extern int g_67d920;

int __cdecl fcn_00475830(const char* name);
void* __cdecl fcn_004770a0(TexDesc* d, int fmt);
void __cdecl fcn_00475fd0(void* t);
void __cdecl fcn_00475a00(const char* name, void* t);
void __cdecl fcn_00476060(void* t);

/* ADDRESS: GOLDTL 0x00475830 */
int __cdecl fcn_00475830(const char* name)
{
	BmpInfo bi;
	FILE* f;

	f = fopen(name, s_6750e8);
	if (f) {
		fseek(f, 14, SEEK_SET);
		fread(&bi, 1, 0x28, f);
		fclose(f);
		if (bi.planes == 1 && bi.bits == 0x18 && bi.compression == 0) {
			return (bi.height << 16) | bi.width;
		}
		return -2;
	}
	return -1;
}

/* ADDRESS: GOLDTL 0x00475c10 */
void* __cdecl fcn_00475c10(const char* name)
{
	TexDesc d;
	int r;
	int w;
	int h;
	void* t;

	memset(&d, 0, sizeof(d));
	r = fcn_00475830(name);
	if (r < 0) {
		return 0;
	}
	w = r & 0xffff;
	h = r >> 16;
	if (h < 0) {
		h = abs(h);
	}
	d.w = w;
	d.h = h;
	d.bpp = 0x18;
	if (w <= g_67d920 && h <= g_67d920) {
		t = fcn_004770a0(&d, 2);
	} else {
		t = fcn_004770a0(&d, 0x22);
	}
	if (!t) {
		return 0;
	}
	fcn_00475fd0(t);
	fcn_00475a00(name, t);
	fcn_00476060(t);
	return t;
}
