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
// SIZE 0x5c

extern int g_67d920;

int __cdecl fcn_00475830(const char* name);
void* __cdecl fcn_004770a0(TexDesc* d, int fmt);
void __cdecl fcn_00475fd0(void* t);
void __cdecl fcn_00475a00(const char* name, void* t);
void __cdecl fcn_00476060(void* t);

// FUNCTION: GOLDTL 0x475c10
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
