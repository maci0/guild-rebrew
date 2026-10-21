#include <stdlib.h>

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

typedef struct Surface {
	char pad0[0x10];
	int pitch;
	char pad14[8];
	unsigned int* pixels;
	char pad20[8];
	int fmt;
} Surface;

void* __cdecl fcn_0064e2f9(const char*, const char*);
int __cdecl fcn_0064e48f(void*, int, int);
int __cdecl fcn_0064ebe4(void*, int, int, void*);
int __cdecl fcn_0064e1fd(void*);
void* __cdecl m_alloc(int, int);
void __cdecl m_FreeTracked(void*);

/* ADDRESS: GOLDTL 0x00475a00 */
int __cdecl fcn_00475a00(char* name, Surface* s)
{
	BmpInfo bi;
	unsigned char* buf;
	unsigned char* p;
	unsigned char* d;
	int h;
	int rev;
	int align;
	int row;
	int i;
	int y;
	int x;
	int b;
	int g;
	int r;
	unsigned char t;
	void* f;

	f = fcn_0064e2f9(name, (char*) 0x6750e8);
	if (f == 0)
		return 0;
	fcn_0064e48f(f, 0xe, 0);
	fcn_0064ebe4(&bi, 1, 0x28, f);
	fcn_0064e48f(f, bi.clr_used * 4 + 0x36, 0);
	if (bi.compression != 0 || bi.planes != 1 || bi.bits != 0x18) {
		fcn_0064e1fd(f);
		return 1;
	}
	h = bi.height;
	rev = h >= 0;
	bi.height = abs(h);
	buf = (unsigned char*) m_alloc(abs(h) * bi.width * 3,
	    (char*) 0x67d940);
	align = (bi.width * 3) & 3;
	for (i = 0; i < bi.height; i++) {
		row = rev ? bi.height - i - 1 : i;
		fcn_0064ebe4(buf + row * bi.width * 3, 1, bi.width * 3, f);
		if (align != 0)
			fcn_0064e48f(f, 4 - align, 1);
	}
	fcn_0064e1fd(f);
	p = buf + 2;
	for (i = 0; i < bi.width * bi.height; i++) {
		t = p[-2];
		p[-2] = p[0];
		p[0] = t;
		p += 3;
	}
	if (s->fmt == 0x15 || s->fmt == 0x16) {
		for (y = 0; y < bi.height; y++) {
			for (x = 0; x < bi.width; x++) {
				p = buf + (y * bi.width + x) * 3;
				b = p[0];
				d = (unsigned char*) (s->pixels + s->pitch * y + x);
				g = p[1];
				r = p[2];
				if (b + g + r == 0)
					d[3] = 0;
				else
					d[3] = 0xff;
				d[2] = p[0];
				d[1] = p[1];
				d[0] = p[2];
			}
		}
	}
	m_FreeTracked(buf);
	return 1;
}
