#include <stdio.h>
#include <string.h>

#include "client_types.h"
#include "Develop/Units/d2.v1/d2_gui.h"

typedef struct
{
	int i[0x2f4 / 4];
} fcn_00466550_Ent;

typedef struct
{
	unsigned short id;
	unsigned short w;
	unsigned short h;
	unsigned short pad6;
} fcn_00466550_Glyph;

extern Fld_102d140 g_102d140[];
extern char* g_1015ea0;
extern int g_67d370;
extern int g_67d374;
extern int g_67d398;
extern int g_67d964;
extern int g_67d968;
extern char* g_772500;
extern int g_77250c;
extern int g_772568;
extern int g_7725d0;
extern int g_7725f8;
extern int g_7725fc;
extern float g_6628a8;
extern double g_662908;
extern double g_662950;

int __cdecl fcn_0046b520(char* s, int font);
void __cdecl fcn_0046bbc0(int x, int y, int surf, char* text, int flags);
void __cdecl fcn_0046bd20(int x, int y, int w, int h, int surf, char* text, int flags);
void __cdecl fcn_00472880(int font);
void __cdecl fcn_0047a040(int a, int b, int c, int d);
fcn_00466550_Glyph* __cdecl fcn_0047b620(char* font, int c);
void __cdecl fcn_0047cba0(int x, int y, int surf, char* font, int c);
void __cdecl fcn_0047cbf0(int x, int y, int surf, char* font, int c);

