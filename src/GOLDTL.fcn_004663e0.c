#include <stdlib.h>

typedef struct
{
	unsigned short f0;
	unsigned short w;
	unsigned short f4;
	unsigned short h;
} fcn_004663e0_Glyph;
// SIZE 0x8

typedef struct
{
	int i[0x2f4 / 4];
} fcn_004663e0_Ent;
// SIZE 0x2f4

extern char* g_1015ea0;
extern int g_67d394;
extern int g_67d398;
extern int g_1040490;
extern int g_1040494;
extern short g_14ce8c2;
extern int g_102d028;
extern int g_102d02c;

char* __cdecl fcn_00466190(int id);
fcn_004663e0_Glyph* __cdecl fcn_0047b620(char* font, int c);
void __cdecl fcn_0047a040(int a, int b, int c, int d);
void __cdecl fcn_0047cba0(int x, int y, int surf, char* font, int c);
void __cdecl fcn_00472880(int font);
void __cdecl fcn_0046bd20(int x, int y, int w, int h, int surf, char* text, int flags);

// FUNCTION: GOLDTL 0x4663e0
void __cdecl fcn_004663e0(char* f, int surf)
{
	fcn_004663e0_Ent* e;
	char* font;
	fcn_004663e0_Glyph* g0;
	fcn_004663e0_Glyph* g1;
	fcn_004663e0_Glyph* g2;
	fcn_004663e0_Glyph* g3;
	int x;
	int y;
	char buf[24];

	e = &((fcn_004663e0_Ent*)g_1015ea0)[*(int*) (f + 0x134)];
	font = fcn_00466190(g_67d394);
	g0 = fcn_0047b620(font, 0);
	g1 = fcn_0047b620(font, 1);
	g2 = fcn_0047b620(font, 2);
	g3 = fcn_0047b620(font, 3);
	x = e->i[0x10 / 4] - 0x20;
	y = *(int*) (f + 0x20) - g0->h - 0x64;
	fcn_0047a040(0, 0, g_1040494, g_1040490);
	fcn_0047cba0(x, y, surf, font, 0);
	fcn_0047cba0(x, g0->h + y + 0x64, surf, font, 1);
	fcn_0047cba0(x, g0->h + y, surf, font, 2);
	y = g_14ce8c2 - g3->h / 2;
	x += g0->w / 2 - g3->w / 2;
	fcn_0047cba0(x, y, surf, font, 3);
	g_102d028 = x;
	g_102d02c = y;
	if (*(int*) (f + 0x12c) < 100000 && *(int*) (f + 0x12c) > -100000) {
		fcn_00472880(g_67d398 + 1);
		_itoa(*(int*) (f + 0x12c), buf, 10);
		fcn_0046bd20(x, y, g3->w, g3->h, surf, buf, 8);
	}
}
