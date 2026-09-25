// FUNCTION: GOLDTL 0x005e3d20
// SIZE: 316

#include <string.h>

// SIZE 0x5c
typedef struct {
	int pad0;
	int w;
	int h;
	int pad1[7];
	int fmt;
	int pad2[12];
} TexDesc;

// SIZE 0x10
typedef struct {
	int left;
	int top;
	int right;
	int bottom;
} Rect;

typedef struct {
	char pad0[0x10];
	int pitch;
	char pad1[8];
	unsigned short* bits;
	char pad2[4];
	void* surf;
} Tex;

extern int g_1040490;
extern int g_1040494;
extern int g_14ce86c;
extern int g_77250c;
extern unsigned short g_7ea3c0[];

Tex* __cdecl fcn_004770a0(TexDesc*, int);
void __cdecl fcn_00476620(int, int, int, int, int, int, int, Tex*);
long __stdcall fcn_006114ff(void*, void*, Rect*, void*, void*, Rect*, int, unsigned int);
void __cdecl fcn_00475fd0(Tex*);
void __cdecl fcn_00476060(Tex*);
void __cdecl fcn_00475f80(Tex*);

void __cdecl fcn_005e3d20(void)
{
	Rect src;
	Rect dst;
	TexDesc d;
	Tex* small;
	Tex* big;
	int x;
	int y;
	int k;

	memset(&d, 0, sizeof(d));
	d.w = 0xa0;
	d.h = 0x78;
	d.fmt = 0x17;
	small = fcn_004770a0(&d, 0);
	memset(&d, 0, sizeof(d));
	d.w = g_1040494;
	d.h = g_1040490;
	d.fmt = g_14ce86c;
	big = fcn_004770a0(&d, 0);
	src.left = 0;
	src.top = 0x40;
	src.right = g_1040494 - 0xa0;
	src.bottom = g_1040490 - 0x40;
	dst.left = 0;
	dst.right = 0xa0;
	dst.top = 0;
	dst.bottom = 0x78;
	fcn_00476620(0, 0, g_1040494, g_1040490, g_77250c, 0, 0, big);
	fcn_006114ff(small->surf, 0, &dst, big->surf, 0, &src, 4, 0xff000000);
	fcn_00475fd0(small);
	k = 0;
	for (y = 0; y < 0x78; y++) {
		for (x = 0; x < 0xa0; x++) {
			g_7ea3c0[k++] = small->bits[small->pitch * y + x];
		}
	}
	fcn_00476060(small);
	fcn_00475f80(small);
	fcn_00475f80(big);
}