/* ADDRESS: GOLDTL 0x00466550 */
void __cdecl fcn_00466550(int idx, int surf)
{
	Fld_102d140* f;
	fcn_00466550_Ent* e;
	fcn_00466550_Glyph* g0;
	fcn_00466550_Glyph* g1;
	fcn_00466550_Glyph* g2;
	char* font;
	unsigned int flags;
	int w0;
	int v;
	int n;
	int i;
	int y;
	int width;
	char buf[32];
	char buf2[32];
	char buf3[40];

	f = &g_102d140[idx];
	fcn_00472880(f->font);
	flags = f->flags;
	if (flags & 1) {
		if (f->def == -1 && !(flags & 0x200)) {
			f->w = fcn_0046b520(((char*) f + 0x2c), f->font);
		} else {
			f->w = *(int*) (g_1015ea0 + f->ent * 0x2f4 + 0x18);
		}
		if (f->w < 0x30) {
			f->w = 0x30;
		}
		v = *(int*) ((char*) f + 0x15c);
		if (v >= 1) {
			if (f->w < v) {
				v = f->w;
			}
			f->w = v;
		}
		fcn_0047a040(0, 0, g_1040494, g_1040490);
		*(int*) (g_1015ea0 + f->ent * 0x2f4 + 0x18) = f->w;
		if (*(int*) (g_1015ea0 + f->ent * 0x2f4 + 0x3c) != 0 || g_67d370 == f->ent) {
			fcn_0046bbc0(f->x, f->y, surf, ((char*) f + 0x2c), 2);
		} else {
			fcn_0046bbc0(f->x, f->y, surf, ((char*) f + 0x2c), 0);
		}
	} else if (flags & 2) {
		v = f->max;
		for (n = 0; n < 10; n++) {
			if (v <= 0) {
				break;
			}
			v /= 10;
		}
		f->digits = n;
		if (flags & 4) {
			v = f->f140 * f->f12c;
			if (v < 1000) {
				sprintf(buf, (char*) 0x67d464, v);
			} else if (v < 1000000) {
				sprintf(buf, (char*) 0x67d45c, (double) v * *(double*) 0x662a20);
			} else {
				sprintf(buf, (char*) 0x67d454, (double) v * *(double*) 0x664060);
			}
		} else if (flags & 8) {
			sprintf(buf2, (char*) 0x67d448, f->digits);
			sprintf(buf, buf2, f->f140 * f->f12c);
		} else {
			sprintf(buf, (char*) 0x67d444, f->f12c);
		}
		e = &((fcn_00466550_Ent*) g_1015ea0)[f->ent];
		if (f->def == -1) {
			font = (char*) d2_GetResourceData(*(int*) 0x67d39c);
			g0 = fcn_0047b620(font, 0);
			g1 = fcn_0047b620(font, 1);
			g2 = fcn_0047b620(font, 2);
			e->i[0x18 / 4] = f->w = g0->w + f->digits * 14 + g2->w;
			e->i[0x10 / 4] = f->x;
			v = f->w - g0->w - g1->w;
			fcn_0047cba0(f->x, e->i[0x14 / 4], surf, font, 0);
			fcn_0047cba0(f->x + f->w - g1->w, e->i[0x14 / 4], surf, font, 1);
			w0 = e->i[0x10 / 4] + g0->w;
			fcn_0047a040(w0 - 1, g_7725fc, w0 + v, g_67d968);
			i = 0;
			if (g_662950 < (double) (v / g2->w) + g_662908) {
				do {
					fcn_0047cba0(g2->w * i + g0->w + e->i[0x10 / 4],
					    e->i[0x14 / 4], surf, font, 2);
					i++;
				} while ((double) i < (double) (v / g2->w) + g_662908);
			}
			fcn_00472880(g_67d398);
			fcn_0046bd20(f->x, e->i[0x14 / 4] + 1, v, e->i[0x1c / 4],
			    surf, buf, 0x10);
		} else {
			font = (char*) d2_GetResourceData(f->def);
			e->i[0x1d4 / 4] = *(unsigned short*) (font + 6);
			e->i[0x1d8 / 4] = *(unsigned short*) (font + 8);
			if (e->i[0x60 / 4] != 0 && *(float*) (e + 0x1f4) == g_6628a8) {
				fcn_0047cbf0(f->x, f->y, surf, font, g_772568);
			} else {
				fcn_0047cba0(f->x, f->y, surf, font, g_772568);
			}
			if (*(float*) (e + 0x1f4) != g_6628a8) {
				y = (int) ((*(double*) 0x6629c8 - *(float*) (e + 0x1f4))
				    * e->i[0x1c / 4] + f->y);
				if (y > g_67d968) {
					y = g_67d968;
				}
				fcn_0047a040(g_7725f8, g_7725fc, g_67d964, y);
				fcn_0047cbf0(f->x, f->y, g_77250c, font, g_772568);
				fcn_0047a040(g_7725f8, g_7725fc, g_67d964, g_67d968);
				if (g_67d370 != e->i[0]) {
					width = (int) ((*(float*) (e + 0x1f4) <= *(double*) 0x6629c8
					    ? *(float*) (e + 0x1f4)
					    : *(double*) 0x6629c8) * *(double*) 0x662c38);
					sprintf(buf3, (char*) 0x67d43c, width);
					fcn_00472880(g_67d398 + 1);
					fcn_0046bd20(f->x,
					    e->i[0x14 / 4] + e->i[0x1c / 4] - 0xf,
					    *(unsigned short*) (font + 6), f->h, surf,
					    buf3, 0x28);
				}
			}
		}
		if (f->def != -1 && !(flags & 0x100) && f->f12c != 0
		    && !(flags & 0x20)) {
			if (e->i[0x3c / 4] != 0) {
				fcn_0046bbc0(f->x,
				    f->y + *(short*) (g_772500 + f->def * 0x54 + 0x52),
				    surf, buf, 2);
			} else {
				fcn_0046bbc0(f->x,
				    f->y + *(short*) (g_772500 + f->def * 0x54 + 0x52),
				    surf, buf, 0);
			}
		} else {
			strcpy(((char*) f + 0x2c), buf);
		}
	}
	if (g_67d374 != -1
	    && *(char*) (g_1015ea0 + f->ent * 0x2f4 + 0xcc) != 0
	    && g_1015ea0 + g_67d374 * 0x2f4 == g_1015ea0 + f->ent * 0x2f4
	    && g_7725d0 == 0) {
		*(int*) 0x7725a4 = (int) (g_1015ea0 + f->ent * 0x2f4);
		*(int*) 0x7725a0 = *(int*) (g_1015ea0 + f->ent * 0x2f4 + 0x40);
	}
}
